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

// C++ Functionality
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*---------------------------------------------- Includes ----------------------------------------------*/
/** 
 * @brief For register mapping base types
 * @include @file stm32f1xx.h 
 */
#include "stm32f1xx.h"
#include "rcc.h"

// ======================================================================================================
// GPIO Register APIs
// ======================================================================================================

/**
 * @addtogroup GPIO_01_Registers_03_API
 * @{
 */

/*---------------------------------------------- GPIO CRx ----------------------------------------------*/
/**
 * @defgroup GPIO_01_Registers_03_API_01_CRx GPIO Configuration Register
 * @ingroup GPIO_01_Registers_03_API
 * @brief APIs for GPIO Configuration Register
 * @{
 */

/**
 * @brief 				Reads @ref GPIO_CRL "GPIOx->CRL"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @returns				CRL
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE uint32_t __GPIO_ReadCRL(GPIO_TypeDef* const GPIOx)
{
	return (uint32_t) GPIOx->CRL.REG;
}

/**
 * @brief				Writes @ref GPIO_CRL "GPIOx->CRL"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Updated Value to be written
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE void __GPIO_WriteCRL(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->CRL.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref GPIO_CRL "GPIOx->CRL"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to OR with current register value
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE void __GPIO_SetCRL(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->CRL.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref GPIO_CRL "GPIOx->CRL"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to AND with current register value
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE void __GPIO_ClearCRL(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->CRL.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref GPIO_CRL "GPIOx->CRL"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to EXOR with current register value
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE void __GPIO_ToggleCRL(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->CRL.REG ^= value;
}

/**
 * @brief				Reads @ref GPIO_CRH "GPIOx->CRH"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port" 
 * @returns				CRH
 * @ref GPIO_Pins_Summary "GPIO Pin Summary" 
 */
__STATIC_FORCEINLINE uint32_t __GPIO_ReadCRH(GPIO_TypeDef* const GPIOx)
{
	return (uint32_t) GPIOx->CRH.REG;
}

/**
 * @brief				Writes @ref GPIO_CRH "GPIOx->CRH"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Updated Value to be written
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE void __GPIO_WriteCRH(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->CRH.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref GPIO_CRH "GPIOx->CRH"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to OR with current register value
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE void __GPIO_SetCRH(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->CRH.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref GPIO_CRH "GPIOx->CRH"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to AND with current register value
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE void __GPIO_ClearCRH(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->CRH.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref GPIO_CRH "GPIOx->CRH"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to EXOR with current register value
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE void __GPIO_ToggleCRH(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->CRH.REG ^= value;
}

/** @} */ // GPIO_01_Registers_03_API_01_CRx

/*---------------------------------------------- GPIO IDR ----------------------------------------------*/

/**
 * @defgroup GPIO_01_Registers_03_API_02_IDR GPIO Input Data Register
 * @ingroup GPIO_01_Registers_03_API
 * @brief APIs for GPIO Input Data Register
 * @{
 */

/**
 * @brief Reads @ref GPIO_IDR "GPIOx->IDR"
 * @param[in] GPIOx Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @returns Value read from @ref GPIO_IDR "GPIOx->IDR"
 */
__STATIC_FORCEINLINE uint32_t __GPIO_ReadIDR(GPIO_TypeDef* const GPIOx)
{
	return (uint32_t)(GPIOx->IDR.REG);
}

/**
 * @brief				Writes @ref GPIO_IDR "GPIOx->IDR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Updated Value to be written
 */
// __STATIC_FORCEINLINE void __GPIO_WriteIDR(GPIO_TypeDef* const GPIOx, const uint32_t value)
// {
// 	GPIOx->IDR.REG = value;
// }

/**
 * @brief				Performs a bitwise OR Operation on @ref GPIO_IDR "GPIOx->IDR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to OR with current register value
 */
// __STATIC_FORCEINLINE void __GPIO_SetIDR(GPIO_TypeDef* const GPIOx, const uint32_t value)
// {
// 	GPIOx->IDR.REG |= value;
// }

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref GPIO_IDR "GPIOx->IDR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to AND with current register value
 */
// __STATIC_FORCEINLINE void __GPIO_ClearIDR(GPIO_TypeDef* const GPIOx, const uint32_t value)
// {
// 	GPIOx->IDR.REG &= ~value;
// }

/**
 * @brief				Performs a bitwise EXOR Operation on @ref GPIO_IDR "GPIOx->IDR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to EXOR with current register value
 */
// __STATIC_FORCEINLINE void __GPIO_ToggleIDR(GPIO_TypeDef* const GPIOx, const uint32_t value)
// {
// 	GPIOx->IDR.REG ^= value;
// }

/** @} */ // GPIO_01_Registers_03_API_02_IDR

/*---------------------------------------------- GPIO ODR ----------------------------------------------*/

/**
 * @defgroup GPIO_01_Registers_03_API_03_ODR GPIO Output Data Register
 * @ingroup GPIO_01_Registers_03_API
 * @brief APIs for GPIO Output Data Register
 * @{
 */

/**
 * @brief Reads from @ref GPIO_ODR "GPIOx->ODR"
 * @param[in] GPIOx Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @returns Value read from @ref GPIO_ODR "GPIOx->ODR"
 */
