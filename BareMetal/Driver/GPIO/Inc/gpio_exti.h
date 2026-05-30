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

/** @brief Trigger on falling edge */
#define GPIO_EXTI_TRIGGER_FALLING						((gpio_exti_trigger_t) 0x01U)
/** @brief Trigger on rising edge */
#define GPIO_EXTI_TRIGGER_RISING						((gpio_exti_trigger_t) 0x02U)
/** @brief Trigger on both rising and falling edges */
#define GPIO_EXTI_TRIGGER_BOTH							((gpio_exti_trigger_t) (GPIO_EXTI_TRIGGER_FALLING | GPIO_EXTI_TRIGGER_RISING))

/**
 * @brief Checks whether an EXTI trigger selector is valid
 * @param[in] trigger Driver EXTI trigger selector
 * @returns Non-zero if valid, otherwise `0`
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

/** @brief EXTI source: GPIO Port A */
#define GPIO_EXTI_PORT_A								((gpio_exti_port_t) 0x00U)
/** @brief EXTI source: GPIO Port B */
#define GPIO_EXTI_PORT_B								((gpio_exti_port_t) 0x01U)
/** @brief EXTI source: GPIO Port C */
#define GPIO_EXTI_PORT_C								((gpio_exti_port_t) 0x02U)
/** @brief EXTI source: GPIO Port D */
#define GPIO_EXTI_PORT_D								((gpio_exti_port_t) 0x03U)
/** @brief EXTI source: GPIO Port E */
#define GPIO_EXTI_PORT_E								((gpio_exti_port_t) 0x04U)
/** @brief EXTI source: GPIO Port F */
#define GPIO_EXTI_PORT_F								((gpio_exti_port_t) 0x05U)
/** @brief EXTI source: GPIO Port G */
#define GPIO_EXTI_PORT_G								((gpio_exti_port_t) 0x06U)

/**
 * @brief Checks whether an AFIO EXTI port-source selector is valid
 * @param[in] portSource Driver EXTI port-source selector
 * @returns Non-zero if valid, otherwise `0`
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
 * @param[in] pin GPIO pin mask identifying the EXTI line(s)
 * @param[in] trigger Driver EXTI trigger selector
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: EXTI line initialization completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx, @p pin, or @p trigger was invalid, or the selected GPIO pin(s) were not configured as digital inputs.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
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
 * @param[in] pin GPIO pin mask identifying the EXTI line(s)
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: EXTI line deinitialization completed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx or @p pin was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed unexpectedly.
 */
driver_status_t GPIO_EXTI_Deinit(GPIO_TypeDef* const GPIOx, gpio_pin_t pin);

/**
 * @brief Returns whether any selected EXTI line is pending
 * @param[in] pin GPIO pin mask identifying the EXTI line(s)
 * @returns `0x01U` when any selected line is pending, otherwise `0x00U`
 * @note Returns `0x00U` when @p pin is invalid.
 */
uint8_t GPIO_EXTI_IsTriggered(const gpio_pin_t pin);

/**
 * @brief Acknowledges one or more EXTI pending line bits
 * @param[in] pin GPIO pin mask identifying the EXTI line(s)
 * @returns - @ref driver_status_t Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The selected pending bit(s) were acknowledged.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin was invalid.
 */
driver_status_t GPIO_EXTI_Ack(const gpio_pin_t pin);

/** @} */ // GPIO_EXTI_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_EXTI_H_ */
