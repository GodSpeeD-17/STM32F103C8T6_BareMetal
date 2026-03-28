/**
 * @file	gpio_helper.h
 * @author	Shrey Shah
 * @brief	GPIO Internal Driver Helper Interface
 * @version	v1.0
 * @date	29-03-2026
 *
 * @details
 * This header defines the internal helper utilities that bridge the GPIO
 * driver layer and the GPIO low-level layer.
 *
 * The helper layer accepts driver-facing GPIO selectors, translates them into
 * raw STM32F1 GPIO register fields, and updates staged register images so the
 * driver can perform one read-modify-write cycle per touched register.
 *
 * This is not a user-facing GPIO interface.
 *
 * Practical Rule:
 * - `gpio.c` owns driver policy and register-level batching.
 * - `gpio_helper.c` owns the per-pin staged-image updates and hardware-state
 *   decoding needed to keep `gpio.c` free from bit-position plumbing.
 */

#ifndef GPIO_HELPER_H_
#define GPIO_HELPER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//											   Includes											   //
// ==================================================================================================== //
#include "gpio_ll.h"

/**
 * @brief Checks whether a GPIO pin mask selects exactly one valid pin
 * @def _GPIO_HELPER_IS_SINGLE_PIN_MASK_VALID
 * @param[in] _PIN GPIO pin mask
 * @returns Single-pin-mask validity status
 * @retval - `0x00U`: Pin Mask Invalid
 * @retval - `0x01U`: Pin Mask Valid
 */
#define _GPIO_HELPER_IS_SINGLE_PIN_MASK_VALID(_PIN)													\
(																										\
	((((gpio_pin_t)(_PIN)) != GPIO_PIN_NONE) && ((((gpio_pin_t)(_PIN)) & ~GPIO_PIN_ALL) == GPIO_PIN_NONE) &&	\
	((((gpio_pin_t)(_PIN)) & (((gpio_pin_t)(_PIN)) - (gpio_pin_t) 1U)) == GPIO_PIN_NONE)) ? 0x01U : 0x00U	\
)

/**
 * @brief Checks whether a raw MODE field value is valid
 * @def _GPIO_HELPER_IS_MODE_BITS_VALID
 * @param[in] _MODE_BITS Raw 2-bit MODE field value
 * @returns MODE field validity status
 * @retval - `0x00U`:	MODE Invalid
 * @retval - `0x01U`:	MODE Valid
 */
#define _GPIO_HELPER_IS_MODE_BITS_VALID(_MODE_BITS)													\
	((((gpio_mode_t)(_MODE_BITS) & (gpio_mode_t) ~0x03U) == (gpio_mode_t) 0x00U) ? 0x01U : 0x00U)

/**
 * @brief Checks whether a raw CNF field value is valid
 * @def _GPIO_HELPER_IS_CNF_BITS_VALID
 * @param[in] _CNF_BITS Raw 2-bit CNF field value
 * @returns CNF field validity status
 * @retval - `0x00U`:	CNF Invalid
 * @retval - `0x01U`:	CNF Valid
 */
#define _GPIO_HELPER_IS_CNF_BITS_VALID(_CNF_BITS)													\
	((((gpio_cnf_t)(_CNF_BITS) & ((gpio_cnf_t) ~0x03U)) == (gpio_cnf_t) 0x00U) ? 0x01U : 0x00U)

/**
 * @brief Checks whether a raw pull-direction bit value is valid
 * @def _GPIO_HELPER_IS_PULL_BIT_VALID
 * @param[in] _PULL_BIT Raw pull-direction bit
 * @returns Pull-bit validity status
 * @retval - `0x00U`:	Pull Invalid
 * @retval - `0x01U`:	Pull Valid
 */
#define _GPIO_HELPER_IS_PULL_BIT_VALID(_PULL_BIT)													\
	((((gpio_pull_t)(_PULL_BIT)) <= ((gpio_pull_t) 0x01U)) ? 0x01U : 0x00U)

