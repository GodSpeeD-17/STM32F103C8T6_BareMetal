/**
 * @file i2c_ll.h
 * @author Shrey Shah
 * @brief 
 * @version v1.0
 * @date 16-11-2025
 */

// Header Guards
#ifndef I2C_LL_H_
#define I2C_LL_H_

/** 
 * @brief For register mapping base types
 * @include @file stm32f1xx.h 
 */
#include "stm32f1xx.h"

// ======================================================================================================
// I2C Register APIs
// ======================================================================================================

/**
 * @addtogroup I2C_01_Registers_03_API
 * @{
 */

/*---------------------------------------------- I2C CR1 ----------------------------------------------*/

/**
 * @defgroup I2C_01_Registers_03_API_01_CR1 Control Register 1
 * @ingroup I2C_01_Registers_03_API
 * @brief APIs for I2C Control Register 1
 * @{
 */

/**
 * @brief 				Reads @ref I2C_CR1 "I2C->CR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->CR1 register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadCR1(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->CR1.REG;
}

/**
 * @brief				Writes @ref I2C_CR1 "I2C->CR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteCR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR1.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref I2C_CR1 "I2C->CR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetCR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR1.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref I2C_CR1 "I2C->CR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearCR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR1.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref I2C_CR1 "I2C->CR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __I2C_ToggleCR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR1.REG ^= value;
}

/** @} */ // I2C_01_Registers_03_API_01_CR1

/*---------------------------------------------- I2C CR2 ----------------------------------------------*/

/**
 * @defgroup I2C_01_Registers_03_API_02_CR2 Control Register 2
 * @ingroup I2C_01_Registers_03_API
 * @brief APIs for I2C Control Register 2
 * @{
 */

/**
 * @brief 				Reads @ref I2C_CR2 "I2C->CR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->CR2 register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadCR2(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->CR2.REG;
}

/**
 * @brief				Writes @ref I2C_CR2 "I2C->CR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteCR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR2.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref I2C_CR2 "I2C->CR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetCR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR2.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref I2C_CR2 "I2C->CR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearCR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR2.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref I2C_CR2 "I2C->CR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __I2C_ToggleCR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR2.REG ^= value;
}

/** @} */ // I2C_01_Registers_03_API_02_CR2

/*---------------------------------------------- I2C OAR1 ----------------------------------------------*/

/**
 * @defgroup I2C_01_Registers_03_API_03_OAR1 Own Address Register 1
 * @ingroup I2C_01_Registers_03_API
 * @brief APIs for I2C Own Address Register 1
 * @{
 */

/**
 * @brief 				Reads @ref I2C_OAR1 "I2C->OAR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->OAR1 register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadOAR1(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->OAR1.REG;
}

/**
 * @brief				Writes @ref I2C_OAR1 "I2C->OAR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteOAR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR1.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref I2C_OAR1 "I2C->OAR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetOAR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR1.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref I2C_OAR1 "I2C->OAR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearOAR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR1.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref I2C_OAR1 "I2C->OAR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __I2C_ToggleOAR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR1.REG ^= value;
}

/** @} */ // I2C_01_Registers_03_API_03_OAR1

/*---------------------------------------------- I2C OAR2 ----------------------------------------------*/

/**
 * @defgroup I2C_01_Registers_03_API_04_OAR2 Own Address Register 2
 * @ingroup I2C_01_Registers_03_API
 * @brief APIs for I2C Own Address Register 2
 * @{
 */

/**
 * @brief 				Reads @ref I2C_OAR2 "I2C->OAR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->OAR2 register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadOAR2(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->OAR2.REG;
}

/**
 * @brief				Writes @ref I2C_OAR2 "I2C->OAR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteOAR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR2.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref I2C_OAR2 "I2C->OAR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetOAR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR2.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref I2C_OAR2 "I2C->OAR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearOAR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR2.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref I2C_OAR2 "I2C->OAR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __I2C_ToggleOAR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR2.REG ^= value;
}

/** @} */ // I2C_01_Registers_03_API_04_OAR2

/*---------------------------------------------- I2C DR ----------------------------------------------*/

/**
 * @defgroup I2C_01_Registers_03_API_05_DR Data Register
 * @ingroup I2C_01_Registers_03_API
 * @brief APIs for I2C Data Register
 * @{
 */

