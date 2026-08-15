/**
 * @file	rcc_ll.h
 * @author	Shrey Shah
 * @brief	RCC Low-Level Control Interface
 * @version	v3.0
 * @date	22-03-2026
 *
 * @details
 * The RCC low-level layer is a thin, typed wrapper over the register definitions from
 * @ref stm32f1xx_rcc.h. It does not own clock-tree policy or board-level validation.
 * Its only job is to expose direct hardware actions with meaningful function names.
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
//                                      RCC LL Register Operation Macros                                //
// ==================================================================================================== //

/**
 * @brief	RCC LL Register Operation Macros
 * @defgroup RCC_02_LL_01_RegisterOps RCC LL Register Operation Macros
 * @ingroup	RCC_02_LL
 * @details
 * These macros build a thin RCC-specific convenience layer on top of the generic
 * @ref `REGOPS_READ`, @ref `REGOPS_WRITE`, @ref `REGOPS_SET`, @ref `REGOPS_CLEAR`, and
 * @ref `REGOPS_MODIFY` utilities.
 *
 * Practical Rule:
 * - Always access RCC registers through the `.REG` member.
 * - Do not use the `.BIT` view in the LL layer.
 * - Do not introduce RCC-specific selector values here; use raw hardware masks
 *   from @ref stm32f1xx_rcc.h.
 * @{
 */

/**
 * @brief	Returns pointer to RCC register `.REG` image
 * @def		RCC_LL_REG
 * @param[in] _REG	Register member name inside @ref RCC_TypeDef
 * @returns Pointer to the selected RCC register `.REG` image
 */
#define RCC_LL_REG(_REG)								REGOPS_REG(RCC, _REG)

/**
 * @brief	Reads full RCC register image
 * @def		RCC_LL_READ_REG
 * @param[in]	_REG	Register member name inside @ref RCC_TypeDef
 * @param[out]	_VAR	Destination variable that receives the register image
 */
#define RCC_LL_READ_REG(_REG, _VAR)						REGOPS_READ(RCC_LL_REG(_REG), (_VAR))

/**
 * @brief	Writes full RCC register image
 * @def		RCC_LL_WRITE_REG
 * @param[in]	_REG	Register member name inside @ref RCC_TypeDef
 * @param[in]	_VAL	Register image to write
 */
#define RCC_LL_WRITE_REG(_REG, _VAL)					REGOPS_WRITE(RCC_LL_REG(_REG), (_VAL))

/**
 * @brief	Sets RCC register bits
 * @def		RCC_LL_SET_BITS
 * @param[in]	_REG	Register member name inside @ref RCC_TypeDef
 * @param[in]	_MASK	Bit mask to set
 */
#define RCC_LL_SET_BITS(_REG, _MASK)					REGOPS_SET(RCC_LL_REG(_REG), (_MASK))

/**
 * @brief	Clears RCC register bits
 * @def		RCC_LL_CLEAR_BITS
 * @param[in]	_REG	Register member name inside @ref RCC_TypeDef
 * @param[in]	_MASK	Bit mask to clear
 */
#define RCC_LL_CLEAR_BITS(_REG, _MASK)					REGOPS_CLEAR(RCC_LL_REG(_REG), (_MASK))

/**
 * @brief	Modifies RCC register masked field
 * @def		RCC_LL_MODIFY_REG
 * @param[in]	_REG	Register member name inside @ref RCC_TypeDef
 * @param[in]	_MASK	Field mask to modify
 * @param[in]	_VAL	Masked field value to write
 *
 * @note `_VAL` must already be aligned to the target field position.
 */
#define RCC_LL_MODIFY_REG(_REG, _MASK, _VAL)			REGOPS_MODIFY(RCC_LL_REG(_REG), (_MASK), (_VAL))

/**
 * @brief	Checks System Clock Source Field Validity
 * @def		RCC_LL_IS_SYSTEM_CLOCK_SOURCE_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_SW`
 * @returns System Clock Source Validity Status
 * @retval - `0x00U`: Invalid System Clock Source
 * @retval - `0x01U`: Valid System Clock Source
 */
#define RCC_LL_IS_SYSTEM_CLOCK_SOURCE_VALID(_FIELD)										\
(																						\
	(((_FIELD) == RCC_CFGR_SW_HSI)	||	((_FIELD) == RCC_CFGR_SW_HSE)	||				\
	((_FIELD) == RCC_CFGR_SW_PLL)) ? 0x01U : 0x00U										\
)

