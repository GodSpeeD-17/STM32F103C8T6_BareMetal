/**
 * @file	rcc_ll.h
 * @author	Shrey Shah
 * @brief	RCC Low-Level Register Access Layer
 * @version	v2.4
 * @date	20-03-2026
 *
 * @details
 * This header exposes the **Low-Level (LL)** RCC interface for direct hardware register
 * read/modify/write operations. The LL layer owns register-near primitives, while the driver
 * layer in `rcc.h` owns orchestration, validation policy, clock-tree workflows, and presets.
 *
 * The LL module is intentionally split into:
 * - Generic RCC register utility macros.
 * - RCC LL data types that mirror hardware field encodings.
 * - RCC LL functions for source control, prescalers, clock gating, and reset control.
 * - Compatibility aliases retained for existing LL users such as GPIO and I2C.
 */

// Header Guards
#ifndef RCC_LL_H_
#define RCC_LL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*---------------------------------------------- Includes ----------------------------------------------*/
#include "stm32f1xx.h"

/**
 * @addtogroup RCC_02_LL
 * @{
 */

/*---------------------------------------------- Generic RCC LL Register Macros ----------------------------------------------*/
/**
 * @brief	RCC Generic Register Access Macros
 * @defgroup RCC_02_LL_01_RegOps RCC LL Register Operation Macros
 * @ingroup	RCC_02_LL
 * @details
 * - These macros directly reuse the generic `REGOPS_*` helpers from the core utility layer.
 * - They operate on the `.REG` field of each RCC register union.
 * - They are intended for use by the RCC LL implementation and other low-level code paths.
 * @{
 */

/**
 * @brief	Retrieves pointer to an RCC register `.REG` field
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @returns	Pointer to the 32-bit register storage
 * @def		RCC_LL_REG
 */
#define RCC_LL_REG(_RCC_, _REG_)							(&((_RCC_)->_REG_.REG))

/**
 * @brief	Reads an RCC register through the generic register utility layer
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @param[out] _VAR_	Destination variable that receives the register image
 * @def		RCC_LL_READ
 */
#define RCC_LL_READ(_RCC_, _REG_, _VAR_)					REGOPS_READ(RCC_LL_REG((_RCC_), _REG_), (_VAR_))

/**
 * @brief	Writes an RCC register through the generic register utility layer
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @param[in] _VAL_	32-bit value to be written
 * @def		RCC_LL_WRITE
 */
#define RCC_LL_WRITE(_RCC_, _REG_, _VAL_)					REGOPS_WRITE(RCC_LL_REG((_RCC_), _REG_), (_VAL_))

/**
 * @brief	Sets masked bits in an RCC register
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @param[in] _MASK_	Bit-mask to be ORed into the target register
 * @def		RCC_LL_SET
 */
#define RCC_LL_SET(_RCC_, _REG_, _MASK_)					REGOPS_SET(RCC_LL_REG((_RCC_), _REG_), (_MASK_))

/**
 * @brief	Clears masked bits in an RCC register
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @param[in] _MASK_	Bit-mask to be cleared from the target register
 * @def		RCC_LL_CLEAR
 */
#define RCC_LL_CLEAR(_RCC_, _REG_, _MASK_)					REGOPS_CLEAR(RCC_LL_REG((_RCC_), _REG_), (_MASK_))

/**
 * @brief	Toggles masked bits in an RCC register
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @param[in] _MASK_	Bit-mask to be toggled in the target register
 * @def		RCC_LL_TOGGLE
 */
#define RCC_LL_TOGGLE(_RCC_, _REG_, _MASK_)					REGOPS_TOGGLE(RCC_LL_REG((_RCC_), _REG_), (_MASK_))

/**
 * @brief	Performs a masked register-field modification
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @param[in] _MASK_	Field mask to clear before update
 * @param[in] _VAL_	Pre-shifted field value to be merged into the register
 * @def		RCC_LL_MODIFY
 */
#define RCC_LL_MODIFY(_RCC_, _REG_, _MASK_, _VAL_)			REGOPS_MODIFY(RCC_LL_REG((_RCC_), _REG_), (_MASK_), (_VAL_))

/**
 * @brief	Prepares a field value for masked register insertion
 * @param[in] _VAL_	Raw unshifted field value
 * @param[in] _MASK_	Target field mask
 * @param[in] _POS_	Target field position
 * @returns	Shifted and masked field value
 * @def		RCC_LL_FIELD_PREP
 */
#define RCC_LL_FIELD_PREP(_VAL_, _MASK_, _POS_)				((((uint32_t)(_VAL_)) << (_POS_)) & (_MASK_))

/**
 * @brief	Extracts a right-aligned field value from a register image
 * @param[in] _REG_	Register image
 * @param[in] _MASK_	Target field mask
 * @param[in] _POS_	Target field position
 * @returns	Right-aligned field value
 * @def		RCC_LL_FIELD_GET
 */
