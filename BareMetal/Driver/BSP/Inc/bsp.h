/**
 * @file	bsp.h
 * @author	Shrey Shah
 * @brief	Board Support Package Public Interface
 * @version	v1.0
 * @date	31-05-2026
 *
 * @details
 * The BSP layer owns board-level policy. Generic peripheral drivers such as
 * GPIO expose reusable port/pin APIs, while this layer binds those APIs to one
 * physical board. For the STM32F103C8T6 Blue Pill, the board policy currently
 * captured here is the active-low on-board LED connected to PC13 and the
 * reset-default full-duplex UART route on USART1 PA9/PA10.
 *
 * Keeping this mapping in BSP prevents the generic GPIO driver from knowing
 * which package pin has an LED attached, whether that LED is active-low, or
 * which board-specific convenience functions should exist.
 */

// Header Guards
#ifndef BSP_H_
#define BSP_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "gpio.h"
#include "usart.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Board support package APIs and board-level constants
 * @defgroup BSP_01_BoardSupport BSP Board Support
 * @details
 * This group contains symbols that are valid for a concrete target board rather
 * than for the STM32F1 GPIO peripheral in general. Code that needs direct GPIO
 * control should include @ref `gpio.h`; code that needs Blue Pill board
 * conveniences should include @ref `bsp.h`.
 * @{
 */

// ==================================================================================================== //
//										STM32F103C8T6 Board Defaults									//
// ==================================================================================================== //

#ifdef STM32F103C8T6__

/**
 * @brief GPIO peripheral instance connected to the Blue Pill on-board LED
 * @def GPIO_OB_LED_PORT
 * @details
 * The STM32F103C8T6 Blue Pill routes the on-board LED to GPIO port C. This is
 * board routing information, not a GPIO peripheral fact.
 */
#define GPIO_OB_LED_PORT						GPIOC
/**
 * @brief GPIO pin connected to the Blue Pill on-board LED
 * @def GPIO_OB_LED_PIN
 * @details
 * The on-board LED is connected to PC13 and is wired active-low. A reset output
 * latch turns the LED on, while a set output latch turns it off.
 */
#define GPIO_OB_LED_PIN							GPIO_PIN_13
/**
 * @brief APB2 clock-enable mask owned by the on-board LED GPIO port
 * @def GPIO_OB_LED_CLOCK_ENABLE_MASK
 * @details
 * The application must enable this clock gate through @ref `RCC_SetPeripheralClockState`
 * before calling @ref `BSP_OB_LED_Init`; the BSP and GPIO drivers only verify it.
 */
#define GPIO_OB_LED_CLOCK_ENABLE_MASK			(RCC_APB2ENR_IOPCEN)

// Uncomment this to achieve delay from SysTick
// #define SYSTICK_DELAY__

// Use Timer for Delay
#ifndef SYSTICK_DELAY__
/** @brief Dedicated Timer instance used by the startup blocking-delay service @def DELAY_TIMER */
#define DELAY_TIMER								(TIM4)
/** @brief APB1 clock-enable mask owned by the startup blocking-delay service @def DELAY_TIMER_CLOCK_ENABLE_MASK */
#define DELAY_TIMER_CLOCK_ENABLE_MASK			(RCC_APB1ENR_TIM4EN)
#endif /* SYSTICK_DELAY__ */

// ==================================================================================================== //
//										On-Board LED APIs												//
// ==================================================================================================== //

/**
 * @brief Initializes the board on-board LED GPIO
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: On-board LED GPIO was initialized.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Board LED GPIO mapping was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: @ref `GPIO_OB_LED_CLOCK_ENABLE_MASK` is disabled, or the
 * internal GPIO staged-image update failed.
 * @pre The application enabled @ref `GPIO_OB_LED_CLOCK_ENABLE_MASK` through
 * @ref `RCC_SetPeripheralClockState` before calling this API.
 * @details
 * This API configures @ref `GPIO_OB_LED_PORT` / @ref `GPIO_OB_LED_PIN` through
 * @ref `GPIO_LED_Init`, which applies @ref `GPIO_PIN_MODE_OUTPUT_2MHZ` and
 * @ref `GPIO_PIN_CONFIG_OUTPUT_PUSH_PULL`. The active-low polarity is handled
 * by the set/reset helper APIs below. This API only verifies the clock gate;
 * it never enables it.
 */
driver_status_t BSP_OB_LED_Init(void);

/**
 * @brief Sets the active-low board on-board LED
 * @details
 * The Blue Pill LED turns on when PC13 is driven low, so this API resets the
 * GPIO output latch through @ref `GPIO_PinReset`.
 */
void BSP_OB_LED_Set(void);

/**
 * @brief Resets the active-low board on-board LED
 * @details
 * The Blue Pill LED turns off when PC13 is driven high, so this API sets the
 * GPIO output latch through @ref `GPIO_PinSet`.
 */
void BSP_OB_LED_Reset(void);

/**
 * @brief Toggles the active-low board on-board LED
 * @details
 * This API forwards to @ref `GPIO_PinToggle` for the board LED pin. The logical
 * LED state changes because the underlying PC13 output latch is inverted.
 */
void BSP_OB_LED_Toggle(void);

/**
 * @brief Deinitializes the board on-board LED GPIO
 * @returns Driver operation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: On-board LED GPIO was restored.
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Board LED GPIO mapping was invalid.
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: Internal GPIO staged-image update failed.
 * @details
 * This API forwards to @ref `GPIO_Deinit` for @ref `GPIO_OB_LED_PORT` /
 * @ref `GPIO_OB_LED_PIN`, restoring the pin to the GPIO reset-style floating
 * input configuration used by the driver.
 */
driver_status_t BSP_OB_LED_Deinit(void);

// ==================================================================================================== //
// Board UART Mapping
// ==================================================================================================== //

/**
 * @brief USART peripheral instance used by the board full-duplex UART
 * @def BSP_USART_INSTANCE
 * @details
 * Every BSP_USART_* API uses USART1's reset-default PA9/PA10 board route.
 * Defining this macro does not enable USART1's clock or peripheral state.
 * Accepted values:
 * - @ref `USART1`: Blue Pill board UART peripheral
 */
#define BSP_USART_INSTANCE						(USART1)
/**
 * @brief GPIO port carrying both board UART signals
 * @def BSP_USART_GPIO_PORT
 * @details
 * BSP_USART_Init() configures the TX and RX companion pin masks on GPIOA.
 * Defining this macro does not enable GPIOA's clock or configure pins.
 * Accepted values:
 * - @ref `GPIOA`: Port containing USART1 PA9/PA10 reset-default routing
 */
#define BSP_USART_GPIO_PORT					(GPIOA)
/**
 * @brief Board UART transmitter pin mask
 * @def BSP_USART_TX_PIN_MASK
 * @details
 * BSP_USART_Init() configures PA9 as 50 MHz alternate-function push-pull so
 * USART1, rather than GPIO software, drives the outgoing signal.
 * Accepted values:
 * - @ref `GPIO_PIN_9`: USART1 reset-default transmitter pin on GPIOA
 * @note This mapping neither configures the pin nor enables transmitter state
 */
#define BSP_USART_TX_PIN_MASK				((gpio_pin_t) GPIO_PIN_9)
/**
 * @brief Board UART receiver pin mask
 * @def BSP_USART_RX_PIN_MASK
 * @details
 * BSP_USART_Init() configures PA10 as floating input because the external UART
 * peer drives the incoming signal.
 * Accepted values:
 * - @ref `GPIO_PIN_10`: USART1 reset-default receiver pin on GPIOA
 * @note This mapping neither configures the pin nor enables receiver state
 */
#define BSP_USART_RX_PIN_MASK				((gpio_pin_t) GPIO_PIN_10)
/**
 * @brief GPIOA clock gate required by the board UART pin route
 * @def BSP_USART_GPIO_CLOCK_ENABLE_MASK
 * @details
 * The application must enable this clock gate through
 * RCC_SetPeripheralClockState() before calling BSP_USART_Init(). The board
 * retains USART1's reset-default PA9/PA10 route and writes no AFIO register,
 * so AFIO's clock is unnecessary.
 * Accepted values:
 * - @ref `RCC_APB2ENR_IOPAEN`: GPIOA peripheral-clock gate
 * @note This resource is application-owned; BSP never mutates this clock gate
 */
#define BSP_USART_GPIO_CLOCK_ENABLE_MASK		(RCC_APB2ENR_IOPAEN)
/**
 * @brief USART1 clock gate required by the board UART capability
 * @def BSP_USART_CLOCK_ENABLE_MASK
 * @details
 * The application must enable this clock gate through
 * RCC_SetPeripheralClockState() before calling BSP_USART_Init(). USART Driver
 * APIs verify this gate but deliberately never mutate it.
 * Accepted values:
 * - @ref `RCC_APB2ENR_USART1EN`: USART1 peripheral-clock gate
 * @note This resource is application-owned; BSP never mutates this clock gate
 */
#define BSP_USART_CLOCK_ENABLE_MASK			(RCC_APB2ENR_USART1EN)

/**
 * @brief Fixed board UART baud-rate preset
 * @def BSP_USART_BAUD_RATE
 * @details
 * BSP_USART_Init() supplies this rate with fixed 8N1 and TX+RX policy.
 * Accepted values:
 * - @ref `USART_BAUD_RATE_115200`: Blue Pill board UART rate
 * @note This macro does not program USART BRR by itself
 */
#define BSP_USART_BAUD_RATE					(USART_BAUD_RATE_115200)

/**
 * @brief Deinitializes the board UART peripheral and both mapped GPIO pins
 * @details
 * Restores USART1 and PA9/PA10 through their respective Driver deconfiguration
 * APIs. RCC clock-gate state remains application-owned and unchanged.
 * @returns @ref driver_status_t "Board UART deinitialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: USART1 and both board UART pins were restored
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A fixed board GPIO or USART mapping was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1's clock gate was disabled or GPIO staging failed
 * @pre The application keeps @ref `BSP_USART_GPIO_CLOCK_ENABLE_MASK` and
 * @ref `BSP_USART_CLOCK_ENABLE_MASK` enabled until this API completes
 */
driver_status_t BSP_USART_Deinit(void);

/**
 * @brief Initializes the board full-duplex UART capability
 * @details
 * Configures PA9 as alternate-function push-pull and PA10 as floating input,
 * then configures and enables USART1 for 115200 baud, 8 data bits, no parity,
 * one stop bit, and both transmitter/receiver hardware. It composes GPIO and
 * USART public APIs only; it does not mutate an RCC clock gate.
 * @returns @ref driver_status_t "Board UART initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Board UART pins and USART1 were configured and enabled
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A fixed board GPIO or USART configuration was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: GPIO staging failed, USART1's clock gate was disabled, or its bus frequency was zero
 * @pre The application enabled @ref `BSP_USART_GPIO_CLOCK_ENABLE_MASK` and
 * @ref `BSP_USART_CLOCK_ENABLE_MASK` through RCC_SetPeripheralClockState()
 * before calling this API
 * @warning Reconfigures the complete mapped USART1 transport; no other client
 * may own USART1, PA9, or PA10 while this capability is active
 */
driver_status_t BSP_USART_Init(void);

/**
 * @brief Receives one byte through the board UART by bounded polling
 * @param[out] pByte Destination for the received byte
 * Expected values:
 * - Non-`NULL`: Storage for one received byte
 * @returns @ref driver_status_t "Board UART receive status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `pByte` was populated with one received byte
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pByte` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1's peripheral clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: No byte arrived within the bounded polling window
 * @pre BSP_USART_Init() completed successfully before calling this API
 * @note This forwarding path does not enable USART IRQ or DMA requests
 */
driver_status_t BSP_USART_ReceiveByte(uint8_t* const pByte);

/**
 * @brief Transmits one byte through the board UART by bounded polling
 * @param[in] byte Byte to transmit
 * Accepted values:
 * - `0x00U..0xFFU`: Any 8-bit UART payload value
 * @returns @ref driver_status_t "Board UART transmit status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `byte` was accepted by USART1 data register
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1's peripheral clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: USART1 data register did not become free within the bounded polling window
 * @pre BSP_USART_Init() completed successfully before calling this API
 * @note This forwarding path does not enable USART IRQ or DMA requests
 */
driver_status_t BSP_USART_TransmitByte(const uint8_t byte);

/**
 * @brief Formats and transmits a message through the board UART
 * @details
 * Brackets the variadic arguments and forwards them to USART_vprintf() for
 * the fixed board UART instance, reusing the USART Driver's bounded buffer
 * and per-byte polling behavior.
 * @param[in] pFormat `printf`-style format string
 * Expected values:
 * - Non-`NULL`: A null-terminated format string
 * @param[in] ... Variadic arguments matching @p `pFormat`'s conversion specifiers
 * @returns @ref driver_status_t "Board UART formatted-transmit status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every formatted byte was transmitted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pFormat` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_FAIL`: `vsnprintf()` reported a formatting error
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1's peripheral clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A formatted byte did not become transmittable within its bounded polling window
 * @pre BSP_USART_Init() completed successfully before calling this API
 */
driver_status_t BSP_USART_printf(const char* const pFormat, ...);

// ==================================================================================================== //
// Legacy Debug UART Compatibility
// ==================================================================================================== //

/**
 * @brief Compatibility alias for the board UART USART instance
 * @def GPIO_DEBUG_UART_INSTANCE
 * @details Use @ref `BSP_USART_INSTANCE` in new code.
 */
#define GPIO_DEBUG_UART_INSTANCE				BSP_USART_INSTANCE

/**
 * @brief Compatibility alias for the board UART GPIO port
 * @def GPIO_DEBUG_UART_PORT
 * @details Use @ref `BSP_USART_GPIO_PORT` in new code.
 */
#define GPIO_DEBUG_UART_PORT					BSP_USART_GPIO_PORT

/**
 * @brief Compatibility alias for the board UART transmitter pin
 * @def GPIO_DEBUG_UART_TX_PIN
 * @details Use @ref `BSP_USART_TX_PIN_MASK` in new code.
 */
#define GPIO_DEBUG_UART_TX_PIN					BSP_USART_TX_PIN_MASK

/**
 * @brief Compatibility alias for the board UART USART1 clock gate
 * @def GPIO_DEBUG_UART_CLOCK_ENABLE_MASK
 * @details Use @ref `BSP_USART_CLOCK_ENABLE_MASK` in new code.
 */
#define GPIO_DEBUG_UART_CLOCK_ENABLE_MASK		BSP_USART_CLOCK_ENABLE_MASK

/**
 * @brief Compatibility alias for the board UART GPIOA clock gate
 * @def GPIO_DEBUG_UART_GPIO_CLOCK_ENABLE_MASK
 * @details Use @ref `BSP_USART_GPIO_CLOCK_ENABLE_MASK` in new code.
 */
#define GPIO_DEBUG_UART_GPIO_CLOCK_ENABLE_MASK	BSP_USART_GPIO_CLOCK_ENABLE_MASK

/**
 * @brief Compatibility alias for the board UART baud-rate preset
 * @def GPIO_DEBUG_UART_BAUD_RATE
 * @details Use @ref `BSP_USART_BAUD_RATE` in new code.
 */
#define GPIO_DEBUG_UART_BAUD_RATE				BSP_USART_BAUD_RATE

/**
 * @brief Deinitializes the legacy debug-UART compatibility path
 * @details Delegates to BSP_USART_Deinit() without changing RCC clock-gate state.
 * @returns @ref driver_status_t "Legacy debug-UART deinitialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: BSP_USART_Deinit() completed successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Fixed board UART mapping was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1's clock gate was disabled or GPIO staging failed
 * @pre The application keeps both legacy clock-enable aliases enabled until
 * this API completes
 * @deprecated Use BSP_USART_Deinit(); this wrapper preserves existing callers
 */
driver_status_t BSP_Debug_UART_Deinit(void);

/**
 * @brief Initializes the legacy debug-UART compatibility path
 * @details Delegates to BSP_USART_Init() without changing its full-duplex contract.
 * @returns @ref driver_status_t "Legacy debug-UART initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: BSP_USART_Init() completed successfully
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Fixed board UART configuration was rejected
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: GPIO staging failed, USART1's clock gate was disabled, or its bus frequency was zero
 * @pre The application enabled both legacy clock-enable aliases before calling
 * this API
 * @deprecated Use BSP_USART_Init(); this wrapper preserves existing callers
 */
driver_status_t BSP_Debug_UART_Init(void);

/**
 * @brief Transmits a formatted legacy debug message through the board UART
 * @details Delegates to USART_vprintf() for the fixed board UART instance.
 * @param[in] pFormat `printf`-style format string
 * Expected values:
 * - Non-`NULL`: A null-terminated format string
 * @param[in] ... Variadic arguments matching @p `pFormat` conversion specifiers
 * @returns @ref driver_status_t "Legacy debug formatted-transmit status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every formatted byte was transmitted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pFormat` was `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_FAIL`: `vsnprintf()` reported a formatting error
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: USART1's peripheral clock gate was disabled
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: A formatted byte did not become transmittable within its bounded polling window
 * @pre BSP_Debug_UART_Init() completed successfully before calling this API
 * @deprecated Use BSP_USART_printf(); this wrapper preserves existing callers
 */
driver_status_t BSP_Debug_UART_Printf(const char* const pFormat, ...);

#endif /* STM32F103C8T6__ */

/** @} */ // BSP_01_BoardSupport

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BSP_H_ */
