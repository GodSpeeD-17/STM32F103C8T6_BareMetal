/**
 * @file    nvic_types.h
 * @author  Shrey Shah
 * @brief   STM32F1xx - NVIC Interrupt Types and Definitions
 * @version v1.2
 * @date    21-10-2025
 *
 * 
 * @details This module defines all interrupt numbers (IRQn) and types used with the
 *          NVIC (Nested Vectored Interrupt Controller) for STM32F1xx microcontrollers.
 *          Includes definitions for all peripheral interrupts and system exceptions.
 *
 * @note Interrupt numbers follow the Cortex-M3 exception model
 * @see Reference Manual RM0008 - Section 10.2.2 Interrupt and exception vectors
 * @see Cortex-M3 Technical Reference Manual - Section 5.2.3 Exception types
 *
 */

#ifndef NVIC_TYPES_H_
#define NVIC_TYPES_H_

#include <stdint.h>

/*********************************************** NVIC Interrupt Numbers ***********************************************/

/**
 * @brief    STM32F1xx Peripheral Interrupt Request Numbers
 * @defgroup NVIC_IRQn NVIC Interrupt Numbers
 * @ingroup  NVIC
 *
 * @details These constants represent the interrupt numbers for all STM32F1xx peripherals.
 *          Used with NVIC functions to enable, disable, and configure interrupts.
 *
 * @note Interrupt numbers 0-67 are available on STM32F103xx devices
 * @warning Not all interrupts are available on all STM32F1xx variants
 * @see Reference Manual RM0008 - Table 63 Vector table
 * @{
 */

/**
 * @brief Interrupt Request Number Type
 * @details 8-bit type representing interrupt numbers (0-67 for STM32F103xx)
 */
typedef uint8_t 								irq_t;

/**
 * @addtogroup NVIC_IRQn
 * @section NVIC_IRQn_0 System and Window Watchdog
 * @{
 */

/** @brief Window Watchdog interrupt */
#define WWDG_IRQn                               ((irq_t) 0)
/** @brief PVD through EXTI line detection */
#define PVD_IRQn                                ((irq_t) 1)
/** @brief Tamper interrupt */
#define TAMPER_IRQn                             ((irq_t) 2)
/** @brief RTC global interrupt */
#define RTC_IRQn                                ((irq_t) 3)
/** @brief Flash global interrupt */
#define FLASH_IRQn                              ((irq_t) 4)
/** @brief RCC global interrupt */
#define RCC_IRQn                                ((irq_t) 5)
/**
 * @}
 */ // NVIC_IRQn_0

/**
 * @addtogroup NVIC_IRQn 
 * @defgroup NVIC_IRQn_1 External Interrupts
 * @{
 */
/** @brief EXTI Line0 interrupt */
#define EXTI0_IRQn                              ((irq_t) 6)
/** @brief EXTI Line1 interrupt */
#define EXTI1_IRQn                              ((irq_t) 7)
/** @brief EXTI Line2 interrupt */
#define EXTI2_IRQn                              ((irq_t) 8)
/** @brief EXTI Line3 interrupt */
#define EXTI3_IRQn                              ((irq_t) 9)
/** @brief EXTI Line4 interrupt */
#define EXTI4_IRQn                              ((irq_t) 10)
/**
 * @}
 */ // NVIC_IRQn_1

/* DMA Interrupts */
/** @brief DMA1 Channel1 global interrupt */
#define DMA1_Channel1_IRQn                      ((irq_t) 11)
/** @brief DMA1 Channel2 global interrupt */
#define DMA1_Channel2_IRQn                      ((irq_t) 12)
/** @brief DMA1 Channel3 global interrupt */
#define DMA1_Channel3_IRQn                      ((irq_t) 13)
/** @brief DMA1 Channel4 global interrupt */
#define DMA1_Channel4_IRQn                      ((irq_t) 14)
/** @brief DMA1 Channel5 global interrupt */
#define DMA1_Channel5_IRQn                      ((irq_t) 15)
/** @brief DMA1 Channel6 global interrupt */
#define DMA1_Channel6_IRQn                      ((irq_t) 16)
/** @brief DMA1 Channel7 global interrupt */
#define DMA1_Channel7_IRQn                      ((irq_t) 17)

/* Analog and USB/CAN Interrupts */
/** @brief ADC1 and ADC2 global interrupts */
#define ADC1_2_IRQn                             ((irq_t) 18)
/** @brief USB High Priority or CAN TX interrupts */
#define USB_HP_CAN_TX_IRQ                       ((irq_t) 19)
/** @brief USB Low Priority or CAN RX0 interrupts */
#define USB_LP_CAN_RX0_IRQ                      ((irq_t) 20)
/** @brief CAN RX1 interrupt */
#define CAN_RX1_IRQ                             ((irq_t) 21)
/** @brief CAN SCE interrupt */
#define CAN_SCE_IRQ                             ((irq_t) 22)

