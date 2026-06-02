/**
 * @file stm32f1xx_exti.h
 * @author Shrey Shah
 * @brief STM32F1 EXTI Register-Layer Definitions
 * @version v1.1
 * @date 30-05-2026
 */
#ifndef STM32F1XX_EXTI_H_
#define STM32F1XX_EXTI_H_

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //
#include "stm32f1xx_utils.h"

/**
 * @defgroup EXTI External Interrupt/Event Controller (EXTI)
 * @brief STM32F1 external interrupt and event line controller register model
 * @details
 * RM0008 Section 10 describes EXTI as the hardware block that:
 * - masks interrupt requests through IMR,
 * - masks event requests through EMR,
 * - selects rising and falling edge triggers through RTSR and FTSR,
 * - raises software interrupt/event requests through SWIER,
 * - exposes and clears pending state through PR.
 *
 * This codebase documents EXTI in three software layers in execution order:
 * - Register layer: @ref `stm32f1xx_exti.h`
 * - Low-level control layer: @ref `gpio_irq_ll.h`
 * - Driver/orchestration layer: @ref `gpio_irq.h`
 */

/**
 * @defgroup EXTI_01_RegisterLayer EXTI Register Layer
 * @ingroup EXTI
 * @brief Raw EXTI register structure and hardware-visible bitfield layout
 * @details
 * This layer mirrors the hardware-visible EXTI register map. It does not own
 * GPIO port routing, public trigger selectors, NVIC policy, or validation.
 */

/**
 * @addtogroup EXTI_01_RegisterLayer
 * @{
 */

// ------------------------------------------------------------------------------------------
// EXTI_IMR (Interrupt Mask Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief EXTI Interrupt Mask Register Definitions
 * @defgroup EXTI_01_RegisterLayer_01_IMR EXTI Interrupt Mask Register
 * @ingroup EXTI_01_RegisterLayer
 * @details
 * @section EXTI_IMR_Theory Theory and Practical Role
 * This page documents `EXTI_IMR`, which provides interrupt request mask bits for EXTI lines 0 through 19.
 *
 * @section EXTI_IMR_Macros Register-Specific Macros
 * The macro definitions below expose raw bit positions, masks, and
 * convenience aliases used by LL layers when they need direct symbolic access to `EXTI_IMR`.
 *
 * @section EXTI_IMR_Union Register Union View
 * The `union EXTI_IMR` view inside @ref EXTI_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ MR[19:0] (Interrupt Mask Bits) ------ //
/** @brief EXTI_IMR_MR Position @def EXTI_IMR_MR_Pos */
#define EXTI_IMR_MR_Pos						(0U)
/** @brief EXTI_IMR_MR Mask @def EXTI_IMR_MR_Msk */
#define EXTI_IMR_MR_Msk						(REG_FIELD_VALUE(0x000FFFFFUL, EXTI_IMR_MR_Pos))
/** @brief Interrupt Mask Bits @def EXTI_IMR_MR */
#define EXTI_IMR_MR							EXTI_IMR_MR_Msk

/** @brief EXTI_IMR_MR0 Position @def EXTI_IMR_MR0_Pos */
#define EXTI_IMR_MR0_Pos						(0U)
/** @brief EXTI_IMR_MR0 Mask @def EXTI_IMR_MR0_Msk */
#define EXTI_IMR_MR0_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR0_Pos))
/** @brief Interrupt Mask bit for EXTI line 0 @def EXTI_IMR_MR0 */
#define EXTI_IMR_MR0							EXTI_IMR_MR0_Msk

/** @brief EXTI_IMR_MR1 Position @def EXTI_IMR_MR1_Pos */
#define EXTI_IMR_MR1_Pos						(1U)
/** @brief EXTI_IMR_MR1 Mask @def EXTI_IMR_MR1_Msk */
#define EXTI_IMR_MR1_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR1_Pos))
/** @brief Interrupt Mask bit for EXTI line 1 @def EXTI_IMR_MR1 */
#define EXTI_IMR_MR1							EXTI_IMR_MR1_Msk

/** @brief EXTI_IMR_MR2 Position @def EXTI_IMR_MR2_Pos */
#define EXTI_IMR_MR2_Pos						(2U)
/** @brief EXTI_IMR_MR2 Mask @def EXTI_IMR_MR2_Msk */
#define EXTI_IMR_MR2_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR2_Pos))
/** @brief Interrupt Mask bit for EXTI line 2 @def EXTI_IMR_MR2 */
#define EXTI_IMR_MR2							EXTI_IMR_MR2_Msk

/** @brief EXTI_IMR_MR3 Position @def EXTI_IMR_MR3_Pos */
#define EXTI_IMR_MR3_Pos						(3U)
/** @brief EXTI_IMR_MR3 Mask @def EXTI_IMR_MR3_Msk */
#define EXTI_IMR_MR3_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR3_Pos))
/** @brief Interrupt Mask bit for EXTI line 3 @def EXTI_IMR_MR3 */
#define EXTI_IMR_MR3							EXTI_IMR_MR3_Msk

/** @brief EXTI_IMR_MR4 Position @def EXTI_IMR_MR4_Pos */
#define EXTI_IMR_MR4_Pos						(4U)
/** @brief EXTI_IMR_MR4 Mask @def EXTI_IMR_MR4_Msk */
#define EXTI_IMR_MR4_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR4_Pos))
/** @brief Interrupt Mask bit for EXTI line 4 @def EXTI_IMR_MR4 */
#define EXTI_IMR_MR4							EXTI_IMR_MR4_Msk

/** @brief EXTI_IMR_MR5 Position @def EXTI_IMR_MR5_Pos */
#define EXTI_IMR_MR5_Pos						(5U)
/** @brief EXTI_IMR_MR5 Mask @def EXTI_IMR_MR5_Msk */
#define EXTI_IMR_MR5_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR5_Pos))
/** @brief Interrupt Mask bit for EXTI line 5 @def EXTI_IMR_MR5 */
#define EXTI_IMR_MR5							EXTI_IMR_MR5_Msk

/** @brief EXTI_IMR_MR6 Position @def EXTI_IMR_MR6_Pos */
#define EXTI_IMR_MR6_Pos						(6U)
/** @brief EXTI_IMR_MR6 Mask @def EXTI_IMR_MR6_Msk */
#define EXTI_IMR_MR6_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR6_Pos))
/** @brief Interrupt Mask bit for EXTI line 6 @def EXTI_IMR_MR6 */
#define EXTI_IMR_MR6							EXTI_IMR_MR6_Msk

/** @brief EXTI_IMR_MR7 Position @def EXTI_IMR_MR7_Pos */
#define EXTI_IMR_MR7_Pos						(7U)
/** @brief EXTI_IMR_MR7 Mask @def EXTI_IMR_MR7_Msk */
#define EXTI_IMR_MR7_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR7_Pos))
/** @brief Interrupt Mask bit for EXTI line 7 @def EXTI_IMR_MR7 */
#define EXTI_IMR_MR7							EXTI_IMR_MR7_Msk

/** @brief EXTI_IMR_MR8 Position @def EXTI_IMR_MR8_Pos */
#define EXTI_IMR_MR8_Pos						(8U)
/** @brief EXTI_IMR_MR8 Mask @def EXTI_IMR_MR8_Msk */
#define EXTI_IMR_MR8_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR8_Pos))
/** @brief Interrupt Mask bit for EXTI line 8 @def EXTI_IMR_MR8 */
#define EXTI_IMR_MR8							EXTI_IMR_MR8_Msk

/** @brief EXTI_IMR_MR9 Position @def EXTI_IMR_MR9_Pos */
#define EXTI_IMR_MR9_Pos						(9U)
/** @brief EXTI_IMR_MR9 Mask @def EXTI_IMR_MR9_Msk */
#define EXTI_IMR_MR9_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR9_Pos))
/** @brief Interrupt Mask bit for EXTI line 9 @def EXTI_IMR_MR9 */
#define EXTI_IMR_MR9							EXTI_IMR_MR9_Msk

/** @brief EXTI_IMR_MR10 Position @def EXTI_IMR_MR10_Pos */
#define EXTI_IMR_MR10_Pos						(10U)
/** @brief EXTI_IMR_MR10 Mask @def EXTI_IMR_MR10_Msk */
#define EXTI_IMR_MR10_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR10_Pos))
/** @brief Interrupt Mask bit for EXTI line 10 @def EXTI_IMR_MR10 */
#define EXTI_IMR_MR10							EXTI_IMR_MR10_Msk

/** @brief EXTI_IMR_MR11 Position @def EXTI_IMR_MR11_Pos */
#define EXTI_IMR_MR11_Pos						(11U)
/** @brief EXTI_IMR_MR11 Mask @def EXTI_IMR_MR11_Msk */
#define EXTI_IMR_MR11_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR11_Pos))
/** @brief Interrupt Mask bit for EXTI line 11 @def EXTI_IMR_MR11 */
#define EXTI_IMR_MR11							EXTI_IMR_MR11_Msk

/** @brief EXTI_IMR_MR12 Position @def EXTI_IMR_MR12_Pos */
#define EXTI_IMR_MR12_Pos						(12U)
/** @brief EXTI_IMR_MR12 Mask @def EXTI_IMR_MR12_Msk */
#define EXTI_IMR_MR12_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR12_Pos))
/** @brief Interrupt Mask bit for EXTI line 12 @def EXTI_IMR_MR12 */
#define EXTI_IMR_MR12							EXTI_IMR_MR12_Msk

/** @brief EXTI_IMR_MR13 Position @def EXTI_IMR_MR13_Pos */
#define EXTI_IMR_MR13_Pos						(13U)
/** @brief EXTI_IMR_MR13 Mask @def EXTI_IMR_MR13_Msk */
#define EXTI_IMR_MR13_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR13_Pos))
/** @brief Interrupt Mask bit for EXTI line 13 @def EXTI_IMR_MR13 */
#define EXTI_IMR_MR13							EXTI_IMR_MR13_Msk

