// Includes
#include "gpio.h"

/*********************************************** Config Status MACROS ***********************************************/
#define IS_PULL_CONFIG(cfg) 		((cfg) == GPIO_CNF_IN_PULL_UP || (cfg) == GPIO_CNF_IN_PULL_DOWN)
#define GPIO_CRL_UPDATED 			((uint8_t) 0x01)
#define GPIO_CRH_UPDATED 			((uint8_t) 0x02)
#define GPIO_ODR_UPDATED 			((uint8_t) 0x04)

/*********************************************** Function Definition ***********************************************/
/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param gpio GPIO Port (Refer `gpio_port_t`)
 * @param gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_Config(gpio_port_t gpio, gpio_config_t* const gpioConfig){
	// Validate GPIO Port Support on Hardware
	GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpio);
	if(GPIOx == NULL){
		return DRIVER_FAIL;
	}
	// Enable Clock for GPIO Port
	__GPIO_enableClock__(gpio);
	// Local Variables
	uint32_t gpioX_CRH = GPIOx->CRH.REG;
	uint32_t gpioX_CRL = GPIOx->CRL.REG;
	uint32_t gpioX_ODR = GPIOx->ODR.REG;
	gpio_pin_t pinMask = gpioConfig->pin;
	uint8_t regStatus = 0x00;
	// Configure Each Pin
	while(pinMask){
		// Extract only the 1st bit set from LSB 
		gpio_pin_t currentPin = (gpio_pin_t) (pinMask & -pinMask);
		// Configure the Control Register High
		if(__GPIO_getPin__(currentPin) > 7){
			__GPIO_updateCtrlRegister__(currentPin, gpioConfig->mode, gpioConfig->config, &gpioX_CRH);
			regStatus |= GPIO_CRH_UPDATED;
		}
		// Configure the Control Register Low
		else{
			__GPIO_updateCtrlRegister__(currentPin, gpioConfig->mode, gpioConfig->config, &gpioX_CRL);
			regStatus |= GPIO_CRL_UPDATED;
		}
		// Pull-Up or Pull-Down Configuration
		if((gpioConfig->mode == GPIO_MODE_INPUT) && (IS_PULL_CONFIG(gpioConfig->config))){
			__GPIO_updatePullConfig__(currentPin, gpioConfig->config, &gpioX_ODR);
			regStatus |= GPIO_ODR_UPDATED;
		}
		// Update the status
		pinMask &= ~currentPin;
	}
	// Write the data back to Registers
	if(regStatus & GPIO_CRH_UPDATED)
		GPIOx->CRH.REG = gpioX_CRH;
	if(regStatus & GPIO_CRL_UPDATED)
		GPIOx->CRL.REG = gpioX_CRL;
	if(regStatus & GPIO_ODR_UPDATED)
		GPIOx->ODR.REG = gpioX_ODR;
	return DRIVER_SUCCESS;
}

/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param gpio GPIO Port (Refer `gpio_port_t`)
 * @param gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_Deconfig(gpio_port_t gpio, gpio_config_t* const gpioConfig){
	// Validate GPIO Port Support on Hardware
	GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpio);
	if(GPIOx == NULL){
		return DRIVER_FAIL;
	}
	// Local Variables
	uint32_t gpioX_CRH = GPIOx->CRH.REG;
	uint32_t gpioX_CRL = GPIOx->CRL.REG;
	uint32_t gpioX_ODR = GPIOx->ODR.REG;
	gpio_pin_t pinMask = gpioConfig->pin;
	uint8_t regStatus = 0x00;
	// Configure Each Pin
	while(pinMask){
		// Extract only the 1st bit set from LSB 
		gpio_pin_t currentPin = (gpio_pin_t) (pinMask & -pinMask);
		// Configure the Control Register High
		if(__GPIO_getPin__(currentPin) > 7){
			__GPIO_resetCtrlRegister__(currentPin, &gpioX_CRH);
			regStatus |= GPIO_CRH_UPDATED;
		}
		// Configure the Control Register Low
		else{
			__GPIO_resetCtrlRegister__(currentPin, &gpioX_CRL);
			regStatus |= GPIO_CRL_UPDATED;
		}
		// Pull-Up or Pull-Down Configuration
		if((gpioConfig->mode == GPIO_MODE_INPUT) && (IS_PULL_CONFIG(gpioConfig->config))){
			__GPIO_resetPullConfig__(currentPin, &gpioX_ODR);
			regStatus |= GPIO_ODR_UPDATED;
		}
		// Update the status
		pinMask &= ~currentPin;
	}
	// Write the data back to Registers
	if(regStatus & GPIO_CRH_UPDATED)
		GPIOx->CRH.REG = gpioX_CRH;
	if(regStatus & GPIO_CRL_UPDATED)
		GPIOx->CRL.REG = gpioX_CRL;
	if(regStatus & GPIO_ODR_UPDATED)
		GPIOx->ODR.REG = gpioX_ODR;
	return DRIVER_SUCCESS;
}

/**
 * @brief Configures the LED connected to the specified GPIO Port and Pin
 * @param gpio GPIO Port (Refer `gpio_port_t`)
 * @param gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_LED_Config(gpio_port_t gpio, gpio_config_t* gpioConfig){
	// Validate GPIO Port Support on Hardware
	GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpio);
	if(GPIOx == NULL){
		return DRIVER_FAIL;
	}
	// Update the GPIO Configuration Structure for LED
	gpioConfig->mode = GPIO_MODE_OUTPUT_10MHz;
	gpioConfig->config = GPIO_CNF_OUT_GP_PP;
	// Call GPIO Config()
	return GPIO_Config(gpio, gpioConfig);
}

/**
 * @brief Configures the On-board LED
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t OB_LED_Config(void){
	// On-board (OB) LED Configuration Structure
	gpio_config_t obLedConfig = {
		.pin = GPIO_PIN_OB_LED,
		.mode = GPIO_MODE_OUTPUT_2MHz, // Refer datasheet for this speed selection
		.config = GPIO_CNF_OUT_GP_PP // General Purpose Push-Pull Configuration
	};
	// Call GPIO Config()
	return GPIO_Config(GPIO_PORT_OB_LED, &obLedConfig);
}

/**
 * @brief Deconfigures the On-board LED
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t OB_LED_Deconfig(void){
	// On-board (OB) LED Configuration Structure
	gpio_config_t obLedConfig = {
		.pin = GPIO_PIN_OB_LED,
		.mode = GPIO_MODE_OUTPUT_2MHz, // Refer datasheet for this speed selection
		.config = GPIO_CNF_OUT_GP_PP // General Purpose Push-Pull Configuration
	};
	// Call GPIO Config()
	return GPIO_Deconfig(GPIO_PORT_OB_LED, &obLedConfig);
}
