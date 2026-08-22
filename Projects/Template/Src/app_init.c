#include "app_init.h"

#include "app_config.h"
#include "app_delay.h"
#include "app_time.h"
#include "rcc.h"

driver_status_t App_Init(void)
{
	ASSERT_DRIVER_STATUS(RCC_Config_72MHz());

	#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)
		ASSERT_DRIVER_STATUS(App_TimeInit(RCC_GetBusFreq(RCC_AHB_BUS)));
	#endif

#if (APP_ENABLE_TIMER_US_DELAY == 1U)
	ASSERT_DRIVER_STATUS(App_DelayTimerInit());
#endif

	return DRIVER_STATUS_SUCCESS;
}