/** @brief EXTI_IMR_MR14 Position @def EXTI_IMR_MR14_Pos */
#define EXTI_IMR_MR14_Pos						(14U)
/** @brief EXTI_IMR_MR14 Mask @def EXTI_IMR_MR14_Msk */
#define EXTI_IMR_MR14_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR14_Pos))
/** @brief Interrupt Mask bit for EXTI line 14 @def EXTI_IMR_MR14 */
#define EXTI_IMR_MR14							EXTI_IMR_MR14_Msk

/** @brief EXTI_IMR_MR15 Position @def EXTI_IMR_MR15_Pos */
#define EXTI_IMR_MR15_Pos						(15U)
/** @brief EXTI_IMR_MR15 Mask @def EXTI_IMR_MR15_Msk */
#define EXTI_IMR_MR15_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR15_Pos))
/** @brief Interrupt Mask bit for EXTI line 15 @def EXTI_IMR_MR15 */
#define EXTI_IMR_MR15							EXTI_IMR_MR15_Msk

/** @brief EXTI_IMR_MR16 Position @def EXTI_IMR_MR16_Pos */
#define EXTI_IMR_MR16_Pos						(16U)
/** @brief EXTI_IMR_MR16 Mask @def EXTI_IMR_MR16_Msk */
#define EXTI_IMR_MR16_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR16_Pos))
/** @brief Interrupt Mask bit for EXTI line 16 @def EXTI_IMR_MR16 */
#define EXTI_IMR_MR16							EXTI_IMR_MR16_Msk

/** @brief EXTI_IMR_MR17 Position @def EXTI_IMR_MR17_Pos */
#define EXTI_IMR_MR17_Pos						(17U)
/** @brief EXTI_IMR_MR17 Mask @def EXTI_IMR_MR17_Msk */
#define EXTI_IMR_MR17_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR17_Pos))
/** @brief Interrupt Mask bit for EXTI line 17 @def EXTI_IMR_MR17 */
#define EXTI_IMR_MR17							EXTI_IMR_MR17_Msk

/** @brief EXTI_IMR_MR18 Position @def EXTI_IMR_MR18_Pos */
#define EXTI_IMR_MR18_Pos						(18U)
/** @brief EXTI_IMR_MR18 Mask @def EXTI_IMR_MR18_Msk */
#define EXTI_IMR_MR18_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR18_Pos))
/** @brief Interrupt Mask bit for EXTI line 18 @def EXTI_IMR_MR18 */
#define EXTI_IMR_MR18							EXTI_IMR_MR18_Msk

/** @brief EXTI_IMR_MR19 Position @def EXTI_IMR_MR19_Pos */
#define EXTI_IMR_MR19_Pos						(19U)
/** @brief EXTI_IMR_MR19 Mask @def EXTI_IMR_MR19_Msk */
#define EXTI_IMR_MR19_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_IMR_MR19_Pos))
/** @brief Interrupt Mask bit for EXTI line 19 @def EXTI_IMR_MR19 */
#define EXTI_IMR_MR19							EXTI_IMR_MR19_Msk

/** @} */ // EXTI_01_RegisterLayer_01_IMR

// ------------------------------------------------------------------------------------------
// EXTI_EMR (Event Mask Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief EXTI Event Mask Register Definitions
 * @defgroup EXTI_01_RegisterLayer_02_EMR EXTI Event Mask Register
 * @ingroup EXTI_01_RegisterLayer
 * @details
 * @section EXTI_EMR_Theory Theory and Practical Role
 * This page documents `EXTI_EMR`, which provides event request mask bits for EXTI lines 0 through 19.
 *
 * @section EXTI_EMR_Macros Register-Specific Macros
 * The macro definitions below expose raw bit positions, masks, and
 * convenience aliases used by LL layers when they need direct symbolic access to `EXTI_EMR`.
 *
 * @section EXTI_EMR_Union Register Union View
 * The `union EXTI_EMR` view inside @ref EXTI_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ MR[19:0] (Event Mask Bits) ------ //
/** @brief EXTI_EMR_MR Position @def EXTI_EMR_MR_Pos */
#define EXTI_EMR_MR_Pos						(0U)
/** @brief EXTI_EMR_MR Mask @def EXTI_EMR_MR_Msk */
#define EXTI_EMR_MR_Msk						(REG_FIELD_VALUE(0x000FFFFFUL, EXTI_EMR_MR_Pos))
/** @brief Event Mask Bits @def EXTI_EMR_MR */
#define EXTI_EMR_MR							EXTI_EMR_MR_Msk

/** @brief EXTI_EMR_MR0 Position @def EXTI_EMR_MR0_Pos */
#define EXTI_EMR_MR0_Pos						(0U)
/** @brief EXTI_EMR_MR0 Mask @def EXTI_EMR_MR0_Msk */
#define EXTI_EMR_MR0_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR0_Pos))
/** @brief Event Mask bit for EXTI line 0 @def EXTI_EMR_MR0 */
#define EXTI_EMR_MR0							EXTI_EMR_MR0_Msk

/** @brief EXTI_EMR_MR1 Position @def EXTI_EMR_MR1_Pos */
#define EXTI_EMR_MR1_Pos						(1U)
/** @brief EXTI_EMR_MR1 Mask @def EXTI_EMR_MR1_Msk */
#define EXTI_EMR_MR1_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR1_Pos))
/** @brief Event Mask bit for EXTI line 1 @def EXTI_EMR_MR1 */
#define EXTI_EMR_MR1							EXTI_EMR_MR1_Msk

/** @brief EXTI_EMR_MR2 Position @def EXTI_EMR_MR2_Pos */
#define EXTI_EMR_MR2_Pos						(2U)
/** @brief EXTI_EMR_MR2 Mask @def EXTI_EMR_MR2_Msk */
#define EXTI_EMR_MR2_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR2_Pos))
/** @brief Event Mask bit for EXTI line 2 @def EXTI_EMR_MR2 */
#define EXTI_EMR_MR2							EXTI_EMR_MR2_Msk

/** @brief EXTI_EMR_MR3 Position @def EXTI_EMR_MR3_Pos */
#define EXTI_EMR_MR3_Pos						(3U)
/** @brief EXTI_EMR_MR3 Mask @def EXTI_EMR_MR3_Msk */
#define EXTI_EMR_MR3_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR3_Pos))
/** @brief Event Mask bit for EXTI line 3 @def EXTI_EMR_MR3 */
#define EXTI_EMR_MR3							EXTI_EMR_MR3_Msk

/** @brief EXTI_EMR_MR4 Position @def EXTI_EMR_MR4_Pos */
#define EXTI_EMR_MR4_Pos						(4U)
/** @brief EXTI_EMR_MR4 Mask @def EXTI_EMR_MR4_Msk */
#define EXTI_EMR_MR4_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR4_Pos))
/** @brief Event Mask bit for EXTI line 4 @def EXTI_EMR_MR4 */
#define EXTI_EMR_MR4							EXTI_EMR_MR4_Msk

/** @brief EXTI_EMR_MR5 Position @def EXTI_EMR_MR5_Pos */
#define EXTI_EMR_MR5_Pos						(5U)
/** @brief EXTI_EMR_MR5 Mask @def EXTI_EMR_MR5_Msk */
#define EXTI_EMR_MR5_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR5_Pos))
/** @brief Event Mask bit for EXTI line 5 @def EXTI_EMR_MR5 */
#define EXTI_EMR_MR5							EXTI_EMR_MR5_Msk

/** @brief EXTI_EMR_MR6 Position @def EXTI_EMR_MR6_Pos */
#define EXTI_EMR_MR6_Pos						(6U)
/** @brief EXTI_EMR_MR6 Mask @def EXTI_EMR_MR6_Msk */
#define EXTI_EMR_MR6_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR6_Pos))
/** @brief Event Mask bit for EXTI line 6 @def EXTI_EMR_MR6 */
#define EXTI_EMR_MR6							EXTI_EMR_MR6_Msk

/** @brief EXTI_EMR_MR7 Position @def EXTI_EMR_MR7_Pos */
#define EXTI_EMR_MR7_Pos						(7U)
/** @brief EXTI_EMR_MR7 Mask @def EXTI_EMR_MR7_Msk */
#define EXTI_EMR_MR7_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR7_Pos))
/** @brief Event Mask bit for EXTI line 7 @def EXTI_EMR_MR7 */
#define EXTI_EMR_MR7							EXTI_EMR_MR7_Msk

/** @brief EXTI_EMR_MR8 Position @def EXTI_EMR_MR8_Pos */
#define EXTI_EMR_MR8_Pos						(8U)
/** @brief EXTI_EMR_MR8 Mask @def EXTI_EMR_MR8_Msk */
#define EXTI_EMR_MR8_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR8_Pos))
/** @brief Event Mask bit for EXTI line 8 @def EXTI_EMR_MR8 */
#define EXTI_EMR_MR8							EXTI_EMR_MR8_Msk

/** @brief EXTI_EMR_MR9 Position @def EXTI_EMR_MR9_Pos */
#define EXTI_EMR_MR9_Pos						(9U)
/** @brief EXTI_EMR_MR9 Mask @def EXTI_EMR_MR9_Msk */
#define EXTI_EMR_MR9_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR9_Pos))
/** @brief Event Mask bit for EXTI line 9 @def EXTI_EMR_MR9 */
#define EXTI_EMR_MR9							EXTI_EMR_MR9_Msk

/** @brief EXTI_EMR_MR10 Position @def EXTI_EMR_MR10_Pos */
#define EXTI_EMR_MR10_Pos						(10U)
/** @brief EXTI_EMR_MR10 Mask @def EXTI_EMR_MR10_Msk */
#define EXTI_EMR_MR10_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR10_Pos))
/** @brief Event Mask bit for EXTI line 10 @def EXTI_EMR_MR10 */
#define EXTI_EMR_MR10							EXTI_EMR_MR10_Msk

