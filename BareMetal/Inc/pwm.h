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
} pwm_config_t;

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
 * @brief Starts the PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
__attribute__((always_inline)) inline void start_PWM(pwm_config_t* PWMx){
    // Enable Timer
    enable_GPT(PWMx->GPT_CONFIGx);
    // Enable Channel
    enable_GPT_CH(PWMx->GPT_CONFIGx);
}

/**
 * @brief Stops the PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
__attribute__((always_inline)) inline void stop_PWM(pwm_config_t* PWMx){
    // Disable Channel
	disable_GPT_CH(PWMx->GPT_CONFIGx);
	// Disable Timer
	disable_GPT(PWMx->GPT_CONFIGx);
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

#endif /* __PWM_H__ */ 
