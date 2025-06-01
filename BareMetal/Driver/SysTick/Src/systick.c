/***************************************************************************************
 *  File: systick.c
 *  Created on: 10/10/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Main Header File
#include "systick.h"
#include "rcc.h"

// Delay Variable
static volatile uint64_t future_ticks = 0x00;
// Ticks Counter
static volatile uint64_t curr_ticks = 0x00;
// Default SysTick Configuration
static systick_config_t default_systick_config = {
	.CLK_SRC = 1, // Core Clock
	.TICK_INT = 1, // Enable SysTick Interrupt
	.LOAD = 0x00FFFFFF,
	.VAL = 0x00 // Initial Value
};

/**
 * @brief Returns the current number of ticks
 * @note The ticks are dependent on Core Clock Frequency
 */
uint64_t SysTick_Get_Ticks(void){
	// Return final Value
	return curr_ticks;
}

/**
 * @brief Sets the current number of ticks
 * @param[in] tick_value The number of ticks to be set
 * @note The ticks are dependent on Core Clock Frequency
 */
void SysTick_Set_Ticks(uint64_t tick_value){
	// Set the Current number of Ticks as `tick_value`
	curr_ticks = tick_value;
	// Update the SysTick Current Value Register (24-bit)
	SysTick->VAL = tick_value & 0x00FFFFFF;
}

/**
 * @brief Configures the SysTick Timer based upon the input count value
 * @param[in] reloadValue Number of Ticks
 * @note Value should be within the range of 24-bit unsigned integer
 */
void SysTick_Config(uint32_t reloadValue){
	// Reset Value
	SysTick->CTRL.REG = 0x00;
	// Reload Value (24-bit)
	SysTick->LOAD = ((reloadValue - 1) & 0x00FFFFFF);
	// Update Current Value
	SysTick->VAL = 0x00;
	// Set Core as Reference Clock
	SysTick->CTRL.REG = (SysTick_CTRL_CLKSOURCE_Msk | 
						 SysTick_CTRL_TICKINT_Msk | 
						 SysTick_CTRL_ENABLE_Msk);
}

/***
 * @brief Accurate us delay generation
 * @param[in] delayTime Delay in microseconds (us)
 * @note Based upon SysTick Timer
 */
void delay_us(uint32_t delayTime){
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
void delay_ms(uint32_t delayTime){
	// Calculate the delay time
	while(delayTime--){
		// Wait for 1ms
		delay_us(1000);
	}
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
	if(curr_ticks <= (uint64_t) 0xFFFFFFFFFFFFFFF)
		curr_ticks++;
	else
		curr_ticks = 0;
	/*********************************************** DO NOT COMMENT ***********************************************/
}