/** @brief EXTI_EMR_MR11 Position @def EXTI_EMR_MR11_Pos */
#define EXTI_EMR_MR11_Pos						(11U)
/** @brief EXTI_EMR_MR11 Mask @def EXTI_EMR_MR11_Msk */
#define EXTI_EMR_MR11_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR11_Pos))
/** @brief Event Mask bit for EXTI line 11 @def EXTI_EMR_MR11 */
#define EXTI_EMR_MR11							EXTI_EMR_MR11_Msk

/** @brief EXTI_EMR_MR12 Position @def EXTI_EMR_MR12_Pos */
#define EXTI_EMR_MR12_Pos						(12U)
/** @brief EXTI_EMR_MR12 Mask @def EXTI_EMR_MR12_Msk */
#define EXTI_EMR_MR12_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR12_Pos))
/** @brief Event Mask bit for EXTI line 12 @def EXTI_EMR_MR12 */
#define EXTI_EMR_MR12							EXTI_EMR_MR12_Msk

/** @brief EXTI_EMR_MR13 Position @def EXTI_EMR_MR13_Pos */
#define EXTI_EMR_MR13_Pos						(13U)
/** @brief EXTI_EMR_MR13 Mask @def EXTI_EMR_MR13_Msk */
#define EXTI_EMR_MR13_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR13_Pos))
/** @brief Event Mask bit for EXTI line 13 @def EXTI_EMR_MR13 */
#define EXTI_EMR_MR13							EXTI_EMR_MR13_Msk

/** @brief EXTI_EMR_MR14 Position @def EXTI_EMR_MR14_Pos */
#define EXTI_EMR_MR14_Pos						(14U)
/** @brief EXTI_EMR_MR14 Mask @def EXTI_EMR_MR14_Msk */
#define EXTI_EMR_MR14_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR14_Pos))
/** @brief Event Mask bit for EXTI line 14 @def EXTI_EMR_MR14 */
#define EXTI_EMR_MR14							EXTI_EMR_MR14_Msk

/** @brief EXTI_EMR_MR15 Position @def EXTI_EMR_MR15_Pos */
#define EXTI_EMR_MR15_Pos						(15U)
/** @brief EXTI_EMR_MR15 Mask @def EXTI_EMR_MR15_Msk */
#define EXTI_EMR_MR15_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR15_Pos))
/** @brief Event Mask bit for EXTI line 15 @def EXTI_EMR_MR15 */
#define EXTI_EMR_MR15							EXTI_EMR_MR15_Msk

/** @brief EXTI_EMR_MR16 Position @def EXTI_EMR_MR16_Pos */
#define EXTI_EMR_MR16_Pos						(16U)
/** @brief EXTI_EMR_MR16 Mask @def EXTI_EMR_MR16_Msk */
#define EXTI_EMR_MR16_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR16_Pos))
/** @brief Event Mask bit for EXTI line 16 @def EXTI_EMR_MR16 */
#define EXTI_EMR_MR16							EXTI_EMR_MR16_Msk

/** @brief EXTI_EMR_MR17 Position @def EXTI_EMR_MR17_Pos */
#define EXTI_EMR_MR17_Pos						(17U)
/** @brief EXTI_EMR_MR17 Mask @def EXTI_EMR_MR17_Msk */
#define EXTI_EMR_MR17_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR17_Pos))
/** @brief Event Mask bit for EXTI line 17 @def EXTI_EMR_MR17 */
#define EXTI_EMR_MR17							EXTI_EMR_MR17_Msk

/** @brief EXTI_EMR_MR18 Position @def EXTI_EMR_MR18_Pos */
#define EXTI_EMR_MR18_Pos						(18U)
/** @brief EXTI_EMR_MR18 Mask @def EXTI_EMR_MR18_Msk */
#define EXTI_EMR_MR18_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR18_Pos))
/** @brief Event Mask bit for EXTI line 18 @def EXTI_EMR_MR18 */
#define EXTI_EMR_MR18							EXTI_EMR_MR18_Msk

/** @brief EXTI_EMR_MR19 Position @def EXTI_EMR_MR19_Pos */
#define EXTI_EMR_MR19_Pos						(19U)
/** @brief EXTI_EMR_MR19 Mask @def EXTI_EMR_MR19_Msk */
#define EXTI_EMR_MR19_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_EMR_MR19_Pos))
/** @brief Event Mask bit for EXTI line 19 @def EXTI_EMR_MR19 */
#define EXTI_EMR_MR19							EXTI_EMR_MR19_Msk

/** @} */ // EXTI_01_RegisterLayer_02_EMR

// ------------------------------------------------------------------------------------------
// EXTI_RTSR (Rising Trigger Selection Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief EXTI Rising Trigger Selection Register Definitions
 * @defgroup EXTI_01_RegisterLayer_03_RTSR EXTI Rising Trigger Selection Register
 * @ingroup EXTI_01_RegisterLayer
 * @details
 * @section EXTI_RTSR_Theory Theory and Practical Role
 * This page documents `EXTI_RTSR`, which provides rising-edge trigger selection bits for EXTI lines 0 through 19.
 *
 * @section EXTI_RTSR_Macros Register-Specific Macros
 * The macro definitions below expose raw bit positions, masks, and
 * convenience aliases used by LL layers when they need direct symbolic access to `EXTI_RTSR`.
 *
 * @section EXTI_RTSR_Union Register Union View
 * The `union EXTI_RTSR` view inside @ref EXTI_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ TR[19:0] (Rising Trigger Selection Bits) ------ //
/** @brief EXTI_RTSR_TR Position @def EXTI_RTSR_TR_Pos */
#define EXTI_RTSR_TR_Pos						(0U)
/** @brief EXTI_RTSR_TR Mask @def EXTI_RTSR_TR_Msk */
#define EXTI_RTSR_TR_Msk						(REG_FIELD_VALUE(0x000FFFFFUL, EXTI_RTSR_TR_Pos))
/** @brief Rising Trigger Selection Bits @def EXTI_RTSR_TR */
#define EXTI_RTSR_TR							EXTI_RTSR_TR_Msk

/** @brief EXTI_RTSR_TR0 Position @def EXTI_RTSR_TR0_Pos */
#define EXTI_RTSR_TR0_Pos						(0U)
/** @brief EXTI_RTSR_TR0 Mask @def EXTI_RTSR_TR0_Msk */
#define EXTI_RTSR_TR0_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR0_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 0 @def EXTI_RTSR_TR0 */
#define EXTI_RTSR_TR0							EXTI_RTSR_TR0_Msk

/** @brief EXTI_RTSR_TR1 Position @def EXTI_RTSR_TR1_Pos */
#define EXTI_RTSR_TR1_Pos						(1U)
/** @brief EXTI_RTSR_TR1 Mask @def EXTI_RTSR_TR1_Msk */
#define EXTI_RTSR_TR1_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR1_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 1 @def EXTI_RTSR_TR1 */
#define EXTI_RTSR_TR1							EXTI_RTSR_TR1_Msk

/** @brief EXTI_RTSR_TR2 Position @def EXTI_RTSR_TR2_Pos */
#define EXTI_RTSR_TR2_Pos						(2U)
/** @brief EXTI_RTSR_TR2 Mask @def EXTI_RTSR_TR2_Msk */
#define EXTI_RTSR_TR2_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR2_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 2 @def EXTI_RTSR_TR2 */
#define EXTI_RTSR_TR2							EXTI_RTSR_TR2_Msk

/** @brief EXTI_RTSR_TR3 Position @def EXTI_RTSR_TR3_Pos */
#define EXTI_RTSR_TR3_Pos						(3U)
/** @brief EXTI_RTSR_TR3 Mask @def EXTI_RTSR_TR3_Msk */
#define EXTI_RTSR_TR3_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR3_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 3 @def EXTI_RTSR_TR3 */
#define EXTI_RTSR_TR3							EXTI_RTSR_TR3_Msk

/** @brief EXTI_RTSR_TR4 Position @def EXTI_RTSR_TR4_Pos */
#define EXTI_RTSR_TR4_Pos						(4U)
/** @brief EXTI_RTSR_TR4 Mask @def EXTI_RTSR_TR4_Msk */
#define EXTI_RTSR_TR4_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR4_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 4 @def EXTI_RTSR_TR4 */
#define EXTI_RTSR_TR4							EXTI_RTSR_TR4_Msk

/** @brief EXTI_RTSR_TR5 Position @def EXTI_RTSR_TR5_Pos */
#define EXTI_RTSR_TR5_Pos						(5U)
/** @brief EXTI_RTSR_TR5 Mask @def EXTI_RTSR_TR5_Msk */
#define EXTI_RTSR_TR5_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR5_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 5 @def EXTI_RTSR_TR5 */
#define EXTI_RTSR_TR5							EXTI_RTSR_TR5_Msk

/** @brief EXTI_RTSR_TR6 Position @def EXTI_RTSR_TR6_Pos */
#define EXTI_RTSR_TR6_Pos						(6U)
/** @brief EXTI_RTSR_TR6 Mask @def EXTI_RTSR_TR6_Msk */
#define EXTI_RTSR_TR6_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR6_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 6 @def EXTI_RTSR_TR6 */
#define EXTI_RTSR_TR6							EXTI_RTSR_TR6_Msk

/** @brief EXTI_RTSR_TR7 Position @def EXTI_RTSR_TR7_Pos */
#define EXTI_RTSR_TR7_Pos						(7U)
/** @brief EXTI_RTSR_TR7 Mask @def EXTI_RTSR_TR7_Msk */
#define EXTI_RTSR_TR7_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR7_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 7 @def EXTI_RTSR_TR7 */
#define EXTI_RTSR_TR7							EXTI_RTSR_TR7_Msk

