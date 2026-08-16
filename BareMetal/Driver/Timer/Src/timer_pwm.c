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
 * @brief Validates a Timer peripheral instance for PWM operations
 * @param[in] TIMx Timer peripheral instance used for PWM
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @returns @ref driver_status_t "PWM-instance validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p TIMx is supported
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is unsupported
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidatePWMInstance(const TIM_TypeDef* const TIMx)
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
 * @brief Validates a Timer PWM single-channel selector
 * @param[in] channel Timer PWM single-channel selector
 * @returns @ref driver_status_t "PWM-channel selector validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p channel selects one supported PWM channel
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is empty, selects multiple channels, or contains unsupported bits
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidatePWMChannel(const tim_channel_t channel)
{
	//! Require exactly one channel for every per-channel operation.
	if (TIM_CHANNEL_MASK_HAS_ONLY_ONE_VALID_CHANNEL(channel) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a non-empty Timer PWM channel mask
 * @param[in] channelMask Timer PWM channel mask
 * @returns @ref driver_status_t "PWM-channel-mask validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `channelMask` selects one or more supported PWM channels
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `channelMask` is empty or contains unsupported bits
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidatePWMMask(const tim_channel_t channelMask)
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
 * - @ref `TIMx_CHANNEL_MODE_PWM1`: PWM mode 1 (channel is active as long as `TIMx_CNT` < `TIMx_CCR1`)
 * - @ref `TIMx_CHANNEL_MODE_PWM2`: PWM mode 2 (channel is active as long as `TIMx_CNT` > `TIMx_CCR1`)
 * @returns @ref driver_status_t "PWM-channel-mode validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `channelMode` is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `channelMode` is not PWM mode 1 or PWM mode 2
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidatePWMMode(const tim_channel_mode_t channelMode)
{
	//! Restrict the public PWM surface to hardware PWM modes 1 and 2.
	if (TIM_PWM_MODE_IS_VALID(channelMode) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer PWM channel duty-cycle value
 * @param[in] dutyCycle Timer PWM channel duty cycle in permille units
 * Accepted values:
 * - @ref `TIM_PWM_DUTY_CYCLE_MIN` through @ref `TIM_PWM_DUTY_CYCLE_MAX`
 * @returns @ref driver_status_t "PWM-channel duty-cycle validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p dutyCycle is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p dutyCycle is outside `0U..1000U`
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidatePWMDuty(const tim_pwm_duty_cycle_t dutyCycle)
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
__STATIC_FORCEINLINE driver_status_t _TIM_ValidatePWMOutputEnable(const driver_status_t outputEnableState)
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
 * @brief Reads the capture/compare mode register containing one Timer PWM channel
 * @param[in] TIMx Validated Timer peripheral instance
 * @param[in] channel Valid Timer PWM single-channel selector
 * @returns The `CCMR1` or `CCMR2` image containing @p channel
 * @pre @p TIMx and @p channel are validated before this helper is called
 */
__STATIC_FORCEINLINE reg _TIM_ReadPWMChannelCCMR(const TIM_TypeDef* const TIMx, const tim_channel_t channel)
{
	//! Channels 1/2 share CCMR1 while channels 3/4 share CCMR2.
	if ((channel & (TIMx_CHANNEL_1 | TIMx_CHANNEL_2)) != (tim_channel_t) 0x00UL)
	{
		return LL_TIM_ReadCCMR1(TIMx);
	}

	return LL_TIM_ReadCCMR2(TIMx);
}

/**
 * @brief Writes one Timer PWM channel's capture/compare mode register when changed
 * @param[in] TIMx Validated Timer peripheral instance
 * @param[in] channel Valid Timer PWM single-channel selector
 * @param[in] currentImage Current `CCMR1` or `CCMR2` image
 * @param[in] stagedImage Staged `CCMR1` or `CCMR2` image
 * @returns Nothing
 * @pre @p TIMx and @p channel are validated before this helper is called
 */
__STATIC_FORCEINLINE void _TIM_WritePWMChannelCCMRIfChanged
(
	TIM_TypeDef* const		TIMx,
	const tim_channel_t		channel,
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
	if ((channel & (TIMx_CHANNEL_1 | TIMx_CHANNEL_2)) != (tim_channel_t) 0x00UL)
	{
		LL_TIM_WriteCCMR1(TIMx, stagedImage);
	}
	else
	{
		LL_TIM_WriteCCMR2(TIMx, stagedImage);
	}
}

/**
 * @brief Reads the capture/compare register selected by one Timer PWM channel
 * @param[in] TIMx Validated Timer peripheral instance
 * @param[in] channel Valid Timer PWM single-channel selector
 * @returns The selected `CCRx` register image
 * @pre @p channel is configured for output compare before this helper is called
 * @warning Reading an input-capture `CCRx` can consume capture-notification state
 */
__STATIC_FORCEINLINE reg _TIM_ReadPWMChannelCCR(const TIM_TypeDef* const TIMx, const tim_channel_t channel)
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
			//! Validation guarantees that the remaining selector is channel 4.
			return LL_TIM_ReadCCR4(TIMx);
		}
	}
}

/**
 * @brief Writes the capture/compare register selected by one Timer PWM channel
 * @param[in] TIMx Validated Timer peripheral instance
 * @param[in] channel Valid Timer PWM single-channel selector
 * @param[in] regImage Output-compare `CCRx` image to write
 * @returns Nothing
 * @pre @p channel is configured for output compare before this helper is called
 */
__STATIC_FORCEINLINE void _TIM_WritePWMChannelCCR(TIM_TypeDef* const TIMx, const tim_channel_t channel, const reg regImage)
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
			//! Validation guarantees that the remaining selector is channel 4.
			LL_TIM_WriteCCR4(TIMx, regImage);
			break;
		}
	}
}

