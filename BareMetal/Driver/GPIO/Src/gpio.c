/*---------------------------------------------- Includes ---------------------------------------------- */
#include "gpio.h"
#include "gpio_helper.h"

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
 * @retval `DRIVER_STATUS_SUCCESS`:				Configuration applied successfully
 * @retval `DRIVER_STATUS_ERROR_INVALID_ARG`:	`gpio`, `pin`, `mode`, or `config` was invalid
 * @retval `DRIVER_STATUS_ERROR_STATE`:			Staged configuration update failed
 */
driver_status_t GPIO_SetPinModeConfig(const gpio_port_t gpio, gpio_pin_t pin, const gpio_pin_mode_t mode, const gpio_pin_config_t config)
{
	if ((GPIO_DRIVER_IS_PORT(gpio) == 0x00) ||
		(GPIO_DRIVER_IS_PIN(pin) == 0x00) ||
		(GPIO_DRIVER_PIN_IS_MODE(mode) == 0x00) ||
		(GPIO_DRIVER_PIN_IS_CONFIG(config) == 0x00) ||
		(GPIO_DRIVER_PIN_IS_MODE_CONFIG_COMPATIBLE(mode, config) == 0x00))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	// Local Variables
	GPIO_TypeDef* const GPIOx = GPIO_D2L_GetPort(gpio);
	uint32_t gpioX_CRH = 0x00UL;
	uint32_t gpioX_CRL = 0x00UL;
	uint32_t gpioX_ODR = 0x00UL;
	uint8_t regStatus = 0x00;
	// Read
	if(GPIO_DRIVER_PIN_REQUIRES_CRL(pin)) GPIO_LL_READ_REG(GPIOx, CRL, gpioX_CRL);
	if(GPIO_DRIVER_PIN_REQUIRES_CRH(pin)) GPIO_LL_READ_REG(GPIOx, CRH, gpioX_CRH);
	if(GPIO_DRIVER_PIN_IS_PULL_CONFIG(mode, config)) GPIO_LL_READ_REG(GPIOx, ODR, gpioX_ODR);
	// Modify
	while (pin)
	{
		// Extract only the 1st bit set from LSB
		gpio_pin_t currentPin = (gpio_pin_t)(pin & -pin);
		// Configure the Control Register High
		if (GPIO_DRIVER_PIN_REQUIRES_CRH(currentPin))
		{
			if (_GPIO_Helper_UpdatePinModeConfigImage(currentPin, mode, config, &gpioX_CRH) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			regStatus |= GPIO_CRH_UPDATED;
		}
		// Configure the Control Register Low
		else
		{
			if (_GPIO_Helper_UpdatePinModeConfigImage(currentPin, mode, config, &gpioX_CRL) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			regStatus |= GPIO_CRL_UPDATED;
		}
		// Pull-Up or Pull-Down Configuration
		if (GPIO_DRIVER_PIN_IS_PULL_CONFIG(mode, config))
		{
			if (_GPIO_Helper_UpdatePinPullImage(currentPin, config, &gpioX_ODR) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			regStatus |= GPIO_ODR_UPDATED;
		}
		// Update the status
		pin &= ~currentPin;
	}
	// Write
	if (regStatus & GPIO_CRH_UPDATED) GPIO_LL_WRITE_REG(GPIOx, CRH, gpioX_CRH);
	if (regStatus & GPIO_CRL_UPDATED) GPIO_LL_WRITE_REG(GPIOx, CRL, gpioX_CRL);
	if (regStatus & GPIO_ODR_UPDATED) GPIO_LL_WRITE_REG(GPIOx, ODR, gpioX_ODR);

	return DRIVER_STATUS_SUCCESS;
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
	gpio_pin_mode_t mode = GPIO_PIN_MODE_INPUT;

	if (_GPIO_Helper_ReadPinModeConfig(GPIO_D2L_GetPort(gpio), pin, &mode, NULL) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_MODE_INPUT;
	}

	return mode;
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
	if(GPIO_DRIVER_PIN_REQUIRES_CRH(pin)) GPIO_LL_READ_REG(GPIOx, CRH, gpioX_CRH);
	if(GPIO_DRIVER_PIN_REQUIRES_CRL(pin)) GPIO_LL_READ_REG(GPIOx, CRL, gpioX_CRL);
	// Update
	while(pin)
	{
		// Extract only the 1st bit set from LSB
		gpio_pin_t currentPin = (gpio_pin_t)(pin & -pin);
		// Configure the Control Register High
		if (GPIO_DRIVER_PIN_REQUIRES_CRH(currentPin))
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_UpdatePinModeImage(currentPin, mode, &gpioX_CRH));
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_UpdatePinModeImage(currentPin, mode, &gpioX_CRL));
			regStatus |= GPIO_CRL_UPDATED;
		}
		// Update the parameters
		pin &= ~currentPin;
	}
	// Write
	if(regStatus & GPIO_CRH_UPDATED) GPIO_LL_WRITE_REG(GPIOx, CRH, gpioX_CRH);
	if(regStatus & GPIO_CRL_UPDATED) GPIO_LL_WRITE_REG(GPIOx, CRL, gpioX_CRL);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Get GPIO Pin Configuration Type
 * @param[in] gpio @ref gpio_port_t "GPIO Port"
 * @param[in] pin @ref gpio_pin_t "GPIO Pin"
 * @return `gpio_pin_config_t` driver-facing configuration derived from the raw LL fields
 * 
 * @details
 * Extracts the CNF field from the pin's configuration register.
 * Returns only the 2-bit configuration value without the mode bits.
 */
gpio_pin_config_t GPIO_GetPinConfig(const gpio_port_t gpio, const gpio_pin_t pin)
{
	gpio_pin_config_t config = GPIO_PIN_CNF_IN_ANALOG;

	if (_GPIO_Helper_ReadPinModeConfig(GPIO_D2L_GetPort(gpio), pin, NULL, &config) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_CNF_IN_ANALOG;
	}

	return config;
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
	if(GPIO_DRIVER_PIN_REQUIRES_CRH(pin)) GPIO_LL_READ_REG(GPIOx, CRH, gpioX_CRH);
	if(GPIO_DRIVER_PIN_REQUIRES_CRL(pin)) GPIO_LL_READ_REG(GPIOx, CRL, gpioX_CRL);
	// Update
	while(pin)
	{
		// Extract only the 1st bit set from LSB
		gpio_pin_t currentPin = (gpio_pin_t)(pin & -pin);
		// Configure the Control Register High
		if (GPIO_DRIVER_PIN_REQUIRES_CRH(currentPin))
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_UpdatePinConfigImage(currentPin, config, &gpioX_CRH));
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_UpdatePinConfigImage(currentPin, config, &gpioX_CRL));
			regStatus |= GPIO_CRL_UPDATED;
		}
		// Update the parameters
		pin &= ~currentPin;
	}
	// Write
	if(regStatus & GPIO_CRH_UPDATED) GPIO_LL_WRITE_REG(GPIOx, CRH, gpioX_CRH);
	if(regStatus & GPIO_CRL_UPDATED) GPIO_LL_WRITE_REG(GPIOx, CRL, gpioX_CRL);
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
	if ((gpioConfig == NULL) ||
		(GPIO_DRIVER_IS_PORT(gpio) == 0x00) ||
		(GPIO_DRIVER_IS_PIN(gpioConfig->pin) == 0x00) ||
		(GPIO_DRIVER_PIN_IS_MODE(gpioConfig->mode) == 0x00) ||
		(GPIO_DRIVER_PIN_IS_CONFIG(gpioConfig->config) == 0x00) ||
		(GPIO_DRIVER_PIN_IS_MODE_CONFIG_COMPATIBLE(gpioConfig->mode, gpioConfig->config) == 0x00))
	{
		return DRIVER_STATUS_ERROR_FAIL;
	}
	// Enable Clock for GPIO Port
	GPIO_LL_EnablePortClock(GPIO_D2L_GetPort(gpio));
	// Enable AFIO Clock
	if (GPIO_DRIVER_PIN_IS_AF_CONFIG(gpioConfig->config)) GPIO_LL_EnableAFIOClock();
	// Set Pin Parameters
	ASSERT_DRIVER_STATUS(GPIO_SetPinModeConfig(gpio, gpioConfig->pin, gpioConfig->mode, gpioConfig->config));
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
	if(GPIO_DRIVER_PIN_REQUIRES_CRL(pin)) GPIO_LL_READ_REG(GPIOx, CRL, gpioX_CRL);
	if(GPIO_DRIVER_PIN_REQUIRES_CRH(pin)) GPIO_LL_READ_REG(GPIOx, CRH, gpioX_CRH);

	// Configure Each Pin
	while (pin)
	{
		// Extract only the 1st bit set from LSB
		gpio_pin_t currentPin = (gpio_pin_t)(pin & -pin);
		// Configure the Control Register High
		if (GPIO_DRIVER_PIN_REQUIRES_CRH(currentPin))
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_ResetPinConfigImage(currentPin, &gpioX_CRH));
			regStatus |= GPIO_CRH_UPDATED;
		}
		// Configure the Control Register Low
		else
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_ResetPinConfigImage(currentPin, &gpioX_CRL));
			regStatus |= GPIO_CRL_UPDATED;
		}
		// Update the status
		gpioX_BRR |= currentPin;
		pin &= ~currentPin;
	}
	// Write the data back to Registers
	if (regStatus & GPIO_CRH_UPDATED) GPIO_LL_WRITE_REG(GPIOx, CRH, gpioX_CRH);
	if (regStatus & GPIO_CRL_UPDATED) GPIO_LL_WRITE_REG(GPIOx, CRL, gpioX_CRL);
	GPIO_LL_WRITE_REG(GPIOx, BRR, gpioX_BRR);
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
