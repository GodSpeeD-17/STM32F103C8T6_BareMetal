/**
 * @file	timer_pwm.c
 * @author	Shrey Shah
 * @brief	Timer PWM Driver Implementation
 * @version	v1.0
 * @date	16-08-2026
 *
 * @details
 * Implements the Timer-owned PWM channel surface declared by
 * `timer_pwm.h`. The Driver owns validation, Timer register snapshots,
 * transaction sequencing, duty arithmetic, and dirty writes. The existing
 * Timer Codec owns field extraction/staging, while Timer LL owns named MMIO.
 * GPIO, AFIO, RCC clock-gate query/mutation, Timer frequency, and `CR1.CEN`
 * remain outside this source file's ownership. A successful @ref TIM_Config
 * call is the PWM subdomain's Timer-lifecycle prerequisite.
 */

// ==================================================================================================== //
//												Includes											//
// ==================================================================================================== //
#include "timer_pwm.h"
#include "timer_codec.h"
#include "timer_ll.h"

// ==================================================================================================== //
//									Local Validation Helpers									//
// ==================================================================================================== //

/**
 * @brief Validates a Timer peripheral instance pointer
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @returns @ref driver_status_t "Timer-instance validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p TIMx is supported
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is unsupported
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ValidateInstance(const TIM_TypeDef* const TIMx)
{
	//! Reject a null pointer before evaluating the supported-instance policy.
	if (TIMx == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Keep Timer PWM instance validation aligned with the Timer driver policy.
	if (TIM_INSTANCE_IS_VALID(TIMx) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer single-channel selector
 * @param[in] channel Timer single-channel selector
 * @returns @ref driver_status_t "Channel validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p channel selects one supported channel
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is empty, selects multiple channels, or contains unsupported bits
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ValidateChannel(const tim_channel_t channel)
{
	//! Require exactly one channel for every per-channel operation.
	if (TIM_CHANNEL_MASK_HAS_ONLY_ONE_VALID_CHANNEL(channel) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a non-empty Timer channel mask
 * @param[in] channelMask Timer channel mask
 * @returns @ref driver_status_t "Channel-mask validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p channelMask selects one or more supported channels
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channelMask is empty or contains unsupported bits
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ValidateChannelMask(const tim_channel_t channelMask)
{
	//! Multi-channel operations accept any non-empty subset of the four channels.
	if (TIM_CHANNEL_MASK_IS_VALID(channelMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer PWM channel-mode selector
 * @param[in] channelMode Timer PWM channel-mode selector
 * Accepted values:
 * - @ref `TIMx_CHANNEL_MODE_PWM1`: PWM mode 1
 * - @ref `TIMx_CHANNEL_MODE_PWM2`: PWM mode 2
 * @returns @ref driver_status_t "PWM-channel-mode validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p channelMode is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channelMode is not PWM mode 1 or PWM mode 2
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ValidateChannelMode(const tim_channel_mode_t channelMode)
{
	//! Restrict the public PWM surface to hardware PWM modes 1 and 2.
	if (TIM_PWM_MODE_IS_VALID(channelMode) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer PWM duty-cycle value
 * @param[in] dutyCycle PWM duty cycle in permille units
 * Accepted values:
 * - @ref `TIM_PWM_DUTY_CYCLE_MIN` through @ref `TIM_PWM_DUTY_CYCLE_MAX`
 * @returns @ref driver_status_t "PWM duty-cycle validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p dutyCycle is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p dutyCycle is outside `0U..1000U`
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ValidateDutyCycle(const tim_pwm_duty_cycle_t dutyCycle)
{
	//! Validate the public permille range before any compare arithmetic.
	if (TIM_PWM_DUTY_CYCLE_IS_VALID(dutyCycle) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer PWM channel output-enable-state selector
 * @param[in] outputEnableState Requested Timer PWM channel output-enable state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable the selected PWM channel output
 * - @ref `DRIVER_STATUS_ON`: Enable the selected PWM channel output
 * @returns @ref driver_status_t "PWM-channel output-enable-state validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p outputEnableState is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p outputEnableState is invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ValidateOutputEnableState(const driver_status_t outputEnableState)
{
	//! Public output-enable-state mutation accepts only OFF and ON.
	if ((outputEnableState != DRIVER_STATUS_OFF) && (outputEnableState != DRIVER_STATUS_ON))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//									Local Register Selection									//
// ==================================================================================================== //

/**
 * @brief Reads the capture/compare mode register containing one Timer channel
 * @param[in] TIMx Validated Timer peripheral instance
 * @param[in] channel Valid Timer single-channel selector
 * @returns The `CCMR1` or `CCMR2` image containing @p channel
 * @pre @p TIMx and @p channel are validated before this helper is called
 */
