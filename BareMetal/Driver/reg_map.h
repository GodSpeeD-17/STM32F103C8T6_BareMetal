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
#define __IO								volatile
/*********************************************** Custom Declaration ***********************************************/

/*********************************************** ARM CORTEX M3 ***********************************************/
#include "arm_reg_map.h"
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
#define SysTick_BASE_ADDR					0xE000E010
#define NVIC_BASE_ADDR						0xE000E100
#define CPU_ID_BASE_ADDR					0xE000ED00
#define APB1_BASE_ADDR						0x40000000
#define APB2_BASE_ADDR						0x40010000
#define AHB_BASE_ADDR						0x40018000
#define FLASH_BASE_ADDR						0x40022000
#define DMA1_BASE_ADDR						(AHB_BASE_ADDR + 0x00008000)
#define DMA2_BASE_ADDR						(DMA1_BASE_ADDR + 0x00000400)

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
#define BIT_SET								(0x01)
#define BIT_RESET							(0x00)

// GPIO PIN
#define GPIOx_PIN_0							(0x00)
#define GPIOx_PIN_1							(0x01)
#define GPIOx_PIN_2							(0x02)
#define GPIOx_PIN_3							(0x03)
#define GPIOx_PIN_4							(0x04)
#define GPIOx_PIN_5							(0x05)
#define GPIOx_PIN_6							(0x06)
#define GPIOx_PIN_7							(0x07)
#define GPIOx_PIN_8							(0x08)
#define GPIOx_PIN_9							(0x09)
#define GPIOx_PIN_10						(0x0A)
#define GPIOx_PIN_11						(0x0B)
#define GPIOx_PIN_12						(0x0C)
#define GPIOx_PIN_13						(0x0D)
#define GPIOx_PIN_14						(0x0E)
#define GPIOx_PIN_15						(0x0F)
#define OB_LED_PORT							(GPIOC)
#define OB_LED_PIN							(GPIOx_PIN_13)

// MODE
#define GPIOx_MODE_IN						(0x00)
#define GPIOx_MODE_OUT_10MHz				(0x01)
#define GPIOx_MODE_OUT_2MHz					(0x02)
#define GPIOx_MODE_OUT_50MHz				(0x03)

// CONFIGURATION
#define GPIOx_CNF_IN_ANALOG					(0x00)
#define GPIOx_CNF_IN_FLOAT					(0x01)
#define GPIOx_CNF_IN_PD						(0x03)
#define GPIOx_CNF_IN_PU						(0x04)
#define GPIOx_CNF_OUT_GP_PP					(0x00)
#define GPIOx_CNF_OUT_GP_OD					(0x01)
#define GPIOx_CNF_OUT_AF_PP					(0x02)
#define GPIOx_CNF_OUT_AF_OD					(0x03)

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
#define RCCx_SW_CLK_HSI						(0x00)
#define RCCx_SW_CLK_HSE						(0x01)
#define RCCx_SW_CLK_PLL						(0x02)

// AHB Prescaler
#define RCCx_AHB_DIV_1						(0x00)
#define RCCx_AHB_DIV_2						(0x08)
#define RCCx_AHB_DIV_4						(0x09)
#define RCCx_AHB_DIV_8						(0x0A)
#define RCCx_AHB_DIV_16						(0x0B)
#define RCCx_AHB_DIV_64						(0x0C)
#define RCCx_AHB_DIV_128					(0x0D)
#define RCCx_AHB_DIV_256					(0x0E)
#define RCCx_AHB_DIV_512					(0x0F)

// APB1 Prescaler
#define RCCx_APB1_DIV_1						(0x03)
#define RCCx_APB1_DIV_2						(0x04)
#define RCCx_APB1_DIV_4						(0x05)
#define RCCx_APB1_DIV_8						(0x06)
#define RCCx_APB1_DIV_16					(0x07)

