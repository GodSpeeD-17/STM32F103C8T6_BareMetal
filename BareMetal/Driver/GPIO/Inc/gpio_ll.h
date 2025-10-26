/**
 * @file    gpio_ll.h
 * @author  Shrey Shah
 * @brief   GPIO Low-Level Hardware Instruction Layer
 * @version v1.2
 * @date    24-10-2025
 *
 * @details
 * This header defines the **Low Level (LL)** GPIO API for STM32F103C8T6.
 * All functions directly map to hardware registers (CRL/CRH/ODR/IDR/BSRR/BRR)
 * and provide atomic bit-level access.
 *
 * The file is modular by design:
 * - Core LL functions are always compiled.
 * - Optional commit/IRQ layers can be enabled via compile-time flags
 * 
 */

#ifndef GPIO_LL_H_
#define GPIO_LL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*---------------------------------------------- Includes ----------------------------------------------*/
/** 
 * @brief For register mapping base types
 * @include Test
 */
#include "stm32f1xx.h"

// ######################################################################################################
// GPIO Register APIs
// ######################################################################################################

/**
 * @defgroup GPIO_01_Registers GPIO Low-Level Layer
 * @ingroup GPIO
 * 
 * @{
 */

/**
 * @defgroup GPIO_01_Registers_04_API GPIO Register Access APIs
 * @ingroup GPIO_01_Registers
 * 
 * @{
 */


/*---------------------------------------------- GPIO Clock Control ----------------------------------------------*/
/**
 * @defgroup GPIO_01_Registers_04_API_01_Clock GPIO Clock APIs
 * @ingroup GPIO_01_Registers_04_API
 * @brief Direct RCC register access for GPIO clocks
 * @{
 */

/**
 * @brief Enable GPIO peripheral clock
 * @param[in] gpio Target @ref GPIO_03_Registers_03_Memory "GPIO Port"
 */
__STATIC_FORCEINLINE void _GPIO_EnableClock(const GPIO_TypeDef* const gpio)
{
	RCC->APB2ENR.REG |= (0x01U << (RCC_APB2ENR_IOPAEN_Pos + GPIO_CLK_POS(gpio)));
}

/**
 * @brief Disable GPIO peripheral clock
 * @param[in] gpio Target @ref GPIO_03_Registers_03_Memory "GPIO Port"
 */
__STATIC_FORCEINLINE void _GPIO_DisableClock(const GPIO_TypeDef* const gpio)
{
	RCC->APB2ENR.REG &= ~(0x01U << (RCC_APB2ENR_IOPAEN_Pos + GPIO_CLK_POS(gpio)));
}

/** @} */ // GPIO_01_Registers_04_API_01_Clock

/*---------------------------------------------- GPIO Configuration ----------------------------------------------*/
/**
 * @defgroup GPIO_01_Registers_04_API_02_CRx GPIO Configuration Register APIs
 * @ingroup GPIO_01_Registers_04_API
 * @brief Direct pin mode and configuration access (CRL/CRH)
 * @{
 */

/**
 * @brief 				Reads @ref GPIO_Typdef_CRL "CRL"
 * @param[in] GPIOx		Target @ref GPIO_03_Registers_03_Memory "GPIO Port"
 * @returns				CRL
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE uint32_t _GPIO_ReadCRL(const GPIO_TypeDef* const GPIOx)
{
	return (uint32_t) GPIOx->CRL.REG;
}

/**
 * @brief				Writes @ref GPIO_Typdef_CRL "CRL"
 * @param[in] GPIOx		Target @ref GPIO_03_Registers_03_Memory "GPIO Port"
 * @param[in] value		Updated Value to be written
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE void _GPIO_WriteCRL(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->CRL.REG = value;
}

/**
 * @brief				Reads @ref GPIO_Typdef_CRH "CRH"
 * @param[in] GPIOx		Target GPIO port 
 * @returns				CRH
 * @ref GPIO_Pins_Summary "GPIO Pin Summary" 
 */
__STATIC_FORCEINLINE uint32_t _GPIO_ReadCRH(const GPIO_TypeDef* const GPIOx)
{
	return (uint32_t) GPIOx->CRH.REG;
}

/**
 * @brief				Writes @ref GPIO_Typdef_CRH "CRH"
 * @param[in] GPIOx		Target GPIO port
 * @param[in] value		Updated Value to be written
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE void _GPIO_WriteCRH(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->CRH.REG = value;
}

/** @} */ // GPIO_01_Registers_04_API_02_CRx

/*---------------------------------------------- GPIO Output Operations ----------------------------------------------*/
/**
 * @defgroup GPIO_01_Registers_04_API_03_Output GPIO Output APIs
 * @ingroup GPIO_01_Registers_04_API
 * @brief Output write operations
 * @{
 */

/**
 * @brief Writes an entire pattern to @ref GPIO_Typdef_ODR "ODR"
 * @param[in] GPIOx Target GPIO port
 * @param[in] value 32-bit port output value
 */
__STATIC_FORCEINLINE void _GPIO_WriteODR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->ODR.REG = value;
}

/**
 * @brief Writes an entire pattern to @ref GPIO_Typdef_BSRR "BSRR"
 * @param[in] GPIOx Target GPIO port
 * @param[in] value 32-bit port output value
 */
__STATIC_FORCEINLINE void _GPIO_WriteBSRR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->BSRR.REG = value;
}

/**
 * @brief Writes an entire pattern to @ref GPIO_Typdef_BRR "BRR"
 * @param[in] GPIOx Target GPIO port
 * @param[in] value 32-bit port output value
 */
__STATIC_FORCEINLINE void _GPIO_WriteBRR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->BRR.REG = value;
}

/** @} */ // GPIO_01_Registers_04_API_03_Output

/*---------------------------------------------- GPIO Input Operations ----------------------------------------------*/
/**
 * @defgroup GPIO_01_Registers_04_API_04_Input GPIO Input APIs
 * @ingroup GPIO_01_Registers_04_API
 * @brief Reads current input state from GPIO pins
 * @{
 */

/**
 * @brief Reads an entire pattern from IDR
 * @param[in] GPIOx Target GPIO port
 * @returns Status of GPIO Input
 */
__STATIC_FORCEINLINE uint32_t _GPIO_ReadIDR(const GPIO_TypeDef* const GPIOx)
{
	return (uint32_t)(GPIOx->IDR.REG);
}

/** @} */ // GPIO_01_Registers_04_API_04_Input

/*---------------------------------------------- GPIO Lock Operations ----------------------------------------------*/
/**
 * @defgroup GPIO_01_Registers_04_API_05_Lock GPIO Lock APIs
 * @ingroup GPIO_01_Registers_04_API
 * @brief Locks the state of GPIO pins until next reset
 * @{
 */

/**
 * @brief Writes an entire pattern from @ref GPIO_Typdef_LCKR "LCKR"
 * @param[in] GPIOx Target GPIO port
 */
__STATIC_FORCEINLINE uint32_t _GPIO_WriteLCKR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->LCKR.REG = value;
} 

/** @} */ // GPIO_01_Registers_04_API_05_Lock

/** @} */ // GPIO_01_Registers_04_API

/** @} */ // GPIO_01_Registers

// ######################################################################################################
// GPIO Low Level APIs
// ######################################################################################################

/**
 * @brief GPIO Low Level APIs
 * @defgroup GPIO_02_LL GPIO Low Level
 * 
 * @{
 */



 
/** @} */ // GPIO_02_LL





#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_LL_H_ */
