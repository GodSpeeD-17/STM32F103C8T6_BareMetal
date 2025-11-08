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

/** @} */ // RCC_02_LL

#ifdef __cplusplus
}
#endif /* __cplusplus */



#endif /* RCC_LL_H_ */