// APB2 Prescaler
#define RCCx_APB2_DIV_1						(0x03)
#define RCCx_APB2_DIV_2						(0x04)
#define RCCx_APB2_DIV_4						(0x05)
#define RCCx_APB2_DIV_8						(0x06)
#define RCCx_APB2_DIV_16					(0x07)

// ADC Prescaler
#define RCCx_ADC_DIV_2						(0x00)
#define RCCx_ADC_DIV_4						(0x01)
#define RCCx_ADC_DIV_6						(0x02)
#define RCCx_ADC_DIV_8						(0x03)

// PLL Clock Source
#define RCCx_PLL_SRC_HSI_DIV_2				(0x00)
#define RCCx_PLL_SRC_HSE_DIV_1				(0x01)
#define RCCx_PLL_SRC_HSE_DIV_2				(0x03)

// PLL Multiplication Factor
#define RCCx_PLL_MUL_2						(0x00)
#define RCCx_PLL_MUL_3						(0x01)
#define RCCx_PLL_MUL_4						(0x02)
#define RCCx_PLL_MUL_5						(0x03)
#define RCCx_PLL_MUL_6						(0x04)
#define RCCx_PLL_MUL_7						(0x05)
#define RCCx_PLL_MUL_8						(0x06)
#define RCCx_PLL_MUL_9						(0x07)
#define RCCx_PLL_MUL_10						(0x08)
#define RCCx_PLL_MUL_11						(0x09)
#define RCCx_PLL_MUL_12						(0x0A)
#define RCCx_PLL_MUL_13						(0x0B)
#define RCCx_PLL_MUL_14						(0x0C)
#define RCCx_PLL_MUL_15						(0x0D)
#define RCCx_PLL_MUL_16						(0x0E)

// USB Prescaler
#define RCCx_USB_DIV_1_5					(0x00)
#define RCCx_USB_DIV_1						(0x01)
/*********************************************** RCC MACROS ***********************************************/

/*********************************************** NVIC MACROS ***********************************************/
// IRQn Number
#define WWDG_IRQn							(0)
#define PVD_IRQn							(1)
#define TAMPER_IRQn							(2)
#define RTC_IRQn							(3)
#define RCC_IRQn							(5)
#define EXTI0_IRQn							(6)
#define EXTI1_IRQn							(7)
#define EXTI2_IRQn							(8)
#define EXTI3_IRQn							(9)
#define EXTI4_IRQn							(10)
#define DMA1_Channel1_IRQn					(11)
#define DMA1_Channel2_IRQn					(12)
#define DMA1_Channel3_IRQn					(13)
#define DMA1_Channel4_IRQn					(14)
#define DMA1_Channel5_IRQn					(15)
#define DMA1_Channel6_IRQn					(16)
#define DMA1_Channel7_IRQn					(17)
#define ADC1_2_IRQn							(18)
#define EXTI9_5_IRQn						(23)
#define TIM2_IRQn							(28)
#define TIM3_IRQn							(29)
#define TIM4_IRQn							(30)
#define I2C1_EV_IRQn						(31)
#define I2C1_ER_IRQn						(32)
#define I2C2_EV_IRQn						(33)
#define I2C2_ER_IRQn						(34)
#define SPI1_IRQn							(35)
#define SPI2_IRQn							(36)
#define USART1_IRQn							(37)
#define USART2_IRQn							(38)
#define USART3_IRQn							(39)
#define EXTI15_10_IRQn						(40)
#define ADC3_IRQn							(47)
#define DMA2_Channel1_IRQn					(56)
#define DMA2_Channel2_IRQn					(57)
#define DMA2_Channel3_IRQn					(58)
#define DMA2_Channel4_5_IRQn				(59)
/*********************************************** NVIC MACROS ***********************************************/

/*********************************************** EXTI MACROS ***********************************************/
// External Trigger Selection
#define EXTI_TRIG_FALLING					(0x00)
#define EXTI_TRIG_RISING					(0x01)
#define EXTI_TRIG_BOTH						(0x02)

