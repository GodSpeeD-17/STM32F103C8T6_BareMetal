/**
 * @file	gpio_helper.c
 * @author	Shrey Shah
 * @brief	GPIO Internal Driver Helper Implementation
 * @version	v1.0
 * @date	29-03-2026
 *
 * @details
 * This source file implements the internal helper utilities that bridge the
 * GPIO driver layer and the GPIO low-level layer.
 *
 * The helper layer translates driver-facing GPIO selectors into the raw
 * STM32F1 GPIO register fields required by the low-level layer and updates
 * staged register images so the driver can batch hardware writes efficiently.
 */

// ==================================================================================================== //
//											   Includes											   //
// ==================================================================================================== //
#include "gpio.h"
#include "gpio_helper.h"

// ==================================================================================================== //
//										   Local Helpers											  //
// ==================================================================================================== //

__STATIC_FORCEINLINE uint32_t _GPIO_Helper_GetPinFieldShift(const gpio_pin_t pin)
{
	uint32_t fieldShift = 0x00UL;
	gpio_pin_t tempPin = pin;

	while ((tempPin & (gpio_pin_t) 0x0001U) == GPIO_PIN_NONE)
	{
		tempPin = (gpio_pin_t)(tempPin >> 1U);
		++fieldShift;
	}

	return ((fieldShift & 0x07UL) << 2U);
}

__STATIC_FORCEINLINE uint32_t _GPIO_Helper_GetPinModeMask(const gpio_pin_t pin)
{
	return BIT_VALUE(0x03UL, _GPIO_Helper_GetPinFieldShift(pin));
}

__STATIC_FORCEINLINE uint32_t _GPIO_Helper_GetPinCnfMask(const gpio_pin_t pin)
{
	return BIT_VALUE(0x03UL, (_GPIO_Helper_GetPinFieldShift(pin) + 2U));
}

__STATIC_FORCEINLINE uint32_t _GPIO_Helper_GetPinControlMask(const gpio_pin_t pin)
{
	return BIT_VALUE(0x0FUL, _GPIO_Helper_GetPinFieldShift(pin));
}

