/**
 * @file	gpio_irq.c
 * @author	Shrey Shah
 * @brief	GPIO IRQ Driver Implementation
 * @version	v1.0
 * @date	31-03-2026
 *
 * @details
 * This source file implements the GPIO IRQ driver layer.
 */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //
#include "gpio_irq.h"
#include "gpio.h"
#include "gpio_irq_codec.h"
#include "gpio_irq_ll.h"
#include "nvic.h"

// ==================================================================================================== //
//                                              Local Macros                                            //
// ==================================================================================================== //

/** @brief Number of AFIO EXTICR register images used for EXTI0..EXTI15 routing @def GPIO_IRQ_AFIO_EXTICR_COUNT */
#define GPIO_IRQ_AFIO_EXTICR_COUNT						((uint8_t) 0x04U)
/** @brief Pin-index shift used to select EXTICR register index @def GPIO_IRQ_EXTICR_REG_INDEX_SHIFT */
#define GPIO_IRQ_EXTICR_REG_INDEX_SHIFT					((uint8_t) 0x02U)
/** @brief Shared NVIC line mask for EXTI5..EXTI9 @def GPIO_IRQ_GROUP_05_09_MASK */
#define GPIO_IRQ_GROUP_05_09_MASK						((reg) 0x000003E0UL)
/** @brief Shared NVIC line mask for EXTI10..EXTI15 @def GPIO_IRQ_GROUP_10_15_MASK */
#define GPIO_IRQ_GROUP_10_15_MASK						((reg) 0x0000FC00UL)

// ==================================================================================================== //
//                                           Local Driver Utilities                                     //
// ==================================================================================================== //

/**
 * @brief Returns the AFIO EXTICR routing-register address for one GPIO IRQ line
 * @param[in] pin GPIO single-pin mask
 * Accepted values:
 * - @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`
 * @param[out] pRegIndex Optional destination for the local EXTICR register index
 * Expected values:
 * - Non-`NULL`: EXTICR index `0U..3U` is written to @p pRegIndex
 * - `NULL`: EXTICR index is ignored
 * @returns AFIO EXTICR `.REG` address selected by @p pin
 * @retval - Non-`NULL`: Address of `AFIO->EXTICR1.REG` through `AFIO->EXTICR4.REG`
 * @retval - `NULL`: @p pin was not a single valid pin
 * @note Routing register selection is derived as:
 * `GPIO_PinMaskToIndex(pin) >> 2U`, so pins `0..3` map to `EXTICR1`,
 * `4..7` map to `EXTICR2`, `8..11` map to `EXTICR3`, and `12..15`
 * map to `EXTICR4`.
 */
__STATIC _IO* _GPIO_IRQ_GetRoutingRegisterAddress
(
	const gpio_pin_t			pin,
	uint8_t* const				pRegIndex
)
{
	// Local Variables
	const gpio_pin_index_t pinIndex = GPIO_PinMaskToIndex(pin);
	uint8_t exticrIndex = 0x00U;
	_IO* pRegisterAddress = NULL;

	// Validate Input
	if (pinIndex == GPIO_PIN_INDEX_INVALID)
	{
		return NULL;
	}

	//! EXTICR register group is selected by pinIndex / 4, i.e. pinIndex >> 2U
	exticrIndex = (uint8_t) (pinIndex >> GPIO_IRQ_EXTICR_REG_INDEX_SHIFT);
	switch(exticrIndex)
	{
		case 0x00U:
		{
			pRegisterAddress = LL_GPIO_IRQ_AFIO_REG(EXTICR1);
			break;
		}
		case 0x01U:
		{
			pRegisterAddress = LL_GPIO_IRQ_AFIO_REG(EXTICR2);
			break;
		}
		case 0x02U:
		{
			pRegisterAddress = LL_GPIO_IRQ_AFIO_REG(EXTICR3);
			break;
		}
		case 0x03U:
		{
			pRegisterAddress = LL_GPIO_IRQ_AFIO_REG(EXTICR4);
			break;
		}
		default:
		{
			pRegisterAddress = NULL;
			break;
		}
	}

	if ((pRegisterAddress != NULL) && (pRegIndex != NULL))
	{
		*pRegIndex = exticrIndex;
	}

	return pRegisterAddress;
}