// AF EXTI
#define AF_EXTI_PA							(0x00)
#define AF_EXTI_PB							(0x01)
#define AF_EXTI_PC							(0x02)
#define AF_EXTI_PD							(0x03)
#define AF_EXTI_PE							(0x04)
#define AF_EXTI_PF							(0x05)
#define AF_EXTI_PG							(0x06)

/*
// Error Checking MACROs
#define IS_EXTI_TRIG_VALID(TRIGx)			(((TRIGx) == EXTI_TRIG_FALLING) \
											 || ((TRIGx) == EXTI_TRIG_RISING) \
											 || ((TRIGx) == EXTI_TRIG_BOTH))
#define IS_EXTI_IRQn_VALID(IRQn)			((IRQn) < 60)
#define IS_EXTI_STRUCTURE_VALID(EXTI_CONFIGx)	\
											((IS_GPIO_STRUCTURE_VALID(EXTI_CONFIGx->GPIOx_CONFIG) )&& \
											 (IS_EXTI_TRIG_VALID(EXTI_CONFIGx->TRIGx)) && \
											 (IS_EXTI_IRQn_VALID(EXTI_CONFIGx->IRQn)) && \
											 (EXTI_CONFIGx->GPIOx_CONFIG->MODE == GPIOx_MODE_IN))
*/							 
/*********************************************** EXTI MACROS ***********************************************/

/*********************************************** I2C MACROS ***********************************************/
// I2C Speed
#define I2Cx_SPEED_STD						(FREQ_100kHz)	
#define I2Cx_SPEED_FAST						(4 * FREQ_100kHz)
// I2C SCL Clock Frequency
#define I2Cx_SCL_FREQ_4MHz					(0x04)
#define I2Cx_SCL_FREQ_8MHz					(0x08)
#define I2Cx_SCL_FREQ_16MHz					(0x10)
#define I2Cx_SCL_FREQ_32MHz					(0x20)
#define I2Cx_SCL_FREQ_DEFAULT				RCC_Get_APB1Clock()
// I2C Mode
#define I2Cx_MODE_STD						(0x00)
#define I2Cx_MODE_FAST						(0x01)
// I2C Interrupt Mapping
#define	I2Cx_IRQ_EVENT						(0x01)
#define I2Cx_IRQ_BUFFER						(0x02)
#define I2Cx_IRQ_ERROR						(0x04)
#define I2Cx_IRQ_ALL						(I2Cx_IRQ_EVENT | I2Cx_IRQ_BUFFER | I2Cx_IRQ_ERROR)
// I2C Fast Mode Duty
#define I2Cx_DUTY_NORMAL					(0x00)
#define I2Cx_DUTY_FAST						(0x01)
// I2C Slave R/W Definitions
#define I2Cx_WRITE							(0x00)
#define I2Cx_READ							(0x01)
// I2C Peripheral Definitions
#define I2C1_SCL_GPIO						(GPIOB)
#define I2C1_SCL_PIN						(GPIOx_PIN_6)
#define I2C1_SDA_GPIO						(GPIOB)
#define I2C1_SDA_PIN						(GPIOx_PIN_7)
#define I2C2_SCL_GPIO						(GPIOB)
#define I2C2_SCL_PIN						(GPIOx_PIN_10)
#define I2C2_SDA_GPIO						(GPIOB)
#define I2C2_SDA_PIN						(GPIOx_PIN_11)
/*********************************************** I2C MACROS ***********************************************/

/*********************************************** SysTick MACROS ***********************************************/
// SysTick Clock Selection
#define SYSTICK_CLK_EXT						(0x00)
#define SYSTICK_CLK_CORE					(0x01)

// SysTick Delay
#define SYSTICK_DELAY_1_US					(RCC_Get_AHBClock())
#define SYSTICK_DELAY_2_US					(2 * SYSTICK_DELAY_1_US)
#define SYSTICK_DELAY_1_MS					(SYSTICK_DELAY_1_US / 1000)
#define SYSTICK_DELAYS_2_MS					(2 * SYSTICK_DELAY_1_MS)
/*********************************************** SysTick MACROS ***********************************************/

