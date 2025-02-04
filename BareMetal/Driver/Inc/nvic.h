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
__attribute__((always_inline)) inline void enable_NVIC_IRQ(uint8_t IRQn){
    // Enable the IRQn
    NVIC->ISER[(IRQn) >> 5] |=  (1 << ((IRQn) & (32 - 1)));
}

/**
 * @brief Disables the NVIC Interrupt for the input IRQn
 * @param[in] IRQn  The Interrupt Number
 * @note Global Interrupt Configuration
 */
__attribute__((always_inline)) inline void disable_NVIC_IRQ(uint8_t IRQn){
    // Disable the IRQn
    NVIC->ICER[(IRQn) >> 5] |=  (1 << ((IRQn) & (32 - 1)));
}

#endif /* __NVIC_H__ */
