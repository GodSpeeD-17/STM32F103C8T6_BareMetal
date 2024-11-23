/***************************************************************************************
 *  File: pwm.c
 *  Created on: 26/10/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

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
static void config_PWM_mode(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, TIMx_OCM_MODE pwm_mode, uint8_t preload_enable){

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
static void set_PWM_polarity(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, uint8_t polarity){

	// Channel based Configuration
	switch(channel){
		
		case TIMx_CHANNEL_1:
			// Configure Input Polarity
			GP_TIMx->CCER.BIT.CC1P = polarity;
		break;
		
		case TIMx_CHANNEL_2:
			// Configure Input Polarity
			GP_TIMx->CCER.BIT.CC2P = polarity;
		break;
		
		case TIMx_CHANNEL_3:
			// Configure Input Polarity
			GP_TIMx->CCER.BIT.CC3P = polarity;
		break;
		
		case TIMx_CHANNEL_4:
			// Configure Input Polarity
			GP_TIMx->CCER.BIT.CC4P = polarity;
		break;

		case TIMx_CHANNEL_ALL:
			// Configure Input Polarity
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
static void set_PWM_duty(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, uint8_t duty_cycle){

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

/**
 * @brief Configures the parameters necessary for PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
void config_PWM(pwm_config_t* PWMx){
	
	// Error Handling
	
	// Configure Timer
	config_GPT(&PWMx->GPT_CONFIGx);

	// Wrap duty cycle    
	PWMx->duty_cycle = (PWMx->duty_cycle > MAX_DUTY_CYCLE) ? MAX_DUTY_CYCLE : PWMx->duty_cycle;
	// Store the CCRx Value
	uint16_t CCRx_VALUE = ((((PWMx->GPT_CONFIGx.GP_TIMx->ARR + 1) * PWMx->duty_cycle) / 100) - 1);

	// Channel based Configuration
	switch(PWMx->GPT_CONFIGx.channel){
		
		case TIMx_CHANNEL_1:
			// PWM Mode + Enable Channel Preload
			PWMx->GPT_CONFIGx.GP_TIMx->CCMR1.REG |= (uint32_t)(((PWMx->pwm_mode) << 4) | (1 << 3));
			// Polarity Configuration
			PWMx->GPT_CONFIGx.GP_TIMx->CCER.BIT.CC1P = PWMx->polarity;
			// Store the Duty Cycle Value
			PWMx->GPT_CONFIGx.GP_TIMx->CCR1.CC1_OUT = CCRx_VALUE;
		break;
		
		case TIMx_CHANNEL_2:
			// PWM Mode + Enable Channel Preload
			PWMx->GPT_CONFIGx.GP_TIMx->CCMR1.REG |= (uint32_t)(((PWMx->pwm_mode) << 12) | (1 << 11));
			// Polarity Configuration
			PWMx->GPT_CONFIGx.GP_TIMx->CCER.BIT.CC2P = PWMx->polarity;
			// Store the Duty Cycle Value
			PWMx->GPT_CONFIGx.GP_TIMx->CCR2.CC2_OUT = CCRx_VALUE;
		break;
		
		case TIMx_CHANNEL_3:
			// PWM Mode + Enable Channel Preload
			PWMx->GPT_CONFIGx.GP_TIMx->CCMR2.REG |= (uint32_t)(((PWMx->pwm_mode) << 4) | (1 << 3));
			// Polarity Configuration
			PWMx->GPT_CONFIGx.GP_TIMx->CCER.BIT.CC3P = PWMx->polarity;
			// Store the Duty Cycle Value
			PWMx->GPT_CONFIGx.GP_TIMx->CCR3.CC3_OUT = CCRx_VALUE;
		break;
		
		case TIMx_CHANNEL_4:
			// PWM Mode + Enable Channel Preload
			PWMx->GPT_CONFIGx.GP_TIMx->CCMR2.REG |= (uint32_t)(((PWMx->pwm_mode) << 12) | (1 << 11));
			// Polarity Configuration
			PWMx->GPT_CONFIGx.GP_TIMx->CCER.BIT.CC4P = PWMx->polarity;
			// Store the Duty Cycle Value
			PWMx->GPT_CONFIGx.GP_TIMx->CCR4.CC4_OUT = CCRx_VALUE;
		break;

		case TIMx_CHANNEL_ALL:
			// PWM Mode + Enable Channel Preload
			PWMx->GPT_CONFIGx.GP_TIMx->CCMR1.REG |= (uint32_t)((((PWMx->pwm_mode) << 12) | (1 << 11)) | (((PWMx->pwm_mode) << 4) | (1 << 3)));
			PWMx->GPT_CONFIGx.GP_TIMx->CCMR2.REG |= (uint32_t)((((PWMx->pwm_mode) << 12) | (1 << 11)) | (((PWMx->pwm_mode) << 4) | (1 << 3)));
			// Polarity Configuration
			PWMx->GPT_CONFIGx.GP_TIMx->CCER.REG |=  (uint32_t)((PWMx->polarity << 13) | (PWMx->polarity << 9) | (PWMx->polarity << 5) | (PWMx->polarity << 1));
			// Store the Duty Cycle Value
			PWMx->GPT_CONFIGx.GP_TIMx->CCR1.CC1_OUT = CCRx_VALUE;
			PWMx->GPT_CONFIGx.GP_TIMx->CCR2.CC2_OUT = CCRx_VALUE;
			PWMx->GPT_CONFIGx.GP_TIMx->CCR3.CC3_OUT = CCRx_VALUE;
			PWMx->GPT_CONFIGx.GP_TIMx->CCR4.CC4_OUT = CCRx_VALUE;
		break;
	}
}

/**
 * @brief Sets the duty cycle for PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
void set_PWM_duty_cycle(pwm_config_t* PWMx){

	// Disable the Timer
	disable_GPT(&PWMx->GPT_CONFIGx);

	// Wrap duty cycle    
	PWMx->duty_cycle = (PWMx->duty_cycle > MAX_DUTY_CYCLE) ? MAX_DUTY_CYCLE : PWMx->duty_cycle;
	// Store the CCRx Value
	uint16_t CCRx_VALUE = ((((PWMx->GPT_CONFIGx.GP_TIMx->ARR + 1) * PWMx->duty_cycle) / 100) - 1);

	// Channel based Configuration
	switch(PWMx->GPT_CONFIGx.channel){
		
		case TIMx_CHANNEL_1:
			// Store the Duty Cycle Value
			PWMx->GPT_CONFIGx.GP_TIMx->CCR1.CC1_OUT = CCRx_VALUE;
		break;
		
		case TIMx_CHANNEL_2:
			// Store the Duty Cycle Value
			PWMx->GPT_CONFIGx.GP_TIMx->CCR2.CC2_OUT = CCRx_VALUE;
		break;
		
		case TIMx_CHANNEL_3:
			// Store the Duty Cycle Value
			PWMx->GPT_CONFIGx.GP_TIMx->CCR3.CC3_OUT = CCRx_VALUE;
		break;
		
		case TIMx_CHANNEL_4:
			// Store the Duty Cycle Value
			PWMx->GPT_CONFIGx.GP_TIMx->CCR4.CC4_OUT = CCRx_VALUE;
		break;

		case TIMx_CHANNEL_ALL:
			// Store the Duty Cycle Value
			PWMx->GPT_CONFIGx.GP_TIMx->CCR1.CC1_OUT = CCRx_VALUE;
			PWMx->GPT_CONFIGx.GP_TIMx->CCR2.CC2_OUT = CCRx_VALUE;
			PWMx->GPT_CONFIGx.GP_TIMx->CCR3.CC3_OUT = CCRx_VALUE;
			PWMx->GPT_CONFIGx.GP_TIMx->CCR4.CC4_OUT = CCRx_VALUE;
		break;
	}

	// Update Event
	update_GPT_params(&PWMx->GPT_CONFIGx);

	// Enable the Timer
	enable_GPT(&PWMx->GPT_CONFIGx);

}
