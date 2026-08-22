/**
 * @file	rcc_ll.h
 * @author	Shrey Shah
 * @brief	RCC Low-Level Register Access Interface
 * @version	v4.0
 * @date	22-08-2026
 *
 * @details
 * This header defines the RCC low-level module that sits directly above the
 * register-layer definitions from @ref stm32f1xx_rcc.h.
 *
 * LL authority is intentionally narrow. It owns dumb RCC register access:
 * - a generic pointer-based read/write primitive pair shared by every named accessor
 * - named full-register accessors for `CR`, `CFGR`, `AHBENR`, `APB2ENR`, `APB1ENR`,
 *   `APB2RSTR`, and `APB1RSTR`
 * - single-field set/get wrappers built on those named accessors
 *
 * This module does not own:
 * - RCC selector vocabulary or selector/field translation (that is @ref rcc_codec.h)
 * - clock-tree sequencing, timeout policy, or ready-state waiting
 * - derived frequency calculation
 * - public driver policy validation beyond raw field/mask legality
 *
 * Practical Authority Rule:
 * - Layer 0 (`stm32f1xx_rcc.h`) defines the raw RCC register map.
 * - LL exposes named full-register accessors plus single-field wrappers only.
 * - Codec APIs own selector-to-field translation.
 * - RegOps owns peripheral-independent register access mechanics.
 * - Driver APIs (`rcc.h` / `rcc.c`) own public validation, sequencing, and
 *   user-facing status.
 *
 * @note Functions in this file do not validate clock-tree policy or hardware
 * readiness; they only apply the raw field or mask the caller supplies.
 */

#ifndef RCC_LL_H_
#define RCC_LL_H_

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //
#include "stm32f1xx.h"

/**
 * @addtogroup RCC_02_LL
 * @{
 */

// ==================================================================================================== //
//                                     RCC LL Register Access APIs                                      //
// ==================================================================================================== //

/**
 * @brief	RCC LL register access APIs
 * @defgroup RCC_02_LL_01_RegisterOps RCC LL Register Access APIs
 * @ingroup	RCC_02_LL
 * @details
 * These functions are intentionally dumb full-register image readers and
 * writers. They do not know RCC selector vocabulary, selector-to-field
 * translation, or clock-tree sequencing policy.
 *
 * Practical Rule:
 * - Use `.REG` through @ref `LL_RCC_REG` for RCC union registers.
 * - Do not use `.BIT` in the LL layer.
 * - Read-modify-write policy for a single field belongs to the single-field
 *   wrapper functions below, which stage the field in a local image and
 *   commit it through the same primitive pair as every other accessor.
 *
 * @warning These accessors perform no NULL, reserved-bit, or write-permission
 * checks beyond the raw field/mask legality checks documented per function.
 * @{
 */

/**
 * @brief Returns pointer to an RCC union register `.REG` image
 * @def LL_RCC_REG
 * @param[in]	_REG	Union register member token inside @ref RCC_TypeDef
 * @returns Pointer to the selected RCC register `.REG` image.
 * @note Thin RCC LL alias over @ref `REGOPS_REG`.
 */
#define LL_RCC_REG(_REG)							REGOPS_REG(RCC, _REG)

/**
 * @brief Reads one RCC register image by register pointer
 * @param[in]	pRegister	Pointer to an RCC register image
 * @returns Full 32-bit register image currently observed at @p pRegister.
 * @note Caller must pass a valid RCC register pointer.
 */
__STATIC_FORCEINLINE reg LL_RCC_ReadRegister(const _IO* const pRegister)
{
	// Local Variable
	reg regImage = 0x00000000UL;
	//! Read the full 32-bit register image into caller-owned storage.
	(void) RegOps_Read(pRegister, &regImage);
	//! Return the full 32-bit register image to the caller.
	return regImage;
}

/**
 * @brief Writes one RCC register image by register pointer
 * @param[in]	pRegister	Pointer to a writable RCC register image
 * @param[in]	regImage	Full 32-bit register image to write
 * @note Caller must pass a valid writable RCC register pointer and a complete
 * register image appropriate for that register.
 */
__STATIC_FORCEINLINE void LL_RCC_WriteRegister(_IO* const pRegister, const reg regImage)
{
	//! Forward the complete image without adding register-specific policy.
	(void) RegOps_Write(pRegister, regImage);
}

/**
 * @brief Reads the RCC `CR` register image
 * @returns Full `RCC_CR` image.
 * @note HSI/HSE/PLL enable-bit and ready-flag decoding belongs above LL.
 */
__STATIC_FORCEINLINE reg LL_RCC_ReadCR(void)
{
	//! Address the CR union image through the shared register-pointer accessor.
	return LL_RCC_ReadRegister(LL_RCC_REG(CR));
}

/**
 * @brief Writes the RCC `CR` register image
 * @param[in]	regImage	Full `RCC_CR` image to write
 * @note Caller owns read-modify-write staging for the single bit it intends to change.
 */
__STATIC_FORCEINLINE void LL_RCC_WriteCR(const reg regImage)
{
	//! Forward the staged CR image without modifying unrelated bits.
	LL_RCC_WriteRegister(LL_RCC_REG(CR), regImage);
}

/**
 * @brief Reads the RCC `CFGR` register image
 * @returns Full `RCC_CFGR` image.
 * @note Selector field extraction belongs to @ref rcc_codec.h.
 */
__STATIC_FORCEINLINE reg LL_RCC_ReadCFGR(void)
{
	//! Address the CFGR union image through the shared register-pointer accessor.
	return LL_RCC_ReadRegister(LL_RCC_REG(CFGR));
}

