/***************************************************************************************
 *  File: gpt.h
 *  Created on: 23/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __TIMER_H__
#define __TIMER_H__

// Register Mapping
#include "timer_config.h"

/**
 * @brief Calculates the Prescaler Value based upon ARR Value provided
 * @param[in] freq_Hz Frequency (in Hz)
 * @param[in] arr_value Auto-Reload Register Value
 * @return Prescaler Value
 */
uint16_t TIM_Calc_Prescaler(uint32_t freq_Hz, uint16_t arr_value);

/**
 * @brief Configures the General Purpose Timer (TIMx)
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 */
void TIM_config(timer_config_t* TIM_CONFIGx);

/**
 * @brief Gets the GP Timer Clock Frequency
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @returns Timer Frequency	
 */
uint32_t TIM_getFreq(timer_config_t* TIM_CONFIGx);

/**
 * @brief General Purpose Timer Delay
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 * @param[in] delayMs Number of milliseconds
 */
void TIM__delay_ms(timer_config_t* TIM_CONFIGx, volatile uint32_t delayMs);

/**
 * @brief Configures the default parameters for TIM_CONFIGx
 * @param[in] TIM_CONFIGx `timer_config_t *` structure containing the configuration
 */
__INLINE__ void TIM_load_default(timer_config_t* TIM_CONFIGx){
	// Configure Mode and Configuration for GPIO
	// TIM_CONFIGx->GPIO_CONFIGx->MODE = GPIOx_MODE_OUT_10MHz;
	// TIM_CONFIGx->GPIO_CONFIGx->CNF = GPIOx_CNF_OUT_GP_PP;
	// Configure ARR, Frequency & Count
	TIM_CONFIGx->auto_reload = DEFAULT_ARR_VALUE;
	// TIM_CONFIGx->frequency_Hz = FREQ_10kHz;
	TIM_CONFIGx->count = DEFAULT_CNT_VALUE;
	// CMS Mode Selection (Edge Mode Selection)
	TIM_CONFIGx->cms_mode = TIMx_CMS_EDGE;
	// Counting Direction (Up Counting)
	TIM_CONFIGx->direction = TIMx_DIR_COUNT_UP;
	// ARPE
	TIM_CONFIGx->arpe = TIMx_ARPE_ENABLE;
	// One Pulse Mode (OFF)
	TIM_CONFIGx->one_pulse = TIMx_OPM_DISABLE;
	// IRQ Disable
	// TIM_CONFIGx->enable_IRQ = TIMx_IRQ_DISABLE;
}

/**
 * @brief Creates a delay using Timer
 * @param[in] TIM_CONFIGx Timer Configuration Structure
 * @param[in] delayUs Number of microseconds to delay
 * @note Assuming, Timer is already configured for 1MHz
 */
void TIM_delay_us(timer_config_t* TIM_CONFIGx, volatile uint32_t delayUs);

/**
 * @brief Creates a delay using Timer
 * @param[in] TIM_CONFIGx Timer Configuration Structure 
 * @param[in] delayMs Number of milliseconds to delay
 * @note Depends upon `TIM_delay_us()`
 */
void TIM_delay_ms(timer_config_t* TIM_CONFIGx, volatile uint32_t delayMs);

#endif /* __TIMER_H__ */
