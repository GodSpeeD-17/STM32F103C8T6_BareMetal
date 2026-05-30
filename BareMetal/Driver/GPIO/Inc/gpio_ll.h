/**
 * @file	gpio_ll.h
 * @author	Shrey Shah
 * @brief	GPIO Low-Level Control Interface
 * @version	v2.1
 * @date	29-03-2026
 *
 * @details
 * This header defines the GPIO low-level module that sits directly above the
 * register-layer definitions from @ref stm32f1xx_gpio.h.
 *
 * LL authority owns direct hardware-facing actions and STM32F1 GPIO register
 * layout primitives:
 * - GPIO register access macros built on the generic register utilities
 * - direct raw pin-mask operations on IDR/ODR/BSRR/BRR
 * - enabling or disabling GPIO-related APB2 clock gates through RCC LL
 * - raw CRL/CRH pin-field layout, packing, and placement helpers
 *
 * This module does not own:
 * - GPIO selector vocabulary definitions
 * - public selector to raw field translation
 * - public driver policy validation
 * - staged batching policy
 * - board-specific behavior
 *
 * Practical Authority Rule:
 * - Layer 0 (`stm32f1xx_gpio.h`) defines raw register symbols and register map.
 * - Raw LL APIs in this file assume valid raw inputs.
 * - Codec APIs own selector translation and staged image mutation.
 * - Driver APIs (`gpio.h` / `gpio.c`) own public validation, sequencing, and
 *   user-facing status.
 */

#ifndef GPIO_LL_H_
#define GPIO_LL_H_

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//											   Includes													//
// ==================================================================================================== //
#include "stm32f1xx.h"
#include "gpio_defines.h"
#include "rcc_ll.h"

/**
 * @addtogroup GPIO_02_LL
 * @{
 */

// ==================================================================================================== //
//									 GPIO LL Register Operation Macros									//
// ==================================================================================================== //

/**
 * @brief	GPIO LL Register Operation Macros
 * @defgroup GPIO_02_LL_01_RegisterOps GPIO LL Register Operation Macros
 * @ingroup	GPIO_02_LL
 * @details
 * These macros build a thin GPIO-specific convenience layer on top of the
 * generic @ref REGOPS_READ, @ref REGOPS_WRITE, @ref REGOPS_SET,
 * @ref REGOPS_CLEAR, @ref REGOPS_TOGGLE, and @ref REGOPS_MODIFY utilities.
 *
 * Practical Rule:
 * - Always access GPIO registers through the `.REG` member.
 * - Do not use the `.BIT` view in the LL layer.
 * - Do not introduce driver-level selector values here.
 * @{
 */

/**
 * @brief Returns pointer to GPIO register `.REG` image
 * @def GPIO_LL_REG
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @returns Pointer to the selected GPIO register `.REG` image
 */
#define GPIO_LL_REG(_GPIOX, _REG)							(&((_GPIOX)->_REG.REG))

/**
 * @brief Reads full GPIO register image
 * @def GPIO_LL_READ_REG
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @param[in] _VAR Destination variable that receives the register image
 */
#define GPIO_LL_READ_REG(_GPIOX, _REG, _VAR)				REGOPS_READ(GPIO_LL_REG((_GPIOX), _REG), (_VAR))

/**
 * @brief Writes full GPIO register image
 * @def GPIO_LL_WRITE_REG
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @param[in] _VAL Register image to write
 */
#define GPIO_LL_WRITE_REG(_GPIOX, _REG, _VAL)				REGOPS_WRITE(GPIO_LL_REG((_GPIOX), _REG), (_VAL))

/**
 * @brief Sets GPIO register bits
 * @def GPIO_LL_SET_BITS
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @param[in] _MASK Bit mask to set
 */
#define GPIO_LL_SET_BITS(_GPIOX, _REG, _MASK)				REGOPS_SET(GPIO_LL_REG((_GPIOX), _REG), (_MASK))

/**
 * @brief Clears GPIO register bits
 * @def GPIO_LL_CLEAR_BITS
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @param[in] _MASK Bit mask to clear
 */
#define GPIO_LL_CLEAR_BITS(_GPIOX, _REG, _MASK)				REGOPS_CLEAR(GPIO_LL_REG((_GPIOX), _REG), (_MASK))

