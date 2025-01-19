// Header Guards
#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "stm32f1xx.h"

// Actual Variable
static volatile uint64_t ticks = 0x00;

/**
 * @brief Configures SysTick Downcounter
 * @param[in] ticks Tick Value (24-bit)
 */
void config_SysTick(uint32_t ticks);

/**
 * @brief SysTick Handler
 */
void SysTick_Handler(void);

/**
 * @brief Delay using SysTick
 * @param[in] delay_ms Number of milliseconds
 */
void delay_ms(const uint32_t delay_ms);

/**
 * @brief Returns the current SysTick Count
 * @param[out] ticks Current tick count
 */
uint64_t get_ticks(void);


#endif /* __SYSTICK_H__ */