/**
 * @brief	Checks PLL Source Field Validity
 * @def		RCC_LL_IS_PLL_SOURCE_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_PLLSRC`
 * @returns PLL Source Validity Status
 * @retval - `0x00U`: Invalid PLL Source
 * @retval - `0x01U`: Valid PLL Source
 */
#define RCC_LL_IS_PLL_SOURCE_VALID(_FIELD)															\
(																									\
	(((_FIELD) == RCC_CFGR_PLLSRC_HSI_DIV2)	|| ((_FIELD) == RCC_CFGR_PLLSRC_HSE)) ? 0x01U : 0x00U	\
)

/**
 * @brief	Checks PLL HSE Divider Field Validity
 * @def		RCC_LL_IS_PLL_HSE_DIVIDER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_PLLXTPRE`
 * @returns PLL HSE Divider Validity Status
 * @retval - `0x00U`: Invalid PLL HSE Divider
 * @retval - `0x01U`: Valid PLL HSE Divider
 */
#define RCC_LL_IS_PLL_HSE_DIVIDER_VALID(_FIELD)															\
(																										\
	(((_FIELD) == RCC_CFGR_PLLXTPRE_HSE) ||	((_FIELD) == RCC_CFGR_PLLXTPRE_HSE_DIV2)) ? 0x01U : 0x00U	\
)

/**
 * @brief	Checks PLL Multiplier Field Validity
 * @def		RCC_LL_IS_PLL_MULTIPLIER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_PLLMUL`
 * @returns PLL Multiplier Validity Status
 * @retval - `0x00U`: Invalid PLL Multiplier
 * @retval - `0x01U`: Valid PLL Multiplier
 */
#define RCC_LL_IS_PLL_MULTIPLIER_VALID(_FIELD)											\
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
 * @def		RCC_LL_IS_AHB_PRESCALER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_HPRE`
 * @returns AHB Prescaler Validity Status
 * @retval - `0x00U`: Invalid AHB Prescaler
 * @retval - `0x01U`: Valid AHB Prescaler
 */
#define RCC_LL_IS_AHB_PRESCALER_VALID(_FIELD)												\
(																							\
	(((_FIELD) == RCC_CFGR_HPRE_DIV1)		||	((_FIELD) == RCC_CFGR_HPRE_DIV2)		||	\
	((_FIELD) == RCC_CFGR_HPRE_DIV4)		||	((_FIELD) == RCC_CFGR_HPRE_DIV8)		||	\
	((_FIELD) == RCC_CFGR_HPRE_DIV16)		||	((_FIELD) == RCC_CFGR_HPRE_DIV64)		||	\
	((_FIELD) == RCC_CFGR_HPRE_DIV128)		||	((_FIELD) == RCC_CFGR_HPRE_DIV256)		||	\
	((_FIELD) == RCC_CFGR_HPRE_DIV512)) ? 0x01U : 0x00U										\
)

/**
 * @brief	Checks APB1 Prescaler Field Validity
 * @def		RCC_LL_IS_APB1_PRESCALER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_PPRE1`
 * @returns APB1 Prescaler Validity Status
 * @retval - `0x00U`: Invalid APB1 Prescaler
 * @retval - `0x01U`: Valid APB1 Prescaler
 */
#define RCC_LL_IS_APB1_PRESCALER_VALID(_FIELD)											\
(																						\
	(((_FIELD) == RCC_CFGR_PPRE1_DIV1)	||	((_FIELD) == RCC_CFGR_PPRE1_DIV2)	||		\
	((_FIELD) == RCC_CFGR_PPRE1_DIV4)	||	((_FIELD) == RCC_CFGR_PPRE1_DIV8)	||		\
	((_FIELD) == RCC_CFGR_PPRE1_DIV16)) ? 0x01U : 0x00U									\
)

/**
 * @brief	Checks APB2 Prescaler Field Validity
 * @def		RCC_LL_IS_APB2_PRESCALER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_PPRE2`
 * @returns APB2 Prescaler Validity Status
 * @retval - `0x00U`: Invalid APB2 Prescaler
 * @retval - `0x01U`: Valid APB2 Prescaler
 */
#define RCC_LL_IS_APB2_PRESCALER_VALID(_FIELD)											\
(																						\
	(((_FIELD) == RCC_CFGR_PPRE2_DIV1)	||	((_FIELD) == RCC_CFGR_PPRE2_DIV2)	||		\
	((_FIELD) == RCC_CFGR_PPRE2_DIV4)	||	((_FIELD) == RCC_CFGR_PPRE2_DIV8)	||		\
	((_FIELD) == RCC_CFGR_PPRE2_DIV16)) ? 0x01U : 0x00U								\
)

