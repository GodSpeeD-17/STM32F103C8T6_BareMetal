// Header Guards
#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

// Register Mapping
#include "reg_map.h"
#include "gpio.h"
#include "timer.h"

// Timer GPIO Mapping Configuration Structure
typedef struct {
	// GPIO
	// - `GPIOA`
	// - `GPIOB`
	// - `GPIOC`
	// - `GPIOD`
	GPIO_REG_STRUCT* GPIO;
	// GPIO Pin
	// - `GPIO_PIN_0`
	// ....
	// - `GPIO_PIN_15`
	uint8_t PIN;
} timer_gpio_mapping_t;

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
	// PWM Mode
	uint16_t mode: 3;
} pwm_config_t;

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


#endif /* __PWM_CONFIG_H__ */