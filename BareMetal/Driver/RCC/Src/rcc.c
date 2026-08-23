/**
 * @file	rcc.c
 * @author	Shrey Shah
 * @brief	Implements RCC policy, sequencing, and derived clock state
 * @version	v5.0
 * @date	23-08-2026
 *
 * @details
 * @section RCC_C_HIERARCHY Hierarchy
 * This Layer 3 implementation consumes pure Codec transformations and Layer 1
 * LL access while serving the public operations declared by `rcc.h`.
 *
 * @section RCC_C_RESPONSIBILITY Responsibility
 * The source validates complete requests before mutation, orders Flash and
 * clock-tree transitions, polls bounded ready/switch states, and maintains the
 * derived-frequency cache.
 *
 * @section RCC_C_BOUNDARY Dependency Boundary
 * Public selector vocabulary remains in `rcc_defines.h`, configuration
 * structures remain in `rcc_config.h`, raw field translation remains in
 * Codec, and mechanical register access remains in LL.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "rcc.h"
#include "rcc_codec.h"
#include "rcc_ll.h"
#include "stm32f1xx_flash.h"
#include "stm32f1xx_defines.h"
#include "stm32f1xx_base_address.h"

// ==================================================================================================== //
// Macros
// ==================================================================================================== //
/** @brief Timeout used while validating switch clock @def RCC_READY_TIMEOUT */
#define RCC_READY_TIMEOUT		((uint32_t) 1000UL)

// ==================================================================================================== //
// Typedefs
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
// Local Helpers
// ==================================================================================================== //

/**
 * @brief Waits until one clock source reports the requested ready state
 * @param[in] pReadyGetter Clock-source status getter used for polling
 * Accepted values:
 * - Non-`NULL`: HSI, HSE, or PLL ready-state getter
 * @param[in] targetStatus Ready state expected from @p pReadyGetter
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Wait until the source is not ready
 * - @ref `DRIVER_STATUS_READY`: Wait until the source is ready
 * @returns @ref driver_status_t "Clock-source wait status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The source reached the requested status before timeout
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: The ready getter callback is NULL
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: The requested status was not reached within the timeout window
 */
