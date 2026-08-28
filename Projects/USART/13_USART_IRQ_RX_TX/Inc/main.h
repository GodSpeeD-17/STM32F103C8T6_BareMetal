/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the USART IRQ echo application entry points
 * @version	v1.0
 * @date	28-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 2 application services through `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the sleeping application entry point and the strong
 * USART1 handler that replaces the startup module's weak default handler.
 *
 * @section MAIN_H_BOUNDARY Dependency Boundary
 * This header remains standalone. USART Driver and LL dependencies stay in
 * `main.c`, so startup acquires no peripheral dependencies through `main.h`.
 */

// Header Guard
#ifndef MAIN_H_
#define MAIN_H_

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief USART interrupt-driven line echo application
 * @defgroup App_Main Application Control Loop
 * @ingroup App_Template
 * @{
 */

// ==================================================================================================== //
// Entry Point
// ==================================================================================================== //

/**
 * @brief Executes the application control loop
 * @details
 * Arms USART1 RXNE interrupt delivery, then sleeps while Handler mode receives
 * bounded lines and echoes them through TXE/TC interrupts.
 * @returns Application-defined exit status if the infinite loop is replaced
 * @note This implementation does not return
 */
int main(void);

// ==================================================================================================== //
// Interrupt Handlers
// ==================================================================================================== //

/**
 * @brief Advances the RXNE -> TXE -> TC application state machine
 * @details RXNE captures one character, TXE writes one buffered character,
 * and TC re-arms reception only after the final frame has left the wire.
 */
void USART1_IRQHandler(void);

/** @} */

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
