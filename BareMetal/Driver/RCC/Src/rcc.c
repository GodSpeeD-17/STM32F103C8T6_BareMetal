/**
 * @file	rcc.c
 * @author	Shrey Shah
 * @brief	RCC Driver Source File
 * @version	v2.2
 * @date	20-03-2026
 */

// ==================================================================================================== //
//													Includes											  //
// ==================================================================================================== //
#include "rcc.h"

// ==================================================================================================== //
//													Macros												//
// ==================================================================================================== //
/** @brief Timeout used while validating switch clock @def RCC_READY_TIMEOUT */
#define RCC_READY_TIMEOUT					((uint32_t) 1000UL)
#define RCC_DRIVER_INVALID_FIELD			((uint32_t) 0xFFFFFFFFUL)
#define RCC_DRIVER_INVALID_INDEX			((uint32_t) 0xFFFFFFFFUL)

// ==================================================================================================== //
//												Typedefs												//
// ==================================================================================================== //
/** @brief Function to be executed inside validating system clock switch @typedef _rcc_ready_getter_t */
typedef driver_status_t (*_rcc_ready_getter_t)(void);

// ==================================================================================================== //
//											Look Up Tables (LUTs)										//
// ==================================================================================================== //
typedef struct _rcc_lut_entry_t
{
	uint32_t	ll_field;
	uint32_t	value;
} _rcc_lut_entry_t;

static const _rcc_lut_entry_t _RCC_AHBPrescalerLUT[] =
{
	{ RCC_LL_AHB_DIV_1,		1UL   },
	{ RCC_LL_AHB_DIV_2,		2UL   },
	{ RCC_LL_AHB_DIV_4,		4UL   },
	{ RCC_LL_AHB_DIV_8,		8UL   },
	{ RCC_LL_AHB_DIV_16,	16UL  },
	{ RCC_LL_AHB_DIV_64,	64UL  },
	{ RCC_LL_AHB_DIV_128,	128UL },
	{ RCC_LL_AHB_DIV_256,	256UL },
	{ RCC_LL_AHB_DIV_512,	512UL }
};

static const _rcc_lut_entry_t _RCC_APBPrescalerLUT[] =
{
	{ RCC_LL_APB_DIV_1,		1UL  },
	{ RCC_LL_APB_DIV_2,		2UL  },
	{ RCC_LL_APB_DIV_4,		4UL  },
	{ RCC_LL_APB_DIV_8,		8UL  },
	{ RCC_LL_APB_DIV_16,	16UL }
};

static const _rcc_lut_entry_t _RCC_ADCPrescalerLUT[] =
{
	{ RCC_LL_ADC_DIV_2,		2UL },
	{ RCC_LL_ADC_DIV_4,		4UL },
	{ RCC_LL_ADC_DIV_6,		6UL },
	{ RCC_LL_ADC_DIV_8,		8UL }
};

static const _rcc_lut_entry_t _RCC_USBPrescalerLUT[] =
{
	{ RCC_LL_USB_DIV_1_5,	RCC_USB_DIV_1_5 },
	{ RCC_LL_USB_DIV_1,	RCC_USB_DIV_1   }
};

static const _rcc_lut_entry_t _RCC_PLLMultiplierLUT[] =
{
	{ RCC_LL_PLL_MUL_2,		RCC_PLL_MUL_2  },
	{ RCC_LL_PLL_MUL_3,		RCC_PLL_MUL_3  },
	{ RCC_LL_PLL_MUL_4,		RCC_PLL_MUL_4  },
	{ RCC_LL_PLL_MUL_5,		RCC_PLL_MUL_5  },
	{ RCC_LL_PLL_MUL_6,		RCC_PLL_MUL_6  },
	{ RCC_LL_PLL_MUL_7,		RCC_PLL_MUL_7  },
	{ RCC_LL_PLL_MUL_8,		RCC_PLL_MUL_8  },
	{ RCC_LL_PLL_MUL_9,		RCC_PLL_MUL_9  },
	{ RCC_LL_PLL_MUL_10,	RCC_PLL_MUL_10 },
	{ RCC_LL_PLL_MUL_11,	RCC_PLL_MUL_11 },
	{ RCC_LL_PLL_MUL_12,	RCC_PLL_MUL_12 },
	{ RCC_LL_PLL_MUL_13,	RCC_PLL_MUL_13 },
	{ RCC_LL_PLL_MUL_14,	RCC_PLL_MUL_14 },
	{ RCC_LL_PLL_MUL_15,	RCC_PLL_MUL_15 },
	{ RCC_LL_PLL_MUL_16,	RCC_PLL_MUL_16 }
};

// ==================================================================================================== //
//                                            Local Helpers                                             //
// ==================================================================================================== //

