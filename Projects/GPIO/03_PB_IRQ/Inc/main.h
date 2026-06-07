/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	GPIO 03_PB_IRQ Project Configuration
 * @version	v1.0
 * @date	07-06-2026
 *
 * @details
 * This header owns project-local timing constants and GPIO mappings for the
 * GPIO push-button interrupt demo. Generic GPIO, GPIO IRQ, and BSP behavior
 * remains owned by the driver layer.
 */

#ifndef MAIN_H_
#define MAIN_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "bsp.h"
#include "gpio.h"
#include "gpio_irq.h"
#include "systick.h"

// ==================================================================================================== //
//												Macros													//
// ==================================================================================================== //

/**
 * @brief GPIO 03_PB_IRQ project-local timing and GPIO configuration
 * @details
 * The push button is connected to an externally pulled-up input, so the GPIO IRQ
 * input configuration uses @ref `GPIO_PIN_CONFIG_INPUT_FLOATING` and the EXTI
 * trigger uses @ref `GPIO_IRQ_TRIGGER_FALLING`.
 * @{
 */
/** @brief Main-loop heartbeat delay in milliseconds @def LOOP_DELAY_MS */
#define LOOP_DELAY_MS							((uint32_t) 1000UL)
/** @brief Push-button debounce guard time in milliseconds @def BUTTON_DEBOUNCE_DELAY_MS */
#define BUTTON_DEBOUNCE_DELAY_MS				((uint32_t) 50UL)
/** @brief Red LED GPIO port instance @def RED_LED_PORT */
#define RED_LED_PORT							GPIOA
/** @brief Red LED GPIO pin mask @def RED_LED_PIN */
#define RED_LED_PIN								GPIO_PIN_2
/** @brief Yellow LED GPIO port instance @def YELLOW_LED_PORT */
#define YELLOW_LED_PORT							GPIOA
/** @brief Yellow LED GPIO pin mask @def YELLOW_LED_PIN */
#define YELLOW_LED_PIN							GPIO_PIN_3
/** @brief Push-button GPIO port instance @def PUSH_BUTTON_PORT */
#define PUSH_BUTTON_PORT						GPIOA
/** @brief Push-button GPIO pin mask @def PUSH_BUTTON_PIN */
#define PUSH_BUTTON_PIN							GPIO_PIN_1
/** @brief Push-button GPIO input configuration @def PUSH_BUTTON_INPUT_CONFIG */
#define PUSH_BUTTON_INPUT_CONFIG				GPIO_PIN_CONFIG_INPUT_FLOATING
/** @brief Push-button EXTI trigger selector @def PUSH_BUTTON_IRQ_TRIGGER */
#define PUSH_BUTTON_IRQ_TRIGGER					GPIO_IRQ_TRIGGER_FALLING
/** @} */

// ==================================================================================================== //
//											Function Prototypes											//
// ==================================================================================================== //

/**
 * @brief Blocking millisecond delay supplied by the project startup timing layer
 * @param[in] delayTime Delay duration in milliseconds
 */
void delay_ms(uint32_t delayTime);

/**
 * @brief EXTI line 1 interrupt handler for the project push button
 */
void EXTI1_IRQHandler(void);

#endif /* MAIN_H_ */
