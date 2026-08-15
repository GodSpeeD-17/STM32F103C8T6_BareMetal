/**
 * @file	timer_ll.h
 * @author	Shrey Shah
 * @brief	Timer Low-Level Register Access Interface
 * @version	v1.0
 * @date	07-06-2026
 *
 * @details
 * This header defines the Timer low-level module that sits directly above the
 * register-layer definitions from `stm32f1xx_timer.h`.
 *
 * LL authority is intentionally narrow. It owns dumb Timer register access:
 * - static inline read/write accessors for Timer register images
 * - minimal register-address macros needed to select C struct members
 *
 * This module does not own:
 * - Timer selector vocabulary definitions
 * - public selector to raw field translation
 * - CR1/CR2/SMCR/CCMR/CCER/DIER/SR bitfield placement, packing, or decoding
 * - channel-mask to channel-index translation
 * - public driver policy validation
 * - clock enable/reset sequencing
 * - staged batching policy
 * - interrupt or NVIC policy
 *
 * Practical Authority Rule:
 * - Layer 0 (`stm32f1xx_timer.h`) defines the raw Timer register map.
 * - LL exposes named full-register accessors only.
 * - Codec APIs own selector translation and register-image mutation.
 * - RegOps owns peripheral-independent register access and compare/write mechanics.
 * - Driver APIs (`timer.h` / `timer.c`) own public validation, sequencing,
 *   clock enable, batching, register-specific dirty-write decisions, and
 *   user-facing status.
 *
 * @note Functions in this file do not validate @ref TIM_TypeDef pointers, do
 * not check clock state, and do not preserve unrelated register bits unless the
 * caller supplies a pre-staged full register image.
 */

#ifndef TIMER_LL_H_
#define TIMER_LL_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx_timer.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup TIM_02_LL Timer Low-Level Register Access Layer
 * @ingroup TIM
 * @brief Register-near Timer access interface used by the Timer driver layer
 * @details
 * This layer exposes direct full-register image reads and writes. It does not
 * encode public selectors, validate Timer configurations, choose mode-specific
 * behavior, or decide when a register should be read or written.
 */

/**
 * @addtogroup TIM_02_LL
 * @{
 */

// ==================================================================================================== //
//										Timer LL Register Access APIs									//
// ==================================================================================================== //

/**
 * @brief Timer LL register access APIs
 * @defgroup TIM_02_LL_01_RegisterOps Timer LL Register Access APIs
 * @ingroup TIM_02_LL
 * @details
 * These functions are intentionally dumb full-register image readers and
 * writers. They do not know public Timer selectors, Timer channel masks, raw
 * field positions, or update/interrupt policy.
 *
 * Practical Rule:
 * - Use `.REG` through @ref LL_TIM_REG for Timer union registers.
 * - Use @ref LL_TIM_SCALAR_REG for direct scalar register members.
 * - Do not use `.BIT` in the LL layer.
 * - Read-modify-write policy belongs to the caller, not to this LL layer.
 *
 * @warning These accessors perform no NULL, instance-validity, clock,
 * reserved-bit, or write-permission checks.
 * @{
 */

/**
 * @brief Returns pointer to a Timer union register `.REG` image
 * @def LL_TIM_REG
 * @param[in]	_TIMX	Target Timer peripheral instance expression
 * @param[in]	_REG	Union register member token inside @ref TIM_TypeDef
 * @returns Pointer to the selected Timer register `.REG` image.
 * @note Thin Timer LL alias over @ref REGOPS_REG.
 * @note Use this only for union registers that expose a `.REG` member.
 */
#define LL_TIM_REG(_TIMX, _REG)					REGOPS_REG((_TIMX), _REG)

/**
 * @brief Returns pointer to a Timer scalar register image
 * @def LL_TIM_SCALAR_REG
 * @param[in]	_TIMX	Target Timer peripheral instance expression
 * @param[in]	_REG	Scalar register member token inside @ref TIM_TypeDef
 * @returns Pointer to the selected Timer scalar register image.
 * @note Use this for direct `_IO` members such as `CNT`, `PSC`, `ARR`, and `DMAR`.
 */
#define LL_TIM_SCALAR_REG(_TIMX, _REG)			(&((_TIMX)->_REG))

