/**
 * @file stm32f1xx_rcc.h
 * @author Shrey Shah
 * @brief STM32F1 RCC Register-Layer Definitions
 * @version v1.1
 * @date 22-03-2026
 */
#ifndef STM32F1XX_RCC_H_
#define STM32F1XX_RCC_H_

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------
#include "stm32f1xx_utils.h"

/**
 * @defgroup RCC Reset and Clock Control (RCC)
 * @brief STM32F1 reset, clock source, prescaler, gate, and reset infrastructure
 * @details
 * RM0008 Section 7 describes RCC as the hardware block that:
 * - starts and monitors clock sources such as HSI, HSE, PLL, LSI, and LSE,
 * - selects the system clock source,
 * - derives bus clocks through AHB and APB prescalers,
 * - derives peripheral-specific clocks such as ADC and USB,
 * - gates and resets peripherals to control power and initialization order.
 *
 * @section RCC_RegisterLayoutBrief Register Layout Brief
 * <table>
 * <tr><th>Register</th><th>Offset</th><th>Primary Practical Role</th></tr>
 * <tr><td><code>RCC_CR</code></td><td><code>0x00</code></td><td>Clock-source enable, ready, bypass, CSS, and PLL state control</td></tr>
 * <tr><td><code>RCC_CFGR</code></td><td><code>0x04</code></td><td>SYSCLK selection/status, bus prescalers, PLL configuration, USB, and MCO</td></tr>
 * <tr><td><code>RCC_CIR</code></td><td><code>0x08</code></td><td>Clock-ready interrupts, status flags, and clear bits</td></tr>
 * <tr><td><code>RCC_APB2RSTR</code> / <code>RCC_APB1RSTR</code></td><td><code>0x0C</code> / <code>0x10</code></td><td>Peripheral reset control on APB2 and APB1 buses</td></tr>
 * <tr><td><code>RCC_AHBENR</code> / <code>RCC_APB2ENR</code> / <code>RCC_APB1ENR</code></td><td><code>0x14</code> / <code>0x18</code> / <code>0x1C</code></td><td>Peripheral clock gating on AHB, APB2, and APB1 buses</td></tr>
 * <tr><td><code>RCC_BDCR</code> / <code>RCC_CSR</code></td><td><code>0x20</code> / <code>0x24</code></td><td>Backup-domain control, low-speed clocks, and reset-status flags</td></tr>
 * </table>
 *
 * This codebase documents RCC in three software layers in execution order:
 * - Register layer: @ref `stm32f1xx_rcc.h`
 * - Low-level control layer: @ref `rcc_ll.h`
 * - Driver/orchestration layer: @ref `rcc.h`
 */

/**
 * @defgroup RCC_01_RegisterLayer RCC Register Layer
 * @ingroup RCC
 * @brief Raw RCC register structures, register fields, and device-level encodings
 * @details
 * This layer mirrors the hardware-visible RCC chapter from the reference manual.
 * It is intentionally close to the register map so the LL layer can program the
 * hardware without re-describing bit positions or field encodings.
 *
 * Theory to implementation mapping:
 * - Clock-source control lives in `RCC_CR`.
 * - Clock-tree selection and prescalers live in `RCC_CFGR`.
 * - Bus gate and reset masks live in `RCC_AHBENR`, `RCC_APB2ENR`, `RCC_APB1ENR`,
 *   `RCC_APB2RSTR`, and `RCC_APB1RSTR`.
 * - Backup and low-speed clock control live in `RCC_BDCR` and `RCC_CSR`.
 */

/**
 * @defgroup RCC_02_LL RCC Low-Level Control Layer
 * @ingroup RCC
 * @brief Register-near RCC control interface used by the driver layer
 * @details
 * This layer converts raw RCC register definitions into typed operations that directly
 * express hardware actions. It owns register access helpers, hardware field encodings,
 * system-clock source control, prescaler programming, and peripheral clock/reset access.
 */

/**
 * @defgroup RCC_03_Driver RCC Driver Layer
 * @ingroup RCC
 * @brief Validated RCC orchestration layer built on top of `rcc_ll.h`
 * @details
 * This layer turns a requested clock-tree policy into a safe runtime sequence.
 * It owns validation, derived-frequency calculation, transition planning, clock-tree
 * orchestration, and public runtime query APIs.
 */

/**
 * @addtogroup RCC_01_RegisterLayer
 * @{
 */

// ------------------------------------------------------------------------------------------
// RCC_CR (Clock Control Register)
// ------------------------------------------------------------------------------------------ 

/**
 * @brief RCC Clock Source Control Register Definitions
 * @defgroup RCC_01_RegisterLayer_01_ClockControl RCC Clock Control Register
 * @ingroup RCC_01_RegisterLayer
 * @details
 * @section RCC_CR_Theory Theory and Practical Role
 * This page documents `RCC_CR`, which controls oscillator enable states, ready flags,
 * HSI trimming/calibration, HSE bypass, CSS, and PLL enable sequencing.
 * It is the practical entry point for bringing clock sources online before any
 * system-clock switch can occur.
 *
 * @section RCC_CR_Macros Register-Specific Macros
 * The macro definitions below expose the raw bit positions, masks, and convenience aliases
 * used by the LL layer when it needs direct symbolic access to `RCC_CR` fields.
 *
 * @section RCC_CR_Union Register Union View
 * The `union RCC_CR` view inside @ref RCC_TypeDef mirrors the same register in software so
 * a developer can compare the full register image (`.REG`) against the named bitfield view (`.BIT`).
 * @{
 */

// ------ HSION (Internal High-Speed Clock Enable) ------ // 
/** @brief Internal High-Speed Clock Enable Position @def RCC_CR_HSION_Pos */
#define RCC_CR_HSION_Pos							((uint8_t) 0U)
/** @brief Internal High-Speed Clock Enable Mask @def RCC_CR_HSION_Msk */
#define RCC_CR_HSION_Msk							(BIT_VALUE(0x01UL, RCC_CR_HSION_Pos))
/** @brief Internal High-Speed Clock Enable @def RCC_CR_HSION */
#define RCC_CR_HSION								RCC_CR_HSION_Msk

// ------ HSIRDY (Internal High-Speed Clock Ready) ------ // 
/** @brief Internal High-Speed Clock Ready Flag Position @def RCC_CR_HSIRDY_Pos */
#define RCC_CR_HSIRDY_Pos							((uint8_t) 1U)
/** @brief Internal High-Speed Clock Ready Flag Mask @def RCC_CR_HSIRDY_Msk */
#define RCC_CR_HSIRDY_Msk							(BIT_VALUE(0x01UL, RCC_CR_HSIRDY_Pos))
/** @brief Internal High-Speed Clock Ready Flag @def RCC_CR_HSIRDY */
#define RCC_CR_HSIRDY								RCC_CR_HSIRDY_Msk

// ------ HSITRIM (Internal High-Speed Clock Trimming) ------ // 
/** @brief Internal High-Speed Clock Trimming Position (5 bits) @def RCC_CR_HSITRIM_Pos */
#define RCC_CR_HSITRIM_Pos							((uint8_t) 3U)
/** @brief Internal High-Speed Clock Trimming Mask (5 bits) @def RCC_CR_HSITRIM_Msk */
#define RCC_CR_HSITRIM_Msk							(BIT_VALUE(0x1FUL, RCC_CR_HSITRIM_Pos))
/** @brief Internal High-Speed Clock Trimming @def RCC_CR_HSITRIM */
#define RCC_CR_HSITRIM								RCC_CR_HSITRIM_Msk

// ------ HSICAL (Internal High-Speed Clock Calibration) ------ // 
/** @brief Internal High-Speed Clock Calibration Position (8 bits) @def RCC_CR_HSICAL_Pos */
#define RCC_CR_HSICAL_Pos							((uint8_t) 8U)
/** @brief Internal High-Speed Clock Calibration Mask (8 bits) @def RCC_CR_HSICAL_Msk */
#define RCC_CR_HSICAL_Msk							(BIT_VALUE(0xFFUL, RCC_CR_HSICAL_Pos))
/** @brief Internal High-Speed Clock Calibration @def RCC_CR_HSICAL */
#define RCC_CR_HSICAL								RCC_CR_HSICAL_Msk

// ------ HSEON (External High-Speed Clock Enable) ------ // 
/** @brief External High-Speed Clock Enable Position @def RCC_CR_HSEON_Pos */
#define RCC_CR_HSEON_Pos							((uint8_t) 16U)
/** @brief External High-Speed Clock Enable Mask @def RCC_CR_HSEON_Msk */
#define RCC_CR_HSEON_Msk							(BIT_VALUE(0x01UL, RCC_CR_HSEON_Pos))
/** @brief External High-Speed Clock Enable @def RCC_CR_HSEON */
#define RCC_CR_HSEON								RCC_CR_HSEON_Msk

// ------ HSERDY (External High-Speed Clock Ready) ------ // 
/** @brief External High-Speed Clock Ready Flag Position @def RCC_CR_HSERDY_Pos */
#define RCC_CR_HSERDY_Pos							((uint8_t) 17U)
/** @brief External High-Speed Clock Ready Flag Mask @def RCC_CR_HSERDY_Msk */
#define RCC_CR_HSERDY_Msk							(BIT_VALUE(0x01UL, RCC_CR_HSERDY_Pos))
/** @brief External High-Speed Clock Ready Flag @def RCC_CR_HSERDY */
#define RCC_CR_HSERDY								RCC_CR_HSERDY_Msk

// ------ HSEBYP (External High-Speed Clock Bypass) ------ // 
/** @brief External High-Speed Clock Bypass Position @def RCC_CR_HSEBYP_Pos */
#define RCC_CR_HSEBYP_Pos							((uint8_t) 18U)
/** @brief External High-Speed Clock Bypass Mask @def RCC_CR_HSEBYP_Msk */
#define RCC_CR_HSEBYP_Msk							(BIT_VALUE(0x01UL, RCC_CR_HSEBYP_Pos))
/** @brief External High-Speed Clock Bypass @def RCC_CR_HSEBYP */
#define RCC_CR_HSEBYP								RCC_CR_HSEBYP_Msk

// ------ CSSON (Clock Security System Enable) ------ // 
/** @brief Clock Security System Enable Position @def RCC_CR_CSSON_Pos */
#define RCC_CR_CSSON_Pos							((uint8_t) 19U)
/** @brief Clock Security System Enable Mask @def RCC_CR_CSSON_Msk */
#define RCC_CR_CSSON_Msk							(BIT_VALUE(0x01UL, RCC_CR_CSSON_Pos))
/** @brief Clock Security System Enable @def RCC_CR_CSSON */
#define RCC_CR_CSSON								RCC_CR_CSSON_Msk

// ------ PLLON (PLL Enable) ------ // 
/** @brief PLL Enable Position @def RCC_CR_PLLON_Pos */
#define RCC_CR_PLLON_Pos							((uint8_t) 24U)
/** @brief PLL Enable Mask @def RCC_CR_PLLON_Msk */
#define RCC_CR_PLLON_Msk							(BIT_VALUE(0x01UL, RCC_CR_PLLON_Pos))
/** @brief PLL Enable @def RCC_CR_PLLON */
#define RCC_CR_PLLON								RCC_CR_PLLON_Msk

// ------ PLLRDY (PLL Ready) ------ // 
/** @brief PLL Ready Flag Position @def RCC_CR_PLLRDY_Pos */
#define RCC_CR_PLLRDY_Pos							((uint8_t) 25U)
/** @brief PLL Ready Flag Mask @def RCC_CR_PLLRDY_Msk */
#define RCC_CR_PLLRDY_Msk							(BIT_VALUE(0x01UL, RCC_CR_PLLRDY_Pos))
/** @brief PLL Ready Flag @def RCC_CR_PLLRDY */
#define RCC_CR_PLLRDY								RCC_CR_PLLRDY_Msk

/** @} */ // RCC_CR

// ------------------------------------------------------------------------------------------
// RCC_CFGR (Clock Configuration Register)
// ------------------------------------------------------------------------------------------ 

/**
 * @brief RCC Clock Tree Configuration Register Definitions
 * @defgroup RCC_01_RegisterLayer_02_ClockConfiguration RCC Clock Configuration Register
 * @ingroup RCC_01_RegisterLayer
 * @details
 * @section RCC_CFGR_Theory Theory and Practical Role
 * This page documents `RCC_CFGR`, which owns SYSCLK switching, SWS status, AHB/APB
 * prescalers, ADC prescaler, PLL source/divider/multiplier selection, USB prescaler,
 * and MCO output selection.
 *
 * @section RCC_CFGR_Macros Register-Specific Macros
 * The macro definitions below describe the field encodings used to build or decode the
 * practical clock-tree state stored in `RCC_CFGR`.
 *
 * @section RCC_CFGR_Union Register Union View
 * The `union RCC_CFGR` view inside @ref RCC_TypeDef provides both whole-register access and a
 * bitfield representation so the register theory maps directly to implementation.
 * @{
 */

// ------ SW (System Clock Switch) ------ //
/** @brief System Clock Switch Position (2 bits) @def RCC_CFGR_SW_Pos */
#define RCC_CFGR_SW_Pos							((uint8_t) 0U)
/** @brief System Clock Switch Mask (2 bits) @def RCC_CFGR_SW_Msk */
#define RCC_CFGR_SW_Msk							(BIT_VALUE(0x03UL, RCC_CFGR_SW_Pos))
/** @brief System Clock Switch @def RCC_CFGR_SW */
#define RCC_CFGR_SW								RCC_CFGR_SW_Msk
/** @brief HSI selected as system clock @def RCC_CFGR_SW_HSI */
#define RCC_CFGR_SW_HSI							(BIT_VALUE(0x00UL, RCC_CFGR_SW_Pos))
/** @brief HSE selected as system clock @def RCC_CFGR_SW_HSE */
#define RCC_CFGR_SW_HSE							(BIT_VALUE(0x01UL, RCC_CFGR_SW_Pos))
/** @brief PLL selected as system clock @def RCC_CFGR_SW_PLL */
#define RCC_CFGR_SW_PLL							(BIT_VALUE(0x02UL, RCC_CFGR_SW_Pos))

