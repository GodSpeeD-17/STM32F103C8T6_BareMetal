/**
 * @file	bsp_usart.h
 * @author	Shrey Shah
 * @brief	Declares the Blue Pill full-duplex USART capability
 * @version	v1.0
 * @date	26-08-2026
 *
 * @details
 * This self-contained capability header owns the public USART1 PA9/PA10 board
 * mapping and operations. It includes only GPIO and USART because its public
 * macros use their symbols; RCC remains private to BSP_InitUSART().
 */

// Header Guard
#ifndef BSP_USART_H_
#define BSP_USART_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "gpio.h"
#include "usart.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup BSP_01_BoardSupport
 * @{
 */

#ifdef STM32F103C8T6__

// ==================================================================================================== //
// Board USART Mapping
// ==================================================================================================== //

/**
 * @brief USART peripheral instance used by the board full-duplex capability
 * @def BSP_USART_INSTANCE
 * @details
 * Every BSP USART operation uses USART1's reset-default PA9/PA10 route. This
 * mapping does not enable or configure USART1 by itself.
 * Accepted values:
 * - @ref `USART1`: Blue Pill board USART peripheral
 */
#define BSP_USART_INSTANCE			(USART1)

/**
 * @brief GPIO port carrying both board USART signals
 * @def BSP_USART_GPIO_PORT
 * @details
 * PA9 and PA10 both reside on GPIOA. This mapping does not enable GPIOA or
 * configure either pin by itself.
 * Accepted values:
 * - @ref `GPIOA`: Port containing the reset-default USART1 route
 */
#define BSP_USART_GPIO_PORT			(GPIOA)

/**
 * @brief Board USART transmitter pin mask
 * @def BSP_USART_TX_PIN_MASK
 * @details
 * BSP_InitUSART() configures PA9 as a 50 MHz alternate-function push-pull
 * output so USART1 drives outgoing data.
 * Accepted values:
 * - @ref `GPIO_PIN_9`: USART1 reset-default transmitter pin
 */
#define BSP_USART_TX_PIN_MASK		((gpio_pin_t) GPIO_PIN_9)

/**
 * @brief Board USART receiver pin mask
 * @def BSP_USART_RX_PIN_MASK
 * @details
 * BSP_InitUSART() configures PA10 as a floating input because the external
 * peer drives incoming data.
 * Accepted values:
 * - @ref `GPIO_PIN_10`: USART1 reset-default receiver pin
 */
#define BSP_USART_RX_PIN_MASK		((gpio_pin_t) GPIO_PIN_10)

/**
 * @brief Fixed board USART baud-rate preset
 * @def BSP_USART_BAUD_RATE
 * @details
 * BSP_InitUSART() combines this rate with fixed 8N1 and TX+RX configuration.
 * The macro alone does not write BRR or enable USART1.
 * Accepted values:
 * - @ref `USART_BAUD_RATE_115200`: Blue Pill board USART rate
 */
#define BSP_USART_BAUD_RATE			(USART_BAUD_RATE_115200)

// ==================================================================================================== //
// Board USART APIs
// ==================================================================================================== //

/**
 * @brief Initializes the complete Blue Pill full-duplex USART capability
 * @details
 * Enables the GPIOA and USART1 clocks, configures PA9 as alternate-function
 * push-pull and PA10 as floating input, applies 115200-baud 8N1 TX+RX policy,
 * and enables USART1. BSP owns this complete RCC/GPIO/USART transaction.
 * @returns @ref driver_status_t "Board USART initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clocks, pins, and USART1 were initialized and enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A fixed RCC, GPIO, or USART mapping was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: GPIO staging failed, a required clock was unavailable, or the USART bus frequency was zero
 * @warning Reconfigures the complete mapped USART1 transport; no other client
 * may own USART1, PA9, or PA10 while this capability is active
 */
driver_status_t BSP_InitUSART(void);

/**
 * @brief Receives one byte through the board USART by bounded polling
 * @param[out] pByte Destination for the received byte
 * Expected values:
 * - Non-`NULL`: Storage for one received byte
 * @returns @ref driver_status_t "Board USART receive status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `pByte` was populated with one received byte
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pByte` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1 clock was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: No byte arrived within the bounded polling window
 * @pre BSP_InitUSART() completed successfully
 * @note This forwarding path does not enable USART IRQ or DMA requests
 */
driver_status_t BSP_USART_ReceiveByte(uint8_t* const pByte);

/**
 * @brief Transmits one byte through the board USART by bounded polling
 * @param[in] byte Byte to transmit
 * Accepted values:
 * - `0x00U..0xFFU`: Any 8-bit USART payload value
 * @returns @ref driver_status_t "Board USART transmit status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `byte` was accepted by USART1 data register
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1 clock was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: USART1 data register did not become free within its polling window
 * @pre BSP_InitUSART() completed successfully
 * @note This forwarding path does not enable USART IRQ or DMA requests
 */
driver_status_t BSP_USART_TransmitByte(const uint8_t byte);

/**
 * @brief Formats and transmits a message through the board USART
 * @details
 * Brackets the variadic arguments and forwards them to USART_vprintf() for
 * the fixed board instance, reusing its bounded buffer and TX polling.
 * @param[in] pFormat `printf`-style format string
 * Expected values:
 * - Non-`NULL`: A null-terminated format string
 * @param[in] ... Variadic arguments matching @p `pFormat` conversion specifiers
 * @returns @ref driver_status_t "Board USART formatted-transmit status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every formatted byte was transmitted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pFormat` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_FAIL`: `vsnprintf()` reported a formatting error
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1 clock was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A formatted byte did not become transmittable within its polling window
 * @pre BSP_InitUSART() completed successfully
 */
driver_status_t BSP_USART_printf(const char* const pFormat, ...);

// ==================================================================================================== //
// Legacy Debug USART Compatibility
// ==================================================================================================== //

/**
 * @brief Initializes the legacy debug-USART compatibility path
 * @details Delegates to BSP_InitUSART() so legacy consumers receive the same
 * complete RCC/GPIO/USART initialization transaction.
 * @returns @ref driver_status_t "Legacy debug-USART initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: BSP_InitUSART() completed successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A fixed BSP resource mapping was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: BSP USART hardware configuration failed
 * @deprecated Use BSP_InitUSART(); this wrapper preserves existing consumers
 */
driver_status_t BSP_Debug_UART_Init(void);

/**
 * @brief Transmits a formatted legacy debug message through the board USART
 * @param[in] pFormat `printf`-style format string
 * Expected values:
 * - Non-`NULL`: A null-terminated format string
 * @param[in] ... Variadic arguments matching @p `pFormat` conversion specifiers
 * @returns @ref driver_status_t "Legacy debug formatted-transmit status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every formatted byte was transmitted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pFormat` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_FAIL`: `vsnprintf()` reported a formatting error
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1 clock was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A formatted byte did not become transmittable within its polling window
 * @pre BSP_Debug_UART_Init() completed successfully
 * @deprecated Use BSP_USART_printf(); this wrapper preserves existing consumers
 */
driver_status_t BSP_Debug_UART_Printf(const char* const pFormat, ...);

#endif /* STM32F103C8T6__ */

/** @} */ // BSP_01_BoardSupport

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BSP_USART_H_ */
