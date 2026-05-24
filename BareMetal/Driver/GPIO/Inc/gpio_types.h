/**
 * @file	gpio_types.h
 * @author	Shrey Shah
 * @brief	GPIO Driver Shared Types and Selectors
 * @version	v1.0
 * @date	24-05-2026
 *
 * @details
 * This header owns GPIO driver-facing scalar aliases, public selector values,
 * validation helpers, and lightweight configuration descriptors.
 *
 * Keep this file independent of GPIO register access. It is shared by the
 * public driver layer, internal helper layer, and peripheral drivers that need
 * GPIO selector vocabulary.
 */

#ifndef GPIO_TYPES_H_
#define GPIO_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //
#include "stm32f1xx_utils.h"
#include "stm32f1xx.h"

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
 * @{
 */

/** @brief GPIO pin bit-mask type @typedef gpio_pin_t */
typedef uint16_t								gpio_pin_t;
/** @brief GPIO pin mode selector type @typedef gpio_pin_mode_t */
typedef uint8_t									gpio_pin_mode_t;
/** @brief GPIO pin configuration selector type @typedef gpio_pin_config_t */
typedef uint8_t									gpio_pin_config_t;
/** @brief Raw GPIO MODE field type @typedef gpio_mode_t */
typedef uint8_t									gpio_mode_t;
/** @brief Raw GPIO output speed field type @typedef gpio_speed_t */
typedef uint8_t									gpio_speed_t;
/** @brief Raw GPIO CNF field type @typedef gpio_cnf_t */
typedef uint8_t									gpio_cnf_t;
/** @brief Raw GPIO pull direction bit type @typedef gpio_pull_t */
typedef uint8_t									gpio_pull_t;
/** @brief Raw packed GPIO pin configuration field type @typedef gpio_pin_config_bits_t */
typedef uint8_t									gpio_pin_config_bits_t;
/** @brief GPIO EXTI trigger selector type @typedef gpio_exti_trigger_t */
typedef uint8_t									gpio_exti_trigger_t;
/** @brief GPIO EXTI port source selector type @typedef gpio_exti_port_t */
typedef uint8_t									gpio_exti_port_t;

// ==================================================================================================== //
//                                               GPIO Pins                                              //
// ==================================================================================================== //

/**
 * @brief GPIO shared pin bitmasks
 * @defgroup GPIO_03_Driver_01_Types_02_Pins GPIO Driver Pins
 * @ingroup GPIO_03_Driver_01_Types
 * @{
 */

/** @brief First valid zero-based GPIO pin index @def GPIO_PIN_INDEX_FIRST */
#define GPIO_PIN_INDEX_FIRST					((uint8_t) 0U)
/** @brief Last valid zero-based GPIO pin index @def GPIO_PIN_INDEX_LAST */
#define GPIO_PIN_INDEX_LAST						((uint8_t) 15U)
/** @brief Number of GPIO pins available on one GPIO port @def GPIO_PORT_PIN_COUNT */
#define GPIO_PORT_PIN_COUNT						((uint8_t) (GPIO_PIN_INDEX_LAST + 1U))
/** @brief Invalid GPIO pin index sentinel @def GPIO_PIN_INDEX_INVALID */
#define GPIO_PIN_INDEX_INVALID					GPIO_PORT_PIN_COUNT

/**
 * @brief Converts a zero-based GPIO pin index to a single-pin mask
 * @param[in] pinIndex Zero-based GPIO pin index
 * @returns GPIO pin mask generated from @p pinIndex
 * @retval - @ref `GPIO_PIN_0`..@ref `GPIO_PIN_15`: @p pinIndex is in the valid GPIO pin-index range
 * @def GPIO_PIN_INDEX_TO_MASK
 */
#define GPIO_PIN_INDEX_TO_MASK(pinIndex)		((gpio_pin_t) BIT_MASK(pinIndex))
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
 * @brief Bitmask selecting every GPIO pin controlled through CRL
 * @def GPIO_PIN_MASK_CRL_RANGE
 */
#define GPIO_PIN_MASK_CRL_RANGE						\
(													\
	(gpio_pin_t)									\
	(												\
		GPIO_PIN_0 | GPIO_PIN_1 |					\
		GPIO_PIN_2 | GPIO_PIN_3 |					\
		GPIO_PIN_4 | GPIO_PIN_5 |					\
		GPIO_PIN_6 | GPIO_PIN_7						\
	)												\
)

/**
 * @brief Bitmask selecting every GPIO pin controlled through CRH
 * @def GPIO_PIN_MASK_CRH_RANGE
 */
#define GPIO_PIN_MASK_CRH_RANGE						\
(													\
	(gpio_pin_t)									\
	(												\
		GPIO_PIN_8  | GPIO_PIN_9  |					\
		GPIO_PIN_10 | GPIO_PIN_11 |					\
		GPIO_PIN_12 | GPIO_PIN_13 |					\
		GPIO_PIN_14 | GPIO_PIN_15					\
	)												\
)

/**
 * @brief Bitmask selecting every valid GPIO pin on one GPIO port
 * @def GPIO_PIN_ALL
 */
#define GPIO_PIN_ALL							((gpio_pin_t) (GPIO_PIN_MASK_CRL_RANGE | GPIO_PIN_MASK_CRH_RANGE))

/**
 * @brief No pins bitmask
 * @def GPIO_PIN_NONE
 */
#define GPIO_PIN_NONE							((gpio_pin_t) 0x0000U)

/** @} */ // GPIO_03_Driver_01_Types_02_Pins

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
 * @brief Checks if any of the pins require CRL register configuration
 * @param[in]	pinMask	GPIO pin mask to check
 * @returns CRL usage status of the input GPIO pin mask
 * @retval - `0U`: @p pinMask does not select any pins controlled by CRL
 * @retval - Non-zero: @p pinMask selects at least one pin controlled by CRL
 * @def GPIO_PIN_MASK_REQUIRES_CRL
 */
#define GPIO_PIN_MASK_REQUIRES_CRL(pinMask)			\
	(((((gpio_pin_t) (pinMask)) & GPIO_PIN_MASK_CRL_RANGE) != GPIO_PIN_NONE))

/**
 * @brief Checks if any of the pins require CRH register configuration
 * @param[in]	pinMask	GPIO pin mask to check
 * @returns CRH usage status of the input GPIO pin mask
 * @retval - `0U`: @p pinMask does not select any pins controlled by CRH
 * @retval - Non-zero: @p pinMask selects at least one pin controlled by CRH
 * @def GPIO_PIN_MASK_REQUIRES_CRH
 */
#define GPIO_PIN_MASK_REQUIRES_CRH(pinMask)			\
	(((((gpio_pin_t) (pinMask)) & GPIO_PIN_MASK_CRH_RANGE) != GPIO_PIN_NONE))

/**
 * @brief Returns the pin index for a single-pin mask
 * @param[in]	pinMask	GPIO single-pin mask
 * @returns GPIO pin index decoded from @p pinMask
 * @retval - `0U..15U`: Valid GPIO pin index
 * @retval - @ref `GPIO_PIN_INDEX_INVALID`: Invalid, empty, or multi-pin mask
 */
__STATIC_FORCEINLINE uint8_t GPIO_PinMaskToIndex(const gpio_pin_t pinMask)
{
	uint8_t pinIndex = 0U;

	if ((GPIO_PIN_MASK_IS_VALID(pinMask) == 0U) || (GPIO_PIN_MASK_HAS_AT_MOST_ONE_BIT(pinMask) == 0U))
	{
		return GPIO_PIN_INDEX_INVALID;
	}

	for (pinIndex = GPIO_PIN_INDEX_FIRST; pinIndex < GPIO_PORT_PIN_COUNT; ++pinIndex)
	{
		if (pinMask == GPIO_PIN_INDEX_TO_MASK(pinIndex))
		{
			return pinIndex;
		}
	}

	return GPIO_PIN_INDEX_INVALID;
}

// ==================================================================================================== //
//                                           GPIO Pin Mode Types                                        //
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
//                                       GPIO Pin Configuration Types                                   //
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

/** @} */ // GPIO_03_Driver_01_Types

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

/** @} */ // GPIO_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_TYPES_H_ */