// ------ SWS (System Clock Switch Status) ------ //
/** @brief System Clock Switch Status Position (2 bits) @def RCC_CFGR_SWS_Pos */
#define RCC_CFGR_SWS_Pos						((uint8_t) 2U)
/** @brief System Clock Switch Status Mask (2 bits) @def RCC_CFGR_SWS_Msk */
#define RCC_CFGR_SWS_Msk						(BIT_VALUE(0x03UL, RCC_CFGR_SWS_Pos))
/** @brief System Clock Switch Status @def RCC_CFGR_SWS */
#define RCC_CFGR_SWS							RCC_CFGR_SWS_Msk
/** @brief HSI selected as system clock @def RCC_CFGR_SWS_HSI */
#define RCC_CFGR_SWS_HSI						(BIT_VALUE(0x00UL, RCC_CFGR_SWS_Pos))
/** @brief HSE selected as system clock @def RCC_CFGR_SWS_HSE */
#define RCC_CFGR_SWS_HSE						(BIT_VALUE(0x01UL, RCC_CFGR_SWS_Pos))
/** @brief PLL selected as system clock @def RCC_CFGR_SWS_PLL */
#define RCC_CFGR_SWS_PLL						(BIT_VALUE(0x02UL, RCC_CFGR_SWS_Pos))

// ------ HPRE (AHB Prescaler) ------ //
/** @brief AHB Prescaler Position (4 bits) @def RCC_CFGR_HPRE_Pos */
#define RCC_CFGR_HPRE_Pos						((uint8_t) 4U)
/** @brief AHB Prescaler Mask (4 bits) @def RCC_CFGR_HPRE_Msk */
#define RCC_CFGR_HPRE_Msk						(BIT_VALUE(0x0FUL, RCC_CFGR_HPRE_Pos))
/** @brief AHB Prescaler @def RCC_CFGR_HPRE */
#define RCC_CFGR_HPRE							RCC_CFGR_HPRE_Msk
/** @brief AHB prescaler = 1 (no division) @def RCC_CFGR_HPRE_DIV1 */
#define RCC_CFGR_HPRE_DIV1						(BIT_VALUE(0x00UL, RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 2 @def RCC_CFGR_HPRE_DIV2 */
#define RCC_CFGR_HPRE_DIV2						(BIT_VALUE(0x08UL, RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 4 @def RCC_CFGR_HPRE_DIV4 */
#define RCC_CFGR_HPRE_DIV4						(BIT_VALUE(0x09UL, RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 8 @def RCC_CFGR_HPRE_DIV8 */
#define RCC_CFGR_HPRE_DIV8						(BIT_VALUE(0x0AUL, RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 16 @def RCC_CFGR_HPRE_DIV16 */
#define RCC_CFGR_HPRE_DIV16						(BIT_VALUE(0x0BUL, RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 64 @def RCC_CFGR_HPRE_DIV64 */
#define RCC_CFGR_HPRE_DIV64						(BIT_VALUE(0x0CUL, RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 128 @def RCC_CFGR_HPRE_DIV128 */
#define RCC_CFGR_HPRE_DIV128					(BIT_VALUE(0x0DUL, RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 256 @def RCC_CFGR_HPRE_DIV256 */
#define RCC_CFGR_HPRE_DIV256					(BIT_VALUE(0x0EUL, RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 512 @def RCC_CFGR_HPRE_DIV512 */
#define RCC_CFGR_HPRE_DIV512					(BIT_VALUE(0x0FUL, RCC_CFGR_HPRE_Pos))

// ------ PPRE1 (APB Low-Speed Prescaler - APB1) ------ //
/** @brief APB1 Prescaler Position (3 bits) @def RCC_CFGR_PPRE1_Pos */
#define RCC_CFGR_PPRE1_Pos						((uint8_t) 8U)
/** @brief APB1 Prescaler Mask (3 bits) @def RCC_CFGR_PPRE1_Msk */
#define RCC_CFGR_PPRE1_Msk						(BIT_VALUE(0x07UL, RCC_CFGR_PPRE1_Pos))
/** @brief APB1 Prescaler @def RCC_CFGR_PPRE1 */
#define RCC_CFGR_PPRE1							RCC_CFGR_PPRE1_Msk
/** @brief APB1 prescaler = 1 (no division) @def RCC_CFGR_PPRE1_DIV1 */
#define RCC_CFGR_PPRE1_DIV1						(BIT_VALUE(0x00UL, RCC_CFGR_PPRE1_Pos))
/** @brief APB1 prescaler = 2 @def RCC_CFGR_PPRE1_DIV2 */
#define RCC_CFGR_PPRE1_DIV2						(BIT_VALUE(0x04UL, RCC_CFGR_PPRE1_Pos))
/** @brief APB1 prescaler = 4 @def RCC_CFGR_PPRE1_DIV4 */
#define RCC_CFGR_PPRE1_DIV4						(BIT_VALUE(0x05UL, RCC_CFGR_PPRE1_Pos))
/** @brief APB1 prescaler = 8 @def RCC_CFGR_PPRE1_DIV8 */
#define RCC_CFGR_PPRE1_DIV8						(BIT_VALUE(0x06UL, RCC_CFGR_PPRE1_Pos))
/** @brief APB1 prescaler = 16 @def RCC_CFGR_PPRE1_DIV16 */
#define RCC_CFGR_PPRE1_DIV16					(BIT_VALUE(0x07UL, RCC_CFGR_PPRE1_Pos))

// ------ PPRE2 (APB High-Speed Prescaler - APB2) ------ //
/** @brief APB2 Prescaler Position (3 bits) @def RCC_CFGR_PPRE2_Pos */
#define RCC_CFGR_PPRE2_Pos						((uint8_t) 11U)
/** @brief APB2 Prescaler Mask (3 bits) @def RCC_CFGR_PPRE2_Msk */
#define RCC_CFGR_PPRE2_Msk						(BIT_VALUE(0x07UL, RCC_CFGR_PPRE2_Pos))
/** @brief APB2 Prescaler @def RCC_CFGR_PPRE2 */
#define RCC_CFGR_PPRE2							RCC_CFGR_PPRE2_Msk
/** @brief APB2 prescaler = 1 (no division) @def RCC_CFGR_PPRE2_DIV1 */
#define RCC_CFGR_PPRE2_DIV1						(BIT_VALUE(0x00UL, RCC_CFGR_PPRE2_Pos))
/** @brief APB2 prescaler = 2 @def RCC_CFGR_PPRE2_DIV2 */
#define RCC_CFGR_PPRE2_DIV2						(BIT_VALUE(0x04UL, RCC_CFGR_PPRE2_Pos))
/** @brief APB2 prescaler = 4 @def RCC_CFGR_PPRE2_DIV4 */
#define RCC_CFGR_PPRE2_DIV4						(BIT_VALUE(0x05UL, RCC_CFGR_PPRE2_Pos))
/** @brief APB2 prescaler = 8 @def RCC_CFGR_PPRE2_DIV8 */
#define RCC_CFGR_PPRE2_DIV8						(BIT_VALUE(0x06UL, RCC_CFGR_PPRE2_Pos))
/** @brief APB2 prescaler = 16 @def RCC_CFGR_PPRE2_DIV16 */
#define RCC_CFGR_PPRE2_DIV16					(BIT_VALUE(0x07UL, RCC_CFGR_PPRE2_Pos))

// ------ ADCPRE (ADC Prescaler) ------ //
/** @brief ADC Prescaler Position (2 bits) @def RCC_CFGR_ADCPRE_Pos */
#define RCC_CFGR_ADCPRE_Pos						((uint8_t) 14U)
/** @brief ADC Prescaler Mask (2 bits) @def RCC_CFGR_ADCPRE_Msk */
#define RCC_CFGR_ADCPRE_Msk						(BIT_VALUE(0x03UL, RCC_CFGR_ADCPRE_Pos))
/** @brief ADC Prescaler @def RCC_CFGR_ADCPRE */
#define RCC_CFGR_ADCPRE							RCC_CFGR_ADCPRE_Msk
/** @brief ADC prescaler = 2 (PCLK2/2) @def RCC_CFGR_ADCPRE_DIV2 */
#define RCC_CFGR_ADCPRE_DIV2					(BIT_VALUE(0x00UL, RCC_CFGR_ADCPRE_Pos))
/** @brief ADC prescaler = 4 (PCLK2/4) @def RCC_CFGR_ADCPRE_DIV4 */
#define RCC_CFGR_ADCPRE_DIV4					(BIT_VALUE(0x01UL, RCC_CFGR_ADCPRE_Pos))
/** @brief ADC prescaler = 6 (PCLK2/6) @def RCC_CFGR_ADCPRE_DIV6 */
#define RCC_CFGR_ADCPRE_DIV6					(BIT_VALUE(0x02UL, RCC_CFGR_ADCPRE_Pos))
/** @brief ADC prescaler = 8 (PCLK2/8) @def RCC_CFGR_ADCPRE_DIV8 */
#define RCC_CFGR_ADCPRE_DIV8					(BIT_VALUE(0x03UL, RCC_CFGR_ADCPRE_Pos))

// ------ PLLSRC (PLL Entry Clock Source) ------ //
/** @brief PLL Entry Clock Source Position @def RCC_CFGR_PLLSRC_Pos */
#define RCC_CFGR_PLLSRC_Pos						((uint8_t) 16U)
/** @brief PLL Entry Clock Source Mask @def RCC_CFGR_PLLSRC_Msk */
#define RCC_CFGR_PLLSRC_Msk						(BIT_VALUE(0x01UL, RCC_CFGR_PLLSRC_Pos))
/** @brief PLL Entry Clock Source @def RCC_CFGR_PLLSRC */
#define RCC_CFGR_PLLSRC							RCC_CFGR_PLLSRC_Msk
/** @brief HSI/2 selected as PLL input clock @def RCC_CFGR_PLLSRC_HSI_DIV2 */
#define RCC_CFGR_PLLSRC_HSI_DIV2				(BIT_VALUE(0x00UL, RCC_CFGR_PLLSRC_Pos))
/** @brief HSE selected as PLL input clock @def RCC_CFGR_PLLSRC_HSE */
#define RCC_CFGR_PLLSRC_HSE						(BIT_VALUE(0x01UL, RCC_CFGR_PLLSRC_Pos))

// ------ PLLXTPRE (HSE Divider for PLL Entry) ------ //
/** @brief HSE Divider for PLL Entry Position @def RCC_CFGR_PLLXTPRE_Pos */
#define RCC_CFGR_PLLXTPRE_Pos					((uint8_t) 17U)
/** @brief HSE Divider for PLL Entry Mask @def RCC_CFGR_PLLXTPRE_Msk */
#define RCC_CFGR_PLLXTPRE_Msk					(BIT_VALUE(0x01UL, RCC_CFGR_PLLXTPRE_Pos))
/** @brief HSE Divider for PLL Entry @def RCC_CFGR_PLLXTPRE */
#define RCC_CFGR_PLLXTPRE						RCC_CFGR_PLLXTPRE_Msk
#define RCC_CFGR_PLLXTPRE_HSE					(BIT_VALUE(0x00UL, RCC_CFGR_PLLXTPRE_Pos))
/** @brief HSE divided by 2 before PLL @def RCC_CFGR_PLLXTPRE_HSE_DIV2 */
#define RCC_CFGR_PLLXTPRE_HSE_DIV2				(BIT_VALUE(0x01UL, RCC_CFGR_PLLXTPRE_Pos))

// ------ PLLMUL (PLL Multiplication Factor) ------ //
/** @brief PLL Multiplication Factor Position (4 bits) @def RCC_CFGR_PLLMUL_Pos */
#define RCC_CFGR_PLLMUL_Pos						((uint8_t) 18U)
/** @brief PLL Multiplication Factor Mask (4 bits) @def RCC_CFGR_PLLMUL_Msk */
#define RCC_CFGR_PLLMUL_Msk						(BIT_VALUE(0x0FUL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL Multiplication Factor @def RCC_CFGR_PLLMUL */
#define RCC_CFGR_PLLMUL							RCC_CFGR_PLLMUL_Msk
/** @brief PLL input clock x 2 @def RCC_CFGR_PLLMUL_2 */
#define RCC_CFGR_PLLMUL_2						(BIT_VALUE(0x00UL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 3 @def RCC_CFGR_PLLMUL_3 */
#define RCC_CFGR_PLLMUL_3						(BIT_VALUE(0x01UL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 4 @def RCC_CFGR_PLLMUL_4 */
#define RCC_CFGR_PLLMUL_4						(BIT_VALUE(0x02UL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 5 @def RCC_CFGR_PLLMUL_5 */
#define RCC_CFGR_PLLMUL_5						(BIT_VALUE(0x03UL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 6 @def RCC_CFGR_PLLMUL_6 */
#define RCC_CFGR_PLLMUL_6						(BIT_VALUE(0x04UL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 7 @def RCC_CFGR_PLLMUL_7 */
#define RCC_CFGR_PLLMUL_7						(BIT_VALUE(0x05UL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 8 @def RCC_CFGR_PLLMUL_8 */
#define RCC_CFGR_PLLMUL_8						(BIT_VALUE(0x06UL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 9 @def RCC_CFGR_PLLMUL_9 */
#define RCC_CFGR_PLLMUL_9						(BIT_VALUE(0x07UL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 10 @def RCC_CFGR_PLLMUL_10 */
#define RCC_CFGR_PLLMUL_10						(BIT_VALUE(0x08UL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 11 @def RCC_CFGR_PLLMUL_11 */
#define RCC_CFGR_PLLMUL_11						(BIT_VALUE(0x9UL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 12 @def RCC_CFGR_PLLMUL_12 */
#define RCC_CFGR_PLLMUL_12						(BIT_VALUE(0xAUL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 13 @def RCC_CFGR_PLLMUL_13 */
#define RCC_CFGR_PLLMUL_13						(BIT_VALUE(0xBUL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 14 @def RCC_CFGR_PLLMUL_14 */
#define RCC_CFGR_PLLMUL_14						(BIT_VALUE(0xCUL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 15 @def RCC_CFGR_PLLMUL_15 */
#define RCC_CFGR_PLLMUL_15						(BIT_VALUE(0xDUL, RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 16 @def RCC_CFGR_PLLMUL_16 */
#define RCC_CFGR_PLLMUL_16						(BIT_VALUE(0xEUL, RCC_CFGR_PLLMUL_Pos))

