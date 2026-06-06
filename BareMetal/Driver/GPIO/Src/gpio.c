/**
 * @file	gpio.c
 * @author	Shrey Shah
 * @brief	GPIO Driver Implementation
 * @version	v1.4
 * @date	31-05-2026
 *
 * @details
 * This source is being rebuilt around the public GPIO APIs declared in
 * `gpio.h`. The driver owns validation, selected-pin iteration, staged
 * read-modify-write flow, and write ordering. LL owns direct register access.
 * Codec owns register-image mutation and extraction.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "gpio.h"
#include "gpio_codec.h"
#include "gpio_ll.h"

// ==================================================================================================== //
//												Local Defines											//
// ==================================================================================================== //

/** @brief CRL register image tracking bit @def GPIO_IMAGE_CRL */
#define GPIO_IMAGE_CRL							((uint8_t) 0x01U)
/** @brief CRH register image tracking bit @def GPIO_IMAGE_CRH */
#define GPIO_IMAGE_CRH							((uint8_t) 0x02U)
/** @brief GPIO pins controlled through CRL @def GPIO_PIN_MASK_CRL_RANGE */
#define GPIO_PIN_MASK_CRL_RANGE					\
	(GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7)
/** @brief GPIO pins controlled through CRH @def GPIO_PIN_MASK_CRH_RANGE */
#define GPIO_PIN_MASK_CRH_RANGE					\
	(GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15)

// ==================================================================================================== //
//										GPIO Driver Configuration APIs									//
// ==================================================================================================== //

