/**
 * @file stm32f1xx_timer.h
 * @author Shrey Shah
 * @brief STM32F1 Timer Register-Layer Definitions
 * @version v1.1
 * @date 07-06-2026
 */

// Header Guards
#ifndef STM32F1XX_TIMER_H_
#define STM32F1XX_TIMER_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx_utils.h"

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup TIM General-Purpose Timer (TIM)
 * @brief STM32F1 timer counting, capture/compare, interrupt, DMA, and trigger infrastructure
 * @details
 * RM0008 describes the TIM2-TIM5-style general-purpose timer block as the
 * hardware engine that:
 * - counts up, down, or center-aligned through `TIMx_CNT`,
 * - scales the timer clock through `TIMx_PSC`,
 * - defines the reload period through `TIMx_ARR`,
 * - generates update, capture/compare, and trigger events,
 * - exposes capture/compare channels through `TIMx_CCMR1`, `TIMx_CCMR2`,
 *   `TIMx_CCER`, and `TIMx_CCR1..CCR4`,
 * - gates interrupt and DMA requests through `TIMx_DIER`.
 *
 * @section TIM_RegisterLayoutBrief Register Layout Brief
 * <table>
 * <tr><th>Register</th><th>Offset</th><th>Primary Practical Role</th></tr>
 * <tr><td><code>TIMx_CR1</code></td><td><code>0x00</code></td><td>Counter enable, update behavior, direction, alignment, preload, and clock division</td></tr>
 * <tr><td><code>TIMx_CR2</code></td><td><code>0x04</code></td><td>DMA capture/compare selection, master-mode output, and TI1 input selection</td></tr>
 * <tr><td><code>TIMx_SMCR</code></td><td><code>0x08</code></td><td>Slave-mode, trigger, master/slave synchronization, and external clock/filter control</td></tr>
 * <tr><td><code>TIMx_DIER</code></td><td><code>0x0C</code></td><td>Interrupt and DMA request enable bits</td></tr>
 * <tr><td><code>TIMx_SR</code></td><td><code>0x10</code></td><td>Status flags for update, capture/compare, trigger, and overcapture events</td></tr>
 * <tr><td><code>TIMx_EGR</code></td><td><code>0x14</code></td><td>Software event generation</td></tr>
 * <tr><td><code>TIMx_CCMR1</code></td><td><code>0x18</code></td><td>Capture/compare mode control for channels 1 and 2</td></tr>
 * <tr><td><code>TIMx_CCMR2</code></td><td><code>0x1C</code></td><td>Capture/compare mode control for channels 3 and 4</td></tr>
 * <tr><td><code>TIMx_CCER</code></td><td><code>0x20</code></td><td>Capture/compare channel enable and polarity control</td></tr>
 * <tr><td><code>TIMx_CNT</code></td><td><code>0x24</code></td><td>Counter value</td></tr>
 * <tr><td><code>TIMx_PSC</code></td><td><code>0x28</code></td><td>Prescaler value</td></tr>
 * <tr><td><code>TIMx_ARR</code></td><td><code>0x2C</code></td><td>Auto-reload value</td></tr>
 * <tr><td><code>TIMx_CCR1</code></td><td><code>0x34</code></td><td>Capture/compare value for channel 1</td></tr>
 * <tr><td><code>TIMx_CCR2</code></td><td><code>0x38</code></td><td>Capture/compare value for channel 2</td></tr>
 * <tr><td><code>TIMx_CCR3</code></td><td><code>0x3C</code></td><td>Capture/compare value for channel 3</td></tr>
 * <tr><td><code>TIMx_CCR4</code></td><td><code>0x40</code></td><td>Capture/compare value for channel 4</td></tr>
 * <tr><td><code>TIMx_DCR</code></td><td><code>0x48</code></td><td>DMA burst base address and burst length</td></tr>
 * <tr><td><code>TIMx_DMAR</code></td><td><code>0x4C</code></td><td>DMA burst transfer access window</td></tr>
 * </table>
 *
 * This codebase documents Timer in layered ownership order:
 * - Register layer: @ref `stm32f1xx_timer.h`
 * - Driver selector vocabulary: @ref `timer_defines.h`
 * - Driver/orchestration layer: @ref `timer.h`
 */

/**
 * @defgroup TIM_01_RegisterLayer Timer Register Layer
 * @ingroup TIM
 * @brief Raw STM32F1 Timer register structure and hardware-visible register views
 * @details
 * This layer mirrors the hardware register map. It intentionally owns only raw
 * register structure layout and named bitfield views. Driver-facing selectors,
 * validation, encoding, read-modify-write batching, and interrupt policy belong
 * in higher Timer layers.
 */

/**
 * @addtogroup TIM_01_RegisterLayer
 * @{
 */

// ==================================================================================================== //
//											Timer Register Defines										//
// ==================================================================================================== //

/**
 * @defgroup TIM_01_RegisterLayer_00_RegisterDefines Timer Register Bit Positions and Masks
 * @ingroup TIM_01_RegisterLayer
 * @brief Raw Timer register bit positions and masks for TIM2-TIM5-style general-purpose timers
 * @details
 * These macros expose the hardware-visible field positions and masks used by
 * the Timer codec and LL layers. They are intentionally raw register symbols;
 * driver-facing selectors and validation belong above this register layer.
 *
 * @{
 */

// ---------------------------------------------------------------------------------------------------- //
//											TIMx_CR1														//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Counter enable (`TIMx_CR1.CEN`) bit position @def TIM_CR1_CEN_Pos */
#define TIM_CR1_CEN_Pos						((reg_bit_pos_t) 0U)
/** @brief Counter enable (`TIMx_CR1.CEN`) bit mask @def TIM_CR1_CEN_Msk */
#define TIM_CR1_CEN_Msk						REG_BIT_MASK(TIM_CR1_CEN_Pos)
/** @brief Counter enable (`TIMx_CR1.CEN`) bit mask alias @def TIM_CR1_CEN */
#define TIM_CR1_CEN							TIM_CR1_CEN_Msk

/** @brief Update event generation disable (`TIMx_CR1.UDIS`) bit position @def TIM_CR1_UDIS_Pos */
#define TIM_CR1_UDIS_Pos					((reg_bit_pos_t) 1U)
/** @brief Update event generation disable (`TIMx_CR1.UDIS`) bit mask @def TIM_CR1_UDIS_Msk */
#define TIM_CR1_UDIS_Msk					REG_BIT_MASK(TIM_CR1_UDIS_Pos)
/** @brief Update event generation disable (`TIMx_CR1.UDIS`) bit mask alias @def TIM_CR1_UDIS */
#define TIM_CR1_UDIS						TIM_CR1_UDIS_Msk

/** @brief Update request source selection (`TIMx_CR1.URS`) bit position @def TIM_CR1_URS_Pos */
#define TIM_CR1_URS_Pos						((reg_bit_pos_t) 2U)
/** @brief Update request source selection (`TIMx_CR1.URS`) bit mask @def TIM_CR1_URS_Msk */
#define TIM_CR1_URS_Msk						REG_BIT_MASK(TIM_CR1_URS_Pos)
/** @brief Update request source selection (`TIMx_CR1.URS`) bit mask alias @def TIM_CR1_URS */
#define TIM_CR1_URS							TIM_CR1_URS_Msk

/** @brief One-pulse mode enable (`TIMx_CR1.OPM`) bit position @def TIM_CR1_OPM_Pos */
#define TIM_CR1_OPM_Pos						((reg_bit_pos_t) 3U)
/** @brief One-pulse mode enable (`TIMx_CR1.OPM`) bit mask @def TIM_CR1_OPM_Msk */
#define TIM_CR1_OPM_Msk						REG_BIT_MASK(TIM_CR1_OPM_Pos)
/** @brief One-pulse mode enable (`TIMx_CR1.OPM`) bit mask alias @def TIM_CR1_OPM */
#define TIM_CR1_OPM							TIM_CR1_OPM_Msk

/** @brief Counter direction selection (`TIMx_CR1.DIR`) bit position @def TIM_CR1_DIR_Pos */
#define TIM_CR1_DIR_Pos						((reg_bit_pos_t) 4U)
/** @brief Counter direction selection (`TIMx_CR1.DIR`) bit mask @def TIM_CR1_DIR_Msk */
#define TIM_CR1_DIR_Msk						REG_BIT_MASK(TIM_CR1_DIR_Pos)
/** @brief Counter direction selection (`TIMx_CR1.DIR`) bit mask alias @def TIM_CR1_DIR */
#define TIM_CR1_DIR							TIM_CR1_DIR_Msk

/** @brief Center-aligned mode selection (`TIMx_CR1.CMS[1:0]`) field position @def TIM_CR1_CMS_Pos */
#define TIM_CR1_CMS_Pos						((reg_bit_pos_t) 5U)
/** @brief Center-aligned mode selection (`TIMx_CR1.CMS[1:0]`) field width @def TIM_CR1_CMS_Width */
#define TIM_CR1_CMS_Width					((reg_field_width_t) 2U)
/** @brief Center-aligned mode selection (`TIMx_CR1.CMS[1:0]`) field mask @def TIM_CR1_CMS_Msk */
#define TIM_CR1_CMS_Msk						REG_FIELD_MASK(TIM_CR1_CMS_Pos, TIM_CR1_CMS_Width)
/** @brief Center-aligned mode selection (`TIMx_CR1.CMS[1:0]`) field mask alias @def TIM_CR1_CMS */
#define TIM_CR1_CMS							TIM_CR1_CMS_Msk
/** @brief Center-aligned mode selection (`TIMx_CR1.CMS[0]`) raw field bit 0 mask @def TIM_CR1_CMS_0 */
#define TIM_CR1_CMS_0						REG_FIELD_VALUE(TIM_CR1_CMS_Pos, 0x01UL)
/** @brief Center-aligned mode selection (`TIMx_CR1.CMS[1]`) raw field bit 1 mask @def TIM_CR1_CMS_1 */
#define TIM_CR1_CMS_1						REG_FIELD_VALUE(TIM_CR1_CMS_Pos, 0x02UL)
/** @brief Center-aligned mode selection raw value: edge-aligned mode @def TIM_CR1_CMS_EDGE_ALIGNED */
#define TIM_CR1_CMS_EDGE_ALIGNED			((reg) 0x00UL)
/** @brief Center-aligned mode selection raw value: center-aligned mode 1 @def TIM_CR1_CMS_CENTER_ALIGNED_MODE_1 */
#define TIM_CR1_CMS_CENTER_ALIGNED_MODE_1	(TIM_CR1_CMS_0)
/** @brief Center-aligned mode selection raw value: center-aligned mode 2 @def TIM_CR1_CMS_CENTER_ALIGNED_MODE_2 */
#define TIM_CR1_CMS_CENTER_ALIGNED_MODE_2	(TIM_CR1_CMS_1)
/** @brief Center-aligned mode selection raw value: center-aligned mode 3 @def TIM_CR1_CMS_CENTER_ALIGNED_MODE_3 */
#define TIM_CR1_CMS_CENTER_ALIGNED_MODE_3	(TIM_CR1_CMS_1 | TIM_CR1_CMS_0)

/** @brief Auto-reload preload enable (`TIMx_CR1.ARPE`) bit position @def TIM_CR1_ARPE_Pos */
#define TIM_CR1_ARPE_Pos					((reg_bit_pos_t) 7U)
/** @brief Auto-reload preload enable (`TIMx_CR1.ARPE`) bit mask @def TIM_CR1_ARPE_Msk */
#define TIM_CR1_ARPE_Msk					REG_BIT_MASK(TIM_CR1_ARPE_Pos)
/** @brief Auto-reload preload enable (`TIMx_CR1.ARPE`) bit mask alias @def TIM_CR1_ARPE */
#define TIM_CR1_ARPE						TIM_CR1_ARPE_Msk

/** @brief Timer clock division selection (`TIMx_CR1.CKD[1:0]`) field position @def TIM_CR1_CKD_Pos */
#define TIM_CR1_CKD_Pos						((reg_bit_pos_t) 8U)
/** @brief Timer clock division selection (`TIMx_CR1.CKD[1:0]`) field width @def TIM_CR1_CKD_Width */
#define TIM_CR1_CKD_Width					((reg_field_width_t) 2U)
/** @brief Timer clock division selection (`TIMx_CR1.CKD[1:0]`) field mask @def TIM_CR1_CKD_Msk */
#define TIM_CR1_CKD_Msk						REG_FIELD_MASK(TIM_CR1_CKD_Pos, TIM_CR1_CKD_Width)
/** @brief Timer clock division selection (`TIMx_CR1.CKD[1:0]`) field mask alias @def TIM_CR1_CKD */
#define TIM_CR1_CKD							TIM_CR1_CKD_Msk
/** @brief Timer clock division selection (`TIMx_CR1.CKD[0]`) raw field bit 0 mask @def TIM_CR1_CKD_0 */
#define TIM_CR1_CKD_0						REG_FIELD_VALUE(TIM_CR1_CKD_Pos, 0x01UL)
/** @brief Timer clock division selection (`TIMx_CR1.CKD[1]`) raw field bit 1 mask @def TIM_CR1_CKD_1 */
#define TIM_CR1_CKD_1						REG_FIELD_VALUE(TIM_CR1_CKD_Pos, 0x02UL)
/** @brief Timer clock division raw value: tDTS equals tCK_INT @def TIM_CR1_CKD_TDTS_TCK_INT */
#define TIM_CR1_CKD_TDTS_TCK_INT		((reg) 0x00UL)
/** @brief Timer clock division raw value: tDTS equals 2 x tCK_INT @def TIM_CR1_CKD_TDTS_2_TCK_INT */
#define TIM_CR1_CKD_TDTS_2_TCK_INT		(TIM_CR1_CKD_0)
/** @brief Timer clock division raw value: tDTS equals 4 x tCK_INT @def TIM_CR1_CKD_TDTS_4_TCK_INT */
#define TIM_CR1_CKD_TDTS_4_TCK_INT		(TIM_CR1_CKD_1)
/** @brief Timer clock division raw value: reserved, do not program @def TIM_CR1_CKD_RESERVED */
#define TIM_CR1_CKD_RESERVED			(TIM_CR1_CKD_1 | TIM_CR1_CKD_0)

// ---------------------------------------------------------------------------------------------------- //
//											TIMx_CR2														//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Capture/compare DMA request source selection (`TIMx_CR2.CCDS`) bit position @def TIM_CR2_CCDS_Pos */
#define TIM_CR2_CCDS_Pos					((reg_bit_pos_t) 3U)
/** @brief Capture/compare DMA request source selection (`TIMx_CR2.CCDS`) bit mask @def TIM_CR2_CCDS_Msk */
#define TIM_CR2_CCDS_Msk					REG_BIT_MASK(TIM_CR2_CCDS_Pos)
/** @brief Capture/compare DMA request source selection (`TIMx_CR2.CCDS`) bit mask alias @def TIM_CR2_CCDS */
#define TIM_CR2_CCDS						TIM_CR2_CCDS_Msk

