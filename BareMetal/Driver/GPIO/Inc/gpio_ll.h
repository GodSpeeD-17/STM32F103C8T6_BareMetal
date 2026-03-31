/**
 * @file	gpio_ll.h
 * @author	Shrey Shah
 * @brief	GPIO Low-Level Control Interface
 * @version	v2.1
 * @date	29-03-2026
 *
 * @details
 * This header defines the Layer 1 GPIO low-level interface that sits directly
 * above the register-layer definitions from @ref stm32f1xx_gpio.h.
 *
 * The GPIO LL layer owns only direct hardware-facing actions:
 * - GPIO register access macros built on the generic register utilities
 * - enabling or disabling the RCC clock gates required by GPIO
 *
 * The GPIO LL layer does not own:
 * - public GPIO selector vocabulary
 * - mode and configuration translation logic
 * - driver validation and compatibility checks
 * - board-specific behavior
 *
 * Practical Layering Rule:
 * - Layer 0 (`stm32f1xx_gpio.h`) defines raw register symbols and register map.
 * - Layer 1 (`gpio_ll.h`) provides register-near access primitives using those symbols.
 * - Layer 2 (`gpio_helper.h` / `gpio_helper.c`) bridges driver-facing selectors to
 *   raw register images.
 * - Layer 3 (`gpio.h` / `gpio.c`) validates requests, stages batched updates, and
 *   sequences the required LL calls.
 */

#ifndef GPIO_LL_H_
#define GPIO_LL_H_

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//											   Includes											   //
// ==================================================================================================== //
#include "stm32f1xx.h"
#include "rcc_ll.h"

/**
 * @addtogroup GPIO_02_LL
 * @{
 */

// ==================================================================================================== //
//									 GPIO LL Register Operation Macros								//
// ==================================================================================================== //

/**
 * @brief	GPIO LL Register Operation Macros
 * @defgroup GPIO_02_LL_01_RegisterOps GPIO LL Register Operation Macros
 * @ingroup	GPIO_02_LL
 * @details
 * These macros build a thin GPIO-specific convenience layer on top of the
 * generic @ref REGOPS_READ, @ref REGOPS_WRITE, @ref REGOPS_SET,
 * @ref REGOPS_CLEAR, @ref REGOPS_TOGGLE, and @ref REGOPS_MODIFY utilities.
 *
 * Practical Rule:
 * - Always access GPIO registers through the `.REG` member.
 * - Do not use the `.BIT` view in the LL layer.
 * - Do not introduce driver-level selector values here.
 * @{
 */

/**
 * @brief Returns pointer to GPIO register `.REG` image
 * @def GPIO_LL_REG
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @returns Pointer to the selected GPIO register `.REG` image
 */
#define GPIO_LL_REG(_GPIOX, _REG)							(&((_GPIOX)->_REG.REG))

/**
 * @brief Reads full GPIO register image
 * @def GPIO_LL_READ_REG
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @param[in] _VAR Destination variable that receives the register image
 */
#define GPIO_LL_READ_REG(_GPIOX, _REG, _VAR)				REGOPS_READ(GPIO_LL_REG((_GPIOX), _REG), (_VAR))

/**
 * @brief Writes full GPIO register image
 * @def GPIO_LL_WRITE_REG
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @param[in] _VAL Register image to write
 */
#define GPIO_LL_WRITE_REG(_GPIOX, _REG, _VAL)				REGOPS_WRITE(GPIO_LL_REG((_GPIOX), _REG), (_VAL))

/**
 * @brief Sets GPIO register bits
 * @def GPIO_LL_SET_BITS
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @param[in] _MASK Bit mask to set
 */
#define GPIO_LL_SET_BITS(_GPIOX, _REG, _MASK)				REGOPS_SET(GPIO_LL_REG((_GPIOX), _REG), (_MASK))

/**
 * @brief Clears GPIO register bits
 * @def GPIO_LL_CLEAR_BITS
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @param[in] _MASK Bit mask to clear
 */
#define GPIO_LL_CLEAR_BITS(_GPIOX, _REG, _MASK)				REGOPS_CLEAR(GPIO_LL_REG((_GPIOX), _REG), (_MASK))

/**
 * @brief Toggles GPIO register bits
 * @def GPIO_LL_TOGGLE_BITS
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @param[in] _MASK Bit mask to toggle
 */
#define GPIO_LL_TOGGLE_BITS(_GPIOX, _REG, _MASK)			REGOPS_TOGGLE(GPIO_LL_REG((_GPIOX), _REG), (_MASK))

/**
 * @brief Modifies GPIO register masked field
 * @def GPIO_LL_MODIFY_REG
 * @param[in] _GPIOX Target GPIO peripheral instance
 * @param[in] _REG Register member name inside @ref GPIO_TypeDef
 * @param[in] _MASK Field mask to modify
 * @param[in] _VAL Masked field value to write
 *
 * @note `_VAL` must already be aligned to the target field position.
 */
#define GPIO_LL_MODIFY_REG(_GPIOX, _REG, _MASK, _VAL)		REGOPS_MODIFY(GPIO_LL_REG((_GPIOX), _REG), (_MASK), (_VAL))

