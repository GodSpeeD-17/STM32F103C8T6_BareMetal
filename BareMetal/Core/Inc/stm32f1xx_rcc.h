/**
 * @file stm32f1xx_rcc.h
 * @author Shrey Shah
 * @version v1.0
 * @date 08-11-2025
 * @defgroup RCC Reset & Clock Control (RCC)
 * @details
 * This module provides complete access to RCC peripheral including:
 * - @ref stm32f1xx_rcc.h "Register mapping"
 * - @ref stm32f1xx.h "Memory Address"
 * - @ref rcc_ll.h "RCC Low Level (LL) APIs"
 * - @ref rcc.h "RCC Driver APIs"
 *
 * @note    All peripheral clock operations require proper RCC configuration
 * @warning Direct register access should only be used when performance is critical
 */
// Header Guards
#ifndef STM32F1XX_RCC_H_
#define STM32F1XX_RCC_H_

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------
#include <stdint.h>

// ------------------------------------------------------------------------------------------
// Theory of Operation
// ------------------------------------------------------------------------------------------
/**
 * @brief RCC Peripheral Hardware Register Mapping
 * @defgroup  RCC_01_Registers RCC Registers
 * @ingroup   RCC
 * @details
 * - STM32F103C8T6 RCC peripheral controls system clocks, resets, and clock gating
 * - Manages multiple clock sources and distribution to all peripherals
 *
 * - RCC Register Map:
 *
 * | Offset | Register | Name | Description |
 * |--------|----------|------|-------------|
 * | `0x00`   | @ref `RCC_CR`     | Clock Control Register | Controls internal/external clock sources |
 * | `0x04`   | @ref `RCC_CFGR`   | Clock Configuration Register | Configures clock dividers and PLL |
 * | `0x08`   | @ref `RCC_CIR`    | Clock Interrupt Register | Manages clock-related interrupts |
 * | `0x0C`   | @ref `RCC_APB2RSTR` | APB2 Peripheral Reset Register | Resets APB2 peripherals |
 * | `0x10`   | @ref `RCC_APB1RSTR` | APB1 Peripheral Reset Register | Resets APB1 peripherals |
 * | `0x14`   | @ref `RCC_AHBENR`  | AHB Peripheral Clock Enable Register | Enables AHB peripherals |
 * | `0x18`   | @ref `RCC_APB2ENR` | APB2 Peripheral Clock Enable Register | Enables APB2 peripherals |
 * | `0x1C`   | @ref `RCC_APB1ENR` | APB1 Peripheral Clock Enable Register | Enables APB1 peripherals |
 * | `0x20`   | @ref `RCC_BDCR`    | Backup Domain Control Register | Controls RTC and backup domain |
 * | `0x24`   | @ref `RCC_CSR`     | Control/Status Register | Controls LSI and reset status |
 *
 * - Key Features:
 * <ul>
 * <li> Multiple clock sources:
 * 	<ul>
 *   <li> HSI: 8 MHz internal RC oscillator </li>
 *   <li> HSE: 4-16 MHz external crystal/oscillator </li>
 *   <li> PLL: Clock multiplier for system clock </li>
 *   <li> LSI: 40 kHz internal RC for IWDG </li>
 *   <li> LSE: 32.768 kHz external crystal for RTC </li>
 * 	</ul>
 * </li>
 * <li> Flexible clock distribution with prescalers </li>
 * <li> Individual peripheral clock gating for power management </li>
 * <li> Clock security system (CSS) for HSE failure detection </li>
 * <li> Backup domain with independent power supply </li>
 * </ul>
 *
 * @note System clock configuration must follow proper sequence
 * @warning Changing clock settings during operation may cause system instability
 *
 * @see Reference Manual RM0008 - Section 7. Reset and Clock Control (RCC)
 * @see Datasheet DS5319 - Section 5. Memory mapping
 * @{ 
 */

// ------------------------------------------------------------------------------------------
// Doxygen Groups
// ------------------------------------------------------------------------------------------ 

/**
 * @defgroup RCC_01_Registers_01_Structure RCC Registers Encapsulation
 * @ingroup  RCC_01_Registers
 * @brief    RCC Registers representation using structure
 */

/**
 * @defgroup RCC_01_Registers_02_Memory RCC Memory Address
 * @ingroup  RCC_01_Registers 
 * @brief    STM32F1xx RCC Memory Address Mapping
 */

/**
 * @defgroup RCC_01_Registers_03_API RCC Register Access APIs
 * @ingroup  RCC_01_Registers 
 * @brief    APIs to access @ref RCC_01_Registers_01_Structure "RCC Registers"
 */

/** @} */ // RCC_01_Registers

/**
 * @defgroup RCC_02_LL RCC Low Level APIs
 * @ingroup  RCC
 * @brief 	 RCC Low Level APIs
 */

/**
 * @defgroup RCC_03_Driver RCC Driver APIs
 * @ingroup  RCC
 * @brief 	 RCC Driver APIs
 */

// ------------------------------------------------------------------------------------------
// RCC_CR (Clock Control Register)
// ------------------------------------------------------------------------------------------ 

/**
 * @brief Clock Control Register (RCC_CR)
 * @defgroup RCC_CR RCC Clock Control Register
 * @ingroup  RCC_01_Registers
 * @{
 */

// ------ HSION (Internal High-Speed Clock Enable) ------ // 
/** @brief Internal High-Speed Clock Enable Position @def RCC_CR_HSION_Pos */
#define RCC_CR_HSION_Pos							((uint8_t) 0U)
/** @brief Internal High-Speed Clock Enable Mask @def RCC_CR_HSION_Msk */
#define RCC_CR_HSION_Msk							((uint32_t)(0x01UL << RCC_CR_HSION_Pos))
/** @brief Internal High-Speed Clock Enable @def RCC_CR_HSION */
#define RCC_CR_HSION								RCC_CR_HSION_Msk

// ------ HSIRDY (Internal High-Speed Clock Ready) ------ // 
/** @brief Internal High-Speed Clock Ready Flag Position @def RCC_CR_HSIRDY_Pos */
#define RCC_CR_HSIRDY_Pos							((uint8_t) 1U)
/** @brief Internal High-Speed Clock Ready Flag Mask @def RCC_CR_HSIRDY_Msk */
#define RCC_CR_HSIRDY_Msk							((uint32_t)(0x01UL << RCC_CR_HSIRDY_Pos))
/** @brief Internal High-Speed Clock Ready Flag @def RCC_CR_HSIRDY */
#define RCC_CR_HSIRDY								RCC_CR_HSIRDY_Msk

// ------ HSITRIM (Internal High-Speed Clock Trimming) ------ // 
/** @brief Internal High-Speed Clock Trimming Position (5 bits) @def RCC_CR_HSITRIM_Pos */
#define RCC_CR_HSITRIM_Pos							((uint8_t) 3U)
/** @brief Internal High-Speed Clock Trimming Mask (5 bits) @def RCC_CR_HSITRIM_Msk */
#define RCC_CR_HSITRIM_Msk							((uint32_t)(0x1FUL << RCC_CR_HSITRIM_Pos))
/** @brief Internal High-Speed Clock Trimming @def RCC_CR_HSITRIM */
#define RCC_CR_HSITRIM								RCC_CR_HSITRIM_Msk

// ------ HSICAL (Internal High-Speed Clock Calibration) ------ // 
/** @brief Internal High-Speed Clock Calibration Position (8 bits) @def RCC_CR_HSICAL_Pos */
#define RCC_CR_HSICAL_Pos							((uint8_t) 8U)
/** @brief Internal High-Speed Clock Calibration Mask (8 bits) @def RCC_CR_HSICAL_Msk */
#define RCC_CR_HSICAL_Msk							((uint32_t)(0xFFUL << RCC_CR_HSICAL_Pos))
/** @brief Internal High-Speed Clock Calibration @def RCC_CR_HSICAL */
#define RCC_CR_HSICAL								RCC_CR_HSICAL_Msk

// ------ HSEON (External High-Speed Clock Enable) ------ // 
/** @brief External High-Speed Clock Enable Position @def RCC_CR_HSEON_Pos */
#define RCC_CR_HSEON_Pos							((uint8_t) 16U)
/** @brief External High-Speed Clock Enable Mask @def RCC_CR_HSEON_Msk */
#define RCC_CR_HSEON_Msk							((uint32_t)(0x01UL << RCC_CR_HSEON_Pos))
/** @brief External High-Speed Clock Enable @def RCC_CR_HSEON */
#define RCC_CR_HSEON								RCC_CR_HSEON_Msk

