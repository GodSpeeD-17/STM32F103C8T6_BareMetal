// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

// Bare Metal Libraries
#include "bare_metal.h"

// MACROS
#define SYSCLK_MHz                      (SYSCLK_72MHz)
#define DELAY_MS                        ((uint32_t) 100)
#define LOOP_DELAY_MS                   ((uint32_t) 50)
// Indication LED
#define LED_PORT                        (GPIOB)
#define LED_PIN                         (GPIO_PIN_12)
// External LED1
#define LED1_PORT                       (GPIOA)
#define LED1_PIN                        (GPIO_PIN_2)
// External LED2
#define LED2_PORT                       (GPIOA)
#define LED2_PIN                        (GPIO_PIN_3)
// PWM Configuration for LED1 & LED2
#define GP_TIMER                        (TIM2)
#define GPT_FREQ                        (FREQ_10kHz)   
#define GPT_ARR                         (DEFAULT_ARR_VALUE)
#define GPT_CNT                         ((uint16_t) 0x00)
#define GPT_CHANNEL1                    (TIMx_CHANNEL_3)
#define GPT_CHANNEL2                    (TIMx_CHANNEL_4)
// Rising Edge   
#define PB_RISING_PORT                  (GPIOB)   
#define PB_RISING_PIN                   (GPIO_PIN_5)   
#define PB_RISING_IRQ_NUM               (EXTI9_5_IRQn)

// System Clock Frequency (Core)
extern volatile uint32_t CoreClock;
// Advanced High Performance Bus (AHB) Frequency
extern volatile uint32_t AHBClock;
// Advanced Peripheral Bus 1 (APB1) Frequency
extern volatile uint32_t APB1Clock;
// Advanced Peripheral Bus 2 (APB2) Frequency
extern volatile uint32_t APB2Clock;

#endif /* __MAIN_H__ */