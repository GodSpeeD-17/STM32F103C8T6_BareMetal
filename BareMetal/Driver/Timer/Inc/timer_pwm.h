/**
 * @file	timer_pwm.h
 * @author	Shrey Shah
 * @brief	Timer PWM Driver Public Interface
 * @version	v1.0
 * @date	16-08-2026
 *
 * @details
 * This header exposes the PWM channel surface owned by the Timer driver.
 * Applications configure the Timer base through @ref TIM_Config first,
 * configure the required PWM channel set through this interface second, and start the
 * shared counter through @ref TIM_SetOperationState last.
 *
 * Timer PWM APIs do not query or mutate RCC state. Successful completion of
 * @ref TIM_Config is the lifecycle admission point for every subsequent PWM
 * operation, and the application must keep that Timer configuration valid.
 *
 * PWM frequency remains a Timer timebase property. GPIO mode, output speed,
 * AFIO routing, RCC clock gates, IRQ delivery, and physical-pin lifecycle
 * remain application-owned. This interface allocates no memory and stores no
 * hidden handle, endpoint, frequency, or requested-duty state.
 */

// Header Guard
#ifndef TIMER_PWM_H_
#define TIMER_PWM_H_

// ==================================================================================================== //
//												Includes											//
// ==================================================================================================== //
#include "timer.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup TIM_03_Driver
 * @{
 */

/**
 * @brief Timer PWM channel driver
 * @defgroup TIM_03_Driver_05_PWM Timer PWM Channel Driver
 * @ingroup TIM_03_Driver
 * @details
 * Owns Timer output-compare PWM mode, polarity, compare value, preload,
 * fast mode, and channel-output enable state. See @ref TIM_PWM_Peripheral_Guide for the full
 * ownership, timing, transaction, and exact-duty contracts.
 *
 * @warning These APIs provide no internal task/ISR synchronization. The
 * application must serialize every access to one Timer instance and retain
 * ownership of its shared timebase and trigger relationships. Hardware trigger
 * configuration must not start a counter during a stopped-state transaction.
 * @{
 */

// ==================================================================================================== //
//									Timer PWM Configuration APIs									//
// ==================================================================================================== //

/**
 * @brief Restores selected disabled Timer PWM channels to their channel reset state
 * @details
 * Validates and stages the complete selected channel set before the first
 * hardware write, then clears only each selected channel's CCMR lane, `CCxE`,
 * `CCxP`, and `CCRx`. Every unselected Timer channel, the Timer timebase, RCC,
 * IRQ, DMA, GPIO, AFIO, and NVIC state is preserved.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] channelMask Timer channel mask
 * Accepted values:
 * - One or more OR-combined values from @ref `TIMx_CHANNEL_1` through @ref `TIMx_CHANNEL_4`
 * @returns @ref driver_status_t "PWM-channel-set deconfiguration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every selected channel-owned state was reset
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Instance or channel mask is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: At least one selected channel is not configured for PWM
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Counter or at least one selected channel output is enabled
 * @pre Every selected channel output is disabled
 * @note A failure before the first hardware write leaves all Timer state unchanged
 */
driver_status_t TIM_DeConfigPWM(TIM_TypeDef* const TIMx, const tim_channel_t channelMask);

/**
 * @brief Gets one Timer PWM channel's complete configuration
 * @details
 * Reads the selected `CCMR` lane and `CCER`, validates the complete supported
 * PWM shape, and publishes mode, polarity, preload, and fast-mode selectors
 * only after successful extraction.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] channel Timer single-channel selector
 * Accepted values:
 * - @ref `TIMx_CHANNEL_1`: Timer channel 1
 * - @ref `TIMx_CHANNEL_2`: Timer channel 2
 * - @ref `TIMx_CHANNEL_3`: Timer channel 3
 * - @ref `TIMx_CHANNEL_4`: Timer channel 4
 * @param[out] pChannelMode Destination for the configured PWM channel mode
 * Expected values:
 * - @ref `TIMx_CHANNEL_MODE_PWM1`: PWM mode 1
 * - @ref `TIMx_CHANNEL_MODE_PWM2`: PWM mode 2
 * @param[out] pChannelPolarity Destination for the configured PWM channel polarity
 * Expected values:
 * - @ref `TIMx_CHANNEL_POLARITY_HIGH`: Active-high output
 * - @ref `TIMx_CHANNEL_POLARITY_LOW`: Active-low output
 * @param[out] pOutputComparePreload Destination for the configured output-compare preload selector
 * Expected values:
 * - @ref `TIMx_CHANNEL_OC_PRELOAD_DISABLE`: Compare writes update the active register directly
 * - @ref `TIMx_CHANNEL_OC_PRELOAD_ENABLE`: Compare writes target the preload register
 * @param[out] pOutputCompareFast Destination for the configured output-compare fast-mode selector
 * Expected values:
 * - @ref `TIMx_CHANNEL_OC_FAST_DISABLE`: Use normal output-compare response timing
 * - @ref `TIMx_CHANNEL_OC_FAST_ENABLE`: Use fast output-compare response timing
 * @returns @ref driver_status_t "PWM-channel configuration extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Complete PWM configuration was published
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An input or output pointer is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Instance or channel is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The channel does not have the admitted PWM shape
 * @note Output storage remains unchanged on failure
 */
driver_status_t TIM_GetPWMConfig
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channel,
	tim_channel_mode_t* const		pChannelMode,
	tim_channel_polarity_t* const	pChannelPolarity,
	tim_channel_oc_preload_t* const	pOutputComparePreload,
	tim_channel_oc_fast_t* const		pOutputCompareFast
);

