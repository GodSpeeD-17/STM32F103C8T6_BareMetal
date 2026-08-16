/**
 * @file	nvic_defines.h
 * @author	Shrey Shah
 * @brief	NVIC Driver Defines
 * @version	v1.0
 * @date	06-06-2026
 *
 * @details
 * This header owns NVIC driver macros, IRQ number aliases, priority group
 * selectors, sub-priority selectors, and small register-index helpers. Data
 * type aliases remain in @ref `nvic_data_types.h`.
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
 * @brief IRQ, priority, and register-index helper macros
 * @{
 */

/** @brief First STM32F103 external IRQ number @def NVIC_IRQ_NUMBER_FIRST */
#define NVIC_IRQ_NUMBER_FIRST							((irq_t) 0x00U)
/** @brief Last STM32F103 external IRQ number represented in this driver @def NVIC_IRQ_NUMBER_LAST */
#define NVIC_IRQ_NUMBER_LAST							((irq_t) 0x43U)
/** @brief Number of IRQ enable/pending bits per NVIC register @def NVIC_IRQ_BITS_PER_REG */
#define NVIC_IRQ_BITS_PER_REG							((uint8_t) 0x20U)
/** @brief Bit shift for `IRQn / 32U` register index calculation @def NVIC_IRQ_REG_INDEX_SHIFT */
#define NVIC_IRQ_REG_INDEX_SHIFT						((uint8_t) 0x05U)
/** @brief Bit mask for `IRQn % 32U` local bit calculation @def NVIC_IRQ_REG_LOCAL_BIT_MASK */
#define NVIC_IRQ_REG_LOCAL_BIT_MASK						((uint8_t) 0x1FU)
/** @brief Bit shift for `IRQn / 4U` IPR register index calculation @def NVIC_IPR_REG_INDEX_SHIFT */
#define NVIC_IPR_REG_INDEX_SHIFT						((uint8_t) 0x02U)
/** @brief Local priority-field index mask inside one IPR register @def NVIC_IPR_LOCAL_FIELD_MASK */
#define NVIC_IPR_LOCAL_FIELD_MASK						((uint8_t) 0x03U)
/** @brief Width of one IPR priority field in bits @def NVIC_PRIORITY_FIELD_WIDTH */
#define NVIC_PRIORITY_FIELD_WIDTH						((uint8_t) 0x08U)
/** @brief Raw right-aligned priority field mask @def NVIC_PRIORITY_FIELD_MASK */
#define NVIC_PRIORITY_FIELD_MASK						((uint32_t) 0xFFUL)
/** @brief Implemented STM32F1 priority bits inside one 8-bit priority field @def NVIC_PRIORITY_IMPLEMENTED_BITS */
#define NVIC_PRIORITY_IMPLEMENTED_BITS					((uint8_t) 0x04U)
/** @brief Unimplemented low bits inside one 8-bit priority field @def NVIC_PRIORITY_UNIMPLEMENTED_BITS */
#define NVIC_PRIORITY_UNIMPLEMENTED_BITS				((uint8_t) (NVIC_PRIORITY_FIELD_WIDTH - NVIC_PRIORITY_IMPLEMENTED_BITS))
/** @brief AIRCR VECTKEY value required for writes @def SCB_AIRCR_WRITE_KEY */
#define SCB_AIRCR_WRITE_KEY								((uint32_t) 0x05FAUL)

/**
 * @brief Returns the NVIC enable/pending register index for one external IRQ number
 * @param[in] IRQn External IRQ number
 * @returns Register index containing @p IRQn bit
 * @retval - `IRQn / 32U`
 * @def NVIC_IRQ_GET_REG_INDEX
 */
#define NVIC_IRQ_GET_REG_INDEX(IRQn)					((uint8_t) (((irq_t) (IRQn)) >> NVIC_IRQ_REG_INDEX_SHIFT))

/**
 * @brief Returns the local bit position for one external IRQ number
 * @param[in] IRQn External IRQ number
 * @returns Bit position inside the selected NVIC enable/pending register
 * @retval - `IRQn % 32U`
 * @def NVIC_IRQ_GET_LOCAL_BIT_POS
 */
#define NVIC_IRQ_GET_LOCAL_BIT_POS(IRQn)				((uint8_t) (((irq_t) (IRQn)) & NVIC_IRQ_REG_LOCAL_BIT_MASK))