// ------ HSERDY (External High-Speed Clock Ready) ------ // 
/** @brief External High-Speed Clock Ready Flag Position @def RCC_CR_HSERDY_Pos */
#define RCC_CR_HSERDY_Pos							((uint8_t) 17U)
/** @brief External High-Speed Clock Ready Flag Mask @def RCC_CR_HSERDY_Msk */
#define RCC_CR_HSERDY_Msk							((uint32_t)(0x01UL << RCC_CR_HSERDY_Pos))
/** @brief External High-Speed Clock Ready Flag @def RCC_CR_HSERDY */
#define RCC_CR_HSERDY								RCC_CR_HSERDY_Msk

// ------ HSEBYP (External High-Speed Clock Bypass) ------ // 
/** @brief External High-Speed Clock Bypass Position @def RCC_CR_HSEBYP_Pos */
#define RCC_CR_HSEBYP_Pos							((uint8_t) 18U)
/** @brief External High-Speed Clock Bypass Mask @def RCC_CR_HSEBYP_Msk */
#define RCC_CR_HSEBYP_Msk							((uint32_t)(0x01UL << RCC_CR_HSEBYP_Pos))
/** @brief External High-Speed Clock Bypass @def RCC_CR_HSEBYP */
#define RCC_CR_HSEBYP								RCC_CR_HSEBYP_Msk

// ------ CSSON (Clock Security System Enable) ------ // 
/** @brief Clock Security System Enable Position @def RCC_CR_CSSON_Pos */
#define RCC_CR_CSSON_Pos							((uint8_t) 19U)
/** @brief Clock Security System Enable Mask @def RCC_CR_CSSON_Msk */
#define RCC_CR_CSSON_Msk							((uint32_t)(0x01UL << RCC_CR_CSSON_Pos))
/** @brief Clock Security System Enable @def RCC_CR_CSSON */
#define RCC_CR_CSSON								RCC_CR_CSSON_Msk

// ------ PLLON (PLL Enable) ------ // 
/** @brief PLL Enable Position @def RCC_CR_PLLON_Pos */
#define RCC_CR_PLLON_Pos							((uint8_t) 24U)
/** @brief PLL Enable Mask @def RCC_CR_PLLON_Msk */
#define RCC_CR_PLLON_Msk							((uint32_t)(0x01UL << RCC_CR_PLLON_Pos))
/** @brief PLL Enable @def RCC_CR_PLLON */
#define RCC_CR_PLLON								RCC_CR_PLLON_Msk

// ------ PLLRDY (PLL Ready) ------ // 
/** @brief PLL Ready Flag Position @def RCC_CR_PLLRDY_Pos */
#define RCC_CR_PLLRDY_Pos							((uint8_t) 25U)
/** @brief PLL Ready Flag Mask @def RCC_CR_PLLRDY_Msk */
#define RCC_CR_PLLRDY_Msk							((uint32_t)(0x01UL << RCC_CR_PLLRDY_Pos))
/** @brief PLL Ready Flag @def RCC_CR_PLLRDY */
#define RCC_CR_PLLRDY								RCC_CR_PLLRDY_Msk

/** @} */ // RCC_CR

// ------------------------------------------------------------------------------------------
// RCC_CFGR (Clock Configuration Register)
// ------------------------------------------------------------------------------------------ 

/**
 * @brief Clock Configuration Register (RCC_CFGR)
 * @defgroup RCC_CFGR RCC Clock Configuration Register
 * @ingroup  RCC_01_Registers
 * @{
 */

// ------ SW (System Clock Switch) ------ //
/** @brief System Clock Switch Position (2 bits) @def RCC_CFGR_SW_Pos */
#define RCC_CFGR_SW_Pos							((uint8_t) 0U)
/** @brief System Clock Switch Mask (2 bits) @def RCC_CFGR_SW_Msk */
#define RCC_CFGR_SW_Msk							((uint32_t)(0x03UL << RCC_CFGR_SW_Pos))
/** @brief System Clock Switch @def RCC_CFGR_SW */
#define RCC_CFGR_SW								RCC_CFGR_SW_Msk
/** @brief HSI selected as system clock @def RCC_CFGR_SW_HSI */
#define RCC_CFGR_SW_HSI							((uint32_t)(0x00UL << RCC_CFGR_SW_Pos))
/** @brief HSE selected as system clock @def RCC_CFGR_SW_HSE */
#define RCC_CFGR_SW_HSE							((uint32_t)(0x01UL << RCC_CFGR_SW_Pos))
/** @brief PLL selected as system clock @def RCC_CFGR_SW_PLL */
#define RCC_CFGR_SW_PLL							((uint32_t)(0x02UL << RCC_CFGR_SW_Pos))

// ------ SWS (System Clock Switch Status) ------ //
/** @brief System Clock Switch Status Position (2 bits) @def RCC_CFGR_SWS_Pos */
#define RCC_CFGR_SWS_Pos						((uint8_t) 2U)
/** @brief System Clock Switch Status Mask (2 bits) @def RCC_CFGR_SWS_Msk */
#define RCC_CFGR_SWS_Msk						((uint32_t)(0x03UL << RCC_CFGR_SWS_Pos))
/** @brief System Clock Switch Status @def RCC_CFGR_SWS */
#define RCC_CFGR_SWS							RCC_CFGR_SWS_Msk
/** @brief HSI selected as system clock @def RCC_CFGR_SWS_HSI */
#define RCC_CFGR_SWS_HSI						((uint32_t)(0x00UL << RCC_CFGR_SWS_Pos))
/** @brief HSE selected as system clock @def RCC_CFGR_SWS_HSE */
#define RCC_CFGR_SWS_HSE						((uint32_t)(0x01UL << RCC_CFGR_SWS_Pos))
/** @brief PLL selected as system clock @def RCC_CFGR_SWS_PLL */
#define RCC_CFGR_SWS_PLL						((uint32_t)(0x02UL << RCC_CFGR_SWS_Pos))

// ------ HPRE (AHB Prescaler) ------ //
/** @brief AHB Prescaler Position (4 bits) @def RCC_CFGR_HPRE_Pos */
#define RCC_CFGR_HPRE_Pos						((uint8_t) 4U)
/** @brief AHB Prescaler Mask (4 bits) @def RCC_CFGR_HPRE_Msk */
#define RCC_CFGR_HPRE_Msk						((uint32_t)(0x0FUL << RCC_CFGR_HPRE_Pos))
/** @brief AHB Prescaler @def RCC_CFGR_HPRE */
#define RCC_CFGR_HPRE							RCC_CFGR_HPRE_Msk
/** @brief AHB prescaler = 1 (no division) @def RCC_CFGR_HPRE_DIV1 */
#define RCC_CFGR_HPRE_DIV1						((uint32_t)(0x00UL << RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 2 @def RCC_CFGR_HPRE_DIV2 */
#define RCC_CFGR_HPRE_DIV2						((uint32_t)(0x08UL << RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 4 @def RCC_CFGR_HPRE_DIV4 */
#define RCC_CFGR_HPRE_DIV4						((uint32_t)(0x09UL << RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 8 @def RCC_CFGR_HPRE_DIV8 */
#define RCC_CFGR_HPRE_DIV8						((uint32_t)(0x0AUL << RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 16 @def RCC_CFGR_HPRE_DIV16 */
#define RCC_CFGR_HPRE_DIV16						((uint32_t)(0x0BUL << RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 64 @def RCC_CFGR_HPRE_DIV64 */
#define RCC_CFGR_HPRE_DIV64						((uint32_t)(0x0CUL << RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 128 @def RCC_CFGR_HPRE_DIV128 */
#define RCC_CFGR_HPRE_DIV128					((uint32_t)(0x0DUL << RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 256 @def RCC_CFGR_HPRE_DIV256 */
#define RCC_CFGR_HPRE_DIV256					((uint32_t)(0x0EUL << RCC_CFGR_HPRE_Pos))
/** @brief AHB prescaler = 512 @def RCC_CFGR_HPRE_DIV512 */
#define RCC_CFGR_HPRE_DIV512					((uint32_t)(0x0FUL << RCC_CFGR_HPRE_Pos))

