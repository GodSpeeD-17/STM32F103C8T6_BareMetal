// Main Header
#include "pwm.h"
// Dynamic Memory Allocation
#include "stdlib.h"
// Memory Copy
#include "string.h"

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
	if(!pwm_handle)
		return NULL;
	// Deep Copy PWM Configuration
	memcpy(&pwm_handle->PWM_CONFIG, PWM_CONFIG, sizeof(pwm_config_t));
	// Fetch the Timer & Channel Mapping based on GPIO
	if(!PWM_Get_TIM_From_GPIO(&PWM_CONFIG->GPIOx_CONFIG, &pwm_handle->TIMx_CONFIG))
		return NULL;
	// Prescaler Based on PWM Frequency
	pwm_handle->TIMx_CONFIG.prescaler = (RCC_Get_APB1Clock() / PWM_CONFIG->freq_Hz) - 1;
	// Default Timer Configuration for PWM
	PWM_Default_TIM_Config(pwm_handle);
	// Configure Timer based on the PWM Configuration
	TIM_Config(&pwm_handle->TIMx_CONFIG);
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
			pwm_handle->TIMx_CONFIG.TIM->CCR3.CC3_OUT = PWM_CONFIG->duty_cycle;
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
		// Error Case
		default:
			return -2;
		break;
	}
	// Configures the GPIO for PWM output
	PWM_GPIO_Config(&PWM_CONFIG->GPIOx_CONFIG);
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
 * @brief Copies the PWM Configuration from source to destination
 * @param dest Destination PWM Configuration Structure
 * @param src Source PWM Configuration Structure
 */
void PWM_Config_Copy(pwm_config_t* dest, const pwm_config_t* src){
	// Copy the Frequency
	dest->freq_Hz = src->freq_Hz;
	// Copy the Duty Cycle
	dest->duty_cycle = src->duty_cycle;
	// Copy the Mode
	dest->mode = src->mode;
	// Copy the Polarity
	dest->polarity = src->polarity;
	// Copy the Preload
	dest->preload = src->preload;
	// Copy the GPIO Configuration
	dest->GPIOx_CONFIG.MODE = src->GPIOx_CONFIG.MODE;
	dest->GPIOx_CONFIG.CNF = src->GPIOx_CONFIG.CNF;
	dest->GPIOx_CONFIG.GPIO = src->GPIOx_CONFIG.GPIO;
	dest->GPIOx_CONFIG.PIN = src->GPIOx_CONFIG.PIN;
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
