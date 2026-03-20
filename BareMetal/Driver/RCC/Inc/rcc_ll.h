/**
 * @file	rcc_ll.h
 * @author	Shrey Shah
 * @brief	RCC Low-Level Register Access Layer
 * @version	v2.2
 * @date	20-03-2026
 *
 * @details
 * This header provides the **Low-Level (LL)** RCC register access surface for the framework.
 * It intentionally stays macro-based and builds on top of the generic register utilities from
 * `stm32f1xx_utils.h`, so the driver does not need one wrapper function per RCC register.
 *
 * The header is split into two parts:
 * - Generic RCC LL register operation macros used by the RCC driver implementation.
 * - Compatibility aliases kept for existing LL users such as GPIO and I2C.
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
 * - They are intended for use by the RCC driver implementation and any LL code that needs
 *   direct RCC register manipulation without introducing redundant wrapper functions.
 * @{
 */

/**
 * @brief	Retrieves pointer to an RCC register `.REG` field
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @returns	Pointer to the 32-bit register storage
 */
#define RCC_LL_REG(_RCC_, _REG_)							(&((_RCC_)->_REG_.REG))

/**
 * @brief	Reads an RCC register through the generic register utility layer
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @param[out] _VAR_	Destination variable that receives the register image
 */
#define RCC_LL_READ(_RCC_, _REG_, _VAR_)					REGOPS_READ(RCC_LL_REG((_RCC_), _REG_), (_VAR_))

/**
 * @brief	Writes an RCC register through the generic register utility layer
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @param[in] _VAL_	32-bit value to be written
 */
#define RCC_LL_WRITE(_RCC_, _REG_, _VAL_)					REGOPS_WRITE(RCC_LL_REG((_RCC_), _REG_), (_VAL_))

/**
 * @brief	Sets masked bits in an RCC register
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @param[in] _MASK_	Bit-mask to be ORed into the target register
 */
#define RCC_LL_SET(_RCC_, _REG_, _MASK_)					REGOPS_SET(RCC_LL_REG((_RCC_), _REG_), (_MASK_))

/**
 * @brief	Clears masked bits in an RCC register
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @param[in] _MASK_	Bit-mask to be cleared from the target register
 */
#define RCC_LL_CLEAR(_RCC_, _REG_, _MASK_)					REGOPS_CLEAR(RCC_LL_REG((_RCC_), _REG_), (_MASK_))

/**
 * @brief	Toggles masked bits in an RCC register
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @param[in] _MASK_	Bit-mask to be toggled in the target register
 */
#define RCC_LL_TOGGLE(_RCC_, _REG_, _MASK_)					REGOPS_TOGGLE(RCC_LL_REG((_RCC_), _REG_), (_MASK_))

/**
 * @brief	Performs a masked register-field modification
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _REG_	Register member name inside @ref RCC_TypeDef
 * @param[in] _MASK_	Field mask to clear before update
 * @param[in] _VAL_	Pre-shifted field value to be merged into the register
 */
#define RCC_LL_MODIFY(_RCC_, _REG_, _MASK_, _VAL_)			REGOPS_MODIFY(RCC_LL_REG((_RCC_), _REG_), (_MASK_), (_VAL_))

/**
 * @brief	Prepares a field value for masked register insertion
 * @param[in] _VAL_	Raw unshifted field value
 * @param[in] _MASK_	Target field mask
 * @param[in] _POS_	Target field position
 * @returns	Shifted and masked field value
 */
#define RCC_LL_FIELD_PREP(_VAL_, _MASK_, _POS_)				((((uint32_t)(_VAL_)) << (_POS_)) & (_MASK_))

/**
 * @brief	Extracts a right-aligned field value from a register image
 * @param[in] _REG_	Register image
 * @param[in] _MASK_	Target field mask
 * @param[in] _POS_	Target field position
 * @returns	Right-aligned field value
 */
