/**
 * @file	usart_defines.h
 * @author	Shrey Shah
 * @brief	Declares public USART selector and validation macros
 * @version	v1.0
 * @date	23-08-2026
 *
 * @details
 * @section USART_DEFINES_H_HIERARCHY Hierarchy
 * - Position: Layer 3 USART Driver selector and validation vocabulary
 * - Used by: `usart_config.h`, `usart_codec.h`/`.c`, `usart.h`/`.c`
 * - Uses: `usart_data_types.h` scalar aliases, Core `USART_TypeDef` instance identity
 *
 * @section USART_DEFINES_H_RESPONSIBILITY Responsibility
 * Owns every public USART selector value and the pure validation macros that
 * guard those selectors. Owns no register access, clock sequencing, or
 * configuration structures.
 *
 * @section USART_DEFINES_H_BOUNDARY Dependency Boundary
 * This header depends only on `usart_data_types.h` and the Core USART
 * instance identity. It must not depend on `usart_config.h`, `usart_codec.h`,
 * `usart_ll.h`, or `usart.h`.
 */

// Header Guard
#ifndef USART_DEFINES_H_
#define USART_DEFINES_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "usart_data_types.h"
#include "stm32f1xx_usart.h"
#include "stm32f1xx.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup USART_03_Driver
 * @{
 */

/**
 * @brief USART Driver selector and validation defines
 * @defgroup USART_03_Driver_02_Defines USART Driver Selector and Validation Defines
 * @ingroup USART_03_Driver
 * @{
 */

// ==================================================================================================== //
//											USART Instance													//
// ==================================================================================================== //

/**
 * @brief USART instance validation
 * @defgroup USART_03_Driver_02_Defines_01_Instance USART Instance Defines
 * @ingroup USART_03_Driver_02_Defines
 * @{
 */

/**
 * @brief Returns whether a pointer is a supported USART instance
 * @param[in] USARTx Candidate USART peripheral instance
 * @returns Boolean-style validity result
 * @retval - `0x00U`: @p USARTx is not a supported USART peripheral instance
 * @retval - `0x01U`: @p USARTx is a supported USART peripheral instance
 * @def USART_INSTANCE_IS_VALID
 * @note The STM32F103C8T6 implements only `USART1`, `USART2`, and `USART3`.
 */
#define USART_INSTANCE_IS_VALID(USARTx)				\
	(((USARTx) == USART1) || ((USARTx) == USART2) || ((USARTx) == USART3))

/** @} */ // USART_03_Driver_02_Defines_01_Instance

// ==================================================================================================== //
//											USART Hardware Enable											//
// ==================================================================================================== //

/**
 * @brief USART TX/RX/RTS/CTS pin-enable selectors
 * @defgroup USART_03_Driver_02_Defines_02_Hardware USART Hardware Enable Defines
 * @ingroup USART_03_Driver_02_Defines
 * @details
 * Synchronous clock output (`CK`) is deliberately absent; see the Deferred
 * Domains table in `USART_ARCHITECTURE.md`.
 * @{
 */

/** @brief No USART hardware pins selected @def USART_HARDWARE_ENABLE_NONE */
#define USART_HARDWARE_ENABLE_NONE						((usart_hardware_enable_t) 0x00U)
/** @brief Enables the transmitter pin @def USART_HARDWARE_ENABLE_TX */
#define USART_HARDWARE_ENABLE_TX							((usart_hardware_enable_t) 0x01U)
/** @brief Enables the receiver pin @def USART_HARDWARE_ENABLE_RX */
#define USART_HARDWARE_ENABLE_RX							((usart_hardware_enable_t) 0x02U)
/** @brief Enables both the transmitter and receiver pins @def USART_HARDWARE_ENABLE_TX_RX */
#define USART_HARDWARE_ENABLE_TX_RX						((usart_hardware_enable_t) (USART_HARDWARE_ENABLE_TX | USART_HARDWARE_ENABLE_RX))
/** @brief Enables the RTS hardware flow-control pin @def USART_HARDWARE_ENABLE_RTS */
#define USART_HARDWARE_ENABLE_RTS						((usart_hardware_enable_t) 0x04U)
/** @brief Enables the CTS hardware flow-control pin @def USART_HARDWARE_ENABLE_CTS */
#define USART_HARDWARE_ENABLE_CTS						((usart_hardware_enable_t) 0x08U)
/** @brief Enables both the RTS and CTS hardware flow-control pins @def USART_HARDWARE_ENABLE_RTS_CTS */
#define USART_HARDWARE_ENABLE_RTS_CTS					((usart_hardware_enable_t) (USART_HARDWARE_ENABLE_RTS | USART_HARDWARE_ENABLE_CTS))
/** @brief All currently supported USART hardware pins @def USART_HARDWARE_ENABLE_ALL */
#define USART_HARDWARE_ENABLE_ALL						((usart_hardware_enable_t) (USART_HARDWARE_ENABLE_TX_RX | USART_HARDWARE_ENABLE_RTS_CTS))

/**
 * @brief Returns whether a hardware-enable bitmask is a supported combination
 * @param[in] hardware Candidate hardware-enable bitmask
 * @returns Boolean-style validity result
 * @retval - `0x00U`: @p hardware selects at least one unsupported bit
 * @retval - `0x01U`: @p hardware selects only supported bits
 * @def USART_HARDWARE_ENABLE_IS_VALID
 */
#define USART_HARDWARE_ENABLE_IS_VALID(hardware)		\
	(((usart_hardware_enable_t) (hardware) & (usart_hardware_enable_t) (~USART_HARDWARE_ENABLE_ALL)) == 0x00U)

/** @} */ // USART_03_Driver_02_Defines_02_Hardware

// ==================================================================================================== //
//											USART Line Configuration										//
// ==================================================================================================== //

/**
 * @brief USART data-bit, parity, and stop-bit selectors
 * @defgroup USART_03_Driver_02_Defines_03_LineConfig USART Line Configuration Defines
 * @ingroup USART_03_Driver_02_Defines
 * @{
 */

/** @brief 8 data bits per frame @def USART_DATA_BITS_8 */
#define USART_DATA_BITS_8							((usart_data_bits_t) 0x00U)
/** @brief 9 data bits per frame @def USART_DATA_BITS_9 */
#define USART_DATA_BITS_9							((usart_data_bits_t) 0x01U)

/**
 * @brief Returns whether a data-bit-count selector is supported
 * @param[in] dataBits Candidate data-bit-count selector
 * @returns Boolean-style validity result
 * @retval - `0x00U`: @p dataBits is not a supported selector
 * @retval - `0x01U`: @p dataBits is a supported selector
 * @def USART_DATA_BITS_IS_VALID
 */
#define USART_DATA_BITS_IS_VALID(dataBits)				\
	(((dataBits) == USART_DATA_BITS_8) || ((dataBits) == USART_DATA_BITS_9))

/** @brief No parity bit @def USART_PARITY_NONE */
#define USART_PARITY_NONE						((usart_parity_t) 0x00U)
/** @brief Even parity @def USART_PARITY_EVEN */
#define USART_PARITY_EVEN						((usart_parity_t) 0x01U)
/** @brief Odd parity @def USART_PARITY_ODD */
#define USART_PARITY_ODD						((usart_parity_t) 0x02U)

/**
 * @brief Returns whether a parity selector is supported
 * @param[in] parity Candidate parity selector
 * @returns Boolean-style validity result
 * @retval - `0x00U`: @p parity is not a supported selector
 * @retval - `0x01U`: @p parity is a supported selector
 * @def USART_PARITY_IS_VALID
 */
#define USART_PARITY_IS_VALID(parity)					\
	(((parity) == USART_PARITY_NONE) || ((parity) == USART_PARITY_EVEN) || ((parity) == USART_PARITY_ODD))

/** @brief 1 stop bit @def USART_STOP_BIT_1 */
#define USART_STOP_BIT_1						((usart_stop_bits_t) 0x00U)
/** @brief 0.5 stop bit; Smartcard mode only @def USART_STOP_BIT_0_5 */
#define USART_STOP_BIT_0_5						((usart_stop_bits_t) 0x01U)
/** @brief 2 stop bits @def USART_STOP_BIT_2 */
#define USART_STOP_BIT_2						((usart_stop_bits_t) 0x02U)
/** @brief 1.5 stop bits; Smartcard mode only @def USART_STOP_BIT_1_5 */
#define USART_STOP_BIT_1_5						((usart_stop_bits_t) 0x03U)

/**
 * @brief Returns whether a stop-bit-count selector is supported
 * @param[in] stopBits Candidate stop-bit-count selector
 * @returns Boolean-style validity result
 * @retval - `0x00U`: @p stopBits is not a supported selector
 * @retval - `0x01U`: @p stopBits is a supported selector
 * @def USART_STOP_BITS_IS_VALID
 */
#define USART_STOP_BITS_IS_VALID(stopBits)				\
	((usart_stop_bits_t) (stopBits) <= USART_STOP_BIT_1_5)

/** @} */ // USART_03_Driver_02_Defines_03_LineConfig

// ==================================================================================================== //
//											USART Baud Rate													//
// ==================================================================================================== //

/**
 * @brief USART preset baud-rate selectors
 * @defgroup USART_03_Driver_02_Defines_04_BaudRate USART Baud Rate Defines
 * @ingroup USART_03_Driver_02_Defines
 * @details
 * Callers select a fixed preset; `usart_codec.h` resolves the preset to its
 * numeric bits-per-second value and computes the `BRR` divider against the
 * live bus frequency.
 * @{
 */

/** @brief 9600 bits per second @def USART_BAUD_RATE_9600 */
#define USART_BAUD_RATE_9600					((usart_baud_rate_t) 0x00U)
/** @brief 19200 bits per second @def USART_BAUD_RATE_19200 */
#define USART_BAUD_RATE_19200					((usart_baud_rate_t) 0x01U)
/** @brief 38400 bits per second @def USART_BAUD_RATE_38400 */
#define USART_BAUD_RATE_38400					((usart_baud_rate_t) 0x02U)
/** @brief 57600 bits per second @def USART_BAUD_RATE_57600 */
#define USART_BAUD_RATE_57600					((usart_baud_rate_t) 0x03U)
/** @brief 115200 bits per second @def USART_BAUD_RATE_115200 */
#define USART_BAUD_RATE_115200					((usart_baud_rate_t) 0x04U)
/** @brief 230400 bits per second @def USART_BAUD_RATE_230400 */
#define USART_BAUD_RATE_230400					((usart_baud_rate_t) 0x05U)
/** @brief 460800 bits per second @def USART_BAUD_RATE_460800 */
#define USART_BAUD_RATE_460800					((usart_baud_rate_t) 0x06U)
/** @brief 921600 bits per second @def USART_BAUD_RATE_921600 */
#define USART_BAUD_RATE_921600					((usart_baud_rate_t) 0x07U)

/**
 * @brief Returns whether a baud-rate selector is supported
 * @param[in] baudRate Candidate baud-rate selector
 * @returns Boolean-style validity result
 * @retval - `0x00U`: @p baudRate is not a supported selector
 * @retval - `0x01U`: @p baudRate is a supported selector
 * @def USART_BAUD_RATE_IS_VALID
 */
#define USART_BAUD_RATE_IS_VALID(baudRate)				\
	((usart_baud_rate_t) (baudRate) <= USART_BAUD_RATE_921600)

/** @} */ // USART_03_Driver_02_Defines_04_BaudRate

// ==================================================================================================== //
//											USART IRQ														//
// ==================================================================================================== //

/**
 * @brief USART interrupt-request source and event-flag selectors
 * @defgroup USART_03_Driver_02_Defines_05_IRQ USART IRQ Defines
 * @ingroup USART_03_Driver_02_Defines
 * @details
 * Sources are enable-capable bits spanning two registers (`CR1` and `CR3`);
 * events are `SR` status flags. The two vocabularies are deliberately
 * separate types, matching the Timer driver's `tim_irq_source_t`/
 * `tim_event_flag_t` split.
 * @{
 */

/** @brief No USART interrupt-request source selected @def USART_IRQ_SOURCE_NONE */
#define USART_IRQ_SOURCE_NONE					((usart_irq_source_t) 0x00U)
/** @brief IDLE-line interrupt-request source (`CR1.IDLEIE`) @def USART_IRQ_SOURCE_IDLE */
#define USART_IRQ_SOURCE_IDLE					((usart_irq_source_t) 0x01U)
/** @brief RXNE/overrun interrupt-request source (`CR1.RXNEIE`) @def USART_IRQ_SOURCE_RXNE */
#define USART_IRQ_SOURCE_RXNE					((usart_irq_source_t) 0x02U)
/** @brief Transmission-complete interrupt-request source (`CR1.TCIE`) @def USART_IRQ_SOURCE_TC */
#define USART_IRQ_SOURCE_TC						((usart_irq_source_t) 0x04U)
/** @brief TXE interrupt-request source (`CR1.TXEIE`) @def USART_IRQ_SOURCE_TXE */
#define USART_IRQ_SOURCE_TXE					((usart_irq_source_t) 0x08U)
/** @brief Parity-error interrupt-request source (`CR1.PEIE`) @def USART_IRQ_SOURCE_PE */
#define USART_IRQ_SOURCE_PE						((usart_irq_source_t) 0x10U)
/** @brief CTS interrupt-request source (`CR3.CTSIE`) @def USART_IRQ_SOURCE_CTS */
#define USART_IRQ_SOURCE_CTS					((usart_irq_source_t) 0x20U)
/** @brief Framing/overrun/noise error interrupt-request source (`CR3.EIE`) @def USART_IRQ_SOURCE_ERROR */
#define USART_IRQ_SOURCE_ERROR					((usart_irq_source_t) 0x40U)
/** @brief All currently supported USART interrupt-request sources @def USART_IRQ_SOURCE_ALL */
#define USART_IRQ_SOURCE_ALL					((usart_irq_source_t) 0x7FU)

/**
 * @brief Returns whether an interrupt-request source bitmask is supported
 * @param[in] sources Candidate interrupt-request source bitmask
 * @returns Boolean-style validity result
 * @retval - `0x00U`: @p sources selects at least one unsupported bit
 * @retval - `0x01U`: @p sources selects only supported bits
 * @def USART_IRQ_SOURCE_IS_VALID
 */
#define USART_IRQ_SOURCE_IS_VALID(sources)				\
	(((usart_irq_source_t) (sources) & (usart_irq_source_t) (~USART_IRQ_SOURCE_ALL)) == 0x00U)

/** @brief No USART event flag selected @def USART_IRQ_EVENT_NONE */
#define USART_IRQ_EVENT_NONE					((usart_event_flag_t) 0x0000U)
/** @brief Parity-error event flag (`SR.PE`) @def USART_IRQ_EVENT_PE */
#define USART_IRQ_EVENT_PE						((usart_event_flag_t) 0x0001U)
/** @brief Framing-error event flag (`SR.FE`) @def USART_IRQ_EVENT_FE */
#define USART_IRQ_EVENT_FE						((usart_event_flag_t) 0x0002U)
/** @brief Noise-error event flag (`SR.NE`) @def USART_IRQ_EVENT_NE */
#define USART_IRQ_EVENT_NE						((usart_event_flag_t) 0x0004U)
/** @brief Overrun-error event flag (`SR.ORE`) @def USART_IRQ_EVENT_ORE */
#define USART_IRQ_EVENT_ORE						((usart_event_flag_t) 0x0008U)
/** @brief IDLE-line event flag (`SR.IDLE`) @def USART_IRQ_EVENT_IDLE */
#define USART_IRQ_EVENT_IDLE					((usart_event_flag_t) 0x0010U)
/** @brief Read-data-register-not-empty event flag (`SR.RXNE`) @def USART_IRQ_EVENT_RXNE */
#define USART_IRQ_EVENT_RXNE					((usart_event_flag_t) 0x0020U)
/** @brief Transmission-complete event flag (`SR.TC`) @def USART_IRQ_EVENT_TC */
#define USART_IRQ_EVENT_TC						((usart_event_flag_t) 0x0040U)
/** @brief Transmit-data-register-empty event flag (`SR.TXE`) @def USART_IRQ_EVENT_TXE */
#define USART_IRQ_EVENT_TXE						((usart_event_flag_t) 0x0080U)
/** @brief LIN break-detection event flag (`SR.LBD`) @def USART_IRQ_EVENT_LBD */
#define USART_IRQ_EVENT_LBD						((usart_event_flag_t) 0x0100U)
/** @brief CTS event flag (`SR.CTS`) @def USART_IRQ_EVENT_CTS */
#define USART_IRQ_EVENT_CTS						((usart_event_flag_t) 0x0200U)
/** @brief All currently supported USART event flags @def USART_IRQ_EVENT_ALL */
#define USART_IRQ_EVENT_ALL						((usart_event_flag_t) 0x03FFU)

/**
 * @brief Returns whether an event-flag bitmask is supported
 * @param[in] events Candidate event-flag bitmask
 * @returns Boolean-style validity result
 * @retval - `0x00U`: @p events selects at least one unsupported bit
 * @retval - `0x01U`: @p events selects only supported bits
 * @def USART_IRQ_EVENT_IS_VALID
 */
#define USART_IRQ_EVENT_IS_VALID(events)				\
	(((usart_event_flag_t) (events) & (usart_event_flag_t) (~USART_IRQ_EVENT_ALL)) == 0x0000U)

/** @} */ // USART_03_Driver_02_Defines_05_IRQ

/** @} */ // USART_03_Driver_02_Defines

/** @} */ // USART_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USART_DEFINES_H_ */