/**
 * @brief Configures selected Timer channels for PWM operation
 * @details
 * Trusts the Timer base established by @ref TIM_Config and atomically applies
 * one PWM mode, polarity, preload policy, and fast-mode policy to every
 * selected channel while keeping output-compare clear disabled. It accesses
 * only the touched `CCMR` registers and `CCER`; it never reads or writes
 * `CR1`, `ARR`, `CNT`, or any `CCRx`, never generates a Timer-wide update
 * event, and never enables any `CCxE` or `CR1.CEN`.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] channelMask Timer channel mask
 * Accepted values:
 * - One or more OR-combined values from @ref `TIMx_CHANNEL_1` through @ref `TIMx_CHANNEL_4`
 * @param[in] channelMode Timer PWM channel-mode selector
 * Accepted values:
 * - @ref `TIMx_CHANNEL_MODE_PWM1`: PWM mode 1
 * - @ref `TIMx_CHANNEL_MODE_PWM2`: PWM mode 2
 * @param[in] channelPolarity Timer PWM channel-polarity selector
 * Accepted values:
 * - @ref `TIMx_CHANNEL_POLARITY_HIGH`: Active-high output
 * - @ref `TIMx_CHANNEL_POLARITY_LOW`: Active-low output
 * @param[in] outputComparePreload Timer PWM output-compare preload selector
 * Accepted values:
 * - @ref `TIMx_CHANNEL_OC_PRELOAD_DISABLE`: Compare writes update the active register directly
 * - @ref `TIMx_CHANNEL_OC_PRELOAD_ENABLE`: Compare writes target the preload register
 * @param[in] outputCompareFast Timer PWM output-compare fast-mode selector
 * Accepted values:
 * - @ref `TIMx_CHANNEL_OC_FAST_DISABLE`: Use normal output-compare response timing
 * - @ref `TIMx_CHANNEL_OC_FAST_ENABLE`: Use fast output-compare response timing
 * @returns @ref driver_status_t "PWM-channel-set configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every selected PWM channel was configured and remains disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Instance, channel mask, mode, polarity, preload, or fast-mode selector is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: At least one selected channel-enable state is undecodable
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: At least one selected channel output is enabled
 * @pre The application successfully completed @ref TIM_Config and has not enabled the Timer
 * @pre Every selected channel output is disabled
 * @pre The application calls @ref TIM_SetPWMDuty for every selected channel before enabling its output
 * @note GPIO and AFIO state are never read or modified
 * @note Timer PWM trusts the application to preserve the Timer base established by @ref TIM_Config
 * @note Fast mode controls the hardware trigger-to-output response; it does not change PWM frequency
 * @warning With preload disabled, a running duty update changes the active
 * compare value immediately and may alter the current PWM period
 * @note A failure before the first hardware write leaves all Timer state unchanged
 */
driver_status_t TIM_ConfigPWM
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channelMask,
	const tim_channel_mode_t		channelMode,
	const tim_channel_polarity_t	channelPolarity,
	const tim_channel_oc_preload_t	outputComparePreload,
	const tim_channel_oc_fast_t		outputCompareFast
);

// ==================================================================================================== //
//									Timer PWM Duty-Cycle APIs									//
// ==================================================================================================== //

/**
 * @brief Gets the duty represented by one Timer PWM channel's programmed state
 * @details
 * Reads the configured PWM mode, `ARR`, and selected `CCRx`, then reconstructs
 * the achieved duty in permille units. The destination is published only after
 * successful validation and calculation.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] channel Timer single-channel selector
 * Accepted values:
 * - @ref `TIMx_CHANNEL_1`: Timer channel 1
 * - @ref `TIMx_CHANNEL_2`: Timer channel 2
 * - @ref `TIMx_CHANNEL_3`: Timer channel 3
 * - @ref `TIMx_CHANNEL_4`: Timer channel 4
 * @param[out] pDutyCycle Destination for the achieved duty in permille units
 * Expected values:
 * - @ref `TIM_PWM_DUTY_CYCLE_MIN` through @ref `TIM_PWM_DUTY_CYCLE_MAX`
 * @returns @ref driver_status_t "PWM-channel duty-cycle extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Programmed duty was published
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An input or output pointer is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Instance, channel, ARR, or compare value is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Channel is not configured for PWM
 * @note While running with preload enabled, the readable programmed compare
 * may not yet be active until the next update event
 * @note Output storage remains unchanged on failure
 */