/** @brief EXTI_RTSR_TR8 Position @def EXTI_RTSR_TR8_Pos */
#define EXTI_RTSR_TR8_Pos						(8U)
/** @brief EXTI_RTSR_TR8 Mask @def EXTI_RTSR_TR8_Msk */
#define EXTI_RTSR_TR8_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR8_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 8 @def EXTI_RTSR_TR8 */
#define EXTI_RTSR_TR8							EXTI_RTSR_TR8_Msk

/** @brief EXTI_RTSR_TR9 Position @def EXTI_RTSR_TR9_Pos */
#define EXTI_RTSR_TR9_Pos						(9U)
/** @brief EXTI_RTSR_TR9 Mask @def EXTI_RTSR_TR9_Msk */
#define EXTI_RTSR_TR9_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR9_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 9 @def EXTI_RTSR_TR9 */
#define EXTI_RTSR_TR9							EXTI_RTSR_TR9_Msk

/** @brief EXTI_RTSR_TR10 Position @def EXTI_RTSR_TR10_Pos */
#define EXTI_RTSR_TR10_Pos						(10U)
/** @brief EXTI_RTSR_TR10 Mask @def EXTI_RTSR_TR10_Msk */
#define EXTI_RTSR_TR10_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR10_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 10 @def EXTI_RTSR_TR10 */
#define EXTI_RTSR_TR10							EXTI_RTSR_TR10_Msk

/** @brief EXTI_RTSR_TR11 Position @def EXTI_RTSR_TR11_Pos */
#define EXTI_RTSR_TR11_Pos						(11U)
/** @brief EXTI_RTSR_TR11 Mask @def EXTI_RTSR_TR11_Msk */
#define EXTI_RTSR_TR11_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR11_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 11 @def EXTI_RTSR_TR11 */
#define EXTI_RTSR_TR11							EXTI_RTSR_TR11_Msk

/** @brief EXTI_RTSR_TR12 Position @def EXTI_RTSR_TR12_Pos */
#define EXTI_RTSR_TR12_Pos						(12U)
/** @brief EXTI_RTSR_TR12 Mask @def EXTI_RTSR_TR12_Msk */
#define EXTI_RTSR_TR12_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR12_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 12 @def EXTI_RTSR_TR12 */
#define EXTI_RTSR_TR12							EXTI_RTSR_TR12_Msk

/** @brief EXTI_RTSR_TR13 Position @def EXTI_RTSR_TR13_Pos */
#define EXTI_RTSR_TR13_Pos						(13U)
/** @brief EXTI_RTSR_TR13 Mask @def EXTI_RTSR_TR13_Msk */
#define EXTI_RTSR_TR13_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR13_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 13 @def EXTI_RTSR_TR13 */
#define EXTI_RTSR_TR13							EXTI_RTSR_TR13_Msk

/** @brief EXTI_RTSR_TR14 Position @def EXTI_RTSR_TR14_Pos */
#define EXTI_RTSR_TR14_Pos						(14U)
/** @brief EXTI_RTSR_TR14 Mask @def EXTI_RTSR_TR14_Msk */
#define EXTI_RTSR_TR14_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR14_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 14 @def EXTI_RTSR_TR14 */
#define EXTI_RTSR_TR14							EXTI_RTSR_TR14_Msk

/** @brief EXTI_RTSR_TR15 Position @def EXTI_RTSR_TR15_Pos */
#define EXTI_RTSR_TR15_Pos						(15U)
/** @brief EXTI_RTSR_TR15 Mask @def EXTI_RTSR_TR15_Msk */
#define EXTI_RTSR_TR15_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR15_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 15 @def EXTI_RTSR_TR15 */
#define EXTI_RTSR_TR15							EXTI_RTSR_TR15_Msk

/** @brief EXTI_RTSR_TR16 Position @def EXTI_RTSR_TR16_Pos */
#define EXTI_RTSR_TR16_Pos						(16U)
/** @brief EXTI_RTSR_TR16 Mask @def EXTI_RTSR_TR16_Msk */
#define EXTI_RTSR_TR16_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR16_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 16 @def EXTI_RTSR_TR16 */
#define EXTI_RTSR_TR16							EXTI_RTSR_TR16_Msk

/** @brief EXTI_RTSR_TR17 Position @def EXTI_RTSR_TR17_Pos */
#define EXTI_RTSR_TR17_Pos						(17U)
/** @brief EXTI_RTSR_TR17 Mask @def EXTI_RTSR_TR17_Msk */
#define EXTI_RTSR_TR17_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR17_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 17 @def EXTI_RTSR_TR17 */
#define EXTI_RTSR_TR17							EXTI_RTSR_TR17_Msk

/** @brief EXTI_RTSR_TR18 Position @def EXTI_RTSR_TR18_Pos */
#define EXTI_RTSR_TR18_Pos						(18U)
/** @brief EXTI_RTSR_TR18 Mask @def EXTI_RTSR_TR18_Msk */
#define EXTI_RTSR_TR18_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR18_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 18 @def EXTI_RTSR_TR18 */
#define EXTI_RTSR_TR18							EXTI_RTSR_TR18_Msk

/** @brief EXTI_RTSR_TR19 Position @def EXTI_RTSR_TR19_Pos */
#define EXTI_RTSR_TR19_Pos						(19U)
/** @brief EXTI_RTSR_TR19 Mask @def EXTI_RTSR_TR19_Msk */
#define EXTI_RTSR_TR19_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_RTSR_TR19_Pos))
/** @brief Rising Trigger Selection bit for EXTI line 19 @def EXTI_RTSR_TR19 */
#define EXTI_RTSR_TR19							EXTI_RTSR_TR19_Msk

/** @} */ // EXTI_01_RegisterLayer_03_RTSR

// ------------------------------------------------------------------------------------------
// EXTI_FTSR (Falling Trigger Selection Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief EXTI Falling Trigger Selection Register Definitions
 * @defgroup EXTI_01_RegisterLayer_04_FTSR EXTI Falling Trigger Selection Register
 * @ingroup EXTI_01_RegisterLayer
 * @details
 * @section EXTI_FTSR_Theory Theory and Practical Role
 * This page documents `EXTI_FTSR`, which provides falling-edge trigger selection bits for EXTI lines 0 through 19.
 *
 * @section EXTI_FTSR_Macros Register-Specific Macros
 * The macro definitions below expose raw bit positions, masks, and
 * convenience aliases used by LL layers when they need direct symbolic access to `EXTI_FTSR`.
 *
 * @section EXTI_FTSR_Union Register Union View
 * The `union EXTI_FTSR` view inside @ref EXTI_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ TR[19:0] (Falling Trigger Selection Bits) ------ //
/** @brief EXTI_FTSR_TR Position @def EXTI_FTSR_TR_Pos */
#define EXTI_FTSR_TR_Pos						(0U)
/** @brief EXTI_FTSR_TR Mask @def EXTI_FTSR_TR_Msk */
#define EXTI_FTSR_TR_Msk						(REG_FIELD_VALUE(0x000FFFFFUL, EXTI_FTSR_TR_Pos))
/** @brief Falling Trigger Selection Bits @def EXTI_FTSR_TR */
#define EXTI_FTSR_TR							EXTI_FTSR_TR_Msk

/** @brief EXTI_FTSR_TR0 Position @def EXTI_FTSR_TR0_Pos */
#define EXTI_FTSR_TR0_Pos						(0U)
/** @brief EXTI_FTSR_TR0 Mask @def EXTI_FTSR_TR0_Msk */
#define EXTI_FTSR_TR0_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR0_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 0 @def EXTI_FTSR_TR0 */
#define EXTI_FTSR_TR0							EXTI_FTSR_TR0_Msk

/** @brief EXTI_FTSR_TR1 Position @def EXTI_FTSR_TR1_Pos */
#define EXTI_FTSR_TR1_Pos						(1U)
/** @brief EXTI_FTSR_TR1 Mask @def EXTI_FTSR_TR1_Msk */
#define EXTI_FTSR_TR1_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR1_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 1 @def EXTI_FTSR_TR1 */
#define EXTI_FTSR_TR1							EXTI_FTSR_TR1_Msk

/** @brief EXTI_FTSR_TR2 Position @def EXTI_FTSR_TR2_Pos */
#define EXTI_FTSR_TR2_Pos						(2U)
/** @brief EXTI_FTSR_TR2 Mask @def EXTI_FTSR_TR2_Msk */
#define EXTI_FTSR_TR2_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR2_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 2 @def EXTI_FTSR_TR2 */
#define EXTI_FTSR_TR2							EXTI_FTSR_TR2_Msk

/** @brief EXTI_FTSR_TR3 Position @def EXTI_FTSR_TR3_Pos */
#define EXTI_FTSR_TR3_Pos						(3U)
/** @brief EXTI_FTSR_TR3 Mask @def EXTI_FTSR_TR3_Msk */
#define EXTI_FTSR_TR3_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR3_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 3 @def EXTI_FTSR_TR3 */
#define EXTI_FTSR_TR3							EXTI_FTSR_TR3_Msk

/** @brief EXTI_FTSR_TR4 Position @def EXTI_FTSR_TR4_Pos */
#define EXTI_FTSR_TR4_Pos						(4U)
/** @brief EXTI_FTSR_TR4 Mask @def EXTI_FTSR_TR4_Msk */
#define EXTI_FTSR_TR4_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR4_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 4 @def EXTI_FTSR_TR4 */
#define EXTI_FTSR_TR4							EXTI_FTSR_TR4_Msk

/** @brief EXTI_FTSR_TR5 Position @def EXTI_FTSR_TR5_Pos */
#define EXTI_FTSR_TR5_Pos						(5U)
/** @brief EXTI_FTSR_TR5 Mask @def EXTI_FTSR_TR5_Msk */
#define EXTI_FTSR_TR5_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR5_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 5 @def EXTI_FTSR_TR5 */
#define EXTI_FTSR_TR5							EXTI_FTSR_TR5_Msk