// ------ USBPRE (USB Prescaler) ------ //
/** @brief USB Prescaler Position @def RCC_CFGR_USBPRE_Pos */
#define RCC_CFGR_USBPRE_Pos						((uint8_t) 22U)
/** @brief USB Prescaler Mask @def RCC_CFGR_USBPRE_Msk */
#define RCC_CFGR_USBPRE_Msk						(BIT_VALUE(0x01UL, RCC_CFGR_USBPRE_Pos))
/** @brief USB Prescaler @def RCC_CFGR_USBPRE */
#define RCC_CFGR_USBPRE							RCC_CFGR_USBPRE_Msk
/** @brief PLL clock divided by 1.5 (48 MHz for USB) @def RCC_CFGR_USBPRE_DIV1_5 */
#define RCC_CFGR_USBPRE_DIV1_5					(BIT_VALUE(0x00UL, RCC_CFGR_USBPRE_Pos))
/** @brief PLL clock directly used as USB clock (must be 48 MHz) @def RCC_CFGR_USBPRE_DIRECT */
#define RCC_CFGR_USBPRE_DIRECT					(BIT_VALUE(0x01UL, RCC_CFGR_USBPRE_Pos))

// ------ MCO (Microcontroller Clock Output) ------ //
/** @brief Microcontroller Clock Output Position (3 bits) @def RCC_CFGR_MCO_Pos */
#define RCC_CFGR_MCO_Pos						((uint8_t) 24U)
/** @brief Microcontroller Clock Output Mask (3 bits) @def RCC_CFGR_MCO_Msk */
#define RCC_CFGR_MCO_Msk						(BIT_VALUE(0x07UL, RCC_CFGR_MCO_Pos))
/** @brief Microcontroller Clock Output @def RCC_CFGR_MCO */
#define RCC_CFGR_MCO							RCC_CFGR_MCO_Msk
/** @brief No clock output on MCO @def RCC_CFGR_MCO_NOCLOCK */
#define RCC_CFGR_MCO_NOCLOCK					(BIT_VALUE(0x00UL, RCC_CFGR_MCO_Pos))
/** @brief System clock output on MCO @def RCC_CFGR_MCO_SYSCLK */
#define RCC_CFGR_MCO_SYSCLK						(BIT_VALUE(0x01UL, RCC_CFGR_MCO_Pos))
/** @brief HSI clock output on MCO @def RCC_CFGR_MCO_HSI */
#define RCC_CFGR_MCO_HSI						(BIT_VALUE(0x02UL, RCC_CFGR_MCO_Pos))
/** @brief HSE clock output on MCO @def RCC_CFGR_MCO_HSE */
#define RCC_CFGR_MCO_HSE						(BIT_VALUE(0x03UL, RCC_CFGR_MCO_Pos))
/** @brief PLL clock divided by 2 output on MCO @def RCC_CFGR_MCO_PLL_DIV2 */
#define RCC_CFGR_MCO_PLL_DIV2					(BIT_VALUE(0x04UL, RCC_CFGR_MCO_Pos))
/** @brief PLL clock output on MCO @def RCC_CFGR_MCO_PLL */
#define RCC_CFGR_MCO_PLL						(BIT_VALUE(0x05UL, RCC_CFGR_MCO_Pos))

/** @} */ // RCC_CFGR 

// ------------------------------------------------------------------------------------------
// RCC_CIR (Clock Interrupt Register)
// ------------------------------------------------------------------------------------------ 

/**
 * @brief RCC Clock Interrupt Register Definitions
 * @defgroup RCC_01_RegisterLayer_03_ClockInterrupt RCC Clock Interrupt Register
 * @ingroup RCC_01_RegisterLayer
 * @details
 * @section RCC_CIR_Theory Theory and Practical Role
 * This page documents `RCC_CIR`, which collects ready interrupts and clear flags for
 * internal/external oscillators, PLL lock, and the clock security system.
 *
 * @section RCC_CIR_Macros Register-Specific Macros
 * The macro definitions below map the interrupt/status, enable, and clear fields that the
 * LL layer uses when working with RCC ready interrupts and CSS reporting.
 *
 * @section RCC_CIR_Union Register Union View
 * The `union RCC_CIR` view inside @ref RCC_TypeDef lets you inspect the same register either
 * as a 32-bit image or as individual interrupt-related fields.
 * @{
 */

// ------ LSIRDYF (LSI Ready Interrupt Flag) ------ // 
/** @brief LSI Ready Interrupt Flag Position @def RCC_CIR_LSIRDYF_Pos */
#define RCC_CIR_LSIRDYF_Pos							((uint8_t) 0U)
/** @brief LSI Ready Interrupt Flag Mask @def RCC_CIR_LSIRDYF_Msk */
#define RCC_CIR_LSIRDYF_Msk							(BIT_VALUE(0x01UL, RCC_CIR_LSIRDYF_Pos))
/** @brief LSI Ready Interrupt Flag @def RCC_CIR_LSIRDYF */
#define RCC_CIR_LSIRDYF								RCC_CIR_LSIRDYF_Msk

// ------ LSERDYF (LSE Ready Interrupt Flag) ------ // 
/** @brief LSE Ready Interrupt Flag Position @def RCC_CIR_LSERDYF_Pos */
#define RCC_CIR_LSERDYF_Pos							((uint8_t) 1U)
/** @brief LSE Ready Interrupt Flag Mask @def RCC_CIR_LSERDYF_Msk */
#define RCC_CIR_LSERDYF_Msk							(BIT_VALUE(0x01UL, RCC_CIR_LSERDYF_Pos))
/** @brief LSE Ready Interrupt Flag @def RCC_CIR_LSERDYF */
#define RCC_CIR_LSERDYF								RCC_CIR_LSERDYF_Msk

// ------ HSIRDYF (HSI Ready Interrupt Flag) ------ // 
/** @brief HSI Ready Interrupt Flag Position @def RCC_CIR_HSIRDYF_Pos */
#define RCC_CIR_HSIRDYF_Pos							((uint8_t) 2U)
/** @brief HSI Ready Interrupt Flag Mask @def RCC_CIR_HSIRDYF_Msk */
#define RCC_CIR_HSIRDYF_Msk							(BIT_VALUE(0x01UL, RCC_CIR_HSIRDYF_Pos))
/** @brief HSI Ready Interrupt Flag @def RCC_CIR_HSIRDYF */
#define RCC_CIR_HSIRDYF								RCC_CIR_HSIRDYF_Msk

// ------ HSERDYF (HSE Ready Interrupt Flag) ------ // 
/** @brief HSE Ready Interrupt Flag Position @def RCC_CIR_HSERDYF_Pos */
#define RCC_CIR_HSERDYF_Pos							((uint8_t) 3U)
/** @brief HSE Ready Interrupt Flag Mask @def RCC_CIR_HSERDYF_Msk */
#define RCC_CIR_HSERDYF_Msk							(BIT_VALUE(0x01UL, RCC_CIR_HSERDYF_Pos))
/** @brief HSE Ready Interrupt Flag @def RCC_CIR_HSERDYF */
#define RCC_CIR_HSERDYF								RCC_CIR_HSERDYF_Msk

// ------ PLLRDYF (PLL Ready Interrupt Flag) ------ // 
/** @brief PLL Ready Interrupt Flag Position @def RCC_CIR_PLLRDYF_Pos */
#define RCC_CIR_PLLRDYF_Pos							((uint8_t) 4U)
/** @brief PLL Ready Interrupt Flag Mask @def RCC_CIR_PLLRDYF_Msk */
#define RCC_CIR_PLLRDYF_Msk							(BIT_VALUE(0x01UL, RCC_CIR_PLLRDYF_Pos))
/** @brief PLL Ready Interrupt Flag @def RCC_CIR_PLLRDYF */
#define RCC_CIR_PLLRDYF								RCC_CIR_PLLRDYF_Msk

// ------ CSFF (Clock Security System Interrupt Flag) ------ // 
/** @brief Clock Security System Interrupt Flag Position @def RCC_CIR_CSFF_Pos */
#define RCC_CIR_CSFF_Pos							((uint8_t) 7U)
/** @brief Clock Security System Interrupt Flag Mask @def RCC_CIR_CSFF_Msk */
#define RCC_CIR_CSFF_Msk							(BIT_VALUE(0x01UL, RCC_CIR_CSFF_Pos))
/** @brief Clock Security System Interrupt Flag @def RCC_CIR_CSFF */
#define RCC_CIR_CSFF								RCC_CIR_CSFF_Msk

// ------ LSIRDYIE (LSI Ready Interrupt Enable) ------ // 
/** @brief LSI Ready Interrupt Enable Position @def RCC_CIR_LSIRDYIE_Pos */
#define RCC_CIR_LSIRDYIE_Pos						((uint8_t) 8U)
/** @brief LSI Ready Interrupt Enable Mask @def RCC_CIR_LSIRDYIE_Msk */
#define RCC_CIR_LSIRDYIE_Msk						(BIT_VALUE(0x01UL, RCC_CIR_LSIRDYIE_Pos))
/** @brief LSI Ready Interrupt Enable @def RCC_CIR_LSIRDYIE */
#define RCC_CIR_LSIRDYIE							RCC_CIR_LSIRDYIE_Msk

// ------ LSERDYIE (LSE Ready Interrupt Enable) ------ // 
/** @brief LSE Ready Interrupt Enable Position @def RCC_CIR_LSERDYIE_Pos */
#define RCC_CIR_LSERDYIE_Pos						((uint8_t) 9U)
/** @brief LSE Ready Interrupt Enable Mask @def RCC_CIR_LSERDYIE_Msk */
#define RCC_CIR_LSERDYIE_Msk						(BIT_VALUE(0x01UL, RCC_CIR_LSERDYIE_Pos))
/** @brief LSE Ready Interrupt Enable @def RCC_CIR_LSERDYIE */
#define RCC_CIR_LSERDYIE							RCC_CIR_LSERDYIE_Msk

// ------ HSIRDYIE (HSI Ready Interrupt Enable) ------ // 
/** @brief HSI Ready Interrupt Enable Position @def RCC_CIR_HSIRDYIE_Pos */
#define RCC_CIR_HSIRDYIE_Pos						((uint8_t) 10U)
/** @brief HSI Ready Interrupt Enable Mask @def RCC_CIR_HSIRDYIE_Msk */
#define RCC_CIR_HSIRDYIE_Msk						(BIT_VALUE(0x01UL, RCC_CIR_HSIRDYIE_Pos))
/** @brief HSI Ready Interrupt Enable @def RCC_CIR_HSIRDYIE */
#define RCC_CIR_HSIRDYIE							RCC_CIR_HSIRDYIE_Msk

// ------ HSERDYIE (HSE Ready Interrupt Enable) ------ // 
/** @brief HSE Ready Interrupt Enable Position @def RCC_CIR_HSERDYIE_Pos */
#define RCC_CIR_HSERDYIE_Pos						((uint8_t) 11U)
/** @brief HSE Ready Interrupt Enable Mask @def RCC_CIR_HSERDYIE_Msk */
#define RCC_CIR_HSERDYIE_Msk						(BIT_VALUE(0x01UL, RCC_CIR_HSERDYIE_Pos))
/** @brief HSE Ready Interrupt Enable @def RCC_CIR_HSERDYIE */
#define RCC_CIR_HSERDYIE							RCC_CIR_HSERDYIE_Msk

// ------ PLLRDYIE (PLL Ready Interrupt Enable) ------ // 
/** @brief PLL Ready Interrupt Enable Position @def RCC_CIR_PLLRDYIE_Pos */
#define RCC_CIR_PLLRDYIE_Pos						((uint8_t) 12U)
/** @brief PLL Ready Interrupt Enable Mask @def RCC_CIR_PLLRDYIE_Msk */
#define RCC_CIR_PLLRDYIE_Msk						(BIT_VALUE(0x01UL, RCC_CIR_PLLRDYIE_Pos))
/** @brief PLL Ready Interrupt Enable @def RCC_CIR_PLLRDYIE */
#define RCC_CIR_PLLRDYIE							RCC_CIR_PLLRDYIE_Msk

// ------ LSIRDYC (LSI Ready Interrupt Clear) ------ // 
/** @brief LSI Ready Interrupt Clear Position @def RCC_CIR_LSIRDYC_Pos */
#define RCC_CIR_LSIRDYC_Pos							((uint8_t) 16U)
/** @brief LSI Ready Interrupt Clear Mask @def RCC_CIR_LSIRDYC_Msk */
#define RCC_CIR_LSIRDYC_Msk							(BIT_VALUE(0x01UL, RCC_CIR_LSIRDYC_Pos))
/** @brief LSI Ready Interrupt Clear @def RCC_CIR_LSIRDYC */
#define RCC_CIR_LSIRDYC								RCC_CIR_LSIRDYC_Msk

// ------ LSERDYC (LSE Ready Interrupt Clear) ------ // 
/** @brief LSE Ready Interrupt Clear Position @def RCC_CIR_LSERDYC_Pos */
#define RCC_CIR_LSERDYC_Pos							((uint8_t) 17U)
/** @brief LSE Ready Interrupt Clear Mask @def RCC_CIR_LSERDYC_Msk */
#define RCC_CIR_LSERDYC_Msk							(BIT_VALUE(0x01UL, RCC_CIR_LSERDYC_Pos))
/** @brief LSE Ready Interrupt Clear @def RCC_CIR_LSERDYC */
#define RCC_CIR_LSERDYC								RCC_CIR_LSERDYC_Msk

// ------ HSIRDYC (HSI Ready Interrupt Clear) ------ // 
/** @brief HSI Ready Interrupt Clear Position @def RCC_CIR_HSIRDYC_Pos */
#define RCC_CIR_HSIRDYC_Pos							((uint8_t) 18U)
/** @brief HSI Ready Interrupt Clear Mask @def RCC_CIR_HSIRDYC_Msk */
#define RCC_CIR_HSIRDYC_Msk							(BIT_VALUE(0x01UL, RCC_CIR_HSIRDYC_Pos))
/** @brief HSI Ready Interrupt Clear @def RCC_CIR_HSIRDYC */
#define RCC_CIR_HSIRDYC								RCC_CIR_HSIRDYC_Msk

