/**
 * @file	gpio_irq.c
 * @author	Shrey Shah
 * @brief	GPIO IRQ Driver Implementation
 * @version	v1.0
 * @date	31-03-2026
 *
 * @details
 * This source file implements the Layer 3 GPIO IRQ driver.
 */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "gpio_irq.h"
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
//                                              Local Codecs                                           //
// ==================================================================================================== //

/**
 * @brief Extracts the lowest selected GPIO IRQ line from a GPIO pin mask
 * @param[in] pinMask GPIO pin mask identifying one or more GPIO IRQ lines
 * @returns Single-pin mask for the lowest selected GPIO IRQ line
 * @retval - @ref `GPIO_PIN_NONE`: @p pinMask has no selected line
 * @retval - @ref `GPIO_PIN_0` through @ref `GPIO_PIN_15`: Lowest selected line mask
 */
static gpio_pin_t _GPIO_IRQ_GetLowestSelectedLine(const gpio_pin_t pinMask)
{
	gpio_pin_t currentPin = GPIO_PIN_0;

	while (currentPin != GPIO_PIN_NONE)
	{
		if ((pinMask & currentPin) != GPIO_PIN_NONE)
		{
			return currentPin;
		}

		currentPin = (gpio_pin_t) (currentPin << 1U);
	}

	return GPIO_PIN_NONE;
}

/**
 * @brief Checks whether a GPIO input configuration is compatible with EXTI
 * @param[in] config Driver GPIO configuration selector
 * Accepted values:
 * - @ref `GPIO_PIN_CONFIG_INPUT_FLOATING`
 * - @ref `GPIO_PIN_CONFIG_INPUT_PULL_DOWN`
 * - @ref `GPIO_PIN_CONFIG_INPUT_PULL_UP`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p config is accepted for EXTI input usage.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p config is not accepted for EXTI input usage.
 */
static driver_status_t _GPIO_IRQ_InputConfigIsCompatible(const gpio_pin_config_t config)
{
	driver_status_t status = DRIVER_STATUS_ERROR_INVALID_ARG;

	switch (config)
	{
		case GPIO_PIN_CONFIG_INPUT_FLOATING:
		case GPIO_PIN_CONFIG_INPUT_PULL_DOWN:
		case GPIO_PIN_CONFIG_INPUT_PULL_UP:
		{
			status = DRIVER_STATUS_SUCCESS;
			break;
		}
		default:
		{
			break;
		}
	}

	return status;
}

/**
 * @brief Reads one AFIO EXTICR register image by EXTICR index
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
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: EXTICR image was read.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRegImage was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p regIndex was outside `0U..3U`.
 */
static driver_status_t _GPIO_IRQ_ReadConfigRegisterImage(const uint8_t regIndex, reg* const pRegImage)
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
 * @brief Writes one AFIO EXTICR register image by EXTICR index
 * @param[in] regIndex Zero-based EXTICR index
 * Accepted values:
 * - `0x00U`: Write `AFIO_EXTICR1`
 * - `0x01U`: Write `AFIO_EXTICR2`
 * - `0x02U`: Write `AFIO_EXTICR3`
 * - `0x03U`: Write `AFIO_EXTICR4`
 * @param[in] regImage Full EXTICR register image to write
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: EXTICR image was written.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p regIndex was outside `0U..3U`.
 */
static driver_status_t _GPIO_IRQ_WriteConfigRegisterImage(const uint8_t regIndex, const reg regImage)
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
 * @brief Disables NVIC IRQ groups whose selected GPIO IRQ lines are no longer interrupt-masked
 * @param[in] pin GPIO pin mask identifying GPIO IRQ lines being deinitialized
 * @param[in] imrRegImage Updated EXTI IMR image after selected lines were cleared
 * @details
 * EXTI0..EXTI4 own dedicated NVIC IRQs. EXTI5..EXTI9 and EXTI10..EXTI15 share
 * grouped NVIC IRQs, so those groups are disabled only when no line in the group
 * remains enabled in @p imrRegImage.
 */
