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

// Custom Declaration
#define NULL            					((void *) 0)

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
#define NVIC_BASE_ADDR						((uint32_t) 0xE000E100)
#define APB1_BASE_ADDR						((uint32_t) 0x40000000)
#define APB2_BASE_ADDR						((uint32_t) 0x40010000)
#define AHB_BASE_ADDR						((uint32_t) 0x40018000)
#define FLASH_BASE_ADDR						((uint32_t) 0x40022000)

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
// Generic
#define BIT_SET								((uint8_t) 0x01)
#define BIT_RESET							((uint8_t) 0x00)

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
#define IS_VALID_GPIO(GPIOx) 				((GPIOx) == GPIOA || (GPIOx) == GPIOB || (GPIOx) == GPIOC || (GPIOx) == NULL)
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
#define IS_GPIO_STRUCTURE_VALID(GPIO_CONFIGx)	\	
											(((GPIO_CONFIGx) == NULL) || (\
											 IS_VALID_GPIO(GPIO_CONFIGx->GPIOx) && \
											 IS_VALID_PIN(GPIO_CONFIGx->PINx) && \
											 IS_MODE_VALID(GPIO_CONFIGx->MODEx) && \
											 IS_CNF_VALID(GPIO_CONFIGx->CNFx) && \
											 IS_MODE_CNF_VALID(GPIO_CONFIGx->MODEx, GPIO_CONFIGx->CNFx)))

/*********************************************** GPIO MACROS ***********************************************/

/*********************************************** RCC MACROS ***********************************************/
// Generic Frequencies
#define FREQ_12Hz							((uint32_t) (12))   
#define FREQ_25Hz							((uint32_t) ((2 * FREQ_12Hz) + (uint32_t) 1))   
#define FREQ_50Hz							((uint32_t) (2 * FREQ_25Hz))   
#define FREQ_100Hz							((uint32_t) (2 * FREQ_50Hz))   
#define FREQ_500Hz							((uint32_t) (5 * FREQ_100Hz))   
#define FREQ_1kHz							((uint32_t) (10 * FREQ_100Hz))   
#define FREQ_2kHz							((uint32_t) (2 * FREQ_1kHz))   
#define FREQ_5kHz							((uint32_t) (5 * FREQ_1kHz))   
#define FREQ_10kHz							((uint32_t) (10 * FREQ_1kHz))   
#define FREQ_50kHz							((uint32_t) (50 * FREQ_1kHz))   
#define FREQ_72kHz							((uint32_t) (72 * FREQ_1kHz))   
#define FREQ_100kHz							((uint32_t) (100 * FREQ_1kHz))   
#define FREQ_200kHz							((uint32_t) (2 * FREQ_100kHz)) 
#define FREQ_1MHz							((uint32_t) (FREQ_1kHz * FREQ_1kHz))
#define FREQ_10MHz							((uint32_t) (10 * FREQ_1MHz))

// Clock Speed
#define HSI_FREQ							((uint32_t) (8 * FREQ_1MHz))
#define HSE_FREQ							((uint32_t) (8 * FREQ_1MHz))
#define PLL_MIN_FREQ						((uint32_t) (16 * FREQ_1MHz))
#define PLL_MAX_FREQ						((uint32_t) (72 * FREQ_1MHz))

// Clock Source
#define SW_CLK_HSI							((uint8_t) 0x00)
#define SW_CLK_HSE							((uint8_t) 0x01)
#define SW_CLK_PLL							((uint8_t) 0x02)

// AHB Prescaler
#define AHB_DIV_1							((uint8_t) 0x00)
#define AHB_DIV_2							((uint8_t) 0x08)
#define AHB_DIV_4							((uint8_t) 0x09)
#define AHB_DIV_8							((uint8_t) 0x0A)
#define AHB_DIV_16							((uint8_t) 0x0B)
#define AHB_DIV_64							((uint8_t) 0x0C)
#define AHB_DIV_128							((uint8_t) 0x0D)
#define AHB_DIV_256							((uint8_t) 0x0E)
#define AHB_DIV_512							((uint8_t) 0x0F)

// APB1 Prescaler
#define APB1_DIV_1							((uint8_t) 0x03)
#define APB1_DIV_2							((uint8_t) 0x04)
#define APB1_DIV_4							((uint8_t) 0x05)
#define APB1_DIV_8							((uint8_t) 0x06)
#define APB1_DIV_16							((uint8_t) 0x07)

// APB2 Prescaler
#define APB2_DIV_1							((uint8_t) 0x03)
#define APB2_DIV_2							((uint8_t) 0x04)
#define APB2_DIV_4							((uint8_t) 0x05)
#define APB2_DIV_8							((uint8_t) 0x06)
#define APB2_DIV_16							((uint8_t) 0x07)

// ADC Prescaler
#define ADC_DIV_2							((uint8_t) 0x00)
#define ADC_DIV_4							((uint8_t) 0x01)
#define ADC_DIV_6							((uint8_t) 0x02)
#define ADC_DIV_8							((uint8_t) 0x03)