#define RCC_LL_FIELD_GET(_REG_, _MASK_, _POS_)				((((uint32_t)(_REG_)) & (_MASK_)) >> (_POS_))

/** @} */ // RCC_02_LL_01_RegOps

/*---------------------------------------------- RCC LL Compatibility Macros ----------------------------------------------*/
/**
 * @brief	RCC Legacy Compatibility Macros
 * @defgroup RCC_02_LL_02_Compat RCC LL Compatibility Helpers
 * @ingroup	RCC_02_LL
 * @details
 * - These aliases are retained for LL modules that still call the historic `__RCC_*` helpers.
 * - They are thin compatibility shims over the generic @ref RCC_02_LL_01_RegOps macros.
 * - New RCC code should prefer the generic `RCC_LL_*` macros directly.
 * @{
 */

/*---------------------------------------------- RCC CR Compatibility ----------------------------------------------*/
/**
 * @brief	RCC Control Register compatibility macros
 * @defgroup RCC_02_LL_02_Compat_01_CR RCC LL CR Compatibility Macros
 * @ingroup	RCC_02_LL_02_Compat
 * @{
 */

/**
 * @brief	Reads @ref RCC_CR "RCC->CR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @returns	Current RCC CR register image
 */
#define __RCC_ReadCR(_RCC_)							(*RCC_LL_REG((_RCC_), CR))

/**
 * @brief	Writes @ref RCC_CR "RCC->CR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _VAL_	Value to be written into CR
 */
#define __RCC_WriteCR(_RCC_, _VAL_)					RCC_LL_WRITE((_RCC_), CR, (_VAL_))

/**
 * @brief	Sets masked bits in @ref RCC_CR "RCC->CR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	Bit-mask to set
 */
#define __RCC_SetCR(_RCC_, _MASK_)					RCC_LL_SET((_RCC_), CR, (_MASK_))

/**
 * @brief	Clears masked bits in @ref RCC_CR "RCC->CR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	Bit-mask to clear
 */
#define __RCC_ClearCR(_RCC_, _MASK_)				RCC_LL_CLEAR((_RCC_), CR, (_MASK_))

/** @} */ // RCC_02_LL_02_Compat_01_CR

/*---------------------------------------------- RCC CFGR Compatibility ----------------------------------------------*/
/**
 * @brief	RCC Clock Configuration Register compatibility macros
 * @defgroup RCC_02_LL_02_Compat_02_CFGR RCC LL CFGR Compatibility Macros
 * @ingroup	RCC_02_LL_02_Compat
 * @{
 */

/**
 * @brief	Reads @ref RCC_CFGR "RCC->CFGR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @returns	Current RCC CFGR register image
 */
#define __RCC_ReadCFGR(_RCC_)						(*RCC_LL_REG((_RCC_), CFGR))

/**
 * @brief	Writes @ref RCC_CFGR "RCC->CFGR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _VAL_	Value to be written into CFGR
 */
#define __RCC_WriteCFGR(_RCC_, _VAL_)				RCC_LL_WRITE((_RCC_), CFGR, (_VAL_))

/**
 * @brief	Sets masked bits in @ref RCC_CFGR "RCC->CFGR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	Bit-mask to set
 */
#define __RCC_SetCFGR(_RCC_, _MASK_)				RCC_LL_SET((_RCC_), CFGR, (_MASK_))

/**
 * @brief	Clears masked bits in @ref RCC_CFGR "RCC->CFGR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	Bit-mask to clear
 */
#define __RCC_ClearCFGR(_RCC_, _MASK_)				RCC_LL_CLEAR((_RCC_), CFGR, (_MASK_))

/** @} */ // RCC_02_LL_02_Compat_02_CFGR

/*---------------------------------------------- RCC Clock Enable Compatibility ----------------------------------------------*/
/**
 * @brief	RCC clock gate register compatibility macros
 * @defgroup RCC_02_LL_02_Compat_03_ENR RCC LL Enable Register Compatibility Macros
 * @ingroup	RCC_02_LL_02_Compat
 * @{
 */