/*********************************************** TIMER MACROS ***********************************************/
// - Prescaler
// |-> Timer Frequency: 10kHz 
// |-> (PSC + 1) = (7199 + 1) = (7200)
#define TIMx_DEFAULT_10kHz_PSC				((uint16_t) 7199)
// - Max Count Value
// |-> Timer Frequency: 10kHz
// |-> (ARR + 1) = (9999 + 1) = (10000)
#define TIMx_DEFAULT_10kHz_ARR				((uint16_t) 9999)
// - Prescaler
// |-> Timer Frequency: 1MHz 
// |-> (PSC + 1) = (71 + 1) = (72)
#define TIMx_DEFAULT_1MHz_PSC				((uint16_t) 71)
// - Max Count Value
// |-> Timer Frequency: 10kHz
// |-> (ARR + 1) = (999 + 1) = (1000)
#define TIMx_DEFAULT_1MHz_ARR				((uint16_t) 999)
// Timer Start Value
#define TIMx_DEFAULT_CNT					((uint16_t) 0)

// Centre-align Mode Selection
#define TIMx_CMS_EDGE						(0x00)
#define TIMx_CMS_IF_DOWN					(0x01)
#define TIMx_CMS_IF_UP						(0x02)
#define TIMx_CMS_IF_BOTH					(0x03)

// Clock Division
#define TIMx_CKD_CLK_FREQ					(0x00)
#define TIMx_CKD_CLK_2_FREQ					(0x01)
#define TIMx_CKD_CLK_4_FREQ					(0x02)

// Master Mode Selection
#define TIMx_MMS_RESET						(0x00)
#define TIMx_MMS_ENABLE						(0x01)
#define TIMx_MMS_UPDATE						(0x02)
#define TIMx_MMS_CMP_PULSE					(0x03)
#define TIMx_MMS_CMP_OC1REF					(0x04)
#define TIMx_MMS_CMP_OC2REF					(0x05)
#define TIMx_MMS_CMP_OC3REF					(0x06)
#define TIMx_MMS_CMP_OC4REF					(0x07)

// Slave Mode Selection
#define TIMx_SMS_DISABLE					(0x00)
#define TIMx_SMS_ENC_MODE1					(0x01)
#define TIMx_SMS_ENC_MODE2					(0x02)
#define TIMx_SMS_ENC_MODE3					(0x03)

// TIM1 REMAP
#define TIM1_NO_REMAP						(0x00)    // (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12, CH1N/PB13, CH2N/PB14, CH3N/PB15)
#define TIM1_PARTIAL_REMAP					(0x01)    // (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6, CH1N/PA7, CH2N/PB0, CH3N/PB1)
#define TIM1_NOT_USED_REMAP					(0x02)    // Not Used
#define TIM1_FULL_REMAP						(0x03)    // (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15, CH1N/PE8, CH2N/PE10, CH3N/PE12)

// TIM2 REMAP
#define TIM2_NO_REMAP						(0x00)    // (CH1/ETR/PA0, CH2/PA1, CH3/PA2, CH4/PA3)
#define TIM2_PARTIAL1_REMAP					(0x01)    // (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3)
#define TIM2_PARTIAL2_REMAP					(0x02)    // (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11)
#define TIM2_FULL_REMAP						(0x03)    // (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11) 

// TIM3 REMAP
#define TIM3_NO_REMAP						(0x00)    // (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1)
#define TIM3_NOT_USED_REMAP					(0x01)    // Not Used
#define TIM3_PARTIAL_REMAP					(0x02)    // (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1)
#define TIM3_FULL_REMAP						(0x03)    // (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9) 