/**
 * @brief Writes the RCC `CFGR` register image
 * @param[in]	regImage	Full `RCC_CFGR` image to write
 * @note Caller owns read-modify-write staging for the single field it intends to change.
 */
__STATIC_FORCEINLINE void LL_RCC_WriteCFGR(const reg regImage)
{
	//! Forward the staged CFGR image without modifying unrelated fields.
	LL_RCC_WriteRegister(LL_RCC_REG(CFGR), regImage);
}

/**
 * @brief Reads the RCC `AHBENR` register image
 * @returns Full `RCC_AHBENR` image.
 */
__STATIC_FORCEINLINE reg LL_RCC_ReadAHBENR(void)
{
	//! Address the AHBENR union image through the shared register-pointer accessor.
	return LL_RCC_ReadRegister(LL_RCC_REG(AHBENR));
}

/**
 * @brief Writes the RCC `AHBENR` register image
 * @param[in]	regImage	Full `RCC_AHBENR` image to write
 * @note Caller owns read-modify-write staging for the requested clock-gate mask.
 */
__STATIC_FORCEINLINE void LL_RCC_WriteAHBENR(const reg regImage)
{
	//! Forward the staged AHBENR image without touching unrelated clock gates.
	LL_RCC_WriteRegister(LL_RCC_REG(AHBENR), regImage);
}

/**
 * @brief Reads the RCC `APB2ENR` register image
 * @returns Full `RCC_APB2ENR` image.
 */
__STATIC_FORCEINLINE reg LL_RCC_ReadAPB2ENR(void)
{
	//! Address the APB2ENR union image through the shared register-pointer accessor.
	return LL_RCC_ReadRegister(LL_RCC_REG(APB2ENR));
}

/**
 * @brief Writes the RCC `APB2ENR` register image
 * @param[in]	regImage	Full `RCC_APB2ENR` image to write
 * @note Caller owns read-modify-write staging for the requested clock-gate mask.
 */
__STATIC_FORCEINLINE void LL_RCC_WriteAPB2ENR(const reg regImage)
{
	//! Forward the staged APB2ENR image without touching unrelated clock gates.
	LL_RCC_WriteRegister(LL_RCC_REG(APB2ENR), regImage);
}

/**
 * @brief Reads the RCC `APB1ENR` register image
 * @returns Full `RCC_APB1ENR` image.
 */
__STATIC_FORCEINLINE reg LL_RCC_ReadAPB1ENR(void)
{
	//! Address the APB1ENR union image through the shared register-pointer accessor.
	return LL_RCC_ReadRegister(LL_RCC_REG(APB1ENR));
}

/**
 * @brief Writes the RCC `APB1ENR` register image
 * @param[in]	regImage	Full `RCC_APB1ENR` image to write
 * @note Caller owns read-modify-write staging for the requested clock-gate mask.
 */
__STATIC_FORCEINLINE void LL_RCC_WriteAPB1ENR(const reg regImage)
{
	//! Forward the staged APB1ENR image without touching unrelated clock gates.
	LL_RCC_WriteRegister(LL_RCC_REG(APB1ENR), regImage);
}

/**
 * @brief Reads the RCC `APB2RSTR` register image
 * @returns Full `RCC_APB2RSTR` image.
 */
__STATIC_FORCEINLINE reg LL_RCC_ReadAPB2RSTR(void)
{
	//! Address the APB2RSTR union image through the shared register-pointer accessor.
	return LL_RCC_ReadRegister(LL_RCC_REG(APB2RSTR));
}

/**
 * @brief Writes the RCC `APB2RSTR` register image
 * @param[in]	regImage	Full `RCC_APB2RSTR` image to write
 * @note Caller owns force/release reset-bit staging and pulse sequencing.
 */
__STATIC_FORCEINLINE void LL_RCC_WriteAPB2RSTR(const reg regImage)
{
	//! Forward the staged APB2RSTR image without touching unrelated reset bits.
	LL_RCC_WriteRegister(LL_RCC_REG(APB2RSTR), regImage);
}

/**
 * @brief Reads the RCC `APB1RSTR` register image
 * @returns Full `RCC_APB1RSTR` image.
 */
__STATIC_FORCEINLINE reg LL_RCC_ReadAPB1RSTR(void)
{
	//! Address the APB1RSTR union image through the shared register-pointer accessor.
	return LL_RCC_ReadRegister(LL_RCC_REG(APB1RSTR));
}

/**
 * @brief Writes the RCC `APB1RSTR` register image
 * @param[in]	regImage	Full `RCC_APB1RSTR` image to write
 * @note Caller owns force/release reset-bit staging and pulse sequencing.
 */
__STATIC_FORCEINLINE void LL_RCC_WriteAPB1RSTR(const reg regImage)
{
	//! Forward the staged APB1RSTR image without touching unrelated reset bits.
	LL_RCC_WriteRegister(LL_RCC_REG(APB1RSTR), regImage);
}

/** @} */ // RCC_02_LL_01_RegisterOps

// ==================================================================================================== //
//                                    RCC LL Field Validity Predicates                                  //
// ==================================================================================================== //

/**
 * @brief	RCC LL field validity predicates
 * @defgroup RCC_02_LL_02_Validity RCC LL Field Validity Predicates
 * @ingroup	RCC_02_LL
 * @{
 */

