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

static const _rcc_field_value_map_t _RCC_APBPrescalerLUT[] =
{
	{ RCC_LL_APB_DIV_1,		1UL  },
	{ RCC_LL_APB_DIV_2,		2UL  },
	{ RCC_LL_APB_DIV_4,		4UL  },
	{ RCC_LL_APB_DIV_8,		8UL  },
	{ RCC_LL_APB_DIV_16,	16UL }
};

static const _rcc_field_value_map_t _RCC_ADCPrescalerLUT[] =
{
	{ RCC_LL_ADC_DIV_2,		2UL },
	{ RCC_LL_ADC_DIV_4,		4UL },
	{ RCC_LL_ADC_DIV_6,		6UL },
	{ RCC_LL_ADC_DIV_8,		8UL }
};

static const _rcc_field_value_map_t _RCC_USBPrescalerLUT[] =
{
	{ RCC_LL_USB_DIV_1_5,	RCC_USB_DIV_1_5 },
	{ RCC_LL_USB_DIV_1,	RCC_USB_DIV_1   }
};

static const _rcc_field_value_map_t _RCC_PLLMultiplierLUT[] =
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

/** @brief Cached RCC clock frequencies snapshot maintained by the driver. */
rcc_clock_frequencies_t _rccClockFrequenciesSnapshot =
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
static driver_status_t _RCC_WaitForClockSourceReadyStatus(_rcc_ready_status_getter_t const pReadyGetter, const driver_status_t targetStatus)
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
static driver_status_t _RCC_WaitForSystemClockSourceSwitch(const rcc_system_clock_t source)
{
	rcc_ll_sysclk_status_t	status = RCC_LL_SYSCLK_STATUS_HSI;
	volatile uint32_t		timeout = RCC_READY_TIMEOUT;

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

/**
 * @brief Finds the LUT index whose LL field matches the requested field value.
 * @param[in] pLUT Pointer to the LUT to scan.
 * @param[in] itemCount Number of valid items in the LUT.
 * @param[in] fieldValue LL field value to search for.
 * @returns Matching LUT index when found, otherwise @ref RCC_DRIVER_INVALID_INDEX.
 */
__STATIC_FORCEINLINE uint32_t _RCC_FindFieldValueMapIndex(const _rcc_field_value_map_t* const pLUT, const uint32_t itemCount, const uint32_t fieldValue)
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
 * @brief Returns the effective AHB divider for the supplied driver selector.
 * @param[in] prescalerSelector The AHB prescaler selector.
 * @returns The effective divider value.
 */
__STATIC_FORCEINLINE rcc_freq_t _RCC_GetAHBPrescalerDividerBySelector(const rcc_bus_prescaler_t prescalerSelector)
{
	return (rcc_freq_t) _RCC_GetFieldValueMapValueByIndex
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
__STATIC_FORCEINLINE rcc_freq_t _RCC_GetAPBBusPrescalerDividerBySelector(const rcc_bus_prescaler_t prescalerSelector)
{
	return (rcc_freq_t) _RCC_GetFieldValueMapValueByIndex
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
__STATIC_FORCEINLINE rcc_freq_t _RCC_GetADCPrescalerDividerBySelector(const rcc_component_prescaler_t prescalerSelector)
{
	return (rcc_freq_t) _RCC_GetFieldValueMapValueByIndex
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

	return _RCC_GetFieldValueMapValueByIndex
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
	return _RCC_GetFieldValueMapValueByIndex
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
__STATIC_FORCEINLINE uint32_t _RCC_GetAPBPrescalerLLField(const rcc_bus_prescaler_t prescalerSelector)
{
	return _RCC_GetFieldValueMapValueByIndex
	(
		_RCC_APBPrescalerLUT,
		ARRAY_SIZE(_RCC_APBPrescalerLUT),
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
	return _RCC_GetFieldValueMapValueByIndex
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
	return _RCC_GetFieldValueMapValueByIndex
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
__STATIC_FORCEINLINE rcc_system_clock_t _RCC_GetSystemClockSourceFromLLStatus(const rcc_ll_sysclk_status_t status)
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

/**
 * @brief Decodes the LL AHB prescaler field to the public selector value.
 * @param[in] prescalerField The LL AHB prescaler field.
 * @returns The corresponding public selector value.
 */
__STATIC_FORCEINLINE rcc_bus_prescaler_t _RCC_GetAHBPrescalerSelectorFromLLField(const rcc_ll_ahb_prescaler_t prescalerField)
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
__STATIC_FORCEINLINE rcc_bus_prescaler_t _RCC_GetAPBPrescalerSelectorFromLLField(const rcc_ll_apb_prescaler_t prescalerField)
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
 * @brief Decodes the LL ADC prescaler field to the public selector value.
 * @param[in] prescalerField The LL ADC prescaler field.
 * @returns The corresponding public selector value.
 */
__STATIC_FORCEINLINE rcc_component_prescaler_t _RCC_GetADCPrescalerSelectorFromLLField(const rcc_ll_adc_prescaler_t prescalerField)
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
__STATIC_FORCEINLINE rcc_component_prescaler_t _RCC_GetUSBPrescalerSelectorFromLLField(const rcc_ll_usb_prescaler_t prescalerField)
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
 * @brief Returns the PLL input frequency for the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The PLL input frequency.
 */
__STATIC_FORCEINLINE rcc_freq_t _RCC_GetPLLInputClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
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
__STATIC_FORCEINLINE rcc_freq_t _RCC_GetSystemClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
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
			return (_RCC_GetPLLInputClockFrequency(pClockTreeConfig) * (rcc_freq_t) pClockTreeConfig->system.pll.multiplication_factor);
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
__STATIC_FORCEINLINE rcc_freq_t _RCC_GetAHBClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	return (_RCC_GetSystemClockFrequency(pClockTreeConfig) / _RCC_GetAHBPrescalerDividerBySelector(pClockTreeConfig->bus.AHB));
}

/**
 * @brief Returns the target APB1 frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target APB1 frequency.
 */
__STATIC_FORCEINLINE rcc_freq_t _RCC_GetAPB1ClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	return (_RCC_GetAHBClockFrequency(pClockTreeConfig) / _RCC_GetAPBBusPrescalerDividerBySelector(pClockTreeConfig->bus.APB1));
}

/**
 * @brief Returns the target APB2 frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target APB2 frequency.
 */
__STATIC_FORCEINLINE rcc_freq_t _RCC_GetAPB2ClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	return (_RCC_GetAHBClockFrequency(pClockTreeConfig) / _RCC_GetAPBBusPrescalerDividerBySelector(pClockTreeConfig->bus.APB2));
}

/**
 * @brief Returns the target ADC frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target ADC frequency.
 */
__STATIC_FORCEINLINE rcc_freq_t _RCC_GetADCClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	return (_RCC_GetAPB2ClockFrequency(pClockTreeConfig) / _RCC_GetADCPrescalerDividerBySelector(pClockTreeConfig->component.ADC));
}

/**
 * @brief Returns the target USB frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target USB frequency.
 */
static rcc_freq_t _RCC_GetUSBClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	const rcc_freq_t pllClock = _RCC_GetPLLInputClockFrequency(pClockTreeConfig) * (rcc_freq_t) pClockTreeConfig->system.pll.multiplication_factor;

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
static driver_status_t _RCC_LoadClockFrequenciesSnapshotFromConfig(const rcc_clock_tree_config_t* const pClockTreeConfig, rcc_clock_frequencies_t* const pClockFrequencies)
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
static driver_status_t _RCC_ValidatePLLConfiguration(const rcc_clock_tree_config_t* const pClockTreeConfig)
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
static driver_status_t _RCC_ValidateClockTreeConfiguration(const rcc_config_t* const pRCCConfig)
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

	if (_RCC_GetAPBPrescalerLLField(pClockTreeConfig->bus.APB1) == RCC_DRIVER_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (_RCC_GetAPBPrescalerLLField(pClockTreeConfig->bus.APB2) == RCC_DRIVER_INVALID_FIELD)
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
		ASSERT_DRIVER_STATUS(_RCC_ValidatePLLConfiguration(pClockTreeConfig));
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Stores the supplied clock frequencies into the RCC driver cache.
 * @param[in] pClockFrequencies Pointer to the clock frequencies snapshot.
 */
__STATIC_FORCEINLINE void _RCC_UpdateClockFrequenciesSnapshotCache(const rcc_clock_frequencies_t* const pClockFrequencies)
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
static driver_status_t _RCC_LoadClockFrequenciesSnapshotFromHardware(rcc_clock_frequencies_t* const pClockFrequencies);

/**
 * @brief Refreshes the RCC driver clock-frequency snapshot cache from current hardware state.
 * @returns - @ref driver_status_t Status of the cache refresh operation.
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The cache snapshot was refreshed successfully.
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read while rebuilding the snapshot.
 */
static driver_status_t _RCC_RefreshClockFrequenciesSnapshotCache(void)
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

	ASSERT_DRIVER_STATUS(_RCC_LoadClockFrequenciesSnapshotFromHardware(&clockFrequencies));
	_RCC_UpdateClockFrequenciesSnapshotCache(&clockFrequencies);
	return DRIVER_STATUS_SUCCESS;
}
static driver_status_t _RCC_LoadClockFrequenciesSnapshotFromHardware(rcc_clock_frequencies_t* const pClockFrequencies)
{
	rcc_system_clock_t systemClockSource = RCC_SYS_CLK_HSI;
	rcc_ll_adc_prescaler_t adcPrescaler = RCC_LL_ADC_DIV_2;
	rcc_ll_usb_prescaler_t usbPrescaler = RCC_LL_USB_DIV_1_5;
	rcc_freq_t pllInputFrequency = RCC_FREQ_ZERO;

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
			pClockFrequencies->sysclk = (pllInputFrequency * (rcc_freq_t) RCC_GetPLLMultiplier());
			break;
		}
		default:
		{
			pClockFrequencies->sysclk = RCC_HSI_FREQ;
			break;
		}
	}

	pClockFrequencies->hclk = (pClockFrequencies->sysclk / (rcc_freq_t) RCC_GetBusPrescaler(RCC_AHB_BUS));
	pClockFrequencies->pclk1 = (pClockFrequencies->hclk / (rcc_freq_t) RCC_GetBusPrescaler(RCC_APB1_BUS));
	pClockFrequencies->pclk2 = (pClockFrequencies->hclk / (rcc_freq_t) RCC_GetBusPrescaler(RCC_APB2_BUS));

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
static driver_status_t _RCC_ValidateClockFrequencyLimits(const rcc_clock_frequencies_t* const pClockFreqSnapshot)
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
static driver_status_t _RCC_ValidateClockConfigurationDependencies(const rcc_config_t* const pRCCConfig, const rcc_clock_frequencies_t* const pClockFreqSnapshot)
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
	ASSERT_DRIVER_STATUS(_RCC_ValidateClockTreeConfiguration(pRCCConfig));
	ASSERT_DRIVER_STATUS(_RCC_LoadClockFrequenciesSnapshotFromConfig(pClockTreeConfig, &clockFreqSnapshot));
	ASSERT_DRIVER_STATUS(_RCC_ValidateClockFrequencyLimits(&clockFreqSnapshot));
	ASSERT_DRIVER_STATUS(_RCC_ValidateClockConfigurationDependencies(pRCCConfig, &clockFreqSnapshot));
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

	ahbPrescaler = _RCC_GetAHBPrescalerLLField(pBusConfig->AHB);
	apb1Prescaler = _RCC_GetAPBPrescalerLLField(pBusConfig->APB1);
	apb2Prescaler = _RCC_GetAPBPrescalerLLField(pBusConfig->APB2);

	if ((ahbPrescaler == RCC_DRIVER_INVALID_FIELD) || (apb1Prescaler == RCC_DRIVER_INVALID_FIELD) || (apb2Prescaler == RCC_DRIVER_INVALID_FIELD))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(RCC_LL_SetAHBPrescaler((rcc_ll_ahb_prescaler_t) ahbPrescaler));
	ASSERT_DRIVER_STATUS(RCC_LL_SetAPB1Prescaler((rcc_ll_apb_prescaler_t) apb1Prescaler));
	ASSERT_DRIVER_STATUS(RCC_LL_SetAPB2Prescaler((rcc_ll_apb_prescaler_t) apb2Prescaler));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesSnapshotCache());
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

	adcPrescaler = _RCC_GetADCPrescalerLLField(pComponentConfig->ADC);
	usbPrescaler = _RCC_GetUSBPrescalerLLField(pComponentConfig->USB);

	if ((adcPrescaler == RCC_DRIVER_INVALID_FIELD) || (usbPrescaler == RCC_DRIVER_INVALID_FIELD))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS(RCC_LL_SetADCPrescaler((rcc_ll_adc_prescaler_t) adcPrescaler));
	ASSERT_DRIVER_STATUS(RCC_LL_SetUSBPrescaler((rcc_ll_usb_prescaler_t) usbPrescaler));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesSnapshotCache());
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SwitchClockSourceToHSI(void)
{
	RCC_LL_HSI_Enable();
	ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReadyStatus(RCC_LL_HSI_GetReadyStatus, DRIVER_STATUS_READY));
	ASSERT_DRIVER_STATUS(RCC_LL_SetSystemClockSource(RCC_LL_SYSCLK_SRC_HSI));
	ASSERT_DRIVER_STATUS(_RCC_WaitForSystemClockSourceSwitch(RCC_SYS_CLK_HSI));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesSnapshotCache());
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SwitchClockSourceToHSE(void)
{
	RCC_LL_HSE_Enable();
	ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReadyStatus(RCC_LL_HSE_GetReadyStatus, DRIVER_STATUS_READY));
	ASSERT_DRIVER_STATUS(RCC_LL_SetSystemClockSource(RCC_LL_SYSCLK_SRC_HSE));
	ASSERT_DRIVER_STATUS(_RCC_WaitForSystemClockSourceSwitch(RCC_SYS_CLK_HSE));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesSnapshotCache());
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SwitchClockSourceToPLL(void)
{
	if (RCC_LL_PLL_GetReadyStatus() != DRIVER_STATUS_READY)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	ASSERT_DRIVER_STATUS(RCC_LL_SetSystemClockSource(RCC_LL_SYSCLK_SRC_PLL));
	ASSERT_DRIVER_STATUS(_RCC_WaitForSystemClockSourceSwitch(RCC_SYS_CLK_PLL));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesSnapshotCache());
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
	ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReadyStatus(RCC_LL_HSI_GetReadyStatus, DRIVER_STATUS_READY));

	if (activeSource == RCC_SYS_CLK_PLL)
	{
		ASSERT_DRIVER_STATUS(RCC_SwitchClockSourceToHSI());
	}

	if ((pClockTreeConfig->system.clk_src == RCC_SYS_CLK_HSE) ||
		((pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL) && (pClockTreeConfig->system.pll.source == RCC_PLL_SRC_HSE)))
	{
		RCC_LL_HSE_Enable();
		ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReadyStatus(RCC_LL_HSE_GetReadyStatus, DRIVER_STATUS_READY));
	}

	if (RCC_LL_PLL_GetReadyStatus() == DRIVER_STATUS_READY)
	{
		RCC_LL_PLL_Disable();
		ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReadyStatus(RCC_LL_PLL_GetReadyStatus, DRIVER_STATUS_OFF));
	}

	ASSERT_DRIVER_STATUS(RCC_ConfigBusPrescaler(&pClockTreeConfig->bus));
	ASSERT_DRIVER_STATUS(RCC_ConfigComponentPrescaler(&pClockTreeConfig->component));

	if (pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL)
	{
		pllSource = _RCC_GetPLLSourceLLField(pClockTreeConfig->system.pll.source);
		pllMultiplier = _RCC_GetPLLMultiplierLLField(pClockTreeConfig->system.pll.multiplication_factor);

		if ((pllSource == RCC_DRIVER_INVALID_FIELD) || (pllMultiplier == RCC_DRIVER_INVALID_FIELD))
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		ASSERT_DRIVER_STATUS(RCC_LL_SetPLLSource((rcc_ll_pll_src_t) pllSource));

		if (pClockTreeConfig->system.pll.source == RCC_PLL_SRC_HSE)
		{
			pllDivider = _RCC_GetPLLHSEDividerLLField(pClockTreeConfig->system.pll.source_prescaler);
			if (pllDivider == RCC_DRIVER_INVALID_FIELD)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}

			ASSERT_DRIVER_STATUS(RCC_LL_SetPLLHSEDivider((rcc_ll_pll_hse_div_t) pllDivider));
		}

		ASSERT_DRIVER_STATUS(RCC_LL_SetPLLMultiplier((rcc_ll_pll_mul_t) pllMultiplier));
		RCC_LL_PLL_Enable();
		ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReadyStatus(RCC_LL_PLL_GetReadyStatus, DRIVER_STATUS_READY));
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

	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesSnapshotCache());
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

	return _RCC_GetSystemClockSourceFromLLStatus(status);
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

	return RCC_PLL_SRC_HSI;
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

	return RCC_PLL_SRC_HSE_DIV_1;
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

