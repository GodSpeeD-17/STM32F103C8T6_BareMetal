/***************************************************************************************
 *  File: timer.c
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
	|=> PWM Mode 1 (TIMx_OCM_PWM_NORMAL): ***
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
	|--> TIMx === General Purpose Timer
*/

// Main Library
#include "timer.h"
// APB1 Clock Frequency
#include "rcc.h"
// IRQ Enable/Disable
#include "nvic.h"

// Lookup Table for Timer IRQn
static const uint8_t TIMx_IRQn[3] = {
	TIM2_IRQn,
	TIM3_IRQn,
	TIM4_IRQn
};

/**
 * @brief Calculates the Prescaler Value based upon ARR Value provided
 * @param[in] freq_Hz Frequency (in Hz)
 * @param[in] arr_value Auto-Reload Register Value
 * @return Prescaler Value
 */
uint16_t TIM_Calc_Prescaler(uint32_t freq_Hz, uint16_t arr_value){
	// Final Value
	uint32_t prescaler_value = RCC_Get_APB1Clock();
	// Calculate the Timer Frequency
	if((RCC->CFGR.REG & RCC_CFGR_PPRE1) != RCC_CFGR_PPRE1_DIV1)
		prescaler_value = (RCC_Get_APB1Clock() << 1);
	// Update the value based upon the desired frequency
	prescaler_value /= freq_Hz;
	// Update the value based upon the ARR Value
	prescaler_value /= (arr_value + 1);
	// Final Calculated Value
	return (uint16_t)(prescaler_value - 1);
} 

/**
 * @brief Configures the default parameters for TIM_CONFIGx
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @note - TIM & Channel should be already configured
 * @note - This loads frequency as 10kHz
 */
void TIM_10kHz_Load_Default(timer_config_t* TIM_CONFIGx){
	// Configure Auto-Reload Register Value
	TIM_CONFIGx->auto_reload = TIMx_DEFAULT_10kHz_ARR;
	// Configure Prescaler Value
	TIM_CONFIGx->prescaler = TIMx_DEFAULT_10kHz_PSC;
	// Configure Timer Count Value
	TIM_CONFIGx->count = TIMx_DEFAULT_CNT;
	// CMS Mode Selection (Edge Mode Selection)
	TIM_CONFIGx->cms_mode = TIMx_CMS_EDGE;
	// Counting Direction (Up Counting)
	TIM_CONFIGx->direction = TIMx_DIR_COUNT_UP;
	// Auto Reload-Preload Enable
	TIM_CONFIGx->arpe = TIMx_ARPE_ENABLE;
	// One Pulse Mode (OFF)
	TIM_CONFIGx->one_pulse = TIMx_OPM_DISABLE;
}

/**
 * @brief Configures the default parameters for TIM_CONFIGx
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @note - TIM & Channel should be already configured
 * @note - This loads frequency as 1MHz
 */
void TIM_1MHz_Load_Default(timer_config_t* TIM_CONFIGx){
	// Configure Auto-Reload Register Value
	TIM_CONFIGx->auto_reload = TIMx_DEFAULT_1MHz_ARR;
	// Configure Prescaler Value
	TIM_CONFIGx->prescaler = TIMx_DEFAULT_1MHz_PSC;
	// Configure Timer Count Value
	TIM_CONFIGx->count = TIMx_DEFAULT_CNT;
	// CMS Mode Selection (Edge Mode Selection)
	TIM_CONFIGx->cms_mode = TIMx_CMS_EDGE;
	// Counting Direction (Up Counting)
	TIM_CONFIGx->direction = TIMx_DIR_COUNT_UP;
	// Auto Reload-Preload Enable
	TIM_CONFIGx->arpe = TIMx_ARPE_ENABLE;
	// One Pulse Mode (OFF)
	TIM_CONFIGx->one_pulse = TIMx_OPM_DISABLE;	
}

/**
 * @brief Configures the General Purpose Timer (TIMx)
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 */
void TIM_Config(timer_config_t* TIM_CONFIGx){
	// Enable Clock for Timer
	TIM_Clk_Enable(TIM_CONFIGx->TIM);
	// Reset the Timer
	TIM_Reset(TIM_CONFIGx->TIM);
	// Disable the Timer
	TIM_Disable(TIM_CONFIGx->TIM);
	// Disable Update Event
	TIM_UEV_Disable(TIM_CONFIGx->TIM);
	// Auto Reload Value
	TIM_CONFIGx->TIM->ARR = TIM_CONFIGx->auto_reload;
	// Prescaler Value
	TIM_CONFIGx->TIM->PSC = TIM_CONFIGx->prescaler;
	// Initial Count Value
	TIM_CONFIGx->TIM->CNT = TIM_CONFIGx->count;
	// Auto Reload Preload Enable
	TIM_CONFIGx->TIM->CR1.REG |= (((TIM_CONFIGx->arpe & 0x01)<< TIM_CR1_ARPE_Pos) | \
									// Centre-Aligned Mode 
								   ((TIM_CONFIGx->cms_mode & 0x03) << TIM_CR1_CMS_Pos) | \
									// Direction 
								   ((TIM_CONFIGx->direction & 0x01)<< TIM_CR1_DIR_Pos) | \
									// One Pulse Mode (OPM)
								   ((TIM_CONFIGx->one_pulse & 0x01) << TIM_CR1_OPM_Pos));
	// Enable Update Event
	TIM_UEV_Enable(TIM_CONFIGx->TIM);
	// Update the Timer
	TIM_Update_Parameters(TIM_CONFIGx->TIM);
}

