/**
 * @file stm32f1xx_scb.h
 * @author Shrey Shah
 * @brief STM32F1 System Control Block Register-Layer Definitions
 * @version v1.1
 * @date 16-08-2026
 */

// Header Guards
#ifndef STM32F1XX_SCB_H_
#define STM32F1XX_SCB_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx_utils.h"

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup SCB System Control Block (SCB)
 * @ingroup STM32F1xx
 * @brief Cortex-M3 system exception, vector, fault, reset, sleep, and priority-group control
 * @details
 * This module owns the raw register fields and memory map of the Cortex-M3
 * System Control Block. NVIC priority code consumes
 * `SCB_AIRCR_PRIGROUP_Pos` and `SCB_AIRCR_PRIGROUP_Msk`, but AIRCR and every
 * `SCB_xxx` symbol remain SCB-owned.
 */

/**
 * @defgroup SCB_01_RegisterLayer SCB Register Layer
 * @ingroup SCB
 * @brief Raw Cortex-M3 SCB register fields and memory-mapped structure
 * @details
 * This layer owns hardware-visible SCB positions, masks, and register layout.
 * Higher layers may consume these symbols without transferring ownership.
 */

/**
 * @addtogroup SCB_01_RegisterLayer
 * @{
 */

// ==================================================================================================== //
//										SCB Register Defines											//
// ==================================================================================================== //

/**
 * @defgroup SCB_01_RegisterLayer_00_RegisterDefines SCB Register Field Definitions
 * @ingroup SCB_01_RegisterLayer
 * @brief Raw Cortex-M3 System Control Block register-field definitions
 * @details
 * Fields are grouped by owning hardware register and ordered from the least-
 * significant implemented bit toward the most-significant implemented bit.
 * Single-bit fields expose `_Pos`, `_Msk`, and an unsuffixed mask alias;
 * multi-bit fields additionally expose `_Width`. Existing `_Pos` and `_Msk`
 * identifiers remain available through this SCB-owned header.
 * @{
 */

// ---------------------------------------------------------------------------------------------------- //
//											SCB_CPUID											//
// ---------------------------------------------------------------------------------------------------- //
/** @brief Revision number (`SCB_CPUID.REVISION[3:0]`) field position @def SCB_CPUID_REVISION_Pos */
#define SCB_CPUID_REVISION_Pos			((reg_bit_pos_t) 0U)
/** @brief Revision number (`SCB_CPUID.REVISION[3:0]`) field width @def SCB_CPUID_REVISION_Width */
#define SCB_CPUID_REVISION_Width		((reg_field_width_t) 4U)
/** @brief Revision number (`SCB_CPUID.REVISION[3:0]`) field mask @def SCB_CPUID_REVISION_Msk */
#define SCB_CPUID_REVISION_Msk			REG_FIELD_MASK(SCB_CPUID_REVISION_Pos, SCB_CPUID_REVISION_Width)
/** @brief Revision number (`SCB_CPUID.REVISION[3:0]`) field mask alias @def SCB_CPUID_REVISION */
#define SCB_CPUID_REVISION			SCB_CPUID_REVISION_Msk

/** @brief Processor part number (`SCB_CPUID.PARTNO[15:4]`) field position @def SCB_CPUID_PARTNO_Pos */
#define SCB_CPUID_PARTNO_Pos			((reg_bit_pos_t) 4U)
/** @brief Processor part number (`SCB_CPUID.PARTNO[15:4]`) field width @def SCB_CPUID_PARTNO_Width */
#define SCB_CPUID_PARTNO_Width			((reg_field_width_t) 12U)
/** @brief Processor part number (`SCB_CPUID.PARTNO[15:4]`) field mask @def SCB_CPUID_PARTNO_Msk */
#define SCB_CPUID_PARTNO_Msk			REG_FIELD_MASK(SCB_CPUID_PARTNO_Pos, SCB_CPUID_PARTNO_Width)
/** @brief Processor part number (`SCB_CPUID.PARTNO[15:4]`) field mask alias @def SCB_CPUID_PARTNO */
#define SCB_CPUID_PARTNO			SCB_CPUID_PARTNO_Msk

/** @brief Architecture identifier (`SCB_CPUID.ARCHITECTURE[19:16]`) field position @def SCB_CPUID_ARCHITECTURE_Pos */
#define SCB_CPUID_ARCHITECTURE_Pos		((reg_bit_pos_t) 16U)
/** @brief Architecture identifier (`SCB_CPUID.ARCHITECTURE[19:16]`) field width @def SCB_CPUID_ARCHITECTURE_Width */
#define SCB_CPUID_ARCHITECTURE_Width		((reg_field_width_t) 4U)
/** @brief Architecture identifier (`SCB_CPUID.ARCHITECTURE[19:16]`) field mask @def SCB_CPUID_ARCHITECTURE_Msk */
#define SCB_CPUID_ARCHITECTURE_Msk		REG_FIELD_MASK(SCB_CPUID_ARCHITECTURE_Pos, SCB_CPUID_ARCHITECTURE_Width)
/** @brief Architecture identifier (`SCB_CPUID.ARCHITECTURE[19:16]`) field mask alias @def SCB_CPUID_ARCHITECTURE */
#define SCB_CPUID_ARCHITECTURE			SCB_CPUID_ARCHITECTURE_Msk

/** @brief Processor variant number (`SCB_CPUID.VARIANT[23:20]`) field position @def SCB_CPUID_VARIANT_Pos */
#define SCB_CPUID_VARIANT_Pos			((reg_bit_pos_t) 20U)
/** @brief Processor variant number (`SCB_CPUID.VARIANT[23:20]`) field width @def SCB_CPUID_VARIANT_Width */
#define SCB_CPUID_VARIANT_Width			((reg_field_width_t) 4U)
/** @brief Processor variant number (`SCB_CPUID.VARIANT[23:20]`) field mask @def SCB_CPUID_VARIANT_Msk */
#define SCB_CPUID_VARIANT_Msk			REG_FIELD_MASK(SCB_CPUID_VARIANT_Pos, SCB_CPUID_VARIANT_Width)
/** @brief Processor variant number (`SCB_CPUID.VARIANT[23:20]`) field mask alias @def SCB_CPUID_VARIANT */
#define SCB_CPUID_VARIANT			SCB_CPUID_VARIANT_Msk

/** @brief Implementer identifier (`SCB_CPUID.IMPLEMENTER[31:24]`) field position @def SCB_CPUID_IMPLEMENTER_Pos */
#define SCB_CPUID_IMPLEMENTER_Pos		((reg_bit_pos_t) 24U)
/** @brief Implementer identifier (`SCB_CPUID.IMPLEMENTER[31:24]`) field width @def SCB_CPUID_IMPLEMENTER_Width */
#define SCB_CPUID_IMPLEMENTER_Width		((reg_field_width_t) 8U)
/** @brief Implementer identifier (`SCB_CPUID.IMPLEMENTER[31:24]`) field mask @def SCB_CPUID_IMPLEMENTER_Msk */
#define SCB_CPUID_IMPLEMENTER_Msk		REG_FIELD_MASK(SCB_CPUID_IMPLEMENTER_Pos, SCB_CPUID_IMPLEMENTER_Width)
/** @brief Implementer identifier (`SCB_CPUID.IMPLEMENTER[31:24]`) field mask alias @def SCB_CPUID_IMPLEMENTER */
#define SCB_CPUID_IMPLEMENTER			SCB_CPUID_IMPLEMENTER_Msk

// ---------------------------------------------------------------------------------------------------- //
//											SCB_ICSR											//
// ---------------------------------------------------------------------------------------------------- //
/** @brief Active exception number (`SCB_ICSR.VECTACTIVE[8:0]`) field position @def SCB_ICSR_VECTACTIVE_Pos */
#define SCB_ICSR_VECTACTIVE_Pos			((reg_bit_pos_t) 0U)
/** @brief Active exception number (`SCB_ICSR.VECTACTIVE[8:0]`) field width @def SCB_ICSR_VECTACTIVE_Width */
#define SCB_ICSR_VECTACTIVE_Width		((reg_field_width_t) 9U)
/** @brief Active exception number (`SCB_ICSR.VECTACTIVE[8:0]`) field mask @def SCB_ICSR_VECTACTIVE_Msk */
#define SCB_ICSR_VECTACTIVE_Msk			REG_FIELD_MASK(SCB_ICSR_VECTACTIVE_Pos, SCB_ICSR_VECTACTIVE_Width)
/** @brief Active exception number (`SCB_ICSR.VECTACTIVE[8:0]`) field mask alias @def SCB_ICSR_VECTACTIVE */
#define SCB_ICSR_VECTACTIVE			SCB_ICSR_VECTACTIVE_Msk

/** @brief Return-to-base state (`SCB_ICSR.RETTOBASE`) bit position @def SCB_ICSR_RETTOBASE_Pos */
#define SCB_ICSR_RETTOBASE_Pos			((reg_bit_pos_t) 11U)
/** @brief Return-to-base state (`SCB_ICSR.RETTOBASE`) bit mask @def SCB_ICSR_RETTOBASE_Msk */
#define SCB_ICSR_RETTOBASE_Msk			REG_BIT_MASK(SCB_ICSR_RETTOBASE_Pos)
/** @brief Return-to-base state (`SCB_ICSR.RETTOBASE`) bit mask alias @def SCB_ICSR_RETTOBASE */
#define SCB_ICSR_RETTOBASE			SCB_ICSR_RETTOBASE_Msk

/** @brief Highest-priority pending exception number (`SCB_ICSR.VECTPENDING[20:12]`) field position @def SCB_ICSR_VECTPENDING_Pos */
#define SCB_ICSR_VECTPENDING_Pos		((reg_bit_pos_t) 12U)
/** @brief Highest-priority pending exception number (`SCB_ICSR.VECTPENDING[20:12]`) field width @def SCB_ICSR_VECTPENDING_Width */
#define SCB_ICSR_VECTPENDING_Width		((reg_field_width_t) 9U)
/** @brief Highest-priority pending exception number (`SCB_ICSR.VECTPENDING[20:12]`) field mask @def SCB_ICSR_VECTPENDING_Msk */
#define SCB_ICSR_VECTPENDING_Msk		REG_FIELD_MASK(SCB_ICSR_VECTPENDING_Pos, SCB_ICSR_VECTPENDING_Width)
/** @brief Highest-priority pending exception number (`SCB_ICSR.VECTPENDING[20:12]`) field mask alias @def SCB_ICSR_VECTPENDING */
#define SCB_ICSR_VECTPENDING			SCB_ICSR_VECTPENDING_Msk

/** @brief External interrupt pending state (`SCB_ICSR.ISRPENDING`) bit position @def SCB_ICSR_ISRPENDING_Pos */
#define SCB_ICSR_ISRPENDING_Pos			((reg_bit_pos_t) 22U)
/** @brief External interrupt pending state (`SCB_ICSR.ISRPENDING`) bit mask @def SCB_ICSR_ISRPENDING_Msk */
#define SCB_ICSR_ISRPENDING_Msk			REG_BIT_MASK(SCB_ICSR_ISRPENDING_Pos)
/** @brief External interrupt pending state (`SCB_ICSR.ISRPENDING`) bit mask alias @def SCB_ICSR_ISRPENDING */
#define SCB_ICSR_ISRPENDING			SCB_ICSR_ISRPENDING_Msk

