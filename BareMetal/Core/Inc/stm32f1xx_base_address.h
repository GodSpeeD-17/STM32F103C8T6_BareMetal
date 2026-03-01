/**
 * @file	stm32f1xx_base_address.h
 * @author	Shrey Shah
 * @brief	STM32F1xx Base Address Mapping
 * @version v1.0
 * @date	01-03-2026
 */

// Header Guards
#ifndef STM32F1XX_BASE_ADDRESS_H_
#define STM32F1XX_BASE_ADDRESS_H_

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------
#include "stm32f1xx_base_offset.h"

// ------------------------------------------------------------------------------------------
// Cortex-M3 Core Peripheral Base Addresses
// ------------------------------------------------------------------------------------------
/** @brief System Timer Base (Cortex-M3 Core Peripheral) @def SysTick_BASE_ADDR */
#define SysTick_BASE_ADDR						((uint32_t) 0xE000E010UL)
/** @brief Nested Vectored Interrupt Controller Base @def NVIC_BASE_ADDR */
#define NVIC_BASE_ADDR							((uint32_t) 0xE000E100UL)
/** @brief System Control Block Base @def SCB_BASE_ADDR */
#define SCB_BASE_ADDR							((uint32_t) 0xE000ED00UL)
/** @brief Core Debug Registers Base @def CoreDebug_BASE_ADDR */
#define CoreDebug_BASE_ADDR						((uint32_t) 0xE000EDF0UL)

// ------------------------------------------------------------------------------------------
// Bus Base Address
// ------------------------------------------------------------------------------------------
/** @brief APB1 Peripheral Base (Low-speed peripherals) @def APB1_BASE_ADDR @def APB1_BASE_ADDR */
#define APB1_BASE_ADDR							((uint32_t) 0x40000000UL)
/** @brief APB2 Peripheral Base (High-speed peripherals) @def APB2_BASE_ADDR @def APB2_BASE_ADDR */
#define APB2_BASE_ADDR							((uint32_t) 0x40010000UL)
/** @brief AHB Peripheral Base (Memory, DMA, CRC) @def AHB_BASE_ADDR @def AHB_BASE_ADDR */
#define AHB_BASE_ADDR							((uint32_t) 0x40018000UL)

// ------------------------------------------------------------------------------------------
// AHB Peripheral Base Addresses
// ------------------------------------------------------------------------------------------
/** @brief DMA1 Controller Base @def DMA1_BASE_ADDR */
#define DMA1_BASE_ADDR							((uint32_t) (AHB_BASE_ADDR + DMA1_OFFSET))
/** @brief DMA2 Controller Base @def DMA2_BASE_ADDR */
#define DMA2_BASE_ADDR							((uint32_t) (AHB_BASE_ADDR + DMA2_OFFSET))
/** @brief RCC Peripheral Base Address @def RCC_BASE_ADDRESS  */
#define RCC_BASE_ADDRESS						((uint32_t) (AHB_BASE_ADDR + RCC_OFFSET))
/** @brief Flash Memory Interface Base @def FLASH_BASE_ADDR */
#define FLASH_BASE_ADDR							((uint32_t) (AHB_BASE_ADDR + FLASH_OFFSET))