#define RCC_LL_FIELD_GET(_REG_, _MASK_, _POS_)				((((uint32_t)(_REG_)) & (_MASK_)) >> (_POS_))

/** @} */ // RCC_02_LL_01_RegOps

/*---------------------------------------------- RCC LL Data Types ----------------------------------------------*/
/**
 * @brief	RCC LL Field Data Types and Encoded Values
 * @defgroup RCC_02_LL_02_Types RCC LL Field Types and Macros
 * @ingroup	RCC_02_LL
 * @details
 * - These values intentionally mirror the hardware field encodings.
 * - They are used directly by the LL functions to avoid unnecessary translation inside the LL layer.
 * - Each exposed macro in this section is part of the LL contract and documented individually.
 * @{
 */

/*---------------------------------------------- LL System Clock Source ----------------------------------------------*/
/**
 * @brief	LL system clock source request field type
 * @typedef	rcc_ll_sysclk_src_t
 */
typedef uint32_t											rcc_ll_sysclk_src_t;
/** @brief HSI selected as requested system clock source @def RCC_LL_SYSCLK_SRC_HSI */
#define RCC_LL_SYSCLK_SRC_HSI								(RCC_CFGR_SW_HSI)
/** @brief HSE selected as requested system clock source @def RCC_LL_SYSCLK_SRC_HSE */
#define RCC_LL_SYSCLK_SRC_HSE								(RCC_CFGR_SW_HSE)
/** @brief PLL selected as requested system clock source @def RCC_LL_SYSCLK_SRC_PLL */
#define RCC_LL_SYSCLK_SRC_PLL								(RCC_CFGR_SW_PLL)

/*---------------------------------------------- LL System Clock Status ----------------------------------------------*/
/**
 * @brief	LL system clock status field type
 * @typedef	rcc_ll_sysclk_status_t
 */
typedef uint32_t											rcc_ll_sysclk_status_t;
/** @brief HSI is currently driving SYSCLK @def RCC_LL_SYSCLK_STATUS_HSI */
#define RCC_LL_SYSCLK_STATUS_HSI							(RCC_CFGR_SWS_HSI)
/** @brief HSE is currently driving SYSCLK @def RCC_LL_SYSCLK_STATUS_HSE */
#define RCC_LL_SYSCLK_STATUS_HSE							(RCC_CFGR_SWS_HSE)
/** @brief PLL is currently driving SYSCLK @def RCC_LL_SYSCLK_STATUS_PLL */
#define RCC_LL_SYSCLK_STATUS_PLL							(RCC_CFGR_SWS_PLL)

/*---------------------------------------------- LL PLL Source ----------------------------------------------*/
/**
 * @brief	LL PLL source field type
 * @typedef	rcc_ll_pll_src_t
 */
typedef uint32_t											rcc_ll_pll_src_t;
/** @brief HSI divided by 2 selected as PLL input @def RCC_LL_PLL_SRC_HSI_DIV2 */
#define RCC_LL_PLL_SRC_HSI_DIV2								(RCC_CFGR_PLLSRC_HSI_DIV2)
/** @brief HSE selected as PLL input @def RCC_LL_PLL_SRC_HSE */
#define RCC_LL_PLL_SRC_HSE									(RCC_CFGR_PLLSRC_HSE)

/*---------------------------------------------- LL PLL HSE Divider ----------------------------------------------*/
/**
 * @brief	LL PLL HSE divider field type
 * @typedef	rcc_ll_pll_hse_div_t
 */
typedef uint32_t											rcc_ll_pll_hse_div_t;
/** @brief HSE divided by 1 before PLL input @def RCC_LL_PLL_HSE_DIV_1 */
#define RCC_LL_PLL_HSE_DIV_1								(RCC_CFGR_PLLXTPRE_HSE)
/** @brief HSE divided by 2 before PLL input @def RCC_LL_PLL_HSE_DIV_2 */
#define RCC_LL_PLL_HSE_DIV_2								(RCC_CFGR_PLLXTPRE_HSE_DIV2)

/*---------------------------------------------- LL PLL Multiplier ----------------------------------------------*/
/**
 * @brief	LL PLL multiplication field type
 * @typedef	rcc_ll_pll_mul_t
 */
