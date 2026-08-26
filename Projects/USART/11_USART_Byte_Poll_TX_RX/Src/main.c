/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the USART byte TX/RX polling demo behavior
 * @version	v1.0
 * @date	26-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_BootInit() succeeds
 * - Uses: Layer 1 RCC/GPIO/USART Drivers and, when enabled, BSP on-board LED APIs
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * Boot-time debug directs BSP to configure USART1 PA9 TX / PA10 RX for
 * 115200-baud 8N1 operation with both transmitter and receiver enabled.
 * Otherwise this module explicitly performs the equivalent application-owned
 * RCC, GPIO, and USART Driver configuration.
 * The main loop then polls for one received byte and, on success, polls until
 * the transmit data register accepts that same byte.
 * This terminal-echo behavior demonstrates configured full-duplex hardware
 * while keeping control flow polling based: no USART interrupt source and no
 * DMA request is enabled. A receive timeout means the terminal is idle and is
 * retried; a transmit timeout is unrecoverable because this stateless demo
 * cannot safely defer the captured byte. The optional BSP on-board LED
 * indicates an unrecoverable fault.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * This module owns application USART configuration when boot-time debug is
 * disabled, steady-state USART Driver polling, and optional board fault
 * indication. BSP owns only selected board-capability transactions, while
 * shared Drivers own register access. This module does not reconfigure a
 * transport already initialized for boot-time debug.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "app_config.h"
#include "cmsis_gcc.h"
#include "gpio.h"
#include "rcc.h"
#include "usart.h"

#if (APP_ENABLE_ONBOARD_LED == 1U)
#include "bsp_gpio.h"
#endif /* APP_ENABLE_ONBOARD_LED */


// ==================================================================================================== //
// Private Configuration
// ==================================================================================================== //

/** @brief Application-owned full-duplex USART instance @def APP_USART_INSTANCE */
#define APP_USART_INSTANCE				(USART1)
/** @brief RCC bus containing the application USART clock gate @def APP_USART_CLOCK_BUS */
#define APP_USART_CLOCK_BUS				(RCC_APB2_BUS)
/** @brief Application USART peripheral clock gate @def APP_USART_CLOCK_MASK */
#define APP_USART_CLOCK_MASK			(RCC_APB2ENR_USART1EN)
/** @brief RCC bus containing the application USART GPIO clock gate @def APP_USART_GPIO_CLOCK_BUS */
#define APP_USART_GPIO_CLOCK_BUS		(RCC_APB2_BUS)
/** @brief GPIOA clock gate for the reset-default USART1 route @def APP_USART_GPIO_CLOCK_MASK */
#define APP_USART_GPIO_CLOCK_MASK		(RCC_APB2ENR_IOPAEN)
/** @brief GPIO port carrying the application USART route @def APP_USART_GPIO_PORT */
#define APP_USART_GPIO_PORT				(GPIOA)
/** @brief PA9 application USART transmitter pin @def APP_USART_TX_PIN_MASK */
#define APP_USART_TX_PIN_MASK			((gpio_pin_t) GPIO_PIN_9)
/** @brief PA10 application USART receiver pin @def APP_USART_RX_PIN_MASK */
#define APP_USART_RX_PIN_MASK			((gpio_pin_t) GPIO_PIN_10)
/** @brief Application USART baud-rate preset @def APP_USART_BAUD_RATE */
#define APP_USART_BAUD_RATE				(USART_BAUD_RATE_115200)

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

#if (APP_ENABLE_DEBUG == 0U)
/**
 * @brief Configures the application-owned USART1 GPIO route
 * @returns @ref driver_status_t "Application USART GPIO-configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: GPIOA, PA9, and PA10 were configured
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: An application RCC or GPIO mapping was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: GPIOA clock validation or GPIO staging failed
 */