/**
 * @brief Reads one Timer register image by register pointer
 * @param[in]	pRegister	Pointer to a Timer register image
 * @returns Full 32-bit register image currently observed at @p pRegister.
 * @note Caller must pass a valid Timer register pointer.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadRegister(const _IO* const pRegister)
{
	// Local Variable
	reg regImage = 0x00000000UL;
	//! Read the full 32-bit register image into caller-owned storage.
	(void) RegOps_Read(pRegister, &regImage);
	//! Return the full 32-bit register image to the caller.
	return regImage;
}

/**
 * @brief Writes one Timer register image by register pointer
 * @param[in]	pRegister	Pointer to a writable Timer register image
 * @param[in]	regImage	Full 32-bit register image to write
 * @note Caller must pass a valid writable Timer register pointer and a complete
 * register image appropriate for that register.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteRegister(_IO* const pRegister, const reg regImage)
{
	//! Forward the complete image without adding register-specific policy.
	(void) RegOps_Write(pRegister, regImage);
}

/**
 * @brief Reads the Timer `CR1` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_CR1` image.
 * @note Counter mode, direction, preload, update-source, one-pulse, and clock
 * division extraction are codec responsibilities.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadCR1(const TIM_TypeDef* const TIMx)
{
	//! Address the CR1 union image through the shared register-pointer accessor.
	return LL_TIM_ReadRegister(LL_TIM_REG(TIMx, CR1));
}

/**
 * @brief Writes the Timer `CR1` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_CR1` image to write
 * @note Caller owns read-modify-write staging and raw field placement.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteCR1(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the staged CR1 image without modifying unrelated fields.
	LL_TIM_WriteRegister(LL_TIM_REG(TIMx, CR1), regImage);
}

/**
 * @brief Reads the Timer `CR2` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_CR2` image.
 * @note DMA selection and master-mode interpretation belong above LL.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadCR2(const TIM_TypeDef* const TIMx)
{
	//! Address the CR2 union image through the shared register-pointer accessor.
	return LL_TIM_ReadRegister(LL_TIM_REG(TIMx, CR2));
}

/**
 * @brief Writes the Timer `CR2` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_CR2` image to write
 * @note Caller owns read-modify-write staging and raw field placement.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteCR2(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the staged CR2 image without modifying unrelated fields.
	LL_TIM_WriteRegister(LL_TIM_REG(TIMx, CR2), regImage);
}

/**
 * @brief Reads the Timer `SMCR` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_SMCR` image.
 * @note Slave-mode and trigger-source interpretation belong above LL.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadSMCR(const TIM_TypeDef* const TIMx)
{
	//! Address the SMCR union image through the shared register-pointer accessor.
	return LL_TIM_ReadRegister(LL_TIM_REG(TIMx, SMCR));
}

/**
 * @brief Writes the Timer `SMCR` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_SMCR` image to write
 * @note Caller owns read-modify-write staging and raw field placement.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteSMCR(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the staged SMCR image without modifying unrelated fields.
	LL_TIM_WriteRegister(LL_TIM_REG(TIMx, SMCR), regImage);
}

/**
 * @brief Reads the Timer `DIER` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_DIER` image.
 * @note IRQ/DMA selector extraction and NVIC policy belong above LL.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadDIER(const TIM_TypeDef* const TIMx)
{
	//! Address the DIER union image through the shared register-pointer accessor.
	return LL_TIM_ReadRegister(LL_TIM_REG(TIMx, DIER));
}

/**
 * @brief Writes the Timer `DIER` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_DIER` image to write
 * @note Caller owns IRQ/DMA source staging and any NVIC side effects.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteDIER(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the staged DIER image without applying interrupt policy.
	LL_TIM_WriteRegister(LL_TIM_REG(TIMx, DIER), regImage);
}

/**
 * @brief Reads the Timer `SR` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_SR` image.
 * @note IRQ status extraction and acknowledge-mask staging belong above LL.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadSR(const TIM_TypeDef* const TIMx)
{
	//! Address the SR union image through the shared register-pointer accessor.
	return LL_TIM_ReadRegister(LL_TIM_REG(TIMx, SR));
}

/**
 * @brief Writes the Timer `SR` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_SR` image to write
 * @note Caller owns flag clear semantics and must stage a complete raw status
 * register image.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteSR(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the staged SR image exactly so write-zero-to-clear semantics remain caller-owned.
	LL_TIM_WriteRegister(LL_TIM_REG(TIMx, SR), regImage);
}

/**
 * @brief Writes the Timer `EGR` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_EGR` image to write
 * @note Caller owns event-generation policy and any follow-up flag handling.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteEGR(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the staged EGR image without generating additional events.
	LL_TIM_WriteRegister(LL_TIM_REG(TIMx, EGR), regImage);
}

/**
 * @brief Reads the Timer `CCMR1` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_CCMR1` image.
 * @note Channel 1/2 output-compare and input-capture field extraction belongs
 * to the codec layer.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadCCMR1(const TIM_TypeDef* const TIMx)
{
	//! Address the CCMR1 union image through the shared register-pointer accessor.
	return LL_TIM_ReadRegister(LL_TIM_REG(TIMx, CCMR1));
}

/**
 * @brief Writes the Timer `CCMR1` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_CCMR1` image to write
 * @note Caller owns channel 1/2 staging and raw field placement.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteCCMR1(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the staged CCMR1 image without interpreting channel mode.
	LL_TIM_WriteRegister(LL_TIM_REG(TIMx, CCMR1), regImage);
}

/**
 * @brief Reads the Timer `CCMR2` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_CCMR2` image.
 * @note Channel 3/4 output-compare and input-capture field extraction belongs
 * to the codec layer.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadCCMR2(const TIM_TypeDef* const TIMx)
{
	//! Address the CCMR2 union image through the shared register-pointer accessor.
	return LL_TIM_ReadRegister(LL_TIM_REG(TIMx, CCMR2));
}

/**
 * @brief Writes the Timer `CCMR2` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_CCMR2` image to write
 * @note Caller owns channel 3/4 staging and raw field placement.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteCCMR2(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the staged CCMR2 image without interpreting channel mode.
	LL_TIM_WriteRegister(LL_TIM_REG(TIMx, CCMR2), regImage);
}

/**
 * @brief Reads the Timer `CCER` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_CCER` image.
 * @note Channel enable and polarity extraction belong to the codec layer.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadCCER(const TIM_TypeDef* const TIMx)
{
	//! Address the CCER union image through the shared register-pointer accessor.
	return LL_TIM_ReadRegister(LL_TIM_REG(TIMx, CCER));
}

/**
 * @brief Writes the Timer `CCER` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_CCER` image to write
 * @note Caller owns capture/compare enable and polarity staging.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteCCER(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the staged CCER image without applying channel policy.
	LL_TIM_WriteRegister(LL_TIM_REG(TIMx, CCER), regImage);
}

/**
 * @brief Reads the Timer `CNT` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_CNT` image.
 * @note Public counter-width handling belongs above LL.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadCNT(const TIM_TypeDef* const TIMx)
{
	//! Use the scalar-register path because CNT has no `.REG` union member.
	return LL_TIM_ReadRegister(LL_TIM_SCALAR_REG(TIMx, CNT));
}

/**
 * @brief Writes the Timer `CNT` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_CNT` image to write
 * @note Caller owns counter-width masking and sequencing.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteCNT(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the full scalar CNT image without applying counter-width policy.
	LL_TIM_WriteRegister(LL_TIM_SCALAR_REG(TIMx, CNT), regImage);
}

/**
 * @brief Reads the Timer `PSC` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_PSC` image.
 * @note Prescaler value extraction belongs above LL.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadPSC(const TIM_TypeDef* const TIMx)
{
	//! Use the scalar-register path because PSC has no `.REG` union member.
	return LL_TIM_ReadRegister(LL_TIM_SCALAR_REG(TIMx, PSC));
}

/**
 * @brief Writes the Timer `PSC` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_PSC` image to write
 * @note Caller owns prescaler masking and update-event sequencing.
 */
