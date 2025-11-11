/**
 * @file rcc_ll.h
 * @author Shrey Shah
 * @version v1.2
 * @date 08-11-2025
 */
#ifndef RCC_LL_H_
#define RCC_LL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** 
 * @brief For register mapping base types
 * @include @file stm32f1xx.h 
 */
#include "stm32f1xx.h"

// ======================================================================================================
// RCC Register APIs
// ======================================================================================================

/**
 * @addtogroup RCC_01_Registers_03_API
 * @{
 */

/*---------------------------------------------- RCC CR ----------------------------------------------*/

/**
 * @defgroup RCC_01_Registers_03_API_01_CR Clock Control Register
 * @ingroup RCC_01_Registers_03_API
 * @brief APIs for Clock Control Register
 * @{
 */

/**
 * @brief 				Reads @ref RCC_CR "RCC->CR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @returns				RCC->CR register value
 */
__STATIC_FORCEINLINE uint32_t __RCC_ReadCR(RCC_TypeDef* const RCCx)
{
	return (uint32_t) RCCx->CR.REG;
}

/**
 * @brief				Writes @ref RCC_CR "RCC->CR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __RCC_WriteCR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref RCC_CR "RCC->CR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __RCC_SetCR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref RCC_CR "RCC->CR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __RCC_ClearCR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref RCC_CR "RCC->CR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __RCC_ToggleCR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CR.REG ^= value;
}

/** @} */ // RCC_01_Registers_03_API_01_CR

/*---------------------------------------------- RCC CFGR ----------------------------------------------*/

/**
 * @defgroup RCC_01_Registers_03_API_02_CFGR Clock Configuration Register
 * @ingroup RCC_01_Registers_03_API
 * @brief APIs for Clock Configuration Register
 * @{
 */

/**
 * @brief 				Reads @ref RCC_CFGR "RCC->CFGR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @returns				RCC->CFGR register value
 */
__STATIC_FORCEINLINE uint32_t __RCC_ReadCFGR(RCC_TypeDef* const RCCx)
{
	return (uint32_t) RCCx->CFGR.REG;
}

/**
 * @brief				Writes @ref RCC_CFGR "RCC->CFGR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __RCC_WriteCFGR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CFGR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref RCC_CFGR "RCC->CFGR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __RCC_SetCFGR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CFGR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref RCC_CFGR "RCC->CFGR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __RCC_ClearCFGR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CFGR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref RCC_CFGR "RCC->CFGR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __RCC_ToggleCFGR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CFGR.REG ^= value;
}

/** @} */ // RCC_01_Registers_03_API_02_CFGR

/*---------------------------------------------- RCC CIR ----------------------------------------------*/

/**
 * @defgroup RCC_01_Registers_03_API_03_CIR Clock Interrupt Register
 * @ingroup RCC_01_Registers_03_API
 * @brief APIs for Clock Interrupt Register
 * @{
 */

/**
 * @brief 				Reads @ref RCC_CIR "RCC->CIR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @returns				RCC->CIR register value
 */
__STATIC_FORCEINLINE uint32_t __RCC_ReadCIR(RCC_TypeDef* const RCCx)
{
	return (uint32_t) RCCx->CIR.REG;
}

/**
 * @brief				Writes @ref RCC_CIR "RCC->CIR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __RCC_WriteCIR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CIR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref RCC_CIR "RCC->CIR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __RCC_SetCIR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CIR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref RCC_CIR "RCC->CIR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __RCC_ClearCIR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CIR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref RCC_CIR "RCC->CIR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __RCC_ToggleCIR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CIR.REG ^= value;
}

/** @} */ // RCC_01_Registers_03_API_03_CIR

/*---------------------------------------------- RCC APB2RSTR ----------------------------------------------*/

/**
 * @defgroup RCC_01_Registers_03_API_04_APB2RSTR APB2 Peripheral Reset Register
 * @ingroup RCC_01_Registers_03_API
 * @brief APIs for APB2 Peripheral Reset Register
 * @{
 */

/**
 * @brief 				Reads @ref RCC_APB2RSTR "RCC->APB2RSTR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @returns				RCC->APB2RSTR register value
 */
__STATIC_FORCEINLINE uint32_t __RCC_ReadAPB2RSTR(RCC_TypeDef* const RCCx)
{
	return (uint32_t) RCCx->APB2RSTR.REG;
}

/**
 * @brief				Writes @ref RCC_APB2RSTR "RCC->APB2RSTR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __RCC_WriteAPB2RSTR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB2RSTR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref RCC_APB2RSTR "RCC->APB2RSTR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __RCC_SetAPB2RSTR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB2RSTR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref RCC_APB2RSTR "RCC->APB2RSTR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __RCC_ClearAPB2RSTR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB2RSTR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref RCC_APB2RSTR "RCC->APB2RSTR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __RCC_ToggleAPB2RSTR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB2RSTR.REG ^= value;
}

/** @} */ // RCC_01_Registers_03_API_04_APB2RSTR

/*---------------------------------------------- RCC APB1RSTR ----------------------------------------------*/

/**
 * @defgroup RCC_01_Registers_03_API_05_APB1RSTR APB1 Peripheral Reset Register
 * @ingroup RCC_01_Registers_03_API
 * @brief APIs for APB1 Peripheral Reset Register
 * @{
 */

/**
 * @brief 				Reads @ref RCC_APB1RSTR "RCC->APB1RSTR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @returns				RCC->APB1RSTR register value
 */
__STATIC_FORCEINLINE uint32_t __RCC_ReadAPB1RSTR(RCC_TypeDef* const RCCx)
{
	return (uint32_t) RCCx->APB1RSTR.REG;
}

