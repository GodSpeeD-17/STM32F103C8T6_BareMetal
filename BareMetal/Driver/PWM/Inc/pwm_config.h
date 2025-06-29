// Header Guards
#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

// Dynamic Memory Allocation
#include <stdlib.h>
// Memory Copy
#include <string.h>
// Register Mapping
#include "reg_map.h"
// GPIO Configuration
#include "gpio.h"
// Timer Configuration
#include "timer.h"

// PWM Configuration Structure
typedef struct {
	// GPIO Configuration Structure
	gpio_config_t GPIOx_CONFIG;
	// PWM Frequency (in Hz)
	uint32_t freq_Hz;
	// PWM Duty Cycle (in %)
	// - Gain factor of 10
		// - `0` for 0%
		// - `1000` for 100%
	uint16_t duty_cycle: 10;
	// PWM Mode:
	// - `PWM_MODE_NORMAL`
	// - `PWM_MODE_INVERTED`
	uint16_t mode: 3;
	// Polarity
	// - `PWM_CHx_POL_ACTIVE_HIGH`: Active High
	// - `PWM_CHx_POL_ACTIVE_LOW`: Active Low
	uint16_t polarity: 1;
	// PWM Channel Preload Enable
	// - `PWM_CHx_PRELOAD_DISABLE`: Preload Disabled
	// - `PWM_CHx_PRELOAD_ENABLE`: Preload Enabled
	uint16_t preload: 1;
} pwm_config_t;

// Handle Type Definition
typedef struct pwm_handle* pwm_handle_t;

/**
 * @brief Retrieve the GPIO mapping for a given General Purpose Timer
 * @param TIMx_CONFIG General Purpose Timer Configuration Structure
 * @param GPIOx_CONFIG GPIO Configuration Structure 
 */
void PWM_Get_GPIO_Mapping(const timer_config_t* TIMx_CONFIG, gpio_config_t* GPIOx_CONFIG);

/**
 * @brief Retrieve the Timer Mapping for a given GPIO Configuration Structure
 * @param[in] TIMx_CONFIG General Purpose Timer Configuration Structure
 * @param[in] GPIOx_CONFIG GPIO Configuration Structure 
 * @returns - 0: Failure
 * @returns - 1: Success 
 */
uint8_t PWM_Get_TIM_Mapping(timer_config_t* TIMx_CONFIG, const gpio_config_t* GPIOx_CONFIG);

/**
 * @brief Timer Mapping based on GPIO Configuration
 * @param gpio GPIO Configuration Structure
 * @param timer_cfg Timer Configuration Structure
 * @return - 0: Failure
 * @return - 1: Success
 * @note This function retrieves the Timer Mapping for a given GPIO configuration 
 */
uint8_t PWM_Get_TIM_From_GPIO(const gpio_config_t* gpio, timer_config_t* timer_cfg);

/**
 * @brief Default PWM Configuration
 * @param PWM_CONFIG Pointer to PWM Configuration Structure
 */
void PWM_Default_Configuration(pwm_config_t* PWM_CONFIG);

#endif /* __PWM_CONFIG_H__ */