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
 * The root configuration surface owns:
 * - `TIMx_CR1` counter behavior fields represented by @ref tim_config_counter_t
 * - `TIMx_PSC` prescaler
 * - `TIMx_ARR` auto-reload value
 * - `TIMx_CNT` counter value
 *
 * Channel/PWM, DMA, and master/slave behavior remain deferred. This driver also
 * owns Timer DIER/SR IRQ mapping, instance NVIC policy, and bounded blocking
 * @ref TIM_DelayUs / @ref TIM_DelayMs helpers.
 *
 * @section TIM_DRIVER_IMPL_LAYOUT Source Layout
 * The public implementation follows the same banner and sub-banner order as
 * `timer.h`: clock state, operation state, root configuration, grouped
 * configuration, timebase fields, counter fields, and blocking delay helpers
 * at the end. Local helpers are kept ahead of the public API sections so public
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
#include "nvic.h"

// ==================================================================================================== //
//										Local Driver Configuration										//
// ==================================================================================================== //

/** @brief Microsecond delay chunk used by the millisecond blocking helper @def TIM_DRIVER_DELAY_MS_CHUNK_US */
#define TIM_DRIVER_DELAY_MS_CHUNK_US			((uint16_t) 1000U)
/** @brief Conservative polling-loop budget per requested microsecond @def TIM_DRIVER_DELAY_POLL_BUDGET_PER_US */
#define TIM_DRIVER_DELAY_POLL_BUDGET_PER_US		((uint32_t) 1024UL)
/** @brief Fixed setup allowance added to the polling-loop budget @def TIM_DRIVER_DELAY_POLL_BUDGET_BASE */
#define TIM_DRIVER_DELAY_POLL_BUDGET_BASE		((uint32_t) 1024UL)

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
 * @returns Clock-bus lookup status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer clock bus was resolved.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An input pointer was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was unsupported.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_GetClockBus