// PLL Clock Source
#define PLL_SRC_HSI_DIV_2					((uint8_t) 0x00)
#define PLL_SRC_HSE							((uint8_t) 0x01)

// PLL Clock Source Prescaler
#define PLL_HSE_DIV_1						((uint8_t) 0x00)
#define PLL_HSE_DIV_2						((uint8_t) 0x01)

// PLL Multiplication Factor
#define PLL_MUL_2							((uint8_t) 0x00)
#define PLL_MUL_3							((uint8_t) 0x01)
#define PLL_MUL_4							((uint8_t) 0x02)
#define PLL_MUL_5							((uint8_t) 0x03)
#define PLL_MUL_6							((uint8_t) 0x04)
#define PLL_MUL_7							((uint8_t) 0x05)
#define PLL_MUL_8							((uint8_t) 0x06)
#define PLL_MUL_9							((uint8_t) 0x07)
#define PLL_MUL_10							((uint8_t) 0x08)
#define PLL_MUL_11							((uint8_t) 0x09)
#define PLL_MUL_12							((uint8_t) 0x0A)
#define PLL_MUL_13							((uint8_t) 0x0B)
#define PLL_MUL_14							((uint8_t) 0x0C)
#define PLL_MUL_15							((uint8_t) 0x0D)
#define PLL_MUL_16_0						((uint8_t) 0x0E)
#define PLL_MUL_16_1						((uint8_t) 0x0F)

// USB Prescaler
#define USB_DIV_1_5							((uint8_t) 0x00)
#define USB_DIV_1							((uint8_t) 0x01)

// PLL Clock Source
typedef enum {
	HSE_DIV_1 = (uint8_t)0XAA,
	HSE_DIV_2 = (uint8_t)0XBB,
	HSI_DIV_2 = (uint8_t)0XCC,
} PLL_CLK_SRC_ENUM;

// System Clock Frequency
typedef enum {
	SYSCLK_16MHz = (uint8_t) 0x01,
	SYSCLK_24MHz,
	SYSCLK_32MHz,
	SYSCLK_40MHz,
	SYSCLK_48MHz,
	SYSCLK_56MHz,
	SYSCLK_64MHz,
	SYSCLK_72MHz,
} SYSCLK_FREQ;
/*********************************************** RCC MACROS ***********************************************/

/*********************************************** NVIC MACROS ***********************************************/
// IRQn Number
#define WWDG_IRQn							((uint8_t) 0)
#define PVD_IRQn							((uint8_t) 1)
#define TAMPER_IRQn							((uint8_t) 2)
#define RTC_IRQn							((uint8_t) 3)
#define RCC_IRQn							((uint8_t) 5)
#define EXTI0_IRQn							((uint8_t) 6)
#define EXTI1_IRQn							((uint8_t) 7)
#define EXTI2_IRQn							((uint8_t) 8)
#define EXTI3_IRQn							((uint8_t) 9)
#define EXTI4_IRQn							((uint8_t) 10)
#define EXTI9_5_IRQn						((uint8_t) 23)
#define TIM2_IRQn							((uint8_t) 28)
#define TIM3_IRQn							((uint8_t) 29)
#define TIM4_IRQn							((uint8_t) 30)
#define SPI1_IRQn							((uint8_t) 35)
#define SPI2_IRQn							((uint8_t) 36)
#define USART1_IRQn							((uint8_t) 37)
#define USART2_IRQn							((uint8_t) 38)
#define USART3_IRQn							((uint8_t) 39)
#define EXTI15_10_IRQn						((uint8_t) 40)

/*********************************************** NVIC MACROS ***********************************************/

/*********************************************** EXTI MACROS ***********************************************/
// External Trigger Selection
#define EXTI_TRIG_FALLING               ((uint8_t) 0x00)
#define EXTI_TRIG_RISING                ((uint8_t) 0x01)
#define EXTI_TRIG_BOTH                  ((uint8_t) 0x02)

// AF EXTI
#define AF_EXTI_PA						((uint8_t) 0x00)
#define AF_EXTI_PB                      ((uint8_t) 0x01)
#define AF_EXTI_PC                      ((uint8_t) 0x02)
#define AF_EXTI_PD                      ((uint8_t) 0x03)
#define AF_EXTI_PE                      ((uint8_t) 0x04)
#define AF_EXTI_PF                      ((uint8_t) 0x05)
#define AF_EXTI_PG                      ((uint8_t) 0x06)

// Error Checking MACROs
#define IS_EXTI_TRIG_VALID(TRIGx)            (((TRIGx) == EXTI_TRIG_FALLING) \
											 || ((TRIGx) == EXTI_TRIG_RISING) \
											 || ((TRIGx) == EXTI_TRIG_BOTH))
#define IS_EXTI_IRQn_VALID(IRQn)			((IRQn) < 60)
#define IS_EXTI_STRUCTURE_VALID(EXTI_CONFIGx)	\
											((IS_GPIO_STRUCTURE_VALID(EXTI_CONFIGx->GPIO_CONFIGx) )&& \
											 (IS_EXTI_TRIG_VALID(EXTI_CONFIGx->TRIGx)) && \
											 (IS_EXTI_IRQn_VALID(EXTI_CONFIGx->IRQn)) && \
											 (EXTI_CONFIGx->GPIO_CONFIGx->MODEx == MODE_IN))
								 
