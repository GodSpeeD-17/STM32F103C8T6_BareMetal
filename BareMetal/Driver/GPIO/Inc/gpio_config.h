/**
 * @file gpio_config.h
 * @author Shrey Shah
 * @brief GPIO Configuration File
 * @version 1.1
 * @date 27-09-2025
 * @note Logs till v1.1:
 * @note - Aborted usage of `enums` as it consumes a lot of space
 * @note - Shifted to use combination of `typedef` & macros
 */
// Header Guards
#ifndef __GPIO_CONFIG_H__
#define __GPIO_CONFIG_H__

/*********************************************** Includes ***********************************************/
#include "reg_map.h"
#include "rcc.h"

/*********************************************** GPIO DataType Definitions ***********************************************/
typedef uint8_t gpio_port_t;
typedef uint16_t gpio_pin_t;
typedef uint8_t gpio_pin_mode_t;
typedef uint8_t gpio_pin_cnf_t;
typedef uint8_t gpio_exti_trigger_t;
typedef uint8_t gpio_exti_port_t;

/*********************************************** GPIO Port ***********************************************/
#define GPIO_PORT_A								((gpio_port_t) 0x00)
#define GPIO_PORT_B								((gpio_port_t) 0x01)
#define GPIO_PORT_C								((gpio_port_t) 0x02)
#define GPIO_PORT_D								((gpio_port_t) 0x03)
#define GPIO_PORT_E								((gpio_port_t) 0x04)
#define GPIO_PORT_F								((gpio_port_t) 0x05)
#define GPIO_PORT_G								((gpio_port_t) 0x06)

/*********************************************** GPIO Pin ***********************************************/
#define GPIO_PIN_0								((gpio_pin_t) 0x0001)
#define GPIO_PIN_1								((gpio_pin_t) 0x0002)
#define GPIO_PIN_2								((gpio_pin_t) 0x0004)
#define GPIO_PIN_3								((gpio_pin_t) 0x0008)
#define GPIO_PIN_4								((gpio_pin_t) 0x0010)
#define GPIO_PIN_5								((gpio_pin_t) 0x0020)
#define GPIO_PIN_6								((gpio_pin_t) 0x0040)
#define GPIO_PIN_7								((gpio_pin_t) 0x0080)
#define GPIO_PIN_8								((gpio_pin_t) 0x0100)
#define GPIO_PIN_9								((gpio_pin_t) 0x0200)
#define GPIO_PIN_10								((gpio_pin_t) 0x0400)
#define GPIO_PIN_11								((gpio_pin_t) 0x0800)
#define GPIO_PIN_12								((gpio_pin_t) 0x1000)
#define GPIO_PIN_13								((gpio_pin_t) 0x2000)
#define GPIO_PIN_14								((gpio_pin_t) 0x4000)
#define GPIO_PIN_15								((gpio_pin_t) 0x8000)
#define GPIO_PIN_ALL							((gpio_pin_t) 0xFFFF)
#define GPIO_PIN_NONE							((gpio_pin_t) 0x0000) 

/*********************************************** GPIO Pin Mode ***********************************************/
#define	GPIO_MODE_INPUT 						((gpio_pin_mode_t) 0x00)
#define	GPIO_MODE_OUTPUT_10MHz 					((gpio_pin_mode_t) 0x01)
#define	GPIO_MODE_OUTPUT_2MHz 					((gpio_pin_mode_t) 0x02)
#define	GPIO_MODE_OUTPUT_50MHz 					((gpio_pin_mode_t) 0x03)

/*********************************************** GPIO Pin Configuration ***********************************************/
#define GPIO_PIN_CNF_IN_ANALOG 					((gpio_pin_cnf_t) 0x00)
#define GPIO_PIN_CNF_IN_FLOAT 					((gpio_pin_cnf_t) 0x01)
#define GPIO_PIN_CNF_IN_PULL_DOWN 				((gpio_pin_cnf_t) 0x02)
#define GPIO_PIN_CNF_IN_PULL_UP 				((gpio_pin_cnf_t) 0x03)
#define GPIO_PIN_CNF_OUT_GP_PP 					((gpio_pin_cnf_t) 0x00)
#define GPIO_PIN_CNF_OUT_GP_OD 					((gpio_pin_cnf_t) 0x01)
#define GPIO_PIN_CNF_OUT_AF_PP 					((gpio_pin_cnf_t) 0x02)
#define GPIO_PIN_CNF_OUT_AF_OD 					((gpio_pin_cnf_t) 0x03)

/*********************************************** GPIO Pin Interrupt Trigger ***********************************************/
#define GPIO_EXTI_TRIGGER_FALLING 				((gpio_exti_trigger_t) 0x01)
#define GPIO_EXTI_TRIGGER_RISING 				((gpio_exti_trigger_t) 0x02)
#define GPIO_EXTI_TRIGGER_BOTH 					(GPIO_EXTI_TRIGGER_FALLING | GPIO_EXTI_TRIGGER_RISING)

