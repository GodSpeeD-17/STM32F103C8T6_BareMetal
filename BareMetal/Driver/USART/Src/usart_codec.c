/**
 * @file	usart_codec.c
 * @author	Shrey Shah
 * @brief	USART Selector Codec Implementation
 * @version	v1.0
 * @date	23-08-2026
 *
 * @details
 * This source file implements the USART codec layer. It encodes
 * driver-facing USART selectors into raw STM32F1 USART fields, decodes raw
 * fields back into driver-facing selectors, and returns updated
 * caller-owned register images. It does not read or write peripheral
 * hardware.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "usart_codec.h"

// ==================================================================================================== //
//												Local Defines											//
// ==================================================================================================== //

/** @brief Width of a one-bit USART register field @def USART_CODEC_FIELD_WIDTH_1BIT */
#define USART_CODEC_FIELD_WIDTH_1BIT				((reg_field_width_t) 0x01U)
/** @brief Baud-rate preset count @def USART_CODEC_BAUD_RATE_PRESET_COUNT */
#define USART_CODEC_BAUD_RATE_PRESET_COUNT			((uint8_t) 0x08U)
/** @brief USART `SR` flags with write-0-to-clear behavior @def USART_CODEC_SR_W0C_FLAG_MASK */
#define USART_CODEC_SR_W0C_FLAG_MASK				(USART_SR_TC | USART_SR_CTS)

/**
 * @brief Fixed-point scale factor representing `USARTDIV` as an integer (`USARTDIV x100`)
 * @def USART_CODEC_BRR_DIV_SCALE_FACTOR
 * @see RM0008 Section 27.3.4 Fractional baud rate generation
 */
#define USART_CODEC_BRR_DIV_SCALE_FACTOR			100UL
/**
 * @brief RM0008's 16x oversampling divisor in `baud = fCK / (16 * USARTDIV)`
 * @def USART_CODEC_BRR_OVERSAMPLING
 * @details
 * The same constant also equals the number of fractional steps encoded by
 * `BRR.DIV_FRACTION` (`2^4 = 16`) — the fraction field expresses 16ths of
 * one mantissa unit precisely because the hardware oversamples by 16.
 * @see RM0008 Section 27.3.4 Fractional baud rate generation
 */
#define USART_CODEC_BRR_OVERSAMPLING				16UL
/**
 * @brief Half of @ref USART_CODEC_BRR_DIV_SCALE_FACTOR
 * @def USART_CODEC_BRR_DIV_SCALE_HALF
 * @details Added before an integer division to round to nearest instead of
 * truncating toward zero.
 */
#define USART_CODEC_BRR_DIV_SCALE_HALF				(USART_CODEC_BRR_DIV_SCALE_FACTOR / 2UL)

// ==================================================================================================== //
//										Local Baud-Rate Preset Table									//
// ==================================================================================================== //

/**
 * @brief Numeric bits-per-second value for each supported @ref usart_baud_rate_t preset
 * @details Indexed by the preset's ordinal selector value.
 */
static const uint32_t __usartCodecBaudRatePresetTable__[USART_CODEC_BAUD_RATE_PRESET_COUNT] =
{
	[USART_BAUD_RATE_9600]		= 9600UL,
	[USART_BAUD_RATE_19200]		= 19200UL,
	[USART_BAUD_RATE_38400]		= 38400UL,
	[USART_BAUD_RATE_57600]		= 57600UL,
	[USART_BAUD_RATE_115200]	= 115200UL,
	[USART_BAUD_RATE_230400]	= 230400UL,
	[USART_BAUD_RATE_460800]	= 460800UL,
	[USART_BAUD_RATE_921600]	= 921600UL,
};

// ==================================================================================================== //
//										Local Register Image Helpers									//
// ==================================================================================================== //

/**
 * @brief Validates whether a state selector is an accepted ON/OFF state
 * @param[in] state Driver state selector
 * @returns @ref driver_status_t "Binary-state validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `state` is accepted
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `state` is not @ref `DRIVER_STATUS_OFF` or @ref `DRIVER_STATUS_ON`
 */
