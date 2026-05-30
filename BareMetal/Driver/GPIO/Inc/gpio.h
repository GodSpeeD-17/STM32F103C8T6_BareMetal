/**
 * @file	gpio.h
 * @author	Shrey Shah
 * @brief	GPIO Driver Public Interface
 * @version	v1.4
 * @date	30-05-2026
 *
 * @details
 * This header exposes the public GPIO driver API. Public code sees GPIO
 * selectors, validation macros, and driver entry points. Low-level register
 * access and codec image staging remain private to `gpio.c`.
 */

#ifndef GPIO_H_
#define GPIO_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "gpio_defines.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GPIO_03_Driver
 * @{
 */

// ==================================================================================================== //
//										GPIO Configuration Descriptor									//
// ==================================================================================================== //

/**
 * @brief GPIO configuration descriptor
 * @defgroup GPIO_03_Driver_02_Config Driver GPIO Configuration Descriptor
 * @ingroup GPIO_03_Driver
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
//									Board Defaults Kept For Current Projects							//
// ==================================================================================================== //

#ifdef STM32F103C8T6__
/** @brief On-board LED GPIO port @def GPIO_OB_LED_PORT */
#define GPIO_OB_LED_PORT						GPIOC
/** @brief On-board LED GPIO pin @def GPIO_OB_LED_PIN */
#define GPIO_OB_LED_PIN							GPIO_PIN_13

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
#endif /* STM32F103C8T6__ */

// ==================================================================================================== //
//											GPIO Driver APIs											//
// ==================================================================================================== //

/**
 * @brief Configures the mode and electrical behavior of one or more GPIO pins
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO pin mask
 * @param[in] mode Driver GPIO mode selector
 * @param[in] config Driver GPIO configuration selector
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested mode/config pair was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx, @p pin, @p mode, or @p config was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 */
driver_status_t GPIO_SetPinModeConfig
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pin,
	const gpio_pin_mode_t		mode,
	const gpio_pin_config_t		config
);

/**
 * @brief Configures the mode field of one or more GPIO pins
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO pin mask
 * @param[in] mode Driver GPIO mode selector
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested mode field was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx, @p pin, or @p mode was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Existing pin state could not be decoded or staged.
 * @note Use @ref `GPIO_SetPinModeConfig` when changing mode and config together.
 */
driver_status_t GPIO_SetPinMode
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pin,
	const gpio_pin_mode_t		mode
);

/**
 * @brief Configures the electrical configuration field of one or more GPIO pins
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO pin mask
 * @param[in] config Driver GPIO configuration selector
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested configuration field was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx, @p pin, or @p config was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Existing pin state could not be decoded or staged.
 */
driver_status_t GPIO_SetPinConfig
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pin,
	const gpio_pin_config_t		config
);

/**
 * @brief Returns the current driver-facing mode selector for one GPIO pin
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO single-pin mask
 * @returns Current mode as @ref gpio_pin_mode_t
 * @note Returns @ref `GPIO_PIN_MODE_INPUT` if validation or decode fails.
 */
gpio_pin_mode_t GPIO_GetPinMode(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin);

/**
 * @brief Returns the current driver-facing configuration selector for one GPIO pin
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO single-pin mask
 * @returns Current configuration as @ref gpio_pin_config_t
 * @note Returns @ref `GPIO_PIN_CONFIG_INPUT_ANALOG` if validation or decode fails.
 */
gpio_pin_config_t GPIO_GetPinConfig(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin);

/**
 * @brief Initializes a GPIO port/pin set from a configuration descriptor
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pGPIOConfig Pointer to @ref gpio_config_t
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock enable and pin configuration completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pGPIOConfig was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The descriptor fields or @p GPIOx were invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 */
driver_status_t GPIO_Init(GPIO_TypeDef* const GPIOx, const gpio_config_t* const pGPIOConfig);

/**
 * @brief Restores one or more GPIO pins to floating-input configuration
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO pin mask
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The selected pins were restored.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pin was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 * @note This API restores the CRL/CRH configuration and does not force ODR latch state.
 */
driver_status_t GPIO_Deinit(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin);

/**
 * @brief Sets one or more GPIO output latch bits
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO pin mask
 * @returns Driver operation status
 */
driver_status_t GPIO_PinSet(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin);

/**
 * @brief Resets one or more GPIO output latch bits
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO pin mask
 * @returns Driver operation status
 */
driver_status_t GPIO_PinReset(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin);

/**
 * @brief Toggles one or more GPIO output latch bits
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO pin mask
 * @returns Driver operation status
 */
driver_status_t GPIO_PinToggle(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin);

/**
 * @brief Reads the sampled logic level of one GPIO input pin
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO single-pin mask
 * @returns `0x00U` when low or invalid, otherwise `0x01U`
 */
uint8_t GPIO_Get(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin);

/**
 * @brief Fills LED-safe mode/config fields and initializes the selected GPIO
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in,out] pGPIOConfig Pointer to @ref gpio_config_t
 * @returns Driver operation status
 */
driver_status_t GPIO_LED_Init(GPIO_TypeDef* const GPIOx, gpio_config_t* const pGPIOConfig);

#ifdef STM32F103C8T6__
/**
 * @brief Initializes the board on-board LED GPIO
 * @returns Driver operation status
 */
driver_status_t OB_LED_Init(void);

/** @brief Sets the active-low board on-board LED */
void OB_LED_Set(void);

/** @brief Resets the active-low board on-board LED */
void OB_LED_Reset(void);

/** @brief Toggles the active-low board on-board LED */
void OB_LED_Toggle(void);

/**
 * @brief Deinitializes the board on-board LED GPIO
 * @returns Driver operation status
 */
driver_status_t OB_LED_Deinit(void);
#endif /* STM32F103C8T6__ */

/** @} */ // GPIO_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_H_ */
