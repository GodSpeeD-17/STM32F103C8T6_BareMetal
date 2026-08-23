/**
 * @file	usart.h
 * @author	Shrey Shah
 * @brief	USART Driver Public Interface
 * @version	v2.0
 * @date	23-08-2026
 *
 * @details
 * This header exposes the public USART driver API for UART (asynchronous)
 * mode only, per `USART_ARCHITECTURE.md`. Public code sees `USART_TypeDef*`
 * instance identity, `usart_config_t` configuration, public selectors, and
 * driver entry points. Low-level register access and codec image staging
 * remain private to `usart.c`.
 *
 * This pass admits only:
 * - `CR1.UE` operation state
 * - Root `USART_Config()`/`USART_DeConfig()` lifecycle
 * - `CR1`/`CR3` interrupt-request sources and `SR` event flags
 *
 * Byte-level TX/RX helpers and `USART_printf()` are intentionally not yet
 * declared here. Their signatures are undecided pending the `usart_codec.h`/
 * `usart.c` rewrite; they will return once frozen, rebuilt on `usart_ll.h`
 * instead of direct register access. Synchronous clock, Smartcard, IrDA,
 * LIN, multiprocessor wake, and DMA remain deferred; see
 * `USART_ARCHITECTURE.md`'s Deferred Domains table.
 */