driver_status_t GPIO_GetPinModeConfig
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pin,
	gpio_pin_mode_t* const		pMode,
	gpio_pin_config_t* const	pConfig
)
{
	// Local Variables
	reg gpioCrxRegImage = 0x00000000UL;
	reg gpioOdrRegImage = 0x00000000UL;

	// Validate Input
	if ((pMode == NULL) || (pConfig == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_HAS_ONLY_ONE_VALID_PIN(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Read each touched register image once before staging selected pins
	if ((pin & GPIO_PIN_MASK_CRH_RANGE) != GPIO_PIN_NONE)
	{
		gpioCrxRegImage = LL_GPIO_ReadCRH(GPIOx);
	}
	else
	{
		gpioCrxRegImage = LL_GPIO_ReadCRL(GPIOx);
	}
	gpioOdrRegImage = LL_GPIO_ReadODR(GPIOx);

	//! Extract the configuration from appropriate register
	if (Codec_GPIO_ExtractPinConfigMode(gpioCrxRegImage, gpioOdrRegImage, pin, pConfig, pMode) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_SetPinModeConfig
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pinMask,
	const gpio_pin_mode_t		mode,
	const gpio_pin_config_t		config
)
{
	// Local Variables
	reg gpioCrlRegImage = 0x00000000UL;
	reg gpioCrhRegImage = 0x00000000UL;
	reg initialGpioOdrRegImage = 0x00000000UL;
	reg gpioOdrRegImage = 0x00000000UL;
	reg gpioBsrrRegImage = 0x00000000UL;
	reg gpioBrrRegImage = 0x00000000UL;
	reg* pGpioCrxRegImage = NULL;
	gpio_pin_t remainingPins = pinMask;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	uint8_t crxImageMask = GPIO_IMAGE_CRL;
	uint8_t dirtyImages = 0x00U;
	const uint8_t pullConfigUsed = GPIO_PIN_MODE_CONFIG_IS_INPUT_PULL(mode, config);

	// Validate Input
	if
	(
		(GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U) ||
		(GPIO_PIN_MODE_IS_VALID(mode) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(config) == 0x00U) ||
		(GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, config) == 0x00U)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Read each touched register image once before staging selected pins
	if ((pinMask & GPIO_PIN_MASK_CRL_RANGE) != GPIO_PIN_NONE)
	{
		gpioCrlRegImage = LL_GPIO_ReadCRL(GPIOx);
	}
	if ((pinMask & GPIO_PIN_MASK_CRH_RANGE) != GPIO_PIN_NONE)
	{
		gpioCrhRegImage = LL_GPIO_ReadCRH(GPIOx);
	}
	if (pullConfigUsed != 0x00U)
	{
		initialGpioOdrRegImage = LL_GPIO_ReadODR(GPIOx);
		gpioOdrRegImage = initialGpioOdrRegImage;
	}

	//! Loop through each pin
	while (remainingPins != GPIO_PIN_NONE)
	{
		//! Extract lowest pin from pin mask
		currentPin = GPIO_PinMaskExtractLowestPin(remainingPins);

		//! CRH?
		if ((currentPin & GPIO_PIN_MASK_CRH_RANGE) != GPIO_PIN_NONE)
		{
			pGpioCrxRegImage = &gpioCrhRegImage;
			crxImageMask = GPIO_IMAGE_CRH;
		}
		//! CRL?
		else
		{
			pGpioCrxRegImage = &gpioCrlRegImage;
			crxImageMask = GPIO_IMAGE_CRL;
		}

		//! Stage the configuration to appropriate register
		if
		(
			Codec_GPIO_StagePinConfigMode
			(
				*pGpioCrxRegImage,
				gpioOdrRegImage,
				currentPin,
				config,
				mode,
				pGpioCrxRegImage,
				&gpioOdrRegImage
			) != DRIVER_STATUS_SUCCESS
		)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		//! Mark this as updated register image
		dirtyImages |= crxImageMask;

		//! Remove the lowest selected pin from pin mask
		ASSERT_DRIVER_STATUS(GPIO_PinMaskRemovePin(&remainingPins, currentPin));
	}

	//! Program pull-up/pull-down latch delta before exposing the CRL/CRH input-pull fields
	if (pullConfigUsed != 0x00U)
	{
		const reg gpioOdrChangedBits = (initialGpioOdrRegImage ^ gpioOdrRegImage);
		gpioBsrrRegImage = gpioOdrChangedBits & gpioOdrRegImage;
		gpioBrrRegImage = gpioOdrChangedBits & (~gpioOdrRegImage);
		if (gpioBrrRegImage != 0x00000000UL)
		{
			LL_GPIO_WriteBRR(GPIOx, gpioBrrRegImage);
		}
		if (gpioBsrrRegImage != 0x00000000UL)
		{
			LL_GPIO_WriteBSRR(GPIOx, gpioBsrrRegImage);
		}
	}

	//! Write each touched configuration register image after staging selected pins
	if ((dirtyImages & GPIO_IMAGE_CRL) != 0x00U)
	{
		LL_GPIO_WriteCRL(GPIOx, gpioCrlRegImage);
	}
	if ((dirtyImages & GPIO_IMAGE_CRH) != 0x00U)
	{
		LL_GPIO_WriteCRH(GPIOx, gpioCrhRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

gpio_pin_mode_t GPIO_GetPinMode(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	// Local Variables
	gpio_pin_mode_t mode = GPIO_PIN_MODE_INPUT;
	gpio_pin_config_t config = GPIO_PIN_CONFIG_INPUT_ANALOG;

	if (GPIO_GetPinModeConfig(GPIOx, pin, &mode, &config) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_MODE_INPUT;
	}

	return mode;
}

driver_status_t GPIO_SetPinMode
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pinMask,
	const gpio_pin_mode_t		mode
)
{
	// Local Variables
	gpio_pin_t remainingPins = pinMask;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	gpio_pin_config_t currentConfig = GPIO_PIN_CONFIG_INPUT_ANALOG;

	// Validate Input
	if
	(
		(GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U) ||
		(GPIO_PIN_MODE_IS_VALID(mode) == 0x00U)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Loop through each pin
	while (remainingPins != GPIO_PIN_NONE)
	{
		//! Extract lowest pin from pin mask
		currentPin = GPIO_PinMaskExtractLowestPin(remainingPins);
		currentConfig = GPIO_GetPinConfig(GPIOx, currentPin);
		if (GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, currentConfig) == 0x00U)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		//! Update the mode of the pin while retaining its configuration
		if (GPIO_SetPinModeConfig(GPIOx, currentPin, mode, currentConfig) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		ASSERT_DRIVER_STATUS(GPIO_PinMaskRemovePin(&remainingPins, currentPin));
	}

	return DRIVER_STATUS_SUCCESS;
}

gpio_pin_config_t GPIO_GetPinConfig(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	// Local Variables
	gpio_pin_mode_t mode = GPIO_PIN_MODE_INPUT;
	gpio_pin_config_t config = GPIO_PIN_CONFIG_INPUT_ANALOG;

	if (GPIO_GetPinModeConfig(GPIOx, pin, &mode, &config) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_CONFIG_INPUT_ANALOG;
	}

	return config;
}

driver_status_t GPIO_SetPinConfig
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pinMask,
	const gpio_pin_config_t		config
)
{
	// Local Variables
	gpio_pin_t remainingPins = pinMask;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	gpio_pin_mode_t currentMode = GPIO_PIN_MODE_INPUT;

	// Validate Input
	if
	(
		(GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(config) == 0x00U)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Loop through each pin
	while (remainingPins != GPIO_PIN_NONE)
	{
		//! Extract lowest pin from pin mask
		currentPin = GPIO_PinMaskExtractLowestPin(remainingPins);
		currentMode = GPIO_GetPinMode(GPIOx, currentPin);
		if (GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(currentMode, config) == 0x00U)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		//! Update the configuration of the pin while retaining its mode
		if (GPIO_SetPinModeConfig(GPIOx, currentPin, currentMode, config) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		ASSERT_DRIVER_STATUS(GPIO_PinMaskRemovePin(&remainingPins, currentPin));
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Init
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pinMask,
	const gpio_pin_mode_t		mode,
	const gpio_pin_config_t		config
)
{
	// Validate Input
	if
	(
		(GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U) ||
		(GPIO_PIN_MODE_IS_VALID(mode) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(config) == 0x00U) ||
		(GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, config) == 0x00U)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Enable the GPIO peripheral clock before touching the selected GPIO registers
	ASSERT_DRIVER_STATUS(LL_GPIO_EnableClock(GPIOx));

	//! Enable AFIO clock when the requested configuration uses alternate function output
	if (GPIO_PIN_CONFIG_IS_ALTERNATE(config) != 0x00U)
	{
		ASSERT_DRIVER_STATUS(LL_GPIO_EnableAFIOClock());
	}

	//! Apply requested selectors through the normal mode/config staging path
	return GPIO_SetPinModeConfig(GPIOx, pinMask, mode, config);
}

driver_status_t GPIO_Deinit(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask)
{
	//! Restore selected CRL/CRH fields to STM32F1 reset state: input floating
	ASSERT_DRIVER_STATUS(GPIO_SetPinModeConfig(GPIOx, pinMask, GPIO_PIN_MODE_INPUT, GPIO_PIN_CONFIG_INPUT_FLOATING));

	//! Restore selected output latch bits to their reset state through BRR
	LL_GPIO_WriteBRR(GPIOx, (reg) pinMask);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										GPIO Driver Pin State APIs										//
// ==================================================================================================== //

driver_status_t GPIO_PinGet(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	// Local Variables
	reg gpioIdrRegImage = 0x00000000UL;
	driver_status_t pinState = DRIVER_STATUS_OFF;

	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_HAS_ONLY_ONE_VALID_PIN(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Read the sampled input image and extract the selected pin state
	gpioIdrRegImage = LL_GPIO_ReadIDR(GPIOx);
	if (Codec_GPIO_ExtractPinInputState(gpioIdrRegImage, pin, &pinState) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	return pinState;
}

driver_status_t GPIO_PinSet(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask)
{
	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Set selected output latch bits through BSRR
	LL_GPIO_WriteBSRR(GPIOx, (reg) pinMask);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_PinReset(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask)
{
	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Reset selected output latch bits through BRR
	LL_GPIO_WriteBRR(GPIOx, (reg) pinMask);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_PinToggle(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask)
{
	// Local Variables
	reg gpioOdrRegImage = 0x00000000UL;

	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Toggle requires the current latch state, so this API owns the ODR read-modify-write path
	gpioOdrRegImage = LL_GPIO_ReadODR(GPIOx);
	gpioOdrRegImage ^= (reg) pinMask;
	LL_GPIO_WriteODR(GPIOx, gpioOdrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_LED_Init(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask)
{
	//! Initialize LED pins through the normal GPIO initialization path
	return GPIO_Init(GPIOx, pinMask, GPIO_PIN_MODE_OUTPUT_2MHZ, GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL);
}
