/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the USART byte TX/RX polling demo entry point
 * @version	v1.0
 * @date	26-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 1 RCC/GPIO/USART Drivers and optional BSP on-board LED APIs
 *   through `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the application entry point only. Application policy
 * lives in `app_config.h`; `main.c` explicitly configures the application
 * USART through RCC, GPIO, and USART Drivers when boot-time debug has not
 * already initialized the same hardware, then owns the polling behavior.
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
 * @brief Executes the USART byte TX/RX polling demo control loop
 * @details
 * Ensures USART1 on PA9/PA10 is configured for 115200-baud 8N1 operation with
 * both TX and RX enabled, performing the complete application-owned RCC/GPIO/
 * USART Driver transaction when boot-time debug did not already configure the
 * same hardware. It then repeatedly receives one byte and immediately
 * transmits that byte through the USART Driver's bounded polling operations;
 * no interrupt handler or DMA channel participates.
 * @returns Does not return
 */
int main(void);

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