__STATIC driver_status_t App_ConfigGPIOForUSART(void)
{
	//! The untouched reset-default PA9/PA10 route needs GPIOA but no AFIO clock or remap transaction.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(APP_USART_GPIO_CLOCK_BUS, APP_USART_GPIO_CLOCK_MASK, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS
	(
		GPIO_SetPinModeConfig
		(
			APP_USART_GPIO_PORT,
			APP_USART_TX_PIN_MASK,
			GPIO_PIN_MODE_OUTPUT_50MHZ,
			GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL
		)
	);

	//! PA10 remains an input because the connected USART peer drives received data.
	return GPIO_SetPinModeConfig
	(
		APP_USART_GPIO_PORT,
		APP_USART_RX_PIN_MASK,
		GPIO_PIN_MODE_INPUT,
		GPIO_PIN_CONFIG_INPUT_FLOATING
	);
}

/**
 * @brief Configures and enables the application-owned full-duplex USART
 * @returns @ref driver_status_t "Application USART-configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: USART1 was configured and enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The application USART configuration was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1's clock or bus frequency was unavailable
 */
__STATIC driver_status_t App_ConfigUSART(void)
{
	const usart_config_t usartConfig =
	{
		.frameFormat =
		{
			.parity = USART_PARITY_NONE,
			.stopBits = USART_STOP_BIT_1,
			.dataBits = USART_DATA_BITS_8
		},
		.hardware = USART_HARDWARE_ENABLE_TX_RX,
		.baudRate = APP_USART_BAUD_RATE
	};

	//! The application owns the USART1 clock gate; the USART Driver only validates it.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(APP_USART_CLOCK_BUS, APP_USART_CLOCK_MASK, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(USART_Config(APP_USART_INSTANCE, &usartConfig));
	return USART_SetOperationState(APP_USART_INSTANCE, DRIVER_STATUS_ON);
}
#endif /* APP_ENABLE_DEBUG */

/**
 * @brief Enters the application error-indication loop
 * @details
 * When @ref `APP_ENABLE_ONBOARD_LED` is `1U`, App_BootInit() already configures
 * and forces off the BSP on-board LED, so this handler asserts it as a visible
 * fault indication. With the LED capability disabled, the same non-returning
 * loop preserves the USART fault state without visible indication.
 */
__STATIC void App_ErrorHandler(void)
{
#if (APP_ENABLE_ONBOARD_LED == 1U)
	//! A persistent active-low LED state provides a visible fault indication without relying on USART.
	BSP_OB_LED_Set();
#endif /* APP_ENABLE_ONBOARD_LED */

	//! There is no recovery path for a failed peripheral transaction in this minimal demonstration.
	while (1)
	{
		//! Remain in the fault state until reset so the on-board LED cannot be mistaken for normal operation.
	}
}

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	// Local Variables
	uint8_t receivedByte = 0x00U;
	driver_status_t receiveStatus = DRIVER_STATUS_SUCCESS;

#if (APP_ENABLE_DEBUG == 0U)
	//! Without implicit debug setup, the application explicitly owns the complete GPIO and USART configuration sequence.
	if (App_ConfigGPIOForUSART() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}
	if (App_ConfigUSART() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}
#endif /* APP_ENABLE_DEBUG */

	//! The BSP transport transaction is complete; main now owns only steady-state polling behavior.
	while (1)
	{
		//! RXNE polling waits only for a completed terminal byte; timeout means no peer data arrived in this poll window.
		receiveStatus = USART_ReceiveByte(APP_USART_INSTANCE, &receivedByte);
		if (receiveStatus == DRIVER_STATUS_SUCCESS)
		{
			//! Echo exactly the captured byte, using TXE polling so DR is never overwritten before the previous byte is accepted.
			if (USART_TransmitByte(APP_USART_INSTANCE, receivedByte) != DRIVER_STATUS_SUCCESS)
			{
				App_ErrorHandler();
			}
		}
		else if (receiveStatus != DRIVER_STATUS_ERROR_TIMEOUT)
		{
			//! A receive timeout is expected during terminal idle time; every other Driver result invalidates the demo state.
			App_ErrorHandler();
		}
	}
}
