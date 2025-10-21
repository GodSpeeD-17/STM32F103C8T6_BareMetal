/**
 * @file gpio_config.h
 * @author Shrey Shah
 * @brief GPIO Configuration File
 * @version 1.1
 * @date 27-09-2025
 * @note Logs till v1.1:
 * @note - Aborted usage of `enums` as it consumes a lot of space
 * @note - Shifted to use combination of `typedef` & macros
 * @ingroup GPIO
 */
// Header Guards
#ifndef GPIO_CONFIG_H_
#define GPIO_CONFIG_H_

/*********************************************** Includes ***********************************************/
#include "gpio_types.h"

/*********************************************** Helper APIs ***********************************************/
/**
 * @brief Enable the clock for the specified GPIO port
 * @param gpioPort GPIO Port Enumeration `gpio_port_t`
 */
__STATIC_FORCEINLINE void __GPIO_enableClock__(const gpio_port_t gpioPort)
{
	// Enable Clock for GPIO Port
	RCC->APB2ENR.REG |= (1 << (2 + gpioPort));
}

/**
 * @brief Disable the clock for the specified GPIO port
 * @param gpioPort GPIO Port Enumeration `gpio_port_t`
 */
__STATIC_FORCEINLINE void __GPIO_disableClock__(const gpio_port_t gpioPort)
{
	// Disable Clock for GPIO Port
	RCC->APB2ENR.REG &= ~(1 << (2 + gpioPort));
}

/**
 * @brief Retrieves the GPIO Port structure based on port enumeration
 * @param gpioPort GPIO Port Enumeration `gpio_port_t` 
 * @return GPIO_TypeDef* Pointer to the GPIO Port structure
 */
__STATIC_FORCEINLINE GPIO_TypeDef* __GPIO_getPort__(const gpio_port_t gpioPort){
	// Return Pointer to GPIO Port Structure
	extern const GPIO_TypeDef* const __gpioDriverMapping__[7];
	return __gpioDriverMapping__[gpioPort];
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

#endif /* GPIO_CONFIG_H_ */