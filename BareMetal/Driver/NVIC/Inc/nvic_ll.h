/**
 * @file	nvic_ll.h
 * @author	Shrey Shah
 * @brief	NVIC Low-Level Register Access Interface
 * @version	v1.2
 * @date	16-08-2026
 *
 * @details
 * @section NVIC_LL_SCOPE Scope
 * This header defines the register-near NVIC/SCB access layer. Each primitive
 * is a static inline function that performs exactly one access of the
 * documented width to one named register.
 *
 * @section NVIC_LL_AUTHORITY Authority
 * LL owns only mechanical register transfer. It does not validate public IRQ
 * numbers, translate priority selectors, build write-one action masks, apply
 * AIRCR key policy, sequence barriers, or arbitrate shared interrupt vectors.
 * Those responsibilities remain in the Driver and Codec layers.
 *
 * @section NVIC_LL_LAYOUT Interface Layout
 * Accessors are grouped by enable, pending, active, priority, software-trigger,
 * and AIRCR register families. Following the Timer LL pattern, the complete
 * implementation remains in this internal header and has no LL source file.
 */

// Header Guards
#ifndef NVIC_LL_H_
#define NVIC_LL_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx.h"
#include "nvic_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup NVIC_02_LL NVIC Low-Level Register Access Layer
 * @ingroup NVIC
 * @brief Register-near NVIC and SCB AIRCR access used by the NVIC Driver
 * @details
 * These functions expose exact-width raw register transfers only. All inputs
 * must already satisfy the Driver's exact-target validation and transaction
 * policy.
 * @see @ref NVIC_Peripheral_Guide "STM32F103C8T6 NVIC Architecture"
 */

/**
 * @addtogroup NVIC_02_LL
 * @{
 */

/**
 * @brief NVIC and SCB low-level register access APIs
 * @defgroup NVIC_02_LL_01_RegisterOps NVIC LL Register Access APIs
 * @ingroup NVIC_02_LL
 * @details
 * These static inline functions are intentionally dumb register readers and
 * writers. They do not validate public selectors, translate priority values,
 * build action masks, apply barriers, or choose transaction policy.
 * @warning These accessors perform no range, privilege, concurrency, or
 * write-permission checks.
 * @{
 */

// ==================================================================================================== //
//										NVIC Enable Register Access APIs								//
// ==================================================================================================== //

// -------------------------------------- NVIC ISER State Read --------------------------------------- //

/**
 * @brief Reads one complete NVIC ISER enable-state image
 * @param[in] registerIndex Zero-based ISER bank index
 * Accepted values:
 * - `0U` : External IRQ numbers 0 through 31
 * - `1U` : External IRQ numbers 32 through 42
 * @returns @ref reg "Complete 32-bit ISER state image"
 * @pre Caller validated @p registerIndex for the exact target
 * @note Performs exactly one 32-bit volatile read
 */
__STATIC_FORCEINLINE reg LL_NVIC_ReadISER(const uint8_t registerIndex)
{
	//! Capture one complete enable-state bank without interpreting its bits.
	return NVIC->ISER[registerIndex];
}

// ----------------------------------- NVIC ISER/ICER Action Writes ----------------------------------- //

/**
 * @brief Issues one direct NVIC ISER write-one-to-set action
 * @param[in] registerIndex Zero-based ISER bank index
 * Accepted values:
 * - `0U` : External IRQ numbers 0 through 31
 * - `1U` : External IRQ numbers 32 through 42
 * @param[in] actionMask Register-positioned IRQ enable action mask
 * Accepted values:
 * - Exactly one implemented IRQ bit in the selected register bank
 * @returns Void.
 * @pre Caller validated @p registerIndex and @p actionMask
 * @note Performs exactly one direct 32-bit volatile write
 * @warning ISER is a write-one-to-set register; caller must not supply a
 * read-modify-write result
 */
__STATIC_FORCEINLINE void LL_NVIC_WriteISER(const uint8_t registerIndex, const reg actionMask)
{
	//! Forward the action mask as one direct write-one-to-set transfer.
	NVIC->ISER[registerIndex] = actionMask;
}