driver_status_t RCC_ClockFrequenciesGet(rcc_clock_frequencies_t* const pClockFrequencies)
{
	if (pClockFrequencies == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	if (_rccClockFrequenciesSnapshot.sysclk == RCC_FREQ_ZERO)
	{
		ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesSnapshotCache());
	}

	*pClockFrequencies = _rccClockFrequenciesSnapshot;
	return DRIVER_STATUS_SUCCESS;
}

rcc_freq_t RCC_GetCoreClockFreq(void)
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

	if (RCC_ClockFrequenciesGet(&clockFrequencies) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_FREQ_ZERO;
	}

	return clockFrequencies.sysclk;
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
				return (rcc_bus_prescaler_t) _RCC_GetAHBPrescalerDividerBySelector(RCC_AHB_DIV_1);
			}
			return (rcc_bus_prescaler_t) _RCC_GetAHBPrescalerDividerBySelector(_RCC_GetAHBPrescalerSelectorFromLLField(ahbPrescaler));
		}
		case RCC_APB1_BUS:
		{
			if (RCC_LL_GetAPB1Prescaler(&apbPrescaler) != DRIVER_STATUS_SUCCESS)
			{
				return (rcc_bus_prescaler_t) _RCC_GetAPBBusPrescalerDividerBySelector(RCC_APB1_DIV_1);
			}
			return (rcc_bus_prescaler_t) _RCC_GetAPBBusPrescalerDividerBySelector(_RCC_GetAPBPrescalerSelectorFromLLField(apbPrescaler));
		}
		case RCC_APB2_BUS:
		{
			if (RCC_LL_GetAPB2Prescaler(&apbPrescaler) != DRIVER_STATUS_SUCCESS)
			{
				return (rcc_bus_prescaler_t) _RCC_GetAPBBusPrescalerDividerBySelector(RCC_APB2_DIV_1);
			}
			return (rcc_bus_prescaler_t) _RCC_GetAPBBusPrescalerDividerBySelector(_RCC_GetAPBPrescalerSelectorFromLLField(apbPrescaler));
		}
		default:
		{
			return (rcc_bus_prescaler_t) _RCC_GetAPBBusPrescalerDividerBySelector(RCC_APB1_DIV_1);
		}
	}
}

rcc_freq_t RCC_GetBusFreq(const rcc_bus_t bus)
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

	if (RCC_ClockFrequenciesGet(&clockFrequencies) != DRIVER_STATUS_SUCCESS)
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

rcc_freq_t RCC_GetADCFreq(void)
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

	if (RCC_ClockFrequenciesGet(&clockFrequencies) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_FREQ_ZERO;
	}

	return clockFrequencies.adcclk;
}

rcc_freq_t RCC_GetUSBFreq(void)
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

	if (RCC_ClockFrequenciesGet(&clockFrequencies) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_FREQ_ZERO;
	}

	return clockFrequencies.usbclk;
}
