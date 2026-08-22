/**
 * @file	app_config.h
 * @author	Shrey Shah
 * @brief	Defines the compile-time policy shared by application services
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section APP_CONFIG_H_HIERARCHY Application Hierarchy
 * Dependencies flow downward through four runtime layers:
 * - Layer 4 - Entry: `app_startup` performs reset handling
 * - Layer 3 - Orchestration: `app_init` initializes services and `main` runs
 *   application behavior
 * - Layer 2 - Services: `app_time` and `app_delay` provide reusable operations
 * - Layer 1 - Hardware access: `systick` and shared RCC/Timer Drivers
 * Layer 1 is always closest to hardware. Increasing layer numbers represent
 * progressively more software-only behavior, policy, and orchestration.
 *
 * @section APP_CONFIG_H_POSITION Position of This File
 * `app_config.h` is cross-cutting compile-time policy, not a runtime layer.
 * Layers 2 and 3 read it; it does not call or initialize any layer.
 *
 * @section APP_CONFIG_H_USERS Direct Users
 * `app_init.c`, `main.c`, `app_time.h`, and `app_delay.h` include this file.
 *
 * @section APP_CONFIG_H_BOUNDARY Dependency Boundary
 * This file includes no project, Core, or Driver header. It selects features
 * and publishes constants only; hardware initialization belongs to Layer 3.
 */

// Header Guard
#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

/**
 * @brief Application-owned Template services
 * @defgroup APP_Template Application Template
 */

/**
 * @brief Compile-time application feature and timing policy
 * @defgroup APP_Config Application Configuration
 * @ingroup APP_Template
 * @details
 * These macros select which timing capabilities are compiled, define the
 * application timebase contract, and map an optional dedicated Timer service
 * to its hardware instance and RCC clock gate. Defining a macro publishes
 * policy only; Layer 3 initialization performs every hardware transaction.
 * @{
 */

// ==================================================================================================== //
// SysTick Timebase Configuration
// ==================================================================================================== //

/**
 * @brief Selects the SysTick-backed application millisecond timebase
 * @def APP_ENABLE_SYSTICK_TIMEBASE
 * @details
 * This is the master compile-time switch for monotonic application time.
 * App_Init() starts SysTick, `app_time` exposes tick/elapsed APIs, `main`
 * enables its non-blocking periodic example, and App_DelayMs() becomes
 * operational only when this value is `1U`.
 * Accepted values:
 * - `0U`: Omit application timebase initialization and time-dependent behavior
 * - `1U`: Compile and initialize the SysTick-backed millisecond capability
 * @note Selecting `0U` leaves SysTick unconfigured by the Template and causes
 * App_DelayMs() to report @ref `DRIVER_STATUS_ERROR_STATE`
 * @note This switch does not allocate a general-purpose Timer or enable NVIC
 * delivery; SysTick is a dedicated Cortex-M3 exception
 */
#define APP_ENABLE_SYSTICK_TIMEBASE		(1U)

/**
 * @brief Defines the SysTick interrupt rate that represents milliseconds
 * @def APP_SYSTICK_TICK_HZ
 * @details
 * App_TimeInit() passes this frequency to SysTick_SetConfig(). At `1000UL`, one
 * interrupt represents one millisecond, so the software tick count can be
 * returned directly by App_TimeGetTickMs() without conversion or division.
 * Accepted values:
 * - `1000UL`: Required rate for the current one-tick-equals-one-millisecond contract
 * @note The configured AHB clock must be exactly divisible by this frequency
 * and must produce a SysTick reload period within the 24-bit hardware limit
 * @warning Changing this value requires corresponding time-unit conversion in
 * `app_time`; changing only the macro makes every `*Ms` API report the wrong unit
 */
#define APP_SYSTICK_TICK_HZ				(1000UL)

