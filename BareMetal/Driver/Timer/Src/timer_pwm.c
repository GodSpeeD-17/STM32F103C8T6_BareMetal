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
	//! Output-state batching accepts any non-empty subset of the four channels.
	if (TIM_CHANNEL_MASK_IS_VALID(channelMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer PWM mode selector
 * @param[in] mode Timer PWM mode selector
 * @returns @ref driver_status_t "PWM-mode validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p mode is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mode is not PWM mode 1 or PWM mode 2
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ValidateMode(const tim_channel_mode_t mode)
{
	//! Restrict the public PWM surface to hardware PWM modes 1 and 2.
	if (TIM_PWM_MODE_IS_VALID(mode) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer PWM duty-cycle value
 * @param[in] dutyCycle PWM duty cycle in permille units
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
 * @brief Validates a Timer ON/OFF state selector
 * @param[in] state Timer state selector
 * @returns @ref driver_status_t "Binary-state validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p state is @ref `DRIVER_STATUS_OFF` or @ref `DRIVER_STATUS_ON`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p state is invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ValidateState(const driver_status_t state)
{
	//! Public output-state mutation accepts only OFF and ON.
	if ((state != DRIVER_STATUS_OFF) && (state != DRIVER_STATUS_ON))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//									Local Register Selection									//
// ==================================================================================================== //

/**
 * @brief Reads the CCMR image containing one Timer channel
 * @param[in] TIMx Validated Timer peripheral instance
 * @param[in] channel Valid Timer single-channel selector
 * @returns The `CCMR1` or `CCMR2` image containing @p channel
 * @pre @p TIMx and @p channel are validated before this helper is called
 */
__STATIC_FORCEINLINE reg _TIM_PWM_ReadCCMR
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
 * @brief Writes the selected CCMR only when its staged image changed
 * @param[in] TIMx Validated Timer peripheral instance
 * @param[in] channel Valid Timer single-channel selector
 * @param[in] currentImage Current `CCMR1` or `CCMR2` image
 * @param[in] stagedImage Staged `CCMR1` or `CCMR2` image
 * @returns Nothing
 * @pre @p TIMx and @p channel are validated before this helper is called
 */
__STATIC_FORCEINLINE void _TIM_PWM_WriteCCMRIfChanged
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
 * @brief Reads the CCR selected by one Timer channel
 * @param[in] TIMx Validated Timer peripheral instance
 * @param[in] channel Valid Timer single-channel selector
 * @returns The selected `CCRx` register image
 * @pre @p channel is configured for output compare before this helper is called
 * @warning Reading an input-capture `CCRx` can consume capture-notification state
 */
__STATIC_FORCEINLINE reg _TIM_PWM_ReadCCR
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
 * @brief Writes the CCR selected by one Timer channel
 * @param[in] TIMx Validated Timer peripheral instance
 * @param[in] channel Valid Timer single-channel selector
 * @param[in] regImage Output-compare `CCRx` image to write
 * @returns Nothing
 * @pre @p channel is configured for output compare before this helper is called
 */
__STATIC_FORCEINLINE void _TIM_PWM_WriteCCR
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
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ValidateBaseImages
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
 * @param[out] pMode Optional destination for the decoded PWM mode
 * @param[out] pPolarity Optional destination for the decoded output polarity
 * @returns @ref driver_status_t "PWM configuration extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The channel PWM configuration is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The channel is not configured for the supported PWM shape
 * @pre @p channel is validated before this helper is called
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ExtractChannelConfig
(
	const reg						ccmrRegImage,
	const reg						ccerRegImage,
	const tim_channel_t			channel,
	tim_channel_mode_t* const		pMode,
	tim_channel_polarity_t* const	pPolarity
)
{
	tim_channel_oc_clear_t outputCompareClear = TIMx_CHANNEL_OC_CLEAR_DISABLE;
	tim_channel_mode_t outputCompareMode = TIMx_CHANNEL_MODE_FREEZE;
	tim_channel_oc_preload_t outputComparePreload = TIMx_CHANNEL_OC_PRELOAD_DISABLE;
	tim_channel_oc_fast_t outputCompareFast = TIMx_CHANNEL_OC_FAST_DISABLE;
	tim_channel_polarity_t polarity = TIMx_CHANNEL_POLARITY_HIGH;

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
	if (Codec_TIM_ExtractChannelPolarity(ccerRegImage, channel, &polarity) != DRIVER_STATUS_SUCCESS)
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
	if (pMode != NULL)
	{
		*pMode = outputCompareMode;
	}
	if (pPolarity != NULL)
	{
		*pPolarity = polarity;
	}
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Computes one mode-correct CCR value with round-half-up duty arithmetic
 * @param[in] autoReload Programmed Timer auto-reload value
 * @param[in] mode Timer PWM mode selector
 * @param[in] dutyCycle Requested PWM duty cycle in permille units
 * @param[out] pCompareValue Destination for the computed 16-bit compare value
 * @returns @ref driver_status_t "PWM compare-value calculation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The compare value was calculated
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCompareValue is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p autoReload, @p mode, or @p dutyCycle is invalid
 * @note The calculation uses 64-bit intermediates and performs no MMIO
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ComputeCompareValue
(
	const tim_auto_reload_t		autoReload,
	const tim_channel_mode_t		mode,
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
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateMode(mode));
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
	if (mode == TIMx_CHANNEL_MODE_PWM1)
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
 * @param[in] mode Timer PWM mode selector
 * @param[in] compareValue Programmed Timer output-compare value
 * @param[out] pDutyCycle Destination for achieved duty in permille units
 * @returns @ref driver_status_t "PWM duty-cycle calculation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The achieved duty cycle was calculated
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDutyCycle is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p autoReload, @p mode, or @p compareValue is invalid
 * @note The calculation uses 64-bit intermediates and performs no MMIO
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PWM_ComputeDutyCycle
(
	const tim_auto_reload_t		autoReload,
	const tim_channel_mode_t		mode,
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
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateMode(mode));
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
	if (mode == TIMx_CHANNEL_MODE_PWM1)
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

driver_status_t TIM_ConfigPWM
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channel,
	const tim_channel_mode_t		mode,
	const tim_channel_polarity_t	polarity
)
{
	reg cr1RegImage = 0x00000000UL;
	reg arrRegImage = 0x00000000UL;
	reg cntRegImage = 0x00000000UL;
	reg ccmrRegImage = 0x00000000UL;
	reg directCcmrRegImage = 0x00000000UL;
	reg stagedCcmrRegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	reg stagedCcerRegImage = 0x00000000UL;
	reg stagedCcrRegImage = 0x00000000UL;
	tim_auto_reload_t autoReload = 0U;
	tim_counter_value_t counterValue = 0U;
	tim_compare_value_t compareValue = 0U;
	driver_status_t counterState = DRIVER_STATUS_ERROR;
	driver_status_t channelState = DRIVER_STATUS_ERROR;

	//! Complete argument validation precedes Timer MMIO.
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannel(channel));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateMode(mode));
	if (TIM_CHANNEL_POLARITY_IS_VALID(polarity) == 0x00U)
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
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateBaseImages(cr1RegImage, arrRegImage));
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

	//! Require the selected output disabled and snapshot only its owned channel images.
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	channelState = Codec_TIM_ExtractChannelEnableState(ccerRegImage, channel);
	if (channelState == DRIVER_STATUS_ON)
	{
		return DRIVER_STATUS_ERROR_BUSY;
	}
	if (channelState != DRIVER_STATUS_OFF)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	ccmrRegImage = _TIM_PWM_ReadCCMR(TIMx, channel);
	stagedCcmrRegImage = ccmrRegImage;
	stagedCcerRegImage = ccerRegImage;

	//! Stage the complete admitted PWM channel shape and exact mode-correct zero duty.
	ASSERT_DRIVER_STATUS
	(
		Codec_TIM_StageOutputCompareConfig
		(
			&stagedCcmrRegImage,
			channel,
			TIMx_CHANNEL_OC_CLEAR_DISABLE,
			mode,
			TIMx_CHANNEL_OC_PRELOAD_ENABLE,
			TIMx_CHANNEL_OC_FAST_DISABLE
		)
	);
	directCcmrRegImage = stagedCcmrRegImage;
	ASSERT_DRIVER_STATUS
	(
		Codec_TIM_StageOutputCompareConfig
		(
			&directCcmrRegImage,
			channel,
			TIMx_CHANNEL_OC_CLEAR_DISABLE,
			mode,
			TIMx_CHANNEL_OC_PRELOAD_DISABLE,
			TIMx_CHANNEL_OC_FAST_DISABLE
		)
	);
	ASSERT_DRIVER_STATUS(Codec_TIM_StageChannelEnableState(&stagedCcerRegImage, channel, DRIVER_STATUS_OFF));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageChannelPolarity(&stagedCcerRegImage, channel, polarity));
	ASSERT_DRIVER_STATUS
	(
		_TIM_PWM_ComputeCompareValue
		(
			autoReload,
			mode,
			TIM_PWM_DUTY_CYCLE_MIN,
			&compareValue
		)
	);
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCompareValue(&stagedCcrRegImage, compareValue));

	//! Point of no return: load the active CCR directly while the channel and counter are disabled.
	if (ccerRegImage != stagedCcerRegImage)
	{
		LL_TIM_WriteCCER(TIMx, stagedCcerRegImage);
	}
	_TIM_PWM_WriteCCMRIfChanged(TIMx, channel, ccmrRegImage, directCcmrRegImage);
	_TIM_PWM_WriteCCR(TIMx, channel, stagedCcrRegImage);
	_TIM_PWM_WriteCCMRIfChanged(TIMx, channel, directCcmrRegImage, stagedCcmrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetPWMConfig
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channel,
	tim_channel_mode_t* const		pMode,
	tim_channel_polarity_t* const	pPolarity
)
{
	reg ccmrRegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	tim_channel_mode_t mode = TIMx_CHANNEL_MODE_FREEZE;
	tim_channel_polarity_t polarity = TIMx_CHANNEL_POLARITY_HIGH;

	if ((pMode == NULL) || (pPolarity == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannel(channel));

	ccmrRegImage = _TIM_PWM_ReadCCMR(TIMx, channel);
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	ASSERT_DRIVER_STATUS
	(
		_TIM_PWM_ExtractChannelConfig
		(
			ccmrRegImage,
			ccerRegImage,
			channel,
			&mode,
			&polarity
		)
	);

	*pMode = mode;
	*pPolarity = polarity;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_DeConfigPWM
(
	TIM_TypeDef* const		TIMx,
	const tim_channel_t	channel
)
{
	reg cr1RegImage = 0x00000000UL;
	reg ccmrRegImage = 0x00000000UL;
	reg stagedCcmrRegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	reg stagedCcerRegImage = 0x00000000UL;
	reg ccrRegImage = 0x00000000UL;
	reg stagedCcrRegImage = 0x00000000UL;
	driver_status_t counterState = DRIVER_STATUS_ERROR;
	driver_status_t channelState = DRIVER_STATUS_ERROR;

	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannel(channel));

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
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	channelState = Codec_TIM_ExtractChannelEnableState(ccerRegImage, channel);
	if (channelState == DRIVER_STATUS_ON)
	{
		return DRIVER_STATUS_ERROR_BUSY;
	}
	if (channelState != DRIVER_STATUS_OFF)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	ccmrRegImage = _TIM_PWM_ReadCCMR(TIMx, channel);
	ASSERT_DRIVER_STATUS(_TIM_PWM_ExtractChannelConfig(ccmrRegImage, ccerRegImage, channel, NULL, NULL));
	ccrRegImage = _TIM_PWM_ReadCCR(TIMx, channel);
	stagedCcmrRegImage = ccmrRegImage;
	stagedCcerRegImage = ccerRegImage;
	stagedCcrRegImage = ccrRegImage;

	ASSERT_DRIVER_STATUS
	(
		Codec_TIM_StageOutputCompareConfig
		(
			&stagedCcmrRegImage,
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
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCompareValue(&stagedCcrRegImage, (tim_compare_value_t) 0U));

	//! Disable preload before clearing CCR so the stopped channel reaches reset state immediately.
	_TIM_PWM_WriteCCMRIfChanged(TIMx, channel, ccmrRegImage, stagedCcmrRegImage);
	if (ccerRegImage != stagedCcerRegImage)
	{
		LL_TIM_WriteCCER(TIMx, stagedCcerRegImage);
	}
	if (ccrRegImage != stagedCcrRegImage)
	{
		_TIM_PWM_WriteCCR(TIMx, channel, stagedCcrRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//									Timer PWM Duty-Cycle APIs									//
// ==================================================================================================== //

driver_status_t TIM_SetPWMDutyCycle
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
	tim_channel_mode_t mode = TIMx_CHANNEL_MODE_FREEZE;
	tim_auto_reload_t autoReload = 0U;
	tim_counter_value_t counterValue = 0U;
	tim_compare_value_t compareValue = 0U;
	driver_status_t counterState = DRIVER_STATUS_ERROR;
	driver_status_t channelState = DRIVER_STATUS_ERROR;

	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannel(channel));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateDutyCycle(dutyCycle));

	//! Validate the channel before reading CCR so input-capture flags cannot be consumed.
	ccmrRegImage = _TIM_PWM_ReadCCMR(TIMx, channel);
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_PWM_ExtractChannelConfig(ccmrRegImage, ccerRegImage, channel, &mode, NULL));
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	arrRegImage = LL_TIM_ReadARR(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateBaseImages(cr1RegImage, arrRegImage));
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

	ccrRegImage = _TIM_PWM_ReadCCR(TIMx, channel);
	stagedCcrRegImage = ccrRegImage;
	ASSERT_DRIVER_STATUS(_TIM_PWM_ComputeCompareValue(autoReload, mode, dutyCycle, &compareValue));
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
				mode,
				TIMx_CHANNEL_OC_PRELOAD_DISABLE,
				TIMx_CHANNEL_OC_FAST_DISABLE
			)
		);
	}

	//! A stopped update loads only the selected active CCR; a running update stages its preload.
	if (counterState == DRIVER_STATUS_OFF)
	{
		_TIM_PWM_WriteCCMRIfChanged(TIMx, channel, ccmrRegImage, directCcmrRegImage);
		_TIM_PWM_WriteCCR(TIMx, channel, stagedCcrRegImage);
		_TIM_PWM_WriteCCMRIfChanged(TIMx, channel, directCcmrRegImage, ccmrRegImage);
	}
	else if (ccrRegImage != stagedCcrRegImage)
	{
		_TIM_PWM_WriteCCR(TIMx, channel, stagedCcrRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetPWMDutyCycle
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
	tim_channel_mode_t mode = TIMx_CHANNEL_MODE_FREEZE;
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
	ccmrRegImage = _TIM_PWM_ReadCCMR(TIMx, channel);
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_PWM_ExtractChannelConfig(ccmrRegImage, ccerRegImage, channel, &mode, NULL));
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	arrRegImage = LL_TIM_ReadARR(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateBaseImages(cr1RegImage, arrRegImage));
	if (Codec_TIM_ExtractAutoReload(arrRegImage, &autoReload) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	ccrRegImage = _TIM_PWM_ReadCCR(TIMx, channel);
	if (Codec_TIM_ExtractCompareValue(ccrRegImage, &compareValue) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	ASSERT_DRIVER_STATUS(_TIM_PWM_ComputeDutyCycle(autoReload, mode, compareValue, &dutyCycle));

	*pDutyCycle = dutyCycle;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//									Timer PWM Output-State APIs									//
// ==================================================================================================== //

driver_status_t TIM_SetPWMOutputState
(
	TIM_TypeDef* const			TIMx,
	const tim_channel_t		channelMask,
	const driver_status_t		outputState
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
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateState(outputState));

	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	stagedCcerRegImage = ccerRegImage;
	if (outputState == DRIVER_STATUS_ON)
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
		if (outputState == DRIVER_STATUS_ON)
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
		ASSERT_DRIVER_STATUS(Codec_TIM_StageChannelEnableState(&stagedCcerRegImage, channel, outputState));
	}

	if (ccerRegImage != stagedCcerRegImage)
	{
		LL_TIM_WriteCCER(TIMx, stagedCcerRegImage);
	}
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetPWMOutputState
(
	TIM_TypeDef* const		TIMx,
	const tim_channel_t	channel
)
{
	reg ccmrRegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;

	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_PWM_ValidateChannel(channel));

	ccmrRegImage = _TIM_PWM_ReadCCMR(TIMx, channel);
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_PWM_ExtractChannelConfig(ccmrRegImage, ccerRegImage, channel, NULL, NULL));
	return Codec_TIM_ExtractChannelEnableState(ccerRegImage, channel);
}
