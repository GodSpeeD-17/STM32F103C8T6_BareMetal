/**
 * @file	gpio.h
 * @author	Shrey Shah
 * @brief	GPIO Driver Public Interface
 * @version	v1.3
 * @date	31-03-2026
 *
 * @details
 * This header defines the GPIO driver layer built on top of `gpio_ll.h` and
 * `gpio_helper.h`.
 *
 * Theory:
 * - Layer 0 owns the raw STM32F1 register model and shared GPIO scalar types.
 * - Layer 1 (`gpio_ll.h`) owns thin register-near access primitives.
 * - Layer 2 (`gpio_helper.h` / `gpio_helper.c`) bridges driver selectors to
 *   staged raw register images.
 * - Layer 3 (`gpio.h` / `gpio.c`) owns the public GPIO API, validation,
 *   orchestration, and batched register writes.
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

#include "gpio_ll.h"

/**
 * @addtogroup GPIO_03_Driver
 * @{
 */

// ==================================================================================================== //
//                                         GPIO Driver Data Types                                       //
// ==================================================================================================== //

/**
 * @brief GPIO Driver Types
 * @defgroup GPIO_03_Driver_01_Types GPIO Driver Data Types
 * @ingroup GPIO_03_Driver
 *
 * @{
 */

/**
 * @brief Checks whether a GPIO peripheral instance is supported by the driver
 * @param[in] GPIOx GPIO peripheral instance
 * @returns Non-zero if valid, otherwise `0`
 * @def GPIO_IS_PORT
 */
#define GPIO_IS_PORT(GPIOx)	\
(									\
	((GPIOx) == GPIOA) ||			\
	((GPIOx) == GPIOB) || \
	((GPIOx) == GPIOC) || \
	((GPIOx) == GPIOD) || \
	((GPIOx) == GPIOE) || \
	((GPIOx) == GPIOF) || \
	((GPIOx) == GPIOG) \
)

/**
 * @brief Checks if a GPIO pin mask is valid
 * @param[in] pin @ref GPIO_Driver_Pin_Macros "GPIO Pin Mask" to check
 * @returns Non-zero if valid, otherwise `0`
 * @note Multiple pins can be ORed together, e.g., (GPIO_PIN_0 | GPIO_PIN_3)
 * @def GPIO_IS_PIN
 */
#define GPIO_IS_PIN(pin)												\
(																			\
	(((uint32_t) (pin)) != (uint32_t) GPIO_PIN_NONE) &&						\
	((((uint32_t) (pin)) & (~((uint32_t) GPIO_PIN_ALL))) == 0x00000000UL)	\
)

/**
 * @brief Checks if any of the pins require CRL register configuration
 * @param[in] pin @ref GPIO_Driver_Pin_Macros "GPIO Pin Mask" to check
 * @returns Non-zero if any pins 0-7 are selected
 * @def GPIO_PIN_REQUIRES_CRL
 */
#define GPIO_PIN_REQUIRES_CRL(pin) \
	(((gpio_pin_t) (pin)) & (gpio_pin_t) 0x00FFU)

/**
 * @brief Checks if any of the pins require CRH register configuration
 * @param[in] pin @ref GPIO_Driver_Pin_Macros "GPIO Pin Mask" to check
 * @returns Non-zero if any pins 8-15 are selected
 * @def GPIO_PIN_REQUIRES_CRH
 */
#define GPIO_PIN_REQUIRES_CRH(pin) \
	(((gpio_pin_t) (pin)) & (gpio_pin_t) 0xFF00U)

/**
 * @brief Returns the pin index for a single-pin mask
 * @param[in] pin GPIO single-pin mask
 * @returns Pin index in the range `0..15`, or `0x10U` when @p pin is invalid
 */
__STATIC_FORCEINLINE uint8_t _GPIO_GetPinIndexFromMask(const gpio_pin_t pin)
{
	uint8_t pinIndex = 0x00U;
	gpio_pin_t currentPin = GPIO_PIN_0;

	while (currentPin != GPIO_PIN_NONE)
	{
		if (pin == currentPin)
		{
			return pinIndex;
		}
		currentPin = (gpio_pin_t)(currentPin << 1U);
		++pinIndex;
	}

	return (uint8_t) 0x10U;
}

