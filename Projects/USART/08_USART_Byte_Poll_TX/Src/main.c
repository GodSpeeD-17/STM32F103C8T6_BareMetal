/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the USART byte-TX demo application behavior
 * @version	v2.0
 * @date	23-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 2 `app_time` and Layer 1 USART/GPIO/BSP Drivers
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * Configures USART1 TX on PA9 at 115200 baud and repeatedly transmits one
 * incrementing byte from 'A' to 'Z', each blocking on its own
 * `USART_TransmitByte()` call, sending a single '\n' byte right after 'Z' to
 * mark the end of each completed cycle before wrapping back to 'A'. The
 * By default the application owns RCC, GPIO, and USART configuration in that
 * order; the USART Driver never touches GPIO or its own clock gate. Debug mode
 * instead demonstrates the BSP initialization shortcut and reuses that
 * configured transport without a second application configuration pass.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * Application behavior belongs here. Processor startup, clock configuration,
 * and service initialization do not.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "app_config.h"
#include "app_time.h"
#include "bsp_gpio.h"
#include "gpio.h"
#include "rcc.h"
#include "usart.h"

// ==================================================================================================== //
// Private Defines
// ==================================================================================================== //

/** @brief USART instance used by the demo @def APP_USART */
#define APP_USART							(USART1)
/** @brief Application-owned USART peripheral clock gate @def APP_USART_CLOCK_MASK */
#define APP_USART_CLOCK_MASK				(RCC_APB2ENR_USART1EN)
/** @brief Application-owned GPIO clock gate @def APP_USART_GPIO_CLOCK_MASK */
#define APP_USART_GPIO_CLOCK_MASK			(RCC_APB2ENR_IOPAEN)
/** @brief GPIO port carrying reset-default USART1 TX @def APP_USART_GPIO_PORT */
#define APP_USART_GPIO_PORT					(GPIOA)
/** @brief PA9 carrying default-remap USART1 TX @def APP_USART_TX_PIN_MASK */
#define APP_USART_TX_PIN_MASK				((gpio_pin_t) GPIO_PIN_9)
/** @brief Demo baud rate preset @def APP_USART_BAUD_RATE */
#define APP_USART_BAUD_RATE					(USART_BAUD_RATE_115200)
/** @brief Main-loop TX pacing delay in milliseconds @def LOOP_DELAY_MS */
#define LOOP_DELAY_MS						((uint32_t) 500UL)

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

/**
 * @brief Enters the application error-indication loop
 * @details
 * App_Init() already configures and forces off the BSP on-board LED, so this
 * handler only needs to set it once.
 */
static void App_ErrorHandler(void)
{
	//! Indicate Error
	BSP_OB_LED_Set();
	//! Infinite Loop
	while (1)
	{
		//! Preserve the visible active-low error indication until reset.
	}
}

/**
 * @brief Configures application-owned PA9 routing for USART1 TX
 * @returns @ref driver_status_t "GPIO configuration status"
 */
#if (APP_ENABLE_DEBUG == 0U)
static driver_status_t App_ConfigGPIOForUSART(void)
{
	//! The untouched reset-default PA9 route needs GPIOA but no AFIO clock or remap transaction.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(RCC_APB2_BUS, APP_USART_GPIO_CLOCK_MASK, DRIVER_STATUS_ON));
	//! 50 MHz drive strength keeps TX edge rate comfortable across every supported baud preset.
	return GPIO_SetPinModeConfig
	(
		APP_USART_GPIO_PORT,
		APP_USART_TX_PIN_MASK,
		GPIO_PIN_MODE_OUTPUT_50MHZ,
		GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL
	);
}

/**
 * @brief Configures USART1 for TX-only 115200 8N1 operation
 * @returns @ref driver_status_t "USART initialization status"
 */
static driver_status_t App_ConfigUSART(void)
{
	const usart_config_t usartConfig =
	{
		.frameFormat =
		{
			.parity = USART_PARITY_NONE,
			.stopBits = USART_STOP_BIT_1,
			.dataBits = USART_DATA_BITS_8
		},
		.hardware = USART_HARDWARE_ENABLE_TX,
		.baudRate = APP_USART_BAUD_RATE
	};

	//! The application owns the USART peripheral clock gate; the driver only verifies it.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(RCC_APB2_BUS, APP_USART_CLOCK_MASK, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(USART_Config(APP_USART, &usartConfig));

	//! Enabling UE is the final independent USART operation.
	return USART_SetOperationState(APP_USART, DRIVER_STATUS_ON);
}
#endif /* APP_ENABLE_DEBUG */

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	//! Data to be sent
	uint8_t counter = 'A';

#if (APP_ENABLE_DEBUG == 0U)
	//! The default educational path explicitly configures routing and USART state through shared Drivers.
	if (App_ConfigGPIOForUSART() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}
	if (App_ConfigUSART() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}
#endif /* APP_ENABLE_DEBUG */

	//! Infinite Loop
	while (1)
	{
		//! USART_TransmitByte() blocks on TXE internally, so no separate readiness poll is needed here.
		if (USART_TransmitByte(APP_USART, counter) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}

		//! Send '\n' after 'Z' to mark the end of each completed A-to-Z cycle, then wrap back to 'A'.
		if (counter == 'Z')
		{
			//! One '\n' byte (0x0A) separates each completed A-to-Z cycle, sent right after 'Z'.
			if (USART_TransmitByte(APP_USART, (uint8_t) '\n') != DRIVER_STATUS_SUCCESS)
			{
				App_ErrorHandler();
			}
			counter = 'A';
		}
		else
		{
			counter++;
		}

		//! Small Delay
		(void) App_DelayMs(LOOP_DELAY_MS);
	}
}
