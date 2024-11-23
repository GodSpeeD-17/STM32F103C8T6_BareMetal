/***************************************************************************************
 *  File: timer.c
 *  Created on: 19/10/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

/*
  THEORY:
	|=> Refer Reference Manual (RM008) PDF Page 93 for Clock Tree Configuration
	|=> It is quite evident that, SYSCLK is passed to AHB Prescaler
	|
	|=> For General Purpose Timer refer Table Number 23 (PDF Page 166) (TIM2, TIM3, TIM4)
	|    SYSCLK [72 MHz] => AHB Prescaler (/1) [72 MHz] => APB1 Prescaler (/2) [36 MHz] => GP_TIMx Prescaler (x2) [72 MHz]
	|       |-> That is until AHB/APB2 Prescaler remain unchanged 
	|       |-> TIMx_CLK == SYSCLK == 72MHz
	|
	|=> Capture/Compare Register (CCR): 
	|    |-> Each timer channel has its own CCR (e.g., CCR1 for OC1, CCR2 for OC2, etc.) 
	|    |-> This register holds the value against which the timer counter is compared 
	|    |-> The value in the CCR determines when the timer output changes state
	|
	|=> PWM Mode 1 (TIMx_OCM_PWM_NORMAL): 
	|    |-> The output is high as long as the timer counter is less than the CCR value
	|
	|=> PWM Mode 2 (TIMx_OCM_PWM_INVERTED):
	|    |-> The output is high as long as the timer counter is greater than the CCR value
	|
	|=> Auto-Reload Register (ARR): 
	|    |-> This register sets the maximum value the timer counter can reach
	|    |-> When the counter exceeds this value, it resets back to zero, effectively defining the period of the PWM signal
	|
	|=> Timer Counter (CNT): 
	|    |-> This is the current value of the timer, which increments based on the configured prescaler and clock settings    
	|
	|=> Summary:
	|    |-> ARR + PSC sets the frequency of the PWM signal            
	|    |-> CCR determines the duty cycle of the PWM signal
	|
	|
	|=> FORMULA:
	|                                (Timer Frequency)
	|            PWM Frequency = -------------------------   [Hz]
	|                              (ARR + 1) * (PSC + 1)     
	|    where,
	|        Timer Frequency = ((SYSCLK)*(TIMx_PRE)) / ((AHB_PRE)*(APB1_PRE)) {72 MHz}
	|        ARR = GP_TIMx Auto Reload Register
	|        PSC = GP_TIMx Prescaler
	|
	|    After re-arranging,
	|                        (Timer Frequency)
	|            PSC = ------------------------------ - 1;
	|                    (PWM Frequency) * (ARR + 1)
	|
	|
	|--> GPT === General Purpose Timer
	|--> TO DO: Error Handling Uniformity for GP_TIMx
*/

// Main Library
#include "gpt.h"

/**
 * @brief Configure General Purpose GP_TIMx (Clock Source + Frequency)
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] arr_value ARR Value
 * @param[in] freq_Hz Timer Frequency (in Hz)
 * @param[in] count_value Timer Counter Value 
 * @note - Configures DIR is Up Counting
 * @note - Configures Edge Aligned Mode (Up counting or Down counting based upon `DIR`)
 */
void config_GPT(GPT_REG_STRUCT* GP_TIMx, uint16_t arr_value, uint32_t freq_Hz, uint16_t count_value){
	
	// Error Check
	if (freq_Hz == 0)
		return;

	// Set the prescaler value
	GP_TIMx->ARR = arr_value;

	// Calculate GP_TIMx Prescaler for desired frequency
	GP_TIMx->PSC = calc_GPT_PSC(freq_Hz, GP_TIMx->ARR);

	// Set the count value
	GP_TIMx->CNT = count_value;

	// Send an update event to reset the timer and apply settings
  	GP_TIMx->EGR.BIT.UG = BIT_SET;
}

/**
 * @brief Gets the GP Timer Clock Frequency
 * @param[in] GP_TIMx  `TIM2`, `TIM3`, `TIM4`
 * @note Refer the formula mentioned in .c file  & clock tree to get clear understanding
 */
uint32_t get_GPT_freq(GPT_REG_STRUCT* GP_TIMx){

	// Timer Frequency
	uint32_t timer_freq = 0x00;	

	// Retrieve Timer Source Clock Frequency
	timer_freq = (uint32_t) ((RCC->CFGR.BIT.PPRE1 == APB1_DIV_1)? (get_APB1_freq()) : (2 * get_APB1_freq()));

	// Consider ARR Value
	timer_freq /= (GP_TIMx->ARR + 1);

	// Consider Prescaler Value
	timer_freq /= (GP_TIMx->PSC + 1);

	// Return the Timer Frequency
	return timer_freq;
}

/**
 * @brief General Purpose Timer Delay
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] delayMs Number of milliseconds
 */
void GPT_delay_ms(GPT_REG_STRUCT* GP_TIMx, volatile uint32_t delayMs){

	// Update the Event Frequency at 1kHz
	if(get_GPT_freq(GP_TIMx) != FREQ_1kHz){
		// Set update event after 1ms (1kHz)
		set_GPT_freq(GP_TIMx, FREQ_1kHz);
	}

	// Iteration for Milliseconds
	while(delayMs--){

		// Wait till Update Flag is Set
		while(!(GP_TIMx->SR.BIT.UIF));

		// Clear the update flag
		GP_TIMx->SR.BIT.UIF = BIT_RESET;
	}
}
