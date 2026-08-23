/**
 * @file stm32f1xx_usart.h
 * @author Shrey Shah
 * @brief STM32F1 USART Register-Layer Definitions
 * @version v1.1
 * @date 23-08-2026
 */

// Header Guards
#ifndef STM32F1XX_USART_H_
#define STM32F1XX_USART_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx_utils.h"

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup USART Universal Synchronous Asynchronous Receiver Transmitter (USART)
 * @brief STM32F1 USART asynchronous/synchronous transmit, receive, and error/status infrastructure
 * @details
 * RM0008 describes the USART1/USART2/USART3-style block as the hardware engine
 * that:
 * - transmits and receives byte- or word-wide serial data through `USARTx_DR`,
 * - derives the baud rate from the peripheral kernel clock through
 *   `USARTx_BRR`,
 * - enables the transmitter, receiver, and USART itself through `USARTx_CR1`,
 * - configures word length, parity, and local interrupt sources through
 *   `USARTx_CR1`,
 * - configures synchronous clock, LIN break detection, and stop-bit count
 *   through `USARTx_CR2`,
 * - configures IrDA, Smartcard, half-duplex, DMA, and hardware flow-control
 *   behavior through `USARTx_CR3`,
 * - reports parity/framing/noise/overrun errors, IDLE, RXNE, TC, TXE, LIN
 *   break, and CTS status through `USARTx_SR`,
 * - configures Smartcard guard time and IrDA/Smartcard prescaler through
 *   `USARTx_GTPR`.
 *
 * @section USART_RegisterLayoutBrief Register Layout Brief
 * <table>
 * <tr><th>Register</th><th>Offset</th><th>Primary Practical Role</th></tr>
 * <tr><td><code>USARTx_SR</code></td><td><code>0x00</code></td><td>Parity/framing/noise/overrun error, IDLE, RXNE, TC, TXE, LIN break, and CTS status flags</td></tr>
 * <tr><td><code>USARTx_DR</code></td><td><code>0x04</code></td><td>Read/write data register, 9-bit capable</td></tr>
 * <tr><td><code>USARTx_BRR</code></td><td><code>0x08</code></td><td>Baud rate mantissa/fraction divider</td></tr>
 * <tr><td><code>USARTx_CR1</code></td><td><code>0x0C</code></td><td>USART/transmitter/receiver enable, word length, parity, wakeup, and local interrupt enables</td></tr>
 * <tr><td><code>USARTx_CR2</code></td><td><code>0x10</code></td><td>Address mark, LIN break detection, synchronous clock control, stop-bit count, LIN mode enable</td></tr>
 * <tr><td><code>USARTx_CR3</code></td><td><code>0x14</code></td><td>Error interrupt, IrDA, half-duplex, Smartcard, DMA enable, and RTS/CTS flow control</td></tr>
 * <tr><td><code>USARTx_GTPR</code></td><td><code>0x18</code></td><td>Smartcard guard time and Smartcard/IrDA prescaler</td></tr>
 * </table>
 *
 * @see RM0008 Section 27.6 USART registers
 *
 * This codebase documents USART in layered ownership order:
 * - Register layer: @ref `stm32f1xx_usart.h`
 * - Driver selector vocabulary: @ref `usart_defines.h`
 * - Driver/orchestration layer: @ref `usart.h`
 */

/**
 * @defgroup USART_01_RegisterLayer USART Register Layer
 * @ingroup USART
 * @brief Raw STM32F1 USART register structure and hardware-visible register views
 * @details
 * This layer mirrors the hardware register map. It intentionally owns only raw
 * register structure layout and named bitfield views. Driver-facing selectors,
 * validation, encoding, read-modify-write batching, and interrupt policy belong
 * in higher USART layers.
 */

/**
 * @addtogroup USART_01_RegisterLayer
 * @{
 */

// ==================================================================================================== //
//											USART Register Defines										//
// ==================================================================================================== //

/**
 * @defgroup USART_01_RegisterLayer_00_RegisterDefines USART Register Bit Positions and Masks
 * @ingroup USART_01_RegisterLayer
 * @brief Raw USART register bit positions and masks for USART1/USART2/USART3-style peripherals
 * @details
 * These macros expose the hardware-visible field positions and masks used by
 * the USART codec and LL layers. They are intentionally raw register symbols;
 * driver-facing selectors and validation belong above this register layer.
 *
 * @{
 */

// ---------------------------------------------------------------------------------------------------- //
//											USARTx_SR														//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Parity mismatch detected on the current received word (`USARTx_SR.PE`) bit position @def USART_SR_PE_Pos */
#define USART_SR_PE_Pos						((reg_bit_pos_t) 0U)
/** @brief Parity mismatch detected on the current received word (`USARTx_SR.PE`) bit mask @def USART_SR_PE_Msk */
#define USART_SR_PE_Msk						REG_BIT_MASK(USART_SR_PE_Pos)
/** @brief Parity mismatch detected on the current received word (`USARTx_SR.PE`) bit mask alias @def USART_SR_PE */
#define USART_SR_PE							USART_SR_PE_Msk

/** @brief Stop bit not found at the expected sampling point (`USARTx_SR.FE`) bit position @def USART_SR_FE_Pos */
#define USART_SR_FE_Pos						((reg_bit_pos_t) 1U)
/** @brief Stop bit not found at the expected sampling point (`USARTx_SR.FE`) bit mask @def USART_SR_FE_Msk */
#define USART_SR_FE_Msk						REG_BIT_MASK(USART_SR_FE_Pos)
/** @brief Stop bit not found at the expected sampling point (`USARTx_SR.FE`) bit mask alias @def USART_SR_FE */
#define USART_SR_FE							USART_SR_FE_Msk

/** @brief Noise detected while sampling a received bit (`USARTx_SR.NE`) bit position @def USART_SR_NE_Pos */
#define USART_SR_NE_Pos						((reg_bit_pos_t) 2U)
/** @brief Noise detected while sampling a received bit (`USARTx_SR.NE`) bit mask @def USART_SR_NE_Msk */
#define USART_SR_NE_Msk						REG_BIT_MASK(USART_SR_NE_Pos)
/** @brief Noise detected while sampling a received bit (`USARTx_SR.NE`) bit mask alias @def USART_SR_NE */
#define USART_SR_NE							USART_SR_NE_Msk

/** @brief New word received while the previous word in `DR` was still unread (`USARTx_SR.ORE`) bit position @def USART_SR_ORE_Pos */
#define USART_SR_ORE_Pos					((reg_bit_pos_t) 3U)
/** @brief New word received while the previous word in `DR` was still unread (`USARTx_SR.ORE`) bit mask @def USART_SR_ORE_Msk */
#define USART_SR_ORE_Msk					REG_BIT_MASK(USART_SR_ORE_Pos)
/** @brief New word received while the previous word in `DR` was still unread (`USARTx_SR.ORE`) bit mask alias @def USART_SR_ORE */
#define USART_SR_ORE						USART_SR_ORE_Msk

