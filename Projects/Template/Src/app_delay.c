#include "app_delay.h"

#include "app_time.h"
#include "stm32f1xx.h"

/** @brief Largest wrap-safe 32-bit millisecond delay interval @def APP_DELAY_MS_MAX */
#define APP_DELAY_MS_MAX					((uint32_t) 0x7FFFFFFFUL)

#if (APP_ENABLE_TIMER_US_DELAY == 1U)
#include "rcc.h"
#include "timer.h"
#endif

driver_status_t App_DelayMs(const uint32_t delayMs)
{
	uint32_t startTickMs = 0UL;

	if ((delayMs == 0UL) || (delayMs > APP_DELAY_MS_MAX))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)
		if ((App_TimeGetOperationState() != DRIVER_STATUS_ON) ||
		(__get_IPSR() != 0UL) ||
		(__get_PRIMASK() != 0UL))
	{
		return DRIVER_STATUS_ERROR_STATE;
	}

	startTickMs = App_TimeGetTickMs();
	while (App_TimeGetElapsedMs(startTickMs) < delayMs)
	{
		//! Sleep between tick interrupts instead of spinning for the complete blocking interval.
		__WFI();
	}

	return DRIVER_STATUS_SUCCESS;
#else
	(void) startTickMs;
	return DRIVER_STATUS_ERROR_STATE;
#endif
}

#if (APP_ENABLE_TIMER_US_DELAY == 1U)
driver_status_t App_DelayTimerInit(void)
{
	ASSERT_DRIVER_STATUS(RCC_APB1_ClockEnable(APP_DELAY_TIMER_CLOCK_MASK));
	return TIM_ConfigForBlockingDelay(APP_DELAY_TIMER);
}

driver_status_t App_DelayUs(const uint32_t delayUs)
{
	uint32_t remainingDelayUs = delayUs;

	if (delayUs == 0UL)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	while (remainingDelayUs != 0UL)
	{
		uint16_t delayChunkUs = 0U;

		if (remainingDelayUs > 0xFFFFUL)
		{
			delayChunkUs = 0xFFFFU;
		}
		else
		{
			delayChunkUs = (uint16_t) remainingDelayUs;
		}

		ASSERT_DRIVER_STATUS(TIM_BlockingDelayUs(APP_DELAY_TIMER, delayChunkUs));
		remainingDelayUs -= (uint32_t) delayChunkUs;
	}

	return DRIVER_STATUS_SUCCESS;
}
#endif
