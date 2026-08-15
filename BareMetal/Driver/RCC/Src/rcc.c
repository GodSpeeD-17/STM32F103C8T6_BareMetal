/**
 * @file	rcc.c
 * @author	Shrey Shah
 * @brief	RCC Driver Source File
 * @version	v2.3
 * @date	22-03-2026
 *
 * @details
 * This source file implements the RCC driver orchestration layer.
 * It sits above the LL layer and converts validated driver-level selections into
 * safe RCC hardware sequences while maintaining derived frequency snapshots.
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
/** @brief Function to be executed inside validating system clock switch @typedef _rcc_ready_status_getter_t */
typedef driver_status_t (*_rcc_ready_status_getter_t)(void);

// ==================================================================================================== //
//											Look Up Tables (LUTs)										//
// ==================================================================================================== //
/**  Internal field-to-value lookup descriptor  _rcc_field_value_map_t */
typedef struct _rcc_field_value_map_t
{
	uint32_t	ll_field;
	uint32_t	value;
} _rcc_field_value_map_t;

static const _rcc_field_value_map_t _RCC_AHBPrescalerLUT[] =
{
	{ RCC_CFGR_HPRE_DIV1,	1UL   },
	{ RCC_CFGR_HPRE_DIV2,	2UL   },
	{ RCC_CFGR_HPRE_DIV4,	4UL   },
	{ RCC_CFGR_HPRE_DIV8,	8UL   },
	{ RCC_CFGR_HPRE_DIV16,	16UL  },
	{ RCC_CFGR_HPRE_DIV64,	64UL  },
	{ RCC_CFGR_HPRE_DIV128,	128UL },
	{ RCC_CFGR_HPRE_DIV256,	256UL },
	{ RCC_CFGR_HPRE_DIV512,	512UL }
};

static const _rcc_field_value_map_t _RCC_APBPrescalerLUT[] =
{
	{ RCC_CFGR_PPRE1_DIV1,	1UL  },
	{ RCC_CFGR_PPRE1_DIV2,	2UL  },
	{ RCC_CFGR_PPRE1_DIV4,	4UL  },
	{ RCC_CFGR_PPRE1_DIV8,	8UL  },
	{ RCC_CFGR_PPRE1_DIV16,	16UL }
};

static const _rcc_field_value_map_t _RCC_APB2PrescalerLUT[] =
{
	{ RCC_CFGR_PPRE2_DIV1,	1UL  },
	{ RCC_CFGR_PPRE2_DIV2,	2UL  },
	{ RCC_CFGR_PPRE2_DIV4,	4UL  },
	{ RCC_CFGR_PPRE2_DIV8,	8UL  },
	{ RCC_CFGR_PPRE2_DIV16,	16UL }
};

static const _rcc_field_value_map_t _RCC_ADCPrescalerLUT[] =
{
	{ RCC_CFGR_ADCPRE_DIV2,	2UL },
	{ RCC_CFGR_ADCPRE_DIV4,	4UL },
	{ RCC_CFGR_ADCPRE_DIV6,	6UL },
	{ RCC_CFGR_ADCPRE_DIV8,	8UL }
};

static const _rcc_field_value_map_t _RCC_USBPrescalerLUT[] =
{
	{ RCC_CFGR_USBPRE_DIV1_5,	RCC_USB_DIV_1_5 },
	{ RCC_CFGR_USBPRE_DIRECT,	RCC_USB_DIV_1   }
};

static const _rcc_field_value_map_t _RCC_PLLMultiplierLUT[] =
{
	{ RCC_CFGR_PLLMUL_2,	RCC_PLL_MUL_2  },
	{ RCC_CFGR_PLLMUL_3,	RCC_PLL_MUL_3  },
	{ RCC_CFGR_PLLMUL_4,	RCC_PLL_MUL_4  },
	{ RCC_CFGR_PLLMUL_5,	RCC_PLL_MUL_5  },
	{ RCC_CFGR_PLLMUL_6,	RCC_PLL_MUL_6  },
	{ RCC_CFGR_PLLMUL_7,	RCC_PLL_MUL_7  },
	{ RCC_CFGR_PLLMUL_8,	RCC_PLL_MUL_8  },
	{ RCC_CFGR_PLLMUL_9,	RCC_PLL_MUL_9  },
	{ RCC_CFGR_PLLMUL_10,	RCC_PLL_MUL_10 },
	{ RCC_CFGR_PLLMUL_11,	RCC_PLL_MUL_11 },
	{ RCC_CFGR_PLLMUL_12,	RCC_PLL_MUL_12 },
	{ RCC_CFGR_PLLMUL_13,	RCC_PLL_MUL_13 },
	{ RCC_CFGR_PLLMUL_14,	RCC_PLL_MUL_14 },
	{ RCC_CFGR_PLLMUL_15,	RCC_PLL_MUL_15 },
	{ RCC_CFGR_PLLMUL_16,	RCC_PLL_MUL_16 }
};

/** @brief Cached RCC clock frequencies snapshot maintained by the driver. */
static volatile rcc_clock_frequencies_t _rccClockFrequenciesSnapshot =
{
	RCC_FREQ_ZERO,
	RCC_FREQ_ZERO,
	RCC_FREQ_ZERO,
	RCC_FREQ_ZERO,
	RCC_FREQ_ZERO,
	RCC_FREQ_ZERO
};

// ==================================================================================================== //
//                                            Local Helpers                                             //
// ==================================================================================================== //

/**
 * @brief Waits until the supplied source status getter reports the requested state.
 * @param pReadyGetter Status getter used to poll the hardware source state.
 * @param targetStatus Target driver status expected from the ready getter.
 * @returns - @ref driver_status_t Status of the wait operation.
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The source reached the requested status before timeout.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: The ready getter callback is NULL.
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: The requested status was not reached within the timeout window.
 */
