/**
 * @file gpio.h
 * @author Shrey Shah
 * @brief GPIO Header File
 * @version v1.2
 * @date 14-09-2025
 */

// Header Guards
#ifndef GPIO_H_
#define GPIO_H_

/*---------------------------------------------- Includes ----------------------------------------------*/
#include "gpio_ll.h"

/**
 * @addtogroup GPIO_03_Driver
 * @{
 */

/**
 * @brief GPIO Driver Types
 * @defgroup GPIO_03_Driver_01_Types GPIO Driver Data Types
 * @ingroup GPIO_03_Driver
 *
 * @{
 */

/*---------------------------------------------- Driver GPIO Port ----------------------------------------------*/
/**
 * @brief    Driver GPIO Ports Declarations
 * @defgroup GPIO_03_Driver_01_Types_01_Ports Driver GPIO Ports
 * @ingroup  GPIO_03_Driver_01_Types
 * @details
 * - These constants identify specific GPIO ports
 * - Not all ports may be available on all STM32F1xx variants
 * - STM32F103C8T6 has ports A, B, and C fully available
 *
 * @see STM32F103C8T6 Datasheet - Section 4 Memory mapping | @ref GPIO_01_Registers_02_Memory "GPIO Ports"
 * @{
 */

/**
 * @section GPIO_Driver_Port_Macros GPIO Driver Port Macros
 * @details GPIO Driver Macros 
 * @{ 
 */

/** @brief GPIO Port A @def GPIO_PORT_A */
#define GPIO_PORT_A										((gpio_port_t) 0x00)
/** @brief GPIO Port B @def GPIO_PORT_B */
#define GPIO_PORT_B										((gpio_port_t) 0x01)
/** @brief GPIO Port C @def GPIO_PORT_C */
#define GPIO_PORT_C										((gpio_port_t) 0x02)
/** @brief GPIO Port D @def GPIO_PORT_D */
#define GPIO_PORT_D										((gpio_port_t) 0x03)
/** @brief GPIO Port E @def GPIO_PORT_E */
#define GPIO_PORT_E										((gpio_port_t) 0x04)
/** @brief GPIO Port F @def GPIO_PORT_F */
#define GPIO_PORT_F										((gpio_port_t) 0x05)
/** @brief GPIO Port G @def GPIO_PORT_G */
#define GPIO_PORT_G										((gpio_port_t) 0x06)

/** @} */ // GPIO_Driver_Port_Macros

/**
 * @brief Checks if a GPIO port value is valid
 * @param[in] port The GPIO port value to check
 * @return non-zero (true) if valid, 0 (false) otherwise
 * @def GPIO_DRIVER_IS_PORT
 */
#define GPIO_DRIVER_IS_PORT(port) \
( \
	((port) == GPIO_PORT_A) || \
	((port) == GPIO_PORT_B) || \
	((port) == GPIO_PORT_C) || \
	((port) == GPIO_PORT_D) || \
	((port) == GPIO_PORT_E) || \
	((port) == GPIO_PORT_F) || \
	((port) == GPIO_PORT_G) \
)

/**
 * @brief Helper Function to translate Driver GPIO to LL GPIO Data Type
 * @param[in] gpio Values of @ref GPIO_Driver_Port_Macros "GPIO Driver Port" 
 * @return GPIO Port Data Type used by LL
 * @note Pointer to GPIO Memory Address
 */
__STATIC_FORCEINLINE GPIO_TypeDef* GPIO_D2L_GetPort(const gpio_port_t gpio)
{
	/** @brief Driver GPIO Port Mapping Lookup Table */
	static GPIO_TypeDef* const _driverGPIOPortMapping[] =
	{
		[GPIO_PORT_A] = GPIOA,
		[GPIO_PORT_B] = GPIOB,
		[GPIO_PORT_C] = GPIOC,
		[GPIO_PORT_D] = GPIOD,
		[GPIO_PORT_E] = GPIOE,
		[GPIO_PORT_F] = GPIOF,
		[GPIO_PORT_G] = GPIOG
	};
	return _driverGPIOPortMapping[gpio];
}

/** @} */ // GPIO_03_Driver_01_Types_01_Ports

/**
 * @brief Checks if a GPIO pin mask is valid
 * @param[in] pin @ref GPIO_Driver_Pin_Macros "GPIO Pin Mask" to check
 * @return non-zero (true) if valid, 0 (false) otherwise
 * @note Multiple pins can be ORed together, e.g., (GPIO_PIN_0 | GPIO_PIN_3)
 * @def GPIO_DRIVER_IS_PIN
 */
