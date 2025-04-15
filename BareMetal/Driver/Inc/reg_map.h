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

/*********************************************** Custom Declaration ***********************************************/
#define NULL            					((void *) 0)
#define __INLINE__							__attribute__((always_inline)) inline
#define __STATIC_INLINE__					static __attribute__((always_inline)) inline
/*********************************************** Custom Declaration ***********************************************/

/*********************************************** ARM CORTEX M3 ***********************************************/
#include "flash_reg_map.h"
#include "nvic_reg_map.h"
#include "systick_reg_map.h"
#include "wwdg_reg_map.h"
/*********************************************** ARM CORTEX M3 ***********************************************/

/*********************************************** STM32F103C8T6 ***********************************************/
#include "adc_reg_map.h"
#include "advtim_reg_map.h"
#include "afio_reg_map.h"
#include "dma_reg_map.h"
#include "exti_reg_map.h"
#include "gpio_reg_map.h"
#include "i2c_reg_map.h"
#include "timer_reg_map.h"
#include "rcc_reg_map.h"
#include "usart_reg_map.h"
/*********************************************** STM32F103C8T6 ***********************************************/

/*********************************************** Address Mapping ***********************************************/
// Memory Mapping
#define SysTick_BASE_ADDR					((uint32_t) 0xE000E010)
#define NVIC_BASE_ADDR						((uint32_t) 0xE000E100)
#define APB1_BASE_ADDR						((uint32_t) 0x40000000)
#define APB2_BASE_ADDR						((uint32_t) 0x40010000)
#define AHB_BASE_ADDR						((uint32_t) 0x40018000)
#define FLASH_BASE_ADDR						((uint32_t) 0x40022000)
#define DMA1_BASE_ADDR						((uint32_t) (AHB_BASE_ADDR + 0x00008000))
#define DMA2_BASE_ADDR						((uint32_t) (DMA1_BASE_ADDR + 0x00000400))

