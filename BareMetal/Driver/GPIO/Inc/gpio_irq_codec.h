/**
 * @file	gpio_irq_codec.h
 * @author	Shrey Shah
 * @brief	GPIO IRQ Codec Interface
 * @version	v1.1
 * @date	06-06-2026
 *
 * @details
 * This header defines the GPIO IRQ codec layer between GPIO IRQ LL and the
 * public GPIO IRQ driver. Codec APIs accept driver-facing GPIO pin masks and
 * caller-owned EXTI/AFIO register images, then encode, decode, stage, or
 * extract raw register fields. They do not read/write hardware and they do not
 * decide GPIO port ownership policy.
 */

#ifndef GPIO_IRQ_CODEC_H_
#define GPIO_IRQ_CODEC_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "gpio_defines.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GPIO_IRQ_03_Codec
 * @{
 */

/**
 * @brief	GPIO IRQ Codec Translation, Staging, and Extraction APIs
 * @defgroup GPIO_IRQ_03_Codec_01_API GPIO IRQ Codec Translation, Staging, and Extraction APIs
 * @ingroup	GPIO_IRQ_03_Codec
 * @details
 * These APIs own GPIO IRQ selector translation and staged EXTI/AFIO EXTICR
 * register-image mutation for the GPIO IRQ driver. They assume the driver
 * already validated public GPIO inputs and selected the correct register image
 * to pass. Codec owns conversion from `GPIOx` and `gpio_pin_t` into raw AFIO
 * EXTICR route fields.
 * @{
 */

// ==================================================================================================== //
//										GPIO IRQ Port Routing Codecs									//
// ==================================================================================================== //

/**
 * @brief Extracts one GPIO port route from an AFIO EXTICR image
 * @param[in] exticrRegImage Caller-owned AFIO EXTICR image containing the selected line route
 * @param[in] pin GPIO single-pin mask
 * Accepted values:
 * - @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[out] pGPIOx Destination for the routed GPIO peripheral instance
 * Expected values:
 * - Non-`NULL`: Extracted route is written to @p pGPIOx
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AFIO EXTICR route was extracted successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pGPIOx was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was invalid or the raw route was unsupported.
 * @details This is the extraction counterpart of
 * @ref `Codec_GPIO_IRQ_StagePortRouting`. It decodes the selected EXTICR field
 * back into the driver-facing `GPIOx` pointer.
 */
driver_status_t Codec_GPIO_IRQ_ExtractPortRouting
(
	const reg					exticrRegImage,
	const gpio_pin_t			pin,
	GPIO_TypeDef** const		pGPIOx
);

/**
 * @brief Stages reset routing for one AFIO EXTICR route inside a register image
 * @param[in] exticrRegImage Caller-owned AFIO EXTICR image before replacement
 * @param[in] pin GPIO single-pin mask
 * Accepted values:
 * - @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[out] pExticrRegImage Destination for the updated AFIO EXTICR image
 * Expected values:
 * - Non-`NULL`: Updated image is written to @p pExticrRegImage
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AFIO EXTICR reset routing image was staged successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pExticrRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was not a single valid pin.
 */
driver_status_t Codec_GPIO_IRQ_StageResetPortRouting
(
	const reg					exticrRegImage,
	const gpio_pin_t			pin,
	reg* const					pExticrRegImage
);

/**
 * @brief Stages one GPIO port route inside an AFIO EXTICR image
 * @param[in] exticrRegImage Caller-owned AFIO EXTICR image before replacement
 * @param[in] pin GPIO single-pin mask
 * Accepted values:
 * - @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[in] GPIOx GPIO peripheral instance to route to the selected EXTI line
 * Accepted values:
 * - @ref `GPIOA` through @ref `GPIOG`
 * @param[out] pExticrRegImage Destination for the updated AFIO EXTICR image
 * Expected values:
 * - Non-`NULL`: Updated image is written to @p pExticrRegImage
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AFIO EXTICR routing image was staged successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pExticrRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pin was invalid.
 */
driver_status_t Codec_GPIO_IRQ_StagePortRouting
(
	const reg					exticrRegImage,
	const gpio_pin_t			pin,
	GPIO_TypeDef* const			GPIOx,
	reg* const					pExticrRegImage
);

// ==================================================================================================== //
//										GPIO IRQ Trigger Codecs											//
// ==================================================================================================== //

/**
 * @brief Extracts one GPIO IRQ trigger selector from EXTI trigger images
 * @param[in] rtsrRegImage Caller-owned EXTI RTSR image
 * @param[in] ftsrRegImage Caller-owned EXTI FTSR image
 * @param[in] pin GPIO single-pin mask
 * Accepted values:
 * - @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[out] pTrigger Destination for the extracted trigger selector
 * Expected values:
 * - Non-`NULL`: Extracted selector is written to @p pTrigger
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Trigger selector was extracted successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pTrigger was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was not a single valid pin.
 * @note When neither RTSR nor FTSR selects @p pin, `0x00U` is written to @p pTrigger.
 */
driver_status_t Codec_GPIO_IRQ_ExtractTrigger
(
	const reg					rtsrRegImage,
	const reg					ftsrRegImage,
	const gpio_pin_t			pin,
	gpio_irq_trigger_t* const	pTrigger
);

/**
 * @brief Stages reset trigger state for one GPIO IRQ line
 * @param[in] rtsrRegImage Caller-owned EXTI RTSR image before replacement
 * @param[in] ftsrRegImage Caller-owned EXTI FTSR image before replacement
 * @param[in] pin GPIO single-pin mask
 * Accepted values:
 * - @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[out] pRtsrRegImage Destination for the updated EXTI RTSR image
 * @param[out] pFtsrRegImage Destination for the updated EXTI FTSR image
 * Expected values:
 * - Non-`NULL`: Updated images are written to @p pRtsrRegImage and @p pFtsrRegImage
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Reset trigger images were staged successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: One or more staged-image pointers were null.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was not a single valid pin.
 */
driver_status_t Codec_GPIO_IRQ_StageResetTrigger
(
	const reg					rtsrRegImage,
	const reg					ftsrRegImage,
	const gpio_pin_t			pin,
	reg* const					pRtsrRegImage,
	reg* const					pFtsrRegImage
);

/**
 * @brief Stages EXTI rising and falling trigger images for one GPIO IRQ line
 * @param[in] rtsrRegImage Caller-owned EXTI RTSR image before replacement
 * @param[in] ftsrRegImage Caller-owned EXTI FTSR image before replacement
 * @param[in] pin GPIO single-pin mask
 * Accepted values:
 * - @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[in] trigger Driver EXTI trigger selector
 * Accepted values:
 * - @ref `GPIO_IRQ_TRIGGER_FALLING`
 * - @ref `GPIO_IRQ_TRIGGER_RISING`
 * - @ref `GPIO_IRQ_TRIGGER_BOTH`
 * @param[out] pRtsrRegImage Destination for the updated EXTI RTSR image
 * @param[out] pFtsrRegImage Destination for the updated EXTI FTSR image
 * Expected values:
 * - Non-`NULL`: Updated images are written to @p pRtsrRegImage and @p pFtsrRegImage
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Trigger images were staged successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: One or more staged-image pointers were null.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin or @p trigger was invalid.
 */
driver_status_t Codec_GPIO_IRQ_StageTrigger
(
	const reg					rtsrRegImage,
	const reg					ftsrRegImage,
	const gpio_pin_t			pin,
	const gpio_irq_trigger_t	trigger,
	reg* const					pRtsrRegImage,
	reg* const					pFtsrRegImage
);

/** @} */ // GPIO_IRQ_03_Codec_01_API

/** @} */ // GPIO_IRQ_03_Codec

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_IRQ_CODEC_H_ */