/**
 * @brief	Sets bits in @ref RCC_AHBENR "RCC->AHBENR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	AHB peripheral clock mask
 */
#define __RCC_SetAHBENR(_RCC_, _MASK_)				RCC_LL_SET((_RCC_), AHBENR, (_MASK_))

/**
 * @brief	Clears bits in @ref RCC_AHBENR "RCC->AHBENR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	AHB peripheral clock mask
 */
#define __RCC_ClearAHBENR(_RCC_, _MASK_)			RCC_LL_CLEAR((_RCC_), AHBENR, (_MASK_))

/**
 * @brief	Sets bits in @ref RCC_APB2ENR "RCC->APB2ENR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	APB2 peripheral clock mask
 */
#define __RCC_SetAPB2ENR(_RCC_, _MASK_)				RCC_LL_SET((_RCC_), APB2ENR, (_MASK_))

/**
 * @brief	Clears bits in @ref RCC_APB2ENR "RCC->APB2ENR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	APB2 peripheral clock mask
 */
#define __RCC_ClearAPB2ENR(_RCC_, _MASK_)			RCC_LL_CLEAR((_RCC_), APB2ENR, (_MASK_))

/**
 * @brief	Sets bits in @ref RCC_APB1ENR "RCC->APB1ENR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	APB1 peripheral clock mask
 */
#define __RCC_SetAPB1ENR(_RCC_, _MASK_)				RCC_LL_SET((_RCC_), APB1ENR, (_MASK_))

/**
 * @brief	Clears bits in @ref RCC_APB1ENR "RCC->APB1ENR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	APB1 peripheral clock mask
 */
#define __RCC_ClearAPB1ENR(_RCC_, _MASK_)			RCC_LL_CLEAR((_RCC_), APB1ENR, (_MASK_))

/** @} */ // RCC_02_LL_02_Compat_03_ENR

/*---------------------------------------------- RCC Reset Compatibility ----------------------------------------------*/
/**
 * @brief	RCC peripheral reset register compatibility macros
 * @defgroup RCC_02_LL_02_Compat_04_RSTR RCC LL Reset Register Compatibility Macros
 * @ingroup	RCC_02_LL_02_Compat
 * @{
 */

/**
 * @brief	Sets bits in @ref RCC_APB2RSTR "RCC->APB2RSTR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	APB2 peripheral reset mask
 */
#define __RCC_SetAPB2RSTR(_RCC_, _MASK_)			RCC_LL_SET((_RCC_), APB2RSTR, (_MASK_))

/**
 * @brief	Clears bits in @ref RCC_APB2RSTR "RCC->APB2RSTR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	APB2 peripheral reset mask
 */
#define __RCC_ClearAPB2RSTR(_RCC_, _MASK_)			RCC_LL_CLEAR((_RCC_), APB2RSTR, (_MASK_))

/**
 * @brief	Sets bits in @ref RCC_APB1RSTR "RCC->APB1RSTR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	APB1 peripheral reset mask
 */
#define __RCC_SetAPB1RSTR(_RCC_, _MASK_)			RCC_LL_SET((_RCC_), APB1RSTR, (_MASK_))

/**
 * @brief	Clears bits in @ref RCC_APB1RSTR "RCC->APB1RSTR"
 * @param[in] _RCC_	Target @ref RCC_TypeDef peripheral pointer
 * @param[in] _MASK_	APB1 peripheral reset mask
 */
#define __RCC_ClearAPB1RSTR(_RCC_, _MASK_)			RCC_LL_CLEAR((_RCC_), APB1RSTR, (_MASK_))

/** @} */ // RCC_02_LL_02_Compat_04_RSTR

/** @} */ // RCC_02_LL_02_Compat

/** @} */ // RCC_02_LL

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_LL_H_ */