/**
 * @brief Returns the NVIC IPR register index for one external IRQ number
 * @param[in] IRQn External IRQ number
 * @returns IPR register index containing @p IRQn priority field
 * @retval - `IRQn / 4U`
 * @def _NVIC_IRQn_GET_IPR_REG
 */
#define _NVIC_IRQn_GET_IPR_REG(IRQn)					((uint8_t) (((irq_t) (IRQn)) >> NVIC_IPR_REG_INDEX_SHIFT))

/**
 * @brief Returns the priority-field bit shift inside one IPR register
 * @param[in] IRQn External IRQ number
 * @returns Bit shift of @p IRQn priority field inside its IPR register
 * @retval - `(IRQn % 4U) * 8U`
 * @def _NVIC_IRQn_GET_IPR_REG_INDEX
 * @note The macro name is kept for existing call sites; the returned value is
 * a bit position, not a register index.
 */
#define _NVIC_IRQn_GET_IPR_REG_INDEX(IRQn)				((uint8_t) ((((irq_t) (IRQn)) & NVIC_IPR_LOCAL_FIELD_MASK) << 0x03U))

/**
 * @brief Converts a logical priority group selector to the raw AIRCR PRIGROUP field
 * @param[in] priorityGroup Logical priority group selector
 * @returns Raw AIRCR PRIGROUP field value
 * @def NVIC_PRIO_GROUP_TO_AIRCR
 * @note STM32-style logical groups `0..4` map to ARM AIRCR fields `7..3`.
 */
#define NVIC_PRIO_GROUP_TO_AIRCR(priorityGroup)			((nvic_priority_group_t) (0x07U - ((nvic_priority_group_t) (priorityGroup))))

/**
 * @brief Converts a raw AIRCR PRIGROUP field to a logical priority group selector
 * @param[in] aircrPriorityGroup Raw AIRCR PRIGROUP field value
 * @returns Logical priority group selector
 * @def NVIC_AIRCR_TO_PRIO_GROUP
 * @note ARM AIRCR fields `7..3` map to logical STM32-style groups `0..4`.
 */
#define NVIC_AIRCR_TO_PRIO_GROUP(aircrPriorityGroup)	((nvic_priority_group_t) (0x07U - ((nvic_priority_group_t) (aircrPriorityGroup))))

/** @} */ // NVIC_02_Defines

// ==================================================================================================== //
//										NVIC Interrupt Numbers											//
// ==================================================================================================== //

/**
 * @defgroup NVIC_02_Defines_01_IRQn NVIC Interrupt Request Numbers
 * @ingroup NVIC_02_Defines
 * @brief STM32F103 external interrupt request numbers
 * @{
 */

