/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements interrupt-driven USART line reception and echo
 * @version	v1.0
 * @date	28-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_Init() succeeds
 * - Uses: Layer 1 RCC/GPIO/USART/NVIC Drivers, USART LL access in Handler
 *   mode, and the Core `WFI` intrinsic
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * This module receives one line into a fixed application buffer through RXNE
 * interrupts. After at least one character is captured, a carriage return,
 * line feed, or full buffer starts an echo through TXE interrupts. TC then
 * confirms that the final stop bit left the wire before reception is re-armed.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * Driver APIs own main-context peripheral and NVIC setup. The strong USART1
 * handler intentionally uses LL register-image APIs because it exclusively
 * owns DR and the RXNEIE/TXEIE/TCIE source bits while the demo is active.
 */

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "main.h"
#include "app_config.h"
#include "app_time.h"
#include "cmsis_gcc.h"
#include "gpio.h"
#include "nvic.h"
#include "rcc.h"
#include "usart.h"
#include "usart_ll.h"

#if (APP_ENABLE_ONBOARD_LED == 1U)
#include "bsp_gpio.h"
#endif /* APP_ENABLE_ONBOARD_LED */

// ==================================================================================================== //
// Private Types
// ==================================================================================================== //

/** @brief Application USART state-selector type @typedef app_usart_state_t */
typedef uint8_t								app_usart_state_t;
/** @brief Application USART character-storage type @typedef app_usart_character_t */
typedef uint8_t								app_usart_character_t;
/** @brief Application USART buffer length and index type @typedef app_usart_size_t */
typedef uint16_t							app_usart_size_t;

// ==================================================================================================== //
// Private Configuration
// ==================================================================================================== //

/** @brief Application-owned full-duplex USART instance @def APP_USART_INSTANCE */
#define APP_USART_INSTANCE					(USART1)
/** @brief NVIC line paired with the application USART instance @def APP_USART_IRQn */
#define APP_USART_IRQn						(USART1_IRQn)
/** @brief RCC bus containing the application USART clock gate @def APP_USART_CLOCK_BUS */
#define APP_USART_CLOCK_BUS					(RCC_APB2_BUS)
/** @brief Application USART peripheral clock gate @def APP_USART_CLOCK_MASK */
#define APP_USART_CLOCK_MASK				(RCC_APB2ENR_USART1EN)
/** @brief RCC bus containing the application USART GPIO clock gate @def APP_USART_GPIO_CLOCK_BUS */
#define APP_USART_GPIO_CLOCK_BUS			(RCC_APB2_BUS)
/** @brief GPIOA clock gate for the reset-default USART1 route @def APP_USART_GPIO_CLOCK_MASK */
#define APP_USART_GPIO_CLOCK_MASK			(RCC_APB2ENR_IOPAEN)
/** @brief GPIO port carrying the reset-default USART1 route @def APP_USART_GPIO_PORT */
#define APP_USART_GPIO_PORT					(GPIOA)
/** @brief PA9 application USART transmitter pin @def APP_USART_TX_PIN_MASK */
#define APP_USART_TX_PIN_MASK				((gpio_pin_t) GPIO_PIN_9)
/** @brief PA10 application USART receiver pin @def APP_USART_RX_PIN_MASK */
#define APP_USART_RX_PIN_MASK				((gpio_pin_t) GPIO_PIN_10)
/** @brief Application USART baud-rate preset @def APP_USART_BAUD_RATE */
#define APP_USART_BAUD_RATE					(USART_BAUD_RATE_115200)
/** @brief Application GPIO - Port @def APP_LED_GPIO_PORT */
#define APP_LED_GPIO_PORT					(GPIOA)
/** @brief Application GPIO - Pin @def APP_LED_GPIO_PIN */
#define APP_LED_GPIO_PIN					(GPIO_PIN_3)
/** @brief Application Delay @def APP_DELAY_MS */
#define APP_DELAY_MS						((uint32_t) 1000UL)