static driver_status_t _RCC_WaitReadyStatus(_rcc_ready_getter_t const pReadyGetter, const driver_status_t targetStatus)
{
	uint32_t timeout = RCC_READY_TIMEOUT;

	if (pReadyGetter == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	while (timeout > 0x00UL)
	{
		if (pReadyGetter() == targetStatus)
		{
			return DRIVER_STATUS_SUCCESS;
		}

		timeout--;
	}

	return DRIVER_STATUS_ERROR_TIMEOUT;
}

static driver_status_t _RCC_WaitSystemClockSource(const rcc_system_clock_t source)
{
	rcc_ll_sysclk_status_t	status = RCC_LL_SYSCLK_STATUS_HSI;
	uint32_t				timeout = RCC_READY_TIMEOUT;

	while (timeout > 0x00UL)
	{
		if (RCC_LL_GetSystemClockStatus(&status) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR;
		}

		if (((source == RCC_SYS_CLK_HSI) && (status == RCC_LL_SYSCLK_STATUS_HSI)) ||
			((source == RCC_SYS_CLK_HSE) && (status == RCC_LL_SYSCLK_STATUS_HSE)) ||
			((source == RCC_SYS_CLK_PLL) && (status == RCC_LL_SYSCLK_STATUS_PLL)))
		{
			return DRIVER_STATUS_SUCCESS;
		}

		timeout--;
	}

	return DRIVER_STATUS_ERROR_TIMEOUT;
}

static uint32_t _RCC_FindLUTIndex(const _rcc_lut_entry_t* const pLUT, const uint32_t itemCount, const uint32_t fieldValue)
{
	uint32_t index = 0x00UL;

	for (index = 0x00UL; index < itemCount; index++)
	{
		if (pLUT[index].ll_field == fieldValue)
		{
			return index;
		}
	}

	return RCC_DRIVER_INVALID_INDEX;
}

__STATIC_FORCEINLINE uint32_t _RCC_GetLUTValue(const _rcc_lut_entry_t* const pLUT, const uint32_t itemCount, const uint32_t index, const uint32_t defaultValue)
{
	if (index >= itemCount)
	{
		return defaultValue;
	}

	return pLUT[index].value;
}

__STATIC_FORCEINLINE rcc_freq_t _RCC_GetAHBDividerValue(const rcc_bus_prescaler_t dividerSelector)
{
	return (rcc_freq_t) _RCC_GetLUTValue
	(
		_RCC_AHBPrescalerLUT,
		(uint32_t) (sizeof(_RCC_AHBPrescalerLUT) / sizeof(_RCC_AHBPrescalerLUT[0])),
		(uint32_t) dividerSelector,
		1UL
	);
}

__STATIC_FORCEINLINE rcc_freq_t _RCC_GetAPBDividerValue(const rcc_bus_prescaler_t dividerSelector)
{
	return (rcc_freq_t) _RCC_GetLUTValue
	(
		_RCC_APBPrescalerLUT,
		(uint32_t) (sizeof(_RCC_APBPrescalerLUT) / sizeof(_RCC_APBPrescalerLUT[0])),
		(uint32_t) dividerSelector,
		1UL
	);
}

__STATIC_FORCEINLINE rcc_freq_t _RCC_GetADCDividerValue(const rcc_component_prescaler_t dividerSelector)
{
	return (rcc_freq_t) _RCC_GetLUTValue
	(
		_RCC_ADCPrescalerLUT,
		(uint32_t) (sizeof(_RCC_ADCPrescalerLUT) / sizeof(_RCC_ADCPrescalerLUT[0])),
		(uint32_t) dividerSelector,
		2UL
	);
}

__STATIC_FORCEINLINE uint32_t _RCC_MapSystemClockSource(const rcc_system_clock_t source)
{
	switch (source)
	{
		case RCC_SYS_CLK_HSI:
		{
			return RCC_LL_SYSCLK_SRC_HSI;
		}
		case RCC_SYS_CLK_HSE:
		{
			return RCC_LL_SYSCLK_SRC_HSE;
		}
		case RCC_SYS_CLK_PLL:
		{
			return RCC_LL_SYSCLK_SRC_PLL;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

__STATIC_FORCEINLINE uint32_t _RCC_MapPLLSource(const rcc_pll_src_t source)
{
	switch (source)
	{
		case RCC_PLL_SRC_HSI:
		{
			return RCC_LL_PLL_SRC_HSI_DIV2;
		}
		case RCC_PLL_SRC_HSE:
		{
			return RCC_LL_PLL_SRC_HSE;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

__STATIC_FORCEINLINE uint32_t _RCC_MapPLLHSEDivider(const rcc_pll_src_psc_t divider)
{
	switch (divider)
	{
		case RCC_PLL_SRC_HSE_DIV_1:
		{
			return RCC_LL_PLL_HSE_DIV_1;
		}
		case RCC_PLL_SRC_HSE_DIV_2:
		{
			return RCC_LL_PLL_HSE_DIV_2;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

__STATIC_FORCEINLINE uint32_t _RCC_MapPLLMultiplier(const rcc_pll_mul_t multiplier)
{
	if ((multiplier < RCC_PLL_MUL_2) || (multiplier > RCC_PLL_MUL_16))
	{
		return RCC_DRIVER_INVALID_FIELD;
	}

	return _RCC_GetLUTValue
	(
		_RCC_PLLMultiplierLUT,
		(uint32_t) (sizeof(_RCC_PLLMultiplierLUT) / sizeof(_RCC_PLLMultiplierLUT[0])),
		(uint32_t) (multiplier - RCC_PLL_MUL_2),
		RCC_DRIVER_INVALID_FIELD
	);
}

__STATIC_FORCEINLINE uint32_t _RCC_MapAHBPrescaler(const rcc_bus_prescaler_t dividerSelector)
{
	return _RCC_GetLUTValue
	(
		_RCC_AHBPrescalerLUT,
		(uint32_t) (sizeof(_RCC_AHBPrescalerLUT) / sizeof(_RCC_AHBPrescalerLUT[0])),
		(uint32_t) dividerSelector,
		RCC_DRIVER_INVALID_FIELD
	);
}

__STATIC_FORCEINLINE uint32_t _RCC_MapAPBPrescaler(const rcc_bus_prescaler_t dividerSelector)
{
	return _RCC_GetLUTValue
	(
		_RCC_APBPrescalerLUT,
		(uint32_t) (sizeof(_RCC_APBPrescalerLUT) / sizeof(_RCC_APBPrescalerLUT[0])),
		(uint32_t) dividerSelector,
		RCC_DRIVER_INVALID_FIELD
	);
}

__STATIC_FORCEINLINE uint32_t _RCC_MapADCPrescaler(const rcc_component_prescaler_t dividerSelector)
{
	return _RCC_GetLUTValue
	(
		_RCC_ADCPrescalerLUT,
		(uint32_t) (sizeof(_RCC_ADCPrescalerLUT) / sizeof(_RCC_ADCPrescalerLUT[0])),
		(uint32_t) dividerSelector,
		RCC_DRIVER_INVALID_FIELD
	);
}

__STATIC_FORCEINLINE uint32_t _RCC_MapUSBPrescaler(const rcc_component_prescaler_t dividerSelector)
{
	return _RCC_GetLUTValue
	(
		_RCC_USBPrescalerLUT,
		(uint32_t) (sizeof(_RCC_USBPrescalerLUT) / sizeof(_RCC_USBPrescalerLUT[0])),
		(uint32_t) dividerSelector,
		RCC_DRIVER_INVALID_FIELD
	);
}

__STATIC_FORCEINLINE rcc_system_clock_t _RCC_DecodeSystemClockStatus(const rcc_ll_sysclk_status_t status)
{
	switch (status)
	{
		case RCC_LL_SYSCLK_STATUS_HSI:
		{
			return RCC_SYS_CLK_HSI;
		}
		case RCC_LL_SYSCLK_STATUS_HSE:
		{
			return RCC_SYS_CLK_HSE;
		}
		case RCC_LL_SYSCLK_STATUS_PLL:
		{
			return RCC_SYS_CLK_PLL;
		}
		default:
		{
			return RCC_SYS_CLK_HSI;
		}
	}
}

static rcc_bus_prescaler_t _RCC_DecodeAHBPrescaler(const rcc_ll_ahb_prescaler_t prescaler)
{
	const uint32_t index = _RCC_FindLUTIndex
	(
		_RCC_AHBPrescalerLUT,
		(uint32_t) (sizeof(_RCC_AHBPrescalerLUT) / sizeof(_RCC_AHBPrescalerLUT[0])),
		(uint32_t) prescaler
	);

	if (index == RCC_DRIVER_INVALID_INDEX)
	{
		return RCC_AHB_DIV_1;
	}

	return (rcc_bus_prescaler_t) index;
}

static rcc_bus_prescaler_t _RCC_DecodeAPBPrescaler(const rcc_ll_apb_prescaler_t prescaler)
{
	const uint32_t index = _RCC_FindLUTIndex
	(
		_RCC_APBPrescalerLUT,
		(uint32_t) (sizeof(_RCC_APBPrescalerLUT) / sizeof(_RCC_APBPrescalerLUT[0])),
		(uint32_t) prescaler
	);

	if (index == RCC_DRIVER_INVALID_INDEX)
	{
		return RCC_APB1_DIV_1;
	}

	return (rcc_bus_prescaler_t) index;
}

static rcc_component_prescaler_t _RCC_DecodeADCPrescaler(const rcc_ll_adc_prescaler_t prescaler)
{
	const uint32_t index = _RCC_FindLUTIndex
	(
		_RCC_ADCPrescalerLUT,
		(uint32_t) (sizeof(_RCC_ADCPrescalerLUT) / sizeof(_RCC_ADCPrescalerLUT[0])),
		(uint32_t) prescaler
	);

	if (index == RCC_DRIVER_INVALID_INDEX)
	{
		return RCC_ADC_DIV_2;
	}

	return (rcc_component_prescaler_t) index;
}

static rcc_component_prescaler_t _RCC_DecodeUSBPrescaler(const rcc_ll_usb_prescaler_t prescaler)
{
	const uint32_t index = _RCC_FindLUTIndex
	(
		_RCC_USBPrescalerLUT,
		(uint32_t) (sizeof(_RCC_USBPrescalerLUT) / sizeof(_RCC_USBPrescalerLUT[0])),
		(uint32_t) prescaler
	);

	if (index == RCC_DRIVER_INVALID_INDEX)
	{
		return RCC_USB_DIV_1_5;
	}

	return (rcc_component_prescaler_t) index;
}

__STATIC_FORCEINLINE rcc_freq_t _RCC_ComputePLLInputFreq(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	if (pClockTreeConfig->system.pll.source == RCC_PLL_SRC_HSI)
	{
		return (RCC_HSI_FREQ >> 1);
	}
	else
	{
		if (pClockTreeConfig->system.pll.source_prescaler == RCC_PLL_SRC_HSE_DIV_2)
		{
			return (RCC_HSE_FREQ >> 1);
		}
		else
		{
			return RCC_HSE_FREQ;
		}
	}
}

static rcc_freq_t _RCC_ComputeSYSCLK(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	switch (pClockTreeConfig->system.clk_src)
	{
		case RCC_SYS_CLK_HSI:
		{
			return RCC_HSI_FREQ;
		}
		case RCC_SYS_CLK_HSE:
		{
			return RCC_HSE_FREQ;
		}
		case RCC_SYS_CLK_PLL:
		{
			return (_RCC_ComputePLLInputFreq(pClockTreeConfig) * (rcc_freq_t) pClockTreeConfig->system.pll.multiplication_factor);
		}
		default:
		{
			return RCC_FREQ_ZERO;
		}
	}
}

__STATIC_FORCEINLINE rcc_freq_t _RCC_ComputeHCLK(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	return (_RCC_ComputeSYSCLK(pClockTreeConfig) / _RCC_GetAHBDividerValue(pClockTreeConfig->bus.AHB));
}

__STATIC_FORCEINLINE rcc_freq_t _RCC_ComputePCLK1(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	return (_RCC_ComputeHCLK(pClockTreeConfig) / _RCC_GetAPBDividerValue(pClockTreeConfig->bus.APB1));
}

__STATIC_FORCEINLINE rcc_freq_t _RCC_ComputePCLK2(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	return (_RCC_ComputeHCLK(pClockTreeConfig) / _RCC_GetAPBDividerValue(pClockTreeConfig->bus.APB2));
}

__STATIC_FORCEINLINE rcc_freq_t _RCC_ComputeADCCLK(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	return (_RCC_ComputePCLK2(pClockTreeConfig) / _RCC_GetADCDividerValue(pClockTreeConfig->component.ADC));
}

static rcc_freq_t _RCC_ComputeUSBCLK(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	const rcc_freq_t pllClock = _RCC_ComputePLLInputFreq(pClockTreeConfig) * (rcc_freq_t) pClockTreeConfig->system.pll.multiplication_factor;

	if (pClockTreeConfig->system.clk_src != RCC_SYS_CLK_PLL)
	{
		return RCC_FREQ_ZERO;
	}

	if (pClockTreeConfig->component.USB == RCC_USB_DIV_1)
	{
		return pllClock;
	}
	else
	{
		return ((pllClock << 1) / 3U);
	}
}

// ==================================================================================================== //
//                                   Driver Clock Gate and Reset APIs                                   //
// ==================================================================================================== //

driver_status_t RCC_ValidateConfig(const rcc_config_t* const pRCCConfig)
{
	const rcc_clock_tree_config_t* pClockTreeConfig = NULL;
	rcc_freq_t sysClk = RCC_FREQ_ZERO;
	rcc_freq_t hClk = RCC_FREQ_ZERO;
	rcc_freq_t pClk1 = RCC_FREQ_ZERO;
	rcc_freq_t pClk2 = RCC_FREQ_ZERO;
	rcc_freq_t adcClk = RCC_FREQ_ZERO;
	rcc_freq_t usbClk = RCC_FREQ_ZERO;

	if (pRCCConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	pClockTreeConfig = &(pRCCConfig->clock_tree);

	if (_RCC_MapSystemClockSource(pClockTreeConfig->system.clk_src) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_MapAHBPrescaler(pClockTreeConfig->bus.AHB) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_MapAPBPrescaler(pClockTreeConfig->bus.APB1) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_MapAPBPrescaler(pClockTreeConfig->bus.APB2) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_MapADCPrescaler(pClockTreeConfig->component.ADC) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_MapUSBPrescaler(pClockTreeConfig->component.USB) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((pRCCConfig->flash.latency > RCC_FLASH_LATENCY_2) || (pRCCConfig->flash.prefetch > RCC_FLASH_PREFETCH_ENABLE))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL)
	{
		if (_RCC_MapPLLSource(pClockTreeConfig->system.pll.source) == RCC_DRIVER_INVALID_FIELD)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		if (_RCC_MapPLLMultiplier(pClockTreeConfig->system.pll.multiplication_factor) == RCC_DRIVER_INVALID_FIELD)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		if (pClockTreeConfig->system.pll.source == RCC_PLL_SRC_HSI)
		{
			if (pClockTreeConfig->system.pll.source_prescaler != RCC_PLL_SRC_HSI_DIV_2)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
		}
		else
		{
			if (_RCC_MapPLLHSEDivider(pClockTreeConfig->system.pll.source_prescaler) == RCC_DRIVER_INVALID_FIELD)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}
		}
	}

	sysClk = _RCC_ComputeSYSCLK(pClockTreeConfig);
	hClk = _RCC_ComputeHCLK(pClockTreeConfig);
	pClk1 = _RCC_ComputePCLK1(pClockTreeConfig);
	pClk2 = _RCC_ComputePCLK2(pClockTreeConfig);
	adcClk = _RCC_ComputeADCCLK(pClockTreeConfig);
	usbClk = _RCC_ComputeUSBCLK(pClockTreeConfig);

	if (sysClk > RCC_SYSCLK_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (hClk > RCC_HCLK_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (pClk1 > RCC_PCLK1_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (pClk2 > RCC_PCLK2_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (adcClk > RCC_ADCCLK_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL) && (usbClk != RCC_FREQ_ZERO) && (usbClk != RCC_USBCLK_TARGET_FREQ))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((sysClk <= RCC_FLASH_LATENCY_0_MAX_FREQ) && (pRCCConfig->flash.latency != RCC_FLASH_LATENCY_0))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((sysClk > RCC_FLASH_LATENCY_0_MAX_FREQ) && (sysClk <= RCC_FLASH_LATENCY_1_MAX_FREQ) && (pRCCConfig->flash.latency != RCC_FLASH_LATENCY_1))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((sysClk > RCC_FLASH_LATENCY_1_MAX_FREQ) && (pRCCConfig->flash.latency != RCC_FLASH_LATENCY_2))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigFlash(const rcc_flash_config_t* const pFlashConfig)
{
	uint32_t flashLatency = FLASH_ACR_LATENCY_0;

	if (pFlashConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (pFlashConfig->latency)
	{
		case RCC_FLASH_LATENCY_0:
		{
			flashLatency = FLASH_ACR_LATENCY_0;
			break;
		}
		case RCC_FLASH_LATENCY_1:
		{
			flashLatency = FLASH_ACR_LATENCY_1;
			break;
		}
		case RCC_FLASH_LATENCY_2:
		{
			flashLatency = FLASH_ACR_LATENCY_2;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	REGOPS_MODIFY(&FLASH->ACR.REG, FLASH_ACR_LATENCY_Msk, flashLatency);

	if (pFlashConfig->prefetch == RCC_FLASH_PREFETCH_ENABLE)
	{
		REGOPS_SET(&FLASH->ACR.REG, FLASH_ACR_PRFTBE);
	}
	else
	{
		REGOPS_CLEAR(&FLASH->ACR.REG, FLASH_ACR_PRFTBE);
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigBusPrescaler(const rcc_bus_config_t* const pBusConfig)
{
	uint32_t ahbPrescaler = 0x00UL;
	uint32_t apb1Prescaler = 0x00UL;
	uint32_t apb2Prescaler = 0x00UL;

	if (pBusConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ahbPrescaler = _RCC_MapAHBPrescaler(pBusConfig->AHB);
	apb1Prescaler = _RCC_MapAPBPrescaler(pBusConfig->APB1);
	apb2Prescaler = _RCC_MapAPBPrescaler(pBusConfig->APB2);

	if ((ahbPrescaler == RCC_DRIVER_INVALID_FIELD) || (apb1Prescaler == RCC_DRIVER_INVALID_FIELD) || (apb2Prescaler == RCC_DRIVER_INVALID_FIELD))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(RCC_LL_SetAHBPrescaler((rcc_ll_ahb_prescaler_t) ahbPrescaler));
	ASSERT_DRIVER_STATUS(RCC_LL_SetAPB1Prescaler((rcc_ll_apb_prescaler_t) apb1Prescaler));
	ASSERT_DRIVER_STATUS(RCC_LL_SetAPB2Prescaler((rcc_ll_apb_prescaler_t) apb2Prescaler));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigComponentPrescaler(const rcc_component_config_t* const pComponentConfig)
{
	uint32_t adcPrescaler = 0x00UL;
	uint32_t usbPrescaler = 0x00UL;

	if (pComponentConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	adcPrescaler = _RCC_MapADCPrescaler(pComponentConfig->ADC);
	usbPrescaler = _RCC_MapUSBPrescaler(pComponentConfig->USB);

	if ((adcPrescaler == RCC_DRIVER_INVALID_FIELD) || (usbPrescaler == RCC_DRIVER_INVALID_FIELD))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(RCC_LL_SetADCPrescaler((rcc_ll_adc_prescaler_t) adcPrescaler));
	ASSERT_DRIVER_STATUS(RCC_LL_SetUSBPrescaler((rcc_ll_usb_prescaler_t) usbPrescaler));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SwitchClockSourceToHSI(void)
{
	RCC_LL_HSI_Enable();
	ASSERT_DRIVER_STATUS(_RCC_WaitReadyStatus(RCC_LL_HSI_GetReadyStatus, DRIVER_STATUS_READY));
	ASSERT_DRIVER_STATUS(RCC_LL_SetSystemClockSource(RCC_LL_SYSCLK_SRC_HSI));
	ASSERT_DRIVER_STATUS(_RCC_WaitSystemClockSource(RCC_SYS_CLK_HSI));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SwitchClockSourceToHSE(void)
{
	RCC_LL_HSE_Enable();
	ASSERT_DRIVER_STATUS(_RCC_WaitReadyStatus(RCC_LL_HSE_GetReadyStatus, DRIVER_STATUS_READY));
	ASSERT_DRIVER_STATUS(RCC_LL_SetSystemClockSource(RCC_LL_SYSCLK_SRC_HSE));
	ASSERT_DRIVER_STATUS(_RCC_WaitSystemClockSource(RCC_SYS_CLK_HSE));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SwitchClockSourceToPLL(void)
{
	if (RCC_LL_PLL_GetReadyStatus() != DRIVER_STATUS_READY)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	ASSERT_DRIVER_STATUS(RCC_LL_SetSystemClockSource(RCC_LL_SYSCLK_SRC_PLL));
	ASSERT_DRIVER_STATUS(_RCC_WaitSystemClockSource(RCC_SYS_CLK_PLL));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigClockTree(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	rcc_system_clock_t activeSource = RCC_SYS_CLK_HSI;
	uint32_t pllSource = 0x00UL;
	uint32_t pllDivider = 0x00UL;
	uint32_t pllMultiplier = 0x00UL;

	if (pClockTreeConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	activeSource = RCC_GetSysClkSrc();
	RCC_LL_HSI_Enable();
	ASSERT_DRIVER_STATUS(_RCC_WaitReadyStatus(RCC_LL_HSI_GetReadyStatus, DRIVER_STATUS_READY));

	if (activeSource == RCC_SYS_CLK_PLL)
	{
		ASSERT_DRIVER_STATUS(RCC_SwitchClockSourceToHSI());
	}

	if ((pClockTreeConfig->system.clk_src == RCC_SYS_CLK_HSE) ||
		((pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL) && (pClockTreeConfig->system.pll.source == RCC_PLL_SRC_HSE)))
	{
		RCC_LL_HSE_Enable();
		ASSERT_DRIVER_STATUS(_RCC_WaitReadyStatus(RCC_LL_HSE_GetReadyStatus, DRIVER_STATUS_READY));
	}

	if (RCC_LL_PLL_GetReadyStatus() == DRIVER_STATUS_READY)
	{
		RCC_LL_PLL_Disable();
		ASSERT_DRIVER_STATUS(_RCC_WaitReadyStatus(RCC_LL_PLL_GetReadyStatus, DRIVER_STATUS_OFF));
	}

	ASSERT_DRIVER_STATUS(RCC_ConfigBusPrescaler(&pClockTreeConfig->bus));
	ASSERT_DRIVER_STATUS(RCC_ConfigComponentPrescaler(&pClockTreeConfig->component));

	if (pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL)
	{
		pllSource = _RCC_MapPLLSource(pClockTreeConfig->system.pll.source);
		pllMultiplier = _RCC_MapPLLMultiplier(pClockTreeConfig->system.pll.multiplication_factor);

		if ((pllSource == RCC_DRIVER_INVALID_FIELD) || (pllMultiplier == RCC_DRIVER_INVALID_FIELD))
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		ASSERT_DRIVER_STATUS(RCC_LL_SetPLLSource((rcc_ll_pll_src_t) pllSource));

		if (pClockTreeConfig->system.pll.source == RCC_PLL_SRC_HSE)
		{
			pllDivider = _RCC_MapPLLHSEDivider(pClockTreeConfig->system.pll.source_prescaler);
			if (pllDivider == RCC_DRIVER_INVALID_FIELD)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}

			ASSERT_DRIVER_STATUS(RCC_LL_SetPLLHSEDivider((rcc_ll_pll_hse_div_t) pllDivider));
		}

		ASSERT_DRIVER_STATUS(RCC_LL_SetPLLMultiplier((rcc_ll_pll_mul_t) pllMultiplier));
		RCC_LL_PLL_Enable();
		ASSERT_DRIVER_STATUS(_RCC_WaitReadyStatus(RCC_LL_PLL_GetReadyStatus, DRIVER_STATUS_READY));
	}

	switch (pClockTreeConfig->system.clk_src)
	{
		case RCC_SYS_CLK_HSI:
		{
			ASSERT_DRIVER_STATUS(RCC_SwitchClockSourceToHSI());
			break;
		}
		case RCC_SYS_CLK_HSE:
		{
			ASSERT_DRIVER_STATUS(RCC_SwitchClockSourceToHSE());
			break;
		}
		case RCC_SYS_CLK_PLL:
		{
			ASSERT_DRIVER_STATUS(RCC_SwitchClockSourceToPLL());
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_Config(const rcc_config_t* const pRCCConfig)
{
	ASSERT_DRIVER_STATUS(RCC_ValidateConfig(pRCCConfig));
	ASSERT_DRIVER_STATUS(RCC_ConfigFlash(&(pRCCConfig->flash)));
	ASSERT_DRIVER_STATUS(RCC_ConfigClockTree(&(pRCCConfig->clock_tree)));
	return DRIVER_STATUS_SUCCESS;
}

void RCC_72MHz_LoadDefaultConfig(rcc_config_t* const pRCCConfig)
{
	if (pRCCConfig == NULL)
	{
		return;
	}

	pRCCConfig->flash.latency = RCC_FLASH_LATENCY_2;
	pRCCConfig->flash.prefetch = RCC_FLASH_PREFETCH_ENABLE;

	pRCCConfig->clock_tree.system.clk_src = RCC_SYS_CLK_PLL;
	pRCCConfig->clock_tree.system.pll.source = RCC_PLL_SRC_HSE;
	pRCCConfig->clock_tree.system.pll.source_prescaler = RCC_PLL_SRC_HSE_DIV_1;
	pRCCConfig->clock_tree.system.pll.multiplication_factor = RCC_PLL_MUL_9;

	pRCCConfig->clock_tree.bus.AHB = RCC_AHB_DIV_1;
	pRCCConfig->clock_tree.bus.APB1 = RCC_APB1_DIV_2;
	pRCCConfig->clock_tree.bus.APB2 = RCC_APB2_DIV_1;

	pRCCConfig->clock_tree.component.ADC = RCC_ADC_DIV_6;
	pRCCConfig->clock_tree.component.USB = RCC_USB_DIV_1_5;
}

driver_status_t RCC_Config_72MHz(void)
{
	rcc_config_t cfg;

	RCC_72MHz_LoadDefaultConfig(&cfg);
	return RCC_Config(&cfg);
}

// ==================================================================================================== //
//                                   Driver Status and Frequency APIs                                   //
// ==================================================================================================== //

rcc_system_clock_t RCC_GetSysClkSrc(void)
{
	rcc_ll_sysclk_status_t status = RCC_LL_SYSCLK_STATUS_HSI;

	if (RCC_LL_GetSystemClockStatus(&status) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_SYS_CLK_HSI;
	}

	return _RCC_DecodeSystemClockStatus(status);
}

rcc_pll_src_t RCC_GetPLLSource(void)
{
	rcc_ll_pll_src_t source = RCC_LL_PLL_SRC_HSI_DIV2;

	if (RCC_LL_GetPLLSource(&source) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_PLL_SRC_HSI;
	}

	if (source == RCC_LL_PLL_SRC_HSE)
	{
		return RCC_PLL_SRC_HSE;
	}
	else
	{
		return RCC_PLL_SRC_HSI;
	}
}

rcc_pll_src_psc_t RCC_GetPLLSourcePrescaler(void)
{
	rcc_ll_pll_hse_div_t divider = RCC_LL_PLL_HSE_DIV_1;

	if (RCC_GetPLLSource() == RCC_PLL_SRC_HSI)
	{
		return RCC_PLL_SRC_HSI_DIV_2;
	}

	if (RCC_LL_GetPLLHSEDivider(&divider) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_PLL_SRC_HSE_DIV_1;
	}

	if (divider == RCC_LL_PLL_HSE_DIV_2)
	{
		return RCC_PLL_SRC_HSE_DIV_2;
	}
	else
	{
		return RCC_PLL_SRC_HSE_DIV_1;
	}
}

rcc_pll_mul_t RCC_GetPLLMultiplier(void)
{
	rcc_ll_pll_mul_t multiplier = RCC_LL_PLL_MUL_2;

	if (RCC_LL_GetPLLMultiplier(&multiplier) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_PLL_MUL_2;
	}

	switch (multiplier)
	{
		case RCC_LL_PLL_MUL_2:
		{
			return RCC_PLL_MUL_2;
		}
		case RCC_LL_PLL_MUL_3:
		{
			return RCC_PLL_MUL_3;
		}
		case RCC_LL_PLL_MUL_4:
		{
			return RCC_PLL_MUL_4;
		}
		case RCC_LL_PLL_MUL_5:
		{
			return RCC_PLL_MUL_5;
		}
		case RCC_LL_PLL_MUL_6:
		{
			return RCC_PLL_MUL_6;
		}
		case RCC_LL_PLL_MUL_7:
		{
			return RCC_PLL_MUL_7;
		}
		case RCC_LL_PLL_MUL_8:
		{
			return RCC_PLL_MUL_8;
		}
		case RCC_LL_PLL_MUL_9:
		{
			return RCC_PLL_MUL_9;
		}
		case RCC_LL_PLL_MUL_10:
		{
			return RCC_PLL_MUL_10;
		}
		case RCC_LL_PLL_MUL_11:
		{
			return RCC_PLL_MUL_11;
		}
		case RCC_LL_PLL_MUL_12:
		{
			return RCC_PLL_MUL_12;
		}
		case RCC_LL_PLL_MUL_13:
		{
			return RCC_PLL_MUL_13;
		}
		case RCC_LL_PLL_MUL_14:
		{
			return RCC_PLL_MUL_14;
		}
		case RCC_LL_PLL_MUL_15:
		{
			return RCC_PLL_MUL_15;
		}
		case RCC_LL_PLL_MUL_16:
		{
			return RCC_PLL_MUL_16;
		}
		default:
		{
			return RCC_PLL_MUL_2;
		}
	}
}

rcc_freq_t RCC_GetCoreClockFreq(void)
{
	rcc_freq_t pllInput = RCC_FREQ_ZERO;

	switch (RCC_GetSysClkSrc())
	{
		case RCC_SYS_CLK_HSI:
		{
			return RCC_HSI_FREQ;
		}
		case RCC_SYS_CLK_HSE:
		{
			return RCC_HSE_FREQ;
		}
		case RCC_SYS_CLK_PLL:
		{
			pllInput = (RCC_GetPLLSource() == RCC_PLL_SRC_HSE) ? RCC_HSE_FREQ : (RCC_HSI_FREQ >> 1);
			if (RCC_GetPLLSourcePrescaler() == RCC_PLL_SRC_HSE_DIV_2)
			{
				pllInput >>= 1;
			}
			return (pllInput * (rcc_freq_t) RCC_GetPLLMultiplier());
		}
		default:
		{
			return RCC_HSI_FREQ;
		}
	}
}

rcc_bus_prescaler_t RCC_GetBusPrescaler(const rcc_bus_t bus)
{
	rcc_ll_ahb_prescaler_t ahbPrescaler = RCC_LL_AHB_DIV_1;
	rcc_ll_apb_prescaler_t apbPrescaler = RCC_LL_APB_DIV_1;

	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			if (RCC_LL_GetAHBPrescaler(&ahbPrescaler) != DRIVER_STATUS_SUCCESS)
			{
				return (rcc_bus_prescaler_t) _RCC_GetAHBDividerValue(RCC_AHB_DIV_1);
			}
			return (rcc_bus_prescaler_t) _RCC_GetAHBDividerValue(_RCC_DecodeAHBPrescaler(ahbPrescaler));
		}
		case RCC_APB1_BUS:
		{
			if (RCC_LL_GetAPB1Prescaler(&apbPrescaler) != DRIVER_STATUS_SUCCESS)
			{
				return (rcc_bus_prescaler_t) _RCC_GetAPBDividerValue(RCC_APB1_DIV_1);
			}
			return (rcc_bus_prescaler_t) _RCC_GetAPBDividerValue(_RCC_DecodeAPBPrescaler(apbPrescaler));
		}
		case RCC_APB2_BUS:
		{
			if (RCC_LL_GetAPB2Prescaler(&apbPrescaler) != DRIVER_STATUS_SUCCESS)
			{
				return (rcc_bus_prescaler_t) _RCC_GetAPBDividerValue(RCC_APB2_DIV_1);
			}
			return (rcc_bus_prescaler_t) _RCC_GetAPBDividerValue(_RCC_DecodeAPBPrescaler(apbPrescaler));
		}
		default:
		{
			return (rcc_bus_prescaler_t) _RCC_GetAPBDividerValue(RCC_APB1_DIV_1);
		}
	}
}

rcc_freq_t RCC_GetBusFreq(const rcc_bus_t bus)
{
	const rcc_freq_t sysClk = RCC_GetCoreClockFreq();
	const rcc_freq_t hClk = (sysClk / (rcc_freq_t) RCC_GetBusPrescaler(RCC_AHB_BUS));

	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			return hClk;
		}
		case RCC_APB1_BUS:
		{
			return (hClk / (rcc_freq_t) RCC_GetBusPrescaler(RCC_APB1_BUS));
		}
		case RCC_APB2_BUS:
		{
			return (hClk / (rcc_freq_t) RCC_GetBusPrescaler(RCC_APB2_BUS));
		}
		default:
		{
			return hClk;
		}
	}
}

rcc_freq_t RCC_GetADCFreq(void)
{
	rcc_ll_adc_prescaler_t adcPrescaler = RCC_LL_ADC_DIV_2;

	if (RCC_LL_GetADCPrescaler(&adcPrescaler) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_FREQ_ZERO;
	}

	return (RCC_GetBusFreq(RCC_APB2_BUS) / _RCC_GetADCDividerValue(_RCC_DecodeADCPrescaler(adcPrescaler)));
}

rcc_freq_t RCC_GetUSBFreq(void)
{
	rcc_ll_usb_prescaler_t usbPrescaler = RCC_LL_USB_DIV_1_5;
	const rcc_freq_t pllClock = (RCC_GetSysClkSrc() == RCC_SYS_CLK_PLL) ? RCC_GetCoreClockFreq() : RCC_FREQ_ZERO;

	if (pllClock == RCC_FREQ_ZERO)
	{
		return RCC_FREQ_ZERO;
	}

	if (RCC_LL_GetUSBPrescaler(&usbPrescaler) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_FREQ_ZERO;
	}

	if (_RCC_DecodeUSBPrescaler(usbPrescaler) == RCC_USB_DIV_1)
	{
		return pllClock;
	}
	else
	{
		return ((pllClock << 1) / 3U);
	}
}