/**
 * @brief Toggles GPIO register bits
 * @def GPIO_LL_TOGGLE_BITS
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @param[in] _MASK Bit mask to toggle
 */
#define GPIO_LL_TOGGLE_BITS(_GPIOX, _REG, _MASK)			REGOPS_TOGGLE(GPIO_LL_REG((_GPIOX), _REG), (_MASK))

/**
 * @brief Modifies GPIO register masked field
 * @def GPIO_LL_MODIFY_REG
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @param[in] _MASK Field mask to modify
 * @param[in] _VAL Masked field value to write
 *
 * @note `_VAL` must already be aligned to the target field position.
 */
#define GPIO_LL_MODIFY_REG(_GPIOX, _REG, _MASK, _VAL)		REGOPS_MODIFY(GPIO_LL_REG((_GPIOX), _REG), (_MASK), (_VAL))

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
 * - GPIO port clock APIs accept a @ref GPIO_TypeDef pointer and resolve it to
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
__STATIC_FORCEINLINE uint32_t GPIO_LL_GetPortClockMask(const GPIO_TypeDef* const GPIOx)
{
	uint32_t clockGateMask = 0x00000000UL;

	//! Decide the clock mask based on GPIO Address
	switch ((uint32_t) GPIOx)
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
 * @returns Status forwarded from @ref RCC_LL_EnableAPB2Clock
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: GPIO port APB2 clock gate was enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx did not resolve to a valid APB2 clock-gate mask
 */
__STATIC_FORCEINLINE driver_status_t GPIO_LL_EnableClock(const GPIO_TypeDef* const GPIOx)
{
	const uint32_t clockMask = GPIO_LL_GetPortClockMask(GPIOx);
	return RCC_LL_EnableAPB2Clock(clockMask);
}

/**
 * @brief Disables the APB2 clock gate for one GPIO port
 * @param[in]	GPIOx	GPIO peripheral instance
 * @returns Status forwarded from @ref RCC_LL_DisableAPB2Clock
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: GPIO port APB2 clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx did not resolve to a valid APB2 clock-gate mask
 */
__STATIC_FORCEINLINE driver_status_t GPIO_LL_DisableClock(const GPIO_TypeDef* const GPIOx)
{
	const uint32_t clockMask = GPIO_LL_GetPortClockMask(GPIOx);
	return RCC_LL_DisableAPB2Clock(clockMask);
}

/**
 * @brief Enables the AFIO APB2 clock gate
 * @returns Status forwarded from @ref RCC_LL_EnableAPB2Clock
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AFIO APB2 clock gate was enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `RCC_APB2ENR_AFIOEN` was rejected by RCC LL
 */
__STATIC_FORCEINLINE driver_status_t GPIO_LL_EnableAFIOClock(void)
{
	return RCC_LL_EnableAPB2Clock(RCC_APB2ENR_AFIOEN);
}

/**
 * @brief Disables the AFIO APB2 clock gate
 * @returns Status forwarded from @ref RCC_LL_DisableAPB2Clock
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AFIO APB2 clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `RCC_APB2ENR_AFIOEN` was rejected by RCC LL
 */
__STATIC_FORCEINLINE driver_status_t GPIO_LL_DisableAFIOClock(void)
{
	return RCC_LL_DisableAPB2Clock(RCC_APB2ENR_AFIOEN);
}

/** @} */ // GPIO_02_LL_02_Clock

// ==================================================================================================== //
//										GPIO LL Mode and CNF APIs										//
// ==================================================================================================== //

/**
 * @brief	GPIO LL Mode and CNF APIs
 * @defgroup GPIO_02_LL_03_ModeCNF GPIO LL Mode and CNF APIs
 * @ingroup	GPIO_02_LL
 * @details
 * These APIs operate on raw STM32F1 CRL/CRH MODE and CNF register images.
 * They own the field positions and raw field packing rules, but they do not
 * translate public driver selectors.
 *
 * Practical Rule:
 * - Caller provides raw MODE/CNF field values and caller-owned register images.
 * - Hardware read APIs return the right-aligned raw MODE/CNF field for one pin.
 * - Pin inputs are expected to be single-pin masks from @ref `GPIO_PIN_0`
 *   through @ref `GPIO_PIN_15`.
 * - These APIs do not validate public selector compatibility.
 * @{
 */

/** @brief Width of one CRL/CRH pin MODE/CNF field @def GPIO_LL_CRX_PIN_MODE_CNF_FIELD_WIDTH */
#define GPIO_LL_CRX_PIN_MODE_CNF_FIELD_WIDTH		((uint32_t) 0x04UL)
/** @brief Raw right-aligned four-bit CRL/CRH pin MODE/CNF field mask @def GPIO_LL_CRX_PIN_MODE_CNF_FIELD_MASK */
#define GPIO_LL_CRX_PIN_MODE_CNF_FIELD_MASK			((uint32_t) 0x0FUL)
/** @brief Local pin-index mask inside one CRL/CRH register @def GPIO_LL_CRX_LOCAL_PIN_INDEX_MASK */
#define GPIO_LL_CRX_LOCAL_PIN_INDEX_MASK			((uint8_t) 0x07U)
/** @brief MODE bit offset inside one right-aligned MODE/CNF field @def GPIO_LL_CRX_MODE_BITS_SHIFT */
#define GPIO_LL_CRX_MODE_BITS_SHIFT					((uint32_t) 0x00UL)
/** @brief Raw right-aligned MODE field mask @def GPIO_LL_CRX_MODE_BITS_MASK */
#define GPIO_LL_CRX_MODE_BITS_MASK					((uint32_t) 0x03UL)
/** @brief CNF bit offset inside one right-aligned MODE/CNF field @def GPIO_LL_CRX_CNF_BITS_SHIFT */
#define GPIO_LL_CRX_CNF_BITS_SHIFT					((uint32_t) 0x02UL)
/** @brief Raw right-aligned CNF field mask @def GPIO_LL_CRX_CNF_BITS_MASK */
#define GPIO_LL_CRX_CNF_BITS_MASK					((uint32_t) 0x03UL)

/**
 * @brief Bitmask selecting every GPIO pin controlled through CRL
 * @def LL_GPIO_PIN_MASK_CRL_RANGE
 */
#define LL_GPIO_PIN_MASK_CRL_RANGE					\
(													\
	(gpio_pin_t)									\
	(												\
		GPIO_PIN_0 | GPIO_PIN_1 |					\
		GPIO_PIN_2 | GPIO_PIN_3 |					\
		GPIO_PIN_4 | GPIO_PIN_5 |					\
		GPIO_PIN_6 | GPIO_PIN_7						\
	)												\
)

/**
 * @brief Bitmask selecting every GPIO pin controlled through CRH
 * @def LL_GPIO_PIN_MASK_CRH_RANGE
 */
#define LL_GPIO_PIN_MASK_CRH_RANGE					\
(													\
	(gpio_pin_t)									\
	(												\
		GPIO_PIN_8  | GPIO_PIN_9  |					\
		GPIO_PIN_10 | GPIO_PIN_11 |					\
		GPIO_PIN_12 | GPIO_PIN_13 |					\
		GPIO_PIN_14 | GPIO_PIN_15					\
	)												\
)

/**
 * @brief Checks if any selected pin is controlled through CRL
 * @def LL_GPIO_PIN_MASK_REQUIRES_CRL
 */
#define LL_GPIO_PIN_MASK_REQUIRES_CRL(pinMask)		\
	(((((gpio_pin_t) (pinMask)) & LL_GPIO_PIN_MASK_CRL_RANGE) != GPIO_PIN_NONE))

/**
 * @brief Checks if any selected pin is controlled through CRH
 * @def LL_GPIO_PIN_MASK_REQUIRES_CRH
 */
#define LL_GPIO_PIN_MASK_REQUIRES_CRH(pinMask)		\
	(((((gpio_pin_t) (pinMask)) & LL_GPIO_PIN_MASK_CRH_RANGE) != GPIO_PIN_NONE))

/* Temporary compatibility aliases for callers not yet migrated to LL_GPIO_* names. */
#define GPIO_PIN_MASK_CRL_RANGE						LL_GPIO_PIN_MASK_CRL_RANGE
#define GPIO_PIN_MASK_CRH_RANGE						LL_GPIO_PIN_MASK_CRH_RANGE
#define GPIO_PIN_MASK_REQUIRES_CRL(pinMask)			LL_GPIO_PIN_MASK_REQUIRES_CRL(pinMask)
#define GPIO_PIN_MASK_REQUIRES_CRH(pinMask)			LL_GPIO_PIN_MASK_REQUIRES_CRH(pinMask)


/**
 * @brief Gets one pin's raw MODE/CNF field from a CRL/CRH register image
 * @param[in]	crxRegImage	CRL/CRH register image
 * @param[in]	pinMask		GPIO single-pin mask
 * @returns Right-aligned raw four-bit MODE/CNF field
 * @retval - `0x00U..0x0FU`: Raw `CNF[1:0] | MODE[1:0]` field value
 * @note LL callers are expected to pass a valid single-pin mask.
 */
__STATIC_FORCEINLINE gpio_pin_config_bits_t GPIO_LL_GetPinModeCNFFieldFromCRx
(
	const uint32_t crxRegImage,
	const gpio_pin_t pinMask
)
{
	const uint8_t localPinIndex = (uint8_t) (GPIO_PinMaskToIndex(pinMask) & GPIO_LL_CRX_LOCAL_PIN_INDEX_MASK);
	const uint32_t fieldShift = ((uint32_t) localPinIndex * GPIO_LL_CRX_PIN_MODE_CNF_FIELD_WIDTH);

	return (gpio_pin_config_bits_t)
	(
		(crxRegImage >> fieldShift) & GPIO_LL_CRX_PIN_MODE_CNF_FIELD_MASK
	);
}

/**
 * @brief Reads one raw pin MODE/CNF field from `CRL` or `CRH`
 * @param[in]	GPIOx		GPIO peripheral instance
 * @param[in]	pinMask		GPIO single-pin mask
 * @returns Right-aligned raw four-bit MODE/CNF field read from `CRL` or `CRH`
 * @retval - `0x00U..0x0FU`: Raw `CNF[1:0] | MODE[1:0]` field value; `0x00U` is also used for invalid input
 */
__STATIC_FORCEINLINE gpio_pin_config_bits_t GPIO_LL_ReadPinModeCNFField
(
	const GPIO_TypeDef* const	GPIOx,
	const gpio_pin_t			pinMask
)
{
	uint32_t crxRegImage = 0x00000000UL;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0U) ||
		(GPIO_PIN_MASK_IS_VALID(pinMask) == 0U) ||
		(GPIO_PIN_MASK_HAS_AT_MOST_ONE_BIT(pinMask) == 0U))
	{
		return (gpio_pin_config_bits_t) 0x00U;
	}

	if (GPIO_PIN_MASK_REQUIRES_CRH(pinMask) != 0U)
	{
		GPIO_LL_READ_REG(GPIOx, CRH, crxRegImage);
	}
	else
	{
		GPIO_LL_READ_REG(GPIOx, CRL, crxRegImage);
	}

	return GPIO_LL_GetPinModeCNFFieldFromCRx(crxRegImage, pinMask);
}

