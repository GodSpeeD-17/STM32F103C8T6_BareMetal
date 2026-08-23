/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the Timer PWM update-IRQ demo application behavior
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 1 Timer/GPIO/BSP/NVIC Drivers
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * Demonstrates TIM2 channel 4 PWM on PA3 paired with the TIM2 update-event
 * interrupt. The ISR only signals that a PWM period elapsed by setting one
 * flag; every ramp decision (direction, clamping) and the sole
 * TIM_SetPWMDuty() call live in the main loop. This keeps the ISR reduced to
 * its one responsibility - a timing signal - and keeps all ramp policy in one
 * place, matching the deferred-work pattern already used by
 * `Projects/Timer/05_Timer_IRQ`.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * Application behavior belongs here. Processor startup, clock configuration,
 * and service initialization do not.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "bsp.h"
#include "gpio.h"
#include "nvic.h"
#include "rcc.h"
#include "stm32f1xx.h"
#include "timer_pwm.h"

// ==================================================================================================== //
// Private Defines
// ==================================================================================================== //

/** @brief Timer instance used by the PWM-IRQ demonstration @def APP_PWM_TIMER */
#define APP_PWM_TIMER					(TIM2)
/** @brief Application-owned Timer clock gate @def APP_PWM_TIMER_CLOCK_MASK */
#define APP_PWM_TIMER_CLOCK_MASK		(RCC_APB1ENR_TIM2EN)
/** @brief NVIC line delivering TIM2 update-event interrupts @def APP_PWM_TIMER_IRQn */
#define APP_PWM_TIMER_IRQn				(TIM2_IRQn)
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
#define APP_PWM_PRESCALER				((tim_prescaler_t) 719U)
/** @brief Timer auto-reload producing a 1 kHz PWM period @def APP_PWM_AUTO_RELOAD */
#define APP_PWM_AUTO_RELOAD				((tim_auto_reload_t) 999U)
/** @brief PWM ramp increment in permille units applied once per elapsed period @def APP_PWM_DUTY_STEP */
#define APP_PWM_DUTY_STEP				((tim_pwm_duty_cycle_t) 1U)

// ==================================================================================================== //
// Local Variables
// ==================================================================================================== //
/** @brief Set by TIM2_IRQHandler() once per elapsed PWM period; cleared by the main loop */
static volatile uint8_t isDutyStepRequired = 0U;

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

/**
 * @brief Enters the application error-indication loop
 * @details
 * App_Init() already configures and forces off the BSP on-board LED, so this
 * handler only needs to set it once. Used to prevent return into an
 * unacknowledged or incorrectly configured IRQ path.
 */
static void App_ErrorHandler(void)
{
	//! Indicate
	OB_LED_Set();

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
	ASSERT_DRIVER_STATUS(RCC_SetAPB2ClockState(APP_PWM_GPIO_CLOCK_MASK, DRIVER_STATUS_ON));
	return GPIO_SetPinModeConfig
	(
		APP_PWM_GPIO_PORT,
		APP_PWM_GPIO_PIN_MASK,
		GPIO_PIN_MODE_OUTPUT_10MHZ,
		GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL
	);
}

/**
 * @brief Configures TIM2 channel 4 PWM and its update-event interrupt
 * @details
 * Applies the same Timer base and PWM channel configuration as the polling
 * demonstration, then additionally enables the Timer update-request source,
 * arms the dedicated NVIC line, and only then starts the shared counter so no
 * interrupt can arrive before TIM2_IRQHandler() is ready to service it.
 * @returns @ref driver_status_t "PWM-IRQ initialization status"
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
	ASSERT_DRIVER_STATUS(RCC_SetAPB1ClockState(APP_PWM_TIMER_CLOCK_MASK, DRIVER_STATUS_ON));
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

	//! Explicitly enable the Timer update request before enabling its independently owned NVIC line.
	ASSERT_DRIVER_STATUS(TIM_SetIRQSources(APP_PWM_TIMER, TIMx_IRQ_SOURCE_UPDATE, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(NVIC_ClearPendingIRQ(APP_PWM_TIMER_IRQn));
	ASSERT_DRIVER_STATUS(NVIC_EnableIRQ(APP_PWM_TIMER_IRQn));

	//! Starting the shared counter is the final independent Timer operation.
	return TIM_SetOperationState(APP_PWM_TIMER, DRIVER_STATUS_ON);
}

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	// Local Variables
	tim_pwm_duty_cycle_t dutyCycle = TIM_PWM_DUTY_CYCLE_MIN;
	int16_t rampDirection = +1;

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
		//! PWM IRQ Triggered?
		if (isDutyStepRequired != 0U)
		{
			//! Acknowledge the IRQ
			isDutyStepRequired = 0U;
			//! Update the Duty Cycle
			dutyCycle = (tim_pwm_duty_cycle_t) (dutyCycle + (rampDirection * (int16_t) APP_PWM_DUTY_STEP));
			
			//! Clamp the duty cycle to the valid range and reverse ramp direction if a limit is reached.
			if (dutyCycle >= TIM_PWM_DUTY_CYCLE_MAX)
			{
				dutyCycle = TIM_PWM_DUTY_CYCLE_MAX;
				rampDirection = -1;
			}
			else if (dutyCycle <= TIM_PWM_DUTY_CYCLE_MIN)
			{
				dutyCycle = TIM_PWM_DUTY_CYCLE_MIN;
				rampDirection = +1;
			}

			//! Update the duty cycle
			if (TIM_SetPWMDuty(APP_PWM_TIMER, APP_PWM_CHANNEL_MASK, dutyCycle) != DRIVER_STATUS_SUCCESS)
			{
				App_ErrorHandler();
			}
		}
		else
		{
			//! Sleep until the next TIM2 update interrupt produces work for this loop.
			__WFI();
		}
	}
}

// ==================================================================================================== //
// Interrupt Handlers
// ==================================================================================================== //

/**
 * @brief Handles TIM2 update interrupts
 * @details
 * Reads the public pending-event mask, services only the update flag by
 * setting the deferred-work flag consumed by main(), and acknowledges that
 * flag through the public W0C-aware Timer path. No ramp arithmetic and no
 * TIM_SetPWMDuty() call happen here; a failure is terminal so execution
 * cannot return into an unacknowledged IRQ storm.
 */
void TIM2_IRQHandler(void)
{
	tim_event_flag_t irqEvents = TIMx_IRQ_EVENT_NONE;
	//! Read the public pending-event mask
	if (TIM_GetIRQEvents(APP_PWM_TIMER, &irqEvents) != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}
	//! Service only the update flag
	if ((irqEvents & TIMx_IRQ_EVENT_UPDATE) != TIMx_IRQ_EVENT_NONE)
	{
		//! Ask the main loop to compute and program the next duty step.
		isDutyStepRequired = 1U;

		//! Acknowledge only the serviced update flag and preserve unrelated Timer flags.
		if (TIM_AckIRQEvents(APP_PWM_TIMER, TIMx_IRQ_EVENT_UPDATE) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}
	}
}
