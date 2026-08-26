/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the USART printf demo entry point
 * @version	v2.0
 * @date	23-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 2 `app_time` and Layer 1 USART/GPIO Drivers through `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the application entry point only. The default path's
 * explicit USART configuration and timing constants live in `main.c`; Debug
 * policy may instead supply the same hardware through BSP before entry.
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
 * @brief Executes the USART printf demo control loop
 * @details
 * Configures USART1 TX on PA9 at 115200 baud and repeatedly prints an
 * incrementing counter via USART_printf(), paced by App_DelayMs().
 * @returns Does not return
 */
int main(void);

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
