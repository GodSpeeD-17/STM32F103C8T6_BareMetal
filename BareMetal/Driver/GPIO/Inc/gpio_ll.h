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
 * - Optional commit/IRQ layers can be enabled via compile-time flags.
 * 
 * @defgroup GPIO_LL GPIO Low-Level Hardware Instruction Layer
 * @ingroup GPIO
 */

#ifndef GPIO_LL_H_
#define GPIO_LL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*---------------------------------------------- Includes ----------------------------------------------*/
#include "gpio_types.h"

/*---------------------------------------------- Macros ----------------------------------------------*/
#define GPIO_CLK_POS(GPIOx)						BIT_POS(GPIOx, GPIOA, GPIO_TypeDef)

/*---------------------------------------------- GPIO Clock Control ----------------------------------------------*/
/**
 * @section GPIO_LL_ClockAPI
 * @defgroup GPIO_LL_Clock GPIO LL Clock Control
 * @ingroup GPIO_LL
 * @brief Direct RCC register access for GPIO clocks.
 * @{
 */

/**
 * @brief Enable GPIO peripheral clock
 *
 * @param[in] gpio Target GPIO port (`GPIOA` – `GPIOG`)
 */
__STATIC_FORCEINLINE void _GPIO_EnableClock(const GPIO_TypeDef* const gpio)
{
	RCC->APB2ENR.REG |= (0x01U << (RCC_APB2ENR_IOPAEN_Pos + GPIO_CLK_POS(gpio)));
}

/**
 * @brief Disable GPIO peripheral clock
 *
 * @param[in] gpio Target GPIO port (`GPIOA` – `GPIOG`)
 */
__STATIC_FORCEINLINE void _GPIO_DisableClock(const GPIO_TypeDef* const gpio)
{
	RCC->APB2ENR.REG &= ~(0x01U << (RCC_APB2ENR_IOPAEN_Pos + GPIO_CLK_POS(gpio)));
}

/** @} */ // GPIO_LL_Clock

/*---------------------------------------------- GPIO Configuration ----------------------------------------------*/
/**
 * @defgroup GPIO_LL_Config GPIO LL Configuration
 * @ingroup GPIO_LL
 * @brief Direct pin mode and configuration access (CRL/CRH)
 * @{
 */

/**
 * @brief Read CRL
 * @param[in] GPIOx    Target GPIO port
 * @returns CRL
 * 
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE uint32_t _GPIO_ReadCRL(const GPIO_TypeDef* const GPIOx)
{
	return (uint32_t) GPIOx->CRL.REG;
}

/**
 * @brief				Writes CRL
 * @param[in] GPIOx		Target GPIO port
 * @param[in] value		Updated Value to be written
 * 
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE void _GPIO_WriteCRL(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->CRL.REG = value;
}

/**
 * @brief				Read CRH
 * @param[in] GPIOx		Target GPIO port 
 * @returns				CRH
 * 
 * @ref GPIO_Pins_Summary "GPIO Pin Summary" 
 */
__STATIC_FORCEINLINE uint32_t _GPIO_ReadCRH(const GPIO_TypeDef* const GPIOx)
{
	return (uint32_t) GPIOx->CRH.REG;
}

/**
 * @brief				Writes CRH
 *
 * @param[in] GPIOx		Target GPIO port
 * @param[in] value		Updated Value to be written
 * 
 * @ref GPIO_Pins_Summary "GPIO Pin Summary"
 */
__STATIC_FORCEINLINE void _GPIO_WriteCRH(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->CRH.REG = value;
}

/** @} */ // GPIO_LL_Config

/*---------------------------------------------- GPIO Output Operations ----------------------------------------------*/
/**
 * @defgroup GPIO_LL_Output GPIO LL Output
 * @ingroup GPIO_LL
 * @brief Atomic pin and port write operations
 * 
 * @{
 */

/**
 * @brief Sets specified GPIO pin
 *
 * @param[in] GPIOx Target GPIO port
 * @param[in] pin   Pin Number
 */
__STATIC_FORCEINLINE void _GPIO_SetPin(GPIO_TypeDef *GPIOx, const uint8_t pin)
{
	GPIOx->BSRR.REG |= (uint32_t)(0x01UL << pin);
}

/**
 * @brief Toggles output pin
 *
 * @param[in] GPIOx Target GPIO port
 * @param[in] pin   Pin Number
 */
__STATIC_FORCEINLINE void _GPIO_TogglePin(GPIO_TypeDef* const GPIOx, const uint8_t pin)
{
	GPIOx->ODR.REG ^= (uint32_t)(0x01UL <<pin);
}

/**
 * @brief Writes an entire pattern to GPIO Port
 *
 * @param[in] GPIOx Target GPIO port
 * @param[in] value 32-bit port output value
 */
__STATIC_FORCEINLINE void _GPIO_WritePort(GPIO_TypeDef* const GPIOx, const uint32_t value)
{
	GPIOx->ODR.REG = value;
}

/** @} */ // GPIO_LL_Output

/*---------------------------------------------- GPIO Input Operations ----------------------------------------------*/
/**
 * @defgroup GPIO_LL_Input GPIO LL Input
 * @ingroup GPIO_LL
 * @brief Reads current input state from GPIO pins
 * @{
 */

/**
 * @brief Get specified GPIO pin status
 *
 * @param[in] GPIOx Target GPIO port
 * @param[in] pin   Pin Number
 * 
 * @returns Status of GPIO Pin:
 * @returns - `0x00`: GPIO Pin Reset 
 * @returns - `0x01`: GPIO Pin Set 
 */
__STATIC_FORCEINLINE uint8_t _GPIO_GetPin(GPIO_TypeDef *GPIOx, const uint8_t pin)
{
	return ((uint8_t)((GPIOx->IDR.REG >> pin) & 0x01));
}
 
/**
 * @brief Gets entire pattern of GPIO Port
 * @param[in] GPIOx Target GPIO port
 * @returns Status of GPIO Port
 */
__STATIC_FORCEINLINE uint32_t _GPIO_GetPort(const GPIO_TypeDef* const GPIOx)
{
	return (uint32_t)(GPIOx->IDR.REG);
}

/** @} */ // GPIO_LL_Input

/*---------------------------------------------- GPIO Pull Control ----------------------------------------------*/
/**
 * @defgroup GPIO_LL_Pull GPIO LL Pull Control
 * @ingroup GPIO_LL
 * @brief Configure internal pull-up/pull-down resistors.
 * @{
 */

/**
 * @brief Enables pull-up resistor on selected pins
 * @param[in] GPIOx Target GPIO port
 * @param[in] pin   Bitmask of pins
 */
__STATIC_FORCEINLINE void _GPIO_SetPullUp(GPIO_TypeDef* const GPIOx, const uint8_t pin)
{
	GPIOx->BSRR.REG |= (uint32_t)(0x01UL << pin);
}

/**
 * @brief Enables pull-down resistor on selected pins
 * @param[in] GPIOx Target GPIO port
 * @param[in] pin   Bitmask of pins
 */
__STATIC_FORCEINLINE void _GPIO_SetPullDown(GPIO_TypeDef* const GPIOx, const uint8_t pin)
{
	GPIOx->BRR.REG |= (uint32_t)(0x01UL << pin);
}

/** @} */ // GPIO_LL_Pull


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_LL_H_ */
