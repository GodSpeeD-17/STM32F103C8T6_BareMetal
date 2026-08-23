/**
 * @file stm32f1xx_spi.h
 * @author Shrey Shah
 * @brief STM32F1 SPI/I2S Register-Layer Definitions
 * @version v1.0
 * @date 23-08-2026
 * @details
 * This file is the canonical Core-layer owner of the STM32F103C8T6 SPI/I2S
 * register map and raw register-field positions and masks. It depends only on
 * `stm32f1xx_utils.h`; communication policy, clock calculation, transaction
 * sequencing, DMA ownership, and interrupt handling remain responsibilities
 * of the future SPI Driver stack.
 */

// Header Guard
#ifndef STM32F1XX_SPI_H_
#define STM32F1XX_SPI_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "stm32f1xx_utils.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup SPI Serial Peripheral Interface (SPI/I2S)
 * @brief STM32F1 synchronous serial, audio, interrupt, DMA, and CRC infrastructure
 * @details
 * RM0008 describes the SPI1 and SPI2/I2S2 blocks as hardware engines that:
 * - operate as SPI controller or peripheral in full-duplex, receive-only, or
 *   bidirectional single-data-line modes,
 * - transfer 8-bit or 16-bit SPI frames with programmable clock polarity,
 *   clock phase, bit order, and controller baud-rate division,
 * - manage hardware or software slave selection,
 * - transfer payloads through separate transmit and receive buffers sharing
 *   the `SPIx_DR` address,
 * - expose transmit, receive, busy, mode-fault, overrun, underrun, and CRC
 *   state through `SPIx_SR`,
 * - gate buffer and error interrupt requests through `SPIx_CR2`,
 * - request receive and transmit DMA service through `SPIx_CR2`,
 * - calculate programmable 8-bit or 16-bit SPI CRC values, and
 * - multiplex SPI2 with the I2S2 audio interface configured through
 *   `SPI2_I2SCFGR` and `SPI2_I2SPR`.
 *
 * @section SPI_RegisterLayoutBrief Register Layout Brief
 * <table>
 * <tr><th>Register</th><th>Offset</th><th>Primary Practical Role</th></tr>
 * <tr><td><code>SPIx_CR1</code></td><td><code>0x00</code></td><td>SPI mode, wire direction, frame, clock, slave-selection, CRC, and operation control</td></tr>
 * <tr><td><code>SPIx_CR2</code></td><td><code>0x04</code></td><td>DMA requests, slave-select output, and interrupt-source control</td></tr>
 * <tr><td><code>SPIx_SR</code></td><td><code>0x08</code></td><td>Buffer readiness, transfer activity, protocol state, and error flags</td></tr>
 * <tr><td><code>SPIx_DR</code></td><td><code>0x0C</code></td><td>Shared receive/transmit data-port address</td></tr>
 * <tr><td><code>SPIx_CRCPR</code></td><td><code>0x10</code></td><td>Programmable SPI CRC polynomial</td></tr>
 * <tr><td><code>SPIx_RXCRCR</code></td><td><code>0x14</code></td><td>Last computed receive CRC</td></tr>
 * <tr><td><code>SPIx_TXCRCR</code></td><td><code>0x18</code></td><td>Last computed transmit CRC</td></tr>
 * <tr><td><code>SPIx_I2SCFGR</code></td><td><code>0x1C</code></td><td>SPI/I2S selection and I2S protocol, role, frame, and operation control</td></tr>
 * <tr><td><code>SPIx_I2SPR</code></td><td><code>0x20</code></td><td>I2S serial-clock divider and master-clock output control</td></tr>
 * </table>
 *
 * @section SPI_DeviceBoundary Device Boundary
 * STM32F103C8T6 implements SPI1 and SPI2. SPI2 additionally exposes I2S2;
 * SPI3/I2S3 belongs to larger STM32F103 variants and is intentionally not
 * mapped by this device-specific Core integration.
 *
 * This codebase currently documents SPI through one ownership level:
 * - Register layer: @ref `stm32f1xx_spi.h`
 *
 * Future LL, Codec, and Driver layers will consume this raw register
 * vocabulary without duplicating it.
 */

/**
 * @defgroup SPI_01_RegisterLayer SPI/I2S Register Layer
 * @ingroup SPI
 * @brief Raw STM32F1 SPI/I2S register structure and field definitions
 * @details
 * This layer mirrors hardware-visible state and data ports. Driver-facing
 * selectors, timing calculations, validation, transaction sequencing, DMA
 * integration, and interrupt policy belong above this Core register layer.
 */

/**
 * @addtogroup SPI_01_RegisterLayer
 * @{
 */

// ==================================================================================================== //
// SPI/I2S Register Defines
// ==================================================================================================== //

/**
 * @defgroup SPI_01_RegisterLayer_00_RegisterDefines SPI/I2S Register Bit Positions and Masks
 * @ingroup SPI_01_RegisterLayer
 * @brief Raw SPI/I2S register positions, widths, masks, and field-bit values
 * @details
 * Single-bit fields expose a position, a mask built with @ref REG_BIT_MASK,
 * and an unsuffixed mask alias. Multi-bit fields additionally expose a width
 * and use @ref REG_FIELD_MASK. Raw field-bit values use
 * @ref REG_FIELD_VALUE so every positioned value has one shared construction
 * path.
 * @{
 */

// ---------------------------------------------------------------------------------------------------- //
// SPIx_CR1
// ---------------------------------------------------------------------------------------------------- //

/** @brief Clock phase selection (`SPIx_CR1.CPHA`) bit position @def SPI_CR1_CPHA_Pos */
#define SPI_CR1_CPHA_Pos				((reg_bit_pos_t) 0U)
/** @brief Clock phase selection (`SPIx_CR1.CPHA`) bit mask @def SPI_CR1_CPHA_Msk */
#define SPI_CR1_CPHA_Msk				REG_BIT_MASK(SPI_CR1_CPHA_Pos)
/** @brief Clock phase selection (`SPIx_CR1.CPHA`) bit mask alias @def SPI_CR1_CPHA */
#define SPI_CR1_CPHA					SPI_CR1_CPHA_Msk

/** @brief Idle clock polarity selection (`SPIx_CR1.CPOL`) bit position @def SPI_CR1_CPOL_Pos */
#define SPI_CR1_CPOL_Pos				((reg_bit_pos_t) 1U)
/** @brief Idle clock polarity selection (`SPIx_CR1.CPOL`) bit mask @def SPI_CR1_CPOL_Msk */
#define SPI_CR1_CPOL_Msk				REG_BIT_MASK(SPI_CR1_CPOL_Pos)
/** @brief Idle clock polarity selection (`SPIx_CR1.CPOL`) bit mask alias @def SPI_CR1_CPOL */
#define SPI_CR1_CPOL					SPI_CR1_CPOL_Msk

