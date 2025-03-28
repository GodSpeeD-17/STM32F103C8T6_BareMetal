// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

// Bare Metal Libraries
#include "bare_metal.h"

// MACROS
#define SYSCLK_MHz                      (SYSCLK_72MHz)
#define DELAY_MS                        ((uint32_t) 1000) 
#define LED_PORT                        (GPIOA)
#define LED_PIN                         (GPIO_PIN_2)   
#define GP_TIMER                        (TIM4)
#define GPT_CHANNEL                     (TIMx_CHANNEL_ALL)   
#define GPT_FREQ                        (FREQ_1kHz)   
#define GPT_ARR                         (DEFAULT_ARR_VALUE)
#define GPT_CNT                         ((uint16_t) 0x00)

// System Clock Frequency (Core)
extern volatile uint32_t CoreClock;
// Advanced High Performance Bus (AHB) Frequency
extern volatile uint32_t AHBClock;
// Advanced Peripheral Bus 1 (APB1) Frequency
extern volatile uint32_t APB1Clock;
// Advanced Peripheral Bus 2 (APB2) Frequency
extern volatile uint32_t APB2Clock;

#endif /* __MAIN_H__ */