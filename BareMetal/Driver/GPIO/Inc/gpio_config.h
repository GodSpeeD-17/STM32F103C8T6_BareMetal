// Header Guards
#ifndef __GPIO_CONFIG_H__
#define __GPIO_CONFIG_H__

/*********************************************** Includes ***********************************************/
#include "reg_map.h"
#include "rcc.h"


/*********************************************** GPIO Enum MACROS ***********************************************/
/**
 * @brief GPIO Port Enumeration
 * @note Used to specify the port of a GPIO
 */
typedef enum {
	// GPIO Port A
	GPIO_PORT_A = (uint8_t) 0x00,
	// GPIO Port B
	GPIO_PORT_B = (uint8_t) 0x01,
	// GPIO Port C
	GPIO_PORT_C = (uint8_t) 0x02,
	// GPIO Port D
	GPIO_PORT_D = (uint8_t) 0x03,
	// GPIO Port E
	GPIO_PORT_E = (uint8_t) 0x04,
	// GPIO Port F
	GPIO_PORT_F = (uint8_t) 0x05,
	// GPIO Port G
	GPIO_PORT_G = (uint8_t) 0x06,
	// On-board (OB) LED Port
	GPIO_PORT_OB_LED = GPIO_PORT_C
} gpio_port_t;

/**
 * @brief GPIO Pin Enumeration
 * @note Used to specify the pin number of a GPIO
 */
typedef enum {
	GPIO_PIN_0 = (uint16_t) 0x0001,
	GPIO_PIN_1 = (uint16_t) 0x0002,
	GPIO_PIN_2 = (uint16_t) 0x0004,
	GPIO_PIN_3 = (uint16_t) 0x0008,
	GPIO_PIN_4 = (uint16_t) 0x0010,
	GPIO_PIN_5 = (uint16_t) 0x0020,
	GPIO_PIN_6 = (uint16_t) 0x0040,
	GPIO_PIN_7 = (uint16_t) 0x0080,
	GPIO_PIN_8 = (uint16_t) 0x0100,
	GPIO_PIN_9 = (uint16_t) 0x0200,
	GPIO_PIN_10 = (uint16_t) 0x0400,
	GPIO_PIN_11 = (uint16_t) 0x0800,
	GPIO_PIN_12 = (uint16_t) 0x1000,
	GPIO_PIN_13 = (uint16_t) 0x2000,
	GPIO_PIN_14 = (uint16_t) 0x4000,
	GPIO_PIN_15 = (uint16_t) 0x8000,
	GPIO_PIN_ALL = (uint16_t) 0xFFFF,
	GPIO_PIN_OB_LED = GPIO_PIN_13
} gpio_pin_t;

/**
 * @brief GPIO Mode Enumeration
 * @brief Used to specify the mode of a GPIO
 */
typedef enum {
	// GPIO as Input
	GPIO_MODE_INPUT = (uint8_t) 0x00,
	// GPIO as Output @10MHz
	GPIO_MODE_OUTPUT_10MHz = (uint8_t) 0x01,
	// GPIO as Output @2MHz
	GPIO_MODE_OUTPUT_2MHz = (uint8_t) 0x02,
	// GPIO as Output @50MHz
	GPIO_MODE_OUTPUT_50MHz = (uint8_t) 0x03
} gpio_mode_t;

/**
 * @brief GPIO Pin Configuration Enumeration
 * @note Configuration options vary based on whether the pin is set as input or output
 */
typedef enum {
	GPIO_PIN_CNF_IN_ANALOG = (uint8_t) 0x00,
	GPIO_PIN_CNF_IN_FLOAT = (uint8_t) 0x01,
	GPIO_PIN_CNF_IN_PULL_DOWN = (uint8_t) 0x02,
	GPIO_PIN_CNF_IN_PULL_UP = (uint8_t) 0x03,
	GPIO_PIN_CNF_OUT_GP_PP = (uint8_t) 0x00,
	GPIO_PIN_CNF_OUT_GP_OD = (uint8_t) 0x01,
	GPIO_PIN_CNF_OUT_AF_PP = (uint8_t) 0x02,
	GPIO_PIN_CNF_OUT_AF_OD = (uint8_t) 0x03
} gpio_pin_cnf_t;

/**
 * @brief External Interrupt Trigger Enumeration
 * @note Defines the Interrupt Trigger
 */
typedef enum {
	GPIO_EXTI_TRIGGER_FALLING = (uint8_t) 0x01,
	GPIO_EXTI_TRIGGER_RISING = (uint8_t) 0x02,
	GPIO_EXTI_TRIGGER_BOTH = (GPIO_EXTI_TRIGGER_FALLING | GPIO_EXTI_TRIGGER_RISING)
} gpio_exti_trigger_t;

/**
 * @brief External Interrupt Source Port Enumeration
 * @note Configures the Source Port for Interrupt at a particular pin
 */