/** @brief Window watchdog interrupt @def WWDG_IRQn */
#define WWDG_IRQn									((irq_t) 0U)
/** @brief PVD through EXTI line detection interrupt @def PVD_IRQn */
#define PVD_IRQn									((irq_t) 1U)
/** @brief Tamper interrupt @def TAMPER_IRQn */
#define TAMPER_IRQn									((irq_t) 2U)
/** @brief RTC global interrupt @def RTC_IRQn */
#define RTC_IRQn									((irq_t) 3U)
/** @brief Flash global interrupt @def FLASH_IRQn */
#define FLASH_IRQn									((irq_t) 4U)
/** @brief RCC global interrupt @def RCC_IRQn */
#define RCC_IRQn									((irq_t) 5U)
/** @brief EXTI line 0 interrupt @def EXTI0_IRQn */
#define EXTI0_IRQn									((irq_t) 6U)
/** @brief EXTI line 1 interrupt @def EXTI1_IRQn */
#define EXTI1_IRQn									((irq_t) 7U)
/** @brief EXTI line 2 interrupt @def EXTI2_IRQn */
#define EXTI2_IRQn									((irq_t) 8U)
/** @brief EXTI line 3 interrupt @def EXTI3_IRQn */
#define EXTI3_IRQn									((irq_t) 9U)
/** @brief EXTI line 4 interrupt @def EXTI4_IRQn */
#define EXTI4_IRQn									((irq_t) 10U)
/** @brief DMA1 channel 1 global interrupt @def DMA1_Channel1_IRQn */
#define DMA1_Channel1_IRQn							((irq_t) 11U)
/** @brief DMA1 channel 2 global interrupt @def DMA1_Channel2_IRQn */
#define DMA1_Channel2_IRQn							((irq_t) 12U)
/** @brief DMA1 channel 3 global interrupt @def DMA1_Channel3_IRQn */
#define DMA1_Channel3_IRQn							((irq_t) 13U)
/** @brief DMA1 channel 4 global interrupt @def DMA1_Channel4_IRQn */
#define DMA1_Channel4_IRQn							((irq_t) 14U)
/** @brief DMA1 channel 5 global interrupt @def DMA1_Channel5_IRQn */
#define DMA1_Channel5_IRQn							((irq_t) 15U)
/** @brief DMA1 channel 6 global interrupt @def DMA1_Channel6_IRQn */
#define DMA1_Channel6_IRQn							((irq_t) 16U)
/** @brief DMA1 channel 7 global interrupt @def DMA1_Channel7_IRQn */
#define DMA1_Channel7_IRQn							((irq_t) 17U)
/** @brief ADC1 and ADC2 global interrupt @def ADC1_2_IRQn */
#define ADC1_2_IRQn									((irq_t) 18U)
/** @brief USB high-priority or CAN TX interrupt @def USB_HP_CAN_TX_IRQ */
#define USB_HP_CAN_TX_IRQ							((irq_t) 19U)
/** @brief USB low-priority or CAN RX0 interrupt @def USB_LP_CAN_RX0_IRQ */
#define USB_LP_CAN_RX0_IRQ							((irq_t) 20U)
/** @brief CAN RX1 interrupt @def CAN_RX1_IRQ */
#define CAN_RX1_IRQ									((irq_t) 21U)
/** @brief CAN SCE interrupt @def CAN_SCE_IRQ */
#define CAN_SCE_IRQ									((irq_t) 22U)
/** @brief EXTI line 9 through line 5 interrupt @def EXTI9_5_IRQn */
#define EXTI9_5_IRQn								((irq_t) 23U)
/** @brief TIM1 break interrupt @def TIM1_BRK_IRQn */
#define TIM1_BRK_IRQn								((irq_t) 24U)
/** @brief TIM1 update interrupt @def TIM1_UP_IRQn */
#define TIM1_UP_IRQn								((irq_t) 25U)
/** @brief TIM1 trigger and commutation interrupt @def TIM1_TRG_COM_IRQn */
#define TIM1_TRG_COM_IRQn							((irq_t) 26U)
/** @brief TIM1 capture compare interrupt @def TIM1_CC_IRQn */
#define TIM1_CC_IRQn								((irq_t) 27U)
/** @brief TIM2 global interrupt @def TIM2_IRQn */
#define TIM2_IRQn									((irq_t) 28U)
/** @brief TIM3 global interrupt @def TIM3_IRQn */
#define TIM3_IRQn									((irq_t) 29U)
/** @brief TIM4 global interrupt @def TIM4_IRQn */
#define TIM4_IRQn									((irq_t) 30U)
/** @brief I2C1 event interrupt @def I2C1_EV_IRQn */
#define I2C1_EV_IRQn								((irq_t) 31U)
/** @brief I2C1 error interrupt @def I2C1_ER_IRQn */
#define I2C1_ER_IRQn								((irq_t) 32U)
/** @brief I2C2 event interrupt @def I2C2_EV_IRQn */
#define I2C2_EV_IRQn								((irq_t) 33U)
/** @brief I2C2 error interrupt @def I2C2_ER_IRQn */
#define I2C2_ER_IRQn								((irq_t) 34U)
/** @brief SPI1 global interrupt @def SPI1_IRQn */
#define SPI1_IRQn									((irq_t) 35U)
/** @brief SPI2 global interrupt @def SPI2_IRQn */
#define SPI2_IRQn									((irq_t) 36U)
/** @brief USART1 global interrupt @def USART1_IRQn */
#define USART1_IRQn									((irq_t) 37U)
/** @brief USART2 global interrupt @def USART2_IRQn */
#define USART2_IRQn									((irq_t) 38U)
/** @brief USART3 global interrupt @def USART3_IRQn */
#define USART3_IRQn									((irq_t) 39U)
/** @brief EXTI line 15 through line 10 interrupt @def EXTI15_10_IRQn */
#define EXTI15_10_IRQn								((irq_t) 40U)
/** @brief RTC alarm through EXTI line interrupt @def RTC_Alarm_IRQn */
#define RTC_Alarm_IRQn								((irq_t) 41U)
/** @brief USB wakeup from suspend interrupt @def USBWakeUp_IRQn */
#define USBWakeUp_IRQn								((irq_t) 42U)
/** @brief TIM8 break interrupt @def TIM8_BRK_IRQn */
#define TIM8_BRK_IRQn								((irq_t) 43U)
/** @brief TIM8 update interrupt @def TIM8_UP_IRQn */
#define TIM8_UP_IRQn								((irq_t) 44U)
/** @brief TIM8 trigger and commutation interrupt @def TIM8_TRG_COM_IRQn */
#define TIM8_TRG_COM_IRQn							((irq_t) 45U)
/** @brief TIM8 capture compare interrupt @def TIM8_CC_IRQn */
#define TIM8_CC_IRQn								((irq_t) 46U)
/** @brief ADC3 global interrupt @def ADC3_IRQn */
#define ADC3_IRQn									((irq_t) 47U)
/** @brief FSMC global interrupt @def FMSC_IRQn */
#define FMSC_IRQn									((irq_t) 48U)
/** @brief SPI3 global interrupt @def SPI3_IRQn */
#define SPI3_IRQn									((irq_t) 49U)
/** @brief UART4 global interrupt @def UART4_IRQn */
#define UART4_IRQn									((irq_t) 50U)
/** @brief UART5 global interrupt @def UART5_IRQn */
#define UART5_IRQn									((irq_t) 51U)
/** @brief TIM6 global interrupt @def TIM6_IRQn */
#define TIM6_IRQn									((irq_t) 52U)
/** @brief TIM7 global interrupt @def TIM7_IRQn */
#define TIM7_IRQn									((irq_t) 53U)
/** @brief DMA2 channel 1 global interrupt @def DMA2_Channel1_IRQn */
#define DMA2_Channel1_IRQn							((irq_t) 56U)
/** @brief DMA2 channel 2 global interrupt @def DMA2_Channel2_IRQn */
#define DMA2_Channel2_IRQn							((irq_t) 57U)
/** @brief DMA2 channel 3 global interrupt @def DMA2_Channel3_IRQn */
#define DMA2_Channel3_IRQn							((irq_t) 58U)
/** @brief DMA2 channel 4 and channel 5 global interrupt @def DMA2_Channel4_5_IRQn */
#define DMA2_Channel4_5_IRQn						((irq_t) 59U)
/** @brief Ethernet global interrupt @def ETH_IRQn */
#define ETH_IRQn									((irq_t) 61U)
/** @brief Ethernet wakeup through EXTI line interrupt @def ETH_WakeUp_IRQn */
#define ETH_WakeUp_IRQn								((irq_t) 62U)
/** @brief CAN2 TX interrupt @def CAN2_TX_IRQn */
#define CAN2_TX_IRQn								((irq_t) 63U)
/** @brief CAN2 RX0 interrupt @def CAN2_RX0_IRQn */
#define CAN2_RX0_IRQn								((irq_t) 64U)
/** @brief CAN2 RX1 interrupt @def CAN2_RX1_IRQn */
#define CAN2_RX1_IRQn								((irq_t) 65U)
/** @brief CAN2 SCE interrupt @def CAN2_SCE_IRQn */
#define CAN2_SCE_IRQn								((irq_t) 66U)
/** @brief USB OTG FS global interrupt @def OTG_FS_IRQn */
#define OTG_FS_IRQn									((irq_t) 67U)

