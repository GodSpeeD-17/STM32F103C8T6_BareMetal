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
#include "rcc_codec.h"

// ==================================================================================================== //
//													Macros												//
// ==================================================================================================== //
/** @brief Timeout used while validating switch clock @def RCC_READY_TIMEOUT */
#define RCC_READY_TIMEOUT					((uint32_t) 1000UL)

// ==================================================================================================== //
//												Typedefs												//
// ==================================================================================================== //
/** @brief Function to be executed inside validating system clock switch @typedef _rcc_ready_status_getter_t */
typedef driver_status_t (*_rcc_ready_status_getter_t)(void);

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
 * @brief Returns the effective divider currently programmed for the requested bus.
 * @param[in] bus Target bus selector.
 * @returns Effective divider value for the requested bus.
 */
static uint32_t _RCC_GetBusPrescalerDivider(const rcc_bus_t bus)
{
	uint32_t				ahbPrescalerField = RCC_CFGR_HPRE_DIV1;
	uint32_t				apb1PrescalerField = RCC_CFGR_PPRE1_DIV1;
	uint32_t				apb2PrescalerField = RCC_CFGR_PPRE2_DIV1;
	rcc_bus_prescaler_t		prescalerSelector = RCC_AHB_DIV_1;
	uint32_t				divider = 1UL;

	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			if (RCC_LL_GetAHBPrescaler(&ahbPrescalerField) != DRIVER_STATUS_SUCCESS)
			{
				return 1UL;
			}

			//! Decode/resolve failures cannot occur here; both Codec calls always publish a safe default.
			(void) Codec_RCC_DecodeAHBPrescaler(ahbPrescalerField, &prescalerSelector);
			(void) Codec_RCC_GetAHBPrescalerDivider(prescalerSelector, &divider);
			return divider;
		}
		case RCC_APB1_BUS:
		{
			if (RCC_LL_GetAPB1Prescaler(&apb1PrescalerField) != DRIVER_STATUS_SUCCESS)
			{
				return 1UL;
			}

			(void) Codec_RCC_DecodeAPB1Prescaler(apb1PrescalerField, &prescalerSelector);
			(void) Codec_RCC_GetAPBPrescalerDivider(prescalerSelector, &divider);
			return divider;
		}
		case RCC_APB2_BUS:
		{
			if (RCC_LL_GetAPB2Prescaler(&apb2PrescalerField) != DRIVER_STATUS_SUCCESS)
			{
				return 1UL;
			}

			(void) Codec_RCC_DecodeAPB2Prescaler(apb2PrescalerField, &prescalerSelector);
			(void) Codec_RCC_GetAPBPrescalerDivider(prescalerSelector, &divider);
			return divider;
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
	uint32_t divider = 1UL;

	//! Codec divider resolution cannot fail; a `1UL` fallback is published even for a stray selector.
	(void) Codec_RCC_GetAHBPrescalerDivider(pClockTreeConfig->bus.AHB, &divider);
	return (_RCC_GetSystemClockFrequency(pClockTreeConfig) / divider);
}

