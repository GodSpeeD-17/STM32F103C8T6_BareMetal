/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the USART interrupt-driven character-array TX demo
 * @version	v1.0
 * @date	28-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 1 Driver and USART LL APIs privately through `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the application entry point and processor-mandated
 * USART1 interrupt-handler ABI. `main.c` owns the fixed character array and
 * its TXE-to-TC transmit state machine.
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
 * @brief Executes the USART interrupt-driven character-array TX demo
 * @details
 * Configures USART1 TX when required, enables TXEIE to request the first
 * character from Handler mode, and sleeps while USART1_IRQHandler() completes
 * the TXE-to-TC lifecycle.
 * @returns Does not return
 */
int main(void);

// ==================================================================================================== //
// Interrupt Handler
// ==================================================================================================== //

/**
 * @brief Services the USART1 TXE/TC character-array transmission
 * @details
 * Writes one array element through LL on each TXE event, enables TCIE only
 * after the final DR write, and publishes completion after the final stop bit
 * leaves the wire.
 */
void USART1_IRQHandler(void);

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */

