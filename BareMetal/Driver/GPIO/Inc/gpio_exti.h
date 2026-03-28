// /**
//  * @file gpio_exti.h
//  * @author Shrey Shah
//  * @brief GPIO Interrupt APIs
//  * @version v1.2
//  * @date 14-09-2025
//  */

// // Header Guards
// #ifndef GPIO_EXTI_H_
// #define GPIO_EXTI_H_

// /*********************************************** Includes ***********************************************/
// // GPIO Configuration
// #include "gpio.h"
// // Global Interrupt
// #include "nvic.h"

// /*********************************************** Helper APIs ***********************************************/
// /**
//  * @brief Enables the External Interrupt
//  * @param pin Refer to `gpio_pin_t` enum
//  */
// __STATIC_FORCEINLINE void GPIO_EXTI_Enable(const gpio_pin_t pin){
// 	// Unmask the IRQ
// 	EXTI->IMR.REG |= pin;
// }

// /**
//  * @brief Disables the External Interrupt
//  * @param pin Refer to `gpio_pin_t` enum
//  */
// __STATIC_FORCEINLINE void GPIO_EXTI_Disable(const gpio_pin_t pin){
// 	// Unmask the IRQ
// 	EXTI->IMR.REG &= ~(pin);
// }

// /**
//  * @brief Returns the Pending Bit of External Interrupt
//  * @param pin Refer to `gpio_pin_t` enum
//  * @returns Pending Bit Status for Input Pin
//  */
// __STATIC_FORCEINLINE uint16_t GPIO_EXTI_IsTriggered(const gpio_pin_t pin){
// 	// Return the value
// 	return (uint16_t) (EXTI->PR.REG & pin);
// }

// /**
//  * @brief Acknowledge the Pending Bit of External Interrupt
//  * @param pin Refer to `gpio_pin_t` enum
//  */
// __STATIC_FORCEINLINE void GPIO_EXTI_Ack(const gpio_pin_t pin){
// 	// Acknowledge the Pending Bit
// 	EXTI->PR.REG |= pin;
// }

// /**
//  * @brief Retrieves the EXTI Configuration Register based upon the Pin Number
//  * @param pin Refer to `gpio_pin_t` enum
//  * @return Pointer to the relevant EXTI Configuration Register
//  * @note Pass only one pin at a time
//  */
// __STATIC_FORCEINLINE uint32_t* __GPIO_EXTI_GetCR__(const gpio_pin_t pin){
// 	// Return the Register Address
// 	return (uint32_t *) (&AFIO->EXTICR1.REG + (__GPIO_getPin__(pin) >> 2));
// }

// /*********************************************** Driver APIs ***********************************************/
// /**
//  * @brief @brief Maps the EXTI Source Port to Interrupt
//  * @param gpio Refer to `gpio_port_t` enum
//  * @param pin Refer to `gpio_pin_t` enum
//  * @param extiConfigReg Pointer to the relevant EXTI Configuration Register
//  * @note Pass only one pin at a time
//  */
// void GPIO_EXTI_MapPort(const gpio_port_t gpio, const gpio_pin_t pin, uint32_t* extiConfigReg);

// /**
//  * @brief Unmaps the EXTI Source Port from Interrupt
//  * @param gpio Refer to `gpio_port_t` enum
//  * @param pin Refer to `gpio_pin_t` enum
//  * @param extiConfigReg Pointer to the relevant EXTI Configuration Register
//  * @note Pass only one pin at a time
//  */
// void GPIO_EXTI_UnmapPort(const gpio_port_t gpio, const gpio_pin_t pin, uint32_t* extiConfigReg);

// /**
//  * @brief Sets the EXTI Trigger Selection
//  * @param pin Refer to `gpio_pin_t` enum
//  * @param trigger Refer to `gpio_exti_trigger_t` enum
//  */
// void GPIO_EXTI_SetTrigger(const gpio_pin_t pin, const gpio_exti_trigger_t trigger);

// /**
//  * @brief Resets the EXTI Trigger Selection
//  * @param pin Refer to `gpio_pin_t` enum
//  * @param trigger Refer to `gpio_exti_trigger_t` enum
//  */
// void GPIO_EXTI_ResetTrigger(const gpio_pin_t pin, const gpio_exti_trigger_t trigger);

// /**
//  * @brief Initializes the External Interrupt
//  * @param gpio GPIO Port (Refer to `gpio_port_t` enum)
//  * @param pin GPIO Pin (Refer to `gpio_pin_t` enum)
//  * @param trigger GPIO Trigger (Refer to `gpio_exti_trigger_t` enum)
//  * @note - GPIO should be configured as Input: Floating or Pull-Up/Pull-Down
//  * @note - Failing to do so may cause driver to misbehave
//  * @return Status of Driver Operation
//  * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
//  * @returns - DRIVER_STATUS_SUCCESS: Success
//  */
// driver_status_t GPIO_EXTI_Init(const gpio_port_t gpio, const gpio_pin_t pin, const gpio_exti_trigger_t trigger);

// /**
//  * @brief Deinitialize the External Interrupt
//  * @param gpio GPIO Port (Refer to `gpio_port_t` enum)
//  * @param pin GPIO Pin (Refer to `gpio_pin_t` enum)
//  * @param trigger GPIO Trigger (Refer to `gpio_exti_trigger_t` enum)
//  * @note - GPIO should be configured as Input: Floating or Pull-Up/Pull-Down
//  * @note - Failing to do so may cause driver to misbehave
//  * @return Status of Driver Operation
//  * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
//  * @returns - DRIVER_STATUS_SUCCESS: Success
//  */
// driver_status_t GPIO_EXTI_Deinit(const gpio_port_t gpio, const gpio_pin_t pin, const gpio_exti_trigger_t trigger);

// #endif /* GPIO_EXTI_H_ */