/***************************************************************************************
 *  File: gpt.h
 *  Created on: 23/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __GPT_H__
#define __GPT_H__

// Register Mapping
#include "reg_map.h"
#include "rcc.h"		// Required for get_APB1_freq()
#include "gpio.h"		// Required for Configuration
#include "nvic.h"		// IRQ Configuration

// Timer Configuration Structure
typedef struct {
	// GPIO Structure
	gpio_config_t* GPIO_CONFIGx;
    // General Purpose Timer
    GPT_REG_STRUCT* GP_TIMx;
	// General Purpose Timer Channel
    uint8_t channel;
    // Auto Reload Value
    uint16_t auto_reload_value;
    // Frequency
    uint32_t frequency_Hz;
    // Count
    uint16_t count;
    // Centre-Aligned Mode Selection
	uint8_t cms_mode;
    // Count Direction
	uint8_t direction;
	// Auto-Reload Preload Enable
	uint8_t auto_reload_preload;
	// One-Pulse Mode
	uint8_t one_pulse;
	// IRQ Enable
	uint8_t enable_IRQ;
} gpt_config_t;

/**
 * @brief Enables the Clock for General Purpose Timer
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void enable_GPT_clk(gpt_config_t* GPT_CONFIGx){
	// Enable the clock for the timer
	if(GPT_CONFIGx->GP_TIMx == TIM2)
		RCC->APB1ENR.BIT.TIM2EN = BIT_SET;
	else if(GPT_CONFIGx->GP_TIMx == TIM3)
		RCC->APB1ENR.BIT.TIM3EN = BIT_SET;
	else if(GPT_CONFIGx->GP_TIMx == TIM4)
		RCC->APB1ENR.BIT.TIM4EN = BIT_SET;
}

/**
 * @brief Disables the Clock for General Purpose Timer
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 * @note RCC->APB1ENR
 */
__attribute__((always_inline)) inline void disable_GPT_clk(gpt_config_t* GPT_CONFIGx){
	// Disable the clock for the timer
	if(GPT_CONFIGx->GP_TIMx == TIM2)
		RCC->APB1ENR.BIT.TIM2EN = BIT_RESET;
	else if(GPT_CONFIGx->GP_TIMx == TIM3)
		RCC->APB1ENR.BIT.TIM3EN = BIT_RESET;
	else if(GPT_CONFIGx->GP_TIMx == TIM4)
		RCC->APB1ENR.BIT.TIM4EN = BIT_RESET;
}

/**
 * @brief Enables the General Purpose GP_TIMx
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void enable_GPT(gpt_config_t* GPT_CONFIGx){
    // Clear Update Interrupt Flag
    GPT_CONFIGx->GP_TIMx->SR.REG &= ~BIT_SET;
	// Enable GP_TIMx
	GPT_CONFIGx->GP_TIMx->CR1.REG |= BIT_SET;
}

/**
 * @brief Disables the General Purpose GP_TIMx
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void disable_GPT(gpt_config_t* GPT_CONFIGx){
	// Disable GP_TIMx
	GPT_CONFIGx->GP_TIMx->CR1.REG &= ~BIT_SET;
    // Clear Update Interrupt Flag
    GPT_CONFIGx->GP_TIMx->SR.REG &= ~BIT_SET;
}

/**
 * @brief Enables the General Purpose GP_TIMx's Channel
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 * @note Use this for single channel configuration
 */
__attribute__((always_inline)) inline void enable_GPT_CH(gpt_config_t* GPT_CONFIGx){
	// Enable the General Purpose Timer Channel
	if(GPT_CONFIGx->channel & TIMx_CHANNEL_1)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC1E = BIT_SET;
	if(GPT_CONFIGx->channel & TIMx_CHANNEL_2)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC2E = BIT_SET;
	if(GPT_CONFIGx->channel & TIMx_CHANNEL_3)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC3E = BIT_SET;
	if(GPT_CONFIGx->channel & TIMx_CHANNEL_4)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC4E = BIT_SET;
}

/**
 * @brief Disables the General Purpose GP_TIMx's Channel
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 * @note Use this for single channel configuration
 */
__attribute__((always_inline)) inline void disable_GPT_CH(gpt_config_t* GPT_CONFIGx){
	// Disable the General Purpose Timer Channel
	if(GPT_CONFIGx->channel & TIMx_CHANNEL_1)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC1E = BIT_RESET;
	if(GPT_CONFIGx->channel & TIMx_CHANNEL_2)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC2E = BIT_RESET;
	if(GPT_CONFIGx->channel & TIMx_CHANNEL_3)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC3E = BIT_RESET;
	if(GPT_CONFIGx->channel & TIMx_CHANNEL_4)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC4E = BIT_RESET;
}