// Header Guard
#ifndef USART_H_
#define USART_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "usart_config.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup USART_03_Driver
 * @{
 */

// ==================================================================================================== //
// USART Operation State APIs
// ==================================================================================================== //

/**
 * @brief Returns the current USART operation state
 * @details Reads `CR1.UE` only; it does not query the RCC clock gate.
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @returns @ref driver_status_t "USART operation-state observation"
 * @retval - @ref `DRIVER_STATUS_OFF`: The USART peripheral is disabled
 * @retval - @ref `DRIVER_STATUS_ON`: The USART peripheral is enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p USARTx was invalid
 */
driver_status_t USART_GetOperationState(const USART_TypeDef* const USARTx);

/**
 * @brief Sets the USART operation state
 * @details
 * Owns only the `CR1.UE` Read/Modify/Write transaction. It does not enable
 * or disable the RCC peripheral clock gate.
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[in] operationState Requested USART operation state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable the USART peripheral
 * - @ref `DRIVER_STATUS_ON`: Enable the USART peripheral
 * @returns @ref driver_status_t "USART operation-state operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested operation state was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p USARTx or @p operationState was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The USART peripheral clock gate is disabled
 * @pre The application enabled the USART peripheral clock gate through RCC
 * before calling this API.
 */
driver_status_t USART_SetOperationState(USART_TypeDef* const USARTx, const driver_status_t operationState);

// ==================================================================================================== //
// USART Configuration APIs
// ==================================================================================================== //

/**
 * @brief Restores one USART instance to its power-on register state
 * @details Pulses the matching `APB1RSTR`/`APB2RSTR` reset bit through
 * `RCC_PulsePeripheralReset()`. Leaves the RCC clock gate and NVIC delivery
 * state unchanged.
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @returns @ref driver_status_t "USART de-configuration operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested USART instance was reset-pulsed
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p USARTx was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The USART peripheral clock gate is disabled
 * @pre The application enabled the USART peripheral clock gate through RCC
 * before calling this API.
 */
driver_status_t USART_DeConfig(USART_TypeDef* const USARTx);

/**
 * @brief Applies one complete USART line/hardware/baud-rate configuration
 * @details
 * Validates @p USARTx and every field in @p pConfig, verifies the USART
 * peripheral clock gate is already enabled, enables the GPIO/AFIO clock
 * gate(s) required by this instance's private pin table and configures
 * those pins, then stages and commits the hardware-enable, line-format, and
 * baud-rate domains. This API never enables the USART peripheral's own
 * clock gate.
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[in] pConfig USART configuration to apply
 * Expected values:
 * - Non-`NULL`: Complete hardware, line-format, and baud-rate policy
 * @returns @ref driver_status_t "USART configuration operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested configuration was applied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pConfig was a null pointer
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p USARTx was invalid, or @p pConfig
 * contained an invalid hardware, line-format, or baud-rate selector
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The USART peripheral clock gate is disabled
 * @pre The application enabled the USART peripheral clock gate through RCC
 * before calling this API.
 * @note This API enables the GPIO port clock gate, and the AFIO clock gate
 * for alternate-function pins, for its own private pin table only. It never
 * enables the USART peripheral's own clock gate.
 */
driver_status_t USART_Config(USART_TypeDef* const USARTx, const usart_config_t* const pConfig);

// ==================================================================================================== //
// USART IRQ Source APIs
// ==================================================================================================== //

/**
 * @brief Returns the currently enabled USART interrupt-request sources
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[out] pSources Destination for the enabled interrupt-request source bitmask
 * Expected values:
 * - Any OR-combination of @ref `USART_IRQ_SOURCE_IDLE` through @ref `USART_IRQ_SOURCE_ERROR`
 * @returns @ref driver_status_t "USART interrupt-request source query status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p pSources was published successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSources was a null pointer
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p USARTx was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The USART peripheral clock gate is disabled
 */
driver_status_t USART_GetIRQSources(const USART_TypeDef* const USARTx, usart_irq_source_t* const pSources);

/**
 * @brief Enables or disables selected USART interrupt-request sources
 * @details
 * Sources span two registers (`CR1` for `IDLE`/`RXNE`/`TC`/`TXE`/`PE`, `CR3`
 * for `CTS`/error); this API stages and writes only the registers touched
 * by @p sources. It does not enable the matching NVIC vector.
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[in] sources Interrupt-request source bitmask to change
 * Accepted values:
 * - Any OR-combination of @ref `USART_IRQ_SOURCE_IDLE` through @ref `USART_IRQ_SOURCE_ERROR`
 * @param[in] sourceState Requested state for every selected source
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable every selected interrupt-request source
 * - @ref `DRIVER_STATUS_ON`: Enable every selected interrupt-request source
 * @returns @ref driver_status_t "USART interrupt-request source operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested sources were updated
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p USARTx, @p sources, or @p sourceState was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The USART peripheral clock gate is disabled
 * @note This API does not enable or disable the corresponding NVIC vector.
 * The application or integration layer owns global IRQ delivery.
 */
driver_status_t USART_SetIRQSources
(
	USART_TypeDef* const		USARTx,
	const usart_irq_source_t	sources,
	const driver_status_t		sourceState
);

// ==================================================================================================== //
// USART IRQ Event APIs
// ==================================================================================================== //

/**
 * @brief Returns the currently pending USART event flags
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[out] pEvents Destination for the pending event-flag bitmask
 * Expected values:
 * - Any OR-combination of @ref `USART_IRQ_EVENT_PE` through @ref `USART_IRQ_EVENT_CTS`
 * @returns @ref driver_status_t "USART event-flag query status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p pEvents was published successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pEvents was a null pointer
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p USARTx was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The USART peripheral clock gate is disabled
 * @note Reading `SR` through this API participates in the hardware
 * error-flag clearing sequence documented for `USART_AckIRQEvents()`.
 */
driver_status_t USART_GetIRQEvents(const USART_TypeDef* const USARTx, usart_event_flag_t* const pEvents);

/**
 * @brief Acknowledges selected USART event flags
 * @details
 * Applies the correct hardware-specific clearing mechanism per selected
 * bit rather than one uniform register write: `TC`/`CTS` are write-0-to-clear;
 * `PE`/`FE`/`NE`/`ORE`/`IDLE`/`RXNE` clear only through the hardware-mandated
 * sequence of reading `SR` followed by reading `DR`. `TXE` is read-only
 * status and is never acknowledged.
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[in] events Event-flag bitmask to acknowledge
 * Accepted values:
 * - Any OR-combination of @ref `USART_IRQ_EVENT_PE` through @ref `USART_IRQ_EVENT_CTS`
 * @returns @ref driver_status_t "USART event-flag acknowledgement status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The selected event flag(s) were acknowledged
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p USARTx or @p events was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The USART peripheral clock gate is disabled
 * @warning Acknowledging `PE`/`FE`/`NE`/`ORE`/`IDLE`/`RXNE` reads and discards
 * the buffered `DR` value as part of the hardware clearing sequence.
 */
driver_status_t USART_AckIRQEvents(USART_TypeDef* const USARTx, const usart_event_flag_t events);

/** @} */ // USART_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USART_H_ */