typedef uint32_t									rcc_ll_pll_mul_t;
/** @brief PLL input clock multiplied by 2 @def RCC_LL_PLL_MUL_2 */
#define RCC_LL_PLL_MUL_2							(RCC_CFGR_PLLMUL_2)
/** @brief PLL input clock multiplied by 3 @def RCC_LL_PLL_MUL_3 */
#define RCC_LL_PLL_MUL_3							(RCC_CFGR_PLLMUL_3)
/** @brief PLL input clock multiplied by 4 @def RCC_LL_PLL_MUL_4 */
#define RCC_LL_PLL_MUL_4							(RCC_CFGR_PLLMUL_4)
/** @brief PLL input clock multiplied by 5 @def RCC_LL_PLL_MUL_5 */
#define RCC_LL_PLL_MUL_5							(RCC_CFGR_PLLMUL_5)
/** @brief PLL input clock multiplied by 6 @def RCC_LL_PLL_MUL_6 */
#define RCC_LL_PLL_MUL_6							(RCC_CFGR_PLLMUL_6)
/** @brief PLL input clock multiplied by 7 @def RCC_LL_PLL_MUL_7 */
#define RCC_LL_PLL_MUL_7							(RCC_CFGR_PLLMUL_7)
/** @brief PLL input clock multiplied by 8 @def RCC_LL_PLL_MUL_8 */
#define RCC_LL_PLL_MUL_8							(RCC_CFGR_PLLMUL_8)
/** @brief PLL input clock multiplied by 9 @def RCC_LL_PLL_MUL_9 */
#define RCC_LL_PLL_MUL_9							(RCC_CFGR_PLLMUL_9)
/** @brief PLL input clock multiplied by 10 @def RCC_LL_PLL_MUL_10 */
#define RCC_LL_PLL_MUL_10							(RCC_CFGR_PLLMUL_10)
/** @brief PLL input clock multiplied by 11 @def RCC_LL_PLL_MUL_11 */
#define RCC_LL_PLL_MUL_11							(RCC_CFGR_PLLMUL_11)
/** @brief PLL input clock multiplied by 12 @def RCC_LL_PLL_MUL_12 */
#define RCC_LL_PLL_MUL_12							(RCC_CFGR_PLLMUL_12)
/** @brief PLL input clock multiplied by 13 @def RCC_LL_PLL_MUL_13 */
#define RCC_LL_PLL_MUL_13							(RCC_CFGR_PLLMUL_13)
/** @brief PLL input clock multiplied by 14 @def RCC_LL_PLL_MUL_14 */
#define RCC_LL_PLL_MUL_14							(RCC_CFGR_PLLMUL_14)
/** @brief PLL input clock multiplied by 15 @def RCC_LL_PLL_MUL_15 */
#define RCC_LL_PLL_MUL_15							(RCC_CFGR_PLLMUL_15)
/** @brief PLL input clock multiplied by 16 @def RCC_LL_PLL_MUL_16 */
#define RCC_LL_PLL_MUL_16							(RCC_CFGR_PLLMUL_16)

/*---------------------------------------------- LL AHB Prescaler ----------------------------------------------*/
/**
 * @brief	LL AHB prescaler field type
 * @typedef	rcc_ll_ahb_prescaler_t
 */
typedef uint32_t									rcc_ll_ahb_prescaler_t;
/** @brief AHB clock not divided @def RCC_LL_AHB_DIV_1 */
#define RCC_LL_AHB_DIV_1							(RCC_CFGR_HPRE_DIV1)
/** @brief AHB clock divided by 2 @def RCC_LL_AHB_DIV_2 */
#define RCC_LL_AHB_DIV_2							(RCC_CFGR_HPRE_DIV2)
/** @brief AHB clock divided by 4 @def RCC_LL_AHB_DIV_4 */
#define RCC_LL_AHB_DIV_4							(RCC_CFGR_HPRE_DIV4)
/** @brief AHB clock divided by 8 @def RCC_LL_AHB_DIV_8 */
#define RCC_LL_AHB_DIV_8							(RCC_CFGR_HPRE_DIV8)
/** @brief AHB clock divided by 16 @def RCC_LL_AHB_DIV_16 */
#define RCC_LL_AHB_DIV_16							(RCC_CFGR_HPRE_DIV16)
/** @brief AHB clock divided by 64 @def RCC_LL_AHB_DIV_64 */
#define RCC_LL_AHB_DIV_64							(RCC_CFGR_HPRE_DIV64)
/** @brief AHB clock divided by 128 @def RCC_LL_AHB_DIV_128 */
#define RCC_LL_AHB_DIV_128							(RCC_CFGR_HPRE_DIV128)
/** @brief AHB clock divided by 256 @def RCC_LL_AHB_DIV_256 */
#define RCC_LL_AHB_DIV_256							(RCC_CFGR_HPRE_DIV256)
/** @brief AHB clock divided by 512 @def RCC_LL_AHB_DIV_512 */
#define RCC_LL_AHB_DIV_512							(RCC_CFGR_HPRE_DIV512)

/*---------------------------------------------- LL APB Prescaler ----------------------------------------------*/
/**
 * @brief	LL APB prescaler field type
 * @typedef	rcc_ll_apb_prescaler_t
 */
