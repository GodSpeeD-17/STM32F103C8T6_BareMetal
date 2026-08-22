/**
 * @file	gpio_irq_ll.h
 * @author	Shrey Shah
 * @brief	GPIO IRQ Low-Level Register Access Interface
 * @version	v2.0
 * @date	31-03-2026
 *
 * @details
 * This header defines the GPIO IRQ low-level module that sits directly above
 * the raw EXTI and AFIO register-layer definitions used for GPIO-backed IRQs.
 *
 * LL authority is intentionally narrow. It owns dumb EXTI/AFIO register access:
 * - static inline read/write accessors for EXTI register images
 * - static inline read/write accessors for AFIO EXTICR register images
 * - the minimal register-address macros needed to select C struct members
 * - enabling or disabling the AFIO APB2 clock gate through RCC LL
 *
 * This module does not own:
 * - GPIO pin selector, mask, or index translation
 * - AFIO EXTICR field placement, packing, or decoding
 * - EXTI trigger selector translation
 * - NVIC enable/disable policy
 * - public driver validation
 * - staged batching policy
 *
 * Practical Authority Rule:
 * - Layer 0 (`stm32f1xx_exti.h` / `stm32f1xx_afio.h`) defines raw registers.
 * - LL exposes named full-register accessors and thin AFIO clock forwarding.
 * - Codec APIs own selector translation and staged image mutation.
 * - Driver APIs own public validation,
 *   sequencing, NVIC policy, and user-facing status.
 *
 * @note Functions in this file do not validate pointers, do not check clock
 * state, and do not preserve unrelated register bits unless the caller supplies
 * a pre-staged full register image.
 */

#ifndef LL_GPIO_IRQ_H_
#define LL_GPIO_IRQ_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx.h"
#include "rcc_ll.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup GPIO_IRQ_02_LL GPIO IRQ Low-Level Control Layer
 * @brief Dumb EXTI/AFIO register-image access used by GPIO IRQ drivers
 */

/**
 * @addtogroup GPIO_IRQ_02_LL
 * @{
 */

// ==================================================================================================== //
//                                   GPIO IRQ LL Register Access APIs                                  //
// ==================================================================================================== //

/**
 * @brief GPIO IRQ LL Register Access APIs
 * @defgroup GPIO_IRQ_02_LL_01_RegisterOps GPIO IRQ LL Register Access APIs
 * @ingroup GPIO_IRQ_02_LL
 * @details
 * These functions are intentionally dumb full-register image readers and
 * writers. They do not know GPIO pins, EXTI line ownership, AFIO EXTICR field
 * layout, trigger selectors, or NVIC policy.
 *
 * Practical Rule:
 * - Always access EXTI and AFIO registers through the `.REG` member.
 * - Do not use the `.BIT` view in the LL layer.
 * - Use named static inline accessors in driver code.
 * - Read-modify-write policy belongs to the caller, not to this LL layer.
 *
 * @warning These accessors perform no NULL, clock, reserved-bit, or
 * write-permission checks.
 * @{
 */

/**
 * @brief Returns pointer to an EXTI register `.REG` image
 * @def LL_GPIO_IRQ_EXTI_REG
 * @param[in]	_REG	Register member token inside @ref `EXTI_TypeDef`
 * @returns Pointer to the selected EXTI register `.REG` image.
 * @note Thin GPIO IRQ LL alias over @ref `REGOPS_REG`.
 */
#define LL_GPIO_IRQ_EXTI_REG(_REG)						REGOPS_REG(EXTI, _REG)

/**
 * @brief Returns pointer to an AFIO register `.REG` image
 * @def LL_GPIO_IRQ_AFIO_REG
 * @param[in]	_REG	Register member token inside @ref `AFIO_TypeDef`
 * @returns Pointer to the selected AFIO register `.REG` image.
 * @note Thin GPIO IRQ LL alias over @ref `REGOPS_REG`.
 */
#define LL_GPIO_IRQ_AFIO_REG(_REG)						REGOPS_REG(AFIO, _REG)