// ------------------------------------------------------------------------------------------
// APB1 Peripheral Base Addresses
// ------------------------------------------------------------------------------------------
/** @brief General-purpose Timer 2 Base Memory Address @def TIM2_BASE_ADDRESS */
#define TIM2_BASE_ADDRESS						((uint32_t) (APB1_BASE_ADDR + TIM2_OFFSET))
/** @brief General-purpose Timer 3 Base Memory Address @def TIM3_BASE_ADDRESS */
#define TIM3_BASE_ADDRESS						((uint32_t) (APB1_BASE_ADDR + TIM3_OFFSET))
/** @brief General-purpose Timer 4 Base Memory Address @def TIM4_BASE_ADDRESS */
#define TIM4_BASE_ADDRESS						((uint32_t) (APB1_BASE_ADDR + TIM4_OFFSET))
/** @brief General-purpose Timer 5 Base Memory Address @def TIM5_BASE_ADDRESS */
#define TIM5_BASE_ADDRESS						((uint32_t) (APB1_BASE_ADDR + TIM5_OFFSET))
/** @brief Basic Timer 6 Base Memory Address @def TIM6_BASE_ADDRESS */
#define TIM6_BASE_ADDRESS						((uint32_t) (APB1_BASE_ADDR + TIM6_OFFSET))
/** @brief Basic Timer 7 Base Memory Address @def TIM7_BASE_ADDRESS */
#define TIM7_BASE_ADDRESS						((uint32_t) (APB1_BASE_ADDR + TIM7_OFFSET))
/** @brief USART2 Base Memory Address @def USART2_BASE_ADDRESS */
#define USART2_BASE_ADDRESS						((uint32_t) (APB1_BASE_ADDR + USART2_OFFSET))
/** @brief USART3 Base Memory Address @def USART3_BASE_ADDRESS */
#define USART3_BASE_ADDRESS						((uint32_t) (APB1_BASE_ADDR + USART3_OFFSET))
/** @brief I2C1 Base Memory Address @def I2C1_BASE_ADDRESS */
#define I2C1_BASE_ADDRESS						((uint32_t) (APB1_BASE_ADDR + I2C1_OFFSET))
/** @brief I2C2 Base Memory Address @def I2C2_BASE_ADDRESS */
#define I2C2_BASE_ADDRESS						((uint32_t) (APB1_BASE_ADDR + I2C2_OFFSET))
/** @brief Window Watchdog Base @def WWDG_BASE_ADDR */
#define WWDG_BASE_ADDR							((uint32_t) (APB1_BASE_ADDR + WWDG_OFFSET))
/** @brief Independent Watchdog Base @def IWDG_BASE_ADDR */
#define IWDG_BASE_ADDR							((uint32_t) (APB1_BASE_ADDR + IWDG_OFFSET))

// ------------------------------------------------------------------------------------------
// APB2 Peripheral Base Addresses
// ------------------------------------------------------------------------------------------
/** @brief AFIO Base Memory Address @def AFIO_BASE_ADDRESS */
#define AFIO_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + AFIO_OFFSET))
/** @brief EXTI Base Memory Address @def EXTI_BASE_ADDRESS */
#define EXTI_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + EXTI_OFFSET))
/** @brief GPIOA Base Memory Address @def GPIOA_BASE_ADDRESS */
#define GPIOA_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + GPIOA_OFFSET))
/** @brief GPIOB Base Memory Address @def GPIOB_BASE_ADDRESS */
#define GPIOB_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + GPIOB_OFFSET))
/** @brief GPIOC Base Memory Address @def GPIOC_BASE_ADDRESS */
#define GPIOC_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + GPIOC_OFFSET))
/** @brief GPIOD Base Memory Address @def GPIOD_BASE_ADDRESS */
#define GPIOD_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + GPIOD_OFFSET))
/** @brief GPIOE Base Memory Address @def GPIOE_BASE_ADDRESS */
#define GPIOE_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + GPIOE_OFFSET))
/** @brief GPIOF Base Memory Address @def GPIOF_BASE_ADDRESS */
#define GPIOF_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + GPIOF_OFFSET))
/** @brief GPIOG Base Memory Address @def GPIOG_BASE_ADDRESS */
#define GPIOG_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + GPIOG_OFFSET))
/** @brief ADC1 Base Memory Address @def ADC1_BASE_ADDRESS */
#define ADC1_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + ADC1_OFFSET))
/** @brief ADC2 Base Memory Address @def ADC2_BASE_ADDRESS */
#define ADC2_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + ADC2_OFFSET))
/** @brief TIM1 Base Memory Address @def TIM1_BASE_ADDRESS */
#define TIM1_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + TIM1_OFFSET))
/** @brief TIM8 Base Memory Address @def TIM8_BASE_ADDRESS */
#define TIM8_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + TIM8_OFFSET))
/** @brief USART1 Base Memory Address @def USART1_BASE_ADDRESS */
#define USART1_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + USART1_OFFSET))
/** @brief ADC3 Base Memory Address @def ADC3_BASE_ADDRESS */
#define ADC3_BASE_ADDRESS						((uint32_t) (APB2_BASE_ADDR + ADC3_OFFSET))

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_BASE_ADDRESS_H_ */
