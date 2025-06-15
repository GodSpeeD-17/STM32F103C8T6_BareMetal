// Main Header
#include "pwm.h"
#include "pwm_handle.h"

/**
 * @brief Configures PWM
 * @param PWM_HANDLE Final Handle for future reference to PWM Configuration
 * @param PWM_CONFIG PWM Configuration Structure
 */
void PWM_Config(pwm_handle_t* PWM_HANDLE, pwm_config_t* PWM_CONFIG){
	// Deep Copy PWM Configuration
	PWM_Config_Copy(&PWM_HANDLE->PWM_CONFIG, PWM_CONFIG);
	// Fetch the Timer & Channel Mapping
	if(!PWM_Get_TIM_Mapping(&PWM_HANDLE->TIMx_CONFIG, &PWM_CONFIG->GPIOx_CONFIG))
		return -1;
	// Prescaler Based on PWM Frequency
	PWM_HANDLE->TIMx_CONFIG.prescaler = (RCC_Get_APB1Clock() / PWM_CONFIG->freq_Hz) - 1;
	// Default Timer Configuration for PWM
	PWM_Default_TIM_Config(PWM_HANDLE);
	// Configure Timer based on the PWM Configuration
	TIM_Config(&PWM_HANDLE->TIMx_CONFIG);
	// Channel Configuration
	switch(PWM_HANDLE->TIMx_CONFIG.channel){
		// Channel 1 Configuration
		case TIMx_CHANNEL_1:
			// Set the PWM Mode & Preload
			PWM_HANDLE->TIMx_CONFIG.TIM->CCMR1.REG |= ((PWM_CONFIG->mode << TIM_CCMR1_OC1M_Pos) |
													   (PWM_CONFIG->preload << TIM_CCMR1_OC1PE_Pos));
			// Set the Polarity	
			PWM_HANDLE->TIMx_CONFIG.TIM->CCER.REG |= (PWM_CONFIG->polarity << TIM_CCER_CC1P_Pos);											   
			// Duty Cycle
			PWM_HANDLE->TIMx_CONFIG.TIM->CCR1.CC1_OUT = PWM_CONFIG->duty_cycle;
		break;
		// Channel 2 Configuration
		case TIMx_CHANNEL_2:
			// Set the PWM Mode & Preload
			PWM_HANDLE->TIMx_CONFIG.TIM->CCMR1.REG |= ((PWM_CONFIG->mode << TIM_CCMR1_OC2M_Pos) |
													   (PWM_CONFIG->preload << TIM_CCMR1_OC2PE_Pos));
			// Set the Polarity	
			PWM_HANDLE->TIMx_CONFIG.TIM->CCER.REG |= (PWM_CONFIG->polarity << TIM_CCER_CC2P_Pos);
			// Duty Cycle
			PWM_HANDLE->TIMx_CONFIG.TIM->CCR2.CC2_OUT = PWM_CONFIG->duty_cycle;
		break;
		// Channel 3 Configuration
		case TIMx_CHANNEL_3:
			// Set the PWM Mode & Preload
			PWM_HANDLE->TIMx_CONFIG.TIM->CCMR2.REG |= ((PWM_CONFIG->mode << TIM_CCMR2_OC3M_Pos) |
													   (PWM_CONFIG->preload << TIM_CCMR2_OC3PE_Pos));
			// Set the Polarity	
			PWM_HANDLE->TIMx_CONFIG.TIM->CCER.REG |= (PWM_CONFIG->polarity << TIM_CCER_CC3P_Pos);
			// Duty Cycle
			PWM_HANDLE->TIMx_CONFIG.TIM->CCR3.CC3_OUT = PWM_CONFIG->duty_cycle;
		break;
		// Channel 4 Configuration
		case TIMx_CHANNEL_4:
			// Set the PWM Mode & Preload
			PWM_HANDLE->TIMx_CONFIG.TIM->CCMR2.REG |= ((PWM_CONFIG->mode << TIM_CCMR2_OC4M_Pos) |
													   (PWM_CONFIG->preload << TIM_CCMR2_OC4PE_Pos));
			// Set the Polarity	
			PWM_HANDLE->TIMx_CONFIG.TIM->CCER.REG |= (PWM_CONFIG->polarity << TIM_CCER_CC4P_Pos);
			// Duty Cycle
			PWM_HANDLE->TIMx_CONFIG.TIM->CCR4.CC4_OUT = PWM_CONFIG->duty_cycle;
		break;
		// Error Case
		default:
			return -2;
		break;
	}
	// Configures the GPIO for PWM output
	PWM_GPIO_Config(&PWM_CONFIG->GPIOx_CONFIG);
}

/**
 * @brief Enables the PWM
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Enable(pwm_handle_t* PWM_HANDLE){
	// Enable the Timer
	TIM_Enable(PWM_HANDLE->TIMx_CONFIG.TIM);
	// Enable the Channel
	TIM_Channel_Enable(PWM_HANDLE->TIMx_CONFIG.TIM, PWM_HANDLE->TIMx_CONFIG.channel);
}

/**
 * @brief Enables the PWM Channel
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Channel_Enable(pwm_handle_t* PWM_HANDLE){
	// Enable the Channel
	TIM_Channel_Enable(PWM_HANDLE->TIMx_CONFIG.TIM, PWM_HANDLE->TIMx_CONFIG.channel);
}

/**
 * @brief Disables the PWM
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Disable(pwm_handle_t* PWM_HANDLE){
	// Disable the Channel
	TIM_Channel_Disable(PWM_HANDLE->TIMx_CONFIG.TIM, PWM_HANDLE->TIMx_CONFIG.channel);
	// Disable the Timer
	TIM_Disable(PWM_HANDLE->TIMx_CONFIG.TIM);
}

/**
 * @brief Disables the PWM Channel
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Channel_Disable(pwm_handle_t* PWM_HANDLE){
	// Disable the Channel
	TIM_Channel_Disable(PWM_HANDLE->TIMx_CONFIG.TIM, PWM_HANDLE->TIMx_CONFIG.channel);
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