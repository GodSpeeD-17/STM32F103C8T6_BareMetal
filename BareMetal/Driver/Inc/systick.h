/***************************************************************************************
 *  File: systick.h
 *  Created on: 10/10/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "reg_map.h"

/**
 * @brief Enables SysTick Counter
 */
__STATIC_INLINE__ void SysTick_enable(void){
	// Enable SysTick
	SysTick->CTRL.REG |= SysTick_CTRL_ENABLE_Msk;
}

/**
 * @brief Disables SysTick Counter
 */
__STATIC_INLINE__ void SysTick_disable(void){
	// Disable SysTick
	SysTick->CTRL.REG &= ~SysTick_CTRL_ENABLE_Msk;
}

/**
 * @brief Configures the SysTick Timer based upon the input count value
 * @param[in] reloadValue Number of Ticks
 * @note Value should be within the range of 24-bit unsigned integer
 */
void SysTick_config(uint32_t reloadValue);

/***
 * @brief Accurate delay generation
 * @param[in] delayTime Delay in Milliseconds
 * @note Based upon SysTick Timer
 */
void delay_ms(uint32_t delayTime);

/**
 * @brief Returns the current number of ticks
 * @note The ticks are dependent on Core Clock Frequency
 */
uint64_t SysTick_getCurrTicks(void);

/**
 * @brief Sets the current number of ticks
 * @param[in] tick_value The number of ticks to be set
 * @note The ticks are dependent on Core Clock Frequency
 */
void SysTick_setCurrTicks(uint64_t tick_value);

/***
 * @brief ISR for SysTick
 * @note Used for Delay Generation and Getting the total Number of Ticks
 */
__attribute__((weak)) void SysTick_Handler(void);

#endif /* __SYSTICK_H__ */