static driver_status_t _RCC_WaitForClockSourceReady(_rcc_ready_status_getter_t const pReadyGetter, const driver_status_t targetStatus)
{
	volatile uint32_t timeout = RCC_READY_TIMEOUT;

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

/**
 * @brief Waits until the selected system clock source becomes active in hardware.
 * @param source Requested system clock source.
 * @returns - @ref driver_status_t Status of the wait operation.
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested source became the active system clock.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Reading the system clock status failed.
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: The requested source did not become active before timeout.
 */
static driver_status_t _RCC_WaitForSystemClockSwitch(const rcc_system_clock_t source)
{
	uint32_t			status = RCC_CFGR_SWS_HSI;
	volatile uint32_t	timeout = RCC_READY_TIMEOUT;

	while (timeout > 0x00UL)
	{
		if (RCC_LL_GetSystemClockStatus(&status) != DRIVER_STATUS_SUCCESS)
		{
			return DRIVER_STATUS_ERROR;
		}

		if (((source == RCC_SYS_CLK_HSI) && (status == RCC_CFGR_SWS_HSI)) ||
			((source == RCC_SYS_CLK_HSE) && (status == RCC_CFGR_SWS_HSE)) ||
			((source == RCC_SYS_CLK_PLL) && (status == RCC_CFGR_SWS_PLL)))
		{
			return DRIVER_STATUS_SUCCESS;
		}

		timeout--;
	}

	return DRIVER_STATUS_ERROR_TIMEOUT;
}

/**
 * @brief Finds the LUT index whose LL field matches the requested field value.
 * @param[in] pLUT Pointer to the LUT to scan.
 * @param[in] itemCount Number of valid items in the LUT.
 * @param[in] fieldValue LL field value to search for.
 * @returns Matching LUT index when found, otherwise @ref RCC_DRIVER_INVALID_INDEX.
 */
__STATIC_FORCEINLINE uint32_t _RCC_FindFieldValueMapIndex(const _rcc_field_value_map_t* const pLUT, const uint32_t itemCount, const uint32_t fieldValue)
{
	uint32_t index = RCC_DRIVER_INVALID_INDEX;

	for (index = 0x00UL; index < itemCount; index++)
	{
		if (pLUT[index].ll_field == fieldValue)
		{
			return index;
		}
	}

	return RCC_DRIVER_INVALID_INDEX;
}

/**
 * @brief Returns the logical value stored at the requested LUT index.
 * @param[in] pLUT Pointer to the LUT to read.
 * @param[in] itemCount Number of valid items in the LUT.
 * @param[in] index Requested LUT index.
 * @param[in] defaultValue Fallback value used when the index is outside the LUT range.
 * @returns Logical value stored in the LUT, or @p defaultValue when the index is invalid.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetFieldValueMapValueByIndex(const _rcc_field_value_map_t* const pLUT, const uint32_t itemCount, const uint32_t index, const uint32_t defaultValue)
{
	if (index >= itemCount)
	{
		return defaultValue;
	}

	return pLUT[index].value;
}

/**
 * @brief Returns the LL field stored at the requested LUT index.
 * @param[in] pLUT Pointer to the LUT to read.
 * @param[in] itemCount Number of valid items in the LUT.
 * @param[in] index Requested LUT index.
 * @param[in] defaultField Fallback LL field used when the index is outside the LUT range.
 * @returns LL field stored in the LUT, or @p defaultField when the index is invalid.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetFieldValueMapLLFieldByIndex(const _rcc_field_value_map_t* const pLUT, const uint32_t itemCount, const uint32_t index, const uint32_t defaultField)
{
	if (index >= itemCount)
	{
		return defaultField;
	}

	return pLUT[index].ll_field;
}

/**
 * @brief Returns the effective AHB divider for the supplied driver selector.
 * @param[in] prescalerSelector The AHB prescaler selector.
 * @returns The effective divider value.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetAHBPrescalerDividerBySelector(const rcc_bus_prescaler_t prescalerSelector)
{
	return (uint32_t) _RCC_GetFieldValueMapValueByIndex
	(
		_RCC_AHBPrescalerLUT,
		ARRAY_SIZE(_RCC_AHBPrescalerLUT),
		(uint32_t) prescalerSelector,
		1UL
	);
}

/**
 * @brief Returns the effective APB divider for the supplied driver selector.
 * @param[in] prescalerSelector The APB prescaler selector.
 * @returns The effective divider value.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetAPBBusPrescalerDividerBySelector(const rcc_bus_prescaler_t prescalerSelector)
{
	return (uint32_t) _RCC_GetFieldValueMapValueByIndex
	(
		_RCC_APBPrescalerLUT,
		ARRAY_SIZE(_RCC_APBPrescalerLUT),
		(uint32_t) prescalerSelector,
		1UL
	);
}

/**
 * @brief Returns the effective ADC divider for the supplied driver selector.
 * @param[in] prescalerSelector The ADC prescaler selector.
 * @returns The effective divider value.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetADCPrescalerDividerBySelector(const rcc_component_prescaler_t prescalerSelector)
{
	return (uint32_t) _RCC_GetFieldValueMapValueByIndex
	(
		_RCC_ADCPrescalerLUT,
		ARRAY_SIZE(_RCC_ADCPrescalerLUT),
		(uint32_t) prescalerSelector,
		2UL
	);
}

/**
 * @brief Resolves the public system clock selection to the LL field encoding.
 * @param[in] source The system clock source selection.
 * @returns The corresponding LL field value.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetSystemClockSourceLLField(const rcc_system_clock_t source)
{
	switch (source)
	{
		case RCC_SYS_CLK_HSI:
		{
			return RCC_CFGR_SW_HSI;
		}
		case RCC_SYS_CLK_HSE:
		{
			return RCC_CFGR_SW_HSE;
		}
		case RCC_SYS_CLK_PLL:
		{
			return RCC_CFGR_SW_PLL;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

/**
 * @brief Resolves the public PLL source selection to the LL field encoding.
 * @param[in] source The PLL source selection.
 * @returns The corresponding LL field value.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetPLLSourceLLField(const rcc_pll_src_t source)
{
	switch (source)
	{
		case RCC_PLL_SRC_HSI:
		{
			return RCC_CFGR_PLLSRC_HSI_DIV2;
		}
		case RCC_PLL_SRC_HSE:
		{
			return RCC_CFGR_PLLSRC_HSE;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

/**
 * @brief Resolves the public HSE PLL divider selection to the LL field encoding.
 * @param[in] divider The HSE PLL divider selection.
 * @returns The corresponding LL field value.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetPLLHSEDividerLLField(const rcc_pll_src_psc_t divider)
{
	switch (divider)
	{
		case RCC_PLL_SRC_HSE_DIV_1:
		{
			return RCC_CFGR_PLLXTPRE_HSE;
		}
		case RCC_PLL_SRC_HSE_DIV_2:
		{
			return RCC_CFGR_PLLXTPRE_HSE_DIV2;
		}
		default:
		{
			return RCC_DRIVER_INVALID_FIELD;
		}
	}
}

/**
 * @brief Resolves the public PLL multiplier selection to the LL field encoding.
 * @param[in] multiplier The PLL multiplier selection.
 * @returns The corresponding LL field value.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetPLLMultiplierLLField(const rcc_pll_mul_t multiplier)
{
	if ((multiplier < RCC_PLL_MUL_2) || (multiplier > RCC_PLL_MUL_16))
	{
		return RCC_DRIVER_INVALID_FIELD;
	}

	return _RCC_GetFieldValueMapLLFieldByIndex
	(
		_RCC_PLLMultiplierLUT,
		ARRAY_SIZE(_RCC_PLLMultiplierLUT),
		(uint32_t) (multiplier - RCC_PLL_MUL_2),
		RCC_DRIVER_INVALID_FIELD
	);
}

/**
 * @brief Resolves the public AHB prescaler selector to the LL field encoding.
 * @param[in] prescalerSelector The AHB prescaler selector.
 * @returns The corresponding LL field value.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetAHBPrescalerLLField(const rcc_bus_prescaler_t prescalerSelector)
{
	return _RCC_GetFieldValueMapLLFieldByIndex
	(
		_RCC_AHBPrescalerLUT,
		ARRAY_SIZE(_RCC_AHBPrescalerLUT),
		(uint32_t) prescalerSelector,
		RCC_DRIVER_INVALID_FIELD
	);
}

/**
 * @brief Resolves the public APB prescaler selector to the LL field encoding.
 * @param[in] prescalerSelector The APB prescaler selector.
 * @returns The corresponding LL field value.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetAPB1PrescalerLLField(const rcc_bus_prescaler_t prescalerSelector)
{
	return _RCC_GetFieldValueMapLLFieldByIndex
	(
		_RCC_APBPrescalerLUT,
		ARRAY_SIZE(_RCC_APBPrescalerLUT),
		(uint32_t) prescalerSelector,
		RCC_DRIVER_INVALID_FIELD
	);
}

/**
 * @brief Resolves the public APB2 prescaler selector to the LL field encoding.
 * @param[in] prescalerSelector The APB2 prescaler selector.
 * @returns The corresponding LL field value.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetAPB2PrescalerLLField(const rcc_bus_prescaler_t prescalerSelector)
{
	return _RCC_GetFieldValueMapLLFieldByIndex
	(
		_RCC_APB2PrescalerLUT,
		ARRAY_SIZE(_RCC_APB2PrescalerLUT),
		(uint32_t) prescalerSelector,
		RCC_DRIVER_INVALID_FIELD
	);
}

/**
 * @brief Resolves the public ADC prescaler selector to the LL field encoding.
 * @param[in] prescalerSelector The ADC prescaler selector.
 * @returns The corresponding LL field value.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetADCPrescalerLLField(const rcc_component_prescaler_t prescalerSelector)
{
	return _RCC_GetFieldValueMapLLFieldByIndex
	(
		_RCC_ADCPrescalerLUT,
		ARRAY_SIZE(_RCC_ADCPrescalerLUT),
		(uint32_t) prescalerSelector,
		RCC_DRIVER_INVALID_FIELD
	);
}

/**
 * @brief Resolves the public USB prescaler selector to the LL field encoding.
 * @param[in] prescalerSelector The USB prescaler selector.
 * @returns The corresponding LL field value.
 */
__STATIC_FORCEINLINE uint32_t _RCC_GetUSBPrescalerLLField(const rcc_component_prescaler_t prescalerSelector)
{
	return _RCC_GetFieldValueMapLLFieldByIndex
	(
		_RCC_USBPrescalerLUT,
		ARRAY_SIZE(_RCC_USBPrescalerLUT),
		(uint32_t) prescalerSelector,
		RCC_DRIVER_INVALID_FIELD
	);
}

/**
 * @brief Decodes the LL system clock status field to the public driver value.
 * @param[in] status The LL system clock status field.
 * @returns The corresponding public driver value.
 */
__STATIC_FORCEINLINE rcc_system_clock_t _RCC_GetSystemClockSourceFromLLStatus(const uint32_t status)
{
	switch (status)
	{
		case RCC_CFGR_SWS_HSI:
		{
			return RCC_SYS_CLK_HSI;
		}
		case RCC_CFGR_SWS_HSE:
		{
			return RCC_SYS_CLK_HSE;
		}
		case RCC_CFGR_SWS_PLL:
		{
			return RCC_SYS_CLK_PLL;
		}
		default:
		{
			return RCC_SYS_CLK_HSI;
		}
	}
}

/**
 * @brief Decodes the LL AHB prescaler field to the public selector value.
 * @param[in] prescalerField The LL AHB prescaler field.
 * @returns The corresponding public selector value.
 */
__STATIC_FORCEINLINE rcc_bus_prescaler_t _RCC_GetAHBPrescalerSelectorFromLLField(const uint32_t prescalerField)
{
	const uint32_t index = _RCC_FindFieldValueMapIndex
	(
		_RCC_AHBPrescalerLUT,
		ARRAY_SIZE(_RCC_AHBPrescalerLUT),
		(uint32_t) prescalerField
	);

	if (index == RCC_DRIVER_INVALID_INDEX)
	{
		return RCC_AHB_DIV_1;
	}

	return (rcc_bus_prescaler_t) index;
}

/**
 * @brief Decodes the LL APB prescaler field to the public selector value.
 * @param[in] prescalerField The LL APB prescaler field.
 * @returns The corresponding public selector value.
 */
__STATIC_FORCEINLINE rcc_bus_prescaler_t _RCC_GetAPB1PrescalerSelectorFromLLField(const uint32_t prescalerField)
{
	const uint32_t index = _RCC_FindFieldValueMapIndex
	(
		_RCC_APBPrescalerLUT,
		ARRAY_SIZE(_RCC_APBPrescalerLUT),
		(uint32_t) prescalerField
	);

	if (index == RCC_DRIVER_INVALID_INDEX)
	{
		return RCC_APB1_DIV_1;
	}

	return (rcc_bus_prescaler_t) index;
}

/**
 * @brief Decodes the LL APB2 prescaler field to the public selector value.
 * @param[in] prescalerField The LL APB2 prescaler field.
 * @returns The corresponding public selector value.
 */
__STATIC_FORCEINLINE rcc_bus_prescaler_t _RCC_GetAPB2PrescalerSelectorFromLLField(const uint32_t prescalerField)
{
	const uint32_t index = _RCC_FindFieldValueMapIndex
	(
		_RCC_APB2PrescalerLUT,
		ARRAY_SIZE(_RCC_APB2PrescalerLUT),
		(uint32_t) prescalerField
	);

	if (index == RCC_DRIVER_INVALID_INDEX)
	{
		return RCC_APB2_DIV_1;
	}

	return (rcc_bus_prescaler_t) index;
}

/**
 * @brief Decodes the LL ADC prescaler field to the public selector value.
 * @param[in] prescalerField The LL ADC prescaler field.
 * @returns The corresponding public selector value.
 */
__STATIC_FORCEINLINE rcc_component_prescaler_t _RCC_GetADCPrescalerSelectorFromLLField(const uint32_t prescalerField)
{
	const uint32_t index = _RCC_FindFieldValueMapIndex
	(
		_RCC_ADCPrescalerLUT,
		ARRAY_SIZE(_RCC_ADCPrescalerLUT),
		(uint32_t) prescalerField
	);

	if (index == RCC_DRIVER_INVALID_INDEX)
	{
		return RCC_ADC_DIV_2;
	}

	return (rcc_component_prescaler_t) index;
}

/**
 * @brief Decodes the LL USB prescaler field to the public selector value.
 * @param[in] prescalerField The LL USB prescaler field.
 * @returns The corresponding public selector value.
 */
__STATIC_FORCEINLINE rcc_component_prescaler_t _RCC_GetUSBPrescalerSelectorFromLLField(const uint32_t prescalerField)
{
	const uint32_t index = _RCC_FindFieldValueMapIndex
	(
		_RCC_USBPrescalerLUT,
		ARRAY_SIZE(_RCC_USBPrescalerLUT),
		(uint32_t) prescalerField
	);

	if (index == RCC_DRIVER_INVALID_INDEX)
	{
		return RCC_USB_DIV_1_5;
	}

	return (rcc_component_prescaler_t) index;
}

/**
 * @brief Returns the effective divider currently programmed for the requested bus.
 * @param[in] bus Target bus selector.
 * @returns Effective divider value for the requested bus.
 */
static uint32_t _RCC_GetBusPrescalerDivider(const rcc_bus_t bus)
{
	uint32_t ahbPrescalerField = RCC_CFGR_HPRE_DIV1;
	uint32_t apb1PrescalerField = RCC_CFGR_PPRE1_DIV1;
	uint32_t apb2PrescalerField = RCC_CFGR_PPRE2_DIV1;

	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			if (RCC_LL_GetAHBPrescaler(&ahbPrescalerField) != DRIVER_STATUS_SUCCESS)
			{
				return 1UL;
			}

			return _RCC_GetAHBPrescalerDividerBySelector(_RCC_GetAHBPrescalerSelectorFromLLField(ahbPrescalerField));
		}
		case RCC_APB1_BUS:
		{
			if (RCC_LL_GetAPB1Prescaler(&apb1PrescalerField) != DRIVER_STATUS_SUCCESS)
			{
				return 1UL;
			}

			return _RCC_GetAPBBusPrescalerDividerBySelector(_RCC_GetAPB1PrescalerSelectorFromLLField(apb1PrescalerField));
		}
		case RCC_APB2_BUS:
		{
			if (RCC_LL_GetAPB2Prescaler(&apb2PrescalerField) != DRIVER_STATUS_SUCCESS)
			{
				return 1UL;
			}

			return _RCC_GetAPBBusPrescalerDividerBySelector(_RCC_GetAPB2PrescalerSelectorFromLLField(apb2PrescalerField));
		}
		default:
		{
			return 1UL;
		}
	}
}

