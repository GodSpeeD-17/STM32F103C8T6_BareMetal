/***************************************************************************************
 *  File: gpt.c
 *  Created on: 23/11/2024
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
 * @brief Configures the General Purpose Timer (GPT)
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
void config_GPT(gpt_config_t* GPT_CONFIGx){
	
	// Error Handling
	if(!IS_VALID_GPT_CONFIG_STRUCT(GPT_CONFIGx))
		return;

	// Enable Clock
	enable_GPT_clk(GPT_CONFIGx);
	// Reset the GP_TIMx
	reset_GPT(GPT_CONFIGx);
	// Disable the Timer
	disable_GPT(GPT_CONFIGx);

	// Update disable
	GPT_CONFIGx->GP_TIMx->CR1.REG |= (1 << 1);

	// Set Auto Reload Value (ARR)
	GPT_CONFIGx->GP_TIMx->ARR = GPT_CONFIGx->auto_reload_value;
	// Calculate updated PSC Value
	GPT_CONFIGx->GP_TIMx->PSC = calc_GPT_PSC(GPT_CONFIGx->frequency_Hz, GPT_CONFIGx->auto_reload_value);
	// Set Initial Count Value (CNT)
	GPT_CONFIGx->GP_TIMx->CNT = GPT_CONFIGx->count;
	// Centre-Aligned Mode + Direction + Auto Reload Preload Selection
	GPT_CONFIGx->GP_TIMx->CR1.REG |= (uint32_t)(((GPT_CONFIGx->auto_reload_preload & 0x01)<< 7) | ((GPT_CONFIGx->cms_mode & 0x03) << 5) | ((GPT_CONFIGx->direction & 0x01)<< 4) | ((GPT_CONFIGx->one_pulse & 0x01) << 3));
	
	// Update enable
	GPT_CONFIGx->GP_TIMx->CR1.REG &= ~(1 << 1);

	// IRQ Configuration
	if(GPT_CONFIGx->enable_IRQ == TIMx_IRQ_ENABLE){
		// Enable NVIC Interrupt
    	enable_NVIC_IRQ(get_TIMx_IRQn(GPT_CONFIGx->GP_TIMx));
    	// Enable Timer Interrupt
    	GPT_CONFIGx->GP_TIMx->DIER.REG |= (1 << 0);
	}

	// Update the GPT
	update_GPT_params(GPT_CONFIGx);
}

/**
 * @brief Gets the GP Timer Clock Frequency
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
uint32_t get_GPT_freq(gpt_config_t* GPT_CONFIGx){
	// Timer Frequency
	uint32_t timer_freq = 0x00;	
	// Retrieve Timer Source Clock Frequency
	timer_freq = (uint32_t) ((RCC->CFGR.BIT.PPRE1 == APB1_DIV_1)? (get_APB1_freq()) : (2 * get_APB1_freq()));
	// Consider ARR Value
	timer_freq /= (GPT_CONFIGx->GP_TIMx->ARR + 1);
	// Consider Prescaler Value
	timer_freq /= (GPT_CONFIGx->GP_TIMx->PSC + 1);
	// Return the Timer Frequency
	return timer_freq;
}

/**
 * @brief Updates the GP Timer Clock Frequency
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 * @param[in] freq_Hz Updated Timer Frequency
 */
__attribute__((always_inline)) inline void update_GPT_freq(gpt_config_t* GPT_CONFIGx, uint32_t freq_Hz){
	// Error Check
	if(!IS_VALID_GPT_FREQ(freq_Hz))
		return;
	// Calculate updated PSC Value
	GPT_CONFIGx->GP_TIMx->PSC = calc_GPT_PSC(freq_Hz, GPT_CONFIGx->GP_TIMx->ARR);
}

/**
 * @brief General Purpose Timer Delay
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 * @param[in] delayMs Number of milliseconds
 */
void GPT_delay_ms(gpt_config_t* GPT_CONFIGx, volatile uint32_t delayMs){
	// Update the Event Frequency at 1kHz
	if(get_GPT_freq(GPT_CONFIGx) != FREQ_1kHz){
		// Disable Timer
		disable_GPT(GPT_CONFIGx);
		// Set update event after 1ms (1kHz)
		update_GPT_freq(GPT_CONFIGx, FREQ_1kHz);
		// Update the Parameters
		update_GPT_params(GPT_CONFIGx);
		// Enable Timer
		enable_GPT(GPT_CONFIGx);
	}

	// Iteration for Milliseconds
	while(delayMs--){
		// Wait till Update Flag is Set
		while(!(GPT_CONFIGx->GP_TIMx->SR.REG & 0x01));
		// Clear the update flag
		GPT_CONFIGx->GP_TIMx->SR.REG &= ~BIT_SET;
	}
}