// Address Mapping
#define SysTick								((SYSTICK_REG_STRUCT *)(SysTick_BASE_ADDR))
#define NVIC								((NVIC_REG_STRUCT *)(NVIC_BASE_ADDR))
#define FLASH								((FLASH_REG_STRUCT *)(FLASH_BASE_ADDR))
#define WWDG								((WWDG_REG_STRUCT *) (APB1_BASE_ADDR + 0x00002C00))
#define RCC                     			((RCC_REG_STRUCT *)(AHB_BASE_ADDR + 0x00009000))
#define GPIOA								((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + 0x00000800))
#define GPIOB								((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + 0x00000C00))
#define GPIOC								((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + 0x00001000))
#define GPIOD								((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + 0x00001400))
#define GPIOE								((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + 0x00001800))
#define GPIOF								((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + 0x00001C00))
#define GPIOG								((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + 0x00002000))
#define AFIO								((AFIO_REG_STRUCT *)(APB2_BASE_ADDR))
#define TIM1								((ADV_TIM_REG_STRUCT *)(APB2_BASE_ADDR + 0x00002C00))
#define TIM2								((TIM_REG_STRUCT *)(APB1_BASE_ADDR + 0x00000000))
#define TIM3								((TIM_REG_STRUCT *)(APB1_BASE_ADDR + 0x00000400))
#define TIM4								((TIM_REG_STRUCT *)(APB1_BASE_ADDR + 0x00000800))
#define TIM5								((TIM_REG_STRUCT *)(APB1_BASE_ADDR + 0x00000C00))
#define TIM6								((TIM_REG_STRUCT *)(APB1_BASE_ADDR + 0x00001000))
#define TIM7								((TIM_REG_STRUCT *)(APB1_BASE_ADDR + 0x00001400))
#define TIM8								((ADV_TIM_REG_STRUCT *)(APB2_BASE_ADDR + 0x00003400))
#define ADC1								((ADC_REG_STRUCT *)(APB2_BASE_ADDR + 0x00002400))
#define ADC2								((ADC_REG_STRUCT *)(APB2_BASE_ADDR + 0x00002800))
#define ADC3								((ADC_REG_STRUCT *)(APB2_BASE_ADDR + 0x00003C00))
#define USART1								((USART_REG_STRUCT *)(APB2_BASE_ADDR + 0x00003800))
#define USART2								((USART_REG_STRUCT *)(APB1_BASE_ADDR + 0x00004400))
#define USART3								((USART_REG_STRUCT *)(APB1_BASE_ADDR + 0x00004800))
#define EXTI								((EXTI_REG_STRUCT*)(APB2_BASE_ADDR + 0x00000400))
#define I2C1								((I2C_REG_STRUCT *)(APB1_BASE_ADDR + 0x00005400))
#define I2C2								((I2C_REG_STRUCT *)(APB1_BASE_ADDR + 0x00005800))
#define DMA1								((DMA_REG_STRUCT *) DMA1_BASE_ADDR)
#define DMA1_Channel1						((DMA_CHANNEL_REG_STRUCT *) (DMA1_BASE_ADDR + 0x00000008))
#define DMA1_Channel2						((DMA_CHANNEL_REG_STRUCT *) (DMA1_BASE_ADDR + 0x0000001C))
#define DMA1_Channel3						((DMA_CHANNEL_REG_STRUCT *) (DMA1_BASE_ADDR + 0x00000030))
#define DMA1_Channel4						((DMA_CHANNEL_REG_STRUCT *) (DMA1_BASE_ADDR + 0x00000044))
#define DMA1_Channel5						((DMA_CHANNEL_REG_STRUCT *) (DMA1_BASE_ADDR + 0x00000058))
#define DMA1_Channel6						((DMA_CHANNEL_REG_STRUCT *) (DMA1_BASE_ADDR + 0x0000006C))
#define DMA1_Channel7						((DMA_CHANNEL_REG_STRUCT *) (DMA1_BASE_ADDR + 0x00000080))
#define DMA2								((DMA_REG_STRUCT *) DMA2_BASE_ADDR)
#define DMA2_Channel1						((DMA_CHANNEL_REG_STRUCT *) (DMA2_BASE_ADDR + 0x00000008))
#define DMA2_Channel2						((DMA_CHANNEL_REG_STRUCT *) (DMA2_BASE_ADDR + 0x0000001C))
#define DMA2_Channel3						((DMA_CHANNEL_REG_STRUCT *) (DMA2_BASE_ADDR + 0x00000030))
#define DMA2_Channel4						((DMA_CHANNEL_REG_STRUCT *) (DMA2_BASE_ADDR + 0x00000044))
#define DMA2_Channel5						((DMA_CHANNEL_REG_STRUCT *) (DMA2_BASE_ADDR + 0x00000058))
/*********************************************** Address Mapping ***********************************************/

/*********************************************** GPIO MACROS ***********************************************/
// Generic
#define BIT_SET								((uint8_t) 0x01)
#define BIT_RESET							((uint8_t) 0x00)

// GPIO PIN
#define GPIOx_PIN_0							((uint8_t) 0)
#define GPIOx_PIN_1							((uint8_t) 1)
#define GPIOx_PIN_2							((uint8_t) 2)
#define GPIOx_PIN_3							((uint8_t) 3)
#define GPIOx_PIN_4							((uint8_t) 4)
#define GPIOx_PIN_5							((uint8_t) 5)
#define GPIOx_PIN_6							((uint8_t) 6)
#define GPIOx_PIN_7							((uint8_t) 7)
#define GPIOx_PIN_8							((uint8_t) 8)
#define GPIOx_PIN_9							((uint8_t) 9)
#define GPIOx_PIN_10						((uint8_t) 10)
#define GPIOx_PIN_11						((uint8_t) 11)
#define GPIOx_PIN_12						((uint8_t) 12)
#define GPIOx_PIN_13						((uint8_t) 13)
#define GPIOx_PIN_14						((uint8_t) 14)
#define GPIOx_PIN_15						((uint8_t) 15)
#define OB_LED_PORT							(GPIOC)
#define OB_LED_PIN							(GPIOx_PIN_13)

// MODE
#define GPIOx_MODE_IN						((uint8_t) 0)
#define GPIOx_MODE_OUT_10MHz				((uint8_t) 1)
#define GPIOx_MODE_OUT_2MHz					((uint8_t) 2)
#define GPIOx_MODE_OUT_50MHz				((uint8_t) 3)

