/**
 * @file	main.c
 * @author	Shrey Shah
 * @brief	Implements the USART interrupt-driven character-array TX demo
 * @version	v1.0
 * @date	28-08-2026
 *
 * @details
 * @section MAIN_C_HIERARCHY Hierarchy
 * - Position: Layer 3 - Application behavior implementation
 * - Called by: Layer 4 Reset_Handler() after App_BootInit() succeeds
 * - Uses: Layer 1 RCC/GPIO/USART/NVIC Drivers, USART LL access in Handler
 *   mode, and optional BSP on-board LED APIs
 *
 * @section MAIN_C_RESPONSIBILITY Responsibility
 * This module configures USART1 PA9 for 115200-baud 8N1 transmission when
 * debug did not already acquire the same board transport. It owns one fixed
 * character array and a four-state interrupt-driven transmit lifecycle.
 * Startup enables only TXEIE, so the first and every subsequent character are
 * written by USART1_IRQHandler(). After the final DR write, the handler
 * replaces TXEIE with TCIE and waits for the final stop bit to leave the wire.
 *
 * @section MAIN_C_BOUNDARY Dependency Boundary
 * Driver APIs own initialization and main-context IRQ/NVIC sequencing. The
 * application intentionally uses dumb USART LL register-image APIs inside its
 * strong ISR, accepting exclusive ownership of DR and CR1.TXEIE/TCIE for the
 * duration of the one-shot transfer.
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

/** @brief Application USART transmit-state selector type @typedef app_usart_tx_state_t */
typedef uint8_t								app_usart_tx_state_t;
/** @brief Application USART character-count and array-index type @typedef app_usart_tx_size_t */
typedef uint16_t							app_usart_tx_size_t;

// ==================================================================================================== //
// Private Configuration
// ==================================================================================================== //

/** @brief Application-owned transmit USART instance @def APP_USART_INSTANCE */
#define APP_USART_INSTANCE					(USART1)
/** @brief NVIC line paired with the application USART instance @def APP_USART_IRQn */
#define APP_USART_IRQn						(USART1_IRQn)
/** @brief RCC bus containing the application USART clock gate @def APP_USART_CLOCK_BUS */
#define APP_USART_CLOCK_BUS					(RCC_APB2_BUS)
/** @brief Application USART peripheral clock gate @def APP_USART_CLOCK_MASK */
#define APP_USART_CLOCK_MASK				(RCC_APB2ENR_USART1EN)
/** @brief RCC bus containing the USART GPIO clock gate @def APP_USART_GPIO_CLOCK_BUS */
#define APP_USART_GPIO_CLOCK_BUS			(RCC_APB2_BUS)
/** @brief GPIOA clock gate for the reset-default USART1 route @def APP_USART_GPIO_CLOCK_MASK */
#define APP_USART_GPIO_CLOCK_MASK			(RCC_APB2ENR_IOPAEN)
/** @brief GPIO port carrying the reset-default USART1 route @def APP_USART_GPIO_PORT */
#define APP_USART_GPIO_PORT					(GPIOA)
/** @brief PA9 USART1 transmitter pin @def APP_USART_TX_PIN_MASK */
#define APP_USART_TX_PIN_MASK				((gpio_pin_t) GPIO_PIN_9)
/** @brief Application USART baud-rate preset @def APP_USART_BAUD_RATE */
#define APP_USART_BAUD_RATE					(USART_BAUD_RATE_115200)
/** @brief Application delay @def APP_DELAY_MS */
#define APP_DELAY_MS						((uint32_t) 1000UL)

/** @brief No interrupt-driven transmission has been started @def APP_USART_TX_STATE_IDLE */
#define APP_USART_TX_STATE_IDLE				((app_usart_tx_state_t) 0x00U)
/** @brief TXE interrupts are feeding character-array elements into DR @def APP_USART_TX_STATE_TXE_ACTIVE */
#define APP_USART_TX_STATE_TXE_ACTIVE		((app_usart_tx_state_t) 0x01U)
/** @brief The final frame is shifting while TCIE waits for wire completion @def APP_USART_TX_STATE_WAIT_TC */
#define APP_USART_TX_STATE_WAIT_TC			((app_usart_tx_state_t) 0x02U)
/** @brief The final frame, including its stop bit, has left the wire @def APP_USART_TX_STATE_COMPLETE */
#define APP_USART_TX_STATE_COMPLETE			((app_usart_tx_state_t) 0x03U)

