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
 * @brief Reads one AFIO EXTICR routing register image by EXTICR index
 * @param[in] regIndex Zero-based EXTICR index
 * Accepted values:
 * - `0x00U`: Read `AFIO_EXTICR1`
 * - `0x01U`: Read `AFIO_EXTICR2`
 * - `0x02U`: Read `AFIO_EXTICR3`
 * - `0x03U`: Read `AFIO_EXTICR4`
 * @param[out] pRegImage Destination for the selected EXTICR image
 * Expected values:
 * - Non-`NULL`: Register image is written to @p pRegImage
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: EXTICR routing image was read.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRegImage was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p regIndex was outside `0U..3U`.
 */
static driver_status_t _GPIO_IRQ_ReadRoutingRegisterImage(const uint8_t regIndex, reg* const pRegImage)
{
	if (pRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (regIndex)
	{
		case 0x00U:
		{
			*pRegImage = LL_GPIO_IRQ_ReadEXTICR1();
			break;
		}
		case 0x01U:
		{
			*pRegImage = LL_GPIO_IRQ_ReadEXTICR2();
			break;
		}
		case 0x02U:
		{
			*pRegImage = LL_GPIO_IRQ_ReadEXTICR3();
			break;
		}
		case 0x03U:
		{
			*pRegImage = LL_GPIO_IRQ_ReadEXTICR4();
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
 * @brief Writes one AFIO EXTICR routing register image by EXTICR index
 * @param[in] regIndex Zero-based EXTICR index
 * Accepted values:
 * - `0x00U`: Write `AFIO_EXTICR1`
 * - `0x01U`: Write `AFIO_EXTICR2`
 * - `0x02U`: Write `AFIO_EXTICR3`
 * - `0x03U`: Write `AFIO_EXTICR4`
 * @param[in] regImage Full EXTICR register image to write
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: EXTICR routing image was written.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p regIndex was outside `0U..3U`.
 */
static driver_status_t _GPIO_IRQ_WriteRoutingRegisterImage(const uint8_t regIndex, const reg regImage)
{
	switch (regIndex)
	{
		case 0x00U:
		{
			LL_GPIO_IRQ_WriteEXTICR1(regImage);
			break;
		}
		case 0x01U:
		{
			LL_GPIO_IRQ_WriteEXTICR2(regImage);
			break;
		}
		case 0x02U:
		{
			LL_GPIO_IRQ_WriteEXTICR3(regImage);
			break;
		}
		case 0x03U:
		{
			LL_GPIO_IRQ_WriteEXTICR4(regImage);
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
	reg afioExticrRegImage[GPIO_IRQ_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	gpio_pin_t remainingPins = pinMask;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	gpio_pin_index_t currentPinIndex = GPIO_PIN_INDEX_INVALID;
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
		currentPinIndex = GPIO_PinMaskToIndex(currentPin);
		if (currentPinIndex == GPIO_PIN_INDEX_INVALID)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_GetRoutingRegisterIndex(currentPinIndex, &regIndex));
		if ((exticrReadStatus & (uint8_t) (0x01U << regIndex)) == 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_IRQ_ReadRoutingRegisterImage(regIndex, &afioExticrRegImage[regIndex]));
			exticrReadStatus |= (uint8_t) (0x01U << regIndex);
		}

		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_StagePortRouting(GPIOx, currentPinIndex, &afioExticrRegImage[regIndex]));
		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_StageTrigger(currentPinIndex, trigger, &extiRtsrRegImage, &extiFtsrRegImage));

		exticrUpdateStatus |= (uint8_t) (0x01U << regIndex);
		extiImrRegImage |= (reg) currentPin;
		ASSERT_DRIVER_STATUS(GPIO_PinMaskRemovePin(&remainingPins, currentPin));
	}

	for (regIndex = 0x00U; regIndex < GPIO_IRQ_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if ((exticrUpdateStatus & (uint8_t) (0x01U << regIndex)) != 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_IRQ_WriteRoutingRegisterImage(regIndex, afioExticrRegImage[regIndex]));
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
	reg afioExticrRegImage[GPIO_IRQ_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	gpio_pin_t remainingPins = pinMask;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	gpio_pin_index_t currentPinIndex = GPIO_PIN_INDEX_INVALID;
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
		currentPinIndex = GPIO_PinMaskToIndex(currentPin);
		if (currentPinIndex == GPIO_PIN_INDEX_INVALID)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_GetRoutingRegisterIndex(currentPinIndex, &regIndex));
		if ((exticrReadStatus & (uint8_t) (0x01U << regIndex)) == 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_IRQ_ReadRoutingRegisterImage(regIndex, &afioExticrRegImage[regIndex]));
			exticrReadStatus |= (uint8_t) (0x01U << regIndex);
		}

		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_ExtractPortRoutingState(GPIOx, currentPinIndex, afioExticrRegImage[regIndex], &routeState));
		if (routeState != DRIVER_STATUS_ON)
		{
			LL_GPIO_IRQ_WriteIMR(originalExtiImrRegImage);
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_StageResetPortRouting(currentPinIndex, &afioExticrRegImage[regIndex]));
		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_StageResetTrigger(currentPinIndex, &extiRtsrRegImage, &extiFtsrRegImage));

		exticrUpdateStatus |= (uint8_t) (0x01U << regIndex);
		ASSERT_DRIVER_STATUS(GPIO_PinMaskRemovePin(&remainingPins, currentPin));
	}

	for (regIndex = 0x00U; regIndex < GPIO_IRQ_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if ((exticrUpdateStatus & (uint8_t) (0x01U << regIndex)) != 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_IRQ_WriteRoutingRegisterImage(regIndex, afioExticrRegImage[regIndex]));
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
