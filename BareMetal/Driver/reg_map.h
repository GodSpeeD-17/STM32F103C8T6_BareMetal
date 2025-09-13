/*
****************************************************************************************************************
 *	Basic Notes:-
 *	YouTube Reference Video: https://youtu.be/zvTd3Zxtiek
 *	`uint32_t` inside every BIT struct because of padding alignment
 *	`volatile` used for ensuring no further optimization by compiler
 *	`: x` indicates only x bit(s) to be used from that 32-bit
****************************************************************************************************************
 *                            🔧 Bit Manipulation Built-ins (GCC)                      
 * -------------------------------------------------------------------------------------
 * | Built-in Function        | Description                                           |
 * |--------------------------|--------------------------------------------------------|
 * | __builtin_clz(x)         | Counts leading zeros from MSB (Undefined if x == 0)   |
 * | __builtin_ctz(x)         | Counts trailing zeros from LSB (Undefined if x == 0)  |
 * | __builtin_popcount(x)    | Counts number of bits set to 1 (Hamming weight)       |
 * | __builtin_parity(x)      | Returns 1 if number of 1-bits is odd, else 0          |
 * | __builtin_ffsl(x)        | Index (1-based) of first bit set (LSB side)           |
 * | __builtin_bswap16(x)     | Swaps byte order (Endian swap) for 16-bit integer     |
 * | __builtin_bswap32(x)     | Swaps byte order for 32-bit integer                   |
 * | __builtin_bswap64(x)     | Swaps byte order for 64-bit integer                   |
 * -------------------------------------------------------------------------------------
 * Notes:
 * - All __builtin_* functions are evaluated at compile-time if argument is constant.
 * - __builtin_clz/ctz are undefined if input is zero; guard input accordingly.
 * - These generate single assembly instructions (CLZ, RBIT, etc.) on ARM Cortex-M.
 * - Use with uint32_t or cast explicitly to avoid type promotion issues.
 *
 * Example Usage:
 *   uint32_t val = 0x0000000F;
 *   uint8_t zeros = __builtin_clz(val);      // → 28
 *   uint8_t set   = __builtin_popcount(val); // → 4
 *   uint8_t rev   = __builtin_bswap32(val);  // → 0xF0000000
 *
*/

// Header Guards
#ifndef __REG_MAP_H__
#define __REG_MAP_H__

/*********************************************** Core C ***********************************************/
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
/*********************************************** Core C ***********************************************/

/*********************************************** Custom Declaration ***********************************************/
// #define NULL            					((void *) 0)
#define __INLINE__							__attribute__((always_inline)) inline
#define __STATIC__							static
#define __STATIC_INLINE__					__STATIC__ __INLINE__
#define __IO								volatile
#define __PACKED__							__attribute__((__packed__))

/**
 * @brief Enumeration for Success/Failure for Driver return
 */
