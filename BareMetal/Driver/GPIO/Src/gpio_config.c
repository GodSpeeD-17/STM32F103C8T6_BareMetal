/*********************************************** Includes ***********************************************/
#include "gpio_config.h"

/*********************************************** Lookup Table ***********************************************/
// GPIO Port Lookup Table
const GPIO_TypeDef* const __gpioDriverMapping__[7] = 
{
	GPIOA, 
	GPIOB, 
	GPIOC, 
	GPIOD, 
	GPIOE, 
	GPIOF, 
	GPIOG
};

/*********************************************** Driver APIs ***********************************************/
/**
 * @brief Updates the control register (CRL or CRH) for a specific GPIO pin based on the provided configuration
 * @param pinMask Mask representing the specific GPIO pin to be configured
 * @param gpioMode GPIO Mode Enumeration `gpio_pin_mode_t`
 * @param gpioCnf GPIO Configuration Enumeration `gpio_pin_cnf_t`
 * @param gpioCtrlReg Pointer to the control register (CRL or CRH) to be updated
 * @note Pass only single pin not logical combination of Pins
 */
void __GPIO_updateCtrlRegister__(const gpio_pin_t pinMask, const gpio_pin_mode_t gpioMode, gpio_pin_cnf_t gpioCnf, uint32_t* gpioCtrlReg){
	// Local Variables
	uint8_t maskPos = __GPIO_getPin__(pinMask);
	maskPos = ((maskPos < (uint8_t) 8) ? (maskPos) : (maskPos - 8));
	maskPos <<= 2;
	// Clear existing configuration
	*gpioCtrlReg &= ~(0x0F << maskPos);
	// Update GPIO Mode in Control Register 
	*gpioCtrlReg |= ((gpioMode & 0x03) << maskPos);
	// Pull-Up & Pull-Down Configuration
	if(gpioMode == GPIO_MODE_INPUT){
		if((gpioCnf == GPIO_PIN_CNF_IN_PULL_UP) || (gpioCnf == GPIO_PIN_CNF_IN_PULL_DOWN))
			gpioCnf = 0x02;
	}
	// Update GPIO Configuration in Control Register 
	*gpioCtrlReg |= ((gpioCnf & 0x03) << (maskPos + 2));
}

/**
 * @brief Updates the control register (CRL or CRH) for a specific GPIO pin based on the provided configuration
 * @param pinMask Mask representing the specific GPIO pin to be configured
 * @param gpioCnf GPIO Configuration Enumeration `gpio_pin_cnf_t`
 * @param gpioODRReg Pointer to the output data register (ODR) to be updated
 * @note Pass only single pin not logical combination of Pins 
 */
void __GPIO_updatePullConfig__(const gpio_pin_t pinMask, gpio_pin_cnf_t gpioCnf, uint32_t* gpioODRReg){
	// Pull-Up
	if(gpioCnf == GPIO_PIN_CNF_IN_PULL_UP){
		*gpioODRReg |= pinMask;
	}
	// Pull-Down
	else if(gpioCnf == GPIO_PIN_CNF_IN_PULL_DOWN){
		*gpioODRReg &= ~(pinMask);
	}
}

/**
 * @brief Resets the control register (CRL or CRH) for a specific GPIO pin based on the provided configuration
 * @param pinMask Mask representing the specific GPIO pin to be configured
 * @param gpioCtrlReg Pointer to the control register (CRL or CRH) to be updated
 * @note Pass only single pin not logical combination of Pins
 */
void __GPIO_resetCtrlRegister__(const gpio_pin_t pinMask, uint32_t* gpioCtrlReg){
	// Local Variables
	uint8_t maskPos = __GPIO_getPin__(pinMask);
	maskPos = ((maskPos < (uint8_t)8) ? (maskPos) : (maskPos - 8));
	maskPos <<= 2;
	// Clear existing configuration
	*gpioCtrlReg &= ~(0x0F << maskPos);
	// Update GPIO Mode in Control Register 
	*gpioCtrlReg |= (0x04 << maskPos);
}