/**
 * @brief Defines the non-blocking demonstration task period in milliseconds
 * @def APP_MAIN_PERIOD_MS
 * @details
 * `main.c` compares the elapsed application time against this interval and
 * advances its previous-deadline tick by the same amount when the interval is
 * due. The macro changes application scheduling cadence without changing the
 * SysTick interrupt frequency.
 * Accepted values:
 * - `1UL..0x7FFFFFFFUL`: Non-zero wrap-safe scheduling interval
 * @note This macro has no effect when @ref `APP_ENABLE_SYSTICK_TIMEBASE` is `0U`
 * @note Replace the demonstration block in `main.c` with project behavior while
 * retaining this period only when the application needs it
 */
#define APP_MAIN_PERIOD_MS				(1000UL)

// ==================================================================================================== //
// Optional Timer Delay Configuration
// ==================================================================================================== //

#ifndef APP_ENABLE_TIMER_US_DELAY
/**
 * @brief Selects the optional dedicated-Timer microsecond delay capability
 * @def APP_ENABLE_TIMER_US_DELAY
 * @details
 * CMake normally defines this macro from `APP_ENABLE_TIMER_US_DELAY`. When it
 * is `1U`, the build adds the Timer Driver, app_delay exposes its microsecond
 * APIs, and App_Init() configures the dedicated delay Timer once. This fallback
 * definition supports builds that do not inject the CMake option.
 * Accepted values:
 * - `0U`: Exclude the Timer delay API and leave every general-purpose Timer untouched
 * - `1U`: Compile, initialize, and expose the dedicated polling-delay service
 * @note This service polls Timer completion; it does not enable Timer IRQ
 * sources or NVIC delivery
 */
#define APP_ENABLE_TIMER_US_DELAY		(0U)

#endif /* APP_ENABLE_TIMER_US_DELAY */

#if (APP_ENABLE_TIMER_US_DELAY == 1U)
/**
 * @brief Selects the Timer instance reserved for microsecond blocking delays
 * @def APP_DELAY_TIMER
 * @details
 * App_DelayTimerInit() passes this instance to TIM_ConfigForBlockingDelay(),
 * and App_DelayUs() passes it to TIM_BlockingDelayUs(). The Timer remains
 * configured between calls so a delay does not repeatedly configure hardware.
 * Accepted values:
 * - `TIM2`: Reserve Timer 2 for the delay service
 * - `TIM3`: Reserve Timer 3 for the delay service
 * - `TIM4`: Reserve Timer 4 for the delay service; Template default
 * @pre @ref `APP_DELAY_TIMER_CLOCK_MASK` must select the matching APB1 clock gate
 * @warning The application must not reuse or reconfigure the selected Timer
 * while the delay service owns it
 */
#define APP_DELAY_TIMER					TIM4

/**
 * @brief Selects the RCC APB1 clock gate for the dedicated delay Timer
 * @def APP_DELAY_TIMER_CLOCK_MASK
 * @details
 * App_DelayTimerInit() passes this mask to RCC_APB1_ClockEnable() before
 * configuring @ref `APP_DELAY_TIMER`. Keeping the gate explicit preserves RCC
 * ownership at the application-service boundary.
 * Accepted values:
 * - `RCC_APB1ENR_TIM2EN`: Clock gate paired with `TIM2`
 * - `RCC_APB1ENR_TIM3EN`: Clock gate paired with `TIM3`
 * - `RCC_APB1ENR_TIM4EN`: Clock gate paired with `TIM4`; Template default
 * @pre This mask must correspond exactly to @ref `APP_DELAY_TIMER`
 * @note The macro enables no clock by itself; Layer 3 App_Init() reaches the
 * Layer 2 delay service, which explicitly requests the Layer 1 RCC transaction
 */
#define APP_DELAY_TIMER_CLOCK_MASK		RCC_APB1ENR_TIM4EN

#endif /* APP_ENABLE_TIMER_US_DELAY */

/** @} */ // APP_Config

#endif /* APP_CONFIG_H_ */