typedef enum {
	DRIVER_SUCCESS = (uint8_t) 0x00,
	DRIVER_FAIL = (uint8_t) 0x01
} driver_status_t;
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
#define SysTick								((SysTick_TypeDef *)(SysTick_BASE_ADDR))
#define NVIC								((NVIC_TypeDef *)(NVIC_BASE_ADDR))
#define FLASH								((FLASH_REG_STRUCT *)(FLASH_BASE_ADDR))
#define WWDG								((WWDG_REG_STRUCT *) (APB1_BASE_ADDR + 0x00002C00))
#define RCC                     			((RCC_REG_STRUCT *)(AHB_BASE_ADDR + 0x00009000))
#define GPIOA								((GPIO_TypeDef *)(APB2_BASE_ADDR + 0x00000800))
#define GPIOB								((GPIO_TypeDef *)(APB2_BASE_ADDR + 0x00000C00))
#define GPIOC								((GPIO_TypeDef *)(APB2_BASE_ADDR + 0x00001000))
#define GPIOD								((GPIO_TypeDef *)(APB2_BASE_ADDR + 0x00001400))
#define GPIOE								((GPIO_TypeDef *)(APB2_BASE_ADDR + 0x00001800))
#define GPIOF								((GPIO_TypeDef *)(APB2_BASE_ADDR + 0x00001C00))
#define GPIOG								((GPIO_TypeDef *)(APB2_BASE_ADDR + 0x00002000))
#define AFIO								((AFIO_TypeDef *)(APB2_BASE_ADDR))
#define TIM1								((Adv_TIM_TypeDef *)(APB2_BASE_ADDR + 0x00002C00))
#define TIM2								((TIM_TypeDef *)(APB1_BASE_ADDR + 0x00000000))
#define TIM3								((TIM_TypeDef *)(APB1_BASE_ADDR + 0x00000400))
#define TIM4								((TIM_TypeDef *)(APB1_BASE_ADDR + 0x00000800))
#define TIM5								((TIM_TypeDef *)(APB1_BASE_ADDR + 0x00000C00))
#define TIM6								((TIM_TypeDef *)(APB1_BASE_ADDR + 0x00001000))
#define TIM7								((TIM_TypeDef *)(APB1_BASE_ADDR + 0x00001400))
#define TIM8								((Adv_TIM_TypeDef *)(APB2_BASE_ADDR + 0x00003400))
#define ADC1								((ADC_TypeDef *)(APB2_BASE_ADDR + 0x00002400))
#define ADC2								((ADC_TypeDef *)(APB2_BASE_ADDR + 0x00002800))
#define ADC3								((ADC_TypeDef *)(APB2_BASE_ADDR + 0x00003C00))
#define USART1								((USART_TypeDef *)(APB2_BASE_ADDR + 0x00003800))
#define USART2								((USART_TypeDef *)(APB1_BASE_ADDR + 0x00004400))
#define USART3								((USART_TypeDef *)(APB1_BASE_ADDR + 0x00004800))
#define EXTI								((EXTI_REG_STRUCT*)(APB2_BASE_ADDR + 0x00000400))
#define I2C1								((I2C_TypeDef *)(APB1_BASE_ADDR + 0x00005400))
#define I2C2								((I2C_TypeDef *)(APB1_BASE_ADDR + 0x00005800))
#define DMA1								((DMA_TypeDef *) DMA1_BASE_ADDR)
#define DMA1_Channel1						((DMA_Channel_TypeDef *) (DMA1_BASE_ADDR + 0x00000008))
#define DMA1_Channel2						((DMA_Channel_TypeDef *) (DMA1_BASE_ADDR + 0x0000001C))
#define DMA1_Channel3						((DMA_Channel_TypeDef *) (DMA1_BASE_ADDR + 0x00000030))
#define DMA1_Channel4						((DMA_Channel_TypeDef *) (DMA1_BASE_ADDR + 0x00000044))
#define DMA1_Channel5						((DMA_Channel_TypeDef *) (DMA1_BASE_ADDR + 0x00000058))
#define DMA1_Channel6						((DMA_Channel_TypeDef *) (DMA1_BASE_ADDR + 0x0000006C))
#define DMA1_Channel7						((DMA_Channel_TypeDef *) (DMA1_BASE_ADDR + 0x00000080))
#define DMA2								((DMA_TypeDef *) DMA2_BASE_ADDR)
#define DMA2_Channel1						((DMA_Channel_TypeDef *) (DMA2_BASE_ADDR + 0x00000008))
#define DMA2_Channel2						((DMA_Channel_TypeDef *) (DMA2_BASE_ADDR + 0x0000001C))
#define DMA2_Channel3						((DMA_Channel_TypeDef *) (DMA2_BASE_ADDR + 0x00000030))
#define DMA2_Channel4						((DMA_Channel_TypeDef *) (DMA2_BASE_ADDR + 0x00000044))
#define DMA2_Channel5						((DMA_Channel_TypeDef *) (DMA2_BASE_ADDR + 0x00000058))
/*********************************************** Address Mapping ***********************************************/

/*********************************************** GPIO MACROS ***********************************************/
// Generic
#define BIT_SET								(0x01)
#define BIT_RESET							(0x00)

/**
 * @brief GPIO Port Enumeration
 * @note Used to specify the port of a GPIO
 */
typedef enum {
	// GPIO Port A
	GPIO_PORT_A = (uint8_t) 0x00,
	// GPIO Port B
	GPIO_PORT_B = (uint8_t) 0x01,
	// GPIO Port C
	GPIO_PORT_C = (uint8_t) 0x02,
	// GPIO Port D
	GPIO_PORT_D = (uint8_t) 0x03,
	// GPIO Port E
	GPIO_PORT_E = (uint8_t) 0x04,
	// GPIO Port F
	GPIO_PORT_F = (uint8_t) 0x05,
	// GPIO Port G
	GPIO_PORT_G = (uint8_t) 0x06,
	// On-board (OB) LED Port
	GPIO_PORT_OB_LED = GPIO_PORT_C
} gpio_port_t;