/** @brief Master mode trigger output selection (`TIMx_CR2.MMS[2:0]`) field position @def TIM_CR2_MMS_Pos */
#define TIM_CR2_MMS_Pos						((reg_bit_pos_t) 4U)
/** @brief Master mode trigger output selection (`TIMx_CR2.MMS[2:0]`) field width @def TIM_CR2_MMS_Width */
#define TIM_CR2_MMS_Width					((reg_field_width_t) 3U)
/** @brief Master mode trigger output selection (`TIMx_CR2.MMS[2:0]`) field mask @def TIM_CR2_MMS_Msk */
#define TIM_CR2_MMS_Msk						REG_FIELD_MASK(TIM_CR2_MMS_Pos, TIM_CR2_MMS_Width)
/** @brief Master mode trigger output selection (`TIMx_CR2.MMS[2:0]`) field mask alias @def TIM_CR2_MMS */
#define TIM_CR2_MMS							TIM_CR2_MMS_Msk
/** @brief Master mode trigger output selection (`TIMx_CR2.MMS[0]`) raw field bit 0 mask @def TIM_CR2_MMS_0 */
#define TIM_CR2_MMS_0						REG_FIELD_VALUE(TIM_CR2_MMS_Pos, 0x01UL)
/** @brief Master mode trigger output selection (`TIMx_CR2.MMS[1]`) raw field bit 1 mask @def TIM_CR2_MMS_1 */
#define TIM_CR2_MMS_1						REG_FIELD_VALUE(TIM_CR2_MMS_Pos, 0x02UL)
/** @brief Master mode trigger output selection (`TIMx_CR2.MMS[2]`) raw field bit 2 mask @def TIM_CR2_MMS_2 */
#define TIM_CR2_MMS_2						REG_FIELD_VALUE(TIM_CR2_MMS_Pos, 0x04UL)
/** @brief Master mode raw value: reset event drives TRGO from `TIMx_EGR.UG` @def TIM_CR2_MMS_RESET */
#define TIM_CR2_MMS_RESET					((reg) 0x00UL)
/** @brief Master mode raw value: counter enable signal drives TRGO @def TIM_CR2_MMS_ENABLE */
#define TIM_CR2_MMS_ENABLE					(TIM_CR2_MMS_0)
/** @brief Master mode raw value: update event drives TRGO @def TIM_CR2_MMS_UPDATE */
#define TIM_CR2_MMS_UPDATE					(TIM_CR2_MMS_1)
/** @brief Master mode raw value: compare pulse drives TRGO @def TIM_CR2_MMS_COMPARE_PULSE */
#define TIM_CR2_MMS_COMPARE_PULSE			(TIM_CR2_MMS_1 | TIM_CR2_MMS_0)
/** @brief Master mode raw value: `OC1REF` drives TRGO @def TIM_CR2_MMS_COMPARE_OC1REF */
#define TIM_CR2_MMS_COMPARE_OC1REF			(TIM_CR2_MMS_2)
/** @brief Master mode raw value: `OC2REF` drives TRGO @def TIM_CR2_MMS_COMPARE_OC2REF */
#define TIM_CR2_MMS_COMPARE_OC2REF			(TIM_CR2_MMS_2 | TIM_CR2_MMS_0)
/** @brief Master mode raw value: `OC3REF` drives TRGO @def TIM_CR2_MMS_COMPARE_OC3REF */
#define TIM_CR2_MMS_COMPARE_OC3REF			(TIM_CR2_MMS_2 | TIM_CR2_MMS_1)
/** @brief Master mode raw value: `OC4REF` drives TRGO @def TIM_CR2_MMS_COMPARE_OC4REF */
#define TIM_CR2_MMS_COMPARE_OC4REF			(TIM_CR2_MMS_2 | TIM_CR2_MMS_1 | TIM_CR2_MMS_0)

/** @brief TI1 input XOR selection (`TIMx_CR2.TI1S`) bit position @def TIM_CR2_TI1S_Pos */
#define TIM_CR2_TI1S_Pos					((reg_bit_pos_t) 7U)
/** @brief TI1 input XOR selection (`TIMx_CR2.TI1S`) bit mask @def TIM_CR2_TI1S_Msk */
#define TIM_CR2_TI1S_Msk					REG_BIT_MASK(TIM_CR2_TI1S_Pos)
/** @brief TI1 input XOR selection (`TIMx_CR2.TI1S`) bit mask alias @def TIM_CR2_TI1S */
#define TIM_CR2_TI1S						TIM_CR2_TI1S_Msk

// ---------------------------------------------------------------------------------------------------- //
//											TIMx_SMCR													//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Slave mode selection (`TIMx_SMCR.SMS[2:0]`) field position @def TIM_SMCR_SMS_Pos */
#define TIM_SMCR_SMS_Pos					((reg_bit_pos_t) 0U)
/** @brief Slave mode selection (`TIMx_SMCR.SMS[2:0]`) field width @def TIM_SMCR_SMS_Width */
#define TIM_SMCR_SMS_Width					((reg_field_width_t) 3U)
/** @brief Slave mode selection (`TIMx_SMCR.SMS[2:0]`) field mask @def TIM_SMCR_SMS_Msk */
#define TIM_SMCR_SMS_Msk					REG_FIELD_MASK(TIM_SMCR_SMS_Pos, TIM_SMCR_SMS_Width)
/** @brief Slave mode selection (`TIMx_SMCR.SMS[2:0]`) field mask alias @def TIM_SMCR_SMS */
#define TIM_SMCR_SMS						TIM_SMCR_SMS_Msk
/** @brief Slave mode selection (`TIMx_SMCR.SMS[0]`) raw field bit 0 mask @def TIM_SMCR_SMS_0 */
#define TIM_SMCR_SMS_0						REG_FIELD_VALUE(TIM_SMCR_SMS_Pos, 0x01UL)
/** @brief Slave mode selection (`TIMx_SMCR.SMS[1]`) raw field bit 1 mask @def TIM_SMCR_SMS_1 */
#define TIM_SMCR_SMS_1						REG_FIELD_VALUE(TIM_SMCR_SMS_Pos, 0x02UL)
/** @brief Slave mode selection (`TIMx_SMCR.SMS[2]`) raw field bit 2 mask @def TIM_SMCR_SMS_2 */
#define TIM_SMCR_SMS_2						REG_FIELD_VALUE(TIM_SMCR_SMS_Pos, 0x04UL)
/** @brief Slave mode raw value: disabled @def TIM_SMCR_SMS_DISABLED */
#define TIM_SMCR_SMS_DISABLED				((reg) 0x00UL)
/** @brief Slave mode raw value: encoder mode 1 @def TIM_SMCR_SMS_ENCODER_MODE_1 */
#define TIM_SMCR_SMS_ENCODER_MODE_1			(TIM_SMCR_SMS_0)
/** @brief Slave mode raw value: encoder mode 2 @def TIM_SMCR_SMS_ENCODER_MODE_2 */
#define TIM_SMCR_SMS_ENCODER_MODE_2			(TIM_SMCR_SMS_1)
/** @brief Slave mode raw value: encoder mode 3 @def TIM_SMCR_SMS_ENCODER_MODE_3 */
#define TIM_SMCR_SMS_ENCODER_MODE_3			(TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)
/** @brief Slave mode raw value: reset mode @def TIM_SMCR_SMS_RESET_MODE */
#define TIM_SMCR_SMS_RESET_MODE				(TIM_SMCR_SMS_2)
/** @brief Slave mode raw value: gated mode @def TIM_SMCR_SMS_GATED_MODE */
#define TIM_SMCR_SMS_GATED_MODE				(TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0)
/** @brief Slave mode raw value: trigger mode @def TIM_SMCR_SMS_TRIGGER_MODE */
#define TIM_SMCR_SMS_TRIGGER_MODE			(TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
/** @brief Slave mode raw value: external clock mode 1 @def TIM_SMCR_SMS_EXTERNAL_CLOCK_MODE_1 */
#define TIM_SMCR_SMS_EXTERNAL_CLOCK_MODE_1	(TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)

/** @brief Trigger input selection (`TIMx_SMCR.TS[2:0]`) field position @def TIM_SMCR_TS_Pos */
#define TIM_SMCR_TS_Pos						((reg_bit_pos_t) 4U)
/** @brief Trigger input selection (`TIMx_SMCR.TS[2:0]`) field width @def TIM_SMCR_TS_Width */
#define TIM_SMCR_TS_Width					((reg_field_width_t) 3U)
/** @brief Trigger input selection (`TIMx_SMCR.TS[2:0]`) field mask @def TIM_SMCR_TS_Msk */
#define TIM_SMCR_TS_Msk						REG_FIELD_MASK(TIM_SMCR_TS_Pos, TIM_SMCR_TS_Width)
/** @brief Trigger input selection (`TIMx_SMCR.TS[2:0]`) field mask alias @def TIM_SMCR_TS */
#define TIM_SMCR_TS							TIM_SMCR_TS_Msk
/** @brief Trigger input selection (`TIMx_SMCR.TS[0]`) raw field bit 0 mask @def TIM_SMCR_TS_0 */
#define TIM_SMCR_TS_0						REG_FIELD_VALUE(TIM_SMCR_TS_Pos, 0x01UL)
/** @brief Trigger input selection (`TIMx_SMCR.TS[1]`) raw field bit 1 mask @def TIM_SMCR_TS_1 */
#define TIM_SMCR_TS_1						REG_FIELD_VALUE(TIM_SMCR_TS_Pos, 0x02UL)
/** @brief Trigger input selection (`TIMx_SMCR.TS[2]`) raw field bit 2 mask @def TIM_SMCR_TS_2 */
#define TIM_SMCR_TS_2						REG_FIELD_VALUE(TIM_SMCR_TS_Pos, 0x04UL)
/** @brief Trigger selection raw value: internal trigger 0 @def TIM_SMCR_TS_ITR0 */
#define TIM_SMCR_TS_ITR0					((reg) 0x00UL)
/** @brief Trigger selection raw value: internal trigger 1 @def TIM_SMCR_TS_ITR1 */
#define TIM_SMCR_TS_ITR1					(TIM_SMCR_TS_0)
/** @brief Trigger selection raw value: internal trigger 2 @def TIM_SMCR_TS_ITR2 */
#define TIM_SMCR_TS_ITR2					(TIM_SMCR_TS_1)
/** @brief Trigger selection raw value: internal trigger 3 @def TIM_SMCR_TS_ITR3 */
#define TIM_SMCR_TS_ITR3					(TIM_SMCR_TS_1 | TIM_SMCR_TS_0)
/** @brief Trigger selection raw value: `TI1` edge detector @def TIM_SMCR_TS_TI1_EDGE_DETECTOR */
#define TIM_SMCR_TS_TI1_EDGE_DETECTOR		(TIM_SMCR_TS_2)
/** @brief Trigger selection raw value: filtered timer input 1 @def TIM_SMCR_TS_TI1FP1 */
#define TIM_SMCR_TS_TI1FP1					(TIM_SMCR_TS_2 | TIM_SMCR_TS_0)
/** @brief Trigger selection raw value: filtered timer input 2 @def TIM_SMCR_TS_TI2FP2 */
#define TIM_SMCR_TS_TI2FP2					(TIM_SMCR_TS_2 | TIM_SMCR_TS_1)
/** @brief Trigger selection raw value: external trigger input @def TIM_SMCR_TS_ETRF */
#define TIM_SMCR_TS_ETRF					(TIM_SMCR_TS_2 | TIM_SMCR_TS_1 | TIM_SMCR_TS_0)

/** @brief Master/slave mode enable (`TIMx_SMCR.MSM`) bit position @def TIM_SMCR_MSM_Pos */
#define TIM_SMCR_MSM_Pos					((reg_bit_pos_t) 7U)
/** @brief Master/slave mode enable (`TIMx_SMCR.MSM`) bit mask @def TIM_SMCR_MSM_Msk */
#define TIM_SMCR_MSM_Msk					REG_BIT_MASK(TIM_SMCR_MSM_Pos)
/** @brief Master/slave mode enable (`TIMx_SMCR.MSM`) bit mask alias @def TIM_SMCR_MSM */
#define TIM_SMCR_MSM						TIM_SMCR_MSM_Msk

/** @brief External trigger digital filter selection (`TIMx_SMCR.ETF[3:0]`) field position @def TIM_SMCR_ETF_Pos */
#define TIM_SMCR_ETF_Pos					((reg_bit_pos_t) 8U)
/** @brief External trigger digital filter selection (`TIMx_SMCR.ETF[3:0]`) field width @def TIM_SMCR_ETF_Width */
#define TIM_SMCR_ETF_Width					((reg_field_width_t) 4U)
/** @brief External trigger digital filter selection (`TIMx_SMCR.ETF[3:0]`) field mask @def TIM_SMCR_ETF_Msk */
#define TIM_SMCR_ETF_Msk					REG_FIELD_MASK(TIM_SMCR_ETF_Pos, TIM_SMCR_ETF_Width)
/** @brief External trigger digital filter selection (`TIMx_SMCR.ETF[3:0]`) field mask alias @def TIM_SMCR_ETF */
#define TIM_SMCR_ETF						TIM_SMCR_ETF_Msk
/** @brief External trigger digital filter selection (`TIMx_SMCR.ETF[0]`) raw field bit 0 mask @def TIM_SMCR_ETF_0 */
#define TIM_SMCR_ETF_0						REG_FIELD_VALUE(TIM_SMCR_ETF_Pos, 0x01UL)
/** @brief External trigger digital filter selection (`TIMx_SMCR.ETF[1]`) raw field bit 1 mask @def TIM_SMCR_ETF_1 */
#define TIM_SMCR_ETF_1						REG_FIELD_VALUE(TIM_SMCR_ETF_Pos, 0x02UL)
/** @brief External trigger digital filter selection (`TIMx_SMCR.ETF[2]`) raw field bit 2 mask @def TIM_SMCR_ETF_2 */
#define TIM_SMCR_ETF_2						REG_FIELD_VALUE(TIM_SMCR_ETF_Pos, 0x04UL)
/** @brief External trigger digital filter selection (`TIMx_SMCR.ETF[3]`) raw field bit 3 mask @def TIM_SMCR_ETF_3 */
#define TIM_SMCR_ETF_3						REG_FIELD_VALUE(TIM_SMCR_ETF_Pos, 0x08UL)
/** @brief External trigger filter raw value: no filter, sampled at fDTS @def TIM_SMCR_ETF_NO_FILTER */
#define TIM_SMCR_ETF_NO_FILTER				((reg) 0x00UL)
/** @brief External trigger filter raw value: fCK_INT sampling, N=2 @def TIM_SMCR_ETF_FCK_INT_N2 */
#define TIM_SMCR_ETF_FCK_INT_N2				(TIM_SMCR_ETF_0)
/** @brief External trigger filter raw value: fCK_INT sampling, N=4 @def TIM_SMCR_ETF_FCK_INT_N4 */
#define TIM_SMCR_ETF_FCK_INT_N4				(TIM_SMCR_ETF_1)
/** @brief External trigger filter raw value: fCK_INT sampling, N=8 @def TIM_SMCR_ETF_FCK_INT_N8 */
#define TIM_SMCR_ETF_FCK_INT_N8				(TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)
/** @brief External trigger filter raw value: fDTS/2 sampling, N=6 @def TIM_SMCR_ETF_FDTS_DIV2_N6 */
#define TIM_SMCR_ETF_FDTS_DIV2_N6			(TIM_SMCR_ETF_2)
/** @brief External trigger filter raw value: fDTS/2 sampling, N=8 @def TIM_SMCR_ETF_FDTS_DIV2_N8 */
#define TIM_SMCR_ETF_FDTS_DIV2_N8			(TIM_SMCR_ETF_2 | TIM_SMCR_ETF_0)
/** @brief External trigger filter raw value: fDTS/4 sampling, N=6 @def TIM_SMCR_ETF_FDTS_DIV4_N6 */
#define TIM_SMCR_ETF_FDTS_DIV4_N6			(TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1)
/** @brief External trigger filter raw value: fDTS/4 sampling, N=8 @def TIM_SMCR_ETF_FDTS_DIV4_N8 */
#define TIM_SMCR_ETF_FDTS_DIV4_N8			(TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)
/** @brief External trigger filter raw value: fDTS/8 sampling, N=6 @def TIM_SMCR_ETF_FDTS_DIV8_N6 */
#define TIM_SMCR_ETF_FDTS_DIV8_N6			(TIM_SMCR_ETF_3)
/** @brief External trigger filter raw value: fDTS/8 sampling, N=8 @def TIM_SMCR_ETF_FDTS_DIV8_N8 */
#define TIM_SMCR_ETF_FDTS_DIV8_N8			(TIM_SMCR_ETF_3 | TIM_SMCR_ETF_0)
/** @brief External trigger filter raw value: fDTS/16 sampling, N=5 @def TIM_SMCR_ETF_FDTS_DIV16_N5 */
#define TIM_SMCR_ETF_FDTS_DIV16_N5			(TIM_SMCR_ETF_3 | TIM_SMCR_ETF_1)
/** @brief External trigger filter raw value: fDTS/16 sampling, N=6 @def TIM_SMCR_ETF_FDTS_DIV16_N6 */
#define TIM_SMCR_ETF_FDTS_DIV16_N6			(TIM_SMCR_ETF_3 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)
/** @brief External trigger filter raw value: fDTS/16 sampling, N=8 @def TIM_SMCR_ETF_FDTS_DIV16_N8 */
#define TIM_SMCR_ETF_FDTS_DIV16_N8			(TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2)
/** @brief External trigger filter raw value: fDTS/32 sampling, N=5 @def TIM_SMCR_ETF_FDTS_DIV32_N5 */
#define TIM_SMCR_ETF_FDTS_DIV32_N5			(TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_0)
/** @brief External trigger filter raw value: fDTS/32 sampling, N=6 @def TIM_SMCR_ETF_FDTS_DIV32_N6 */
#define TIM_SMCR_ETF_FDTS_DIV32_N6			(TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1)
/** @brief External trigger filter raw value: fDTS/32 sampling, N=8 @def TIM_SMCR_ETF_FDTS_DIV32_N8 */
#define TIM_SMCR_ETF_FDTS_DIV32_N8			(TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)

