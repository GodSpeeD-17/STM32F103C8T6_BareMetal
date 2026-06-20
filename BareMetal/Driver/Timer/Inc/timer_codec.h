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
#include "timer_config.h"

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
 *
 * @note Stage APIs mutate caller-owned register images in place. The image
 * pointer must reference a local driver-owned @ref `reg` image, not a live
 * peripheral register address. Implementations stage through local temporaries
 * and write back only after successful validation.
 * @{
 */

// ==================================================================================================== //
//										Timer Timebase Codecs											//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer Timebase Scalar Codecs									//
// ==================================================================================================== //

/**
 * @brief Extracts a Timer prescaler value from a `PSC` image
 * @param[in] pscRegImage Caller-owned `PSC` image
 * @param[out] pPrescaler Destination for decoded prescaler value
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Prescaler value was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPrescaler is `NULL`
 */
driver_status_t Codec_TIM_ExtractPrescaler
(
	const reg							pscRegImage,
	timer_prescaler_t* const			pPrescaler
);

/**
 * @brief Stages a Timer prescaler value into a `PSC` image
 * @param[in,out] pPscRegImage Caller-owned `PSC` image to update in place
 * @param[in] prescaler Prescaler value to stage into `PSC[15:0]`
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Prescaler value was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPscRegImage is `NULL`
 */
driver_status_t Codec_TIM_StagePrescaler
(
	reg* const							pPscRegImage,
	const timer_prescaler_t				prescaler
);

/**
 * @brief Extracts a Timer auto-reload value from an `ARR` image
 * @param[in] arrRegImage Caller-owned `ARR` image
 * @param[out] pAutoReload Destination for decoded auto-reload value
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload value was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pAutoReload is `NULL`
 */
driver_status_t Codec_TIM_ExtractAutoReload
(
	const reg							arrRegImage,
	timer_auto_reload_t* const			pAutoReload
);

/**
 * @brief Stages a Timer auto-reload value into an `ARR` image
 * @param[in,out] pArrRegImage Caller-owned `ARR` image to update in place
 * @param[in] autoReload Auto-reload value to stage into `ARR[15:0]`
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload value was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pArrRegImage is `NULL`
 */
driver_status_t Codec_TIM_StageAutoReload
(
	reg* const							pArrRegImage,
	const timer_auto_reload_t			autoReload
);

/**
 * @brief Extracts a Timer counter value from a `CNT` image
 * @param[in] cntRegImage Caller-owned `CNT` image
 * @param[out] pCounterValue Destination for decoded counter value
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter value was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounterValue is `NULL`
 */
driver_status_t Codec_TIM_ExtractCounterValue
(
	const reg							cntRegImage,
	timer_counter_value_t* const		pCounterValue
);

/**
 * @brief Stages a Timer counter value into a `CNT` image
 * @param[in,out] pCntRegImage Caller-owned `CNT` image to update in place
 * @param[in] counterValue Counter value to stage into `CNT[15:0]`
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter value was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCntRegImage is `NULL`
 */
driver_status_t Codec_TIM_StageCounterValue
(
	reg* const							pCntRegImage,
	const timer_counter_value_t			counterValue
);

// ==================================================================================================== //
//										Timer Timebase Config Codecs									//
// ==================================================================================================== //

/**
 * @brief Extracts Timer timebase configuration from `PSC`, `ARR`, and `CNT` images
 * @param[in] pscRegImage Caller-owned `PSC` image
 * @param[in] arrRegImage Caller-owned `ARR` image
 * @param[in] cntRegImage Caller-owned `CNT` image
 * @param[out] pTimebase Destination for decoded timebase configuration
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timebase configuration was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pTimebase is `NULL`
 */
driver_status_t Codec_TIM_ExtractTimeBaseConfig
(
	const reg							pscRegImage,
	const reg							arrRegImage,
	const reg							cntRegImage,
	timer_config_timebase_t* const		pTimebase
);

/**
 * @brief Stages Timer timebase configuration into `PSC`, `ARR`, and `CNT` images
 * @param[in,out] pPscRegImage Caller-owned `PSC` image to update in place
 * @param[in,out] pArrRegImage Caller-owned `ARR` image to update in place
 * @param[in,out] pCntRegImage Caller-owned `CNT` image to update in place
 * @param[in] pTimebase Timebase configuration to stage
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timebase configuration was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: One or more required pointers are `NULL`
 */
driver_status_t Codec_TIM_StageTimeBaseConfig
(
	reg* const								pPscRegImage,
	reg* const								pArrRegImage,
	reg* const								pCntRegImage,
	const timer_config_timebase_t* const	pTimebase
);

// ==================================================================================================== //
//										Timer CR1 Counter Codecs										//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer CR1 Counter Selector Codecs								//
// ==================================================================================================== //

/**
 * @brief Extracts the Timer counter direction selector from a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[out] pDirection Destination for decoded direction selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Direction selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDirection is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Raw `DIR` field is not decodable
 */
driver_status_t Codec_TIM_ExtractCounterDirection
(
	const reg							cr1RegImage,
	timer_direction_t* const			pDirection
);

/**
 * @brief Stages the Timer counter direction selector into a `CR1` image
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in] direction Timer counter direction selector
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Direction selector was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p direction cannot be encoded
 */
driver_status_t Codec_TIM_StageCounterDirection
(
	reg* const							pCr1RegImage,
	const timer_direction_t				direction
);

/**
 * @brief Extracts the Timer counter alignment selector from a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[out] pAlignment Destination for decoded edge/center-aligned selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Alignment selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pAlignment is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Raw `CMS` field is not decodable
 */
driver_status_t Codec_TIM_ExtractCounterAlignment
(
	const reg							cr1RegImage,
	timer_count_mode_t* const			pAlignment
);

/**
 * @brief Stages the Timer counter alignment selector into a `CR1` image
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in] alignment Timer edge/center-aligned selector
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Alignment selector was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p alignment cannot be encoded
 */
driver_status_t Codec_TIM_StageCounterAlignment
(
	reg* const							pCr1RegImage,
	const timer_count_mode_t			alignment
);

/**
 * @brief Extracts the Timer one-pulse selector from a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[out] pOnePulse Destination for decoded one-pulse selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: One-pulse selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pOnePulse is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Raw `OPM` field is not decodable
 */
driver_status_t Codec_TIM_ExtractOnePulse
(
	const reg							cr1RegImage,
	timer_opm_t* const					pOnePulse
);

/**
 * @brief Stages the Timer one-pulse selector into a `CR1` image
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in] onePulse Timer one-pulse selector
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: One-pulse selector was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p onePulse cannot be encoded
 */
driver_status_t Codec_TIM_StageOnePulse
(
	reg* const							pCr1RegImage,
	const timer_opm_t					onePulse
);

/**
 * @brief Extracts the Timer auto-reload preload selector from a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[out] pAutoReloadPreload Destination for decoded auto-reload preload selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload preload selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pAutoReloadPreload is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Raw `ARPE` field is not decodable
 */
driver_status_t Codec_TIM_ExtractAutoReloadPreload
(
	const reg							cr1RegImage,
	timer_arpe_t* const					pAutoReloadPreload
);

/**
 * @brief Stages the Timer auto-reload preload selector into a `CR1` image
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in] autoReloadPreload Timer auto-reload preload selector
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Auto-reload preload selector was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p autoReloadPreload cannot be encoded
 */
driver_status_t Codec_TIM_StageAutoReloadPreload
(
	reg* const							pCr1RegImage,
	const timer_arpe_t					autoReloadPreload
);

/**
 * @brief Extracts the Timer update request source selector from a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[out] pUpdateSource Destination for decoded update-source selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update-source selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pUpdateSource is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Raw `URS` field is not decodable
 */
driver_status_t Codec_TIM_ExtractUpdateSource
(
	const reg							cr1RegImage,
	timer_update_source_t* const		pUpdateSource
);

/**
 * @brief Stages the Timer update request source selector into a `CR1` image
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in] updateSource Timer update-source selector
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update-source selector was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p updateSource cannot be encoded
 */
driver_status_t Codec_TIM_StageUpdateSource
(
	reg* const							pCr1RegImage,
	const timer_update_source_t			updateSource
);

/**
 * @brief Extracts the Timer clock division selector from a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[out] pClockDivision Destination for decoded clock-division selector
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock-division selector was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockDivision is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Raw `CKD` field is not decodable
 */
driver_status_t Codec_TIM_ExtractClockDivision
(
	const reg							cr1RegImage,
	timer_clock_division_t* const		pClockDivision
);

/**
 * @brief Stages the Timer clock division selector into a `CR1` image
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in] clockDivision Timer clock-division selector
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock-division selector was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockDivision cannot be encoded
 */
driver_status_t Codec_TIM_StageClockDivision
(
	reg* const							pCr1RegImage,
	const timer_clock_division_t		clockDivision
);

// ==================================================================================================== //
//										Timer CR1 Counter Config Codecs								//
// ==================================================================================================== //

/**
 * @brief Extracts Timer counter configuration selectors from a `CR1` image
 * @param[in] cr1RegImage Caller-owned `CR1` image
 * @param[out] pCounter Destination for decoded counter configuration
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter configuration was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounter is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A raw `CR1` field is not decodable by the current public Timer vocabulary
 * @note This API preserves no hardware state because it reads only @p cr1RegImage.
 */
driver_status_t Codec_TIM_ExtractCounterConfig
(
	const reg							cr1RegImage,
	timer_config_counter_t* const		pCounter
);

/**
 * @brief Stages Timer counter configuration selectors into a `CR1` image
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in] pCounter Counter configuration to stage
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `CR1` image was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounter or @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more selectors cannot be encoded
 * @note This API preserves `CEN` and `UDIS`; use the dedicated state codecs for those fields.
 */
driver_status_t Codec_TIM_StageCounterConfig
(
	reg* const							pCr1RegImage,
	const timer_config_counter_t* const	pCounter
);

// ==================================================================================================== //
//										Timer CR1 Runtime State Codecs									//
// ==================================================================================================== //

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
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in] counterState Requested counter state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Clear `CEN`
 * - @ref `DRIVER_STATUS_ON`: Set `CEN`
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter enable state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p counterState is not an accepted state
 */