__STATIC_FORCEINLINE driver_status_t Codec_USART_ValidateState(const driver_status_t state)
{
	//! Codec binary state helpers accept only explicit OFF/ON states, never generic SUCCESS/ERROR states.
	if ((state != DRIVER_STATUS_OFF) && (state != DRIVER_STATUS_ON))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Extracts one positive-polarity bit state from a register image
 * @param[in] regImage Caller-owned register image
 * @param[in] bitMask Register-positioned bit mask
 * @returns @ref driver_status_t "Decoded state"
 * @retval - @ref `DRIVER_STATUS_OFF`: @p `bitMask` is clear in @p `regImage`
 * @retval - @ref `DRIVER_STATUS_ON`: @p `bitMask` is set in @p `regImage`
 */
__STATIC_FORCEINLINE driver_status_t Codec_USART_ExtractBitStateFromImage(const reg regImage, const reg bitMask)
{
	//! Positive-polarity hardware bit convention: clear means OFF, set means ON.
	if ((regImage & bitMask) != 0x00000000UL)
	{
		return DRIVER_STATUS_ON;
	}
	else
	{
		return DRIVER_STATUS_OFF;
	}
}

/**
 * @brief Stages one positive-polarity bit state inside a register image
 * @param[in,out] pRegImage Caller-owned register image to update in place
 * @param[in] bitMask Register-positioned bit mask
 * @param[in] state Requested ON/OFF state
 * @returns @ref driver_status_t "Staging status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `bitMask` was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pRegImage` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `state` is not an accepted state
 */
__STATIC_FORCEINLINE driver_status_t Codec_USART_StageBitStateInImage
(
	reg* const				pRegImage,
	const reg				bitMask,
	const driver_status_t	state
)
{
	// Validate Input
	if (pRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_USART_ValidateState(state));

	// Local Variable
	reg updatedRegImage = *pRegImage;

	//! Convert the driver ON/OFF state into the raw bit value and stage only that bit.
	if (state == DRIVER_STATUS_ON)
	{
		updatedRegImage |= bitMask;
	}
	else
	{
		updatedRegImage &= ~bitMask;
	}

	*pRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										USART Hardware Enable Codecs									//
// ==================================================================================================== //

driver_status_t Codec_USART_ExtractHardwareEnableState
(
	const reg						cr1RegImage,
	const reg						cr3RegImage,
	usart_hardware_enable_t* const	pHardware
)
{
	if (pHardware == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	// Local Variable
	usart_hardware_enable_t hardware = USART_HARDWARE_ENABLE_NONE;

	//! TX/RX live in CR1; RTS/CTS flow control lives in CR3 — combine into one abstract bitmask.
	if ((cr1RegImage & USART_CR1_TE) != 0x00000000UL)
	{
		hardware |= USART_HARDWARE_ENABLE_TX;
	}
	if ((cr1RegImage & USART_CR1_RE) != 0x00000000UL)
	{
		hardware |= USART_HARDWARE_ENABLE_RX;
	}
	if ((cr3RegImage & USART_CR3_RTSE) != 0x00000000UL)
	{
		hardware |= USART_HARDWARE_ENABLE_RTS;
	}
	if ((cr3RegImage & USART_CR3_CTSE) != 0x00000000UL)
	{
		hardware |= USART_HARDWARE_ENABLE_CTS;
	}

	*pHardware = hardware;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_USART_StageHardwareEnableState
(
	reg* const						pCr1RegImage,
	reg* const						pCr3RegImage,
	const usart_hardware_enable_t	hardware
)
{
	// Validate Input
	if ((pCr1RegImage == NULL) || (pCr3RegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (USART_HARDWARE_ENABLE_IS_VALID(hardware) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	// Local Variables
	reg updatedCr1RegImage = *pCr1RegImage;
	reg updatedCr3RegImage = *pCr3RegImage;

	//! Stage each pin-enable bit independently; unrelated CR1/CR3 bits are preserved.
	if ((hardware & USART_HARDWARE_ENABLE_TX) != 0x00U)
	{
		updatedCr1RegImage |= USART_CR1_TE;
	}
	else
	{
		updatedCr1RegImage &= ~USART_CR1_TE;
	}

	if ((hardware & USART_HARDWARE_ENABLE_RX) != 0x00U)
	{
		updatedCr1RegImage |= USART_CR1_RE;
	}
	else
	{
		updatedCr1RegImage &= ~USART_CR1_RE;
	}

	if ((hardware & USART_HARDWARE_ENABLE_RTS) != 0x00U)
	{
		updatedCr3RegImage |= USART_CR3_RTSE;
	}
	else
	{
		updatedCr3RegImage &= ~USART_CR3_RTSE;
	}

	if ((hardware & USART_HARDWARE_ENABLE_CTS) != 0x00U)
	{
		updatedCr3RegImage |= USART_CR3_CTSE;
	}
	else
	{
		updatedCr3RegImage &= ~USART_CR3_CTSE;
	}

	//! Update the caller-owned register images with the staged values.
	*pCr1RegImage = updatedCr1RegImage;
	*pCr3RegImage = updatedCr3RegImage;

	// Return Status
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										USART Data-Config Codecs										//
// ==================================================================================================== //

driver_status_t Codec_USART_ExtractDataConfig
(
	const reg					cr1RegImage,
	const reg					cr2RegImage,
	usart_frame_format_t* const	pFrameFormat
)
{
	// Validate Input
	if (pFrameFormat == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! `M` maps directly onto `usart_data_bits_t`; both are single-bit, exhaustively valid.
	pFrameFormat->dataBits = (usart_data_bits_t) RegOps_ExtractFieldValue(cr1RegImage, USART_CR1_M, USART_CR1_M_Pos);

	//! Parity is synthesized from PCE/PS: PCE clear means no parity regardless of PS.
	if ((cr1RegImage & USART_CR1_PCE) == 0x00000000UL)
	{
		pFrameFormat->parity = USART_PARITY_NONE;
	}
	else if ((cr1RegImage & USART_CR1_PS) == 0x00000000UL)
	{
		pFrameFormat->parity = USART_PARITY_EVEN;
	}
	else
	{
		pFrameFormat->parity = USART_PARITY_ODD;
	}

	//! `STOP[1:0]` maps directly onto `usart_stop_bits_t`'s raw-compatible encoding.
	pFrameFormat->stopBits = (usart_stop_bits_t) RegOps_ExtractFieldValue(cr2RegImage, USART_CR2_STOP, USART_CR2_STOP_Pos);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_USART_StageDataConfig
(
	reg* const							pCr1RegImage,
	reg* const							pCr2RegImage,
	const usart_frame_format_t* const	pFrameFormat
)
{
	if ((pCr1RegImage == NULL) || (pCr2RegImage == NULL) || (pFrameFormat == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (USART_DATA_BITS_IS_VALID(pFrameFormat->dataBits) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	if (USART_PARITY_IS_VALID(pFrameFormat->parity) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	if (USART_STOP_BITS_IS_VALID(pFrameFormat->stopBits) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	// Local Variables
	reg updatedCr1RegImage = *pCr1RegImage;
	reg updatedCr2RegImage = *pCr2RegImage;

	updatedCr1RegImage = RegOps_StageFieldValue
	(
		updatedCr1RegImage, USART_CR1_M_Pos, (reg) pFrameFormat->dataBits, USART_CODEC_FIELD_WIDTH_1BIT
	);

	//! Decompose the ordinal parity selector back into the PCE/PS bit pair.
	if (pFrameFormat->parity != USART_PARITY_NONE)
	{
		updatedCr1RegImage |= USART_CR1_PCE;
	}
	else
	{
		updatedCr1RegImage &= ~USART_CR1_PCE;
	}

	if (pFrameFormat->parity == USART_PARITY_ODD)
	{
		updatedCr1RegImage |= USART_CR1_PS;
	}
	else
	{
		updatedCr1RegImage &= ~USART_CR1_PS;
	}

	updatedCr2RegImage = RegOps_StageFieldValue
	(
		updatedCr2RegImage, USART_CR2_STOP_Pos, (reg) pFrameFormat->stopBits, USART_CR2_STOP_Width
	);

	*pCr1RegImage = updatedCr1RegImage;
	*pCr2RegImage = updatedCr2RegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										USART Operation-State Codecs									//
// ==================================================================================================== //

driver_status_t Codec_USART_ExtractOperationState(const reg cr1RegImage)
{
	//! UE uses normal positive polarity: clear means disabled, set means enabled.
	return Codec_USART_ExtractBitStateFromImage(cr1RegImage, USART_CR1_UE);
}

driver_status_t Codec_USART_StageOperationState
(
	reg* const				pCr1RegImage,
	const driver_status_t	operationState
)
{
	return Codec_USART_StageBitStateInImage(pCr1RegImage, USART_CR1_UE, operationState);
}

// ==================================================================================================== //
//										USART Baud Rate Codecs											//
// ==================================================================================================== //

driver_status_t Codec_USART_ExtractBaudRate
(
	const reg					brrRegImage,
	const frequency_t			busFrequency,
	usart_baud_rate_t* const	pBaudRate
)
{
	if (pBaudRate == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (busFrequency == 0x00000000UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	// Local Variables
	reg mantissa = RegOps_ExtractFieldValue(brrRegImage, USART_BRR_DIV_MANTISSA, USART_BRR_DIV_MANTISSA_Pos);
	reg fraction = RegOps_ExtractFieldValue(brrRegImage, USART_BRR_DIV_FRACTION, USART_BRR_DIV_FRACTION_Pos);
	reg rawDivider = (mantissa << USART_BRR_DIV_FRACTION_Width) | fraction;

	if (rawDivider == 0x00000000UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! `16 * USARTDIV` equals the raw 16-bit divider, so the actual baud rate is a direct division.
	uint32_t actualBaudRate = busFrequency / rawDivider;

	//! Resolve the closest supported preset; BRR quantization means this is rarely an exact match.
	uint8_t closestIndex = 0x00U;
	uint32_t closestDelta = 0xFFFFFFFFUL;
	for (uint8_t index = 0x00U; index < USART_CODEC_BAUD_RATE_PRESET_COUNT; index++)
	{
		uint32_t presetBps = __usartCodecBaudRatePresetTable__[index];
		uint32_t delta = 0x00000000UL;

		if (actualBaudRate > presetBps)
		{
			delta = actualBaudRate - presetBps;
		}
		else
		{
			delta = presetBps - actualBaudRate;
		}

		if (delta < closestDelta)
		{
			closestDelta = delta;
			closestIndex = index;
		}
	}

	*pBaudRate = (usart_baud_rate_t) closestIndex;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_USART_StageBaudRate
(
	reg* const				pBrrRegImage,
	const frequency_t		busFrequency,
	const usart_baud_rate_t	baudRate
)
{
	// Validate Input
	if (pBrrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (USART_BAUD_RATE_IS_VALID(baudRate) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	if (busFrequency == 0x00000000UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! RM0008 27.3.4: baud = fCK / (16 * USARTDIV), so USARTDIV = fCK / (16 * baud).
	//! Widen only the division to 64 bits because `busFrequency * 100` can exceed
	//! UINT32_MAX (e.g. 72 MHz * 100); the quotient always fits back in 32 bits.
	uint32_t scaledDivider = (uint32_t) (((uint64_t) busFrequency * USART_CODEC_BRR_DIV_SCALE_FACTOR) / (USART_CODEC_BRR_OVERSAMPLING * (uint64_t) __usartCodecBaudRatePresetTable__[baudRate]));

	//! scaledDivider is USARTDIV x100; splitting it by /100 and the x100 remainder
	//! recovers USARTDIV's integer part (mantissa) and fractional part (in hundredths).
	uint32_t mantissa = scaledDivider / USART_CODEC_BRR_DIV_SCALE_FACTOR;
	uint32_t fractionRemainder = scaledDivider - (mantissa * USART_CODEC_BRR_DIV_SCALE_FACTOR);

	//! DIV_FRACTION expresses the fraction in sixteenths, not hundredths, so rescale by
	//! OVERSAMPLING (x16) before dividing back out by the x100 scale. Plain integer
	//! division always truncates toward zero (e.g. 1.6 -> 1), so DIV_SCALE_HALF (half of
	//! the x100 divisor) is added first to turn that truncation into round-to-nearest
	//! (e.g. 1.6 -> 2), matching RM0008's own rounded BRR worked examples.
	uint32_t fraction = ((fractionRemainder * USART_CODEC_BRR_OVERSAMPLING) + USART_CODEC_BRR_DIV_SCALE_HALF) / USART_CODEC_BRR_DIV_SCALE_FACTOR;

	//! Rounding to nearest can push fraction up to a full 16/16, which does not fit
	//! DIV_FRACTION's 4-bit range (max 15); treat that overflow as one whole extra
	//! mantissa unit with zero fraction, the same way 1.99 rounds up to 2.0.
	if (fraction >= USART_CODEC_BRR_OVERSAMPLING)
	{
		mantissa += 1UL;
		fraction = 0UL;
	}

	//! Update the caller's BRR register image with the new mantissa/fraction values, leaving every other bit untouched.
	reg updatedBrrRegImage = *pBrrRegImage;
	updatedBrrRegImage = RegOps_StageFieldValue(updatedBrrRegImage, USART_BRR_DIV_MANTISSA_Pos, (reg) mantissa, USART_BRR_DIV_MANTISSA_Width);
	updatedBrrRegImage = RegOps_StageFieldValue(updatedBrrRegImage, USART_BRR_DIV_FRACTION_Pos, (reg) fraction, USART_BRR_DIV_FRACTION_Width);
	*pBrrRegImage = updatedBrrRegImage;

	// Return Status
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										USART IRQ Source Codecs										//
// ==================================================================================================== //

driver_status_t Codec_USART_ExtractIRQSources
(
	const reg					cr1RegImage,
	const reg					cr3RegImage,
	usart_irq_source_t* const	pSources
)
{
	// Validate Input
	if (pSources == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	// Local Variable
	usart_irq_source_t sources = USART_IRQ_SOURCE_NONE;

	//! Sources span CR1 (local status interrupts) and CR3 (CTS/error interrupts).
	if ((cr1RegImage & USART_CR1_IDLEIE) != 0x00000000UL)
	{
		sources |= USART_IRQ_SOURCE_IDLE;
	}
	if ((cr1RegImage & USART_CR1_RXNEIE) != 0x00000000UL)
	{
		sources |= USART_IRQ_SOURCE_RXNE;
	}
	if ((cr1RegImage & USART_CR1_TCIE) != 0x00000000UL)
	{
		sources |= USART_IRQ_SOURCE_TC;
	}
	if ((cr1RegImage & USART_CR1_TXEIE) != 0x00000000UL)
	{
		sources |= USART_IRQ_SOURCE_TXE;
	}
	if ((cr1RegImage & USART_CR1_PEIE) != 0x00000000UL)
	{
		sources |= USART_IRQ_SOURCE_PE;
	}
	if ((cr3RegImage & USART_CR3_CTSIE) != 0x00000000UL)
	{
		sources |= USART_IRQ_SOURCE_CTS;
	}
	if ((cr3RegImage & USART_CR3_EIE) != 0x00000000UL)
	{
		sources |= USART_IRQ_SOURCE_ERROR;
	}

	*pSources = sources;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_USART_StageIRQSources
(
	reg* const					pCr1RegImage,
	reg* const					pCr3RegImage,
	const usart_irq_source_t	sources,
	const driver_status_t		sourceState
)
{
	// Validate Input
	if ((pCr1RegImage == NULL) || (pCr3RegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (USART_IRQ_SOURCE_IS_VALID(sources) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	ASSERT_DRIVER_STATUS(Codec_USART_ValidateState(sourceState));

	// Local Variables
	reg updatedCr1RegImage = *pCr1RegImage;
	reg updatedCr3RegImage = *pCr3RegImage;

	//! Stage only the CR1/CR3 enable bits selected by `sources`, leaving every other bit untouched.
	if ((sources & USART_IRQ_SOURCE_IDLE) != 0x00U)
	{
		if (sourceState == DRIVER_STATUS_ON)
		{
			updatedCr1RegImage |= USART_CR1_IDLEIE;
		}
		else
		{
			updatedCr1RegImage &= ~USART_CR1_IDLEIE;
		}
	}

	if ((sources & USART_IRQ_SOURCE_RXNE) != 0x00U)
	{
		if (sourceState == DRIVER_STATUS_ON)
		{
			updatedCr1RegImage |= USART_CR1_RXNEIE;
		}
		else
		{
			updatedCr1RegImage &= ~USART_CR1_RXNEIE;
		}
	}

	if ((sources & USART_IRQ_SOURCE_TC) != 0x00U)
	{
		if (sourceState == DRIVER_STATUS_ON)
		{
			updatedCr1RegImage |= USART_CR1_TCIE;
		}
		else
		{
			updatedCr1RegImage &= ~USART_CR1_TCIE;
		}
	}

	if ((sources & USART_IRQ_SOURCE_TXE) != 0x00U)
	{
		if (sourceState == DRIVER_STATUS_ON)
		{
			updatedCr1RegImage |= USART_CR1_TXEIE;
		}
		else
		{
			updatedCr1RegImage &= ~USART_CR1_TXEIE;
		}
	}

	if ((sources & USART_IRQ_SOURCE_PE) != 0x00U)
	{
		if (sourceState == DRIVER_STATUS_ON)
		{
			updatedCr1RegImage |= USART_CR1_PEIE;
		}
		else
		{
			updatedCr1RegImage &= ~USART_CR1_PEIE;
		}
	}

	if ((sources & USART_IRQ_SOURCE_CTS) != 0x00U)
	{
		if (sourceState == DRIVER_STATUS_ON)
		{
			updatedCr3RegImage |= USART_CR3_CTSIE;
		}
		else
		{
			updatedCr3RegImage &= ~USART_CR3_CTSIE;
		}
	}

	if ((sources & USART_IRQ_SOURCE_ERROR) != 0x00U)
	{
		if (sourceState == DRIVER_STATUS_ON)
		{
			updatedCr3RegImage |= USART_CR3_EIE;
		}
		else
		{
			updatedCr3RegImage &= ~USART_CR3_EIE;
		}
	}

	*pCr1RegImage = updatedCr1RegImage;
	*pCr3RegImage = updatedCr3RegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										USART IRQ Event Codecs											//
// ==================================================================================================== //

driver_status_t Codec_USART_ExtractIRQEvents(const reg srRegImage, usart_event_flag_t* const pEvents)
{
	if (pEvents == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! `SR[9:0]` bit positions are identical to the public event-flag bit positions.
	*pEvents = (usart_event_flag_t) (srRegImage & USART_IRQ_EVENT_ALL);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_USART_StageIRQEventsClear
(
	reg* const					pSrRegImage,
	const usart_event_flag_t	events
)
{
	if (pSrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (USART_IRQ_EVENT_IS_VALID(events) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	// Local Variable
	reg updatedRegImage = *pSrRegImage;

	//! Only TC/CTS clear through an SR write; write 1 to every other w0c flag so it is preserved.
	const reg toClear = ((reg) events) & USART_CODEC_SR_W0C_FLAG_MASK;
	updatedRegImage |= (USART_CODEC_SR_W0C_FLAG_MASK & ~toClear);
	updatedRegImage &= ~toClear;

	*pSrRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}
