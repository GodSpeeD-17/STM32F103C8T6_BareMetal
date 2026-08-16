/**
 * @file	nvic_defines.h
 * @author	Shrey Shah
 * @brief	NVIC Driver Selector and Capability Defines
 * @version	v2.1
 * @date	16-08-2026
 *
 * @details
 * This header owns the public STM32F103C8T6 external IRQ numbers, exact-target
 * capability limits, and logical NVIC priority-group selectors. Register-bank
 * indexes, action masks, raw AIRCR values, and IPR field encodings remain
 * private to the NVIC Driver and Codec implementation layers.
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
 * @addtogroup NVIC_03_Driver
 * @{
 */

/**
 * @brief NVIC public selector and exact-target capability defines
 * @defgroup NVIC_03_Driver_02_Defines NVIC Driver Defines
 * @ingroup NVIC_03_Driver
 * @details
 * These definitions expose semantic application vocabulary only. Raw NVIC
 * and SCB register mechanics are deliberately excluded from the public layer.
 * @{
 */

// ==================================================================================================== //
//								NVIC Exact-Target Capability Defines								//
// ==================================================================================================== //

/**
 * @brief STM32F103C8T6 external IRQ capability limits
 * @defgroup NVIC_03_Driver_02_Defines_01_Capability NVIC Capability Defines
 * @ingroup NVIC_03_Driver_02_Defines
 * @{
 */

/** @brief First STM32F103C8T6 external IRQ number @def NVIC_IRQ_NUMBER_FIRST */
#define NVIC_IRQ_NUMBER_FIRST		((irq_t) 0x00U)
/** @brief Last STM32F103C8T6 external IRQ number @def NVIC_IRQ_NUMBER_LAST */
#define NVIC_IRQ_NUMBER_LAST		((irq_t) 0x2AU)
/** @brief Number of STM32F103C8T6 external IRQ channels @def NVIC_IRQ_NUMBER_COUNT */
#define NVIC_IRQ_NUMBER_COUNT		((uint8_t) 0x2BU)

/** @} */ // NVIC_03_Driver_02_Defines_01_Capability

// ==================================================================================================== //
//									NVIC Interrupt Request Numbers									//
// ==================================================================================================== //

/**
 * @brief STM32F103C8T6 external interrupt request numbers
 * @defgroup NVIC_03_Driver_02_Defines_02_IRQn NVIC Interrupt Request Numbers
 * @ingroup NVIC_03_Driver_02_Defines
 * @details
 * Values map one-to-one to external vector-table entries 0 through 42. Shared
 * names retain every peripheral source represented by the physical vector.
 * @{
 */

