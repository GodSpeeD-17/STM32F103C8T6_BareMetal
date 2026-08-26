/**
 * @file	bsp.c
 * @author	Shrey Shah
 * @brief	Board Support Package Implementation
 * @version	v1.0
 * @date	31-05-2026
 *
 * @details
 * This source owns board-specific behavior for the selected STM32F103C8T6
 * target. Generic GPIO driver code stays board-agnostic.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "bsp.h"
#include <stdarg.h>

#ifdef STM32F103C8T6__

// ==================================================================================================== //
//										On-Board LED APIs												//
// ==================================================================================================== //

driver_status_t BSP_OB_LED_Init(void)
{
	return GPIO_LED_Init(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

void BSP_OB_LED_Set(void)
{
	(void) GPIO_PinReset(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

void BSP_OB_LED_Reset(void)
{
	(void) GPIO_PinSet(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

void BSP_OB_LED_Toggle(void)
{
	(void) GPIO_PinToggle(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

driver_status_t BSP_OB_LED_Deinit(void)
{
	return GPIO_Deinit(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

// ==================================================================================================== //
// Board UART Local Helpers
// ==================================================================================================== //

/**
 * @brief Formats and transmits through the fixed board UART from an active variadic list
 * @param[in] pFormat `printf`-style format string
 * Expected values:
 * - Non-`NULL`: A null-terminated format string
 * @param[in] args Active variadic arguments matching @p `pFormat` conversion specifiers
 * Expected values:
 * - An active `va_list` started by the caller through `va_start()`
 * @returns @ref driver_status_t "Board UART variadic formatted-transmit status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every formatted byte was transmitted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pFormat` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_FAIL`: `vsnprintf()` reported a formatting error
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1's peripheral clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A formatted byte did not become transmittable within its bounded polling window
 * @pre BSP_USART_Init() completed successfully and the caller owns @p `args`
 */
static driver_status_t BSP_USART_vprintf(const char* const pFormat, va_list args)
{
	//! Keep both public variadic wrappers on USART_vprintf() so formatting buffering and TX polling have one implementation.
	return USART_vprintf(BSP_USART_INSTANCE, pFormat, args);
}

// ==================================================================================================== //
// Board UART APIs
// ==================================================================================================== //

driver_status_t BSP_USART_Deinit(void)
{
	//! Restore the USART register bank before returning its pins to GPIO reset state, leaving both RCC gates untouched.
	ASSERT_DRIVER_STATUS(USART_DeConfig(BSP_USART_INSTANCE));
	return GPIO_Deinit(BSP_USART_GPIO_PORT, BSP_USART_TX_PIN_MASK | BSP_USART_RX_PIN_MASK);
}

driver_status_t BSP_USART_Init(void)
{
	const usart_config_t boardUartConfig =
	{
		.frameFormat =
		{
			.parity = USART_PARITY_NONE,
			.stopBits = USART_STOP_BIT_1,
			.dataBits = USART_DATA_BITS_8
		},
		.hardware = USART_HARDWARE_ENABLE_TX_RX,
		.baudRate = BSP_USART_BAUD_RATE
	};

	//! Pin ownership precedes USART configuration: PA9 must route the peripheral transmitter before UE can drive it.
	ASSERT_DRIVER_STATUS
	(
		GPIO_SetPinModeConfig
		(
			BSP_USART_GPIO_PORT,
			BSP_USART_TX_PIN_MASK,
			GPIO_PIN_MODE_OUTPUT_50MHZ,
			GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL
		)
	);
	//! PA10 remains an input because the external UART peer, not STM32 GPIO output logic, drives received data.
	ASSERT_DRIVER_STATUS
	(
		GPIO_SetPinModeConfig
		(
			BSP_USART_GPIO_PORT,
			BSP_USART_RX_PIN_MASK,
			GPIO_PIN_MODE_INPUT,
			GPIO_PIN_CONFIG_INPUT_FLOATING
		)
	);
	//! The application already enabled GPIOA and USART1 clocks; configure both data directions without changing that ownership.
	ASSERT_DRIVER_STATUS(USART_Config(BSP_USART_INSTANCE, &boardUartConfig));
	return USART_SetOperationState(BSP_USART_INSTANCE, DRIVER_STATUS_ON);
}

driver_status_t BSP_USART_ReceiveByte(uint8_t* const pByte)
{
	//! The board API fixes the USART instance while retaining the Driver's bounded RXNE polling and status propagation.
	return USART_ReceiveByte(BSP_USART_INSTANCE, pByte);
}

driver_status_t BSP_USART_TransmitByte(const uint8_t byte)
{
	//! The board API fixes the USART instance while retaining the Driver's bounded TXE polling and status propagation.
	return USART_TransmitByte(BSP_USART_INSTANCE, byte);
}

driver_status_t BSP_USART_printf(const char* const pFormat, ...)
{
	// Local Variables
	va_list			args;
	driver_status_t	status = DRIVER_STATUS_SUCCESS;

	//! Bracket this public variadic call once, then share the fixed-instance formatting path with legacy consumers.
	va_start(args, pFormat);
	status = BSP_USART_vprintf(pFormat, args);
	va_end(args);

	return status;
}

// ==================================================================================================== //
// Legacy Debug UART Compatibility
// ==================================================================================================== //

driver_status_t BSP_Debug_UART_Deinit(void)
{
	//! Preserve the legacy lifecycle entry point while applying the canonical board UART restoration transaction.
	return BSP_USART_Deinit();
}

driver_status_t BSP_Debug_UART_Init(void)
{
	//! Preserve existing debug-UART users while configuring the canonical full-duplex board transport.
	return BSP_USART_Init();
}

driver_status_t BSP_Debug_UART_Printf(const char* const pFormat, ...)
{
	// Local Variables
	va_list			args;
	driver_status_t	status = DRIVER_STATUS_SUCCESS;

	//! Retain source compatibility without duplicating the variadic formatting and bounded TX-polling implementation.
	va_start(args, pFormat);
	status = BSP_USART_vprintf(pFormat, args);
	va_end(args);

	return status;
}

#endif /* STM32F103C8T6__ */
