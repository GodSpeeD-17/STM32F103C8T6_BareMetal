#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

/** @brief Enables the SysTick-backed application millisecond timebase @def APP_ENABLE_SYSTICK_TIMEBASE */
#define APP_ENABLE_SYSTICK_TIMEBASE				(1U)
/** @brief Application SysTick interrupt frequency in hertz @def APP_SYSTICK_TICK_HZ */
#define APP_SYSTICK_TICK_HZ						(1000UL)
/** @brief Demonstration application scheduling period in milliseconds @def APP_MAIN_PERIOD_MS */
#define APP_MAIN_PERIOD_MS						(1000UL)

/* CMake defines this option so disabled projects do not compile Timer sources. */
#ifndef APP_ENABLE_TIMER_US_DELAY
/** @brief Enables the optional TIM4 microsecond blocking-delay service @def APP_ENABLE_TIMER_US_DELAY */
#define APP_ENABLE_TIMER_US_DELAY				(0U)
#endif /* APP_ENABLE_TIMER_US_DELAY */

#if (APP_ENABLE_TIMER_US_DELAY == 1U)
/** @brief Dedicated Timer instance owned by the optional delay service @def APP_DELAY_TIMER */
#define APP_DELAY_TIMER							TIM4
/** @brief APB1 clock mask for the dedicated delay Timer @def APP_DELAY_TIMER_CLOCK_MASK */
#define APP_DELAY_TIMER_CLOCK_MASK				RCC_APB1ENR_TIM4EN
#endif /* APP_ENABLE_TIMER_US_DELAY */

#endif /* APP_CONFIG_H_ */