// TIM4 REMAP
#define TIM4_NO_REMAP						(0x00)    // (TIM4_CH1/PB6, TIM4_CH2/PB7, TIM4_CH3/PB8, TIM4_CH4/PB9)
#define TIM4_FULL_REMAP						(0x01)    // (TIM4_CH1/PD12, TIM4_CH2/PD13, TIM4_CH3/PD14, TIM4_CH4/PD15)

// Channel
#define TIMx_CHANNEL_1						(0x01)
#define TIMx_CHANNEL_2						(0x02)
#define TIMx_CHANNEL_3						(0x04)
#define TIMx_CHANNEL_4						(0x08)
#define TIMx_CHANNEL_ALL					(TIMx_CHANNEL_1 | TIMx_CHANNEL_2 | TIMx_CHANNEL_3 | TIMx_CHANNEL_4)

// Counting Mode
// "Up" if DIR = 0; "Down" if DIR = 1
#define TIMx_MODE_NORMAL					(0x00)
#define TIMx_MODE_ALT_IF_DOWN				(0x01)
#define TIMx_MODE_ALT_IF_UP					(0x02)
#define TIMx_MODE_ALT_IF_BOTH				(0x03)

// Direction 
#define TIMx_DIR_COUNT_UP					(0x00)
#define TIMx_DIR_COUNT_DOWN					(0x01)

// Auto Reload Preload Enable
#define TIMx_ARPE_DISABLE					(0x00)
#define TIMx_ARPE_ENABLE					(0x01)

// One Pulse Mode
#define TIMx_OPM_DISABLE					(0x00)
#define TIMx_OPM_ENABLE						(0x01)

// IRQ Enable
#define TIMx_IRQ_DISABLE					(0x00)
#define TIMx_IRQ_ENABLE						(0x01)

/*
// Error Check MACROS
#define IS_VALID_GPT(GP_TIMx)				((GP_TIMx) == TIM2 || (GP_TIMx) == TIM3 || (GP_TIMx) == TIM4)
#define IS_VALID_TIM_CHANNEL(CHx)			(((CHx) & ~(TIMx_CHANNEL_1 | TIMx_CHANNEL_2 | TIMx_CHANNEL_3 | TIMx_CHANNEL_4)) == ((uint8_t)0x00))
#define IS_VALID_TIM_CMS_MODE(MODE)			((MODE) == CMS_EDGE || (MODE) == CMS_IF_BOTH || (MODE) == CMS_IF_DOWN || (MODE) == CMS_IF_UP)
#define IS_VALID_TIM_DIRECTION(DIRx)		((DIRx) == TIMx_COUNT_UP || (DIRx) == TIMx_COUNT_DOWN)
#define IS_VALID_TIM_COUNT_MODE(MODE)		((MODE) == TIMx_MODE_NORMAL || (MODE) == TIMx_MODE_ALT_IF_DOWN || \
											 (MODE) == TIMx_MODE_ALT_IF_UP || (MODE) == TIMx_MODE_ALT_IF_BOTH)
#define IS_VALID_TIM_ARR(ARRx)				(((ARRx) >= (uint16_t)0x00) && ((ARRx) < (uint16_t)0xFFFF))
#define IS_VALID_TIM_FREQ(FREQx)			(((FREQx) > (uint32_t)0x00) && ((FREQx) <= PLL_MAX_FREQ))
#define IS_VALID_TIM_CNT(CNTx)				(((CNTx) >= (uint16_t)0x00) && ((CNTx) <= (uint16_t)0xFFFF))
#define IS_VALID_TIM_ARPE(ARPEx)			((ARPEx) == TIMx_ARPE_DISABLE || ((ARPEx) == TIMx_ARPE_ENABLE))
#define IS_VALID_TIM_OPM(OPMx)				((OPMx) == TIMx_OPM_DISABLE || ((OPMx) == TIMx_OPM_ENABLE))
#define IS_VALID_TIM_IRQ(IRQx)				(((IRQx) == TIMx_IRQ_ENABLE) || ((IRQx) == TIMx_IRQ_DISABLE))
#define IS_VALID_TIM_CONFIG_STRUCT(TIMx_CONFIG) \
											(IS_GPIO_STRUCTURE_VALID(TIMx_CONFIG->GPIOx_CONFIG) && \
											 IS_VALID_GPT((TIMx_CONFIG->GP_TIMx)) && \
											 IS_VALID_TIM_CHANNEL((TIMx_CONFIG->channel)) && \
											 IS_VALID_TIM_ARR((TIMx_CONFIG->auto_reload_value)) && \
											 IS_VALID_TIM_FREQ((TIMx_CONFIG->frequency_Hz)) && \
											 IS_VALID_TIM_CNT((TIMx_CONFIG->count)) && \
											 IS_VALID_TIM_CMS_MODE((TIMx_CONFIG->cms_mode)) && \
											 IS_VALID_TIM_DIRECTION((TIMx_CONFIG->direction)) && \
											 IS_VALID_TIM_ARPE((TIMx_CONFIG->auto_reload_preload)) && \
											 IS_VALID_TIM_OPM((TIMx_CONFIG->one_pulse)))									 
*/
/*********************************************** TIMER MACROS ***********************************************/

