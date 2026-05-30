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

static driver_status_t _GPIO_ReadPinModeConfigField
(
	GPIO_TypeDef* const				GPIOx,
	const gpio_pin_index_t			pinIndex,
	reg_field_t* const				pPinField
)
{
	reg crxRegImage = 0x00000000UL;

	if (pPinField == NULL)
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

	*pPinField = Codec_GPIO_ExtractPinModeConfigField(crxRegImage, pinIndex);
	return DRIVER_STATUS_SUCCESS;
}

static driver_status_t _GPIO_DecodePinModeConfigField
(
	const reg_field_t				pinField,
	const reg						odrRegImage,
	const gpio_pin_index_t			pinIndex,
	gpio_pin_mode_t* const			pMode,
	gpio_pin_config_t* const			pConfig
)
{
	if ((pMode == NULL) && (pConfig == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (Codec_GPIO_PinModeConfigFieldIsDecodable(pinField) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	if (pMode != NULL)
	{
		*pMode = Codec_GPIO_DecodePinMode(pinField);
	}
	if (pConfig != NULL)
	{
		*pConfig = Codec_GPIO_DecodePinConfig(pinField, odrRegImage, pinIndex);
	}

	return DRIVER_STATUS_SUCCESS;
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
			gpioCrhRegImage = Codec_GPIO_StagePinModeConfigImage(gpioCrhRegImage, currentPinIndex, mode, config);
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			if ((regStatus & GPIO_CRL_UPDATED) == 0x00U)
			{
				gpioCrlRegImage = LL_GPIO_ReadCRL(GPIOx);
			}
			gpioCrlRegImage = Codec_GPIO_StagePinModeConfigImage(gpioCrlRegImage, currentPinIndex, mode, config);
			regStatus |= GPIO_CRL_UPDATED;
		}

		if (pullConfigUsed != 0x00U)
		{
			gpioOdrRegImage = Codec_GPIO_StagePinPullImage(gpioOdrRegImage, currentPinIndex, config);
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
	reg_field_t pinField = (reg_field_t) 0x00U;
	const gpio_pin_index_t pinIndex = GPIO_PinMaskToIndex(pin);

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (pinIndex == GPIO_PIN_INDEX_INVALID))
	{
		return GPIO_PIN_MODE_INPUT;
	}

	if (_GPIO_ReadPinModeConfigField(GPIOx, pinIndex, &pinField) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_MODE_INPUT;
	}
	if (_GPIO_DecodePinModeConfigField(pinField, 0x00000000UL, pinIndex, &mode, NULL) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_MODE_INPUT;
	}

	return mode;
}

driver_status_t GPIO_SetPinMode(GPIO_TypeDef* const GPIOx, gpio_pin_t pin, const gpio_pin_mode_t mode)
{
	reg gpioCrhRegImage = 0x00000000UL;
	reg gpioCrlRegImage = 0x00000000UL;
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	gpio_pin_index_t currentPinIndex = GPIO_PIN_INDEX_INVALID;
	reg_field_t pinField = (reg_field_t) 0x00U;
	gpio_pin_config_t currentConfig = GPIO_PIN_CONFIG_INPUT_ANALOG;
	uint8_t regStatus = 0x00U;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pin) == 0x00U) ||
		(GPIO_PIN_MODE_IS_VALID(mode) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
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
			pinField = Codec_GPIO_ExtractPinModeConfigField(gpioCrhRegImage, currentPinIndex);
			if (_GPIO_DecodePinModeConfigField(pinField, 0x00000000UL, currentPinIndex, NULL, &currentConfig) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			if (GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, currentConfig) == 0x00U)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
			gpioCrhRegImage = Codec_GPIO_StagePinModeImage(gpioCrhRegImage, currentPinIndex, mode);
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			if ((regStatus & GPIO_CRL_UPDATED) == 0x00U)
			{
				gpioCrlRegImage = LL_GPIO_ReadCRL(GPIOx);
			}
			pinField = Codec_GPIO_ExtractPinModeConfigField(gpioCrlRegImage, currentPinIndex);
			if (_GPIO_DecodePinModeConfigField(pinField, 0x00000000UL, currentPinIndex, NULL, &currentConfig) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			if (GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, currentConfig) == 0x00U)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
			gpioCrlRegImage = Codec_GPIO_StagePinModeImage(gpioCrlRegImage, currentPinIndex, mode);
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
	reg_field_t pinField = (reg_field_t) 0x00U;
	reg gpioOdrRegImage = 0x00000000UL;
	const gpio_pin_index_t pinIndex = GPIO_PinMaskToIndex(pin);

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (pinIndex == GPIO_PIN_INDEX_INVALID))
	{
		return GPIO_PIN_CONFIG_INPUT_ANALOG;
	}

	if (_GPIO_ReadPinModeConfigField(GPIOx, pinIndex, &pinField) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_CONFIG_INPUT_ANALOG;
	}
	gpioOdrRegImage = LL_GPIO_ReadODR(GPIOx);

	if (_GPIO_DecodePinModeConfigField(pinField, gpioOdrRegImage, pinIndex, NULL, &config) != DRIVER_STATUS_SUCCESS)
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
	reg_field_t pinField = (reg_field_t) 0x00U;
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
			pinField = Codec_GPIO_ExtractPinModeConfigField(gpioCrhRegImage, currentPinIndex);
			if (_GPIO_DecodePinModeConfigField(pinField, 0x00000000UL, currentPinIndex, &currentMode, NULL) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			if (GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(currentMode, config) == 0x00U)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
			gpioCrhRegImage = Codec_GPIO_StagePinConfigImage(gpioCrhRegImage, currentPinIndex, config);
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			if ((regStatus & GPIO_CRL_UPDATED) == 0x00U)
			{
				gpioCrlRegImage = LL_GPIO_ReadCRL(GPIOx);
			}
			pinField = Codec_GPIO_ExtractPinModeConfigField(gpioCrlRegImage, currentPinIndex);
			if (_GPIO_DecodePinModeConfigField(pinField, 0x00000000UL, currentPinIndex, &currentMode, NULL) != DRIVER_STATUS_SUCCESS)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}
			if (GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(currentMode, config) == 0x00U)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
			gpioCrlRegImage = Codec_GPIO_StagePinConfigImage(gpioCrlRegImage, currentPinIndex, config);
			regStatus |= GPIO_CRL_UPDATED;
		}

		if (GPIO_PIN_MODE_CONFIG_IS_INPUT_PULL(currentMode, config) != 0x00U)
		{
			gpioOdrRegImage = Codec_GPIO_StagePinPullImage(gpioOdrRegImage, currentPinIndex, config);
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
			gpioCrhRegImage = Codec_GPIO_StagePinResetConfigImage(gpioCrhRegImage, currentPinIndex);
			regStatus |= GPIO_CRH_UPDATED;
		}
		else
		{
			if ((regStatus & GPIO_CRL_UPDATED) == 0x00U)
			{
				gpioCrlRegImage = LL_GPIO_ReadCRL(GPIOx);
			}
			gpioCrlRegImage = Codec_GPIO_StagePinResetConfigImage(gpioCrlRegImage, currentPinIndex);
			regStatus |= GPIO_CRL_UPDATED;
		}

		gpioOdrRegImage &= ~((reg) currentPin);
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