typedef uint32_t									rcc_ll_apb_prescaler_t;
/** @brief APB clock not divided @def RCC_LL_APB_DIV_1 */
#define RCC_LL_APB_DIV_1							(RCC_CFGR_PPRE1_DIV1)
/** @brief APB clock divided by 2 @def RCC_LL_APB_DIV_2 */
#define RCC_LL_APB_DIV_2							(RCC_CFGR_PPRE1_DIV2)
/** @brief APB clock divided by 4 @def RCC_LL_APB_DIV_4 */
#define RCC_LL_APB_DIV_4							(RCC_CFGR_PPRE1_DIV4)
/** @brief APB clock divided by 8 @def RCC_LL_APB_DIV_8 */
#define RCC_LL_APB_DIV_8							(RCC_CFGR_PPRE1_DIV8)
/** @brief APB clock divided by 16 @def RCC_LL_APB_DIV_16 */
#define RCC_LL_APB_DIV_16							(RCC_CFGR_PPRE1_DIV16)

/*---------------------------------------------- LL ADC Prescaler ----------------------------------------------*/
/**
 * @brief	LL ADC prescaler field type
 * @typedef	rcc_ll_adc_prescaler_t
 */
typedef uint32_t									rcc_ll_adc_prescaler_t;
/** @brief ADC clock derived from PCLK2 divided by 2 @def RCC_LL_ADC_DIV_2 */
#define RCC_LL_ADC_DIV_2							(RCC_CFGR_ADCPRE_DIV2)
/** @brief ADC clock derived from PCLK2 divided by 4 @def RCC_LL_ADC_DIV_4 */
#define RCC_LL_ADC_DIV_4							(RCC_CFGR_ADCPRE_DIV4)
/** @brief ADC clock derived from PCLK2 divided by 6 @def RCC_LL_ADC_DIV_6 */
#define RCC_LL_ADC_DIV_6							(RCC_CFGR_ADCPRE_DIV6)
/** @brief ADC clock derived from PCLK2 divided by 8 @def RCC_LL_ADC_DIV_8 */
#define RCC_LL_ADC_DIV_8							(RCC_CFGR_ADCPRE_DIV8)

/*---------------------------------------------- LL USB Prescaler ----------------------------------------------*/
/**
 * @brief	LL USB prescaler field type
 * @typedef	rcc_ll_usb_prescaler_t
 */
typedef uint32_t								rcc_ll_usb_prescaler_t;

/** @brief PLL clock divided by 1.5 for USB clock generation @def RCC_LL_USB_DIV_1_5 */
#define RCC_LL_USB_DIV_1_5							(RCC_CFGR_USBPRE_DIV1_5)
/** @brief PLL clock used directly for USB clock generation @def RCC_LL_USB_DIV_1 */
#define RCC_LL_USB_DIV_1							(RCC_CFGR_USBPRE_DIRECT)

/** @} */ // RCC_02_LL_02_Types

/*---------------------------------------------- RCC LL Compatibility Macros ----------------------------------------------*/
/**
 * @brief	RCC Legacy Compatibility Macros
 * @defgroup RCC_02_LL_03_RegAccess RCC LL Compatibility Helpers
 * @ingroup	RCC_02_LL
 * @details
 * - These aliases are retained for LL modules that still call the historic `__RCC_*` helpers.
 * - They are thin compatibility shims over the generic @ref RCC_02_LL_01_RegOps macros.
 * - New RCC code should prefer the functional LL API or the generic `RCC_LL_*` macros directly.
 * @{
 */

/** @brief Reads @ref RCC_CR "RCC->CR" @def __RCC_ReadCR */
#define __RCC_ReadCR(_RCC_)									(*RCC_LL_REG((_RCC_), CR))
/** @brief Writes @ref RCC_CR "RCC->CR" @def __RCC_WriteCR */
#define __RCC_WriteCR(_RCC_, _VAL_)							RCC_LL_WRITE((_RCC_), CR, (_VAL_))
/** @brief Sets masked bits in @ref RCC_CR "RCC->CR" @def __RCC_SetCR */
#define __RCC_SetCR(_RCC_, _MASK_)							RCC_LL_SET((_RCC_), CR, (_MASK_))
/** @brief Clears masked bits in @ref RCC_CR "RCC->CR" @def __RCC_ClearCR */
#define __RCC_ClearCR(_RCC_, _MASK_)						RCC_LL_CLEAR((_RCC_), CR, (_MASK_))

/** @brief Reads @ref RCC_CFGR "RCC->CFGR" @def __RCC_ReadCFGR */
#define __RCC_ReadCFGR(_RCC_)								(*RCC_LL_REG((_RCC_), CFGR))
/** @brief Writes @ref RCC_CFGR "RCC->CFGR" @def __RCC_WriteCFGR */
#define __RCC_WriteCFGR(_RCC_, _VAL_)						RCC_LL_WRITE((_RCC_), CFGR, (_VAL_))
/** @brief Sets masked bits in @ref RCC_CFGR "RCC->CFGR" @def __RCC_SetCFGR */
#define __RCC_SetCFGR(_RCC_, _MASK_)						RCC_LL_SET((_RCC_), CFGR, (_MASK_))
/** @brief Clears masked bits in @ref RCC_CFGR "RCC->CFGR" @def __RCC_ClearCFGR */
#define __RCC_ClearCFGR(_RCC_, _MASK_)						RCC_LL_CLEAR((_RCC_), CFGR, (_MASK_))

