/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Provides the replaceable Template application control loop
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 2 `app_time` and Core `WFI` intrinsic
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * This replaceable control loop demonstrates non-blocking periodic scheduling
 * against the application timebase while sleeping between interrupts.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * Application behavior belongs here. Processor startup, clock configuration,
 * service initialization, and interrupt-side work do not.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "app_config.h"
#include "app_time.h"
#include "stm32f1xx.h"

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

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