/**
 * @brief	Checks ADC Prescaler Field Validity
 * @def		RCC_LL_IS_ADC_PRESCALER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_ADCPRE`
 * @returns ADC Prescaler Validity Status
 * @retval - `0x00U`: Invalid ADC Prescaler
 * @retval - `0x01U`: Valid ADC Prescaler
 */
#define RCC_LL_IS_ADC_PRESCALER_VALID(_FIELD)											\
(																						\
	(((_FIELD) == RCC_CFGR_ADCPRE_DIV2)	||	((_FIELD) == RCC_CFGR_ADCPRE_DIV4)	||		\
	((_FIELD) == RCC_CFGR_ADCPRE_DIV6)	||	((_FIELD) == RCC_CFGR_ADCPRE_DIV8)) ?			\
	0x01U : 0x00U																			\
)

/**
 * @brief	Checks USB Prescaler Field Validity
 * @def		RCC_LL_IS_USB_PRESCALER_VALID
 * @param[in] _FIELD	Raw hardware field value for `RCC_CFGR_USBPRE`
 * @returns USB Prescaler Validity Status
 * @retval - `0x00U`: Invalid USB Prescaler
 * @retval - `0x01U`: Valid USB Prescaler
 */
#define RCC_LL_IS_USB_PRESCALER_VALID(_FIELD)											\
(																						\
	(((_FIELD) == RCC_CFGR_USBPRE_DIV1_5)	||	((_FIELD) == RCC_CFGR_USBPRE_DIRECT)) ?		\
	0x01U : 0x00U																			\
)

/**
 * @brief	Checks Bit-Mask Validity
 * @def		RCC_LL_IS_MASK_VALID
 * @param[in] _MASK	Raw hardware bit-mask
 * @returns Bit-Mask Validity Status
 * @retval - `0x00U`: Invalid Bit-Mask
 * @retval - `0x01U`: Valid Bit-Mask
 */
#define RCC_LL_IS_MASK_VALID(_MASK)															\
(																						\
	(((_MASK) != 0x00UL) ? 0x01U : 0x00U)												\
)

/** @} */ // RCC_02_LL_01_RegisterOps

// ==================================================================================================== //
//                                       RCC LL System Clock APIs                                       //
// ==================================================================================================== //

/**
 * @brief	RCC LL System Clock Control
 * @defgroup RCC_02_LL_02_SystemClock RCC LL System Clock Control
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
 * Sets the `HSION` bit in `RCC->CR.REG` to request enabling the internal
 * high-speed oscillator.
 *
 * @returns	Void
 */
__STATIC_FORCEINLINE void RCC_LL_EnableHSI(void)
{
	RCC_LL_SET_BITS(CR, RCC_CR_HSION);
}

/**
 * @brief	Disables HSI Clock Source
 * @details
 * Clears the `HSION` bit in `RCC->CR.REG` to request disabling the internal
 * high-speed oscillator.
 *
 * @returns	Void
 */
__STATIC_FORCEINLINE void RCC_LL_DisableHSI(void)
{
	RCC_LL_CLEAR_BITS(CR, RCC_CR_HSION);
}

/**
 * @brief	Gets HSI Ready Status
 * @details
 * Reads the `HSIRDY` bit from `RCC->CR.REG` and reports whether HSI is stable
 * and ready for use.
 *
 * @returns	@ref driver_status_t Status of HSI ready state
 * @retval	`DRIVER_STATUS_READY`: HSI clock source is ready
 * @retval	`DRIVER_STATUS_OFF`: HSI clock source is not ready
 */
__STATIC_FORCEINLINE driver_status_t RCC_LL_GetHSIReadyStatus(void)
{
	uint32_t regImage = 0x00UL;
	RCC_LL_READ_REG(CR, regImage);
	return (((regImage & RCC_CR_HSIRDY) != 0x00UL) ? DRIVER_STATUS_READY : DRIVER_STATUS_OFF);
}

/**
 * @brief	Enables HSE Clock Source
 * @details
 * Sets the `HSEON` bit in `RCC->CR.REG` to request enabling the external
 * high-speed oscillator.
 *
 * @returns	Void
 */
__STATIC_FORCEINLINE void RCC_LL_EnableHSE(void)
{
	RCC_LL_SET_BITS(CR, RCC_CR_HSEON);
}

/**
 * @brief	Disables HSE Clock Source
 * @details
 * Clears the `HSEON` bit in `RCC->CR.REG` to request disabling the external
 * high-speed oscillator.
 *
 * @returns	Void
 */