driver_status_t _GPIO_Helper_UpdatePinModeConfigImage
(
	const gpio_pin_t pin,
	const gpio_pin_mode_t mode,
	const gpio_pin_config_t config,
	uint32_t* const pCrxRegImage
)
{
	gpio_mode_t modeBits = (gpio_mode_t) 0x00U;
	gpio_cnf_t cnfBits = (gpio_cnf_t) 0x00U;
	gpio_pin_config_bits_t pinConfigBits = (gpio_pin_config_bits_t) 0x00U;
	uint32_t regImage = 0x00UL;

	if (pCrxRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((_GPIO_HELPER_IS_SINGLE_PIN_MASK_VALID(pin) == 0x00U) ||
		(GPIO_DRIVER_PIN_IS_MODE(mode) == 0x00U) ||
		(GPIO_DRIVER_PIN_IS_CONFIG(config) == 0x00U) ||
		(GPIO_DRIVER_PIN_IS_MODE_CONFIG_COMPATIBLE(mode, config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	modeBits = (gpio_mode_t) GPIO_D2L_GetPinMode(mode);
	cnfBits = (gpio_cnf_t) GPIO_D2L_GetPinConfig(config);
	pinConfigBits = _GPIO_HELPER_GET_PIN_CONFIG_BITS(modeBits, cnfBits);

	regImage = *pCrxRegImage;
	regImage &= ~_GPIO_Helper_GetPinModeMask(pin);
	regImage |= BIT_VALUE(((uint32_t)pinConfigBits & 0x03UL), _GPIO_Helper_GetPinFieldShift(pin));
	regImage &= ~_GPIO_Helper_GetPinCnfMask(pin);
	regImage |= BIT_VALUE((((uint32_t)pinConfigBits >> 2U) & 0x03UL), (_GPIO_Helper_GetPinFieldShift(pin) + 2U));

	*pCrxRegImage = regImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t _GPIO_Helper_UpdatePinModeImage
(
	const gpio_pin_t pin,
	const gpio_pin_mode_t mode,
	uint32_t* const pCrxRegImage
)
{
	gpio_mode_t modeBits = (gpio_mode_t) 0x00U;
	uint32_t regImage = 0x00UL;

	if (pCrxRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((_GPIO_HELPER_IS_SINGLE_PIN_MASK_VALID(pin) == 0x00U) || (GPIO_DRIVER_PIN_IS_MODE(mode) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	modeBits = (gpio_mode_t) GPIO_D2L_GetPinMode(mode);
	regImage = *pCrxRegImage;
	regImage &= ~_GPIO_Helper_GetPinModeMask(pin);
	regImage |= BIT_VALUE(((uint32_t)modeBits & 0x03UL), _GPIO_Helper_GetPinFieldShift(pin));

	*pCrxRegImage = regImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t _GPIO_Helper_UpdatePinConfigImage
(
	const gpio_pin_t pin,
	const gpio_pin_config_t config,
	uint32_t* const pCrxRegImage
)
{
	gpio_cnf_t cnfBits = (gpio_cnf_t) 0x00U;
	uint32_t regImage = 0x00UL;

	if (pCrxRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((_GPIO_HELPER_IS_SINGLE_PIN_MASK_VALID(pin) == 0x00U) || (GPIO_DRIVER_PIN_IS_CONFIG(config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	cnfBits = (gpio_cnf_t) GPIO_D2L_GetPinConfig(config);
	regImage = *pCrxRegImage;
	regImage &= ~_GPIO_Helper_GetPinCnfMask(pin);
	regImage |= BIT_VALUE(((uint32_t)cnfBits & 0x03UL), (_GPIO_Helper_GetPinFieldShift(pin) + 2U));

	*pCrxRegImage = regImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t _GPIO_Helper_ResetPinConfigImage
(
	const gpio_pin_t pin,
	uint32_t* const pCrxRegImage
)
{
	return _GPIO_Helper_UpdatePinModeConfigImage(pin, GPIO_PIN_MODE_INPUT, GPIO_PIN_CNF_IN_FLOAT, pCrxRegImage);
}

driver_status_t _GPIO_Helper_UpdatePinPullImage
(
	const gpio_pin_t pin,
	const gpio_pin_config_t config,
	uint32_t* const pOdrRegImage
)
{
	gpio_pull_t pullBit = (gpio_pull_t) 0x00U;
	uint32_t regImage = 0x00UL;

	if (pOdrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((_GPIO_HELPER_IS_SINGLE_PIN_MASK_VALID(pin) == 0x00U) || (GPIO_DRIVER_PIN_IS_CONFIG(config) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	pullBit = (gpio_pull_t) GPIO_DRIVER_GET_PULL_BIT(config);
	if (_GPIO_HELPER_IS_PULL_BIT_VALID(pullBit) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	regImage = *pOdrRegImage;
	if (pullBit == (gpio_pull_t) 0x00U)
	{
		regImage &= ~(uint32_t) pin;
	}
	else
	{
		regImage |= (uint32_t) pin;
	}

	*pOdrRegImage = regImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t _GPIO_Helper_ReadPinModeConfig
(
	GPIO_TypeDef* const GPIOx,
	const gpio_pin_t pin,
	gpio_pin_mode_t* const pMode,
	gpio_pin_config_t* const pConfig
)
{
	gpio_pin_config_bits_t pinConfigBits = (gpio_pin_config_bits_t) 0x00U;
	gpio_mode_t modeBits = (gpio_mode_t) 0x00U;
	gpio_cnf_t cnfBits = (gpio_cnf_t) 0x00U;
	uint32_t regImage = 0x00UL;
	uint32_t odrRegImage = 0x00UL;

	if ((pMode == NULL) && (pConfig == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((GPIOx == NULL) || (_GPIO_HELPER_IS_SINGLE_PIN_MASK_VALID(pin) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((((uint32_t) pin) & 0xFF00UL) != 0x00UL)
	{
		GPIO_LL_READ_REG(GPIOx, CRH, regImage);
	}
	else
	{
		GPIO_LL_READ_REG(GPIOx, CRL, regImage);
	}

	pinConfigBits = (gpio_pin_config_bits_t)
	(
		(regImage & _GPIO_Helper_GetPinControlMask(pin)) >> _GPIO_Helper_GetPinFieldShift(pin)
	);

	modeBits = (gpio_mode_t) (pinConfigBits & (gpio_pin_config_bits_t) 0x03U);
	cnfBits = (gpio_cnf_t) ((pinConfigBits >> 2U) & (gpio_pin_config_bits_t) 0x03U);

	if (pMode != NULL)
	{
		switch (modeBits)
		{
			case (gpio_mode_t) 0x00U: *pMode = GPIO_PIN_MODE_INPUT; break;
			case (gpio_mode_t) 0x01U: *pMode = GPIO_PIN_MODE_OUTPUT_10MHz; break;
			case (gpio_mode_t) 0x02U: *pMode = GPIO_PIN_MODE_OUTPUT_2MHz; break;
			case (gpio_mode_t) 0x03U: *pMode = GPIO_PIN_MODE_OUTPUT_50MHz; break;
			default: return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	if (pConfig != NULL)
	{
		switch (modeBits)
		{
			case (gpio_mode_t) 0x00U:
				switch (cnfBits)
				{
					case (gpio_cnf_t) 0x00U: *pConfig = GPIO_PIN_CNF_IN_ANALOG; break;
					case (gpio_cnf_t) 0x01U: *pConfig = GPIO_PIN_CNF_IN_FLOAT; break;
					case (gpio_cnf_t) 0x02U:
						GPIO_LL_READ_REG(GPIOx, ODR, odrRegImage);
						*pConfig = ((odrRegImage & (uint32_t) pin) != 0x00UL) ? GPIO_PIN_CNF_IN_PULL_UP : GPIO_PIN_CNF_IN_PULL_DOWN;
						break;
					default:
						return DRIVER_STATUS_ERROR_INVALID_ARG;
				}
				break;
			case (gpio_mode_t) 0x01U:
			case (gpio_mode_t) 0x02U:
			case (gpio_mode_t) 0x03U:
				switch (cnfBits)
				{
					case (gpio_cnf_t) 0x00U: *pConfig = GPIO_PIN_CNF_OUT_GP_PP; break;
					case (gpio_cnf_t) 0x01U: *pConfig = GPIO_PIN_CNF_OUT_GP_OD; break;
					case (gpio_cnf_t) 0x02U: *pConfig = GPIO_PIN_CNF_OUT_AF_PP; break;
					case (gpio_cnf_t) 0x03U: *pConfig = GPIO_PIN_CNF_OUT_AF_OD; break;
					default:
						return DRIVER_STATUS_ERROR_INVALID_ARG;
				}
				break;
			default:
				return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}
