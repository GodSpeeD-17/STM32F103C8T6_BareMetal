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
/** @brief Shared NVIC line mask for EXTI5..EXTI9 @def GPIO_IRQ_GROUP_05_09_MASK */
#define GPIO_IRQ_GROUP_05_09_MASK						((reg) 0x000003E0UL)
/** @brief Shared NVIC line mask for EXTI10..EXTI15 @def GPIO_IRQ_GROUP_10_15_MASK */
#define GPIO_IRQ_GROUP_10_15_MASK						((reg) 0x0000FC00UL)

// ==================================================================================================== //
//                                           Local Driver Utilities                                     //
// ==================================================================================================== //

/**
 * @brief Resolves the local EXTICR image slot for one AFIO EXTICR register address
 * @param[in] pExticrRegister AFIO EXTICR `.REG` address returned by GPIO IRQ Codec
 * @param[in] pExticrRegisterTable Local table of AFIO EXTICR register addresses
 * @param[out] pRegIndex Destination for the local EXTICR image slot index
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Local EXTICR image slot was resolved.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: One or more pointers were `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pExticrRegister was not in @p pExticrRegisterTable.
 */
static driver_status_t _GPIO_IRQ_GetRoutingRegisterImageIndex
(
	const _IO* const			pExticrRegister,
	_IO* const* const			pExticrRegisterTable,
	uint8_t* const				pRegIndex
)
{
	// Local Variable
	uint8_t regIndex = 0x00U;

	// Validate Input
	if ((pExticrRegister == NULL) || (pExticrRegisterTable == NULL) || (pRegIndex == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	for (regIndex = 0x00U; regIndex < GPIO_IRQ_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if (pExticrRegister == pExticrRegisterTable[regIndex])
		{
			*pRegIndex = regIndex;
			return DRIVER_STATUS_SUCCESS;
		}
	}

	return DRIVER_STATUS_ERROR_INVALID_ARG;
}

/**
 * @brief Enables NVIC IRQ groups touched by the selected GPIO IRQ lines
 * @param[in] pinMask GPIO pin mask identifying GPIO IRQ lines being initialized
 * @details
 * EXTI0..EXTI4 own dedicated NVIC IRQs. EXTI5..EXTI9 and EXTI10..EXTI15 share
 * grouped NVIC IRQs, so those groups are enabled once when any selected line in
 * the group is initialized.
 */
static void _GPIO_IRQ_EnableIRQsForUnmaskedLines(const gpio_pin_t pinMask)
{
	if (((reg) pinMask & (reg) GPIO_PIN_0) != 0x00000000UL)
	{
		NVIC_IRQEnable((uint8_t) EXTI0_IRQn);
	}
	if (((reg) pinMask & (reg) GPIO_PIN_1) != 0x00000000UL)
	{
		NVIC_IRQEnable((uint8_t) EXTI1_IRQn);
	}
	if (((reg) pinMask & (reg) GPIO_PIN_2) != 0x00000000UL)
	{
		NVIC_IRQEnable((uint8_t) EXTI2_IRQn);
	}
	if (((reg) pinMask & (reg) GPIO_PIN_3) != 0x00000000UL)
	{
		NVIC_IRQEnable((uint8_t) EXTI3_IRQn);
	}
	if (((reg) pinMask & (reg) GPIO_PIN_4) != 0x00000000UL)
	{
		NVIC_IRQEnable((uint8_t) EXTI4_IRQn);
	}
	if (((reg) pinMask & GPIO_IRQ_GROUP_05_09_MASK) != 0x00000000UL)
	{
		NVIC_IRQEnable((uint8_t) EXTI9_5_IRQn);
	}
	if (((reg) pinMask & GPIO_IRQ_GROUP_10_15_MASK) != 0x00000000UL)
	{
		NVIC_IRQEnable((uint8_t) EXTI15_10_IRQn);
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
static void _GPIO_IRQ_DisableIRQsForMaskedLines(const gpio_pin_t pinMask, const reg imrRegImage)
{
	if (((reg) pinMask & (reg) GPIO_PIN_0) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_0) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI0_IRQn);
		}
	}
	if (((reg) pinMask & (reg) GPIO_PIN_1) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_1) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI1_IRQn);
		}
	}
	if (((reg) pinMask & (reg) GPIO_PIN_2) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_2) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI2_IRQn);
		}
	}
	if (((reg) pinMask & (reg) GPIO_PIN_3) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_3) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI3_IRQn);
		}
	}
	if (((reg) pinMask & (reg) GPIO_PIN_4) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_4) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI4_IRQn);
		}
	}
	if (((reg) pinMask & GPIO_IRQ_GROUP_05_09_MASK) != 0x00000000UL)
	{
		if ((imrRegImage & GPIO_IRQ_GROUP_05_09_MASK) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI9_5_IRQn);
		}
	}
	if (((reg) pinMask & GPIO_IRQ_GROUP_10_15_MASK) != 0x00000000UL)
	{
		if ((imrRegImage & GPIO_IRQ_GROUP_10_15_MASK) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI15_10_IRQn);
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
	driver_status_t status = DRIVER_STATUS_SUCCESS;
	reg originalExtiImrRegImage = 0x00000000UL;
	reg extiImrRegImage = 0x00000000UL;
	reg extiRtsrRegImage = 0x00000000UL;
	reg extiFtsrRegImage = 0x00000000UL;
	_IO* const pAfioExticrRegister[GPIO_IRQ_AFIO_EXTICR_COUNT] =
	{
		LL_GPIO_IRQ_AFIO_REG(EXTICR1),
		LL_GPIO_IRQ_AFIO_REG(EXTICR2),
		LL_GPIO_IRQ_AFIO_REG(EXTICR3),
		LL_GPIO_IRQ_AFIO_REG(EXTICR4)
	};
	reg afioExticrRegImage[GPIO_IRQ_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	gpio_pin_t remainingPins = pinMask;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	_IO* pExticrRegister = NULL;
	uint8_t exticrReadStatus = 0x00U;
	uint8_t exticrUpdateStatus = 0x00U;
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
	extiImrRegImage = originalExtiImrRegImage;
	if ((originalExtiImrRegImage & ((reg) pinMask)) != 0x00000000UL)
	{
		LL_GPIO_IRQ_WriteIMR(originalExtiImrRegImage & ~((reg) pinMask));
	}

	status = GPIO_SetPinModeConfig(GPIOx, pinMask, GPIO_PIN_MODE_INPUT, inputConfig);
	if (status != DRIVER_STATUS_SUCCESS)
	{
		LL_GPIO_IRQ_WriteIMR(originalExtiImrRegImage);
		return status;
	}
	extiRtsrRegImage = LL_GPIO_IRQ_ReadRTSR();
	extiFtsrRegImage = LL_GPIO_IRQ_ReadFTSR();

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = GPIO_PinMaskExtractLowestPin(remainingPins);

		pExticrRegister = Codec_GPIO_IRQ_GetRoutingRegisterAddress(currentPin);
		if (pExticrRegister == NULL)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
		ASSERT_DRIVER_STATUS(_GPIO_IRQ_GetRoutingRegisterImageIndex(pExticrRegister, pAfioExticrRegister, &regIndex));
		if ((exticrReadStatus & (uint8_t) (0x01U << regIndex)) == 0x00U)
		{
			afioExticrRegImage[regIndex] = LL_GPIO_IRQ_ReadRegister(pExticrRegister);
			exticrReadStatus |= (uint8_t) (0x01U << regIndex);
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
		ASSERT_DRIVER_STATUS
		(
			Codec_GPIO_IRQ_StageTrigger
			(
				extiRtsrRegImage,
				extiFtsrRegImage,
				currentPin,
				trigger,
				&extiRtsrRegImage,
				&extiFtsrRegImage
			)
		);

		exticrUpdateStatus |= (uint8_t) (0x01U << regIndex);
		extiImrRegImage |= (reg) currentPin;
		ASSERT_DRIVER_STATUS(GPIO_PinMaskRemovePin(&remainingPins, currentPin));
	}

	for (regIndex = 0x00U; regIndex < GPIO_IRQ_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if ((exticrUpdateStatus & (uint8_t) (0x01U << regIndex)) != 0x00U)
		{
			LL_GPIO_IRQ_WriteRegister(pAfioExticrRegister[regIndex], afioExticrRegImage[regIndex]);
		}
	}

	LL_GPIO_IRQ_WriteRTSR(extiRtsrRegImage);
	LL_GPIO_IRQ_WriteFTSR(extiFtsrRegImage);
	LL_GPIO_IRQ_WritePR((reg) pinMask);
	LL_GPIO_IRQ_WriteIMR(extiImrRegImage);
	_GPIO_IRQ_EnableIRQsForUnmaskedLines(pinMask);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_IRQ_Deinit(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask)
{
	reg originalExtiImrRegImage = 0x00000000UL;
	reg extiImrRegImage = 0x00000000UL;
	reg extiRtsrRegImage = 0x00000000UL;
	reg extiFtsrRegImage = 0x00000000UL;
	_IO* const pAfioExticrRegister[GPIO_IRQ_AFIO_EXTICR_COUNT] =
	{
		LL_GPIO_IRQ_AFIO_REG(EXTICR1),
		LL_GPIO_IRQ_AFIO_REG(EXTICR2),
		LL_GPIO_IRQ_AFIO_REG(EXTICR3),
		LL_GPIO_IRQ_AFIO_REG(EXTICR4)
	};
	reg afioExticrRegImage[GPIO_IRQ_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	gpio_pin_t remainingPins = pinMask;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	_IO* pExticrRegister = NULL;
	driver_status_t routeState = DRIVER_STATUS_OFF;
	uint8_t exticrReadStatus = 0x00U;
	uint8_t exticrUpdateStatus = 0x00U;
	uint8_t regIndex = 0x00U;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(LL_GPIO_IRQ_EnableAFIOClock());
	originalExtiImrRegImage = LL_GPIO_IRQ_ReadIMR();
	extiImrRegImage = originalExtiImrRegImage & ~((reg) pinMask);
	LL_GPIO_IRQ_WriteIMR(extiImrRegImage);
	extiRtsrRegImage = LL_GPIO_IRQ_ReadRTSR();
	extiFtsrRegImage = LL_GPIO_IRQ_ReadFTSR();

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = GPIO_PinMaskExtractLowestPin(remainingPins);

		pExticrRegister = Codec_GPIO_IRQ_GetRoutingRegisterAddress(currentPin);
		if (pExticrRegister == NULL)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}
		ASSERT_DRIVER_STATUS(_GPIO_IRQ_GetRoutingRegisterImageIndex(pExticrRegister, pAfioExticrRegister, &regIndex));
		if ((exticrReadStatus & (uint8_t) (0x01U << regIndex)) == 0x00U)
		{
			afioExticrRegImage[regIndex] = LL_GPIO_IRQ_ReadRegister(pExticrRegister);
			exticrReadStatus |= (uint8_t) (0x01U << regIndex);
		}

		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_ExtractPortRouting(afioExticrRegImage[regIndex], GPIOx, currentPin, &routeState));
		if (routeState != DRIVER_STATUS_ON)
		{
			LL_GPIO_IRQ_WriteIMR(originalExtiImrRegImage);
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
		ASSERT_DRIVER_STATUS
		(
			Codec_GPIO_IRQ_StageResetTrigger
			(
				extiRtsrRegImage,
				extiFtsrRegImage,
				currentPin,
				&extiRtsrRegImage,
				&extiFtsrRegImage
			)
		);

		exticrUpdateStatus |= (uint8_t) (0x01U << regIndex);
		ASSERT_DRIVER_STATUS(GPIO_PinMaskRemovePin(&remainingPins, currentPin));
	}

	for (regIndex = 0x00U; regIndex < GPIO_IRQ_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if ((exticrUpdateStatus & (uint8_t) (0x01U << regIndex)) != 0x00U)
		{
			LL_GPIO_IRQ_WriteRegister(pAfioExticrRegister[regIndex], afioExticrRegImage[regIndex]);
		}
	}

	LL_GPIO_IRQ_WriteRTSR(extiRtsrRegImage);
	LL_GPIO_IRQ_WriteFTSR(extiFtsrRegImage);
	LL_GPIO_IRQ_WritePR((reg) pinMask);
	LL_GPIO_IRQ_WriteIMR(extiImrRegImage);
	_GPIO_IRQ_DisableIRQsForMaskedLines(pinMask, extiImrRegImage);

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
