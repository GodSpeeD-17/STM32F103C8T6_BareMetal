/**
 * @file	usart.c
 * @author	Shrey Shah
 * @brief	USART Driver Implementation
 * @version	v2.0
 * @date	23-08-2026
 *
 * @details
 * @section USART_DRIVER_IMPL_SCOPE Scope
 * This source file implements the public USART driver API declared in
 * `usart.h`, for UART (asynchronous) mode only on `USART1`, `USART2`, and
 * `USART3`. The driver layer owns public validation, USART clock-state
 * verification, register-image reads, codec staging/extraction
 * orchestration, register-specific dirty-write decisions, and public
 * @ref driver_status_t handling.
 *
 * @section USART_DRIVER_IMPL_FIELD_OWNERSHIP Field Ownership
 * `USART_Config()` owns every domain represented by @ref usart_config_t:
 * `CR1.TE/RE` and `CR3.RTSE/CTSE` hardware enables, `CR1.M/PCE/PS` and
 * `CR2.STOP` frame format, and the `BRR` baud-rate divider. This source also
 * owns `CR1`/`CR3` interrupt-request sources and `SR` event
 * observation/acknowledgement. GPIO/AFIO pin configuration and its clock
 * gates are entirely application-owned, matching Timer PWM's GPIO ownership
 * model; this file never touches GPIO. The USART peripheral's own RCC clock
 * gate is likewise application-owned — every public entry point requires it
 * enabled beforehand and only verifies it through `_USART_ValidateClockEnabled()`.
 *
 * @section USART_DRIVER_IMPL_LAYOUT Source Layout
 * The public implementation follows the same banner and sub-banner order as
 * `usart.h`: operation state, root configuration, IRQ sources, then IRQ
 * events. Local helpers are kept ahead of the public functions and read as
 * orchestration over validation, codec staging, and the shared
 * `RegOps_WriteIfChanged()` dirty-write primitive.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "usart.h"
#include "usart_codec.h"
#include "usart_ll.h"
#include "rcc.h"
#include "stm32f1xx_rcc.h"

// ==================================================================================================== //
//										Local Validation Helpers										//
// ==================================================================================================== //

/**
 * @brief Validates a USART peripheral instance pointer
 * @param[in] USARTx USART peripheral instance
 * Accepted values:
 * - `USART1`
 * - `USART2`
 * - `USART3`
 * @returns @ref driver_status_t "USART-instance validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `USARTx` is supported
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `USARTx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `USARTx` is unsupported
 */