/** @brief External trigger prescaler selection (`TIMx_SMCR.ETPS[1:0]`) field position @def TIM_SMCR_ETPS_Pos */
#define TIM_SMCR_ETPS_Pos					((reg_bit_pos_t) 12U)
/** @brief External trigger prescaler selection (`TIMx_SMCR.ETPS[1:0]`) field width @def TIM_SMCR_ETPS_Width */
#define TIM_SMCR_ETPS_Width					((reg_field_width_t) 2U)
/** @brief External trigger prescaler selection (`TIMx_SMCR.ETPS[1:0]`) field mask @def TIM_SMCR_ETPS_Msk */
#define TIM_SMCR_ETPS_Msk					REG_FIELD_MASK(TIM_SMCR_ETPS_Pos, TIM_SMCR_ETPS_Width)
/** @brief External trigger prescaler selection (`TIMx_SMCR.ETPS[1:0]`) field mask alias @def TIM_SMCR_ETPS */
#define TIM_SMCR_ETPS						TIM_SMCR_ETPS_Msk
/** @brief External trigger prescaler selection (`TIMx_SMCR.ETPS[0]`) raw field bit 0 mask @def TIM_SMCR_ETPS_0 */
#define TIM_SMCR_ETPS_0						REG_FIELD_VALUE(TIM_SMCR_ETPS_Pos, 0x01UL)
/** @brief External trigger prescaler selection (`TIMx_SMCR.ETPS[1]`) raw field bit 1 mask @def TIM_SMCR_ETPS_1 */
#define TIM_SMCR_ETPS_1						REG_FIELD_VALUE(TIM_SMCR_ETPS_Pos, 0x02UL)
/** @brief External trigger prescaler raw value: prescaler off @def TIM_SMCR_ETPS_OFF */
#define TIM_SMCR_ETPS_OFF					((reg) 0x00UL)
/** @brief External trigger prescaler raw value: ETRP divided by 2 @def TIM_SMCR_ETPS_DIV2 */
#define TIM_SMCR_ETPS_DIV2					(TIM_SMCR_ETPS_0)
/** @brief External trigger prescaler raw value: ETRP divided by 4 @def TIM_SMCR_ETPS_DIV4 */
#define TIM_SMCR_ETPS_DIV4					(TIM_SMCR_ETPS_1)
/** @brief External trigger prescaler raw value: ETRP divided by 8 @def TIM_SMCR_ETPS_DIV8 */
#define TIM_SMCR_ETPS_DIV8					(TIM_SMCR_ETPS_1 | TIM_SMCR_ETPS_0)

/** @brief External clock mode 2 enable (`TIMx_SMCR.ECE`) bit position @def TIM_SMCR_ECE_Pos */
#define TIM_SMCR_ECE_Pos					((reg_bit_pos_t) 14U)
/** @brief External clock mode 2 enable (`TIMx_SMCR.ECE`) bit mask @def TIM_SMCR_ECE_Msk */
#define TIM_SMCR_ECE_Msk					REG_BIT_MASK(TIM_SMCR_ECE_Pos)
/** @brief External clock mode 2 enable (`TIMx_SMCR.ECE`) bit mask alias @def TIM_SMCR_ECE */
#define TIM_SMCR_ECE						TIM_SMCR_ECE_Msk

/** @brief External trigger polarity selection (`TIMx_SMCR.ETP`) bit position @def TIM_SMCR_ETP_Pos */
#define TIM_SMCR_ETP_Pos					((reg_bit_pos_t) 15U)
/** @brief External trigger polarity selection (`TIMx_SMCR.ETP`) bit mask @def TIM_SMCR_ETP_Msk */
#define TIM_SMCR_ETP_Msk					REG_BIT_MASK(TIM_SMCR_ETP_Pos)
/** @brief External trigger polarity selection (`TIMx_SMCR.ETP`) bit mask alias @def TIM_SMCR_ETP */
#define TIM_SMCR_ETP						TIM_SMCR_ETP_Msk

// ---------------------------------------------------------------------------------------------------- //
//											TIMx_DIER													//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Update interrupt enable (`TIMx_DIER.UIE`) bit position @def TIM_DIER_UIE_Pos */
#define TIM_DIER_UIE_Pos					((reg_bit_pos_t) 0U)
/** @brief Update interrupt enable (`TIMx_DIER.UIE`) bit mask @def TIM_DIER_UIE_Msk */
#define TIM_DIER_UIE_Msk					REG_BIT_MASK(TIM_DIER_UIE_Pos)
/** @brief Update interrupt enable (`TIMx_DIER.UIE`) bit mask alias @def TIM_DIER_UIE */
#define TIM_DIER_UIE						TIM_DIER_UIE_Msk

/** @brief Capture/compare channel 1 interrupt enable (`TIMx_DIER.CC1IE`) bit position @def TIM_DIER_CC1IE_Pos */
#define TIM_DIER_CC1IE_Pos					((reg_bit_pos_t) 1U)
/** @brief Capture/compare channel 1 interrupt enable (`TIMx_DIER.CC1IE`) bit mask @def TIM_DIER_CC1IE_Msk */
#define TIM_DIER_CC1IE_Msk					REG_BIT_MASK(TIM_DIER_CC1IE_Pos)
/** @brief Capture/compare channel 1 interrupt enable (`TIMx_DIER.CC1IE`) bit mask alias @def TIM_DIER_CC1IE */
#define TIM_DIER_CC1IE						TIM_DIER_CC1IE_Msk

/** @brief Capture/compare channel 2 interrupt enable (`TIMx_DIER.CC2IE`) bit position @def TIM_DIER_CC2IE_Pos */
#define TIM_DIER_CC2IE_Pos					((reg_bit_pos_t) 2U)
/** @brief Capture/compare channel 2 interrupt enable (`TIMx_DIER.CC2IE`) bit mask @def TIM_DIER_CC2IE_Msk */
#define TIM_DIER_CC2IE_Msk					REG_BIT_MASK(TIM_DIER_CC2IE_Pos)
/** @brief Capture/compare channel 2 interrupt enable (`TIMx_DIER.CC2IE`) bit mask alias @def TIM_DIER_CC2IE */
#define TIM_DIER_CC2IE						TIM_DIER_CC2IE_Msk

/** @brief Capture/compare channel 3 interrupt enable (`TIMx_DIER.CC3IE`) bit position @def TIM_DIER_CC3IE_Pos */
#define TIM_DIER_CC3IE_Pos					((reg_bit_pos_t) 3U)
/** @brief Capture/compare channel 3 interrupt enable (`TIMx_DIER.CC3IE`) bit mask @def TIM_DIER_CC3IE_Msk */
#define TIM_DIER_CC3IE_Msk					REG_BIT_MASK(TIM_DIER_CC3IE_Pos)
/** @brief Capture/compare channel 3 interrupt enable (`TIMx_DIER.CC3IE`) bit mask alias @def TIM_DIER_CC3IE */
#define TIM_DIER_CC3IE						TIM_DIER_CC3IE_Msk

/** @brief Capture/compare channel 4 interrupt enable (`TIMx_DIER.CC4IE`) bit position @def TIM_DIER_CC4IE_Pos */
#define TIM_DIER_CC4IE_Pos					((reg_bit_pos_t) 4U)
/** @brief Capture/compare channel 4 interrupt enable (`TIMx_DIER.CC4IE`) bit mask @def TIM_DIER_CC4IE_Msk */
#define TIM_DIER_CC4IE_Msk					REG_BIT_MASK(TIM_DIER_CC4IE_Pos)
/** @brief Capture/compare channel 4 interrupt enable (`TIMx_DIER.CC4IE`) bit mask alias @def TIM_DIER_CC4IE */
#define TIM_DIER_CC4IE						TIM_DIER_CC4IE_Msk

/** @brief Trigger interrupt enable (`TIMx_DIER.TIE`) bit position @def TIM_DIER_TIE_Pos */
#define TIM_DIER_TIE_Pos					((reg_bit_pos_t) 6U)
/** @brief Trigger interrupt enable (`TIMx_DIER.TIE`) bit mask @def TIM_DIER_TIE_Msk */
#define TIM_DIER_TIE_Msk					REG_BIT_MASK(TIM_DIER_TIE_Pos)
/** @brief Trigger interrupt enable (`TIMx_DIER.TIE`) bit mask alias @def TIM_DIER_TIE */
#define TIM_DIER_TIE						TIM_DIER_TIE_Msk

/** @brief Update DMA request enable (`TIMx_DIER.UDE`) bit position @def TIM_DIER_UDE_Pos */
#define TIM_DIER_UDE_Pos					((reg_bit_pos_t) 8U)
/** @brief Update DMA request enable (`TIMx_DIER.UDE`) bit mask @def TIM_DIER_UDE_Msk */
#define TIM_DIER_UDE_Msk					REG_BIT_MASK(TIM_DIER_UDE_Pos)
/** @brief Update DMA request enable (`TIMx_DIER.UDE`) bit mask alias @def TIM_DIER_UDE */
#define TIM_DIER_UDE						TIM_DIER_UDE_Msk

/** @brief Capture/compare channel 1 DMA request enable (`TIMx_DIER.CC1DE`) bit position @def TIM_DIER_CC1DE_Pos */
#define TIM_DIER_CC1DE_Pos					((reg_bit_pos_t) 9U)
/** @brief Capture/compare channel 1 DMA request enable (`TIMx_DIER.CC1DE`) bit mask @def TIM_DIER_CC1DE_Msk */
#define TIM_DIER_CC1DE_Msk					REG_BIT_MASK(TIM_DIER_CC1DE_Pos)
/** @brief Capture/compare channel 1 DMA request enable (`TIMx_DIER.CC1DE`) bit mask alias @def TIM_DIER_CC1DE */
#define TIM_DIER_CC1DE						TIM_DIER_CC1DE_Msk

/** @brief Capture/compare channel 2 DMA request enable (`TIMx_DIER.CC2DE`) bit position @def TIM_DIER_CC2DE_Pos */
#define TIM_DIER_CC2DE_Pos					((reg_bit_pos_t) 10U)
/** @brief Capture/compare channel 2 DMA request enable (`TIMx_DIER.CC2DE`) bit mask @def TIM_DIER_CC2DE_Msk */
#define TIM_DIER_CC2DE_Msk					REG_BIT_MASK(TIM_DIER_CC2DE_Pos)
/** @brief Capture/compare channel 2 DMA request enable (`TIMx_DIER.CC2DE`) bit mask alias @def TIM_DIER_CC2DE */
#define TIM_DIER_CC2DE						TIM_DIER_CC2DE_Msk

/** @brief Capture/compare channel 3 DMA request enable (`TIMx_DIER.CC3DE`) bit position @def TIM_DIER_CC3DE_Pos */
#define TIM_DIER_CC3DE_Pos					((reg_bit_pos_t) 11U)
/** @brief Capture/compare channel 3 DMA request enable (`TIMx_DIER.CC3DE`) bit mask @def TIM_DIER_CC3DE_Msk */
#define TIM_DIER_CC3DE_Msk					REG_BIT_MASK(TIM_DIER_CC3DE_Pos)
/** @brief Capture/compare channel 3 DMA request enable (`TIMx_DIER.CC3DE`) bit mask alias @def TIM_DIER_CC3DE */
#define TIM_DIER_CC3DE						TIM_DIER_CC3DE_Msk

/** @brief Capture/compare channel 4 DMA request enable (`TIMx_DIER.CC4DE`) bit position @def TIM_DIER_CC4DE_Pos */
#define TIM_DIER_CC4DE_Pos					((reg_bit_pos_t) 12U)
/** @brief Capture/compare channel 4 DMA request enable (`TIMx_DIER.CC4DE`) bit mask @def TIM_DIER_CC4DE_Msk */
#define TIM_DIER_CC4DE_Msk					REG_BIT_MASK(TIM_DIER_CC4DE_Pos)
/** @brief Capture/compare channel 4 DMA request enable (`TIMx_DIER.CC4DE`) bit mask alias @def TIM_DIER_CC4DE */
#define TIM_DIER_CC4DE						TIM_DIER_CC4DE_Msk

/** @brief Trigger DMA request enable (`TIMx_DIER.TDE`) bit position @def TIM_DIER_TDE_Pos */
#define TIM_DIER_TDE_Pos					((reg_bit_pos_t) 14U)
/** @brief Trigger DMA request enable (`TIMx_DIER.TDE`) bit mask @def TIM_DIER_TDE_Msk */
#define TIM_DIER_TDE_Msk					REG_BIT_MASK(TIM_DIER_TDE_Pos)
/** @brief Trigger DMA request enable (`TIMx_DIER.TDE`) bit mask alias @def TIM_DIER_TDE */
#define TIM_DIER_TDE						TIM_DIER_TDE_Msk