__STATIC_FORCEINLINE uint32_t __GPIO_ReadODR(GPIO_TypeDef* const GPIOx)
{
	return (uint32_t)(GPIOx->ODR.REG);
}

/**
 * @brief Writes an entire pattern to @ref GPIO_ODR "GPIOx->ODR"
 * @param[in] GPIOx Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value Updated 32-bit @ref GPIO_ODR "GPIOx->ODR" value
 */
__STATIC_FORCEINLINE void __GPIO_WriteODR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->ODR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref GPIO_ODR "GPIOx->ODR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __GPIO_SetODR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->ODR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref GPIO_ODR "GPIOx->ODR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __GPIO_ClearODR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->ODR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref GPIO_ODR "GPIOx->ODR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __GPIO_ToggleODR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->ODR.REG ^= value;
}

/** @} */ // GPIO_01_Registers_03_API_03_ODR

/*---------------------------------------------- GPIO BSRR ----------------------------------------------*/
/**
 * @defgroup GPIO_01_Registers_03_API_04_BSRR GPIO Bit Set/Reset Register
 * @ingroup GPIO_01_Registers_03_API
 * @brief APIs for GPIO Bit Set/Reset Register
 * @{
 */

/**
 * @brief 				Reads @ref GPIO_BSRR "GPIOx->BSRR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @returns				GPIOx->BSRR register value
 */
__STATIC_FORCEINLINE uint32_t __GPIO_ReadBSRR(GPIO_TypeDef* const GPIOx)
{
	return (uint32_t) GPIOx->BSRR.REG;
}

/**
 * @brief Writes an entire pattern to @ref GPIO_BSRR "BSRR"
 * @param[in] GPIOx Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value Updated 32-bit @ref GPIO_BSRR "BSRR" value
 */
__STATIC_FORCEINLINE void __GPIO_WriteBSRR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->BSRR.REG = value;
}

/**
 * @brief				Performs a bitwise OR Operation on @ref GPIO_BSRR "GPIOx->BSRR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __GPIO_SetBSRR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->BSRR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref GPIO_BSRR "GPIOx->BSRR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __GPIO_ClearBSRR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->BSRR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref GPIO_BSRR "GPIOx->BSRR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __GPIO_ToggleBSRR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->BSRR.REG ^= value;
}

/** @} */ // GPIO_01_Registers_03_API_04_BSRR

/*---------------------------------------------- GPIO BRR ----------------------------------------------*/

/**
 * @defgroup GPIO_01_Registers_03_API_05_BRR GPIO Reset Register
 * @ingroup GPIO_01_Registers_03_API
 * @brief APIs for GPIO Reset Register
 * @{
 */

/**
 * @brief 				Reads @ref GPIO_BRR "GPIOx->BRR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @returns				GPIOx->BRR register value
 */
__STATIC_FORCEINLINE uint32_t __GPIO_ReadBRR(GPIO_TypeDef* const GPIOx)
{
	return (uint32_t) GPIOx->BRR.REG;
}

/**
 * @brief Writes an entire pattern to @ref GPIO_BRR "BRR"
 * @param[in] GPIOx Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value Updated 32-bit @ref GPIO_BRR "BRR" value
 */
__STATIC_FORCEINLINE void __GPIO_WriteBRR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->BRR.REG = value;
} 

/**
 * @brief				Performs a bitwise OR Operation on @ref GPIO_BRR "GPIOx->BRR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __GPIO_SetBRR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->BRR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref GPIO_BRR "GPIOx->BRR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __GPIO_ClearBRR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->BRR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref GPIO_BRR "GPIOx->BRR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __GPIO_ToggleBRR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->BRR.REG ^= value;
}

/** @} */ // GPIO_01_Registers_03_API_05_BRR

/*---------------------------------------------- GPIO Lock Operations ----------------------------------------------*/
/**
 * @defgroup GPIO_01_Registers_03_API_06_LCKR GPIO Lock Configuration Register
 * @ingroup GPIO_01_Registers_03_API
 * @brief APIs for GPIO Lock Configuration Register
 * @{
 */

/**
 * @brief Writes an entire pattern to @ref GPIO_LCKR "LCKR"
 * @param[in] GPIOx Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value Updated 32-bit @ref GPIO_LCKR "LCKR" value 
 */
__STATIC_FORCEINLINE void __GPIO_WriteLCKR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->LCKR.REG = value;
} 

/**
 * @brief Reads an entire pattern from @ref GPIO_LCKR "LCKR"
 * @param[in] GPIOx Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @returns Value read from @ref GPIO_LCKR "LCKR"
 */
__STATIC_FORCEINLINE uint32_t __GPIO_ReadLCKR(GPIO_TypeDef* const GPIOx)
{
	return (GPIOx->LCKR.REG);
} 

/**
 * @brief				Performs a bitwise OR Operation on @ref GPIO_LCKR "GPIOx->LCKR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to OR with current register value
 */
__STATIC_FORCEINLINE void __GPIO_SetLCKR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->LCKR.REG |= value;
}

/**
 * @brief				Performs a bitwise AND, ~ Operation on @ref GPIO_LCKR "GPIOx->LCKR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to AND with current register value
 */
__STATIC_FORCEINLINE void __GPIO_ClearLCKR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->LCKR.REG &= ~value;
}