static driver_status_t _RCC_WaitForClockSourceReady
(
	_rcc_ready_status_getter_t const	pReadyGetter,
	const driver_status_t				targetStatus
)
{
	volatile uint32_t timeout = RCC_READY_TIMEOUT;

	//! Reject a missing callback before entering the bounded polling loop.
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
 * @brief Waits until hardware confirms the requested active SYSCLK source
 * @param[in] source Requested system clock source
 * Accepted values:
 * - @ref `RCC_SYS_CLK_HSI`
 * - @ref `RCC_SYS_CLK_HSE`
 * - @ref `RCC_SYS_CLK_PLL`
 * @returns @ref driver_status_t "System-clock switch wait status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The requested source became the active system clock
 * @retval - @ref `DRIVER_STATUS_ERROR`: Reading the system clock status failed
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: The requested source did not become active before timeout
 */
static driver_status_t _RCC_WaitForSystemClockSwitch(const rcc_system_clock_t source)
{
	reg			status = RCC_CFGR_SWS_HSI;
	volatile uint32_t	timeout = RCC_READY_TIMEOUT;

	//! Poll the read-only SWS field until hardware confirms the requested SYSCLK mux input.
	while (timeout > 0x00UL)
	{
		if (LL_RCC_GetSystemClockStatus(&status) != DRIVER_STATUS_SUCCESS)
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
 * @brief Returns the effective divider currently programmed for one bus
 * @param[in] bus Target bus selector
 * Accepted values:
 * - @ref `RCC_AHB_BUS`: Read and decode the AHB prescaler
 * - @ref `RCC_APB1_BUS`: Read and decode the APB1 prescaler
 * - @ref `RCC_APB2_BUS`: Read and decode the APB2 prescaler
 * @returns Effective numeric divider for the selected bus
 * @retval - `1UL`: Hardware access failed, @p bus was invalid, or divide-by-one is configured
 * @retval - `2UL..512UL`: Effective divider represented by the observed prescaler field
 */
static uint32_t _RCC_GetBusPrescalerDivider(const rcc_bus_t bus)
{
	reg				ahbPrescalerField = RCC_CFGR_HPRE_DIV1;
	reg				apb1PrescalerField = RCC_CFGR_PPRE1_DIV1;
	reg				apb2PrescalerField = RCC_CFGR_PPRE2_DIV1;
	rcc_bus_prescaler_t		prescalerSelector = RCC_AHB_DIV_1;
	uint32_t				divider = 1UL;

	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			if (LL_RCC_GetAHBPrescaler(&ahbPrescalerField) != DRIVER_STATUS_SUCCESS)
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
			if (LL_RCC_GetAPB1Prescaler(&apb1PrescalerField) != DRIVER_STATUS_SUCCESS)
			{
				return 1UL;
			}

			(void) Codec_RCC_DecodeAPB1Prescaler(apb1PrescalerField, &prescalerSelector);
			(void) Codec_RCC_GetAPBPrescalerDivider(prescalerSelector, &divider);
			return divider;
		}
		case RCC_APB2_BUS:
		{
			if (LL_RCC_GetAPB2Prescaler(&apb2PrescalerField) != DRIVER_STATUS_SUCCESS)
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
 * @brief Returns the PLL input frequency described by one clock-tree configuration
 * @param[in] pClockTreeConfig Clock-tree configuration to evaluate
 * Expected values:
 * - Non-`NULL`: Previously validated clock-tree configuration
 * @returns Requested PLL input frequency in hertz
 * @retval - `RCC_HSI_FREQ / 2U`: HSI fixed-divider path
 * @retval - `RCC_HSE_FREQ / 2U`: HSE divide-by-two path
 * @retval - `RCC_HSE_FREQ`: HSE direct path
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetPLLInputClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	//! Apply the fixed HSI divide-by-two path before considering the programmable HSE divider.
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
 * @brief Returns the SYSCLK frequency described by one clock-tree configuration
 * @param[in] pClockTreeConfig Clock-tree configuration to evaluate
 * Expected values:
 * - Non-`NULL`: Previously validated clock-tree configuration
 * @returns Requested SYSCLK frequency in hertz
 * @retval - @ref `RCC_FREQ_ZERO`: System-clock source is invalid
 * @retval - `1UL..RCC_SYSCLK_MAX_FREQ`: Frequency represented by the requested source path
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetSystemClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	//! Resolve the requested semantic source without observing or mutating live hardware.
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
			return
			(
				_RCC_GetPLLInputClockFrequency(pClockTreeConfig) *
				(frequency_t) pClockTreeConfig->system.pll.multiplication_factor
			);
		}
		default:
		{
			return RCC_FREQ_ZERO;
		}
	}
}

/**
 * @brief Returns the HCLK frequency described by one clock-tree configuration
 * @param[in] pClockTreeConfig Clock-tree configuration to evaluate
 * Expected values:
 * - Non-`NULL`: Previously validated clock-tree configuration
 * @returns Requested HCLK frequency in hertz after AHB division
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetAHBClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	uint32_t divider = 1UL;

	//! Codec divider resolution cannot fail; a `1UL` fallback is published even for a stray selector.
	(void) Codec_RCC_GetAHBPrescalerDivider(pClockTreeConfig->bus.AHB, &divider);
	return (_RCC_GetSystemClockFrequency(pClockTreeConfig) / divider);
}

/**
 * @brief Returns the PCLK1 frequency described by one clock-tree configuration
 * @param[in] pClockTreeConfig Clock-tree configuration to evaluate
 * Expected values:
 * - Non-`NULL`: Previously validated clock-tree configuration
 * @returns Requested PCLK1 frequency in hertz after AHB and APB1 division
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetAPB1ClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	uint32_t divider = 1UL;

	//! Codec divider resolution cannot fail; a `1UL` fallback is published even for a stray selector.
	(void) Codec_RCC_GetAPBPrescalerDivider(pClockTreeConfig->bus.APB1, &divider);
	return (_RCC_GetAHBClockFrequency(pClockTreeConfig) / divider);
}

/**
 * @brief Returns the PCLK2 frequency described by one clock-tree configuration
 * @param[in] pClockTreeConfig Clock-tree configuration to evaluate
 * Expected values:
 * - Non-`NULL`: Previously validated clock-tree configuration
 * @returns Requested PCLK2 frequency in hertz after AHB and APB2 division
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetAPB2ClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	uint32_t divider = 1UL;

	//! Codec divider resolution cannot fail; a `1UL` fallback is published even for a stray selector.
	(void) Codec_RCC_GetAPBPrescalerDivider(pClockTreeConfig->bus.APB2, &divider);
	return (_RCC_GetAHBClockFrequency(pClockTreeConfig) / divider);
}

/**
 * @brief Returns the ADC frequency described by one clock-tree configuration
 * @param[in] pClockTreeConfig Clock-tree configuration to evaluate
 * Expected values:
 * - Non-`NULL`: Previously validated clock-tree configuration
 * @returns Requested ADC frequency in hertz after PCLK2 and ADC division
 */
__STATIC_FORCEINLINE frequency_t _RCC_GetADCClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	uint32_t divider = 2UL;

	//! Codec divider resolution cannot fail; a `2UL` fallback is published even for a stray selector.
	(void) Codec_RCC_GetADCPrescalerDivider(pClockTreeConfig->component.ADC, &divider);
	return (_RCC_GetAPB2ClockFrequency(pClockTreeConfig) / divider);
}