// ---------------------------------------------------------------------------------------------------- //
//											TIMx_SR														//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Update interrupt flag (`TIMx_SR.UIF`) bit position @def TIM_SR_UIF_Pos */
#define TIM_SR_UIF_Pos						((reg_bit_pos_t) 0U)
/** @brief Update interrupt flag (`TIMx_SR.UIF`) bit mask @def TIM_SR_UIF_Msk */
#define TIM_SR_UIF_Msk						REG_BIT_MASK(TIM_SR_UIF_Pos)
/** @brief Update interrupt flag (`TIMx_SR.UIF`) bit mask alias @def TIM_SR_UIF */
#define TIM_SR_UIF							TIM_SR_UIF_Msk

/** @brief Capture/compare channel 1 interrupt flag (`TIMx_SR.CC1IF`) bit position @def TIM_SR_CC1IF_Pos */
#define TIM_SR_CC1IF_Pos					((reg_bit_pos_t) 1U)
/** @brief Capture/compare channel 1 interrupt flag (`TIMx_SR.CC1IF`) bit mask @def TIM_SR_CC1IF_Msk */
#define TIM_SR_CC1IF_Msk					REG_BIT_MASK(TIM_SR_CC1IF_Pos)
/** @brief Capture/compare channel 1 interrupt flag (`TIMx_SR.CC1IF`) bit mask alias @def TIM_SR_CC1IF */
#define TIM_SR_CC1IF						TIM_SR_CC1IF_Msk

/** @brief Capture/compare channel 2 interrupt flag (`TIMx_SR.CC2IF`) bit position @def TIM_SR_CC2IF_Pos */
#define TIM_SR_CC2IF_Pos					((reg_bit_pos_t) 2U)
/** @brief Capture/compare channel 2 interrupt flag (`TIMx_SR.CC2IF`) bit mask @def TIM_SR_CC2IF_Msk */
#define TIM_SR_CC2IF_Msk					REG_BIT_MASK(TIM_SR_CC2IF_Pos)
/** @brief Capture/compare channel 2 interrupt flag (`TIMx_SR.CC2IF`) bit mask alias @def TIM_SR_CC2IF */
#define TIM_SR_CC2IF						TIM_SR_CC2IF_Msk

/** @brief Capture/compare channel 3 interrupt flag (`TIMx_SR.CC3IF`) bit position @def TIM_SR_CC3IF_Pos */
#define TIM_SR_CC3IF_Pos					((reg_bit_pos_t) 3U)
/** @brief Capture/compare channel 3 interrupt flag (`TIMx_SR.CC3IF`) bit mask @def TIM_SR_CC3IF_Msk */
#define TIM_SR_CC3IF_Msk					REG_BIT_MASK(TIM_SR_CC3IF_Pos)
/** @brief Capture/compare channel 3 interrupt flag (`TIMx_SR.CC3IF`) bit mask alias @def TIM_SR_CC3IF */
#define TIM_SR_CC3IF						TIM_SR_CC3IF_Msk

/** @brief Capture/compare channel 4 interrupt flag (`TIMx_SR.CC4IF`) bit position @def TIM_SR_CC4IF_Pos */
#define TIM_SR_CC4IF_Pos					((reg_bit_pos_t) 4U)
/** @brief Capture/compare channel 4 interrupt flag (`TIMx_SR.CC4IF`) bit mask @def TIM_SR_CC4IF_Msk */
#define TIM_SR_CC4IF_Msk					REG_BIT_MASK(TIM_SR_CC4IF_Pos)
/** @brief Capture/compare channel 4 interrupt flag (`TIMx_SR.CC4IF`) bit mask alias @def TIM_SR_CC4IF */
#define TIM_SR_CC4IF						TIM_SR_CC4IF_Msk

/** @brief Trigger interrupt flag (`TIMx_SR.TIF`) bit position @def TIM_SR_TIF_Pos */
#define TIM_SR_TIF_Pos						((reg_bit_pos_t) 6U)
/** @brief Trigger interrupt flag (`TIMx_SR.TIF`) bit mask @def TIM_SR_TIF_Msk */
#define TIM_SR_TIF_Msk						REG_BIT_MASK(TIM_SR_TIF_Pos)
/** @brief Trigger interrupt flag (`TIMx_SR.TIF`) bit mask alias @def TIM_SR_TIF */
#define TIM_SR_TIF							TIM_SR_TIF_Msk

/** @brief Capture/compare channel 1 overcapture flag (`TIMx_SR.CC1OF`) bit position @def TIM_SR_CC1OF_Pos */
#define TIM_SR_CC1OF_Pos					((reg_bit_pos_t) 9U)
/** @brief Capture/compare channel 1 overcapture flag (`TIMx_SR.CC1OF`) bit mask @def TIM_SR_CC1OF_Msk */
#define TIM_SR_CC1OF_Msk					REG_BIT_MASK(TIM_SR_CC1OF_Pos)
/** @brief Capture/compare channel 1 overcapture flag (`TIMx_SR.CC1OF`) bit mask alias @def TIM_SR_CC1OF */
#define TIM_SR_CC1OF						TIM_SR_CC1OF_Msk

/** @brief Capture/compare channel 2 overcapture flag (`TIMx_SR.CC2OF`) bit position @def TIM_SR_CC2OF_Pos */
#define TIM_SR_CC2OF_Pos					((reg_bit_pos_t) 10U)
/** @brief Capture/compare channel 2 overcapture flag (`TIMx_SR.CC2OF`) bit mask @def TIM_SR_CC2OF_Msk */
#define TIM_SR_CC2OF_Msk					REG_BIT_MASK(TIM_SR_CC2OF_Pos)
/** @brief Capture/compare channel 2 overcapture flag (`TIMx_SR.CC2OF`) bit mask alias @def TIM_SR_CC2OF */
#define TIM_SR_CC2OF						TIM_SR_CC2OF_Msk

/** @brief Capture/compare channel 3 overcapture flag (`TIMx_SR.CC3OF`) bit position @def TIM_SR_CC3OF_Pos */
#define TIM_SR_CC3OF_Pos					((reg_bit_pos_t) 11U)
/** @brief Capture/compare channel 3 overcapture flag (`TIMx_SR.CC3OF`) bit mask @def TIM_SR_CC3OF_Msk */
#define TIM_SR_CC3OF_Msk					REG_BIT_MASK(TIM_SR_CC3OF_Pos)
/** @brief Capture/compare channel 3 overcapture flag (`TIMx_SR.CC3OF`) bit mask alias @def TIM_SR_CC3OF */
#define TIM_SR_CC3OF						TIM_SR_CC3OF_Msk

/** @brief Capture/compare channel 4 overcapture flag (`TIMx_SR.CC4OF`) bit position @def TIM_SR_CC4OF_Pos */
#define TIM_SR_CC4OF_Pos					((reg_bit_pos_t) 12U)
/** @brief Capture/compare channel 4 overcapture flag (`TIMx_SR.CC4OF`) bit mask @def TIM_SR_CC4OF_Msk */
#define TIM_SR_CC4OF_Msk					REG_BIT_MASK(TIM_SR_CC4OF_Pos)
/** @brief Capture/compare channel 4 overcapture flag (`TIMx_SR.CC4OF`) bit mask alias @def TIM_SR_CC4OF */
#define TIM_SR_CC4OF						TIM_SR_CC4OF_Msk

// ---------------------------------------------------------------------------------------------------- //
//											TIMx_EGR													//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Update event generation trigger (`TIMx_EGR.UG`) bit position @def TIM_EGR_UG_Pos */
#define TIM_EGR_UG_Pos						((reg_bit_pos_t) 0U)
/** @brief Update event generation trigger (`TIMx_EGR.UG`) bit mask @def TIM_EGR_UG_Msk */
#define TIM_EGR_UG_Msk						REG_BIT_MASK(TIM_EGR_UG_Pos)
/** @brief Update event generation trigger (`TIMx_EGR.UG`) bit mask alias @def TIM_EGR_UG */
#define TIM_EGR_UG							TIM_EGR_UG_Msk

/** @brief Capture/compare channel 1 event generation trigger (`TIMx_EGR.CC1G`) bit position @def TIM_EGR_CC1G_Pos */
#define TIM_EGR_CC1G_Pos					((reg_bit_pos_t) 1U)
/** @brief Capture/compare channel 1 event generation trigger (`TIMx_EGR.CC1G`) bit mask @def TIM_EGR_CC1G_Msk */
#define TIM_EGR_CC1G_Msk					REG_BIT_MASK(TIM_EGR_CC1G_Pos)
/** @brief Capture/compare channel 1 event generation trigger (`TIMx_EGR.CC1G`) bit mask alias @def TIM_EGR_CC1G */
#define TIM_EGR_CC1G						TIM_EGR_CC1G_Msk

/** @brief Capture/compare channel 2 event generation trigger (`TIMx_EGR.CC2G`) bit position @def TIM_EGR_CC2G_Pos */
#define TIM_EGR_CC2G_Pos					((reg_bit_pos_t) 2U)
/** @brief Capture/compare channel 2 event generation trigger (`TIMx_EGR.CC2G`) bit mask @def TIM_EGR_CC2G_Msk */
#define TIM_EGR_CC2G_Msk					REG_BIT_MASK(TIM_EGR_CC2G_Pos)
/** @brief Capture/compare channel 2 event generation trigger (`TIMx_EGR.CC2G`) bit mask alias @def TIM_EGR_CC2G */
#define TIM_EGR_CC2G						TIM_EGR_CC2G_Msk

/** @brief Capture/compare channel 3 event generation trigger (`TIMx_EGR.CC3G`) bit position @def TIM_EGR_CC3G_Pos */
#define TIM_EGR_CC3G_Pos					((reg_bit_pos_t) 3U)
/** @brief Capture/compare channel 3 event generation trigger (`TIMx_EGR.CC3G`) bit mask @def TIM_EGR_CC3G_Msk */
#define TIM_EGR_CC3G_Msk					REG_BIT_MASK(TIM_EGR_CC3G_Pos)
/** @brief Capture/compare channel 3 event generation trigger (`TIMx_EGR.CC3G`) bit mask alias @def TIM_EGR_CC3G */
#define TIM_EGR_CC3G						TIM_EGR_CC3G_Msk

/** @brief Capture/compare channel 4 event generation trigger (`TIMx_EGR.CC4G`) bit position @def TIM_EGR_CC4G_Pos */
#define TIM_EGR_CC4G_Pos					((reg_bit_pos_t) 4U)
/** @brief Capture/compare channel 4 event generation trigger (`TIMx_EGR.CC4G`) bit mask @def TIM_EGR_CC4G_Msk */
#define TIM_EGR_CC4G_Msk					REG_BIT_MASK(TIM_EGR_CC4G_Pos)
/** @brief Capture/compare channel 4 event generation trigger (`TIMx_EGR.CC4G`) bit mask alias @def TIM_EGR_CC4G */
#define TIM_EGR_CC4G						TIM_EGR_CC4G_Msk

/** @brief Trigger event generation trigger (`TIMx_EGR.TG`) bit position @def TIM_EGR_TG_Pos */
#define TIM_EGR_TG_Pos						((reg_bit_pos_t) 6U)
/** @brief Trigger event generation trigger (`TIMx_EGR.TG`) bit mask @def TIM_EGR_TG_Msk */
#define TIM_EGR_TG_Msk						REG_BIT_MASK(TIM_EGR_TG_Pos)
/** @brief Trigger event generation trigger (`TIMx_EGR.TG`) bit mask alias @def TIM_EGR_TG */
#define TIM_EGR_TG							TIM_EGR_TG_Msk

// ---------------------------------------------------------------------------------------------------- //
//											TIMx_CCMR1													//
// ---------------------------------------------------------------------------------------------------- //

// ------ CCMRx Shared Raw Field Values ------ //
/** @brief Capture/compare selection raw value: channel configured as output @def TIM_CCMR_CCXS_OUTPUT */
#define TIM_CCMR_CCXS_OUTPUT				((reg_field_t) 0x00U)
/** @brief Capture/compare selection raw value: channel configured as input mapped to direct timer input @def TIM_CCMR_CCXS_INPUT_DIRECT_TI */
#define TIM_CCMR_CCXS_INPUT_DIRECT_TI		((reg_field_t) 0x01U)
/** @brief Capture/compare selection raw value: channel configured as input mapped to indirect timer input @def TIM_CCMR_CCXS_INPUT_INDIRECT_TI */
#define TIM_CCMR_CCXS_INPUT_INDIRECT_TI		((reg_field_t) 0x02U)
/** @brief Capture/compare selection raw value: channel configured as input mapped to `TRC` @def TIM_CCMR_CCXS_INPUT_TRC */
#define TIM_CCMR_CCXS_INPUT_TRC				((reg_field_t) 0x03U)

/** @brief Output compare mode raw value: frozen output reference @def TIM_CCMR_OCXM_FROZEN */
#define TIM_CCMR_OCXM_FROZEN				((reg_field_t) 0x00U)
/** @brief Output compare mode raw value: force active level on compare match @def TIM_CCMR_OCXM_ACTIVE_ON_MATCH */
#define TIM_CCMR_OCXM_ACTIVE_ON_MATCH		((reg_field_t) 0x01U)
/** @brief Output compare mode raw value: force inactive level on compare match @def TIM_CCMR_OCXM_INACTIVE_ON_MATCH */
#define TIM_CCMR_OCXM_INACTIVE_ON_MATCH		((reg_field_t) 0x02U)
/** @brief Output compare mode raw value: toggle output reference on compare match @def TIM_CCMR_OCXM_TOGGLE_ON_MATCH */
#define TIM_CCMR_OCXM_TOGGLE_ON_MATCH		((reg_field_t) 0x03U)
/** @brief Output compare mode raw value: force inactive level @def TIM_CCMR_OCXM_FORCE_INACTIVE */
#define TIM_CCMR_OCXM_FORCE_INACTIVE		((reg_field_t) 0x04U)
/** @brief Output compare mode raw value: force active level @def TIM_CCMR_OCXM_FORCE_ACTIVE */
#define TIM_CCMR_OCXM_FORCE_ACTIVE			((reg_field_t) 0x05U)
/** @brief Output compare mode raw value: PWM mode 1 @def TIM_CCMR_OCXM_PWM_MODE_1 */
#define TIM_CCMR_OCXM_PWM_MODE_1			((reg_field_t) 0x06U)
/** @brief Output compare mode raw value: PWM mode 2 @def TIM_CCMR_OCXM_PWM_MODE_2 */
#define TIM_CCMR_OCXM_PWM_MODE_2			((reg_field_t) 0x07U)

/** @brief Input capture prescaler raw value: capture each valid edge @def TIM_CCMR_ICXPSC_EACH_EDGE */
#define TIM_CCMR_ICXPSC_EACH_EDGE			((reg_field_t) 0x00U)
/** @brief Input capture prescaler raw value: capture once every 2 events @def TIM_CCMR_ICXPSC_DIV2 */
#define TIM_CCMR_ICXPSC_DIV2				((reg_field_t) 0x01U)
/** @brief Input capture prescaler raw value: capture once every 4 events @def TIM_CCMR_ICXPSC_DIV4 */
#define TIM_CCMR_ICXPSC_DIV4				((reg_field_t) 0x02U)
/** @brief Input capture prescaler raw value: capture once every 8 events @def TIM_CCMR_ICXPSC_DIV8 */
#define TIM_CCMR_ICXPSC_DIV8				((reg_field_t) 0x03U)

