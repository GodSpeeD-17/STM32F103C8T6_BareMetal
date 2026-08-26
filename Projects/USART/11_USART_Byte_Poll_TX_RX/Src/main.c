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
 * - Uses: Layer 1 BSP board USART and, when enabled, BSP on-board LED APIs
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * When @ref `APP_ENABLE_USART` is `1U`, App_BootInit() directs BSP to enable
 * the required clocks and configure its fixed USART1 PA9 TX / PA10 RX mapping
 * for 115200 baud 8N1 operation with both transmitter and receiver enabled.
 * The main loop then polls for one received byte and,
 * on success, polls until the transmit data register accepts that same byte.
 * This terminal-echo behavior demonstrates configured full-duplex hardware
 * while keeping control flow polling based: no USART interrupt source and no
 * DMA request is enabled. A receive timeout means the terminal is idle and is
 * retried; a transmit timeout is unrecoverable because this stateless demo
 * cannot safely defer the captured byte. When the capability is `0U`, main()
 * remains an idle firmware loop and compiles no BSP_USART_* reference. When
 * enabled, the optional BSP on-board LED indicates an unrecoverable fault.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * This module owns only steady-state polling behavior, optional diagnostics,
 * and optional board fault indication. BSP owns each selected capability's
 * complete RCC/peripheral initialization transaction, and shared Drivers own
 * register access. This module neither reconfigures an
 * enabled transport nor accesses USART mapping details.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "app_config.h"

#if (APP_ENABLE_ONBOARD_LED == 1U)
#include "bsp_gpio.h"
#endif /* APP_ENABLE_ONBOARD_LED */

#if (APP_ENABLE_USART == 1U)
#include "bsp_usart.h"
#endif /* APP_ENABLE_USART */

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

#if (APP_ENABLE_USART == 1U)

/**
 * @brief Enters the application error-indication loop
 * @details
 * When @ref `APP_ENABLE_ONBOARD_LED` is `1U`, App_BootInit() already configures
 * and forces off the BSP on-board LED, so this handler asserts it as a visible
 * fault indication. With the capability disabled, the same non-returning loop
 * preserves the fault state without touching the independently selectable BSP
 * USART capability.
 */
static void App_ErrorHandler(void)
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

#endif /* APP_ENABLE_USART */

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
#if (APP_ENABLE_USART == 1U)
	// Local Variables
	uint8_t receivedByte = 0x00U;
	driver_status_t receiveStatus = DRIVER_STATUS_SUCCESS;

	//! App_BootInit() completed the BSP transport transaction; main owns only steady-state polling behavior.
	while (1)
	{
		//! RXNE polling waits only for a completed terminal byte; timeout means no peer data arrived in this poll window.
		receiveStatus = BSP_USART_ReceiveByte(&receivedByte);
		if (receiveStatus == DRIVER_STATUS_SUCCESS)
		{
			//! Echo exactly the captured byte, using TXE polling so DR is never overwritten before the previous byte is accepted.
			if (BSP_USART_TransmitByte(receivedByte) != DRIVER_STATUS_SUCCESS)
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
#else
	//! USART is deliberately absent, so retain a valid reset-to-idle firmware image without touching any board transport resource.
	while (1)
	{
		//! Remain idle until reset because this demonstration has no enabled steady-state capability.
	}
#endif /* APP_ENABLE_USART */
}
