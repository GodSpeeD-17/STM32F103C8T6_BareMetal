/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the Timer PWM polling demo application behavior
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 2 `app_delay` and Layer 1 Timer/GPIO/BSP Drivers
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * Demonstrates TIM2 channel 4 PWM on PA3 without a heap, handle, frequency
 * registry, or GPIO ownership inside the Timer driver. The application owns
 * RCC, GPIO/AFIO, Timer base configuration, PWM channel configuration,
 * channel output-enable state, and final counter start order.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * Application behavior belongs here. Processor startup, clock configuration,
 * and service initialization do not.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "app_delay.h"
#include "bsp_gpio.h"
#include "gpio.h"
#include "rcc.h"
#include "timer_pwm.h"

// ==================================================================================================== //
// Private Defines
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

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

/**
 * @brief Enters the application error-indication loop
 * @details
 * App_Init() already configures and forces off the BSP on-board LED, so this
 * handler only needs to set it once.
 */
static void App_ErrorHandler(void)
{
	BSP_OB_LED_Set();
	while (1)
	{
		//! Preserve the visible active-low error indication until reset.
	}
}

/**
 * @brief Configures application-owned PA3 routing for TIM2 channel 4
 * @returns @ref driver_status_t "GPIO configuration status"
 */
static driver_status_t App_ConfigPWMGPIO(void)
{
	//! The application explicitly owns both the GPIO-port and AFIO clock gates.
	ASSERT_DRIVER_STATUS
(
	RCC_SetPeripheralClockState
	(
		RCC_APB2_BUS,
		APP_PWM_GPIO_CLOCK_MASK,
		DRIVER_STATUS_ON
	)
);
	return GPIO_SetPinModeConfig
	(
		APP_PWM_GPIO_PORT,
		APP_PWM_GPIO_PIN_MASK,
		GPIO_PIN_MODE_OUTPUT_10MHZ,
		GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL
	);
}

/**
 * @brief Configures the Timer base followed by TIM2 channel 4 PWM
 * @returns @ref driver_status_t "PWM initialization status"
 */
static driver_status_t App_ConfigPWM(void)
{
	const tim_config_t timerConfig =
	{
		.timebase =
		{
			.prescaler = APP_PWM_PRESCALER,
			.auto_reload = APP_PWM_AUTO_RELOAD,
			.initial_count = 0U
		},
		.counter =
		{
			.digital_filter_clock_division = TIMx_DIGITAL_FILTER_CLOCK_DIV_1,
			.alignment = TIMx_MODE_NORMAL,
			.direction = TIMx_DIR_COUNT_UP,
			.one_pulse = TIMx_OPM_DISABLE,
			.auto_reload_preload = TIMx_ARPE_ENABLE,
			.update_source = TIMx_UPDATE_SOURCE_OVERFLOW_UNDERFLOW_ONLY
		}
	};

	//! The application owns the Timer clock gate and complete base timebase.
	ASSERT_DRIVER_STATUS
(
	RCC_SetPeripheralClockState
	(
		RCC_APB1_BUS,
		APP_PWM_TIMER_CLOCK_MASK,
		DRIVER_STATUS_ON
	)
);
	ASSERT_DRIVER_STATUS(TIM_Config(APP_PWM_TIMER, &timerConfig));

	//! Configure TIM2 channel 4 only after the Timer base is valid.
	ASSERT_DRIVER_STATUS
	(
		TIM_ConfigPWM
		(
			APP_PWM_TIMER,
			APP_PWM_CHANNEL_MASK,
			APP_PWM_CHANNEL_MODE,
			APP_PWM_CHANNEL_POLARITY,
			APP_PWM_CHANNEL_PRELOAD,
			APP_PWM_CHANNEL_FAST
		)
	);

	//! Duty remains a separate lifecycle operation from channel mode configuration.
	ASSERT_DRIVER_STATUS(TIM_SetPWMDuty(APP_PWM_TIMER, TIMx_CHANNEL_4, TIM_PWM_DUTY_CYCLE_MIN));
	//! Connect the PA3 PWM channel while CEN remains disabled.
	ASSERT_DRIVER_STATUS(TIM_SetPWMOutputEnable(APP_PWM_TIMER, APP_PWM_CHANNEL_MASK, DRIVER_STATUS_ON));

	//! Starting the shared counter is the final independent Timer operation.
	return TIM_SetOperationState(APP_PWM_TIMER, DRIVER_STATUS_ON);
}

/** @brief Programs one duty value into the TIM2 channel 4 preload */
static driver_status_t App_SetDutyCycle(const tim_pwm_duty_cycle_t dutyCycle)
{
	return TIM_SetPWMDuty(APP_PWM_TIMER, TIMx_CHANNEL_4, dutyCycle);
}

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	tim_pwm_duty_cycle_t dutyCycle = TIM_PWM_DUTY_CYCLE_MIN;

	//! Physical output configuration is intentionally outside the Timer PWM driver.
	if (App_ConfigPWMGPIO() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}
	if (App_ConfigPWM() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}

	//! Infinite Loop
	while (1)
	{
		//! Increase the Duty Cycle from 0% to 100% in APP_PWM_DUTY_STEP increments, then decrease back to 0%.
		for (dutyCycle = TIM_PWM_DUTY_CYCLE_MIN; dutyCycle < TIM_PWM_DUTY_CYCLE_MAX; dutyCycle = (tim_pwm_duty_cycle_t) (dutyCycle + APP_PWM_DUTY_STEP))
		{
			if (App_SetDutyCycle(dutyCycle) != DRIVER_STATUS_SUCCESS)
			{
				App_ErrorHandler();
			}
			if (App_DelayMs(APP_PWM_STEP_DELAY_MS) != DRIVER_STATUS_SUCCESS)
			{
				App_ErrorHandler();
			}
		}
		if (App_SetDutyCycle(TIM_PWM_DUTY_CYCLE_MAX) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}

		//! Toggle the LED to indicate a completed ramp before the next ramp begins.
		BSP_OB_LED_Toggle();

		//! Decrease the Duty Cycle from 100% to 0% in APP_PWM_DUTY_STEP decrements, then increase back to 100%.
		for (dutyCycle = TIM_PWM_DUTY_CYCLE_MAX; dutyCycle > TIM_PWM_DUTY_CYCLE_MIN; dutyCycle = (tim_pwm_duty_cycle_t) (dutyCycle - APP_PWM_DUTY_STEP))
		{
			if (App_SetDutyCycle(dutyCycle) != DRIVER_STATUS_SUCCESS)
			{
				App_ErrorHandler();
			}
			if (App_DelayMs(APP_PWM_STEP_DELAY_MS) != DRIVER_STATUS_SUCCESS)
			{
				App_ErrorHandler();
			}
		}
		if (App_SetDutyCycle(TIM_PWM_DUTY_CYCLE_MIN) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}

		//! Toggle the LED to indicate a completed ramp before the next ramp begins.
		BSP_OB_LED_Toggle();

		//! Block for a moment before the next ramp begins to allow the user to see the completed ramp.
		if (App_DelayMs(APP_PWM_LOOP_DELAY_MS) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}
	}
}
