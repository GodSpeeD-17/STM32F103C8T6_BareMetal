/**
 * @file	gpio_exti.h
 * @author	Shrey Shah
 * @brief	GPIO EXTI Driver Public Interface
 * @version	v1.0
 * @date	31-03-2026
 *
 * @details
 * This header defines the public EXTI driver built on top of the GPIO driver.
 *
 * Theory:
 * - Layer 0 owns the raw EXTI and AFIO register model and shared EXTI scalar types.
 * - Layer 1 (`gpio_exti_ll.h`) owns dumb EXTI/AFIO register access and AFIO
 *   clock forwarding.
 * - Layer 2 (`gpio_exti_helper.h` / `gpio_exti_helper.c`) bridges `GPIOx + pin`
 *   selectors to staged EXTI and AFIO register images.
 * - Layer 3 (`gpio_exti.h` / `gpio_exti.c`) owns the public EXTI API, validation,
 *   GPIO integration, NVIC policy, orchestration, and batched register writes.
 */

#ifndef GPIO_EXTI_H_
#define GPIO_EXTI_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "gpio.h"

/**
 * @defgroup GPIO_EXTI GPIO-backed External Interrupt Driver
 * @ingroup GPIO
 * @brief GPIO-aware EXTI routing, trigger configuration, and pending-bit control
 * @details
 * GPIO EXTI documentation is kept under the GPIO module because STM32F1 EXTI
 * line routing depends on GPIO pin selection and AFIO EXTICR port-source
 * configuration. Raw EXTI/AFIO register definitions remain in the Core layer.
 */

/**
 * @defgroup GPIO_EXTI_02_LL GPIO EXTI Low-Level Control Layer
 * @ingroup GPIO_EXTI
 * @brief Dumb EXTI/AFIO register-image access used by the GPIO EXTI driver
 */

/**
 * @defgroup GPIO_EXTI_03_Driver GPIO EXTI Driver Layer
 * @ingroup GPIO_EXTI
 * @brief Validated GPIO-backed EXTI orchestration layer
 */

/**
 * @addtogroup GPIO_EXTI_03_Driver
 * @{
 */

// ==================================================================================================== //
//                                         GPIO EXTI Data Types                                         //
// ==================================================================================================== //

/**
 * @brief GPIO EXTI driver types
 * @defgroup GPIO_EXTI_03_Driver_01_Types GPIO EXTI Driver Data Types
 * @ingroup GPIO_EXTI_03_Driver
 * @{
 */

/**
 * @brief Driver EXTI trigger selectors
 * @defgroup GPIO_EXTI_03_Driver_01_Types_01_Triggers GPIO EXTI Trigger Selectors
 * @ingroup GPIO_EXTI_03_Driver_01_Types
 * @{
 */

/** @brief Trigger on falling edge @def GPIO_EXTI_TRIGGER_FALLING */
#define GPIO_EXTI_TRIGGER_FALLING						((gpio_exti_trigger_t) 0x01U)
/** @brief Trigger on rising edge @def GPIO_EXTI_TRIGGER_RISING */
#define GPIO_EXTI_TRIGGER_RISING						((gpio_exti_trigger_t) 0x02U)
/** @brief Trigger on both rising and falling edges @def GPIO_EXTI_TRIGGER_BOTH */
#define GPIO_EXTI_TRIGGER_BOTH							((gpio_exti_trigger_t) (GPIO_EXTI_TRIGGER_FALLING | GPIO_EXTI_TRIGGER_RISING))

/**
 * @brief Checks whether an EXTI trigger selector is valid
 * @param[in] trigger Driver EXTI trigger selector
 * @returns Trigger selector validity status
 * @retval - `0x00U`: @p trigger is not a supported EXTI trigger selector
 * @retval - Non-zero: @p trigger is a supported EXTI trigger selector
 * @def GPIO_EXTI_IS_TRIGGER
 */
#define GPIO_EXTI_IS_TRIGGER(trigger)						\
(															\
	(((gpio_exti_trigger_t) (trigger)) != (gpio_exti_trigger_t) 0x00U) &&	\
	((((gpio_exti_trigger_t) (trigger)) &						\
	(~((gpio_exti_trigger_t) GPIO_EXTI_TRIGGER_BOTH))) == (gpio_exti_trigger_t) 0x00U)	\
)

/** @} */ // GPIO_EXTI_03_Driver_01_Types_01_Triggers

/**
 * @brief Driver AFIO EXTI port-source selectors
 * @defgroup GPIO_EXTI_03_Driver_01_Types_02_PortSources GPIO EXTI Port Source Selectors
 * @ingroup GPIO_EXTI_03_Driver_01_Types
 * @{
 */

/** @brief EXTI source: GPIO Port A @def GPIO_EXTI_PORT_A */
#define GPIO_EXTI_PORT_A								((gpio_exti_port_t) 0x00U)
/** @brief EXTI source: GPIO Port B @def GPIO_EXTI_PORT_B */
#define GPIO_EXTI_PORT_B								((gpio_exti_port_t) 0x01U)
/** @brief EXTI source: GPIO Port C @def GPIO_EXTI_PORT_C */
#define GPIO_EXTI_PORT_C								((gpio_exti_port_t) 0x02U)
/** @brief EXTI source: GPIO Port D @def GPIO_EXTI_PORT_D */
#define GPIO_EXTI_PORT_D								((gpio_exti_port_t) 0x03U)
/** @brief EXTI source: GPIO Port E @def GPIO_EXTI_PORT_E */
#define GPIO_EXTI_PORT_E								((gpio_exti_port_t) 0x04U)
/** @brief EXTI source: GPIO Port F @def GPIO_EXTI_PORT_F */
#define GPIO_EXTI_PORT_F								((gpio_exti_port_t) 0x05U)
/** @brief EXTI source: GPIO Port G @def GPIO_EXTI_PORT_G */
#define GPIO_EXTI_PORT_G								((gpio_exti_port_t) 0x06U)