/*********************************************** PWM MACROS ***********************************************/
// PWM Min Duty Cycle: 1%
#define PWM_MIN_DUTY_CYCLE					(1)
// PWM Max Duty Cycle: 100%
#define PWM_MAX_DUTY_CYCLE					(999)

// Timer Remapping
#define TIM1_NO_REMAP						(0x00)
#define TIM1_PARTIAL_REMAP					(0x01)
#define TIM2_NO_REMAP						(0x00)
#define TIM2_PARTIAL_REMAP_1				(0x01)
#define TIM2_PARTIAL_REMAP_2				(0x02)
#define TIM2_FULL_REMAP						(0x03)
#define TIM3_NO_REMAP						(0x00)
#define TIM3_PARTIAL_REMAP					(0x02)
#define TIM4_NO_REMAP						(0x00)

// PWM Channel Active Polarity
#define PWM_CHx_POL_ACTIVE_HIGH				(0x00)
#define PWM_CHx_POL_ACTIVE_LOW				(0x01)

// PWM Channel Preload
#define PWM_CHx_PRELOAD_DISABLE				(0x00)
#define PWM_CHx_PRELOAD_ENABLE				(0x01)

// Freeze mode: 
// Comparison between `TIMx_CCRy` and `TIMx_CNT` has no effect on the outputs 
#define PWM_MODE_FREEZE						(0x00)
// Set Channel Mode:
// `OCyREF` signal is forced high when `TIMx_CNT` == `TIMx_CCRy`
#define PWM_MODE_SET_CH						(0x01)    
// Reset Channel Mode:
// `OCyREF` signal is forced low when `TIMx_CNT` == `TIMx_CCRy`
#define PWM_MODE_RESET_CH					(0x02)
// Toggle Mode:
// `OCyREF` toggles when `TIMx_CNT` == `TIMx_CCRy`
#define PWM_MODE_TOGGLE						(0x03)
// Force Reset Mode:
// `OCyREF` is forced low
#define PWM_MODE_FORCE_RESET				(0x04)
// Force Set Mode:
// `OCyREF` is forced high
#define PWM_MODE_FORCE_SET					(0x05)
// PWM Normal Mode:
// `CHy` is active as long as `TIMx_CNT` < `TIMx_CCRy`
#define PWM_MODE_NORMAL						(0x06)
// PWM Inverted Mode:
// `CHy` is active as long as `TIMx_CNT` > `TIMx_CCRy`
#define PWM_MODE_INVERTED					(0x07)

// Max Counter Value for PWM
#define PWM_DEFAULT_ARR						((uint16_t) 999)

