/**
 * @file stm32f1xx_afio.h
 * @author Shrey Shah
 * @brief STM32F1 AFIO Register-Layer Definitions
 * @version v1.1
 * @date 30-05-2026
 */
#ifndef STM32F1XX_AFIO_H_
#define STM32F1XX_AFIO_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx_utils.h"

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup AFIO Alternate Function I/O (AFIO)
 * @brief STM32F1 alternate-function remap and EXTI source-selection register model
 * @details
 * AFIO is the hardware block that:
 * - selects the event output pin and port through EVCR,
 * - controls peripheral remapping and SWJ configuration through MAPR,
 * - routes GPIO ports to EXTI lines through EXTICR1 through EXTICR4.
 *
 * This file owns only the raw memory-mapped register view. GPIO EXTI routing,
 * public selectors, validation, and sequencing belong above the core layer.
 */

/**
 * @defgroup AFIO_01_RegisterLayer AFIO Register Layer
 * @ingroup AFIO
 * @brief Raw AFIO register structure and hardware-visible bitfield layout
 * @details
 * This layer mirrors the hardware-visible AFIO register map. It does not own
 * public GPIO selector vocabulary, EXTI routing policy, or driver validation.
 */

/**
 * @addtogroup AFIO_01_RegisterLayer
 * @{
 */

// ------------------------------------------------------------------------------------------
// AFIO_EVCR (Event Control Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief AFIO Event Control Register Definitions
 * @defgroup AFIO_01_RegisterLayer_01_EventControl AFIO Event Control Register
 * @ingroup AFIO_01_RegisterLayer
 * @details
 * @section AFIO_EVCR_Theory Theory and Practical Role
 * This page documents `AFIO_EVCR`, which selects the GPIO pin and port used for
 * event output and enables or disables the event output path.
 *
 * @section AFIO_EVCR_Macros Register-Specific Macros
 * The macro definitions below expose raw bit positions, masks, and convenience
 * aliases used by LL layers when they need direct symbolic access to `AFIO_EVCR`.
 *
 * @section AFIO_EVCR_Union Register Union View
 * The `union AFIO_EVCR` view inside @ref AFIO_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ PIN[3:0] (Event Output Pin Selection) ------ //
/** @brief AFIO_EVCR_PIN Position @def AFIO_EVCR_PIN_Pos */
#define AFIO_EVCR_PIN_Pos					(0U)
/** @brief AFIO_EVCR_PIN Mask @def AFIO_EVCR_PIN_Msk */
#define AFIO_EVCR_PIN_Msk					(REG_FIELD_VALUE(0xFUL, AFIO_EVCR_PIN_Pos))
/** @brief Event Output Pin Selection @def AFIO_EVCR_PIN */
#define AFIO_EVCR_PIN						AFIO_EVCR_PIN_Msk
/** @brief PIN bit 0 @def AFIO_EVCR_PIN_0 */
#define AFIO_EVCR_PIN_0						(REG_FIELD_VALUE(0x1UL, AFIO_EVCR_PIN_Pos))
/** @brief PIN bit 1 @def AFIO_EVCR_PIN_1 */
#define AFIO_EVCR_PIN_1						(REG_FIELD_VALUE(0x2UL, AFIO_EVCR_PIN_Pos))
/** @brief PIN bit 2 @def AFIO_EVCR_PIN_2 */
#define AFIO_EVCR_PIN_2						(REG_FIELD_VALUE(0x4UL, AFIO_EVCR_PIN_Pos))
/** @brief PIN bit 3 @def AFIO_EVCR_PIN_3 */
#define AFIO_EVCR_PIN_3						(REG_FIELD_VALUE(0x8UL, AFIO_EVCR_PIN_Pos))

// ------ PORT[2:0] (Event Output Port Selection) ------ //
/** @brief AFIO_EVCR_PORT Position @def AFIO_EVCR_PORT_Pos */
#define AFIO_EVCR_PORT_Pos					(4U)
/** @brief AFIO_EVCR_PORT Mask @def AFIO_EVCR_PORT_Msk */
#define AFIO_EVCR_PORT_Msk					(REG_FIELD_VALUE(0x7UL, AFIO_EVCR_PORT_Pos))
/** @brief Event Output Port Selection @def AFIO_EVCR_PORT */
#define AFIO_EVCR_PORT						AFIO_EVCR_PORT_Msk
/** @brief PORT bit 0 @def AFIO_EVCR_PORT_0 */
#define AFIO_EVCR_PORT_0					(REG_FIELD_VALUE(0x1UL, AFIO_EVCR_PORT_Pos))
/** @brief PORT bit 1 @def AFIO_EVCR_PORT_1 */
#define AFIO_EVCR_PORT_1					(REG_FIELD_VALUE(0x2UL, AFIO_EVCR_PORT_Pos))
/** @brief PORT bit 2 @def AFIO_EVCR_PORT_2 */
#define AFIO_EVCR_PORT_2					(REG_FIELD_VALUE(0x4UL, AFIO_EVCR_PORT_Pos))

// ------ EVOE (Event Output Enable) ------ //
/** @brief AFIO_EVCR_EVOE Position @def AFIO_EVCR_EVOE_Pos */
#define AFIO_EVCR_EVOE_Pos					(7U)
/** @brief AFIO_EVCR_EVOE Mask @def AFIO_EVCR_EVOE_Msk */
#define AFIO_EVCR_EVOE_Msk					(REG_FIELD_VALUE(0x1UL, AFIO_EVCR_EVOE_Pos))
/** @brief Event Output Enable @def AFIO_EVCR_EVOE */
#define AFIO_EVCR_EVOE						AFIO_EVCR_EVOE_Msk

/** @} */ // AFIO_01_RegisterLayer_01_EventControl

// ------------------------------------------------------------------------------------------
// AFIO_MAPR (AF Remap and Debug I/O Configuration Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief AFIO Remap and Debug Configuration Register Definitions
 * @defgroup AFIO_01_RegisterLayer_02_RemapDebug AFIO Remap and Debug Configuration Register
 * @ingroup AFIO_01_RegisterLayer
 * @details
 * @section AFIO_MAPR_Theory Theory and Practical Role
 * This page documents `AFIO_MAPR`, which controls peripheral alternate-function
 * remapping and serial-wire/JTAG debug-port configuration.
 *
 * @section AFIO_MAPR_Macros Register-Specific Macros
 * The macro definitions below expose raw bit positions, masks, and convenience
 * aliases used by LL layers when they need direct symbolic access to `AFIO_MAPR`.
 *
 * @section AFIO_MAPR_Union Register Union View
 * The `union AFIO_MAPR` view inside @ref AFIO_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ SPI1_REMAP ------ //
/** @brief AFIO_MAPR_SPI1_REMAP Position @def AFIO_MAPR_SPI1_REMAP_Pos */
#define AFIO_MAPR_SPI1_REMAP_Pos			(0U)
/** @brief AFIO_MAPR_SPI1_REMAP Mask @def AFIO_MAPR_SPI1_REMAP_Msk */
#define AFIO_MAPR_SPI1_REMAP_Msk			(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_SPI1_REMAP_Pos))
/** @brief SPI1 Remap @def AFIO_MAPR_SPI1_REMAP */
#define AFIO_MAPR_SPI1_REMAP				AFIO_MAPR_SPI1_REMAP_Msk