/** @brief Input capture filter raw value: no filter, sampled at fDTS @def TIM_CCMR_ICXF_NO_FILTER */
#define TIM_CCMR_ICXF_NO_FILTER				((reg_field_t) 0x00U)
/** @brief Input capture filter raw value: fCK_INT sampling, N=2 @def TIM_CCMR_ICXF_FCK_INT_N2 */
#define TIM_CCMR_ICXF_FCK_INT_N2			((reg_field_t) 0x01U)
/** @brief Input capture filter raw value: fCK_INT sampling, N=4 @def TIM_CCMR_ICXF_FCK_INT_N4 */
#define TIM_CCMR_ICXF_FCK_INT_N4			((reg_field_t) 0x02U)
/** @brief Input capture filter raw value: fCK_INT sampling, N=8 @def TIM_CCMR_ICXF_FCK_INT_N8 */
#define TIM_CCMR_ICXF_FCK_INT_N8			((reg_field_t) 0x03U)
/** @brief Input capture filter raw value: fDTS/2 sampling, N=6 @def TIM_CCMR_ICXF_FDTS_DIV2_N6 */
#define TIM_CCMR_ICXF_FDTS_DIV2_N6			((reg_field_t) 0x04U)
/** @brief Input capture filter raw value: fDTS/2 sampling, N=8 @def TIM_CCMR_ICXF_FDTS_DIV2_N8 */
#define TIM_CCMR_ICXF_FDTS_DIV2_N8			((reg_field_t) 0x05U)
/** @brief Input capture filter raw value: fDTS/4 sampling, N=6 @def TIM_CCMR_ICXF_FDTS_DIV4_N6 */
#define TIM_CCMR_ICXF_FDTS_DIV4_N6			((reg_field_t) 0x06U)
/** @brief Input capture filter raw value: fDTS/4 sampling, N=8 @def TIM_CCMR_ICXF_FDTS_DIV4_N8 */
#define TIM_CCMR_ICXF_FDTS_DIV4_N8			((reg_field_t) 0x07U)
/** @brief Input capture filter raw value: fDTS/8 sampling, N=6 @def TIM_CCMR_ICXF_FDTS_DIV8_N6 */
#define TIM_CCMR_ICXF_FDTS_DIV8_N6			((reg_field_t) 0x08U)
/** @brief Input capture filter raw value: fDTS/8 sampling, N=8 @def TIM_CCMR_ICXF_FDTS_DIV8_N8 */
#define TIM_CCMR_ICXF_FDTS_DIV8_N8			((reg_field_t) 0x09U)
/** @brief Input capture filter raw value: fDTS/16 sampling, N=5 @def TIM_CCMR_ICXF_FDTS_DIV16_N5 */
#define TIM_CCMR_ICXF_FDTS_DIV16_N5			((reg_field_t) 0x0AU)
/** @brief Input capture filter raw value: fDTS/16 sampling, N=6 @def TIM_CCMR_ICXF_FDTS_DIV16_N6 */
#define TIM_CCMR_ICXF_FDTS_DIV16_N6			((reg_field_t) 0x0BU)
/** @brief Input capture filter raw value: fDTS/16 sampling, N=8 @def TIM_CCMR_ICXF_FDTS_DIV16_N8 */
#define TIM_CCMR_ICXF_FDTS_DIV16_N8			((reg_field_t) 0x0CU)
/** @brief Input capture filter raw value: fDTS/32 sampling, N=5 @def TIM_CCMR_ICXF_FDTS_DIV32_N5 */
#define TIM_CCMR_ICXF_FDTS_DIV32_N5			((reg_field_t) 0x0DU)
/** @brief Input capture filter raw value: fDTS/32 sampling, N=6 @def TIM_CCMR_ICXF_FDTS_DIV32_N6 */
#define TIM_CCMR_ICXF_FDTS_DIV32_N6			((reg_field_t) 0x0EU)
/** @brief Input capture filter raw value: fDTS/32 sampling, N=8 @def TIM_CCMR_ICXF_FDTS_DIV32_N8 */
#define TIM_CCMR_ICXF_FDTS_DIV32_N8			((reg_field_t) 0x0FU)

/** @brief Capture/compare channel 1 direction and input selection (`TIMx_CCMR1.CC1S[1:0]`) field position @def TIM_CCMR1_CC1S_Pos */
#define TIM_CCMR1_CC1S_Pos					((reg_bit_pos_t) 0U)
/** @brief Capture/compare channel 1 direction and input selection (`TIMx_CCMR1.CC1S[1:0]`) field width @def TIM_CCMR1_CC1S_Width */
#define TIM_CCMR1_CC1S_Width				((reg_field_width_t) 2U)
/** @brief Capture/compare channel 1 direction and input selection (`TIMx_CCMR1.CC1S[1:0]`) field mask @def TIM_CCMR1_CC1S_Msk */
#define TIM_CCMR1_CC1S_Msk					REG_FIELD_MASK(TIM_CCMR1_CC1S_Pos, TIM_CCMR1_CC1S_Width)
/** @brief Capture/compare channel 1 direction and input selection (`TIMx_CCMR1.CC1S[1:0]`) field mask alias @def TIM_CCMR1_CC1S */
#define TIM_CCMR1_CC1S						TIM_CCMR1_CC1S_Msk

/** @brief Output compare channel 1 fast enable (`TIMx_CCMR1.OC1FE`) bit position @def TIM_CCMR1_OC1FE_Pos */
#define TIM_CCMR1_OC1FE_Pos					((reg_bit_pos_t) 2U)
/** @brief Output compare channel 1 fast enable (`TIMx_CCMR1.OC1FE`) bit mask @def TIM_CCMR1_OC1FE_Msk */
#define TIM_CCMR1_OC1FE_Msk					REG_BIT_MASK(TIM_CCMR1_OC1FE_Pos)
/** @brief Output compare channel 1 fast enable (`TIMx_CCMR1.OC1FE`) bit mask alias @def TIM_CCMR1_OC1FE */
#define TIM_CCMR1_OC1FE						TIM_CCMR1_OC1FE_Msk

/** @brief Output compare channel 1 preload enable (`TIMx_CCMR1.OC1PE`) bit position @def TIM_CCMR1_OC1PE_Pos */
#define TIM_CCMR1_OC1PE_Pos					((reg_bit_pos_t) 3U)
/** @brief Output compare channel 1 preload enable (`TIMx_CCMR1.OC1PE`) bit mask @def TIM_CCMR1_OC1PE_Msk */
#define TIM_CCMR1_OC1PE_Msk					REG_BIT_MASK(TIM_CCMR1_OC1PE_Pos)
/** @brief Output compare channel 1 preload enable (`TIMx_CCMR1.OC1PE`) bit mask alias @def TIM_CCMR1_OC1PE */
#define TIM_CCMR1_OC1PE						TIM_CCMR1_OC1PE_Msk

/** @brief Output compare channel 1 mode selection (`TIMx_CCMR1.OC1M[2:0]`) field position @def TIM_CCMR1_OC1M_Pos */
#define TIM_CCMR1_OC1M_Pos					((reg_bit_pos_t) 4U)
/** @brief Output compare channel 1 mode selection (`TIMx_CCMR1.OC1M[2:0]`) field width @def TIM_CCMR1_OC1M_Width */
#define TIM_CCMR1_OC1M_Width				((reg_field_width_t) 3U)
/** @brief Output compare channel 1 mode selection (`TIMx_CCMR1.OC1M[2:0]`) field mask @def TIM_CCMR1_OC1M_Msk */
#define TIM_CCMR1_OC1M_Msk					REG_FIELD_MASK(TIM_CCMR1_OC1M_Pos, TIM_CCMR1_OC1M_Width)
/** @brief Output compare channel 1 mode selection (`TIMx_CCMR1.OC1M[2:0]`) field mask alias @def TIM_CCMR1_OC1M */
#define TIM_CCMR1_OC1M						TIM_CCMR1_OC1M_Msk

/** @brief Output compare channel 1 clear enable (`TIMx_CCMR1.OC1CE`) bit position @def TIM_CCMR1_OC1CE_Pos */
#define TIM_CCMR1_OC1CE_Pos					((reg_bit_pos_t) 7U)
/** @brief Output compare channel 1 clear enable (`TIMx_CCMR1.OC1CE`) bit mask @def TIM_CCMR1_OC1CE_Msk */
#define TIM_CCMR1_OC1CE_Msk					REG_BIT_MASK(TIM_CCMR1_OC1CE_Pos)
/** @brief Output compare channel 1 clear enable (`TIMx_CCMR1.OC1CE`) bit mask alias @def TIM_CCMR1_OC1CE */
#define TIM_CCMR1_OC1CE						TIM_CCMR1_OC1CE_Msk

/** @brief Capture/compare channel 2 direction and input selection (`TIMx_CCMR1.CC2S[1:0]`) field position @def TIM_CCMR1_CC2S_Pos */
#define TIM_CCMR1_CC2S_Pos					((reg_bit_pos_t) 8U)
/** @brief Capture/compare channel 2 direction and input selection (`TIMx_CCMR1.CC2S[1:0]`) field width @def TIM_CCMR1_CC2S_Width */
#define TIM_CCMR1_CC2S_Width				((reg_field_width_t) 2U)
/** @brief Capture/compare channel 2 direction and input selection (`TIMx_CCMR1.CC2S[1:0]`) field mask @def TIM_CCMR1_CC2S_Msk */
#define TIM_CCMR1_CC2S_Msk					REG_FIELD_MASK(TIM_CCMR1_CC2S_Pos, TIM_CCMR1_CC2S_Width)
/** @brief Capture/compare channel 2 direction and input selection (`TIMx_CCMR1.CC2S[1:0]`) field mask alias @def TIM_CCMR1_CC2S */
#define TIM_CCMR1_CC2S						TIM_CCMR1_CC2S_Msk

/** @brief Output compare channel 2 fast enable (`TIMx_CCMR1.OC2FE`) bit position @def TIM_CCMR1_OC2FE_Pos */
#define TIM_CCMR1_OC2FE_Pos					((reg_bit_pos_t) 10U)
/** @brief Output compare channel 2 fast enable (`TIMx_CCMR1.OC2FE`) bit mask @def TIM_CCMR1_OC2FE_Msk */
#define TIM_CCMR1_OC2FE_Msk					REG_BIT_MASK(TIM_CCMR1_OC2FE_Pos)
/** @brief Output compare channel 2 fast enable (`TIMx_CCMR1.OC2FE`) bit mask alias @def TIM_CCMR1_OC2FE */
#define TIM_CCMR1_OC2FE						TIM_CCMR1_OC2FE_Msk

/** @brief Output compare channel 2 preload enable (`TIMx_CCMR1.OC2PE`) bit position @def TIM_CCMR1_OC2PE_Pos */
#define TIM_CCMR1_OC2PE_Pos					((reg_bit_pos_t) 11U)
/** @brief Output compare channel 2 preload enable (`TIMx_CCMR1.OC2PE`) bit mask @def TIM_CCMR1_OC2PE_Msk */
#define TIM_CCMR1_OC2PE_Msk					REG_BIT_MASK(TIM_CCMR1_OC2PE_Pos)
/** @brief Output compare channel 2 preload enable (`TIMx_CCMR1.OC2PE`) bit mask alias @def TIM_CCMR1_OC2PE */
#define TIM_CCMR1_OC2PE						TIM_CCMR1_OC2PE_Msk

/** @brief Output compare channel 2 mode selection (`TIMx_CCMR1.OC2M[2:0]`) field position @def TIM_CCMR1_OC2M_Pos */
#define TIM_CCMR1_OC2M_Pos					((reg_bit_pos_t) 12U)
/** @brief Output compare channel 2 mode selection (`TIMx_CCMR1.OC2M[2:0]`) field width @def TIM_CCMR1_OC2M_Width */
#define TIM_CCMR1_OC2M_Width				((reg_field_width_t) 3U)
/** @brief Output compare channel 2 mode selection (`TIMx_CCMR1.OC2M[2:0]`) field mask @def TIM_CCMR1_OC2M_Msk */
#define TIM_CCMR1_OC2M_Msk					REG_FIELD_MASK(TIM_CCMR1_OC2M_Pos, TIM_CCMR1_OC2M_Width)
/** @brief Output compare channel 2 mode selection (`TIMx_CCMR1.OC2M[2:0]`) field mask alias @def TIM_CCMR1_OC2M */
#define TIM_CCMR1_OC2M						TIM_CCMR1_OC2M_Msk

/** @brief Output compare channel 2 clear enable (`TIMx_CCMR1.OC2CE`) bit position @def TIM_CCMR1_OC2CE_Pos */
#define TIM_CCMR1_OC2CE_Pos					((reg_bit_pos_t) 15U)
/** @brief Output compare channel 2 clear enable (`TIMx_CCMR1.OC2CE`) bit mask @def TIM_CCMR1_OC2CE_Msk */
#define TIM_CCMR1_OC2CE_Msk					REG_BIT_MASK(TIM_CCMR1_OC2CE_Pos)
/** @brief Output compare channel 2 clear enable (`TIMx_CCMR1.OC2CE`) bit mask alias @def TIM_CCMR1_OC2CE */
#define TIM_CCMR1_OC2CE						TIM_CCMR1_OC2CE_Msk

/** @brief Input capture channel 1 prescaler selection (`TIMx_CCMR1.IC1PSC[1:0]`) field position @def TIM_CCMR1_IC1PSC_Pos */
#define TIM_CCMR1_IC1PSC_Pos				((reg_bit_pos_t) 2U)
/** @brief Input capture channel 1 prescaler selection (`TIMx_CCMR1.IC1PSC[1:0]`) field mask @def TIM_CCMR1_IC1PSC_Msk */
#define TIM_CCMR1_IC1PSC_Msk				REG_FIELD_MASK(TIM_CCMR1_IC1PSC_Pos, ((reg_field_width_t) 2U))
/** @brief Input capture channel 1 prescaler selection (`TIMx_CCMR1.IC1PSC[1:0]`) field mask alias @def TIM_CCMR1_IC1PSC */
#define TIM_CCMR1_IC1PSC					TIM_CCMR1_IC1PSC_Msk
/** @brief Input capture channel 1 digital filter selection (`TIMx_CCMR1.IC1F[3:0]`) field position @def TIM_CCMR1_IC1F_Pos */
#define TIM_CCMR1_IC1F_Pos					((reg_bit_pos_t) 4U)
/** @brief Input capture channel 1 digital filter selection (`TIMx_CCMR1.IC1F[3:0]`) field mask @def TIM_CCMR1_IC1F_Msk */
#define TIM_CCMR1_IC1F_Msk					REG_FIELD_MASK(TIM_CCMR1_IC1F_Pos, ((reg_field_width_t) 4U))
/** @brief Input capture channel 1 digital filter selection (`TIMx_CCMR1.IC1F[3:0]`) field mask alias @def TIM_CCMR1_IC1F */
#define TIM_CCMR1_IC1F						TIM_CCMR1_IC1F_Msk
/** @brief Input capture channel 2 prescaler selection (`TIMx_CCMR1.IC2PSC[1:0]`) field position @def TIM_CCMR1_IC2PSC_Pos */
#define TIM_CCMR1_IC2PSC_Pos				((reg_bit_pos_t) 10U)
/** @brief Input capture channel 2 prescaler selection (`TIMx_CCMR1.IC2PSC[1:0]`) field mask @def TIM_CCMR1_IC2PSC_Msk */
#define TIM_CCMR1_IC2PSC_Msk				REG_FIELD_MASK(TIM_CCMR1_IC2PSC_Pos, ((reg_field_width_t) 2U))
/** @brief Input capture channel 2 prescaler selection (`TIMx_CCMR1.IC2PSC[1:0]`) field mask alias @def TIM_CCMR1_IC2PSC */
#define TIM_CCMR1_IC2PSC					TIM_CCMR1_IC2PSC_Msk
/** @brief Input capture channel 2 digital filter selection (`TIMx_CCMR1.IC2F[3:0]`) field position @def TIM_CCMR1_IC2F_Pos */
#define TIM_CCMR1_IC2F_Pos					((reg_bit_pos_t) 12U)
/** @brief Input capture channel 2 digital filter selection (`TIMx_CCMR1.IC2F[3:0]`) field mask @def TIM_CCMR1_IC2F_Msk */
#define TIM_CCMR1_IC2F_Msk					REG_FIELD_MASK(TIM_CCMR1_IC2F_Pos, ((reg_field_width_t) 4U))
/** @brief Input capture channel 2 digital filter selection (`TIMx_CCMR1.IC2F[3:0]`) field mask alias @def TIM_CCMR1_IC2F */
#define TIM_CCMR1_IC2F						TIM_CCMR1_IC2F_Msk

