// Header Guards
#ifndef __GPIO_CONFIG_H__
#define __GPIO_CONFIG_H__

/*********************************************** Includes ***********************************************/
#include "reg_map.h"
#include "rcc.h"

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