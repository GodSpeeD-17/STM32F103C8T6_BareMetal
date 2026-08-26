/**
 * @file	app_init.c
 * @author	Shrey Shah
 * @brief	Orchestrates application-selected hardware services
 * @version	v1.0
 * @date	26-08-2026
 *
 * @details
 * @section APP_INIT_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application orchestration implementation
 * - Called by: Layer 4 Reset_Handler()
 * - Uses: Layer 2 `app_time` and Layer 1 RCC/selected BSP capabilities
 *
 * @section APP_INIT_C_RESPONSIBILITY Responsibility
 * App_BootInit() establishes the system clock, starts the selected application
 * timebase, requests the optional BSP-owned TIM4 delay service, and configures
 * the optional on-board LED. Debug policy additionally requests the complete
 * board USART initialization transaction before emitting boot output. The
 * first initialization failure propagates unchanged.
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
#include "app_time.h"
#include "cmsis_gcc.h"
#include "rcc.h"

#if (APP_ENABLE_TIMER_US_DELAY == 1U)
#include "bsp_timer.h"
#endif /* APP_ENABLE_TIMER_US_DELAY */

#if (APP_ENABLE_ONBOARD_LED == 1U)
#include "bsp_gpio.h"
#endif /* APP_ENABLE_ONBOARD_LED */

#if (APP_ENABLE_DEBUG == 1U)
#include "bsp_usart.h"
#endif /* APP_ENABLE_DEBUG */

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

#if (APP_ENABLE_DEBUG == 1U)
/**
 * @brief Emits the optional post-configuration boot diagnostic
 * @returns @ref driver_status_t "Debug boot-diagnostic status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The boot diagnostic was transmitted
 * @retval - @ref `DRIVER_STATUS_ERROR_FAIL`: `vsnprintf()` could not format the fixed diagnostic string
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1's BSP-owned initialization state was unavailable
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: USART TX did not become ready in its polling window
 * @pre BSP_InitUSART() completed successfully and no code disabled USART1's
 * peripheral clock gate before this helper executes
 * @note The fixed format literal and fixed BSP mapping exclude the lower
 * formatter's null-format and invalid-instance failure paths
 */
__STATIC driver_status_t App_DebugLogBootReady(void)
{
#if (APP_ENABLE_FLOAT == 1U)
	const float bootProtocolVersion = 1.0F;

	//! Debug plus float policy emits the `%f` field through the boot-configured board transport.
	return BSP_USART_printf("[boot] USART polling echo ready; protocol=%.1f\r\n", (double) bootProtocolVersion);
#else
	//! Debug without float policy keeps diagnostics integer-only and avoids linking the `%f` formatter.
	return BSP_USART_printf("[boot] USART polling echo ready\r\n");
#endif /* APP_ENABLE_FLOAT */
}
#endif /* APP_ENABLE_DEBUG */

// ==================================================================================================== //
// Public API
// ==================================================================================================== //

driver_status_t App_BootInit(void)
{
	//! Establish the application clock tree before initializing clock-dependent services.
	ASSERT_DRIVER_STATUS(RCC_Config72MHz());

#if (APP_TIMEBASE_SOURCE != APP_TIME_SOURCE_NONE)
	//! Initialize the selected fixed-1-ms interrupt source only after every Core and bus clock is final.
	ASSERT_DRIVER_STATUS(App_TimeInit((app_time_source_t) APP_TIMEBASE_SOURCE));
#endif /* APP_TIMEBASE_SOURCE != APP_TIME_SOURCE_NONE */

#if (APP_ENABLE_TIMER_US_DELAY == 1U)
	//! Request the complete board-locked TIM4 polling-delay transaction without reproducing its mapping in the application.
	ASSERT_DRIVER_STATUS(BSP_InitTimerUSDelay());
#endif /* APP_ENABLE_TIMER_US_DELAY */

#if (APP_ENABLE_ONBOARD_LED == 1U)
	//! Request the complete BSP-owned RCC/GPIO transaction; successful initialization leaves the active-low LED off.
	ASSERT_DRIVER_STATUS(BSP_InitOBLED());
#endif /* APP_ENABLE_ONBOARD_LED */

#if (APP_ENABLE_DEBUG == 1U)
	//! Debug implicitly acquires the complete BSP USART transport before its first diagnostic.
	ASSERT_DRIVER_STATUS(BSP_InitUSART());
	//! Optional boot text is emitted only after BSP configured USART1's pins, baud rate, and UE state.
	ASSERT_DRIVER_STATUS(App_DebugLogBootReady());
#endif /* APP_ENABLE_DEBUG */

	return DRIVER_STATUS_SUCCESS;
}
