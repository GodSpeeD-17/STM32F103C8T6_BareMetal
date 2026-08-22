/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the GPIO push-button IRQ demo entry point
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 2 `app_time`/`app_delay` and Layer 1 GPIO/BSP/NVIC Drivers
 *   through `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the application entry point only. Timing constants,
 * GPIO mappings, and the EXTI1 handler live in `main.c` as they are private
 * to this demo.
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
 * @brief Executes the GPIO push-button IRQ demo control loop
 * @details
 * Configures an externally pulled-up push button as a falling-edge EXTI
 * source, then toggles the on-board LED as a heartbeat while the push-button
 * IRQ toggles the red LED after a debounce guard period.
 * @returns Does not return
 */
int main(void);

/**
 * @brief Handles EXTI line 1 interrupts from the project push button
 * @details Defined in `main.c`; declared here only to satisfy
 * `-Wmissing-prototypes` for this externally linked interrupt handler.
 */
void EXTI1_IRQHandler(void);

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
