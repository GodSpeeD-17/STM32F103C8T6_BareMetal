/***************************************************************************************
 *  File: systick.c
 *  Created on: 10/10/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Main Header File
#include "systick.h"

// Delay Variable
static volatile uint32_t delayMs = 0x00;
// Ticks Counter
static volatile uint64_t curr_ticks = 0x00;

/**
 * @brief Configures the SysTick Timer based upon the input count value
 * @param[in] reloadValue Number of Ticks
 * @note Value should be within the range of 24-bit unsigned integer
 */
void config_SysTick(uint32_t reloadValue){
    
	// Infinite Interrupts or Reload Value beyond register scope
    if((!reloadValue) || (reloadValue > 0x00FFFFFF)){
        return;
    }

    // Reset Value
	SYSTICK->CSR.REG = (uint32_t) 0x00;
	// Reload Value (24-bit)
	SYSTICK->RELOAD_VALUE = reloadValue - 1;
	// Update Current Value
	SYSTICK->CURR_VALUE = (uint32_t) 0x00;
    // Set Core as Reference Clock
	SYSTICK->CSR.BIT.CLKSRC = SYSTICK_CLK_CORE;
    // Enable Interrupt
	SYSTICK->CSR.BIT.TICKINT = BIT_SET;
	// Enable the SysTick
	SYSTICK->CSR.BIT.EN = BIT_SET;
}

/***
 * @brief Accurate delay generation
 * @param[in] delayTime Delay in Milliseconds
 * @note Based upon SysTick Timer
 */
void SysTick_delay_ms(uint32_t delayTime){
	// Update the delay time
	delayMs = delayTime;
	// Wait (delayMs != 0)
	while(delayMs);
}

/**
 * @brief Returns the current number of ticks
 * @note The ticks are dependent on Core Clock Frequency
 */
uint64_t get_curr_ticks(void){
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
void set_curr_ticks(uint64_t tick_value){
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
	// Delay (Blocking)
	if(delayMs){
		delayMs--;
	}
	// Delay (Non-blocking)
	curr_ticks++;
	/*********************************************** DO NOT COMMENT ***********************************************/
}