// ------ PPRE1 (APB Low-Speed Prescaler - APB1) ------ //
/** @brief APB1 Prescaler Position (3 bits) @def RCC_CFGR_PPRE1_Pos */
#define RCC_CFGR_PPRE1_Pos						((uint8_t) 8U)
/** @brief APB1 Prescaler Mask (3 bits) @def RCC_CFGR_PPRE1_Msk */
#define RCC_CFGR_PPRE1_Msk						((uint32_t)(0x07UL << RCC_CFGR_PPRE1_Pos))
/** @brief APB1 Prescaler @def RCC_CFGR_PPRE1 */
#define RCC_CFGR_PPRE1							RCC_CFGR_PPRE1_Msk
/** @brief APB1 prescaler = 1 (no division) @def RCC_CFGR_PPRE1_DIV1 */
#define RCC_CFGR_PPRE1_DIV1						((uint32_t)(0x00UL << RCC_CFGR_PPRE1_Pos))
/** @brief APB1 prescaler = 2 @def RCC_CFGR_PPRE1_DIV2 */
#define RCC_CFGR_PPRE1_DIV2						((uint32_t)(0x04UL << RCC_CFGR_PPRE1_Pos))
/** @brief APB1 prescaler = 4 @def RCC_CFGR_PPRE1_DIV4 */
#define RCC_CFGR_PPRE1_DIV4						((uint32_t)(0x05UL << RCC_CFGR_PPRE1_Pos))
/** @brief APB1 prescaler = 8 @def RCC_CFGR_PPRE1_DIV8 */
#define RCC_CFGR_PPRE1_DIV8						((uint32_t)(0x06UL << RCC_CFGR_PPRE1_Pos))
/** @brief APB1 prescaler = 16 @def RCC_CFGR_PPRE1_DIV16 */
#define RCC_CFGR_PPRE1_DIV16					((uint32_t)(0x07UL << RCC_CFGR_PPRE1_Pos))

// ------ PPRE2 (APB High-Speed Prescaler - APB2) ------ //
/** @brief APB2 Prescaler Position (3 bits) @def RCC_CFGR_PPRE2_Pos */
#define RCC_CFGR_PPRE2_Pos						((uint8_t) 11U)
/** @brief APB2 Prescaler Mask (3 bits) @def RCC_CFGR_PPRE2_Msk */
#define RCC_CFGR_PPRE2_Msk						((uint32_t)(0x07UL << RCC_CFGR_PPRE2_Pos))
/** @brief APB2 Prescaler @def RCC_CFGR_PPRE2 */
#define RCC_CFGR_PPRE2							RCC_CFGR_PPRE2_Msk
/** @brief APB2 prescaler = 1 (no division) @def RCC_CFGR_PPRE2_DIV1 */
#define RCC_CFGR_PPRE2_DIV1						((uint32_t)(0x00UL << RCC_CFGR_PPRE2_Pos))
/** @brief APB2 prescaler = 2 @def RCC_CFGR_PPRE2_DIV2 */
#define RCC_CFGR_PPRE2_DIV2						((uint32_t)(0x04UL << RCC_CFGR_PPRE2_Pos))
/** @brief APB2 prescaler = 4 @def RCC_CFGR_PPRE2_DIV4 */
#define RCC_CFGR_PPRE2_DIV4						((uint32_t)(0x05UL << RCC_CFGR_PPRE2_Pos))
/** @brief APB2 prescaler = 8 @def RCC_CFGR_PPRE2_DIV8 */
#define RCC_CFGR_PPRE2_DIV8						((uint32_t)(0x06UL << RCC_CFGR_PPRE2_Pos))
/** @brief APB2 prescaler = 16 @def RCC_CFGR_PPRE2_DIV16 */
#define RCC_CFGR_PPRE2_DIV16					((uint32_t)(0x07UL << RCC_CFGR_PPRE2_Pos))

// ------ ADCPRE (ADC Prescaler) ------ //
/** @brief ADC Prescaler Position (2 bits) @def RCC_CFGR_ADCPRE_Pos */
#define RCC_CFGR_ADCPRE_Pos						((uint8_t) 14U)
/** @brief ADC Prescaler Mask (2 bits) @def RCC_CFGR_ADCPRE_Msk */
#define RCC_CFGR_ADCPRE_Msk						((uint32_t)(0x03UL << RCC_CFGR_ADCPRE_Pos))
/** @brief ADC Prescaler @def RCC_CFGR_ADCPRE */
#define RCC_CFGR_ADCPRE							RCC_CFGR_ADCPRE_Msk
/** @brief ADC prescaler = 2 (PCLK2/2) @def RCC_CFGR_ADCPRE_DIV2 */
#define RCC_CFGR_ADCPRE_DIV2					((uint32_t)(0x00UL << RCC_CFGR_ADCPRE_Pos))
/** @brief ADC prescaler = 4 (PCLK2/4) @def RCC_CFGR_ADCPRE_DIV4 */
#define RCC_CFGR_ADCPRE_DIV4					((uint32_t)(0x01UL << RCC_CFGR_ADCPRE_Pos))
/** @brief ADC prescaler = 6 (PCLK2/6) @def RCC_CFGR_ADCPRE_DIV6 */
#define RCC_CFGR_ADCPRE_DIV6					((uint32_t)(0x02UL << RCC_CFGR_ADCPRE_Pos))
/** @brief ADC prescaler = 8 (PCLK2/8) @def RCC_CFGR_ADCPRE_DIV8 */
#define RCC_CFGR_ADCPRE_DIV8					((uint32_t)(0x03UL << RCC_CFGR_ADCPRE_Pos))

// ------ PLLSRC (PLL Entry Clock Source) ------ //
/** @brief PLL Entry Clock Source Position @def RCC_CFGR_PLLSRC_Pos */
#define RCC_CFGR_PLLSRC_Pos						((uint8_t) 16U)
/** @brief PLL Entry Clock Source Mask @def RCC_CFGR_PLLSRC_Msk */
#define RCC_CFGR_PLLSRC_Msk						((uint32_t)(0x01UL << RCC_CFGR_PLLSRC_Pos))
/** @brief PLL Entry Clock Source @def RCC_CFGR_PLLSRC */
#define RCC_CFGR_PLLSRC							RCC_CFGR_PLLSRC_Msk
/** @brief HSI/2 selected as PLL input clock @def RCC_CFGR_PLLSRC_HSI_DIV2 */
#define RCC_CFGR_PLLSRC_HSI_DIV2				((uint32_t)(0x00UL << RCC_CFGR_PLLSRC_Pos))
/** @brief HSE selected as PLL input clock @def RCC_CFGR_PLLSRC_HSE */
#define RCC_CFGR_PLLSRC_HSE						((uint32_t)(0x01UL << RCC_CFGR_PLLSRC_Pos))

// ------ PLLXTPRE (HSE Divider for PLL Entry) ------ //
/** @brief HSE Divider for PLL Entry Position @def RCC_CFGR_PLLXTPRE_Pos */
#define RCC_CFGR_PLLXTPRE_Pos					((uint8_t) 17U)
/** @brief HSE Divider for PLL Entry Mask @def RCC_CFGR_PLLXTPRE_Msk */
#define RCC_CFGR_PLLXTPRE_Msk					((uint32_t)(0x01UL << RCC_CFGR_PLLXTPRE_Pos))
/** @brief HSE Divider for PLL Entry @def RCC_CFGR_PLLXTPRE */
#define RCC_CFGR_PLLXTPRE						RCC_CFGR_PLLXTPRE_Msk
#define RCC_CFGR_PLLXTPRE_HSE						((uint32_t)(0x00UL << RCC_CFGR_PLLXTPRE_Pos))
/** @brief HSE divided by 2 before PLL @def RCC_CFGR_PLLXTPRE_HSE_DIV2 */
#define RCC_CFGR_PLLXTPRE_HSE_DIV2					((uint32_t)(0x01UL << RCC_CFGR_PLLXTPRE_Pos))

// ------ PLLMUL (PLL Multiplication Factor) ------ //
/** @brief PLL Multiplication Factor Position (4 bits) @def RCC_CFGR_PLLMUL_Pos */
#define RCC_CFGR_PLLMUL_Pos						((uint8_t) 18U)
/** @brief PLL Multiplication Factor Mask (4 bits) @def RCC_CFGR_PLLMUL_Msk */
#define RCC_CFGR_PLLMUL_Msk						((uint32_t)(0x0FUL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL Multiplication Factor @def RCC_CFGR_PLLMUL */
#define RCC_CFGR_PLLMUL							RCC_CFGR_PLLMUL_Msk