// ==================================================================================================== //
//                                           GPIO Pin Mode Types                                        //
// ==================================================================================================== //
/**
 * @brief    Driver GPIO pin mode selectors
 * @defgroup GPIO_03_Driver_01_Types_03_PinModes Driver GPIO Pin Modes
 * @ingroup  GPIO_03_Driver_01_Types
 * @details
 * - The constants define the operational mode (MODE[1:0] bits) of GPIO pins.
 * - The mode determines whether the pin is input/output and the output speed.
 * @note Output speed affects both slew rate and power consumption.
 * @see Reference Manual RM0008 - Section 9.1.1 GPIO port configuration
 * @{
 */

/**
 * @section GPIO_Driver_PinMode_Macros GPIO Driver Pin Mode Macros 
 * @details GPIO Driver Pin Mode Macros 
 * @{
 */
/** @brief Input mode @def GPIO_PIN_MODE_INPUT */
#define GPIO_PIN_MODE_INPUT								((gpio_pin_mode_t) 0x00U)
/** @brief Output mode, max speed 10 MHz @def GPIO_PIN_MODE_OUTPUT_10MHz */
#define GPIO_PIN_MODE_OUTPUT_10MHz						((gpio_pin_mode_t) 0x01U)
/** @brief Output mode, max speed 2 MHz @def GPIO_PIN_MODE_OUTPUT_2MHz */
#define GPIO_PIN_MODE_OUTPUT_2MHz						((gpio_pin_mode_t) 0x02U)
/** @brief Output mode, max speed 50 MHz @def GPIO_PIN_MODE_OUTPUT_50MHz */
#define GPIO_PIN_MODE_OUTPUT_50MHz						((gpio_pin_mode_t) 0x03U)

/** @} */ // GPIO_Driver_PinMode_Macros

/**
 * @brief Checks if a GPIO pin mode is valid
 * @param[in] mode The GPIO pin mode to check
 * @returns Non-zero if valid, otherwise `0`
 * @def GPIO_PIN_IS_MODE
 */