/**
 * @brief	Checks System Clock Source Field Validity
 * @def		LL_RCC_IS_SYSTEM_CLOCK_SOURCE_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_SW`
 * @returns System Clock Source Validity Status
 * @retval - `0x00U`: Invalid System Clock Source
 * @retval - `0x01U`: Valid System Clock Source
 */
#define LL_RCC_IS_SYSTEM_CLOCK_SOURCE_VALID(_FIELD)										\
(																						\
	(((_FIELD) == RCC_CFGR_SW_HSI)	||	((_FIELD) == RCC_CFGR_SW_HSE)	||				\
	((_FIELD) == RCC_CFGR_SW_PLL)) ? 0x01U : 0x00U										\
)

/**
 * @brief	Checks PLL Source Field Validity
 * @def		LL_RCC_IS_PLL_SOURCE_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_PLLSRC`
 * @returns PLL Source Validity Status
 * @retval - `0x00U`: Invalid PLL Source
 * @retval - `0x01U`: Valid PLL Source
 */
#define LL_RCC_IS_PLL_SOURCE_VALID(_FIELD)															\
(																									\
	(((_FIELD) == RCC_CFGR_PLLSRC_HSI_DIV2)	|| ((_FIELD) == RCC_CFGR_PLLSRC_HSE)) ? 0x01U : 0x00U	\
)

/**
 * @brief	Checks PLL HSE Divider Field Validity
 * @def		LL_RCC_IS_PLL_HSE_DIVIDER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_PLLXTPRE`
 * @returns PLL HSE Divider Validity Status
 * @retval - `0x00U`: Invalid PLL HSE Divider
 * @retval - `0x01U`: Valid PLL HSE Divider
 */
#define LL_RCC_IS_PLL_HSE_DIVIDER_VALID(_FIELD)															\
(																										\
	(((_FIELD) == RCC_CFGR_PLLXTPRE_HSE) ||	((_FIELD) == RCC_CFGR_PLLXTPRE_HSE_DIV2)) ? 0x01U : 0x00U	\
)

/**
 * @brief	Checks PLL Multiplier Field Validity
 * @def		LL_RCC_IS_PLL_MULTIPLIER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_PLLMUL`
 * @returns PLL Multiplier Validity Status
 * @retval - `0x00U`: Invalid PLL Multiplier
 * @retval - `0x01U`: Valid PLL Multiplier
 */
#define LL_RCC_IS_PLL_MULTIPLIER_VALID(_FIELD)											\
(																						\
	(((_FIELD) == RCC_CFGR_PLLMUL_2)	||	((_FIELD) == RCC_CFGR_PLLMUL_3)		||		\
	((_FIELD) == RCC_CFGR_PLLMUL_4)		||	((_FIELD) == RCC_CFGR_PLLMUL_5)		||		\
	((_FIELD) == RCC_CFGR_PLLMUL_6)		||	((_FIELD) == RCC_CFGR_PLLMUL_7)		||		\
	((_FIELD) == RCC_CFGR_PLLMUL_8)		||	((_FIELD) == RCC_CFGR_PLLMUL_9)		||		\
	((_FIELD) == RCC_CFGR_PLLMUL_10)	||	((_FIELD) == RCC_CFGR_PLLMUL_11)	||		\
	((_FIELD) == RCC_CFGR_PLLMUL_12)	||	((_FIELD) == RCC_CFGR_PLLMUL_13)	||		\
	((_FIELD) == RCC_CFGR_PLLMUL_14)	||	((_FIELD) == RCC_CFGR_PLLMUL_15)	||		\
	((_FIELD) == RCC_CFGR_PLLMUL_16)) ? 0x01U : 0x00U									\
)

/**
 * @brief	Checks AHB Prescaler Field Validity
 * @def		LL_RCC_IS_AHB_PRESCALER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_HPRE`
 * @returns AHB Prescaler Validity Status
 * @retval - `0x00U`: Invalid AHB Prescaler
 * @retval - `0x01U`: Valid AHB Prescaler
 */
#define LL_RCC_IS_AHB_PRESCALER_VALID(_FIELD)												\
(																							\
	(((_FIELD) == RCC_CFGR_HPRE_DIV1)		||	((_FIELD) == RCC_CFGR_HPRE_DIV2)		||	\
	((_FIELD) == RCC_CFGR_HPRE_DIV4)		||	((_FIELD) == RCC_CFGR_HPRE_DIV8)		||	\
	((_FIELD) == RCC_CFGR_HPRE_DIV16)		||	((_FIELD) == RCC_CFGR_HPRE_DIV64)		||	\
	((_FIELD) == RCC_CFGR_HPRE_DIV128)		||	((_FIELD) == RCC_CFGR_HPRE_DIV256)		||	\
	((_FIELD) == RCC_CFGR_HPRE_DIV512)) ? 0x01U : 0x00U										\
)

/**
 * @brief	Checks APB1 Prescaler Field Validity
 * @def		LL_RCC_IS_APB1_PRESCALER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_PPRE1`
 * @returns APB1 Prescaler Validity Status
 * @retval - `0x00U`: Invalid APB1 Prescaler
 * @retval - `0x01U`: Valid APB1 Prescaler
 */
#define LL_RCC_IS_APB1_PRESCALER_VALID(_FIELD)											\
(																						\
	(((_FIELD) == RCC_CFGR_PPRE1_DIV1)	||	((_FIELD) == RCC_CFGR_PPRE1_DIV2)	||		\
	((_FIELD) == RCC_CFGR_PPRE1_DIV4)	||	((_FIELD) == RCC_CFGR_PPRE1_DIV8)	||		\
	((_FIELD) == RCC_CFGR_PPRE1_DIV16)) ? 0x01U : 0x00U									\
)

