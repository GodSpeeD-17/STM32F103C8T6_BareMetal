/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the USART byte-RX demo application behavior
 * @version	v1.0
 * @date	23-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 1 USART/GPIO/BSP Drivers
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * Configures USART1 RX on PA10 at 115200 baud and repeatedly blocks on
 * `USART_ReceiveByte()` to pick up a one-byte mode command that drives an
 * external LED on PA3: '0' off, '1' always on, '2' toggles every 1000ms, '3'
 * toggles every 500ms. The toggle modes are timed against the non-blocking
 * `App_TimeGetElapsedMs()` application timebase rather than a blocking delay,
 * so the LED keeps toggling on schedule between received bytes. A receive
 * timeout (no byte within the bounded poll window) is expected while the
 * sender is idle and is not an error. The application owns RCC and GPIO
 * configuration in that order; the USART driver never touches GPIO or its
 * own clock gate.
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
#include "bsp.h"
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
/** @brief GPIO port carrying default-remap USART1 RX @def APP_USART_GPIO_PORT */
#define APP_USART_GPIO_PORT					(GPIOA)
/** @brief PA10 carrying default-remap USART1 RX @def APP_USART_RX_PIN_MASK */
#define APP_USART_RX_PIN_MASK				((gpio_pin_t) GPIO_PIN_10)
/** @brief Demo baud rate preset @def APP_USART_BAUD_RATE */
#define APP_USART_BAUD_RATE					(USART_BAUD_RATE_115200)
/** @brief External LED pin driven by the received mode command @def APP_LED_PIN_MASK */
#define APP_LED_PIN_MASK					((gpio_pin_t) GPIO_PIN_3)
/** @brief Mode command: LED off @def APP_LED_MODE_OFF */
#define APP_LED_MODE_OFF					((uint8_t) '0')
/** @brief Mode command: LED always on @def APP_LED_MODE_ON */
#define APP_LED_MODE_ON						((uint8_t) '1')
/** @brief Mode command: LED toggles every 1000ms @def APP_LED_MODE_TOGGLE_1000MS */
#define APP_LED_MODE_TOGGLE_1000MS			((uint8_t) '2')
/** @brief Mode command: LED toggles every 500ms @def APP_LED_MODE_TOGGLE_500MS */
#define APP_LED_MODE_TOGGLE_500MS			((uint8_t) '3')
/** @brief Toggle period in milliseconds for @ref APP_LED_MODE_TOGGLE_1000MS @def APP_LED_TOGGLE_PERIOD_1000MS */
#define APP_LED_TOGGLE_PERIOD_1000MS		((uint32_t) 1000UL)
/** @brief Toggle period in milliseconds for @ref APP_LED_MODE_TOGGLE_500MS @def APP_LED_TOGGLE_PERIOD_500MS */
#define APP_LED_TOGGLE_PERIOD_500MS			((uint32_t) 500UL)

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
 * @brief Configures application-owned PA10 routing for USART1 RX
 * @returns @ref driver_status_t "GPIO configuration status"
 */
static driver_status_t App_ConfigGPIOForUSART(void)
{
	//! The application explicitly owns the GPIO-port clock gate.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(RCC_APB2_BUS, APP_USART_GPIO_CLOCK_MASK, DRIVER_STATUS_ON));
	//! RM0008 requires the USART RX pin to be configured as a floating input.
	return GPIO_SetPinModeConfig
	(
		APP_USART_GPIO_PORT,
		APP_USART_RX_PIN_MASK,
		GPIO_PIN_MODE_INPUT,
		GPIO_PIN_CONFIG_INPUT_FLOATING
	);
}

/**
 * @brief Configures application-owned PA3 as the received-byte LED output
 * @returns @ref driver_status_t "GPIO configuration status"
 */
static driver_status_t App_ConfigLEDGPIO(void)
{
	//! Shares APP_USART_GPIO_PORT's clock gate; the RCC codec makes a repeat enable a no-op.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(RCC_APB2_BUS, APP_USART_GPIO_CLOCK_MASK, DRIVER_STATUS_ON));
	return GPIO_LED_Init(APP_USART_GPIO_PORT, APP_LED_PIN_MASK);
}

