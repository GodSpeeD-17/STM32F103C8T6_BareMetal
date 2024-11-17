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

// External Trigger Selection
#define EXTI_TRIG_FALLING               ((uint8_t) 0)
#define EXTI_TRIG_RISING                ((uint8_t) 1)
#define EXTI_TRIG_BOTH                  ((uint8_t) 2)

/**
 * @brief Enables the External Interrupt Mask
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
__attribute__((always_inline)) inline void enable_EXTI_IRQ(uint8_t PINx){
    // Enable the IRQ Mask
    EXTI->IMR.REG |= (1 << PINx);
}

/**
 * @brief Disables the External Interrupt Mask
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
__attribute__((always_inline)) inline void disable_EXTI_IRQ(uint8_t PINx){
    // Disable the IRQ Mask
    EXTI->IMR.REG &= ~(1 << PINx);
}

/**
 * @brief Configures the NVIC EXTI Source
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
void config_EXTI_src(GPIO_REG_STRUCT* GPIOx, uint8_t PINx);

/**
 * @brief Configures the External Interrupt Trigger Selection
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] TRIGx `EXTI_TRIG_FALLING`, `EXTI_TRIG_FALLING`, `EXTI_TRIG_BOTH`
 * @note The external wakeup lines are edge triggered, no glitches must be generated on these lines
 */
void config_EXTI_trig(uint8_t PINx, uint8_t TRIGx);

/**
 * @brief Configures the GPIO for EXTI
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] TRIGx `NVIC_TRIG_FALLING`, `NVIC_TRIG_FALLING`, `NVIC_TRIG_BOTH`
 * @param[in] IRQn The Interrupt Number
 */
void config_EXTI(GPIO_REG_STRUCT* GPIOx, uint8_t PINx, uint8_t TRIGx, uint8_t IRQn);

#endif /* __EXTI_H__ */