/** @brief Sets bits in @ref RCC_AHBENR "RCC->AHBENR" @def __RCC_SetAHBENR */
#define __RCC_SetAHBENR(_RCC_, _MASK_)						RCC_LL_SET((_RCC_), AHBENR, (_MASK_))
/** @brief Clears bits in @ref RCC_AHBENR "RCC->AHBENR" @def __RCC_ClearAHBENR */
#define __RCC_ClearAHBENR(_RCC_, _MASK_)					RCC_LL_CLEAR((_RCC_), AHBENR, (_MASK_))
/** @brief Sets bits in @ref RCC_APB2ENR "RCC->APB2ENR" @def __RCC_SetAPB2ENR */
#define __RCC_SetAPB2ENR(_RCC_, _MASK_)						RCC_LL_SET((_RCC_), APB2ENR, (_MASK_))
/** @brief Clears bits in @ref RCC_APB2ENR "RCC->APB2ENR" @def __RCC_ClearAPB2ENR */
#define __RCC_ClearAPB2ENR(_RCC_, _MASK_)					RCC_LL_CLEAR((_RCC_), APB2ENR, (_MASK_))
/** @brief Sets bits in @ref RCC_APB1ENR "RCC->APB1ENR" @def __RCC_SetAPB1ENR */
#define __RCC_SetAPB1ENR(_RCC_, _MASK_)						RCC_LL_SET((_RCC_), APB1ENR, (_MASK_))
/** @brief Clears bits in @ref RCC_APB1ENR "RCC->APB1ENR" @def __RCC_ClearAPB1ENR */
#define __RCC_ClearAPB1ENR(_RCC_, _MASK_)					RCC_LL_CLEAR((_RCC_), APB1ENR, (_MASK_))

/** @brief Sets bits in @ref RCC_APB2RSTR "RCC->APB2RSTR" @def __RCC_SetAPB2RSTR */
#define __RCC_SetAPB2RSTR(_RCC_, _MASK_)					RCC_LL_SET((_RCC_), APB2RSTR, (_MASK_))
/** @brief Clears bits in @ref RCC_APB2RSTR "RCC->APB2RSTR" @def __RCC_ClearAPB2RSTR */
#define __RCC_ClearAPB2RSTR(_RCC_, _MASK_)					RCC_LL_CLEAR((_RCC_), APB2RSTR, (_MASK_))
/** @brief Sets bits in @ref RCC_APB1RSTR "RCC->APB1RSTR" @def __RCC_SetAPB1RSTR */
#define __RCC_SetAPB1RSTR(_RCC_, _MASK_)					RCC_LL_SET((_RCC_), APB1RSTR, (_MASK_))
/** @brief Clears bits in @ref RCC_APB1RSTR "RCC->APB1RSTR" @def __RCC_ClearAPB1RSTR */
#define __RCC_ClearAPB1RSTR(_RCC_, _MASK_)					RCC_LL_CLEAR((_RCC_), APB1RSTR, (_MASK_))

/** @} */ // RCC_02_LL_03_RegAccess

/*---------------------------------------------- RCC LL Functional APIs ----------------------------------------------*/
/**
 * @brief	RCC LL Functional APIs
 * @defgroup RCC_02_LL_04_API RCC LL Functional APIs
 * @ingroup	RCC_02_LL
 * @{
 */

/*---------------------------------------------- RCC LL Clock Source Control ----------------------------------------------*/
/**
 * @brief	RCC LL Clock Source Control APIs
 * @defgroup RCC_02_LL_04_API_01_SourceControl RCC LL Clock Source Control
 * @ingroup	RCC_02_LL_04_API
 * @{
 */

/**
 * @brief	Enables the internal high-speed oscillator
 */
__STATIC_FORCEINLINE void RCC_LL_HSI_Enable(void)
{
	RCC_LL_SET(RCC, CR, RCC_CR_HSION);
}

/**
 * @brief	Disables the internal high-speed oscillator
 */
__STATIC_FORCEINLINE void RCC_LL_HSI_Disable(void)
{
	RCC_LL_CLEAR(RCC, CR, RCC_CR_HSION);
}

/**
 * @brief	Retrieves the internal high-speed oscillator ready state
 * @returns - @ref driver_status_t HSI ready-state status
 * @retval - @ref `DRIVER_STATUS_READY`: HSI ready flag is set.
 * @retval - @ref `DRIVER_STATUS_OFF`: HSI ready flag is cleared.
 */
