/*---------------------------------------------- Includes ---------------------------------------------- */
#include "gpio.h"

/*---------------------------------------------- MACROs ---------------------------------------------- */
#define GPIO_CRL_UPDATED								((uint8_t) 0x01)
#define GPIO_CRH_UPDATED								((uint8_t) 0x02)
#define GPIO_ODR_UPDATED								((uint8_t) 0x04)

/*---------------------------------------------- Driver APIs ---------------------------------------------- */

/**
 * @brief  Configures GPIO pin mode and electrical parameters.
 * @details
 * Updates the MODE and CNF fields in the GPIO control registers (CRL/CRH),
 * and sets the pull-up/pull-down state in ODR when applicable.
 * Supports batch configuration of multiple pins using bitmask.
 *
 * @param[in] gpio    GPIO port identifier (see @ref gpio_port_t)
 * @param[in] pin     Target pin(s) as bitmask (see @ref gpio_pin_t)
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
void GPIO_SetPinParameters(const gpio_port_t gpio, gpio_pin_t pin, const gpio_pin_mode_t mode, const gpio_pin_config_t config)
{
	// Local Variables
	GPIO_TypeDef* const GPIOx = GPIO_D2L_GetPort(gpio);
	uint32_t gpioX_CRH = 0x00UL;
	uint32_t gpioX_CRL = 0x00UL;
	uint32_t gpioX_ODR = 0x00UL;
	uint8_t regStatus = 0x00;
	// Read
	if(GPIO_DRIVER_PIN_REQUIRES_CRL(pin)) gpioX_CRL = __GPIO_ReadCRL(GPIOx);
	if(GPIO_DRIVER_PIN_REQUIRES_CRH(pin)) gpioX_CRH = __GPIO_ReadCRH(GPIOx);
	if(GPIO_DRIVER_PIN_IS_PULL_CONFIG(mode, config)) gpioX_ODR = __GPIO_ReadODR(GPIOx);
	// Modify
	while (pin)
	{
		// Extract only the 1st bit set from LSB
		gpio_pin_t currentPin = (gpio_pin_t)(pin & -pin);
		// Configure the Control Register High
		if (GPIO_DRIVER_PIN_REQUIRES_CRH(currentPin))
		{
			gpioX_CRH = _GPIO_PinStageParams(GPIO_D2L_GetPin(currentPin), GPIO_D2L_GetPinMode(mode), GPIO_D2L_GetPinConfig(config), gpioX_CRH);
			regStatus |= GPIO_CRH_UPDATED;
		}
		// Configure the Control Register Low
		else
		{
			gpioX_CRL = _GPIO_PinStageParams(GPIO_D2L_GetPin(currentPin), GPIO_D2L_GetPinMode(mode), GPIO_D2L_GetPinConfig(config), gpioX_CRL);
			regStatus |= GPIO_CRL_UPDATED;
		}
		// Pull-Up or Pull-Down Configuration
		if (GPIO_DRIVER_PIN_IS_PULL_CONFIG(mode, config))
		{
			gpioX_ODR = _GPIO_PinStagePullConfig(GPIO_D2L_GetPin(currentPin), config, gpioX_ODR);
			regStatus |= GPIO_ODR_UPDATED;
		}
		// Update the status
		pin &= ~currentPin;
	}
	// Write
	if (regStatus & GPIO_CRH_UPDATED) __GPIO_WriteCRH(GPIOx, gpioX_CRH);
	if (regStatus & GPIO_CRL_UPDATED) __GPIO_WriteCRL(GPIOx, gpioX_CRL);
	if (regStatus & GPIO_ODR_UPDATED) __GPIO_WriteODR(GPIOx, gpioX_ODR);
}

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
gpio_pin_mode_t GPIO_GetPinMode(const gpio_port_t gpio, const gpio_pin_t pin)
{
	switch(GPIO_LL_PIN_PARAMETER_EXTRACT_MODE(GPIO_GetPinParameters(gpio, pin)))
	{
		case _GPIO_PIN_MODE_INPUT: return GPIO_PIN_MODE_INPUT; break;
		case _GPIO_PIN_MODE_OUTPUT_10MHz: return GPIO_PIN_MODE_OUTPUT_10MHz; break;
		case _GPIO_PIN_MODE_OUTPUT_2MHz: return GPIO_PIN_MODE_OUTPUT_2MHz; break;
		case _GPIO_PIN_MODE_OUTPUT_50MHz: return GPIO_PIN_MODE_OUTPUT_50MHz; break;
		default: break;
	}
}

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
 * @retval `DRIVER_STATUS_SUCCESS`:  Configuration applied successfully.
 * @retval `DRIVER_STATUS_ERROR_FAIL`:     Invalid parameter (port, pin, or mode).
 *
 * @note
 * - Automatically determines whether CRL or CRH needs to be updated.
 * - Existing configuration bits for unaffected pins remain unchanged.
 * - Use with @ref GPIO_SetPinConfig for full electrical configuration.
 */