#define GPIO_PIN_IS_MODE(mode)									\
(																\
    ((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_INPUT ||		\
    ((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_10MHz ||	\
    ((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_2MHz ||	\
    ((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_50MHz	\
)

/** @} */ // GPIO_03_Driver_01_Types_03_PinModes

// ==================================================================================================== //
//                                       GPIO Pin Configuration Types                                   //
// ==================================================================================================== //
/**
 * @brief    Driver GPIO pin configuration selectors
 * @defgroup GPIO_03_Driver_01_Types_04_PinConfig Driver GPIO Pin Configurations
 * @ingroup  GPIO_03_Driver_01_Types
 * @details
 * - The constants define the electrical configuration (CNF[1:0] bits) of GPIO pins.
 * - The configuration must be compatible with the selected mode.
 * @warning Configuration must match mode:
 * - Input modes (MODE=00): Use `GPIO_PIN_CNF_IN_*`
 * - Output modes (MODE>00): Use `GPIO_PIN_CNF_OUT_*`
 * @see Reference Manual RM0008 - Section 9.1.1 GPIO port configuration
 * @{
 */

/**
 * @section GPIO_Driver_PinConfiguration_Macros GPIO Driver Pin Configuration Macros
 * @details GPIO Driver Pin Configuration Macros
 * @{
 */
/** @brief Analog input mode @def GPIO_PIN_CNF_IN_ANALOG */
#define GPIO_PIN_CNF_IN_ANALOG							((gpio_pin_config_t) 0x00)
/** @brief Floating input (no pull-up/down) @def GPIO_PIN_CNF_IN_FLOAT */
#define GPIO_PIN_CNF_IN_FLOAT							((gpio_pin_config_t) 0x01)
/**
 * @brief Input with pull-down resistor
 * @details Requires the corresponding bit in ODR to be set to 0
 * @def GPIO_PIN_CNF_IN_PULL_DOWN
 */
#define GPIO_PIN_CNF_IN_PULL_DOWN						((gpio_pin_config_t) 0x02)
/**
 * @brief Input with pull-up resistor
 * @details Requires the corresponding bit in ODR to be set to 1
 * @def GPIO_PIN_CNF_IN_PULL_UP
 */
#define GPIO_PIN_CNF_IN_PULL_UP							((gpio_pin_config_t) 0x12)
/** @brief General purpose output push-pull @def GPIO_PIN_CNF_OUT_GP_PP */
#define GPIO_PIN_CNF_OUT_GP_PP							((gpio_pin_config_t) 0x03)
/** @brief General purpose output open-drain @def GPIO_PIN_CNF_OUT_GP_OD */
#define GPIO_PIN_CNF_OUT_GP_OD							((gpio_pin_config_t) 0x04)
/** @brief Alternate function output push-pull @def GPIO_PIN_CNF_OUT_AF_PP */
#define GPIO_PIN_CNF_OUT_AF_PP							((gpio_pin_config_t) 0x05)
/** @brief Alternate function output open-drain @def GPIO_PIN_CNF_OUT_AF_OD */
#define GPIO_PIN_CNF_OUT_AF_OD							((gpio_pin_config_t) 0x06)

/** @}  */ // GPIO_Driver_PinConfiguration_Macros

/**
 * @brief Validates a GPIO pin configuration value
 * @param[in] config The configuration to validate
 * @returns Non-zero if valid, otherwise `0`
 * @note This validation macro only checks for defined constants. It does not
 *       verify mode-to-configuration compatibility (handled at runtime)
 * @def GPIO_PIN_IS_CONFIG
 */
#define GPIO_PIN_IS_CONFIG(config)										\
(																		\
    (((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_ANALOG)     ||	\
    (((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_FLOAT)      ||	\
    (((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_PULL_DOWN)  ||	\
    (((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_PULL_UP)    ||	\
    (((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_GP_PP)     ||	\
    (((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_GP_OD)     ||	\
    (((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_AF_PP)     ||	\
    (((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_AF_OD)			\
)

/**
 * @brief Checks if a GPIO configuration uses Alternate Function (AF) mode
 * @param[in] config GPIO pin configuration value of type @ref gpio_pin_config_t
 * @returns Non-zero if the configuration selects alternate function output, otherwise `0`
 * @note According to STM32F1 reference manual (RM0008, Table 20),
 *       Alternate Function configurations are:
 *       - @ref GPIO_PIN_CNF_OUT_AF_PP  → AF Push-Pull  
 *       - @ref GPIO_PIN_CNF_OUT_AF_OD  → AF Open-Drain
 * @def GPIO_PIN_IS_AF_CONFIG
 */
#define GPIO_PIN_IS_AF_CONFIG(config)									\
(																		\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_AF_PP) ||		\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_AF_OD)			\
)

/**
 * @brief Checks whether a driver mode/config pair selects input pull-up or pull-down
 * @def GPIO_PIN_IS_PULL_CONFIG
 * @param[in] mode Driver GPIO mode selector
 * @param[in] config Driver GPIO configuration selector
 * @returns Non-zero when the pair selects input pull-up or pull-down
 */
#define GPIO_PIN_IS_PULL_CONFIG(mode, config)							\
(																		\
	(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_INPUT) &&				\
	((((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_PULL_DOWN) ||	\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_PULL_UP))		\
)

/**
 * @brief Validates GPIO mode and configuration compatibility
 * @param[in] mode The GPIO pin mode (of type gpio_pin_mode_t)
 * @param[in] config  The GPIO pin configuration (of type gpio_pin_config_t)
 * @returns Non-zero if the combination is valid, otherwise `0`
 * @note According to STM32F1 reference manual (RM0008, Table 20):
 * - When MODE = 0b00 (Input), CNF must be one of the `GPIO_PIN_CNF_IN_*` values.
 * - When MODE > 0b00 (Output/AF), CNF must be one of the `GPIO_PIN_CNF_OUT_*` values.
 * @def GPIO_PIN_IS_MODE_CONFIG_COMPATIBLE
 */
#define GPIO_PIN_IS_MODE_CONFIG_COMPATIBLE(mode, config)					\
(																			\
	((((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_INPUT) &&					\
	(																		\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_ANALOG)     ||	\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_FLOAT)      ||	\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_PULL_DOWN)  ||	\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_PULL_UP)			\
	))																		\
									||										\
	(((((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_10MHz) ||			\
	(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_2MHz)  ||			\
	(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_50MHz)) &&			\
	(																		\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_GP_PP)     ||	\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_GP_OD)     ||	\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_AF_PP)     ||	\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_AF_OD)			\
	))																		\
)

/** @} */ // GPIO_03_Driver_01_Types_04_PinConfig

/** @} */ // GPIO_03_Driver_01_Types

/**
 * @brief GPIO configuration descriptor
 * @defgroup GPIO_03_Driver_02_Config Driver GPIO Configuration Descriptor
 * @ingroup  GPIO_03_Driver
 * 
 * @{
 */
typedef struct _gpio_config_t
{

	/**
	 * @brief Pin selection bitmask
	 *
	 * @details
	 * - @ref `GPIO_PIN_0`: Pin 0
	 * - @ref `GPIO_PIN_1`: Pin 1
	 * ...
	 * - @ref `GPIO_PIN_15`: Pin 15
	 * - @ref `GPIO_PIN_ALL`: All pins
	 * - @ref `GPIO_PIN_NONE`: No pins
	 *
	 * @see @ref GPIO_03_Driver_01_Types_02_Pins "GPIO Pins"
	 */
	gpio_pin_t pin;

	/**
	 * @brief Pin operating mode and speed
	 *
	 * @details
	 * @ref `GPIO_PIN_MODE_INPUT`: Input mode
	 * @ref `GPIO_PIN_MODE_OUTPUT_10MHz`: Output 10MHz
	 * @ref `GPIO_PIN_MODE_OUTPUT_2MHz`: Output 2MHz
	 * @ref `GPIO_PIN_MODE_OUTPUT_50MHz`: Output 50MHz
	 *
	 * @see @ref GPIO_03_Driver_01_Types_03_PinModes "GPIO Pin Modes"
	 */
	gpio_pin_mode_t mode;

	/**
	 * @brief Pin electrical configuration
	 *
	 * @details
	 * @ref `GPIO_PIN_MODE_INPUT` "Input Modes:"
	 * @ref `GPIO_PIN_CNF_IN_ANALOG`: Analog input
	 * @ref `GPIO_PIN_CNF_IN_FLOAT`: Floating input
	 * @ref `GPIO_PIN_CNF_IN_PULL_DOWN`: Input with pull-down
	 * @ref `GPIO_PIN_CNF_IN_PULL_UP`: Input with pull-up
	 *
	 * @ref `GPIO_PIN_MODE_OUTPUT_10MHz` "Output Modes:"
	 * @ref `GPIO_PIN_CNF_OUT_GP_PP`: General purpose push-pull
	 * @ref `GPIO_PIN_CNF_OUT_GP_OD`: General purpose open-drain
	 * @ref `GPIO_PIN_CNF_OUT_AF_PP`: Alternate function push-pull
	 * @ref `GPIO_PIN_CNF_OUT_AF_OD`: Alternate function open-drain
	 *
	 * @warning Must be compatible with mode field
	 *
	 * @see @ref GPIO_03_Driver_01_Types_04_PinConfig "GPIO Pin Configuration"
	 */
	gpio_pin_config_t config;

} gpio_config_t;

/** @} */ // GPIO_03_Driver_02_Config

/**
 * @brief Default configuration descriptor for the on-board LED
 * @def GPIO_OB_LED_CONFIG
 */
#define GPIO_OB_LED_CONFIG()				\
{											\
	.pin = GPIO_OB_LED_PIN,					\
	.mode = GPIO_PIN_MODE_OUTPUT_2MHz,		\
	.config = GPIO_PIN_CNF_OUT_GP_PP		\
}

/** @} */ // GPIO_03_Driver

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
	if ((GPIO_IS_PORT(GPIOx) == 0x00U) || (GPIO_IS_PIN(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	GPIO_LL_WRITE_REG(GPIOx, BSRR, (uint32_t) pin);
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
	if ((GPIO_IS_PORT(GPIOx) == 0x00U) || (GPIO_IS_PIN(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	GPIO_LL_WRITE_REG(GPIOx, BRR, (uint32_t) pin);
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
	if ((GPIO_IS_PORT(GPIOx) == 0x00U) || (GPIO_IS_PIN(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	GPIO_LL_TOGGLE_BITS(GPIOx, ODR, (uint32_t) pin);
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
	uint32_t reg = 0x00UL;
	const uint8_t pinIndex = _GPIO_GetPinIndexFromMask(pin);

	if ((GPIO_IS_PORT(GPIOx) == 0x00U) || (pinIndex == (uint8_t) 0x10U))
	{
		return (uint8_t) 0x00U;
	}
	GPIO_LL_READ_REG(GPIOx, IDR, reg);
	reg = (reg & ((uint32_t) pin)) >> pinIndex;
	return ((uint8_t) reg);
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
 * @note Returns @ref GPIO_PIN_CNF_IN_ANALOG if the selected pin state cannot be decoded.
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

	pGPIOConfig->mode = GPIO_PIN_MODE_OUTPUT_10MHz;
	pGPIOConfig->config = GPIO_PIN_CNF_OUT_GP_PP;

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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_H_ */
