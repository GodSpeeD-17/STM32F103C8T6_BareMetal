/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	GPIO Push-Button IRQ Demo
 * @version	v1.0
 * @date	07-06-2026
 *
 * @details
 * This project configures an externally pulled-up push button as a GPIO-backed
 * EXTI falling-edge interrupt source. The main loop toggles the Blue Pill
 * on-board LED as a heartbeat, while the push-button IRQ toggles the red LED
 * after a debounce guard period.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "main.h"

// ==================================================================================================== //
//											Local Variables												//
// ==================================================================================================== //

/** @brief Last accepted push-button IRQ timestamp in milliseconds */
static volatile uint32_t buttonLastIrqTick = 0x00000000UL;

// ==================================================================================================== //
//											Local Helpers												//
// ==================================================================================================== //

/**
 * @brief Enters the project error indication loop
 * @details
 * The BSP on-board LED is active-low; @ref `OB_LED_Set` turns it on. This
 * handler is used only when initialization fails before the main demo loop.
 */
static void APP_ErrorHandler(void)
{
	OB_LED_Set();
	while(1)
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
static driver_status_t APP_Init(void)
{
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
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Returns whether the push-button IRQ event is outside the debounce window
 * @param[in] currentTick Current project tick count in milliseconds
 * @returns Debounce decision
 * @retval - @ref `DRIVER_STATUS_ON`: The IRQ event is accepted.
 * @retval - @ref `DRIVER_STATUS_OFF`: The IRQ event is ignored as bounce.
 */
__STATIC_FORCEINLINE driver_status_t APP_PushButtonIRQDebounceAccepted(const uint32_t currentTick)
{
	return (((currentTick - buttonLastIrqTick) > BUTTON_DEBOUNCE_DELAY_MS) ? DRIVER_STATUS_ON : DRIVER_STATUS_OFF);
}

// ==================================================================================================== //
//											Main Entry Point											//
// ==================================================================================================== //

/**
 * @brief Application entry point for the GPIO push-button IRQ demo
 * @returns Process status
 * @retval - `0`: The function returned normally, which is not expected in this
 * bare-metal application.
 */
int main(void)
{
	if (APP_Init() != DRIVER_STATUS_SUCCESS)
	{
		APP_ErrorHandler();
	}

	while(1)
	{
		OB_LED_Toggle();
		delay_ms(LOOP_DELAY_MS);
	}

	return 0;
}

// ==================================================================================================== //
//											Interrupt Handlers											//
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
	// Local Variables
	const uint32_t currentTick = SysTick_Get_Ticks();

	if (GPIO_IRQ_IsTriggered(PUSH_BUTTON_PIN) == DRIVER_STATUS_ON)
	{
		if (APP_PushButtonIRQDebounceAccepted(currentTick) == DRIVER_STATUS_ON)
		{
			buttonLastIrqTick = currentTick;
			(void) GPIO_PinToggle(RED_LED_PORT, RED_LED_PIN);
		}

		(void) GPIO_IRQ_Ack(PUSH_BUTTON_PIN);
	}
}
