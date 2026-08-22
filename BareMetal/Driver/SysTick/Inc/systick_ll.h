/**
 * @file	systick_ll.h
 * @author	Shrey Shah
 * @brief	SysTick low-level register-access interface
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section SYSTICK_LL_H_HIERARCHY Hierarchy
 * - Position: Layer 1 - Hardware-nearest SysTick LL sublayer
 * - Used by: SysTick Driver implementation only
 * - Uses: Layer 0 Core SysTick register map
 *
 * @section SYSTICK_LL_H_RESPONSIBILITY Responsibility
 * This Layer 1 LL interface centralizes full-width register reads and writes in
 * one generic primitive pair. Named SysTick accessors only select a register
 * pointer and delegate the operation to that pair.
 *
 * @section SYSTICK_LL_H_BOUNDARY Dependency Boundary
 * It owns no validation, public selector policy, application tick storage, or
 * interrupt handler. Driver orchestration points downward into LL; LL never
 * includes or calls the Driver or application.
 */

// Header Guard
#ifndef SYSTICK_LL_H_
#define SYSTICK_LL_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "stm32f1xx_systick.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup SYSTICK_02_LL SysTick Low-Level Layer
 * @ingroup SYSTICK
 * @brief Direct full-register SysTick accessors
 * @details See @ref SYSTICK_Peripheral_Guide for register semantics and layer ownership.
 * @{
 */

// ==================================================================================================== //
// SysTick LL Register Access APIs
// ==================================================================================================== //

/**
 * @brief Returns a pointer to one SysTick register `.REG` image
 * @def LL_SysTick_REG
 * @param[in]	_REG	Register member token inside @ref SysTick_TypeDef
 * Accepted values:
 * - `CTRL`
 * - `LOAD`
 * - `VAL`
 * - `CALIB`
 * @returns Pointer to the selected SysTick register image
 * @note Thin SysTick LL alias over the shared `REGOPS_REG` macro
 */
#define LL_SysTick_REG(_REG)		REGOPS_REG(SysTick, _REG)

/**
 * @brief Reads one SysTick register image by register pointer
 * @param[in]	pRegister	Pointer to a readable SysTick register image
 * Accepted values:
 * - Non-`NULL`: Address of one readable SysTick `.REG` member
 * @returns Full 32-bit register image currently observed at @p pRegister
 * @note Caller must pass a valid SysTick register pointer
 * @warning Register-specific read side effects remain the caller's responsibility
 */
__STATIC_FORCEINLINE reg LL_SysTick_ReadRegister(const _IO* const pRegister)
{
	// Local Variable
	reg registerImage = 0x00000000UL;

	//! Centralize the full-width volatile read through the shared register utility.
	(void) RegOps_Read(pRegister, &registerImage);
	//! Return the complete image without applying SysTick field interpretation.
	return registerImage;
}

/**
 * @brief Writes one SysTick register image by register pointer
 * @param[in]	pRegister	Pointer to a writable SysTick register image
 * Accepted values:
 * - Non-`NULL`: Address of one writable SysTick `.REG` member
 * @param[in]	registerImage	Full 32-bit register image to write
 * Accepted values:
 * - Register-semantic image already validated and staged by the caller
 * @returns Nothing
 * @note Caller owns register-specific write and preservation semantics
 */
__STATIC_FORCEINLINE void LL_SysTick_WriteRegister(_IO* const pRegister, const reg registerImage)
{
	//! Centralize the full-width volatile write without adding register policy.
	(void) RegOps_Write(pRegister, registerImage);
}

/**
 * @brief Reads the complete SysTick control register image
 * @returns Current `SysTick_CTRL` register image
 * @warning Reading `SysTick_CTRL` clears `COUNTFLAG`
 */
__STATIC_FORCEINLINE reg LL_SysTick_ReadCTRL(void)
{
	//! Select CTRL while the generic primitive owns the actual register read.
	return LL_SysTick_ReadRegister(LL_SysTick_REG(CTRL));
}

/**
 * @brief Writes the complete SysTick control register image
 * @param[in]	registerImage	Complete control-register image
 * Accepted values:
 * - Any image containing only writable `ENABLE`, `TICKINT`, and `CLKSOURCE` state
 * @returns Nothing
 */
__STATIC_FORCEINLINE void LL_SysTick_WriteCTRL(const reg registerImage)
{
	//! Select CTRL while the generic primitive owns the actual register write.
	LL_SysTick_WriteRegister(LL_SysTick_REG(CTRL), registerImage);
}

/**
 * @brief Reads the complete SysTick reload register image
 * @returns Current `SysTick_LOAD` register image
 */
__STATIC_FORCEINLINE reg LL_SysTick_ReadLOAD(void)
{
	//! Select LOAD while the generic primitive owns the actual register read.
	return LL_SysTick_ReadRegister(LL_SysTick_REG(LOAD));
}

/**
 * @brief Writes the complete SysTick reload register image
 * @param[in]	registerImage	Complete reload-register image
 * Accepted values:
 * - `0x00000000UL..0x00FFFFFFUL`
 * @returns Nothing
 */
__STATIC_FORCEINLINE void LL_SysTick_WriteLOAD(const reg registerImage)
{
	//! Select LOAD while the generic primitive owns the actual register write.
	LL_SysTick_WriteRegister(LL_SysTick_REG(LOAD), registerImage);
}

/**
 * @brief Reads the complete SysTick current-value register image
 * @returns Current `SysTick_VAL` register image
 * @note Reading `SysTick_VAL` has no clear side effect
 */
__STATIC_FORCEINLINE reg LL_SysTick_ReadVAL(void)
{
	//! Select VAL while the generic primitive owns the actual register read.
	return LL_SysTick_ReadRegister(LL_SysTick_REG(VAL));
}

/**
 * @brief Writes the SysTick current-value action register
 * @param[in]	registerImage	Full 32-bit action payload to write
 * Accepted values:
 * - Any 32-bit value; hardware ignores the payload and performs the clear action
 * @returns Nothing
 * @warning Any write clears the current counter value and `COUNTFLAG`; the
 * payload is not stored
 */
__STATIC_FORCEINLINE void LL_SysTick_WriteVAL(const reg registerImage)
{
	//! Select VAL while the generic primitive owns the actual action write.
	LL_SysTick_WriteRegister(LL_SysTick_REG(VAL), registerImage);
}

/**
 * @brief Clears the current SysTick counter value and `COUNTFLAG`
 * @returns Nothing
 * @note Any write to `SysTick_VAL` performs the same hardware clear action
 */
__STATIC_FORCEINLINE void LL_SysTick_ResetVAL(void)
{
	//! Express the reset policy through the named VAL writer and its single generic primitive.
	LL_SysTick_WriteVAL(0x00000000UL);
}

/**
 * @brief Reads the complete SysTick calibration register image
 * @returns Current read-only `SysTick_CALIB` register image
 * @note No write conjugate exists because `SysTick_CALIB` is hardware read-only
 */
__STATIC_FORCEINLINE reg LL_SysTick_ReadCALIB(void)
{
	//! Select CALIB while the generic primitive owns the actual register read.
	return LL_SysTick_ReadRegister(LL_SysTick_REG(CALIB));
}

/** @} */ // SYSTICK_02_LL

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SYSTICK_LL_H_ */
