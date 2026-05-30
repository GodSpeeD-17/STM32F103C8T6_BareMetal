/**
 * @file	gpio_codec.h
 * @author	Shrey Shah
 * @brief	GPIO Selector Codec Interface
 * @version	v1.0
 * @date	24-05-2026
 *
 * @details
 * This header defines the GPIO codec layer between GPIO LL and the public
 * GPIO driver. Codec APIs encode driver-facing selectors into raw STM32F1 GPIO
 * fields, decode raw fields back into driver-facing selectors, and mutate
 * caller-owned register images. They do not read or write peripheral hardware.
 */

#ifndef GPIO_CODEC_H_
#define GPIO_CODEC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "gpio_defines.h"

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
 * the GPIO driver. They may validate translation inputs and return
 * @ref driver_status_t, but they must not touch hardware registers directly.
 * @{
 */

/** @brief Width of one CRL/CRH pin MODE/CNF field @def GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_WIDTH */
#define GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_WIDTH		((uint32_t) 0x04UL)
/** @brief Raw right-aligned four-bit CRL/CRH pin MODE/CNF field mask @def GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_MASK */
#define GPIO_CODEC_CRX_PIN_MODE_CNF_FIELD_MASK		((uint32_t) 0x0FUL)
/** @brief Local pin-index mask inside one CRL/CRH register @def GPIO_CODEC_CRX_LOCAL_PIN_INDEX_MASK */
#define GPIO_CODEC_CRX_LOCAL_PIN_INDEX_MASK			((gpio_pin_index_t) 0x07U)
/** @brief First zero-based pin index controlled through CRH @def GPIO_CODEC_CRH_PIN_INDEX_FIRST */
#define GPIO_CODEC_CRH_PIN_INDEX_FIRST				((gpio_pin_index_t) 0x08U)
/** @brief CRL selector returned by @ref GPIO_Codec_GetCRxRegisterIndexFromPinIndex @def GPIO_CODEC_CRX_REGISTER_INDEX_CRL */
#define GPIO_CODEC_CRX_REGISTER_INDEX_CRL			((uint8_t) 0x00U)
/** @brief CRH selector returned by @ref GPIO_Codec_GetCRxRegisterIndexFromPinIndex @def GPIO_CODEC_CRX_REGISTER_INDEX_CRH */
#define GPIO_CODEC_CRX_REGISTER_INDEX_CRH			((uint8_t) 0x01U)
/** @brief MODE bit offset inside one right-aligned MODE/CNF field @def GPIO_CODEC_CRX_MODE_BITS_SHIFT */
#define GPIO_CODEC_CRX_MODE_BITS_SHIFT				((uint32_t) 0x00UL)
/** @brief Raw right-aligned MODE field mask @def GPIO_CODEC_CRX_MODE_BITS_MASK */
#define GPIO_CODEC_CRX_MODE_BITS_MASK				((uint32_t) 0x03UL)
/** @brief CNF bit offset inside one right-aligned MODE/CNF field @def GPIO_CODEC_CRX_CNF_BITS_SHIFT */
#define GPIO_CODEC_CRX_CNF_BITS_SHIFT				((uint32_t) 0x02UL)
/** @brief Raw right-aligned CNF field mask @def GPIO_CODEC_CRX_CNF_BITS_MASK */
#define GPIO_CODEC_CRX_CNF_BITS_MASK				((uint32_t) 0x03UL)

/**
 * @brief Returns the CRL/CRH register selector for one pin index
 * @param[in] pinIndex Zero-based GPIO pin index in the range `0..15`
 * @returns CRx register selector for @p pinIndex
 * @retval - @ref `GPIO_CODEC_CRX_REGISTER_INDEX_CRL`: @p pinIndex maps to `CRL`
 * @retval - @ref `GPIO_CODEC_CRX_REGISTER_INDEX_CRH`: @p pinIndex maps to `CRH`
 * @note Caller owns pin-index validation before using this helper.
 */
__STATIC_FORCEINLINE uint8_t GPIO_Codec_GetCRxRegisterIndexFromPinIndex(const gpio_pin_index_t pinIndex)
{
	return (pinIndex < GPIO_CODEC_CRH_PIN_INDEX_FIRST) ?
		GPIO_CODEC_CRX_REGISTER_INDEX_CRL :
		GPIO_CODEC_CRX_REGISTER_INDEX_CRH;
}

/**
 * @brief Extracts one right-aligned raw MODE/CNF field from a CRL/CRH register image
 * @param[in]	crxRegImage		Caller-owned CRL/CRH register image
 * @param[in]	pinIndex		Zero-based GPIO pin index
 * @param[out]	pCrxField		Destination for right-aligned raw `CNF[1:0] | MODE[1:0]`
 * @returns Extraction status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Raw field was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinIndex is invalid
 */
driver_status_t GPIO_Codec_GetPinModeConfigField
(
	const uint32_t				crxRegImage,
	const gpio_pin_index_t		pinIndex,
	gpio_pin_config_bits_t* const pCrxField
);

/**
 * @brief Stages one pin's complete CRL/CRH mode/config field in a register image
 * @param[in]		pinIndex		Zero-based GPIO pin index
 * @param[in]		mode			Driver-facing GPIO mode selector
 * @param[in]		config			Driver-facing GPIO configuration selector
 * @param[in,out]	pCrxRegImage	Caller-owned CRL or CRH image
 * @returns Staging status for the requested pin mode/config field
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin mode/config field was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinIndex, @p mode, or @p config is invalid
 */
driver_status_t GPIO_Codec_StagePinModeConfigImage
(
	const gpio_pin_index_t	pinIndex,
	const gpio_pin_mode_t	mode,
	const gpio_pin_config_t	config,
	uint32_t* const			pCrxRegImage
);

/**
 * @brief Stages one pin's CRL/CRH MODE field in a register image
 * @param[in]		pinIndex		Zero-based GPIO pin index
 * @param[in]		mode			Driver-facing GPIO mode selector
 * @param[in,out]	pCrxRegImage	Caller-owned CRL or CRH image
 * @returns Staging status for the requested pin MODE field
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin MODE field was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinIndex or @p mode is invalid
 */
driver_status_t GPIO_Codec_StagePinModeImage
(
	const gpio_pin_index_t	pinIndex,
	const gpio_pin_mode_t	mode,
	uint32_t* const			pCrxRegImage
);

/**
 * @brief Stages one pin's CRL/CRH CNF field in a register image
 * @param[in]		pinIndex		Zero-based GPIO pin index
 * @param[in]		config			Driver-facing GPIO configuration selector
 * @param[in,out]	pCrxRegImage	Caller-owned CRL or CRH image
 * @returns Staging status for the requested pin CNF field
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin CNF field was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinIndex or @p config is invalid
 */
driver_status_t GPIO_Codec_StagePinConfigImage
(
	const gpio_pin_index_t	pinIndex,
	const gpio_pin_config_t	config,
	uint32_t* const			pCrxRegImage
);

/**
 * @brief Stages one pin's reset CRL/CRH field in a register image
 * @param[in]		pinIndex		Zero-based GPIO pin index
 * @param[in,out]	pCrxRegImage	Caller-owned CRL or CRH image
 * @returns Staging status for the requested pin reset field
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin reset field was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCrxRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinIndex is invalid
 */
driver_status_t GPIO_Codec_StagePinResetConfigImage
(
	const gpio_pin_index_t	pinIndex,
	uint32_t* const			pCrxRegImage
);

/**
 * @brief Stages one pin's input pull state in an ODR register image
 * @param[in]		pinIndex		Zero-based GPIO pin index
 * @param[in]		config			Driver-facing GPIO pull configuration selector
 * @param[in,out]	pOdrRegImage	Caller-owned ODR image
 * @returns Staging status for the requested pull state
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pull state was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pOdrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinIndex or @p config is invalid
 */
driver_status_t GPIO_Codec_StagePinPullImage
(
	const gpio_pin_index_t	pinIndex,
	const gpio_pin_config_t	config,
	uint32_t* const			pOdrRegImage
);

/**
 * @brief Decodes one raw MODE/CNF field and ODR image into driver-facing selectors
 * @param[in]	crxField	Right-aligned raw `CNF[1:0] | MODE[1:0]` field
 * @param[in]	odrRegImage	ODR image used to resolve input pull-up/pull-down state
 * @param[in]	pinIndex	Zero-based GPIO pin index
 * @param[out]	pMode		Destination for decoded GPIO mode selector
 * @param[out]	pConfig	Destination for decoded GPIO configuration selector
 * @returns Decode status for the requested pin state
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pin state was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: Both @p pMode and @p pConfig are `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinIndex or @p crxField is invalid
 */
driver_status_t GPIO_Codec_DecodePinModeConfigField
(
	const gpio_pin_config_bits_t	crxField,
	const uint32_t				odrRegImage,
	const gpio_pin_index_t		pinIndex,
	gpio_pin_mode_t* const		pMode,
	gpio_pin_config_t* const		pConfig
);

/** @} */ // GPIO_03_Driver_02_Codec
/** @} */ // GPIO_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_CODEC_H_ */
