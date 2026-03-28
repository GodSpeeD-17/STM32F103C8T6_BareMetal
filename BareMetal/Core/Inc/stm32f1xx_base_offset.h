/**
 * @file stm32f1xx_base_offset.h
 * @author Shrey Shah
 * @brief 
 * @version v1.0
 * @date 01-03-2026
 */

// Header Guards
#ifndef STM32F1XX_BASE_OFFSET_H_
#define STM32F1XX_BASE_OFFSET_H_

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------
#include "stm32f1xx_data_types.h"

// ------------------------------------------------------------------------------------------
// AHB Peripheral Offset
// ------------------------------------------------------------------------------------------
/** @brief DMA1 Peripheral Offset from @def `AHB_BASE_ADDR` @def DMA1_OFFSET */
#define DMA1_OFFSET								((uint32_t) 0x00008000UL)
/** @brief DMA2 Peripheral Offset from @def `AHB_BASE_ADDR` @def DMA2_OFFSET */
#define DMA2_OFFSET								((uint32_t) 0x00008400UL)
/** @brief RCC Peripheral Offset from @def `AHB_BASE_ADDR` @def RCC_OFFSET */
#define RCC_OFFSET								((uint32_t) 0x00009000UL)
/** @brief Flash Offset from @def `AHB_BASE_ADDR` @def FLASH_OFFSET */
#define FLASH_OFFSET							((uint32_t) 0x0000A000UL)
/** @brief CRC Offset from @def `AHB_BASE_ADDR` @def CRC_OFFSET */
#define CRC_OFFSET								((uint32_t) 0x0000B000UL)

// ------------------------------------------------------------------------------------------
// APB1 Peripheral Offset
// ------------------------------------------------------------------------------------------

/** @brief TIM2 offset from @ref `APB1_BASE_ADDR` @def TIM2_OFFSET */
#define TIM2_OFFSET								((uint32_t) 0x00000000UL)
/** @brief TIM3 offset from @ref `APB1_BASE_ADDR` @def TIM3_OFFSET */
#define TIM3_OFFSET								((uint32_t) 0x00000400UL)
/** @brief TIM4 offset from @ref `APB1_BASE_ADDR` @def TIM4_OFFSET */
#define TIM4_OFFSET								((uint32_t) 0x00000800UL)
/** @brief TIM5 offset from @ref `APB1_BASE_ADDR` @def TIM5_OFFSET */
#define TIM5_OFFSET								((uint32_t) 0x00000C00UL)
/** @brief TIM6 offset from @ref `APB1_BASE_ADDR` @def TIM6_OFFSET */
#define TIM6_OFFSET								((uint32_t) 0x00001000UL)
/** @brief TIM7 offset from @ref `APB1_BASE_ADDR` @def TIM7_OFFSET */
#define TIM7_OFFSET								((uint32_t) 0x00001400UL)
/** @brief WWDG offset from @ref `APB1_BASE_ADDR` @def WWDG_OFFSET */
#define WWDG_OFFSET								((uint32_t) 0x00002C00UL)
/** @brief IWDG offset from @ref `APB1_BASE_ADDR` @def IWDG_OFFSET */
#define IWDG_OFFSET								((uint32_t) 0x00003000UL)
/** @brief USART2 offset from @ref `APB1_BASE_ADDR` @def USART2_OFFSET */
#define USART2_OFFSET							((uint32_t) 0x00004400UL)
/** @brief USART3 offset from @ref `APB1_BASE_ADDR` @def USART3_OFFSET */
#define USART3_OFFSET							((uint32_t) 0x00004800UL)
/** @brief I2C1 Peripheral Offset @def I2C1_OFFSET */ 
#define I2C1_OFFSET								((uint32_t) 0x00005400UL)
/** @brief I2C2 Peripheral Offset @def I2C2_OFFSET */
#define I2C2_OFFSET								((uint32_t) 0x00005800UL)

// ------------------------------------------------------------------------------------------
// APB2 Peripheral Offset
// ------------------------------------------------------------------------------------------

/** @brief AFIO offset from @ref `APB2_BASE_ADDR` @def AFIO_OFFSET */
#define AFIO_OFFSET								((uint32_t) 0x00000000UL)
/** @brief EXTI offset from @ref `APB2_BASE_ADDR` @def EXTI_OFFSET */
#define EXTI_OFFSET								((uint32_t) 0x00000400UL)
/** @brief GPIO Port A offset from @ref `APB2_BASE_ADDR` @def GPIOA_OFFSET */
#define GPIOA_OFFSET							((uint32_t) 0x00000800UL)
/** @brief GPIO Port B offset from @ref `APB2_BASE_ADDR` @def GPIOB_OFFSET */
#define GPIOB_OFFSET							((uint32_t) 0x00000C00UL)
/** @brief GPIO Port C offset from @ref `APB2_BASE_ADDR` @def GPIOC_OFFSET */
#define GPIOC_OFFSET							((uint32_t) 0x00001000UL)
/** @brief GPIO Port D offset from @ref `APB2_BASE_ADDR` @def GPIOD_OFFSET */
#define GPIOD_OFFSET							((uint32_t) 0x00001400UL)
/** @brief GPIO Port E offset from @ref `APB2_BASE_ADDR` @def GPIOE_OFFSET */
#define GPIOE_OFFSET							((uint32_t) 0x00001800UL)
/** @brief GPIO Port F offset from @ref `APB2_BASE_ADDR` @def GPIOF_OFFSET */
#define GPIOF_OFFSET							((uint32_t) 0x00001C00UL)
/** @brief GPIO Port G offset from @ref `APB2_BASE_ADDR` @def GPIOG_OFFSET */
#define GPIOG_OFFSET							((uint32_t) 0x00002000UL)
/** @brief ADC1 offset from @ref `APB2_BASE_ADDR` @def ADC1_OFFSET */
#define ADC1_OFFSET								((uint32_t) 0x00002400UL)
/** @brief ADC2 offset from @ref `APB2_BASE_ADDR` @def ADC2_OFFSET */
#define ADC2_OFFSET								((uint32_t) 0x00002800UL)
/** @brief TIM1 offset from @ref `APB2_BASE_ADDR` @def TIM1_OFFSET */
#define TIM1_OFFSET								((uint32_t) 0x00002C00UL)
/** @brief TIM8 offset from @ref `APB2_BASE_ADDR` @def TIM8_OFFSET */
#define TIM8_OFFSET								((uint32_t) 0x00003400UL)
/** @brief USART1 offset from @ref `APB2_BASE_ADDR` @def USART1_OFFSET */
#define USART1_OFFSET							((uint32_t) 0x00003800UL)
/** @brief ADC3 offset from @ref `APB2_BASE_ADDR` @def ADC3_OFFSET */
#define ADC3_OFFSET								((uint32_t) 0x00003C00UL)

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_BASE_OFFSET_H_ */