// ------ I2C1_REMAP ------ //
/** @brief AFIO_MAPR_I2C1_REMAP Position @def AFIO_MAPR_I2C1_REMAP_Pos */
#define AFIO_MAPR_I2C1_REMAP_Pos			(1U)
/** @brief AFIO_MAPR_I2C1_REMAP Mask @def AFIO_MAPR_I2C1_REMAP_Msk */
#define AFIO_MAPR_I2C1_REMAP_Msk			(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_I2C1_REMAP_Pos))
/** @brief I2C1 Remap @def AFIO_MAPR_I2C1_REMAP */
#define AFIO_MAPR_I2C1_REMAP				AFIO_MAPR_I2C1_REMAP_Msk

// ------ USART1_REMAP ------ //
/** @brief AFIO_MAPR_USART1_REMAP Position @def AFIO_MAPR_USART1_REMAP_Pos */
#define AFIO_MAPR_USART1_REMAP_Pos			(2U)
/** @brief AFIO_MAPR_USART1_REMAP Mask @def AFIO_MAPR_USART1_REMAP_Msk */
#define AFIO_MAPR_USART1_REMAP_Msk			(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_USART1_REMAP_Pos))
/** @brief USART1 Remap @def AFIO_MAPR_USART1_REMAP */
#define AFIO_MAPR_USART1_REMAP				AFIO_MAPR_USART1_REMAP_Msk

// ------ USART2_REMAP ------ //
/** @brief AFIO_MAPR_USART2_REMAP Position @def AFIO_MAPR_USART2_REMAP_Pos */
#define AFIO_MAPR_USART2_REMAP_Pos			(3U)
/** @brief AFIO_MAPR_USART2_REMAP Mask @def AFIO_MAPR_USART2_REMAP_Msk */
#define AFIO_MAPR_USART2_REMAP_Msk			(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_USART2_REMAP_Pos))
/** @brief USART2 Remap @def AFIO_MAPR_USART2_REMAP */
#define AFIO_MAPR_USART2_REMAP				AFIO_MAPR_USART2_REMAP_Msk

// ------ USART3_REMAP[1:0] ------ //
/** @brief AFIO_MAPR_USART3_REMAP Position @def AFIO_MAPR_USART3_REMAP_Pos */
#define AFIO_MAPR_USART3_REMAP_Pos			(4U)
/** @brief AFIO_MAPR_USART3_REMAP Mask @def AFIO_MAPR_USART3_REMAP_Msk */
#define AFIO_MAPR_USART3_REMAP_Msk			(REG_FIELD_VALUE(0x3UL, AFIO_MAPR_USART3_REMAP_Pos))
/** @brief USART3 Remap @def AFIO_MAPR_USART3_REMAP */
#define AFIO_MAPR_USART3_REMAP				AFIO_MAPR_USART3_REMAP_Msk
/** @brief USART3_REMAP bit 0 @def AFIO_MAPR_USART3_REMAP_0 */
#define AFIO_MAPR_USART3_REMAP_0			(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_USART3_REMAP_Pos))
/** @brief USART3_REMAP bit 1 @def AFIO_MAPR_USART3_REMAP_1 */
#define AFIO_MAPR_USART3_REMAP_1			(REG_FIELD_VALUE(0x2UL, AFIO_MAPR_USART3_REMAP_Pos))

// ------ TIM1_REMAP[1:0] ------ //
/** @brief AFIO_MAPR_TIM1_REMAP Position @def AFIO_MAPR_TIM1_REMAP_Pos */
#define AFIO_MAPR_TIM1_REMAP_Pos			(6U)
/** @brief AFIO_MAPR_TIM1_REMAP Mask @def AFIO_MAPR_TIM1_REMAP_Msk */
#define AFIO_MAPR_TIM1_REMAP_Msk			(REG_FIELD_VALUE(0x3UL, AFIO_MAPR_TIM1_REMAP_Pos))
/** @brief TIM1 Remap @def AFIO_MAPR_TIM1_REMAP */
#define AFIO_MAPR_TIM1_REMAP				AFIO_MAPR_TIM1_REMAP_Msk
/** @brief TIM1_REMAP bit 0 @def AFIO_MAPR_TIM1_REMAP_0 */
#define AFIO_MAPR_TIM1_REMAP_0				(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_TIM1_REMAP_Pos))
/** @brief TIM1_REMAP bit 1 @def AFIO_MAPR_TIM1_REMAP_1 */
#define AFIO_MAPR_TIM1_REMAP_1				(REG_FIELD_VALUE(0x2UL, AFIO_MAPR_TIM1_REMAP_Pos))

// ------ TIM2_REMAP[1:0] ------ //
/** @brief AFIO_MAPR_TIM2_REMAP Position @def AFIO_MAPR_TIM2_REMAP_Pos */
#define AFIO_MAPR_TIM2_REMAP_Pos			(8U)
/** @brief AFIO_MAPR_TIM2_REMAP Mask @def AFIO_MAPR_TIM2_REMAP_Msk */
#define AFIO_MAPR_TIM2_REMAP_Msk			(REG_FIELD_VALUE(0x3UL, AFIO_MAPR_TIM2_REMAP_Pos))
/** @brief TIM2 Remap @def AFIO_MAPR_TIM2_REMAP */
#define AFIO_MAPR_TIM2_REMAP				AFIO_MAPR_TIM2_REMAP_Msk
/** @brief TIM2_REMAP bit 0 @def AFIO_MAPR_TIM2_REMAP_0 */
#define AFIO_MAPR_TIM2_REMAP_0				(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_TIM2_REMAP_Pos))
/** @brief TIM2_REMAP bit 1 @def AFIO_MAPR_TIM2_REMAP_1 */
#define AFIO_MAPR_TIM2_REMAP_1				(REG_FIELD_VALUE(0x2UL, AFIO_MAPR_TIM2_REMAP_Pos))

// ------ TIM3_REMAP[1:0] ------ //
/** @brief AFIO_MAPR_TIM3_REMAP Position @def AFIO_MAPR_TIM3_REMAP_Pos */
#define AFIO_MAPR_TIM3_REMAP_Pos			(10U)
/** @brief AFIO_MAPR_TIM3_REMAP Mask @def AFIO_MAPR_TIM3_REMAP_Msk */
#define AFIO_MAPR_TIM3_REMAP_Msk			(REG_FIELD_VALUE(0x3UL, AFIO_MAPR_TIM3_REMAP_Pos))
/** @brief TIM3 Remap @def AFIO_MAPR_TIM3_REMAP */
#define AFIO_MAPR_TIM3_REMAP				AFIO_MAPR_TIM3_REMAP_Msk
/** @brief TIM3_REMAP bit 0 @def AFIO_MAPR_TIM3_REMAP_0 */
#define AFIO_MAPR_TIM3_REMAP_0				(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_TIM3_REMAP_Pos))
/** @brief TIM3_REMAP bit 1 @def AFIO_MAPR_TIM3_REMAP_1 */
#define AFIO_MAPR_TIM3_REMAP_1				(REG_FIELD_VALUE(0x2UL, AFIO_MAPR_TIM3_REMAP_Pos))

