/***************************************************************************************
 *  File: systick.c
 *  Created on: 10/10/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Main Header File
#include "systick.h"

// Delay Variable
static volatile uint64_t future_ticks = 0x00;
// Ticks Counter
static volatile uint64_t curr_ticks = 0x00;

/**
 * @brief Configures the SysTick Timer based upon the input count value
 * @param[in] reloadValue Number of Ticks
 * @note Value should be within the range of 24-bit unsigned integer
 */
void SysTick_config(uint32_t reloadValue){
	// Reset Value
	SysTick->CTRL.REG = (uint32_t) 0x00;
	// Reload Value (24-bit)
	SysTick->LOAD = (reloadValue - 1) & 0x00FFFFFF;
	// Update Current Value
	SysTick->VAL = (uint32_t) 0x00;
	// Set Core as Reference Clock
	SysTick->CTRL.REG |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

/***
 * @brief Accurate delay generation
 * @param[in] delayTime Delay in Milliseconds
 * @note Based upon SysTick Timer
 */
void delay_ms(uint32_t delayTime){
	// Calculate the delay time
	future_ticks = curr_ticks + delayTime;
	// Wait for delay
	while(curr_ticks <= future_ticks);
}

/**
 * @brief Returns the current number of ticks
 * @note The ticks are dependent on Core Clock Frequency
 */
uint64_t SysTick_getCurrTicks(void){
	// Final Value
	uint64_t return_value = 0x00;
	// Current number of Ticks
	return_value = curr_ticks;
	// Return final Value
	return return_value;
}

/**
 * @brief Sets the current number of ticks
 * @param[in] tick_value The number of ticks to be set
 * @note The ticks are dependent on Core Clock Frequency
 */
void SysTick_setCurrTicks(uint64_t tick_value){
	// Set the Current number of Ticks as `tick_value`
	curr_ticks = tick_value;
}

/***
 * @brief ISR for SysTick
 * @note Used for Delay Generation and Getting the total Number of Ticks
 */
__attribute__((weak)) void SysTick_Handler(void){
	
	/*********************************************** USER CODE ***********************************************/

	/*********************************************** USER CODE ***********************************************/

	/*********************************************** DO NOT COMMENT ***********************************************/
	// Delay (Non-blocking)
	curr_ticks++;
	/*********************************************** DO NOT COMMENT ***********************************************/
}
