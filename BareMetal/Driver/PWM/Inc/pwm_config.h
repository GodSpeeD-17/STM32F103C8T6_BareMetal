// Header Guards
#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

// Register Mapping
#include "reg_map.h"
#include "gpio.h"
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
 * @brief Configures the GPIO for PWM output
 * @param GPIOx_CONFIG GPIO Configuration Structure
 * @note Assumes that the GPIO & PIN is already set in the GPIO Configuration Structure
 */
void PWM_GPIO_Config(gpio_config_t* GPIOx_CONFIG);

/**
 * @brief Copies the PWM Configuration from source to destination
 * @param dest Destination PWM Configuration Structure
 * @param src Source PWM Configuration Structure
 */
void PWM_Config_Copy(pwm_config_t* dest, const pwm_config_t* src);

/**
 * @brief Enables the PWM Channel
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
__INLINE__ void PWM_Start(pwm_handle_t PWM_HANDLE){
	// Enable the Channel
	TIM_Channel_Enable(PWM_HANDLE->TIMx_CONFIG.TIM, PWM_HANDLE->TIMx_CONFIG.channel);
}

/**
 * @brief Enables the PWM
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
__INLINE__ void PWM_Enable(pwm_handle_t PWM_HANDLE){
	// Enable the Timer
	TIM_Enable(PWM_HANDLE->TIMx_CONFIG.TIM);
	// Enable the Channel
	PWM_Start(PWM_HANDLE);
}

/**
 * @brief Disables the PWM Channel
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
__INLINE__ void PWM_Stop(pwm_handle_t PWM_HANDLE){
	// Disable the Channel
	TIM_Channel_Disable(PWM_HANDLE->TIMx_CONFIG.TIM, PWM_HANDLE->TIMx_CONFIG.channel);
}

/**
 * @brief Disables the PWM
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
__INLINE__ void PWM_Disable(pwm_handle_t PWM_HANDLE){
	// Disable the Channel
	PWM_Stop(PWM_HANDLE);
	// Disable the Timer
	TIM_Disable(PWM_HANDLE->TIMx_CONFIG.TIM);
}


#endif /* __PWM_CONFIG_H__ */