// ------ HSERDYC (HSE Ready Interrupt Clear) ------ // 
/** @brief HSE Ready Interrupt Clear Position @def RCC_CIR_HSERDYC_Pos */
#define RCC_CIR_HSERDYC_Pos							((uint8_t) 19U)
/** @brief HSE Ready Interrupt Clear Mask @def RCC_CIR_HSERDYC_Msk */
#define RCC_CIR_HSERDYC_Msk							(BIT_VALUE(0x01UL, RCC_CIR_HSERDYC_Pos))
/** @brief HSE Ready Interrupt Clear @def RCC_CIR_HSERDYC */
#define RCC_CIR_HSERDYC								RCC_CIR_HSERDYC_Msk

// ------ PLLRDYC (PLL Ready Interrupt Clear) ------ // 
/** @brief PLL Ready Interrupt Clear Position @def RCC_CIR_PLLRDYC_Pos */
#define RCC_CIR_PLLRDYC_Pos							((uint8_t) 20U)
/** @brief PLL Ready Interrupt Clear Mask @def RCC_CIR_PLLRDYC_Msk */
#define RCC_CIR_PLLRDYC_Msk							(BIT_VALUE(0x01UL, RCC_CIR_PLLRDYC_Pos))
/** @brief PLL Ready Interrupt Clear @def RCC_CIR_PLLRDYC */
#define RCC_CIR_PLLRDYC								RCC_CIR_PLLRDYC_Msk

// ------ CSSC (Clock Security System Interrupt Clear) ------ // 
/** @brief Clock Security System Interrupt Clear Position @def RCC_CIR_CSSC_Pos */
#define RCC_CIR_CSSC_Pos							((uint8_t) 23U)
/** @brief Clock Security System Interrupt Clear Mask @def RCC_CIR_CSSC_Msk */
#define RCC_CIR_CSSC_Msk							(BIT_VALUE(0x01UL, RCC_CIR_CSSC_Pos))
/** @brief Clock Security System Interrupt Clear @def RCC_CIR_CSSC */
#define RCC_CIR_CSSC								RCC_CIR_CSSC_Msk

/** @} */ // RCC_CIR

/**
 * @brief RCC Peripheral Reset Register Definitions
 * @defgroup RCC_01_RegisterLayer_04_PeripheralReset RCC Peripheral Reset Registers
 * @ingroup RCC_01_RegisterLayer
 * @details
 * @section RCC_RSTR_Theory Theory and Practical Role
 * This page documents the reset-register view used by the RCC software stack.
 * The explicit bit-mask definitions cover both `RCC_APB2RSTR` and `RCC_APB1RSTR`
 * so driver code can use symbolic reset masks without depending on bitfield access.
 *
 * @section RCC_RSTR_Macros Register-Specific Macros
 * The macro definitions below describe the APB2 and APB1 peripheral reset bits that can
 * be asserted and released through RCC reset control.
 *
 * @section RCC_RSTR_Union Register Union View
 * The register map later in this file exposes both `union RCC_APB2RSTR` and `union RCC_APB1RSTR`
 * so the reset theory and the concrete memory layout stay visible together.
 * @{
 */

// ------ AFIORST (Alternate Function I/O Reset) ------ //
/** @brief Alternate Function I/O Reset Position @def RCC_APB2RSTR_AFIORST_Pos */
#define RCC_APB2RSTR_AFIORST_Pos						((uint8_t) 0U)
/** @brief Alternate Function I/O Reset Mask @def RCC_APB2RSTR_AFIORST_Msk */
#define RCC_APB2RSTR_AFIORST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_AFIORST_Pos))
/** @brief Alternate Function I/O Reset @def RCC_APB2RSTR_AFIORST */
#define RCC_APB2RSTR_AFIORST							RCC_APB2RSTR_AFIORST_Msk

// ------ IOPARST (I/O Port A Reset) ------ //
/** @brief I/O Port A Reset Position @def RCC_APB2RSTR_IOPARST_Pos */
#define RCC_APB2RSTR_IOPARST_Pos						((uint8_t) 2U)
/** @brief I/O Port A Reset Mask @def RCC_APB2RSTR_IOPARST_Msk */
#define RCC_APB2RSTR_IOPARST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_IOPARST_Pos))
/** @brief I/O Port A Reset @def RCC_APB2RSTR_IOPARST */
#define RCC_APB2RSTR_IOPARST							RCC_APB2RSTR_IOPARST_Msk

// ------ IOPBRST (I/O Port B Reset) ------ //
/** @brief I/O Port B Reset Position @def RCC_APB2RSTR_IOPBRST_Pos */
#define RCC_APB2RSTR_IOPBRST_Pos						((uint8_t) 3U)
/** @brief I/O Port B Reset Mask @def RCC_APB2RSTR_IOPBRST_Msk */
#define RCC_APB2RSTR_IOPBRST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_IOPBRST_Pos))
/** @brief I/O Port B Reset @def RCC_APB2RSTR_IOPBRST */
#define RCC_APB2RSTR_IOPBRST							RCC_APB2RSTR_IOPBRST_Msk

// ------ IOPCRST (I/O Port C Reset) ------ //
/** @brief I/O Port C Reset Position @def RCC_APB2RSTR_IOPCRST_Pos */
#define RCC_APB2RSTR_IOPCRST_Pos						((uint8_t) 4U)
/** @brief I/O Port C Reset Mask @def RCC_APB2RSTR_IOPCRST_Msk */
#define RCC_APB2RSTR_IOPCRST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_IOPCRST_Pos))
/** @brief I/O Port C Reset @def RCC_APB2RSTR_IOPCRST */
#define RCC_APB2RSTR_IOPCRST							RCC_APB2RSTR_IOPCRST_Msk

// ------ IOPDRST (I/O Port D Reset) ------ //
/** @brief I/O Port D Reset Position @def RCC_APB2RSTR_IOPDRST_Pos */
#define RCC_APB2RSTR_IOPDRST_Pos						((uint8_t) 5U)
/** @brief I/O Port D Reset Mask @def RCC_APB2RSTR_IOPDRST_Msk */
#define RCC_APB2RSTR_IOPDRST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_IOPDRST_Pos))
/** @brief I/O Port D Reset @def RCC_APB2RSTR_IOPDRST */
#define RCC_APB2RSTR_IOPDRST							RCC_APB2RSTR_IOPDRST_Msk

// ------ IOPERST (I/O Port E Reset) ------ //
/** @brief I/O Port E Reset Position @def RCC_APB2RSTR_IOPERST_Pos */
#define RCC_APB2RSTR_IOPERST_Pos						((uint8_t) 6U)
/** @brief I/O Port E Reset Mask @def RCC_APB2RSTR_IOPERST_Msk */
#define RCC_APB2RSTR_IOPERST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_IOPERST_Pos))
/** @brief I/O Port E Reset @def RCC_APB2RSTR_IOPERST */
#define RCC_APB2RSTR_IOPERST							RCC_APB2RSTR_IOPERST_Msk

// ------ IOPFRST (I/O Port F Reset) ------ //
/** @brief I/O Port F Reset Position @def RCC_APB2RSTR_IOPFRST_Pos */
#define RCC_APB2RSTR_IOPFRST_Pos						((uint8_t) 7U)
/** @brief I/O Port F Reset Mask @def RCC_APB2RSTR_IOPFRST_Msk */
#define RCC_APB2RSTR_IOPFRST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_IOPFRST_Pos))
/** @brief I/O Port F Reset @def RCC_APB2RSTR_IOPFRST */
#define RCC_APB2RSTR_IOPFRST							RCC_APB2RSTR_IOPFRST_Msk

// ------ IOPGRST (I/O Port G Reset) ------ //
/** @brief I/O Port G Reset Position @def RCC_APB2RSTR_IOPGRST_Pos */
#define RCC_APB2RSTR_IOPGRST_Pos						((uint8_t) 8U)
/** @brief I/O Port G Reset Mask @def RCC_APB2RSTR_IOPGRST_Msk */
#define RCC_APB2RSTR_IOPGRST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_IOPGRST_Pos))
/** @brief I/O Port G Reset @def RCC_APB2RSTR_IOPGRST */
#define RCC_APB2RSTR_IOPGRST							RCC_APB2RSTR_IOPGRST_Msk

// ------ ADC1RST (ADC 1 Reset) ------ //
/** @brief ADC 1 Reset Position @def RCC_APB2RSTR_ADC1RST_Pos */
#define RCC_APB2RSTR_ADC1RST_Pos						((uint8_t) 9U)
/** @brief ADC 1 Reset Mask @def RCC_APB2RSTR_ADC1RST_Msk */
#define RCC_APB2RSTR_ADC1RST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_ADC1RST_Pos))
/** @brief ADC 1 Reset @def RCC_APB2RSTR_ADC1RST */
#define RCC_APB2RSTR_ADC1RST							RCC_APB2RSTR_ADC1RST_Msk

// ------ ADC2RST (ADC 2 Reset) ------ //
/** @brief ADC 2 Reset Position @def RCC_APB2RSTR_ADC2RST_Pos */
#define RCC_APB2RSTR_ADC2RST_Pos						((uint8_t) 10U)
/** @brief ADC 2 Reset Mask @def RCC_APB2RSTR_ADC2RST_Msk */
#define RCC_APB2RSTR_ADC2RST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_ADC2RST_Pos))
/** @brief ADC 2 Reset @def RCC_APB2RSTR_ADC2RST */
#define RCC_APB2RSTR_ADC2RST							RCC_APB2RSTR_ADC2RST_Msk

// ------ TIM1RST (TIM1 Timer Reset) ------ //
/** @brief TIM1 Timer Reset Position @def RCC_APB2RSTR_TIM1RST_Pos */
#define RCC_APB2RSTR_TIM1RST_Pos						((uint8_t) 11U)
/** @brief TIM1 Timer Reset Mask @def RCC_APB2RSTR_TIM1RST_Msk */
#define RCC_APB2RSTR_TIM1RST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_TIM1RST_Pos))
/** @brief TIM1 Timer Reset @def RCC_APB2RSTR_TIM1RST */
#define RCC_APB2RSTR_TIM1RST							RCC_APB2RSTR_TIM1RST_Msk

// ------ SPI1RST (SPI1 Reset) ------ //
/** @brief SPI1 Reset Position @def RCC_APB2RSTR_SPI1RST_Pos */
#define RCC_APB2RSTR_SPI1RST_Pos						((uint8_t) 12U)
/** @brief SPI1 Reset Mask @def RCC_APB2RSTR_SPI1RST_Msk */
#define RCC_APB2RSTR_SPI1RST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_SPI1RST_Pos))
/** @brief SPI1 Reset @def RCC_APB2RSTR_SPI1RST */
#define RCC_APB2RSTR_SPI1RST							RCC_APB2RSTR_SPI1RST_Msk

// ------ TIM8RST (TIM8 Timer Reset) ------ //
/** @brief TIM8 Timer Reset Position @def RCC_APB2RSTR_TIM8RST_Pos */
#define RCC_APB2RSTR_TIM8RST_Pos						((uint8_t) 13U)
/** @brief TIM8 Timer Reset Mask @def RCC_APB2RSTR_TIM8RST_Msk */
#define RCC_APB2RSTR_TIM8RST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_TIM8RST_Pos))
/** @brief TIM8 Timer Reset @def RCC_APB2RSTR_TIM8RST */
#define RCC_APB2RSTR_TIM8RST							RCC_APB2RSTR_TIM8RST_Msk

// ------ USART1RST (USART1 Reset) ------ //
/** @brief USART1 Reset Position @def RCC_APB2RSTR_USART1RST_Pos */
#define RCC_APB2RSTR_USART1RST_Pos						((uint8_t) 14U)
/** @brief USART1 Reset Mask @def RCC_APB2RSTR_USART1RST_Msk */
#define RCC_APB2RSTR_USART1RST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_USART1RST_Pos))
/** @brief USART1 Reset @def RCC_APB2RSTR_USART1RST */
#define RCC_APB2RSTR_USART1RST							RCC_APB2RSTR_USART1RST_Msk

// ------ ADC3RST (ADC 3 Reset) ------ //
/** @brief ADC 3 Reset Position @def RCC_APB2RSTR_ADC3RST_Pos */
#define RCC_APB2RSTR_ADC3RST_Pos						((uint8_t) 15U)
/** @brief ADC 3 Reset Mask @def RCC_APB2RSTR_ADC3RST_Msk */
#define RCC_APB2RSTR_ADC3RST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_ADC3RST_Pos))
/** @brief ADC 3 Reset @def RCC_APB2RSTR_ADC3RST */
#define RCC_APB2RSTR_ADC3RST							RCC_APB2RSTR_ADC3RST_Msk

// ------ TIM9RST (TIM9 Timer Reset) ------ // 
/** @brief TIM9 Timer Reset Position @def RCC_APB2RSTR_TIM9RST_Pos */
#define RCC_APB2RSTR_TIM9RST_Pos						((uint8_t) 19U)
/** @brief TIM9 Timer Reset Mask @def RCC_APB2RSTR_TIM9RST_Msk */
#define RCC_APB2RSTR_TIM9RST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_TIM9RST_Pos))
/** @brief TIM9 Timer Reset @def RCC_APB2RSTR_TIM9RST */
#define RCC_APB2RSTR_TIM9RST							RCC_APB2RSTR_TIM9RST_Msk

// ------ TIM10RST (TIM10 Timer Reset) ------ // 
/** @brief TIM10 Timer Reset Position @def RCC_APB2RSTR_TIM10RST_Pos */
#define RCC_APB2RSTR_TIM10RST_Pos						((uint8_t) 20U)
/** @brief TIM10 Timer Reset Mask @def RCC_APB2RSTR_TIM10RST_Msk */
#define RCC_APB2RSTR_TIM10RST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_TIM10RST_Pos))
/** @brief TIM10 Timer Reset @def RCC_APB2RSTR_TIM10RST */
#define RCC_APB2RSTR_TIM10RST							RCC_APB2RSTR_TIM10RST_Msk

