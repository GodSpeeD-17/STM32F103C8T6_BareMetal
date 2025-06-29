/***************************************************************************************
 *  File: pwm.c
 *  Created on: 22/06/2025
 *  Author: Shrey Shah
 ***************************************************************************************/

/*
	THEORY:
	|=> Pulse Width Modulation (PWM) is used to create pseudo Analog Value from Digital Value
	|=> Main job is to provide an Average Voltage value which is Analog in nature but made up of Digital Signals
	|=> PWM is used in various applications like Motor Speed Control, LED Dimming
	|=> From experience, 10kHz - 100kHz is the best range of frequency where almost all the devices will work
	|=> From Datasheet and Formula, do not exceed 200kHz and do not go below 100Hz (Toy Servo Motor)
	|=> FORMULA:
	|                                (Timer Frequency)
	|            PWM Frequency = -------------------------   [Hz]
	|                              (ARR + 1) * (PSC + 1)     
	|    where,
	|        Timer Frequency = ((SysClk)*(TIMx_PRE)) / ((AHB_PRE)*(APB1_PRE)) {72 MHz}
	|        ARR = TIMx Auto Reload Register
	|        PSC = TIMx Prescaler
	|
	|    After re-arranging,
	|                        (Timer Frequency)
	|            PSC = ------------------------------ - 1;
	|                    (PWM Frequency) * (ARR + 1)
	|
*/

// Main Header
#include "pwm.h"

// Internal Handle for PWM Configuration
struct pwm_handle {
	// PWM Configuration Structure
	pwm_config_t PWM_CONFIG;
	// Timer Configuration Structure
	timer_config_t TIMx_CONFIG;
};

/**
 * @brief Configures PWM
 * @param PWM_HANDLE Final Handle for future reference to PWM Configuration
 * @param PWM_CONFIG PWM Configuration Structure
 * @returns - Pointer to the PWM Handle on success
 * @returns - `NULL` on memory allocation failure
 * @note This function dynamically allocates memory for the PWM handle
 * @note After using, remember to free the handle using `PWM_DeConfig()`
 */
pwm_handle_t PWM_Config(pwm_config_t* PWM_CONFIG){
	// Dynamic Memory Allocation for PWM Handle
	pwm_handle_t pwm_handle = calloc(1, sizeof(struct pwm_handle));
	if(!pwm_handle) return NULL;
	// Deep Copy PWM Configuration
	memcpy(&pwm_handle->PWM_CONFIG, PWM_CONFIG, sizeof(pwm_config_t));
	// Fetch the Timer & Channel Mapping based on GPIO
	if(!PWM_Get_TIM_From_GPIO(&PWM_CONFIG->GPIOx_CONFIG, &pwm_handle->TIMx_CONFIG)){
		free(pwm_handle);
		return NULL;
	}
	// Disable the Timer Module
	TIM_Disable(pwm_handle->TIMx_CONFIG.TIM);
	// Timer is not configured
	if(pwm_handle->TIMx_CONFIG.TIM->ARR != PWM_DEFAULT_ARR){
		// Default Timer Configuration for PWM
		PWM_Default_TIM_Config(pwm_handle);
		// Prescaler for Target PWM Frequency based on Timer Frequency
		pwm_handle->TIMx_CONFIG.prescaler = PWM_Calc_TIM_Prescaler(pwm_handle);
		// Configure Timer based on the PWM Configuration
		TIM_Config(&pwm_handle->TIMx_CONFIG);
	}
	// Channel Configuration
	switch(pwm_handle->TIMx_CONFIG.channel){
		// Channel 1 Configuration
		case TIMx_CHANNEL_1:
			// Set the PWM Mode & Preload
			pwm_handle->TIMx_CONFIG.TIM->CCMR1.REG |= ((PWM_CONFIG->mode << TIM_CCMR1_OC1M_Pos) |
													   (PWM_CONFIG->preload << TIM_CCMR1_OC1PE_Pos));
			// Set the Polarity	
			pwm_handle->TIMx_CONFIG.TIM->CCER.REG |= (PWM_CONFIG->polarity << TIM_CCER_CC1P_Pos);											   
			// Duty Cycle
			pwm_handle->TIMx_CONFIG.TIM->CCR1.CC1_OUT = PWM_CONFIG->duty_cycle;
		break;
		// Channel 2 Configuration
		case TIMx_CHANNEL_2:
			// Set the PWM Mode & Preload
			pwm_handle->TIMx_CONFIG.TIM->CCMR1.REG |= ((PWM_CONFIG->mode << TIM_CCMR1_OC2M_Pos) |
													   (PWM_CONFIG->preload << TIM_CCMR1_OC2PE_Pos));
			// Set the Polarity	
			pwm_handle->TIMx_CONFIG.TIM->CCER.REG |= (PWM_CONFIG->polarity << TIM_CCER_CC2P_Pos);
			// Duty Cycle
			pwm_handle->TIMx_CONFIG.TIM->CCR2.CC2_OUT = PWM_CONFIG->duty_cycle;
		break;
		// Channel 3 Configuration
		case TIMx_CHANNEL_3:
			// Set the PWM Mode & Preload
			pwm_handle->TIMx_CONFIG.TIM->CCMR2.REG |= ((PWM_CONFIG->mode << TIM_CCMR2_OC3M_Pos) |
													   (PWM_CONFIG->preload << TIM_CCMR2_OC3PE_Pos));
			// Set the Polarity	
			pwm_handle->TIMx_CONFIG.TIM->CCER.REG |= (PWM_CONFIG->polarity << TIM_CCER_CC3P_Pos);
			// Duty Cycle
			pwm_handle->TIMx_CONFIG.TIM->CCR3.CC3_OUT = (PWM_CONFIG->duty_cycle - 1);
		break;
		// Channel 4 Configuration
		case TIMx_CHANNEL_4:
			// Set the PWM Mode & Preload
			pwm_handle->TIMx_CONFIG.TIM->CCMR2.REG |= ((PWM_CONFIG->mode << TIM_CCMR2_OC4M_Pos) |
													   (PWM_CONFIG->preload << TIM_CCMR2_OC4PE_Pos));
			// Set the Polarity	
			pwm_handle->TIMx_CONFIG.TIM->CCER.REG |= (PWM_CONFIG->polarity << TIM_CCER_CC4P_Pos);
			// Duty Cycle
			pwm_handle->TIMx_CONFIG.TIM->CCR4.CC4_OUT = PWM_CONFIG->duty_cycle;
		break;
	}
	// Configures the GPIO for PWM output
	PWM_GPIO_Config(pwm_handle);
	// Return Pointer to the PWM Handle
	return pwm_handle;
}

