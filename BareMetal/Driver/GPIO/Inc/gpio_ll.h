/**
 * @file	gpio_ll.h
 * @author	Shrey Shah
 * @brief	GPIO Low-Level Control Interface
 * @version	v2.1
 * @date	29-03-2026
 *
 * @details
 * This header defines the GPIO low-level module that sits directly above the
 * register-layer definitions from @ref `stm32f1xx_gpio.h`.
 *
 * LL authority is intentionally narrow. It owns dumb GPIO register access:
 * - static inline read/write accessors for GPIO register images
 * - the minimal register-address macro needed to select a C struct member
 * - enabling or disabling GPIO-related APB2 clock gates through RCC LL
 *
 * This module does not own:
 * - GPIO selector vocabulary definitions
 * - public selector to raw field translation
 * - CRL/CRH bitfield placement, packing, or decoding
 * - pin-mask to pin-index translation
 * - public driver policy validation
 * - staged batching policy
 * - board-specific behavior
 *
 * Practical Authority Rule:
 * - Layer 0 (`stm32f1xx_gpio.h`) defines raw register symbols and register map.
 * - LL exposes named full-register accessors and thin clock forwarding only.
 * - Codec APIs own selector translation and CRL/CRH/ODR image mutation.
 * - Driver APIs (`gpio.h` / `gpio.c`) own public validation, sequencing, and
 *   user-facing status.
 *
 * @note Functions in this file do not validate @ref `GPIO_TypeDef` pointers, do
 * not check clock state, and do not preserve unrelated register bits unless the
 * caller supplies a pre-staged full register image.
 */

