// Header Guard
#ifndef MAIN_H_
#define MAIN_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "bsp.h"
#include "nvic.h"
#include "timer.h"

// ==================================================================================================== //
//										Application Constants										//
// ==================================================================================================== //

/** @brief TIM3 prescaler producing a 10 kHz counter tick from the configured 72 MHz Timer clock @def APP_TIMER_PRESCALER */
#define APP_TIMER_PRESCALER			((tim_prescaler_t) 7199U)
/** @brief TIM3 auto-reload value producing a one-second update period @def APP_TIMER_AUTO_RELOAD */
#define APP_TIMER_AUTO_RELOAD		((tim_auto_reload_t) 9999U)

void TIM3_IRQHandler(void);

#endif /* MAIN_H_ */
