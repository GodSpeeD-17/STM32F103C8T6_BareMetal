/**
 * @file	timer_codec.h
 * @author	Shrey Shah
 * @brief	Timer Selector Codec Interface
 * @version	v1.0
 * @date	07-06-2026
 *
 * @details
 * This header defines the Timer codec layer between Timer LL and the public
 * Timer driver. Codec APIs encode driver-facing selectors into raw STM32F1
 * Timer fields, decode raw fields back into driver-facing selectors, and
 * return updated caller-owned register images.
 *
 * Codec APIs do not read or write peripheral hardware, do not enable clocks,
 * do not touch NVIC, and do not decide public driver orchestration.
 */

#ifndef TIMER_CODEC_H_
#define TIMER_CODEC_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "timer_defines.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup TIM_03_Driver
 * @{
 */

/**
 * @brief Timer Codec Translation, Staging, and Extraction APIs
 * @defgroup TIM_03_Driver_03_Codec Timer Codec Translation, Staging, and Extraction APIs
 * @ingroup TIM_03_Driver
 * @details
 * These APIs own selector translation and staged register-image mutation for
 * the Timer driver. They assume the driver layer owns public validation,
 * hardware register reads/writes, sequencing, clock enable/reset, batching,
 * dirty-register writes, and interrupt/NVIC policy.
 * @{
 */

// ==================================================================================================== //
//										Timer CR1 Counter Codecs										//
// ==================================================================================================== //

/**
 * @brief Extracts Timer counter configuration selectors from a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[out] pDirection Optional destination for decoded direction selector
 * @param[out] pMode Optional destination for decoded count-mode selector
 * @param[out] pOnePulse Optional destination for decoded one-pulse selector
 * @param[out] pAutoReloadPreload Optional destination for decoded auto-reload preload selector
 * @param[out] pUpdateSource Optional destination for decoded update-source selector
 * @param[out] pClockDivision Optional destination for decoded clock-division selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter selectors were extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: All output pointers are `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A raw `CR1` field is not decodable by the current public Timer vocabulary
 * @note Codec reads only @p cr1RegImage and writes only non-`NULL` output pointers.
 */
driver_status_t Codec_TIM_ExtractCounterConfig
(
	const reg							cr1RegImage,
	timer_direction_t* const				pDirection,
	timer_count_mode_t* const				pMode,
	timer_opm_t* const					pOnePulse,
	timer_arpe_t* const					pAutoReloadPreload,
	timer_update_source_t* const			pUpdateSource,
	timer_clock_division_t* const			pClockDivision
);

/**
 * @brief Stages Timer counter configuration selectors into a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image before replacement
 * @param[in] direction Timer direction selector
 * @param[in] mode Timer count-mode selector
 * @param[in] onePulse Timer one-pulse selector
 * @param[in] autoReloadPreload Timer auto-reload preload selector
 * @param[in] updateSource Timer update-source selector
 * @param[in] clockDivision Timer clock-division selector
 * @param[out] pCr1RegImage Destination for the updated `CR1` image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `CR1` image was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more selectors cannot be encoded
 * @note This API preserves `CEN` and `UDIS`; use the dedicated state codecs for those fields.
 */
driver_status_t Codec_TIM_StageCounterConfig
(
	const reg							cr1RegImage,
	const timer_direction_t				direction,
	const timer_count_mode_t				mode,
	const timer_opm_t						onePulse,
	const timer_arpe_t					autoReloadPreload,
	const timer_update_source_t			updateSource,
	const timer_clock_division_t			clockDivision,
	reg* const							pCr1RegImage
);

/**
 * @brief Extracts the Timer counter enable state from a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[out] pCounterState Destination for the decoded counter state
 * Updated Values:
 * - @ref `DRIVER_STATUS_OFF`: Counter is disabled
 * - @ref `DRIVER_STATUS_ON`: Counter is enabled
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter state was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounterState is `NULL`
 */
driver_status_t Codec_TIM_ExtractCounterEnableState
(
	const reg							cr1RegImage,
	driver_status_t* const				pCounterState
);

/**
 * @brief Stages the Timer counter enable state into a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image before replacement
 * @param[in] counterState Requested counter state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Clear `CEN`
 * - @ref `DRIVER_STATUS_ON`: Set `CEN`
 * @param[out] pCr1RegImage Destination for the updated `CR1` image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter enable state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p counterState is not an accepted state
 */
driver_status_t Codec_TIM_StageCounterEnableState
(
	const reg							cr1RegImage,
	const driver_status_t				counterState,
	reg* const							pCr1RegImage
);

/**
 * @brief Extracts the Timer update-event enable state from a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[out] pUpdateEventState Destination for the decoded update-event state
 * Updated Values:
 * - @ref `DRIVER_STATUS_OFF`: Update events are disabled through `UDIS`
 * - @ref `DRIVER_STATUS_ON`: Update events are enabled
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update-event state was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pUpdateEventState is `NULL`
 * @note Raw `UDIS` has inverse polarity: `UDIS == 1U` means update events are disabled.
 */
driver_status_t Codec_TIM_ExtractUpdateEventState
(
	const reg							cr1RegImage,
	driver_status_t* const				pUpdateEventState
);

/**
 * @brief Stages the Timer update-event enable state into a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image before replacement
 * @param[in] updateEventState Requested update-event state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Set `UDIS`
 * - @ref `DRIVER_STATUS_ON`: Clear `UDIS`
 * @param[out] pCr1RegImage Destination for the updated `CR1` image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update-event state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p updateEventState is not an accepted state
 * @note Raw `UDIS` has inverse polarity: `UDIS == 1U` means update events are disabled.
 */
driver_status_t Codec_TIM_StageUpdateEventState
(
	const reg							cr1RegImage,
	const driver_status_t				updateEventState,
	reg* const							pCr1RegImage
);

// ==================================================================================================== //
//										Timer Trigger Codecs											//
// ==================================================================================================== //

/**
 * @brief Extracts the Timer master-mode selector from a `CR2` image
 * @param[in] cr2RegImage Caller-owned `CR2` image
 * @param[out] pMasterMode Destination for decoded master-mode selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Master-mode selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pMasterMode is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Raw `MMS` field is not decodable
 */
driver_status_t Codec_TIM_ExtractMasterMode
(
	const reg							cr2RegImage,
	timer_master_mode_t* const			pMasterMode
);

/**
 * @brief Stages the Timer master-mode selector into a `CR2` image
 * @param[in] cr2RegImage Caller-owned `CR2` image before replacement
 * @param[in] masterMode Timer master-mode selector
 * @param[out] pCr2RegImage Destination for the updated `CR2` image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Master-mode selector was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr2RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p masterMode cannot be encoded
 */
driver_status_t Codec_TIM_StageMasterMode
(
	const reg							cr2RegImage,
	const timer_master_mode_t				masterMode,
	reg* const							pCr2RegImage
);

/**
 * @brief Extracts the Timer slave-mode selector from an `SMCR` image
 * @param[in] smcrRegImage Caller-owned `SMCR` image
 * @param[out] pSlaveMode Destination for decoded slave-mode selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Slave-mode selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSlaveMode is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Raw `SMS` field is not decodable
 */
driver_status_t Codec_TIM_ExtractSlaveMode
(
	const reg							smcrRegImage,
	timer_slave_mode_t* const				pSlaveMode
);

/**
 * @brief Stages the Timer slave-mode selector into an `SMCR` image
 * @param[in] smcrRegImage Caller-owned `SMCR` image before replacement
 * @param[in] slaveMode Timer slave-mode selector
 * @param[out] pSmcrRegImage Destination for the updated `SMCR` image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Slave-mode selector was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSmcrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p slaveMode cannot be encoded
 */
driver_status_t Codec_TIM_StageSlaveMode
(
	const reg							smcrRegImage,
	const timer_slave_mode_t				slaveMode,
	reg* const							pSmcrRegImage
);

// ==================================================================================================== //
//										Timer CCMR Channel Codecs										//
// ==================================================================================================== //

/**
 * @brief Extracts one channel capture/compare selection from a `CCMR1` or `CCMR2` image
 * @param[in] ccmrRegImage Caller-owned `CCMR1` or `CCMR2` image
 * @param[in] channel Timer single-channel mask
 * @param[out] pCaptureCompareSelection Destination for decoded `CCxS` selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Capture/compare selection was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCaptureCompareSelection is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel or raw `CCxS` is not decodable
 * @note Caller must pass the `CCMR1` image for channels 1/2 and the `CCMR2` image for channels 3/4.
 */
driver_status_t Codec_TIM_ExtractChannelSelection
(
	const reg							ccmrRegImage,
	const timer_channel_t					channel,
	timer_channel_ccs_t* const			pCaptureCompareSelection
);

/**
 * @brief Stages one channel capture/compare selection into a `CCMR1` or `CCMR2` image
 * @param[in] ccmrRegImage Caller-owned `CCMR1` or `CCMR2` image before replacement
 * @param[in] channel Timer single-channel mask
 * @param[in] captureCompareSelection Timer `CCxS` selector
 * @param[out] pCcmrRegImage Destination for the updated `CCMR1` or `CCMR2` image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Capture/compare selection was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCcmrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel or @p captureCompareSelection cannot be encoded
 * @note Caller must pass the `CCMR1` image for channels 1/2 and the `CCMR2` image for channels 3/4.
 */
driver_status_t Codec_TIM_StageChannelSelection
(
	const reg							ccmrRegImage,
	const timer_channel_t					channel,
	const timer_channel_ccs_t				captureCompareSelection,
	reg* const							pCcmrRegImage
);

/**
 * @brief Extracts one output-compare channel configuration from a `CCMR1` or `CCMR2` image
 * @param[in] ccmrRegImage Caller-owned `CCMR1` or `CCMR2` image
 * @param[in] channel Timer single-channel mask
 * @param[out] pOutputCompareClear Optional destination for decoded output-compare clear selector
 * @param[out] pOutputCompareMode Optional destination for decoded output-compare mode selector
 * @param[out] pOutputComparePreload Optional destination for decoded output-compare preload selector
 * @param[out] pOutputCompareFast Optional destination for decoded output-compare fast selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Output-compare configuration was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: All output pointers are `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel, `CCxS` is not output mode, or a raw output-compare field is not decodable
 * @note This API decodes only output-compare interpretation. Input-capture
 * interpretation requires a separate codec surface.
 */
driver_status_t Codec_TIM_ExtractOutputCompareConfig
(
	const reg							ccmrRegImage,
	const timer_channel_t					channel,
	timer_channel_oc_clear_t* const		pOutputCompareClear,
	timer_channel_mode_t* const			pOutputCompareMode,
	timer_channel_oc_preload_t* const		pOutputComparePreload,
	timer_channel_oc_fast_t* const		pOutputCompareFast
);

/**
 * @brief Stages one output-compare channel configuration into a `CCMR1` or `CCMR2` image
 * @param[in] ccmrRegImage Caller-owned `CCMR1` or `CCMR2` image before replacement
 * @param[in] channel Timer single-channel mask
 * @param[in] outputCompareClear Timer output-compare clear selector
 * @param[in] outputCompareMode Timer output-compare mode selector
 * @param[in] outputComparePreload Timer output-compare preload selector
 * @param[in] outputCompareFast Timer output-compare fast selector
 * @param[out] pCcmrRegImage Destination for the updated `CCMR1` or `CCMR2` image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Output-compare configuration was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCcmrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel or one or more selectors cannot be encoded
 * @note This API also stages `CCxS` to @ref `TIMx_CHANNEL_CCS_OUTPUT`.
 */
driver_status_t Codec_TIM_StageOutputCompareConfig
(
	const reg							ccmrRegImage,
	const timer_channel_t					channel,
	const timer_channel_oc_clear_t		outputCompareClear,
	const timer_channel_mode_t			outputCompareMode,
	const timer_channel_oc_preload_t		outputComparePreload,
	const timer_channel_oc_fast_t			outputCompareFast,
	reg* const							pCcmrRegImage
);

// ==================================================================================================== //
//										Timer CCER Channel Codecs										//
// ==================================================================================================== //

/**
 * @brief Extracts one channel enable state from a `CCER` image
 * @param[in] ccerRegImage Caller-owned `CCER` image
 * @param[in] channel Timer single-channel mask
 * @param[out] pChannelState Destination for decoded channel enable state
 * Updated Values:
 * - @ref `DRIVER_STATUS_OFF`: Channel output is disabled
 * - @ref `DRIVER_STATUS_ON`: Channel output is enabled
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Channel enable state was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pChannelState is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel
 */
driver_status_t Codec_TIM_ExtractChannelEnableState
(
	const reg							ccerRegImage,
	const timer_channel_t					channel,
	driver_status_t* const				pChannelState
);

/**
 * @brief Stages one channel enable state into a `CCER` image
 * @param[in] ccerRegImage Caller-owned `CCER` image before replacement
 * @param[in] channel Timer single-channel mask
 * @param[in] channelState Requested channel enable state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Clear `CCxE`
 * - @ref `DRIVER_STATUS_ON`: Set `CCxE`
 * @param[out] pCcerRegImage Destination for the updated `CCER` image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Channel enable state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCcerRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel or @p channelState is not an accepted state
 */
driver_status_t Codec_TIM_StageChannelEnableState
(
	const reg							ccerRegImage,
	const timer_channel_t					channel,
	const driver_status_t				channelState,
	reg* const							pCcerRegImage
);

/**
 * @brief Extracts one channel polarity selector from a `CCER` image
 * @param[in] ccerRegImage Caller-owned `CCER` image
 * @param[in] channel Timer single-channel mask
 * @param[out] pPolarity Destination for decoded channel polarity selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Channel polarity selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPolarity is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel or raw polarity field is not decodable
 */
driver_status_t Codec_TIM_ExtractChannelPolarity
(
	const reg							ccerRegImage,
	const timer_channel_t					channel,
	timer_channel_polarity_t* const		pPolarity
);

/**
 * @brief Stages one channel polarity selector into a `CCER` image
 * @param[in] ccerRegImage Caller-owned `CCER` image before replacement
 * @param[in] channel Timer single-channel mask
 * @param[in] polarity Timer channel polarity selector
 * @param[out] pCcerRegImage Destination for the updated `CCER` image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Channel polarity selector was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCcerRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel or @p polarity cannot be encoded
 */
driver_status_t Codec_TIM_StageChannelPolarity
(
	const reg							ccerRegImage,
	const timer_channel_t					channel,
	const timer_channel_polarity_t		polarity,
	reg* const							pCcerRegImage
);

// ==================================================================================================== //
//										Timer DIER Request Codecs										//
// ==================================================================================================== //

/**
 * @brief Extracts enabled Timer IRQ source selectors from a `DIER` image
 * @param[in] dierRegImage Caller-owned `DIER` image
 * @param[out] pIrqMask Destination for enabled IRQ source mask
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: IRQ enable mask was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pIrqMask is `NULL`
 */
driver_status_t Codec_TIM_ExtractIRQEnableMask
(
	const reg							dierRegImage,
	timer_irq_t* const					pIrqMask
);

/**
 * @brief Stages IRQ enable or disable state for selected IRQ sources into a `DIER` image
 * @param[in] dierRegImage Caller-owned `DIER` image before replacement
 * @param[in] irqMask Timer IRQ source mask to modify
 * @param[in] irqEnable Requested IRQ enable selector
 * Accepted values:
 * - @ref `TIMx_IRQ_DISABLE`: Disable selected IRQ sources
 * - @ref `TIMx_IRQ_ENABLE`: Enable selected IRQ sources
 * @param[out] pDierRegImage Destination for the updated `DIER` image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: IRQ enable state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDierRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p irqMask or @p irqEnable is invalid
 * @note NVIC enable/disable policy belongs to the Timer driver layer.
 */
driver_status_t Codec_TIM_StageIRQEnableMask
(
	const reg							dierRegImage,
	const timer_irq_t						irqMask,
	const timer_irq_enable_t				irqEnable,
	reg* const							pDierRegImage
);

/**
 * @brief Extracts enabled Timer DMA source selectors from a `DIER` image
 * @param[in] dierRegImage Caller-owned `DIER` image
 * @param[out] pDmaMask Destination for enabled DMA source mask
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: DMA enable mask was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDmaMask is `NULL`
 */
driver_status_t Codec_TIM_ExtractDMAEnableMask
(
	const reg							dierRegImage,
	timer_dma_t* const					pDmaMask
);

/**
 * @brief Stages DMA enable or disable state for selected DMA sources into a `DIER` image
 * @param[in] dierRegImage Caller-owned `DIER` image before replacement
 * @param[in] dmaMask Timer DMA source mask to modify
 * @param[in] dmaState Requested DMA enable state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable selected DMA sources
 * - @ref `DRIVER_STATUS_ON`: Enable selected DMA sources
 * @param[out] pDierRegImage Destination for the updated `DIER` image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: DMA enable state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDierRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p dmaMask or @p dmaState is invalid
 */
driver_status_t Codec_TIM_StageDMAEnableMask
(
	const reg							dierRegImage,
	const timer_dma_t						dmaMask,
	const driver_status_t				dmaState,
	reg* const							pDierRegImage
);

// ==================================================================================================== //
//										Timer SR Flag Codecs											//
// ==================================================================================================== //

/**
 * @brief Extracts pending Timer IRQ flag selectors from an `SR` image
 * @param[in] srRegImage Caller-owned `SR` image
 * @param[out] pIrqMask Destination for pending IRQ flag mask
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: IRQ flag mask was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pIrqMask is `NULL`
 */
driver_status_t Codec_TIM_ExtractIRQFlagMask
(
	const reg							srRegImage,
	timer_irq_t* const					pIrqMask
);

/**
 * @brief Stages an IRQ flag acknowledge write image for selected IRQ sources
 * @param[in] srRegImage Caller-owned `SR` image before acknowledge staging
 * @param[in] irqMask Timer IRQ source mask to acknowledge
 * @param[out] pSrRegImage Destination for the staged `SR` acknowledge image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: IRQ acknowledge image was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p irqMask is invalid
 * @note STM32F1 Timer status flags use write-`0`-to-clear semantics. This API
 * clears only selected supported IRQ flags and stages write-`1` preserve bits
 * for other supported status flags when an acknowledge write is needed.
 */
driver_status_t Codec_TIM_StageIRQAckMask
(
	const reg							srRegImage,
	const timer_irq_t						irqMask,
	reg* const							pSrRegImage
);

/** @} */ // TIM_03_Driver_03_Codec

/** @} */ // TIM_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_CODEC_H_ */
