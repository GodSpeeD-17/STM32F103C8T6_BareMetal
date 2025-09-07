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

// MACROS for Channel Configuration (Local)
#define TIMx_CCMR1_STATUS		0x0F
#define TIMx_CCMR2_STATUS		0xF0

// Lookup Table for Timer IRQn
static const uint8_t TIMx_IRQn[3] = {
	TIM2_IRQn,
	TIM3_IRQn,
	TIM4_IRQn,
};

/**
 * @brief Calculates the Prescaler Value based upon ARR Value provided
 * @param freq_Hz Frequency (in Hz)
 * @param arr_value Auto-Reload Register Value
 * @return Prescaler Value
 */
uint16_t TIM_Calc_Prescaler(uint32_t freq_Hz, uint16_t arr_value){
	// Final Value
	uint32_t prescaler_value = RCC_Get_APB1Clock();
	// Calculate the Timer Frequency
	if(RCC_Get_APB1_Prescaler() != RCC_CFGR_PPRE1_DIV1)
		prescaler_value = (RCC_Get_APB1Clock() << 1);
	// Update the value based upon the desired frequency
	prescaler_value /= freq_Hz;
	// Update the value based upon the ARR Value
	prescaler_value /= (arr_value + 1);
	// Final Calculated Value
	return (uint16_t)(prescaler_value - 1);
} 

#ifdef __OLD_TIMER_METHOD__
/**
 * @brief Configures the default parameters for TIMx_CONFIG
 * @param TIMx_CONFIG Pointer to timer configuration structure
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
 * @param TIMx_CONFIG Pointer to timer configuration structure
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
 * @param TIMx_CONFIG Pointer to timer configuration structure
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
	TIMx_CONFIG->TIM->CR1.REG |= (((TIMx_CONFIG->arpe & 0x01)<< TIM_CR1_ARPE_Pos) |
									// Centre-Aligned Mode 
								   ((TIMx_CONFIG->cms_mode & 0x03) << TIM_CR1_CMS_Pos) |
									// Direction 
								   ((TIMx_CONFIG->direction & 0x01)<< TIM_CR1_DIR_Pos) |
									// One Pulse Mode (OPM)
								   ((TIMx_CONFIG->one_pulse & 0x01) << TIM_CR1_OPM_Pos));
	// Enable Update Event
	TIM_UEV_Enable(TIMx_CONFIG->TIM);
	// Update the Timer
	TIM_Update_Parameters(TIMx_CONFIG->TIM);
}

/**
 * @brief General Purpose Timer Delay
 * @param TIMx_CONFIG Pointer to timer configuration structure
 * @param delayMs Number of milliseconds
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

#else

/**
 * @brief Helper Function for Timer Configuration
 * @param TIMx_CONFIG Pointer to timer configuration structure
 */
__STATIC__ void __TIM__Config_Default__(timer_config_t* TIMx_CONFIG){
	// !<< Timer Parameter Configuration >>!
	// CMS Mode Selection (Edge Mode Selection)
	TIMx_CONFIG->config.mode = TIMx_MODE_NORMAL;
	// Counting Direction (Up Counting)
	TIMx_CONFIG->config.direction = TIMx_DIR_COUNT_UP;
	// Auto Reload-Preload Enable
	TIMx_CONFIG->config.preload_arr = TIMx_ARPE_ENABLE;
	// One Pulse Mode Disable
	TIMx_CONFIG->config.one_pulse = TIMx_OPM_DISABLE;
	// Update Source - Any
	TIMx_CONFIG->config.update_source = TIMx_UPDATE_SOURCE_ANY;
	// !<< Timer Channel Configuration >>!
	TIMx_CONFIG->channel.config.oc_clear = TIMx_CHANNEL_OC_CLEAR_DISABLE;
	TIMx_CONFIG->channel.config.mode = TIMx_CHANNEL_MODE_PWM1;
	TIMx_CONFIG->channel.config.oc_preload = TIMx_CHANNEL_OC_PRELOAD_ENABLE;
	TIMx_CONFIG->channel.config.oc_fast = TIMx_CHANNEL_OC_FAST_DISABLE;
	TIMx_CONFIG->channel.config.ccs = TIMx_CHANNEL_CCS_OUTPUT;
}

