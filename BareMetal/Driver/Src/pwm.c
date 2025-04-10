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
 * @brief Configures the parameters necessary for PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 */
void PWM_config(pwm_config_t* PWMx){

	// Configure GPIO 
	GPIO_config(PWMx->TIM_CONFIGx->GPIO_CONFIGx);

	// Configure Timer
	config_GPT(PWMx->TIM_CONFIGx);

	// Wrap duty cycle
	PWM_DUTY_CYCLE_WRAP(PWMx);
	// Store the CCRx Value
	uint16_t CCRx_VALUE = PWM_calc_CCRx(PWMx);

	// Channel 1
	if (PWMx->TIM_CONFIGx->channel & TIMx_CHANNEL_1){
		// PWM Mode + Enable Channel Preload for Channel 1
		PWMx->TIM_CONFIGx->TIMx->CCMR1.REG |= (uint32_t)(((PWMx->pwm_mode & 0x07) << 4) | ((PWMx->pwm_channel_preload & 0x01) << 3));
		// Polarity Configuration
		PWMx->TIM_CONFIGx->TIMx->CCER.BIT.CC1P = PWMx->polarity;
		// Store the Duty Cycle Value
		PWMx->TIM_CONFIGx->TIMx->CCR1.CC1_OUT = CCRx_VALUE;
	}

	// Channel 2
	if (PWMx->TIM_CONFIGx->channel & TIMx_CHANNEL_2){
		// PWM Mode + Enable Channel Preload for Channel 2
		PWMx->TIM_CONFIGx->TIMx->CCMR1.REG |= (uint32_t)(((PWMx->pwm_mode & 0x07) << 12) | ((PWMx->pwm_channel_preload & 0x01) << 11));
		// Polarity Configuration
		PWMx->TIM_CONFIGx->TIMx->CCER.BIT.CC2P = PWMx->polarity;
		// Store the Duty Cycle Value
		PWMx->TIM_CONFIGx->TIMx->CCR2.CC2_OUT = CCRx_VALUE;
	}

	// Channel 3
	if (PWMx->TIM_CONFIGx->channel & TIMx_CHANNEL_3){
		// PWM Mode + Enable Channel Preload for Channel 3
		PWMx->TIM_CONFIGx->TIMx->CCMR2.REG |= (uint32_t)(((PWMx->pwm_mode & 0x07) << 4) | ((PWMx->pwm_channel_preload & 0x01) << 3));
		// Polarity Configuration
		PWMx->TIM_CONFIGx->TIMx->CCER.BIT.CC3P = PWMx->polarity;
		// Store the Duty Cycle Value
		PWMx->TIM_CONFIGx->TIMx->CCR3.CC3_OUT = CCRx_VALUE;
	}

	// Channel 4
	if (PWMx->TIM_CONFIGx->channel & TIMx_CHANNEL_4){
		// PWM Mode + Enable Channel Preload for Channel 4
		PWMx->TIM_CONFIGx->TIMx->CCMR2.REG |= (uint32_t)(((PWMx->pwm_mode & 0x07) << 12) | ((PWMx->pwm_channel_preload & 0x01) << 11));
		// Polarity Configuration
		PWMx->TIM_CONFIGx->TIMx->CCER.BIT.CC4P = PWMx->polarity;
		// Store the Duty Cycle Value
		PWMx->TIM_CONFIGx->TIMx->CCR4.CC4_OUT = CCRx_VALUE;
	}
}

/**
 * @brief Sets the duty cycle for PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 * @note Use this function only when single channel is used for PWM configuration
 */
void PWM_setDutyCycle(pwm_config_t* PWMx){

	// Stop the PWM
	PWM_stop(PWMx);
	// Wrap duty cycle
	PWM_DUTY_CYCLE_WRAP(PWMx);
	// Store the CCRx Value
	uint16_t CCRx_VALUE = PWM_calc_CCRx(PWMx);

	// Channel based configuration to store duty cycle value
	if (PWMx->TIM_CONFIGx->channel & TIMx_CHANNEL_1)
		PWMx->TIM_CONFIGx->TIMx->CCR1.CC1_OUT = CCRx_VALUE;
	if (PWMx->TIM_CONFIGx->channel & TIMx_CHANNEL_2)
		PWMx->TIM_CONFIGx->TIMx->CCR2.CC2_OUT = CCRx_VALUE;
	if (PWMx->TIM_CONFIGx->channel & TIMx_CHANNEL_3)
		PWMx->TIM_CONFIGx->TIMx->CCR3.CC3_OUT = CCRx_VALUE;
	if (PWMx->TIM_CONFIGx->channel & TIMx_CHANNEL_4)
		PWMx->TIM_CONFIGx->TIMx->CCR4.CC4_OUT = CCRx_VALUE;
	
	// Update Event
	update_GPT_params(PWMx->TIM_CONFIGx);
	// Start the PWM
	PWM_start(PWMx);
}

/**
 * @brief Sets the duty cycle for PWM
 * @param[in] PWMx `pwm_config_t` The structure containing PWM Configuration
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
void PWM_setMultiChannelDutyCycle(pwm_config_t* PWMx, uint8_t channel){

	// Stop the PWM
	PWM_stopMultiChannel(PWMx, channel);

	// Wrap duty cycle
	PWM_DUTY_CYCLE_WRAP(PWMx);
	// Store the CCRx Value
	uint16_t CCRx_VALUE = PWM_calc_CCRx(PWMx);

	// Channel based configuration to store duty cycle value
	if((PWMx->TIM_CONFIGx->channel & channel) == TIMx_CHANNEL_1)
		PWMx->TIM_CONFIGx->TIMx->CCR1.CC1_OUT = CCRx_VALUE;
	if((PWMx->TIM_CONFIGx->channel & channel) == TIMx_CHANNEL_2)
		PWMx->TIM_CONFIGx->TIMx->CCR2.CC2_OUT = CCRx_VALUE;
	if((PWMx->TIM_CONFIGx->channel & channel) == TIMx_CHANNEL_3)
		PWMx->TIM_CONFIGx->TIMx->CCR3.CC3_OUT = CCRx_VALUE;
	if((PWMx->TIM_CONFIGx->channel & channel) == TIMx_CHANNEL_4)
		PWMx->TIM_CONFIGx->TIMx->CCR4.CC4_OUT = CCRx_VALUE;

	// Update Event
	update_GPT_params(PWMx->TIM_CONFIGx);

	// Start the PWM
	PWM_startMultiChannel(PWMx, channel);
}
