/*---------------------------------------------- Includes ---------------------------------------------- */
#include "gpio.h"

/*---------------------------------------------- MACROs ---------------------------------------------- */
#define GPIO_CRL_UPDATED								((uint8_t) 0x01)
#define GPIO_CRH_UPDATED								((uint8_t) 0x02)
#define GPIO_ODR_UPDATED								((uint8_t) 0x04)

/*---------------------------------------------- Driver APIs ---------------------------------------------- */

/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param gpio GPIO Port (Refer `gpio_port_t`)
 * @param gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_Init(const gpio_port_t gpio, const gpio_config_t* const gpioConfig)
{
	// Validation
	 if((GPIO_DRIVER_IS_PORT(gpio) == 0x00) || (GPIO_DRIVER_IS_PIN(gpioConfig->pin) == 0x00) ||
       (GPIO_DRIVER_IS_PIN_MODE(gpioConfig->mode) == 0x00) || (GPIO_DRIVER_IS_PIN_CONFIG(gpioConfig->config) == 0x00) ||
       (GPIO_DRIVER_PIN_IS_MODE_CONFIG_COMPATIBLE(gpioConfig->mode, gpioConfig->config) == 0x00)) 
		return DRIVER_FAIL;
    
	// Local Variables
	GPIO_TypeDef* const GPIOx = GPIO_getLLPort(gpio);
	// Enable Clock for GPIO Port
	_GPIO_EnableClock(GPIOx);
	// Enable AFIO Clock
	if (GPIO_DRIVER_PIN_IS_AF_CONFIG(gpioConfig->config)) _GPIO_EnableAFIOClock();
	// Local Variables
	uint32_t gpioX_CRH = 0x00UL;
	uint32_t gpioX_CRL = 0x00UL;
	uint32_t gpioX_ODR = 0x00UL;
	gpio_pin_t pinMask = gpioConfig->pin;
	uint8_t regStatus = 0x00;
	if(GPIO_DRIVER_PIN_REQUIRES_CRL(pinMask)) gpioX_CRL = __GPIO_ReadCRL(GPIOx);
	if(GPIO_DRIVER_PIN_REQUIRES_CRH(pinMask)) gpioX_CRH = __GPIO_ReadCRH(GPIOx);
	if(GPIO_DRIVER_PIN_IS_PULL_CONFIG(gpioConfig->mode, gpioConfig->config)) gpioX_ODR = __GPIO_ReadODR(GPIOx);
	// Configure Each Pin
	while (pinMask)
	{
		// Extract only the 1st bit set from LSB
		gpio_pin_t currentPin = (gpio_pin_t)(pinMask & -pinMask);
		// Configure the Control Register High
		if (GPIO_DRIVER_PIN_REQUIRES_CRH(currentPin))
		{
			gpioX_CRH = _GPIO_PinStageParams(GPIO_getLLPin(currentPin), GPIO_getLLPinMode(gpioConfig->mode), GPIO_getLLPinConfig(gpioConfig->config), gpioX_CRH);
			regStatus |= GPIO_CRH_UPDATED;
		}
		// Configure the Control Register Low
		else
		{
			gpioX_CRL = _GPIO_PinStageParams(GPIO_getLLPin(currentPin), GPIO_getLLPinMode(gpioConfig->mode), GPIO_getLLPinConfig(gpioConfig->config), gpioX_CRL);
			regStatus |= GPIO_CRL_UPDATED;
		}
		// Pull-Up or Pull-Down Configuration
		if (GPIO_DRIVER_PIN_IS_PULL_CONFIG(gpioConfig->mode, gpioConfig->config))
		{
			gpioX_ODR = _GPIO_PinStagePullConfig(GPIO_getLLPin(currentPin), gpioConfig->config, gpioX_ODR);
			regStatus |= GPIO_ODR_UPDATED;
		}
		// Update the status
		pinMask &= ~currentPin;
	}

	// Write the data back to Registers
	if (regStatus & GPIO_CRH_UPDATED) __GPIO_WriteCRH(GPIOx, gpioX_CRH);
	if (regStatus & GPIO_CRL_UPDATED) __GPIO_WriteCRL(GPIOx, gpioX_CRL);
	if (regStatus & GPIO_ODR_UPDATED) __GPIO_WriteODR(GPIOx, gpioX_ODR);

	// Return Success
	return DRIVER_SUCCESS;
}

