// Header Guards
#ifndef __SYSTICK_REG_MAP_H__
#define __SYSTICK_REG_MAP_H__

// Core C Library
#include <stdint.h>

// SysTick Structure
typedef struct {
	// Control and Status Register (CSR)
	union{
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t EN: 1;
			volatile uint32_t TICKINT: 1;
			volatile uint32_t CLKSRC: 1;
			volatile uint32_t resereved_1: 13;
			volatile uint32_t CNTFLAG: 1;
			volatile uint32_t reserved_2: 15;
		} BIT;
	} CSR;

	// Reload Value Register (RELOAD)
	uint32_t RELOAD_VALUE: 24;					// 24-bit used only (From LSB)

	// Current Value Register (CURRENT)
	uint32_t CURR_VALUE: 24;					// 24-bit used only (From LSB)

	// Calibration Value Register (CAL)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t TENMS: 24;
			volatile uint32_t reserved: 6;
			volatile uint32_t SKEW: 1;
			volatile uint32_t NOREF: 1;
		} BIT;
	} CAL;
} SYSTICK_REG_STRUCT;

#endif /* __SYSTICK_REG_MAP_H__ */ 
