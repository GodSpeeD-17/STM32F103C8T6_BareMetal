/**
 * @file i2c_ll.h
 * @author Shrey Shah
 * @brief I2C Low Level Driver Header File
 * @version v1.0
 * @date 16-11-2025
 */

// Header Guards
#ifndef I2C_LL
#define I2C_LL

/** 
 * @brief For register mapping base types
 * @include @file stm32f1xx.h 
 */
#include "stm32f1xx.h"
#include "rcc_ll.h"

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
 * @brief 				Reads @ref `I2C_CR1` "I2C->CR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->CR1 register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadCR1(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->CR1.REG;
}

/**
 * @brief				Writes @ref `I2C_CR1` "I2C->CR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteCR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR1.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref `I2C_CR1` "I2C->CR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetCR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR1.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref `I2C_CR1` "I2C->CR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearCR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR1.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref `I2C_CR1` "I2C->CR1"
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
 * @brief 				Reads @ref `I2C_CR2` "I2C->CR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->CR2 register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadCR2(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->CR2.REG;
}

/**
 * @brief				Writes @ref `I2C_CR2` "I2C->CR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteCR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR2.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref `I2C_CR2` "I2C->CR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetCR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR2.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref `I2C_CR2` "I2C->CR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearCR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CR2.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref `I2C_CR2` "I2C->CR2"
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
 * @brief 				Reads @ref `I2C_OAR1` "I2C->OAR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->OAR1 register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadOAR1(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->OAR1.REG;
}

/**
 * @brief				Writes @ref `I2C_OAR1` "I2C->OAR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteOAR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR1.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref `I2C_OAR1` "I2C->OAR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetOAR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR1.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref `I2C_OAR1` "I2C->OAR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearOAR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR1.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref `I2C_OAR1` "I2C->OAR1"
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
 * @brief 				Reads @ref `I2C_OAR2` "I2C->OAR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->OAR2 register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadOAR2(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->OAR2.REG;
}

/**
 * @brief				Writes @ref `I2C_OAR2` "I2C->OAR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteOAR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR2.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref `I2C_OAR2` "I2C->OAR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetOAR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR2.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref `I2C_OAR2` "I2C->OAR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearOAR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->OAR2.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref `I2C_OAR2` "I2C->OAR2"
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
 * @brief 				Reads @ref `I2C_DR` "I2C->DR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->DR register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadDR(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->DR.REG;
}

/**
 * @brief				Writes @ref `I2C_DR` "I2C->DR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteDR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->DR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref `I2C_DR` "I2C->DR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetDR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->DR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref `I2C_DR` "I2C->DR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearDR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->DR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref `I2C_DR` "I2C->DR"
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
 * @brief 				Reads @ref `I2C_SR1` "I2C->SR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->SR1 register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadSR1(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->SR1.REG;
}

/**
 * @brief				Writes @ref `I2C_SR1` "I2C->SR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteSR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR1.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref `I2C_SR1` "I2C->SR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetSR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR1.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref `I2C_SR1` "I2C->SR1"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearSR1(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR1.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref `I2C_SR1` "I2C->SR1"
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
 * @brief 				Reads @ref `I2C_SR2` "I2C->SR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->SR2 register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadSR2(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->SR2.REG;
}

/**
 * @brief				Writes @ref `I2C_SR2` "I2C->SR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteSR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR2.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref `I2C_SR2` "I2C->SR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetSR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR2.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref `I2C_SR2` "I2C->SR2"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearSR2(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->SR2.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref `I2C_SR2` "I2C->SR2"
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
 * @brief 				Reads @ref `I2C_CCR` "I2C->CCR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->CCR register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadCCR(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->CCR.REG;
}

/**
 * @brief				Writes @ref `I2C_CCR` "I2C->CCR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteCCR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CCR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref `I2C_CCR` "I2C->CCR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetCCR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CCR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref `I2C_CCR` "I2C->CCR"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearCCR(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->CCR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref `I2C_CCR` "I2C->CCR"
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
 * @brief 				Reads @ref `I2C_TRISE` "I2C->TRISE"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @returns				I2C->TRISE register value
 */
