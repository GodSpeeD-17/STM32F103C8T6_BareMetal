// Main Header File
#include "systick.h"
#include "gpio.h"

// Tick Counter for microseconds
static volatile uint64_t tickCount = 0x00;

/**
 * @brief Returns the current number of ticks
 * @note The ticks are dependent on Core Clock Frequency
 */
uint64_t SysTick_Get_Ticks(void){
	// Return final Value
	return tickCount;
}

/**
 * @brief Sets the current number of ticks
 * @param tick_value The number of ticks to be set
 * @note The ticks are dependent on Core Clock Frequency
 */
void SysTick_Set_Ticks(uint64_t tick_value){
	// SysTick Disable
	SysTick_Disable();
	// Set the Current number of Ticks as `tick_value`
	tickCount = tick_value;
	// Update the SysTick Current Value Register (24-bit)
	SysTick->VAL = SYSTICK_WRAP_VAL(tick_value - 1);
	// SysTick Enable
	SysTick_Enable();
}

/**
 * @brief Configures the SysTick Timer based upon the input count value
 * @param reloadValue Number of Ticks
 * @note - Value should be within the range of 24-bit unsigned integer
 * @note - Call `SysTick_Enable()` to start the SysTick Timer
 */
void SysTick_Config(uint64_t reloadValue){
	// Reset Value
	SysTick->CTRL.REG = 0x00;
	// Reload Value (24-bit)
	SysTick->LOAD = SYSTICK_WRAP_VAL(reloadValue - 1);
	// Update Current Value
	SysTick->VAL = 0x00;
	// Set Core as Reference Clock
	SysTick->CTRL.REG = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk);
}

/**
 * @brief Accurate us delay generation
 * @param delayTime Delay in microseconds (us)
 * @note Based upon SysTick Timer
 */
void delay_us(uint64_t delayTime){
	// Get Reference Ticks
	uint64_t refTicks = SysTick_Get_Ticks();
	// Wait for delay
	while((SysTick_Get_Ticks() - refTicks) <= delayTime){
		__WFI();
	}
}

/**
 * @brief Accurate ms delay generation
 * @param delayTime Delay in milliseconds (ms)
 * @note Based upon SysTick Timer
 */
void delay_ms(uint64_t delayTime){
	// Calculate the delay time
	delay_us(delayTime * 1000);
}

/**
 * @brief ISR for SysTick
 * @note Used for Delay Generation and Getting the total Number of Ticks
 */
void SysTick_Handler(void){

	/*********************************************** DO NOT COMMENT ***********************************************/
	// Delay (Non-blocking)
	tickCount++;
	/*********************************************** DO NOT COMMENT ***********************************************/

	/*********************************************** USER CODE ***********************************************/
	
	/*********************************************** USER CODE ***********************************************/
}
