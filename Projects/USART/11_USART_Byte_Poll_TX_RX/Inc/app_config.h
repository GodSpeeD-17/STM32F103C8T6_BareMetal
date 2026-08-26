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
 * - Layer 1 - Hardware access: shared SysTick, RCC, Timer, GPIO, USART, and
 *   optional BSP Drivers
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
 * and publishes constants only. Layer 3 orders enabled services; Layer 2
 * services request their Layer 1 hardware transactions. Project 11's fixed
 * full-duplex UART mapping is a BSP capability; this file selects only
 * application behavior and never republishes board pin or USART mappings.
 */

// Header Guard
#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

/**
 * @brief Application-owned Template services
 * @defgroup App_Template Application Template
 */

/**
 * @brief Compile-time application feature and timing policy
 * @defgroup App_Config Application Configuration
 * @ingroup App_Template
 * @details
 * These macros select which timing capabilities are compiled, define the
 * application timebase contract, and map an optional dedicated Timer service
 * to its hardware instance and RCC clock gate. Defining a macro publishes
 * policy only; Layer 3 orders initialization while each Layer 2 service owns
 * its cohesive Layer 1 hardware transaction.
 * @{
 */

// ==================================================================================================== //
// SysTick Timebase Configuration
// ==================================================================================================== //

#ifndef APP_ENABLE_SYSTICK_TIMEBASE

/**
 * @brief Selects the SysTick-backed application millisecond timebase
 * @def APP_ENABLE_SYSTICK_TIMEBASE
 * @details
 * CMake normally defines this master switch from
 * `APP_ENABLE_SYSTICK_TIMEBASE`. When enabled, the build adds the shared
 * SysTick Driver, App_BootInit() starts the application time service, and
 * App_DelayMs() becomes operational. This fallback supports builds that do
 * not inject the option.
 * Accepted values:
 * - `0U`: Omit application timebase initialization and time-dependent behavior
 * - `1U`: Compile and initialize the SysTick-backed millisecond capability
 * @note Selecting `0U` leaves SysTick unconfigured by the Template and causes
 * App_DelayMs() to report @ref `DRIVER_STATUS_ERROR_STATE`
 * @note This switch does not allocate a general-purpose Timer or enable NVIC
 * delivery; SysTick is a dedicated Cortex-M3 exception
 */
#define APP_ENABLE_SYSTICK_TIMEBASE		(1U)

#endif /* APP_ENABLE_SYSTICK_TIMEBASE */

/**
 * @brief Defines the SysTick interrupt rate that represents milliseconds
 * @def APP_SYSTICK_TICK_HZ
 * @details
 * App_TimeInit() converts this frequency and the processor clock into the
 * register-semantic SysTick reload value. At `1000UL`, one interrupt
 * represents one millisecond, so App_TimeGetTickMs() requires no conversion.
 * Accepted values:
 * - `1000UL`: Required rate for the current one-tick-equals-one-millisecond contract
 * @note The configured AHB clock must be exactly divisible by this frequency
 * and must produce a SysTick reload period within the 24-bit hardware limit
 * @warning Changing this value requires corresponding time-unit conversion in
 * `app_time`; changing only the macro makes every `*Ms` API report the wrong unit
 */
#define APP_SYSTICK_TICK_HZ				(1000UL)

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
 * APIs, and App_BootInit() configures the dedicated delay Timer once. This fallback
 * definition supports builds that do not inject the CMake option.
 * Accepted values:
 * - `0U`: Exclude the Timer delay API and leave every general-purpose Timer untouched
 * - `1U`: Compile, initialize, and expose the dedicated polling-delay service
 * @note This service polls Timer completion; it does not enable Timer IRQ
 * sources or NVIC delivery
 */
#define APP_ENABLE_TIMER_US_DELAY		(0U)

#endif /* APP_ENABLE_TIMER_US_DELAY */

// ==================================================================================================== //
// Optional On-Board LED Configuration
// ==================================================================================================== //

#ifndef APP_ENABLE_ONBOARD_LED