/** @brief Pending interrupt preemption state (`SCB_ICSR.ISRPREEMPT`) bit position @def SCB_ICSR_ISRPREEMPT_Pos */
#define SCB_ICSR_ISRPREEMPT_Pos			((reg_bit_pos_t) 23U)
/** @brief Pending interrupt preemption state (`SCB_ICSR.ISRPREEMPT`) bit mask @def SCB_ICSR_ISRPREEMPT_Msk */
#define SCB_ICSR_ISRPREEMPT_Msk			REG_BIT_MASK(SCB_ICSR_ISRPREEMPT_Pos)
/** @brief Pending interrupt preemption state (`SCB_ICSR.ISRPREEMPT`) bit mask alias @def SCB_ICSR_ISRPREEMPT */
#define SCB_ICSR_ISRPREEMPT			SCB_ICSR_ISRPREEMPT_Msk

/** @brief SysTick pending-clear action (`SCB_ICSR.PENDSTCLR`) bit position @def SCB_ICSR_PENDSTCLR_Pos */
#define SCB_ICSR_PENDSTCLR_Pos			((reg_bit_pos_t) 25U)
/** @brief SysTick pending-clear action (`SCB_ICSR.PENDSTCLR`) bit mask @def SCB_ICSR_PENDSTCLR_Msk */
#define SCB_ICSR_PENDSTCLR_Msk			REG_BIT_MASK(SCB_ICSR_PENDSTCLR_Pos)
/** @brief SysTick pending-clear action (`SCB_ICSR.PENDSTCLR`) bit mask alias @def SCB_ICSR_PENDSTCLR */
#define SCB_ICSR_PENDSTCLR			SCB_ICSR_PENDSTCLR_Msk

/** @brief SysTick pending-set state and action (`SCB_ICSR.PENDSTSET`) bit position @def SCB_ICSR_PENDSTSET_Pos */
#define SCB_ICSR_PENDSTSET_Pos			((reg_bit_pos_t) 26U)
/** @brief SysTick pending-set state and action (`SCB_ICSR.PENDSTSET`) bit mask @def SCB_ICSR_PENDSTSET_Msk */
#define SCB_ICSR_PENDSTSET_Msk			REG_BIT_MASK(SCB_ICSR_PENDSTSET_Pos)
/** @brief SysTick pending-set state and action (`SCB_ICSR.PENDSTSET`) bit mask alias @def SCB_ICSR_PENDSTSET */
#define SCB_ICSR_PENDSTSET			SCB_ICSR_PENDSTSET_Msk

/** @brief PendSV pending-clear action (`SCB_ICSR.PENDSVCLR`) bit position @def SCB_ICSR_PENDSVCLR_Pos */
#define SCB_ICSR_PENDSVCLR_Pos			((reg_bit_pos_t) 27U)
/** @brief PendSV pending-clear action (`SCB_ICSR.PENDSVCLR`) bit mask @def SCB_ICSR_PENDSVCLR_Msk */
#define SCB_ICSR_PENDSVCLR_Msk			REG_BIT_MASK(SCB_ICSR_PENDSVCLR_Pos)
/** @brief PendSV pending-clear action (`SCB_ICSR.PENDSVCLR`) bit mask alias @def SCB_ICSR_PENDSVCLR */
#define SCB_ICSR_PENDSVCLR			SCB_ICSR_PENDSVCLR_Msk

/** @brief PendSV pending-set state and action (`SCB_ICSR.PENDSVSET`) bit position @def SCB_ICSR_PENDSVSET_Pos */
#define SCB_ICSR_PENDSVSET_Pos			((reg_bit_pos_t) 28U)
/** @brief PendSV pending-set state and action (`SCB_ICSR.PENDSVSET`) bit mask @def SCB_ICSR_PENDSVSET_Msk */
#define SCB_ICSR_PENDSVSET_Msk			REG_BIT_MASK(SCB_ICSR_PENDSVSET_Pos)
/** @brief PendSV pending-set state and action (`SCB_ICSR.PENDSVSET`) bit mask alias @def SCB_ICSR_PENDSVSET */
#define SCB_ICSR_PENDSVSET			SCB_ICSR_PENDSVSET_Msk

/** @brief NMI pending-set state and action (`SCB_ICSR.NMIPENDSET`) bit position @def SCB_ICSR_NMIPENDSET_Pos */
#define SCB_ICSR_NMIPENDSET_Pos			((reg_bit_pos_t) 31U)
/** @brief NMI pending-set state and action (`SCB_ICSR.NMIPENDSET`) bit mask @def SCB_ICSR_NMIPENDSET_Msk */
#define SCB_ICSR_NMIPENDSET_Msk			REG_BIT_MASK(SCB_ICSR_NMIPENDSET_Pos)
/** @brief NMI pending-set state and action (`SCB_ICSR.NMIPENDSET`) bit mask alias @def SCB_ICSR_NMIPENDSET */
#define SCB_ICSR_NMIPENDSET			SCB_ICSR_NMIPENDSET_Msk

// ---------------------------------------------------------------------------------------------------- //
//											SCB_VTOR											//
// ---------------------------------------------------------------------------------------------------- //
#if !defined(__CM3_REV) || (__CM3_REV < 0x0201U)
/** @brief Vector table offset (`SCB_VTOR.TBLOFF[28:7]`) field position @def SCB_VTOR_TBLOFF_Pos */
#define SCB_VTOR_TBLOFF_Pos		((reg_bit_pos_t) 7U)
/** @brief Vector table offset (`SCB_VTOR.TBLOFF[28:7]`) field width @def SCB_VTOR_TBLOFF_Width */
#define SCB_VTOR_TBLOFF_Width		((reg_field_width_t) 22U)
/** @brief Vector table offset (`SCB_VTOR.TBLOFF[28:7]`) field mask @def SCB_VTOR_TBLOFF_Msk */
#define SCB_VTOR_TBLOFF_Msk		REG_FIELD_MASK(SCB_VTOR_TBLOFF_Pos, SCB_VTOR_TBLOFF_Width)
/** @brief Vector table offset (`SCB_VTOR.TBLOFF[28:7]`) field mask alias @def SCB_VTOR_TBLOFF */
#define SCB_VTOR_TBLOFF			SCB_VTOR_TBLOFF_Msk

/** @brief Vector table memory-region selection (`SCB_VTOR.TBLBASE`) bit position @def SCB_VTOR_TBLBASE_Pos */
#define SCB_VTOR_TBLBASE_Pos		((reg_bit_pos_t) 29U)
/** @brief Vector table memory-region selection (`SCB_VTOR.TBLBASE`) bit mask @def SCB_VTOR_TBLBASE_Msk */
#define SCB_VTOR_TBLBASE_Msk		REG_BIT_MASK(SCB_VTOR_TBLBASE_Pos)
/** @brief Vector table memory-region selection (`SCB_VTOR.TBLBASE`) bit mask alias @def SCB_VTOR_TBLBASE */
#define SCB_VTOR_TBLBASE		SCB_VTOR_TBLBASE_Msk
#else
/** @brief Vector table offset (`SCB_VTOR.TBLOFF[31:7]`) field position @def SCB_VTOR_TBLOFF_Pos */
#define SCB_VTOR_TBLOFF_Pos		((reg_bit_pos_t) 7U)
/** @brief Vector table offset (`SCB_VTOR.TBLOFF[31:7]`) field width @def SCB_VTOR_TBLOFF_Width */
#define SCB_VTOR_TBLOFF_Width		((reg_field_width_t) 25U)
/** @brief Vector table offset (`SCB_VTOR.TBLOFF[31:7]`) field mask @def SCB_VTOR_TBLOFF_Msk */
#define SCB_VTOR_TBLOFF_Msk		REG_FIELD_MASK(SCB_VTOR_TBLOFF_Pos, SCB_VTOR_TBLOFF_Width)
/** @brief Vector table offset (`SCB_VTOR.TBLOFF[31:7]`) field mask alias @def SCB_VTOR_TBLOFF */
#define SCB_VTOR_TBLOFF			SCB_VTOR_TBLOFF_Msk
#endif /* !defined(__CM3_REV) || (__CM3_REV < 0x0201U) */

// ---------------------------------------------------------------------------------------------------- //
//											SCB_AIRCR											//
// ---------------------------------------------------------------------------------------------------- //
/** @brief Local system-reset request (`SCB_AIRCR.VECTRESET`) bit position @def SCB_AIRCR_VECTRESET_Pos */
#define SCB_AIRCR_VECTRESET_Pos			((reg_bit_pos_t) 0U)
/** @brief Local system-reset request (`SCB_AIRCR.VECTRESET`) bit mask @def SCB_AIRCR_VECTRESET_Msk */
#define SCB_AIRCR_VECTRESET_Msk			REG_BIT_MASK(SCB_AIRCR_VECTRESET_Pos)
/** @brief Local system-reset request (`SCB_AIRCR.VECTRESET`) bit mask alias @def SCB_AIRCR_VECTRESET */
#define SCB_AIRCR_VECTRESET			SCB_AIRCR_VECTRESET_Msk

/** @brief Active exception-state clear request (`SCB_AIRCR.VECTCLRACTIVE`) bit position @def SCB_AIRCR_VECTCLRACTIVE_Pos */
#define SCB_AIRCR_VECTCLRACTIVE_Pos		((reg_bit_pos_t) 1U)
/** @brief Active exception-state clear request (`SCB_AIRCR.VECTCLRACTIVE`) bit mask @def SCB_AIRCR_VECTCLRACTIVE_Msk */
#define SCB_AIRCR_VECTCLRACTIVE_Msk		REG_BIT_MASK(SCB_AIRCR_VECTCLRACTIVE_Pos)
/** @brief Active exception-state clear request (`SCB_AIRCR.VECTCLRACTIVE`) bit mask alias @def SCB_AIRCR_VECTCLRACTIVE */
#define SCB_AIRCR_VECTCLRACTIVE			SCB_AIRCR_VECTCLRACTIVE_Msk

/** @brief System-reset request (`SCB_AIRCR.SYSRESETREQ`) bit position @def SCB_AIRCR_SYSRESETREQ_Pos */
#define SCB_AIRCR_SYSRESETREQ_Pos		((reg_bit_pos_t) 2U)
/** @brief System-reset request (`SCB_AIRCR.SYSRESETREQ`) bit mask @def SCB_AIRCR_SYSRESETREQ_Msk */
#define SCB_AIRCR_SYSRESETREQ_Msk		REG_BIT_MASK(SCB_AIRCR_SYSRESETREQ_Pos)
/** @brief System-reset request (`SCB_AIRCR.SYSRESETREQ`) bit mask alias @def SCB_AIRCR_SYSRESETREQ */
#define SCB_AIRCR_SYSRESETREQ			SCB_AIRCR_SYSRESETREQ_Msk

