// ---------------------------------------------------------------------------------------------------- //
// Header Files
// ---------------------------------------------------------------------------------------------------- //
#include "main.h"

// ---------------------------------------------------------------------------------------------------- //
// Local Helpers
// ---------------------------------------------------------------------------------------------------- //
static void APP_SetOnboardLed(const uint8_t isOn)
{
	if (isOn != 0x00U)
	{
		OB_LED_Set();
	}
	else
	{
		OB_LED_Reset();
	}
}

static void APP_SetUserLed(const gpio_port_t port, const gpio_pin_t pin, const uint8_t isOn)
{
	if (isOn != 0x00U)
	{
		GPIO_PinSet(port, pin);
	}
	else
	{
		GPIO_PinReset(port, pin);
	}
}

static void APP_ApplyLedPattern(const uint8_t pattern)
{
	APP_SetUserLed(RED_LED_PORT, RED_LED_PIN, (uint8_t) (pattern & 0x01U));
	APP_SetUserLed(YELLOW_LED_PORT, YELLOW_LED_PIN, (uint8_t) ((pattern >> 1U) & 0x01U));
	APP_SetOnboardLed((uint8_t) ((pattern >> 2U) & 0x01U));
}

static void APP_RunLampTest(void)
{
	APP_ApplyLedPattern(0x00U);
	delay_ms(LED_LAMP_TEST_DELAY_MS);

	APP_ApplyLedPattern(0x07U);
	delay_ms(LED_LAMP_TEST_DELAY_MS);

	APP_ApplyLedPattern(0x00U);
	delay_ms(LED_LAMP_TEST_DELAY_MS);
}
// ---------------------------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------------------------- //
// Main Entry Point
// ---------------------------------------------------------------------------------------------------- //
int main()
{
	// Configure LEDs
	gpio_config_t multiLedConfig =
	{
		.pin = (RED_LED_PIN | YELLOW_LED_PIN),
	};
	uint8_t pattern = 0x00U;

	ASSERT_DRIVER_STATUS(GPIO_LED_Init(RED_LED_PORT, &multiLedConfig));
	APP_RunLampTest();

	// Infinite Loop
	while (1)
	{
		// 3-bit LED counter:
		// bit0 -> RED LED, bit1 -> YELLOW LED, bit2 -> On-board LED
		APP_ApplyLedPattern(pattern);
		delay_ms(LED_STEP_DELAY_MS);

		pattern++;
		if (pattern > 0x07U)
		{
			pattern = 0x00U;
			APP_RunLampTest();
		}
	}

	// Return Value
	return 0;
}
// ---------------------------------------------------------------------------------------------------- //
