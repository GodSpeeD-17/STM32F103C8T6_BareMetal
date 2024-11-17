/***************************************************************************************
 *  File: nvic.h
 *  Created on: 26/10/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __NVIC_H__
#define __NVIC_H__

// Main Library
#include "reg_map.h"

// External Trigger Selection
#define NVIC_TRIG_FALLING               ((uint8_t) 0)
#define NVIC_TRIG_RISING                ((uint8_t) 1)
#define NVIC_TRIG_BOTH                  ((uint8_t) 2)

// IRQn Number
#define WWDG_IRQn                       ((uint8_t) 0)
#define PVD_IRQn                        ((uint8_t) 1)
#define RTC_IRQn                        ((uint8_t) 3)
#define EXTI0_IRQn                      ((uint8_t) 6)
#define EXTI1_IRQn                      ((uint8_t) 7)
#define EXTI2_IRQn                      ((uint8_t) 8)
#define EXTI3_IRQn                      ((uint8_t) 9)
#define EXTI4_IRQn                      ((uint8_t) 10)
#define EXTI9_5_IRQn                    ((uint8_t) 23)
#define TIM2_IRQn                       ((uint8_t) 28)
#define EXTI15_10_IRQn                  ((uint8_t) 40)

/**
 * @brief Enables the NVIC Interrupt for the input IRQn
 * @param[in] IRQn  The Interrupt Number
 * @note Global Interrupt Configuration
 */
__attribute__((always_inline)) inline void enable_NVIC_IRQ(uint8_t IRQn){
	// Clear the Disable IRQn
	NVIC->ICER[((IRQn) / 32)] &=  ~(BIT_SET << ((IRQn) & (32 - 1)));
    // Enable the IRQn
    NVIC->ISER[((IRQn) / 32)] |=  (BIT_SET << ((IRQn) & (32 - 1)));
}

/**
 * @brief Disables the NVIC Interrupt for the input IRQn
 * @param[in] IRQn  The Interrupt Number
 * @note Global Interrupt Configuration
 */
__attribute__((always_inline)) inline void disable_NVIC_IRQ(uint8_t IRQn){
	// Clear the Enable IRQn
	NVIC->ISER[((IRQn) / 32)] &=  ~(1 << ((IRQn) & (32 - 1)));
    // Disable the IRQn
    NVIC->ICER[((IRQn) / 32)] |=  (1 << ((IRQn) & (32 - 1)));
}

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
 * @param[in] TRIGx `NVIC_TRIG_FALLING`, `NVIC_TRIG_FALLING`, `NVIC_TRIG_BOTH`
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
void config_NVIC_EXTI(GPIO_REG_STRUCT* GPIOx, uint8_t PINx, uint8_t TRIGx, uint8_t IRQn);

#endif /* __NVIC_H__ */
