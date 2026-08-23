/**
 * @file	usart_ll.h
 * @author	Shrey Shah
 * @brief	Declares register-near USART access
 * @version	v1.0
 * @date	23-08-2026
 *
 * @details
 * @section USART_LL_H_HIERARCHY Hierarchy
 * - Position: Layer 2 USART hardware-access layer
 * - Used by: Layer 4 USART Driver implementation, Layer 3 USART Codec
 * - Uses: Layer 1 Core USART register model and shared RegOps mechanics
 *
 * @section USART_LL_H_RESPONSIBILITY Responsibility
 * LL owns one shared pointer-based register read/write pair and symmetric
 * named full-register accessors for every currently implemented USART
 * register. It owns no public selector vocabulary, selector-to-field
 * translation, clock-gate policy, or field-level sequencing.
 *
 * @section USART_LL_H_BOUNDARY Dependency Boundary
 * LL accepts and returns full register images only. It performs no
 * validation, batching, or asymmetric acknowledge-sequencing; those
 * decisions belong to the USART Codec and Driver layers.
 *
 * @note `USARTx_GTPR` has no accessor here. It is unclassified raw
 * foundation until Smartcard/IrDA mode is admitted, per the Deferred
 * Domains table in `USART_ARCHITECTURE.md`.
 *
 * @see @ref USART_Peripheral_Guide "USART Implementation Guide"
 */

// Header Guard
#ifndef USART_LL_H_
#define USART_LL_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "stm32f1xx_usart.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup USART_02_LL USART Low-Level Register Access Layer
 * @ingroup USART
 * @brief Dumb, mechanical USART register-image access
 * @details
 * This layer mirrors the Timer/RCC LL pattern: one generic pointer-based
 * register read/write primitive pair, plus named full-register accessors
 * built on it. It knows nothing about USART selector vocabulary, pin
 * mapping, clock-gate state, or the per-bit acknowledge asymmetry
 * documented for `USARTx_SR` in `USART_ARCHITECTURE.md`.
 */

/**
 * @addtogroup USART_02_LL
 * @{
 */

// ==================================================================================================== //
// USART LL Register Access APIs
// ==================================================================================================== //

/**
 * @brief USART LL register access APIs
 * @defgroup USART_02_LL_01_RegisterOps USART LL Register Access APIs
 * @ingroup USART_02_LL
 * @details
 * These functions are intentionally dumb full-register image readers and
 * writers. They do not know USART selector vocabulary, selector-to-field
 * translation, or clock/pin sequencing policy.
 *
 * Practical Rule:
 * - Use `.REG` through @ref `LL_USART_REG` for USART union registers.
 * - Do not use `.BIT` in the LL layer.
 * - Read-modify-write staging for a single field belongs to the Codec and
 *   Driver layers, which commit through this same primitive pair.
 *
 * @warning These accessors perform no NULL, instance, or field-legality
 * checks. The caller owns a valid `USART_TypeDef*` and a register image
 * appropriate for the target register.
 * @{
 */

/**
 * @brief Returns pointer to a USART union register `.REG` image
 * @def LL_USART_REG
 * @param[in] _USARTX Target USART peripheral instance expression
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[in] _REG Union register member token inside @ref USART_TypeDef
 * Accepted values:
 * - `SR`
 * - `DR`
 * - `BRR`
 * - `CR1`
 * - `CR2`
 * - `CR3`
 * @returns Pointer to the selected USART register `.REG` image.
 * @note Thin USART LL alias over @ref `REGOPS_REG`.
 */
#define LL_USART_REG(_USARTX, _REG)				REGOPS_REG((_USARTX), _REG)

/**
 * @brief Reads one USART register image by register pointer
 * @param[in] pRegister Pointer to a readable USART register image
 * Expected values:
 * - Non-`NULL`: Aligned pointer to one readable 32-bit USART register image
 * @returns Full 32-bit register image currently observed at @p `pRegister`.
 * @note Caller must pass a valid USART register pointer.
 */
