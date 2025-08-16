// Header Guards
#ifndef __SYSTICK_H__
#define __SYSTICK_H__

// Register Mapping
#include "reg_map.h"
// RCC Configuration
#include "rcc.h"

// SysTick Wrap Value Macro
#define SYSTICK_WRAP_VAL(X) 				((X) & 0x00FFFFFF)

#ifdef __SYSTICK_CONFIG__
// SysTick Configuration Structure
typedef struct {
	// SysTick Clock Source
	// - 0: External Reference Clock
	// - 1: Core Clock (AHB Clock)
	uint64_t CLK_SRC: 1;
	// SysTick Interrupt
	// - 0: Counting Down to 0 does not pend the `SysTick_Handler`
	// - 1: Counting Down to 0 pends the `SysTick_Handler`
	uint64_t TICK_INT: 1;
	// SysTick Reload Value Register
	// - 24-bit value that is loaded into the counter register
	uint64_t LOAD: 24;
	// SysTick Current Value Register
	uint64_t VAL;
} systick_config_t;
#endif

/**
 * @brief Enables SysTick Counter
 */
__STATIC_INLINE__ void SysTick_Enable(void){
	// Disable Interrupts
	__disable_irq();
	// Enable SysTick
	SysTick->CTRL.REG |= SysTick_CTRL_ENABLE_Msk;
	// Enable Interrupts
	__enable_irq();
}

/**
 * @brief Disables SysTick Counter
 */
__STATIC_INLINE__ void SysTick_Disable(void){
	// Disable Interrupts
	__disable_irq();
	// Disable SysTick
	SysTick->CTRL.REG &= ~SysTick_CTRL_ENABLE_Msk;
	// Enable Interrupts
	__enable_irq();
}

/**
 * @brief Returns the current number of ticks
 * @note The ticks are dependent on Core Clock Frequency
 */
uint64_t SysTick_Get_Ticks(void);

/**
 * @brief Sets the current number of ticks
 * @param tick_value The number of ticks to be set
 * @note The ticks are dependent on Core Clock Frequency
 */
void SysTick_Set_Ticks(uint64_t tick_value);

/**
 * @brief Configures the SysTick Timer based upon the input count value
 * @param reloadValue Number of Ticks
 * @note Value should be within the range of 24-bit unsigned integer
 * @note Call `SysTick_Enable()` to start the SysTick Timer
 */
void SysTick_Config(uint64_t reloadValue);

/**
 * @brief Accurate us delay generation
 * @param delayTime Delay in microseconds (us)
 * @note Based upon SysTick Timer
 */
void delay_us(uint64_t delayTime);

/**
 * @brief Accurate ms delay generation
 * @param delayTime Delay in milliseconds (ms)
 * @note Based upon SysTick Timer
 */
void delay_ms(uint64_t delayTime);

/**
 * @brief ISR for SysTick
 * @note Used for Delay Generation and Getting the total Number of Ticks
 */
void SysTick_Handler(void);

#endif /* __SYSTICK_H__ */