/*********************************************** EXTI MACROS ***********************************************/


/*********************************************** SYSTICK MACROS ***********************************************/
// SysTick
#define SYSTICK_CLK_EXT						((uint8_t) 0x00)
#define SYSTICK_CLK_CORE					((uint8_t) 0x01)
/*********************************************** SYSTICK MACROS ***********************************************/

/*********************************************** GPT MACROS ***********************************************/
// Centre-align Mode Selection
#define CMS_EDGE							((uint8_t) 0x00)
#define CMS_IF_DOWN							((uint8_t) 0x01)
#define CMS_IF_UP							((uint8_t) 0x02)
#define CMS_IF_BOTH							((uint8_t) 0x03)

// Clock Division
#define CKD_CLK_FREQ						((uint8_t) 0x00)
#define CKD_CLK_2_FREQ						((uint8_t) 0x01)
#define CKD_CLK_4_FREQ						((uint8_t) 0x02)

// Master Mode Selection
#define MMS_RESET							((uint8_t) 0x00)
#define MMS_ENABLE							((uint8_t) 0x01)
#define MMS_UPDATE							((uint8_t) 0x02)
#define MMS_CMP_PULSE						((uint8_t) 0x03)
#define MMS_CMP_OC1REF						((uint8_t) 0x04)
#define MMS_CMP_OC2REF						((uint8_t) 0x05)
#define MMS_CMP_OC3REF						((uint8_t) 0x06)
#define MMS_CMP_OC4REF						((uint8_t) 0x07)

// Slave Mode Selection
#define SMS_DISABLE							((uint8_t) 0x00)
#define SMS_ENC_MODE1						((uint8_t) 0x01)
#define SMS_ENC_MODE2						((uint8_t) 0x02)
#define SMS_ENC_MODE3						((uint8_t) 0x03)

// TIM1 REMAP
#define TIM1_NO_REMAP						((uint8_t) 0x00)    // (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12, CH1N/PB13, CH2N/PB14, CH3N/PB15)
#define TIM1_PARTIAL_REMAP					((uint8_t) 0x01)    // (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6, CH1N/PA7, CH2N/PB0, CH3N/PB1)
#define TIM1_NOT_USED_REMAP					((uint8_t) 0x02)    // Not Used
#define TIM1_FULL_REMAP						((uint8_t) 0x03)    // (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15, CH1N/PE8, CH2N/PE10, CH3N/PE12)

// TIM2 REMAP
#define TIM2_NO_REMAP						((uint8_t) 0x00)    // (CH1/ETR/PA0, CH2/PA1, CH3/PA2, CH4/PA3)
#define TIM2_PARTIAL1_REMAP					((uint8_t) 0x01)    // (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3)
#define TIM2_PARTIAL2_REMAP					((uint8_t) 0x02)    // (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11)
#define TIM2_FULL_REMAP						((uint8_t) 0x03)    // (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11) 

// TIM3 REMAP
#define TIM3_NO_REMAP						((uint8_t) 0x00)    // (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1)
#define TIM3_NOT_USED_REMAP					((uint8_t) 0x01)    // Not Used
#define TIM3_PARTIAL_REMAP					((uint8_t) 0x02)    // (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1)
#define TIM3_FULL_REMAP						((uint8_t) 0x03)    // (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9) 

// TIM4 REMAP
#define TIM4_NO_REMAP						((uint8_t) 0x00)    // (TIM4_CH1/PB6, TIM4_CH2/PB7, TIM4_CH3/PB8, TIM4_CH4/PB9)
#define TIM4_FULL_REMAP						((uint8_t) 0x01)    // (TIM4_CH1/PD12, TIM4_CH2/PD13, TIM4_CH3/PD14, TIM4_CH4/PD15)

// Channel
#define TIMx_CHANNEL_1						((uint8_t) 0x01)
#define TIMx_CHANNEL_2						((uint8_t) 0x02)
#define TIMx_CHANNEL_3						((uint8_t) 0x04)
#define TIMx_CHANNEL_4						((uint8_t) 0x08)
#define TIMx_CHANNEL_ALL					(TIMx_CHANNEL_1 | TIMx_CHANNEL_2 | TIMx_CHANNEL_3 | TIMx_CHANNEL_4)

// Counting Mode
#define TIMx_MODE_NORMAL					((uint8_t) 0x00)    // Up if DIR = 0 else Down if DIR = 1
#define TIMx_MODE_ALT_IF_DOWN				((uint8_t) 0x01)
#define TIMx_MODE_ALT_IF_UP					((uint8_t) 0x02)
#define TIMx_MODE_ALT_IF_BOTH				((uint8_t) 0x03)

// Direction 
#define TIMx_COUNT_UP						((uint8_t) 0x00)
#define TIMx_COUNT_DOWN						((uint8_t) 0x01)

// Auto Reload Preload 
#define TIMx_ARPE_DISABLE					((uint8_t) 0x00)
#define TIMx_ARPE_ENABLE					((uint8_t) 0x01)

