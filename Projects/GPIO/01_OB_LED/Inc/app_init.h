/**
 * @file	app_init.h
 * @author	Shrey Shah
 * @brief	Declares application-owned hardware-service initialization
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section APP_INIT_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application orchestration
 * - Used by: Layer 4 `app_startup`
 * - Uses: Layer 2 application services and Layer 1 RCC Driver
 *
 * @section APP_INIT_H_RESPONSIBILITY Responsibility
 * This interface exposes the single ordered initialization transaction used
 * before `main`. The implementation configures the clock first and then every
 * application service enabled by `app_config.h`, including the optional
 * on-board LED GPIO.
 *
 * @section APP_INIT_H_BOUNDARY Dependency Boundary
 * This header includes shared status types only. RCC, SysTick, Timer, BSP,
 * and application-service headers remain private to `app_init.c` and do not
 * leak upward into startup.
 */

// Header Guard
#ifndef APP_INIT_H_
#define APP_INIT_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "stm32f1xx_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Application hardware-service initialization
 * @defgroup APP_Init Application Initialization
 * @ingroup APP_Template
 * @{
 */

// ==================================================================================================== //
// Public API
// ==================================================================================================== //

/**
 * @brief Initializes the hardware services selected by application policy
 * @details
 * Applies the 72 MHz RCC preset first, initializes the SysTick-backed timebase
 * when enabled, initializes the optional dedicated microsecond-delay Timer,
 * then configures the optional on-board LED GPIO and forces it off. Processing
 * stops at the first failed transaction.
 * @returns @ref driver_status_t "Application initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every enabled application service was initialized
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An enabled service resolved to a `NULL` peripheral instance
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: An enabled service configuration was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: An enabled service hardware precondition was not satisfied
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: The optional dedicated Timer was running
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: RCC initialization timed out
 * @retval - @ref `DRIVER_STATUS_ERROR`: RCC hardware state could not be decoded
 * @note Timer hardware is untouched when @ref `APP_ENABLE_TIMER_US_DELAY` is `0U`
 * @note The on-board LED GPIO is untouched when @ref `APP_ENABLE_ONBOARD_LED` is `0U`
 */
driver_status_t App_Init(void);

/** @} */

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* APP_INIT_H_ */
