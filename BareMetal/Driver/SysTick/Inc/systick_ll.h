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
 * This Layer 1 LL interface performs only named, full-width SysTick register
 * reads and writes.
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
 * @brief Reads the complete SysTick control register image
 * @returns Current `SysTick_CTRL` register image
 * @warning Reading `SysTick_CTRL` clears `COUNTFLAG`
 */
__STATIC_FORCEINLINE reg LL_SysTick_ReadCTRL(void)
{
	//! Keep destructive-read awareness at the named register-access boundary.
	return SysTick->CTRL.REG;
}

/**
 * @brief Writes the complete SysTick control register image
 * @param[in] registerImage Complete control-register image
 * Accepted values:
 * - Any image containing only writable `ENABLE`, `TICKINT`, and `CLKSOURCE` state
 * @returns Nothing
 */
__STATIC_FORCEINLINE void LL_SysTick_WriteCTRL(const reg registerImage)
{
	//! Commit one full-width control word without compiler-generated bitfield access.
	SysTick->CTRL.REG = registerImage;
}

/**
 * @brief Reads the complete SysTick reload register image
 * @returns Current `SysTick_LOAD` register image
 */
__STATIC_FORCEINLINE reg LL_SysTick_ReadLOAD(void)
{
	//! Read the full hardware word so field extraction remains Driver policy.
	return SysTick->LOAD.REG;
}

/**
 * @brief Writes the complete SysTick reload register image
 * @param[in] registerImage Complete reload-register image
 * Accepted values:
 * - `0x00000000UL..0x00FFFFFFUL`
 * @returns Nothing
 */
__STATIC_FORCEINLINE void LL_SysTick_WriteLOAD(const reg registerImage)
{
	//! Commit the validated reload image in one full-width hardware write.
	SysTick->LOAD.REG = registerImage;
}

/**
 * @brief Clears the current SysTick counter value and `COUNTFLAG`
 * @returns Nothing
 * @note Any write to `SysTick_VAL` performs the same hardware clear action
 */
__STATIC_FORCEINLINE void LL_SysTick_ResetVAL(void)
{
	//! Use the documented zero payload for the write-to-clear action port.
	SysTick->VAL.REG = 0x00000000UL;
}

/** @} */ // SYSTICK_02_LL

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SYSTICK_LL_H_ */