// CONFIGURATION
#define GPIOx_CNF_IN_ANALOG					((uint8_t) 0)
#define GPIOx_CNF_IN_FLOAT					((uint8_t) 1)
#define GPIOx_CNF_IN_PD						((uint8_t) 3)
#define GPIOx_CNF_IN_PU						((uint8_t) 4)
#define GPIOx_CNF_OUT_GP_PP					((uint8_t) 0)
#define GPIOx_CNF_OUT_GP_OD					((uint8_t) 1)
#define GPIOx_CNF_OUT_AF_PP					((uint8_t) 2)
#define GPIOx_CNF_OUT_AF_OD					((uint8_t) 3)

// Error Checking MACROS
#define IS_VALID_GPIO(GPIO) 				((GPIO) == GPIOA || (GPIO) == GPIOB || (GPIO) == GPIOC || (GPIO) == NULL)
#define IS_VALID_PIN(PIN) 					((PIN) <= GPIOx_PIN_15)
#define IS_MODE_VALID(MODE)				((MODE) == GPIOx_MODE_IN || (MODE) == GPIOx_MODE_OUT_10MHz || (MODE) == GPIOx_MODE_OUT_2MHz || (MODE) == GPIOx_MODE_OUT_50MHz)
#define IS_CNF_VALID(CNF)					((CNF) == GPIOx_CNF_IN_ANALOG || (CNF) == GPIOx_CNF_IN_FLOAT || (CNF) == GPIOx_CNF_IN_PD || (CNF) == GPIOx_CNF_IN_PU || \
											 (CNF) == GPIOx_CNF_OUT_GP_PP || (CNF) == GPIOx_CNF_OUT_GP_OD || (CNF) == GPIOx_CNF_OUT_AF_PP || (CNF) == GPIOx_CNF_OUT_AF_OD)
#define ARE_GPIO_PARAMETERS_VALID(GPIO, PIN, MODE, CNF)	\
											(IS_VALID_GPIO((GPIO)) && \
											 IS_VALID_PIN((PIN)) && \
											 IS_MODE_VALID((MODE)) && \
											 IS_CNF_VALID((CNF)))
#define IS_MODE_IN_VALID(MODE, CNF)		(((MODE) == GPIOx_MODE_IN && (CNF) == GPIOx_CNF_IN_ANALOG) || ((MODE) == GPIOx_MODE_IN && (CNF) == GPIOx_CNF_IN_FLOAT) || \
											 ((MODE) == GPIOx_MODE_IN && (CNF) == GPIOx_CNF_IN_PD) || ((MODE) == GPIOx_MODE_IN && (CNF) == GPIOx_CNF_IN_PU))
#define IS_MODE_OUT_VALID(MODE, CNF)		(((MODE) != GPIOx_MODE_IN && (CNF) == GPIOx_CNF_OUT_GP_PP) || ((MODE) != GPIOx_MODE_IN && (CNF) == GPIOx_CNF_OUT_GP_OD) || \
											 ((MODE) != GPIOx_MODE_IN && (CNF) == GPIOx_CNF_OUT_AF_PP) || ((MODE) != GPIOx_MODE_IN && (CNF) == GPIOx_CNF_OUT_AF_OD))
#define IS_MODE_CNF_VALID(MODE, CNF)		(IS_MODE_IN_VALID((MODE), (CNF)) || IS_MODE_OUT_VALID((MODE), (CNF)))
#define IS_GPIO_STRUCTURE_VALID(GPIO_CONFIGx)	\	
											(((GPIO_CONFIGx) == NULL) || (\
											 IS_VALID_GPIO(GPIO_CONFIGx->GPIO) && \
											 IS_VALID_PIN(GPIO_CONFIGx->PIN) && \
											 IS_MODE_VALID(GPIO_CONFIGx->MODE) && \
											 IS_CNF_VALID(GPIO_CONFIGx->CNF) && \
											 IS_MODE_CNF_VALID(GPIO_CONFIGx->MODE, GPIO_CONFIGx->CNF)))

/*********************************************** GPIO MACROS ***********************************************/

