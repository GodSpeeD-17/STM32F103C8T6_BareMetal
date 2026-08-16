/**
 * @file	main.h
 * @author	Shrey Shah
 * @brief	Timer PWM Polling Demonstration Configuration
 * @version	v1.0
 * @date	16-08-2026
 */

#ifndef MAIN_H_
#define MAIN_H_

// ==================================================================================================== //
//												Includes											//
// ==================================================================================================== //
#include "bsp.h"
#include "gpio.h"
#include "rcc.h"
#include "systick.h"
#include "timer_pwm.h"

// ==================================================================================================== //
//									Application PWM Configuration									//
// ==================================================================================================== //

/** @brief Timer instance used by the PWM demonstration @def APP_PWM_TIMER */
#define APP_PWM_TIMER					(TIM2)
/** @brief Application-owned Timer clock gate @def APP_PWM_TIMER_CLOCK_MASK */
#define APP_PWM_TIMER_CLOCK_MASK		(RCC_APB1ENR_TIM2EN)
/** @brief Application-owned GPIO and AFIO clock gates @def APP_PWM_GPIO_CLOCK_MASK */
#define APP_PWM_GPIO_CLOCK_MASK			(RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN)
/** @brief GPIO port carrying default-remap TIM2 channel 4 @def APP_PWM_GPIO_PORT */
#define APP_PWM_GPIO_PORT				(GPIOA)
/** @brief PA3 carrying default-remap TIM2 channel 4 @def APP_PWM_GPIO_PIN_MASK */
#define APP_PWM_GPIO_PIN_MASK			((gpio_pin_t) GPIO_PIN_3)
/** @brief TIM2 channel 4 exercised by the demonstration @def APP_PWM_CHANNEL_MASK */
#define APP_PWM_CHANNEL_MASK			((tim_channel_t) TIMx_CHANNEL_4)
/** @brief PWM mode applied to the demonstration channel @def APP_PWM_CHANNEL_MODE */
#define APP_PWM_CHANNEL_MODE			(TIMx_CHANNEL_MODE_PWM1)
/** @brief Active polarity applied to the demonstration channel @def APP_PWM_CHANNEL_POLARITY */
#define APP_PWM_CHANNEL_POLARITY		(TIMx_CHANNEL_POLARITY_HIGH)
/** @brief CCR preload policy applied to the demonstration channel @def APP_PWM_CHANNEL_PRELOAD */
#define APP_PWM_CHANNEL_PRELOAD			(TIMx_CHANNEL_OC_PRELOAD_ENABLE)
/** @brief Output-compare fast-mode policy applied to the demonstration channel @def APP_PWM_CHANNEL_FAST */
#define APP_PWM_CHANNEL_FAST			(TIMx_CHANNEL_OC_FAST_DISABLE)
/** @brief Timer prescaler producing a 1 MHz counter tick from 72 MHz @def APP_PWM_PRESCALER */
#define APP_PWM_PRESCALER				((tim_prescaler_t) 71U)
/** @brief Timer auto-reload producing a 1 kHz PWM period @def APP_PWM_AUTO_RELOAD */
#define APP_PWM_AUTO_RELOAD				((tim_auto_reload_t) 999U)
/** @brief PWM ramp increment in permille units @def APP_PWM_DUTY_STEP */
#define APP_PWM_DUTY_STEP				((tim_pwm_duty_cycle_t) 1U)
/** @brief Delay between PWM ramp updates in milliseconds @def APP_PWM_STEP_DELAY_MS */
#define APP_PWM_STEP_DELAY_MS			((uint32_t) 20UL)
/** @brief Delay between completed ramps in milliseconds @def APP_PWM_LOOP_DELAY_MS */
#define APP_PWM_LOOP_DELAY_MS			((uint32_t) 1000UL)

#endif /* MAIN_H_ */
