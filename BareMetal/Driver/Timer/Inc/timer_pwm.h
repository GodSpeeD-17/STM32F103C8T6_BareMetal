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
 * configure each PWM channel through this interface second, and start the
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
 * Owns Timer output-compare PWM mode, polarity, compare value, preload, and
 * channel-output enable state. See @ref TIM_PWM_Peripheral_Guide for the full
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
 * @brief Configures one stopped Timer channel for PWM operation
 * @details
 * Requires an already-configured, stopped, edge-aligned, up-counting Timer
 * with auto-reload preload and update events enabled. The function configures
 * output compare, disables fast/clear behavior, and stages the requested
 * channel polarity. It loads exact 0 percent duty directly while CCR preload
 * is disabled, and then
 * enables CCR preload. It never generates a Timer-wide update event and never
 * enables `CCxE` or `CR1.CEN`.
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
 * @param[in] channelMode Timer PWM channel-mode selector
 * Accepted values:
 * - @ref `TIMx_CHANNEL_MODE_PWM1`: PWM mode 1
 * - @ref `TIMx_CHANNEL_MODE_PWM2`: PWM mode 2
 * @param[in] channelPolarity Timer PWM channel-polarity selector
 * Accepted values:
 * - @ref `TIMx_CHANNEL_POLARITY_HIGH`: Active-high output
 * - @ref `TIMx_CHANNEL_POLARITY_LOW`: Active-low output
 * @returns @ref driver_status_t "PWM-channel configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: PWM channel was configured and remains disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Instance, channel mode, channel polarity, or programmed ARR is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer base configuration does not satisfy the PWM contract
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Counter or selected channel output is enabled
 * @pre The application successfully completed @ref TIM_Config and left `CNT` at zero
 * @pre The selected channel output is disabled
 * @note GPIO and AFIO state are never read or modified
 */
driver_status_t TIM_ConfigPWMChannel
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channel,
	const tim_channel_mode_t		channelMode,
	const tim_channel_polarity_t	channelPolarity
);

/**
 * @brief Gets one Timer PWM channel's mode and polarity configuration
 * @details
 * Reads the selected `CCMR` lane and `CCER`, validates the complete supported
 * PWM shape, and publishes both selectors only after successful extraction.
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
 * @returns @ref driver_status_t "PWM-channel configuration extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Complete PWM configuration was published
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An input or output pointer is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Instance or channel is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The channel does not have the admitted PWM shape
 * @note Output storage remains unchanged on failure
 */
driver_status_t TIM_GetPWMChannelConfig
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channel,
	tim_channel_mode_t* const		pChannelMode,
	tim_channel_polarity_t* const	pChannelPolarity
);

/**
 * @brief Restores one disabled Timer PWM channel to its channel reset state
 * @details
 * Clears only the selected channel's CCMR lane, `CCxE`, `CCxP`, and `CCRx`.
 * Every other Timer channel, the Timer timebase, RCC, IRQ, DMA, GPIO, AFIO,
 * and NVIC state is preserved.
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
 * @returns @ref driver_status_t "PWM-channel deconfiguration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Selected channel-owned state was reset
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Instance or channel is invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The selected channel is not configured for PWM
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Counter or selected channel output is enabled
 */
driver_status_t TIM_DeConfigPWMChannel
(
	TIM_TypeDef* const		TIMx,
	const tim_channel_t	channel
);

// ==================================================================================================== //
//									Timer PWM Duty-Cycle APIs									//
// ==================================================================================================== //

/**
 * @brief Sets one configured Timer PWM channel's duty cycle
 * @details
 * Duty is expressed in permille units: `0` is exact 0.0 percent, `500` is
 * 50.0 percent, and `1000` is exact 100.0 percent. PWM mode 1 and mode 2 use
 * mode-correct compare equations so the value always describes time at the
 * selected active polarity. For a stopped Timer with the selected output
 * disabled, the function loads only that channel's active CCR. For a running
 * Timer, it updates the programmed preload for the next natural update event.
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
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Channel is not configured for
 * PWM or a stopped counter is not at zero
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: A stopped Timer still has the selected channel output enabled
 * @pre Disable the selected channel output before changing its stopped-state duty
 * @note The stopped path temporarily disables only the selected lane's CCR
 * preload, writes its active compare value, and restores preload before return
 */
driver_status_t TIM_SetPWMChannelDutyCycle
(
	TIM_TypeDef* const			TIMx,
	const tim_channel_t			channel,
	const tim_pwm_duty_cycle_t	dutyCycle
);

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
 * @note While running, the readable preload may not yet be active until the next update event
 * @note Output storage remains unchanged on failure
 */
driver_status_t TIM_GetPWMChannelDutyCycle
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t				channel,
	tim_pwm_duty_cycle_t* const		pDutyCycle
);

// ==================================================================================================== //
//								Timer PWM Output-Enable-State APIs								//
// ==================================================================================================== //

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
 */
driver_status_t TIM_SetPWMChannelOutputEnableState
(
	TIM_TypeDef* const			TIMx,
	const tim_channel_t			channelMask,
	const driver_status_t		outputEnableState
);

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
driver_status_t TIM_GetPWMChannelOutputEnableState
(
	TIM_TypeDef* const		TIMx,
	const tim_channel_t	channel
);

/** @} */ // TIM_03_Driver_05_PWM

/** @} */ // TIM_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_PWM_H_ */