__STATIC_FORCEINLINE driver_status_t _USART_ValidateInstance(const USART_TypeDef* const USARTx)
{
	//! Reject a null pointer before evaluating the supported-instance policy.
	if (USARTx == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	if (USART_INSTANCE_IS_VALID(USARTx) != 0x00U)
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief Validates that a state selector is an accepted ON/OFF state
 * @param[in] state Driver state selector
 * @returns @ref driver_status_t "Binary-state validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `state` is accepted
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `state` is not @ref `DRIVER_STATUS_OFF` or @ref `DRIVER_STATUS_ON`
 */
__STATIC_FORCEINLINE driver_status_t _USART_ValidateState(const driver_status_t state)
{
	//! Driver binary-state parameters accept only explicit OFF/ON states, never generic SUCCESS/ERROR states.
	if ((state != DRIVER_STATUS_OFF) && (state != DRIVER_STATUS_ON))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a non-empty USART interrupt-request source mask
 * @param[in] sources USART interrupt-request source bitmask to validate
 * @returns @ref driver_status_t "IRQ-source validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `sources` contains only supported, non-empty source bits
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `sources` is empty or contains unsupported bits
 */
__STATIC_FORCEINLINE driver_status_t _USART_ValidateIRQSources(const usart_irq_source_t sources)
{
	//! Require at least one source and reject every bit outside the public CR1/CR3 vocabulary.
	if ((sources == USART_IRQ_SOURCE_NONE) || (USART_IRQ_SOURCE_IS_VALID(sources) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a non-empty USART event-flag mask
 * @param[in] events USART event-flag bitmask to validate
 * @returns @ref driver_status_t "IRQ-event validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `events` contains only supported, non-empty event bits
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `events` is empty or contains unsupported bits
 */
__STATIC_FORCEINLINE driver_status_t _USART_ValidateIRQEvents(const usart_event_flag_t events)
{
	//! Require at least one event and reject every bit outside the public SR vocabulary.
	if ((events == USART_IRQ_EVENT_NONE) || (USART_IRQ_EVENT_IS_VALID(events) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Decodes the RCC bus hosting one USART instance's peripheral clock
 * @param[in] USARTx USART peripheral instance
 * @param[out] pClockBus Destination for the decoded RCC bus selector
 * @returns @ref driver_status_t "Clock-bus decode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `pClockBus` was published
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `USARTx` or @p `pClockBus` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `USARTx` is unsupported
 * @note `USART1` hangs off APB2; `USART2`/`USART3` hang off APB1.
 */
__STATIC_FORCEINLINE driver_status_t _USART_DecodeClockBus(const USART_TypeDef* const USARTx, rcc_bus_t* const pClockBus)
{
	if (pClockBus == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_USART_ValidateInstance(USARTx));

	//! Match by peripheral base address because instance macros are raw memory-mapped pointers.
	switch ((uintptr_t) USARTx)
	{
		case USART1_BASE_ADDRESS:
		{
			*pClockBus = RCC_APB2_BUS;
			break;
		}
		case USART2_BASE_ADDRESS:
		{
			*pClockBus = RCC_APB1_BUS;
			break;
		}
		case USART3_BASE_ADDRESS:
		{
			*pClockBus = RCC_APB1_BUS;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Decodes the RCC peripheral clock-enable mask for one USART instance
 * @param[in] USARTx USART peripheral instance
 * @param[out] pClockEnableMask Destination for the decoded clock-enable mask
 * @returns @ref driver_status_t "Clock-enable-mask decode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `pClockEnableMask` was published
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `USARTx` or @p `pClockEnableMask` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `USARTx` is unsupported
 */
__STATIC_FORCEINLINE driver_status_t _USART_DecodeClockEnableMask(const USART_TypeDef* const USARTx, reg* const pClockEnableMask)
{
	if (pClockEnableMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_USART_ValidateInstance(USARTx));

	//! Match by peripheral base address because instance macros are raw memory-mapped pointers.
	switch ((uintptr_t) USARTx)
	{
		case USART1_BASE_ADDRESS:
		{
			*pClockEnableMask = RCC_APB2ENR_USART1EN;
			break;
		}
		case USART2_BASE_ADDRESS:
		{
			*pClockEnableMask = RCC_APB1ENR_USART2EN;
			break;
		}
		case USART3_BASE_ADDRESS:
		{
			*pClockEnableMask = RCC_APB1ENR_USART3EN;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Decodes the RCC peripheral reset mask for one USART instance
 * @param[in] USARTx USART peripheral instance
 * @param[out] pPeripheralResetMask Destination for the decoded reset mask
 * @returns @ref driver_status_t "Peripheral-reset-mask decode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `pPeripheralResetMask` was published
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `USARTx` or @p `pPeripheralResetMask` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `USARTx` is unsupported
 */
__STATIC_FORCEINLINE driver_status_t _USART_DecodePeripheralResetMask(const USART_TypeDef* const USARTx, reg* const pPeripheralResetMask)
{
	if (pPeripheralResetMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_USART_ValidateInstance(USARTx));

	//! Match by peripheral base address so deconfiguration cannot pulse an unrelated peripheral reset.
	switch ((uintptr_t) USARTx)
	{
		case USART1_BASE_ADDRESS:
		{
			*pPeripheralResetMask = RCC_APB2RSTR_USART1RST;
			break;
		}
		case USART2_BASE_ADDRESS:
		{
			*pPeripheralResetMask = RCC_APB1RSTR_USART2RST;
			break;
		}
		case USART3_BASE_ADDRESS:
		{
			*pPeripheralResetMask = RCC_APB1RSTR_USART3RST;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates that the USART peripheral's RCC clock gate is enabled
 * @param[in] USARTx USART peripheral instance
 * @returns @ref driver_status_t "Clock-gate validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The USART peripheral clock gate is enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `USARTx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `USARTx` is unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The USART peripheral clock gate is disabled
 * @note This helper never mutates the clock gate; enabling it remains an
 * exclusively application-owned action through RCC.
 */
__STATIC_FORCEINLINE driver_status_t _USART_ValidateClockEnabled(const USART_TypeDef* const USARTx)
{
	// Local Variables
	rcc_bus_t clockBus = RCC_APB1_BUS;
	reg clockEnableMask = 0x00000000UL;
	driver_status_t clockState = DRIVER_STATUS_ERROR;

	//! Decode the peripheral's RCC bus and clock-enable mask, then query the RCC directly for the gate state.
	ASSERT_DRIVER_STATUS(_USART_DecodeClockBus(USARTx, &clockBus));
	ASSERT_DRIVER_STATUS(_USART_DecodeClockEnableMask(USARTx, &clockEnableMask));

	//! Query RCC directly rather than caching state locally; the application exclusively owns this gate.
	clockState = RCC_GetPeripheralClockState(clockBus, clockEnableMask);
	if (clockState != DRIVER_STATUS_ERROR_INVALID_ARG)
	{
		if (clockState == DRIVER_STATUS_ON)
		{
			clockState = DRIVER_STATUS_SUCCESS;
		}
		else
		{
			clockState = DRIVER_STATUS_ERROR_STATE;
		}
	}

	return clockState;
}

// ==================================================================================================== //
//										Local Dirty-Write Helpers										//
// ==================================================================================================== //

/**
 * @brief Writes `USARTx_CR1` only when the staged image changed
 * @param[in] USARTx USART peripheral instance
 * @param[in] currentRegImage Current hardware `CR1` image
 * @param[in] stagedRegImage Staged `CR1` image
 * @returns @ref driver_status_t "CR1 dirty-write operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `CR1` write was skipped or performed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `USARTx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `USARTx` is unsupported
 */
__STATIC_FORCEINLINE driver_status_t _USART_WriteCR1IfChanged(USART_TypeDef* const USARTx, const reg currentRegImage, const reg stagedRegImage)
{
	ASSERT_DRIVER_STATUS(_USART_ValidateInstance(USARTx));
	return RegOps_WriteIfChanged(LL_USART_REG(USARTx, CR1), currentRegImage, stagedRegImage);
}

/**
 * @brief Writes `USARTx_CR2` only when the staged image changed
 * @param[in] USARTx USART peripheral instance
 * @param[in] currentRegImage Current hardware `CR2` image
 * @param[in] stagedRegImage Staged `CR2` image
 * @returns @ref driver_status_t "CR2 dirty-write operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `CR2` write was skipped or performed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `USARTx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `USARTx` is unsupported
 */
__STATIC_FORCEINLINE driver_status_t _USART_WriteCR2IfChanged(USART_TypeDef* const USARTx, const reg currentRegImage, const reg stagedRegImage)
{
	ASSERT_DRIVER_STATUS(_USART_ValidateInstance(USARTx));
	return RegOps_WriteIfChanged(LL_USART_REG(USARTx, CR2), currentRegImage, stagedRegImage);
}

/**
 * @brief Writes `USARTx_CR3` only when the staged image changed
 * @param[in] USARTx USART peripheral instance
 * @param[in] currentRegImage Current hardware `CR3` image
 * @param[in] stagedRegImage Staged `CR3` image
 * @returns @ref driver_status_t "CR3 dirty-write operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `CR3` write was skipped or performed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `USARTx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `USARTx` is unsupported
 */
__STATIC_FORCEINLINE driver_status_t _USART_WriteCR3IfChanged(USART_TypeDef* const USARTx, const reg currentRegImage, const reg stagedRegImage)
{
	ASSERT_DRIVER_STATUS(_USART_ValidateInstance(USARTx));
	return RegOps_WriteIfChanged(LL_USART_REG(USARTx, CR3), currentRegImage, stagedRegImage);
}

/**
 * @brief Writes `USARTx_BRR` only when the staged image changed
 * @param[in] USARTx USART peripheral instance
 * @param[in] currentRegImage Current hardware `BRR` image
 * @param[in] stagedRegImage Staged `BRR` image
 * @returns @ref driver_status_t "BRR dirty-write operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `BRR` write was skipped or performed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `USARTx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `USARTx` is unsupported
 */
__STATIC_FORCEINLINE driver_status_t _USART_WriteBRRIfChanged(USART_TypeDef* const USARTx, const reg currentRegImage, const reg stagedRegImage)
{
	ASSERT_DRIVER_STATUS(_USART_ValidateInstance(USARTx));
	return RegOps_WriteIfChanged(LL_USART_REG(USARTx, BRR), currentRegImage, stagedRegImage);
}

// ==================================================================================================== //
// USART Operation State APIs
// ==================================================================================================== //

driver_status_t USART_GetOperationState(const USART_TypeDef* const USARTx)
{
	//! Operation state is CR1.UE; the USART clock gate must be enabled before CR1 can be read.
	ASSERT_DRIVER_STATUS(_USART_ValidateClockEnabled(USARTx));
	return Codec_USART_ExtractOperationState(LL_USART_ReadCR1(USARTx));
}

driver_status_t USART_SetOperationState(USART_TypeDef* const USARTx, const driver_status_t operationState)
{
	// Local Variables
	reg currentCr1RegImage = 0x00000000UL;
	reg stagedCr1RegImage = 0x00000000UL;

	//! Operation state owns only CR1.UE; it refuses to touch CR1 while the USART clock gate is off.
	ASSERT_DRIVER_STATUS(_USART_ValidateClockEnabled(USARTx));
	ASSERT_DRIVER_STATUS(_USART_ValidateState(operationState));

	//! Snapshot CR1 once and stage only UE while preserving every unrelated field.
	currentCr1RegImage = LL_USART_ReadCR1(USARTx);
	stagedCr1RegImage = currentCr1RegImage;
	ASSERT_DRIVER_STATUS(Codec_USART_StageOperationState(&stagedCr1RegImage, operationState));

	//! Commit CR1 only when UE changed.
	return _USART_WriteCR1IfChanged(USARTx, currentCr1RegImage, stagedCr1RegImage);
}

// ==================================================================================================== //
// USART Configuration APIs
// ==================================================================================================== //

driver_status_t USART_DeConfig(USART_TypeDef* const USARTx)
{
	// Local Variable
	reg peripheralResetMask = 0x00000000UL;
	rcc_bus_t clockBus = RCC_APB1_BUS;

	//! Require explicit application clock ownership before resetting the USART register bank.
	ASSERT_DRIVER_STATUS(_USART_ValidateClockEnabled(USARTx));
	ASSERT_DRIVER_STATUS(_USART_DecodeClockBus(USARTx, &clockBus));
	ASSERT_DRIVER_STATUS(_USART_DecodePeripheralResetMask(USARTx, &peripheralResetMask));

	//! Reset only USART-owned peripheral state; RCC clock gating and NVIC delivery remain unchanged.
	return RCC_PulsePeripheralReset(clockBus, peripheralResetMask);
}

driver_status_t USART_Config(USART_TypeDef* const USARTx, const usart_config_t* const pConfig)
{
	// Local Variables
	rcc_bus_t clockBus = RCC_APB1_BUS;
	frequency_t busFrequency = FREQ_ZERO;
	reg currentCr1RegImage = 0x00000000UL;
	reg targetCr1RegImage = 0x00000000UL;
	reg currentCr2RegImage = 0x00000000UL;
	reg targetCr2RegImage = 0x00000000UL;
	reg currentCr3RegImage = 0x00000000UL;
	reg targetCr3RegImage = 0x00000000UL;
	reg currentBrrRegImage = 0x00000000UL;
	reg targetBrrRegImage = 0x00000000UL;

	//! Validate the complete root request and require the application-owned clock gate.
	if (pConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_USART_ValidateClockEnabled(USARTx));

	//! Snapshot every register the root transaction can touch, exactly once each.
	currentCr1RegImage = LL_USART_ReadCR1(USARTx);
	targetCr1RegImage = currentCr1RegImage;
	currentCr2RegImage = LL_USART_ReadCR2(USARTx);
	targetCr2RegImage = currentCr2RegImage;
	currentCr3RegImage = LL_USART_ReadCR3(USARTx);
	targetCr3RegImage = currentCr3RegImage;
	currentBrrRegImage = LL_USART_ReadBRR(USARTx);
	targetBrrRegImage = currentBrrRegImage;

	//! Stage the hardware-enable and frame-format domains into their owning local images.
	ASSERT_DRIVER_STATUS(Codec_USART_StageHardwareEnableState(&targetCr1RegImage, &targetCr3RegImage, pConfig->hardware));
	ASSERT_DRIVER_STATUS(Codec_USART_StageDataConfig(&targetCr1RegImage, &targetCr2RegImage, &(pConfig->frameFormat)));

	//! Resolve the live bus frequency this instance's BRR divider must be computed against.
	ASSERT_DRIVER_STATUS(_USART_DecodeClockBus(USARTx, &clockBus));
	busFrequency = RCC_GetBusFrequency(clockBus);
	if (busFrequency == FREQ_ZERO)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	ASSERT_DRIVER_STATUS(Codec_USART_StageBaudRate(&targetBrrRegImage, busFrequency, pConfig->baudRate));

	//! Dirty-write each changed register exactly once; unrelated fields outside each domain are preserved.
	ASSERT_DRIVER_STATUS(_USART_WriteCR1IfChanged(USARTx, currentCr1RegImage, targetCr1RegImage));
	ASSERT_DRIVER_STATUS(_USART_WriteCR2IfChanged(USARTx, currentCr2RegImage, targetCr2RegImage));
	ASSERT_DRIVER_STATUS(_USART_WriteCR3IfChanged(USARTx, currentCr3RegImage, targetCr3RegImage));
	ASSERT_DRIVER_STATUS(_USART_WriteBRRIfChanged(USARTx, currentBrrRegImage, targetBrrRegImage));

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
// USART IRQ Source APIs
// ==================================================================================================== //

driver_status_t USART_GetIRQSources(const USART_TypeDef* const USARTx, usart_irq_source_t* const pSources)
{
	//! Validate destination storage before reading the peripheral interrupt-enable registers.
	if (pSources == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	//! Sources span CR1 and CR3; the clock gate must be enabled before either can be read.
	ASSERT_DRIVER_STATUS(_USART_ValidateClockEnabled(USARTx));
	return Codec_USART_ExtractIRQSources(LL_USART_ReadCR1(USARTx), LL_USART_ReadCR3(USARTx), pSources);
}

driver_status_t USART_SetIRQSources
(
	USART_TypeDef* const		USARTx,
	const usart_irq_source_t	sources,
	const driver_status_t		sourceState
)
{
	// Local Variables
	reg currentCr1RegImage = 0x00000000UL;
	reg targetCr1RegImage = 0x00000000UL;
	reg currentCr3RegImage = 0x00000000UL;
	reg targetCr3RegImage = 0x00000000UL;

	//! Validate the instance, source mask, and state before reading or staging CR1/CR3.
	ASSERT_DRIVER_STATUS(_USART_ValidateInstance(USARTx));
	ASSERT_DRIVER_STATUS(_USART_ValidateIRQSources(sources));
	ASSERT_DRIVER_STATUS(_USART_ValidateState(sourceState));
	ASSERT_DRIVER_STATUS(_USART_ValidateClockEnabled(USARTx));

	//! Snapshot both registers once and stage only the selected sources.
	currentCr1RegImage = LL_USART_ReadCR1(USARTx);
	targetCr1RegImage = currentCr1RegImage;
	currentCr3RegImage = LL_USART_ReadCR3(USARTx);
	targetCr3RegImage = currentCr3RegImage;
	ASSERT_DRIVER_STATUS(Codec_USART_StageIRQSources(&targetCr1RegImage, &targetCr3RegImage, sources, sourceState));

	//! Commit each register only when the selected sources actually changed its image.
	ASSERT_DRIVER_STATUS(_USART_WriteCR1IfChanged(USARTx, currentCr1RegImage, targetCr1RegImage));
	ASSERT_DRIVER_STATUS(_USART_WriteCR3IfChanged(USARTx, currentCr3RegImage, targetCr3RegImage));

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
// USART IRQ Event APIs
// ==================================================================================================== //

driver_status_t USART_GetIRQEvents(const USART_TypeDef* const USARTx, usart_event_flag_t* const pEvents)
{
	//! Validate destination storage before reading the USART status register.
	if (pEvents == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	//! Decode SR flags independently from CR1/CR3 source state and NVIC delivery state.
	ASSERT_DRIVER_STATUS(_USART_ValidateClockEnabled(USARTx));
	return Codec_USART_ExtractIRQEvents(LL_USART_ReadSR(USARTx), pEvents);
}

driver_status_t USART_AckIRQEvents(USART_TypeDef* const USARTx, const usart_event_flag_t events)
{
	// Local Variables
	reg srRegImage = 0x00000000UL;
	const usart_event_flag_t readSequenceEvents =
	(
		USART_IRQ_EVENT_PE | USART_IRQ_EVENT_FE | USART_IRQ_EVENT_NE |
		USART_IRQ_EVENT_ORE | USART_IRQ_EVENT_IDLE | USART_IRQ_EVENT_RXNE
	);

	//! Validate the instance, event mask, and clock gate before touching SR/DR.
	ASSERT_DRIVER_STATUS(_USART_ValidateInstance(USARTx));
	ASSERT_DRIVER_STATUS(_USART_ValidateIRQEvents(events));
	ASSERT_DRIVER_STATUS(_USART_ValidateClockEnabled(USARTx));

	//! Read SR once; for PE/FE/NE/ORE/IDLE/RXNE this read is the first half of the hardware clear sequence.
	srRegImage = LL_USART_ReadSR(USARTx);
	ASSERT_DRIVER_STATUS(Codec_USART_StageIRQEventsClear(&srRegImage, events));
	//! Unconditional write: SR is write-0-to-clear for TC/CTS, so re-writing an unchanged image is harmless.
	LL_USART_WriteSR(USARTx, srRegImage);

	//! Complete the read-SR-then-read-DR sequence for the remaining flags; this discards the buffered DR value.
	if ((events & readSequenceEvents) != 0x0000U)
	{
		(void) LL_USART_ReadDR(USARTx);
	}

	return DRIVER_STATUS_SUCCESS;
}
