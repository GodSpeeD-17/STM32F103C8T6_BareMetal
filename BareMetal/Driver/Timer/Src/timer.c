/**
 * @file	timer.c
 * @author	Shrey Shah
 * @brief	Timer Driver Implementation
 * @version	v1.0
 * @date	20-06-2026
 *
 * @details
 * @section TIM_DRIVER_IMPL_SCOPE Scope
 * This source file implements the public Timer driver API declared in
 * `timer.h`. The driver layer owns public validation, Timer clock-state
 * orchestration, register-image reads, codec staging/extraction orchestration,
 * register-specific dirty-write decisions, and public @ref driver_status_t handling.
 *
 * @section TIM_DRIVER_IMPL_FIELD_OWNERSHIP Field Ownership
 * The root configuration surface owns every base-configuration domain represented by @ref tim_config_t:
 * - `TIMx_CR1` counter behavior fields represented by @ref tim_config_counter_t
 * - `TIMx_PSC` prescaler
 * - `TIMx_ARR` auto-reload value
 * - `TIMx_CNT` counter value
 *
 * Channel/PWM, DMA, and master/slave behavior remain deferred. This driver also
 * owns Timer DIER interrupt-request sources, SR event observation/acknowledgement,
 * and the fixed @ref TIM_ConfigForBlockingDelay service bootstrap plus bounded
 * blocking @ref TIM_DelayUs / @ref TIM_BlockingDelayMs helpers. Generic
 * Clock-gate mutation and NVIC delivery remain under RCC/application and
 * NVIC/application ownership respectively. Timer configuration APIs require
 * the application to enable the matching APB1 clock gate before entry.
 *
 * @section TIM_DRIVER_IMPL_LAYOUT Source Layout
 * The public implementation follows the same banner and sub-banner order as
 * `timer.h`: clock state, operation state, root configuration, grouped
 * configuration, timebase fields, counter fields, IRQ sources/events, and
 * blocking delay helpers at the end. Local helpers are kept ahead of the public
 * functions read as orchestration over validation, codec staging, and the
 * shared `RegOps_WriteIfChanged()` dirty-write primitive.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "timer.h"
#include "timer_codec.h"
#include "timer_ll.h"
#include "rcc.h"

// ==================================================================================================== //
//										Local Driver Configuration										//
// ==================================================================================================== //

/** @brief Microsecond delay chunk used by the millisecond blocking helper @def TIM_DRIVER_BLOCKING_DELAY_MS_CHUNK_US */
#define TIM_DRIVER_BLOCKING_DELAY_MS_CHUNK_US			((uint16_t) 1000U)
/** @brief Conservative polling-loop budget per requested microsecond @def TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_PER_US */
#define TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_PER_US		((uint32_t) 1024UL)
/** @brief Fixed setup allowance added to the blocking polling-loop budget @def TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_BASE */
#define TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_BASE		((uint32_t) 1024UL)

// ==================================================================================================== //
//									Timer Clock Bus Mapping										//
// ==================================================================================================== //

/**
 * @brief Maps each supported Timer index to its RCC clock bus
 * @note Entries are indexed using the value returned by @ref TIM_InstanceToIndex.
 */
static const rcc_bus_t _TIM_ClockBusLUT[TIM_INSTANCE_COUNT] =
{
	[TIM_INSTANCE_INDEX_TIM2] = RCC_APB1_BUS,
	[TIM_INSTANCE_INDEX_TIM3] = RCC_APB1_BUS,
	[TIM_INSTANCE_INDEX_TIM4] = RCC_APB1_BUS
};

/**
 * @brief Resolves the RCC clock bus associated with one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[out] pClockBus Destination for the resolved RCC clock bus
 * @returns @ref driver_status_t "Clock-bus lookup status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer clock bus was resolved
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An input pointer was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was unsupported
 */