/** @brief RXNE interrupts are collecting the current line @def APP_USART_STATE_RX_ACTIVE */
#define APP_USART_STATE_RX_ACTIVE			((app_usart_state_t) 0x00U)
/** @brief TXE interrupts are feeding the captured line into DR @def APP_USART_STATE_TXE_ACTIVE */
#define APP_USART_STATE_TXE_ACTIVE			((app_usart_state_t) 0x01U)
/** @brief The final frame is shifting while TCIE waits for wire completion @def APP_USART_STATE_WAIT_TC */
#define APP_USART_STATE_WAIT_TC				((app_usart_state_t) 0x02U)

// ==================================================================================================== //
// Private Data
// ==================================================================================================== //

/** @brief Fixed storage shared by the receive and transmit phases */
__STATIC app_usart_character_t appUSARTDataBuffer[64U] = {0U};
/** @brief Maximum number of characters held by the fixed application buffer */
__STATIC const app_usart_size_t appUSARTDataCapacity = (app_usart_size_t) sizeof(appUSARTDataBuffer);
/** @brief Receive errors cleared by the mandatory SR-then-DR read sequence */
__STATIC const reg appUSARTReceiveErrorMask = (USART_SR_ORE | USART_SR_NE | USART_SR_FE);
/** @brief Number of characters currently captured by RXNE interrupts */
__STATIC app_usart_size_t appUSARTReceiveLength = 0U;
/** @brief Number of captured characters scheduled for transmission */
__STATIC app_usart_size_t appUSARTTransmitLength = 0U;
/** @brief Index of the next character written to DR by a TXE interrupt */
__STATIC app_usart_size_t appUSARTTransmitIndex = 0U;
/** @brief Current ownership phase used by USART1_IRQHandler() */
__STATIC volatile app_usart_state_t appUSARTState = APP_USART_STATE_RX_ACTIVE;

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

/**
 * @brief Configures the application-owned USART1 GPIO route
 * @returns @ref driver_status_t "Application USART GPIO-configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: GPIOA, PA9, and PA10 were configured
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: An RCC or GPIO selector was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: GPIOA clock validation or GPIO staging failed
 */
__STATIC driver_status_t App_ConfigGPIOForUSART(void)
{
	//! The reset-default PA9/PA10 route needs GPIOA but no AFIO remap transaction.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(APP_USART_GPIO_CLOCK_BUS, APP_USART_GPIO_CLOCK_MASK, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS
	(
		GPIO_SetPinModeConfig
		(
			APP_USART_GPIO_PORT,
			APP_USART_TX_PIN_MASK,
			GPIO_PIN_MODE_OUTPUT_50MHZ,
			GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL
		)
	);

	//! PA10 remains an input because the connected serial peer drives it.
	return GPIO_SetPinModeConfig
	(
		APP_USART_GPIO_PORT,
		APP_USART_RX_PIN_MASK,
		GPIO_PIN_MODE_INPUT,
		GPIO_PIN_CONFIG_INPUT_FLOATING
	);
}

/**
 * @brief Configures and enables the application-owned full-duplex USART
 * @returns @ref driver_status_t "Application USART-configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: USART1 was configured and enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The fixed USART configuration was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1's clock or bus frequency was unavailable
 */
__STATIC driver_status_t App_ConfigUSART(void)
{
	const usart_config_t usartConfig =
	{
		.frameFormat =
		{
			.parity = USART_PARITY_NONE,
			.stopBits = USART_STOP_BIT_1,
			.dataBits = USART_DATA_BITS_8
		},
		.hardware = USART_HARDWARE_ENABLE_TX_RX,
		.baudRate = APP_USART_BAUD_RATE
	};

	//! The application owns the USART1 clock gate; USART_Config() validates it.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(APP_USART_CLOCK_BUS, APP_USART_CLOCK_MASK, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(USART_Config(APP_USART_INSTANCE, &usartConfig));
	return USART_SetOperationState(APP_USART_INSTANCE, DRIVER_STATUS_ON);
}

/**
 * @brief Arms USART1 for the first interrupt-driven receive phase
 * @returns @ref driver_status_t "USART IRQ echo-start status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: NVIC delivery and RXNEIE were enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A fixed USART, IRQ, or source selector was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The configured USART clock was unavailable
 * @pre USART1 full-duplex configuration and operation enablement completed
 */