// ------ TIM4_REMAP ------ //
/** @brief AFIO_MAPR_TIM4_REMAP Position @def AFIO_MAPR_TIM4_REMAP_Pos */
#define AFIO_MAPR_TIM4_REMAP_Pos			(12U)
/** @brief AFIO_MAPR_TIM4_REMAP Mask @def AFIO_MAPR_TIM4_REMAP_Msk */
#define AFIO_MAPR_TIM4_REMAP_Msk			(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_TIM4_REMAP_Pos))
/** @brief TIM4 Remap @def AFIO_MAPR_TIM4_REMAP */
#define AFIO_MAPR_TIM4_REMAP				AFIO_MAPR_TIM4_REMAP_Msk

// ------ CAN_REMAP[1:0] ------ //
/** @brief AFIO_MAPR_CAN_REMAP Position @def AFIO_MAPR_CAN_REMAP_Pos */
#define AFIO_MAPR_CAN_REMAP_Pos				(13U)
/** @brief AFIO_MAPR_CAN_REMAP Mask @def AFIO_MAPR_CAN_REMAP_Msk */
#define AFIO_MAPR_CAN_REMAP_Msk				(REG_FIELD_VALUE(0x3UL, AFIO_MAPR_CAN_REMAP_Pos))
/** @brief CAN Remap @def AFIO_MAPR_CAN_REMAP */
#define AFIO_MAPR_CAN_REMAP					AFIO_MAPR_CAN_REMAP_Msk
/** @brief CAN_REMAP bit 0 @def AFIO_MAPR_CAN_REMAP_0 */
#define AFIO_MAPR_CAN_REMAP_0				(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_CAN_REMAP_Pos))
/** @brief CAN_REMAP bit 1 @def AFIO_MAPR_CAN_REMAP_1 */
#define AFIO_MAPR_CAN_REMAP_1				(REG_FIELD_VALUE(0x2UL, AFIO_MAPR_CAN_REMAP_Pos))

// ------ PD01_REMAP ------ //
/** @brief AFIO_MAPR_PD01_REMAP Position @def AFIO_MAPR_PD01_REMAP_Pos */
#define AFIO_MAPR_PD01_REMAP_Pos			(15U)
/** @brief AFIO_MAPR_PD01_REMAP Mask @def AFIO_MAPR_PD01_REMAP_Msk */
#define AFIO_MAPR_PD01_REMAP_Msk			(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_PD01_REMAP_Pos))
/** @brief Port D0/D1 Remap @def AFIO_MAPR_PD01_REMAP */
#define AFIO_MAPR_PD01_REMAP				AFIO_MAPR_PD01_REMAP_Msk

// ------ TIM5CH4_IREMAP ------ //
/** @brief AFIO_MAPR_TIM5CH4_IREMAP Position @def AFIO_MAPR_TIM5CH4_IREMAP_Pos */
#define AFIO_MAPR_TIM5CH4_IREMAP_Pos		(16U)
/** @brief AFIO_MAPR_TIM5CH4_IREMAP Mask @def AFIO_MAPR_TIM5CH4_IREMAP_Msk */
#define AFIO_MAPR_TIM5CH4_IREMAP_Msk		(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_TIM5CH4_IREMAP_Pos))
/** @brief TIM5 Channel 4 Internal Remap @def AFIO_MAPR_TIM5CH4_IREMAP */
#define AFIO_MAPR_TIM5CH4_IREMAP			AFIO_MAPR_TIM5CH4_IREMAP_Msk

// ------ ADC1_ETRGINJ_REMAP ------ //
/** @brief AFIO_MAPR_ADC1_ETRGINJ_REMAP Position @def AFIO_MAPR_ADC1_ETRGINJ_REMAP_Pos */
#define AFIO_MAPR_ADC1_ETRGINJ_REMAP_Pos	(17U)
/** @brief AFIO_MAPR_ADC1_ETRGINJ_REMAP Mask @def AFIO_MAPR_ADC1_ETRGINJ_REMAP_Msk */
#define AFIO_MAPR_ADC1_ETRGINJ_REMAP_Msk	(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_ADC1_ETRGINJ_REMAP_Pos))
/** @brief ADC1 External Trigger Injected Conversion Remap @def AFIO_MAPR_ADC1_ETRGINJ_REMAP */
#define AFIO_MAPR_ADC1_ETRGINJ_REMAP		AFIO_MAPR_ADC1_ETRGINJ_REMAP_Msk

// ------ ADC1_ETGREG_REMAP ------ //
/** @brief AFIO_MAPR_ADC1_ETGREG_REMAP Position @def AFIO_MAPR_ADC1_ETGREG_REMAP_Pos */
#define AFIO_MAPR_ADC1_ETGREG_REMAP_Pos		(18U)
/** @brief AFIO_MAPR_ADC1_ETGREG_REMAP Mask @def AFIO_MAPR_ADC1_ETGREG_REMAP_Msk */
#define AFIO_MAPR_ADC1_ETGREG_REMAP_Msk		(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_ADC1_ETGREG_REMAP_Pos))
/** @brief ADC1 External Trigger Regular Conversion Remap @def AFIO_MAPR_ADC1_ETGREG_REMAP */
#define AFIO_MAPR_ADC1_ETGREG_REMAP			AFIO_MAPR_ADC1_ETGREG_REMAP_Msk

// ------ ADC2_ETRGINJ_REMAP ------ //
/** @brief AFIO_MAPR_ADC2_ETRGINJ_REMAP Position @def AFIO_MAPR_ADC2_ETRGINJ_REMAP_Pos */
#define AFIO_MAPR_ADC2_ETRGINJ_REMAP_Pos	(19U)
/** @brief AFIO_MAPR_ADC2_ETRGINJ_REMAP Mask @def AFIO_MAPR_ADC2_ETRGINJ_REMAP_Msk */
#define AFIO_MAPR_ADC2_ETRGINJ_REMAP_Msk	(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_ADC2_ETRGINJ_REMAP_Pos))
/** @brief ADC2 External Trigger Injected Conversion Remap @def AFIO_MAPR_ADC2_ETRGINJ_REMAP */
#define AFIO_MAPR_ADC2_ETRGINJ_REMAP		AFIO_MAPR_ADC2_ETRGINJ_REMAP_Msk

// ------ ADC2_ETGREG_REMAP ------ //
/** @brief AFIO_MAPR_ADC2_ETGREG_REMAP Position @def AFIO_MAPR_ADC2_ETGREG_REMAP_Pos */
#define AFIO_MAPR_ADC2_ETGREG_REMAP_Pos		(20U)
/** @brief AFIO_MAPR_ADC2_ETGREG_REMAP Mask @def AFIO_MAPR_ADC2_ETGREG_REMAP_Msk */
#define AFIO_MAPR_ADC2_ETGREG_REMAP_Msk		(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_ADC2_ETGREG_REMAP_Pos))
/** @brief ADC2 External Trigger Regular Conversion Remap @def AFIO_MAPR_ADC2_ETGREG_REMAP */
#define AFIO_MAPR_ADC2_ETGREG_REMAP			AFIO_MAPR_ADC2_ETGREG_REMAP_Msk