/*********************************************** RCC MACROS ***********************************************/
// Generic Frequencies
#define FREQ_12Hz							((uint32_t) 12)   
#define FREQ_25Hz							((uint32_t) 25)   
#define FREQ_50Hz							((uint32_t) 50)   
#define FREQ_100Hz							((uint32_t) 100)   
#define FREQ_500Hz							((uint32_t) 500)   
#define FREQ_1kHz							((uint32_t) 1000)   
#define FREQ_2kHz							((uint32_t) 2000)   
#define FREQ_5kHz							((uint32_t) 5000)   
#define FREQ_10kHz							((uint32_t) 10000)   
#define FREQ_50kHz							((uint32_t) 50000)   
#define FREQ_72kHz							((uint32_t) 72000)   
#define FREQ_100kHz							((uint32_t) 100000)   
#define FREQ_200kHz							((uint32_t) 200000) 
#define FREQ_1MHz							((uint32_t) 1000000)
#define FREQ_10MHz							((uint32_t) 10000000)

// Clock Speed
#define HSI_FREQ							((uint32_t) 8000000)
#define HSE_FREQ							((uint32_t) 8000000)
#define PLL_MIN_FREQ						((uint32_t) 16000000)
#define PLL_MAX_FREQ						((uint32_t) 72000000)

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
#define PLL_MUL_16							((uint8_t) 0x0E)

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

// Advanced High Performance Bus (AHB) Frequency
static volatile uint32_t CoreClock = HSI_FREQ;
// Advanced High Performance Bus (AHB) Frequency
static volatile uint32_t AHBClock = HSI_FREQ;
// Advanced Peripheral Bus 1 (APB1) Frequency
static volatile uint32_t APB1Clock = HSI_FREQ;
// Advanced Peripheral Bus 2 (APB2) Frequency
static volatile uint32_t APB2Clock = HSI_FREQ;
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
#define DMA1_Channel1_IRQn					((uint8_t) 11)
#define DMA1_Channel2_IRQn					((uint8_t) 12)
#define DMA1_Channel3_IRQn					((uint8_t) 13)
#define DMA1_Channel4_IRQn					((uint8_t) 14)
#define DMA1_Channel5_IRQn					((uint8_t) 15)
#define DMA1_Channel6_IRQn					((uint8_t) 16)
#define DMA1_Channel7_IRQn					((uint8_t) 17)
#define ADC1_2_IRQn							((uint8_t) 18)
#define EXTI9_5_IRQn						((uint8_t) 23)
#define TIM2_IRQn							((uint8_t) 28)
#define TIM3_IRQn							((uint8_t) 29)
#define TIM4_IRQn							((uint8_t) 30)
#define I2C1_EV_IRQn						((uint8_t) 31)
#define I2C1_ER_IRQn						((uint8_t) 32)
#define I2C2_EV_IRQn						((uint8_t) 33)
#define I2C2_ER_IRQn						((uint8_t) 34)
#define SPI1_IRQn							((uint8_t) 35)
#define SPI2_IRQn							((uint8_t) 36)
#define USART1_IRQn							((uint8_t) 37)
#define USART2_IRQn							((uint8_t) 38)
#define USART3_IRQn							((uint8_t) 39)
#define EXTI15_10_IRQn						((uint8_t) 40)
#define ADC3_IRQn							((uint8_t) 47)
#define DMA2_Channel1_IRQn					((uint8_t) 56)
#define DMA2_Channel2_IRQn					((uint8_t) 57)
#define DMA2_Channel3_IRQn					((uint8_t) 58)
#define DMA2_Channel4_5_IRQn				((uint8_t) 59)
/*********************************************** NVIC MACROS ***********************************************/

/*********************************************** EXTI MACROS ***********************************************/
// External Trigger Selection
#define EXTI_TRIG_FALLING					((uint8_t) 0x00)
#define EXTI_TRIG_RISING					((uint8_t) 0x01)
#define EXTI_TRIG_BOTH						((uint8_t) 0x02)

// AF EXTI
#define AF_EXTI_PA							((uint8_t) 0x00)
#define AF_EXTI_PB							((uint8_t) 0x01)
#define AF_EXTI_PC							((uint8_t) 0x02)
#define AF_EXTI_PD							((uint8_t) 0x03)
#define AF_EXTI_PE							((uint8_t) 0x04)
#define AF_EXTI_PF							((uint8_t) 0x05)
#define AF_EXTI_PG							((uint8_t) 0x06)