/**
 * @brief Returns the target APB1 frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target APB1 frequency.
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetAPB1ClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	uint32_t divider = 1UL;

	//! Codec divider resolution cannot fail; a `1UL` fallback is published even for a stray selector.
	(void) Codec_RCC_GetAPBPrescalerDivider(pClockTreeConfig->bus.APB1, &divider);
	return (_RCC_GetAHBClockFrequency(pClockTreeConfig) / divider);
}

/**
 * @brief Returns the target APB2 frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target APB2 frequency.
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetAPB2ClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	uint32_t divider = 1UL;

	//! Codec divider resolution cannot fail; a `1UL` fallback is published even for a stray selector.
	(void) Codec_RCC_GetAPBPrescalerDivider(pClockTreeConfig->bus.APB2, &divider);
	return (_RCC_GetAHBClockFrequency(pClockTreeConfig) / divider);
}

/**
 * @brief Returns the target ADC frequency described by the supplied clock tree configuration.
 * @param[in] pClockTreeConfig Pointer to the clock tree configuration.
 * @returns The target ADC frequency.
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetADCClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	uint32_t divider = 2UL;

	//! Codec divider resolution cannot fail; a `2UL` fallback is published even for a stray selector.
	(void) Codec_RCC_GetADCPrescalerDivider(pClockTreeConfig->component.ADC, &divider);
	return (_RCC_GetAPB2ClockFrequency(pClockTreeConfig) / divider);
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
	uint32_t llField = 0x00UL;

	if (pClockTreeConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! A failed Codec encode means the selector has no hardware field; surface it as invalid input.
	if (Codec_RCC_EncodePLLSource(pClockTreeConfig->system.pll.source, &llField) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (Codec_RCC_EncodePLLMultiplier(pClockTreeConfig->system.pll.multiplication_factor, &llField) != DRIVER_STATUS_SUCCESS)
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
		if (Codec_RCC_EncodePLLHSEDivider(pClockTreeConfig->system.pll.source_prescaler, &llField) != DRIVER_STATUS_SUCCESS)
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
	uint32_t llField = 0x00UL;

	if (pRCCConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	pClockTreeConfig = &(pRCCConfig->clock_tree);

	//! Every failed Codec encode below means the selector has no hardware field; surface it as invalid input.
	if (Codec_RCC_EncodeSystemClockSource(pClockTreeConfig->system.clk_src, &llField) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (Codec_RCC_EncodeAHBPrescaler(pClockTreeConfig->bus.AHB, &llField) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (Codec_RCC_EncodeAPB1Prescaler(pClockTreeConfig->bus.APB1, &llField) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (Codec_RCC_EncodeAPB2Prescaler(pClockTreeConfig->bus.APB2, &llField) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (Codec_RCC_EncodeADCPrescaler(pClockTreeConfig->component.ADC, &llField) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (Codec_RCC_EncodeUSBPrescaler(pClockTreeConfig->component.USB, &llField) != DRIVER_STATUS_SUCCESS)
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

	//! Reject the whole request before any LL write if any single selector fails to encode.
	if
	(
		(Codec_RCC_EncodeAHBPrescaler(pBusConfig->AHB, &ahbPrescalerField) != DRIVER_STATUS_SUCCESS)		||
		(Codec_RCC_EncodeAPB1Prescaler(pBusConfig->APB1, &apb1PrescalerField) != DRIVER_STATUS_SUCCESS)	||
		(Codec_RCC_EncodeAPB2Prescaler(pBusConfig->APB2, &apb2PrescalerField) != DRIVER_STATUS_SUCCESS)
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

	//! Reject the whole request before any LL write if either selector fails to encode.
	if
	(
		(Codec_RCC_EncodeADCPrescaler(pComponentConfig->ADC, &adcPrescalerField) != DRIVER_STATUS_SUCCESS) ||
		(Codec_RCC_EncodeUSBPrescaler(pComponentConfig->USB, &usbPrescalerField) != DRIVER_STATUS_SUCCESS)
	)
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

	{
		rcc_component_prescaler_t	adcSelector = RCC_ADC_DIV_2;
		uint32_t					adcDivider = 2UL;

		//! Decode/resolve failures cannot occur here; both Codec calls always publish a safe default.
		(void) Codec_RCC_DecodeADCPrescaler(adcPrescaler, &adcSelector);
		(void) Codec_RCC_GetADCPrescalerDivider(adcSelector, &adcDivider);
		pClockFrequencies->adcclk = (pClockFrequencies->pclk2 / adcDivider);
	}

	if (systemClockSource != RCC_SYS_CLK_PLL)
	{
		pClockFrequencies->usbclk = RCC_FREQ_ZERO;
		return DRIVER_STATUS_SUCCESS;
	}

	if (RCC_LL_GetUSBPrescaler(&usbPrescaler) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR;
	}

	{
		rcc_component_prescaler_t usbSelector = RCC_USB_DIV_1_5;

		//! Decode failure cannot occur here; the Codec call always publishes a safe default.
		(void) Codec_RCC_DecodeUSBPrescaler(usbPrescaler, &usbSelector);

		if (usbSelector == RCC_USB_DIV_1)
		{
			pClockFrequencies->usbclk = pClockFrequencies->sysclk;
		}
		else
		{
			pClockFrequencies->usbclk = ((pClockFrequencies->sysclk << 1) / 3U);
		}
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
		//! Encode both PLL fields before any LL write so an invalid selector never leaves a partial commit.
		if
		(
			(Codec_RCC_EncodePLLSource(pClockTreeConfig->system.pll.source, &pllSource) != DRIVER_STATUS_SUCCESS) ||
			(Codec_RCC_EncodePLLMultiplier(pClockTreeConfig->system.pll.multiplication_factor, &pllMultiplier) != DRIVER_STATUS_SUCCESS)
		)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		ASSERT_DRIVER_STATUS(RCC_LL_SetPLLSource(pllSource));

		if (pClockTreeConfig->system.pll.source == RCC_PLL_SRC_HSE)
		{
			if (Codec_RCC_EncodePLLHSEDivider(pClockTreeConfig->system.pll.source_prescaler, &pllDivider) != DRIVER_STATUS_SUCCESS)
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
	uint32_t			status = RCC_CFGR_SWS_HSI;
	rcc_system_clock_t	source = RCC_SYS_CLK_HSI;

	if (RCC_LL_GetSystemClockStatus(&status) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_SYS_CLK_HSI;
	}

	//! Decode failure cannot occur here; the Codec call always publishes a safe default.
	(void) Codec_RCC_DecodeSystemClockSource(status, &source);
	return source;
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
	uint32_t				ahbPrescaler = RCC_CFGR_HPRE_DIV1;
	uint32_t				apb1Prescaler = RCC_CFGR_PPRE1_DIV1;
	uint32_t				apb2Prescaler = RCC_CFGR_PPRE2_DIV1;
	rcc_bus_prescaler_t		selector = RCC_AHB_DIV_1;

	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			if (RCC_LL_GetAHBPrescaler(&ahbPrescaler) != DRIVER_STATUS_SUCCESS)
			{
				return RCC_AHB_DIV_1;
			}
			//! Decode failure cannot occur here; the Codec call always publishes a safe default.
			(void) Codec_RCC_DecodeAHBPrescaler(ahbPrescaler, &selector);
			return selector;
		}
		case RCC_APB1_BUS:
		{
			if (RCC_LL_GetAPB1Prescaler(&apb1Prescaler) != DRIVER_STATUS_SUCCESS)
			{
				return RCC_APB1_DIV_1;
			}
			(void) Codec_RCC_DecodeAPB1Prescaler(apb1Prescaler, &selector);
			return selector;
		}
		case RCC_APB2_BUS:
		{
			if (RCC_LL_GetAPB2Prescaler(&apb2Prescaler) != DRIVER_STATUS_SUCCESS)
			{
				return RCC_APB2_DIV_1;
			}
			(void) Codec_RCC_DecodeAPB2Prescaler(apb2Prescaler, &selector);
			return selector;
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