__STATIC driver_status_t App_StartUSARTIRQEcho(void)
{
	//! Establish all software state before the first RXNE request can reach Handler mode.
	appUSARTReceiveLength = 0U;
	appUSARTTransmitLength = 0U;
	appUSARTTransmitIndex = 0U;
	appUSARTState = APP_USART_STATE_RX_ACTIVE;

	//! Remove every application-owned source before clearing and enabling its shared NVIC line.
	ASSERT_DRIVER_STATUS
	(
		USART_SetIRQSources
		(
			APP_USART_INSTANCE,
			(USART_IRQ_SOURCE_RXNE | USART_IRQ_SOURCE_TXE | USART_IRQ_SOURCE_TC),
			DRIVER_STATUS_OFF
		)
	);
	ASSERT_DRIVER_STATUS(NVIC_ClearPendingIRQ(APP_USART_IRQn));
	ASSERT_DRIVER_STATUS(NVIC_EnableIRQ(APP_USART_IRQn));

	//! Reception starts only through RXNEIE; main never polls DR.
	return USART_SetIRQSources(APP_USART_INSTANCE, USART_IRQ_SOURCE_RXNE, DRIVER_STATUS_ON);
}

/**
 * @brief Enters the application error-indication loop
 * @details The optional BSP on-board LED is asserted when initialization or
 * IRQ-path setup fails.
 */
__STATIC void App_ErrorHandler(void)
{
#if (APP_ENABLE_ONBOARD_LED == 1U)
	//! Report failure without depending on the USART path being operational.
	BSP_OB_LED_Set();
#endif /* APP_ENABLE_ONBOARD_LED */

	while (1)
	{
		__WFI();
	}
}

// ==================================================================================================== //
// Application Entry Point
// ==================================================================================================== //

int main(void)
{
	//! Without BSP debug setup, the application owns the complete GPIO and USART transaction.
	if (App_ConfigGPIOForUSART() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}
	if (App_ConfigUSART() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}

	if (GPIO_LED_Init(APP_LED_GPIO_PORT, APP_LED_GPIO_PIN) != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}

	//! Arm RXNE only after USART and NVIC setup is complete.
	if (App_StartUSARTIRQEcho() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}

	while (1)
	{
		GPIO_PinToggle(APP_LED_GPIO_PORT, APP_LED_GPIO_PIN);
		App_DelayMs(APP_DELAY_MS);
	}
}

// ==================================================================================================== //
// USART Interrupt Handler
// ==================================================================================================== //

