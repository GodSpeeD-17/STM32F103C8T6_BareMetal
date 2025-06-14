// Header Guards
#ifndef __PWM_H__
#define __PWM_H__

// Header Files
#include "pwm_config.h"
#include "gpio.h"
#include "timer.h"

/**
 * @brief Retrieve the GPIO mapping for a given timer
 * @param TIMx General Purpose Timer
 * @param GPIO_CONFIGx GPIO Configuration Structure 
 */
void PWM_Get_GPIO_Mapping(const timer_config_t* TIM_CONFIGx, gpio_config_t* GPIO_CONFIGx);

/**
 * @brief Configures the GPIO based on Timer for PWM output
 * @param TIM_CONFIGx General Purpose Timer Configuration Structure
 * @param GPIO_CONFIGx GPIO Configuration Structure
 */
void PWM_GPIO_Config(const timer_config_t* TIM_CONFIGx, gpio_config_t* GPIO_CONFIGx);

#endif /* __PWM_H__ */