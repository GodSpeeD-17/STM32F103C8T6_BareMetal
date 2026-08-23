/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the USART byte-RX demo entry point
 * @version	v1.0
 * @date	23-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 1 USART Driver through `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the application entry point only. USART configuration
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

// ==================================================================================================== //
// Entry Point
// ==================================================================================================== //

/**
 * @brief Executes the USART byte-RX demo control loop
 * @details
 * Configures USART1 and repeatedly blocks on `USART_ReceiveByte()` to pick up
 * a one-byte mode command driving an external LED on PA3: '0' off, '1'
 * always on, '2' toggles every 1000ms, '3' toggles every 500ms. The toggle
 * modes run off the non-blocking application timebase instead of a blocking
 * delay, so timing keeps advancing between received bytes.
 * @returns Does not return
 */
int main(void);

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
