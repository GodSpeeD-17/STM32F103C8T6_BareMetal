// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

// Bare Metal Libraries
#include "bare_metal.h"

// MACROS
#define SYSCLK_MHz                      (SYSCLK_72MHz)
#define DELAY_MS                        ((uint32_t) 100)
// ADC Definitions
#define POT_PORT                        (GPIOA)      
#define POT_PIN                         (GPIO_PIN_4)
#define POT_ADC                         (ADC1)
#define POT_ADC_CHANNEL                 (ADC_CHANNEL_4)
#define POT_ADC_SAMPLE_TIME             (ADC_SAMPLE_CH4_SMP_239_5)
#define ADC_ERROR_RANGE                 ((uint16_t) 10)
// PWM Definitions
#define LED_PORT                        (GPIOA)
#define LED_PIN                         (GPIO_PIN_2)
#define GP_TIMER                        (TIM2)
#define GPT_CHANNEL                     (TIMx_CHANNEL_3)
#define GPT_FREQ                        (FREQ_10kHz)   
#define GPT_ARR                         (DEFAULT_ARR_VALUE)
#define GPT_CNT                         ((uint16_t) 0x00)
// Debugging LED
#define DEBUG_LED_PORT                  (GPIOB)
#define DEBUG_LED_PIN                   (GPIO_PIN_12)


// System Clock Frequency (Core)
extern volatile uint32_t CoreClock;
// Advanced High Performance Bus (AHB) Frequency
extern volatile uint32_t AHBClock;
// Advanced Peripheral Bus 1 (APB1) Frequency
extern volatile uint32_t APB1Clock;
// Advanced Peripheral Bus 2 (APB2) Frequency
extern volatile uint32_t APB2Clock;

/**
 * @brief Calculates Duty Cycle based upon input ADC Value
 * @param[in] adc_value 12-bit ADC Value
 */
uint8_t calc_PWM_ADC(uint16_t adc_value);

#endif /* __MAIN_H__ */