/** @brief SPI controller-role selection (`SPIx_CR1.MSTR`) bit position @def SPI_CR1_MSTR_Pos */
#define SPI_CR1_MSTR_Pos				((reg_bit_pos_t) 2U)
/** @brief SPI controller-role selection (`SPIx_CR1.MSTR`) bit mask @def SPI_CR1_MSTR_Msk */
#define SPI_CR1_MSTR_Msk				REG_BIT_MASK(SPI_CR1_MSTR_Pos)
/** @brief SPI controller-role selection (`SPIx_CR1.MSTR`) bit mask alias @def SPI_CR1_MSTR */
#define SPI_CR1_MSTR					SPI_CR1_MSTR_Msk

/** @brief SPI controller baud-rate divider (`SPIx_CR1.BR[2:0]`) field position @def SPI_CR1_BR_Pos */
#define SPI_CR1_BR_Pos					((reg_bit_pos_t) 3U)
/** @brief SPI controller baud-rate divider (`SPIx_CR1.BR[2:0]`) field width @def SPI_CR1_BR_Width */
#define SPI_CR1_BR_Width				((reg_field_width_t) 3U)
/** @brief SPI controller baud-rate divider (`SPIx_CR1.BR[2:0]`) field mask @def SPI_CR1_BR_Msk */
#define SPI_CR1_BR_Msk					REG_FIELD_MASK(SPI_CR1_BR_Pos, SPI_CR1_BR_Width)
/** @brief SPI controller baud-rate divider (`SPIx_CR1.BR[2:0]`) field mask alias @def SPI_CR1_BR */
#define SPI_CR1_BR						SPI_CR1_BR_Msk
/** @brief SPI controller baud-rate divider (`SPIx_CR1.BR[0]`) raw field bit 0 mask @def SPI_CR1_BR_0 */
#define SPI_CR1_BR_0					REG_FIELD_VALUE(SPI_CR1_BR_Pos, 0x01UL)
/** @brief SPI controller baud-rate divider (`SPIx_CR1.BR[1]`) raw field bit 1 mask @def SPI_CR1_BR_1 */
#define SPI_CR1_BR_1					REG_FIELD_VALUE(SPI_CR1_BR_Pos, 0x02UL)
/** @brief SPI controller baud-rate divider (`SPIx_CR1.BR[2]`) raw field bit 2 mask @def SPI_CR1_BR_2 */
#define SPI_CR1_BR_2					REG_FIELD_VALUE(SPI_CR1_BR_Pos, 0x04UL)

/** @brief SPI operation enable (`SPIx_CR1.SPE`) bit position @def SPI_CR1_SPE_Pos */
#define SPI_CR1_SPE_Pos					((reg_bit_pos_t) 6U)
/** @brief SPI operation enable (`SPIx_CR1.SPE`) bit mask @def SPI_CR1_SPE_Msk */
#define SPI_CR1_SPE_Msk					REG_BIT_MASK(SPI_CR1_SPE_Pos)
/** @brief SPI operation enable (`SPIx_CR1.SPE`) bit mask alias @def SPI_CR1_SPE */
#define SPI_CR1_SPE						SPI_CR1_SPE_Msk

/** @brief Least-significant-bit-first frame selection (`SPIx_CR1.LSBFIRST`) bit position @def SPI_CR1_LSBFIRST_Pos */
#define SPI_CR1_LSBFIRST_Pos			((reg_bit_pos_t) 7U)
/** @brief Least-significant-bit-first frame selection (`SPIx_CR1.LSBFIRST`) bit mask @def SPI_CR1_LSBFIRST_Msk */
#define SPI_CR1_LSBFIRST_Msk			REG_BIT_MASK(SPI_CR1_LSBFIRST_Pos)
/** @brief Least-significant-bit-first frame selection (`SPIx_CR1.LSBFIRST`) bit mask alias @def SPI_CR1_LSBFIRST */
#define SPI_CR1_LSBFIRST				SPI_CR1_LSBFIRST_Msk

/** @brief Internal slave-select level (`SPIx_CR1.SSI`) bit position @def SPI_CR1_SSI_Pos */
#define SPI_CR1_SSI_Pos					((reg_bit_pos_t) 8U)
/** @brief Internal slave-select level (`SPIx_CR1.SSI`) bit mask @def SPI_CR1_SSI_Msk */
#define SPI_CR1_SSI_Msk					REG_BIT_MASK(SPI_CR1_SSI_Pos)
/** @brief Internal slave-select level (`SPIx_CR1.SSI`) bit mask alias @def SPI_CR1_SSI */
#define SPI_CR1_SSI						SPI_CR1_SSI_Msk

/** @brief Software slave management enable (`SPIx_CR1.SSM`) bit position @def SPI_CR1_SSM_Pos */
#define SPI_CR1_SSM_Pos					((reg_bit_pos_t) 9U)
/** @brief Software slave management enable (`SPIx_CR1.SSM`) bit mask @def SPI_CR1_SSM_Msk */
#define SPI_CR1_SSM_Msk					REG_BIT_MASK(SPI_CR1_SSM_Pos)
/** @brief Software slave management enable (`SPIx_CR1.SSM`) bit mask alias @def SPI_CR1_SSM */
#define SPI_CR1_SSM						SPI_CR1_SSM_Msk

/** @brief Two-line receive-only mode selection (`SPIx_CR1.RXONLY`) bit position @def SPI_CR1_RXONLY_Pos */
#define SPI_CR1_RXONLY_Pos				((reg_bit_pos_t) 10U)
/** @brief Two-line receive-only mode selection (`SPIx_CR1.RXONLY`) bit mask @def SPI_CR1_RXONLY_Msk */
#define SPI_CR1_RXONLY_Msk				REG_BIT_MASK(SPI_CR1_RXONLY_Pos)
/** @brief Two-line receive-only mode selection (`SPIx_CR1.RXONLY`) bit mask alias @def SPI_CR1_RXONLY */
#define SPI_CR1_RXONLY					SPI_CR1_RXONLY_Msk

/** @brief SPI data-frame width selection (`SPIx_CR1.DFF`) bit position @def SPI_CR1_DFF_Pos */
#define SPI_CR1_DFF_Pos					((reg_bit_pos_t) 11U)
/** @brief SPI data-frame width selection (`SPIx_CR1.DFF`) bit mask @def SPI_CR1_DFF_Msk */
#define SPI_CR1_DFF_Msk					REG_BIT_MASK(SPI_CR1_DFF_Pos)
/** @brief SPI data-frame width selection (`SPIx_CR1.DFF`) bit mask alias @def SPI_CR1_DFF */
#define SPI_CR1_DFF						SPI_CR1_DFF_Msk

