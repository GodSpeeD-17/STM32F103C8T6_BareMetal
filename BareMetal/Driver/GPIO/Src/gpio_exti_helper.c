/**
 * @file	gpio_exti_helper.c
 * @author	Shrey Shah
 * @brief	GPIO EXTI Internal Helper Implementation
 * @version	v1.0
 * @date	31-03-2026
 *
 * @details
 * This source file implements the Layer 2 helper bridge for the GPIO EXTI
 * driver.
 */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "gpio_exti_helper.h"

// ==================================================================================================== //
//                                              Local Helpers                                           //
// ==================================================================================================== //

__STATIC_FORCEINLINE uint8_t _GPIO_EXTI_Helper_IsSinglePinMaskValid(const gpio_pin_t pin)
{
	return ((GPIO_PIN_MASK_IS_VALID(pin) != 0x00U) &&
		(GPIO_PIN_MASK_HAS_AT_MOST_ONE_BIT(pin) != 0x00U)) ? 0x01U : 0x00U;
}

__STATIC_FORCEINLINE gpio_exti_port_t _GPIO_EXTI_Helper_GetPortSource(const GPIO_TypeDef* const GPIOx)
{
	gpio_exti_port_t portSource = (gpio_exti_port_t) 0xFFU;
	const uint32_t gpioIndex = BIT_POS(GPIOx, GPIOA, GPIO_PERIPHERAL_SIZE);

	switch (gpioIndex)
	{
		case 0x00UL:
		{
			portSource = GPIO_EXTI_PORT_A;
			break;
		}
		case 0x01UL:
		{
			portSource = GPIO_EXTI_PORT_B;
			break;
		}
		case 0x02UL:
		{
			portSource = GPIO_EXTI_PORT_C;
			break;
		}
		case 0x03UL:
		{
			portSource = GPIO_EXTI_PORT_D;
			break;
		}
		case 0x04UL:
		{
			portSource = GPIO_EXTI_PORT_E;
			break;
		}
		case 0x05UL:
		{
			portSource = GPIO_EXTI_PORT_F;
			break;
		}
		case 0x06UL:
		{
			portSource = GPIO_EXTI_PORT_G;
			break;
		}
		default:
		{
			break;
		}
	}

	return portSource;
}

__STATIC_FORCEINLINE uint8_t _GPIO_EXTI_Helper_GetConfigRegisterIndex(const gpio_pin_t pin)
{
	return (uint8_t) (GPIO_PinMaskToIndex(pin) >> 2U);
}

__STATIC_FORCEINLINE uint32_t _GPIO_EXTI_Helper_GetConfigFieldShift(const gpio_pin_t pin)
{
	return ((uint32_t) (GPIO_PinMaskToIndex(pin) & (gpio_pin_index_t) 0x03U) << 2U);
}

