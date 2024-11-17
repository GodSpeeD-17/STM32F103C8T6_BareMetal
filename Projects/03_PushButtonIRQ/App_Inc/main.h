// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

// Bare Metal Libraries
#include "bare_metal.h"

// MACROS
#define SYSCLK_MHz                      (SYSCLK_72MHz)
#define DELAY_MS                        ((uint32_t) 10)    
#define IRQ_PORT                        (GPIOB)   
#define IRQ_PIN                         (GPIO_PIN_5)   
#define IRQ_NUM                         (EXTI9_5_IRQn)   
#define LED_PORT                        (GPIOA)
#define LED_PIN                         (GPIO_PIN_4)

// System Clock Frequency (Core)
extern volatile uint32_t CoreClock;
// Advanced High Performance Bus (AHB) Frequency
extern volatile uint32_t AHBClock;
// Advanced Peripheral Bus 1 (APB1) Frequency
extern volatile uint32_t APB1Clock;
// Advanced Peripheral Bus 2 (APB2) Frequency
extern volatile uint32_t APB2Clock;

#endif /* __MAIN_H__ */