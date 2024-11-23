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