/**
 * @brief	Checks APB2 Prescaler Field Validity
 * @def		LL_RCC_IS_APB2_PRESCALER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_PPRE2`
 * @returns APB2 Prescaler Validity Status
 * @retval - `0x00U`: Invalid APB2 Prescaler
 * @retval - `0x01U`: Valid APB2 Prescaler
 */
#define LL_RCC_IS_APB2_PRESCALER_VALID(_FIELD)											\
(																						\
	(((_FIELD) == RCC_CFGR_PPRE2_DIV1)	||	((_FIELD) == RCC_CFGR_PPRE2_DIV2)	||		\
	((_FIELD) == RCC_CFGR_PPRE2_DIV4)	||	((_FIELD) == RCC_CFGR_PPRE2_DIV8)	||		\
	((_FIELD) == RCC_CFGR_PPRE2_DIV16)) ? 0x01U : 0x00U								\
)

/**
 * @brief	Checks ADC Prescaler Field Validity
 * @def		LL_RCC_IS_ADC_PRESCALER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_ADCPRE`
 * @returns ADC Prescaler Validity Status
 * @retval - `0x00U`: Invalid ADC Prescaler
 * @retval - `0x01U`: Valid ADC Prescaler
 */
#define LL_RCC_IS_ADC_PRESCALER_VALID(_FIELD)											\
(																						\
	(((_FIELD) == RCC_CFGR_ADCPRE_DIV2)	||	((_FIELD) == RCC_CFGR_ADCPRE_DIV4)	||		\
	((_FIELD) == RCC_CFGR_ADCPRE_DIV6)	||	((_FIELD) == RCC_CFGR_ADCPRE_DIV8)) ?			\
	0x01U : 0x00U																			\
)

/**
 * @brief	Checks USB Prescaler Field Validity
 * @def		LL_RCC_IS_USB_PRESCALER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_USBPRE`
 * @returns USB Prescaler Validity Status
 * @retval - `0x00U`: Invalid USB Prescaler
 * @retval - `0x01U`: Valid USB Prescaler
 */
#define LL_RCC_IS_USB_PRESCALER_VALID(_FIELD)											\
(																						\
	(((_FIELD) == RCC_CFGR_USBPRE_DIV1_5)	||	((_FIELD) == RCC_CFGR_USBPRE_DIRECT)) ?		\
	0x01U : 0x00U																			\
)

/**
 * @brief	Checks Bit-Mask Validity
 * @def		LL_RCC_IS_MASK_VALID
 * @param[in] _MASK	Raw hardware bit-mask
 * @returns Bit-Mask Validity Status
 * @retval - `0x00U`: Invalid Bit-Mask
 * @retval - `0x01U`: Valid Bit-Mask
 */
#define LL_RCC_IS_MASK_VALID(_MASK)															\
(																						\
	(((_MASK) != 0x00UL) ? 0x01U : 0x00U)												\
)

/** @} */ // RCC_02_LL_02_Validity

// ==================================================================================================== //
//                                       RCC LL System Clock APIs                                       //
// ==================================================================================================== //

/**
 * @brief	RCC LL System Clock Control
 * @defgroup RCC_02_LL_03_SystemClock RCC LL System Clock Control
 * @ingroup	RCC_02_LL
 * @details
 * This group owns register-near control of HSI, HSE, PLL, SYSCLK source selection,
 * and PLL-related field programming using raw hardware field values from
 * @ref stm32f1xx_rcc.h.
 * @{
 */

/**
 * @brief	Enables HSI Clock Source
 * @details
 * Sets the `HSION` bit in `RCC_CR` to request enabling the internal
 * high-speed oscillator.
 * @returns	Void
 */
__STATIC_FORCEINLINE void LL_RCC_EnableHSI(void)
{
	// Local Variable
	reg crImage = LL_RCC_ReadCR();
	//! Preserve every other CR bit while setting only HSION.
	crImage |= RCC_CR_HSION;
	LL_RCC_WriteCR(crImage);
}

/**
 * @brief	Disables HSI Clock Source
 * @details
 * Clears the `HSION` bit in `RCC_CR` to request disabling the internal
 * high-speed oscillator.
 * @returns	Void
 */
__STATIC_FORCEINLINE void LL_RCC_DisableHSI(void)
{
	// Local Variable
	reg crImage = LL_RCC_ReadCR();
	//! Preserve every other CR bit while clearing only HSION.
	crImage &= ~RCC_CR_HSION;
	LL_RCC_WriteCR(crImage);
}

/**
 * @brief	Gets HSI Ready Status
 * @details
 * Reads the `HSIRDY` bit from `RCC_CR` and reports whether HSI is stable
 * and ready for use.
 * @returns @ref driver_status_t "Status of HSI ready state"
 * @retval - @ref `DRIVER_STATUS_READY`: HSI clock source is ready
 * @retval - @ref `DRIVER_STATUS_OFF`: HSI clock source is not ready
 */
__STATIC_FORCEINLINE driver_status_t LL_RCC_GetHSIReadyStatus(void)
{
	const reg crImage = LL_RCC_ReadCR();
	return (((crImage & RCC_CR_HSIRDY) != 0x00UL) ? DRIVER_STATUS_READY : DRIVER_STATUS_OFF);
}

/**
 * @brief	Enables HSE Clock Source
 * @details
 * Sets the `HSEON` bit in `RCC_CR` to request enabling the external
 * high-speed oscillator.
 * @returns	Void
 */