__STATIC_FORCEINLINE uint32_t __I2C_ReadTRISE(I2C_TypeDef* const I2Cx)
{
	return (uint32_t) I2Cx->TRISE.REG;
}

/**
 * @brief				Writes @ref `I2C_TRISE` "I2C->TRISE"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Updated Value to be written
 */
__STATIC_FORCEINLINE void __I2C_WriteTRISE(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->TRISE.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref `I2C_TRISE` "I2C->TRISE"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __I2C_SetTRISE(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->TRISE.REG |= value;
}

/**
 * @brief				Performs a bitwise AND + ~ Operation on @ref `I2C_TRISE` "I2C->TRISE"
 * @param[in] I2Cx		Target @ref I2C_01_Registers "I2C Peripheral"
 * @param[in] value		Value to AND + ~ with current register value
 */
__STATIC_FORCEINLINE void __I2C_ClearTRISE(I2C_TypeDef* const I2Cx, const uint32_t value)
{
	I2Cx->TRISE.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref `I2C_TRISE` "I2C->TRISE"
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
 * @defgroup I2C_02_LL I2C Low Level APIs
 * @ingroup I2C
 * @brief I2C Low Level APIs
 * @{
 */

/**
 * @defgroup I2C_02_LL_01_Clock I2C Clock Control APIs
 * @ingroup I2C_02_LL
 * @brief I2C Clock Control Functions
 * @{
 */

/**
 * @brief Compute I2C peripheral clock bit position in RCC registers
 * @param[in] I2Cx I2C peripheral instance (I2C1, I2C2)
 * @returns Zero-based bit position relative to I2C1 clock enable bit
 * @details
 * Computes the relative position of I2C peripheral clock enable bit
 * in RCC_APB1ENR register using peripheral memory mapping.
 * 
 * **Bit Position Calculation:**
 * - I2C1: Position 0 (RCC_APB1ENR bit 21)
 * - I2C2: Position 1 (RCC_APB1ENR bit 22)
 * 
 * @note Result must be added to RCC_APB1ENR_I2C1EN_Pos for actual register bit position
 * @see @ref `BIT_POS`() for underlying computation algorithm
 * @def I2C_CLK_POS()
 */
#define I2C_CLK_POS(I2Cx)							BIT_POS((I2Cx), I2C1, I2C_PERIPHERAL_SIZE)

/**
 * @brief Generate I2C peripheral clock enable/disable bit mask
 * @param[in] I2Cx I2C peripheral instance (I2C1, I2C2)
 * @returns Bit mask for RCC_APB1ENR register to control I2C clock
 * @details
 * Computes the complete bit mask for enabling/disabling I2C peripheral clock
 * in RCC_APB1ENR register. The mask positions the bit at the correct offset
 * based on the peripheral instance.
 * 
 * **Register Bit Mapping:**
 * - I2C1: RCC_APB1ENR bit 21 (0x00200000)
 * - I2C2: RCC_APB1ENR bit 22 (0x00400000)
 * 
 * **Usage:**
 * @code
 * // Enable clock
 * RCC->APB1ENR.REG |= I2C_CLK_MASK(I2C1);
 * 
 * // Disable clock  
 * RCC->APB1ENR.REG &= ~I2C_CLK_MASK(I2C2);
 * 
 * // Check clock status
 * if(RCC->APB1ENR.REG & I2C_CLK_MASK(I2C1)) {
 *     // I2C1 clock is enabled
 * }
 * @endcode
 * 
 * @note This macro generates compile-time constant when used with constant I2C instances
 * @warning Do not use with invalid I2C peripheral pointers
 * @def I2C_CLK_MASK()
 */
#define I2C_CLK_MASK(I2Cx) \
	((uint32_t) (0x01UL << ((RCC_APB1ENR_I2C1EN_Pos + I2C_CLK_POS(I2Cx)) & ((uint32_t) 0x1F))))

/**
 * @brief Enable I2C Peripheral Clock
 * @param[in] I2Cx Target @ref I2C_Registers_Memory_Peripherals "I2C Peripheral"
 */	
__STATIC_FORCEINLINE _I2C_EnableClock(I2C_TypeDef* const I2Cx)
{
	(void) RCC_LL_EnableAPB1Clock(I2C_CLK_MASK(I2Cx));
}

/**
 * @brief Disable I2C Peripheral Clock
 * @param[in] I2Cx Target @ref I2C_Registers_Memory_Peripherals "I2C Peripheral"
 */	
__STATIC_FORCEINLINE _I2C_DisableClock(I2C_TypeDef* const I2Cx)
{
	(void) RCC_LL_DisableAPB1Clock(I2C_CLK_MASK(I2Cx));
}

/** @} */ // I2C_02_LL_01_Clock

/**
 * @defgroup I2C_02_LL_02_Peripheral I2C Peripheral Control APIs
 * @ingroup I2C_02_LL
 * @brief I2C Peripheral Control Functions
 * @{
 */

/**
 * @brief Enable I2C Peripheral
 * @param[in] I2Cx Target @ref I2C_01_Registers_02_Memory "I2C Peripheral"
 */
__STATIC_FORCEINLINE _I2C_Enable(I2C_TypeDef* const I2Cx)
{
	__I2C_SetCR1(I2Cx, I2C_CR1_PE);
}

/**
 * @brief Disable I2C Peripheral
 * @param[in] I2Cx Target @ref I2C_01_Registers_02_Memory "I2C Peripheral"
 */
__STATIC_FORCEINLINE _I2C_Disable(I2C_TypeDef* const I2Cx)
{
	__I2C_ClearCR1(I2Cx, I2C_CR1_PE);
}

/** @} */ // I2C_02_LL_02_Peripheral

/*---------------------------------------------- I2C Protocol Configuration ----------------------------------------------*/ 

/**
 * @defgroup I2C_02_LL_03_Protocol I2C Protocol Configuration Structure
 * @ingroup I2C_02_LL
 * @brief I2C Protocol Configuration
 * @{
 */

/**
 * @defgroup I2C_02_LL_03_Protocol_01_SpeedMode I2C Speed Mode Definitions
 * @ingroup I2C_02_LL
 * @brief I2C Speed Mode Definitions
 * @{
 */

/** @brief I2C protocol speed mode type definition @typedef i2c_protocol_speed_mode_t */
typedef uint8_t									_i2c_protocol_speed_mode_t;
/** @brief Standard Mode (up to 100 kHz) @def I2C_PROTOCOL_SPEED_MODE_SM */
#define _I2C_PROTOCOL_SPEED_MODE_SM				((_i2c_protocol_speed_mode_t) (0x00))
/** @brief Fast Mode (up to 400 kHz) @def I2C_PROTOCOL_SPEED_MODE_FM */
#define _I2C_PROTOCOL_SPEED_MODE_FM				((_i2c_protocol_speed_mode_t) (0x01)) 

/**
 * @brief Stage I2C Speed Mode into CCR Register Value
 * @param[in] i2cMode Target @ref _i2c_protocol_speed_mode_t "I2C Speed Mode"
 * @param[in] ccrReg Current CCR Register Value
 * @returns Updated CCR Register Value with staged Speed Mode
 */
__STATIC_FORCEINLINE uint32_t _I2C_StageProtocolSpeedMode(const _i2c_protocol_speed_mode_t i2cMode, uint32_t ccrReg)
{
	switch(i2cMode)
	{
		case _I2C_PROTOCOL_SPEED_MODE_SM:
			ccrReg &= ~I2C_CCR_FS;
		break;
		case _I2C_PROTOCOL_SPEED_MODE_FM:
			ccrReg |= I2C_CCR_FS;
		break;
	}
	return ccrReg;
}

/** @} */ // I2C_02_LL_03_Protocol_01_SpeedMode

/**
 * @brief    I2C Fast Mode Duty Cycle Configuration
 * @defgroup I2C_02_LL_03_Protocol_02_SpeedFMDuty I2C Fast Mode Duty Cycle
 * @ingroup  I2C_02_LL_02_Protocol
 * @details
 * - Defines duty cycle options for I2C Fast Mode operation
 * - Controls the Thigh/Tlow ratio for SCL signal in Fast Mode
 * - Available only when Fast Mode is selected
 *
 * **Duty Cycle Options:**
 * - 2:1 duty cycle: Thigh = 2 × Tlow (33% duty)
 * - 16:9 duty cycle: Thigh = 16/9 × Tlow (64% duty)
 *
 * @see Reference Manual RM0008 - Section 24.4.5 I2C clock generation
 * @see @ref I2C_02_LL_02_Protocol_01_SpeedMode for speed mode selection
 * @{
 */

/**
 * \section I2C_Driver_ProtocolSpeedFMDuty_Definitions I2C Driver Fast Mode Duty Cycle Definitions
 * \brief I2C Fast Mode Duty Cycle Configuration
 */
/** @brief I2C Fast Mode duty cycle type definition @typedef _i2c_protocol_speed_fm_duty_t */
typedef uint8_t									_i2c_protocol_speed_fm_duty_t;
/** @brief 2:1 duty cycle (Thigh = 2 × Tlow) @def I2C_PROTOCOL_SPEED_FM_DUTY_2_1 */
#define _I2C_PROTOCOL_SPEED_FM_DUTY_2_1			((_i2c_protocol_speed_fm_duty_t) (0x00))
/** @brief 16:9 duty cycle (Thigh = 16/9 × Tlow) @def I2C_PROTOCOL_SPEED_FM_DUTY_16_9 */
#define _I2C_PROTOCOL_SPEED_FM_DUTY_16_9		((_i2c_protocol_speed_fm_duty_t) (0x01))

/**
 * @brief Stage I2C Speed Fm Duty into CCR Register Value
 * @param[in] i2cFmDuty Target @ref _i2c_protocol_speed_fm_duty_t "I2C Speed Fm Duty"
 * @param[in] ccrReg Current CCR Register Value
 * @returns Updated CCR Register Value with staged Speed Mode
 */
__STATIC_FORCEINLINE uint32_t _I2C_StageProtocolSpeedFmDuty(const _i2c_protocol_speed_fm_duty_t i2cFmDuty, uint32_t ccrReg)
{
	switch(i2cFmDuty)
	{
		case _I2C_PROTOCOL_SPEED_FM_DUTY_2_1:
			ccrReg &= ~I2C_CCR_DUTY;
		break;
		case _I2C_PROTOCOL_SPEED_FM_DUTY_16_9:
			ccrReg |= I2C_CCR_DUTY;
		break;
	}
	return ccrReg;
}

/** @} */ // I2C_02_LL_03_Protocol_02_SpeedFMDuty

/**
 * @brief    I2C Acknowledgment Configuration
 * @defgroup I2C_02_LL_03_Protocol_03_Ack I2C Acknowledgment Control
 * @ingroup  I2C_02_LL_03_Protocol
 * @details
 * - Controls I2C acknowledgment generation for slave devices
 * - When enabled, slave generates ACK after each byte reception
 * - When disabled, slave does not generate ACK (used in some advanced scenarios)
 * - Typically kept enabled for normal operation
 *
 * @see Reference Manual RM0008 - Section 24.6.1 Control register 1 (I2C_CR1)
 * @{
 */

/** @brief I2C acknowledgment control type definition @typedef i2c_protocol_ack_t */
typedef uint8_t									_i2c_protocol_ack_t;
/** @brief Acknowledgment disabled @def I2C_PROTOCOL_ACK_DISABLE */
#define _I2C_PROTOCOL_ACK_DISABLE				((_i2c_protocol_ack_t) (0x00))
/** @brief Acknowledgment enabled @def I2C_PROTOCOL_ACK_ENABLE */
#define _I2C_PROTOCOL_ACK_ENABLE				((_i2c_protocol_ack_t) (0x01)) 

/**
 * @brief Stage I2C ACK into CR1 Register Value
 * @param[in] i2cAck Target @ref _i2c_protocol_ack_t "I2C ACK State"
 * @param[in] cr1Reg Current CR1 Register Value
 * @returns Updated CR1 Register Value with staged Speed Mode
 */
__STATIC_FORCEINLINE uint32_t _I2C_StageProtocolAck(const _i2c_protocol_ack_t i2cAck, uint32_t cr1Reg)
{
	switch(i2cAck)
	{
		case _I2C_PROTOCOL_ACK_DISABLE:
			cr1Reg &= ~I2C_CR1_ACK;
		break;
		case _I2C_PROTOCOL_ACK_ENABLE:
			cr1Reg |= I2C_CR1_ACK;
		break;
	}
	return cr1Reg;
}

/** @} */ // I2C_02_LL_03_Protocol_03_Ack

/**
 * @brief    I2C Clock Stretching Configuration
 * @defgroup I2C_02_LL_03_Protocol_04_Stretch I2C Clock Stretching Control
 * @ingroup  I2C_02_LL_03_Protocol
 * @details
 * - Controls I2C clock stretching capability for slave devices
 * - When enabled, slave can hold SCL low to delay communication
 * - When disabled, slave cannot stretch clock (useful for some masters)
 * - Typically enabled to allow slaves time to process data
 *
 * @see Reference Manual RM0008 - Section 24.4.6 Clock stretching
 * @{
 * \section I2C_Driver_ProtocolStretch_Definitions I2C Driver Clock Stretching Definitions
 * \brief I2C Clock Stretching Configuration
 */

/** @brief I2C clock stretching control type definition @typedef i2c_protocol_stretch_t */
typedef uint8_t									_i2c_protocol_stretch_t;
/** @brief Clock stretching disabled @def I2C_PROTOCOL_STRETCH_DISABLE */
#define _I2C_PROTOCOL_STRETCH_DISABLE			((_i2c_protocol_stretch_t) (0x00))
/** @brief Clock stretching enabled @def I2C_PROTOCOL_STRETCH_ENABLE */
#define _I2C_PROTOCOL_STRETCH_ENABLE			((_i2c_protocol_stretch_t) (0x01))

/**
 * @brief Stage I2C Stretching into CR1 Register Value
 * @param[in] i2cStretch Target @ref _i2c_protocol_ack_t "I2C Stretch Mode"
 * @param[in] cr1Reg Current CR1 Register Value
 * @returns Updated CR1 Register Value with staged Speed Mode
 */
__STATIC_FORCEINLINE uint32_t _I2C_StageProtocolStretch(const _i2c_protocol_stretch_t i2cStretch, uint32_t cr1Reg)
{
	switch(i2cStretch)
	{
		case _I2C_PROTOCOL_STRETCH_DISABLE:
			cr1Reg &= ~I2C_CR1_NOSTRETCH;
		break;
		case _I2C_PROTOCOL_STRETCH_ENABLE:
			cr1Reg |= I2C_CR1_NOSTRETCH;
		break;
	}
	return cr1Reg;
}

/** @} */ // I2C_02_LL_03_Protocol_04_Stretch

/** @} */ // I2C_02_LL_03_Protocol

/** @} */ // I2C_02_LL

#endif /* I2C_LL */
