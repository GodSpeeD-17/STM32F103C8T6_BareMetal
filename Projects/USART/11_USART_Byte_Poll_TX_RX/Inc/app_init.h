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
 * - Uses: Layer 2 application services and Layer 1 RCC and BSP Drivers
 *
 * @section APP_INIT_H_RESPONSIBILITY Responsibility
 * This interface exposes the single ordered initialization transaction used
 * before `main`. The implementation configures the clock first and then every
 * application service enabled by `app_config.h`. It configures the optional
 * on-board LED GPIO, then enables application-owned board UART clock gates
 * and directs BSP to establish the fixed full-duplex transport before `main`
 * starts polling it.
 *
 * @section APP_INIT_H_BOUNDARY Dependency Boundary
 * This header includes shared status types only. RCC, SysTick, Timer, BSP,
 * and application-service headers remain private to
 * `app_init.c` and do not leak upward into startup.
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
 * @defgroup App_BootInit Application Boot Initialization
 * @ingroup App_Template
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
 * then configures the optional on-board LED GPIO and forces it off. It next
 * enables GPIOA and USART1 clock gates before BSP_USART_Init() configures the
 * fixed PA9/PA10 115200-baud 8N1 full-duplex board transport, then optionally
 * emits a diagnostic through BSP_USART_printf(). Processing stops at the first
 * failed transaction.
 * @returns @ref driver_status_t "Application initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every enabled application service was initialized
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: An enabled service configuration was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_FAIL`: An enabled debug diagnostic's
 * `BSP_USART_printf()` formatting failed
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: An enabled service hardware
 * precondition was not satisfied, including a board UART clock gate during debug output
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: The optional dedicated Timer was running
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: RCC initialization or an
 * enabled debug diagnostic's `BSP_USART_printf()` TX polling timed out
 * @retval - @ref `DRIVER_STATUS_ERROR`: RCC hardware state could not be decoded
 * @note Timer hardware is untouched when @ref `APP_ENABLE_TIMER_US_DELAY` is `0U`
 * @note The on-board LED GPIO is untouched when @ref `APP_ENABLE_ONBOARD_LED` is `0U`
 * @note Board UART setup is unconditional for this polling-echo project;
 * the application owns its clock-gate transaction while BSP owns the fixed
 * pin and USART configuration
 */
driver_status_t App_BootInit(void);

/** @} */

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* APP_INIT_H_ */
