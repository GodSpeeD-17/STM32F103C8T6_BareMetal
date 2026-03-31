// ==================================================================================================== //
//                                                Includes                                              //
// ==================================================================================================== //
#include "gpio.h"
#include "gpio_helper.h"

// ==================================================================================================== //
//                                               Local Macros                                           //
// ==================================================================================================== //
#define GPIO_CRL_UPDATED                               ((uint8_t) 0x01U)
#define GPIO_CRH_UPDATED                               ((uint8_t) 0x02U)
#define GPIO_ODR_UPDATED                               ((uint8_t) 0x04U)

// ==================================================================================================== //
//                                              Local Helpers                                           //
// ==================================================================================================== //

static gpio_pin_t _GPIO_GetLowestSelectedPin(const gpio_pin_t pinMask)
{
	gpio_pin_t currentPin = GPIO_PIN_0;

	while (currentPin != GPIO_PIN_NONE)
	{
		if ((pinMask & currentPin) != GPIO_PIN_NONE)
		{
			return currentPin;
		}

		currentPin = (gpio_pin_t) (currentPin << 1U);
	}

	return GPIO_PIN_NONE;
}

// ==================================================================================================== //
//                                               Driver APIs                                            //
// ==================================================================================================== //

driver_status_t GPIO_SetPinModeConfig
(
	GPIO_TypeDef* const GPIOx,
	gpio_pin_t pin,
	const gpio_pin_mode_t mode,
	const gpio_pin_config_t config
)
{
	uint32_t gpioCrhRegImage = 0x00000000UL;
	uint32_t gpioCrlRegImage = 0x00000000UL;
	uint32_t gpioOdrRegImage = 0x00000000UL;
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	uint8_t regStatus = 0x00U;
	const uint8_t pullConfigUsed = (GPIO_PIN_IS_PULL_CONFIG(mode, config) != 0x00U) ? 0x01U : 0x00U;

	if ((GPIO_IS_PORT(GPIOx) == 0x00U) ||
		(GPIO_IS_PIN(pin) == 0x00U) ||
		(GPIO_PIN_IS_MODE(mode) == 0x00U) ||
		(GPIO_PIN_IS_CONFIG(config) == 0x00U) ||
		(GPIO_PIN_IS_MODE_CONFIG_COMPATIBLE(mode, config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (GPIO_PIN_REQUIRES_CRL(pin) != GPIO_PIN_NONE)
	{
		GPIO_LL_READ_REG(GPIOx, CRL, gpioCrlRegImage);
	}
	if (GPIO_PIN_REQUIRES_CRH(pin) != GPIO_PIN_NONE)
	{
		GPIO_LL_READ_REG(GPIOx, CRH, gpioCrhRegImage);
	}
	if (pullConfigUsed != 0x00U)
	{
		GPIO_LL_READ_REG(GPIOx, ODR, gpioOdrRegImage);
	}

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_GetLowestSelectedPin(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		if (GPIO_PIN_REQUIRES_CRH(currentPin) != GPIO_PIN_NONE)
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_UpdatePinModeConfigImage(currentPin, mode, config, &gpioCrhRegImage));
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_UpdatePinModeConfigImage(currentPin, mode, config, &gpioCrlRegImage));
			regStatus |= GPIO_CRL_UPDATED;
		}

		if (pullConfigUsed != 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_UpdatePinPullImage(currentPin, config, &gpioOdrRegImage));
			regStatus |= GPIO_ODR_UPDATED;
		}

		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	if ((regStatus & GPIO_CRH_UPDATED) != 0x00U)
	{
		GPIO_LL_WRITE_REG(GPIOx, CRH, gpioCrhRegImage);
	}
	if ((regStatus & GPIO_CRL_UPDATED) != 0x00U)
	{
		GPIO_LL_WRITE_REG(GPIOx, CRL, gpioCrlRegImage);
	}
	if ((regStatus & GPIO_ODR_UPDATED) != 0x00U)
	{
		GPIO_LL_WRITE_REG(GPIOx, ODR, gpioOdrRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

gpio_pin_mode_t GPIO_GetPinMode(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	gpio_pin_mode_t mode = GPIO_PIN_MODE_INPUT;

	if (GPIO_IS_PORT(GPIOx) == 0x00U)
	{
		return GPIO_PIN_MODE_INPUT;
	}

	if (_GPIO_Helper_ReadPinModeConfig(GPIOx, pin, &mode, NULL) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_MODE_INPUT;
	}

	return mode;
}

driver_status_t GPIO_SetPinMode(GPIO_TypeDef* const GPIOx, gpio_pin_t pin, const gpio_pin_mode_t mode)
{
	uint32_t gpioCrhRegImage = 0x00000000UL;
	uint32_t gpioCrlRegImage = 0x00000000UL;
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	uint8_t regStatus = 0x00U;

	if ((GPIO_IS_PORT(GPIOx) == 0x00U) ||
		(GPIO_IS_PIN(pin) == 0x00U) ||
		(GPIO_PIN_IS_MODE(mode) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (GPIO_PIN_REQUIRES_CRH(pin) != GPIO_PIN_NONE)
	{
		GPIO_LL_READ_REG(GPIOx, CRH, gpioCrhRegImage);
	}
	if (GPIO_PIN_REQUIRES_CRL(pin) != GPIO_PIN_NONE)
	{
		GPIO_LL_READ_REG(GPIOx, CRL, gpioCrlRegImage);
	}

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_GetLowestSelectedPin(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		if (GPIO_PIN_REQUIRES_CRH(currentPin) != GPIO_PIN_NONE)
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_UpdatePinModeImage(currentPin, mode, &gpioCrhRegImage));
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_UpdatePinModeImage(currentPin, mode, &gpioCrlRegImage));
			regStatus |= GPIO_CRL_UPDATED;
		}

		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	if ((regStatus & GPIO_CRH_UPDATED) != 0x00U)
	{
		GPIO_LL_WRITE_REG(GPIOx, CRH, gpioCrhRegImage);
	}
	if ((regStatus & GPIO_CRL_UPDATED) != 0x00U)
	{
		GPIO_LL_WRITE_REG(GPIOx, CRL, gpioCrlRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

gpio_pin_config_t GPIO_GetPinConfig(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	gpio_pin_config_t config = GPIO_PIN_CNF_IN_ANALOG;

	if (GPIO_IS_PORT(GPIOx) == 0x00U)
	{
		return GPIO_PIN_CNF_IN_ANALOG;
	}

	if (_GPIO_Helper_ReadPinModeConfig(GPIOx, pin, NULL, &config) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_CNF_IN_ANALOG;
	}

	return config;
}

driver_status_t GPIO_SetPinConfig(GPIO_TypeDef* const GPIOx, gpio_pin_t pin, const gpio_pin_config_t config)
{
	uint32_t gpioCrhRegImage = 0x00000000UL;
	uint32_t gpioCrlRegImage = 0x00000000UL;
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	uint8_t regStatus = 0x00U;

	if ((GPIO_IS_PORT(GPIOx) == 0x00U) ||
		(GPIO_IS_PIN(pin) == 0x00U) ||
		(GPIO_PIN_IS_CONFIG(config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (GPIO_PIN_REQUIRES_CRH(pin) != GPIO_PIN_NONE)
	{
		GPIO_LL_READ_REG(GPIOx, CRH, gpioCrhRegImage);
	}
	if (GPIO_PIN_REQUIRES_CRL(pin) != GPIO_PIN_NONE)
	{
		GPIO_LL_READ_REG(GPIOx, CRL, gpioCrlRegImage);
	}

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_GetLowestSelectedPin(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		if (GPIO_PIN_REQUIRES_CRH(currentPin) != GPIO_PIN_NONE)
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_UpdatePinConfigImage(currentPin, config, &gpioCrhRegImage));
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_UpdatePinConfigImage(currentPin, config, &gpioCrlRegImage));
			regStatus |= GPIO_CRL_UPDATED;
		}

		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	if ((regStatus & GPIO_CRH_UPDATED) != 0x00U)
	{
		GPIO_LL_WRITE_REG(GPIOx, CRH, gpioCrhRegImage);
	}
	if ((regStatus & GPIO_CRL_UPDATED) != 0x00U)
	{
		GPIO_LL_WRITE_REG(GPIOx, CRL, gpioCrlRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Init(GPIO_TypeDef* const GPIOx, const gpio_config_t* const pGPIOConfig)
{
	if (pGPIOConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_IS_PORT(GPIOx) == 0x00U) ||
		(GPIO_IS_PIN(pGPIOConfig->pin) == 0x00U) ||
		(GPIO_PIN_IS_MODE(pGPIOConfig->mode) == 0x00U) ||
		(GPIO_PIN_IS_CONFIG(pGPIOConfig->config) == 0x00U) ||
		(GPIO_PIN_IS_MODE_CONFIG_COMPATIBLE(pGPIOConfig->mode, pGPIOConfig->config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	GPIO_LL_EnablePortClock(GPIOx);
	if (GPIO_PIN_IS_AF_CONFIG(pGPIOConfig->config) != 0x00U)
	{
		GPIO_LL_EnableAFIOClock();
	}

	ASSERT_DRIVER_STATUS(GPIO_SetPinModeConfig(GPIOx, pGPIOConfig->pin, pGPIOConfig->mode, pGPIOConfig->config));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Deinit(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	uint32_t gpioCrhRegImage = 0x00000000UL;
	uint32_t gpioCrlRegImage = 0x00000000UL;
	uint32_t gpioBrrRegImage = 0x00000000UL;
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	uint8_t regStatus = 0x00U;

	if ((GPIO_IS_PORT(GPIOx) == 0x00U) || (GPIO_IS_PIN(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (GPIO_PIN_REQUIRES_CRL(pin) != GPIO_PIN_NONE)
	{
		GPIO_LL_READ_REG(GPIOx, CRL, gpioCrlRegImage);
	}
	if (GPIO_PIN_REQUIRES_CRH(pin) != GPIO_PIN_NONE)
	{
		GPIO_LL_READ_REG(GPIOx, CRH, gpioCrhRegImage);
	}

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_GetLowestSelectedPin(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		if (GPIO_PIN_REQUIRES_CRH(currentPin) != GPIO_PIN_NONE)
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_ResetPinConfigImage(currentPin, &gpioCrhRegImage));
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			ASSERT_DRIVER_STATUS(_GPIO_Helper_ResetPinConfigImage(currentPin, &gpioCrlRegImage));
			regStatus |= GPIO_CRL_UPDATED;
		}

		gpioBrrRegImage |= (uint32_t) currentPin;
		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	if ((regStatus & GPIO_CRH_UPDATED) != 0x00U)
	{
		GPIO_LL_WRITE_REG(GPIOx, CRH, gpioCrhRegImage);
	}
	if ((regStatus & GPIO_CRL_UPDATED) != 0x00U)
	{
		GPIO_LL_WRITE_REG(GPIOx, CRL, gpioCrlRegImage);
	}
	GPIO_LL_WRITE_REG(GPIOx, BRR, gpioBrrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t OB_LED_Init(void)
{
	gpio_config_t obLedConfig =
	{
		.pin = GPIO_OB_LED_PIN,
		.mode = GPIO_PIN_MODE_OUTPUT_2MHz,
		.config = GPIO_PIN_CNF_OUT_GP_PP
	};

	return GPIO_Init(GPIO_OB_LED_PORT, &obLedConfig);
}
