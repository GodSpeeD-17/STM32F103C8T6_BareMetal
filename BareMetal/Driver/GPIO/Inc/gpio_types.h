/**
 * @file    gpio_types.h
 * @author  Shrey Shah
 * @brief   GPIO Data Types and Configuration Definitions
 * @version v1.2
 * @date    21-10-2025
 *
 */

// Header Guards
#ifndef GPIO_TYPES_H_
#define GPIO_TYPES_H_

/*---------------------------------------------- Includes ----------------------------------------------*/
/** 
 * @brief For register mapping base types
 * @include Test
 */
#include "stm32f1xx.h"
/** 
 * @brief For Reset and Clock Control dependenciess 
 */
#include "rcc.h"

/*---------------------------------------------- GPIO Port Definitions ----------------------------------------------*/

/**
 * @brief    API used GPIO ports on STM32F103C8T6
 * @defgroup 02_GPIO_Ports GPIO Port
 * @ingroup  GPIO
 * @section GPIO Ports: API
 * @details These constants identify specific GPIO ports. 
 * 			Not all ports may be available on all STM32F1xx variants. 
 * 			STM32F103C8T6 has ports A, B, and C fully available.
 * 
 * @see STM32F103C8T6 Datasheet - Section 4 Memory mapping
 * 
 * @{
 */
/** @typedef gpio_port_t GPIO port identifier type */
typedef uint8_t  	   gpio_port_t;
/** @brief GPIO Port A */
#define GPIO_PORT_A    ((gpio_port_t) 0x00)
/** @brief GPIO Port B */
#define GPIO_PORT_B    ((gpio_port_t) 0x01)
/** @brief GPIO Port C */
#define GPIO_PORT_C    ((gpio_port_t) 0x02)
/** @brief GPIO Port D */
#define GPIO_PORT_D    ((gpio_port_t) 0x03)
/** @brief GPIO Port E */
#define GPIO_PORT_E    ((gpio_port_t) 0x04)
/** @brief GPIO Port F */
#define GPIO_PORT_F    ((gpio_port_t) 0x05)
/** @brief GPIO Port G */
#define GPIO_PORT_G    ((gpio_port_t) 0x06)

/** @} */ // 02_GPIO_Ports

/*---------------------------------------------- GPIO Pin Definitions ----------------------------------------------*/
/**
 * @brief    GPIO Pin Selection
 * @ingroup  GPIO
 * @defgroup 03_GPIO_Pins GPIO Pins
 * 
 * @details These constants represent individual pins as bitmasks. 
 * 			Thus, allowing multiple pins to be selected using bitwise OR operations.
 * 
 * @note 	Use `GPIO_PIN_ALL` for all pins 
 * @note 	Use `GPIO_PIN_NONE` for no pins
 * 
 * @warning Not all pins are available on all ports - check device datasheet
 * @{
 */
/** @typedef GPIO pin bitmask type */
typedef uint16_t				gpio_pin_t;
 /** @brief No pins bitmask */
#define GPIO_PIN_NONE			((gpio_pin_t) 0x0000)
/** @brief Pin 0 bitmask */
#define GPIO_PIN_0				((gpio_pin_t) 0x0001)
/** @brief Pin 1 bitmask */
#define GPIO_PIN_1				((gpio_pin_t) 0x0002)
/** @brief Pin 2 bitmask */
#define GPIO_PIN_2				((gpio_pin_t) 0x0004)
/** @brief Pin 3 bitmask */
#define GPIO_PIN_3				((gpio_pin_t) 0x0008)
/** @brief Pin 4 bitmask */
#define GPIO_PIN_4				((gpio_pin_t) 0x0010)
/** @brief Pin 5 bitmask */
#define GPIO_PIN_5				((gpio_pin_t) 0x0020)
/** @brief Pin 6 bitmask */
#define GPIO_PIN_6				((gpio_pin_t) 0x0040)
/** @brief Pin 7 bitmask */
#define GPIO_PIN_7				((gpio_pin_t) 0x0080)
/** @brief Pin 8 bitmask */
#define GPIO_PIN_8				((gpio_pin_t) 0x0100)
/** @brief Pin 9 bitmask */
#define GPIO_PIN_9				((gpio_pin_t) 0x0200)
/** @brief Pin 10 bitmask */
#define GPIO_PIN_10				((gpio_pin_t) 0x0400)
/** @brief Pin 11 bitmask */
#define GPIO_PIN_11				((gpio_pin_t) 0x0800)
/** @brief Pin 12 bitmask */
#define GPIO_PIN_12				((gpio_pin_t) 0x1000)
/** @brief Pin 13 bitmask */
#define GPIO_PIN_13				((gpio_pin_t) 0x2000)
/** @brief Pin 14 bitmask */
#define GPIO_PIN_14				((gpio_pin_t) 0x4000)
/** @brief Pin 15 bitmask */
#define GPIO_PIN_15				((gpio_pin_t) 0x8000)
/** @brief All pins bitmask */
#define GPIO_PIN_ALL			((gpio_pin_t) 0xFFFF)

