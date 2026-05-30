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
 * @brief Validates that a GPIO pin index is inside the supported range
 * @param[in] pinIndex Zero-based GPIO pin index to check
 * @returns Pin-index validation status of @p pinIndex
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p pinIndex selects a valid GPIO pin
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinIndex is outside the supported range
 */
__STATIC_FORCEINLINE driver_status_t GPIO_Codec_ValidatePinIndex(const gpio_pin_index_t pinIndex)
{
	if (GPIO_PIN_INDEX_IS_VALID(pinIndex) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Returns the bit shift of one pin field inside its local CRL/CRH register image
 * @param[in] pinIndex Zero-based GPIO pin index
 * @returns Bit shift for the pin's four-bit MODE/CNF field inside CRL or CRH
 */
__STATIC_FORCEINLINE uint32_t GPIO_Codec_GetCRxFieldShiftFromPinIndex(const gpio_pin_index_t pinIndex)
{
	const gpio_pin_index_t localPinIndex = (gpio_pin_index_t) (pinIndex & GPIO_CODEC_CRX_LOCAL_PIN_INDEX_MASK);
	return ((uint32_t) localPinIndex * GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_WIDTH);
}

/**
 * @brief Packs raw MODE and CNF bits into one right-aligned MODE/CNF field
 * @param[in]	modeBits	Raw STM32F1 `MODE[1:0]` field value
 * @param[in]	cnfBits		Raw STM32F1 `CNF[1:0]` field value
 * @returns Right-aligned raw four-bit MODE/CNF field
 */
__STATIC_FORCEINLINE gpio_pin_config_bits_t GPIO_Codec_PackPinModeConfigField
(
	const gpio_mode_t modeBits,
	const gpio_cnf_t cnfBits
)
{
	return (gpio_pin_config_bits_t)
	(
		((((uint32_t) cnfBits) & GPIO_CODEC_CRX_CNF_BITS_MASK) << GPIO_CODEC_CRX_CNF_BITS_SHIFT) |
		((((uint32_t) modeBits) & GPIO_CODEC_CRX_MODE_BITS_MASK) << GPIO_CODEC_CRX_MODE_BITS_SHIFT)
	);
}

/**
 * @brief Sets one right-aligned MODE/CNF field inside a CRL/CRH register image
 * @param[in]	crxRegImage	CRL/CRH register image before replacement
 * @param[in]	pinIndex	Zero-based GPIO pin index
 * @param[in]	crxField	Right-aligned raw `CNF[1:0] | MODE[1:0]` field value
 * @returns Updated CRL/CRH register image
 */
__STATIC_FORCEINLINE uint32_t GPIO_Codec_SetPinModeConfigFieldInCRx
(
	const uint32_t					crxRegImage,
	const gpio_pin_index_t			pinIndex,
	const gpio_pin_config_bits_t	crxField
)
{
	uint32_t updatedRegImage = crxRegImage;
	const uint32_t fieldShift = GPIO_Codec_GetCRxFieldShiftFromPinIndex(pinIndex);
	const uint32_t fieldMask = BIT_VALUE(GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_MASK, fieldShift);

	updatedRegImage &= ~fieldMask;
	updatedRegImage |= BIT_VALUE((((uint32_t) crxField) & GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_MASK), fieldShift);

	return updatedRegImage;
}

/**
 * @brief Sets one raw MODE field inside a CRL/CRH register image
 * @param[in]	crxRegImage	CRL/CRH register image before replacement
 * @param[in]	pinIndex	Zero-based GPIO pin index
 * @param[in]	modeBits	Raw STM32F1 `MODE[1:0]` field value
 * @returns Updated CRL/CRH register image
 */
__STATIC_FORCEINLINE uint32_t GPIO_Codec_SetPinModeBitsInCRx
(
	const uint32_t			crxRegImage,
	const gpio_pin_index_t	pinIndex,
	const gpio_mode_t		modeBits
)
{
	uint32_t updatedRegImage = crxRegImage;
	const uint32_t fieldShift = GPIO_Codec_GetCRxFieldShiftFromPinIndex(pinIndex);
	const uint32_t modeShift = (fieldShift + GPIO_CODEC_CRX_MODE_BITS_SHIFT);
	const uint32_t modeMask = BIT_VALUE(GPIO_CODEC_CRX_MODE_BITS_MASK, modeShift);

	updatedRegImage &= ~modeMask;
	updatedRegImage |= BIT_VALUE((((uint32_t) modeBits) & GPIO_CODEC_CRX_MODE_BITS_MASK), modeShift);

	return updatedRegImage;
}

/**
 * @brief Sets one raw CNF field inside a CRL/CRH register image
 * @param[in]	crxRegImage	CRL/CRH register image before replacement
 * @param[in]	pinIndex	Zero-based GPIO pin index
 * @param[in]	cnfBits		Raw STM32F1 `CNF[1:0]` field value
 * @returns Updated CRL/CRH register image
 */
__STATIC_FORCEINLINE uint32_t GPIO_Codec_SetPinCNFBitsInCRx
(
	const uint32_t			crxRegImage,
	const gpio_pin_index_t	pinIndex,
	const gpio_cnf_t		cnfBits
)
{
	uint32_t updatedRegImage = crxRegImage;
	const uint32_t fieldShift = GPIO_Codec_GetCRxFieldShiftFromPinIndex(pinIndex);
	const uint32_t cnfShift = (fieldShift + GPIO_CODEC_CRX_CNF_BITS_SHIFT);
	const uint32_t cnfMask = BIT_VALUE(GPIO_CODEC_CRX_CNF_BITS_MASK, cnfShift);

	updatedRegImage &= ~cnfMask;
	updatedRegImage |= BIT_VALUE((((uint32_t) cnfBits) & GPIO_CODEC_CRX_CNF_BITS_MASK), cnfShift);

	return updatedRegImage;
}

/**
 * @brief Reads raw MODE bits from one right-aligned MODE/CNF field
 * @param[in] crxField Right-aligned raw MODE/CNF field
 * @returns Raw STM32F1 `MODE[1:0]` field value
 */
__STATIC_FORCEINLINE gpio_mode_t GPIO_Codec_GetModeBitsFromPinModeConfigField(const gpio_pin_config_bits_t crxField)
{
	return (gpio_mode_t) ((((uint32_t) crxField) >> GPIO_CODEC_CRX_MODE_BITS_SHIFT) & GPIO_CODEC_CRX_MODE_BITS_MASK);
}

/**
 * @brief Reads raw CNF bits from one right-aligned MODE/CNF field
 * @param[in] crxField Right-aligned raw MODE/CNF field
 * @returns Raw STM32F1 `CNF[1:0]` field value
 */
__STATIC_FORCEINLINE gpio_cnf_t GPIO_Codec_GetCNFBitsFromPinModeConfigField(const gpio_pin_config_bits_t crxField)
{
	return (gpio_cnf_t)
	(
		(((uint32_t) crxField) >> GPIO_CODEC_CRX_CNF_BITS_SHIFT) &
		GPIO_CODEC_CRX_CNF_BITS_MASK
	);
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

driver_status_t GPIO_Codec_GetPinModeConfigField
(
	const uint32_t				crxRegImage,
	const gpio_pin_index_t		pinIndex,
	gpio_pin_config_bits_t* const pCrxField
)
{
	const uint32_t fieldShift = GPIO_Codec_GetCRxFieldShiftFromPinIndex(pinIndex);

	if (pCrxField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (GPIO_Codec_ValidatePinIndex(pinIndex) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pCrxField = (gpio_pin_config_bits_t)
	(
		(crxRegImage >> fieldShift) & GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_MASK
	);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Codec_StagePinModeConfigImage
(
	const gpio_pin_index_t pinIndex,
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
	if ((GPIO_Codec_ValidatePinIndex(pinIndex) != DRIVER_STATUS_SUCCESS) ||
		(GPIO_PIN_MODE_IS_VALID(mode) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(config) == 0x00U) ||
		(GPIO_PIN_MODE_CONFIG_IS_VALID_PAIR(mode, config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	pinField = GPIO_Codec_PackPinModeConfigField(GPIO_Codec_EncodeModeBits(mode), GPIO_Codec_EncodeConfigBits(config));

	*pCrxRegImage = GPIO_Codec_SetPinModeConfigFieldInCRx(*pCrxRegImage, pinIndex, pinField);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Codec_StagePinModeImage
(
	const gpio_pin_index_t pinIndex,
	const gpio_pin_mode_t mode,
	uint32_t* const pCrxRegImage
)
{
	if (pCrxRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_Codec_ValidatePinIndex(pinIndex) != DRIVER_STATUS_SUCCESS) || (GPIO_PIN_MODE_IS_VALID(mode) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pCrxRegImage = GPIO_Codec_SetPinModeBitsInCRx(*pCrxRegImage, pinIndex, GPIO_Codec_EncodeModeBits(mode));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Codec_StagePinConfigImage
(
	const gpio_pin_index_t pinIndex,
	const gpio_pin_config_t config,
	uint32_t* const pCrxRegImage
)
{
	if (pCrxRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_Codec_ValidatePinIndex(pinIndex) != DRIVER_STATUS_SUCCESS) || (GPIO_PIN_CONFIG_IS_VALID(config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pCrxRegImage = GPIO_Codec_SetPinCNFBitsInCRx(*pCrxRegImage, pinIndex, GPIO_Codec_EncodeConfigBits(config));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Codec_StagePinResetConfigImage
(
	const gpio_pin_index_t pinIndex,
	uint32_t* const pCrxRegImage
)
{
	return GPIO_Codec_StagePinModeConfigImage
	(
		pinIndex,
		GPIO_PIN_MODE_INPUT,
		GPIO_PIN_CONFIG_INPUT_FLOATING,
		pCrxRegImage
	);
}

driver_status_t GPIO_Codec_StagePinPullImage
(
	const gpio_pin_index_t pinIndex,
	const gpio_pin_config_t config,
	uint32_t* const pOdrRegImage
)
{
	uint32_t regImage = 0x00000000UL;
	gpio_pin_t pinMask = GPIO_PIN_NONE;

	if (pOdrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_Codec_ValidatePinIndex(pinIndex) != DRIVER_STATUS_SUCCESS) ||
		(
			((gpio_pin_config_t) config != GPIO_PIN_CONFIG_INPUT_PULL_DOWN) &&
			((gpio_pin_config_t) config != GPIO_PIN_CONFIG_INPUT_PULL_UP)
		))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	regImage = *pOdrRegImage;
	pinMask = GPIO_PIN_INDEX_TO_MASK(pinIndex);
	if ((gpio_pin_config_t) config == GPIO_PIN_CONFIG_INPUT_PULL_DOWN)
	{
		regImage &= ~((uint32_t) pinMask);
	}
	else
	{
		regImage |= (uint32_t) pinMask;
	}

	*pOdrRegImage = regImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_Codec_DecodePinModeConfigField
(
	const gpio_pin_config_bits_t	crxField,
	const uint32_t					odrRegImage,
	const gpio_pin_index_t			pinIndex,
	gpio_pin_mode_t* const			pMode,
	gpio_pin_config_t* const		pConfig
)
{
	gpio_mode_t modeBits = (gpio_mode_t) 0x00U;
	gpio_cnf_t cnfBits = (gpio_cnf_t) 0x00U;
	gpio_pin_t pinMask = GPIO_PIN_NONE;

	if ((pMode == NULL) && (pConfig == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (GPIO_Codec_ValidatePinIndex(pinIndex) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	modeBits = GPIO_Codec_GetModeBitsFromPinModeConfigField(crxField);
	cnfBits = GPIO_Codec_GetCNFBitsFromPinModeConfigField(crxField);
	pinMask = GPIO_PIN_INDEX_TO_MASK(pinIndex);

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
						*pConfig = ((odrRegImage & (uint32_t) pinMask) != 0x00000000UL) ?
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
