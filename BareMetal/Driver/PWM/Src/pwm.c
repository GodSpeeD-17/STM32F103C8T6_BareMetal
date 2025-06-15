// Main Header
#include "pwm.h"
#include "pwm_handle.h"

/**
 * @brief Configures the GPIO based on Timer for PWM output
 * @param TIMx_CONFIG General Purpose Timer Configuration Structure
 * @param GPIOx_CONFIG GPIO Configuration Structure
 */
void PWM_GPIO_Config(const timer_config_t* TIMx_CONFIG, gpio_config_t* GPIOx_CONFIG){
	// Get the GPIO Mapping
	PWM_Get_GPIO_Mapping(TIMx_CONFIG, GPIOx_CONFIG);
	// Set the GPIO Mode to Output
	GPIOx_CONFIG->MODE = GPIOx_MODE_OUT_10MHz;
	// Set the GPIO Configuration to Alternate Function Push-Pull
	GPIOx_CONFIG->CNF = GPIOx_CNF_OUT_AF_PP;
	// Configure the GPIO
	GPIO_Config(GPIOx_CONFIG);
}


void PWM_Config(pwm_handle_t* PWMx_HANDLE, pwm_config_t* PWMx_CONFIG) {
	// Assign the PWM Configuration
	PWMx_HANDLE->PWMx_CONFIG = PWMx_CONFIG;
	
}