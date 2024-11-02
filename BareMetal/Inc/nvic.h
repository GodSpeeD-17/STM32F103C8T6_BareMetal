// Header Guards
#ifndef __NVIC_H__
#define __NVIC_H__

// Main Library
#include "reg_map.h"

// Macros
#define WWDG_IRQn                       ((uint8_t) 0)
#define PVD_IRQn                        ((uint8_t) 1)
#define RTC_IRQn                        ((uint8_t) 3)
#define TIM2_IRQn                       ((uint8_t) 28)

/**
 * @brief Enables the NVIC Interrupt for the input IRQn
 * @param[in] IRQn  The Interrupt Number
 */
inline __attribute__((always_inline)) void enable_NVIC_IRQ(uint8_t IRQn){
	// Clear the IRQn
	NVIC->ICER[((IRQn) / 32)] &=  ~(BIT_SET << ((IRQn) & (32 - 1)));
    // Enable the IRQn
    NVIC->ISER[((IRQn) / 32)] |=  (BIT_SET << ((IRQn) & (32 - 1)));
}

/**
 * @brief Disables the NVIC Interrupt for the input IRQn
 * @param[in] IRQn  The Interrupt Number
 */
inline __attribute__((always_inline)) void disable_NVIC_IRQ(uint8_t IRQn){
	// Clear the IRQn
	NVIC->ISER[((IRQn) / 32)] &=  ~(BIT_SET << ((IRQn) & (32 - 1)));
    // Disable the IRQn
    NVIC->ICER[((IRQn) / 32)] |=  (BIT_SET << ((IRQn) & (32 - 1)));
}

#endif /* __NVIC_H__ */
