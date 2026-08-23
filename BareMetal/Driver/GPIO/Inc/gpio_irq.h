/**
 * @file	gpio_irq.h
 * @author	Shrey Shah
 * @brief	GPIO IRQ Driver Public Interface
 * @version	v1.0
 * @date	31-03-2026
 *
 * @details
 * This header defines the public GPIO-backed IRQ driver built on top of the GPIO driver.
 *
 * Theory:
 * - Layer 0 owns the raw EXTI and AFIO register model and shared EXTI scalar types.
 * - Layer 1 (`gpio_data_types.h` / `gpio_defines.h`) owns scalar aliases,
 *   public IRQ selectors, and pure validation.
 * - Layer 2 (`gpio_irq_ll.h`) owns dumb EXTI/AFIO register access and AFIO
 *   clock forwarding.
 * - Layer 3 (`gpio_irq_codec.h` / `gpio_irq_codec.c`) bridges GPIO pin masks
 *   and raw route/trigger selectors to staged EXTI and AFIO EXTICR images.
 * - Layer 4 (`gpio_irq.h` / `gpio_irq.c`) owns the public GPIO IRQ API, validation,
 *   GPIOx-to-route conversion, GPIO integration, EXTI orchestration, and
 *   batched register writes.
 */

#ifndef GPIO_IRQ_H_
#define GPIO_IRQ_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "gpio_defines.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup GPIO_IRQ GPIO-backed IRQ Driver
 * @ingroup GPIO
 * @brief GPIO-aware IRQ routing, trigger configuration, and pending-bit control
 * @details
 * GPIO IRQ documentation is kept under the GPIO module because STM32F1 EXTI
 * line routing depends on GPIO pin selection and AFIO EXTICR routing
 * configuration. Raw EXTI/AFIO register definitions remain in the Core layer.
 */

/**
 * @defgroup GPIO_IRQ_02_LL GPIO IRQ Low-Level Control Layer
 * @ingroup GPIO_IRQ
 * @brief Dumb EXTI/AFIO register-image access used by the GPIO IRQ driver
 */

/**
 * @defgroup GPIO_IRQ_03_Codec GPIO IRQ Codec Layer
 * @ingroup GPIO_IRQ
 * @brief Staged EXTI/AFIO route and trigger register-image translation layer
 */

/**
 * @defgroup GPIO_IRQ_04_Driver GPIO IRQ Driver Layer
 * @ingroup GPIO_IRQ
 * @brief Validated GPIO-backed EXTI orchestration layer
 */

/**
 * @addtogroup GPIO_IRQ_04_Driver
 * @{
 */

// ==================================================================================================== //
//                                              Driver APIs                                             //
// ==================================================================================================== //

/**
 * @brief Initializes one or more GPIO IRQ lines for the selected GPIO port
 * @details
 * Reads only the AFIO and EXTI register images needed for the selected line(s),
 * updates staged images, then writes back only the images that changed.
 *
 * @param[in] GPIOx GPIO peripheral instance that owns the selected GPIO IRQ line(s)
 * Accepted values:
 * - @ref `GPIOA`
 * - @ref `GPIOB`
 * - @ref `GPIOC`
 * - @ref `GPIOD`
 * - @ref `GPIOE`
 * - @ref `GPIOF`
 * - @ref `GPIOG`
 * @param[in] pinMask GPIO pin mask identifying the GPIO IRQ line(s)
 * Accepted values:
 * - One or more OR-combined values from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[in] inputConfig Driver GPIO input configuration selector
 * Accepted values:
 * - @ref `GPIO_PIN_CONFIG_INPUT_FLOATING`
 * - @ref `GPIO_PIN_CONFIG_INPUT_PULL_DOWN`
 * - @ref `GPIO_PIN_CONFIG_INPUT_PULL_UP`
 * @param[in] trigger Driver EXTI trigger selector
 * Accepted values:
 * - @ref `GPIO_IRQ_TRIGGER_FALLING`
 * - @ref `GPIO_IRQ_TRIGGER_RISING`
 * - @ref `GPIO_IRQ_TRIGGER_BOTH`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: GPIO IRQ line initialization completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx, @p pinMask, @p inputConfig, or @p trigger was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The @p GPIOx port clock gate is disabled, or the
 * internal staged-image update failed unexpectedly.
 * @pre The application enabled the matching GPIO port clock gate through the RCC driver before
 * calling this API; this API forwards that requirement to @ref `GPIO_Init`.
 * @note This API configures the selected GPIO pins as @ref `GPIO_PIN_MODE_INPUT`
 * before routing and unmasking the EXTI line(s).
 * @note Use @ref `GPIO_PIN_CONFIG_INPUT_FLOATING` when the board already has
 * an external pull-up or pull-down resistor.
 * @note This API does not enable any NVIC vector. The application or
 * integration layer owns global delivery, especially for shared EXTI vectors.
 */
driver_status_t GPIO_IRQ_Init
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pinMask,
	const gpio_pin_config_t		inputConfig,
	const gpio_irq_trigger_t		trigger
);

/**
 * @brief De-initializes one or more GPIO IRQ lines for the selected GPIO port
 * @details
 * Clears interrupt masking, clears rising/falling trigger selection, restores
 * the AFIO EXTI routing field(s) to reset state, and clears the selected
 * pending bit(s). Register images are written back only when the staged image
 * differs from the original image.
 *
 * @param[in] GPIOx GPIO peripheral instance that owns the selected GPIO IRQ line(s)
 * Accepted values:
 * - @ref `GPIOA`
 * - @ref `GPIOB`
 * - @ref `GPIOC`
 * - @ref `GPIOD`
 * - @ref `GPIOE`
 * - @ref `GPIOF`
 * - @ref `GPIOG`
 * @param[in] pinMask GPIO pin mask identifying the GPIO IRQ line(s)
 * Accepted values:
 * - One or more OR-combined values from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: GPIO IRQ line deinitialization completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pinMask was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 * @note This API enables AFIO long enough to restore EXTICR routing. It does
 * not disable AFIO after deinitialization.
 * @note Each selected line must currently be routed to @p GPIOx; this prevents
 * accidental deinitialization of another port sharing the same EXTI line number.
 * @note This API does not disable any NVIC vector.
 */
driver_status_t GPIO_IRQ_Deinit(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask);

/**
 * @brief Returns whether any selected GPIO IRQ line is pending
 * @param[in] pinMask GPIO pin mask identifying the GPIO IRQ line(s)
 * Accepted values:
 * - One or more OR-combined values from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @returns Pending-line status
 * @retval - @ref `DRIVER_STATUS_ON`: At least one selected GPIO IRQ line is pending.
 * @retval - @ref `DRIVER_STATUS_OFF`: None of the selected GPIO IRQ lines are pending.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinMask was invalid.
 */
driver_status_t GPIO_IRQ_IsTriggered(const gpio_pin_t pinMask);

/**
 * @brief Acknowledges one or more EXTI pending line bits
 * @param[in] pinMask GPIO pin mask identifying the GPIO IRQ line(s)
 * Accepted values:
 * - One or more OR-combined values from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The selected pending bit(s) were acknowledged.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pinMask was invalid.
 * @note EXTI pending bits are write-one-to-clear bits. This API writes the
 * selected pin mask directly to `EXTI_PR`.
 */
driver_status_t GPIO_IRQ_Ack(const gpio_pin_t pinMask);

/** @} */ // GPIO_IRQ_04_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_IRQ_H_ */
