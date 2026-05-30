/**
 * @file	gpio_exti.c
 * @author	Shrey Shah
 * @brief	GPIO EXTI Driver Implementation
 * @version	v1.0
 * @date	31-03-2026
 *
 * @details
 * This source file implements the Layer 3 GPIO EXTI driver.
 */

// ==================================================================================================== //
//                                               Includes                                               //
// ==================================================================================================== //

#include "gpio_exti.h"
#include "gpio_exti_helper.h"
#include "gpio_exti_ll.h"
#include "nvic.h"

// ==================================================================================================== //
//                                              Local Macros                                            //
// ==================================================================================================== //

#define GPIO_EXTI_AFIO_EXTICR_COUNT						((uint8_t) 0x04U)
#define GPIO_EXTI_GROUP_05_09_MASK						((reg) 0x000003E0UL)
#define GPIO_EXTI_GROUP_10_15_MASK						((reg) 0x0000FC00UL)

// ==================================================================================================== //
//                                              Local Helpers                                           //
// ==================================================================================================== //

static gpio_pin_t _GPIO_EXTI_GetLowestSelectedLine(const gpio_pin_t pinMask)
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

static uint8_t _GPIO_EXTI_IsInputConfigCompatible(const gpio_pin_config_t config)
{
	uint8_t isCompatible = 0x00U;

	switch (config)
	{
		case GPIO_PIN_CONFIG_INPUT_FLOATING:
		case GPIO_PIN_CONFIG_INPUT_PULL_DOWN:
		case GPIO_PIN_CONFIG_INPUT_PULL_UP:
		{
			isCompatible = 0x01U;
			break;
		}
		default:
		{
			break;
		}
	}

	return isCompatible;
}