/** @brief Idle frame detected on the receive line (`USARTx_SR.IDLE`) bit position @def USART_SR_IDLE_Pos */
#define USART_SR_IDLE_Pos					((reg_bit_pos_t) 4U)
/** @brief Idle frame detected on the receive line (`USARTx_SR.IDLE`) bit mask @def USART_SR_IDLE_Msk */
#define USART_SR_IDLE_Msk					REG_BIT_MASK(USART_SR_IDLE_Pos)
/** @brief Idle frame detected on the receive line (`USARTx_SR.IDLE`) bit mask alias @def USART_SR_IDLE */
#define USART_SR_IDLE						USART_SR_IDLE_Msk

/** @brief Received data is ready to read from `DR` (`USARTx_SR.RXNE`) bit position @def USART_SR_RXNE_Pos */
#define USART_SR_RXNE_Pos					((reg_bit_pos_t) 5U)
/** @brief Received data is ready to read from `DR` (`USARTx_SR.RXNE`) bit mask @def USART_SR_RXNE_Msk */
#define USART_SR_RXNE_Msk					REG_BIT_MASK(USART_SR_RXNE_Pos)
/** @brief Received data is ready to read from `DR` (`USARTx_SR.RXNE`) bit mask alias @def USART_SR_RXNE */
#define USART_SR_RXNE						USART_SR_RXNE_Msk

/** @brief Last transmitted frame, including its stop bit, has completed (`USARTx_SR.TC`) bit position @def USART_SR_TC_Pos */
#define USART_SR_TC_Pos						((reg_bit_pos_t) 6U)
/** @brief Last transmitted frame, including its stop bit, has completed (`USARTx_SR.TC`) bit mask @def USART_SR_TC_Msk */
#define USART_SR_TC_Msk						REG_BIT_MASK(USART_SR_TC_Pos)
/** @brief Last transmitted frame, including its stop bit, has completed (`USARTx_SR.TC`) bit mask alias @def USART_SR_TC */
#define USART_SR_TC							USART_SR_TC_Msk

/** @brief Transmit data register is empty and ready to accept the next byte (`USARTx_SR.TXE`) bit position @def USART_SR_TXE_Pos */
#define USART_SR_TXE_Pos					((reg_bit_pos_t) 7U)
/** @brief Transmit data register is empty and ready to accept the next byte (`USARTx_SR.TXE`) bit mask @def USART_SR_TXE_Msk */
#define USART_SR_TXE_Msk					REG_BIT_MASK(USART_SR_TXE_Pos)
/** @brief Transmit data register is empty and ready to accept the next byte (`USARTx_SR.TXE`) bit mask alias @def USART_SR_TXE */
#define USART_SR_TXE						USART_SR_TXE_Msk

/** @brief LIN break character detected on the receive line (`USARTx_SR.LBD`) bit position @def USART_SR_LBD_Pos */
#define USART_SR_LBD_Pos					((reg_bit_pos_t) 8U)
/** @brief LIN break character detected on the receive line (`USARTx_SR.LBD`) bit mask @def USART_SR_LBD_Msk */
#define USART_SR_LBD_Msk					REG_BIT_MASK(USART_SR_LBD_Pos)
/** @brief LIN break character detected on the receive line (`USARTx_SR.LBD`) bit mask alias @def USART_SR_LBD */
#define USART_SR_LBD						USART_SR_LBD_Msk

/** @brief `CTS` input pin changed state since it was last cleared (`USARTx_SR.CTS`) bit position @def USART_SR_CTS_Pos */
#define USART_SR_CTS_Pos					((reg_bit_pos_t) 9U)
/** @brief `CTS` input pin changed state since it was last cleared (`USARTx_SR.CTS`) bit mask @def USART_SR_CTS_Msk */
#define USART_SR_CTS_Msk					REG_BIT_MASK(USART_SR_CTS_Pos)
/** @brief `CTS` input pin changed state since it was last cleared (`USARTx_SR.CTS`) bit mask alias @def USART_SR_CTS */
#define USART_SR_CTS						USART_SR_CTS_Msk

// ---------------------------------------------------------------------------------------------------- //
//											USARTx_DR														//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Next byte/word to transmit when written, or the last received byte/word when read (`USARTx_DR.DR[8:0]`) field position @def USART_DR_DR_Pos */
#define USART_DR_DR_Pos						((reg_bit_pos_t) 0U)
/** @brief Next byte/word to transmit when written, or the last received byte/word when read (`USARTx_DR.DR[8:0]`) field width @def USART_DR_DR_Width */
#define USART_DR_DR_Width					((reg_field_width_t) 9U)
/** @brief Next byte/word to transmit when written, or the last received byte/word when read (`USARTx_DR.DR[8:0]`) field mask @def USART_DR_DR_Msk */
#define USART_DR_DR_Msk						REG_FIELD_MASK(USART_DR_DR_Pos, USART_DR_DR_Width)
/** @brief Next byte/word to transmit when written, or the last received byte/word when read (`USARTx_DR.DR[8:0]`) field mask alias @def USART_DR_DR */
#define USART_DR_DR							USART_DR_DR_Msk

// ---------------------------------------------------------------------------------------------------- //
//											USARTx_BRR														//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Fractional part of the USARTDIV baud-rate divisor, in 1/16ths of a bit period (`USARTx_BRR.DIV_FRACTION[3:0]`) field position @def USART_BRR_DIV_FRACTION_Pos */
#define USART_BRR_DIV_FRACTION_Pos			((reg_bit_pos_t) 0U)
/** @brief Fractional part of the USARTDIV baud-rate divisor, in 1/16ths of a bit period (`USARTx_BRR.DIV_FRACTION[3:0]`) field width @def USART_BRR_DIV_FRACTION_Width */
#define USART_BRR_DIV_FRACTION_Width		((reg_field_width_t) 4U)
/** @brief Fractional part of the USARTDIV baud-rate divisor, in 1/16ths of a bit period (`USARTx_BRR.DIV_FRACTION[3:0]`) field mask @def USART_BRR_DIV_FRACTION_Msk */
#define USART_BRR_DIV_FRACTION_Msk			REG_FIELD_MASK(USART_BRR_DIV_FRACTION_Pos, USART_BRR_DIV_FRACTION_Width)
/** @brief Fractional part of the USARTDIV baud-rate divisor, in 1/16ths of a bit period (`USARTx_BRR.DIV_FRACTION[3:0]`) field mask alias @def USART_BRR_DIV_FRACTION */
#define USART_BRR_DIV_FRACTION				USART_BRR_DIV_FRACTION_Msk