/*********************************************** GPIO Port Interrupt Trigger ***********************************************/
#define GPIO_EXTI_PORT_A 						((gpio_exti_port_t) 0x00)
#define GPIO_EXTI_PORT_B 						((gpio_exti_port_t) 0x01)
#define GPIO_EXTI_PORT_C 						((gpio_exti_port_t) 0x02)
#define GPIO_EXTI_PORT_D 						((gpio_exti_port_t) 0x03)
#define GPIO_EXTI_PORT_E 						((gpio_exti_port_t) 0x04)
#define GPIO_EXTI_PORT_F 						((gpio_exti_port_t) 0x05)
#define GPIO_EXTI_PORT_G 						((gpio_exti_port_t) 0x06)

/*********************************************** GPIO Configuration Structure ***********************************************/
typedef struct
{
	// GPIO Pin
	gpio_pin_t pin;
	// GPIO Mode
	gpio_pin_mode_t mode : 2;
	// GPIO Configuration
	gpio_pin_cnf_t config : 2;
} gpio_config_t;

/*********************************************** Extern Mapping ***********************************************/
extern const GPIO_TypeDef* const __gpioDriverMapping__[7];

/*********************************************** Helper APIs ***********************************************/
/**
 * @brief Enables the clock for the specified GPIO port
 * @param thisPort GPIO Port Enumeration `gpio_port_t`
 */
__STATIC_FORCEINLINE void __GPIO_enableClock__(const gpio_port_t thisPort)
{
	// Enable Clock for GPIO Port
	RCC->APB2ENR.REG |= (1 << (2 + thisPort));
}

/**
 * @brief Disables the clock for the specified GPIO port
 * @param thisPort GPIO Port Enumeration `gpio_port_t`
 */
__STATIC_FORCEINLINE void __GPIO_disableClock__(const gpio_port_t thisPort)
{
	// Disables Clock for GPIO Port
	RCC->APB2ENR.REG &= ~(1 << (2 + thisPort));
}

/**
 * @brief Retrieves the GPIO Port structure based on port enumeration
 * @param thisPort GPIO Port Enumeration `gpio_port_t` 
 * @return GPIO_TypeDef* Pointer to the GPIO Port structure
 */
__STATIC_FORCEINLINE GPIO_TypeDef* __GPIO_getPort__(const gpio_port_t thisPort){
	// Return Pointer to GPIO Port Structure
	return __gpioDriverMapping__[thisPort];
}

/**
 * @brief Retrieves the pin position (0-15) based on the provided pin mask
 * @param pinMask Mask representing the specific GPIO pin
 * @return GPIO Pin Number
 */
__STATIC_FORCEINLINE uint8_t __GPIO_getPin__(const gpio_pin_t pinMask)
{
	// Retrieve Pin Position (0-15)
	return ((uint8_t) ((pinMask == GPIO_PIN_NONE)? (0x00) : (__builtin_ctz(pinMask))));
}

/**
 * @brief Updates the control register (CRL or CRH) for a specific GPIO pin based on the provided configuration
 * @param pinMask Mask representing the specific GPIO pin to be configured
 * @param gpioODRReg Pointer to the output data register (ODR) to be updated
 * @note Pass only single pin not logical combination of Pins
 */
__STATIC_FORCEINLINE void __GPIO_resetPullConfig__(const gpio_pin_t pinMask, uint32_t *gpioODRReg)
{
	*gpioODRReg &= ~(pinMask);
}

/*********************************************** Driver APIs ***********************************************/
/**
 * @brief Updates the control register (CRL or CRH) for a specific GPIO pin based on the provided configuration
 * @param pinMask Mask representing the specific GPIO pin to be configured
 * @param gpioMode GPIO Mode Enumeration `gpio_pin_mode_t`
 * @param gpioCnf GPIO Configuration Enumeration `gpio_pin_cnf_t`
 * @param gpioCtrlReg Pointer to the control register (CRL or CRH) to be updated
 * @note Pass only single pin not logical combination of Pins
 */
void __GPIO_updateCtrlRegister__(const gpio_pin_t pinMask, const gpio_pin_mode_t gpioMode, gpio_pin_cnf_t gpioCnf, uint32_t *gpioCtrlReg);

/**
 * @brief Resets the control register (CRL or CRH) for a specific GPIO pin based on the provided configuration
 * @param pinMask Mask representing the specific GPIO pin to be configured
 * @param gpioCtrlReg Pointer to the control register (CRL or CRH) to be updated
 * @note Pass only single pin not logical combination of Pins
 */
void __GPIO_resetCtrlRegister__(const gpio_pin_t pinMask, uint32_t *gpioCtrlReg);

/**
 * @brief Updates the control register (CRL or CRH) for a specific GPIO pin based on the provided configuration
 * @param pinMask Mask representing the specific GPIO pin to be configured
 * @param gpioCnf GPIO Configuration Enumeration `gpio_pin_cnf_t`
 * @param gpioODRReg Pointer to the output data register (ODR) to be updated
 * @note Pass only single pin not logical combination of Pins
 */
void __GPIO_updatePullConfig__(const gpio_pin_t pinMask, gpio_pin_cnf_t gpioCnf, uint32_t *gpioODRReg);

#endif /* __GPIO_CONFIG_H__ */