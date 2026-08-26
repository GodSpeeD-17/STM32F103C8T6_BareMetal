/**
 * @file	app_init.c
 * @author	Shrey Shah
 * @brief	Orchestrates application-selected hardware services
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section APP_INIT_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application orchestration implementation
 * - Called by: Layer 4 Reset_Handler()
 * - Uses: Layer 2 `app_time` / `app_delay` and Layer 1 RCC Driver
 *
 * @section APP_INIT_C_RESPONSIBILITY Responsibility
 * App_Init() establishes the system clock, starts the configured monotonic
 * timebase, allocates the optional Timer delay service, and configures the
 * optional on-board LED in that order. It propagates the first initialization
 * failure unchanged.
 *
 * @section APP_INIT_C_BOUNDARY Dependency Boundary
 * This module selects and orders services but does not access peripheral
 * registers directly. No service depends upward on `app_init`.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "app_init.h"
#include "app_config.h"
#include "app_delay.h"
#include "app_time.h"
#include "rcc.h"
#if (APP_ENABLE_ONBOARD_LED == 1U)
#include "bsp_gpio.h"
#endif /* APP_ENABLE_ONBOARD_LED */

// ==================================================================================================== //
// Public API
// ==================================================================================================== //

driver_status_t App_Init(void)
{
	//! Establish the application clock tree before initializing clock-dependent services.
	ASSERT_DRIVER_STATUS(RCC_Config72MHz());

#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)
	//! Initialize the monotonic service only after its AHB input clock is final.
	ASSERT_DRIVER_STATUS(App_TimeInit(RCC_GetBusFrequency(RCC_AHB_BUS)));
#endif

#if (APP_ENABLE_TIMER_US_DELAY == 1U)
	//! Allocate Timer hardware only when the application selected the optional service.
	ASSERT_DRIVER_STATUS(App_DelayTimerInit());
#endif

#if (APP_ENABLE_ONBOARD_LED == 1U)
	//! Request the complete BSP-owned RCC/GPIO transaction; successful initialization leaves the active-low LED off.
	ASSERT_DRIVER_STATUS(BSP_InitOBLED());
#endif

	return DRIVER_STATUS_SUCCESS;
}
