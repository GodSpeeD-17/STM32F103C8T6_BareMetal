// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "main.h"

// ==================================================================================================== //
//												Macros													//
// ==================================================================================================== //
/**
 * @brief LED application pattern constants
 * @details
 * The demo treats the red LED, yellow LED, and Blue Pill on-board LED as a
 * three-bit output pattern. Bit `0` drives the red LED, bit `1` drives the
 * yellow LED, and bit `2` drives the on-board LED through the BSP active-low
 * helper APIs.
 * @{
 */
/** @brief Pattern value with every LED switched off @def APP_LED_PATTERN_ALL_OFF */
#define APP_LED_PATTERN_ALL_OFF				((uint8_t) 0x00U)
/** @brief Pattern value with every LED switched on @def APP_LED_PATTERN_ALL_ON */
#define APP_LED_PATTERN_ALL_ON				((uint8_t) 0x07U)
/** @brief Highest valid three-bit LED pattern value @def APP_LED_PATTERN_MAX */
#define APP_LED_PATTERN_MAX					APP_LED_PATTERN_ALL_ON
/** @brief Red LED bit position inside the app LED pattern @def APP_LED_RED_BIT */
#define APP_LED_RED_BIT						((uint8_t) 0x00U)
/** @brief Yellow LED bit position inside the app LED pattern @def APP_LED_YELLOW_BIT */
#define APP_LED_YELLOW_BIT					((uint8_t) 0x01U)
/** @brief On-board LED bit position inside the app LED pattern @def APP_LED_ONBOARD_BIT */
#define APP_LED_ONBOARD_BIT					((uint8_t) 0x02U)
/** @} */

// ==================================================================================================== //
//											Local Helpers												//
// ==================================================================================================== //
/**
 * @brief Extracts one logical LED state from a three-bit LED pattern
 * @param[in] pattern Three-bit LED pattern
 * Accepted values:
 * - @ref `APP_LED_PATTERN_ALL_OFF` through @ref `APP_LED_PATTERN_MAX`
 * @param[in] bitPosition LED bit position inside @p pattern
 * Accepted values:
 * - @ref `APP_LED_RED_BIT`
 * - @ref `APP_LED_YELLOW_BIT`
 * - @ref `APP_LED_ONBOARD_BIT`
 * @returns Logical LED state
 * @retval - @ref `DRIVER_STATUS_OFF`: Selected pattern bit is cleared.
 * @retval - @ref `DRIVER_STATUS_ON`: Selected pattern bit is set.
 */
static driver_status_t APP_ExtractLEDStateFromPattern(const uint8_t pattern, const uint8_t bitPosition)
{
	return ((((pattern >> bitPosition) & 0x01U) == 0x00U) ? DRIVER_STATUS_OFF : DRIVER_STATUS_ON);
}

/**
 * @brief Applies a logical state to the board on-board LED
 * @param[in] ledState Logical LED request
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Switch the LED off
 * - @ref `DRIVER_STATUS_ON`: Switch the LED on
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested LED state was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p ledState was invalid.
 * @details
 * The BSP owns the Blue Pill active-low polarity. This helper therefore uses
 * @ref `OB_LED_Set` for logical on and @ref `OB_LED_Reset` for logical off.
 */
static driver_status_t APP_SetOnboardLED(const driver_status_t ledState)
{
	if (ledState == DRIVER_STATUS_ON)
	{
		OB_LED_Set();
	}
	else if (ledState == DRIVER_STATUS_OFF)
	{
		OB_LED_Reset();
	}
	else
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Applies a logical state to one external user LED
 * @param[in] GPIOx GPIO peripheral instance connected to the LED
 * Accepted values:
 * - @ref `GPIOA`
 * - @ref `GPIOB`
 * - @ref `GPIOC`
 * - @ref `GPIOD`
 * - @ref `GPIOE`
 * - @ref `GPIOF`
 * - @ref `GPIOG`
 * @param[in] pin GPIO single-pin mask connected to the LED
 * Accepted values:
 * - @ref `GPIO_PIN_0`..@ref `GPIO_PIN_15`
 * @param[in] ledState Logical LED request
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Switch the LED off
 * - @ref `DRIVER_STATUS_ON`: Switch the LED on
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Requested output latch state was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p GPIOx, @p pin, or
 * @p ledState was invalid.
 * @details
 * External LEDs are treated as active-high GPIO outputs in this project.
 */
static driver_status_t APP_SetUserLED
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pin,
	const driver_status_t		ledState
)
{
	if (ledState == DRIVER_STATUS_ON)
	{
		return GPIO_PinSet(GPIOx, pin);
	}
	else if (ledState == DRIVER_STATUS_OFF)
	{
		return GPIO_PinReset(GPIOx, pin);
	}

	return DRIVER_STATUS_ERROR_INVALID_ARG;
}

