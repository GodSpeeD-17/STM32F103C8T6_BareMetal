/**
 * @file stm32f1xx_scb.h
 * @author Shrey Shah
 * @brief System Control Block Typedef
 * @version 1.0
 * @date 04-10-2025
 */
#ifndef __STM32F1XX_SCB_H__
#define __STM32F1XX_SCB_H__

// ---- Includes ---- //
#include "common.h"

/**
 * @brief System Control Block (SCB) - CPU Core Registers
 */
typedef struct {
	// CPUID Base Register
	uint32_t CPUID;
	// Interrupt Control State Register  
	uint32_t ICSR;
	// Vector Table Offset Register
	uint32_t VTOR;
	// Application Interrupt/Reset Control Register
	uint32_t AIRCR;
	// System Control Register
	uint32_t SCR;
	// Configuration Control Register
	uint32_t CCR;
	// System Handler Priority Register 1
	uint32_t SHPR1;
	// System Handler Priority Register 2
	uint32_t SHPR2;
	// System Handler Priority Register 3
	uint32_t SHPR3;
	// System Handler Control & State Register
	uint32_t SHCSR;
	// Configurable Fault Status Register
	uint32_t CFSR;
	// Hard Fault Status Register
	uint32_t HFSR;
	// Debug Fault Status Register
	uint32_t DFSR;
	// Mem Manage Fault Address Register
	uint32_t MMFAR;
	// Bus Fault Address Register
	uint32_t BFAR;
	// Auxiliary Fault Status Register
	uint32_t AFSR;
} SCB_TypeDef;

#endif /* __STM32F1XX_SCB_H__ */