__STATIC_FORCEINLINE driver_status_t RCC_LL_HSI_GetReadyStatus(void)
{
	if ((RCC->CR.REG & RCC_CR_HSIRDY) != 0x00UL)
	{
		return DRIVER_STATUS_READY;
	}
	else
	{
		return DRIVER_STATUS_OFF;
	}
}

/**
 * @brief	Enables the external high-speed oscillator
 */
__STATIC_FORCEINLINE void RCC_LL_HSE_Enable(void)
{
	RCC_LL_SET(RCC, CR, RCC_CR_HSEON);
}

/**
 * @brief	Disables the external high-speed oscillator
 */
__STATIC_FORCEINLINE void RCC_LL_HSE_Disable(void)
{
	RCC_LL_CLEAR(RCC, CR, RCC_CR_HSEON);
}

/**
 * @brief	Enables HSE bypass mode
 */
__STATIC_FORCEINLINE void RCC_LL_HSE_BypassEnable(void)
{
	RCC_LL_SET(RCC, CR, RCC_CR_HSEBYP);
}

/**
 * @brief	Disables HSE bypass mode
 */
__STATIC_FORCEINLINE void RCC_LL_HSE_BypassDisable(void)
{
	RCC_LL_CLEAR(RCC, CR, RCC_CR_HSEBYP);
}

/**
 * @brief	Retrieves the external high-speed oscillator ready state
 * @returns - @ref driver_status_t HSE ready-state status
 * @retval - @ref `DRIVER_STATUS_READY`: HSE ready flag is set.
 * @retval - @ref `DRIVER_STATUS_OFF`: HSE ready flag is cleared.
 */
__STATIC_FORCEINLINE driver_status_t RCC_LL_HSE_GetReadyStatus(void)
{
	if ((RCC->CR.REG & RCC_CR_HSERDY) != 0x00UL)
	{
		return DRIVER_STATUS_READY;
	}
	else
	{
		return DRIVER_STATUS_OFF;
	}
}

/**
 * @brief	Enables the PLL
 */
__STATIC_FORCEINLINE void RCC_LL_PLL_Enable(void)
{
	RCC_LL_SET(RCC, CR, RCC_CR_PLLON);
}

/**
 * @brief	Disables the PLL
 */
__STATIC_FORCEINLINE void RCC_LL_PLL_Disable(void)
{
	RCC_LL_CLEAR(RCC, CR, RCC_CR_PLLON);
}

/**
 * @brief	Retrieves the PLL ready state
 * @returns - @ref driver_status_t PLL ready-state status
 * @retval - @ref `DRIVER_STATUS_READY`: PLL ready flag is set.
 * @retval - @ref `DRIVER_STATUS_OFF`: PLL ready flag is cleared.
 */
__STATIC_FORCEINLINE driver_status_t RCC_LL_PLL_GetReadyStatus(void)
{
	if ((RCC->CR.REG & RCC_CR_PLLRDY) != 0x00UL)
	{
		return DRIVER_STATUS_READY;
	}
	else
	{
		return DRIVER_STATUS_OFF;
	}
}
/** @} */ // RCC_02_LL_04_API_01_SourceControl

/*---------------------------------------------- RCC LL Clock Tree Fields ----------------------------------------------*/
/**
 * @brief	RCC LL Clock Tree Field APIs
 * @defgroup RCC_02_LL_04_API_02_ClockTree RCC LL Clock Tree Field Access
 * @ingroup	RCC_02_LL_04_API
 * @{
 */

/**
 * @brief	Programs the requested SYSCLK source field
 * @param[in] source	Requested system clock source field value of @ref rcc_ll_sysclk_src_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Valid system clock source field was programmed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p source is not a valid @ref rcc_ll_sysclk_src_t value.
 */
driver_status_t RCC_LL_SetSystemClockSource(const rcc_ll_sysclk_src_t source);

/**
 * @brief	Reads the configured SYSCLK source request field
 * @param[out] pSource	Pointer receiving @ref rcc_ll_sysclk_src_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: System clock source field was read successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSource is NULL.
 */
driver_status_t RCC_LL_GetSystemClockSource(rcc_ll_sysclk_src_t* const pSource);

/**
 * @brief	Reads the active SYSCLK status field
 * @param[out] pStatus	Pointer receiving @ref rcc_ll_sysclk_status_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: System clock status field was read successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pStatus is NULL.
 */
driver_status_t RCC_LL_GetSystemClockStatus(rcc_ll_sysclk_status_t* const pStatus);

/**
 * @brief	Programs the PLL input source field
 * @param[in] source	PLL source field value of @ref rcc_ll_pll_src_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Valid PLL source field was programmed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p source is not a valid @ref rcc_ll_pll_src_t value.
 */
driver_status_t RCC_LL_SetPLLSource(const rcc_ll_pll_src_t source);

