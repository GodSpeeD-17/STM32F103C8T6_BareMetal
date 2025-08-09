// Header Guards
#ifndef __SYSTICK_CONFIG_H__
#define __SYSTICK_CONFIG_H__

// Register Mapping
#include "reg_map.h"
// RCC Configuration
#include "rcc.h"

// SysTick Configuration Structure
typedef struct {
	// SysTick Clock Source
	// - 0: External Reference Clock
	// - 1: Core Clock (AHB Clock)
	uint32_t CLK_SRC: 1;
	// SysTick Interrupt
	// - 0: Counting Down to 0 does not pend the `SysTick_Handler`
	// - 1: Counting Down to 0 pends the `SysTick_Handler`
	uint32_t TICK_INT: 1;
	// SysTick Reload Value Register
	// - 24-bit value that is loaded into the counter register
	uint32_t LOAD: 24;
	// SysTick Current Value Register
	uint32_t VAL;
} systick_config_t;

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

#endif /* __SYSTICK_CONFIG_H__ */