/**
 * @brief Configures the default parameters for TIMx_CONFIG
 * @param TIMx_CONFIG Pointer to timer configuration structure
 * @note - TIM & Channel should be already configured
 * @note - This loads frequency as 10kHz
 */
void TIM_10kHz_Load_Default(timer_config_t* TIMx_CONFIG){
	// !<< Timer Clock Configuration >>!
	// Configure Auto-Reload Register Value
	TIMx_CONFIG->clk.auto_reload = TIMx_DEFAULT_10kHz_ARR;
	// Configure Prescaler Value
	TIMx_CONFIG->clk.prescaler = TIMx_DEFAULT_10kHz_PSC;
	// Configure Timer Count Value
	TIMx_CONFIG->clk.count = TIMx_DEFAULT_CNT;
	// Configure Default Parameters
	__TIM__Config_Default__(TIMx_CONFIG);
}

/**
 * @brief Configures the default parameters for TIMx_CONFIG
 * @param TIMx_CONFIG Pointer to timer configuration structure
 * @note - TIM & Channel should be already configured
 * @note - This loads frequency as 1MHz
 */
void TIM_1MHz_Load_Default(timer_config_t* TIMx_CONFIG){
	// !<< Timer Clock Configuration >>!
	// Configure Auto-Reload Register Value
	TIMx_CONFIG->clk.auto_reload = TIMx_DEFAULT_1MHz_ARR;
	// Configure Prescaler Value
	TIMx_CONFIG->clk.prescaler = TIMx_DEFAULT_1MHz_PSC;
	// Configure Timer Count Value
	TIMx_CONFIG->clk.count = TIMx_DEFAULT_CNT;
	// Configure Default Parameters
	__TIM__Config_Default__(TIMx_CONFIG);
}

/**
 * @brief Provides CCMRx expected register value based on Channel Configuration Settings
 * @param channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`  
 * @param config Channel Configuration Structure
 * @param ccmr_reg Pointer to CCMR register value
 */
void TIM_Channel_CCMRx_Config(tim_channel_t channel, tim_channel_config_t config, uint16_t* ccmr_reg){
	uint8_t index = (uint8_t)(((channel & TIMx_CHANNEL_2) || (channel & TIMx_CHANNEL_4)) ? TIM_CCMR1_CC2S_Pos: TIM_CCMR1_CC1S_Pos);
	*ccmr_reg &= ~(0xFF << index);
	*ccmr_reg |= (((config.oc_clear & 0x01) << (index + 7)) |
				  ((config.mode & 0x07) << (index + 4)) |
				  ((config.oc_preload & 0x01) << (index + 3)) |
				  ((config.oc_fast & 0x01) << (index + 2)) |
				  ((config.ccs & 0x03) << (index)));
}

/**
 * @brief Configures the Timer Channel as per configuration structure
 * @param TIMx_CONFIG Pointer to Timer Configuration Structure
 */
void TIM_Channel_Config(timer_config_t* TIMx_CONFIG){
	// No Configuration
	if(TIMx_CONFIG->channel.instance == TIMx_CHANNEL_NONE)
		return;
	// Local Variables
	uint16_t ccmr1_reg = TIMx_CONFIG->instance->CCMR1.REG;
	uint16_t ccmr2_reg = TIMx_CONFIG->instance->CCMR2.REG;
	uint8_t ccmr_status = 0x00;
	tim_channel_t current_channel = 0x00;
	// Iterate through all timer channels
	for(uint8_t i = 0; i < 4; i++){
		// All possible channels
		current_channel = (0x01 << i);
		// Only proceed if channel is defined
		if(TIMx_CONFIG->channel.instance & current_channel){
			if(current_channel < TIMx_CHANNEL_3){
				TIM_Channel_CCMRx_Config(current_channel, TIMx_CONFIG->channel.config, &ccmr1_reg);
				ccmr_status |= TIMx_CCMR1_STATUS; 
			}
			else{
				TIM_Channel_CCMRx_Config(current_channel, TIMx_CONFIG->channel.config, &ccmr2_reg);
				ccmr_status |= TIMx_CCMR2_STATUS; 
			}
		}
	}
	// Writing back to CCMR Registers
	if(ccmr_status & TIMx_CCMR1_STATUS){
		TIMx_CONFIG->instance->CCMR1.REG = ccmr1_reg;
	}
	if(ccmr_status & TIMx_CCMR2_STATUS){
		TIMx_CONFIG->instance->CCMR2.REG = ccmr2_reg;
	}
}