__STATIC_FORCEINLINE void LL_RCC_EnableHSE(void)
{
	// Local Variable
	reg crImage = LL_RCC_ReadCR();
	//! Preserve every other CR bit while setting only HSEON.
	crImage |= RCC_CR_HSEON;
	LL_RCC_WriteCR(crImage);
}

/**
 * @brief	Disables HSE Clock Source
 * @details
 * Clears the `HSEON` bit in `RCC_CR` to request disabling the external
 * high-speed oscillator.
 * @returns	Void
 */
__STATIC_FORCEINLINE void LL_RCC_DisableHSE(void)
{
	// Local Variable
	reg crImage = LL_RCC_ReadCR();
	//! Preserve every other CR bit while clearing only HSEON.
	crImage &= ~RCC_CR_HSEON;
	LL_RCC_WriteCR(crImage);
}

/**
 * @brief	Enables HSE Bypass
 * @details
 * Sets the `HSEBYP` bit in `RCC_CR` to bypass the crystal oscillator and
 * use an external clock source on HSE.
 * @returns	Void
 */
__STATIC_FORCEINLINE void LL_RCC_EnableHSEBypass(void)
{
	// Local Variable
	reg crImage = LL_RCC_ReadCR();
	//! Preserve every other CR bit while setting only HSEBYP.
	crImage |= RCC_CR_HSEBYP;
	LL_RCC_WriteCR(crImage);
}

/**
 * @brief	Disables HSE Bypass
 * @details
 * Clears the `HSEBYP` bit in `RCC_CR` to use the normal HSE crystal path.
 * @returns	Void
 */
__STATIC_FORCEINLINE void LL_RCC_DisableHSEBypass(void)
{
	// Local Variable
	reg crImage = LL_RCC_ReadCR();
	//! Preserve every other CR bit while clearing only HSEBYP.
	crImage &= ~RCC_CR_HSEBYP;
	LL_RCC_WriteCR(crImage);
}

/**
 * @brief	Gets HSE Ready Status
 * @details
 * Reads the `HSERDY` bit from `RCC_CR` and reports whether HSE is stable
 * and ready for use.
 * @returns @ref driver_status_t "Status of HSE ready state"
 * @retval - @ref `DRIVER_STATUS_READY`: HSE clock source is ready
 * @retval - @ref `DRIVER_STATUS_OFF`: HSE clock source is not ready
 */
__STATIC_FORCEINLINE driver_status_t LL_RCC_GetHSEReadyStatus(void)
{
	const reg crImage = LL_RCC_ReadCR();
	return (((crImage & RCC_CR_HSERDY) != 0x00UL) ? DRIVER_STATUS_READY : DRIVER_STATUS_OFF);
}

/**
 * @brief	Enables PLL
 * @details
 * Sets the `PLLON` bit in `RCC_CR` to request enabling the PLL.
 * @returns	Void
 */
__STATIC_FORCEINLINE void LL_RCC_EnablePLL(void)
{
	// Local Variable
	reg crImage = LL_RCC_ReadCR();
	//! Preserve every other CR bit while setting only PLLON.
	crImage |= RCC_CR_PLLON;
	LL_RCC_WriteCR(crImage);
}

/**
 * @brief	Disables PLL
 * @details
 * Clears the `PLLON` bit in `RCC_CR` to request disabling the PLL.
 * @returns	Void
 */
__STATIC_FORCEINLINE void LL_RCC_DisablePLL(void)
{
	// Local Variable
	reg crImage = LL_RCC_ReadCR();
	//! Preserve every other CR bit while clearing only PLLON.
	crImage &= ~RCC_CR_PLLON;
	LL_RCC_WriteCR(crImage);
}

/**
 * @brief	Gets PLL Ready Status
 * @details
 * Reads the `PLLRDY` bit from `RCC_CR` and reports whether PLL is stable
 * and ready for use.
 * @returns @ref driver_status_t "Status of PLL ready state"
 * @retval - @ref `DRIVER_STATUS_READY`: PLL is ready
 * @retval - @ref `DRIVER_STATUS_OFF`: PLL is not ready
 */
__STATIC_FORCEINLINE driver_status_t LL_RCC_GetPLLReadyStatus(void)
{
	const reg crImage = LL_RCC_ReadCR();
	return (((crImage & RCC_CR_PLLRDY) != 0x00UL) ? DRIVER_STATUS_READY : DRIVER_STATUS_OFF);
}

/**
 * @brief	Sets System Clock Source Field
 * @details
 * Programs the `SW` field in `RCC_CFGR` using the supplied raw hardware
 * field value.
 * @param[in] sysClkSrcField	Raw hardware field value for `RCC_CFGR_SW`
 * Accepted values:
 * - `RCC_CFGR_SW_HSI`: Selects HSI as SYSCLK
 * - `RCC_CFGR_SW_HSE`: Selects HSE as SYSCLK
 * - `RCC_CFGR_SW_PLL`: Selects PLL as SYSCLK
 * @returns @ref driver_status_t "Status of system clock source update"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: System clock source field updated successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `sysClkSrcField` is invalid
 */
driver_status_t LL_RCC_SetSystemClockSource(const uint32_t sysClkSrcField);

/**
 * @brief	Gets System Clock Source Field
 * @details
 * Reads the `SW` field from `RCC_CFGR` and stores the raw hardware field
 * value in the supplied output pointer.
 * @param[out] pSysClkSrcField	Pointer to destination variable for `RCC_CFGR_SW` field value
 * @returns @ref driver_status_t "Status of system clock source read"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: System clock source field read successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: `pSysClkSrcField` is `NULL`
 */
