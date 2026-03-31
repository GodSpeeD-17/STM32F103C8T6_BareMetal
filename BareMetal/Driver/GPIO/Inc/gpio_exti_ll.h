/**
 * @file	gpio_exti_ll.h
 * @author	Shrey Shah
 * @brief	GPIO EXTI Low-Level Interface
 * @version	v1.0
 * @date	31-03-2026
 *
 * @details
 * This header defines the Layer 1 EXTI low-level interface that sits directly
 * above the raw EXTI, AFIO, RCC, and NVIC register model.
 *
 * The EXTI LL layer owns only direct hardware-facing actions:
 * - EXTI register access macros
 * - AFIO EXTICR register access helpers
 * - AFIO clock enable
 * - NVIC IRQ enable/disable wrappers for EXTI integration
 */

#ifndef GPIO_EXTI_LL_H_
#define GPIO_EXTI_LL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "stm32f1xx.h"
#include "nvic.h"
#include "rcc_ll.h"

/**
 * @addtogroup GPIO_EXTI_02_LL
 * @{
 */

// ==================================================================================================== //
//                                         EXTI Register Macros                                         //
// ==================================================================================================== //

/**
 * @brief Returns a pointer to the selected EXTI register `.REG` image
 * @def GPIO_EXTI_LL_EXTI_REG
 */
#define GPIO_EXTI_LL_EXTI_REG(_REG)						(&(EXTI->_REG.REG))

/**
 * @brief Reads the selected EXTI register `.REG` image
 * @def GPIO_EXTI_LL_EXTI_READ_REG
 */
#define GPIO_EXTI_LL_EXTI_READ_REG(_REG, _VAR)			REGOPS_READ(GPIO_EXTI_LL_EXTI_REG(_REG), (_VAR))

/**
 * @brief Writes the selected EXTI register `.REG` image
 * @def GPIO_EXTI_LL_EXTI_WRITE_REG
 */
#define GPIO_EXTI_LL_EXTI_WRITE_REG(_REG, _VAL)			REGOPS_WRITE(GPIO_EXTI_LL_EXTI_REG(_REG), (_VAL))

/**
 * @brief Sets EXTI register bits
 * @def GPIO_EXTI_LL_EXTI_SET_BITS
 */
#define GPIO_EXTI_LL_EXTI_SET_BITS(_REG, _MASK)			REGOPS_SET(GPIO_EXTI_LL_EXTI_REG(_REG), (_MASK))

/**
 * @brief Clears EXTI register bits
 * @def GPIO_EXTI_LL_EXTI_CLEAR_BITS
 */
#define GPIO_EXTI_LL_EXTI_CLEAR_BITS(_REG, _MASK)		REGOPS_CLEAR(GPIO_EXTI_LL_EXTI_REG(_REG), (_MASK))

/**
 * @brief Returns a pointer to the selected AFIO EXTICR register `.REG` image
 * @def GPIO_EXTI_LL_AFIO_REG
 */
#define GPIO_EXTI_LL_AFIO_REG(_REG)						(&(AFIO->_REG.REG))

/**
 * @brief Reads the selected AFIO EXTICR register `.REG` image
 * @def GPIO_EXTI_LL_AFIO_READ_REG
 */
#define GPIO_EXTI_LL_AFIO_READ_REG(_REG, _VAR)			REGOPS_READ(GPIO_EXTI_LL_AFIO_REG(_REG), (_VAR))

/**
 * @brief Writes the selected AFIO EXTICR register `.REG` image
 * @def GPIO_EXTI_LL_AFIO_WRITE_REG
 */
#define GPIO_EXTI_LL_AFIO_WRITE_REG(_REG, _VAL)			REGOPS_WRITE(GPIO_EXTI_LL_AFIO_REG(_REG), (_VAL))

/**
 * @brief Reads one AFIO EXTI configuration register image by index
 * @param[in] regIndex AFIO EXTICR register index in the range `0..3`
 * @param[out] pRegImage Destination for the register image
 * @returns Void
 */
__STATIC_FORCEINLINE void GPIO_EXTI_LL_ReadConfigRegister(const uint8_t regIndex, uint32_t* const pRegImage)
{
	if (pRegImage == NULL)
	{
		return;
	}

	switch (regIndex)
	{
		case 0x00U:
		{
			GPIO_EXTI_LL_AFIO_READ_REG(EXTICR1, *pRegImage);
			break;
		}
		case 0x01U:
		{
			GPIO_EXTI_LL_AFIO_READ_REG(EXTICR2, *pRegImage);
			break;
		}
		case 0x02U:
		{
			GPIO_EXTI_LL_AFIO_READ_REG(EXTICR3, *pRegImage);
			break;
		}
		case 0x03U:
		{
			GPIO_EXTI_LL_AFIO_READ_REG(EXTICR4, *pRegImage);
			break;
		}
		default:
		{
			*pRegImage = 0x00000000UL;
			break;
		}
	}
}

/**
 * @brief Writes one AFIO EXTI configuration register image by index
 * @param[in] regIndex AFIO EXTICR register index in the range `0..3`
 * @param[in] regImage Register image to write
 * @returns Void
 */
__STATIC_FORCEINLINE void GPIO_EXTI_LL_WriteConfigRegister(const uint8_t regIndex, const uint32_t regImage)
{
	switch (regIndex)
	{
		case 0x00U:
		{
			GPIO_EXTI_LL_AFIO_WRITE_REG(EXTICR1, regImage);
			break;
		}
		case 0x01U:
		{
			GPIO_EXTI_LL_AFIO_WRITE_REG(EXTICR2, regImage);
			break;
		}
		case 0x02U:
		{
			GPIO_EXTI_LL_AFIO_WRITE_REG(EXTICR3, regImage);
			break;
		}
		case 0x03U:
		{
			GPIO_EXTI_LL_AFIO_WRITE_REG(EXTICR4, regImage);
			break;
		}
		default:
		{
			break;
		}
	}
}

// ==================================================================================================== //
//                                             LL Helpers                                               //
// ==================================================================================================== //

/**
 * @brief Enables the APB2 clock gate for AFIO
 * @returns Void
 */
__STATIC_FORCEINLINE void GPIO_EXTI_LL_EnableAFIOClock(void)
{
	(void) RCC_LL_EnableAPB2Clock(RCC_APB2ENR_AFIOEN);
}

/**
 * @brief Acknowledges one or more EXTI pending line bits
 * @param[in] pin GPIO pin mask identifying the EXTI line(s)
 * @returns Void
 */
__STATIC_FORCEINLINE void GPIO_EXTI_LL_AckPendingLines(const gpio_pin_t pin)
{
	GPIO_EXTI_LL_EXTI_WRITE_REG(PR, (uint32_t) pin);
}

/**
 * @brief Enables one NVIC IRQ line
 * @param[in] IRQn NVIC interrupt number
 * @returns Void
 */
__STATIC_FORCEINLINE void GPIO_EXTI_LL_EnableIRQ(const irq_t IRQn)
{
	NVIC_IRQEnable((uint8_t) IRQn);
}

/**
 * @brief Disables one NVIC IRQ line
 * @param[in] IRQn NVIC interrupt number
 * @returns Void
 */
__STATIC_FORCEINLINE void GPIO_EXTI_LL_DisableIRQ(const irq_t IRQn)
{
	NVIC_IRQDisable((uint8_t) IRQn);
}

/** @} */ // GPIO_EXTI_02_LL

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_EXTI_LL_H_ */