/**
 * @brief				Performs a bitwise EXOR Operation on @ref GPIO_LCKR "GPIOx->LCKR"
 * @param[in] GPIOx		Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 * @param[in] value		Value to EXOR with current register value
 */
__STATIC_FORCEINLINE void __GPIO_ToggleLCKR(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->LCKR.REG ^= value;
}

/** @} */ // GPIO_01_Registers_03_API_06_LCKR

/** @} */ // GPIO_01_Registers_03_API

// ======================================================================================================
// GPIO Low Level APIs
// ======================================================================================================

/**
 * @addtogroup GPIO_02_LL
 * @{
 */

/*---------------------------------------------- GPIO LL Clock ----------------------------------------------*/
/**
 * @brief GPIO Low Level Clock APIs
 * @defgroup GPIO_02_LL_01_Clock GPIO LL Clock APIs
 * @ingroup GPIO_02_LL
 * @{
 */

/**
 * @brief Compute the RCC clock-enable bit position for a GPIO port
 * @details
 * Determines the <b>relative bit position</b> of a GPIO port within `RCC->APB2ENR`
 * by calculating its offset from @ref GPIOA using @ref BIT_POS() "BIT_POS()()"
 *
 * The result provides a **zero-based index** for clock-enable bit positioning.
 * This is purely compile-time arithmetic — no hardware access occurs.
 *
 * @param[in] GPIOx Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 *
 * @return Zero-based index of the GPIO port relative to @ref GPIOA
 * @see @ref BIT_POS() "BIT_POS()()" | @ref _GPIO_EnableClock() | @ref _GPIO_DisableClock()
 * @par Example:
 * @example
 * @code
 * uint32_t pos = GPIO_CLK_POS(GPIOC);  // GPIOC → index 2
 * RCC->APB2ENR |= (1U << (RCC_APB2ENR_IOPAEN_Pos + pos));
 * @endcode
 * @def GPIO_CLK_POS()
 */
#define GPIO_CLK_POS(GPIOx) 						BIT_POS((GPIOx), GPIOA, GPIO_PERIPHERAL_SIZE)

/**
 * @brief Compute the RCC clock-enable bitmask for a GPIO port
 *
 * @details
 * Generates the bitmask corresponding to a GPIO port’s enable bit in 
 * `RCC->APB2ENR` using @ref GPIO_CLK_POS to determine its bit position.
 *
 * This macro provides a ready-to-use mask for enabling or disabling
 * the clock for a specific GPIO port.
 *
 * @param[in] GPIOx Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 *
 * @return Bitmask for the GPIO port’s clock-enable bit
 *
 * @see @ref GPIO_CLK_POS()
 * @see @ref _GPIO_EnableClock
 * @see @ref _GPIO_DisableClock
 *
 * @par Example:
 * @code
 * // Enable GPIOB clock
 * RCC->APB2ENR |= GPIO_CLK_MASK(GPIOB);
 *
 * // Disable GPIOB clock
 * RCC->APB2ENR &= ~GPIO_CLK_MASK(GPIOB);
 * @endcode
 * 
 * @def GPIO_CLK_MASK
 */
#define GPIO_CLK_MASK(GPIOx) \
	((uint32_t) (0x01UL << ((RCC_APB2ENR_IOPAEN_Pos + GPIO_CLK_POS(GPIOx)) & ((uint32_t) 0x1F))))

/**
 * @brief Enable GPIO Peripheral Clock
 * @param[in] GPIOx Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 */
__STATIC_FORCEINLINE void _GPIO_EnableClock(GPIO_TypeDef* const GPIOx)
{
	(void) RCC_LL_EnableAPB2Clock(GPIO_CLK_MASK(GPIOx));
}

/**
 * @brief Disable GPIO Peripheral Clock
 * @param[in] GPIOx Target @ref GPIO_01_Registers_02_Memory "GPIO Port"
 */
__STATIC_FORCEINLINE void _GPIO_DisableClock(GPIO_TypeDef* const GPIOx)
{
	(void) RCC_LL_DisableAPB2Clock(GPIO_CLK_MASK(GPIOx));
}

/**
 * @brief Enables AFIO Clock
 */
__STATIC_FORCEINLINE void _GPIO_EnableAFIOClock(void)
{
	(void) RCC_LL_EnableAPB2Clock(RCC_APB2ENR_AFIOEN);
}

/** @} */ // GPIO_02_LL_01_Clock

/**
 * @brief GPIO Low Level Pin APIs
 * @defgroup GPIO_02_LL_02_Pin GPIO LL Pin APIs
 * @ingroup GPIO_02_LL
 * @{
 */

/**
 * @brief GPIO Pin Identifier Type
 * @section GPIO_LL_Pin_Values GPIO LL Pins
 * @{
 * @details
 * Type-safe abstraction for GPIO pin identifiers. Using a typedef allows for
 * easy portability across different microcontroller architectures and future
 * enhancements without modifying function prototypes.
 * <ul>
 * <li> <b>Current implementation</b>: `uint8_t` (0-255 range, supports up to 256 pins) </li>
 * <li> <b>Future flexibility</b>: Can change to `uint16_t` for larger pin counts </li>
 * <li> <b>Type safety</b>: Prevents accidental mixing with other integer types </li>
 * <li> <b>Documentation clarity</b>: Self-documenting pin parameters </li>
 * </ul>
 * 
 * @note Changing the underlying type requires updating only this typedef and
 *       the pin constant definitions - all function signatures remain unchanged.
 * 
 * @example
 * @code
 * // Current usage (uint8_t based):
 * _gpio_pin_t led_pin = _GPIO_PIN_13;
 * _GPIO_SetPin(GPIOA, led_pin);
 * 
 * // Future usage (if changed to uint16_t):
 * // No code changes required in function calls!
 * @endcode
 */