/**
 * @brief				Writes @ref RCC_APB1RSTR "RCC->APB1RSTR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __RCC_WriteAPB1RSTR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB1RSTR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref RCC_APB1RSTR "RCC->APB1RSTR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __RCC_SetAPB1RSTR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB1RSTR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref RCC_APB1RSTR "RCC->APB1RSTR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __RCC_ClearAPB1RSTR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB1RSTR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref RCC_APB1RSTR "RCC->APB1RSTR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __RCC_ToggleAPB1RSTR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB1RSTR.REG ^= value;
}

/** @} */ // RCC_01_Registers_03_API_05_APB1RSTR

/*---------------------------------------------- RCC AHBENR ----------------------------------------------*/

/**
 * @defgroup RCC_01_Registers_03_API_06_AHBENR AHB Peripheral Clock Enable Register
 * @ingroup RCC_01_Registers_03_API
 * @brief APIs for AHB Peripheral Clock Enable Register
 * @{
 */

/**
 * @brief 				Reads @ref RCC_AHBENR "RCC->AHBENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @returns				RCC->AHBENR register value
 */
__STATIC_FORCEINLINE uint32_t __RCC_ReadAHBENR(RCC_TypeDef* const RCCx)
{
	return (uint32_t) RCCx->AHBENR.REG;
}

/**
 * @brief				Writes @ref RCC_AHBENR "RCC->AHBENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __RCC_WriteAHBENR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->AHBENR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref RCC_AHBENR "RCC->AHBENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __RCC_SetAHBENR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->AHBENR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref RCC_AHBENR "RCC->AHBENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __RCC_ClearAHBENR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->AHBENR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref RCC_AHBENR "RCC->AHBENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __RCC_ToggleAHBENR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->AHBENR.REG ^= value;
}

/** @} */ // RCC_01_Registers_03_API_06_AHBENR

/*---------------------------------------------- RCC APB2ENR ----------------------------------------------*/

/**
 * @defgroup RCC_01_Registers_03_API_07_APB2ENR APB2 Peripheral Clock Enable Register
 * @ingroup RCC_01_Registers_03_API
 * @brief APIs for APB2 Peripheral Clock Enable Register
 * @{ 
 */

/**
 * @brief 				Reads @ref RCC_APB2ENR "RCC->APB2ENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @returns				RCC->APB2ENR register value
 */
__STATIC_FORCEINLINE uint32_t __RCC_ReadAPB2ENR(RCC_TypeDef* const RCCx)
{
	return (uint32_t) RCCx->APB2ENR.REG;
}

/**
 * @brief				Writes @ref RCC_APB2ENR "RCC->APB2ENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __RCC_WriteAPB2ENR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB2ENR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref RCC_APB2ENR "RCC->APB2ENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __RCC_SetAPB2ENR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB2ENR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref RCC_APB2ENR "RCC->APB2ENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __RCC_ClearAPB2ENR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB2ENR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref RCC_APB2ENR "RCC->APB2ENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __RCC_ToggleAPB2ENR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB2ENR.REG ^= value;
}

/** @} */ // RCC_01_Registers_03_API_07_APB2ENR

/*---------------------------------------------- RCC APB1ENR ----------------------------------------------*/

/**
 * @defgroup RCC_01_Registers_03_API_08_APB1ENR APB1 Peripheral Clock Enable Register
 * @ingroup RCC_01_Registers_03_API
 * @brief APIs for APB1 Peripheral Clock Enable Register
 * @{ 
 */

/**
 * @brief 				Reads @ref RCC_APB1ENR "RCC->APB1ENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @returns				RCC->APB1ENR register value
 */
__STATIC_FORCEINLINE uint32_t __RCC_ReadAPB1ENR(RCC_TypeDef* const RCCx)
{
	return (uint32_t) RCCx->APB1ENR.REG;
}

/**
 * @brief				Writes @ref RCC_APB1ENR "RCC->APB1ENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __RCC_WriteAPB1ENR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB1ENR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref RCC_APB1ENR "RCC->APB1ENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __RCC_SetAPB1ENR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB1ENR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref RCC_APB1ENR "RCC->APB1ENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __RCC_ClearAPB1ENR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB1ENR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref RCC_APB1ENR "RCC->APB1ENR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __RCC_ToggleAPB1ENR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->APB1ENR.REG ^= value;
}

/** @} */ // RCC_01_Registers_03_API_08_APB1ENR

/*---------------------------------------------- RCC BDCR ----------------------------------------------*/

/**
 * @defgroup RCC_01_Registers_03_API_09_BDCR Backup Domain Control Register
 * @ingroup RCC_01_Registers_03_API
 * @brief APIs for Backup Domain Control Register
 * @{ 
 */

/**
 * @brief 				Reads @ref RCC_BDCR "RCC->BDCR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @returns				RCC->BDCR register value
 */
__STATIC_FORCEINLINE uint32_t __RCC_ReadBDCR(RCC_TypeDef* const RCCx)
{
	return (uint32_t) RCCx->BDCR.REG;
}

/**
 * @brief				Writes @ref RCC_BDCR "RCC->BDCR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __RCC_WriteBDCR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->BDCR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref RCC_BDCR "RCC->BDCR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __RCC_SetBDCR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->BDCR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref RCC_BDCR "RCC->BDCR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __RCC_ClearBDCR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->BDCR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref RCC_BDCR "RCC->BDCR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __RCC_ToggleBDCR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->BDCR.REG ^= value;
}

/** @} */ // RCC_01_Registers_03_API_09_BDCR

/*---------------------------------------------- RCC CSR ----------------------------------------------*/

/**
 * @defgroup RCC_01_Registers_03_API_10_CSR Control/Status Register
 * @ingroup RCC_01_Registers_03_API
 * @brief APIs for Control/Status Register
 * @{ 
 */

/**
 * @brief 				Reads @ref RCC_CSR "RCC->CSR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @returns				RCC->CSR register value
 */
