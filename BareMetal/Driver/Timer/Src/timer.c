/**
 * @file	timer.c
 * @author	Shrey Shah
 * @brief	Timer Driver Implementation
 * @version	v1.0
 * @date	20-06-2026
 *
 * @details
 * This source file implements the public Timer driver API declared in
 * @ref `timer.h`. The driver layer owns public validation, Timer clock enable,
 * register-image reads, codec staging/extraction orchestration, dirty writes,
 * and public @ref `driver_status_t` handling.
 *
 * This first Timer refactor pass is intentionally limited to:
 * - `TIMx_CR1` counter behavior fields represented by @ref `timer_config_counter_t`
 * - `TIMx_PSC` prescaler
 * - `TIMx_ARR` auto-reload value
 * - `TIMx_CNT` counter value
 *
 * Channel/PWM, IRQ/NVIC, DMA, master/slave, and delay helper behavior are not
 * part of this implementation pass.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "timer.h"
#include "timer_codec.h"
#include "timer_ll.h"
#include "rcc.h"

// ==================================================================================================== //
//										Local Reset Configuration										//
// ==================================================================================================== //

/** @brief Reset-equivalent Timer prescaler value @def TIM_DRIVER_RESET_PSC */
#define TIM_DRIVER_RESET_PSC						((timer_prescaler_t) 0U)
/** @brief Reset-equivalent Timer auto-reload value @def TIM_DRIVER_RESET_ARR */
#define TIM_DRIVER_RESET_ARR						((timer_auto_reload_t) 0U)
/** @brief Reset-equivalent Timer counter value @def TIM_DRIVER_RESET_CNT */
#define TIM_DRIVER_RESET_CNT						((timer_counter_value_t) 0U)

/**
 * @brief Reset-equivalent timebase configuration for the driver-owned fields
 */
static const timer_config_timebase_t TIM_DRIVER_RESET_TIMEBASE =
{
	.prescaler		= TIM_DRIVER_RESET_PSC,
	.auto_reload	= TIM_DRIVER_RESET_ARR,
	.initial_count	= TIM_DRIVER_RESET_CNT
};

/**
 * @brief Reset-equivalent counter configuration for the driver-owned `CR1` fields
 * @details
 * This intentionally excludes `CEN` and `UDIS`, because those runtime fields
 * are not members of @ref `timer_config_counter_t`.
 */
static const timer_config_counter_t TIM_DRIVER_RESET_COUNTER =
{
	.direction				= TIMx_DIR_COUNT_UP,
	.alignment				= TIMx_MODE_NORMAL,
	.one_pulse				= TIMx_OPM_DISABLE,
	.auto_reload_preload	= TIMx_ARPE_DISABLE,
	.update_source			= TIMx_UPDATE_SOURCE_ANY,
	.clock_division			= TIMx_CKD_CLK_FREQ
};

// ==================================================================================================== //
//										Local Validation Helpers										//
// ==================================================================================================== //

