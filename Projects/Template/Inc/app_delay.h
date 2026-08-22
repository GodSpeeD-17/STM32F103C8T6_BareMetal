/**
 * @file	app_delay.h
 * @author	Shrey Shah
 * @brief	Declares blocking-delay policy owned by the application
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section APP_DELAY_H_HIERARCHY Hierarchy
 * - Position: Layer 2 - Application service
 * - Used by: Layer 3 application orchestration and behavior
 * - Uses: Layer 2 `app_time` and optional Layer 1 Timer Driver
 *
 * @section APP_DELAY_H_RESPONSIBILITY Responsibility
 * This interface exposes blocking waits without exposing the timing hardware.
 * Millisecond waits use the monotonic application timebase; optional
 * microsecond waits use one dedicated general-purpose Timer.
 *
 * @section APP_DELAY_H_BOUNDARY Dependency Boundary
 * This header includes only application configuration and shared types. The
 * implementation alone may include `app_time.h`, Core intrinsics, RCC, and
 * Timer; neither delay path owns Timer IRQ sources or NVIC delivery.
 */

// Header Guard
#ifndef APP_DELAY_H_
#define APP_DELAY_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //

#include "app_config.h"
#include "stm32f1xx_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Application blocking-delay services
 * @defgroup APP_Delay Application Delay
 * @ingroup APP_Template
 * @{
 */

// ==================================================================================================== //
// Millisecond Blocking Delay
// ==================================================================================================== //

/**
 * @brief Provides a blocking millisecond delay using the application timebase
 * @details
 * Captures the current millisecond tick, sleeps with `WFI` between interrupts,
 * and returns when unsigned elapsed-time subtraction reaches @p delayMs. The
 * transaction does not reconfigure SysTick or any general-purpose Timer.
 * @param[in] delayMs Requested delay in milliseconds
 * Accepted values:
 * - `1U..0x7FFFFFFFU`: Wrap-safe interval of at most approximately 24.85 days
 * @returns @ref driver_status_t "Application millisecond-delay status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested tick interval elapsed
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `delayMs` was zero or exceeded the wrap-safe interval range
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The timebase was disabled, the
 * call originated in an exception, or global interrupts were disabled
 * @pre @ref App_Init successfully configured and enabled the application timebase
 * @note Unsigned subtraction remains correct across one 32-bit tick-counter wrap
 * @warning This function blocks the calling thread while interrupt handlers continue to execute
 */
driver_status_t App_DelayMs(const uint32_t delayMs);

// ==================================================================================================== //
// Microsecond Timer Delay
// ==================================================================================================== //

#if (APP_ENABLE_TIMER_US_DELAY == 1U)
/**
 * @brief Initializes the optional dedicated Timer microsecond-delay service
 * @details
 * Enables @ref `APP_DELAY_TIMER_CLOCK_MASK`, then delegates the fixed 1 MHz
 * blocking-delay configuration of @ref `APP_DELAY_TIMER` to
 * @ref TIM_ConfigForBlockingDelay. Timer IRQ-source and NVIC state are not
 * read or modified.
 * @returns @ref driver_status_t "Application Timer-delay initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The Timer clock and 1 MHz blocking-delay configuration were applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @ref `APP_DELAY_TIMER` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The configured Timer or clock mask was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The Timer clock gate or kernel-clock contract was not satisfied
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: The configured Timer was running
 * @note This API is declared only when @ref `APP_ENABLE_TIMER_US_DELAY` is `1U`
 */
driver_status_t App_DelayTimerInit(void);

/**
 * @brief Provides a blocking microsecond delay using the optional dedicated Timer
 * @details
 * Splits @p delayUs into transactions no larger than `0xFFFFU` and delegates
 * each transaction to @ref TIM_BlockingDelayUs. Configuration is retained
 * between transactions; this function does not reconfigure the Timer.
 * @param[in] delayUs Requested delay in microseconds
 * Accepted values:
 * - `1U..0xFFFFFFFFU`: Delay composed from bounded 16-bit Timer transactions
 * @returns @ref driver_status_t "Application microsecond-delay status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every requested Timer interval completed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @ref `APP_DELAY_TIMER` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `delayUs` was zero or the Timer state was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The dedicated Timer clock was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A Timer interval did not complete within its polling budget
 * @pre @ref App_DelayTimerInit completed successfully and the application
 * retained exclusive ownership of @ref `APP_DELAY_TIMER`
 * @note Each hardware transaction is limited to `65535 us`; larger requests use multiple transactions
 * @note The requested duration is a minimum delay because setup and polling add positive overhead
 * @warning This polling API blocks the processor and does not use Timer IRQ or NVIC delivery
 */
driver_status_t App_DelayUs(const uint32_t delayUs);
#endif /* APP_ENABLE_TIMER_US_DELAY */

/** @} */

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* APP_DELAY_H_ */