/** @brief Next transmitted frame carries the SPI CRC (`SPIx_CR1.CRCNEXT`) bit position @def SPI_CR1_CRCNEXT_Pos */
#define SPI_CR1_CRCNEXT_Pos				((reg_bit_pos_t) 12U)
/** @brief Next transmitted frame carries the SPI CRC (`SPIx_CR1.CRCNEXT`) bit mask @def SPI_CR1_CRCNEXT_Msk */
#define SPI_CR1_CRCNEXT_Msk				REG_BIT_MASK(SPI_CR1_CRCNEXT_Pos)
/** @brief Next transmitted frame carries the SPI CRC (`SPIx_CR1.CRCNEXT`) bit mask alias @def SPI_CR1_CRCNEXT */
#define SPI_CR1_CRCNEXT					SPI_CR1_CRCNEXT_Msk

/** @brief SPI hardware CRC calculation enable (`SPIx_CR1.CRCEN`) bit position @def SPI_CR1_CRCEN_Pos */
#define SPI_CR1_CRCEN_Pos				((reg_bit_pos_t) 13U)
/** @brief SPI hardware CRC calculation enable (`SPIx_CR1.CRCEN`) bit mask @def SPI_CR1_CRCEN_Msk */
#define SPI_CR1_CRCEN_Msk				REG_BIT_MASK(SPI_CR1_CRCEN_Pos)
/** @brief SPI hardware CRC calculation enable (`SPIx_CR1.CRCEN`) bit mask alias @def SPI_CR1_CRCEN */
#define SPI_CR1_CRCEN					SPI_CR1_CRCEN_Msk

/** @brief Bidirectional-mode output enable (`SPIx_CR1.BIDIOE`) bit position @def SPI_CR1_BIDIOE_Pos */
#define SPI_CR1_BIDIOE_Pos				((reg_bit_pos_t) 14U)
/** @brief Bidirectional-mode output enable (`SPIx_CR1.BIDIOE`) bit mask @def SPI_CR1_BIDIOE_Msk */
#define SPI_CR1_BIDIOE_Msk				REG_BIT_MASK(SPI_CR1_BIDIOE_Pos)
/** @brief Bidirectional-mode output enable (`SPIx_CR1.BIDIOE`) bit mask alias @def SPI_CR1_BIDIOE */
#define SPI_CR1_BIDIOE					SPI_CR1_BIDIOE_Msk

/** @brief Bidirectional single-data-line mode enable (`SPIx_CR1.BIDIMODE`) bit position @def SPI_CR1_BIDIMODE_Pos */
#define SPI_CR1_BIDIMODE_Pos			((reg_bit_pos_t) 15U)
/** @brief Bidirectional single-data-line mode enable (`SPIx_CR1.BIDIMODE`) bit mask @def SPI_CR1_BIDIMODE_Msk */
#define SPI_CR1_BIDIMODE_Msk			REG_BIT_MASK(SPI_CR1_BIDIMODE_Pos)
/** @brief Bidirectional single-data-line mode enable (`SPIx_CR1.BIDIMODE`) bit mask alias @def SPI_CR1_BIDIMODE */
#define SPI_CR1_BIDIMODE				SPI_CR1_BIDIMODE_Msk

// ---------------------------------------------------------------------------------------------------- //
// SPIx_CR2
// ---------------------------------------------------------------------------------------------------- //

/** @brief Receive-buffer DMA request enable (`SPIx_CR2.RXDMAEN`) bit position @def SPI_CR2_RXDMAEN_Pos */
#define SPI_CR2_RXDMAEN_Pos				((reg_bit_pos_t) 0U)
/** @brief Receive-buffer DMA request enable (`SPIx_CR2.RXDMAEN`) bit mask @def SPI_CR2_RXDMAEN_Msk */
#define SPI_CR2_RXDMAEN_Msk				REG_BIT_MASK(SPI_CR2_RXDMAEN_Pos)
/** @brief Receive-buffer DMA request enable (`SPIx_CR2.RXDMAEN`) bit mask alias @def SPI_CR2_RXDMAEN */
#define SPI_CR2_RXDMAEN					SPI_CR2_RXDMAEN_Msk

/** @brief Transmit-buffer DMA request enable (`SPIx_CR2.TXDMAEN`) bit position @def SPI_CR2_TXDMAEN_Pos */
#define SPI_CR2_TXDMAEN_Pos				((reg_bit_pos_t) 1U)
/** @brief Transmit-buffer DMA request enable (`SPIx_CR2.TXDMAEN`) bit mask @def SPI_CR2_TXDMAEN_Msk */
#define SPI_CR2_TXDMAEN_Msk				REG_BIT_MASK(SPI_CR2_TXDMAEN_Pos)
/** @brief Transmit-buffer DMA request enable (`SPIx_CR2.TXDMAEN`) bit mask alias @def SPI_CR2_TXDMAEN */
#define SPI_CR2_TXDMAEN					SPI_CR2_TXDMAEN_Msk

/** @brief Controller-mode slave-select output enable (`SPIx_CR2.SSOE`) bit position @def SPI_CR2_SSOE_Pos */
#define SPI_CR2_SSOE_Pos				((reg_bit_pos_t) 2U)
/** @brief Controller-mode slave-select output enable (`SPIx_CR2.SSOE`) bit mask @def SPI_CR2_SSOE_Msk */
#define SPI_CR2_SSOE_Msk				REG_BIT_MASK(SPI_CR2_SSOE_Pos)
/** @brief Controller-mode slave-select output enable (`SPIx_CR2.SSOE`) bit mask alias @def SPI_CR2_SSOE */
#define SPI_CR2_SSOE					SPI_CR2_SSOE_Msk

/** @brief SPI/I2S error interrupt-request enable (`SPIx_CR2.ERRIE`) bit position @def SPI_CR2_ERRIE_Pos */
#define SPI_CR2_ERRIE_Pos				((reg_bit_pos_t) 5U)
/** @brief SPI/I2S error interrupt-request enable (`SPIx_CR2.ERRIE`) bit mask @def SPI_CR2_ERRIE_Msk */
#define SPI_CR2_ERRIE_Msk				REG_BIT_MASK(SPI_CR2_ERRIE_Pos)
/** @brief SPI/I2S error interrupt-request enable (`SPIx_CR2.ERRIE`) bit mask alias @def SPI_CR2_ERRIE */
#define SPI_CR2_ERRIE					SPI_CR2_ERRIE_Msk

/** @brief Receive-buffer-not-empty interrupt-request enable (`SPIx_CR2.RXNEIE`) bit position @def SPI_CR2_RXNEIE_Pos */
#define SPI_CR2_RXNEIE_Pos				((reg_bit_pos_t) 6U)
/** @brief Receive-buffer-not-empty interrupt-request enable (`SPIx_CR2.RXNEIE`) bit mask @def SPI_CR2_RXNEIE_Msk */
#define SPI_CR2_RXNEIE_Msk				REG_BIT_MASK(SPI_CR2_RXNEIE_Pos)
/** @brief Receive-buffer-not-empty interrupt-request enable (`SPIx_CR2.RXNEIE`) bit mask alias @def SPI_CR2_RXNEIE */
#define SPI_CR2_RXNEIE					SPI_CR2_RXNEIE_Msk