#define GPIO_DRIVER_IS_PIN(pin)							((((gpio_pin_t)(pin)) & GPIO_PIN_ALL) == ((gpio_pin_t)(pin)))

/**
 * @brief Checks if any of the pins require CRL register configuration
 * @param[in] pin @ref GPIO_Driver_Pin_Macros "GPIO Pin Mask" to check
 * @return non-zero if any pins 0-7 are selected
 * @def GPIO_DRIVER_PIN_REQUIRES_CRL
 */
#define GPIO_DRIVER_PIN_REQUIRES_CRL(pin)				(((gpio_pin_t)(pin)) & (gpio_pin_t) 0x00FF)

/**
 * @brief Checks if any of the pins require CRH register configuration
 * @param[in] pin @ref GPIO_Driver_Pin_Macros "GPIO Pin Mask" to check
 * @return non-zero if any pins 8-15 are selected
 * @def GPIO_DRIVER_PIN_REQUIRES_CRH
 */
#define GPIO_DRIVER_PIN_REQUIRES_CRH(pin)				(((gpio_pin_t)(pin)) & (gpio_pin_t) 0xFF00)

/**
 * @brief Retrieves LL equivalent pin value 
 * @param[in] pin @ref GPIO_Driver_Pin_Macros "GPIO Pin Mask" to check 
 * @return GPIO Pin Data Type used by LL 
 */
__STATIC_FORCEINLINE uint8_t GPIO_D2L_GetPin(const gpio_pin_t pin)
{
	uint8_t pinIndex = 0x00U;
	gpio_pin_t pinMask = pin;

	if ((pin == GPIO_PIN_NONE) || ((pin & GPIO_PIN_ALL) != pin) || ((pin & (pin - 1U)) != GPIO_PIN_NONE))
	{
		return (uint8_t) 0x10U;
	}

	while ((pinMask & (gpio_pin_t) 0x0001U) == (gpio_pin_t) 0x0000U)
	{
		pinMask = (gpio_pin_t) (pinMask >> 1U);
		++pinIndex;
	}

	return pinIndex;
}

/*---------------------------------------------- Driver GPIO Pin Modes ----------------------------------------------*/
/**
 * @brief    GPIO pin operating modes
 * @defgroup GPIO_03_Driver_01_Types_03_PinModes Driver GPIO Pin Modes
 * @ingroup  GPIO_03_Driver_01_Types
 * * @details
 * - The constants define the operational mode (MODE[1:0] bits) of GPIO pins.
 * - The mode determines whether the pin is input/output and the output speed.
 * * @note Output speed affects both slew rate and power consumption.
 * @see Reference Manual RM0008 - Section 9.1.1 GPIO port configuration
 * * @{
 */

/**
 * @section GPIO_Driver_PinMode_Macros GPIO Driver Pin Mode Macros 
 * @details GPIO Driver Pin Mode Macros 
 * @{
 */
/** @brief Input mode @def GPIO_PIN_MODE_INPUT */
#define GPIO_PIN_MODE_INPUT								((gpio_pin_mode_t) 0x00)
/** @brief Output mode, max speed 10 MHz @def GPIO_PIN_MODE_OUTPUT_10MHz */
#define GPIO_PIN_MODE_OUTPUT_10MHz						((gpio_pin_mode_t) 0x01)
/** @brief Output mode, max speed 2 MHz @def GPIO_PIN_MODE_OUTPUT_2MHz */
#define GPIO_PIN_MODE_OUTPUT_2MHz						((gpio_pin_mode_t) 0x02)
/** @brief Output mode, max speed 50 MHz @def GPIO_PIN_MODE_OUTPUT_50MHz */
#define GPIO_PIN_MODE_OUTPUT_50MHz						((gpio_pin_mode_t) 0x03)

/** @} */ // GPIO_Driver_PinMode_Macros

/**
 * @brief Checks if a GPIO pin mode is valid
 * @param[in] mode The GPIO pin mode to check
 * @return non-zero if valid, 0 otherwise
 * @def GPIO_DRIVER_PIN_IS_MODE
 */