/** @} */ // 03_GPIO_Pins

/*---------------------------------------------- GPIO Pin Mode Definitions ----------------------------------------------*/
/**
 * @brief    GPIO pin operating modes
 * @ingroup  03_GPIO_Pins
 * @defgroup 03_01_GPIO_PinModes GPIO Pin Modes
 * 
 * @details 
 * - The constants define the operational mode of GPIO Pins (@ref 03_GPIO_Pins) 
 * - The mode determines whether the pin is input/output and the output speed
 * 
 * @note Output speed affects both slew rate and power consumption
 * @see Reference Manual RM0008 - Section 9.1.1 GPIO port configuration
 * 
 * @{
 */
/** @typedef gpio_pin_mode_t @brief GPIO Pin Mode */
typedef uint8_t  				gpio_pin_mode_t;
/** @brief Input mode */
#define GPIO_MODE_INPUT			((gpio_pin_mode_t) 0x00)
/** @brief Output mode, max speed 10 MHz */
#define GPIO_MODE_OUTPUT_10MHz	((gpio_pin_mode_t) 0x01)
/** @brief Output mode, max speed 2 MHz */
#define GPIO_MODE_OUTPUT_2MHz	((gpio_pin_mode_t) 0x02)
/** @brief Output mode, max speed 50 MHz */
#define GPIO_MODE_OUTPUT_50MHz	((gpio_pin_mode_t) 0x03)

/** @} */ // 03_01_GPIO_PinModes

/*---------------------------------------------- GPIO Pin Configuration Definitions ----------------------------------------------*/
/**
 * @brief    GPIO pin configuration settings
 * @ingroup  03_GPIO_Pins
 * @defgroup 03_02_GPIO_PinConfig GPIO Pin Configurations
 * 
 * @details 
 * - The constants define the electrical configuration of GPIO_Pins
 * - The configuration must be compatible with the selected mode
 * 
 * @warning Configuration must match mode:
 *          - Input modes: Use `GPIO_PIN_CNF_IN_*`
 *          - Output modes: Use `GPIO_PIN_CNF_OUT_*`
 * @see Reference Manual RM0008 - Section 9.1.1 GPIO port configuration
 * 
 * @{
 */
/** @typedef gpio_pin_cnf_t GPIO Pin Configuration type */
typedef uint8_t  				  gpio_pin_cnf_t;
/** @brief Analog input mode */
#define GPIO_PIN_CNF_IN_ANALOG    ((gpio_pin_cnf_t) 0x00)
/** @brief Floating input (no pull-up/down) */
#define GPIO_PIN_CNF_IN_FLOAT     ((gpio_pin_cnf_t) 0x01)
/** @brief Input with pull-down resistor */
#define GPIO_PIN_CNF_IN_PULL_DOWN ((gpio_pin_cnf_t) 0x02)
/** @brief Input with pull-up resistor */
#define GPIO_PIN_CNF_IN_PULL_UP   ((gpio_pin_cnf_t) 0x03)
/** @brief General purpose output push-pull */
#define GPIO_PIN_CNF_OUT_GP_PP    ((gpio_pin_cnf_t) 0x00)
/** @brief General purpose output open-drain */
#define GPIO_PIN_CNF_OUT_GP_OD    ((gpio_pin_cnf_t) 0x01)
/** @brief Alternate function output push-pull */
#define GPIO_PIN_CNF_OUT_AF_PP    ((gpio_pin_cnf_t) 0x02)
/** @brief Alternate function output open-drain */
#define GPIO_PIN_CNF_OUT_AF_OD    ((gpio_pin_cnf_t) 0x03)

