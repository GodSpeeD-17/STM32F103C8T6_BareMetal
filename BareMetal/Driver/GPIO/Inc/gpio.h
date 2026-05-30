/**
 * @file	gpio.h
 * @author	Shrey Shah
 * @brief	GPIO Driver Public Interface
 * @version	v1.3
 * @date	31-03-2026
 *
 * @details
 * This header defines the GPIO driver layer built on top of `gpio_ll.h`.
 *
 * Theory:
 * - Layer 0 owns the raw STM32F1 register model.
 * - Shared GPIO typedef aliases live in `gpio_data_types.h`.
 * - Public GPIO selectors and pure validation macros live in `gpio_defines.h`.
 * - `gpio_ll.h/.c` owns raw register-near access and GPIO register-layout
 *   primitives.
 * - `gpio_codec.h/.c` owns translation and staged register-image mutation.
 * - `gpio.h` / `gpio.c` owns the public GPIO API, validation, orchestration,
 *   and batched register writes.
 */

#ifndef GPIO_H_
#define GPIO_H_

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "gpio_defines.h"
#include "gpio_ll.h"

/**
 * @addtogroup GPIO_03_Driver
 * @{
 */

// ==================================================================================================== //
//                                      GPIO Configuration Descriptor                                   //
// ==================================================================================================== //

/**
 * @brief GPIO configuration descriptor
 * @defgroup GPIO_03_Driver_02_Config Driver GPIO Configuration Descriptor
 * @ingroup  GPIO_03_Driver
 * @{
 */
typedef struct _gpio_config_t
{
	/** @brief Pin selection bitmask */
	gpio_pin_t			pin;
	/** @brief Pin operating mode and speed */
	gpio_pin_mode_t		mode;
	/** @brief Pin electrical configuration */
	gpio_pin_config_t	config;
} gpio_config_t;

/** @} */ // GPIO_03_Driver_02_Config

// ==================================================================================================== //
//                                  Board Defaults Kept For Current Driver                              //
// ==================================================================================================== //

#ifdef STM32F103C8T6__
/** @brief On-board LED GPIO port @def GPIO_OB_LED_PORT */
#define GPIO_OB_LED_PORT						GPIOC
/** @brief On-board LED GPIO pin @def GPIO_OB_LED_PIN */
#define GPIO_OB_LED_PIN							GPIO_PIN_13
#endif /* STM32F103C8T6__ */

/**
 * @brief Default configuration descriptor for the on-board LED
 * @def GPIO_OB_LED_CONFIG
 */
#define GPIO_OB_LED_CONFIG()					\
{												\
	.pin = GPIO_OB_LED_PIN,						\
	.mode = GPIO_PIN_MODE_OUTPUT_2MHZ,			\
	.config = GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL	\
}

/**
 * @brief Sets one or more GPIO output pins
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The selected pin(s) were set.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pin was invalid.
 * @note Atomic operation through `BSRR`.
 */