/** @brief Transmit-buffer-empty interrupt-request enable (`SPIx_CR2.TXEIE`) bit position @def SPI_CR2_TXEIE_Pos */
#define SPI_CR2_TXEIE_Pos				((reg_bit_pos_t) 7U)
/** @brief Transmit-buffer-empty interrupt-request enable (`SPIx_CR2.TXEIE`) bit mask @def SPI_CR2_TXEIE_Msk */
#define SPI_CR2_TXEIE_Msk				REG_BIT_MASK(SPI_CR2_TXEIE_Pos)
/** @brief Transmit-buffer-empty interrupt-request enable (`SPIx_CR2.TXEIE`) bit mask alias @def SPI_CR2_TXEIE */
#define SPI_CR2_TXEIE					SPI_CR2_TXEIE_Msk

// ---------------------------------------------------------------------------------------------------- //
// SPIx_SR
// ---------------------------------------------------------------------------------------------------- //

/** @brief Receive-buffer-not-empty state (`SPIx_SR.RXNE`) bit position @def SPI_SR_RXNE_Pos */
#define SPI_SR_RXNE_Pos					((reg_bit_pos_t) 0U)
/** @brief Receive-buffer-not-empty state (`SPIx_SR.RXNE`) bit mask @def SPI_SR_RXNE_Msk */
#define SPI_SR_RXNE_Msk					REG_BIT_MASK(SPI_SR_RXNE_Pos)
/** @brief Receive-buffer-not-empty state (`SPIx_SR.RXNE`) bit mask alias @def SPI_SR_RXNE */
#define SPI_SR_RXNE						SPI_SR_RXNE_Msk

/** @brief Transmit-buffer-empty state (`SPIx_SR.TXE`) bit position @def SPI_SR_TXE_Pos */
#define SPI_SR_TXE_Pos					((reg_bit_pos_t) 1U)
/** @brief Transmit-buffer-empty state (`SPIx_SR.TXE`) bit mask @def SPI_SR_TXE_Msk */
#define SPI_SR_TXE_Msk					REG_BIT_MASK(SPI_SR_TXE_Pos)
/** @brief Transmit-buffer-empty state (`SPIx_SR.TXE`) bit mask alias @def SPI_SR_TXE */
#define SPI_SR_TXE						SPI_SR_TXE_Msk

/** @brief I2S left/right channel state (`SPIx_SR.CHSIDE`) bit position @def SPI_SR_CHSIDE_Pos */
#define SPI_SR_CHSIDE_Pos				((reg_bit_pos_t) 2U)
/** @brief I2S left/right channel state (`SPIx_SR.CHSIDE`) bit mask @def SPI_SR_CHSIDE_Msk */
#define SPI_SR_CHSIDE_Msk				REG_BIT_MASK(SPI_SR_CHSIDE_Pos)
/** @brief I2S left/right channel state (`SPIx_SR.CHSIDE`) bit mask alias @def SPI_SR_CHSIDE */
#define SPI_SR_CHSIDE					SPI_SR_CHSIDE_Msk

/** @brief I2S underrun event (`SPIx_SR.UDR`) bit position @def SPI_SR_UDR_Pos */
#define SPI_SR_UDR_Pos					((reg_bit_pos_t) 3U)
/** @brief I2S underrun event (`SPIx_SR.UDR`) bit mask @def SPI_SR_UDR_Msk */
#define SPI_SR_UDR_Msk					REG_BIT_MASK(SPI_SR_UDR_Pos)
/** @brief I2S underrun event (`SPIx_SR.UDR`) bit mask alias @def SPI_SR_UDR */
#define SPI_SR_UDR						SPI_SR_UDR_Msk

/** @brief SPI receive CRC mismatch event (`SPIx_SR.CRCERR`) bit position @def SPI_SR_CRCERR_Pos */
#define SPI_SR_CRCERR_Pos				((reg_bit_pos_t) 4U)
/** @brief SPI receive CRC mismatch event (`SPIx_SR.CRCERR`) bit mask @def SPI_SR_CRCERR_Msk */
#define SPI_SR_CRCERR_Msk				REG_BIT_MASK(SPI_SR_CRCERR_Pos)
/** @brief SPI receive CRC mismatch event (`SPIx_SR.CRCERR`) bit mask alias @def SPI_SR_CRCERR */
#define SPI_SR_CRCERR					SPI_SR_CRCERR_Msk

/** @brief SPI controller mode-fault event (`SPIx_SR.MODF`) bit position @def SPI_SR_MODF_Pos */
#define SPI_SR_MODF_Pos					((reg_bit_pos_t) 5U)
/** @brief SPI controller mode-fault event (`SPIx_SR.MODF`) bit mask @def SPI_SR_MODF_Msk */
#define SPI_SR_MODF_Msk					REG_BIT_MASK(SPI_SR_MODF_Pos)
/** @brief SPI controller mode-fault event (`SPIx_SR.MODF`) bit mask alias @def SPI_SR_MODF */
#define SPI_SR_MODF						SPI_SR_MODF_Msk

/** @brief SPI/I2S receive-overrun event (`SPIx_SR.OVR`) bit position @def SPI_SR_OVR_Pos */
#define SPI_SR_OVR_Pos					((reg_bit_pos_t) 6U)
/** @brief SPI/I2S receive-overrun event (`SPIx_SR.OVR`) bit mask @def SPI_SR_OVR_Msk */
#define SPI_SR_OVR_Msk					REG_BIT_MASK(SPI_SR_OVR_Pos)
/** @brief SPI/I2S receive-overrun event (`SPIx_SR.OVR`) bit mask alias @def SPI_SR_OVR */
#define SPI_SR_OVR						SPI_SR_OVR_Msk

/** @brief SPI/I2S transfer-busy state (`SPIx_SR.BSY`) bit position @def SPI_SR_BSY_Pos */
#define SPI_SR_BSY_Pos					((reg_bit_pos_t) 7U)
/** @brief SPI/I2S transfer-busy state (`SPIx_SR.BSY`) bit mask @def SPI_SR_BSY_Msk */
#define SPI_SR_BSY_Msk					REG_BIT_MASK(SPI_SR_BSY_Pos)
/** @brief SPI/I2S transfer-busy state (`SPIx_SR.BSY`) bit mask alias @def SPI_SR_BSY */
#define SPI_SR_BSY						SPI_SR_BSY_Msk

// ---------------------------------------------------------------------------------------------------- //
// SPIx_DR
// ---------------------------------------------------------------------------------------------------- //