driver_status_t Codec_TIM_StageCounterEnableState
(
	reg* const							pCr1RegImage,
	const driver_status_t				counterState
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
 * @param[in,out] pCr1RegImage Caller-owned `CR1` image to update in place
 * @param[in] updateEventState Requested update-event state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Set `UDIS`
 * - @ref `DRIVER_STATUS_ON`: Clear `UDIS`
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update-event state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr1RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p updateEventState is not an accepted state
 * @note Raw `UDIS` has inverse polarity: `UDIS == 1U` means update events are disabled.
 */
driver_status_t Codec_TIM_StageUpdateEventState
(
	reg* const							pCr1RegImage,
	const driver_status_t				updateEventState
);

// ==================================================================================================== //
//										Timer Trigger Codecs											//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer Master Mode Codecs										//
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
 * @param[in,out] pCr2RegImage Caller-owned `CR2` image to update in place
 * @param[in] masterMode Timer master-mode selector
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Master-mode selector was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCr2RegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p masterMode cannot be encoded
 */
driver_status_t Codec_TIM_StageMasterMode
(
	reg* const							pCr2RegImage,
	const timer_master_mode_t			masterMode
);

// ==================================================================================================== //
//										Timer Slave Mode Codecs										//
// ==================================================================================================== //

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
	timer_slave_mode_t* const			pSlaveMode
);