__STATIC_FORCEINLINE void RCC_LL_DisableHSE(void)
{
	RCC_LL_CLEAR_BITS(CR, RCC_CR_HSEON);
}

/**
 * @brief	Enables HSE Bypass
 * @details
 * Sets the `HSEBYP` bit in `RCC->CR.REG` to bypass the crystal oscillator and
 * use an external clock source on HSE.
 *
 * @returns	Void
 */
__STATIC_FORCEINLINE void RCC_LL_EnableHSEBypass(void)
{
	RCC_LL_SET_BITS(CR, RCC_CR_HSEBYP);
}

/**
 * @brief	Disables HSE Bypass
 * @details
 * Clears the `HSEBYP` bit in `RCC->CR.REG` to use the normal HSE crystal path.
 *
 * @returns	Void
 */
__STATIC_FORCEINLINE void RCC_LL_DisableHSEBypass(void)
{
	RCC_LL_CLEAR_BITS(CR, RCC_CR_HSEBYP);
}

/**
 * @brief	Gets HSE Ready Status
 * @details
 * Reads the `HSERDY` bit from `RCC->CR.REG` and reports whether HSE is stable
 * and ready for use.
 *
 * @returns	@ref driver_status_t Status of HSE ready state
 * @retval	`DRIVER_STATUS_READY`: HSE clock source is ready
 * @retval	`DRIVER_STATUS_OFF`: HSE clock source is not ready
 */
__STATIC_FORCEINLINE driver_status_t RCC_LL_GetHSEReadyStatus(void)
{
	uint32_t regImage = 0x00UL;
	RCC_LL_READ_REG(CR, regImage);
	return (((regImage & RCC_CR_HSERDY) != 0x00UL) ? DRIVER_STATUS_READY : DRIVER_STATUS_OFF);
}

/**
 * @brief	Enables PLL
 * @details
 * Sets the `PLLON` bit in `RCC->CR.REG` to request enabling the PLL.
 *
 * @returns	Void
 */
__STATIC_FORCEINLINE void RCC_LL_EnablePLL(void)
{
	RCC_LL_SET_BITS(CR, RCC_CR_PLLON);
}

/**
 * @brief	Disables PLL
 * @details
 * Clears the `PLLON` bit in `RCC->CR.REG` to request disabling the PLL.
 *
 * @returns	Void
 */
__STATIC_FORCEINLINE void RCC_LL_DisablePLL(void)
{
	RCC_LL_CLEAR_BITS(CR, RCC_CR_PLLON);
}

/**
 * @brief	Gets PLL Ready Status
 * @details
 * Reads the `PLLRDY` bit from `RCC->CR.REG` and reports whether PLL is stable
 * and ready for use.
 *
 * @returns	@ref driver_status_t Status of PLL ready state
 * @retval	`DRIVER_STATUS_READY`: PLL is ready
 * @retval	`DRIVER_STATUS_OFF`: PLL is not ready
 */
__STATIC_FORCEINLINE driver_status_t RCC_LL_GetPLLReadyStatus(void)
{
	uint32_t regImage = 0x00UL;

	RCC_LL_READ_REG(CR, regImage);
	return (((regImage & RCC_CR_PLLRDY) != 0x00UL) ? DRIVER_STATUS_READY : DRIVER_STATUS_OFF);
}

/**
 * @brief	Sets System Clock Source Field
 * @details
 * Programs the `SW` field in `RCC->CFGR.REG` using the supplied raw hardware
 * field value.
 *
 * @param[in] sysClkSrcField	Raw hardware field value for `RCC_CFGR_SW`
 *
 * @returns	@ref driver_status_t Status of system clock source update
 * @retval	`DRIVER_STATUS_SUCCESS`: System clock source field updated successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `sysClkSrcField` is invalid
 */
driver_status_t RCC_LL_SetSystemClockSource(const uint32_t sysClkSrcField);

/**
 * @brief	Gets System Clock Source Field
 * @details
 * Reads the `SW` field from `RCC->CFGR.REG` and stores the raw hardware field
 * value in the supplied output pointer.
 *
 * @param[out] pSysClkSrcField	Pointer to destination variable for `RCC_CFGR_SW` field value
 *
 * @returns	@ref driver_status_t Status of system clock source read
 * @retval	`DRIVER_STATUS_SUCCESS`: System clock source field read successfully
 * @retval	`DRIVER_STATUS_ERROR_NULL_PTR`: `pSysClkSrcField` is `NULL`
 */
driver_status_t RCC_LL_GetSystemClockSource(uint32_t* const pSysClkSrcField);

