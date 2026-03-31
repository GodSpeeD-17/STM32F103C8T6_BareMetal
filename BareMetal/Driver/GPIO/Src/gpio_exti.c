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

// ==================================================================================================== //
//                                              Local Macros                                            //
// ==================================================================================================== //

#define GPIO_EXTI_AFIO_EXTICR_COUNT						((uint8_t) 0x04U)
#define GPIO_EXTI_GROUP_05_09_MASK						((uint32_t) 0x000003E0UL)
#define GPIO_EXTI_GROUP_10_15_MASK						((uint32_t) 0x0000FC00UL)

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
		case GPIO_PIN_CNF_IN_FLOAT:
		case GPIO_PIN_CNF_IN_PULL_DOWN:
		case GPIO_PIN_CNF_IN_PULL_UP:
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

static void _GPIO_EXTI_DisableIRQsForMaskedLines(const gpio_pin_t pin, const uint32_t imrRegImage)
{
	if ((((uint32_t) pin) & (uint32_t) GPIO_PIN_0) != 0x00000000UL)
	{
		if ((imrRegImage & (uint32_t) GPIO_PIN_0) == 0x00000000UL)
		{
			GPIO_EXTI_LL_DisableIRQ(EXTI0_IRQn);
		}
	}
	if ((((uint32_t) pin) & (uint32_t) GPIO_PIN_1) != 0x00000000UL)
	{
		if ((imrRegImage & (uint32_t) GPIO_PIN_1) == 0x00000000UL)
		{
			GPIO_EXTI_LL_DisableIRQ(EXTI1_IRQn);
		}
	}
	if ((((uint32_t) pin) & (uint32_t) GPIO_PIN_2) != 0x00000000UL)
	{
		if ((imrRegImage & (uint32_t) GPIO_PIN_2) == 0x00000000UL)
		{
			GPIO_EXTI_LL_DisableIRQ(EXTI2_IRQn);
		}
	}
	if ((((uint32_t) pin) & (uint32_t) GPIO_PIN_3) != 0x00000000UL)
	{
		if ((imrRegImage & (uint32_t) GPIO_PIN_3) == 0x00000000UL)
		{
			GPIO_EXTI_LL_DisableIRQ(EXTI3_IRQn);
		}
	}
	if ((((uint32_t) pin) & (uint32_t) GPIO_PIN_4) != 0x00000000UL)
	{
		if ((imrRegImage & (uint32_t) GPIO_PIN_4) == 0x00000000UL)
		{
			GPIO_EXTI_LL_DisableIRQ(EXTI4_IRQn);
		}
	}
	if ((((uint32_t) pin) & GPIO_EXTI_GROUP_05_09_MASK) != 0x00000000UL)
	{
		if ((imrRegImage & GPIO_EXTI_GROUP_05_09_MASK) == 0x00000000UL)
		{
			GPIO_EXTI_LL_DisableIRQ(EXTI9_5_IRQn);
		}
	}
	if ((((uint32_t) pin) & GPIO_EXTI_GROUP_10_15_MASK) != 0x00000000UL)
	{
		if ((imrRegImage & GPIO_EXTI_GROUP_10_15_MASK) == 0x00000000UL)
		{
			GPIO_EXTI_LL_DisableIRQ(EXTI15_10_IRQn);
		}
	}
}

// ==================================================================================================== //
//                                              Driver APIs                                             //
// ==================================================================================================== //