__STATIC_FORCEINLINE reg _TIM_PWM_ReadCaptureCompareModeRegister
(
	const TIM_TypeDef* const	TIMx,
	const tim_channel_t		channel
)
{
	//! Channels 1/2 share CCMR1 while channels 3/4 share CCMR2.
	if ((((uint32_t) channel) & ((uint32_t) (TIMx_CHANNEL_1 | TIMx_CHANNEL_2))) != 0x00000000UL)
	{
		return LL_TIM_ReadCCMR1(TIMx);
	}

	return LL_TIM_ReadCCMR2(TIMx);
}

/**
 * @brief Writes the selected capture/compare mode register only when its staged image changed
 * @param[in] TIMx Validated Timer peripheral instance
 * @param[in] channel Valid Timer single-channel selector
 * @param[in] currentImage Current `CCMR1` or `CCMR2` image
 * @param[in] stagedImage Staged `CCMR1` or `CCMR2` image
 * @returns Nothing
 * @pre @p TIMx and @p channel are validated before this helper is called
 */
__STATIC_FORCEINLINE void _TIM_PWM_WriteCaptureCompareModeRegisterIfChanged
(
	TIM_TypeDef* const		TIMx,
	const tim_channel_t	channel,
	const reg				currentImage,
	const reg				stagedImage
)
{
	//! Skip the MMIO write when staging preserved the complete register image.
	if (currentImage == stagedImage)
	{
		return;
	}

	//! Commit the complete shared CCMR image selected by the validated channel.
	if ((((uint32_t) channel) & ((uint32_t) (TIMx_CHANNEL_1 | TIMx_CHANNEL_2))) != 0x00000000UL)
	{
		LL_TIM_WriteCCMR1(TIMx, stagedImage);
	}
	else
	{
		LL_TIM_WriteCCMR2(TIMx, stagedImage);
	}
}

/**
 * @brief Reads the capture/compare register selected by one Timer channel
 * @param[in] TIMx Validated Timer peripheral instance
 * @param[in] channel Valid Timer single-channel selector
 * @returns The selected `CCRx` register image
 * @pre @p channel is configured for output compare before this helper is called
 * @warning Reading an input-capture `CCRx` can consume capture-notification state
 */
__STATIC_FORCEINLINE reg _TIM_PWM_ReadCaptureCompareRegister
(
	const TIM_TypeDef* const	TIMx,
	const tim_channel_t		channel
)
{
	//! Select exactly one output CCR through named LL access.
	switch (channel)
	{
		case TIMx_CHANNEL_1:
		{
			return LL_TIM_ReadCCR1(TIMx);
		}
		case TIMx_CHANNEL_2:
		{
			return LL_TIM_ReadCCR2(TIMx);
		}
		case TIMx_CHANNEL_3:
		{
			return LL_TIM_ReadCCR3(TIMx);
		}
		default:
		{
			return LL_TIM_ReadCCR4(TIMx);
		}
	}
}

/**
 * @brief Writes the capture/compare register selected by one Timer channel
 * @param[in] TIMx Validated Timer peripheral instance
 * @param[in] channel Valid Timer single-channel selector
 * @param[in] regImage Output-compare `CCRx` image to write
 * @returns Nothing
 * @pre @p channel is configured for output compare before this helper is called
 */
__STATIC_FORCEINLINE void _TIM_PWM_WriteCaptureCompareRegister
(
	TIM_TypeDef* const		TIMx,
	const tim_channel_t	channel,
	const reg				regImage
)
{
	//! Select exactly one output CCR through named LL access.
	switch (channel)
	{
		case TIMx_CHANNEL_1:
		{
			LL_TIM_WriteCCR1(TIMx, regImage);
			break;
		}
		case TIMx_CHANNEL_2:
		{
			LL_TIM_WriteCCR2(TIMx, regImage);
			break;
		}
		case TIMx_CHANNEL_3:
		{
			LL_TIM_WriteCCR3(TIMx, regImage);
			break;
		}
		default:
		{
			LL_TIM_WriteCCR4(TIMx, regImage);
			break;
		}
	}
}

// ==================================================================================================== //
//									Local PWM State Helpers									//
// ==================================================================================================== //