// ==================================================================================================== //
// Private Data
// ==================================================================================================== //

/** @brief Pre-stored character array transmitted once after initialization */
__STATIC const char appUSARTTransmitData[] = "USART IRQ TX: character array sent successfully.\r\n";
/** @brief Number of transmitted characters excluding the C-string terminator */
__STATIC const app_usart_tx_size_t appUSARTTransmitLength = (app_usart_tx_size_t) (sizeof(appUSARTTransmitData) - 1U);
/** @brief Index of the next character written by USART1_IRQHandler() */
__STATIC volatile app_usart_tx_size_t appUSARTTransmitIndex = 0UL;
/** @brief USART TX lifecycle shared between Handler mode and main context */
__STATIC volatile app_usart_tx_state_t appUSARTTransmitState = APP_USART_TX_STATE_IDLE;

// ==================================================================================================== //
// Local Helpers
// ==================================================================================================== //

/**
 * @brief Configures the application-owned USART1 TX GPIO route
 * @returns @ref driver_status_t "Application USART GPIO-configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: GPIOA and PA9 were configured
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: An RCC or GPIO selector was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: GPIOA clock validation or GPIO staging failed
 */
__STATIC driver_status_t App_ConfigGPIOForUSART(void)
{
	//! The reset-default PA9 route needs GPIOA but no AFIO clock or remap transaction.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(APP_USART_GPIO_CLOCK_BUS, APP_USART_GPIO_CLOCK_MASK, DRIVER_STATUS_ON));
	return GPIO_SetPinModeConfig
	(
		APP_USART_GPIO_PORT,
		APP_USART_TX_PIN_MASK,
		GPIO_PIN_MODE_OUTPUT_50MHZ,
		GPIO_PIN_CONFIG_ALTERNATE_PUSH_PULL
	);
}

/**
 * @brief Configures and enables the application-owned USART1 transmitter
 * @returns @ref driver_status_t "Application USART-configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: USART1 TX was configured and enabled
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
		.hardware = USART_HARDWARE_ENABLE_TX,
		.baudRate = APP_USART_BAUD_RATE
	};

	//! The application owns the USART1 clock gate; USART_Config() only verifies it.
	ASSERT_DRIVER_STATUS(RCC_SetPeripheralClockState(APP_USART_CLOCK_BUS, APP_USART_CLOCK_MASK, DRIVER_STATUS_ON));
	ASSERT_DRIVER_STATUS(USART_Config(APP_USART_INSTANCE, &usartConfig));
	return USART_SetOperationState(APP_USART_INSTANCE, DRIVER_STATUS_ON);
}

/**
 * @brief Arms the one-shot interrupt-driven character-array transmission
 * @returns @ref driver_status_t "USART IRQ-transmission startup status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: NVIC delivery and TXEIE were enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A fixed USART, IRQ, or source selector was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: The configured USART clock was unavailable
 * @pre USART1 transmitter configuration and operation enablement completed
 */