// GPIO PIN
// #define GPIOx_PIN_0							(0x00)
// #define GPIOx_PIN_1							(0x01)
// #define GPIOx_PIN_2							(0x02)
// #define GPIOx_PIN_3							(0x03)
// #define GPIOx_PIN_4							(0x04)
// #define GPIOx_PIN_5							(0x05)
// #define GPIOx_PIN_6							(0x06)
// #define GPIOx_PIN_7							(0x07)
// #define GPIOx_PIN_8							(0x08)
// #define GPIOx_PIN_9							(0x09)
// #define GPIOx_PIN_10						(0x0A)
// #define GPIOx_PIN_11						(0x0B)
// #define GPIOx_PIN_12						(0x0C)
// #define GPIOx_PIN_13						(0x0D)
// #define GPIOx_PIN_14						(0x0E)
// #define GPIOx_PIN_15						(0x0F)
// #define OB_LED_PORT							GPIOC
// #define OB_LED_PIN							GPIOx_PIN_13

/**
 * @brief GPIO Pin Enumeration
 * @note Used to specify the pin number of a GPIO
 */
typedef enum {
	GPIO_PIN_0 = (uint16_t) 0x0001,
	GPIO_PIN_1 = (uint16_t) 0x0002,
	GPIO_PIN_2 = (uint16_t) 0x0004,
	GPIO_PIN_3 = (uint16_t) 0x0008,
	GPIO_PIN_4 = (uint16_t) 0x0010,
	GPIO_PIN_5 = (uint16_t) 0x0020,
	GPIO_PIN_6 = (uint16_t) 0x0040,
	GPIO_PIN_7 = (uint16_t) 0x0080,
	GPIO_PIN_8 = (uint16_t) 0x0100,
	GPIO_PIN_9 = (uint16_t) 0x0200,
	GPIO_PIN_10 = (uint16_t) 0x0400,
	GPIO_PIN_11 = (uint16_t) 0x0800,
	GPIO_PIN_12 = (uint16_t) 0x1000,
	GPIO_PIN_13 = (uint16_t) 0x2000,
	GPIO_PIN_14 = (uint16_t) 0x4000,
	GPIO_PIN_15 = (uint16_t) 0x8000,
	GPIO_PIN_ALL = (uint16_t) 0xFFFF,
	GPIO_PIN_OB_LED = GPIO_PIN_13
} gpio_pin_t;

// MODE
#define GPIOx_MODE_IN						(0x00)
#define GPIOx_MODE_OUT_10MHz				(0x01)
#define GPIOx_MODE_OUT_2MHz					(0x02)
#define GPIOx_MODE_OUT_50MHz				(0x03)

/**
 * @brief GPIO Mode Enumeration
 * @brief Used to specify the mode of a GPIO
 */
typedef enum {
	// GPIO as Input
	GPIO_MODE_INPUT = (uint8_t) 0x00,
	// GPIO as Output @10MHz
	GPIO_MODE_OUTPUT_10MHz = (uint8_t) 0x01,
	// GPIO as Output @2MHz
	GPIO_MODE_OUTPUT_2MHz = (uint8_t) 0x02,
	// GPIO as Output @50MHz
	GPIO_MODE_OUTPUT_50MHz = (uint8_t) 0x03
} gpio_mode_t;

// CONFIGURATION
#define GPIOx_CNF_IN_ANALOG					(0x00)
#define GPIOx_CNF_IN_FLOAT					(0x01)
#define GPIOx_CNF_IN_PD						(0x03)
#define GPIOx_CNF_IN_PU						(0x04)
#define GPIOx_CNF_OUT_GP_PP					(0x00)
#define GPIOx_CNF_OUT_GP_OD					(0x01)
#define GPIOx_CNF_OUT_AF_PP					(0x02)
#define GPIOx_CNF_OUT_AF_OD					(0x03)

/**
 * @brief GPIO Pin Configuration Enumeration
 * @note Configuration options vary based on whether the pin is set as input or output
 */
