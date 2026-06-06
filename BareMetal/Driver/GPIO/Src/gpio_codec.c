/**
 * @file	gpio_codec.c
 * @author	Shrey Shah
 * @brief	GPIO Selector Codec Implementation
 * @version	v1.1
 * @date	30-05-2026
 *
 * @details
 * This source file implements the GPIO codec layer. It encodes driver-facing
 * GPIO selectors into raw STM32F1 GPIO fields, decodes raw fields back into
 * driver-facing selectors, and returns updated caller-owned register images.
 * It does not read or write peripheral hardware.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "gpio_codec.h"

// ==================================================================================================== //
//												Local Defines											//
// ==================================================================================================== //

/** @brief Width of one CRL/CRH pin MODE/CNF field @def GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_WIDTH */
#define GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_WIDTH		((reg_field_t) 0x04U)
/** @brief Raw right-aligned four-bit CRL/CRH pin MODE/CNF field mask @def GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_MASK */
#define GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_MASK		((reg_field_t) 0x0FU)
/** @brief Local pin-index mask inside one CRL/CRH register @def GPIO_CODEC_CRX_LOCAL_PIN_INDEX_MASK */
#define GPIO_CODEC_CRX_LOCAL_PIN_INDEX_MASK			((gpio_pin_index_t) 0x07U)
/** @brief First zero-based pin index controlled through CRH @def GPIO_CODEC_CRH_PIN_INDEX_FIRST */
#define GPIO_CODEC_CRH_PIN_INDEX_FIRST				((gpio_pin_index_t) 0x08U)
/** @brief MODE bit offset inside one right-aligned MODE/CNF field @def GPIO_CODEC_CRX_MODE_BITS_SHIFT */
#define GPIO_CODEC_CRX_MODE_BITS_SHIFT				((reg_field_t) 0x00U)
/** @brief Width of one raw MODE field @def GPIO_CODEC_CRX_MODE_BITS_FIELD_WIDTH */
#define GPIO_CODEC_CRX_MODE_BITS_FIELD_WIDTH		((uint8_t) 0x02U)
/** @brief Raw right-aligned MODE field mask @def GPIO_CODEC_CRX_MODE_BITS_MASK */
#define GPIO_CODEC_CRX_MODE_BITS_MASK				((reg_field_t) 0x03U)
/** @brief CNF bit offset inside one right-aligned MODE/CNF field @def GPIO_CODEC_CRX_CNF_BITS_SHIFT */
#define GPIO_CODEC_CRX_CNF_BITS_SHIFT				((reg_field_t) 0x02U)
/** @brief Width of one raw CNF field @def GPIO_CODEC_CRX_CNF_BITS_FIELD_WIDTH */
#define GPIO_CODEC_CRX_CNF_BITS_FIELD_WIDTH			((uint8_t) 0x02U)
/** @brief Raw right-aligned CNF field mask @def GPIO_CODEC_CRX_CNF_BITS_MASK */
#define GPIO_CODEC_CRX_CNF_BITS_MASK				((reg_field_t) 0x03U)

// ==================================================================================================== //
//										Local Register Image Helpers									//
// ==================================================================================================== //

/**
 * @brief Computes the bit position of one pin's MODE/CNF field inside a CRL/CRH image
 * @param[in] pinIndex Zero-based GPIO pin index
 * @returns CRL/CRH-local bit position for the pin's four-bit MODE/CNF field
 * @retval - `0U, 4U, 8U, ..., 28U`: Bit position inside the selected CRL/CRH image
 * @note Caller owns validation that @p pinIndex is inside the supported GPIO pin range.
 */
__STATIC_FORCEINLINE reg_field_t Codec_GPIO_GetPinConfigModeFieldBitPos(const gpio_pin_index_t pinIndex)
{
	//! Wrap pin index to 0-7 range since both CRL and CRH have identical field layouts
	const gpio_pin_index_t localPinIndex = (gpio_pin_index_t) (pinIndex & GPIO_CODEC_CRX_LOCAL_PIN_INDEX_MASK);
	//! Each pin occupies a four-bit MODE/CNF field, so shift by (localPinIndex * 4)
	return (reg_field_t)(localPinIndex * GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_WIDTH);
}

/**
 * @brief Decodes one GPIO single-pin mask into a GPIO pin index
 * @param[in] pin GPIO single-pin mask
 * Accepted values:
 * - @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[out] pPinIndex Destination for decoded zero-based GPIO pin index
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p pin was decoded into @p pPinIndex
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPinIndex is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin is not a single valid pin
 */