/**
 * @brief Returns the PLL input frequency for the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The PLL input frequency.
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetPLLInputClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	if (pClockTreeConfig->system.pll.source == RCC_PLL_SRC_HSI)
	{
		return (RCC_HSI_FREQ >> 1);
	}

	if (pClockTreeConfig->system.pll.source_prescaler == RCC_PLL_SRC_HSE_DIV_2)
	{
		return (RCC_HSE_FREQ >> 1);
	}

	return RCC_HSE_FREQ;
}

/**
 * @brief Returns the target SYSCLK frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target SYSCLK frequency.
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetSystemClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
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
			return (_RCC_GetPLLInputClockFrequency(pClockTreeConfig) * (frequency_t) pClockTreeConfig->system.pll.multiplication_factor);
		}
		default:
		{
			return RCC_FREQ_ZERO;
		}
	}
}

/**
 * @brief Returns the target HCLK frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target HCLK frequency.
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetAHBClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	return (_RCC_GetSystemClockFrequency(pClockTreeConfig) / _RCC_GetAHBPrescalerDividerBySelector(pClockTreeConfig->bus.AHB));
}

/**
 * @brief Returns the target APB1 frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target APB1 frequency.
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetAPB1ClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	return (_RCC_GetAHBClockFrequency(pClockTreeConfig) / _RCC_GetAPBBusPrescalerDividerBySelector(pClockTreeConfig->bus.APB1));
}

/**
 * @brief Returns the target APB2 frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target APB2 frequency.
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetAPB2ClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	return (_RCC_GetAHBClockFrequency(pClockTreeConfig) / _RCC_GetAPBBusPrescalerDividerBySelector(pClockTreeConfig->bus.APB2));
}

/**
 * @brief Returns the target ADC frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target ADC frequency.
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetADCClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	return (_RCC_GetAPB2ClockFrequency(pClockTreeConfig) / _RCC_GetADCPrescalerDividerBySelector(pClockTreeConfig->component.ADC));
}

/**
 * @brief Returns the target USB frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target USB frequency.
 */
