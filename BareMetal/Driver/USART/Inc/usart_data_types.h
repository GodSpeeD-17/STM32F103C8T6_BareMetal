/**
 * @file	usart_data_types.h
 * @author	Shrey Shah
 * @brief	Declares USART Driver scalar data types
 * @version	v1.0
 * @date	23-08-2026
 *
 * @details
 * @section USART_DATA_TYPES_H_HIERARCHY Hierarchy
 * - Position: Layer 3 USART Driver data types
 * - Used by: `usart_defines.h`, `usart_config.h`, `usart_codec.h`/`.c`, `usart.h`/`.c`
 * - Uses: Core scalar aliases
 *
 * @section USART_DATA_TYPES_H_RESPONSIBILITY Responsibility
 * Owns USART scalar typedef aliases shared across the USART stack. Owns no
 * selector values, validation, configuration structures, or register access.
 *
 * @section USART_DATA_TYPES_H_BOUNDARY Dependency Boundary
 * This header depends only on Core scalar vocabulary. It must not depend on
 * `usart_defines.h`, `usart_config.h`, `usart_codec.h`, `usart_ll.h`, or `usart.h`.
 */

// Header Guard
#ifndef USART_DATA_TYPES_H_
#define USART_DATA_TYPES_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "stm32f1xx_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup USART_03_Driver
 * @{
 */

/**
 * @brief USART Driver data types
 * @defgroup USART_03_Driver_01_Types USART Driver Data Types
 * @ingroup USART_03_Driver
 * @details
 * Scalar aliases shared by the USART Defines, Config, Codec, and Driver
 * layers. No selector values, validation, or register access live here.
 * @{
 */

/** @brief USART data-bit-count selector type @typedef usart_data_bits_t */
typedef uint8_t				usart_data_bits_t;
/** @brief USART parity selector type @typedef usart_parity_t */
typedef uint8_t				usart_parity_t;
/** @brief USART stop-bit-count selector type @typedef usart_stop_bits_t */
typedef uint8_t				usart_stop_bits_t;
/** @brief USART hardware pin-enable bitmask type (TX/RX/RTS/CTS) @typedef usart_hardware_enable_t */
typedef uint8_t				usart_hardware_enable_t;
/** @brief USART preset baud-rate selector type @typedef usart_baud_rate_t */
typedef uint8_t				usart_baud_rate_t;
/** @brief USART interrupt-request source selector bitmask type (`CR1` + `CR3` enable bits) @typedef usart_irq_source_t */
typedef uint8_t				usart_irq_source_t;
/** @brief USART interrupt event-flag bitmask type (`SR` status bits) @typedef usart_event_flag_t */
typedef uint16_t			usart_event_flag_t;

/** @} */ // USART_03_Driver_01_Types

/** @} */ // USART_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USART_DATA_TYPES_H_ */
