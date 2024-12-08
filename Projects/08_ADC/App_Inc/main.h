// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

// Bare Metal Libraries
#include "bare_metal.h"

// MACROS
#define SYSCLK_MHz                      (SYSCLK_72MHz)
#define DELAY_MS                        ((uint32_t) 100)
#define POT_PORT                        (GPIOA)      
#define POT_PIN                         (GPIO_PIN_4)
#define POT_ADC                         (ADC1)
#define POT_ADC_CHANNEL                 (ADC_CHANNEL_4)
#define POT_ADC_SAMPLE_TIME             (ADC_SAMPLE_CH4_SMP_239_5)
#define ADC_ERROR_RANGE                 ((uint16_t) 10)
#define LED_PORT                        (GPIOB)
#define LED_PIN                         (GPIO_PIN_12)

// System Clock Frequency (Core)
extern volatile uint32_t CoreClock;
// Advanced High Performance Bus (AHB) Frequency
extern volatile uint32_t AHBClock;
// Advanced Peripheral Bus 1 (APB1) Frequency
extern volatile uint32_t APB1Clock;
// Advanced Peripheral Bus 2 (APB2) Frequency
extern volatile uint32_t APB2Clock;

#endif /* __MAIN_H__ */
