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
 * PWM frequency remains a Timer timebase property. GPIO mode, output speed,
 * AFIO routing, RCC clock gates, IRQ delivery, and physical-pin lifecycle
 * remain application-owned. This interface allocates no memory and stores no
 * hidden handle, endpoint, frequency, or requested-duty state.
 */

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
 * output compare, disables fast/clear behavior, stages the requested polarity,
 * loads exact 0 percent duty directly while CCR preload is disabled, and then
 * enables CCR preload. It never generates a Timer-wide update event and never
 * enables `CCxE` or `CR1.CEN`.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values: `TIM2`, `TIM3`, or `TIM4`
 * @param[in] channel Timer single-channel selector
 * Accepted values: @ref TIMx_CHANNEL_1 "`TIMx_CHANNEL_1`" through
 * @ref TIMx_CHANNEL_4 "`TIMx_CHANNEL_4`"
 * @param[in] mode Timer PWM mode selector
 * Accepted values: @ref TIMx_CHANNEL_MODE_PWM1 "`TIMx_CHANNEL_MODE_PWM1`" or
 * @ref TIMx_CHANNEL_MODE_PWM2 "`TIMx_CHANNEL_MODE_PWM2`"
 * @param[in] polarity Timer channel polarity selector
 * Accepted values: @ref TIMx_CHANNEL_POLARITY_HIGH "`TIMx_CHANNEL_POLARITY_HIGH`" or
 * @ref TIMx_CHANNEL_POLARITY_LOW "`TIMx_CHANNEL_POLARITY_LOW`"
 * @returns @ref driver_status_t "PWM configuration status"
 * @retval DRIVER_STATUS_SUCCESS PWM channel was configured and remains disabled
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG Instance, channel, mode, polarity, or programmed ARR is invalid
 * @retval DRIVER_STATUS_ERROR_STATE Clock gate or Timer base configuration does not satisfy the PWM contract
 * @retval DRIVER_STATUS_ERROR_BUSY Counter or selected channel output is enabled
 * @pre The application enabled the matching Timer APB1 clock gate
 * @pre The application completed @ref TIM_Config and left `CNT` at zero
 * @pre The selected channel output is disabled
 * @note GPIO and AFIO state are never read or modified
 */
driver_status_t TIM_ConfigPWM
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t			channel,
	const tim_channel_mode_t		mode,
	const tim_channel_polarity_t	polarity
);

/**
 * @brief Gets one Timer PWM channel's mode and polarity
 * @param[in] TIMx Timer peripheral instance
 * Accepted values: `TIM2`, `TIM3`, or `TIM4`
 * @param[in] channel Timer single-channel selector
 * Accepted values: @ref TIMx_CHANNEL_1 "`TIMx_CHANNEL_1`" through
 * @ref TIMx_CHANNEL_4 "`TIMx_CHANNEL_4`"
 * @param[out] pMode Destination for the configured PWM mode
 * @param[out] pPolarity Destination for the configured channel polarity
 * @returns @ref driver_status_t "PWM configuration extraction status"
 * @retval DRIVER_STATUS_SUCCESS Complete PWM configuration was published
 * @retval DRIVER_STATUS_ERROR_NULL_PTR An input or output pointer is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG Instance or channel is invalid
 * @retval DRIVER_STATUS_ERROR_STATE Clock gate is disabled or the channel does not have the admitted PWM shape
 * @note Output storage remains unchanged on failure
 */
driver_status_t TIM_GetPWMConfig
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t			channel,
	tim_channel_mode_t* const		pMode,
	tim_channel_polarity_t* const	pPolarity
);

/**
 * @brief Restores one disabled Timer PWM channel to its channel reset state
 * @details
 * Clears only the selected channel's CCMR lane, `CCxE`, `CCxP`, and `CCRx`.
 * Every other Timer channel, the Timer timebase, RCC, IRQ, DMA, GPIO, AFIO,
 * and NVIC state is preserved.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values: `TIM2`, `TIM3`, or `TIM4`
 * @param[in] channel Timer single-channel selector
 * Accepted values: @ref TIMx_CHANNEL_1 "`TIMx_CHANNEL_1`" through
 * @ref TIMx_CHANNEL_4 "`TIMx_CHANNEL_4`"
 * @returns @ref driver_status_t "PWM deconfiguration status"
 * @retval DRIVER_STATUS_SUCCESS Selected channel-owned state was reset
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG Instance or channel is invalid
 * @retval DRIVER_STATUS_ERROR_STATE Clock gate is disabled or the selected channel is not configured for PWM
 * @retval DRIVER_STATUS_ERROR_BUSY Counter or selected channel output is enabled
 */