__STATIC_FORCEINLINE uint32_t __RCC_ReadCSR(RCC_TypeDef* const RCCx)
{
	return (uint32_t) RCCx->CSR.REG;
}

/**
 * @brief				Writes @ref RCC_CSR "RCC->CSR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __RCC_WriteCSR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CSR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref RCC_CSR "RCC->CSR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __RCC_SetCSR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CSR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref RCC_CSR "RCC->CSR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __RCC_ClearCSR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CSR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref RCC_CSR "RCC->CSR"
 * @param[in] RCCx		Target @ref RCC_01_Registers "RCC Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __RCC_ToggleCSR(RCC_TypeDef* const RCCx, const uint32_t value)
{
	RCCx->CSR.REG ^= value;
}

/** @} */ // RCC_01_Registers_03_API_10_CSR

/** @} */ // RCC_01_Registers_03_API

// ======================================================================================================
// RCC Low Level APIs
// ======================================================================================================

/**
 * @addtogroup RCC_02_LL
 * @{
 */

/*---------------------------------------------- RCC Flash ----------------------------------------------*/
/** @brief Low-level flash latency type definition @typedef _rcc_flash_latency_t */
typedef uint8_t 								_rcc_flash_latency_t;

/** @brief Zero wait state @def _RCC_FLASH_LATENCY_0 */
#define _RCC_FLASH_LATENCY_0					((_rcc_flash_latency_t) 0x00)
/** @brief One wait state @def _RCC_FLASH_LATENCY_1 */
#define _RCC_FLASH_LATENCY_1					((_rcc_flash_latency_t) 0x01)
/** @brief Two wait states @def _RCC_FLASH_LATENCY_2 */
#define _RCC_FLASH_LATENCY_2					((_rcc_flash_latency_t) 0x02)

/** @brief Low-level flash prefetch type definition @typedef _rcc_flash_prefetch_t */
typedef uint8_t _rcc_flash_prefetch_t;

/** @brief Prefetch disabled @def _RCC_FLASH_PREFETCH_DISABLE */
#define _RCC_FLASH_PREFETCH_DISABLE				((_rcc_flash_prefetch_t) 0x00)
/** @brief Prefetch enabled @def _RCC_FLASH_PREFETCH_ENABLE */
#define _RCC_FLASH_PREFETCH_ENABLE				((_rcc_flash_prefetch_t) 0x01)

/**
 * @brief Stage Flash Latency configuration into FLASH_ACR register value
 * @param[in] latency Flash latency configuration (@ref RCC_FLASH_LATENCY_0, RCC_FLASH_LATENCY_1, RCC_FLASH_LATENCY_2)
 * @param[in] acrReg Current FLASH_ACR register value
 * @returns The updated staged FLASH_ACR register value with new latency configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 */
__STATIC_FORCEINLINE uint32_t _RCC_StageFlashLatency(const _rcc_flash_latency_t latency, uint32_t acrReg)
{
	// Clear latency bits (bits 0-2 for LATENCY[2:0])
	acrReg &= ~FLASH_ACR_LATENCY;
	// Stage latency configuration
	acrReg |= (uint32_t)(latency << FLASH_ACR_LATENCY_Pos);
	return acrReg;
}

/**
 * @brief Stage Flash Prefetch Buffer configuration into FLASH_ACR register value
 * @param[in] prefetch Flash prefetch configuration (@ref RCC_FLASH_PREFETCH_DISABLE, RCC_FLASH_PREFETCH_ENABLE)
 * @param[in] acrReg Current FLASH_ACR register value
 * @returns The updated staged FLASH_ACR register value with new prefetch configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 */
__STATIC_FORCEINLINE uint32_t _RCC_StageFlashPrefetch(const _rcc_flash_prefetch_t prefetch, uint32_t acrReg)
{
	// Clear prefetch buffer enable bit
	acrReg &= ~FLASH_ACR_PRFTBE;
	// Stage prefetch configuration
	if(prefetch == _RCC_FLASH_PREFETCH_ENABLE) acrReg |= FLASH_ACR_PRFTBE;
	return acrReg;
}

/**
 * @brief Stage complete Flash ACR configuration into register value
 * @param[in] latency Flash latency configuration (@ref RCC_FLASH_LATENCY_0, RCC_FLASH_LATENCY_1, RCC_FLASH_LATENCY_2) 
 * @param[in] prefetch Flash prefetch configuration (@ref RCC_FLASH_PREFETCH_DISABLE, RCC_FLASH_PREFETCH_ENABLE)
 * @param[in] acrReg Current FLASH_ACR register value
 * @returns The updated staged FLASH_ACR register value with new flash configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 * @note - This combines both latency and prefetch configurations
 */
__STATIC_FORCEINLINE uint32_t _RCC_StageFlashConfig(const _rcc_flash_latency_t latency, const _rcc_flash_prefetch_t prefetch, uint32_t acrReg)
{
	// Stage latency configuration
	acrReg = _RCC_StageFlashLatency(latency, acrReg);
	// Stage prefetch configuration
	acrReg = _RCC_StageFlashPrefetch(prefetch, acrReg);
	return acrReg;
}

/** @} */ // RCC_02_LL_01_FlashConfig

/*---------------------------------------------- RCC Frequency ----------------------------------------------*/
/**
 * @brief		RCC Low Level Frequency Type and Definitions
 * @defgroup 	RCC_02_LL_02_Freq RCC Low Level Frequency
 * @ingroup 	RCC_02_LL
 * @details
 * - These constants define standard frequency values used in RCC configuration
 * - Used for timer configurations, peripheral clock settings, and system clock setup
 * - All values are in Hertz (Hz)
 * @see Reference Manual RM0008 - Section 7. Clock Configuration
 * @{
 */

