// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

// Bare Metal Libraries
#include "bare_metal.h"

// LED Sequence Library
#include "led_function.h"

// MACROS
#define SYSCLK_MHz                      (SYSCLK_72MHz)
#define LOOP_DELAY_MS                   ((uint32_t) 10)
#define LED_DELAY_MS                    ((uint64_t) 1000)
// Rising Edge   
#define PB_RISING_PORT                  (GPIOB)   
#define PB_RISING_PIN                   (GPIO_PIN_5)   
#define PB_RISING_IRQ_NUM               (EXTI9_5_IRQn)  
#define LED_RISING_PORT                 (GPIOA)
#define LED_RISING_PIN                  (GPIO_PIN_4)
// Falling Edge 
#define PB_FALLING_PORT                 (GPIOB)   
#define PB_FALLING_PIN                  (GPIO_PIN_8)
#define PB_FALLING_IRQ_NUM              (EXTI9_5_IRQn)   
#define LED_FALLING_PORT                (GPIOA)
#define LED_FALLING_PIN                 (GPIO_PIN_9)

// System Clock Frequency (Core)
extern volatile uint32_t CoreClock;
// Advanced High Performance Bus (AHB) Frequency
extern volatile uint32_t AHBClock;
// Advanced Peripheral Bus 1 (APB1) Frequency
extern volatile uint32_t APB1Clock;
// Advanced Peripheral Bus 2 (APB2) Frequency
extern volatile uint32_t APB2Clock;

#endif /* __MAIN_H__ */