driver_status_t LL_RCC_GetSystemClockSource(uint32_t* const pSysClkSrcField);

/**
 * @brief	Gets Active System Clock Status Field
 * @details
 * Reads the `SWS` field from `RCC_CFGR` and stores the raw hardware field
 * value in the supplied output pointer.
 * @param[out] pSysClkStatusField	Pointer to destination variable for `RCC_CFGR_SWS` field value
 * @returns @ref driver_status_t "Status of system clock status read"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: System clock status field read successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: `pSysClkStatusField` is `NULL`
 */
driver_status_t LL_RCC_GetSystemClockStatus(uint32_t* const pSysClkStatusField);

/**
 * @brief	Sets PLL Source Field
 * @details
 * Programs the `PLLSRC` field in `RCC_CFGR` using the supplied raw
 * hardware field value.
 * @param[in] pllSrcField	Raw hardware field value for `RCC_CFGR_PLLSRC`
 * Accepted values:
 * - `RCC_CFGR_PLLSRC_HSI_DIV2`: Selects HSI/2 as the PLL input
 * - `RCC_CFGR_PLLSRC_HSE`: Selects HSE as the PLL input
 * @returns @ref driver_status_t "Status of PLL source field update"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: PLL source field updated successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `pllSrcField` is invalid
 */
driver_status_t LL_RCC_SetPLLSource(const uint32_t pllSrcField);

/**
 * @brief	Gets PLL Source Field
 * @details
 * Reads the `PLLSRC` field from `RCC_CFGR` and stores the raw hardware
 * field value in the supplied output pointer.
 * @param[out] pPllSrcField	Pointer to destination variable for `RCC_CFGR_PLLSRC` field value
 * @returns @ref driver_status_t "Status of PLL source field read"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: PLL source field read successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: `pPllSrcField` is `NULL`
 */
driver_status_t LL_RCC_GetPLLSource(uint32_t* const pPllSrcField);

/**
 * @brief	Sets PLL HSE Divider Field
 * @details
 * Programs the `PLLXTPRE` field in `RCC_CFGR` using the supplied raw
 * hardware field value.
 * @param[in] pllHseDividerField	Raw hardware field value for `RCC_CFGR_PLLXTPRE`
 * Accepted values:
 * - `RCC_CFGR_PLLXTPRE_HSE`: HSE feeds the PLL undivided
 * - `RCC_CFGR_PLLXTPRE_HSE_DIV2`: HSE/2 feeds the PLL
 * @returns @ref driver_status_t "Status of PLL HSE divider field update"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: PLL HSE divider field updated successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `pllHseDividerField` is invalid
 */
driver_status_t LL_RCC_SetPLLHSEDivider(const uint32_t pllHseDividerField);

/**
 * @brief	Gets PLL HSE Divider Field
 * @details
 * Reads the `PLLXTPRE` field from `RCC_CFGR` and stores the raw hardware
 * field value in the supplied output pointer.
 * @param[out] pPllHseDividerField	Pointer to destination variable for `RCC_CFGR_PLLXTPRE` field value
 * @returns @ref driver_status_t "Status of PLL HSE divider field read"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: PLL HSE divider field read successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: `pPllHseDividerField` is `NULL`
 */
driver_status_t LL_RCC_GetPLLHSEDivider(uint32_t* const pPllHseDividerField);

/**
 * @brief	Sets PLL Multiplier Field
 * @details
 * Programs the `PLLMUL` field in `RCC_CFGR` using the supplied raw
 * hardware field value.
 * @param[in] pllMulField	Raw hardware field value for `RCC_CFGR_PLLMUL`
 * Accepted values:
 * - `RCC_CFGR_PLLMUL_2` through `RCC_CFGR_PLLMUL_16`: PLL multiplication factors x2 through x16
 * @returns @ref driver_status_t "Status of PLL multiplier field update"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: PLL multiplier field updated successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `pllMulField` is invalid
 */
driver_status_t LL_RCC_SetPLLMultiplier(const uint32_t pllMulField);

/**
 * @brief	Gets PLL Multiplier Field
 * @details
 * Reads the `PLLMUL` field from `RCC_CFGR` and stores the raw hardware
 * field value in the supplied output pointer.
 * @param[out] pPllMulField	Pointer to destination variable for `RCC_CFGR_PLLMUL` field value
 * @returns @ref driver_status_t "Status of PLL multiplier field read"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: PLL multiplier field read successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: `pPllMulField` is `NULL`
 */
driver_status_t LL_RCC_GetPLLMultiplier(uint32_t* const pPllMulField);

/** @} */ // RCC_02_LL_03_SystemClock

// ==================================================================================================== //
//                                        RCC LL Prescaler APIs                                         //
// ==================================================================================================== //

/**
 * @brief	RCC LL Prescaler Control
 * @defgroup RCC_02_LL_04_Prescalers RCC LL Prescaler Control
 * @ingroup	RCC_02_LL
 * @details
 * This group owns register-near programming of AHB, APB, ADC, and USB prescaler
 * fields using raw hardware encodings from @ref stm32f1xx_rcc.h.
 * @{
 */