/** @brief Frequency type definition @typedef _rcc_freq_t */
typedef uint32_t _rcc_freq_t;
/** @brief 12 Hz frequency @def _RCC_FREQ_12Hz */
#define _RCC_FREQ_12Hz 									((_rcc_freq_t) 12)
/** @brief 25 Hz frequency @def _RCC_FREQ_25Hz */
#define _RCC_FREQ_25Hz 									((_rcc_freq_t) 25)
/** @brief 50 Hz frequency @def _RCC_FREQ_50Hz */
#define _RCC_FREQ_50Hz 									((_rcc_freq_t) 50)
/** @brief 100 Hz frequency @def _RCC_FREQ_100Hz */
#define _RCC_FREQ_100Hz 								((_rcc_freq_t) 100)
/** @brief 500 Hz frequency @def _RCC_FREQ_500Hz */
#define _RCC_FREQ_500Hz 								((_rcc_freq_t) 500)
/** @brief 1 kHz frequency @def _RCC_FREQ_1kHz */
#define _RCC_FREQ_1kHz 									((_rcc_freq_t) 1000)
/** @brief 2 kHz frequency @def _RCC_FREQ_2kHz */
#define _RCC_FREQ_2kHz 									((_rcc_freq_t) 2000)
/** @brief 5 kHz frequency @def _RCC_FREQ_5kHz */
#define _RCC_FREQ_5kHz 									((_rcc_freq_t) 5000)
/** @brief 10 kHz frequency @def _RCC_FREQ_10kHz */
#define _RCC_FREQ_10kHz 								((_rcc_freq_t) 10000)
/** @brief 50 kHz frequency @def _RCC_FREQ_50kHz */
#define _RCC_FREQ_50kHz 								((_rcc_freq_t) 50000)
/** @brief 72 kHz frequency @def _RCC_FREQ_72kHz */
#define _RCC_FREQ_72kHz 								((_rcc_freq_t) 72000)
/** @brief 100 kHz frequency @def _RCC_FREQ_100kHz */
#define _RCC_FREQ_100kHz 								((_rcc_freq_t) 100000)
/** @brief 200 kHz frequency @def _RCC_FREQ_200kHz */
#define _RCC_FREQ_200kHz 								((_rcc_freq_t) 200000)
/** @brief 1 MHz frequency @def _RCC_FREQ_1MHz */
#define _RCC_FREQ_1MHz 									((_rcc_freq_t) 1000000)
/** @brief 10 MHz frequency @def _RCC_FREQ_10MHz */
#define _RCC_FREQ_10MHz 								((_rcc_freq_t) 10000000)
/** @brief HSI (High Speed Internal) oscillator frequency @def _RCC_HSI_FREQ */
#define _RCC_HSI_FREQ 									((_rcc_freq_t) 8000000)
/** @brief HSE (High Speed External) oscillator frequency @def _RCC_HSE_FREQ */
#define _RCC_HSE_FREQ 									((_rcc_freq_t) 8000000)
/** @brief Minimum PLL output frequency @def _RCC_PLL_MIN_FREQ */
#define _RCC_PLL_MIN_FREQ 								((_rcc_freq_t) 16000000)
/** @brief Maximum PLL output frequency @def _RCC_PLL_MAX_FREQ */
#define _RCC_PLL_MAX_FREQ 								((_rcc_freq_t) 72000000)

/** @} */ // RCC_02_LL_02_Freq

/*---------------------------------------------- RCC Clock Source ----------------------------------------------*/
/**
 * @brief		RCC Low Level Clock Source Definitions
 * @defgroup	RCC_02_LL_03_ClockSource RCC Low Level Clock Source
 * @ingroup		RCC_02_LL
 * @details
 * - These constants define the available system clock sources for RCC configuration
 * - Used for selecting the main system clock source during initialization
 * - Each source has different characteristics and use cases
 * 
 * @see Reference Manual RM0008 - Section 7.3.1 Clock control register (RCC_CR)
 * @{
 */

/** @brief System clock source type definition @typedef _rcc_sys_clk_t */
typedef uint8_t 										_rcc_sys_clk_t;
/** @brief HSI (High Speed Internal) RC oscillator @def _RCC_SYS_CLK_HSI */
#define _RCC_SYS_CLK_HSI 								((_rcc_sys_clk_t) 0x00)
/** @brief HSE (High Speed External) crystal oscillator @def _RCC_SYS_CLK_HSE */
#define _RCC_SYS_CLK_HSE 								((_rcc_sys_clk_t) 0x01)
/** @brief PLL (Phase Locked Loop) output @def _RCC_SYS_CLK_PLL */
#define _RCC_SYS_CLK_PLL 								((_rcc_sys_clk_t) 0x02)

/**
 * @brief Stage System Clock Source configuration into RCC_CFGR register value
 * @param[in] sysClk System clock source configuration
 * @param[in] cfgrReg Current RCC_CFGR register value
 * @returns The updated staged RCC_CFGR register value with new system clock source configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 */
__STATIC_FORCEINLINE uint32_t _RCC_StageSystemClockSource(const _rcc_sys_clk_t sysClk, uint32_t cfgrReg)
{
	cfgrReg &= ~RCC_CFGR_SW;
	cfgrReg |= (uint32_t)(sysClk << RCC_CFGR_SW_Pos);
	return cfgrReg;
}

/** @} */ // RCC_02_LL_03_ClockSource

/*---------------------------------------------- RCC Prescaler ----------------------------------------------*/

/**
 * @brief		RCC Low Level Prescaler Definitions
 * @defgroup 	RCC_02_LL_04_Prescaler RCC Low Level Prescalers
 * @ingroup 	RCC_02_LL
 * @details
 * - These constants define the AHB (Advanced High-performance Bus) prescaler values
 * - Used to divide the system clock frequency for AHB peripherals
 * - AHB bus connects to core, memory, and DMA
 * 
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief AHB bus prescaler type definition @typedef _rcc_bus_prescaler_t */
typedef uint8_t 								_rcc_bus_prescaler_t; 