#define GPIO_DRIVER_PIN_IS_MODE(mode) \
( \
    ((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_INPUT || \
    ((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_10MHz || \
    ((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_2MHz || \
    ((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_50MHz \
)

/**
 * @brief Returns the driver-specific GPIO mode for a given GPIO pin mode
 * @param[in] mode Public GPIO pin mode
 * @return GPIO mode
 * @note Make sure to validate the mode using @ref GPIO_DRIVER_IS_MODE before calling
 */
__STATIC_FORCEINLINE uint8_t GPIO_D2L_GetPinMode(const gpio_pin_mode_t mode)
{
	switch(mode)
	{
		case GPIO_PIN_MODE_INPUT: return 0x00U; break;
		case GPIO_PIN_MODE_OUTPUT_10MHz: return 0x01U; break;
		case GPIO_PIN_MODE_OUTPUT_2MHz: return 0x02U; break;
		case GPIO_PIN_MODE_OUTPUT_50MHz: return 0x03U; break;
		default: return 0x00U;
	}
}

/** @} */ // GPIO_03_Driver_01_Types_03_PinModes

/*---------------------------------------------- Driver GPIO Pin Configurations ----------------------------------------------*/
/**
 * @brief    GPIO pin configuration settings
 * @defgroup GPIO_03_Driver_01_Types_04_PinConfig Driver GPIO Pin Configurations
 * @ingroup  GPIO_03_Driver_01_Types
 * * @details
 * - The constants define the electrical configuration (CNF[1:0] bits) of GPIO pins.
 * - The configuration must be compatible with the selected mode (@ref GPIO_03_Driver_01_Types01_PinModes).
 * * @warning Configuration must match mode:
 * - Input modes (MODE=00): Use `GPIO_PIN_CNF_IN_*`
 * - Output modes (MODE>00): Use `GPIO_PIN_CNF_OUT_*`
 * @see Reference Manual RM0008 - Section 9.1.1 GPIO port configuration
 * * @{
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
 * @returns non-zero if valid else 0
 * @note This validation macro only checks for defined constants — it does not
 *       verify mode-to-configuration compatibility (handled at runtime)
 * @def GPIO_DRIVER_PIN_IS_CONFIG
 */
#define GPIO_DRIVER_PIN_IS_CONFIG(config)								\
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
 * @brief Maps driver-side GPIO configuration to LL GPIO configuration
 * @param[in] config GPIO pin configuration (gpio_pin_config_t)
 * @return Corresponding raw GPIO configuration field value
 */
__STATIC_FORCEINLINE uint8_t GPIO_D2L_GetPinConfig(const gpio_pin_config_t config)
{
	switch (config)
	{
		// Input configurations
		case GPIO_PIN_CNF_IN_ANALOG: return 0x00U; break;	
		case GPIO_PIN_CNF_IN_FLOAT: return 0x01U; break;	
		case GPIO_PIN_CNF_IN_PULL_DOWN:
		case GPIO_PIN_CNF_IN_PULL_UP: return 0x02U; break;	
		// Output configurations
		case GPIO_PIN_CNF_OUT_GP_PP: return 0x00U; break;	
		case GPIO_PIN_CNF_OUT_GP_OD: return 0x01U; break;	
		case GPIO_PIN_CNF_OUT_AF_PP: return 0x02U; break;	
		case GPIO_PIN_CNF_OUT_AF_OD: return 0x03U; break;	
		// Default fallback for invalid values
		default: return 0x00U;
	}
}

/**
 * @brief Checks if a GPIO configuration uses Alternate Function (AF) mode
 * @param[in] config GPIO pin configuration value of type @ref gpio_pin_config_t
 * @returns true (non-zero) if configuration is AF type else 0
 * @note According to STM32F1 reference manual (RM0008, Table 20),
 *       Alternate Function configurations are:
 *       - @ref GPIO_PIN_CNF_OUT_AF_PP  → AF Push-Pull  
 *       - @ref GPIO_PIN_CNF_OUT_AF_OD  → AF Open-Drain
 * @def GPIO_DRIVER_PIN_IS_AF_CONFIG
 */
#define GPIO_DRIVER_PIN_IS_AF_CONFIG(config)								\
	(																		\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_AF_PP) ||		\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_AF_OD)			\
	)

/** 
 * @brief Determines whether pull-up or pull-down mode is used 
 * @def GPIO_DRIVER_PIN_IS_PULL_CONFIG 
 * @see @ref GPIO_03_Driver_01_Types_03_PinModes "GPIO Driver Pin Modes" | @ref GPIO_03_Driver_01_Types_04_PinConfig "GPIO Driver Pin Configurations" 
 */
#define GPIO_DRIVER_PIN_IS_PULL_CONFIG(mode, config)						\
	(																		\
		(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_INPUT) &&				\
		((((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_PULL_DOWN) ||	\
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_PULL_UP))		\
	)

/**
 * @brief Validates GPIO mode and configuration compatibility
 * @param[in] mode The GPIO pin mode (of type gpio_pin_mode_t)
 * @param[in] config  The GPIO pin configuration (of type gpio_pin_config_t)
 * @returns non-zero (true) if combination is valid else 0
 * @note According to STM32F1 reference manual (RM0008, Table 20):
 * - When MODE = 0b00 (Input), CNF must be one of the `GPIO_PIN_CNF_IN_*` values.
 * - When MODE > 0b00 (Output/AF), CNF must be one of the `GPIO_PIN_CNF_OUT_*` values.
 * @def GPIO_DRIVER_PIN_IS_MODE_CONFIG_COMPATIBLE
 */
#define GPIO_DRIVER_PIN_IS_MODE_CONFIG_COMPATIBLE(mode, config) ( \
	((((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_INPUT) && ( \
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_ANALOG)     || \
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_FLOAT)      || \
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_PULL_DOWN)  || \
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_IN_PULL_UP)       \
	)) || \
	(((((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_10MHz) || \
	(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_2MHz)  || \
	(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_50MHz)) && ( \
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_GP_PP)     || \
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_GP_OD)     || \
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_AF_PP)     || \
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_AF_OD)       \
	)) \
)

/**
 * @brief Extracts GPIO Pull-Up or Pull-Down configuration from a driver pin configuration value.
 * @param[in] config GPIO configuration value of type @ref gpio_pin_config_t.
 *
 * @returns `0x01U` if the configuration value has any bits set in
 *         the upper nibble (`0xF0`), otherwise `0x00U`.
 *
 * @note This macro assumes that the pull direction is encoded in the upper nibble
 *       of the driver configuration constants:
 *       - Pull-Down → Low nibble (0x02)
 *       - Pull-Up   → High nibble (0x12)
 *
 * @def GPIO_DRIVER_GET_PULL_BIT
 */
#define GPIO_DRIVER_GET_PULL_BIT(config) \
	((((gpio_pin_config_t)(config)) & ((gpio_pin_config_t) 0xF0)) ? 0x01U : 0x00U)
	
/** @} */ // GPIO_03_Driver_01_Types_04_PinConfig

/*---------------------------------------------- Driver EXTI ----------------------------------------------*/
/**
 * @brief    External Interrupt Trigger Configurations
 * @defgroup GPIO_03_Driver_01_Types_05_EXTITriggers Driver EXTI Trigger Types
 * @ingroup  GPIO_03_Driver_01_Types
 * * @details
 * - These constants define when an external interrupt should trigger for a given line.
 * - Used with EXTI configuration registers (RTSR/FTSR).
 * * @see Reference Manual RM0008 - Section 10.2.3 EXTI rising/falling trigger selection
 * @{
 */

/** @brief Trigger on falling edge @def GPIO_EXTI_TRIGGER_FALLING */
#define GPIO_EXTI_TRIGGER_FALLING							((gpio_exti_trigger_t) 0x01)
/** @brief Trigger on rising edge @def GPIO_EXTI_TRIGGER_RISING */
#define GPIO_EXTI_TRIGGER_RISING							((gpio_exti_trigger_t) 0x02)
/** @brief Trigger on both edges @def GPIO_EXTI_TRIGGER_BOTH */
#define GPIO_EXTI_TRIGGER_BOTH								(GPIO_EXTI_TRIGGER_FALLING | GPIO_EXTI_TRIGGER_RISING)

/** @} */ // GPIO_03_Driver_01_Types_05_EXTITriggers

/*---------------------------------------------- Driver EXTI GPIO Port ----------------------------------------------*/
/**
 * @brief    EXTI port source selections
 * @defgroup GPIO_03_Driver_01_Types_06_EXTIPorts Driver EXTI Port Sources
 * @ingroup  GPIO_03_Driver_01_Types
 * * @details These constants define which GPIO port is connected to the EXTI lines
 * (EXTI lines 0-15). The values correspond to the selection bits in the $\text{AFIO}$ registers.
 * * @see Reference Manual RM0008 - Section 9.2.5 AFIO_EXTICR1-4 registers
 * @{
 */

/** @brief EXTI source: GPIO Port A (0000) @def GPIO_EXTI_PORT_A */
#define GPIO_EXTI_PORT_A									((gpio_exti_port_t) 0x00)
/** @brief EXTI source: GPIO Port B (0001) @def GPIO_EXTI_PORT_B */
#define GPIO_EXTI_PORT_B									((gpio_exti_port_t) 0x01)
/** @brief EXTI source: GPIO Port C (0010) @def GPIO_EXTI_PORT_C */
#define GPIO_EXTI_PORT_C									((gpio_exti_port_t) 0x02)
/** @brief EXTI source: GPIO Port D (0011) @def GPIO_EXTI_PORT_D */
#define GPIO_EXTI_PORT_D									((gpio_exti_port_t) 0x03)
/** @brief EXTI source: GPIO Port E (0100) @def GPIO_EXTI_PORT_E */
#define GPIO_EXTI_PORT_E									((gpio_exti_port_t) 0x04)
/** @brief EXTI source: GPIO Port F (0101) @def GPIO_EXTI_PORT_F */
#define GPIO_EXTI_PORT_F									((gpio_exti_port_t) 0x05)
/** @brief EXTI source: GPIO Port G (0110) @def GPIO_EXTI_PORT_G */
#define GPIO_EXTI_PORT_G									((gpio_exti_port_t) 0x06)

/** @} */ // GPIO_03_Driver_01_Types_06_EXTIPorts

/** @} */ // GPIO_03_Driver_01_Types

/**
 * @brief GPIO Pin Configuration Structure
 * @defgroup GPIO_03_Driver_02_Config Driver GPIO Configuration Structure
 * @ingroup  GPIO_03_Driver
 * @example
 * @code
 * // Configure Pin5 as output push-pull @2MHz
 * gpio_config_t led_config =
 * {
 *     .pin = GPIO_PIN_5,
 *     .mode = GPIO_PIN_MODE_OUTPUT_2MHz,
 *     .config = GPIO_PIN_CNF_OUT_GP_PP
 * };
 *
 * // Configure Pin13 as input with pull-up
 * gpio_config_t button_config =
 * {
 *     .pin = GPIO_PIN_13,
 *     .mode = GPIO_PIN_MODE_INPUT,
 *     .config = GPIO_PIN_CNF_IN_PULL_UP
 * };
 *
 * // Configure multiple pins as analog inputs
 * gpio_config_t adc_config =
 * {
 *     .pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2,
 *     .mode = GPIO_PIN_MODE_INPUT,
 *     .config = GPIO_PIN_CNF_IN_ANALOG
 * };
 * @endcode
 * 
 * @{
 */
typedef struct
{
	/**
	 * @brief Pin selection bitmask
	 *
	 * @details
	 * - @ref GPIO_PIN_0: Pin 0
	 * - @ref GPIO_PIN_1: Pin 1
	 * ...
	 * - @ref GPIO_PIN_15: Pin 15
	 * - @ref GPIO_PIN_ALL: All pins
	 * - @ref GPIO_PIN_NONE: No pins
	 *
	 * @see @ref GPIO_03_Driver_01_Types_02_Pins "GPIO Pins"
	 */
	gpio_pin_t pin;

	/**
	 * @brief Pin operating mode and speed
	 *
	 * @details
	 * @ref GPIO_PIN_MODE_INPUT: Input mode
	 * @ref GPIO_PIN_MODE_OUTPUT_10MHz: Output 10MHz
	 * @ref GPIO_PIN_MODE_OUTPUT_2MHz: Output 2MHz
	 * @ref GPIO_PIN_MODE_OUTPUT_50MHz: Output 50MHz
	 *
	 * @see @ref GPIO_03_Driver_01_Types_03_PinModes "GPIO Pin Modes"
	 */
		gpio_pin_mode_t mode;

	/**
	 * @brief Pin electrical configuration
	 *
	 * @details
	 * @ref GPIO_PIN_MODE_INPUT "Input Modes:"
	 * @ref GPIO_PIN_CNF_IN_ANALOG: Analog input
	 * @ref GPIO_PIN_CNF_IN_FLOAT: Floating input
	 * @ref GPIO_PIN_CNF_IN_PULL_DOWN: Input with pull-down
	 * @ref GPIO_PIN_CNF_IN_PULL_UP: Input with pull-up
	 *
	 * @ref GPIO_PIN_MODE_OUTPUT_10MHz "Output Modes:"
	 * @ref GPIO_PIN_CNF_OUT_GP_PP: General purpose push-pull
	 * @ref GPIO_PIN_CNF_OUT_GP_OD: General purpose open-drain
	 * @ref GPIO_PIN_CNF_OUT_AF_PP: Alternate function push-pull
	 * @ref GPIO_PIN_CNF_OUT_AF_OD: Alternate function open-drain
	 *
	 * @warning Must be compatible with mode field
	 *
	 * @see @ref GPIO_03_Driver_01_Types_04_PinConfig "GPIO Pin Configuration"
	 */
		gpio_pin_config_t config;
} gpio_config_t;

/** @} */ // GPIO_03_Driver_02_Config

#define GPIO_OB_LED_CONFIG() \
{											\
	.pin = GPIO_OB_LED_PIN,					\
	.mode = GPIO_PIN_MODE_OUTPUT_2MHz,		\
	.config = GPIO_PIN_CNF_OUT_GP_PP		\
}

/** @} */ // GPIO_03_Driver

/**
 * @brief Sets the GPIO
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @note Atomic operation through `BSRR`
 */
__STATIC_FORCEINLINE void GPIO_PinSet(const gpio_port_t gpio, const gpio_pin_t pin)
{
	GPIO_LL_WRITE_REG(GPIO_D2L_GetPort(gpio), BSRR, (uint32_t) pin);
}

/**
 * @brief Resets the GPIO
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @note Atomic operation through `BRR`
 */
__STATIC_FORCEINLINE void GPIO_PinReset(const gpio_port_t gpio, const gpio_pin_t pin)
{
	GPIO_LL_WRITE_REG(GPIO_D2L_GetPort(gpio), BRR, (uint32_t) pin);
}

/**
 * @brief Toggles the GPIO
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 */
__STATIC_FORCEINLINE void GPIO_PinToggle(const gpio_port_t gpio, const gpio_pin_t pin)
{
	GPIO_TypeDef* const GPIOx = GPIO_D2L_GetPort(gpio);
	uint32_t regImage = 0x00UL;

	GPIO_LL_READ_REG(GPIOx, ODR, regImage);
	regImage ^= (uint32_t) pin;
	GPIO_LL_WRITE_REG(GPIOx, ODR, regImage);
}

/**
 * @brief Retrieves the GPIO Status
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @returns `0x00U` when the selected pin is low, else `0x01U`
 * @note This API expects a single-pin mask.
 */
__STATIC_FORCEINLINE uint8_t GPIO_Get(const gpio_port_t gpio, const gpio_pin_t pin)
{
	uint32_t reg = 0x00UL;
	const uint8_t pinIndex = GPIO_D2L_GetPin(pin);

	if (pinIndex == (uint8_t) 0x10U)
	{
		return (uint8_t) 0x00U;
	}

	GPIO_LL_READ_REG(GPIO_D2L_GetPort(gpio), IDR, reg);
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

/*---------------------------------------------- Driver APIs ----------------------------------------------*/

/**
 * @brief  Configures GPIO pin mode and electrical parameters.
 * @details
 * Updates the MODE and CNF fields in the GPIO control registers (CRL/CRH),
 * and sets the pull-up/pull-down state in ODR when applicable.
 * Supports batch configuration of multiple pins using bitmask.
 *
 * @param[in] gpio    GPIO port identifier (see @ref gpio_port_t)
 * @param[in] pin	  @ref gpio_pin_t "GPIO Pin"
 * @param[in] mode    Desired operating mode (see @ref gpio_pin_mode_t)
 * @param[in] config  Electrical configuration (see @ref gpio_pin_config_t)
 *
 * @note
 * - Automatically detects whether CRL or CRH should be updated per pin.
 * - Pull-up/down configuration is only applied when valid for input modes.
 * - Existing register bits for unaffected pins remain unchanged.
 * - Does not perform validation; call-site must ensure compatible parameters.
 *
 * @retval `DRIVER_STATUS_SUCCESS`:				Configuration applied successfully
 * @retval `DRIVER_STATUS_ERROR_INVALID_ARG`:	`gpio`, `pin`, `mode`, or `config` was invalid
 * @retval `DRIVER_STATUS_ERROR_STATE`:			Staged configuration update failed
 *
 */
driver_status_t GPIO_SetPinModeConfig(const gpio_port_t gpio, gpio_pin_t pin, const gpio_pin_mode_t mode, const gpio_pin_config_t config);

/**
 * @brief Get GPIO Pin Mode Configuration
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @return @ref gpio_pin_mode_t "GPIO Driver Pin Mode"
 * 
 * @details
 * Extracts the MODE field from the pin's configuration register.
 * Returns only the 2-bit mode value without the configuration bits.
 */
gpio_pin_mode_t GPIO_GetPinMode(const gpio_port_t gpio, const gpio_pin_t pin);

/**
 * @brief  Configures the operating mode of one or more GPIO pins.
 * @details
 * Updates the MODE bits in the GPIO port configuration registers (CRL/CRH)
 * for the selected pin(s). Supports configuring multiple pins simultaneously.
 *
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @param[in] mode   Desired pin mode (see @ref gpio_pin_mode_t)
 *
 * @retval `DRIVER_STATUS_SUCCESS`:  Configuration applied successfully.
 * @retval `DRIVER_STATUS_ERROR_FAIL`:     Invalid parameter (port, pin, or mode).
 *
 * @note
 * - Automatically determines whether CRL or CRH needs to be updated.
 * - Existing configuration bits for unaffected pins remain unchanged.
 * - Use with @ref GPIO_SetPinConfig for full electrical configuration.
 */
driver_status_t GPIO_SetPinMode(const gpio_port_t gpio, gpio_pin_t pin, const gpio_pin_mode_t mode);

/**
 * @brief Get GPIO Pin Configuration Type
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @return @ref gpio_pin_config_t "GPIO Driver Pin Configuration"
 * 
 * @details
 * Extracts the CNF field from the pin's configuration register.
 * Returns only the 2-bit configuration value without the mode bits.
 */
gpio_pin_config_t GPIO_GetPinConfig(const gpio_port_t gpio, const gpio_pin_t pin);

/**
 * @brief  Configures the electrical setting (CNF bits) of one or more GPIO pins.
 * @details
 * Updates the CNF[1:0] configuration bits in CRL/CRH for the specified pins,
 * setting input/output type and alternate-function behavior as defined
 * by the driver configuration constants.
 *
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @param[in] config  Desired configuration (see @ref gpio_pin_config_t)
 *
 * @retval `DRIVER_STATUS_SUCCESS`:  Configuration applied successfully.
 * @retval `DRIVER_STATUS_ERROR_FAIL`:     Invalid parameter (port, pin, or configuration).
 *
 * @note
 * - Automatically determines whether CRL or CRH registers are affected.
 * - Use with @ref GPIO_SetPinMode to fully configure a pin.
 * - Safe for multi-pin configuration; unaffected bits are preserved.
 * - Does not configure Pull Up, need to be externally set.
 */
driver_status_t GPIO_SetPinConfig(const gpio_port_t gpio, gpio_pin_t pin, const gpio_pin_config_t config);

/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param[in] gpio GPIO Port (Refer `gpio_port_t`)
 * @param[in] gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
driver_status_t GPIO_Init(const gpio_port_t gpio, gpio_config_t *const gpioConfig);

/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param[in] gpio GPIO Port (Refer `gpio_port_t`)
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
driver_status_t GPIO_Deinit(const gpio_port_t gpio, const gpio_pin_t pin);

/**
 * @brief Configures the On-board LED
 * @returns Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
driver_status_t OB_LED_Init(void);

/**
 * @brief Configures the LED connected to the specified GPIO Port and Pin
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] gpioConfig @ref gpio_config_t "GPIO Configuration Structure"
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 * @note Assumes Pin is already filled
 */
__STATIC_FORCEINLINE driver_status_t GPIO_LED_Init(const gpio_port_t gpio, gpio_config_t* const gpioConfig)
{
	// Update the GPIO Configuration Structure for LED
	gpioConfig->mode = GPIO_PIN_MODE_OUTPUT_10MHz;
	gpioConfig->config = GPIO_PIN_CNF_OUT_GP_PP;
	// Call GPIO Config()
	return GPIO_Init(gpio, gpioConfig);
}

/**
 * @brief Deinitialize the On-board LED
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
__STATIC_FORCEINLINE driver_status_t OB_LED_Deinit(void)
{
	return GPIO_Deinit(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

#endif /* GPIO_H_ */
