// Header Guard
#ifndef MAIN_H_
#define MAIN_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "bsp.h"
#include "timer.h"

// ==================================================================================================== //
//										Application Constants										//
// ==================================================================================================== //

/** @brief TIM3 counter tick frequency used by the IRQ demo @def APP_TIMER_TICK_FREQUENCY_HZ */
#define APP_TIMER_TICK_FREQUENCY_HZ		((tim_frequency_t) 10000UL)
/** @brief TIM3 auto-reload value producing a one-second update period @def APP_TIMER_AUTO_RELOAD */
#define APP_TIMER_AUTO_RELOAD			((tim_auto_reload_t) 9999U)

void TIM3_IRQHandler(void);

#endif /* MAIN_H_ */