__STATIC_FORCEINLINE driver_status_t _TIM_GetClockBus(const TIM_TypeDef* const TIMx, rcc_bus_t* const pClockBus)
{
	// Local Variable
	tim_instance_index_t instanceIndex = TIM_INSTANCE_INDEX_INVALID;

	//! Validate both pointers before resolving or publishing the bus selector.
	if ((TIMx == NULL) || (pClockBus == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Reject the invalid index sentinel before indexing the static bus table.
	instanceIndex = TIM_InstanceToIndex(TIMx);
	if (TIM_INSTANCE_INDEX_IS_VALID(instanceIndex) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pClockBus = _TIM_ClockBusLUT[instanceIndex];
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local Validation Helpers										//
// ==================================================================================================== //

/**
 * @brief Validates a Timer peripheral instance pointer
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @returns @ref driver_status_t "Timer-instance validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p TIMx is supported
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is unsupported
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateInstance(const TIM_TypeDef* const TIMx)
{
	//! Reject a null pointer before evaluating the supported-instance policy.
	if (TIMx == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Keep general instance validation independent from clock-topology metadata.
	if (TIM_INSTANCE_IS_VALID(TIMx) != 0x00U)
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief Validates a Timer direction selector
 * @param[in] direction Timer direction selector
 * @returns @ref driver_status_t "Direction validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p direction is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p direction is invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateDirection(const tim_direction_t direction)
{
	//! Keep selector policy in the public defines layer instead of duplicating raw values here.
	if (TIM_DIRECTION_IS_VALID(direction) != 0x00U)
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief Validates a Timer alignment selector
 * @param[in] alignment Timer edge/center-aligned selector
 * @returns @ref driver_status_t "Alignment validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p alignment is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p alignment is invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateAlignment(const tim_count_mode_t alignment)
{
	//! Accept only the edge/center-aligned modes exposed by the public driver vocabulary.
	if (TIM_COUNT_MODE_IS_VALID(alignment) != 0x00U)
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief Validates a Timer one-pulse selector
 * @param[in] onePulse Timer one-pulse selector
 * @returns @ref driver_status_t "One-pulse validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p onePulse is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p onePulse is invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateOnePulse(const tim_opm_t onePulse)
{
	//! Restrict OPM input to the two public binary selectors.
	if (TIM_OPM_IS_VALID(onePulse) != 0x00U)
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief Validates a Timer auto-reload preload selector
 * @param[in] autoReloadPreload Timer auto-reload preload selector
 * @returns @ref driver_status_t "Auto-reload preload validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p autoReloadPreload is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p autoReloadPreload is invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateAutoReloadPreload(const tim_arpe_t autoReloadPreload)
{
	//! Restrict ARPE input to the two public binary selectors.
	if (TIM_ARPE_IS_VALID(autoReloadPreload) != 0x00U)
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief Validates a Timer update request source selector
 * @param[in] updateSource Timer update request source selector
 * @returns @ref driver_status_t "Update-source validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p updateSource is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p updateSource is invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateUpdateSource(const tim_update_source_t updateSource)
{
	//! Reject raw URS encodings that are outside the public update-source vocabulary.
	if (TIM_UPDATE_SOURCE_IS_VALID(updateSource) != 0x00U)
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief Validates a Timer digital-filter sampling-clock division selector
 * @param[in] digitalFilterClockDivision Digital-filter clock-division selector
 * @returns @ref driver_status_t "Digital-filter clock-division validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p digitalFilterClockDivision is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p digitalFilterClockDivision is invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateDigitalFilterClockDivision(const tim_digital_filter_clock_division_t digitalFilterClockDivision)
{
	//! Reject the reserved CKD encoding before CR1 staging.
	if (TIM_DIGITAL_FILTER_CLOCK_DIVISION_IS_VALID(digitalFilterClockDivision) != 0x00U)
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief Validates a Timer counter configuration pointer and all public selectors
 * @param[in] pCounter Timer counter configuration
 * @returns @ref driver_status_t "Counter-configuration validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p pCounter is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounter is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more selectors are invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateCounterConfig(const tim_config_counter_t* const pCounter)
{
	//! Validate the container before reading any grouped selector fields.
	if (pCounter == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Reuse scalar selector validators so grouped and scalar APIs share the same validation path.
	ASSERT_DRIVER_STATUS(_TIM_ValidateDirection(pCounter->direction));
	ASSERT_DRIVER_STATUS(_TIM_ValidateAlignment(pCounter->alignment));
	ASSERT_DRIVER_STATUS(_TIM_ValidateOnePulse(pCounter->one_pulse));
	ASSERT_DRIVER_STATUS(_TIM_ValidateAutoReloadPreload(pCounter->auto_reload_preload));
	ASSERT_DRIVER_STATUS(_TIM_ValidateUpdateSource(pCounter->update_source));
	ASSERT_DRIVER_STATUS(_TIM_ValidateDigitalFilterClockDivision(pCounter->digital_filter_clock_division));

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer ON/OFF state selector
 * @param[in] state Timer state selector
 * @returns @ref driver_status_t "Binary-state validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p state is @ref `DRIVER_STATUS_OFF` or @ref `DRIVER_STATUS_ON`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p state is invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateState(const driver_status_t state)
{
	//! Public binary-state APIs accept only OFF and ON, never generic error statuses.
	if ((state == DRIVER_STATUS_OFF) || (state == DRIVER_STATUS_ON))
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
}

/**
 * @brief Validates a non-empty Timer interrupt-request source mask
 * @param[in] irqSources Timer interrupt-request sources to validate
 * @returns @ref driver_status_t "IRQ-source validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p irqSources contains only supported sources
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p irqSources is empty or contains unsupported sources
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateIRQSources(const tim_irq_source_t irqSources)
{
	//! Require at least one source and reject every bit outside the public DIER vocabulary.
	if ((irqSources == TIMx_IRQ_SOURCE_NONE) || ((((uint32_t) irqSources) & (~((uint32_t) TIMx_IRQ_SOURCE_ALL))) != 0x00UL))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a non-empty Timer event-flag mask
 * @param[in] irqEvents Timer event flags to validate
 * @returns @ref driver_status_t "IRQ-event validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p irqEvents contains only supported event flags
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p irqEvents is empty or contains unsupported event flags
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateIRQEvents(const tim_event_flag_t irqEvents)
{
	//! Require at least one event and reject every bit outside the public SR vocabulary.
	if ((irqEvents == TIMx_IRQ_EVENT_NONE) || ((((uint32_t) irqEvents) & (~((uint32_t) TIMx_IRQ_EVENT_ALL))) != 0x00UL))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local RCC Integration Helpers									//
// ==================================================================================================== //

/**
 * @brief Decodes the APB1 clock enable mask for one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pClockEnableMask Destination for the APB1 clock enable mask
 * Expected values:
 * - Non-`NULL`: Decoded APB1 clock enable mask is written to @p `pClockEnableMask`
 * @returns @ref driver_status_t "APB1 clock-mask decode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 clock enable mask was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pClockEnableMask` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is not supported
 */
__STATIC_FORCEINLINE driver_status_t _TIM_DecodeAPB1ClockEnableMask(const TIM_TypeDef* const TIMx, reg* const pClockEnableMask)
{
	//! Validate the instance before resolving its RCC clock gate.
	if (pClockEnableMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));

	//! Compare pointer-width addresses so the instance lookup matches the uintptr_t base definitions.
	switch ((uintptr_t) TIMx)
	{
		case TIM2_BASE_ADDRESS:
		{
			*pClockEnableMask = RCC_APB1ENR_TIM2EN;
			break;
		}
		case TIM3_BASE_ADDRESS:
		{
			*pClockEnableMask = RCC_APB1ENR_TIM3EN;
			break;
		}
		case TIM4_BASE_ADDRESS:
		{
			*pClockEnableMask = RCC_APB1ENR_TIM4EN;
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
 * @brief Decodes the APB1 peripheral reset mask for one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[out] pPeripheralResetMask Destination for the APB1 peripheral reset mask
 * Expected values:
 * - Non-`NULL`: Decoded APB1 peripheral reset mask is written to @p `pPeripheralResetMask`
 * @returns @ref driver_status_t "APB1 peripheral-reset-mask decode status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: APB1 peripheral reset mask was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` or @p `pPeripheralResetMask` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is not supported
 */
__STATIC_FORCEINLINE driver_status_t _TIM_DecodeAPB1PeripheralResetMask(const TIM_TypeDef* const TIMx, reg* const pPeripheralResetMask)
{
	//! Validate destination storage before decoding the instance address.
	if (pPeripheralResetMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));

	//! Match by peripheral base address so deconfiguration cannot pulse an unrelated peripheral reset.
	switch ((uintptr_t) TIMx)
	{
		case TIM2_BASE_ADDRESS:
		{
			*pPeripheralResetMask = RCC_APB1RSTR_TIM2RST;
			break;
		}
		case TIM3_BASE_ADDRESS:
		{
			*pPeripheralResetMask = RCC_APB1RSTR_TIM3RST;
			break;
		}
		case TIM4_BASE_ADDRESS:
		{
			*pPeripheralResetMask = RCC_APB1RSTR_TIM4RST;
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
 * @brief Derives one Timer instance's kernel clock from its mapped RCC bus
 * @param[in] TIMx Timer peripheral instance
 * @param[out] pFrequency Destination for the Timer kernel frequency in hertz
 * @returns @ref driver_status_t "Frequency derivation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer kernel frequency was derived
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An input pointer was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The mapped bus frequency was unavailable
 * @note STM32F1 APB Timer kernels run at twice their bus frequency whenever
 * that APB bus is prescaled.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_GetInputClockFrequency(const TIM_TypeDef* const TIMx, frequency_t* const pFrequency)
{
	// Local Variables
	rcc_bus_t timerClockBus = RCC_APB1_BUS;
	frequency_t timerInputClock = 0UL;

	//! Validate destination storage before resolving or consulting the Timer clock bus.
	if (pFrequency == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_GetClockBus(TIMx, &timerClockBus));

	//! Derive the peripheral clock from the bus selected by the instance LUT.
	timerInputClock = RCC_GetBusFreq(timerClockBus);
	if (timerInputClock == 0UL)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Apply the Timer-kernel x2 rule only when the mapped APB bus is prescaled.
	if (RCC_GetBusPrescaler(timerClockBus) != RCC_APB1_DIV_1)
	{
		timerInputClock <<= 1U;
	}

	*pFrequency = timerInputClock;
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates that the Timer APB1 clock gate is enabled
 * @param[in] TIMx Timer peripheral instance
 * @returns @ref driver_status_t "Clock-gate validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer APB1 clock gate is enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateClockEnabled(TIM_TypeDef* const TIMx)
{
	//! Resolve and sample the APB1 enable bit without touching Timer registers.
	reg clockEnableMask = 0x00000000UL;
	driver_status_t clockState = DRIVER_STATUS_ERROR;
	ASSERT_DRIVER_STATUS(_TIM_DecodeAPB1ClockEnableMask(TIMx, &clockEnableMask));

	//! Read the RCC APB1 clock-enable bit for the requested Timer
	clockState = RCC_APB1_ClockGetState(clockEnableMask);
	if (clockState != DRIVER_STATUS_ERROR_INVALID_ARG)
	{
		if (clockState == DRIVER_STATUS_ON)
		{
			clockState = DRIVER_STATUS_SUCCESS;
		}
		else
		{
			clockState = DRIVER_STATUS_ERROR_STATE;
		}
	}

	return clockState;
}

/**
 * @brief Validates that one caller-owned `TIMx_CR1` image represents a stopped counter
 * @param[in] controlRegisterImage Caller-owned `TIMx_CR1` image
 * @returns @ref driver_status_t "Counter-image validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `TIMx_CR1.CEN` is cleared
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: `TIMx_CR1.CEN` could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: `TIMx_CR1.CEN` is set
 * @note This helper performs no MMIO.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateCounterStoppedImage(const reg controlRegisterImage)
{
	// Local Variable
	driver_status_t counterState = DRIVER_STATUS_ERROR;

	//! Decode and validate CEN without collapsing an unexpected Codec status into BUSY.
	counterState = Codec_TIM_ExtractCounterEnableState(controlRegisterImage);
	ASSERT_DRIVER_STATUS(_TIM_ValidateState(counterState));

	//! Treat an enabled counter image as a busy configuration transaction.
	if (counterState == DRIVER_STATUS_OFF)
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_BUSY;
	}
}

/**
 * @brief Validates that the live Timer counter is stopped before a timing-mode transition
 * @param[in] TIMx Timer peripheral instance
 * @returns @ref driver_status_t "Counter-state validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer clock is enabled and the counter is stopped
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is unsupported
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Timer counter is running
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateCounterStopped(TIM_TypeDef* const TIMx)
{
	//! CEN is readable only while the Timer clock gate is available.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	//! Reuse image validation after taking the one live CR1 snapshot owned by this check.
	return _TIM_ValidateCounterStoppedImage(LL_TIM_ReadCR1(TIMx));
}

/**
 * @brief Validates that selected channel events belong to an output-compare lane
 * @param[in] ccmrRegImage Caller-owned `CCMR1` or `CCMR2` image
 * @param[in] channel Timer channel represented by @p channelEvents
 * @param[in] channelEvents Capture/compare and overcapture events for @p channel
 * @param[in] irqEvents Requested event acknowledgement mask
 * @returns @ref driver_status_t "Channel-event acknowledgement validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: No selected event would discard an unread capture
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The channel selector could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: A selected event belongs to an input-capture lane
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateChannelEventAckMode
(
	const reg				ccmrRegImage,
	const tim_channel_t		channel,
	const tim_event_flag_t	channelEvents,
	const tim_event_flag_t	irqEvents
)
{
	// Local Variable
	tim_channel_ccs_t captureCompareSelection = TIMx_CHANNEL_CCS_OUTPUT;

	//! Skip channel-mode decoding when no event for this lane was selected.
	if ((irqEvents & channelEvents) == TIMx_IRQ_EVENT_NONE)
	{
		return DRIVER_STATUS_SUCCESS;
	}

	ASSERT_DRIVER_STATUS
	(
		Codec_TIM_ExtractChannelSelection
		(
			ccmrRegImage,
			channel,
			&captureCompareSelection
		)
	);
	//! Generic W0C acknowledgement must not discard an unread input-capture notification.
	if (captureCompareSelection != TIMx_CHANNEL_CCS_OUTPUT)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates capture/compare event acknowledgement against live channel modes
 * @param[in] TIMx Timer peripheral instance with an enabled clock gate
 * @param[in] irqEvents Validated event flags requested for acknowledgement
 * @returns @ref driver_status_t "IRQ-event acknowledgement validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Selected channel events are safe to acknowledge generically
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A channel selector could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: A selected event belongs to an input-capture lane
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateIRQEventAckMode(TIM_TypeDef* const TIMx, const tim_event_flag_t irqEvents)
{
	// Local Variable
	reg ccmrRegImage = 0x00000000UL;

	//! Read CCMR1 only when channel 1 or 2 event semantics must be classified.
	if ((irqEvents & (TIMx_IRQ_EVENT_CC1 | TIMx_IRQ_EVENT_CC2 | TIMx_IRQ_EVENT_CC1_OVERCAPTURE | TIMx_IRQ_EVENT_CC2_OVERCAPTURE)) != TIMx_IRQ_EVENT_NONE)
	{
		ccmrRegImage = LL_TIM_ReadCCMR1(TIMx);
		ASSERT_DRIVER_STATUS
		(
			_TIM_ValidateChannelEventAckMode
			(
				ccmrRegImage,
				TIMx_CHANNEL_1,
				TIMx_IRQ_EVENT_CC1 | TIMx_IRQ_EVENT_CC1_OVERCAPTURE,
				irqEvents
			)
		);
		ASSERT_DRIVER_STATUS
		(
			_TIM_ValidateChannelEventAckMode
			(
				ccmrRegImage,
				TIMx_CHANNEL_2,
				TIMx_IRQ_EVENT_CC2 | TIMx_IRQ_EVENT_CC2_OVERCAPTURE,
				irqEvents
			)
		);
	}

	//! Read CCMR2 only when channel 3 or 4 event semantics must be classified.
	if
	(
		(irqEvents &
		(
			TIMx_IRQ_EVENT_CC3 |
			TIMx_IRQ_EVENT_CC4 |
			TIMx_IRQ_EVENT_CC3_OVERCAPTURE |
			TIMx_IRQ_EVENT_CC4_OVERCAPTURE
		)) != TIMx_IRQ_EVENT_NONE
	)
	{
		ccmrRegImage = LL_TIM_ReadCCMR2(TIMx);
		ASSERT_DRIVER_STATUS
		(
			_TIM_ValidateChannelEventAckMode
			(
				ccmrRegImage,
				TIMx_CHANNEL_3,
				TIMx_IRQ_EVENT_CC3 | TIMx_IRQ_EVENT_CC3_OVERCAPTURE,
				irqEvents
			)
		);
		ASSERT_DRIVER_STATUS
		(
			_TIM_ValidateChannelEventAckMode
			(
				ccmrRegImage,
				TIMx_CHANNEL_4,
				TIMx_IRQ_EVENT_CC4 | TIMx_IRQ_EVENT_CC4_OVERCAPTURE,
				irqEvents
			)
		);
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local Dirty Write Helpers										//
// ==================================================================================================== //

/**
 * @brief Writes `TIMx_CR1` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] currentRegImage Current hardware `CR1` image
 * @param[in] stagedRegImage Staged `CR1` image
 * @returns @ref driver_status_t "CR1 dirty-write operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `CR1` write was skipped or performed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is not supported
 * @note Caller owns Timer clock-gate availability before invoking this helper
 */
__STATIC_FORCEINLINE driver_status_t _TIM_WriteCR1IfChanged
(
	TIM_TypeDef* const	TIMx,
	const reg			currentRegImage,
	const reg			stagedRegImage
)
{
	//! Validate the instance before deriving its CR1 register address.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	//! Delegate the generic comparison/write policy while retaining Timer-specific address selection.
	return RegOps_WriteIfChanged(LL_TIM_REG(TIMx, CR1), currentRegImage, stagedRegImage);
}

/**
 * @brief Writes `TIMx_PSC` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] currentRegImage Current hardware `PSC` image
 * @param[in] stagedRegImage Staged `PSC` image
 * @returns @ref driver_status_t "PSC dirty-write operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `PSC` write was skipped or performed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is not supported
 * @note Caller owns Timer clock-gate availability before invoking this helper
 */
__STATIC_FORCEINLINE driver_status_t _TIM_WritePSCIfChanged
(
	TIM_TypeDef* const	TIMx,
	const reg			currentRegImage,
	const reg			stagedRegImage
)
{
	//! Validate the instance before deriving its PSC register address.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	//! Delegate the generic comparison/write policy while retaining Timer-specific address selection.
	return RegOps_WriteIfChanged(LL_TIM_SCALAR_REG(TIMx, PSC), currentRegImage, stagedRegImage);
}

/**
 * @brief Writes `TIMx_ARR` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] currentRegImage Current hardware `ARR` image
 * @param[in] stagedRegImage Staged `ARR` image
 * @returns @ref driver_status_t "ARR dirty-write operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `ARR` write was skipped or performed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is not supported
 * @note Caller owns Timer clock-gate availability before invoking this helper
 */
__STATIC_FORCEINLINE driver_status_t _TIM_WriteARRIfChanged
(
	TIM_TypeDef* const	TIMx,
	const reg			currentRegImage,
	const reg			stagedRegImage
)
{
	//! Validate the instance before deriving its ARR register address.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	//! Delegate the generic comparison/write policy while retaining Timer-specific address selection.
	return RegOps_WriteIfChanged(LL_TIM_SCALAR_REG(TIMx, ARR), currentRegImage, stagedRegImage);
}

/**
 * @brief Writes `TIMx_CNT` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] currentRegImage Current hardware `CNT` image
 * @param[in] stagedRegImage Staged `CNT` image
 * @returns @ref driver_status_t "CNT dirty-write operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `CNT` write was skipped or performed
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `TIMx` is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` is not supported
 * @note Caller owns Timer clock-gate availability before invoking this helper
 */
__STATIC_FORCEINLINE driver_status_t _TIM_WriteCNTIfChanged
(
	TIM_TypeDef* const	TIMx,
	const reg			currentRegImage,
	const reg			stagedRegImage
)
{
	//! Validate the instance before deriving its CNT register address.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	//! Delegate the generic comparison/write policy while retaining Timer-specific address selection.
	return RegOps_WriteIfChanged(LL_TIM_SCALAR_REG(TIMx, CNT), currentRegImage, stagedRegImage);
}

// ==================================================================================================== //
//										Local Update Event Helpers										//
// ==================================================================================================== //

/**
 * @brief Clears `TIMx_SR.UIF` when a generated update event set it
 * @param[in] TIMx Timer peripheral instance
 * @returns @ref driver_status_t "Driver operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Update flag was clear or was acknowledged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is not supported
 * @note Caller owns Timer clock-gate availability before invoking this helper.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ClearUpdateFlagIfPending(TIM_TypeDef* const TIMx)
{
	// Local Variables
	reg srRegImage = 0x00UL;
	driver_status_t updateFlagState = DRIVER_STATUS_ERROR;

	// Validate Input
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));

	//! Decode the current UIF state without collapsing an unexpected Codec status.
	srRegImage = LL_TIM_ReadSR(TIMx);
	updateFlagState = Codec_TIM_ExtractUpdateFlagState(srRegImage);
	ASSERT_DRIVER_STATUS(_TIM_ValidateState(updateFlagState));

	//! The update flag may or may not be set by UG depending on Timer state; avoid writing SR unless needed.
	if (updateFlagState == DRIVER_STATUS_ON)
	{
		//! Stage write-0-to-clear semantics through the codec so the driver does not encode SR flag policy.
		ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateFlagClear(&srRegImage));
		LL_TIM_WriteSR(TIMx, srRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Aborts one incomplete blocking delay and clears its update flag
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @returns @ref driver_status_t "Blocking-delay abort status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Counter operation and `UIF` were cleared after an incomplete delay
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is invalid or Timer state could not be decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Timer APB1 clock gate is disabled
 * @pre @p TIMx retains the dedicated blocking-delay configuration established by
 * @ref TIM_ConfigForBlockingDelay
 */
__STATIC_FORCEINLINE driver_status_t _TIM_CleanupBlockingDelayState(TIM_TypeDef* const TIMx)
{
	// Local Variables
	reg currentControlRegisterImage = 0x00000000UL;
	reg targetControlRegisterImage = 0x00000000UL;

	//! Abort incomplete counter operation while preserving the dedicated blocking-delay configuration.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	currentControlRegisterImage = LL_TIM_ReadCR1(TIMx);
	targetControlRegisterImage = currentControlRegisterImage;
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterEnableState(&targetControlRegisterImage, DRIVER_STATUS_OFF));

	//! Dirty-write CEN, then remove any update flag that raced with the abort.
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentControlRegisterImage, targetControlRegisterImage));
	return _TIM_ClearUpdateFlagIfPending(TIMx);
}

/**
 * @brief Polls one dedicated blocking-delay Timer until its update flag is asserted
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - `TIM2`
 * - `TIM3`
 * - `TIM4`
 * @param[in] pollsRemaining Maximum number of clear-flag samples to tolerate
 * Accepted values:
 * - `1U..0xFFFFFFFFU`: Bounded polling budget
 * @returns @ref driver_status_t "Delay-polling operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: `TIMx_SR.UIF` was asserted
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: Polling budget expired before `TIMx_SR.UIF` was asserted
 * @pre The caller validated @p TIMx and its clock-gate state
 */
__STATIC_FORCEINLINE driver_status_t _TIM_PollBlockingDelayCompletion(TIM_TypeDef* const TIMx, uint32_t	pollsRemaining)
{
	driver_status_t updateFlagState = DRIVER_STATUS_OFF;

	while (pollsRemaining > 0UL)
	{
		//! Sample UIF until hardware completes the one-pulse blocking delay.
		updateFlagState = Codec_TIM_ExtractUpdateFlagState(LL_TIM_ReadSR(TIMx));
		if (updateFlagState == DRIVER_STATUS_ON)
		{
			return DRIVER_STATUS_SUCCESS;
		}

		//! Consume one bounded blocking sample only when the completion flag remained clear.
		pollsRemaining--;
	}

	return DRIVER_STATUS_ERROR_TIMEOUT;
}

// ==================================================================================================== //
//									Local Configuration Staging									//
// ==================================================================================================== //

/**
 * @brief Stages the Timer control and action images required to commit a timebase update
 * @param[in,out] pCommitControlRegisterImage Caller-owned temporary `TIMx_CR1` commit image
 * Accepted values:
 * - Non-`NULL`: Mutable `TIMx_CR1` image
 * @param[in,out] pUpdateEventRegisterImage Caller-owned write-only `TIMx_EGR` action image
 * Accepted values:
 * - Non-`NULL`: Mutable `TIMx_EGR` image
 * @returns @ref driver_status_t "Timebase-update staging status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timebase-update policy and action images were staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: A register-image pointer is `NULL`
 * @note This helper performs no MMIO and publishes both images only after all staging succeeds.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_StageTimeBaseUpdate
(
	reg* const	pCommitControlRegisterImage,
	reg* const	pUpdateEventRegisterImage
)
{
	//! Validate both caller-owned images before staging locally.
	if ((pCommitControlRegisterImage == NULL) || (pUpdateEventRegisterImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	// Local Variables
	reg commitControlRegisterImage = *pCommitControlRegisterImage;
	reg updateEventRegisterImage = *pUpdateEventRegisterImage;

	//! Stage the non-requesting software-update policy and write-only UG action.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateEventState(&commitControlRegisterImage, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateSource(&commitControlRegisterImage, TIMx_UPDATE_SOURCE_OVERFLOW_UNDERFLOW_ONLY));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateEventGeneration(&updateEventRegisterImage));

	*pCommitControlRegisterImage = commitControlRegisterImage;
	*pUpdateEventRegisterImage = updateEventRegisterImage;
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Stages one complete Timer timebase configuration
 * @param[in] pTimeBaseConfig Timer timebase configuration to stage
 * Accepted values:
 * - Non-`NULL`: Complete Timer timebase configuration
 * @param[in,out] pPrescalerRegisterImage Caller-owned `TIMx_PSC` image
 * Accepted values:
 * - Non-`NULL`: Mutable `TIMx_PSC` image
 * @param[in,out] pAutoReloadRegisterImage Caller-owned `TIMx_ARR` image
 * Accepted values:
 * - Non-`NULL`: Mutable `TIMx_ARR` image
 * @param[in,out] pCounterRegisterImage Caller-owned `TIMx_CNT` image
 * Accepted values:
 * - Non-`NULL`: Mutable `TIMx_CNT` image
 * @returns @ref driver_status_t "Timebase-staging operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Complete timebase register images were staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: A configuration or register-image pointer is `NULL`
 * @note This helper performs no MMIO and owns only the fields represented by
 * @ref tim_config_timebase_t
 */
__STATIC_FORCEINLINE driver_status_t _TIM_StageTimeBaseConfig
(
	const tim_config_timebase_t* const	pTimeBaseConfig,
	reg* const							pPrescalerRegisterImage,
	reg* const							pAutoReloadRegisterImage,
	reg* const							pCounterRegisterImage
)
{
	//! Validate every caller-owned object before reading or publishing an image.
	if
	(
		(pTimeBaseConfig == NULL) || (pPrescalerRegisterImage == NULL) ||
		(pAutoReloadRegisterImage == NULL) || (pCounterRegisterImage == NULL)
	)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	// Local Variables
	reg prescalerRegisterImage = *pPrescalerRegisterImage;
	reg autoReloadRegisterImage = *pAutoReloadRegisterImage;
	reg counterRegisterImage = *pCounterRegisterImage;

	//! Stage only the register images represented by the timebase structure.
	ASSERT_DRIVER_STATUS
	(
		Codec_TIM_StageTimeBaseConfig
		(
			&prescalerRegisterImage,
			&autoReloadRegisterImage,
			&counterRegisterImage,
			pTimeBaseConfig
		)
	);

	//! Publish every timebase image only after the grouped Codec stage succeeds.
	*pPrescalerRegisterImage = prescalerRegisterImage;
	*pAutoReloadRegisterImage = autoReloadRegisterImage;
	*pCounterRegisterImage = counterRegisterImage;

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Stages one complete Timer counter configuration image
 * @param[in] pCounterConfig Timer counter configuration to stage
 * Accepted values:
 * - Non-`NULL`: Complete validated Timer counter configuration
 * @param[in,out] pControlRegisterImage Caller-owned `TIMx_CR1` image
 * Accepted values:
 * - Non-`NULL`: Mutable cached `TIMx_CR1` image
 * @returns @ref driver_status_t "Counter-staging operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Complete counter configuration image was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCounterConfig or @p pControlRegisterImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One or more counter selectors are invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Direction cannot change while the current mode is center-aligned
 * @note This helper performs no MMIO and publishes its output only after all staging succeeds.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_StageCounterConfig
(
	const tim_config_counter_t* const	pCounterConfig,
	reg* const							pControlRegisterImage
)
{
	//! Validate the complete domain and destination before staging the target image.
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterConfig(pCounterConfig));
	if (pControlRegisterImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	// Local Variables
	reg targetControlRegisterImage = *pControlRegisterImage;
	tim_config_counter_t currentCounterConfig;

	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractCounterConfig(targetControlRegisterImage, &currentCounterConfig));

	//! Reject a direction change that hardware cannot accept in the current center-aligned mode.
	if
	(
		(currentCounterConfig.alignment != TIMx_MODE_NORMAL) &&
		(currentCounterConfig.direction != pCounterConfig->direction)
	)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Coalesce the complete counter domain into one final CR1 image.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterConfig(&targetControlRegisterImage, pCounterConfig));

	//! Publish the target only after every fallible transformation succeeds.
	*pControlRegisterImage = targetControlRegisterImage;

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Operation State APIs										//
// ==================================================================================================== //

// ------------------------------------ Timer Operation State Pair ------------------------------------ //

driver_status_t TIM_GetOperationState(TIM_TypeDef* const TIMx)
{
	//! Operation state is CR1.CEN; the Timer clock gate must be enabled before CR1 can be read.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	return Codec_TIM_ExtractCounterEnableState(LL_TIM_ReadCR1(TIMx));
}

driver_status_t TIM_SetOperationState(TIM_TypeDef* const TIMx, const driver_status_t operationState)
{
	// Local Variables
	reg currentControlRegisterImage = 0x00000000UL;
	reg stagedControlRegisterImage = 0x00000000UL;

	//! Operation state owns only CR1.CEN; it refuses to touch CR1 while the Timer clock gate is off.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidateState(operationState));

	//! Snapshot CR1 once and stage only CEN while preserving every unrelated field.
	currentControlRegisterImage = LL_TIM_ReadCR1(TIMx);
	stagedControlRegisterImage = currentControlRegisterImage;
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterEnableState(&stagedControlRegisterImage, operationState));

	//! Commit CR1 only when CEN changed.
	return _TIM_WriteCR1IfChanged(TIMx, currentControlRegisterImage, stagedControlRegisterImage);
}

// ==================================================================================================== //
//										Timer Root Configuration APIs									//
// ==================================================================================================== //

// ---------------------------------- Timer Root Configuration Pair ----------------------------------- //

driver_status_t TIM_DeConfig(TIM_TypeDef* const TIMx)
{
	// Local Variable
	reg peripheralResetMask = 0x00000000UL;

	//! Require explicit application clock ownership before resetting the Timer register bank.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_DecodeAPB1PeripheralResetMask(TIMx, &peripheralResetMask));

	//! Reset only Timer-owned peripheral state; RCC clock gating and NVIC delivery remain unchanged.
	return RCC_APB1_ResetPulse(peripheralResetMask);
}

driver_status_t TIM_Config(TIM_TypeDef* const TIMx, const tim_config_t* const pConfig)
{
	// Local Variables
	driver_status_t status = DRIVER_STATUS_SUCCESS;
	reg currentControlRegisterImage = 0x00000000UL;
	reg targetControlRegisterImage = 0x00000000UL;
	reg commitControlRegisterImage = 0x00000000UL;
	reg updateEventRegisterImage = 0x00000000UL;
	reg currentPrescalerRegisterImage = 0x00000000UL;
	reg stagedPrescalerRegisterImage = 0x00000000UL;
	reg currentAutoReloadRegisterImage = 0x00000000UL;
	reg stagedAutoReloadRegisterImage = 0x00000000UL;
	reg stagedCounterRegisterImage = 0x00000000UL;

	//! Validate the complete root request and require the application-owned clock gate.
	if (pConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterConfig(&(pConfig->counter)));

	//! Snapshot CR1 once and validate its stopped state before reading the remaining root images.
	currentControlRegisterImage = LL_TIM_ReadCR1(TIMx);
	status = _TIM_ValidateCounterStoppedImage(currentControlRegisterImage);
	if (status == DRIVER_STATUS_SUCCESS)
	{
		//! Snapshot every remaining register required by the root transaction.
		currentPrescalerRegisterImage = LL_TIM_ReadPSC(TIMx);
		stagedPrescalerRegisterImage = currentPrescalerRegisterImage;
		currentAutoReloadRegisterImage = LL_TIM_ReadARR(TIMx);
		stagedAutoReloadRegisterImage = currentAutoReloadRegisterImage;
		stagedCounterRegisterImage = LL_TIM_ReadCNT(TIMx);

		//! Stage the complete counter domain into one final CR1 image.
		targetControlRegisterImage = currentControlRegisterImage;
		status = _TIM_StageCounterConfig(&(pConfig->counter), &targetControlRegisterImage);
	}
	if (status == DRIVER_STATUS_SUCCESS)
	{
		//! Stage only the register images represented by the root timebase structure.
		status = _TIM_StageTimeBaseConfig
		(
			&(pConfig->timebase),
			&stagedPrescalerRegisterImage,
			&stagedAutoReloadRegisterImage,
			&stagedCounterRegisterImage
		);
	}
	if (status == DRIVER_STATUS_SUCCESS)
	{
		//! Stage the mandatory update action from the final counter-control image.
		commitControlRegisterImage = targetControlRegisterImage;
		status = _TIM_StageTimeBaseUpdate(&commitControlRegisterImage, &updateEventRegisterImage);
	}

	if (status == DRIVER_STATUS_SUCCESS)
	{
		//! Dirty-write the root-owned preload registers before generating the staged update event.
		ASSERT_DRIVER_STATUS
		(
			_TIM_WritePSCIfChanged
			(
				TIMx,
				currentPrescalerRegisterImage,
				stagedPrescalerRegisterImage
			)
		);
		ASSERT_DRIVER_STATUS
		(
			_TIM_WriteARRIfChanged
			(
				TIMx,
				currentAutoReloadRegisterImage,
				stagedAutoReloadRegisterImage
			)
		);

		//! Apply the temporary update policy only when it differs from the cached CR1 image.
		ASSERT_DRIVER_STATUS
		(
			_TIM_WriteCR1IfChanged
			(
				TIMx,
				currentControlRegisterImage,
				commitControlRegisterImage
			)
		);
		//! Generate UG only after every cached configuration image has been committed.
		LL_TIM_WriteEGR(TIMx, updateEventRegisterImage);
		//! Restore the final requested CR1 image after the mandatory update action.
		ASSERT_DRIVER_STATUS
		(
			_TIM_WriteCR1IfChanged
			(
				TIMx,
				commitControlRegisterImage,
				targetControlRegisterImage
			)
		);
		//! UG resets CNT to its known default, so restore the staged initial count without rereading hardware.
		ASSERT_DRIVER_STATUS
		(
			_TIM_WriteCNTIfChanged
			(
				TIMx,
				(reg) TIMx_DEFAULT_CNT,
				stagedCounterRegisterImage
			)
		);
	}

	return status;
}

// ==================================================================================================== //
//										Timer Group Configuration APIs									//
// ==================================================================================================== //

// -------------------------------- Timer TimeBase Configuration Pair --------------------------------- //

driver_status_t TIM_GetTimeBaseConfig(TIM_TypeDef* const TIMx, tim_config_timebase_t* const	pTimeBase)
{
	// Local Variables
	reg pscRegImage = 0x00000000UL;
	reg arrRegImage = 0x00000000UL;
	reg cntRegImage = 0x00000000UL;

	//! Validate the output pointer before any hardware access.
	if (pTimeBase == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Snapshot only the registers needed to extract the timebase group.
	pscRegImage = LL_TIM_ReadPSC(TIMx);
	arrRegImage = LL_TIM_ReadARR(TIMx);
	cntRegImage = LL_TIM_ReadCNT(TIMx);

	//! Decode the caller-owned register images into the public grouped structure.
	return Codec_TIM_ExtractTimeBaseConfig(pscRegImage, arrRegImage, cntRegImage, pTimeBase);
}

driver_status_t TIM_SetTimeBaseConfig(TIM_TypeDef* const TIMx, const tim_config_timebase_t* const pTimeBase)
{
	// Local Variables
	reg currentControlRegisterImage = 0x00000000UL;
	reg commitControlRegisterImage = 0x00000000UL;
	reg updateEventRegisterImage = 0x00000000UL;
	reg currentPrescalerRegisterImage = 0x00000000UL;
	reg stagedPrescalerRegisterImage = 0x00000000UL;
	reg currentAutoReloadRegisterImage = 0x00000000UL;
	reg stagedAutoReloadRegisterImage = 0x00000000UL;
	reg stagedCounterRegisterImage = 0x00000000UL;

	//! TimeBase scalars have no selector constraints, so only the user-supplied pointer is checked here.
	if (pTimeBase == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Own the narrow timebase transaction under an enabled clock.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Snapshot CR1 once and reject a running counter before reading the remaining images.
	currentControlRegisterImage = LL_TIM_ReadCR1(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStoppedImage(currentControlRegisterImage));

	//! Snapshot each remaining required register once before staging locally.
	commitControlRegisterImage = currentControlRegisterImage;
	currentPrescalerRegisterImage = LL_TIM_ReadPSC(TIMx);
	stagedPrescalerRegisterImage = currentPrescalerRegisterImage;
	currentAutoReloadRegisterImage = LL_TIM_ReadARR(TIMx);
	stagedAutoReloadRegisterImage = currentAutoReloadRegisterImage;
	stagedCounterRegisterImage = LL_TIM_ReadCNT(TIMx);

	ASSERT_DRIVER_STATUS
	(
		_TIM_StageTimeBaseConfig
		(
			pTimeBase,
			&stagedPrescalerRegisterImage,
			&stagedAutoReloadRegisterImage,
			&stagedCounterRegisterImage
		)
	);
	ASSERT_DRIVER_STATUS(_TIM_StageTimeBaseUpdate(&commitControlRegisterImage, &updateEventRegisterImage));

	//! Dirty-write both grouped preload registers before generating the staged update event.
	ASSERT_DRIVER_STATUS
	(
		_TIM_WritePSCIfChanged
		(
			TIMx,
			currentPrescalerRegisterImage,
			stagedPrescalerRegisterImage
		)
	);
	ASSERT_DRIVER_STATUS
	(
		_TIM_WriteARRIfChanged
		(
			TIMx,
			currentAutoReloadRegisterImage,
			stagedAutoReloadRegisterImage
		)
	);

	//! Apply the temporary update policy and generate UG only after every fallible step succeeds.
	ASSERT_DRIVER_STATUS
	(
		_TIM_WriteCR1IfChanged
		(
			TIMx,
			currentControlRegisterImage,
			commitControlRegisterImage
		)
	);
	LL_TIM_WriteEGR(TIMx, updateEventRegisterImage);
	//! Restore the caller's CR1 policy after the update action.
	ASSERT_DRIVER_STATUS
	(
		_TIM_WriteCR1IfChanged
		(
			TIMx,
			commitControlRegisterImage,
			currentControlRegisterImage
		)
	);
	//! UG resets CNT to its known default, so restore the staged initial count without rereading hardware.
	ASSERT_DRIVER_STATUS
	(
		_TIM_WriteCNTIfChanged
		(
			TIMx,
			(reg) TIMx_DEFAULT_CNT,
			stagedCounterRegisterImage
		)
	);

	return DRIVER_STATUS_SUCCESS;
}

// --------------------------------- Timer Counter Configuration Pair --------------------------------- //

driver_status_t TIM_GetCounterConfig(TIM_TypeDef* const TIMx, tim_config_counter_t* const pCounter)
{
	reg cr1RegImage = 0x00000000UL;

	//! Validate the output pointer before reading CR1.
	if (pCounter == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Counter configuration is fully represented by the current CR1 image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	//! Return the codec extraction status directly.
	return Codec_TIM_ExtractCounterConfig(cr1RegImage, pCounter);
}

driver_status_t TIM_SetCounterConfig(TIM_TypeDef* const TIMx, const tim_config_counter_t* const	pCounter)
{
	// Local Variables
	reg currentControlRegisterImage = 0x00000000UL;
	reg targetControlRegisterImage = 0x00000000UL;

	//! Validate the complete domain and own its narrow enabled-clock transaction.
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterConfig(pCounter));
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Snapshot CR1 once, reject a running counter, and stage one final target image.
	currentControlRegisterImage = LL_TIM_ReadCR1(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStoppedImage(currentControlRegisterImage));
	targetControlRegisterImage = currentControlRegisterImage;
	ASSERT_DRIVER_STATUS(_TIM_StageCounterConfig(pCounter, &targetControlRegisterImage));

	return _TIM_WriteCR1IfChanged(TIMx, currentControlRegisterImage, targetControlRegisterImage);
}

// ==================================================================================================== //
//										Timer TimeBase Field APIs										//
// ==================================================================================================== //

driver_status_t TIM_GetProgrammedTickFrequency(TIM_TypeDef* const TIMx, frequency_t* const pFrequency)
{
	// Local Variables
	tim_prescaler_t prescaler = 0U;
	frequency_t timerInputClock = 0UL;

	//! Validate the output pointer before any derived-frequency calculation.
	if (pFrequency == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Reuse the public PSC getter so instance validation, clock-gate verification, and extraction stay centralized.
	ASSERT_DRIVER_STATUS(TIM_GetPrescaler(TIMx, &prescaler));
	ASSERT_DRIVER_STATUS(_TIM_GetInputClockFrequency(TIMx, &timerInputClock));

	//! Hardware divides the Timer input clock by PSC + 1 to produce the counter tick frequency.
	*pFrequency = (frequency_t) (timerInputClock / (((frequency_t) prescaler) + 1UL));
	return DRIVER_STATUS_SUCCESS;
}

// --------------------------------------- Timer Prescaler Pair --------------------------------------- //

driver_status_t TIM_GetPrescaler(TIM_TypeDef* const TIMx, tim_prescaler_t* const pPrescaler)
{
	//! Validate the destination before touching the peripheral.
	if (pPrescaler == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! PSC is a scalar register, so extraction only needs the current PSC image.
	return Codec_TIM_ExtractPrescaler(LL_TIM_ReadPSC(TIMx), pPrescaler);
}

driver_status_t TIM_SetPrescaler(TIM_TypeDef* const TIMx, const tim_prescaler_t	prescaler)
{
	// Local Variables
	reg currentControlRegisterImage = 0x00000000UL;
	reg commitControlRegisterImage = 0x00000000UL;
	reg updateEventRegisterImage = 0x00000000UL;
	reg currentPrescalerRegisterImage = 0x00000000UL;
	reg stagedPrescalerRegisterImage = 0x00000000UL;
	reg targetCounterRegisterImage = 0x00000000UL;

	//! Snapshot only the stopped-Timer images required to update and latch PSC.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	currentControlRegisterImage = LL_TIM_ReadCR1(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStoppedImage(currentControlRegisterImage));
	commitControlRegisterImage = currentControlRegisterImage;
	currentPrescalerRegisterImage = LL_TIM_ReadPSC(TIMx);
	stagedPrescalerRegisterImage = currentPrescalerRegisterImage;
	targetCounterRegisterImage = LL_TIM_ReadCNT(TIMx);

	//! Stage the owned PSC field and the shared non-requesting update action before the first write.
	ASSERT_DRIVER_STATUS(Codec_TIM_StagePrescaler(&stagedPrescalerRegisterImage, prescaler));
	ASSERT_DRIVER_STATUS(_TIM_StageTimeBaseUpdate(&commitControlRegisterImage, &updateEventRegisterImage));

	//! Dirty-write only PSC, then latch it through the shared update-event commit sequence.
	ASSERT_DRIVER_STATUS
	(
		_TIM_WritePSCIfChanged
		(
			TIMx,
			currentPrescalerRegisterImage,
			stagedPrescalerRegisterImage
		)
	);

	//! Apply the temporary update policy and generate UG after the cached PSC write.
	ASSERT_DRIVER_STATUS
	(
		_TIM_WriteCR1IfChanged
		(
			TIMx,
			currentControlRegisterImage,
			commitControlRegisterImage
		)
	);
	LL_TIM_WriteEGR(TIMx, updateEventRegisterImage);
	//! Restore the original CR1 policy after the update action.
	ASSERT_DRIVER_STATUS
	(
		_TIM_WriteCR1IfChanged
		(
			TIMx,
			commitControlRegisterImage,
			currentControlRegisterImage
		)
	);
	//! UG resets CNT to its known default, so restore the cached value without rereading hardware.
	ASSERT_DRIVER_STATUS
	(
		_TIM_WriteCNTIfChanged
		(
			TIMx,
			(reg) TIMx_DEFAULT_CNT,
			targetCounterRegisterImage
		)
	);

	return DRIVER_STATUS_SUCCESS;
}

// -------------------------------------- Timer Auto-Reload Pair -------------------------------------- //

driver_status_t TIM_GetAutoReload(TIM_TypeDef* const TIMx, tim_auto_reload_t* const	pAutoReload)
{
	//! Validate the destination before touching the peripheral.
	if (pAutoReload == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! ARR is a scalar register, so extraction only needs the current ARR image.
	return Codec_TIM_ExtractAutoReload(LL_TIM_ReadARR(TIMx), pAutoReload);
}

driver_status_t TIM_SetAutoReload(TIM_TypeDef* const TIMx, const tim_auto_reload_t autoReload)
{
	// Local Variables
	reg currentControlRegisterImage = 0x00000000UL;
	reg commitControlRegisterImage = 0x00000000UL;
	reg updateEventRegisterImage = 0x00000000UL;
	reg currentAutoReloadRegisterImage = 0x00000000UL;
	reg stagedAutoReloadRegisterImage = 0x00000000UL;
	reg targetCounterRegisterImage = 0x00000000UL;

	//! Snapshot only the stopped-Timer images required to update and latch ARR.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	currentControlRegisterImage = LL_TIM_ReadCR1(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStoppedImage(currentControlRegisterImage));
	commitControlRegisterImage = currentControlRegisterImage;
	currentAutoReloadRegisterImage = LL_TIM_ReadARR(TIMx);
	stagedAutoReloadRegisterImage = currentAutoReloadRegisterImage;
	targetCounterRegisterImage = LL_TIM_ReadCNT(TIMx);

	//! Stage the owned ARR field and the shared non-requesting update action before the first write.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageAutoReload(&stagedAutoReloadRegisterImage, autoReload));
	ASSERT_DRIVER_STATUS(_TIM_StageTimeBaseUpdate(&commitControlRegisterImage, &updateEventRegisterImage));

	//! Dirty-write only ARR, then latch it through the shared update-event commit sequence.
	ASSERT_DRIVER_STATUS
	(
		_TIM_WriteARRIfChanged
		(
			TIMx,
			currentAutoReloadRegisterImage,
			stagedAutoReloadRegisterImage
		)
	);

	//! Apply the temporary update policy and generate UG after the cached ARR write.
	ASSERT_DRIVER_STATUS
	(
		_TIM_WriteCR1IfChanged
		(
			TIMx,
			currentControlRegisterImage,
			commitControlRegisterImage
		)
	);
	LL_TIM_WriteEGR(TIMx, updateEventRegisterImage);
	//! Restore the original CR1 policy after the update action.
	ASSERT_DRIVER_STATUS
	(
		_TIM_WriteCR1IfChanged
		(
			TIMx,
			commitControlRegisterImage,
			currentControlRegisterImage
		)
	);
	//! UG resets CNT to its known default, so restore the cached value without rereading hardware.
	ASSERT_DRIVER_STATUS
	(
		_TIM_WriteCNTIfChanged
		(
			TIMx,
			(reg) TIMx_DEFAULT_CNT,
			targetCounterRegisterImage
		)
	);

	return DRIVER_STATUS_SUCCESS;
}

// ------------------------------------- Timer Counter Value Pair ------------------------------------- //

driver_status_t TIM_GetCounterValue(TIM_TypeDef* const TIMx, tim_counter_value_t* const	pCounterValue)
{
	//! Validate the destination before touching the peripheral.
	if (pCounterValue == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! CNT is a scalar register, so extraction only needs the current CNT image.
	return Codec_TIM_ExtractCounterValue(LL_TIM_ReadCNT(TIMx), pCounterValue);
}

driver_status_t TIM_SetCounterValue(TIM_TypeDef* const TIMx, const tim_counter_value_t counterValue)
{
	reg cntRegImage = 0x00000000UL;
	reg currentCntRegImage = 0x00000000UL;

	//! Avoid implementation-defined writes while running in center-aligned mode.
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStopped(TIMx));

	//! Snapshot CNT so the codec can mutate a local image and the driver can dirty-write afterward.
	cntRegImage = LL_TIM_ReadCNT(TIMx);
	currentCntRegImage = cntRegImage;

	//! Stage the requested counter value into the local image, then write only if it changed.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterValue(&cntRegImage, counterValue));
	ASSERT_DRIVER_STATUS(_TIM_WriteCNTIfChanged(TIMx, currentCntRegImage, cntRegImage));

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Counter Field APIs										//
// ==================================================================================================== //

// --------------------------------------- Timer Direction Pair --------------------------------------- //

driver_status_t TIM_GetDirection(TIM_TypeDef* const TIMx, tim_direction_t* const pDirection)
{
	//! Validate the destination before reading CR1.
	if (pDirection == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Direction is encoded in CR1, so extract it from the current CR1 image.
	return Codec_TIM_ExtractCounterDirection(LL_TIM_ReadCR1(TIMx), pDirection);
}

driver_status_t TIM_SetDirection(TIM_TypeDef* const TIMx, const tim_direction_t	direction)
{
	// Local Variables
	tim_config_counter_t counter;
	reg currentControlRegisterImage = 0x00000000UL;
	reg targetControlRegisterImage = 0x00000000UL;

	//! Require a valid selector and snapshot the stopped CR1 domain once.
	ASSERT_DRIVER_STATUS(_TIM_ValidateDirection(direction));
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	currentControlRegisterImage = LL_TIM_ReadCR1(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStoppedImage(currentControlRegisterImage));
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractCounterConfig(currentControlRegisterImage, &counter));

	//! Modify only the requested field, then stage one final CR1 image.
	counter.direction = direction;
	targetControlRegisterImage = currentControlRegisterImage;
	ASSERT_DRIVER_STATUS
	(
		_TIM_StageCounterConfig
		(
			&counter,
			&targetControlRegisterImage
		)
	);
	return _TIM_WriteCR1IfChanged(TIMx, currentControlRegisterImage, targetControlRegisterImage);
}

// --------------------------------------- Timer Alignment Pair --------------------------------------- //

driver_status_t TIM_GetAlignment(TIM_TypeDef* const TIMx, tim_count_mode_t* const pAlignment)
{
	//! Validate the destination before reading CR1
	if (pAlignment == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Alignment is encoded in CR1.CMS, so extract it from the current CR1 image.
	return Codec_TIM_ExtractCounterAlignment(LL_TIM_ReadCR1(TIMx), pAlignment);
}

driver_status_t TIM_SetAlignment(TIM_TypeDef* const TIMx, const tim_count_mode_t alignment)
{
	// Local Variables
	tim_config_counter_t counter = {0};
	reg currentControlRegisterImage = 0x00000000UL;
	reg targetControlRegisterImage = 0x00000000UL;

	//! Require a valid selector and snapshot the stopped CR1 domain once.
	ASSERT_DRIVER_STATUS(_TIM_ValidateAlignment(alignment));
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	currentControlRegisterImage = LL_TIM_ReadCR1(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStoppedImage(currentControlRegisterImage));
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractCounterConfig(currentControlRegisterImage, &counter));

	//! Modify only the requested field, then stage one final CR1 image.
	counter.alignment = alignment;
	targetControlRegisterImage = currentControlRegisterImage;
	ASSERT_DRIVER_STATUS
	(
		_TIM_StageCounterConfig
		(
			&counter,
			&targetControlRegisterImage
		)
	);
	return _TIM_WriteCR1IfChanged(TIMx, currentControlRegisterImage, targetControlRegisterImage);
}

// --------------------------------------- Timer One-Pulse Pair --------------------------------------- //

driver_status_t TIM_GetOnePulse(TIM_TypeDef* const TIMx, tim_opm_t* const pOnePulse)
{
	//! Validate the destination before reading CR1.
	if (pOnePulse == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! One-pulse mode is encoded in CR1.OPM, so extract it from the current CR1 image.
	return Codec_TIM_ExtractOnePulse(LL_TIM_ReadCR1(TIMx), pOnePulse);
}

driver_status_t TIM_SetOnePulse(TIM_TypeDef* const TIMx, const tim_opm_t onePulse)
{

	// Local Variables
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	//! Validate the public selector and verify the Timer clock gate before staging CR1.
	ASSERT_DRIVER_STATUS(_TIM_ValidateOnePulse(onePulse));
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Snapshot CR1 so only the one-pulse field is changed in a local image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	//! Stage the one-pulse selector and preserve unrelated CR1 fields through dirty-write commit.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageOnePulse(&cr1RegImage, onePulse));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));

	return DRIVER_STATUS_SUCCESS;
}

// ---------------------------------- Timer Auto-Reload Preload Pair ---------------------------------- //

driver_status_t TIM_GetAutoReloadPreload(TIM_TypeDef* const	TIMx, tim_arpe_t* const	pAutoReloadPreload)
{
	//! Validate the destination before reading CR1.
	if (pAutoReloadPreload == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Auto-reload preload is encoded in CR1.ARPE, so extract it from the current CR1 image.
	return Codec_TIM_ExtractAutoReloadPreload(LL_TIM_ReadCR1(TIMx), pAutoReloadPreload);
}

driver_status_t TIM_SetAutoReloadPreload(TIM_TypeDef* const	TIMx, const tim_arpe_t autoReloadPreload)
{
	// Local Variables
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	//! Validate the public selector and verify the Timer clock gate before staging CR1.
	ASSERT_DRIVER_STATUS(_TIM_ValidateAutoReloadPreload(autoReloadPreload));
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Snapshot CR1 so only the auto-reload preload field is changed in a local image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	//! Stage the preload selector and preserve unrelated CR1 fields through dirty-write commit.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageAutoReloadPreload(&cr1RegImage, autoReloadPreload));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));

	return DRIVER_STATUS_SUCCESS;
}

// ------------------------------------- Timer Update Source Pair ------------------------------------- //

driver_status_t TIM_GetUpdateSource(TIM_TypeDef* const TIMx, tim_update_source_t* const	pUpdateSource)
{
	//! Validate the destination before reading CR1.
	if (pUpdateSource == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Update source is encoded in CR1.URS, so extract it from the current CR1 image.
	return Codec_TIM_ExtractUpdateSource(LL_TIM_ReadCR1(TIMx), pUpdateSource);
}

driver_status_t TIM_SetUpdateSource(TIM_TypeDef* const TIMx, const tim_update_source_t updateSource)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	//! Validate the public selector and verify the Timer clock gate before staging CR1.
	ASSERT_DRIVER_STATUS(_TIM_ValidateUpdateSource(updateSource));
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Snapshot CR1 so only the update-source field is changed in a local image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	//! Stage the update-source selector and preserve unrelated CR1 fields through dirty-write commit.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateSource(&cr1RegImage, updateSource));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));

	return DRIVER_STATUS_SUCCESS;
}

// -------------------------- Timer Digital-Filter Clock Division Pair ------------------------------- //

driver_status_t TIM_GetDigitalFilterClockDivision
(
	TIM_TypeDef* const							TIMx,
	tim_digital_filter_clock_division_t* const	pDigitalFilterClockDivision
)
{
	//! Validate the destination before reading CR1.
	if (pDigitalFilterClockDivision == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! CR1.CKD divides tDTS, so extract the digital-filter sampling-clock selector.
	return Codec_TIM_ExtractDigitalFilterClockDivision
	(
		LL_TIM_ReadCR1(TIMx),
		pDigitalFilterClockDivision
	);
}

driver_status_t TIM_SetDigitalFilterClockDivision
(
	TIM_TypeDef* const							TIMx,
	const tim_digital_filter_clock_division_t	digitalFilterClockDivision
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	//! Validate the public selector and verify the Timer clock gate before staging CR1.
	ASSERT_DRIVER_STATUS(_TIM_ValidateDigitalFilterClockDivision(digitalFilterClockDivision));
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Snapshot CR1 so only the clock-division field is changed in a local image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	//! Stage the tDTS clock-division selector and preserve unrelated CR1 fields.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageDigitalFilterClockDivision(&cr1RegImage, digitalFilterClockDivision));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer IRQ APIs										//
// ==================================================================================================== //

driver_status_t TIM_GetIRQSources(TIM_TypeDef* const TIMx, tim_irq_source_t* const pIrqSources)
{
	//! Validate destination storage before reading the peripheral interrupt-enable register.
	if (pIrqSources == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	//! Decode only Timer IRQ sources; DMA enable bits remain outside the returned mask.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	return Codec_TIM_ExtractIRQSources(LL_TIM_ReadDIER(TIMx), pIrqSources);
}

driver_status_t TIM_SetIRQSources
(
	TIM_TypeDef* const			TIMx,
	const tim_irq_source_t		irqSources,
	const driver_status_t		sourceState
)
{
	reg dierRegImage = 0x00000000UL;
	reg currentDierRegImage = 0x00000000UL;

	//! Validate the instance, source mask, and state before reading or staging DIER.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidateIRQSources(irqSources));
	ASSERT_DRIVER_STATUS(_TIM_ValidateState(sourceState));
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	dierRegImage = LL_TIM_ReadDIER(TIMx);
	currentDierRegImage = dierRegImage;
	//! Stage only the selected DIER sources while preserving unrelated interrupt and DMA enables.
	ASSERT_DRIVER_STATUS
	(
		Codec_TIM_StageIRQSources
		(
			&dierRegImage,
			irqSources,
			sourceState
		)
	);
	//! Avoid a DIER write when the selected sources already have the requested state.
	if (dierRegImage != currentDierRegImage)
	{
		LL_TIM_WriteDIER(TIMx, dierRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetIRQEvents(TIM_TypeDef* const TIMx, tim_event_flag_t* const pIrqEvents)
{
	//! Validate destination storage before reading the Timer status register.
	if (pIrqEvents == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	//! Decode SR flags independently from DIER source state and NVIC delivery state.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	return Codec_TIM_ExtractIRQEvents(LL_TIM_ReadSR(TIMx), pIrqEvents);
}

driver_status_t TIM_AckIRQEvents(TIM_TypeDef* const TIMx, const tim_event_flag_t irqEvents)
{
	reg srRegImage = 0x00000000UL;

	//! Validate the instance, event mask, and capture-lane policy before touching W0C status bits.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidateIRQEvents(irqEvents));
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidateIRQEventAckMode(TIMx, irqEvents));

	//! Snapshot SR for Codec traceability, then issue one unconditional semantic W0C write.
	srRegImage = LL_TIM_ReadSR(TIMx);
	ASSERT_DRIVER_STATUS(Codec_TIM_StageIRQEventAck(&srRegImage, irqEvents));
	LL_TIM_WriteSR(TIMx, srRegImage);
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Blocking Delay APIs										//
// ==================================================================================================== //

// ---------------------------- Timer Blocking Delay Configuration Helper --------------------------- //

driver_status_t TIM_ConfigForBlockingDelay(TIM_TypeDef* const TIMx)
{
	// Local Variables
	driver_status_t status = DRIVER_STATUS_SUCCESS;
	frequency_t timerInputClock = RCC_FREQ_ZERO;
	reg currentControlRegisterImage = 0x00000000UL;
	reg targetControlRegisterImage = 0x00000000UL;
	const tim_config_t blockingDelayTimerConfig =
	{
		.timebase =
		{
			.prescaler = TIMx_DEFAULT_1MHz_PSC,
			.auto_reload = TIMx_DEFAULT_1MHz_ARR,
			.initial_count = TIMx_DEFAULT_CNT
		},
		.counter =
		{
			.digital_filter_clock_division = TIMx_DIGITAL_FILTER_CLOCK_DIV_1,
			.alignment = TIMx_MODE_NORMAL,
			.direction = TIMx_DIR_COUNT_UP,
			.one_pulse = TIMx_OPM_ENABLE,
			.auto_reload_preload = TIMx_ARPE_DISABLE,
			.update_source = TIMx_UPDATE_SOURCE_ANY
		}
	};

	//! Require the application-owned Timer gate before validating the fixed delay clock contract.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	//! Reject an incompatible clock tree before changing Timer register state.
	ASSERT_DRIVER_STATUS(_TIM_GetInputClockFrequency(TIMx, &timerInputClock));
	if (timerInputClock != RCC_SYSCLK_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Apply the stable timebase, OPM, and immediate-ARR policy for the blocking delay service.
	status = TIM_Config(TIMx, &blockingDelayTimerConfig);
	if (status != DRIVER_STATUS_SUCCESS)
	{
		return status;
	}

	//! Enable update events once so every allocated blocking delay can terminate on UIF.
	currentControlRegisterImage = LL_TIM_ReadCR1(TIMx);
	targetControlRegisterImage = currentControlRegisterImage;
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateEventState(&targetControlRegisterImage, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS
	(
		_TIM_WriteCR1IfChanged
		(
			TIMx,
			currentControlRegisterImage,
			targetControlRegisterImage
		)
	);

	//! Complete allocation with a stopped counter and no stale blocking-delay completion flag.
	return _TIM_ClearUpdateFlagIfPending(TIMx);
}

// ---------------------------------- Timer Microsecond Delay Helper ---------------------------------- //

driver_status_t TIM_DelayUs(TIM_TypeDef* const TIMx, const uint16_t delayUs)
{
	// Local Variables
	tim_auto_reload_t delayReload = 0U;
	driver_status_t pollStatus = DRIVER_STATUS_SUCCESS;
	driver_status_t cleanupStatus = DRIVER_STATUS_SUCCESS;
	uint32_t pollsRemaining = 0UL;
	reg currentControlRegisterImage = 0x00000000UL;
	reg currentAutoReloadRegisterImage = 0x00000000UL;
	reg currentCounterRegisterImage = 0x00000000UL;
	reg targetControlRegisterImage = 0x00000000UL;

	// Validate Input
	if (delayUs == 0U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	//! Validate peripheral access; blocking-delay allocation remains an application-owned contract.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	delayReload = (tim_auto_reload_t) (delayUs - 1U);
	pollsRemaining = (((uint32_t) delayUs) * TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_PER_US) + TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_BASE;

	//! Program only changed blocking-delay interval and counter images, then clear stale completion state.
	currentAutoReloadRegisterImage = LL_TIM_ReadARR(TIMx);
	currentCounterRegisterImage = LL_TIM_ReadCNT(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_WriteARRIfChanged(TIMx, currentAutoReloadRegisterImage, (reg) delayReload));
	ASSERT_DRIVER_STATUS(_TIM_WriteCNTIfChanged(TIMx, currentCounterRegisterImage, (reg) TIMx_DEFAULT_CNT));
	ASSERT_DRIVER_STATUS(_TIM_ClearUpdateFlagIfPending(TIMx));

	//! Start the preconfigured one-pulse blocking delay only after ARR, CNT, and UIF are ready.
	currentControlRegisterImage = LL_TIM_ReadCR1(TIMx);
	targetControlRegisterImage = currentControlRegisterImage;
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterEnableState(&targetControlRegisterImage, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentControlRegisterImage, targetControlRegisterImage));

	//! Poll within the bounded blocking budget; OPM stops the counter after successful completion.
	pollStatus = _TIM_PollBlockingDelayCompletion(TIMx, pollsRemaining);
	if (pollStatus == DRIVER_STATUS_SUCCESS)
	{
		//! Acknowledge the completion event without redundantly stopping an OPM-stopped counter.
		return _TIM_ClearUpdateFlagIfPending(TIMx);
	}

	//! An incomplete delay may still be counting, so abort it and clear any racing update event.
	cleanupStatus = _TIM_CleanupBlockingDelayState(TIMx);
	if (cleanupStatus != DRIVER_STATUS_SUCCESS)
	{
		return cleanupStatus;
	}

	return pollStatus;
}

// ---------------------------------- Timer Millisecond Delay Helper ---------------------------------- //

driver_status_t TIM_BlockingDelayMs(TIM_TypeDef* const TIMx, const uint32_t delayMs)
{
	// Local Variables
	volatile uint32_t elapsedMs = 0UL;

	//! Reject an empty request before the first composed Timer transaction.
	if (delayMs == 0UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Compose the millisecond delay from bounded 1000-us primitive operations.
	for (elapsedMs = 0UL; elapsedMs < delayMs; elapsedMs++)
	{
		ASSERT_DRIVER_STATUS(TIM_DelayUs(TIMx, TIM_DRIVER_BLOCKING_DELAY_MS_CHUNK_US));
	}

	return DRIVER_STATUS_SUCCESS;
}