/**
 * @brief Configures USART1 for RX-only 115200 8N1 operation
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
		.hardware = USART_HARDWARE_ENABLE_RX,
		.baudRate = APP_USART_BAUD_RATE
	};

	//! The application owns the USART peripheral clock gate; the driver only verifies it.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(RCC_APB2_BUS, APP_USART_CLOCK_MASK, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(USART_Config(APP_USART, &usartConfig));

	//! Enabling UE is the final independent USART operation.
	return USART_SetOperationState(APP_USART, DRIVER_STATUS_ON);
}

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	//! Data received into
	uint8_t rxByte = 0x00U;
	//! Status of the last receive attempt
	driver_status_t status = DRIVER_STATUS_SUCCESS;
	//! Toggle period for the active mode; 0 means OFF/ON hold with no toggling
	uint32_t togglePeriodMs = 0x00UL;
	//! Tick at which the toggle modes last flipped the LED
	uint32_t lastToggleTickMs = 0x00UL;

	//! Physical pin routing is intentionally outside the USART driver.
	if (App_ConfigGPIOForUSART() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}
	if (App_ConfigLEDGPIO() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}
	if (App_ConfigUSART() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}

	//! Infinite Loop
	while (1)
	{
		//! USART_ReceiveByte() blocks on RXNE internally within a bounded poll window.
		status = USART_ReceiveByte(APP_USART, &rxByte);

		//! Data Received?
		if (status == DRIVER_STATUS_SUCCESS)
		{
			//! Each case re-origins the toggle window so a mode switch always starts a fresh period;
			//! any byte outside these four exact mode commands falls to default and is ignored.
			switch (rxByte)
			{
				//! Turn LED OFF
				case APP_LED_MODE_OFF:
				{
					togglePeriodMs = 0x00UL;
					if (GPIO_PinReset(APP_USART_GPIO_PORT, APP_LED_PIN_MASK) != DRIVER_STATUS_SUCCESS)
					{
						App_ErrorHandler();
					}
					lastToggleTickMs = App_TimeGetTickMs();
					break;
				}

				//! Turn LED ON
				case APP_LED_MODE_ON:
				{
					togglePeriodMs = 0x00UL;
					if (GPIO_PinSet(APP_USART_GPIO_PORT, APP_LED_PIN_MASK) != DRIVER_STATUS_SUCCESS)
					{
						App_ErrorHandler();
					}
					lastToggleTickMs = App_TimeGetTickMs();
					break;
				}

				//! Toggle LED every 1000ms
				case APP_LED_MODE_TOGGLE_1000MS:
				{
					togglePeriodMs = APP_LED_TOGGLE_PERIOD_1000MS;
					break;
				}

				//! Toggle LED every 500ms
				case APP_LED_MODE_TOGGLE_500MS:
				{
					togglePeriodMs = APP_LED_TOGGLE_PERIOD_500MS;
					break;
				}

				//! Unknown Command - Skip
				default:
				{
					break;
				}
			}
		}
		//! Generic error except for timeout?
		else if (status != DRIVER_STATUS_ERROR_TIMEOUT)
		{
			//! A timeout just means the sender was idle; anything else is a real fault.
			App_ErrorHandler();
		}

		//! Need to Toggle?
		if (togglePeriodMs != 0x00UL)
		{
			//! Time elapsed? 
			if (App_TimeGetElapsedMs(lastToggleTickMs) >= togglePeriodMs)
			{
				//! Toggle the GPIO
				if (GPIO_PinToggle(APP_USART_GPIO_PORT, APP_LED_PIN_MASK) != DRIVER_STATUS_SUCCESS)
				{
					App_ErrorHandler();
				}
				//! Update the last toggle timestamp
				lastToggleTickMs = App_TimeGetTickMs();
			}
		}
	}
}
