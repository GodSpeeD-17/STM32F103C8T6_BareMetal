/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the USART byte-TX demo entry point
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 2 `app_time` and Layer 1 USART Driver through `main.c`
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
 * @brief Executes the USART byte-TX demo control loop
 * @details
 * Configures USART1 and repeatedly transmits one incrementing byte from 'A'
 * to 'Z', paced by App_DelayMs(), sending a single '\n' byte right after
 * 'Z' to mark each completed cycle.
 * @returns Does not return
 */
int main(void);

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