/**
 * @brief	Gets Active System Clock Status Field
 * @details
 * Reads the `SWS` field from `RCC->CFGR.REG` and stores the raw hardware field
 * value in the supplied output pointer.
 *
 * @param[out] pSysClkStatusField	Pointer to destination variable for `RCC_CFGR_SWS` field value
 *
 * @returns	@ref driver_status_t Status of system clock status read
 * @retval	`DRIVER_STATUS_SUCCESS`: System clock status field read successfully
 * @retval	`DRIVER_STATUS_ERROR_NULL_PTR`: `pSysClkStatusField` is `NULL`
 */
driver_status_t RCC_LL_GetSystemClockStatus(uint32_t* const pSysClkStatusField);

/**
 * @brief	Sets PLL Source Field
 * @details
 * Programs the `PLLSRC` field in `RCC->CFGR.REG` using the supplied raw
 * hardware field value.
 *
 * @param[in] pllSrcField	Raw hardware field value for `RCC_CFGR_PLLSRC`
 *
 * @returns	@ref driver_status_t Status of PLL source field update
 * @retval	`DRIVER_STATUS_SUCCESS`: PLL source field updated successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `pllSrcField` is invalid
 */
driver_status_t RCC_LL_SetPLLSource(const uint32_t pllSrcField);

/**
 * @brief	Gets PLL Source Field
 * @details
 * Reads the `PLLSRC` field from `RCC->CFGR.REG` and stores the raw hardware
 * field value in the supplied output pointer.
 *
 * @param[out] pPllSrcField	Pointer to destination variable for `RCC_CFGR_PLLSRC` field value
 *
 * @returns	@ref driver_status_t Status of PLL source field read
 * @retval	`DRIVER_STATUS_SUCCESS`: PLL source field read successfully
 * @retval	`DRIVER_STATUS_ERROR_NULL_PTR`: `pPllSrcField` is `NULL`
 */
driver_status_t RCC_LL_GetPLLSource(uint32_t* const pPllSrcField);

/**
 * @brief	Sets PLL HSE Divider Field
 * @details
 * Programs the `PLLXTPRE` field in `RCC->CFGR.REG` using the supplied raw
 * hardware field value.
 *
 * @param[in] pllHseDividerField	Raw hardware field value for `RCC_CFGR_PLLXTPRE`
 *
 * @returns	@ref driver_status_t Status of PLL HSE divider field update
 * @retval	`DRIVER_STATUS_SUCCESS`: PLL HSE divider field updated successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `pllHseDividerField` is invalid
 */
driver_status_t RCC_LL_SetPLLHSEDivider(const uint32_t pllHseDividerField);

/**
 * @brief	Gets PLL HSE Divider Field
 * @details
 * Reads the `PLLXTPRE` field from `RCC->CFGR.REG` and stores the raw hardware
 * field value in the supplied output pointer.
 *
 * @param[out] pPllHseDividerField	Pointer to destination variable for `RCC_CFGR_PLLXTPRE` field value
 *
 * @returns	@ref driver_status_t Status of PLL HSE divider field read
 * @retval	`DRIVER_STATUS_SUCCESS`: PLL HSE divider field read successfully
 * @retval	`DRIVER_STATUS_ERROR_NULL_PTR`: `pPllHseDividerField` is `NULL`
 */
driver_status_t RCC_LL_GetPLLHSEDivider(uint32_t* const pPllHseDividerField);

/**
 * @brief	Sets PLL Multiplier Field
 * @details
 * Programs the `PLLMUL` field in `RCC->CFGR.REG` using the supplied raw
 * hardware field value.
 *
 * @param[in] pllMulField	Raw hardware field value for `RCC_CFGR_PLLMUL`
 *
 * @returns	@ref driver_status_t Status of PLL multiplier field update
 * @retval	`DRIVER_STATUS_SUCCESS`: PLL multiplier field updated successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `pllMulField` is invalid
 */
driver_status_t RCC_LL_SetPLLMultiplier(const uint32_t pllMulField);

/**
 * @brief	Gets PLL Multiplier Field
 * @details
 * Reads the `PLLMUL` field from `RCC->CFGR.REG` and stores the raw hardware
 * field value in the supplied output pointer.
 *
 * @param[out] pPllMulField	Pointer to destination variable for `RCC_CFGR_PLLMUL` field value
 *
 * @returns	@ref driver_status_t Status of PLL multiplier field read
 * @retval	`DRIVER_STATUS_SUCCESS`: PLL multiplier field read successfully
 * @retval	`DRIVER_STATUS_ERROR_NULL_PTR`: `pPllMulField` is `NULL`
 */