// One Pulse Mode
#define TIMx_OPM_DISABLE					((uint8_t) 0x00)
#define TIMx_OPM_ENABLE						((uint8_t) 0x01)

// IRQ Enable
#define TIMx_IRQ_DISABLE					((uint8_t) 0x00)
#define TIMx_IRQ_ENABLE						((uint8_t) 0x01)

// Error Check MACROS
#define IS_VALID_GPT(GP_TIMx)				((GP_TIMx) == TIM2 || (GP_TIMx) == TIM3 || (GP_TIMx) == TIM4)
#define IS_VALID_GPT_CHANNEL(CHx)			(((CHx) & ~(TIMx_CHANNEL_1 | TIMx_CHANNEL_2 | TIMx_CHANNEL_3 | TIMx_CHANNEL_4)) == ((uint8_t)0x00))
#define IS_VALID_GPT_CMS_MODE(MODEx)		((MODEx) == CMS_EDGE || (MODEx) == CMS_IF_BOTH || (MODEx) == CMS_IF_DOWN || (MODEx) == CMS_IF_UP)
#define IS_VALID_GPT_DIRECTION(DIRx)		((DIRx) == TIMx_COUNT_UP || (DIRx) == TIMx_COUNT_DOWN)
#define IS_VALID_GPT_COUNT_MODE(MODEx)		((MODEx) == TIMx_MODE_NORMAL || (MODEx) == TIMx_MODE_ALT_IF_DOWN || \
											 (MODEx) == TIMx_MODE_ALT_IF_UP || (MODEx) == TIMx_MODE_ALT_IF_BOTH)
#define IS_VALID_GPT_ARR(ARRx)				(((ARRx) >= (uint16_t)0x00) && ((ARRx) < (uint16_t)0xFFFF))
#define IS_VALID_GPT_FREQ(FREQx)			(((FREQx) > (uint32_t)0x00) && ((FREQx) <= PLL_MAX_FREQ))
#define IS_VALID_GPT_CNT(CNTx)				(((CNTx) >= (uint16_t)0x00) && ((CNTx) <= (uint16_t)0xFFFF))
#define IS_VALID_GPT_ARPE(ARPEx)			((ARPEx) == TIMx_ARPE_DISABLE || ((ARPEx) == TIMx_ARPE_ENABLE))
#define IS_VALID_GPT_OPM(OPMx)				((OPMx) == TIMx_OPM_DISABLE || ((OPMx) == TIMx_OPM_ENABLE))
#define IS_VALID_GPT_IRQ(IRQx)				(((IRQx) == TIMx_IRQ_ENABLE) || ((IRQx) == TIMx_IRQ_DISABLE))
#define IS_VALID_GPT_CONFIG_STRUCT(GPT_CONFIGx) \
											(IS_GPIO_STRUCTURE_VALID(GPT_CONFIGx->GPIO_CONFIGx) && \
											 IS_VALID_GPT((GPT_CONFIGx->GP_TIMx)) && \
											 IS_VALID_GPT_CHANNEL((GPT_CONFIGx->channel)) && \
											 IS_VALID_GPT_ARR((GPT_CONFIGx->auto_reload_value)) && \
											 IS_VALID_GPT_FREQ((GPT_CONFIGx->frequency_Hz)) && \
											 IS_VALID_GPT_CNT((GPT_CONFIGx->count)) && \
											 IS_VALID_GPT_CMS_MODE((GPT_CONFIGx->cms_mode)) && \
											 IS_VALID_GPT_DIRECTION((GPT_CONFIGx->direction)) && \
											 IS_VALID_GPT_ARPE((GPT_CONFIGx->auto_reload_preload)) && \
											 IS_VALID_GPT_OPM((GPT_CONFIGx->one_pulse)))									 
/*********************************************** GPT MACROS ***********************************************/

/*********************************************** PWM MACROS ***********************************************/
// IMP: Store this value in ARR always to simplify the PWM calculation
#define DEFAULT_ARR_VALUE					((uint16_t) 99)    // (ARR + 1) = (99 + 1) = (100) 
#define MIN_DUTY_CYCLE						((uint8_t) 1)      // Min Value = 1%
#define MAX_DUTY_CYCLE						((uint8_t) 100)    // Max Value = 100%

// Timer Remapping
#define TIM1_NO_REMAP						((uint8_t) 0x00)
#define TIM1_PARTIAL_REMAP					((uint8_t) 0x01)
#define TIM2_NO_REMAP						((uint8_t) 0x00)
#define TIM2_PARTIAL_REMAP_1				((uint8_t) 0x01)
#define TIM2_PARTIAL_REMAP_2				((uint8_t) 0x02)
#define TIM2_FULL_REMAP						((uint8_t) 0x03)
#define TIM3_NO_REMAP						((uint8_t) 0x00)
#define TIM3_PARTIAL_REMAP					((uint8_t) 0x02)
#define TIM4_NO_REMAP						((uint8_t) 0x00)

// Preload Enable
#define PRELOAD_DISABLE						((uint8_t) 0x00)
#define PRELOAD_ENABLE						((uint8_t) 0x01)