/**
 * @brief Stages the Timer slave-mode selector into an `SMCR` image
 * @param[in,out] pSmcrRegImage Caller-owned `SMCR` image to update in place
 * @param[in] slaveMode Timer slave-mode selector
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Slave-mode selector was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSmcrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p slaveMode cannot be encoded
 */
driver_status_t Codec_TIM_StageSlaveMode
(
	reg* const							pSmcrRegImage,
	const timer_slave_mode_t			slaveMode
);

// ==================================================================================================== //
//										Timer CCMR Channel Codecs										//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer CCMR Channel Selection Codecs							//
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
	const timer_channel_t				channel,
	timer_channel_ccs_t* const			pCaptureCompareSelection
);

/**
 * @brief Stages one channel capture/compare selection into a `CCMR1` or `CCMR2` image
 * @param[in,out] pCcmrRegImage Caller-owned `CCMR1` or `CCMR2` image to update in place
 * @param[in] channel Timer single-channel mask
 * @param[in] captureCompareSelection Timer `CCxS` selector
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Capture/compare selection was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCcmrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel or @p captureCompareSelection cannot be encoded
 * @note Caller must pass the `CCMR1` image for channels 1/2 and the `CCMR2` image for channels 3/4.
 */
driver_status_t Codec_TIM_StageChannelSelection
(
	reg* const							pCcmrRegImage,
	const timer_channel_t				channel,
	const timer_channel_ccs_t			captureCompareSelection
);

// ==================================================================================================== //
//										Timer CCMR Output Compare Codecs								//
// ==================================================================================================== //

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
	const timer_channel_t				channel,
	timer_channel_oc_clear_t* const		pOutputCompareClear,
	timer_channel_mode_t* const			pOutputCompareMode,
	timer_channel_oc_preload_t* const	pOutputComparePreload,
	timer_channel_oc_fast_t* const		pOutputCompareFast
);