static frequency_t _RCC_GetUSBClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	const frequency_t pllClock = _RCC_GetPLLInputClockFrequency(pClockTreeConfig) * (frequency_t) pClockTreeConfig->system.pll.multiplication_factor;

	if (pClockTreeConfig->system.clk_src != RCC_SYS_CLK_PLL)
	{
		return RCC_FREQ_ZERO;
	}

	if (pClockTreeConfig->component.USB == RCC_USB_DIV_1)
	{
		return pllClock;
	}

	return ((pllClock << 1) / 3U);
}

/**
 * @brief Computes the derived frequencies for the supplied clock tree configuration.
 * @param pClockTreeConfig Pointer to the clock tree configuration.
 * @param pClockFrequencies Pointer to the destination clock-frequency snapshot.
 * @returns - @ref driver_status_t Status of the snapshot load.
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The snapshot was loaded successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: Either input pointer is `NULL`.
 */
static driver_status_t _RCC_LoadClockFrequenciesFromConfig(const rcc_clock_tree_config_t* const pClockTreeConfig, rcc_clock_frequencies_t* const pClockFrequencies)
{
	if ((pClockTreeConfig == NULL) || (pClockFrequencies == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	pClockFrequencies->sysclk = _RCC_GetSystemClockFrequency(pClockTreeConfig);
	pClockFrequencies->hclk = _RCC_GetAHBClockFrequency(pClockTreeConfig);
	pClockFrequencies->pclk1 = _RCC_GetAPB1ClockFrequency(pClockTreeConfig);
	pClockFrequencies->pclk2 = _RCC_GetAPB2ClockFrequency(pClockTreeConfig);
	pClockFrequencies->adcclk = _RCC_GetADCClockFrequency(pClockTreeConfig);
	pClockFrequencies->usbclk = _RCC_GetUSBClockFrequency(pClockTreeConfig);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates PLL-specific selections inside the supplied clock tree configuration.
 * @param pClockTreeConfig Pointer to the clock tree configuration to validate.
 * @returns - @ref driver_status_t Status of PLL configuration validation.
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The PLL configuration is valid.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more PLL selections are invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @c pClockTreeConfig is `NULL`.
 */
static driver_status_t _RCC_ValidatePLLConfig(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	if (pClockTreeConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	if (_RCC_GetPLLSourceLLField(pClockTreeConfig->system.pll.source) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_GetPLLMultiplierLLField(pClockTreeConfig->system.pll.multiplication_factor) == RCC_DRIVER_INVALID_FIELD)
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
		if (_RCC_GetPLLHSEDividerLLField(pClockTreeConfig->system.pll.source_prescaler) == RCC_DRIVER_INVALID_FIELD)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates the basic field selections provided to the RCC driver.
 * @param pRCCConfig Pointer to the top-level RCC configuration.
 * @returns - @ref driver_status_t Status of field validation.
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: All requested field selections are valid.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: The configuration pointer is NULL.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more requested field selections are invalid.
 */
static driver_status_t _RCC_ValidateClockTreeConfig(const rcc_config_t* const pRCCConfig)
{
	const rcc_clock_tree_config_t* pClockTreeConfig = NULL;

	if (pRCCConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	pClockTreeConfig = &(pRCCConfig->clock_tree);

	if (_RCC_GetSystemClockSourceLLField(pClockTreeConfig->system.clk_src) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_GetAHBPrescalerLLField(pClockTreeConfig->bus.AHB) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_GetAPB1PrescalerLLField(pClockTreeConfig->bus.APB1) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_GetAPB2PrescalerLLField(pClockTreeConfig->bus.APB2) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_GetADCPrescalerLLField(pClockTreeConfig->component.ADC) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_GetUSBPrescalerLLField(pClockTreeConfig->component.USB) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	rcc_flash_latency_t flashLatency = pRCCConfig->flash.latency;
	if ((flashLatency != RCC_FLASH_LATENCY_0) && (flashLatency != RCC_FLASH_LATENCY_1) && (flashLatency != RCC_FLASH_LATENCY_2))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((pRCCConfig->flash.prefetch != RCC_FLASH_PREFETCH_ENABLE) && (pRCCConfig->flash.prefetch != RCC_FLASH_PREFETCH_DISABLE))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL)
	{
		ASSERT_DRIVER_STATUS(_RCC_ValidatePLLConfig(pClockTreeConfig));
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Stores the supplied clock frequencies into the RCC driver cache.
 * @param[in] pClockFrequencies Pointer to the clock frequencies snapshot.
 */
__STATIC_FORCEINLINE void _RCC_UpdateClockFrequenciesCache(const rcc_clock_frequencies_t* const pClockFrequencies)
{
	if (pClockFrequencies == NULL)
	{
		return;
	}

	_rccClockFrequenciesSnapshot = *pClockFrequencies;
}

/**
 * @brief Builds the current clock frequency snapshot directly from RCC hardware state.
 * @param pClockFrequencies Pointer to @ref rcc_clock_frequencies_t.
 * @returns - @ref driver_status_t Status of the snapshot build.
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The snapshot was built successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockFrequencies was a null pointer.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read while building the snapshot.
 */
static driver_status_t _RCC_LoadClockFrequenciesFromHardware(rcc_clock_frequencies_t* const pClockFrequencies);

/**
 * @brief Refreshes the RCC driver clock-frequency snapshot cache from current hardware state.
 * @returns - @ref driver_status_t Status of the cache refresh operation.
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The cache snapshot was refreshed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read while rebuilding the snapshot.
 */
static driver_status_t _RCC_RefreshClockFrequenciesCache(void)
{
	rcc_clock_frequencies_t clockFrequencies =
	{
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO
	};

	ASSERT_DRIVER_STATUS(_RCC_LoadClockFrequenciesFromHardware(&clockFrequencies));
	_RCC_UpdateClockFrequenciesCache(&clockFrequencies);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Applies bus prescaler configuration without refreshing the public cache.
 * @param[in] pBusConfig Pointer to bus prescaler configuration.
 * @returns - @ref driver_status_t Status of bus prescaler programming.
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Bus prescaler fields were programmed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: `pBusConfig` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more bus prescaler selectors were invalid.
 */
static driver_status_t _RCC_ApplyBusPrescalerConfig(const rcc_bus_config_t* const pBusConfig)
{
	uint32_t ahbPrescalerField = 0x00UL;
	uint32_t apb1PrescalerField = 0x00UL;
	uint32_t apb2PrescalerField = 0x00UL;

	if (pBusConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ahbPrescalerField = _RCC_GetAHBPrescalerLLField(pBusConfig->AHB);
	apb1PrescalerField = _RCC_GetAPB1PrescalerLLField(pBusConfig->APB1);
	apb2PrescalerField = _RCC_GetAPB2PrescalerLLField(pBusConfig->APB2);

	if
	(
		(ahbPrescalerField == RCC_DRIVER_INVALID_FIELD)		||
		(apb1PrescalerField == RCC_DRIVER_INVALID_FIELD)	||
		(apb2PrescalerField == RCC_DRIVER_INVALID_FIELD)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(RCC_LL_SetAHBPrescaler(ahbPrescalerField));
	ASSERT_DRIVER_STATUS(RCC_LL_SetAPB1Prescaler(apb1PrescalerField));
	ASSERT_DRIVER_STATUS(RCC_LL_SetAPB2Prescaler(apb2PrescalerField));
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Applies component prescaler configuration without refreshing the public cache.
 * @param[in] pComponentConfig Pointer to component prescaler configuration.
 * @returns - @ref driver_status_t Status of component prescaler programming.
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Component prescaler fields were programmed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: `pComponentConfig` was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more component prescaler selectors were invalid.
 */
static driver_status_t _RCC_ApplyComponentPrescalerConfig(const rcc_component_config_t* const pComponentConfig)
{
	uint32_t adcPrescalerField = 0x00UL;
	uint32_t usbPrescalerField = 0x00UL;

	if (pComponentConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	adcPrescalerField = _RCC_GetADCPrescalerLLField(pComponentConfig->ADC);
	usbPrescalerField = _RCC_GetUSBPrescalerLLField(pComponentConfig->USB);

	if ((adcPrescalerField == RCC_DRIVER_INVALID_FIELD) || (usbPrescalerField == RCC_DRIVER_INVALID_FIELD))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(RCC_LL_SetADCPrescaler(adcPrescalerField));
	ASSERT_DRIVER_STATUS(RCC_LL_SetUSBPrescaler(usbPrescalerField));
	return DRIVER_STATUS_SUCCESS;
}

static driver_status_t _RCC_LoadClockFrequenciesFromHardware(rcc_clock_frequencies_t* const pClockFrequencies)
{
	rcc_system_clock_t systemClockSource = RCC_SYS_CLK_HSI;
	uint32_t adcPrescaler = RCC_CFGR_ADCPRE_DIV2;
	uint32_t usbPrescaler = RCC_CFGR_USBPRE_DIV1_5;
	frequency_t pllInputFrequency = RCC_FREQ_ZERO;

	if (pClockFrequencies == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	systemClockSource = RCC_GetSysClkSrc();

	switch (systemClockSource)
	{
		case RCC_SYS_CLK_HSI:
		{
			pClockFrequencies->sysclk = RCC_HSI_FREQ;
			break;
		}
		case RCC_SYS_CLK_HSE:
		{
			pClockFrequencies->sysclk = RCC_HSE_FREQ;
			break;
		}
		case RCC_SYS_CLK_PLL:
		{
			pllInputFrequency = (RCC_GetPLLSource() == RCC_PLL_SRC_HSE) ? RCC_HSE_FREQ : (RCC_HSI_FREQ >> 1);
			if (RCC_GetPLLSourcePrescaler() == RCC_PLL_SRC_HSE_DIV_2)
			{
				pllInputFrequency >>= 1;
			}
			pClockFrequencies->sysclk = (pllInputFrequency * (frequency_t) RCC_GetPLLMultiplier());
			break;
		}
		default:
		{
			pClockFrequencies->sysclk = RCC_HSI_FREQ;
			break;
		}
	}

	pClockFrequencies->hclk = (pClockFrequencies->sysclk / _RCC_GetBusPrescalerDivider(RCC_AHB_BUS));
	pClockFrequencies->pclk1 = (pClockFrequencies->hclk / _RCC_GetBusPrescalerDivider(RCC_APB1_BUS));
	pClockFrequencies->pclk2 = (pClockFrequencies->hclk / _RCC_GetBusPrescalerDivider(RCC_APB2_BUS));

	if (RCC_LL_GetADCPrescaler(&adcPrescaler) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR;
	}

	pClockFrequencies->adcclk =
		(pClockFrequencies->pclk2 / _RCC_GetADCPrescalerDividerBySelector(_RCC_GetADCPrescalerSelectorFromLLField(adcPrescaler)));

	if (systemClockSource != RCC_SYS_CLK_PLL)
	{
		pClockFrequencies->usbclk = RCC_FREQ_ZERO;
		return DRIVER_STATUS_SUCCESS;
	}

	if (RCC_LL_GetUSBPrescaler(&usbPrescaler) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR;
	}

	if (_RCC_GetUSBPrescalerSelectorFromLLField(usbPrescaler) == RCC_USB_DIV_1)
	{
		pClockFrequencies->usbclk = pClockFrequencies->sysclk;
	}
	else
	{
		pClockFrequencies->usbclk = ((pClockFrequencies->sysclk << 1) / 3U);
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates the maximum allowed derived clock frequencies.
 * @param pClockFreqSnapshot Pointer to the derived clock frequency snapshot.
 * @returns - @ref driver_status_t Status of frequency-limit validation.
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: All derived frequencies are within device limits.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: The snapshot pointer is NULL.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more derived frequencies exceed the supported limits.
 */
static driver_status_t _RCC_ValidateClockFrequencies(const rcc_clock_frequencies_t* const pClockFreqSnapshot)
{
	if (pClockFreqSnapshot == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	if (pClockFreqSnapshot->sysclk > RCC_SYSCLK_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (pClockFreqSnapshot->hclk > RCC_HCLK_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (pClockFreqSnapshot->pclk1 > RCC_PCLK1_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (pClockFreqSnapshot->pclk2 > RCC_PCLK2_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (pClockFreqSnapshot->adcclk > RCC_ADCCLK_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates inter-parameter dependencies across the RCC configuration.
 * @param pRCCConfig Pointer to the top-level RCC configuration.
 * @param pClockFreqSnapshot Pointer to the derived clock frequency snapshot.
 * @returns - @ref driver_status_t Status of dependency validation.
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: All inter-parameter dependencies are satisfied.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: One or more input pointers are NULL.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more dependent configuration constraints are violated.
 */
static driver_status_t _RCC_ValidateClockConfigDependencies(const rcc_config_t* const pRCCConfig, const rcc_clock_frequencies_t* const pClockFreqSnapshot)
{
	const rcc_clock_tree_config_t* pClockTreeConfig = NULL;

	if ((pRCCConfig == NULL) || (pClockFreqSnapshot == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	pClockTreeConfig = &(pRCCConfig->clock_tree);

	if ((pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL) && (pClockFreqSnapshot->usbclk != RCC_FREQ_ZERO) && (pClockFreqSnapshot->usbclk != RCC_USBCLK_TARGET_FREQ))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((pClockFreqSnapshot->sysclk <= RCC_FLASH_LATENCY_0_MAX_FREQ) && (pRCCConfig->flash.latency != RCC_FLASH_LATENCY_0))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((pClockFreqSnapshot->sysclk > RCC_FLASH_LATENCY_0_MAX_FREQ) && (pClockFreqSnapshot->sysclk <= RCC_FLASH_LATENCY_1_MAX_FREQ) && (pRCCConfig->flash.latency != RCC_FLASH_LATENCY_1))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((pClockFreqSnapshot->sysclk > RCC_FLASH_LATENCY_1_MAX_FREQ) && (pRCCConfig->flash.latency != RCC_FLASH_LATENCY_2))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}
// ==================================================================================================== //
//                                   Driver Clock Gate and Reset APIs                                   //
// ==================================================================================================== //

driver_status_t RCC_ValidateConfig(const rcc_config_t* const pRCCConfig)
{
	const rcc_clock_tree_config_t* pClockTreeConfig = NULL;
	rcc_clock_frequencies_t clockFreqSnapshot =
	{
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO
	};

	if (pRCCConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	pClockTreeConfig = &(pRCCConfig->clock_tree);
	ASSERT_DRIVER_STATUS(_RCC_ValidateClockTreeConfig(pRCCConfig));
	ASSERT_DRIVER_STATUS(_RCC_LoadClockFrequenciesFromConfig(pClockTreeConfig, &clockFreqSnapshot));
	ASSERT_DRIVER_STATUS(_RCC_ValidateClockFrequencies(&clockFreqSnapshot));
	ASSERT_DRIVER_STATUS(_RCC_ValidateClockConfigDependencies(pRCCConfig, &clockFreqSnapshot));
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
	else if (pFlashConfig->prefetch == RCC_FLASH_PREFETCH_DISABLE)
	{
		REGOPS_CLEAR(&FLASH->ACR.REG, FLASH_ACR_PRFTBE);
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigBusPrescalers(const rcc_bus_config_t* const pBusConfig)
{
	ASSERT_DRIVER_STATUS(_RCC_ApplyBusPrescalerConfig(pBusConfig));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesCache());
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigComponentPrescalers(const rcc_component_config_t* const pComponentConfig)
{
	ASSERT_DRIVER_STATUS(_RCC_ApplyComponentPrescalerConfig(pComponentConfig));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesCache());
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SwitchClockSourceToHSI(void)
{
	RCC_LL_EnableHSI();
	ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReady(RCC_LL_GetHSIReadyStatus, DRIVER_STATUS_READY));
	ASSERT_DRIVER_STATUS(RCC_LL_SetSystemClockSource(RCC_CFGR_SW_HSI));
	ASSERT_DRIVER_STATUS(_RCC_WaitForSystemClockSwitch(RCC_SYS_CLK_HSI));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesCache());
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SwitchClockSourceToHSE(void)
{
	RCC_LL_EnableHSE();
	ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReady(RCC_LL_GetHSEReadyStatus, DRIVER_STATUS_READY));
	ASSERT_DRIVER_STATUS(RCC_LL_SetSystemClockSource(RCC_CFGR_SW_HSE));
	ASSERT_DRIVER_STATUS(_RCC_WaitForSystemClockSwitch(RCC_SYS_CLK_HSE));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesCache());
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SwitchClockSourceToPLL(void)
{
	if (RCC_LL_GetPLLReadyStatus() != DRIVER_STATUS_READY)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	ASSERT_DRIVER_STATUS(RCC_LL_SetSystemClockSource(RCC_CFGR_SW_PLL));
	ASSERT_DRIVER_STATUS(_RCC_WaitForSystemClockSwitch(RCC_SYS_CLK_PLL));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesCache());
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
	RCC_LL_EnableHSI();
	ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReady(RCC_LL_GetHSIReadyStatus, DRIVER_STATUS_READY));

	if (activeSource == RCC_SYS_CLK_PLL)
	{
		ASSERT_DRIVER_STATUS(RCC_SwitchClockSourceToHSI());
		activeSource = RCC_SYS_CLK_HSI;
	}

	if ((pClockTreeConfig->system.clk_src == RCC_SYS_CLK_HSE) ||
		((pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL) && (pClockTreeConfig->system.pll.source == RCC_PLL_SRC_HSE)))
	{
		RCC_LL_EnableHSE();
		ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReady(RCC_LL_GetHSEReadyStatus, DRIVER_STATUS_READY));
	}

	if (RCC_LL_GetPLLReadyStatus() == DRIVER_STATUS_READY)
	{
		RCC_LL_DisablePLL();
		ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReady(RCC_LL_GetPLLReadyStatus, DRIVER_STATUS_OFF));
	}

	ASSERT_DRIVER_STATUS(_RCC_ApplyBusPrescalerConfig(&pClockTreeConfig->bus));
	ASSERT_DRIVER_STATUS(_RCC_ApplyComponentPrescalerConfig(&pClockTreeConfig->component));

	if (pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL)
	{
		pllSource = _RCC_GetPLLSourceLLField(pClockTreeConfig->system.pll.source);
		pllMultiplier = _RCC_GetPLLMultiplierLLField(pClockTreeConfig->system.pll.multiplication_factor);

		if ((pllSource == RCC_DRIVER_INVALID_FIELD) || (pllMultiplier == RCC_DRIVER_INVALID_FIELD))
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		ASSERT_DRIVER_STATUS(RCC_LL_SetPLLSource(pllSource));

		if (pClockTreeConfig->system.pll.source == RCC_PLL_SRC_HSE)
		{
			pllDivider = _RCC_GetPLLHSEDividerLLField(pClockTreeConfig->system.pll.source_prescaler);
			if (pllDivider == RCC_DRIVER_INVALID_FIELD)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}

			ASSERT_DRIVER_STATUS(RCC_LL_SetPLLHSEDivider(pllDivider));
		}

		ASSERT_DRIVER_STATUS(RCC_LL_SetPLLMultiplier(pllMultiplier));
		RCC_LL_EnablePLL();
		ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReady(RCC_LL_GetPLLReadyStatus, DRIVER_STATUS_READY));
	}

	switch (pClockTreeConfig->system.clk_src)
	{
		case RCC_SYS_CLK_HSI:
		{
			if (activeSource != RCC_SYS_CLK_HSI)
			{
				ASSERT_DRIVER_STATUS(RCC_SwitchClockSourceToHSI());
			}
			break;
		}
		case RCC_SYS_CLK_HSE:
		{
			if (activeSource != RCC_SYS_CLK_HSE)
			{
				ASSERT_DRIVER_STATUS(RCC_SwitchClockSourceToHSE());
			}
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

	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesCache());
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_Config(const rcc_config_t* const pRCCConfig)
{
	rcc_clock_frequencies_t currentClockFrequencies =
	{
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO
	};
	rcc_clock_frequencies_t targetClockFrequencies =
	{
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO
	};

	if (pRCCConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(RCC_ValidateConfig(pRCCConfig));
	ASSERT_DRIVER_STATUS(_RCC_LoadClockFrequenciesFromHardware(&currentClockFrequencies));
	ASSERT_DRIVER_STATUS(_RCC_LoadClockFrequenciesFromConfig(&(pRCCConfig->clock_tree), &targetClockFrequencies));

	if (targetClockFrequencies.sysclk > currentClockFrequencies.sysclk)
	{
		ASSERT_DRIVER_STATUS(RCC_ConfigFlash(&(pRCCConfig->flash)));
		ASSERT_DRIVER_STATUS(RCC_ConfigClockTree(&(pRCCConfig->clock_tree)));
	}
	else
	{
		ASSERT_DRIVER_STATUS(RCC_ConfigClockTree(&(pRCCConfig->clock_tree)));
		ASSERT_DRIVER_STATUS(RCC_ConfigFlash(&(pRCCConfig->flash)));
	}

	return DRIVER_STATUS_SUCCESS;
}

void RCC_Load72MHzDefaultConfig(rcc_config_t* const pRCCConfig)
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

driver_status_t RCC_Config72MHz(void)
{
	rcc_config_t cfg = {0};
	RCC_Load72MHzDefaultConfig(&cfg);
	return RCC_Config(&cfg);
}

// ==================================================================================================== //
//                                   Driver Status and Frequency APIs                                   //
// ==================================================================================================== //

rcc_system_clock_t RCC_GetSysClkSrc(void)
{
	uint32_t status = RCC_CFGR_SWS_HSI;

	if (RCC_LL_GetSystemClockStatus(&status) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_SYS_CLK_HSI;
	}

	return _RCC_GetSystemClockSourceFromLLStatus(status);
}

rcc_pll_src_t RCC_GetPLLSource(void)
{
	uint32_t source = RCC_CFGR_PLLSRC_HSI_DIV2;

	if (RCC_LL_GetPLLSource(&source) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_PLL_SRC_HSI;
	}

	if (source == RCC_CFGR_PLLSRC_HSE)
	{
		return RCC_PLL_SRC_HSE;
	}

	return RCC_PLL_SRC_HSI;
}

rcc_pll_src_psc_t RCC_GetPLLSourcePrescaler(void)
{
	uint32_t divider = RCC_CFGR_PLLXTPRE_HSE;

	if (RCC_GetPLLSource() == RCC_PLL_SRC_HSI)
	{
		return RCC_PLL_SRC_HSI_DIV_2;
	}

	if (RCC_LL_GetPLLHSEDivider(&divider) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_PLL_SRC_HSE_DIV_1;
	}

	if (divider == RCC_CFGR_PLLXTPRE_HSE_DIV2)
	{
		return RCC_PLL_SRC_HSE_DIV_2;
	}

	return RCC_PLL_SRC_HSE_DIV_1;
}

rcc_pll_mul_t RCC_GetPLLMultiplier(void)
{
	uint32_t multiplier = RCC_CFGR_PLLMUL_2;

	if (RCC_LL_GetPLLMultiplier(&multiplier) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_PLL_MUL_2;
	}

	switch (multiplier)
	{
		case RCC_CFGR_PLLMUL_2:
		{
			return RCC_PLL_MUL_2;
		}
		case RCC_CFGR_PLLMUL_3:
		{
			return RCC_PLL_MUL_3;
		}
		case RCC_CFGR_PLLMUL_4:
		{
			return RCC_PLL_MUL_4;
		}
		case RCC_CFGR_PLLMUL_5:
		{
			return RCC_PLL_MUL_5;
		}
		case RCC_CFGR_PLLMUL_6:
		{
			return RCC_PLL_MUL_6;
		}
		case RCC_CFGR_PLLMUL_7:
		{
			return RCC_PLL_MUL_7;
		}
		case RCC_CFGR_PLLMUL_8:
		{
			return RCC_PLL_MUL_8;
		}
		case RCC_CFGR_PLLMUL_9:
		{
			return RCC_PLL_MUL_9;
		}
		case RCC_CFGR_PLLMUL_10:
		{
			return RCC_PLL_MUL_10;
		}
		case RCC_CFGR_PLLMUL_11:
		{
			return RCC_PLL_MUL_11;
		}
		case RCC_CFGR_PLLMUL_12:
		{
			return RCC_PLL_MUL_12;
		}
		case RCC_CFGR_PLLMUL_13:
		{
			return RCC_PLL_MUL_13;
		}
		case RCC_CFGR_PLLMUL_14:
		{
			return RCC_PLL_MUL_14;
		}
		case RCC_CFGR_PLLMUL_15:
		{
			return RCC_PLL_MUL_15;
		}
		case RCC_CFGR_PLLMUL_16:
		{
			return RCC_PLL_MUL_16;
		}
		default:
		{
			return RCC_PLL_MUL_2;
		}
	}
}

driver_status_t RCC_GetClockFrequencies(rcc_clock_frequencies_t* const pClockFrequencies)
{
	if (pClockFrequencies == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	if (_rccClockFrequenciesSnapshot.sysclk == RCC_FREQ_ZERO)
	{
		ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesCache());
	}

	*pClockFrequencies = _rccClockFrequenciesSnapshot;
	return DRIVER_STATUS_SUCCESS;
}

frequency_t RCC_GetCoreClockFreq(void)
{
	rcc_clock_frequencies_t clockFrequencies =
	{
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO
	};

	if (RCC_GetClockFrequencies(&clockFrequencies) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_FREQ_ZERO;
	}

	return clockFrequencies.sysclk;
}

rcc_bus_prescaler_t RCC_GetBusPrescaler(const rcc_bus_t bus)
{
	uint32_t ahbPrescaler = RCC_CFGR_HPRE_DIV1;
	uint32_t apb1Prescaler = RCC_CFGR_PPRE1_DIV1;
	uint32_t apb2Prescaler = RCC_CFGR_PPRE2_DIV1;

	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			if (RCC_LL_GetAHBPrescaler(&ahbPrescaler) != DRIVER_STATUS_SUCCESS)
			{
				return RCC_AHB_DIV_1;
			}
			return _RCC_GetAHBPrescalerSelectorFromLLField(ahbPrescaler);
		}
		case RCC_APB1_BUS:
		{
			if (RCC_LL_GetAPB1Prescaler(&apb1Prescaler) != DRIVER_STATUS_SUCCESS)
			{
				return RCC_APB1_DIV_1;
			}
			return _RCC_GetAPB1PrescalerSelectorFromLLField(apb1Prescaler);
		}
		case RCC_APB2_BUS:
		{
			if (RCC_LL_GetAPB2Prescaler(&apb2Prescaler) != DRIVER_STATUS_SUCCESS)
			{
				return RCC_APB2_DIV_1;
			}
			return _RCC_GetAPB2PrescalerSelectorFromLLField(apb2Prescaler);
		}
		default:
		{
			return RCC_AHB_DIV_1;
		}
	}
}

frequency_t RCC_GetBusFreq(const rcc_bus_t bus)
{
	rcc_clock_frequencies_t clockFrequencies =
	{
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO
	};

	if (RCC_GetClockFrequencies(&clockFrequencies) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_FREQ_ZERO;
	}

	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			return clockFrequencies.hclk;
		}
		case RCC_APB1_BUS:
		{
			return clockFrequencies.pclk1;
		}
		case RCC_APB2_BUS:
		{
			return clockFrequencies.pclk2;
		}
		default:
		{
			return clockFrequencies.hclk;
		}
	}
}

frequency_t RCC_GetADCFreq(void)
{
	rcc_clock_frequencies_t clockFrequencies =
	{
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO
	};

	if (RCC_GetClockFrequencies(&clockFrequencies) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_FREQ_ZERO;
	}

	return clockFrequencies.adcclk;
}

frequency_t RCC_GetUSBFreq(void)
{
	rcc_clock_frequencies_t clockFrequencies =
	{
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO,
		RCC_FREQ_ZERO
	};

	if (RCC_GetClockFrequencies(&clockFrequencies) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_FREQ_ZERO;
	}

	return clockFrequencies.usbclk;
}
