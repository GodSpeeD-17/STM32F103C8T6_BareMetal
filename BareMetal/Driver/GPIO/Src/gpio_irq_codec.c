/**
 * @file	gpio_irq_codec.c
 * @author	Shrey Shah
 * @brief	GPIO IRQ Codec Implementation
 * @version	v1.0
 * @date	31-03-2026
 *
 * @details
 * This source file implements the Layer 2 codec bridge for the GPIO IRQ
 * driver.
 */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "gpio_irq_codec.h"

// ==================================================================================================== //
//                                              Local Codecs                                           //
// ==================================================================================================== //

/**
 * @brief Checks whether a GPIO pin mask selects exactly one valid GPIO IRQ line
 * @param[in] pin GPIO single-pin mask candidate
 * @returns Single-line validity status
 * @retval - `0x00U`: @p pin is empty, invalid, or selects multiple lines
 * @retval - `0x01U`: @p pin selects exactly one supported line
 */
__STATIC_FORCEINLINE uint8_t Codec_GPIO_IRQ_IsSinglePinMaskValid(const gpio_pin_t pin)
{
	return ((GPIO_PIN_MASK_IS_VALID(pin) != 0x00U) &&
		(GPIO_PIN_MASK_HAS_AT_MOST_ONE_PIN(pin) != 0x00U)) ? 0x01U : 0x00U;
}

/**
 * @brief Returns which AFIO EXTICR register owns one GPIO IRQ line
 * @param[in] pin GPIO single-pin mask identifying the GPIO IRQ line
 * @returns Zero-based AFIO EXTICR index
 * @retval - `0U`: EXTI0..EXTI3 route through `EXTICR1`
 * @retval - `1U`: EXTI4..EXTI7 route through `EXTICR2`
 * @retval - `2U`: EXTI8..EXTI11 route through `EXTICR3`
 * @retval - `3U`: EXTI12..EXTI15 route through `EXTICR4`
 * @note Caller owns validation that @p pin contains exactly one supported line.
 */
__STATIC_FORCEINLINE uint8_t Codec_GPIO_IRQ_GetConfigRegisterIndex(const gpio_pin_t pin)
{
	return (uint8_t) (GPIO_PinMaskToIndex(pin) >> 2U);
}

/**
 * @brief Returns the EXTICR field shift for one GPIO IRQ line inside its local EXTICR image
 * @param[in] pin GPIO single-pin mask identifying the GPIO IRQ line
 * @returns Bit position of the selected four-bit EXTICR field
 * @retval - `0U, 4U, 8U, 12U`: Field shift inside the selected EXTICR image
 * @note Caller owns validation that @p pin contains exactly one supported line.
 */
__STATIC_FORCEINLINE reg_field_t Codec_GPIO_IRQ_GetConfigFieldShift(const gpio_pin_t pin)
{
	return (reg_field_t) (((reg) (GPIO_PinMaskToIndex(pin) & (gpio_pin_index_t) 0x03U)) << 2U);
}

driver_status_t Codec_GPIO_IRQ_UpdatePortConfigImage
(
	GPIO_TypeDef* const GPIOx,
	const gpio_pin_t pin,
	reg* const pExticrRegImage
)
{
	const uint32_t gpioPortIndex = BIT_POS(GPIOx, GPIOA, GPIO_PERIPHERAL_SIZE);
	reg regImage = 0x00000000UL;
	reg_field_t fieldShift = 0x00000000UL;
	reg fieldMask = 0x00000000UL;

	if (pExticrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (Codec_GPIO_IRQ_IsSinglePinMaskValid(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	if (gpioPortIndex > 0x06UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	fieldShift = Codec_GPIO_IRQ_GetConfigFieldShift(pin);
	fieldMask = REG_FIELD_VALUE(0x0FUL, fieldShift);
	regImage = *pExticrRegImage;
	regImage &= ~fieldMask;
	regImage |= REG_FIELD_VALUE(((reg) gpioPortIndex & 0x0FUL), fieldShift);

	*pExticrRegImage = regImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_ResetPortConfigImage
(
	const gpio_pin_t pin,
	reg* const pExticrRegImage
)
{
	reg regImage = 0x00000000UL;
	reg_field_t fieldShift = 0x00000000UL;
	reg fieldMask = 0x00000000UL;

	if (pExticrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (Codec_GPIO_IRQ_IsSinglePinMaskValid(pin) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	fieldShift = Codec_GPIO_IRQ_GetConfigFieldShift(pin);
	fieldMask = REG_FIELD_VALUE(0x0FUL, fieldShift);
	regImage = *pExticrRegImage;
	regImage &= ~fieldMask;

	*pExticrRegImage = regImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_UpdateTriggerImages
(
	const gpio_pin_t pin,
	const gpio_irq_trigger_t trigger,
	reg* const pRtsrRegImage,
	reg* const pFtsrRegImage
)
{
	reg rtsrRegImage = 0x00000000UL;
	reg ftsrRegImage = 0x00000000UL;

	if ((pRtsrRegImage == NULL) || (pFtsrRegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((Codec_GPIO_IRQ_IsSinglePinMaskValid(pin) == 0x00U) || (GPIO_IRQ_TRIGGER_IS_VALID(trigger) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	rtsrRegImage = *pRtsrRegImage;
	ftsrRegImage = *pFtsrRegImage;

	if ((((reg) trigger) & ((reg) GPIO_IRQ_TRIGGER_RISING)) != 0x00000000UL)
	{
		rtsrRegImage |= (reg) pin;
	}
	else
	{
		rtsrRegImage &= ~((reg) pin);
	}

	if ((((reg) trigger) & ((reg) GPIO_IRQ_TRIGGER_FALLING)) != 0x00000000UL)
	{
		ftsrRegImage |= (reg) pin;
	}
	else
	{
		ftsrRegImage &= ~((reg) pin);
	}

	*pRtsrRegImage = rtsrRegImage;
	*pFtsrRegImage = ftsrRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_ResetTriggerImages
(
	const gpio_pin_t pin,
	reg* const pRtsrRegImage,
	reg* const pFtsrRegImage
)
{
	reg rtsrRegImage = 0x00000000UL;
	reg ftsrRegImage = 0x00000000UL;

	if ((pRtsrRegImage == NULL) || (pFtsrRegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (Codec_GPIO_IRQ_IsSinglePinMaskValid(pin) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	rtsrRegImage = *pRtsrRegImage;
	ftsrRegImage = *pFtsrRegImage;
	rtsrRegImage &= ~((reg) pin);
	ftsrRegImage &= ~((reg) pin);

	*pRtsrRegImage = rtsrRegImage;
	*pFtsrRegImage = ftsrRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_GetIRQn
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