// ------ TIM11RST (TIM11 Timer Reset) ------ // 
/** @brief TIM11 Timer Reset Position @def RCC_APB2RSTR_TIM11RST_Pos */
#define RCC_APB2RSTR_TIM11RST_Pos						((uint8_t) 21U)
/** @brief TIM11 Timer Reset Mask @def RCC_APB2RSTR_TIM11RST_Msk */
#define RCC_APB2RSTR_TIM11RST_Msk						(BIT_VALUE(0x01UL, RCC_APB2RSTR_TIM11RST_Pos))
/** @brief TIM11 Timer Reset @def RCC_APB2RSTR_TIM11RST */
#define RCC_APB2RSTR_TIM11RST							RCC_APB2RSTR_TIM11RST_Msk

/** @} */ // RCC_APB2RSTR

// ------------------------------------------------------------------------------------------
// RCC_APB1RSTR (APB1 Peripheral Reset Register)
// ------------------------------------------------------------------------------------------

/** @brief TIM2 Reset Position @def RCC_APB1RSTR_TIM2RST_Pos */
#define RCC_APB1RSTR_TIM2RST_Pos						((uint8_t) 0U)
/** @brief TIM2 Reset Mask @def RCC_APB1RSTR_TIM2RST_Msk */
#define RCC_APB1RSTR_TIM2RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_TIM2RST_Pos))
/** @brief TIM2 Reset @def RCC_APB1RSTR_TIM2RST */
#define RCC_APB1RSTR_TIM2RST							RCC_APB1RSTR_TIM2RST_Msk

/** @brief TIM3 Reset Position @def RCC_APB1RSTR_TIM3RST_Pos */
#define RCC_APB1RSTR_TIM3RST_Pos						((uint8_t) 1U)
/** @brief TIM3 Reset Mask @def RCC_APB1RSTR_TIM3RST_Msk */
#define RCC_APB1RSTR_TIM3RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_TIM3RST_Pos))
/** @brief TIM3 Reset @def RCC_APB1RSTR_TIM3RST */
#define RCC_APB1RSTR_TIM3RST							RCC_APB1RSTR_TIM3RST_Msk

/** @brief TIM4 Reset Position @def RCC_APB1RSTR_TIM4RST_Pos */
#define RCC_APB1RSTR_TIM4RST_Pos						((uint8_t) 2U)
/** @brief TIM4 Reset Mask @def RCC_APB1RSTR_TIM4RST_Msk */
#define RCC_APB1RSTR_TIM4RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_TIM4RST_Pos))
/** @brief TIM4 Reset @def RCC_APB1RSTR_TIM4RST */
#define RCC_APB1RSTR_TIM4RST							RCC_APB1RSTR_TIM4RST_Msk

/** @brief TIM5 Reset Position @def RCC_APB1RSTR_TIM5RST_Pos */
#define RCC_APB1RSTR_TIM5RST_Pos						((uint8_t) 3U)
/** @brief TIM5 Reset Mask @def RCC_APB1RSTR_TIM5RST_Msk */
#define RCC_APB1RSTR_TIM5RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_TIM5RST_Pos))
/** @brief TIM5 Reset @def RCC_APB1RSTR_TIM5RST */
#define RCC_APB1RSTR_TIM5RST							RCC_APB1RSTR_TIM5RST_Msk

/** @brief TIM6 Reset Position @def RCC_APB1RSTR_TIM6RST_Pos */
#define RCC_APB1RSTR_TIM6RST_Pos						((uint8_t) 4U)
/** @brief TIM6 Reset Mask @def RCC_APB1RSTR_TIM6RST_Msk */
#define RCC_APB1RSTR_TIM6RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_TIM6RST_Pos))
/** @brief TIM6 Reset @def RCC_APB1RSTR_TIM6RST */
#define RCC_APB1RSTR_TIM6RST							RCC_APB1RSTR_TIM6RST_Msk

/** @brief TIM7 Reset Position @def RCC_APB1RSTR_TIM7RST_Pos */
#define RCC_APB1RSTR_TIM7RST_Pos						((uint8_t) 5U)
/** @brief TIM7 Reset Mask @def RCC_APB1RSTR_TIM7RST_Msk */
#define RCC_APB1RSTR_TIM7RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_TIM7RST_Pos))
/** @brief TIM7 Reset @def RCC_APB1RSTR_TIM7RST */
#define RCC_APB1RSTR_TIM7RST							RCC_APB1RSTR_TIM7RST_Msk

/** @brief TIM12 Reset Position @def RCC_APB1RSTR_TIM12RST_Pos */
#define RCC_APB1RSTR_TIM12RST_Pos						((uint8_t) 6U)
/** @brief TIM12 Reset Mask @def RCC_APB1RSTR_TIM12RST_Msk */
#define RCC_APB1RSTR_TIM12RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_TIM12RST_Pos))
/** @brief TIM12 Reset @def RCC_APB1RSTR_TIM12RST */
#define RCC_APB1RSTR_TIM12RST							RCC_APB1RSTR_TIM12RST_Msk

/** @brief TIM13 Reset Position @def RCC_APB1RSTR_TIM13RST_Pos */
#define RCC_APB1RSTR_TIM13RST_Pos						((uint8_t) 7U)
/** @brief TIM13 Reset Mask @def RCC_APB1RSTR_TIM13RST_Msk */
#define RCC_APB1RSTR_TIM13RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_TIM13RST_Pos))
/** @brief TIM13 Reset @def RCC_APB1RSTR_TIM13RST */
#define RCC_APB1RSTR_TIM13RST							RCC_APB1RSTR_TIM13RST_Msk

/** @brief TIM14 Reset Position @def RCC_APB1RSTR_TIM14RST_Pos */
#define RCC_APB1RSTR_TIM14RST_Pos						((uint8_t) 8U)
/** @brief TIM14 Reset Mask @def RCC_APB1RSTR_TIM14RST_Msk */
#define RCC_APB1RSTR_TIM14RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_TIM14RST_Pos))
/** @brief TIM14 Reset @def RCC_APB1RSTR_TIM14RST */
#define RCC_APB1RSTR_TIM14RST							RCC_APB1RSTR_TIM14RST_Msk

/** @brief WWDG Reset Position @def RCC_APB1RSTR_WWDGRST_Pos */
#define RCC_APB1RSTR_WWDGRST_Pos						((uint8_t) 11U)
/** @brief WWDG Reset Mask @def RCC_APB1RSTR_WWDGRST_Msk */
#define RCC_APB1RSTR_WWDGRST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_WWDGRST_Pos))
/** @brief WWDG Reset @def RCC_APB1RSTR_WWDGRST */
#define RCC_APB1RSTR_WWDGRST							RCC_APB1RSTR_WWDGRST_Msk

/** @brief SPI2 Reset Position @def RCC_APB1RSTR_SPI2RST_Pos */
#define RCC_APB1RSTR_SPI2RST_Pos						((uint8_t) 14U)
/** @brief SPI2 Reset Mask @def RCC_APB1RSTR_SPI2RST_Msk */
#define RCC_APB1RSTR_SPI2RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_SPI2RST_Pos))
/** @brief SPI2 Reset @def RCC_APB1RSTR_SPI2RST */
#define RCC_APB1RSTR_SPI2RST							RCC_APB1RSTR_SPI2RST_Msk

/** @brief SPI3 Reset Position @def RCC_APB1RSTR_SPI3RST_Pos */
#define RCC_APB1RSTR_SPI3RST_Pos						((uint8_t) 15U)
/** @brief SPI3 Reset Mask @def RCC_APB1RSTR_SPI3RST_Msk */
#define RCC_APB1RSTR_SPI3RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_SPI3RST_Pos))
/** @brief SPI3 Reset @def RCC_APB1RSTR_SPI3RST */
#define RCC_APB1RSTR_SPI3RST							RCC_APB1RSTR_SPI3RST_Msk

/** @brief USART2 Reset Position @def RCC_APB1RSTR_USART2RST_Pos */
#define RCC_APB1RSTR_USART2RST_Pos						((uint8_t) 17U)
/** @brief USART2 Reset Mask @def RCC_APB1RSTR_USART2RST_Msk */
#define RCC_APB1RSTR_USART2RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_USART2RST_Pos))
/** @brief USART2 Reset @def RCC_APB1RSTR_USART2RST */
#define RCC_APB1RSTR_USART2RST							RCC_APB1RSTR_USART2RST_Msk

/** @brief USART3 Reset Position @def RCC_APB1RSTR_USART3RST_Pos */
#define RCC_APB1RSTR_USART3RST_Pos						((uint8_t) 18U)
/** @brief USART3 Reset Mask @def RCC_APB1RSTR_USART3RST_Msk */
#define RCC_APB1RSTR_USART3RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_USART3RST_Pos))
/** @brief USART3 Reset @def RCC_APB1RSTR_USART3RST */
#define RCC_APB1RSTR_USART3RST							RCC_APB1RSTR_USART3RST_Msk

/** @brief UART4 Reset Position @def RCC_APB1RSTR_UART4RST_Pos */
#define RCC_APB1RSTR_UART4RST_Pos						((uint8_t) 19U)
/** @brief UART4 Reset Mask @def RCC_APB1RSTR_UART4RST_Msk */
#define RCC_APB1RSTR_UART4RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_UART4RST_Pos))
/** @brief UART4 Reset @def RCC_APB1RSTR_UART4RST */
#define RCC_APB1RSTR_UART4RST							RCC_APB1RSTR_UART4RST_Msk

/** @brief UART5 Reset Position @def RCC_APB1RSTR_UART5RST_Pos */
#define RCC_APB1RSTR_UART5RST_Pos						((uint8_t) 20U)
/** @brief UART5 Reset Mask @def RCC_APB1RSTR_UART5RST_Msk */
#define RCC_APB1RSTR_UART5RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_UART5RST_Pos))
/** @brief UART5 Reset @def RCC_APB1RSTR_UART5RST */
#define RCC_APB1RSTR_UART5RST							RCC_APB1RSTR_UART5RST_Msk

/** @brief I2C1 Reset Position @def RCC_APB1RSTR_I2C1RST_Pos */
#define RCC_APB1RSTR_I2C1RST_Pos						((uint8_t) 21U)
/** @brief I2C1 Reset Mask @def RCC_APB1RSTR_I2C1RST_Msk */
#define RCC_APB1RSTR_I2C1RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_I2C1RST_Pos))
/** @brief I2C1 Reset @def RCC_APB1RSTR_I2C1RST */
#define RCC_APB1RSTR_I2C1RST							RCC_APB1RSTR_I2C1RST_Msk

/** @brief I2C2 Reset Position @def RCC_APB1RSTR_I2C2RST_Pos */
#define RCC_APB1RSTR_I2C2RST_Pos						((uint8_t) 22U)
/** @brief I2C2 Reset Mask @def RCC_APB1RSTR_I2C2RST_Msk */
#define RCC_APB1RSTR_I2C2RST_Msk						(BIT_VALUE(0x01UL, RCC_APB1RSTR_I2C2RST_Pos))
/** @brief I2C2 Reset @def RCC_APB1RSTR_I2C2RST */
#define RCC_APB1RSTR_I2C2RST							RCC_APB1RSTR_I2C2RST_Msk

/** @brief USB Reset Position @def RCC_APB1RSTR_USBRST_Pos */
#define RCC_APB1RSTR_USBRST_Pos							((uint8_t) 23U)
/** @brief USB Reset Mask @def RCC_APB1RSTR_USBRST_Msk */
#define RCC_APB1RSTR_USBRST_Msk							(BIT_VALUE(0x01UL, RCC_APB1RSTR_USBRST_Pos))
/** @brief USB Reset @def RCC_APB1RSTR_USBRST */
#define RCC_APB1RSTR_USBRST								RCC_APB1RSTR_USBRST_Msk

/** @brief CAN Reset Position @def RCC_APB1RSTR_CANRST_Pos */
#define RCC_APB1RSTR_CANRST_Pos							((uint8_t) 25U)
/** @brief CAN Reset Mask @def RCC_APB1RSTR_CANRST_Msk */
#define RCC_APB1RSTR_CANRST_Msk							(BIT_VALUE(0x01UL, RCC_APB1RSTR_CANRST_Pos))
/** @brief CAN Reset @def RCC_APB1RSTR_CANRST */
#define RCC_APB1RSTR_CANRST								RCC_APB1RSTR_CANRST_Msk

/** @brief BKP Reset Position @def RCC_APB1RSTR_BKPRST_Pos */
#define RCC_APB1RSTR_BKPRST_Pos							((uint8_t) 27U)
/** @brief BKP Reset Mask @def RCC_APB1RSTR_BKPRST_Msk */
#define RCC_APB1RSTR_BKPRST_Msk							(BIT_VALUE(0x01UL, RCC_APB1RSTR_BKPRST_Pos))
/** @brief BKP Reset @def RCC_APB1RSTR_BKPRST */
#define RCC_APB1RSTR_BKPRST								RCC_APB1RSTR_BKPRST_Msk

/** @brief PWR Reset Position @def RCC_APB1RSTR_PWRRST_Pos */
#define RCC_APB1RSTR_PWRRST_Pos							((uint8_t) 28U)
/** @brief PWR Reset Mask @def RCC_APB1RSTR_PWRRST_Msk */
#define RCC_APB1RSTR_PWRRST_Msk							(BIT_VALUE(0x01UL, RCC_APB1RSTR_PWRRST_Pos))
/** @brief PWR Reset @def RCC_APB1RSTR_PWRRST */
#define RCC_APB1RSTR_PWRRST								RCC_APB1RSTR_PWRRST_Msk

/** @brief DAC Reset Position @def RCC_APB1RSTR_DACRST_Pos */
#define RCC_APB1RSTR_DACRST_Pos							((uint8_t) 29U)
/** @brief DAC Reset Mask @def RCC_APB1RSTR_DACRST_Msk */
#define RCC_APB1RSTR_DACRST_Msk							(BIT_VALUE(0x01UL, RCC_APB1RSTR_DACRST_Pos))
/** @brief DAC Reset @def RCC_APB1RSTR_DACRST */
#define RCC_APB1RSTR_DACRST								RCC_APB1RSTR_DACRST_Msk

/** @} */ // RCC_01_RegisterLayer_04_PeripheralReset