// ==================================================================================================== //
//											Local PWM State Helpers										//
// ==================================================================================================== //

/**
 * @brief Extracts and validates one Timer PWM channel configuration
 * @param[in] ccmrRegImage Caller-owned `CCMR1` or `CCMR2` image containing @p channel
 * @param[in] ccerRegImage Caller-owned `CCER` image
 * @param[in] channel Valid Timer PWM single-channel selector
 * @param[out] pChannelMode Optional destination for the decoded PWM channel mode
 * Expected values:
 * - @ref `TIMx_CHANNEL_MODE_PWM1`: PWM mode 1
 * - @ref `TIMx_CHANNEL_MODE_PWM2`: PWM mode 2
 * @param[out] pChannelPolarity Optional destination for the decoded PWM channel polarity
 * Expected values:
 * - @ref `TIMx_CHANNEL_POLARITY_HIGH`: Active-high output
 * - @ref `TIMx_CHANNEL_POLARITY_LOW`: Active-low output
 * @param[out] pOutputComparePreload Optional destination for the decoded output-compare preload selector
 * Expected values:
 * - @ref `TIMx_CHANNEL_OC_PRELOAD_DISABLE`: Output-compare preload is disabled
 * - @ref `TIMx_CHANNEL_OC_PRELOAD_ENABLE`: Output-compare preload is enabled
 * @param[out] pOutputCompareFast Optional destination for the decoded output-compare fast-mode selector
 * Expected values:
 * - @ref `TIMx_CHANNEL_OC_FAST_DISABLE`: Output-compare fast mode is disabled
 * - @ref `TIMx_CHANNEL_OC_FAST_ENABLE`: Output-compare fast mode is enabled
 * @returns @ref driver_status_t "PWM-channel configuration extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The PWM channel configuration is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The channel is not configured for the supported PWM shape
 * @pre @p channel is validated before this helper is called
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ExtractPWMConfig
(
	const reg							ccmrRegImage,
	const reg							ccerRegImage,
	const tim_channel_t					channel,
	tim_channel_mode_t* const			pChannelMode,
	tim_channel_polarity_t* const		pChannelPolarity,
	tim_channel_oc_preload_t* const		pOutputComparePreload,
	tim_channel_oc_fast_t* const		pOutputCompareFast
)
{
	// Local Variables
	tim_channel_oc_clear_t outputCompareClear = TIMx_CHANNEL_OC_CLEAR_DISABLE;
	tim_channel_mode_t outputCompareMode = TIMx_CHANNEL_MODE_FREEZE;
	tim_channel_oc_preload_t outputComparePreload = TIMx_CHANNEL_OC_PRELOAD_DISABLE;
	tim_channel_oc_fast_t outputCompareFast = TIMx_CHANNEL_OC_FAST_DISABLE;
	tim_channel_polarity_t channelPolarity = TIMx_CHANNEL_POLARITY_HIGH;

	//! Decode the complete CCMR lane before accepting its PWM interpretation.
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

	//! Decode polarity separately because CCxP is owned by the shared CCER image.
	if (Codec_TIM_ExtractChannelPolarity(ccerRegImage, channel, &channelPolarity) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Admit both caller-selectable preload/fast states while keeping clear mode outside PWM scope.
	if ((TIM_PWM_MODE_IS_VALID(outputCompareMode) == 0x00U) || (outputCompareClear != TIMx_CHANNEL_OC_CLEAR_DISABLE))
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
	if (pOutputComparePreload != NULL)
	{
		*pOutputComparePreload = outputComparePreload;
	}
	if (pOutputCompareFast != NULL)
	{
		*pOutputCompareFast = outputCompareFast;
	}
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Computes one Timer PWM channel compare value with round-half-up duty arithmetic
 * @param[in] autoReload Programmed Timer auto-reload value
 * @param[in] channelMode Timer PWM channel-mode selector
 * @param[in] dutyCycle Requested Timer PWM channel duty cycle in permille units
 * @param[out] pCompareValue Destination for the computed 16-bit compare value
 * @returns @ref driver_status_t "PWM-channel compare-value calculation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The compare value was calculated
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCompareValue is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p autoReload, @p channelMode, or @p dutyCycle is invalid
 * @note The calculation uses 64-bit intermediates and performs no MMIO
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ComputePWMCompare
(
	const tim_auto_reload_t			autoReload,
	const tim_channel_mode_t		channelMode,
	const tim_pwm_duty_cycle_t		dutyCycle,
	tim_compare_value_t* const		pCompareValue
)
{
	// Local Variables
	uint32_t periodTicks = 0UL;
	uint32_t activeTicks = 0UL;
	uint32_t compareValue = 0UL;

	//! Complete validation before calculating or publishing a compare value.
	if (pCompareValue == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMMode(channelMode));
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMDuty(dutyCycle));
	if (TIM_PWM_AUTO_RELOAD_IS_VALID(autoReload) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Use 64-bit round-half-up arithmetic before applying mode-specific placement.
	periodTicks = ((uint32_t) autoReload) + 1UL;
	activeTicks = (uint32_t)(((((uint64_t) dutyCycle) * ((uint64_t) periodTicks)) + (((uint64_t) TIM_PWM_DUTY_CYCLE_MAX) / 2ULL)) / ((uint64_t) TIM_PWM_DUTY_CYCLE_MAX));

	//! PWM1 uses active ticks directly while PWM2 uses the complementary boundary.
	if (channelMode == TIMx_CHANNEL_MODE_PWM1)
	{
		compareValue = activeTicks;
	}
	else
	{
		compareValue = periodTicks - activeTicks;
	}

	//! Publish only after range validation and mode-specific placement succeed.
	*pCompareValue = (tim_compare_value_t) compareValue;
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Computes one Timer PWM channel duty cycle from its admitted register state
 * @param[in] autoReload Programmed Timer auto-reload value
 * @param[in] channelMode Timer PWM channel-mode selector
 * @param[in] compareValue Programmed Timer output-compare value
 * @param[out] pDutyCycle Destination for achieved duty in permille units
 * @returns @ref driver_status_t "PWM-channel duty-cycle calculation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The achieved duty cycle was calculated
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDutyCycle is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p autoReload, @p channelMode, or @p compareValue is invalid
 * @note The calculation uses 64-bit intermediates and performs no MMIO
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ComputePWMDuty
(
	const tim_auto_reload_t			autoReload,
	const tim_channel_mode_t		channelMode,
	const tim_compare_value_t		compareValue,
	tim_pwm_duty_cycle_t* const		pDutyCycle
)
{
	// Local Variables
	uint32_t periodTicks = 0UL;
	uint32_t activeTicks = 0UL;
	uint32_t dutyCycle = 0UL;

	//! Complete validation before reconstructing or publishing duty.
	if (pDutyCycle == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMMode(channelMode));
	if (TIM_PWM_AUTO_RELOAD_IS_VALID(autoReload) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	periodTicks = ((uint32_t) autoReload) + 1UL;

	//! Reject a compare boundary beyond the programmed PWM period.
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

	//! Convert achieved active ticks back to permille with round-half-up arithmetic.
	dutyCycle = (uint32_t)(((((uint64_t) activeTicks) * ((uint64_t) TIM_PWM_DUTY_CYCLE_MAX)) + (((uint64_t) periodTicks) / 2ULL)) /((uint64_t) periodTicks));

	//! Publish achieved permille duty only after the complete calculation succeeds.
	*pDutyCycle = (tim_pwm_duty_cycle_t) dutyCycle;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer PWM Configuration APIs									//
// ==================================================================================================== //

driver_status_t TIM_GetPWMConfig
(
	TIM_TypeDef* const					TIMx,
	const tim_channel_t					channel,
	tim_channel_mode_t* const			pChannelMode,
	tim_channel_polarity_t* const		pChannelPolarity,
	tim_channel_oc_preload_t* const		pOutputComparePreload,
	tim_channel_oc_fast_t* const		pOutputCompareFast
)
{
	// Local Variables
	reg ccmrRegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	tim_channel_mode_t channelMode = TIMx_CHANNEL_MODE_FREEZE;
	tim_channel_polarity_t channelPolarity = TIMx_CHANNEL_POLARITY_HIGH;
	tim_channel_oc_preload_t outputComparePreload = TIMx_CHANNEL_OC_PRELOAD_DISABLE;
	tim_channel_oc_fast_t outputCompareFast = TIMx_CHANNEL_OC_FAST_DISABLE;

	//! Protect every caller destination until the complete channel shape is decoded.
	if
	(
		(pChannelMode == NULL) || (pChannelPolarity == NULL) ||
		(pOutputComparePreload == NULL) || (pOutputCompareFast == NULL)
	)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Validate identity before accessing either shared Timer register.
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMChannel(channel));

	//! Snapshot the selected CCMR lane and its paired CCER state exactly once.
	ccmrRegImage = _TIM_ReadPWMChannelCCMR(TIMx, channel);
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	ASSERT_DRIVER_STATUS
	(
		_TIM_ExtractPWMConfig
		(
			ccmrRegImage,
			ccerRegImage,
			channel,
			&channelMode,
			&channelPolarity,
			&outputComparePreload,
			&outputCompareFast
		)
	);

	//! Publish the complete caller-owned PWM configuration only after extraction succeeds.
	*pChannelMode = channelMode;
	*pChannelPolarity = channelPolarity;
	*pOutputComparePreload = outputComparePreload;
	*pOutputCompareFast = outputCompareFast;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_DeConfigPWM(TIM_TypeDef* const TIMx, const tim_channel_t channelMask)
{
	// Local Variables
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

	//! Reject invalid identity and selection before Timer MMIO.
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMMask(channelMask));

	//! Require the shared counter to be stopped before resetting any channel-owned state.
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

	//! Validate every selected lane and stage its reset state before the first write.
	while (remainingChannels != TIMx_CHANNEL_NONE)
	{
		channel = TIM_ChannelMaskExtractLowestChannel(remainingChannels);

		//! A connected lane cannot be safely reset while its output remains exposed.
		channelState = Codec_TIM_ExtractChannelEnableState(ccerRegImage, channel);
		if (channelState == DRIVER_STATUS_ON)
		{
			return DRIVER_STATUS_ERROR_BUSY;
		}
		if (channelState != DRIVER_STATUS_OFF)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		//! Route the selected lane to its immutable snapshot and staged shared image.
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

		//! Prove the lane has the admitted PWM shape before resetting its channel state.
		ASSERT_DRIVER_STATUS(_TIM_ExtractPWMConfig(*pCcmrRegImage, ccerRegImage, channel, NULL, NULL, NULL, NULL));

		//! Freeze the lane with preload disabled so its active CCR can be cleared directly.
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

		//! Restore the selected lane's enable and polarity fields to their reset values.
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

		//! Retire the lane only after its complete reset image is staged successfully.
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

		ccrRegImages[channelIndex] = _TIM_ReadPWMChannelCCR(TIMx, channel);
		stagedCcrRegImages[channelIndex] = ccrRegImages[channelIndex];
		ASSERT_DRIVER_STATUS(Codec_TIM_StageCompareValue(&stagedCcrRegImages[channelIndex], (tim_compare_value_t) 0U));
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

	//! Commit all selected CCxE and CCxP reset fields through one shared CCER write.
	if (ccerRegImage != stagedCcerRegImage)
	{
		LL_TIM_WriteCCER(TIMx, stagedCcerRegImage);
	}

	//! Clear only dirty selected CCRs after their preload paths are disabled.
	for (channelIndex = TIM_CHANNEL_INDEX_FIRST; channelIndex < TIM_CHANNEL_COUNT; ++channelIndex)
	{
		channel = TIM_CHANNEL_INDEX_TO_MASK(channelIndex);
		if (((channelMask & channel) != TIMx_CHANNEL_NONE) && (ccrRegImages[channelIndex] != stagedCcrRegImages[channelIndex]))
		{
			_TIM_WritePWMChannelCCR(TIMx, channel, stagedCcrRegImages[channelIndex]);
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_ConfigPWM
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channelMask,
	const tim_channel_mode_t		channelMode,
	const tim_channel_polarity_t	channelPolarity,
	const tim_channel_oc_preload_t	outputComparePreload,
	const tim_channel_oc_fast_t		outputCompareFast
)
{
	// Local Variables
	reg ccmr1RegImage = 0x00000000UL;
	reg ccmr2RegImage = 0x00000000UL;
	reg stagedCcmr1RegImage = 0x00000000UL;
	reg stagedCcmr2RegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	reg stagedCcerRegImage = 0x00000000UL;
	reg* pStagedCcmrRegImage = NULL;
	tim_channel_t remainingChannels = channelMask;
	tim_channel_t channel = TIMx_CHANNEL_NONE;
	driver_status_t channelState = DRIVER_STATUS_ERROR;

	//! Complete argument validation precedes Timer MMIO.
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMMask(channelMask));
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMMode(channelMode));
	if (TIM_CHANNEL_POLARITY_IS_VALID(channelPolarity) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	if (TIM_CHANNEL_OC_PRELOAD_IS_VALID(outputComparePreload) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	if (TIM_CHANNEL_OC_FAST_IS_VALID(outputCompareFast) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Trust the completed Timer-base lifecycle and snapshot only PWM-owned shared registers.
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

	//! Validate and stage every selected lane before any Timer register is written.
	while (remainingChannels != TIMx_CHANNEL_NONE)
	{
		//! Resolve one lane at a time while retaining shared-register staging across the full mask.
		channel = TIM_ChannelMaskExtractLowestChannel(remainingChannels);

		//! Reject an exposed lane before changing its mode or polarity.
		channelState = Codec_TIM_ExtractChannelEnableState(ccerRegImage, channel);
		if (channelState == DRIVER_STATUS_ON)
		{
			return DRIVER_STATUS_ERROR_BUSY;
		}
		if (channelState != DRIVER_STATUS_OFF)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		//! Route the selected lane to its staged shared CCMR image.
		if ((channel & (TIMx_CHANNEL_1 | TIMx_CHANNEL_2)) != TIMx_CHANNEL_NONE)
		{
			pStagedCcmrRegImage = &stagedCcmr1RegImage;
		}
		else
		{
			pStagedCcmrRegImage = &stagedCcmr2RegImage;
		}

		//! Build the admitted PWM shape with the caller-selected preload and fast behavior.
		ASSERT_DRIVER_STATUS
		(
			Codec_TIM_StageOutputCompareConfig
			(
				pStagedCcmrRegImage,
				channel,
				TIMx_CHANNEL_OC_CLEAR_DISABLE,
				channelMode,
				outputComparePreload,
				outputCompareFast
			)
		);

		//! Keep the lane disconnected while staging its requested active polarity.
		ASSERT_DRIVER_STATUS(Codec_TIM_StageChannelEnableState(&stagedCcerRegImage, channel, DRIVER_STATUS_OFF));
		ASSERT_DRIVER_STATUS(Codec_TIM_StageChannelPolarity(&stagedCcerRegImage, channel, channelPolarity));

		//! Retire the lane only after every fallible stage for it succeeds.
		ASSERT_DRIVER_STATUS(TIM_ChannelMaskRemoveChannel(&remainingChannels, channel));
	}

	//! Point of no return: disconnect selected outputs and publish polarity before channel-mode changes.
	if (ccerRegImage != stagedCcerRegImage)
	{
		LL_TIM_WriteCCER(TIMx, stagedCcerRegImage);
	}

	//! Commit each touched shared CCMR once without reading or writing any Timer-base or CCR state.
	if (ccmr1RegImage != stagedCcmr1RegImage)
	{
		LL_TIM_WriteCCMR1(TIMx, stagedCcmr1RegImage);
	}
	if (ccmr2RegImage != stagedCcmr2RegImage)
	{
		LL_TIM_WriteCCMR2(TIMx, stagedCcmr2RegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//									Timer PWM Duty-Cycle APIs									//
// ==================================================================================================== //

driver_status_t TIM_GetPWMDuty
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channel,
	tim_pwm_duty_cycle_t* const		pDutyCycle
)
{
	// Local Variables
	reg arrRegImage = 0x00000000UL;
	reg ccmrRegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	reg ccrRegImage = 0x00000000UL;
	tim_channel_mode_t channelMode = TIMx_CHANNEL_MODE_FREEZE;
	tim_auto_reload_t autoReload = 0U;
	tim_compare_value_t compareValue = 0U;
	tim_pwm_duty_cycle_t dutyCycle = TIM_PWM_DUTY_CYCLE_MIN;

	//! Protect the caller destination until the complete duty reconstruction succeeds.
	if (pDutyCycle == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Validate identity before reading shared or channel-specific Timer state.
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMChannel(channel));

	//! Establish output-compare interpretation before performing the potentially consuming CCR read.
	ccmrRegImage = _TIM_ReadPWMChannelCCMR(TIMx, channel);
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_ExtractPWMConfig(ccmrRegImage, ccerRegImage, channel, &channelMode, NULL, NULL, NULL));

	//! Read ARR only because the programmed period is the duty denominator.
	arrRegImage = LL_TIM_ReadARR(TIMx);
	if (Codec_TIM_ExtractAutoReload(arrRegImage, &autoReload) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Decode CCR only after proving that the lane is output compare rather than capture.
	ccrRegImage = _TIM_ReadPWMChannelCCR(TIMx, channel);
	if (Codec_TIM_ExtractCompareValue(ccrRegImage, &compareValue) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	ASSERT_DRIVER_STATUS(_TIM_ComputePWMDuty(autoReload, channelMode, compareValue, &dutyCycle));

	//! Publish the reconstructed permille duty only after every decode and calculation succeeds.
	*pDutyCycle = dutyCycle;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_SetPWMDuty
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channel,
	const tim_pwm_duty_cycle_t		dutyCycle
)
{
	// Local Variables
	reg cr1RegImage = 0x00000000UL;
	reg arrRegImage = 0x00000000UL;
	reg ccmrRegImage = 0x00000000UL;
	reg directCcmrRegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	reg ccrRegImage = 0x00000000UL;
	reg stagedCcrRegImage = 0x00000000UL;
	tim_channel_mode_t channelMode = TIMx_CHANNEL_MODE_FREEZE;
	tim_channel_oc_preload_t outputComparePreload = TIMx_CHANNEL_OC_PRELOAD_DISABLE;
	tim_channel_oc_fast_t outputCompareFast = TIMx_CHANNEL_OC_FAST_DISABLE;
	tim_auto_reload_t autoReload = 0U;
	tim_compare_value_t compareValue = 0U;
	driver_status_t counterState = DRIVER_STATUS_ERROR;
	driver_status_t channelState = DRIVER_STATUS_ERROR;

	//! Reject invalid instance, channel, and duty before Timer MMIO.
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMChannel(channel));
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMDuty(dutyCycle));

	//! Validate the channel before reading CCR so input-capture flags cannot be consumed.
	ccmrRegImage = _TIM_ReadPWMChannelCCMR(TIMx, channel);
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	ASSERT_DRIVER_STATUS
	(
		_TIM_ExtractPWMConfig
		(
			ccmrRegImage,
			ccerRegImage,
			channel,
			&channelMode,
			NULL,
			&outputComparePreload,
			&outputCompareFast
		)
	);

	//! Read only the base values required for duty arithmetic and stopped/running sequencing.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	arrRegImage = LL_TIM_ReadARR(TIMx);
	if (Codec_TIM_ExtractAutoReload(arrRegImage, &autoReload) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Decode counter state so stopped writes can use the isolated direct-load contract.
	counterState = Codec_TIM_ExtractCounterEnableState(cr1RegImage);
	if ((counterState != DRIVER_STATUS_OFF) && (counterState != DRIVER_STATUS_ON))
	{
		return DRIVER_STATUS_ERROR_STATE;
	}
	if (counterState == DRIVER_STATUS_OFF)
	{
		//! A stopped active-CCR change is unsafe while the selected output remains connected.
		channelState = Codec_TIM_ExtractChannelEnableState(ccerRegImage, channel);
		if (channelState == DRIVER_STATUS_ON)
		{
			return DRIVER_STATUS_ERROR_BUSY;
		}
		if (channelState != DRIVER_STATUS_OFF)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
	}

	//! Derive and stage the mode-correct compare value only after all live-state checks pass.
	ccrRegImage = _TIM_ReadPWMChannelCCR(TIMx, channel);
	stagedCcrRegImage = ccrRegImage;
	ASSERT_DRIVER_STATUS(_TIM_ComputePWMCompare(autoReload, channelMode, dutyCycle, &compareValue));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCompareValue(&stagedCcrRegImage, compareValue));

	if (counterState == DRIVER_STATUS_OFF)
	{
		//! Bypass preload when required so the stopped write reaches the active CCR immediately.
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
				outputCompareFast
			)
		);
	}

	//! Preserve the configured preload policy after directly loading a stopped channel.
	if (counterState == DRIVER_STATUS_OFF)
	{
		_TIM_WritePWMChannelCCMRIfChanged(TIMx, channel, ccmrRegImage, directCcmrRegImage);
		_TIM_WritePWMChannelCCR(TIMx, channel, stagedCcrRegImage);
		_TIM_WritePWMChannelCCMRIfChanged(TIMx, channel, directCcmrRegImage, ccmrRegImage);
	}
	else if (ccrRegImage != stagedCcrRegImage)
	{
		//! A running write is deferred with preload enabled and immediate with preload disabled.
		_TIM_WritePWMChannelCCR(TIMx, channel, stagedCcrRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//								Timer PWM Output-Enable-State APIs								//
// ==================================================================================================== //

driver_status_t TIM_SetPWMOutputEnable
(
	TIM_TypeDef* const			TIMx,
	const tim_channel_t			channelMask,
	const driver_status_t		outputEnableState
)
{
	// Local Variables
	reg ccmr1RegImage = 0x00000000UL;
	reg ccmr2RegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;
	reg stagedCcerRegImage = 0x00000000UL;
	reg selectedCcmrRegImage = 0x00000000UL;
	tim_channel_t channel = TIMx_CHANNEL_NONE;
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_FIRST;

	//! Reject invalid identity, selection, and requested state before Timer MMIO.
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMMask(channelMask));
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMOutputEnable(outputEnableState));

	//! Preserve every unselected CCER field while staging the complete selected mask.
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	stagedCcerRegImage = ccerRegImage;

	//! Enabling requires PWM-shape proof; disabling remains safe without CCMR reads.
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
			//! Route the lane to its previously cached shared CCMR image.
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
				_TIM_ExtractPWMConfig
				(
					selectedCcmrRegImage,
					ccerRegImage,
					channel,
					NULL,
					NULL,
					NULL,
					NULL
				)
			);
		}
		ASSERT_DRIVER_STATUS(Codec_TIM_StageChannelEnableState(&stagedCcerRegImage, channel, outputEnableState));
	}

	//! Commit every selected CCxE change coherently through at most one dirty write.
	if (ccerRegImage != stagedCcerRegImage)
	{
		LL_TIM_WriteCCER(TIMx, stagedCcerRegImage);
	}
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetPWMOutputEnable
(
	TIM_TypeDef* const		TIMx,
	const tim_channel_t		channel
)
{
	// Local Variables
	reg ccmrRegImage = 0x00000000UL;
	reg ccerRegImage = 0x00000000UL;

	//! Validate identity before sampling the selected lane's shared registers.
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidatePWMChannel(channel));

	//! Prove the admitted PWM shape before interpreting the selected CCxE bit.
	ccmrRegImage = _TIM_ReadPWMChannelCCMR(TIMx, channel);
	ccerRegImage = LL_TIM_ReadCCER(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_ExtractPWMConfig(ccmrRegImage, ccerRegImage, channel, NULL, NULL, NULL, NULL));

	//! Return the decoded channel-output gate state without changing Timer state.
	return Codec_TIM_ExtractChannelEnableState(ccerRegImage, channel);
}
