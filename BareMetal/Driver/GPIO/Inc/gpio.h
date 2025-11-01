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
typedef uint8_t gpio_port_t;
/** @brief GPIO Port A @def GPIO_PORT_A */
#define GPIO_PORT_A ((gpio_port_t)0x01)
/** @brief GPIO Port B @def GPIO_PORT_B */
#define GPIO_PORT_B ((gpio_port_t)0x02)
/** @brief GPIO Port C @def GPIO_PORT_C */
#define GPIO_PORT_C ((gpio_port_t)0x04)
/** @brief GPIO Port D @def GPIO_PORT_D */
#define GPIO_PORT_D ((gpio_port_t)0x08)
/** @brief GPIO Port E @def GPIO_PORT_E */
#define GPIO_PORT_E ((gpio_port_t)0x10)
/** @brief GPIO Port F @def GPIO_PORT_F */
#define GPIO_PORT_F ((gpio_port_t)0x20)
/** @brief GPIO Port G @def GPIO_PORT_G */
#define GPIO_PORT_G ((gpio_port_t)0x40)

/** @} */ // GPIO_03_Driver_01_Types_01_Ports

/*---------------------------------------------- Driver GPIO Pins ----------------------------------------------*/
/**
 * @brief    Driver GPIO Pins Declarations
 * @defgroup GPIO_03_Driver_01_Types_02_Pins Driver GPIO Pins
 * @ingroup  GPIO_03_Driver_01_Types
 *
 * @details
 * - These constants represent individual pins as bitmasks
 * - Thus, allowing multiple pins to be selected using bitwise OR operations
 *
 * @{
 */

/** @typedef GPIO pin bitmask type @typedef gpio_pin_t*/
typedef uint16_t gpio_pin_t;
/** @brief No pins bitmask @def GPIO_PIN_NONE */
#define GPIO_PIN_NONE ((gpio_pin_t)0x0000)
/** @brief Pin 0 bitmask @def GPIO_PIN_0 */
#define GPIO_PIN_0 ((gpio_pin_t)0x0001)
/** @brief Pin 1 bitmask @def GPIO_PIN_1 */
#define GPIO_PIN_1 ((gpio_pin_t)0x0002)
/** @brief Pin 2 bitmask @def GPIO_PIN_2 */
#define GPIO_PIN_2 ((gpio_pin_t)0x0004)
/** @brief Pin 3 bitmask @def GPIO_PIN_3 */
#define GPIO_PIN_3 ((gpio_pin_t)0x0008)
/** @brief Pin 4 bitmask @def GPIO_PIN_4 */
#define GPIO_PIN_4 ((gpio_pin_t)0x0010)
/** @brief Pin 5 bitmask @def GPIO_PIN_5 */
#define GPIO_PIN_5 ((gpio_pin_t)0x0020)
/** @brief Pin 6 bitmask @def GPIO_PIN_6 */
#define GPIO_PIN_6 ((gpio_pin_t)0x0040)
/** @brief Pin 7 bitmask @def GPIO_PIN_7 */
#define GPIO_PIN_7 ((gpio_pin_t)0x0080)
/** @brief Pin 8 bitmask @def GPIO_PIN_8 */
#define GPIO_PIN_8 ((gpio_pin_t)0x0100)
/** @brief Pin 9 bitmask @def GPIO_PIN_9 */
#define GPIO_PIN_9 ((gpio_pin_t)0x0200)
/** @brief Pin 10 bitmask @def GPIO_PIN_10 */
#define GPIO_PIN_10 ((gpio_pin_t)0x0400)
/** @brief Pin 11 bitmask @def GPIO_PIN_11 */
#define GPIO_PIN_11 ((gpio_pin_t)0x0800)
/** @brief Pin 12 bitmask @def GPIO_PIN_12 */
#define GPIO_PIN_12 ((gpio_pin_t)0x1000)
/** @brief Pin 13 bitmask @def GPIO_PIN_13 */
#define GPIO_PIN_13 ((gpio_pin_t)0x2000)
/** @brief Pin 14 bitmask @def GPIO_PIN_14 */
#define GPIO_PIN_14 ((gpio_pin_t)0x4000)
/** @brief Pin 15 bitmask @def GPIO_PIN_15 */
#define GPIO_PIN_15 ((gpio_pin_t)0x8000)
/** @brief All pins bitmask @def GPIO_PIN_ALL */
#define GPIO_PIN_ALL ((gpio_pin_t)0xFFFF)