/** @brief Priority grouping selection (`SCB_AIRCR.PRIGROUP[10:8]`) field position @def SCB_AIRCR_PRIGROUP_Pos */
#define SCB_AIRCR_PRIGROUP_Pos			((reg_bit_pos_t) 8U)
/** @brief Priority grouping selection (`SCB_AIRCR.PRIGROUP[10:8]`) field width @def SCB_AIRCR_PRIGROUP_Width */
#define SCB_AIRCR_PRIGROUP_Width		((reg_field_width_t) 3U)
/** @brief Priority grouping selection (`SCB_AIRCR.PRIGROUP[10:8]`) field mask @def SCB_AIRCR_PRIGROUP_Msk */
#define SCB_AIRCR_PRIGROUP_Msk			REG_FIELD_MASK(SCB_AIRCR_PRIGROUP_Pos, SCB_AIRCR_PRIGROUP_Width)
/** @brief Priority grouping selection (`SCB_AIRCR.PRIGROUP[10:8]`) field mask alias @def SCB_AIRCR_PRIGROUP */
#define SCB_AIRCR_PRIGROUP			SCB_AIRCR_PRIGROUP_Msk

/** @brief Data endianness state (`SCB_AIRCR.ENDIANESS`) bit position @def SCB_AIRCR_ENDIANESS_Pos */
#define SCB_AIRCR_ENDIANESS_Pos			((reg_bit_pos_t) 15U)
/** @brief Data endianness state (`SCB_AIRCR.ENDIANESS`) bit mask @def SCB_AIRCR_ENDIANESS_Msk */
#define SCB_AIRCR_ENDIANESS_Msk			REG_BIT_MASK(SCB_AIRCR_ENDIANESS_Pos)
/** @brief Data endianness state (`SCB_AIRCR.ENDIANESS`) bit mask alias @def SCB_AIRCR_ENDIANESS */
#define SCB_AIRCR_ENDIANESS			SCB_AIRCR_ENDIANESS_Msk

/** @brief Write access key (`SCB_AIRCR.VECTKEY[31:16]`) field position @def SCB_AIRCR_VECTKEY_Pos */
#define SCB_AIRCR_VECTKEY_Pos			((reg_bit_pos_t) 16U)
/** @brief Write access key (`SCB_AIRCR.VECTKEY[31:16]`) field width @def SCB_AIRCR_VECTKEY_Width */
#define SCB_AIRCR_VECTKEY_Width			((reg_field_width_t) 16U)
/** @brief Write access key (`SCB_AIRCR.VECTKEY[31:16]`) field mask @def SCB_AIRCR_VECTKEY_Msk */
#define SCB_AIRCR_VECTKEY_Msk			REG_FIELD_MASK(SCB_AIRCR_VECTKEY_Pos, SCB_AIRCR_VECTKEY_Width)
/** @brief Write access key (`SCB_AIRCR.VECTKEY[31:16]`) field mask alias @def SCB_AIRCR_VECTKEY */
#define SCB_AIRCR_VECTKEY			SCB_AIRCR_VECTKEY_Msk

/** @brief Read-side access-key status (`SCB_AIRCR.VECTKEYSTAT[31:16]`) field position @def SCB_AIRCR_VECTKEYSTAT_Pos */
#define SCB_AIRCR_VECTKEYSTAT_Pos		((reg_bit_pos_t) 16U)
/** @brief Read-side access-key status (`SCB_AIRCR.VECTKEYSTAT[31:16]`) field width @def SCB_AIRCR_VECTKEYSTAT_Width */
#define SCB_AIRCR_VECTKEYSTAT_Width		((reg_field_width_t) 16U)
/** @brief Read-side access-key status (`SCB_AIRCR.VECTKEYSTAT[31:16]`) field mask @def SCB_AIRCR_VECTKEYSTAT_Msk */
#define SCB_AIRCR_VECTKEYSTAT_Msk		REG_FIELD_MASK(SCB_AIRCR_VECTKEYSTAT_Pos, SCB_AIRCR_VECTKEYSTAT_Width)
/** @brief Read-side access-key status (`SCB_AIRCR.VECTKEYSTAT[31:16]`) field mask alias @def SCB_AIRCR_VECTKEYSTAT */
#define SCB_AIRCR_VECTKEYSTAT			SCB_AIRCR_VECTKEYSTAT_Msk

// ---------------------------------------------------------------------------------------------------- //
//											SCB_SCR											//
// ---------------------------------------------------------------------------------------------------- //
/** @brief Sleep-on-exception-return control (`SCB_SCR.SLEEPONEXIT`) bit position @def SCB_SCR_SLEEPONEXIT_Pos */
#define SCB_SCR_SLEEPONEXIT_Pos		((reg_bit_pos_t) 1U)
/** @brief Sleep-on-exception-return control (`SCB_SCR.SLEEPONEXIT`) bit mask @def SCB_SCR_SLEEPONEXIT_Msk */
#define SCB_SCR_SLEEPONEXIT_Msk		REG_BIT_MASK(SCB_SCR_SLEEPONEXIT_Pos)
/** @brief Sleep-on-exception-return control (`SCB_SCR.SLEEPONEXIT`) bit mask alias @def SCB_SCR_SLEEPONEXIT */
#define SCB_SCR_SLEEPONEXIT		SCB_SCR_SLEEPONEXIT_Msk

/** @brief Deep-sleep selection (`SCB_SCR.SLEEPDEEP`) bit position @def SCB_SCR_SLEEPDEEP_Pos */
#define SCB_SCR_SLEEPDEEP_Pos		((reg_bit_pos_t) 2U)
/** @brief Deep-sleep selection (`SCB_SCR.SLEEPDEEP`) bit mask @def SCB_SCR_SLEEPDEEP_Msk */
#define SCB_SCR_SLEEPDEEP_Msk		REG_BIT_MASK(SCB_SCR_SLEEPDEEP_Pos)
/** @brief Deep-sleep selection (`SCB_SCR.SLEEPDEEP`) bit mask alias @def SCB_SCR_SLEEPDEEP */
#define SCB_SCR_SLEEPDEEP		SCB_SCR_SLEEPDEEP_Msk

/** @brief Send-event-on-pend control (`SCB_SCR.SEVONPEND`) bit position @def SCB_SCR_SEVONPEND_Pos */
#define SCB_SCR_SEVONPEND_Pos		((reg_bit_pos_t) 4U)
/** @brief Send-event-on-pend control (`SCB_SCR.SEVONPEND`) bit mask @def SCB_SCR_SEVONPEND_Msk */
#define SCB_SCR_SEVONPEND_Msk		REG_BIT_MASK(SCB_SCR_SEVONPEND_Pos)
/** @brief Send-event-on-pend control (`SCB_SCR.SEVONPEND`) bit mask alias @def SCB_SCR_SEVONPEND */
#define SCB_SCR_SEVONPEND		SCB_SCR_SEVONPEND_Msk

// ---------------------------------------------------------------------------------------------------- //
//											SCB_CCR											//
// ---------------------------------------------------------------------------------------------------- //
/** @brief Non-base thread-mode enable (`SCB_CCR.NONBASETHRDENA`) bit position @def SCB_CCR_NONBASETHRDENA_Pos */
#define SCB_CCR_NONBASETHRDENA_Pos		((reg_bit_pos_t) 0U)
/** @brief Non-base thread-mode enable (`SCB_CCR.NONBASETHRDENA`) bit mask @def SCB_CCR_NONBASETHRDENA_Msk */
#define SCB_CCR_NONBASETHRDENA_Msk		REG_BIT_MASK(SCB_CCR_NONBASETHRDENA_Pos)
/** @brief Non-base thread-mode enable (`SCB_CCR.NONBASETHRDENA`) bit mask alias @def SCB_CCR_NONBASETHRDENA */
#define SCB_CCR_NONBASETHRDENA			SCB_CCR_NONBASETHRDENA_Msk

/** @brief Unprivileged software-trigger enable (`SCB_CCR.USERSETMPEND`) bit position @def SCB_CCR_USERSETMPEND_Pos */
#define SCB_CCR_USERSETMPEND_Pos		((reg_bit_pos_t) 1U)
/** @brief Unprivileged software-trigger enable (`SCB_CCR.USERSETMPEND`) bit mask @def SCB_CCR_USERSETMPEND_Msk */
#define SCB_CCR_USERSETMPEND_Msk		REG_BIT_MASK(SCB_CCR_USERSETMPEND_Pos)
/** @brief Unprivileged software-trigger enable (`SCB_CCR.USERSETMPEND`) bit mask alias @def SCB_CCR_USERSETMPEND */
#define SCB_CCR_USERSETMPEND			SCB_CCR_USERSETMPEND_Msk

/** @brief Unaligned-access trap enable (`SCB_CCR.UNALIGN_TRP`) bit position @def SCB_CCR_UNALIGN_TRP_Pos */
#define SCB_CCR_UNALIGN_TRP_Pos			((reg_bit_pos_t) 3U)
/** @brief Unaligned-access trap enable (`SCB_CCR.UNALIGN_TRP`) bit mask @def SCB_CCR_UNALIGN_TRP_Msk */
#define SCB_CCR_UNALIGN_TRP_Msk			REG_BIT_MASK(SCB_CCR_UNALIGN_TRP_Pos)
/** @brief Unaligned-access trap enable (`SCB_CCR.UNALIGN_TRP`) bit mask alias @def SCB_CCR_UNALIGN_TRP */
#define SCB_CCR_UNALIGN_TRP			SCB_CCR_UNALIGN_TRP_Msk

/** @brief Divide-by-zero trap enable (`SCB_CCR.DIV_0_TRP`) bit position @def SCB_CCR_DIV_0_TRP_Pos */
#define SCB_CCR_DIV_0_TRP_Pos			((reg_bit_pos_t) 4U)
/** @brief Divide-by-zero trap enable (`SCB_CCR.DIV_0_TRP`) bit mask @def SCB_CCR_DIV_0_TRP_Msk */
#define SCB_CCR_DIV_0_TRP_Msk			REG_BIT_MASK(SCB_CCR_DIV_0_TRP_Pos)
/** @brief Divide-by-zero trap enable (`SCB_CCR.DIV_0_TRP`) bit mask alias @def SCB_CCR_DIV_0_TRP */
#define SCB_CCR_DIV_0_TRP			SCB_CCR_DIV_0_TRP_Msk

/** @brief Bus-fault ignore control for HardFault and NMI (`SCB_CCR.BFHFNMIGN`) bit position @def SCB_CCR_BFHFNMIGN_Pos */
#define SCB_CCR_BFHFNMIGN_Pos			((reg_bit_pos_t) 8U)
/** @brief Bus-fault ignore control for HardFault and NMI (`SCB_CCR.BFHFNMIGN`) bit mask @def SCB_CCR_BFHFNMIGN_Msk */
#define SCB_CCR_BFHFNMIGN_Msk			REG_BIT_MASK(SCB_CCR_BFHFNMIGN_Pos)
/** @brief Bus-fault ignore control for HardFault and NMI (`SCB_CCR.BFHFNMIGN`) bit mask alias @def SCB_CCR_BFHFNMIGN */
#define SCB_CCR_BFHFNMIGN			SCB_CCR_BFHFNMIGN_Msk