/** @brief GPIO Pin Data Type @typedef _gpio_pin_t */
typedef uint8_t _gpio_pin_t;
/** @brief GPIO Pin 0 @def _GPIO_PIN_0 */
#define _GPIO_PIN_0						((_gpio_pin_t)0x00)
/** @brief GPIO Pin 1 @def _GPIO_PIN_1 */
#define _GPIO_PIN_1						((_gpio_pin_t)0x01)
/** @brief GPIO Pin 2 @def _GPIO_PIN_2 */
#define _GPIO_PIN_2						((_gpio_pin_t)0x02)
/** @brief GPIO Pin 3 @def _GPIO_PIN_3 */
#define _GPIO_PIN_3						((_gpio_pin_t)0x03)
/** @brief GPIO Pin 4 @def _GPIO_PIN_4 */
#define _GPIO_PIN_4						((_gpio_pin_t)0x04)
/** @brief GPIO Pin 5 @def _GPIO_PIN_5 */
#define _GPIO_PIN_5						((_gpio_pin_t)0x05)
/** @brief GPIO Pin 6 @def _GPIO_PIN_6 */
#define _GPIO_PIN_6						((_gpio_pin_t)0x06)
/** @brief GPIO Pin 7 @def _GPIO_PIN_7 */
#define _GPIO_PIN_7						((_gpio_pin_t)0x07)
/** @brief GPIO Pin 8 @def _GPIO_PIN_8 */
#define _GPIO_PIN_8						((_gpio_pin_t)0x08)
/** @brief GPIO Pin 9 @def _GPIO_PIN_9 */
#define _GPIO_PIN_9						((_gpio_pin_t)0x09)
/** @brief GPIO Pin 10 @def _GPIO_PIN_10 */
#define _GPIO_PIN_10					((_gpio_pin_t)0x0A)
/** @brief GPIO Pin 11 @def _GPIO_PIN_11 */
#define _GPIO_PIN_11					((_gpio_pin_t)0x0B)
/** @brief GPIO Pin 12 @def _GPIO_PIN_12 */
#define _GPIO_PIN_12					((_gpio_pin_t)0x0C)
/** @brief GPIO Pin 13 @def _GPIO_PIN_13 */
#define _GPIO_PIN_13					((_gpio_pin_t)0x0D)
/** @brief GPIO Pin 14 @def _GPIO_PIN_14 */
#define _GPIO_PIN_14					((_gpio_pin_t)0x0E)
/** @brief GPIO Pin 15 @def _GPIO_PIN_15 */
#define _GPIO_PIN_15					((_gpio_pin_t)0x0F)
/** @brief GPIO Max Pin used for Masking  @def _GPIO_MAX_PIN */
#define _GPIO_MAX_PIN					_GPIO_PIN_15

/** @} */ // GPIO_LL_Pin_Values

/**
 * @brief Creates a 32-bit mask for a single GPIO Pin
 * @param[in] pin The GPIO pin number (0-15) for which the mask should be created.
 * @return A 32-bit unsigned integer pinMask
 * @note
 * - This implementation assumes a standard 16-pin port structure, as it masks the result with \c 0xFFFFUL
 * - Pins greater than 15 will result in a mask of \c 0x0000UL due to the final AND operation
 * @def GPIO_LL_GET_PIN_MASK
 */
#define GPIO_LL_GET_PIN_MASK(pin)						((uint32_t)((0x01UL << (pin)) & 0xFFFFUL))

/**
 * @brief Extracts the Pin Number (0-15) from a mask with a single bit set
 * @param[in] pinMask A non-zero 32-bit mask with exactly one bit set (e.g., 0x0020UL)
 * @return uint32_t The position of the set bit, which is the Pin Number (0-15)
 * @note This macro uses the highly optimized GCC built-in function `__builtin_ctz`
 * * @def GPIO_LL_EXTRACT_PIN_MASK
 */
#define GPIO_LL_EXTRACT_PIN_MASK(pinMask)		\
	(											\
		((pinMask) != GPIO_PIN_NONE) ?			\
		((_gpio_pin_t)(__builtin_ctz((uint32_t)((pinMask) & _GPIO_MAX_PIN)))) : \
		((_gpio_pin_t) 16)\
	)

/** @} */ // GPIO_02_LL_02_Pin

/**
 * @brief GPIO Low Level Pin Parameter APIs
 * @defgroup GPIO_02_LL_03_PinParams GPIO LL Pin Parameters APIs
 * @ingroup GPIO_02_LL
 * @{
 */

/**
 * @brief GPIO Mode Configuration Type
 * @section GPIO_LL_PinParams_Mode GPIO LL Pin Mode
 * @details
 * Type-safe abstraction for GPIO mode and speed configuration. Using a typedef allows for
 * easy portability and future enhancements without modifying function prototypes.
 * 
 * - **Encapsulates**: MODE field in CRL/CRH registers
 * - **Current implementation**: `uint8_t` (0-3 range for 4 mode types)
 * - **Future flexibility**: Can extend range if new modes are added
 * - **Type safety**: Prevents accidental mixing with configuration types
 * - **Hardware mapping**: Directly maps to 2-bit MODE field in configuration registers
 * 
 * @note Changing the underlying type requires updating only this typedef and
 *       the mode constant definitions - all function signatures remain unchanged.
 * 
 * @{
 */