typedef enum {
	GPIO_CNF_IN_ANALOG = (uint8_t) 0x00,
	GPIO_CNF_IN_FLOAT = (uint8_t) 0x01,
	GPIO_CNF_IN_PULL_DOWN = (uint8_t) 0x02,
	GPIO_CNF_IN_PULL_UP = (uint8_t) 0x03,
	GPIO_CNF_OUT_GP_PP = (uint8_t) 0x00,
	GPIO_CNF_OUT_GP_OD = (uint8_t) 0x01,
	GPIO_CNF_OUT_AF_PP = (uint8_t) 0x02,
	GPIO_CNF_OUT_AF_OD = (uint8_t) 0x03
} gpio_cnf_t;

typedef enum {
	GPIO_ANALOG = 0x00,
	GPIO_FLOATING = 0x01,
	GPIO_PULL_DOWN = 0x03,
	GPIO_PULL_UP = 0x04,
} gpio_state_input_t;

typedef enum {
	GPIO_GP_PUSH_PULL = 0x00,
	GPIO_GP_OPEN_DRAIN = 0x01,
	GPIO_AF_PUSH_PULL = 0x02,
	GPIO_AF_OPEN_DRAIN = 0x03
} gpio_state_output_t;

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
#define FLASH_IRQn							(4)
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
#define USB_HP_CAN_TX_IRQ					(19)
#define USB_LP_CAN_RX0_IRQ					(20)
#define CAN_RX1_IRQ							(21)
#define CAN_SCE_IRQ							(22)
#define EXTI9_5_IRQn						(23)
#define TIM1_BRK_IRQn						(24)
#define TIM1_UP_IRQn						(25)
#define TIM1_TRG_COM_IRQn					(26)
#define TIM1_CC_IRQn						(27)
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
#define RTC_Alarm_IRQn						(41)
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
#define SYSTICK_DELAY_2_US					(SYSTICK_DELAY_1_US << 1)
#define SYSTICK_DELAY_1_MS					(SYSTICK_DELAY_1_US / FREQ_1kHz)
#define SYSTICK_DELAYS_2_MS					(SYSTICK_DELAY_1_MS << 1)
/*********************************************** SysTick MACROS ***********************************************/

/*********************************************** Timer MACROS ***********************************************/
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

/**
 * @enum tim_channel_t
 * @brief Timer Channel Enumeration
 * @note  This enumeration defines the available timer channels
 */
typedef enum {
	// Timer Channel None
	TIMx_CHANNEL_NONE = 0x00,
	// Timer Channel 1
	TIMx_CHANNEL_1 = 0x01,
	// Timer Channel 2
	TIMx_CHANNEL_2 = 0x02,
	// Timer Channel 3
	TIMx_CHANNEL_3 = 0x04,
	// Timer Channel 4
	TIMx_CHANNEL_4 = 0x08,
	// All Timer Channels
	TIMx_CHANNEL_ALL = 0x0F
} tim_channel_t;

/**
 * @brief Timer Counting Mode Enumeration
 * @note  This enumeration defines the available timer modes
 */
typedef enum {
	/**
	 	@brief Normal Mode
	 	@note The counter counts up or down depending on direction
	 */
	TIMx_MODE_NORMAL = 0x00,
	/**
	 	@brief Alternate Mode Counting
	 	@note  The counter counts up and down alternatively but 
				interrupt flags are set only during counting down
	 */
	TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING = 0x01,
	/**
	 	@brief Alternate Mode Counting
	 	@note  The counter counts up and down alternatively but 
				interrupt flags are set only during counting up
	 */
	TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING = 0x02,
	/**
	 	@brief Alternate Mode Counting
	 	@note  The counter counts up and down alternatively but 
				interrupt flags are set during both counting up and down
	 */
	TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING = 0x03
} tim_count_mode_t;

/**
 * @brief Timer Direction Enumeration
 * @note  This enumeration defines the counting direction of the timer
 */
typedef enum {
	/**
	 	@brief Count Up
	 	@note  The timer counts up
	 */
	TIMx_DIR_COUNT_UP = 0x00,
	/**
	 	@brief Count Down
	 	@note  The timer counts down
	 */
	TIMx_DIR_COUNT_DOWN = 0x01
} tim_direction_t;

/**
 * @brief Auto-Reload Preload Enable
 * @note  This enumeration defines the Auto-Reload Preload Enable state of the timer
 */
