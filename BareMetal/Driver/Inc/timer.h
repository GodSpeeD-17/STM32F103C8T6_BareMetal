/***************************************************************************************
 *  File: gpt.h
 *  Created on: 23/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __TIMER_H__
#define __TIMER_H__

// Register Mapping
#include "reg_map.h"
#include "rcc.h"		// Required for get_APB1_freq()
#include "gpio.h"		// Required for Configuration
#include "nvic.h"		// IRQ Configuration

// Timer Configuration Structure
typedef struct {
	// GPIO Configuration Structure
	gpio_config_t* GPIO_CONFIGx;
	// Timer
	GPT_REG_STRUCT* TIMx;
	// Timer Channel
	uint8_t channel;
	// Auto Reload Value
	uint16_t auto_reload;
	// Prescaler Value
	uint16_t prescaler;
	// Frequency (in Hz)
	uint32_t frequency_Hz;
	// Initial Count Value
	uint16_t count;
	// Centre-Aligned Mode Selection
	uint8_t cms_mode: 1;
	// Count Direction
	uint8_t direction: 1;
	// Auto-Reload Preload Enable
	uint8_t arpe: 1;
	// One-Pulse Mode Enable
	uint8_t one_pulse: 1;
	// IRQ Enable
	uint8_t enable_IRQ: 1;
} timer_config_t;

/**
 * @brief Enables the Clock for General Purpose Timer
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void enable_GPT_clk(timer_config_t* TIM_CONFIGx){
	// Enable the clock for the timer
	if(TIM_CONFIGx->TIMx == TIM2)
		RCC->APB1ENR.REG |= RCC_APB1ENR_TIM2EN;
	else if(TIM_CONFIGx->TIMx == TIM3)
		RCC->APB1ENR.REG |= RCC_APB1ENR_TIM3EN;
	else if(TIM_CONFIGx->TIMx == TIM4)
		RCC->APB1ENR.REG |= RCC_APB1ENR_TIM4EN;
}

/**
 * @brief Disables the Clock for General Purpose Timer
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void disable_GPT_clk(timer_config_t* TIM_CONFIGx){
	// Disable the clock for the timer
	if(TIM_CONFIGx->TIMx == TIM2)
		RCC->APB1ENR.REG &= ~RCC_APB1ENR_TIM2EN;
	else if(TIM_CONFIGx->TIMx == TIM3)
		RCC->APB1ENR.REG &= ~RCC_APB1ENR_TIM3EN;
	else if(TIM_CONFIGx->TIMx == TIM4)
		RCC->APB1ENR.REG &= ~RCC_APB1ENR_TIM4EN;
}

/**
 * @brief Enables the General Purpose TIMx
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void enable_GPT(timer_config_t* TIM_CONFIGx){
	// Clear Update Interrupt Flag
	TIM_CONFIGx->TIMx->SR.REG &= ~TIM_SR_UIF;
	// Enable TIMx
	TIM_CONFIGx->TIMx->CR1.REG |= TIM_CR1_CEN;
}

/**
 * @brief Disables the General Purpose TIMx
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void disable_GPT(timer_config_t* TIM_CONFIGx){
	// Disable TIMx
	TIM_CONFIGx->TIMx->CR1.REG &= ~TIM_CR1_CEN;
	// Clear Update Interrupt Flag
	TIM_CONFIGx->TIMx->SR.REG &= ~TIM_SR_UIF;
}

/**
 * @brief Enables the General Purpose TIMx's Channel
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @note Use this for single channel configuration
 */
__attribute__((always_inline)) inline void enable_GPT_CH(timer_config_t* TIM_CONFIGx){
	// Local Variable
	uint32_t reg = TIM_CONFIGx->TIMx->CCER.REG; 
	// Enable the General Purpose Timer Channel
	if(TIM_CONFIGx->channel & TIMx_CHANNEL_1)
		reg |= TIM_CCER_CC1E;
	if(TIM_CONFIGx->channel & TIMx_CHANNEL_2)
		reg |= TIM_CCER_CC2E;
	if(TIM_CONFIGx->channel & TIMx_CHANNEL_3)
		reg |= TIM_CCER_CC3E;
	if(TIM_CONFIGx->channel & TIMx_CHANNEL_4)
		reg |= TIM_CCER_CC4E;
	// Write to the register
	TIM_CONFIGx->TIMx->CCER.REG = reg;
}

