/*
	Basic Notes:-
	YT Reference Video: https://youtu.be/zvTd3Zxtiek
	`uint32_t` inside every BIT struct because of padding alignment
	`volatile` used for ensuring no further optimization by compiler
	`: x` indicates only x bit(s) to be used from that 32-bit
*/

// Header Guards
#ifndef __REG_MAP_H__
#define __REG_MAP_H__

/*********************************************** ARM CORTEX M3 ***********************************************/
#include "../Core/flash_reg_map.h"
#include "../Core/nvic_reg_map.h"
#include "../Core/systick_reg_map.h"
#include "../Core/wwdg_reg_map.h"
/*********************************************** ARM CORTEX M3 ***********************************************/

/*********************************************** STM32F103C8T6 ***********************************************/
#include "../Core/adc_reg_map.h"
#include "../Core/advtim_reg_map.h"
#include "../Core/afio_reg_map.h"
#include "../Core/exti_reg_map.h"
#include "../Core/gpio_reg_map.h"
#include "../Core/gpt_reg_map.h"
#include "../Core/rcc_reg_map.h"
#include "../Core/usart_reg_map.h"
/*********************************************** STM32F103C8T6 ***********************************************/

/*********************************************** Address Mapping ***********************************************/
// Memory Mapping
#define SYSTICK_BASE_ADDR					((uint32_t) 0xE000E010)
#define NVIC_BASE_ADDR                      ((uint32_t) 0xE000E100)
#define APB1_BASE_ADDR          			((uint32_t) 0x40000000)
#define APB2_BASE_ADDR          			((uint32_t) 0x40010000)
#define AHB_BASE_ADDR           			((uint32_t) 0x40018000)
#define FLASH_BASE_ADDR                     ((uint32_t) 0x40022000)

// Address Mapping
#define SYSTICK								((SYSTICK_REG_STRUCT *)(SYSTICK_BASE_ADDR))
#define NVIC								((NVIC_REG_STRUCT *)(NVIC_BASE_ADDR))
#define FLASH                               ((FLASH_REG_STRUCT *)(FLASH_BASE_ADDR))
#define WWDG								((WWDG_REG_STRUCT *) (APB1_BASE_ADDR + (uint32_t)0x2C00))
#define RCC                     			((RCC_REG_STRUCT *)(AHB_BASE_ADDR + (uint32_t)0x9000))
#define GPIOA                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x0800))
#define GPIOB                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x0C00))
#define GPIOC                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x1000))
#define GPIOD                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x1400))
#define GPIOE                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x1800))
#define GPIOF                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x1C00))
#define GPIOG                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x2000))
#define AFIO                                ((AFIO_REG_STRUCT *)(APB2_BASE_ADDR))
#define TIM1								((ADV_TIM_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x2C00))
#define TIM2								((GPT_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x0000))
#define TIM3								((GPT_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x0400))
#define TIM4								((GPT_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x0800))
#define TIM5								((GPT_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x0C00))
#define TIM6								((GPT_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x1000))
#define TIM7								((GPT_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x1400))
#define TIM8								((ADV_TIM_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x3400))
#define ADC1								((ADC_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x2400))
#define ADC2								((ADC_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x2800))
#define USART1								((USART_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x3800))
#define USART2								((USART_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x4400))
#define USART3								((USART_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x4800))
#define EXTI								((EXTI_REG_STRUCT*)(APB2_BASE_ADDR + (uint32_t)0x0400))
/*********************************************** Address Mapping ***********************************************/

