/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the DMA memory-to-memory poll demo entry point
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 2 `app_delay` and Layer 1 DMA/BSP Drivers through `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the application entry point only. DMA transfer
 * configuration and timing constants live in `main.c` as they are private
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
 * @brief Executes the DMA memory-to-memory poll demo control loop
 * @details
 * Performs one polled DMA memory-to-memory transfer, then toggles the
 * on-board LED forever, paced by App_DelayMs().
 * @returns Does not return
 */
int main(void);

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