/**
 * @brief Gets the GP Timer Clock Frequency
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @returns Timer Frequency	(in Hz)
 */
uint32_t TIM_Get_Freq(TIM_REG_STRUCT* TIMx){
	// Timer Frequency
	uint32_t timer_freq = RCC_Get_APB1Clock();
	// APB1_Prescaler != 1 --> 2 * APB1Clock
	if((RCC->CFGR.REG & RCC_CFGR_PPRE1) != RCC_CFGR_PPRE1_DIV1)
		timer_freq <<= 1;
	// Consider ARR Value
	timer_freq /= (TIMx->ARR + 1);
	// Consider Prescaler Value
	timer_freq /= (TIMx->PSC + 1);
	// Return the Timer Frequency
	return timer_freq;
}

/**
 * @brief General Purpose Timer Delay
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @param[in] delayMs Number of milliseconds
 */
static void TIM__delay_ms(timer_config_t* TIM_CONFIGx, volatile uint32_t delayMs){
	// Update the Event Frequency at 1kHz
	if(TIM_Get_Freq(TIM_CONFIGx) != FREQ_1kHz){
		// Disable Timer
		TIM_Disable(TIM_CONFIGx);
		// Set update event after 1ms (1kHz)
		update_TIM_freq(TIM_CONFIGx, FREQ_1kHz);
		// Update the Parameters
		TIM_Update_Parameters(TIM_CONFIGx);
		// Enable Timer
		TIM_Enable(TIM_CONFIGx);
	}
	// Iteration for Milliseconds
	while(delayMs--){
		// Wait till Update Flag is Set
		while(!(TIM_CONFIGx->TIM->SR.REG & TIM_SR_UIF));
		// Clear the update flag
		TIM_CONFIGx->TIM->SR.REG &= ~TIM_SR_UIF;
	}
}

/**
 * @brief Creates a delay using Timer
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] delayUs Number of microseconds to delay
 * @note Assuming, Timer is already configured for 1MHz
 */
void TIM_delay_us(TIM_REG_STRUCT* TIMx, uint32_t delayUs){
	// Disable the Timer
	TIM_Disable(TIMx);
	// Configure Delay Time
	TIMx->ARR = delayUs - 1;
	// Enable One Pulse Mode + Timer
	TIMx->CR1.REG |= (TIM_CR1_OPM | TIM_CR1_CEN);
	// Wait until Timer is Enabled
	while(TIMx->CR1.REG & TIM_CR1_CEN);
}

/**
 * @brief Creates a delay using Timer
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] delayMs Number of milliseconds to delay
 * @note Assuming, Timer is already configured for 1MHz
 */
void TIM_delay_ms(TIM_REG_STRUCT* TIMx, uint32_t delayMs){
	// Iteration for each number of milliseconds
	while(delayMs--){
		TIM_delay_us(TIMx, 1000);
	}
}

/**
 * @brief Enables the Timer Interrupt
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 */
void TIM_IRQ_Enable(TIM_REG_STRUCT* TIMx){
	// Enable NVIC Interrupt
	NVIC_IRQ_Enable(TIMx_IRQn[((TIMx - TIM2) >> 10)]);
	// Enable the Timer Interrupt
	TIMx->DIER.REG |= TIM_DIER_UIE;
}

/**
 * @brief Disables the Timer Interrupt
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 */
void TIM_IRQ_Disable(TIM_REG_STRUCT* TIMx){
	// Disable NVIC Interrupt
	NVIC_IRQ_Disable(TIMx_IRQn[((TIMx - TIM2) >> 10)]);
	// Disable the Timer Interrupt
	TIMx->DIER.REG &= ~TIM_DIER_UIE;
}

/**
 * @brief Resets the General Purpose TIMx
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 */
void TIM_Reset(TIM_REG_STRUCT* TIMx){
	// Register
	uint32_t reg = RCC->APB1RSTR.REG;
	// Set based on Timer
	if(TIMx == TIM2){
		reg |= RCC_APB1RSTR_TIM2RST;
	}
	if(TIMx == TIM3){
		reg |= RCC_APB1RSTR_TIM3RST;
	}
	if(TIMx == TIM4){
		reg |= RCC_APB1RSTR_TIM4RST;
	}
	// Write to Register
	RCC->APB1RSTR.REG = reg;
	// Reset Based on Timer
	if(TIMx == TIM2){
		reg &= ~RCC_APB1RSTR_TIM2RST;
	}
	if(TIMx == TIM3){
		reg &= ~RCC_APB1RSTR_TIM3RST;
	}
	if(TIMx == TIM4){
		reg &= ~RCC_APB1RSTR_TIM4RST;
	}
	// Local Delay
	volatile uint16_t i = 10 * 1000;
	while(i--);
	// Write to Register
	RCC->APB1RSTR.REG = reg;
}
