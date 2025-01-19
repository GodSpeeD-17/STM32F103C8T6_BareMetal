/***************************************************************************************
 *  File: nvic.h
 *  Created on: 17/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/
/*
    THEORY: 
        NVIC: Nested Interrupt Vector Configuration
            - Global Interrupt Configuration
            - NVIC is used to configure the priority of interrupts
*/

// Header Guards
#ifndef __NVIC_H__
#define __NVIC_H__

// Main Library
#include "reg_map.h"

/*
// Stores the status of Interrupts before disabling it Globally
volatile uint32_t nvic_irq_enabled[2] = {0};
// volatile uint32_t nvic_irq_disabled[2] = {0};
*/

/**
 * @brief Disables the All the Interrupts Globally
 * @note NVIC->ICER, NVIC->ISER
 */
/*
__attribute__((always_inline)) inline void __disable_IRQ(void){
    for(uint8_t i = 0; i < 2; i++){
        // Store the previous state of the interrupt
        nvic_irq_enabled[i] = NVIC->ISER[i];
        // nvic_irq_disabled[i] = NVIC->ICER[i];
        // Disable all the interrupts
        NVIC->ICER[i] = 0xFFFFFFFF; 
    }
}
*/

/**
 * @brief Enables the All the Interrupts Globally
 * @note NVIC->ICER, NVIC->ISER
 */
/*
__attribute__((always_inline)) inline void __enable_IRQ(void){
    // Traverse through all the registers
    for(uint8_t i = 0; i < 2; i++){
        // Restore the previous state of the interrupts
        NVIC->ISER[i] = nvic_irq_enabled[i]; 
        // NVIC->ICER[i] = nvic_irq_disabled[i] ;
    }
}
*/

/**
 * @brief Enables the NVIC Interrupt for the input IRQn
 * @param[in] IRQn  The Interrupt Number
 * @note Global Interrupt Configuration
 */
__attribute__((always_inline)) inline void enable_NVIC_IRQ(uint8_t IRQn){
	// Clear the Disable IRQn
	NVIC->ICER[((IRQn) / 32)] &=  ~(1 << ((IRQn) & (32 - 1)));
    // Enable the IRQn
    NVIC->ISER[((IRQn) / 32)] |=  (1 << ((IRQn) & (32 - 1)));
}

/**
 * @brief Disables the NVIC Interrupt for the input IRQn
 * @param[in] IRQn  The Interrupt Number
 * @note Global Interrupt Configuration
 */
__attribute__((always_inline)) inline void disable_NVIC_IRQ(uint8_t IRQn){
	// Clear the Enable IRQn
	NVIC->ISER[((IRQn) / 32)] &=  ~(1 << ((IRQn) & (32 - 1)));
    // Disable the IRQn
    NVIC->ICER[((IRQn) / 32)] |=  (1 << ((IRQn) & (32 - 1)));
}

#endif /* __NVIC_H__ */