/**
 * @brief Issues one direct NVIC ICER write-one-to-clear action
 * @param[in] registerIndex Zero-based ICER bank index
 * Accepted values:
 * - `0U` : External IRQ numbers 0 through 31
 * - `1U` : External IRQ numbers 32 through 42
 * @param[in] actionMask Register-positioned IRQ disable action mask
 * Accepted values:
 * - Exactly one implemented IRQ bit in the selected register bank
 * @returns Void.
 * @pre Caller validated @p registerIndex and @p actionMask
 * @pre Caller owns required post-write synchronization
 * @note Performs exactly one direct 32-bit volatile write
 * @warning ICER is a write-one-to-clear register; caller must not supply a
 * read-modify-write result
 */
__STATIC_FORCEINLINE void LL_NVIC_WriteICER(const uint8_t registerIndex, const reg actionMask)
{
	//! Forward the action mask as one direct write-one-to-clear transfer.
	NVIC->ICER[registerIndex] = actionMask;
}

// ==================================================================================================== //
//									NVIC Pending Register Access APIs									//
// ==================================================================================================== //

// -------------------------------------- NVIC ISPR State Read --------------------------------------- //

/**
 * @brief Reads one complete NVIC ISPR pending-state image
 * @param[in] registerIndex Zero-based ISPR bank index
 * Accepted values:
 * - `0U` : External IRQ numbers 0 through 31
 * - `1U` : External IRQ numbers 32 through 42
 * @returns @ref reg "Complete 32-bit ISPR state image"
 * @pre Caller validated @p registerIndex for the exact target
 * @note Performs exactly one 32-bit volatile read
 */
__STATIC_FORCEINLINE reg LL_NVIC_ReadISPR(const uint8_t registerIndex)
{
	//! Capture one complete pending-state bank without interpreting its bits.
	return NVIC->ISPR[registerIndex];
}

// -------------------------------------- NVIC ICPR Action Write -------------------------------------- //

/**
 * @brief Issues one direct NVIC ICPR write-one-to-clear action
 * @param[in] registerIndex Zero-based ICPR bank index
 * Accepted values:
 * - `0U` : External IRQ numbers 0 through 31
 * - `1U` : External IRQ numbers 32 through 42
 * @param[in] actionMask Register-positioned pending-clear action mask
 * Accepted values:
 * - Exactly one implemented IRQ bit in the selected register bank
 * @returns Void.
 * @pre Caller validated @p registerIndex and @p actionMask
 * @note Performs exactly one direct 32-bit volatile write
 * @warning ICPR is a write-one-to-clear register; caller must not supply a
 * read-modify-write result
 */
__STATIC_FORCEINLINE void LL_NVIC_WriteICPR(const uint8_t registerIndex, const reg actionMask)
{
	//! Forward the action mask as one direct write-one-to-clear pending transfer.
	NVIC->ICPR[registerIndex] = actionMask;
}

// ==================================================================================================== //
//										NVIC Active Register Access API									//
// ==================================================================================================== //

// -------------------------------------- NVIC IABR State Read --------------------------------------- //

/**
 * @brief Reads one complete read-only NVIC IABR active-state image
 * @param[in] registerIndex Zero-based IABR bank index
 * Accepted values:
 * - `0U` : External IRQ numbers 0 through 31
 * - `1U` : External IRQ numbers 32 through 42
 * @returns @ref reg "Complete 32-bit IABR state image"
 * @pre Caller validated @p registerIndex for the exact target
 * @note Performs exactly one 32-bit volatile read
 */
__STATIC_FORCEINLINE reg LL_NVIC_ReadIABR(const uint8_t registerIndex)
{
	//! Capture one complete active-state bank without interpreting its bits.
	return NVIC->IABR[registerIndex];
}

// ==================================================================================================== //
//								NVIC Priority Register Access APIs								//
// ==================================================================================================== //

// ---------------------------------------- NVIC IPR Byte Pair ---------------------------------------- //

/**
 * @brief Reads exactly one external IRQ priority byte
 * @param[in] IRQn Validated external IRQ number
 * Accepted values:
 * - @ref NVIC_IRQ_NUMBER_FIRST "`NVIC_IRQ_NUMBER_FIRST`" through @ref NVIC_IRQ_NUMBER_LAST "`NVIC_IRQ_NUMBER_LAST`"
 * @returns @ref reg_field_t "Complete raw IPR byte image"
 * @retval 0x00U..0xFFU Captured byte image; only bits 7 through 4 are implemented
 * @pre Caller validated @p IRQn for the exact target
 * @note Performs exactly one 8-bit volatile read and does not access neighboring priorities
 */