driver_status_t RCC_LL_GetPLLMultiplier(uint32_t* const pPllMulField);

/** @} */ // RCC_02_LL_02_SystemClock

// ==================================================================================================== //
//                                        RCC LL Prescaler APIs                                         //
// ==================================================================================================== //

/**
 * @brief	RCC LL Prescaler Control
 * @defgroup RCC_02_LL_03_Prescalers RCC LL Prescaler Control
 * @ingroup	RCC_02_LL
 * @details
 * This group owns register-near programming of AHB, APB, ADC, and USB prescaler
 * fields using raw hardware encodings from @ref stm32f1xx_rcc.h.
 * @{
 */

/**
 * @brief	Sets AHB Prescaler Field
 * @details
 * Programs the `HPRE` field in `RCC->CFGR.REG`.
 *
 * @param[in] ahbPrescalerField	Raw hardware field value for `RCC_CFGR_HPRE`
 *
 * @returns	@ref driver_status_t Status of AHB prescaler field update
 * @retval	`DRIVER_STATUS_SUCCESS`: AHB prescaler field updated successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `ahbPrescalerField` is invalid
 */
driver_status_t RCC_LL_SetAHBPrescaler(const uint32_t ahbPrescalerField);

/**
 * @brief	Gets AHB Prescaler Field
 * @details
 * Reads the `HPRE` field from `RCC->CFGR.REG`.
 *
 * @param[out] pAhbPrescalerField	Pointer to destination variable for `RCC_CFGR_HPRE` field value
 *
 * @returns	@ref driver_status_t Status of AHB prescaler field read
 * @retval	`DRIVER_STATUS_SUCCESS`: AHB prescaler field read successfully
 * @retval	`DRIVER_STATUS_ERROR_NULL_PTR`: `pAhbPrescalerField` is `NULL`
 */
driver_status_t RCC_LL_GetAHBPrescaler(uint32_t* const pAhbPrescalerField);

/**
 * @brief	Sets APB1 Prescaler Field
 * @details
 * Programs the `PPRE1` field in `RCC->CFGR.REG`.
 *
 * @param[in] apb1PrescalerField	Raw hardware field value for `RCC_CFGR_PPRE1`
 *
 * @returns	@ref driver_status_t Status of APB1 prescaler field update
 * @retval	`DRIVER_STATUS_SUCCESS`: APB1 prescaler field updated successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `apb1PrescalerField` is invalid
 */
driver_status_t RCC_LL_SetAPB1Prescaler(const uint32_t apb1PrescalerField);

/**
 * @brief	Gets APB1 Prescaler Field
 * @details
 * Reads the `PPRE1` field from `RCC->CFGR.REG`.
 *
 * @param[out] pApb1PrescalerField	Pointer to destination variable for `RCC_CFGR_PPRE1` field value
 *
 * @returns	@ref driver_status_t Status of APB1 prescaler field read
 * @retval	`DRIVER_STATUS_SUCCESS`: APB1 prescaler field read successfully
 * @retval	`DRIVER_STATUS_ERROR_NULL_PTR`: `pApb1PrescalerField` is `NULL`
 */
driver_status_t RCC_LL_GetAPB1Prescaler(uint32_t* const pApb1PrescalerField);

/**
 * @brief	Sets APB2 Prescaler Field
 * @details
 * Programs the `PPRE2` field in `RCC->CFGR.REG`.
 *
 * @param[in] apb2PrescalerField	Raw hardware field value for `RCC_CFGR_PPRE2`
 *
 * @returns	@ref driver_status_t Status of APB2 prescaler field update
 * @retval	`DRIVER_STATUS_SUCCESS`: APB2 prescaler field updated successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `apb2PrescalerField` is invalid
 */
driver_status_t RCC_LL_SetAPB2Prescaler(const uint32_t apb2PrescalerField);

/**
 * @brief	Gets APB2 Prescaler Field
 * @details
 * Reads the `PPRE2` field from `RCC->CFGR.REG`.
 *
 * @param[out] pApb2PrescalerField	Pointer to destination variable for `RCC_CFGR_PPRE2` field value
 *
 * @returns	@ref driver_status_t Status of APB2 prescaler field read
 * @retval	`DRIVER_STATUS_SUCCESS`: APB2 prescaler field read successfully
 * @retval	`DRIVER_STATUS_ERROR_NULL_PTR`: `pApb2PrescalerField` is `NULL`
 */
driver_status_t RCC_LL_GetAPB2Prescaler(uint32_t* const pApb2PrescalerField);

