/***************************************************************************************
 *  File: systick.c
 *  Created on: 10/10/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Main Header File
#include "systick.h"

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
	SysTick->CTRL.REG = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
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