/**
 * @brief Enables NVIC IRQ groups touched by the selected GPIO IRQ lines
 * @param[in] pinMask GPIO pin mask identifying GPIO IRQ lines being initialized
 * @details
 * EXTI0..EXTI4 own dedicated NVIC IRQs. EXTI5..EXTI9 and EXTI10..EXTI15 share
 * grouped NVIC IRQs, so those groups are enabled once when any selected line in
 * the group is initialized.
 */
__STATIC void _GPIO_IRQ_UnmaskIRQForPin(const gpio_pin_t pinMask)
{
	if (((reg) pinMask & (reg) GPIO_PIN_0) != 0x00000000UL)
	{
		NVIC_IRQ_Enable((uint8_t) EXTI0_IRQn);
	}
	if (((reg) pinMask & (reg) GPIO_PIN_1) != 0x00000000UL)
	{
		NVIC_IRQ_Enable((uint8_t) EXTI1_IRQn);
	}
	if (((reg) pinMask & (reg) GPIO_PIN_2) != 0x00000000UL)
	{
		NVIC_IRQ_Enable((uint8_t) EXTI2_IRQn);
	}
	if (((reg) pinMask & (reg) GPIO_PIN_3) != 0x00000000UL)
	{
		NVIC_IRQ_Enable((uint8_t) EXTI3_IRQn);
	}
	if (((reg) pinMask & (reg) GPIO_PIN_4) != 0x00000000UL)
	{
		NVIC_IRQ_Enable((uint8_t) EXTI4_IRQn);
	}
	if (((reg) pinMask & GPIO_IRQ_GROUP_05_09_MASK) != 0x00000000UL)
	{
		NVIC_IRQ_Enable((uint8_t) EXTI9_5_IRQn);
	}
	if (((reg) pinMask & GPIO_IRQ_GROUP_10_15_MASK) != 0x00000000UL)
	{
		NVIC_IRQ_Enable((uint8_t) EXTI15_10_IRQn);
	}
}

/**
 * @brief Disables NVIC IRQ groups whose selected GPIO IRQ lines are no longer interrupt-masked
 * @param[in] pinMask GPIO pin mask identifying GPIO IRQ lines being deinitialized
 * @param[in] imrRegImage Updated EXTI IMR image after selected lines were cleared
 * @details
 * EXTI0..EXTI4 own dedicated NVIC IRQs. EXTI5..EXTI9 and EXTI10..EXTI15 share
 * grouped NVIC IRQs, so those groups are disabled only when no line in the group
 * remains enabled in @p imrRegImage.
 */
static void _GPIO_IRQ_MaskIRQForPin(const gpio_pin_t pinMask, const reg imrRegImage)
{
	if (((reg) pinMask & (reg) GPIO_PIN_0) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_0) == 0x00000000UL)
		{
			NVIC_IRQ_Disable((uint8_t) EXTI0_IRQn);
		}
	}
	if (((reg) pinMask & (reg) GPIO_PIN_1) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_1) == 0x00000000UL)
		{
			NVIC_IRQ_Disable((uint8_t) EXTI1_IRQn);
		}
	}
	if (((reg) pinMask & (reg) GPIO_PIN_2) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_2) == 0x00000000UL)
		{
			NVIC_IRQ_Disable((uint8_t) EXTI2_IRQn);
		}
	}
	if (((reg) pinMask & (reg) GPIO_PIN_3) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_3) == 0x00000000UL)
		{
			NVIC_IRQ_Disable((uint8_t) EXTI3_IRQn);
		}
	}
	if (((reg) pinMask & (reg) GPIO_PIN_4) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_4) == 0x00000000UL)
		{
			NVIC_IRQ_Disable((uint8_t) EXTI4_IRQn);
		}
	}
	if (((reg) pinMask & GPIO_IRQ_GROUP_05_09_MASK) != 0x00000000UL)
	{
		if ((imrRegImage & GPIO_IRQ_GROUP_05_09_MASK) == 0x00000000UL)
		{
			NVIC_IRQ_Disable((uint8_t) EXTI9_5_IRQn);
		}
	}
	if (((reg) pinMask & GPIO_IRQ_GROUP_10_15_MASK) != 0x00000000UL)
	{
		if ((imrRegImage & GPIO_IRQ_GROUP_10_15_MASK) == 0x00000000UL)
		{
			NVIC_IRQ_Disable((uint8_t) EXTI15_10_IRQn);
		}
	}
}