__STATIC_FORCEINLINE driver_status_t GPIO_PinSet(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	GPIO_LL_SetPin(GPIOx, pin);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Resets one or more GPIO output pins
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The selected pin(s) were reset.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pin was invalid.
 * @note Atomic operation through `BRR`.
 */
__STATIC_FORCEINLINE driver_status_t GPIO_PinReset(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	GPIO_LL_ResetPin(GPIOx, pin);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Toggles one or more GPIO output pins
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The selected pin(s) were toggled.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pin was invalid.
 */
__STATIC_FORCEINLINE driver_status_t GPIO_PinToggle(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	GPIO_LL_TogglePin(GPIOx, pin);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Reads the sampled logic level of a single GPIO input pin
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @returns `0x00U` when the selected pin is low, otherwise `0x01U`
 * @note This API expects a valid GPIO instance and a single-pin mask.
 * @note Returns `0x00U` for an invalid GPIO instance or pin mask.
 */
__STATIC_FORCEINLINE uint8_t GPIO_Get(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PinMaskToIndex(pin) == GPIO_PIN_INDEX_INVALID))
	{
		return (uint8_t) 0x00U;
	}

	return (GPIO_LL_ReadPin(GPIOx, pin) != 0x00000000UL) ? (uint8_t) 0x01U : (uint8_t) 0x00U;
}

/**
 * @brief Sets the On-board (OB) LED
 * @note OB LED is active LOW
 */
__STATIC_FORCEINLINE void OB_LED_Set(void)
{
	GPIO_PinReset(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

/**
 * @brief Resets the On-board (OB) LED
 * @note OB LED is active LOW
 */
__STATIC_FORCEINLINE void OB_LED_Reset(void)
{
	GPIO_PinSet(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

/**
 * @brief Toggles the On-board (OB) LED
 * @note OB LED is active LOW
 */
__STATIC_FORCEINLINE void OB_LED_Toggle(void)
{
	GPIO_PinToggle(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

// ==================================================================================================== //
//                                             GPIO Driver APIs                                          //
// ==================================================================================================== //

/**
 * @brief Configures the mode and electrical behavior of one or more GPIO pins
 * @details
 * Reads each touched GPIO register once, updates staged register images per
 * selected pin, then writes each touched register once.
 *
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO pin mask
 * @param[in] mode Driver GPIO mode selector
 * @param[in] config Driver GPIO configuration selector
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested mode/config pair was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx, @p pin, @p mode, or @p config was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 */
driver_status_t GPIO_SetPinModeConfig(GPIO_TypeDef* const GPIOx, gpio_pin_t pin, const gpio_pin_mode_t mode, const gpio_pin_config_t config);

/**
 * @brief Returns the current driver-facing mode selector for one GPIO pin
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO single-pin mask
 * @returns Current mode as @ref gpio_pin_mode_t
 * @note Expects a valid @p GPIOx and a single-pin @p pin mask.
 * @note Returns @ref GPIO_PIN_MODE_INPUT if the selected pin state cannot be decoded.
 */
gpio_pin_mode_t GPIO_GetPinMode(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin);

/**
 * @brief Configures the mode field of one or more GPIO pins
 * @details
 * Updates the MODE bits in the GPIO port configuration registers (CRL/CRH)
 * for the selected pin(s). Supports configuring multiple pins simultaneously.
 *
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO pin mask
 * @param[in] mode Driver GPIO mode selector
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested mode field was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx, @p pin, or @p mode was invalid.
 *
 * @note
 * - Automatically determines whether CRL or CRH needs to be updated.
 * - Existing configuration bits for unaffected pins remain unchanged.
 * - Use with @ref GPIO_SetPinConfig or @ref GPIO_SetPinModeConfig for complete configuration.
 */
driver_status_t GPIO_SetPinMode(GPIO_TypeDef* const GPIOx, gpio_pin_t pin, const gpio_pin_mode_t mode);

/**
 * @brief Returns the current driver-facing configuration selector for one GPIO pin
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO single-pin mask
 * @returns Current configuration as @ref gpio_pin_config_t
 * @note Expects a valid @p GPIOx and a single-pin @p pin mask.
 * @note Returns @ref GPIO_PIN_CONFIG_INPUT_ANALOG if the selected pin state cannot be decoded.
 */
gpio_pin_config_t GPIO_GetPinConfig(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin);

/**
 * @brief Configures the electrical `CNF` field of one or more GPIO pins
 * @details
 * Updates the CNF[1:0] configuration bits in CRL/CRH for the specified pins,
 * setting input/output type and alternate-function behavior as defined
 * by the driver configuration constants.
 *
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO pin mask
 * @param[in] config Driver GPIO configuration selector
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested configuration field was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx, @p pin, or @p config was invalid.
 *
 * @note
 * - Automatically determines whether CRL or CRH registers are affected.
 * - Use with @ref GPIO_SetPinMode to fully configure a pin.
 * - Safe for multi-pin configuration; unaffected bits are preserved.
 * - This API does not update `ODR` for input pull-up/pull-down selection.
 */
driver_status_t GPIO_SetPinConfig(GPIO_TypeDef* const GPIOx, gpio_pin_t pin, const gpio_pin_config_t config);

/**
 * @brief Initializes a GPIO port/pin set from a configuration descriptor
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pGPIOConfig Pointer to @ref gpio_config_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock enable and pin configuration completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pGPIOConfig was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The descriptor fields or @p GPIOx were invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 */
driver_status_t GPIO_Init(GPIO_TypeDef* const GPIOx, const gpio_config_t* const pGPIOConfig);

/**
 * @brief Restores one or more GPIO pins to their reset configuration
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO pin mask
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The selected pins were restored to reset state.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pin was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 */
driver_status_t GPIO_Deinit(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin);

/**
 * @brief Initializes the board on-board LED GPIO
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The on-board LED GPIO was initialized.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The board LED alias fields were invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 */
driver_status_t OB_LED_Init(void);

/**
 * @brief Fills LED-safe mode/config fields and initializes the selected GPIO
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in,out] pGPIOConfig Pointer to @ref gpio_config_t
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The LED GPIO was initialized.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pGPIOConfig was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or `pGPIOConfig->pin` was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 * @note The caller must populate `pGPIOConfig->pin` before calling.
 */
__STATIC_FORCEINLINE driver_status_t GPIO_LED_Init(GPIO_TypeDef* const GPIOx, gpio_config_t* const pGPIOConfig)
{
	if (pGPIOConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	pGPIOConfig->mode = GPIO_PIN_MODE_OUTPUT_10MHZ;
	pGPIOConfig->config = GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL;

	return GPIO_Init(GPIOx, pGPIOConfig);
}

/**
 * @brief Deinitializes the board on-board LED GPIO
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The on-board LED GPIO was restored to reset state.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The board LED alias fields were invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 */
__STATIC_FORCEINLINE driver_status_t OB_LED_Deinit(void)
{
	return GPIO_Deinit(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

/** @} */ // GPIO_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_H_ */