/** @brief Exception stack-alignment selection (`SCB_CCR.STKALIGN`) bit position @def SCB_CCR_STKALIGN_Pos */
#define SCB_CCR_STKALIGN_Pos			((reg_bit_pos_t) 9U)
/** @brief Exception stack-alignment selection (`SCB_CCR.STKALIGN`) bit mask @def SCB_CCR_STKALIGN_Msk */
#define SCB_CCR_STKALIGN_Msk			REG_BIT_MASK(SCB_CCR_STKALIGN_Pos)
/** @brief Exception stack-alignment selection (`SCB_CCR.STKALIGN`) bit mask alias @def SCB_CCR_STKALIGN */
#define SCB_CCR_STKALIGN			SCB_CCR_STKALIGN_Msk

// ---------------------------------------------------------------------------------------------------- //
//											SCB_SHCSR											//
// ---------------------------------------------------------------------------------------------------- //
/** @brief MemManage fault active state (`SCB_SHCSR.MEMFAULTACT`) bit position @def SCB_SHCSR_MEMFAULTACT_Pos */
#define SCB_SHCSR_MEMFAULTACT_Pos		((reg_bit_pos_t) 0U)
/** @brief MemManage fault active state (`SCB_SHCSR.MEMFAULTACT`) bit mask @def SCB_SHCSR_MEMFAULTACT_Msk */
#define SCB_SHCSR_MEMFAULTACT_Msk		REG_BIT_MASK(SCB_SHCSR_MEMFAULTACT_Pos)
/** @brief MemManage fault active state (`SCB_SHCSR.MEMFAULTACT`) bit mask alias @def SCB_SHCSR_MEMFAULTACT */
#define SCB_SHCSR_MEMFAULTACT			SCB_SHCSR_MEMFAULTACT_Msk

/** @brief BusFault active state (`SCB_SHCSR.BUSFAULTACT`) bit position @def SCB_SHCSR_BUSFAULTACT_Pos */
#define SCB_SHCSR_BUSFAULTACT_Pos		((reg_bit_pos_t) 1U)
/** @brief BusFault active state (`SCB_SHCSR.BUSFAULTACT`) bit mask @def SCB_SHCSR_BUSFAULTACT_Msk */
#define SCB_SHCSR_BUSFAULTACT_Msk		REG_BIT_MASK(SCB_SHCSR_BUSFAULTACT_Pos)
/** @brief BusFault active state (`SCB_SHCSR.BUSFAULTACT`) bit mask alias @def SCB_SHCSR_BUSFAULTACT */
#define SCB_SHCSR_BUSFAULTACT			SCB_SHCSR_BUSFAULTACT_Msk

/** @brief UsageFault active state (`SCB_SHCSR.USGFAULTACT`) bit position @def SCB_SHCSR_USGFAULTACT_Pos */
#define SCB_SHCSR_USGFAULTACT_Pos		((reg_bit_pos_t) 3U)
/** @brief UsageFault active state (`SCB_SHCSR.USGFAULTACT`) bit mask @def SCB_SHCSR_USGFAULTACT_Msk */
#define SCB_SHCSR_USGFAULTACT_Msk		REG_BIT_MASK(SCB_SHCSR_USGFAULTACT_Pos)
/** @brief UsageFault active state (`SCB_SHCSR.USGFAULTACT`) bit mask alias @def SCB_SHCSR_USGFAULTACT */
#define SCB_SHCSR_USGFAULTACT			SCB_SHCSR_USGFAULTACT_Msk

/** @brief SVCall active state (`SCB_SHCSR.SVCALLACT`) bit position @def SCB_SHCSR_SVCALLACT_Pos */
#define SCB_SHCSR_SVCALLACT_Pos			((reg_bit_pos_t) 7U)
/** @brief SVCall active state (`SCB_SHCSR.SVCALLACT`) bit mask @def SCB_SHCSR_SVCALLACT_Msk */
#define SCB_SHCSR_SVCALLACT_Msk			REG_BIT_MASK(SCB_SHCSR_SVCALLACT_Pos)
/** @brief SVCall active state (`SCB_SHCSR.SVCALLACT`) bit mask alias @def SCB_SHCSR_SVCALLACT */
#define SCB_SHCSR_SVCALLACT			SCB_SHCSR_SVCALLACT_Msk

/** @brief DebugMonitor active state (`SCB_SHCSR.MONITORACT`) bit position @def SCB_SHCSR_MONITORACT_Pos */
#define SCB_SHCSR_MONITORACT_Pos		((reg_bit_pos_t) 8U)
/** @brief DebugMonitor active state (`SCB_SHCSR.MONITORACT`) bit mask @def SCB_SHCSR_MONITORACT_Msk */
#define SCB_SHCSR_MONITORACT_Msk		REG_BIT_MASK(SCB_SHCSR_MONITORACT_Pos)
/** @brief DebugMonitor active state (`SCB_SHCSR.MONITORACT`) bit mask alias @def SCB_SHCSR_MONITORACT */
#define SCB_SHCSR_MONITORACT			SCB_SHCSR_MONITORACT_Msk

/** @brief PendSV active state (`SCB_SHCSR.PENDSVACT`) bit position @def SCB_SHCSR_PENDSVACT_Pos */
#define SCB_SHCSR_PENDSVACT_Pos			((reg_bit_pos_t) 10U)
/** @brief PendSV active state (`SCB_SHCSR.PENDSVACT`) bit mask @def SCB_SHCSR_PENDSVACT_Msk */
#define SCB_SHCSR_PENDSVACT_Msk			REG_BIT_MASK(SCB_SHCSR_PENDSVACT_Pos)
/** @brief PendSV active state (`SCB_SHCSR.PENDSVACT`) bit mask alias @def SCB_SHCSR_PENDSVACT */
#define SCB_SHCSR_PENDSVACT			SCB_SHCSR_PENDSVACT_Msk

/** @brief SysTick active state (`SCB_SHCSR.SYSTICKACT`) bit position @def SCB_SHCSR_SYSTICKACT_Pos */
#define SCB_SHCSR_SYSTICKACT_Pos		((reg_bit_pos_t) 11U)
/** @brief SysTick active state (`SCB_SHCSR.SYSTICKACT`) bit mask @def SCB_SHCSR_SYSTICKACT_Msk */
#define SCB_SHCSR_SYSTICKACT_Msk		REG_BIT_MASK(SCB_SHCSR_SYSTICKACT_Pos)
/** @brief SysTick active state (`SCB_SHCSR.SYSTICKACT`) bit mask alias @def SCB_SHCSR_SYSTICKACT */
#define SCB_SHCSR_SYSTICKACT			SCB_SHCSR_SYSTICKACT_Msk

/** @brief UsageFault pending state (`SCB_SHCSR.USGFAULTPENDED`) bit position @def SCB_SHCSR_USGFAULTPENDED_Pos */
#define SCB_SHCSR_USGFAULTPENDED_Pos		((reg_bit_pos_t) 12U)
/** @brief UsageFault pending state (`SCB_SHCSR.USGFAULTPENDED`) bit mask @def SCB_SHCSR_USGFAULTPENDED_Msk */
#define SCB_SHCSR_USGFAULTPENDED_Msk		REG_BIT_MASK(SCB_SHCSR_USGFAULTPENDED_Pos)
/** @brief UsageFault pending state (`SCB_SHCSR.USGFAULTPENDED`) bit mask alias @def SCB_SHCSR_USGFAULTPENDED */
#define SCB_SHCSR_USGFAULTPENDED		SCB_SHCSR_USGFAULTPENDED_Msk

/** @brief MemManage fault pending state (`SCB_SHCSR.MEMFAULTPENDED`) bit position @def SCB_SHCSR_MEMFAULTPENDED_Pos */
#define SCB_SHCSR_MEMFAULTPENDED_Pos		((reg_bit_pos_t) 13U)
/** @brief MemManage fault pending state (`SCB_SHCSR.MEMFAULTPENDED`) bit mask @def SCB_SHCSR_MEMFAULTPENDED_Msk */
#define SCB_SHCSR_MEMFAULTPENDED_Msk		REG_BIT_MASK(SCB_SHCSR_MEMFAULTPENDED_Pos)
/** @brief MemManage fault pending state (`SCB_SHCSR.MEMFAULTPENDED`) bit mask alias @def SCB_SHCSR_MEMFAULTPENDED */
#define SCB_SHCSR_MEMFAULTPENDED		SCB_SHCSR_MEMFAULTPENDED_Msk

/** @brief BusFault pending state (`SCB_SHCSR.BUSFAULTPENDED`) bit position @def SCB_SHCSR_BUSFAULTPENDED_Pos */
#define SCB_SHCSR_BUSFAULTPENDED_Pos		((reg_bit_pos_t) 14U)
/** @brief BusFault pending state (`SCB_SHCSR.BUSFAULTPENDED`) bit mask @def SCB_SHCSR_BUSFAULTPENDED_Msk */
#define SCB_SHCSR_BUSFAULTPENDED_Msk		REG_BIT_MASK(SCB_SHCSR_BUSFAULTPENDED_Pos)
/** @brief BusFault pending state (`SCB_SHCSR.BUSFAULTPENDED`) bit mask alias @def SCB_SHCSR_BUSFAULTPENDED */
#define SCB_SHCSR_BUSFAULTPENDED		SCB_SHCSR_BUSFAULTPENDED_Msk

/** @brief SVCall pending state (`SCB_SHCSR.SVCALLPENDED`) bit position @def SCB_SHCSR_SVCALLPENDED_Pos */
#define SCB_SHCSR_SVCALLPENDED_Pos		((reg_bit_pos_t) 15U)
/** @brief SVCall pending state (`SCB_SHCSR.SVCALLPENDED`) bit mask @def SCB_SHCSR_SVCALLPENDED_Msk */
#define SCB_SHCSR_SVCALLPENDED_Msk		REG_BIT_MASK(SCB_SHCSR_SVCALLPENDED_Pos)
/** @brief SVCall pending state (`SCB_SHCSR.SVCALLPENDED`) bit mask alias @def SCB_SHCSR_SVCALLPENDED */
#define SCB_SHCSR_SVCALLPENDED			SCB_SHCSR_SVCALLPENDED_Msk

/** @brief MemManage fault enable (`SCB_SHCSR.MEMFAULTENA`) bit position @def SCB_SHCSR_MEMFAULTENA_Pos */
#define SCB_SHCSR_MEMFAULTENA_Pos		((reg_bit_pos_t) 16U)
/** @brief MemManage fault enable (`SCB_SHCSR.MEMFAULTENA`) bit mask @def SCB_SHCSR_MEMFAULTENA_Msk */
#define SCB_SHCSR_MEMFAULTENA_Msk		REG_BIT_MASK(SCB_SHCSR_MEMFAULTENA_Pos)
/** @brief MemManage fault enable (`SCB_SHCSR.MEMFAULTENA`) bit mask alias @def SCB_SHCSR_MEMFAULTENA */
#define SCB_SHCSR_MEMFAULTENA			SCB_SHCSR_MEMFAULTENA_Msk