/**
 * @note 	Use @ref GPIO_PIN_ALL "`GPIO_PIN_ALL`" for all pins
 * @note 	Use @ref GPIO_PIN_NONE "`GPIO_PIN_NONE`" for no pins
 *
 * @warning Not all pins are available on all ports - check device datasheet
 *
 * @}
 */
// GPIO_03_Driver_01_Types_02_Pins

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
typedef uint8_t gpio_pin_mode_t;

/** @brief Input mode @def GPIO_MODE_INPUT */
#define GPIO_MODE_INPUT ((gpio_pin_mode_t)0x00)

/** @brief Output mode, max speed 10 MHz @def GPIO_MODE_OUTPUT_10MHz */
#define GPIO_MODE_OUTPUT_10MHz ((gpio_pin_mode_t)0x01)

/** @brief Output mode, max speed 2 MHz @def GPIO_MODE_OUTPUT_2MHz */
#define GPIO_MODE_OUTPUT_2MHz ((gpio_pin_mode_t)0x02)

/** @brief Output mode, max speed 50 MHz @def GPIO_MODE_OUTPUT_50MHz */
#define GPIO_MODE_OUTPUT_50MHz ((gpio_pin_mode_t)0x03)

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

/** @brief GPIO Pin Configuration type @typedef gpio_pin_cnf_t */
typedef uint8_t gpio_pin_cnf_t;

/** @brief Analog input mode @def GPIO_PIN_CNF_IN_ANALOG */
#define GPIO_PIN_CNF_IN_ANALOG ((gpio_pin_cnf_t)0x00)

/** @brief Floating input (no pull-up/down) @def GPIO_PIN_CNF_IN_FLOAT */
#define GPIO_PIN_CNF_IN_FLOAT ((gpio_pin_cnf_t)0x01)

/**
 * @brief Input with pull-down resistor
 * @details Requires the corresponding bit in ODR to be set to 0.
 * @def GPIO_PIN_CNF_IN_PULL_DOWN
 */
#define GPIO_PIN_CNF_IN_PULL_DOWN ((gpio_pin_cnf_t)0x02)

/**
 * @brief Input with pull-up resistor
 * @details Requires the corresponding bit in ODR to be set to 1
 * @def GPIO_PIN_CNF_IN_PULL_UP
 */
#define GPIO_PIN_CNF_IN_PULL_UP ((gpio_pin_cnf_t)0x03)

/** @brief General purpose output push-pull @def GPIO_PIN_CNF_OUT_GP_PP */
#define GPIO_PIN_CNF_OUT_GP_PP ((gpio_pin_cnf_t)0x00)

/** @brief General purpose output open-drain @def GPIO_PIN_CNF_OUT_GP_OD */
#define GPIO_PIN_CNF_OUT_GP_OD ((gpio_pin_cnf_t)0x01)

/** @brief Alternate function output push-pull @def GPIO_PIN_CNF_OUT_AF_PP */
#define GPIO_PIN_CNF_OUT_AF_PP ((gpio_pin_cnf_t)0x02)

/** @brief Alternate function output open-drain @def GPIO_PIN_CNF_OUT_AF_OD */
#define GPIO_PIN_CNF_OUT_AF_OD ((gpio_pin_cnf_t)0x03)

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
typedef uint8_t gpio_exti_trigger_t;

/** @brief Trigger on falling edge @def GPIO_EXTI_TRIGGER_FALLING */
#define GPIO_EXTI_TRIGGER_FALLING ((gpio_exti_trigger_t)0x01)

/** @brief Trigger on rising edge @def GPIO_EXTI_TRIGGER_RISING */
#define GPIO_EXTI_TRIGGER_RISING ((gpio_exti_trigger_t)0x02)

/** @brief Trigger on both edges @def GPIO_EXTI_TRIGGER_BOTH */
#define GPIO_EXTI_TRIGGER_BOTH (GPIO_EXTI_TRIGGER_FALLING | GPIO_EXTI_TRIGGER_RISING)

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
#define GPIO_EXTI_PORT_A ((gpio_exti_port_t)0x00)