driver_status_t _GPIO_EXTI_Helper_UpdatePortConfigImage
(
	GPIO_TypeDef* const GPIOx,
	const gpio_pin_t pin,
	uint32_t* const pExticrRegImage
)
{
	gpio_exti_port_t portSource = (gpio_exti_port_t) 0xFFU;
	uint32_t regImage = 0x00000000UL;
	uint32_t fieldShift = 0x00000000UL;
	uint32_t fieldMask = 0x00000000UL;

	if (pExticrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (_GPIO_EXTI_Helper_IsSinglePinMaskValid(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	portSource = _GPIO_EXTI_Helper_GetPortSource(GPIOx);
	if (GPIO_EXTI_IS_PORT_SOURCE(portSource) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	fieldShift = _GPIO_EXTI_Helper_GetConfigFieldShift(pin);
	fieldMask = BIT_VALUE(0x0FUL, fieldShift);
	regImage = *pExticrRegImage;
	regImage &= ~fieldMask;
	regImage |= BIT_VALUE(((uint32_t) portSource & 0x0FUL), fieldShift);

	*pExticrRegImage = regImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t _GPIO_EXTI_Helper_ResetPortConfigImage
(
	const gpio_pin_t pin,
	uint32_t* const pExticrRegImage
)
{
	uint32_t regImage = 0x00000000UL;
	uint32_t fieldShift = 0x00000000UL;
	uint32_t fieldMask = 0x00000000UL;

	if (pExticrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (_GPIO_EXTI_Helper_IsSinglePinMaskValid(pin) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	fieldShift = _GPIO_EXTI_Helper_GetConfigFieldShift(pin);
	fieldMask = BIT_VALUE(0x0FUL, fieldShift);
	regImage = *pExticrRegImage;
	regImage &= ~fieldMask;

	*pExticrRegImage = regImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t _GPIO_EXTI_Helper_UpdateTriggerImages
(
	const gpio_pin_t pin,
	const gpio_exti_trigger_t trigger,
	uint32_t* const pRtsrRegImage,
	uint32_t* const pFtsrRegImage
)
{
	uint32_t rtsrRegImage = 0x00000000UL;
	uint32_t ftsrRegImage = 0x00000000UL;

	if ((pRtsrRegImage == NULL) || (pFtsrRegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((_GPIO_EXTI_Helper_IsSinglePinMaskValid(pin) == 0x00U) || (GPIO_EXTI_IS_TRIGGER(trigger) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	rtsrRegImage = *pRtsrRegImage;
	ftsrRegImage = *pFtsrRegImage;

	if ((((uint32_t) trigger) & ((uint32_t) GPIO_EXTI_TRIGGER_RISING)) != 0x00000000UL)
	{
		rtsrRegImage |= (uint32_t) pin;
	}
	else
	{
		rtsrRegImage &= ~((uint32_t) pin);
	}

	if ((((uint32_t) trigger) & ((uint32_t) GPIO_EXTI_TRIGGER_FALLING)) != 0x00000000UL)
	{
		ftsrRegImage |= (uint32_t) pin;
	}
	else
	{
		ftsrRegImage &= ~((uint32_t) pin);
	}

	*pRtsrRegImage = rtsrRegImage;
	*pFtsrRegImage = ftsrRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t _GPIO_EXTI_Helper_ResetTriggerImages
(
	const gpio_pin_t pin,
	uint32_t* const pRtsrRegImage,
	uint32_t* const pFtsrRegImage
)
{
	uint32_t rtsrRegImage = 0x00000000UL;
	uint32_t ftsrRegImage = 0x00000000UL;

	if ((pRtsrRegImage == NULL) || (pFtsrRegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (_GPIO_EXTI_Helper_IsSinglePinMaskValid(pin) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	rtsrRegImage = *pRtsrRegImage;
	ftsrRegImage = *pFtsrRegImage;
	rtsrRegImage &= ~((uint32_t) pin);
	ftsrRegImage &= ~((uint32_t) pin);

	*pRtsrRegImage = rtsrRegImage;
	*pFtsrRegImage = ftsrRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t _GPIO_EXTI_Helper_GetIRQn
(
	const gpio_pin_t pin,
	irq_t* const pIRQn
)
{
	const gpio_pin_index_t lineIndex = GPIO_PinMaskToIndex(pin);

	if (pIRQn == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (lineIndex > GPIO_PIN_INDEX_LAST)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	switch (lineIndex)
	{
		case 0x00U:
		{
			*pIRQn = EXTI0_IRQn;
			break;
		}
		case 0x01U:
		{
			*pIRQn = EXTI1_IRQn;
			break;
		}
		case 0x02U:
		{
			*pIRQn = EXTI2_IRQn;
			break;
		}
		case 0x03U:
		{
			*pIRQn = EXTI3_IRQn;
			break;
		}
		case 0x04U:
		{
			*pIRQn = EXTI4_IRQn;
			break;
		}
		case 0x05U:
		case 0x06U:
		case 0x07U:
		case 0x08U:
		case 0x09U:
		{
			*pIRQn = EXTI9_5_IRQn;
			break;
		}
		case 0x0AU:
		case 0x0BU:
		case 0x0CU:
		case 0x0DU:
		case 0x0EU:
		case 0x0FU:
		{
			*pIRQn = EXTI15_10_IRQn;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}
