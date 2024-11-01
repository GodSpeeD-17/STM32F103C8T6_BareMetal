/*
  THEORY:
	|=> Refer Reference Manual (RM008) PDF Page 93 for Clock Tree Configuration
	|=> It is quite evident that, SYSCLK is passed to AHB Prescaler
	|
	|=> For General Purpose Timer refer Table Number 23 (PDF Page 166) (TIM2, TIM3, TIM4, TIM5)
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
#include "timer.h"

/**
 * @brief Enables the Clock for General Purpose Timer
 * @param[in] GP_TIMx General Purpose Timer
 * @note RCC->APB1ENR
 */
void enable_GPT_clk(GPT_REG_STRUCT* GP_TIMx){
	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5)
		return;
		
	// Enable the clock for the timer
	if(GP_TIMx == TIM2)
		RCC->APB1ENR.BIT.TIM2EN = BIT_SET;
	else if(GP_TIMx == TIM3)
		RCC->APB1ENR.BIT.TIM3EN = BIT_SET;
	else if(GP_TIMx == TIM4)
		RCC->APB1ENR.BIT.TIM4EN = BIT_SET;
	else if(GP_TIMx == TIM5)
		RCC->APB1ENR.BIT.TIM5EN = BIT_SET;
}

/**
 * @brief Disables the Clock for General Purpose Timer
 * @param[in] GP_TIMx General Purpose Timer
 * @note RCC->APB1ENR
 */
void disable_GPT_clk(GPT_REG_STRUCT* GP_TIMx){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5)
		return;

	// Disable the clock for the timer
	if(GP_TIMx == TIM2)
		RCC->APB1ENR.BIT.TIM2EN = BIT_RESET;
	else if(GP_TIMx == TIM3)
		RCC->APB1ENR.BIT.TIM3EN = BIT_RESET;
	else if(GP_TIMx == TIM4)
		RCC->APB1ENR.BIT.TIM4EN = BIT_RESET;
	else if(GP_TIMx == TIM5)
		RCC->APB1ENR.BIT.TIM5EN = BIT_RESET;
}

/**
 * @brief Enables the General Purpose GP_TIMx
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 */
void enable_GPT(GPT_REG_STRUCT* GP_TIMx){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5)
		return;

	// Enable GP_TIMx
	GP_TIMx->CR1.BIT.CEN = BIT_SET;
}

/**
 * @brief Disables the General Purpose GP_TIMx
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 */
void disable_GPT(GPT_REG_STRUCT* GP_TIMx){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5)
		return;

	// Disable GP_TIMx
	GP_TIMx->CR1.BIT.CEN = BIT_RESET;
}

/**
 * @brief Enables the General Purpose GP_TIMx's Channel
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
void enable_GPT_CH(GPT_REG_STRUCT* GP_TIMx, uint8_t channel){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5)
		return;

	// Enable the General Purpose Timer Channel
	switch(channel){
		
		case TIMx_CHANNEL_1:
			GP_TIMx->CCER.BIT.CC1E = BIT_SET;
		break;

		case TIMx_CHANNEL_2:
			GP_TIMx->CCER.BIT.CC2E = BIT_SET;
		break;
		
		case TIMx_CHANNEL_3:
			GP_TIMx->CCER.BIT.CC3E = BIT_SET;
		break;
		
		case TIMx_CHANNEL_4:
			GP_TIMx->CCER.BIT.CC4E = BIT_SET;
		break;

		case TIMx_CHANNEL_ALL:
			GP_TIMx->CCER.BIT.CC1E = BIT_SET;
			GP_TIMx->CCER.BIT.CC2E = BIT_SET;
			GP_TIMx->CCER.BIT.CC3E = BIT_SET;
			GP_TIMx->CCER.BIT.CC4E = BIT_SET;
		break;
	}
}

/**
 * @brief Disables the General Purpose GP_TIMx's Channel
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
void disable_GPT_CH(GPT_REG_STRUCT* GP_TIMx, uint8_t channel){
	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5)
		return;

	// Enable the General Purpose Timer Channel
	switch(channel){
		
		case TIMx_CHANNEL_1:
			GP_TIMx->CCER.BIT.CC1E = BIT_RESET;
		break;

		case TIMx_CHANNEL_2:
			GP_TIMx->CCER.BIT.CC2E = BIT_RESET;
		break;
		
		case TIMx_CHANNEL_3:
			GP_TIMx->CCER.BIT.CC3E = BIT_RESET;
		break;
		
		case TIMx_CHANNEL_4:
			GP_TIMx->CCER.BIT.CC4E = BIT_RESET;
		break;

		case TIMx_CHANNEL_ALL:
			GP_TIMx->CCER.BIT.CC1E = BIT_RESET;
			GP_TIMx->CCER.BIT.CC2E = BIT_RESET;
			GP_TIMx->CCER.BIT.CC3E = BIT_RESET;
			GP_TIMx->CCER.BIT.CC4E = BIT_RESET;
		break;
	}
}

/**
 * @brief Calculates the Prescaler Value based upon ARR Value provided
 * @param[in] freq_Hz Frequency (in Hz)
 * @param[in] arr_value Auto-Reload Register Value
 * @return Prescaler Value
 */
