#include "main.h"

#include "app_config.h"
#include "app_time.h"
#include "stm32f1xx.h"

int main(void)
{
#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)
	uint32_t previousTickMs = App_TimeGetTickMs();
#endif

	while (1)
	{
#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)
		//! Keep periodic application work non-blocking by observing the shared monotonic timebase.
		if (App_TimeGetElapsedMs(previousTickMs) >= APP_MAIN_PERIOD_MS)
		{
			previousTickMs += APP_MAIN_PERIOD_MS;
			/* Add periodic application work here. */
		}
#endif

		//! Sleep until an enabled interrupt produces work for the application loop.
		__WFI();
	}
}