/**
 * @brief Checks whether a packed raw pin configuration field is valid
 * @def _GPIO_HELPER_IS_PIN_CONFIG_BITS_VALID
 * @param[in] _PIN_CONFIG_BITS Packed raw pin configuration bits
 * @returns Packed pin-configuration validity status
 * @retval - `0x00U`:	Pin Configuration Invalid
 * @retval - `0x01U`:	Pin Configuration Valid
 */
#define _GPIO_HELPER_IS_PIN_CONFIG_BITS_VALID(_PIN_CONFIG_BITS)										\
	((((gpio_pin_config_bits_t)(_PIN_CONFIG_BITS) & (gpio_pin_config_bits_t) ~0x0FU) == (gpio_pin_config_bits_t) 0x00U) ? 0x01U : 0x00U)

/**
 * @brief Packs raw CNF and MODE bits into one 4-bit GPIO pin configuration field
 * @def _GPIO_HELPER_GET_PIN_CONFIG_BITS
 * @param[in] _MODE_BITS Raw 2-bit MODE field value
 * @param[in] _CNF_BITS Raw 2-bit CNF field value
 * @returns Packed raw GPIO pin configuration field as `CNF[3:2] | MODE[1:0]`
 */
#define _GPIO_HELPER_GET_PIN_CONFIG_BITS(_MODE_BITS, _CNF_BITS)										\
	((gpio_pin_config_bits_t)((((gpio_cnf_t)(_CNF_BITS)) & (gpio_cnf_t) 0x03U) << 2U) |	\
	((gpio_mode_t)(_MODE_BITS) & (gpio_mode_t) 0x03U))

/**
 * @brief Updates one pin slot inside a staged `CRL` or `CRH` image
 * @details
 * This helper forms the driver-to-LL bridge for full pin configuration.
 * It accepts driver-layer `mode` and `config` selectors, translates them into
 * the raw `MODE[1:0]` and `CNF[1:0]` fields expected by the STM32F1 register
 * layout, and updates only the selected pin slot inside the staged register
 * image.
 *
 * @param[in] pin GPIO single-pin mask
 * @param[in] mode Driver-layer GPIO mode selector
 * @param[in] config Driver-layer GPIO configuration selector
 * @param[in,out] pCrxRegImage Staged `CRL` or `CRH` image to update in place
 * @returns Driver operation status
 * @retval `DRIVER_STATUS_SUCCESS`:				Pin mode/config image updated successfully
 * @retval `DRIVER_STATUS_ERROR_NULL_PTR`:		`pCrxRegImage` was `NULL`
 * @retval `DRIVER_STATUS_ERROR_INVALID_ARG`:	`pin`, `mode`, or `config` was invalid
 */
driver_status_t _GPIO_Helper_UpdatePinModeConfigImage
(
	const gpio_pin_t		pin,
	const gpio_pin_mode_t	mode,
	const gpio_pin_config_t	config,
	uint32_t* const			pCrxRegImage
);

/**
 * @brief Updates the MODE field for one pin inside a staged `CRL` or `CRH` image
 * @details
 * This helper accepts a driver-layer mode selector, translates it into the raw
 * STM32F1 `MODE[1:0]` field, and updates only the selected pin slot inside the
 * staged register image.
 *
 * @param[in] pin GPIO single-pin mask
 * @param[in] mode Driver-layer GPIO mode selector
 * @param[in,out] pCrxRegImage Staged `CRL` or `CRH` image to update in place
 * @returns Driver operation status
 * @retval `DRIVER_STATUS_SUCCESS`:				Pin MODE field updated successfully
 * @retval `DRIVER_STATUS_ERROR_NULL_PTR`:		`pCrxRegImage` was `NULL`
 * @retval `DRIVER_STATUS_ERROR_INVALID_ARG`:	`pin` or `mode` was invalid
 */
driver_status_t _GPIO_Helper_UpdatePinModeImage
(
	const gpio_pin_t		pin,
	const gpio_pin_mode_t	mode,
	uint32_t* const			pCrxRegImage
);