/*
// Error Checking MACROS
#define IS_VALID_PWM_MODE(MODE)				((MODE) == TIMx_OCM_FREEZE || (MODE) == TIMx_OCM_SET_CH || \
											 (MODE) == TIMx_OCM_RESET_CH || (MODE) == TIMx_OCM_TOGGLE || \
											 (MODE) == TIMx_OCM_FORCE_RESET || (MODE) == TIMx_OCM_FORCE_SET || \
											 (MODE) == TIMx_OCM_PWM_NORMAL || (MODE) == TIMx_OCM_PWM_INVERTED)
#define IS_VALID_PWM_POLARITY(POLx)			((POLx) == TIMx_POL_ACTIVE_HIGH || (POLx) == TIMx_POL_ACTIVE_LOW)
#define IS_VALID_PWM_DUTY_CYCLE(DUTYx)		((DUTYx) >= MIN_DUTY_CYCLE && (DUTYx) <= MAX_DUTY_CYCLE)
#define IS_VALID_PWM_CHANNEL_PRELOAD(CH_PRx)(((CH_PRx) == PWM_CHx_PRELOAD_DISABLE) || ((CH_PRx) == PWM_CHx_PRELOAD_ENABLE))
#define IS_VALID_PWM_CONFIG_STRUCT(PWM_CONFIG) \
											(IS_VALID_TIM_CONFIG_STRUCT(PWM_CONFIG->TIMx_CONFIG) && \
											 IS_VALID_PWM_MODE(PWM_CONFIG->pwm_mode) && \
											 IS_VALID_PWM_POLARITY(PWM_CONFIG->polarity) && \
											 IS_VALID_PWM_DUTY_CYCLE(PWM_CONFIG->duty_cycle) && \
											 IS_VALID_PWM_CHANNEL_PRELOAD(PWM_CONFIG->pwm_channel_preload))
#define WRAP_DUTY_CYCLE(DUTYx)				((DUTYx) = (((DUTYx) > MAX_DUTY_CYCLE) ? (MAX_DUTY_CYCLE) : (((DUTYx) < MIN_DUTY_CYCLE) ? (MIN_DUTY_CYCLE) : (DUTYx))))
#define PWM_DUTY_CYCLE_WRAP(PWMx)			(WRAP_DUTY_CYCLE(((PWMx)->duty_cycle)))
*/

/*********************************************** PWM MACROS ***********************************************/

/*********************************************** ADC MACROS ***********************************************/
// ADC Max Value
#define MAX_ADC_VALUE						((uint16_t) 0x0FFF)

// ADC Channel
#define ADC_CHANNEL_0						(0)
#define ADC_CHANNEL_1						(1)
#define ADC_CHANNEL_2						(2)
#define ADC_CHANNEL_3						(3)
#define ADC_CHANNEL_4						(4)
#define ADC_CHANNEL_5						(5)
#define ADC_CHANNEL_6						(6)
#define ADC_CHANNEL_7						(7)
#define ADC_CHANNEL_8						(8)
#define ADC_CHANNEL_9						(9)

// ADC Sample Time
#define ADC_SAMPLE_1_5						(0)
#define ADC_SAMPLE_7_5						(1)
#define ADC_SAMPLE_13_5						(2)
#define ADC_SAMPLE_28_5						(3)
#define ADC_SAMPLE_41_5						(4)
#define ADC_SAMPLE_55_5						(5)
#define ADC_SAMPLE_71_5						(6)
#define ADC_SAMPLE_239_5					(7)

// ADC Continuous Conversion
#define ADC_CONT_CONV_OFF					(0)
#define ADC_CONT_CONV_ON					(1)

// ADC Data Alignment
#define ADC_DATA_ALIGN_RIGHT				(0)
#define ADC_DATA_ALIGN_LEFT					(1)

// ADC IRQ
#define ADCx_IRQ_DISABLE					(0)
#define ADCx_IRQ_ENABLE						(1)

// ADC Sample Time Channel Decoding
#define ADC_SAMPLE_CHANNEL(ADC_SAMPLEx)		((uint8_t)(((ADC_SAMPLEx) & 0xF0) >> 4))
// ADC Sample Time Decoding
#define ADC_SAMPLE_TIME(ADC_SAMPLEx)		((uint8_t)((ADC_SAMPLEx) & 0x0F))