/**
 * @brief Initializes every LED used by the 01_OB_LED demo
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: All LED GPIOs were initialized.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One LED GPIO mapping was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal GPIO staged-image update failed.
 * @details
 * The red/yellow LEDs are initialized through the generic GPIO LED helper, while
 * the on-board LED is initialized through BSP so board polarity stays outside
 * generic GPIO driver ownership.
 */
static driver_status_t APP_InitLEDs(void)
{
	ASSERT_DRIVER_STATUS(GPIO_LED_Init(RED_LED_PORT, (RED_LED_PIN | YELLOW_LED_PIN)));
	ASSERT_DRIVER_STATUS(OB_LED_Init());
	ASSERT_DRIVER_STATUS(APP_SetOnboardLED(DRIVER_STATUS_OFF));

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Applies one three-bit LED pattern to the demo LEDs
 * @param[in] pattern Three-bit LED pattern
 * Accepted values:
 * - @ref `APP_LED_PATTERN_ALL_OFF` through @ref `APP_LED_PATTERN_MAX`
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pattern was applied.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p pattern or one LED GPIO
 * mapping was invalid.
 * @details
 * Pattern bit ownership:
 * - @ref `APP_LED_RED_BIT`: Red LED
 * - @ref `APP_LED_YELLOW_BIT`: Yellow LED
 * - @ref `APP_LED_ONBOARD_BIT`: BSP on-board LED
 */
static driver_status_t APP_ApplyLEDPattern(const uint8_t pattern)
{
	// Local Variables
	const driver_status_t redLEDState = APP_ExtractLEDStateFromPattern(pattern, APP_LED_RED_BIT);
	const driver_status_t yellowLEDState = APP_ExtractLEDStateFromPattern(pattern, APP_LED_YELLOW_BIT);
	const driver_status_t onboardLEDState = APP_ExtractLEDStateFromPattern(pattern, APP_LED_ONBOARD_BIT);

	// Validate Input
	if (pattern > APP_LED_PATTERN_MAX)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	ASSERT_DRIVER_STATUS
	(
		APP_SetUserLED
		(
			RED_LED_PORT,
			RED_LED_PIN,
			redLEDState
		)
	);
	ASSERT_DRIVER_STATUS
	(
		APP_SetUserLED
		(
			YELLOW_LED_PORT,
			YELLOW_LED_PIN,
			yellowLEDState
		)
	);
	ASSERT_DRIVER_STATUS(APP_SetOnboardLED(onboardLEDState));

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Runs the startup lamp-test sequence
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Lamp-test sequence completed.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: One user LED GPIO mapping was invalid.
 * @details
 * The sequence is all-off, all-on, then all-off. Each state is held for
 * @ref `LED_LAMP_TEST_DELAY_MS`.
 */
static driver_status_t APP_RunLampTest(void)
{
	ASSERT_DRIVER_STATUS(APP_ApplyLEDPattern(APP_LED_PATTERN_ALL_OFF));
	delay_ms(LED_LAMP_TEST_DELAY_MS);

	ASSERT_DRIVER_STATUS(APP_ApplyLEDPattern(APP_LED_PATTERN_ALL_ON));
	delay_ms(LED_LAMP_TEST_DELAY_MS);

	ASSERT_DRIVER_STATUS(APP_ApplyLEDPattern(APP_LED_PATTERN_ALL_OFF));
	delay_ms(LED_LAMP_TEST_DELAY_MS);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//											Main Entry Point											//
// ==================================================================================================== //
/**
 * @brief Application entry point for the GPIO on-board LED demo
 * @returns Process status
 * @retval - `0`: The function returned normally, which is not expected in this
 * bare-metal application.
 * @details
 * The application initializes the two external active-high LEDs and the BSP
 * on-board active-low LED, runs a short lamp test, then continuously displays a
 * three-bit counter across the LEDs.
 */
int main()
{
	// Configure LEDs
	uint8_t pattern = APP_LED_PATTERN_ALL_OFF;

	ASSERT_DRIVER_STATUS(APP_InitLEDs());
	delay_ms(LED_STEP_DELAY_MS);
	ASSERT_DRIVER_STATUS(APP_RunLampTest());
	delay_ms(LED_STEP_DELAY_MS);

	// Infinite Loop
	while (1)
	{
		// 3-bit LED counter:
		// bit0 -> RED LED, bit1 -> YELLOW LED, bit2 -> On-board LED
		ASSERT_DRIVER_STATUS(APP_ApplyLEDPattern(pattern));
		delay_ms(LED_STEP_DELAY_MS);

		pattern++;
		if (pattern > APP_LED_PATTERN_MAX)
		{
			pattern = APP_LED_PATTERN_ALL_OFF;
			ASSERT_DRIVER_STATUS(APP_RunLampTest());
		}
	}

	// Return Value
	return 0;
}
