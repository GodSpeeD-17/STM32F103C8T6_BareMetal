/**
 * @file	gpio_irq_codec.c
 * @author	Shrey Shah
 * @brief	GPIO IRQ Codec Implementation
 * @version	v1.1
 * @date	06-06-2026
 *
 * @details
 * This source file implements GPIO IRQ staged-image translation. The public
 * codec boundary accepts GPIO single-pin masks from the driver layer, converts
 * them into EXTI line indexes internally, and updates caller-owned EXTI/AFIO
 * register images without touching hardware.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "gpio_irq_codec.h"

// ==================================================================================================== //
//												Local Defines											//
// ==================================================================================================== //

/** @brief Right-aligned AFIO EXTICR port-route field mask @def GPIO_IRQ_EXTICR_PORT_ROUTE_FIELD_MASK */
#define GPIO_IRQ_EXTICR_PORT_ROUTE_FIELD_MASK				((reg_field_t) 0x0FU)
/** @brief Pin-index mask selecting local EXTICR field index @def GPIO_IRQ_EXTICR_LOCAL_PIN_INDEX_MASK */
#define GPIO_IRQ_EXTICR_LOCAL_PIN_INDEX_MASK				((gpio_pin_index_t) 0x03U)
/** @brief Pin-index shift used to select EXTICR register index @def GPIO_IRQ_EXTICR_REG_INDEX_SHIFT */
#define GPIO_IRQ_EXTICR_REG_INDEX_SHIFT						((uint8_t) 0x02U)
/** @brief Width of one AFIO EXTICR route field @def GPIO_IRQ_EXTICR_ROUTE_FIELD_WIDTH */
#define GPIO_IRQ_EXTICR_ROUTE_FIELD_WIDTH					((reg_field_t) 0x04U)

// ==================================================================================================== //
//												Local Codecs											//
// ==================================================================================================== //

/**
 * @brief Decodes one GPIO single-pin mask into a GPIO IRQ line index
 * @param[in] pin GPIO single-pin mask
 * Accepted values:
 * - @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[out] pPinIndex Destination for decoded zero-based EXTI line index
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p pin was decoded into @p pPinIndex
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPinIndex is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pin is not a single valid pin
 */
