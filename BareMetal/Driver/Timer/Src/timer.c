/**
 * @file	timer.c
 * @author	Shrey Shah
 * @brief	Timer Driver Implementation
 * @version	v1.0
 * @date	20-06-2026
 *
 * @details
 * This source file implements the public Timer driver API declared in
 * @ref `timer.h`. The driver layer owns public validation, Timer clock-state
 * orchestration, register-image reads, codec staging/extraction orchestration,
 * dirty writes, and public @ref `driver_status_t` handling.
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
#define TIM_DRIVER_RESET_ARR						((timer_auto_reload_t) 0xFFFFU)
/** @brief Reset-equivalent Timer counter value @def TIM_DRIVER_RESET_CNT */
#define TIM_DRIVER_RESET_CNT						((timer_counter_value_t) 0U)

/**
 * @brief Reset Timer configuration
 */
static const timer_config_t _TIM_ResetConfig =
{
	.timebase	=
	{
		.prescaler				= TIM_DRIVER_RESET_PSC,
		.auto_reload			= TIM_DRIVER_RESET_ARR,
		.initial_count			= TIM_DRIVER_RESET_CNT
	},
	.counter =
	{
		.direction				= TIMx_DIR_COUNT_UP,
		.alignment				= TIMx_MODE_NORMAL,
		.one_pulse				= TIMx_OPM_DISABLE,
		.auto_reload_preload	= TIMx_ARPE_DISABLE,
		.update_source			= TIMx_UPDATE_SOURCE_ANY,
		.clock_division			= TIMx_CKD_CLK_FREQ
	}
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
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateInstance(const TIM_TypeDef* const TIMx)
{
	return (TIM_INSTANCE_IS_VALID(TIMx) != 0x00U) ? DRIVER_STATUS_SUCCESS : DRIVER_STATUS_ERROR_INVALID_ARG;
}

/**
 * @brief Validates a Timer direction selector
 * @param[in] direction Timer direction selector
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p direction is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p direction is invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateDirection(const timer_direction_t direction)
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
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateAlignment(const timer_count_mode_t alignment)
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
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateOnePulse(const timer_opm_t onePulse)
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
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateAutoReloadPreload(const timer_arpe_t autoReloadPreload)
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
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateUpdateSource(const timer_update_source_t updateSource)
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
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateClockDivision(const timer_clock_division_t clockDivision)
{
	return (TIM_CLOCK_DIVISION_IS_VALID(clockDivision) != 0x00U) ? DRIVER_STATUS_SUCCESS : DRIVER_STATUS_ERROR_INVALID_ARG;
}

/**
 * @brief Validates a Timer counter configuration pointer and all public selectors
 * @param[in] pCounter Timer counter configuration
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p pCounter is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounter is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more selectors are invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateCounterConfig(const timer_config_counter_t* const pCounter)
{
	//! Validate the container before reading any grouped selector fields.
	if (pCounter == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Reuse scalar selector validators so grouped and scalar APIs share the same validation path.
	ASSERT_DRIVER_STATUS(_TIM_ValidateDirection(pCounter->direction));
	ASSERT_DRIVER_STATUS(_TIM_ValidateAlignment(pCounter->alignment));
	ASSERT_DRIVER_STATUS(_TIM_ValidateOnePulse(pCounter->one_pulse));
	ASSERT_DRIVER_STATUS(_TIM_ValidateAutoReloadPreload(pCounter->auto_reload_preload));
	ASSERT_DRIVER_STATUS(_TIM_ValidateUpdateSource(pCounter->update_source));
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockDivision(pCounter->clock_division));

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer ON/OFF state selector
 * @param[in] state Timer state selector
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p state is @ref `DRIVER_STATUS_OFF` or @ref `DRIVER_STATUS_ON`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p state is invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateState(const driver_status_t state)
{
	return ((state == DRIVER_STATUS_OFF) || (state == DRIVER_STATUS_ON)) ? DRIVER_STATUS_SUCCESS : DRIVER_STATUS_ERROR_INVALID_ARG;
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
__STATIC_FORCEINLINE driver_status_t _TIM_GetAPB1ClockMask
(
	const TIM_TypeDef* const	TIMx,
	reg* const					pClockMask
)
{
	//! Decode into a caller-owned mask so the RCC helper remains independent of Timer instances.
	if (pClockMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Match by peripheral base address because instance macros are raw memory-mapped pointers.
	switch ((uint32_t) TIMx)
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
 * @brief Validates that the Timer APB1 clock gate is enabled
 * @param[in] TIMx Timer peripheral instance
 * @returns Clock-gate validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer APB1 clock gate is enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ClockEnabled(TIM_TypeDef* const TIMx)
{
	// Local Variables
	reg clockMask = 0x00000000UL;
	driver_status_t clockState = DRIVER_STATUS_ERROR;

	// Validate Input
	if (TIMx == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_GetAPB1ClockMask(TIMx, &clockMask));

	clockState = RCC_APB1_ClockGetState(clockMask);
	if (clockState != DRIVER_STATUS_ERROR_INVALID_ARG)
	{
		clockState = (clockState == DRIVER_STATUS_ON) ? DRIVER_STATUS_SUCCESS : DRIVER_STATUS_ERROR_STATE;
	}

	return clockState;
}

// ==================================================================================================== //
//										Local Dirty Write Helpers										//
// ==================================================================================================== //

/**
 * @brief Writes `TIMx_CR1` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * @param[in] currentRegImage Current hardware `CR1` image
 * @param[in] stagedRegImage Staged `CR1` image
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `CR1` write was skipped or performed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
__STATIC_FORCEINLINE driver_status_t _TIM_WriteCR1IfChanged
(
	TIM_TypeDef* const	TIMx,
	const reg			currentRegImage,
	const reg			stagedRegImage
)
{
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Dirty-write policy avoids touching CR1 when codec staging produced the existing image.
	if (currentRegImage != stagedRegImage)
	{
		LL_TIM_WriteCR1(TIMx, stagedRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Writes `TIMx_PSC` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * @param[in] currentRegImage Current hardware `PSC` image
 * @param[in] stagedRegImage Staged `PSC` image
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `PSC` write was skipped or performed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
__STATIC_FORCEINLINE driver_status_t _TIM_WritePSCIfChanged
(
	TIM_TypeDef* const	TIMx,
	const reg			currentRegImage,
	const reg			stagedRegImage
)
{
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Dirty-write policy avoids forcing a prescaler preload update when the value is unchanged.
	if (currentRegImage != stagedRegImage)
	{
		LL_TIM_WritePSC(TIMx, stagedRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Writes `TIMx_ARR` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * @param[in] currentRegImage Current hardware `ARR` image
 * @param[in] stagedRegImage Staged `ARR` image
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `ARR` write was skipped or performed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
__STATIC_FORCEINLINE driver_status_t _TIM_WriteARRIfChanged
(
	TIM_TypeDef* const	TIMx,
	const reg			currentRegImage,
	const reg			stagedRegImage
)
{
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Dirty-write policy keeps ARR untouched unless the staged image differs from hardware.
	if (currentRegImage != stagedRegImage)
	{
		LL_TIM_WriteARR(TIMx, stagedRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Writes `TIMx_CNT` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * @param[in] currentRegImage Current hardware `CNT` image
 * @param[in] stagedRegImage Staged `CNT` image
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `CNT` write was skipped or performed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
__STATIC_FORCEINLINE driver_status_t _TIM_WriteCNTIfChanged
(
	TIM_TypeDef* const	TIMx,
	const reg			currentRegImage,
	const reg			stagedRegImage
)
{
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Dirty-write policy avoids resetting the counter when the requested count already matches.
	if (currentRegImage != stagedRegImage)
	{
		LL_TIM_WriteCNT(TIMx, stagedRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local Update Event Helpers										//
// ==================================================================================================== //

/**
 * @brief Generates one software update event
 * @param[in] TIMx Timer peripheral instance
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update event generation was requested
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
__STATIC_FORCEINLINE driver_status_t _TIM_GenerateUpdateEvent(TIM_TypeDef* const TIMx)
{
	reg egrRegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! EGR is an action register, so the driver writes a codec-staged UG image instead of read-modify-write.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateEventGeneration(&egrRegImage));
	LL_TIM_WriteEGR(TIMx, egrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Clears `TIMx_SR.UIF` when a generated update event set it
 * @param[in] TIMx Timer peripheral instance
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update flag was clear or was acknowledged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ClearUpdateFlagIfPending(TIM_TypeDef* const TIMx)
{
	reg srRegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	srRegImage = LL_TIM_ReadSR(TIMx);

	//! The update flag may or may not be set by UG depending on Timer state; avoid writing SR unless needed.
	if (Codec_TIM_ExtractUpdateFlagState(srRegImage) == DRIVER_STATUS_ON)
	{
		//! Stage write-0-to-clear semantics through the codec so the driver does not encode SR flag policy.
		ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateFlagClear(&srRegImage));
		LL_TIM_WriteSR(TIMx, srRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local TimeBase Orchestration									//
// ==================================================================================================== //

/**
 * @brief Applies a staged timebase configuration to one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[in] pTimeBase TimeBase configuration to apply
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TimeBase fields were applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx or @p pTimeBase is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ApplyTimeBaseConfig
(
	TIM_TypeDef* const						TIMx,
	const timer_config_timebase_t* const	pTimeBase
)
{
	if (pTimeBase == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Read each timebase register once, then stage all caller-requested values into local images.
	reg pscRegImage = LL_TIM_ReadPSC(TIMx);
	reg arrRegImage = LL_TIM_ReadARR(TIMx);
	reg cntRegImage = LL_TIM_ReadCNT(TIMx);
	//! Keep the original images so only modified registers are committed back to hardware.
	const reg currentPscRegImage = pscRegImage;
	const reg currentArrRegImage = arrRegImage;
	const reg currentCntRegImage = cntRegImage;

	//! Codec owns field staging; ASSERT_DRIVER_STATUS propagates codec status directly.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageTimeBaseConfig(&pscRegImage, &arrRegImage, &cntRegImage, pTimeBase));

	//! Commit the staged images after every timebase field has been prepared successfully.
	ASSERT_DRIVER_STATUS(_TIM_WritePSCIfChanged(TIMx, currentPscRegImage, pscRegImage));
	ASSERT_DRIVER_STATUS(_TIM_WriteARRIfChanged(TIMx, currentArrRegImage, arrRegImage));
	ASSERT_DRIVER_STATUS(_TIM_WriteCNTIfChanged(TIMx, currentCntRegImage, cntRegImage));

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Applies a staged counter configuration to one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[in] pCounter Counter configuration to apply
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter fields were applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx or @p pCounter is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or one or more counter fields are invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ApplyCounterConfig
(
	TIM_TypeDef* const						TIMx,
	const timer_config_counter_t* const		pCounter
)
{
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterConfig(pCounter));
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Read CR1 once because all counter-behavior fields staged here live in the same register.
	reg cr1RegImage = LL_TIM_ReadCR1(TIMx);
	//! Preserve the original CR1 image for dirty-write comparison after codec staging.
	const reg currentCr1RegImage = cr1RegImage;

	//! Codec stages only the configuration-owned CR1 fields and preserves unrelated runtime bits.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterConfig(&cr1RegImage, pCounter));

	//! Commit CR1 only after staging succeeds and only when a field actually changed.
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Applies a staged counter enable state to one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[in] counterState Counter runtime state to apply
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter runtime state was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx or @p counterState is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ApplyCounterEnableState
(
	TIM_TypeDef* const			TIMx,
	const driver_status_t		counterState
)
{
	ASSERT_DRIVER_STATUS(_TIM_ValidateState(counterState));
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Read CR1 once because counter enable state is represented by the runtime CEN bit.
	reg cr1RegImage = LL_TIM_ReadCR1(TIMx);
	//! Preserve the original CR1 image so enable/disable APIs avoid redundant CR1 writes.
	const reg currentCr1RegImage = cr1RegImage;

	//! Codec stages only CR1.CEN and preserves every other counter configuration/runtime bit.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterEnableState(&cr1RegImage, counterState));

	//! Commit CR1 only after staging succeeds and only when CEN actually changed.
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Clock State APIs											//
// ==================================================================================================== //

driver_status_t TIM_GetClockState(TIM_TypeDef* const TIMx)
{
	reg clockMask = 0x00000000UL;

	//! Clock state is the RCC APB1 gate bit for this Timer instance.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_GetAPB1ClockMask(TIMx, &clockMask));
	return RCC_APB1_ClockGetState(clockMask);
}

driver_status_t TIM_SetClockState(TIM_TypeDef* const TIMx, const driver_status_t clockState)
{
	reg clockMask = 0x00000000UL;

	//! Clock state owns only the RCC APB1 gate; Timer counter start remains a separate operation state.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidateState(clockState));
	ASSERT_DRIVER_STATUS(_TIM_GetAPB1ClockMask(TIMx, &clockMask));
	return (clockState == DRIVER_STATUS_ON) ? RCC_APB1_ClockEnable(clockMask) : RCC_APB1_ClockDisable(clockMask);
}

// ==================================================================================================== //
//										Timer Operation State APIs										//
// ==================================================================================================== //

driver_status_t TIM_GetOperationState(TIM_TypeDef* const TIMx)
{
	//! Operation state is CR1.CEN; the Timer clock gate must be enabled before CR1 can be read.
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));
	return Codec_TIM_ExtractCounterEnableState(LL_TIM_ReadCR1(TIMx));
}

driver_status_t TIM_SetOperationState(TIM_TypeDef* const TIMx, const driver_status_t operationState)
{
	//! Operation state owns only CR1.CEN; it refuses to touch CR1 while the Timer clock gate is off.
	ASSERT_DRIVER_STATUS(_TIM_ValidateState(operationState));
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));
	return _TIM_ApplyCounterEnableState(TIMx, operationState);
}

// ==================================================================================================== //
//										Timer Root Configuration APIs									//
// ==================================================================================================== //

driver_status_t TIM_DeConfig(TIM_TypeDef* const TIMx)
{
	//! De-configuration first enables the clock so the Timer registers are accessible.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(TIM_SetClockState(TIMx, DRIVER_STATUS_ON));
	//! Stop the counter before restoring timing fields so deconfig does not rewrite a running timer.
	ASSERT_DRIVER_STATUS(TIM_SetOperationState(TIMx, DRIVER_STATUS_OFF));
	//! Restore only the fields owned by timer_config_t; channel, IRQ, PWM, DMA, and reset state are untouched.
	ASSERT_DRIVER_STATUS(_TIM_ApplyCounterConfig(TIMx, &(_TIM_ResetConfig.counter)));
	ASSERT_DRIVER_STATUS(_TIM_ApplyTimeBaseConfig(TIMx, &(_TIM_ResetConfig.timebase)));
	//! End de-configuration at the Timer clock gate boundary; do not issue an RCC peripheral reset.
	ASSERT_DRIVER_STATUS(TIM_SetClockState(TIMx, DRIVER_STATUS_OFF));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_Config(TIM_TypeDef* const TIMx, const timer_config_t* const pConfig)
{
	// Validate Input Configurations
	if (pConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterConfig(&(pConfig->counter)));
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));

	//! Enable Clock for Timer
	ASSERT_DRIVER_STATUS(TIM_SetClockState(TIMx, DRIVER_STATUS_ON));
	//! Disable Timer counter before applying configuration
	ASSERT_DRIVER_STATUS(TIM_SetOperationState(TIMx, DRIVER_STATUS_OFF));

	//! After the counter is stopped, read configuration registers that must be staged before UG.
	reg cr1RegImage = LL_TIM_ReadCR1(TIMx);
	reg pscRegImage = LL_TIM_ReadPSC(TIMx);
	reg arrRegImage = LL_TIM_ReadARR(TIMx);
	reg cntRegImage = 0x00000000UL;
	const reg currentCr1RegImage = cr1RegImage;
	const reg currentPscRegImage = pscRegImage;
	const reg currentArrRegImage = arrRegImage;
	const driver_status_t updateFlagStateBeforeUpdate = Codec_TIM_ExtractUpdateFlagState(LL_TIM_ReadSR(TIMx));

	//! Stage the full configuration first so partial hardware updates are avoided on codec failure.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterConfig(&cr1RegImage, &(pConfig->counter)));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageTimeBaseConfig(&pscRegImage, &arrRegImage, &cntRegImage, &(pConfig->timebase)));

	//! Apply CR1, PSC, and ARR before UG so prescaler and any preloaded ARR value can be latched together.
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));
	ASSERT_DRIVER_STATUS(_TIM_WritePSCIfChanged(TIMx, currentPscRegImage, pscRegImage));
	ASSERT_DRIVER_STATUS(_TIM_WriteARRIfChanged(TIMx, currentArrRegImage, arrRegImage));

	//! Generate one update event to transfer PSC and any preloaded ARR value into the active timer logic.
	ASSERT_DRIVER_STATUS(_TIM_GenerateUpdateEvent(TIMx));
	//! Clear UIF only when this configuration-generated UG transitioned the flag from clear to pending.
	if (updateFlagStateBeforeUpdate == DRIVER_STATUS_OFF)
	{
		ASSERT_DRIVER_STATUS(_TIM_ClearUpdateFlagIfPending(TIMx));
	}

	//! Write the requested initial counter value after UG because the update event can affect CNT.
	const reg currentCntRegImage = LL_TIM_ReadCNT(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_WriteCNTIfChanged(TIMx, currentCntRegImage, cntRegImage));

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Group Configuration APIs									//
// ==================================================================================================== //

driver_status_t TIM_GetTimeBaseConfig
(
	TIM_TypeDef* const					TIMx,
	timer_config_timebase_t* const		pTimeBase
)
{
	reg pscRegImage = 0x00000000UL;
	reg arrRegImage = 0x00000000UL;
	reg cntRegImage = 0x00000000UL;

	//! Validate the output pointer before any hardware access.
	if (pTimeBase == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Snapshot only the registers needed to extract the timebase group.
	pscRegImage = LL_TIM_ReadPSC(TIMx);
	arrRegImage = LL_TIM_ReadARR(TIMx);
	cntRegImage = LL_TIM_ReadCNT(TIMx);

	//! Decode the caller-owned register images into the public grouped structure.
	return Codec_TIM_ExtractTimeBaseConfig(pscRegImage, arrRegImage, cntRegImage, pTimeBase);
}

driver_status_t TIM_GetCounterConfig
(
	TIM_TypeDef* const					TIMx,
	timer_config_counter_t* const		pCounter
)
{
	reg cr1RegImage = 0x00000000UL;

	//! Validate the output pointer before reading CR1.
	if (pCounter == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Counter configuration is fully represented by the current CR1 image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	//! Return the codec extraction status directly.
	return Codec_TIM_ExtractCounterConfig(cr1RegImage, pCounter);
}

driver_status_t TIM_SetTimeBaseConfig
(
	TIM_TypeDef* const						TIMx,
	const timer_config_timebase_t* const	pTimeBase
)
{
	//! TimeBase scalars have no selector constraints, so only the user-supplied pointer is checked here.
	if (pTimeBase == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Reuse the shared apply path to keep batching and dirty writes consistent.
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	return _TIM_ApplyTimeBaseConfig(TIMx, pTimeBase);
}

driver_status_t TIM_SetCounterConfig
(
	TIM_TypeDef* const						TIMx,
	const timer_config_counter_t* const		pCounter
)
{
	//! Validate first, then reuse the shared CR1 apply path for staging and dirty-write behavior.
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterConfig(pCounter));
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	return _TIM_ApplyCounterConfig(TIMx, pCounter);
}

// ==================================================================================================== //
//										Timer TimeBase Field APIs										//
// ==================================================================================================== //

driver_status_t TIM_GetPrescaler
(
	TIM_TypeDef* const				TIMx,
	timer_prescaler_t* const		pPrescaler
)
{
	//! Validate the destination before touching the peripheral.
	if (pPrescaler == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! PSC is a scalar register, so extraction only needs the current PSC image.
	return Codec_TIM_ExtractPrescaler(LL_TIM_ReadPSC(TIMx), pPrescaler);
}

driver_status_t TIM_GetFrequency
(
	TIM_TypeDef* const				TIMx,
	timer_frequency_t* const		pFrequency
)
{
	timer_prescaler_t prescaler = 0U;
	timer_frequency_t timerInputClock = 0UL;

	//! Validate the output pointer before any derived-frequency calculation.
	if (pFrequency == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Reuse the public PSC getter so instance validation, clock-gate verification, and extraction stay centralized.
	ASSERT_DRIVER_STATUS(TIM_GetPrescaler(TIMx, &prescaler));

	//! General-purpose Timers are on APB1, so derive the Timer input clock from the APB1 bus state.
	timerInputClock = (timer_frequency_t) RCC_GetBusFreq(RCC_APB1_BUS);
	if (timerInputClock == 0UL)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	//! STM32F1 doubles the Timer kernel clock when the APB prescaler is not divide-by-one.
	if (RCC_GetBusPrescaler(RCC_APB1_BUS) != RCC_APB1_DIV_1)
	{
		timerInputClock <<= 1U;
	}

	//! Hardware divides the Timer input clock by PSC + 1 to produce the counter tick frequency.
	*pFrequency = (timer_frequency_t) (timerInputClock / (((timer_frequency_t) prescaler) + 1UL));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetAutoReload
(
	TIM_TypeDef* const			TIMx,
	timer_auto_reload_t* const	pAutoReload
)
{
	//! Validate the destination before touching the peripheral.
	if (pAutoReload == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! ARR is a scalar register, so extraction only needs the current ARR image.
	return Codec_TIM_ExtractAutoReload(LL_TIM_ReadARR(TIMx), pAutoReload);
}

driver_status_t TIM_GetCounterValue
(
	TIM_TypeDef* const					TIMx,
	timer_counter_value_t* const			pCounterValue
)
{
	//! Validate the destination before touching the peripheral.
	if (pCounterValue == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! CNT is a scalar register, so extraction only needs the current CNT image.
	return Codec_TIM_ExtractCounterValue(LL_TIM_ReadCNT(TIMx), pCounterValue);
}

driver_status_t TIM_SetPrescaler
(
	TIM_TypeDef* const					TIMx,
	const timer_prescaler_t				prescaler
)
{
	reg pscRegImage = 0x00000000UL;
	reg currentPscRegImage = 0x00000000UL;

	//! Verify the Timer clock gate before reading or staging the PSC register image.
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Snapshot PSC so the codec can mutate a local image and the driver can dirty-write afterward.
	pscRegImage = LL_TIM_ReadPSC(TIMx);
	currentPscRegImage = pscRegImage;

	//! Stage the requested prescaler into the local image, then write only if it changed.
	ASSERT_DRIVER_STATUS(Codec_TIM_StagePrescaler(&pscRegImage, prescaler));
	ASSERT_DRIVER_STATUS(_TIM_WritePSCIfChanged(TIMx, currentPscRegImage, pscRegImage));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_SetAutoReload
(
	TIM_TypeDef* const						TIMx,
	const timer_auto_reload_t				autoReload
)
{
	reg arrRegImage = 0x00000000UL;
	reg currentArrRegImage = 0x00000000UL;

	//! Verify the Timer clock gate before reading or staging the ARR register image.
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Snapshot ARR so the codec can mutate a local image and the driver can dirty-write afterward.
	arrRegImage = LL_TIM_ReadARR(TIMx);
	currentArrRegImage = arrRegImage;

	//! Stage the requested auto-reload value into the local image, then write only if it changed.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageAutoReload(&arrRegImage, autoReload));
	ASSERT_DRIVER_STATUS(_TIM_WriteARRIfChanged(TIMx, currentArrRegImage, arrRegImage));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_SetCounterValue
(
	TIM_TypeDef* const				TIMx,
	const timer_counter_value_t		counterValue
)
{
	reg cntRegImage = 0x00000000UL;
	reg currentCntRegImage = 0x00000000UL;

	//! Verify the Timer clock gate before reading or staging the CNT register image.
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Snapshot CNT so the codec can mutate a local image and the driver can dirty-write afterward.
	cntRegImage = LL_TIM_ReadCNT(TIMx);
	currentCntRegImage = cntRegImage;

	//! Stage the requested counter value into the local image, then write only if it changed.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterValue(&cntRegImage, counterValue));
	ASSERT_DRIVER_STATUS(_TIM_WriteCNTIfChanged(TIMx, currentCntRegImage, cntRegImage));

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
	//! Validate the destination before reading CR1.
	if (pDirection == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Direction is encoded in CR1, so extract it from the current CR1 image.
	return Codec_TIM_ExtractCounterDirection(LL_TIM_ReadCR1(TIMx), pDirection);
}

driver_status_t TIM_GetAlignment
(
	TIM_TypeDef* const				TIMx,
	timer_count_mode_t* const		pAlignment
)
{
	//! Validate the destination before reading CR1.
	if (pAlignment == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Alignment is encoded in CR1.CMS, so extract it from the current CR1 image.
	return Codec_TIM_ExtractCounterAlignment(LL_TIM_ReadCR1(TIMx), pAlignment);
}

driver_status_t TIM_GetOnePulse
(
	TIM_TypeDef* const			TIMx,
	timer_opm_t* const			pOnePulse
)
{
	//! Validate the destination before reading CR1.
	if (pOnePulse == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! One-pulse mode is encoded in CR1.OPM, so extract it from the current CR1 image.
	return Codec_TIM_ExtractOnePulse(LL_TIM_ReadCR1(TIMx), pOnePulse);
}

driver_status_t TIM_GetAutoReloadPreload
(
	TIM_TypeDef* const			TIMx,
	timer_arpe_t* const			pAutoReloadPreload
)
{
	//! Validate the destination before reading CR1.
	if (pAutoReloadPreload == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Auto-reload preload is encoded in CR1.ARPE, so extract it from the current CR1 image.
	return Codec_TIM_ExtractAutoReloadPreload(LL_TIM_ReadCR1(TIMx), pAutoReloadPreload);
}

driver_status_t TIM_GetUpdateSource
(
	TIM_TypeDef* const				TIMx,
	timer_update_source_t* const	pUpdateSource
)
{
	//! Validate the destination before reading CR1.
	if (pUpdateSource == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Update source is encoded in CR1.URS, so extract it from the current CR1 image.
	return Codec_TIM_ExtractUpdateSource(LL_TIM_ReadCR1(TIMx), pUpdateSource);
}

driver_status_t TIM_GetClockDivision
(
	TIM_TypeDef* const				TIMx,
	timer_clock_division_t* const	pClockDivision
)
{
	//! Validate the destination before reading CR1.
	if (pClockDivision == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Clock division is encoded in CR1.CKD, so extract it from the current CR1 image.
	return Codec_TIM_ExtractClockDivision(LL_TIM_ReadCR1(TIMx), pClockDivision);
}

driver_status_t TIM_SetDirection
(
	TIM_TypeDef* const		TIMx,
	const timer_direction_t	direction
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	//! Validate the public selector and verify the Timer clock gate before staging CR1.
	ASSERT_DRIVER_STATUS(_TIM_ValidateDirection(direction));
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Snapshot CR1 so only the direction field is changed in a local image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	//! Stage the direction selector and preserve unrelated CR1 fields through dirty-write commit.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterDirection(&cr1RegImage, direction));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_SetAlignment
(
	TIM_TypeDef* const			TIMx,
	const timer_count_mode_t	alignment
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	//! Validate the public selector and verify the Timer clock gate before staging CR1.
	ASSERT_DRIVER_STATUS(_TIM_ValidateAlignment(alignment));
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Snapshot CR1 so only the alignment field is changed in a local image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	//! Stage the alignment selector and preserve unrelated CR1 fields through dirty-write commit.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterAlignment(&cr1RegImage, alignment));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_SetOnePulse
(
	TIM_TypeDef* const	TIMx,
	const timer_opm_t	onePulse
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	//! Validate the public selector and verify the Timer clock gate before staging CR1.
	ASSERT_DRIVER_STATUS(_TIM_ValidateOnePulse(onePulse));
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Snapshot CR1 so only the one-pulse field is changed in a local image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	//! Stage the one-pulse selector and preserve unrelated CR1 fields through dirty-write commit.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageOnePulse(&cr1RegImage, onePulse));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_SetAutoReloadPreload
(
	TIM_TypeDef* const	TIMx,
	const timer_arpe_t	autoReloadPreload
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	//! Validate the public selector and verify the Timer clock gate before staging CR1.
	ASSERT_DRIVER_STATUS(_TIM_ValidateAutoReloadPreload(autoReloadPreload));
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Snapshot CR1 so only the auto-reload preload field is changed in a local image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	//! Stage the preload selector and preserve unrelated CR1 fields through dirty-write commit.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageAutoReloadPreload(&cr1RegImage, autoReloadPreload));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_SetUpdateSource
(
	TIM_TypeDef* const			TIMx,
	const timer_update_source_t	updateSource
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	//! Validate the public selector and verify the Timer clock gate before staging CR1.
	ASSERT_DRIVER_STATUS(_TIM_ValidateUpdateSource(updateSource));
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Snapshot CR1 so only the update-source field is changed in a local image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	//! Stage the update-source selector and preserve unrelated CR1 fields through dirty-write commit.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateSource(&cr1RegImage, updateSource));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_SetClockDivision
(
	TIM_TypeDef* const				TIMx,
	const timer_clock_division_t	clockDivision
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	//! Validate the public selector and verify the Timer clock gate before staging CR1.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockDivision(clockDivision));
	ASSERT_DRIVER_STATUS(_TIM_ClockEnabled(TIMx));

	//! Snapshot CR1 so only the clock-division field is changed in a local image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	//! Stage the clock-division selector and preserve unrelated CR1 fields through dirty-write commit.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageClockDivision(&cr1RegImage, clockDivision));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));

	return DRIVER_STATUS_SUCCESS;
}