// ---------------------------------------------------------------------------------------------------- //
//											TIMx_CCMR2													//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Capture/compare channel 3 direction and input selection (`TIMx_CCMR2.CC3S[1:0]`) field position @def TIM_CCMR2_CC3S_Pos */
#define TIM_CCMR2_CC3S_Pos					((reg_bit_pos_t) 0U)
/** @brief Capture/compare channel 3 direction and input selection (`TIMx_CCMR2.CC3S[1:0]`) field width @def TIM_CCMR2_CC3S_Width */
#define TIM_CCMR2_CC3S_Width				((reg_field_width_t) 2U)
/** @brief Capture/compare channel 3 direction and input selection (`TIMx_CCMR2.CC3S[1:0]`) field mask @def TIM_CCMR2_CC3S_Msk */
#define TIM_CCMR2_CC3S_Msk					REG_FIELD_MASK(TIM_CCMR2_CC3S_Pos, TIM_CCMR2_CC3S_Width)
/** @brief Capture/compare channel 3 direction and input selection (`TIMx_CCMR2.CC3S[1:0]`) field mask alias @def TIM_CCMR2_CC3S */
#define TIM_CCMR2_CC3S						TIM_CCMR2_CC3S_Msk

/** @brief Output compare channel 3 fast enable (`TIMx_CCMR2.OC3FE`) bit position @def TIM_CCMR2_OC3FE_Pos */
#define TIM_CCMR2_OC3FE_Pos					((reg_bit_pos_t) 2U)
/** @brief Output compare channel 3 fast enable (`TIMx_CCMR2.OC3FE`) bit mask @def TIM_CCMR2_OC3FE_Msk */
#define TIM_CCMR2_OC3FE_Msk					REG_BIT_MASK(TIM_CCMR2_OC3FE_Pos)
/** @brief Output compare channel 3 fast enable (`TIMx_CCMR2.OC3FE`) bit mask alias @def TIM_CCMR2_OC3FE */
#define TIM_CCMR2_OC3FE						TIM_CCMR2_OC3FE_Msk

/** @brief Output compare channel 3 preload enable (`TIMx_CCMR2.OC3PE`) bit position @def TIM_CCMR2_OC3PE_Pos */
#define TIM_CCMR2_OC3PE_Pos					((reg_bit_pos_t) 3U)
/** @brief Output compare channel 3 preload enable (`TIMx_CCMR2.OC3PE`) bit mask @def TIM_CCMR2_OC3PE_Msk */
#define TIM_CCMR2_OC3PE_Msk					REG_BIT_MASK(TIM_CCMR2_OC3PE_Pos)
/** @brief Output compare channel 3 preload enable (`TIMx_CCMR2.OC3PE`) bit mask alias @def TIM_CCMR2_OC3PE */
#define TIM_CCMR2_OC3PE						TIM_CCMR2_OC3PE_Msk

/** @brief Output compare channel 3 mode selection (`TIMx_CCMR2.OC3M[2:0]`) field position @def TIM_CCMR2_OC3M_Pos */
#define TIM_CCMR2_OC3M_Pos					((reg_bit_pos_t) 4U)
/** @brief Output compare channel 3 mode selection (`TIMx_CCMR2.OC3M[2:0]`) field width @def TIM_CCMR2_OC3M_Width */
#define TIM_CCMR2_OC3M_Width				((reg_field_width_t) 3U)
/** @brief Output compare channel 3 mode selection (`TIMx_CCMR2.OC3M[2:0]`) field mask @def TIM_CCMR2_OC3M_Msk */
#define TIM_CCMR2_OC3M_Msk					REG_FIELD_MASK(TIM_CCMR2_OC3M_Pos, TIM_CCMR2_OC3M_Width)
/** @brief Output compare channel 3 mode selection (`TIMx_CCMR2.OC3M[2:0]`) field mask alias @def TIM_CCMR2_OC3M */
#define TIM_CCMR2_OC3M						TIM_CCMR2_OC3M_Msk

/** @brief Output compare channel 3 clear enable (`TIMx_CCMR2.OC3CE`) bit position @def TIM_CCMR2_OC3CE_Pos */
#define TIM_CCMR2_OC3CE_Pos					((reg_bit_pos_t) 7U)
/** @brief Output compare channel 3 clear enable (`TIMx_CCMR2.OC3CE`) bit mask @def TIM_CCMR2_OC3CE_Msk */
#define TIM_CCMR2_OC3CE_Msk					REG_BIT_MASK(TIM_CCMR2_OC3CE_Pos)
/** @brief Output compare channel 3 clear enable (`TIMx_CCMR2.OC3CE`) bit mask alias @def TIM_CCMR2_OC3CE */
#define TIM_CCMR2_OC3CE						TIM_CCMR2_OC3CE_Msk

/** @brief Capture/compare channel 4 direction and input selection (`TIMx_CCMR2.CC4S[1:0]`) field position @def TIM_CCMR2_CC4S_Pos */
#define TIM_CCMR2_CC4S_Pos					((reg_bit_pos_t) 8U)
/** @brief Capture/compare channel 4 direction and input selection (`TIMx_CCMR2.CC4S[1:0]`) field width @def TIM_CCMR2_CC4S_Width */
#define TIM_CCMR2_CC4S_Width				((reg_field_width_t) 2U)
/** @brief Capture/compare channel 4 direction and input selection (`TIMx_CCMR2.CC4S[1:0]`) field mask @def TIM_CCMR2_CC4S_Msk */
#define TIM_CCMR2_CC4S_Msk					REG_FIELD_MASK(TIM_CCMR2_CC4S_Pos, TIM_CCMR2_CC4S_Width)
/** @brief Capture/compare channel 4 direction and input selection (`TIMx_CCMR2.CC4S[1:0]`) field mask alias @def TIM_CCMR2_CC4S */
#define TIM_CCMR2_CC4S						TIM_CCMR2_CC4S_Msk

/** @brief Output compare channel 4 fast enable (`TIMx_CCMR2.OC4FE`) bit position @def TIM_CCMR2_OC4FE_Pos */
#define TIM_CCMR2_OC4FE_Pos					((reg_bit_pos_t) 10U)
/** @brief Output compare channel 4 fast enable (`TIMx_CCMR2.OC4FE`) bit mask @def TIM_CCMR2_OC4FE_Msk */
#define TIM_CCMR2_OC4FE_Msk					REG_BIT_MASK(TIM_CCMR2_OC4FE_Pos)
/** @brief Output compare channel 4 fast enable (`TIMx_CCMR2.OC4FE`) bit mask alias @def TIM_CCMR2_OC4FE */
#define TIM_CCMR2_OC4FE						TIM_CCMR2_OC4FE_Msk

/** @brief Output compare channel 4 preload enable (`TIMx_CCMR2.OC4PE`) bit position @def TIM_CCMR2_OC4PE_Pos */
#define TIM_CCMR2_OC4PE_Pos					((reg_bit_pos_t) 11U)
/** @brief Output compare channel 4 preload enable (`TIMx_CCMR2.OC4PE`) bit mask @def TIM_CCMR2_OC4PE_Msk */
#define TIM_CCMR2_OC4PE_Msk					REG_BIT_MASK(TIM_CCMR2_OC4PE_Pos)
/** @brief Output compare channel 4 preload enable (`TIMx_CCMR2.OC4PE`) bit mask alias @def TIM_CCMR2_OC4PE */
#define TIM_CCMR2_OC4PE						TIM_CCMR2_OC4PE_Msk

/** @brief Output compare channel 4 mode selection (`TIMx_CCMR2.OC4M[2:0]`) field position @def TIM_CCMR2_OC4M_Pos */
#define TIM_CCMR2_OC4M_Pos					((reg_bit_pos_t) 12U)
/** @brief Output compare channel 4 mode selection (`TIMx_CCMR2.OC4M[2:0]`) field width @def TIM_CCMR2_OC4M_Width */
#define TIM_CCMR2_OC4M_Width				((reg_field_width_t) 3U)
/** @brief Output compare channel 4 mode selection (`TIMx_CCMR2.OC4M[2:0]`) field mask @def TIM_CCMR2_OC4M_Msk */
#define TIM_CCMR2_OC4M_Msk					REG_FIELD_MASK(TIM_CCMR2_OC4M_Pos, TIM_CCMR2_OC4M_Width)
/** @brief Output compare channel 4 mode selection (`TIMx_CCMR2.OC4M[2:0]`) field mask alias @def TIM_CCMR2_OC4M */
#define TIM_CCMR2_OC4M						TIM_CCMR2_OC4M_Msk

/** @brief Output compare channel 4 clear enable (`TIMx_CCMR2.OC4CE`) bit position @def TIM_CCMR2_OC4CE_Pos */
#define TIM_CCMR2_OC4CE_Pos					((reg_bit_pos_t) 15U)
/** @brief Output compare channel 4 clear enable (`TIMx_CCMR2.OC4CE`) bit mask @def TIM_CCMR2_OC4CE_Msk */
#define TIM_CCMR2_OC4CE_Msk					REG_BIT_MASK(TIM_CCMR2_OC4CE_Pos)
/** @brief Output compare channel 4 clear enable (`TIMx_CCMR2.OC4CE`) bit mask alias @def TIM_CCMR2_OC4CE */
#define TIM_CCMR2_OC4CE						TIM_CCMR2_OC4CE_Msk

/** @brief Input capture channel 3 prescaler selection (`TIMx_CCMR2.IC3PSC[1:0]`) field position @def TIM_CCMR2_IC3PSC_Pos */
#define TIM_CCMR2_IC3PSC_Pos				((reg_bit_pos_t) 2U)
/** @brief Input capture channel 3 prescaler selection (`TIMx_CCMR2.IC3PSC[1:0]`) field mask @def TIM_CCMR2_IC3PSC_Msk */
#define TIM_CCMR2_IC3PSC_Msk				REG_FIELD_MASK(TIM_CCMR2_IC3PSC_Pos, ((reg_field_width_t) 2U))
/** @brief Input capture channel 3 prescaler selection (`TIMx_CCMR2.IC3PSC[1:0]`) field mask alias @def TIM_CCMR2_IC3PSC */
#define TIM_CCMR2_IC3PSC					TIM_CCMR2_IC3PSC_Msk
/** @brief Input capture channel 3 digital filter selection (`TIMx_CCMR2.IC3F[3:0]`) field position @def TIM_CCMR2_IC3F_Pos */
#define TIM_CCMR2_IC3F_Pos					((reg_bit_pos_t) 4U)
/** @brief Input capture channel 3 digital filter selection (`TIMx_CCMR2.IC3F[3:0]`) field mask @def TIM_CCMR2_IC3F_Msk */
#define TIM_CCMR2_IC3F_Msk					REG_FIELD_MASK(TIM_CCMR2_IC3F_Pos, ((reg_field_width_t) 4U))
/** @brief Input capture channel 3 digital filter selection (`TIMx_CCMR2.IC3F[3:0]`) field mask alias @def TIM_CCMR2_IC3F */
#define TIM_CCMR2_IC3F						TIM_CCMR2_IC3F_Msk
/** @brief Input capture channel 4 prescaler selection (`TIMx_CCMR2.IC4PSC[1:0]`) field position @def TIM_CCMR2_IC4PSC_Pos */
#define TIM_CCMR2_IC4PSC_Pos				((reg_bit_pos_t) 10U)
/** @brief Input capture channel 4 prescaler selection (`TIMx_CCMR2.IC4PSC[1:0]`) field mask @def TIM_CCMR2_IC4PSC_Msk */
#define TIM_CCMR2_IC4PSC_Msk				REG_FIELD_MASK(TIM_CCMR2_IC4PSC_Pos, ((reg_field_width_t) 2U))
/** @brief Input capture channel 4 prescaler selection (`TIMx_CCMR2.IC4PSC[1:0]`) field mask alias @def TIM_CCMR2_IC4PSC */
#define TIM_CCMR2_IC4PSC					TIM_CCMR2_IC4PSC_Msk
/** @brief Input capture channel 4 digital filter selection (`TIMx_CCMR2.IC4F[3:0]`) field position @def TIM_CCMR2_IC4F_Pos */
#define TIM_CCMR2_IC4F_Pos					((reg_bit_pos_t) 12U)
/** @brief Input capture channel 4 digital filter selection (`TIMx_CCMR2.IC4F[3:0]`) field mask @def TIM_CCMR2_IC4F_Msk */
#define TIM_CCMR2_IC4F_Msk					REG_FIELD_MASK(TIM_CCMR2_IC4F_Pos, ((reg_field_width_t) 4U))
/** @brief Input capture channel 4 digital filter selection (`TIMx_CCMR2.IC4F[3:0]`) field mask alias @def TIM_CCMR2_IC4F */
#define TIM_CCMR2_IC4F						TIM_CCMR2_IC4F_Msk

// ---------------------------------------------------------------------------------------------------- //
//											TIMx_CCER													//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Capture/compare channel 1 enable (`TIMx_CCER.CC1E`) bit position @def TIM_CCER_CC1E_Pos */
#define TIM_CCER_CC1E_Pos					((reg_bit_pos_t) 0U)
/** @brief Capture/compare channel 1 enable (`TIMx_CCER.CC1E`) bit mask @def TIM_CCER_CC1E_Msk */
#define TIM_CCER_CC1E_Msk					REG_BIT_MASK(TIM_CCER_CC1E_Pos)
/** @brief Capture/compare channel 1 enable (`TIMx_CCER.CC1E`) bit mask alias @def TIM_CCER_CC1E */
#define TIM_CCER_CC1E						TIM_CCER_CC1E_Msk

