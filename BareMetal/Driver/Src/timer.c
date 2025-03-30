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
	|    SYSCLK [72 MHz] => AHB Prescaler (/1) [72 MHz] => APB1 Prescaler (/2) [36 MHz] => TIMx Prescaler (x2) [72 MHz]
	|       |-> That is until AHB/APB2 Prescaler remain unchanged 
	|       |-> TIMx_CLK == SYSCLK == 72MHz
	|
	|=> Capture/Compare Register (CCR): 
	|    |-> Each timer channel has its own CCRx (e.g., CCR1 for OC1, CCR2 for OC2, etc.) 
	|    |-> This register holds the value against which the timer counter is compared 
	|    |-> The value in the CCRx determines when the timer output changes OCx state
	|    |-> The active CCRx contains the value to be compared to the TIMx_CNT and signaled on OCx output
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
	|        ARR = TIMx Auto Reload Register
	|        PSC = TIMx Prescaler
	|
	|    After re-arranging,
	|                        (Timer Frequency)
	|            PSC = ------------------------------ - 1;
	|                    (PWM Frequency) * (ARR + 1)
	|
	|
	|--> TIMx === General Purpose Timer
	|--> TO DO: Error Handling Uniformity for TIMx
*/

// Main Library
#include "timer.h"

/**
 * @brief Configures the General Purpose Timer (TIMx)
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 */
void TIM_config(timer_config_t* TIM_CONFIGx){
	// Enable APBx Clock for Timer
	TIM_clk_enable(TIM_CONFIGx);
	// Reset the Timer
	TIM_reset(TIM_CONFIGx);
	// Disable the Timer
	TIM_disable(TIM_CONFIGx);
	// Disable Update Event
	TIM_CONFIGx->TIMx->CR1.REG |= TIM_CR1_UDIS;
	// Auto Reload Value
	TIM_CONFIGx->TIMx->ARR = TIM_CONFIGx->auto_reload;
	// Prescaler Value
	TIM_CONFIGx->TIMx->PSC = TIM_CONFIGx->prescaler;
	// Initial Count Value
	TIM_CONFIGx->TIMx->CNT = TIM_CONFIGx->count;
	// Auto Reload Preload Enable
	TIM_CONFIGx->TIMx->CR1.REG |= (((TIM_CONFIGx->arpe & 0x01)<< TIM_CR1_ARPE_Pos) | \
									// Centre-Aligned Mode 
								   ((TIM_CONFIGx->cms_mode & 0x03) << TIM_CR1_CMS_Pos) | \
									// Direction 
								   ((TIM_CONFIGx->direction & 0x01)<< TIM_CR1_DIR_Pos) | \
									// One Pulse Mode 
								   ((TIM_CONFIGx->one_pulse & 0x01) << TIM_CR1_OPM_Pos));
	// Enable Update Event
	TIM_CONFIGx->TIMx->CR1.REG &= ~TIM_CR1_UDIS;
	// IRQ Configuration
	if(TIM_CONFIGx->enable_IRQ == TIMx_IRQ_ENABLE){
		// Global Interrupt Disable
		__disable_irq();
		// Enable NVIC Interrupt
    	NVIC_IRQ_enable(TIM_get_IRQn(TIM_CONFIGx->TIMx));
    	// Enable Timer Interrupt
    	TIM_CONFIGx->TIMx->DIER.REG |= TIM_DIER_UIE;
		// Global Interrupt Enable
		__enable_irq();
	}
	// Update the Timer
	TIM_updateParams(TIM_CONFIGx);
}

/**
 * @brief Gets the GP Timer Clock Frequency
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @returns Timer Frequency	
 */
uint32_t TIM_getFreq(timer_config_t* TIM_CONFIGx){
	// Timer Frequency
	uint32_t timer_freq = 0x00;	
	// Retrieve Timer Source Clock Frequency
	timer_freq = (uint32_t) (((RCC->CFGR.REG & RCC_CFGR_PPRE1)== RCC_CFGR_PPRE1_DIV1)? (APB1Clock) : (2 * APB1Clock));
	// Consider ARR Value
	timer_freq /= (TIM_CONFIGx->TIMx->ARR + 1);
	// Consider Prescaler Value
	timer_freq /= (TIM_CONFIGx->TIMx->PSC + 1);
	// Return the Timer Frequency
	return timer_freq;
}

/**
 * @brief Updates the GP Timer Clock Frequency
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @param[in] freq_Hz Updated Timer Frequency
 */
__STATIC_INLINE__ void update_TIM_freq(timer_config_t* TIM_CONFIGx, uint32_t freq_Hz){
	// Calculate updated PSC Value
	TIM_CONFIGx->TIMx->PSC = TIM_calcPrescaler(freq_Hz, TIM_CONFIGx->TIMx->ARR);
}

/**
 * @brief General Purpose Timer Delay
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @param[in] delayMs Number of milliseconds
 */
void TIM__delay_ms(timer_config_t* TIM_CONFIGx, volatile uint32_t delayMs){
	// Update the Event Frequency at 1kHz
	if(TIM_getFreq(TIM_CONFIGx) != FREQ_1kHz){
		// Disable Timer
		TIM_disable(TIM_CONFIGx);
		// Set update event after 1ms (1kHz)
		update_TIM_freq(TIM_CONFIGx, FREQ_1kHz);
		// Update the Parameters
		TIM_updateParams(TIM_CONFIGx);
		// Enable Timer
		TIM_enable(TIM_CONFIGx);
	}
	// Iteration for Milliseconds
	while(delayMs--){
		// Wait till Update Flag is Set
		while(!(TIM_CONFIGx->TIMx->SR.REG & TIM_SR_UIF));
		// Clear the update flag
		TIM_CONFIGx->TIMx->SR.REG &= ~TIM_SR_UIF;
	}
}

/**
 * @brief Creates a delay using Timer
 * @param[in] TIM_CONFIGx Timer Configuration Structure
 * @param[in] delayUs Number of microseconds to delay
 * @note Assuming, Timer is already configured for 1MHz
 */
void TIM_delay_us(timer_config_t* TIM_CONFIGx, volatile uint32_t delayUs){
	// Configure Delay Time
	TIM_CONFIGx->TIMx->ARR = delayUs - 1;
	// Enable One Pulse Mode + Timer
	TIM_CONFIGx->TIMx->CR1.REG |= (TIM_CR1_OPM | TIM_CR1_CEN);
	// Wait until Timer is Enabled
	while(TIM_CONFIGx->TIMx->CR1.REG & TIM_CR1_CEN);
}

/**
 * @brief Creates a delay using Timer
 * @param[in] TIM_CONFIGx Timer Configuration Structure 
 * @param[in] delayMs Number of milliseconds to delay
 * @note Depends upon `TIM_delay_us()`
 */
void TIM_delay_ms(timer_config_t* TIM_CONFIGx, volatile uint32_t delayMs){
	// Iteration for each number of milliseconds
	while(delayMs--){
		TIM_delay_us(TIM_CONFIGx, 1000);
	}
}