/**
 * @brief 				Reads @ref I2C_DR "I2C->DR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->DR register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadDR(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->DR.REG;
}

/**
 * @brief				Writes @ref I2C_DR "I2C->DR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteDR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->DR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref I2C_DR "I2C->DR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetDR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->DR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref I2C_DR "I2C->DR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearDR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->DR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref I2C_DR "I2C->DR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __I2C_ToggleDR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->DR.REG ^= value;
}

/** @} */ // I2C_01_Registers_03_API_05_DR

/*---------------------------------------------- I2C SR1 ----------------------------------------------*/

/**
 * @defgroup I2C_01_Registers_03_API_06_SR1 Status Register 1
 * @ingroup I2C_01_Registers_03_API
 * @brief APIs for I2C Status Register 1
 * @{
 */

/**
 * @brief 				Reads @ref I2C_SR1 "I2C->SR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->SR1 register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadSR1(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->SR1.REG;
}

/**
 * @brief				Writes @ref I2C_SR1 "I2C->SR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteSR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR1.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref I2C_SR1 "I2C->SR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetSR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR1.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref I2C_SR1 "I2C->SR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearSR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR1.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref I2C_SR1 "I2C->SR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __I2C_ToggleSR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR1.REG ^= value;
}

/** @} */ // I2C_01_Registers_03_API_06_SR1

/*---------------------------------------------- I2C SR2 ----------------------------------------------*/

/**
 * @defgroup I2C_01_Registers_03_API_07_SR2 Status Register 2
 * @ingroup I2C_01_Registers_03_API
 * @brief APIs for I2C Status Register 2
 * @{
 */

/**
 * @brief 				Reads @ref I2C_SR2 "I2C->SR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->SR2 register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadSR2(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->SR2.REG;
}

/**
 * @brief				Writes @ref I2C_SR2 "I2C->SR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteSR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR2.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref I2C_SR2 "I2C->SR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetSR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR2.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref I2C_SR2 "I2C->SR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearSR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR2.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref I2C_SR2 "I2C->SR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __I2C_ToggleSR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR2.REG ^= value;
}

/** @} */ // I2C_01_Registers_03_API_07_SR2

/*---------------------------------------------- I2C CCR ----------------------------------------------*/

/**
 * @defgroup I2C_01_Registers_03_API_08_CCR Clock Control Register
 * @ingroup I2C_01_Registers_03_API
 * @brief APIs for I2C Clock Control Register
 * @{
 */

/**
 * @brief 				Reads @ref I2C_CCR "I2C->CCR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->CCR register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadCCR(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->CCR.REG;
}

/**
 * @brief				Writes @ref I2C_CCR "I2C->CCR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteCCR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CCR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref I2C_CCR "I2C->CCR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetCCR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CCR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref I2C_CCR "I2C->CCR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearCCR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CCR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref I2C_CCR "I2C->CCR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __I2C_ToggleCCR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CCR.REG ^= value;
}

/** @} */ // I2C_01_Registers_03_API_08_CCR

/*---------------------------------------------- I2C TRISE ----------------------------------------------*/

/**
 * @defgroup I2C_01_Registers_03_API_09_TRISE TRISE Register
 * @ingroup I2C_01_Registers_03_API
 * @brief APIs for I2C TRISE Register
 * @{
 */

/**
 * @brief 				Reads @ref I2C_TRISE "I2C->TRISE"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->TRISE register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadTRISE(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->TRISE.REG;
}

/**
 * @brief				Writes @ref I2C_TRISE "I2C->TRISE"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteTRISE(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->TRISE.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref I2C_TRISE "I2C->TRISE"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetTRISE(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->TRISE.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref I2C_TRISE "I2C->TRISE"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearTRISE(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->TRISE.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref I2C_TRISE "I2C->TRISE"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __I2C_ToggleTRISE(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->TRISE.REG ^= value;
}

/** @} */ // I2C_01_Registers_03_API_09_TRISE

/** @} */ // I2C_01_Registers_03_API 

// ======================================================================================================
// I2C Low Level APIs
// ======================================================================================================

/**
 * @addtogroup I2C_02_LL
 * @{
 */

 

/** @} */ // I2C_02_LL

#endif /* I2C_LL_H_ */