// External Interrupt Groups
/** @brief EXTI Line[9:5] interrupts */
#define EXTI9_5_IRQn                            ((irq_t) 23)

// Timer Interrupts
/** @brief TIM1 Break interrupt */
#define TIM1_BRK_IRQn                           ((irq_t) 24)
/** @brief TIM1 Update interrupt */
#define TIM1_UP_IRQn                            ((irq_t) 25)
/** @brief TIM1 Trigger and Commutation */
#define TIM1_TRG_COM_IRQn                       ((irq_t) 26)
/** @brief TIM1 Capture Compare interrupt */
#define TIM1_CC_IRQn                            ((irq_t) 27)
/** @brief TIM2 global interrupt */
#define TIM2_IRQn                               ((irq_t) 28)
/** @brief TIM3 global interrupt */
#define TIM3_IRQn                               ((irq_t) 29)
/** @brief TIM4 global interrupt */
#define TIM4_IRQn                               ((irq_t) 30)

/* Communication Interface Interrupts */
/** @brief I2C1 event interrupt */
#define I2C1_EV_IRQn                            ((irq_t) 31)
/** @brief I2C1 error interrupt */
#define I2C1_ER_IRQn                            ((irq_t) 32)
/** @brief I2C2 event interrupt */
#define I2C2_EV_IRQn                            ((irq_t) 33)
/** @brief I2C2 error interrupt */
#define I2C2_ER_IRQn                            ((irq_t) 34)
/** @brief SPI1 global interrupt */
#define SPI1_IRQn                               ((irq_t) 35)
/** @brief SPI2 global interrupt */
#define SPI2_IRQn                               ((irq_t) 36)

/* USART Interrupts */
#define USART1_IRQn                             ((irq_t) 37)  /**< @brief USART1 global interrupt */
#define USART2_IRQn                             ((irq_t) 38)  /**< @brief USART2 global interrupt */
#define USART3_IRQn                             ((irq_t) 39)  /**< @brief USART3 global interrupt */

/* More External and RTC Interrupts */
#define EXTI15_10_IRQn                          ((irq_t) 40)  /**< @brief EXTI Line[15:10] interrupts */
#define RTC_Alarm_IRQn                          ((irq_t) 41)  /**< @brief RTC Alarm through EXTI line */
#define USBWakeUp_IRQn                          ((irq_t) 42)  /**< @brief USB Wakeup from suspend */

/* Advanced Timer 8 Interrupts */
#define TIM8_BRK_IRQn                           ((irq_t) 43)  /**< @brief TIM8 Break interrupt */
#define TIM8_UP_IRQn                            ((irq_t) 44)  /**< @brief TIM8 Update interrupt */
#define TIM8_TRG_COM_IRQn                       ((irq_t) 45)  /**< @brief TIM8 Trigger and Commutation */
#define TIM8_CC_IRQn                            ((irq_t) 46)  /**< @brief TIM8 Capture Compare interrupt */

/* Additional Peripherals */
#define ADC3_IRQn                               ((irq_t) 47)  /**< @brief ADC3 global interrupt */
#define FMSC_IRQn                               ((irq_t) 48)  /**< @brief FSMC global interrupt */
#define SPI3_IRQn                               ((irq_t) 49)  /**< @brief SPI3 global interrupt */
#define UART4_IRQn                              ((irq_t) 50)  /**< @brief UART4 global interrupt */
#define UART5_IRQn                              ((irq_t) 51)  /**< @brief UART5 global interrupt */

/* Basic Timers */
#define TIM6_IRQn                               ((irq_t) 52)  /**< @brief TIM6 global interrupt */
#define TIM7_IRQn                               ((irq_t) 53)  /**< @brief TIM7 global interrupt */

/* DMA2 Interrupts */
#define DMA2_Channel1_IRQn                      ((irq_t) 56)  /**< @brief DMA2 Channel1 global interrupt */
#define DMA2_Channel2_IRQn                      ((irq_t) 57)  /**< @brief DMA2 Channel2 global interrupt */
#define DMA2_Channel3_IRQn                      ((irq_t) 58)  /**< @brief DMA2 Channel3 global interrupt */
#define DMA2_Channel4_5_IRQn                    ((irq_t) 59)  /**< @brief DMA2 Channel4 and Channel5 global interrupts */

