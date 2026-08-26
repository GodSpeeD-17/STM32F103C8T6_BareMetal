/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the Timer polling-delay demo entry point
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 1 Timer/BSP Drivers directly through `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the application entry point only. This demo
 * deliberately owns TIM2 directly instead of through `app_time`, so the
 * Timer driver's blocking-delay API stays visible end to end.
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
 * @brief Executes the TIM2 blocking polling-delay demonstration
 * @details
 * Configures TIM2 as a dedicated 1 MHz blocking polling-delay source, then
 * toggles the on-board LED once per blocking delay interval.
 * @returns Does not return
 */
int main(void);

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
