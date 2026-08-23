/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the GPIO push-button IRQ demo application behavior
 * @version	v1.0
 * @date	22-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 2 `app_time`/`app_delay` and Layer 1 GPIO/BSP/NVIC Drivers
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * This project configures an externally pulled-up push button as a GPIO-backed
 * EXTI falling-edge interrupt source. The main loop toggles the Blue Pill
 * on-board LED as a heartbeat, while the push-button IRQ toggles the red LED
 * after a debounce guard period.
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
#include "app_time.h"
#include "bsp.h"
#include "gpio.h"
#include "gpio_irq.h"
#include "nvic.h"
#include "rcc.h"

// ==================================================================================================== //
// Private Defines
// ==================================================================================================== //

/**
 * @brief GPIO 03_PB_IRQ project-local timing and GPIO configuration
 * @details
 * The push button is connected to an externally pulled-up input, so the GPIO IRQ
 * input configuration uses @ref `GPIO_PIN_CONFIG_INPUT_FLOATING` and the EXTI
 * trigger uses @ref `GPIO_IRQ_TRIGGER_FALLING`.
 * @{
 */
/** @brief Main-loop heartbeat delay in milliseconds @def LOOP_DELAY_MS */
#define LOOP_DELAY_MS							((uint32_t) 1000UL)
/** @brief Push-button debounce guard time in milliseconds @def BUTTON_DEBOUNCE_DELAY_MS */
#define BUTTON_DEBOUNCE_DELAY_MS				((uint32_t) 50UL)
/** @brief Red LED GPIO port instance @def RED_LED_PORT */
#define RED_LED_PORT							GPIOA
/** @brief Red LED GPIO pin mask @def RED_LED_PIN */
#define RED_LED_PIN								GPIO_PIN_2
/** @brief Yellow LED GPIO port instance @def YELLOW_LED_PORT */
#define YELLOW_LED_PORT							GPIOA
/** @brief Yellow LED GPIO pin mask @def YELLOW_LED_PIN */
#define YELLOW_LED_PIN							GPIO_PIN_3
/** @brief Push-button GPIO port instance @def PUSH_BUTTON_PORT */
#define PUSH_BUTTON_PORT						GPIOA
/** @brief Push-button GPIO pin mask @def PUSH_BUTTON_PIN */
#define PUSH_BUTTON_PIN							GPIO_PIN_1
/** @brief Push-button GPIO input configuration @def PUSH_BUTTON_INPUT_CONFIG */
#define PUSH_BUTTON_INPUT_CONFIG				GPIO_PIN_CONFIG_INPUT_FLOATING
/** @brief Push-button EXTI trigger selector @def PUSH_BUTTON_IRQ_TRIGGER */
#define PUSH_BUTTON_IRQ_TRIGGER					GPIO_IRQ_TRIGGER_FALLING
/** @brief Application-owned GPIO port clock gate shared by every pin above @def APP_GPIO_CLOCK_MASK */
#define APP_GPIO_CLOCK_MASK						(RCC_APB2ENR_IOPAEN)
/** @} */

// ==================================================================================================== //
// Local Variables
// ==================================================================================================== //

/** @brief Last accepted push-button IRQ timestamp in milliseconds */
static volatile uint32_t buttonLastIrqTick = 0x00000000UL;

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

/**
 * @brief Enters the project error indication loop
 * @details
 * App_Init() already configures and forces off the BSP on-board LED, so this
 * handler only needs to set it once. Used only when project-local peripheral
 * setup fails before the main demo loop.
 */
static void App_ErrorHandler(void)
{
	BSP_OB_LED_Set();
	while (1)
	{
		// Stay here so the on-board LED remains the visible error indicator.
	}
}

/**
 * @brief Initializes project peripherals used by the demo
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Project initialization completed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One project GPIO mapping was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal staged-image update failed.
 */
static driver_status_t App_Init(void)
{
	//! The application explicitly owns the GPIOA port clock gate shared by the LEDs and push button.
	ASSERT_DRIVER_STATUS
(
	RCC_SetPeripheralClockState
	(
		RCC_APB2_BUS,
		APP_GPIO_CLOCK_MASK,
		DRIVER_STATUS_ON
	)
);
	ASSERT_DRIVER_STATUS(GPIO_LED_Init(RED_LED_PORT, (RED_LED_PIN | YELLOW_LED_PIN)));
	ASSERT_DRIVER_STATUS(GPIO_PinReset(RED_LED_PORT, (RED_LED_PIN | YELLOW_LED_PIN)));
	ASSERT_DRIVER_STATUS
	(
		GPIO_IRQ_Init
		(
			PUSH_BUTTON_PORT,
			PUSH_BUTTON_PIN,
			PUSH_BUTTON_INPUT_CONFIG,
			PUSH_BUTTON_IRQ_TRIGGER
		)
	);
	ASSERT_DRIVER_STATUS(NVIC_ClearPendingIRQ(EXTI1_IRQn));
	ASSERT_DRIVER_STATUS(NVIC_EnableIRQ(EXTI1_IRQn));
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Returns whether the push-button IRQ event is outside the debounce window
 * @param[in] currentTick Current application tick count in milliseconds
 * @returns Debounce decision
 * @retval - @ref `DRIVER_STATUS_ON`: The IRQ event is accepted.
 * @retval - @ref `DRIVER_STATUS_OFF`: The IRQ event is ignored as bounce.
 */
__STATIC_FORCEINLINE driver_status_t App_PushButtonIRQDebounceAccepted(const uint32_t currentTick)
{
	return (((currentTick - buttonLastIrqTick) > BUTTON_DEBOUNCE_DELAY_MS) ? DRIVER_STATUS_ON : DRIVER_STATUS_OFF);
}

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	if (App_Init() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}

	while (1)
	{
		BSP_OB_LED_Toggle();
		(void) App_DelayMs(LOOP_DELAY_MS);
	}
}

// ==================================================================================================== //
// Interrupt Handlers
// ==================================================================================================== //

/**
 * @brief Handles EXTI line 1 interrupts from the project push button
 * @details
 * The pending bit is acknowledged only after the line is confirmed pending.
 * A software debounce guard prevents repeated toggles caused by mechanical
 * switch bounce.
 */
void EXTI1_IRQHandler(void)
{
	const uint32_t currentTick = App_TimeGetTickMs();

	if (GPIO_IRQ_IsTriggered(PUSH_BUTTON_PIN) == DRIVER_STATUS_ON)
	{
		if (App_PushButtonIRQDebounceAccepted(currentTick) == DRIVER_STATUS_ON)
		{
			buttonLastIrqTick = currentTick;
			(void) GPIO_PinToggle(RED_LED_PORT, RED_LED_PIN);
		}

		(void) GPIO_IRQ_Ack(PUSH_BUTTON_PIN);
	}
}
