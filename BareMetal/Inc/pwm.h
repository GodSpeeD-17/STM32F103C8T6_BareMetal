/***************************************************************************************
 *  File: pwm.h
 *  Created on: 23/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __PWM_H__
#define __PWM_H__

// Dependency
#include "gpt.h"

// PWM Configuration Structure
typedef struct {
	// Timer Configuration Structure
	gpt_config_t* GPT_CONFIGx;
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
__attribute__((always_inline)) inline void start_PWM(pwm_config_t* PWMx){
	// Stop if already running
	if(PWMx->GPT_CONFIGx->GP_TIMx->CR1.BIT.CEN){
		PWMx->GPT_CONFIGx->GP_TIMx->CR1.BIT.CEN = 0;
	}
	// Clear the update flag
	PWMx->GPT_CONFIGx->GP_TIMx->SR.REG &= ~BIT_SET;
	// Enable Channel
	enable_GPT_CH(PWMx->GPT_CONFIGx);
	// Enable Timer
	enable_GPT(PWMx->GPT_CONFIGx);
}

/**
 * @brief Stops the PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 * @note Use this only for single channel configuration
 */
__attribute__((always_inline)) inline void stop_PWM(pwm_config_t* PWMx){
	// Disable Timer
	disable_GPT(PWMx->GPT_CONFIGx);
	// Disable Channel
	disable_GPT_CH(PWMx->GPT_CONFIGx);
	// Clear the update flag
	PWMx->GPT_CONFIGx->GP_TIMx->SR.REG &= (uint32_t)~(1 << 0);
}

/**
 * @brief Stops the PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
__attribute__((always_inline)) inline uint16_t calc_PWM_CCRx(pwm_config_t* PWMx){
	// Final Result
	uint16_t result;
	// Store the Value
	result = (((PWMx->GPT_CONFIGx->GP_TIMx->ARR) + 1) * PWMx->duty_cycle);
	result /= 100;
	result -= 1;
	// Return the final Calculated Value
	return result;
}

/**
 * @brief Starts PWM on specific Channel
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
__attribute__((always_inline)) inline void start_multi_channel_PWM(pwm_config_t* PWMx, uint8_t channel){
	// Enable Timer
	enable_GPT(PWMx->GPT_CONFIGx);
	// Enable Channel
	enable_GPT_multi_CH(PWMx->GPT_CONFIGx, channel);
}

/**
 * @brief Stops PWM on specific Channel
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
__attribute__((always_inline)) inline void stop_multi_channel_PWM(pwm_config_t* PWMx, uint8_t channel){
	// Disable Channel
	disable_GPT_multi_CH(PWMx->GPT_CONFIGx, channel);
	// Disable Timer
	disable_GPT(PWMx->GPT_CONFIGx);
}

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

/**
 * @brief Sets the duty cycle for PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 * @param[in] channel `TIMx_CHANNEL_1`
 * @note Use this function when multiple channel is used for PWM configuration
 */
void set_PWM_duty_cycle_multi_channel(pwm_config_t* PWMx, uint8_t channel);

/**
 * @brief Configures the PWM Structure to default values
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
__attribute__((always_inline)) inline void load_PWM_default(pwm_config_t* PWM_CONFIGx){
	// Load Default Timer Value
	load_GPT_default(PWM_CONFIGx->GPT_CONFIGx);
	// Update the GPIO Configuration
	PWM_CONFIGx->GPT_CONFIGx->GPIO_CONFIGx->MODEx = MODE_OUT_10MHz;
	PWM_CONFIGx->GPT_CONFIGx->GPIO_CONFIGx->CNFx = CNF_OUT_AF_PP;
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