__STATIC driver_status_t App_StartUSARTIRQTransmission(void)
{
	//! Validate the USART State
	if (((appUSARTTransmitState != APP_USART_TX_STATE_IDLE) && (appUSARTTransmitState != APP_USART_TX_STATE_COMPLETE)) || (appUSARTTransmitIndex != 0U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Update the State Machine
	appUSARTTransmitState = APP_USART_TX_STATE_TXE_ACTIVE;
	//! Remove both owned sources so only the deliberately enabled TXE path can start the transfer.
	ASSERT_DRIVER_STATUS(USART_SetIRQSources(APP_USART_INSTANCE, (USART_IRQ_SOURCE_TXE | USART_IRQ_SOURCE_TC), DRIVER_STATUS_OFF));
	//! Reset NVIC IRQ State
	ASSERT_DRIVER_STATUS(NVIC_ClearPendingIRQ(APP_USART_IRQn));
	ASSERT_DRIVER_STATUS(NVIC_EnableIRQ(APP_USART_IRQn));
	//! DR is empty after configuration, so enabling TXEIE generates the first character's interrupt.
	return USART_SetIRQSources(APP_USART_INSTANCE, USART_IRQ_SOURCE_TXE, DRIVER_STATUS_ON);
}

/**
 * @brief Enters the application error-indication loop
 * @details The optional BSP on-board LED is asserted when initialization or
 * IRQ-path setup fails.
 */
__STATIC void App_ErrorHandler(void)
{
#if (APP_ENABLE_ONBOARD_LED == 1U)
	//! A persistent active-low LED state reports failure without relying on the USART path.
	BSP_OB_LED_Set();
#endif /* APP_ENABLE_ONBOARD_LED */

	//! This focused example requires reset after a failed initialization transaction.
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
	//! Configure USART
	if (App_ConfigGPIOForUSART() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}
	if (App_ConfigUSART() != DRIVER_STATUS_SUCCESS)
	{
		App_ErrorHandler();
	}

	//! Keep the completed one-shot demonstration quiescent until reset.
	while (1)
	{
		//! TXEIE is enabled only here; the empty DR then invokes the ISR for the first character.
		if (App_StartUSARTIRQTransmission() != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}

		//! Main performs no byte polling; it sleeps while the ISR advances the complete TX lifecycle.
		while (appUSARTTransmitState != APP_USART_TX_STATE_COMPLETE)
		{
			__WFI();
		}

		//! Delay
		if (App_DelayMs(APP_DELAY_MS) != DRIVER_STATUS_SUCCESS)
		{
			App_ErrorHandler();
		}
	}
}

// ==================================================================================================== //
// USART Interrupt Handler
// ==================================================================================================== //

void USART1_IRQHandler(void)
{
	// Local Variables
	reg srRegImage = 0x00000000UL;
	reg cr1RegImage = 0x00000000UL;

	//! One SR snapshot decides which of the two application-owned TX phases this invocation can advance.
	srRegImage = LL_USART_ReadSR(APP_USART_INSTANCE);

	//! TX not completed?
	if (appUSARTTransmitState == APP_USART_TX_STATE_TXE_ACTIVE)
	{
		//! TX Register Empty?
		if ((srRegImage & USART_SR_TXE) != 0UL)
		{
			//! Safety Check: TX Index <= Max Length
			if (appUSARTTransmitIndex < appUSARTTransmitLength)
			{
				//! Transmit the character
				//NOTE: Writing to DR clears the TXE IRQ - no explicit clearing required
				LL_USART_WriteDR(APP_USART_INSTANCE, (reg) appUSARTTransmitData[appUSARTTransmitIndex]);
				//! Increment the next TX index
				appUSARTTransmitIndex++;
	
				//! Final Character?
				if (appUSARTTransmitIndex == appUSARTTransmitLength)
				{
					//! Read CR1
					cr1RegImage = LL_USART_ReadCR1(APP_USART_INSTANCE);
					//! Disable TX Empty IRQ
					cr1RegImage &= ~USART_CR1_TXEIE;
					//! Enable TX Completed IRQ
					cr1RegImage |= USART_CR1_TCIE;
					//! Write the updated IRQ Source
					LL_USART_WriteCR1(APP_USART_INSTANCE, cr1RegImage);
					//! Update the State Machine
					appUSARTTransmitState = APP_USART_TX_STATE_WAIT_TC;
				}
			}
		}
	}
	//! TX Completed?
	else if (appUSARTTransmitState == APP_USART_TX_STATE_WAIT_TC)
	{
		//! TX Completed?
		if ((srRegImage & USART_SR_TC) != 0x00000000UL)
		{
			//! Read CR1
			cr1RegImage = LL_USART_ReadCR1(APP_USART_INSTANCE);
			//! Disable IRQ
			cr1RegImage &= ~USART_CR1_TCIE;
			//! Update CR1
			LL_USART_WriteCR1(APP_USART_INSTANCE, cr1RegImage);
			//! Update State Machine
			appUSARTTransmitState = APP_USART_TX_STATE_COMPLETE;
			//! Reset the TX Index
			appUSARTTransmitIndex = 0U;
		}
	}
}