/** @brief Window watchdog interrupt request number @def WWDG_IRQn */
#define WWDG_IRQn				((irq_t) 0U)
/** @brief Programmable voltage detector through EXTI interrupt request number @def PVD_IRQn */
#define PVD_IRQn				((irq_t) 1U)
/** @brief Tamper interrupt request number @def TAMPER_IRQn */
#define TAMPER_IRQn				((irq_t) 2U)
/** @brief RTC global interrupt request number @def RTC_IRQn */
#define RTC_IRQn				((irq_t) 3U)
/** @brief Flash global interrupt request number @def FLASH_IRQn */
#define FLASH_IRQn				((irq_t) 4U)
/** @brief RCC global interrupt request number @def RCC_IRQn */
#define RCC_IRQn				((irq_t) 5U)
/** @brief EXTI line 0 interrupt request number @def EXTI0_IRQn */
#define EXTI0_IRQn				((irq_t) 6U)
/** @brief EXTI line 1 interrupt request number @def EXTI1_IRQn */
#define EXTI1_IRQn				((irq_t) 7U)
/** @brief EXTI line 2 interrupt request number @def EXTI2_IRQn */
#define EXTI2_IRQn				((irq_t) 8U)
/** @brief EXTI line 3 interrupt request number @def EXTI3_IRQn */
#define EXTI3_IRQn				((irq_t) 9U)
/** @brief EXTI line 4 interrupt request number @def EXTI4_IRQn */
#define EXTI4_IRQn				((irq_t) 10U)
/** @brief DMA1 channel 1 global interrupt request number @def DMA1_Channel1_IRQn */
#define DMA1_Channel1_IRQn		((irq_t) 11U)
/** @brief DMA1 channel 2 global interrupt request number @def DMA1_Channel2_IRQn */
#define DMA1_Channel2_IRQn		((irq_t) 12U)
/** @brief DMA1 channel 3 global interrupt request number @def DMA1_Channel3_IRQn */
#define DMA1_Channel3_IRQn		((irq_t) 13U)
/** @brief DMA1 channel 4 global interrupt request number @def DMA1_Channel4_IRQn */
#define DMA1_Channel4_IRQn		((irq_t) 14U)
/** @brief DMA1 channel 5 global interrupt request number @def DMA1_Channel5_IRQn */
#define DMA1_Channel5_IRQn		((irq_t) 15U)
/** @brief DMA1 channel 6 global interrupt request number @def DMA1_Channel6_IRQn */
#define DMA1_Channel6_IRQn		((irq_t) 16U)
/** @brief DMA1 channel 7 global interrupt request number @def DMA1_Channel7_IRQn */
#define DMA1_Channel7_IRQn		((irq_t) 17U)
/** @brief Shared ADC1 and ADC2 global interrupt request number @def ADC1_2_IRQn */
#define ADC1_2_IRQn				((irq_t) 18U)
/** @brief Shared USB high-priority and CAN transmit interrupt request number @def USB_HP_CAN_TX_IRQn */
#define USB_HP_CAN_TX_IRQn		((irq_t) 19U)
/** @brief Shared USB low-priority and CAN receive FIFO 0 interrupt request number @def USB_LP_CAN_RX0_IRQn */
#define USB_LP_CAN_RX0_IRQn		((irq_t) 20U)
/** @brief CAN receive FIFO 1 interrupt request number @def CAN_RX1_IRQn */
#define CAN_RX1_IRQn			((irq_t) 21U)
/** @brief CAN status-change and error interrupt request number @def CAN_SCE_IRQn */
#define CAN_SCE_IRQn			((irq_t) 22U)
/** @brief Shared EXTI lines 5 through 9 interrupt request number @def EXTI9_5_IRQn */
#define EXTI9_5_IRQn			((irq_t) 23U)
/** @brief TIM1 break interrupt request number @def TIM1_BRK_IRQn */
#define TIM1_BRK_IRQn			((irq_t) 24U)
/** @brief TIM1 update interrupt request number @def TIM1_UP_IRQn */
#define TIM1_UP_IRQn			((irq_t) 25U)
/** @brief TIM1 trigger and commutation interrupt request number @def TIM1_TRG_COM_IRQn */
#define TIM1_TRG_COM_IRQn		((irq_t) 26U)
/** @brief TIM1 capture/compare interrupt request number @def TIM1_CC_IRQn */
#define TIM1_CC_IRQn			((irq_t) 27U)
/** @brief TIM2 global interrupt request number @def TIM2_IRQn */
#define TIM2_IRQn				((irq_t) 28U)
/** @brief TIM3 global interrupt request number @def TIM3_IRQn */
#define TIM3_IRQn				((irq_t) 29U)
/** @brief TIM4 global interrupt request number @def TIM4_IRQn */
#define TIM4_IRQn				((irq_t) 30U)
/** @brief I2C1 event interrupt request number @def I2C1_EV_IRQn */
#define I2C1_EV_IRQn			((irq_t) 31U)
/** @brief I2C1 error interrupt request number @def I2C1_ER_IRQn */
#define I2C1_ER_IRQn			((irq_t) 32U)
/** @brief I2C2 event interrupt request number @def I2C2_EV_IRQn */
#define I2C2_EV_IRQn			((irq_t) 33U)
/** @brief I2C2 error interrupt request number @def I2C2_ER_IRQn */
#define I2C2_ER_IRQn			((irq_t) 34U)
/** @brief SPI1 global interrupt request number @def SPI1_IRQn */
#define SPI1_IRQn				((irq_t) 35U)
/** @brief SPI2 global interrupt request number @def SPI2_IRQn */
#define SPI2_IRQn				((irq_t) 36U)
/** @brief USART1 global interrupt request number @def USART1_IRQn */
#define USART1_IRQn				((irq_t) 37U)
/** @brief USART2 global interrupt request number @def USART2_IRQn */
#define USART2_IRQn				((irq_t) 38U)
/** @brief USART3 global interrupt request number @def USART3_IRQn */
#define USART3_IRQn				((irq_t) 39U)
/** @brief Shared EXTI lines 10 through 15 interrupt request number @def EXTI15_10_IRQn */
#define EXTI15_10_IRQn			((irq_t) 40U)
/** @brief RTC alarm through EXTI interrupt request number @def RTCAlarm_IRQn */
#define RTCAlarm_IRQn			((irq_t) 41U)
/** @brief USB wakeup from suspend interrupt request number @def USBWakeUp_IRQn */
#define USBWakeUp_IRQn			((irq_t) 42U)

