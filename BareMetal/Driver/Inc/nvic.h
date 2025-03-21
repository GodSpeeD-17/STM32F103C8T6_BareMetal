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
*/

// Header Guards
#ifndef __NVIC_H__
#define __NVIC_H__

// Main Library
#include "reg_map.h"

/**
 * @brief Enables the NVIC Interrupt for the input IRQn
 * @param[in] IRQn  The Interrupt Number
 * @note Global Interrupt Configuration
 */
__attribute__((always_inline)) inline void NVIC_IRQ_enable(uint8_t IRQn){
	// Enable the IRQn
	NVIC->ISER[(IRQn) >> 5] |=  (1 << ((IRQn) & 0x1F));
	// >> 5 := Divide the number by 32(2^5) [Each register has 32-bits]
	// & 0x1F := Wrap the number within 32 i.e 0 - 31 [Each bit representation]
}

/**
 * @brief Disables the NVIC Interrupt for the input IRQn
 * @param[in] IRQn  The Interrupt Number
 * @note Global Interrupt Configuration
 */
__attribute__((always_inline)) inline void NVIC_IRQ_disable(uint8_t IRQn){
	// Disable the IRQn
	NVIC->ICER[(IRQn) >> 5] |=  (1 << ((IRQn) & 0x1F));
	// >> 5 := Divide the number by 32 (2^5) [Each register has 32-bits]
	// & 0x1F := Wrap the number within 32 i.e 0 - 31 [Each bit representation]
}

#endif /* __NVIC_H__ */
