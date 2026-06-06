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
/** @brief Width of one AFIO EXTICR route field @def GPIO_IRQ_EXTICR_ROUTE_FIELD_WIDTH */
#define GPIO_IRQ_EXTICR_ROUTE_FIELD_WIDTH					((reg_field_t) 0x04U)

// ==================================================================================================== //
//											Local Common Helpers										//
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
__STATIC driver_status_t Codec_GPIO_IRQ_GetPinIndexFromPinMask(const gpio_pin_t pin, gpio_pin_index_t* const pPinIndex)
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

// ==================================================================================================== //
//									Local Port Routing Decode/Encode Helpers								//
// ==================================================================================================== //

/**
 * @brief Decodes one raw AFIO EXTICR route field into a GPIO peripheral instance
 * @param[in] portRoute Right-aligned raw AFIO EXTICR route field
 * Accepted values:
 * - @ref `AFIO_EXTICR_PORT_SOURCE_GPIOA` through @ref `AFIO_EXTICR_PORT_SOURCE_GPIOG`
 * @param[out] pGPIOx Destination for decoded GPIO peripheral instance
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p portRoute was decoded into @p pGPIOx
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pGPIOx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p portRoute is not supported
 */
__STATIC driver_status_t Codec_GPIO_IRQ_DecodePortRoute
(
	const reg_field_t			portRoute,
	GPIO_TypeDef** const		pGPIOx
)
{
	// Validate Input
	if (pGPIOx == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Convert the raw AFIO EXTICR port-source field value to a GPIO instance
	switch(portRoute)
	{
		case AFIO_EXTICR_PORT_SOURCE_GPIOA:
		{
			*pGPIOx = GPIOA;
			break;
		}
		case AFIO_EXTICR_PORT_SOURCE_GPIOB:
		{
			*pGPIOx = GPIOB;
			break;
		}
		case AFIO_EXTICR_PORT_SOURCE_GPIOC:
		{
			*pGPIOx = GPIOC;
			break;
		}
		case AFIO_EXTICR_PORT_SOURCE_GPIOD:
		{
			*pGPIOx = GPIOD;
			break;
		}
		case AFIO_EXTICR_PORT_SOURCE_GPIOE:
		{
			*pGPIOx = GPIOE;
			break;
		}
		case AFIO_EXTICR_PORT_SOURCE_GPIOF:
		{
			*pGPIOx = GPIOF;
			break;
		}
		case AFIO_EXTICR_PORT_SOURCE_GPIOG:
		{
			*pGPIOx = GPIOG;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
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
//										GPIO IRQ Port Routing Codecs									//
// ==================================================================================================== //

driver_status_t Codec_GPIO_IRQ_ExtractPortRouting
(
	const reg					exticrRegImage,
	const gpio_pin_t			pin,
	GPIO_TypeDef** const		pGPIOx
)
{
	// Local Variables
	reg_field_t fieldShift = (reg_field_t) 0x00U;
	reg_field_t routeField = (reg_field_t) 0x00U;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Output Pointer
	if (pGPIOx == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_GetPinIndexFromPinMask(pin, &pinIndex));

	//! Extract the right-aligned raw AFIO route field and decode it into a GPIO instance
	fieldShift = Codec_GPIO_IRQ_GetRoutingFieldBitPos(pinIndex);
	routeField = (reg_field_t) ((exticrRegImage >> fieldShift) & GPIO_IRQ_EXTICR_PORT_ROUTE_FIELD_MASK);

	return Codec_GPIO_IRQ_DecodePortRoute(routeField, pGPIOx);
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
	updatedRegImage = RegOps_StageField(updatedRegImage, fieldMask, 0x00000000UL);

	*pExticrRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
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
	reg fieldSet = 0x00000000UL;
	reg_field_t portRoute = (reg_field_t) 0x00U;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Output Pointer
	if (pExticrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Get the pin index and encoded port route for the selected GPIO pin and peripheral
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_GetPinIndexFromPinMask(pin, &pinIndex));
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_EncodePortRoute(GPIOx, &portRoute));

	//! Clear only the selected EXTI line route field before staging the new route
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_StageResetPortRouting(updatedRegImage, pin, &updatedRegImage));

	//! Pack and set only the selected EXTI line route field inside the EXTICR image
	fieldShift = Codec_GPIO_IRQ_GetRoutingFieldBitPos(pinIndex);
	fieldSet = REG_FIELD_PACK
	(
		fieldShift,
		portRoute,
		GPIO_IRQ_EXTICR_ROUTE_FIELD_WIDTH
	);
	updatedRegImage |= fieldSet;

	*pExticrRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										GPIO IRQ Trigger Codecs											//
// ==================================================================================================== //

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
	gpio_irq_trigger_t trigger = GPIO_IRQ_TRIGGER_NONE;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Output Pointer
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
	updatedRtsrRegImage = RegOps_StageField(updatedRtsrRegImage, lineMask, 0x00000000UL);
	updatedFtsrRegImage = RegOps_StageField(updatedFtsrRegImage, lineMask, 0x00000000UL);

	*pRtsrRegImage = updatedRtsrRegImage;
	*pFtsrRegImage = updatedFtsrRegImage;
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
	reg risingLineSet = 0x00000000UL;
	reg fallingLineSet = 0x00000000UL;
	gpio_pin_index_t pinIndex = GPIO_PIN_INDEX_INVALID;

	// Validate Output Pointers
	if ((pRtsrRegImage == NULL) || (pFtsrRegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (GPIO_IRQ_TRIGGER_IS_VALID(trigger) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_GetPinIndexFromPinMask(pin, &pinIndex));

	//! Determine the line mask and set values for the selected EXTI line based on the input trigger selector
	lineMask = REG_BIT_MASK(pinIndex);
	risingLineSet = ((((reg) trigger) & ((reg) GPIO_IRQ_TRIGGER_RISING)) != 0x00000000UL) ? lineMask : 0x00000000UL;
	fallingLineSet = ((((reg) trigger) & ((reg) GPIO_IRQ_TRIGGER_FALLING)) != 0x00000000UL) ? lineMask : 0x00000000UL;

	//! Clear both trigger bits for the selected EXTI line before staging the requested trigger
	ASSERT_DRIVER_STATUS
	(
		Codec_GPIO_IRQ_StageResetTrigger
		(
			updatedRtsrRegImage,
			updatedFtsrRegImage,
			pin,
			&updatedRtsrRegImage,
			&updatedFtsrRegImage
		)
	);

	//! Stage requested trigger bits for the selected EXTI line while preserving other lines
	updatedRtsrRegImage |= risingLineSet;
	updatedFtsrRegImage |= fallingLineSet;

	//! Update the caller-owned EXTI trigger images
	*pRtsrRegImage = updatedRtsrRegImage;
	*pFtsrRegImage = updatedFtsrRegImage;
	return DRIVER_STATUS_SUCCESS;
}
