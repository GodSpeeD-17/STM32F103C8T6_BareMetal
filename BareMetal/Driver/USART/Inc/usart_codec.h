/**
 * @file	usart_codec.h
 * @author	Shrey Shah
 * @brief	USART Selector Codec Interface
 * @version	v1.0
 * @date	23-08-2026
 *
 * @details
 * This header defines the codec layer between USART LL and the public
 * USART driver. Codec APIs encode driver-facing selectors into raw STM32F1
 * USART fields, decode raw fields back into driver-facing selectors, and
 * return updated caller-owned register images.
 *
 * Codec APIs do not read or write peripheral hardware, do not enable clocks,
 * do not touch NVIC, and do not decide public driver orchestration. The
 * `SR` read-`SR`-then-read-`DR` acknowledge sequence for `PE/FE/NE/ORE/
 * IDLE/RXNE` requires a live `DR` register read, so that sequencing is
 * Driver-owned; this layer only stages the write-0-to-clear subset (`TC`/
 * `CTS`) and decodes `SR` into the public event-flag bitmask.
 */

#ifndef USART_CODEC_H_
#define USART_CODEC_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "usart_config.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup USART_03_Driver
 * @{
 */

/**
 * @brief USART Codec Translation, Staging, and Extraction APIs
 * @defgroup USART_03_Driver_03_Codec USART Codec Translation, Staging, and Extraction APIs
 * @ingroup USART_03_Driver
 * @details
 * These APIs own selector translation and staged register-image mutation for
 * the USART driver. They assume the driver layer owns public validation,
 * hardware register reads/writes, sequencing, clock enable/reset, and
 * interrupt/NVIC policy.
 *
 * @note Stage APIs mutate caller-owned register images in place. The image
 * pointer must reference a local driver-owned @ref reg image, not a live
 * peripheral register address.
 * @{
 */

// ==================================================================================================== //
// USART Hardware Enable Codecs
// ==================================================================================================== //

/**
 * @brief Extracts the USART TX/RX/RTS/CTS hardware-enable bitmask from `CR1`/`CR3` images
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[in] cr3RegImage Caller-owned `CR3` image
 * @param[out] pHardware Destination for the decoded hardware-enable bitmask
 * Expected values:
 * - Any OR-combination of @ref `USART_HARDWARE_ENABLE_TX`, @ref `USART_HARDWARE_ENABLE_RX`,
 *   @ref `USART_HARDWARE_ENABLE_RTS`, @ref `USART_HARDWARE_ENABLE_CTS`
 * @returns @ref driver_status_t "Extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Hardware-enable bitmask was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pHardware is `NULL`
 */
driver_status_t Codec_USART_ExtractHardwareEnableState
(
	const reg					cr1RegImage,
	const reg					cr3RegImage,
	usart_hardware_enable_t* const	pHardware
);

/**
 * @brief Stages the USART TX/RX/RTS/CTS hardware-enable bitmask into `CR1`/`CR3` images
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in,out] pCr3RegImage Caller-owned `CR3` image to update in place
 * @param[in] hardware Hardware-enable bitmask to stage
 * Accepted values:
 * - Any OR-combination of @ref `USART_HARDWARE_ENABLE_TX`, @ref `USART_HARDWARE_ENABLE_RX`,
 *   @ref `USART_HARDWARE_ENABLE_RTS`, @ref `USART_HARDWARE_ENABLE_CTS`
 * @returns @ref driver_status_t "Staging status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Hardware-enable bitmask was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage or @p pCr3RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p hardware selects an unsupported bit
 */
driver_status_t Codec_USART_StageHardwareEnableState
(
	reg* const					pCr1RegImage,
	reg* const					pCr3RegImage,
	const usart_hardware_enable_t	hardware
);

// ==================================================================================================== //
// USART Data-Config Codecs
// ==================================================================================================== //

/**
 * @brief Extracts the USART data-bit/parity/stop-bit frame format from `CR1`/`CR2` images
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[in] cr2RegImage Caller-owned `CR2` image
 * @param[out] pFrameFormat Destination for the decoded frame-format configuration
 * Expected member values:
 * - @ref usart_frame_format_t::dataBits : @ref `USART_DATA_BITS_8` or @ref `USART_DATA_BITS_9`
 * - @ref usart_frame_format_t::parity : @ref `USART_PARITY_NONE`, @ref `USART_PARITY_EVEN`, or @ref `USART_PARITY_ODD`
 * - @ref usart_frame_format_t::stopBits : @ref `USART_STOP_BIT_1`, @ref `USART_STOP_BIT_0_5`,
 *   @ref `USART_STOP_BIT_2`, or @ref `USART_STOP_BIT_1_5`
 * @returns @ref driver_status_t "Extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Frame-format configuration was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFrameFormat is `NULL`
 */
driver_status_t Codec_USART_ExtractDataConfig
(
	const reg					cr1RegImage,
	const reg					cr2RegImage,
	usart_frame_format_t* const	pFrameFormat
);

/**
 * @brief Stages the USART data-bit/parity/stop-bit frame format into `CR1`/`CR2` images
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in,out] pCr2RegImage Caller-owned `CR2` image to update in place
 * @param[in] pFrameFormat Frame-format configuration to stage
 * Accepted member values:
 * - @ref usart_frame_format_t::dataBits : Any value accepted by @ref `USART_DATA_BITS_IS_VALID`
 * - @ref usart_frame_format_t::parity : Any value accepted by @ref `USART_PARITY_IS_VALID`
 * - @ref usart_frame_format_t::stopBits : Any value accepted by @ref `USART_STOP_BITS_IS_VALID`
 * @returns @ref driver_status_t "Staging status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Frame-format configuration was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage, @p pCr2RegImage, or @p pFrameFormat is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more frame-format fields cannot be encoded
 */
driver_status_t Codec_USART_StageDataConfig
(
	reg* const						pCr1RegImage,
	reg* const						pCr2RegImage,
	const usart_frame_format_t* const	pFrameFormat
);

// ==================================================================================================== //
// USART Operation-State Codecs
// ==================================================================================================== //

/**
 * @brief Extracts the USART peripheral enable state from a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @returns @ref driver_status_t "Decoded operation state"
 * @retval - @ref `DRIVER_STATUS_OFF`: `CR1.UE` is clear
 * @retval - @ref `DRIVER_STATUS_ON`: `CR1.UE` is set
 */
driver_status_t Codec_USART_ExtractOperationState(const reg cr1RegImage);

/**
 * @brief Stages the USART peripheral enable state into a `CR1` image
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in] operationState Requested operation state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF` : Clear `CR1.UE`
 * - @ref `DRIVER_STATUS_ON` : Set `CR1.UE`
 * @returns @ref driver_status_t "Staging status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Operation state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p operationState is not an accepted state
 */
driver_status_t Codec_USART_StageOperationState
(
	reg* const				pCr1RegImage,
	const driver_status_t	operationState
);

// ==================================================================================================== //
// USART Baud Rate Codecs
// ==================================================================================================== //

/**
 * @brief Extracts the closest supported baud-rate preset from a `BRR` image
 * @param[in] brrRegImage Caller-owned `BRR` image
 * @param[in] busFrequency Live USART kernel bus frequency, in hertz
 * @param[out] pBaudRate Destination for the resolved baud-rate preset
 * Expected values:
 * - Any value in @ref `USART_BAUD_RATE_9600` through @ref `USART_BAUD_RATE_921600`
 * @returns @ref driver_status_t "Extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Baud-rate preset was resolved
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pBaudRate is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p busFrequency is zero or @p brrRegImage divides to zero
 * @note The resolved preset is the closest supported rate to the raw
 * divider; `BRR` quantizes to 1/16th-bit-period steps, so this is not
 * guaranteed to round-trip exactly against a prior @ref Codec_USART_StageBaudRate call.
 * @see RM0008 Section 27.3.4 Fractional baud rate generation
 */
driver_status_t Codec_USART_ExtractBaudRate
(
	const reg					brrRegImage,
	const frequency_t			busFrequency,
	usart_baud_rate_t* const	pBaudRate
);

/**
 * @brief Stages the `BRR` mantissa/fraction divider for a baud-rate preset
 * @param[in,out] pBrrRegImage Caller-owned `BRR` image to update in place
 * @param[in] busFrequency Live USART kernel bus frequency, in hertz
 * @param[in] baudRate Baud-rate preset to stage
 * Accepted values:
 * - Any value in @ref `USART_BAUD_RATE_9600` through @ref `USART_BAUD_RATE_921600`
 * @returns @ref driver_status_t "Staging status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `BRR` divider was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pBrrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p baudRate is not a supported preset, or @p busFrequency is zero
 * @see RM0008 Section 27.3.4 Fractional baud rate generation
 */
driver_status_t Codec_USART_StageBaudRate
(
	reg* const				pBrrRegImage,
	const frequency_t		busFrequency,
	const usart_baud_rate_t	baudRate
);

// ==================================================================================================== //
// USART IRQ Source Codecs
// ==================================================================================================== //

/**
 * @brief Extracts the enabled USART interrupt-request sources from `CR1`/`CR3` images
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[in] cr3RegImage Caller-owned `CR3` image
 * @param[out] pSources Destination for the decoded interrupt-request source bitmask
 * Expected values:
 * - Any OR-combination of @ref `USART_IRQ_SOURCE_IDLE` through @ref `USART_IRQ_SOURCE_ERROR`
 * @returns @ref driver_status_t "Extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Interrupt-request source bitmask was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSources is `NULL`
 */
driver_status_t Codec_USART_ExtractIRQSources
(
	const reg					cr1RegImage,
	const reg					cr3RegImage,
	usart_irq_source_t* const	pSources
);

/**
 * @brief Stages the USART interrupt-request source enable state into `CR1`/`CR3` images
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in,out] pCr3RegImage Caller-owned `CR3` image to update in place
 * @param[in] sources Interrupt-request source bitmask to stage
 * Accepted values:
 * - Any OR-combination of @ref `USART_IRQ_SOURCE_IDLE` through @ref `USART_IRQ_SOURCE_ERROR`
 * @param[in] sourceState Requested state for every selected source
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF` : Clear every selected source's enable bit
 * - @ref `DRIVER_STATUS_ON` : Set every selected source's enable bit
 * @returns @ref driver_status_t "Staging status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Interrupt-request sources were staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage or @p pCr3RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p sources selects an unsupported bit, or @p sourceState is not an accepted state
 */
driver_status_t Codec_USART_StageIRQSources
(
	reg* const					pCr1RegImage,
	reg* const					pCr3RegImage,
	const usart_irq_source_t	sources,
	const driver_status_t		sourceState
);

// ==================================================================================================== //
// USART IRQ Event Codecs
// ==================================================================================================== //

/**
 * @brief Extracts the pending USART event-flag bitmask from an `SR` image
 * @param[in] srRegImage Caller-owned `SR` image
 * @param[out] pEvents Destination for the decoded event-flag bitmask
 * Expected values:
 * - Any OR-combination of @ref `USART_IRQ_EVENT_PE` through @ref `USART_IRQ_EVENT_CTS`
 * @returns @ref driver_status_t "Extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Event-flag bitmask was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pEvents is `NULL`
 * @note `USARTx_SR`'s status bits are positioned identically to their
 * matching @ref usart_event_flag_t bits, so this is a direct masked copy.
 */
driver_status_t Codec_USART_ExtractIRQEvents
(
	const reg				srRegImage,
	usart_event_flag_t* const	pEvents
);

/**
 * @brief Stages a write-0-to-clear image for the write-0-to-clear USART event flags
 * @param[in,out] pSrRegImage Caller-owned `SR` image to update in place
 * @param[in] events Event-flag bitmask to acknowledge
 * Accepted values:
 * - Any OR-combination of @ref `USART_IRQ_EVENT_PE` through @ref `USART_IRQ_EVENT_CTS`
 * @returns @ref driver_status_t "Staging status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Write-0-to-clear image was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p events selects an unsupported bit
 * @note This API only clears `TC`/`CTS`; every other flag in @p events is
 * ignored here because `PE/FE/NE/ORE/IDLE/RXNE` require a live read-`SR`-
 * then-read-`DR` hardware sequence, and `TXE` is never acknowledged. The
 * driver layer owns performing that sequence.
 */
driver_status_t Codec_USART_StageIRQEventsClear
(
	reg* const					pSrRegImage,
	const usart_event_flag_t	events
);

/** @} */ // USART_03_Driver_03_Codec

/** @} */ // USART_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USART_CODEC_H_ */