/**
 * @brief Stages one output-compare channel configuration into a `CCMR1` or `CCMR2` image
 * @param[in,out] pCcmrRegImage Caller-owned `CCMR1` or `CCMR2` image to update in place
 * @param[in] channel Timer single-channel mask
 * @param[in] outputCompareClear Timer output-compare clear selector
 * @param[in] outputCompareMode Timer output-compare mode selector
 * @param[in] outputComparePreload Timer output-compare preload selector
 * @param[in] outputCompareFast Timer output-compare fast selector
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Output-compare configuration was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCcmrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel or one or more selectors cannot be encoded
 * @note This API also stages `CCxS` to @ref `TIMx_CHANNEL_CCS_OUTPUT`.
 */
driver_status_t Codec_TIM_StageOutputCompareConfig
(
	reg* const							pCcmrRegImage,
	const timer_channel_t				channel,
	const timer_channel_oc_clear_t		outputCompareClear,
	const timer_channel_mode_t			outputCompareMode,
	const timer_channel_oc_preload_t	outputComparePreload,
	const timer_channel_oc_fast_t		outputCompareFast
);

// ==================================================================================================== //
//										Timer CCER Channel Codecs										//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer CCER Channel Enable Codecs								//
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
	const timer_channel_t				channel,
	driver_status_t* const				pChannelState
);

/**
 * @brief Stages one channel enable state into a `CCER` image
 * @param[in,out] pCcerRegImage Caller-owned `CCER` image to update in place
 * @param[in] channel Timer single-channel mask
 * @param[in] channelState Requested channel enable state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Clear `CCxE`
 * - @ref `DRIVER_STATUS_ON`: Set `CCxE`
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Channel enable state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCcerRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel or @p channelState is not an accepted state
 */
driver_status_t Codec_TIM_StageChannelEnableState
(
	reg* const							pCcerRegImage,
	const timer_channel_t				channel,
	const driver_status_t				channelState
);

// ==================================================================================================== //
//										Timer CCER Channel Polarity Codecs								//
// ==================================================================================================== //

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
	const timer_channel_t				channel,
	timer_channel_polarity_t* const		pPolarity
);

/**
 * @brief Stages one channel polarity selector into a `CCER` image
 * @param[in,out] pCcerRegImage Caller-owned `CCER` image to update in place
 * @param[in] channel Timer single-channel mask
 * @param[in] polarity Timer channel polarity selector
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Channel polarity selector was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCcerRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel or @p polarity cannot be encoded
 */
driver_status_t Codec_TIM_StageChannelPolarity
(
	reg* const							pCcerRegImage,
	const timer_channel_t				channel,
	const timer_channel_polarity_t		polarity
);

// ==================================================================================================== //
//										Timer DIER Request Codecs										//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer DIER IRQ Request Codecs									//
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
 * @param[in,out] pDierRegImage Caller-owned `DIER` image to update in place
 * @param[in] irqMask Timer IRQ source mask to modify
 * @param[in] irqEnable Requested IRQ enable selector
 * Accepted values:
 * - @ref `TIMx_IRQ_DISABLE`: Disable selected IRQ sources
 * - @ref `TIMx_IRQ_ENABLE`: Enable selected IRQ sources
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: IRQ enable state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDierRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p irqMask or @p irqEnable is invalid
 * @note NVIC enable/disable policy belongs to the Timer driver layer.
 */
driver_status_t Codec_TIM_StageIRQEnableMask
(
	reg* const							pDierRegImage,
	const timer_irq_t					irqMask,
	const timer_irq_enable_t			irqEnable
);

// ==================================================================================================== //
//										Timer DIER DMA Request Codecs									//
// ==================================================================================================== //

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
 * @param[in,out] pDierRegImage Caller-owned `DIER` image to update in place
 * @param[in] dmaMask Timer DMA source mask to modify
 * @param[in] dmaState Requested DMA enable state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable selected DMA sources
 * - @ref `DRIVER_STATUS_ON`: Enable selected DMA sources
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: DMA enable state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDierRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p dmaMask or @p dmaState is invalid
 */
driver_status_t Codec_TIM_StageDMAEnableMask
(
	reg* const							pDierRegImage,
	const timer_dma_t					dmaMask,
	const driver_status_t				dmaState
);

// ==================================================================================================== //
//										Timer SR Flag Codecs											//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer SR IRQ Flag Codecs										//
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
 * @param[in,out] pSrRegImage Caller-owned `SR` image to update in place
 * @param[in] irqMask Timer IRQ source mask to acknowledge
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
	reg* const							pSrRegImage,
	const timer_irq_t					irqMask
);

/** @} */ // TIM_03_Driver_03_Codec

/** @} */ // TIM_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_CODEC_H_ */