// ==================================================================================================== //
//                                              Driver APIs                                             //
// ==================================================================================================== //

driver_status_t GPIO_IRQ_Init
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pinMask,
	const gpio_pin_config_t		inputConfig,
	const gpio_irq_trigger_t		trigger
)
{
	// Local Variables
	driver_status_t status = DRIVER_STATUS_SUCCESS;
	reg originalExtiImrRegImage = 0x00000000UL;
	reg currentExtiImrRegImage = 0x00000000UL;
	reg extiImrRegImage = 0x00000000UL;
	reg originalExtiRtsrRegImage = 0x00000000UL;
	reg originalExtiFtsrRegImage = 0x00000000UL;
	reg extiRtsrRegImage = 0x00000000UL;
	reg extiFtsrRegImage = 0x00000000UL;
	reg extiPrRegImage = 0x00000000UL;
	reg originalAfioExticrRegImage[GPIO_IRQ_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	reg afioExticrRegImage[GPIO_IRQ_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	_IO* pAfioExticrRegister[GPIO_IRQ_AFIO_EXTICR_COUNT] = {NULL, NULL, NULL, NULL};
	gpio_pin_t remainingPins = pinMask;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	_IO* pExticrRegister = NULL;
	uint8_t touchedExticrStatus = 0x00U;
	uint8_t exticrStatusMask = 0x00U;
	uint8_t regIndex = 0x00U;

	if
	(
		(GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(inputConfig) == 0x00U) ||
		(GPIO_IRQ_INPUT_CONFIG_IS_VALID(inputConfig) == 0x00U) ||
		(GPIO_IRQ_TRIGGER_IS_VALID(trigger) == 0x00U)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(LL_GPIO_IRQ_EnableAFIOClock());
	originalExtiImrRegImage = LL_GPIO_IRQ_ReadIMR();
	extiImrRegImage = RegOps_StageField(originalExtiImrRegImage, (reg) pinMask, 0x00000000UL);
	currentExtiImrRegImage = originalExtiImrRegImage;
	if (extiImrRegImage != originalExtiImrRegImage)
	{
		LL_GPIO_IRQ_WriteIMR(extiImrRegImage);
		currentExtiImrRegImage = extiImrRegImage;
	}

	status = GPIO_Init(GPIOx, pinMask, GPIO_PIN_MODE_INPUT, inputConfig);
	if (status != DRIVER_STATUS_SUCCESS)
	{
		if (currentExtiImrRegImage != originalExtiImrRegImage)
		{
			LL_GPIO_IRQ_WriteIMR(originalExtiImrRegImage);
		}
		return status;
	}
	originalExtiRtsrRegImage = LL_GPIO_IRQ_ReadRTSR();
	originalExtiFtsrRegImage = LL_GPIO_IRQ_ReadFTSR();
	extiRtsrRegImage = originalExtiRtsrRegImage;
	extiFtsrRegImage = originalExtiFtsrRegImage;
	ASSERT_DRIVER_STATUS
	(
		Codec_GPIO_IRQ_StageTrigger
		(
			extiRtsrRegImage,
			extiFtsrRegImage,
			pinMask,
			trigger,
			&extiRtsrRegImage,
			&extiFtsrRegImage
		)
	);

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = GPIO_PinMaskExtractLowestPin(remainingPins);

		pExticrRegister = _GPIO_IRQ_GetRoutingRegisterAddress(currentPin, &regIndex);
		if (pExticrRegister == NULL)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
		exticrStatusMask = (uint8_t) REG_BIT_MASK(regIndex);
		if ((touchedExticrStatus & exticrStatusMask) == 0x00U)
		{
			pAfioExticrRegister[regIndex] = pExticrRegister;
			originalAfioExticrRegImage[regIndex] = LL_GPIO_IRQ_ReadRegister(pExticrRegister);
			afioExticrRegImage[regIndex] = originalAfioExticrRegImage[regIndex];
			touchedExticrStatus |= exticrStatusMask;
		}

		ASSERT_DRIVER_STATUS
		(
			Codec_GPIO_IRQ_StagePortRouting
			(
				afioExticrRegImage[regIndex],
				currentPin,
				GPIOx,
				&afioExticrRegImage[regIndex]
			)
		);
		ASSERT_DRIVER_STATUS(GPIO_PinMaskRemovePin(&remainingPins, currentPin));
	}

	for (regIndex = 0x00U; regIndex < GPIO_IRQ_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if ((touchedExticrStatus & (uint8_t) REG_BIT_MASK(regIndex)) != 0x00U)
		{
			if (afioExticrRegImage[regIndex] != originalAfioExticrRegImage[regIndex])
			{
				LL_GPIO_IRQ_WriteRegister(pAfioExticrRegister[regIndex], afioExticrRegImage[regIndex]);
			}
		}
	}

	if (extiRtsrRegImage != originalExtiRtsrRegImage)
	{
		LL_GPIO_IRQ_WriteRTSR(extiRtsrRegImage);
	}
	if (extiFtsrRegImage != originalExtiFtsrRegImage)
	{
		LL_GPIO_IRQ_WriteFTSR(extiFtsrRegImage);
	}
	extiPrRegImage = LL_GPIO_IRQ_ReadPR();
	if ((extiPrRegImage & ((reg) pinMask)) != 0x00000000UL)
	{
		LL_GPIO_IRQ_WritePR(extiPrRegImage & ((reg) pinMask));
	}
	extiImrRegImage = RegOps_StageField(currentExtiImrRegImage, (reg) pinMask, (reg) pinMask);
	if (extiImrRegImage != currentExtiImrRegImage)
	{
		LL_GPIO_IRQ_WriteIMR(extiImrRegImage);
	}
	_GPIO_IRQ_UnmaskIRQForPin(pinMask);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_IRQ_Deinit(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask)
{
	reg originalExtiImrRegImage = 0x00000000UL;
	reg currentExtiImrRegImage = 0x00000000UL;
	reg extiImrRegImage = 0x00000000UL;
	reg originalExtiRtsrRegImage = 0x00000000UL;
	reg originalExtiFtsrRegImage = 0x00000000UL;
	reg extiRtsrRegImage = 0x00000000UL;
	reg extiFtsrRegImage = 0x00000000UL;
	reg extiPrRegImage = 0x00000000UL;
	reg originalAfioExticrRegImage[GPIO_IRQ_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	reg afioExticrRegImage[GPIO_IRQ_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	_IO* pAfioExticrRegister[GPIO_IRQ_AFIO_EXTICR_COUNT] = {NULL, NULL, NULL, NULL};
	gpio_pin_t remainingPins = pinMask;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	_IO* pExticrRegister = NULL;
	GPIO_TypeDef* routedGPIOx = NULL;
	uint8_t touchedExticrStatus = 0x00U;
	uint8_t exticrStatusMask = 0x00U;
	uint8_t regIndex = 0x00U;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(LL_GPIO_IRQ_EnableAFIOClock());
	originalExtiImrRegImage = LL_GPIO_IRQ_ReadIMR();
	extiImrRegImage = RegOps_StageField(originalExtiImrRegImage, (reg) pinMask, 0x00000000UL);
	currentExtiImrRegImage = originalExtiImrRegImage;
	if (extiImrRegImage != originalExtiImrRegImage)
	{
		LL_GPIO_IRQ_WriteIMR(extiImrRegImage);
		currentExtiImrRegImage = extiImrRegImage;
	}
	originalExtiRtsrRegImage = LL_GPIO_IRQ_ReadRTSR();
	originalExtiFtsrRegImage = LL_GPIO_IRQ_ReadFTSR();
	extiRtsrRegImage = originalExtiRtsrRegImage;
	extiFtsrRegImage = originalExtiFtsrRegImage;
	ASSERT_DRIVER_STATUS
	(
		Codec_GPIO_IRQ_StageResetTrigger
		(
			extiRtsrRegImage,
			extiFtsrRegImage,
			pinMask,
			&extiRtsrRegImage,
			&extiFtsrRegImage
		)
	);

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = GPIO_PinMaskExtractLowestPin(remainingPins);

		pExticrRegister = _GPIO_IRQ_GetRoutingRegisterAddress(currentPin, &regIndex);
		if (pExticrRegister == NULL)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
		exticrStatusMask = (uint8_t) REG_BIT_MASK(regIndex);
		if ((touchedExticrStatus & exticrStatusMask) == 0x00U)
		{
			pAfioExticrRegister[regIndex] = pExticrRegister;
			originalAfioExticrRegImage[regIndex] = LL_GPIO_IRQ_ReadRegister(pExticrRegister);
			afioExticrRegImage[regIndex] = originalAfioExticrRegImage[regIndex];
			touchedExticrStatus |= exticrStatusMask;
		}

		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_ExtractPortRouting(afioExticrRegImage[regIndex], currentPin, &routedGPIOx));
		if (routedGPIOx != GPIOx)
		{
			if (currentExtiImrRegImage != originalExtiImrRegImage)
			{
				LL_GPIO_IRQ_WriteIMR(originalExtiImrRegImage);
			}
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		ASSERT_DRIVER_STATUS
		(
			Codec_GPIO_IRQ_StageResetPortRouting
			(
				afioExticrRegImage[regIndex],
				currentPin,
				&afioExticrRegImage[regIndex]
			)
		);
		ASSERT_DRIVER_STATUS(GPIO_PinMaskRemovePin(&remainingPins, currentPin));
	}

	for (regIndex = 0x00U; regIndex < GPIO_IRQ_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if ((touchedExticrStatus & (uint8_t) REG_BIT_MASK(regIndex)) != 0x00U)
		{
			if (afioExticrRegImage[regIndex] != originalAfioExticrRegImage[regIndex])
			{
				LL_GPIO_IRQ_WriteRegister(pAfioExticrRegister[regIndex], afioExticrRegImage[regIndex]);
			}
		}
	}

	if (extiRtsrRegImage != originalExtiRtsrRegImage)
	{
		LL_GPIO_IRQ_WriteRTSR(extiRtsrRegImage);
	}
	if (extiFtsrRegImage != originalExtiFtsrRegImage)
	{
		LL_GPIO_IRQ_WriteFTSR(extiFtsrRegImage);
	}
	extiPrRegImage = LL_GPIO_IRQ_ReadPR();
	if ((extiPrRegImage & ((reg) pinMask)) != 0x00000000UL)
	{
		LL_GPIO_IRQ_WritePR(extiPrRegImage & ((reg) pinMask));
	}
	_GPIO_IRQ_MaskIRQForPin(pinMask, extiImrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_IRQ_IsTriggered(const gpio_pin_t pinMask)
{
	reg pendingRegImage = 0x00000000UL;

	if (GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	pendingRegImage = LL_GPIO_IRQ_ReadPR();
	return ((pendingRegImage & (reg) pinMask) != 0x00000000UL) ? DRIVER_STATUS_ON : DRIVER_STATUS_OFF;
}

driver_status_t GPIO_IRQ_Ack(const gpio_pin_t pinMask)
{
	if (GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	LL_GPIO_IRQ_WritePR((reg) pinMask);
	return DRIVER_STATUS_SUCCESS;
}
