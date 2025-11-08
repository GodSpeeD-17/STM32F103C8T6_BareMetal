// Header Guards
#ifndef STM32F1XX_SYSTICK_H__
#define STM32F1XX_SYSTICK_H__

// C++ Safeguards
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// Includes
#include <stdint.h>

// SysTick Structure
typedef volatile struct __SysTick_TypeDef 
{
	// Control and Status Register (CTRL)
	union{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t EN: 1;
			volatile uint32_t TICKINT: 1;
			volatile uint32_t CLKSRC: 1;
			volatile uint32_t resereved_1: 13;
			volatile uint32_t CNTFLAG: 1;
			volatile uint32_t reserved_2: 15;
		} BIT;
	} CTRL;

	// Reload Value Register (RELOAD)
	uint32_t LOAD: 24;					// 24-bit used only (From LSB)

	// Current Value Register (CURRENT)
	uint32_t VAL: 24;					// 24-bit used only (From LSB)

	// Calibration Value Register (CAL)
	union {
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t TENMS: 24;
			volatile uint32_t reserved: 6;
			volatile uint32_t SKEW: 1;
			volatile uint32_t NOREF: 1;
		} BIT;
	} CALIB;
} SysTick_TypeDef;

// C++ Safeguards
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_SYSTICK_H__ */ 