// Error Checking MACROs
#define IS_EXTI_TRIG_VALID(TRIGx)			(((TRIGx) == EXTI_TRIG_FALLING) \
											 || ((TRIGx) == EXTI_TRIG_RISING) \
											 || ((TRIGx) == EXTI_TRIG_BOTH))
#define IS_EXTI_IRQn_VALID(IRQn)			((IRQn) < 60)
#define IS_EXTI_STRUCTURE_VALID(EXTI_CONFIGx)	\
											((IS_GPIO_STRUCTURE_VALID(EXTI_CONFIGx->GPIO_CONFIGx) )&& \
											 (IS_EXTI_TRIG_VALID(EXTI_CONFIGx->TRIGx)) && \
											 (IS_EXTI_IRQn_VALID(EXTI_CONFIGx->IRQn)) && \
											 (EXTI_CONFIGx->GPIO_CONFIGx->MODE == GPIOx_MODE_IN))
								 
/*********************************************** EXTI MACROS ***********************************************/

/*********************************************** I2C MACROS ***********************************************/
// I2C Speed
#define I2Cx_SPEED_STD						(FREQ_100kHz)		// Sm
#define I2Cx_SPEED_FAST						(4 * FREQ_100kHz)	// Fm
// I2C Configuration Structure SCL Clock Freq
#define I2Cx_SCL_FREQ_4MHz					((uint8_t) 0x04)
#define I2Cx_SCL_FREQ_8MHz					((uint8_t) 0x08)
#define I2Cx_SCL_FREQ_16MHz					((uint8_t) 0x10)
#define I2Cx_SCL_FREQ_32MHz					((uint8_t) 0x20)
#define I2Cx_SCL_FREQ_DEFAULT				(APB1Clock)
// I2C Configuration Structure Mode
#define I2Cx_MODE_STD						((uint8_t) 0x00)
#define I2Cx_MODE_FAST						((uint8_t) 0x01)
// I2C Configuration Structure Buffer Interrupt
#define I2Cx_BUFFER_IRQ_DISABLE				((uint8_t) 0x00)
#define I2Cx_BUFFER_IRQ_ENABLE				((uint8_t) 0x01)
// I2C Configuration Structure Event Interrupt
#define I2Cx_EVENT_IRQ_DISABLE				((uint8_t) 0x00)
#define I2Cx_EVENT_IRQ_ENABLE				((uint8_t) 0x01)
// I2C Configuration Structure Fast Mode Duty
#define I2Cx_DUTY_NORMAL					((uint8_t) 0x00)
#define I2Cx_DUTY_FAST						((uint8_t) 0x01)
// I2C Read/Write
#define I2Cx_WRITE							((uint8_t) 0x00)
#define I2Cx_READ							((uint8_t) 0x01)
/*********************************************** I2C MACROS ***********************************************/

/*********************************************** SysTick MACROS ***********************************************/
// SysTick Clock Selection
#define SYSTICK_CLK_EXT						((uint8_t) 0x00)
#define SYSTICK_CLK_CORE					((uint8_t) 0x01)

// SysTick Delay
#define SYSTICK_DELAY_1_MS					((uint32_t)(AHBClock/1000))
#define SYSTICK_DELAYS_2_MS					((uint32_t)(2 * SYSTICK_DELAY_1_MS))
/*********************************************** SysTick MACROS ***********************************************/

/*********************************************** TIMER MACROS ***********************************************/
// Centre-align Mode Selection
#define TIMx_CMS_EDGE						((uint8_t) 0x00)
#define TIMx_CMS_IF_DOWN					((uint8_t) 0x01)
#define TIMx_CMS_IF_UP						((uint8_t) 0x02)
#define TIMx_CMS_IF_BOTH					((uint8_t) 0x03)

// Clock Division
#define TIMx_CKD_CLK_FREQ					((uint8_t) 0x00)
#define TIMx_CKD_CLK_2_FREQ					((uint8_t) 0x01)
#define TIMx_CKD_CLK_4_FREQ					((uint8_t) 0x02)