/**
 * @brief Updates the CNF field for one pin inside a staged `CRL` or `CRH` image
 * @details
 * This helper accepts a driver-layer configuration selector, translates it into
 * the raw STM32F1 `CNF[1:0]` field, and updates only the selected pin slot
 * inside the staged register image.
 *
 * @param[in] pin GPIO single-pin mask
 * @param[in] config Driver-layer GPIO configuration selector
 * @param[in,out] pCrxRegImage Staged `CRL` or `CRH` image to update in place
 * @returns Driver operation status
 * @retval `DRIVER_STATUS_SUCCESS`:				Pin CNF field updated successfully
 * @retval `DRIVER_STATUS_ERROR_NULL_PTR`:		`pCrxRegImage` was `NULL`
 * @retval `DRIVER_STATUS_ERROR_INVALID_ARG`:	`pin` or `config` was invalid
 */
driver_status_t _GPIO_Helper_UpdatePinConfigImage
(
	const gpio_pin_t		pin,
	const gpio_pin_config_t	config,
	uint32_t* const			pCrxRegImage
);

/**
 * @brief Restores one pin slot to the STM32F1 reset configuration image
 * @param[in] pin GPIO single-pin mask
 * @param[in,out] pCrxRegImage Staged `CRL` or `CRH` image to reset in place
 * @returns Driver operation status
 * @retval `DRIVER_STATUS_SUCCESS`:				Pin reset image staged successfully
 * @retval `DRIVER_STATUS_ERROR_NULL_PTR`:		`pCrxRegImage` was `NULL`
 * @retval `DRIVER_STATUS_ERROR_INVALID_ARG`:	`pin` was invalid
 */
driver_status_t _GPIO_Helper_ResetPinConfigImage
(
	const gpio_pin_t	pin,
	uint32_t* const		pCrxRegImage
);

/**
 * @brief Updates the staged `ODR` image for input pull-up or pull-down selection
 * @details
 * This helper accepts a driver-layer GPIO configuration selector, extracts the
 * pull direction required by the configuration, and updates the staged `ODR`
 * image for the selected pin.
 *
 * @param[in] pin GPIO single-pin mask
 * @param[in] config Driver-layer GPIO configuration selector
 * @param[in,out] pOdrRegImage Staged `ODR` image to update in place
 * @returns Driver operation status
 * @retval `DRIVER_STATUS_SUCCESS`:				Pull state staged successfully
 * @retval `DRIVER_STATUS_ERROR_NULL_PTR`:		`pOdrRegImage` was `NULL`
 * @retval `DRIVER_STATUS_ERROR_INVALID_ARG`:	`pin` or `config` was invalid
 */
driver_status_t _GPIO_Helper_UpdatePinPullImage
(
	const gpio_pin_t		pin,
	const gpio_pin_config_t	config,
	uint32_t* const			pOdrRegImage
);

/**
 * @brief Reads one GPIO pin slot and translates it into driver-facing mode/config selectors
 * @details
 * This helper reads the selected pin slot from `CRL` or `CRH`, decodes the raw
 * `MODE[1:0]` and `CNF[1:0]` fields, and translates them into the driver-layer
 * `gpio_pin_mode_t` and `gpio_pin_config_t` values.
 *
 * For input pull-up or pull-down mode, this helper also reads `ODR` to resolve
 * whether the configured pull direction is UP or DOWN.
 *
 * At least one of `pMode` or `pConfig` must be non-`NULL`.
 *
 * @param[in] GPIOx Target GPIO peripheral instance
 * @param[in] pin GPIO single-pin mask
 * @param[out] pMode Driver-facing GPIO mode selector
 * @param[out] pConfig Driver-facing GPIO configuration selector
 * @returns Driver operation status
 * @retval `DRIVER_STATUS_SUCCESS`:				Pin mode/config read successfully
 * @retval `DRIVER_STATUS_ERROR_NULL_PTR`:		Both `pMode` and `pConfig` were `NULL`
 * @retval `DRIVER_STATUS_ERROR_INVALID_ARG`:	`GPIOx`, `pin`, or the raw pin slot state was invalid
 */
driver_status_t _GPIO_Helper_ReadPinModeConfig
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pin,
	gpio_pin_mode_t* const		pMode,
	gpio_pin_config_t* const	pConfig
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_HELPER_H_ */
