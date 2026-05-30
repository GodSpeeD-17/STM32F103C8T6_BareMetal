/**
 * @file	gpio.c
 * @author	Shrey Shah
 * @brief	GPIO Driver Implementation
 * @version	v1.4
 * @date	30-05-2026
 *
 * @details
 * This source owns public GPIO validation, selected-pin iteration, register-image
 * batching, clock sequencing, and write ordering. Direct hardware access stays
 * behind LL accessors and raw selector translation stays behind Codec helpers.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "gpio.h"
#include "gpio_codec.h"
#include "gpio_ll.h"

// ==================================================================================================== //
//											Local Defines												//
// ==================================================================================================== //

/** @brief CRL image loaded/dirty tracking bit @def GPIO_DRIVER_REG_IMAGE_CRL */
#define GPIO_DRIVER_REG_IMAGE_CRL					((uint8_t) 0x01U)
/** @brief CRH image loaded/dirty tracking bit @def GPIO_DRIVER_REG_IMAGE_CRH */
#define GPIO_DRIVER_REG_IMAGE_CRH					((uint8_t) 0x02U)
/** @brief ODR image loaded/dirty tracking bit @def GPIO_DRIVER_REG_IMAGE_ODR */
#define GPIO_DRIVER_REG_IMAGE_ODR					((uint8_t) 0x04U)

// ==================================================================================================== //
//											Local Types													//
// ==================================================================================================== //

/**
 * @brief Caller-owned GPIO register images used during one public driver operation
 */
typedef struct _gpio_driver_register_images_t
{
	/** @brief Staged CRL image */
	reg		crl;
	/** @brief Staged CRH image */
	reg		crh;
	/** @brief Staged ODR image */
	reg		odr;
	/** @brief Bitmask of register images already read from hardware */
	uint8_t	loaded;
	/** @brief Bitmask of register images modified locally and requiring writeback */
	uint8_t	dirty;
} gpio_driver_register_images_t;

// ==================================================================================================== //
//											Local Pin Helpers											//
// ==================================================================================================== //

/**
 * @brief Extracts the lowest selected single-pin mask from a pin mask
 * @param[in] pinMask GPIO pin mask
 * @returns Lowest selected GPIO pin mask
 * @retval - @ref `GPIO_PIN_NONE`: @p pinMask is empty
 * @retval - @ref `GPIO_PIN_0`..@ref `GPIO_PIN_15`: Lowest selected pin
 */
static gpio_pin_t _GPIO_ExtractLowestSelectedPin(const gpio_pin_t pinMask)
{
	// Local Variable
	gpio_pin_t selectedPin = GPIO_PIN_NONE;

	//! Isolate the least-significant set bit in the selected pin mask
	selectedPin = (gpio_pin_t) (((uint32_t) pinMask) & (0UL - ((uint32_t) pinMask)));

	return selectedPin;
}

/**
 * @brief Clears the lowest selected single-pin mask from a pin mask
 * @param[in] pinMask GPIO pin mask before clearing
 * @returns GPIO pin mask with the lowest selected bit cleared
 */
static gpio_pin_t _GPIO_ClearLowestSelectedPin(const gpio_pin_t pinMask)
{
	// Local Variable
	gpio_pin_t remainingPins = GPIO_PIN_NONE;

	//! Clear the least-significant set bit so the next while iteration visits the next selected pin
	remainingPins = (gpio_pin_t) (((uint32_t) pinMask) & (((uint32_t) pinMask) - 1UL));

	return remainingPins;
}

/**
 * @brief Pops the next selected pin index from a remaining pin mask
 * @param[in,out] pRemainingPins Remaining GPIO pin mask
 * @param[out] pPinIndex Destination for the popped GPIO pin index
 * @returns Pop status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: One selected pin index was popped
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: A required output pointer is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The remaining mask could not be decoded
 */
