/**
 * @file	gpio_codec.h
 * @author	Shrey Shah
 * @brief	GPIO Selector Codec Interface
 * @version	v1.1
 * @date	30-05-2026
 *
 * @details
 * This header defines the GPIO codec layer between GPIO LL and the public
 * GPIO driver. Codec APIs encode driver-facing selectors into raw STM32F1 GPIO
 * fields, decode raw fields back into driver-facing selectors, and return
 * updated caller-owned register images. They do not read or write peripheral
 * hardware.
 */

#ifndef GPIO_CODEC_H_
#define GPIO_CODEC_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "gpio_defines.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GPIO_03_Driver
 * @{
 */

/**
 * @brief	GPIO Codec Translation and Staging APIs
 * @defgroup GPIO_03_Driver_02_Codec GPIO Codec Translation and Staging APIs
 * @ingroup	GPIO_03_Driver
 * @details
 * These APIs own selector translation and staged register-image mutation for
 * the GPIO driver. They assume the driver already validated public inputs and
 * never touch hardware registers directly.
 * @{
 */

/**
 * @brief Checks whether a GPIO pin index maps to the CRH register image
 * @param[in] pinIndex Zero-based GPIO pin index
 * @returns CRH target state for @p pinIndex
 * @retval - @ref `DRIVER_STATUS_OFF`: @p pinIndex maps to `CRL`
 * @retval - @ref `DRIVER_STATUS_ON`: @p pinIndex maps to `CRH`
 * @note Caller owns pin-index validation before using this helper.
 */
__STATIC_FORCEINLINE driver_status_t Codec_GPIO_PinIndexTargetsCRH(const gpio_pin_index_t pinIndex)
{
	return (pinIndex >= ((gpio_pin_index_t) (GPIO_PORT_PIN_COUNT / 2U))) ? DRIVER_STATUS_ON : DRIVER_STATUS_OFF;
}

/**
 * @brief Extracts one right-aligned raw MODE/CNF field from a CRL/CRH image
 * @param[in] crxRegImage Caller-owned CRL/CRH register image
 * @param[in] pinIndex Zero-based GPIO pin index
 * @returns Right-aligned raw `CNF[1:0] | MODE[1:0]` field
 * @note Caller owns pin-index validation before using this helper.
 */
reg_field_t Codec_GPIO_ExtractPinModeConfigField
(
	const reg					crxRegImage,
	const gpio_pin_index_t		pinIndex
);

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
);

/**
 * @brief Stages one pin's complete CRL/CRH mode/config field in an image
 * @param[in] crxRegImage Caller-owned CRL/CRH image before staging
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[in] mode Driver-facing GPIO mode selector
 * @param[in] config Driver-facing GPIO configuration selector
 * @returns Updated CRL/CRH register image
 * @note Caller owns validation of @p pinIndex, @p mode, @p config, and the
 * mode/config compatibility pair.
 */
reg Codec_GPIO_StagePinModeConfigImage
(
	const reg					crxRegImage,
	const gpio_pin_index_t		pinIndex,
	const gpio_pin_mode_t		mode,
	const gpio_pin_config_t		config
);

/**
 * @brief Stages one pin's CRL/CRH MODE field in an image
 * @param[in] crxRegImage Caller-owned CRL/CRH image before staging
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[in] mode Driver-facing GPIO mode selector
 * @returns Updated CRL/CRH register image
 * @note Caller owns validation of @p pinIndex and @p mode, and must validate
 * the final MODE/CNF pair before writing the image.
 */
reg Codec_GPIO_StagePinModeImage
(
	const reg					crxRegImage,
	const gpio_pin_index_t		pinIndex,
	const gpio_pin_mode_t		mode
);

/**
 * @brief Stages one pin's CRL/CRH CNF field in an image
 * @param[in] crxRegImage Caller-owned CRL/CRH image before staging
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[in] config Driver-facing GPIO configuration selector
 * @returns Updated CRL/CRH register image
 * @note Caller owns validation of @p pinIndex and @p config, and must validate
 * the final MODE/CNF pair before writing the image.
 */
reg Codec_GPIO_StagePinConfigImage
(
	const reg					crxRegImage,
	const gpio_pin_index_t		pinIndex,
	const gpio_pin_config_t		config
);

/**
 * @brief Stages one pin's reset CRL/CRH field in an image
 * @param[in] crxRegImage Caller-owned CRL/CRH image before staging
 * @param[in] pinIndex Zero-based GPIO pin index
 * @returns Updated CRL/CRH register image with the pin set to floating input
 * @note Caller owns pin-index validation before using this helper.
 */
reg Codec_GPIO_StagePinResetConfigImage
(
	const reg					crxRegImage,
	const gpio_pin_index_t		pinIndex
);

/**
 * @brief Stages one pin's input pull state in an ODR image
 * @param[in] odrRegImage Caller-owned ODR image before staging
 * @param[in] pinIndex Zero-based GPIO pin index
 * @param[in] config Driver-facing GPIO pull configuration selector
 * @returns Updated ODR register image
 * @note Caller owns validation that @p config is input pull-up or pull-down.
 */
reg Codec_GPIO_StagePinPullImage
(
	const reg					odrRegImage,
	const gpio_pin_index_t		pinIndex,
	const gpio_pin_config_t		config
);

/**
 * @brief Checks whether one raw MODE/CNF field can be decoded
 * @param[in] crxField Right-aligned raw `CNF[1:0] | MODE[1:0]` field
 * @returns Decode support status for @p crxField
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p crxField can be decoded to driver selectors
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p crxField contains an unsupported or reserved encoding
 */
driver_status_t Codec_GPIO_PinModeConfigFieldIsDecodable(const reg_field_t crxField);

/**
 * @brief Decodes one raw MODE/CNF field into a driver-facing mode selector
 * @param[in] crxField Right-aligned raw `CNF[1:0] | MODE[1:0]` field
 * @returns Decoded GPIO mode selector
 * @note Caller should call @ref `Codec_GPIO_PinModeConfigFieldIsDecodable` before
 * decoding externally observed register fields.
 */
gpio_pin_mode_t Codec_GPIO_DecodePinMode(const reg_field_t crxField);

/**
 * @brief Decodes one raw MODE/CNF field into a driver-facing config selector
 * @param[in] crxField Right-aligned raw `CNF[1:0] | MODE[1:0]` field
 * @param[in] odrRegImage ODR image used to resolve input pull-up/pull-down
 * @param[in] pinIndex Zero-based GPIO pin index
 * @returns Decoded GPIO configuration selector
 * @note Caller should call @ref `Codec_GPIO_PinModeConfigFieldIsDecodable` before
 * decoding externally observed register fields.
 */
gpio_pin_config_t Codec_GPIO_DecodePinConfig
(
	const reg_field_t				crxField,
	const reg						odrRegImage,
	const gpio_pin_index_t			pinIndex
);

/** @} */ // GPIO_03_Driver_02_Codec

/** @} */ // GPIO_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_CODEC_H_ */
