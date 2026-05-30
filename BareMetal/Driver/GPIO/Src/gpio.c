// ==================================================================================================== //
//                                                Includes                                              //
// ==================================================================================================== //
#include "gpio.h"
#include "gpio_codec.h"

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

static driver_status_t _GPIO_ReadPinConfigMode
(
	GPIO_TypeDef* const				GPIOx,
	const gpio_pin_index_t			pinIndex,
	gpio_pin_config_t* const			pConfig,
	gpio_pin_mode_t* const			pMode
)
{
	reg crxRegImage = 0x00000000UL;
	reg odrRegImage = 0x00000000UL;

	if ((pConfig == NULL) && (pMode == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	if (Codec_GPIO_PinIndexTargetsCRH(pinIndex) == DRIVER_STATUS_ON)
	{
		crxRegImage = LL_GPIO_ReadCRH(GPIOx);
	}
	else
	{
		crxRegImage = LL_GPIO_ReadCRL(GPIOx);
	}

	if (pConfig != NULL)
	{
		odrRegImage = LL_GPIO_ReadODR(GPIOx);
	}

	return Codec_GPIO_ExtractPinConfigMode(crxRegImage, odrRegImage, pinIndex, pConfig, pMode);
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
	reg gpioCrhRegImage = 0x00000000UL;
	reg gpioCrlRegImage = 0x00000000UL;
	reg gpioOdrRegImage = 0x00000000UL;
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	gpio_pin_index_t currentPinIndex = GPIO_PIN_INDEX_INVALID;
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

	if (pullConfigUsed != 0x00U)
	{
		gpioOdrRegImage = LL_GPIO_ReadODR(GPIOx);
	}

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_GetLowestSelectedPin(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		currentPinIndex = GPIO_PinMaskToIndex(currentPin);
		if (currentPinIndex == GPIO_PIN_INDEX_INVALID)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		if (Codec_GPIO_PinIndexTargetsCRH(currentPinIndex) == DRIVER_STATUS_ON)
		{
			if ((regStatus & GPIO_CRH_UPDATED) == 0x00U)
			{
				gpioCrhRegImage = LL_GPIO_ReadCRH(GPIOx);
			}
			if (Codec_GPIO_StagePinConfigMode
			(
				gpioCrhRegImage,
				gpioOdrRegImage,
				currentPinIndex,
				config,
				mode,
				&gpioCrhRegImage,
				&gpioOdrRegImage
			) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			if ((regStatus & GPIO_CRL_UPDATED) == 0x00U)
			{
				gpioCrlRegImage = LL_GPIO_ReadCRL(GPIOx);
			}
			if (Codec_GPIO_StagePinConfigMode
			(
				gpioCrlRegImage,
				gpioOdrRegImage,
				currentPinIndex,
				config,
				mode,
				&gpioCrlRegImage,
				&gpioOdrRegImage
			) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			regStatus |= GPIO_CRL_UPDATED;
		}

		if (pullConfigUsed != 0x00U)
		{
			regStatus |= GPIO_ODR_UPDATED;
		}

		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	if ((regStatus & GPIO_ODR_UPDATED) != 0x00U)
	{
		LL_GPIO_WriteODR(GPIOx, gpioOdrRegImage);
	}
	if ((regStatus & GPIO_CRH_UPDATED) != 0x00U)
	{
		LL_GPIO_WriteCRH(GPIOx, gpioCrhRegImage);
	}
	if ((regStatus & GPIO_CRL_UPDATED) != 0x00U)
	{
		LL_GPIO_WriteCRL(GPIOx, gpioCrlRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

gpio_pin_mode_t GPIO_GetPinMode(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	gpio_pin_mode_t mode = GPIO_PIN_MODE_INPUT;
	const gpio_pin_index_t pinIndex = GPIO_PinMaskToIndex(pin);

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (pinIndex == GPIO_PIN_INDEX_INVALID))
	{
		return GPIO_PIN_MODE_INPUT;
	}

	if (_GPIO_ReadPinConfigMode(GPIOx, pinIndex, NULL, &mode) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_MODE_INPUT;
	}

	return mode;
}

driver_status_t GPIO_SetPinMode(GPIO_TypeDef* const GPIOx, gpio_pin_t pin, const gpio_pin_mode_t mode)
{
	reg gpioCrhRegImage = 0x00000000UL;
	reg gpioCrlRegImage = 0x00000000UL;
	reg gpioOdrRegImage = 0x00000000UL;
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	gpio_pin_index_t currentPinIndex = GPIO_PIN_INDEX_INVALID;
	gpio_pin_config_t currentConfig = GPIO_PIN_CONFIG_INPUT_ANALOG;
	uint8_t regStatus = 0x00U;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pin) == 0x00U) ||
		(GPIO_PIN_MODE_IS_VALID(mode) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	gpioOdrRegImage = LL_GPIO_ReadODR(GPIOx);

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_GetLowestSelectedPin(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		currentPinIndex = GPIO_PinMaskToIndex(currentPin);
		if (currentPinIndex == GPIO_PIN_INDEX_INVALID)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		if (Codec_GPIO_PinIndexTargetsCRH(currentPinIndex) == DRIVER_STATUS_ON)
		{
			if ((regStatus & GPIO_CRH_UPDATED) == 0x00U)
			{
				gpioCrhRegImage = LL_GPIO_ReadCRH(GPIOx);
			}
			if (Codec_GPIO_ExtractPinConfigMode(gpioCrhRegImage, gpioOdrRegImage, currentPinIndex, &currentConfig, NULL) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			if (GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, currentConfig) == 0x00U)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
			if (Codec_GPIO_StagePinConfigMode
			(
				gpioCrhRegImage,
				gpioOdrRegImage,
				currentPinIndex,
				currentConfig,
				mode,
				&gpioCrhRegImage,
				&gpioOdrRegImage
			) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			if ((regStatus & GPIO_CRL_UPDATED) == 0x00U)
			{
				gpioCrlRegImage = LL_GPIO_ReadCRL(GPIOx);
			}
			if (Codec_GPIO_ExtractPinConfigMode(gpioCrlRegImage, gpioOdrRegImage, currentPinIndex, &currentConfig, NULL) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			if (GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, currentConfig) == 0x00U)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
			if (Codec_GPIO_StagePinConfigMode
			(
				gpioCrlRegImage,
				gpioOdrRegImage,
				currentPinIndex,
				currentConfig,
				mode,
				&gpioCrlRegImage,
				&gpioOdrRegImage
			) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			regStatus |= GPIO_CRL_UPDATED;
		}

		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	if ((regStatus & GPIO_CRH_UPDATED) != 0x00U)
	{
		LL_GPIO_WriteCRH(GPIOx, gpioCrhRegImage);
	}
	if ((regStatus & GPIO_CRL_UPDATED) != 0x00U)
	{
		LL_GPIO_WriteCRL(GPIOx, gpioCrlRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

gpio_pin_config_t GPIO_GetPinConfig(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	gpio_pin_config_t config = GPIO_PIN_CONFIG_INPUT_ANALOG;
	const gpio_pin_index_t pinIndex = GPIO_PinMaskToIndex(pin);

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (pinIndex == GPIO_PIN_INDEX_INVALID))
	{
		return GPIO_PIN_CONFIG_INPUT_ANALOG;
	}

	if (_GPIO_ReadPinConfigMode(GPIOx, pinIndex, &config, NULL) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_CONFIG_INPUT_ANALOG;
	}

	return config;
}

driver_status_t GPIO_SetPinConfig(GPIO_TypeDef* const GPIOx, gpio_pin_t pin, const gpio_pin_config_t config)
{
	reg gpioCrhRegImage = 0x00000000UL;
	reg gpioCrlRegImage = 0x00000000UL;
	reg gpioOdrRegImage = 0x00000000UL;
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	gpio_pin_index_t currentPinIndex = GPIO_PIN_INDEX_INVALID;
	gpio_pin_mode_t currentMode = GPIO_PIN_MODE_INPUT;
	uint8_t regStatus = 0x00U;
	const uint8_t pullConfigRequested =
	(
		(((gpio_pin_config_t) config) == GPIO_PIN_CONFIG_INPUT_PULL_DOWN) ||
		(((gpio_pin_config_t) config) == GPIO_PIN_CONFIG_INPUT_PULL_UP)
	) ? (uint8_t) 0x01U : (uint8_t) 0x00U;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pin) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (pullConfigRequested != 0x00U)
	{
		gpioOdrRegImage = LL_GPIO_ReadODR(GPIOx);
	}

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_GetLowestSelectedPin(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		currentPinIndex = GPIO_PinMaskToIndex(currentPin);
		if (currentPinIndex == GPIO_PIN_INDEX_INVALID)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		if (Codec_GPIO_PinIndexTargetsCRH(currentPinIndex) == DRIVER_STATUS_ON)
		{
			if ((regStatus & GPIO_CRH_UPDATED) == 0x00U)
			{
				gpioCrhRegImage = LL_GPIO_ReadCRH(GPIOx);
			}
			if (Codec_GPIO_ExtractPinConfigMode(gpioCrhRegImage, 0x00000000UL, currentPinIndex, NULL, &currentMode) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			if (GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(currentMode, config) == 0x00U)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
			if (Codec_GPIO_StagePinConfigMode
			(
				gpioCrhRegImage,
				gpioOdrRegImage,
				currentPinIndex,
				config,
				currentMode,
				&gpioCrhRegImage,
				&gpioOdrRegImage
			) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			if ((regStatus & GPIO_CRL_UPDATED) == 0x00U)
			{
				gpioCrlRegImage = LL_GPIO_ReadCRL(GPIOx);
			}
			if (Codec_GPIO_ExtractPinConfigMode(gpioCrlRegImage, 0x00000000UL, currentPinIndex, NULL, &currentMode) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			if (GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(currentMode, config) == 0x00U)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
			if (Codec_GPIO_StagePinConfigMode
			(
				gpioCrlRegImage,
				gpioOdrRegImage,
				currentPinIndex,
				config,
				currentMode,
				&gpioCrlRegImage,
				&gpioOdrRegImage
			) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			regStatus |= GPIO_CRL_UPDATED;
		}

		if (GPIO_PIN_MODE_CONFIG_IS_INPUT_PULL(currentMode, config) != 0x00U)
		{
			regStatus |= GPIO_ODR_UPDATED;
		}

		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	if ((regStatus & GPIO_ODR_UPDATED) != 0x00U)
	{
		LL_GPIO_WriteODR(GPIOx, gpioOdrRegImage);
	}
	if ((regStatus & GPIO_CRH_UPDATED) != 0x00U)
	{
		LL_GPIO_WriteCRH(GPIOx, gpioCrhRegImage);
	}
	if ((regStatus & GPIO_CRL_UPDATED) != 0x00U)
	{
		LL_GPIO_WriteCRL(GPIOx, gpioCrlRegImage);
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

	ASSERT_DRIVER_STATUS(LL_GPIO_EnableClock(GPIOx));
	if (GPIO_PIN_CONFIG_IS_ALTERNATE(pGPIOConfig->config) != 0x00U)
	{
		ASSERT_DRIVER_STATUS(LL_GPIO_EnableAFIOClock());
	}

	ASSERT_DRIVER_STATUS(GPIO_SetPinModeConfig(GPIOx, pGPIOConfig->pin, pGPIOConfig->mode, pGPIOConfig->config));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Deinit(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	reg gpioCrhRegImage = 0x00000000UL;
	reg gpioCrlRegImage = 0x00000000UL;
	reg gpioOdrRegImage = 0x00000000UL;
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	gpio_pin_index_t currentPinIndex = GPIO_PIN_INDEX_INVALID;
	uint8_t regStatus = 0x00U;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	gpioOdrRegImage = LL_GPIO_ReadODR(GPIOx);

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_GetLowestSelectedPin(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		currentPinIndex = GPIO_PinMaskToIndex(currentPin);
		if (currentPinIndex == GPIO_PIN_INDEX_INVALID)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		if (Codec_GPIO_PinIndexTargetsCRH(currentPinIndex) == DRIVER_STATUS_ON)
		{
			if ((regStatus & GPIO_CRH_UPDATED) == 0x00U)
			{
				gpioCrhRegImage = LL_GPIO_ReadCRH(GPIOx);
			}
			if (Codec_GPIO_StagePinConfigMode
			(
				gpioCrhRegImage,
				gpioOdrRegImage,
				currentPinIndex,
				GPIO_PIN_CONFIG_INPUT_FLOATING,
				GPIO_PIN_MODE_INPUT,
				&gpioCrhRegImage,
				&gpioOdrRegImage
			) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			if ((regStatus & GPIO_CRL_UPDATED) == 0x00U)
			{
				gpioCrlRegImage = LL_GPIO_ReadCRL(GPIOx);
			}
			if (Codec_GPIO_StagePinConfigMode
			(
				gpioCrlRegImage,
				gpioOdrRegImage,
				currentPinIndex,
				GPIO_PIN_CONFIG_INPUT_FLOATING,
				GPIO_PIN_MODE_INPUT,
				&gpioCrlRegImage,
				&gpioOdrRegImage
			) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			regStatus |= GPIO_CRL_UPDATED;
		}

		if (Codec_GPIO_StagePinOutputState
		(
			gpioOdrRegImage,
			currentPinIndex,
			DRIVER_STATUS_OFF,
			&gpioOdrRegImage
		) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	if ((regStatus & GPIO_CRH_UPDATED) != 0x00U)
	{
		LL_GPIO_WriteCRH(GPIOx, gpioCrhRegImage);
	}
	if ((regStatus & GPIO_CRL_UPDATED) != 0x00U)
	{
		LL_GPIO_WriteCRL(GPIOx, gpioCrlRegImage);
	}
	LL_GPIO_WriteODR(GPIOx, gpioOdrRegImage);

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