/**
 * @brief Sets one pin's raw MODE/CNF field inside a CRL/CRH register image
 * @param[in]	crxRegImage	CRL/CRH register image before replacement
 * @param[in]	pinMask		GPIO single-pin mask
 * @param[in]	crxField	Right-aligned raw four-bit `CNF[1:0] | MODE[1:0]` field value
 * @returns Updated CRL/CRH register image
 * @retval - Any `uint32_t`: CRL/CRH image with the selected pin field replaced
 * @note LL callers are expected to pass a valid single-pin mask.
 */
__STATIC_FORCEINLINE uint32_t GPIO_LL_SetPinModeCNFFieldInCRx
(
	const uint32_t					crxRegImage,
	const gpio_pin_t				pinMask,
	const gpio_pin_config_bits_t	crxField
)
{
	uint32_t updatedRegImage = crxRegImage;
	const uint8_t localPinIndex = (uint8_t) (GPIO_PinMaskToIndex(pinMask) & GPIO_LL_CRX_LOCAL_PIN_INDEX_MASK);
	const uint32_t fieldShift = ((uint32_t) localPinIndex * GPIO_LL_CRX_PIN_MODE_CNF_FIELD_WIDTH);
	const uint32_t fieldMask = BIT_VALUE(GPIO_LL_CRX_PIN_MODE_CNF_FIELD_MASK, fieldShift);

	updatedRegImage &= ~fieldMask;
	updatedRegImage |= BIT_VALUE((((uint32_t) crxField) & GPIO_LL_CRX_PIN_MODE_CNF_FIELD_MASK), fieldShift);

	return updatedRegImage;
}

