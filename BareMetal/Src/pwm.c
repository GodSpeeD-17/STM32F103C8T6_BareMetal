/*
	THEORY:
	|=> Pulse Width Modulation (PWM) is used to create pseudo Analog Value from Digital Value
	|=> Main job is to provide an Average Voltage value which is Analog in nature but made up of Digital Signals
	|=> PWM is used in various applications like Motor Speed Control, LED Dimming
	|=> From experience, 10kHz - 100kHz is the best range of frequency where almost all the devices will work
	|=> From Datasheet and Formula, do not exceed 200kHz and do not go below 100Hz (Toy Servo Motor)
*/


// Main Header
#include "pwm.h"

/**
 * @brief Configure PWM Mode for General Purpose TIMx
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 * @param[in] pwm_mode  `TIMx_OCM_PWM_NORMAL`, `TIMx_OCM_PWM_INVERTED`
 * @param[in] preload_enable `PRELOAD_ENABLE`, `PRELOAD_DISABLE`
 */
void config_PWM_mode(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, TIMx_OCM_MODE pwm_mode, uint8_t preload_enable){
	
	// Error
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4)
		return;

	// Preload the value
	if(preload_enable == PRELOAD_ENABLE){
		// Enable Auto Reload of Timer
		GP_TIMx->CR1.BIT.ARPE = BIT_SET;
	}

	// Enable Event Updation on Overflow
	GP_TIMx->EGR.BIT.UG = BIT_SET;

	// Channel based Configuration
	switch(channel){
		
		case TIMx_CHANNEL_1:
			// Select the PWM Mode 
			GP_TIMx->CCMR1.BIT.OCM.OC1M = pwm_mode;
			// Enable Channel Preload
			GP_TIMx->CCMR1.BIT.OCM.OC1PE = BIT_SET;
		break;
		
		case TIMx_CHANNEL_2:
			// Select the PWM Mode
			GP_TIMx->CCMR1.BIT.OCM.OC2M = pwm_mode;
			// Enable Channel Preload
			GP_TIMx->CCMR1.BIT.OCM.OC2PE = BIT_SET;
		break;
		
		case TIMx_CHANNEL_3:
			// Select the PWM Mode
			GP_TIMx->CCMR2.BIT.OCM.OC3M = pwm_mode;
			// Enable Channel Preload
			GP_TIMx->CCMR2.BIT.OCM.OC3PE = BIT_SET;
		break;
		
		case TIMx_CHANNEL_4:
			// Select the PWM Mode
			GP_TIMx->CCMR2.BIT.OCM.OC4M = pwm_mode;
			// Enable Channel Preload
			GP_TIMx->CCMR2.BIT.OCM.OC4PE = BIT_SET;
		break;

		case TIMx_CHANNEL_ALL:
			// Select the PWM Mode
			GP_TIMx->CCMR1.BIT.OCM.OC1M = pwm_mode;
			GP_TIMx->CCMR1.BIT.OCM.OC2M = pwm_mode;
			GP_TIMx->CCMR2.BIT.OCM.OC3M = pwm_mode;
			GP_TIMx->CCMR2.BIT.OCM.OC4M = pwm_mode;
			// Enable Channel Preload
			GP_TIMx->CCMR1.BIT.OCM.OC1PE = BIT_SET;
			GP_TIMx->CCMR1.BIT.OCM.OC2PE = BIT_SET;
			GP_TIMx->CCMR2.BIT.OCM.OC3PE = BIT_SET;
			GP_TIMx->CCMR2.BIT.OCM.OC4PE = BIT_SET;
		break;
	}
}

/**
 * @brief Configure PWM related parameters for GP Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4` 
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 * @param[in] polarity  `TIMx_POL_ACTIVE_LOW`, `TIMx_POL_ACTIVE_HIGH`
 */
void set_PWM_polarity(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, uint8_t polarity){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5)
		return; 

	// Channel based Configuration
	switch(channel){
		
		case TIMx_CHANNEL_1:
			// Configure Active Polarity
			GP_TIMx->CCER.BIT.CC1P = polarity;
		break;
		
		case TIMx_CHANNEL_2:
			// Configure Active Polarity
			GP_TIMx->CCER.BIT.CC2P = polarity;
		break;
		
		case TIMx_CHANNEL_3:
			// Configure Active Polarity
			GP_TIMx->CCER.BIT.CC3P = polarity;
		break;
		
		case TIMx_CHANNEL_4:
			// Configure Active Polarity
			GP_TIMx->CCER.BIT.CC4P = polarity;
		break;

		case TIMx_CHANNEL_ALL:
			// Configure Active Polarity
			GP_TIMx->CCER.BIT.CC1P = polarity;
			GP_TIMx->CCER.BIT.CC2P = polarity;
			GP_TIMx->CCER.BIT.CC3P = polarity;
			GP_TIMx->CCER.BIT.CC4P = polarity;
		break;
	}	
}

/**
 * @brief Updates the Duty Cycle for the specified TIMx and Channel
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4` 
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 * @param[in] duty_cycle Duty Cycle Value in (%) 
 */
void set_PWM_duty_cycle(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, uint8_t duty_cycle){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5)
		return; 

	// Wrap duty cycle    
	duty_cycle = (duty_cycle > MAX_DUTY_CYCLE) ? MAX_DUTY_CYCLE : duty_cycle;

	// Channel based Configuration
	switch(channel){
		
		case TIMx_CHANNEL_1:
			// Store the Duty Cycle Value
			GP_TIMx->CCR1.CC1_OUT = (uint16_t)((((GP_TIMx->ARR + 1) * duty_cycle) / 100) - 1);
		break;
		
		case TIMx_CHANNEL_2:
			// Store the Duty Cycle Value
			GP_TIMx->CCR2.CC2_OUT = (uint16_t)((((GP_TIMx->ARR + 1) * duty_cycle) / 100) - 1);
		break;
		
		case TIMx_CHANNEL_3:
			// Store the Duty Cycle Value
			GP_TIMx->CCR3.CC3_OUT = (uint16_t)((((GP_TIMx->ARR + 1) * duty_cycle) / 100) - 1);
		break;
		
		case TIMx_CHANNEL_4:
			// Store the Duty Cycle Value
			GP_TIMx->CCR4.CC4_OUT = (uint16_t)((((GP_TIMx->ARR + 1) * duty_cycle) / 100) - 1);
		break;

		case TIMx_CHANNEL_ALL:
			// Store the Duty Cycle Value
			GP_TIMx->CCR1.CC1_OUT = (uint16_t)((((GP_TIMx->ARR + 1) * duty_cycle) / 100) - 1);
			GP_TIMx->CCR2.CC2_OUT = (uint16_t)((((GP_TIMx->ARR + 1) * duty_cycle) / 100) - 1);
			GP_TIMx->CCR3.CC3_OUT = (uint16_t)((((GP_TIMx->ARR + 1) * duty_cycle) / 100) - 1);
			GP_TIMx->CCR4.CC4_OUT = (uint16_t)((((GP_TIMx->ARR + 1) * duty_cycle) / 100) - 1);
		break;
	}
}