/**
 * @brief		RCC Low Level AHB Prescaler Definitions
 * @defgroup 	RCC_02_LL_04_Prescaler_01_AHB RCC Low Level AHB Prescaler
 * @ingroup 	RCC_02_LL_04_Prescaler
 * @details
 * - These constants define the AHB (Advanced High-performance Bus) prescaler values
 * - Used to divide the system clock frequency for AHB peripherals
 * - AHB bus connects to core, memory, and DMA
 * 
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief AHB division by 1 (no prescaling) @def _RCC_AHB_DIV_1 */
#define _RCC_AHB_DIV_1 							((_rcc_bus_prescaler_t) 0x00)
/** @brief AHB division by 2 @def _RCC_AHB_DIV_2 */
#define _RCC_AHB_DIV_2 							((_rcc_bus_prescaler_t) 0x08)
/** @brief AHB division by 4 @def _RCC_AHB_DIV_4 */
#define _RCC_AHB_DIV_4 							((_rcc_bus_prescaler_t) 0x09)
/** @brief AHB division by 8 @def _RCC_AHB_DIV_8 */
#define _RCC_AHB_DIV_8 							((_rcc_bus_prescaler_t) 0x0A)
/** @brief AHB division by 16 @def _RCC_AHB_DIV_16 */
#define _RCC_AHB_DIV_16 						((_rcc_bus_prescaler_t) 0x0B)
/** @brief AHB division by 64 @def _RCC_AHB_DIV_64 */
#define _RCC_AHB_DIV_64 						((_rcc_bus_prescaler_t) 0x0C)
/** @brief AHB division by 128 @def _RCC_AHB_DIV_128 */
#define _RCC_AHB_DIV_128 						((_rcc_bus_prescaler_t) 0x0D)
/** @brief AHB division by 256 @def _RCC_AHB_DIV_256 */
#define _RCC_AHB_DIV_256 						((_rcc_bus_prescaler_t) 0x0E)
/** @brief AHB division by 512 @def _RCC_AHB_DIV_512 */
#define _RCC_AHB_DIV_512 						((_rcc_bus_prescaler_t) 0x0F)

/** @} */ // RCC_02_LL_04_Prescaler_01_AHB

/**
 * @brief		RCC Low Level APB1 Prescaler Definitions
 * @defgroup 	RCC_02_LL_04_Prescaler_02_APB1 RCC Low Level APB1 Prescaler
 * @ingroup 	RCC_02_LL_04_Prescaler
 * @details
 * - These constants define the APB1 (Advanced Peripheral Bus 1) prescaler values
 * - Used to divide the AHB clock frequency for low-speed peripherals
 * - APB1 bus connects to timers 2-7, USART2-5, I2C1-2, SPI2-3, etc.
 * - Maximum APB1 frequency is 36 MHz
 * 
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */
/** @brief APB1 division by 1 (no prescaling) @def _RCC_APB1_DIV_1 */
#define _RCC_APB1_DIV_1 							((_rcc_bus_prescaler_t) 0x00)
/** @brief APB1 division by 2 @def _RCC_APB1_DIV_2 */
#define _RCC_APB1_DIV_2 							((_rcc_bus_prescaler_t) 0x04)
/** @brief APB1 division by 4 @def _RCC_APB1_DIV_4 */
#define _RCC_APB1_DIV_4 							((_rcc_bus_prescaler_t) 0x05)
/** @brief APB1 division by 8 @def _RCC_APB1_DIV_8 */
#define _RCC_APB1_DIV_8 							((_rcc_bus_prescaler_t) 0x06)
/** @brief APB1 division by 16 @def _RCC_APB1_DIV_16 */
#define _RCC_APB1_DIV_16 							((_rcc_bus_prescaler_t) 0x07)
/** @} */ // RCC_02_LL_04_Prescaler_02_APB1

/**
 * @brief		RCC Low Level APB2 Prescaler Definitions
 * @defgroup 	RCC_02_LL_04_Prescaler_03_APB2 RCC Low Level APB2 Prescaler
 * @ingroup 	RCC_02_LL_04_Prescaler
 * @details
 * - These constants define the APB2 (Advanced Peripheral Bus 2) prescaler values
 * - Used to divide the AHB clock frequency for high-speed peripherals
 * - APB2 bus connects to GPIO ports, ADC, TIM1, TIM8, USART1, SPI1, etc.
 * - Maximum APB2 frequency is 72 MHz
 * 
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */
/** @brief APB2 division by 1 (no prescaling) @def _RCC_APB2_DIV_1 */
#define _RCC_APB2_DIV_1 							((_rcc_bus_prescaler_t) 0x00)
/** @brief APB2 division by 2 @def _RCC_APB2_DIV_2 */
#define _RCC_APB2_DIV_2 							((_rcc_bus_prescaler_t) 0x04)
/** @brief APB2 division by 4 @def _RCC_APB2_DIV_4 */
#define _RCC_APB2_DIV_4 							((_rcc_bus_prescaler_t) 0x05)
/** @brief APB2 division by 8 @def _RCC_APB2_DIV_8 */
#define _RCC_APB2_DIV_8 							((_rcc_bus_prescaler_t) 0x06)
/** @brief APB2 division by 16 @def _RCC_APB2_DIV_16 */
#define _RCC_APB2_DIV_16 							((_rcc_bus_prescaler_t) 0x07)

/** @} */ // RCC_02_LL_04_Prescaler_03_APB2

/**
 * @brief Stage AHB Prescaler configuration into @ref RCC_CFGR "RCC->CFGR" register value
 * @param[in] ahbPrescaler AHB prescaler configuration
 * @param[in] cfgrReg Current RCC_CFGR register value
 * @returns The updated staged RCC_CFGR register value with new AHB prescaler configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 */