/** @brief EXTI_FTSR_TR6 Position @def EXTI_FTSR_TR6_Pos */
#define EXTI_FTSR_TR6_Pos						(6U)
/** @brief EXTI_FTSR_TR6 Mask @def EXTI_FTSR_TR6_Msk */
#define EXTI_FTSR_TR6_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR6_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 6 @def EXTI_FTSR_TR6 */
#define EXTI_FTSR_TR6							EXTI_FTSR_TR6_Msk

/** @brief EXTI_FTSR_TR7 Position @def EXTI_FTSR_TR7_Pos */
#define EXTI_FTSR_TR7_Pos						(7U)
/** @brief EXTI_FTSR_TR7 Mask @def EXTI_FTSR_TR7_Msk */
#define EXTI_FTSR_TR7_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR7_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 7 @def EXTI_FTSR_TR7 */
#define EXTI_FTSR_TR7							EXTI_FTSR_TR7_Msk

/** @brief EXTI_FTSR_TR8 Position @def EXTI_FTSR_TR8_Pos */
#define EXTI_FTSR_TR8_Pos						(8U)
/** @brief EXTI_FTSR_TR8 Mask @def EXTI_FTSR_TR8_Msk */
#define EXTI_FTSR_TR8_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR8_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 8 @def EXTI_FTSR_TR8 */
#define EXTI_FTSR_TR8							EXTI_FTSR_TR8_Msk

/** @brief EXTI_FTSR_TR9 Position @def EXTI_FTSR_TR9_Pos */
#define EXTI_FTSR_TR9_Pos						(9U)
/** @brief EXTI_FTSR_TR9 Mask @def EXTI_FTSR_TR9_Msk */
#define EXTI_FTSR_TR9_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR9_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 9 @def EXTI_FTSR_TR9 */
#define EXTI_FTSR_TR9							EXTI_FTSR_TR9_Msk

/** @brief EXTI_FTSR_TR10 Position @def EXTI_FTSR_TR10_Pos */
#define EXTI_FTSR_TR10_Pos						(10U)
/** @brief EXTI_FTSR_TR10 Mask @def EXTI_FTSR_TR10_Msk */
#define EXTI_FTSR_TR10_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR10_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 10 @def EXTI_FTSR_TR10 */
#define EXTI_FTSR_TR10							EXTI_FTSR_TR10_Msk

/** @brief EXTI_FTSR_TR11 Position @def EXTI_FTSR_TR11_Pos */
#define EXTI_FTSR_TR11_Pos						(11U)
/** @brief EXTI_FTSR_TR11 Mask @def EXTI_FTSR_TR11_Msk */
#define EXTI_FTSR_TR11_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR11_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 11 @def EXTI_FTSR_TR11 */
#define EXTI_FTSR_TR11							EXTI_FTSR_TR11_Msk

/** @brief EXTI_FTSR_TR12 Position @def EXTI_FTSR_TR12_Pos */
#define EXTI_FTSR_TR12_Pos						(12U)
/** @brief EXTI_FTSR_TR12 Mask @def EXTI_FTSR_TR12_Msk */
#define EXTI_FTSR_TR12_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR12_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 12 @def EXTI_FTSR_TR12 */
#define EXTI_FTSR_TR12							EXTI_FTSR_TR12_Msk

/** @brief EXTI_FTSR_TR13 Position @def EXTI_FTSR_TR13_Pos */
#define EXTI_FTSR_TR13_Pos						(13U)
/** @brief EXTI_FTSR_TR13 Mask @def EXTI_FTSR_TR13_Msk */
#define EXTI_FTSR_TR13_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR13_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 13 @def EXTI_FTSR_TR13 */
#define EXTI_FTSR_TR13							EXTI_FTSR_TR13_Msk

/** @brief EXTI_FTSR_TR14 Position @def EXTI_FTSR_TR14_Pos */
#define EXTI_FTSR_TR14_Pos						(14U)
/** @brief EXTI_FTSR_TR14 Mask @def EXTI_FTSR_TR14_Msk */
#define EXTI_FTSR_TR14_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR14_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 14 @def EXTI_FTSR_TR14 */
#define EXTI_FTSR_TR14							EXTI_FTSR_TR14_Msk

/** @brief EXTI_FTSR_TR15 Position @def EXTI_FTSR_TR15_Pos */
#define EXTI_FTSR_TR15_Pos						(15U)
/** @brief EXTI_FTSR_TR15 Mask @def EXTI_FTSR_TR15_Msk */
#define EXTI_FTSR_TR15_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR15_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 15 @def EXTI_FTSR_TR15 */
#define EXTI_FTSR_TR15							EXTI_FTSR_TR15_Msk

/** @brief EXTI_FTSR_TR16 Position @def EXTI_FTSR_TR16_Pos */
#define EXTI_FTSR_TR16_Pos						(16U)
/** @brief EXTI_FTSR_TR16 Mask @def EXTI_FTSR_TR16_Msk */
#define EXTI_FTSR_TR16_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR16_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 16 @def EXTI_FTSR_TR16 */
#define EXTI_FTSR_TR16							EXTI_FTSR_TR16_Msk

/** @brief EXTI_FTSR_TR17 Position @def EXTI_FTSR_TR17_Pos */
#define EXTI_FTSR_TR17_Pos						(17U)
/** @brief EXTI_FTSR_TR17 Mask @def EXTI_FTSR_TR17_Msk */
#define EXTI_FTSR_TR17_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR17_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 17 @def EXTI_FTSR_TR17 */
#define EXTI_FTSR_TR17							EXTI_FTSR_TR17_Msk

/** @brief EXTI_FTSR_TR18 Position @def EXTI_FTSR_TR18_Pos */
#define EXTI_FTSR_TR18_Pos						(18U)
/** @brief EXTI_FTSR_TR18 Mask @def EXTI_FTSR_TR18_Msk */
#define EXTI_FTSR_TR18_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR18_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 18 @def EXTI_FTSR_TR18 */
#define EXTI_FTSR_TR18							EXTI_FTSR_TR18_Msk

/** @brief EXTI_FTSR_TR19 Position @def EXTI_FTSR_TR19_Pos */
#define EXTI_FTSR_TR19_Pos						(19U)
/** @brief EXTI_FTSR_TR19 Mask @def EXTI_FTSR_TR19_Msk */
#define EXTI_FTSR_TR19_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_FTSR_TR19_Pos))
/** @brief Falling Trigger Selection bit for EXTI line 19 @def EXTI_FTSR_TR19 */
#define EXTI_FTSR_TR19							EXTI_FTSR_TR19_Msk

/** @} */ // EXTI_01_RegisterLayer_04_FTSR

// ------------------------------------------------------------------------------------------
// EXTI_SWIER (Software Interrupt Event Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief EXTI Software Interrupt Event Register Definitions
 * @defgroup EXTI_01_RegisterLayer_05_SWIER EXTI Software Interrupt Event Register
 * @ingroup EXTI_01_RegisterLayer
 * @details
 * @section EXTI_SWIER_Theory Theory and Practical Role
 * This page documents `EXTI_SWIER`, which provides software interrupt/event request bits for EXTI lines 0 through 19.
 *
 * @section EXTI_SWIER_Macros Register-Specific Macros
 * The macro definitions below expose raw bit positions, masks, and
 * convenience aliases used by LL layers when they need direct symbolic access to `EXTI_SWIER`.
 *
 * @section EXTI_SWIER_Union Register Union View
 * The `union EXTI_SWIER` view inside @ref EXTI_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ SWIER[19:0] (Software Interrupt Event Bits) ------ //
/** @brief EXTI_SWIER_SWIER Position @def EXTI_SWIER_SWIER_Pos */
#define EXTI_SWIER_SWIER_Pos						(0U)
/** @brief EXTI_SWIER_SWIER Mask @def EXTI_SWIER_SWIER_Msk */
#define EXTI_SWIER_SWIER_Msk						(REG_FIELD_VALUE(0x000FFFFFUL, EXTI_SWIER_SWIER_Pos))
/** @brief Software Interrupt Event Bits @def EXTI_SWIER_SWIER */
#define EXTI_SWIER_SWIER							EXTI_SWIER_SWIER_Msk

/** @brief EXTI_SWIER_SWIER0 Position @def EXTI_SWIER_SWIER0_Pos */
#define EXTI_SWIER_SWIER0_Pos						(0U)
/** @brief EXTI_SWIER_SWIER0 Mask @def EXTI_SWIER_SWIER0_Msk */
#define EXTI_SWIER_SWIER0_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER0_Pos))
/** @brief Software Interrupt Event bit for EXTI line 0 @def EXTI_SWIER_SWIER0 */
#define EXTI_SWIER_SWIER0							EXTI_SWIER_SWIER0_Msk

/** @brief EXTI_SWIER_SWIER1 Position @def EXTI_SWIER_SWIER1_Pos */
#define EXTI_SWIER_SWIER1_Pos						(1U)
/** @brief EXTI_SWIER_SWIER1 Mask @def EXTI_SWIER_SWIER1_Msk */
#define EXTI_SWIER_SWIER1_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER1_Pos))
/** @brief Software Interrupt Event bit for EXTI line 1 @def EXTI_SWIER_SWIER1 */
#define EXTI_SWIER_SWIER1							EXTI_SWIER_SWIER1_Msk

/** @brief EXTI_SWIER_SWIER2 Position @def EXTI_SWIER_SWIER2_Pos */
#define EXTI_SWIER_SWIER2_Pos						(2U)
/** @brief EXTI_SWIER_SWIER2 Mask @def EXTI_SWIER_SWIER2_Msk */
#define EXTI_SWIER_SWIER2_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER2_Pos))
/** @brief Software Interrupt Event bit for EXTI line 2 @def EXTI_SWIER_SWIER2 */
#define EXTI_SWIER_SWIER2							EXTI_SWIER_SWIER2_Msk

