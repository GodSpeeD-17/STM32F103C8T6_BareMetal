/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the GPIO push-button poll demo entry point
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 2 `app_time` and Layer 1 GPIO/BSP Drivers through `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the application entry point only. Timing constants and
 * GPIO mappings live in `main.c` as they are private to this demo.
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
 * @brief Executes the GPIO push-button poll demo control loop
 * @details
 * Initializes the red/yellow LEDs and an externally pulled-up push button,
 * then polls the button and toggles both LEDs while it is pressed.
 * @returns Does not return
 */
int main(void);

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