/** @brief BusFault enable (`SCB_SHCSR.BUSFAULTENA`) bit position @def SCB_SHCSR_BUSFAULTENA_Pos */
#define SCB_SHCSR_BUSFAULTENA_Pos		((reg_bit_pos_t) 17U)
/** @brief BusFault enable (`SCB_SHCSR.BUSFAULTENA`) bit mask @def SCB_SHCSR_BUSFAULTENA_Msk */
#define SCB_SHCSR_BUSFAULTENA_Msk		REG_BIT_MASK(SCB_SHCSR_BUSFAULTENA_Pos)
/** @brief BusFault enable (`SCB_SHCSR.BUSFAULTENA`) bit mask alias @def SCB_SHCSR_BUSFAULTENA */
#define SCB_SHCSR_BUSFAULTENA			SCB_SHCSR_BUSFAULTENA_Msk

/** @brief UsageFault enable (`SCB_SHCSR.USGFAULTENA`) bit position @def SCB_SHCSR_USGFAULTENA_Pos */
#define SCB_SHCSR_USGFAULTENA_Pos		((reg_bit_pos_t) 18U)
/** @brief UsageFault enable (`SCB_SHCSR.USGFAULTENA`) bit mask @def SCB_SHCSR_USGFAULTENA_Msk */
#define SCB_SHCSR_USGFAULTENA_Msk		REG_BIT_MASK(SCB_SHCSR_USGFAULTENA_Pos)
/** @brief UsageFault enable (`SCB_SHCSR.USGFAULTENA`) bit mask alias @def SCB_SHCSR_USGFAULTENA */
#define SCB_SHCSR_USGFAULTENA			SCB_SHCSR_USGFAULTENA_Msk

// ---------------------------------------------------------------------------------------------------- //
//											SCB_CFSR											//
// ---------------------------------------------------------------------------------------------------- //
/** @brief MemManage Fault Status subregister (`SCB_CFSR.MEMFAULTSR[7:0]`) field position @def SCB_CFSR_MEMFAULTSR_Pos */
#define SCB_CFSR_MEMFAULTSR_Pos			((reg_bit_pos_t) 0U)
/** @brief MemManage Fault Status subregister (`SCB_CFSR.MEMFAULTSR[7:0]`) field width @def SCB_CFSR_MEMFAULTSR_Width */
#define SCB_CFSR_MEMFAULTSR_Width		((reg_field_width_t) 8U)
/** @brief MemManage Fault Status subregister (`SCB_CFSR.MEMFAULTSR[7:0]`) field mask @def SCB_CFSR_MEMFAULTSR_Msk */
#define SCB_CFSR_MEMFAULTSR_Msk			REG_FIELD_MASK(SCB_CFSR_MEMFAULTSR_Pos, SCB_CFSR_MEMFAULTSR_Width)
/** @brief MemManage Fault Status subregister (`SCB_CFSR.MEMFAULTSR[7:0]`) field mask alias @def SCB_CFSR_MEMFAULTSR */
#define SCB_CFSR_MEMFAULTSR			SCB_CFSR_MEMFAULTSR_Msk

/** @brief Instruction access violation status (`SCB_CFSR.IACCVIOL`) bit position @def SCB_CFSR_IACCVIOL_Pos */
#define SCB_CFSR_IACCVIOL_Pos			((reg_bit_pos_t) 0U)
/** @brief Instruction access violation status (`SCB_CFSR.IACCVIOL`) bit mask @def SCB_CFSR_IACCVIOL_Msk */
#define SCB_CFSR_IACCVIOL_Msk			REG_BIT_MASK(SCB_CFSR_IACCVIOL_Pos)
/** @brief Instruction access violation status (`SCB_CFSR.IACCVIOL`) bit mask alias @def SCB_CFSR_IACCVIOL */
#define SCB_CFSR_IACCVIOL			SCB_CFSR_IACCVIOL_Msk

/** @brief Data access violation status (`SCB_CFSR.DACCVIOL`) bit position @def SCB_CFSR_DACCVIOL_Pos */
#define SCB_CFSR_DACCVIOL_Pos			((reg_bit_pos_t) 1U)
/** @brief Data access violation status (`SCB_CFSR.DACCVIOL`) bit mask @def SCB_CFSR_DACCVIOL_Msk */
#define SCB_CFSR_DACCVIOL_Msk			REG_BIT_MASK(SCB_CFSR_DACCVIOL_Pos)
/** @brief Data access violation status (`SCB_CFSR.DACCVIOL`) bit mask alias @def SCB_CFSR_DACCVIOL */
#define SCB_CFSR_DACCVIOL			SCB_CFSR_DACCVIOL_Msk

/** @brief MemManage unstacking error status (`SCB_CFSR.MUNSTKERR`) bit position @def SCB_CFSR_MUNSTKERR_Pos */
#define SCB_CFSR_MUNSTKERR_Pos			((reg_bit_pos_t) 3U)
/** @brief MemManage unstacking error status (`SCB_CFSR.MUNSTKERR`) bit mask @def SCB_CFSR_MUNSTKERR_Msk */
#define SCB_CFSR_MUNSTKERR_Msk			REG_BIT_MASK(SCB_CFSR_MUNSTKERR_Pos)
/** @brief MemManage unstacking error status (`SCB_CFSR.MUNSTKERR`) bit mask alias @def SCB_CFSR_MUNSTKERR */
#define SCB_CFSR_MUNSTKERR			SCB_CFSR_MUNSTKERR_Msk

/** @brief MemManage stacking error status (`SCB_CFSR.MSTKERR`) bit position @def SCB_CFSR_MSTKERR_Pos */
#define SCB_CFSR_MSTKERR_Pos			((reg_bit_pos_t) 4U)
/** @brief MemManage stacking error status (`SCB_CFSR.MSTKERR`) bit mask @def SCB_CFSR_MSTKERR_Msk */
#define SCB_CFSR_MSTKERR_Msk			REG_BIT_MASK(SCB_CFSR_MSTKERR_Pos)
/** @brief MemManage stacking error status (`SCB_CFSR.MSTKERR`) bit mask alias @def SCB_CFSR_MSTKERR */
#define SCB_CFSR_MSTKERR			SCB_CFSR_MSTKERR_Msk

/** @brief MemManage fault address validity (`SCB_CFSR.MMARVALID`) bit position @def SCB_CFSR_MMARVALID_Pos */
#define SCB_CFSR_MMARVALID_Pos			((reg_bit_pos_t) 7U)
/** @brief MemManage fault address validity (`SCB_CFSR.MMARVALID`) bit mask @def SCB_CFSR_MMARVALID_Msk */
#define SCB_CFSR_MMARVALID_Msk			REG_BIT_MASK(SCB_CFSR_MMARVALID_Pos)
/** @brief MemManage fault address validity (`SCB_CFSR.MMARVALID`) bit mask alias @def SCB_CFSR_MMARVALID */
#define SCB_CFSR_MMARVALID			SCB_CFSR_MMARVALID_Msk

/** @brief BusFault Status subregister (`SCB_CFSR.BUSFAULTSR[15:8]`) field position @def SCB_CFSR_BUSFAULTSR_Pos */
#define SCB_CFSR_BUSFAULTSR_Pos			((reg_bit_pos_t) 8U)
/** @brief BusFault Status subregister (`SCB_CFSR.BUSFAULTSR[15:8]`) field width @def SCB_CFSR_BUSFAULTSR_Width */
#define SCB_CFSR_BUSFAULTSR_Width		((reg_field_width_t) 8U)
/** @brief BusFault Status subregister (`SCB_CFSR.BUSFAULTSR[15:8]`) field mask @def SCB_CFSR_BUSFAULTSR_Msk */
#define SCB_CFSR_BUSFAULTSR_Msk			REG_FIELD_MASK(SCB_CFSR_BUSFAULTSR_Pos, SCB_CFSR_BUSFAULTSR_Width)
/** @brief BusFault Status subregister (`SCB_CFSR.BUSFAULTSR[15:8]`) field mask alias @def SCB_CFSR_BUSFAULTSR */
#define SCB_CFSR_BUSFAULTSR			SCB_CFSR_BUSFAULTSR_Msk

/** @brief Instruction bus error status (`SCB_CFSR.IBUSERR`) bit position @def SCB_CFSR_IBUSERR_Pos */
#define SCB_CFSR_IBUSERR_Pos			((reg_bit_pos_t) 8U)
/** @brief Instruction bus error status (`SCB_CFSR.IBUSERR`) bit mask @def SCB_CFSR_IBUSERR_Msk */
#define SCB_CFSR_IBUSERR_Msk			REG_BIT_MASK(SCB_CFSR_IBUSERR_Pos)
/** @brief Instruction bus error status (`SCB_CFSR.IBUSERR`) bit mask alias @def SCB_CFSR_IBUSERR */
#define SCB_CFSR_IBUSERR			SCB_CFSR_IBUSERR_Msk

/** @brief Precise data bus error status (`SCB_CFSR.PRECISERR`) bit position @def SCB_CFSR_PRECISERR_Pos */
#define SCB_CFSR_PRECISERR_Pos			((reg_bit_pos_t) 9U)
/** @brief Precise data bus error status (`SCB_CFSR.PRECISERR`) bit mask @def SCB_CFSR_PRECISERR_Msk */
#define SCB_CFSR_PRECISERR_Msk			REG_BIT_MASK(SCB_CFSR_PRECISERR_Pos)
/** @brief Precise data bus error status (`SCB_CFSR.PRECISERR`) bit mask alias @def SCB_CFSR_PRECISERR */
#define SCB_CFSR_PRECISERR			SCB_CFSR_PRECISERR_Msk

/** @brief Imprecise data bus error status (`SCB_CFSR.IMPRECISERR`) bit position @def SCB_CFSR_IMPRECISERR_Pos */
#define SCB_CFSR_IMPRECISERR_Pos		((reg_bit_pos_t) 10U)
/** @brief Imprecise data bus error status (`SCB_CFSR.IMPRECISERR`) bit mask @def SCB_CFSR_IMPRECISERR_Msk */
#define SCB_CFSR_IMPRECISERR_Msk		REG_BIT_MASK(SCB_CFSR_IMPRECISERR_Pos)
/** @brief Imprecise data bus error status (`SCB_CFSR.IMPRECISERR`) bit mask alias @def SCB_CFSR_IMPRECISERR */
#define SCB_CFSR_IMPRECISERR			SCB_CFSR_IMPRECISERR_Msk

/** @brief BusFault unstacking error status (`SCB_CFSR.UNSTKERR`) bit position @def SCB_CFSR_UNSTKERR_Pos */
#define SCB_CFSR_UNSTKERR_Pos			((reg_bit_pos_t) 11U)
/** @brief BusFault unstacking error status (`SCB_CFSR.UNSTKERR`) bit mask @def SCB_CFSR_UNSTKERR_Msk */
#define SCB_CFSR_UNSTKERR_Msk			REG_BIT_MASK(SCB_CFSR_UNSTKERR_Pos)
/** @brief BusFault unstacking error status (`SCB_CFSR.UNSTKERR`) bit mask alias @def SCB_CFSR_UNSTKERR */
#define SCB_CFSR_UNSTKERR				SCB_CFSR_UNSTKERR_Msk

