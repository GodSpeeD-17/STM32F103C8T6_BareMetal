// Driver Header
#include "systick.h"

/**
 * @brief Configures SysTick Downcounter
 * @param[in] ticks Tick Value (24-bit)
 */
void config_SysTick(uint32_t ticks){
	// Reset Control Register
	SysTick->CTRL = 0;
	// Reload Value
	SysTick->LOAD = (ticks - 1) & 0x00FFFFFF;
	// Current Value
	SysTick->VAL = 0;
	// Enable SysTick Counter
	SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
}

/**
 * @brief SysTick Handler
 */
void SysTick_Handler(void){
	ticks++;
}

/**
 * @brief Delay using SysTick
 * @param[in] delay_ms Number of milliseconds
 */
void delay_ms(const uint32_t delay_ms){
	uint64_t end = ticks + delay_ms;
	while(ticks < end){
		__asm("nop");
	}
}

/**
 * @brief Returns the current SysTick Count
 * @param[out] ticks Current tick count
 */
uint64_t get_ticks(void){
	return ticks;
}