/** @brief GPIO Mode LL Data Type @typedef _gpio_pin_mode_t */
typedef uint8_t _gpio_pin_mode_t;
/**
 * @section GPIO_LL_PinParams_Mode_Macros GPIO LL Pin Configuration Macros
 * @details Use this for LL
 * @{
 */
/** @brief Input mode @def _GPIO_PIN_MODE_INPUT */
#define _GPIO_PIN_MODE_INPUT						((_gpio_pin_mode_t)0x00)
/** @brief Output mode, max speed 10 MHz @def _GPIO_PIN_MODE_OUTPUT_10MHz */
#define _GPIO_PIN_MODE_OUTPUT_10MHz					((_gpio_pin_mode_t)0x01)
/** @brief Output mode, max speed 2 MHz @def _GPIO_PIN_MODE_OUTPUT_2MHz */
#define _GPIO_PIN_MODE_OUTPUT_2MHz					((_gpio_pin_mode_t)0x02)
/** @brief Output mode, max speed 50 MHz @def _GPIO_PIN_MODE_OUTPUT_50MHz */
#define _GPIO_PIN_MODE_OUTPUT_50MHz					((_gpio_pin_mode_t)0x03)
/** @} */ // GPIO_LL_PinParams_Mode_Macros
/**
 * @brief Creates a mask for the MODE field (bits 1:0 of the 4-bit block)
 * @param[in] pin The @ref GPIO_02_LL_02_Pin "GPIO Pin Number"
 * @param mode @ref GPIO_LL_PinParams_Mode_Macros "Pin Mode Value"
 * @return The final 32-bit mask value
 * @def _GPIO_PIN_MODE_GET_MASK
 */
#define _GPIO_PIN_MODE_GET_MASK(pin, mode) \
    ((uint32_t)(((uint32_t)(mode)) << (((pin) & _GPIO_PIN_7) << 2)))
/**
 * @brief Masks the MODE field (bits 1:0 of the 4-bit block)
 * @param[in] pin The @ref GPIO_02_LL_02_Pin "GPIO Pin Number"
 * @return The final 32-bit mask value
 * @def _GPIO_PIN_MODE_MASK
 */
#define _GPIO_PIN_MODE_MASK(pin) \
    ((uint32_t)(0x03UL << (((pin) & _GPIO_PIN_7) << 2)))
/**
 * @brief Creates a reset mask for the MODE field (bits 1:0 of the 4-bit block)
 * @param[in] pin The @ref GPIO_02_LL_02_Pin "GPIO Pin Number"
 * @return The final 32-bit mask value (with 2 bits set to '1')
 * @ref _GPIO_PIN_MODE_GET_MASK "GPIO Pin Mode Mask"
 * @def _GPIO_PIN_MODE_RESET_MASK
 */
#define _GPIO_PIN_MODE_RESET_MASK(pin)						_GPIO_PIN_MODE_GET_MASK(pin, 0x03)

/** @} */ // GPIO_LL_PinParams_Mode

/**
 * @brief GPIO Pin Configuration Type
 * @section GPIO_LL_PinParams_Config GPIO LL Pin Configuration 
 * @details
 * Type-safe abstraction for GPIO electrical configuration. Using a typedef allows for
 * easy portability and future enhancements without modifying function prototypes.
 * 
 * - **Encapsulates**: CNF field in CRL/CRH registers  
 * - **Current implementation**: `uint8_t` (0-3 range for 4 configuration types)
 * - **Future flexibility**: Can extend range if new configurations are added
 * - **Type safety**: Prevents accidental mixing with mode types
 * - **Context dependent**: Interpretation depends on mode (input vs output)
 * - **Hardware mapping**: Directly maps to 2-bit CNF field in configuration registers
 * 
 * @note Interpretation depends on current mode setting:
 *       - Input mode: Analog/Floating/Pull configurations
 *       - Output mode: Push-pull/Open-drain configurations
 * @{
 */
/** @brief GPIO Pin Configuration LL Data Type @typedef _gpio_pin_config_t */
typedef uint8_t _gpio_pin_config_t;
/** @brief GPIO Pull-Up/Pull-Down State @typedef _gpio_pin_pull_state_t */
typedef uint8_t _gpio_pin_pull_state_t;

/**
 * @brief Configuration setting when MODE = Input (0x00)
 * @section GPIO_LL_PinParams_CNF_Input_Macros 
 * @details Use this for LL Input Configuration 
 * @{
 */
/** @brief Input: Analog mode (CNF=0x00) @def _GPIO_PIN_CNF_INPUT_ANALOG */
#define _GPIO_PIN_CNF_INPUT_ANALOG						((_gpio_pin_config_t) 0x00)
/** @brief Input: Floating input (CNF=0x01) @def _GPIO_PIN_CNF_INPUT_FLOATING */
#define _GPIO_PIN_CNF_INPUT_FLOATING					((_gpio_pin_config_t) 0x01)
/** @brief Input: Pull-up/Pull-down (CNF=0x02) @def _GPIO_PIN_CNF_INPUT_PULL */
#define _GPIO_PIN_CNF_INPUT_PULL						((_gpio_pin_config_t) 0x02)
/** @brief Input: Reserved (CNF=0x03) @def _GPIO_PIN_CNF_INPUT_RESERVED */
#define _GPIO_PIN_CNF_INPUT_RESERVED					((_gpio_pin_config_t) 0x03)