/** @brief EXTI source: GPIO Port B (0001) @def GPIO_EXTI_PORT_B */
#define GPIO_EXTI_PORT_B ((gpio_exti_port_t)0x01)

/** @brief EXTI source: GPIO Port C (0010) @def GPIO_EXTI_PORT_C */
#define GPIO_EXTI_PORT_C ((gpio_exti_port_t)0x02)

/** @brief EXTI source: GPIO Port D (0011) @def GPIO_EXTI_PORT_D */
#define GPIO_EXTI_PORT_D ((gpio_exti_port_t)0x03)

/** @brief EXTI source: GPIO Port E (0100) @def GPIO_EXTI_PORT_E */
#define GPIO_EXTI_PORT_E ((gpio_exti_port_t)0x04)

/** @brief EXTI source: GPIO Port F (0101) @def GPIO_EXTI_PORT_F */
#define GPIO_EXTI_PORT_F ((gpio_exti_port_t)0x05)

/** @brief EXTI source: GPIO Port G (0110) @def GPIO_EXTI_PORT_G */
#define GPIO_EXTI_PORT_G ((gpio_exti_port_t)0x06)

/** @} */ // GPIO_03_Driver_01_Types_06_EXTIPorts

/** @} */ // GPIO_03_Driver_01_Types

/**
 * @brief GPIO Pin Configuration Structure
 * @defgroup GPIO_03_Driver_02_Config Driver GPIO Configuration Structure
 * @ingroup  GPIO_03_Driver
 *
 * @{
 * @example
 * @code
 * // Configure Pin5 as output push-pull @2MHz
 * gpio_config_t led_config =
 * {
 *     .pin = GPIO_PIN_5,
 *     .mode = GPIO_MODE_OUTPUT_2MHz,
 *     .config = GPIO_PIN_CNF_OUT_GP_PP
 * };
 *
 * // Configure Pin13 as input with pull-up
 * gpio_config_t button_config =
 * {
 *     .pin = GPIO_PIN_13,
 *     .mode = GPIO_MODE_INPUT,
 *     .config = GPIO_PIN_CNF_IN_PULL_UP
 * };
 *
 * // Configure multiple pins as analog inputs
 * gpio_config_t adc_config =
 * {
 *     .pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2,
 *     .mode = GPIO_MODE_INPUT,
 *     .config = GPIO_PIN_CNF_IN_ANALOG
 * };
 * @endcode
 * @}
 */

/**
 * @addtogroup GPIO_03_Driver_02_Config
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
	 * @ref GPIO_MODE_INPUT: Input mode
	 * @ref GPIO_MODE_OUTPUT_10MHz: Output 10MHz
	 * @ref GPIO_MODE_OUTPUT_2MHz: Output 2MHz
	 * @ref GPIO_MODE_OUTPUT_50MHz: Output 50MHz
	 *
	 * @see @ref GPIO_03_Driver_01_Types_03_PinModes "GPIO Pin Modes"
	 */
	gpio_pin_mode_t mode : 2;

	/**
	 * @brief Pin electrical configuration
	 *
	 * @details
	 * @ref GPIO_MODE_INPUT "Input Modes:"
	 * @ref GPIO_PIN_CNF_IN_ANALOG: Analog input
	 * @ref GPIO_PIN_CNF_IN_FLOAT: Floating input
	 * @ref GPIO_PIN_CNF_IN_PULL_DOWN: Input with pull-down
	 * @ref GPIO_PIN_CNF_IN_PULL_UP: Input with pull-up
	 *
	 * @ref GPIO_MODE_OUTPUT_10MHz "Output Modes:"
	 * @ref GPIO_PIN_CNF_OUT_GP_PP: General purpose push-pull
	 * @ref GPIO_PIN_CNF_OUT_GP_OD: General purpose open-drain
	 * @ref GPIO_PIN_CNF_OUT_AF_PP: Alternate function push-pull
	 * @ref GPIO_PIN_CNF_OUT_AF_OD: Alternate function open-drain
	 *
	 * @warning Must be compatible with mode field
	 *
	 * @see @ref GPIO_03_Driver_01_Types_04_PinConfig "GPIO Pin Configuration"
	 */
	gpio_pin_cnf_t config : 2;
} gpio_config_t;

