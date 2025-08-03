/***************************************************************************************
 *  File: systick.h
 *  Created on: 10/10/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __SYSTICK_H__
#define __SYSTICK_H__

// Dependency
#include "systick_config.h"

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
void SysTick_Config(uint32_t reloadValue);

/**
 * @brief Accurate us delay generation
 * @param delayTime Delay in microseconds (us)
 * @note Based upon SysTick Timer
 */
void delay_us(uint32_t delayTime);

/**
 * @brief Accurate ms delay generation
 * @param delayTime Delay in milliseconds (ms)
 * @note Based upon SysTick Timer
 */
void delay_ms(uint32_t delayTime);

/**
 * @brief Registers Callback Function for SysTick
 * @param callback Callback Function
 */
void SysTick_Register_Callback(void (*callback)(void));

/**
 * @brief ISR for SysTick
 * @note Used for Delay Generation and Getting the total Number of Ticks
 */
__attribute__((weak)) void SysTick_Handler(void);

#endif /* __SYSTICK_H__ */