// Polarity (Defines what Active means)
#define TIMx_POL_ACTIVE_HIGH				((uint8_t) 0x00)
#define TIMx_POL_ACTIVE_LOW					((uint8_t) 0x01)

// Timer Modes
typedef enum{
	TIMx_OCM_FREEZE         = ((uint8_t) 0x00),    // The comparison between the output compare register TIMx_CCRy and the counter TIMx_CNT has no effect on the outputs.
	TIMx_OCM_SET_CH         = ((uint8_t) 0x01),    // OCyREF signal is forced high when TIMx_CNT == TIMx_CCRy    
	TIMx_OCM_RESET_CH       = ((uint8_t) 0x02),    // OCyREF signal is forced low when TIMx_CNT == TIMx_CCRy
	TIMx_OCM_TOGGLE         = ((uint8_t) 0x03),    // OCyREF toggles when TIMx_CNT == TIMx_CCRy
	TIMx_OCM_FORCE_RESET    = ((uint8_t) 0x04),    // OCyREF is forced low
	TIMx_OCM_FORCE_SET      = ((uint8_t) 0x05),    // OCyREF is forced high
	TIMx_OCM_PWM_NORMAL     = ((uint8_t) 0x06),    // In up counting, CHy is active as long as TIMx_CNT < TIMx_CCRy else inactive. In down counting, CHy is inactive (OC1REF = ‘0’) as long as TIMx_CNT > TIMx_CCRy else active (OC1REF = ’1’) 
	TIMx_OCM_PWM_INVERTED   = ((uint8_t) 0x07),    // In up counting, CHy is inactive as long as TIMx_CNT < TIMx_CCRy else active. In down counting, CHy is active (OC1REF = ‘0’) as long as TIMx_CNT > TIMx_CCRy else active (OC1REF = ’1’) 
} TIMx_OCM_MODE;

// PWM Channel Preload Enable
#define PWM_CHx_PRELOAD_DISABLE				((uint8_t) 0x00)
#define PWM_CHx_PRELOAD_ENABLE				((uint8_t) 0x01)


// Error Checking MACROS
#define IS_VALID_PWM_MODE(MODEx)			((MODEx) == TIMx_OCM_FREEZE || (MODEx) == TIMx_OCM_SET_CH || \
											 (MODEx) == TIMx_OCM_RESET_CH || (MODEx) == TIMx_OCM_TOGGLE || \
											 (MODEx) == TIMx_OCM_FORCE_RESET || (MODEx) == TIMx_OCM_FORCE_SET || \
											 (MODEx) == TIMx_OCM_PWM_NORMAL || (MODEx) == TIMx_OCM_PWM_INVERTED)
#define IS_VALID_PWM_POLARITY(POLx)			((POLx) == TIMx_POL_ACTIVE_HIGH || (POLx) == TIMx_POL_ACTIVE_LOW)
#define IS_VALID_PWM_DUTY_CYCLE(DUTYx)		((DUTYx) >= MIN_DUTY_CYCLE && (DUTYx) <= MAX_DUTY_CYCLE)
#define IS_VALID_PWM_CHANNEL_PRELOAD(CH_PRx)(((CH_PRx) == PWM_CHx_PRELOAD_DISABLE) || ((CH_PRx) == PWM_CHx_PRELOAD_ENABLE))
#define IS_VALID_PWM_CONFIG_STRUCT(PWM_CONFIGx) \
											(IS_VALID_GPT_CONFIG_STRUCT(PWM_CONFIGx->GPT_CONFIGx) && \
											 IS_VALID_PWM_MODE(PWM_CONFIGx->pwm_mode) && \
											 IS_VALID_PWM_POLARITY(PWM_CONFIGx->polarity) && \
											 IS_VALID_PWM_DUTY_CYCLE(PWM_CONFIGx->duty_cycle) && \
											 IS_VALID_PWM_CHANNEL_PRELOAD(PWM_CONFIGx->pwm_channel_preload))
#define WRAP_DUTY_CYCLE(DUTYx)				((DUTYx) = (((DUTYx) > MAX_DUTY_CYCLE) ? (MAX_DUTY_CYCLE) : (((DUTYx) < MIN_DUTY_CYCLE) ? (MIN_DUTY_CYCLE) : (DUTYx))))
#define PWM_DUTY_CYCLE_WRAP(PWMx)			(WRAP_DUTY_CYCLE(((PWMx)->duty_cycle)))

/*********************************************** PWM MACROS ***********************************************/

/*********************************************** ADC MACROS ***********************************************/
// ADC Max Value
#define MAX_ADC_VALUE						((uint16_t) 0x0FFF)

// ADC Channel
#define ADC_CHANNEL_0						((uint8_t) 0)
#define ADC_CHANNEL_1						((uint8_t) 1)
#define ADC_CHANNEL_2						((uint8_t) 2)
#define ADC_CHANNEL_3						((uint8_t) 3)
#define ADC_CHANNEL_4						((uint8_t) 4)
#define ADC_CHANNEL_5						((uint8_t) 5)
#define ADC_CHANNEL_6						((uint8_t) 6)
#define ADC_CHANNEL_7						((uint8_t) 7)
#define ADC_CHANNEL_8						((uint8_t) 8)
#define ADC_CHANNEL_9						((uint8_t) 9)