/** @} */ // NVIC_03_Driver_02_Defines_02_IRQn

// ==================================================================================================== //
//									NVIC Priority Selector Limits									//
// ==================================================================================================== //

/**
 * @brief Logical NVIC priority selector limits
 * @defgroup NVIC_03_Driver_02_Defines_03_PriorityLimits NVIC Priority Selector Limits
 * @ingroup NVIC_03_Driver_02_Defines
 * @details
 * STM32F103C8T6 implements four priority bits. The active priority group
 * determines how these four bits divide between preemption and sub-priority.
 * @{
 */

/** @brief Lowest representable logical NVIC priority selector @def NVIC_PRIORITY_VALUE_MIN */
#define NVIC_PRIORITY_VALUE_MIN		((uint8_t) 0x00U)
/** @brief Highest representable logical NVIC priority selector @def NVIC_PRIORITY_VALUE_MAX */
#define NVIC_PRIORITY_VALUE_MAX		((uint8_t) 0x0FU)

/** @} */ // NVIC_03_Driver_02_Defines_03_PriorityLimits

// ==================================================================================================== //
//									NVIC Priority Group Selectors								//
// ==================================================================================================== //

/**
 * @brief Logical NVIC priority-group selectors
 * @defgroup NVIC_03_Driver_02_Defines_04_PriorityGroup NVIC Priority Group Selectors
 * @ingroup NVIC_03_Driver_02_Defines
 * @details
 * Logical groups map to AIRCR `PRIGROUP` values 7 through 3 while presenting
 * preemption-bit count directly to the Driver and Codec layers.
 * @{
 */

/** @brief Group 0 with zero preemption bits and four sub-priority bits @def NVIC_PRIO_GROUP_0 */
#define NVIC_PRIO_GROUP_0		((nvic_priority_group_t) 0x00U)
/** @brief Group 1 with one preemption bit and three sub-priority bits @def NVIC_PRIO_GROUP_1 */
#define NVIC_PRIO_GROUP_1		((nvic_priority_group_t) 0x01U)
/** @brief Group 2 with two preemption bits and two sub-priority bits @def NVIC_PRIO_GROUP_2 */
#define NVIC_PRIO_GROUP_2		((nvic_priority_group_t) 0x02U)
/** @brief Group 3 with three preemption bits and one sub-priority bit @def NVIC_PRIO_GROUP_3 */
#define NVIC_PRIO_GROUP_3		((nvic_priority_group_t) 0x03U)
/** @brief Group 4 with four preemption bits and zero sub-priority bits @def NVIC_PRIO_GROUP_4 */
#define NVIC_PRIO_GROUP_4		((nvic_priority_group_t) 0x04U)

/** @} */ // NVIC_03_Driver_02_Defines_04_PriorityGroup

/** @} */ // NVIC_03_Driver_02_Defines

/** @} */ // NVIC_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_DEFINES_H_ */