/**
 * @brief	Reads the configured PLL source field
 * @param[out] pSource	Pointer receiving @ref rcc_ll_pll_src_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: PLL source field was read successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSource is NULL.
 */
driver_status_t RCC_LL_GetPLLSource(rcc_ll_pll_src_t* const pSource);

/**
 * @brief	Programs the HSE predivider used before PLL input
 * @param[in] divider	PLL HSE divider value of @ref rcc_ll_pll_hse_div_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Valid PLL HSE divider field was programmed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p divider is not a valid @ref rcc_ll_pll_hse_div_t value.
 */
driver_status_t RCC_LL_SetPLLHSEDivider(const rcc_ll_pll_hse_div_t divider);

/**
 * @brief	Reads the configured HSE predivider used before PLL input
 * @param[out] pDivider	Pointer receiving @ref rcc_ll_pll_hse_div_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: PLL HSE divider field was read successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pDivider is NULL.
 */
driver_status_t RCC_LL_GetPLLHSEDivider(rcc_ll_pll_hse_div_t* const pDivider);

/**
 * @brief	Programs the PLL multiplication factor field
 * @param[in] multiplier	PLL multiplication field value of @ref rcc_ll_pll_mul_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Valid PLL multiplication field was programmed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p multiplier is not a valid @ref rcc_ll_pll_mul_t value.
 */
driver_status_t RCC_LL_SetPLLMultiplier(const rcc_ll_pll_mul_t multiplier);

/**
 * @brief	Reads the configured PLL multiplication factor field
 * @param[out] pMultiplier	Pointer receiving @ref rcc_ll_pll_mul_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: PLL multiplication field was read successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pMultiplier is NULL.
 */
driver_status_t RCC_LL_GetPLLMultiplier(rcc_ll_pll_mul_t* const pMultiplier);

/**
 * @brief	Programs the AHB prescaler field
 * @param[in] prescaler	AHB prescaler field value of @ref rcc_ll_ahb_prescaler_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Valid AHB prescaler field was programmed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p prescaler is not a valid @ref rcc_ll_ahb_prescaler_t value.
 */
driver_status_t RCC_LL_SetAHBPrescaler(const rcc_ll_ahb_prescaler_t prescaler);

/**
 * @brief	Reads the configured AHB prescaler field
 * @param[out] pPrescaler	Pointer receiving @ref rcc_ll_ahb_prescaler_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AHB prescaler field was read successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPrescaler is NULL.
 */
driver_status_t RCC_LL_GetAHBPrescaler(rcc_ll_ahb_prescaler_t* const pPrescaler);

/**
 * @brief	Programs the APB1 prescaler field
 * @param[in] prescaler	APB prescaler field value of @ref rcc_ll_apb_prescaler_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Valid APB1 prescaler field was programmed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p prescaler is not a valid @ref rcc_ll_apb_prescaler_t value.
 */
driver_status_t RCC_LL_SetAPB1Prescaler(const rcc_ll_apb_prescaler_t prescaler);

/**
 * @brief	Reads the configured APB1 prescaler field
 * @param[out] pPrescaler	Pointer receiving @ref rcc_ll_apb_prescaler_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 prescaler field was read successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPrescaler is NULL.
 */
driver_status_t RCC_LL_GetAPB1Prescaler(rcc_ll_apb_prescaler_t* const pPrescaler);

/**
 * @brief	Programs the APB2 prescaler field
 * @param[in] prescaler	APB prescaler field value of @ref rcc_ll_apb_prescaler_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Valid APB2 prescaler field was programmed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p prescaler is not a valid @ref rcc_ll_apb_prescaler_t value.
 */
driver_status_t RCC_LL_SetAPB2Prescaler(const rcc_ll_apb_prescaler_t prescaler);

/**
 * @brief	Reads the configured APB2 prescaler field
 * @param[out] pPrescaler	Pointer receiving @ref rcc_ll_apb_prescaler_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 prescaler field was read successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPrescaler is NULL.
 */
driver_status_t RCC_LL_GetAPB2Prescaler(rcc_ll_apb_prescaler_t* const pPrescaler);

/**
 * @brief	Programs the ADC prescaler field
 * @param[in] prescaler	ADC prescaler field value of @ref rcc_ll_adc_prescaler_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Valid ADC prescaler field was programmed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p prescaler is not a valid @ref rcc_ll_adc_prescaler_t value.
 */
driver_status_t RCC_LL_SetADCPrescaler(const rcc_ll_adc_prescaler_t prescaler);

/**
 * @brief	Reads the configured ADC prescaler field
 * @param[out] pPrescaler	Pointer receiving @ref rcc_ll_adc_prescaler_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: ADC prescaler field was read successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPrescaler is NULL.
 */
driver_status_t RCC_LL_GetADCPrescaler(rcc_ll_adc_prescaler_t* const pPrescaler);