/** @brief Integer part of the USARTDIV baud-rate divisor (`USARTx_BRR.DIV_MANTISSA[11:0]`) field position @def USART_BRR_DIV_MANTISSA_Pos */
#define USART_BRR_DIV_MANTISSA_Pos			((reg_bit_pos_t) 4U)
/** @brief Integer part of the USARTDIV baud-rate divisor (`USARTx_BRR.DIV_MANTISSA[11:0]`) field width @def USART_BRR_DIV_MANTISSA_Width */
#define USART_BRR_DIV_MANTISSA_Width		((reg_field_width_t) 12U)
/** @brief Integer part of the USARTDIV baud-rate divisor (`USARTx_BRR.DIV_MANTISSA[11:0]`) field mask @def USART_BRR_DIV_MANTISSA_Msk */
#define USART_BRR_DIV_MANTISSA_Msk			REG_FIELD_MASK(USART_BRR_DIV_MANTISSA_Pos, USART_BRR_DIV_MANTISSA_Width)
/** @brief Integer part of the USARTDIV baud-rate divisor (`USARTx_BRR.DIV_MANTISSA[11:0]`) field mask alias @def USART_BRR_DIV_MANTISSA */
#define USART_BRR_DIV_MANTISSA				USART_BRR_DIV_MANTISSA_Msk

// ---------------------------------------------------------------------------------------------------- //
//											USARTx_CR1														//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Requests transmission of one break frame; hardware clears this bit once the break is sent (`USARTx_CR1.SBK`) bit position @def USART_CR1_SBK_Pos */
#define USART_CR1_SBK_Pos					((reg_bit_pos_t) 0U)
/** @brief Requests transmission of one break frame; hardware clears this bit once the break is sent (`USARTx_CR1.SBK`) bit mask @def USART_CR1_SBK_Msk */
#define USART_CR1_SBK_Msk					REG_BIT_MASK(USART_CR1_SBK_Pos)
/** @brief Requests transmission of one break frame; hardware clears this bit once the break is sent (`USARTx_CR1.SBK`) bit mask alias @def USART_CR1_SBK */
#define USART_CR1_SBK						USART_CR1_SBK_Msk

/** @brief Places the receiver in mute mode until the `WAKE`-selected wakeup condition occurs (`USARTx_CR1.RWU`) bit position @def USART_CR1_RWU_Pos */
#define USART_CR1_RWU_Pos					((reg_bit_pos_t) 1U)
/** @brief Places the receiver in mute mode until the `WAKE`-selected wakeup condition occurs (`USARTx_CR1.RWU`) bit mask @def USART_CR1_RWU_Msk */
#define USART_CR1_RWU_Msk					REG_BIT_MASK(USART_CR1_RWU_Pos)
/** @brief Places the receiver in mute mode until the `WAKE`-selected wakeup condition occurs (`USARTx_CR1.RWU`) bit mask alias @def USART_CR1_RWU */
#define USART_CR1_RWU						USART_CR1_RWU_Msk

/** @brief Enables the receiver block (`USARTx_CR1.RE`) bit position @def USART_CR1_RE_Pos */
#define USART_CR1_RE_Pos					((reg_bit_pos_t) 2U)
/** @brief Enables the receiver block (`USARTx_CR1.RE`) bit mask @def USART_CR1_RE_Msk */
#define USART_CR1_RE_Msk					REG_BIT_MASK(USART_CR1_RE_Pos)
/** @brief Enables the receiver block (`USARTx_CR1.RE`) bit mask alias @def USART_CR1_RE */
#define USART_CR1_RE						USART_CR1_RE_Msk

/** @brief Enables the transmitter block (`USARTx_CR1.TE`) bit position @def USART_CR1_TE_Pos */
#define USART_CR1_TE_Pos					((reg_bit_pos_t) 3U)
/** @brief Enables the transmitter block (`USARTx_CR1.TE`) bit mask @def USART_CR1_TE_Msk */
#define USART_CR1_TE_Msk					REG_BIT_MASK(USART_CR1_TE_Pos)
/** @brief Enables the transmitter block (`USARTx_CR1.TE`) bit mask alias @def USART_CR1_TE */
#define USART_CR1_TE						USART_CR1_TE_Msk

/** @brief Requests an interrupt when `SR.IDLE` is set (`USARTx_CR1.IDLEIE`) bit position @def USART_CR1_IDLEIE_Pos */
#define USART_CR1_IDLEIE_Pos				((reg_bit_pos_t) 4U)
/** @brief Requests an interrupt when `SR.IDLE` is set (`USARTx_CR1.IDLEIE`) bit mask @def USART_CR1_IDLEIE_Msk */
#define USART_CR1_IDLEIE_Msk				REG_BIT_MASK(USART_CR1_IDLEIE_Pos)
/** @brief Requests an interrupt when `SR.IDLE` is set (`USARTx_CR1.IDLEIE`) bit mask alias @def USART_CR1_IDLEIE */
#define USART_CR1_IDLEIE					USART_CR1_IDLEIE_Msk

/** @brief Requests an interrupt when `SR.RXNE` or `SR.ORE` is set (`USARTx_CR1.RXNEIE`) bit position @def USART_CR1_RXNEIE_Pos */
#define USART_CR1_RXNEIE_Pos				((reg_bit_pos_t) 5U)
/** @brief Requests an interrupt when `SR.RXNE` or `SR.ORE` is set (`USARTx_CR1.RXNEIE`) bit mask @def USART_CR1_RXNEIE_Msk */
#define USART_CR1_RXNEIE_Msk				REG_BIT_MASK(USART_CR1_RXNEIE_Pos)
/** @brief Requests an interrupt when `SR.RXNE` or `SR.ORE` is set (`USARTx_CR1.RXNEIE`) bit mask alias @def USART_CR1_RXNEIE */
#define USART_CR1_RXNEIE					USART_CR1_RXNEIE_Msk

/** @brief Requests an interrupt when `SR.TC` is set (`USARTx_CR1.TCIE`) bit position @def USART_CR1_TCIE_Pos */
#define USART_CR1_TCIE_Pos					((reg_bit_pos_t) 6U)
/** @brief Requests an interrupt when `SR.TC` is set (`USARTx_CR1.TCIE`) bit mask @def USART_CR1_TCIE_Msk */
#define USART_CR1_TCIE_Msk					REG_BIT_MASK(USART_CR1_TCIE_Pos)
/** @brief Requests an interrupt when `SR.TC` is set (`USARTx_CR1.TCIE`) bit mask alias @def USART_CR1_TCIE */
#define USART_CR1_TCIE						USART_CR1_TCIE_Msk