/** @} */ // NVIC_02_Defines_01_IRQn

// ==================================================================================================== //
//										NVIC Priority Selectors											//
// ==================================================================================================== //

/**
 * @defgroup NVIC_02_Defines_02_PriorityGroup NVIC Priority Group Selectors
 * @ingroup NVIC_02_Defines
 * @brief Logical priority-group selectors used by @ref `NVIC_SetPriorityGrouping`
 * @{
 */

/** @brief Group 0: 0 preemption bits, 4 sub-priority bits @def NVIC_PRIO_GROUP_0 */
#define NVIC_PRIO_GROUP_0							((nvic_priority_group_t) 0x00U)
/** @brief Group 1: 1 preemption bit, 3 sub-priority bits @def NVIC_PRIO_GROUP_1 */
#define NVIC_PRIO_GROUP_1							((nvic_priority_group_t) 0x01U)
/** @brief Group 2: 2 preemption bits, 2 sub-priority bits @def NVIC_PRIO_GROUP_2 */
#define NVIC_PRIO_GROUP_2							((nvic_priority_group_t) 0x02U)
/** @brief Group 3: 3 preemption bits, 1 sub-priority bit @def NVIC_PRIO_GROUP_3 */
#define NVIC_PRIO_GROUP_3							((nvic_priority_group_t) 0x03U)
/** @brief Group 4: 4 preemption bits, 0 sub-priority bits @def NVIC_PRIO_GROUP_4 */
#define NVIC_PRIO_GROUP_4							((nvic_priority_group_t) 0x04U)