/** @brief SPI/I2S receive or transmit payload (`SPIx_DR.DR[15:0]`) field position @def SPI_DR_DR_Pos */
#define SPI_DR_DR_Pos					((reg_bit_pos_t) 0U)
/** @brief SPI/I2S receive or transmit payload (`SPIx_DR.DR[15:0]`) field width @def SPI_DR_DR_Width */
#define SPI_DR_DR_Width					((reg_field_width_t) 16U)
/** @brief SPI/I2S receive or transmit payload (`SPIx_DR.DR[15:0]`) field mask @def SPI_DR_DR_Msk */
#define SPI_DR_DR_Msk					REG_FIELD_MASK(SPI_DR_DR_Pos, SPI_DR_DR_Width)
/** @brief SPI/I2S receive or transmit payload (`SPIx_DR.DR[15:0]`) field mask alias @def SPI_DR_DR */
#define SPI_DR_DR						SPI_DR_DR_Msk

// ---------------------------------------------------------------------------------------------------- //
// SPIx_CRCPR
// ---------------------------------------------------------------------------------------------------- //

/** @brief SPI CRC polynomial (`SPIx_CRCPR.CRCPOLY[15:0]`) field position @def SPI_CRCPR_CRCPOLY_Pos */
#define SPI_CRCPR_CRCPOLY_Pos			((reg_bit_pos_t) 0U)
/** @brief SPI CRC polynomial (`SPIx_CRCPR.CRCPOLY[15:0]`) field width @def SPI_CRCPR_CRCPOLY_Width */
#define SPI_CRCPR_CRCPOLY_Width			((reg_field_width_t) 16U)
/** @brief SPI CRC polynomial (`SPIx_CRCPR.CRCPOLY[15:0]`) field mask @def SPI_CRCPR_CRCPOLY_Msk */
#define SPI_CRCPR_CRCPOLY_Msk			REG_FIELD_MASK(SPI_CRCPR_CRCPOLY_Pos, SPI_CRCPR_CRCPOLY_Width)
/** @brief SPI CRC polynomial (`SPIx_CRCPR.CRCPOLY[15:0]`) field mask alias @def SPI_CRCPR_CRCPOLY */
#define SPI_CRCPR_CRCPOLY				SPI_CRCPR_CRCPOLY_Msk

// ---------------------------------------------------------------------------------------------------- //
// SPIx_RXCRCR
// ---------------------------------------------------------------------------------------------------- //

/** @brief Computed SPI receive CRC (`SPIx_RXCRCR.RXCRC[15:0]`) field position @def SPI_RXCRCR_RXCRC_Pos */
#define SPI_RXCRCR_RXCRC_Pos			((reg_bit_pos_t) 0U)
/** @brief Computed SPI receive CRC (`SPIx_RXCRCR.RXCRC[15:0]`) field width @def SPI_RXCRCR_RXCRC_Width */
#define SPI_RXCRCR_RXCRC_Width			((reg_field_width_t) 16U)
/** @brief Computed SPI receive CRC (`SPIx_RXCRCR.RXCRC[15:0]`) field mask @def SPI_RXCRCR_RXCRC_Msk */
#define SPI_RXCRCR_RXCRC_Msk			REG_FIELD_MASK(SPI_RXCRCR_RXCRC_Pos, SPI_RXCRCR_RXCRC_Width)
/** @brief Computed SPI receive CRC (`SPIx_RXCRCR.RXCRC[15:0]`) field mask alias @def SPI_RXCRCR_RXCRC */
#define SPI_RXCRCR_RXCRC				SPI_RXCRCR_RXCRC_Msk

// ---------------------------------------------------------------------------------------------------- //
// SPIx_TXCRCR
// ---------------------------------------------------------------------------------------------------- //

/** @brief Computed SPI transmit CRC (`SPIx_TXCRCR.TXCRC[15:0]`) field position @def SPI_TXCRCR_TXCRC_Pos */
#define SPI_TXCRCR_TXCRC_Pos			((reg_bit_pos_t) 0U)
/** @brief Computed SPI transmit CRC (`SPIx_TXCRCR.TXCRC[15:0]`) field width @def SPI_TXCRCR_TXCRC_Width */
#define SPI_TXCRCR_TXCRC_Width			((reg_field_width_t) 16U)
/** @brief Computed SPI transmit CRC (`SPIx_TXCRCR.TXCRC[15:0]`) field mask @def SPI_TXCRCR_TXCRC_Msk */
#define SPI_TXCRCR_TXCRC_Msk			REG_FIELD_MASK(SPI_TXCRCR_TXCRC_Pos, SPI_TXCRCR_TXCRC_Width)
/** @brief Computed SPI transmit CRC (`SPIx_TXCRCR.TXCRC[15:0]`) field mask alias @def SPI_TXCRCR_TXCRC */
#define SPI_TXCRCR_TXCRC				SPI_TXCRCR_TXCRC_Msk

// ---------------------------------------------------------------------------------------------------- //
// SPIx_I2SCFGR
// ---------------------------------------------------------------------------------------------------- //

/** @brief I2S channel width selection (`SPIx_I2SCFGR.CHLEN`) bit position @def SPI_I2SCFGR_CHLEN_Pos */
#define SPI_I2SCFGR_CHLEN_Pos			((reg_bit_pos_t) 0U)
/** @brief I2S channel width selection (`SPIx_I2SCFGR.CHLEN`) bit mask @def SPI_I2SCFGR_CHLEN_Msk */
#define SPI_I2SCFGR_CHLEN_Msk			REG_BIT_MASK(SPI_I2SCFGR_CHLEN_Pos)
/** @brief I2S channel width selection (`SPIx_I2SCFGR.CHLEN`) bit mask alias @def SPI_I2SCFGR_CHLEN */
#define SPI_I2SCFGR_CHLEN				SPI_I2SCFGR_CHLEN_Msk

/** @brief I2S payload width selection (`SPIx_I2SCFGR.DATLEN[1:0]`) field position @def SPI_I2SCFGR_DATLEN_Pos */
#define SPI_I2SCFGR_DATLEN_Pos			((reg_bit_pos_t) 1U)
/** @brief I2S payload width selection (`SPIx_I2SCFGR.DATLEN[1:0]`) field width @def SPI_I2SCFGR_DATLEN_Width */
#define SPI_I2SCFGR_DATLEN_Width		((reg_field_width_t) 2U)
/** @brief I2S payload width selection (`SPIx_I2SCFGR.DATLEN[1:0]`) field mask @def SPI_I2SCFGR_DATLEN_Msk */
#define SPI_I2SCFGR_DATLEN_Msk			REG_FIELD_MASK(SPI_I2SCFGR_DATLEN_Pos, SPI_I2SCFGR_DATLEN_Width)
/** @brief I2S payload width selection (`SPIx_I2SCFGR.DATLEN[1:0]`) field mask alias @def SPI_I2SCFGR_DATLEN */
#define SPI_I2SCFGR_DATLEN				SPI_I2SCFGR_DATLEN_Msk

