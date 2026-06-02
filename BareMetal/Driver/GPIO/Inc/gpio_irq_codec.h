/**
 * @file	gpio_irq_codec.h
 * @author	Shrey Shah
 * @brief	GPIO IRQ Codec Interface
 * @version	v1.0
 * @date	31-03-2026
 *
 * @details
 * This header defines the codec utilities that bridge the GPIO IRQ
 * driver layer and staged EXTI/AFIO register images.
 */

#ifndef GPIO_IRQ_CODEC_H_
#define GPIO_IRQ_CODEC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "gpio_defines.h"
#include "nvic_types.h"

/**
 * @addtogroup GPIO_IRQ_03_Driver
 * @{
 */

/**
 * @brief GPIO IRQ Codec APIs
 * @defgroup GPIO_IRQ_03_Driver_02_Codec GPIO IRQ Codec APIs
 * @ingroup GPIO_IRQ_03_Driver
 * @details
 * These codecs bridge GPIO IRQ selectors to caller-owned EXTI and AFIO
 * register images. They do not directly access hardware registers and are
 * intended for use by `gpio_irq.c`.
 * @{
 */

/**
 * @brief Updates one AFIO EXTICR line slot inside a staged register image
 * @param[in] GPIOx GPIO peripheral instance
 * Accepted values:
 * - @ref `GPIOA`
 * - @ref `GPIOB`
 * - @ref `GPIOC`
 * - @ref `GPIOD`
 * - @ref `GPIOE`
 * - @ref `GPIOF`
 * - @ref `GPIOG`
 * @param[in] pin GPIO single-pin mask identifying the GPIO IRQ line
 * Accepted values:
 * - One value from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[in,out] pExticrRegImage Staged AFIO EXTICR image to update in place
 * Expected values:
 * - Non-`NULL`: Updated image is written back to @p pExticrRegImage
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Port source image updated successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pExticrRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pin was invalid.
 */
driver_status_t Codec_GPIO_IRQ_UpdatePortConfigImage
(
	GPIO_TypeDef* const GPIOx,
	const gpio_pin_t pin,
	reg* const pExticrRegImage
);

/**
 * @brief Restores one AFIO EXTICR line slot to reset state inside a staged register image
 * @param[in] pin GPIO single-pin mask identifying the GPIO IRQ line
 * Accepted values:
 * - One value from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[in,out] pExticrRegImage Staged AFIO EXTICR image to update in place
 * Expected values:
 * - Non-`NULL`: Updated image is written back to @p pExticrRegImage
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Port source reset image updated successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pExticrRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was invalid.
 */
driver_status_t Codec_GPIO_IRQ_ResetPortConfigImage
(
	const gpio_pin_t pin,
	reg* const pExticrRegImage
);

/**
 * @brief Updates the staged EXTI rising and falling trigger images for one line
 * @param[in] pin GPIO single-pin mask identifying the GPIO IRQ line
 * Accepted values:
 * - One value from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
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
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Trigger images updated successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: One or more staged-image pointers were null.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin or @p trigger was invalid.
 */
driver_status_t Codec_GPIO_IRQ_UpdateTriggerImages
(
	const gpio_pin_t pin,
	const gpio_irq_trigger_t trigger,
	reg* const pRtsrRegImage,
	reg* const pFtsrRegImage
);

/**
 * @brief Clears the staged EXTI rising and falling trigger images for one line
 * @param[in] pin GPIO single-pin mask identifying the GPIO IRQ line
 * Accepted values:
 * - One value from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[in,out] pRtsrRegImage Staged EXTI RTSR image
 * @param[in,out] pFtsrRegImage Staged EXTI FTSR image
 * Expected values:
 * - Non-`NULL`: Updated images are written back to @p pRtsrRegImage and @p pFtsrRegImage
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Trigger images reset successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: One or more staged-image pointers were null.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was invalid.
 */
driver_status_t Codec_GPIO_IRQ_ResetTriggerImages
(
	const gpio_pin_t pin,
	reg* const pRtsrRegImage,
	reg* const pFtsrRegImage
);

/**
 * @brief Returns the NVIC IRQ number associated with one GPIO IRQ line
 * @param[in] pin GPIO single-pin mask identifying the GPIO IRQ line
 * Accepted values:
 * - One value from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[out] pIRQn Destination for the NVIC IRQ number
 * Expected values:
 * - Non-`NULL`: Resolved IRQ number is written to @p pIRQn
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: IRQ number resolved successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pIRQn was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was invalid.
 */
driver_status_t Codec_GPIO_IRQ_GetIRQn
(
	const gpio_pin_t pin,
	irq_t* const pIRQn
);

/** @} */ // GPIO_IRQ_03_Driver_02_Codec

/** @} */ // GPIO_IRQ_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_IRQ_CODEC_H_ */