// ------ PLLMUL Values (PLL Multiplication Factor Selection) ------ //
/** @brief PLL input clock x 2 @def RCC_CFGR_PLLMUL_2 */
#define RCC_CFGR_PLLMUL_2						((uint32_t)(0x00UL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 3 @def RCC_CFGR_PLLMUL_3 */
#define RCC_CFGR_PLLMUL_3						((uint32_t)(0x01UL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 4 @def RCC_CFGR_PLLMUL_4 */
#define RCC_CFGR_PLLMUL_4						((uint32_t)(0x02UL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 5 @def RCC_CFGR_PLLMUL_5 */
#define RCC_CFGR_PLLMUL_5						((uint32_t)(0x03UL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 6 @def RCC_CFGR_PLLMUL_6 */
#define RCC_CFGR_PLLMUL_6						((uint32_t)(0x04UL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 7 @def RCC_CFGR_PLLMUL_7 */
#define RCC_CFGR_PLLMUL_7						((uint32_t)(0x05UL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 8 @def RCC_CFGR_PLLMUL_8 */
#define RCC_CFGR_PLLMUL_8						((uint32_t)(0x06UL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 9 @def RCC_CFGR_PLLMUL_9 */
#define RCC_CFGR_PLLMUL_9						((uint32_t)(0x07UL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 10 @def RCC_CFGR_PLLMUL_10 */
#define RCC_CFGR_PLLMUL_10						((uint32_t)(0x08UL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 11 @def RCC_CFGR_PLLMUL_11 */
#define RCC_CFGR_PLLMUL_11						((uint32_t)(0x9UL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 12 @def RCC_CFGR_PLLMUL_12 */
#define RCC_CFGR_PLLMUL_12						((uint32_t)(0xAUL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 13 @def RCC_CFGR_PLLMUL_13 */
#define RCC_CFGR_PLLMUL_13						((uint32_t)(0xBUL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 14 @def RCC_CFGR_PLLMUL_14 */
#define RCC_CFGR_PLLMUL_14						((uint32_t)(0xCUL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 15 @def RCC_CFGR_PLLMUL_15 */
#define RCC_CFGR_PLLMUL_15						((uint32_t)(0xDUL << RCC_CFGR_PLLMUL_Pos))
/** @brief PLL input clock x 16 @def RCC_CFGR_PLLMUL_16 */
#define RCC_CFGR_PLLMUL_16						((uint32_t)(0xEUL << RCC_CFGR_PLLMUL_Pos))

// ------ USBPRE (USB Prescaler) ------ //
/** @brief USB Prescaler Position @def RCC_CFGR_USBPRE_Pos */
#define RCC_CFGR_USBPRE_Pos						((uint8_t) 22U)
/** @brief USB Prescaler Mask @def RCC_CFGR_USBPRE_Msk */
#define RCC_CFGR_USBPRE_Msk						((uint32_t)(0x01UL << RCC_CFGR_USBPRE_Pos))
/** @brief USB Prescaler @def RCC_CFGR_USBPRE */
#define RCC_CFGR_USBPRE							RCC_CFGR_USBPRE_Msk
/** @brief PLL clock divided by 1.5 (48 MHz for USB) @def RCC_CFGR_USBPRE_DIV1_5 */
#define RCC_CFGR_USBPRE_DIV1_5					((uint32_t)(0x00UL << RCC_CFGR_USBPRE_Pos))
/** @brief PLL clock directly used as USB clock (must be 48 MHz) @def RCC_CFGR_USBPRE_DIRECT */
#define RCC_CFGR_USBPRE_DIRECT					((uint32_t)(0x01UL << RCC_CFGR_USBPRE_Pos))

// ------ MCO (Microcontroller Clock Output) ------ //
/** @brief Microcontroller Clock Output Position (3 bits) @def RCC_CFGR_MCO_Pos */
#define RCC_CFGR_MCO_Pos						((uint8_t) 24U)
/** @brief Microcontroller Clock Output Mask (3 bits) @def RCC_CFGR_MCO_Msk */
#define RCC_CFGR_MCO_Msk						((uint32_t)(0x07UL << RCC_CFGR_MCO_Pos))
/** @brief Microcontroller Clock Output @def RCC_CFGR_MCO */
#define RCC_CFGR_MCO							RCC_CFGR_MCO_Msk
/** @brief No clock output on MCO @def RCC_CFGR_MCO_NOCLOCK */
#define RCC_CFGR_MCO_NOCLOCK					((uint32_t)(0x00UL << RCC_CFGR_MCO_Pos))
/** @brief System clock output on MCO @def RCC_CFGR_MCO_SYSCLK */
#define RCC_CFGR_MCO_SYSCLK						((uint32_t)(0x01UL << RCC_CFGR_MCO_Pos))
/** @brief HSI clock output on MCO @def RCC_CFGR_MCO_HSI */
#define RCC_CFGR_MCO_HSI						((uint32_t)(0x02UL << RCC_CFGR_MCO_Pos))
/** @brief HSE clock output on MCO @def RCC_CFGR_MCO_HSE */
#define RCC_CFGR_MCO_HSE						((uint32_t)(0x03UL << RCC_CFGR_MCO_Pos))
/** @brief PLL clock divided by 2 output on MCO @def RCC_CFGR_MCO_PLL_DIV2 */
#define RCC_CFGR_MCO_PLL_DIV2					((uint32_t)(0x04UL << RCC_CFGR_MCO_Pos))
/** @brief PLL clock output on MCO @def RCC_CFGR_MCO_PLL */
#define RCC_CFGR_MCO_PLL						((uint32_t)(0x05UL << RCC_CFGR_MCO_Pos))

/** @} */ // RCC_CFGR 

// ------------------------------------------------------------------------------------------
// RCC_CIR (Clock Interrupt Register)
// ------------------------------------------------------------------------------------------ 

/**
 * @brief Clock Interrupt Register (RCC_CIR)
 * @defgroup RCC_CIR RCC Clock Interrupt Register
 * @ingroup  RCC_01_Registers
 * @{
 */

// ------ LSIRDYF (LSI Ready Interrupt Flag) ------ // 
/** @brief LSI Ready Interrupt Flag Position @def RCC_CIR_LSIRDYF_Pos */
#define RCC_CIR_LSIRDYF_Pos							((uint8_t) 0U)
/** @brief LSI Ready Interrupt Flag Mask @def RCC_CIR_LSIRDYF_Msk */
#define RCC_CIR_LSIRDYF_Msk							((uint32_t)(0x01UL << RCC_CIR_LSIRDYF_Pos))
/** @brief LSI Ready Interrupt Flag @def RCC_CIR_LSIRDYF */
#define RCC_CIR_LSIRDYF								RCC_CIR_LSIRDYF_Msk

// ------ LSERDYF (LSE Ready Interrupt Flag) ------ // 
/** @brief LSE Ready Interrupt Flag Position @def RCC_CIR_LSERDYF_Pos */
#define RCC_CIR_LSERDYF_Pos							((uint8_t) 1U)
/** @brief LSE Ready Interrupt Flag Mask @def RCC_CIR_LSERDYF_Msk */
#define RCC_CIR_LSERDYF_Msk							((uint32_t)(0x01UL << RCC_CIR_LSERDYF_Pos))
/** @brief LSE Ready Interrupt Flag @def RCC_CIR_LSERDYF */
#define RCC_CIR_LSERDYF								RCC_CIR_LSERDYF_Msk

// ------ HSIRDYF (HSI Ready Interrupt Flag) ------ // 
/** @brief HSI Ready Interrupt Flag Position @def RCC_CIR_HSIRDYF_Pos */
#define RCC_CIR_HSIRDYF_Pos							((uint8_t) 2U)
/** @brief HSI Ready Interrupt Flag Mask @def RCC_CIR_HSIRDYF_Msk */
#define RCC_CIR_HSIRDYF_Msk							((uint32_t)(0x01UL << RCC_CIR_HSIRDYF_Pos))
/** @brief HSI Ready Interrupt Flag @def RCC_CIR_HSIRDYF */
#define RCC_CIR_HSIRDYF								RCC_CIR_HSIRDYF_Msk

