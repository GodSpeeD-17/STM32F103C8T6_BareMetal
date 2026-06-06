/**
 * @file	gpio_irq_codec.c
 * @author	Shrey Shah
 * @brief	GPIO IRQ Codec Implementation
 * @version	v1.0
 * @date	31-03-2026
 *
 * @details
 * This source file implements the GPIO IRQ codec bridge between staged
 * EXTI/AFIO register images and driver-facing GPIO IRQ selectors.
 */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "gpio_irq_codec.h"

// ==================================================================================================== //
//                                              Local Codecs                                           //
// ==================================================================================================== //

/**
 * @brief Returns the AFIO EXTICR routing-field bit position for one GPIO IRQ line
 * @param[in] pinIndex Zero-based GPIO IRQ line index
 * @returns Bit position of the selected four-bit EXTICR field
 * @retval - `0U, 4U, 8U, 12U`: Field shift inside the selected EXTICR image
 * @note Caller owns validation that @p pinIndex is inside the supported GPIO pin range.
 */
__STATIC_FORCEINLINE reg_field_t Codec_GPIO_IRQ_GetRoutingFieldBitPos(const gpio_pin_index_t pinIndex)
{
	return (reg_field_t) (((reg) (pinIndex & (gpio_pin_index_t) 0x03U)) << 2U);
}

driver_status_t Codec_GPIO_IRQ_GetRoutingRegisterIndex
(
	const gpio_pin_index_t		pinIndex,
	uint8_t* const				pExticrIndex
)
{
	if (pExticrIndex == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (GPIO_PIN_INDEX_IS_VALID(pinIndex) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pExticrIndex = (uint8_t) (pinIndex >> 2U);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_StagePortRouting
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_index_t		pinIndex,
	reg* const					pExticrRegImage
)
{
	uint32_t gpioPortIndex = 0xFFFFFFFFUL;
	reg regImage = 0x00000000UL;
	reg_field_t fieldShift = 0x00000000UL;
	reg fieldMask = 0x00000000UL;

	if (pExticrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_INDEX_IS_VALID(pinIndex) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	gpioPortIndex = BIT_POS(GPIOx, GPIOA, GPIO_PERIPHERAL_SIZE);
	if (gpioPortIndex > 0x06UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	fieldShift = Codec_GPIO_IRQ_GetRoutingFieldBitPos(pinIndex);
	fieldMask = REG_FIELD_VALUE(0x0FUL, fieldShift);
	regImage = *pExticrRegImage;
	regImage &= ~fieldMask;
	regImage |= REG_FIELD_VALUE(((reg) gpioPortIndex & 0x0FUL), fieldShift);

	*pExticrRegImage = regImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_ExtractPortRoutingState
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_index_t		pinIndex,
	const reg					exticrRegImage,
	driver_status_t* const		pRouteState
)
{
	uint32_t gpioPortIndex = 0xFFFFFFFFUL;
	reg_field_t fieldShift = 0x00000000UL;
	reg_field_t routeField = 0x00U;

	if (pRouteState == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_INDEX_IS_VALID(pinIndex) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	gpioPortIndex = BIT_POS(GPIOx, GPIOA, GPIO_PERIPHERAL_SIZE);
	if (gpioPortIndex > 0x06UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	fieldShift = Codec_GPIO_IRQ_GetRoutingFieldBitPos(pinIndex);
	routeField = (reg_field_t) ((exticrRegImage >> fieldShift) & 0x0FUL);
	*pRouteState = (((reg) routeField) == (((reg) gpioPortIndex) & 0x0FUL)) ? DRIVER_STATUS_ON : DRIVER_STATUS_OFF;

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_StageResetPortRouting
(
	const gpio_pin_index_t		pinIndex,
	reg* const					pExticrRegImage
)
{
	reg regImage = 0x00000000UL;
	reg_field_t fieldShift = 0x00000000UL;
	reg fieldMask = 0x00000000UL;

	if (pExticrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (GPIO_PIN_INDEX_IS_VALID(pinIndex) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	fieldShift = Codec_GPIO_IRQ_GetRoutingFieldBitPos(pinIndex);
	fieldMask = REG_FIELD_VALUE(0x0FUL, fieldShift);
	regImage = *pExticrRegImage;
	regImage &= ~fieldMask;

	*pExticrRegImage = regImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_StageTrigger
(
	const gpio_pin_index_t		pinIndex,
	const gpio_irq_trigger_t		trigger,
	reg* const					pRtsrRegImage,
	reg* const					pFtsrRegImage
)
{
	reg rtsrRegImage = 0x00000000UL;
	reg ftsrRegImage = 0x00000000UL;
	reg lineMask = 0x00000000UL;

	if ((pRtsrRegImage == NULL) || (pFtsrRegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIO_PIN_INDEX_IS_VALID(pinIndex) == 0x00U) || (GPIO_IRQ_TRIGGER_IS_VALID(trigger) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	lineMask = (reg) GPIO_PIN_INDEX_TO_MASK(pinIndex);
	rtsrRegImage = *pRtsrRegImage;
	ftsrRegImage = *pFtsrRegImage;

	if ((((reg) trigger) & ((reg) GPIO_IRQ_TRIGGER_RISING)) != 0x00000000UL)
	{
		rtsrRegImage |= lineMask;
	}
	else
	{
		rtsrRegImage &= ~lineMask;
	}

	if ((((reg) trigger) & ((reg) GPIO_IRQ_TRIGGER_FALLING)) != 0x00000000UL)
	{
		ftsrRegImage |= lineMask;
	}
	else
	{
		ftsrRegImage &= ~lineMask;
	}

	*pRtsrRegImage = rtsrRegImage;
	*pFtsrRegImage = ftsrRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_StageResetTrigger
(
	const gpio_pin_index_t		pinIndex,
	reg* const					pRtsrRegImage,
	reg* const					pFtsrRegImage
)
{
	reg rtsrRegImage = 0x00000000UL;
	reg ftsrRegImage = 0x00000000UL;
	reg lineMask = 0x00000000UL;

	if ((pRtsrRegImage == NULL) || (pFtsrRegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (GPIO_PIN_INDEX_IS_VALID(pinIndex) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	lineMask = (reg) GPIO_PIN_INDEX_TO_MASK(pinIndex);
	rtsrRegImage = *pRtsrRegImage;
	ftsrRegImage = *pFtsrRegImage;
	rtsrRegImage &= ~lineMask;
	ftsrRegImage &= ~lineMask;

	*pRtsrRegImage = rtsrRegImage;
	*pFtsrRegImage = ftsrRegImage;
	return DRIVER_STATUS_SUCCESS;
}