// Header Guards
#ifndef LL_GPIO_H_
#define LL_GPIO_H_

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
 * @addtogroup GPIO_02_LL
 * @{
 */

// ==================================================================================================== //
//										GPIO LL Register Access APIs									//
// ==================================================================================================== //

/**
 * @brief	GPIO LL Register Access APIs
 * @defgroup GPIO_02_LL_01_RegisterOps GPIO LL Register Access APIs
 * @ingroup	GPIO_02_LL
 * @details
 * These functions are intentionally dumb full-register image readers and
 * writers. They do not know pin masks, pin indices, CRL/CRH field layout, or
 * public GPIO selectors.
 *
 * Practical Rule:
 * - Always access GPIO registers through the `.REG` member.
 * - Do not use the `.BIT` view in the LL layer.
 * - Use named static inline accessors in driver code.
 * - Read-modify-write policy belongs to the caller, not to this LL layer.
 *
 * @warning These accessors perform no NULL, port-validity, clock, reserved-bit,
 * or write-permission checks.
 * @{
 */

/**
 * @brief Returns pointer to GPIO register `.REG` image
 * @def LL_GPIO_REG
 * @param[in]	_GPIOX	Target GPIO peripheral instance expression
 * @param[in]	_REG	Register member token inside @ref `GPIO_TypeDef`
 * @returns Pointer to the selected GPIO register `.REG` image.
 * @note Thin GPIO LL alias over @ref `REGOPS_REG`.
 */
#define LL_GPIO_REG(_GPIOX, _REG)				REGOPS_REG((_GPIOX), _REG)

/**
 * @brief Reads one GPIO register image by register pointer
 * @param[in]	pRegister	Pointer to a GPIO `.REG` member
 * @returns Full 32-bit register image currently observed at @p pRegister.
 * @note Caller must pass a valid GPIO register pointer.
 */
__STATIC_FORCEINLINE reg LL_GPIO_ReadRegister(const _IO* const pRegister)
{
	reg regImage = 0x00000000UL;
	(void) RegOps_Read(pRegister, &regImage);
	return regImage;
}

/**
 * @brief Writes one GPIO register image by register pointer
 * @param[in]	pRegister	Pointer to a writable GPIO `.REG` member
 * @param[in]	regImage	Full 32-bit register image to write
 * @returns Void.
 * @note Caller must pass a valid writable GPIO register pointer and a complete
 * register image appropriate for that register.
 */
__STATIC_FORCEINLINE void LL_GPIO_WriteRegister(_IO* const pRegister, const reg regImage)
{
	(void) RegOps_Write(pRegister, regImage);
}

/**
 * @brief Reads the GPIO `CRL` register image
 * @param[in]	GPIOx	GPIO peripheral instance
 * @returns Full `GPIOx_CRL` image.
 * @note `CRL` controls the MODE/CNF fields for pins 0 through 7. Field
 * extraction and interpretation are codec responsibilities.
 */
__STATIC_FORCEINLINE reg LL_GPIO_ReadCRL(GPIO_TypeDef* const GPIOx)
{
	return LL_GPIO_ReadRegister(LL_GPIO_REG(GPIOx, CRL));
}

/**
 * @brief Writes the GPIO `CRL` register image
 * @param[in]	GPIOx		GPIO peripheral instance
 * @param[in]	regImage	Full `GPIOx_CRL` image to write
 * @returns Void.
 * @note Caller owns read-modify-write staging and MODE/CNF field placement.
 */
__STATIC_FORCEINLINE void LL_GPIO_WriteCRL(GPIO_TypeDef* const GPIOx, const reg regImage)
{
	LL_GPIO_WriteRegister(LL_GPIO_REG(GPIOx, CRL), regImage);
}

/**
 * @brief Reads the GPIO `CRH` register image
 * @param[in]	GPIOx	GPIO peripheral instance
 * @returns Full `GPIOx_CRH` image.
 * @note `CRH` controls the MODE/CNF fields for pins 8 through 15. Field
 * extraction and interpretation are codec responsibilities.
 */
__STATIC_FORCEINLINE reg LL_GPIO_ReadCRH(GPIO_TypeDef* const GPIOx)
{
	return LL_GPIO_ReadRegister(LL_GPIO_REG(GPIOx, CRH));
}

/**
 * @brief Writes the GPIO `CRH` register image
 * @param[in]	GPIOx		GPIO peripheral instance
 * @param[in]	regImage	Full `GPIOx_CRH` image to write
 * @returns Void.
 * @note Caller owns read-modify-write staging and MODE/CNF field placement.
 */
__STATIC_FORCEINLINE void LL_GPIO_WriteCRH(GPIO_TypeDef* const GPIOx, const reg regImage)
{
	LL_GPIO_WriteRegister(LL_GPIO_REG(GPIOx, CRH), regImage);
}

/**
 * @brief Reads the GPIO `IDR` register image
 * @param[in]	GPIOx	GPIO peripheral instance
 * @returns Full sampled `GPIOx_IDR` image.
 * @note Pin masking and public logic-level conversion belong above LL.
 */
__STATIC_FORCEINLINE reg LL_GPIO_ReadIDR(GPIO_TypeDef* const GPIOx)
{
	return LL_GPIO_ReadRegister(LL_GPIO_REG(GPIOx, IDR));
}

/**
 * @brief Reads the GPIO `ODR` register image
 * @param[in]	GPIOx	GPIO peripheral instance
 * @returns Full latched `GPIOx_ODR` image.
 * @note Use this accessor only when the current output latch image is required,
 * such as pull-up/pull-down extraction or toggle read-modify-write. Simple
 * set/reset operations should use `BSRR`/`BRR`.
 */
__STATIC_FORCEINLINE reg LL_GPIO_ReadODR(GPIO_TypeDef* const GPIOx)
{
	return LL_GPIO_ReadRegister(LL_GPIO_REG(GPIOx, ODR));
}

/**
 * @brief Writes the GPIO `ODR` register image
 * @param[in]	GPIOx		GPIO peripheral instance
 * @param[in]	regImage	Full `GPIOx_ODR` image to write
 * @returns Void.
 * @note Caller must preserve any bits that should not change. Prefer `BSRR`
 * and `BRR` for set/reset operations; reserve direct ODR writes for explicit
 * full-image updates or toggle-style read-modify-write flows.
 */
__STATIC_FORCEINLINE void LL_GPIO_WriteODR(GPIO_TypeDef* const GPIOx, const reg regImage)
{
	LL_GPIO_WriteRegister(LL_GPIO_REG(GPIOx, ODR), regImage);
}

/**
 * @brief Writes the GPIO `BSRR` register image
 * @param[in]	GPIOx		GPIO peripheral instance
 * @param[in]	regImage	Raw `GPIOx_BSRR` image to write
 * @returns Void.
 * @note `BSRR` is a hardware action register. Lower 16 bits set pins and upper
 * 16 bits reset pins. Public driver policy decides whether to use this path or
 * a staged `ODR` image.
 */
__STATIC_FORCEINLINE void LL_GPIO_WriteBSRR(GPIO_TypeDef* const GPIOx, const reg regImage)
{
	LL_GPIO_WriteRegister(LL_GPIO_REG(GPIOx, BSRR), regImage);
}

/**
 * @brief Writes the GPIO `BRR` register image
 * @param[in]	GPIOx		GPIO peripheral instance
 * @param[in]	regImage	Raw `GPIOx_BRR` image to write
 * @returns Void.
 * @note `BRR` is a hardware action register. Bits 0 through 15 reset the
 * matching output pins.
 */
__STATIC_FORCEINLINE void LL_GPIO_WriteBRR(GPIO_TypeDef* const GPIOx, const reg regImage)
{
	LL_GPIO_WriteRegister(LL_GPIO_REG(GPIOx, BRR), regImage);
}

/**
 * @brief Reads the GPIO `LCKR` register image
 * @param[in]	GPIOx	GPIO peripheral instance
 * @returns Full `GPIOx_LCKR` image.
 * @note Lock-sequence policy belongs above LL.
 */
__STATIC_FORCEINLINE reg LL_GPIO_ReadLCKR(GPIO_TypeDef* const GPIOx)
{
	return LL_GPIO_ReadRegister(LL_GPIO_REG(GPIOx, LCKR));
}

/**
 * @brief Writes the GPIO `LCKR` register image
 * @param[in]	GPIOx		GPIO peripheral instance
 * @param[in]	regImage	Full `GPIOx_LCKR` image to write
 * @returns Void.
 * @note Caller owns the STM32F1 lock-key write sequence.
 */
__STATIC_FORCEINLINE void LL_GPIO_WriteLCKR(GPIO_TypeDef* const GPIOx, const reg regImage)
{
	LL_GPIO_WriteRegister(LL_GPIO_REG(GPIOx, LCKR), regImage);
}

/** @} */ // GPIO_02_LL_01_RegisterOps

// ==================================================================================================== //
//										  GPIO LL Clock APIs											//
// ==================================================================================================== //

/**
 * @brief	GPIO LL Clock APIs
 * @defgroup GPIO_02_LL_02_Clock GPIO LL Clock APIs
 * @ingroup	GPIO_02_LL
 * @details
 * These APIs resolve GPIO-related APB2 clock gates and forward the raw
 * `RCC_APB2ENR` bit masks to RCC LL.
 *
 * Practical Rule:
 * - GPIO port clock APIs accept a @ref `GPIO_TypeDef` pointer and resolve it to
 *   the matching `RCC_APB2ENR_IOPxEN` bit.
 * - AFIO clock APIs use the raw `RCC_APB2ENR_AFIOEN` bit directly.
 * - This section only performs the requested clock-gate action. Driver policy
 *   decides when GPIO or AFIO clocks are required.
 * @{
 */

/**
 * @brief Resolves a GPIO peripheral instance to the matching APB2 clock-gate mask
 * @details
 * Supported @p GPIOx inputs:
 * - @ref `GPIOA`
 * - @ref `GPIOB`
 * - @ref `GPIOC`
 * - @ref `GPIOD`
 * - @ref `GPIOE`
 * - @ref `GPIOF`
 * - @ref `GPIOG`
 *
 * @param[in]	GPIOx	GPIO peripheral instance
 * @returns GPIO port APB2 clock-gate mask resolved from @p GPIOx
 * @retval - @ref `RCC_APB2ENR_IOPAEN`: GPIOA APB2 clock-gate mask
 * @retval - @ref `RCC_APB2ENR_IOPBEN`: GPIOB APB2 clock-gate mask
 * @retval - @ref `RCC_APB2ENR_IOPCEN`: GPIOC APB2 clock-gate mask
 * @retval - @ref `RCC_APB2ENR_IOPDEN`: GPIOD APB2 clock-gate mask
 * @retval - @ref `RCC_APB2ENR_IOPEEN`: GPIOE APB2 clock-gate mask
 * @retval - @ref `RCC_APB2ENR_IOPFEN`: GPIOF APB2 clock-gate mask
 * @retval - @ref `RCC_APB2ENR_IOPGEN`: GPIOG APB2 clock-gate mask
 * @retval - `0x00000000UL`: @p `GPIOx` did not map to a supported GPIO port
 */
__STATIC_FORCEINLINE reg LL_GPIO_GetPortClockMask(const GPIO_TypeDef* const GPIOx)
{
	reg clockGateMask = 0x00000000UL;

	/* Map GPIO base address to its APB2 clock-enable bit. */
	switch ((reg) GPIOx)
	{
		case GPIOA_BASE_ADDRESS:
		{
			clockGateMask = RCC_APB2ENR_IOPAEN;
			break;
		}
		case GPIOB_BASE_ADDRESS:
		{
			clockGateMask = RCC_APB2ENR_IOPBEN;
			break;
		}
		case GPIOC_BASE_ADDRESS:
		{
			clockGateMask = RCC_APB2ENR_IOPCEN;
			break;
		}
		case GPIOD_BASE_ADDRESS:
		{
			clockGateMask = RCC_APB2ENR_IOPDEN;
			break;
		}
		case GPIOE_BASE_ADDRESS:
		{
			clockGateMask = RCC_APB2ENR_IOPEEN;
			break;
		}
		case GPIOF_BASE_ADDRESS:
		{
			clockGateMask = RCC_APB2ENR_IOPFEN;
			break;
		}
		case GPIOG_BASE_ADDRESS:
		{
			clockGateMask = RCC_APB2ENR_IOPGEN;
			break;
		}
		default:
		{
			clockGateMask = 0x00000000UL;
			break;
		}
	}

	return clockGateMask;
}

/**
 * @brief Enables the APB2 clock gate for one GPIO port
 * @param[in]	GPIOx	GPIO peripheral instance
 * @returns Status forwarded from @ref `LL_RCC_EnableAPB2Clock`
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: GPIO port APB2 clock gate was enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx did not resolve to a valid APB2 clock-gate mask
 */
__STATIC_FORCEINLINE driver_status_t LL_GPIO_EnableClock(const GPIO_TypeDef* const GPIOx)
{
	const reg clockMask = LL_GPIO_GetPortClockMask(GPIOx);
	return LL_RCC_EnableAPB2Clock(clockMask);
}

/**
 * @brief Disables the APB2 clock gate for one GPIO port
 * @param[in]	GPIOx	GPIO peripheral instance
 * @returns Status forwarded from @ref `LL_RCC_DisableAPB2Clock`
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: GPIO port APB2 clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx did not resolve to a valid APB2 clock-gate mask
 */
__STATIC_FORCEINLINE driver_status_t LL_GPIO_DisableClock(const GPIO_TypeDef* const GPIOx)
{
	const reg clockMask = LL_GPIO_GetPortClockMask(GPIOx);
	return LL_RCC_DisableAPB2Clock(clockMask);
}

/**
 * @brief Enables the AFIO APB2 clock gate
 * @returns Status forwarded from @ref `LL_RCC_EnableAPB2Clock`
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AFIO APB2 clock gate was enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `RCC_APB2ENR_AFIOEN` was rejected by RCC LL
 */
__STATIC_FORCEINLINE driver_status_t LL_GPIO_EnableAFIOClock(void)
{
	return LL_RCC_EnableAPB2Clock(RCC_APB2ENR_AFIOEN);
}

/**
 * @brief Disables the AFIO APB2 clock gate
 * @returns Status forwarded from @ref `LL_RCC_DisableAPB2Clock`
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AFIO APB2 clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `RCC_APB2ENR_AFIOEN` was rejected by RCC LL
 */
__STATIC_FORCEINLINE driver_status_t LL_GPIO_DisableAFIOClock(void)
{
	return LL_RCC_DisableAPB2Clock(RCC_APB2ENR_AFIOEN);
}

/** @} */ // GPIO_02_LL_02_Clock

/** @} */ // GPIO_02_LL

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LL_GPIO_H_ */
