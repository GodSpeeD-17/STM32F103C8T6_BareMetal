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
//                                               Includes                                               //
// ==================================================================================================== //
#include "gpio_codec.h"

// ==================================================================================================== //
//                                           Local Defines                                              //
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
/** @brief Raw right-aligned MODE field mask @def GPIO_CODEC_CRX_MODE_BITS_MASK */
#define GPIO_CODEC_CRX_MODE_BITS_MASK				((reg_field_t) 0x03U)
/** @brief CNF bit offset inside one right-aligned MODE/CNF field @def GPIO_CODEC_CRX_CNF_BITS_SHIFT */
#define GPIO_CODEC_CRX_CNF_BITS_SHIFT				((reg_field_t) 0x02U)
/** @brief Raw right-aligned CNF field mask @def GPIO_CODEC_CRX_CNF_BITS_MASK */
#define GPIO_CODEC_CRX_CNF_BITS_MASK				((reg_field_t) 0x03U)

// ==================================================================================================== //
//											Local CRx Helpers											//
// ==================================================================================================== //

/**
 * @brief Computes the bit position of one pin's MODE/CNF field inside a CRL/CRH image
 * @param[in] pinIndex Zero-based GPIO pin index
 * @returns CRL/CRH-local bit position for the pin's four-bit MODE/CNF field
 * @retval - `0U, 4U, ..., 28U`: Bit position inside the selected CRL/CRH image
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
 * @brief Shifts a right-aligned MODE/CNF field value into one pin's CRL/CRH slot
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[in] value Right-aligned raw MODE/CNF field value or field mask
 * Expected values:
 * - `0x00U..0x0FU`: Raw `CNF[1:0] | MODE[1:0]` field value
 * - @ref `GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_MASK`: Four-bit MODE/CNF field mask
 * @returns CRL/CRH-positioned MODE/CNF field value for @p pinIndex
 * @retval - Shifted @p value aligned to the selected pin's MODE/CNF field slot
 * @note Caller owns validation that @p pinIndex is inside the supported GPIO pin range.
 */
__STATIC_FORCEINLINE reg Codec_GPIO_BuildPinConfigModeFieldBitMask
(
	const gpio_pin_index_t		pinIndex,
	const reg_field_t			value
)
{
	// Local Variable
	reg bitMask = 0x00000000UL;
	//! Retrieve target pin bit position
	const reg_field_t fieldShift = Codec_GPIO_GetPinConfigModeFieldBitPos(pinIndex);
	bitMask = (((reg) value) & GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_MASK);
	bitMask = (reg) BIT_VALUE(bitMask, fieldShift);
	//! Return the field value shifted to the target pin position
	return bitMask;
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
__STATIC_FORCEINLINE reg_field_t Codec_GPIO_ExtractPinModeConfigFieldFromImage
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
__STATIC_FORCEINLINE reg_field_t Codec_GPIO_GetConfigBitsFromField(const reg_field_t configModeField)
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

	configModeField |= (reg_field_t) BIT_VALUE((((reg) modeBits) & GPIO_CODEC_CRX_MODE_BITS_MASK), GPIO_CODEC_CRX_MODE_BITS_SHIFT);
	configModeField |= (reg_field_t) BIT_VALUE((((reg) cnfBits) & GPIO_CODEC_CRX_CNF_BITS_MASK), GPIO_CODEC_CRX_CNF_BITS_SHIFT);

	return configModeField;
}

// ==================================================================================================== //
//										Local CRx Encode/Decode Helpers									//
// ==================================================================================================== //

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
	const reg_field_t cnfBits = Codec_GPIO_GetConfigBitsFromField(configModeField);

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

// ==================================================================================================== //
//									  Local CRx Register Image Helpers									//
// ==================================================================================================== //

/**
 * @brief Sets one complete MODE/CNF field inside a CRL/CRH image
 * @param[in] crxRegImage Caller-owned CRL/CRH image before replacement
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[in] config Driver-facing GPIO configuration selector
 * @param[in] mode Driver-facing GPIO mode selector
 * @returns Updated CRL/CRH image with only the selected pin field replaced
 * @note Caller owns validation of @p pinIndex, @p config, @p mode, and the
 * mode/config compatibility pair.
 */
reg Codec_GPIO_StagePinConfigMode
(
	const reg				crxRegImage,
	const gpio_pin_index_t	pinIndex,
	const gpio_pin_config_t	config,
	const gpio_pin_mode_t	mode
)
{
	// Local Variables
	reg updatedRegImage = crxRegImage;
	const reg fieldBitMask = Codec_GPIO_BuildPinConfigModeFieldBitMask(pinIndex, GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_MASK);
	reg_field_t configModeField = (reg_field_t) 0x00U;

	//! Encode the MODE/CNF field
	if (Codec_GPIO_EncodePinConfigModeField(config, mode, &configModeField) != DRIVER_STATUS_SUCCESS)
	{
		return crxRegImage;
	}

	//! Clear the target pin's MODE/CNF field
	updatedRegImage &= ~fieldBitMask;
	//! Set the target pin's MODE/CNF field to the new value
	updatedRegImage |= Codec_GPIO_BuildPinConfigModeFieldBitMask(pinIndex, configModeField);

	//! Return updated register image
	return updatedRegImage;
}