driver_status_t TIM_DeConfigPWM
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
 * Accepted values: `TIM2`, `TIM3`, or `TIM4`
 * @param[in] channel Timer single-channel selector
 * Accepted values: @ref TIMx_CHANNEL_1 "`TIMx_CHANNEL_1`" through
 * @ref TIMx_CHANNEL_4 "`TIMx_CHANNEL_4`"
 * @param[in] dutyCycle Duty cycle in permille units
 * Accepted values: @ref TIM_PWM_DUTY_CYCLE_MIN "`TIM_PWM_DUTY_CYCLE_MIN`" through
 * @ref TIM_PWM_DUTY_CYCLE_MAX "`TIM_PWM_DUTY_CYCLE_MAX`"
 * @returns @ref driver_status_t "PWM duty update status"
 * @retval DRIVER_STATUS_SUCCESS Selected compare value was programmed
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG Instance, channel, duty, or programmed ARR is invalid
 * @retval DRIVER_STATUS_ERROR_STATE Clock gate is disabled, channel
 * is not configured for PWM, or a stopped counter is not at zero
 * @retval DRIVER_STATUS_ERROR_BUSY A stopped Timer still has the selected channel output enabled
 * @pre Disable the selected channel output before changing its stopped-state duty
 * @note The stopped path temporarily disables only the selected lane's CCR
 * preload, writes its active compare value, and restores preload before return
 */
driver_status_t TIM_SetPWMDutyCycle
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t			channel,
	const tim_pwm_duty_cycle_t	dutyCycle
);

/**
 * @brief Gets the duty represented by one Timer PWM channel's programmed state
 * @param[in] TIMx Timer peripheral instance
 * Accepted values: `TIM2`, `TIM3`, or `TIM4`
 * @param[in] channel Timer single-channel selector
 * Accepted values: @ref TIMx_CHANNEL_1 "`TIMx_CHANNEL_1`" through
 * @ref TIMx_CHANNEL_4 "`TIMx_CHANNEL_4`"
 * @param[out] pDutyCycle Destination for the achieved duty in permille units
 * @returns @ref driver_status_t "PWM duty extraction status"
 * @retval DRIVER_STATUS_SUCCESS Programmed duty was published
 * @retval DRIVER_STATUS_ERROR_NULL_PTR An input or output pointer is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG Instance, channel, ARR, or compare value is invalid
 * @retval DRIVER_STATUS_ERROR_STATE Clock gate is disabled or channel is not configured for PWM
 * @note While running, the readable preload may not yet be active until the next update event
 * @note Output storage remains unchanged on failure
 */
driver_status_t TIM_GetPWMDutyCycle
(
	TIM_TypeDef* const				TIMx,
	const tim_channel_t			channel,
	tim_pwm_duty_cycle_t* const	pDutyCycle
);

// ==================================================================================================== //
//									Timer PWM Output-State APIs									//
// ==================================================================================================== //

/**
 * @brief Sets the output state of one or more Timer PWM channels
 * @details
 * Stages all selected `CCxE` fields into one `CCER` image and writes `CCER` at
 * most once. Enabling validates the admitted PWM shape of every selected lane.
 * Disabling remains available as a safe cleanup operation. `CR1.CEN` is never
 * changed.
 *
 * @param[in] TIMx Timer peripheral instance
 * Accepted values: `TIM2`, `TIM3`, or `TIM4`
 * @param[in] channelMask Non-empty Timer channel mask
 * Accepted values: Any combination of @ref TIMx_CHANNEL_1 "`TIMx_CHANNEL_1`"
 * through @ref TIMx_CHANNEL_4 "`TIMx_CHANNEL_4`"
 * @param[in] outputState Requested output state
 * Accepted values: @ref DRIVER_STATUS_OFF "`DRIVER_STATUS_OFF`" or
 * @ref DRIVER_STATUS_ON "`DRIVER_STATUS_ON`"
 * @returns @ref driver_status_t "PWM output-state update status"
 * @retval DRIVER_STATUS_SUCCESS Selected `CCxE` fields were updated coherently
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG Instance, channel mask, or output state is invalid
 * @retval DRIVER_STATUS_ERROR_STATE Clock gate is disabled or an enabled lane is not configured for PWM
 */
driver_status_t TIM_SetPWMOutputState
(
	TIM_TypeDef* const			TIMx,
	const tim_channel_t		channelMask,
	const driver_status_t		outputState
);

/**
 * @brief Gets one Timer PWM channel's output-enable state
 * @param[in] TIMx Timer peripheral instance
 * Accepted values: `TIM2`, `TIM3`, or `TIM4`
 * @param[in] channel Timer single-channel selector
 * Accepted values: @ref TIMx_CHANNEL_1 "`TIMx_CHANNEL_1`" through
 * @ref TIMx_CHANNEL_4 "`TIMx_CHANNEL_4`"
 * @returns @ref driver_status_t "PWM output state"
 * @retval DRIVER_STATUS_OFF Selected channel output is disabled
 * @retval DRIVER_STATUS_ON Selected channel output is enabled
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG Instance or channel is invalid
 * @retval DRIVER_STATUS_ERROR_STATE Clock gate is disabled or channel is not configured for PWM
 */
driver_status_t TIM_GetPWMOutputState
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