/**
 * @brief Reads one EXTI/AFIO register image by register pointer
 * @param[in]	pRegister	Pointer to an EXTI/AFIO `.REG` member
 * @returns Full 32-bit register image currently observed at @p pRegister.
 * @note Caller must pass a valid register pointer.
 */
__STATIC_FORCEINLINE reg LL_GPIO_IRQ_ReadRegister(const _IO* const pRegister)
{
	reg regImage = 0x00000000UL;
	(void) RegOps_Read(pRegister, &regImage);
	return regImage;
}

/**
 * @brief Writes one EXTI/AFIO register image by register pointer
 * @param[in]	pRegister	Pointer to a writable EXTI/AFIO `.REG` member
 * @param[in]	regImage	Full 32-bit register image to write
 * @returns Void.
 * @note Caller must pass a valid writable register pointer and a complete
 * register image appropriate for that register.
 */
__STATIC_FORCEINLINE void LL_GPIO_IRQ_WriteRegister(_IO* const pRegister, const reg regImage)
{
	(void) RegOps_Write(pRegister, regImage);
}

/**
 * @brief Reads the EXTI `IMR` register image
 * @returns Full `EXTI_IMR` image.
 * @note EXTI line masking policy belongs above LL.
 */
__STATIC_FORCEINLINE reg LL_GPIO_IRQ_ReadIMR(void)
{
	return LL_GPIO_IRQ_ReadRegister(LL_GPIO_IRQ_EXTI_REG(IMR));
}

/**
 * @brief Writes the EXTI `IMR` register image
 * @param[in]	regImage	Full `EXTI_IMR` image to write
 * @returns Void.
 * @note Caller owns read-modify-write staging and line-mask placement.
 */
__STATIC_FORCEINLINE void LL_GPIO_IRQ_WriteIMR(const reg regImage)
{
	LL_GPIO_IRQ_WriteRegister(LL_GPIO_IRQ_EXTI_REG(IMR), regImage);
}

/**
 * @brief Reads the EXTI `EMR` register image
 * @returns Full `EXTI_EMR` image.
 * @note EXTI event masking policy belongs above LL.
 */
__STATIC_FORCEINLINE reg LL_GPIO_IRQ_ReadEMR(void)
{
	return LL_GPIO_IRQ_ReadRegister(LL_GPIO_IRQ_EXTI_REG(EMR));
}

/**
 * @brief Writes the EXTI `EMR` register image
 * @param[in]	regImage	Full `EXTI_EMR` image to write
 * @returns Void.
 * @note Caller owns read-modify-write staging and event-mask placement.
 */
__STATIC_FORCEINLINE void LL_GPIO_IRQ_WriteEMR(const reg regImage)
{
	LL_GPIO_IRQ_WriteRegister(LL_GPIO_IRQ_EXTI_REG(EMR), regImage);
}

/**
 * @brief Reads the EXTI `RTSR` register image
 * @returns Full `EXTI_RTSR` image.
 * @note Rising-trigger selector translation belongs above LL.
 */
__STATIC_FORCEINLINE reg LL_GPIO_IRQ_ReadRTSR(void)
{
	return LL_GPIO_IRQ_ReadRegister(LL_GPIO_IRQ_EXTI_REG(RTSR));
}

/**
 * @brief Writes the EXTI `RTSR` register image
 * @param[in]	regImage	Full `EXTI_RTSR` image to write
 * @returns Void.
 * @note Caller owns read-modify-write staging and trigger-bit placement.
 */
__STATIC_FORCEINLINE void LL_GPIO_IRQ_WriteRTSR(const reg regImage)
{
	LL_GPIO_IRQ_WriteRegister(LL_GPIO_IRQ_EXTI_REG(RTSR), regImage);
}

/**
 * @brief Reads the EXTI `FTSR` register image
 * @returns Full `EXTI_FTSR` image.
 * @note Falling-trigger selector translation belongs above LL.
 */