/** @brief BusFault stacking error status (`SCB_CFSR.STKERR`) bit position @def SCB_CFSR_STKERR_Pos */
#define SCB_CFSR_STKERR_Pos				((reg_bit_pos_t) 12U)
/** @brief BusFault stacking error status (`SCB_CFSR.STKERR`) bit mask @def SCB_CFSR_STKERR_Msk */
#define SCB_CFSR_STKERR_Msk				REG_BIT_MASK(SCB_CFSR_STKERR_Pos)
/** @brief BusFault stacking error status (`SCB_CFSR.STKERR`) bit mask alias @def SCB_CFSR_STKERR */
#define SCB_CFSR_STKERR					SCB_CFSR_STKERR_Msk

/** @brief BusFault address validity (`SCB_CFSR.BFARVALID`) bit position @def SCB_CFSR_BFARVALID_Pos */
#define SCB_CFSR_BFARVALID_Pos			((reg_bit_pos_t) 15U)
/** @brief BusFault address validity (`SCB_CFSR.BFARVALID`) bit mask @def SCB_CFSR_BFARVALID_Msk */
#define SCB_CFSR_BFARVALID_Msk			REG_BIT_MASK(SCB_CFSR_BFARVALID_Pos)
/** @brief BusFault address validity (`SCB_CFSR.BFARVALID`) bit mask alias @def SCB_CFSR_BFARVALID */
#define SCB_CFSR_BFARVALID			SCB_CFSR_BFARVALID_Msk

/** @brief UsageFault Status subregister (`SCB_CFSR.USGFAULTSR[31:16]`) field position @def SCB_CFSR_USGFAULTSR_Pos */
#define SCB_CFSR_USGFAULTSR_Pos			((reg_bit_pos_t) 16U)
/** @brief UsageFault Status subregister (`SCB_CFSR.USGFAULTSR[31:16]`) field width @def SCB_CFSR_USGFAULTSR_Width */
#define SCB_CFSR_USGFAULTSR_Width		((reg_field_width_t) 16U)
/** @brief UsageFault Status subregister (`SCB_CFSR.USGFAULTSR[31:16]`) field mask @def SCB_CFSR_USGFAULTSR_Msk */
#define SCB_CFSR_USGFAULTSR_Msk			REG_FIELD_MASK(SCB_CFSR_USGFAULTSR_Pos, SCB_CFSR_USGFAULTSR_Width)
/** @brief UsageFault Status subregister (`SCB_CFSR.USGFAULTSR[31:16]`) field mask alias @def SCB_CFSR_USGFAULTSR */
#define SCB_CFSR_USGFAULTSR				SCB_CFSR_USGFAULTSR_Msk

/** @brief Undefined-instruction usage fault status (`SCB_CFSR.UNDEFINSTR`) bit position @def SCB_CFSR_UNDEFINSTR_Pos */
#define SCB_CFSR_UNDEFINSTR_Pos			((reg_bit_pos_t) 16U)
/** @brief Undefined-instruction usage fault status (`SCB_CFSR.UNDEFINSTR`) bit mask @def SCB_CFSR_UNDEFINSTR_Msk */
#define SCB_CFSR_UNDEFINSTR_Msk			REG_BIT_MASK(SCB_CFSR_UNDEFINSTR_Pos)
/** @brief Undefined-instruction usage fault status (`SCB_CFSR.UNDEFINSTR`) bit mask alias @def SCB_CFSR_UNDEFINSTR */
#define SCB_CFSR_UNDEFINSTR				SCB_CFSR_UNDEFINSTR_Msk

/** @brief Invalid-state usage fault status (`SCB_CFSR.INVSTATE`) bit position @def SCB_CFSR_INVSTATE_Pos */
#define SCB_CFSR_INVSTATE_Pos			((reg_bit_pos_t) 17U)
/** @brief Invalid-state usage fault status (`SCB_CFSR.INVSTATE`) bit mask @def SCB_CFSR_INVSTATE_Msk */
#define SCB_CFSR_INVSTATE_Msk			REG_BIT_MASK(SCB_CFSR_INVSTATE_Pos)
/** @brief Invalid-state usage fault status (`SCB_CFSR.INVSTATE`) bit mask alias @def SCB_CFSR_INVSTATE */
#define SCB_CFSR_INVSTATE				SCB_CFSR_INVSTATE_Msk

/** @brief Invalid-PC-load usage fault status (`SCB_CFSR.INVPC`) bit position @def SCB_CFSR_INVPC_Pos */
#define SCB_CFSR_INVPC_Pos				((reg_bit_pos_t) 18U)
/** @brief Invalid-PC-load usage fault status (`SCB_CFSR.INVPC`) bit mask @def SCB_CFSR_INVPC_Msk */
#define SCB_CFSR_INVPC_Msk				REG_BIT_MASK(SCB_CFSR_INVPC_Pos)
/** @brief Invalid-PC-load usage fault status (`SCB_CFSR.INVPC`) bit mask alias @def SCB_CFSR_INVPC */
#define SCB_CFSR_INVPC					SCB_CFSR_INVPC_Msk

/** @brief No-coprocessor usage fault status (`SCB_CFSR.NOCP`) bit position @def SCB_CFSR_NOCP_Pos */
#define SCB_CFSR_NOCP_Pos				((reg_bit_pos_t) 19U)
/** @brief No-coprocessor usage fault status (`SCB_CFSR.NOCP`) bit mask @def SCB_CFSR_NOCP_Msk */
#define SCB_CFSR_NOCP_Msk				REG_BIT_MASK(SCB_CFSR_NOCP_Pos)
/** @brief No-coprocessor usage fault status (`SCB_CFSR.NOCP`) bit mask alias @def SCB_CFSR_NOCP */
#define SCB_CFSR_NOCP					SCB_CFSR_NOCP_Msk

/** @brief Unaligned-access usage fault status (`SCB_CFSR.UNALIGNED`) bit position @def SCB_CFSR_UNALIGNED_Pos */
#define SCB_CFSR_UNALIGNED_Pos			((reg_bit_pos_t) 24U)
/** @brief Unaligned-access usage fault status (`SCB_CFSR.UNALIGNED`) bit mask @def SCB_CFSR_UNALIGNED_Msk */
#define SCB_CFSR_UNALIGNED_Msk			REG_BIT_MASK(SCB_CFSR_UNALIGNED_Pos)
/** @brief Unaligned-access usage fault status (`SCB_CFSR.UNALIGNED`) bit mask alias @def SCB_CFSR_UNALIGNED */
#define SCB_CFSR_UNALIGNED			SCB_CFSR_UNALIGNED_Msk

/** @brief Divide-by-zero usage fault status (`SCB_CFSR.DIVBYZERO`) bit position @def SCB_CFSR_DIVBYZERO_Pos */
#define SCB_CFSR_DIVBYZERO_Pos			((reg_bit_pos_t) 25U)
/** @brief Divide-by-zero usage fault status (`SCB_CFSR.DIVBYZERO`) bit mask @def SCB_CFSR_DIVBYZERO_Msk */
#define SCB_CFSR_DIVBYZERO_Msk			REG_BIT_MASK(SCB_CFSR_DIVBYZERO_Pos)
/** @brief Divide-by-zero usage fault status (`SCB_CFSR.DIVBYZERO`) bit mask alias @def SCB_CFSR_DIVBYZERO */
#define SCB_CFSR_DIVBYZERO			SCB_CFSR_DIVBYZERO_Msk

// ---------------------------------------------------------------------------------------------------- //
//											SCB_HFSR											//
// ---------------------------------------------------------------------------------------------------- //
/** @brief Vector-table read HardFault status (`SCB_HFSR.VECTTBL`) bit position @def SCB_HFSR_VECTTBL_Pos */
#define SCB_HFSR_VECTTBL_Pos		((reg_bit_pos_t) 1U)
/** @brief Vector-table read HardFault status (`SCB_HFSR.VECTTBL`) bit mask @def SCB_HFSR_VECTTBL_Msk */
#define SCB_HFSR_VECTTBL_Msk		REG_BIT_MASK(SCB_HFSR_VECTTBL_Pos)
/** @brief Vector-table read HardFault status (`SCB_HFSR.VECTTBL`) bit mask alias @def SCB_HFSR_VECTTBL */
#define SCB_HFSR_VECTTBL		SCB_HFSR_VECTTBL_Msk

/** @brief Escalated configurable-fault status (`SCB_HFSR.FORCED`) bit position @def SCB_HFSR_FORCED_Pos */
#define SCB_HFSR_FORCED_Pos		((reg_bit_pos_t) 30U)
/** @brief Escalated configurable-fault status (`SCB_HFSR.FORCED`) bit mask @def SCB_HFSR_FORCED_Msk */
#define SCB_HFSR_FORCED_Msk		REG_BIT_MASK(SCB_HFSR_FORCED_Pos)
/** @brief Escalated configurable-fault status (`SCB_HFSR.FORCED`) bit mask alias @def SCB_HFSR_FORCED */
#define SCB_HFSR_FORCED			SCB_HFSR_FORCED_Msk

/** @brief Debug-event HardFault status (`SCB_HFSR.DEBUGEVT`) bit position @def SCB_HFSR_DEBUGEVT_Pos */
#define SCB_HFSR_DEBUGEVT_Pos		((reg_bit_pos_t) 31U)
/** @brief Debug-event HardFault status (`SCB_HFSR.DEBUGEVT`) bit mask @def SCB_HFSR_DEBUGEVT_Msk */
#define SCB_HFSR_DEBUGEVT_Msk		REG_BIT_MASK(SCB_HFSR_DEBUGEVT_Pos)
/** @brief Debug-event HardFault status (`SCB_HFSR.DEBUGEVT`) bit mask alias @def SCB_HFSR_DEBUGEVT */
#define SCB_HFSR_DEBUGEVT		SCB_HFSR_DEBUGEVT_Msk

// ---------------------------------------------------------------------------------------------------- //
//											SCB_DFSR											//
// ---------------------------------------------------------------------------------------------------- //
/** @brief Halt-request debug event status (`SCB_DFSR.HALTED`) bit position @def SCB_DFSR_HALTED_Pos */
#define SCB_DFSR_HALTED_Pos		((reg_bit_pos_t) 0U)
/** @brief Halt-request debug event status (`SCB_DFSR.HALTED`) bit mask @def SCB_DFSR_HALTED_Msk */
#define SCB_DFSR_HALTED_Msk		REG_BIT_MASK(SCB_DFSR_HALTED_Pos)
/** @brief Halt-request debug event status (`SCB_DFSR.HALTED`) bit mask alias @def SCB_DFSR_HALTED */
#define SCB_DFSR_HALTED			SCB_DFSR_HALTED_Msk