/**
 * @brief Deconfigures the PWM
 * @param PWM_HANDLE Final Handle for future reference to PWM Configuration
 * @return `NULL` on success
 * @note This function frees the dynamically allocated memory for the PWM handle
 * @note This function should be called after the PWM is no longer needed post `PWM_Config()`
 */
pwm_handle_t PWM_DeConfig(pwm_handle_t PWM_HANDLE){
	// Stop the PWM
	PWM_Stop(PWM_HANDLE);
	// Deconfigure the GPIO
	GPIO_DeConfig(&PWM_HANDLE->PWM_CONFIG.GPIOx_CONFIG);
	// Free the Dynamic Memory
	free(PWM_HANDLE);
	// Return the PWM Handle
	return NULL;
}

/**
 * @brief Default Timer Configuration Structure for PWM
 * @param PWM_HANDLE PWM Handle
 * @note - Timer Mode: Edge Mode
 * @note - Direction: Up Counting
 */
void PWM_Default_TIM_Config(pwm_handle_t PWM_HANDLE){
	// Counter Max Value based on Duty Cycle precision of 0.1%
	PWM_HANDLE->TIMx_CONFIG.auto_reload = PWM_DEFAULT_ARR;
	// Default Count Value 
	PWM_HANDLE->TIMx_CONFIG.count = TIMx_DEFAULT_CNT;
	// Default Timer Couting Mode
	PWM_HANDLE->TIMx_CONFIG.cms_mode = TIMx_CMS_EDGE;
	// Default Timer Couting Direction
	PWM_HANDLE->TIMx_CONFIG.direction = TIMx_DIR_COUNT_UP;
	// Default Timer Auto-Reload Preload Enabled
	PWM_HANDLE->TIMx_CONFIG.arpe = TIMx_ARPE_ENABLE;
	// Default Timer One Pulse Mode Disabled
	PWM_HANDLE->TIMx_CONFIG.one_pulse = TIMx_OPM_DISABLE;
}