/**
 * @brief LL Constants for setting the Pull-Up/Pull-Down state in the ODR register.
 * @section GPIO_LL_PinParams_CNF_Input_Macros_PullConfig 
 * @details Use this for LL PULL Staging 
 * @{
 */
/** @brief Sets the ODR bit to '0' for PULL-DOWN activation. @def _GPIO_PIN_CNF_INPUT_PULL_DOWN */
#define _GPIO_PIN_CNF_INPUT_PULL_DOWN					((_gpio_pin_pull_state_t) 0x00)
/** @brief Sets the ODR bit to '1' for PULL-UP activation. @def _GPIO_PIN_CNF_INPUT_PULL_UP */
#define _GPIO_PIN_CNF_INPUT_PULL_UP						((_gpio_pin_pull_state_t) 0x01)

/** @} */ // GPIO_LL_PinParams_CNF_Input_Macros_PullConfig

/** @} */ // GPIO_LL_PinParams_CNF_Input_Macros

/**
 * @brief Configuration setting when MODE = Output/AF (0x01, 0x02, 0x03)
 * @section GPIO_LL_PinParams_CNF_Output_Macros 
 * @details Use this for LL Output Configuration 
 * @{
 */
/** @brief Output: General Purpose Push-pull (CNF=0x00) @def _GPIO_PIN_CNF_OUTPUT_PP */
#define _GPIO_PIN_CNF_OUTPUT_PP							((_gpio_pin_config_t) 0x00)
/** @brief Output: General Purpose Open-drain (CNF=0x01) @def _GPIO_PIN_CNF_OUTPUT_OD */
#define _GPIO_PIN_CNF_OUTPUT_OD							((_gpio_pin_config_t) 0x01)
/** @brief Output: Alternate Function Push-pull (CNF=0x02) @def _GPIO_PIN_CNF_AF_PP */
#define _GPIO_PIN_CNF_AF_PP								((_gpio_pin_config_t) 0x02)
/** @brief Output: Alternate Function Open-drain (CNF=0x03) @def _GPIO_PIN_CNF_AF_OD */
#define _GPIO_PIN_CNF_AF_OD								((_gpio_pin_config_t) 0x03)

/** @} */ // GPIO_LL_PinParams_CNF_Output_Macros

/** @} */ // GPIO_LL_PinParams_Config_Macros

/** @} */ // GPIO_LL_PinParams_Config

/**
 * @brief Creates a mask for the CNF field (bits 3:2 of the 4-bit block).
 * @param[in] pin The @ref GPIO_02_LL_02_Pin "GPIO Pin Number"
 * @param cnf @ref GPIO_LL_PinParams_Config_Macros "Pin Configuration Value"
 * @return The final 32-bit mask value
 * @def _GPIO_PIN_CNF_GET_MASK
 */
#define _GPIO_PIN_CNF_GET_MASK(pin, cnf) \
	((uint32_t)(((uint32_t)(cnf)) << ((((pin) & _GPIO_PIN_7) << 2) + 2)))
/**
 * @brief Masks the CNF field (bits 3:2 of the 4-bit block).
 * @param[in] pin The @ref GPIO_02_LL_02_Pin "GPIO Pin Number"
 * @return The final 32-bit mask value
 * @def _GPIO_PIN_CNF_MASK
 */
#define _GPIO_PIN_CNF_MASK(pin) \
	((uint32_t)((0x03UL) << ((((pin) & _GPIO_PIN_7) << 2) + 2)))
/**
 * @brief Creates a reset mask for the CNF field (bits 3:2 of the 4-bit block).
 * @param[in] pin The @ref GPIO_02_LL_02_Pin "GPIO Pin Number" (0-15).
 * @return The final 32-bit mask value (with 2 bits set to '1').
 * @ref _GPIO_PIN_CNF_GET_MASK "GPIO Pin Configuration Mask"
 * @def _GPIO_PIN_CNF_RESET_MASK
 */
#define _GPIO_PIN_CNF_RESET_MASK(pin)							_GPIO_PIN_CNF_GET_MASK(pin, 0x03)	

/**
 * @brief Masks the CNF & MODE field (bits 3:0 of the 4-bit block)
 * @param[in] pin The @ref GPIO_02_LL_02_Pin "GPIO Pin Number"
 * @return The final 32-bit mask value
 * @def _GPIO_PIN_CNF_MODE_MASK
 */
#define _GPIO_PIN_CNF_MODE_MASK(pin) \
	((uint32_t)(0x0FUL) << (((pin) & _GPIO_PIN_7) << 2))

/** @} */ // GPIO_02_LL_03_PinParams

/**
 * @brief GPIO Low Level Lock APIs
 * @defgroup GPIO_02_LL_03_Lock GPIO LL Locking APIs
 * @ingroup GPIO_02_LL
 * @{
 */