// ------ SWJ_CFG[2:0] ------ //
/** @brief AFIO_MAPR_SWJ_CFG Position @def AFIO_MAPR_SWJ_CFG_Pos */
#define AFIO_MAPR_SWJ_CFG_Pos				(24U)
/** @brief AFIO_MAPR_SWJ_CFG Mask @def AFIO_MAPR_SWJ_CFG_Msk */
#define AFIO_MAPR_SWJ_CFG_Msk				(REG_FIELD_VALUE(0x7UL, AFIO_MAPR_SWJ_CFG_Pos))
/** @brief Serial Wire JTAG Configuration @def AFIO_MAPR_SWJ_CFG */
#define AFIO_MAPR_SWJ_CFG					AFIO_MAPR_SWJ_CFG_Msk
/** @brief SWJ_CFG bit 0 @def AFIO_MAPR_SWJ_CFG_0 */
#define AFIO_MAPR_SWJ_CFG_0					(REG_FIELD_VALUE(0x1UL, AFIO_MAPR_SWJ_CFG_Pos))
/** @brief SWJ_CFG bit 1 @def AFIO_MAPR_SWJ_CFG_1 */
#define AFIO_MAPR_SWJ_CFG_1					(REG_FIELD_VALUE(0x2UL, AFIO_MAPR_SWJ_CFG_Pos))
/** @brief SWJ_CFG bit 2 @def AFIO_MAPR_SWJ_CFG_2 */
#define AFIO_MAPR_SWJ_CFG_2					(REG_FIELD_VALUE(0x4UL, AFIO_MAPR_SWJ_CFG_Pos))

/** @} */ // AFIO_01_RegisterLayer_02_RemapDebug

// ------------------------------------------------------------------------------------------
// AFIO_EXTICR1 (External Interrupt Configuration Register 1)
// ------------------------------------------------------------------------------------------

/**
 * @brief AFIO External Interrupt Configuration Register 1 Definitions
 * @defgroup AFIO_01_RegisterLayer_03_ExtiConfig1 AFIO External Interrupt Configuration Register 1
 * @ingroup AFIO_01_RegisterLayer
 * @details
 * @section AFIO_EXTICR1_Theory Theory and Practical Role
 * This page documents `AFIO_EXTICR1`, which selects the GPIO port source for
 * EXTI lines 0 through 3.
 *
 * @section AFIO_EXTICR1_Macros Register-Specific Macros
 * The macro definitions below expose raw bit positions, masks, and convenience
 * aliases used by LL layers when they need direct symbolic access to
 * `AFIO_EXTICR1`.
 *
 * @section AFIO_EXTICR1_Union Register Union View
 * The `union AFIO_EXTICR1` view inside @ref AFIO_TypeDef mirrors the same
 * register in software so a developer can compare the full register image
 * (`.REG`) against the named bitfield view (`.BIT`).
 * @{
 */

// ------ EXTI0[3:0] ------ //
/** @brief AFIO_EXTICR1_EXTI0 Position @def AFIO_EXTICR1_EXTI0_Pos */
#define AFIO_EXTICR1_EXTI0_Pos				(0U)
/** @brief AFIO_EXTICR1_EXTI0 Mask @def AFIO_EXTICR1_EXTI0_Msk */
#define AFIO_EXTICR1_EXTI0_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR1_EXTI0_Pos))
/** @brief EXTI Line 0 Port Source @def AFIO_EXTICR1_EXTI0 */
#define AFIO_EXTICR1_EXTI0					AFIO_EXTICR1_EXTI0_Msk
/** @brief EXTI0 bit 0 @def AFIO_EXTICR1_EXTI0_0 */
#define AFIO_EXTICR1_EXTI0_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR1_EXTI0_Pos))
/** @brief EXTI0 bit 1 @def AFIO_EXTICR1_EXTI0_1 */
#define AFIO_EXTICR1_EXTI0_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR1_EXTI0_Pos))
/** @brief EXTI0 bit 2 @def AFIO_EXTICR1_EXTI0_2 */
#define AFIO_EXTICR1_EXTI0_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR1_EXTI0_Pos))
/** @brief EXTI0 bit 3 @def AFIO_EXTICR1_EXTI0_3 */
#define AFIO_EXTICR1_EXTI0_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR1_EXTI0_Pos))

// ------ EXTI1[3:0] ------ //
/** @brief AFIO_EXTICR1_EXTI1 Position @def AFIO_EXTICR1_EXTI1_Pos */
#define AFIO_EXTICR1_EXTI1_Pos				(4U)
/** @brief AFIO_EXTICR1_EXTI1 Mask @def AFIO_EXTICR1_EXTI1_Msk */
#define AFIO_EXTICR1_EXTI1_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR1_EXTI1_Pos))
/** @brief EXTI Line 1 Port Source @def AFIO_EXTICR1_EXTI1 */
#define AFIO_EXTICR1_EXTI1					AFIO_EXTICR1_EXTI1_Msk
/** @brief EXTI1 bit 0 @def AFIO_EXTICR1_EXTI1_0 */
#define AFIO_EXTICR1_EXTI1_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR1_EXTI1_Pos))
/** @brief EXTI1 bit 1 @def AFIO_EXTICR1_EXTI1_1 */
#define AFIO_EXTICR1_EXTI1_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR1_EXTI1_Pos))
/** @brief EXTI1 bit 2 @def AFIO_EXTICR1_EXTI1_2 */
#define AFIO_EXTICR1_EXTI1_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR1_EXTI1_Pos))
/** @brief EXTI1 bit 3 @def AFIO_EXTICR1_EXTI1_3 */
#define AFIO_EXTICR1_EXTI1_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR1_EXTI1_Pos))

// ------ EXTI2[3:0] ------ //
/** @brief AFIO_EXTICR1_EXTI2 Position @def AFIO_EXTICR1_EXTI2_Pos */
#define AFIO_EXTICR1_EXTI2_Pos				(8U)
/** @brief AFIO_EXTICR1_EXTI2 Mask @def AFIO_EXTICR1_EXTI2_Msk */
#define AFIO_EXTICR1_EXTI2_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR1_EXTI2_Pos))
/** @brief EXTI Line 2 Port Source @def AFIO_EXTICR1_EXTI2 */
#define AFIO_EXTICR1_EXTI2					AFIO_EXTICR1_EXTI2_Msk
/** @brief EXTI2 bit 0 @def AFIO_EXTICR1_EXTI2_0 */
#define AFIO_EXTICR1_EXTI2_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR1_EXTI2_Pos))
/** @brief EXTI2 bit 1 @def AFIO_EXTICR1_EXTI2_1 */
#define AFIO_EXTICR1_EXTI2_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR1_EXTI2_Pos))
/** @brief EXTI2 bit 2 @def AFIO_EXTICR1_EXTI2_2 */
#define AFIO_EXTICR1_EXTI2_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR1_EXTI2_Pos))
/** @brief EXTI2 bit 3 @def AFIO_EXTICR1_EXTI2_3 */
#define AFIO_EXTICR1_EXTI2_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR1_EXTI2_Pos))

