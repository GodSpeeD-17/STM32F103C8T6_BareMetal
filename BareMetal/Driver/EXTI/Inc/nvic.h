/***************************************************************************************
 *  File: nvic.h
 *  Created on: 17/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/
/*
	THEORY: 
		NVIC: Nested Interrupt Vector Configuration
			- Global Interrupt Configuration (ARM)
			- NVIC is used to configure the priority of interrupts
		- >> 5 := Divide the number by 32(2^5) [Each register has 32-bits]
		- & 0x1F := Wrap the number within 32 i.e 0 - 31 [Each bit representation]
*/

// Header Guards
#ifndef __NVIC_H__
#define __NVIC_H__

// Main Library
#include "reg_map.h"
// Alternate Function I/O
#include "rcc.h"

/**
 * @brief Enables the NVIC Interrupt for the input IRQn
 * @param[in] IRQn The Interrupt Number
 * @note Global Interrupt Configuration
 */
__INLINE__ void NVIC_IRQ_Enable(uint8_t IRQn){
	// Enable the IRQn
	NVIC->ISER[(IRQn) >> 5] |=  (1 << (IRQn & 0x1F));
}

/**
 * @brief Disables the NVIC Interrupt for the input IRQn
 * @param[in] IRQn The Interrupt Number
 * @note Global Interrupt Configuration
 */
__INLINE__ void NVIC_IRQ_Disable(uint8_t IRQn){
	// Disable the IRQn
	NVIC->ICER[(IRQn) >> 5] |=  (1 << (IRQn & 0x1F));
}

/**
 * @brief Software IRQ Trigger
 * @param[in] IRQn The Interrupt Number
 */
__INLINE__ void NVIC_IRQ_Software_Trigger(uint8_t IRQn){
	// Set Pending Register
	NVIC->ISPR[(IRQn >> 5)] = (1 << (IRQn & 0x1F));
}

#endif /* __NVIC_H__ */