/** @brief Capture/compare channel 1 polarity selection (`TIMx_CCER.CC1P`) bit position @def TIM_CCER_CC1P_Pos */
#define TIM_CCER_CC1P_Pos					((reg_bit_pos_t) 1U)
/** @brief Capture/compare channel 1 polarity selection (`TIMx_CCER.CC1P`) bit mask @def TIM_CCER_CC1P_Msk */
#define TIM_CCER_CC1P_Msk					REG_BIT_MASK(TIM_CCER_CC1P_Pos)
/** @brief Capture/compare channel 1 polarity selection (`TIMx_CCER.CC1P`) bit mask alias @def TIM_CCER_CC1P */
#define TIM_CCER_CC1P						TIM_CCER_CC1P_Msk

/** @brief Capture/compare channel 2 enable (`TIMx_CCER.CC2E`) bit position @def TIM_CCER_CC2E_Pos */
#define TIM_CCER_CC2E_Pos					((reg_bit_pos_t) 4U)
/** @brief Capture/compare channel 2 enable (`TIMx_CCER.CC2E`) bit mask @def TIM_CCER_CC2E_Msk */
#define TIM_CCER_CC2E_Msk					REG_BIT_MASK(TIM_CCER_CC2E_Pos)
/** @brief Capture/compare channel 2 enable (`TIMx_CCER.CC2E`) bit mask alias @def TIM_CCER_CC2E */
#define TIM_CCER_CC2E						TIM_CCER_CC2E_Msk

/** @brief Capture/compare channel 2 polarity selection (`TIMx_CCER.CC2P`) bit position @def TIM_CCER_CC2P_Pos */
#define TIM_CCER_CC2P_Pos					((reg_bit_pos_t) 5U)
/** @brief Capture/compare channel 2 polarity selection (`TIMx_CCER.CC2P`) bit mask @def TIM_CCER_CC2P_Msk */
#define TIM_CCER_CC2P_Msk					REG_BIT_MASK(TIM_CCER_CC2P_Pos)
/** @brief Capture/compare channel 2 polarity selection (`TIMx_CCER.CC2P`) bit mask alias @def TIM_CCER_CC2P */
#define TIM_CCER_CC2P						TIM_CCER_CC2P_Msk

/** @brief Capture/compare channel 3 enable (`TIMx_CCER.CC3E`) bit position @def TIM_CCER_CC3E_Pos */
#define TIM_CCER_CC3E_Pos					((reg_bit_pos_t) 8U)
/** @brief Capture/compare channel 3 enable (`TIMx_CCER.CC3E`) bit mask @def TIM_CCER_CC3E_Msk */
#define TIM_CCER_CC3E_Msk					REG_BIT_MASK(TIM_CCER_CC3E_Pos)
/** @brief Capture/compare channel 3 enable (`TIMx_CCER.CC3E`) bit mask alias @def TIM_CCER_CC3E */
#define TIM_CCER_CC3E						TIM_CCER_CC3E_Msk

/** @brief Capture/compare channel 3 polarity selection (`TIMx_CCER.CC3P`) bit position @def TIM_CCER_CC3P_Pos */
#define TIM_CCER_CC3P_Pos					((reg_bit_pos_t) 9U)
/** @brief Capture/compare channel 3 polarity selection (`TIMx_CCER.CC3P`) bit mask @def TIM_CCER_CC3P_Msk */
#define TIM_CCER_CC3P_Msk					REG_BIT_MASK(TIM_CCER_CC3P_Pos)
/** @brief Capture/compare channel 3 polarity selection (`TIMx_CCER.CC3P`) bit mask alias @def TIM_CCER_CC3P */
#define TIM_CCER_CC3P						TIM_CCER_CC3P_Msk

/** @brief Capture/compare channel 4 enable (`TIMx_CCER.CC4E`) bit position @def TIM_CCER_CC4E_Pos */
#define TIM_CCER_CC4E_Pos					((reg_bit_pos_t) 12U)
/** @brief Capture/compare channel 4 enable (`TIMx_CCER.CC4E`) bit mask @def TIM_CCER_CC4E_Msk */
#define TIM_CCER_CC4E_Msk					REG_BIT_MASK(TIM_CCER_CC4E_Pos)
/** @brief Capture/compare channel 4 enable (`TIMx_CCER.CC4E`) bit mask alias @def TIM_CCER_CC4E */
#define TIM_CCER_CC4E						TIM_CCER_CC4E_Msk

/** @brief Capture/compare channel 4 polarity selection (`TIMx_CCER.CC4P`) bit position @def TIM_CCER_CC4P_Pos */
#define TIM_CCER_CC4P_Pos					((reg_bit_pos_t) 13U)
/** @brief Capture/compare channel 4 polarity selection (`TIMx_CCER.CC4P`) bit mask @def TIM_CCER_CC4P_Msk */
#define TIM_CCER_CC4P_Msk					REG_BIT_MASK(TIM_CCER_CC4P_Pos)
/** @brief Capture/compare channel 4 polarity selection (`TIMx_CCER.CC4P`) bit mask alias @def TIM_CCER_CC4P */
#define TIM_CCER_CC4P						TIM_CCER_CC4P_Msk

// ---------------------------------------------------------------------------------------------------- //
//									TIMx Scalar Register Fields										//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Counter value (`TIMx_CNT.CNT[15:0]`) field position @def TIM_CNT_CNT_Pos */
#define TIM_CNT_CNT_Pos						((reg_bit_pos_t) 0U)
/** @brief Counter value (`TIMx_CNT.CNT[15:0]`) field mask @def TIM_CNT_CNT_Msk */
#define TIM_CNT_CNT_Msk						REG_FIELD_MASK(TIM_CNT_CNT_Pos, ((reg_field_width_t) 16U))
/** @brief Counter value (`TIMx_CNT.CNT[15:0]`) field mask alias @def TIM_CNT_CNT */
#define TIM_CNT_CNT							TIM_CNT_CNT_Msk

/** @brief Prescaler value (`TIMx_PSC.PSC[15:0]`) field position @def TIM_PSC_PSC_Pos */
#define TIM_PSC_PSC_Pos						((reg_bit_pos_t) 0U)
/** @brief Prescaler value (`TIMx_PSC.PSC[15:0]`) field mask @def TIM_PSC_PSC_Msk */
#define TIM_PSC_PSC_Msk						REG_FIELD_MASK(TIM_PSC_PSC_Pos, ((reg_field_width_t) 16U))
/** @brief Prescaler value (`TIMx_PSC.PSC[15:0]`) field mask alias @def TIM_PSC_PSC */
#define TIM_PSC_PSC							TIM_PSC_PSC_Msk

/** @brief Auto-reload value (`TIMx_ARR.ARR[15:0]`) field position @def TIM_ARR_ARR_Pos */
#define TIM_ARR_ARR_Pos						((reg_bit_pos_t) 0U)
/** @brief Auto-reload value (`TIMx_ARR.ARR[15:0]`) field mask @def TIM_ARR_ARR_Msk */
#define TIM_ARR_ARR_Msk						REG_FIELD_MASK(TIM_ARR_ARR_Pos, ((reg_field_width_t) 16U))
/** @brief Auto-reload value (`TIMx_ARR.ARR[15:0]`) field mask alias @def TIM_ARR_ARR */
#define TIM_ARR_ARR							TIM_ARR_ARR_Msk

/** @brief Capture/compare channel 1 value (`TIMx_CCR1.CCR1[15:0]`) field position @def TIM_CCR1_CCR1_Pos */
#define TIM_CCR1_CCR1_Pos					((reg_bit_pos_t) 0U)
/** @brief Capture/compare channel 1 value (`TIMx_CCR1.CCR1[15:0]`) field mask @def TIM_CCR1_CCR1_Msk */
#define TIM_CCR1_CCR1_Msk					REG_FIELD_MASK(TIM_CCR1_CCR1_Pos, ((reg_field_width_t) 16U))
/** @brief Capture/compare channel 1 value (`TIMx_CCR1.CCR1[15:0]`) field mask alias @def TIM_CCR1_CCR1 */
#define TIM_CCR1_CCR1						TIM_CCR1_CCR1_Msk

/** @brief Capture/compare channel 2 value (`TIMx_CCR2.CCR2[15:0]`) field position @def TIM_CCR2_CCR2_Pos */
#define TIM_CCR2_CCR2_Pos					((reg_bit_pos_t) 0U)
/** @brief Capture/compare channel 2 value (`TIMx_CCR2.CCR2[15:0]`) field mask @def TIM_CCR2_CCR2_Msk */
#define TIM_CCR2_CCR2_Msk					REG_FIELD_MASK(TIM_CCR2_CCR2_Pos, ((reg_field_width_t) 16U))
/** @brief Capture/compare channel 2 value (`TIMx_CCR2.CCR2[15:0]`) field mask alias @def TIM_CCR2_CCR2 */
#define TIM_CCR2_CCR2						TIM_CCR2_CCR2_Msk

/** @brief Capture/compare channel 3 value (`TIMx_CCR3.CCR3[15:0]`) field position @def TIM_CCR3_CCR3_Pos */
#define TIM_CCR3_CCR3_Pos					((reg_bit_pos_t) 0U)
/** @brief Capture/compare channel 3 value (`TIMx_CCR3.CCR3[15:0]`) field mask @def TIM_CCR3_CCR3_Msk */
#define TIM_CCR3_CCR3_Msk					REG_FIELD_MASK(TIM_CCR3_CCR3_Pos, ((reg_field_width_t) 16U))
/** @brief Capture/compare channel 3 value (`TIMx_CCR3.CCR3[15:0]`) field mask alias @def TIM_CCR3_CCR3 */
#define TIM_CCR3_CCR3						TIM_CCR3_CCR3_Msk

/** @brief Capture/compare channel 4 value (`TIMx_CCR4.CCR4[15:0]`) field position @def TIM_CCR4_CCR4_Pos */
#define TIM_CCR4_CCR4_Pos					((reg_bit_pos_t) 0U)
/** @brief Capture/compare channel 4 value (`TIMx_CCR4.CCR4[15:0]`) field mask @def TIM_CCR4_CCR4_Msk */
#define TIM_CCR4_CCR4_Msk					REG_FIELD_MASK(TIM_CCR4_CCR4_Pos, ((reg_field_width_t) 16U))
/** @brief Capture/compare channel 4 value (`TIMx_CCR4.CCR4[15:0]`) field mask alias @def TIM_CCR4_CCR4 */
#define TIM_CCR4_CCR4						TIM_CCR4_CCR4_Msk

/** @brief DMA burst base address selection (`TIMx_DCR.DBA[4:0]`) field position @def TIM_DCR_DBA_Pos */
#define TIM_DCR_DBA_Pos						((reg_bit_pos_t) 0U)
/** @brief DMA burst base address selection (`TIMx_DCR.DBA[4:0]`) field mask @def TIM_DCR_DBA_Msk */
#define TIM_DCR_DBA_Msk						REG_FIELD_MASK(TIM_DCR_DBA_Pos, ((reg_field_width_t) 5U))
/** @brief DMA burst base address selection (`TIMx_DCR.DBA[4:0]`) field mask alias @def TIM_DCR_DBA */
#define TIM_DCR_DBA							TIM_DCR_DBA_Msk

/** @brief DMA burst length selection (`TIMx_DCR.DBL[4:0]`) field position @def TIM_DCR_DBL_Pos */
#define TIM_DCR_DBL_Pos						((reg_bit_pos_t) 8U)
/** @brief DMA burst length selection (`TIMx_DCR.DBL[4:0]`) field mask @def TIM_DCR_DBL_Msk */
#define TIM_DCR_DBL_Msk						REG_FIELD_MASK(TIM_DCR_DBL_Pos, ((reg_field_width_t) 5U))
/** @brief DMA burst length selection (`TIMx_DCR.DBL[4:0]`) field mask alias @def TIM_DCR_DBL */
#define TIM_DCR_DBL							TIM_DCR_DBL_Msk

/** @brief DMA burst transfer data (`TIMx_DMAR.DMAB[15:0]`) field position @def TIM_DMAR_DMAB_Pos */
#define TIM_DMAR_DMAB_Pos					((reg_bit_pos_t) 0U)
/** @brief DMA burst transfer data (`TIMx_DMAR.DMAB[15:0]`) field mask @def TIM_DMAR_DMAB_Msk */
#define TIM_DMAR_DMAB_Msk					REG_FIELD_MASK(TIM_DMAR_DMAB_Pos, ((reg_field_width_t) 16U))
/** @brief DMA burst transfer data (`TIMx_DMAR.DMAB[15:0]`) field mask alias @def TIM_DMAR_DMAB */
#define TIM_DMAR_DMAB						TIM_DMAR_DMAB_Msk

/** @} */ // TIM_01_RegisterLayer_00_RegisterDefines

// ==================================================================================================== //
//											Timer Register Map											//
// ==================================================================================================== //

/**
 * @defgroup TIM_01_RegisterLayer_01_RegisterMap Timer Register Block Map
 * @ingroup TIM_01_RegisterLayer
 * @brief Memory-mapped Timer register block and practical register layout
 * @details
 * @section TIM_RegisterMap_Theory Theory and Practical Role
 * @ref TIM_TypeDef is the raw peripheral view consumed by Timer low-level code.
 * It exposes full-register `.REG` access for register-image operations and
 * named `.BIT` views for direct field inspection where useful.
 *
 * @section TIM_RegisterMap_Structure Timer Register Block Structure
 * The structure below is ordered by the STM32F1 general-purpose timer memory
 * map. Reserved words are kept in the structure so later registers remain at
 * their hardware offsets.
 * @{
 */

/**
 * @brief General-purpose Timer register block structure
 * @details
 * Complete memory-mapped register map for the TIM2-TIM5-style general-purpose
 * timer peripheral. On STM32F103C8T6, public base-address exposure determines
 * which concrete TIM instances are available.
 *
 * @see RM0008 Section 15.4 TIMx registers
 * @typedef TIM_TypeDef
 */