__STATIC_FORCEINLINE uint32_t _RCC_StageAHBPrescaler(const _rcc_bus_prescaler_t ahbPrescaler, uint32_t cfgrReg)
{
	cfgrReg &= ~RCC_CFGR_HPRE;
	cfgrReg |= (uint32_t)(ahbPrescaler << RCC_CFGR_HPRE_Pos);
	return cfgrReg;
}

/**
 * @brief Stage APB1 Prescaler configuration into @ref RCC_CFGR "RCC->CFGR" register value
 * @param[in] apb1Prescaler APB1 prescaler configuration
 * @param[in] cfgrReg Current RCC_CFGR register value
 * @returns The updated staged RCC_CFGR register value with new APB1 prescaler configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 */
__STATIC_FORCEINLINE uint32_t _RCC_StageAPB1Prescaler(const _rcc_bus_prescaler_t apb1Prescaler, uint32_t cfgrReg)
{
	cfgrReg &= ~RCC_CFGR_PPRE1;
	cfgrReg |= (uint32_t)(apb1Prescaler << RCC_CFGR_PPRE1_Pos);
	return cfgrReg;
}

/**
 * @brief Stage APB2 Prescaler configuration into @ref RCC_CFGR "RCC->CFGR" register value
 * @param[in] apb2Prescaler APB2 prescaler configuration
 * @param[in] cfgrReg Current RCC_CFGR register value
 * @returns The updated staged RCC_CFGR register value with new APB2 prescaler configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 */
__STATIC_FORCEINLINE uint32_t _RCC_StageAPB2Prescaler(const _rcc_bus_prescaler_t apb2Prescaler, uint32_t cfgrReg)
{
	cfgrReg &= ~RCC_CFGR_PPRE2;
	cfgrReg |= (uint32_t)(apb2Prescaler << RCC_CFGR_PPRE2_Pos);
	return cfgrReg;
}

/**
 * @brief Stage complete Bus Prescaler configuration into @ref RCC_CFGR "RCC->CFGR" register value
 * @param[in] ahbPrescaler AHB prescaler configuration
 * @param[in] apb1Prescaler APB1 prescaler configuration
 * @param[in] apb2Prescaler APB2 prescaler configuration
 * @param[in] cfgrReg Current RCC_CFGR register value
 * @returns The updated staged RCC_CFGR register value with new bus prescaler configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 * @note - This combines AHB, APB1, and APB2 prescaler configurations
 */
__STATIC_FORCEINLINE uint32_t _RCC_StageBusPrescaler(const _rcc_bus_prescaler_t ahbPrescaler, const _rcc_bus_prescaler_t apb1Prescaler, const _rcc_bus_prescaler_t apb2Prescaler, uint32_t cfgrReg)
{
	cfgrReg &= ~(RCC_CFGR_PPRE2 | RCC_CFGR_PPRE1 | RCC_CFGR_HPRE);
	cfgrReg |= (uint32_t)((apb2Prescaler << RCC_CFGR_PPRE2_Pos) | (apb1Prescaler << RCC_CFGR_PPRE1_Pos) | (ahbPrescaler << RCC_CFGR_HPRE_Pos));
	return cfgrReg;
}

/** @} */ // RCC_02_LL_04_Prescaler

/*---------------------------------------------- RCC PLL ----------------------------------------------*/
/**
 * @brief		RCC Low Level PLL Configuration Definitions
 * @defgroup 	RCC_02_LL_05_PLL RCC Low Level PLL Configuration
 * @ingroup 	RCC_02_LL
 * @details
 * - These constants define the PLL (Phase Locked Loop) configuration parameters
 * - Used to configure PLL source, prescaler, and multiplication factor
 * - PLL generates high-frequency system clock from lower frequency sources
 * 
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief PLL source type definition @typedef _rcc_pll_src_t */
typedef uint8_t 								_rcc_pll_src_t;
/** @brief PLL source prescaler type definition @typedef _rcc_pll_src_psc_t */
typedef uint8_t 								_rcc_pll_src_psc_t;
/** @brief PLL multiplication factor type definition @typedef _rcc_pll_mul_t */
typedef uint8_t 								_rcc_pll_mul_t;

/**
 * @brief		RCC Low Level PLL Source Definitions
 * @defgroup 	RCC_02_LL_05_PLL_01_Source RCC Low Level PLL Source
 * @ingroup 	RCC_02_LL_05_PLL
 * @details
 * - These constants define the available clock sources for PLL input
 * - PLL can use either HSI or HSE as its input source
 * - Source selection affects PLL output frequency and stability
 * 
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief PLL source HSI (High Speed Internal) @def _RCC_PLL_SRC_HSI */
#define _RCC_PLL_SRC_HSI 						((_rcc_pll_src_t) 0x00)
/** @brief PLL source HSE (High Speed External) @def _RCC_PLL_SRC_HSE */
#define _RCC_PLL_SRC_HSE 						((_rcc_pll_src_t) 0x01)

/** @} */ // RCC_02_LL_05_PLL_01_Source

/**
 * @brief		RCC Low Level PLL Source Prescaler Definitions
 * @defgroup 	RCC_02_LL_05_PLL_02_SourcePrescaler RCC Low Level PLL Source Prescaler
 * @ingroup 	RCC_02_LL_05_PLL
 * @details
 * - These constants define the prescaler for PLL input source
 * - HSE can be divided by 1 or 2 before PLL input
 * - HSI is always divided by 2 for PLL input
 * 
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief HSI division by 2 for PLL input @def _RCC_PLL_SRC_HSI_DIV_2 */
#define _RCC_PLL_SRC_HSI_DIV_2 					((_rcc_pll_src_psc_t) 0x00)
/** @brief HSE division by 1 for PLL input @def _RCC_PLL_SRC_HSE_DIV_1 */
#define _RCC_PLL_SRC_HSE_DIV_1 					((_rcc_pll_src_psc_t) 0x00)
/** @brief HSE division by 2 for PLL input @def _RCC_PLL_SRC_HSE_DIV_2 */
#define _RCC_PLL_SRC_HSE_DIV_2 					((_rcc_pll_src_psc_t) 0x01)