/**
 * @brief Configures the General Purpose Timer (TIMx)
 * @param TIMx_CONFIG Pointer to timer configuration structure
 */
void TIM_Config(timer_config_t* TIMx_CONFIG){
	// Enable Clock for Timer
	TIM_Clk_Enable(TIMx_CONFIG->instance);
	// Reset the Timer
	TIM_Reset(TIMx_CONFIG->instance);
	// Disable the Timer
	TIM_Disable(TIMx_CONFIG->instance);
	// Disable Update Event
	TIM_UEV_Disable(TIMx_CONFIG->instance);
	// << Timer Clock Source Configuration >>
	// Auto Reload Value
	TIMx_CONFIG->instance->ARR = TIMx_CONFIG->clk.auto_reload;
	// Prescaler Value
	TIMx_CONFIG->instance->PSC = TIMx_CONFIG->clk.prescaler;
	// Initial Count Value
	TIMx_CONFIG->instance->CNT = TIMx_CONFIG->clk.count;
	// << Timer Configuration >>
	TIMx_CONFIG->instance->CR1.REG |= (
		((TIMx_CONFIG->config.preload_arr & 0x01) << TIM_CR1_ARPE_Pos) |
		((TIMx_CONFIG->config.mode & 0x03) << TIM_CR1_CMS_Pos) |
		((TIMx_CONFIG->config.direction & 0x01) << TIM_CR1_DIR_Pos) |
		((TIMx_CONFIG->config.one_pulse & 0x01) << TIM_CR1_OPM_Pos) |
		((TIMx_CONFIG->config.update_source & 0x01) << TIM_CR1_URS_Pos));
	// << Timer Channel Configuration >> 
	TIM_Channel_Config(TIMx_CONFIG);
	// Enable Update Event
	TIM_UEV_Enable(TIMx_CONFIG->instance);
	// Update the Timer
	TIM_Update_Parameters(TIMx_CONFIG->instance);
}

#endif /* __OLD_TIMER_METHOD__ */

/**
 * @brief Creates a delay using Timer
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param delayUs Number of microseconds to delay
 * @note The following assumptions are made:
 * @note - Timer is configured for 1MHz
 * @note - Timer is upcounter
 * @note - Timer Channel 1 is used for output compare
 */
void TIM_delay_us(TIM_REG_STRUCT* TIMx, uint32_t delayUs){
	// Disable the Timer
	TIM_Disable(TIMx);
	// Configure Timer Count Value
	TIMx->CNT = TIMx_DEFAULT_CNT;
	// Configure Delay Time
	TIMx->ARR = (delayUs - 1);
	// Enable the Timer
	TIM_Enable(TIMx);
	// Wait until ARR is reached
	while(!(TIMx->SR.REG & TIM_SR_UIF));
	// Disable the Timer
	TIM_Disable(TIMx);
	// Clear the UIF Flag
	TIMx->SR.REG &= ~TIM_SR_UIF;
}

/**
 * @brief Creates a delay using Timer
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param delayMs Number of milliseconds to delay
 * @note The following assumptions are made: 
 * @note - Timer is configured for 1MHz
 * @note - Timer is upcounter
 * @note - Timer Channel 1 is used for output compare
 * @note - This is designed in such a way for scalability in `ms` delays
 */