// Master Mode Selection
#define TIMx_MMS_RESET						((uint8_t) 0x00)
#define TIMx_MMS_ENABLE						((uint8_t) 0x01)
#define TIMx_MMS_UPDATE						((uint8_t) 0x02)
#define TIMx_MMS_CMP_PULSE					((uint8_t) 0x03)
#define TIMx_MMS_CMP_OC1REF					((uint8_t) 0x04)
#define TIMx_MMS_CMP_OC2REF					((uint8_t) 0x05)
#define TIMx_MMS_CMP_OC3REF					((uint8_t) 0x06)
#define TIMx_MMS_CMP_OC4REF					((uint8_t) 0x07)

// Slave Mode Selection
#define TIMx_SMS_DISABLE					((uint8_t) 0x00)
#define TIMx_SMS_ENC_MODE1					((uint8_t) 0x01)
#define TIMx_SMS_ENC_MODE2					((uint8_t) 0x02)
#define TIMx_SMS_ENC_MODE3					((uint8_t) 0x03)

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
// "Up" if DIR = 0; "Down" if DIR = 1
#define TIMx_MODE_NORMAL					((uint8_t) 0x00)
#define TIMx_MODE_ALT_IF_DOWN				((uint8_t) 0x01)
#define TIMx_MODE_ALT_IF_UP					((uint8_t) 0x02)
#define TIMx_MODE_ALT_IF_BOTH				((uint8_t) 0x03)

// Direction 
#define TIMx_DIR_COUNT_UP					((uint8_t) 0x00)
#define TIMx_DIR_COUNT_DOWN					((uint8_t) 0x01)

// Auto Reload Preload Enable
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
#define IS_VALID_TIM_CHANNEL(CHx)			(((CHx) & ~(TIMx_CHANNEL_1 | TIMx_CHANNEL_2 | TIMx_CHANNEL_3 | TIMx_CHANNEL_4)) == ((uint8_t)0x00))
#define IS_VALID_TIM_CMS_MODE(MODE)		((MODE) == CMS_EDGE || (MODE) == CMS_IF_BOTH || (MODE) == CMS_IF_DOWN || (MODE) == CMS_IF_UP)
#define IS_VALID_TIM_DIRECTION(DIRx)		((DIRx) == TIMx_COUNT_UP || (DIRx) == TIMx_COUNT_DOWN)
#define IS_VALID_TIM_COUNT_MODE(MODE)		((MODE) == TIMx_MODE_NORMAL || (MODE) == TIMx_MODE_ALT_IF_DOWN || \
											 (MODE) == TIMx_MODE_ALT_IF_UP || (MODE) == TIMx_MODE_ALT_IF_BOTH)
#define IS_VALID_TIM_ARR(ARRx)				(((ARRx) >= (uint16_t)0x00) && ((ARRx) < (uint16_t)0xFFFF))
#define IS_VALID_TIM_FREQ(FREQx)			(((FREQx) > (uint32_t)0x00) && ((FREQx) <= PLL_MAX_FREQ))
#define IS_VALID_TIM_CNT(CNTx)				(((CNTx) >= (uint16_t)0x00) && ((CNTx) <= (uint16_t)0xFFFF))
#define IS_VALID_TIM_ARPE(ARPEx)			((ARPEx) == TIMx_ARPE_DISABLE || ((ARPEx) == TIMx_ARPE_ENABLE))
#define IS_VALID_TIM_OPM(OPMx)				((OPMx) == TIMx_OPM_DISABLE || ((OPMx) == TIMx_OPM_ENABLE))
#define IS_VALID_TIM_IRQ(IRQx)				(((IRQx) == TIMx_IRQ_ENABLE) || ((IRQx) == TIMx_IRQ_DISABLE))
#define IS_VALID_TIM_CONFIG_STRUCT(TIM_CONFIGx) \
											(IS_GPIO_STRUCTURE_VALID(TIM_CONFIGx->GPIO_CONFIGx) && \
											 IS_VALID_GPT((TIM_CONFIGx->GP_TIMx)) && \
											 IS_VALID_TIM_CHANNEL((TIM_CONFIGx->channel)) && \
											 IS_VALID_TIM_ARR((TIM_CONFIGx->auto_reload_value)) && \
											 IS_VALID_TIM_FREQ((TIM_CONFIGx->frequency_Hz)) && \
											 IS_VALID_TIM_CNT((TIM_CONFIGx->count)) && \
											 IS_VALID_TIM_CMS_MODE((TIM_CONFIGx->cms_mode)) && \
											 IS_VALID_TIM_DIRECTION((TIM_CONFIGx->direction)) && \
											 IS_VALID_TIM_ARPE((TIM_CONFIGx->auto_reload_preload)) && \
											 IS_VALID_TIM_OPM((TIM_CONFIGx->one_pulse)))									 