/**
 * @brief Sets one pin's raw MODE bits inside a CRL/CRH register image
 * @param[in]	crxRegImage	CRL/CRH register image before replacement
 * @param[in]	pinMask		GPIO single-pin mask
 * @param[in]	modeBits	Raw STM32F1 `MODE[1:0]` field value
 * @returns Updated CRL/CRH register image
 * @retval - Any `uint32_t`: CRL/CRH image with the selected MODE bits replaced
 * @note LL callers are expected to pass a valid single-pin mask.
 */
__STATIC_FORCEINLINE uint32_t GPIO_LL_SetPinModeBitsInCRx
(
	const uint32_t		crxRegImage,
	const gpio_pin_t	pinMask,
	const gpio_mode_t	modeBits
)
{
	uint32_t updatedRegImage = crxRegImage;
	const uint8_t localPinIndex = (uint8_t) (GPIO_PinMaskToIndex(pinMask) & GPIO_LL_CRX_LOCAL_PIN_INDEX_MASK);
	const uint32_t fieldShift = ((uint32_t) localPinIndex * GPIO_LL_CRX_PIN_MODE_CNF_FIELD_WIDTH);
	const uint32_t modeShift = (fieldShift + GPIO_LL_CRX_MODE_BITS_SHIFT);
	const uint32_t modeMask = BIT_VALUE(GPIO_LL_CRX_MODE_BITS_MASK, modeShift);

	updatedRegImage &= ~modeMask;
	updatedRegImage |= BIT_VALUE((((uint32_t) modeBits) & GPIO_LL_CRX_MODE_BITS_MASK), modeShift);

	return updatedRegImage;
}

