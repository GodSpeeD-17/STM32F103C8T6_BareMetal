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
 * - Uses: Layer 2 `app_time` / `app_delay` and Layer 1 RCC/BSP Drivers
 *
 * @section APP_INIT_C_RESPONSIBILITY Responsibility
 * App_BootInit() establishes the system clock, starts the configured monotonic
 * timebase, allocates the optional Timer delay service, configures the
 * optional on-board LED, then enables the board UART's application-owned
 * clocks and establishes its polling-echo transport through BSP. When
 * selected, it emits the boot diagnostic only after that UART is ready. It
 * propagates the first initialization failure unchanged.
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
#include "bsp.h"

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

#if (APP_ENABLE_DEBUG == 1U)
/**
 * @brief Emits the optional post-configuration boot diagnostic
 * @returns @ref driver_status_t "Debug boot-diagnostic status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The boot diagnostic was transmitted
 * @retval - @ref `DRIVER_STATUS_ERROR_FAIL`: `vsnprintf()` could not format the fixed diagnostic string
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1's application-owned peripheral clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: USART TX did not become ready in its polling window
 * @pre BSP_USART_Init() completed successfully and no code disabled USART1's
 * peripheral clock gate before this helper executes
 * @note The fixed format literal and fixed BSP mapping exclude the lower
 * formatter's null-format and invalid-instance failure paths
 */
static driver_status_t App_DebugLogBootReady(void)
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

#if (APP_ENABLE_SYSTICK_TIMEBASE == 1U)
	//! Initialize the monotonic service only after its AHB input clock is final.
	ASSERT_DRIVER_STATUS(App_TimeInit(RCC_GetBusFrequency(RCC_AHB_BUS)));
#endif /* APP_ENABLE_SYSTICK_TIMEBASE */

#if (APP_ENABLE_TIMER_US_DELAY == 1U)
	//! Allocate Timer hardware only when the application selected the optional service.
	ASSERT_DRIVER_STATUS(App_DelayTimerInit());
#endif /* APP_ENABLE_TIMER_US_DELAY */

#if (APP_ENABLE_ONBOARD_LED == 1U)
	//! The application explicitly owns the on-board LED GPIO port clock gate.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(RCC_APB2_BUS, GPIO_OB_LED_CLOCK_ENABLE_MASK, DRIVER_STATUS_ON));
	//! Configure the on-board LED GPIO and force a deterministic off state before application code runs.
	ASSERT_DRIVER_STATUS(BSP_OB_LED_Init());
	BSP_OB_LED_Reset();
#endif /* APP_ENABLE_ONBOARD_LED */

	//! Clock gates are application-owned preconditions; BSP configures the fixed PA9/PA10 and USART1 mapping without mutating RCC.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(RCC_APB2_BUS, BSP_USART_GPIO_CLOCK_ENABLE_MASK, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(RCC_APB2_BUS, BSP_USART_CLOCK_ENABLE_MASK, DRIVER_STATUS_ON));
	//! Main's polling loop requires the board transport to be fully configured before its first RXNE wait.
	ASSERT_DRIVER_STATUS(BSP_USART_Init());

#if (APP_ENABLE_DEBUG == 1U)
	//! Optional boot text is emitted only after BSP configured USART1's pins, baud rate, and UE state.
	ASSERT_DRIVER_STATUS(App_DebugLogBootReady());
#endif /* APP_ENABLE_DEBUG */

	return DRIVER_STATUS_SUCCESS;
}