driver_status_t TIM_GetPWMDuty
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channel,
	tim_pwm_duty_cycle_t* const		pDutyCycle
);

/**
 * @brief Sets one configured Timer PWM channel's duty cycle
 * @details
 * Duty is expressed in permille units: `0` is exact 0.0 percent, `500` is
 * 50.0 percent, and `1000` is exact 100.0 percent. PWM mode 1 and mode 2 use
 * mode-correct compare equations so the value always describes time at the
 * selected active polarity. For a stopped Timer with the selected output
 * disabled, the function loads only that channel's active CCR. For a running
 * Timer, it updates the programmed preload for the next natural update event
 * when preload is enabled, or the active compare value immediately when
 * preload is disabled.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] channel Timer single-channel selector
 * Accepted values:
 * - @ref `TIMx_CHANNEL_1`: Timer channel 1
 * - @ref `TIMx_CHANNEL_2`: Timer channel 2
 * - @ref `TIMx_CHANNEL_3`: Timer channel 3
 * - @ref `TIMx_CHANNEL_4`: Timer channel 4
 * @param[in] dutyCycle Duty cycle in permille units
 * Accepted values:
 * - @ref `TIM_PWM_DUTY_CYCLE_MIN` through @ref `TIM_PWM_DUTY_CYCLE_MAX`
 * @returns @ref driver_status_t "PWM-channel duty-cycle operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Selected compare value was programmed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Instance, channel, duty, or programmed ARR is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Channel is not configured for PWM or a required register field is undecodable
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: A stopped Timer still has the selected channel output enabled
 * @pre Disable the selected channel output before changing its stopped-state duty
 * @note The stopped path temporarily bypasses only an enabled selected-lane
 * CCR preload, writes its active compare value, and restores the configured
 * preload state before return
 */
driver_status_t TIM_SetPWMDuty
(
	TIM_TypeDef* const			TIMx,
	const tim_channel_t			channel,
	const tim_pwm_duty_cycle_t	dutyCycle
);

// ==================================================================================================== //
//								Timer PWM Output-Enable-State APIs								//
// ==================================================================================================== //

/**
 * @brief Gets one Timer PWM channel's output-enable state
 * @details
 * Validates the complete selected PWM shape before returning `CCxE` state.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] channel Timer single-channel selector
 * Accepted values:
 * - @ref `TIMx_CHANNEL_1`: Timer channel 1
 * - @ref `TIMx_CHANNEL_2`: Timer channel 2
 * - @ref `TIMx_CHANNEL_3`: Timer channel 3
 * - @ref `TIMx_CHANNEL_4`: Timer channel 4
 * @returns @ref driver_status_t "PWM-channel output-enable-state query status"
 * @retval - @ref `DRIVER_STATUS_OFF`: Selected channel output is disabled
 * @retval - @ref `DRIVER_STATUS_ON`: Selected channel output is enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Instance or channel is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Channel is not configured for PWM
 */
driver_status_t TIM_GetPWMOutputEnable(TIM_TypeDef* const TIMx, const tim_channel_t channel);

/**
 * @brief Sets the output-enable state of one or more Timer PWM channels
 * @details
 * Stages all selected `CCxE` fields into one `CCER` image and writes `CCER` at
 * most once. Enabling validates the admitted PWM shape of every selected lane.
 * Disabling remains available as a safe cleanup operation. `CR1.CEN` is never
 * changed.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] channelMask Non-empty Timer channel mask
 * Accepted values:
 * - Any non-empty combination of @ref `TIMx_CHANNEL_1` through @ref `TIMx_CHANNEL_4`
 * @param[in] outputEnableState Requested PWM channel output-enable state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable selected channel outputs
 * - @ref `DRIVER_STATUS_ON`: Enable selected channel outputs
 * @returns @ref driver_status_t "PWM-channel output-enable-state operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Selected `CCxE` fields were updated coherently
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Instance, channel mask, or output-enable state is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: An enabled lane is not configured for PWM
 * @pre Before enabling, the application successfully called @ref TIM_SetPWMDuty for every selected channel
 */
driver_status_t TIM_SetPWMOutputEnable
(
	TIM_TypeDef* const			TIMx,
	const tim_channel_t			channelMask,
	const driver_status_t		outputEnableState
);

/** @} */ // TIM_03_Driver_05_PWM

/** @} */ // TIM_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_PWM_H_ */