// ADC Sample Time
#define ADC_SAMPLE_1_5						((uint8_t) 0)
#define ADC_SAMPLE_7_5						((uint8_t) 1)
#define ADC_SAMPLE_13_5						((uint8_t) 2)
#define ADC_SAMPLE_28_5						((uint8_t) 3)
#define ADC_SAMPLE_41_5						((uint8_t) 4)
#define ADC_SAMPLE_55_5						((uint8_t) 5)
#define ADC_SAMPLE_71_5						((uint8_t) 6)
#define ADC_SAMPLE_239_5					((uint8_t) 7)

// ADC Final Sample Time

// Channel 0
#define ADC_SAMPLE_CH0_SMP_1_5				((uint8_t)(ADC_CHANNEL_0 << 4 | ADC_SAMPLE_1_5))
#define ADC_SAMPLE_CH0_SMP_7_5				((uint8_t)(ADC_CHANNEL_0 << 4 | ADC_SAMPLE_7_5))
#define ADC_SAMPLE_CH0_SMP_13_5				((uint8_t)(ADC_CHANNEL_0 << 4 | ADC_SAMPLE_13_5))
#define ADC_SAMPLE_CH0_SMP_28_5				((uint8_t)(ADC_CHANNEL_0 << 4 | ADC_SAMPLE_28_5))
#define ADC_SAMPLE_CH0_SMP_41_5				((uint8_t)(ADC_CHANNEL_0 << 4 | ADC_SAMPLE_41_5))
#define ADC_SAMPLE_CH0_SMP_55_5				((uint8_t)(ADC_CHANNEL_0 << 4 | ADC_SAMPLE_55_5))
#define ADC_SAMPLE_CH0_SMP_71_5				((uint8_t)(ADC_CHANNEL_0 << 4 | ADC_SAMPLE_71_5))
#define ADC_SAMPLE_CH0_SMP_239_5			((uint8_t)(ADC_CHANNEL_0 << 4 | ADC_SAMPLE_239_5))

// Channel 1
#define ADC_SAMPLE_CH0_SMP_1_5				((uint8_t)(ADC_CHANNEL_1 << 4 | ADC_SAMPLE_1_5))
#define ADC_SAMPLE_CH0_SMP_7_5				((uint8_t)(ADC_CHANNEL_1 << 4 | ADC_SAMPLE_7_5))
#define ADC_SAMPLE_CH0_SMP_13_5				((uint8_t)(ADC_CHANNEL_1 << 4 | ADC_SAMPLE_13_5))
#define ADC_SAMPLE_CH0_SMP_28_5				((uint8_t)(ADC_CHANNEL_1 << 4 | ADC_SAMPLE_28_5))
#define ADC_SAMPLE_CH0_SMP_41_5				((uint8_t)(ADC_CHANNEL_1 << 4 | ADC_SAMPLE_41_5))
#define ADC_SAMPLE_CH0_SMP_55_5				((uint8_t)(ADC_CHANNEL_1 << 4 | ADC_SAMPLE_55_5))
#define ADC_SAMPLE_CH0_SMP_71_5				((uint8_t)(ADC_CHANNEL_1 << 4 | ADC_SAMPLE_71_5))
#define ADC_SAMPLE_CH0_SMP_239_5			((uint8_t)(ADC_CHANNEL_1 << 4 | ADC_SAMPLE_239_5))

// Channel 2
#define ADC_SAMPLE_CH2_SMP_1_5				((uint8_t)(ADC_CHANNEL_2 << 4 | ADC_SAMPLE_1_5))
#define ADC_SAMPLE_CH2_SMP_7_5				((uint8_t)(ADC_CHANNEL_2 << 4 | ADC_SAMPLE_7_5))
#define ADC_SAMPLE_CH2_SMP_13_5				((uint8_t)(ADC_CHANNEL_2 << 4 | ADC_SAMPLE_13_5))
#define ADC_SAMPLE_CH2_SMP_28_5				((uint8_t)(ADC_CHANNEL_2 << 4 | ADC_SAMPLE_28_5))
#define ADC_SAMPLE_CH2_SMP_41_5				((uint8_t)(ADC_CHANNEL_2 << 4 | ADC_SAMPLE_41_5))
#define ADC_SAMPLE_CH2_SMP_55_5				((uint8_t)(ADC_CHANNEL_2 << 4 | ADC_SAMPLE_55_5))
#define ADC_SAMPLE_CH2_SMP_71_5				((uint8_t)(ADC_CHANNEL_2 << 4 | ADC_SAMPLE_71_5))
#define ADC_SAMPLE_CH2_SMP_239_5			((uint8_t)(ADC_CHANNEL_2 << 4 | ADC_SAMPLE_239_5))