__STATIC_FORCEINLINE reg LL_USART_ReadRegister(const _IO* const pRegister)
{
	// Local Variable
	reg regImage = 0x00000000UL;
	//! Read the full 32-bit register image into caller-owned storage.
	(void) RegOps_Read(pRegister, &regImage);
	//! Return the full 32-bit register image to the caller.
	return regImage;
}

/**
 * @brief Writes one USART register image by register pointer
 * @param[in] pRegister Pointer to a writable USART register image
 * Expected values:
 * - Non-`NULL`: Aligned pointer to one writable 32-bit USART register image
 * @param[in] regImage Full 32-bit register image to write
 * Accepted values:
 * - `0x00000000UL..0xFFFFFFFFUL`: Complete caller-staged register image
 * @note Caller must pass a valid writable USART register pointer and a
 * complete register image appropriate for that register.
 */
__STATIC_FORCEINLINE void LL_USART_WriteRegister(_IO* const pRegister, const reg regImage)
{
	//! Forward the complete image without adding register-specific policy.
	(void) RegOps_Write(pRegister, regImage);
}

/**
 * @brief Reads the USART `SR` register image
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @returns Full `USARTx_SR` image.
 * @note The per-bit acknowledge mechanism (write-0-to-clear for `TC`/`CTS`,
 * read-`SR`-then-read-`DR` for the remaining error/status flags) belongs to
 * the Codec and Driver layers, not here.
 */
__STATIC_FORCEINLINE reg LL_USART_ReadSR(const USART_TypeDef* const USARTx)
{
	//! Address the SR union image through the shared register-pointer accessor.
	return LL_USART_ReadRegister(LL_USART_REG(USARTx, SR));
}

/**
 * @brief Writes the USART `SR` register image
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[in] regImage Full `USARTx_SR` image to write
 * Accepted values:
 * - `0x00000000UL..0xFFFFFFFFUL`: Complete caller-staged `USARTx_SR` image
 * @note Caller owns the write-0-to-clear staging for `TC`/`CTS`; writing a
 * bit that is `1` in @p `regImage` has no clearing effect on those two flags.
 */
__STATIC_FORCEINLINE void LL_USART_WriteSR(USART_TypeDef* const USARTx, const reg regImage)
{
	//! Forward the staged SR image without modifying unrelated flags.
	LL_USART_WriteRegister(LL_USART_REG(USARTx, SR), regImage);
}

/**
 * @brief Reads the USART `DR` register image
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @returns Full `USARTx_DR` image; reading `DR` also participates in the
 * hardware error-flag clearing sequence documented for `SR`.
 */
__STATIC_FORCEINLINE reg LL_USART_ReadDR(const USART_TypeDef* const USARTx)
{
	//! Address the DR union image through the shared register-pointer accessor.
	return LL_USART_ReadRegister(LL_USART_REG(USARTx, DR));
}

/**
 * @brief Writes the USART `DR` register image
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[in] regImage Full `USARTx_DR` image to write
 * Accepted values:
 * - `0x00000000UL..0x000001FFUL`: 9-bit data value in the low bits of a
 *   complete caller-staged `USARTx_DR` image
 * @note Writing `DR` queues one byte/word for transmission; it does not
 * itself wait for `TXE`.
 */
__STATIC_FORCEINLINE void LL_USART_WriteDR(USART_TypeDef* const USARTx, const reg regImage)
{
	//! Forward the staged DR image; TXE/TC readiness is a Driver concern.
	LL_USART_WriteRegister(LL_USART_REG(USARTx, DR), regImage);
}

/**
 * @brief Reads the USART `BRR` register image
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @returns Full `USARTx_BRR` image.
 * @note Mantissa/fraction divider math belongs to @ref usart_codec.h.
 */
__STATIC_FORCEINLINE reg LL_USART_ReadBRR(const USART_TypeDef* const USARTx)
{
	//! Address the BRR union image through the shared register-pointer accessor.
	return LL_USART_ReadRegister(LL_USART_REG(USARTx, BRR));
}