// ------ HSERDYF (HSE Ready Interrupt Flag) ------ // 
/** @brief HSE Ready Interrupt Flag Position @def RCC_CIR_HSERDYF_Pos */
#define RCC_CIR_HSERDYF_Pos							((uint8_t) 3U)
/** @brief HSE Ready Interrupt Flag Mask @def RCC_CIR_HSERDYF_Msk */
#define RCC_CIR_HSERDYF_Msk							((uint32_t)(0x01UL << RCC_CIR_HSERDYF_Pos))
/** @brief HSE Ready Interrupt Flag @def RCC_CIR_HSERDYF */
#define RCC_CIR_HSERDYF								RCC_CIR_HSERDYF_Msk

// ------ PLLRDYF (PLL Ready Interrupt Flag) ------ // 
/** @brief PLL Ready Interrupt Flag Position @def RCC_CIR_PLLRDYF_Pos */
#define RCC_CIR_PLLRDYF_Pos							((uint8_t) 4U)
/** @brief PLL Ready Interrupt Flag Mask @def RCC_CIR_PLLRDYF_Msk */
#define RCC_CIR_PLLRDYF_Msk							((uint32_t)(0x01UL << RCC_CIR_PLLRDYF_Pos))
/** @brief PLL Ready Interrupt Flag @def RCC_CIR_PLLRDYF */
#define RCC_CIR_PLLRDYF								RCC_CIR_PLLRDYF_Msk

// ------ CSFF (Clock Security System Interrupt Flag) ------ // 
/** @brief Clock Security System Interrupt Flag Position @def RCC_CIR_CSFF_Pos */
#define RCC_CIR_CSFF_Pos							((uint8_t) 7U)
/** @brief Clock Security System Interrupt Flag Mask @def RCC_CIR_CSFF_Msk */
#define RCC_CIR_CSFF_Msk							((uint32_t)(0x01UL << RCC_CIR_CSFF_Pos))
/** @brief Clock Security System Interrupt Flag @def RCC_CIR_CSFF */
#define RCC_CIR_CSFF								RCC_CIR_CSFF_Msk

// ------ LSIRDYIE (LSI Ready Interrupt Enable) ------ // 
/** @brief LSI Ready Interrupt Enable Position @def RCC_CIR_LSIRDYIE_Pos */
#define RCC_CIR_LSIRDYIE_Pos						((uint8_t) 8U)
/** @brief LSI Ready Interrupt Enable Mask @def RCC_CIR_LSIRDYIE_Msk */
#define RCC_CIR_LSIRDYIE_Msk						((uint32_t)(0x01UL << RCC_CIR_LSIRDYIE_Pos))
/** @brief LSI Ready Interrupt Enable @def RCC_CIR_LSIRDYIE */
#define RCC_CIR_LSIRDYIE							RCC_CIR_LSIRDYIE_Msk

// ------ LSERDYIE (LSE Ready Interrupt Enable) ------ // 
/** @brief LSE Ready Interrupt Enable Position @def RCC_CIR_LSERDYIE_Pos */
#define RCC_CIR_LSERDYIE_Pos						((uint8_t) 9U)
/** @brief LSE Ready Interrupt Enable Mask @def RCC_CIR_LSERDYIE_Msk */
#define RCC_CIR_LSERDYIE_Msk						((uint32_t)(0x01UL << RCC_CIR_LSERDYIE_Pos))
/** @brief LSE Ready Interrupt Enable @def RCC_CIR_LSERDYIE */
#define RCC_CIR_LSERDYIE							RCC_CIR_LSERDYIE_Msk

// ------ HSIRDYIE (HSI Ready Interrupt Enable) ------ // 
/** @brief HSI Ready Interrupt Enable Position @def RCC_CIR_HSIRDYIE_Pos */
#define RCC_CIR_HSIRDYIE_Pos						((uint8_t) 10U)
/** @brief HSI Ready Interrupt Enable Mask @def RCC_CIR_HSIRDYIE_Msk */
#define RCC_CIR_HSIRDYIE_Msk						((uint32_t)(0x01UL << RCC_CIR_HSIRDYIE_Pos))
/** @brief HSI Ready Interrupt Enable @def RCC_CIR_HSIRDYIE */
#define RCC_CIR_HSIRDYIE							RCC_CIR_HSIRDYIE_Msk

// ------ HSERDYIE (HSE Ready Interrupt Enable) ------ // 
/** @brief HSE Ready Interrupt Enable Position @def RCC_CIR_HSERDYIE_Pos */
#define RCC_CIR_HSERDYIE_Pos						((uint8_t) 11U)
/** @brief HSE Ready Interrupt Enable Mask @def RCC_CIR_HSERDYIE_Msk */
#define RCC_CIR_HSERDYIE_Msk						((uint32_t)(0x01UL << RCC_CIR_HSERDYIE_Pos))
/** @brief HSE Ready Interrupt Enable @def RCC_CIR_HSERDYIE */
#define RCC_CIR_HSERDYIE							RCC_CIR_HSERDYIE_Msk

// ------ PLLRDYIE (PLL Ready Interrupt Enable) ------ // 
/** @brief PLL Ready Interrupt Enable Position @def RCC_CIR_PLLRDYIE_Pos */
#define RCC_CIR_PLLRDYIE_Pos						((uint8_t) 12U)
/** @brief PLL Ready Interrupt Enable Mask @def RCC_CIR_PLLRDYIE_Msk */
#define RCC_CIR_PLLRDYIE_Msk						((uint32_t)(0x01UL << RCC_CIR_PLLRDYIE_Pos))
/** @brief PLL Ready Interrupt Enable @def RCC_CIR_PLLRDYIE */
#define RCC_CIR_PLLRDYIE							RCC_CIR_PLLRDYIE_Msk

// ------ LSIRDYC (LSI Ready Interrupt Clear) ------ // 
/** @brief LSI Ready Interrupt Clear Position @def RCC_CIR_LSIRDYC_Pos */
#define RCC_CIR_LSIRDYC_Pos							((uint8_t) 16U)
/** @brief LSI Ready Interrupt Clear Mask @def RCC_CIR_LSIRDYC_Msk */
#define RCC_CIR_LSIRDYC_Msk							((uint32_t)(0x01UL << RCC_CIR_LSIRDYC_Pos))
/** @brief LSI Ready Interrupt Clear @def RCC_CIR_LSIRDYC */
#define RCC_CIR_LSIRDYC								RCC_CIR_LSIRDYC_Msk

// ------ LSERDYC (LSE Ready Interrupt Clear) ------ // 
/** @brief LSE Ready Interrupt Clear Position @def RCC_CIR_LSERDYC_Pos */
#define RCC_CIR_LSERDYC_Pos							((uint8_t) 17U)
/** @brief LSE Ready Interrupt Clear Mask @def RCC_CIR_LSERDYC_Msk */
#define RCC_CIR_LSERDYC_Msk							((uint32_t)(0x01UL << RCC_CIR_LSERDYC_Pos))
/** @brief LSE Ready Interrupt Clear @def RCC_CIR_LSERDYC */
#define RCC_CIR_LSERDYC								RCC_CIR_LSERDYC_Msk

// ------ HSIRDYC (HSI Ready Interrupt Clear) ------ // 
/** @brief HSI Ready Interrupt Clear Position @def RCC_CIR_HSIRDYC_Pos */
#define RCC_CIR_HSIRDYC_Pos							((uint8_t) 18U)
/** @brief HSI Ready Interrupt Clear Mask @def RCC_CIR_HSIRDYC_Msk */
#define RCC_CIR_HSIRDYC_Msk							((uint32_t)(0x01UL << RCC_CIR_HSIRDYC_Pos))
/** @brief HSI Ready Interrupt Clear @def RCC_CIR_HSIRDYC */
#define RCC_CIR_HSIRDYC								RCC_CIR_HSIRDYC_Msk

// ------ HSERDYC (HSE Ready Interrupt Clear) ------ // 
/** @brief HSE Ready Interrupt Clear Position @def RCC_CIR_HSERDYC_Pos */
#define RCC_CIR_HSERDYC_Pos							((uint8_t) 19U)
/** @brief HSE Ready Interrupt Clear Mask @def RCC_CIR_HSERDYC_Msk */
#define RCC_CIR_HSERDYC_Msk							((uint32_t)(0x01UL << RCC_CIR_HSERDYC_Pos))
/** @brief HSE Ready Interrupt Clear @def RCC_CIR_HSERDYC */
#define RCC_CIR_HSERDYC								RCC_CIR_HSERDYC_Msk