driver_status_t GPIO_EXTI_Init(GPIO_TypeDef* const GPIOx, gpio_pin_t pin, const gpio_exti_trigger_t trigger)
{
	uint32_t extiImrRegImage = 0x00000000UL;
	uint32_t extiRtsrRegImage = 0x00000000UL;
	uint32_t extiFtsrRegImage = 0x00000000UL;
	uint32_t afioExticrRegImage[GPIO_EXTI_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	gpio_pin_mode_t pinMode = GPIO_PIN_MODE_INPUT;
	gpio_pin_config_t pinConfig = GPIO_PIN_CNF_IN_ANALOG;
	irq_t IRQn = (irq_t) 0x00U;
	uint8_t exticrReadStatus = 0x00U;
	uint8_t exticrUpdateStatus = 0x00U;
	uint8_t regIndex = 0x00U;

	if ((GPIO_IS_PORT(GPIOx) == 0x00U) ||
		(GPIO_IS_PIN(pin) == 0x00U) ||
		(GPIO_EXTI_IS_TRIGGER(trigger) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	GPIO_EXTI_LL_EnableAFIOClock();
	GPIO_EXTI_LL_EXTI_READ_REG(IMR, extiImrRegImage);
	GPIO_EXTI_LL_EXTI_READ_REG(RTSR, extiRtsrRegImage);
	GPIO_EXTI_LL_EXTI_READ_REG(FTSR, extiFtsrRegImage);

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

		regIndex = (uint8_t) (_GPIO_GetPinIndexFromMask(currentPin) >> 2U);
		if ((exticrReadStatus & (uint8_t) (0x01U << regIndex)) == 0x00U)
		{
			GPIO_EXTI_LL_ReadConfigRegister(regIndex, &afioExticrRegImage[regIndex]);
			exticrReadStatus |= (uint8_t) (0x01U << regIndex);
		}

		ASSERT_DRIVER_STATUS(_GPIO_EXTI_Helper_UpdatePortConfigImage(GPIOx, currentPin, &afioExticrRegImage[regIndex]));
		ASSERT_DRIVER_STATUS(_GPIO_EXTI_Helper_UpdateTriggerImages(currentPin, trigger, &extiRtsrRegImage, &extiFtsrRegImage));
		ASSERT_DRIVER_STATUS(_GPIO_EXTI_Helper_GetIRQn(currentPin, &IRQn));

		exticrUpdateStatus |= (uint8_t) (0x01U << regIndex);
		extiImrRegImage |= (uint32_t) currentPin;
		GPIO_EXTI_LL_EnableIRQ(IRQn);
		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	for (regIndex = 0x00U; regIndex < GPIO_EXTI_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if ((exticrUpdateStatus & (uint8_t) (0x01U << regIndex)) != 0x00U)
		{
			GPIO_EXTI_LL_WriteConfigRegister(regIndex, afioExticrRegImage[regIndex]);
		}
	}

	GPIO_EXTI_LL_EXTI_WRITE_REG(RTSR, extiRtsrRegImage);
	GPIO_EXTI_LL_EXTI_WRITE_REG(FTSR, extiFtsrRegImage);
	GPIO_EXTI_LL_AckPendingLines(pin);
	GPIO_EXTI_LL_EXTI_WRITE_REG(IMR, extiImrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t GPIO_EXTI_Deinit(GPIO_TypeDef* const GPIOx, gpio_pin_t pin)
{
	uint32_t extiImrRegImage = 0x00000000UL;
	uint32_t extiRtsrRegImage = 0x00000000UL;
	uint32_t extiFtsrRegImage = 0x00000000UL;
	uint32_t afioExticrRegImage[GPIO_EXTI_AFIO_EXTICR_COUNT] = {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
	gpio_pin_t remainingPins = pin;
	gpio_pin_t currentPin = GPIO_PIN_NONE;
	uint8_t exticrReadStatus = 0x00U;
	uint8_t exticrUpdateStatus = 0x00U;
	uint8_t regIndex = 0x00U;

	if ((GPIO_IS_PORT(GPIOx) == 0x00U) || (GPIO_IS_PIN(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	GPIO_EXTI_LL_EnableAFIOClock();
	GPIO_EXTI_LL_EXTI_READ_REG(IMR, extiImrRegImage);
	GPIO_EXTI_LL_EXTI_READ_REG(RTSR, extiRtsrRegImage);
	GPIO_EXTI_LL_EXTI_READ_REG(FTSR, extiFtsrRegImage);

	while (remainingPins != GPIO_PIN_NONE)
	{
		currentPin = _GPIO_EXTI_GetLowestSelectedLine(remainingPins);
		if (currentPin == GPIO_PIN_NONE)
		{
			return DRIVER_STATUS_ERROR_STATE;
		}

		regIndex = (uint8_t) (_GPIO_GetPinIndexFromMask(currentPin) >> 2U);
		if ((exticrReadStatus & (uint8_t) (0x01U << regIndex)) == 0x00U)
		{
			GPIO_EXTI_LL_ReadConfigRegister(regIndex, &afioExticrRegImage[regIndex]);
			exticrReadStatus |= (uint8_t) (0x01U << regIndex);
		}

		ASSERT_DRIVER_STATUS(_GPIO_EXTI_Helper_ResetPortConfigImage(currentPin, &afioExticrRegImage[regIndex]));
		ASSERT_DRIVER_STATUS(_GPIO_EXTI_Helper_ResetTriggerImages(currentPin, &extiRtsrRegImage, &extiFtsrRegImage));

		exticrUpdateStatus |= (uint8_t) (0x01U << regIndex);
		extiImrRegImage &= ~((uint32_t) currentPin);
		remainingPins = (gpio_pin_t) (remainingPins & (gpio_pin_t) (~currentPin));
	}

	for (regIndex = 0x00U; regIndex < GPIO_EXTI_AFIO_EXTICR_COUNT; ++regIndex)
	{
		if ((exticrUpdateStatus & (uint8_t) (0x01U << regIndex)) != 0x00U)
		{
			GPIO_EXTI_LL_WriteConfigRegister(regIndex, afioExticrRegImage[regIndex]);
		}
	}

	GPIO_EXTI_LL_EXTI_WRITE_REG(RTSR, extiRtsrRegImage);
	GPIO_EXTI_LL_EXTI_WRITE_REG(FTSR, extiFtsrRegImage);
	GPIO_EXTI_LL_AckPendingLines(pin);
	GPIO_EXTI_LL_EXTI_WRITE_REG(IMR, extiImrRegImage);
	_GPIO_EXTI_DisableIRQsForMaskedLines(pin, extiImrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

uint8_t GPIO_EXTI_IsTriggered(const gpio_pin_t pin)
{
	uint32_t pendingRegImage = 0x00000000UL;

	if (GPIO_IS_PIN(pin) == 0x00U)
	{
		return (uint8_t) 0x00U;
	}

	GPIO_EXTI_LL_EXTI_READ_REG(PR, pendingRegImage);
	return ((pendingRegImage & (uint32_t) pin) != 0x00000000UL) ? (uint8_t) 0x01U : (uint8_t) 0x00U;
}

driver_status_t GPIO_EXTI_Ack(const gpio_pin_t pin)
{
	if (GPIO_IS_PIN(pin) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	GPIO_EXTI_LL_AckPendingLines(pin);
	return DRIVER_STATUS_SUCCESS;
}