// Channel 3
#define ADC_SAMPLE_CH3_SMP_1_5				((uint8_t)(ADC_CHANNEL_3 << 4 | ADC_SAMPLE_1_5))
#define ADC_SAMPLE_CH3_SMP_7_5				((uint8_t)(ADC_CHANNEL_3 << 4 | ADC_SAMPLE_7_5))
#define ADC_SAMPLE_CH3_SMP_13_5				((uint8_t)(ADC_CHANNEL_3 << 4 | ADC_SAMPLE_13_5))
#define ADC_SAMPLE_CH3_SMP_28_5				((uint8_t)(ADC_CHANNEL_3 << 4 | ADC_SAMPLE_28_5))
#define ADC_SAMPLE_CH3_SMP_41_5				((uint8_t)(ADC_CHANNEL_3 << 4 | ADC_SAMPLE_41_5))
#define ADC_SAMPLE_CH3_SMP_55_5				((uint8_t)(ADC_CHANNEL_3 << 4 | ADC_SAMPLE_55_5))
#define ADC_SAMPLE_CH3_SMP_71_5				((uint8_t)(ADC_CHANNEL_3 << 4 | ADC_SAMPLE_71_5))
#define ADC_SAMPLE_CH3_SMP_239_5			((uint8_t)(ADC_CHANNEL_3 << 4 | ADC_SAMPLE_239_5))

// Channel 4
#define ADC_SAMPLE_CH4_SMP_1_5				((uint8_t)(ADC_CHANNEL_4 << 4 | ADC_SAMPLE_1_5))
#define ADC_SAMPLE_CH4_SMP_7_5				((uint8_t)(ADC_CHANNEL_4 << 4 | ADC_SAMPLE_7_5))
#define ADC_SAMPLE_CH4_SMP_13_5				((uint8_t)(ADC_CHANNEL_4 << 4 | ADC_SAMPLE_13_5))
#define ADC_SAMPLE_CH4_SMP_28_5				((uint8_t)(ADC_CHANNEL_4 << 4 | ADC_SAMPLE_28_5))
#define ADC_SAMPLE_CH4_SMP_41_5				((uint8_t)(ADC_CHANNEL_4 << 4 | ADC_SAMPLE_41_5))
#define ADC_SAMPLE_CH4_SMP_55_5				((uint8_t)(ADC_CHANNEL_4 << 4 | ADC_SAMPLE_55_5))
#define ADC_SAMPLE_CH4_SMP_71_5				((uint8_t)(ADC_CHANNEL_4 << 4 | ADC_SAMPLE_71_5))
#define ADC_SAMPLE_CH4_SMP_239_5			((uint8_t)(ADC_CHANNEL_4 << 4 | ADC_SAMPLE_239_5))

// Channel 5
#define ADC_SAMPLE_CH5_SMP_1_5				((uint8_t)(ADC_CHANNEL_5 << 4 | ADC_SAMPLE_1_5))
#define ADC_SAMPLE_CH5_SMP_7_5				((uint8_t)(ADC_CHANNEL_5 << 4 | ADC_SAMPLE_7_5))
#define ADC_SAMPLE_CH5_SMP_13_5				((uint8_t)(ADC_CHANNEL_5 << 4 | ADC_SAMPLE_13_5))
#define ADC_SAMPLE_CH5_SMP_28_5				((uint8_t)(ADC_CHANNEL_5 << 4 | ADC_SAMPLE_28_5))
#define ADC_SAMPLE_CH5_SMP_41_5				((uint8_t)(ADC_CHANNEL_5 << 4 | ADC_SAMPLE_41_5))
#define ADC_SAMPLE_CH5_SMP_55_5				((uint8_t)(ADC_CHANNEL_5 << 4 | ADC_SAMPLE_55_5))
#define ADC_SAMPLE_CH5_SMP_71_5				((uint8_t)(ADC_CHANNEL_5 << 4 | ADC_SAMPLE_71_5))
#define ADC_SAMPLE_CH5_SMP_239_5			((uint8_t)(ADC_CHANNEL_5 << 4 | ADC_SAMPLE_239_5))

// Channel 6
#define ADC_SAMPLE_CH6_SMP_1_5				((uint8_t)(ADC_CHANNEL_6 << 4 | ADC_SAMPLE_1_5))
#define ADC_SAMPLE_CH6_SMP_7_5				((uint8_t)(ADC_CHANNEL_6 << 4 | ADC_SAMPLE_7_5))
#define ADC_SAMPLE_CH6_SMP_13_5				((uint8_t)(ADC_CHANNEL_6 << 4 | ADC_SAMPLE_13_5))
#define ADC_SAMPLE_CH6_SMP_28_5				((uint8_t)(ADC_CHANNEL_6 << 4 | ADC_SAMPLE_28_5))
#define ADC_SAMPLE_CH6_SMP_41_5				((uint8_t)(ADC_CHANNEL_6 << 4 | ADC_SAMPLE_41_5))
#define ADC_SAMPLE_CH6_SMP_55_5				((uint8_t)(ADC_CHANNEL_6 << 4 | ADC_SAMPLE_55_5))
#define ADC_SAMPLE_CH6_SMP_71_5				((uint8_t)(ADC_CHANNEL_6 << 4 | ADC_SAMPLE_71_5))
#define ADC_SAMPLE_CH6_SMP_239_5			((uint8_t)(ADC_CHANNEL_6 << 4 | ADC_SAMPLE_239_5))