/** @brief Requests an interrupt when `SR.TXE` is set (`USARTx_CR1.TXEIE`) bit position @def USART_CR1_TXEIE_Pos */
#define USART_CR1_TXEIE_Pos					((reg_bit_pos_t) 7U)
/** @brief Requests an interrupt when `SR.TXE` is set (`USARTx_CR1.TXEIE`) bit mask @def USART_CR1_TXEIE_Msk */
#define USART_CR1_TXEIE_Msk					REG_BIT_MASK(USART_CR1_TXEIE_Pos)
/** @brief Requests an interrupt when `SR.TXE` is set (`USARTx_CR1.TXEIE`) bit mask alias @def USART_CR1_TXEIE */
#define USART_CR1_TXEIE						USART_CR1_TXEIE_Msk

/** @brief Requests an interrupt when `SR.PE` is set (`USARTx_CR1.PEIE`) bit position @def USART_CR1_PEIE_Pos */
#define USART_CR1_PEIE_Pos					((reg_bit_pos_t) 8U)
/** @brief Requests an interrupt when `SR.PE` is set (`USARTx_CR1.PEIE`) bit mask @def USART_CR1_PEIE_Msk */
#define USART_CR1_PEIE_Msk					REG_BIT_MASK(USART_CR1_PEIE_Pos)
/** @brief Requests an interrupt when `SR.PE` is set (`USARTx_CR1.PEIE`) bit mask alias @def USART_CR1_PEIE */
#define USART_CR1_PEIE						USART_CR1_PEIE_Msk

/** @brief Selects even or odd parity when `PCE` is set (`USARTx_CR1.PS`) bit position @def USART_CR1_PS_Pos */
#define USART_CR1_PS_Pos					((reg_bit_pos_t) 9U)
/** @brief Selects even or odd parity when `PCE` is set (`USARTx_CR1.PS`) bit mask @def USART_CR1_PS_Msk */
#define USART_CR1_PS_Msk					REG_BIT_MASK(USART_CR1_PS_Pos)
/** @brief Selects even or odd parity when `PCE` is set (`USARTx_CR1.PS`) bit mask alias @def USART_CR1_PS */
#define USART_CR1_PS						USART_CR1_PS_Msk

/** @brief Enables hardware parity generation on transmit and parity checking on receive (`USARTx_CR1.PCE`) bit position @def USART_CR1_PCE_Pos */
#define USART_CR1_PCE_Pos					((reg_bit_pos_t) 10U)
/** @brief Enables hardware parity generation on transmit and parity checking on receive (`USARTx_CR1.PCE`) bit mask @def USART_CR1_PCE_Msk */
#define USART_CR1_PCE_Msk					REG_BIT_MASK(USART_CR1_PCE_Pos)
/** @brief Enables hardware parity generation on transmit and parity checking on receive (`USARTx_CR1.PCE`) bit mask alias @def USART_CR1_PCE */
#define USART_CR1_PCE						USART_CR1_PCE_Msk

/** @brief Selects whether mute-mode wakeup triggers on an idle line or an address match (`USARTx_CR1.WAKE`) bit position @def USART_CR1_WAKE_Pos */
#define USART_CR1_WAKE_Pos					((reg_bit_pos_t) 11U)
/** @brief Selects whether mute-mode wakeup triggers on an idle line or an address match (`USARTx_CR1.WAKE`) bit mask @def USART_CR1_WAKE_Msk */
#define USART_CR1_WAKE_Msk					REG_BIT_MASK(USART_CR1_WAKE_Pos)
/** @brief Selects whether mute-mode wakeup triggers on an idle line or an address match (`USARTx_CR1.WAKE`) bit mask alias @def USART_CR1_WAKE */
#define USART_CR1_WAKE						USART_CR1_WAKE_Msk

/** @brief Selects 8-bit or 9-bit word length (`USARTx_CR1.M`) bit position @def USART_CR1_M_Pos */
#define USART_CR1_M_Pos						((reg_bit_pos_t) 12U)
/** @brief Selects 8-bit or 9-bit word length (`USARTx_CR1.M`) bit mask @def USART_CR1_M_Msk */
#define USART_CR1_M_Msk						REG_BIT_MASK(USART_CR1_M_Pos)
/** @brief Selects 8-bit or 9-bit word length (`USARTx_CR1.M`) bit mask alias @def USART_CR1_M */
#define USART_CR1_M							USART_CR1_M_Msk

/** @brief Enables the USART peripheral; disabling it after the current transfer completes reduces power consumption (`USARTx_CR1.UE`) bit position @def USART_CR1_UE_Pos */
#define USART_CR1_UE_Pos					((reg_bit_pos_t) 13U)
/** @brief Enables the USART peripheral; disabling it after the current transfer completes reduces power consumption (`USARTx_CR1.UE`) bit mask @def USART_CR1_UE_Msk */
#define USART_CR1_UE_Msk					REG_BIT_MASK(USART_CR1_UE_Pos)
/** @brief Enables the USART peripheral; disabling it after the current transfer completes reduces power consumption (`USARTx_CR1.UE`) bit mask alias @def USART_CR1_UE */
#define USART_CR1_UE						USART_CR1_UE_Msk

// ---------------------------------------------------------------------------------------------------- //
//											USARTx_CR2														//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Node address compared against the received word for address-mark mute-mode wakeup (`USARTx_CR2.ADD[3:0]`) field position @def USART_CR2_ADD_Pos */
#define USART_CR2_ADD_Pos					((reg_bit_pos_t) 0U)
/** @brief Node address compared against the received word for address-mark mute-mode wakeup (`USARTx_CR2.ADD[3:0]`) field width @def USART_CR2_ADD_Width */
#define USART_CR2_ADD_Width					((reg_field_width_t) 4U)
/** @brief Node address compared against the received word for address-mark mute-mode wakeup (`USARTx_CR2.ADD[3:0]`) field mask @def USART_CR2_ADD_Msk */
#define USART_CR2_ADD_Msk					REG_FIELD_MASK(USART_CR2_ADD_Pos, USART_CR2_ADD_Width)
/** @brief Node address compared against the received word for address-mark mute-mode wakeup (`USARTx_CR2.ADD[3:0]`) field mask alias @def USART_CR2_ADD */
#define USART_CR2_ADD						USART_CR2_ADD_Msk

/** @brief Selects the 10-bit or 11-bit LIN break detection length (`USARTx_CR2.LBDL`) bit position @def USART_CR2_LBDL_Pos */
#define USART_CR2_LBDL_Pos					((reg_bit_pos_t) 5U)
/** @brief Selects the 10-bit or 11-bit LIN break detection length (`USARTx_CR2.LBDL`) bit mask @def USART_CR2_LBDL_Msk */
#define USART_CR2_LBDL_Msk					REG_BIT_MASK(USART_CR2_LBDL_Pos)
/** @brief Selects the 10-bit or 11-bit LIN break detection length (`USARTx_CR2.LBDL`) bit mask alias @def USART_CR2_LBDL */
#define USART_CR2_LBDL						USART_CR2_LBDL_Msk

