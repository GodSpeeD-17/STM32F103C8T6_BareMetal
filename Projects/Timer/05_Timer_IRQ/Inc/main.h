// Header Guard
#ifndef MAIN
#define MAIN

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "bsp.h"
#include "nvic.h"
#include "rcc.h"
#include "timer.h"
#include "gpio.h"

// ==================================================================================================== //
//										Application Constants										//
// ==================================================================================================== //

/** @brief Application GPIO Port @def APP_GPIO_LED_PORT */
#define APP_GPIO_LED_PORT			(GPIOA)
/** @brief Application GPIO Pin @def APP_GPIO_LED_PIN */
#define APP_GPIO_LED_PIN			(GPIO_PIN_3)
/** @brief Application Timer @def APP_TIMER */
#define APP_TIMER					(TIM3)
/** @brief Application Timer Clock Enable Mask @def APP_TIMER_ENABLE_MASK */
#define APP_TIMER_ENABLE_MASK		(RCC_APB1ENR_TIM3EN)
/** @brief Application Timer Interrupt Request Number @def APP_TIMER_IRQn */
#define APP_TIMER_IRQn				(TIM3_IRQn)
/** @brief Application Timer Prescaler @def APP_TIMER_PRESCALER */
#define APP_TIMER_PRESCALER			((tim_prescaler_t) 7199U)
/** @brief Application Timer Auto-Reload @def APP_TIMER_AUTO_RELOAD */
#define APP_TIMER_AUTO_RELOAD		((tim_auto_reload_t) 9999U)
/** @brief Application Timer Interrupt Handler @def APP_TIMER_IRQHandler */
#define APP_TIMER_IRQHandler		(TIM3_IRQHandler)

void APP_TIMER_IRQHandler(void);

#endif /* MAIN */
