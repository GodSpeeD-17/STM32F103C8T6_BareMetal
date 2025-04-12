/***************************************************************************************
 *  File: systick.h
 *  Created on: 10/10/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __SYSTICK_H__
#define __SYSTICK_H__

// Dependency
#include "reg_map.h"

// Delay Variable
static volatile uint64_t future_ticks = 0x00;
// Ticks Counter
static volatile uint64_t curr_ticks = 0x00;

/**
 * @brief Enables SysTick Counter
 */
__INLINE__ void SysTick_enable(void){
	// Enable SysTick
	SysTick->CTRL.REG |= SysTick_CTRL_ENABLE_Msk;
}

/**
 * @brief Disables SysTick Counter
 */
__INLINE__ void SysTick_disable(void){
	// Disable SysTick
	SysTick->CTRL.REG &= ~SysTick_CTRL_ENABLE_Msk;
}

/**
 * @brief Configures the SysTick Timer based upon the input count value
 * @param[in] reloadValue Number of Ticks
 * @note Value should be within the range of 24-bit unsigned integer
 */
void SysTick_Config(uint32_t reloadValue);

/***
 * @brief Accurate us delay generation
 * @param[in] delayTime Delay in microseconds (us)
 * @note Based upon SysTick Timer
 */
__INLINE__ void delay_us(uint32_t delayTime){
	// Calculate the delay time
	future_ticks = curr_ticks + delayTime;
	// Wait for delay
	while(curr_ticks <= future_ticks);
}

/***
 * @brief Accurate ms delay generation
 * @param[in] delayTime Delay in milliseconds (ms)
 * @note Based upon SysTick Timer
 */
__INLINE__ void delay_ms(uint32_t delayTime){
	// Calculate the delay time
	while(delayTime--){
		// Wait for 1ms
		delay_us(1000);
	}
}

/**
 * @brief Returns the current number of ticks
 * @note The ticks are dependent on Core Clock Frequency
 */
__INLINE__ uint64_t SysTick_getCurrTicks(void){
	// Return final Value
	return curr_ticks;
}

/**
 * @brief Sets the current number of ticks
 * @param[in] tick_value The number of ticks to be set
 * @note The ticks are dependent on Core Clock Frequency
 */
__INLINE__ void SysTick_setCurrTicks(uint64_t tick_value){
	// Set the Current number of Ticks as `tick_value`
	curr_ticks = tick_value;
}

/***
 * @brief ISR for SysTick
 * @note Used for Delay Generation and Getting the total Number of Ticks
 */
__attribute__((weak)) void SysTick_Handler(void);

#endif /* __SYSTICK_H__ */