/**
 * @brief Enables the General Purpose GP_TIMx's Multiple Channel
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
__attribute__((always_inline)) inline void enable_GPT_multi_CH(gpt_config_t* GPT_CONFIGx, uint8_t channel){
	// Enable the General Purpose Timer Channel
	if((GPT_CONFIGx->channel & channel) == TIMx_CHANNEL_1)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC1E = BIT_SET;
	if((GPT_CONFIGx->channel & channel) == TIMx_CHANNEL_2)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC2E = BIT_SET;
	if((GPT_CONFIGx->channel & channel) == TIMx_CHANNEL_3)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC3E = BIT_SET;
	if((GPT_CONFIGx->channel & channel) == TIMx_CHANNEL_4)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC4E = BIT_SET;
}

/**
 * @brief Disables the General Purpose GP_TIMx's Multiple Channel
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
__attribute__((always_inline)) inline void disable_GPT_multi_CH(gpt_config_t* GPT_CONFIGx, uint8_t channel){
	// Disable the General Purpose Timer Channel
	if((GPT_CONFIGx->channel & channel) == TIMx_CHANNEL_1)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC1E = BIT_RESET;
	if((GPT_CONFIGx->channel & channel) == TIMx_CHANNEL_2)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC2E = BIT_RESET;
	if((GPT_CONFIGx->channel & channel) == TIMx_CHANNEL_3)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC3E = BIT_RESET;
	if((GPT_CONFIGx->channel & channel) == TIMx_CHANNEL_4)
		GPT_CONFIGx->GP_TIMx->CCER.BIT.CC4E = BIT_RESET;
}

/**
 * @brief Resets the General Purpose GP_TIMx
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void reset_GPT(gpt_config_t* GPT_CONFIGx){
	// Local Variable
	uint16_t i = 10000;

    // Reset Based on GPT
    if(GPT_CONFIGx->GP_TIMx == TIM2){
        RCC->APB1RSTR.BIT.TIM2RST = BIT_SET;
		while(i--);
        RCC->APB1RSTR.BIT.TIM2RST = BIT_RESET;
    }
    else if(GPT_CONFIGx->GP_TIMx == TIM3){
        RCC->APB1RSTR.BIT.TIM3RST = BIT_SET;
		while(i--);
        RCC->APB1RSTR.BIT.TIM3RST = BIT_RESET;
    }
    else if(GPT_CONFIGx->GP_TIMx == TIM4){
        RCC->APB1RSTR.BIT.TIM4RST = BIT_SET;
		while(i--);
        RCC->APB1RSTR.BIT.TIM4RST = BIT_RESET;
    }
}

/**
 * @brief Triggers an update event to apply the settings
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void update_GPT_params(gpt_config_t* GPT_CONFIGx){
	// Send an update event to reset the timer and apply settings
  	GPT_CONFIGx->GP_TIMx->EGR.REG |= BIT_SET;
	// Wait until bit reset by Hardware
	while(GPT_CONFIGx->GP_TIMx->EGR.REG & 0x01);
	// Clear the update flag
	GPT_CONFIGx->GP_TIMx->SR.REG &= ~(1 << 0); 
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
 * @brief Retrieves the GP_TIMx Interrupt Status
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 * @returns UIF Flag Status
 */
__attribute__((always_inline)) inline uint8_t get_TIMx_IRQ_status(gpt_config_t* GPT_CONFIGx){
	// Update Interrupt Flag (UIF) Status
	return (uint8_t)(GPT_CONFIGx->GP_TIMx->SR.REG & 0x00000001);
}

/**
 * @brief Clears the pending interrupt of GP_TIMx 
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 * @returns UIF Flag Status
 */
__attribute__((always_inline)) inline void clear_TIMx_IRQ_status(gpt_config_t* GPT_CONFIGx){
	// Clear Update Interrupt Flag (UIF)
	GPT_CONFIGx->GP_TIMx->SR.REG &=  ~(1 << 0);
}

/**
 * @brief Retrieves the IRQn based upon TIMx
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @returns IRQn (0 - 59)
 */
__attribute__((always_inline)) inline uint8_t get_TIMx_IRQn(GPT_REG_STRUCT* GP_TIMx){
	// Return IRQn based upon TIMx
	if(GP_TIMx == TIM2)	
		return TIM2_IRQn;	
	else if(GP_TIMx == TIM3)	
		return TIM3_IRQn;		
	else if(GP_TIMx == TIM4)	
		return TIM4_IRQn;		
}

/**
 * @brief Configures the General Purpose Timer (GPT)
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
void config_GPT(gpt_config_t* GPT_CONFIGx);

/**
 * @brief Gets the GP Timer Clock Frequency
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
uint32_t get_GPT_freq(gpt_config_t* GPT_CONFIGx);

/**
 * @brief General Purpose Timer Delay
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 * @param[in] delayMs Number of milliseconds
 */
void GPT_delay_ms(gpt_config_t* GPT_CONFIGx, volatile uint32_t delayMs);

/**
 * @brief Configures the default parameters for GPT_CONFIGx
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void load_GPT_default(gpt_config_t* GPT_CONFIGx){
	// Configure Mode and Configuration for GPIO
	GPT_CONFIGx->GPIO_CONFIGx->MODEx = MODE_OUT_10MHz;
	GPT_CONFIGx->GPIO_CONFIGx->CNFx = CNF_OUT_GP_PP;
	// Configure ARR, Frequency & Count
	GPT_CONFIGx->auto_reload_value = DEFAULT_ARR_VALUE;
	GPT_CONFIGx->frequency_Hz = FREQ_10kHz;
	GPT_CONFIGx->count = DEFAULT_CNT_VALUE;
	// CMS Mode Selection (Edge Mode Selection)
	GPT_CONFIGx->cms_mode = CMS_EDGE;
	// Counting Direction (Up Counting)
	GPT_CONFIGx->direction = TIMx_COUNT_UP;
	// ARPE
	GPT_CONFIGx->auto_reload_preload = TIMx_ARPE_ENABLE;
	// One Pulse Mode (OFF)
	GPT_CONFIGx->one_pulse = TIMx_OPM_DISABLE;
	// IRQ Disable
	GPT_CONFIGx->enable_IRQ = TIMx_IRQ_DISABLE;
}

#endif /* __GPT_H__ */
