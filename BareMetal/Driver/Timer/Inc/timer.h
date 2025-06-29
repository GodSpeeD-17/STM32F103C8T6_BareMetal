/***************************************************************************************
 *  File: timer.h
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
 * @brief Configures the default parameters for TIMx_CONFIG
 * @param[in] TIMx_CONFIG `timer_config_t *` structure containing the configuration
 * @note - TIM & Channel should be already configured
 * @note - This loads frequency as 10kHz
 */
void TIM_10kHz_Load_Default(timer_config_t* TIMx_CONFIG);

/**
 * @brief Configures the default parameters for TIMx_CONFIG
 * @param[in] TIMx_CONFIG `timer_config_t *` structure containing the configuration
 * @note - TIM & Channel should be already configured
 * @note - This loads frequency as 1MHz
 */
void TIM_1MHz_Load_Default(timer_config_t* TIMx_CONFIG);

/**
 * @brief Configures the General Purpose Timer (TIMx)
 * @param[in] TIMx_CONFIG `timer_config_t *` structure containing the configuration
 */
void TIM_Config(timer_config_t* TIMx_CONFIG);

/**
 * @brief Creates a delay using Timer
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] delayUs Number of microseconds to delay
 * @note Assuming, Timer is already configured for 1MHz
 */
void TIM_delay_us(TIM_REG_STRUCT* TIMx, uint32_t delayUs);

/**
 * @brief Creates a delay using Timer
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] delayMs Number of milliseconds to delay
 * @note Assuming, Timer is already configured for 1MHz
 */
void TIM_delay_ms(TIM_REG_STRUCT* TIMx, uint32_t delayMs);

/**
 * @brief Enables Timer Interrupt for mentioned Interrupt
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_CMP_CHx`, `TIMx_IRQ_CAP_CHx`
 */
void TIM_IRQ_Enable(TIM_REG_STRUCT* TIMx, uint8_t IRQ);

/**
 * @brief Disables Timer Interrupt for mentioned Interrupt
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_CMP_CHx`, `TIMx_IRQ_CAP_CHx`
 */
void TIM_IRQ_Disable(TIM_REG_STRUCT* TIMx, uint8_t IRQ);

/**
 * @brief Timer Interrupt Flag Acknowledge
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_CMP_CHx`, `TIMx_IRQ_CAP_CHx`
 */
void TIM_IRQ_Ack(TIM_REG_STRUCT* TIMx, uint8_t IRQ);

/**
 * @brief Retrieves the Interrupt Status
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_CMP_CHx`, `TIMx_IRQ_CAP_CHx`
 * @return - 0: Interrupt was not triggered 
 * @return - 1: Interrupt was triggered 
 */
uint8_t TIM_Get_IRQ_Status(TIM_REG_STRUCT* TIMx, uint8_t IRQ);

/**
 * @brief Resets the General Purpose TIMx
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 */
void TIM_Reset(TIM_REG_STRUCT* TIMx);

/**
 * @brief Provides the Timer Frequency
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @returns Timer Frequency (in Hz)
 */
uint32_t TIM_Get_Frequency(TIM_REG_STRUCT* TIMx);

#endif /* __TIMER_H__ */