/** @brief I2S steady-state clock polarity (`SPIx_I2SCFGR.CKPOL`) bit position @def SPI_I2SCFGR_CKPOL_Pos */
#define SPI_I2SCFGR_CKPOL_Pos			((reg_bit_pos_t) 3U)
/** @brief I2S steady-state clock polarity (`SPIx_I2SCFGR.CKPOL`) bit mask @def SPI_I2SCFGR_CKPOL_Msk */
#define SPI_I2SCFGR_CKPOL_Msk			REG_BIT_MASK(SPI_I2SCFGR_CKPOL_Pos)
/** @brief I2S steady-state clock polarity (`SPIx_I2SCFGR.CKPOL`) bit mask alias @def SPI_I2SCFGR_CKPOL */
#define SPI_I2SCFGR_CKPOL				SPI_I2SCFGR_CKPOL_Msk

/** @brief I2S audio-standard selection (`SPIx_I2SCFGR.I2SSTD[1:0]`) field position @def SPI_I2SCFGR_I2SSTD_Pos */
#define SPI_I2SCFGR_I2SSTD_Pos			((reg_bit_pos_t) 4U)
/** @brief I2S audio-standard selection (`SPIx_I2SCFGR.I2SSTD[1:0]`) field width @def SPI_I2SCFGR_I2SSTD_Width */
#define SPI_I2SCFGR_I2SSTD_Width		((reg_field_width_t) 2U)
/** @brief I2S audio-standard selection (`SPIx_I2SCFGR.I2SSTD[1:0]`) field mask @def SPI_I2SCFGR_I2SSTD_Msk */
#define SPI_I2SCFGR_I2SSTD_Msk			REG_FIELD_MASK(SPI_I2SCFGR_I2SSTD_Pos, SPI_I2SCFGR_I2SSTD_Width)
/** @brief I2S audio-standard selection (`SPIx_I2SCFGR.I2SSTD[1:0]`) field mask alias @def SPI_I2SCFGR_I2SSTD */
#define SPI_I2SCFGR_I2SSTD				SPI_I2SCFGR_I2SSTD_Msk

/** @brief PCM long-frame synchronization selection (`SPIx_I2SCFGR.PCMSYNC`) bit position @def SPI_I2SCFGR_PCMSYNC_Pos */
#define SPI_I2SCFGR_PCMSYNC_Pos			((reg_bit_pos_t) 7U)
/** @brief PCM long-frame synchronization selection (`SPIx_I2SCFGR.PCMSYNC`) bit mask @def SPI_I2SCFGR_PCMSYNC_Msk */
#define SPI_I2SCFGR_PCMSYNC_Msk			REG_BIT_MASK(SPI_I2SCFGR_PCMSYNC_Pos)
/** @brief PCM long-frame synchronization selection (`SPIx_I2SCFGR.PCMSYNC`) bit mask alias @def SPI_I2SCFGR_PCMSYNC */
#define SPI_I2SCFGR_PCMSYNC				SPI_I2SCFGR_PCMSYNC_Msk

/** @brief I2S controller/peripheral and transfer-direction selection (`SPIx_I2SCFGR.I2SCFG[1:0]`) field position @def SPI_I2SCFGR_I2SCFG_Pos */
#define SPI_I2SCFGR_I2SCFG_Pos			((reg_bit_pos_t) 8U)
/** @brief I2S controller/peripheral and transfer-direction selection (`SPIx_I2SCFGR.I2SCFG[1:0]`) field width @def SPI_I2SCFGR_I2SCFG_Width */
#define SPI_I2SCFGR_I2SCFG_Width		((reg_field_width_t) 2U)
/** @brief I2S controller/peripheral and transfer-direction selection (`SPIx_I2SCFGR.I2SCFG[1:0]`) field mask @def SPI_I2SCFGR_I2SCFG_Msk */
#define SPI_I2SCFGR_I2SCFG_Msk			REG_FIELD_MASK(SPI_I2SCFGR_I2SCFG_Pos, SPI_I2SCFGR_I2SCFG_Width)
/** @brief I2S controller/peripheral and transfer-direction selection (`SPIx_I2SCFGR.I2SCFG[1:0]`) field mask alias @def SPI_I2SCFGR_I2SCFG */
#define SPI_I2SCFGR_I2SCFG				SPI_I2SCFGR_I2SCFG_Msk

/** @brief I2S operation enable (`SPIx_I2SCFGR.I2SE`) bit position @def SPI_I2SCFGR_I2SE_Pos */
#define SPI_I2SCFGR_I2SE_Pos			((reg_bit_pos_t) 10U)
/** @brief I2S operation enable (`SPIx_I2SCFGR.I2SE`) bit mask @def SPI_I2SCFGR_I2SE_Msk */
#define SPI_I2SCFGR_I2SE_Msk			REG_BIT_MASK(SPI_I2SCFGR_I2SE_Pos)
/** @brief I2S operation enable (`SPIx_I2SCFGR.I2SE`) bit mask alias @def SPI_I2SCFGR_I2SE */
#define SPI_I2SCFGR_I2SE				SPI_I2SCFGR_I2SE_Msk

/** @brief SPI or I2S operating-mode selection (`SPIx_I2SCFGR.I2SMOD`) bit position @def SPI_I2SCFGR_I2SMOD_Pos */
#define SPI_I2SCFGR_I2SMOD_Pos			((reg_bit_pos_t) 11U)
/** @brief SPI or I2S operating-mode selection (`SPIx_I2SCFGR.I2SMOD`) bit mask @def SPI_I2SCFGR_I2SMOD_Msk */
#define SPI_I2SCFGR_I2SMOD_Msk			REG_BIT_MASK(SPI_I2SCFGR_I2SMOD_Pos)
/** @brief SPI or I2S operating-mode selection (`SPIx_I2SCFGR.I2SMOD`) bit mask alias @def SPI_I2SCFGR_I2SMOD */
#define SPI_I2SCFGR_I2SMOD				SPI_I2SCFGR_I2SMOD_Msk

// ---------------------------------------------------------------------------------------------------- //
// SPIx_I2SPR
// ---------------------------------------------------------------------------------------------------- //

/** @brief I2S linear prescaler (`SPIx_I2SPR.I2SDIV[7:0]`) field position @def SPI_I2SPR_I2SDIV_Pos */
#define SPI_I2SPR_I2SDIV_Pos			((reg_bit_pos_t) 0U)
/** @brief I2S linear prescaler (`SPIx_I2SPR.I2SDIV[7:0]`) field width @def SPI_I2SPR_I2SDIV_Width */
#define SPI_I2SPR_I2SDIV_Width			((reg_field_width_t) 8U)
/** @brief I2S linear prescaler (`SPIx_I2SPR.I2SDIV[7:0]`) field mask @def SPI_I2SPR_I2SDIV_Msk */
#define SPI_I2SPR_I2SDIV_Msk			REG_FIELD_MASK(SPI_I2SPR_I2SDIV_Pos, SPI_I2SPR_I2SDIV_Width)
/** @brief I2S linear prescaler (`SPIx_I2SPR.I2SDIV[7:0]`) field mask alias @def SPI_I2SPR_I2SDIV */
#define SPI_I2SPR_I2SDIV				SPI_I2SPR_I2SDIV_Msk