void TIM_delay_ms(TIM_REG_STRUCT* TIMx, uint32_t delayMs){
	// Iteration for each number of milliseconds
	while(delayMs--){
		TIM_delay_us(TIMx, 998);
	}
}

/**
 * @brief Enables Timer Interrupt for mentioned Interrupt
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_OUT_CMP_CHx`, `TIMx_IRQ_IN_CAP_CHx`
 */
void TIM_IRQ_Enable(TIM_REG_STRUCT* TIMx, tim_irq_t IRQ){
	// Get the DMA/Interrupt Enable Register Status
	uint16_t reg = TIMx->DIER.REG;
	// Enable the Timer Event Interrupt
	if(IRQ & TIMx_IRQ_OVF_UVF)
		reg |= TIM_DIER_UIE;
	// Enable Capture/Compare Interrupt for Channel 1
	if((IRQ & TIMx_IRQ_OUT_CMP_CH1) || (IRQ & TIMx_IRQ_IN_CAP_CH1))
		reg |= TIM_DIER_CC1IE;
	// Enable Capture/Compare Interrupt for Channel 2
	if((IRQ & TIMx_IRQ_OUT_CMP_CH2) || (IRQ & TIMx_IRQ_IN_CAP_CH2))
		reg |= TIM_DIER_CC2IE;
	// Enable Capture/Compare Interrupt for Channel 3
	if((IRQ & TIMx_IRQ_OUT_CMP_CH3) || (IRQ & TIMx_IRQ_IN_CAP_CH3))
		reg |= TIM_DIER_CC3IE;
	// Enable Capture/Compare Interrupt for Channel 4
	if((IRQ & TIMx_IRQ_OUT_CMP_CH4) || (IRQ & TIMx_IRQ_IN_CAP_CH4))
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
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_OUT_CMP_CHx`, `TIMx_IRQ_IN_CAP_CHx`
 */
void TIM_IRQ_Disable(TIM_REG_STRUCT* TIMx, tim_irq_t IRQ){
	// Get the DMA/Interrupt Enable Register Status
	uint16_t reg = TIMx->DIER.REG;
	// Enable the Timer Event Interrupt
	if(IRQ & TIMx_IRQ_OVF_UVF)
		reg &= ~TIM_DIER_UIE;
	// Enable Capture/Compare Interrupt for Channel 1
	if((IRQ & TIMx_IRQ_OUT_CMP_CH1) || (IRQ & TIMx_IRQ_IN_CAP_CH1))
		reg &= ~TIM_DIER_CC1IE;
	// Enable Capture/Compare Interrupt for Channel 2
	if((IRQ & TIMx_IRQ_OUT_CMP_CH2) || (IRQ & TIMx_IRQ_IN_CAP_CH2))
		reg &= ~TIM_DIER_CC2IE;
	// Enable Capture/Compare Interrupt for Channel 3
	if((IRQ & TIMx_IRQ_OUT_CMP_CH3) || (IRQ & TIMx_IRQ_IN_CAP_CH3))
		reg &= ~TIM_DIER_CC3IE;
	// Enable Capture/Compare Interrupt for Channel 4
	if((IRQ & TIMx_IRQ_OUT_CMP_CH4) || (IRQ & TIMx_IRQ_IN_CAP_CH4))
		reg &= ~TIM_DIER_CC4IE;
	// Update the DMA/Interrupt Enable Register
	TIMx->DIER.REG = reg;
	// Update reg with calculation
	reg = (((uint32_t)TIMx - (uint32_t)TIM2) >> 10);
	// Enable NVIC Interrupt
	NVIC_IRQ_Disable(TIMx_IRQn[reg]);
}

/**
 * @brief Resets the General Purpose TIMx
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
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
		if(prescaler != 0x01){
			// Multiplication Factor = 2 (Refer Clock Tree)
			timer_freq_Hz <<= 1;
		}
	}
	// Timer Frequency
	return timer_freq_Hz;
}