typedef enum {
	/**
	 	@brief Auto-Reload Preload Disable
	 	@note  The timer's auto-reload preload is disabled
	 */
	TIMx_ARPE_DISABLE = 0x00,
	/**
	 	@brief Auto-Reload Preload Enable
	 	@note  The timer's auto-reload preload is enabled
	 */
	TIMx_ARPE_ENABLE = 0x01
} tim_arpe_t;

/**
 * @brief One Pulse Mode
 * @note  This enumeration defines the One Pulse Mode state of the timer
 */
typedef enum {
	/**
	 	@brief One Pulse Mode Disable
	 	@note  The timer's one pulse mode is disabled
	 */
	TIMx_OPM_DISABLE = 0x00,
	/**
	 	@brief One Pulse Mode Enable
	 	@note  The timer's one pulse mode is enabled
	 */
	TIMx_OPM_ENABLE = 0x01
} tim_opm_t;

/**
 * @brief Trigger Source Enumeration
 * @note  This enumeration defines the available trigger sources for the timer
 */
typedef enum {
	/**
	 	@brief Trigger Source - All
	 	@note  Only following sources for Updated Event (UEV) enabled:
				@note 1. Counter overflow (OVF)
				@note 2. Counter underflow (UVF)
				@note 3. DMA request
				@note 4. Setting the `UG` bit (Refer `TIMx->EGR`)
				@note 5. Update generation through the slave mode controller
	 */
	TIMx_UPDATE_SOURCE_ANY = 0x00,
	/**
	 	@brief Trigger Source - UVF/OVF/DMA
	 	@note  Only following sources for Updated Event (UEV) enabled:
				@note 1. Counter overflow (OVF) 
				@note 2. Counter underflow (UVF) 
				@note 3. DMA request
	 */
	TIMx_UPDATE_SOURCE_OVF_DMA = 0x01
} tim_update_source_t;

// IRQ Enable
typedef enum {
	TIMx_IRQ_DISABLE = 0x00,
	TIMx_IRQ_ENABLE = 0x01
} tim_irq_enable_t;

/**
 * @brief Timer Interrupt Request (IRQ) Enumeration
 * @note  This enumeration defines the available timer IRQ sources
 */
typedef enum {
	/* Timer Interrupt for Overflow (OVF) /Underflow (UVF) Event */
	TIMx_IRQ_OVF_UVF = 0x01,
	/* Timer Interrupt for Output Compare (CMP) Event on Channel 1 */
	TIMx_IRQ_OUT_CMP_CH1 = 0x02,
	/* Timer Interrupt for Output Compare (CMP) Event on Channel 2 */
	TIMx_IRQ_OUT_CMP_CH2 = 0x04,
	/* Timer Interrupt for Output Compare (CMP) Event on Channel 3 */
	TIMx_IRQ_OUT_CMP_CH3 = 0x08,
	/* Timer Interrupt for Output Compare (CMP) Event on Channel 4 */
	TIMx_IRQ_OUT_CMP_CH4 = 0x10,
	/* Timer Interrupt for Input Capture (CAP) Event on Channel 1 */
	TIMx_IRQ_IN_CAP_CH1 = 0x02,
	/* Timer Interrupt for Input Capture (CAP) Event on Channel 2 */
	TIMx_IRQ_IN_CAP_CH2 = 0x04,
	/* Timer Interrupt for Input Capture (CAP) Event on Channel 3 */
	TIMx_IRQ_IN_CAP_CH3 = 0x08,
	/* Timer Interrupt for Input Capture (CAP) Event on Channel 4 */
	TIMx_IRQ_IN_CAP_CH4 = 0x10,
	/* Timer Interrupt for All Events */
	TIMx_IRQ_ALL = 0x1F
} tim_irq_t;

// Timer DMA Definitions
#define TIMx_DMA_UPDATE						(0x01)
#define TIMx_DMA_CC1DE						(0x02)
#define TIMx_DMA_CC2DE						(0x04)
#define TIMx_DMA_CC3DE						(0x08)
#define TIMx_DMA_CC4DE						(0x10)

/*********************************************** Timer MACROS ***********************************************/

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

/**
 * @enum `tim_channel_mode_t`
 * @brief Channel Output Compare operating modes for TIMx channels
 * @note These modes define how the Output Compare (OC) signal behaves based on
 * @note the relationship between the counter (`TIMx_CNT`) and the capture/compare
 * @note register (`TIMx_CCRy`)
 */