driver_status_t GPIO_SetPinMode(const gpio_port_t gpio, gpio_pin_t pin, const gpio_pin_mode_t mode)
{
	// Validation
	if ((GPIO_DRIVER_IS_PORT(gpio) == 0x00) || (GPIO_DRIVER_IS_PIN(pin) == 0x00) || (GPIO_DRIVER_PIN_IS_MODE(mode) == 0x00))
		return DRIVER_STATUS_ERROR_FAIL;
	// Local Variables
	GPIO_TypeDef* const GPIOx = GPIO_D2L_GetPort(gpio);
	uint32_t gpioX_CRH = 0x00UL;
	uint32_t gpioX_CRL = 0x00UL;
	uint8_t regStatus = 0x00;
	// Read
	if(GPIO_DRIVER_PIN_REQUIRES_CRH(pin)) gpioX_CRH = __GPIO_ReadCRH(GPIOx);
	if(GPIO_DRIVER_PIN_REQUIRES_CRL(pin)) gpioX_CRL = __GPIO_ReadCRL(GPIOx);
	// Update
	while(pin)
	{
		// Extract only the 1st bit set from LSB
		gpio_pin_t currentPin = (gpio_pin_t)(pin & -pin);
		// Configure the Control Register High
		if (GPIO_DRIVER_PIN_REQUIRES_CRH(currentPin))
		{
			gpioX_CRH = _GPIO_PinStageMode(GPIO_D2L_GetPin(currentPin), GPIO_D2L_GetPinMode(mode), gpioX_CRH);
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			gpioX_CRL = _GPIO_PinStageMode(GPIO_D2L_GetPin(currentPin), GPIO_D2L_GetPinMode(mode), gpioX_CRL);
			regStatus |= GPIO_CRL_UPDATED;
		}
		// Update the parameters
		pin &= ~currentPin;
	}
	// Write
	if(regStatus & GPIO_CRH_UPDATED) __GPIO_WriteCRH(GPIOx, gpioX_CRH);
	if(regStatus & GPIO_CRL_UPDATED) __GPIO_WriteCRL(GPIOx, gpioX_CRL);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Get GPIO Pin Configuration Type
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @return _gpio_pin_config_t @ref GPIO_LL_Config "Pin Configuration"
 * 
 * @details
 * Extracts the CNF field from the pin's configuration register.
 * Returns only the 2-bit configuration value without the mode bits.
 */
gpio_pin_config_t GPIO_GetPinConfig(const gpio_port_t gpio, const gpio_pin_t pin)
{
    const gpio_pin_parameter_t pinParams = GPIO_GetPinParameters(gpio, pin);
	switch(GPIO_LL_PIN_PARAMETER_EXTRACT_MODE(pinParams))
	{
		// Input Mode
		case _GPIO_PIN_MODE_INPUT:
			switch(GPIO_LL_PIN_PARAMETER_EXTRACT_CONFIGURATION(pinParams))
			{
				case _GPIO_PIN_CNF_INPUT_ANALOG: return GPIO_PIN_CNF_IN_ANALOG; break;
				case _GPIO_PIN_CNF_INPUT_FLOATING: return GPIO_PIN_CNF_IN_FLOAT; break;
				case _GPIO_PIN_CNF_INPUT_PULL:
					if(__GPIO_ReadODR(GPIO_D2L_GetPort(gpio)) & (uint32_t) pin) return GPIO_PIN_CNF_IN_PULL_UP;
					else return GPIO_PIN_CNF_IN_PULL_DOWN;
				break;
			}
		break;
		// Output Mode
		case _GPIO_PIN_MODE_OUTPUT_10MHz:
		case _GPIO_PIN_MODE_OUTPUT_2MHz:
		case _GPIO_PIN_MODE_OUTPUT_50MHz:
			switch(GPIO_LL_PIN_PARAMETER_EXTRACT_CONFIGURATION(pinParams))
			{
				case _GPIO_PIN_CNF_OUTPUT_PP: return GPIO_PIN_CNF_OUT_GP_PP; break;
				case _GPIO_PIN_CNF_OUTPUT_OD: return GPIO_PIN_CNF_OUT_GP_OD; break;
				case _GPIO_PIN_CNF_AF_PP: return GPIO_PIN_CNF_OUT_AF_PP; break;
				case _GPIO_PIN_CNF_AF_OD: return GPIO_PIN_CNF_OUT_AF_OD; break;
				default: break;
			}
		break;
		// Default Case	
		default: break;
	}
}

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
 * @retval `DRIVER_STATUS_SUCCESS`:  Configuration applied successfully.
 * @retval `DRIVER_STATUS_ERROR_FAIL`:     Invalid parameter (port, pin, or configuration).
 *
 * @note
 * - Automatically determines whether CRL or CRH registers are affected.
 * - Use with @ref GPIO_SetPinMode to fully configure a pin.
 * - Safe for multi-pin configuration; unaffected bits are preserved.
 * - Does not configure Pull Up, need to be externally set.
 */
driver_status_t GPIO_SetPinConfig(const gpio_port_t gpio, gpio_pin_t pin, const gpio_pin_config_t config)
{
	// Validation
	if ((GPIO_DRIVER_IS_PORT(gpio) == 0x00) || (GPIO_DRIVER_IS_PIN(pin) == 0x00) || (GPIO_DRIVER_PIN_IS_CONFIG(config) == 0x00))
		return DRIVER_STATUS_ERROR_FAIL;
	// Local Variables
	GPIO_TypeDef* const GPIOx = GPIO_D2L_GetPort(gpio);
	uint32_t gpioX_CRH = 0x00UL;
	uint32_t gpioX_CRL = 0x00UL;
	uint8_t regStatus = 0x00;
	// Read
	if(GPIO_DRIVER_PIN_REQUIRES_CRH(pin)) gpioX_CRH = __GPIO_ReadCRH(GPIOx);
	if(GPIO_DRIVER_PIN_REQUIRES_CRL(pin)) gpioX_CRL = __GPIO_ReadCRL(GPIOx);
	// Update
	while(pin)
	{
		// Extract only the 1st bit set from LSB
		gpio_pin_t currentPin = (gpio_pin_t)(pin & -pin);
		// Configure the Control Register High
		if (GPIO_DRIVER_PIN_REQUIRES_CRH(currentPin))
		{
			gpioX_CRH = _GPIO_PinStageConfig(GPIO_D2L_GetPin(currentPin), GPIO_D2L_GetPinConfig(config), gpioX_CRH);
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			gpioX_CRL = _GPIO_PinStageConfig(GPIO_D2L_GetPin(currentPin), GPIO_D2L_GetPinConfig(config), gpioX_CRL);
			regStatus |= GPIO_CRL_UPDATED;
		}
		// Update the parameters
		pin &= ~currentPin;
	}
	// Write
	if(regStatus & GPIO_CRH_UPDATED) __GPIO_WriteCRH(GPIOx, gpioX_CRH);
	if(regStatus & GPIO_CRL_UPDATED) __GPIO_WriteCRL(GPIOx, gpioX_CRL);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param[in] gpio GPIO Port (Refer `gpio_port_t`)
 * @param[in] gpioConfig GPIO Configuration Structure (Refer `gpio_config_t`)
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
driver_status_t GPIO_Init(const gpio_port_t gpio, gpio_config_t* const gpioConfig)
{
	// Validation
	if ((GPIO_DRIVER_IS_PORT(gpio) == 0x00) || (GPIO_DRIVER_IS_PIN(gpioConfig->pin) == 0x00) ||
       (GPIO_DRIVER_PIN_IS_MODE(gpioConfig->mode) == 0x00) || (GPIO_DRIVER_PIN_IS_CONFIG(gpioConfig->config) == 0x00) ||
       (GPIO_DRIVER_PIN_IS_MODE_CONFIG_COMPATIBLE(gpioConfig->mode, gpioConfig->config) == 0x00)) 
		return DRIVER_STATUS_ERROR_FAIL;
	// Enable Clock for GPIO Port
	_GPIO_EnableClock(GPIO_D2L_GetPort(gpio));
	// Enable AFIO Clock
	if (GPIO_DRIVER_PIN_IS_AF_CONFIG(gpioConfig->config)) _GPIO_EnableAFIOClock();
	// Set Pin Parameters
	GPIO_SetPinParameters(gpio, gpioConfig->pin, gpioConfig->mode, gpioConfig->config);
	// Return Success
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Configures GPIO Port based on GPIO Configuration Structure
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
driver_status_t GPIO_Deinit(const gpio_port_t gpio, gpio_pin_t pin)
{
	// Validation
	if((GPIO_DRIVER_IS_PORT(gpio) == 0x00) || (GPIO_DRIVER_IS_PIN(pin) == 0x00)) return DRIVER_STATUS_ERROR_FAIL;
	// Local Variables
	GPIO_TypeDef* const GPIOx = GPIO_D2L_GetPort(gpio);
	// Local Variables
	uint32_t gpioX_CRH = 0x00UL;
	uint32_t gpioX_CRL = 0x00UL;
	uint32_t gpioX_BRR = 0x00UL;
	uint8_t regStatus = 0x00;
	if(GPIO_DRIVER_PIN_REQUIRES_CRL(pin)) gpioX_CRL = __GPIO_ReadCRL(GPIOx);
	if(GPIO_DRIVER_PIN_REQUIRES_CRH(pin)) gpioX_CRH = __GPIO_ReadCRH(GPIOx);

	// Configure Each Pin
	while (pin)
	{
		// Extract only the 1st bit set from LSB
		gpio_pin_t currentPin = (gpio_pin_t)(pin & -pin);
		// Configure the Control Register High
		if (GPIO_DRIVER_PIN_REQUIRES_CRH(currentPin))
		{
			gpioX_CRH = _GPIO_PinStageResetParams(GPIO_D2L_GetPin(currentPin), gpioX_CRH);
			regStatus |= GPIO_CRH_UPDATED;
		}
		// Configure the Control Register Low
		else
		{
			gpioX_CRL = _GPIO_PinStageResetParams(GPIO_D2L_GetPin(currentPin), gpioX_CRL);
			regStatus |= GPIO_CRL_UPDATED;
		}
		// Update the status
		gpioX_BRR |= currentPin;
		pin &= ~currentPin;
	}
	// Write the data back to Registers
	if (regStatus & GPIO_CRH_UPDATED) __GPIO_WriteCRH(GPIOx, gpioX_CRH);
	if (regStatus & GPIO_CRL_UPDATED) __GPIO_WriteCRL(GPIOx, gpioX_CRL);
	__GPIO_WriteBRR(GPIOx, gpioX_BRR);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Configures the On-board LED
 * @returns Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
driver_status_t OB_LED_Init(void)
{
	// On-board (OB) LED Configuration Structure
	gpio_config_t obLedConfig = 
	{
		.pin = GPIO_OB_LED_PIN,
		.mode = GPIO_PIN_MODE_OUTPUT_2MHz,	///<  Refer datasheet for this speed selection
		.config = GPIO_PIN_CNF_OUT_GP_PP	///< General Purpose Push-Pull Configuration
	};
	// Call GPIO Config()
	return GPIO_Init(GPIO_OB_LED_PORT, &obLedConfig);
}