/**
 * @brief GPIO Lock Status Type
 * @section GPIO_LL_Lock GPIO LL Lock Macros 
 * @details
 * Type-safe abstraction for GPIO lock operation results. Provides clear
 * status reporting for lock configuration operations without using enums.
 * 
 * - **0x00**: Lock operation completed successfully
 * - **0x01**: Lock operation failed (hardware verification failed)
 * - **0x02**: Lock is currently active and enforced
 * - **0x03**: Lock is not active or has been reset
 * 
 * @note Lock status is verified by reading back the LCKR register and
 *       checking the LCKK bit after the locking sequence completes.
 * 
 * @example
 * @code
 * _gpio_lock_status_t status = _GPIO_LockPin(GPIOA, _GPIO_PIN_5);
 * if (status == _GPIO_LOCK_SUCCESS) 
 * {
 *     // Pin successfully locked until next reset
 * }
 * @endcode 
 * 
 */
/** @brief GPIO Lock LL Data Type @typedef _gpio_lock_status_t */
typedef uint8_t _gpio_lock_status_t;
/** @brief Lock operation completed successfully @def _GPIO_LOCK_SUCCESS */
#define _GPIO_LOCK_SUCCESS									((_gpio_lock_status_t) 0x00)
/** @brief Lock operation failed @def _GPIO_LOCK_FAILED */
#define _GPIO_LOCK_FAILED									((_gpio_lock_status_t) 0x01)
/** @brief Lock is currently active @def _GPIO_LOCK_ENABLED */
#define _GPIO_LOCK_ENABLED									((_gpio_lock_status_t) 0x02)
/** @brief Lock is not active @def _GPIO_LOCK_DISABLED */
#define _GPIO_LOCK_DISABLED									((_gpio_lock_status_t) 0x03)

/** @} */ // GPIO_02_LL_03_Lock */

/**
 * @section GPIO_LL_Mode_Stage GPIO Low Level Mode Stage APIs
 * @ingroup GPIO_02_LL_03_PinParams
 * @{
 */

/**
 * @brief Stage GPIO Pin Mode Configuration into input register
 * @param[in] pin The @ref GPIO_02_LL_02_Pin "GPIO Pin Number"
 * @param[in] mode Value of @ref GPIO_LL_PinParams_Mode_Macros "GPIO Pin Mode"
 * @param[in] crxReg The current staged CRL/CRH (CRx) value
 * @returns The updated staged register value with Pin Mode
 * @note - Preferred usage is during batch update for configuration
 * @note - Register should be updated instance of either CRL/CRH
 * @note - Register Value to be provided as input
 * @see @ref GPIO_Pins_Mode "GPIO Pin Mode Theory"
 */
__STATIC_FORCEINLINE uint32_t _GPIO_PinStageMode(const _gpio_pin_t pin, const _gpio_pin_mode_t mode, uint32_t crxReg)
{
	crxReg &= ~_GPIO_PIN_MODE_RESET_MASK(pin);
	crxReg |= _GPIO_PIN_MODE_GET_MASK(pin, mode);
	return crxReg;
}

/**
 * @brief Stage GPIO Pin Configuration into the input register
 * @param[in] pin The @ref GPIO_02_LL_02_Pin "GPIO Pin Number"
 * @param[in] config Value of @ref GPIO_LL_PinParams_Config_Macros "GPIO Pin Configuration"
 * @param[in] crxReg The current staged CRL/CRH (CRx) value
 * @returns The updated staged register value with Pin Configuration
 * @note - Preferred usage is during batch update for configuration
 * @note - Register should be updated instance of either CRL/CRH (CRx)
 * @note - Register Value to be provided as input
 * @see @ref @ref GPIO_LL_PinParams_Config "GPIO Pin Configuration Theory"
 */
__STATIC_FORCEINLINE uint32_t _GPIO_PinStageConfig(const _gpio_pin_t pin, const _gpio_pin_config_t config, uint32_t crxReg)
{
	crxReg &= ~_GPIO_PIN_CNF_RESET_MASK(pin);
	crxReg |= _GPIO_PIN_CNF_GET_MASK(pin, config);
	return crxReg; 
}

/**
 * @brief Stage GPIO Pin Mode and Configuration into the input register
 * @param[in] pin The @ref GPIO_02_LL_02_Pin "GPIO Pin Number"
 * @param[in] mode Value of @ref GPIO_LL_PinParams_Mode_Macros "GPIO Pin Mode"
 * @param[in] config Value of @ref GPIO_LL_PinParams_Config_Macros "GPIO Pin Configuration"
 * @param[in] crxReg The current staged CRL/CRH (CRx) value
 * @returns The updated staged register value with Pin Mode and Configuration
 * @note - This function simplifies User API configuration by wrapping _GPIO_PinStageMode and _GPIO_PinStageConfig.
 * @note - Preferred usage is during batch update for configuration
 * @note - Register should be updated instance of either CRL/CRH (CRx)
 * @note - Register Value to be provided as input
 * @see @ref _GPIO_PinStageMode "GPIO Pin Mode Staging API" | @ref _GPIO_PinStageConfig "GPIO Pin Configuration Staging API"
 */
__STATIC_FORCEINLINE uint32_t _GPIO_PinStageParams(const _gpio_pin_t pin, const _gpio_pin_mode_t mode, const _gpio_pin_config_t config, uint32_t crxReg)
{
	return _GPIO_PinStageConfig(pin, config, _GPIO_PinStageMode(pin, mode, crxReg));
}

