/**
 * @file	gpio_irq_codec.h
 * @author	Shrey Shah
 * @brief	GPIO IRQ Codec Interface
 * @version	v1.0
 * @date	31-03-2026
 *
 * @details
 * This header defines the GPIO IRQ codec APIs that bridge staged EXTI/AFIO
 * register images and driver-facing GPIO IRQ selectors.
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
 * @addtogroup GPIO_IRQ_03_Driver
 * @{
 */

/**
 * @brief GPIO IRQ Codec Translation, Staging, and Extraction APIs
 * @defgroup GPIO_IRQ_03_Driver_02_Codec GPIO IRQ Codec Translation, Staging, and Extraction APIs
 * @ingroup GPIO_IRQ_03_Driver
 * @details
 * These APIs own GPIO IRQ selector translation and staged EXTI/AFIO EXTICR
 * register-image mutation for the GPIO IRQ driver. They assume the driver
 * already validated public inputs and never touch hardware registers directly.
 * @{
 */

/**
 * @brief Returns the AFIO EXTICR routing-register index for one GPIO IRQ line
 * @param[in] pinIndex Zero-based GPIO IRQ line index
 * Accepted values:
 * - `0U..15U`
 * @param[out] pExticrIndex Destination for the AFIO EXTICR routing-register index
 * Expected values:
 * - Non-`NULL`: Resolved EXTICR index is written to @p pExticrIndex
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: EXTICR routing-register index resolved successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pExticrIndex was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinIndex was invalid.
 */
driver_status_t Codec_GPIO_IRQ_GetRoutingRegisterIndex
(
	const gpio_pin_index_t		pinIndex,
	uint8_t* const				pExticrIndex
);

/**
 * @brief Stages one GPIO port route inside an AFIO EXTICR image
 * @param[in] GPIOx GPIO peripheral instance
 * Accepted values:
 * - @ref `GPIOA`
 * - @ref `GPIOB`
 * - @ref `GPIOC`
 * - @ref `GPIOD`
 * - @ref `GPIOE`
 * - @ref `GPIOF`
 * - @ref `GPIOG`
 * @param[in] pinIndex Zero-based GPIO IRQ line index
 * Accepted values:
 * - `0U..15U`
 * @param[in,out] pExticrRegImage Staged AFIO EXTICR image to update in place
 * Expected values:
 * - Non-`NULL`: Updated image is written back to @p pExticrRegImage
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AFIO EXTICR routing image was staged successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pExticrRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pinIndex was invalid.
 */
driver_status_t Codec_GPIO_IRQ_StagePortRouting
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_index_t		pinIndex,
	reg* const					pExticrRegImage
);

/**
 * @brief Extracts whether one AFIO EXTICR route matches the requested GPIO port
 * @param[in] GPIOx GPIO peripheral instance expected to own the route
 * Accepted values:
 * - @ref `GPIOA`
 * - @ref `GPIOB`
 * - @ref `GPIOC`
 * - @ref `GPIOD`
 * - @ref `GPIOE`
 * - @ref `GPIOF`
 * - @ref `GPIOG`
 * @param[in] pinIndex Zero-based GPIO IRQ line index
 * Accepted values:
 * - `0U..15U`
 * @param[in] exticrRegImage Staged AFIO EXTICR image containing the selected line's routing field
 * @param[out] pRouteState Destination for route-match state
 * Expected values:
 * - Non-`NULL`: @ref `DRIVER_STATUS_ON` is written when route matches @p GPIOx;
 *   @ref `DRIVER_STATUS_OFF` is written otherwise
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AFIO EXTICR route state was extracted successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRouteState was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pinIndex was invalid.
 */
driver_status_t Codec_GPIO_IRQ_ExtractPortRoutingState
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_index_t		pinIndex,
	const reg					exticrRegImage,
	driver_status_t* const		pRouteState
);

/**
 * @brief Stages reset routing for one AFIO EXTICR route inside a register image
 * @param[in] pinIndex Zero-based GPIO IRQ line index
 * Accepted values:
 * - `0U..15U`
 * @param[in,out] pExticrRegImage Staged AFIO EXTICR image to update in place
 * Expected values:
 * - Non-`NULL`: Updated image is written back to @p pExticrRegImage
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AFIO EXTICR reset routing image was staged successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pExticrRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinIndex was invalid.
 */
driver_status_t Codec_GPIO_IRQ_StageResetPortRouting
(
	const gpio_pin_index_t		pinIndex,
	reg* const					pExticrRegImage
);

/**
 * @brief Stages EXTI rising and falling trigger images for one GPIO IRQ line
 * @param[in] pinIndex Zero-based GPIO IRQ line index
 * Accepted values:
 * - `0U..15U`
 * @param[in] trigger Driver EXTI trigger selector
 * Accepted values:
 * - @ref `GPIO_IRQ_TRIGGER_FALLING`
 * - @ref `GPIO_IRQ_TRIGGER_RISING`
 * - @ref `GPIO_IRQ_TRIGGER_BOTH`
 * @param[in,out] pRtsrRegImage Staged EXTI RTSR image
 * @param[in,out] pFtsrRegImage Staged EXTI FTSR image
 * Expected values:
 * - Non-`NULL`: Updated images are written back to @p pRtsrRegImage and @p pFtsrRegImage
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Trigger images were staged successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: One or more staged-image pointers were null.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinIndex or @p trigger was invalid.
 */
driver_status_t Codec_GPIO_IRQ_StageTrigger
(
	const gpio_pin_index_t		pinIndex,
	const gpio_irq_trigger_t		trigger,
	reg* const					pRtsrRegImage,
	reg* const					pFtsrRegImage
);

/**
 * @brief Stages reset trigger state for one GPIO IRQ line
 * @param[in] pinIndex Zero-based GPIO IRQ line index
 * Accepted values:
 * - `0U..15U`
 * @param[in,out] pRtsrRegImage Staged EXTI RTSR image
 * @param[in,out] pFtsrRegImage Staged EXTI FTSR image
 * Expected values:
 * - Non-`NULL`: Updated images are written back to @p pRtsrRegImage and @p pFtsrRegImage
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Reset trigger images were staged successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: One or more staged-image pointers were null.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinIndex was invalid.
 */
driver_status_t Codec_GPIO_IRQ_StageResetTrigger
(
	const gpio_pin_index_t		pinIndex,
	reg* const					pRtsrRegImage,
	reg* const					pFtsrRegImage
);

/** @} */ // GPIO_IRQ_03_Driver_02_Codec

/** @} */ // GPIO_IRQ_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_IRQ_CODEC_H_ */