/**
 * @brief Checks whether an AFIO EXTI port-source selector is valid
 * @param[in] portSource Driver EXTI port-source selector
 * @returns Port-source selector validity status
 * @retval - `0x00U`: @p portSource is not a supported EXTI port-source selector
 * @retval - Non-zero: @p portSource is a supported EXTI port-source selector
 * @def GPIO_EXTI_IS_PORT_SOURCE
 */
#define GPIO_EXTI_IS_PORT_SOURCE(portSource)				\
(															\
	((gpio_exti_port_t) (portSource)) <= GPIO_EXTI_PORT_G	\
)

/** @} */ // GPIO_EXTI_03_Driver_01_Types_02_PortSources

/** @} */ // GPIO_EXTI_03_Driver_01_Types

// ==================================================================================================== //
//                                              Driver APIs                                             //
// ==================================================================================================== //

/**
 * @brief Initializes one or more GPIO EXTI lines for the selected GPIO port
 * @details
 * Reads each touched AFIO and EXTI register once, updates staged images per
 * selected line, then writes each touched register once.
 *
 * The selected GPIO pins must already be configured as digital inputs using the
 * GPIO driver.
 *
 * @param[in] GPIOx GPIO peripheral instance that owns the selected EXTI line(s)
 * Accepted values:
 * - @ref `GPIOA`
 * - @ref `GPIOB`
 * - @ref `GPIOC`
 * - @ref `GPIOD`
 * - @ref `GPIOE`
 * - @ref `GPIOF`
 * - @ref `GPIOG`
 * @param[in] pin GPIO pin mask identifying the EXTI line(s)
 * Accepted values:
 * - One or more OR-combined values from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[in] trigger Driver EXTI trigger selector
 * Accepted values:
 * - @ref `GPIO_EXTI_TRIGGER_FALLING`
 * - @ref `GPIO_EXTI_TRIGGER_RISING`
 * - @ref `GPIO_EXTI_TRIGGER_BOTH`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: EXTI line initialization completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx, @p pin, or @p trigger was invalid, or the selected GPIO pin(s) were not configured as digital inputs.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 * @note Selected pins must already be configured as @ref `GPIO_PIN_MODE_INPUT`
 * with @ref `GPIO_PIN_CONFIG_INPUT_FLOATING`, @ref `GPIO_PIN_CONFIG_INPUT_PULL_DOWN`,
 * or @ref `GPIO_PIN_CONFIG_INPUT_PULL_UP`.
 */
driver_status_t GPIO_EXTI_Init(GPIO_TypeDef* const GPIOx, gpio_pin_t pin, const gpio_exti_trigger_t trigger);

/**
 * @brief Deinitializes one or more GPIO EXTI lines for the selected GPIO port
 * @details
 * Clears interrupt masking, clears rising/falling trigger selection, restores
 * the AFIO EXTI routing field(s) to reset state, and clears the selected
 * pending bit(s).
 *
 * @param[in] GPIOx GPIO peripheral instance that owns the selected EXTI line(s)
 * Accepted values:
 * - @ref `GPIOA`
 * - @ref `GPIOB`
 * - @ref `GPIOC`
 * - @ref `GPIOD`
 * - @ref `GPIOE`
 * - @ref `GPIOF`
 * - @ref `GPIOG`
 * @param[in] pin GPIO pin mask identifying the EXTI line(s)
 * Accepted values:
 * - One or more OR-combined values from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: EXTI line deinitialization completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pin was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 * @note This API enables AFIO long enough to restore EXTICR routing. It does
 * not disable AFIO after deinitialization.
 */
driver_status_t GPIO_EXTI_Deinit(GPIO_TypeDef* const GPIOx, gpio_pin_t pin);

/**
 * @brief Returns whether any selected EXTI line is pending
 * @param[in] pin GPIO pin mask identifying the EXTI line(s)
 * Accepted values:
 * - One or more OR-combined values from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @returns Pending-line status
 * @retval - `0x00U`: @p pin is invalid or none of the selected EXTI lines are pending.
 * @retval - `0x01U`: At least one selected EXTI line is pending.
 * @note Returns `0x00U` when @p pin is invalid.
 */
uint8_t GPIO_EXTI_IsTriggered(const gpio_pin_t pin);

/**
 * @brief Acknowledges one or more EXTI pending line bits
 * @param[in] pin GPIO pin mask identifying the EXTI line(s)
 * Accepted values:
 * - One or more OR-combined values from @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The selected pending bit(s) were acknowledged.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was invalid.
 * @note EXTI pending bits are write-one-to-clear bits. This API writes the
 * selected pin mask directly to `EXTI_PR`.
 */
driver_status_t GPIO_EXTI_Ack(const gpio_pin_t pin);

/** @} */ // GPIO_EXTI_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_EXTI_H_ */