/**
 * @brief RCC Peripheral Clock Enable Register Definitions
 * @defgroup RCC_01_RegisterLayer_05_PeripheralClockEnable RCC Peripheral Clock Enable Registers
 * @ingroup RCC_01_RegisterLayer
 * @details
 * @section RCC_ENR_Theory Theory and Practical Role
 * This page documents the explicit clock-gate masks used by the RCC software stack.
 * These definitions cover `RCC_AHBENR`, `RCC_APB2ENR`, and `RCC_APB1ENR` so LL and
 * driver layers can enable or disable peripheral clocks through raw hardware masks.
 *
 * @section RCC_ENR_Macros Register-Specific Macros
 * The macro definitions below describe the AHB, APB2, and APB1 peripheral clock-enable
 * bits that can be asserted or cleared through RCC gate control.
 *
 * @section RCC_ENR_Union Register Union View
 * The register map later in this file exposes `union RCC_AHBENR`, `union RCC_APB2ENR`,
 * and `union RCC_APB1ENR` so the documented masks line up with the final memory layout.
 * @{
 */

// ------------------------------------------------------------------------------------------
// RCC_AHBENR (AHB Peripheral Clock Enable Register)
// ------------------------------------------------------------------------------------------

/** @brief DMA1 Clock Enable Position @def RCC_AHBENR_DMA1EN_Pos */
#define RCC_AHBENR_DMA1EN_Pos							((uint8_t) 0U)
/** @brief DMA1 Clock Enable Mask @def RCC_AHBENR_DMA1EN_Msk */
#define RCC_AHBENR_DMA1EN_Msk							(BIT_VALUE(0x01UL, RCC_AHBENR_DMA1EN_Pos))
/** @brief DMA1 Clock Enable @def RCC_AHBENR_DMA1EN */
#define RCC_AHBENR_DMA1EN								RCC_AHBENR_DMA1EN_Msk

/** @brief DMA2 Clock Enable Position @def RCC_AHBENR_DMA2EN_Pos */
#define RCC_AHBENR_DMA2EN_Pos							((uint8_t) 1U)
/** @brief DMA2 Clock Enable Mask @def RCC_AHBENR_DMA2EN_Msk */
#define RCC_AHBENR_DMA2EN_Msk							(BIT_VALUE(0x01UL, RCC_AHBENR_DMA2EN_Pos))
/** @brief DMA2 Clock Enable @def RCC_AHBENR_DMA2EN */
#define RCC_AHBENR_DMA2EN								RCC_AHBENR_DMA2EN_Msk

/** @brief SRAM Clock Enable Position @def RCC_AHBENR_SRAMEN_Pos */
#define RCC_AHBENR_SRAMEN_Pos							((uint8_t) 2U)
/** @brief SRAM Clock Enable Mask @def RCC_AHBENR_SRAMEN_Msk */
#define RCC_AHBENR_SRAMEN_Msk							(BIT_VALUE(0x01UL, RCC_AHBENR_SRAMEN_Pos))
/** @brief SRAM Clock Enable @def RCC_AHBENR_SRAMEN */
#define RCC_AHBENR_SRAMEN								RCC_AHBENR_SRAMEN_Msk

/** @brief FLITF Clock Enable Position @def RCC_AHBENR_FLITFEN_Pos */
#define RCC_AHBENR_FLITFEN_Pos							((uint8_t) 4U)
/** @brief FLITF Clock Enable Mask @def RCC_AHBENR_FLITFEN_Msk */
#define RCC_AHBENR_FLITFEN_Msk							(BIT_VALUE(0x01UL, RCC_AHBENR_FLITFEN_Pos))
/** @brief FLITF Clock Enable @def RCC_AHBENR_FLITFEN */
#define RCC_AHBENR_FLITFEN								RCC_AHBENR_FLITFEN_Msk

/** @brief CRC Clock Enable Position @def RCC_AHBENR_CRCEN_Pos */
#define RCC_AHBENR_CRCEN_Pos							((uint8_t) 6U)
/** @brief CRC Clock Enable Mask @def RCC_AHBENR_CRCEN_Msk */
#define RCC_AHBENR_CRCEN_Msk							(BIT_VALUE(0x01UL, RCC_AHBENR_CRCEN_Pos))
/** @brief CRC Clock Enable @def RCC_AHBENR_CRCEN */
#define RCC_AHBENR_CRCEN								RCC_AHBENR_CRCEN_Msk

/** @brief FSMC Clock Enable Position @def RCC_AHBENR_FSMCEN_Pos */
#define RCC_AHBENR_FSMCEN_Pos							((uint8_t) 8U)
/** @brief FSMC Clock Enable Mask @def RCC_AHBENR_FSMCEN_Msk */
#define RCC_AHBENR_FSMCEN_Msk							(BIT_VALUE(0x01UL, RCC_AHBENR_FSMCEN_Pos))
/** @brief FSMC Clock Enable @def RCC_AHBENR_FSMCEN */
#define RCC_AHBENR_FSMCEN								RCC_AHBENR_FSMCEN_Msk

/** @brief SDIO Clock Enable Position @def RCC_AHBENR_SDIOEN_Pos */
#define RCC_AHBENR_SDIOEN_Pos							((uint8_t) 10U)
/** @brief SDIO Clock Enable Mask @def RCC_AHBENR_SDIOEN_Msk */
#define RCC_AHBENR_SDIOEN_Msk							(BIT_VALUE(0x01UL, RCC_AHBENR_SDIOEN_Pos))
/** @brief SDIO Clock Enable @def RCC_AHBENR_SDIOEN */
#define RCC_AHBENR_SDIOEN								RCC_AHBENR_SDIOEN_Msk

// ------------------------------------------------------------------------------------------
// RCC_APB2ENR (APB2 Peripheral Clock Enable Register)
// ------------------------------------------------------------------------------------------

/** @brief AFIO Clock Enable Position @def RCC_APB2ENR_AFIOEN_Pos */
#define RCC_APB2ENR_AFIOEN_Pos							((uint8_t) 0U)
/** @brief AFIO Clock Enable Mask @def RCC_APB2ENR_AFIOEN_Msk */
#define RCC_APB2ENR_AFIOEN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_AFIOEN_Pos))
/** @brief AFIO Clock Enable @def RCC_APB2ENR_AFIOEN */
#define RCC_APB2ENR_AFIOEN								RCC_APB2ENR_AFIOEN_Msk

/** @brief GPIOA Clock Enable Position @def RCC_APB2ENR_IOPAEN_Pos */
#define RCC_APB2ENR_IOPAEN_Pos							((uint8_t) 2U)
/** @brief GPIOA Clock Enable Mask @def RCC_APB2ENR_IOPAEN_Msk */
#define RCC_APB2ENR_IOPAEN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_IOPAEN_Pos))
/** @brief GPIOA Clock Enable @def RCC_APB2ENR_IOPAEN */
#define RCC_APB2ENR_IOPAEN								RCC_APB2ENR_IOPAEN_Msk

/** @brief GPIOB Clock Enable Position @def RCC_APB2ENR_IOPBEN_Pos */
#define RCC_APB2ENR_IOPBEN_Pos							((uint8_t) 3U)
/** @brief GPIOB Clock Enable Mask @def RCC_APB2ENR_IOPBEN_Msk */
#define RCC_APB2ENR_IOPBEN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_IOPBEN_Pos))
/** @brief GPIOB Clock Enable @def RCC_APB2ENR_IOPBEN */
#define RCC_APB2ENR_IOPBEN								RCC_APB2ENR_IOPBEN_Msk

/** @brief GPIOC Clock Enable Position @def RCC_APB2ENR_IOPCEN_Pos */
#define RCC_APB2ENR_IOPCEN_Pos							((uint8_t) 4U)
/** @brief GPIOC Clock Enable Mask @def RCC_APB2ENR_IOPCEN_Msk */
#define RCC_APB2ENR_IOPCEN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_IOPCEN_Pos))
/** @brief GPIOC Clock Enable @def RCC_APB2ENR_IOPCEN */
#define RCC_APB2ENR_IOPCEN								RCC_APB2ENR_IOPCEN_Msk

/** @brief GPIOD Clock Enable Position @def RCC_APB2ENR_IOPDEN_Pos */
#define RCC_APB2ENR_IOPDEN_Pos							((uint8_t) 5U)
/** @brief GPIOD Clock Enable Mask @def RCC_APB2ENR_IOPDEN_Msk */
#define RCC_APB2ENR_IOPDEN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_IOPDEN_Pos))
/** @brief GPIOD Clock Enable @def RCC_APB2ENR_IOPDEN */
#define RCC_APB2ENR_IOPDEN								RCC_APB2ENR_IOPDEN_Msk

/** @brief GPIOE Clock Enable Position @def RCC_APB2ENR_IOPEEN_Pos */
#define RCC_APB2ENR_IOPEEN_Pos							((uint8_t) 6U)
/** @brief GPIOE Clock Enable Mask @def RCC_APB2ENR_IOPEEN_Msk */
#define RCC_APB2ENR_IOPEEN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_IOPEEN_Pos))
/** @brief GPIOE Clock Enable @def RCC_APB2ENR_IOPEEN */
#define RCC_APB2ENR_IOPEEN								RCC_APB2ENR_IOPEEN_Msk

/** @brief GPIOF Clock Enable Position @def RCC_APB2ENR_IOPFEN_Pos */
#define RCC_APB2ENR_IOPFEN_Pos							((uint8_t) 7U)
/** @brief GPIOF Clock Enable Mask @def RCC_APB2ENR_IOPFEN_Msk */
#define RCC_APB2ENR_IOPFEN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_IOPFEN_Pos))
/** @brief GPIOF Clock Enable @def RCC_APB2ENR_IOPFEN */
#define RCC_APB2ENR_IOPFEN								RCC_APB2ENR_IOPFEN_Msk

/** @brief GPIOG Clock Enable Position @def RCC_APB2ENR_IOPGEN_Pos */
#define RCC_APB2ENR_IOPGEN_Pos							((uint8_t) 8U)
/** @brief GPIOG Clock Enable Mask @def RCC_APB2ENR_IOPGEN_Msk */
#define RCC_APB2ENR_IOPGEN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_IOPGEN_Pos))
/** @brief GPIOG Clock Enable @def RCC_APB2ENR_IOPGEN */
#define RCC_APB2ENR_IOPGEN								RCC_APB2ENR_IOPGEN_Msk

/** @brief ADC1 Clock Enable Position @def RCC_APB2ENR_ADC1EN_Pos */
#define RCC_APB2ENR_ADC1EN_Pos							((uint8_t) 9U)
/** @brief ADC1 Clock Enable Mask @def RCC_APB2ENR_ADC1EN_Msk */
#define RCC_APB2ENR_ADC1EN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_ADC1EN_Pos))
/** @brief ADC1 Clock Enable @def RCC_APB2ENR_ADC1EN */
#define RCC_APB2ENR_ADC1EN								RCC_APB2ENR_ADC1EN_Msk

/** @brief ADC2 Clock Enable Position @def RCC_APB2ENR_ADC2EN_Pos */
#define RCC_APB2ENR_ADC2EN_Pos							((uint8_t) 10U)
/** @brief ADC2 Clock Enable Mask @def RCC_APB2ENR_ADC2EN_Msk */
#define RCC_APB2ENR_ADC2EN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_ADC2EN_Pos))
/** @brief ADC2 Clock Enable @def RCC_APB2ENR_ADC2EN */
#define RCC_APB2ENR_ADC2EN								RCC_APB2ENR_ADC2EN_Msk

/** @brief TIM1 Clock Enable Position @def RCC_APB2ENR_TIM1EN_Pos */
#define RCC_APB2ENR_TIM1EN_Pos							((uint8_t) 11U)
/** @brief TIM1 Clock Enable Mask @def RCC_APB2ENR_TIM1EN_Msk */
#define RCC_APB2ENR_TIM1EN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_TIM1EN_Pos))
/** @brief TIM1 Clock Enable @def RCC_APB2ENR_TIM1EN */
#define RCC_APB2ENR_TIM1EN								RCC_APB2ENR_TIM1EN_Msk

/** @brief SPI1 Clock Enable Position @def RCC_APB2ENR_SPI1EN_Pos */
#define RCC_APB2ENR_SPI1EN_Pos							((uint8_t) 12U)
/** @brief SPI1 Clock Enable Mask @def RCC_APB2ENR_SPI1EN_Msk */
#define RCC_APB2ENR_SPI1EN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_SPI1EN_Pos))
/** @brief SPI1 Clock Enable @def RCC_APB2ENR_SPI1EN */
#define RCC_APB2ENR_SPI1EN								RCC_APB2ENR_SPI1EN_Msk

/** @brief TIM8 Clock Enable Position @def RCC_APB2ENR_TIM8EN_Pos */
#define RCC_APB2ENR_TIM8EN_Pos							((uint8_t) 13U)
/** @brief TIM8 Clock Enable Mask @def RCC_APB2ENR_TIM8EN_Msk */
#define RCC_APB2ENR_TIM8EN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_TIM8EN_Pos))
/** @brief TIM8 Clock Enable @def RCC_APB2ENR_TIM8EN */
#define RCC_APB2ENR_TIM8EN								RCC_APB2ENR_TIM8EN_Msk

/** @brief USART1 Clock Enable Position @def RCC_APB2ENR_USART1EN_Pos */
#define RCC_APB2ENR_USART1EN_Pos						((uint8_t) 14U)
/** @brief USART1 Clock Enable Mask @def RCC_APB2ENR_USART1EN_Msk */
#define RCC_APB2ENR_USART1EN_Msk						(BIT_VALUE(0x01UL, RCC_APB2ENR_USART1EN_Pos))
/** @brief USART1 Clock Enable @def RCC_APB2ENR_USART1EN */
#define RCC_APB2ENR_USART1EN							RCC_APB2ENR_USART1EN_Msk

/** @brief ADC3 Clock Enable Position @def RCC_APB2ENR_ADC3EN_Pos */
#define RCC_APB2ENR_ADC3EN_Pos							((uint8_t) 15U)
/** @brief ADC3 Clock Enable Mask @def RCC_APB2ENR_ADC3EN_Msk */
#define RCC_APB2ENR_ADC3EN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_ADC3EN_Pos))
/** @brief ADC3 Clock Enable @def RCC_APB2ENR_ADC3EN */
#define RCC_APB2ENR_ADC3EN								RCC_APB2ENR_ADC3EN_Msk

