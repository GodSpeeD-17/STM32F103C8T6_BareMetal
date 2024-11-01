/***************************************************************************************
 *  File: systick.c
 *  Created on: 10/10/2024
 *  Author: shrey_shah
 ***************************************************************************************/

// Main Header File
#include "systick.h"

// Delay Variable
static volatile uint32_t delayMs = 0x00;
// Ticks Counter
static volatile uint64_t curr_ticks = 0x00;

/**
 * @brief Enables SysTick Counter
 */
static inline void enable_SysTick(void){
	// Enable the SysTick
	SYSTICK->CSR.BIT.EN = BIT_SET;
}

/**
 * @brief Disables SysTick Counter
 */
static inline void disable_SysTick(void){
	// Disable the SysTick
	SYSTICK->CSR.BIT.EN = BIT_RESET;
}

/**
 * @brief Configures the SysTick Timer based upon the input count value
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
	// Return Current number of Ticks
	return curr_ticks;
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
 */
__attribute__((weak)) void SysTick_Handler(void){

	// Delay (!!! DO NOT COMMENT !!!)
	if(delayMs){
		delayMs--;
	}

	// Increment Ticks Counter (!!! DO NOT COMMENT !!!)
	curr_ticks++;
}