/**
 * @brief Configures the LED connected to the specified GPIO Port and Pin
 * @param gpio @ref gpio_port_t "GPIO Port"
 * @param gpioConfig @ref gpio_config_t "GPIO Configuration Structure"
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t GPIO_LED_Init(const gpio_port_t gpio, gpio_config_t* const gpioConfig)
{
	// Update the GPIO Configuration Structure for LED
	gpioConfig->mode = GPIO_PIN_MODE_OUTPUT_10MHz;
	gpioConfig->config = GPIO_PIN_CNF_OUT_GP_PP;
	// Call GPIO Config()
	return GPIO_Init(gpio, gpioConfig);
}

/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param gpio GPIO Port (Refer `gpio_port_t`)
 * @param gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
// driver_status_t GPIO_Deinit(const gpio_port_t gpio, const gpio_pin_t pin)
// {
// 	// Validation
// 	if((GPIO_DRIVER_IS_PORT(gpio) == 0x00) || (GPIO_DRIVER_IS_PIN(pin) == 0x00))
// 		return DRIVER_FAIL;
// 	// Local Variables
// 	GPIO_TypeDef *GPIOx = GPIO_getLLPort(gpio);

// 	// Local Variables
// 	uint32_t gpioX_CRH = GPIOx->CRH.REG;
// 	uint32_t gpioX_CRL = GPIOx->CRL.REG;
// 	uint32_t gpioX_ODR = GPIOx->ODR.REG;
// 	gpio_pin_t pinMask = pin;
// 	uint8_t regStatus = 0x00;
// 	// Configure Each Pin
// 	while (pinMask)
// 	{
// 		// Extract only the 1st bit set from LSB
// 		gpio_pin_t currentPin = (gpio_pin_t)(pinMask & -pinMask);
// 		// Configure the Control Register High
// 		if (__GPIO_getPin__(currentPin) > 7)
// 		{
// 			__GPIO_resetCtrlRegister__(currentPin, &gpioX_CRH);
// 			regStatus |= GPIO_CRH_UPDATED;
// 		}
// 		// Configure the Control Register Low
// 		else
// 		{
// 			__GPIO_resetCtrlRegister__(currentPin, &gpioX_CRL);
// 			regStatus |= GPIO_CRL_UPDATED;
// 		}
// 		// Pull-Up or Pull-Down Configuration
// 		if ((gpioConfig->mode == GPIO_PIN_MODE_INPUT) && (IS_PULL_CONFIG(gpioConfig->config)))
// 		{
// 			__GPIO_resetPullConfig__(currentPin, &gpioX_ODR);
// 			regStatus |= GPIO_ODR_UPDATED;
// 		}
// 		// Update the status
// 		pinMask &= ~currentPin;
// 	}
// 	// Write the data back to Registers
// 	if (regStatus & GPIO_CRH_UPDATED)
// 		GPIOx->CRH.REG = gpioX_CRH;
// 	if (regStatus & GPIO_CRL_UPDATED)
// 		GPIOx->CRL.REG = gpioX_CRL;
// 	if (regStatus & GPIO_ODR_UPDATED)
// 		GPIOx->ODR.REG = gpioX_ODR;
// 	return DRIVER_SUCCESS;
// }



// /**
//  * @brief Configures the On-board LED
//  * @return Status of Driver Operation
//  * @returns - DRIVER_FAIL: Failure
//  * @returns - DRIVER_SUCCESS: Success
//  */
// driver_status_t OB_LED_Init(void)
// {
// 	// On-board (OB) LED Configuration Structure
// 	gpio_config_t obLedConfig = 
// 	{
// 		.pin = GPIO_PIN_OB_LED,
// 		.mode = GPIO_PIN_MODE_OUTPUT_2MHz,	 // Refer datasheet for this speed selection
// 		.config = GPIO_PIN_CNF_OUT_GP_PP // General Purpose Push-Pull Configuration
// 	};
// 	// Call GPIO Config()
// 	return GPIO_Init(GPIO_PORT_OB_LED, &obLedConfig);
// }

// /**
//  * @brief Deconfigures the On-board LED
//  * @return Status of Driver Operation
//  * @returns - DRIVER_FAIL: Failure
//  * @returns - DRIVER_SUCCESS: Success
//  */
// driver_status_t OB_LED_Deinit(void)
// {
// 	// On-board (OB) LED Configuration Structure
// 	gpio_config_t obLedConfig = 
// 	{
// 		.pin = GPIO_PIN_OB_LED,
// 		.mode = GPIO_PIN_MODE_OUTPUT_2MHz,	 // Refer datasheet for this speed selection
// 		.config = GPIO_PIN_CNF_OUT_GP_PP // General Purpose Push-Pull Configuration
// 	};
// 	// Call GPIO Config()
// 	return GPIO_Deinit(GPIO_PORT_OB_LED, &obLedConfig);
// }
