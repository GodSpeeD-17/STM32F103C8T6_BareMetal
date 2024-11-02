// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

// Bare Metal Libraries
#include "gpio.h"
#include "rcc.h"
#include "systick.h"
#include "timer.h"
#include "pwm.h"
#include "nvic.h"

// MACROS
#define SYSCLK_MHz                      (SYSCLK_72MHz)
#define DELAY_MS                        ((uint32_t) 1000)  
#define GP_TIMER                        (TIM2)
#define TIMER_CHANNEL                   (TIMx_CHANNEL_3)
#define TIMER_PORT                      (GPIOA)     
#define TIMER_PIN                       (GPIO_PIN_2)     
#define TIMER_FREQ                      (FREQ_1kHz)
#define TIMER_ARR                       (DEFAULT_ARR_VALUE)
#define TIMER_CNT                       (BIT_RESET)
#define TIMER_IRQn                      (TIM2_IRQn)
#define LED_PORT                        (GPIOA)
#define LED_PIN                         (GPIO_PIN_2)

// System Clock Frequency (Core)
extern volatile uint32_t CoreClock;
// Advanced High Performance Bus (AHB) Frequency
extern volatile uint32_t AHBClock;
// Advanced Peripheral Bus 1 (APB1) Frequency
extern volatile uint32_t APB1Clock;
// Advanced Peripheral Bus 2 (APB2) Frequency
extern volatile uint32_t APB2Clock;


/**
 * @brief TIM2 IRQ Handler
 */
__attribute__((weak)) void TIM2_IRQHandler(void);

#endif /* __MAIN_H__ */