/**
 * @brief Sets one pin's raw CNF bits inside a CRL/CRH register image
 * @param[in]	crxRegImage	CRL/CRH register image before replacement
 * @param[in]	pinMask		GPIO single-pin mask
 * @param[in]	cnfBits		Raw STM32F1 `CNF[1:0]` field value
 * @returns Updated CRL/CRH register image
 * @retval - Any `uint32_t`: CRL/CRH image with the selected CNF bits replaced
 * @note LL callers are expected to pass a valid single-pin mask.
 */
__STATIC_FORCEINLINE uint32_t GPIO_LL_SetPinCNFBitsInCRx
(
	const uint32_t	crxRegImage,
	const gpio_pin_t	pinMask,
	const gpio_cnf_t	cnfBits
)
{
	uint32_t updatedRegImage = crxRegImage;
	const uint8_t localPinIndex = (uint8_t) (GPIO_PinMaskToIndex(pinMask) & GPIO_LL_CRX_LOCAL_PIN_INDEX_MASK);
	const uint32_t fieldShift = ((uint32_t) localPinIndex * GPIO_LL_CRX_PIN_MODE_CNF_FIELD_WIDTH);
	const uint32_t cnfShift = (fieldShift + GPIO_LL_CRX_CNF_BITS_SHIFT);
	const uint32_t cnfMask = BIT_VALUE(GPIO_LL_CRX_CNF_BITS_MASK, cnfShift);

	updatedRegImage &= ~cnfMask;
	updatedRegImage |= BIT_VALUE((((uint32_t) cnfBits) & GPIO_LL_CRX_CNF_BITS_MASK), cnfShift);

	return updatedRegImage;
}

/**
 * @brief Packs raw MODE and CNF bits into one right-aligned pin MODE/CNF field
 * @param[in]	modeBits	Raw STM32F1 `MODE[1:0]` field value
 * @param[in]	cnfBits		Raw STM32F1 `CNF[1:0]` field value
 * @returns Right-aligned raw four-bit MODE/CNF field
 * @retval - `0x00U..0x0FU`: Raw `CNF[1:0] | MODE[1:0]` field value
 */
__STATIC_FORCEINLINE gpio_pin_config_bits_t GPIO_LL_PackPinModeCNFField
(
	const gpio_mode_t modeBits,
	const gpio_cnf_t cnfBits
)
{
	return (gpio_pin_config_bits_t)
	(
		((((uint32_t) cnfBits) & GPIO_LL_CRX_CNF_BITS_MASK) << GPIO_LL_CRX_CNF_BITS_SHIFT) |
		((((uint32_t) modeBits) & GPIO_LL_CRX_MODE_BITS_MASK) << GPIO_LL_CRX_MODE_BITS_SHIFT)
	);
}

