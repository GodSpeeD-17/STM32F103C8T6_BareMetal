/*
	Basic Notes:-
	YT Reference Video: https://youtu.be/zvTd3Zxtiek
	`uint32_t` inside every BIT struct because of padding alignment
	`volatile` used for ensuring no optimization by compiler
	`: x` indicates only x bit(s) to be used from that 32-bit
*/

// Header Guards
#ifndef __REG_MAP_H__
#define __REG_MAP_H__

/*********************************************** ARM CORTEX M3 ***********************************************/
#include "./Reg_Map/systick_reg_map.h"
#include "./Reg_Map/flash_reg_map.h"
#include "./Reg_Map/wwdg_reg_map.h"
#include "./Reg_Map/nvic_reg_map.h"
/*********************************************** ARM CORTEX M3 ***********************************************/

/*********************************************** STM32F103C8T6 ***********************************************/
#include "./Reg_Map/rcc_reg_map.h"
#include "./Reg_Map/gpio_reg_map.h"
#include "./Reg_Map/afio_reg_map.h"
#include "./Reg_Map/advtim_reg_map.h"
#include "./Reg_Map/gpt_reg_map.h"
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
#define NVIC_SET_IRQ						((NVIC_IRQ_SET_REG_STRUCT *)(NVIC_BASE_ADDR))
#define NVIC_CLEAR_IRQ						((NVIC_IRQ_CLEAR_REG_STRUCT *)(NVIC_BASE_ADDR + (uint32_t) 0x0080))
#define NVIC_SET_PEND_IRQ					((NVIC_IRQ_SET_PEND_REG_STRUCT *)(NVIC_BASE_ADDR + (uint32_t) 0x0100))
#define NVIC_CLEAR_PEND_IRQ					((NVIC_IRQ_CLEAR_PEND_REG_STRUCT *)(NVIC_BASE_ADDR + (uint32_t) 0x0180))
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
/*********************************************** Address Mapping ***********************************************/


#endif  /* __REG_MAP_H__ */