/** @brief Requests an interrupt when `SR.LBD` is set (`USARTx_CR2.LBDIE`) bit position @def USART_CR2_LBDIE_Pos */
#define USART_CR2_LBDIE_Pos					((reg_bit_pos_t) 6U)
/** @brief Requests an interrupt when `SR.LBD` is set (`USARTx_CR2.LBDIE`) bit mask @def USART_CR2_LBDIE_Msk */
#define USART_CR2_LBDIE_Msk					REG_BIT_MASK(USART_CR2_LBDIE_Pos)
/** @brief Requests an interrupt when `SR.LBD` is set (`USARTx_CR2.LBDIE`) bit mask alias @def USART_CR2_LBDIE */
#define USART_CR2_LBDIE						USART_CR2_LBDIE_Msk

/** @brief Outputs a clock pulse for the last transmitted data bit in synchronous mode (`USARTx_CR2.LBCL`) bit position @def USART_CR2_LBCL_Pos */
#define USART_CR2_LBCL_Pos					((reg_bit_pos_t) 8U)
/** @brief Outputs a clock pulse for the last transmitted data bit in synchronous mode (`USARTx_CR2.LBCL`) bit mask @def USART_CR2_LBCL_Msk */
#define USART_CR2_LBCL_Msk					REG_BIT_MASK(USART_CR2_LBCL_Pos)
/** @brief Outputs a clock pulse for the last transmitted data bit in synchronous mode (`USARTx_CR2.LBCL`) bit mask alias @def USART_CR2_LBCL */
#define USART_CR2_LBCL						USART_CR2_LBCL_Msk

/** @brief Selects the clock phase used in synchronous mode (`USARTx_CR2.CPHA`) bit position @def USART_CR2_CPHA_Pos */
#define USART_CR2_CPHA_Pos					((reg_bit_pos_t) 9U)
/** @brief Selects the clock phase used in synchronous mode (`USARTx_CR2.CPHA`) bit mask @def USART_CR2_CPHA_Msk */
#define USART_CR2_CPHA_Msk					REG_BIT_MASK(USART_CR2_CPHA_Pos)
/** @brief Selects the clock phase used in synchronous mode (`USARTx_CR2.CPHA`) bit mask alias @def USART_CR2_CPHA */
#define USART_CR2_CPHA						USART_CR2_CPHA_Msk

/** @brief Selects the clock idle-state polarity used in synchronous mode (`USARTx_CR2.CPOL`) bit position @def USART_CR2_CPOL_Pos */
#define USART_CR2_CPOL_Pos					((reg_bit_pos_t) 10U)
/** @brief Selects the clock idle-state polarity used in synchronous mode (`USARTx_CR2.CPOL`) bit mask @def USART_CR2_CPOL_Msk */
#define USART_CR2_CPOL_Msk					REG_BIT_MASK(USART_CR2_CPOL_Pos)
/** @brief Selects the clock idle-state polarity used in synchronous mode (`USARTx_CR2.CPOL`) bit mask alias @def USART_CR2_CPOL */
#define USART_CR2_CPOL						USART_CR2_CPOL_Msk

/** @brief Enables the synchronous clock output pin (`USARTx_CR2.CLKEN`) bit position @def USART_CR2_CLKEN_Pos */
#define USART_CR2_CLKEN_Pos					((reg_bit_pos_t) 11U)
/** @brief Enables the synchronous clock output pin (`USARTx_CR2.CLKEN`) bit mask @def USART_CR2_CLKEN_Msk */
#define USART_CR2_CLKEN_Msk					REG_BIT_MASK(USART_CR2_CLKEN_Pos)
/** @brief Enables the synchronous clock output pin (`USARTx_CR2.CLKEN`) bit mask alias @def USART_CR2_CLKEN */
#define USART_CR2_CLKEN						USART_CR2_CLKEN_Msk

/** @brief Selects how many stop bits terminate each transmitted/received frame (`USARTx_CR2.STOP[1:0]`) field position @def USART_CR2_STOP_Pos */
#define USART_CR2_STOP_Pos					((reg_bit_pos_t) 12U)
/** @brief Selects how many stop bits terminate each transmitted/received frame (`USARTx_CR2.STOP[1:0]`) field width @def USART_CR2_STOP_Width */
#define USART_CR2_STOP_Width				((reg_field_width_t) 2U)
/** @brief Selects how many stop bits terminate each transmitted/received frame (`USARTx_CR2.STOP[1:0]`) field mask @def USART_CR2_STOP_Msk */
#define USART_CR2_STOP_Msk					REG_FIELD_MASK(USART_CR2_STOP_Pos, USART_CR2_STOP_Width)
/** @brief Selects how many stop bits terminate each transmitted/received frame (`USARTx_CR2.STOP[1:0]`) field mask alias @def USART_CR2_STOP */
#define USART_CR2_STOP						USART_CR2_STOP_Msk
/** @brief Stop-bit count selection (`USARTx_CR2.STOP[0]`) raw field bit 0 mask @def USART_CR2_STOP_0 */
#define USART_CR2_STOP_0					REG_FIELD_VALUE(USART_CR2_STOP_Pos, 0x01UL)
/** @brief Stop-bit count selection (`USARTx_CR2.STOP[1]`) raw field bit 1 mask @def USART_CR2_STOP_1 */
#define USART_CR2_STOP_1					REG_FIELD_VALUE(USART_CR2_STOP_Pos, 0x02UL)
/** @brief Stop-bit count raw value: 1 stop bit per frame @def USART_CR2_STOP_1_STOP_BIT */
#define USART_CR2_STOP_1_STOP_BIT			((reg) 0x00UL)
/** @brief Stop-bit count raw value: 0.5 stop bit per frame, used only with Smartcard mode @def USART_CR2_STOP_0_5_STOP_BIT */
#define USART_CR2_STOP_0_5_STOP_BIT			(USART_CR2_STOP_0)
/** @brief Stop-bit count raw value: 2 stop bits per frame @def USART_CR2_STOP_2_STOP_BITS */
#define USART_CR2_STOP_2_STOP_BITS			(USART_CR2_STOP_1)
/** @brief Stop-bit count raw value: 1.5 stop bits per frame, used only with Smartcard mode @def USART_CR2_STOP_1_5_STOP_BITS */
#define USART_CR2_STOP_1_5_STOP_BITS		(USART_CR2_STOP_1 | USART_CR2_STOP_0)

/** @brief Enables LIN mode (`USARTx_CR2.LINEN`) bit position @def USART_CR2_LINEN_Pos */
#define USART_CR2_LINEN_Pos					((reg_bit_pos_t) 14U)
/** @brief Enables LIN mode (`USARTx_CR2.LINEN`) bit mask @def USART_CR2_LINEN_Msk */
#define USART_CR2_LINEN_Msk					REG_BIT_MASK(USART_CR2_LINEN_Pos)
/** @brief Enables LIN mode (`USARTx_CR2.LINEN`) bit mask alias @def USART_CR2_LINEN */
#define USART_CR2_LINEN						USART_CR2_LINEN_Msk

