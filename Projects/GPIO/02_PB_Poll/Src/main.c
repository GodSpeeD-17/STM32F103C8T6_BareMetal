/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(void)
{
	//! Initialisation of LEDs
	if (GPIO_LED_Init(RED_LED_PORT, (RED_LED_PIN | YELLOW_LED_PIN)) != DRIVER_STATUS_SUCCESS)
	{
		OB_LED_Set();
		while(1);
	}
	//! Initialization of Push Button (External Pull-Up)
	if (GPIO_Init(PUSH_BUTTON_PORT, PUSH_BUTTON_PIN, GPIO_PIN_MODE_INPUT, GPIO_PIN_CONFIG_INPUT_FLOATING) != DRIVER_STATUS_SUCCESS)
	{
		OB_LED_Set();
		while(1);
	}

	// Infinite Loop
	while(1)
	{
		//! Poll Push Button State (External Pull-Up)
		if (GPIO_PinGet(PUSH_BUTTON_PORT, PUSH_BUTTON_PIN) == DRIVER_STATUS_OFF)
		{
			GPIO_PinToggle(RED_LED_PORT, RED_LED_PIN);
			GPIO_PinToggle(YELLOW_LED_PORT, YELLOW_LED_PIN);
		}
		
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/