/** @brief TIM9 Clock Enable Position @def RCC_APB2ENR_TIM9EN_Pos */
#define RCC_APB2ENR_TIM9EN_Pos							((uint8_t) 19U)
/** @brief TIM9 Clock Enable Mask @def RCC_APB2ENR_TIM9EN_Msk */
#define RCC_APB2ENR_TIM9EN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_TIM9EN_Pos))
/** @brief TIM9 Clock Enable @def RCC_APB2ENR_TIM9EN */
#define RCC_APB2ENR_TIM9EN								RCC_APB2ENR_TIM9EN_Msk

/** @brief TIM10 Clock Enable Position @def RCC_APB2ENR_TIM10EN_Pos */
#define RCC_APB2ENR_TIM10EN_Pos							((uint8_t) 20U)
/** @brief TIM10 Clock Enable Mask @def RCC_APB2ENR_TIM10EN_Msk */
#define RCC_APB2ENR_TIM10EN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_TIM10EN_Pos))
/** @brief TIM10 Clock Enable @def RCC_APB2ENR_TIM10EN */
#define RCC_APB2ENR_TIM10EN								RCC_APB2ENR_TIM10EN_Msk

/** @brief TIM11 Clock Enable Position @def RCC_APB2ENR_TIM11EN_Pos */
#define RCC_APB2ENR_TIM11EN_Pos							((uint8_t) 21U)
/** @brief TIM11 Clock Enable Mask @def RCC_APB2ENR_TIM11EN_Msk */
#define RCC_APB2ENR_TIM11EN_Msk							(BIT_VALUE(0x01UL, RCC_APB2ENR_TIM11EN_Pos))
/** @brief TIM11 Clock Enable @def RCC_APB2ENR_TIM11EN */
#define RCC_APB2ENR_TIM11EN								RCC_APB2ENR_TIM11EN_Msk

// ------------------------------------------------------------------------------------------
// RCC_APB1ENR (APB1 Peripheral Clock Enable Register)
// ------------------------------------------------------------------------------------------

/** @brief TIM2 Clock Enable Position @def RCC_APB1ENR_TIM2EN_Pos */
#define RCC_APB1ENR_TIM2EN_Pos							((uint8_t) 0U)
/** @brief TIM2 Clock Enable Mask @def RCC_APB1ENR_TIM2EN_Msk */
#define RCC_APB1ENR_TIM2EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_TIM2EN_Pos))
/** @brief TIM2 Clock Enable @def RCC_APB1ENR_TIM2EN */
#define RCC_APB1ENR_TIM2EN								RCC_APB1ENR_TIM2EN_Msk

/** @brief TIM3 Clock Enable Position @def RCC_APB1ENR_TIM3EN_Pos */
#define RCC_APB1ENR_TIM3EN_Pos							((uint8_t) 1U)
/** @brief TIM3 Clock Enable Mask @def RCC_APB1ENR_TIM3EN_Msk */
#define RCC_APB1ENR_TIM3EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_TIM3EN_Pos))
/** @brief TIM3 Clock Enable @def RCC_APB1ENR_TIM3EN */
#define RCC_APB1ENR_TIM3EN								RCC_APB1ENR_TIM3EN_Msk

/** @brief TIM4 Clock Enable Position @def RCC_APB1ENR_TIM4EN_Pos */
#define RCC_APB1ENR_TIM4EN_Pos							((uint8_t) 2U)
/** @brief TIM4 Clock Enable Mask @def RCC_APB1ENR_TIM4EN_Msk */
#define RCC_APB1ENR_TIM4EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_TIM4EN_Pos))
/** @brief TIM4 Clock Enable @def RCC_APB1ENR_TIM4EN */
#define RCC_APB1ENR_TIM4EN								RCC_APB1ENR_TIM4EN_Msk

/** @brief TIM5 Clock Enable Position @def RCC_APB1ENR_TIM5EN_Pos */
#define RCC_APB1ENR_TIM5EN_Pos							((uint8_t) 3U)
/** @brief TIM5 Clock Enable Mask @def RCC_APB1ENR_TIM5EN_Msk */
#define RCC_APB1ENR_TIM5EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_TIM5EN_Pos))
/** @brief TIM5 Clock Enable @def RCC_APB1ENR_TIM5EN */
#define RCC_APB1ENR_TIM5EN								RCC_APB1ENR_TIM5EN_Msk

/** @brief TIM6 Clock Enable Position @def RCC_APB1ENR_TIM6EN_Pos */
#define RCC_APB1ENR_TIM6EN_Pos							((uint8_t) 4U)
/** @brief TIM6 Clock Enable Mask @def RCC_APB1ENR_TIM6EN_Msk */
#define RCC_APB1ENR_TIM6EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_TIM6EN_Pos))
/** @brief TIM6 Clock Enable @def RCC_APB1ENR_TIM6EN */
#define RCC_APB1ENR_TIM6EN								RCC_APB1ENR_TIM6EN_Msk

/** @brief TIM7 Clock Enable Position @def RCC_APB1ENR_TIM7EN_Pos */
#define RCC_APB1ENR_TIM7EN_Pos							((uint8_t) 5U)
/** @brief TIM7 Clock Enable Mask @def RCC_APB1ENR_TIM7EN_Msk */
#define RCC_APB1ENR_TIM7EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_TIM7EN_Pos))
/** @brief TIM7 Clock Enable @def RCC_APB1ENR_TIM7EN */
#define RCC_APB1ENR_TIM7EN								RCC_APB1ENR_TIM7EN_Msk

/** @brief TIM12 Clock Enable Position @def RCC_APB1ENR_TIM12EN_Pos */
#define RCC_APB1ENR_TIM12EN_Pos							((uint8_t) 6U)
/** @brief TIM12 Clock Enable Mask @def RCC_APB1ENR_TIM12EN_Msk */
#define RCC_APB1ENR_TIM12EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_TIM12EN_Pos))
/** @brief TIM12 Clock Enable @def RCC_APB1ENR_TIM12EN */
#define RCC_APB1ENR_TIM12EN								RCC_APB1ENR_TIM12EN_Msk

/** @brief TIM13 Clock Enable Position @def RCC_APB1ENR_TIM13EN_Pos */
#define RCC_APB1ENR_TIM13EN_Pos							((uint8_t) 7U)
/** @brief TIM13 Clock Enable Mask @def RCC_APB1ENR_TIM13EN_Msk */
#define RCC_APB1ENR_TIM13EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_TIM13EN_Pos))
/** @brief TIM13 Clock Enable @def RCC_APB1ENR_TIM13EN */
#define RCC_APB1ENR_TIM13EN								RCC_APB1ENR_TIM13EN_Msk

/** @brief TIM14 Clock Enable Position @def RCC_APB1ENR_TIM14EN_Pos */
#define RCC_APB1ENR_TIM14EN_Pos							((uint8_t) 8U)
/** @brief TIM14 Clock Enable Mask @def RCC_APB1ENR_TIM14EN_Msk */
#define RCC_APB1ENR_TIM14EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_TIM14EN_Pos))
/** @brief TIM14 Clock Enable @def RCC_APB1ENR_TIM14EN */
#define RCC_APB1ENR_TIM14EN								RCC_APB1ENR_TIM14EN_Msk

/** @brief WWDG Clock Enable Position @def RCC_APB1ENR_WWDGEN_Pos */
#define RCC_APB1ENR_WWDGEN_Pos							((uint8_t) 11U)
/** @brief WWDG Clock Enable Mask @def RCC_APB1ENR_WWDGEN_Msk */
#define RCC_APB1ENR_WWDGEN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_WWDGEN_Pos))
/** @brief WWDG Clock Enable @def RCC_APB1ENR_WWDGEN */
#define RCC_APB1ENR_WWDGEN								RCC_APB1ENR_WWDGEN_Msk

/** @brief SPI2 Clock Enable Position @def RCC_APB1ENR_SPI2EN_Pos */
#define RCC_APB1ENR_SPI2EN_Pos							((uint8_t) 14U)
/** @brief SPI2 Clock Enable Mask @def RCC_APB1ENR_SPI2EN_Msk */
#define RCC_APB1ENR_SPI2EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_SPI2EN_Pos))
/** @brief SPI2 Clock Enable @def RCC_APB1ENR_SPI2EN */
#define RCC_APB1ENR_SPI2EN								RCC_APB1ENR_SPI2EN_Msk

/** @brief SPI3 Clock Enable Position @def RCC_APB1ENR_SPI3EN_Pos */
#define RCC_APB1ENR_SPI3EN_Pos							((uint8_t) 15U)
/** @brief SPI3 Clock Enable Mask @def RCC_APB1ENR_SPI3EN_Msk */
#define RCC_APB1ENR_SPI3EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_SPI3EN_Pos))
/** @brief SPI3 Clock Enable @def RCC_APB1ENR_SPI3EN */
#define RCC_APB1ENR_SPI3EN								RCC_APB1ENR_SPI3EN_Msk

/** @brief USART2 Clock Enable Position @def RCC_APB1ENR_USART2EN_Pos */
#define RCC_APB1ENR_USART2EN_Pos						((uint8_t) 17U)
/** @brief USART2 Clock Enable Mask @def RCC_APB1ENR_USART2EN_Msk */
#define RCC_APB1ENR_USART2EN_Msk						(BIT_VALUE(0x01UL, RCC_APB1ENR_USART2EN_Pos))
/** @brief USART2 Clock Enable @def RCC_APB1ENR_USART2EN */
#define RCC_APB1ENR_USART2EN							RCC_APB1ENR_USART2EN_Msk

/** @brief USART3 Clock Enable Position @def RCC_APB1ENR_USART3EN_Pos */
#define RCC_APB1ENR_USART3EN_Pos						((uint8_t) 18U)
/** @brief USART3 Clock Enable Mask @def RCC_APB1ENR_USART3EN_Msk */
#define RCC_APB1ENR_USART3EN_Msk						(BIT_VALUE(0x01UL, RCC_APB1ENR_USART3EN_Pos))
/** @brief USART3 Clock Enable @def RCC_APB1ENR_USART3EN */
#define RCC_APB1ENR_USART3EN							RCC_APB1ENR_USART3EN_Msk

/** @brief UART4 Clock Enable Position @def RCC_APB1ENR_UART4EN_Pos */
#define RCC_APB1ENR_UART4EN_Pos							((uint8_t) 19U)
/** @brief UART4 Clock Enable Mask @def RCC_APB1ENR_UART4EN_Msk */
#define RCC_APB1ENR_UART4EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_UART4EN_Pos))
/** @brief UART4 Clock Enable @def RCC_APB1ENR_UART4EN */
#define RCC_APB1ENR_UART4EN								RCC_APB1ENR_UART4EN_Msk

/** @brief UART5 Clock Enable Position @def RCC_APB1ENR_UART5EN_Pos */
#define RCC_APB1ENR_UART5EN_Pos							((uint8_t) 20U)
/** @brief UART5 Clock Enable Mask @def RCC_APB1ENR_UART5EN_Msk */
#define RCC_APB1ENR_UART5EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_UART5EN_Pos))
/** @brief UART5 Clock Enable @def RCC_APB1ENR_UART5EN */
#define RCC_APB1ENR_UART5EN								RCC_APB1ENR_UART5EN_Msk

/** @brief I2C1 Clock Enable Position @def RCC_APB1ENR_I2C1EN_Pos */
#define RCC_APB1ENR_I2C1EN_Pos							((uint8_t) 21U)
/** @brief I2C1 Clock Enable Mask @def RCC_APB1ENR_I2C1EN_Msk */
#define RCC_APB1ENR_I2C1EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_I2C1EN_Pos))
/** @brief I2C1 Clock Enable @def RCC_APB1ENR_I2C1EN */
#define RCC_APB1ENR_I2C1EN								RCC_APB1ENR_I2C1EN_Msk

/** @brief I2C2 Clock Enable Position @def RCC_APB1ENR_I2C2EN_Pos */
#define RCC_APB1ENR_I2C2EN_Pos							((uint8_t) 22U)
/** @brief I2C2 Clock Enable Mask @def RCC_APB1ENR_I2C2EN_Msk */
#define RCC_APB1ENR_I2C2EN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_I2C2EN_Pos))
/** @brief I2C2 Clock Enable @def RCC_APB1ENR_I2C2EN */
#define RCC_APB1ENR_I2C2EN								RCC_APB1ENR_I2C2EN_Msk

/** @brief USB Clock Enable Position @def RCC_APB1ENR_USBEN_Pos */
#define RCC_APB1ENR_USBEN_Pos							((uint8_t) 23U)
/** @brief USB Clock Enable Mask @def RCC_APB1ENR_USBEN_Msk */
#define RCC_APB1ENR_USBEN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_USBEN_Pos))
/** @brief USB Clock Enable @def RCC_APB1ENR_USBEN */
#define RCC_APB1ENR_USBEN								RCC_APB1ENR_USBEN_Msk

/** @brief CAN Clock Enable Position @def RCC_APB1ENR_CANEN_Pos */
#define RCC_APB1ENR_CANEN_Pos							((uint8_t) 25U)
/** @brief CAN Clock Enable Mask @def RCC_APB1ENR_CANEN_Msk */
#define RCC_APB1ENR_CANEN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_CANEN_Pos))
/** @brief CAN Clock Enable @def RCC_APB1ENR_CANEN */
#define RCC_APB1ENR_CANEN								RCC_APB1ENR_CANEN_Msk

/** @brief BKP Clock Enable Position @def RCC_APB1ENR_BKPEN_Pos */
#define RCC_APB1ENR_BKPEN_Pos							((uint8_t) 27U)
/** @brief BKP Clock Enable Mask @def RCC_APB1ENR_BKPEN_Msk */
#define RCC_APB1ENR_BKPEN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_BKPEN_Pos))
/** @brief BKP Clock Enable @def RCC_APB1ENR_BKPEN */
#define RCC_APB1ENR_BKPEN								RCC_APB1ENR_BKPEN_Msk

/** @brief PWR Clock Enable Position @def RCC_APB1ENR_PWREN_Pos */
#define RCC_APB1ENR_PWREN_Pos							((uint8_t) 28U)
/** @brief PWR Clock Enable Mask @def RCC_APB1ENR_PWREN_Msk */
#define RCC_APB1ENR_PWREN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_PWREN_Pos))
/** @brief PWR Clock Enable @def RCC_APB1ENR_PWREN */
#define RCC_APB1ENR_PWREN								RCC_APB1ENR_PWREN_Msk