/**
 * @brief Disables the General Purpose TIMx's Channel
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @note Use this for single channel configuration
 */
__attribute__((always_inline)) inline void disable_GPT_CH(timer_config_t* TIM_CONFIGx){
	// Local Variable
	uint32_t reg = TIM_CONFIGx->TIMx->CCER.REG; 
	// Disable the General Purpose Timer Channel
	if(TIM_CONFIGx->channel & TIMx_CHANNEL_1)
		reg &= ~TIM_CCER_CC1E;
	if(TIM_CONFIGx->channel & TIMx_CHANNEL_2)
		reg &= ~TIM_CCER_CC2E;
	if(TIM_CONFIGx->channel & TIMx_CHANNEL_3)
		reg &= ~TIM_CCER_CC3E;
	if(TIM_CONFIGx->channel & TIMx_CHANNEL_4)
		reg &= ~TIM_CCER_CC4E;
	// Write to the register
	TIM_CONFIGx->TIMx->CCER.REG = reg;
}

/**
 * @brief Enables the General Purpose TIMx's Multiple Channel
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`

__attribute__((always_inline)) inline void enable_GPT_multi_CH(timer_config_t* TIM_CONFIGx, uint8_t channel){
	// Enable the General Purpose Timer Channel
	if((TIM_CONFIGx->channel & channel) == TIMx_CHANNEL_1)
		TIM_CONFIGx->TIMx->CCER.BIT.CC1E = BIT_SET;
	if((TIM_CONFIGx->channel & channel) == TIMx_CHANNEL_2)
		TIM_CONFIGx->TIMx->CCER.BIT.CC2E = BIT_SET;
	if((TIM_CONFIGx->channel & channel) == TIMx_CHANNEL_3)
		TIM_CONFIGx->TIMx->CCER.BIT.CC3E = BIT_SET;
	if((TIM_CONFIGx->channel & channel) == TIMx_CHANNEL_4)
		TIM_CONFIGx->TIMx->CCER.BIT.CC4E = BIT_SET;
}

/**
 * @brief Disables the General Purpose TIMx's Multiple Channel
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`

__attribute__((always_inline)) inline void disable_GPT_multi_CH(timer_config_t* TIM_CONFIGx, uint8_t channel){
	// Disable the General Purpose Timer Channel
	if((TIM_CONFIGx->channel & channel) == TIMx_CHANNEL_1)
		TIM_CONFIGx->TIMx->CCER.BIT.CC1E = BIT_RESET;
	if((TIM_CONFIGx->channel & channel) == TIMx_CHANNEL_2)
		TIM_CONFIGx->TIMx->CCER.BIT.CC2E = BIT_RESET;
	if((TIM_CONFIGx->channel & channel) == TIMx_CHANNEL_3)
		TIM_CONFIGx->TIMx->CCER.BIT.CC3E = BIT_RESET;
	if((TIM_CONFIGx->channel & channel) == TIMx_CHANNEL_4)
		TIM_CONFIGx->TIMx->CCER.BIT.CC4E = BIT_RESET;
}
*/

/**
 * @brief Resets the General Purpose TIMx
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void reset_GPT(timer_config_t* TIM_CONFIGx){
	// Local Variable
	uint16_t i = 10 * 1000;
	uint32_t reg = RCC->APB1RSTR.REG;
	// Set Based on Timer
	if(TIM_CONFIGx->TIMx == TIM2){
		reg |= RCC_APB1RSTR_TIM2RST;
	}
	if(TIM_CONFIGx->TIMx == TIM3){
		reg |= RCC_APB1RSTR_TIM3RST;
	}
	if(TIM_CONFIGx->TIMx == TIM4){
		reg |= RCC_APB1RSTR_TIM4RST;
	}
	// Write to Register
	RCC->APB1RSTR.REG = reg;
	// Reset Based on Timer
	if(TIM_CONFIGx->TIMx == TIM2){
		reg &= ~RCC_APB1RSTR_TIM2RST;
	}
	if(TIM_CONFIGx->TIMx == TIM3){
		reg &= ~RCC_APB1RSTR_TIM3RST;
	}
	if(TIM_CONFIGx->TIMx == TIM4){
		reg &= ~RCC_APB1RSTR_TIM4RST;
	}
	// Local Delay
	while(i--);
	// Write to Register
	RCC->APB1RSTR.REG = reg;
}

/**
 * @brief Triggers an update event to apply the settings
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void update_GPT_params(timer_config_t* TIM_CONFIGx){
	// Send an update event to reset the timer and apply settings
  	TIM_CONFIGx->TIMx->EGR.REG |= TIM_EGR_UG;
	// Wait until bit reset by Hardware
	while(TIM_CONFIGx->TIMx->EGR.REG & TIM_EGR_UG);
	// Clear the update flag
	TIM_CONFIGx->TIMx->SR.REG &= ~TIM_SR_UIF; 
}

/**
 * @brief Calculates the Prescaler Value based upon ARR Value provided
 * @param[in] freq_Hz Frequency (in Hz)
 * @param[in] arr_value Auto-Reload Register Value
 * @return Prescaler Value
 */
