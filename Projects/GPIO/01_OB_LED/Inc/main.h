/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the GPIO on-board LED demo entry point
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 2 `app_time` and Layer 1 BSP/GPIO Drivers through `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the application entry point only. LED pattern policy
 * and timing constants live in `main.c` as they are private to this demo.
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

/**
 * @brief GPIO on-board LED demo application
 * @defgroup App_Main Application Control Loop
 * @{
 */

// ==================================================================================================== //
// Entry Point
// ==================================================================================================== //

/**
 * @brief Executes the GPIO on-board LED demo control loop
 * @details
 * Initializes the red, yellow, and on-board LEDs, runs a lamp-test sequence,
 * then continuously drives a three-bit LED counter, repeating the lamp test
 * on every counter wrap.
 * @returns Does not return
 * @note This implementation does not return
 */
int main(void);

/** @} */

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
