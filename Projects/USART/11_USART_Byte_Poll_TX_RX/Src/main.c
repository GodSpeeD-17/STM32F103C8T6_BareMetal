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
 * - Uses: Layer 1 BSP board UART and, when enabled, BSP on-board LED APIs
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * App_BootInit() enables the application-owned clocks then directs BSP to
 * configure its fixed USART1 PA9 TX / PA10 RX mapping for 115200 baud 8N1
 * operation with both transmitter and receiver enabled. The main loop then
 * polls for one received byte and, on success, polls until the transmit data
 * register accepts that same byte. This terminal-echo behavior demonstrates
 * the configured full-duplex hardware while keeping application control flow
 * intentionally polling based: no USART interrupt source and no DMA request
 * is enabled. A receive timeout only means the terminal is idle and is
 * therefore retried; a transmit timeout is an unrecoverable fault because
 * the already-received byte cannot be safely deferred by this stateless demo.
 * Optional diagnostics use BSP_USART_printf() on this same board transport.
 * When enabled, the BSP on-board LED indicates an unrecoverable fault.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * This module owns only steady-state polling behavior, optional diagnostics,
 * and optional board fault indication. App_BootInit() owns the one-time RCC
 * clock-gate transaction; BSP owns the fixed GPIO/USART configuration and
 * shared Drivers own register access. This module neither reconfigures the
 * transport nor accesses USART mapping details.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "app_config.h"
#include "bsp.h"

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

/**
 * @brief Enters the application error-indication loop
 * @details
 * When @ref `APP_ENABLE_ONBOARD_LED` is `1U`, App_BootInit() already configures
 * and forces off the BSP on-board LED, so this handler asserts it as a visible
 * fault indication. With the capability disabled, the same non-returning loop
 * preserves the fault state without touching the separately required BSP UART
 * capability.
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

#if (APP_ENABLE_DEBUG == 1U)

/**
 * @brief Emits one optional diagnostic for a successfully echoed byte
 * @param[in] receivedByte Byte accepted by USART RX and returned through USART TX
 * Accepted values:
 * - `0x00U..0xFFU`: Any received 8-bit terminal byte
 * @returns @ref driver_status_t "Debug-output status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The complete diagnostic was transmitted
 * @retval - @ref `DRIVER_STATUS_ERROR_FAIL`: `vsnprintf()` could not format the fixed diagnostic string
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1's application-owned peripheral clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: USART TX did not become ready in its polling window
 * @pre App_BootInit() completed successfully and no code disabled USART1's
 * peripheral clock gate before this helper executes
 * @note The fixed format literal and BSP mapping exclude the lower formatter's
 * null-format and invalid-instance failure paths
 */
static driver_status_t App_DebugLogEchoedByte(const uint8_t receivedByte)
{
#if (APP_ENABLE_FLOAT == 1U)
	const float normalizedByte = (float) receivedByte / 255.0F;

	//! Debug plus float policy adds the normalized field without reconfiguring or disabling the ready full-duplex board transport.
	return BSP_USART_printf("[debug] echoed=0x%02X normalized=%.3f\r\n", (unsigned int) receivedByte, (double) normalizedByte);
#else
	//! Debug without float policy uses integer-only output and avoids linking the `%f` formatter.
	return BSP_USART_printf("[debug] echoed=0x%02X\r\n", (unsigned int) receivedByte);
#endif /* APP_ENABLE_FLOAT */
}

#endif /* APP_ENABLE_DEBUG */

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	// Local Variables
	uint8_t receivedByte = 0x00U;
	driver_status_t receiveStatus = DRIVER_STATUS_SUCCESS;

	//! App_BootInit() completed application clock gating and BSP transport setup; main owns only steady-state polling behavior.
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

#if (APP_ENABLE_DEBUG == 1U)
			//! Emit diagnostics only after the echo completes so debug text cannot change the echoed-byte ordering.
			if (App_DebugLogEchoedByte(receivedByte) != DRIVER_STATUS_SUCCESS)
			{
				App_ErrorHandler();
			}
#endif /* APP_ENABLE_DEBUG */
		}
		else if (receiveStatus != DRIVER_STATUS_ERROR_TIMEOUT)
		{
			//! A receive timeout is expected during terminal idle time; every other Driver result invalidates the demo state.
			App_ErrorHandler();
		}
	}
}