__attribute__((always_inline)) static inline uint16_t calc_GPT_PSC(uint32_t freq_Hz, uint16_t arr_value){
	// Final Value
	uint32_t prescaler_value = 0x00;
	
	// Calculate the Timer Frequency
	if((RCC->CFGR.BIT.PPRE1 == APB1_DIV_1))
		prescaler_value = get_APB1_freq();
	else
		prescaler_value = (uint32_t)(2 * get_APB1_freq());
	
	// Update the value based upon the desired frequency
	prescaler_value /= freq_Hz;

	// Update the value based upon the ARR Value
	prescaler_value /= (arr_value + 1);

	// Final Calculated Value
	return (uint16_t)(prescaler_value - 1);
} 

/**
 * @brief Configure General Purpose GP_TIMx (Clock Source + Frequency)
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @param[in] arr_value ARR Value
 * @param[in] freq_Hz Timer Frequency (in Hz)
 * @param[in] count_value Timer Counter Value 
 * @note - ERROR HANDLING NOT DONE
 * @note - Configures DIR is Up Counting
 * @note - Configures Edge Aligned Mode (Up counting or Down counting based upon `DIR`)
 */
void config_GPT(GPT_REG_STRUCT* GP_TIMx, uint16_t arr_value, uint32_t freq_Hz, uint16_t count_value){
	
	// Error Check
	if ((freq_Hz == 0) || (GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5))
		return;

	// Set the prescaler value
	GP_TIMx->ARR = arr_value;

	// Calculate GP_TIMx Prescaler for desired frequency
	GP_TIMx->PSC = calc_GPT_PSC(freq_Hz, GP_TIMx->ARR);

	// Set the count value
	GP_TIMx->CNT = count_value;
}

/**
 * @brief Configures GP Timer Counting Mode along with Direction
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @param[in] cms_mode `TIMx_MODE_...`
 * @param[in] direction `TIMx_COUNT_UP`, `TIMx_COUNT_DOWN`
 */
void config_GPT_mode(GPT_REG_STRUCT* GP_TIMx, uint8_t cms_mode, uint8_t direction){
	
	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5)
		return; 

	// Centre-Aligned Mode Selection
	GP_TIMx->CR1.BIT.CMS = cms_mode;

	// Direction Selection
	GP_TIMx->CR1.BIT.DIR = direction;
}

/**
 * @brief Updates the frequency of already configured General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @param[in] freq_Hz Timer Frequency (in Hz)
 */
void update_GPT_freq(GPT_REG_STRUCT* GP_TIMx, uint32_t freq_Hz){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5)
		return; 

	// Calculate updated PSC Value
	GP_TIMx->PSC = calc_GPT_PSC(freq_Hz, GP_TIMx->ARR);
}

/**
 * @brief Updates the frequency of already configured General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @param[in] arr_value Auto Reload Value
 */
void update_GPT_ARR(GPT_REG_STRUCT* GP_TIMx, uint16_t arr_value){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5)
		return;

	// Calculate updated PSC Value
	GP_TIMx->ARR = arr_value;
}

/**
 * @brief Gets the GP Timer Clock Frequency
 * @param[in] GP_TIMx  `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @note Refer the formula mentioned in .c file  & clock tree to get clear understanding
 */
uint32_t get_GPT_freq(GPT_REG_STRUCT* GP_TIMx){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4 && GP_TIMx != TIM5)
		return (uint32_t) 0xFFFFFFFF;

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
 * @param[in] GP_TIMx General Purpose Timer (TIM2, ..., TIM5)
 * @param[in] delayMs Number of milliseconds
 */
void GPT_delay_ms(GPT_REG_STRUCT* GP_TIMx, volatile uint32_t delayMs){

	// Update the Event Frequency at 1kHz
	if(get_GPT_freq(GP_TIMx) != FREQ_1kHz){
		// Set update event after 1ms (1kHz)
		update_GPT_freq(GP_TIMx, FREQ_1kHz);
	}

	// Iteration for Milliseconds
	while(delayMs--){
		// Wait till Update Flag is Set
		while(!(GP_TIMx->SR.BIT.UIF));

		// Clear the update flag
		GP_TIMx->SR.BIT.UIF = BIT_RESET;
	}
}