/** @} */ // GPIO_02_LL_01_RegisterOps

// ==================================================================================================== //
//										  GPIO LL Clock Control									   //
// ==================================================================================================== //

/**
 * @brief Resolves a GPIO peripheral instance to the matching APB2 clock-gate mask
 * @param[in] GPIOx Target GPIO peripheral instance
 * @returns Matching APB2 clock-gate mask for the selected GPIO port
 * @retval `RCC_APB2ENR_IOPAEN`: GPIOA clock-gate mask
 * @retval `RCC_APB2ENR_IOPBEN`: GPIOB clock-gate mask
 * @retval `RCC_APB2ENR_IOPCEN`: GPIOC clock-gate mask
 * @retval `RCC_APB2ENR_IOPDEN`: GPIOD clock-gate mask
 * @retval `RCC_APB2ENR_IOPEEN`: GPIOE clock-gate mask
 * @retval `RCC_APB2ENR_IOPFEN`: GPIOF clock-gate mask
 * @retval `RCC_APB2ENR_IOPGEN`: GPIOG clock-gate mask
 * @retval `0x00000000UL`: @p GPIOx did not map to a supported GPIO port
 */
__STATIC_FORCEINLINE uint32_t _GPIO_LL_GetPortClockMask(const GPIO_TypeDef* const GPIOx)
{
	const uint32_t gpioIndex = BIT_POS(GPIOx, GPIOA, GPIO_PERIPHERAL_SIZE);

	switch (gpioIndex)
	{
		case 0x00UL:
		{
			return RCC_APB2ENR_IOPAEN;
		}
		case 0x01UL:
		{
			return RCC_APB2ENR_IOPBEN;
		}
		case 0x02UL:
		{
			return RCC_APB2ENR_IOPCEN;
		}
		case 0x03UL:
		{
			return RCC_APB2ENR_IOPDEN;
		}
		case 0x04UL:
		{
			return RCC_APB2ENR_IOPEEN;
		}
		case 0x05UL:
		{
			return RCC_APB2ENR_IOPFEN;
		}
		case 0x06UL:
		{
			return RCC_APB2ENR_IOPGEN;
		}
		default:
			{
				return 0x00000000UL;
			}
	}
}

/**
 * @brief	GPIO LL Clock Control
 * @defgroup GPIO_02_LL_02_ClockControl GPIO LL Clock Control
 * @ingroup	GPIO_02_LL
 * @details
 * These APIs perform the GPIO-related APB2 clock gate actions required by the
 * GPIO stack.
 *
 * The mapping remains hardware-facing:
 * - a `GPIOx` instance is converted into the matching `RCC_APB2ENR_IOPxEN` bit
 * - AFIO enable is issued using the raw `RCC_APB2ENR_AFIOEN` mask
 *
 * Practical Rule:
 * - Use these helpers only to control the underlying hardware clock gate.
 * - Keep all policy such as "when should the clock be enabled?" in the driver
 *   layer.
 * @{
 */

/**
 * @brief Enables the APB2 clock gate for a GPIO port
 * @details
 * Resolves the supplied GPIO peripheral instance to the matching APB2 enable
 * bit, then forwards that raw mask to @ref RCC_LL_EnableAPB2Clock.
 *
 * @param[in] GPIOx Target GPIO peripheral instance
 *
 * @returns Void
 */
__STATIC_FORCEINLINE void GPIO_LL_EnablePortClock(GPIO_TypeDef* const GPIOx)
{
	const uint32_t clockMask = _GPIO_LL_GetPortClockMask(GPIOx);
	if (clockMask != 0x00000000UL)
	{
		(void) RCC_LL_EnableAPB2Clock(clockMask);
	}
}

/**
 * @brief Disables the APB2 clock gate for a GPIO port
 * @details
 * Resolves the supplied GPIO peripheral instance to the matching APB2 enable
 * bit, then forwards that raw mask to @ref RCC_LL_DisableAPB2Clock.
 *
 * @param[in] GPIOx Target GPIO peripheral instance
 *
 * @returns Void
 */
__STATIC_FORCEINLINE void GPIO_LL_DisablePortClock(GPIO_TypeDef* const GPIOx)
{
	const uint32_t clockMask = _GPIO_LL_GetPortClockMask(GPIOx);
	if (clockMask != 0x00000000UL)
	{
		(void) RCC_LL_DisableAPB2Clock(clockMask);
	}
}

/**
 * @brief Enables the APB2 clock gate for AFIO
 * @details
 * Forwards the raw `RCC_APB2ENR_AFIOEN` mask to @ref RCC_LL_EnableAPB2Clock
 * so that alternate-function routing logic becomes accessible.
 *
 * @returns Void
 */
__STATIC_FORCEINLINE void GPIO_LL_EnableAFIOClock(void)
{
	(void) RCC_LL_EnableAPB2Clock(RCC_APB2ENR_AFIOEN);
}

/** @} */ // GPIO_02_LL_02_ClockControl

/** @} */ // GPIO_02_LL

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_LL_H_ */