/**
 * @brief Stages the GPIO Pin to default mode
 * @param[in] pin The @ref GPIO_02_LL_02_Pin "GPIO Pin Number"
 * @param[in] crxReg The current staged CRL/CRH (CRx) value
 * @note Sets the Pin to Default (Input Floating) State
 * @note - Preferred usage is during batch update for configuration
 * @note - Register should be updated instance of either CRL/CRH (CRx)
 * @note - Register Value to be provided as input
 * @see @ref _GPIO_PinStageParams "GPIO Pin Parameters Staging API"
 */
__STATIC_FORCEINLINE uint32_t _GPIO_PinStageResetParams(const _gpio_pin_t pin, uint32_t crxReg)
{
    return _GPIO_PinStageParams(pin, _GPIO_PIN_MODE_INPUT, _GPIO_PIN_CNF_INPUT_FLOATING, crxReg);
}

/**
 * @brief Stage GPIO Pin Pull-Up/Pull-Down state into the input ODR register value
 * @param[in] pin The @ref GPIO_02_LL_02_Pin "GPIO Pin Number"
 * @param[in] pud_state Value of @ref GPIO_LL_PinParams_CNF_Input_Macros_PullConfig "Pull-Up or Pull-Down"
 * @param[in] odrReg The current staged ODR value
 * @returns The updated staged ODR register value with new PULL state
 * @note - Preferred usage is during batch update for configuration
 * @note - Register Value to be provided as input
 */
__STATIC_FORCEINLINE uint32_t _GPIO_PinStagePullConfig(const _gpio_pin_t pin, const _gpio_pin_pull_state_t pud_state, uint32_t odrReg)
{
	if(pud_state == _GPIO_PIN_CNF_INPUT_PULL_DOWN) odrReg &= ~GPIO_LL_GET_PIN_MASK(pin);
	else if (pud_state == _GPIO_PIN_CNF_INPUT_PULL_UP) odrReg |= GPIO_LL_GET_PIN_MASK(pin);
	return odrReg;
}

/** @} */ // GPIO_02_LL_03_PinParams

/*---------------------------------------------- GPIO LL Pin ----------------------------------------------*/

// /**
//  * @brief Lock GPIO pin configuration
//  * @param[in] GPIOx Target GPIO Port
//  * @param[in] pin Pin Number (0-15)
//  * @return _gpio_lock_status_t Lock operation status
//  * 
//  * @details
//  * Implements the hardware locking sequence to permanently protect GPIO pin
//  * configuration until next system reset. The function follows the exact
//  * sequence specified in the STM32F1 reference manual.
//  * 
//  * @locking_sequence
//  * The function automatically performs:
//  * 1. Write LCKR = (pin_mask | LCKK)  [LCKK = 1]
//  * 2. Write LCKR = (pin_mask)          [LCKK = 0]  
//  * 3. Write LCKR = (pin_mask | LCKK)  [LCKK = 1]
//  * 4. Read LCKK bit to verify success
//  * 
//  * @warning Once locked, the pin configuration cannot be changed until
//  *          the next system reset. Use this function with extreme caution.
//  * 
//  * @note Locking affects the entire port but only the specified pin's
//  *       configuration is protected from modification.
//  */
// __STATIC_FORCEINLINE _gpio_lock_status_t _GPIO_LockPin(GPIO_TypeDef* const GPIOx, const _gpio_pin_t pin)
// {
//     const uint32_t lock_key = BIT_MASK(16) | BIT_MASK(pin);
//     // Strict locking sequence per reference manual
//     __GPIO_WriteLCKR(GPIOx, lock_key);
//     __GPIO_WriteLCKR(GPIOx, (lock_key & ~BIT_MASK(16)));  
//     __GPIO_WriteLCKR(GPIOx, lock_key);
//     // Hardware verification
//     return (__GPIO_ReadLCKR(GPIOx) & BIT_MASK(16)) ? _GPIO_LOCK_SUCCESS : _GPIO_LOCK_FAILED;
// }

// /**
//  * @brief Check if GPIO pin configuration is locked
//  * @param[in] GPIOx Target GPIO Port
//  * @param[in] pin Pin Number (0-15)
//  * @return _gpio_lock_status_t Lock status (_GPIO_LOCK_ENABLED or _GPIO_LOCK_DISABLED)
//  * 
//  * @details
//  * Verifies whether a specific pin's configuration is currently locked by
//  * checking both the global lock status (LCKK bit) and the individual pin's
//  * lock bit in the LCKR register.
//  * 
//  * @note This function only checks the lock status - it does not attempt
//  *       to modify or verify the actual pin configuration.
//  */
// __STATIC_FORCEINLINE _gpio_lock_status_t _GPIO_IsPinLocked(const GPIO_TypeDef* const GPIOx, const _gpio_pin_t pin)
// {
//     return (__GPIO_ReadLCKR(GPIOx) & (BIT_MASK(16) | BIT_MASK(pin))) ? _GPIO_LOCK_ENABLED : _GPIO_LOCK_DISABLED;
// }

// /** @} */ // GPIO_02_LL_03_Lock

// /** @} */ // GPIO_02_LL

// C++ Functionality
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_LL_H_ */