/** @brief EXTI_SWIER_SWIER3 Position @def EXTI_SWIER_SWIER3_Pos */
#define EXTI_SWIER_SWIER3_Pos						(3U)
/** @brief EXTI_SWIER_SWIER3 Mask @def EXTI_SWIER_SWIER3_Msk */
#define EXTI_SWIER_SWIER3_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER3_Pos))
/** @brief Software Interrupt Event bit for EXTI line 3 @def EXTI_SWIER_SWIER3 */
#define EXTI_SWIER_SWIER3							EXTI_SWIER_SWIER3_Msk

/** @brief EXTI_SWIER_SWIER4 Position @def EXTI_SWIER_SWIER4_Pos */
#define EXTI_SWIER_SWIER4_Pos						(4U)
/** @brief EXTI_SWIER_SWIER4 Mask @def EXTI_SWIER_SWIER4_Msk */
#define EXTI_SWIER_SWIER4_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER4_Pos))
/** @brief Software Interrupt Event bit for EXTI line 4 @def EXTI_SWIER_SWIER4 */
#define EXTI_SWIER_SWIER4							EXTI_SWIER_SWIER4_Msk

/** @brief EXTI_SWIER_SWIER5 Position @def EXTI_SWIER_SWIER5_Pos */
#define EXTI_SWIER_SWIER5_Pos						(5U)
/** @brief EXTI_SWIER_SWIER5 Mask @def EXTI_SWIER_SWIER5_Msk */
#define EXTI_SWIER_SWIER5_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER5_Pos))
/** @brief Software Interrupt Event bit for EXTI line 5 @def EXTI_SWIER_SWIER5 */
#define EXTI_SWIER_SWIER5							EXTI_SWIER_SWIER5_Msk

/** @brief EXTI_SWIER_SWIER6 Position @def EXTI_SWIER_SWIER6_Pos */
#define EXTI_SWIER_SWIER6_Pos						(6U)
/** @brief EXTI_SWIER_SWIER6 Mask @def EXTI_SWIER_SWIER6_Msk */
#define EXTI_SWIER_SWIER6_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER6_Pos))
/** @brief Software Interrupt Event bit for EXTI line 6 @def EXTI_SWIER_SWIER6 */
#define EXTI_SWIER_SWIER6							EXTI_SWIER_SWIER6_Msk

/** @brief EXTI_SWIER_SWIER7 Position @def EXTI_SWIER_SWIER7_Pos */
#define EXTI_SWIER_SWIER7_Pos						(7U)
/** @brief EXTI_SWIER_SWIER7 Mask @def EXTI_SWIER_SWIER7_Msk */
#define EXTI_SWIER_SWIER7_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER7_Pos))
/** @brief Software Interrupt Event bit for EXTI line 7 @def EXTI_SWIER_SWIER7 */
#define EXTI_SWIER_SWIER7							EXTI_SWIER_SWIER7_Msk

/** @brief EXTI_SWIER_SWIER8 Position @def EXTI_SWIER_SWIER8_Pos */
#define EXTI_SWIER_SWIER8_Pos						(8U)
/** @brief EXTI_SWIER_SWIER8 Mask @def EXTI_SWIER_SWIER8_Msk */
#define EXTI_SWIER_SWIER8_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER8_Pos))
/** @brief Software Interrupt Event bit for EXTI line 8 @def EXTI_SWIER_SWIER8 */
#define EXTI_SWIER_SWIER8							EXTI_SWIER_SWIER8_Msk

/** @brief EXTI_SWIER_SWIER9 Position @def EXTI_SWIER_SWIER9_Pos */
#define EXTI_SWIER_SWIER9_Pos						(9U)
/** @brief EXTI_SWIER_SWIER9 Mask @def EXTI_SWIER_SWIER9_Msk */
#define EXTI_SWIER_SWIER9_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER9_Pos))
/** @brief Software Interrupt Event bit for EXTI line 9 @def EXTI_SWIER_SWIER9 */
#define EXTI_SWIER_SWIER9							EXTI_SWIER_SWIER9_Msk

/** @brief EXTI_SWIER_SWIER10 Position @def EXTI_SWIER_SWIER10_Pos */
#define EXTI_SWIER_SWIER10_Pos						(10U)
/** @brief EXTI_SWIER_SWIER10 Mask @def EXTI_SWIER_SWIER10_Msk */
#define EXTI_SWIER_SWIER10_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER10_Pos))
/** @brief Software Interrupt Event bit for EXTI line 10 @def EXTI_SWIER_SWIER10 */
#define EXTI_SWIER_SWIER10							EXTI_SWIER_SWIER10_Msk

/** @brief EXTI_SWIER_SWIER11 Position @def EXTI_SWIER_SWIER11_Pos */
#define EXTI_SWIER_SWIER11_Pos						(11U)
/** @brief EXTI_SWIER_SWIER11 Mask @def EXTI_SWIER_SWIER11_Msk */
#define EXTI_SWIER_SWIER11_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER11_Pos))
/** @brief Software Interrupt Event bit for EXTI line 11 @def EXTI_SWIER_SWIER11 */
#define EXTI_SWIER_SWIER11							EXTI_SWIER_SWIER11_Msk

/** @brief EXTI_SWIER_SWIER12 Position @def EXTI_SWIER_SWIER12_Pos */
#define EXTI_SWIER_SWIER12_Pos						(12U)
/** @brief EXTI_SWIER_SWIER12 Mask @def EXTI_SWIER_SWIER12_Msk */
#define EXTI_SWIER_SWIER12_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER12_Pos))
/** @brief Software Interrupt Event bit for EXTI line 12 @def EXTI_SWIER_SWIER12 */
#define EXTI_SWIER_SWIER12							EXTI_SWIER_SWIER12_Msk

/** @brief EXTI_SWIER_SWIER13 Position @def EXTI_SWIER_SWIER13_Pos */
#define EXTI_SWIER_SWIER13_Pos						(13U)
/** @brief EXTI_SWIER_SWIER13 Mask @def EXTI_SWIER_SWIER13_Msk */
#define EXTI_SWIER_SWIER13_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER13_Pos))
/** @brief Software Interrupt Event bit for EXTI line 13 @def EXTI_SWIER_SWIER13 */
#define EXTI_SWIER_SWIER13							EXTI_SWIER_SWIER13_Msk

/** @brief EXTI_SWIER_SWIER14 Position @def EXTI_SWIER_SWIER14_Pos */
#define EXTI_SWIER_SWIER14_Pos						(14U)
/** @brief EXTI_SWIER_SWIER14 Mask @def EXTI_SWIER_SWIER14_Msk */
#define EXTI_SWIER_SWIER14_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER14_Pos))
/** @brief Software Interrupt Event bit for EXTI line 14 @def EXTI_SWIER_SWIER14 */
#define EXTI_SWIER_SWIER14							EXTI_SWIER_SWIER14_Msk

/** @brief EXTI_SWIER_SWIER15 Position @def EXTI_SWIER_SWIER15_Pos */
#define EXTI_SWIER_SWIER15_Pos						(15U)
/** @brief EXTI_SWIER_SWIER15 Mask @def EXTI_SWIER_SWIER15_Msk */
#define EXTI_SWIER_SWIER15_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER15_Pos))
/** @brief Software Interrupt Event bit for EXTI line 15 @def EXTI_SWIER_SWIER15 */
#define EXTI_SWIER_SWIER15							EXTI_SWIER_SWIER15_Msk

/** @brief EXTI_SWIER_SWIER16 Position @def EXTI_SWIER_SWIER16_Pos */
#define EXTI_SWIER_SWIER16_Pos						(16U)
/** @brief EXTI_SWIER_SWIER16 Mask @def EXTI_SWIER_SWIER16_Msk */
#define EXTI_SWIER_SWIER16_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER16_Pos))
/** @brief Software Interrupt Event bit for EXTI line 16 @def EXTI_SWIER_SWIER16 */
#define EXTI_SWIER_SWIER16							EXTI_SWIER_SWIER16_Msk

/** @brief EXTI_SWIER_SWIER17 Position @def EXTI_SWIER_SWIER17_Pos */
#define EXTI_SWIER_SWIER17_Pos						(17U)
/** @brief EXTI_SWIER_SWIER17 Mask @def EXTI_SWIER_SWIER17_Msk */
#define EXTI_SWIER_SWIER17_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER17_Pos))
/** @brief Software Interrupt Event bit for EXTI line 17 @def EXTI_SWIER_SWIER17 */
#define EXTI_SWIER_SWIER17							EXTI_SWIER_SWIER17_Msk

/** @brief EXTI_SWIER_SWIER18 Position @def EXTI_SWIER_SWIER18_Pos */
#define EXTI_SWIER_SWIER18_Pos						(18U)
/** @brief EXTI_SWIER_SWIER18 Mask @def EXTI_SWIER_SWIER18_Msk */
#define EXTI_SWIER_SWIER18_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER18_Pos))
/** @brief Software Interrupt Event bit for EXTI line 18 @def EXTI_SWIER_SWIER18 */
#define EXTI_SWIER_SWIER18							EXTI_SWIER_SWIER18_Msk

/** @brief EXTI_SWIER_SWIER19 Position @def EXTI_SWIER_SWIER19_Pos */
#define EXTI_SWIER_SWIER19_Pos						(19U)
/** @brief EXTI_SWIER_SWIER19 Mask @def EXTI_SWIER_SWIER19_Msk */
#define EXTI_SWIER_SWIER19_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_SWIER_SWIER19_Pos))
/** @brief Software Interrupt Event bit for EXTI line 19 @def EXTI_SWIER_SWIER19 */
#define EXTI_SWIER_SWIER19							EXTI_SWIER_SWIER19_Msk