typedef volatile struct __TIM_TypeDef
{
	/**
	 * @section TIM_TypeDef_CR1 Timer Control Register 1 (CR1)
	 * @brief [R/W] Counter control, update behavior, direction, alignment, preload, and clock division
	 * @details
	 * `TIMx_CR1` owns the primary runtime counter controls. The Timer codec layer
	 * should translate driver-facing count-mode selectors into the raw `DIR` and
	 * `CMS` fields rather than letting public driver code write those fields directly.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_CR1` register image */
		_IO REG;
		/** @brief Named `TIMx_CR1` bitfield view */
		struct
		{
			_IO CEN : 1;			/**< Counter enable */
			_IO UDIS : 1;			/**< Update disable */
			_IO URS : 1;			/**< Update request source */
			_IO OPM : 1;			/**< One-pulse mode */
			_IO DIR : 1;			/**< Direction */
			_IO CMS : 2;			/**< Center-aligned mode selection */
			_IO ARPE : 1;			/**< Auto-reload preload enable */
			_IO CKD : 2;			/**< Clock division */
			_IO reserved : 22;		/**< Reserved */
		} BIT;
	} CR1;

	/**
	 * @section TIM_TypeDef_CR2 Timer Control Register 2 (CR2)
	 * @brief [R/W] Capture/compare DMA selection, master-mode output, and TI1 selection
	 * @details
	 * `TIMx_CR2` configures secondary timer behavior used for DMA request
	 * routing and timer synchronization through trigger output.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_CR2` register image */
		_IO REG;
		/** @brief Named `TIMx_CR2` bitfield view */
		struct
		{
			_IO reserved_1 : 3;		/**< Reserved */
			_IO CCDS : 1;			/**< Capture/compare DMA selection */
			_IO MMS : 3;			/**< Master mode selection */
			_IO TI1S : 1;			/**< TI1 selection */
			_IO reserved_2 : 24;	/**< Reserved */
		} BIT;
	} CR2;

	/**
	 * @section TIM_TypeDef_SMCR Timer Slave Mode Control Register (SMCR)
	 * @brief [R/W] Slave-mode, trigger, synchronization, and external clock/filter control
	 * @details
	 * `TIMx_SMCR` selects slave-mode behavior, trigger source, master/slave
	 * synchronization, external trigger filtering, and external clock mode bits.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_SMCR` register image */
		_IO REG;
		/** @brief Named `TIMx_SMCR` bitfield view */
		struct
		{
			_IO SMS : 3;			/**< Slave mode selection */
			_IO reserved_1 : 1;		/**< Reserved */
			_IO TS : 3;				/**< Trigger selection */
			_IO MSM : 1;			/**< Master/slave mode */
			_IO ETF : 4;			/**< External trigger filter */
			_IO ETPS : 2;			/**< External trigger prescaler */
			_IO ECE : 1;			/**< External clock enable */
			_IO ETP : 1;			/**< External trigger polarity */
			_IO reserved_2 : 16;	/**< Reserved */
		} BIT;
	} SMCR;

	/**
	 * @section TIM_TypeDef_DIER Timer DMA/Interrupt Enable Register (DIER)
	 * @brief [R/W] Interrupt and DMA request enables
	 * @details
	 * `TIMx_DIER` gates update, capture/compare, and trigger interrupt/DMA
	 * requests. NVIC enable/disable policy is intentionally outside this raw
	 * register layer.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_DIER` register image */
		_IO REG;
		/** @brief Named `TIMx_DIER` bitfield view */
		struct
		{
			_IO UIE : 1;			/**< Update interrupt enable */
			_IO CC1IE : 1;			/**< Capture/compare 1 interrupt enable */
			_IO CC2IE : 1;			/**< Capture/compare 2 interrupt enable */
			_IO CC3IE : 1;			/**< Capture/compare 3 interrupt enable */
			_IO CC4IE : 1;			/**< Capture/compare 4 interrupt enable */
			_IO reserved_1 : 1;		/**< Reserved */
			_IO TIE : 1;			/**< Trigger interrupt enable */
			_IO reserved_2 : 1;		/**< Reserved */
			_IO UDE : 1;			/**< Update DMA request enable */
			_IO CC1DE : 1;			/**< Capture/compare 1 DMA request enable */
			_IO CC2DE : 1;			/**< Capture/compare 2 DMA request enable */
			_IO CC3DE : 1;			/**< Capture/compare 3 DMA request enable */
			_IO CC4DE : 1;			/**< Capture/compare 4 DMA request enable */
			_IO reserved_3 : 1;		/**< Reserved */
			_IO TDE : 1;			/**< Trigger DMA request enable */
			_IO reserved_4 : 17;	/**< Reserved */
		} BIT;
	} DIER;

	/**
	 * @section TIM_TypeDef_SR Timer Status Register (SR)
	 * @brief [R/W] Event flags for update, capture/compare, trigger, and overcapture status
	 * @details
	 * `TIMx_SR` reports timer event flags. Software clears supported flags by
	 * writing the hardware-defined clear value through a full-register or field
	 * access path owned by higher layers.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_SR` register image */
		_IO REG;
		/** @brief Named `TIMx_SR` bitfield view */
		struct
		{
			_IO UIF : 1;			/**< Update interrupt flag */
			_IO CC1IF : 1;			/**< Capture/compare 1 interrupt flag */
			_IO CC2IF : 1;			/**< Capture/compare 2 interrupt flag */
			_IO CC3IF : 1;			/**< Capture/compare 3 interrupt flag */
			_IO CC4IF : 1;			/**< Capture/compare 4 interrupt flag */
			_IO reserved_1 : 1;		/**< Reserved */
			_IO TIF : 1;			/**< Trigger interrupt flag */
			_IO reserved_2 : 2;		/**< Reserved */
			_IO CC1OF : 1;			/**< Capture/compare 1 overcapture flag */
			_IO CC2OF : 1;			/**< Capture/compare 2 overcapture flag */
			_IO CC3OF : 1;			/**< Capture/compare 3 overcapture flag */
			_IO CC4OF : 1;			/**< Capture/compare 4 overcapture flag */
			_IO reserved_3 : 19;	/**< Reserved */
		} BIT;
	} SR;

	/**
	 * @section TIM_TypeDef_EGR Timer Event Generation Register (EGR)
	 * @brief [W] Software event-generation register
	 * @details
	 * `TIMx_EGR` lets software request update, capture/compare, and trigger
	 * events. Event-generation sequencing belongs in the driver layer.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_EGR` register image */
		_IO REG;
		/** @brief Named `TIMx_EGR` bitfield view */
		struct
		{
			_IO UG : 1;				/**< Update generation */
			_IO CC1G : 1;			/**< Capture/compare 1 generation */
			_IO CC2G : 1;			/**< Capture/compare 2 generation */
			_IO CC3G : 1;			/**< Capture/compare 3 generation */
			_IO CC4G : 1;			/**< Capture/compare 4 generation */
			_IO reserved_1 : 1;		/**< Reserved */
			_IO TG : 1;				/**< Trigger generation */
			_IO reserved_2 : 25;	/**< Reserved */
		} BIT;
	} EGR;

	/**
	 * @section TIM_TypeDef_CCMR1 Timer Capture/Compare Mode Register 1 (CCMR1)
	 * @brief [R/W] Capture/compare mode control for channels 1 and 2
	 * @details
	 * `TIMx_CCMR1` has two hardware interpretations: output-compare mode (`OCM`)
	 * and input-capture mode (`ICM`). The `CC1S` and `CC2S` fields select which
	 * interpretation is meaningful for each channel.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_CCMR1` register image */
		_IO REG;
		/** @brief Output-compare and input-capture bitfield views for `TIMx_CCMR1` */
		union
		{
			/** @brief Output-compare mode field view for channels 1 and 2 */
			struct
			{
				_IO CC1S : 2;		/**< Capture/compare 1 selection */
				_IO OC1FE : 1;		/**< Output compare 1 fast enable */
				_IO OC1PE : 1;		/**< Output compare 1 preload enable */
				_IO OC1M : 3;		/**< Output compare 1 mode */
				_IO OC1CE : 1;		/**< Output compare 1 clear enable */
				_IO CC2S : 2;		/**< Capture/compare 2 selection */
				_IO OC2FE : 1;		/**< Output compare 2 fast enable */
				_IO OC2PE : 1;		/**< Output compare 2 preload enable */
				_IO OC2M : 3;		/**< Output compare 2 mode */
				_IO OC2CE : 1;		/**< Output compare 2 clear enable */
				_IO reserved : 16;	/**< Reserved */
			} OCM;
			/** @brief Input-capture mode field view for channels 1 and 2 */
			struct
			{
				_IO CC1S : 2;		/**< Capture/compare 1 selection */
				_IO IC1PSC : 2;		/**< Input capture 1 prescaler */
				_IO IC1F : 4;		/**< Input capture 1 filter */
				_IO CC2S : 2;		/**< Capture/compare 2 selection */
				_IO IC2PSC : 2;		/**< Input capture 2 prescaler */
				_IO IC2F : 4;		/**< Input capture 2 filter */
				_IO reserved : 16;	/**< Reserved */
			} ICM;
		} BIT;
	} CCMR1;

	/**
	 * @section TIM_TypeDef_CCMR2 Timer Capture/Compare Mode Register 2 (CCMR2)
	 * @brief [R/W] Capture/compare mode control for channels 3 and 4
	 * @details
	 * `TIMx_CCMR2` has the same output-compare/input-capture split as
	 * `TIMx_CCMR1`, but applies to channels 3 and 4.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_CCMR2` register image */
		_IO REG;
		/** @brief Output-compare and input-capture bitfield views for `TIMx_CCMR2` */
		union
		{
			/** @brief Output-compare mode field view for channels 3 and 4 */
			struct
			{
				_IO CC3S : 2;		/**< Capture/compare 3 selection */
				_IO OC3FE : 1;		/**< Output compare 3 fast enable */
				_IO OC3PE : 1;		/**< Output compare 3 preload enable */
				_IO OC3M : 3;		/**< Output compare 3 mode */
				_IO OC3CE : 1;		/**< Output compare 3 clear enable */
				_IO CC4S : 2;		/**< Capture/compare 4 selection */
				_IO OC4FE : 1;		/**< Output compare 4 fast enable */
				_IO OC4PE : 1;		/**< Output compare 4 preload enable */
				_IO OC4M : 3;		/**< Output compare 4 mode */
				_IO OC4CE : 1;		/**< Output compare 4 clear enable */
				_IO reserved : 16;	/**< Reserved */
			} OCM;
			/** @brief Input-capture mode field view for channels 3 and 4 */
			struct
			{
				_IO CC3S : 2;		/**< Capture/compare 3 selection */
				_IO IC3PSC : 2;		/**< Input capture 3 prescaler */
				_IO IC3F : 4;		/**< Input capture 3 filter */
				_IO CC4S : 2;		/**< Capture/compare 4 selection */
				_IO IC4PSC : 2;		/**< Input capture 4 prescaler */
				_IO IC4F : 4;		/**< Input capture 4 filter */
				_IO reserved : 16;	/**< Reserved */
			} ICM;
		} BIT;
	} CCMR2;

	/**
	 * @section TIM_TypeDef_CCER Timer Capture/Compare Enable Register (CCER)
	 * @brief [R/W] Capture/compare output enable and polarity control
	 * @details
	 * `TIMx_CCER` enables each capture/compare channel and controls the active
	 * polarity for each channel signal.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_CCER` register image */
		_IO REG;
		/** @brief Named `TIMx_CCER` bitfield view */
		struct
		{
			_IO CC1E : 1;			/**< Capture/compare 1 output enable */
			_IO CC1P : 1;			/**< Capture/compare 1 output polarity */
			_IO reserved_1 : 2;		/**< Reserved */
			_IO CC2E : 1;			/**< Capture/compare 2 output enable */
			_IO CC2P : 1;			/**< Capture/compare 2 output polarity */
			_IO reserved_2 : 2;		/**< Reserved */
			_IO CC3E : 1;			/**< Capture/compare 3 output enable */
			_IO CC3P : 1;			/**< Capture/compare 3 output polarity */
			_IO reserved_3 : 2;		/**< Reserved */
			_IO CC4E : 1;			/**< Capture/compare 4 output enable */
			_IO CC4P : 1;			/**< Capture/compare 4 output polarity */
			_IO reserved_4 : 18;	/**< Reserved */
		} BIT;
	} CCER;

	/**
	 * @section TIM_TypeDef_CNT Timer Counter Register (CNT)
	 * @brief [R/W] Current counter value
	 * @details
	 * `TIMx_CNT` holds the current timer counter value. General-purpose timers in
	 * this target family use the low 16 bits.
	 */
	_IO CNT;

	/**
	 * @section TIM_TypeDef_PSC Timer Prescaler Register (PSC)
	 * @brief [R/W] Counter clock prescaler value
	 * @details
	 * `TIMx_PSC` divides the timer input clock by `PSC + 1`.
	 */
	_IO PSC;

	/**
	 * @section TIM_TypeDef_ARR Timer Auto-Reload Register (ARR)
	 * @brief [R/W] Auto-reload period value
	 * @details
	 * `TIMx_ARR` holds the period boundary used by update-event generation.
	 */
	_IO ARR;

	/** @brief Reserved word at offset `0x30` */
	_IO RESERVED_1;

	/**
	 * @section TIM_TypeDef_CCR1 Timer Capture/Compare Register 1 (CCR1)
	 * @brief [R/W] Capture/compare value for channel 1
	 * @details
	 * `CC1_IN` and `CC1_OUT` are aliases for the same hardware register image.
	 * The active meaning depends on the channel mode selected in `TIMx_CCMR1`.
	 */
	union
	{
		_IO CC1_IN;				/**< Input-capture view of channel 1 capture/compare value */
		_IO CC1_OUT;			/**< Output-compare view of channel 1 capture/compare value */
	} CCR1;

	/**
	 * @section TIM_TypeDef_CCR2 Timer Capture/Compare Register 2 (CCR2)
	 * @brief [R/W] Capture/compare value for channel 2
	 * @details
	 * `CC2_IN` and `CC2_OUT` are aliases for the same hardware register image.
	 * The active meaning depends on the channel mode selected in `TIMx_CCMR1`.
	 */
	union
	{
		_IO CC2_IN;				/**< Input-capture view of channel 2 capture/compare value */
		_IO CC2_OUT;			/**< Output-compare view of channel 2 capture/compare value */
	} CCR2;

	/**
	 * @section TIM_TypeDef_CCR3 Timer Capture/Compare Register 3 (CCR3)
	 * @brief [R/W] Capture/compare value for channel 3
	 * @details
	 * `CC3_IN` and `CC3_OUT` are aliases for the same hardware register image.
	 * The active meaning depends on the channel mode selected in `TIMx_CCMR2`.
	 */
	union
	{
		_IO CC3_IN;				/**< Input-capture view of channel 3 capture/compare value */
		_IO CC3_OUT;			/**< Output-compare view of channel 3 capture/compare value */
	} CCR3;

	/**
	 * @section TIM_TypeDef_CCR4 Timer Capture/Compare Register 4 (CCR4)
	 * @brief [R/W] Capture/compare value for channel 4
	 * @details
	 * `CC4_IN` and `CC4_OUT` are aliases for the same hardware register image.
	 * The active meaning depends on the channel mode selected in `TIMx_CCMR2`.
	 */
	union
	{
		_IO CC4_IN;				/**< Input-capture view of channel 4 capture/compare value */
		_IO CC4_OUT;			/**< Output-compare view of channel 4 capture/compare value */
	} CCR4;

	/** @brief Reserved word at offset `0x44` */
	_IO RESERVED_2;

	/**
	 * @section TIM_TypeDef_DCR Timer DMA Control Register (DCR)
	 * @brief [R/W] DMA burst base address and burst length configuration
	 * @details
	 * `TIMx_DCR` configures the starting register offset and number of transfers
	 * used by timer DMA burst operations through `TIMx_DMAR`.
	 */
	union
	{
		/** @brief Full 32-bit `TIMx_DCR` register image */
		_IO REG;
		/** @brief Named `TIMx_DCR` bitfield view */
		struct
		{
			_IO DBA : 5;			/**< DMA base address */
			_IO reserved_1 : 3;		/**< Reserved */
			_IO DBL : 5;			/**< DMA burst length */
			_IO reserved_2 : 19;	/**< Reserved */
		} BIT;
	} DCR;

	/**
	 * @section TIM_TypeDef_DMAR Timer DMA Address Register (DMAR)
	 * @brief [R/W] DMA burst transfer register access window
	 * @details
	 * `TIMx_DMAR` is the data access window used for DMA burst transfers
	 * configured by `TIMx_DCR`.
	 */
	_IO DMAR;
} TIM_TypeDef;

/** @} */ // TIM_01_RegisterLayer_01_RegisterMap

/** @} */ // TIM_01_RegisterLayer

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_TIMER_H_ */