/** @} */ // NVIC_02_Defines_02_PriorityGroup

/**
 * @defgroup NVIC_02_Defines_03_SubPriority NVIC Sub-Priority Selectors
 * @ingroup NVIC_02_Defines
 * @brief Logical sub-priority selector values
 * @{
 */

/** @brief Sub-priority 0, highest order within same preemption level @def NVIC_SUB_PRIO_0 */
#define NVIC_SUB_PRIO_0								((nvic_sub_priority_t) 0U)
/** @brief Sub-priority 1 @def NVIC_SUB_PRIO_1 */
#define NVIC_SUB_PRIO_1								((nvic_sub_priority_t) 1U)
/** @brief Sub-priority 2 @def NVIC_SUB_PRIO_2 */
#define NVIC_SUB_PRIO_2								((nvic_sub_priority_t) 2U)
/** @brief Sub-priority 3 @def NVIC_SUB_PRIO_3 */
#define NVIC_SUB_PRIO_3								((nvic_sub_priority_t) 3U)
/** @brief Sub-priority 4 @def NVIC_SUB_PRIO_4 */
#define NVIC_SUB_PRIO_4								((nvic_sub_priority_t) 4U)
/** @brief Sub-priority 5 @def NVIC_SUB_PRIO_5 */
#define NVIC_SUB_PRIO_5								((nvic_sub_priority_t) 5U)
/** @brief Sub-priority 6 @def NVIC_SUB_PRIO_6 */
#define NVIC_SUB_PRIO_6								((nvic_sub_priority_t) 6U)
/** @brief Sub-priority 7 @def NVIC_SUB_PRIO_7 */
#define NVIC_SUB_PRIO_7								((nvic_sub_priority_t) 7U)
/** @brief Sub-priority 8 @def NVIC_SUB_PRIO_8 */
#define NVIC_SUB_PRIO_8								((nvic_sub_priority_t) 8U)
/** @brief Sub-priority 9 @def NVIC_SUB_PRIO_9 */
#define NVIC_SUB_PRIO_9								((nvic_sub_priority_t) 9U)
/** @brief Sub-priority 10 @def NVIC_SUB_PRIO_10 */
#define NVIC_SUB_PRIO_10							((nvic_sub_priority_t) 10U)
/** @brief Sub-priority 11 @def NVIC_SUB_PRIO_11 */
#define NVIC_SUB_PRIO_11							((nvic_sub_priority_t) 11U)
/** @brief Sub-priority 12 @def NVIC_SUB_PRIO_12 */
#define NVIC_SUB_PRIO_12							((nvic_sub_priority_t) 12U)
/** @brief Sub-priority 13 @def NVIC_SUB_PRIO_13 */
#define NVIC_SUB_PRIO_13							((nvic_sub_priority_t) 13U)
/** @brief Sub-priority 14 @def NVIC_SUB_PRIO_14 */
#define NVIC_SUB_PRIO_14							((nvic_sub_priority_t) 14U)
/** @brief Sub-priority 15, lowest order within same preemption level @def NVIC_SUB_PRIO_15 */
#define NVIC_SUB_PRIO_15							((nvic_sub_priority_t) 15U)

/** @} */ // NVIC_02_Defines_03_SubPriority

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_DEFINES_H_ */
