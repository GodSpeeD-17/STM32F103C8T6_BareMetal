/**
 * @file	gpio_defines.h
 * @author	Shrey Shah
 * @brief	GPIO Driver Selector and Validation Defines
 * @version	v1.0
 * @date	30-05-2026
 *
 * @details
 * This header owns public GPIO selector macros and pure validation helpers.
 * It does not own GPIO typedef aliases; those live in `gpio_data_types.h`.
 *
 * Keep this file free of direct GPIO register reads/writes. STM32F1 register
 * layout helpers belong in the GPIO LL layer.
 */

#ifndef GPIO_DEFINES_H_
#define GPIO_DEFINES_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx.h"
#include "gpio_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GPIO_03_Driver
 * @{
 */

// ==================================================================================================== //
//												GPIO Pins												//
// ==================================================================================================== //

/**
 * @brief GPIO shared pin bitmasks
 * @defgroup GPIO_03_Driver_02_Defines_01_Pins GPIO Driver Pins
 * @ingroup GPIO_03_Driver
 * @{
 */

/** @brief First valid zero-based GPIO pin index @def GPIO_PIN_INDEX_FIRST */
#define GPIO_PIN_INDEX_FIRST					((gpio_pin_index_t) 0U)
/** @brief Last valid zero-based GPIO pin index @def GPIO_PIN_INDEX_LAST */
#define GPIO_PIN_INDEX_LAST						((gpio_pin_index_t) 15U)
/** @brief Number of GPIO pins available on one GPIO port @def GPIO_PORT_PIN_COUNT */
#define GPIO_PORT_PIN_COUNT						((gpio_pin_index_t) (GPIO_PIN_INDEX_LAST + 1U))
/** @brief Invalid GPIO pin index sentinel @def GPIO_PIN_INDEX_INVALID */
#define GPIO_PIN_INDEX_INVALID					GPIO_PORT_PIN_COUNT
/**
 * @brief Checks if a GPIO pin index is inside the supported GPIO pin-index range
 * @param[in] pinIndex Zero-based GPIO pin index to check
 * @returns Pin-index validity status
 * @retval - `0U`: @p pinIndex is outside `0..15`
 * @retval - Non-zero: @p pinIndex is inside `0..15`
 * @def GPIO_PIN_INDEX_IS_VALID
 */
#define GPIO_PIN_INDEX_IS_VALID(pinIndex)		\
	(((uint32_t) (pinIndex)) <= ((uint32_t) GPIO_PIN_INDEX_LAST))

/**
 * @brief Converts a zero-based GPIO pin index to a single-pin mask
 * @param[in] pinIndex Zero-based GPIO pin index
 * @returns GPIO pin mask generated from @p pinIndex
 * @retval - @ref `GPIO_PIN_0`..@ref `GPIO_PIN_15`: @p pinIndex is in the valid GPIO pin-index range
 * @def GPIO_PIN_INDEX_TO_MASK
 */
#define GPIO_PIN_INDEX_TO_MASK(pinIndex)		((gpio_pin_t) REG_BIT_MASK(pinIndex))
/** @brief Pin 0 bitmask @def GPIO_PIN_0 */
#define GPIO_PIN_0								GPIO_PIN_INDEX_TO_MASK(0U)
/** @brief Pin 1 bitmask @def GPIO_PIN_1 */
#define GPIO_PIN_1								GPIO_PIN_INDEX_TO_MASK(1U)
/** @brief Pin 2 bitmask @def GPIO_PIN_2 */
#define GPIO_PIN_2								GPIO_PIN_INDEX_TO_MASK(2U)
/** @brief Pin 3 bitmask @def GPIO_PIN_3 */
#define GPIO_PIN_3								GPIO_PIN_INDEX_TO_MASK(3U)
/** @brief Pin 4 bitmask @def GPIO_PIN_4 */
#define GPIO_PIN_4								GPIO_PIN_INDEX_TO_MASK(4U)
/** @brief Pin 5 bitmask @def GPIO_PIN_5 */
#define GPIO_PIN_5								GPIO_PIN_INDEX_TO_MASK(5U)
/** @brief Pin 6 bitmask @def GPIO_PIN_6 */
#define GPIO_PIN_6								GPIO_PIN_INDEX_TO_MASK(6U)
/** @brief Pin 7 bitmask @def GPIO_PIN_7 */
#define GPIO_PIN_7								GPIO_PIN_INDEX_TO_MASK(7U)
/** @brief Pin 8 bitmask @def GPIO_PIN_8 */
#define GPIO_PIN_8								GPIO_PIN_INDEX_TO_MASK(8U)
/** @brief Pin 9 bitmask @def GPIO_PIN_9 */
#define GPIO_PIN_9								GPIO_PIN_INDEX_TO_MASK(9U)
/** @brief Pin 10 bitmask @def GPIO_PIN_10 */
#define GPIO_PIN_10								GPIO_PIN_INDEX_TO_MASK(10U)
/** @brief Pin 11 bitmask @def GPIO_PIN_11 */
#define GPIO_PIN_11								GPIO_PIN_INDEX_TO_MASK(11U)
/** @brief Pin 12 bitmask @def GPIO_PIN_12 */
#define GPIO_PIN_12								GPIO_PIN_INDEX_TO_MASK(12U)
/** @brief Pin 13 bitmask @def GPIO_PIN_13 */
#define GPIO_PIN_13								GPIO_PIN_INDEX_TO_MASK(13U)
/** @brief Pin 14 bitmask @def GPIO_PIN_14 */
#define GPIO_PIN_14								GPIO_PIN_INDEX_TO_MASK(14U)
/** @brief Pin 15 bitmask @def GPIO_PIN_15 */
#define GPIO_PIN_15								GPIO_PIN_INDEX_TO_MASK(15U)
/**
 * @brief Bitmask selecting every valid GPIO pin on one GPIO port
 * @def GPIO_PIN_ALL
 */
#define GPIO_PIN_ALL							((gpio_pin_t) 0xFFFFU)
/**
 * @brief No pins bitmask
 * @def GPIO_PIN_NONE
 */
#define GPIO_PIN_NONE							((gpio_pin_t) 0x0000U)

/** @} */ // GPIO_03_Driver_02_Defines_01_Pins

// ==================================================================================================== //
//										GPIO Defines Validation										//
// ==================================================================================================== //

/**
 * @brief Checks whether a GPIO peripheral instance is supported by the driver
 * @param[in]	GPIOx	GPIO peripheral instance
 * @returns Validity status of the input GPIO peripheral instance
 * @retval - `0U`: @p GPIOx is not a supported GPIO peripheral instance
 * @retval - Non-zero: @p GPIOx is a supported GPIO peripheral instance
 * @def GPIO_PORT_IS_VALID
 */
#define GPIO_PORT_IS_VALID(GPIOx)					\
(													\
	((GPIOx) == GPIOA)	|| ((GPIOx) == GPIOB)	||	\
	((GPIOx) == GPIOC)	|| ((GPIOx) == GPIOD)	||	\
	((GPIOx) == GPIOE)	|| ((GPIOx) == GPIOF)	||	\
	((GPIOx) == GPIOG)								\
)

/**
 * @brief Checks if a GPIO pin mask selects at least one pin
 * @param[in]	pinMask	GPIO pin mask to check
 * @returns Pin-selection presence status of the input GPIO pin mask
 * @retval - `0U`: @p pinMask does not select any GPIO pin
 * @retval - Non-zero: @p pinMask selects at least one GPIO pin
 * @def GPIO_PIN_MASK_HAS_ANY_PIN
 */
#define GPIO_PIN_MASK_HAS_ANY_PIN(pinMask)			\
	(((gpio_pin_t) (pinMask)) != GPIO_PIN_NONE)

/**
 * @brief Checks if a GPIO pin mask contains only supported GPIO pin bits
 * @param[in]	pinMask	GPIO pin mask to check
 * @returns Supported-range status of the input GPIO pin mask
 * @retval - `0U`: @p pinMask contains one or more bits outside @ref `GPIO_PIN_ALL`
 * @retval - Non-zero: @p pinMask contains only bits inside @ref `GPIO_PIN_ALL`
 * @def GPIO_PIN_MASK_HAS_ONLY_VALID_PINS
 */
#define GPIO_PIN_MASK_HAS_ONLY_VALID_PINS(pinMask)	\
	((((uint32_t) (pinMask)) & (~((uint32_t) GPIO_PIN_ALL))) ==	0x00000000UL)

/**
 * @brief Checks if a GPIO pin mask is valid
 * @param[in]	pinMask	GPIO pin mask to check
 * @returns Validity status of the input GPIO pin mask
 * @retval - `0U`: @p pinMask is empty or contains bits outside the supported GPIO pin range
 * @retval - Non-zero: @p pinMask selects one or more supported GPIO pins
 * @def GPIO_PIN_MASK_IS_VALID
 */
#define GPIO_PIN_MASK_IS_VALID(pinMask)				\
	(GPIO_PIN_MASK_HAS_ANY_PIN(pinMask) && GPIO_PIN_MASK_HAS_ONLY_VALID_PINS(pinMask))

/**
 * @brief Checks if a GPIO pin mask has zero or one bit set
 * @param[in]	pinMask	GPIO pin mask to check
 * @returns At-most-one-bit status of the input GPIO pin mask
 * @retval - `0U`: @p pinMask contains multiple set bits
 * @retval - Non-zero: @p pinMask is zero or contains exactly one set bit
 * @def GPIO_PIN_MASK_HAS_AT_MOST_ONE_BIT
 */
#define GPIO_PIN_MASK_HAS_AT_MOST_ONE_BIT(pinMask)	\
	((((uint32_t) (pinMask)) & (((uint32_t) (pinMask)) - 1UL)) == 0x00000000UL)

/**
 * @brief Returns the pin index for a single-pin mask
 * @param[in]	pinMask	GPIO single-pin mask
 * @returns GPIO pin index decoded from @p pinMask
 * @retval - `0U..15U`: Valid GPIO pin index
 * @retval - @ref `GPIO_PIN_INDEX_INVALID`: Invalid, empty, or multi-pin mask
 */
__STATIC_FORCEINLINE gpio_pin_index_t GPIO_PinMaskToIndex(const gpio_pin_t pinMask)
{
	// Local Variables
	gpio_pin_t pinMaskImage = pinMask;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_FIRST;

	//! Validate that the input pin mask is a single valid pin selection
	if ((GPIO_PIN_MASK_IS_VALID(pinMask) == 0U) || (GPIO_PIN_MASK_HAS_AT_MOST_ONE_BIT(pinMask) == 0U))
	{
		return GPIO_PIN_INDEX_INVALID;
	}

	//! Shift the single selected bit down to bit 0 while counting the bit position
	while (pinMaskImage > GPIO_PIN_0)
	{
		pinMaskImage = (gpio_pin_t) (((uint32_t) pinMaskImage) >> 1U);
		++pinIndex;
	}

	return pinIndex;
}

// ==================================================================================================== //
//											GPIO Pin Mode Types											//
// ==================================================================================================== //

/** @brief Input mode @def GPIO_PIN_MODE_INPUT */
#define GPIO_PIN_MODE_INPUT								((gpio_pin_mode_t) 0x00U)
/** @brief Output mode, max speed 10 MHz @def GPIO_PIN_MODE_OUTPUT_10MHZ */
#define GPIO_PIN_MODE_OUTPUT_10MHZ						((gpio_pin_mode_t) 0x01U)
/** @brief Output mode, max speed 2 MHz @def GPIO_PIN_MODE_OUTPUT_2MHZ */
#define GPIO_PIN_MODE_OUTPUT_2MHZ						((gpio_pin_mode_t) 0x02U)
/** @brief Output mode, max speed 50 MHz @def GPIO_PIN_MODE_OUTPUT_50MHZ */
#define GPIO_PIN_MODE_OUTPUT_50MHZ						((gpio_pin_mode_t) 0x03U)

/**
 * @brief Checks if a GPIO pin mode is valid
 * @param[in]	mode	GPIO pin mode selector to check
 * @returns Validity status of the input GPIO pin mode selector
 * @retval - `0U`: @p mode is not a supported GPIO pin mode selector
 * @retval - Non-zero: @p mode is a supported GPIO pin mode selector
 * @def GPIO_PIN_MODE_IS_VALID
 */
#define GPIO_PIN_MODE_IS_VALID(mode)							\
(																\
	((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_INPUT ||		\
	((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_10MHZ ||	\
	((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_2MHZ ||	\
	((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_50MHZ	\
)

// ==================================================================================================== //
//										GPIO Pin Configuration Types									//
// ==================================================================================================== //
/** @brief Analog input mode @def GPIO_PIN_CONFIG_INPUT_ANALOG */
#define GPIO_PIN_CONFIG_INPUT_ANALOG					((gpio_pin_config_t) 0x00U)
/** @brief Floating input (no pull-up/down) @def GPIO_PIN_CONFIG_INPUT_FLOATING */
#define GPIO_PIN_CONFIG_INPUT_FLOATING					((gpio_pin_config_t) 0x01U)
/** @brief Input with pull-down resistor @def GPIO_PIN_CONFIG_INPUT_PULL_DOWN */
#define GPIO_PIN_CONFIG_INPUT_PULL_DOWN					((gpio_pin_config_t) 0x02U)
/** @brief Input with pull-up resistor @def GPIO_PIN_CONFIG_INPUT_PULL_UP */
#define GPIO_PIN_CONFIG_INPUT_PULL_UP					((gpio_pin_config_t) 0x12U)
/** @brief General purpose output push-pull @def GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL */
#define GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL				((gpio_pin_config_t) 0x03U)
/** @brief General purpose output open-drain @def GPIO_PIN_CONFIG_OUTPUT_OPEN_DRAIN */
#define GPIO_PIN_CONFIG_OUTPUT_OPEN_DRAIN				((gpio_pin_config_t) 0x04U)
/** @brief Alternate function output push-pull @def GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL */
#define GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL				((gpio_pin_config_t) 0x05U)
/** @brief Alternate function output open-drain @def GPIO_PIN_CONFIG_ALTERNATE_OPEN_DRAIN */
#define GPIO_PIN_CONFIG_ALTERNATE_OPEN_DRAIN			((gpio_pin_config_t) 0x06U)

/**
 * @brief Validates a GPIO pin configuration value
 * @param[in]	config	GPIO pin configuration selector to check
 * @returns Validity status of the input GPIO pin configuration selector
 * @retval - `0U`: @p config is not a supported GPIO pin configuration selector
 * @retval - Non-zero: @p config is a supported GPIO pin configuration selector
 * @def GPIO_PIN_CONFIG_IS_VALID
 */
#define GPIO_PIN_CONFIG_IS_VALID(config)										\
(																				\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_INPUT_ANALOG) ||			\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_INPUT_FLOATING) ||		\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_INPUT_PULL_DOWN) ||		\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_INPUT_PULL_UP) ||		\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL) ||		\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_OUTPUT_OPEN_DRAIN) ||	\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL) ||	\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_ALTERNATE_OPEN_DRAIN)	\
)

/**
 * @brief Checks if a GPIO configuration uses alternate-function output mode
 * @param[in]	config	GPIO pin configuration selector to check
 * @returns Alternate-function usage status of the input GPIO pin configuration selector
 * @retval - `0U`: @p config does not select alternate-function output
 * @retval - Non-zero: @p config selects alternate-function output
 * @def GPIO_PIN_CONFIG_IS_ALTERNATE
 */
#define GPIO_PIN_CONFIG_IS_ALTERNATE(config)									\
(																				\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL) ||	\
	(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_ALTERNATE_OPEN_DRAIN)	\
)