(
	const TIM_TypeDef* const	TIMx,
	rcc_bus_t* const			pClockBus
)
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
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p TIMx is supported.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p TIMx is `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx is unsupported.
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
 * @returns Validation status
 * @retval DRIVER_STATUS_SUCCESS @p direction is valid
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p direction is invalid
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
 * @returns Validation status
 * @retval DRIVER_STATUS_SUCCESS @p alignment is valid
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p alignment is invalid
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
 * @returns Validation status
 * @retval DRIVER_STATUS_SUCCESS @p onePulse is valid
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p onePulse is invalid
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
 * @returns Validation status
 * @retval DRIVER_STATUS_SUCCESS @p autoReloadPreload is valid
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p autoReloadPreload is invalid
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
 * @returns Validation status
 * @retval DRIVER_STATUS_SUCCESS @p updateSource is valid
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p updateSource is invalid
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
 * @brief Validates a Timer clock division selector
 * @param[in] clockDivision Timer clock division selector
 * @returns Validation status
 * @retval DRIVER_STATUS_SUCCESS @p clockDivision is valid
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p clockDivision is invalid
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateClockDivision(const tim_clock_division_t clockDivision)
{
	//! Reject the reserved CKD encoding before CR1 staging.
	if (TIM_CLOCK_DIVISION_IS_VALID(clockDivision) != 0x00U)
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
 * @returns Validation status
 * @retval DRIVER_STATUS_SUCCESS @p pCounter is valid
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p pCounter is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG One or more selectors are invalid
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
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockDivision(pCounter->clock_division));

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates a Timer ON/OFF state selector
 * @param[in] state Timer state selector
 * @returns Validation status
 * @retval DRIVER_STATUS_SUCCESS @p state is @ref DRIVER_STATUS_OFF or @ref DRIVER_STATUS_ON
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p state is invalid
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

// ==================================================================================================== //
//										Local RCC Integration Helpers									//
// ==================================================================================================== //

/**
 * @brief Returns the APB1 clock enable mask for one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[out] pClockMask Destination for APB1 clock enable mask
 * @returns Decode status
 * @retval DRIVER_STATUS_SUCCESS Clock mask was decoded
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx OR @p pClockMask is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx is not supported
 */
__STATIC_FORCEINLINE driver_status_t _TIM_GetAPB1ClockMask
(
	const TIM_TypeDef* const	TIMx,
	reg* const					pClockMask
)
{
	//! Validate the instance before resolving its RCC clock gate.
	if (pClockMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));

	//! Match by peripheral base address because instance macros are raw memory-mapped pointers.
	switch ((uint32_t) TIMx)
	{
		case TIM2_BASE_ADDRESS:
		{
			*pClockMask = RCC_APB1ENR_TIM2EN;
			break;
		}
		case TIM3_BASE_ADDRESS:
		{
			*pClockMask = RCC_APB1ENR_TIM3EN;
			break;
		}
		case TIM4_BASE_ADDRESS:
		{
			*pClockMask = RCC_APB1ENR_TIM4EN;
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
 * @brief Returns the APB1 reset mask for one supported Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[out] pResetMask Destination for the APB1 reset mask
 * @returns Reset-mask decode status
 * @retval DRIVER_STATUS_SUCCESS Reset mask was decoded.
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx / @p pResetMask was `NULL`.
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx was unsupported.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_GetAPB1ResetMask
(
	const TIM_TypeDef* const	TIMx,
	reg* const					pResetMask
)
{
	//! Validate destination storage before decoding the instance address.
	if (pResetMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));

	//! Match by peripheral base address so deconfiguration cannot pulse an unrelated peripheral reset.
	switch ((uint32_t) TIMx)
	{
		case TIM2_BASE_ADDRESS:
		{
			*pResetMask = RCC_APB1RSTR_TIM2RST;
			break;
		}
		case TIM3_BASE_ADDRESS:
		{
			*pResetMask = RCC_APB1RSTR_TIM3RST;
			break;
		}
		case TIM4_BASE_ADDRESS:
		{
			*pResetMask = RCC_APB1RSTR_TIM4RST;
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
 * @brief Returns the NVIC IRQ number for one supported Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[out] pIRQn Destination for the external IRQ number
 * @returns IRQ-number decode status
 * @retval DRIVER_STATUS_SUCCESS IRQ number was decoded.
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx / @p pIRQn was `NULL`.
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx was unsupported.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_GetIRQn
(
	const TIM_TypeDef* const	TIMx,
	irq_t* const				pIRQn
)
{
	//! Validate destination storage before decoding the instance address.
	if (pIRQn == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));

	//! Map each Timer to its dedicated external interrupt line.
	switch ((uint32_t) TIMx)
	{
		case TIM2_BASE_ADDRESS:
		{
			*pIRQn = TIM2_IRQn;
			break;
		}
		case TIM3_BASE_ADDRESS:
		{
			*pIRQn = TIM3_IRQn;
			break;
		}
		case TIM4_BASE_ADDRESS:
		{
			*pIRQn = TIM4_IRQn;
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
 * @returns Frequency derivation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer kernel frequency was derived.
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An input pointer was `NULL`.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p TIMx was unsupported.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The mapped bus frequency was unavailable.
 * @note STM32F1 APB Timer kernels run at twice their bus frequency whenever
 * that APB bus is prescaled.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_GetInputClockFrequency
(
	const TIM_TypeDef* const	TIMx,
	tim_frequency_t* const		pFrequency
)
{
	// Local Variables
	rcc_bus_t timerClockBus = RCC_APB1_BUS;
	tim_frequency_t timerInputClock = 0UL;

	//! Validate destination storage before resolving or consulting the Timer clock bus.
	if (pFrequency == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_GetClockBus(TIMx, &timerClockBus));

	//! Derive the peripheral clock from the bus selected by the instance LUT.
	timerInputClock = (tim_frequency_t) RCC_GetBusFreq(timerClockBus);
	if (timerInputClock == 0UL)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	//! Apply the Timer-kernel x2 rule only when the mapped APB bus is prescaled.
	if (RCC_GetBusPrescaler(timerClockBus) != ((rcc_bus_prescaler_t) 0U))
	{
		timerInputClock <<= 1U;
	}

	*pFrequency = timerInputClock;
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Validates that the Timer APB1 clock gate is enabled
 * @param[in] TIMx Timer peripheral instance
 * @returns Clock-gate validation status
 * @retval DRIVER_STATUS_SUCCESS Timer APB1 clock gate is enabled
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx is not supported
 * @retval DRIVER_STATUS_ERROR_STATE Timer APB1 clock gate is disabled
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateClockEnabled(TIM_TypeDef* const TIMx)
{
	//! Validate the instance before resolving its RCC clock gate.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));

	//! Resolve and sample the APB1 enable bit without touching Timer registers.
	reg clockMask = 0x00000000UL;
	driver_status_t clockState = DRIVER_STATUS_ERROR;
	ASSERT_DRIVER_STATUS(_TIM_GetAPB1ClockMask(TIMx, &clockMask));

	//! Read the RCC APB1 clock-enable bit for the requested Timer
	clockState = RCC_APB1_ClockGetState(clockMask);
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
 * @brief Requires the Timer counter to be stopped before a timing-mode transition
 * @param[in] TIMx Timer peripheral instance
 * @returns Counter-state validation status
 * @retval DRIVER_STATUS_SUCCESS Timer clock is enabled and the counter is stopped.
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx was `NULL`.
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx was unsupported.
 * @retval DRIVER_STATUS_ERROR_STATE Timer APB1 clock gate was disabled.
 * @retval DRIVER_STATUS_ERROR_BUSY Timer counter was running.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ValidateCounterStopped(TIM_TypeDef* const TIMx)
{
	//! CEN is readable only while the Timer clock gate is available.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	//! Timebase and DIR/CMS transitions are rejected while hardware is counting.
	if (Codec_TIM_ExtractCounterEnableState(LL_TIM_ReadCR1(TIMx)) == DRIVER_STATUS_OFF)
	{
		return DRIVER_STATUS_SUCCESS;
	}
	else
	{
		return DRIVER_STATUS_ERROR_BUSY;
	}
}

// ==================================================================================================== //
//										Local Dirty Write Helpers										//
// ==================================================================================================== //

/**
 * @brief Writes `TIMx_CR1` only when the staged image changed
 * @param[in] TIMx Timer peripheral instance
 * @param[in] currentRegImage Current hardware `CR1` image
 * @param[in] stagedRegImage Staged `CR1` image
 * @returns Driver operation status
 * @retval DRIVER_STATUS_SUCCESS `CR1` write was skipped or performed
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx is not supported
 * @note Caller owns Timer clock-gate availability before invoking this helper.
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
 * @param[in] currentRegImage Current hardware `PSC` image
 * @param[in] stagedRegImage Staged `PSC` image
 * @returns Driver operation status
 * @retval DRIVER_STATUS_SUCCESS `PSC` write was skipped or performed
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx is not supported
 * @note Caller owns Timer clock-gate availability before invoking this helper.
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
 * @param[in] currentRegImage Current hardware `ARR` image
 * @param[in] stagedRegImage Staged `ARR` image
 * @returns Driver operation status
 * @retval DRIVER_STATUS_SUCCESS `ARR` write was skipped or performed
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx is not supported
 * @note Caller owns Timer clock-gate availability before invoking this helper.
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
 * @param[in] currentRegImage Current hardware `CNT` image
 * @param[in] stagedRegImage Staged `CNT` image
 * @returns Driver operation status
 * @retval DRIVER_STATUS_SUCCESS `CNT` write was skipped or performed
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx is not supported
 * @note Caller owns Timer clock-gate availability before invoking this helper.
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
 * @brief Generates one software update event
 * @param[in] TIMx Timer peripheral instance
 * @returns Driver operation status
 * @retval DRIVER_STATUS_SUCCESS Update event generation was requested
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx is not supported
 * @note Caller owns Timer clock-gate availability before invoking this helper.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_GenerateUpdateEvent(TIM_TypeDef* const TIMx)
{
	// Validate Input
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));

	// Local Variables
	reg egrRegImage = 0x00000000UL;
	//! EGR is write-only register
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateEventGeneration(&egrRegImage));
	LL_TIM_WriteEGR(TIMx, egrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Clears `TIMx_SR.UIF` when a generated update event set it
 * @param[in] TIMx Timer peripheral instance
 * @returns Driver operation status
 * @retval DRIVER_STATUS_SUCCESS Update flag was clear or was acknowledged
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx is not supported
 * @note Caller owns Timer clock-gate availability before invoking this helper.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ClearUpdateFlagIfPending(TIM_TypeDef* const TIMx)
{
	// Validate Input
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));

	// Local Variable
	reg srRegImage = 0x00UL;
	srRegImage = LL_TIM_ReadSR(TIMx);

	//! The update flag may or may not be set by UG depending on Timer state; avoid writing SR unless needed.
	if (Codec_TIM_ExtractUpdateFlagState(srRegImage) == DRIVER_STATUS_ON)
	{
		//! Stage write-0-to-clear semantics through the codec so the driver does not encode SR flag policy.
		ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateFlagClear(&srRegImage));
		LL_TIM_WriteSR(TIMx, srRegImage);
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Commits buffered timebase values without creating a software-update IRQ
 * @details Temporarily enables update events and selects overflow/underflow-only
 * update requests, generates `UG`, restores CR1, and restores the requested CNT.
 * @param[in] TIMx Timer peripheral instance
 * @param[in] targetCntRegImage Counter image to restore after the update event
 * @returns Timebase commit status
 * @retval DRIVER_STATUS_SUCCESS Buffered values were committed and CNT was restored.
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx was `NULL`.
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx was unsupported.
 * @retval DRIVER_STATUS_ERROR_STATE The Timer clock gate was disabled.
 * @retval DRIVER_STATUS_ERROR_BUSY The Timer counter was running.
 * @note The caller must stage PSC and ARR before invoking this helper.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_CommitTimeBase
(
	TIM_TypeDef* const	TIMx,
	const reg			targetCntRegImage
)
{
	// Local Variables
	reg currentCr1RegImage = 0x00000000UL;
	reg commitCr1RegImage = 0x00000000UL;
	reg postUpdateCntRegImage = 0x00000000UL;

	//! A software update is safe only while the counter is stopped.
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStopped(TIMx));

	//! Temporarily allow UG while suppressing its interrupt and DMA request side effects.
	currentCr1RegImage = LL_TIM_ReadCR1(TIMx);
	commitCr1RegImage = currentCr1RegImage;
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateEventState(&commitCr1RegImage, DRIVER_STATUS_ON));
	//! URS=1 allows UG to latch buffered values without asserting UIF or an IRQ/DMA request.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateSource(&commitCr1RegImage, TIMx_UPDATE_SOURCE_OVF_DMA));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, commitCr1RegImage));
	ASSERT_DRIVER_STATUS(_TIM_GenerateUpdateEvent(TIMx));
	//! Restore the caller's update-event policy immediately after committing the preload registers.
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, commitCr1RegImage, currentCr1RegImage));

	//! UG resets CNT, so restore the requested initial count after the buffered commit.
	postUpdateCntRegImage = LL_TIM_ReadCNT(TIMx);
	ASSERT_DRIVER_STATUS(_TIM_WriteCNTIfChanged(TIMx, postUpdateCntRegImage, targetCntRegImage));
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local TimeBase Orchestration									//
// ==================================================================================================== //

/**
 * @brief Applies a staged timebase configuration to one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[in] pTimeBase TimeBase configuration to apply
 * @returns Driver operation status
 * @retval DRIVER_STATUS_SUCCESS TimeBase fields were applied
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx or @p pTimeBase is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx is not supported
 * @note Caller owns Timer clock-gate availability before invoking this helper.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ApplyTimeBaseConfig
(
	TIM_TypeDef* const						TIMx,
	const tim_config_timebase_t* const		pTimeBase
)
{
	// Validate Input
	if (pTimeBase == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));

	//! Read each timebase register once, then stage all caller-requested values into local images.
	reg pscRegImage = LL_TIM_ReadPSC(TIMx);
	reg arrRegImage = LL_TIM_ReadARR(TIMx);
	reg cntRegImage = LL_TIM_ReadCNT(TIMx);
	//! Keep the original images so only modified registers are committed back to hardware.
	const reg currentPscRegImage = pscRegImage;
	const reg currentArrRegImage = arrRegImage;

	//! Codec owns field staging; ASSERT_DRIVER_STATUS propagates codec status directly.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageTimeBaseConfig(&pscRegImage, &arrRegImage, &cntRegImage, pTimeBase));

	//! Commit PSC/ARR, then generate UG so their active shadow state matches the public API result.
	ASSERT_DRIVER_STATUS(_TIM_WritePSCIfChanged(TIMx, currentPscRegImage, pscRegImage));
	ASSERT_DRIVER_STATUS(_TIM_WriteARRIfChanged(TIMx, currentArrRegImage, arrRegImage));
	ASSERT_DRIVER_STATUS(_TIM_CommitTimeBase(TIMx, cntRegImage));

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Applies a staged counter configuration to one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[in] pCounter Counter configuration to apply
 * @returns Driver operation status
 * @retval DRIVER_STATUS_SUCCESS Counter fields were applied
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx or @p pCounter is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx or one or more counter fields are invalid
 * @note Caller owns Timer clock-gate availability before invoking this helper.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ApplyCounterConfig
(
	TIM_TypeDef* const						TIMx,
	const tim_config_counter_t* const		pCounter
)
{
	//! Validate the complete request and require a stopped counter before changing DIR/CMS.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterConfig(pCounter));
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStopped(TIMx));

	reg currentCr1RegImage = LL_TIM_ReadCR1(TIMx);
	reg stagedCr1RegImage = currentCr1RegImage;
	tim_config_counter_t currentCounter;
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractCounterConfig(currentCr1RegImage, &currentCounter));

	//! DIR is read-only in center-aligned mode, so leave center-aligned mode before changing direction.
	if
	(
		(currentCounter.alignment != TIMx_MODE_NORMAL) &&
		(currentCounter.direction != pCounter->direction)
	)
	{
		//! Move to edge-aligned mode so DIR becomes writable before changing direction.
		stagedCr1RegImage = currentCr1RegImage;
		ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterAlignment(&stagedCr1RegImage, TIMx_MODE_NORMAL));
		ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, stagedCr1RegImage));
		currentCr1RegImage = stagedCr1RegImage;
		currentCounter.alignment = TIMx_MODE_NORMAL;
	}

	if
	(
		(pCounter->alignment != TIMx_MODE_NORMAL) &&
		(currentCounter.direction != pCounter->direction)
	)
	{
		//! Set the requested direction while still edge-aligned before entering the target center-aligned mode.
		stagedCr1RegImage = currentCr1RegImage;
		ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterDirection(&stagedCr1RegImage, pCounter->direction));
		ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, stagedCr1RegImage));
		currentCr1RegImage = stagedCr1RegImage;
	}

	//! Commit the complete requested counter image after any required intermediate transition.
	stagedCr1RegImage = currentCr1RegImage;
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterConfig(&stagedCr1RegImage, pCounter));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, stagedCr1RegImage));
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local Root Configuration Orchestration							//
// ==================================================================================================== //

/**
 * @brief Applies a complete Timer root configuration using the update-event latch sequence
 * @param[in] TIMx Timer peripheral instance
 * @param[in] pConfig Complete Timer root configuration to apply
 * @returns @ref driver_status_t "Driver Operation Status"
 * @retval DRIVER_STATUS_SUCCESS Root configuration was applied
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx or @p pConfig is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx or one or more counter selectors are invalid
 * @details
 * This helper owns the register ordering used by @ref TIM_Config. The caller
 * must stop the counter and keep the Timer clock gate enabled throughout it.
 *
 * The Timer prescaler and preloaded auto-reload value become active only after
 * an update event. Because @ref tim_config_t does not own `CR1.UDIS`, this
 * helper preserves the caller's final update-event state while temporarily
 * using `UDIS=0` and `URS=1` for the software-generated `UG`. This latches
 * buffered values without asserting `UIF` or requesting an interrupt/DMA.
 *
 * Register order:
 * - Mask the instance NVIC line when it is currently enabled.
 * - Apply the counter configuration through the safe stopped DIR/CMS sequence.
 * - Stage and write `PSC`/`ARR`, generate a non-requesting `EGR.UG`, restore
 *   `CR1`, and restore the requested `CNT` value.
 * - Restore the instance NVIC line to its entry state.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ApplyRootConfig
(
	TIM_TypeDef* const				TIMx,
	const tim_config_t* const		pConfig
)
{
	driver_status_t status = DRIVER_STATUS_SUCCESS;
	driver_status_t nvicState = DRIVER_STATUS_OFF;
	irq_t IRQn = TIM2_IRQn;

	if (pConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterConfig(&(pConfig->counter)));
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStopped(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_GetIRQn(TIMx, &IRQn));

	//! Prevent an existing Timer IRQ configuration from pre-empting the multi-register transaction.
	nvicState = NVIC_IRQ_GetState(IRQn);
	if (nvicState == DRIVER_STATUS_ON)
	{
		NVIC_IRQ_Disable(IRQn);
	}

	status = _TIM_ApplyCounterConfig(TIMx, &(pConfig->counter));
	if (status == DRIVER_STATUS_SUCCESS)
	{
		status = _TIM_ApplyTimeBaseConfig(TIMx, &(pConfig->timebase));
	}

	if (nvicState == DRIVER_STATUS_ON)
	{
		NVIC_IRQ_Enable(IRQn);
	}

	return status;
}

/**
 * @brief Applies a staged counter enable state to one Timer instance
 * @param[in] TIMx Timer peripheral instance
 * @param[in] counterState Counter runtime state to apply
 * @returns Driver operation status
 * @retval DRIVER_STATUS_SUCCESS Counter runtime state was applied
 * @retval DRIVER_STATUS_ERROR_NULL_PTR @p TIMx is `NULL`
 * @retval DRIVER_STATUS_ERROR_INVALID_ARG @p TIMx or @p counterState is invalid
 * @note Caller owns Timer clock-gate availability before invoking this helper.
 */
__STATIC_FORCEINLINE driver_status_t _TIM_ApplyCounterEnableState
(
	TIM_TypeDef* const			TIMx,
	const driver_status_t		counterState
)
{
	// Validate Input
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidateState(counterState));

	//! Read CR1 once because counter enable state is represented by the runtime CEN bit.
	reg cr1RegImage = LL_TIM_ReadCR1(TIMx);
	//! Preserve the original CR1 image so enable/disable APIs avoid redundant CR1 writes.
	const reg currentCr1RegImage = cr1RegImage;

	//! Codec stages only CR1.CEN and preserves every other counter configuration/runtime bit.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterEnableState(&cr1RegImage, counterState));

	//! Commit CR1 only after staging succeeds and only when CEN actually changed.
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Clock State APIs											//
// ==================================================================================================== //

// -------------------------------------- Timer Clock State Pair -------------------------------------- //

driver_status_t TIM_GetClockState(TIM_TypeDef* const TIMx)
{
	// Local Variable
	reg clockMask = 0x00000000UL;
	// Validate Input
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	//! Clock state is the RCC APB1 gate bit for this Timer instance.
	ASSERT_DRIVER_STATUS(_TIM_GetAPB1ClockMask(TIMx, &clockMask));
	return RCC_APB1_ClockGetState(clockMask);
}

driver_status_t TIM_SetClockState(TIM_TypeDef* const TIMx, const driver_status_t clockState)
{
	// Local Variable
	reg clockMask = 0x00000000UL;
	// Validate Input
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidateState(clockState));
	//! Clock state owns only the RCC APB1 gate; Timer counter start remains a separate operation state.
	ASSERT_DRIVER_STATUS(_TIM_GetAPB1ClockMask(TIMx, &clockMask));
	if (clockState == DRIVER_STATUS_ON)
	{
		return RCC_APB1_ClockEnable(clockMask);
	}
	else
	{
		return RCC_APB1_ClockDisable(clockMask);
	}
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
	//! Operation state owns only CR1.CEN; it refuses to touch CR1 while the Timer clock gate is off.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidateState(operationState));
	return _TIM_ApplyCounterEnableState(TIMx, operationState);
}

// ==================================================================================================== //
//										Timer Root Configuration APIs									//
// ==================================================================================================== //

// ---------------------------------- Timer Root Configuration Pair ----------------------------------- //

driver_status_t TIM_DeConfig(TIM_TypeDef* const TIMx)
{
	reg resetMask = 0x00000000UL;
	irq_t IRQn = TIM2_IRQn;

	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_GetAPB1ResetMask(TIMx, &resetMask));
	ASSERT_DRIVER_STATUS(_TIM_GetIRQn(TIMx, &IRQn));

	//! A full deconfiguration removes both peripheral-side state and NVIC delivery state.
	NVIC_IRQ_Disable(IRQn);
	NVIC_IRQ_ClearPending(IRQn);
	ASSERT_DRIVER_STATUS(TIM_SetClockState(TIMx, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(RCC_APB1_ResetPulse(resetMask));
	ASSERT_DRIVER_STATUS(TIM_SetClockState(TIMx, DRIVER_STATUS_OFF));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_Config(TIM_TypeDef* const TIMx, const tim_config_t* const pConfig)
{
	// Validate Input Configurations
	if (pConfig == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	// Validate the Timer instance and counter configuration before touching any hardware.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterConfig(&(pConfig->counter)));

	//! Enable Clock for Timer
	ASSERT_DRIVER_STATUS(TIM_SetClockState(TIMx, DRIVER_STATUS_ON));
	//! Disable Timer counter before applying configuration
	ASSERT_DRIVER_STATUS(TIM_SetOperationState(TIMx, DRIVER_STATUS_OFF));

	//! Apply the full root configuration with the forced-update latch sequence.
	ASSERT_DRIVER_STATUS(_TIM_ApplyRootConfig(TIMx, pConfig));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_ConfigTickFrequency
(
	TIM_TypeDef* const		TIMx,
	const tim_frequency_t	targetFrequency
)
{
	tim_frequency_t timerInputClock = 0UL;
	tim_frequency_t divider = 0UL;
	tim_config_t config;

	//! Validate the public request before reading the RCC clock tree.
	ASSERT_DRIVER_STATUS(_TIM_ValidateInstance(TIMx));
	if (targetFrequency == 0UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	//! Derive the live Timer kernel clock and require an exact integer divider.
	ASSERT_DRIVER_STATUS(_TIM_GetInputClockFrequency(TIMx, &timerInputClock));
	if ((targetFrequency > timerInputClock) || ((timerInputClock % targetFrequency) != 0UL))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Convert the exact divider to the hardware PSC encoding and enforce its 16-bit range.
	divider = timerInputClock / targetFrequency;
	if ((divider == 0UL) || (divider > 0x00010000UL))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Build the reusable base-Timer preset and delegate hardware sequencing to TIM_Config().
	config.timebase.prescaler = (tim_prescaler_t) (divider - 1UL);
	config.timebase.auto_reload = TIMx_DEFAULT_1MHz_ARR;
	config.timebase.initial_count = TIMx_DEFAULT_CNT;
	config.counter.direction = TIMx_DIR_COUNT_UP;
	config.counter.alignment = TIMx_MODE_NORMAL;
	config.counter.one_pulse = TIMx_OPM_DISABLE;
	config.counter.auto_reload_preload = TIMx_ARPE_ENABLE;
	config.counter.update_source = TIMx_UPDATE_SOURCE_ANY;
	config.counter.clock_division = TIMx_CKD_CLK_FREQ;

	return TIM_Config(TIMx, &config);
}

// ==================================================================================================== //
//										Timer Group Configuration APIs									//
// ==================================================================================================== //

// -------------------------------- Timer TimeBase Configuration Pair --------------------------------- //

driver_status_t TIM_GetTimeBaseConfig
(
	TIM_TypeDef* const				TIMx,
	tim_config_timebase_t* const	pTimeBase
)
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

driver_status_t TIM_SetTimeBaseConfig
(
	TIM_TypeDef* const					TIMx,
	const tim_config_timebase_t* const	pTimeBase
)
{
	//! TimeBase scalars have no selector constraints, so only the user-supplied pointer is checked here.
	if (pTimeBase == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Reuse the shared apply path to keep batching and dirty writes consistent.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	return _TIM_ApplyTimeBaseConfig(TIMx, pTimeBase);
}

// --------------------------------- Timer Counter Configuration Pair --------------------------------- //

driver_status_t TIM_GetCounterConfig
(
	TIM_TypeDef* const				TIMx,
	tim_config_counter_t* const		pCounter
)
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

driver_status_t TIM_SetCounterConfig
(
	TIM_TypeDef* const					TIMx,
	const tim_config_counter_t* const	pCounter
)
{
	//! Validate first, then reuse the shared CR1 apply path for staging and dirty-write behavior.
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterConfig(pCounter));
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	return _TIM_ApplyCounterConfig(TIMx, pCounter);
}

// ==================================================================================================== //
//										Timer TimeBase Field APIs										//
// ==================================================================================================== //

driver_status_t TIM_GetFrequency
(
	TIM_TypeDef* const			TIMx,
	tim_frequency_t* const		pFrequency
)
{
	tim_prescaler_t prescaler = 0U;
	tim_frequency_t timerInputClock = 0UL;

	//! Validate the output pointer before any derived-frequency calculation.
	if (pFrequency == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Reuse the public PSC getter so instance validation, clock-gate verification, and extraction stay centralized.
	ASSERT_DRIVER_STATUS(TIM_GetPrescaler(TIMx, &prescaler));

	ASSERT_DRIVER_STATUS(_TIM_GetInputClockFrequency(TIMx, &timerInputClock));

	//! Hardware divides the Timer input clock by PSC + 1 to produce the counter tick frequency.
	*pFrequency = (tim_frequency_t) (timerInputClock / (((tim_frequency_t) prescaler) + 1UL));
	return DRIVER_STATUS_SUCCESS;
}

// --------------------------------------- Timer Prescaler Pair --------------------------------------- //

driver_status_t TIM_GetPrescaler
(
	TIM_TypeDef* const		TIMx,
	tim_prescaler_t* const	pPrescaler
)
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

driver_status_t TIM_SetPrescaler
(
	TIM_TypeDef* const		TIMx,
	const tim_prescaler_t	prescaler
)
{
	tim_config_timebase_t timeBase;
	//! Timebase preload changes are accepted only while the counter is stopped.
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStopped(TIMx));
	//! Read the complete timebase first so changing PSC preserves ARR and CNT.
	ASSERT_DRIVER_STATUS
	(
		Codec_TIM_ExtractTimeBaseConfig
		(
			LL_TIM_ReadPSC(TIMx),
			LL_TIM_ReadARR(TIMx),
			LL_TIM_ReadCNT(TIMx),
			&timeBase
		)
	);
	timeBase.prescaler = prescaler;
	//! Reuse the shared apply path to keep batching and dirty writes consistent.
	return _TIM_ApplyTimeBaseConfig(TIMx, &timeBase);
}

// -------------------------------------- Timer Auto-Reload Pair -------------------------------------- //

driver_status_t TIM_GetAutoReload
(
	TIM_TypeDef* const			TIMx,
	tim_auto_reload_t* const	pAutoReload
)
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

driver_status_t TIM_SetAutoReload
(
	TIM_TypeDef* const			TIMx,
	const tim_auto_reload_t		autoReload
)
{
	tim_config_timebase_t timeBase;
	//! Timebase preload changes are accepted only while the counter is stopped.
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStopped(TIMx));
	//! Read the complete timebase first so changing ARR preserves PSC and CNT.
	ASSERT_DRIVER_STATUS
	(
		Codec_TIM_ExtractTimeBaseConfig
		(
			LL_TIM_ReadPSC(TIMx),
			LL_TIM_ReadARR(TIMx),
			LL_TIM_ReadCNT(TIMx),
			&timeBase
		)
	);
	timeBase.auto_reload = autoReload;
	//! Reuse the shared apply path to keep batching and dirty writes consistent.
	return _TIM_ApplyTimeBaseConfig(TIMx, &timeBase);
}

// ------------------------------------- Timer Counter Value Pair ------------------------------------- //

driver_status_t TIM_GetCounterValue
(
	TIM_TypeDef* const			TIMx,
	tim_counter_value_t* const	pCounterValue
)
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

driver_status_t TIM_SetCounterValue
(
	TIM_TypeDef* const			TIMx,
	const tim_counter_value_t	counterValue
)
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
	tim_config_counter_t counter;
	//! Require a valid selector and stopped counter before reading mode-dependent DIR/CMS state.
	ASSERT_DRIVER_STATUS(_TIM_ValidateDirection(direction));
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStopped(TIMx));
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractCounterConfig(LL_TIM_ReadCR1(TIMx), &counter));
	//! Modify only the requested field, then reuse the safe grouped counter transition path.
	counter.direction = direction;
	return _TIM_ApplyCounterConfig(TIMx, &counter);
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
	// Local Variable
	tim_config_counter_t counter = {0};

	//! Require a valid selector and stopped counter before changing edge/center-aligned mode.
	ASSERT_DRIVER_STATUS(_TIM_ValidateAlignment(alignment));
	ASSERT_DRIVER_STATUS(_TIM_ValidateCounterStopped(TIMx));
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractCounterConfig(LL_TIM_ReadCR1(TIMx), &counter));

	//! Modify only the requested field, then reuse the safe grouped counter transition path.
	counter.alignment = alignment;
	return _TIM_ApplyCounterConfig(TIMx, &counter);
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

driver_status_t TIM_SetAutoReloadPreload(TIM_TypeDef* const	TIMx, const tim_arpe_t	autoReloadPreload)
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

driver_status_t TIM_GetUpdateSource
(
	TIM_TypeDef* const			TIMx,
	tim_update_source_t* const	pUpdateSource
)
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

driver_status_t TIM_SetUpdateSource
(
	TIM_TypeDef* const			TIMx,
	const tim_update_source_t	updateSource
)
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

// ------------------------------------ Timer Clock Division Pair ------------------------------------- //

driver_status_t TIM_GetClockDivision
(
	TIM_TypeDef* const			TIMx,
	tim_clock_division_t* const	pClockDivision
)
{
	//! Validate the destination before reading CR1.
	if (pClockDivision == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Clock division is encoded in CR1.CKD, so extract it from the current CR1 image.
	return Codec_TIM_ExtractClockDivision(LL_TIM_ReadCR1(TIMx), pClockDivision);
}

driver_status_t TIM_SetClockDivision
(
	TIM_TypeDef* const			TIMx,
	const tim_clock_division_t	clockDivision
)
{
	reg cr1RegImage = 0x00000000UL;
	reg currentCr1RegImage = 0x00000000UL;

	//! Validate the public selector and verify the Timer clock gate before staging CR1.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockDivision(clockDivision));
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));

	//! Snapshot CR1 so only the clock-division field is changed in a local image.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	currentCr1RegImage = cr1RegImage;

	//! Stage the clock-division selector and preserve unrelated CR1 fields through dirty-write commit.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageClockDivision(&cr1RegImage, clockDivision));
	ASSERT_DRIVER_STATUS(_TIM_WriteCR1IfChanged(TIMx, currentCr1RegImage, cr1RegImage));

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer IRQ APIs										//
// ==================================================================================================== //

driver_status_t TIM_GetIRQEnableMask(TIM_TypeDef* const TIMx, tim_irq_t* const pIrqMask)
{
	//! Validate destination storage before reading the peripheral interrupt-enable register.
	if (pIrqMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	//! Decode only Timer IRQ sources; DMA enable bits remain outside the returned mask.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	return Codec_TIM_ExtractIRQEnableMask(LL_TIM_ReadDIER(TIMx), pIrqMask);
}

driver_status_t TIM_SetIRQState
(
	TIM_TypeDef* const		TIMx,
	const tim_irq_t			irqMask,
	const driver_status_t	irqState
)
{
	// Local Variables
	reg dierRegImage = 0x00000000UL;
	reg currentDierRegImage = 0x00000000UL;
	tim_irq_t enabledMask = (tim_irq_t) 0U;
	tim_irq_enable_t irqEnable = TIMx_IRQ_DISABLE;
	irq_t IRQn = TIM2_IRQn;

	//! Reject unsupported source bits and non-binary state selectors before reading DIER.
	if ((TIM_IRQ_MASK_IS_VALID(irqMask) == 0x00U) || ((irqState != DRIVER_STATUS_OFF) && (irqState != DRIVER_STATUS_ON)))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_GetIRQn(TIMx, &IRQn));
	//! Convert the driver-facing state once before passing the codec-specific IRQ selector.
	if (irqState == DRIVER_STATUS_ON)
	{
		irqEnable = TIMx_IRQ_ENABLE;
	}
	else
	{
		irqEnable = TIMx_IRQ_DISABLE;
	}

	dierRegImage = LL_TIM_ReadDIER(TIMx);
	currentDierRegImage = dierRegImage;
	//! Stage only the selected DIER sources while preserving unrelated interrupt and DMA enables.
	ASSERT_DRIVER_STATUS
	(
		Codec_TIM_StageIRQEnableMask
		(
			&dierRegImage,
			irqMask,
			irqEnable
		)
	);
	//! Avoid a DIER write when the selected sources already have the requested state.
	if (dierRegImage != currentDierRegImage)
	{
		LL_TIM_WriteDIER(TIMx, dierRegImage);
	}

	//! Enable the shared NVIC line whenever at least one requested Timer source is enabled.
	if (irqState == DRIVER_STATUS_ON)
	{
		NVIC_IRQ_ClearPending(IRQn);
		NVIC_IRQ_Enable(IRQn);
	}
	else
	{
		//! Disable the NVIC line only after the final Timer interrupt source is disabled.
		ASSERT_DRIVER_STATUS(Codec_TIM_ExtractIRQEnableMask(dierRegImage, &enabledMask));
		if (enabledMask == (tim_irq_t) 0U)
		{
			NVIC_IRQ_Disable(IRQn);
			NVIC_IRQ_ClearPending(IRQn);
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t TIM_GetPendingIRQMask(TIM_TypeDef* const TIMx, tim_irq_t* const pIrqMask)
{
	//! Validate destination storage before reading the Timer status register.
	if (pIrqMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	//! Decode supported SR event flags into the public IRQ mask vocabulary.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	return Codec_TIM_ExtractIRQFlagMask(LL_TIM_ReadSR(TIMx), pIrqMask);
}

driver_status_t TIM_AcknowledgeIRQ(TIM_TypeDef* const TIMx, const tim_irq_t irqMask)
{
	reg srRegImage = 0x00000000UL;
	reg stagedSrRegImage = 0x00000000UL;
	irq_t IRQn = TIM2_IRQn;

	//! Reject empty or unsupported acknowledge masks before touching W0C status bits.
	if (TIM_IRQ_MASK_IS_VALID(irqMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	ASSERT_DRIVER_STATUS(_TIM_GetIRQn(TIMx, &IRQn));

	//! Stage write-zero-to-clear semantics from the current SR image so unrelated flags remain pending.
	srRegImage = LL_TIM_ReadSR(TIMx);
	stagedSrRegImage = srRegImage;
	ASSERT_DRIVER_STATUS(Codec_TIM_StageIRQAckMask(&stagedSrRegImage, irqMask));
	if (stagedSrRegImage != srRegImage)
	{
		LL_TIM_WriteSR(TIMx, stagedSrRegImage);
	}
	//! Clear stale NVIC pending state after peripheral flags have been acknowledged.
	NVIC_IRQ_ClearPending(IRQn);
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Blocking Delay APIs										//
// ==================================================================================================== //

// ---------------------------------- Timer Microsecond Delay Helper ---------------------------------- //

driver_status_t TIM_DelayUs(TIM_TypeDef* const TIMx, const uint16_t delayUs)
{
	// Local Variables
	tim_auto_reload_t delayReload = 0U;
	tim_frequency_t actualFrequency = 0UL;
	driver_status_t updateEventState = DRIVER_STATUS_ERROR;
	uint32_t pollsRemaining = 0UL;
	reg cr1RegImage = 0x00000000UL;

	// Validate Input
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	if (delayUs == 0U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	ASSERT_DRIVER_STATUS(TIM_GetFrequency(TIMx, &actualFrequency));
	if (actualFrequency != (tim_frequency_t) 1000000UL)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	delayReload = (tim_auto_reload_t) (delayUs - 1U);
	pollsRemaining = (((uint32_t) delayUs) * TIM_DRIVER_DELAY_POLL_BUDGET_PER_US) + TIM_DRIVER_DELAY_POLL_BUDGET_BASE;

	//! Disable ARPE and stop the counter before preparing the delay window.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	updateEventState = Codec_TIM_ExtractUpdateEventState(cr1RegImage);
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterEnableState(&cr1RegImage, DRIVER_STATUS_OFF));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageAutoReloadPreload(&cr1RegImage, TIMx_ARPE_DISABLE));
	LL_TIM_WriteCR1(TIMx, cr1RegImage);

	//! Configure ARR and CNT for this delay window, then clear any stale update flag.
	LL_TIM_WriteARR(TIMx, (reg) delayReload);
	LL_TIM_WriteCNT(TIMx, (reg) TIMx_DEFAULT_CNT);
	ASSERT_DRIVER_STATUS(_TIM_ClearUpdateFlagIfPending(TIMx));

	//! Enable OPM and CEN together so counting starts only after ARR/CNT/UIF are prepared.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageOnePulse(&cr1RegImage, TIMx_OPM_ENABLE));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateEventState(&cr1RegImage, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterEnableState(&cr1RegImage, DRIVER_STATUS_ON));
	LL_TIM_WriteCR1(TIMx, cr1RegImage);

	while (Codec_TIM_ExtractUpdateFlagState(LL_TIM_ReadSR(TIMx)) == DRIVER_STATUS_OFF)
	{
		//! Bound polling so a stopped or misclocked peripheral cannot block forever.
		if (pollsRemaining == 0UL)
		{
			cr1RegImage = LL_TIM_ReadCR1(TIMx);
			(void) Codec_TIM_StageCounterEnableState(&cr1RegImage, DRIVER_STATUS_OFF);
			(void) Codec_TIM_StageUpdateEventState(&cr1RegImage, updateEventState);
			LL_TIM_WriteCR1(TIMx, cr1RegImage);
			(void) _TIM_ClearUpdateFlagIfPending(TIMx);
			return DRIVER_STATUS_ERROR_TIMEOUT;
		}
		pollsRemaining--;
	}

	//! OPM should clear CEN after UIF, but stop explicitly and restore the caller's update-event state.
	cr1RegImage = LL_TIM_ReadCR1(TIMx);
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterEnableState(&cr1RegImage, DRIVER_STATUS_OFF));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateEventState(&cr1RegImage, updateEventState));
	LL_TIM_WriteCR1(TIMx, cr1RegImage);
	ASSERT_DRIVER_STATUS(_TIM_ClearUpdateFlagIfPending(TIMx));

	return DRIVER_STATUS_SUCCESS;
}

// ---------------------------------- Timer Millisecond Delay Helper ---------------------------------- //

driver_status_t TIM_DelayMs(TIM_TypeDef* const TIMx, const uint32_t delayMs)
{
	// Local Variables
	uint32_t elapsedMs = 0UL;

	//! Validate the dedicated delay Timer and reject an empty delay request.
	ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
	if (delayMs == 0UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Compose the millisecond delay from bounded 1000-us primitive operations.
	for (elapsedMs = 0UL; elapsedMs < delayMs; elapsedMs++)
	{
		ASSERT_DRIVER_STATUS(TIM_DelayUs(TIMx, TIM_DRIVER_DELAY_MS_CHUNK_US));
	}

	return DRIVER_STATUS_SUCCESS;
}