static driver_status_t _GPIO_PopNextSelectedPinIndex
(
	gpio_pin_t* const			pRemainingPins,
	gpio_pin_index_t* const		pPinIndex
)
{
	// Local Variables
	gpio_pin_t selectedPin = GPIO_PIN_NONE;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Input
	if ((pRemainingPins == NULL) || (pPinIndex == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Extract exactly one selected pin from the remaining bit mask
	selectedPin = _GPIO_ExtractLowestSelectedPin(*pRemainingPins);
	if (selectedPin == GPIO_PIN_NONE)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Convert the single-pin mask to a zero-based pin index before entering Codec
	pinIndex = GPIO_PinMaskToIndex(selectedPin);
	if (pinIndex == GPIO_PIN_INDEX_INVALID)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Remove the selected bit from the remaining mask for the next while iteration
	*pRemainingPins = _GPIO_ClearLowestSelectedPin(*pRemainingPins);
	*pPinIndex = pinIndex;

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local Register Image Helpers									//
// ==================================================================================================== //

/**
 * @brief Loads ODR into the staged register-image set if it has not been read yet
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in,out] pImages Staged register-image set
 */
static void _GPIO_LoadODRImage(GPIO_TypeDef* const GPIOx, gpio_driver_register_images_t* const pImages)
{
	if ((pImages->loaded & GPIO_DRIVER_REG_IMAGE_ODR) == 0x00U)
	{
		pImages->odr = LL_GPIO_ReadODR(GPIOx);
		pImages->loaded |= GPIO_DRIVER_REG_IMAGE_ODR;
	}
}

/**
 * @brief Loads the CRL/CRH image that owns one pin index
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[in,out] pImages Staged register-image set
 * @param[out] ppCrxImage Destination for the selected CRL/CRH image pointer
 * @param[out] pCrxMask Destination for the selected CRL/CRH tracking mask
 * @returns Register-image selection status
 */
static driver_status_t _GPIO_LoadCRxImageForPin
(
	GPIO_TypeDef* const							GPIOx,
	const gpio_pin_index_t						pinIndex,
	gpio_driver_register_images_t* const			pImages,
	reg** const									ppCrxImage,
	uint8_t* const								pCrxMask
)
{
	// Validate Input
	if ((pImages == NULL) || (ppCrxImage == NULL) || (pCrxMask == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	if (Codec_GPIO_PinIndexTargetsCRH(pinIndex) == DRIVER_STATUS_ON)
	{
		if ((pImages->loaded & GPIO_DRIVER_REG_IMAGE_CRH) == 0x00U)
		{
			pImages->crh = LL_GPIO_ReadCRH(GPIOx);
			pImages->loaded |= GPIO_DRIVER_REG_IMAGE_CRH;
		}
		*ppCrxImage = &(pImages->crh);
		*pCrxMask = GPIO_DRIVER_REG_IMAGE_CRH;
	}
	else
	{
		if ((pImages->loaded & GPIO_DRIVER_REG_IMAGE_CRL) == 0x00U)
		{
			pImages->crl = LL_GPIO_ReadCRL(GPIOx);
			pImages->loaded |= GPIO_DRIVER_REG_IMAGE_CRL;
		}
		*ppCrxImage = &(pImages->crl);
		*pCrxMask = GPIO_DRIVER_REG_IMAGE_CRL;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Writes all dirty GPIO register images in hardware-safe order
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pImages Staged register-image set
 * @note ODR is written before CRL/CRH so input pull-up/down latch state is ready
 * before exposing the CRx input-pull configuration.
 */
static void _GPIO_WriteDirtyImages(GPIO_TypeDef* const GPIOx, const gpio_driver_register_images_t* const pImages)
{
	if ((pImages->dirty & GPIO_DRIVER_REG_IMAGE_ODR) != 0x00U)
	{
		LL_GPIO_WriteODR(GPIOx, pImages->odr);
	}
	if ((pImages->dirty & GPIO_DRIVER_REG_IMAGE_CRL) != 0x00U)
	{
		LL_GPIO_WriteCRL(GPIOx, pImages->crl);
	}
	if ((pImages->dirty & GPIO_DRIVER_REG_IMAGE_CRH) != 0x00U)
	{
		LL_GPIO_WriteCRH(GPIOx, pImages->crh);
	}
}

/**
 * @brief Extracts one pin's current config/mode selectors through staged images
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in,out] pImages Staged register-image set
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[out] pConfig Optional destination for decoded GPIO config
 * @param[out] pMode Optional destination for decoded GPIO mode
 * @returns Extraction status
 */
static driver_status_t _GPIO_ExtractPinConfigMode
(
	GPIO_TypeDef* const							GPIOx,
	gpio_driver_register_images_t* const			pImages,
	const gpio_pin_index_t						pinIndex,
	gpio_pin_config_t* const						pConfig,
	gpio_pin_mode_t* const						pMode
)
{
	// Local Variables
	reg* pCrxImage = NULL;
	uint8_t crxMask = 0x00U;

	// Validate Input
	if ((pConfig == NULL) && (pMode == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_GPIO_LoadCRxImageForPin(GPIOx, pinIndex, pImages, &pCrxImage, &crxMask));
	(void) crxMask;

	if (pConfig != NULL)
	{
		_GPIO_LoadODRImage(GPIOx, pImages);
	}

	return Codec_GPIO_ExtractPinConfigMode(*pCrxImage, pImages->odr, pinIndex, pConfig, pMode);
}

/**
 * @brief Stages one pin's config/mode selectors through staged images
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in,out] pImages Staged register-image set
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[in] config Driver GPIO configuration selector
 * @param[in] mode Driver GPIO mode selector
 * @returns Staging status
 */
static driver_status_t _GPIO_StagePinConfigMode
(
	GPIO_TypeDef* const							GPIOx,
	gpio_driver_register_images_t* const			pImages,
	const gpio_pin_index_t						pinIndex,
	const gpio_pin_config_t						config,
	const gpio_pin_mode_t						mode
)
{
	// Local Variables
	reg* pCrxImage = NULL;
	uint8_t crxMask = 0x00U;

	ASSERT_DRIVER_STATUS(_GPIO_LoadCRxImageForPin(GPIOx, pinIndex, pImages, &pCrxImage, &crxMask));

	if (GPIO_PIN_MODE_CONFIG_IS_INPUT_PULL(mode, config) != 0x00U)
	{
		_GPIO_LoadODRImage(GPIOx, pImages);
	}

	if (Codec_GPIO_StagePinConfigMode
	(
		*pCrxImage,
		pImages->odr,
		pinIndex,
		config,
		mode,
		pCrxImage,
		&(pImages->odr)
	) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	pImages->dirty |= crxMask;
	if (GPIO_PIN_MODE_CONFIG_IS_INPUT_PULL(mode, config) != 0x00U)
	{
		pImages->dirty |= GPIO_DRIVER_REG_IMAGE_ODR;
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//											GPIO Driver APIs											//
// ==================================================================================================== //

driver_status_t GPIO_SetPinModeConfig
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pin,
	const gpio_pin_mode_t		mode,
	const gpio_pin_config_t		config
)
{
	// Local Variables
	gpio_driver_register_images_t images = {0};
	gpio_pin_t remainingPins = pin;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pin) == 0x00U) ||
		(GPIO_PIN_MODE_IS_VALID(mode) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(config) == 0x00U) ||
		(GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	while (remainingPins != GPIO_PIN_NONE)
	{
		ASSERT_DRIVER_STATUS(_GPIO_PopNextSelectedPinIndex(&remainingPins, &pinIndex));
		ASSERT_DRIVER_STATUS(_GPIO_StagePinConfigMode(GPIOx, &images, pinIndex, config, mode));
	}

	_GPIO_WriteDirtyImages(GPIOx, &images);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_SetPinMode
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pin,
	const gpio_pin_mode_t		mode
)
{
	// Local Variables
	gpio_driver_register_images_t images = {0};
	gpio_pin_t remainingPins = pin;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;
	gpio_pin_config_t currentConfig = GPIO_PIN_CONFIG_INPUT_ANALOG;

	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pin) == 0x00U) ||
		(GPIO_PIN_MODE_IS_VALID(mode) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	while (remainingPins != GPIO_PIN_NONE)
	{
		ASSERT_DRIVER_STATUS(_GPIO_PopNextSelectedPinIndex(&remainingPins, &pinIndex));
		if (_GPIO_ExtractPinConfigMode(GPIOx, &images, pinIndex, &currentConfig, NULL) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
		if (GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, currentConfig) == 0x00U)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
		ASSERT_DRIVER_STATUS(_GPIO_StagePinConfigMode(GPIOx, &images, pinIndex, currentConfig, mode));
	}

	_GPIO_WriteDirtyImages(GPIOx, &images);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_SetPinConfig
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pin,
	const gpio_pin_config_t		config
)
{
	// Local Variables
	gpio_driver_register_images_t images = {0};
	gpio_pin_t remainingPins = pin;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;
	gpio_pin_mode_t currentMode = GPIO_PIN_MODE_INPUT;

	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pin) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	while (remainingPins != GPIO_PIN_NONE)
	{
		ASSERT_DRIVER_STATUS(_GPIO_PopNextSelectedPinIndex(&remainingPins, &pinIndex));
		if (_GPIO_ExtractPinConfigMode(GPIOx, &images, pinIndex, NULL, &currentMode) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
		if (GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(currentMode, config) == 0x00U)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
		ASSERT_DRIVER_STATUS(_GPIO_StagePinConfigMode(GPIOx, &images, pinIndex, config, currentMode));
	}

	_GPIO_WriteDirtyImages(GPIOx, &images);

	return DRIVER_STATUS_SUCCESS;
}

gpio_pin_mode_t GPIO_GetPinMode(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	// Local Variables
	gpio_driver_register_images_t images = {0};
	gpio_pin_mode_t mode = GPIO_PIN_MODE_INPUT;
	const gpio_pin_index_t pinIndex = GPIO_PinMaskToIndex(pin);

	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (pinIndex == GPIO_PIN_INDEX_INVALID))
	{
		return GPIO_PIN_MODE_INPUT;
	}

	if (_GPIO_ExtractPinConfigMode(GPIOx, &images, pinIndex, NULL, &mode) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_MODE_INPUT;
	}

	return mode;
}

gpio_pin_config_t GPIO_GetPinConfig(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	// Local Variables
	gpio_driver_register_images_t images = {0};
	gpio_pin_config_t config = GPIO_PIN_CONFIG_INPUT_ANALOG;
	const gpio_pin_index_t pinIndex = GPIO_PinMaskToIndex(pin);

	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (pinIndex == GPIO_PIN_INDEX_INVALID))
	{
		return GPIO_PIN_CONFIG_INPUT_ANALOG;
	}

	if (_GPIO_ExtractPinConfigMode(GPIOx, &images, pinIndex, &config, NULL) != DRIVER_STATUS_SUCCESS)
	{
		return GPIO_PIN_CONFIG_INPUT_ANALOG;
	}

	return config;
}

driver_status_t GPIO_Init(GPIO_TypeDef* const GPIOx, const gpio_config_t* const pGPIOConfig)
{
	// Validate Input
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
	// Local Variables
	gpio_driver_register_images_t images = {0};
	gpio_pin_t remainingPins = pin;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	while (remainingPins != GPIO_PIN_NONE)
	{
		ASSERT_DRIVER_STATUS(_GPIO_PopNextSelectedPinIndex(&remainingPins, &pinIndex));
		ASSERT_DRIVER_STATUS(_GPIO_StagePinConfigMode
		(
			GPIOx,
			&images,
			pinIndex,
			GPIO_PIN_CONFIG_INPUT_FLOATING,
			GPIO_PIN_MODE_INPUT
		));
	}

	_GPIO_WriteDirtyImages(GPIOx, &images);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_PinSet(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	// Local Variables
	reg gpioOdrRegImage = 0x00000000UL;
	gpio_pin_t remainingPins = pin;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	gpioOdrRegImage = LL_GPIO_ReadODR(GPIOx);
	while (remainingPins != GPIO_PIN_NONE)
	{
		ASSERT_DRIVER_STATUS(_GPIO_PopNextSelectedPinIndex(&remainingPins, &pinIndex));
		if (Codec_GPIO_StagePinOutputState(gpioOdrRegImage, pinIndex, DRIVER_STATUS_ON, &gpioOdrRegImage) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
	}
	LL_GPIO_WriteODR(GPIOx, gpioOdrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_PinReset(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	// Local Variables
	reg gpioOdrRegImage = 0x00000000UL;
	gpio_pin_t remainingPins = pin;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	gpioOdrRegImage = LL_GPIO_ReadODR(GPIOx);
	while (remainingPins != GPIO_PIN_NONE)
	{
		ASSERT_DRIVER_STATUS(_GPIO_PopNextSelectedPinIndex(&remainingPins, &pinIndex));
		if (Codec_GPIO_StagePinOutputState(gpioOdrRegImage, pinIndex, DRIVER_STATUS_OFF, &gpioOdrRegImage) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
	}
	LL_GPIO_WriteODR(GPIOx, gpioOdrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_PinToggle(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	// Local Variables
	reg gpioOdrRegImage = 0x00000000UL;
	gpio_pin_t remainingPins = pin;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;
	driver_status_t pinState = DRIVER_STATUS_OFF;

	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	gpioOdrRegImage = LL_GPIO_ReadODR(GPIOx);
	while (remainingPins != GPIO_PIN_NONE)
	{
		ASSERT_DRIVER_STATUS(_GPIO_PopNextSelectedPinIndex(&remainingPins, &pinIndex));
		if (Codec_GPIO_ExtractPinOutputState(gpioOdrRegImage, pinIndex, &pinState) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
		pinState = (pinState == DRIVER_STATUS_ON) ? DRIVER_STATUS_OFF : DRIVER_STATUS_ON;
		if (Codec_GPIO_StagePinOutputState(gpioOdrRegImage, pinIndex, pinState, &gpioOdrRegImage) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
	}
	LL_GPIO_WriteODR(GPIOx, gpioOdrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

uint8_t GPIO_Get(GPIO_TypeDef* const GPIOx, const gpio_pin_t pin)
{
	// Local Variables
	reg gpioIdrRegImage = 0x00000000UL;
	driver_status_t pinState = DRIVER_STATUS_OFF;
	const gpio_pin_index_t pinIndex = GPIO_PinMaskToIndex(pin);

	// Validate Input
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (pinIndex == GPIO_PIN_INDEX_INVALID))
	{
		return (uint8_t) 0x00U;
	}

	gpioIdrRegImage = LL_GPIO_ReadIDR(GPIOx);
	if (Codec_GPIO_ExtractPinInputState(gpioIdrRegImage, pinIndex, &pinState) != DRIVER_STATUS_SUCCESS)
	{
		return (uint8_t) 0x00U;
	}

	return (pinState == DRIVER_STATUS_ON) ? (uint8_t) 0x01U : (uint8_t) 0x00U;
}

driver_status_t GPIO_LED_Init(GPIO_TypeDef* const GPIOx, gpio_config_t* const pGPIOConfig)
{
	// Validate Input
	if (pGPIOConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	pGPIOConfig->mode = GPIO_PIN_MODE_OUTPUT_10MHZ;
	pGPIOConfig->config = GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL;

	return GPIO_Init(GPIOx, pGPIOConfig);
}

#ifdef STM32F103C8T6__
driver_status_t OB_LED_Init(void)
{
	// Local Variable
	gpio_config_t obLedConfig = GPIO_OB_LED_CONFIG();

	return GPIO_Init(GPIO_OB_LED_PORT, &obLedConfig);
}

void OB_LED_Set(void)
{
	(void) GPIO_PinReset(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

void OB_LED_Reset(void)
{
	(void) GPIO_PinSet(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

void OB_LED_Toggle(void)
{
	(void) GPIO_PinToggle(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

driver_status_t OB_LED_Deinit(void)
{
	return GPIO_Deinit(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}
#endif /* STM32F103C8T6__ */
