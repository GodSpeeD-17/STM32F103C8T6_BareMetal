/**
 * @file	bsp_usart.c
 * @author	Shrey Shah
 * @brief	Implements the Blue Pill full-duplex USART capability
 * @version	v1.0
 * @date	26-08-2026
 *
 * @details
 * This source owns the cohesive RCC, GPIO, and USART initialization transaction
 * for USART1 PA9/PA10. Application code selects and calls the capability but
 * does not reproduce its fixed board-resource configuration.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "bsp_usart.h"
#include "rcc.h"
#include <stdarg.h>

#ifdef STM32F103C8T6__

// ==================================================================================================== //
// Private Configuration
// ==================================================================================================== //

/** @brief GPIOA clock gate required by the board USART route @def BSP_USART_GPIO_CLOCK_ENABLE_MASK */
#define BSP_USART_GPIO_CLOCK_ENABLE_MASK		(RCC_APB2ENR_IOPAEN)
/** @brief USART1 clock gate required by the board USART peripheral @def BSP_USART_CLOCK_ENABLE_MASK */
#define BSP_USART_CLOCK_ENABLE_MASK				(RCC_APB2ENR_USART1EN)

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

/**
 * @brief Enables both clocks required by the fixed board USART capability
 * @returns @ref driver_status_t "Board USART clock-enable status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: GPIOA and USART1 clocks were enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A fixed APB2 clock mapping was rejected
 */
static inline driver_status_t BSP_USART_EnableClocks(void)
{
	//! GPIOA must be clocked before its PA9/PA10 configuration registers can accept the board route.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(RCC_APB2_BUS, BSP_USART_GPIO_CLOCK_ENABLE_MASK, DRIVER_STATUS_ON));
	//! USART1 has a separate APB2 gate even though its reset-default pins need no AFIO transaction.
	return RCC_SetPeripheralClockState(RCC_APB2_BUS, BSP_USART_CLOCK_ENABLE_MASK, DRIVER_STATUS_ON);
}

/**
 * @brief Configures the PA9 transmitter and PA10 receiver board route
 * @returns @ref driver_status_t "Board USART GPIO-configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: PA9 and PA10 were configured
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A fixed board GPIO mapping was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: GPIOA clock validation or GPIO staging failed
 */
static inline driver_status_t BSP_USART_ConfigureGPIO(void)
{
	//! Configure PA9 before enabling USART1 so the transmitter never drives an unprepared pin route.
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
	//! PA10 remains an input because the external USART peer drives the received signal.
	return GPIO_SetPinModeConfig
	(
		BSP_USART_GPIO_PORT,
		BSP_USART_RX_PIN_MASK,
		GPIO_PIN_MODE_INPUT,
		GPIO_PIN_CONFIG_INPUT_FLOATING
	);
}

/**
 * @brief Configures and enables USART1 with the fixed board transport policy
 * @returns @ref driver_status_t "Board USART peripheral-configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: USART1 was configured and enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The fixed USART configuration was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1 clock was disabled or its bus frequency was zero
 */
static inline driver_status_t BSP_USART_ConfigurePeripheral(void)
{
	const usart_config_t boardUsartConfig =
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

	//! Apply the complete 115200-baud 8N1 TX+RX configuration before publishing USART1 as operational.
	ASSERT_DRIVER_STATUS(USART_Config(BSP_USART_INSTANCE, &boardUsartConfig));
	return USART_SetOperationState(BSP_USART_INSTANCE, DRIVER_STATUS_ON);
}

/**
 * @brief Formats and transmits through the fixed board USART from an active variadic list
 * @param[in] pFormat `printf`-style format string
 * Expected values:
 * - Non-`NULL`: A null-terminated format string
 * @param[in] args Active variadic arguments matching @p `pFormat` conversion specifiers
 * Expected values:
 * - An active `va_list` started by the caller through `va_start()`
 * @returns @ref driver_status_t "Board USART variadic formatted-transmit status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every formatted byte was transmitted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pFormat` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_FAIL`: `vsnprintf()` reported a formatting error
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1 clock was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A formatted byte did not become transmittable within its polling window
 * @pre BSP_InitUSART() completed successfully and the caller owns @p `args`
 */
static driver_status_t BSP_USART_vprintf(const char* const pFormat, va_list args)
{
	//! Both public variadic APIs share one fixed-instance formatter and bounded TX polling path.
	return USART_vprintf(BSP_USART_INSTANCE, pFormat, args);
}

// ==================================================================================================== //
// Public API
// ==================================================================================================== //

driver_status_t BSP_InitUSART(void)
{
	//! Acquire the fixed board clocks before configuring their dependent GPIO and USART register banks.
	ASSERT_DRIVER_STATUS(BSP_USART_EnableClocks());
	ASSERT_DRIVER_STATUS(BSP_USART_ConfigureGPIO());
	return BSP_USART_ConfigurePeripheral();
}

driver_status_t BSP_USART_ReceiveByte(uint8_t* const pByte)
{
	//! Fix the board instance while retaining the USART Driver's bounded RXNE polling and exact status propagation.
	return USART_ReceiveByte(BSP_USART_INSTANCE, pByte);
}

driver_status_t BSP_USART_TransmitByte(const uint8_t byte)
{
	//! Fix the board instance while retaining the USART Driver's bounded TXE polling and exact status propagation.
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
// Legacy Debug USART Compatibility
// ==================================================================================================== //

driver_status_t BSP_Debug_UART_Init(void)
{
	//! Preserve the legacy entry point while using the canonical complete board USART initialization transaction.
	return BSP_InitUSART();
}

driver_status_t BSP_Debug_UART_Printf(const char* const pFormat, ...)
{
	// Local Variables
	va_list			args;
	driver_status_t	status = DRIVER_STATUS_SUCCESS;

	//! Retain source compatibility without duplicating the variadic formatter and bounded TX-polling implementation.
	va_start(args, pFormat);
	status = BSP_USART_vprintf(pFormat, args);
	va_end(args);

	return status;
}

#endif /* STM32F103C8T6__ */
