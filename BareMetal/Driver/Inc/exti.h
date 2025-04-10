/***************************************************************************************
 *  File: exti.h
 *  Created on: 17/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __EXTI_H__
#define __EXTI_H__

// Main Library
#include "reg_map.h"
#include "gpio.h"		// Structure
#include "nvic.h"		// Global Interrupt
#include "rcc.h"		// AFIO

// EXTI Configuration Structure
typedef struct {
	// GPIO Configuration Structure
	gpio_config_t* GPIO_CONFIGx;
	// EXTI Trigger Selection
	uint8_t TRIGx;
	// IRQ Number
	uint8_t IRQn;
} exti_config_t;

/**
 * @brief Enables the External Interrupt
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
__INLINE__ void EXTI_IRQ_enable(uint8_t PINx){
	// Disable the IRQ Mask
	EXTI->IMR.REG |= (1 << PINx);
}

/**
 * @brief Disables the External Interrupt Mask
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
__INLINE__ void EXTI_IRQ_disable(uint8_t PINx){
	// Enable the IRQ Mask
	EXTI->IMR.REG &= ~(1 << PINx);
}

/**
 * @brief Clear the EXTI bit
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
__INLINE__ void EXTI_clearPending(uint8_t PINx){
	// Acknowledge the Pending Bit
	EXTI->PR.REG |= (1 << PINx);
}

/**
 * @brief Returns the Pending Bit of External Interrupt
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @returns Pending Bit Status for Input Pin
 */
__INLINE__ uint8_t EXTI_getPending(uint8_t PINx){
	// Get the Pending Register Status
	uint32_t result = EXTI->PR.REG;
	// Get the exact bit
	result = ((result >> PINx) & 0x01);
	// Return the value
	return (uint8_t) result;
}

/**
 * @brief Configures the NVIC EXTI Source
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
void EXTI_srcConfig(GPIO_REG_STRUCT* GPIOx, uint8_t PINx);

/**
 * @brief Configures the External Interrupt Trigger Selection
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] TRIGx `EXTI_TRIG_FALLING`, `EXTI_TRIG_FALLING`, `EXTI_TRIG_BOTH`
 * @note The external wakeup lines are edge triggered, no glitches must be generated on these lines
 */
void EXTI_trigConfig(uint8_t PINx, uint8_t TRIGx);

/**
 * @brief Configures the EXTI Parameters Based Upon EXTI Configuration Structure
 * @param[in] EXTI_CONFIGx External Interrupt Configuration Structure 
 */
void EXTI_config(exti_config_t* EXTI_CONFIGx);

#endif /* __EXTI_H__ */