/**
 * @brief Validates a Timer peripheral instance pointer
 * @param[in] TIMx Timer peripheral instance
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p TIMx is a supported general-purpose Timer instance
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 */
__STATIC_FORCEINLINE driver_status_t TIM_ValidateInstance(const TIM_TypeDef* const TIMx)
{
	if (TIM_INSTANCE_IS_VALID(TIMx) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer timebase configuration pointer
 * @param[in] pTimebase Timer timebase configuration
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p pTimebase is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pTimebase is `NULL`
 * @note The scalar members are 16-bit register-backed typedefs, so every value
 * representable by the public type is encodable by the current codec.
 */
__STATIC_FORCEINLINE driver_status_t TIM_ValidateTimebaseConfig
(
	const timer_config_timebase_t* const pTimebase
)
{
	if (pTimebase == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer counter configuration pointer and all public selectors
 * @param[in] pCounter Timer counter configuration
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p pCounter is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounter is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more selectors are invalid
 */
__STATIC_FORCEINLINE driver_status_t TIM_ValidateCounterConfig
(
	const timer_config_counter_t* const pCounter
)
{
	if (pCounter == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if
	(
		(TIM_DIRECTION_IS_VALID(pCounter->direction) == 0x00U) ||
		(TIM_COUNT_MODE_IS_VALID(pCounter->alignment) == 0x00U) ||
		(TIM_OPM_IS_VALID(pCounter->one_pulse) == 0x00U) ||
		(TIM_ARPE_IS_VALID(pCounter->auto_reload_preload) == 0x00U) ||
		(TIM_UPDATE_SOURCE_IS_VALID(pCounter->update_source) == 0x00U) ||
		(TIM_CLOCK_DIVISION_IS_VALID(pCounter->clock_division) == 0x00U)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a complete Timer configuration pointer
 * @param[in] pConfig Timer root configuration
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p pConfig is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pConfig is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more selector fields are invalid
 */
__STATIC_FORCEINLINE driver_status_t TIM_ValidateConfig(const timer_config_t* const pConfig)
{
	if (pConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_ValidateTimebaseConfig(&(pConfig->timebase)));
	ASSERT_DRIVER_STATUS(TIM_ValidateCounterConfig(&(pConfig->counter)));

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer direction selector
 * @param[in] direction Timer direction selector
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p direction is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p direction is invalid
 */
__STATIC_FORCEINLINE driver_status_t TIM_ValidateDirection(const timer_direction_t direction)
{
	return (TIM_DIRECTION_IS_VALID(direction) != 0x00U) ? DRIVER_STATUS_SUCCESS : DRIVER_STATUS_ERROR_INVALID_ARG;
}

/**
 * @brief Validates a Timer alignment selector
 * @param[in] alignment Timer edge/center-aligned selector
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p alignment is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p alignment is invalid
 */
__STATIC_FORCEINLINE driver_status_t TIM_ValidateAlignment(const timer_count_mode_t alignment)
{
	return (TIM_COUNT_MODE_IS_VALID(alignment) != 0x00U) ? DRIVER_STATUS_SUCCESS : DRIVER_STATUS_ERROR_INVALID_ARG;
}

/**
 * @brief Validates a Timer one-pulse selector
 * @param[in] onePulse Timer one-pulse selector
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p onePulse is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p onePulse is invalid
 */
__STATIC_FORCEINLINE driver_status_t TIM_ValidateOnePulse(const timer_opm_t onePulse)
{
	return (TIM_OPM_IS_VALID(onePulse) != 0x00U) ? DRIVER_STATUS_SUCCESS : DRIVER_STATUS_ERROR_INVALID_ARG;
}

/**
 * @brief Validates a Timer auto-reload preload selector
 * @param[in] autoReloadPreload Timer auto-reload preload selector
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p autoReloadPreload is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p autoReloadPreload is invalid
 */
__STATIC_FORCEINLINE driver_status_t TIM_ValidateAutoReloadPreload
(
	const timer_arpe_t autoReloadPreload
)
{
	return (TIM_ARPE_IS_VALID(autoReloadPreload) != 0x00U) ? DRIVER_STATUS_SUCCESS : DRIVER_STATUS_ERROR_INVALID_ARG;
}

/**
 * @brief Validates a Timer update request source selector
 * @param[in] updateSource Timer update request source selector
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p updateSource is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p updateSource is invalid
 */
__STATIC_FORCEINLINE driver_status_t TIM_ValidateUpdateSource
(
	const timer_update_source_t updateSource
)
{
	return (TIM_UPDATE_SOURCE_IS_VALID(updateSource) != 0x00U) ? DRIVER_STATUS_SUCCESS : DRIVER_STATUS_ERROR_INVALID_ARG;
}

/**
 * @brief Validates a Timer clock division selector
 * @param[in] clockDivision Timer clock division selector
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p clockDivision is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockDivision is invalid
 */
__STATIC_FORCEINLINE driver_status_t TIM_ValidateClockDivision
(
	const timer_clock_division_t clockDivision
)
{
	return (TIM_CLOCK_DIVISION_IS_VALID(clockDivision) != 0x00U) ? DRIVER_STATUS_SUCCESS : DRIVER_STATUS_ERROR_INVALID_ARG;
}

// ==================================================================================================== //
//										Local RCC Integration Helpers									//
// ==================================================================================================== //

/**
 * @brief Returns the APB1 clock enable mask for one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[out] pClockMask Destination for APB1 clock enable mask
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock mask was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockMask is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 */
__STATIC_FORCEINLINE driver_status_t TIM_GetAPB1ClockMask
(
	const TIM_TypeDef* const	TIMx,
	reg* const				pClockMask
)
{
	if (pClockMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch ((uintptr_t) TIMx)
	{
		case TIM2_BASE_ADDRESS:
		{
			*pClockMask = RCC_APB1ENR_TIM2EN;
			break;
		}
		case TIM3_BASE_ADDRESS:
		{
			*pClockMask = RCC_APB1ENR_TIM3EN;
			break;
		}
		case TIM4_BASE_ADDRESS:
		{
			*pClockMask = RCC_APB1ENR_TIM4EN;
			break;
		}
		case TIM5_BASE_ADDRESS:
		{
			*pClockMask = RCC_APB1ENR_TIM5EN;
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
 * @brief Enables the APB1 peripheral clock for one supported Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer clock was enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 */
__STATIC_FORCEINLINE driver_status_t TIM_EnableClock(const TIM_TypeDef* const TIMx)
{
	reg clockMask = 0x00000000UL;

	ASSERT_DRIVER_STATUS(TIM_GetAPB1ClockMask(TIMx, &clockMask));
	return RCC_APB1_ClockEnable(clockMask);
}

// ==================================================================================================== //
//										Local Status Mapping Helpers									//
// ==================================================================================================== //

/**
 * @brief Maps a validated staging failure into a public driver state failure
 * @param[in] codecStatus Status returned by a codec Stage API after driver-side validation
 * @returns Public driver status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Codec staging succeeded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Codec staging failed after driver validation
 * @note Public validation occurs before staging. Any codec error after that
 * means driver orchestration or local image ownership is inconsistent.
 */
__STATIC_FORCEINLINE driver_status_t TIM_MapCodecStageStatus(const driver_status_t codecStatus)
{
	return (codecStatus == DRIVER_STATUS_SUCCESS) ? DRIVER_STATUS_SUCCESS : DRIVER_STATUS_ERROR_STATE;
}

/**
 * @brief Maps a codec extraction status into the public driver vocabulary
 * @param[in] codecStatus Status returned by a codec Extract API
 * @returns Public driver status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Codec extraction succeeded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: Codec destination pointer was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Raw hardware image could not be decoded
 */
__STATIC_FORCEINLINE driver_status_t TIM_MapCodecExtractStatus(const driver_status_t codecStatus)
{
	if (codecStatus == DRIVER_STATUS_ERROR_NULL_PTR)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	return (codecStatus == DRIVER_STATUS_SUCCESS) ? DRIVER_STATUS_SUCCESS : DRIVER_STATUS_ERROR_STATE;
}

// ==================================================================================================== //
//										Local Dirty Write Helpers										//
// ==================================================================================================== //

/**
 * @brief Writes `TIMx_CR1` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * @param[in] currentRegImage Current hardware `CR1` image
 * @param[in] stagedRegImage Staged `CR1` image
 * @returns Void
 */
__STATIC_FORCEINLINE void TIM_WriteCR1IfChanged
(
	TIM_TypeDef* const	TIMx,
	const reg			currentRegImage,
	const reg			stagedRegImage
)
{
	if (currentRegImage != stagedRegImage)
	{
		LL_TIM_WriteCR1(TIMx, stagedRegImage);
	}
}

/**
 * @brief Writes `TIMx_PSC` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * @param[in] currentRegImage Current hardware `PSC` image
 * @param[in] stagedRegImage Staged `PSC` image
 * @returns Void
 */
__STATIC_FORCEINLINE void TIM_WritePSCIfChanged
(
	TIM_TypeDef* const	TIMx,
	const reg			currentRegImage,
	const reg			stagedRegImage
)
{
	if (currentRegImage != stagedRegImage)
	{
		LL_TIM_WritePSC(TIMx, stagedRegImage);
	}
}

/**
 * @brief Writes `TIMx_ARR` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * @param[in] currentRegImage Current hardware `ARR` image
 * @param[in] stagedRegImage Staged `ARR` image
 * @returns Void
 */
__STATIC_FORCEINLINE void TIM_WriteARRIfChanged
(
	TIM_TypeDef* const	TIMx,
	const reg			currentRegImage,
	const reg			stagedRegImage
)
{
	if (currentRegImage != stagedRegImage)
	{
		LL_TIM_WriteARR(TIMx, stagedRegImage);
	}
}

/**
 * @brief Writes `TIMx_CNT` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * @param[in] currentRegImage Current hardware `CNT` image
 * @param[in] stagedRegImage Staged `CNT` image
 * @returns Void
 */
__STATIC_FORCEINLINE void TIM_WriteCNTIfChanged
(
	TIM_TypeDef* const	TIMx,
	const reg			currentRegImage,
	const reg			stagedRegImage
)
{
	if (currentRegImage != stagedRegImage)
	{
		LL_TIM_WriteCNT(TIMx, stagedRegImage);
	}
}

// ==================================================================================================== //
//										Local Timebase Orchestration									//
// ==================================================================================================== //

/**
 * @brief Applies a staged timebase configuration to one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[in] pTimebase Timebase configuration to apply
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timebase fields were applied
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Codec staging failed after validation
 */
__STATIC_FORCEINLINE driver_status_t TIM_ApplyTimebaseConfig
(
	TIM_TypeDef* const						TIMx,
	const timer_config_timebase_t* const	pTimebase
)
{
	reg pscRegImage = LL_TIM_ReadPSC(TIMx);
	reg arrRegImage = LL_TIM_ReadARR(TIMx);
	reg cntRegImage = LL_TIM_ReadCNT(TIMx);
	const reg currentPscRegImage = pscRegImage;
	const reg currentArrRegImage = arrRegImage;
	const reg currentCntRegImage = cntRegImage;

	ASSERT_DRIVER_STATUS
	(
			TIM_MapCodecStageStatus
		(
			Codec_TIM_StageTimeBaseConfig(&pscRegImage, &arrRegImage, &cntRegImage, pTimebase)
		)
	);

	TIM_WritePSCIfChanged(TIMx, currentPscRegImage, pscRegImage);
	TIM_WriteARRIfChanged(TIMx, currentArrRegImage, arrRegImage);
	TIM_WriteCNTIfChanged(TIMx, currentCntRegImage, cntRegImage);

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Applies a staged counter configuration to one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[in] pCounter Counter configuration to apply
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter fields were applied
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Codec staging failed after validation
 */
__STATIC_FORCEINLINE driver_status_t TIM_ApplyCounterConfig
(
	TIM_TypeDef* const						TIMx,
	const timer_config_counter_t* const		pCounter
)
{
	reg cr1RegImage = LL_TIM_ReadCR1(TIMx);
	const reg currentCr1RegImage = cr1RegImage;

	ASSERT_DRIVER_STATUS
	(
			TIM_MapCodecStageStatus
		(
			Codec_TIM_StageCounterConfig(&cr1RegImage, pCounter)
		)
	);

	TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage);
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Root Configuration APIs									//
// ==================================================================================================== //

driver_status_t TIM_Config(TIM_TypeDef* const TIMx, const timer_config_t* const pConfig)
{
	reg cr1RegImage = 0x00000000UL;
	reg pscRegImage = 0x00000000UL;
	reg arrRegImage = 0x00000000UL;
	reg cntRegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;
	reg currentPscRegImage = 0x00000000UL;
	reg currentArrRegImage = 0x00000000UL;
	reg currentCntRegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(TIM_ValidateConfig(pConfig));
	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	//! Read each required register exactly once, then stage all requested fields into local images.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	pscRegImage = LL_TIM_ReadPSC(TIMx);
	arrRegImage = LL_TIM_ReadARR(TIMx);
	cntRegImage = LL_TIM_ReadCNT(TIMx);

	currentCr1RegImage = cr1RegImage;
	currentPscRegImage = pscRegImage;
	currentArrRegImage = arrRegImage;
	currentCntRegImage = cntRegImage;

	ASSERT_DRIVER_STATUS(TIM_MapCodecStageStatus(Codec_TIM_StageCounterConfig(&cr1RegImage, &(pConfig->counter))));
	ASSERT_DRIVER_STATUS
	(
			TIM_MapCodecStageStatus
		(
			Codec_TIM_StageTimeBaseConfig(&pscRegImage, &arrRegImage, &cntRegImage, &(pConfig->timebase))
		)
	);

	TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage);
	TIM_WritePSCIfChanged(TIMx, currentPscRegImage, pscRegImage);
	TIM_WriteARRIfChanged(TIMx, currentArrRegImage, arrRegImage);
	TIM_WriteCNTIfChanged(TIMx, currentCntRegImage, cntRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_DeConfig(TIM_TypeDef* const TIMx)
{
	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));
	ASSERT_DRIVER_STATUS(TIM_ApplyCounterConfig(TIMx, &TIM_DRIVER_RESET_COUNTER));
	ASSERT_DRIVER_STATUS(TIM_ApplyTimebaseConfig(TIMx, &TIM_DRIVER_RESET_TIMEBASE));

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Group Configuration APIs									//
// ==================================================================================================== //

driver_status_t TIM_GetTimebaseConfig
(
	TIM_TypeDef* const					TIMx,
	timer_config_timebase_t* const		pTimebase
)
{
	reg pscRegImage = 0x00000000UL;
	reg arrRegImage = 0x00000000UL;
	reg cntRegImage = 0x00000000UL;

	if (pTimebase == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	pscRegImage = LL_TIM_ReadPSC(TIMx);
	arrRegImage = LL_TIM_ReadARR(TIMx);
	cntRegImage = LL_TIM_ReadCNT(TIMx);

	return Codec_TIM_ExtractTimeBaseConfig(pscRegImage, arrRegImage, cntRegImage, pTimebase);
}

driver_status_t TIM_SetTimebaseConfig
(
	TIM_TypeDef* const						TIMx,
	const timer_config_timebase_t* const	pTimebase
)
{
	ASSERT_DRIVER_STATUS(TIM_ValidateTimebaseConfig(pTimebase));
	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	return TIM_ApplyTimebaseConfig(TIMx, pTimebase);
}

driver_status_t TIM_GetCounterConfig
(
	TIM_TypeDef* const					TIMx,
	timer_config_counter_t* const		pCounter
)
{
	reg cr1RegImage = 0x00000000UL;

	if (pCounter == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	return TIM_MapCodecExtractStatus(Codec_TIM_ExtractCounterConfig(cr1RegImage, pCounter));
}

driver_status_t TIM_SetCounterConfig
(
	TIM_TypeDef* const						TIMx,
	const timer_config_counter_t* const		pCounter
)
{
	ASSERT_DRIVER_STATUS(TIM_ValidateCounterConfig(pCounter));
	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	return TIM_ApplyCounterConfig(TIMx, pCounter);
}

// ==================================================================================================== //
//										Timer Timebase Field APIs										//
// ==================================================================================================== //

driver_status_t TIM_GetPrescaler
(
	TIM_TypeDef* const				TIMx,
	timer_prescaler_t* const		pPrescaler
)
{
	if (pPrescaler == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	return Codec_TIM_ExtractPrescaler(LL_TIM_ReadPSC(TIMx), pPrescaler);
}

driver_status_t TIM_SetPrescaler
(
	TIM_TypeDef* const					TIMx,
	const timer_prescaler_t				prescaler
)
{
	reg pscRegImage = 0x00000000UL;
	reg currentPscRegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	pscRegImage = LL_TIM_ReadPSC(TIMx);
	currentPscRegImage = pscRegImage;

	ASSERT_DRIVER_STATUS(TIM_MapCodecStageStatus(Codec_TIM_StagePrescaler(&pscRegImage, prescaler)));
	TIM_WritePSCIfChanged(TIMx, currentPscRegImage, pscRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetFrequency
(
	TIM_TypeDef* const				TIMx,
	timer_frequency_t* const		pFrequency
)
{
	timer_prescaler_t prescaler = 0U;
	timer_frequency_t timerInputClock = 0UL;

	if (pFrequency == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_GetPrescaler(TIMx, &prescaler));

	timerInputClock = (timer_frequency_t) RCC_GetBusFreq(RCC_APB1_BUS);
	if (timerInputClock == 0UL)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	if (RCC_GetBusPrescaler(RCC_APB1_BUS) != RCC_APB1_DIV_1)
	{
		timerInputClock <<= 1U;
	}

	*pFrequency = (timer_frequency_t) (timerInputClock / (((timer_frequency_t) prescaler) + 1UL));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetAutoReload
(
	TIM_TypeDef* const					TIMx,
	timer_auto_reload_t* const			pAutoReload
)
{
	if (pAutoReload == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	return Codec_TIM_ExtractAutoReload(LL_TIM_ReadARR(TIMx), pAutoReload);
}

driver_status_t TIM_SetAutoReload
(
	TIM_TypeDef* const						TIMx,
	const timer_auto_reload_t				autoReload
)
{
	reg arrRegImage = 0x00000000UL;
	reg currentArrRegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	arrRegImage = LL_TIM_ReadARR(TIMx);
	currentArrRegImage = arrRegImage;

	ASSERT_DRIVER_STATUS(TIM_MapCodecStageStatus(Codec_TIM_StageAutoReload(&arrRegImage, autoReload)));
	TIM_WriteARRIfChanged(TIMx, currentArrRegImage, arrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetCounterValue
(
	TIM_TypeDef* const					TIMx,
	timer_counter_value_t* const			pCounterValue
)
{
	if (pCounterValue == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	return Codec_TIM_ExtractCounterValue(LL_TIM_ReadCNT(TIMx), pCounterValue);
}

driver_status_t TIM_SetCounterValue
(
	TIM_TypeDef* const						TIMx,
	const timer_counter_value_t				counterValue
)
{
	reg cntRegImage = 0x00000000UL;
	reg currentCntRegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	cntRegImage = LL_TIM_ReadCNT(TIMx);
	currentCntRegImage = cntRegImage;

	ASSERT_DRIVER_STATUS(TIM_MapCodecStageStatus(Codec_TIM_StageCounterValue(&cntRegImage, counterValue)));
	TIM_WriteCNTIfChanged(TIMx, currentCntRegImage, cntRegImage);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Counter Field APIs										//
// ==================================================================================================== //

driver_status_t TIM_GetDirection
(
	TIM_TypeDef* const				TIMx,
	timer_direction_t* const		pDirection
)
{
	if (pDirection == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	return TIM_MapCodecExtractStatus(Codec_TIM_ExtractCounterDirection(LL_TIM_ReadCR1(TIMx), pDirection));
}

driver_status_t TIM_SetDirection
(
	TIM_TypeDef* const				TIMx,
	const timer_direction_t			direction
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_ValidateDirection(direction));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	ASSERT_DRIVER_STATUS(TIM_MapCodecStageStatus(Codec_TIM_StageCounterDirection(&cr1RegImage, direction)));
	TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetAlignment
(
	TIM_TypeDef* const				TIMx,
	timer_count_mode_t* const		pAlignment
)
{
	if (pAlignment == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	return TIM_MapCodecExtractStatus(Codec_TIM_ExtractCounterAlignment(LL_TIM_ReadCR1(TIMx), pAlignment));
}

driver_status_t TIM_SetAlignment
(
	TIM_TypeDef* const					TIMx,
	const timer_count_mode_t				alignment
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_ValidateAlignment(alignment));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	ASSERT_DRIVER_STATUS(TIM_MapCodecStageStatus(Codec_TIM_StageCounterAlignment(&cr1RegImage, alignment)));
	TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetOnePulse
(
	TIM_TypeDef* const			TIMx,
	timer_opm_t* const			pOnePulse
)
{
	if (pOnePulse == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	return TIM_MapCodecExtractStatus(Codec_TIM_ExtractOnePulse(LL_TIM_ReadCR1(TIMx), pOnePulse));
}

driver_status_t TIM_SetOnePulse
(
	TIM_TypeDef* const			TIMx,
	const timer_opm_t			onePulse
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_ValidateOnePulse(onePulse));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	ASSERT_DRIVER_STATUS(TIM_MapCodecStageStatus(Codec_TIM_StageOnePulse(&cr1RegImage, onePulse)));
	TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetAutoReloadPreload
(
	TIM_TypeDef* const			TIMx,
	timer_arpe_t* const			pAutoReloadPreload
)
{
	if (pAutoReloadPreload == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	return TIM_MapCodecExtractStatus(Codec_TIM_ExtractAutoReloadPreload(LL_TIM_ReadCR1(TIMx), pAutoReloadPreload));
}

driver_status_t TIM_SetAutoReloadPreload
(
	TIM_TypeDef* const			TIMx,
	const timer_arpe_t			autoReloadPreload
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_ValidateAutoReloadPreload(autoReloadPreload));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	ASSERT_DRIVER_STATUS(TIM_MapCodecStageStatus(Codec_TIM_StageAutoReloadPreload(&cr1RegImage, autoReloadPreload)));
	TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetUpdateSource
(
	TIM_TypeDef* const				TIMx,
	timer_update_source_t* const	pUpdateSource
)
{
	if (pUpdateSource == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	return TIM_MapCodecExtractStatus(Codec_TIM_ExtractUpdateSource(LL_TIM_ReadCR1(TIMx), pUpdateSource));
}

driver_status_t TIM_SetUpdateSource
(
	TIM_TypeDef* const					TIMx,
	const timer_update_source_t			updateSource
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_ValidateUpdateSource(updateSource));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	ASSERT_DRIVER_STATUS(TIM_MapCodecStageStatus(Codec_TIM_StageUpdateSource(&cr1RegImage, updateSource)));
	TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetClockDivision
(
	TIM_TypeDef* const					TIMx,
	timer_clock_division_t* const		pClockDivision
)
{
	if (pClockDivision == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	return TIM_MapCodecExtractStatus(Codec_TIM_ExtractClockDivision(LL_TIM_ReadCR1(TIMx), pClockDivision));
}

driver_status_t TIM_SetClockDivision
(
	TIM_TypeDef* const						TIMx,
	const timer_clock_division_t				clockDivision
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_ValidateClockDivision(clockDivision));
	ASSERT_DRIVER_STATUS(TIM_EnableClock(TIMx));

	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	ASSERT_DRIVER_STATUS(TIM_MapCodecStageStatus(Codec_TIM_StageClockDivision(&cr1RegImage, clockDivision)));
	TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage);

	return DRIVER_STATUS_SUCCESS;
}
