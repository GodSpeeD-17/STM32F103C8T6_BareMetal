/**
 * @file	rcc_codec.c
 * @author	Shrey Shah
 * @brief	RCC Selector Codec Implementation
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * This source file implements the pure selector/field translation helpers
 * declared in @ref rcc_codec.h. Every function here is a deterministic
 * transformation with no peripheral pointer and no volatile I/O; the RCC
 * driver layer owns every hardware read/write around these calls.
 */

// ==================================================================================================== //
//													Includes											  //
// ==================================================================================================== //
#include "rcc_codec.h"

// ==================================================================================================== //
//												Typedefs												//
// ==================================================================================================== //

/** @brief Internal field-to-value lookup descriptor @typedef _rcc_field_value_map_t */
typedef struct _rcc_field_value_map_t
{
	uint32_t	ll_field;
	uint32_t	value;
} _rcc_field_value_map_t;

// ==================================================================================================== //
//											Look Up Tables (LUTs)										//
// ==================================================================================================== //

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

// ==================================================================================================== //
//                                       Local LUT Search Helpers                                       //
// ==================================================================================================== //

/**
 * @brief Finds the LUT index whose LL field matches the requested field value
 * @param[in] pLUT Pointer to the LUT to scan
 * @param[in] itemCount Number of valid items in the LUT
 * @param[in] fieldValue LL field value to search for
 * @returns Matching LUT index when found, otherwise `itemCount`
 */
__STATIC_FORCEINLINE uint32_t Codec_RCC_FindFieldValueMapIndex(const _rcc_field_value_map_t* const pLUT, const uint32_t itemCount, const uint32_t fieldValue)
{
	// Local Variable
	uint32_t index = 0x00UL;

	//! Linear scan is acceptable because every RCC selector LUT has at most sixteen rows.
	for (index = 0x00UL; index < itemCount; index++)
	{
		if (pLUT[index].ll_field == fieldValue)
		{
			return index;
		}
	}

	return itemCount;
}

/**
 * @brief Returns the logical value stored at the requested LUT index
 * @param[in] pLUT Pointer to the LUT to read
 * @param[in] itemCount Number of valid items in the LUT
 * @param[in] index Requested LUT index
 * @param[in] defaultValue Fallback value used when the index is outside the LUT range
 * @returns Logical value stored in the LUT, or @p defaultValue when the index is invalid
 */
__STATIC_FORCEINLINE uint32_t Codec_RCC_GetFieldValueMapValueByIndex(const _rcc_field_value_map_t* const pLUT, const uint32_t itemCount, const uint32_t index, const uint32_t defaultValue)
{
	//! Preserve the historical safe-default fallback instead of surfacing an out-of-range error.
	if (index >= itemCount)
	{
		return defaultValue;
	}

	return pLUT[index].value;
}

/**
 * @brief Returns the LL field stored at the requested LUT index
 * @param[in] pLUT Pointer to the LUT to read
 * @param[in] itemCount Number of valid items in the LUT
 * @param[in] index Requested LUT index
 * @param[in] defaultField Fallback LL field used when the index is outside the LUT range
 * @returns LL field stored in the LUT, or @p defaultField when the index is invalid
 */
__STATIC_FORCEINLINE uint32_t Codec_RCC_GetFieldValueMapLLFieldByIndex(const _rcc_field_value_map_t* const pLUT, const uint32_t itemCount, const uint32_t index, const uint32_t defaultField)
{
	//! Signal "not encodable" by returning the caller-supplied sentinel field.
	if (index >= itemCount)
	{
		return defaultField;
	}

	return pLUT[index].ll_field;
}

/** @brief Sentinel LL field returned by an encode helper when the selector has no hardware encoding */
#define RCC_CODEC_INVALID_FIELD				((uint32_t) 0xFFFFFFFFUL)

// ==================================================================================================== //
//                                    RCC System Clock Source Codec                                     //
// ==================================================================================================== //

