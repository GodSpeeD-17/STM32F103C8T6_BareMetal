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
#include "gpio.h"

/**
 * @brief Enables the External Interrupt
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
__INLINE__ void EXTI_IRQ_Enable(uint8_t PINx){
	// Unmask the IRQ
	EXTI->IMR.REG |= (1 << PINx);
}

/**
 * @brief Disables the External Interrupt Mask
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
__INLINE__ void EXTI_IRQ_Disable(uint8_t PINx){
	// Mask the IRQ
	EXTI->IMR.REG &= ~(1 << PINx);
}

/**
 * @brief Clear the EXTI bit
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
__INLINE__ void EXTI_IRQ_Clear_Pending(uint8_t PINx){
	// Acknowledge the Pending Bit
	EXTI->PR.REG |= (1 << PINx);
}

/**
 * @brief Returns the Pending Bit of External Interrupt
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @returns Pending Bit Status for Input Pin
 */
__INLINE__ uint8_t EXTI_IRQ_Get_Pending(uint8_t PINx){
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
__INLINE__ uint32_t* AFIO_EXTI_CR_Register(uint8_t PINx){
	// Return the Register Address
	return (uint32_t*)((&AFIO->EXTICR1) + (PINx >> 2));
}

/**
 * @brief Configures the NVIC EXTI Source
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
void EXTI_Source_Set(GPIO_REG_STRUCT* GPIOx, uint8_t PINx);

/**
 * @brief Configures the External Interrupt Trigger Selection
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] TRIGx `EXTI_TRIG_FALLING`, `EXTI_TRIG_FALLING`, `EXTI_TRIG_BOTH`
 * @note The external wakeup lines are edge triggered, no glitches must be generated on these lines
 */
void EXTI_Trigger_Set(uint8_t PINx, uint8_t TRIGx);

/**
 * @brief Configures the External Interrupt
 * @param[in] GPIO_CONFIGx GPIO Configuration Structure
 * @param[in] TRIGx `EXTI_TRIG_FALLING`, `EXTI_TRIG_RISING`, `EXTI_TRIG_BOTH`
 */
void EXTI_Config(gpio_config_t* GPIO_CONFIGx, uint8_t TRIGx);

#endif /* __EXTI_H__ */