/**
 * @brief Selects the optional BSP on-board LED initialization and fault indication
 * @def APP_ENABLE_ONBOARD_LED
 * @details
 * CMake normally defines this macro from `APP_ENABLE_ONBOARD_LED`. When it is
 * `1U`, App_BootInit() configures the board on-board LED GPIO and forces it
 * to a deterministic off state, and `main.c` compiles the fault-indication
 * call in App_ErrorHandler(). This fallback definition supports builds that
 * do not inject the CMake option.
 * Accepted values:
 * - `0U`: Leave the on-board LED GPIO untouched and preserve the error loop
 *   without a visible LED indication
 * - `1U`: Initialize the on-board LED GPIO, force it off, and compile the
 *   error-handler LED indication; Template default
 * @note Application code owns every BSP_OB_LED_Set() / BSP_OB_LED_Reset() /
 * BSP_OB_LED_Toggle() call; this switch does not make BSP own application
 * control flow
 * @note Project 11 always links BSP for its board UART capability; `0U` only
 * removes this separate LED behavior
 */
#define APP_ENABLE_ONBOARD_LED			(1U)

#endif /* APP_ENABLE_ONBOARD_LED */

// ==================================================================================================== //
// Optional Float and Debug Configuration
// ==================================================================================================== //

#ifndef APP_ENABLE_FLOAT

/**
 * @brief Selects application code that requires float or double arithmetic
 * @def APP_ENABLE_FLOAT
 * @details
 * CMake normally defines this policy from `APP_ENABLE_FLOAT`. It controls
 * whether the application may compile float-dependent behavior. When debug is
 * also enabled, Project 11 emits float-derived diagnostics and CMake links
 * newlib-nano's `%f` formatter; otherwise it does not add printf formatting.
 * Accepted values:
 * - `0U`: Exclude float-dependent application behavior
 * - `1U`: Permit float-dependent application behavior
 * @note This switch alone does not enable diagnostics or call any BSP API
 */
#define APP_ENABLE_FLOAT				(0U)

#endif /* APP_ENABLE_FLOAT */

#ifndef APP_ENABLE_DEBUG

/**
 * @brief Selects optional application debug behavior
 * @def APP_ENABLE_DEBUG
 * @details
 * CMake normally defines this policy from `APP_ENABLE_DEBUG`. When enabled,
 * App_BootInit() emits a USART readiness message after transport setup and
 * `main.c` emits a diagnostic after each successful echo, both through the
 * already configured BSP_USART_printf() transport. When disabled, neither
 * diagnostic path is compiled or changes the polling echo transaction.
 * Accepted values:
 * - `0U`: Exclude optional application debug behavior
 * - `1U`: Compile optional application debug behavior
 * @note This switch does not initialize the board UART; App_BootInit() owns
 * its clock-gate transaction and calls BSP_USART_Init()
 * @note `%f` formatting is linked only when this switch and
 * @ref `APP_ENABLE_FLOAT` are both `1U`
 */
#define APP_ENABLE_DEBUG				(0U)

#endif /* APP_ENABLE_DEBUG */

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
 * App_DelayTimerInit() passes this mask to `RCC_SetPeripheralClockState()`
 * with `RCC_APB1_BUS` and `DRIVER_STATUS_ON` before configuring
 * @ref `APP_DELAY_TIMER`. Keeping the gate explicit preserves RCC
 * ownership at the application-service boundary.
 * Accepted values:
 * - `RCC_APB1ENR_TIM2EN`: Clock gate paired with `TIM2`
 * - `RCC_APB1ENR_TIM3EN`: Clock gate paired with `TIM3`
 * - `RCC_APB1ENR_TIM4EN`: Clock gate paired with `TIM4`; Template default
 * @pre This mask must correspond exactly to @ref `APP_DELAY_TIMER`
 * @note The macro enables no clock by itself; Layer 3 App_BootInit() reaches the
 * Layer 2 delay service, which explicitly requests the Layer 1 RCC transaction
 */
#define APP_DELAY_TIMER_CLOCK_MASK		RCC_APB1ENR_TIM4EN

#endif /* APP_ENABLE_TIMER_US_DELAY */

/** @} */ // App_Config

#endif /* APP_CONFIG_H_ */