/** @} */ // 03_02_GPIO_PinConfig

/*---------------------------------------------- GPIO External Interrupt Trigger Definitions ----------------------------------------------*/

/**
 * @brief    External interrupt trigger configurations
 * @defgroup 07_GPIO_EXTITriggers EXTI Trigger Types
 * @ingroup  GPIO
 * 
 * @details These constants define when an external interrupt should trigger.
 *          Used with EXTI configuration functions.
 * 
 * @see Reference Manual RM0008 - Section 10.2.3 EXTI rising/falling trigger selection
 * @{
 */
/** @brief EXTI trigger type */
typedef uint8_t						gpio_exti_trigger_t;
/** @brief Trigger on falling edge */
#define GPIO_EXTI_TRIGGER_FALLING  ((gpio_exti_trigger_t) 0x01)
/** @brief Trigger on rising edge */
#define GPIO_EXTI_TRIGGER_RISING   ((gpio_exti_trigger_t) 0x02)
/** @brief Trigger on both edges */
#define GPIO_EXTI_TRIGGER_BOTH     (GPIO_EXTI_TRIGGER_FALLING | GPIO_EXTI_TRIGGER_RISING)

/** 
 * @}
 */ // 07_GPIO_EXTITriggers

/*---------------------------------------------- GPIO EXTI Port Source Definitions ----------------------------------------------*/

/**
 * @brief    EXTI port source selections
 * @defgroup 08_GPIO_EXTIPorts EXTI Port Sources
 * @ingroup  GPIO
 * 
 * @details These constants define which GPIO port is connected to EXTI lines.
 *          Used to configure EXTI source selection in AFIO registers.
 * 
 * @see Reference Manual RM0008 - Section 9.2.5 AFIO_EXTICR1-4 registers
 * @{
 */
/** @brief EXTI port source type */
typedef uint8_t  			gpio_exti_port_t;
/** @brief EXTI source: GPIO Port A */
#define GPIO_EXTI_PORT_A  ((gpio_exti_port_t) 0x00)
/** @brief EXTI source: GPIO Port B */
#define GPIO_EXTI_PORT_B  ((gpio_exti_port_t) 0x01)
/** @brief EXTI source: GPIO Port C */
#define GPIO_EXTI_PORT_C  ((gpio_exti_port_t) 0x02)
/** @brief EXTI source: GPIO Port D */
#define GPIO_EXTI_PORT_D  ((gpio_exti_port_t) 0x03)
/** @brief EXTI source: GPIO Port E */
#define GPIO_EXTI_PORT_E  ((gpio_exti_port_t) 0x04)
/** @brief EXTI source: GPIO Port F */
#define GPIO_EXTI_PORT_F  ((gpio_exti_port_t) 0x05)
/** @brief EXTI source: GPIO Port G */
#define GPIO_EXTI_PORT_G  ((gpio_exti_port_t) 0x06)

/** 
 * @}
 */ // 08_GPIO_EXTIPorts

/*---------------------------------------------- GPIO Configuration Structure ----------------------------------------------*/

/*---------------------------------------------- GPIO Configuration Structure ----------------------------------------------*/

/**
 * @brief    GPIO configuration data structures
 * @defgroup 09_GPIO_Config GPIO Configuration Structure
 * @ingroup  GPIO
 * @{
 */

