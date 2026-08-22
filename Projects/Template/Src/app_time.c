#include "app_time.h"

#include "systick.h"

#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)
driver_status_t App_TimeInit(const frequency_t inputClockHz)
{
	ASSERT_DRIVER_STATUS(SysTick_Config(inputClockHz, APP_SYSTICK_TICK_HZ));
	SysTick_ResetTicks();
	SysTick_Enable();

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t App_TimeGetOperationState(void)
{
	return SysTick_GetOperationState();
}

uint32_t App_TimeGetTickMs(void)
{
	return SysTick_GetTicks();
}

uint32_t App_TimeGetElapsedMs(const uint32_t startTickMs)
{
	return App_TimeGetTickMs() - startTickMs;
}
#endif