/**
 * @brief	Sets ADC Prescaler Field
 * @details
 * Programs the `ADCPRE` field in `RCC->CFGR.REG`.
 *
 * @param[in] adcPrescalerField	Raw hardware field value for `RCC_CFGR_ADCPRE`
 *
 * @returns	@ref driver_status_t Status of ADC prescaler field update
 * @retval	`DRIVER_STATUS_SUCCESS`: ADC prescaler field updated successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `adcPrescalerField` is invalid
 */
driver_status_t RCC_LL_SetADCPrescaler(const uint32_t adcPrescalerField);

/**
 * @brief	Gets ADC Prescaler Field
 * @details
 * Reads the `ADCPRE` field from `RCC->CFGR.REG`.
 *
 * @param[out] pAdcPrescalerField	Pointer to destination variable for `RCC_CFGR_ADCPRE` field value
 *
 * @returns	@ref driver_status_t Status of ADC prescaler field read
 * @retval	`DRIVER_STATUS_SUCCESS`: ADC prescaler field read successfully
 * @retval	`DRIVER_STATUS_ERROR_NULL_PTR`: `pAdcPrescalerField` is `NULL`
 */
driver_status_t RCC_LL_GetADCPrescaler(uint32_t* const pAdcPrescalerField);

/**
 * @brief	Sets USB Prescaler Field
 * @details
 * Programs the `USBPRE` field in `RCC->CFGR.REG`.
 *
 * @param[in] usbPrescalerField	Raw hardware field value for `RCC_CFGR_USBPRE`
 *
 * @returns	@ref driver_status_t Status of USB prescaler field update
 * @retval	`DRIVER_STATUS_SUCCESS`: USB prescaler field updated successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `usbPrescalerField` is invalid
 */
driver_status_t RCC_LL_SetUSBPrescaler(const uint32_t usbPrescalerField);

/**
 * @brief	Gets USB Prescaler Field
 * @details
 * Reads the `USBPRE` field from `RCC->CFGR.REG`.
 *
 * @param[out] pUsbPrescalerField	Pointer to destination variable for `RCC_CFGR_USBPRE` field value
 *
 * @returns	@ref driver_status_t Status of USB prescaler field read
 * @retval	`DRIVER_STATUS_SUCCESS`: USB prescaler field read successfully
 * @retval	`DRIVER_STATUS_ERROR_NULL_PTR`: `pUsbPrescalerField` is `NULL`
 */
driver_status_t RCC_LL_GetUSBPrescaler(uint32_t* const pUsbPrescalerField);

/** @} */ // RCC_02_LL_03_Prescalers

// ==================================================================================================== //
//                                     RCC LL Clock Gate and Reset                                      //
// ==================================================================================================== //

/**
 * @brief	RCC LL Clock Gate and Reset Control
 * @defgroup RCC_02_LL_04_ClockReset RCC LL Clock Gate and Reset Control
 * @ingroup	RCC_02_LL
 * @{
 */

