/**
 * @file	bsp.h
 * @author	Shrey Shah
 * @brief	Board Support Package Public Interface
 * @version	v1.0
 * @date	31-05-2026
 *
 * @details
 * The BSP layer owns board-level policy. Generic peripheral drivers such as
 * GPIO expose reusable port/pin APIs, while this layer binds those APIs to one
 * physical board. For the STM32F103C8T6 Blue Pill, the board policy currently
 * captured here is the active-low on-board LED connected to PC13.
 *
 * Keeping this mapping in BSP prevents the generic GPIO driver from knowing
 * which package pin has an LED attached, whether that LED is active-low, or
 * which board-specific convenience functions should exist.
 */

// Header Guards
#ifndef BSP_H_
#define BSP_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "gpio.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Board support package APIs and board-level constants
 * @defgroup BSP_01_BoardSupport BSP Board Support
 * @details
 * This group contains symbols that are valid for a concrete target board rather
 * than for the STM32F1 GPIO peripheral in general. Code that needs direct GPIO
 * control should include @ref `gpio.h`; code that needs Blue Pill board
 * conveniences should include @ref `bsp.h`.
 * @{
 */

// ==================================================================================================== //
//										STM32F103C8T6 Board Defaults									//
// ==================================================================================================== //

#ifdef STM32F103C8T6__

/**
 * @brief GPIO peripheral instance connected to the Blue Pill on-board LED
 * @def GPIO_OB_LED_PORT
 * @details
 * The STM32F103C8T6 Blue Pill routes the on-board LED to GPIO port C. This is
 * board routing information, not a GPIO peripheral fact.
 */
#define GPIO_OB_LED_PORT						GPIOC
/**
 * @brief GPIO pin connected to the Blue Pill on-board LED
 * @def GPIO_OB_LED_PIN
 * @details
 * The on-board LED is connected to PC13 and is wired active-low. A reset output
 * latch turns the LED on, while a set output latch turns it off.
 */
#define GPIO_OB_LED_PIN							GPIO_PIN_13

// Uncomment this to achieve delay from SysTick
// #define SYSTICK_DELAY__

// Use Timer for Delay
#ifndef SYSTICK_DELAY__
/** @brief Dedicated Timer instance used by the startup blocking-delay service @def DELAY_TIMER */
#define DELAY_TIMER								(TIM4)
/** @brief APB1 clock-enable mask owned by the startup blocking-delay service @def DELAY_TIMER_CLOCK_ENABLE_MASK */
#define DELAY_TIMER_CLOCK_ENABLE_MASK			(RCC_APB1ENR_TIM4EN)
#endif /* SYSTICK_DELAY__ */

// ==================================================================================================== //
//										On-Board LED APIs												//
// ==================================================================================================== //

/**
 * @brief Initializes the board on-board LED GPIO
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: On-board LED GPIO was initialized.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Board LED GPIO mapping was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal GPIO staged-image update failed.
 * @details
 * This API configures @ref `GPIO_OB_LED_PORT` / @ref `GPIO_OB_LED_PIN` through
 * @ref `GPIO_LED_Init`, which applies @ref `GPIO_PIN_MODE_OUTPUT_2MHZ` and
 * @ref `GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL`. The active-low polarity is handled
 * by the set/reset helper APIs below.
 */
driver_status_t OB_LED_Init(void);

/**
 * @brief Sets the active-low board on-board LED
 * @details
 * The Blue Pill LED turns on when PC13 is driven low, so this API resets the
 * GPIO output latch through @ref `GPIO_PinReset`.
 */
void OB_LED_Set(void);

/**
 * @brief Resets the active-low board on-board LED
 * @details
 * The Blue Pill LED turns off when PC13 is driven high, so this API sets the
 * GPIO output latch through @ref `GPIO_PinSet`.
 */
void OB_LED_Reset(void);

/**
 * @brief Toggles the active-low board on-board LED
 * @details
 * This API forwards to @ref `GPIO_PinToggle` for the board LED pin. The logical
 * LED state changes because the underlying PC13 output latch is inverted.
 */
void OB_LED_Toggle(void);

/**
 * @brief Deinitializes the board on-board LED GPIO
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: On-board LED GPIO was restored.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Board LED GPIO mapping was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal GPIO staged-image update failed.
 * @details
 * This API forwards to @ref `GPIO_Deinit` for @ref `GPIO_OB_LED_PORT` /
 * @ref `GPIO_OB_LED_PIN`, restoring the pin to the GPIO reset-style floating
 * input configuration used by the driver.
 */
driver_status_t OB_LED_Deinit(void);

#endif /* STM32F103C8T6__ */

/** @} */ // BSP_01_BoardSupport

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BSP_H_ */