// ==================================================================================================== //
//                                             Codec APIs                                               //
// ==================================================================================================== //

reg_field_t Codec_GPIO_ExtractPinModeConfigField
(
	const reg					crxRegImage,
	const gpio_pin_index_t		pinIndex
)
{
	return (reg_field_t) Codec_GPIO_ExtractPinModeConfigFieldFromImage(crxRegImage, pinIndex);
}

reg Codec_GPIO_StagePinModeConfigImage
(
	const reg					crxRegImage,
	const gpio_pin_index_t		pinIndex,
	const gpio_pin_mode_t		mode,
	const gpio_pin_config_t		config
)
{
	return Codec_GPIO_StagePinConfigMode(crxRegImage, pinIndex, config, mode);
}

reg Codec_GPIO_StagePinModeImage
(
	const reg					crxRegImage,
	const gpio_pin_index_t		pinIndex,
	const gpio_pin_mode_t		mode
)
{
	reg_field_t configModeField = Codec_GPIO_ExtractPinModeConfigFieldFromImage(crxRegImage, pinIndex);
	gpio_pin_config_t config = GPIO_PIN_CONFIG_INPUT_ANALOG;

	if (Codec_GPIO_DecodePinConfigModeField(configModeField, &config, NULL) != DRIVER_STATUS_SUCCESS)
	{
		return crxRegImage;
	}

	return Codec_GPIO_StagePinConfigMode(crxRegImage, pinIndex, config, mode);
}

reg Codec_GPIO_StagePinConfigImage
(
	const reg					crxRegImage,
	const gpio_pin_index_t		pinIndex,
	const gpio_pin_config_t		config
)
{
	reg_field_t configModeField = Codec_GPIO_ExtractPinModeConfigFieldFromImage(crxRegImage, pinIndex);
	gpio_pin_mode_t mode = GPIO_PIN_MODE_INPUT;

	if (Codec_GPIO_DecodePinConfigModeField(configModeField, NULL, &mode) != DRIVER_STATUS_SUCCESS)
	{
		return crxRegImage;
	}

	return Codec_GPIO_StagePinConfigMode(crxRegImage, pinIndex, config, mode);
}

reg Codec_GPIO_StagePinResetConfigImage
(
	const reg					crxRegImage,
	const gpio_pin_index_t		pinIndex
)
{
	return Codec_GPIO_StagePinModeConfigImage
	(
		crxRegImage,
		pinIndex,
		GPIO_PIN_MODE_INPUT,
		GPIO_PIN_CONFIG_INPUT_FLOATING
	);
}

reg Codec_GPIO_StagePinPullImage
(
	const reg					odrRegImage,
	const gpio_pin_index_t		pinIndex,
	const gpio_pin_config_t		config
)
{
	reg updatedRegImage = odrRegImage;
	const reg pinBit = BIT_VALUE(0x1UL, pinIndex);

	if ((gpio_pin_config_t) config == GPIO_PIN_CONFIG_INPUT_PULL_DOWN)
	{
		updatedRegImage &= ~pinBit;
	}
	else
	{
		updatedRegImage |= pinBit;
	}

	return updatedRegImage;
}

driver_status_t Codec_GPIO_PinModeConfigFieldIsDecodable(const reg_field_t crxField)
{
	gpio_pin_mode_t mode = GPIO_PIN_MODE_INPUT;
	return Codec_GPIO_DecodePinConfigModeField(crxField, NULL, &mode);
}

gpio_pin_mode_t Codec_GPIO_DecodePinMode(const reg_field_t crxField)
{
	gpio_pin_mode_t mode = GPIO_PIN_MODE_INPUT;
	(void) Codec_GPIO_DecodePinConfigModeField(crxField, NULL, &mode);
	return mode;
}

gpio_pin_config_t Codec_GPIO_DecodePinConfig
(
	const reg_field_t				crxField,
	const reg						odrRegImage,
	const gpio_pin_index_t			pinIndex
)
{
	gpio_pin_config_t config = GPIO_PIN_CONFIG_INPUT_ANALOG;
	const reg_field_t modeBits = Codec_GPIO_GetPinModeBitsFromField(crxField);
	const reg_field_t cnfBits = Codec_GPIO_GetConfigBitsFromField(crxField);
	const reg pinBit = BIT_VALUE(0x1UL, pinIndex);

	(void) Codec_GPIO_DecodePinConfigModeField(crxField, &config, NULL);

	if ((modeBits == GPIO_CRX_MODE_INPUT) && (cnfBits == GPIO_CRX_CNF_INPUT_PULL))
	{
		config = ((odrRegImage & pinBit) != 0x00000000UL) ?
			GPIO_PIN_CONFIG_INPUT_PULL_UP :
			GPIO_PIN_CONFIG_INPUT_PULL_DOWN;
	}

	return config;
}
