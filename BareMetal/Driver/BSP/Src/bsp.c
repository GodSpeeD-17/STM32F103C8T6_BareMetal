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
#if defined(BSP_ENABLE_DEBUG_UART)
#include <stdarg.h>
#endif /* BSP_ENABLE_DEBUG_UART */

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

#if defined(BSP_ENABLE_DEBUG_UART)

// ==================================================================================================== //
//										Debug UART APIs												//
// ==================================================================================================== //

driver_status_t BSP_Debug_UART_Init(void)
{
	const usart_config_t debugUartConfig =
	{
		.frameFormat =
		{
			.parity = USART_PARITY_NONE,
			.stopBits = USART_STOP_BIT_1,
			.dataBits = USART_DATA_BITS_8
		},
		.hardware = USART_HARDWARE_ENABLE_TX,
		.baudRate = GPIO_DEBUG_UART_BAUD_RATE
	};

	//! Board-level pin routing precedes USART configuration; the USART driver never touches GPIO.
	ASSERT_DRIVER_STATUS
	(
		GPIO_SetPinModeConfig
		(
			GPIO_DEBUG_UART_PORT,
			GPIO_DEBUG_UART_TX_PIN,
			GPIO_PIN_MODE_OUTPUT_50MHZ,
			GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL
		)
	);
	ASSERT_DRIVER_STATUS(USART_Config(GPIO_DEBUG_UART_INSTANCE, &debugUartConfig));
	return USART_SetOperationState(GPIO_DEBUG_UART_INSTANCE, DRIVER_STATUS_ON);
}

driver_status_t BSP_Debug_UART_Printf(const char* const pFormat, ...)
{
	// Local Variables
	va_list			args;
	driver_status_t	status;

	va_start(args, pFormat);
	status = USART_vprintf(GPIO_DEBUG_UART_INSTANCE, pFormat, args);
	va_end(args);
	return status;
}

driver_status_t BSP_Debug_UART_Deinit(void)
{
	ASSERT_DRIVER_STATUS(USART_DeConfig(GPIO_DEBUG_UART_INSTANCE));
	return GPIO_Deinit(GPIO_DEBUG_UART_PORT, GPIO_DEBUG_UART_TX_PIN);
}

#endif /* BSP_ENABLE_DEBUG_UART */

#endif /* STM32F103C8T6__ */
