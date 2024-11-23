/***************************************************************************************
 *  File: pwm.h
 *  Created on: 23/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __PWM_H__
#define __PWM_H__

// Dependency
#include "gpio.h"
#include "gpt.h"

// PWM Configuration Structure
typedef struct {
    // Timer Configuration
    gpt_config_t GPT_CONFIGx;
    // PWM Mode
    TIMx_OCM_MODE pwm_mode;
    // PWM Active Polarity
    uint8_t polarity;
    // Duty Cycle (%)
    uint16_t duty_cycle;
} pwm_config_t;

/**
 * @brief Configure PWM Mode for General Purpose TIMx
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 * @param[in] pwm_mode  `TIMx_OCM_PWM_NORMAL`, `TIMx_OCM_PWM_INVERTED`
 * @param[in] preload_enable `PRELOAD_ENABLE`, `PRELOAD_DISABLE`
 */
static void config_PWM_mode(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, TIMx_OCM_MODE pwm_mode, uint8_t preload_enable);

/**
 * @brief Configure PWM related parameters for GP Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4` 
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 * @param[in] polarity  `TIMx_POL_ACTIVE_LOW`, `TIMx_POL_ACTIVE_HIGH`
 */
static void set_PWM_polarity(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, uint8_t polarity);

/**
 * @brief Updates the Duty Cycle for the specified TIMx and Channel
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4` 
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 * @param[in] duty_cycle Duty Cycle Value in (%) 
 */
static void set_PWM_duty(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, uint8_t duty_cycle);

/**
 * @brief Configures the parameters necessary for PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
void config_PWM(pwm_config_t* PWMx);

/**
 * @brief Sets the duty cycle for PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
void set_PWM_duty_cycle(pwm_config_t* PWMx);

#endif // __PWM_H__
