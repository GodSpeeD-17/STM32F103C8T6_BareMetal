/***************************************************************************************
 *  File: pwm.h
 *  Created on: 23/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __PWM_H__
#define __PWM_H__

// Dependency
#include "timer.h"

// PWM Configuration Structure
typedef struct {
	// Timer Configuration Structure
	timer_config_t* TIM_CONFIGx;
	// PWM Mode
	TIMx_OCM_MODE pwm_mode;
	// PWM Active Polarity
	uint8_t polarity;
	// Duty Cycle (%)
	uint8_t duty_cycle;
	// PWM Channel Preload
	uint8_t pwm_channel_preload;
} pwm_config_t;

/**
 * @brief Starts the PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 * @note Use this only for single channel configuration
 */
__INLINE__ void PWM_start(pwm_config_t* PWMx){
	// Stop if already running
	if(PWMx->TIM_CONFIGx->TIMx->CR1.BIT.CEN){
		PWMx->TIM_CONFIGx->TIMx->CR1.BIT.CEN = 0;
	}
	// Clear the update flag
	PWMx->TIM_CONFIGx->TIMx->SR.REG &= ~BIT_SET;
	// Enable Channel
	enable_GPT_CH(PWMx->TIM_CONFIGx);
	// Enable Timer
	enable_GPT(PWMx->TIM_CONFIGx);
}

/**
 * @brief Stops the PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 * @note Use this only for single channel configuration
 */
__INLINE__ void PWM_stop(pwm_config_t* PWMx){
	// Disable Timer
	disable_GPT(PWMx->TIM_CONFIGx);
	// Disable Channel
	disable_GPT_CH(PWMx->TIM_CONFIGx);
	// Clear the update flag
	PWMx->TIM_CONFIGx->TIMx->SR.REG &= (uint32_t)~(1 << 0);
}

/**
 * @brief Stops the PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
__INLINE__ uint16_t PWM_calc_CCRx(pwm_config_t* PWMx){
	// Final Result
	uint16_t result;
	// Store the Value
	result = (((PWMx->TIM_CONFIGx->TIMx->ARR) + 1) * PWMx->duty_cycle);
	result /= 100;
	result -= 1;
	// Return the final Calculated Value
	return result;
}

/**
 * @brief Starts PWM on specific Channel
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
__INLINE__ void PWM_startMultiChannel(pwm_config_t* PWMx, uint8_t channel){
	// Enable Timer
	enable_GPT(PWMx->TIM_CONFIGx);
	// Enable Channel
	enable_GPT_multi_CH(PWMx->TIM_CONFIGx, channel);
}

/**
 * @brief Stops PWM on specific Channel
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
__INLINE__ void PWM_stopMultiChannel(pwm_config_t* PWMx, uint8_t channel){
	// Disable Channel
	disable_GPT_multi_CH(PWMx->TIM_CONFIGx, channel);
	// Disable Timer
	disable_GPT(PWMx->TIM_CONFIGx);
}

/**
 * @brief Configures the parameters necessary for PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
void PWM_config(pwm_config_t* PWMx);

/**
 * @brief Sets the duty cycle for PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
void PWM_setDutyCycle(pwm_config_t* PWMx);

/**
 * @brief Sets the duty cycle for PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 * @param[in] channel `TIMx_CHANNEL_1`
 * @note Use this function when multiple channel is used for PWM configuration
 */
void PWM_setMultiChannelDutyCycle(pwm_config_t* PWMx, uint8_t channel);

/**
 * @brief Configures the PWM Structure to default values
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
__INLINE__ void PWM_load_default(pwm_config_t* PWM_CONFIGx){
	// Load Default Timer Value
	load_GPT_default(PWM_CONFIGx->TIM_CONFIGx);
	// Update the GPIO Configuration
	PWM_CONFIGx->TIM_CONFIGx->GPIO_CONFIGx->MODE = GPIOx_MODE_OUT_10MHz;
	PWM_CONFIGx->TIM_CONFIGx->GPIO_CONFIGx->CNF = GPIOx_CNF_OUT_AF_PP;
	// PWM Mode (Normal Mode)
	PWM_CONFIGx->pwm_mode = TIMx_OCM_PWM_NORMAL;
	// Duty Cycle (Minimum)
	PWM_CONFIGx->duty_cycle = MIN_DUTY_CYCLE,
	// Polarity (Active High)
	PWM_CONFIGx->polarity = TIMx_POL_ACTIVE_HIGH;
	// PWM Channel Preload Enable
	PWM_CONFIGx->pwm_channel_preload = PWM_CHx_PRELOAD_ENABLE;
}

#endif /* __PWM_H__ */ 
