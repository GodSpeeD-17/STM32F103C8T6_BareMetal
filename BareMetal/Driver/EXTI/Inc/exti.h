/***************************************************************************************
 *  File: exti.h
 *  Created on: 17/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __EXTI_H__
#define __EXTI_H__

// Register Map
#include "reg_map.h"
// GPIO
#include "gpio.h"
// Alternate Function I/O
#include "rcc.h"
 // Global Interrupt
#include "nvic.h"

#ifdef  __OLD_GPIO_METHOD__

/**
 * @brief Enables the External Interrupt
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
__STATIC_INLINE__ void EXTI_IRQ_Enable(uint8_t PINx){
	// Unmask the IRQ
	EXTI->IMR.REG |= (1 << PINx);
}

/**
 * @brief Disables the External Interrupt Mask
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
__STATIC_INLINE__ void EXTI_IRQ_Disable(uint8_t PINx){
	// Mask the IRQ
	EXTI->IMR.REG &= ~(1 << PINx);
}

/**
 * @brief Clear the EXTI bit
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
__STATIC_INLINE__ void EXTI_IRQ_Clear_Pending(uint8_t PINx){
	// Acknowledge the Pending Bit
	EXTI->PR.REG |= (1 << PINx);
}

/**
 * @brief Returns the Pending Bit of External Interrupt
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @returns Pending Bit Status for Input Pin
 */
__STATIC_INLINE__ uint8_t EXTI_IRQ_Get_Pending(uint8_t PINx){
	// Get the Pending Register Status
	uint32_t result = EXTI->PR.REG;
	// Get the exact bit
	result = ((result >> PINx) & 0x01);
	// Return the value
	return (uint8_t) result;
}

/**
 * @brief Retrieves the AFIO EXTI CR Register Address based upon the Pin Number
 * @param PINx `GPIO_PIN_x` Pin Number
 * @return Pointer to the relevant EXTI AFIO Register 
 */
__STATIC_INLINE__ uint32_t* AFIO_EXTI_CR_Register(uint8_t PINx){
	// Return the Register Address
	return (uint32_t*)((&AFIO->EXTICR1) + (PINx >> 2));
}

/**
 * @brief Configures the NVIC EXTI Source
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
void EXTI_Source_Set(GPIO_TypeDef* GPIOx, uint8_t PINx);

/**
 * @brief Configures the External Interrupt Trigger Selection
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] TRIGx `EXTI_TRIG_FALLING`, `EXTI_TRIG_FALLING`, `EXTI_TRIG_BOTH`
 * @note The external wakeup lines are edge triggered, no glitches must be generated on these lines
 */
void EXTI_Trigger_Set(uint8_t PINx, uint8_t TRIGx);

/**
 * @brief Configures the External Interrupt
 * @param[in] GPIOx_CONFIG GPIO Configuration Structure
 * @param[in] TRIGx `EXTI_TRIG_FALLING`, `EXTI_TRIG_RISING`, `EXTI_TRIG_BOTH`
 */
void EXTI_Config(gpio_config_t* GPIOx_CONFIG, uint8_t TRIGx);

#else

/**
 * @brief Enables the External Interrupt
 * @param pin Refer to `gpio_pin_t` enum
 */
__STATIC_INLINE__ void EXTI_IRQ_Enable(const gpio_pin_t pin){
	// Unmask the IRQ
	EXTI->IMR.REG |= pin;
}

/**
 * @brief Disables the External Interrupt
 * @param pin Refer to `gpio_pin_t` enum
 */
__STATIC_INLINE__ void EXTI_IRQ_Disable(const gpio_pin_t pin){
	// Unmask the IRQ
	EXTI->IMR.REG &= ~(pin);
}

/**
 * @brief Returns the Pending Bit of External Interrupt
 * @param pin Refer to `gpio_pin_t` enum
 * @returns Pending Bit Status for Input Pin
 */
__STATIC_INLINE__ uint16_t EXTI_IRQ_Get_Pending(const gpio_pin_t pin){
	// Return the value
	return (uint16_t) (EXTI->PR.REG & pin);
}

/**
 * @brief Acknowledge the Pending Bit of External Interrupt
 * @param pin Refer to `gpio_pin_t` enum
 */
__STATIC_INLINE__ void EXTI_IRQ_Ack(const gpio_pin_t pin){
	// Acknowledge the Pending Bit
	EXTI->PR.REG |= pin;
}

/**
 * @brief Retrieves the EXTI Configuration Register based upon the Pin Number
 * @param pin Refer to `gpio_pin_t` enum
 * @return Pointer to the relevant EXTI Configuration Register
 * @note Pass only one pin at a time
 */
uint32_t* __EXTI_getPointerToAFIO_EXTICRx__(const gpio_pin_t pin);

/**
 * @brief Sets the EXTI Source Port
 * @param gpio Refer to `gpio_port_t` enum
 * @param pin Refer to `gpio_pin_t` enum
 * @param extiConfigReg Pointer to the relevant EXTI Configuration Register
 * @note Pass only one pin at a time
 */
void EXTI_Set_Source_Port(const gpio_port_t gpio, gpio_pin_t pin, uint32_t* extiConfigReg);

/**
 * @brief Sets the EXTI Trigger Selection
 * @param pin Refer to `gpio_pin_t` enum
 * @param trigger Refer to `exti_trigger_t` enum
 */
void EXTI_Set_Trigger(const gpio_pin_t pin, const exti_trigger_t trigger);

/**
 * @brief Configures the External Interrupt
 * @param gpio GPIO Port (Refer to `gpio_port_t` enum)
 * @param pin GPIO Pin (Refer to `gpio_pin_t` enum)
 * @param trigger GPIO Trigger (Refer to `exti_trigger_t` enum)
 * @return Status of Driver Operation
 * @returns - DRIVER_FAIL: Failure
 * @returns - DRIVER_SUCCESS: Success
 */
driver_status_t EXTI_Config(const gpio_port_t gpio, const gpio_pin_t pin, const exti_trigger_t trigger);

#endif /* __OLD_GPIO_METHOD__ */

#endif /* __EXTI_H__ */