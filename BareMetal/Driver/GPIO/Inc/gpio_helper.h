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
 * - Layer 2 (`gpio_helper.c`) owns per-pin staged-image updates and hardware-state
 *   decoding.
 * - Layer 3 (`gpio.c`) owns driver policy, validation, and register-level batching.
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
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin mode/config image updated successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin, @p mode, or @p config was invalid.
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
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin MODE field updated successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin or @p mode was invalid.
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
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin CNF field updated successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin or @p config was invalid.
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
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin reset image staged successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was invalid.
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
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pull state staged successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pOdrRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin or @p config was invalid.
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
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin mode/config was read successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: Both @p pMode and @p pConfig were null pointers.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx, @p pin, or the raw pin slot state was invalid.
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
