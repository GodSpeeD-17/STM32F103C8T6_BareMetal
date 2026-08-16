/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Timer PWM Polling Demonstration
 * @version	v1.0
 * @date	16-08-2026
 *
 * @details
 * Demonstrates two channels sharing one Timer timebase without a heap, handle,
 * frequency registry, or GPIO ownership inside the Timer driver. The
 * application owns RCC, GPIO/AFIO, Timer base configuration, PWM channel
 * configuration, channel output-enable state, and final counter start order.
 */

// ==================================================================================================== //
//												Includes											//
// ==================================================================================================== //
#include "main.h"

// ==================================================================================================== //
//										Local Helpers										//
// ==================================================================================================== //

/** @brief Enters the application error-indication loop */
static void App_ErrorHandler(void)
{
	OB_LED_Set();
	while (1)
	{
		//! Preserve the visible active-low error indication until reset.
	}
}

/**
 * @brief Configures application-owned GPIO routing for TIM2 channels 3 and 4
 * @returns @ref driver_status_t "GPIO configuration status"
 */
static driver_status_t App_ConfigPWMGPIO(void)
{
	//! The application explicitly owns both the GPIO-port and AFIO clock gates.
	ASSERT_DRIVER_STATUS(RCC_APB2_ClockEnable(APP_PWM_GPIO_CLOCK_MASK));
	return GPIO_SetPinModeConfig
	(
		APP_PWM_GPIO_PORT,
		APP_PWM_GPIO_PIN_MASK,
		GPIO_PIN_MODE_OUTPUT_10MHZ,
		GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL
	);
}

/**
 * @brief Configures the shared Timer base followed by both PWM channels
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
	ASSERT_DRIVER_STATUS(RCC_APB1_ClockEnable(APP_PWM_TIMER_CLOCK_MASK));
	ASSERT_DRIVER_STATUS(TIM_Config(APP_PWM_TIMER, &timerConfig));

	//! Configure both channels coherently only after the shared Timer base is valid.
	ASSERT_DRIVER_STATUS
	(
		TIM_ConfigPWMChannels
		(
			APP_PWM_TIMER,
			APP_PWM_CHANNEL_MASK,
			TIMx_CHANNEL_MODE_PWM1,
			TIMx_CHANNEL_POLARITY_HIGH
		)
	);

	//! Duty remains a separate lifecycle operation from channel mode configuration.
	ASSERT_DRIVER_STATUS(TIM_SetPWMChannelDutyCycle(APP_PWM_TIMER, TIMx_CHANNEL_3, TIM_PWM_DUTY_CYCLE_MIN));
	ASSERT_DRIVER_STATUS(TIM_SetPWMChannelDutyCycle(APP_PWM_TIMER, TIMx_CHANNEL_4, TIM_PWM_DUTY_CYCLE_MIN));

	//! Enable both channel outputs coherently while CEN remains disabled.
	ASSERT_DRIVER_STATUS(TIM_SetPWMChannelOutputEnableState(APP_PWM_TIMER, APP_PWM_CHANNEL_MASK, DRIVER_STATUS_ON));

	//! Starting the shared counter is the final independent Timer operation.
	return TIM_SetOperationState(APP_PWM_TIMER, DRIVER_STATUS_ON);
}

/** @brief Programs one duty value into both PWM channel preloads */
static driver_status_t App_SetDutyCycle(const tim_pwm_duty_cycle_t dutyCycle)
{
	ASSERT_DRIVER_STATUS(TIM_SetPWMChannelDutyCycle(APP_PWM_TIMER, TIMx_CHANNEL_3, dutyCycle));
	return TIM_SetPWMChannelDutyCycle(APP_PWM_TIMER, TIMx_CHANNEL_4, dutyCycle);
}

/**
 * @brief Stops and deconfigures both PWM channels without changing GPIO/RCC ownership
 * @returns @ref driver_status_t "PWM deconfiguration status"
 */
static driver_status_t App_DeConfigPWM(void)
{
	//! Stop the shared counter before disconnecting and resetting either channel.
	ASSERT_DRIVER_STATUS(TIM_SetOperationState(APP_PWM_TIMER, DRIVER_STATUS_OFF));
	ASSERT_DRIVER_STATUS(TIM_SetPWMChannelOutputEnableState(APP_PWM_TIMER, APP_PWM_CHANNEL_MASK, DRIVER_STATUS_OFF));
	return TIM_DeConfigPWMChannels(APP_PWM_TIMER, APP_PWM_CHANNEL_MASK);
}

// ==================================================================================================== //
//										Main Entry Point										//
// ==================================================================================================== //

/**
 * @brief Runs the two-channel Timer PWM duty ramp
 * @returns Process status
 * @retval 0 The function returned normally, which is not expected
 */
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

	while (1)
	{
		for
		(
			dutyCycle = TIM_PWM_DUTY_CYCLE_MIN;
			dutyCycle < TIM_PWM_DUTY_CYCLE_MAX;
			dutyCycle = (tim_pwm_duty_cycle_t) (dutyCycle + APP_PWM_DUTY_STEP)
		)
		{
			if (App_SetDutyCycle(dutyCycle) != DRIVER_STATUS_SUCCESS)
			{
				App_ErrorHandler();
			}
			if (TIM_BlockingDelayMs(DELAY_TIMER, APP_PWM_STEP_DELAY_MS) != DRIVER_STATUS_SUCCESS)
			{
				App_ErrorHandler();
			}
		}
		if (App_SetDutyCycle(TIM_PWM_DUTY_CYCLE_MAX) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}
		OB_LED_Toggle();

		for
		(
			dutyCycle = TIM_PWM_DUTY_CYCLE_MAX;
			dutyCycle > TIM_PWM_DUTY_CYCLE_MIN;
			dutyCycle = (tim_pwm_duty_cycle_t) (dutyCycle - APP_PWM_DUTY_STEP)
		)
		{
			if (App_SetDutyCycle(dutyCycle) != DRIVER_STATUS_SUCCESS)
			{
				App_ErrorHandler();
			}
			if (TIM_BlockingDelayMs(DELAY_TIMER, APP_PWM_STEP_DELAY_MS) != DRIVER_STATUS_SUCCESS)
			{
				App_ErrorHandler();
			}
		}
		if (App_SetDutyCycle(TIM_PWM_DUTY_CYCLE_MIN) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}
		OB_LED_Toggle();
		if (TIM_BlockingDelayMs(DELAY_TIMER, APP_PWM_LOOP_DELAY_MS) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}

		//! Exercise the explicit stop/deconfigure/reconfigure lifecycle at zero duty.
		if (App_DeConfigPWM() != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}
		if (App_ConfigPWM() != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}
	}

	return 0;
}