static driver_status_t _GPIO_EXTI_ReadConfigRegisterImage(const uint8_t regIndex, reg* const pRegImage)
{
	if (pRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (regIndex)
	{
		case 0x00U:
		{
			*pRegImage = LL_GPIO_EXTI_ReadEXTICR1();
			break;
		}
		case 0x01U:
		{
			*pRegImage = LL_GPIO_EXTI_ReadEXTICR2();
			break;
		}
		case 0x02U:
		{
			*pRegImage = LL_GPIO_EXTI_ReadEXTICR3();
			break;
		}
		case 0x03U:
		{
			*pRegImage = LL_GPIO_EXTI_ReadEXTICR4();
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

static driver_status_t _GPIO_EXTI_WriteConfigRegisterImage(const uint8_t regIndex, const reg regImage)
{
	switch (regIndex)
	{
		case 0x00U:
		{
			LL_GPIO_EXTI_WriteEXTICR1(regImage);
			break;
		}
		case 0x01U:
		{
			LL_GPIO_EXTI_WriteEXTICR2(regImage);
			break;
		}
		case 0x02U:
		{
			LL_GPIO_EXTI_WriteEXTICR3(regImage);
			break;
		}
		case 0x03U:
		{
			LL_GPIO_EXTI_WriteEXTICR4(regImage);
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

static void _GPIO_EXTI_DisableIRQsForMaskedLines(const gpio_pin_t pin, const reg imrRegImage)
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
	if (((reg) pin & GPIO_EXTI_GROUP_05_09_MASK) != 0x00000000UL)
	{
		if ((imrRegImage & GPIO_EXTI_GROUP_05_09_MASK) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI9_5_IRQn);
		}
	}
	if (((reg) pin & GPIO_EXTI_GROUP_10_15_MASK) != 0x00000000UL)
	{
		if ((imrRegImage & GPIO_EXTI_GROUP_10_15_MASK) == 0x00000000UL)
		{
			NVIC_IRQDisable((uint8_t) EXTI15_10_IRQn);
		}
	}
}

// ==================================================================================================== //
//                                              Driver APIs                                             //
// ==================================================================================================== //

driver_status_t GPIO_EXTI_Init(GPIO_TypeDef* const GPIOx, gpio_pin_t pin, const gpio_exti_trigger_t trigger)
{
	reg extiImrRegImage = 0x00000000UL;
	reg extiRtsrRegImage = 0x00000000UL;
	reg extiFtsrRegImage = 0x00000000UL;
	reg afioExticrRegImage[GPIO_EXTI_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	gpio_pin_mode_t pinMode = GPIO_PIN_MODE_INPUT;
	gpio_pin_config_t pinConfig = GPIO_PIN_CONFIG_INPUT_ANALOG;
	irq_t IRQn = (irq_t) 0x00U;
	uint8_t exticrReadStatus = 0x00U;
	uint8_t exticrUpdateStatus = 0x00U;
	uint8_t regIndex = 0x00U;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) ||
		(GPIO_PIN_MASK_IS_VALID(pin) == 0x00U) ||
		(GPIO_EXTI_IS_TRIGGER(trigger) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(LL_GPIO_EXTI_EnableAFIOClock());
	extiImrRegImage = LL_GPIO_EXTI_ReadIMR();
	extiRtsrRegImage = LL_GPIO_EXTI_ReadRTSR();
	extiFtsrRegImage = LL_GPIO_EXTI_ReadFTSR();

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_EXTI_GetLowestSelectedLine(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		pinMode = GPIO_GetPinMode(GPIOx, currentPin);
		pinConfig = GPIO_GetPinConfig(GPIOx, currentPin);
		if ((pinMode != GPIO_PIN_MODE_INPUT) || (_GPIO_EXTI_IsInputConfigCompatible(pinConfig) == 0x00U))
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		regIndex = (uint8_t) (GPIO_PinMaskToIndex(currentPin) >> 2U);
		if ((exticrReadStatus & (uint8_t) (0x01U << regIndex)) == 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_EXTI_ReadConfigRegisterImage(regIndex, &afioExticrRegImage[regIndex]));
			exticrReadStatus |= (uint8_t) (0x01U << regIndex);
		}

		ASSERT_DRIVER_STATUS(_GPIO_EXTI_Helper_UpdatePortConfigImage(GPIOx, currentPin, &afioExticrRegImage[regIndex]));
		ASSERT_DRIVER_STATUS(_GPIO_EXTI_Helper_UpdateTriggerImages(currentPin, trigger, &extiRtsrRegImage, &extiFtsrRegImage));
		ASSERT_DRIVER_STATUS(_GPIO_EXTI_Helper_GetIRQn(currentPin, &IRQn));

		exticrUpdateStatus |= (uint8_t) (0x01U << regIndex);
		extiImrRegImage |= (reg) currentPin;
		NVIC_IRQEnable((uint8_t) IRQn);
		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	for (regIndex = 0x00U; regIndex < GPIO_EXTI_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if ((exticrUpdateStatus & (uint8_t) (0x01U << regIndex)) != 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_EXTI_WriteConfigRegisterImage(regIndex, afioExticrRegImage[regIndex]));
		}
	}

	LL_GPIO_EXTI_WriteRTSR(extiRtsrRegImage);
	LL_GPIO_EXTI_WriteFTSR(extiFtsrRegImage);
	LL_GPIO_EXTI_WritePR((reg) pin);
	LL_GPIO_EXTI_WriteIMR(extiImrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_EXTI_Deinit(GPIO_TypeDef* const GPIOx, gpio_pin_t pin)
{
	reg extiImrRegImage = 0x00000000UL;
	reg extiRtsrRegImage = 0x00000000UL;
	reg extiFtsrRegImage = 0x00000000UL;
	reg afioExticrRegImage[GPIO_EXTI_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	uint8_t exticrReadStatus = 0x00U;
	uint8_t exticrUpdateStatus = 0x00U;
	uint8_t regIndex = 0x00U;

	if ((GPIO_PORT_IS_VALID(GPIOx) == 0x00U) || (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(LL_GPIO_EXTI_EnableAFIOClock());
	extiImrRegImage = LL_GPIO_EXTI_ReadIMR();
	extiRtsrRegImage = LL_GPIO_EXTI_ReadRTSR();
	extiFtsrRegImage = LL_GPIO_EXTI_ReadFTSR();

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_EXTI_GetLowestSelectedLine(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		regIndex = (uint8_t) (GPIO_PinMaskToIndex(currentPin) >> 2U);
		if ((exticrReadStatus & (uint8_t) (0x01U << regIndex)) == 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_EXTI_ReadConfigRegisterImage(regIndex, &afioExticrRegImage[regIndex]));
			exticrReadStatus |= (uint8_t) (0x01U << regIndex);
		}

		ASSERT_DRIVER_STATUS(_GPIO_EXTI_Helper_ResetPortConfigImage(currentPin, &afioExticrRegImage[regIndex]));
		ASSERT_DRIVER_STATUS(_GPIO_EXTI_Helper_ResetTriggerImages(currentPin, &extiRtsrRegImage, &extiFtsrRegImage));

		exticrUpdateStatus |= (uint8_t) (0x01U << regIndex);
		extiImrRegImage &= ~((reg) currentPin);
		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	for (regIndex = 0x00U; regIndex < GPIO_EXTI_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if ((exticrUpdateStatus & (uint8_t) (0x01U << regIndex)) != 0x00U)
		{
			ASSERT_DRIVER_STATUS(_GPIO_EXTI_WriteConfigRegisterImage(regIndex, afioExticrRegImage[regIndex]));
		}
	}

	LL_GPIO_EXTI_WriteRTSR(extiRtsrRegImage);
	LL_GPIO_EXTI_WriteFTSR(extiFtsrRegImage);
	LL_GPIO_EXTI_WritePR((reg) pin);
	LL_GPIO_EXTI_WriteIMR(extiImrRegImage);
	_GPIO_EXTI_DisableIRQsForMaskedLines(pin, extiImrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

uint8_t GPIO_EXTI_IsTriggered(const gpio_pin_t pin)
{
	reg pendingRegImage = 0x00000000UL;

	if (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U)
	{
		return (uint8_t) 0x00U;
	}

	pendingRegImage = LL_GPIO_EXTI_ReadPR();
	return ((pendingRegImage & (reg) pin) != 0x00000000UL) ? (uint8_t) 0x01U : (uint8_t) 0x00U;
}

driver_status_t GPIO_EXTI_Ack(const gpio_pin_t pin)
{
	if (GPIO_PIN_MASK_IS_VALID(pin) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	LL_GPIO_EXTI_WritePR((reg) pin);
	return DRIVER_STATUS_SUCCESS;
}
