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
 * @brief GPIO Driver Layer
 * @defgroup GPIO_03_Driver GPIO Driver
 * @ingroup GPIO
 *
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
 * @see STM32F103C8T6 Datasheet - Section 4 Memory mapping | @ref GPIO_03_Registers_03_Memory "GPIO Ports"
 * @{
 */

/** @brief GPIO Port Identifier type @typedef gpio_port_t  */
typedef uint8_t											gpio_port_t;
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

/** @brief Driver GPIO Port Mapping Lookup Table */
static const GPIO_TypeDef* const _driverGpioPortMapping[] =
{
	[GPIO_PORT_A] = GPIOA,
	[GPIO_PORT_B] = GPIOB,
	[GPIO_PORT_C] = GPIOC,
	[GPIO_PORT_D] = GPIOD,
	[GPIO_PORT_E] = GPIOE,
	[GPIO_PORT_F] = GPIOF,
	[GPIO_PORT_G] = GPIOG
};

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
__STATIC_FORCEINLINE GPIO_TypeDef* const GPIO_getLLPort(const gpio_port_t gpio)
{
	return _driverGpioPortMapping[gpio];
}

/** @} */ // GPIO_03_Driver_01_Types_01_Ports

/*---------------------------------------------- Driver GPIO Pins ----------------------------------------------*/
/**
 * @brief    Driver GPIO Pins Declarations
 * @defgroup GPIO_03_Driver_01_Types_02_Pins Driver GPIO Pins
 * @ingroup  GPIO_03_Driver_01_Types
 * @details
 * - These constants represent individual pins as bitmasks
 * - Thus, allowing multiple pins to be selected using bitwise OR operations
 * @warning Not all pins are available on all ports - check device datasheet
 * @{
 */

/** @typedef GPIO pin bitmask type @typedef gpio_pin_t*/
typedef uint16_t 										gpio_pin_t;
/**
 * @section GPIO_Driver_Pin_Macros GPIO Driver Pin Macros 
 * @details GPIO Driver Pin Macros
 * @{
 */
/** @brief No pins bitmask @def GPIO_PIN_NONE @note Use @ref GPIO_PIN_NONE "GPIO_PIN_NONE" for no pins */
#define GPIO_PIN_NONE									((gpio_pin_t) 0x0000)
/** @brief Pin 0 bitmask @def GPIO_PIN_0 */
#define GPIO_PIN_0										((gpio_pin_t) 0x0001)
/** @brief Pin 1 bitmask @def GPIO_PIN_1 */
#define GPIO_PIN_1										((gpio_pin_t) 0x0002)
/** @brief Pin 2 bitmask @def GPIO_PIN_2 */
#define GPIO_PIN_2										((gpio_pin_t) 0x0004)
/** @brief Pin 3 bitmask @def GPIO_PIN_3 */
#define GPIO_PIN_3										((gpio_pin_t) 0x0008)
/** @brief Pin 4 bitmask @def GPIO_PIN_4 */
#define GPIO_PIN_4										((gpio_pin_t) 0x0010)
/** @brief Pin 5 bitmask @def GPIO_PIN_5 */
#define GPIO_PIN_5										((gpio_pin_t) 0x0020)
/** @brief Pin 6 bitmask @def GPIO_PIN_6 */
#define GPIO_PIN_6										((gpio_pin_t) 0x0040)
/** @brief Pin 7 bitmask @def GPIO_PIN_7 */
#define GPIO_PIN_7										((gpio_pin_t) 0x0080)
/** @brief Pin 8 bitmask @def GPIO_PIN_8 */
#define GPIO_PIN_8										((gpio_pin_t) 0x0100)
/** @brief Pin 9 bitmask @def GPIO_PIN_9 */
#define GPIO_PIN_9										((gpio_pin_t) 0x0200)
/** @brief Pin 10 bitmask @def GPIO_PIN_10 */
#define GPIO_PIN_10										((gpio_pin_t) 0x0400)
/** @brief Pin 11 bitmask @def GPIO_PIN_11 */
#define GPIO_PIN_11										((gpio_pin_t) 0x0800)
/** @brief Pin 12 bitmask @def GPIO_PIN_12 */
#define GPIO_PIN_12										((gpio_pin_t) 0x1000)
/** @brief Pin 13 bitmask @def GPIO_PIN_13 */
#define GPIO_PIN_13										((gpio_pin_t) 0x2000)
/** @brief Pin 14 bitmask @def GPIO_PIN_14 */
#define GPIO_PIN_14										((gpio_pin_t) 0x4000)
/** @brief Pin 15 bitmask @def GPIO_PIN_15 */
#define GPIO_PIN_15										((gpio_pin_t)0x8000)
/** @brief All pins bitmask @def GPIO_PIN_ALL @note Use @ref GPIO_PIN_ALL "GPIO_PIN_ALL" for all pins */
#define GPIO_PIN_ALL									((gpio_pin_t) 0xFFFF)

/** @} */ // GPIO_Driver_Pin_Macros

// Board Specific Configuration
#ifdef STM32F103C8T6__
	#define GPIO_OB_LED_PORT 									GPIO_PORT_C
	#define GPIO_OB_LED_PIN 									GPIO_PIN_13
#endif /* STM32F103C8T6__ */

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
__STATIC_FORCEINLINE _gpio_pin_t GPIO_getLLPin(const gpio_pin_t pin)
{
	return GPIO_LL_EXTRACT_PIN_MASK(pin);
} 

/** @} */ // GPIO_03_Driver_01_Types_02_Pins

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

/** @brief GPIO Pin Mode @typedef gpio_pin_mode_t */
typedef uint8_t											gpio_pin_mode_t;
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
__STATIC_FORCEINLINE const _gpio_pin_mode_t GPIO_getLLPinMode(const gpio_pin_mode_t mode)
{
	switch(mode)
	{
		case GPIO_PIN_MODE_INPUT: return _GPIO_PIN_MODE_INPUT; break;
		case GPIO_PIN_MODE_OUTPUT_10MHz: return _GPIO_PIN_MODE_OUTPUT_10MHz; break;
		case GPIO_PIN_MODE_OUTPUT_2MHz: return _GPIO_PIN_MODE_OUTPUT_2MHz; break;
		case GPIO_PIN_MODE_OUTPUT_50MHz: return _GPIO_PIN_MODE_OUTPUT_50MHz; break;
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

/** @brief GPIO Pin Configuration type @typedef gpio_pin_config_t */
typedef uint8_t											gpio_pin_config_t;
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
 * @return Corresponding LL configuration (_gpio_pin_config_t)
 */
__STATIC_FORCEINLINE const _gpio_pin_config_t GPIO_getLLPinConfig(const gpio_pin_config_t config)
{
	switch (config)
	{
		// Input configurations
		case GPIO_PIN_CNF_IN_ANALOG: return _GPIO_PIN_CNF_INPUT_ANALOG; break;	
		case GPIO_PIN_CNF_IN_FLOAT: return _GPIO_PIN_CNF_INPUT_FLOATING; break;	
		case GPIO_PIN_CNF_IN_PULL_DOWN:
		case GPIO_PIN_CNF_IN_PULL_UP: return _GPIO_PIN_CNF_INPUT_PULL; break;	
		// Output configurations
		case GPIO_PIN_CNF_OUT_GP_PP: return _GPIO_PIN_CNF_OUTPUT_PP; break;	
		case GPIO_PIN_CNF_OUT_GP_OD: return _GPIO_PIN_CNF_OUTPUT_OD; break;	
		case GPIO_PIN_CNF_OUT_AF_PP: return _GPIO_PIN_CNF_AF_PP; break;	
		case GPIO_PIN_CNF_OUT_AF_OD: return _GPIO_PIN_CNF_AF_OD; break;	
		// Default fallback for invalid values
		default: break;
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
#define GPIO_DRIVER_PIN_IS_AF_CONFIG(config)							\
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
	((((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_10MHz) || \
	(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_2MHz)  || \
	(((gpio_pin_mode_t) (mode)) == GPIO_PIN_MODE_OUTPUT_50MHz)) && ( \
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_GP_PP)     || \
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_GP_OD)     || \
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_AF_PP)     || \
		(((gpio_pin_config_t) (config)) == GPIO_PIN_CNF_OUT_AF_OD)       \
	) \
)

/**
 * @brief Extracts GPIO Pull-Up or Pull-Down configuration from a driver pin configuration value.
 * @param[in] config GPIO configuration value of type @ref gpio_pin_config_t.
 *
 * @returns `_GPIO_PIN_CNF_INPUT_PULL_UP` if the configuration value has any bits set in
 *         the upper nibble (`0xF0`), otherwise `_GPIO_PIN_CNF_INPUT_PULL_DOWN`.
 *
 * @note This macro assumes that the pull direction is encoded in the upper nibble
 *       of the driver configuration constants:
 *       - Pull-Down → Low nibble (0x02)
 *       - Pull-Up   → High nibble (0x12)
 *
 * @see _GPIO_PIN_CNF_INPUT_PULL_UP
 * @see _GPIO_PIN_CNF_INPUT_PULL_DOWN
 * @def GPIO_LL_PIN_GET_PULL_CONFIG
 */
#define GPIO_LL_PIN_GET_PULL_CONFIG(config) \
	((((gpio_pin_config_t)(config)) & ((gpio_pin_config_t) 0xF0)) ? _GPIO_PIN_CNF_INPUT_PULL_UP : _GPIO_PIN_CNF_INPUT_PULL_DOWN)

/**
 * @brief GPIO pin parameter type
 * @typedef gpio_pin_parameter_t
 * @details 
 * - Represents an encoded 8-bit value containing both mode and configuration information for a GPIO pin.  
 * - Used internally for parameter passing and low-level driver encoding
 * - Each field is defined as follows:
 * <ul>
 * <li>Bits [1:0] → GPIO mode bits (MODE[1:0])</li>
 * <li>Bits [3:2] → GPIO configuration bits (CNF[1:0])</li>
 * </ul>
 * - Remaining bits may be reserved for additional flags or pin attributes
 */
typedef uint8_t gpio_pin_parameter_t;

/**
 * @brief Extracts the GPIO pin mode from a combined @ref gpio_pin_parameter_t "pin parameter" value
 * @param[in] pinParameter Encoded GPIO pin parameter of type @ref gpio_pin_parameter_t.
 * @return GPIO pin mode value of type @ref _gpio_pin_mode_t.
 * 
 * @details
 * The mode information is stored in bits [1:0] of the pin parameter.  
 * This macro masks and returns only those bits, interpreting the result as a 
 * @ref gpio_pin_mode_t value.
 * 
 * @note
 * - This macro should be used when decoding composite GPIO configuration data 
 * - Example: Initializing or validating pin configuration structures
 * @def GPIO_LL_PIN_PARAMETER_EXTRACT_MODE
 */
#define GPIO_LL_PIN_PARAMETER_EXTRACT_MODE(pinParameter) \
	((_gpio_pin_mode_t)(((gpio_pin_parameter_t)(pinParameter)) & ((gpio_pin_parameter_t) 0x03)))

/**
 * @brief Extracts the GPIO pin configuration from a combined @ref gpio_pin_parameter_t "pin parameter" value
 * @param[in] pinParameter Encoded GPIO pin parameter of type @ref gpio_pin_parameter_t.
 * @return GPIO pin mode value of type @ref _gpio_pin_config_t
 * 
 * @details
 * The mode information is stored in bits [1:0] of the pin parameter.  
 * This macro masks and returns only those bits, interpreting the result as a 
 * @ref gpio_pin_mode_t value.
 * 
 * @note
 * - This macro should be used when decoding composite GPIO configuration data 
 * - Example: Initializing or validating pin configuration structures
 * @def GPIO_LL_PIN_PARAMETER_EXTRACT_CONFIGURATION
 */
#define GPIO_LL_PIN_PARAMETER_EXTRACT_CONFIGURATION(pinParameter) \
	((_gpio_pin_config_t)((((gpio_pin_parameter_t)(pinParameter)) >> 0x02) & ((gpio_pin_parameter_t) 0x03)))
	
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

/** @brief EXTI trigger type @typedef gpio_exti_trigger_t */
typedef uint8_t												gpio_exti_trigger_t;
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

/** @brief EXTI port source type @typedef gpio_exti_port_t */
typedef uint8_t gpio_exti_port_t;
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
	gpio_pin_mode_t mode : 2;

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
	gpio_pin_config_t config : 2;
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
 * @note Atomicity
 */
__STATIC_FORCEINLINE void GPIO_PinSet(const gpio_port_t gpio, const gpio_pin_t pin)
{
	__GPIO_WriteBSRR(GPIO_getLLPort(gpio), (uint32_t) pin);
}

/**
 * @brief Resets the GPIO
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @note Atomicity
 */
__STATIC_FORCEINLINE void GPIO_PinReset(const gpio_port_t gpio, const gpio_pin_t pin)
{
	__GPIO_WriteBRR(GPIO_getLLPort(gpio), (uint32_t) pin);
}

/**
 * @brief Toggles the GPIO
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 */
__STATIC_FORCEINLINE void GPIO_PinToggle(const gpio_port_t gpio, const gpio_pin_t pin)
{
	GPIO_TypeDef* const GPIOx = GPIO_getLLPort(gpio);
	__GPIO_WriteODR(GPIOx, (uint32_t)(__GPIO_ReadODR(GPIOx) ^ ((uint32_t) pin)));
}

/**
 * @brief Retrieves the GPIO Status
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @returns 
 */
__STATIC_FORCEINLINE uint8_t GPIO_Get(const gpio_port_t gpio, const gpio_pin_t pin)
{
	uint32_t reg = __GPIO_ReadIDR(GPIO_getLLPort(gpio));
	reg = (reg & ((uint32_t) pin)) >> GPIO_getLLPin(pin);
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
 * @brief Get GPIO Pin Configuration Register Value
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @return @ref gpio_pin_parameter_t "4-bit parameter value (CNF[3:2] | MODE[1:0])"
 * @see @ref GPIO_Pins_Summary "Summary of Configuration"
 * 
 * @details
 * Retrieves the complete 4-bit configuration value for a specified GPIO pin
 * directly from the hardware registers. The returned value matches the exact
 * bit pattern stored in the CRL/CRH registers.
 * 
 * - **Bit 3:2**: CNF configuration field
 * - **Bit 1:0**: MODE configuration field  
 * 
 * @note The returned value can be directly compared with predefined constants
 *       or used for bit manipulation operations.
 * 
 */
__STATIC_FORCEINLINE gpio_pin_parameter_t GPIO_GetPinParameters(const gpio_port_t gpio, const gpio_pin_t pin)
{
	_gpio_pin_t pinLL = GPIO_getLLPin(pin); 
	uint32_t reg = (pinLL & _GPIO_PIN_7) ? __GPIO_ReadCRH(GPIO_getLLPort(gpio)) : __GPIO_ReadCRL(GPIO_getLLPort(gpio));
	reg &= _GPIO_PIN_CNF_MODE_MASK(pinLL);
	return ((gpio_pin_parameter_t)(reg >> pinLL));
}

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
 * @retval None
 *
 */
void GPIO_SetPinParameters(const gpio_port_t gpio, gpio_pin_t pin, const gpio_pin_mode_t mode, const gpio_pin_config_t config);

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
 * @retval `DRIVER_SUCCESS`:  Configuration applied successfully.
 * @retval `DRIVER_FAIL`:     Invalid parameter (port, pin, or mode).
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
 * @retval `DRIVER_SUCCESS`:  Configuration applied successfully.
 * @retval `DRIVER_FAIL`:     Invalid parameter (port, pin, or configuration).
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
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_Init(const gpio_port_t gpio, gpio_config_t *const gpioConfig);

/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param[in] gpio GPIO Port (Refer `gpio_port_t`)
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: FailureGPIO_03_Driver_01_Types01_Types
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_Deinit(const gpio_port_t gpio, const gpio_pin_t pin);

/**
 * @brief Configures the On-board LED
 * @returns Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t OB_LED_Init(void);

/**
 * @brief Configures the LED connected to the specified GPIO Port and Pin
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] gpioConfig @ref gpio_config_t "GPIO Configuration Structure"
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
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
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
__STATIC_FORCEINLINE driver_status_t OB_LED_Deinit(void)
{
	return GPIO_Deinit(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}


#endif /* GPIO_H_ */