/**
 * @brief Validates the Timer base fields required by the admitted PWM model
 * @param[in] cr1RegImage Caller-owned `TIMx_CR1` image
 * @param[in] arrRegImage Caller-owned `TIMx_ARR` image
 * @returns @ref driver_status_t "Timer PWM base-image validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The Timer base images satisfy the PWM contract
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `ARR` is outside the exact-duty range
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: A base field is undecodable or incompatible with PWM
 * @note This helper does not validate `CR1.CEN` or `CNT`
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ValidateTimerBaseImages
(
	const reg	cr1RegImage,
	const reg	arrRegImage
)
{
	tim_config_counter_t counterConfig = { 0 };
	tim_auto_reload_t autoReload = 0U;
	driver_status_t updateEventState = DRIVER_STATUS_ERROR;

	//! Decode the complete counter configuration before applying PWM policy.
	if (Codec_TIM_ExtractCounterConfig(cr1RegImage, &counterConfig) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	updateEventState = Codec_TIM_ExtractUpdateEventState(cr1RegImage);
	if ((updateEventState != DRIVER_STATUS_OFF) && (updateEventState != DRIVER_STATUS_ON))
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	if (Codec_TIM_ExtractAutoReload(arrRegImage, &autoReload) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	if (TIM_PWM_AUTO_RELOAD_IS_VALID(autoReload) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Admit only the edge-aligned, up-counting, continuous preloaded base model.
	if
	(
		(counterConfig.alignment != TIMx_MODE_NORMAL) ||
		(counterConfig.direction != TIMx_DIR_COUNT_UP) ||
		(counterConfig.one_pulse != TIMx_OPM_DISABLE) ||
		(counterConfig.auto_reload_preload != TIMx_ARPE_ENABLE) ||
		(updateEventState != DRIVER_STATUS_ON)
	)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Extracts and validates one Timer channel PWM configuration
 * @param[in] ccmrRegImage Caller-owned `CCMR1` or `CCMR2` image containing @p channel
 * @param[in] ccerRegImage Caller-owned `CCER` image
 * @param[in] channel Valid Timer single-channel selector
 * @param[out] pChannelMode Optional destination for the decoded PWM channel mode
 * @param[out] pChannelPolarity Optional destination for the decoded PWM channel polarity
 * @returns @ref driver_status_t "PWM-channel configuration extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The channel PWM configuration is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The channel is not configured for the supported PWM shape
 * @pre @p channel is validated before this helper is called
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ExtractChannelConfig
(
	const reg						ccmrRegImage,
	const reg						ccerRegImage,
	const tim_channel_t			channel,
	tim_channel_mode_t* const		pChannelMode,
	tim_channel_polarity_t* const	pChannelPolarity
)
{
	tim_channel_oc_clear_t outputCompareClear = TIMx_CHANNEL_OC_CLEAR_DISABLE;
	tim_channel_mode_t outputCompareMode = TIMx_CHANNEL_MODE_FREEZE;
	tim_channel_oc_preload_t outputComparePreload = TIMx_CHANNEL_OC_PRELOAD_DISABLE;
	tim_channel_oc_fast_t outputCompareFast = TIMx_CHANNEL_OC_FAST_DISABLE;
	tim_channel_polarity_t channelPolarity = TIMx_CHANNEL_POLARITY_HIGH;

	//! Decode output-compare interpretation and polarity into local storage.
	if
	(
		Codec_TIM_ExtractOutputCompareConfig
		(
			ccmrRegImage,
			channel,
			&outputCompareClear,
			&outputCompareMode,
			&outputComparePreload,
			&outputCompareFast
		) != DRIVER_STATUS_SUCCESS
	)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	if (Codec_TIM_ExtractChannelPolarity(ccerRegImage, channel, &channelPolarity) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	if
	(
		(TIM_PWM_MODE_IS_VALID(outputCompareMode) == 0x00U) ||
		(outputComparePreload != TIMx_CHANNEL_OC_PRELOAD_ENABLE) ||
		(outputCompareFast != TIMx_CHANNEL_OC_FAST_DISABLE) ||
		(outputCompareClear != TIMx_CHANNEL_OC_CLEAR_DISABLE)
	)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Publish optional outputs only after the complete channel shape validates.
	if (pChannelMode != NULL)
	{
		*pChannelMode = outputCompareMode;
	}
	if (pChannelPolarity != NULL)
	{
		*pChannelPolarity = channelPolarity;
	}
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Computes one mode-correct CCR value with round-half-up duty arithmetic
 * @param[in] autoReload Programmed Timer auto-reload value
 * @param[in] channelMode Timer PWM channel-mode selector
 * @param[in] dutyCycle Requested PWM duty cycle in permille units
 * @param[out] pCompareValue Destination for the computed 16-bit compare value
 * @returns @ref driver_status_t "PWM compare-value calculation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The compare value was calculated
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCompareValue is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p autoReload, @p channelMode, or @p dutyCycle is invalid
 * @note The calculation uses 64-bit intermediates and performs no MMIO
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ComputeCompareValue
(
	const tim_auto_reload_t		autoReload,
	const tim_channel_mode_t		channelMode,
	const tim_pwm_duty_cycle_t	dutyCycle,
	tim_compare_value_t* const		pCompareValue
)
{
	uint32_t periodTicks = 0UL;
	uint32_t activeTicks = 0UL;
	uint32_t compareValue = 0UL;

	//! Complete validation before calculating or publishing a compare value.
	if (pCompareValue == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannelMode(channelMode));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateDutyCycle(dutyCycle));
	if (TIM_PWM_AUTO_RELOAD_IS_VALID(autoReload) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Use 64-bit round-half-up arithmetic before applying mode-specific placement.
	periodTicks = ((uint32_t) autoReload) + 1UL;
	activeTicks = (uint32_t)
	(
		(
			(((uint64_t) dutyCycle) * ((uint64_t) periodTicks)) +
			(((uint64_t) TIM_PWM_DUTY_CYCLE_MAX) / 2ULL)
		) /
		((uint64_t) TIM_PWM_DUTY_CYCLE_MAX)
	);
	if (channelMode == TIMx_CHANNEL_MODE_PWM1)
	{
		compareValue = activeTicks;
	}
	else
	{
		compareValue = periodTicks - activeTicks;
	}

	*pCompareValue = (tim_compare_value_t) compareValue;
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Reconstructs achieved permille duty from one admitted PWM image
 * @param[in] autoReload Programmed Timer auto-reload value
 * @param[in] channelMode Timer PWM channel-mode selector
 * @param[in] compareValue Programmed Timer output-compare value
 * @param[out] pDutyCycle Destination for achieved duty in permille units
 * @returns @ref driver_status_t "PWM duty-cycle calculation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The achieved duty cycle was calculated
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDutyCycle is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p autoReload, @p channelMode, or @p compareValue is invalid
 * @note The calculation uses 64-bit intermediates and performs no MMIO
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ComputeDutyCycle
(
	const tim_auto_reload_t		autoReload,
	const tim_channel_mode_t		channelMode,
	const tim_compare_value_t		compareValue,
	tim_pwm_duty_cycle_t* const	pDutyCycle
)
{
	uint32_t periodTicks = 0UL;
	uint32_t activeTicks = 0UL;
	uint32_t dutyCycle = 0UL;

	//! Complete validation before reconstructing or publishing duty.
	if (pDutyCycle == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannelMode(channelMode));
	if (TIM_PWM_AUTO_RELOAD_IS_VALID(autoReload) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	periodTicks = ((uint32_t) autoReload) + 1UL;
	if (((uint32_t) compareValue) > periodTicks)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Recover active ticks from the mode-specific compare placement.
	if (channelMode == TIMx_CHANNEL_MODE_PWM1)
	{
		activeTicks = (uint32_t) compareValue;
	}
	else
	{
		activeTicks = periodTicks - ((uint32_t) compareValue);
	}
	dutyCycle = (uint32_t)
	(
		(
			(((uint64_t) activeTicks) * ((uint64_t) TIM_PWM_DUTY_CYCLE_MAX)) +
			(((uint64_t) periodTicks) / 2ULL)
		) /
		((uint64_t) periodTicks)
	);

	//! Publish achieved permille duty only after the complete calculation succeeds.
	*pDutyCycle = (tim_pwm_duty_cycle_t) dutyCycle;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer PWM Configuration APIs									//
// ==================================================================================================== //

driver_status_t TIM_ConfigPWMChannels
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channelMask,
	const tim_channel_mode_t		channelMode,
	const tim_channel_polarity_t	channelPolarity
)
{
	// Local Variables
	reg cr1RegImage = 0x00000000UL;
	reg arrRegImage = 0x00000000UL;
	reg cntRegImage = 0x00000000UL;
	reg ccmr1RegImage = 0x00000000UL;
	reg ccmr2RegImage = 0x00000000UL;
	reg directCcmr1RegImage = 0x00000000UL;
	reg directCcmr2RegImage = 0x00000000UL;
	reg stagedCcmr1RegImage = 0x00000000UL;
	reg stagedCcmr2RegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	reg stagedCcerRegImage = 0x00000000UL;
	reg stagedCcrRegImage = 0x00000000UL;
	reg* pDirectCcmrRegImage = NULL;
	reg* pStagedCcmrRegImage = NULL;
	tim_auto_reload_t autoReload = 0U;
	tim_counter_value_t counterValue = 0U;
	tim_compare_value_t compareValue = 0U;
	tim_channel_t remainingChannels = channelMask;
	tim_channel_t channel = TIMx_CHANNEL_NONE;
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_FIRST;
	driver_status_t counterState = DRIVER_STATUS_ERROR;
	driver_status_t channelState = DRIVER_STATUS_ERROR;

	//! Complete argument validation precedes Timer MMIO.
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannelMask(channelMask));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannelMode(channelMode));
	if (TIM_CHANNEL_POLARITY_IS_VALID(channelPolarity) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Validate the stopped Timer base contract before staging any channel mutation.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	counterState = Codec_TIM_ExtractCounterEnableState(cr1RegImage);
	if (counterState == DRIVER_STATUS_ON)
	{
		return DRIVER_STATUS_ERROR_BUSY;
	}
	if (counterState != DRIVER_STATUS_OFF)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	arrRegImage = LL_TIM_ReadARR(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateTimerBaseImages(cr1RegImage, arrRegImage));
	cntRegImage = LL_TIM_ReadCNT(TIMx);
	if (Codec_TIM_ExtractCounterValue(cntRegImage, &counterValue) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	if (counterValue != 0U)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	if (Codec_TIM_ExtractAutoReload(arrRegImage, &autoReload) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Snapshot each shared channel register at most once before staging any mutation.
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	stagedCcerRegImage = ccerRegImage;
	if ((channelMask & (TIMx_CHANNEL_1 | TIMx_CHANNEL_2)) != TIMx_CHANNEL_NONE)
	{
		ccmr1RegImage = LL_TIM_ReadCCMR1(TIMx);
		directCcmr1RegImage = ccmr1RegImage;
		stagedCcmr1RegImage = ccmr1RegImage;
	}
	if ((channelMask & (TIMx_CHANNEL_3 | TIMx_CHANNEL_4)) != TIMx_CHANNEL_NONE)
	{
		ccmr2RegImage = LL_TIM_ReadCCMR2(TIMx);
		directCcmr2RegImage = ccmr2RegImage;
		stagedCcmr2RegImage = ccmr2RegImage;
	}

	//! Validate and stage every selected lane before any Timer register is written.
	while (remainingChannels != TIMx_CHANNEL_NONE)
	{
		channel = TIM_ChannelMaskExtractLowestChannel(remainingChannels);
		channelState = Codec_TIM_ExtractChannelEnableState(ccerRegImage, channel);
		if (channelState == DRIVER_STATUS_ON)
		{
			return DRIVER_STATUS_ERROR_BUSY;
		}
		if (channelState != DRIVER_STATUS_OFF)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		if ((channel & (TIMx_CHANNEL_1 | TIMx_CHANNEL_2)) != TIMx_CHANNEL_NONE)
		{
			pDirectCcmrRegImage = &directCcmr1RegImage;
			pStagedCcmrRegImage = &stagedCcmr1RegImage;
		}
		else
		{
			pDirectCcmrRegImage = &directCcmr2RegImage;
			pStagedCcmrRegImage = &stagedCcmr2RegImage;
		}

		ASSERT_DRIVER_STATUS
		(
			Codec_TIM_StageOutputCompareConfig
			(
				pDirectCcmrRegImage,
				channel,
				TIMx_CHANNEL_OC_CLEAR_DISABLE,
				channelMode,
				TIMx_CHANNEL_OC_PRELOAD_DISABLE,
				TIMx_CHANNEL_OC_FAST_DISABLE
			)
		);
		ASSERT_DRIVER_STATUS
		(
			Codec_TIM_StageOutputCompareConfig
			(
				pStagedCcmrRegImage,
				channel,
				TIMx_CHANNEL_OC_CLEAR_DISABLE,
				channelMode,
				TIMx_CHANNEL_OC_PRELOAD_ENABLE,
				TIMx_CHANNEL_OC_FAST_DISABLE
			)
		);
		ASSERT_DRIVER_STATUS(Codec_TIM_StageChannelEnableState(&stagedCcerRegImage, channel, DRIVER_STATUS_OFF));
		ASSERT_DRIVER_STATUS(Codec_TIM_StageChannelPolarity(&stagedCcerRegImage, channel, channelPolarity));
		ASSERT_DRIVER_STATUS(TIM_ChannelMaskRemoveChannel(&remainingChannels, channel));
	}

	//! Derive one shared mode-correct zero-duty image for every selected channel.
	ASSERT_DRIVER_STATUS
	(
		_TIM_PWM_ComputeCompareValue
		(
			autoReload,
			channelMode,
			TIM_PWM_DUTY_CYCLE_MIN,
			&compareValue
		)
	);
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCompareValue(&stagedCcrRegImage, compareValue));

	//! Point of no return: commit each shared image once and each selected CCR once.
	if (ccerRegImage != stagedCcerRegImage)
	{
		LL_TIM_WriteCCER(TIMx, stagedCcerRegImage);
	}
	if (ccmr1RegImage != directCcmr1RegImage)
	{
		LL_TIM_WriteCCMR1(TIMx, directCcmr1RegImage);
	}
	if (ccmr2RegImage != directCcmr2RegImage)
	{
		LL_TIM_WriteCCMR2(TIMx, directCcmr2RegImage);
	}
	for (channelIndex = TIM_CHANNEL_INDEX_FIRST; channelIndex < TIM_CHANNEL_COUNT; ++channelIndex)
	{
		channel = TIM_CHANNEL_INDEX_TO_MASK(channelIndex);
		if ((channelMask & channel) != TIMx_CHANNEL_NONE)
		{
			_TIM_PWM_WriteCaptureCompareRegister(TIMx, channel, stagedCcrRegImage);
		}
	}
	if (directCcmr1RegImage != stagedCcmr1RegImage)
	{
		LL_TIM_WriteCCMR1(TIMx, stagedCcmr1RegImage);
	}
	if (directCcmr2RegImage != stagedCcmr2RegImage)
	{
		LL_TIM_WriteCCMR2(TIMx, stagedCcmr2RegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetPWMChannelConfig
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channel,
	tim_channel_mode_t* const		pChannelMode,
	tim_channel_polarity_t* const	pChannelPolarity
)
{
	reg ccmrRegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	tim_channel_mode_t channelMode = TIMx_CHANNEL_MODE_FREEZE;
	tim_channel_polarity_t channelPolarity = TIMx_CHANNEL_POLARITY_HIGH;

	if ((pChannelMode == NULL) || (pChannelPolarity == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannel(channel));

	ccmrRegImage = _TIM_PWM_ReadCaptureCompareModeRegister(TIMx, channel);
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	ASSERT_DRIVER_STATUS
	(
		_TIM_PWM_ExtractChannelConfig
		(
			ccmrRegImage,
			ccerRegImage,
			channel,
			&channelMode,
			&channelPolarity
		)
	);

	*pChannelMode = channelMode;
	*pChannelPolarity = channelPolarity;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_DeConfigPWMChannels
(
	TIM_TypeDef* const		TIMx,
	const tim_channel_t	channelMask
)
{
	reg cr1RegImage = 0x00000000UL;
	reg ccmr1RegImage = 0x00000000UL;
	reg ccmr2RegImage = 0x00000000UL;
	reg stagedCcmr1RegImage = 0x00000000UL;
	reg stagedCcmr2RegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	reg stagedCcerRegImage = 0x00000000UL;
	reg ccrRegImages[TIM_CHANNEL_COUNT] = { 0x00000000UL };
	reg stagedCcrRegImages[TIM_CHANNEL_COUNT] = { 0x00000000UL };
	reg* pStagedCcmrRegImage = NULL;
	const reg* pCcmrRegImage = NULL;
	tim_channel_t remainingChannels = channelMask;
	tim_channel_t channel = TIMx_CHANNEL_NONE;
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_FIRST;
	driver_status_t counterState = DRIVER_STATUS_ERROR;
	driver_status_t channelState = DRIVER_STATUS_ERROR;

	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannelMask(channelMask));

	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	counterState = Codec_TIM_ExtractCounterEnableState(cr1RegImage);
	if (counterState == DRIVER_STATUS_ON)
	{
		return DRIVER_STATUS_ERROR_BUSY;
	}
	if (counterState != DRIVER_STATUS_OFF)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Snapshot each shared register once, then validate every selected PWM lane.
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	stagedCcerRegImage = ccerRegImage;
	if ((channelMask & (TIMx_CHANNEL_1 | TIMx_CHANNEL_2)) != TIMx_CHANNEL_NONE)
	{
		ccmr1RegImage = LL_TIM_ReadCCMR1(TIMx);
		stagedCcmr1RegImage = ccmr1RegImage;
	}
	if ((channelMask & (TIMx_CHANNEL_3 | TIMx_CHANNEL_4)) != TIMx_CHANNEL_NONE)
	{
		ccmr2RegImage = LL_TIM_ReadCCMR2(TIMx);
		stagedCcmr2RegImage = ccmr2RegImage;
	}

	while (remainingChannels != TIMx_CHANNEL_NONE)
	{
		channel = TIM_ChannelMaskExtractLowestChannel(remainingChannels);
		channelState = Codec_TIM_ExtractChannelEnableState(ccerRegImage, channel);
		if (channelState == DRIVER_STATUS_ON)
		{
			return DRIVER_STATUS_ERROR_BUSY;
		}
		if (channelState != DRIVER_STATUS_OFF)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		if ((channel & (TIMx_CHANNEL_1 | TIMx_CHANNEL_2)) != TIMx_CHANNEL_NONE)
		{
			pCcmrRegImage = &ccmr1RegImage;
			pStagedCcmrRegImage = &stagedCcmr1RegImage;
		}
		else
		{
			pCcmrRegImage = &ccmr2RegImage;
			pStagedCcmrRegImage = &stagedCcmr2RegImage;
		}

		ASSERT_DRIVER_STATUS(_TIM_PWM_ExtractChannelConfig(*pCcmrRegImage, ccerRegImage, channel, NULL, NULL));
		ASSERT_DRIVER_STATUS
		(
			Codec_TIM_StageOutputCompareConfig
			(
				pStagedCcmrRegImage,
				channel,
				TIMx_CHANNEL_OC_CLEAR_DISABLE,
				TIMx_CHANNEL_MODE_FREEZE,
				TIMx_CHANNEL_OC_PRELOAD_DISABLE,
				TIMx_CHANNEL_OC_FAST_DISABLE
			)
		);
		ASSERT_DRIVER_STATUS(Codec_TIM_StageChannelEnableState(&stagedCcerRegImage, channel, DRIVER_STATUS_OFF));
		ASSERT_DRIVER_STATUS
		(
			Codec_TIM_StageChannelPolarity
			(
				&stagedCcerRegImage,
				channel,
				TIMx_CHANNEL_POLARITY_HIGH
			)
		);
		ASSERT_DRIVER_STATUS(TIM_ChannelMaskRemoveChannel(&remainingChannels, channel));
	}

	//! Read and stage CCR reset images only after every selected lane is proven to be PWM output.
	for (channelIndex = TIM_CHANNEL_INDEX_FIRST; channelIndex < TIM_CHANNEL_COUNT; ++channelIndex)
	{
		channel = TIM_CHANNEL_INDEX_TO_MASK(channelIndex);
		if ((channelMask & channel) == TIMx_CHANNEL_NONE)
		{
			continue;
		}

		ccrRegImages[channelIndex] = _TIM_PWM_ReadCaptureCompareRegister(TIMx, channel);
		stagedCcrRegImages[channelIndex] = ccrRegImages[channelIndex];
		ASSERT_DRIVER_STATUS
		(
			Codec_TIM_StageCompareValue
			(
				&stagedCcrRegImages[channelIndex],
				(tim_compare_value_t) 0U
			)
		);
	}

	//! Point of no return: disable preload before clearing every selected active CCR.
	if (ccmr1RegImage != stagedCcmr1RegImage)
	{
		LL_TIM_WriteCCMR1(TIMx, stagedCcmr1RegImage);
	}
	if (ccmr2RegImage != stagedCcmr2RegImage)
	{
		LL_TIM_WriteCCMR2(TIMx, stagedCcmr2RegImage);
	}
	if (ccerRegImage != stagedCcerRegImage)
	{
		LL_TIM_WriteCCER(TIMx, stagedCcerRegImage);
	}
	for (channelIndex = TIM_CHANNEL_INDEX_FIRST; channelIndex < TIM_CHANNEL_COUNT; ++channelIndex)
	{
		channel = TIM_CHANNEL_INDEX_TO_MASK(channelIndex);
		if
		(
			((channelMask & channel) != TIMx_CHANNEL_NONE) &&
			(ccrRegImages[channelIndex] != stagedCcrRegImages[channelIndex])
		)
		{
			_TIM_PWM_WriteCaptureCompareRegister(TIMx, channel, stagedCcrRegImages[channelIndex]);
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//									Timer PWM Duty-Cycle APIs									//
// ==================================================================================================== //

driver_status_t TIM_SetPWMChannelDutyCycle
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channel,
	const tim_pwm_duty_cycle_t		dutyCycle
)
{
	reg cr1RegImage = 0x00000000UL;
	reg arrRegImage = 0x00000000UL;
	reg cntRegImage = 0x00000000UL;
	reg ccmrRegImage = 0x00000000UL;
	reg directCcmrRegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	reg ccrRegImage = 0x00000000UL;
	reg stagedCcrRegImage = 0x00000000UL;
	tim_channel_mode_t channelMode = TIMx_CHANNEL_MODE_FREEZE;
	tim_auto_reload_t autoReload = 0U;
	tim_counter_value_t counterValue = 0U;
	tim_compare_value_t compareValue = 0U;
	driver_status_t counterState = DRIVER_STATUS_ERROR;
	driver_status_t channelState = DRIVER_STATUS_ERROR;

	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannel(channel));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateDutyCycle(dutyCycle));

	//! Validate the channel before reading CCR so input-capture flags cannot be consumed.
	ccmrRegImage = _TIM_PWM_ReadCaptureCompareModeRegister(TIMx, channel);
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_PWM_ExtractChannelConfig(ccmrRegImage, ccerRegImage, channel, &channelMode, NULL));
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	arrRegImage = LL_TIM_ReadARR(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateTimerBaseImages(cr1RegImage, arrRegImage));
	if (Codec_TIM_ExtractAutoReload(arrRegImage, &autoReload) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	counterState = Codec_TIM_ExtractCounterEnableState(cr1RegImage);
	if ((counterState != DRIVER_STATUS_OFF) && (counterState != DRIVER_STATUS_ON))
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	if (counterState == DRIVER_STATUS_OFF)
	{
		channelState = Codec_TIM_ExtractChannelEnableState(ccerRegImage, channel);
		if (channelState == DRIVER_STATUS_ON)
		{
			return DRIVER_STATUS_ERROR_BUSY;
		}
		if (channelState != DRIVER_STATUS_OFF)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
		cntRegImage = LL_TIM_ReadCNT(TIMx);
		if (Codec_TIM_ExtractCounterValue(cntRegImage, &counterValue) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
		if (counterValue != 0U)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
	}

	ccrRegImage = _TIM_PWM_ReadCaptureCompareRegister(TIMx, channel);
	stagedCcrRegImage = ccrRegImage;
	ASSERT_DRIVER_STATUS(_TIM_PWM_ComputeCompareValue(autoReload, channelMode, dutyCycle, &compareValue));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCompareValue(&stagedCcrRegImage, compareValue));

	if (counterState == DRIVER_STATUS_OFF)
	{
		directCcmrRegImage = ccmrRegImage;
		ASSERT_DRIVER_STATUS
		(
			Codec_TIM_StageOutputCompareConfig
			(
				&directCcmrRegImage,
				channel,
				TIMx_CHANNEL_OC_CLEAR_DISABLE,
				channelMode,
				TIMx_CHANNEL_OC_PRELOAD_DISABLE,
				TIMx_CHANNEL_OC_FAST_DISABLE
			)
		);
	}

	//! A stopped update loads only the selected active CCR; a running update stages its preload.
	if (counterState == DRIVER_STATUS_OFF)
	{
		_TIM_PWM_WriteCaptureCompareModeRegisterIfChanged(TIMx, channel, ccmrRegImage, directCcmrRegImage);
		_TIM_PWM_WriteCaptureCompareRegister(TIMx, channel, stagedCcrRegImage);
		_TIM_PWM_WriteCaptureCompareModeRegisterIfChanged(TIMx, channel, directCcmrRegImage, ccmrRegImage);
	}
	else if (ccrRegImage != stagedCcrRegImage)
	{
		_TIM_PWM_WriteCaptureCompareRegister(TIMx, channel, stagedCcrRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetPWMChannelDutyCycle
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t			channel,
	tim_pwm_duty_cycle_t* const	pDutyCycle
)
{
	reg cr1RegImage = 0x00000000UL;
	reg arrRegImage = 0x00000000UL;
	reg ccmrRegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	reg ccrRegImage = 0x00000000UL;
	tim_channel_mode_t channelMode = TIMx_CHANNEL_MODE_FREEZE;
	tim_auto_reload_t autoReload = 0U;
	tim_compare_value_t compareValue = 0U;
	tim_pwm_duty_cycle_t dutyCycle = TIM_PWM_DUTY_CYCLE_MIN;

	if (pDutyCycle == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannel(channel));

	//! Establish output-compare interpretation before performing the potentially consuming CCR read.
	ccmrRegImage = _TIM_PWM_ReadCaptureCompareModeRegister(TIMx, channel);
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_PWM_ExtractChannelConfig(ccmrRegImage, ccerRegImage, channel, &channelMode, NULL));
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	arrRegImage = LL_TIM_ReadARR(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateTimerBaseImages(cr1RegImage, arrRegImage));
	if (Codec_TIM_ExtractAutoReload(arrRegImage, &autoReload) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	ccrRegImage = _TIM_PWM_ReadCaptureCompareRegister(TIMx, channel);
	if (Codec_TIM_ExtractCompareValue(ccrRegImage, &compareValue) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	ASSERT_DRIVER_STATUS(_TIM_PWM_ComputeDutyCycle(autoReload, channelMode, compareValue, &dutyCycle));

	*pDutyCycle = dutyCycle;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//								Timer PWM Output-Enable-State APIs								//
// ==================================================================================================== //

driver_status_t TIM_SetPWMChannelOutputEnableState
(
	TIM_TypeDef* const			TIMx,
	const tim_channel_t		channelMask,
	const driver_status_t		outputEnableState
)
{
	reg ccmr1RegImage = 0x00000000UL;
	reg ccmr2RegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	reg stagedCcerRegImage = 0x00000000UL;
	reg selectedCcmrRegImage = 0x00000000UL;
	tim_channel_t channel = TIMx_CHANNEL_NONE;
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_FIRST;

	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannelMask(channelMask));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateOutputEnableState(outputEnableState));

	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	stagedCcerRegImage = ccerRegImage;
	if (outputEnableState == DRIVER_STATUS_ON)
	{
		if ((((uint32_t) channelMask) & ((uint32_t) (TIMx_CHANNEL_1 | TIMx_CHANNEL_2))) != 0x00000000UL)
		{
			ccmr1RegImage = LL_TIM_ReadCCMR1(TIMx);
		}
		if ((((uint32_t) channelMask) & ((uint32_t) (TIMx_CHANNEL_3 | TIMx_CHANNEL_4))) != 0x00000000UL)
		{
			ccmr2RegImage = LL_TIM_ReadCCMR2(TIMx);
		}
	}

	//! Validate every requested enable first, then stage every CCxE into one final CCER image.
	for (channelIndex = TIM_CHANNEL_INDEX_FIRST; channelIndex < TIM_CHANNEL_COUNT; ++channelIndex)
	{
		channel = TIM_CHANNEL_INDEX_TO_MASK(channelIndex);
		if ((((uint32_t) channelMask) & ((uint32_t) channel)) == 0x00000000UL)
		{
			continue;
		}
		if (outputEnableState == DRIVER_STATUS_ON)
		{
			if ((((uint32_t) channel) & ((uint32_t) (TIMx_CHANNEL_1 | TIMx_CHANNEL_2))) != 0x00000000UL)
			{
				selectedCcmrRegImage = ccmr1RegImage;
			}
			else
			{
				selectedCcmrRegImage = ccmr2RegImage;
			}
			ASSERT_DRIVER_STATUS
			(
				_TIM_PWM_ExtractChannelConfig
				(
					selectedCcmrRegImage,
					ccerRegImage,
					channel,
					NULL,
					NULL
				)
			);
		}
		ASSERT_DRIVER_STATUS(Codec_TIM_StageChannelEnableState(&stagedCcerRegImage, channel, outputEnableState));
	}

	if (ccerRegImage != stagedCcerRegImage)
	{
		LL_TIM_WriteCCER(TIMx, stagedCcerRegImage);
	}
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetPWMChannelOutputEnableState
(
	TIM_TypeDef* const		TIMx,
	const tim_channel_t	channel
)
{
	reg ccmrRegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannel(channel));

	ccmrRegImage = _TIM_PWM_ReadCaptureCompareModeRegister(TIMx, channel);
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_PWM_ExtractChannelConfig(ccmrRegImage, ccerRegImage, channel, NULL, NULL));
	return Codec_TIM_ExtractChannelEnableState(ccerRegImage, channel);
}