/**
 * @brief	Sets AHB Prescaler Field
 * @details Programs the `HPRE` field in `RCC_CFGR`.
 * @param[in] ahbPrescalerField	Raw hardware field value for `RCC_CFGR_HPRE`
 * Accepted values:
 * - `RCC_CFGR_HPRE_DIV1` through `RCC_CFGR_HPRE_DIV512`: AHB divide-by-1 through divide-by-512
 * @returns @ref driver_status_t "Status of AHB prescaler field update"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AHB prescaler field updated successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `ahbPrescalerField` is invalid
 */
driver_status_t LL_RCC_SetAHBPrescaler(const uint32_t ahbPrescalerField);

/**
 * @brief	Gets AHB Prescaler Field
 * @details Reads the `HPRE` field from `RCC_CFGR`.
 * @param[out] pAhbPrescalerField	Pointer to destination variable for `RCC_CFGR_HPRE` field value
 * @returns @ref driver_status_t "Status of AHB prescaler field read"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AHB prescaler field read successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: `pAhbPrescalerField` is `NULL`
 */
driver_status_t LL_RCC_GetAHBPrescaler(uint32_t* const pAhbPrescalerField);

/**
 * @brief	Sets APB1 Prescaler Field
 * @details Programs the `PPRE1` field in `RCC_CFGR`.
 * @param[in] apb1PrescalerField	Raw hardware field value for `RCC_CFGR_PPRE1`
 * Accepted values:
 * - `RCC_CFGR_PPRE1_DIV1` through `RCC_CFGR_PPRE1_DIV16`: APB1 divide-by-1 through divide-by-16
 * @returns @ref driver_status_t "Status of APB1 prescaler field update"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 prescaler field updated successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `apb1PrescalerField` is invalid
 */
driver_status_t LL_RCC_SetAPB1Prescaler(const uint32_t apb1PrescalerField);

/**
 * @brief	Gets APB1 Prescaler Field
 * @details Reads the `PPRE1` field from `RCC_CFGR`.
 * @param[out] pApb1PrescalerField	Pointer to destination variable for `RCC_CFGR_PPRE1` field value
 * @returns @ref driver_status_t "Status of APB1 prescaler field read"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 prescaler field read successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: `pApb1PrescalerField` is `NULL`
 */
driver_status_t LL_RCC_GetAPB1Prescaler(uint32_t* const pApb1PrescalerField);

/**
 * @brief	Sets APB2 Prescaler Field
 * @details Programs the `PPRE2` field in `RCC_CFGR`.
 * @param[in] apb2PrescalerField	Raw hardware field value for `RCC_CFGR_PPRE2`
 * Accepted values:
 * - `RCC_CFGR_PPRE2_DIV1` through `RCC_CFGR_PPRE2_DIV16`: APB2 divide-by-1 through divide-by-16
 * @returns @ref driver_status_t "Status of APB2 prescaler field update"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 prescaler field updated successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `apb2PrescalerField` is invalid
 */
driver_status_t LL_RCC_SetAPB2Prescaler(const uint32_t apb2PrescalerField);

/**
 * @brief	Gets APB2 Prescaler Field
 * @details Reads the `PPRE2` field from `RCC_CFGR`.
 * @param[out] pApb2PrescalerField	Pointer to destination variable for `RCC_CFGR_PPRE2` field value
 * @returns @ref driver_status_t "Status of APB2 prescaler field read"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 prescaler field read successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: `pApb2PrescalerField` is `NULL`
 */
driver_status_t LL_RCC_GetAPB2Prescaler(uint32_t* const pApb2PrescalerField);

/**
 * @brief	Sets ADC Prescaler Field
 * @details Programs the `ADCPRE` field in `RCC_CFGR`.
 * @param[in] adcPrescalerField	Raw hardware field value for `RCC_CFGR_ADCPRE`
 * Accepted values:
 * - `RCC_CFGR_ADCPRE_DIV2` through `RCC_CFGR_ADCPRE_DIV8`: ADC divide-by-2 through divide-by-8
 * @returns @ref driver_status_t "Status of ADC prescaler field update"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: ADC prescaler field updated successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `adcPrescalerField` is invalid
 */
driver_status_t LL_RCC_SetADCPrescaler(const uint32_t adcPrescalerField);

/**
 * @brief	Gets ADC Prescaler Field
 * @details Reads the `ADCPRE` field from `RCC_CFGR`.
 * @param[out] pAdcPrescalerField	Pointer to destination variable for `RCC_CFGR_ADCPRE` field value
 * @returns @ref driver_status_t "Status of ADC prescaler field read"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: ADC prescaler field read successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: `pAdcPrescalerField` is `NULL`
 */
driver_status_t LL_RCC_GetADCPrescaler(uint32_t* const pAdcPrescalerField);

/**
 * @brief	Sets USB Prescaler Field
 * @details Programs the `USBPRE` field in `RCC_CFGR`.
 * @param[in] usbPrescalerField	Raw hardware field value for `RCC_CFGR_USBPRE`
 * Accepted values:
 * - `RCC_CFGR_USBPRE_DIV1_5`: USB clock equals PLL divided by 1.5
 * - `RCC_CFGR_USBPRE_DIRECT`: USB clock equals PLL directly
 * @returns @ref driver_status_t "Status of USB prescaler field update"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: USB prescaler field updated successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `usbPrescalerField` is invalid
 */
driver_status_t LL_RCC_SetUSBPrescaler(const uint32_t usbPrescalerField);

/**
 * @brief	Gets USB Prescaler Field
 * @details Reads the `USBPRE` field from `RCC_CFGR`.
 * @param[out] pUsbPrescalerField	Pointer to destination variable for `RCC_CFGR_USBPRE` field value
 * @returns @ref driver_status_t "Status of USB prescaler field read"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: USB prescaler field read successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: `pUsbPrescalerField` is `NULL`
 */