/** @} */ // RCC_02_LL_05_PLL_02_SourcePrescaler

/**
 * @brief		RCC Low Level PLL Multiplication Factor Definitions
 * @defgroup 	RCC_02_LL_05_PLL_03_Multiplication RCC Low Level PLL Multiplication
 * @ingroup 	RCC_02_LL_05_PLL
 * @details
 * - These constants define the PLL multiplication factors
 * - PLL output frequency = (PLL input frequency) × (PLL multiplication factor)
 * - Valid multiplication factors range from 2 to 16
 * - PLL output must be between 16 MHz and 72 MHz
 * 
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief PLL multiplication by 2 @def _RCC_PLL_MUL_2 */
#define _RCC_PLL_MUL_2 							((_rcc_pll_mul_t) 0x00)
/** @brief PLL multiplication by 3 @def _RCC_PLL_MUL_3 */
#define _RCC_PLL_MUL_3 							((_rcc_pll_mul_t) 0x01)
/** @brief PLL multiplication by 4 @def _RCC_PLL_MUL_4 */
#define _RCC_PLL_MUL_4 							((_rcc_pll_mul_t) 0x02)
/** @brief PLL multiplication by 5 @def _RCC_PLL_MUL_5 */
#define _RCC_PLL_MUL_5 							((_rcc_pll_mul_t) 0x03)
/** @brief PLL multiplication by 6 @def _RCC_PLL_MUL_6 */
#define _RCC_PLL_MUL_6 							((_rcc_pll_mul_t) 0x04)
/** @brief PLL multiplication by 7 @def _RCC_PLL_MUL_7 */
#define _RCC_PLL_MUL_7 							((_rcc_pll_mul_t) 0x05)
/** @brief PLL multiplication by 8 @def _RCC_PLL_MUL_8 */
#define _RCC_PLL_MUL_8 							((_rcc_pll_mul_t) 0x06)
/** @brief PLL multiplication by 9 @def _RCC_PLL_MUL_9 */
#define _RCC_PLL_MUL_9 							((_rcc_pll_mul_t) 0x07)
/** @brief PLL multiplication by 10 @def _RCC_PLL_MUL_10 */
#define _RCC_PLL_MUL_10 						((_rcc_pll_mul_t) 0x08)
/** @brief PLL multiplication by 11 @def _RCC_PLL_MUL_11 */
#define _RCC_PLL_MUL_11 						((_rcc_pll_mul_t) 0x09)
/** @brief PLL multiplication by 12 @def _RCC_PLL_MUL_12 */
#define _RCC_PLL_MUL_12 						((_rcc_pll_mul_t) 0x0A)
/** @brief PLL multiplication by 13 @def _RCC_PLL_MUL_13 */
#define _RCC_PLL_MUL_13 						((_rcc_pll_mul_t) 0x0B)
/** @brief PLL multiplication by 14 @def _RCC_PLL_MUL_14 */
#define _RCC_PLL_MUL_14 						((_rcc_pll_mul_t) 0x0C)
/** @brief PLL multiplication by 15 @def _RCC_PLL_MUL_15 */
#define _RCC_PLL_MUL_15 						((_rcc_pll_mul_t) 0x0D)
/** @brief PLL multiplication by 16 @def _RCC_PLL_MUL_16 */
#define _RCC_PLL_MUL_16 						((_rcc_pll_mul_t) 0x0E)

/** @} */ // RCC_02_LL_05_PLL_03_Multiplication

/**
 * @brief Stage PLL Source configuration into RCC_CFGR register value
 * @param[in] pllSrc PLL source configuration
 * @param[in] cfgrReg Current RCC_CFGR register value
 * @returns The updated staged RCC_CFGR register value with new PLL source configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 */
__STATIC_FORCEINLINE uint32_t _RCC_StagePLLSource(const _rcc_pll_src_t pllSrc, uint32_t cfgrReg)
{
	cfgrReg &= ~RCC_CFGR_PLLSRC;
	cfgrReg |= (uint32_t)(pllSrc << RCC_CFGR_PLLSRC_Pos);
	return cfgrReg;
}

/**
 * @brief Stage PLL HSE Source Prescaler configuration into RCC_CFGR register value
 * @param[in] pllSrcPrescaler PLL HSE source prescaler configuration
 * @param[in] cfgrReg Current RCC_CFGR register value
 * @returns The updated staged RCC_CFGR register value with new PLL HSE source prescaler configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 * @note - Only applicable when PLL source is HSE
 */
__STATIC_FORCEINLINE uint32_t _RCC_StagePLLSourceHSEPrescaler(const _rcc_pll_src_psc_t pllSrcPrescaler, uint32_t cfgrReg)
{
	cfgrReg &= ~RCC_CFGR_PLLXTPRE;
	cfgrReg |= (uint32_t)(pllSrcPrescaler << RCC_CFGR_PLLXTPRE_Pos);
	return cfgrReg;
}

/**
 * @brief Stage PLL Multiplier configuration into RCC_CFGR register value
 * @param[in] pllMultiplier PLL multiplier configuration
 * @param[in] cfgrReg Current RCC_CFGR register value
 * @returns The updated staged RCC_CFGR register value with new PLL multiplier configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 */
__STATIC_FORCEINLINE uint32_t _RCC_StagePLLMultiplier(const _rcc_pll_mul_t pllMultiplier, uint32_t cfgrReg)
{
	cfgrReg &= ~RCC_CFGR_PLLMULL;
	cfgrReg |= (uint32_t)(pllMultiplier << RCC_CFGR_PLLMULL_Pos);
	return cfgrReg;
}

