// Header Guards
#ifndef __ARM_REG_MAP_H__
#define __ARM_REG_MAP_H__

/*********************************************** Custom Declaration ***********************************************/// Common Libraries
#include "common.h"
/*********************************************** Custom Declaration ***********************************************/// Common Libraries

// CPU ID Register Structure
typedef struct {
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		struct {
			// Revision ID: Implementation defined revision number
			volatile uint32_t REV_ID: 4;
			// Part Number: Number of processor within family
			// [11:10] b11 = Cortex family
			// [9:8] b00 = version
			// [7:6] b00 = reserved
			// [5:4] b10 = M (v7-M)
			// [3:0] X = family member. Cortex-M3 family is b0011
			volatile uint32_t PART_NO: 12;
			// Constant: Reads as 0xF
			volatile uint32_t CONSTANT: 4;
			// Variant: Implementation defined variant number
			volatile uint32_t VARIANT: 4;
			// Implementer code: ARM is 0x41
			volatile uint32_t IMPLEMENTER: 8;
		} BIT;
	} CPU_ID;
} CPU_ID_REG_MAP;

// System Control Register Structure (Power Control)
typedef struct {
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Field Access
		struct {
			// Reserved
			volatile uint32_t RESERVED_0: 1;
			// Sleep on exit when returning from Handler mode to Thread mode
			// Enables interrupt driven applications to avoid returning to empty main application
			// - 1 = sleep on ISR exit
			// - 0 = do not sleep when returning to Thread mode
			volatile uint32_t SLEEPONEXIT: 1;
			// Sleep on exit when returning from Handler mode to Thread mode
			// - 1 = indicates to the system that Cortex-M3 clock can be stopped. Setting this bit causes the SLEEPDEEP port to be asserted when the processor can be stopped.
			// - 0 = not OK to turn off system clock.
			volatile uint32_t SLEEPDEEP: 1;
			// Reserved
			volatile uint32_t RESERVED_1: 1;
			// When enabled, this causes WFE to wake up when an interrupt moves from inactive to pended. 
			// Otherwise, WFE only wakes up from an event signal, external and SEV instruction generated. 
			// The event input, RXEV, is registered even when not waiting for an event, and so effects the next WFE.
			volatile uint32_t SEVONPEND: 1;
			// Reserved
			volatile uint32_t RESERVED_2: 27;
		} BIT;
	} SCR;
} SCR_REG_MAP;

#endif /* __ARM_REG_MAP_H__ */