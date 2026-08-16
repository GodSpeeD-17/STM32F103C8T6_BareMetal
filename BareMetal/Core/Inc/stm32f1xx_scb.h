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
 * Table 8-1, from CPUID through ISAR4. Mixed-access and action fields remain
 * represented by their containing 32-bit register; field-specific access
 * semantics are expressed by the register macros and higher-layer contracts.
 * @{
 */

/**
 * @brief Cortex-M3 System Control Block register structure
 * @details
 * Maps the SCB register window beginning at `0xE000ED00`. Read-only feature
 * and identification registers use `_I`; registers containing writable state
 * or actions use `_IO`.
 * @see Arm DDI 0337G, Table 8-1 NVIC registers
 */
typedef volatile struct __SCB_TypeDef
{
	/**
	 * @section SCB_TypeDef_CPUID CPUID Base Register (CPUID)
	 * @brief [R] Processor implementer, variant, architecture, part, and revision identification
	 * @note Offset: `0x00`
	 */
	_I CPUID;

	/**
	 * @section SCB_TypeDef_ICSR Interrupt Control and State Register (ICSR)
	 * @brief [R/W or R] Exception active/pending state and PendSV, SysTick, and NMI actions
	 * @note Offset: `0x04`
	 */
	_IO ICSR;

	/**
	 * @section SCB_TypeDef_VTOR Vector Table Offset Register (VTOR)
	 * @brief [R/W] Vector table base selection and alignment-constrained offset
	 * @note Offset: `0x08`
	 */
	_IO VTOR;

	/**
	 * @section SCB_TypeDef_AIRCR Application Interrupt and Reset Control Register (AIRCR)
	 * @brief [R/W] Keyed priority grouping, endianness status, and reset actions
	 * @note Offset: `0x0C`
	 */
	_IO AIRCR;

	/**
	 * @section SCB_TypeDef_SCR System Control Register (SCR)
	 * @brief [R/W] Sleep, deep-sleep, and event-on-pend behavior
	 * @note Offset: `0x10`
	 */
	_IO SCR;

	/**
	 * @section SCB_TypeDef_CCR Configuration and Control Register (CCR)
	 * @brief [R/W] Trap, stack alignment, fault handling, and unprivileged trigger controls
	 * @note Offset: `0x14`
	 */
	_IO CCR;

	/**
	 * @section SCB_TypeDef_SHPR1 System Handler Priority Register 1 (SHPR1)
	 * @brief [R/W] Priorities for system handlers 4 through 7
	 * @note Offset: `0x18`
	 */
	_IO SHPR1;

	/**
	 * @section SCB_TypeDef_SHPR2 System Handler Priority Register 2 (SHPR2)
	 * @brief [R/W] Priorities for system handlers 8 through 11
	 * @note Offset: `0x1C`
	 */
	_IO SHPR2;

	/**
	 * @section SCB_TypeDef_SHPR3 System Handler Priority Register 3 (SHPR3)
	 * @brief [R/W] Priorities for system handlers 12 through 15
	 * @note Offset: `0x20`
	 */
	_IO SHPR3;

	/**
	 * @section SCB_TypeDef_SHCSR System Handler Control and State Register (SHCSR)
	 * @brief [R/W] Configurable-fault enables and system-handler active/pending state
	 * @note Offset: `0x24`
	 */
	_IO SHCSR;

	/**
	 * @section SCB_TypeDef_CFSR Configurable Fault Status Register (CFSR)
	 * @brief [R/W] MemManage, BusFault, and UsageFault cause and validity status
	 * @note Offset: `0x28`
	 */
	_IO CFSR;

	/**
	 * @section SCB_TypeDef_HFSR HardFault Status Register (HFSR)
	 * @brief [R/W] Vector-table, escalated-fault, and debug-event HardFault status
	 * @note Offset: `0x2C`
	 */
	_IO HFSR;

	/**
	 * @section SCB_TypeDef_DFSR Debug Fault Status Register (DFSR)
	 * @brief [R/W] Halt, breakpoint, watchpoint, vector-catch, and external debug status
	 * @note Offset: `0x30`
	 */
	_IO DFSR;

	/**
	 * @section SCB_TypeDef_MMFAR MemManage Fault Address Register (MMFAR)
	 * @brief [R/W] Address associated with a valid MemManage data-access fault
	 * @note Offset: `0x34`
	 */
	_IO MMFAR;

	/**
	 * @section SCB_TypeDef_BFAR BusFault Address Register (BFAR)
	 * @brief [R/W] Address associated with a valid precise BusFault
	 * @note Offset: `0x38`
	 */
	_IO BFAR;

	/**
	 * @section SCB_TypeDef_AFSR Auxiliary Fault Status Register (AFSR)
	 * @brief [R/W] Implementation-defined auxiliary fault status
	 * @note Offset: `0x3C`
	 */
	_IO AFSR;

	/**
	 * @section SCB_TypeDef_PFR Processor Feature Registers (PFR0-PFR1)
	 * @brief [R] Processor feature identification
	 * @note Offsets: `0x40` through `0x44`
	 */
	_I PFR[2];

	/**
	 * @section SCB_TypeDef_DFR Debug Feature Register (DFR0)
	 * @brief [R] Debug-model feature identification
	 * @note Offset: `0x48`
	 */
	_I DFR;

	/**
	 * @section SCB_TypeDef_AFR Auxiliary Feature Register (AFR0)
	 * @brief [R] Auxiliary processor feature identification
	 * @note Offset: `0x4C`
	 */
	_I AFR;

	/**
	 * @section SCB_TypeDef_MMFR Memory Model Feature Registers (MMFR0-MMFR3)
	 * @brief [R] Memory-system architecture feature identification
	 * @note Offsets: `0x50` through `0x5C`
	 */
	_I MMFR[4];

	/**
	 * @section SCB_TypeDef_ISAR Instruction Set Attribute Registers (ISAR0-ISAR4)
	 * @brief [R] Implemented instruction-set feature identification
	 * @note Offsets: `0x60` through `0x70`
	 */
	_I ISAR[5];

} SCB_TypeDef;

/** @} */ // SCB_01_RegisterLayer_01_RegisterMap

/** @} */ // SCB_01_RegisterLayer

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_SCB_H_ */