// ------ EXTI3[3:0] ------ //
/** @brief AFIO_EXTICR1_EXTI3 Position @def AFIO_EXTICR1_EXTI3_Pos */
#define AFIO_EXTICR1_EXTI3_Pos				(12U)
/** @brief AFIO_EXTICR1_EXTI3 Mask @def AFIO_EXTICR1_EXTI3_Msk */
#define AFIO_EXTICR1_EXTI3_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR1_EXTI3_Pos))
/** @brief EXTI Line 3 Port Source @def AFIO_EXTICR1_EXTI3 */
#define AFIO_EXTICR1_EXTI3					AFIO_EXTICR1_EXTI3_Msk
/** @brief EXTI3 bit 0 @def AFIO_EXTICR1_EXTI3_0 */
#define AFIO_EXTICR1_EXTI3_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR1_EXTI3_Pos))
/** @brief EXTI3 bit 1 @def AFIO_EXTICR1_EXTI3_1 */
#define AFIO_EXTICR1_EXTI3_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR1_EXTI3_Pos))
/** @brief EXTI3 bit 2 @def AFIO_EXTICR1_EXTI3_2 */
#define AFIO_EXTICR1_EXTI3_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR1_EXTI3_Pos))
/** @brief EXTI3 bit 3 @def AFIO_EXTICR1_EXTI3_3 */
#define AFIO_EXTICR1_EXTI3_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR1_EXTI3_Pos))

/** @} */ // AFIO_01_RegisterLayer_03_ExtiConfig1

// ------------------------------------------------------------------------------------------
// AFIO_EXTICR2 (External Interrupt Configuration Register 2)
// ------------------------------------------------------------------------------------------

/**
 * @brief AFIO External Interrupt Configuration Register 2 Definitions
 * @defgroup AFIO_01_RegisterLayer_04_ExtiConfig2 AFIO External Interrupt Configuration Register 2
 * @ingroup AFIO_01_RegisterLayer
 * @details
 * @section AFIO_EXTICR2_Theory Theory and Practical Role
 * This page documents `AFIO_EXTICR2`, which selects the GPIO port source for
 * EXTI lines 4 through 7.
 *
 * @section AFIO_EXTICR2_Macros Register-Specific Macros
 * The macro definitions below expose raw bit positions, masks, and convenience
 * aliases used by LL layers when they need direct symbolic access to
 * `AFIO_EXTICR2`.
 *
 * @section AFIO_EXTICR2_Union Register Union View
 * The `union AFIO_EXTICR2` view inside @ref AFIO_TypeDef mirrors the same
 * register in software so a developer can compare the full register image
 * (`.REG`) against the named bitfield view (`.BIT`).
 * @{
 */

// ------ EXTI4[3:0] ------ //
/** @brief AFIO_EXTICR2_EXTI4 Position @def AFIO_EXTICR2_EXTI4_Pos */
#define AFIO_EXTICR2_EXTI4_Pos				(0U)
/** @brief AFIO_EXTICR2_EXTI4 Mask @def AFIO_EXTICR2_EXTI4_Msk */
#define AFIO_EXTICR2_EXTI4_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR2_EXTI4_Pos))
/** @brief EXTI Line 4 Port Source @def AFIO_EXTICR2_EXTI4 */
#define AFIO_EXTICR2_EXTI4					AFIO_EXTICR2_EXTI4_Msk
/** @brief EXTI4 bit 0 @def AFIO_EXTICR2_EXTI4_0 */
#define AFIO_EXTICR2_EXTI4_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR2_EXTI4_Pos))
/** @brief EXTI4 bit 1 @def AFIO_EXTICR2_EXTI4_1 */
#define AFIO_EXTICR2_EXTI4_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR2_EXTI4_Pos))
/** @brief EXTI4 bit 2 @def AFIO_EXTICR2_EXTI4_2 */
#define AFIO_EXTICR2_EXTI4_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR2_EXTI4_Pos))
/** @brief EXTI4 bit 3 @def AFIO_EXTICR2_EXTI4_3 */
#define AFIO_EXTICR2_EXTI4_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR2_EXTI4_Pos))

// ------ EXTI5[3:0] ------ //
/** @brief AFIO_EXTICR2_EXTI5 Position @def AFIO_EXTICR2_EXTI5_Pos */
#define AFIO_EXTICR2_EXTI5_Pos				(4U)
/** @brief AFIO_EXTICR2_EXTI5 Mask @def AFIO_EXTICR2_EXTI5_Msk */
#define AFIO_EXTICR2_EXTI5_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR2_EXTI5_Pos))
/** @brief EXTI Line 5 Port Source @def AFIO_EXTICR2_EXTI5 */
#define AFIO_EXTICR2_EXTI5					AFIO_EXTICR2_EXTI5_Msk
/** @brief EXTI5 bit 0 @def AFIO_EXTICR2_EXTI5_0 */
#define AFIO_EXTICR2_EXTI5_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR2_EXTI5_Pos))
/** @brief EXTI5 bit 1 @def AFIO_EXTICR2_EXTI5_1 */
#define AFIO_EXTICR2_EXTI5_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR2_EXTI5_Pos))
/** @brief EXTI5 bit 2 @def AFIO_EXTICR2_EXTI5_2 */
#define AFIO_EXTICR2_EXTI5_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR2_EXTI5_Pos))
/** @brief EXTI5 bit 3 @def AFIO_EXTICR2_EXTI5_3 */
#define AFIO_EXTICR2_EXTI5_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR2_EXTI5_Pos))

// ------ EXTI6[3:0] ------ //
/** @brief AFIO_EXTICR2_EXTI6 Position @def AFIO_EXTICR2_EXTI6_Pos */
#define AFIO_EXTICR2_EXTI6_Pos				(8U)
/** @brief AFIO_EXTICR2_EXTI6 Mask @def AFIO_EXTICR2_EXTI6_Msk */
#define AFIO_EXTICR2_EXTI6_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR2_EXTI6_Pos))
/** @brief EXTI Line 6 Port Source @def AFIO_EXTICR2_EXTI6 */
#define AFIO_EXTICR2_EXTI6					AFIO_EXTICR2_EXTI6_Msk
/** @brief EXTI6 bit 0 @def AFIO_EXTICR2_EXTI6_0 */
#define AFIO_EXTICR2_EXTI6_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR2_EXTI6_Pos))
/** @brief EXTI6 bit 1 @def AFIO_EXTICR2_EXTI6_1 */
#define AFIO_EXTICR2_EXTI6_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR2_EXTI6_Pos))
/** @brief EXTI6 bit 2 @def AFIO_EXTICR2_EXTI6_2 */
#define AFIO_EXTICR2_EXTI6_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR2_EXTI6_Pos))
/** @brief EXTI6 bit 3 @def AFIO_EXTICR2_EXTI6_3 */
#define AFIO_EXTICR2_EXTI6_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR2_EXTI6_Pos))