/** @} */ // EXTI_01_RegisterLayer_05_SWIER

// ------------------------------------------------------------------------------------------
// EXTI_PR (Pending Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief EXTI Pending Register Definitions
 * @defgroup EXTI_01_RegisterLayer_06_PR EXTI Pending Register
 * @ingroup EXTI_01_RegisterLayer
 * @details
 * @section EXTI_PR_Theory Theory and Practical Role
 * This page documents `EXTI_PR`, which provides pending state bits for EXTI lines 0 through 19.
 *
 * @section EXTI_PR_Macros Register-Specific Macros
 * The macro definitions below expose raw bit positions, masks, and
 * convenience aliases used by LL layers when they need direct symbolic access to `EXTI_PR`.
 *
 * @section EXTI_PR_Union Register Union View
 * The `union EXTI_PR` view inside @ref EXTI_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ PR[19:0] (Pending State Bits) ------ //
/** @brief EXTI_PR_PR Position @def EXTI_PR_PR_Pos */
#define EXTI_PR_PR_Pos						(0U)
/** @brief EXTI_PR_PR Mask @def EXTI_PR_PR_Msk */
#define EXTI_PR_PR_Msk						(REG_FIELD_VALUE(0x000FFFFFUL, EXTI_PR_PR_Pos))
/** @brief Pending State Bits @def EXTI_PR_PR */
#define EXTI_PR_PR							EXTI_PR_PR_Msk

/** @brief EXTI_PR_PR0 Position @def EXTI_PR_PR0_Pos */
#define EXTI_PR_PR0_Pos						(0U)
/** @brief EXTI_PR_PR0 Mask @def EXTI_PR_PR0_Msk */
#define EXTI_PR_PR0_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR0_Pos))
/** @brief Pending State bit for EXTI line 0 @def EXTI_PR_PR0 */
#define EXTI_PR_PR0							EXTI_PR_PR0_Msk

/** @brief EXTI_PR_PR1 Position @def EXTI_PR_PR1_Pos */
#define EXTI_PR_PR1_Pos						(1U)
/** @brief EXTI_PR_PR1 Mask @def EXTI_PR_PR1_Msk */
#define EXTI_PR_PR1_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR1_Pos))
/** @brief Pending State bit for EXTI line 1 @def EXTI_PR_PR1 */
#define EXTI_PR_PR1							EXTI_PR_PR1_Msk

/** @brief EXTI_PR_PR2 Position @def EXTI_PR_PR2_Pos */
#define EXTI_PR_PR2_Pos						(2U)
/** @brief EXTI_PR_PR2 Mask @def EXTI_PR_PR2_Msk */
#define EXTI_PR_PR2_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR2_Pos))
/** @brief Pending State bit for EXTI line 2 @def EXTI_PR_PR2 */
#define EXTI_PR_PR2							EXTI_PR_PR2_Msk

/** @brief EXTI_PR_PR3 Position @def EXTI_PR_PR3_Pos */
#define EXTI_PR_PR3_Pos						(3U)
/** @brief EXTI_PR_PR3 Mask @def EXTI_PR_PR3_Msk */
#define EXTI_PR_PR3_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR3_Pos))
/** @brief Pending State bit for EXTI line 3 @def EXTI_PR_PR3 */
#define EXTI_PR_PR3							EXTI_PR_PR3_Msk

/** @brief EXTI_PR_PR4 Position @def EXTI_PR_PR4_Pos */
#define EXTI_PR_PR4_Pos						(4U)
/** @brief EXTI_PR_PR4 Mask @def EXTI_PR_PR4_Msk */
#define EXTI_PR_PR4_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR4_Pos))
/** @brief Pending State bit for EXTI line 4 @def EXTI_PR_PR4 */
#define EXTI_PR_PR4							EXTI_PR_PR4_Msk

/** @brief EXTI_PR_PR5 Position @def EXTI_PR_PR5_Pos */
#define EXTI_PR_PR5_Pos						(5U)
/** @brief EXTI_PR_PR5 Mask @def EXTI_PR_PR5_Msk */
#define EXTI_PR_PR5_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR5_Pos))
/** @brief Pending State bit for EXTI line 5 @def EXTI_PR_PR5 */
#define EXTI_PR_PR5							EXTI_PR_PR5_Msk

/** @brief EXTI_PR_PR6 Position @def EXTI_PR_PR6_Pos */
#define EXTI_PR_PR6_Pos						(6U)
/** @brief EXTI_PR_PR6 Mask @def EXTI_PR_PR6_Msk */
#define EXTI_PR_PR6_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR6_Pos))
/** @brief Pending State bit for EXTI line 6 @def EXTI_PR_PR6 */
#define EXTI_PR_PR6							EXTI_PR_PR6_Msk

/** @brief EXTI_PR_PR7 Position @def EXTI_PR_PR7_Pos */
#define EXTI_PR_PR7_Pos						(7U)
/** @brief EXTI_PR_PR7 Mask @def EXTI_PR_PR7_Msk */
#define EXTI_PR_PR7_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR7_Pos))
/** @brief Pending State bit for EXTI line 7 @def EXTI_PR_PR7 */
#define EXTI_PR_PR7							EXTI_PR_PR7_Msk

/** @brief EXTI_PR_PR8 Position @def EXTI_PR_PR8_Pos */
#define EXTI_PR_PR8_Pos						(8U)
/** @brief EXTI_PR_PR8 Mask @def EXTI_PR_PR8_Msk */
#define EXTI_PR_PR8_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR8_Pos))
/** @brief Pending State bit for EXTI line 8 @def EXTI_PR_PR8 */
#define EXTI_PR_PR8							EXTI_PR_PR8_Msk

/** @brief EXTI_PR_PR9 Position @def EXTI_PR_PR9_Pos */
#define EXTI_PR_PR9_Pos						(9U)
/** @brief EXTI_PR_PR9 Mask @def EXTI_PR_PR9_Msk */
#define EXTI_PR_PR9_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR9_Pos))
/** @brief Pending State bit for EXTI line 9 @def EXTI_PR_PR9 */
#define EXTI_PR_PR9							EXTI_PR_PR9_Msk

/** @brief EXTI_PR_PR10 Position @def EXTI_PR_PR10_Pos */
#define EXTI_PR_PR10_Pos						(10U)
/** @brief EXTI_PR_PR10 Mask @def EXTI_PR_PR10_Msk */
#define EXTI_PR_PR10_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR10_Pos))
/** @brief Pending State bit for EXTI line 10 @def EXTI_PR_PR10 */
#define EXTI_PR_PR10							EXTI_PR_PR10_Msk

/** @brief EXTI_PR_PR11 Position @def EXTI_PR_PR11_Pos */
#define EXTI_PR_PR11_Pos						(11U)
/** @brief EXTI_PR_PR11 Mask @def EXTI_PR_PR11_Msk */
#define EXTI_PR_PR11_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR11_Pos))
/** @brief Pending State bit for EXTI line 11 @def EXTI_PR_PR11 */
#define EXTI_PR_PR11							EXTI_PR_PR11_Msk

/** @brief EXTI_PR_PR12 Position @def EXTI_PR_PR12_Pos */
#define EXTI_PR_PR12_Pos						(12U)
/** @brief EXTI_PR_PR12 Mask @def EXTI_PR_PR12_Msk */
#define EXTI_PR_PR12_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR12_Pos))
/** @brief Pending State bit for EXTI line 12 @def EXTI_PR_PR12 */
#define EXTI_PR_PR12							EXTI_PR_PR12_Msk

/** @brief EXTI_PR_PR13 Position @def EXTI_PR_PR13_Pos */
#define EXTI_PR_PR13_Pos						(13U)
/** @brief EXTI_PR_PR13 Mask @def EXTI_PR_PR13_Msk */
#define EXTI_PR_PR13_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR13_Pos))
/** @brief Pending State bit for EXTI line 13 @def EXTI_PR_PR13 */
#define EXTI_PR_PR13							EXTI_PR_PR13_Msk

/** @brief EXTI_PR_PR14 Position @def EXTI_PR_PR14_Pos */
#define EXTI_PR_PR14_Pos						(14U)
/** @brief EXTI_PR_PR14 Mask @def EXTI_PR_PR14_Msk */
#define EXTI_PR_PR14_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR14_Pos))
/** @brief Pending State bit for EXTI line 14 @def EXTI_PR_PR14 */
#define EXTI_PR_PR14							EXTI_PR_PR14_Msk

/** @brief EXTI_PR_PR15 Position @def EXTI_PR_PR15_Pos */
#define EXTI_PR_PR15_Pos						(15U)
/** @brief EXTI_PR_PR15 Mask @def EXTI_PR_PR15_Msk */
#define EXTI_PR_PR15_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR15_Pos))
/** @brief Pending State bit for EXTI line 15 @def EXTI_PR_PR15 */
#define EXTI_PR_PR15							EXTI_PR_PR15_Msk

/** @brief EXTI_PR_PR16 Position @def EXTI_PR_PR16_Pos */
#define EXTI_PR_PR16_Pos						(16U)
/** @brief EXTI_PR_PR16 Mask @def EXTI_PR_PR16_Msk */
#define EXTI_PR_PR16_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR16_Pos))
/** @brief Pending State bit for EXTI line 16 @def EXTI_PR_PR16 */
#define EXTI_PR_PR16							EXTI_PR_PR16_Msk

/** @brief EXTI_PR_PR17 Position @def EXTI_PR_PR17_Pos */
#define EXTI_PR_PR17_Pos						(17U)
/** @brief EXTI_PR_PR17 Mask @def EXTI_PR_PR17_Msk */
#define EXTI_PR_PR17_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR17_Pos))
/** @brief Pending State bit for EXTI line 17 @def EXTI_PR_PR17 */
#define EXTI_PR_PR17							EXTI_PR_PR17_Msk