/*********************************************** TIMER MACROS ***********************************************/

/*********************************************** PWM MACROS ***********************************************/
// IMP: Store this value in ARR always to simplify the PWM calculation
#define DEFAULT_CNT_VALUE					((uint16_t) 0)
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
#define IS_VALID_PWM_MODE(MODE)			((MODE) == TIMx_OCM_FREEZE || (MODE) == TIMx_OCM_SET_CH || \
											 (MODE) == TIMx_OCM_RESET_CH || (MODE) == TIMx_OCM_TOGGLE || \
											 (MODE) == TIMx_OCM_FORCE_RESET || (MODE) == TIMx_OCM_FORCE_SET || \
											 (MODE) == TIMx_OCM_PWM_NORMAL || (MODE) == TIMx_OCM_PWM_INVERTED)
#define IS_VALID_PWM_POLARITY(POLx)			((POLx) == TIMx_POL_ACTIVE_HIGH || (POLx) == TIMx_POL_ACTIVE_LOW)
#define IS_VALID_PWM_DUTY_CYCLE(DUTYx)		((DUTYx) >= MIN_DUTY_CYCLE && (DUTYx) <= MAX_DUTY_CYCLE)
#define IS_VALID_PWM_CHANNEL_PRELOAD(CH_PRx)(((CH_PRx) == PWM_CHx_PRELOAD_DISABLE) || ((CH_PRx) == PWM_CHx_PRELOAD_ENABLE))
#define IS_VALID_PWM_CONFIG_STRUCT(PWM_CONFIGx) \
											(IS_VALID_TIM_CONFIG_STRUCT(PWM_CONFIGx->TIM_CONFIGx) && \
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

/*
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
*/

// ADC Continuous Conversion
#define ADC_CONT_CONV_OFF					((uint8_t) 0)
#define ADC_CONT_CONV_ON					((uint8_t) 1)

// ADC Data Alignment
#define ADC_DATA_ALIGN_RIGHT				((uint8_t) 0)
#define ADC_DATA_ALIGN_LEFT					((uint8_t) 1)

// ADC IRQ
#define ADCx_IRQ_DISABLE					((uint8_t) 0)
#define ADCx_IRQ_ENABLE						((uint8_t) 1)

// ADC Sample Time Channel Decoding
#define ADC_SAMPLE_CHANNEL(ADC_SAMPLEx)		((uint8_t)(((ADC_SAMPLEx) & 0xF0) >> 4))
// ADC Sample Time Decoding
#define ADC_SAMPLE_TIME(ADC_SAMPLEx)		((uint8_t)((ADC_SAMPLEx) & 0x0F))

// Error Checking MACROS
#define IS_VALID_ADC_CHANNEL(CHx)			(((CHx) == ADC_CHANNEL_0) || ((CHx) == ADC_CHANNEL_1) || \
											 ((CHx) == ADC_CHANNEL_2) || ((CHx) == ADC_CHANNEL_3) || \
											 ((CHx) == ADC_CHANNEL_4) || ((CHx) == ADC_CHANNEL_5) || \
											 ((CHx) == ADC_CHANNEL_6) || ((CHx) == ADC_CHANNEL_7) || \
											 ((CHx) == ADC_CHANNEL_8) || ((CHx) == ADC_CHANNEL_9))		
/*********************************************** ADC MACROS ***********************************************/

/*********************************************** USART MACROS ***********************************************/
// TX
#define USARTx_TX_DISABLE					((uint8_t) 0x00)
#define USARTx_TX_ENABLE					((uint8_t) 0x01)

// RX
#define USARTx_RX_DISABLE					((uint8_t) 0x00)
#define USARTx_RX_ENABLE					((uint8_t) 0x01)