// ------ EXTI7[3:0] ------ //
/** @brief AFIO_EXTICR2_EXTI7 Position @def AFIO_EXTICR2_EXTI7_Pos */
#define AFIO_EXTICR2_EXTI7_Pos				(12U)
/** @brief AFIO_EXTICR2_EXTI7 Mask @def AFIO_EXTICR2_EXTI7_Msk */
#define AFIO_EXTICR2_EXTI7_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR2_EXTI7_Pos))
/** @brief EXTI Line 7 Port Source @def AFIO_EXTICR2_EXTI7 */
#define AFIO_EXTICR2_EXTI7					AFIO_EXTICR2_EXTI7_Msk
/** @brief EXTI7 bit 0 @def AFIO_EXTICR2_EXTI7_0 */
#define AFIO_EXTICR2_EXTI7_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR2_EXTI7_Pos))
/** @brief EXTI7 bit 1 @def AFIO_EXTICR2_EXTI7_1 */
#define AFIO_EXTICR2_EXTI7_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR2_EXTI7_Pos))
/** @brief EXTI7 bit 2 @def AFIO_EXTICR2_EXTI7_2 */
#define AFIO_EXTICR2_EXTI7_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR2_EXTI7_Pos))
/** @brief EXTI7 bit 3 @def AFIO_EXTICR2_EXTI7_3 */
#define AFIO_EXTICR2_EXTI7_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR2_EXTI7_Pos))

/** @} */ // AFIO_01_RegisterLayer_04_ExtiConfig2

// ------------------------------------------------------------------------------------------
// AFIO_EXTICR3 (External Interrupt Configuration Register 3)
// ------------------------------------------------------------------------------------------

/**
 * @brief AFIO External Interrupt Configuration Register 3 Definitions
 * @defgroup AFIO_01_RegisterLayer_05_ExtiConfig3 AFIO External Interrupt Configuration Register 3
 * @ingroup AFIO_01_RegisterLayer
 * @details
 * @section AFIO_EXTICR3_Theory Theory and Practical Role
 * This page documents `AFIO_EXTICR3`, which selects the GPIO port source for
 * EXTI lines 8 through 11.
 *
 * @section AFIO_EXTICR3_Macros Register-Specific Macros
 * The macro definitions below expose raw bit positions, masks, and convenience
 * aliases used by LL layers when they need direct symbolic access to
 * `AFIO_EXTICR3`.
 *
 * @section AFIO_EXTICR3_Union Register Union View
 * The `union AFIO_EXTICR3` view inside @ref AFIO_TypeDef mirrors the same
 * register in software so a developer can compare the full register image
 * (`.REG`) against the named bitfield view (`.BIT`).
 * @{
 */

// ------ EXTI8[3:0] ------ //
/** @brief AFIO_EXTICR3_EXTI8 Position @def AFIO_EXTICR3_EXTI8_Pos */
#define AFIO_EXTICR3_EXTI8_Pos				(0U)
/** @brief AFIO_EXTICR3_EXTI8 Mask @def AFIO_EXTICR3_EXTI8_Msk */
#define AFIO_EXTICR3_EXTI8_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR3_EXTI8_Pos))
/** @brief EXTI Line 8 Port Source @def AFIO_EXTICR3_EXTI8 */
#define AFIO_EXTICR3_EXTI8					AFIO_EXTICR3_EXTI8_Msk
/** @brief EXTI8 bit 0 @def AFIO_EXTICR3_EXTI8_0 */
#define AFIO_EXTICR3_EXTI8_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR3_EXTI8_Pos))
/** @brief EXTI8 bit 1 @def AFIO_EXTICR3_EXTI8_1 */
#define AFIO_EXTICR3_EXTI8_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR3_EXTI8_Pos))
/** @brief EXTI8 bit 2 @def AFIO_EXTICR3_EXTI8_2 */
#define AFIO_EXTICR3_EXTI8_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR3_EXTI8_Pos))
/** @brief EXTI8 bit 3 @def AFIO_EXTICR3_EXTI8_3 */
#define AFIO_EXTICR3_EXTI8_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR3_EXTI8_Pos))

// ------ EXTI9[3:0] ------ //
/** @brief AFIO_EXTICR3_EXTI9 Position @def AFIO_EXTICR3_EXTI9_Pos */
#define AFIO_EXTICR3_EXTI9_Pos				(4U)
/** @brief AFIO_EXTICR3_EXTI9 Mask @def AFIO_EXTICR3_EXTI9_Msk */
#define AFIO_EXTICR3_EXTI9_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR3_EXTI9_Pos))
/** @brief EXTI Line 9 Port Source @def AFIO_EXTICR3_EXTI9 */
#define AFIO_EXTICR3_EXTI9					AFIO_EXTICR3_EXTI9_Msk
/** @brief EXTI9 bit 0 @def AFIO_EXTICR3_EXTI9_0 */
#define AFIO_EXTICR3_EXTI9_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR3_EXTI9_Pos))
/** @brief EXTI9 bit 1 @def AFIO_EXTICR3_EXTI9_1 */
#define AFIO_EXTICR3_EXTI9_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR3_EXTI9_Pos))
/** @brief EXTI9 bit 2 @def AFIO_EXTICR3_EXTI9_2 */
#define AFIO_EXTICR3_EXTI9_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR3_EXTI9_Pos))
/** @brief EXTI9 bit 3 @def AFIO_EXTICR3_EXTI9_3 */
#define AFIO_EXTICR3_EXTI9_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR3_EXTI9_Pos))

// ------ EXTI10[3:0] ------ //
/** @brief AFIO_EXTICR3_EXTI10 Position @def AFIO_EXTICR3_EXTI10_Pos */
#define AFIO_EXTICR3_EXTI10_Pos				(8U)
/** @brief AFIO_EXTICR3_EXTI10 Mask @def AFIO_EXTICR3_EXTI10_Msk */
#define AFIO_EXTICR3_EXTI10_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR3_EXTI10_Pos))
/** @brief EXTI Line 10 Port Source @def AFIO_EXTICR3_EXTI10 */
#define AFIO_EXTICR3_EXTI10					AFIO_EXTICR3_EXTI10_Msk
/** @brief EXTI10 bit 0 @def AFIO_EXTICR3_EXTI10_0 */
#define AFIO_EXTICR3_EXTI10_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR3_EXTI10_Pos))
/** @brief EXTI10 bit 1 @def AFIO_EXTICR3_EXTI10_1 */
#define AFIO_EXTICR3_EXTI10_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR3_EXTI10_Pos))
/** @brief EXTI10 bit 2 @def AFIO_EXTICR3_EXTI10_2 */
#define AFIO_EXTICR3_EXTI10_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR3_EXTI10_Pos))
/** @brief EXTI10 bit 3 @def AFIO_EXTICR3_EXTI10_3 */
#define AFIO_EXTICR3_EXTI10_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR3_EXTI10_Pos))

// ------ EXTI11[3:0] ------ //
/** @brief AFIO_EXTICR3_EXTI11 Position @def AFIO_EXTICR3_EXTI11_Pos */
#define AFIO_EXTICR3_EXTI11_Pos				(12U)
/** @brief AFIO_EXTICR3_EXTI11 Mask @def AFIO_EXTICR3_EXTI11_Msk */
#define AFIO_EXTICR3_EXTI11_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR3_EXTI11_Pos))
/** @brief EXTI Line 11 Port Source @def AFIO_EXTICR3_EXTI11 */
#define AFIO_EXTICR3_EXTI11					AFIO_EXTICR3_EXTI11_Msk
/** @brief EXTI11 bit 0 @def AFIO_EXTICR3_EXTI11_0 */
#define AFIO_EXTICR3_EXTI11_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR3_EXTI11_Pos))
/** @brief EXTI11 bit 1 @def AFIO_EXTICR3_EXTI11_1 */
#define AFIO_EXTICR3_EXTI11_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR3_EXTI11_Pos))
/** @brief EXTI11 bit 2 @def AFIO_EXTICR3_EXTI11_2 */
#define AFIO_EXTICR3_EXTI11_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR3_EXTI11_Pos))
/** @brief EXTI11 bit 3 @def AFIO_EXTICR3_EXTI11_3 */
#define AFIO_EXTICR3_EXTI11_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR3_EXTI11_Pos))