__STATIC_FORCEINLINE driver_status_t Codec_GPIO_GetPinIndexFromPinMask
(
	const gpio_pin_t			pin,
	gpio_pin_index_t* const		pPinIndex
)
{
	// Validate Input
	if (pPinIndex == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	*pPinIndex = GPIO_PinMaskToIndex(pin);
	if (*pPinIndex == GPIO_PIN_INDEX_INVALID)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Extracts one ON/OFF bit state from a register image
 * @param[in] regImage Caller-owned register image
 * @param[in] bitMask Single-bit mask selecting the target field
 * @param[out] pBitState Destination for the extracted bit state
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Bit state was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pBitState is `NULL`
 * @note Writes @ref `DRIVER_STATUS_OFF` when the selected bit is clear and
 * @ref `DRIVER_STATUS_ON` when it is set.
 */
__STATIC_FORCEINLINE driver_status_t Codec_GPIO_ExtractBitStateFromImage
(
	const reg					regImage,
	const reg					bitMask,
	driver_status_t* const		pBitState
)
{
	// Validate output pointer
	if (pBitState == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	//! Decode the selected bit into the driver ON/OFF state
	*pBitState = ((regImage & bitMask) != 0x00000000UL) ? DRIVER_STATUS_ON : DRIVER_STATUS_OFF;
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Stages one ON/OFF bit state inside a register image
 * @param[in] regImage Caller-owned register image before replacement
 * @param[in] bitMask Single-bit mask selecting the target field
 * @param[in] bitState Requested bit state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Clear the selected bit
 * - @ref `DRIVER_STATUS_ON`: Set the selected bit
 * @param[out] pRegImage Destination for the updated register image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Register image was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p bitState is not an accepted state
 */
__STATIC_FORCEINLINE driver_status_t Codec_GPIO_StageBitStateInImage
(
	const reg					regImage,
	const reg					bitMask,
	const driver_status_t		bitState,
	reg* const					pRegImage
)
{
	// Local Variable
	reg updatedRegImage = regImage;
	reg bitSet = 0x00000000UL;

	// Validate output pointer
	if (pRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((bitState != DRIVER_STATUS_OFF) && (bitState != DRIVER_STATUS_ON))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Stage only the selected bit while preserving the rest of the register image
	bitSet = (bitState == DRIVER_STATUS_ON) ? bitMask : 0x00000000UL;
	updatedRegImage = RegOps_StageField(updatedRegImage, bitMask, bitSet);

	//! Store the updated register image
	*pRegImage = updatedRegImage;

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Extracts one pin's right-aligned MODE/CNF field from a CRL/CRH image
 * @param[in] crxRegImage Caller-owned CRL/CRH register image
 * @param[in] pinIndex Zero-based GPIO pin index
 * @returns Right-aligned raw `CNF[1:0] | MODE[1:0]` field value
 * @retval - `0x00U..0x0FU`: Raw MODE/CNF field for @p pinIndex
 * @note This helper reads only the caller-provided image. It does not access hardware.
 * Caller owns validation that @p pinIndex is inside the supported GPIO pin range.
 */
__STATIC_FORCEINLINE reg_field_t Codec_GPIO_ExtractPinConfigModeFieldFromImage
(
	const reg					crxRegImage,
	const gpio_pin_index_t		pinIndex
)
{
	// Local Variable
	reg_field_t pinModeConfig = (reg_field_t) 0x00U;
	//! Extract only the target pin's MODE/CNF field
	pinModeConfig = (reg_field_t)(crxRegImage >> Codec_GPIO_GetPinConfigModeFieldBitPos(pinIndex));
	//! Right-Align and mask out any reserved bits
	pinModeConfig &= GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_MASK;
	return pinModeConfig;
}

/**
 * @brief Gets the raw `MODE` bits from one right-aligned MODE/CNF field
 * @param[in] configModeField Right-aligned raw `CNF[1:0] | MODE[1:0]` field value
 * @returns Raw STM32F1 `MODE[1:0]` field value
 * @retval - @ref `GPIO_CRX_MODE_INPUT`: Input mode
 * @retval - @ref `GPIO_CRX_MODE_OUTPUT_10MHZ`: Output mode, max speed 10 MHz
 * @retval - @ref `GPIO_CRX_MODE_OUTPUT_2MHZ`: Output mode, max speed 2 MHz
 * @retval - @ref `GPIO_CRX_MODE_OUTPUT_50MHZ`: Output mode, max speed 50 MHz
 */
__STATIC_FORCEINLINE reg_field_t Codec_GPIO_GetPinModeBitsFromField(const reg_field_t configModeField)
{
	return (reg_field_t) ((((reg) configModeField) >> GPIO_CODEC_CRX_MODE_BITS_SHIFT) & GPIO_CODEC_CRX_MODE_BITS_MASK);
}

/**
 * @brief Gets the raw `CNF` bits from one right-aligned MODE/CNF field
 * @param[in] configModeField Right-aligned raw `CNF[1:0] | MODE[1:0]` field value
 * @returns Raw STM32F1 `CNF[1:0]` field value
 * @retval - @ref `GPIO_CRX_CNF_INPUT_ANALOG`: Analog input when MODE is input
 * @retval - @ref `GPIO_CRX_CNF_INPUT_FLOATING`: Floating input when MODE is input
 * @retval - @ref `GPIO_CRX_CNF_INPUT_PULL`: Pull-up/pull-down input when MODE is input
 * @retval - @ref `GPIO_CRX_CNF_INPUT_RESERVED`: Reserved input encoding when MODE is input
 * @retval - @ref `GPIO_CRX_CNF_OUTPUT_PUSH_PULL`: General-purpose push-pull output when MODE is output
 * @retval - @ref `GPIO_CRX_CNF_OUTPUT_OPEN_DRAIN`: General-purpose open-drain output when MODE is output
 * @retval - @ref `GPIO_CRX_CNF_ALTERNATE_PUSH_PULL`: Alternate-function push-pull output when MODE is output
 * @retval - @ref `GPIO_CRX_CNF_ALTERNATE_OPEN_DRAIN`: Alternate-function open-drain output when MODE is output
 */
__STATIC_FORCEINLINE reg_field_t Codec_GPIO_GetPinConfigBitsFromField(const reg_field_t configModeField)
{
	return (reg_field_t) ((((reg) configModeField) >> GPIO_CODEC_CRX_CNF_BITS_SHIFT) & GPIO_CODEC_CRX_CNF_BITS_MASK);
}

/**
 * @brief Builds one right-aligned raw MODE/CNF field from raw MODE and CNF bits
 * @param[in] modeBits Raw STM32F1 `MODE[1:0]` field value
 * Accepted values:
 * - @ref `GPIO_CRX_MODE_INPUT`
 * - @ref `GPIO_CRX_MODE_OUTPUT_10MHZ`
 * - @ref `GPIO_CRX_MODE_OUTPUT_2MHZ`
 * - @ref `GPIO_CRX_MODE_OUTPUT_50MHZ`
 * @param[in] cnfBits Raw STM32F1 `CNF[1:0]` field value
 * Accepted values:
 * - @ref `GPIO_CRX_CNF_INPUT_ANALOG` / @ref `GPIO_CRX_CNF_OUTPUT_PUSH_PULL`
 * - @ref `GPIO_CRX_CNF_INPUT_FLOATING` / @ref `GPIO_CRX_CNF_OUTPUT_OPEN_DRAIN`
 * - @ref `GPIO_CRX_CNF_INPUT_PULL` / @ref `GPIO_CRX_CNF_ALTERNATE_PUSH_PULL`
 * - @ref `GPIO_CRX_CNF_INPUT_RESERVED` / @ref `GPIO_CRX_CNF_ALTERNATE_OPEN_DRAIN`
 * @returns Right-aligned raw `CNF[1:0] | MODE[1:0]` field value
 * @retval - `0x00U..0x0FU`: Packed raw MODE/CNF field
 */
__STATIC_FORCEINLINE reg_field_t Codec_GPIO_BuildPinConfigModeField(const reg_field_t modeBits, const reg_field_t cnfBits)
{
	// Local Variable
	reg_field_t configModeField = (reg_field_t) 0x00U;

	configModeField |= (reg_field_t) REG_FIELD_PACK
	(
		GPIO_CODEC_CRX_MODE_BITS_SHIFT,
		modeBits,
		GPIO_CODEC_CRX_MODE_BITS_FIELD_WIDTH
	);
	configModeField |= (reg_field_t) REG_FIELD_PACK
	(
		GPIO_CODEC_CRX_CNF_BITS_SHIFT,
		cnfBits,
		GPIO_CODEC_CRX_CNF_BITS_FIELD_WIDTH
	);

	return configModeField;
}

// ==================================================================================================== //
//										Local CRx Decode/Encode Helpers									//
// ==================================================================================================== //

/**
 * @brief Decodes one raw MODE/CNF field into driver-facing config and mode selectors
 * @param[in] configModeField Right-aligned raw `CNF[1:0] | MODE[1:0]` field value
 * Accepted values:
 * - `0x00U..0x0FU`, excluding `0x0CU`
 * - `0x0CU` is reserved because it represents input mode with `CNF[1:0] == 0b11`
 * @param[out] pConfig Optional destination for decoded GPIO configuration selector
 * Expected values:
 * - Non-`NULL`: Decoded config is written to @p pConfig
 * - `NULL`: Config decode result is ignored
 * @param[out] pMode Optional destination for decoded GPIO mode selector
 * Expected values:
 * - Non-`NULL`: Decoded mode is written to @p pMode
 * - `NULL`: Mode decode result is ignored
 * @returns Decoding status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: MODE/CNF field was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pConfig and @p pMode are both `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p configModeField is not decodable
 * @details This helper is the pure inverse of
 * @ref `Codec_GPIO_EncodePinConfigModeField`. Raw CNF bits are mode-dependent,
 * so decode is done from the full MODE/CNF field. STM32F1 stores input pull
 * direction in `GPIOx_ODR`; this pure CRx decode writes
 * @ref `GPIO_PIN_CONFIG_INPUT_PULL_DOWN` as the canonical input-pull selector.
 * The ODR-aware decode helper resolves pull-up versus pull-down exactly.
 * @note Caller should pass at least one non-`NULL` output pointer. Fields not
 * listed in the STM32F1 GPIO configuration table return
 * @ref `DRIVER_STATUS_ERROR_INVALID_ARG`.
 */
__STATIC driver_status_t Codec_GPIO_DecodePinConfigModeField
(
	const reg_field_t			configModeField,
	gpio_pin_config_t* const	pConfig,
	gpio_pin_mode_t* const		pMode
)
{
	// Local Variables
	gpio_pin_config_t config = GPIO_PIN_CONFIG_INPUT_ANALOG;
	gpio_pin_mode_t mode = GPIO_PIN_MODE_INPUT;
	const reg_field_t modeBits = Codec_GPIO_GetPinModeBitsFromField(configModeField);
	const reg_field_t cnfBits = Codec_GPIO_GetPinConfigBitsFromField(configModeField);

	// Validate Input
	if ((pConfig == NULL) && (pMode == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((((reg) configModeField) & ~GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_MASK) != 0x00000000UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Decode MODE bits
	switch(modeBits)
	{
		case GPIO_CRX_MODE_INPUT:
		{
			mode = GPIO_PIN_MODE_INPUT;
			break;
		}
		case GPIO_CRX_MODE_OUTPUT_10MHZ:
		{
			mode = GPIO_PIN_MODE_OUTPUT_10MHZ;
			break;
		}
		case GPIO_CRX_MODE_OUTPUT_2MHZ:
		{
			mode = GPIO_PIN_MODE_OUTPUT_2MHZ;
			break;
		}
		case GPIO_CRX_MODE_OUTPUT_50MHZ:
		{
			mode = GPIO_PIN_MODE_OUTPUT_50MHZ;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	//! Decode CNF bits
	if (modeBits == GPIO_CRX_MODE_INPUT)
	{
		switch(cnfBits)
		{
			case GPIO_CRX_CNF_INPUT_ANALOG:
			{
				config = GPIO_PIN_CONFIG_INPUT_ANALOG;
				break;
			}
			case GPIO_CRX_CNF_INPUT_FLOATING:
			{
				config = GPIO_PIN_CONFIG_INPUT_FLOATING;
				break;
			}
			case GPIO_CRX_CNF_INPUT_PULL:
			{
				config = GPIO_PIN_CONFIG_INPUT_PULL_DOWN;
				break;
			}
			case GPIO_CRX_CNF_INPUT_RESERVED:
			default:
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
		}
	}
	else
	{
		switch(cnfBits)
		{
			case GPIO_CRX_CNF_OUTPUT_PUSH_PULL:
			{
				config = GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL;
				break;
			}
			case GPIO_CRX_CNF_OUTPUT_OPEN_DRAIN:
			{
				config = GPIO_PIN_CONFIG_OUTPUT_OPEN_DRAIN;
				break;
			}
			case GPIO_CRX_CNF_ALTERNATE_PUSH_PULL:
			{
				config = GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL;
				break;
			}
			case GPIO_CRX_CNF_ALTERNATE_OPEN_DRAIN:
			{
				config = GPIO_PIN_CONFIG_ALTERNATE_OPEN_DRAIN;
				break;
			}
			default:
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
		}
	}

	//! Update output fields
	if (pConfig != NULL)
	{
		*pConfig = config;
	}
	if (pMode != NULL)
	{
		*pMode = mode;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Encodes driver mode/config selectors into one raw MODE/CNF field
 * @param[in] config Driver-facing GPIO configuration selector
 * Accepted values:
 * - @ref `GPIO_PIN_CONFIG_INPUT_ANALOG`
 * - @ref `GPIO_PIN_CONFIG_INPUT_FLOATING`
 * - @ref `GPIO_PIN_CONFIG_INPUT_PULL_DOWN`
 * - @ref `GPIO_PIN_CONFIG_INPUT_PULL_UP`
 * - @ref `GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL`
 * - @ref `GPIO_PIN_CONFIG_OUTPUT_OPEN_DRAIN`
 * - @ref `GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL`
 * - @ref `GPIO_PIN_CONFIG_ALTERNATE_OPEN_DRAIN`
 * @param[in] mode Driver-facing GPIO mode selector
 * Accepted values:
 * - @ref `GPIO_PIN_MODE_INPUT`
 * - @ref `GPIO_PIN_MODE_OUTPUT_10MHZ`
 * - @ref `GPIO_PIN_MODE_OUTPUT_2MHZ`
 * - @ref `GPIO_PIN_MODE_OUTPUT_50MHZ`
 * @param[out] pConfigModeField Destination for right-aligned raw
 * `CNF[1:0] | MODE[1:0]` CRL/CRH field value
 * Expected values:
 * - Non-`NULL`: Encoded field is written to @p pConfigModeField
 * @returns Encoding status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: MODE/CNF field was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pConfigModeField is `NULL`
 * @details This helper is pure translation. It does not read or update a
 * register image.
 * @note Caller owns validation of @p config, @p mode, and the mode/config pair.
 */
__STATIC driver_status_t Codec_GPIO_EncodePinConfigModeField
(
	const gpio_pin_config_t	config,
	const gpio_pin_mode_t	mode,
	reg_field_t* const		pConfigModeField
)
{
	// Local Variable
	reg_field_t configModeField = (reg_field_t) 0x00U;
	reg_field_t modeBits = (reg_field_t) 0x00U;
	reg_field_t cnfBits = (reg_field_t) 0x00U;

	// Validate Input
	if (pConfigModeField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Mode Field Encoding
	switch(mode)
	{
		case GPIO_PIN_MODE_OUTPUT_10MHZ:
		{
			modeBits = (reg_field_t) GPIO_CRX_MODE_OUTPUT_10MHZ;
			break;
		}
		case GPIO_PIN_MODE_OUTPUT_2MHZ:
		{
			modeBits = (reg_field_t) GPIO_CRX_MODE_OUTPUT_2MHZ;
			break;
		}
		case GPIO_PIN_MODE_OUTPUT_50MHZ:
		{
			modeBits = (reg_field_t) GPIO_CRX_MODE_OUTPUT_50MHZ;
			break;
		}
		case GPIO_PIN_MODE_INPUT:
		default:
		{
			modeBits = (reg_field_t) GPIO_CRX_MODE_INPUT;
			break;
		}
	}

	//! Config Field Encoding
	switch(config)
	{
		case GPIO_PIN_CONFIG_INPUT_FLOATING:
		{
			cnfBits = (reg_field_t) GPIO_CRX_CNF_INPUT_FLOATING;
			break;
		}
		case GPIO_PIN_CONFIG_INPUT_PULL_DOWN:
		case GPIO_PIN_CONFIG_INPUT_PULL_UP:
		{
			cnfBits = (reg_field_t) GPIO_CRX_CNF_INPUT_PULL;
			break;
		}
		case GPIO_PIN_CONFIG_OUTPUT_OPEN_DRAIN:
		{
			cnfBits = (reg_field_t) GPIO_CRX_CNF_OUTPUT_OPEN_DRAIN;
			break;
		}
		case GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL:
		{
			cnfBits = (reg_field_t) GPIO_CRX_CNF_ALTERNATE_PUSH_PULL;
			break;
		}
		case GPIO_PIN_CONFIG_ALTERNATE_OPEN_DRAIN:
		{
			cnfBits = (reg_field_t) GPIO_CRX_CNF_ALTERNATE_OPEN_DRAIN;
			break;
		}
		case GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL:
		{
			cnfBits = (reg_field_t) GPIO_CRX_CNF_OUTPUT_PUSH_PULL;
			break;
		}
		case GPIO_PIN_CONFIG_INPUT_ANALOG:
		default:
		{
			cnfBits = (reg_field_t) GPIO_CRX_CNF_INPUT_ANALOG;
			break;
		}
	}

	//! Create the actual field
	configModeField = Codec_GPIO_BuildPinConfigModeField(modeBits, cnfBits);

	//! Store the value
	*pConfigModeField = configModeField;

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										GPIO Pin Config/Mode Codecs										//
// ==================================================================================================== //

driver_status_t Codec_GPIO_ExtractPinConfigMode
(
	const reg					crxRegImage,
	const reg					odrRegImage,
	const gpio_pin_t			pin,
	gpio_pin_config_t* const	pConfig,
	gpio_pin_mode_t* const		pMode
)
{
	// Local Variables
	gpio_pin_config_t config = GPIO_PIN_CONFIG_INPUT_ANALOG;
	gpio_pin_mode_t mode = GPIO_PIN_MODE_INPUT;
	reg_field_t configModeField = (reg_field_t) 0x00U;
	reg_field_t modeBits = (reg_field_t) 0x00U;
	reg_field_t cnfBits = (reg_field_t) 0x00U;
	reg pinBit = 0x00000000UL;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate output pointers
	if ((pConfig == NULL) && (pMode == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_GetPinIndexFromPinMask(pin, &pinIndex));

	configModeField = Codec_GPIO_ExtractPinConfigModeFieldFromImage(crxRegImage, pinIndex);
	modeBits = Codec_GPIO_GetPinModeBitsFromField(configModeField);
	cnfBits = Codec_GPIO_GetPinConfigBitsFromField(configModeField);
	pinBit = REG_BIT_MASK(pinIndex);

	//! Decode the CRL/CRH field into driver-facing selectors
	if (Codec_GPIO_DecodePinConfigModeField(configModeField, &config, &mode) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Resolve input pull-up versus pull-down from ODR
	if ((modeBits == GPIO_CRX_MODE_INPUT) && (cnfBits == GPIO_CRX_CNF_INPUT_PULL))
	{
		config = ((odrRegImage & pinBit) != 0x00000000UL) ? GPIO_PIN_CONFIG_INPUT_PULL_UP : GPIO_PIN_CONFIG_INPUT_PULL_DOWN;
	}

	//! Update output fields
	if (pConfig != NULL)
	{
		*pConfig = config;
	}
	if (pMode != NULL)
	{
		*pMode = mode;
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_StagePinConfigMode
(
	const reg					crxRegImage,
	const reg					odrRegImage,
	const gpio_pin_t			pin,
	const gpio_pin_config_t		config,
	const gpio_pin_mode_t		mode,
	reg* const					pCrxRegImage,
	reg* const					pOdrRegImage
)
{
	// Local Variables
	reg updatedCrxRegImage = crxRegImage;
	reg updatedOdrRegImage = odrRegImage;
	reg_field_t fieldShift = (reg_field_t) 0x00U;
	reg pinBit = 0x00000000UL;
	reg_field_t configModeField = (reg_field_t) 0x00U;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate output pointers
	if ((pCrxRegImage == NULL) || (pOdrRegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_GetPinIndexFromPinMask(pin, &pinIndex));

	fieldShift = Codec_GPIO_GetPinConfigModeFieldBitPos(pinIndex);
	pinBit = REG_BIT_MASK(pinIndex);

	//! Encode the MODE/CNF field
	if (Codec_GPIO_EncodePinConfigModeField(config, mode, &configModeField) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Replace the target pin's MODE/CNF field
	updatedCrxRegImage = RegOps_StageFieldValue
	(
		updatedCrxRegImage,
		fieldShift,
		configModeField,
		GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_WIDTH
	);

	//! Stage input pull state inside ODR image only when the mode/config pair requires it
	if (GPIO_PIN_MODE_CONFIG_IS_INPUT_PULL(mode, config) != 0x00U)
	{
		updatedOdrRegImage = RegOps_StageField
		(
			updatedOdrRegImage,
			pinBit,
			(config == GPIO_PIN_CONFIG_INPUT_PULL_UP) ? pinBit : 0x00000000UL
		);
	}

	//! Store the updated register images
	*pCrxRegImage = updatedCrxRegImage;
	*pOdrRegImage = updatedOdrRegImage;

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										GPIO Pin Output State Codecs									//
// ==================================================================================================== //

driver_status_t Codec_GPIO_ExtractPinOutputState
(
	const reg					odrRegImage,
	const gpio_pin_t			pin,
	driver_status_t* const		pPinState
)
{
	// Local Variable
	reg pinBitMask = 0x00000000UL;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	if (pPinState == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_GetPinIndexFromPinMask(pin, &pinIndex));
	pinBitMask = REG_BIT_MASK(pinIndex);
	//! Extract the selected ODR bit state from the register image
	return Codec_GPIO_ExtractBitStateFromImage(odrRegImage, pinBitMask, pPinState);
}

driver_status_t Codec_GPIO_StagePinOutputState
(
	const reg					odrRegImage,
	const gpio_pin_t			pin,
	const driver_status_t		pinState,
	reg* const					pOdrRegImage
)
{
	// Local Variable
	reg pinBitMask = 0x00000000UL;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	if (pOdrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_GetPinIndexFromPinMask(pin, &pinIndex));
	pinBitMask = REG_BIT_MASK(pinIndex);
	//! Stage the selected ODR bit state inside the register image
	return Codec_GPIO_StageBitStateInImage(odrRegImage, pinBitMask, pinState, pOdrRegImage);
}

// ==================================================================================================== //
//										GPIO Pin Input State Codecs										//
// ==================================================================================================== //

driver_status_t Codec_GPIO_ExtractPinInputState
(
	const reg					idrRegImage,
	const gpio_pin_t			pin,
	driver_status_t* const		pPinState
)
{
	// Local Variable
	reg pinBitMask = 0x00000000UL;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	if (pPinState == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_GetPinIndexFromPinMask(pin, &pinIndex));
	pinBitMask = REG_BIT_MASK(pinIndex);
	//! Extract the selected IDR bit state from the register image
	return Codec_GPIO_ExtractBitStateFromImage(idrRegImage, pinBitMask, pPinState);
}

// ==================================================================================================== //
//										GPIO Lock State Codecs											//
// ==================================================================================================== //

driver_status_t Codec_GPIO_ExtractPinLockState
(
	const reg					lckrRegImage,
	const gpio_pin_t			pin,
	driver_status_t* const		pLockState
)
{
	// Local Variable
	reg pinBitMask = 0x00000000UL;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	if (pLockState == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_GetPinIndexFromPinMask(pin, &pinIndex));
	pinBitMask = REG_BIT_MASK(pinIndex);
	//! Extract the selected LCKR pin-lock bit state from the register image
	return Codec_GPIO_ExtractBitStateFromImage(lckrRegImage, pinBitMask, pLockState);
}

driver_status_t Codec_GPIO_StagePinLockState
(
	const reg					lckrRegImage,
	const gpio_pin_t			pin,
	const driver_status_t		lockState,
	reg* const					pLckrRegImage
)
{
	// Local Variable
	reg pinBitMask = 0x00000000UL;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	if (pLckrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_GetPinIndexFromPinMask(pin, &pinIndex));
	pinBitMask = REG_BIT_MASK(pinIndex);
	//! Stage the selected LCKR pin-lock bit state inside the register image
	return Codec_GPIO_StageBitStateInImage(lckrRegImage, pinBitMask, lockState, pLckrRegImage);
}

driver_status_t Codec_GPIO_ExtractLockKeyState
(
	const reg					lckrRegImage,
	driver_status_t* const		pLockKeyState
)
{
	return Codec_GPIO_ExtractBitStateFromImage(lckrRegImage, GPIO_LCKR_LCKK, pLockKeyState);
}

driver_status_t Codec_GPIO_StageLockKeyState
(
	const reg					lckrRegImage,
	const driver_status_t		lockKeyState,
	reg* const					pLckrRegImage
)
{
	return Codec_GPIO_StageBitStateInImage(lckrRegImage, GPIO_LCKR_LCKK, lockKeyState, pLckrRegImage);
}