/**
 * @brief Enables the PWM Channel
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Start(pwm_handle_t PWM_HANDLE){
	// Enable the Channel
	TIM_Channel_Enable(PWM_HANDLE->TIMx_CONFIG.TIM, PWM_HANDLE->TIMx_CONFIG.channel);
}

/**
 * @brief Enables the PWM
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Enable(pwm_handle_t PWM_HANDLE){
	// Enable the Timer
	TIM_Enable(PWM_HANDLE->TIMx_CONFIG.TIM);
	// Enable the Channel
	PWM_Start(PWM_HANDLE);
}

/**
 * @brief Disables the PWM Channel
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Stop(pwm_handle_t PWM_HANDLE){
	// Disable the Channel
	TIM_Channel_Disable(PWM_HANDLE->TIMx_CONFIG.TIM, PWM_HANDLE->TIMx_CONFIG.channel);
}

/**
 * @brief Disables the PWM
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Disable(pwm_handle_t PWM_HANDLE){
	// Disable the Channel
	PWM_Stop(PWM_HANDLE);
	// Disable the Timer
	TIM_Disable(PWM_HANDLE->TIMx_CONFIG.TIM);
}

/**
 * @brief Updates the Duty Cycle for a PWM Configuration
 * @param PWM_HANDLE Handle to the PWM Configuration
 * @param duty_cycle Updated Duty Cycle Value (%) x 10
 * @note `duty_cycle` is scaled value:
 * @note For 0.1% Duty Cycle -> `duty_cycle = 1`
 * @note For 100% Duty Cycle -> `duty_cycle = 1000`
 */
void PWM_Update_Duty_Cycle(pwm_handle_t PWM_HANDLE, int16_t duty_cycle){
	// Wrap Duty Cycle
	if(duty_cycle >= PWM_MAX_DUTY_CYCLE)
		duty_cycle = PWM_MAX_DUTY_CYCLE;
	else if (duty_cycle <= PWM_MIN_DUTY_CYCLE)
		duty_cycle = PWM_MIN_DUTY_CYCLE;
	// Channel 1: Update the Duty Cycle Directly due to Buffered Value
	if(PWM_HANDLE->TIMx_CONFIG.channel == TIMx_CHANNEL_1)
		PWM_HANDLE->TIMx_CONFIG.TIM->CCR1.CC1_OUT = duty_cycle;
	// Channel 2: Update the Duty Cycle Directly due to Buffered Value	
	else if(PWM_HANDLE->TIMx_CONFIG.channel == TIMx_CHANNEL_2)
		PWM_HANDLE->TIMx_CONFIG.TIM->CCR2.CC2_OUT = duty_cycle;
	// Channel 3: Update the Duty Cycle Directly due to Buffered Value	
	else if(PWM_HANDLE->TIMx_CONFIG.channel == TIMx_CHANNEL_3)
		PWM_HANDLE->TIMx_CONFIG.TIM->CCR3.CC3_OUT = duty_cycle;
	// Channel 4: Update the Duty Cycle Directly due to Buffered Value	
	else if(PWM_HANDLE->TIMx_CONFIG.channel == TIMx_CHANNEL_4)
		PWM_HANDLE->TIMx_CONFIG.TIM->CCR4.CC4_OUT = duty_cycle;
}

/**
 * @brief Calculates Timer Prescaler based on target PWM Frequency 
 * @param PWM_HANDLE Handle to the PWM Configuration
 * @returns Timer Prescaler Value
 */
uint16_t PWM_Calc_TIM_Prescaler(pwm_handle_t PWM_HANDLE){
	// Formula: PSC = ((APB2 Clock Frequency)/((Target PWM Frequency) * (ARR + 1))) - 1
	// Calculate the Timer Input Frequency First
	uint32_t prescaler = TIM_Get_Frequency(PWM_HANDLE->TIMx_CONFIG.TIM);
	// Divide by Auto Reload Value & Target PWM Frequency
	prescaler /= ((PWM_HANDLE->TIMx_CONFIG.auto_reload + 1) * (PWM_HANDLE->PWM_CONFIG.freq_Hz));
	// Return the final Calculated Prescaler Value
	return (uint16_t) (prescaler - 1);
}

/**
 * @brief Configures the GPIO for PWM output
 * @param PWM_HANDLE PWM Handle
 * @note Assumes that the GPIO & PIN is already set in the GPIO Configuration Structure
 */
void PWM_GPIO_Config(pwm_handle_t PWM_HANDLE){
	// Set the GPIO Mode to Output
	PWM_HANDLE->PWM_CONFIG.GPIOx_CONFIG.MODE = GPIOx_MODE_OUT_10MHz;
	// Set the GPIO Configuration to Alternate Function Push-Pull
	PWM_HANDLE->PWM_CONFIG.GPIOx_CONFIG.CNF = GPIOx_CNF_OUT_AF_PP;
	// Configure the GPIO
	GPIO_Config(&PWM_HANDLE->PWM_CONFIG.GPIOx_CONFIG);
}