/** @} */ // AFIO_01_RegisterLayer_05_ExtiConfig3

// ------------------------------------------------------------------------------------------
// AFIO_EXTICR4 (External Interrupt Configuration Register 4)
// ------------------------------------------------------------------------------------------

/**
 * @brief AFIO External Interrupt Configuration Register 4 Definitions
 * @defgroup AFIO_01_RegisterLayer_06_ExtiConfig4 AFIO External Interrupt Configuration Register 4
 * @ingroup AFIO_01_RegisterLayer
 * @details
 * @section AFIO_EXTICR4_Theory Theory and Practical Role
 * This page documents `AFIO_EXTICR4`, which selects the GPIO port source for
 * EXTI lines 12 through 15.
 *
 * @section AFIO_EXTICR4_Macros Register-Specific Macros
 * The macro definitions below expose raw bit positions, masks, and convenience
 * aliases used by LL layers when they need direct symbolic access to
 * `AFIO_EXTICR4`.
 *
 * @section AFIO_EXTICR4_Union Register Union View
 * The `union AFIO_EXTICR4` view inside @ref AFIO_TypeDef mirrors the same
 * register in software so a developer can compare the full register image
 * (`.REG`) against the named bitfield view (`.BIT`).
 * @{
 */

// ------ EXTI12[3:0] ------ //
/** @brief AFIO_EXTICR4_EXTI12 Position @def AFIO_EXTICR4_EXTI12_Pos */
#define AFIO_EXTICR4_EXTI12_Pos				(0U)
/** @brief AFIO_EXTICR4_EXTI12 Mask @def AFIO_EXTICR4_EXTI12_Msk */
#define AFIO_EXTICR4_EXTI12_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR4_EXTI12_Pos))
/** @brief EXTI Line 12 Port Source @def AFIO_EXTICR4_EXTI12 */
#define AFIO_EXTICR4_EXTI12					AFIO_EXTICR4_EXTI12_Msk
/** @brief EXTI12 bit 0 @def AFIO_EXTICR4_EXTI12_0 */
#define AFIO_EXTICR4_EXTI12_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR4_EXTI12_Pos))
/** @brief EXTI12 bit 1 @def AFIO_EXTICR4_EXTI12_1 */
#define AFIO_EXTICR4_EXTI12_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR4_EXTI12_Pos))
/** @brief EXTI12 bit 2 @def AFIO_EXTICR4_EXTI12_2 */
#define AFIO_EXTICR4_EXTI12_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR4_EXTI12_Pos))
/** @brief EXTI12 bit 3 @def AFIO_EXTICR4_EXTI12_3 */
#define AFIO_EXTICR4_EXTI12_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR4_EXTI12_Pos))

// ------ EXTI13[3:0] ------ //
/** @brief AFIO_EXTICR4_EXTI13 Position @def AFIO_EXTICR4_EXTI13_Pos */
#define AFIO_EXTICR4_EXTI13_Pos				(4U)
/** @brief AFIO_EXTICR4_EXTI13 Mask @def AFIO_EXTICR4_EXTI13_Msk */
#define AFIO_EXTICR4_EXTI13_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR4_EXTI13_Pos))
/** @brief EXTI Line 13 Port Source @def AFIO_EXTICR4_EXTI13 */
#define AFIO_EXTICR4_EXTI13					AFIO_EXTICR4_EXTI13_Msk
/** @brief EXTI13 bit 0 @def AFIO_EXTICR4_EXTI13_0 */
#define AFIO_EXTICR4_EXTI13_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR4_EXTI13_Pos))
/** @brief EXTI13 bit 1 @def AFIO_EXTICR4_EXTI13_1 */
#define AFIO_EXTICR4_EXTI13_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR4_EXTI13_Pos))
/** @brief EXTI13 bit 2 @def AFIO_EXTICR4_EXTI13_2 */
#define AFIO_EXTICR4_EXTI13_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR4_EXTI13_Pos))
/** @brief EXTI13 bit 3 @def AFIO_EXTICR4_EXTI13_3 */
#define AFIO_EXTICR4_EXTI13_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR4_EXTI13_Pos))

// ------ EXTI14[3:0] ------ //
/** @brief AFIO_EXTICR4_EXTI14 Position @def AFIO_EXTICR4_EXTI14_Pos */
#define AFIO_EXTICR4_EXTI14_Pos				(8U)
/** @brief AFIO_EXTICR4_EXTI14 Mask @def AFIO_EXTICR4_EXTI14_Msk */
#define AFIO_EXTICR4_EXTI14_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR4_EXTI14_Pos))
/** @brief EXTI Line 14 Port Source @def AFIO_EXTICR4_EXTI14 */
#define AFIO_EXTICR4_EXTI14					AFIO_EXTICR4_EXTI14_Msk
/** @brief EXTI14 bit 0 @def AFIO_EXTICR4_EXTI14_0 */
#define AFIO_EXTICR4_EXTI14_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR4_EXTI14_Pos))
/** @brief EXTI14 bit 1 @def AFIO_EXTICR4_EXTI14_1 */
#define AFIO_EXTICR4_EXTI14_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR4_EXTI14_Pos))
/** @brief EXTI14 bit 2 @def AFIO_EXTICR4_EXTI14_2 */
#define AFIO_EXTICR4_EXTI14_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR4_EXTI14_Pos))
/** @brief EXTI14 bit 3 @def AFIO_EXTICR4_EXTI14_3 */
#define AFIO_EXTICR4_EXTI14_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR4_EXTI14_Pos))

// ------ EXTI15[3:0] ------ //
/** @brief AFIO_EXTICR4_EXTI15 Position @def AFIO_EXTICR4_EXTI15_Pos */
#define AFIO_EXTICR4_EXTI15_Pos				(12U)
/** @brief AFIO_EXTICR4_EXTI15 Mask @def AFIO_EXTICR4_EXTI15_Msk */
#define AFIO_EXTICR4_EXTI15_Msk				(REG_FIELD_VALUE(0xFUL, AFIO_EXTICR4_EXTI15_Pos))
/** @brief EXTI Line 15 Port Source @def AFIO_EXTICR4_EXTI15 */
#define AFIO_EXTICR4_EXTI15					AFIO_EXTICR4_EXTI15_Msk
/** @brief EXTI15 bit 0 @def AFIO_EXTICR4_EXTI15_0 */
#define AFIO_EXTICR4_EXTI15_0				(REG_FIELD_VALUE(0x1UL, AFIO_EXTICR4_EXTI15_Pos))
/** @brief EXTI15 bit 1 @def AFIO_EXTICR4_EXTI15_1 */
#define AFIO_EXTICR4_EXTI15_1				(REG_FIELD_VALUE(0x2UL, AFIO_EXTICR4_EXTI15_Pos))
/** @brief EXTI15 bit 2 @def AFIO_EXTICR4_EXTI15_2 */
#define AFIO_EXTICR4_EXTI15_2				(REG_FIELD_VALUE(0x4UL, AFIO_EXTICR4_EXTI15_Pos))
/** @brief EXTI15 bit 3 @def AFIO_EXTICR4_EXTI15_3 */
#define AFIO_EXTICR4_EXTI15_3				(REG_FIELD_VALUE(0x8UL, AFIO_EXTICR4_EXTI15_Pos))

