// Header Guards
#ifndef __MAIN_H__
#define __MAIN_H__

// Bare Metal Libraries
#include "bare_metal.h"

// MACROS
#define SYSCLK_MHz					(SYSCLK_72MHz)
#define LOOP_DELAY_MS				((uint32_t) 50)

// USART MACROS
#define USART						(USART1)
#define USART_PORT					(GPIOA)
#define USART_TX_PIN				(GPIO_PIN_9)
#define USART_RX_PIN				(GPIO_PIN_10)

// ADC Definitions
#define POT_PORT					(GPIOA)
#define POT_PIN						(GPIO_PIN_4)
#define POT_ADC						(ADC1)
#define POT_ADC_CHANNEL				(ADC_CHANNEL_4)
#define ADC_ERROR_RANGE				((uint16_t) 10)

// PWM Definitions
#define LED_PORT					(GPIOA)
#define LED_PIN						(GPIO_PIN_2)
#define GP_TIMER					(TIM2)
#define GPT_CHANNEL					(TIMx_CHANNEL_3)

/**
 * @brief Duty Cycle Calculation based upon ADCx Value
 * @param[in] adc_value
 * @returns Duty Cycle Value (%)
 */
uint8_t calc_PWM_ADC(uint16_t adc_value);

#endif /* __MAIN_H__ */