// Channel 7
#define ADC_SAMPLE_CH7_SMP_1_5				((uint8_t)(ADC_CHANNEL_7 << 4 | ADC_SAMPLE_1_5))
#define ADC_SAMPLE_CH7_SMP_7_5				((uint8_t)(ADC_CHANNEL_7 << 4 | ADC_SAMPLE_7_5))
#define ADC_SAMPLE_CH7_SMP_13_5				((uint8_t)(ADC_CHANNEL_7 << 4 | ADC_SAMPLE_13_5))
#define ADC_SAMPLE_CH7_SMP_28_5				((uint8_t)(ADC_CHANNEL_7 << 4 | ADC_SAMPLE_28_5))
#define ADC_SAMPLE_CH7_SMP_41_5				((uint8_t)(ADC_CHANNEL_7 << 4 | ADC_SAMPLE_41_5))
#define ADC_SAMPLE_CH7_SMP_55_5				((uint8_t)(ADC_CHANNEL_7 << 4 | ADC_SAMPLE_55_5))
#define ADC_SAMPLE_CH7_SMP_71_5				((uint8_t)(ADC_CHANNEL_7 << 4 | ADC_SAMPLE_71_5))
#define ADC_SAMPLE_CH7_SMP_239_5			((uint8_t)(ADC_CHANNEL_7 << 4 | ADC_SAMPLE_239_5))

// Channel 8
#define ADC_SAMPLE_CH8_SMP_1_5				((uint8_t)(ADC_CHANNEL_8 << 4 | ADC_SAMPLE_1_5))
#define ADC_SAMPLE_CH8_SMP_7_5				((uint8_t)(ADC_CHANNEL_8 << 4 | ADC_SAMPLE_7_5))
#define ADC_SAMPLE_CH8_SMP_13_5				((uint8_t)(ADC_CHANNEL_8 << 4 | ADC_SAMPLE_13_5))
#define ADC_SAMPLE_CH8_SMP_28_5				((uint8_t)(ADC_CHANNEL_8 << 4 | ADC_SAMPLE_28_5))
#define ADC_SAMPLE_CH8_SMP_41_5				((uint8_t)(ADC_CHANNEL_8 << 4 | ADC_SAMPLE_41_5))
#define ADC_SAMPLE_CH8_SMP_55_5				((uint8_t)(ADC_CHANNEL_8 << 4 | ADC_SAMPLE_55_5))
#define ADC_SAMPLE_CH8_SMP_71_5				((uint8_t)(ADC_CHANNEL_8 << 4 | ADC_SAMPLE_71_5))
#define ADC_SAMPLE_CH8_SMP_239_5			((uint8_t)(ADC_CHANNEL_8 << 4 | ADC_SAMPLE_239_5))

// Channel 9
#define ADC_SAMPLE_CH9_SMP_1_5				((uint8_t)(ADC_CHANNEL_9 << 4 | ADC_SAMPLE_1_5))
#define ADC_SAMPLE_CH9_SMP_7_5				((uint8_t)(ADC_CHANNEL_9 << 4 | ADC_SAMPLE_7_5))
#define ADC_SAMPLE_CH9_SMP_13_5				((uint8_t)(ADC_CHANNEL_9 << 4 | ADC_SAMPLE_13_5))
#define ADC_SAMPLE_CH9_SMP_28_5				((uint8_t)(ADC_CHANNEL_9 << 4 | ADC_SAMPLE_28_5))
#define ADC_SAMPLE_CH9_SMP_41_5				((uint8_t)(ADC_CHANNEL_9 << 4 | ADC_SAMPLE_41_5))
#define ADC_SAMPLE_CH9_SMP_55_5				((uint8_t)(ADC_CHANNEL_9 << 4 | ADC_SAMPLE_55_5))
#define ADC_SAMPLE_CH9_SMP_71_5				((uint8_t)(ADC_CHANNEL_9 << 4 | ADC_SAMPLE_71_5))
#define ADC_SAMPLE_CH9_SMP_239_5			((uint8_t)(ADC_CHANNEL_9 << 4 | ADC_SAMPLE_239_5))

// ADC Continuous Conversion
#define ADC_CONT_CONV_OFF					((uint8_t) 0)
#define ADC_CONT_CONV_ON					((uint8_t) 1)

// ADC Data Alignment
#define ADC_DATA_ALIGN_RIGHT				((uint8_t) 0)
#define ADC_DATA_ALIGN_LEFT					((uint8_t) 1)

// ADC Sample Time Channel Decoding
#define ADC_SAMPLE_CHANNEL(ADC_SAMPLEx)		((uint8_t)(((ADC_SAMPLEx) & 0xF0) >> 4))
// ADC Sample Time Decoding
#define ADC_SAMPLE_TIME(ADC_SAMPLEx)		((uint8_t)((ADC_SAMPLEx) & 0x0F))
/*********************************************** ADC MACROS ***********************************************/

#endif  /* __REG_MAP_H__ */