/** @} */ // AFIO_01_RegisterLayer_06_ExtiConfig4

// ==================================================================================================== //
//                                            AFIO Structure                                            //
// ==================================================================================================== //

/**
 * @defgroup AFIO_01_RegisterLayer_07_RegisterMap AFIO Register Block Map
 * @ingroup AFIO_01_RegisterLayer
 * @brief Memory-mapped AFIO register block and practical register layout
 * @details
 * @section AFIO_RegisterMap_Theory Theory and Practical Role
 * This page ties the AFIO register definitions to the concrete memory map used
 * by the software stack. @ref AFIO_TypeDef is the raw peripheral view consumed
 * by LL layers when they read, write, or stage AFIO register state.
 *
 * @section AFIO_RegisterMap_Structure AFIO Register Block Structure
 * The structure below is the software-visible AFIO register layout in offset
 * order. Each register exposes a full-register view (`.REG`) and a named
 * bitfield view (`.BIT`).
 * @{
 */

/**
 * @brief AFIO Register Block Structure
 * @details
 * Complete memory-mapped AFIO peripheral register map for the currently modeled
 * STM32F1 AFIO registers.
 *
 * @typedef AFIO_TypeDef
 */
typedef volatile struct _AFIO_TypeDef
{
	/**
	 * @ingroup AFIO_01_RegisterLayer_07_RegisterMap
	 * @section AFIO_TypeDef_EVCR Event Control Register (EVCR)
	 * @brief [R/W] Event output pin and port selection
	 * @details
	 * `PIN` selects the event output pin, `PORT` selects the event output port,
	 * and `EVOE` enables event output. Bits 8 to 31 are reserved.
	 */
	union AFIO_EVCR
	{
		_IO REG;
		struct
		{
			_IO PIN : 4;
			_IO PORT : 3;
			_IO EVOE : 1;
			_IO RESERVED_EVCR : 24;
		} BIT;
	} EVCR;

	/**
	 * @ingroup AFIO_01_RegisterLayer_07_RegisterMap
	 * @section AFIO_TypeDef_MAPR AF Remap and Debug I/O Configuration Register (MAPR)
	 * @brief [R/W] Peripheral remap and SWJ configuration register
	 * @details
	 * This register controls alternate-function remaps for supported
	 * peripherals and configures the serial wire/JTAG debug port mapping.
	 */
	union AFIO_MAPR
	{
		_IO REG;
		struct
		{
			_IO SPI1_REMAP : 1;
			_IO I2C1_REMAP : 1;
			_IO USART1_REMAP : 1;
			_IO USART2_REMAP : 1;
			_IO USART3_REMAP : 2;
			_IO TIM1_REMAP : 2;
			_IO TIM2_REMAP : 2;
			_IO TIM3_REMAP : 2;
			_IO TIM4_REMAP : 1;
			_IO CAN_REMAP : 2;
			_IO PD01_REMAP : 1;
			_IO TIM5CH4_IREMAP : 1;
			_IO ADC1_ETRGINJ_REMAP : 1;
			_IO ADC1_ETGREG_REMAP : 1;
			_IO ADC2_ETRGINJ_REMAP : 1;
			_IO ADC2_ETGREG_REMAP : 1;
			_IO RESERVED_MAPR_1 : 3;
			_IO SWJ_CFG : 3;
			_IO RESERVED_MAPR_2 : 5;
		} BIT;
	} MAPR;

	/**
	 * @ingroup AFIO_01_RegisterLayer_07_RegisterMap
	 * @section AFIO_TypeDef_EXTICR1 External Interrupt Configuration Register 1 (EXTICR1)
	 * @brief [R/W] GPIO port source selection for EXTI lines 0 to 3
	 * @details
	 * Each four-bit field selects the GPIO port routed to the matching EXTI
	 * line. Bits 16 to 31 are reserved.
	 */
	union AFIO_EXTICR1
	{
		_IO REG;
		struct
		{
			_IO EXTI0 : 4;
			_IO EXTI1 : 4;
			_IO EXTI2 : 4;
			_IO EXTI3 : 4;
			_IO RESERVED_EXTICR1 : 16;
		} BIT;
	} EXTICR1;

	/**
	 * @ingroup AFIO_01_RegisterLayer_07_RegisterMap
	 * @section AFIO_TypeDef_EXTICR2 External Interrupt Configuration Register 2 (EXTICR2)
	 * @brief [R/W] GPIO port source selection for EXTI lines 4 to 7
	 * @details
	 * Each four-bit field selects the GPIO port routed to the matching EXTI
	 * line. Bits 16 to 31 are reserved.
	 */
	union AFIO_EXTICR2
	{
		_IO REG;
		struct
		{
			_IO EXTI4 : 4;
			_IO EXTI5 : 4;
			_IO EXTI6 : 4;
			_IO EXTI7 : 4;
			_IO RESERVED_EXTICR2 : 16;
		} BIT;
	} EXTICR2;

	/**
	 * @ingroup AFIO_01_RegisterLayer_07_RegisterMap
	 * @section AFIO_TypeDef_EXTICR3 External Interrupt Configuration Register 3 (EXTICR3)
	 * @brief [R/W] GPIO port source selection for EXTI lines 8 to 11
	 * @details
	 * Each four-bit field selects the GPIO port routed to the matching EXTI
	 * line. Bits 16 to 31 are reserved.
	 */
	union AFIO_EXTICR3
	{
		_IO REG;
		struct
		{
			_IO EXTI8 : 4;
			_IO EXTI9 : 4;
			_IO EXTI10 : 4;
			_IO EXTI11 : 4;
			_IO RESERVED_EXTICR3 : 16;
		} BIT;
	} EXTICR3;

	/**
	 * @ingroup AFIO_01_RegisterLayer_07_RegisterMap
	 * @section AFIO_TypeDef_EXTICR4 External Interrupt Configuration Register 4 (EXTICR4)
	 * @brief [R/W] GPIO port source selection for EXTI lines 12 to 15
	 * @details
	 * Each four-bit field selects the GPIO port routed to the matching EXTI
	 * line. Bits 16 to 31 are reserved.
	 */
	union AFIO_EXTICR4
	{
		_IO REG;
		struct
		{
			_IO EXTI12 : 4;
			_IO EXTI13 : 4;
			_IO EXTI14 : 4;
			_IO EXTI15 : 4;
			_IO RESERVED_EXTICR4 : 16;
		} BIT;
	} EXTICR4;

} AFIO_TypeDef;

/** @} */ // AFIO_01_RegisterLayer_07_RegisterMap

/** @} */ // AFIO_01_RegisterLayer

// C++ Header Guards
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_AFIO_H_ */