__attribute__((always_inline)) inline uint16_t calc_GPT_PSC(uint32_t freq_Hz, uint16_t arr_value){
	
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
 * @brief Retrieves the TIMx Interrupt Status
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @returns UIF Flag Status
 */
__attribute__((always_inline)) inline uint8_t get_TIMx_IRQ_status(timer_config_t* TIM_CONFIGx){
	// Update Interrupt Flag (UIF) Status
	return (uint8_t)(TIM_CONFIGx->TIMx->SR.REG & TIM_SR_UIF);
}

/**
 * @brief Clears the pending interrupt of TIMx 
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @returns UIF Flag Status
 */
__attribute__((always_inline)) inline void clear_TIMx_IRQ_status(timer_config_t* TIM_CONFIGx){
	// Clear Update Interrupt Flag (UIF)
	TIM_CONFIGx->TIMx->SR.REG &= ~TIM_SR_UIF;
}

/**
 * @brief Retrieves the IRQn based upon TIMx
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @returns IRQn (0 - 59)
 */
__attribute__((always_inline)) inline uint8_t get_TIMx_IRQn(GPT_REG_STRUCT* TIMx){
	// Return IRQn based upon TIMx
	if(TIMx == TIM2)	
		return TIM2_IRQn;	
	else if(TIMx == TIM3)	
		return TIM3_IRQn;		
	else if(TIMx == TIM4)	
		return TIM4_IRQn;		
}

/**
 * @brief Configures the General Purpose Timer (GPT)
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 */
void config_GPT(timer_config_t* TIM_CONFIGx);

/**
 * @brief Gets the GP Timer Clock Frequency
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @returns Timer Frequency	
 */
uint32_t get_GPT_freq(timer_config_t* TIM_CONFIGx);

/**
 * @brief General Purpose Timer Delay
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @param[in] delayMs Number of milliseconds
 */
void GPT_delay_ms(timer_config_t* TIM_CONFIGx, volatile uint32_t delayMs);

/**
 * @brief Configures the default parameters for TIM_CONFIGx
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void load_GPT_default(timer_config_t* TIM_CONFIGx){
	// Configure Mode and Configuration for GPIO
	TIM_CONFIGx->GPIO_CONFIGx->MODEx = MODE_OUT_10MHz;
	TIM_CONFIGx->GPIO_CONFIGx->CNFx = CNF_OUT_GP_PP;
	// Configure ARR, Frequency & Count
	TIM_CONFIGx->auto_reload = DEFAULT_ARR_VALUE;
	TIM_CONFIGx->frequency_Hz = FREQ_10kHz;
	TIM_CONFIGx->count = DEFAULT_CNT_VALUE;
	// CMS Mode Selection (Edge Mode Selection)
	TIM_CONFIGx->cms_mode = CMS_EDGE;
	// Counting Direction (Up Counting)
	TIM_CONFIGx->direction = TIMx_COUNT_UP;
	// ARPE
	TIM_CONFIGx->arpe = TIMx_ARPE_ENABLE;
	// One Pulse Mode (OFF)
	TIM_CONFIGx->one_pulse = TIMx_OPM_DISABLE;
	// IRQ Disable
	TIM_CONFIGx->enable_IRQ = TIMx_IRQ_DISABLE;
}

#endif /* __TIMER_H__ */