/**
 * @brief Writes the USART `BRR` register image
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[in] regImage Full `USARTx_BRR` image to write
 * Accepted values:
 * - `0x00000000UL..0x0000FFFFUL`: Complete caller-staged `USARTx_BRR` image
 * @note Caller owns mantissa/fraction field staging before this write.
 */
__STATIC_FORCEINLINE void LL_USART_WriteBRR(USART_TypeDef* const USARTx, const reg regImage)
{
	//! Forward the staged BRR image without modifying unrelated bits.
	LL_USART_WriteRegister(LL_USART_REG(USARTx, BRR), regImage);
}

/**
 * @brief Reads the USART `CR1` register image
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @returns Full `USARTx_CR1` image.
 * @note Selector field extraction belongs to @ref usart_codec.h.
 */
__STATIC_FORCEINLINE reg LL_USART_ReadCR1(const USART_TypeDef* const USARTx)
{
	//! Address the CR1 union image through the shared register-pointer accessor.
	return LL_USART_ReadRegister(LL_USART_REG(USARTx, CR1));
}

/**
 * @brief Writes the USART `CR1` register image
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[in] regImage Full `USARTx_CR1` image to write
 * Accepted values:
 * - `0x00000000UL..0xFFFFFFFFUL`: Complete caller-staged `USARTx_CR1` image
 * @note Caller owns read-modify-write staging for the fields it intends to change.
 */
__STATIC_FORCEINLINE void LL_USART_WriteCR1(USART_TypeDef* const USARTx, const reg regImage)
{
	//! Forward the staged CR1 image without modifying unrelated fields.
	LL_USART_WriteRegister(LL_USART_REG(USARTx, CR1), regImage);
}

/**
 * @brief Reads the USART `CR2` register image
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @returns Full `USARTx_CR2` image.
 * @note Selector field extraction belongs to @ref usart_codec.h.
 */
__STATIC_FORCEINLINE reg LL_USART_ReadCR2(const USART_TypeDef* const USARTx)
{
	//! Address the CR2 union image through the shared register-pointer accessor.
	return LL_USART_ReadRegister(LL_USART_REG(USARTx, CR2));
}

/**
 * @brief Writes the USART `CR2` register image
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[in] regImage Full `USARTx_CR2` image to write
 * Accepted values:
 * - `0x00000000UL..0xFFFFFFFFUL`: Complete caller-staged `USARTx_CR2` image
 * @note Caller owns read-modify-write staging for the fields it intends to change.
 */
__STATIC_FORCEINLINE void LL_USART_WriteCR2(USART_TypeDef* const USARTx, const reg regImage)
{
	//! Forward the staged CR2 image without modifying unrelated fields.
	LL_USART_WriteRegister(LL_USART_REG(USARTx, CR2), regImage);
}

/**
 * @brief Reads the USART `CR3` register image
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @returns Full `USARTx_CR3` image.
 * @note Selector field extraction belongs to @ref usart_codec.h.
 */
__STATIC_FORCEINLINE reg LL_USART_ReadCR3(const USART_TypeDef* const USARTx)
{
	//! Address the CR3 union image through the shared register-pointer accessor.
	return LL_USART_ReadRegister(LL_USART_REG(USARTx, CR3));
}

/**
 * @brief Writes the USART `CR3` register image
 * @param[in] USARTx Target USART peripheral instance
 * Accepted values:
 * - @ref `USART1`
 * - @ref `USART2`
 * - @ref `USART3`
 * @param[in] regImage Full `USARTx_CR3` image to write
 * Accepted values:
 * - `0x00000000UL..0xFFFFFFFFUL`: Complete caller-staged `USARTx_CR3` image
 * @note Caller owns read-modify-write staging for the fields it intends to change.
 */
__STATIC_FORCEINLINE void LL_USART_WriteCR3(USART_TypeDef* const USARTx, const reg regImage)
{
	//! Forward the staged CR3 image without modifying unrelated fields.
	LL_USART_WriteRegister(LL_USART_REG(USARTx, CR3), regImage);
}

/** @} */ // USART_02_LL_01_RegisterOps

/** @} */ // USART_02_LL

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USART_LL_H_ */
