/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Declares the Timer PWM update-IRQ demo entry point
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_H_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior
 * - Invoked by: Layer 4 `app_startup` after initialization succeeds
 * - Uses: Layer 1 Timer/GPIO/BSP/NVIC Drivers through `main.c`
 *
 * @section MAIN_H_RESPONSIBILITY Responsibility
 * This header declares the application entry point and the externally linked
 * TIM2 update-IRQ handler. PWM channel configuration and timing constants
 * live in `main.c` as they are private to this demo.
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
 * @brief Runs the PA3 Timer PWM duty ramp driven by the TIM2 update IRQ
 * @details
 * Demonstrates pairing a Timer PWM channel with its own update-event
 * interrupt: the TIM2_IRQHandler() only signals that a period elapsed, and
 * this control loop owns every ramp decision and the sole TIM_SetPWMDuty()
 * call. The application owns RCC, GPIO/AFIO, Timer base configuration, PWM
 * channel configuration, channel output-enable state, IRQ-source selection,
 * NVIC delivery, and final counter start order.
 * @returns Does not return
 */
int main(void);

/**
 * @brief Handles TIM2 update interrupts
 * @details Defined in `main.c`; declared here only to satisfy
 * `-Wmissing-prototypes` for this externally linked interrupt handler.
 */
void TIM2_IRQHandler(void);

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAIN_H_ */