// ------ PLLRDYC (PLL Ready Interrupt Clear) ------ // 
/** @brief PLL Ready Interrupt Clear Position @def RCC_CIR_PLLRDYC_Pos */
#define RCC_CIR_PLLRDYC_Pos							((uint8_t) 20U)
/** @brief PLL Ready Interrupt Clear Mask @def RCC_CIR_PLLRDYC_Msk */
#define RCC_CIR_PLLRDYC_Msk							((uint32_t)(0x01UL << RCC_CIR_PLLRDYC_Pos))
/** @brief PLL Ready Interrupt Clear @def RCC_CIR_PLLRDYC */
#define RCC_CIR_PLLRDYC								RCC_CIR_PLLRDYC_Msk

// ------ CSSC (Clock Security System Interrupt Clear) ------ // 
/** @brief Clock Security System Interrupt Clear Position @def RCC_CIR_CSSC_Pos */
#define RCC_CIR_CSSC_Pos							((uint8_t) 23U)
/** @brief Clock Security System Interrupt Clear Mask @def RCC_CIR_CSSC_Msk */
#define RCC_CIR_CSSC_Msk							((uint32_t)(0x01UL << RCC_CIR_CSSC_Pos))
/** @brief Clock Security System Interrupt Clear @def RCC_CIR_CSSC */
#define RCC_CIR_CSSC								RCC_CIR_CSSC_Msk

/** @} */ // RCC_CIR

/**
 * @brief APB2 Peripheral Reset Register (RCC_APB2RSTR)
 * @defgroup RCC_APB2RSTR RCC APB2 Peripheral Reset Register
 * @ingroup	RCC_01_Registers
 * @{
 */

// ------ AFIORST (Alternate Function I/O Reset) ------ //
/** @brief Alternate Function I/O Reset Position @def RCC_APB2RSTR_AFIORST_Pos */
#define RCC_APB2RSTR_AFIORST_Pos					((uint8_t) 0U)
/** @brief Alternate Function I/O Reset Mask @def RCC_APB2RSTR_AFIORST_Msk */
#define RCC_APB2RSTR_AFIORST_Msk					((uint32_t)(0x01UL << RCC_APB2RSTR_AFIORST_Pos))
/** @brief Alternate Function I/O Reset @def RCC_APB2RSTR_AFIORST */
#define RCC_APB2RSTR_AFIORST						RCC_APB2RSTR_AFIORST_Msk

// ------ IOPARST (I/O Port A Reset) ------ //
/** @brief I/O Port A Reset Position @def RCC_APB2RSTR_IOPARST_Pos */
#define RCC_APB2RSTR_IOPARST_Pos						((uint8_t) 2U)
/** @brief I/O Port A Reset Mask @def RCC_APB2RSTR_IOPARST_Msk */
#define RCC_APB2RSTR_IOPARST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_IOPARST_Pos))
/** @brief I/O Port A Reset @def RCC_APB2RSTR_IOPARST */
#define RCC_APB2RSTR_IOPARST							RCC_APB2RSTR_IOPARST_Msk

// ------ IOPBRST (I/O Port B Reset) ------ //
/** @brief I/O Port B Reset Position @def RCC_APB2RSTR_IOPBRST_Pos */
#define RCC_APB2RSTR_IOPBRST_Pos						((uint8_t) 3U)
/** @brief I/O Port B Reset Mask @def RCC_APB2RSTR_IOPBRST_Msk */
#define RCC_APB2RSTR_IOPBRST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_IOPBRST_Pos))
/** @brief I/O Port B Reset @def RCC_APB2RSTR_IOPBRST */
#define RCC_APB2RSTR_IOPBRST							RCC_APB2RSTR_IOPBRST_Msk

// ------ IOPCRST (I/O Port C Reset) ------ //
/** @brief I/O Port C Reset Position @def RCC_APB2RSTR_IOPCRST_Pos */
#define RCC_APB2RSTR_IOPCRST_Pos						((uint8_t) 4U)
/** @brief I/O Port C Reset Mask @def RCC_APB2RSTR_IOPCRST_Msk */
#define RCC_APB2RSTR_IOPCRST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_IOPCRST_Pos))
/** @brief I/O Port C Reset @def RCC_APB2RSTR_IOPCRST */
#define RCC_APB2RSTR_IOPCRST							RCC_APB2RSTR_IOPCRST_Msk

// ------ IOPDRST (I/O Port D Reset) ------ //
/** @brief I/O Port D Reset Position @def RCC_APB2RSTR_IOPDRST_Pos */
#define RCC_APB2RSTR_IOPDRST_Pos						((uint8_t) 5U)
/** @brief I/O Port D Reset Mask @def RCC_APB2RSTR_IOPDRST_Msk */
#define RCC_APB2RSTR_IOPDRST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_IOPDRST_Pos))
/** @brief I/O Port D Reset @def RCC_APB2RSTR_IOPDRST */
#define RCC_APB2RSTR_IOPDRST							RCC_APB2RSTR_IOPDRST_Msk

// ------ IOPERST (I/O Port E Reset) ------ //
/** @brief I/O Port E Reset Position @def RCC_APB2RSTR_IOPERST_Pos */
#define RCC_APB2RSTR_IOPERST_Pos						((uint8_t) 6U)
/** @brief I/O Port E Reset Mask @def RCC_APB2RSTR_IOPERST_Msk */
#define RCC_APB2RSTR_IOPERST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_IOPERST_Pos))
/** @brief I/O Port E Reset @def RCC_APB2RSTR_IOPERST */
#define RCC_APB2RSTR_IOPERST							RCC_APB2RSTR_IOPERST_Msk

// ------ IOPFRST (I/O Port F Reset) ------ //
/** @brief I/O Port F Reset Position @def RCC_APB2RSTR_IOPFRST_Pos */
#define RCC_APB2RSTR_IOPFRST_Pos						((uint8_t) 7U)
/** @brief I/O Port F Reset Mask @def RCC_APB2RSTR_IOPFRST_Msk */
#define RCC_APB2RSTR_IOPFRST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_IOPFRST_Pos))
/** @brief I/O Port F Reset @def RCC_APB2RSTR_IOPFRST */
#define RCC_APB2RSTR_IOPFRST							RCC_APB2RSTR_IOPFRST_Msk

// ------ IOPGRST (I/O Port G Reset) ------ //
/** @brief I/O Port G Reset Position @def RCC_APB2RSTR_IOPGRST_Pos */
#define RCC_APB2RSTR_IOPGRST_Pos						((uint8_t) 8U)
/** @brief I/O Port G Reset Mask @def RCC_APB2RSTR_IOPGRST_Msk */
#define RCC_APB2RSTR_IOPGRST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_IOPGRST_Pos))
/** @brief I/O Port G Reset @def RCC_APB2RSTR_IOPGRST */
#define RCC_APB2RSTR_IOPGRST							RCC_APB2RSTR_IOPGRST_Msk

// ------ ADC1RST (ADC 1 Reset) ------ //
/** @brief ADC 1 Reset Position @def RCC_APB2RSTR_ADC1RST_Pos */
#define RCC_APB2RSTR_ADC1RST_Pos						((uint8_t) 9U)
/** @brief ADC 1 Reset Mask @def RCC_APB2RSTR_ADC1RST_Msk */
#define RCC_APB2RSTR_ADC1RST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_ADC1RST_Pos))
/** @brief ADC 1 Reset @def RCC_APB2RSTR_ADC1RST */
#define RCC_APB2RSTR_ADC1RST							RCC_APB2RSTR_ADC1RST_Msk

// ------ ADC2RST (ADC 2 Reset) ------ //
/** @brief ADC 2 Reset Position @def RCC_APB2RSTR_ADC2RST_Pos */
#define RCC_APB2RSTR_ADC2RST_Pos						((uint8_t) 10U)
/** @brief ADC 2 Reset Mask @def RCC_APB2RSTR_ADC2RST_Msk */
#define RCC_APB2RSTR_ADC2RST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_ADC2RST_Pos))
/** @brief ADC 2 Reset @def RCC_APB2RSTR_ADC2RST */
#define RCC_APB2RSTR_ADC2RST							RCC_APB2RSTR_ADC2RST_Msk

