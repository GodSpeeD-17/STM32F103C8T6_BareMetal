/***************************************************************************************
 *  File: pwm.h
 *  Created on: 26/10/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __PWM_H__
#define __PWM_H__

// Dependency
#include "gpio.h"
#include "gpt.h"

/**
 * @brief Configure PWM Mode for General Purpose TIMx
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 * @param[in] pwm_mode  `TIMx_OCM_PWM_NORMAL`, `TIMx_OCM_PWM_INVERTED`
 * @param[in] preload_enable `PRELOAD_ENABLE`, `PRELOAD_DISABLE`
 */
void config_PWM_mode(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, TIMx_OCM_MODE pwm_mode, uint8_t preload_enable);

/**
 * @brief Configure PWM related parameters for GP Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4` 
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 * @param[in] polarity  `TIMx_POL_ACTIVE_LOW`, `TIMx_POL_ACTIVE_HIGH`
 */
void set_PWM_polarity(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, uint8_t polarity);

/**
 * @brief Updates the Duty Cycle for the specified TIMx and Channel
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4` 
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 * @param[in] duty_cycle Duty Cycle Value in (%) 
 */
void set_PWM_duty_cycle(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, uint8_t duty_cycle);

#endif // __PWM_H__
