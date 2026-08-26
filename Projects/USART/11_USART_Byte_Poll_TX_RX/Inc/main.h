/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the USART byte TX/RX polling demo entry point
 * @version	v1.0
 * @date	26-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 1 BSP board USART and optional on-board LED APIs through
 *   `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the application entry point only. Application policy
 * and one-time board-USART initialization live in `app_config.h` and
 * `app_init.c`; `main.c` owns only the resulting polling behavior.
 *
 * @section MAIN_H_BOUNDARY Dependency Boundary
 * This header is standalone so startup does not acquire application-service or
 * hardware dependencies through `main.h`.
 */

// Header Guard
#ifndef MAIN_H_
#define MAIN_H_

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
// Entry Point
// ==================================================================================================== //

/**
 * @brief Executes the USART byte TX/RX polling demo control loop
 * @details
 * When @ref `APP_ENABLE_USART` is `1U`, App_BootInit() configures BSP's
 * USART1 transport with both TX and RX enabled, then this loop repeatedly
 * receives one byte and immediately transmits the same byte back to the
 * connected terminal. Both operations use BSP forwarding APIs and the USART
 * Driver's bounded polling behavior; no interrupt handler or DMA channel
 * participates. When the capability is `0U`, this entry remains an idle loop
 * and compiles no BSP_USART_* reference.
 * @returns Does not return
 */
int main(void);

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