typedef enum {
	GPIO_EXTI_PORT_A = (uint8_t) 0x00,
	GPIO_EXTI_PORT_B = (uint8_t) 0x01,
	GPIO_EXTI_PORT_C = (uint8_t) 0x02,
	GPIO_EXTI_PORT_D = (uint8_t) 0x03,
	GPIO_EXTI_PORT_E = (uint8_t) 0x04,
	GPIO_EXTI_PORT_F = (uint8_t) 0x05,
	GPIO_EXTI_PORT_G = (uint8_t) 0x06
} gpio_exti_port_t;

/*********************************************** GPIO Configuration Structure ***********************************************/
typedef struct {
	// GPIO Pin
	gpio_pin_t pin: 16;
	// GPIO Mode
	gpio_mode_t mode: 2;
	// GPIO Configuration
	gpio_pin_cnf_t config: 2;
} gpio_config_t;

/*********************************************** Helper APIs ***********************************************/
/**
 * @brief Enables the clock for the specified GPIO port
 * @param thisPort GPIO Port Enumeration `gpio_port_t`
 */
__STATIC_INLINE__ void __GPIO_enableClock__(const gpio_port_t thisPort){
	// Enable Clock for GPIO Port
	RCC->APB2ENR.REG |= (1 << (2 + thisPort));
}

/**
 * @brief Disables the clock for the specified GPIO port
 * @param thisPort GPIO Port Enumeration `gpio_port_t`
 */
__STATIC_INLINE__ void __GPIO_disableClock__(const gpio_port_t thisPort){
	// Disables Clock for GPIO Port
	RCC->APB2ENR.REG &= ~(1 << (2 + thisPort));
}

/**
 * @brief Retrieves the pin position (0-15) based on the provided pin mask
 * @param pinMask Mask representing the specific GPIO pin
 * @return GPIO Pin Number
 */
__STATIC_INLINE__ uint8_t __GPIO_getPin__(const gpio_pin_t pinMask){
	// Retrieve Pin Position (0-15)
	if(pinMask == 0x00)
		return (uint8_t) 0x00;
	else
		return (uint8_t) __builtin_ctz(pinMask);
}

/**
 * @brief Updates the control register (CRL or CRH) for a specific GPIO pin based on the provided configuration
 * @param pinMask Mask representing the specific GPIO pin to be configured
 * @param gpioODRReg Pointer to the output data register (ODR) to be updated
 * @note Pass only single pin not logical combination of Pins 
 */
__STATIC_INLINE__ void __GPIO_resetPullConfig__(const gpio_pin_t pinMask, uint32_t* gpioODRReg){
	*gpioODRReg &= ~(pinMask);
}

/*********************************************** Driver APIs ***********************************************/
/**
 * @brief Retrieves the GPIO Port structure based on port enumeration
 * @param thisPort GPIO Port Enumeration `gpio_port_t` 
 * @return GPIO_TypeDef* Pointer to the GPIO Port structure
 */
GPIO_TypeDef* __GPIO_getPort__(const gpio_port_t thisPort);

/**
 * @brief Updates the control register (CRL or CRH) for a specific GPIO pin based on the provided configuration
 * @param pinMask Mask representing the specific GPIO pin to be configured
 * @param gpioMode GPIO Mode Enumeration `gpio_mode_t`
 * @param gpioCnf GPIO Configuration Enumeration `gpio_pin_cnf_t`
 * @param gpioCtrlReg Pointer to the control register (CRL or CRH) to be updated
 * @note Pass only single pin not logical combination of Pins 
 */
void __GPIO_updateCtrlRegister__(const gpio_pin_t pinMask, gpio_mode_t gpioMode, gpio_pin_cnf_t gpioCnf, uint32_t* gpioCtrlReg);

/**
 * @brief Resets the control register (CRL or CRH) for a specific GPIO pin based on the provided configuration
 * @param pinMask Mask representing the specific GPIO pin to be configured
 * @param gpioCtrlReg Pointer to the control register (CRL or CRH) to be updated
 * @note Pass only single pin not logical combination of Pins
 */
void __GPIO_resetCtrlRegister__(const gpio_pin_t pinMask, uint32_t* gpioCtrlReg);

/**
 * @brief Updates the control register (CRL or CRH) for a specific GPIO pin based on the provided configuration
 * @param pinMask Mask representing the specific GPIO pin to be configured
 * @param gpioCnf GPIO Configuration Enumeration `gpio_pin_cnf_t`
 * @param gpioODRReg Pointer to the output data register (ODR) to be updated
 * @note Pass only single pin not logical combination of Pins 
 */
void __GPIO_updatePullConfig__(const gpio_pin_t pinMask, gpio_pin_cnf_t gpioCnf, uint32_t* gpioODRReg);

#endif /* __GPIO_CONFIG_H__ */