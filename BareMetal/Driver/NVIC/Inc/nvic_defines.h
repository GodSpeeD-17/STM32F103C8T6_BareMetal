/**
 * @file	nvic_defines.h
 * @author	Shrey Shah
 * @brief	NVIC Driver Defines
 * @version	v2.0
 * @date	16-08-2026
 *
 * @details
 * This header exposes only semantic STM32F103C8T6 IRQ and priority selectors.
 * Register indexes, action masks, raw AIRCR values, and IPR encoding details
 * remain private to the NVIC implementation layers.
 */

// Header Guards
#ifndef NVIC_DEFINES_H_
#define NVIC_DEFINES_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "nvic_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup NVIC_02_Defines NVIC Driver Defines
 * @ingroup NVIC_Driver
 * @brief Exact-target IRQ and logical-priority selectors
 * @{
 */

/** @brief First STM32F103C8T6 external IRQ number @def NVIC_IRQ_NUMBER_FIRST */
#define NVIC_IRQ_NUMBER_FIRST							((irq_t) 0x00U)
/** @brief Last STM32F103C8T6 external IRQ number @def NVIC_IRQ_NUMBER_LAST */
#define NVIC_IRQ_NUMBER_LAST							((irq_t) 0x2AU)
/** @brief Number of STM32F103C8T6 external IRQ channels @def NVIC_IRQ_NUMBER_COUNT */
#define NVIC_IRQ_NUMBER_COUNT							((uint8_t) 0x2BU)

/** @brief Lowest representable logical priority selector @def NVIC_PRIORITY_VALUE_MIN */
#define NVIC_PRIORITY_VALUE_MIN						((uint8_t) 0x00U)
/** @brief Highest representable logical priority selector @def NVIC_PRIORITY_VALUE_MAX */
#define NVIC_PRIORITY_VALUE_MAX						((uint8_t) 0x0FU)

/** @} */ // NVIC_02_Defines

// ==================================================================================================== //
//									NVIC Interrupt Numbers									//
// ==================================================================================================== //

/**
 * @defgroup NVIC_02_Defines_01_IRQn NVIC Interrupt Request Numbers
 * @ingroup NVIC_02_Defines
 * @brief STM32F103C8T6 external interrupt request numbers
 * @{
 */

#define WWDG_IRQn									((irq_t) 0U)
#define PVD_IRQn									((irq_t) 1U)
#define TAMPER_IRQn								((irq_t) 2U)
#define RTC_IRQn									((irq_t) 3U)
#define FLASH_IRQn									((irq_t) 4U)
#define RCC_IRQn									((irq_t) 5U)
#define EXTI0_IRQn									((irq_t) 6U)
#define EXTI1_IRQn									((irq_t) 7U)
#define EXTI2_IRQn									((irq_t) 8U)
#define EXTI3_IRQn									((irq_t) 9U)
#define EXTI4_IRQn									((irq_t) 10U)
#define DMA1_Channel1_IRQn							((irq_t) 11U)
#define DMA1_Channel2_IRQn							((irq_t) 12U)
#define DMA1_Channel3_IRQn							((irq_t) 13U)
#define DMA1_Channel4_IRQn							((irq_t) 14U)
#define DMA1_Channel5_IRQn							((irq_t) 15U)
#define DMA1_Channel6_IRQn							((irq_t) 16U)
#define DMA1_Channel7_IRQn							((irq_t) 17U)
#define ADC1_2_IRQn									((irq_t) 18U)
#define USB_HP_CAN_TX_IRQn							((irq_t) 19U)
#define USB_LP_CAN_RX0_IRQn							((irq_t) 20U)
#define CAN_RX1_IRQn									((irq_t) 21U)
#define CAN_SCE_IRQn									((irq_t) 22U)
#define EXTI9_5_IRQn									((irq_t) 23U)
#define TIM1_BRK_IRQn								((irq_t) 24U)
#define TIM1_UP_IRQn									((irq_t) 25U)
#define TIM1_TRG_COM_IRQn							((irq_t) 26U)
#define TIM1_CC_IRQn									((irq_t) 27U)
#define TIM2_IRQn									((irq_t) 28U)
#define TIM3_IRQn									((irq_t) 29U)
#define TIM4_IRQn									((irq_t) 30U)
#define I2C1_EV_IRQn								((irq_t) 31U)
#define I2C1_ER_IRQn								((irq_t) 32U)
#define I2C2_EV_IRQn								((irq_t) 33U)
#define I2C2_ER_IRQn								((irq_t) 34U)
#define SPI1_IRQn									((irq_t) 35U)
#define SPI2_IRQn									((irq_t) 36U)
#define USART1_IRQn									((irq_t) 37U)
#define USART2_IRQn									((irq_t) 38U)
#define USART3_IRQn									((irq_t) 39U)
#define EXTI15_10_IRQn								((irq_t) 40U)
#define RTCAlarm_IRQn								((irq_t) 41U)
#define USBWakeUp_IRQn								((irq_t) 42U)

/** @} */ // NVIC_02_Defines_01_IRQn

// ==================================================================================================== //
//									NVIC Priority Group Selectors								//
// ==================================================================================================== //

/**
 * @defgroup NVIC_02_Defines_02_PriorityGroup NVIC Priority Group Selectors
 * @ingroup NVIC_02_Defines
 * @brief Logical priority-group selectors used by @ref `NVIC_SetPriorityGroup`
 * @{
 */

/** @brief Group 0: zero preemption bits and four sub-priority bits @def NVIC_PRIO_GROUP_0 */
#define NVIC_PRIO_GROUP_0							((nvic_priority_group_t) 0x00U)
/** @brief Group 1: one preemption bit and three sub-priority bits @def NVIC_PRIO_GROUP_1 */
#define NVIC_PRIO_GROUP_1							((nvic_priority_group_t) 0x01U)
/** @brief Group 2: two preemption bits and two sub-priority bits @def NVIC_PRIO_GROUP_2 */
#define NVIC_PRIO_GROUP_2							((nvic_priority_group_t) 0x02U)
/** @brief Group 3: three preemption bits and one sub-priority bit @def NVIC_PRIO_GROUP_3 */
#define NVIC_PRIO_GROUP_3							((nvic_priority_group_t) 0x03U)
/** @brief Group 4: four preemption bits and zero sub-priority bits @def NVIC_PRIO_GROUP_4 */
#define NVIC_PRIO_GROUP_4							((nvic_priority_group_t) 0x04U)

/** @} */ // NVIC_02_Defines_02_PriorityGroup

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_DEFINES_H_ */