__STATIC_FORCEINLINE driver_status_t Codec_GPIO_IRQ_GetPinIndexFromPinMask
(
	const gpio_pin_t			pin,
	gpio_pin_index_t* const		pPinIndex
)
{
	// Validate Input
	if (pPinIndex == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	*pPinIndex = GPIO_PinMaskToIndex(pin);
	if (*pPinIndex == GPIO_PIN_INDEX_INVALID)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Returns the AFIO EXTICR routing-field bit position for one GPIO IRQ line
 * @param[in] pinIndex Zero-based GPIO IRQ line index
 * @returns Bit position of the selected four-bit EXTICR field
 * @retval - `0U, 4U, 8U, 12U`: Field shift inside the selected EXTICR image
 * @note Caller owns validation that @p pinIndex is inside the supported GPIO pin range.
 */
__STATIC_FORCEINLINE reg_field_t Codec_GPIO_IRQ_GetRoutingFieldBitPos(const gpio_pin_index_t pinIndex)
{
	// Local Variable
	const gpio_pin_index_t localPinIndex = (gpio_pin_index_t) (pinIndex & GPIO_IRQ_EXTICR_LOCAL_PIN_INDEX_MASK);
	return (reg_field_t) (localPinIndex * GPIO_IRQ_EXTICR_ROUTE_FIELD_WIDTH);
}

/**
 * @brief Encodes one GPIO peripheral instance into a raw AFIO EXTICR route field
 * @param[in] GPIOx GPIO peripheral instance
 * Accepted values:
 * - @ref `GPIOA` through @ref `GPIOG`
 * @param[out] pPortRoute Destination for right-aligned AFIO route field
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p GPIOx was encoded into @p pPortRoute
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPortRoute is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx is not supported
 */
__STATIC driver_status_t Codec_GPIO_IRQ_EncodePortRoute
(
	GPIO_TypeDef* const			GPIOx,
	reg_field_t* const			pPortRoute
)
{
	// Local Variable
	const uint32_t gpioPortAddress = (uint32_t) GPIOx;
	reg_field_t portRoute = (reg_field_t) 0xFFU;

	// Validate Input
	if (pPortRoute == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (GPIO_PORT_IS_VALID(GPIOx) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Convert the GPIO instance to the raw AFIO EXTICR port-source field value
	switch(gpioPortAddress)
	{
		case GPIOA_BASE_ADDRESS:
		{
			portRoute = AFIO_EXTICR_PORT_SOURCE_GPIOA;
			break;
		}
		case GPIOB_BASE_ADDRESS:
		{
			portRoute = AFIO_EXTICR_PORT_SOURCE_GPIOB;
			break;
		}
		case GPIOC_BASE_ADDRESS:
		{
			portRoute = AFIO_EXTICR_PORT_SOURCE_GPIOC;
			break;
		}
		case GPIOD_BASE_ADDRESS:
		{
			portRoute = AFIO_EXTICR_PORT_SOURCE_GPIOD;
			break;
		}
		case GPIOE_BASE_ADDRESS:
		{
			portRoute = AFIO_EXTICR_PORT_SOURCE_GPIOE;
			break;
		}
		case GPIOF_BASE_ADDRESS:
		{
			portRoute = AFIO_EXTICR_PORT_SOURCE_GPIOF;
			break;
		}
		case GPIOG_BASE_ADDRESS:
		{
			portRoute = AFIO_EXTICR_PORT_SOURCE_GPIOG;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	//! Assign the raw port route field to the output
	*pPortRoute = portRoute;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//												Public Codecs											//
// ==================================================================================================== //

_IO* Codec_GPIO_IRQ_GetRoutingRegisterAddress(const gpio_pin_t pin)
{
	// Local Variable
	const gpio_pin_index_t pinIndex = GPIO_PinMaskToIndex(pin);
	uint8_t exticrIndex = 0x00U;

	// Validate Input
	if (pinIndex == GPIO_PIN_INDEX_INVALID)
	{
		return NULL;
	}

	//! EXTICR register group is selected by pinIndex / 4, i.e. pinIndex >> 2U
	exticrIndex = (uint8_t) (pinIndex >> GPIO_IRQ_EXTICR_REG_INDEX_SHIFT);
	//! Determine EXTI_CR Index
	switch(exticrIndex)
	{
		case 0x00U:
		{
			return REGOPS_REG(AFIO, EXTICR1);
		}
		case 0x01U:
		{
			return REGOPS_REG(AFIO, EXTICR2);
		}
		case 0x02U:
		{
			return REGOPS_REG(AFIO, EXTICR3);
		}
		case 0x03U:
		{
			return REGOPS_REG(AFIO, EXTICR4);
		}
		default:
		{
			return NULL;
		}
	}
}

driver_status_t Codec_GPIO_IRQ_StagePortRouting
(
	const reg					exticrRegImage,
	const gpio_pin_t			pin,
	GPIO_TypeDef* const			GPIOx,
	reg* const					pExticrRegImage
)
{
	// Local Variables
	reg updatedRegImage = exticrRegImage;
	reg_field_t fieldShift = (reg_field_t) 0x00U;
	reg_field_t portRoute = (reg_field_t) 0x00U;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Input
	if (pExticrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Get the pin index and encoded port route for the selected GPIO pin and peripheral
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_GetPinIndexFromPinMask(pin, &pinIndex));
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_EncodePortRoute(GPIOx, &portRoute));

	//! Replace only the selected EXTI line route field inside the EXTICR image
	fieldShift = Codec_GPIO_IRQ_GetRoutingFieldBitPos(pinIndex);
	updatedRegImage = RegOps_StageFieldValue
	(
		updatedRegImage,
		fieldShift,
		portRoute,
		GPIO_IRQ_EXTICR_ROUTE_FIELD_WIDTH
	);

	*pExticrRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_ExtractPortRouting
(
	const reg					exticrRegImage,
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pin,
	driver_status_t* const		pRouteState
)
{
	// Local Variables
	reg_field_t fieldShift = (reg_field_t) 0x00U;
	reg_field_t routeField = (reg_field_t) 0x00U;
	reg_field_t expectedRouteField = (reg_field_t) 0x00U;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Input
	if (pRouteState == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_EncodePortRoute(GPIOx, &expectedRouteField));
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_GetPinIndexFromPinMask(pin, &pinIndex));

	//! Extract the right-aligned raw AFIO route field and compare it against the encoded GPIOx route
	fieldShift = Codec_GPIO_IRQ_GetRoutingFieldBitPos(pinIndex);
	routeField = (reg_field_t) ((exticrRegImage >> fieldShift) & GPIO_IRQ_EXTICR_PORT_ROUTE_FIELD_MASK);
	*pRouteState = (routeField == expectedRouteField) ? DRIVER_STATUS_ON : DRIVER_STATUS_OFF;

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_StageResetPortRouting
(
	const reg					exticrRegImage,
	const gpio_pin_t			pin,
	reg* const					pExticrRegImage
)
{
	// Local Variables
	reg updatedRegImage = exticrRegImage;
	reg fieldMask = 0x00000000UL;
	reg_field_t fieldShift = (reg_field_t) 0x00U;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Input
	if (pExticrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_GetPinIndexFromPinMask(pin, &pinIndex));

	//! Clear only the selected EXTI line route field inside the EXTICR image
	fieldShift = Codec_GPIO_IRQ_GetRoutingFieldBitPos(pinIndex);
	fieldMask = REG_FIELD_VALUE(fieldShift, GPIO_IRQ_EXTICR_PORT_ROUTE_FIELD_MASK);
	updatedRegImage &= ~fieldMask;

	*pExticrRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_StageTrigger
(
	const reg					rtsrRegImage,
	const reg					ftsrRegImage,
	const gpio_pin_t			pin,
	const gpio_irq_trigger_t	trigger,
	reg* const					pRtsrRegImage,
	reg* const					pFtsrRegImage
)
{
	// Local Variables
	reg updatedRtsrRegImage = rtsrRegImage;
	reg updatedFtsrRegImage = ftsrRegImage;
	reg lineMask = 0x00000000UL;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Input
	if ((pRtsrRegImage == NULL) || (pFtsrRegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (GPIO_IRQ_TRIGGER_IS_VALID(trigger) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_GetPinIndexFromPinMask(pin, &pinIndex));

	lineMask = REG_BIT_MASK(pinIndex);

	//! Stage rising trigger bit for the selected EXTI line
	if ((((reg) trigger) & ((reg) GPIO_IRQ_TRIGGER_RISING)) != 0x00000000UL)
	{
		updatedRtsrRegImage |= lineMask;
	}
	else
	{
		updatedRtsrRegImage &= ~lineMask;
	}

	//! Stage falling trigger bit for the selected EXTI line
	if ((((reg) trigger) & ((reg) GPIO_IRQ_TRIGGER_FALLING)) != 0x00000000UL)
	{
		updatedFtsrRegImage |= lineMask;
	}
	else
	{
		updatedFtsrRegImage &= ~lineMask;
	}

	*pRtsrRegImage = updatedRtsrRegImage;
	*pFtsrRegImage = updatedFtsrRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_ExtractTrigger
(
	const reg					rtsrRegImage,
	const reg					ftsrRegImage,
	const gpio_pin_t			pin,
	gpio_irq_trigger_t* const	pTrigger
)
{
	// Local Variables
	reg lineMask = 0x00000000UL;
	gpio_irq_trigger_t trigger = (gpio_irq_trigger_t) 0x00U;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Input
	if (pTrigger == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_GetPinIndexFromPinMask(pin, &pinIndex));

	lineMask = REG_BIT_MASK(pinIndex);

	//! Extract rising trigger bit for the selected EXTI line
	if ((rtsrRegImage & lineMask) != 0x00000000UL)
	{
		trigger = (gpio_irq_trigger_t) (trigger | GPIO_IRQ_TRIGGER_RISING);
	}

	//! Extract falling trigger bit for the selected EXTI line
	if ((ftsrRegImage & lineMask) != 0x00000000UL)
	{
		trigger = (gpio_irq_trigger_t) (trigger | GPIO_IRQ_TRIGGER_FALLING);
	}

	*pTrigger = trigger;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_GPIO_IRQ_StageResetTrigger
(
	const reg					rtsrRegImage,
	const reg					ftsrRegImage,
	const gpio_pin_t			pin,
	reg* const					pRtsrRegImage,
	reg* const					pFtsrRegImage
)
{
	// Local Variables
	reg updatedRtsrRegImage = rtsrRegImage;
	reg updatedFtsrRegImage = ftsrRegImage;
	reg lineMask = 0x00000000UL;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Input
	if ((pRtsrRegImage == NULL) || (pFtsrRegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_GetPinIndexFromPinMask(pin, &pinIndex));

	lineMask = REG_BIT_MASK(pinIndex);
	updatedRtsrRegImage &= ~lineMask;
	updatedFtsrRegImage &= ~lineMask;

	*pRtsrRegImage = updatedRtsrRegImage;
	*pFtsrRegImage = updatedFtsrRegImage;
	return DRIVER_STATUS_SUCCESS;
}
