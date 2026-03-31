/**
 * @file	gpio_exti_helper.h
 * @author	Shrey Shah
 * @brief	GPIO EXTI Internal Helper Interface
 * @version	v1.0
 * @date	31-03-2026
 *
 * @details
 * This header defines the internal helper utilities that bridge the GPIO EXTI
 * driver layer and the EXTI low-level layer.
 */

#ifndef GPIO_EXTI_HELPER_H_
#define GPIO_EXTI_HELPER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "gpio_exti.h"
#include "gpio_exti_ll.h"

/**
 * @brief Updates one AFIO EXTICR line slot inside a staged register image
 * @param[in] GPIOx GPIO peripheral instance
 * @param[in] pin GPIO single-pin mask identifying the EXTI line
 * @param[in,out] pExticrRegImage Staged AFIO EXTICR image to update in place
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Port source image updated successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pExticrRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pin was invalid.
 */
driver_status_t _GPIO_EXTI_Helper_UpdatePortConfigImage
(
	GPIO_TypeDef* const GPIOx,
	const gpio_pin_t pin,
	uint32_t* const pExticrRegImage
);

/**
 * @brief Restores one AFIO EXTICR line slot to reset state inside a staged register image
 * @param[in] pin GPIO single-pin mask identifying the EXTI line
 * @param[in,out] pExticrRegImage Staged AFIO EXTICR image to update in place
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Port source reset image updated successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pExticrRegImage was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was invalid.
 */
driver_status_t _GPIO_EXTI_Helper_ResetPortConfigImage
(
	const gpio_pin_t pin,
	uint32_t* const pExticrRegImage
);

/**
 * @brief Updates the staged EXTI rising and falling trigger images for one line
 * @param[in] pin GPIO single-pin mask identifying the EXTI line
 * @param[in] trigger Driver EXTI trigger selector
 * @param[in,out] pRtsrRegImage Staged EXTI RTSR image
 * @param[in,out] pFtsrRegImage Staged EXTI FTSR image
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Trigger images updated successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: One or more staged-image pointers were null.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin or @p trigger was invalid.
 */
driver_status_t _GPIO_EXTI_Helper_UpdateTriggerImages
(
	const gpio_pin_t pin,
	const gpio_exti_trigger_t trigger,
	uint32_t* const pRtsrRegImage,
	uint32_t* const pFtsrRegImage
);

/**
 * @brief Clears the staged EXTI rising and falling trigger images for one line
 * @param[in] pin GPIO single-pin mask identifying the EXTI line
 * @param[in,out] pRtsrRegImage Staged EXTI RTSR image
 * @param[in,out] pFtsrRegImage Staged EXTI FTSR image
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Trigger images reset successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: One or more staged-image pointers were null.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was invalid.
 */
driver_status_t _GPIO_EXTI_Helper_ResetTriggerImages
(
	const gpio_pin_t pin,
	uint32_t* const pRtsrRegImage,
	uint32_t* const pFtsrRegImage
);

/**
 * @brief Returns the NVIC IRQ number associated with one GPIO EXTI line
 * @param[in] pin GPIO single-pin mask identifying the EXTI line
 * @param[out] pIRQn Destination for the NVIC IRQ number
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: IRQ number resolved successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pIRQn was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was invalid.
 */
driver_status_t _GPIO_EXTI_Helper_GetIRQn
(
	const gpio_pin_t pin,
	irq_t* const pIRQn
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_EXTI_HELPER_H_ */
