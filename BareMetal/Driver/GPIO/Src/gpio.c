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
	const uint8_t pullConfigUsed = (GPIO_PIN_MODE_CONFIG_IS_INPUT_PULL(mode, config) != 0x00U) ? 0x01U : 0x00U;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pin) == 0x00U) ||
		(GPIO_PIN_MODE_IS_VALID(mode) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(config) == 0x00U) ||
		(GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (GPIO_PIN_MASK_REQUIRES_CRL(pin) != 0x00U)
	{
		GPIO_LL_READ_REG(GPIOx, CRL, gpioCrlRegImage);
	}
	if (GPIO_PIN_MASK_REQUIRES_CRH(pin) != 0x00U)
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

		if (GPIO_PIN_MASK_REQUIRES_CRH(currentPin) != 0x00U)
		{
			ASSERT_DRIVER_STATUS(GPIO_Helper_StagePinModeConfigImage(currentPin, mode, config, &gpioCrhRegImage));
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			ASSERT_DRIVER_STATUS(GPIO_Helper_StagePinModeConfigImage(currentPin, mode, config, &gpioCrlRegImage));
			regStatus |= GPIO_CRL_UPDATED;
		}

		if (pullConfigUsed != 0x00U)
		{
			ASSERT_DRIVER_STATUS(GPIO_Helper_StagePinPullImage(currentPin, config, &gpioOdrRegImage));
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
	gpio_pin_config_bits_t pinField = (gpio_pin_config_bits_t) 0x00U;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PinMaskToIndex(pin) == GPIO_PIN_INDEX_INVALID))
	{
		return GPIO_PIN_MODE_INPUT;
	}

	pinField = GPIO_LL_ReadPinModeCNFField(GPIOx, pin);
	if (GPIO_Helper_DecodePinModeConfigField(pinField, 0x00000000UL, pin, &mode, NULL) != DRIVER_STATUS_SUCCESS)
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

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pin) == 0x00U) ||
		(GPIO_PIN_MODE_IS_VALID(mode) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (GPIO_PIN_MASK_REQUIRES_CRH(pin) != 0x00U)
	{
		GPIO_LL_READ_REG(GPIOx, CRH, gpioCrhRegImage);
	}
	if (GPIO_PIN_MASK_REQUIRES_CRL(pin) != 0x00U)
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

		if (GPIO_PIN_MASK_REQUIRES_CRH(currentPin) != 0x00U)
		{
			ASSERT_DRIVER_STATUS(GPIO_Helper_StagePinModeImage(currentPin, mode, &gpioCrhRegImage));
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			ASSERT_DRIVER_STATUS(GPIO_Helper_StagePinModeImage(currentPin, mode, &gpioCrlRegImage));
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
	gpio_pin_config_t config = GPIO_PIN_CONFIG_INPUT_ANALOG;
	gpio_pin_config_bits_t pinField = (gpio_pin_config_bits_t) 0x00U;
	uint32_t gpioOdrRegImage = 0x00000000UL;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PinMaskToIndex(pin) == GPIO_PIN_INDEX_INVALID))
	{
		return GPIO_PIN_CONFIG_INPUT_ANALOG;
	}

	pinField = GPIO_LL_ReadPinModeCNFField(GPIOx, pin);
	GPIO_LL_READ_REG(GPIOx, ODR, gpioOdrRegImage);

	if (GPIO_Helper_DecodePinModeConfigField(pinField, gpioOdrRegImage, pin, NULL, &config) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_CONFIG_INPUT_ANALOG;
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

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pin) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (GPIO_PIN_MASK_REQUIRES_CRH(pin) != 0x00U)
	{
		GPIO_LL_READ_REG(GPIOx, CRH, gpioCrhRegImage);
	}
	if (GPIO_PIN_MASK_REQUIRES_CRL(pin) != 0x00U)
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

		if (GPIO_PIN_MASK_REQUIRES_CRH(currentPin) != 0x00U)
		{
			ASSERT_DRIVER_STATUS(GPIO_Helper_StagePinConfigImage(currentPin, config, &gpioCrhRegImage));
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			ASSERT_DRIVER_STATUS(GPIO_Helper_StagePinConfigImage(currentPin, config, &gpioCrlRegImage));
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
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pGPIOConfig->pin) == 0x00U) ||
		(GPIO_PIN_MODE_IS_VALID(pGPIOConfig->mode) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(pGPIOConfig->config) == 0x00U) ||
		(GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(pGPIOConfig->mode, pGPIOConfig->config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(GPIO_LL_EnableClock(GPIOx));
	if (GPIO_PIN_CONFIG_IS_ALTERNATE(pGPIOConfig->config) != 0x00U)
	{
		ASSERT_DRIVER_STATUS(GPIO_LL_EnableAFIOClock());
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

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (GPIO_PIN_MASK_REQUIRES_CRL(pin) != 0x00U)
	{
		GPIO_LL_READ_REG(GPIOx, CRL, gpioCrlRegImage);
	}
	if (GPIO_PIN_MASK_REQUIRES_CRH(pin) != 0x00U)
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

		if (GPIO_PIN_MASK_REQUIRES_CRH(currentPin) != 0x00U)
		{
			ASSERT_DRIVER_STATUS(GPIO_Helper_StagePinResetConfigImage(currentPin, &gpioCrhRegImage));
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			ASSERT_DRIVER_STATUS(GPIO_Helper_StagePinResetConfigImage(currentPin, &gpioCrlRegImage));
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
	GPIO_LL_ResetPin(GPIOx, (gpio_pin_t) gpioBrrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t OB_LED_Init(void)
{
	gpio_config_t obLedConfig =
	{
		.pin = GPIO_OB_LED_PIN,
		.mode = GPIO_PIN_MODE_OUTPUT_2MHZ,
		.config = GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL
	};

	return GPIO_Init(GPIO_OB_LED_PORT, &obLedConfig);
}