driver_status_t LL_RCC_GetUSBPrescaler(uint32_t* const pUsbPrescalerField);

/** @} */ // RCC_02_LL_04_Prescalers

// ==================================================================================================== //
//                                     RCC LL Clock Gate and Reset                                      //
// ==================================================================================================== //

/**
 * @brief	RCC LL Clock Gate and Reset Control
 * @defgroup RCC_02_LL_05_ClockReset RCC LL Clock Gate and Reset Control
 * @ingroup	RCC_02_LL
 * @{
 */

/**
 * @brief	Enables AHB Peripheral Clock
 * @details Sets the requested enable bits in `RCC_AHBENR`.
 * @param[in] mask	Raw hardware bit mask for AHB peripheral clock enable
 * @returns @ref driver_status_t "Status of AHB clock enable operation"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AHB peripheral clock enabled successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t LL_RCC_EnableAHBClock(const uint32_t mask);

/**
 * @brief	Disables AHB Peripheral Clock
 * @details Clears the requested enable bits in `RCC_AHBENR`.
 * @param[in] mask	Raw hardware bit mask for AHB peripheral clock disable
 * @returns @ref driver_status_t "Status of AHB clock disable operation"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AHB peripheral clock disabled successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t LL_RCC_DisableAHBClock(const uint32_t mask);

/**
 * @brief	Enables APB2 Peripheral Clock
 * @details Sets the requested enable bits in `RCC_APB2ENR`.
 * @param[in] mask	Raw hardware bit mask for APB2 peripheral clock enable
 * @returns @ref driver_status_t "Status of APB2 clock enable operation"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 peripheral clock enabled successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t LL_RCC_EnableAPB2Clock(const uint32_t mask);

/**
 * @brief	Disables APB2 Peripheral Clock
 * @details Clears the requested enable bits in `RCC_APB2ENR`.
 * @param[in] mask	Raw hardware bit mask for APB2 peripheral clock disable
 * @returns @ref driver_status_t "Status of APB2 clock disable operation"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 peripheral clock disabled successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t LL_RCC_DisableAPB2Clock(const uint32_t mask);

/**
 * @brief	Enables APB1 Peripheral Clock
 * @details Sets the requested enable bits in `RCC_APB1ENR`.
 * @param[in] mask	Raw hardware bit mask for APB1 peripheral clock enable
 * @returns @ref driver_status_t "Status of APB1 clock enable operation"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 peripheral clock enabled successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t LL_RCC_EnableAPB1Clock(const uint32_t mask);

/**
 * @brief	Disables APB1 Peripheral Clock
 * @details Clears the requested enable bits in `RCC_APB1ENR`.
 * @param[in] mask	Raw hardware bit mask for APB1 peripheral clock disable
 * @returns @ref driver_status_t "Status of APB1 clock disable operation"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 peripheral clock disabled successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t LL_RCC_DisableAPB1Clock(const uint32_t mask);

/**
 * @brief	Forces APB2 Peripheral Reset
 * @details Sets the requested reset bits in `RCC_APB2RSTR`.
 * @param[in] mask	Raw hardware bit mask for APB2 peripheral reset
 * @returns @ref driver_status_t "Status of APB2 reset force operation"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 reset asserted successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t LL_RCC_ForceAPB2Reset(const uint32_t mask);

/**
 * @brief	Releases APB2 Peripheral Reset
 * @details Clears the requested reset bits in `RCC_APB2RSTR`.
 * @param[in] mask	Raw hardware bit mask for APB2 peripheral reset release
 * @returns @ref driver_status_t "Status of APB2 reset release operation"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 reset released successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t LL_RCC_ReleaseAPB2Reset(const uint32_t mask);

/**
 * @brief	Forces APB1 Peripheral Reset
 * @details Sets the requested reset bits in `RCC_APB1RSTR`.
 * @param[in] mask	Raw hardware bit mask for APB1 peripheral reset
 * @returns @ref driver_status_t "Status of APB1 reset force operation"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 reset asserted successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t LL_RCC_ForceAPB1Reset(const uint32_t mask);

/**
 * @brief	Releases APB1 Peripheral Reset
 * @details Clears the requested reset bits in `RCC_APB1RSTR`.
 * @param[in] mask	Raw hardware bit mask for APB1 peripheral reset release
 * @returns @ref driver_status_t "Status of APB1 reset release operation"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 reset released successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t LL_RCC_ReleaseAPB1Reset(const uint32_t mask);

/**
 * @brief	Pulses APB2 Peripheral Reset
 * @details Asserts and then releases the requested APB2 reset bits.
 * @param[in] mask	Raw hardware bit mask for APB2 peripheral reset pulse
 * @returns @ref driver_status_t "Status of APB2 reset pulse operation"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 reset pulsed successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t LL_RCC_PulseAPB2Reset(const uint32_t mask);

/**
 * @brief	Pulses APB1 Peripheral Reset
 * @details Asserts and then releases the requested APB1 reset bits.
 * @param[in] mask	Raw hardware bit mask for APB1 peripheral reset pulse
 * @returns @ref driver_status_t "Status of APB1 reset pulse operation"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 reset pulsed successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t LL_RCC_PulseAPB1Reset(const uint32_t mask);

/** @} */ // RCC_02_LL_05_ClockReset

/** @} */ // RCC_02_LL

// C++ Compatibility
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_LL_H_ */