typedef enum {
	/**
	 * @brief Freeze Mode
	 * @details `TIMx_CNT == TIMx_CCRy` has no effect on the outputs
	 */
	TIMx_CHANNEL_MODE_FREEZE = 0x00,

	/**
	 * @brief Set Channel Mode
	 * @details `OCyREF` signal is forced high when `TIMx_CNT == TIMx_CCRy`
	 */
	TIMx_CHANNEL_MODE_SET_CH = 0x01,

	/**
	 * @brief Reset Channel Mode
	 * @details `OCyREF` signal is forced low when `TIMx_CNT == TIMx_CCRy`
	 */
	TIMx_CHANNEL_MODE_RESET_CH = 0x02,

	/**
	 * @brief Toggle Mode
	 * @details `OCyREF` toggles whenever `TIMx_CNT == TIMx_CCRy`
	 */
	TIMx_CHANNEL_MODE_TOGGLE = 0x03,

	/**
	 * @brief Force Reset Mode
	 * @details `OCyREF` is permanently forced low
	 */
	TIMx_CHANNEL_MODE_FORCE_RESET = 0x04,

	/**
	 * @brief Force Set Mode
	 * @details `OCyREF` is permanently forced high
	 */
	TIMx_CHANNEL_MODE_FORCE_SET = 0x05,

	/**
	 * @brief PWM Normal Mode
	 * @details Channel `CHy` is active as long as `TIMx_CNT < TIMx_CCRy`
	 */
	TIMx_CHANNEL_MODE_PWM1 = 0x06,

	/**
	 * @brief PWM Inverted Mode
	 * @details Channel `CHy` is active as long as `TIMx_CNT > TIMx_CCRy`
	 */
	TIMx_CHANNEL_MODE_PWM2 = 0x07
} tim_channel_mode_t;

/**
 * @brief Timer Channel Capture/Compare Selection
 * @note This enum defines the selection mode for the Timer Channel Capture/Compare (CC) feature
 */
typedef enum {
	/**
	 	@brief Channel configured as Output
	 	@note This mode allows the channel to output a PWM signal based on the compare value
	 */
	TIMx_CHANNEL_CCS_OUTPUT = 0x00,
	/**
	 	@brief Channel configured as Input
	 	@note This mode allows ICx to be mapped on TIx
	 */
	TIMx_CHANNEL_CCS_INPUT_TIx = 0x01,
	/**
	 	@brief - Channel configured as Input
	 	@brief - If x is odd, This mode allows ICx to be mapped on TIx+1
	 	@brief - If x is even, This mode allows ICx to be mapped on TIx-1
		@note - For CC1S, IC1 is mapped on TI2
		@note - For CC2S, IC2 is mapped on TI1
		@note - For CC3S, IC3 is mapped on TI4
		@note - For CC4S, IC4 is mapped on TI3
	 */
	TIMx_CHANNEL_CCS_INPUT_TIx_1 = 0x02,
	/**
	 	@brief - Channel configured as Input
	 	@brief - This mode allows ICx to be mapped on TRC
	 	@note This mode is working only if an internal trigger input is selected through the TS bit (TIMx_SMCR register)
	 */
	TIMx_CHANNEL_CCS_INPUT_TRC = 0x03
} tim_channel_ccs_t;

/**
 * @enum `tim_channel_oc_preload_t`
 * @brief Timer Channel Output Compare Preload Configuration
 * @note This enum defines the preload configuration for the Output Compare (OC) feature
 */
typedef enum {
	/**
	 * @brief Channel Output Compare Preload Disable
	 * @note The PWM channel does not use preload
	 */
	TIMx_CHANNEL_OC_PRELOAD_DISABLE = 0x00,
	/**
	 * @brief Channel Output Compare Preload Enable
	 * @note The PWM channel uses preload
	 */
	TIMx_CHANNEL_OC_PRELOAD_ENABLE = 0x01
} tim_channel_oc_preload_t;

/**
 * @enum `tim_channel_oc_fast_t`
 * @brief Timer Channel Output Compare Fast Configuration. 
 * @brief Used to accelerate the effect of an event on the trigger in input on the CC output
 * @note This enum defines the fast configuration for the Output Compare (OC) feature
 */
