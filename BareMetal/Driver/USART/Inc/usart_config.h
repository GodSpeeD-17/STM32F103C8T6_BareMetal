/**
 * @file	usart_config.h
 * @author	Shrey Shah
 * @brief	Declares the USART Driver root configuration structures
 * @version	v2.0
 * @date	23-08-2026
 *
 * @details
 * @section USART_CONFIG_H_HIERARCHY Hierarchy
 * - Position: Layer 3 USART Driver configuration structures
 * - Used by: `usart.h`/`.c`
 * - Uses: `usart_data_types.h` scalar aliases, `usart_defines.h` selector values
 *
 * @section USART_CONFIG_H_RESPONSIBILITY Responsibility
 * Owns the instance-independent `usart_config_t` structure-of-structures
 * applied by `USART_Config()`. Keeping `USARTx` out of this structure lets
 * one configuration be reused across `USART1`, `USART2`, and `USART3`.
 *
 * @section USART_CONFIG_H_BOUNDARY Dependency Boundary
 * This header owns configuration structures only. It must not depend on
 * `usart_codec.h`, `usart_ll.h`, or `usart.h`, and it performs no register
 * access or clock sequencing. GPIO/AFIO pin configuration is entirely
 * application-owned (matching Timer PWM); this header has no pin concept.
 */

// Header Guard
#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "usart_data_types.h"
#include "usart_defines.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup USART_03_Driver
 * @{
 */

/**
 * @brief USART Driver configuration structures
 * @defgroup USART_03_Driver_04_Config USART Driver Configuration Structures
 * @ingroup USART_03_Driver
 * @details
 * `usart_config_t` is the root structure of structures for the currently
 * admitted USART configuration domains. GPIO/AFIO pin routing is
 * deliberately absent: it is entirely application-owned (matching Timer
 * PWM's GPIO ownership model), not something `USART_Config()` touches at
 * any level.
 * @{
 */

/**
 * @brief USART frame format configuration
 * @details
 * Represents the `CR1.M`/`CR1.PCE`/`CR1.PS`/`CR2.STOP` domain as one
 * coherent, instance-independent structure.
 * @struct usart_frame_format_t
 */
typedef struct
{
	/**
	 * @brief Parity mode
	 * Accepted values:
	 * - @ref `USART_PARITY_NONE`
	 * - @ref `USART_PARITY_EVEN`
	 * - @ref `USART_PARITY_ODD`
	 * @memberof usart_frame_format_t
	 */
	usart_parity_t			parity: 2;

	/**
	 * @brief Stop-bit count
	 * Accepted values:
	 * - @ref `USART_STOP_BIT_1`
	 * - @ref `USART_STOP_BIT_0_5`
	 * - @ref `USART_STOP_BIT_2`
	 * - @ref `USART_STOP_BIT_1_5`
	 * @memberof usart_frame_format_t
	 */
	usart_stop_bits_t		stopBits: 2;

	/**
	 * @brief Data-bit count
	 * Accepted values:
	 * - @ref `USART_DATA_BITS_8`
	 * - @ref `USART_DATA_BITS_9`
	 * @memberof usart_frame_format_t
	 */
	usart_data_bits_t		dataBits: 1;

} usart_frame_format_t;

/**
 * @brief USART root configuration
 * @details
 * Applied atomically by `USART_Config()`. IRQ-source enablement is
 * deliberately absent, matching the Timer driver's rule that interrupt
 * intent remains an explicit, separately sequenced application action
 * through `USART_SetIRQSources()`.
 * @struct usart_config_t
 */
typedef struct
{
	/** 
	 * @brief Data-bit/parity/stop-bit frame format
	 * @memberof usart_config_t
	 */
	usart_frame_format_t		frameFormat;

	/**
	 * @brief TX/RX/RTS/CTS pin-enable selection
	 * Accepted values: (Any logical combination of)
	 * - @ref `USART_HARDWARE_ENABLE_NONE`
	 * - @ref `USART_HARDWARE_ENABLE_TX`
	 * - @ref `USART_HARDWARE_ENABLE_RX`
	 * - @ref `USART_HARDWARE_ENABLE_RTS`
	 * - @ref `USART_HARDWARE_ENABLE_CTS`
	 * - @ref `USART_HARDWARE_ENABLE_TX_RX`
	 * - @ref `USART_HARDWARE_ENABLE_RTS_CTS`
	 * - @ref `USART_HARDWARE_ENABLE_ALL`
	 * @memberof usart_config_t
	 */
	usart_hardware_enable_t		hardware;

	/**
	 * @brief Baud rate
	 * Accepted values:
	 * - @ref `USART_BAUD_RATE_9600`
	 * - @ref `USART_BAUD_RATE_19200`
	 * - @ref `USART_BAUD_RATE_38400`
	 * - @ref `USART_BAUD_RATE_57600`
	 * - @ref `USART_BAUD_RATE_115200`
	 * - @ref `USART_BAUD_RATE_230400`
	 * - @ref `USART_BAUD_RATE_460800`
	 * - @ref `USART_BAUD_RATE_921600`
	 * @memberof usart_config_t
	 */
	usart_baud_rate_t			baudRate;

} usart_config_t;

/** @} */ // USART_03_Driver_04_Config

/** @} */ // USART_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USART_CONFIG_H_ */