/**
 * @brief Checks whether a driver mode/config pair selects input pull-up or pull-down
 * @param[in]	mode	Driver GPIO mode selector
 * @param[in]	config	Driver GPIO configuration selector
 * @returns Input pull configuration status of the input GPIO mode/config pair
 * @retval - `0U`: @p mode and @p config do not select input pull-up/down
 * @retval - Non-zero: @p mode and @p config select input pull-up/down
 * @def GPIO_PIN_MODE_CONFIG_IS_INPUT_PULL
 */
#define GPIO_PIN_MODE_CONFIG_IS_INPUT_PULL(mode, config)						\
(																				\
	(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_INPUT) &&						\
	(																			\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_INPUT_PULL_DOWN) ||	\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_INPUT_PULL_UP)		\
	)																			\
)

/**
 * @brief Validates GPIO mode and configuration compatibility
 * @param[in]	mode	Driver GPIO mode selector
 * @param[in]	config	Driver GPIO configuration selector
 * @returns Compatibility status of the input GPIO mode/config pair
 * @retval - `0U`: @p mode and @p config are not compatible
 * @retval - Non-zero: @p mode and @p config are compatible
 * @def GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR
 */
#define GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, config)								\
(																						\
	(																					\
		(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_INPUT) &&							\
		(																				\
			(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_INPUT_ANALOG) ||			\
			(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_INPUT_FLOATING) ||		\
			(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_INPUT_PULL_DOWN) ||		\
			(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_INPUT_PULL_UP)			\
		)																				\
	)																					\
										||												\
	(																					\
		(																				\
			(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_10MHZ) ||				\
			(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_2MHZ) ||				\
			(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_50MHZ)					\
		)																				\
											&&											\
		(																				\
			(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL) ||		\
			(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_OUTPUT_OPEN_DRAIN) ||	\
			(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL) ||	\
			(((gpio_pin_config_t) (config)) == GPIO_PIN_CONFIG_ALTERNATE_OPEN_DRAIN)	\
		)																				\
	)																					\
)

/** @} */ // GPIO_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_DEFINES_H_ */
