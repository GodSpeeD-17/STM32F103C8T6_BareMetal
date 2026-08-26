/**
 * @file	bsp_timer.c
 * @author	Shrey Shah
 * @brief	Implements the Blue Pill TIM4 microsecond-delay capability
 * @version	v1.0
 * @date	26-08-2026
 *
 * @details
 * This source owns the cohesive RCC and Timer initialization transaction for
 * the board-locked TIM4 polling-delay service. It does not participate in the
 * application's interrupt-driven timebase or claim Timer/NVIC interrupt state.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "bsp_timer.h"
#include "stm32f1xx.h"
#include "rcc.h"
#include "timer.h"

#ifdef STM32F103C8T6__

// ==================================================================================================== //
// Private Configuration
// ==================================================================================================== //

/** @brief Timer instance reserved by the board microsecond-delay capability @def BSP_TIMER_US_DELAY_INSTANCE */
#define BSP_TIMER_US_DELAY_INSTANCE				(TIM4)
/** @brief APB1 clock gate required by the board microsecond-delay Timer @def BSP_TIMER_US_DELAY_CLOCK_ENABLE_MASK */
#define BSP_TIMER_US_DELAY_CLOCK_ENABLE_MASK	(RCC_APB1ENR_TIM4EN)
/** @brief Largest delay transaction accepted by the 16-bit Timer primitive @def BSP_TIMER_US_DELAY_MAX_CHUNK */
#define BSP_TIMER_US_DELAY_MAX_CHUNK			((uint16_t) 0xFFFFU)

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

/**
 * @brief Validates the stable TIM4 input clock before enabling its peripheral gate
 * @returns @ref driver_status_t "Board delay Timer input-clock status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TIM4 receives the required 72 MHz input clock
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The fixed TIM4 mapping was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The TIM4 input clock was unavailable or was not 72 MHz
 * @pre The application has completed System/Core clock-tree configuration
 * @note This helper performs no Timer MMIO and does not require the TIM4 gate
 */
static inline driver_status_t BSP_TimerValidateUSDelayClock(void)
{
	// Local Variable
	frequency_t timerInputClockHz = RCC_FREQ_ZERO;

	//! Resolve the family-specific TIM4 kernel clock while peripheral MMIO is still inaccessible.
	ASSERT_DRIVER_STATUS(TIM_GetInputClockFrequency(BSP_TIMER_US_DELAY_INSTANCE, &timerInputClockHz));
	if (timerInputClockHz != RCC_SYSCLK_MAX_FREQ)
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Enables the TIM4 clock required by the board delay capability
 * @returns @ref driver_status_t "Board delay Timer clock-enable status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TIM4 clock was enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The fixed APB1 clock mapping was rejected
 */
static inline driver_status_t BSP_TimerEnableUSDelayClock(void)
{
	//! Keep the TIM4 gate inside the complete BSP transaction so callers never reproduce board RCC policy.
	return RCC_SetPeripheralClockState(RCC_APB1_BUS, BSP_TIMER_US_DELAY_CLOCK_ENABLE_MASK, DRIVER_STATUS_ON);
}

/**
 * @brief Resets and configures TIM4 as the deterministic 1 MHz polling source
 * @returns @ref driver_status_t "Board delay Timer configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: TIM4 was reset and configured
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The fixed TIM4 mapping or configuration was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: TIM4 clock validation or input-clock validation failed
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: TIM4 was unexpectedly running during configuration
 */
static inline driver_status_t BSP_TimerConfigureUSDelay(void)
{
	//! Reset every TIM4-owned register before applying the fixed polling policy so initialization is repeatable.
	ASSERT_DRIVER_STATUS(TIM_DeConfig(BSP_TIMER_US_DELAY_INSTANCE));
	//! Allocate the reset TIM4 instance to the Timer Driver's canonical 1 MHz one-pulse delay service.
	return TIM_ConfigForBlockingDelay(BSP_TIMER_US_DELAY_INSTANCE);
}

// ==================================================================================================== //
// Public API
// ==================================================================================================== //

driver_status_t BSP_InitTimerUSDelay(void)
{
	//! Complete every clock-gate-independent preflight before making the TIM4 register bank accessible.
	ASSERT_DRIVER_STATUS(BSP_TimerValidateUSDelayClock());
	//! Enable the fixed board resource only after its stable input clock satisfies the board delay contract.
	ASSERT_DRIVER_STATUS(BSP_TimerEnableUSDelayClock());
	return BSP_TimerConfigureUSDelay();
}

driver_status_t BSP_TimerDelayUs(const uint32_t delayUs)
{
	// Local Variables
	uint32_t	remainingDelayUs = delayUs;
	uint16_t	delayChunkUs = 0U;

	// Validate Input
	if (delayUs == 0UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Preserve the full public range by decomposing it into transactions accepted by the 16-bit Timer primitive.
	while (remainingDelayUs > 0UL)
	{
		if (remainingDelayUs > ((uint32_t) BSP_TIMER_US_DELAY_MAX_CHUNK))
		{
			delayChunkUs = BSP_TIMER_US_DELAY_MAX_CHUNK;
		}
		else
		{
			delayChunkUs = (uint16_t) remainingDelayUs;
		}

		//! Stop immediately on the first Driver failure so exact bounded-polling status reaches the caller.
		ASSERT_DRIVER_STATUS(TIM_BlockingDelayUs(BSP_TIMER_US_DELAY_INSTANCE, delayChunkUs));
		remainingDelayUs -= ((uint32_t) delayChunkUs);
	}

	return DRIVER_STATUS_SUCCESS;
}

#endif /* STM32F103C8T6__ */
