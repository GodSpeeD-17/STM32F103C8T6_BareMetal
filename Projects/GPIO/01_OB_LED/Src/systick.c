// Main Header File
#include "systick.h"

// TODO: Need to find a way for 64-bit handling
// TODO: When carrying out any operation, by default 32-bit is assumed
// TODO: This causes overflow in input data & very large 64-bit values
// TODO: Causes issues with timing and delays
// Tick Counter for microseconds
static volatile uint32_t tickCount = 0x00;

/**
 * @brief Returns the current number of ticks
 * @note The ticks are dependent on Core Clock Frequency
 */
uint32_t SysTick_Get_Ticks(void)
{
	// Return final Value
	return tickCount;
}

/**
 * @brief Sets the current number of ticks
 * @param tick_value The number of ticks to be set
 * @note The ticks are dependent on Core Clock Frequency
 */
void SysTick_Set_Ticks(uint32_t tick_value)
{
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
void SysTick_Config(uint32_t reloadValue)
{
	// Reset Value
	SysTick->CTRL.REG = 0x00;
	// Set Reload Value
	SysTick->LOAD = SYSTICK_WRAP_VAL(reloadValue - 1);
	// Set Current Value as `reloadValue`
	SysTick->VAL = SYSTICK_WRAP_VAL(reloadValue - 1);
	// Set Core as Reference Clock & enable SysTick Interrupt
	SysTick->CTRL.REG = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk);
}

// Delay using SysTick
#ifdef SYSTICK_DELAY__
/**
 * @brief Accurate us delay generation
 * @param delayTime Delay in microseconds (us)
 * @note Based upon SysTick Timer
 */
void delay_us(uint32_t delayTime)
{
	// Get Reference Ticks
	uint32_t refTicks = tickCount;
	// Wait for delay
	while ((tickCount - refTicks) <= delayTime)
		;
}

/**
 * @brief Accurate ms delay generation
 * @param delayTime Delay in milliseconds (ms)
 * @note Based upon SysTick Timer
 */
void delay_ms(uint32_t delayTime)
{
	// Calculate the delay time
	delay_us(delayTime * 1000);
}
#endif /* SYSTICK_DELAY__ */

/**
 * @brief ISR for SysTick
 * @note Used for Delay Generation and Getting the total Number of Ticks
 */
void SysTick_Handler(void)
{

	/*********************************************** DO NOT COMMENT ***********************************************/
	// Delay (Non-blocking)
	tickCount++;
	/*********************************************** DO NOT COMMENT ***********************************************/

	/*********************************************** USER CODE ***********************************************/

	/*********************************************** USER CODE ***********************************************/
}