__STATIC_FORCEINLINE void LL_TIM_WritePSC(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the full scalar PSC image without forcing an update event.
	LL_TIM_WriteRegister(LL_TIM_SCALAR_REG(TIMx, PSC), regImage);
}

/**
 * @brief Reads the Timer `ARR` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_ARR` image.
 * @note Auto-reload value extraction belongs above LL.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadARR(const TIM_TypeDef* const TIMx)
{
	//! Use the scalar-register path because ARR has no `.REG` union member.
	return LL_TIM_ReadRegister(LL_TIM_SCALAR_REG(TIMx, ARR));
}

/**
 * @brief Writes the Timer `ARR` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_ARR` image to write
 * @note Caller owns auto-reload masking and update-event sequencing.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteARR(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the full scalar ARR image without forcing an update event.
	LL_TIM_WriteRegister(LL_TIM_SCALAR_REG(TIMx, ARR), regImage);
}

/**
 * @brief Reads the Timer `CCR1` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_CCR1` image.
 * @note In input-capture mode, reading `CCRx` consumes the corresponding
 * `CCxIF` flag. The Driver must own that consuming-read policy.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadCCR1(const TIM_TypeDef* const TIMx)
{
	//! Read the shared channel-1 storage through its read-only input view.
	return LL_TIM_ReadRegister(&(TIMx->CCR1.CC1_IN));
}

/**
 * @brief Writes the Timer `CCR1` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_CCR1` image to write
 * @note Caller owns capture/compare value masking and channel-mode policy.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteCCR1(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Write the shared channel-1 storage without interpreting capture versus compare mode.
	LL_TIM_WriteRegister(&(TIMx->CCR1.CC1_OUT), regImage);
}

/**
 * @brief Reads the Timer `CCR2` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_CCR2` image.
 * @note In input-capture mode, reading `CCRx` consumes the corresponding
 * `CCxIF` flag. The Driver must own that consuming-read policy.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadCCR2(const TIM_TypeDef* const TIMx)
{
	//! Read the shared channel-2 storage through its read-only input view.
	return LL_TIM_ReadRegister(&(TIMx->CCR2.CC2_IN));
}

/**
 * @brief Writes the Timer `CCR2` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_CCR2` image to write
 * @note Caller owns capture/compare value masking and channel-mode policy.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteCCR2(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Write the shared channel-2 storage without interpreting capture versus compare mode.
	LL_TIM_WriteRegister(&(TIMx->CCR2.CC2_OUT), regImage);
}

/**
 * @brief Reads the Timer `CCR3` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_CCR3` image.
 * @note In input-capture mode, reading `CCRx` consumes the corresponding
 * `CCxIF` flag. The Driver must own that consuming-read policy.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadCCR3(const TIM_TypeDef* const TIMx)
{
	//! Read the shared channel-3 storage through its read-only input view.
	return LL_TIM_ReadRegister(&(TIMx->CCR3.CC3_IN));
}

/**
 * @brief Writes the Timer `CCR3` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_CCR3` image to write
 * @note Caller owns capture/compare value masking and channel-mode policy.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteCCR3(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Write the shared channel-3 storage without interpreting capture versus compare mode.
	LL_TIM_WriteRegister(&(TIMx->CCR3.CC3_OUT), regImage);
}

/**
 * @brief Reads the Timer `CCR4` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_CCR4` image.
 * @note In input-capture mode, reading `CCRx` consumes the corresponding
 * `CCxIF` flag. The Driver must own that consuming-read policy.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadCCR4(const TIM_TypeDef* const TIMx)
{
	//! Read the shared channel-4 storage through its read-only input view.
	return LL_TIM_ReadRegister(&(TIMx->CCR4.CC4_IN));
}

/**
 * @brief Writes the Timer `CCR4` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_CCR4` image to write
 * @note Caller owns capture/compare value masking and channel-mode policy.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteCCR4(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Write the shared channel-4 storage without interpreting capture versus compare mode.
	LL_TIM_WriteRegister(&(TIMx->CCR4.CC4_OUT), regImage);
}

/**
 * @brief Reads the Timer `DCR` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Full `TIMx_DCR` image.
 * @note DMA-burst base/length extraction belongs above LL.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadDCR(const TIM_TypeDef* const TIMx)
{
	//! Address the DCR union image through the shared register-pointer accessor.
	return LL_TIM_ReadRegister(LL_TIM_REG(TIMx, DCR));
}

/**
 * @brief Writes the Timer `DCR` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_DCR` image to write
 * @note Caller owns DMA-burst base/length staging.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteDCR(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the staged DCR image without interpreting DMA burst fields.
	LL_TIM_WriteRegister(LL_TIM_REG(TIMx, DCR), regImage);
}

/**
 * @brief Reads the Timer `DMAR` register image
 * @param[in]	TIMx	Timer peripheral instance
 * @returns Current 16-bit `TIMx_DMAR` portal payload in a register image.
 * @note `TIMx_DMAR` is a transfer portal rather than stable configuration
 * state. DMA-burst direction, width, and sequencing belong above LL.
 */
__STATIC_FORCEINLINE reg LL_TIM_ReadDMAR(const TIM_TypeDef* const TIMx)
{
	//! Use the scalar-register path because DMAR has no `.REG` union member.
	return LL_TIM_ReadRegister(LL_TIM_SCALAR_REG(TIMx, DMAR));
}

/**
 * @brief Writes the Timer `DMAR` register image
 * @param[in]	TIMx		Timer peripheral instance
 * @param[in]	regImage	Full `TIMx_DMAR` image to write
 * @note Caller owns the 16-bit payload constraint plus DMA-burst direction,
 * width, and sequencing policy.
 */
__STATIC_FORCEINLINE void LL_TIM_WriteDMAR(TIM_TypeDef* const TIMx, const reg regImage)
{
	//! Forward the full scalar DMAR image without applying DMA transfer policy.
	LL_TIM_WriteRegister(LL_TIM_SCALAR_REG(TIMx, DMAR), regImage);
}

/** @} */ // TIM_02_LL_01_RegisterOps

/** @} */ // TIM_02_LL

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_LL_H_ */