__STATIC_FORCEINLINE reg_field_t LL_NVIC_ReadIPR(const irq_t IRQn)
{
	//! Read only the byte owned by the selected external IRQ.
	return NVIC->IPR[IRQn];
}

/**
 * @brief Writes exactly one external IRQ priority byte
 * @param[in] IRQn Validated external IRQ number
 * Accepted values:
 * - @ref NVIC_IRQ_NUMBER_FIRST "`NVIC_IRQ_NUMBER_FIRST`" through @ref NVIC_IRQ_NUMBER_LAST "`NVIC_IRQ_NUMBER_LAST`"
 * @param[in] priorityFieldImage Complete raw IPR byte image
 * Accepted values:
 * - Multiples of `0x10U` from `0x00U` through `0xF0U` : Implemented priority
 *   in bits 7 through 4 with the unimplemented low nibble clear
 * @returns Void.
 * @pre Caller validated @p IRQn and staged @p priorityFieldImage through Codec
 * @note Performs exactly one 8-bit volatile write and preserves neighboring priorities
 */
__STATIC_FORCEINLINE void LL_NVIC_WriteIPR(const irq_t IRQn, const reg_field_t priorityFieldImage)
{
	//! Write only the byte owned by the selected external IRQ.
	NVIC->IPR[IRQn] = priorityFieldImage;
}

// ==================================================================================================== //
//								NVIC Software Trigger Access API								//
// ==================================================================================================== //

// --------------------------------------- NVIC STIR Action Write ------------------------------------- //

/**
 * @brief Issues one direct NVIC STIR software-trigger action
 * @param[in] IRQn Validated external IRQ number
 * Accepted values:
 * - @ref NVIC_IRQ_NUMBER_FIRST "`NVIC_IRQ_NUMBER_FIRST`" through @ref NVIC_IRQ_NUMBER_LAST "`NVIC_IRQ_NUMBER_LAST`"
 * @returns Void.
 * @pre Caller validated @p IRQn and owns privilege policy
 * @note Performs exactly one 32-bit volatile action write
 * @warning Writing STIR can immediately make the selected IRQ pending
 */
__STATIC_FORCEINLINE void LL_NVIC_WriteSTIR(const irq_t IRQn)
{
	//! Forward the validated interrupt identifier as one action-only transfer.
	NVIC->STIR = (reg) IRQn;
}

// ==================================================================================================== //
//									SCB AIRCR Access APIs									//
// ==================================================================================================== //

// ------------------------------------------ SCB AIRCR Pair ------------------------------------------ //

/**
 * @brief Reads the complete SCB AIRCR image
 * @returns @ref reg "Complete 32-bit AIRCR image"
 * @note Performs exactly one 32-bit volatile read
 * @note The upper halfword contains the read-side key status image rather than
 * the write key required for a later AIRCR write
 */
__STATIC_FORCEINLINE reg LL_SCB_ReadAIRCR(void)
{
	//! Capture the complete AIRCR image for caller-owned Codec staging.
	return SCB->AIRCR.REG;
}

/**
 * @brief Writes one caller-staged keyed SCB AIRCR image
 * @param[in] aircrRegImage Complete keyed AIRCR write image
 * Accepted values:
 * - Codec-staged image containing write key `0x5FA`, a canonical `PRIGROUP`,
 *   and no reset/action request bits
 * @returns Void.
 * @pre Caller owns AIRCR staging and global priority-group transaction policy
 * @note Performs exactly one 32-bit volatile write
 * @warning An incorrectly staged AIRCR image can request reset or other
 * system-level actions; normal callers must use the NVIC Codec
 */
__STATIC_FORCEINLINE void LL_SCB_WriteAIRCR(const reg aircrRegImage)
{
	//! Commit the caller-staged keyed AIRCR image in one transfer.
	SCB->AIRCR.REG = aircrRegImage;
}

/** @} */ // NVIC_02_LL_01_RegisterOps

/** @} */ // NVIC_02_LL

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_LL_H_ */