// ---------------------------------------------------------------------------------------------------- //
//											USARTx_CR3														//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Requests an interrupt on a framing, overrun, or noise error while `DMAR` is set (`USARTx_CR3.EIE`) bit position @def USART_CR3_EIE_Pos */
#define USART_CR3_EIE_Pos					((reg_bit_pos_t) 0U)
/** @brief Requests an interrupt on a framing, overrun, or noise error while `DMAR` is set (`USARTx_CR3.EIE`) bit mask @def USART_CR3_EIE_Msk */
#define USART_CR3_EIE_Msk					REG_BIT_MASK(USART_CR3_EIE_Pos)
/** @brief Requests an interrupt on a framing, overrun, or noise error while `DMAR` is set (`USARTx_CR3.EIE`) bit mask alias @def USART_CR3_EIE */
#define USART_CR3_EIE						USART_CR3_EIE_Msk

/** @brief Enables IrDA mode (`USARTx_CR3.IREN`) bit position @def USART_CR3_IREN_Pos */
#define USART_CR3_IREN_Pos					((reg_bit_pos_t) 1U)
/** @brief Enables IrDA mode (`USARTx_CR3.IREN`) bit mask @def USART_CR3_IREN_Msk */
#define USART_CR3_IREN_Msk					REG_BIT_MASK(USART_CR3_IREN_Pos)
/** @brief Enables IrDA mode (`USARTx_CR3.IREN`) bit mask alias @def USART_CR3_IREN */
#define USART_CR3_IREN						USART_CR3_IREN_Msk

/** @brief Selects IrDA normal or low-power pulse mode (`USARTx_CR3.IRLP`) bit position @def USART_CR3_IRLP_Pos */
#define USART_CR3_IRLP_Pos					((reg_bit_pos_t) 2U)
/** @brief Selects IrDA normal or low-power pulse mode (`USARTx_CR3.IRLP`) bit mask @def USART_CR3_IRLP_Msk */
#define USART_CR3_IRLP_Msk					REG_BIT_MASK(USART_CR3_IRLP_Pos)
/** @brief Selects IrDA normal or low-power pulse mode (`USARTx_CR3.IRLP`) bit mask alias @def USART_CR3_IRLP */
#define USART_CR3_IRLP						USART_CR3_IRLP_Msk

/** @brief Enables half-duplex single-wire mode by internally connecting TX and RX (`USARTx_CR3.HDSEL`) bit position @def USART_CR3_HDSEL_Pos */
#define USART_CR3_HDSEL_Pos					((reg_bit_pos_t) 3U)
/** @brief Enables half-duplex single-wire mode by internally connecting TX and RX (`USARTx_CR3.HDSEL`) bit mask @def USART_CR3_HDSEL_Msk */
#define USART_CR3_HDSEL_Msk					REG_BIT_MASK(USART_CR3_HDSEL_Pos)
/** @brief Enables half-duplex single-wire mode by internally connecting TX and RX (`USARTx_CR3.HDSEL`) bit mask alias @def USART_CR3_HDSEL */
#define USART_CR3_HDSEL						USART_CR3_HDSEL_Msk

/** @brief Enables automatic NACK transmission on a Smartcard parity error (`USARTx_CR3.NACK`) bit position @def USART_CR3_NACK_Pos */
#define USART_CR3_NACK_Pos					((reg_bit_pos_t) 4U)
/** @brief Enables automatic NACK transmission on a Smartcard parity error (`USARTx_CR3.NACK`) bit mask @def USART_CR3_NACK_Msk */
#define USART_CR3_NACK_Msk					REG_BIT_MASK(USART_CR3_NACK_Pos)
/** @brief Enables automatic NACK transmission on a Smartcard parity error (`USARTx_CR3.NACK`) bit mask alias @def USART_CR3_NACK */
#define USART_CR3_NACK						USART_CR3_NACK_Msk

/** @brief Enables Smartcard mode (`USARTx_CR3.SCEN`) bit position @def USART_CR3_SCEN_Pos */
#define USART_CR3_SCEN_Pos					((reg_bit_pos_t) 5U)
/** @brief Enables Smartcard mode (`USARTx_CR3.SCEN`) bit mask @def USART_CR3_SCEN_Msk */
#define USART_CR3_SCEN_Msk					REG_BIT_MASK(USART_CR3_SCEN_Pos)
/** @brief Enables Smartcard mode (`USARTx_CR3.SCEN`) bit mask alias @def USART_CR3_SCEN */
#define USART_CR3_SCEN						USART_CR3_SCEN_Msk

/** @brief Enables the receiver DMA request generated on `SR.RXNE` (`USARTx_CR3.DMAR`) bit position @def USART_CR3_DMAR_Pos */
#define USART_CR3_DMAR_Pos					((reg_bit_pos_t) 6U)
/** @brief Enables the receiver DMA request generated on `SR.RXNE` (`USARTx_CR3.DMAR`) bit mask @def USART_CR3_DMAR_Msk */
#define USART_CR3_DMAR_Msk					REG_BIT_MASK(USART_CR3_DMAR_Pos)
/** @brief Enables the receiver DMA request generated on `SR.RXNE` (`USARTx_CR3.DMAR`) bit mask alias @def USART_CR3_DMAR */
#define USART_CR3_DMAR						USART_CR3_DMAR_Msk

/** @brief Enables the transmitter DMA request generated on `SR.TXE` (`USARTx_CR3.DMAT`) bit position @def USART_CR3_DMAT_Pos */
#define USART_CR3_DMAT_Pos					((reg_bit_pos_t) 7U)
/** @brief Enables the transmitter DMA request generated on `SR.TXE` (`USARTx_CR3.DMAT`) bit mask @def USART_CR3_DMAT_Msk */
#define USART_CR3_DMAT_Msk					REG_BIT_MASK(USART_CR3_DMAT_Pos)
/** @brief Enables the transmitter DMA request generated on `SR.TXE` (`USARTx_CR3.DMAT`) bit mask alias @def USART_CR3_DMAT */
#define USART_CR3_DMAT						USART_CR3_DMAT_Msk

/** @brief Enables RTS hardware flow control; the receiver deasserts RTS while it cannot accept new data (`USARTx_CR3.RTSE`) bit position @def USART_CR3_RTSE_Pos */
#define USART_CR3_RTSE_Pos					((reg_bit_pos_t) 8U)
/** @brief Enables RTS hardware flow control; the receiver deasserts RTS while it cannot accept new data (`USARTx_CR3.RTSE`) bit mask @def USART_CR3_RTSE_Msk */
#define USART_CR3_RTSE_Msk					REG_BIT_MASK(USART_CR3_RTSE_Pos)
/** @brief Enables RTS hardware flow control; the receiver deasserts RTS while it cannot accept new data (`USARTx_CR3.RTSE`) bit mask alias @def USART_CR3_RTSE */
#define USART_CR3_RTSE						USART_CR3_RTSE_Msk