/**
 * @brief Returns the USB frequency described by one clock-tree configuration
 * @param[in] pClockTreeConfig Clock-tree configuration to evaluate
 * Expected values:
 * - Non-`NULL`: Previously validated clock-tree configuration
 * @returns Requested USB frequency in hertz
 * @retval - @ref `RCC_FREQ_ZERO`: PLL is not the requested SYSCLK source
 * @retval - `1UL..RCC_SYSCLK_MAX_FREQ`: PLL-derived USB frequency
 */
static frequency_t _RCC_GetUSBClockFrequency(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	const frequency_t pllClock =
	(
		_RCC_GetPLLInputClockFrequency(pClockTreeConfig) *
		(frequency_t) pClockTreeConfig->system.pll.multiplication_factor
	);

	//! Publish zero when the requested tree does not make the PLL-derived USB clock available.
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
 * @brief Computes every frequency derived from one validated clock-tree request
 * @param[in] pClockTreeConfig Clock-tree configuration to evaluate
 * Expected values:
 * - Non-`NULL`: Previously validated clock-tree configuration
 * @param[out] pClockFrequencies Destination for the calculated clock snapshot
 * Expected values:
 * - Non-`NULL`: Snapshot is published after both pointers are validated
 * @returns @ref driver_status_t "Configuration-derived frequency status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The snapshot was loaded successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: Either input pointer is `NULL`
 */
static driver_status_t _RCC_LoadClockFrequenciesFromConfig
(
	const rcc_clock_tree_config_t* const	pClockTreeConfig,
	rcc_clock_frequencies_t* const			pClockFrequencies
)
{
	//! Validate both objects before publishing any member of the destination snapshot.
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
 * @brief Validates PLL-specific selections inside one clock-tree configuration
 * @param[in] pClockTreeConfig Clock-tree configuration to validate
 * Expected values:
 * - Non-`NULL`: Complete system-clock configuration domain
 * @returns @ref driver_status_t "PLL-configuration validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The PLL configuration is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more PLL selections are invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockTreeConfig is `NULL`
 */
static driver_status_t _RCC_ValidatePLLConfig(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	reg llField = 0x00UL;

	if (pClockTreeConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! A failed Codec encode means the selector has no hardware field; surface it as invalid input.
	if (Codec_RCC_EncodePLLSource(pClockTreeConfig->system.pll.source, &llField) != DRIVER_STATUS_SUCCESS)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if
	(
		Codec_RCC_EncodePLLMultiplier
		(
			pClockTreeConfig->system.pll.multiplication_factor,
			&llField
		) != DRIVER_STATUS_SUCCESS
	)
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
 * @brief Validates one Flash configuration domain
 * @param[in] pFlashConfig Flash configuration to validate
 * Expected values:
 * - Non-`NULL`: Complete Flash latency and prefetch policy
 * @returns @ref driver_status_t "Flash-configuration validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Both Flash selectors are supported
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFlashConfig is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A Flash selector is unsupported
 */
static driver_status_t _RCC_ValidateFlashConfig(const rcc_flash_config_t* const pFlashConfig)
{
	//! Validate the complete Flash domain before any caller performs an ACR mutation.
	if (pFlashConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	if
	(
		(pFlashConfig->latency != RCC_FLASH_LATENCY_0) &&
		(pFlashConfig->latency != RCC_FLASH_LATENCY_1) &&
		(pFlashConfig->latency != RCC_FLASH_LATENCY_2)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if
	(
		(pFlashConfig->prefetch != RCC_FLASH_PREFETCH_DISABLE) &&
		(pFlashConfig->prefetch != RCC_FLASH_PREFETCH_ENABLE)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates every selector in one clock-tree configuration domain
 * @param[in] pClockTreeConfig Clock-tree configuration to validate
 * Expected values:
 * - Non-`NULL`: Complete system, bus, and component configuration
 * @returns @ref driver_status_t "Clock-tree configuration validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every clock-tree selector is supported
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockTreeConfig is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A selector or PLL combination is unsupported
 */
static driver_status_t _RCC_ValidateClockTreeConfig(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	reg llField = 0x00UL;

	//! Reject the missing domain before invoking any pure selector encoder.
	if (pClockTreeConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

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

	if (pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL)
	{
		ASSERT_DRIVER_STATUS(_RCC_ValidatePLLConfig(pClockTreeConfig));
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Stores one complete clock-frequency snapshot in the Driver cache
 * @param[in] pClockFrequencies Clock-frequency snapshot to publish
 * Expected values:
 * - Non-`NULL`: Coherent snapshot whose members were derived together
 * @returns Nothing
 */
__STATIC_FORCEINLINE void _RCC_UpdateClockFrequenciesCache(const rcc_clock_frequencies_t* const pClockFrequencies)
{
	//! Treat a missing snapshot as a no-op because this internal cache publisher has a void contract.
	if (pClockFrequencies == NULL)
	{
		return;
	}

	_rccClockFrequenciesSnapshot = *pClockFrequencies;
}

/**
 * @brief Builds a derived-frequency snapshot from current RCC hardware state
 * @param[out] pClockFrequencies Destination for the hardware-derived snapshot
 * Expected values:
 * - Non-`NULL`: Snapshot is published as fields are successfully derived
 * @returns @ref driver_status_t "Hardware-derived frequency status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The snapshot was built successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockFrequencies was a null pointer
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read while building the snapshot
 */
static driver_status_t _RCC_LoadClockFrequenciesFromHardware(rcc_clock_frequencies_t* const pClockFrequencies);

/**
 * @brief Refreshes the Driver clock-frequency cache from current hardware state
 * @returns @ref driver_status_t "Clock-frequency cache refresh status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The cache snapshot was refreshed successfully
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware status could not be read while rebuilding the snapshot
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

	//! Publish the rebuilt snapshot only after every hardware-derived member is available.
	ASSERT_DRIVER_STATUS(_RCC_LoadClockFrequenciesFromHardware(&clockFrequencies));
	_RCC_UpdateClockFrequenciesCache(&clockFrequencies);
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Applies one validated bus-prescaler domain without refreshing the public cache
 * @details Encodes every selector before the first LL write.
 * @param[in] pBusConfig Bus-prescaler configuration to apply
 * Expected values:
 * - Non-`NULL`: Complete AHB, APB1, and APB2 prescaler policy
 * @returns @ref driver_status_t "Bus-prescaler apply status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Bus prescaler fields were programmed successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pBusConfig was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more bus prescaler selectors were invalid
 */
static driver_status_t _RCC_ApplyBusPrescalerConfig(const rcc_bus_config_t* const pBusConfig)
{
	reg ahbPrescalerField = 0x00UL;
	reg apb1PrescalerField = 0x00UL;
	reg apb2PrescalerField = 0x00UL;

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

	ASSERT_DRIVER_STATUS(LL_RCC_SetAHBPrescaler(ahbPrescalerField));
	ASSERT_DRIVER_STATUS(LL_RCC_SetAPB1Prescaler(apb1PrescalerField));
	ASSERT_DRIVER_STATUS(LL_RCC_SetAPB2Prescaler(apb2PrescalerField));
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Applies one validated component-prescaler domain without refreshing the public cache
 * @details Encodes both selectors before the first LL write.
 * @param[in] pComponentConfig Component-prescaler configuration to apply
 * Expected values:
 * - Non-`NULL`: Complete ADC and USB prescaler policy
 * @returns @ref driver_status_t "Component-prescaler apply status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Component prescaler fields were programmed successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pComponentConfig was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more component prescaler selectors were invalid
 */
static driver_status_t _RCC_ApplyComponentPrescalerConfig(const rcc_component_config_t* const pComponentConfig)
{
	reg adcPrescalerField = 0x00UL;
	reg usbPrescalerField = 0x00UL;

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

	ASSERT_DRIVER_STATUS(LL_RCC_SetADCPrescaler(adcPrescalerField));
	ASSERT_DRIVER_STATUS(LL_RCC_SetUSBPrescaler(usbPrescalerField));
	return DRIVER_STATUS_SUCCESS;
}

static driver_status_t _RCC_LoadClockFrequenciesFromHardware(rcc_clock_frequencies_t* const pClockFrequencies)
{
	rcc_system_clock_t systemClockSource = RCC_SYS_CLK_HSI;
	reg adcPrescaler = RCC_CFGR_ADCPRE_DIV2;
	reg usbPrescaler = RCC_CFGR_USBPRE_DIV1_5;
	frequency_t pllInputFrequency = RCC_FREQ_ZERO;

	if (pClockFrequencies == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	systemClockSource = RCC_GetSystemClockSource();

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
			//! Resolve the PLL input through explicit source branches so the fixed HSI divider remains visible.
			if (RCC_GetPLLSource() == RCC_PLL_SRC_HSE)
			{
				pllInputFrequency = RCC_HSE_FREQ;
			}
			else
			{
				pllInputFrequency = (RCC_HSI_FREQ >> 1);
			}
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

	if (LL_RCC_GetADCPrescaler(&adcPrescaler) != DRIVER_STATUS_SUCCESS)
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

	if (LL_RCC_GetUSBPrescaler(&usbPrescaler) != DRIVER_STATUS_SUCCESS)
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
 * @brief Validates every derived clock against its device frequency ceiling
 * @param[in] pClockFreqSnapshot Derived frequency snapshot to validate
 * Expected values:
 * - Non-`NULL`: Fully calculated frequency snapshot
 * @returns @ref driver_status_t "Clock-frequency limit validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: All derived frequencies are within device limits
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: The snapshot pointer is NULL
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more derived frequencies exceed the supported limits
 */
static driver_status_t _RCC_ValidateClockFrequencies(const rcc_clock_frequencies_t* const pClockFreqSnapshot)
{
	//! Reject the missing snapshot before checking the device-specific frequency ceilings.
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
 * @brief Validates cross-domain frequency and Flash dependencies
 * @param[in] pRCCConfig Root RCC configuration to validate
 * Expected values:
 * - Non-`NULL`: Complete configuration descriptor
 * @param[in] pClockFreqSnapshot Frequencies derived from @p pRCCConfig
 * Expected values:
 * - Non-`NULL`: Complete frequency snapshot for the same request
 * @returns @ref driver_status_t "Clock-configuration dependency validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: All inter-parameter dependencies are satisfied
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: One or more input pointers are NULL
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more dependent configuration constraints are violated
 */
static driver_status_t _RCC_ValidateClockConfigDependencies
(
	const rcc_config_t* const			pRCCConfig,
	const rcc_clock_frequencies_t* const	pClockFreqSnapshot
)
{
	const rcc_clock_tree_config_t* pClockTreeConfig = NULL;

	//! Validate both immutable inputs before checking cross-domain USB and Flash constraints.
	if ((pRCCConfig == NULL) || (pClockFreqSnapshot == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	pClockTreeConfig = &(pRCCConfig->clock_tree);

	if
	(
		(pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL)		&&
		(pClockFreqSnapshot->usbclk != RCC_FREQ_ZERO)			&&
		(pClockFreqSnapshot->usbclk != RCC_USBCLK_TARGET_FREQ)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if ((pClockFreqSnapshot->sysclk <= RCC_FLASH_LATENCY_0_MAX_FREQ) && (pRCCConfig->flash.latency != RCC_FLASH_LATENCY_0))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if
	(
		(pClockFreqSnapshot->sysclk > RCC_FLASH_LATENCY_0_MAX_FREQ)	&&
		(pClockFreqSnapshot->sysclk <= RCC_FLASH_LATENCY_1_MAX_FREQ)	&&
		(pRCCConfig->flash.latency != RCC_FLASH_LATENCY_1)
	)
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
// RCC Driver Clock Gate and Reset APIs
// ==================================================================================================== //

driver_status_t RCC_GetPeripheralClockState(const rcc_bus_t bus, const reg clockMask)
{
	reg regImage = 0x00000000UL;

	//! Reject an unsupported register bank or empty mask before any volatile read.
	if ((RCC_IS_BUS_VALID(bus) == 0x00U) || (LL_RCC_IS_MASK_VALID(clockMask) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Route the semantic bus selector to exactly one clock-enable register image.
	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			regImage = LL_RCC_ReadAHBENR();
			break;
		}
		case RCC_APB1_BUS:
		{
			regImage = LL_RCC_ReadAPB1ENR();
			break;
		}
		case RCC_APB2_BUS:
		{
			regImage = LL_RCC_ReadAPB2ENR();
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	//! Report ON only when every gate selected by the caller is enabled.
	if ((regImage & clockMask) == clockMask)
	{
		return DRIVER_STATUS_ON;
	}
	else
	{
		return DRIVER_STATUS_OFF;
	}
}

driver_status_t RCC_SetPeripheralClockState
(
	const rcc_bus_t			bus,
	const reg				clockMask,
	const driver_status_t	clockState
)
{
	//! Validate the complete request before selecting a register-specific LL mutation.
	if ((RCC_IS_BUS_VALID(bus) == 0x00U) || (LL_RCC_IS_MASK_VALID(clockMask) == 0x00U) || ((clockState != DRIVER_STATUS_OFF) && (clockState != DRIVER_STATUS_ON)))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Preserve register ownership in LL while collapsing repeated Driver intent.
	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			if (clockState == DRIVER_STATUS_ON)
			{
				return LL_RCC_EnableAHBClock(clockMask);
			}
			else
			{
				return LL_RCC_DisableAHBClock(clockMask);
			}
		}
		case RCC_APB1_BUS:
		{
			if (clockState == DRIVER_STATUS_ON)
			{
				return LL_RCC_EnableAPB1Clock(clockMask);
			}
			else
			{
				return LL_RCC_DisableAPB1Clock(clockMask);
			}
		}
		case RCC_APB2_BUS:
		{
			if (clockState == DRIVER_STATUS_ON)
			{
				return LL_RCC_EnableAPB2Clock(clockMask);
			}
			else
			{
				return LL_RCC_DisableAPB2Clock(clockMask);
			}
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}
}

driver_status_t RCC_PulsePeripheralReset(const rcc_bus_t bus, const reg resetMask)
{
	//! Reject AHB, unsupported selectors, and empty reset masks before the action transaction.
	if ((RCC_IS_RESET_BUS_VALID(bus) == 0x00U) || (LL_RCC_IS_MASK_VALID(resetMask) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Route the pulse to the only APB reset register selected by the validated bus.
	if (bus == RCC_APB1_BUS)
	{
		return LL_RCC_PulseAPB1Reset(resetMask);
	}
	else
	{
		return LL_RCC_PulseAPB2Reset(resetMask);
	}
}

// ==================================================================================================== //
// RCC Driver Configuration APIs
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

	//! Reject the root descriptor before deriving nested pointers or calculated frequencies.
	if (pRCCConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	pClockTreeConfig = &(pRCCConfig->clock_tree);
	ASSERT_DRIVER_STATUS(_RCC_ValidateFlashConfig(&(pRCCConfig->flash)));
	ASSERT_DRIVER_STATUS(_RCC_ValidateClockTreeConfig(pClockTreeConfig));
	ASSERT_DRIVER_STATUS(_RCC_LoadClockFrequenciesFromConfig(pClockTreeConfig, &clockFreqSnapshot));
	ASSERT_DRIVER_STATUS(_RCC_ValidateClockFrequencies(&clockFreqSnapshot));
	ASSERT_DRIVER_STATUS(_RCC_ValidateClockConfigDependencies(pRCCConfig, &clockFreqSnapshot));
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigFlash(const rcc_flash_config_t* const pFlashConfig)
{
	FLASH_TypeDef* const pFlash = (FLASH_TypeDef*) FLASH_BASE_ADDR;
	reg flashLatency = FLASH_ACR_LATENCY_0;

	//! Validate the complete Flash policy before translating or mutating `FLASH_ACR`.
	ASSERT_DRIVER_STATUS(_RCC_ValidateFlashConfig(pFlashConfig));

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

	REGOPS_MODIFY(&(pFlash->ACR.REG), FLASH_ACR_LATENCY_Msk, flashLatency);

	if (pFlashConfig->prefetch == RCC_FLASH_PREFETCH_ENABLE)
	{
		REGOPS_SET(&(pFlash->ACR.REG), FLASH_ACR_PRFTBE);
	}
	else if (pFlashConfig->prefetch == RCC_FLASH_PREFETCH_DISABLE)
	{
		REGOPS_CLEAR(&(pFlash->ACR.REG), FLASH_ACR_PRFTBE);
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigBusPrescalers(const rcc_bus_config_t* const pBusConfig)
{
	//! Rebuild the public frequency cache only after all three bus fields commit successfully.
	ASSERT_DRIVER_STATUS(_RCC_ApplyBusPrescalerConfig(pBusConfig));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesCache());
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigComponentPrescalers(const rcc_component_config_t* const pComponentConfig)
{
	//! Rebuild the public frequency cache only after both component fields commit successfully.
	ASSERT_DRIVER_STATUS(_RCC_ApplyComponentPrescalerConfig(pComponentConfig));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesCache());
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_SetSystemClockSource(const rcc_system_clock_t source)
{
	//! Dispatch to the exact per-source enable/ready/switch sequence formerly split across three functions.
	switch (source)
	{
		case RCC_SYS_CLK_HSI:
		{
			LL_RCC_EnableHSI();
			ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReady(LL_RCC_GetHSIReadyStatus, DRIVER_STATUS_READY));
			ASSERT_DRIVER_STATUS(LL_RCC_SetSystemClockSource(RCC_CFGR_SW_HSI));
			break;
		}
		case RCC_SYS_CLK_HSE:
		{
			LL_RCC_EnableHSE();
			ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReady(LL_RCC_GetHSEReadyStatus, DRIVER_STATUS_READY));
			ASSERT_DRIVER_STATUS(LL_RCC_SetSystemClockSource(RCC_CFGR_SW_HSE));
			break;
		}
		case RCC_SYS_CLK_PLL:
		{
			//! PLL selection never enables the PLL itself; the caller must have already configured and started it.
			if (LL_RCC_GetPLLReadyStatus() != DRIVER_STATUS_READY)
			{
				return DRIVER_STATUS_ERROR_STATE;
			}

			ASSERT_DRIVER_STATUS(LL_RCC_SetSystemClockSource(RCC_CFGR_SW_PLL));
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	ASSERT_DRIVER_STATUS(_RCC_WaitForSystemClockSwitch(source));
	ASSERT_DRIVER_STATUS(_RCC_RefreshClockFrequenciesCache());
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_ConfigClockTree(const rcc_clock_tree_config_t* const pClockTreeConfig)
{
	rcc_system_clock_t activeSource = RCC_SYS_CLK_HSI;
	reg pllSource = 0x00UL;
	reg pllDivider = 0x00UL;
	reg pllMultiplier = 0x00UL;

	//! Complete every pure selector check before enabling, disabling, or switching a clock source.
	ASSERT_DRIVER_STATUS(_RCC_ValidateClockTreeConfig(pClockTreeConfig));

	activeSource = RCC_GetSystemClockSource();
	LL_RCC_EnableHSI();
	ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReady(LL_RCC_GetHSIReadyStatus, DRIVER_STATUS_READY));

	if (activeSource == RCC_SYS_CLK_PLL)
	{
		ASSERT_DRIVER_STATUS(RCC_SetSystemClockSource(RCC_SYS_CLK_HSI));
		activeSource = RCC_SYS_CLK_HSI;
	}

	if ((pClockTreeConfig->system.clk_src == RCC_SYS_CLK_HSE) ||
		((pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL) && (pClockTreeConfig->system.pll.source == RCC_PLL_SRC_HSE)))
	{
		LL_RCC_EnableHSE();
		ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReady(LL_RCC_GetHSEReadyStatus, DRIVER_STATUS_READY));
	}

	if (LL_RCC_GetPLLReadyStatus() == DRIVER_STATUS_READY)
	{
		LL_RCC_DisablePLL();
		ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReady(LL_RCC_GetPLLReadyStatus, DRIVER_STATUS_OFF));
	}

	ASSERT_DRIVER_STATUS(_RCC_ApplyBusPrescalerConfig(&pClockTreeConfig->bus));
	ASSERT_DRIVER_STATUS(_RCC_ApplyComponentPrescalerConfig(&pClockTreeConfig->component));

	if (pClockTreeConfig->system.clk_src == RCC_SYS_CLK_PLL)
	{
		//! Encode both PLL fields before any LL write so an invalid selector never leaves a partial commit.
		if
		(
			(Codec_RCC_EncodePLLSource(pClockTreeConfig->system.pll.source, &pllSource) != DRIVER_STATUS_SUCCESS) ||
			(
				Codec_RCC_EncodePLLMultiplier
				(
					pClockTreeConfig->system.pll.multiplication_factor,
					&pllMultiplier
				) != DRIVER_STATUS_SUCCESS
			)
		)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}

		ASSERT_DRIVER_STATUS(LL_RCC_SetPLLSource(pllSource));

		if (pClockTreeConfig->system.pll.source == RCC_PLL_SRC_HSE)
		{
			if
			(
				Codec_RCC_EncodePLLHSEDivider
				(
					pClockTreeConfig->system.pll.source_prescaler,
					&pllDivider
				) != DRIVER_STATUS_SUCCESS
			)
			{
				return DRIVER_STATUS_ERROR_INVALID_ARG;
			}

			ASSERT_DRIVER_STATUS(LL_RCC_SetPLLHSEDivider(pllDivider));
		}

		ASSERT_DRIVER_STATUS(LL_RCC_SetPLLMultiplier(pllMultiplier));
		LL_RCC_EnablePLL();
		ASSERT_DRIVER_STATUS(_RCC_WaitForClockSourceReady(LL_RCC_GetPLLReadyStatus, DRIVER_STATUS_READY));
	}

	switch (pClockTreeConfig->system.clk_src)
	{
		case RCC_SYS_CLK_HSI:
		{
			if (activeSource != RCC_SYS_CLK_HSI)
			{
				ASSERT_DRIVER_STATUS(RCC_SetSystemClockSource(RCC_SYS_CLK_HSI));
			}
			break;
		}
		case RCC_SYS_CLK_HSE:
		{
			if (activeSource != RCC_SYS_CLK_HSE)
			{
				ASSERT_DRIVER_STATUS(RCC_SetSystemClockSource(RCC_SYS_CLK_HSE));
			}
			break;
		}
		case RCC_SYS_CLK_PLL:
		{
			ASSERT_DRIVER_STATUS(RCC_SetSystemClockSource(RCC_SYS_CLK_PLL));
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

	//! Validate and calculate the complete target before choosing the safe Flash/clock commit order.
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

driver_status_t RCC_Load72MHzDefaultConfig(rcc_config_t* const pRCCConfig)
{
	//! Reject a missing destination before attempting to publish the preset.
	if (pRCCConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Populate the Flash policy required before switching SYSCLK to 72 MHz.
	pRCCConfig->flash.latency = RCC_FLASH_LATENCY_2;
	pRCCConfig->flash.prefetch = RCC_FLASH_PREFETCH_ENABLE;

	//! Select the external 8 MHz oscillator and PLL multiplication required for 72 MHz SYSCLK.
	pRCCConfig->clock_tree.system.clk_src = RCC_SYS_CLK_PLL;
	pRCCConfig->clock_tree.system.pll.source = RCC_PLL_SRC_HSE;
	pRCCConfig->clock_tree.system.pll.source_prescaler = RCC_PLL_SRC_HSE_DIV_1;
	pRCCConfig->clock_tree.system.pll.multiplication_factor = RCC_PLL_MUL_9;

	//! Publish bus prescalers that keep every bus within its documented frequency limit.
	pRCCConfig->clock_tree.bus.AHB = RCC_AHB_DIV_1;
	pRCCConfig->clock_tree.bus.APB1 = RCC_APB1_DIV_2;
	pRCCConfig->clock_tree.bus.APB2 = RCC_APB2_DIV_1;

	//! Publish component prescalers for the supported 72 MHz clock-tree preset.
	pRCCConfig->clock_tree.component.ADC = RCC_ADC_DIV_6;
	pRCCConfig->clock_tree.component.USB = RCC_USB_DIV_1_5;

	//! Confirm that every member of the caller-owned configuration now contains the preset.
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RCC_Config72MHz(void)
{
	rcc_config_t cfg = {0};
	//! Reuse the public preset loader and root transaction so default setup follows the canonical path.
	ASSERT_DRIVER_STATUS(RCC_Load72MHzDefaultConfig(&cfg));
	//! Apply the validated preset through the canonical RCC configuration transaction.
	return RCC_Config(&cfg);
}

// ==================================================================================================== //
// RCC Driver Clock Observation APIs
// ==================================================================================================== //

rcc_system_clock_t RCC_GetSystemClockSource(void)
{
	reg			status = RCC_CFGR_SWS_HSI;
	rcc_system_clock_t	source = RCC_SYS_CLK_HSI;

	//! Read SWS rather than SW so the result represents the source hardware actually selected.
	if (LL_RCC_GetSystemClockStatus(&status) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_SYS_CLK_HSI;
	}

	//! Decode failure cannot occur here; the Codec call always publishes a safe default.
	(void) Codec_RCC_DecodeSystemClockSource(status, &source);
	return source;
}

rcc_pll_src_t RCC_GetPLLSource(void)
{
	reg source = RCC_CFGR_PLLSRC_HSI_DIV2;

	//! Read the raw PLLSRC field once and map its binary hardware state to Driver vocabulary.
	if (LL_RCC_GetPLLSource(&source) != DRIVER_STATUS_SUCCESS)
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
	reg divider = RCC_CFGR_PLLXTPRE_HSE;

	//! The HSI path has a fixed divide-by-two contract and does not consume PLLXTPRE.
	if (RCC_GetPLLSource() == RCC_PLL_SRC_HSI)
	{
		return RCC_PLL_SRC_HSI_DIV_2;
	}

	if (LL_RCC_GetPLLHSEDivider(&divider) != DRIVER_STATUS_SUCCESS)
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
	reg multiplier = RCC_CFGR_PLLMUL_2;

	//! Read the raw PLLMUL field once before translating it into the public multiplier selector.
	if (LL_RCC_GetPLLMultiplier(&multiplier) != DRIVER_STATUS_SUCCESS)
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
	//! Validate the destination before refreshing or publishing the shared frequency snapshot.
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

frequency_t RCC_GetCoreClockFrequency(void)
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

	//! Reuse the coherent snapshot path so SYSCLK reporting shares one cache and refresh policy.
	if (RCC_GetClockFrequencies(&clockFrequencies) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_FREQ_ZERO;
	}

	return clockFrequencies.sysclk;
}

rcc_bus_prescaler_t RCC_GetBusPrescaler(const rcc_bus_t bus)
{
	reg				ahbPrescaler = RCC_CFGR_HPRE_DIV1;
	reg				apb1Prescaler = RCC_CFGR_PPRE1_DIV1;
	reg				apb2Prescaler = RCC_CFGR_PPRE2_DIV1;
	rcc_bus_prescaler_t		selector = RCC_AHB_DIV_1;

	//! Reject non-bus selectors before reading any prescaler field.
	if (RCC_IS_BUS_VALID(bus) == 0x00U)
	{
		return selector;
	}

	switch (bus)
	{
		case RCC_AHB_BUS:
		{
			if (LL_RCC_GetAHBPrescaler(&ahbPrescaler) != DRIVER_STATUS_SUCCESS)
			{
				return RCC_AHB_DIV_1;
			}
			//! Decode failure cannot occur here; the Codec call always publishes a safe default.
			(void) Codec_RCC_DecodeAHBPrescaler(ahbPrescaler, &selector);
			return selector;
		}
		case RCC_APB1_BUS:
		{
			if (LL_RCC_GetAPB1Prescaler(&apb1Prescaler) != DRIVER_STATUS_SUCCESS)
			{
				return RCC_APB1_DIV_1;
			}
			(void) Codec_RCC_DecodeAPB1Prescaler(apb1Prescaler, &selector);
			return selector;
		}
		case RCC_APB2_BUS:
		{
			if (LL_RCC_GetAPB2Prescaler(&apb2Prescaler) != DRIVER_STATUS_SUCCESS)
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

frequency_t RCC_GetBusFrequency(const rcc_bus_t bus)
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

	//! Reject non-bus selectors before refreshing or reading the shared frequency snapshot.
	if (RCC_IS_BUS_VALID(bus) == 0x00U)
	{
		return RCC_FREQ_ZERO;
	}

	if (RCC_GetClockFrequencies(&clockFrequencies) != DRIVER_STATUS_SUCCESS)
	{
		return RCC_FREQ_ZERO;
	}

	//! Return only physical bus clocks; ADC and USB remain available through the coherent snapshot API.
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
			return RCC_FREQ_ZERO;
		}
	}
}