/** @brief I2S odd-prescaler-factor selection (`SPIx_I2SPR.ODD`) bit position @def SPI_I2SPR_ODD_Pos */
#define SPI_I2SPR_ODD_Pos				((reg_bit_pos_t) 8U)
/** @brief I2S odd-prescaler-factor selection (`SPIx_I2SPR.ODD`) bit mask @def SPI_I2SPR_ODD_Msk */
#define SPI_I2SPR_ODD_Msk				REG_BIT_MASK(SPI_I2SPR_ODD_Pos)
/** @brief I2S odd-prescaler-factor selection (`SPIx_I2SPR.ODD`) bit mask alias @def SPI_I2SPR_ODD */
#define SPI_I2SPR_ODD					SPI_I2SPR_ODD_Msk

/** @brief I2S master-clock output enable (`SPIx_I2SPR.MCKOE`) bit position @def SPI_I2SPR_MCKOE_Pos */
#define SPI_I2SPR_MCKOE_Pos				((reg_bit_pos_t) 9U)
/** @brief I2S master-clock output enable (`SPIx_I2SPR.MCKOE`) bit mask @def SPI_I2SPR_MCKOE_Msk */
#define SPI_I2SPR_MCKOE_Msk				REG_BIT_MASK(SPI_I2SPR_MCKOE_Pos)
/** @brief I2S master-clock output enable (`SPIx_I2SPR.MCKOE`) bit mask alias @def SPI_I2SPR_MCKOE */
#define SPI_I2SPR_MCKOE					SPI_I2SPR_MCKOE_Msk

/** @} */ // SPI_01_RegisterLayer_00_RegisterDefines

// ==================================================================================================== //
// SPI/I2S Register Map
// ==================================================================================================== //

/**
 * @defgroup SPI_01_RegisterLayer_01_RegisterMap SPI/I2S Register Block Map
 * @ingroup SPI_01_RegisterLayer
 * @brief Memory-mapped SPI/I2S register block and practical register semantics
 * @details
 * @ref SPI_TypeDef is the raw peripheral view consumed by register-near code.
 * Full-register `.REG` members support register-image operations while
 * `.BIT` members expose named hardware fields for direct inspection.
 * @{
 */

/**
 * @brief SPI/I2S peripheral register block structure
 * @details Complete memory-mapped register map shared by SPI1 and SPI2/I2S2.
 * The two logical directions of `DR` share one address, while several status
 * flags require documented read/write sequences rather than generic clearing.
 * @see RM0008 Section 25.5 SPI registers
 * @struct SPI_TypeDef
 */