/** @brief Breakpoint debug event status (`SCB_DFSR.BKPT`) bit position @def SCB_DFSR_BKPT_Pos */
#define SCB_DFSR_BKPT_Pos		((reg_bit_pos_t) 1U)
/** @brief Breakpoint debug event status (`SCB_DFSR.BKPT`) bit mask @def SCB_DFSR_BKPT_Msk */
#define SCB_DFSR_BKPT_Msk		REG_BIT_MASK(SCB_DFSR_BKPT_Pos)
/** @brief Breakpoint debug event status (`SCB_DFSR.BKPT`) bit mask alias @def SCB_DFSR_BKPT */
#define SCB_DFSR_BKPT			SCB_DFSR_BKPT_Msk

/** @brief Data Watchpoint and Trace event status (`SCB_DFSR.DWTTRAP`) bit position @def SCB_DFSR_DWTTRAP_Pos */
#define SCB_DFSR_DWTTRAP_Pos		((reg_bit_pos_t) 2U)
/** @brief Data Watchpoint and Trace event status (`SCB_DFSR.DWTTRAP`) bit mask @def SCB_DFSR_DWTTRAP_Msk */
#define SCB_DFSR_DWTTRAP_Msk		REG_BIT_MASK(SCB_DFSR_DWTTRAP_Pos)
/** @brief Data Watchpoint and Trace event status (`SCB_DFSR.DWTTRAP`) bit mask alias @def SCB_DFSR_DWTTRAP */
#define SCB_DFSR_DWTTRAP		SCB_DFSR_DWTTRAP_Msk

/** @brief Vector-catch debug event status (`SCB_DFSR.VCATCH`) bit position @def SCB_DFSR_VCATCH_Pos */
#define SCB_DFSR_VCATCH_Pos		((reg_bit_pos_t) 3U)
/** @brief Vector-catch debug event status (`SCB_DFSR.VCATCH`) bit mask @def SCB_DFSR_VCATCH_Msk */
#define SCB_DFSR_VCATCH_Msk		REG_BIT_MASK(SCB_DFSR_VCATCH_Pos)
/** @brief Vector-catch debug event status (`SCB_DFSR.VCATCH`) bit mask alias @def SCB_DFSR_VCATCH */
#define SCB_DFSR_VCATCH			SCB_DFSR_VCATCH_Msk

/** @brief External debug-request status (`SCB_DFSR.EXTERNAL`) bit position @def SCB_DFSR_EXTERNAL_Pos */
#define SCB_DFSR_EXTERNAL_Pos		((reg_bit_pos_t) 4U)
/** @brief External debug-request status (`SCB_DFSR.EXTERNAL`) bit mask @def SCB_DFSR_EXTERNAL_Msk */
#define SCB_DFSR_EXTERNAL_Msk		REG_BIT_MASK(SCB_DFSR_EXTERNAL_Pos)
/** @brief External debug-request status (`SCB_DFSR.EXTERNAL`) bit mask alias @def SCB_DFSR_EXTERNAL */
#define SCB_DFSR_EXTERNAL		SCB_DFSR_EXTERNAL_Msk

/** @} */ // SCB_01_RegisterLayer_00_RegisterDefines

// ==================================================================================================== //
//											SCB Register Map											//
// ==================================================================================================== //

/**
 * @defgroup SCB_01_RegisterLayer_01_RegisterMap SCB Register Block Map
 * @ingroup SCB_01_RegisterLayer
 * @brief Memory-mapped Cortex-M3 System Control Block register layout
 * @details
 * The member order, access qualifiers, and offsets follow Arm DDI 0337G,
 * Table 8-1, from CPUID through ISAR4. Every register exposes a full-width
 * `.REG` image and a named `.BIT` field view. AIRCR additionally separates
 * its overlapping read-key and write-key meanings into `.BIT.READ` and
 * `.BIT.WRITE` views.
 * @{
 */

/**
 * @brief Cortex-M3 System Control Block register structure
 * @details
 * Maps the SCB register window beginning at `0xE000ED00`. Read-only feature
 * and identification views use `_I`; registers containing writable state or
 * actions use `_IO`. The `.REG` member is the canonical LL transaction path.
 * `.BIT` documents and exposes individual hardware fields, but must not be
 * used for read-modify-write operations on keyed, action, or write-one-to-clear
 * registers.
 * @see Arm DDI 0337G, Table 8-1 NVIC registers
 */