/** @brief DAC Clock Enable Position @def RCC_APB1ENR_DACEN_Pos */
#define RCC_APB1ENR_DACEN_Pos							((uint8_t) 29U)
/** @brief DAC Clock Enable Mask @def RCC_APB1ENR_DACEN_Msk */
#define RCC_APB1ENR_DACEN_Msk							(BIT_VALUE(0x01UL, RCC_APB1ENR_DACEN_Pos))
/** @brief DAC Clock Enable @def RCC_APB1ENR_DACEN */
#define RCC_APB1ENR_DACEN								RCC_APB1ENR_DACEN_Msk

/** @} */ // RCC_01_RegisterLayer_05_PeripheralClockEnable

// ------------------------------------------------------------------------------------------
// RCC Structure
// ------------------------------------------------------------------------------------------ 

/**
 * @defgroup RCC_01_RegisterLayer_06_RegisterMap RCC Register Block Map
 * @ingroup RCC_01_RegisterLayer
 * @brief Memory-mapped RCC register block and practical register layout
 * @details
 * @section RCC_RegisterMap_Theory Theory and Practical Role
 * This page ties the theory pages above to the actual software representation used in
 * the project. `RCC_TypeDef` is the concrete register map consumed by the LL layer.
 *
 * Practical role in this codebase:
 * - the register layer defines the layout,
 * - the LL layer accesses `.REG` and bitfield views from this structure,
 * - the driver layer never edits fields directly and instead uses LL services.
 *
 * @section RCC_RegisterMap_Structure RCC Register Block Structure
 * The structure below is the final memory-mapped layout. Use it when you want to see the
 * complete RCC map exactly as the software stack accesses it at runtime.
 * @{
 */

/**
 * @brief RCC Register Block Structure
 * @details
 * This structure represents the complete memory-mapped RCC peripheral.
 *
 * @see RM0008 Section 7.3 RCC registers
 * @typedef RCC_TypeDef
 */
typedef volatile struct _RCC_TypeDef
{
	/**
	 * @ingroup RCC_01_RegisterLayer_01_ClockControl RCC_01_RegisterLayer_06_RegisterMap
	 * @brief Clock Control Register
	 * @details
	 * Controls the internal and external clock sources including HSI, HSE, and PLL.
	 * Manages oscillator enable/disable, ready status, calibration, and clock security system.
	 * This register must be configured before any clock switching operations.
	 */
	union RCC_CR
	{
		// Full 32-bit Register Access
		_IO REG;
		// Bit Access
		struct
		{
			_IO HSION: 1;
			_I HSIRDY: 1;
			_I reserved_1: 1;
			_IO HSITRIM: 5;
			_I HSICAL: 8;
			_IO HSEON: 1;
			_I HSERDY: 1;
			_IO HSEBYP: 1;
			_IO CSSON: 1;
			_I reserved_2: 4;
			_IO PLLON: 1;
			_I PLLRDY: 1;
			_I reserved_3: 6;
		} BIT;
	} CR;

	/**
	 * @ingroup RCC_01_RegisterLayer_02_ClockConfiguration RCC_01_RegisterLayer_06_RegisterMap
	 * @brief Clock Configuration Register  
	 * @details
	 * Configures the system clock source, prescalers for AHB, APB1, APB2 buses,
	 * PLL multiplication factor, and clock output selection. This register determines
	 * the final system clock frequency and peripheral clock speeds.
	 */
	union RCC_CFGR 
	{
		// Full 32-bit Register Access
		_IO REG;
		// Bit Access
		struct
		{
			_IO SW: 2;
			_IO SWS: 2;
			_IO HPRE: 4;
			_IO PPRE1: 3;
			_IO PPRE2: 3;
			_IO ADCPRE: 2;
			_IO PLLSRC: 1;
			_IO PLLXTPRE: 1;
			_IO PLLMUL: 4;
			_IO USBPRE: 1;
			_IO reserved_1: 1;
			_IO MCO: 3;
			_IO reserved_2: 5;
		} BIT;
	} CFGR;

	/**
	 * @ingroup RCC_01_RegisterLayer_03_ClockInterrupt RCC_01_RegisterLayer_06_RegisterMap
	 * @brief Clock Interrupt Register
	 * @details
	 * Manages interrupt flags and enable bits for various clock events including
	 * oscillator ready flags, PLL lock, and clock security system interrupts.
	 * Provides clear bits to reset interrupt flags.
	 */
	union RCC_CIR 
	{
		// Full 32-bit Register Access
		_IO REG;
		// Bit Access
		struct
		{
			_IO LSIRDYF: 1;
			_IO LSERDYF: 1;
			_IO HSIRDYF: 1;
			_IO HSERDYF: 1;
			_IO PLLRDYF: 1;
			_IO reserved_1: 2;
			_IO CSFF: 1;
			_IO LSIRDYIE: 1;
			_IO LSERDYIE: 1;
			_IO HSIRDYIE: 1;
			_IO HSERDYIE: 1;
			_IO PLLRDYIE: 1;
			_IO reserved_2: 3;
			_IO LSIRDYC: 1;
			_IO LSERDYC: 1;
			_IO HSIRDYC: 1;
			_IO HSERDYC: 1;
			_IO PLLRDYC: 1;
			_IO reserved_3: 2;
			_IO CSSC: 1;
			_IO reserved_4: 8;
		} BIT;
	} CIR;

	/**
	 * @ingroup RCC_01_RegisterLayer_04_PeripheralReset RCC_01_RegisterLayer_06_RegisterMap
	 * @brief APB2 Peripheral Reset Register
	 * @details
	 * Controls the reset functionality for peripherals connected to APB2 bus.
	 * Writing 1 to any bit asserts reset for the corresponding peripheral,
	 * writing 0 releases reset. Includes GPIO ports, ADC, TIM1, SPI1, USART1.
	 */
	union RCC_APB2RSTR 
	{
		// Full 32-bit Register Access
		_IO REG;
		// Bit Access
		struct
		{
			_IO AFIORST: 1;
			_IO reserved_1: 1;
			_IO IOPARST: 1;
			_IO IOPBRST: 1;
			_IO IOPCRST: 1;
			_IO IOPDRST: 1;
			_IO IOPERST: 1;
			_IO IOPFRST: 1;
			_IO IOPGRST: 1;
			_IO ADC1RST: 1;
			_IO ADC2RST: 1;
			_IO TIM1RST: 1;
			_IO SPI1RST: 1;
			_IO TIM8RST: 1;
			_IO USART1RST: 1;
			_IO ADC3RST: 1;
			_IO reserved_2: 3;
			_IO TIM9RST: 1;
			_IO TIM10RST: 1;
			_IO TIM11RST: 1;
			_IO reserved_3: 10;
		} BIT;
	} APB2RSTR;

	/**
	 * @ingroup RCC_01_RegisterLayer_04_PeripheralReset RCC_01_RegisterLayer_06_RegisterMap
	 * @brief APB1 Peripheral Reset Register
	 * @details
	 * Controls the reset functionality for peripherals connected to APB1 bus.
	 * Writing 1 to any bit asserts reset for the corresponding peripheral,
	 * writing 0 releases reset. Includes timers, watchdogs, SPI, USART, I2C, USB, CAN.
	 */
	union RCC_APB1RSTR
	{
		// Full 32-bit Register Access
		_IO REG;
		// Bit Access
		struct
		{
			_IO TIM2RST: 1;
			_IO TIM3RST: 1;
			_IO TIM4RST: 1;
			_IO TIM5RST: 1;
			_IO TIM6RST: 1;
			_IO TIM7RST: 1;
			_IO TIM12RST: 1;
			_IO TIM13RST: 1;
			_IO TIM14RST: 1;
			_IO reserved_1: 1;
			_IO WWDGRST: 1;
			_IO reserved_2: 2;
			_IO SPI2RST: 1;
			_IO SPI3RST: 1;
			_IO reserved_3: 1;
			_IO USART2RST: 1;
			_IO USART3RST: 1;
			_IO UART4RST: 1;
			_IO UART5RST: 1;
			_IO I2C1RST: 1;
			_IO I2C2RST: 1;
			_IO USBRST: 1;
			_IO reserved_4: 1;
			_IO CANRST: 1;
			_IO reserved_5: 1;
			_IO BKPRST: 1;
			_IO PWRRST: 1;
			_IO DACRST: 1;
			_IO reserved_6: 2;
		} BIT;
	} APB1RSTR;

	/**
	 * @ingroup RCC_01_RegisterLayer_05_PeripheralClockEnable RCC_01_RegisterLayer_06_RegisterMap
	 * @brief AHB Peripheral Clock Enable Register
	 * @details
	 * Controls clock gating for peripherals connected to AHB bus.
	 * Enables or disables clocks to DMA, SRAM, FLASH, CRC, FSMC, and SDIO peripherals.
	 * Disabling unused peripheral clocks reduces power consumption.
	 */
	union RCC_AHBENR
	{
		// Full 32-bit Register Access
		_IO REG;
		// Bit Access
		struct
		{
			_IO DMA1EN: 1;
			_IO DMA2EN: 1;
			_IO SRAMEN: 1;
			_IO reserved_1: 1;
			_IO FLITFEN: 1;
			_IO reserved_2: 1;
			_IO CRCEN: 1;
			_IO reserved_3: 1;
			_IO FSMCEN: 1;
			_IO reserved_4: 1;
			_IO SDIOEN: 1;
			_IO reserved_5: 21;
		} BIT;
	} AHBENR;

	/**
	 * @ingroup RCC_01_RegisterLayer_05_PeripheralClockEnable RCC_01_RegisterLayer_06_RegisterMap
	 * @brief APB2 Peripheral Clock Enable Register
	 * @details
	 * Controls clock gating for peripherals connected to APB2 bus.
	 * Enables or disables clocks to AFIO, GPIO ports, ADC, advanced timers,
	 * SPI1, and USART1. Essential for GPIO and communication peripheral operation.
	 */
	union RCC_APB2ENR
	{
		// Full 32-bit Register Access
		_IO REG;
		// Bit Access
		struct
		{
			_IO AFIOEN: 1;
			_IO reserved_1: 1;
			_IO IOPAEN: 1;
			_IO IOPBEN: 1;
			_IO IOPCEN: 1;
			_IO IOPDEN: 1;
			_IO IOPEEN: 1;
			_IO IOPFEN: 1;
			_IO IOPGEN: 1;
			_IO ADC1EN: 1;
			_IO ADC2EN: 1;
			_IO TIM1EN: 1;
			_IO SPI1EN: 1;
			_IO TIM8EN: 1;
			_IO USART1EN: 1;
			_IO ADC3EN: 1;
			_IO reserved_2: 3;
			_IO TIM9EN: 1;
			_IO TIM10EN: 1;
			_IO TIM11EN: 1;
			_IO reserved_3: 10;
		} BIT;
	} APB2ENR;
	/**
	 * @ingroup RCC_01_RegisterLayer_05_PeripheralClockEnable RCC_01_RegisterLayer_06_RegisterMap
	 * @brief APB1 Peripheral Clock Enable Register
	 * @details
	 * Controls clock gating for peripherals connected to APB1 bus.
	 * Enables or disables clocks to general-purpose timers, watchdogs,
	 * SPI2/3, USART2-5, I2C, USB, CAN, backup interface, power, and DAC.
	 * Critical for timer and communication peripheral operation.
	 */
	union RCC_APB1ENR
	{
		// Full 32-bit Register Access
		_IO REG;
		// Bit Access
		struct
		{
			_IO TIM2EN: 1;
			_IO TIM3EN: 1;
			_IO TIM4EN: 1;
			_IO TIM5EN: 1;
			_IO TIM6EN: 1;
			_IO TIM7EN: 1;
			_IO TIM12EN: 1;
			_IO TIM13EN: 1;
			_IO TIM14EN: 1;
			_IO reserved_1: 2;
			_IO WWDGEN: 1;
			_IO reserved_2: 2;
			_IO SPI2EN: 1;
			_IO SPI3EN: 1;
			_IO reserved_3: 1;
			_IO USART2EN: 1;
			_IO USART3EN: 1;
			_IO UART4EN: 1;
			_IO UART5EN: 1;
			_IO I2C1EN: 1;
			_IO I2C2EN: 1;
			_IO USBEN: 1;
			_IO reserved_4: 1;
			_IO CANEN: 1;
			_IO reserved_5: 1;
			_IO BKPEN: 1;
			_IO PWREN: 1;
			_IO DACEN: 1;
			_IO reserved_6: 2;
		} BIT;
	} APB1ENR;

	/**
	 * @brief Backup Domain Control Register
	 * @details
	 * Controls the backup domain including LSE oscillator and RTC configuration.
	 * Manages RTC clock source selection, RTC enable, and backup domain reset.
	 * This register is not reset by system reset, only by backup domain reset.
	 */
	union RCC_BDCR
	{
		// Full 32-bit Register Access
		_IO REG;
		// Bit Access
		struct
		{
			_IO LSEON: 1;
			_IO LSERDY: 1;
			_IO LSEBYP: 1;
			_IO reserved_1: 5;
			_IO RTCSEL: 2;
			_IO reserved_2: 5;
			_IO RTCEN: 2;
			_IO BDRST: 2;
			_IO reserved_3: 15;
		} BIT;
	} BDCR;

	/**
	 * @brief Control/Status Register
	 * @details
	 * Controls the LSI oscillator and provides reset status flags.
	 * Indicates the source of the last reset (power-on, pin, watchdog, etc.)
	 * and allows clearing of reset flags. LSI is used for independent watchdog.
	 */
	union RCC_CSR 
	{
		// Full 32-bit Register Access
		_IO REG;
		// Bit Access
		struct
		{
			_IO LSION: 1;
			_IO LSIRDY: 1;
			_IO reserved_1: 22;
			_IO RMVF: 1;
			_IO reserved_2: 1;
			_IO PINRSTF: 1;
			_IO PORRSTF: 1;
			_IO SFTRSTF: 1;
			_IO IWDGRSTF: 1;
			_IO WWDGRSTF: 1;
			_IO LPWRRSTF: 1;
		} BIT;
	} CSR;
} RCC_TypeDef;

/** @} */ // RCC_01_RegisterLayer_06_RegisterMap

/** @} */ // RCC_01_RegisterLayer

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_RCC_H_ */