/**
 * @brief	Enables AHB Peripheral Clock
 * @details
 * Sets the requested enable bits in `RCC->AHBENR.REG`.
 *
 * @param[in] mask	Raw hardware bit mask for AHB peripheral clock enable
 *
 * @returns	@ref driver_status_t Status of AHB clock enable operation
 * @retval	`DRIVER_STATUS_SUCCESS`: AHB peripheral clock enabled successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t RCC_LL_EnableAHBClock(const uint32_t mask);

/**
 * @brief	Disables AHB Peripheral Clock
 * @details
 * Clears the requested enable bits in `RCC->AHBENR.REG`.
 *
 * @param[in] mask	Raw hardware bit mask for AHB peripheral clock disable
 *
 * @returns	@ref driver_status_t Status of AHB clock disable operation
 * @retval	`DRIVER_STATUS_SUCCESS`: AHB peripheral clock disabled successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t RCC_LL_DisableAHBClock(const uint32_t mask);

/**
 * @brief	Enables APB2 Peripheral Clock
 * @details
 * Sets the requested enable bits in `RCC->APB2ENR.REG`.
 *
 * @param[in] mask	Raw hardware bit mask for APB2 peripheral clock enable
 *
 * @returns	@ref driver_status_t Status of APB2 clock enable operation
 * @retval	`DRIVER_STATUS_SUCCESS`: APB2 peripheral clock enabled successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t RCC_LL_EnableAPB2Clock(const uint32_t mask);

/**
 * @brief	Disables APB2 Peripheral Clock
 * @details
 * Clears the requested enable bits in `RCC->APB2ENR.REG`.
 *
 * @param[in] mask	Raw hardware bit mask for APB2 peripheral clock disable
 *
 * @returns	@ref driver_status_t Status of APB2 clock disable operation
 * @retval	`DRIVER_STATUS_SUCCESS`: APB2 peripheral clock disabled successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t RCC_LL_DisableAPB2Clock(const uint32_t mask);

/**
 * @brief	Enables APB1 Peripheral Clock
 * @details
 * Sets the requested enable bits in `RCC->APB1ENR.REG`.
 *
 * @param[in] mask	Raw hardware bit mask for APB1 peripheral clock enable
 *
 * @returns	@ref driver_status_t Status of APB1 clock enable operation
 * @retval	`DRIVER_STATUS_SUCCESS`: APB1 peripheral clock enabled successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t RCC_LL_EnableAPB1Clock(const uint32_t mask);

/**
 * @brief	Disables APB1 Peripheral Clock
 * @details
 * Clears the requested enable bits in `RCC->APB1ENR.REG`.
 *
 * @param[in] mask	Raw hardware bit mask for APB1 peripheral clock disable
 *
 * @returns	@ref driver_status_t Status of APB1 clock disable operation
 * @retval	`DRIVER_STATUS_SUCCESS`: APB1 peripheral clock disabled successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t RCC_LL_DisableAPB1Clock(const uint32_t mask);

/**
 * @brief	Forces APB2 Peripheral Reset
 * @details
 * Sets the requested reset bits in `RCC->APB2RSTR.REG`.
 *
 * @param[in] mask	Raw hardware bit mask for APB2 peripheral reset
 *
 * @returns	@ref driver_status_t Status of APB2 reset force operation
 * @retval	`DRIVER_STATUS_SUCCESS`: APB2 reset asserted successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t RCC_LL_ForceAPB2Reset(const uint32_t mask);

/**
 * @brief	Releases APB2 Peripheral Reset
 * @details
 * Clears the requested reset bits in `RCC->APB2RSTR.REG`.
 *
 * @param[in] mask	Raw hardware bit mask for APB2 peripheral reset release
 *
 * @returns	@ref driver_status_t Status of APB2 reset release operation
 * @retval	`DRIVER_STATUS_SUCCESS`: APB2 reset released successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t RCC_LL_ReleaseAPB2Reset(const uint32_t mask);

/**
 * @brief	Forces APB1 Peripheral Reset
 * @details
 * Sets the requested reset bits in `RCC->APB1RSTR.REG`.
 *
 * @param[in] mask	Raw hardware bit mask for APB1 peripheral reset
 *
 * @returns	@ref driver_status_t Status of APB1 reset force operation
 * @retval	`DRIVER_STATUS_SUCCESS`: APB1 reset asserted successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t RCC_LL_ForceAPB1Reset(const uint32_t mask);

/**
 * @brief	Releases APB1 Peripheral Reset
 * @details
 * Clears the requested reset bits in `RCC->APB1RSTR.REG`.
 *
 * @param[in] mask	Raw hardware bit mask for APB1 peripheral reset release
 *
 * @returns	@ref driver_status_t Status of APB1 reset release operation
 * @retval	`DRIVER_STATUS_SUCCESS`: APB1 reset released successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t RCC_LL_ReleaseAPB1Reset(const uint32_t mask);

/**
 * @brief	Pulses APB2 Peripheral Reset
 * @details
 * Asserts and then releases the requested APB2 reset bits.
 *
 * @param[in] mask	Raw hardware bit mask for APB2 peripheral reset pulse
 *
 * @returns	@ref driver_status_t Status of APB2 reset pulse operation
 * @retval	`DRIVER_STATUS_SUCCESS`: APB2 reset pulsed successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t RCC_LL_PulseAPB2Reset(const uint32_t mask);

/**
 * @brief	Pulses APB1 Peripheral Reset
 * @details
 * Asserts and then releases the requested APB1 reset bits.
 *
 * @param[in] mask	Raw hardware bit mask for APB1 peripheral reset pulse
 *
 * @returns	@ref driver_status_t Status of APB1 reset pulse operation
 * @retval	`DRIVER_STATUS_SUCCESS`: APB1 reset pulsed successfully
 * @retval	`DRIVER_STATUS_ERROR_INVALID_ARG`: `mask` is invalid
 */
driver_status_t RCC_LL_PulseAPB1Reset(const uint32_t mask);

/** @} */ // RCC_02_LL_04_ClockReset

/** @} */ // RCC_02_LL

// C++ Compatibility
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_LL_H_ */