/**
 * @brief	Programs the USB prescaler field
 * @param[in] prescaler	USB prescaler field value of @ref rcc_ll_usb_prescaler_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Valid USB prescaler field was programmed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p prescaler is not a valid @ref rcc_ll_usb_prescaler_t value.
 */
driver_status_t RCC_LL_SetUSBPrescaler(const rcc_ll_usb_prescaler_t prescaler);

/**
 * @brief	Reads the configured USB prescaler field
 * @param[out] pPrescaler	Pointer receiving @ref rcc_ll_usb_prescaler_t
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: USB prescaler field was read successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPrescaler is NULL.
 */
driver_status_t RCC_LL_GetUSBPrescaler(rcc_ll_usb_prescaler_t* const pPrescaler);

/** @} */ // RCC_02_LL_04_API_02_ClockTree

/*---------------------------------------------- RCC LL Clock Gate and Reset ----------------------------------------------*/
/**
 * @brief	RCC LL Clock Gate and Reset APIs
 * @defgroup RCC_02_LL_04_API_03_ClockGateReset RCC LL Clock Gate and Reset Control
 * @ingroup	RCC_02_LL_04_API
 * @{
 */

/**
 * @brief	Enables AHB peripheral clocks using a raw AHBENR mask
 * @param[in] mask	AHBENR peripheral mask
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AHB clock bits were enabled successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mask is zero.
 */
driver_status_t RCC_LL_AHB_EnableClock(const uint32_t mask);

/**
 * @brief	Disables AHB peripheral clocks using a raw AHBENR mask
 * @param[in] mask	AHBENR peripheral mask
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: AHB clock bits were disabled successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mask is zero.
 */
driver_status_t RCC_LL_AHB_DisableClock(const uint32_t mask);

/**
 * @brief	Enables APB2 peripheral clocks using a raw APB2ENR mask
 * @param[in] mask	APB2ENR peripheral mask
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 clock bits were enabled successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mask is zero.
 */
driver_status_t RCC_LL_APB2_EnableClock(const uint32_t mask);

/**
 * @brief	Disables APB2 peripheral clocks using a raw APB2ENR mask
 * @param[in] mask	APB2ENR peripheral mask
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 clock bits were disabled successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mask is zero.
 */
driver_status_t RCC_LL_APB2_DisableClock(const uint32_t mask);

/**
 * @brief	Enables APB1 peripheral clocks using a raw APB1ENR mask
 * @param[in] mask	APB1ENR peripheral mask
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 clock bits were enabled successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mask is zero.
 */
driver_status_t RCC_LL_APB1_EnableClock(const uint32_t mask);

/**
 * @brief	Disables APB1 peripheral clocks using a raw APB1ENR mask
 * @param[in] mask	APB1ENR peripheral mask
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 clock bits were disabled successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mask is zero.
 */
driver_status_t RCC_LL_APB1_DisableClock(const uint32_t mask);

/**
 * @brief	Asserts APB2 peripheral reset bits using a raw APB2RSTR mask
 * @param[in] mask	APB2RSTR peripheral mask
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 reset bits were asserted successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mask is zero.
 */
driver_status_t RCC_LL_APB2_ForceReset(const uint32_t mask);

/**
 * @brief	Releases APB2 peripheral reset bits using a raw APB2RSTR mask
 * @param[in] mask	APB2RSTR peripheral mask
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 reset bits were released successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mask is zero.
 */
driver_status_t RCC_LL_APB2_ReleaseReset(const uint32_t mask);

/**
 * @brief	Asserts APB1 peripheral reset bits using a raw APB1RSTR mask
 * @param[in] mask	APB1RSTR peripheral mask
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 reset bits were asserted successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mask is zero.
 */
driver_status_t RCC_LL_APB1_ForceReset(const uint32_t mask);

/**
 * @brief	Releases APB1 peripheral reset bits using a raw APB1RSTR mask
 * @param[in] mask	APB1RSTR peripheral mask
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 reset bits were released successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mask is zero.
 */
driver_status_t RCC_LL_APB1_ReleaseReset(const uint32_t mask);

/**
 * @brief	Generates an APB2 reset pulse using a raw APB2RSTR mask
 * @param[in] mask	APB2RSTR peripheral mask
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB2 reset pulse was generated successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mask is zero.
 */
driver_status_t RCC_LL_APB2_ResetPulse(const uint32_t mask);

/**
 * @brief	Generates an APB1 reset pulse using a raw APB1RSTR mask
 * @param[in] mask	APB1RSTR peripheral mask
 * @returns - @ref driver_status_t Operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 reset pulse was generated successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mask is zero.
 */
driver_status_t RCC_LL_APB1_ResetPulse(const uint32_t mask);

/** @} */ // RCC_02_LL_04_API_03_ClockGateReset

/** @} */ // RCC_02_LL_04_API

/** @} */ // RCC_02_LL

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_LL_H_ */
