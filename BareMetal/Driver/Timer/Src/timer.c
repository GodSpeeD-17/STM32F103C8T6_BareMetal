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
*/

// Main Library
#include "timer.h"

// Lookup Table for Timer IRQn
static const uint8_t TIMx_IRQn[3] = {
	TIM2_IRQn,
	TIM3_IRQn,
	TIM4_IRQn,
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
 * @brief Configures the default parameters for TIMx_CONFIG
 * @param[in] TIMx_CONFIG `timer_config_t *` structure containing the configuration
 * @note - TIM & Channel should be already configured
 * @note - This loads frequency as 10kHz
 */
void TIM_10kHz_Load_Default(timer_config_t* TIMx_CONFIG){
	// Configure Auto-Reload Register Value
	TIMx_CONFIG->auto_reload = TIMx_DEFAULT_10kHz_ARR;
	// Configure Prescaler Value
	TIMx_CONFIG->prescaler = TIMx_DEFAULT_10kHz_PSC;
	// Configure Timer Count Value
	TIMx_CONFIG->count = TIMx_DEFAULT_CNT;
	// CMS Mode Selection (Edge Mode Selection)
	TIMx_CONFIG->cms_mode = TIMx_CMS_EDGE;
	// Counting Direction (Up Counting)
	TIMx_CONFIG->direction = TIMx_DIR_COUNT_UP;
	// Auto Reload-Preload Enable
	TIMx_CONFIG->arpe = TIMx_ARPE_ENABLE;
	// One Pulse Mode (OFF)
	TIMx_CONFIG->one_pulse = TIMx_OPM_DISABLE;
}

/**
 * @brief Configures the default parameters for TIMx_CONFIG
 * @param[in] TIMx_CONFIG `timer_config_t *` structure containing the configuration
 * @note - TIM & Channel should be already configured
 * @note - This loads frequency as 1MHz
 */
void TIM_1MHz_Load_Default(timer_config_t* TIMx_CONFIG){
	// Configure Auto-Reload Register Value
	TIMx_CONFIG->auto_reload = TIMx_DEFAULT_1MHz_ARR;
	// Configure Prescaler Value
	TIMx_CONFIG->prescaler = TIMx_DEFAULT_1MHz_PSC;
	// Configure Timer Count Value
	TIMx_CONFIG->count = TIMx_DEFAULT_CNT;
	// CMS Mode Selection (Edge Mode Selection)
	TIMx_CONFIG->cms_mode = TIMx_CMS_EDGE;
	// Counting Direction (Up Counting)
	TIMx_CONFIG->direction = TIMx_DIR_COUNT_UP;
	// Auto Reload-Preload Enable
	TIMx_CONFIG->arpe = TIMx_ARPE_ENABLE;
	// One Pulse Mode (OFF)
	TIMx_CONFIG->one_pulse = TIMx_OPM_DISABLE;	
}

/**
 * @brief Configures the General Purpose Timer (TIMx)
 * @param[in] TIMx_CONFIG `timer_config_t *` structure containing the configuration
 */
void TIM_Config(timer_config_t* TIMx_CONFIG){
	// Enable Clock for Timer
	TIM_Clk_Enable(TIMx_CONFIG->TIM);
	// Reset the Timer
	TIM_Reset(TIMx_CONFIG->TIM);
	// Disable the Timer
	TIM_Disable(TIMx_CONFIG->TIM);
	// Disable Update Event
	TIM_UEV_Disable(TIMx_CONFIG->TIM);
	// Auto Reload Value
	TIMx_CONFIG->TIM->ARR = TIMx_CONFIG->auto_reload;
	// Prescaler Value
	TIMx_CONFIG->TIM->PSC = TIMx_CONFIG->prescaler;
	// Initial Count Value
	TIMx_CONFIG->TIM->CNT = TIMx_CONFIG->count;
	// Auto Reload Preload Enable
	TIMx_CONFIG->TIM->CR1.REG |= (((TIMx_CONFIG->arpe & 0x01)<< TIM_CR1_ARPE_Pos) | \
									// Centre-Aligned Mode 
								   ((TIMx_CONFIG->cms_mode & 0x03) << TIM_CR1_CMS_Pos) | \
									// Direction 
								   ((TIMx_CONFIG->direction & 0x01)<< TIM_CR1_DIR_Pos) | \
									// One Pulse Mode (OPM)
								   ((TIMx_CONFIG->one_pulse & 0x01) << TIM_CR1_OPM_Pos));
	// Enable Update Event
	TIM_UEV_Enable(TIMx_CONFIG->TIM);
	// Update the Timer
	TIM_Update_Parameters(TIMx_CONFIG->TIM);
}

/**
 * @brief General Purpose Timer Delay
 * @param[in] TIMx_CONFIG `timer_config_t *` structure containing the configuration
 * @param[in] delayMs Number of milliseconds
 */
static void TIM__delay_ms(timer_config_t* TIMx_CONFIG, volatile uint32_t delayMs){
	// Update the Event Frequency at 1kHz
	if(TIM_Get_Freq(TIMx_CONFIG) != FREQ_1kHz){
		// Disable Timer
		TIM_Disable(TIMx_CONFIG);
		// Set update event after 1ms (1kHz)
		update_TIM_freq(TIMx_CONFIG, FREQ_1kHz);
		// Update the Parameters
		TIM_Update_Parameters(TIMx_CONFIG);
		// Enable Timer
		TIM_Enable(TIMx_CONFIG);
	}
	// Iteration for Milliseconds
	while(delayMs--){
		// Wait till Update Flag is Set
		while(!(TIMx_CONFIG->TIM->SR.REG & TIM_SR_UIF));
		// Clear the update flag
		TIMx_CONFIG->TIM->SR.REG &= ~TIM_SR_UIF;
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
 * @brief Enables Timer Interrupt for mentioned Interrupt
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_CMP_CHx`, `TIMx_IRQ_CAP_CHx`
 */
void TIM_IRQ_Enable(TIM_REG_STRUCT* TIMx, uint8_t IRQ){
	// Get the DMA/Interrupt Enable Register Status
	uint16_t reg = TIMx->DIER.REG;
	// Enable the Timer Event Interrupt
	if(IRQ & TIMx_IRQ_OVF_UVF)
		reg |= TIM_DIER_UIE;
	// Enable Capture/Compare Interrupt for Channel 1
	if((IRQ & TIMx_IRQ_CMP_CH1) || (IRQ & TIMx_IRQ_CAP_CH1))
		reg |= TIM_DIER_CC1IE;
	// Enable Capture/Compare Interrupt for Channel 2
	if((IRQ & TIMx_IRQ_CMP_CH2) || (IRQ & TIMx_IRQ_CAP_CH2))
		reg |= TIM_DIER_CC2IE;
	// Enable Capture/Compare Interrupt for Channel 3
	if((IRQ & TIMx_IRQ_CMP_CH3) || (IRQ & TIMx_IRQ_CAP_CH3))
		reg |= TIM_DIER_CC3IE;
	// Enable Capture/Compare Interrupt for Channel 4
	if((IRQ & TIMx_IRQ_CMP_CH4) || (IRQ & TIMx_IRQ_CAP_CH4))
		reg |= TIM_DIER_CC4IE;
	// Update the DMA/Interrupt Enable Register
	TIMx->DIER.REG = reg;
	// Update reg with calculation
	reg = (((uint32_t)TIMx - (uint32_t)TIM2) >> 10);
	// Enable NVIC Interrupt
	NVIC_IRQ_Enable(TIMx_IRQn[reg]);
}

/**
 * @brief Disables Timer Interrupt for mentioned Interrupt
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_CMP_CHx`, `TIMx_IRQ_CAP_CHx`
 */
void TIM_IRQ_Disable(TIM_REG_STRUCT* TIMx, uint8_t IRQ){
	// Get the DMA/Interrupt Enable Register Status
	uint16_t reg = TIMx->DIER.REG;
	// Disable the Timer Interrupt
	if(IRQ & TIMx_IRQ_OVF_UVF)
		reg &= ~TIM_DIER_UIE;
	// Disable Capture/Compare Interrupt for Channel 1
	if((IRQ & TIMx_IRQ_CMP_CH1) || (IRQ & TIMx_IRQ_CAP_CH1))
		reg &= ~TIM_DIER_CC1IE;
	// Disable Capture/Compare Interrupt for Channel 2
	if((IRQ & TIMx_IRQ_CMP_CH2) || (IRQ & TIMx_IRQ_CAP_CH2))
		reg &= ~TIM_DIER_CC2IE;
	// Disable Capture/Compare Interrupt for Channel 3
	if((IRQ & TIMx_IRQ_CMP_CH3) || (IRQ & TIMx_IRQ_CAP_CH3))
		reg &= ~TIM_DIER_CC3IE;
	// Disable Capture/Compare Interrupt for Channel 4
	if((IRQ & TIMx_IRQ_CMP_CH4) || (IRQ & TIMx_IRQ_CAP_CH4))
		reg &= ~TIM_DIER_CC4IE;
	// Update the DMA/Interrupt Enable Register
	TIMx->DIER.REG = reg;
	// Disable NVIC Interrupt
	NVIC_IRQ_Disable(TIMx_IRQn[((TIMx - TIM2) >> 10)]);
}

/**
 * @brief Timer Interrupt Flag Acknowledge
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_CMP_CHx`, `TIMx_IRQ_CAP_CHx`
 */
void TIM_IRQ_Ack(TIM_REG_STRUCT* TIMx, uint8_t IRQ){
	// Acknowledge Interrupt Flag
	if(IRQ & TIMx_IRQ_OVF_UVF)
		TIMx->SR.REG &= ~TIM_SR_UIF;
	// Acknowledge Capture/Compare Interrupt for Channel 1
	if((IRQ & TIMx_IRQ_CMP_CH1) || (IRQ & TIMx_IRQ_CAP_CH1))
		TIMx->SR.REG &= ~TIM_SR_CC1IF;
	// Acknowledge Capture/Compare Interrupt for Channel 2
	if((IRQ & TIMx_IRQ_CMP_CH2) || (IRQ & TIMx_IRQ_CAP_CH2))
		TIMx->SR.REG &= ~TIM_SR_CC2IF;
	// Acknowledge Capture/Compare Interrupt for Channel 3
	if((IRQ & TIMx_IRQ_CMP_CH3) || (IRQ & TIMx_IRQ_CAP_CH3))
		TIMx->SR.REG &= ~TIM_SR_CC3IF;
	// Acknowledge Capture/Compare Interrupt for Channel 4
	if((IRQ & TIMx_IRQ_CMP_CH4) || (IRQ & TIMx_IRQ_CAP_CH4))
		TIMx->SR.REG &= ~TIM_SR_CC4IF;
}

/**
 * @brief Retrieves the Interrupt Status
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_CMP_CHx`, `TIMx_IRQ_CAP_CHx`
 * @return - 0: Interrupt was not triggered 
 * @return - 1: Interrupt was triggered 
 */
uint8_t TIM_Get_IRQ_Status(TIM_REG_STRUCT* TIMx, uint8_t IRQ){
	// Capture the Status Register
	uint16_t status = TIMx->SR.REG;
	// Acknowledge Interrupt Flag
	if(IRQ & TIMx_IRQ_OVF_UVF)
		status >>= TIM_SR_UIF_Pos;
	// Acknowledge Capture/Compare Interrupt for Channel 1
	if((IRQ & TIMx_IRQ_CMP_CH1) || (IRQ & TIMx_IRQ_CAP_CH1))
		status >>= TIM_SR_CC1IF_Pos;
	// Acknowledge Capture/Compare Interrupt for Channel 2
	if((IRQ & TIMx_IRQ_CMP_CH2) || (IRQ & TIMx_IRQ_CAP_CH2))
		status >>= TIM_SR_CC2IF_Pos;
	// Acknowledge Capture/Compare Interrupt for Channel 3
	if((IRQ & TIMx_IRQ_CMP_CH3) || (IRQ & TIMx_IRQ_CAP_CH3))
		status >>= TIM_SR_CC3IF_Pos;
	// Acknowledge Capture/Compare Interrupt for Channel 4
	if((IRQ & TIMx_IRQ_CMP_CH4) || (IRQ & TIMx_IRQ_CAP_CH4))
		status >>= TIM_SR_CC4IF_Pos;
	// Return the status
	return (uint8_t) status;
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

/**
 * @brief Provides the Timer Frequency
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @returns Timer Frequency (in Hz)
 */
uint32_t TIM_Get_Frequency(TIM_REG_STRUCT* TIMx){
	// Local Variables
	uint32_t timer_freq_Hz = 0x00;
	uint8_t prescaler = 0x00;
	if(TIMx != TIM1 && TIMx != TIM8){
		// APB1 Clock Frequency
		timer_freq_Hz = RCC_Get_APB1Clock();
		// APB1 Clock Prescaler
		prescaler = RCC_Get_APB1_Prescaler();
		// Actual Timer Frequency
		if(prescaler != 1){
			timer_freq_Hz <<= 1;
		}
	}
	// Timer Frequency
	return timer_freq_Hz;
}