/**
 * @brief Stage complete PLL Parameters configuration into RCC_CFGR register value
 * @param[in] pllSrc PLL source configuration
 * @param[in] pllSrcPrescaler PLL HSE source prescaler configuration
 * @param[in] pllMultiplier PLL multiplier configuration
 * @param[in] cfgrReg Current RCC_CFGR register value
 * @returns The updated staged RCC_CFGR register value with new PLL parameters configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 * @note - This combines PLL source, HSE prescaler, and multiplier configurations
 */
__STATIC_FORCEINLINE uint32_t _RCC_StagePLLParameters(const _rcc_pll_src_t pllSrc, const _rcc_pll_src_psc_t pllSrcPrescaler, const _rcc_pll_mul_t pllMultiplier, uint32_t cfgrReg)
{
	cfgrReg &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC);
	cfgrReg |= (uint32_t)((pllMultiplier << RCC_CFGR_PLLMULL_Pos) | (pllSrcPrescaler << RCC_CFGR_PLLXTPRE_Pos) | (pllSrc << RCC_CFGR_PLLSRC_Pos));
	return cfgrReg;
}

/** @} */ // RCC_02_LL_05_PLL

/*---------------------------------------------- RCC Component Prescaler ----------------------------------------------*/

/**
 * @brief		RCC Low Level Component Prescaler Definitions
 * @defgroup 	RCC_02_LL_06_ComponentPrescaler RCC Low Level Component Prescaler
 * @ingroup 	RCC_02_LL
 * @details
 * - These constants define the prescaler values for specific peripherals
 * - Used to divide the APB2 clock for ADC and USB peripherals
 * - Each peripheral has specific prescaler requirements and limitations
 * 
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief Component prescaler type definition @typedef _rcc_component_prescaler_t */
typedef uint8_t 								_rcc_component_prescaler_t;

/**
 * @brief		RCC Low Level ADC Prescaler Definitions
 * @defgroup 	RCC_02_LL_06_ComponentPrescaler_01_ADC RCC Low Level ADC Prescaler
 * @ingroup 	RCC_02_LL_06_ComponentPrescaler
 * @details
 * - These constants define the ADC (Analog-to-Digital Converter) prescaler values
 * - Used to divide the APB2 clock frequency for ADC peripheral
 * - ADC clock must not exceed 14 MHz for accurate conversions
 * - APB2 clock is divided to generate ADC clock
 * 
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief ADC division by 2 @def _RCC_ADC_DIV_2 */
#define _RCC_ADC_DIV_2 							((_rcc_component_prescaler_t) 0x00)
/** @brief ADC division by 4 @def _RCC_ADC_DIV_4 */
#define _RCC_ADC_DIV_4 							((_rcc_component_prescaler_t) 0x01)
/** @brief ADC division by 6 @def _RCC_ADC_DIV_6 */
#define _RCC_ADC_DIV_6 							((_rcc_component_prescaler_t) 0x02)
/** @brief ADC division by 8 @def _RCC_ADC_DIV_8 */
#define _RCC_ADC_DIV_8 							((_rcc_component_prescaler_t) 0x03)

/** @} */ // RCC_02_LL_06_ComponentPrescaler_01_ADC

/**
 * @brief		RCC Low Level USB Prescaler Definitions
 * @defgroup 	RCC_02_LL_06_ComponentPrescaler_02_USB RCC Low Level USB Prescaler
 * @ingroup 	RCC_02_LL_06_ComponentPrescaler
 * @details
 * - These constants define the USB (Universal Serial Bus) prescaler values
 * - Used to generate the 48 MHz clock required for USB peripheral
 * - USB requires precise 48 MHz clock for proper operation
 * - PLL output is divided to generate USB clock
 * 
 * @see Reference Manual RM0008 - Section 7.3.2 Clock configuration register (RCC_CFGR)
 * @{
 */

/** @brief USB division by 1.5 @def _RCC_USB_DIV_1_5 */
#define _RCC_USB_DIV_1_5 						((_rcc_component_prescaler_t) 0x00)
/** @brief USB division by 1 (no prescaling) @def _RCC_USB_DIV_1 */
#define _RCC_USB_DIV_1 							((_rcc_component_prescaler_t) 0x01)

/** @} */ // RCC_02_LL_06_ComponentPrescaler_02_USB

/**
 * @brief Stage ADC Prescaler configuration into RCC_CFGR register value
 * @param[in] adcPrescaler ADC prescaler configuration
 * @param[in] cfgrReg Current RCC_CFGR register value
 * @returns The updated staged RCC_CFGR register value with new ADC prescaler configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 */
__STATIC_FORCEINLINE uint32_t _RCC_StageADCPrescaler(const _rcc_component_prescaler_t adcPrescaler, uint32_t cfgrReg)
{
	cfgrReg &= ~RCC_CFGR_ADCPRE;
	cfgrReg |= (uint32_t)(adcPrescaler << RCC_CFGR_ADCPRE_Pos);
	return cfgrReg;
}

/**
 * @brief Stage USB Prescaler configuration into RCC_CFGR register value
 * @param[in] usbPrescaler USB prescaler configuration
 * @param[in] cfgrReg Current RCC_CFGR register value
 * @returns The updated staged RCC_CFGR register value with new USB prescaler configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 */
__STATIC_FORCEINLINE uint32_t _RCC_StageUSBPrescaler(const _rcc_component_prescaler_t usbPrescaler, uint32_t cfgrReg)
{
	cfgrReg &= ~RCC_CFGR_USBPRE;
	cfgrReg |= (uint32_t)(usbPrescaler << RCC_CFGR_USBPRE_Pos);
	return cfgrReg;
}

/** @} */ // RCC_02_LL_06_ComponentPrescaler

/** @} */ // RCC_02_LL

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_LL_H_ */