/**
 * @brief GPIO Pin Configuration Structure
 * 
 * @details This structure contains all necessary configuration parameters
 *          to initialize a GPIO pin. Used by GPIO initialization functions.
 * 
 * @note The mode and config fields use bitfields to save memory
 * 
 * @var gpio_config_t::pin
 * @brief Pin selection bitmask
 * 
 * **Allowed values:**
 * - GPIO_PIN_0 to GPIO_PIN_15 for individual pins
 * - GPIO_PIN_ALL for all pins
 * - GPIO_PIN_NONE for no pins
 * - Bitwise OR of multiple pins (e.g., GPIO_PIN_5 | GPIO_PIN_6)
 * 
 * @see @ref GPIO_Pins
 * 
 * @var gpio_config_t::mode  
 * @brief Pin operating mode and speed
 * 
 * **Allowed values:**
 * | Value | Constant | Description |
 * |-------|----------|-------------|
 * | 0x00  | GPIO_MODE_INPUT | Input mode |
 * | 0x01  | GPIO_MODE_OUTPUT_10MHz | Output mode, max speed 10 MHz |
 * | 0x02  | GPIO_MODE_OUTPUT_2MHz | Output mode, max speed 2 MHz |
 * | 0x03  | GPIO_MODE_OUTPUT_50MHz | Output mode, max speed 50 MHz |
 * 
 * @see @ref GPIO_Modes
 * 
 * @var gpio_config_t::config
 * @brief Pin electrical configuration
 * 
 * **Allowed values depend on mode:**
 * 
 * **For Input modes (GPIO_MODE_INPUT):**
 * | Value | Constant | Description |
 * |-------|----------|-------------|
 * | 0x00  | GPIO_PIN_CNF_IN_ANALOG | Analog input mode |
 * | 0x01  | GPIO_PIN_CNF_IN_FLOAT | Floating input (no pull-up/down) |
 * | 0x02  | GPIO_PIN_CNF_IN_PULL_DOWN | Input with pull-down resistor |
 * | 0x03  | GPIO_PIN_CNF_IN_PULL_UP | Input with pull-up resistor |
 * 
 * **For Output modes (GPIO_MODE_OUTPUT_*):**
 * | Value | Constant | Description |
 * |-------|----------|-------------|
 * | 0x00  | GPIO_PIN_CNF_OUT_GP_PP | General purpose output push-pull |
 * | 0x01  | GPIO_PIN_CNF_OUT_GP_OD | General purpose output open-drain |
 * | 0x02  | GPIO_PIN_CNF_OUT_AF_PP | Alternate function output push-pull |
 * | 0x03  | GPIO_PIN_CNF_OUT_AF_OD | Alternate function output open-drain |
 * 
 * @see @ref GPIO_Configurations
 * 
 * @warning Mode and configuration must be compatible:
 * - Input modes require GPIO_PIN_CNF_IN_* configurations
 * - Output modes require GPIO_PIN_CNF_OUT_* configurations
 * 
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
 */
typedef struct
{
	/**
	 * @brief Pin selection bitmask
	 * 
	 * `GPIO_PIN_0`: Pin 0
	 * `GPIO_PIN_1`: Pin 1
	 * ...
	 * `GPIO_PIN_15`: Pin 15
	 * `GPIO_PIN_ALL`: All pins
	 * `GPIO_PIN_NONE`: No pins
	 * 
	 * @example
	 * @code
	 * .pin = `GPIO_PIN_5` | `GPIO_PIN_6`;
	 * @endcond
	 * @ref 04_GPIO_Pins
	 */
	gpio_pin_t pin;
	
	/**
	 * @brief Pin operating mode and speed
	 * 
	 * GPIO_MODE_INPUT       - Input mode
	 * GPIO_MODE_OUTPUT_10MHz - Output 10MHz
	 * GPIO_MODE_OUTPUT_2MHz  - Output 2MHz
	 * GPIO_MODE_OUTPUT_50MHz - Output 50MHz
	 * 
	 * @ref 03_01_GPIO_PinModes
	 */
	gpio_pin_mode_t mode : 2;
	
	/**
	 * @brief Pin electrical configuration
	 * 
	 * Input modes (`GPIO_MODE_INPUT`):
	 * - `GPIO_PIN_CNF_IN_ANALOG`    - Analog input
	 * - `GPIO_PIN_CNF_IN_FLOAT`     - Floating input
	 * - `GPIO_PIN_CNF_IN_PULL_DOWN` - Input with pull-down
	 * - `GPIO_PIN_CNF_IN_PULL_UP`   - Input with pull-up
	 * 
	 * Output modes (`GPIO_MODE_OUTPUT_*`):
	 * - `GPIO_PIN_CNF_OUT_GP_PP` - General purpose push-pull
	 * - `GPIO_PIN_CNF_OUT_GP_OD` - General purpose open-drain
	 * - `GPIO_PIN_CNF_OUT_AF_PP` - Alternate function push-pull
	 * - `GPIO_PIN_CNF_OUT_AF_OD` - Alternate function open-drain
	 * 
	 * @warning Must be compatible with mode field
	 */
	gpio_pin_cnf_t config : 2;
} gpio_config_t;

/** 
 * @}
 */ // 09_GPIO_Config

#endif /* GPIO_TYPES_H_ */