typedef enum {
	/**
	 * @brief - Channel Output Compare Fast Disable
	 * @brief - CCx behaves normally depending on counter and CCRx values even when the trigger is ON
	 * @note The minimum delay to activate CC1 output when an edge occurs on the trigger input is 5 clock cycles
	 */
	TIMx_CHANNEL_OC_FAST_DISABLE = 0x00,
	/**
	 * @brief - Channel Output Compare Fast Enable
	 * @brief - An active edge on the trigger input acts like a compare match on CCx output
	 * @brief - OC is set to the compare level independently from the result of the comparison
	 * @brief - Delay to sample the trigger input and to activate CC1 output is reduced to 3 clock cycles
	 * @note Acts only if the channel is configured in PWM1 or PWM2 mode
	 */
	TIMx_CHANNEL_OC_FAST_ENABLE = 0x01
} tim_channel_oc_fast_t;

/**
 * @enum `tim_channel_oc_clear_t`
 * @brief Timer Channel Output Compare Clear Configuration.
 * @brief Used to clear the effect of an event on the trigger in input on the CC output
 * @note This enum defines the clear configuration for the Output Compare (OC) feature
 */
typedef enum {
	/**
	 * @brief - Channel Output Compare Clear Disable
	 * @brief - OCxRef is not affected by the ETRF input
	 */
	TIMx_CHANNEL_OC_CLEAR_DISABLE = 0x00,
	/**
	 * @brief - Channel Output Compare Clear Enable
	 * @brief - OCxRef is cleared as soon as a High level is detected on ETRF input
	 */
	TIMx_CHANNEL_OC_CLEAR_ENABLE = 0x01
} tim_channel_oc_clear_t;

/**
 * @enum `tim_channel_polarity_t`
 * @brief Channel Polarity Configuration
 * @note This enum defines the polarity of the PWM signal for each channel
 */
typedef enum {
	/**
	 * @brief Channel Active High
	 * @note The PWM signal is active high
	 */
	TIMx_CHANNEL_POLARITY_HIGH = 0x00,
	/**
	 * @brief Channel Active Low
	 * @note The PWM signal is active low
	 */
	TIMx_CHANNEL_POLARITY_LOW = 0x01
} tim_channel_polarity_t;

// Max Counter Value for PWM
#define PWM_DEFAULT_ARR						((uint16_t) 999)

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

/*********************************************** Helper Functions ***********************************************/
// Size of an array
// #define SIZEOF(X)							(sizeof((X))/sizeof((X)[0]))

/**
 * @brief Check if a number is a power of 2
 * @param num The number to check
 * @returns 0: Not a power of 2
 * @returns 1: Power of 2
 */
__STATIC_INLINE__ uint8_t Is_Power_Of_2(uint16_t num) {
	// Check if the number is a power of two
	return (num && (!(num & (num - 1))));
}

/**
 * @brief Rounds up a number to the next power of 2
 * @param n The number to round up 
 * @return Rounded up power of 2
 */
__STATIC_INLINE__ uint16_t Logical_Round_Up_Power_Of_2(uint16_t n) {
	// Input = 0 -> Output = 1
	if (n == 0) return 1;
	// Step 1: Subtract 1 to handle exact powers of 2
	n--;
	// Step 2: Propagate highest bit to the right
	// NOTE: No need for >>16 because uint16_t is only 16 bits
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	// Step 3: Add 1 to get the next power of 2
	return n + 1;
}

/**
 * @brief Rounds up a number to the next power of 2
 * @param n The number to round up 
 * @return Rounded up power of 2
 */
__STATIC_INLINE__ uint32_t Round_Up_Power_of_2(uint32_t x) {
	// If x is 0, return 1 (2^0)
	if (x == 0)
		return 0x00000001;
	/**
	 * 		Expression						Meaning
	 *		__builtin_clz(x)				Count leading zeros of 32-bit integer
	 * 		32 - __builtin_clz(x)			log₂(x) rounded up to nearest power
	 * 		1 << (32 - __builtin_clz(x))	Next power of 2
	 *  NOTE: clz() returns 32 for input 0, which is undefined behavior — so we always use (size - 1) to avoid that
	 */
	// Calculate the next power of 2 greater than or equal to x
	return (1 << (32 - __builtin_clz(x - 1)));
}

/*********************************************** Helper Functions ***********************************************/

#endif  /* __REG_MAP_H__ */