// ------ TIM1RST (TIM1 Timer Reset) ------ //
/** @brief TIM1 Timer Reset Position @def RCC_APB2RSTR_TIM1RST_Pos */
#define RCC_APB2RSTR_TIM1RST_Pos						((uint8_t) 11U)
/** @brief TIM1 Timer Reset Mask @def RCC_APB2RSTR_TIM1RST_Msk */
#define RCC_APB2RSTR_TIM1RST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_TIM1RST_Pos))
/** @brief TIM1 Timer Reset @def RCC_APB2RSTR_TIM1RST */
#define RCC_APB2RSTR_TIM1RST							RCC_APB2RSTR_TIM1RST_Msk

// ------ SPI1RST (SPI1 Reset) ------ //
/** @brief SPI1 Reset Position @def RCC_APB2RSTR_SPI1RST_Pos */
#define RCC_APB2RSTR_SPI1RST_Pos						((uint8_t) 12U)
/** @brief SPI1 Reset Mask @def RCC_APB2RSTR_SPI1RST_Msk */
#define RCC_APB2RSTR_SPI1RST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_SPI1RST_Pos))
/** @brief SPI1 Reset @def RCC_APB2RSTR_SPI1RST */
#define RCC_APB2RSTR_SPI1RST							RCC_APB2RSTR_SPI1RST_Msk

// ------ TIM8RST (TIM8 Timer Reset) ------ //
/** @brief TIM8 Timer Reset Position @def RCC_APB2RSTR_TIM8RST_Pos */
#define RCC_APB2RSTR_TIM8RST_Pos						((uint8_t) 13U)
/** @brief TIM8 Timer Reset Mask @def RCC_APB2RSTR_TIM8RST_Msk */
#define RCC_APB2RSTR_TIM8RST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_TIM8RST_Pos))
/** @brief TIM8 Timer Reset @def RCC_APB2RSTR_TIM8RST */
#define RCC_APB2RSTR_TIM8RST							RCC_APB2RSTR_TIM8RST_Msk

// ------ USART1RST (USART1 Reset) ------ //
/** @brief USART1 Reset Position @def RCC_APB2RSTR_USART1RST_Pos */
#define RCC_APB2RSTR_USART1RST_Pos						((uint8_t) 14U)
/** @brief USART1 Reset Mask @def RCC_APB2RSTR_USART1RST_Msk */
#define RCC_APB2RSTR_USART1RST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_USART1RST_Pos))
/** @brief USART1 Reset @def RCC_APB2RSTR_USART1RST */
#define RCC_APB2RSTR_USART1RST							RCC_APB2RSTR_USART1RST_Msk

// ------ ADC3RST (ADC 3 Reset) ------ //
/** @brief ADC 3 Reset Position @def RCC_APB2RSTR_ADC3RST_Pos */
#define RCC_APB2RSTR_ADC3RST_Pos						((uint8_t) 15U)
/** @brief ADC 3 Reset Mask @def RCC_APB2RSTR_ADC3RST_Msk */
#define RCC_APB2RSTR_ADC3RST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_ADC3RST_Pos))
/** @brief ADC 3 Reset @def RCC_APB2RSTR_ADC3RST */
#define RCC_APB2RSTR_ADC3RST							RCC_APB2RSTR_ADC3RST_Msk

// ------ TIM9RST (TIM9 Timer Reset) ------ // 
/** @brief TIM9 Timer Reset Position @def RCC_APB2RSTR_TIM9RST_Pos */
#define RCC_APB2RSTR_TIM9RST_Pos						((uint8_t) 19U)
/** @brief TIM9 Timer Reset Mask @def RCC_APB2RSTR_TIM9RST_Msk */
#define RCC_APB2RSTR_TIM9RST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_TIM9RST_Pos))
/** @brief TIM9 Timer Reset @def RCC_APB2RSTR_TIM9RST */
#define RCC_APB2RSTR_TIM9RST							RCC_APB2RSTR_TIM9RST_Msk

// ------ TIM10RST (TIM10 Timer Reset) ------ // 
/** @brief TIM10 Timer Reset Position @def RCC_APB2RSTR_TIM10RST_Pos */
#define RCC_APB2RSTR_TIM10RST_Pos						((uint8_t) 20U)
/** @brief TIM10 Timer Reset Mask @def RCC_APB2RSTR_TIM10RST_Msk */
#define RCC_APB2RSTR_TIM10RST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_TIM10RST_Pos))
/** @brief TIM10 Timer Reset @def RCC_APB2RSTR_TIM10RST */
#define RCC_APB2RSTR_TIM10RST							RCC_APB2RSTR_TIM10RST_Msk

// ------ TIM11RST (TIM11 Timer Reset) ------ // 
/** @brief TIM11 Timer Reset Position @def RCC_APB2RSTR_TIM11RST_Pos */
#define RCC_APB2RSTR_TIM11RST_Pos						((uint8_t) 21U)
/** @brief TIM11 Timer Reset Mask @def RCC_APB2RSTR_TIM11RST_Msk */
#define RCC_APB2RSTR_TIM11RST_Msk						((uint32_t)(0x01UL << RCC_APB2RSTR_TIM11RST_Pos))
/** @brief TIM11 Timer Reset @def RCC_APB2RSTR_TIM11RST */
#define RCC_APB2RSTR_TIM11RST							RCC_APB2RSTR_TIM11RST_Msk

/** @} */ // RCC_APB2RSTR

// ------------------------------------------------------------------------------------------
// RCC Structure
// ------------------------------------------------------------------------------------------ 

/**
 * @addtogroup RCC_01_Registers_01_Structure
 * @{
 * @details
 * - This structure represents the complete register set for RCC peripheral
 * - It is memory-mapped to the RCC base address
 * @note The structure uses unions to provide both bit-level and register-level access
 * @see Reference Manual RM0008 - Section 7.3 RCC registers (Page 113) 
 * @typedef RCC_TypeDef
 */