/** @brief Enables CTS hardware flow control; the transmitter waits for CTS before sending the next frame (`USARTx_CR3.CTSE`) bit position @def USART_CR3_CTSE_Pos */
#define USART_CR3_CTSE_Pos					((reg_bit_pos_t) 9U)
/** @brief Enables CTS hardware flow control; the transmitter waits for CTS before sending the next frame (`USARTx_CR3.CTSE`) bit mask @def USART_CR3_CTSE_Msk */
#define USART_CR3_CTSE_Msk					REG_BIT_MASK(USART_CR3_CTSE_Pos)
/** @brief Enables CTS hardware flow control; the transmitter waits for CTS before sending the next frame (`USARTx_CR3.CTSE`) bit mask alias @def USART_CR3_CTSE */
#define USART_CR3_CTSE						USART_CR3_CTSE_Msk

/** @brief Requests an interrupt when `SR.CTS` is set (`USARTx_CR3.CTSIE`) bit position @def USART_CR3_CTSIE_Pos */
#define USART_CR3_CTSIE_Pos					((reg_bit_pos_t) 10U)
/** @brief Requests an interrupt when `SR.CTS` is set (`USARTx_CR3.CTSIE`) bit mask @def USART_CR3_CTSIE_Msk */
#define USART_CR3_CTSIE_Msk					REG_BIT_MASK(USART_CR3_CTSIE_Pos)
/** @brief Requests an interrupt when `SR.CTS` is set (`USARTx_CR3.CTSIE`) bit mask alias @def USART_CR3_CTSIE */
#define USART_CR3_CTSIE						USART_CR3_CTSIE_Msk

// ---------------------------------------------------------------------------------------------------- //
//											USARTx_GTPR														//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Divides the USART kernel clock to derive the IrDA low-power baud clock or the Smartcard clock output (`USARTx_GTPR.PSC[7:0]`) field position @def USART_GTPR_PSC_Pos */
#define USART_GTPR_PSC_Pos					((reg_bit_pos_t) 0U)
/** @brief Divides the USART kernel clock to derive the IrDA low-power baud clock or the Smartcard clock output (`USARTx_GTPR.PSC[7:0]`) field width @def USART_GTPR_PSC_Width */
#define USART_GTPR_PSC_Width				((reg_field_width_t) 8U)
/** @brief Divides the USART kernel clock to derive the IrDA low-power baud clock or the Smartcard clock output (`USARTx_GTPR.PSC[7:0]`) field mask @def USART_GTPR_PSC_Msk */
#define USART_GTPR_PSC_Msk					REG_FIELD_MASK(USART_GTPR_PSC_Pos, USART_GTPR_PSC_Width)
/** @brief Divides the USART kernel clock to derive the IrDA low-power baud clock or the Smartcard clock output (`USARTx_GTPR.PSC[7:0]`) field mask alias @def USART_GTPR_PSC */
#define USART_GTPR_PSC						USART_GTPR_PSC_Msk

/** @brief Number of baud clock periods of guard time inserted after each transmitted Smartcard character (`USARTx_GTPR.GT[7:0]`) field position @def USART_GTPR_GT_Pos */
#define USART_GTPR_GT_Pos					((reg_bit_pos_t) 8U)
/** @brief Number of baud clock periods of guard time inserted after each transmitted Smartcard character (`USARTx_GTPR.GT[7:0]`) field width @def USART_GTPR_GT_Width */
#define USART_GTPR_GT_Width					((reg_field_width_t) 8U)
/** @brief Number of baud clock periods of guard time inserted after each transmitted Smartcard character (`USARTx_GTPR.GT[7:0]`) field mask @def USART_GTPR_GT_Msk */
#define USART_GTPR_GT_Msk					REG_FIELD_MASK(USART_GTPR_GT_Pos, USART_GTPR_GT_Width)
/** @brief Number of baud clock periods of guard time inserted after each transmitted Smartcard character (`USARTx_GTPR.GT[7:0]`) field mask alias @def USART_GTPR_GT */
#define USART_GTPR_GT						USART_GTPR_GT_Msk

/** @} */ // USART_01_RegisterLayer_00_RegisterDefines

// ==================================================================================================== //
//											USART Register Map												//
// ==================================================================================================== //

/**
 * @defgroup USART_01_RegisterLayer_01_RegisterMap USART Register Block Map
 * @ingroup USART_01_RegisterLayer
 * @brief Memory-mapped USART register block and practical register layout
 * @details
 * @section USART_RegisterMap_Theory Theory and Practical Role
 * @ref USART_TypeDef is the raw peripheral view consumed by USART low-level code.
 * It exposes full-register `.REG` access for register-image operations and
 * named `.BIT` views for direct field inspection where useful.
 *
 * @section USART_RegisterMap_Structure USART Register Block Structure
 * The structure below is ordered by the STM32F1 USART memory map.
 * @{
 */

/**
 * @brief USART register block structure
 * @details
 * Complete memory-mapped register map for the USART1/USART2/USART3-style
 * peripheral. On STM32F103C8T6, public base-address exposure determines
 * which concrete USART instances are available.
 *
 * @see RM0008 Section 27.6 USART registers
 * @typedef USART_TypeDef
 */