/** @} */ // GPIO_03_Driver_02_Config

/** @} */ // GPIO_03_Driver

// Board Specific Configuration
#ifdef STM32F103C8T6__
#define GPIO_PORT_OB_LED GPIO_PORT_C
#define GPIO_PIN_OB_LED GPIO_PIN_13
#endif /* STM32F103C8T6__ */

/**
 * @brief Sets the GPIO
 * @param gpioPort GPIO Port
 * @param gpioPin GPIO Pin
 * @note Atomicity
 */
__STATIC_FORCEINLINE void GPIO_Set(const gpio_port_t gpioPort, const gpio_pin_t gpioPin)
{
	GPIO_TypeDef *GPIOx = __GPIO_getPort__(gpioPort);
	if (GPIOx != NULL)
	{
		GPIOx->BSRR.REG |= gpioPin;
	}
}

/**
 * @brief Resets the GPIO
 * @param gpioPort GPIO Port
 * @param gpioPin GPIO Pin
 * @note Atomicity
 */
__STATIC_FORCEINLINE void GPIO_Reset(gpio_port_t gpioPort, gpio_pin_t gpioPin)
{
	GPIO_TypeDef *GPIOx = __GPIO_getPort__(gpioPort);
	if (GPIOx != NULL)
		GPIOx->BRR.REG |= gpioPin;
}

/**
 * @brief Toggles the GPIO
 * @param gpioPort GPIO Port
 * @param gpioPin GPIO Pin
 */
__STATIC_FORCEINLINE void GPIO_Toggle(gpio_port_t gpioPort, gpio_pin_t gpioPin)
{
	GPIO_TypeDef *GPIOx = __GPIO_getPort__(gpioPort);
	if (GPIOx != NULL)
		GPIOx->ODR.REG ^= gpioPin;
}

/**
 * @brief Retrieves the GPIO Status
 * @param gpioPort GPIO Port
 * @param gpioPin GPIO Pin
 */
__STATIC_FORCEINLINE uint8_t GPIO_Get(gpio_port_t gpioPort, gpio_pin_t gpioPin)
{
	GPIO_TypeDef *GPIOx = __GPIO_getPort__(gpioPort);
	if (GPIOx != NULL)
	{
		return ((uint8_t)((GPIOx->IDR.REG & gpioPin) ? (0x01) : (0x00)));
	}
}

/**
 * @brief Sets the On-board (OB) LED
 * @note OB LED is active LOW
 */
__STATIC_FORCEINLINE void OB_LED_Set(void)
{
	GPIO_Reset(GPIO_PORT_OB_LED, GPIO_PIN_OB_LED);
}

/**
 * @brief Resets the On-board (OB) LED
 * @note OB LED is active LOW
 */
__STATIC_FORCEINLINE void OB_LED_Reset(void)
{
	GPIO_Set(GPIO_PORT_OB_LED, GPIO_PIN_OB_LED);
}

/**
 * @brief Toggles the On-board (OB) LED
 * @note OB LED is active LOW
 */
__STATIC_FORCEINLINE void OB_LED_Toggle(void)
{
	GPIO_Toggle(GPIO_PORT_OB_LED, GPIO_PIN_OB_LED);
}

/*********************************************** Driver APIs ***********************************************/
/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param gpio GPIO Port (Refer `gpio_port_t`)
 * @param gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_Init(const gpio_port_t gpio, gpio_config_t *const gpioConfig);

/**
 * @brief Configures the LED connected to the specified GPIO Port and Pin
 * @param gpio GPIO Port (Refer `gpio_port_t`)
 * @param gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_LED_Init(const gpio_port_t gpio, gpio_config_t *gpioConfig);

/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param gpio GPIO Port (Refer `gpio_port_t`)
 * @param gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: FailureGPIO_03_Driver_01_Types01_Types
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_Deinit(const gpio_port_t gpio, gpio_config_t *const gpioConfig);

/**
 * @brief Configures the On-board LED
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t OB_LED_Init(void);

/**
 * @brief Deconfigures the On-board LED
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t OB_LED_Deinit(void);

#endif /* GPIO_H_ */