/** @brief EXTI_PR_PR18 Position @def EXTI_PR_PR18_Pos */
#define EXTI_PR_PR18_Pos						(18U)
/** @brief EXTI_PR_PR18 Mask @def EXTI_PR_PR18_Msk */
#define EXTI_PR_PR18_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR18_Pos))
/** @brief Pending State bit for EXTI line 18 @def EXTI_PR_PR18 */
#define EXTI_PR_PR18							EXTI_PR_PR18_Msk

/** @brief EXTI_PR_PR19 Position @def EXTI_PR_PR19_Pos */
#define EXTI_PR_PR19_Pos						(19U)
/** @brief EXTI_PR_PR19 Mask @def EXTI_PR_PR19_Msk */
#define EXTI_PR_PR19_Msk						(REG_FIELD_VALUE(0x1UL, EXTI_PR_PR19_Pos))
/** @brief Pending State bit for EXTI line 19 @def EXTI_PR_PR19 */
#define EXTI_PR_PR19							EXTI_PR_PR19_Msk

/** @} */ // EXTI_01_RegisterLayer_06_PR

// ==================================================================================================== //
//                                            EXTI Structure                                            //
// ==================================================================================================== //

/**
 * @defgroup EXTI_01_RegisterLayer_07_RegisterMap EXTI Register Block Map
 * @ingroup EXTI_01_RegisterLayer
 * @brief Memory-mapped EXTI register block and practical register layout
 * @details
 * @section EXTI_RegisterMap_Theory Theory and Practical Role
 * This page ties the EXTI register definitions to the concrete memory map used
 * by the software stack. @ref EXTI_TypeDef is the raw peripheral view consumed
 * by the LL layer when it reads, writes, or stages EXTI register state.
 *
 * @section EXTI_RegisterMap_Structure EXTI Register Block Structure
 * The structure below is the software-visible EXTI register layout in offset
 * order. Each register exposes a full-register view (`.REG`) and a named
 * bitfield view (`.BIT`).
 * @{
 */

/**
 * @brief EXTI Register Block Structure
 * @details
 * Complete memory-mapped EXTI peripheral register map.
 *
 * @see RM0008 Section 10.3 EXTI registers
 * @typedef EXTI_TypeDef
 */
typedef volatile struct _EXTI_TypeDef
{
	/**
	 * @ingroup EXTI_01_RegisterLayer_07_RegisterMap
	 * @section EXTI_TypeDef_IMR Interrupt Mask Register (IMR)
	 * @brief [R/W] Interrupt request mask for EXTI lines
	 * @details
	 * Bits 0 to 19 control whether each EXTI line can generate an interrupt
	 * request. Bits 20 to 31 are reserved.
	 */
	union EXTI_IMR
	{
		_IO REG;
		struct
		{
			_IO MR0 : 1;
			_IO MR1 : 1;
			_IO MR2 : 1;
			_IO MR3 : 1;
			_IO MR4 : 1;
			_IO MR5 : 1;
			_IO MR6 : 1;
			_IO MR7 : 1;
			_IO MR8 : 1;
			_IO MR9 : 1;
			_IO MR10 : 1;
			_IO MR11 : 1;
			_IO MR12 : 1;
			_IO MR13 : 1;
			_IO MR14 : 1;
			_IO MR15 : 1;
			_IO MR16 : 1;
			_IO MR17 : 1;
			_IO MR18 : 1;
			_IO MR19 : 1;
			_IO RESERVED_IMR : 12;
		} BIT;
	} IMR;

	/**
	 * @ingroup EXTI_01_RegisterLayer_07_RegisterMap
	 * @section EXTI_TypeDef_EMR Event Mask Register (EMR)
	 * @brief [R/W] Event request mask for EXTI lines
	 * @details
	 * Bits 0 to 19 control whether each EXTI line can generate an event
	 * request. Bits 20 to 31 are reserved.
	 */
	union EXTI_EMR
	{
		_IO REG;
		struct
		{
			_IO MR0 : 1;
			_IO MR1 : 1;
			_IO MR2 : 1;
			_IO MR3 : 1;
			_IO MR4 : 1;
			_IO MR5 : 1;
			_IO MR6 : 1;
			_IO MR7 : 1;
			_IO MR8 : 1;
			_IO MR9 : 1;
			_IO MR10 : 1;
			_IO MR11 : 1;
			_IO MR12 : 1;
			_IO MR13 : 1;
			_IO MR14 : 1;
			_IO MR15 : 1;
			_IO MR16 : 1;
			_IO MR17 : 1;
			_IO MR18 : 1;
			_IO MR19 : 1;
			_IO RESERVED_EMR : 12;
		} BIT;
	} EMR;

	/**
	 * @ingroup EXTI_01_RegisterLayer_07_RegisterMap
	 * @section EXTI_TypeDef_RTSR Rising Trigger Selection Register (RTSR)
	 * @brief [R/W] Rising-edge trigger selection for EXTI lines
	 * @details
	 * Bits 0 to 19 select rising-edge trigger detection for each EXTI line.
	 * Bits 20 to 31 are reserved.
	 */
	union EXTI_RTSR
	{
		_IO REG;
		struct
		{
			_IO TR0 : 1;
			_IO TR1 : 1;
			_IO TR2 : 1;
			_IO TR3 : 1;
			_IO TR4 : 1;
			_IO TR5 : 1;
			_IO TR6 : 1;
			_IO TR7 : 1;
			_IO TR8 : 1;
			_IO TR9 : 1;
			_IO TR10 : 1;
			_IO TR11 : 1;
			_IO TR12 : 1;
			_IO TR13 : 1;
			_IO TR14 : 1;
			_IO TR15 : 1;
			_IO TR16 : 1;
			_IO TR17 : 1;
			_IO TR18 : 1;
			_IO TR19 : 1;
			_IO RESERVED_RTSR : 12;
		} BIT;
	} RTSR;

	/**
	 * @ingroup EXTI_01_RegisterLayer_07_RegisterMap
	 * @section EXTI_TypeDef_FTSR Falling Trigger Selection Register (FTSR)
	 * @brief [R/W] Falling-edge trigger selection for EXTI lines
	 * @details
	 * Bits 0 to 19 select falling-edge trigger detection for each EXTI line.
	 * Bits 20 to 31 are reserved.
	 */
	union EXTI_FTSR
	{
		_IO REG;
		struct
		{
			_IO TR0 : 1;
			_IO TR1 : 1;
			_IO TR2 : 1;
			_IO TR3 : 1;
			_IO TR4 : 1;
			_IO TR5 : 1;
			_IO TR6 : 1;
			_IO TR7 : 1;
			_IO TR8 : 1;
			_IO TR9 : 1;
			_IO TR10 : 1;
			_IO TR11 : 1;
			_IO TR12 : 1;
			_IO TR13 : 1;
			_IO TR14 : 1;
			_IO TR15 : 1;
			_IO TR16 : 1;
			_IO TR17 : 1;
			_IO TR18 : 1;
			_IO TR19 : 1;
			_IO RESERVED_FTSR : 12;
		} BIT;
	} FTSR;

	/**
	 * @ingroup EXTI_01_RegisterLayer_07_RegisterMap
	 * @section EXTI_TypeDef_SWIER Software Interrupt Event Register (SWIER)
	 * @brief [R/W] Software interrupt/event request register
	 * @details
	 * Writing one to bits 0 to 19 raises the matching software interrupt/event
	 * request when the line is not already pending. Bits 20 to 31 are reserved.
	 */
	union EXTI_SWIER
	{
		_IO REG;
		struct
		{
			_IO SWIER0 : 1;
			_IO SWIER1 : 1;
			_IO SWIER2 : 1;
			_IO SWIER3 : 1;
			_IO SWIER4 : 1;
			_IO SWIER5 : 1;
			_IO SWIER6 : 1;
			_IO SWIER7 : 1;
			_IO SWIER8 : 1;
			_IO SWIER9 : 1;
			_IO SWIER10 : 1;
			_IO SWIER11 : 1;
			_IO SWIER12 : 1;
			_IO SWIER13 : 1;
			_IO SWIER14 : 1;
			_IO SWIER15 : 1;
			_IO SWIER16 : 1;
			_IO SWIER17 : 1;
			_IO SWIER18 : 1;
			_IO SWIER19 : 1;
			_IO RESERVED_SWIER : 12;
		} BIT;
	} SWIER;

	/**
	 * @ingroup EXTI_01_RegisterLayer_07_RegisterMap
	 * @section EXTI_TypeDef_PR Pending Register (PR)
	 * @brief [R/W1C] Pending state register for EXTI lines
	 * @details
	 * Bits 0 to 19 indicate pending EXTI lines. Writing one clears the matching
	 * pending bit. Bits 20 to 31 are reserved.
	 */
	union EXTI_PR
	{
		_IO REG;
		struct
		{
			_IO PR0 : 1;
			_IO PR1 : 1;
			_IO PR2 : 1;
			_IO PR3 : 1;
			_IO PR4 : 1;
			_IO PR5 : 1;
			_IO PR6 : 1;
			_IO PR7 : 1;
			_IO PR8 : 1;
			_IO PR9 : 1;
			_IO PR10 : 1;
			_IO PR11 : 1;
			_IO PR12 : 1;
			_IO PR13 : 1;
			_IO PR14 : 1;
			_IO PR15 : 1;
			_IO PR16 : 1;
			_IO PR17 : 1;
			_IO PR18 : 1;
			_IO PR19 : 1;
			_IO RESERVED_PR : 12;
		} BIT;
	} PR;

} EXTI_TypeDef;

/** @} */ // EXTI_01_RegisterLayer_07_RegisterMap

/** @} */ // EXTI_01_RegisterLayer

// C++ Header Guards
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_EXTI_H_ */