typedef volatile struct __SCB_TypeDef
{
	/**
	 * @section SCB_TypeDef_CPUID CPUID Base Register (CPUID)
	 * @brief [R] Processor implementer, variant, architecture, part, and revision identification
	 * @note Offset: `0x00`
	 */
	union
	{
		/** @brief Full 32-bit read-only `SCB_CPUID` register image */
		_I REG;
		/** @brief Named read-only `SCB_CPUID` bitfield view */
		struct
		{
			_I REVISION : 4;		/**< Processor revision number */
			_I PARTNO : 12;		/**< Processor part number */
			_I ARCHITECTURE : 4;	/**< Architecture identifier */
			_I VARIANT : 4;		/**< Processor variant number */
			_I IMPLEMENTER : 8;	/**< Implementer code */
		} BIT;
	} CPUID;

	/**
	 * @section SCB_TypeDef_ICSR Interrupt Control and State Register (ICSR)
	 * @brief [Mixed] Exception active/pending state and PendSV, SysTick, and NMI actions
	 * @note Offset: `0x04`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_ICSR` register image */
		_IO REG;
		/** @brief Named mixed-access `SCB_ICSR` bitfield view */
		struct
		{
			_I VECTACTIVE : 9;		/**< Active exception number */
			_I reserved_1 : 2;		/**< Reserved */
			_I RETTOBASE : 1;		/**< Return-to-base status */
			_I VECTPENDING : 9;	/**< Highest-priority pending exception */
			_I reserved_2 : 1;		/**< Reserved */
			_I ISRPENDING : 1;		/**< External interrupt pending status */
			_I ISRPREEMPT : 1;		/**< Pending exception preemption status */
			_I reserved_3 : 1;		/**< Reserved */
			_O PENDSTCLR : 1;		/**< SysTick pending clear action */
			_IO PENDSTSET : 1;		/**< SysTick pending state/set action */
			_O PENDSVCLR : 1;		/**< PendSV pending clear action */
			_IO PENDSVSET : 1;		/**< PendSV pending state/set action */
			_I reserved_4 : 2;		/**< Reserved */
			_IO NMIPENDSET : 1;		/**< NMI pending state/set action */
		} BIT;
	} ICSR;

	/**
	 * @section SCB_TypeDef_VTOR Vector Table Offset Register (VTOR)
	 * @brief [R/W] Vector table base selection and alignment-constrained offset
	 * @note Offset: `0x08`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_VTOR` register image */
		_IO REG;
		/** @brief Named `SCB_VTOR` bitfield view for the selected Cortex-M3 revision */
		struct
		{
			_IO reserved_1 : 7;		/**< Reserved; vector-table alignment */
#if !defined(__CM3_REV) || (__CM3_REV < 0x0201U)
			_IO TBLOFF : 22;		/**< Vector table offset on Cortex-M3 r2p0 and earlier */
			_IO TBLBASE : 1;		/**< Code/SRAM region selection on Cortex-M3 r2p0 and earlier */
			_IO reserved_2 : 2;		/**< Reserved */
#else
			_IO TBLOFF : 25;		/**< Vector table offset on Cortex-M3 r2p1 and later */
#endif
		} BIT;
	} VTOR;

	/**
	 * @section SCB_TypeDef_AIRCR Application Interrupt and Reset Control Register (AIRCR)
	 * @brief [R/W, keyed] Priority grouping, endianness status, and reset actions
	 * @note Offset: `0x0C`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_AIRCR` register image and canonical keyed transaction view */
		_IO REG;
		/** @brief Read-side and write-side field interpretations of `SCB_AIRCR` */
		union
		{
			/** @brief Read-side `SCB_AIRCR` field view */
			struct
			{
				_I VECTRESET : 1;		/**< Local reset state */
				_I VECTCLRACTIVE : 1;	/**< Exception active-state clear action field */
				_I SYSRESETREQ : 1;		/**< System reset request field */
				_I reserved_1 : 5;		/**< Reserved */
				_I PRIGROUP : 3;		/**< Interrupt priority grouping */
				_I reserved_2 : 4;		/**< Reserved */
				_I ENDIANESS : 1;		/**< Data endianness status */
				_I VECTKEYSTAT : 16;	/**< Read-side key status */
			} READ;
			/** @brief Write-side `SCB_AIRCR` field view */
			struct
			{
				_O VECTRESET : 1;		/**< Local reset request */
				_O VECTCLRACTIVE : 1;	/**< Exception active-state clear request */
				_O SYSRESETREQ : 1;		/**< System reset request */
				_O reserved_1 : 5;		/**< Reserved */
				_O PRIGROUP : 3;		/**< Interrupt priority grouping */
				_O reserved_2 : 5;		/**< Reserved and read-only endianness position */
				_O VECTKEY : 16;		/**< Write authorization key */
			} WRITE;
		} BIT;
	} AIRCR;

	/**
	 * @section SCB_TypeDef_SCR System Control Register (SCR)
	 * @brief [R/W] Sleep, deep-sleep, and event-on-pend behavior
	 * @note Offset: `0x10`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_SCR` register image */
		_IO REG;
		/** @brief Named `SCB_SCR` bitfield view */
		struct
		{
			_IO reserved_1 : 1;		/**< Reserved */
			_IO SLEEPONEXIT : 1;	/**< Sleep on exception return */
			_IO SLEEPDEEP : 1;		/**< Deep-sleep selection */
			_IO reserved_2 : 1;		/**< Reserved */
			_IO SEVONPEND : 1;		/**< Send event on pending transition */
			_IO reserved_3 : 27;	/**< Reserved */
		} BIT;
	} SCR;

	/**
	 * @section SCB_TypeDef_CCR Configuration and Control Register (CCR)
	 * @brief [R/W] Trap, stack alignment, fault handling, and unprivileged trigger controls
	 * @note Offset: `0x14`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_CCR` register image */
		_IO REG;
		/** @brief Named `SCB_CCR` bitfield view */
		struct
		{
			_IO NONBASETHRDENA : 1;	/**< Thread entry from non-base level enable */
			_IO USERSETMPEND : 1;		/**< Unprivileged software trigger enable */
			_IO reserved_1 : 1;			/**< Reserved */
			_IO UNALIGN_TRP : 1;		/**< Unaligned access trap enable */
			_IO DIV_0_TRP : 1;			/**< Divide-by-zero trap enable */
			_IO reserved_2 : 3;			/**< Reserved */
			_IO BFHFNMIGN : 1;			/**< BusFault ignore during priority -1 handlers */
			_IO STKALIGN : 1;			/**< Eight-byte exception stack alignment */
			_IO reserved_3 : 22;		/**< Reserved */
		} BIT;
	} CCR;

	/**
	 * @section SCB_TypeDef_SHPR1 System Handler Priority Register 1 (SHPR1)
	 * @brief [R/W] Priorities for system handlers 4 through 7
	 * @note Offset: `0x18`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_SHPR1` register image */
		_IO REG;
		/** @brief Named `SCB_SHPR1` priority-byte view */
		struct
		{
			_IO PRI_4 : 8;		/**< MemManage priority */
			_IO PRI_5 : 8;		/**< BusFault priority */
			_IO PRI_6 : 8;		/**< UsageFault priority */
			_IO reserved : 8;	/**< Reserved priority byte 7 */
		} BIT;
	} SHPR1;

	/**
	 * @section SCB_TypeDef_SHPR2 System Handler Priority Register 2 (SHPR2)
	 * @brief [R/W] Priorities for system handlers 8 through 11
	 * @note Offset: `0x1C`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_SHPR2` register image */
		_IO REG;
		/** @brief Named `SCB_SHPR2` priority-byte view */
		struct
		{
			_IO reserved_1 : 8;	/**< Reserved priority byte 8 */
			_IO reserved_2 : 8;	/**< Reserved priority byte 9 */
			_IO reserved_3 : 8;	/**< Reserved priority byte 10 */
			_IO PRI_11 : 8;		/**< SVCall priority */
		} BIT;
	} SHPR2;

	/**
	 * @section SCB_TypeDef_SHPR3 System Handler Priority Register 3 (SHPR3)
	 * @brief [R/W] Priorities for system handlers 12 through 15
	 * @note Offset: `0x20`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_SHPR3` register image */
		_IO REG;
		/** @brief Named `SCB_SHPR3` priority-byte view */
		struct
		{
			_IO PRI_12 : 8;		/**< Debug monitor priority */
			_IO reserved : 8;	/**< Reserved priority byte 13 */
			_IO PRI_14 : 8;		/**< PendSV priority */
			_IO PRI_15 : 8;		/**< SysTick priority */
		} BIT;
	} SHPR3;

	/**
	 * @section SCB_TypeDef_SHCSR System Handler Control and State Register (SHCSR)
	 * @brief [R/W] Configurable-fault enables and system-handler active/pending state
	 * @note Offset: `0x24`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_SHCSR` register image */
		_IO REG;
		/** @brief Named mixed-access `SCB_SHCSR` bitfield view */
		struct
		{
			_I MEMFAULTACT : 1;		/**< MemManage active status */
			_I BUSFAULTACT : 1;		/**< BusFault active status */
			_I reserved_1 : 1;		/**< Reserved */
			_I USGFAULTACT : 1;		/**< UsageFault active status */
			_I reserved_2 : 3;		/**< Reserved */
			_I SVCALLACT : 1;		/**< SVCall active status */
			_I MONITORACT : 1;		/**< Debug monitor active status */
			_I reserved_3 : 1;		/**< Reserved */
			_I PENDSVACT : 1;		/**< PendSV active status */
			_I SYSTICKACT : 1;		/**< SysTick active status */
			_IO USGFAULTPENDED : 1;	/**< UsageFault pending state */
			_IO MEMFAULTPENDED : 1;	/**< MemManage pending state */
			_IO BUSFAULTPENDED : 1;	/**< BusFault pending state */
			_IO SVCALLPENDED : 1;	/**< SVCall pending state */
			_IO MEMFAULTENA : 1;		/**< MemManage enable */
			_IO BUSFAULTENA : 1;		/**< BusFault enable */
			_IO USGFAULTENA : 1;		/**< UsageFault enable */
			_I reserved_4 : 13;		/**< Reserved */
		} BIT;
	} SHCSR;

	/**
	 * @section SCB_TypeDef_CFSR Configurable Fault Status Register (CFSR)
	 * @brief [R/W1C] MemManage, BusFault, and UsageFault cause and validity status
	 * @note Offset: `0x28`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_CFSR` register image and canonical W1C transaction view */
		_IO REG;
		/** @brief Named write-one-to-clear `SCB_CFSR` status view */
		struct
		{
			_IO IACCVIOL : 1;		/**< Instruction access violation */
			_IO DACCVIOL : 1;		/**< Data access violation */
			_IO reserved_1 : 1;		/**< Reserved */
			_IO MUNSTKERR : 1;		/**< MemManage exception unstacking fault */
			_IO MSTKERR : 1;		/**< MemManage exception stacking fault */
			_IO reserved_2 : 2;		/**< Reserved */
			_IO MMARVALID : 1;		/**< MMFAR validity */
			_IO IBUSERR : 1;		/**< Instruction bus error */
			_IO PRECISERR : 1;		/**< Precise data bus error */
			_IO IMPRECISERR : 1;	/**< Imprecise data bus error */
			_IO UNSTKERR : 1;		/**< BusFault exception unstacking fault */
			_IO STKERR : 1;		/**< BusFault exception stacking fault */
			_IO reserved_3 : 2;		/**< Reserved */
			_IO BFARVALID : 1;		/**< BFAR validity */
			_IO UNDEFINSTR : 1;		/**< Undefined instruction */
			_IO INVSTATE : 1;		/**< Invalid execution state */
			_IO INVPC : 1;			/**< Invalid exception return PC */
			_IO NOCP : 1;			/**< Coprocessor access fault */
			_IO reserved_4 : 4;		/**< Reserved */
			_IO UNALIGNED : 1;		/**< Unaligned access */
			_IO DIVBYZERO : 1;		/**< Divide by zero */
			_IO reserved_5 : 6;		/**< Reserved */
		} BIT;
	} CFSR;

	/**
	 * @section SCB_TypeDef_HFSR HardFault Status Register (HFSR)
	 * @brief [R/W1C] Vector-table, escalated-fault, and debug-event HardFault status
	 * @note Offset: `0x2C`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_HFSR` register image and canonical W1C transaction view */
		_IO REG;
		/** @brief Named write-one-to-clear `SCB_HFSR` status view */
		struct
		{
			_IO reserved_1 : 1;		/**< Reserved */
			_IO VECTTBL : 1;		/**< Vector-table read HardFault */
			_IO reserved_2 : 28;	/**< Reserved */
			_IO FORCED : 1;		/**< Escalated configurable fault */
			_IO DEBUGEVT : 1;		/**< Escalated debug event */
		} BIT;
	} HFSR;

	/**
	 * @section SCB_TypeDef_DFSR Debug Fault Status Register (DFSR)
	 * @brief [R/W1C] Halt, breakpoint, watchpoint, vector-catch, and external debug status
	 * @note Offset: `0x30`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_DFSR` register image and canonical W1C transaction view */
		_IO REG;
		/** @brief Named write-one-to-clear `SCB_DFSR` status view */
		struct
		{
			_IO HALTED : 1;		/**< Halt request debug event */
			_IO BKPT : 1;			/**< Breakpoint debug event */
			_IO DWTTRAP : 1;		/**< DWT match debug event */
			_IO VCATCH : 1;		/**< Vector-catch debug event */
			_IO EXTERNAL : 1;		/**< External debug request event */
			_IO reserved : 27;	/**< Reserved */
		} BIT;
	} DFSR;

	/**
	 * @section SCB_TypeDef_MMFAR MemManage Fault Address Register (MMFAR)
	 * @brief [R/W] Address associated with a valid MemManage data-access fault
	 * @note Offset: `0x34`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_MMFAR` register image */
		_IO REG;
		/** @brief Named `SCB_MMFAR` address view */
		struct
		{
			_IO ADDRESS : 32;	/**< MemManage fault address */
		} BIT;
	} MMFAR;

	/**
	 * @section SCB_TypeDef_BFAR BusFault Address Register (BFAR)
	 * @brief [R/W] Address associated with a valid precise BusFault
	 * @note Offset: `0x38`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_BFAR` register image */
		_IO REG;
		/** @brief Named `SCB_BFAR` address view */
		struct
		{
			_IO ADDRESS : 32;	/**< BusFault address */
		} BIT;
	} BFAR;

	/**
	 * @section SCB_TypeDef_AFSR Auxiliary Fault Status Register (AFSR)
	 * @brief [R/W] Implementation-defined auxiliary fault status
	 * @note Offset: `0x3C`
	 */
	union
	{
		/** @brief Full 32-bit `SCB_AFSR` register image */
		_IO REG;
		/** @brief Named `SCB_AFSR` implementation-defined status view */
		struct
		{
			_IO IMPDEF : 32;	/**< Implementation-defined auxiliary fault status */
		} BIT;
	} AFSR;

	/**
	 * @section SCB_TypeDef_PFR Processor Feature Registers (PFR0-PFR1)
	 * @brief [R] Processor feature identification
	 * @note Offsets: `0x40` through `0x44`
	 */
	union
	{
		/** @brief Full 32-bit read-only processor feature register image */
		_I REG;
		/** @brief Read-only processor feature field view */
		struct
		{
			_I FEATURES : 32;	/**< Processor feature encoding */
		} BIT;
	} PFR[2];

	/**
	 * @section SCB_TypeDef_DFR Debug Feature Register (DFR0)
	 * @brief [R] Debug-model feature identification
	 * @note Offset: `0x48`
	 */
	union
	{
		/** @brief Full 32-bit read-only `SCB_DFR0` register image */
		_I REG;
		/** @brief Read-only `SCB_DFR0` feature field view */
		struct
		{
			_I FEATURES : 32;	/**< Debug feature encoding */
		} BIT;
	} DFR;

	/**
	 * @section SCB_TypeDef_AFR Auxiliary Feature Register (AFR0)
	 * @brief [R] Auxiliary processor feature identification
	 * @note Offset: `0x4C`
	 */
	union
	{
		/** @brief Full 32-bit read-only `SCB_AFR0` register image */
		_I REG;
		/** @brief Read-only `SCB_AFR0` feature field view */
		struct
		{
			_I FEATURES : 32;	/**< Auxiliary feature encoding */
		} BIT;
	} AFR;

	/**
	 * @section SCB_TypeDef_MMFR Memory Model Feature Registers (MMFR0-MMFR3)
	 * @brief [R] Memory-system architecture feature identification
	 * @note Offsets: `0x50` through `0x5C`
	 */
	union
	{
		/** @brief Full 32-bit read-only memory-model feature register image */
		_I REG;
		/** @brief Read-only memory-model feature field view */
		struct
		{
			_I FEATURES : 32;	/**< Memory-model feature encoding */
		} BIT;
	} MMFR[4];

	/**
	 * @section SCB_TypeDef_ISAR Instruction Set Attribute Registers (ISAR0-ISAR4)
	 * @brief [R] Implemented instruction-set feature identification
	 * @note Offsets: `0x60` through `0x70`
	 */
	union
	{
		/** @brief Full 32-bit read-only instruction-set attribute register image */
		_I REG;
		/** @brief Read-only instruction-set attribute field view */
		struct
		{
			_I FEATURES : 32;	/**< Instruction-set attribute encoding */
		} BIT;
	} ISAR[5];

} SCB_TypeDef;

/** @} */ // SCB_01_RegisterLayer_01_RegisterMap

/** @} */ // SCB_01_RegisterLayer

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_SCB_H_ */