__STATIC_FORCEINLINE reg LL_GPIO_IRQ_ReadFTSR(void)
{
	return LL_GPIO_IRQ_ReadRegister(LL_GPIO_IRQ_EXTI_REG(FTSR));
}

/**
 * @brief Writes the EXTI `FTSR` register image
 * @param[in]	regImage	Full `EXTI_FTSR` image to write
 * @returns Void.
 * @note Caller owns read-modify-write staging and trigger-bit placement.
 */
__STATIC_FORCEINLINE void LL_GPIO_IRQ_WriteFTSR(const reg regImage)
{
	LL_GPIO_IRQ_WriteRegister(LL_GPIO_IRQ_EXTI_REG(FTSR), regImage);
}

/**
 * @brief Reads the EXTI `SWIER` register image
 * @returns Full `EXTI_SWIER` image.
 * @note Software interrupt/event policy belongs above LL.
 */
__STATIC_FORCEINLINE reg LL_GPIO_IRQ_ReadSWIER(void)
{
	return LL_GPIO_IRQ_ReadRegister(LL_GPIO_IRQ_EXTI_REG(SWIER));
}

/**
 * @brief Writes the EXTI `SWIER` register image
 * @param[in]	regImage	Full `EXTI_SWIER` image to write
 * @returns Void.
 * @note Caller owns software interrupt/event selection.
 */
__STATIC_FORCEINLINE void LL_GPIO_IRQ_WriteSWIER(const reg regImage)
{
	LL_GPIO_IRQ_WriteRegister(LL_GPIO_IRQ_EXTI_REG(SWIER), regImage);
}

/**
 * @brief Reads the EXTI `PR` register image
 * @returns Full `EXTI_PR` image.
 * @note Pending-line selection and acknowledgement policy belong above LL.
 */
__STATIC_FORCEINLINE reg LL_GPIO_IRQ_ReadPR(void)
{
	return LL_GPIO_IRQ_ReadRegister(LL_GPIO_IRQ_EXTI_REG(PR));
}

/**
 * @brief Writes the EXTI `PR` register image
 * @param[in]	regImage	Full `EXTI_PR` image to write
 * @returns Void.
 * @note `PR` is a write-one-to-clear register. Caller owns the line mask.
 */
__STATIC_FORCEINLINE void LL_GPIO_IRQ_WritePR(const reg regImage)
{
	LL_GPIO_IRQ_WriteRegister(LL_GPIO_IRQ_EXTI_REG(PR), regImage);
}

/**
 * @brief Reads the AFIO `EXTICR1` register image
 * @returns Full `AFIO_EXTICR1` image.
 * @note EXTICR field extraction and interpretation belong above LL.
 */
__STATIC_FORCEINLINE reg LL_GPIO_IRQ_ReadEXTICR1(void)
{
	return LL_GPIO_IRQ_ReadRegister(LL_GPIO_IRQ_AFIO_REG(EXTICR1));
}

/**
 * @brief Writes the AFIO `EXTICR1` register image
 * @param[in]	regImage	Full `AFIO_EXTICR1` image to write
 * @returns Void.
 * @note Caller owns read-modify-write staging and field placement.
 */
__STATIC_FORCEINLINE void LL_GPIO_IRQ_WriteEXTICR1(const reg regImage)
{
	LL_GPIO_IRQ_WriteRegister(LL_GPIO_IRQ_AFIO_REG(EXTICR1), regImage);
}

/**
 * @brief Reads the AFIO `EXTICR2` register image
 * @returns Full `AFIO_EXTICR2` image.
 * @note EXTICR field extraction and interpretation belong above LL.
 */
__STATIC_FORCEINLINE reg LL_GPIO_IRQ_ReadEXTICR2(void)
{
	return LL_GPIO_IRQ_ReadRegister(LL_GPIO_IRQ_AFIO_REG(EXTICR2));
}

/**
 * @brief Writes the AFIO `EXTICR2` register image
 * @param[in]	regImage	Full `AFIO_EXTICR2` image to write
 * @returns Void.
 * @note Caller owns read-modify-write staging and field placement.
 */