/* Ethernet and CAN2 Interrupts */
#define ETH_IRQn                                ((irq_t) 61)  /**< @brief Ethernet global interrupt */
#define ETH_WakeUp_IRQn                         ((irq_t) 62)  /**< @brief Ethernet Wakeup through EXTI line */
#define CAN2_TX_IRQn                            ((irq_t) 63)  /**< @brief CAN2 TX interrupts */
#define CAN2_RX0_IRQn                           ((irq_t) 64)  /**< @brief CAN2 RX0 interrupts */
#define CAN2_RX1_IRQn                           ((irq_t) 65)  /**< @brief CAN2 RX1 interrupts */
#define CAN2_SCE_IRQn                           ((irq_t) 66)  /**< @brief CAN2 SCE interrupt */

/* USB OTG Interrupt */
#define OTG_FS_IRQn                             ((irq_t) 67)  /**< @brief USB OTG FS global interrupt */

/** @} */ // End of NVIC_IRQn

// --- Helper Macros --- //
#define _IRQn_GET_IPR_REG(X)						((X) >> 2)
#define _IRQn_GET_IPR_REG_INDEX(X)					(((X) & 0x03) << 3)
#define SCB_AICR_WRITE_VALUE						(0x5FA)


// ----- tyepdefs ----- //
typedef uint8_t priority_group_t;
typedef uint8_t priority_t;
typedef uint8_t sub_priority_t;
typedef uint32_t scb_exception_t;

// ------ Priority ------ //
/**
 * @brief Priority group configurations for NVIC priority grouping
 * 
 * @note Priority grouping determines how the 8-bit priority field is split
 *       between preemption priority and sub-priority bits
 */
/** 
 * @brief Group 0: 
 * @brief - 0 bits preemption
 * @brief - 4 bits sub-priority
 * @details 0 preemption levels, 16 sub-priority levels
 * @note - Cooperative systems where no interrupt can preempt others
 * @note - Simple applications, no real-time requirements
 */
#define NVIC_PRIO_GROUP_0							((priority_group_t) 0x00)
/** 
 * @brief Group 1: 
 * @brief - 1 bit preemption
 * @brief - 3 bits sub-priority  
 * @details 2 preemption levels, 8 sub-priority levels
 * @note - Basic two-level system (critical vs normal)
 * @note - Systems with one critical task category
 */
#define NVIC_PRIO_GROUP_1							((priority_group_t) 0x01)
/** 
 * @brief Group 2: 
 * @brief - 2 bits preemption
 * @brief - 2 bits sub-priority
 * @details 4 preemption levels, 4 sub-priority levels
 * @note - Balanced preemption control with good flexibility
 * @note - Most embedded systems - recommended default
 */
#define NVIC_PRIO_GROUP_2							((priority_group_t) 0x02)
/** 
 * @brief Group 3: 
 * @brief - 3 bits preemption
 * @brief - 1 bit sub-priority
 * @details 8 preemption levels, 2 sub-priority levels  
 * @note - Many preemption levels with minimal sub-priority
 * @note - Complex real-time systems with many priority levels
 */
#define NVIC_PRIO_GROUP_3							((priority_group_t) 0x03)
/** 
 * @brief Group 4: 
 * @brief - 4 bits preemption
 * @brief - 0 bits sub-priority
 * @details 16 preemption levels, no sub-priority
 * @note - Maximum preemption control, no same-level ordering
 * @note - Hard real-time systems, medical, automotive safety
 */
#define NVIC_PRIO_GROUP_4							((priority_group_t) 0x04)

/**
 * @brief Sub-priority values (0-15) - lower = higher priority
 */
// Highest sub-priority
#define NVIC_SUB_PRIO_0								((sub_priority_t) 0)
// Second highest sub-priority
#define NVIC_SUB_PRIO_1								((sub_priority_t) 1)
#define NVIC_SUB_PRIO_2								((sub_priority_t) 2)
#define NVIC_SUB_PRIO_3								((sub_priority_t) 3)
#define NVIC_SUB_PRIO_4								((sub_priority_t) 4)
#define NVIC_SUB_PRIO_5								((sub_priority_t) 5)
#define NVIC_SUB_PRIO_6								((sub_priority_t) 6)
#define NVIC_SUB_PRIO_7								((sub_priority_t) 7)
#define NVIC_SUB_PRIO_8								((sub_priority_t) 8)
#define NVIC_SUB_PRIO_9								((sub_priority_t) 9)
#define NVIC_SUB_PRIO_10         					((sub_priority_t) 10)
#define NVIC_SUB_PRIO_11         					((sub_priority_t) 11)
#define NVIC_SUB_PRIO_12         					((sub_priority_t) 12)
#define NVIC_SUB_PRIO_13         					((sub_priority_t) 13)
// Second lowest sub-priority
#define NVIC_SUB_PRIO_14         					((sub_priority_t) 14)
// Lowest sub-priority
#define NVIC_SUB_PRIO_15         					((sub_priority_t) 15)

#endif /* NVIC_TYPES_H_ */
