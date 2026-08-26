/**
 * @file	bsp_timer.h
 * @author	Shrey Shah
 * @brief	Declares the Blue Pill TIM4 microsecond-delay capability
 * @version	v1.0
 * @date	26-08-2026
 *
 * @details
 * This self-contained capability header exposes only the initialization and
 * steady-state operations needed by the board-locked TIM4 polling-delay
 * service. TIM4, RCC, and Timer configuration details remain private to
 * `bsp_timer.c`.
 */

// Header Guard
#ifndef BSP_TIMER_H_
#define BSP_TIMER_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "stm32f1xx_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup BSP_01_BoardSupport
 * @{
 */

#ifdef STM32F103C8T6__

// ==================================================================================================== //
// Board Timer APIs
// ==================================================================================================== //

/**
 * @brief Initializes the complete Blue Pill TIM4 microsecond-delay capability
 * @details
 * Validates the stable RCC-derived TIM4 input clock before enabling the TIM4
 * APB1 gate, resets the complete TIM4 register bank, and configures TIM4 as a
 * dedicated polling-only one-pulse counter with a 1 MHz tick. BSP owns this
 * complete RCC/Timer initialization transaction.
 *
 * @returns @ref driver_status_t "Board Timer-delay initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TIM4 was reset and configured as the 1 MHz delay source
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A fixed RCC or Timer mapping was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The required 72 MHz TIM4 input clock or TIM4 gate was unavailable
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: TIM4 was unexpectedly running during configuration
 * @pre The application has completed System/Core clock-tree configuration and
 * the RCC-derived bus frequencies are stable
 * @note This capability does not configure a Timer IRQ source or NVIC delivery
 * @warning Reserves TIM4 exclusively; no application timebase or other client
 * may own TIM4 while this capability is active
 */
driver_status_t BSP_InitTimerUSDelay(void);

/**
 * @brief Provides a minimum blocking delay through the board-locked TIM4 source
 * @details
 * Splits @p `delayUs` into transactions no larger than `65535 us` and forwards
 * each transaction to the Timer Driver's bounded polling-delay operation.
 *
 * @param[in] delayUs Delay duration in microseconds
 * Accepted values:
 * - `1UL..0xFFFFFFFFUL`: Blocking delay duration in microseconds
 * @returns @ref driver_status_t "Board Timer microsecond-delay status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every delay chunk completed
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `delayUs` was `0UL` or TIM4 state could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The TIM4 clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A bounded TIM4 polling transaction timed out
 * @pre BSP_InitTimerUSDelay() completed successfully and TIM4 retained its
 * exclusive BSP-owned configuration
 * @note This is a polling delay and never enables Timer IRQ or NVIC state
 */
driver_status_t BSP_TimerDelayUs(const uint32_t delayUs);

#endif /* STM32F103C8T6__ */

/** @} */ // BSP_01_BoardSupport

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BSP_TIMER_H_ */