/**
 * @addtogroup RCC_03_Driver_08_Codec
 * @{
 */

driver_status_t Codec_RCC_EncodeSystemClockSource(const rcc_system_clock_t source, uint32_t* const pField)
{
	if (pField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (source)
	{
		case RCC_SYS_CLK_HSI:
		{
			*pField = RCC_CFGR_SW_HSI;
			return DRIVER_STATUS_SUCCESS;
		}
		case RCC_SYS_CLK_HSE:
		{
			*pField = RCC_CFGR_SW_HSE;
			return DRIVER_STATUS_SUCCESS;
		}
		case RCC_SYS_CLK_PLL:
		{
			*pField = RCC_CFGR_SW_PLL;
			return DRIVER_STATUS_SUCCESS;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}
}

driver_status_t Codec_RCC_DecodeSystemClockSource(const uint32_t statusField, rcc_system_clock_t* const pSource)
{
	if (pSource == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (statusField)
	{
		case RCC_CFGR_SWS_HSE:
		{
			*pSource = RCC_SYS_CLK_HSE;
			break;
		}
		case RCC_CFGR_SWS_PLL:
		{
			*pSource = RCC_SYS_CLK_PLL;
			break;
		}
		case RCC_CFGR_SWS_HSI:
		default:
		{
			//! Unrecognized status decodes to the HSI reset-state default, matching prior behavior.
			*pSource = RCC_SYS_CLK_HSI;
			break;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//                                          RCC PLL Field Codec                                         //
// ==================================================================================================== //

driver_status_t Codec_RCC_EncodePLLSource(const rcc_pll_src_t source, uint32_t* const pField)
{
	if (pField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (source)
	{
		case RCC_PLL_SRC_HSI:
		{
			*pField = RCC_CFGR_PLLSRC_HSI_DIV2;
			return DRIVER_STATUS_SUCCESS;
		}
		case RCC_PLL_SRC_HSE:
		{
			*pField = RCC_CFGR_PLLSRC_HSE;
			return DRIVER_STATUS_SUCCESS;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}
}

driver_status_t Codec_RCC_EncodePLLHSEDivider(const rcc_pll_src_psc_t divider, uint32_t* const pField)
{
	if (pField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (divider)
	{
		case RCC_PLL_SRC_HSE_DIV_1:
		{
			*pField = RCC_CFGR_PLLXTPRE_HSE;
			return DRIVER_STATUS_SUCCESS;
		}
		case RCC_PLL_SRC_HSE_DIV_2:
		{
			*pField = RCC_CFGR_PLLXTPRE_HSE_DIV2;
			return DRIVER_STATUS_SUCCESS;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}
}

driver_status_t Codec_RCC_EncodePLLMultiplier(const rcc_pll_mul_t multiplier, uint32_t* const pField)
{
	uint32_t llField = RCC_CODEC_INVALID_FIELD;

	if (pField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Reject the range before indexing so the LUT offset below never underflows.
	if ((multiplier < RCC_PLL_MUL_2) || (multiplier > RCC_PLL_MUL_16))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	llField = Codec_RCC_GetFieldValueMapLLFieldByIndex
	(
		_RCC_PLLMultiplierLUT,
		ARRAY_SIZE(_RCC_PLLMultiplierLUT),
		(uint32_t) (multiplier - RCC_PLL_MUL_2),
		RCC_CODEC_INVALID_FIELD
	);

	if (llField == RCC_CODEC_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pField = llField;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//                                       RCC Bus Prescaler Codec                                        //
// ==================================================================================================== //

driver_status_t Codec_RCC_EncodeAHBPrescaler(const rcc_bus_prescaler_t selector, uint32_t* const pField)
{
	uint32_t llField = RCC_CODEC_INVALID_FIELD;

	if (pField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	llField = Codec_RCC_GetFieldValueMapLLFieldByIndex
	(
		_RCC_AHBPrescalerLUT,
		ARRAY_SIZE(_RCC_AHBPrescalerLUT),
		(uint32_t) selector,
		RCC_CODEC_INVALID_FIELD
	);

	if (llField == RCC_CODEC_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pField = llField;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_RCC_DecodeAHBPrescaler(const uint32_t field, rcc_bus_prescaler_t* const pSelector)
{
	uint32_t index = 0x00UL;

	if (pSelector == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	index = Codec_RCC_FindFieldValueMapIndex(_RCC_AHBPrescalerLUT, ARRAY_SIZE(_RCC_AHBPrescalerLUT), field);

	//! Unrecognized fields fall back to the div-1 reset-state default, matching prior behavior.
	if (index >= ARRAY_SIZE(_RCC_AHBPrescalerLUT))
	{
		*pSelector = RCC_AHB_DIV_1;
	}
	else
	{
		*pSelector = (rcc_bus_prescaler_t) index;
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_RCC_EncodeAPB1Prescaler(const rcc_bus_prescaler_t selector, uint32_t* const pField)
{
	uint32_t llField = RCC_CODEC_INVALID_FIELD;

	if (pField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	llField = Codec_RCC_GetFieldValueMapLLFieldByIndex
	(
		_RCC_APBPrescalerLUT,
		ARRAY_SIZE(_RCC_APBPrescalerLUT),
		(uint32_t) selector,
		RCC_CODEC_INVALID_FIELD
	);

	if (llField == RCC_CODEC_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pField = llField;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_RCC_DecodeAPB1Prescaler(const uint32_t field, rcc_bus_prescaler_t* const pSelector)
{
	uint32_t index = 0x00UL;

	if (pSelector == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	index = Codec_RCC_FindFieldValueMapIndex(_RCC_APBPrescalerLUT, ARRAY_SIZE(_RCC_APBPrescalerLUT), field);

	//! Unrecognized fields fall back to the div-1 reset-state default, matching prior behavior.
	if (index >= ARRAY_SIZE(_RCC_APBPrescalerLUT))
	{
		*pSelector = RCC_APB1_DIV_1;
	}
	else
	{
		*pSelector = (rcc_bus_prescaler_t) index;
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_RCC_EncodeAPB2Prescaler(const rcc_bus_prescaler_t selector, uint32_t* const pField)
{
	uint32_t llField = RCC_CODEC_INVALID_FIELD;

	if (pField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	llField = Codec_RCC_GetFieldValueMapLLFieldByIndex
	(
		_RCC_APB2PrescalerLUT,
		ARRAY_SIZE(_RCC_APB2PrescalerLUT),
		(uint32_t) selector,
		RCC_CODEC_INVALID_FIELD
	);

	if (llField == RCC_CODEC_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pField = llField;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_RCC_DecodeAPB2Prescaler(const uint32_t field, rcc_bus_prescaler_t* const pSelector)
{
	uint32_t index = 0x00UL;

	if (pSelector == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	index = Codec_RCC_FindFieldValueMapIndex(_RCC_APB2PrescalerLUT, ARRAY_SIZE(_RCC_APB2PrescalerLUT), field);

	//! Unrecognized fields fall back to the div-1 reset-state default, matching prior behavior.
	if (index >= ARRAY_SIZE(_RCC_APB2PrescalerLUT))
	{
		*pSelector = RCC_APB2_DIV_1;
	}
	else
	{
		*pSelector = (rcc_bus_prescaler_t) index;
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//                                     RCC Component Prescaler Codec                                    //
// ==================================================================================================== //

driver_status_t Codec_RCC_EncodeADCPrescaler(const rcc_component_prescaler_t selector, uint32_t* const pField)
{
	uint32_t llField = RCC_CODEC_INVALID_FIELD;

	if (pField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	llField = Codec_RCC_GetFieldValueMapLLFieldByIndex
	(
		_RCC_ADCPrescalerLUT,
		ARRAY_SIZE(_RCC_ADCPrescalerLUT),
		(uint32_t) selector,
		RCC_CODEC_INVALID_FIELD
	);

	if (llField == RCC_CODEC_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pField = llField;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_RCC_DecodeADCPrescaler(const uint32_t field, rcc_component_prescaler_t* const pSelector)
{
	uint32_t index = 0x00UL;

	if (pSelector == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	index = Codec_RCC_FindFieldValueMapIndex(_RCC_ADCPrescalerLUT, ARRAY_SIZE(_RCC_ADCPrescalerLUT), field);

	//! Unrecognized fields fall back to the div-2 reset-state default, matching prior behavior.
	if (index >= ARRAY_SIZE(_RCC_ADCPrescalerLUT))
	{
		*pSelector = RCC_ADC_DIV_2;
	}
	else
	{
		*pSelector = (rcc_component_prescaler_t) index;
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_RCC_EncodeUSBPrescaler(const rcc_component_prescaler_t selector, uint32_t* const pField)
{
	uint32_t llField = RCC_CODEC_INVALID_FIELD;

	if (pField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	llField = Codec_RCC_GetFieldValueMapLLFieldByIndex
	(
		_RCC_USBPrescalerLUT,
		ARRAY_SIZE(_RCC_USBPrescalerLUT),
		(uint32_t) selector,
		RCC_CODEC_INVALID_FIELD
	);

	if (llField == RCC_CODEC_INVALID_FIELD)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pField = llField;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_RCC_DecodeUSBPrescaler(const uint32_t field, rcc_component_prescaler_t* const pSelector)
{
	uint32_t index = 0x00UL;

	if (pSelector == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	index = Codec_RCC_FindFieldValueMapIndex(_RCC_USBPrescalerLUT, ARRAY_SIZE(_RCC_USBPrescalerLUT), field);

	//! Unrecognized fields fall back to the div-1.5 reset-state default, matching prior behavior.
	if (index >= ARRAY_SIZE(_RCC_USBPrescalerLUT))
	{
		*pSelector = RCC_USB_DIV_1_5;
	}
	else
	{
		*pSelector = (rcc_component_prescaler_t) index;
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//                                    RCC Prescaler Divider Resolution                                  //
// ==================================================================================================== //

driver_status_t Codec_RCC_GetAHBPrescalerDivider(const rcc_bus_prescaler_t selector, uint32_t* const pDivider)
{
	if (pDivider == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Preserve the historical 1UL fallback for a selector outside the LUT range.
	*pDivider = Codec_RCC_GetFieldValueMapValueByIndex(_RCC_AHBPrescalerLUT, ARRAY_SIZE(_RCC_AHBPrescalerLUT), (uint32_t) selector, 1UL);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_RCC_GetAPBPrescalerDivider(const rcc_bus_prescaler_t selector, uint32_t* const pDivider)
{
	if (pDivider == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Shared APB1/APB2 LUT: preserve the historical 1UL fallback for an out-of-range selector.
	*pDivider = Codec_RCC_GetFieldValueMapValueByIndex(_RCC_APBPrescalerLUT, ARRAY_SIZE(_RCC_APBPrescalerLUT), (uint32_t) selector, 1UL);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_RCC_GetADCPrescalerDivider(const rcc_component_prescaler_t selector, uint32_t* const pDivider)
{
	if (pDivider == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Preserve the historical 2UL fallback for a selector outside the LUT range.
	*pDivider = Codec_RCC_GetFieldValueMapValueByIndex(_RCC_ADCPrescalerLUT, ARRAY_SIZE(_RCC_ADCPrescalerLUT), (uint32_t) selector, 2UL);
	return DRIVER_STATUS_SUCCESS;
}

/** @} */ // RCC_03_Driver_08_Codec