/**
 * @brief Reads raw MODE bits from one right-aligned MODE/CNF field
 * @param[in]	crxField	Right-aligned raw MODE/CNF field
 * @returns Raw STM32F1 `MODE[1:0]` field value
 * @retval - `0x00U..0x03U`: Raw MODE field value
 */
__STATIC_FORCEINLINE gpio_mode_t GPIO_LL_GetModeBitsFromPinModeCNFField(const gpio_pin_config_bits_t crxField)
{
	return (gpio_mode_t)
	(
		(((uint32_t) crxField) >> GPIO_LL_CRX_MODE_BITS_SHIFT) &
		GPIO_LL_CRX_MODE_BITS_MASK
	);
}

/**
 * @brief Reads raw CNF bits from one right-aligned MODE/CNF field
 * @param[in]	crxField	Right-aligned raw MODE/CNF field
 * @returns Raw STM32F1 `CNF[1:0]` field value
 * @retval - `0x00U..0x03U`: Raw CNF field value
 */
__STATIC_FORCEINLINE gpio_cnf_t GPIO_LL_GetCNFBitsFromPinModeCNFField(const gpio_pin_config_bits_t crxField)
{
	return (gpio_cnf_t)
	(
		(((uint32_t) crxField) >> GPIO_LL_CRX_CNF_BITS_SHIFT) &
		GPIO_LL_CRX_CNF_BITS_MASK
	);
}

/** @} */ // GPIO_02_LL_03_ModeCNF

// ==================================================================================================== //
//											GPIO LL I/O APIs											//
// ==================================================================================================== //

/**
 * @brief	GPIO LL I/O APIs
 * @defgroup GPIO_02_LL_04_IO GPIO LL I/O APIs
 * @ingroup	GPIO_02_LL
 * @details
 * These APIs name the GPIO register being touched and the raw pin-mask I/O
 * action being performed.
 *
 * Practical Rule:
 * - Caller must pass a valid GPIO instance and valid raw pin mask.
 * - These APIs do not validate inputs and do not apply driver policy.
 * @{
 */

/**
 * @brief Writes a pin-set mask to the GPIO `BSRR` register
 * @param[in]	GPIOx		GPIO peripheral instance
 * @param[in]	pinMask		Raw pin mask to set through `BSRR`
 * @returns Void
 */
__STATIC_FORCEINLINE void GPIO_LL_SetPin(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask)
{
	GPIO_LL_WRITE_REG(GPIOx, BSRR, (uint32_t) pinMask);
}

/**
 * @brief Writes a pin-reset mask to the GPIO `BRR` register
 * @param[in]	GPIOx		GPIO peripheral instance
 * @param[in]	pinMask		Raw pin mask to reset through `BRR`
 * @returns Void
 */
__STATIC_FORCEINLINE void GPIO_LL_ResetPin(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask)
{
	GPIO_LL_WRITE_REG(GPIOx, BRR, (uint32_t) pinMask);
}

/**
 * @brief Toggles selected bits in the GPIO `ODR` register
 * @param[in]	GPIOx		GPIO peripheral instance
 * @param[in]	pinMask		Raw pin mask to toggle in `ODR`
 * @returns Void
 * @note This operation modifies `ODR` and is a read-modify-write operation.
 */
__STATIC_FORCEINLINE void GPIO_LL_TogglePin(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask)
{
	GPIO_LL_TOGGLE_BITS(GPIOx, ODR, (uint32_t) pinMask);
}

/**
 * @brief Reads selected bits from the GPIO `IDR` register
 * @param[in]	GPIOx		GPIO peripheral instance
 * @param[in]	pinMask		Raw pin mask to read from `IDR`
 * @returns Masked `IDR` register image for @p pinMask
 */
__STATIC_FORCEINLINE uint32_t GPIO_LL_ReadPin(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask)
{
	uint32_t regImage = 0x00000000UL;
	GPIO_LL_READ_REG(GPIOx, IDR, regImage);
	return (regImage & (uint32_t) pinMask);
}

/** @} */ // GPIO_02_LL_04_IO

/** @} */ // GPIO_02_LL

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_LL_H_ */
