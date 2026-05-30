/**
 * @file	gpio_codec.c
 * @author	Shrey Shah
 * @brief	GPIO Selector Codec Implementation
 * @version	v1.0
 * @date	24-05-2026
 *
 * @details
 * This source file implements the GPIO codec layer. It encodes driver-facing
 * GPIO selectors into raw STM32F1 GPIO fields, decodes raw fields back into
 * driver-facing selectors, and mutates caller-owned register images. It does
 * not read or write peripheral hardware.
 */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //
#include "gpio_codec.h"

// ==================================================================================================== //
//                                          Local Codec Internals                                       //
// ==================================================================================================== //

/**
 * @brief Validates that a GPIO pin mask selects exactly one valid pin
 * @param[in]	pin	GPIO pin mask to check
 * @returns Single-pin validation status of @p pin
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p pin selects exactly one valid GPIO pin
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin is invalid, empty, or selects multiple pins
 */
__STATIC_FORCEINLINE driver_status_t GPIO_Codec_ValidateSinglePinMask(const gpio_pin_t pin)
{
	if ((GPIO_PIN_MASK_IS_VALID(pin) == 0x00U) || (GPIO_PIN_MASK_HAS_AT_MOST_ONE_BIT(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Encodes a driver GPIO mode selector into raw STM32F1 `MODE[1:0]` bits
 * @param[in]	mode	Driver-facing GPIO mode selector
 * @returns Raw GPIO `MODE[1:0]` field value
 * @retval - `0x00U`: Input mode field
 * @retval - `0x01U`: Output 10 MHz mode field
 * @retval - `0x02U`: Output 2 MHz mode field
 * @retval - `0x03U`: Output 50 MHz mode field
 * @note Caller should pass a valid @ref gpio_pin_mode_t selector.
 */
__STATIC_FORCEINLINE gpio_mode_t GPIO_Codec_EncodeModeBits(const gpio_pin_mode_t mode)
{
	gpio_mode_t modeBits = (gpio_mode_t) 0x00U;

	switch (mode)
	{
		case GPIO_PIN_MODE_INPUT:
		{
			modeBits = (gpio_mode_t) 0x00U;
			break;
		}
		case GPIO_PIN_MODE_OUTPUT_10MHZ:
		{
			modeBits = (gpio_mode_t) 0x01U;
			break;
		}
		case GPIO_PIN_MODE_OUTPUT_2MHZ:
		{
			modeBits = (gpio_mode_t) 0x02U;
			break;
		}
		case GPIO_PIN_MODE_OUTPUT_50MHZ:
		{
			modeBits = (gpio_mode_t) 0x03U;
			break;
		}
		default:
		{
			modeBits = (gpio_mode_t) 0x00U;
			break;
		}
	}

	return modeBits;
}

/**
 * @brief Encodes a driver GPIO config selector into raw STM32F1 `CNF[1:0]` bits
 * @param[in]	config	Driver-facing GPIO configuration selector
 * @returns Raw GPIO `CNF[1:0]` field value
 * @retval - `0x00U`: Analog input or push-pull output field
 * @retval - `0x01U`: Floating input or open-drain output field
 * @retval - `0x02U`: Pull input or alternate push-pull output field
 * @retval - `0x03U`: Alternate open-drain output field
 * @note Caller should pass a valid @ref gpio_pin_config_t selector.
 */
__STATIC_FORCEINLINE gpio_cnf_t GPIO_Codec_EncodeConfigBits(const gpio_pin_config_t config)
{
	gpio_cnf_t cnfBits = (gpio_cnf_t) 0x00U;

	switch (config)
	{
		case GPIO_PIN_CONFIG_INPUT_ANALOG:
		case GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL:
		{
			cnfBits = (gpio_cnf_t) 0x00U;
			break;
		}
		case GPIO_PIN_CONFIG_INPUT_FLOATING:
		case GPIO_PIN_CONFIG_OUTPUT_OPEN_DRAIN:
		{
			cnfBits = (gpio_cnf_t) 0x01U;
			break;
		}
		case GPIO_PIN_CONFIG_INPUT_PULL_DOWN:
		case GPIO_PIN_CONFIG_INPUT_PULL_UP:
		case GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL:
		{
			cnfBits = (gpio_cnf_t) 0x02U;
			break;
		}
		case GPIO_PIN_CONFIG_ALTERNATE_OPEN_DRAIN:
		{
			cnfBits = (gpio_cnf_t) 0x03U;
			break;
		}
		default:
		{
			cnfBits = (gpio_cnf_t) 0x00U;
			break;
		}
	}

	return cnfBits;
}

// ==================================================================================================== //
//                                             Codec APIs                                               //
// ==================================================================================================== //

driver_status_t GPIO_Codec_StagePinModeConfigImage
(
	const gpio_pin_t pin,
	const gpio_pin_mode_t mode,
	const gpio_pin_config_t config,
	uint32_t* const pCrxRegImage
)
{
	gpio_pin_config_bits_t pinField = (gpio_pin_config_bits_t) 0x00U;

	if (pCrxRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_Codec_ValidateSinglePinMask(pin) != DRIVER_STATUS_SUCCESS) ||
		(GPIO_PIN_MODE_IS_VALID(mode) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(config) == 0x00U) ||
		(GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	pinField = GPIO_LL_PackPinModeCNFField(GPIO_Codec_EncodeModeBits(mode), GPIO_Codec_EncodeConfigBits(config));

	*pCrxRegImage = GPIO_LL_SetPinModeCNFFieldInCRx(*pCrxRegImage, pin, pinField);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Codec_StagePinModeImage
(
	const gpio_pin_t pin,
	const gpio_pin_mode_t mode,
	uint32_t* const pCrxRegImage
)
{
	if (pCrxRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_Codec_ValidateSinglePinMask(pin) != DRIVER_STATUS_SUCCESS) || (GPIO_PIN_MODE_IS_VALID(mode) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pCrxRegImage = GPIO_LL_SetPinModeBitsInCRx(*pCrxRegImage, pin, GPIO_Codec_EncodeModeBits(mode));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Codec_StagePinConfigImage
(
	const gpio_pin_t pin,
	const gpio_pin_config_t config,
	uint32_t* const pCrxRegImage
)
{
	if (pCrxRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_Codec_ValidateSinglePinMask(pin) != DRIVER_STATUS_SUCCESS) || (GPIO_PIN_CONFIG_IS_VALID(config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pCrxRegImage = GPIO_LL_SetPinCNFBitsInCRx(*pCrxRegImage, pin, GPIO_Codec_EncodeConfigBits(config));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Codec_StagePinResetConfigImage
(
	const gpio_pin_t pin,
	uint32_t* const pCrxRegImage
)
{
	return GPIO_Codec_StagePinModeConfigImage
	(
		pin,
		GPIO_PIN_MODE_INPUT,
		GPIO_PIN_CONFIG_INPUT_FLOATING,
		pCrxRegImage
	);
}

driver_status_t GPIO_Codec_StagePinPullImage
(
	const gpio_pin_t pin,
	const gpio_pin_config_t config,
	uint32_t* const pOdrRegImage
)
{
	uint32_t regImage = 0x00000000UL;

	if (pOdrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_Codec_ValidateSinglePinMask(pin) != DRIVER_STATUS_SUCCESS) ||
		(
			((gpio_pin_config_t) config != GPIO_PIN_CONFIG_INPUT_PULL_DOWN) &&
			((gpio_pin_config_t) config != GPIO_PIN_CONFIG_INPUT_PULL_UP)
		))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	regImage = *pOdrRegImage;
	if ((gpio_pin_config_t) config == GPIO_PIN_CONFIG_INPUT_PULL_DOWN)
	{
		regImage &= ~(uint32_t) pin;
	}
	else
	{
		regImage |= (uint32_t) pin;
	}

	*pOdrRegImage = regImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Codec_DecodePinModeConfigField
(
	const gpio_pin_config_bits_t	crxField,
	const uint32_t					odrRegImage,
	const gpio_pin_t				pin,
	gpio_pin_mode_t* const			pMode,
	gpio_pin_config_t* const		pConfig
)
{
	gpio_mode_t modeBits = (gpio_mode_t) 0x00U;
	gpio_cnf_t cnfBits = (gpio_cnf_t) 0x00U;

	if ((pMode == NULL) && (pConfig == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (GPIO_Codec_ValidateSinglePinMask(pin) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	modeBits = GPIO_LL_GetModeBitsFromPinModeCNFField(crxField);
	cnfBits = GPIO_LL_GetCNFBitsFromPinModeCNFField(crxField);

	if (pMode != NULL)
	{
		switch (modeBits)
		{
			case (gpio_mode_t) 0x00U:
			{
				*pMode = GPIO_PIN_MODE_INPUT;
				break;
			}
			case (gpio_mode_t) 0x01U:
			{
				*pMode = GPIO_PIN_MODE_OUTPUT_10MHZ;
				break;
			}
			case (gpio_mode_t) 0x02U:
			{
				*pMode = GPIO_PIN_MODE_OUTPUT_2MHZ;
				break;
			}
			case (gpio_mode_t) 0x03U:
			{
				*pMode = GPIO_PIN_MODE_OUTPUT_50MHZ;
				break;
			}
			default:
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
		}
	}

	if (pConfig != NULL)
	{
		switch (modeBits)
		{
			case (gpio_mode_t) 0x00U:
			{
				switch (cnfBits)
				{
					case (gpio_cnf_t) 0x00U:
					{
						*pConfig = GPIO_PIN_CONFIG_INPUT_ANALOG;
						break;
					}
					case (gpio_cnf_t) 0x01U:
					{
						*pConfig = GPIO_PIN_CONFIG_INPUT_FLOATING;
						break;
					}
					case (gpio_cnf_t) 0x02U:
					{
						*pConfig = ((odrRegImage & (uint32_t) pin) != 0x00000000UL) ?
							GPIO_PIN_CONFIG_INPUT_PULL_UP :
							GPIO_PIN_CONFIG_INPUT_PULL_DOWN;
						break;
					}
					default:
					{
						return DRIVER_STATUS_ERROR_INVALID_ARG;
					}
				}
				break;
			}
			case (gpio_mode_t) 0x01U:
			case (gpio_mode_t) 0x02U:
			case (gpio_mode_t) 0x03U:
			{
				switch (cnfBits)
				{
					case (gpio_cnf_t) 0x00U:
					{
						*pConfig = GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL;
						break;
					}
					case (gpio_cnf_t) 0x01U:
					{
						*pConfig = GPIO_PIN_CONFIG_OUTPUT_OPEN_DRAIN;
						break;
					}
					case (gpio_cnf_t) 0x02U:
					{
						*pConfig = GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL;
						break;
					}
					case (gpio_cnf_t) 0x03U:
					{
						*pConfig = GPIO_PIN_CONFIG_ALTERNATE_OPEN_DRAIN;
						break;
					}
					default:
					{
						return DRIVER_STATUS_ERROR_INVALID_ARG;
					}
				}
				break;
			}
			default:
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
		}
	}

	return DRIVER_STATUS_SUCCESS;
}