typedef volatile struct _RCC_TypeDef
{
	/**
	 * @brief Clock Control Register
	 * @details
	 * Controls the internal and external clock sources including HSI, HSE, and PLL.
	 * Manages oscillator enable/disable, ready status, calibration, and clock security system.
	 * This register must be configured before any clock switching operations.
	 */
	union RCC_CR
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t HSION: 1;
			volatile uint32_t HSIRDY: 1;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t HSITRIM: 5;
			volatile uint32_t HSICAL: 8;
			volatile uint32_t HSEON: 1;
			volatile uint32_t HSERDY: 1;
			volatile uint32_t HSEBYP: 1;
			volatile uint32_t CSSON: 1;
			volatile uint32_t reserved_2: 4;
			volatile uint32_t PLLON: 1;
			volatile uint32_t PLLRDY: 1;
			volatile uint32_t reserved_3: 6;
		} BIT;
	} CR;

	/**
	 * @brief Clock Configuration Register  
	 * @details
	 * Configures the system clock source, prescalers for AHB, APB1, APB2 buses,
	 * PLL multiplication factor, and clock output selection. This register determines
	 * the final system clock frequency and peripheral clock speeds.
	 */
	union RCC_CFGR 
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t SW: 2;
			volatile uint32_t SWS: 2;
			volatile uint32_t HPRE: 4;
			volatile uint32_t PPRE1: 3;
			volatile uint32_t PPRE2: 3;
			volatile uint32_t ADCPRE: 2;
			volatile uint32_t PLLSRC: 1;
			volatile uint32_t PLLXTPRE: 1;
			volatile uint32_t PLLMUL: 4;
			volatile uint32_t USBPRE: 1;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t MCO: 3;
			volatile uint32_t reserved_2: 5;
		} BIT;
	} CFGR;

	/**
	 * @brief Clock Interrupt Register
	 * @details
	 * Manages interrupt flags and enable bits for various clock events including
	 * oscillator ready flags, PLL lock, and clock security system interrupts.
	 * Provides clear bits to reset interrupt flags.
	 */
	union RCC_CIR 
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t LSIRDYF: 1;
			volatile uint32_t LSERDYF: 1;
			volatile uint32_t HSIRDYF: 1;
			volatile uint32_t HSERDYF: 1;
			volatile uint32_t PLLRDYF: 1;
			volatile uint32_t reserved_1: 2;
			volatile uint32_t CSFF: 1;
			volatile uint32_t LSIRDYIE: 1;
			volatile uint32_t LSERDYIE: 1;
			volatile uint32_t HSIRDYIE: 1;
			volatile uint32_t HSERDYIE: 1;
			volatile uint32_t PLLRDYIE: 1;
			volatile uint32_t reserved_2: 3;
			volatile uint32_t LSIRDYC: 1;
			volatile uint32_t LSERDYC: 1;
			volatile uint32_t HSIRDYC: 1;
			volatile uint32_t HSERDYC: 1;
			volatile uint32_t PLLRDYC: 1;
			volatile uint32_t reserved_3: 2;
			volatile uint32_t CSSC: 1;
			volatile uint32_t reserved_4: 8;
		} BIT;
	} CIR;

	/**
	 * @brief APB2 Peripheral Reset Register
	 * @details
	 * Controls the reset functionality for peripherals connected to APB2 bus.
	 * Writing 1 to any bit asserts reset for the corresponding peripheral,
	 * writing 0 releases reset. Includes GPIO ports, ADC, TIM1, SPI1, USART1.
	 */
	union RCC_APB2RSTR 
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t AFIORST: 1;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t IOPARST: 1;
			volatile uint32_t IOPBRST: 1;
			volatile uint32_t IOPCRST: 1;
			volatile uint32_t IOPDRST: 1;
			volatile uint32_t IOPERST: 1;
			volatile uint32_t IOPFRST: 1;
			volatile uint32_t IOPGRST: 1;
			volatile uint32_t ADC1RST: 1;
			volatile uint32_t ADC2RST: 1;
			volatile uint32_t TIM1RST: 1;
			volatile uint32_t SPI1RST: 1;
			volatile uint32_t TIM8RST: 1;
			volatile uint32_t USART1RST: 1;
			volatile uint32_t ADC3RST: 1;
			volatile uint32_t reserved_2: 3;
			volatile uint32_t TIM9RST: 1;
			volatile uint32_t TIM10RST: 1;
			volatile uint32_t TIM11RST: 1;
			volatile uint32_t reserved_3: 10;
		} BIT;
	} APB2RSTR;

	/**
	 * @brief APB1 Peripheral Reset Register
	 * @details
	 * Controls the reset functionality for peripherals connected to APB1 bus.
	 * Writing 1 to any bit asserts reset for the corresponding peripheral,
	 * writing 0 releases reset. Includes timers, watchdogs, SPI, USART, I2C, USB, CAN.
	 */
	union RCC_APB1RSTR
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t TIM2RST: 1;
			volatile uint32_t TIM3RST: 1;
			volatile uint32_t TIM4RST: 1;
			volatile uint32_t TIM5RST: 1;
			volatile uint32_t TIM6RST: 1;
			volatile uint32_t TIM7RST: 1;
			volatile uint32_t TIM12RST: 1;
			volatile uint32_t TIM13RST: 1;
			volatile uint32_t TIM14RST: 1;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t WWDGRST: 1;
			volatile uint32_t reserved_2: 2;
			volatile uint32_t SPI2RST: 1;
			volatile uint32_t SPI3RST: 1;
			volatile uint32_t reserved_3: 1;
			volatile uint32_t USART2RST: 1;
			volatile uint32_t USART3RST: 1;
			volatile uint32_t UART4RST: 1;
			volatile uint32_t UART5RST: 1;
			volatile uint32_t I2C1RST: 1;
			volatile uint32_t I2C2RST: 1;
			volatile uint32_t USBRST: 1;
			volatile uint32_t reserved_4: 1;
			volatile uint32_t CANRST: 1;
			volatile uint32_t reserved_5: 1;
			volatile uint32_t BKPRST: 1;
			volatile uint32_t PWRRST: 1;
			volatile uint32_t DACRST: 1;
			volatile uint32_t reserved_6: 2;
		} BIT;
	} APB1RSTR;

	/**
	 * @brief AHB Peripheral Clock Enable Register
	 * @details
	 * Controls clock gating for peripherals connected to AHB bus.
	 * Enables or disables clocks to DMA, SRAM, FLASH, CRC, FSMC, and SDIO peripherals.
	 * Disabling unused peripheral clocks reduces power consumption.
	 */
	union RCC_AHBENR
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t DMA1EN: 1;
			volatile uint32_t DMA2EN: 1;
			volatile uint32_t SRAMEN: 1;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t FLITFEN: 1;
			volatile uint32_t reserved_2: 1;
			volatile uint32_t CRCEN: 1;
			volatile uint32_t reserved_3: 1;
			volatile uint32_t FSMCEN: 1;
			volatile uint32_t reserved_4: 1;
			volatile uint32_t SDIOEN: 1;
			volatile uint32_t reserved_5: 21;
		} BIT;
	} AHBENR;

	/**
	 * @brief APB2 Peripheral Clock Enable Register
	 * @details
	 * Controls clock gating for peripherals connected to APB2 bus.
	 * Enables or disables clocks to AFIO, GPIO ports, ADC, advanced timers,
	 * SPI1, and USART1. Essential for GPIO and communication peripheral operation.
	 */
	union RCC_APB2ENR
	{
		// Full 32-bit Register Access
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t AFIOEN: 1;
			volatile uint32_t reserved_1: 1;
			volatile uint32_t IOPAEN: 1;
			volatile uint32_t IOPBEN: 1;
			volatile uint32_t IOPCEN: 1;
			volatile uint32_t IOPDEN: 1;
			volatile uint32_t IOPEEN: 1;
			volatile uint32_t IOPFEN: 1;
			volatile uint32_t IOPGEN: 1;
			volatile uint32_t ADC1EN: 1;
			volatile uint32_t ADC2EN: 1;
			volatile uint32_t TIM1EN: 1;
			volatile uint32_t SPI1EN: 1;
			volatile uint32_t TIM8EN: 1;
			volatile uint32_t USART1EN: 1;
			volatile uint32_t ADC3EN: 1;
			volatile uint32_t reserved_2: 3;
			volatile uint32_t TIM9EN: 1;
			volatile uint32_t TIM10EN: 1;
			volatile uint32_t TIM11EN: 1;
			volatile uint32_t reserved_3: 10;
		} BIT;
	} APB2ENR;
	/**
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
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t TIM2EN: 1;
			volatile uint32_t TIM3EN: 1;
			volatile uint32_t TIM4EN: 1;
			volatile uint32_t TIM5EN: 1;
			volatile uint32_t TIM6EN: 1;
			volatile uint32_t TIM7EN: 1;
			volatile uint32_t TIM12EN: 1;
			volatile uint32_t TIM13EN: 1;
			volatile uint32_t TIM14EN: 1;
			volatile uint32_t reserved_1: 2;
			volatile uint32_t WWDGEN: 1;
			volatile uint32_t reserved_2: 2;
			volatile uint32_t SPI2EN: 1;
			volatile uint32_t SPI3EN: 1;
			volatile uint32_t reserved_3: 1;
			volatile uint32_t USART2EN: 1;
			volatile uint32_t USART3EN: 1;
			volatile uint32_t UART4EN: 1;
			volatile uint32_t UART5EN: 1;
			volatile uint32_t I2C1EN: 1;
			volatile uint32_t I2C2EN: 1;
			volatile uint32_t USBEN: 1;
			volatile uint32_t reserved_4: 1;
			volatile uint32_t CANEN: 1;
			volatile uint32_t reserved_5: 1;
			volatile uint32_t BKPEN: 1;
			volatile uint32_t PWREN: 1;
			volatile uint32_t DACEN: 1;
			volatile uint32_t reserved_6: 2;
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
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t LSEON: 1;
			volatile uint32_t LSERDY: 1;
			volatile uint32_t LSEBYP: 1;
			volatile uint32_t reserved_1: 5;
			volatile uint32_t RTCSEL: 2;
			volatile uint32_t reserved_2: 5;
			volatile uint32_t RTCEN: 2;
			volatile uint32_t BDRST: 2;
			volatile uint32_t reserved_3: 15;
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
		volatile uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t LSION: 1;
			volatile uint32_t LSIRDY: 1;
			volatile uint32_t reserved_1: 22;
			volatile uint32_t RMVF: 1;
			volatile uint32_t reserved_2: 1;
			volatile uint32_t PINRSTF: 1;
			volatile uint32_t PORRSTF: 1;
			volatile uint32_t SFTRSTF: 1;
			volatile uint32_t IWDGRSTF: 1;
			volatile uint32_t WWDGRSTF: 1;
			volatile uint32_t LPWRRSTF: 1;
		} BIT;
	} CSR;
} RCC_TypeDef;

/** @} */ // RCC_01_Registers_01_Structure

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_RCC_H_ */