__STATIC_FORCEINLINE void LL_GPIO_IRQ_WriteEXTICR2(const reg regImage)
{
	LL_GPIO_IRQ_WriteRegister(LL_GPIO_IRQ_AFIO_REG(EXTICR2), regImage);
}

/**
 * @brief Reads the AFIO `EXTICR3` register image
 * @returns Full `AFIO_EXTICR3` image.
 * @note EXTICR field extraction and interpretation belong above LL.
 */
__STATIC_FORCEINLINE reg LL_GPIO_IRQ_ReadEXTICR3(void)
{
	return LL_GPIO_IRQ_ReadRegister(LL_GPIO_IRQ_AFIO_REG(EXTICR3));
}

/**
 * @brief Writes the AFIO `EXTICR3` register image
 * @param[in]	regImage	Full `AFIO_EXTICR3` image to write
 * @returns Void.
 * @note Caller owns read-modify-write staging and field placement.
 */
__STATIC_FORCEINLINE void LL_GPIO_IRQ_WriteEXTICR3(const reg regImage)
{
	LL_GPIO_IRQ_WriteRegister(LL_GPIO_IRQ_AFIO_REG(EXTICR3), regImage);
}

/**
 * @brief Reads the AFIO `EXTICR4` register image
 * @returns Full `AFIO_EXTICR4` image.
 * @note EXTICR field extraction and interpretation belong above LL.
 */
__STATIC_FORCEINLINE reg LL_GPIO_IRQ_ReadEXTICR4(void)
{
	return LL_GPIO_IRQ_ReadRegister(LL_GPIO_IRQ_AFIO_REG(EXTICR4));
}

/**
 * @brief Writes the AFIO `EXTICR4` register image
 * @param[in]	regImage	Full `AFIO_EXTICR4` image to write
 * @returns Void.
 * @note Caller owns read-modify-write staging and field placement.
 */
__STATIC_FORCEINLINE void LL_GPIO_IRQ_WriteEXTICR4(const reg regImage)
{
	LL_GPIO_IRQ_WriteRegister(LL_GPIO_IRQ_AFIO_REG(EXTICR4), regImage);
}

/** @} */ // GPIO_IRQ_02_LL_01_RegisterOps

// ==================================================================================================== //
//                                       GPIO IRQ LL Clock APIs                                        //
// ==================================================================================================== //

/**
 * @brief GPIO IRQ LL Clock APIs
 * @defgroup GPIO_IRQ_02_LL_02_Clock GPIO IRQ LL Clock APIs
 * @ingroup GPIO_IRQ_02_LL
 * @details
 * These APIs forward the AFIO APB2 clock gate request to RCC LL. Driver policy
 * decides when the AFIO clock is required.
 * @{
 */

/**
 * @brief Enables the AFIO APB2 clock gate
 * @returns Status forwarded from @ref `LL_RCC_EnableAPB2Clock`
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AFIO APB2 clock gate was enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `RCC_APB2ENR_AFIOEN` was rejected by RCC LL
 */
__STATIC_FORCEINLINE driver_status_t LL_GPIO_IRQ_EnableAFIOClock(void)
{
	return LL_RCC_EnableAPB2Clock(RCC_APB2ENR_AFIOEN);
}

/**
 * @brief Disables the AFIO APB2 clock gate
 * @returns Status forwarded from @ref `LL_RCC_DisableAPB2Clock`
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AFIO APB2 clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `RCC_APB2ENR_AFIOEN` was rejected by RCC LL
 */
__STATIC_FORCEINLINE driver_status_t LL_GPIO_IRQ_DisableAFIOClock(void)
{
	return LL_RCC_DisableAPB2Clock(RCC_APB2ENR_AFIOEN);
}

/** @} */ // GPIO_IRQ_02_LL_02_Clock

/** @} */ // GPIO_IRQ_02_LL

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LL_GPIO_IRQ_H_ */