typedef volatile struct __USART_TypeDef
{
	/**
	 * @section USART_TypeDef_SR USART Status Register (SR)
	 * @brief [R/W] Parity/framing/noise/overrun error, IDLE, RXNE, TC, TXE, LIN break, and CTS status
	 * @details
	 * `USARTx_SR` reports USART status flags. `RXNE`/`IDLE`/`PE`/`FE`/`NE`/`ORE`
	 * clear only through the hardware-mandated sequence of reading `SR`
	 * followed by reading `DR`; `TC` and `CTS` are write-0-to-clear; `TXE` is
	 * read-only status. The USART codec/driver layers must apply the correct
	 * per-bit clearing mechanism rather than one uniform register write.
	 */
	union
	{
		/** @brief Full 32-bit `USARTx_SR` register image */
		_IO REG;
		/** @brief Named `USARTx_SR` bitfield view */
		struct
		{
			_IO PE : 1;				/**< Parity error */
			_IO FE : 1;				/**< Framing error */
			_IO NE : 1;				/**< Noise error */
			_IO ORE : 1;			/**< Overrun error */
			_IO IDLE : 1;			/**< IDLE line detected */
			_IO RXNE : 1;			/**< Read data register not empty */
			_IO TC : 1;				/**< Transmission complete */
			_IO TXE : 1;			/**< Transmit data register empty */
			_IO LBD : 1;			/**< LIN break detection */
			_IO CTS : 1;			/**< CTS flag */
			_IO reserved : 22;		/**< Reserved */
		} BIT;
	} SR;

	/**
	 * @section USART_TypeDef_DR USART Data Register (DR)
	 * @brief [R/W] Read/write data register, 9-bit capable
	 * @details
	 * `USARTx_DR` is a read/write access to the buffered receive and transmit
	 * data. Reading `DR` accesses the receive shadow register; writing `DR`
	 * accesses the transmit shadow register.
	 */
	union
	{
		/** @brief Full 32-bit `USARTx_DR` register image */
		_IO REG;
		/** @brief Named `USARTx_DR` bitfield view */
		struct
		{
			_IO DR : 9;				/**< Data value */
			_IO reserved : 23;		/**< Reserved */
		} BIT;
	} DR;

	/**
	 * @section USART_TypeDef_BRR USART Baud Rate Register (BRR)
	 * @brief [R/W] Baud rate mantissa/fraction divider
	 * @details
	 * `USARTx_BRR` holds the `USARTDIV` mantissa and fraction used to derive
	 * the baud rate from the USART kernel clock.
	 */
	union
	{
		/** @brief Full 32-bit `USARTx_BRR` register image */
		_IO REG;
		/** @brief Named `USARTx_BRR` bitfield view */
		struct
		{
			_IO DIV_FRACTION : 4;	/**< Fraction of USARTDIV */
			_IO DIV_MANTISSA : 12;	/**< Mantissa of USARTDIV */
			_IO reserved : 16;		/**< Reserved */
		} BIT;
	} BRR;

	/**
	 * @section USART_TypeDef_CR1 USART Control Register 1 (CR1)
	 * @brief [R/W] USART/transmitter/receiver enable, word length, parity, wakeup, and local interrupt enables
	 * @details
	 * `USARTx_CR1` owns the primary runtime controls: `UE` gates the whole
	 * peripheral, `TE`/`RE` gate the transmitter/receiver independently, and
	 * `M`/`PCE`/`PS` select word length and parity.
	 */
	union
	{
		/** @brief Full 32-bit `USARTx_CR1` register image */
		_IO REG;
		/** @brief Named `USARTx_CR1` bitfield view */
		struct
		{
			_IO SBK : 1;			/**< Send break */
			_IO RWU : 1;			/**< Receiver wakeup */
			_IO RE : 1;				/**< Receiver enable */
			_IO TE : 1;				/**< Transmitter enable */
			_IO IDLEIE : 1;			/**< IDLE interrupt enable */
			_IO RXNEIE : 1;			/**< RXNE interrupt enable */
			_IO TCIE : 1;			/**< Transmission complete interrupt enable */
			_IO TXEIE : 1;			/**< TXE interrupt enable */
			_IO PEIE : 1;			/**< PE interrupt enable */
			_IO PS : 1;				/**< Parity selection */
			_IO PCE : 1;			/**< Parity control enable */
			_IO WAKE : 1;			/**< Wakeup method */
			_IO M : 1;				/**< Word length */
			_IO UE : 1;				/**< USART enable */
			_IO reserved : 18;		/**< Reserved */
		} BIT;
	} CR1;

	/**
	 * @section USART_TypeDef_CR2 USART Control Register 2 (CR2)
	 * @brief [R/W] Address mark, LIN break detection, synchronous clock control, stop-bit count, LIN mode enable
	 * @details
	 * `USARTx_CR2` configures synchronous-clock behavior (`CPOL`/`CPHA`/
	 * `LBCL`/`CLKEN`), asynchronous stop-bit count, LIN break detection, and
	 * multiprocessor address-mark wakeup.
	 */
	union
	{
		/** @brief Full 32-bit `USARTx_CR2` register image */
		_IO REG;
		/** @brief Named `USARTx_CR2` bitfield view */
		struct
		{
			_IO ADD : 4;			/**< Address of the USART node */
			_IO reserved_1 : 1;		/**< Reserved */
			_IO LBDL : 1;			/**< LIN break detection length */
			_IO LBDIE : 1;			/**< LIN break detection interrupt enable */
			_IO reserved_2 : 1;		/**< Reserved */
			_IO LBCL : 1;			/**< Last bit clock pulse */
			_IO CPHA : 1;			/**< Clock phase */
			_IO CPOL : 1;			/**< Clock polarity */
			_IO CLKEN : 1;			/**< Clock enable */
			_IO STOP : 2;			/**< Stop bits selection */
			_IO LINEN : 1;			/**< LIN mode enable */
			_IO reserved_3 : 17;	/**< Reserved */
		} BIT;
	} CR2;

	/**
	 * @section USART_TypeDef_CR3 USART Control Register 3 (CR3)
	 * @brief [R/W] Error interrupt, IrDA, half-duplex, Smartcard, DMA enable, and RTS/CTS flow control
	 * @details
	 * `USARTx_CR3` configures the remaining USART operating modes and DMA
	 * request generation. `RTSE`/`CTSE` are the hardware flow-control fields
	 * relevant to plain UART mode; the rest are Smartcard/IrDA/DMA specific.
	 */
	union
	{
		/** @brief Full 32-bit `USARTx_CR3` register image */
		_IO REG;
		/** @brief Named `USARTx_CR3` bitfield view */
		struct
		{
			_IO EIE : 1;			/**< Error interrupt enable */
			_IO IREN : 1;			/**< IrDA mode enable */
			_IO IRLP : 1;			/**< IrDA low-power */
			_IO HDSEL : 1;			/**< Half-duplex selection */
			_IO NACK : 1;			/**< Smartcard NACK enable */
			_IO SCEN : 1;			/**< Smartcard mode enable */
			_IO DMAR : 1;			/**< DMA enable receiver */
			_IO DMAT : 1;			/**< DMA enable transmitter */
			_IO RTSE : 1;			/**< RTS enable */
			_IO CTSE : 1;			/**< CTS enable */
			_IO CTSIE : 1;			/**< CTS interrupt enable */
			_IO reserved : 21;		/**< Reserved */
		} BIT;
	} CR3;

	/**
	 * @section USART_TypeDef_GTPR USART Guard Time and Prescaler Register (GTPR)
	 * @brief [R/W] Smartcard guard time and Smartcard/IrDA prescaler
	 * @details
	 * `USARTx_GTPR` is only meaningful in Smartcard and IrDA modes; it is
	 * unused raw foundation for the current UART-only driver scope.
	 */
	union
	{
		/** @brief Full 32-bit `USARTx_GTPR` register image */
		_IO REG;
		/** @brief Named `USARTx_GTPR` bitfield view */
		struct
		{
			_IO PSC : 8;			/**< Prescaler value */
			_IO GT : 8;				/**< Guard time value */
			_IO reserved : 16;		/**< Reserved */
		} BIT;
	} GTPR;
} USART_TypeDef;

/** @} */ // USART_01_RegisterLayer_01_RegisterMap

/** @} */ // USART_01_RegisterLayer

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_USART_H_ */