static void _GPIO_IRQ_DisableIRQsForMaskedLines(const gpio_pin_t pin, const reg imrRegImage)
{
	if (((reg) pin & (reg) GPIO_PIN_0) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_0) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI0_IRQn);
		}
	}
	if (((reg) pin & (reg) GPIO_PIN_1) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_1) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI1_IRQn);
		}
	}
	if (((reg) pin & (reg) GPIO_PIN_2) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_2) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI2_IRQn);
		}
	}
	if (((reg) pin & (reg) GPIO_PIN_3) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_3) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI3_IRQn);
		}
	}
	if (((reg) pin & (reg) GPIO_PIN_4) != 0x00000000UL)
	{
		if ((imrRegImage & (reg) GPIO_PIN_4) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI4_IRQn);
		}
	}
	if (((reg) pin & GPIO_IRQ_GROUP_05_09_MASK) != 0x00000000UL)
	{
		if ((imrRegImage & GPIO_IRQ_GROUP_05_09_MASK) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI9_5_IRQn);
		}
	}
	if (((reg) pin & GPIO_IRQ_GROUP_10_15_MASK) != 0x00000000UL)
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
	reg extiImrRegImage = 0x00000000UL;
	reg extiRtsrRegImage = 0x00000000UL;
	reg extiFtsrRegImage = 0x00000000UL;
	reg afioExticrRegImage[GPIO_IRQ_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	gpio_pin_t remainingPins = pinMask;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	irq_t IRQn = (irq_t) 0x00U;
	uint8_t exticrReadStatus = 0x00U;
	uint8_t exticrUpdateStatus = 0x00U;
	uint8_t regIndex = 0x00U;

	if
	(
		(GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pinMask) == 0x00U) ||
		(GPIO_PIN_CONFIG_IS_VALID(inputConfig) == 0x00U) ||
		(_GPIO_IRQ_InputConfigIsCompatible(inputConfig) != DRIVER_STATUS_SUCCESS) ||
		(GPIO_IRQ_TRIGGER_IS_VALID(trigger) == 0x00U)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(GPIO_SetPinModeConfig(GPIOx, pinMask, GPIO_PIN_MODE_INPUT, inputConfig));
	ASSERT_DRIVER_STATUS(LL_GPIO_IRQ_EnableAFIOClock());
	extiImrRegImage = LL_GPIO_IRQ_ReadIMR();
	extiRtsrRegImage = LL_GPIO_IRQ_ReadRTSR();
	extiFtsrRegImage = LL_GPIO_IRQ_ReadFTSR();

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_IRQ_GetLowestSelectedLine(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		regIndex = (uint8_t) (GPIO_PinMaskToIndex(currentPin) >> 2U);
		if ((exticrReadStatus & (uint8_t) (0x01U << regIndex)) == 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_IRQ_ReadConfigRegisterImage(regIndex, &afioExticrRegImage[regIndex]));
			exticrReadStatus |= (uint8_t) (0x01U << regIndex);
		}

		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_UpdatePortConfigImage(GPIOx, currentPin, &afioExticrRegImage[regIndex]));
		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_UpdateTriggerImages(currentPin, trigger, &extiRtsrRegImage, &extiFtsrRegImage));
		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_GetIRQn(currentPin, &IRQn));

		exticrUpdateStatus |= (uint8_t) (0x01U << regIndex);
		extiImrRegImage |= (reg) currentPin;
		NVIC_IRQEnable((uint8_t) IRQn);
		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	for (regIndex = 0x00U; regIndex < GPIO_IRQ_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if ((exticrUpdateStatus & (uint8_t) (0x01U << regIndex)) != 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_IRQ_WriteConfigRegisterImage(regIndex, afioExticrRegImage[regIndex]));
		}
	}

	LL_GPIO_IRQ_WriteRTSR(extiRtsrRegImage);
	LL_GPIO_IRQ_WriteFTSR(extiFtsrRegImage);
	LL_GPIO_IRQ_WritePR((reg) pinMask);
	LL_GPIO_IRQ_WriteIMR(extiImrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_IRQ_Deinit(GPIO_TypeDef* const GPIOx, gpio_pin_t pin)
{
	reg extiImrRegImage = 0x00000000UL;
	reg extiRtsrRegImage = 0x00000000UL;
	reg extiFtsrRegImage = 0x00000000UL;
	reg afioExticrRegImage[GPIO_IRQ_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	uint8_t exticrReadStatus = 0x00U;
	uint8_t exticrUpdateStatus = 0x00U;
	uint8_t regIndex = 0x00U;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(LL_GPIO_IRQ_EnableAFIOClock());
	extiImrRegImage = LL_GPIO_IRQ_ReadIMR();
	extiRtsrRegImage = LL_GPIO_IRQ_ReadRTSR();
	extiFtsrRegImage = LL_GPIO_IRQ_ReadFTSR();

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_IRQ_GetLowestSelectedLine(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		regIndex = (uint8_t) (GPIO_PinMaskToIndex(currentPin) >> 2U);
		if ((exticrReadStatus & (uint8_t) (0x01U << regIndex)) == 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_IRQ_ReadConfigRegisterImage(regIndex, &afioExticrRegImage[regIndex]));
			exticrReadStatus |= (uint8_t) (0x01U << regIndex);
		}

		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_ResetPortConfigImage(currentPin, &afioExticrRegImage[regIndex]));
		ASSERT_DRIVER_STATUS(Codec_GPIO_IRQ_ResetTriggerImages(currentPin, &extiRtsrRegImage, &extiFtsrRegImage));

		exticrUpdateStatus |= (uint8_t) (0x01U << regIndex);
		extiImrRegImage &= ~((reg) currentPin);
		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	for (regIndex = 0x00U; regIndex < GPIO_IRQ_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if ((exticrUpdateStatus & (uint8_t) (0x01U << regIndex)) != 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_IRQ_WriteConfigRegisterImage(regIndex, afioExticrRegImage[regIndex]));
		}
	}

	LL_GPIO_IRQ_WriteRTSR(extiRtsrRegImage);
	LL_GPIO_IRQ_WriteFTSR(extiFtsrRegImage);
	LL_GPIO_IRQ_WritePR((reg) pin);
	LL_GPIO_IRQ_WriteIMR(extiImrRegImage);
	_GPIO_IRQ_DisableIRQsForMaskedLines(pin, extiImrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

uint8_t GPIO_IRQ_IsTriggered(const gpio_pin_t pin)
{
	reg pendingRegImage = 0x00000000UL;

	if (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U)
	{
		return (uint8_t) 0x00U;
	}

	pendingRegImage = LL_GPIO_IRQ_ReadPR();
	return ((pendingRegImage & (reg) pin) != 0x00000000UL) ? (uint8_t) 0x01U : (uint8_t) 0x00U;
}

driver_status_t GPIO_IRQ_Ack(const gpio_pin_t pin)
{
	if (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	LL_GPIO_IRQ_WritePR((reg) pin);
	return DRIVER_STATUS_SUCCESS;
}