typedef volatile struct __SPI_TypeDef
{
	/**
	 * @section SPI_TypeDef_CR1 SPI Control Register 1 (CR1)
	 * @brief [R/W and action] SPI protocol, topology, frame, clock, CRC, and operation control
	 * @details
	 * Most communication-format fields must remain unchanged while SPI is
	 * enabled. `CRCNEXT` is a transfer-sequencing request rather than persistent
	 * policy; setting `CRCEN` also resets the hardware CRC calculators.
	 */
	union SPI_CR1
	{
		/** @brief Full 32-bit `SPIx_CR1` register image */
		_IO REG;
		/** @brief Named `SPIx_CR1` bitfield view */
		struct
		{
			_IO CPHA : 1;				/**< Clock phase selection */
			_IO CPOL : 1;				/**< Idle clock polarity selection */
			_IO MSTR : 1;				/**< SPI controller-role selection */
			_IO BR : 3;					/**< SPI controller baud-rate divider */
			_IO SPE : 1;				/**< SPI operation enable */
			_IO LSBFIRST : 1;			/**< Least-significant-bit-first frame selection */
			_IO SSI : 1;				/**< Internal slave-select level */
			_IO SSM : 1;				/**< Software slave management enable */
			_IO RXONLY : 1;				/**< Two-line receive-only mode selection */
			_IO DFF : 1;				/**< SPI data-frame width selection */
			_IO CRCNEXT : 1;			/**< Next transmitted frame carries the SPI CRC */
			_IO CRCEN : 1;				/**< SPI hardware CRC calculation enable */
			_IO BIDIOE : 1;				/**< Bidirectional-mode output enable */
			_IO BIDIMODE : 1;			/**< Bidirectional single-data-line mode enable */
			_IO reserved_1 : 16;		/**< Reserved */
		} BIT;
	} CR1;			/**< SPI control register 1 image and named-field views */

	/**
	 * @section SPI_TypeDef_CR2 SPI Control Register 2 (CR2)
	 * @brief [R/W] DMA request, slave-select output, and interrupt-source control
	 * @details
	 * DMA-source gates are independent from DMA channel configuration. Interrupt
	 * source gates are independent from NVIC line state, priority, and pending
	 * handling.
	 */
	union SPI_CR2
	{
		/** @brief Full 32-bit `SPIx_CR2` register image */
		_IO REG;
		/** @brief Named `SPIx_CR2` bitfield view */
		struct
		{
			_IO RXDMAEN : 1;			/**< Receive-buffer DMA request enable */
			_IO TXDMAEN : 1;			/**< Transmit-buffer DMA request enable */
			_IO SSOE : 1;				/**< Controller-mode slave-select output enable */
			_IO reserved_1 : 2;			/**< Reserved */
			_IO ERRIE : 1;				/**< SPI/I2S error interrupt-request enable */
			_IO RXNEIE : 1;				/**< Receive-buffer-not-empty interrupt-request enable */
			_IO TXEIE : 1;				/**< Transmit-buffer-empty interrupt-request enable */
			_IO reserved_2 : 24;		/**< Reserved */
		} BIT;
	} CR2;			/**< SPI control register 2 image and named-field views */

	/**
	 * @section SPI_TypeDef_SR SPI Status Register (SR)
	 * @brief [R and software-clear] Buffer, transfer, channel, and error state
	 * @details
	 * `CRCERR` clears when software writes `0`. `OVR`, `MODF`, and `UDR` clear
	 * only through their RM0008-defined register-access sequences. Reading or
	 * writing the complete register without respecting those semantics can lose
	 * events or trigger unintended state transitions.
	 */
	union SPI_SR
	{
		/** @brief Full 32-bit `SPIx_SR` event/state image */
		_IO REG;
		/** @brief Named `SPIx_SR` bitfield view */
		struct
		{
			_I RXNE : 1;				/**< Receive-buffer-not-empty state */
			_I TXE : 1;					/**< Transmit-buffer-empty state */
			_I CHSIDE : 1;				/**< I2S left/right channel state */
			_I UDR : 1;					/**< I2S underrun event */
			_IO CRCERR : 1;				/**< SPI CRC mismatch; write zero to clear */
			_I MODF : 1;				/**< SPI controller mode-fault event */
			_I OVR : 1;					/**< SPI/I2S receive-overrun event */
			_I BSY : 1;					/**< SPI/I2S transfer-busy state */
			_I reserved_1 : 24;			/**< Reserved */
		} BIT;
	} SR;			/**< SPI status register image and named-field views */

	/**
	 * @section SPI_TypeDef_DR SPI Data Register (DR)
	 * @brief [R/W data port] Separate receive and transmit buffers sharing one address
	 * @details
	 * Reading returns the receive buffer and participates in flag-clear
	 * sequences. Writing supplies the transmit buffer. In 8-bit SPI mode only
	 * the low byte participates; in 16-bit SPI and I2S modes the full field is
	 * transferred. This is a data port, not stable configuration storage.
	 */
	union SPI_DR
	{
		/** @brief Full 32-bit `SPIx_DR` data-port image */
		_IO REG;
		/** @brief Named `SPIx_DR` bitfield view */
		struct
		{
			_IO DR : 16;				/**< Receive or transmit frame payload */
			_IO reserved_1 : 16;		/**< Reserved */
		} BIT;
	} DR;			/**< Shared receive/transmit data-port image and named-field views */

	/**
	 * @section SPI_TypeDef_CRCPR SPI CRC Polynomial Register (CRCPR)
	 * @brief [R/W] Polynomial used by the SPI CRC calculators
	 * @details
	 * The reset polynomial is `0x0007`. Configuration belongs to SPI mode and
	 * must remain stable while the peripheral is enabled.
	 */
	union SPI_CRCPR
	{
		/** @brief Full 32-bit `SPIx_CRCPR` register image */
		_IO REG;
		/** @brief Named `SPIx_CRCPR` bitfield view */
		struct
		{
			_IO CRCPOLY : 16;			/**< SPI CRC polynomial */
			_IO reserved_1 : 16;		/**< Reserved */
		} BIT;
	} CRCPR;		/**< SPI CRC polynomial register image and named-field views */

	/**
	 * @section SPI_TypeDef_RXCRCR SPI Receive CRC Register (RXCRCR)
	 * @brief [R] Last receive CRC calculated by SPI hardware
	 * @details
	 * The value may be invalid while `SPIx_SR.BSY` is set. Eight-bit SPI mode
	 * uses only the low byte; sixteen-bit SPI mode uses the full field.
	 */
	union SPI_RXCRCR
	{
		/** @brief Full 32-bit `SPIx_RXCRCR` observation image */
		_I REG;
		/** @brief Named `SPIx_RXCRCR` bitfield view */
		struct
		{
			_I RXCRC : 16;				/**< Computed SPI receive CRC */
			_I reserved_1 : 16;			/**< Reserved */
		} BIT;
	} RXCRCR;		/**< SPI receive CRC observation and named-field views */

	/**
	 * @section SPI_TypeDef_TXCRCR SPI Transmit CRC Register (TXCRCR)
	 * @brief [R] Last transmit CRC calculated by SPI hardware
	 * @details
	 * The value may be invalid while `SPIx_SR.BSY` is set. Eight-bit SPI mode
	 * uses only the low byte; sixteen-bit SPI mode uses the full field.
	 */
	union SPI_TXCRCR
	{
		/** @brief Full 32-bit `SPIx_TXCRCR` observation image */
		_I REG;
		/** @brief Named `SPIx_TXCRCR` bitfield view */
		struct
		{
			_I TXCRC : 16;				/**< Computed SPI transmit CRC */
			_I reserved_1 : 16;			/**< Reserved */
		} BIT;
	} TXCRCR;		/**< SPI transmit CRC observation and named-field views */

	/**
	 * @section SPI_TypeDef_I2SCFGR SPI/I2S Configuration Register (I2SCFGR)
	 * @brief [R/W] SPI/I2S selection and I2S protocol, role, frame, and operation control
	 * @details
	 * On STM32F103C8T6 these fields provide the I2S2 function multiplexed with
	 * SPI2. Protocol, role, frame, and clock-polarity fields must be configured
	 * while I2S is disabled; `I2SMOD` must be changed while both SPI and I2S are
	 * disabled.
	 */
	union SPI_I2SCFGR
	{
		/** @brief Full 32-bit `SPIx_I2SCFGR` register image */
		_IO REG;
		/** @brief Named `SPIx_I2SCFGR` bitfield view */
		struct
		{
			_IO CHLEN : 1;				/**< I2S channel width selection */
			_IO DATLEN : 2;				/**< I2S payload width selection */
			_IO CKPOL : 1;				/**< I2S steady-state clock polarity */
			_IO I2SSTD : 2;				/**< I2S audio-standard selection */
			_IO reserved_1 : 1;			/**< Reserved */
			_IO PCMSYNC : 1;			/**< PCM long-frame synchronization selection */
			_IO I2SCFG : 2;				/**< I2S controller/peripheral and transfer-direction selection */
			_IO I2SE : 1;				/**< I2S operation enable */
			_IO I2SMOD : 1;				/**< SPI or I2S operating-mode selection */
			_IO reserved_2 : 20;		/**< Reserved */
		} BIT;
	} I2SCFGR;		/**< SPI/I2S configuration register image and named-field views */

	/**
	 * @section SPI_TypeDef_I2SPR SPI/I2S Prescaler Register (I2SPR)
	 * @brief [R/W] I2S serial-clock divider and master-clock output control
	 * @details
	 * The effective I2S divider is `(2 x I2SDIV) + ODD`; `I2SDIV` values `0`
	 * and `1` are forbidden. Prescaler and master-clock output fields must be
	 * configured while I2S is disabled.
	 */
	union SPI_I2SPR
	{
		/** @brief Full 32-bit `SPIx_I2SPR` register image */
		_IO REG;
		/** @brief Named `SPIx_I2SPR` bitfield view */
		struct
		{
			_IO I2SDIV : 8;				/**< I2S linear prescaler */
			_IO ODD : 1;				/**< I2S odd-prescaler-factor selection */
			_IO MCKOE : 1;				/**< I2S master-clock output enable */
			_IO reserved_1 : 22;		/**< Reserved */
		} BIT;
	} I2SPR;		/**< I2S prescaler register image and named-field views */
} SPI_TypeDef;

/** @} */ // SPI_01_RegisterLayer_01_RegisterMap

/** @} */ // SPI_01_RegisterLayer

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_SPI_H_ */