void USART1_IRQHandler(void)
{
	// Local Variables
	app_usart_character_t receivedCharacter = 0x00U;
	reg srRegImage = 0x00000000UL;
	reg cr1RegImage = 0x00000000UL;

	//! One SR snapshot keeps every decision coherent and begins the required SR-then-DR receive-clear sequence.
	srRegImage = LL_USART_ReadSR(APP_USART_INSTANCE);

	//! Receiving a Message?
	if (appUSARTState == APP_USART_STATE_RX_ACTIVE)
	{
		//! Any receive-related condition that requires exactly one DR read?
		if ((srRegImage & (USART_SR_RXNE | appUSARTReceiveErrorMask)) != 0UL)
		{
			//! Capture the Character - reading DR exactly once after SR clears RXNE and receive errors without consuming another byte.
			receivedCharacter = (app_usart_character_t) LL_USART_ReadDR(APP_USART_INSTANCE);

			//! Receive Error?
			if ((srRegImage & appUSARTReceiveErrorMask) != 0UL)
			{
				appUSARTReceiveLength = 0U;
				return;
			}

			//! End of Message?
			if ((receivedCharacter == '\n') || (receivedCharacter == '\r'))
			{
				//! Empty Message?
				if (appUSARTReceiveLength == 0U)
				{
					return;
				}
			}

			//! Buffer Space Available?
			if (appUSARTReceiveLength < appUSARTDataCapacity)
			{
				//! Store every received character, including the terminating CR/LF, so the terminal can render the echoed line.
				appUSARTDataBuffer[appUSARTReceiveLength] = receivedCharacter;
				//! Increment the counter only after the corresponding buffer element becomes valid.
				appUSARTReceiveLength++;
			}

			//! Message Still Incomplete?
			if ((receivedCharacter != '\n') && (receivedCharacter != '\r') && (appUSARTReceiveLength < appUSARTDataCapacity))
			{
				return;
			}

			//! Prepare the Completed Message
			appUSARTTransmitLength = appUSARTReceiveLength;
			appUSARTTransmitIndex = 0U;

			//! Read CR1 once so the source handoff preserves every unrelated USART configuration bit.
			cr1RegImage = LL_USART_ReadCR1(APP_USART_INSTANCE);
			//! Disable RXNEIE because the shared buffer is read-only throughout transmission.
			cr1RegImage &= ~USART_CR1_RXNEIE;
			//! Enable TXEIE while TXE is already set so the first character is transmitted by the next IRQ.
			cr1RegImage |= USART_CR1_TXEIE;
			//! Update the State Machine before the CR1 write can expose the pending TXE request.
			appUSARTState = APP_USART_STATE_TXE_ACTIVE;
			//! Commit both source changes together while leaving the USART NVIC line continuously enabled.
			LL_USART_WriteCR1(APP_USART_INSTANCE, cr1RegImage);
		}
	}
	//! Transmitting the Message?
	else if (appUSARTState == APP_USART_STATE_TXE_ACTIVE)
	{
		//! TX Register Empty?
		//! TXE proves hardware accepted the previous character, so writing DR cannot overwrite it.
		if ((srRegImage & USART_SR_TXE) != 0UL)
		{
			//! TX Index Valid?
			//! The bound prevents any unexpected state corruption from reading beyond the completed payload.
			if (appUSARTTransmitIndex < appUSARTTransmitLength)
			{
				//! Transmit the Character
				//! Writing DR clears TXE, de-asserting its request until hardware accepts this character.
				LL_USART_WriteDR(APP_USART_INSTANCE, (reg) appUSARTDataBuffer[appUSARTTransmitIndex]);
				//! Advance only after the character has been committed to the peripheral.
				appUSARTTransmitIndex++;

				//! Final Character Written?
				//! TXE cannot prove wire completion, so the final DR write must transfer ownership to TC.
				if (appUSARTTransmitIndex == appUSARTTransmitLength)
				{
					//! Read CR1 once so the source handoff preserves every unrelated configuration bit.
					cr1RegImage = LL_USART_ReadCR1(APP_USART_INSTANCE);
					//! Disable TXEIE before DR empties again, preventing a request with no character remaining.
					cr1RegImage &= ~USART_CR1_TXEIE;
					//! Enable TCIE so hardware requests service only after the final stop bit leaves the wire.
					cr1RegImage |= USART_CR1_TCIE;
					//! Update the State Machine before the CR1 write exposes the future TC request.
					appUSARTState = APP_USART_STATE_WAIT_TC;
					//! Commit the TXE-to-TC source handoff in one register write.
					LL_USART_WriteCR1(APP_USART_INSTANCE, cr1RegImage);
				}
			}
		}
	}
	//! Waiting for Physical Transmission Completion?
	//! WAIT_TC forbids further buffer reads while hardware finishes the already queued final frame.
	else if (appUSARTState == APP_USART_STATE_WAIT_TC)
	{
		//! Transmission Complete?
		//! TC proves both DR and the shift register are empty, so receive ownership cannot truncate TX.
		if ((srRegImage & USART_SR_TC) != 0UL)
		{
			//! Reset the Buffer Cursors
			//! Publish clean indices before RXNEIE exposes any byte that arrived while transmission was active.
			appUSARTReceiveLength = 0U;
			appUSARTTransmitLength = 0U;
			appUSARTTransmitIndex = 0U;

			//! Read CR1 once so the source handoff preserves every unrelated configuration bit.
			cr1RegImage = LL_USART_ReadCR1(APP_USART_INSTANCE);
			//! Disable TCIE because its already-set TC flag would otherwise keep requesting service.
			cr1RegImage &= ~USART_CR1_TCIE;
			//! Re-enable RXNEIE so a pending or future character begins the next message.
			cr1RegImage |= USART_CR1_RXNEIE;
			//! Update the State Machine before the CR1 write can expose an already-pending RXNE request.
			appUSARTState = APP_USART_STATE_RX_ACTIVE;
			//! Commit the TC-to-RXNE handoff while the USART NVIC line remains continuously enabled.
			LL_USART_WriteCR1(APP_USART_INSTANCE, cr1RegImage);
		}
	}
}
