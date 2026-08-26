/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the GPIO push-button poll demo application behavior
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 2 `app_time` and Layer 1 GPIO/BSP Drivers
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * The application polls an externally pulled-up push button and toggles the
 * red/yellow LEDs while it is pressed.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * Application behavior belongs here. Processor startup, clock configuration,
 * and service initialization do not.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "app_time.h"
#include "bsp_gpio.h"
#include "gpio.h"
#include "rcc.h"

// ==================================================================================================== //
// Private Defines
// ==================================================================================================== //

/** @brief Main-loop poll delay in milliseconds @def LOOP_DELAY_MS */
#define LOOP_DELAY_MS					(10UL)
/** @brief Red LED GPIO port instance @def RED_LED_PORT */
#define RED_LED_PORT					GPIOA
/** @brief Red LED GPIO pin mask @def RED_LED_PIN */
#define RED_LED_PIN						GPIO_PIN_2
/** @brief Yellow LED GPIO port instance @def YELLOW_LED_PORT */
#define YELLOW_LED_PORT					GPIOA
/** @brief Yellow LED GPIO pin mask @def YELLOW_LED_PIN */
#define YELLOW_LED_PIN					GPIO_PIN_3
/** @brief Push-button GPIO port instance @def PUSH_BUTTON_PORT */
#define PUSH_BUTTON_PORT				GPIOA
/** @brief Push-button GPIO pin mask (externally pulled-up) @def PUSH_BUTTON_PIN */
#define PUSH_BUTTON_PIN					GPIO_PIN_1
/** @brief Application-owned GPIO port clock gate shared by every pin above @def APP_GPIO_CLOCK_MASK */
#define APP_GPIO_CLOCK_MASK				(RCC_APB2ENR_IOPAEN)

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	if
	(
		RCC_SetPeripheralClockState
		(
			RCC_APB2_BUS,
			APP_GPIO_CLOCK_MASK,
			DRIVER_STATUS_ON
		) != DRIVER_STATUS_SUCCESS
	)
	{
		BSP_OB_LED_Set();
		while (1);
	}

	if (GPIO_LED_Init(RED_LED_PORT, (RED_LED_PIN | YELLOW_LED_PIN)) != DRIVER_STATUS_SUCCESS)
	{
		BSP_OB_LED_Set();
		while (1);
	}

	if (GPIO_Init(PUSH_BUTTON_PORT, PUSH_BUTTON_PIN, GPIO_PIN_MODE_INPUT, GPIO_PIN_CONFIG_INPUT_FLOATING) != DRIVER_STATUS_SUCCESS)
	{
		BSP_OB_LED_Set();
		while (1);
	}

	while (1)
	{
		//! Externally pulled-up button reads DRIVER_STATUS_OFF while pressed.
		if (GPIO_PinGet(PUSH_BUTTON_PORT, PUSH_BUTTON_PIN) == DRIVER_STATUS_OFF)
		{
			GPIO_PinToggle(RED_LED_PORT, RED_LED_PIN);
			GPIO_PinToggle(YELLOW_LED_PORT, YELLOW_LED_PIN);
		}

		(void) App_DelayMs(LOOP_DELAY_MS);
	}
}