/*********************************************** GPIO MACROS ***********************************************/
// GPIO PIN
#define GPIO_PIN_0							((uint8_t) 0)
#define GPIO_PIN_1							((uint8_t) 1)
#define GPIO_PIN_2							((uint8_t) 2)
#define GPIO_PIN_3							((uint8_t) 3)
#define GPIO_PIN_4							((uint8_t) 4)
#define GPIO_PIN_5							((uint8_t) 5)
#define GPIO_PIN_6							((uint8_t) 6)
#define GPIO_PIN_7							((uint8_t) 7)
#define GPIO_PIN_8							((uint8_t) 8)
#define GPIO_PIN_9							((uint8_t) 9)
#define GPIO_PIN_10							((uint8_t) 10)
#define GPIO_PIN_11							((uint8_t) 11)
#define GPIO_PIN_12							((uint8_t) 12)
#define GPIO_PIN_13							((uint8_t) 13)
#define GPIO_PIN_14							((uint8_t) 14)
#define GPIO_PIN_15							((uint8_t) 15)
#define OB_LED_PORT							(GPIOC)
#define OB_LED_PIN							(GPIO_PIN_13)

// MODE
#define MODE_IN								((uint8_t) 0)
#define MODE_OUT_10MHz						((uint8_t) 1)
#define MODE_OUT_2MHz						((uint8_t) 2)
#define MODE_OUT_50MHz						((uint8_t) 3)

// CONFIGURATION
#define CNF_IN_ANALOG						((uint8_t) 0)
#define CNF_IN_FLOAT						((uint8_t) 1)
#define CNF_IN_PD							((uint8_t) 3)
#define CNF_IN_PU							((uint8_t) 4)
#define CNF_OUT_GP_PP						((uint8_t) 0)
#define CNF_OUT_GP_OD						((uint8_t) 1)
#define CNF_OUT_AF_PP						((uint8_t) 2)
#define CNF_OUT_AF_OD						((uint8_t) 3)

// Error Checking MACROS
#define IS_VALID_GPIO(GPIOx) 				((GPIOx) == GPIOA || (GPIOx) == GPIOB || (GPIOx) == GPIOC)
#define IS_VALID_PIN(PINx) 					((PINx) <= GPIO_PIN_15)
#define IS_MODE_VALID(MODEx)				((MODEx) == MODE_IN || (MODEx) == MODE_OUT_10MHz || (MODEx) == MODE_OUT_2MHz || (MODEx) == MODE_OUT_50MHz)
#define IS_CNF_VALID(CNFx)					((CNFx) == CNF_IN_ANALOG || (CNFx) == CNF_IN_FLOAT || (CNFx) == CNF_IN_PD || (CNFx) == CNF_IN_PU || \
											 (CNFx) == CNF_OUT_GP_PP || (CNFx) == CNF_OUT_GP_OD || (CNFx) == CNF_OUT_AF_PP || (CNFx) == CNF_OUT_AF_OD)
#define ARE_GPIO_PARAMETERS_VALID(GPIOx, PINx, MODEx, CNFx)	\
											(IS_VALID_GPIO((GPIOx)) && \
											 IS_VALID_PIN((PINx)) && \
											 IS_MODE_VALID((MODEx)) && \
											 IS_CNF_VALID((CNFx)))
#define IS_MODE_IN_VALID(MODEx, CNFx)		(((MODEx) == MODE_IN && (CNFx) == CNF_IN_ANALOG) || ((MODEx) == MODE_IN && (CNFx) == CNF_IN_FLOAT) || \
											 ((MODEx) == MODE_IN && (CNFx) == CNF_IN_PD) || ((MODEx) == MODE_IN && (CNFx) == CNF_IN_PU))
#define IS_MODE_OUT_VALID(MODEx, CNFx)		(((MODEx) != MODE_IN && (CNFx) == CNF_OUT_GP_PP) || ((MODEx) != MODE_IN && (CNFx) == CNF_OUT_GP_OD) || \
											 ((MODEx) != MODE_IN && (CNFx) == CNF_OUT_AF_PP) || ((MODEx) != MODE_IN && (CNFx) == CNF_OUT_AF_OD))
#define IS_MODE_CNF_VALID(MODEx, CNFx)		(IS_MODE_IN_VALID((MODEx), (CNFx)) || IS_MODE_OUT_VALID((MODEx), (CNFx)))
/*********************************************** GPIO MACROS ***********************************************/

/*********************************************** RCC MACROS ***********************************************/

/*********************************************** RCC MACROS ***********************************************/


#endif  /* __REG_MAP_H__ */
