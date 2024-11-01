/***************************************************************************************
 *  File: systick.h
 *  Created on: 10/10/2024
 *  Author: shrey_shah
 ***************************************************************************************/

// Header Guards
#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "reg_map.h"

// SysTick
#define SYSTICK_CLK_EXT					((uint8_t) 0)
#define SYSTICK_CLK_CORE				((uint8_t) 1)

/**
 * @brief Enables SysTick Counter
 */
static inline void enable_SysTick(void);

/**
 * @brief Disables SysTick Counter
 */
static inline void disable_SysTick(void);

/**
 * @brief Configures the SysTick Timer based upon the input count value
 * @note Value should be within the range of 24-bit unsigned integer
 */
void config_SysTick(uint32_t reloadValue);

/***
 * @brief Accurate delay generation
 * @note Based upon SysTick Timer
 */
void SysTick_delay_ms(uint32_t delayTime);

/**
 * @brief Returns the current number of ticks
 * @note The ticks are dependent on Core Clock Frequency
 */
uint64_t get_curr_ticks(void);

/**
 * @brief Sets the current number of ticks
 * @param[in] tick_value The number of ticks to be set
 * @note The ticks are dependent on Core Clock Frequency
 */
void set_curr_ticks(uint64_t tick_value);

/***
 * @brief ISR for SysTick
 */
__attribute__((weak)) void SysTick_Handler(void);

#endif /* _SYSTICK_H_ */