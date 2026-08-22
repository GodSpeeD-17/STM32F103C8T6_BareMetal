/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the Timer update-IRQ demo entry point
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 2 `app_delay` and Layer 1 Timer/GPIO/BSP/NVIC Drivers
 *   through `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the application entry point and the externally
 * linked TIM3 update-IRQ handler. Timing constants and Timer mappings live
 * in `main.c` as they are private to this demo.
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
 * @brief Executes the TIM3 update-interrupt demonstration
 * @details
 * Configures TIM3 with a one-second update interrupt that toggles a GPIO
 * LED; the main loop only paces itself with App_DelayMs() between checks.
 * @returns Does not return
 */
int main(void);

/**
 * @brief Handles TIM3 update interrupts
 * @details Defined in `main.c`; declared here only to satisfy
 * `-Wmissing-prototypes` for this externally linked interrupt handler.
 */
void TIM3_IRQHandler(void);

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