/*
// Error Checking MACROS
#define IS_VALID_ADC_CHANNEL(CHx)			(((CHx) == ADC_CHANNEL_0) || ((CHx) == ADC_CHANNEL_1) || \
											 ((CHx) == ADC_CHANNEL_2) || ((CHx) == ADC_CHANNEL_3) || \
											 ((CHx) == ADC_CHANNEL_4) || ((CHx) == ADC_CHANNEL_5) || \
											 ((CHx) == ADC_CHANNEL_6) || ((CHx) == ADC_CHANNEL_7) || \
											 ((CHx) == ADC_CHANNEL_8) || ((CHx) == ADC_CHANNEL_9))
*/
/*********************************************** ADC MACROS ***********************************************/

/*********************************************** USART MACROS ***********************************************/
// TX
#define USARTx_TX_DISABLE					(0x00)
#define USARTx_TX_ENABLE					(0x01)

// RX
#define USARTx_RX_DISABLE					(0x00)
#define USARTx_RX_ENABLE					(0x01)

// TX Empty IRQ
#define USARTx_TXEIE_DISABLE				(0x00) 
#define USARTx_TXEIE_ENABLE					(0x01)

// RX Not Empty IRQ
#define USARTx_RXNEIE_DISABLE				(0x00) 
#define USARTx_RXNEIE_ENABLE				(0x01)

// TX Complete IRQ
#define USARTx_TCIE_DISABLE					(0x00)
#define USARTx_TCIE_ENABLE					(0x01)

// Parity Control
#define USARTx_PARITY_DISABLE				(0x00)
#define USARTx_PARITY_ENABLE				(0x01)

// Word Length
#define USARTx_WORD_8_BITS					(0x00)
#define USARTx_WORD_9_BITS					(0x01)

// Stop Bits
#define USARTx_STOP_1_BIT					(0x00)
#define USARTx_STOP_0_5_BITS				(0x01)
#define USARTx_STOP_2_BITS					(0x02)
#define USARTx_STOP_1_5_BITS				(0x03)

// Parity Mode
#define USARTx_PARITY_EVEN					(0x00)
#define USARTx_PARITY_ODD					(0x01)

// Baud Rate
#define USARTx_BAUD_4800					((uint16_t) 4800)
#define USARTx_BAUD_9600					((uint16_t) 9600)
#define USARTx_BAUD_115200					((uint16_t) 115200)

// Local Delay
#define USARTx_STRING_TX_DELAY				((uint16_t) 3000)
/*********************************************** USART MACROS ***********************************************/

/*********************************************** DMA MACROS ***********************************************/
// DMA Direction
#define DMAx_DIR_READ_PER					(0x00)
#define DMAx_DIR_READ_MEM					(0x01)

// Memory to Memory Transfer
#define DMAx_MEM2MEM_DISABLE				(0x00)
#define DMAx_MEM2MEM_ENABLE					(0x01)

// Circular Mode
#define DMAx_CIRC_DISABLE					(0x00)
#define DMAx_CIRC_ENABLE					(0x01)

// Priority Level
#define DMAx_PRIORITY_LOW 					(0x00)
#define DMAx_PRIORITY_MEDIUM 				(0x01)
#define DMAx_PRIORITY_HIGH	 				(0x02)
#define DMAx_PRIORITY_VERY_HIGH	 			(0x03)

// Address Increment
#define DMAx_INC_DISABLE					(0x00)
#define DMAx_INC_ENABLE						(0x01)

// DMA Data Size for Transfer
#define DMAx_DATA_SIZE_BIT_8				(0x00)
#define DMAx_DATA_SIZE_BIT_16				(0x01)
#define DMAx_DATA_SIZE_BIT_32				(0x02)

// Interrupts
#define DMAx_IRQ_DISABLE					(0x00)
#define DMAx_IRQ_ENABLE						(0x01)

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