// TX Empty IRQ
#define USARTx_TXEIE_DISABLE				((uint8_t) 0x00) 
#define USARTx_TXEIE_ENABLE					((uint8_t) 0x01)

// RX Not Empty IRQ
#define USARTx_RXNEIE_DISABLE				((uint8_t) 0x00) 
#define USARTx_RXNEIE_ENABLE				((uint8_t) 0x01)

// TX Complete IRQ
#define USARTx_TCIE_DISABLE					((uint8_t) 0x00)
#define USARTx_TCIE_ENABLE					((uint8_t) 0x01)

// Parity Control
#define USARTx_PARITY_DISABLE				((uint8_t) 0x00)
#define USARTx_PARITY_ENABLE				((uint8_t) 0x01)

// Word Length
#define USARTx_WORD_8_BITS					((uint8_t) 0x00)
#define USARTx_WORD_9_BITS					((uint8_t) 0x01)

// Stop Bits
#define USARTx_STOP_1_BIT					((uint8_t) 0x00)
#define USARTx_STOP_0_5_BITS				((uint8_t) 0x01)
#define USARTx_STOP_2_BITS					((uint8_t) 0x02)
#define USARTx_STOP_1_5_BITS				((uint8_t) 0x03)

// Parity Mode
#define USARTx_PARITY_EVEN					((uint8_t) 0x00)
#define USARTx_PARITY_ODD					((uint8_t) 0x01)

// Baud Rate
#define USARTx_BAUD_4800					((uint16_t) 4800)
#define USARTx_BAUD_9600					((uint16_t) 9600)
#define USARTx_BAUD_115200					((uint16_t) 115200)

// Local Delay
#define USARTx_STRING_TX_DELAY				((uint16_t) 3000)
/*********************************************** USART MACROS ***********************************************/

/*********************************************** DMA MACROS ***********************************************/
// Reading Direction
#define DMAx_DIR_MEM2MEM					((uint8_t) 0x00)
#define DMAx_DIR_PER2MEM					((uint8_t) 0x01)

// Memory to Memory Transfer
#define DMAx_MEM2MEM_DISABLE				((uint8_t) 0x00)
#define DMAx_MEM2MEM_ENABLE					((uint8_t) 0x01)

// Circular Mode
#define DMAx_CIRC_DISABLE					((uint8_t) 0x00)
#define DMAx_CIRC_ENABLE					((uint8_t) 0x01)

// Priority Level
#define DMAx_PRIORITY_LOW 					((uint8_t) 0x00)
#define DMAx_PRIORITY_MEDIUM 				((uint8_t) 0x01)
#define DMAx_PRIORITY_HIGH	 				((uint8_t) 0x02)
#define DMAx_PRIORITY_VERY_HIGH	 			((uint8_t) 0x03)

// Address Increment
#define DMAx_INC_DISABLE					((uint8_t) 0x00)
#define DMAx_INC_ENABLE						((uint8_t) 0x01)

// DMA Data Size for Transfer
#define DMAx_DATA_SIZE_BIT_8				((uint8_t) 0x00)
#define DMAx_DATA_SIZE_BIT_16				((uint8_t) 0x01)
#define DMAx_DATA_SIZE_BIT_32				((uint8_t) 0x02)

// Interrupts
#define DMAx_IRQ_DISABLE					((uint8_t) 0x00)
#define DMAx_IRQ_ENABLE						((uint8_t) 0x01)

// DMA Channel 6
#define DMA_USART2_RX						(DMA1_Channel6)
#define DMA_I2C1_TX							(DMA1_Channel6)
#define DMA_TIM1_CH3						(DMA1_Channel6)
#define DMA_TIM3_CH1						(DMA1_Channel6)
#define DMA_TIM3_TRIG						(DMA1_Channel6)

// DMA Channel 7
#define DMA_USART2_TX						(DMA1_Channel7)
#define DMA_I2C1_RX							(DMA1_Channel7)
#define DMA_TIM2_CH2						(DMA1_Channel7)
#define DMA_TIM2_CH4						(DMA1_Channel7)
#define DMA_TIM4_UP							(DMA1_Channel7)

/*********************************************** DMA MACROS ***********************************************/

#endif  /* __REG_MAP_H__ */
