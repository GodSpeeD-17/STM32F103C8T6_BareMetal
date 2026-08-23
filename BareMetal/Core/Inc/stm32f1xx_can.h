/**
 * @file stm32f1xx_can.h
 * @author Shrey Shah
 * @brief STM32F1 bxCAN Register-Layer Definitions
 * @version v1.0
 * @date 23-08-2026
 * @details
 * This file is the canonical Core-layer owner of the STM32F103C8T6 bxCAN
 * register map and raw register-field positions and masks. It depends only on
 * `stm32f1xx_utils.h`; protocol policy, bit-timing calculation, mailbox and
 * filter allocation, transaction sequencing, and interrupt handling remain
 * responsibilities of the future CAN Driver stack.
 */

// Header Guard
#ifndef STM32F1XX_CAN_H_
#define STM32F1XX_CAN_H_

// ==================================================================================================== //
// Includes
// ==================================================================================================== //
#include "stm32f1xx_utils.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup CAN Controller Area Network (bxCAN)
 * @brief STM32F1 CAN 2.0A/B communication, mailbox, FIFO, error, and acceptance-filter infrastructure
 * @details
 * STM32F103C8T6 implements one bxCAN controller with three transmit
 * mailboxes, two receive FIFOs, two receive output mailboxes, and fourteen
 * configurable acceptance-filter banks. This Core header exposes raw
 * register state only; a Driver must own initialization-mode sequencing,
 * bit timing, identifier packing, filter allocation, FIFO release, event
 * acknowledgement, and NVIC integration.
 *
 * @section CAN_RegisterLayoutBrief Register Layout Brief
 * <table>
 * <tr><th>Register Domain</th><th>Offsets</th><th>Primary Practical Role</th></tr>
 * <tr><td>Control/status</td><td><code>0x000..0x01C</code></td><td>Lifecycle requests, events, interrupt sources, errors, and bus timing</td></tr>
 * <tr><td>Transmit mailboxes</td><td><code>0x180..0x1AC</code></td><td>Three independently requested identifier, length/time, and payload slots</td></tr>
 * <tr><td>Receive FIFOs</td><td><code>0x1B0..0x1CC</code></td><td>Two FIFO output windows carrying identifier, metadata, and payload</td></tr>
 * <tr><td>Filter control</td><td><code>0x200..0x21C</code></td><td>Filter initialization, mode, scale, FIFO assignment, and activation</td></tr>
 * <tr><td>Filter banks</td><td><code>0x240..0x2AC</code></td><td>Fourteen pairs of programmable filter words</td></tr>
 * </table>
 *
 * @section CAN_DeviceBoundary Device Boundary
 * STM32F103C8T6 provides CAN1 only. The connectivity-line CAN2 controller and
 * its filter-bank split policy are outside this device boundary. Existing
 * `CAN_FMR_CAN2SB_*` symbols are retained solely as source-compatibility
 * vocabulary and must not be used against this device.
 */

/**
 * @defgroup CAN_01_RegisterLayer bxCAN Register Layer
 * @ingroup CAN
 * @brief Raw STM32F1 bxCAN register structure and field definitions
 */

/**
 * @addtogroup CAN_01_RegisterLayer
 * @{
 */

// ==================================================================================================== //
// bxCAN Device Constants
// ==================================================================================================== //

/** @brief Number of hardware transmit mailboxes implemented by CAN1 @def CAN_TX_MAILBOX_COUNT */
#define CAN_TX_MAILBOX_COUNT		((uint8_t) 3U)

/** @brief Number of hardware receive FIFO output mailboxes implemented by CAN1 @def CAN_RX_FIFO_COUNT */
#define CAN_RX_FIFO_COUNT			((uint8_t) 2U)

/** @brief Number of acceptance-filter banks implemented by CAN1 @def CAN_FILTER_BANK_COUNT */
#define CAN_FILTER_BANK_COUNT		((uint8_t) 14U)

// ==================================================================================================== //
// bxCAN Register Defines
// ==================================================================================================== //

/**
 * @defgroup CAN_01_RegisterLayer_00_RegisterDefines bxCAN Register Bit Positions and Masks
 * @ingroup CAN_01_RegisterLayer
 * @brief Raw bxCAN register positions, widths, masks, and field-bit values
 * @details
 * Single-bit fields expose a position, a mask built with @ref REG_BIT_MASK,
 * and an unsuffixed mask alias. Multi-bit fields additionally expose a width
 * and use @ref REG_FIELD_MASK. Mailbox and filter-bank-specific names are
 * retained for source compatibility with the former centralized definition
 * block.
 * @{
 */

// ---------------------------------------------------------------------------------------------------- //
// CAN_MCR
// ---------------------------------------------------------------------------------------------------- //
/** @brief Initialization-mode request (`CANx_MCR.INRQ`) bit position @def CAN_MCR_INRQ_Pos */
#define CAN_MCR_INRQ_Pos			((reg_bit_pos_t) 0U)
/** @brief Initialization-mode request (`CANx_MCR.INRQ`) bit mask @def CAN_MCR_INRQ_Msk */
#define CAN_MCR_INRQ_Msk			REG_BIT_MASK(CAN_MCR_INRQ_Pos)
/** @brief Initialization-mode request (`CANx_MCR.INRQ`) bit mask alias @def CAN_MCR_INRQ */
#define CAN_MCR_INRQ				CAN_MCR_INRQ_Msk

/** @brief Sleep-mode request (`CANx_MCR.SLEEP`) bit position @def CAN_MCR_SLEEP_Pos */
#define CAN_MCR_SLEEP_Pos			((reg_bit_pos_t) 1U)
/** @brief Sleep-mode request (`CANx_MCR.SLEEP`) bit mask @def CAN_MCR_SLEEP_Msk */
#define CAN_MCR_SLEEP_Msk			REG_BIT_MASK(CAN_MCR_SLEEP_Pos)
/** @brief Sleep-mode request (`CANx_MCR.SLEEP`) bit mask alias @def CAN_MCR_SLEEP */
#define CAN_MCR_SLEEP				CAN_MCR_SLEEP_Msk

/** @brief Transmit mailbox priority policy (`CANx_MCR.TXFP`) bit position @def CAN_MCR_TXFP_Pos */
#define CAN_MCR_TXFP_Pos			((reg_bit_pos_t) 2U)
/** @brief Transmit mailbox priority policy (`CANx_MCR.TXFP`) bit mask @def CAN_MCR_TXFP_Msk */
#define CAN_MCR_TXFP_Msk			REG_BIT_MASK(CAN_MCR_TXFP_Pos)
/** @brief Transmit mailbox priority policy (`CANx_MCR.TXFP`) bit mask alias @def CAN_MCR_TXFP */
#define CAN_MCR_TXFP				CAN_MCR_TXFP_Msk

/** @brief Receive FIFO locked-mode policy (`CANx_MCR.RFLM`) bit position @def CAN_MCR_RFLM_Pos */
#define CAN_MCR_RFLM_Pos			((reg_bit_pos_t) 3U)
/** @brief Receive FIFO locked-mode policy (`CANx_MCR.RFLM`) bit mask @def CAN_MCR_RFLM_Msk */
#define CAN_MCR_RFLM_Msk			REG_BIT_MASK(CAN_MCR_RFLM_Pos)
/** @brief Receive FIFO locked-mode policy (`CANx_MCR.RFLM`) bit mask alias @def CAN_MCR_RFLM */
#define CAN_MCR_RFLM				CAN_MCR_RFLM_Msk

/** @brief Automatic retransmission suppression (`CANx_MCR.NART`) bit position @def CAN_MCR_NART_Pos */
#define CAN_MCR_NART_Pos			((reg_bit_pos_t) 4U)
/** @brief Automatic retransmission suppression (`CANx_MCR.NART`) bit mask @def CAN_MCR_NART_Msk */
#define CAN_MCR_NART_Msk			REG_BIT_MASK(CAN_MCR_NART_Pos)
/** @brief Automatic retransmission suppression (`CANx_MCR.NART`) bit mask alias @def CAN_MCR_NART */
#define CAN_MCR_NART				CAN_MCR_NART_Msk

/** @brief Automatic wake-up mode (`CANx_MCR.AWUM`) bit position @def CAN_MCR_AWUM_Pos */
#define CAN_MCR_AWUM_Pos			((reg_bit_pos_t) 5U)
/** @brief Automatic wake-up mode (`CANx_MCR.AWUM`) bit mask @def CAN_MCR_AWUM_Msk */
#define CAN_MCR_AWUM_Msk			REG_BIT_MASK(CAN_MCR_AWUM_Pos)
/** @brief Automatic wake-up mode (`CANx_MCR.AWUM`) bit mask alias @def CAN_MCR_AWUM */
#define CAN_MCR_AWUM				CAN_MCR_AWUM_Msk

/** @brief Automatic bus-off recovery (`CANx_MCR.ABOM`) bit position @def CAN_MCR_ABOM_Pos */
#define CAN_MCR_ABOM_Pos			((reg_bit_pos_t) 6U)
/** @brief Automatic bus-off recovery (`CANx_MCR.ABOM`) bit mask @def CAN_MCR_ABOM_Msk */
#define CAN_MCR_ABOM_Msk			REG_BIT_MASK(CAN_MCR_ABOM_Pos)
/** @brief Automatic bus-off recovery (`CANx_MCR.ABOM`) bit mask alias @def CAN_MCR_ABOM */
#define CAN_MCR_ABOM				CAN_MCR_ABOM_Msk

/** @brief Time-triggered communication mode (`CANx_MCR.TTCM`) bit position @def CAN_MCR_TTCM_Pos */
#define CAN_MCR_TTCM_Pos			((reg_bit_pos_t) 7U)
/** @brief Time-triggered communication mode (`CANx_MCR.TTCM`) bit mask @def CAN_MCR_TTCM_Msk */
#define CAN_MCR_TTCM_Msk			REG_BIT_MASK(CAN_MCR_TTCM_Pos)
/** @brief Time-triggered communication mode (`CANx_MCR.TTCM`) bit mask alias @def CAN_MCR_TTCM */
#define CAN_MCR_TTCM				CAN_MCR_TTCM_Msk

/** @brief Software master-reset action (`CANx_MCR.RESET`) bit position @def CAN_MCR_RESET_Pos */
#define CAN_MCR_RESET_Pos			((reg_bit_pos_t) 15U)
/** @brief Software master-reset action (`CANx_MCR.RESET`) bit mask @def CAN_MCR_RESET_Msk */
#define CAN_MCR_RESET_Msk			REG_BIT_MASK(CAN_MCR_RESET_Pos)
/** @brief Software master-reset action (`CANx_MCR.RESET`) bit mask alias @def CAN_MCR_RESET */
#define CAN_MCR_RESET				CAN_MCR_RESET_Msk

/** @brief Debug-halt freeze control (`CANx_MCR.DBF`) bit position @def CAN_MCR_DBF_Pos */
#define CAN_MCR_DBF_Pos				((reg_bit_pos_t) 16U)
/** @brief Debug-halt freeze control (`CANx_MCR.DBF`) bit mask @def CAN_MCR_DBF_Msk */
#define CAN_MCR_DBF_Msk				REG_BIT_MASK(CAN_MCR_DBF_Pos)
/** @brief Debug-halt freeze control (`CANx_MCR.DBF`) bit mask alias @def CAN_MCR_DBF */
#define CAN_MCR_DBF					CAN_MCR_DBF_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_MSR
// ---------------------------------------------------------------------------------------------------- //
/** @brief Initialization-mode acknowledgement (`CANx_MSR.INAK`) bit position @def CAN_MSR_INAK_Pos */
#define CAN_MSR_INAK_Pos			((reg_bit_pos_t) 0U)
/** @brief Initialization-mode acknowledgement (`CANx_MSR.INAK`) bit mask @def CAN_MSR_INAK_Msk */
#define CAN_MSR_INAK_Msk			REG_BIT_MASK(CAN_MSR_INAK_Pos)
/** @brief Initialization-mode acknowledgement (`CANx_MSR.INAK`) bit mask alias @def CAN_MSR_INAK */
#define CAN_MSR_INAK				CAN_MSR_INAK_Msk

/** @brief Sleep-mode acknowledgement (`CANx_MSR.SLAK`) bit position @def CAN_MSR_SLAK_Pos */
#define CAN_MSR_SLAK_Pos			((reg_bit_pos_t) 1U)
/** @brief Sleep-mode acknowledgement (`CANx_MSR.SLAK`) bit mask @def CAN_MSR_SLAK_Msk */
#define CAN_MSR_SLAK_Msk			REG_BIT_MASK(CAN_MSR_SLAK_Pos)
/** @brief Sleep-mode acknowledgement (`CANx_MSR.SLAK`) bit mask alias @def CAN_MSR_SLAK */
#define CAN_MSR_SLAK				CAN_MSR_SLAK_Msk

/** @brief Error interrupt event (`CANx_MSR.ERRI`) bit position @def CAN_MSR_ERRI_Pos */
#define CAN_MSR_ERRI_Pos			((reg_bit_pos_t) 2U)
/** @brief Error interrupt event (`CANx_MSR.ERRI`) bit mask @def CAN_MSR_ERRI_Msk */
#define CAN_MSR_ERRI_Msk			REG_BIT_MASK(CAN_MSR_ERRI_Pos)
/** @brief Error interrupt event (`CANx_MSR.ERRI`) bit mask alias @def CAN_MSR_ERRI */
#define CAN_MSR_ERRI				CAN_MSR_ERRI_Msk

/** @brief Wake-up interrupt event (`CANx_MSR.WKUI`) bit position @def CAN_MSR_WKUI_Pos */
#define CAN_MSR_WKUI_Pos			((reg_bit_pos_t) 3U)
/** @brief Wake-up interrupt event (`CANx_MSR.WKUI`) bit mask @def CAN_MSR_WKUI_Msk */
#define CAN_MSR_WKUI_Msk			REG_BIT_MASK(CAN_MSR_WKUI_Pos)
/** @brief Wake-up interrupt event (`CANx_MSR.WKUI`) bit mask alias @def CAN_MSR_WKUI */
#define CAN_MSR_WKUI				CAN_MSR_WKUI_Msk

/** @brief Sleep acknowledgement interrupt event (`CANx_MSR.SLAKI`) bit position @def CAN_MSR_SLAKI_Pos */
#define CAN_MSR_SLAKI_Pos			((reg_bit_pos_t) 4U)
/** @brief Sleep acknowledgement interrupt event (`CANx_MSR.SLAKI`) bit mask @def CAN_MSR_SLAKI_Msk */
#define CAN_MSR_SLAKI_Msk			REG_BIT_MASK(CAN_MSR_SLAKI_Pos)
/** @brief Sleep acknowledgement interrupt event (`CANx_MSR.SLAKI`) bit mask alias @def CAN_MSR_SLAKI */
#define CAN_MSR_SLAKI				CAN_MSR_SLAKI_Msk

/** @brief Transmit activity state (`CANx_MSR.TXM`) bit position @def CAN_MSR_TXM_Pos */
#define CAN_MSR_TXM_Pos				((reg_bit_pos_t) 8U)
/** @brief Transmit activity state (`CANx_MSR.TXM`) bit mask @def CAN_MSR_TXM_Msk */
#define CAN_MSR_TXM_Msk				REG_BIT_MASK(CAN_MSR_TXM_Pos)
/** @brief Transmit activity state (`CANx_MSR.TXM`) bit mask alias @def CAN_MSR_TXM */
#define CAN_MSR_TXM					CAN_MSR_TXM_Msk

/** @brief Receive activity state (`CANx_MSR.RXM`) bit position @def CAN_MSR_RXM_Pos */
#define CAN_MSR_RXM_Pos				((reg_bit_pos_t) 9U)
/** @brief Receive activity state (`CANx_MSR.RXM`) bit mask @def CAN_MSR_RXM_Msk */
#define CAN_MSR_RXM_Msk				REG_BIT_MASK(CAN_MSR_RXM_Pos)
/** @brief Receive activity state (`CANx_MSR.RXM`) bit mask alias @def CAN_MSR_RXM */
#define CAN_MSR_RXM					CAN_MSR_RXM_Msk

/** @brief Last sampled CAN_RX level (`CANx_MSR.SAMP`) bit position @def CAN_MSR_SAMP_Pos */
#define CAN_MSR_SAMP_Pos			((reg_bit_pos_t) 10U)
/** @brief Last sampled CAN_RX level (`CANx_MSR.SAMP`) bit mask @def CAN_MSR_SAMP_Msk */
#define CAN_MSR_SAMP_Msk			REG_BIT_MASK(CAN_MSR_SAMP_Pos)
/** @brief Last sampled CAN_RX level (`CANx_MSR.SAMP`) bit mask alias @def CAN_MSR_SAMP */
#define CAN_MSR_SAMP				CAN_MSR_SAMP_Msk

/** @brief Current CAN_RX level (`CANx_MSR.RX`) bit position @def CAN_MSR_RX_Pos */
#define CAN_MSR_RX_Pos				((reg_bit_pos_t) 11U)
/** @brief Current CAN_RX level (`CANx_MSR.RX`) bit mask @def CAN_MSR_RX_Msk */
#define CAN_MSR_RX_Msk				REG_BIT_MASK(CAN_MSR_RX_Pos)
/** @brief Current CAN_RX level (`CANx_MSR.RX`) bit mask alias @def CAN_MSR_RX */
#define CAN_MSR_RX					CAN_MSR_RX_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TSR
// ---------------------------------------------------------------------------------------------------- //
/** @brief Transmit mailbox 0 request-complete event and acknowledgement (`CANx_TSR.RQCP0`) bit position @def CAN_TSR_RQCP0_Pos */
#define CAN_TSR_RQCP0_Pos			((reg_bit_pos_t) 0U)
/** @brief Transmit mailbox 0 request-complete event and acknowledgement (`CANx_TSR.RQCP0`) bit mask @def CAN_TSR_RQCP0_Msk */
#define CAN_TSR_RQCP0_Msk			REG_BIT_MASK(CAN_TSR_RQCP0_Pos)
/** @brief Transmit mailbox 0 request-complete event and acknowledgement (`CANx_TSR.RQCP0`) bit mask alias @def CAN_TSR_RQCP0 */
#define CAN_TSR_RQCP0				CAN_TSR_RQCP0_Msk

/** @brief Transmit mailbox 0 successful-transmission event (`CANx_TSR.TXOK0`) bit position @def CAN_TSR_TXOK0_Pos */
#define CAN_TSR_TXOK0_Pos			((reg_bit_pos_t) 1U)
/** @brief Transmit mailbox 0 successful-transmission event (`CANx_TSR.TXOK0`) bit mask @def CAN_TSR_TXOK0_Msk */
#define CAN_TSR_TXOK0_Msk			REG_BIT_MASK(CAN_TSR_TXOK0_Pos)
/** @brief Transmit mailbox 0 successful-transmission event (`CANx_TSR.TXOK0`) bit mask alias @def CAN_TSR_TXOK0 */
#define CAN_TSR_TXOK0				CAN_TSR_TXOK0_Msk

/** @brief Transmit mailbox 0 arbitration-lost event (`CANx_TSR.ALST0`) bit position @def CAN_TSR_ALST0_Pos */
#define CAN_TSR_ALST0_Pos			((reg_bit_pos_t) 2U)
/** @brief Transmit mailbox 0 arbitration-lost event (`CANx_TSR.ALST0`) bit mask @def CAN_TSR_ALST0_Msk */
#define CAN_TSR_ALST0_Msk			REG_BIT_MASK(CAN_TSR_ALST0_Pos)
/** @brief Transmit mailbox 0 arbitration-lost event (`CANx_TSR.ALST0`) bit mask alias @def CAN_TSR_ALST0 */
#define CAN_TSR_ALST0				CAN_TSR_ALST0_Msk

/** @brief Transmit mailbox 0 transmission-error event (`CANx_TSR.TERR0`) bit position @def CAN_TSR_TERR0_Pos */
#define CAN_TSR_TERR0_Pos			((reg_bit_pos_t) 3U)
/** @brief Transmit mailbox 0 transmission-error event (`CANx_TSR.TERR0`) bit mask @def CAN_TSR_TERR0_Msk */
#define CAN_TSR_TERR0_Msk			REG_BIT_MASK(CAN_TSR_TERR0_Pos)
/** @brief Transmit mailbox 0 transmission-error event (`CANx_TSR.TERR0`) bit mask alias @def CAN_TSR_TERR0 */
#define CAN_TSR_TERR0				CAN_TSR_TERR0_Msk

/** @brief Transmit mailbox 0 abort-request action (`CANx_TSR.ABRQ0`) bit position @def CAN_TSR_ABRQ0_Pos */
#define CAN_TSR_ABRQ0_Pos			((reg_bit_pos_t) 7U)
/** @brief Transmit mailbox 0 abort-request action (`CANx_TSR.ABRQ0`) bit mask @def CAN_TSR_ABRQ0_Msk */
#define CAN_TSR_ABRQ0_Msk			REG_BIT_MASK(CAN_TSR_ABRQ0_Pos)
/** @brief Transmit mailbox 0 abort-request action (`CANx_TSR.ABRQ0`) bit mask alias @def CAN_TSR_ABRQ0 */
#define CAN_TSR_ABRQ0				CAN_TSR_ABRQ0_Msk

/** @brief Transmit mailbox 1 request-complete event and acknowledgement (`CANx_TSR.RQCP1`) bit position @def CAN_TSR_RQCP1_Pos */
#define CAN_TSR_RQCP1_Pos			((reg_bit_pos_t) 8U)
/** @brief Transmit mailbox 1 request-complete event and acknowledgement (`CANx_TSR.RQCP1`) bit mask @def CAN_TSR_RQCP1_Msk */
#define CAN_TSR_RQCP1_Msk			REG_BIT_MASK(CAN_TSR_RQCP1_Pos)
/** @brief Transmit mailbox 1 request-complete event and acknowledgement (`CANx_TSR.RQCP1`) bit mask alias @def CAN_TSR_RQCP1 */
#define CAN_TSR_RQCP1				CAN_TSR_RQCP1_Msk

/** @brief Transmit mailbox 1 successful-transmission event (`CANx_TSR.TXOK1`) bit position @def CAN_TSR_TXOK1_Pos */
#define CAN_TSR_TXOK1_Pos			((reg_bit_pos_t) 9U)
/** @brief Transmit mailbox 1 successful-transmission event (`CANx_TSR.TXOK1`) bit mask @def CAN_TSR_TXOK1_Msk */
#define CAN_TSR_TXOK1_Msk			REG_BIT_MASK(CAN_TSR_TXOK1_Pos)
/** @brief Transmit mailbox 1 successful-transmission event (`CANx_TSR.TXOK1`) bit mask alias @def CAN_TSR_TXOK1 */
#define CAN_TSR_TXOK1				CAN_TSR_TXOK1_Msk

/** @brief Transmit mailbox 1 arbitration-lost event (`CANx_TSR.ALST1`) bit position @def CAN_TSR_ALST1_Pos */
#define CAN_TSR_ALST1_Pos			((reg_bit_pos_t) 10U)
/** @brief Transmit mailbox 1 arbitration-lost event (`CANx_TSR.ALST1`) bit mask @def CAN_TSR_ALST1_Msk */
#define CAN_TSR_ALST1_Msk			REG_BIT_MASK(CAN_TSR_ALST1_Pos)
/** @brief Transmit mailbox 1 arbitration-lost event (`CANx_TSR.ALST1`) bit mask alias @def CAN_TSR_ALST1 */
#define CAN_TSR_ALST1				CAN_TSR_ALST1_Msk

/** @brief Transmit mailbox 1 transmission-error event (`CANx_TSR.TERR1`) bit position @def CAN_TSR_TERR1_Pos */
#define CAN_TSR_TERR1_Pos			((reg_bit_pos_t) 11U)
/** @brief Transmit mailbox 1 transmission-error event (`CANx_TSR.TERR1`) bit mask @def CAN_TSR_TERR1_Msk */
#define CAN_TSR_TERR1_Msk			REG_BIT_MASK(CAN_TSR_TERR1_Pos)
/** @brief Transmit mailbox 1 transmission-error event (`CANx_TSR.TERR1`) bit mask alias @def CAN_TSR_TERR1 */
#define CAN_TSR_TERR1				CAN_TSR_TERR1_Msk

/** @brief Transmit mailbox 1 abort-request action (`CANx_TSR.ABRQ1`) bit position @def CAN_TSR_ABRQ1_Pos */
#define CAN_TSR_ABRQ1_Pos			((reg_bit_pos_t) 15U)
/** @brief Transmit mailbox 1 abort-request action (`CANx_TSR.ABRQ1`) bit mask @def CAN_TSR_ABRQ1_Msk */
#define CAN_TSR_ABRQ1_Msk			REG_BIT_MASK(CAN_TSR_ABRQ1_Pos)
/** @brief Transmit mailbox 1 abort-request action (`CANx_TSR.ABRQ1`) bit mask alias @def CAN_TSR_ABRQ1 */
#define CAN_TSR_ABRQ1				CAN_TSR_ABRQ1_Msk

/** @brief Transmit mailbox 2 request-complete event and acknowledgement (`CANx_TSR.RQCP2`) bit position @def CAN_TSR_RQCP2_Pos */
#define CAN_TSR_RQCP2_Pos			((reg_bit_pos_t) 16U)
/** @brief Transmit mailbox 2 request-complete event and acknowledgement (`CANx_TSR.RQCP2`) bit mask @def CAN_TSR_RQCP2_Msk */
#define CAN_TSR_RQCP2_Msk			REG_BIT_MASK(CAN_TSR_RQCP2_Pos)
/** @brief Transmit mailbox 2 request-complete event and acknowledgement (`CANx_TSR.RQCP2`) bit mask alias @def CAN_TSR_RQCP2 */
#define CAN_TSR_RQCP2				CAN_TSR_RQCP2_Msk

/** @brief Transmit mailbox 2 successful-transmission event (`CANx_TSR.TXOK2`) bit position @def CAN_TSR_TXOK2_Pos */
#define CAN_TSR_TXOK2_Pos			((reg_bit_pos_t) 17U)
/** @brief Transmit mailbox 2 successful-transmission event (`CANx_TSR.TXOK2`) bit mask @def CAN_TSR_TXOK2_Msk */
#define CAN_TSR_TXOK2_Msk			REG_BIT_MASK(CAN_TSR_TXOK2_Pos)
/** @brief Transmit mailbox 2 successful-transmission event (`CANx_TSR.TXOK2`) bit mask alias @def CAN_TSR_TXOK2 */
#define CAN_TSR_TXOK2				CAN_TSR_TXOK2_Msk

/** @brief Transmit mailbox 2 arbitration-lost event (`CANx_TSR.ALST2`) bit position @def CAN_TSR_ALST2_Pos */
#define CAN_TSR_ALST2_Pos			((reg_bit_pos_t) 18U)
/** @brief Transmit mailbox 2 arbitration-lost event (`CANx_TSR.ALST2`) bit mask @def CAN_TSR_ALST2_Msk */
#define CAN_TSR_ALST2_Msk			REG_BIT_MASK(CAN_TSR_ALST2_Pos)
/** @brief Transmit mailbox 2 arbitration-lost event (`CANx_TSR.ALST2`) bit mask alias @def CAN_TSR_ALST2 */
#define CAN_TSR_ALST2				CAN_TSR_ALST2_Msk

/** @brief Transmit mailbox 2 transmission-error event (`CANx_TSR.TERR2`) bit position @def CAN_TSR_TERR2_Pos */
#define CAN_TSR_TERR2_Pos			((reg_bit_pos_t) 19U)
/** @brief Transmit mailbox 2 transmission-error event (`CANx_TSR.TERR2`) bit mask @def CAN_TSR_TERR2_Msk */
#define CAN_TSR_TERR2_Msk			REG_BIT_MASK(CAN_TSR_TERR2_Pos)
/** @brief Transmit mailbox 2 transmission-error event (`CANx_TSR.TERR2`) bit mask alias @def CAN_TSR_TERR2 */
#define CAN_TSR_TERR2				CAN_TSR_TERR2_Msk

/** @brief Transmit mailbox 2 abort-request action (`CANx_TSR.ABRQ2`) bit position @def CAN_TSR_ABRQ2_Pos */
#define CAN_TSR_ABRQ2_Pos			((reg_bit_pos_t) 23U)
/** @brief Transmit mailbox 2 abort-request action (`CANx_TSR.ABRQ2`) bit mask @def CAN_TSR_ABRQ2_Msk */
#define CAN_TSR_ABRQ2_Msk			REG_BIT_MASK(CAN_TSR_ABRQ2_Pos)
/** @brief Transmit mailbox 2 abort-request action (`CANx_TSR.ABRQ2`) bit mask alias @def CAN_TSR_ABRQ2 */
#define CAN_TSR_ABRQ2				CAN_TSR_ABRQ2_Msk

/** @brief Lowest-priority empty-mailbox code (`CANx_TSR.CODE`) field position @def CAN_TSR_CODE_Pos */
#define CAN_TSR_CODE_Pos			((reg_bit_pos_t) 24U)
/** @brief Lowest-priority empty-mailbox code (`CANx_TSR.CODE`) field width @def CAN_TSR_CODE_Width */
#define CAN_TSR_CODE_Width			((reg_field_width_t) 2U)
/** @brief Lowest-priority empty-mailbox code (`CANx_TSR.CODE`) field mask @def CAN_TSR_CODE_Msk */
#define CAN_TSR_CODE_Msk			REG_FIELD_MASK(CAN_TSR_CODE_Pos, CAN_TSR_CODE_Width)
/** @brief Lowest-priority empty-mailbox code (`CANx_TSR.CODE`) field mask alias @def CAN_TSR_CODE */
#define CAN_TSR_CODE				CAN_TSR_CODE_Msk

/** @brief Transmit-mailbox empty-state vector (`CANx_TSR.TME`) field position @def CAN_TSR_TME_Pos */
#define CAN_TSR_TME_Pos				((reg_bit_pos_t) 26U)
/** @brief Transmit-mailbox empty-state vector (`CANx_TSR.TME`) field width @def CAN_TSR_TME_Width */
#define CAN_TSR_TME_Width			((reg_field_width_t) 3U)
/** @brief Transmit-mailbox empty-state vector (`CANx_TSR.TME`) field mask @def CAN_TSR_TME_Msk */
#define CAN_TSR_TME_Msk				REG_FIELD_MASK(CAN_TSR_TME_Pos, CAN_TSR_TME_Width)
/** @brief Transmit-mailbox empty-state vector (`CANx_TSR.TME`) field mask alias @def CAN_TSR_TME */
#define CAN_TSR_TME					CAN_TSR_TME_Msk

/** @brief Transmit mailbox 0 empty state (`CANx_TSR.TME0`) bit position @def CAN_TSR_TME0_Pos */
#define CAN_TSR_TME0_Pos			((reg_bit_pos_t) 26U)
/** @brief Transmit mailbox 0 empty state (`CANx_TSR.TME0`) bit mask @def CAN_TSR_TME0_Msk */
#define CAN_TSR_TME0_Msk			REG_BIT_MASK(CAN_TSR_TME0_Pos)
/** @brief Transmit mailbox 0 empty state (`CANx_TSR.TME0`) bit mask alias @def CAN_TSR_TME0 */
#define CAN_TSR_TME0				CAN_TSR_TME0_Msk

/** @brief Transmit mailbox 1 empty state (`CANx_TSR.TME1`) bit position @def CAN_TSR_TME1_Pos */
#define CAN_TSR_TME1_Pos			((reg_bit_pos_t) 27U)
/** @brief Transmit mailbox 1 empty state (`CANx_TSR.TME1`) bit mask @def CAN_TSR_TME1_Msk */
#define CAN_TSR_TME1_Msk			REG_BIT_MASK(CAN_TSR_TME1_Pos)
/** @brief Transmit mailbox 1 empty state (`CANx_TSR.TME1`) bit mask alias @def CAN_TSR_TME1 */
#define CAN_TSR_TME1				CAN_TSR_TME1_Msk

/** @brief Transmit mailbox 2 empty state (`CANx_TSR.TME2`) bit position @def CAN_TSR_TME2_Pos */
#define CAN_TSR_TME2_Pos			((reg_bit_pos_t) 28U)
/** @brief Transmit mailbox 2 empty state (`CANx_TSR.TME2`) bit mask @def CAN_TSR_TME2_Msk */
#define CAN_TSR_TME2_Msk			REG_BIT_MASK(CAN_TSR_TME2_Pos)
/** @brief Transmit mailbox 2 empty state (`CANx_TSR.TME2`) bit mask alias @def CAN_TSR_TME2 */
#define CAN_TSR_TME2				CAN_TSR_TME2_Msk

/** @brief Lowest-priority mailbox-state vector (`CANx_TSR.LOW`) field position @def CAN_TSR_LOW_Pos */
#define CAN_TSR_LOW_Pos				((reg_bit_pos_t) 29U)
/** @brief Lowest-priority mailbox-state vector (`CANx_TSR.LOW`) field width @def CAN_TSR_LOW_Width */
#define CAN_TSR_LOW_Width			((reg_field_width_t) 3U)
/** @brief Lowest-priority mailbox-state vector (`CANx_TSR.LOW`) field mask @def CAN_TSR_LOW_Msk */
#define CAN_TSR_LOW_Msk				REG_FIELD_MASK(CAN_TSR_LOW_Pos, CAN_TSR_LOW_Width)
/** @brief Lowest-priority mailbox-state vector (`CANx_TSR.LOW`) field mask alias @def CAN_TSR_LOW */
#define CAN_TSR_LOW					CAN_TSR_LOW_Msk

/** @brief Transmit mailbox 0 lowest-priority state (`CANx_TSR.LOW0`) bit position @def CAN_TSR_LOW0_Pos */
#define CAN_TSR_LOW0_Pos			((reg_bit_pos_t) 29U)
/** @brief Transmit mailbox 0 lowest-priority state (`CANx_TSR.LOW0`) bit mask @def CAN_TSR_LOW0_Msk */
#define CAN_TSR_LOW0_Msk			REG_BIT_MASK(CAN_TSR_LOW0_Pos)
/** @brief Transmit mailbox 0 lowest-priority state (`CANx_TSR.LOW0`) bit mask alias @def CAN_TSR_LOW0 */
#define CAN_TSR_LOW0				CAN_TSR_LOW0_Msk

/** @brief Transmit mailbox 1 lowest-priority state (`CANx_TSR.LOW1`) bit position @def CAN_TSR_LOW1_Pos */
#define CAN_TSR_LOW1_Pos			((reg_bit_pos_t) 30U)
/** @brief Transmit mailbox 1 lowest-priority state (`CANx_TSR.LOW1`) bit mask @def CAN_TSR_LOW1_Msk */
#define CAN_TSR_LOW1_Msk			REG_BIT_MASK(CAN_TSR_LOW1_Pos)
/** @brief Transmit mailbox 1 lowest-priority state (`CANx_TSR.LOW1`) bit mask alias @def CAN_TSR_LOW1 */
#define CAN_TSR_LOW1				CAN_TSR_LOW1_Msk

/** @brief Transmit mailbox 2 lowest-priority state (`CANx_TSR.LOW2`) bit position @def CAN_TSR_LOW2_Pos */
#define CAN_TSR_LOW2_Pos			((reg_bit_pos_t) 31U)
/** @brief Transmit mailbox 2 lowest-priority state (`CANx_TSR.LOW2`) bit mask @def CAN_TSR_LOW2_Msk */
#define CAN_TSR_LOW2_Msk			REG_BIT_MASK(CAN_TSR_LOW2_Pos)
/** @brief Transmit mailbox 2 lowest-priority state (`CANx_TSR.LOW2`) bit mask alias @def CAN_TSR_LOW2 */
#define CAN_TSR_LOW2				CAN_TSR_LOW2_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RF0R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Receive FIFO 0 pending-message count (`CANx_RF0R.FMP0`) field position @def CAN_RF0R_FMP0_Pos */
#define CAN_RF0R_FMP0_Pos			((reg_bit_pos_t) 0U)
/** @brief Receive FIFO 0 pending-message count (`CANx_RF0R.FMP0`) field width @def CAN_RF0R_FMP0_Width */
#define CAN_RF0R_FMP0_Width			((reg_field_width_t) 2U)
/** @brief Receive FIFO 0 pending-message count (`CANx_RF0R.FMP0`) field mask @def CAN_RF0R_FMP0_Msk */
#define CAN_RF0R_FMP0_Msk			REG_FIELD_MASK(CAN_RF0R_FMP0_Pos, CAN_RF0R_FMP0_Width)
/** @brief Receive FIFO 0 pending-message count (`CANx_RF0R.FMP0`) field mask alias @def CAN_RF0R_FMP0 */
#define CAN_RF0R_FMP0				CAN_RF0R_FMP0_Msk

/** @brief Receive FIFO 0 full event (`CANx_RF0R.FULL0`) bit position @def CAN_RF0R_FULL0_Pos */
#define CAN_RF0R_FULL0_Pos			((reg_bit_pos_t) 3U)
/** @brief Receive FIFO 0 full event (`CANx_RF0R.FULL0`) bit mask @def CAN_RF0R_FULL0_Msk */
#define CAN_RF0R_FULL0_Msk			REG_BIT_MASK(CAN_RF0R_FULL0_Pos)
/** @brief Receive FIFO 0 full event (`CANx_RF0R.FULL0`) bit mask alias @def CAN_RF0R_FULL0 */
#define CAN_RF0R_FULL0				CAN_RF0R_FULL0_Msk

/** @brief Receive FIFO 0 overrun event (`CANx_RF0R.FOVR0`) bit position @def CAN_RF0R_FOVR0_Pos */
#define CAN_RF0R_FOVR0_Pos			((reg_bit_pos_t) 4U)
/** @brief Receive FIFO 0 overrun event (`CANx_RF0R.FOVR0`) bit mask @def CAN_RF0R_FOVR0_Msk */
#define CAN_RF0R_FOVR0_Msk			REG_BIT_MASK(CAN_RF0R_FOVR0_Pos)
/** @brief Receive FIFO 0 overrun event (`CANx_RF0R.FOVR0`) bit mask alias @def CAN_RF0R_FOVR0 */
#define CAN_RF0R_FOVR0				CAN_RF0R_FOVR0_Msk

/** @brief Receive FIFO 0 output-mailbox release action (`CANx_RF0R.RFOM0`) bit position @def CAN_RF0R_RFOM0_Pos */
#define CAN_RF0R_RFOM0_Pos			((reg_bit_pos_t) 5U)
/** @brief Receive FIFO 0 output-mailbox release action (`CANx_RF0R.RFOM0`) bit mask @def CAN_RF0R_RFOM0_Msk */
#define CAN_RF0R_RFOM0_Msk			REG_BIT_MASK(CAN_RF0R_RFOM0_Pos)
/** @brief Receive FIFO 0 output-mailbox release action (`CANx_RF0R.RFOM0`) bit mask alias @def CAN_RF0R_RFOM0 */
#define CAN_RF0R_RFOM0				CAN_RF0R_RFOM0_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RF1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Receive FIFO 1 pending-message count (`CANx_RF1R.FMP1`) field position @def CAN_RF1R_FMP1_Pos */
#define CAN_RF1R_FMP1_Pos			((reg_bit_pos_t) 0U)
/** @brief Receive FIFO 1 pending-message count (`CANx_RF1R.FMP1`) field width @def CAN_RF1R_FMP1_Width */
#define CAN_RF1R_FMP1_Width			((reg_field_width_t) 2U)
/** @brief Receive FIFO 1 pending-message count (`CANx_RF1R.FMP1`) field mask @def CAN_RF1R_FMP1_Msk */
#define CAN_RF1R_FMP1_Msk			REG_FIELD_MASK(CAN_RF1R_FMP1_Pos, CAN_RF1R_FMP1_Width)
/** @brief Receive FIFO 1 pending-message count (`CANx_RF1R.FMP1`) field mask alias @def CAN_RF1R_FMP1 */
#define CAN_RF1R_FMP1				CAN_RF1R_FMP1_Msk

/** @brief Receive FIFO 1 full event (`CANx_RF1R.FULL1`) bit position @def CAN_RF1R_FULL1_Pos */
#define CAN_RF1R_FULL1_Pos			((reg_bit_pos_t) 3U)
/** @brief Receive FIFO 1 full event (`CANx_RF1R.FULL1`) bit mask @def CAN_RF1R_FULL1_Msk */
#define CAN_RF1R_FULL1_Msk			REG_BIT_MASK(CAN_RF1R_FULL1_Pos)
/** @brief Receive FIFO 1 full event (`CANx_RF1R.FULL1`) bit mask alias @def CAN_RF1R_FULL1 */
#define CAN_RF1R_FULL1				CAN_RF1R_FULL1_Msk

/** @brief Receive FIFO 1 overrun event (`CANx_RF1R.FOVR1`) bit position @def CAN_RF1R_FOVR1_Pos */
#define CAN_RF1R_FOVR1_Pos			((reg_bit_pos_t) 4U)
/** @brief Receive FIFO 1 overrun event (`CANx_RF1R.FOVR1`) bit mask @def CAN_RF1R_FOVR1_Msk */
#define CAN_RF1R_FOVR1_Msk			REG_BIT_MASK(CAN_RF1R_FOVR1_Pos)
/** @brief Receive FIFO 1 overrun event (`CANx_RF1R.FOVR1`) bit mask alias @def CAN_RF1R_FOVR1 */
#define CAN_RF1R_FOVR1				CAN_RF1R_FOVR1_Msk

/** @brief Receive FIFO 1 output-mailbox release action (`CANx_RF1R.RFOM1`) bit position @def CAN_RF1R_RFOM1_Pos */
#define CAN_RF1R_RFOM1_Pos			((reg_bit_pos_t) 5U)
/** @brief Receive FIFO 1 output-mailbox release action (`CANx_RF1R.RFOM1`) bit mask @def CAN_RF1R_RFOM1_Msk */
#define CAN_RF1R_RFOM1_Msk			REG_BIT_MASK(CAN_RF1R_RFOM1_Pos)
/** @brief Receive FIFO 1 output-mailbox release action (`CANx_RF1R.RFOM1`) bit mask alias @def CAN_RF1R_RFOM1 */
#define CAN_RF1R_RFOM1				CAN_RF1R_RFOM1_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_IER
// ---------------------------------------------------------------------------------------------------- //
/** @brief Transmit-mailbox-empty interrupt-request enable (`CANx_IER.TMEIE`) bit position @def CAN_IER_TMEIE_Pos */
#define CAN_IER_TMEIE_Pos			((reg_bit_pos_t) 0U)
/** @brief Transmit-mailbox-empty interrupt-request enable (`CANx_IER.TMEIE`) bit mask @def CAN_IER_TMEIE_Msk */
#define CAN_IER_TMEIE_Msk			REG_BIT_MASK(CAN_IER_TMEIE_Pos)
/** @brief Transmit-mailbox-empty interrupt-request enable (`CANx_IER.TMEIE`) bit mask alias @def CAN_IER_TMEIE */
#define CAN_IER_TMEIE				CAN_IER_TMEIE_Msk

/** @brief Receive FIFO 0 message-pending interrupt-request enable (`CANx_IER.FMPIE0`) bit position @def CAN_IER_FMPIE0_Pos */
#define CAN_IER_FMPIE0_Pos			((reg_bit_pos_t) 1U)
/** @brief Receive FIFO 0 message-pending interrupt-request enable (`CANx_IER.FMPIE0`) bit mask @def CAN_IER_FMPIE0_Msk */
#define CAN_IER_FMPIE0_Msk			REG_BIT_MASK(CAN_IER_FMPIE0_Pos)
/** @brief Receive FIFO 0 message-pending interrupt-request enable (`CANx_IER.FMPIE0`) bit mask alias @def CAN_IER_FMPIE0 */
#define CAN_IER_FMPIE0				CAN_IER_FMPIE0_Msk

/** @brief Receive FIFO 0 full interrupt-request enable (`CANx_IER.FFIE0`) bit position @def CAN_IER_FFIE0_Pos */
#define CAN_IER_FFIE0_Pos			((reg_bit_pos_t) 2U)
/** @brief Receive FIFO 0 full interrupt-request enable (`CANx_IER.FFIE0`) bit mask @def CAN_IER_FFIE0_Msk */
#define CAN_IER_FFIE0_Msk			REG_BIT_MASK(CAN_IER_FFIE0_Pos)
/** @brief Receive FIFO 0 full interrupt-request enable (`CANx_IER.FFIE0`) bit mask alias @def CAN_IER_FFIE0 */
#define CAN_IER_FFIE0				CAN_IER_FFIE0_Msk

/** @brief Receive FIFO 0 overrun interrupt-request enable (`CANx_IER.FOVIE0`) bit position @def CAN_IER_FOVIE0_Pos */
#define CAN_IER_FOVIE0_Pos			((reg_bit_pos_t) 3U)
/** @brief Receive FIFO 0 overrun interrupt-request enable (`CANx_IER.FOVIE0`) bit mask @def CAN_IER_FOVIE0_Msk */
#define CAN_IER_FOVIE0_Msk			REG_BIT_MASK(CAN_IER_FOVIE0_Pos)
/** @brief Receive FIFO 0 overrun interrupt-request enable (`CANx_IER.FOVIE0`) bit mask alias @def CAN_IER_FOVIE0 */
#define CAN_IER_FOVIE0				CAN_IER_FOVIE0_Msk

/** @brief Receive FIFO 1 message-pending interrupt-request enable (`CANx_IER.FMPIE1`) bit position @def CAN_IER_FMPIE1_Pos */
#define CAN_IER_FMPIE1_Pos			((reg_bit_pos_t) 4U)
/** @brief Receive FIFO 1 message-pending interrupt-request enable (`CANx_IER.FMPIE1`) bit mask @def CAN_IER_FMPIE1_Msk */
#define CAN_IER_FMPIE1_Msk			REG_BIT_MASK(CAN_IER_FMPIE1_Pos)
/** @brief Receive FIFO 1 message-pending interrupt-request enable (`CANx_IER.FMPIE1`) bit mask alias @def CAN_IER_FMPIE1 */
#define CAN_IER_FMPIE1				CAN_IER_FMPIE1_Msk

/** @brief Receive FIFO 1 full interrupt-request enable (`CANx_IER.FFIE1`) bit position @def CAN_IER_FFIE1_Pos */
#define CAN_IER_FFIE1_Pos			((reg_bit_pos_t) 5U)
/** @brief Receive FIFO 1 full interrupt-request enable (`CANx_IER.FFIE1`) bit mask @def CAN_IER_FFIE1_Msk */
#define CAN_IER_FFIE1_Msk			REG_BIT_MASK(CAN_IER_FFIE1_Pos)
/** @brief Receive FIFO 1 full interrupt-request enable (`CANx_IER.FFIE1`) bit mask alias @def CAN_IER_FFIE1 */
#define CAN_IER_FFIE1				CAN_IER_FFIE1_Msk

/** @brief Receive FIFO 1 overrun interrupt-request enable (`CANx_IER.FOVIE1`) bit position @def CAN_IER_FOVIE1_Pos */
#define CAN_IER_FOVIE1_Pos			((reg_bit_pos_t) 6U)
/** @brief Receive FIFO 1 overrun interrupt-request enable (`CANx_IER.FOVIE1`) bit mask @def CAN_IER_FOVIE1_Msk */
#define CAN_IER_FOVIE1_Msk			REG_BIT_MASK(CAN_IER_FOVIE1_Pos)
/** @brief Receive FIFO 1 overrun interrupt-request enable (`CANx_IER.FOVIE1`) bit mask alias @def CAN_IER_FOVIE1 */
#define CAN_IER_FOVIE1				CAN_IER_FOVIE1_Msk

/** @brief Error-warning interrupt-request enable (`CANx_IER.EWGIE`) bit position @def CAN_IER_EWGIE_Pos */
#define CAN_IER_EWGIE_Pos			((reg_bit_pos_t) 8U)
/** @brief Error-warning interrupt-request enable (`CANx_IER.EWGIE`) bit mask @def CAN_IER_EWGIE_Msk */
#define CAN_IER_EWGIE_Msk			REG_BIT_MASK(CAN_IER_EWGIE_Pos)
/** @brief Error-warning interrupt-request enable (`CANx_IER.EWGIE`) bit mask alias @def CAN_IER_EWGIE */
#define CAN_IER_EWGIE				CAN_IER_EWGIE_Msk

/** @brief Error-passive interrupt-request enable (`CANx_IER.EPVIE`) bit position @def CAN_IER_EPVIE_Pos */
#define CAN_IER_EPVIE_Pos			((reg_bit_pos_t) 9U)
/** @brief Error-passive interrupt-request enable (`CANx_IER.EPVIE`) bit mask @def CAN_IER_EPVIE_Msk */
#define CAN_IER_EPVIE_Msk			REG_BIT_MASK(CAN_IER_EPVIE_Pos)
/** @brief Error-passive interrupt-request enable (`CANx_IER.EPVIE`) bit mask alias @def CAN_IER_EPVIE */
#define CAN_IER_EPVIE				CAN_IER_EPVIE_Msk

/** @brief Bus-off interrupt-request enable (`CANx_IER.BOFIE`) bit position @def CAN_IER_BOFIE_Pos */
#define CAN_IER_BOFIE_Pos			((reg_bit_pos_t) 10U)
/** @brief Bus-off interrupt-request enable (`CANx_IER.BOFIE`) bit mask @def CAN_IER_BOFIE_Msk */
#define CAN_IER_BOFIE_Msk			REG_BIT_MASK(CAN_IER_BOFIE_Pos)
/** @brief Bus-off interrupt-request enable (`CANx_IER.BOFIE`) bit mask alias @def CAN_IER_BOFIE */
#define CAN_IER_BOFIE				CAN_IER_BOFIE_Msk

/** @brief Last-error-code interrupt-request enable (`CANx_IER.LECIE`) bit position @def CAN_IER_LECIE_Pos */
#define CAN_IER_LECIE_Pos			((reg_bit_pos_t) 11U)
/** @brief Last-error-code interrupt-request enable (`CANx_IER.LECIE`) bit mask @def CAN_IER_LECIE_Msk */
#define CAN_IER_LECIE_Msk			REG_BIT_MASK(CAN_IER_LECIE_Pos)
/** @brief Last-error-code interrupt-request enable (`CANx_IER.LECIE`) bit mask alias @def CAN_IER_LECIE */
#define CAN_IER_LECIE				CAN_IER_LECIE_Msk

/** @brief Error interrupt-request master enable (`CANx_IER.ERRIE`) bit position @def CAN_IER_ERRIE_Pos */
#define CAN_IER_ERRIE_Pos			((reg_bit_pos_t) 15U)
/** @brief Error interrupt-request master enable (`CANx_IER.ERRIE`) bit mask @def CAN_IER_ERRIE_Msk */
#define CAN_IER_ERRIE_Msk			REG_BIT_MASK(CAN_IER_ERRIE_Pos)
/** @brief Error interrupt-request master enable (`CANx_IER.ERRIE`) bit mask alias @def CAN_IER_ERRIE */
#define CAN_IER_ERRIE				CAN_IER_ERRIE_Msk

/** @brief Wake-up interrupt-request enable (`CANx_IER.WKUIE`) bit position @def CAN_IER_WKUIE_Pos */
#define CAN_IER_WKUIE_Pos			((reg_bit_pos_t) 16U)
/** @brief Wake-up interrupt-request enable (`CANx_IER.WKUIE`) bit mask @def CAN_IER_WKUIE_Msk */
#define CAN_IER_WKUIE_Msk			REG_BIT_MASK(CAN_IER_WKUIE_Pos)
/** @brief Wake-up interrupt-request enable (`CANx_IER.WKUIE`) bit mask alias @def CAN_IER_WKUIE */
#define CAN_IER_WKUIE				CAN_IER_WKUIE_Msk

/** @brief Sleep interrupt-request enable (`CANx_IER.SLKIE`) bit position @def CAN_IER_SLKIE_Pos */
#define CAN_IER_SLKIE_Pos			((reg_bit_pos_t) 17U)
/** @brief Sleep interrupt-request enable (`CANx_IER.SLKIE`) bit mask @def CAN_IER_SLKIE_Msk */
#define CAN_IER_SLKIE_Msk			REG_BIT_MASK(CAN_IER_SLKIE_Pos)
/** @brief Sleep interrupt-request enable (`CANx_IER.SLKIE`) bit mask alias @def CAN_IER_SLKIE */
#define CAN_IER_SLKIE				CAN_IER_SLKIE_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_ESR
// ---------------------------------------------------------------------------------------------------- //
/** @brief Error-warning state (`CANx_ESR.EWGF`) bit position @def CAN_ESR_EWGF_Pos */
#define CAN_ESR_EWGF_Pos			((reg_bit_pos_t) 0U)
/** @brief Error-warning state (`CANx_ESR.EWGF`) bit mask @def CAN_ESR_EWGF_Msk */
#define CAN_ESR_EWGF_Msk			REG_BIT_MASK(CAN_ESR_EWGF_Pos)
/** @brief Error-warning state (`CANx_ESR.EWGF`) bit mask alias @def CAN_ESR_EWGF */
#define CAN_ESR_EWGF				CAN_ESR_EWGF_Msk

/** @brief Error-passive state (`CANx_ESR.EPVF`) bit position @def CAN_ESR_EPVF_Pos */
#define CAN_ESR_EPVF_Pos			((reg_bit_pos_t) 1U)
/** @brief Error-passive state (`CANx_ESR.EPVF`) bit mask @def CAN_ESR_EPVF_Msk */
#define CAN_ESR_EPVF_Msk			REG_BIT_MASK(CAN_ESR_EPVF_Pos)
/** @brief Error-passive state (`CANx_ESR.EPVF`) bit mask alias @def CAN_ESR_EPVF */
#define CAN_ESR_EPVF				CAN_ESR_EPVF_Msk

/** @brief Bus-off state (`CANx_ESR.BOFF`) bit position @def CAN_ESR_BOFF_Pos */
#define CAN_ESR_BOFF_Pos			((reg_bit_pos_t) 2U)
/** @brief Bus-off state (`CANx_ESR.BOFF`) bit mask @def CAN_ESR_BOFF_Msk */
#define CAN_ESR_BOFF_Msk			REG_BIT_MASK(CAN_ESR_BOFF_Pos)
/** @brief Bus-off state (`CANx_ESR.BOFF`) bit mask alias @def CAN_ESR_BOFF */
#define CAN_ESR_BOFF				CAN_ESR_BOFF_Msk

/** @brief Last protocol error code (`CANx_ESR.LEC`) field position @def CAN_ESR_LEC_Pos */
#define CAN_ESR_LEC_Pos				((reg_bit_pos_t) 4U)
/** @brief Last protocol error code (`CANx_ESR.LEC`) field width @def CAN_ESR_LEC_Width */
#define CAN_ESR_LEC_Width			((reg_field_width_t) 3U)
/** @brief Last protocol error code (`CANx_ESR.LEC`) field mask @def CAN_ESR_LEC_Msk */
#define CAN_ESR_LEC_Msk				REG_FIELD_MASK(CAN_ESR_LEC_Pos, CAN_ESR_LEC_Width)
/** @brief Last protocol error code (`CANx_ESR.LEC`) field mask alias @def CAN_ESR_LEC */
#define CAN_ESR_LEC					CAN_ESR_LEC_Msk

/** @brief Last protocol error code (`CANx_ESR.LEC[0]`) raw field bit 0 mask @def CAN_ESR_LEC_0 */
#define CAN_ESR_LEC_0				REG_FIELD_VALUE(CAN_ESR_LEC_Pos, 0x1UL)

/** @brief Last protocol error code (`CANx_ESR.LEC[1]`) raw field bit 1 mask @def CAN_ESR_LEC_1 */
#define CAN_ESR_LEC_1				REG_FIELD_VALUE(CAN_ESR_LEC_Pos, 0x2UL)

/** @brief Last protocol error code (`CANx_ESR.LEC[2]`) raw field bit 2 mask @def CAN_ESR_LEC_2 */
#define CAN_ESR_LEC_2				REG_FIELD_VALUE(CAN_ESR_LEC_Pos, 0x4UL)

/** @brief Transmit error counter (`CANx_ESR.TEC`) field position @def CAN_ESR_TEC_Pos */
#define CAN_ESR_TEC_Pos				((reg_bit_pos_t) 16U)
/** @brief Transmit error counter (`CANx_ESR.TEC`) field width @def CAN_ESR_TEC_Width */
#define CAN_ESR_TEC_Width			((reg_field_width_t) 8U)
/** @brief Transmit error counter (`CANx_ESR.TEC`) field mask @def CAN_ESR_TEC_Msk */
#define CAN_ESR_TEC_Msk				REG_FIELD_MASK(CAN_ESR_TEC_Pos, CAN_ESR_TEC_Width)
/** @brief Transmit error counter (`CANx_ESR.TEC`) field mask alias @def CAN_ESR_TEC */
#define CAN_ESR_TEC					CAN_ESR_TEC_Msk

/** @brief Receive error counter (`CANx_ESR.REC`) field position @def CAN_ESR_REC_Pos */
#define CAN_ESR_REC_Pos				((reg_bit_pos_t) 24U)
/** @brief Receive error counter (`CANx_ESR.REC`) field width @def CAN_ESR_REC_Width */
#define CAN_ESR_REC_Width			((reg_field_width_t) 8U)
/** @brief Receive error counter (`CANx_ESR.REC`) field mask @def CAN_ESR_REC_Msk */
#define CAN_ESR_REC_Msk				REG_FIELD_MASK(CAN_ESR_REC_Pos, CAN_ESR_REC_Width)
/** @brief Receive error counter (`CANx_ESR.REC`) field mask alias @def CAN_ESR_REC */
#define CAN_ESR_REC					CAN_ESR_REC_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_BTR
// ---------------------------------------------------------------------------------------------------- //
/** @brief Baud-rate prescaler (`CANx_BTR.BRP`) field position @def CAN_BTR_BRP_Pos */
#define CAN_BTR_BRP_Pos				((reg_bit_pos_t) 0U)
/** @brief Baud-rate prescaler (`CANx_BTR.BRP`) field width @def CAN_BTR_BRP_Width */
#define CAN_BTR_BRP_Width			((reg_field_width_t) 10U)
/** @brief Baud-rate prescaler (`CANx_BTR.BRP`) field mask @def CAN_BTR_BRP_Msk */
#define CAN_BTR_BRP_Msk				REG_FIELD_MASK(CAN_BTR_BRP_Pos, CAN_BTR_BRP_Width)
/** @brief Baud-rate prescaler (`CANx_BTR.BRP`) field mask alias @def CAN_BTR_BRP */
#define CAN_BTR_BRP					CAN_BTR_BRP_Msk

/** @brief Time segment 1 length (`CANx_BTR.TS1`) field position @def CAN_BTR_TS1_Pos */
#define CAN_BTR_TS1_Pos				((reg_bit_pos_t) 16U)
/** @brief Time segment 1 length (`CANx_BTR.TS1`) field width @def CAN_BTR_TS1_Width */
#define CAN_BTR_TS1_Width			((reg_field_width_t) 4U)
/** @brief Time segment 1 length (`CANx_BTR.TS1`) field mask @def CAN_BTR_TS1_Msk */
#define CAN_BTR_TS1_Msk				REG_FIELD_MASK(CAN_BTR_TS1_Pos, CAN_BTR_TS1_Width)
/** @brief Time segment 1 length (`CANx_BTR.TS1`) field mask alias @def CAN_BTR_TS1 */
#define CAN_BTR_TS1					CAN_BTR_TS1_Msk

/** @brief Time segment 1 length (`CANx_BTR.TS1[0]`) raw field bit 0 mask @def CAN_BTR_TS1_0 */
#define CAN_BTR_TS1_0				REG_FIELD_VALUE(CAN_BTR_TS1_Pos, 0x1UL)

/** @brief Time segment 1 length (`CANx_BTR.TS1[1]`) raw field bit 1 mask @def CAN_BTR_TS1_1 */
#define CAN_BTR_TS1_1				REG_FIELD_VALUE(CAN_BTR_TS1_Pos, 0x2UL)

/** @brief Time segment 1 length (`CANx_BTR.TS1[2]`) raw field bit 2 mask @def CAN_BTR_TS1_2 */
#define CAN_BTR_TS1_2				REG_FIELD_VALUE(CAN_BTR_TS1_Pos, 0x4UL)

/** @brief Time segment 1 length (`CANx_BTR.TS1[3]`) raw field bit 3 mask @def CAN_BTR_TS1_3 */
#define CAN_BTR_TS1_3				REG_FIELD_VALUE(CAN_BTR_TS1_Pos, 0x8UL)

/** @brief Time segment 2 length (`CANx_BTR.TS2`) field position @def CAN_BTR_TS2_Pos */
#define CAN_BTR_TS2_Pos				((reg_bit_pos_t) 20U)
/** @brief Time segment 2 length (`CANx_BTR.TS2`) field width @def CAN_BTR_TS2_Width */
#define CAN_BTR_TS2_Width			((reg_field_width_t) 3U)
/** @brief Time segment 2 length (`CANx_BTR.TS2`) field mask @def CAN_BTR_TS2_Msk */
#define CAN_BTR_TS2_Msk				REG_FIELD_MASK(CAN_BTR_TS2_Pos, CAN_BTR_TS2_Width)
/** @brief Time segment 2 length (`CANx_BTR.TS2`) field mask alias @def CAN_BTR_TS2 */
#define CAN_BTR_TS2					CAN_BTR_TS2_Msk

/** @brief Time segment 2 length (`CANx_BTR.TS2[0]`) raw field bit 0 mask @def CAN_BTR_TS2_0 */
#define CAN_BTR_TS2_0				REG_FIELD_VALUE(CAN_BTR_TS2_Pos, 0x1UL)

/** @brief Time segment 2 length (`CANx_BTR.TS2[1]`) raw field bit 1 mask @def CAN_BTR_TS2_1 */
#define CAN_BTR_TS2_1				REG_FIELD_VALUE(CAN_BTR_TS2_Pos, 0x2UL)

/** @brief Time segment 2 length (`CANx_BTR.TS2[2]`) raw field bit 2 mask @def CAN_BTR_TS2_2 */
#define CAN_BTR_TS2_2				REG_FIELD_VALUE(CAN_BTR_TS2_Pos, 0x4UL)

/** @brief Resynchronization jump width (`CANx_BTR.SJW`) field position @def CAN_BTR_SJW_Pos */
#define CAN_BTR_SJW_Pos				((reg_bit_pos_t) 24U)
/** @brief Resynchronization jump width (`CANx_BTR.SJW`) field width @def CAN_BTR_SJW_Width */
#define CAN_BTR_SJW_Width			((reg_field_width_t) 2U)
/** @brief Resynchronization jump width (`CANx_BTR.SJW`) field mask @def CAN_BTR_SJW_Msk */
#define CAN_BTR_SJW_Msk				REG_FIELD_MASK(CAN_BTR_SJW_Pos, CAN_BTR_SJW_Width)
/** @brief Resynchronization jump width (`CANx_BTR.SJW`) field mask alias @def CAN_BTR_SJW */
#define CAN_BTR_SJW					CAN_BTR_SJW_Msk

/** @brief Resynchronization jump width (`CANx_BTR.SJW[0]`) raw field bit 0 mask @def CAN_BTR_SJW_0 */
#define CAN_BTR_SJW_0				REG_FIELD_VALUE(CAN_BTR_SJW_Pos, 0x1UL)

/** @brief Resynchronization jump width (`CANx_BTR.SJW[1]`) raw field bit 1 mask @def CAN_BTR_SJW_1 */
#define CAN_BTR_SJW_1				REG_FIELD_VALUE(CAN_BTR_SJW_Pos, 0x2UL)

/** @brief Internal loopback-mode enable (`CANx_BTR.LBKM`) bit position @def CAN_BTR_LBKM_Pos */
#define CAN_BTR_LBKM_Pos			((reg_bit_pos_t) 30U)
/** @brief Internal loopback-mode enable (`CANx_BTR.LBKM`) bit mask @def CAN_BTR_LBKM_Msk */
#define CAN_BTR_LBKM_Msk			REG_BIT_MASK(CAN_BTR_LBKM_Pos)
/** @brief Internal loopback-mode enable (`CANx_BTR.LBKM`) bit mask alias @def CAN_BTR_LBKM */
#define CAN_BTR_LBKM				CAN_BTR_LBKM_Msk

/** @brief Silent bus-monitoring-mode enable (`CANx_BTR.SILM`) bit position @def CAN_BTR_SILM_Pos */
#define CAN_BTR_SILM_Pos			((reg_bit_pos_t) 31U)
/** @brief Silent bus-monitoring-mode enable (`CANx_BTR.SILM`) bit mask @def CAN_BTR_SILM_Msk */
#define CAN_BTR_SILM_Msk			REG_BIT_MASK(CAN_BTR_SILM_Pos)
/** @brief Silent bus-monitoring-mode enable (`CANx_BTR.SILM`) bit mask alias @def CAN_BTR_SILM */
#define CAN_BTR_SILM				CAN_BTR_SILM_Msk

// ---------------------------------------------------------------------------------------------------- //
// Indexed Transmit and Receive Mailbox Register Vocabulary
// ---------------------------------------------------------------------------------------------------- //
// The repeated mailbox windows share one field layout. These canonical names let LL and Driver code
// select an array element once, then reuse one register transformation path for every mailbox or FIFO.

// ---------------------------------------------------------------------------------------------------- //
// CAN_TIR
// ---------------------------------------------------------------------------------------------------- //
/** @brief Transmit-mailbox request action (`CANx_TX_MAILBOX[n].TIR.TXRQ`) bit position @def CAN_TIR_TXRQ_Pos */
#define CAN_TIR_TXRQ_Pos			((reg_bit_pos_t) 0U)
/** @brief Transmit-mailbox request action (`CANx_TX_MAILBOX[n].TIR.TXRQ`) bit mask @def CAN_TIR_TXRQ_Msk */
#define CAN_TIR_TXRQ_Msk			REG_BIT_MASK(CAN_TIR_TXRQ_Pos)
/** @brief Transmit-mailbox request action (`CANx_TX_MAILBOX[n].TIR.TXRQ`) bit mask alias @def CAN_TIR_TXRQ */
#define CAN_TIR_TXRQ				CAN_TIR_TXRQ_Msk

/** @brief Remote-transmission-request frame selector (`CANx_TX_MAILBOX[n].TIR.RTR`) bit position @def CAN_TIR_RTR_Pos */
#define CAN_TIR_RTR_Pos				((reg_bit_pos_t) 1U)
/** @brief Remote-transmission-request frame selector (`CANx_TX_MAILBOX[n].TIR.RTR`) bit mask @def CAN_TIR_RTR_Msk */
#define CAN_TIR_RTR_Msk				REG_BIT_MASK(CAN_TIR_RTR_Pos)
/** @brief Remote-transmission-request frame selector (`CANx_TX_MAILBOX[n].TIR.RTR`) bit mask alias @def CAN_TIR_RTR */
#define CAN_TIR_RTR					CAN_TIR_RTR_Msk

/** @brief Identifier-extension selector (`CANx_TX_MAILBOX[n].TIR.IDE`) bit position @def CAN_TIR_IDE_Pos */
#define CAN_TIR_IDE_Pos				((reg_bit_pos_t) 2U)
/** @brief Identifier-extension selector (`CANx_TX_MAILBOX[n].TIR.IDE`) bit mask @def CAN_TIR_IDE_Msk */
#define CAN_TIR_IDE_Msk				REG_BIT_MASK(CAN_TIR_IDE_Pos)
/** @brief Identifier-extension selector (`CANx_TX_MAILBOX[n].TIR.IDE`) bit mask alias @def CAN_TIR_IDE */
#define CAN_TIR_IDE					CAN_TIR_IDE_Msk

/** @brief Extended-identifier portion (`CANx_TX_MAILBOX[n].TIR.EXID`) field position @def CAN_TIR_EXID_Pos */
#define CAN_TIR_EXID_Pos			((reg_bit_pos_t) 3U)
/** @brief Extended-identifier portion (`CANx_TX_MAILBOX[n].TIR.EXID`) field width @def CAN_TIR_EXID_Width */
#define CAN_TIR_EXID_Width			((reg_field_width_t) 18U)
/** @brief Extended-identifier portion (`CANx_TX_MAILBOX[n].TIR.EXID`) field mask @def CAN_TIR_EXID_Msk */
#define CAN_TIR_EXID_Msk			REG_FIELD_MASK(CAN_TIR_EXID_Pos, CAN_TIR_EXID_Width)
/** @brief Extended-identifier portion (`CANx_TX_MAILBOX[n].TIR.EXID`) field mask alias @def CAN_TIR_EXID */
#define CAN_TIR_EXID				CAN_TIR_EXID_Msk

/** @brief Standard identifier or extended-identifier prefix (`CANx_TX_MAILBOX[n].TIR.STID`) field position @def CAN_TIR_STID_Pos */
#define CAN_TIR_STID_Pos			((reg_bit_pos_t) 21U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_TX_MAILBOX[n].TIR.STID`) field width @def CAN_TIR_STID_Width */
#define CAN_TIR_STID_Width			((reg_field_width_t) 11U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_TX_MAILBOX[n].TIR.STID`) field mask @def CAN_TIR_STID_Msk */
#define CAN_TIR_STID_Msk			REG_FIELD_MASK(CAN_TIR_STID_Pos, CAN_TIR_STID_Width)
/** @brief Standard identifier or extended-identifier prefix (`CANx_TX_MAILBOX[n].TIR.STID`) field mask alias @def CAN_TIR_STID */
#define CAN_TIR_STID				CAN_TIR_STID_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TDTR
// ---------------------------------------------------------------------------------------------------- //
/** @brief Data length code (`CANx_TX_MAILBOX[n].TDTR.DLC`) field position @def CAN_TDTR_DLC_Pos */
#define CAN_TDTR_DLC_Pos			((reg_bit_pos_t) 0U)
/** @brief Data length code (`CANx_TX_MAILBOX[n].TDTR.DLC`) field width @def CAN_TDTR_DLC_Width */
#define CAN_TDTR_DLC_Width			((reg_field_width_t) 4U)
/** @brief Data length code (`CANx_TX_MAILBOX[n].TDTR.DLC`) field mask @def CAN_TDTR_DLC_Msk */
#define CAN_TDTR_DLC_Msk			REG_FIELD_MASK(CAN_TDTR_DLC_Pos, CAN_TDTR_DLC_Width)
/** @brief Data length code (`CANx_TX_MAILBOX[n].TDTR.DLC`) field mask alias @def CAN_TDTR_DLC */
#define CAN_TDTR_DLC				CAN_TDTR_DLC_Msk

/** @brief Global-time transmission request (`CANx_TX_MAILBOX[n].TDTR.TGT`) bit position @def CAN_TDTR_TGT_Pos */
#define CAN_TDTR_TGT_Pos			((reg_bit_pos_t) 8U)
/** @brief Global-time transmission request (`CANx_TX_MAILBOX[n].TDTR.TGT`) bit mask @def CAN_TDTR_TGT_Msk */
#define CAN_TDTR_TGT_Msk			REG_BIT_MASK(CAN_TDTR_TGT_Pos)
/** @brief Global-time transmission request (`CANx_TX_MAILBOX[n].TDTR.TGT`) bit mask alias @def CAN_TDTR_TGT */
#define CAN_TDTR_TGT				CAN_TDTR_TGT_Msk

/** @brief Message timestamp (`CANx_TX_MAILBOX[n].TDTR.TIME`) field position @def CAN_TDTR_TIME_Pos */
#define CAN_TDTR_TIME_Pos			((reg_bit_pos_t) 16U)
/** @brief Message timestamp (`CANx_TX_MAILBOX[n].TDTR.TIME`) field width @def CAN_TDTR_TIME_Width */
#define CAN_TDTR_TIME_Width			((reg_field_width_t) 16U)
/** @brief Message timestamp (`CANx_TX_MAILBOX[n].TDTR.TIME`) field mask @def CAN_TDTR_TIME_Msk */
#define CAN_TDTR_TIME_Msk			REG_FIELD_MASK(CAN_TDTR_TIME_Pos, CAN_TDTR_TIME_Width)
/** @brief Message timestamp (`CANx_TX_MAILBOX[n].TDTR.TIME`) field mask alias @def CAN_TDTR_TIME */
#define CAN_TDTR_TIME				CAN_TDTR_TIME_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TDLR
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 0 (`CANx_TX_MAILBOX[n].TDLR.DATA0`) field position @def CAN_TDLR_DATA0_Pos */
#define CAN_TDLR_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 0 (`CANx_TX_MAILBOX[n].TDLR.DATA0`) field width @def CAN_TDLR_DATA0_Width */
#define CAN_TDLR_DATA0_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 0 (`CANx_TX_MAILBOX[n].TDLR.DATA0`) field mask @def CAN_TDLR_DATA0_Msk */
#define CAN_TDLR_DATA0_Msk			REG_FIELD_MASK(CAN_TDLR_DATA0_Pos, CAN_TDLR_DATA0_Width)
/** @brief CAN payload byte 0 (`CANx_TX_MAILBOX[n].TDLR.DATA0`) field mask alias @def CAN_TDLR_DATA0 */
#define CAN_TDLR_DATA0				CAN_TDLR_DATA0_Msk

/** @brief CAN payload byte 1 (`CANx_TX_MAILBOX[n].TDLR.DATA1`) field position @def CAN_TDLR_DATA1_Pos */
#define CAN_TDLR_DATA1_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 1 (`CANx_TX_MAILBOX[n].TDLR.DATA1`) field width @def CAN_TDLR_DATA1_Width */
#define CAN_TDLR_DATA1_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 1 (`CANx_TX_MAILBOX[n].TDLR.DATA1`) field mask @def CAN_TDLR_DATA1_Msk */
#define CAN_TDLR_DATA1_Msk			REG_FIELD_MASK(CAN_TDLR_DATA1_Pos, CAN_TDLR_DATA1_Width)
/** @brief CAN payload byte 1 (`CANx_TX_MAILBOX[n].TDLR.DATA1`) field mask alias @def CAN_TDLR_DATA1 */
#define CAN_TDLR_DATA1				CAN_TDLR_DATA1_Msk

/** @brief CAN payload byte 2 (`CANx_TX_MAILBOX[n].TDLR.DATA2`) field position @def CAN_TDLR_DATA2_Pos */
#define CAN_TDLR_DATA2_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 2 (`CANx_TX_MAILBOX[n].TDLR.DATA2`) field width @def CAN_TDLR_DATA2_Width */
#define CAN_TDLR_DATA2_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 2 (`CANx_TX_MAILBOX[n].TDLR.DATA2`) field mask @def CAN_TDLR_DATA2_Msk */
#define CAN_TDLR_DATA2_Msk			REG_FIELD_MASK(CAN_TDLR_DATA2_Pos, CAN_TDLR_DATA2_Width)
/** @brief CAN payload byte 2 (`CANx_TX_MAILBOX[n].TDLR.DATA2`) field mask alias @def CAN_TDLR_DATA2 */
#define CAN_TDLR_DATA2				CAN_TDLR_DATA2_Msk

/** @brief CAN payload byte 3 (`CANx_TX_MAILBOX[n].TDLR.DATA3`) field position @def CAN_TDLR_DATA3_Pos */
#define CAN_TDLR_DATA3_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 3 (`CANx_TX_MAILBOX[n].TDLR.DATA3`) field width @def CAN_TDLR_DATA3_Width */
#define CAN_TDLR_DATA3_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 3 (`CANx_TX_MAILBOX[n].TDLR.DATA3`) field mask @def CAN_TDLR_DATA3_Msk */
#define CAN_TDLR_DATA3_Msk			REG_FIELD_MASK(CAN_TDLR_DATA3_Pos, CAN_TDLR_DATA3_Width)
/** @brief CAN payload byte 3 (`CANx_TX_MAILBOX[n].TDLR.DATA3`) field mask alias @def CAN_TDLR_DATA3 */
#define CAN_TDLR_DATA3				CAN_TDLR_DATA3_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TDHR
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 4 (`CANx_TX_MAILBOX[n].TDHR.DATA4`) field position @def CAN_TDHR_DATA4_Pos */
#define CAN_TDHR_DATA4_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 4 (`CANx_TX_MAILBOX[n].TDHR.DATA4`) field width @def CAN_TDHR_DATA4_Width */
#define CAN_TDHR_DATA4_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 4 (`CANx_TX_MAILBOX[n].TDHR.DATA4`) field mask @def CAN_TDHR_DATA4_Msk */
#define CAN_TDHR_DATA4_Msk			REG_FIELD_MASK(CAN_TDHR_DATA4_Pos, CAN_TDHR_DATA4_Width)
/** @brief CAN payload byte 4 (`CANx_TX_MAILBOX[n].TDHR.DATA4`) field mask alias @def CAN_TDHR_DATA4 */
#define CAN_TDHR_DATA4				CAN_TDHR_DATA4_Msk

/** @brief CAN payload byte 5 (`CANx_TX_MAILBOX[n].TDHR.DATA5`) field position @def CAN_TDHR_DATA5_Pos */
#define CAN_TDHR_DATA5_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 5 (`CANx_TX_MAILBOX[n].TDHR.DATA5`) field width @def CAN_TDHR_DATA5_Width */
#define CAN_TDHR_DATA5_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 5 (`CANx_TX_MAILBOX[n].TDHR.DATA5`) field mask @def CAN_TDHR_DATA5_Msk */
#define CAN_TDHR_DATA5_Msk			REG_FIELD_MASK(CAN_TDHR_DATA5_Pos, CAN_TDHR_DATA5_Width)
/** @brief CAN payload byte 5 (`CANx_TX_MAILBOX[n].TDHR.DATA5`) field mask alias @def CAN_TDHR_DATA5 */
#define CAN_TDHR_DATA5				CAN_TDHR_DATA5_Msk

/** @brief CAN payload byte 6 (`CANx_TX_MAILBOX[n].TDHR.DATA6`) field position @def CAN_TDHR_DATA6_Pos */
#define CAN_TDHR_DATA6_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 6 (`CANx_TX_MAILBOX[n].TDHR.DATA6`) field width @def CAN_TDHR_DATA6_Width */
#define CAN_TDHR_DATA6_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 6 (`CANx_TX_MAILBOX[n].TDHR.DATA6`) field mask @def CAN_TDHR_DATA6_Msk */
#define CAN_TDHR_DATA6_Msk			REG_FIELD_MASK(CAN_TDHR_DATA6_Pos, CAN_TDHR_DATA6_Width)
/** @brief CAN payload byte 6 (`CANx_TX_MAILBOX[n].TDHR.DATA6`) field mask alias @def CAN_TDHR_DATA6 */
#define CAN_TDHR_DATA6				CAN_TDHR_DATA6_Msk

/** @brief CAN payload byte 7 (`CANx_TX_MAILBOX[n].TDHR.DATA7`) field position @def CAN_TDHR_DATA7_Pos */
#define CAN_TDHR_DATA7_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 7 (`CANx_TX_MAILBOX[n].TDHR.DATA7`) field width @def CAN_TDHR_DATA7_Width */
#define CAN_TDHR_DATA7_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 7 (`CANx_TX_MAILBOX[n].TDHR.DATA7`) field mask @def CAN_TDHR_DATA7_Msk */
#define CAN_TDHR_DATA7_Msk			REG_FIELD_MASK(CAN_TDHR_DATA7_Pos, CAN_TDHR_DATA7_Width)
/** @brief CAN payload byte 7 (`CANx_TX_MAILBOX[n].TDHR.DATA7`) field mask alias @def CAN_TDHR_DATA7 */
#define CAN_TDHR_DATA7				CAN_TDHR_DATA7_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RIR
// ---------------------------------------------------------------------------------------------------- //
/** @brief Remote-transmission-request frame selector (`CANx_RX_FIFO[n].RIR.RTR`) bit position @def CAN_RIR_RTR_Pos */
#define CAN_RIR_RTR_Pos				((reg_bit_pos_t) 1U)
/** @brief Remote-transmission-request frame selector (`CANx_RX_FIFO[n].RIR.RTR`) bit mask @def CAN_RIR_RTR_Msk */
#define CAN_RIR_RTR_Msk				REG_BIT_MASK(CAN_RIR_RTR_Pos)
/** @brief Remote-transmission-request frame selector (`CANx_RX_FIFO[n].RIR.RTR`) bit mask alias @def CAN_RIR_RTR */
#define CAN_RIR_RTR					CAN_RIR_RTR_Msk

/** @brief Identifier-extension selector (`CANx_RX_FIFO[n].RIR.IDE`) bit position @def CAN_RIR_IDE_Pos */
#define CAN_RIR_IDE_Pos				((reg_bit_pos_t) 2U)
/** @brief Identifier-extension selector (`CANx_RX_FIFO[n].RIR.IDE`) bit mask @def CAN_RIR_IDE_Msk */
#define CAN_RIR_IDE_Msk				REG_BIT_MASK(CAN_RIR_IDE_Pos)
/** @brief Identifier-extension selector (`CANx_RX_FIFO[n].RIR.IDE`) bit mask alias @def CAN_RIR_IDE */
#define CAN_RIR_IDE					CAN_RIR_IDE_Msk

/** @brief Extended-identifier portion (`CANx_RX_FIFO[n].RIR.EXID`) field position @def CAN_RIR_EXID_Pos */
#define CAN_RIR_EXID_Pos			((reg_bit_pos_t) 3U)
/** @brief Extended-identifier portion (`CANx_RX_FIFO[n].RIR.EXID`) field width @def CAN_RIR_EXID_Width */
#define CAN_RIR_EXID_Width			((reg_field_width_t) 18U)
/** @brief Extended-identifier portion (`CANx_RX_FIFO[n].RIR.EXID`) field mask @def CAN_RIR_EXID_Msk */
#define CAN_RIR_EXID_Msk			REG_FIELD_MASK(CAN_RIR_EXID_Pos, CAN_RIR_EXID_Width)
/** @brief Extended-identifier portion (`CANx_RX_FIFO[n].RIR.EXID`) field mask alias @def CAN_RIR_EXID */
#define CAN_RIR_EXID				CAN_RIR_EXID_Msk

/** @brief Standard identifier or extended-identifier prefix (`CANx_RX_FIFO[n].RIR.STID`) field position @def CAN_RIR_STID_Pos */
#define CAN_RIR_STID_Pos			((reg_bit_pos_t) 21U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_RX_FIFO[n].RIR.STID`) field width @def CAN_RIR_STID_Width */
#define CAN_RIR_STID_Width			((reg_field_width_t) 11U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_RX_FIFO[n].RIR.STID`) field mask @def CAN_RIR_STID_Msk */
#define CAN_RIR_STID_Msk			REG_FIELD_MASK(CAN_RIR_STID_Pos, CAN_RIR_STID_Width)
/** @brief Standard identifier or extended-identifier prefix (`CANx_RX_FIFO[n].RIR.STID`) field mask alias @def CAN_RIR_STID */
#define CAN_RIR_STID				CAN_RIR_STID_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RDTR
// ---------------------------------------------------------------------------------------------------- //
/** @brief Data length code (`CANx_RX_FIFO[n].RDTR.DLC`) field position @def CAN_RDTR_DLC_Pos */
#define CAN_RDTR_DLC_Pos			((reg_bit_pos_t) 0U)
/** @brief Data length code (`CANx_RX_FIFO[n].RDTR.DLC`) field width @def CAN_RDTR_DLC_Width */
#define CAN_RDTR_DLC_Width			((reg_field_width_t) 4U)
/** @brief Data length code (`CANx_RX_FIFO[n].RDTR.DLC`) field mask @def CAN_RDTR_DLC_Msk */
#define CAN_RDTR_DLC_Msk			REG_FIELD_MASK(CAN_RDTR_DLC_Pos, CAN_RDTR_DLC_Width)
/** @brief Data length code (`CANx_RX_FIFO[n].RDTR.DLC`) field mask alias @def CAN_RDTR_DLC */
#define CAN_RDTR_DLC				CAN_RDTR_DLC_Msk

/** @brief Filter match index (`CANx_RX_FIFO[n].RDTR.FMI`) field position @def CAN_RDTR_FMI_Pos */
#define CAN_RDTR_FMI_Pos			((reg_bit_pos_t) 8U)
/** @brief Filter match index (`CANx_RX_FIFO[n].RDTR.FMI`) field width @def CAN_RDTR_FMI_Width */
#define CAN_RDTR_FMI_Width			((reg_field_width_t) 8U)
/** @brief Filter match index (`CANx_RX_FIFO[n].RDTR.FMI`) field mask @def CAN_RDTR_FMI_Msk */
#define CAN_RDTR_FMI_Msk			REG_FIELD_MASK(CAN_RDTR_FMI_Pos, CAN_RDTR_FMI_Width)
/** @brief Filter match index (`CANx_RX_FIFO[n].RDTR.FMI`) field mask alias @def CAN_RDTR_FMI */
#define CAN_RDTR_FMI				CAN_RDTR_FMI_Msk

/** @brief Message timestamp (`CANx_RX_FIFO[n].RDTR.TIME`) field position @def CAN_RDTR_TIME_Pos */
#define CAN_RDTR_TIME_Pos			((reg_bit_pos_t) 16U)
/** @brief Message timestamp (`CANx_RX_FIFO[n].RDTR.TIME`) field width @def CAN_RDTR_TIME_Width */
#define CAN_RDTR_TIME_Width			((reg_field_width_t) 16U)
/** @brief Message timestamp (`CANx_RX_FIFO[n].RDTR.TIME`) field mask @def CAN_RDTR_TIME_Msk */
#define CAN_RDTR_TIME_Msk			REG_FIELD_MASK(CAN_RDTR_TIME_Pos, CAN_RDTR_TIME_Width)
/** @brief Message timestamp (`CANx_RX_FIFO[n].RDTR.TIME`) field mask alias @def CAN_RDTR_TIME */
#define CAN_RDTR_TIME				CAN_RDTR_TIME_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RDLR
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 0 (`CANx_RX_FIFO[n].RDLR.DATA0`) field position @def CAN_RDLR_DATA0_Pos */
#define CAN_RDLR_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 0 (`CANx_RX_FIFO[n].RDLR.DATA0`) field width @def CAN_RDLR_DATA0_Width */
#define CAN_RDLR_DATA0_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 0 (`CANx_RX_FIFO[n].RDLR.DATA0`) field mask @def CAN_RDLR_DATA0_Msk */
#define CAN_RDLR_DATA0_Msk			REG_FIELD_MASK(CAN_RDLR_DATA0_Pos, CAN_RDLR_DATA0_Width)
/** @brief CAN payload byte 0 (`CANx_RX_FIFO[n].RDLR.DATA0`) field mask alias @def CAN_RDLR_DATA0 */
#define CAN_RDLR_DATA0				CAN_RDLR_DATA0_Msk

/** @brief CAN payload byte 1 (`CANx_RX_FIFO[n].RDLR.DATA1`) field position @def CAN_RDLR_DATA1_Pos */
#define CAN_RDLR_DATA1_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 1 (`CANx_RX_FIFO[n].RDLR.DATA1`) field width @def CAN_RDLR_DATA1_Width */
#define CAN_RDLR_DATA1_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 1 (`CANx_RX_FIFO[n].RDLR.DATA1`) field mask @def CAN_RDLR_DATA1_Msk */
#define CAN_RDLR_DATA1_Msk			REG_FIELD_MASK(CAN_RDLR_DATA1_Pos, CAN_RDLR_DATA1_Width)
/** @brief CAN payload byte 1 (`CANx_RX_FIFO[n].RDLR.DATA1`) field mask alias @def CAN_RDLR_DATA1 */
#define CAN_RDLR_DATA1				CAN_RDLR_DATA1_Msk

/** @brief CAN payload byte 2 (`CANx_RX_FIFO[n].RDLR.DATA2`) field position @def CAN_RDLR_DATA2_Pos */
#define CAN_RDLR_DATA2_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 2 (`CANx_RX_FIFO[n].RDLR.DATA2`) field width @def CAN_RDLR_DATA2_Width */
#define CAN_RDLR_DATA2_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 2 (`CANx_RX_FIFO[n].RDLR.DATA2`) field mask @def CAN_RDLR_DATA2_Msk */
#define CAN_RDLR_DATA2_Msk			REG_FIELD_MASK(CAN_RDLR_DATA2_Pos, CAN_RDLR_DATA2_Width)
/** @brief CAN payload byte 2 (`CANx_RX_FIFO[n].RDLR.DATA2`) field mask alias @def CAN_RDLR_DATA2 */
#define CAN_RDLR_DATA2				CAN_RDLR_DATA2_Msk

/** @brief CAN payload byte 3 (`CANx_RX_FIFO[n].RDLR.DATA3`) field position @def CAN_RDLR_DATA3_Pos */
#define CAN_RDLR_DATA3_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 3 (`CANx_RX_FIFO[n].RDLR.DATA3`) field width @def CAN_RDLR_DATA3_Width */
#define CAN_RDLR_DATA3_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 3 (`CANx_RX_FIFO[n].RDLR.DATA3`) field mask @def CAN_RDLR_DATA3_Msk */
#define CAN_RDLR_DATA3_Msk			REG_FIELD_MASK(CAN_RDLR_DATA3_Pos, CAN_RDLR_DATA3_Width)
/** @brief CAN payload byte 3 (`CANx_RX_FIFO[n].RDLR.DATA3`) field mask alias @def CAN_RDLR_DATA3 */
#define CAN_RDLR_DATA3				CAN_RDLR_DATA3_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RDHR
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 4 (`CANx_RX_FIFO[n].RDHR.DATA4`) field position @def CAN_RDHR_DATA4_Pos */
#define CAN_RDHR_DATA4_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 4 (`CANx_RX_FIFO[n].RDHR.DATA4`) field width @def CAN_RDHR_DATA4_Width */
#define CAN_RDHR_DATA4_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 4 (`CANx_RX_FIFO[n].RDHR.DATA4`) field mask @def CAN_RDHR_DATA4_Msk */
#define CAN_RDHR_DATA4_Msk			REG_FIELD_MASK(CAN_RDHR_DATA4_Pos, CAN_RDHR_DATA4_Width)
/** @brief CAN payload byte 4 (`CANx_RX_FIFO[n].RDHR.DATA4`) field mask alias @def CAN_RDHR_DATA4 */
#define CAN_RDHR_DATA4				CAN_RDHR_DATA4_Msk

/** @brief CAN payload byte 5 (`CANx_RX_FIFO[n].RDHR.DATA5`) field position @def CAN_RDHR_DATA5_Pos */
#define CAN_RDHR_DATA5_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 5 (`CANx_RX_FIFO[n].RDHR.DATA5`) field width @def CAN_RDHR_DATA5_Width */
#define CAN_RDHR_DATA5_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 5 (`CANx_RX_FIFO[n].RDHR.DATA5`) field mask @def CAN_RDHR_DATA5_Msk */
#define CAN_RDHR_DATA5_Msk			REG_FIELD_MASK(CAN_RDHR_DATA5_Pos, CAN_RDHR_DATA5_Width)
/** @brief CAN payload byte 5 (`CANx_RX_FIFO[n].RDHR.DATA5`) field mask alias @def CAN_RDHR_DATA5 */
#define CAN_RDHR_DATA5				CAN_RDHR_DATA5_Msk

/** @brief CAN payload byte 6 (`CANx_RX_FIFO[n].RDHR.DATA6`) field position @def CAN_RDHR_DATA6_Pos */
#define CAN_RDHR_DATA6_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 6 (`CANx_RX_FIFO[n].RDHR.DATA6`) field width @def CAN_RDHR_DATA6_Width */
#define CAN_RDHR_DATA6_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 6 (`CANx_RX_FIFO[n].RDHR.DATA6`) field mask @def CAN_RDHR_DATA6_Msk */
#define CAN_RDHR_DATA6_Msk			REG_FIELD_MASK(CAN_RDHR_DATA6_Pos, CAN_RDHR_DATA6_Width)
/** @brief CAN payload byte 6 (`CANx_RX_FIFO[n].RDHR.DATA6`) field mask alias @def CAN_RDHR_DATA6 */
#define CAN_RDHR_DATA6				CAN_RDHR_DATA6_Msk

/** @brief CAN payload byte 7 (`CANx_RX_FIFO[n].RDHR.DATA7`) field position @def CAN_RDHR_DATA7_Pos */
#define CAN_RDHR_DATA7_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 7 (`CANx_RX_FIFO[n].RDHR.DATA7`) field width @def CAN_RDHR_DATA7_Width */
#define CAN_RDHR_DATA7_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 7 (`CANx_RX_FIFO[n].RDHR.DATA7`) field mask @def CAN_RDHR_DATA7_Msk */
#define CAN_RDHR_DATA7_Msk			REG_FIELD_MASK(CAN_RDHR_DATA7_Pos, CAN_RDHR_DATA7_Width)
/** @brief CAN payload byte 7 (`CANx_RX_FIFO[n].RDHR.DATA7`) field mask alias @def CAN_RDHR_DATA7 */
#define CAN_RDHR_DATA7				CAN_RDHR_DATA7_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TI0R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Transmit-mailbox request action (`CANx_TI0R.TXRQ`) bit position @def CAN_TI0R_TXRQ_Pos */
#define CAN_TI0R_TXRQ_Pos			((reg_bit_pos_t) 0U)
/** @brief Transmit-mailbox request action (`CANx_TI0R.TXRQ`) bit mask @def CAN_TI0R_TXRQ_Msk */
#define CAN_TI0R_TXRQ_Msk			REG_BIT_MASK(CAN_TI0R_TXRQ_Pos)
/** @brief Transmit-mailbox request action (`CANx_TI0R.TXRQ`) bit mask alias @def CAN_TI0R_TXRQ */
#define CAN_TI0R_TXRQ				CAN_TI0R_TXRQ_Msk

/** @brief Remote-transmission-request frame selector (`CANx_TI0R.RTR`) bit position @def CAN_TI0R_RTR_Pos */
#define CAN_TI0R_RTR_Pos			((reg_bit_pos_t) 1U)
/** @brief Remote-transmission-request frame selector (`CANx_TI0R.RTR`) bit mask @def CAN_TI0R_RTR_Msk */
#define CAN_TI0R_RTR_Msk			REG_BIT_MASK(CAN_TI0R_RTR_Pos)
/** @brief Remote-transmission-request frame selector (`CANx_TI0R.RTR`) bit mask alias @def CAN_TI0R_RTR */
#define CAN_TI0R_RTR				CAN_TI0R_RTR_Msk

/** @brief Identifier-extension selector (`CANx_TI0R.IDE`) bit position @def CAN_TI0R_IDE_Pos */
#define CAN_TI0R_IDE_Pos			((reg_bit_pos_t) 2U)
/** @brief Identifier-extension selector (`CANx_TI0R.IDE`) bit mask @def CAN_TI0R_IDE_Msk */
#define CAN_TI0R_IDE_Msk			REG_BIT_MASK(CAN_TI0R_IDE_Pos)
/** @brief Identifier-extension selector (`CANx_TI0R.IDE`) bit mask alias @def CAN_TI0R_IDE */
#define CAN_TI0R_IDE				CAN_TI0R_IDE_Msk

/** @brief Extended-identifier portion (`CANx_TI0R.EXID`) field position @def CAN_TI0R_EXID_Pos */
#define CAN_TI0R_EXID_Pos			((reg_bit_pos_t) 3U)
/** @brief Extended-identifier portion (`CANx_TI0R.EXID`) field width @def CAN_TI0R_EXID_Width */
#define CAN_TI0R_EXID_Width			((reg_field_width_t) 18U)
/** @brief Extended-identifier portion (`CANx_TI0R.EXID`) field mask @def CAN_TI0R_EXID_Msk */
#define CAN_TI0R_EXID_Msk			REG_FIELD_MASK(CAN_TI0R_EXID_Pos, CAN_TI0R_EXID_Width)
/** @brief Extended-identifier portion (`CANx_TI0R.EXID`) field mask alias @def CAN_TI0R_EXID */
#define CAN_TI0R_EXID				CAN_TI0R_EXID_Msk

/** @brief Standard identifier or extended-identifier prefix (`CANx_TI0R.STID`) field position @def CAN_TI0R_STID_Pos */
#define CAN_TI0R_STID_Pos			((reg_bit_pos_t) 21U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_TI0R.STID`) field width @def CAN_TI0R_STID_Width */
#define CAN_TI0R_STID_Width			((reg_field_width_t) 11U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_TI0R.STID`) field mask @def CAN_TI0R_STID_Msk */
#define CAN_TI0R_STID_Msk			REG_FIELD_MASK(CAN_TI0R_STID_Pos, CAN_TI0R_STID_Width)
/** @brief Standard identifier or extended-identifier prefix (`CANx_TI0R.STID`) field mask alias @def CAN_TI0R_STID */
#define CAN_TI0R_STID				CAN_TI0R_STID_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TDT0R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Data length code (`CANx_TDT0R.DLC`) field position @def CAN_TDT0R_DLC_Pos */
#define CAN_TDT0R_DLC_Pos			((reg_bit_pos_t) 0U)
/** @brief Data length code (`CANx_TDT0R.DLC`) field width @def CAN_TDT0R_DLC_Width */
#define CAN_TDT0R_DLC_Width			((reg_field_width_t) 4U)
/** @brief Data length code (`CANx_TDT0R.DLC`) field mask @def CAN_TDT0R_DLC_Msk */
#define CAN_TDT0R_DLC_Msk			REG_FIELD_MASK(CAN_TDT0R_DLC_Pos, CAN_TDT0R_DLC_Width)
/** @brief Data length code (`CANx_TDT0R.DLC`) field mask alias @def CAN_TDT0R_DLC */
#define CAN_TDT0R_DLC				CAN_TDT0R_DLC_Msk

/** @brief Global-time transmission request (`CANx_TDT0R.TGT`) bit position @def CAN_TDT0R_TGT_Pos */
#define CAN_TDT0R_TGT_Pos			((reg_bit_pos_t) 8U)
/** @brief Global-time transmission request (`CANx_TDT0R.TGT`) bit mask @def CAN_TDT0R_TGT_Msk */
#define CAN_TDT0R_TGT_Msk			REG_BIT_MASK(CAN_TDT0R_TGT_Pos)
/** @brief Global-time transmission request (`CANx_TDT0R.TGT`) bit mask alias @def CAN_TDT0R_TGT */
#define CAN_TDT0R_TGT				CAN_TDT0R_TGT_Msk

/** @brief Message timestamp (`CANx_TDT0R.TIME`) field position @def CAN_TDT0R_TIME_Pos */
#define CAN_TDT0R_TIME_Pos			((reg_bit_pos_t) 16U)
/** @brief Message timestamp (`CANx_TDT0R.TIME`) field width @def CAN_TDT0R_TIME_Width */
#define CAN_TDT0R_TIME_Width		((reg_field_width_t) 16U)
/** @brief Message timestamp (`CANx_TDT0R.TIME`) field mask @def CAN_TDT0R_TIME_Msk */
#define CAN_TDT0R_TIME_Msk			REG_FIELD_MASK(CAN_TDT0R_TIME_Pos, CAN_TDT0R_TIME_Width)
/** @brief Message timestamp (`CANx_TDT0R.TIME`) field mask alias @def CAN_TDT0R_TIME */
#define CAN_TDT0R_TIME				CAN_TDT0R_TIME_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TDL0R
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 0 (`CANx_TDL0R.DATA0`) field position @def CAN_TDL0R_DATA0_Pos */
#define CAN_TDL0R_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 0 (`CANx_TDL0R.DATA0`) field width @def CAN_TDL0R_DATA0_Width */
#define CAN_TDL0R_DATA0_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 0 (`CANx_TDL0R.DATA0`) field mask @def CAN_TDL0R_DATA0_Msk */
#define CAN_TDL0R_DATA0_Msk			REG_FIELD_MASK(CAN_TDL0R_DATA0_Pos, CAN_TDL0R_DATA0_Width)
/** @brief CAN payload byte 0 (`CANx_TDL0R.DATA0`) field mask alias @def CAN_TDL0R_DATA0 */
#define CAN_TDL0R_DATA0				CAN_TDL0R_DATA0_Msk

/** @brief CAN payload byte 1 (`CANx_TDL0R.DATA1`) field position @def CAN_TDL0R_DATA1_Pos */
#define CAN_TDL0R_DATA1_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 1 (`CANx_TDL0R.DATA1`) field width @def CAN_TDL0R_DATA1_Width */
#define CAN_TDL0R_DATA1_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 1 (`CANx_TDL0R.DATA1`) field mask @def CAN_TDL0R_DATA1_Msk */
#define CAN_TDL0R_DATA1_Msk			REG_FIELD_MASK(CAN_TDL0R_DATA1_Pos, CAN_TDL0R_DATA1_Width)
/** @brief CAN payload byte 1 (`CANx_TDL0R.DATA1`) field mask alias @def CAN_TDL0R_DATA1 */
#define CAN_TDL0R_DATA1				CAN_TDL0R_DATA1_Msk

/** @brief CAN payload byte 2 (`CANx_TDL0R.DATA2`) field position @def CAN_TDL0R_DATA2_Pos */
#define CAN_TDL0R_DATA2_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 2 (`CANx_TDL0R.DATA2`) field width @def CAN_TDL0R_DATA2_Width */
#define CAN_TDL0R_DATA2_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 2 (`CANx_TDL0R.DATA2`) field mask @def CAN_TDL0R_DATA2_Msk */
#define CAN_TDL0R_DATA2_Msk			REG_FIELD_MASK(CAN_TDL0R_DATA2_Pos, CAN_TDL0R_DATA2_Width)
/** @brief CAN payload byte 2 (`CANx_TDL0R.DATA2`) field mask alias @def CAN_TDL0R_DATA2 */
#define CAN_TDL0R_DATA2				CAN_TDL0R_DATA2_Msk

/** @brief CAN payload byte 3 (`CANx_TDL0R.DATA3`) field position @def CAN_TDL0R_DATA3_Pos */
#define CAN_TDL0R_DATA3_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 3 (`CANx_TDL0R.DATA3`) field width @def CAN_TDL0R_DATA3_Width */
#define CAN_TDL0R_DATA3_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 3 (`CANx_TDL0R.DATA3`) field mask @def CAN_TDL0R_DATA3_Msk */
#define CAN_TDL0R_DATA3_Msk			REG_FIELD_MASK(CAN_TDL0R_DATA3_Pos, CAN_TDL0R_DATA3_Width)
/** @brief CAN payload byte 3 (`CANx_TDL0R.DATA3`) field mask alias @def CAN_TDL0R_DATA3 */
#define CAN_TDL0R_DATA3				CAN_TDL0R_DATA3_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TDH0R
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 4 (`CANx_TDH0R.DATA4`) field position @def CAN_TDH0R_DATA4_Pos */
#define CAN_TDH0R_DATA4_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 4 (`CANx_TDH0R.DATA4`) field width @def CAN_TDH0R_DATA4_Width */
#define CAN_TDH0R_DATA4_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 4 (`CANx_TDH0R.DATA4`) field mask @def CAN_TDH0R_DATA4_Msk */
#define CAN_TDH0R_DATA4_Msk			REG_FIELD_MASK(CAN_TDH0R_DATA4_Pos, CAN_TDH0R_DATA4_Width)
/** @brief CAN payload byte 4 (`CANx_TDH0R.DATA4`) field mask alias @def CAN_TDH0R_DATA4 */
#define CAN_TDH0R_DATA4				CAN_TDH0R_DATA4_Msk

/** @brief CAN payload byte 5 (`CANx_TDH0R.DATA5`) field position @def CAN_TDH0R_DATA5_Pos */
#define CAN_TDH0R_DATA5_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 5 (`CANx_TDH0R.DATA5`) field width @def CAN_TDH0R_DATA5_Width */
#define CAN_TDH0R_DATA5_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 5 (`CANx_TDH0R.DATA5`) field mask @def CAN_TDH0R_DATA5_Msk */
#define CAN_TDH0R_DATA5_Msk			REG_FIELD_MASK(CAN_TDH0R_DATA5_Pos, CAN_TDH0R_DATA5_Width)
/** @brief CAN payload byte 5 (`CANx_TDH0R.DATA5`) field mask alias @def CAN_TDH0R_DATA5 */
#define CAN_TDH0R_DATA5				CAN_TDH0R_DATA5_Msk

/** @brief CAN payload byte 6 (`CANx_TDH0R.DATA6`) field position @def CAN_TDH0R_DATA6_Pos */
#define CAN_TDH0R_DATA6_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 6 (`CANx_TDH0R.DATA6`) field width @def CAN_TDH0R_DATA6_Width */
#define CAN_TDH0R_DATA6_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 6 (`CANx_TDH0R.DATA6`) field mask @def CAN_TDH0R_DATA6_Msk */
#define CAN_TDH0R_DATA6_Msk			REG_FIELD_MASK(CAN_TDH0R_DATA6_Pos, CAN_TDH0R_DATA6_Width)
/** @brief CAN payload byte 6 (`CANx_TDH0R.DATA6`) field mask alias @def CAN_TDH0R_DATA6 */
#define CAN_TDH0R_DATA6				CAN_TDH0R_DATA6_Msk

/** @brief CAN payload byte 7 (`CANx_TDH0R.DATA7`) field position @def CAN_TDH0R_DATA7_Pos */
#define CAN_TDH0R_DATA7_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 7 (`CANx_TDH0R.DATA7`) field width @def CAN_TDH0R_DATA7_Width */
#define CAN_TDH0R_DATA7_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 7 (`CANx_TDH0R.DATA7`) field mask @def CAN_TDH0R_DATA7_Msk */
#define CAN_TDH0R_DATA7_Msk			REG_FIELD_MASK(CAN_TDH0R_DATA7_Pos, CAN_TDH0R_DATA7_Width)
/** @brief CAN payload byte 7 (`CANx_TDH0R.DATA7`) field mask alias @def CAN_TDH0R_DATA7 */
#define CAN_TDH0R_DATA7				CAN_TDH0R_DATA7_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TI1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Transmit-mailbox request action (`CANx_TI1R.TXRQ`) bit position @def CAN_TI1R_TXRQ_Pos */
#define CAN_TI1R_TXRQ_Pos			((reg_bit_pos_t) 0U)
/** @brief Transmit-mailbox request action (`CANx_TI1R.TXRQ`) bit mask @def CAN_TI1R_TXRQ_Msk */
#define CAN_TI1R_TXRQ_Msk			REG_BIT_MASK(CAN_TI1R_TXRQ_Pos)
/** @brief Transmit-mailbox request action (`CANx_TI1R.TXRQ`) bit mask alias @def CAN_TI1R_TXRQ */
#define CAN_TI1R_TXRQ				CAN_TI1R_TXRQ_Msk

/** @brief Remote-transmission-request frame selector (`CANx_TI1R.RTR`) bit position @def CAN_TI1R_RTR_Pos */
#define CAN_TI1R_RTR_Pos			((reg_bit_pos_t) 1U)
/** @brief Remote-transmission-request frame selector (`CANx_TI1R.RTR`) bit mask @def CAN_TI1R_RTR_Msk */
#define CAN_TI1R_RTR_Msk			REG_BIT_MASK(CAN_TI1R_RTR_Pos)
/** @brief Remote-transmission-request frame selector (`CANx_TI1R.RTR`) bit mask alias @def CAN_TI1R_RTR */
#define CAN_TI1R_RTR				CAN_TI1R_RTR_Msk

/** @brief Identifier-extension selector (`CANx_TI1R.IDE`) bit position @def CAN_TI1R_IDE_Pos */
#define CAN_TI1R_IDE_Pos			((reg_bit_pos_t) 2U)
/** @brief Identifier-extension selector (`CANx_TI1R.IDE`) bit mask @def CAN_TI1R_IDE_Msk */
#define CAN_TI1R_IDE_Msk			REG_BIT_MASK(CAN_TI1R_IDE_Pos)
/** @brief Identifier-extension selector (`CANx_TI1R.IDE`) bit mask alias @def CAN_TI1R_IDE */
#define CAN_TI1R_IDE				CAN_TI1R_IDE_Msk

/** @brief Extended-identifier portion (`CANx_TI1R.EXID`) field position @def CAN_TI1R_EXID_Pos */
#define CAN_TI1R_EXID_Pos			((reg_bit_pos_t) 3U)
/** @brief Extended-identifier portion (`CANx_TI1R.EXID`) field width @def CAN_TI1R_EXID_Width */
#define CAN_TI1R_EXID_Width			((reg_field_width_t) 18U)
/** @brief Extended-identifier portion (`CANx_TI1R.EXID`) field mask @def CAN_TI1R_EXID_Msk */
#define CAN_TI1R_EXID_Msk			REG_FIELD_MASK(CAN_TI1R_EXID_Pos, CAN_TI1R_EXID_Width)
/** @brief Extended-identifier portion (`CANx_TI1R.EXID`) field mask alias @def CAN_TI1R_EXID */
#define CAN_TI1R_EXID				CAN_TI1R_EXID_Msk

/** @brief Standard identifier or extended-identifier prefix (`CANx_TI1R.STID`) field position @def CAN_TI1R_STID_Pos */
#define CAN_TI1R_STID_Pos			((reg_bit_pos_t) 21U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_TI1R.STID`) field width @def CAN_TI1R_STID_Width */
#define CAN_TI1R_STID_Width			((reg_field_width_t) 11U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_TI1R.STID`) field mask @def CAN_TI1R_STID_Msk */
#define CAN_TI1R_STID_Msk			REG_FIELD_MASK(CAN_TI1R_STID_Pos, CAN_TI1R_STID_Width)
/** @brief Standard identifier or extended-identifier prefix (`CANx_TI1R.STID`) field mask alias @def CAN_TI1R_STID */
#define CAN_TI1R_STID				CAN_TI1R_STID_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TDT1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Data length code (`CANx_TDT1R.DLC`) field position @def CAN_TDT1R_DLC_Pos */
#define CAN_TDT1R_DLC_Pos			((reg_bit_pos_t) 0U)
/** @brief Data length code (`CANx_TDT1R.DLC`) field width @def CAN_TDT1R_DLC_Width */
#define CAN_TDT1R_DLC_Width			((reg_field_width_t) 4U)
/** @brief Data length code (`CANx_TDT1R.DLC`) field mask @def CAN_TDT1R_DLC_Msk */
#define CAN_TDT1R_DLC_Msk			REG_FIELD_MASK(CAN_TDT1R_DLC_Pos, CAN_TDT1R_DLC_Width)
/** @brief Data length code (`CANx_TDT1R.DLC`) field mask alias @def CAN_TDT1R_DLC */
#define CAN_TDT1R_DLC				CAN_TDT1R_DLC_Msk

/** @brief Global-time transmission request (`CANx_TDT1R.TGT`) bit position @def CAN_TDT1R_TGT_Pos */
#define CAN_TDT1R_TGT_Pos			((reg_bit_pos_t) 8U)
/** @brief Global-time transmission request (`CANx_TDT1R.TGT`) bit mask @def CAN_TDT1R_TGT_Msk */
#define CAN_TDT1R_TGT_Msk			REG_BIT_MASK(CAN_TDT1R_TGT_Pos)
/** @brief Global-time transmission request (`CANx_TDT1R.TGT`) bit mask alias @def CAN_TDT1R_TGT */
#define CAN_TDT1R_TGT				CAN_TDT1R_TGT_Msk

/** @brief Message timestamp (`CANx_TDT1R.TIME`) field position @def CAN_TDT1R_TIME_Pos */
#define CAN_TDT1R_TIME_Pos			((reg_bit_pos_t) 16U)
/** @brief Message timestamp (`CANx_TDT1R.TIME`) field width @def CAN_TDT1R_TIME_Width */
#define CAN_TDT1R_TIME_Width		((reg_field_width_t) 16U)
/** @brief Message timestamp (`CANx_TDT1R.TIME`) field mask @def CAN_TDT1R_TIME_Msk */
#define CAN_TDT1R_TIME_Msk			REG_FIELD_MASK(CAN_TDT1R_TIME_Pos, CAN_TDT1R_TIME_Width)
/** @brief Message timestamp (`CANx_TDT1R.TIME`) field mask alias @def CAN_TDT1R_TIME */
#define CAN_TDT1R_TIME				CAN_TDT1R_TIME_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TDL1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 0 (`CANx_TDL1R.DATA0`) field position @def CAN_TDL1R_DATA0_Pos */
#define CAN_TDL1R_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 0 (`CANx_TDL1R.DATA0`) field width @def CAN_TDL1R_DATA0_Width */
#define CAN_TDL1R_DATA0_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 0 (`CANx_TDL1R.DATA0`) field mask @def CAN_TDL1R_DATA0_Msk */
#define CAN_TDL1R_DATA0_Msk			REG_FIELD_MASK(CAN_TDL1R_DATA0_Pos, CAN_TDL1R_DATA0_Width)
/** @brief CAN payload byte 0 (`CANx_TDL1R.DATA0`) field mask alias @def CAN_TDL1R_DATA0 */
#define CAN_TDL1R_DATA0				CAN_TDL1R_DATA0_Msk

/** @brief CAN payload byte 1 (`CANx_TDL1R.DATA1`) field position @def CAN_TDL1R_DATA1_Pos */
#define CAN_TDL1R_DATA1_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 1 (`CANx_TDL1R.DATA1`) field width @def CAN_TDL1R_DATA1_Width */
#define CAN_TDL1R_DATA1_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 1 (`CANx_TDL1R.DATA1`) field mask @def CAN_TDL1R_DATA1_Msk */
#define CAN_TDL1R_DATA1_Msk			REG_FIELD_MASK(CAN_TDL1R_DATA1_Pos, CAN_TDL1R_DATA1_Width)
/** @brief CAN payload byte 1 (`CANx_TDL1R.DATA1`) field mask alias @def CAN_TDL1R_DATA1 */
#define CAN_TDL1R_DATA1				CAN_TDL1R_DATA1_Msk

/** @brief CAN payload byte 2 (`CANx_TDL1R.DATA2`) field position @def CAN_TDL1R_DATA2_Pos */
#define CAN_TDL1R_DATA2_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 2 (`CANx_TDL1R.DATA2`) field width @def CAN_TDL1R_DATA2_Width */
#define CAN_TDL1R_DATA2_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 2 (`CANx_TDL1R.DATA2`) field mask @def CAN_TDL1R_DATA2_Msk */
#define CAN_TDL1R_DATA2_Msk			REG_FIELD_MASK(CAN_TDL1R_DATA2_Pos, CAN_TDL1R_DATA2_Width)
/** @brief CAN payload byte 2 (`CANx_TDL1R.DATA2`) field mask alias @def CAN_TDL1R_DATA2 */
#define CAN_TDL1R_DATA2				CAN_TDL1R_DATA2_Msk

/** @brief CAN payload byte 3 (`CANx_TDL1R.DATA3`) field position @def CAN_TDL1R_DATA3_Pos */
#define CAN_TDL1R_DATA3_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 3 (`CANx_TDL1R.DATA3`) field width @def CAN_TDL1R_DATA3_Width */
#define CAN_TDL1R_DATA3_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 3 (`CANx_TDL1R.DATA3`) field mask @def CAN_TDL1R_DATA3_Msk */
#define CAN_TDL1R_DATA3_Msk			REG_FIELD_MASK(CAN_TDL1R_DATA3_Pos, CAN_TDL1R_DATA3_Width)
/** @brief CAN payload byte 3 (`CANx_TDL1R.DATA3`) field mask alias @def CAN_TDL1R_DATA3 */
#define CAN_TDL1R_DATA3				CAN_TDL1R_DATA3_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TDH1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 4 (`CANx_TDH1R.DATA4`) field position @def CAN_TDH1R_DATA4_Pos */
#define CAN_TDH1R_DATA4_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 4 (`CANx_TDH1R.DATA4`) field width @def CAN_TDH1R_DATA4_Width */
#define CAN_TDH1R_DATA4_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 4 (`CANx_TDH1R.DATA4`) field mask @def CAN_TDH1R_DATA4_Msk */
#define CAN_TDH1R_DATA4_Msk			REG_FIELD_MASK(CAN_TDH1R_DATA4_Pos, CAN_TDH1R_DATA4_Width)
/** @brief CAN payload byte 4 (`CANx_TDH1R.DATA4`) field mask alias @def CAN_TDH1R_DATA4 */
#define CAN_TDH1R_DATA4				CAN_TDH1R_DATA4_Msk

/** @brief CAN payload byte 5 (`CANx_TDH1R.DATA5`) field position @def CAN_TDH1R_DATA5_Pos */
#define CAN_TDH1R_DATA5_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 5 (`CANx_TDH1R.DATA5`) field width @def CAN_TDH1R_DATA5_Width */
#define CAN_TDH1R_DATA5_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 5 (`CANx_TDH1R.DATA5`) field mask @def CAN_TDH1R_DATA5_Msk */
#define CAN_TDH1R_DATA5_Msk			REG_FIELD_MASK(CAN_TDH1R_DATA5_Pos, CAN_TDH1R_DATA5_Width)
/** @brief CAN payload byte 5 (`CANx_TDH1R.DATA5`) field mask alias @def CAN_TDH1R_DATA5 */
#define CAN_TDH1R_DATA5				CAN_TDH1R_DATA5_Msk

/** @brief CAN payload byte 6 (`CANx_TDH1R.DATA6`) field position @def CAN_TDH1R_DATA6_Pos */
#define CAN_TDH1R_DATA6_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 6 (`CANx_TDH1R.DATA6`) field width @def CAN_TDH1R_DATA6_Width */
#define CAN_TDH1R_DATA6_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 6 (`CANx_TDH1R.DATA6`) field mask @def CAN_TDH1R_DATA6_Msk */
#define CAN_TDH1R_DATA6_Msk			REG_FIELD_MASK(CAN_TDH1R_DATA6_Pos, CAN_TDH1R_DATA6_Width)
/** @brief CAN payload byte 6 (`CANx_TDH1R.DATA6`) field mask alias @def CAN_TDH1R_DATA6 */
#define CAN_TDH1R_DATA6				CAN_TDH1R_DATA6_Msk

/** @brief CAN payload byte 7 (`CANx_TDH1R.DATA7`) field position @def CAN_TDH1R_DATA7_Pos */
#define CAN_TDH1R_DATA7_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 7 (`CANx_TDH1R.DATA7`) field width @def CAN_TDH1R_DATA7_Width */
#define CAN_TDH1R_DATA7_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 7 (`CANx_TDH1R.DATA7`) field mask @def CAN_TDH1R_DATA7_Msk */
#define CAN_TDH1R_DATA7_Msk			REG_FIELD_MASK(CAN_TDH1R_DATA7_Pos, CAN_TDH1R_DATA7_Width)
/** @brief CAN payload byte 7 (`CANx_TDH1R.DATA7`) field mask alias @def CAN_TDH1R_DATA7 */
#define CAN_TDH1R_DATA7				CAN_TDH1R_DATA7_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TI2R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Transmit-mailbox request action (`CANx_TI2R.TXRQ`) bit position @def CAN_TI2R_TXRQ_Pos */
#define CAN_TI2R_TXRQ_Pos			((reg_bit_pos_t) 0U)
/** @brief Transmit-mailbox request action (`CANx_TI2R.TXRQ`) bit mask @def CAN_TI2R_TXRQ_Msk */
#define CAN_TI2R_TXRQ_Msk			REG_BIT_MASK(CAN_TI2R_TXRQ_Pos)
/** @brief Transmit-mailbox request action (`CANx_TI2R.TXRQ`) bit mask alias @def CAN_TI2R_TXRQ */
#define CAN_TI2R_TXRQ				CAN_TI2R_TXRQ_Msk

/** @brief Remote-transmission-request frame selector (`CANx_TI2R.RTR`) bit position @def CAN_TI2R_RTR_Pos */
#define CAN_TI2R_RTR_Pos			((reg_bit_pos_t) 1U)
/** @brief Remote-transmission-request frame selector (`CANx_TI2R.RTR`) bit mask @def CAN_TI2R_RTR_Msk */
#define CAN_TI2R_RTR_Msk			REG_BIT_MASK(CAN_TI2R_RTR_Pos)
/** @brief Remote-transmission-request frame selector (`CANx_TI2R.RTR`) bit mask alias @def CAN_TI2R_RTR */
#define CAN_TI2R_RTR				CAN_TI2R_RTR_Msk

/** @brief Identifier-extension selector (`CANx_TI2R.IDE`) bit position @def CAN_TI2R_IDE_Pos */
#define CAN_TI2R_IDE_Pos			((reg_bit_pos_t) 2U)
/** @brief Identifier-extension selector (`CANx_TI2R.IDE`) bit mask @def CAN_TI2R_IDE_Msk */
#define CAN_TI2R_IDE_Msk			REG_BIT_MASK(CAN_TI2R_IDE_Pos)
/** @brief Identifier-extension selector (`CANx_TI2R.IDE`) bit mask alias @def CAN_TI2R_IDE */
#define CAN_TI2R_IDE				CAN_TI2R_IDE_Msk

/** @brief Extended-identifier portion (`CANx_TI2R.EXID`) field position @def CAN_TI2R_EXID_Pos */
#define CAN_TI2R_EXID_Pos			((reg_bit_pos_t) 3U)
/** @brief Extended-identifier portion (`CANx_TI2R.EXID`) field width @def CAN_TI2R_EXID_Width */
#define CAN_TI2R_EXID_Width			((reg_field_width_t) 18U)
/** @brief Extended-identifier portion (`CANx_TI2R.EXID`) field mask @def CAN_TI2R_EXID_Msk */
#define CAN_TI2R_EXID_Msk			REG_FIELD_MASK(CAN_TI2R_EXID_Pos, CAN_TI2R_EXID_Width)
/** @brief Extended-identifier portion (`CANx_TI2R.EXID`) field mask alias @def CAN_TI2R_EXID */
#define CAN_TI2R_EXID				CAN_TI2R_EXID_Msk

/** @brief Standard identifier or extended-identifier prefix (`CANx_TI2R.STID`) field position @def CAN_TI2R_STID_Pos */
#define CAN_TI2R_STID_Pos			((reg_bit_pos_t) 21U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_TI2R.STID`) field width @def CAN_TI2R_STID_Width */
#define CAN_TI2R_STID_Width			((reg_field_width_t) 11U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_TI2R.STID`) field mask @def CAN_TI2R_STID_Msk */
#define CAN_TI2R_STID_Msk			REG_FIELD_MASK(CAN_TI2R_STID_Pos, CAN_TI2R_STID_Width)
/** @brief Standard identifier or extended-identifier prefix (`CANx_TI2R.STID`) field mask alias @def CAN_TI2R_STID */
#define CAN_TI2R_STID				CAN_TI2R_STID_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TDT2R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Data length code (`CANx_TDT2R.DLC`) field position @def CAN_TDT2R_DLC_Pos */
#define CAN_TDT2R_DLC_Pos			((reg_bit_pos_t) 0U)
/** @brief Data length code (`CANx_TDT2R.DLC`) field width @def CAN_TDT2R_DLC_Width */
#define CAN_TDT2R_DLC_Width			((reg_field_width_t) 4U)
/** @brief Data length code (`CANx_TDT2R.DLC`) field mask @def CAN_TDT2R_DLC_Msk */
#define CAN_TDT2R_DLC_Msk			REG_FIELD_MASK(CAN_TDT2R_DLC_Pos, CAN_TDT2R_DLC_Width)
/** @brief Data length code (`CANx_TDT2R.DLC`) field mask alias @def CAN_TDT2R_DLC */
#define CAN_TDT2R_DLC				CAN_TDT2R_DLC_Msk

/** @brief Global-time transmission request (`CANx_TDT2R.TGT`) bit position @def CAN_TDT2R_TGT_Pos */
#define CAN_TDT2R_TGT_Pos			((reg_bit_pos_t) 8U)
/** @brief Global-time transmission request (`CANx_TDT2R.TGT`) bit mask @def CAN_TDT2R_TGT_Msk */
#define CAN_TDT2R_TGT_Msk			REG_BIT_MASK(CAN_TDT2R_TGT_Pos)
/** @brief Global-time transmission request (`CANx_TDT2R.TGT`) bit mask alias @def CAN_TDT2R_TGT */
#define CAN_TDT2R_TGT				CAN_TDT2R_TGT_Msk

/** @brief Message timestamp (`CANx_TDT2R.TIME`) field position @def CAN_TDT2R_TIME_Pos */
#define CAN_TDT2R_TIME_Pos			((reg_bit_pos_t) 16U)
/** @brief Message timestamp (`CANx_TDT2R.TIME`) field width @def CAN_TDT2R_TIME_Width */
#define CAN_TDT2R_TIME_Width		((reg_field_width_t) 16U)
/** @brief Message timestamp (`CANx_TDT2R.TIME`) field mask @def CAN_TDT2R_TIME_Msk */
#define CAN_TDT2R_TIME_Msk			REG_FIELD_MASK(CAN_TDT2R_TIME_Pos, CAN_TDT2R_TIME_Width)
/** @brief Message timestamp (`CANx_TDT2R.TIME`) field mask alias @def CAN_TDT2R_TIME */
#define CAN_TDT2R_TIME				CAN_TDT2R_TIME_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TDL2R
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 0 (`CANx_TDL2R.DATA0`) field position @def CAN_TDL2R_DATA0_Pos */
#define CAN_TDL2R_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 0 (`CANx_TDL2R.DATA0`) field width @def CAN_TDL2R_DATA0_Width */
#define CAN_TDL2R_DATA0_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 0 (`CANx_TDL2R.DATA0`) field mask @def CAN_TDL2R_DATA0_Msk */
#define CAN_TDL2R_DATA0_Msk			REG_FIELD_MASK(CAN_TDL2R_DATA0_Pos, CAN_TDL2R_DATA0_Width)
/** @brief CAN payload byte 0 (`CANx_TDL2R.DATA0`) field mask alias @def CAN_TDL2R_DATA0 */
#define CAN_TDL2R_DATA0				CAN_TDL2R_DATA0_Msk

/** @brief CAN payload byte 1 (`CANx_TDL2R.DATA1`) field position @def CAN_TDL2R_DATA1_Pos */
#define CAN_TDL2R_DATA1_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 1 (`CANx_TDL2R.DATA1`) field width @def CAN_TDL2R_DATA1_Width */
#define CAN_TDL2R_DATA1_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 1 (`CANx_TDL2R.DATA1`) field mask @def CAN_TDL2R_DATA1_Msk */
#define CAN_TDL2R_DATA1_Msk			REG_FIELD_MASK(CAN_TDL2R_DATA1_Pos, CAN_TDL2R_DATA1_Width)
/** @brief CAN payload byte 1 (`CANx_TDL2R.DATA1`) field mask alias @def CAN_TDL2R_DATA1 */
#define CAN_TDL2R_DATA1				CAN_TDL2R_DATA1_Msk

/** @brief CAN payload byte 2 (`CANx_TDL2R.DATA2`) field position @def CAN_TDL2R_DATA2_Pos */
#define CAN_TDL2R_DATA2_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 2 (`CANx_TDL2R.DATA2`) field width @def CAN_TDL2R_DATA2_Width */
#define CAN_TDL2R_DATA2_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 2 (`CANx_TDL2R.DATA2`) field mask @def CAN_TDL2R_DATA2_Msk */
#define CAN_TDL2R_DATA2_Msk			REG_FIELD_MASK(CAN_TDL2R_DATA2_Pos, CAN_TDL2R_DATA2_Width)
/** @brief CAN payload byte 2 (`CANx_TDL2R.DATA2`) field mask alias @def CAN_TDL2R_DATA2 */
#define CAN_TDL2R_DATA2				CAN_TDL2R_DATA2_Msk

/** @brief CAN payload byte 3 (`CANx_TDL2R.DATA3`) field position @def CAN_TDL2R_DATA3_Pos */
#define CAN_TDL2R_DATA3_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 3 (`CANx_TDL2R.DATA3`) field width @def CAN_TDL2R_DATA3_Width */
#define CAN_TDL2R_DATA3_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 3 (`CANx_TDL2R.DATA3`) field mask @def CAN_TDL2R_DATA3_Msk */
#define CAN_TDL2R_DATA3_Msk			REG_FIELD_MASK(CAN_TDL2R_DATA3_Pos, CAN_TDL2R_DATA3_Width)
/** @brief CAN payload byte 3 (`CANx_TDL2R.DATA3`) field mask alias @def CAN_TDL2R_DATA3 */
#define CAN_TDL2R_DATA3				CAN_TDL2R_DATA3_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_TDH2R
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 4 (`CANx_TDH2R.DATA4`) field position @def CAN_TDH2R_DATA4_Pos */
#define CAN_TDH2R_DATA4_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 4 (`CANx_TDH2R.DATA4`) field width @def CAN_TDH2R_DATA4_Width */
#define CAN_TDH2R_DATA4_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 4 (`CANx_TDH2R.DATA4`) field mask @def CAN_TDH2R_DATA4_Msk */
#define CAN_TDH2R_DATA4_Msk			REG_FIELD_MASK(CAN_TDH2R_DATA4_Pos, CAN_TDH2R_DATA4_Width)
/** @brief CAN payload byte 4 (`CANx_TDH2R.DATA4`) field mask alias @def CAN_TDH2R_DATA4 */
#define CAN_TDH2R_DATA4				CAN_TDH2R_DATA4_Msk

/** @brief CAN payload byte 5 (`CANx_TDH2R.DATA5`) field position @def CAN_TDH2R_DATA5_Pos */
#define CAN_TDH2R_DATA5_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 5 (`CANx_TDH2R.DATA5`) field width @def CAN_TDH2R_DATA5_Width */
#define CAN_TDH2R_DATA5_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 5 (`CANx_TDH2R.DATA5`) field mask @def CAN_TDH2R_DATA5_Msk */
#define CAN_TDH2R_DATA5_Msk			REG_FIELD_MASK(CAN_TDH2R_DATA5_Pos, CAN_TDH2R_DATA5_Width)
/** @brief CAN payload byte 5 (`CANx_TDH2R.DATA5`) field mask alias @def CAN_TDH2R_DATA5 */
#define CAN_TDH2R_DATA5				CAN_TDH2R_DATA5_Msk

/** @brief CAN payload byte 6 (`CANx_TDH2R.DATA6`) field position @def CAN_TDH2R_DATA6_Pos */
#define CAN_TDH2R_DATA6_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 6 (`CANx_TDH2R.DATA6`) field width @def CAN_TDH2R_DATA6_Width */
#define CAN_TDH2R_DATA6_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 6 (`CANx_TDH2R.DATA6`) field mask @def CAN_TDH2R_DATA6_Msk */
#define CAN_TDH2R_DATA6_Msk			REG_FIELD_MASK(CAN_TDH2R_DATA6_Pos, CAN_TDH2R_DATA6_Width)
/** @brief CAN payload byte 6 (`CANx_TDH2R.DATA6`) field mask alias @def CAN_TDH2R_DATA6 */
#define CAN_TDH2R_DATA6				CAN_TDH2R_DATA6_Msk

/** @brief CAN payload byte 7 (`CANx_TDH2R.DATA7`) field position @def CAN_TDH2R_DATA7_Pos */
#define CAN_TDH2R_DATA7_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 7 (`CANx_TDH2R.DATA7`) field width @def CAN_TDH2R_DATA7_Width */
#define CAN_TDH2R_DATA7_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 7 (`CANx_TDH2R.DATA7`) field mask @def CAN_TDH2R_DATA7_Msk */
#define CAN_TDH2R_DATA7_Msk			REG_FIELD_MASK(CAN_TDH2R_DATA7_Pos, CAN_TDH2R_DATA7_Width)
/** @brief CAN payload byte 7 (`CANx_TDH2R.DATA7`) field mask alias @def CAN_TDH2R_DATA7 */
#define CAN_TDH2R_DATA7				CAN_TDH2R_DATA7_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RI0R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Remote-transmission-request frame selector (`CANx_RI0R.RTR`) bit position @def CAN_RI0R_RTR_Pos */
#define CAN_RI0R_RTR_Pos			((reg_bit_pos_t) 1U)
/** @brief Remote-transmission-request frame selector (`CANx_RI0R.RTR`) bit mask @def CAN_RI0R_RTR_Msk */
#define CAN_RI0R_RTR_Msk			REG_BIT_MASK(CAN_RI0R_RTR_Pos)
/** @brief Remote-transmission-request frame selector (`CANx_RI0R.RTR`) bit mask alias @def CAN_RI0R_RTR */
#define CAN_RI0R_RTR				CAN_RI0R_RTR_Msk

/** @brief Identifier-extension selector (`CANx_RI0R.IDE`) bit position @def CAN_RI0R_IDE_Pos */
#define CAN_RI0R_IDE_Pos			((reg_bit_pos_t) 2U)
/** @brief Identifier-extension selector (`CANx_RI0R.IDE`) bit mask @def CAN_RI0R_IDE_Msk */
#define CAN_RI0R_IDE_Msk			REG_BIT_MASK(CAN_RI0R_IDE_Pos)
/** @brief Identifier-extension selector (`CANx_RI0R.IDE`) bit mask alias @def CAN_RI0R_IDE */
#define CAN_RI0R_IDE				CAN_RI0R_IDE_Msk

/** @brief Extended-identifier portion (`CANx_RI0R.EXID`) field position @def CAN_RI0R_EXID_Pos */
#define CAN_RI0R_EXID_Pos			((reg_bit_pos_t) 3U)
/** @brief Extended-identifier portion (`CANx_RI0R.EXID`) field width @def CAN_RI0R_EXID_Width */
#define CAN_RI0R_EXID_Width			((reg_field_width_t) 18U)
/** @brief Extended-identifier portion (`CANx_RI0R.EXID`) field mask @def CAN_RI0R_EXID_Msk */
#define CAN_RI0R_EXID_Msk			REG_FIELD_MASK(CAN_RI0R_EXID_Pos, CAN_RI0R_EXID_Width)
/** @brief Extended-identifier portion (`CANx_RI0R.EXID`) field mask alias @def CAN_RI0R_EXID */
#define CAN_RI0R_EXID				CAN_RI0R_EXID_Msk

/** @brief Standard identifier or extended-identifier prefix (`CANx_RI0R.STID`) field position @def CAN_RI0R_STID_Pos */
#define CAN_RI0R_STID_Pos			((reg_bit_pos_t) 21U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_RI0R.STID`) field width @def CAN_RI0R_STID_Width */
#define CAN_RI0R_STID_Width			((reg_field_width_t) 11U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_RI0R.STID`) field mask @def CAN_RI0R_STID_Msk */
#define CAN_RI0R_STID_Msk			REG_FIELD_MASK(CAN_RI0R_STID_Pos, CAN_RI0R_STID_Width)
/** @brief Standard identifier or extended-identifier prefix (`CANx_RI0R.STID`) field mask alias @def CAN_RI0R_STID */
#define CAN_RI0R_STID				CAN_RI0R_STID_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RDT0R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Data length code (`CANx_RDT0R.DLC`) field position @def CAN_RDT0R_DLC_Pos */
#define CAN_RDT0R_DLC_Pos			((reg_bit_pos_t) 0U)
/** @brief Data length code (`CANx_RDT0R.DLC`) field width @def CAN_RDT0R_DLC_Width */
#define CAN_RDT0R_DLC_Width			((reg_field_width_t) 4U)
/** @brief Data length code (`CANx_RDT0R.DLC`) field mask @def CAN_RDT0R_DLC_Msk */
#define CAN_RDT0R_DLC_Msk			REG_FIELD_MASK(CAN_RDT0R_DLC_Pos, CAN_RDT0R_DLC_Width)
/** @brief Data length code (`CANx_RDT0R.DLC`) field mask alias @def CAN_RDT0R_DLC */
#define CAN_RDT0R_DLC				CAN_RDT0R_DLC_Msk

/** @brief Filter match index (`CANx_RDT0R.FMI`) field position @def CAN_RDT0R_FMI_Pos */
#define CAN_RDT0R_FMI_Pos			((reg_bit_pos_t) 8U)
/** @brief Filter match index (`CANx_RDT0R.FMI`) field width @def CAN_RDT0R_FMI_Width */
#define CAN_RDT0R_FMI_Width			((reg_field_width_t) 8U)
/** @brief Filter match index (`CANx_RDT0R.FMI`) field mask @def CAN_RDT0R_FMI_Msk */
#define CAN_RDT0R_FMI_Msk			REG_FIELD_MASK(CAN_RDT0R_FMI_Pos, CAN_RDT0R_FMI_Width)
/** @brief Filter match index (`CANx_RDT0R.FMI`) field mask alias @def CAN_RDT0R_FMI */
#define CAN_RDT0R_FMI				CAN_RDT0R_FMI_Msk

/** @brief Message timestamp (`CANx_RDT0R.TIME`) field position @def CAN_RDT0R_TIME_Pos */
#define CAN_RDT0R_TIME_Pos			((reg_bit_pos_t) 16U)
/** @brief Message timestamp (`CANx_RDT0R.TIME`) field width @def CAN_RDT0R_TIME_Width */
#define CAN_RDT0R_TIME_Width		((reg_field_width_t) 16U)
/** @brief Message timestamp (`CANx_RDT0R.TIME`) field mask @def CAN_RDT0R_TIME_Msk */
#define CAN_RDT0R_TIME_Msk			REG_FIELD_MASK(CAN_RDT0R_TIME_Pos, CAN_RDT0R_TIME_Width)
/** @brief Message timestamp (`CANx_RDT0R.TIME`) field mask alias @def CAN_RDT0R_TIME */
#define CAN_RDT0R_TIME				CAN_RDT0R_TIME_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RDL0R
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 0 (`CANx_RDL0R.DATA0`) field position @def CAN_RDL0R_DATA0_Pos */
#define CAN_RDL0R_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 0 (`CANx_RDL0R.DATA0`) field width @def CAN_RDL0R_DATA0_Width */
#define CAN_RDL0R_DATA0_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 0 (`CANx_RDL0R.DATA0`) field mask @def CAN_RDL0R_DATA0_Msk */
#define CAN_RDL0R_DATA0_Msk			REG_FIELD_MASK(CAN_RDL0R_DATA0_Pos, CAN_RDL0R_DATA0_Width)
/** @brief CAN payload byte 0 (`CANx_RDL0R.DATA0`) field mask alias @def CAN_RDL0R_DATA0 */
#define CAN_RDL0R_DATA0				CAN_RDL0R_DATA0_Msk

/** @brief CAN payload byte 1 (`CANx_RDL0R.DATA1`) field position @def CAN_RDL0R_DATA1_Pos */
#define CAN_RDL0R_DATA1_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 1 (`CANx_RDL0R.DATA1`) field width @def CAN_RDL0R_DATA1_Width */
#define CAN_RDL0R_DATA1_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 1 (`CANx_RDL0R.DATA1`) field mask @def CAN_RDL0R_DATA1_Msk */
#define CAN_RDL0R_DATA1_Msk			REG_FIELD_MASK(CAN_RDL0R_DATA1_Pos, CAN_RDL0R_DATA1_Width)
/** @brief CAN payload byte 1 (`CANx_RDL0R.DATA1`) field mask alias @def CAN_RDL0R_DATA1 */
#define CAN_RDL0R_DATA1				CAN_RDL0R_DATA1_Msk

/** @brief CAN payload byte 2 (`CANx_RDL0R.DATA2`) field position @def CAN_RDL0R_DATA2_Pos */
#define CAN_RDL0R_DATA2_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 2 (`CANx_RDL0R.DATA2`) field width @def CAN_RDL0R_DATA2_Width */
#define CAN_RDL0R_DATA2_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 2 (`CANx_RDL0R.DATA2`) field mask @def CAN_RDL0R_DATA2_Msk */
#define CAN_RDL0R_DATA2_Msk			REG_FIELD_MASK(CAN_RDL0R_DATA2_Pos, CAN_RDL0R_DATA2_Width)
/** @brief CAN payload byte 2 (`CANx_RDL0R.DATA2`) field mask alias @def CAN_RDL0R_DATA2 */
#define CAN_RDL0R_DATA2				CAN_RDL0R_DATA2_Msk

/** @brief CAN payload byte 3 (`CANx_RDL0R.DATA3`) field position @def CAN_RDL0R_DATA3_Pos */
#define CAN_RDL0R_DATA3_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 3 (`CANx_RDL0R.DATA3`) field width @def CAN_RDL0R_DATA3_Width */
#define CAN_RDL0R_DATA3_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 3 (`CANx_RDL0R.DATA3`) field mask @def CAN_RDL0R_DATA3_Msk */
#define CAN_RDL0R_DATA3_Msk			REG_FIELD_MASK(CAN_RDL0R_DATA3_Pos, CAN_RDL0R_DATA3_Width)
/** @brief CAN payload byte 3 (`CANx_RDL0R.DATA3`) field mask alias @def CAN_RDL0R_DATA3 */
#define CAN_RDL0R_DATA3				CAN_RDL0R_DATA3_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RDH0R
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 4 (`CANx_RDH0R.DATA4`) field position @def CAN_RDH0R_DATA4_Pos */
#define CAN_RDH0R_DATA4_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 4 (`CANx_RDH0R.DATA4`) field width @def CAN_RDH0R_DATA4_Width */
#define CAN_RDH0R_DATA4_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 4 (`CANx_RDH0R.DATA4`) field mask @def CAN_RDH0R_DATA4_Msk */
#define CAN_RDH0R_DATA4_Msk			REG_FIELD_MASK(CAN_RDH0R_DATA4_Pos, CAN_RDH0R_DATA4_Width)
/** @brief CAN payload byte 4 (`CANx_RDH0R.DATA4`) field mask alias @def CAN_RDH0R_DATA4 */
#define CAN_RDH0R_DATA4				CAN_RDH0R_DATA4_Msk

/** @brief CAN payload byte 5 (`CANx_RDH0R.DATA5`) field position @def CAN_RDH0R_DATA5_Pos */
#define CAN_RDH0R_DATA5_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 5 (`CANx_RDH0R.DATA5`) field width @def CAN_RDH0R_DATA5_Width */
#define CAN_RDH0R_DATA5_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 5 (`CANx_RDH0R.DATA5`) field mask @def CAN_RDH0R_DATA5_Msk */
#define CAN_RDH0R_DATA5_Msk			REG_FIELD_MASK(CAN_RDH0R_DATA5_Pos, CAN_RDH0R_DATA5_Width)
/** @brief CAN payload byte 5 (`CANx_RDH0R.DATA5`) field mask alias @def CAN_RDH0R_DATA5 */
#define CAN_RDH0R_DATA5				CAN_RDH0R_DATA5_Msk

/** @brief CAN payload byte 6 (`CANx_RDH0R.DATA6`) field position @def CAN_RDH0R_DATA6_Pos */
#define CAN_RDH0R_DATA6_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 6 (`CANx_RDH0R.DATA6`) field width @def CAN_RDH0R_DATA6_Width */
#define CAN_RDH0R_DATA6_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 6 (`CANx_RDH0R.DATA6`) field mask @def CAN_RDH0R_DATA6_Msk */
#define CAN_RDH0R_DATA6_Msk			REG_FIELD_MASK(CAN_RDH0R_DATA6_Pos, CAN_RDH0R_DATA6_Width)
/** @brief CAN payload byte 6 (`CANx_RDH0R.DATA6`) field mask alias @def CAN_RDH0R_DATA6 */
#define CAN_RDH0R_DATA6				CAN_RDH0R_DATA6_Msk

/** @brief CAN payload byte 7 (`CANx_RDH0R.DATA7`) field position @def CAN_RDH0R_DATA7_Pos */
#define CAN_RDH0R_DATA7_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 7 (`CANx_RDH0R.DATA7`) field width @def CAN_RDH0R_DATA7_Width */
#define CAN_RDH0R_DATA7_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 7 (`CANx_RDH0R.DATA7`) field mask @def CAN_RDH0R_DATA7_Msk */
#define CAN_RDH0R_DATA7_Msk			REG_FIELD_MASK(CAN_RDH0R_DATA7_Pos, CAN_RDH0R_DATA7_Width)
/** @brief CAN payload byte 7 (`CANx_RDH0R.DATA7`) field mask alias @def CAN_RDH0R_DATA7 */
#define CAN_RDH0R_DATA7				CAN_RDH0R_DATA7_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RI1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Remote-transmission-request frame selector (`CANx_RI1R.RTR`) bit position @def CAN_RI1R_RTR_Pos */
#define CAN_RI1R_RTR_Pos			((reg_bit_pos_t) 1U)
/** @brief Remote-transmission-request frame selector (`CANx_RI1R.RTR`) bit mask @def CAN_RI1R_RTR_Msk */
#define CAN_RI1R_RTR_Msk			REG_BIT_MASK(CAN_RI1R_RTR_Pos)
/** @brief Remote-transmission-request frame selector (`CANx_RI1R.RTR`) bit mask alias @def CAN_RI1R_RTR */
#define CAN_RI1R_RTR				CAN_RI1R_RTR_Msk

/** @brief Identifier-extension selector (`CANx_RI1R.IDE`) bit position @def CAN_RI1R_IDE_Pos */
#define CAN_RI1R_IDE_Pos			((reg_bit_pos_t) 2U)
/** @brief Identifier-extension selector (`CANx_RI1R.IDE`) bit mask @def CAN_RI1R_IDE_Msk */
#define CAN_RI1R_IDE_Msk			REG_BIT_MASK(CAN_RI1R_IDE_Pos)
/** @brief Identifier-extension selector (`CANx_RI1R.IDE`) bit mask alias @def CAN_RI1R_IDE */
#define CAN_RI1R_IDE				CAN_RI1R_IDE_Msk

/** @brief Extended-identifier portion (`CANx_RI1R.EXID`) field position @def CAN_RI1R_EXID_Pos */
#define CAN_RI1R_EXID_Pos			((reg_bit_pos_t) 3U)
/** @brief Extended-identifier portion (`CANx_RI1R.EXID`) field width @def CAN_RI1R_EXID_Width */
#define CAN_RI1R_EXID_Width			((reg_field_width_t) 18U)
/** @brief Extended-identifier portion (`CANx_RI1R.EXID`) field mask @def CAN_RI1R_EXID_Msk */
#define CAN_RI1R_EXID_Msk			REG_FIELD_MASK(CAN_RI1R_EXID_Pos, CAN_RI1R_EXID_Width)
/** @brief Extended-identifier portion (`CANx_RI1R.EXID`) field mask alias @def CAN_RI1R_EXID */
#define CAN_RI1R_EXID				CAN_RI1R_EXID_Msk

/** @brief Standard identifier or extended-identifier prefix (`CANx_RI1R.STID`) field position @def CAN_RI1R_STID_Pos */
#define CAN_RI1R_STID_Pos			((reg_bit_pos_t) 21U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_RI1R.STID`) field width @def CAN_RI1R_STID_Width */
#define CAN_RI1R_STID_Width			((reg_field_width_t) 11U)
/** @brief Standard identifier or extended-identifier prefix (`CANx_RI1R.STID`) field mask @def CAN_RI1R_STID_Msk */
#define CAN_RI1R_STID_Msk			REG_FIELD_MASK(CAN_RI1R_STID_Pos, CAN_RI1R_STID_Width)
/** @brief Standard identifier or extended-identifier prefix (`CANx_RI1R.STID`) field mask alias @def CAN_RI1R_STID */
#define CAN_RI1R_STID				CAN_RI1R_STID_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RDT1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Data length code (`CANx_RDT1R.DLC`) field position @def CAN_RDT1R_DLC_Pos */
#define CAN_RDT1R_DLC_Pos			((reg_bit_pos_t) 0U)
/** @brief Data length code (`CANx_RDT1R.DLC`) field width @def CAN_RDT1R_DLC_Width */
#define CAN_RDT1R_DLC_Width			((reg_field_width_t) 4U)
/** @brief Data length code (`CANx_RDT1R.DLC`) field mask @def CAN_RDT1R_DLC_Msk */
#define CAN_RDT1R_DLC_Msk			REG_FIELD_MASK(CAN_RDT1R_DLC_Pos, CAN_RDT1R_DLC_Width)
/** @brief Data length code (`CANx_RDT1R.DLC`) field mask alias @def CAN_RDT1R_DLC */
#define CAN_RDT1R_DLC				CAN_RDT1R_DLC_Msk

/** @brief Filter match index (`CANx_RDT1R.FMI`) field position @def CAN_RDT1R_FMI_Pos */
#define CAN_RDT1R_FMI_Pos			((reg_bit_pos_t) 8U)
/** @brief Filter match index (`CANx_RDT1R.FMI`) field width @def CAN_RDT1R_FMI_Width */
#define CAN_RDT1R_FMI_Width			((reg_field_width_t) 8U)
/** @brief Filter match index (`CANx_RDT1R.FMI`) field mask @def CAN_RDT1R_FMI_Msk */
#define CAN_RDT1R_FMI_Msk			REG_FIELD_MASK(CAN_RDT1R_FMI_Pos, CAN_RDT1R_FMI_Width)
/** @brief Filter match index (`CANx_RDT1R.FMI`) field mask alias @def CAN_RDT1R_FMI */
#define CAN_RDT1R_FMI				CAN_RDT1R_FMI_Msk

/** @brief Message timestamp (`CANx_RDT1R.TIME`) field position @def CAN_RDT1R_TIME_Pos */
#define CAN_RDT1R_TIME_Pos			((reg_bit_pos_t) 16U)
/** @brief Message timestamp (`CANx_RDT1R.TIME`) field width @def CAN_RDT1R_TIME_Width */
#define CAN_RDT1R_TIME_Width		((reg_field_width_t) 16U)
/** @brief Message timestamp (`CANx_RDT1R.TIME`) field mask @def CAN_RDT1R_TIME_Msk */
#define CAN_RDT1R_TIME_Msk			REG_FIELD_MASK(CAN_RDT1R_TIME_Pos, CAN_RDT1R_TIME_Width)
/** @brief Message timestamp (`CANx_RDT1R.TIME`) field mask alias @def CAN_RDT1R_TIME */
#define CAN_RDT1R_TIME				CAN_RDT1R_TIME_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RDL1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 0 (`CANx_RDL1R.DATA0`) field position @def CAN_RDL1R_DATA0_Pos */
#define CAN_RDL1R_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 0 (`CANx_RDL1R.DATA0`) field width @def CAN_RDL1R_DATA0_Width */
#define CAN_RDL1R_DATA0_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 0 (`CANx_RDL1R.DATA0`) field mask @def CAN_RDL1R_DATA0_Msk */
#define CAN_RDL1R_DATA0_Msk			REG_FIELD_MASK(CAN_RDL1R_DATA0_Pos, CAN_RDL1R_DATA0_Width)
/** @brief CAN payload byte 0 (`CANx_RDL1R.DATA0`) field mask alias @def CAN_RDL1R_DATA0 */
#define CAN_RDL1R_DATA0				CAN_RDL1R_DATA0_Msk

/** @brief CAN payload byte 1 (`CANx_RDL1R.DATA1`) field position @def CAN_RDL1R_DATA1_Pos */
#define CAN_RDL1R_DATA1_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 1 (`CANx_RDL1R.DATA1`) field width @def CAN_RDL1R_DATA1_Width */
#define CAN_RDL1R_DATA1_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 1 (`CANx_RDL1R.DATA1`) field mask @def CAN_RDL1R_DATA1_Msk */
#define CAN_RDL1R_DATA1_Msk			REG_FIELD_MASK(CAN_RDL1R_DATA1_Pos, CAN_RDL1R_DATA1_Width)
/** @brief CAN payload byte 1 (`CANx_RDL1R.DATA1`) field mask alias @def CAN_RDL1R_DATA1 */
#define CAN_RDL1R_DATA1				CAN_RDL1R_DATA1_Msk

/** @brief CAN payload byte 2 (`CANx_RDL1R.DATA2`) field position @def CAN_RDL1R_DATA2_Pos */
#define CAN_RDL1R_DATA2_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 2 (`CANx_RDL1R.DATA2`) field width @def CAN_RDL1R_DATA2_Width */
#define CAN_RDL1R_DATA2_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 2 (`CANx_RDL1R.DATA2`) field mask @def CAN_RDL1R_DATA2_Msk */
#define CAN_RDL1R_DATA2_Msk			REG_FIELD_MASK(CAN_RDL1R_DATA2_Pos, CAN_RDL1R_DATA2_Width)
/** @brief CAN payload byte 2 (`CANx_RDL1R.DATA2`) field mask alias @def CAN_RDL1R_DATA2 */
#define CAN_RDL1R_DATA2				CAN_RDL1R_DATA2_Msk

/** @brief CAN payload byte 3 (`CANx_RDL1R.DATA3`) field position @def CAN_RDL1R_DATA3_Pos */
#define CAN_RDL1R_DATA3_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 3 (`CANx_RDL1R.DATA3`) field width @def CAN_RDL1R_DATA3_Width */
#define CAN_RDL1R_DATA3_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 3 (`CANx_RDL1R.DATA3`) field mask @def CAN_RDL1R_DATA3_Msk */
#define CAN_RDL1R_DATA3_Msk			REG_FIELD_MASK(CAN_RDL1R_DATA3_Pos, CAN_RDL1R_DATA3_Width)
/** @brief CAN payload byte 3 (`CANx_RDL1R.DATA3`) field mask alias @def CAN_RDL1R_DATA3 */
#define CAN_RDL1R_DATA3				CAN_RDL1R_DATA3_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_RDH1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief CAN payload byte 4 (`CANx_RDH1R.DATA4`) field position @def CAN_RDH1R_DATA4_Pos */
#define CAN_RDH1R_DATA4_Pos			((reg_bit_pos_t) 0U)
/** @brief CAN payload byte 4 (`CANx_RDH1R.DATA4`) field width @def CAN_RDH1R_DATA4_Width */
#define CAN_RDH1R_DATA4_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 4 (`CANx_RDH1R.DATA4`) field mask @def CAN_RDH1R_DATA4_Msk */
#define CAN_RDH1R_DATA4_Msk			REG_FIELD_MASK(CAN_RDH1R_DATA4_Pos, CAN_RDH1R_DATA4_Width)
/** @brief CAN payload byte 4 (`CANx_RDH1R.DATA4`) field mask alias @def CAN_RDH1R_DATA4 */
#define CAN_RDH1R_DATA4				CAN_RDH1R_DATA4_Msk

/** @brief CAN payload byte 5 (`CANx_RDH1R.DATA5`) field position @def CAN_RDH1R_DATA5_Pos */
#define CAN_RDH1R_DATA5_Pos			((reg_bit_pos_t) 8U)
/** @brief CAN payload byte 5 (`CANx_RDH1R.DATA5`) field width @def CAN_RDH1R_DATA5_Width */
#define CAN_RDH1R_DATA5_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 5 (`CANx_RDH1R.DATA5`) field mask @def CAN_RDH1R_DATA5_Msk */
#define CAN_RDH1R_DATA5_Msk			REG_FIELD_MASK(CAN_RDH1R_DATA5_Pos, CAN_RDH1R_DATA5_Width)
/** @brief CAN payload byte 5 (`CANx_RDH1R.DATA5`) field mask alias @def CAN_RDH1R_DATA5 */
#define CAN_RDH1R_DATA5				CAN_RDH1R_DATA5_Msk

/** @brief CAN payload byte 6 (`CANx_RDH1R.DATA6`) field position @def CAN_RDH1R_DATA6_Pos */
#define CAN_RDH1R_DATA6_Pos			((reg_bit_pos_t) 16U)
/** @brief CAN payload byte 6 (`CANx_RDH1R.DATA6`) field width @def CAN_RDH1R_DATA6_Width */
#define CAN_RDH1R_DATA6_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 6 (`CANx_RDH1R.DATA6`) field mask @def CAN_RDH1R_DATA6_Msk */
#define CAN_RDH1R_DATA6_Msk			REG_FIELD_MASK(CAN_RDH1R_DATA6_Pos, CAN_RDH1R_DATA6_Width)
/** @brief CAN payload byte 6 (`CANx_RDH1R.DATA6`) field mask alias @def CAN_RDH1R_DATA6 */
#define CAN_RDH1R_DATA6				CAN_RDH1R_DATA6_Msk

/** @brief CAN payload byte 7 (`CANx_RDH1R.DATA7`) field position @def CAN_RDH1R_DATA7_Pos */
#define CAN_RDH1R_DATA7_Pos			((reg_bit_pos_t) 24U)
/** @brief CAN payload byte 7 (`CANx_RDH1R.DATA7`) field width @def CAN_RDH1R_DATA7_Width */
#define CAN_RDH1R_DATA7_Width		((reg_field_width_t) 8U)
/** @brief CAN payload byte 7 (`CANx_RDH1R.DATA7`) field mask @def CAN_RDH1R_DATA7_Msk */
#define CAN_RDH1R_DATA7_Msk			REG_FIELD_MASK(CAN_RDH1R_DATA7_Pos, CAN_RDH1R_DATA7_Width)
/** @brief CAN payload byte 7 (`CANx_RDH1R.DATA7`) field mask alias @def CAN_RDH1R_DATA7 */
#define CAN_RDH1R_DATA7				CAN_RDH1R_DATA7_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_FMR
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter initialization-mode request (`CANx_FMR.FINIT`) bit position @def CAN_FMR_FINIT_Pos */
#define CAN_FMR_FINIT_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter initialization-mode request (`CANx_FMR.FINIT`) bit mask @def CAN_FMR_FINIT_Msk */
#define CAN_FMR_FINIT_Msk			REG_BIT_MASK(CAN_FMR_FINIT_Pos)
/** @brief Acceptance-filter initialization-mode request (`CANx_FMR.FINIT`) bit mask alias @def CAN_FMR_FINIT */
#define CAN_FMR_FINIT				CAN_FMR_FINIT_Msk

/**
 * @brief Connectivity-line CAN2 filter-bank split selector (`CANx_FMR.CAN2SB`) field position
 * @def CAN_FMR_CAN2SB_Pos
 * @warning STM32F103C8T6 has one CAN controller; bits `13:8` are reserved and this compatibility symbol must not be used
 */
#define CAN_FMR_CAN2SB_Pos			((reg_bit_pos_t) 8U)
/**
 * @brief Connectivity-line CAN2 filter-bank split selector (`CANx_FMR.CAN2SB`) field width
 * @def CAN_FMR_CAN2SB_Width
 * @warning STM32F103C8T6 has one CAN controller; bits `13:8` are reserved and this compatibility symbol must not be used
 */
#define CAN_FMR_CAN2SB_Width		((reg_field_width_t) 6U)
/**
 * @brief Connectivity-line CAN2 filter-bank split selector (`CANx_FMR.CAN2SB`) field mask
 * @def CAN_FMR_CAN2SB_Msk
 * @warning STM32F103C8T6 has one CAN controller; bits `13:8` are reserved and this compatibility symbol must not be used
 */
#define CAN_FMR_CAN2SB_Msk			REG_FIELD_MASK(CAN_FMR_CAN2SB_Pos, CAN_FMR_CAN2SB_Width)
/**
 * @brief Connectivity-line CAN2 filter-bank split selector (`CANx_FMR.CAN2SB`) field mask alias
 * @def CAN_FMR_CAN2SB
 * @warning STM32F103C8T6 has one CAN controller; bits `13:8` are reserved and this compatibility symbol must not be used
 */
#define CAN_FMR_CAN2SB				CAN_FMR_CAN2SB_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_FM1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter identifier-list-mode selectors (`CANx_FM1R.FBM`) field position @def CAN_FM1R_FBM_Pos */
#define CAN_FM1R_FBM_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter identifier-list-mode selectors (`CANx_FM1R.FBM`) field width @def CAN_FM1R_FBM_Width */
#define CAN_FM1R_FBM_Width			((reg_field_width_t) 14U)
/** @brief Acceptance-filter identifier-list-mode selectors (`CANx_FM1R.FBM`) field mask @def CAN_FM1R_FBM_Msk */
#define CAN_FM1R_FBM_Msk			REG_FIELD_MASK(CAN_FM1R_FBM_Pos, CAN_FM1R_FBM_Width)
/** @brief Acceptance-filter identifier-list-mode selectors (`CANx_FM1R.FBM`) field mask alias @def CAN_FM1R_FBM */
#define CAN_FM1R_FBM				CAN_FM1R_FBM_Msk

/** @brief Acceptance-filter bank 0 identifier-list-mode selector (`CANx_FM1R.FBM0`) bit position @def CAN_FM1R_FBM0_Pos */
#define CAN_FM1R_FBM0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 0 identifier-list-mode selector (`CANx_FM1R.FBM0`) bit mask @def CAN_FM1R_FBM0_Msk */
#define CAN_FM1R_FBM0_Msk			REG_BIT_MASK(CAN_FM1R_FBM0_Pos)
/** @brief Acceptance-filter bank 0 identifier-list-mode selector (`CANx_FM1R.FBM0`) bit mask alias @def CAN_FM1R_FBM0 */
#define CAN_FM1R_FBM0				CAN_FM1R_FBM0_Msk

/** @brief Acceptance-filter bank 1 identifier-list-mode selector (`CANx_FM1R.FBM1`) bit position @def CAN_FM1R_FBM1_Pos */
#define CAN_FM1R_FBM1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 1 identifier-list-mode selector (`CANx_FM1R.FBM1`) bit mask @def CAN_FM1R_FBM1_Msk */
#define CAN_FM1R_FBM1_Msk			REG_BIT_MASK(CAN_FM1R_FBM1_Pos)
/** @brief Acceptance-filter bank 1 identifier-list-mode selector (`CANx_FM1R.FBM1`) bit mask alias @def CAN_FM1R_FBM1 */
#define CAN_FM1R_FBM1				CAN_FM1R_FBM1_Msk

/** @brief Acceptance-filter bank 2 identifier-list-mode selector (`CANx_FM1R.FBM2`) bit position @def CAN_FM1R_FBM2_Pos */
#define CAN_FM1R_FBM2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 2 identifier-list-mode selector (`CANx_FM1R.FBM2`) bit mask @def CAN_FM1R_FBM2_Msk */
#define CAN_FM1R_FBM2_Msk			REG_BIT_MASK(CAN_FM1R_FBM2_Pos)
/** @brief Acceptance-filter bank 2 identifier-list-mode selector (`CANx_FM1R.FBM2`) bit mask alias @def CAN_FM1R_FBM2 */
#define CAN_FM1R_FBM2				CAN_FM1R_FBM2_Msk

/** @brief Acceptance-filter bank 3 identifier-list-mode selector (`CANx_FM1R.FBM3`) bit position @def CAN_FM1R_FBM3_Pos */
#define CAN_FM1R_FBM3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 3 identifier-list-mode selector (`CANx_FM1R.FBM3`) bit mask @def CAN_FM1R_FBM3_Msk */
#define CAN_FM1R_FBM3_Msk			REG_BIT_MASK(CAN_FM1R_FBM3_Pos)
/** @brief Acceptance-filter bank 3 identifier-list-mode selector (`CANx_FM1R.FBM3`) bit mask alias @def CAN_FM1R_FBM3 */
#define CAN_FM1R_FBM3				CAN_FM1R_FBM3_Msk

/** @brief Acceptance-filter bank 4 identifier-list-mode selector (`CANx_FM1R.FBM4`) bit position @def CAN_FM1R_FBM4_Pos */
#define CAN_FM1R_FBM4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 4 identifier-list-mode selector (`CANx_FM1R.FBM4`) bit mask @def CAN_FM1R_FBM4_Msk */
#define CAN_FM1R_FBM4_Msk			REG_BIT_MASK(CAN_FM1R_FBM4_Pos)
/** @brief Acceptance-filter bank 4 identifier-list-mode selector (`CANx_FM1R.FBM4`) bit mask alias @def CAN_FM1R_FBM4 */
#define CAN_FM1R_FBM4				CAN_FM1R_FBM4_Msk

/** @brief Acceptance-filter bank 5 identifier-list-mode selector (`CANx_FM1R.FBM5`) bit position @def CAN_FM1R_FBM5_Pos */
#define CAN_FM1R_FBM5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 5 identifier-list-mode selector (`CANx_FM1R.FBM5`) bit mask @def CAN_FM1R_FBM5_Msk */
#define CAN_FM1R_FBM5_Msk			REG_BIT_MASK(CAN_FM1R_FBM5_Pos)
/** @brief Acceptance-filter bank 5 identifier-list-mode selector (`CANx_FM1R.FBM5`) bit mask alias @def CAN_FM1R_FBM5 */
#define CAN_FM1R_FBM5				CAN_FM1R_FBM5_Msk

/** @brief Acceptance-filter bank 6 identifier-list-mode selector (`CANx_FM1R.FBM6`) bit position @def CAN_FM1R_FBM6_Pos */
#define CAN_FM1R_FBM6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 6 identifier-list-mode selector (`CANx_FM1R.FBM6`) bit mask @def CAN_FM1R_FBM6_Msk */
#define CAN_FM1R_FBM6_Msk			REG_BIT_MASK(CAN_FM1R_FBM6_Pos)
/** @brief Acceptance-filter bank 6 identifier-list-mode selector (`CANx_FM1R.FBM6`) bit mask alias @def CAN_FM1R_FBM6 */
#define CAN_FM1R_FBM6				CAN_FM1R_FBM6_Msk

/** @brief Acceptance-filter bank 7 identifier-list-mode selector (`CANx_FM1R.FBM7`) bit position @def CAN_FM1R_FBM7_Pos */
#define CAN_FM1R_FBM7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 7 identifier-list-mode selector (`CANx_FM1R.FBM7`) bit mask @def CAN_FM1R_FBM7_Msk */
#define CAN_FM1R_FBM7_Msk			REG_BIT_MASK(CAN_FM1R_FBM7_Pos)
/** @brief Acceptance-filter bank 7 identifier-list-mode selector (`CANx_FM1R.FBM7`) bit mask alias @def CAN_FM1R_FBM7 */
#define CAN_FM1R_FBM7				CAN_FM1R_FBM7_Msk

/** @brief Acceptance-filter bank 8 identifier-list-mode selector (`CANx_FM1R.FBM8`) bit position @def CAN_FM1R_FBM8_Pos */
#define CAN_FM1R_FBM8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 8 identifier-list-mode selector (`CANx_FM1R.FBM8`) bit mask @def CAN_FM1R_FBM8_Msk */
#define CAN_FM1R_FBM8_Msk			REG_BIT_MASK(CAN_FM1R_FBM8_Pos)
/** @brief Acceptance-filter bank 8 identifier-list-mode selector (`CANx_FM1R.FBM8`) bit mask alias @def CAN_FM1R_FBM8 */
#define CAN_FM1R_FBM8				CAN_FM1R_FBM8_Msk

/** @brief Acceptance-filter bank 9 identifier-list-mode selector (`CANx_FM1R.FBM9`) bit position @def CAN_FM1R_FBM9_Pos */
#define CAN_FM1R_FBM9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 9 identifier-list-mode selector (`CANx_FM1R.FBM9`) bit mask @def CAN_FM1R_FBM9_Msk */
#define CAN_FM1R_FBM9_Msk			REG_BIT_MASK(CAN_FM1R_FBM9_Pos)
/** @brief Acceptance-filter bank 9 identifier-list-mode selector (`CANx_FM1R.FBM9`) bit mask alias @def CAN_FM1R_FBM9 */
#define CAN_FM1R_FBM9				CAN_FM1R_FBM9_Msk

/** @brief Acceptance-filter bank 10 identifier-list-mode selector (`CANx_FM1R.FBM10`) bit position @def CAN_FM1R_FBM10_Pos */
#define CAN_FM1R_FBM10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 10 identifier-list-mode selector (`CANx_FM1R.FBM10`) bit mask @def CAN_FM1R_FBM10_Msk */
#define CAN_FM1R_FBM10_Msk			REG_BIT_MASK(CAN_FM1R_FBM10_Pos)
/** @brief Acceptance-filter bank 10 identifier-list-mode selector (`CANx_FM1R.FBM10`) bit mask alias @def CAN_FM1R_FBM10 */
#define CAN_FM1R_FBM10				CAN_FM1R_FBM10_Msk

/** @brief Acceptance-filter bank 11 identifier-list-mode selector (`CANx_FM1R.FBM11`) bit position @def CAN_FM1R_FBM11_Pos */
#define CAN_FM1R_FBM11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 11 identifier-list-mode selector (`CANx_FM1R.FBM11`) bit mask @def CAN_FM1R_FBM11_Msk */
#define CAN_FM1R_FBM11_Msk			REG_BIT_MASK(CAN_FM1R_FBM11_Pos)
/** @brief Acceptance-filter bank 11 identifier-list-mode selector (`CANx_FM1R.FBM11`) bit mask alias @def CAN_FM1R_FBM11 */
#define CAN_FM1R_FBM11				CAN_FM1R_FBM11_Msk

/** @brief Acceptance-filter bank 12 identifier-list-mode selector (`CANx_FM1R.FBM12`) bit position @def CAN_FM1R_FBM12_Pos */
#define CAN_FM1R_FBM12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 12 identifier-list-mode selector (`CANx_FM1R.FBM12`) bit mask @def CAN_FM1R_FBM12_Msk */
#define CAN_FM1R_FBM12_Msk			REG_BIT_MASK(CAN_FM1R_FBM12_Pos)
/** @brief Acceptance-filter bank 12 identifier-list-mode selector (`CANx_FM1R.FBM12`) bit mask alias @def CAN_FM1R_FBM12 */
#define CAN_FM1R_FBM12				CAN_FM1R_FBM12_Msk

/** @brief Acceptance-filter bank 13 identifier-list-mode selector (`CANx_FM1R.FBM13`) bit position @def CAN_FM1R_FBM13_Pos */
#define CAN_FM1R_FBM13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 13 identifier-list-mode selector (`CANx_FM1R.FBM13`) bit mask @def CAN_FM1R_FBM13_Msk */
#define CAN_FM1R_FBM13_Msk			REG_BIT_MASK(CAN_FM1R_FBM13_Pos)
/** @brief Acceptance-filter bank 13 identifier-list-mode selector (`CANx_FM1R.FBM13`) bit mask alias @def CAN_FM1R_FBM13 */
#define CAN_FM1R_FBM13				CAN_FM1R_FBM13_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_FS1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter 32-bit-scale selectors (`CANx_FS1R.FSC`) field position @def CAN_FS1R_FSC_Pos */
#define CAN_FS1R_FSC_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter 32-bit-scale selectors (`CANx_FS1R.FSC`) field width @def CAN_FS1R_FSC_Width */
#define CAN_FS1R_FSC_Width			((reg_field_width_t) 14U)
/** @brief Acceptance-filter 32-bit-scale selectors (`CANx_FS1R.FSC`) field mask @def CAN_FS1R_FSC_Msk */
#define CAN_FS1R_FSC_Msk			REG_FIELD_MASK(CAN_FS1R_FSC_Pos, CAN_FS1R_FSC_Width)
/** @brief Acceptance-filter 32-bit-scale selectors (`CANx_FS1R.FSC`) field mask alias @def CAN_FS1R_FSC */
#define CAN_FS1R_FSC				CAN_FS1R_FSC_Msk

/** @brief Acceptance-filter bank 0 32-bit-scale selector (`CANx_FS1R.FSC0`) bit position @def CAN_FS1R_FSC0_Pos */
#define CAN_FS1R_FSC0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 0 32-bit-scale selector (`CANx_FS1R.FSC0`) bit mask @def CAN_FS1R_FSC0_Msk */
#define CAN_FS1R_FSC0_Msk			REG_BIT_MASK(CAN_FS1R_FSC0_Pos)
/** @brief Acceptance-filter bank 0 32-bit-scale selector (`CANx_FS1R.FSC0`) bit mask alias @def CAN_FS1R_FSC0 */
#define CAN_FS1R_FSC0				CAN_FS1R_FSC0_Msk

/** @brief Acceptance-filter bank 1 32-bit-scale selector (`CANx_FS1R.FSC1`) bit position @def CAN_FS1R_FSC1_Pos */
#define CAN_FS1R_FSC1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 1 32-bit-scale selector (`CANx_FS1R.FSC1`) bit mask @def CAN_FS1R_FSC1_Msk */
#define CAN_FS1R_FSC1_Msk			REG_BIT_MASK(CAN_FS1R_FSC1_Pos)
/** @brief Acceptance-filter bank 1 32-bit-scale selector (`CANx_FS1R.FSC1`) bit mask alias @def CAN_FS1R_FSC1 */
#define CAN_FS1R_FSC1				CAN_FS1R_FSC1_Msk

/** @brief Acceptance-filter bank 2 32-bit-scale selector (`CANx_FS1R.FSC2`) bit position @def CAN_FS1R_FSC2_Pos */
#define CAN_FS1R_FSC2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 2 32-bit-scale selector (`CANx_FS1R.FSC2`) bit mask @def CAN_FS1R_FSC2_Msk */
#define CAN_FS1R_FSC2_Msk			REG_BIT_MASK(CAN_FS1R_FSC2_Pos)
/** @brief Acceptance-filter bank 2 32-bit-scale selector (`CANx_FS1R.FSC2`) bit mask alias @def CAN_FS1R_FSC2 */
#define CAN_FS1R_FSC2				CAN_FS1R_FSC2_Msk

/** @brief Acceptance-filter bank 3 32-bit-scale selector (`CANx_FS1R.FSC3`) bit position @def CAN_FS1R_FSC3_Pos */
#define CAN_FS1R_FSC3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 3 32-bit-scale selector (`CANx_FS1R.FSC3`) bit mask @def CAN_FS1R_FSC3_Msk */
#define CAN_FS1R_FSC3_Msk			REG_BIT_MASK(CAN_FS1R_FSC3_Pos)
/** @brief Acceptance-filter bank 3 32-bit-scale selector (`CANx_FS1R.FSC3`) bit mask alias @def CAN_FS1R_FSC3 */
#define CAN_FS1R_FSC3				CAN_FS1R_FSC3_Msk

/** @brief Acceptance-filter bank 4 32-bit-scale selector (`CANx_FS1R.FSC4`) bit position @def CAN_FS1R_FSC4_Pos */
#define CAN_FS1R_FSC4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 4 32-bit-scale selector (`CANx_FS1R.FSC4`) bit mask @def CAN_FS1R_FSC4_Msk */
#define CAN_FS1R_FSC4_Msk			REG_BIT_MASK(CAN_FS1R_FSC4_Pos)
/** @brief Acceptance-filter bank 4 32-bit-scale selector (`CANx_FS1R.FSC4`) bit mask alias @def CAN_FS1R_FSC4 */
#define CAN_FS1R_FSC4				CAN_FS1R_FSC4_Msk

/** @brief Acceptance-filter bank 5 32-bit-scale selector (`CANx_FS1R.FSC5`) bit position @def CAN_FS1R_FSC5_Pos */
#define CAN_FS1R_FSC5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 5 32-bit-scale selector (`CANx_FS1R.FSC5`) bit mask @def CAN_FS1R_FSC5_Msk */
#define CAN_FS1R_FSC5_Msk			REG_BIT_MASK(CAN_FS1R_FSC5_Pos)
/** @brief Acceptance-filter bank 5 32-bit-scale selector (`CANx_FS1R.FSC5`) bit mask alias @def CAN_FS1R_FSC5 */
#define CAN_FS1R_FSC5				CAN_FS1R_FSC5_Msk

/** @brief Acceptance-filter bank 6 32-bit-scale selector (`CANx_FS1R.FSC6`) bit position @def CAN_FS1R_FSC6_Pos */
#define CAN_FS1R_FSC6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 6 32-bit-scale selector (`CANx_FS1R.FSC6`) bit mask @def CAN_FS1R_FSC6_Msk */
#define CAN_FS1R_FSC6_Msk			REG_BIT_MASK(CAN_FS1R_FSC6_Pos)
/** @brief Acceptance-filter bank 6 32-bit-scale selector (`CANx_FS1R.FSC6`) bit mask alias @def CAN_FS1R_FSC6 */
#define CAN_FS1R_FSC6				CAN_FS1R_FSC6_Msk

/** @brief Acceptance-filter bank 7 32-bit-scale selector (`CANx_FS1R.FSC7`) bit position @def CAN_FS1R_FSC7_Pos */
#define CAN_FS1R_FSC7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 7 32-bit-scale selector (`CANx_FS1R.FSC7`) bit mask @def CAN_FS1R_FSC7_Msk */
#define CAN_FS1R_FSC7_Msk			REG_BIT_MASK(CAN_FS1R_FSC7_Pos)
/** @brief Acceptance-filter bank 7 32-bit-scale selector (`CANx_FS1R.FSC7`) bit mask alias @def CAN_FS1R_FSC7 */
#define CAN_FS1R_FSC7				CAN_FS1R_FSC7_Msk

/** @brief Acceptance-filter bank 8 32-bit-scale selector (`CANx_FS1R.FSC8`) bit position @def CAN_FS1R_FSC8_Pos */
#define CAN_FS1R_FSC8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 8 32-bit-scale selector (`CANx_FS1R.FSC8`) bit mask @def CAN_FS1R_FSC8_Msk */
#define CAN_FS1R_FSC8_Msk			REG_BIT_MASK(CAN_FS1R_FSC8_Pos)
/** @brief Acceptance-filter bank 8 32-bit-scale selector (`CANx_FS1R.FSC8`) bit mask alias @def CAN_FS1R_FSC8 */
#define CAN_FS1R_FSC8				CAN_FS1R_FSC8_Msk

/** @brief Acceptance-filter bank 9 32-bit-scale selector (`CANx_FS1R.FSC9`) bit position @def CAN_FS1R_FSC9_Pos */
#define CAN_FS1R_FSC9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 9 32-bit-scale selector (`CANx_FS1R.FSC9`) bit mask @def CAN_FS1R_FSC9_Msk */
#define CAN_FS1R_FSC9_Msk			REG_BIT_MASK(CAN_FS1R_FSC9_Pos)
/** @brief Acceptance-filter bank 9 32-bit-scale selector (`CANx_FS1R.FSC9`) bit mask alias @def CAN_FS1R_FSC9 */
#define CAN_FS1R_FSC9				CAN_FS1R_FSC9_Msk

/** @brief Acceptance-filter bank 10 32-bit-scale selector (`CANx_FS1R.FSC10`) bit position @def CAN_FS1R_FSC10_Pos */
#define CAN_FS1R_FSC10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 10 32-bit-scale selector (`CANx_FS1R.FSC10`) bit mask @def CAN_FS1R_FSC10_Msk */
#define CAN_FS1R_FSC10_Msk			REG_BIT_MASK(CAN_FS1R_FSC10_Pos)
/** @brief Acceptance-filter bank 10 32-bit-scale selector (`CANx_FS1R.FSC10`) bit mask alias @def CAN_FS1R_FSC10 */
#define CAN_FS1R_FSC10				CAN_FS1R_FSC10_Msk

/** @brief Acceptance-filter bank 11 32-bit-scale selector (`CANx_FS1R.FSC11`) bit position @def CAN_FS1R_FSC11_Pos */
#define CAN_FS1R_FSC11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 11 32-bit-scale selector (`CANx_FS1R.FSC11`) bit mask @def CAN_FS1R_FSC11_Msk */
#define CAN_FS1R_FSC11_Msk			REG_BIT_MASK(CAN_FS1R_FSC11_Pos)
/** @brief Acceptance-filter bank 11 32-bit-scale selector (`CANx_FS1R.FSC11`) bit mask alias @def CAN_FS1R_FSC11 */
#define CAN_FS1R_FSC11				CAN_FS1R_FSC11_Msk

/** @brief Acceptance-filter bank 12 32-bit-scale selector (`CANx_FS1R.FSC12`) bit position @def CAN_FS1R_FSC12_Pos */
#define CAN_FS1R_FSC12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 12 32-bit-scale selector (`CANx_FS1R.FSC12`) bit mask @def CAN_FS1R_FSC12_Msk */
#define CAN_FS1R_FSC12_Msk			REG_BIT_MASK(CAN_FS1R_FSC12_Pos)
/** @brief Acceptance-filter bank 12 32-bit-scale selector (`CANx_FS1R.FSC12`) bit mask alias @def CAN_FS1R_FSC12 */
#define CAN_FS1R_FSC12				CAN_FS1R_FSC12_Msk

/** @brief Acceptance-filter bank 13 32-bit-scale selector (`CANx_FS1R.FSC13`) bit position @def CAN_FS1R_FSC13_Pos */
#define CAN_FS1R_FSC13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 13 32-bit-scale selector (`CANx_FS1R.FSC13`) bit mask @def CAN_FS1R_FSC13_Msk */
#define CAN_FS1R_FSC13_Msk			REG_BIT_MASK(CAN_FS1R_FSC13_Pos)
/** @brief Acceptance-filter bank 13 32-bit-scale selector (`CANx_FS1R.FSC13`) bit mask alias @def CAN_FS1R_FSC13 */
#define CAN_FS1R_FSC13				CAN_FS1R_FSC13_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_FFA1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter FIFO-assignment selectors (`CANx_FFA1R.FFA`) field position @def CAN_FFA1R_FFA_Pos */
#define CAN_FFA1R_FFA_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter FIFO-assignment selectors (`CANx_FFA1R.FFA`) field width @def CAN_FFA1R_FFA_Width */
#define CAN_FFA1R_FFA_Width			((reg_field_width_t) 14U)
/** @brief Acceptance-filter FIFO-assignment selectors (`CANx_FFA1R.FFA`) field mask @def CAN_FFA1R_FFA_Msk */
#define CAN_FFA1R_FFA_Msk			REG_FIELD_MASK(CAN_FFA1R_FFA_Pos, CAN_FFA1R_FFA_Width)
/** @brief Acceptance-filter FIFO-assignment selectors (`CANx_FFA1R.FFA`) field mask alias @def CAN_FFA1R_FFA */
#define CAN_FFA1R_FFA				CAN_FFA1R_FFA_Msk

/** @brief Acceptance-filter bank 0 FIFO-assignment selector (`CANx_FFA1R.FFA0`) bit position @def CAN_FFA1R_FFA0_Pos */
#define CAN_FFA1R_FFA0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 0 FIFO-assignment selector (`CANx_FFA1R.FFA0`) bit mask @def CAN_FFA1R_FFA0_Msk */
#define CAN_FFA1R_FFA0_Msk			REG_BIT_MASK(CAN_FFA1R_FFA0_Pos)
/** @brief Acceptance-filter bank 0 FIFO-assignment selector (`CANx_FFA1R.FFA0`) bit mask alias @def CAN_FFA1R_FFA0 */
#define CAN_FFA1R_FFA0				CAN_FFA1R_FFA0_Msk

/** @brief Acceptance-filter bank 1 FIFO-assignment selector (`CANx_FFA1R.FFA1`) bit position @def CAN_FFA1R_FFA1_Pos */
#define CAN_FFA1R_FFA1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 1 FIFO-assignment selector (`CANx_FFA1R.FFA1`) bit mask @def CAN_FFA1R_FFA1_Msk */
#define CAN_FFA1R_FFA1_Msk			REG_BIT_MASK(CAN_FFA1R_FFA1_Pos)
/** @brief Acceptance-filter bank 1 FIFO-assignment selector (`CANx_FFA1R.FFA1`) bit mask alias @def CAN_FFA1R_FFA1 */
#define CAN_FFA1R_FFA1				CAN_FFA1R_FFA1_Msk

/** @brief Acceptance-filter bank 2 FIFO-assignment selector (`CANx_FFA1R.FFA2`) bit position @def CAN_FFA1R_FFA2_Pos */
#define CAN_FFA1R_FFA2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 2 FIFO-assignment selector (`CANx_FFA1R.FFA2`) bit mask @def CAN_FFA1R_FFA2_Msk */
#define CAN_FFA1R_FFA2_Msk			REG_BIT_MASK(CAN_FFA1R_FFA2_Pos)
/** @brief Acceptance-filter bank 2 FIFO-assignment selector (`CANx_FFA1R.FFA2`) bit mask alias @def CAN_FFA1R_FFA2 */
#define CAN_FFA1R_FFA2				CAN_FFA1R_FFA2_Msk

/** @brief Acceptance-filter bank 3 FIFO-assignment selector (`CANx_FFA1R.FFA3`) bit position @def CAN_FFA1R_FFA3_Pos */
#define CAN_FFA1R_FFA3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 3 FIFO-assignment selector (`CANx_FFA1R.FFA3`) bit mask @def CAN_FFA1R_FFA3_Msk */
#define CAN_FFA1R_FFA3_Msk			REG_BIT_MASK(CAN_FFA1R_FFA3_Pos)
/** @brief Acceptance-filter bank 3 FIFO-assignment selector (`CANx_FFA1R.FFA3`) bit mask alias @def CAN_FFA1R_FFA3 */
#define CAN_FFA1R_FFA3				CAN_FFA1R_FFA3_Msk

/** @brief Acceptance-filter bank 4 FIFO-assignment selector (`CANx_FFA1R.FFA4`) bit position @def CAN_FFA1R_FFA4_Pos */
#define CAN_FFA1R_FFA4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 4 FIFO-assignment selector (`CANx_FFA1R.FFA4`) bit mask @def CAN_FFA1R_FFA4_Msk */
#define CAN_FFA1R_FFA4_Msk			REG_BIT_MASK(CAN_FFA1R_FFA4_Pos)
/** @brief Acceptance-filter bank 4 FIFO-assignment selector (`CANx_FFA1R.FFA4`) bit mask alias @def CAN_FFA1R_FFA4 */
#define CAN_FFA1R_FFA4				CAN_FFA1R_FFA4_Msk

/** @brief Acceptance-filter bank 5 FIFO-assignment selector (`CANx_FFA1R.FFA5`) bit position @def CAN_FFA1R_FFA5_Pos */
#define CAN_FFA1R_FFA5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 5 FIFO-assignment selector (`CANx_FFA1R.FFA5`) bit mask @def CAN_FFA1R_FFA5_Msk */
#define CAN_FFA1R_FFA5_Msk			REG_BIT_MASK(CAN_FFA1R_FFA5_Pos)
/** @brief Acceptance-filter bank 5 FIFO-assignment selector (`CANx_FFA1R.FFA5`) bit mask alias @def CAN_FFA1R_FFA5 */
#define CAN_FFA1R_FFA5				CAN_FFA1R_FFA5_Msk

/** @brief Acceptance-filter bank 6 FIFO-assignment selector (`CANx_FFA1R.FFA6`) bit position @def CAN_FFA1R_FFA6_Pos */
#define CAN_FFA1R_FFA6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 6 FIFO-assignment selector (`CANx_FFA1R.FFA6`) bit mask @def CAN_FFA1R_FFA6_Msk */
#define CAN_FFA1R_FFA6_Msk			REG_BIT_MASK(CAN_FFA1R_FFA6_Pos)
/** @brief Acceptance-filter bank 6 FIFO-assignment selector (`CANx_FFA1R.FFA6`) bit mask alias @def CAN_FFA1R_FFA6 */
#define CAN_FFA1R_FFA6				CAN_FFA1R_FFA6_Msk

/** @brief Acceptance-filter bank 7 FIFO-assignment selector (`CANx_FFA1R.FFA7`) bit position @def CAN_FFA1R_FFA7_Pos */
#define CAN_FFA1R_FFA7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 7 FIFO-assignment selector (`CANx_FFA1R.FFA7`) bit mask @def CAN_FFA1R_FFA7_Msk */
#define CAN_FFA1R_FFA7_Msk			REG_BIT_MASK(CAN_FFA1R_FFA7_Pos)
/** @brief Acceptance-filter bank 7 FIFO-assignment selector (`CANx_FFA1R.FFA7`) bit mask alias @def CAN_FFA1R_FFA7 */
#define CAN_FFA1R_FFA7				CAN_FFA1R_FFA7_Msk

/** @brief Acceptance-filter bank 8 FIFO-assignment selector (`CANx_FFA1R.FFA8`) bit position @def CAN_FFA1R_FFA8_Pos */
#define CAN_FFA1R_FFA8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 8 FIFO-assignment selector (`CANx_FFA1R.FFA8`) bit mask @def CAN_FFA1R_FFA8_Msk */
#define CAN_FFA1R_FFA8_Msk			REG_BIT_MASK(CAN_FFA1R_FFA8_Pos)
/** @brief Acceptance-filter bank 8 FIFO-assignment selector (`CANx_FFA1R.FFA8`) bit mask alias @def CAN_FFA1R_FFA8 */
#define CAN_FFA1R_FFA8				CAN_FFA1R_FFA8_Msk

/** @brief Acceptance-filter bank 9 FIFO-assignment selector (`CANx_FFA1R.FFA9`) bit position @def CAN_FFA1R_FFA9_Pos */
#define CAN_FFA1R_FFA9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 9 FIFO-assignment selector (`CANx_FFA1R.FFA9`) bit mask @def CAN_FFA1R_FFA9_Msk */
#define CAN_FFA1R_FFA9_Msk			REG_BIT_MASK(CAN_FFA1R_FFA9_Pos)
/** @brief Acceptance-filter bank 9 FIFO-assignment selector (`CANx_FFA1R.FFA9`) bit mask alias @def CAN_FFA1R_FFA9 */
#define CAN_FFA1R_FFA9				CAN_FFA1R_FFA9_Msk

/** @brief Acceptance-filter bank 10 FIFO-assignment selector (`CANx_FFA1R.FFA10`) bit position @def CAN_FFA1R_FFA10_Pos */
#define CAN_FFA1R_FFA10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 10 FIFO-assignment selector (`CANx_FFA1R.FFA10`) bit mask @def CAN_FFA1R_FFA10_Msk */
#define CAN_FFA1R_FFA10_Msk			REG_BIT_MASK(CAN_FFA1R_FFA10_Pos)
/** @brief Acceptance-filter bank 10 FIFO-assignment selector (`CANx_FFA1R.FFA10`) bit mask alias @def CAN_FFA1R_FFA10 */
#define CAN_FFA1R_FFA10				CAN_FFA1R_FFA10_Msk

/** @brief Acceptance-filter bank 11 FIFO-assignment selector (`CANx_FFA1R.FFA11`) bit position @def CAN_FFA1R_FFA11_Pos */
#define CAN_FFA1R_FFA11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 11 FIFO-assignment selector (`CANx_FFA1R.FFA11`) bit mask @def CAN_FFA1R_FFA11_Msk */
#define CAN_FFA1R_FFA11_Msk			REG_BIT_MASK(CAN_FFA1R_FFA11_Pos)
/** @brief Acceptance-filter bank 11 FIFO-assignment selector (`CANx_FFA1R.FFA11`) bit mask alias @def CAN_FFA1R_FFA11 */
#define CAN_FFA1R_FFA11				CAN_FFA1R_FFA11_Msk

/** @brief Acceptance-filter bank 12 FIFO-assignment selector (`CANx_FFA1R.FFA12`) bit position @def CAN_FFA1R_FFA12_Pos */
#define CAN_FFA1R_FFA12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 12 FIFO-assignment selector (`CANx_FFA1R.FFA12`) bit mask @def CAN_FFA1R_FFA12_Msk */
#define CAN_FFA1R_FFA12_Msk			REG_BIT_MASK(CAN_FFA1R_FFA12_Pos)
/** @brief Acceptance-filter bank 12 FIFO-assignment selector (`CANx_FFA1R.FFA12`) bit mask alias @def CAN_FFA1R_FFA12 */
#define CAN_FFA1R_FFA12				CAN_FFA1R_FFA12_Msk

/** @brief Acceptance-filter bank 13 FIFO-assignment selector (`CANx_FFA1R.FFA13`) bit position @def CAN_FFA1R_FFA13_Pos */
#define CAN_FFA1R_FFA13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 13 FIFO-assignment selector (`CANx_FFA1R.FFA13`) bit mask @def CAN_FFA1R_FFA13_Msk */
#define CAN_FFA1R_FFA13_Msk			REG_BIT_MASK(CAN_FFA1R_FFA13_Pos)
/** @brief Acceptance-filter bank 13 FIFO-assignment selector (`CANx_FFA1R.FFA13`) bit mask alias @def CAN_FFA1R_FFA13 */
#define CAN_FFA1R_FFA13				CAN_FFA1R_FFA13_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_FA1R
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter activation selectors (`CANx_FA1R.FACT`) field position @def CAN_FA1R_FACT_Pos */
#define CAN_FA1R_FACT_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter activation selectors (`CANx_FA1R.FACT`) field width @def CAN_FA1R_FACT_Width */
#define CAN_FA1R_FACT_Width			((reg_field_width_t) 14U)
/** @brief Acceptance-filter activation selectors (`CANx_FA1R.FACT`) field mask @def CAN_FA1R_FACT_Msk */
#define CAN_FA1R_FACT_Msk			REG_FIELD_MASK(CAN_FA1R_FACT_Pos, CAN_FA1R_FACT_Width)
/** @brief Acceptance-filter activation selectors (`CANx_FA1R.FACT`) field mask alias @def CAN_FA1R_FACT */
#define CAN_FA1R_FACT				CAN_FA1R_FACT_Msk

/** @brief Acceptance-filter bank 0 activation selector (`CANx_FA1R.FACT0`) bit position @def CAN_FA1R_FACT0_Pos */
#define CAN_FA1R_FACT0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 0 activation selector (`CANx_FA1R.FACT0`) bit mask @def CAN_FA1R_FACT0_Msk */
#define CAN_FA1R_FACT0_Msk			REG_BIT_MASK(CAN_FA1R_FACT0_Pos)
/** @brief Acceptance-filter bank 0 activation selector (`CANx_FA1R.FACT0`) bit mask alias @def CAN_FA1R_FACT0 */
#define CAN_FA1R_FACT0				CAN_FA1R_FACT0_Msk

/** @brief Acceptance-filter bank 1 activation selector (`CANx_FA1R.FACT1`) bit position @def CAN_FA1R_FACT1_Pos */
#define CAN_FA1R_FACT1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 1 activation selector (`CANx_FA1R.FACT1`) bit mask @def CAN_FA1R_FACT1_Msk */
#define CAN_FA1R_FACT1_Msk			REG_BIT_MASK(CAN_FA1R_FACT1_Pos)
/** @brief Acceptance-filter bank 1 activation selector (`CANx_FA1R.FACT1`) bit mask alias @def CAN_FA1R_FACT1 */
#define CAN_FA1R_FACT1				CAN_FA1R_FACT1_Msk

/** @brief Acceptance-filter bank 2 activation selector (`CANx_FA1R.FACT2`) bit position @def CAN_FA1R_FACT2_Pos */
#define CAN_FA1R_FACT2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 2 activation selector (`CANx_FA1R.FACT2`) bit mask @def CAN_FA1R_FACT2_Msk */
#define CAN_FA1R_FACT2_Msk			REG_BIT_MASK(CAN_FA1R_FACT2_Pos)
/** @brief Acceptance-filter bank 2 activation selector (`CANx_FA1R.FACT2`) bit mask alias @def CAN_FA1R_FACT2 */
#define CAN_FA1R_FACT2				CAN_FA1R_FACT2_Msk

/** @brief Acceptance-filter bank 3 activation selector (`CANx_FA1R.FACT3`) bit position @def CAN_FA1R_FACT3_Pos */
#define CAN_FA1R_FACT3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 3 activation selector (`CANx_FA1R.FACT3`) bit mask @def CAN_FA1R_FACT3_Msk */
#define CAN_FA1R_FACT3_Msk			REG_BIT_MASK(CAN_FA1R_FACT3_Pos)
/** @brief Acceptance-filter bank 3 activation selector (`CANx_FA1R.FACT3`) bit mask alias @def CAN_FA1R_FACT3 */
#define CAN_FA1R_FACT3				CAN_FA1R_FACT3_Msk

/** @brief Acceptance-filter bank 4 activation selector (`CANx_FA1R.FACT4`) bit position @def CAN_FA1R_FACT4_Pos */
#define CAN_FA1R_FACT4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 4 activation selector (`CANx_FA1R.FACT4`) bit mask @def CAN_FA1R_FACT4_Msk */
#define CAN_FA1R_FACT4_Msk			REG_BIT_MASK(CAN_FA1R_FACT4_Pos)
/** @brief Acceptance-filter bank 4 activation selector (`CANx_FA1R.FACT4`) bit mask alias @def CAN_FA1R_FACT4 */
#define CAN_FA1R_FACT4				CAN_FA1R_FACT4_Msk

/** @brief Acceptance-filter bank 5 activation selector (`CANx_FA1R.FACT5`) bit position @def CAN_FA1R_FACT5_Pos */
#define CAN_FA1R_FACT5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 5 activation selector (`CANx_FA1R.FACT5`) bit mask @def CAN_FA1R_FACT5_Msk */
#define CAN_FA1R_FACT5_Msk			REG_BIT_MASK(CAN_FA1R_FACT5_Pos)
/** @brief Acceptance-filter bank 5 activation selector (`CANx_FA1R.FACT5`) bit mask alias @def CAN_FA1R_FACT5 */
#define CAN_FA1R_FACT5				CAN_FA1R_FACT5_Msk

/** @brief Acceptance-filter bank 6 activation selector (`CANx_FA1R.FACT6`) bit position @def CAN_FA1R_FACT6_Pos */
#define CAN_FA1R_FACT6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 6 activation selector (`CANx_FA1R.FACT6`) bit mask @def CAN_FA1R_FACT6_Msk */
#define CAN_FA1R_FACT6_Msk			REG_BIT_MASK(CAN_FA1R_FACT6_Pos)
/** @brief Acceptance-filter bank 6 activation selector (`CANx_FA1R.FACT6`) bit mask alias @def CAN_FA1R_FACT6 */
#define CAN_FA1R_FACT6				CAN_FA1R_FACT6_Msk

/** @brief Acceptance-filter bank 7 activation selector (`CANx_FA1R.FACT7`) bit position @def CAN_FA1R_FACT7_Pos */
#define CAN_FA1R_FACT7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 7 activation selector (`CANx_FA1R.FACT7`) bit mask @def CAN_FA1R_FACT7_Msk */
#define CAN_FA1R_FACT7_Msk			REG_BIT_MASK(CAN_FA1R_FACT7_Pos)
/** @brief Acceptance-filter bank 7 activation selector (`CANx_FA1R.FACT7`) bit mask alias @def CAN_FA1R_FACT7 */
#define CAN_FA1R_FACT7				CAN_FA1R_FACT7_Msk

/** @brief Acceptance-filter bank 8 activation selector (`CANx_FA1R.FACT8`) bit position @def CAN_FA1R_FACT8_Pos */
#define CAN_FA1R_FACT8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 8 activation selector (`CANx_FA1R.FACT8`) bit mask @def CAN_FA1R_FACT8_Msk */
#define CAN_FA1R_FACT8_Msk			REG_BIT_MASK(CAN_FA1R_FACT8_Pos)
/** @brief Acceptance-filter bank 8 activation selector (`CANx_FA1R.FACT8`) bit mask alias @def CAN_FA1R_FACT8 */
#define CAN_FA1R_FACT8				CAN_FA1R_FACT8_Msk

/** @brief Acceptance-filter bank 9 activation selector (`CANx_FA1R.FACT9`) bit position @def CAN_FA1R_FACT9_Pos */
#define CAN_FA1R_FACT9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 9 activation selector (`CANx_FA1R.FACT9`) bit mask @def CAN_FA1R_FACT9_Msk */
#define CAN_FA1R_FACT9_Msk			REG_BIT_MASK(CAN_FA1R_FACT9_Pos)
/** @brief Acceptance-filter bank 9 activation selector (`CANx_FA1R.FACT9`) bit mask alias @def CAN_FA1R_FACT9 */
#define CAN_FA1R_FACT9				CAN_FA1R_FACT9_Msk

/** @brief Acceptance-filter bank 10 activation selector (`CANx_FA1R.FACT10`) bit position @def CAN_FA1R_FACT10_Pos */
#define CAN_FA1R_FACT10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 10 activation selector (`CANx_FA1R.FACT10`) bit mask @def CAN_FA1R_FACT10_Msk */
#define CAN_FA1R_FACT10_Msk			REG_BIT_MASK(CAN_FA1R_FACT10_Pos)
/** @brief Acceptance-filter bank 10 activation selector (`CANx_FA1R.FACT10`) bit mask alias @def CAN_FA1R_FACT10 */
#define CAN_FA1R_FACT10				CAN_FA1R_FACT10_Msk

/** @brief Acceptance-filter bank 11 activation selector (`CANx_FA1R.FACT11`) bit position @def CAN_FA1R_FACT11_Pos */
#define CAN_FA1R_FACT11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 11 activation selector (`CANx_FA1R.FACT11`) bit mask @def CAN_FA1R_FACT11_Msk */
#define CAN_FA1R_FACT11_Msk			REG_BIT_MASK(CAN_FA1R_FACT11_Pos)
/** @brief Acceptance-filter bank 11 activation selector (`CANx_FA1R.FACT11`) bit mask alias @def CAN_FA1R_FACT11 */
#define CAN_FA1R_FACT11				CAN_FA1R_FACT11_Msk

/** @brief Acceptance-filter bank 12 activation selector (`CANx_FA1R.FACT12`) bit position @def CAN_FA1R_FACT12_Pos */
#define CAN_FA1R_FACT12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 12 activation selector (`CANx_FA1R.FACT12`) bit mask @def CAN_FA1R_FACT12_Msk */
#define CAN_FA1R_FACT12_Msk			REG_BIT_MASK(CAN_FA1R_FACT12_Pos)
/** @brief Acceptance-filter bank 12 activation selector (`CANx_FA1R.FACT12`) bit mask alias @def CAN_FA1R_FACT12 */
#define CAN_FA1R_FACT12				CAN_FA1R_FACT12_Msk

/** @brief Acceptance-filter bank 13 activation selector (`CANx_FA1R.FACT13`) bit position @def CAN_FA1R_FACT13_Pos */
#define CAN_FA1R_FACT13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 13 activation selector (`CANx_FA1R.FACT13`) bit mask @def CAN_FA1R_FACT13_Msk */
#define CAN_FA1R_FACT13_Msk			REG_BIT_MASK(CAN_FA1R_FACT13_Pos)
/** @brief Acceptance-filter bank 13 activation selector (`CANx_FA1R.FACT13`) bit mask alias @def CAN_FA1R_FACT13 */
#define CAN_FA1R_FACT13				CAN_FA1R_FACT13_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F0R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 0 word 1 bit 0 (`CANx_F0R1.FB0`) bit position @def CAN_F0R1_FB0_Pos */
#define CAN_F0R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 0 word 1 bit 0 (`CANx_F0R1.FB0`) bit mask @def CAN_F0R1_FB0_Msk */
#define CAN_F0R1_FB0_Msk			REG_BIT_MASK(CAN_F0R1_FB0_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 0 (`CANx_F0R1.FB0`) bit mask alias @def CAN_F0R1_FB0 */
#define CAN_F0R1_FB0				CAN_F0R1_FB0_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 1 (`CANx_F0R1.FB1`) bit position @def CAN_F0R1_FB1_Pos */
#define CAN_F0R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 0 word 1 bit 1 (`CANx_F0R1.FB1`) bit mask @def CAN_F0R1_FB1_Msk */
#define CAN_F0R1_FB1_Msk			REG_BIT_MASK(CAN_F0R1_FB1_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 1 (`CANx_F0R1.FB1`) bit mask alias @def CAN_F0R1_FB1 */
#define CAN_F0R1_FB1				CAN_F0R1_FB1_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 2 (`CANx_F0R1.FB2`) bit position @def CAN_F0R1_FB2_Pos */
#define CAN_F0R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 0 word 1 bit 2 (`CANx_F0R1.FB2`) bit mask @def CAN_F0R1_FB2_Msk */
#define CAN_F0R1_FB2_Msk			REG_BIT_MASK(CAN_F0R1_FB2_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 2 (`CANx_F0R1.FB2`) bit mask alias @def CAN_F0R1_FB2 */
#define CAN_F0R1_FB2				CAN_F0R1_FB2_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 3 (`CANx_F0R1.FB3`) bit position @def CAN_F0R1_FB3_Pos */
#define CAN_F0R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 0 word 1 bit 3 (`CANx_F0R1.FB3`) bit mask @def CAN_F0R1_FB3_Msk */
#define CAN_F0R1_FB3_Msk			REG_BIT_MASK(CAN_F0R1_FB3_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 3 (`CANx_F0R1.FB3`) bit mask alias @def CAN_F0R1_FB3 */
#define CAN_F0R1_FB3				CAN_F0R1_FB3_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 4 (`CANx_F0R1.FB4`) bit position @def CAN_F0R1_FB4_Pos */
#define CAN_F0R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 0 word 1 bit 4 (`CANx_F0R1.FB4`) bit mask @def CAN_F0R1_FB4_Msk */
#define CAN_F0R1_FB4_Msk			REG_BIT_MASK(CAN_F0R1_FB4_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 4 (`CANx_F0R1.FB4`) bit mask alias @def CAN_F0R1_FB4 */
#define CAN_F0R1_FB4				CAN_F0R1_FB4_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 5 (`CANx_F0R1.FB5`) bit position @def CAN_F0R1_FB5_Pos */
#define CAN_F0R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 0 word 1 bit 5 (`CANx_F0R1.FB5`) bit mask @def CAN_F0R1_FB5_Msk */
#define CAN_F0R1_FB5_Msk			REG_BIT_MASK(CAN_F0R1_FB5_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 5 (`CANx_F0R1.FB5`) bit mask alias @def CAN_F0R1_FB5 */
#define CAN_F0R1_FB5				CAN_F0R1_FB5_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 6 (`CANx_F0R1.FB6`) bit position @def CAN_F0R1_FB6_Pos */
#define CAN_F0R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 0 word 1 bit 6 (`CANx_F0R1.FB6`) bit mask @def CAN_F0R1_FB6_Msk */
#define CAN_F0R1_FB6_Msk			REG_BIT_MASK(CAN_F0R1_FB6_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 6 (`CANx_F0R1.FB6`) bit mask alias @def CAN_F0R1_FB6 */
#define CAN_F0R1_FB6				CAN_F0R1_FB6_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 7 (`CANx_F0R1.FB7`) bit position @def CAN_F0R1_FB7_Pos */
#define CAN_F0R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 0 word 1 bit 7 (`CANx_F0R1.FB7`) bit mask @def CAN_F0R1_FB7_Msk */
#define CAN_F0R1_FB7_Msk			REG_BIT_MASK(CAN_F0R1_FB7_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 7 (`CANx_F0R1.FB7`) bit mask alias @def CAN_F0R1_FB7 */
#define CAN_F0R1_FB7				CAN_F0R1_FB7_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 8 (`CANx_F0R1.FB8`) bit position @def CAN_F0R1_FB8_Pos */
#define CAN_F0R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 0 word 1 bit 8 (`CANx_F0R1.FB8`) bit mask @def CAN_F0R1_FB8_Msk */
#define CAN_F0R1_FB8_Msk			REG_BIT_MASK(CAN_F0R1_FB8_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 8 (`CANx_F0R1.FB8`) bit mask alias @def CAN_F0R1_FB8 */
#define CAN_F0R1_FB8				CAN_F0R1_FB8_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 9 (`CANx_F0R1.FB9`) bit position @def CAN_F0R1_FB9_Pos */
#define CAN_F0R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 0 word 1 bit 9 (`CANx_F0R1.FB9`) bit mask @def CAN_F0R1_FB9_Msk */
#define CAN_F0R1_FB9_Msk			REG_BIT_MASK(CAN_F0R1_FB9_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 9 (`CANx_F0R1.FB9`) bit mask alias @def CAN_F0R1_FB9 */
#define CAN_F0R1_FB9				CAN_F0R1_FB9_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 10 (`CANx_F0R1.FB10`) bit position @def CAN_F0R1_FB10_Pos */
#define CAN_F0R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 0 word 1 bit 10 (`CANx_F0R1.FB10`) bit mask @def CAN_F0R1_FB10_Msk */
#define CAN_F0R1_FB10_Msk			REG_BIT_MASK(CAN_F0R1_FB10_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 10 (`CANx_F0R1.FB10`) bit mask alias @def CAN_F0R1_FB10 */
#define CAN_F0R1_FB10				CAN_F0R1_FB10_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 11 (`CANx_F0R1.FB11`) bit position @def CAN_F0R1_FB11_Pos */
#define CAN_F0R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 0 word 1 bit 11 (`CANx_F0R1.FB11`) bit mask @def CAN_F0R1_FB11_Msk */
#define CAN_F0R1_FB11_Msk			REG_BIT_MASK(CAN_F0R1_FB11_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 11 (`CANx_F0R1.FB11`) bit mask alias @def CAN_F0R1_FB11 */
#define CAN_F0R1_FB11				CAN_F0R1_FB11_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 12 (`CANx_F0R1.FB12`) bit position @def CAN_F0R1_FB12_Pos */
#define CAN_F0R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 0 word 1 bit 12 (`CANx_F0R1.FB12`) bit mask @def CAN_F0R1_FB12_Msk */
#define CAN_F0R1_FB12_Msk			REG_BIT_MASK(CAN_F0R1_FB12_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 12 (`CANx_F0R1.FB12`) bit mask alias @def CAN_F0R1_FB12 */
#define CAN_F0R1_FB12				CAN_F0R1_FB12_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 13 (`CANx_F0R1.FB13`) bit position @def CAN_F0R1_FB13_Pos */
#define CAN_F0R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 0 word 1 bit 13 (`CANx_F0R1.FB13`) bit mask @def CAN_F0R1_FB13_Msk */
#define CAN_F0R1_FB13_Msk			REG_BIT_MASK(CAN_F0R1_FB13_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 13 (`CANx_F0R1.FB13`) bit mask alias @def CAN_F0R1_FB13 */
#define CAN_F0R1_FB13				CAN_F0R1_FB13_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 14 (`CANx_F0R1.FB14`) bit position @def CAN_F0R1_FB14_Pos */
#define CAN_F0R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 0 word 1 bit 14 (`CANx_F0R1.FB14`) bit mask @def CAN_F0R1_FB14_Msk */
#define CAN_F0R1_FB14_Msk			REG_BIT_MASK(CAN_F0R1_FB14_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 14 (`CANx_F0R1.FB14`) bit mask alias @def CAN_F0R1_FB14 */
#define CAN_F0R1_FB14				CAN_F0R1_FB14_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 15 (`CANx_F0R1.FB15`) bit position @def CAN_F0R1_FB15_Pos */
#define CAN_F0R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 0 word 1 bit 15 (`CANx_F0R1.FB15`) bit mask @def CAN_F0R1_FB15_Msk */
#define CAN_F0R1_FB15_Msk			REG_BIT_MASK(CAN_F0R1_FB15_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 15 (`CANx_F0R1.FB15`) bit mask alias @def CAN_F0R1_FB15 */
#define CAN_F0R1_FB15				CAN_F0R1_FB15_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 16 (`CANx_F0R1.FB16`) bit position @def CAN_F0R1_FB16_Pos */
#define CAN_F0R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 0 word 1 bit 16 (`CANx_F0R1.FB16`) bit mask @def CAN_F0R1_FB16_Msk */
#define CAN_F0R1_FB16_Msk			REG_BIT_MASK(CAN_F0R1_FB16_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 16 (`CANx_F0R1.FB16`) bit mask alias @def CAN_F0R1_FB16 */
#define CAN_F0R1_FB16				CAN_F0R1_FB16_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 17 (`CANx_F0R1.FB17`) bit position @def CAN_F0R1_FB17_Pos */
#define CAN_F0R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 0 word 1 bit 17 (`CANx_F0R1.FB17`) bit mask @def CAN_F0R1_FB17_Msk */
#define CAN_F0R1_FB17_Msk			REG_BIT_MASK(CAN_F0R1_FB17_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 17 (`CANx_F0R1.FB17`) bit mask alias @def CAN_F0R1_FB17 */
#define CAN_F0R1_FB17				CAN_F0R1_FB17_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 18 (`CANx_F0R1.FB18`) bit position @def CAN_F0R1_FB18_Pos */
#define CAN_F0R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 0 word 1 bit 18 (`CANx_F0R1.FB18`) bit mask @def CAN_F0R1_FB18_Msk */
#define CAN_F0R1_FB18_Msk			REG_BIT_MASK(CAN_F0R1_FB18_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 18 (`CANx_F0R1.FB18`) bit mask alias @def CAN_F0R1_FB18 */
#define CAN_F0R1_FB18				CAN_F0R1_FB18_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 19 (`CANx_F0R1.FB19`) bit position @def CAN_F0R1_FB19_Pos */
#define CAN_F0R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 0 word 1 bit 19 (`CANx_F0R1.FB19`) bit mask @def CAN_F0R1_FB19_Msk */
#define CAN_F0R1_FB19_Msk			REG_BIT_MASK(CAN_F0R1_FB19_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 19 (`CANx_F0R1.FB19`) bit mask alias @def CAN_F0R1_FB19 */
#define CAN_F0R1_FB19				CAN_F0R1_FB19_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 20 (`CANx_F0R1.FB20`) bit position @def CAN_F0R1_FB20_Pos */
#define CAN_F0R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 0 word 1 bit 20 (`CANx_F0R1.FB20`) bit mask @def CAN_F0R1_FB20_Msk */
#define CAN_F0R1_FB20_Msk			REG_BIT_MASK(CAN_F0R1_FB20_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 20 (`CANx_F0R1.FB20`) bit mask alias @def CAN_F0R1_FB20 */
#define CAN_F0R1_FB20				CAN_F0R1_FB20_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 21 (`CANx_F0R1.FB21`) bit position @def CAN_F0R1_FB21_Pos */
#define CAN_F0R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 0 word 1 bit 21 (`CANx_F0R1.FB21`) bit mask @def CAN_F0R1_FB21_Msk */
#define CAN_F0R1_FB21_Msk			REG_BIT_MASK(CAN_F0R1_FB21_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 21 (`CANx_F0R1.FB21`) bit mask alias @def CAN_F0R1_FB21 */
#define CAN_F0R1_FB21				CAN_F0R1_FB21_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 22 (`CANx_F0R1.FB22`) bit position @def CAN_F0R1_FB22_Pos */
#define CAN_F0R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 0 word 1 bit 22 (`CANx_F0R1.FB22`) bit mask @def CAN_F0R1_FB22_Msk */
#define CAN_F0R1_FB22_Msk			REG_BIT_MASK(CAN_F0R1_FB22_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 22 (`CANx_F0R1.FB22`) bit mask alias @def CAN_F0R1_FB22 */
#define CAN_F0R1_FB22				CAN_F0R1_FB22_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 23 (`CANx_F0R1.FB23`) bit position @def CAN_F0R1_FB23_Pos */
#define CAN_F0R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 0 word 1 bit 23 (`CANx_F0R1.FB23`) bit mask @def CAN_F0R1_FB23_Msk */
#define CAN_F0R1_FB23_Msk			REG_BIT_MASK(CAN_F0R1_FB23_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 23 (`CANx_F0R1.FB23`) bit mask alias @def CAN_F0R1_FB23 */
#define CAN_F0R1_FB23				CAN_F0R1_FB23_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 24 (`CANx_F0R1.FB24`) bit position @def CAN_F0R1_FB24_Pos */
#define CAN_F0R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 0 word 1 bit 24 (`CANx_F0R1.FB24`) bit mask @def CAN_F0R1_FB24_Msk */
#define CAN_F0R1_FB24_Msk			REG_BIT_MASK(CAN_F0R1_FB24_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 24 (`CANx_F0R1.FB24`) bit mask alias @def CAN_F0R1_FB24 */
#define CAN_F0R1_FB24				CAN_F0R1_FB24_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 25 (`CANx_F0R1.FB25`) bit position @def CAN_F0R1_FB25_Pos */
#define CAN_F0R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 0 word 1 bit 25 (`CANx_F0R1.FB25`) bit mask @def CAN_F0R1_FB25_Msk */
#define CAN_F0R1_FB25_Msk			REG_BIT_MASK(CAN_F0R1_FB25_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 25 (`CANx_F0R1.FB25`) bit mask alias @def CAN_F0R1_FB25 */
#define CAN_F0R1_FB25				CAN_F0R1_FB25_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 26 (`CANx_F0R1.FB26`) bit position @def CAN_F0R1_FB26_Pos */
#define CAN_F0R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 0 word 1 bit 26 (`CANx_F0R1.FB26`) bit mask @def CAN_F0R1_FB26_Msk */
#define CAN_F0R1_FB26_Msk			REG_BIT_MASK(CAN_F0R1_FB26_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 26 (`CANx_F0R1.FB26`) bit mask alias @def CAN_F0R1_FB26 */
#define CAN_F0R1_FB26				CAN_F0R1_FB26_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 27 (`CANx_F0R1.FB27`) bit position @def CAN_F0R1_FB27_Pos */
#define CAN_F0R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 0 word 1 bit 27 (`CANx_F0R1.FB27`) bit mask @def CAN_F0R1_FB27_Msk */
#define CAN_F0R1_FB27_Msk			REG_BIT_MASK(CAN_F0R1_FB27_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 27 (`CANx_F0R1.FB27`) bit mask alias @def CAN_F0R1_FB27 */
#define CAN_F0R1_FB27				CAN_F0R1_FB27_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 28 (`CANx_F0R1.FB28`) bit position @def CAN_F0R1_FB28_Pos */
#define CAN_F0R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 0 word 1 bit 28 (`CANx_F0R1.FB28`) bit mask @def CAN_F0R1_FB28_Msk */
#define CAN_F0R1_FB28_Msk			REG_BIT_MASK(CAN_F0R1_FB28_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 28 (`CANx_F0R1.FB28`) bit mask alias @def CAN_F0R1_FB28 */
#define CAN_F0R1_FB28				CAN_F0R1_FB28_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 29 (`CANx_F0R1.FB29`) bit position @def CAN_F0R1_FB29_Pos */
#define CAN_F0R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 0 word 1 bit 29 (`CANx_F0R1.FB29`) bit mask @def CAN_F0R1_FB29_Msk */
#define CAN_F0R1_FB29_Msk			REG_BIT_MASK(CAN_F0R1_FB29_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 29 (`CANx_F0R1.FB29`) bit mask alias @def CAN_F0R1_FB29 */
#define CAN_F0R1_FB29				CAN_F0R1_FB29_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 30 (`CANx_F0R1.FB30`) bit position @def CAN_F0R1_FB30_Pos */
#define CAN_F0R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 0 word 1 bit 30 (`CANx_F0R1.FB30`) bit mask @def CAN_F0R1_FB30_Msk */
#define CAN_F0R1_FB30_Msk			REG_BIT_MASK(CAN_F0R1_FB30_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 30 (`CANx_F0R1.FB30`) bit mask alias @def CAN_F0R1_FB30 */
#define CAN_F0R1_FB30				CAN_F0R1_FB30_Msk

/** @brief Acceptance-filter bank 0 word 1 bit 31 (`CANx_F0R1.FB31`) bit position @def CAN_F0R1_FB31_Pos */
#define CAN_F0R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 0 word 1 bit 31 (`CANx_F0R1.FB31`) bit mask @def CAN_F0R1_FB31_Msk */
#define CAN_F0R1_FB31_Msk			REG_BIT_MASK(CAN_F0R1_FB31_Pos)
/** @brief Acceptance-filter bank 0 word 1 bit 31 (`CANx_F0R1.FB31`) bit mask alias @def CAN_F0R1_FB31 */
#define CAN_F0R1_FB31				CAN_F0R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F1R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 1 word 1 bit 0 (`CANx_F1R1.FB0`) bit position @def CAN_F1R1_FB0_Pos */
#define CAN_F1R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 1 word 1 bit 0 (`CANx_F1R1.FB0`) bit mask @def CAN_F1R1_FB0_Msk */
#define CAN_F1R1_FB0_Msk			REG_BIT_MASK(CAN_F1R1_FB0_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 0 (`CANx_F1R1.FB0`) bit mask alias @def CAN_F1R1_FB0 */
#define CAN_F1R1_FB0				CAN_F1R1_FB0_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 1 (`CANx_F1R1.FB1`) bit position @def CAN_F1R1_FB1_Pos */
#define CAN_F1R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 1 word 1 bit 1 (`CANx_F1R1.FB1`) bit mask @def CAN_F1R1_FB1_Msk */
#define CAN_F1R1_FB1_Msk			REG_BIT_MASK(CAN_F1R1_FB1_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 1 (`CANx_F1R1.FB1`) bit mask alias @def CAN_F1R1_FB1 */
#define CAN_F1R1_FB1				CAN_F1R1_FB1_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 2 (`CANx_F1R1.FB2`) bit position @def CAN_F1R1_FB2_Pos */
#define CAN_F1R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 1 word 1 bit 2 (`CANx_F1R1.FB2`) bit mask @def CAN_F1R1_FB2_Msk */
#define CAN_F1R1_FB2_Msk			REG_BIT_MASK(CAN_F1R1_FB2_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 2 (`CANx_F1R1.FB2`) bit mask alias @def CAN_F1R1_FB2 */
#define CAN_F1R1_FB2				CAN_F1R1_FB2_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 3 (`CANx_F1R1.FB3`) bit position @def CAN_F1R1_FB3_Pos */
#define CAN_F1R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 1 word 1 bit 3 (`CANx_F1R1.FB3`) bit mask @def CAN_F1R1_FB3_Msk */
#define CAN_F1R1_FB3_Msk			REG_BIT_MASK(CAN_F1R1_FB3_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 3 (`CANx_F1R1.FB3`) bit mask alias @def CAN_F1R1_FB3 */
#define CAN_F1R1_FB3				CAN_F1R1_FB3_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 4 (`CANx_F1R1.FB4`) bit position @def CAN_F1R1_FB4_Pos */
#define CAN_F1R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 1 word 1 bit 4 (`CANx_F1R1.FB4`) bit mask @def CAN_F1R1_FB4_Msk */
#define CAN_F1R1_FB4_Msk			REG_BIT_MASK(CAN_F1R1_FB4_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 4 (`CANx_F1R1.FB4`) bit mask alias @def CAN_F1R1_FB4 */
#define CAN_F1R1_FB4				CAN_F1R1_FB4_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 5 (`CANx_F1R1.FB5`) bit position @def CAN_F1R1_FB5_Pos */
#define CAN_F1R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 1 word 1 bit 5 (`CANx_F1R1.FB5`) bit mask @def CAN_F1R1_FB5_Msk */
#define CAN_F1R1_FB5_Msk			REG_BIT_MASK(CAN_F1R1_FB5_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 5 (`CANx_F1R1.FB5`) bit mask alias @def CAN_F1R1_FB5 */
#define CAN_F1R1_FB5				CAN_F1R1_FB5_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 6 (`CANx_F1R1.FB6`) bit position @def CAN_F1R1_FB6_Pos */
#define CAN_F1R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 1 word 1 bit 6 (`CANx_F1R1.FB6`) bit mask @def CAN_F1R1_FB6_Msk */
#define CAN_F1R1_FB6_Msk			REG_BIT_MASK(CAN_F1R1_FB6_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 6 (`CANx_F1R1.FB6`) bit mask alias @def CAN_F1R1_FB6 */
#define CAN_F1R1_FB6				CAN_F1R1_FB6_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 7 (`CANx_F1R1.FB7`) bit position @def CAN_F1R1_FB7_Pos */
#define CAN_F1R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 1 word 1 bit 7 (`CANx_F1R1.FB7`) bit mask @def CAN_F1R1_FB7_Msk */
#define CAN_F1R1_FB7_Msk			REG_BIT_MASK(CAN_F1R1_FB7_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 7 (`CANx_F1R1.FB7`) bit mask alias @def CAN_F1R1_FB7 */
#define CAN_F1R1_FB7				CAN_F1R1_FB7_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 8 (`CANx_F1R1.FB8`) bit position @def CAN_F1R1_FB8_Pos */
#define CAN_F1R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 1 word 1 bit 8 (`CANx_F1R1.FB8`) bit mask @def CAN_F1R1_FB8_Msk */
#define CAN_F1R1_FB8_Msk			REG_BIT_MASK(CAN_F1R1_FB8_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 8 (`CANx_F1R1.FB8`) bit mask alias @def CAN_F1R1_FB8 */
#define CAN_F1R1_FB8				CAN_F1R1_FB8_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 9 (`CANx_F1R1.FB9`) bit position @def CAN_F1R1_FB9_Pos */
#define CAN_F1R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 1 word 1 bit 9 (`CANx_F1R1.FB9`) bit mask @def CAN_F1R1_FB9_Msk */
#define CAN_F1R1_FB9_Msk			REG_BIT_MASK(CAN_F1R1_FB9_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 9 (`CANx_F1R1.FB9`) bit mask alias @def CAN_F1R1_FB9 */
#define CAN_F1R1_FB9				CAN_F1R1_FB9_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 10 (`CANx_F1R1.FB10`) bit position @def CAN_F1R1_FB10_Pos */
#define CAN_F1R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 1 word 1 bit 10 (`CANx_F1R1.FB10`) bit mask @def CAN_F1R1_FB10_Msk */
#define CAN_F1R1_FB10_Msk			REG_BIT_MASK(CAN_F1R1_FB10_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 10 (`CANx_F1R1.FB10`) bit mask alias @def CAN_F1R1_FB10 */
#define CAN_F1R1_FB10				CAN_F1R1_FB10_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 11 (`CANx_F1R1.FB11`) bit position @def CAN_F1R1_FB11_Pos */
#define CAN_F1R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 1 word 1 bit 11 (`CANx_F1R1.FB11`) bit mask @def CAN_F1R1_FB11_Msk */
#define CAN_F1R1_FB11_Msk			REG_BIT_MASK(CAN_F1R1_FB11_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 11 (`CANx_F1R1.FB11`) bit mask alias @def CAN_F1R1_FB11 */
#define CAN_F1R1_FB11				CAN_F1R1_FB11_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 12 (`CANx_F1R1.FB12`) bit position @def CAN_F1R1_FB12_Pos */
#define CAN_F1R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 1 word 1 bit 12 (`CANx_F1R1.FB12`) bit mask @def CAN_F1R1_FB12_Msk */
#define CAN_F1R1_FB12_Msk			REG_BIT_MASK(CAN_F1R1_FB12_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 12 (`CANx_F1R1.FB12`) bit mask alias @def CAN_F1R1_FB12 */
#define CAN_F1R1_FB12				CAN_F1R1_FB12_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 13 (`CANx_F1R1.FB13`) bit position @def CAN_F1R1_FB13_Pos */
#define CAN_F1R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 1 word 1 bit 13 (`CANx_F1R1.FB13`) bit mask @def CAN_F1R1_FB13_Msk */
#define CAN_F1R1_FB13_Msk			REG_BIT_MASK(CAN_F1R1_FB13_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 13 (`CANx_F1R1.FB13`) bit mask alias @def CAN_F1R1_FB13 */
#define CAN_F1R1_FB13				CAN_F1R1_FB13_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 14 (`CANx_F1R1.FB14`) bit position @def CAN_F1R1_FB14_Pos */
#define CAN_F1R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 1 word 1 bit 14 (`CANx_F1R1.FB14`) bit mask @def CAN_F1R1_FB14_Msk */
#define CAN_F1R1_FB14_Msk			REG_BIT_MASK(CAN_F1R1_FB14_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 14 (`CANx_F1R1.FB14`) bit mask alias @def CAN_F1R1_FB14 */
#define CAN_F1R1_FB14				CAN_F1R1_FB14_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 15 (`CANx_F1R1.FB15`) bit position @def CAN_F1R1_FB15_Pos */
#define CAN_F1R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 1 word 1 bit 15 (`CANx_F1R1.FB15`) bit mask @def CAN_F1R1_FB15_Msk */
#define CAN_F1R1_FB15_Msk			REG_BIT_MASK(CAN_F1R1_FB15_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 15 (`CANx_F1R1.FB15`) bit mask alias @def CAN_F1R1_FB15 */
#define CAN_F1R1_FB15				CAN_F1R1_FB15_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 16 (`CANx_F1R1.FB16`) bit position @def CAN_F1R1_FB16_Pos */
#define CAN_F1R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 1 word 1 bit 16 (`CANx_F1R1.FB16`) bit mask @def CAN_F1R1_FB16_Msk */
#define CAN_F1R1_FB16_Msk			REG_BIT_MASK(CAN_F1R1_FB16_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 16 (`CANx_F1R1.FB16`) bit mask alias @def CAN_F1R1_FB16 */
#define CAN_F1R1_FB16				CAN_F1R1_FB16_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 17 (`CANx_F1R1.FB17`) bit position @def CAN_F1R1_FB17_Pos */
#define CAN_F1R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 1 word 1 bit 17 (`CANx_F1R1.FB17`) bit mask @def CAN_F1R1_FB17_Msk */
#define CAN_F1R1_FB17_Msk			REG_BIT_MASK(CAN_F1R1_FB17_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 17 (`CANx_F1R1.FB17`) bit mask alias @def CAN_F1R1_FB17 */
#define CAN_F1R1_FB17				CAN_F1R1_FB17_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 18 (`CANx_F1R1.FB18`) bit position @def CAN_F1R1_FB18_Pos */
#define CAN_F1R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 1 word 1 bit 18 (`CANx_F1R1.FB18`) bit mask @def CAN_F1R1_FB18_Msk */
#define CAN_F1R1_FB18_Msk			REG_BIT_MASK(CAN_F1R1_FB18_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 18 (`CANx_F1R1.FB18`) bit mask alias @def CAN_F1R1_FB18 */
#define CAN_F1R1_FB18				CAN_F1R1_FB18_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 19 (`CANx_F1R1.FB19`) bit position @def CAN_F1R1_FB19_Pos */
#define CAN_F1R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 1 word 1 bit 19 (`CANx_F1R1.FB19`) bit mask @def CAN_F1R1_FB19_Msk */
#define CAN_F1R1_FB19_Msk			REG_BIT_MASK(CAN_F1R1_FB19_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 19 (`CANx_F1R1.FB19`) bit mask alias @def CAN_F1R1_FB19 */
#define CAN_F1R1_FB19				CAN_F1R1_FB19_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 20 (`CANx_F1R1.FB20`) bit position @def CAN_F1R1_FB20_Pos */
#define CAN_F1R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 1 word 1 bit 20 (`CANx_F1R1.FB20`) bit mask @def CAN_F1R1_FB20_Msk */
#define CAN_F1R1_FB20_Msk			REG_BIT_MASK(CAN_F1R1_FB20_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 20 (`CANx_F1R1.FB20`) bit mask alias @def CAN_F1R1_FB20 */
#define CAN_F1R1_FB20				CAN_F1R1_FB20_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 21 (`CANx_F1R1.FB21`) bit position @def CAN_F1R1_FB21_Pos */
#define CAN_F1R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 1 word 1 bit 21 (`CANx_F1R1.FB21`) bit mask @def CAN_F1R1_FB21_Msk */
#define CAN_F1R1_FB21_Msk			REG_BIT_MASK(CAN_F1R1_FB21_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 21 (`CANx_F1R1.FB21`) bit mask alias @def CAN_F1R1_FB21 */
#define CAN_F1R1_FB21				CAN_F1R1_FB21_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 22 (`CANx_F1R1.FB22`) bit position @def CAN_F1R1_FB22_Pos */
#define CAN_F1R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 1 word 1 bit 22 (`CANx_F1R1.FB22`) bit mask @def CAN_F1R1_FB22_Msk */
#define CAN_F1R1_FB22_Msk			REG_BIT_MASK(CAN_F1R1_FB22_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 22 (`CANx_F1R1.FB22`) bit mask alias @def CAN_F1R1_FB22 */
#define CAN_F1R1_FB22				CAN_F1R1_FB22_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 23 (`CANx_F1R1.FB23`) bit position @def CAN_F1R1_FB23_Pos */
#define CAN_F1R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 1 word 1 bit 23 (`CANx_F1R1.FB23`) bit mask @def CAN_F1R1_FB23_Msk */
#define CAN_F1R1_FB23_Msk			REG_BIT_MASK(CAN_F1R1_FB23_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 23 (`CANx_F1R1.FB23`) bit mask alias @def CAN_F1R1_FB23 */
#define CAN_F1R1_FB23				CAN_F1R1_FB23_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 24 (`CANx_F1R1.FB24`) bit position @def CAN_F1R1_FB24_Pos */
#define CAN_F1R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 1 word 1 bit 24 (`CANx_F1R1.FB24`) bit mask @def CAN_F1R1_FB24_Msk */
#define CAN_F1R1_FB24_Msk			REG_BIT_MASK(CAN_F1R1_FB24_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 24 (`CANx_F1R1.FB24`) bit mask alias @def CAN_F1R1_FB24 */
#define CAN_F1R1_FB24				CAN_F1R1_FB24_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 25 (`CANx_F1R1.FB25`) bit position @def CAN_F1R1_FB25_Pos */
#define CAN_F1R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 1 word 1 bit 25 (`CANx_F1R1.FB25`) bit mask @def CAN_F1R1_FB25_Msk */
#define CAN_F1R1_FB25_Msk			REG_BIT_MASK(CAN_F1R1_FB25_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 25 (`CANx_F1R1.FB25`) bit mask alias @def CAN_F1R1_FB25 */
#define CAN_F1R1_FB25				CAN_F1R1_FB25_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 26 (`CANx_F1R1.FB26`) bit position @def CAN_F1R1_FB26_Pos */
#define CAN_F1R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 1 word 1 bit 26 (`CANx_F1R1.FB26`) bit mask @def CAN_F1R1_FB26_Msk */
#define CAN_F1R1_FB26_Msk			REG_BIT_MASK(CAN_F1R1_FB26_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 26 (`CANx_F1R1.FB26`) bit mask alias @def CAN_F1R1_FB26 */
#define CAN_F1R1_FB26				CAN_F1R1_FB26_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 27 (`CANx_F1R1.FB27`) bit position @def CAN_F1R1_FB27_Pos */
#define CAN_F1R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 1 word 1 bit 27 (`CANx_F1R1.FB27`) bit mask @def CAN_F1R1_FB27_Msk */
#define CAN_F1R1_FB27_Msk			REG_BIT_MASK(CAN_F1R1_FB27_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 27 (`CANx_F1R1.FB27`) bit mask alias @def CAN_F1R1_FB27 */
#define CAN_F1R1_FB27				CAN_F1R1_FB27_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 28 (`CANx_F1R1.FB28`) bit position @def CAN_F1R1_FB28_Pos */
#define CAN_F1R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 1 word 1 bit 28 (`CANx_F1R1.FB28`) bit mask @def CAN_F1R1_FB28_Msk */
#define CAN_F1R1_FB28_Msk			REG_BIT_MASK(CAN_F1R1_FB28_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 28 (`CANx_F1R1.FB28`) bit mask alias @def CAN_F1R1_FB28 */
#define CAN_F1R1_FB28				CAN_F1R1_FB28_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 29 (`CANx_F1R1.FB29`) bit position @def CAN_F1R1_FB29_Pos */
#define CAN_F1R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 1 word 1 bit 29 (`CANx_F1R1.FB29`) bit mask @def CAN_F1R1_FB29_Msk */
#define CAN_F1R1_FB29_Msk			REG_BIT_MASK(CAN_F1R1_FB29_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 29 (`CANx_F1R1.FB29`) bit mask alias @def CAN_F1R1_FB29 */
#define CAN_F1R1_FB29				CAN_F1R1_FB29_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 30 (`CANx_F1R1.FB30`) bit position @def CAN_F1R1_FB30_Pos */
#define CAN_F1R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 1 word 1 bit 30 (`CANx_F1R1.FB30`) bit mask @def CAN_F1R1_FB30_Msk */
#define CAN_F1R1_FB30_Msk			REG_BIT_MASK(CAN_F1R1_FB30_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 30 (`CANx_F1R1.FB30`) bit mask alias @def CAN_F1R1_FB30 */
#define CAN_F1R1_FB30				CAN_F1R1_FB30_Msk

/** @brief Acceptance-filter bank 1 word 1 bit 31 (`CANx_F1R1.FB31`) bit position @def CAN_F1R1_FB31_Pos */
#define CAN_F1R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 1 word 1 bit 31 (`CANx_F1R1.FB31`) bit mask @def CAN_F1R1_FB31_Msk */
#define CAN_F1R1_FB31_Msk			REG_BIT_MASK(CAN_F1R1_FB31_Pos)
/** @brief Acceptance-filter bank 1 word 1 bit 31 (`CANx_F1R1.FB31`) bit mask alias @def CAN_F1R1_FB31 */
#define CAN_F1R1_FB31				CAN_F1R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F2R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 2 word 1 bit 0 (`CANx_F2R1.FB0`) bit position @def CAN_F2R1_FB0_Pos */
#define CAN_F2R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 2 word 1 bit 0 (`CANx_F2R1.FB0`) bit mask @def CAN_F2R1_FB0_Msk */
#define CAN_F2R1_FB0_Msk			REG_BIT_MASK(CAN_F2R1_FB0_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 0 (`CANx_F2R1.FB0`) bit mask alias @def CAN_F2R1_FB0 */
#define CAN_F2R1_FB0				CAN_F2R1_FB0_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 1 (`CANx_F2R1.FB1`) bit position @def CAN_F2R1_FB1_Pos */
#define CAN_F2R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 2 word 1 bit 1 (`CANx_F2R1.FB1`) bit mask @def CAN_F2R1_FB1_Msk */
#define CAN_F2R1_FB1_Msk			REG_BIT_MASK(CAN_F2R1_FB1_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 1 (`CANx_F2R1.FB1`) bit mask alias @def CAN_F2R1_FB1 */
#define CAN_F2R1_FB1				CAN_F2R1_FB1_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 2 (`CANx_F2R1.FB2`) bit position @def CAN_F2R1_FB2_Pos */
#define CAN_F2R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 2 word 1 bit 2 (`CANx_F2R1.FB2`) bit mask @def CAN_F2R1_FB2_Msk */
#define CAN_F2R1_FB2_Msk			REG_BIT_MASK(CAN_F2R1_FB2_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 2 (`CANx_F2R1.FB2`) bit mask alias @def CAN_F2R1_FB2 */
#define CAN_F2R1_FB2				CAN_F2R1_FB2_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 3 (`CANx_F2R1.FB3`) bit position @def CAN_F2R1_FB3_Pos */
#define CAN_F2R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 2 word 1 bit 3 (`CANx_F2R1.FB3`) bit mask @def CAN_F2R1_FB3_Msk */
#define CAN_F2R1_FB3_Msk			REG_BIT_MASK(CAN_F2R1_FB3_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 3 (`CANx_F2R1.FB3`) bit mask alias @def CAN_F2R1_FB3 */
#define CAN_F2R1_FB3				CAN_F2R1_FB3_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 4 (`CANx_F2R1.FB4`) bit position @def CAN_F2R1_FB4_Pos */
#define CAN_F2R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 2 word 1 bit 4 (`CANx_F2R1.FB4`) bit mask @def CAN_F2R1_FB4_Msk */
#define CAN_F2R1_FB4_Msk			REG_BIT_MASK(CAN_F2R1_FB4_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 4 (`CANx_F2R1.FB4`) bit mask alias @def CAN_F2R1_FB4 */
#define CAN_F2R1_FB4				CAN_F2R1_FB4_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 5 (`CANx_F2R1.FB5`) bit position @def CAN_F2R1_FB5_Pos */
#define CAN_F2R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 2 word 1 bit 5 (`CANx_F2R1.FB5`) bit mask @def CAN_F2R1_FB5_Msk */
#define CAN_F2R1_FB5_Msk			REG_BIT_MASK(CAN_F2R1_FB5_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 5 (`CANx_F2R1.FB5`) bit mask alias @def CAN_F2R1_FB5 */
#define CAN_F2R1_FB5				CAN_F2R1_FB5_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 6 (`CANx_F2R1.FB6`) bit position @def CAN_F2R1_FB6_Pos */
#define CAN_F2R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 2 word 1 bit 6 (`CANx_F2R1.FB6`) bit mask @def CAN_F2R1_FB6_Msk */
#define CAN_F2R1_FB6_Msk			REG_BIT_MASK(CAN_F2R1_FB6_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 6 (`CANx_F2R1.FB6`) bit mask alias @def CAN_F2R1_FB6 */
#define CAN_F2R1_FB6				CAN_F2R1_FB6_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 7 (`CANx_F2R1.FB7`) bit position @def CAN_F2R1_FB7_Pos */
#define CAN_F2R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 2 word 1 bit 7 (`CANx_F2R1.FB7`) bit mask @def CAN_F2R1_FB7_Msk */
#define CAN_F2R1_FB7_Msk			REG_BIT_MASK(CAN_F2R1_FB7_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 7 (`CANx_F2R1.FB7`) bit mask alias @def CAN_F2R1_FB7 */
#define CAN_F2R1_FB7				CAN_F2R1_FB7_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 8 (`CANx_F2R1.FB8`) bit position @def CAN_F2R1_FB8_Pos */
#define CAN_F2R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 2 word 1 bit 8 (`CANx_F2R1.FB8`) bit mask @def CAN_F2R1_FB8_Msk */
#define CAN_F2R1_FB8_Msk			REG_BIT_MASK(CAN_F2R1_FB8_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 8 (`CANx_F2R1.FB8`) bit mask alias @def CAN_F2R1_FB8 */
#define CAN_F2R1_FB8				CAN_F2R1_FB8_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 9 (`CANx_F2R1.FB9`) bit position @def CAN_F2R1_FB9_Pos */
#define CAN_F2R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 2 word 1 bit 9 (`CANx_F2R1.FB9`) bit mask @def CAN_F2R1_FB9_Msk */
#define CAN_F2R1_FB9_Msk			REG_BIT_MASK(CAN_F2R1_FB9_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 9 (`CANx_F2R1.FB9`) bit mask alias @def CAN_F2R1_FB9 */
#define CAN_F2R1_FB9				CAN_F2R1_FB9_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 10 (`CANx_F2R1.FB10`) bit position @def CAN_F2R1_FB10_Pos */
#define CAN_F2R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 2 word 1 bit 10 (`CANx_F2R1.FB10`) bit mask @def CAN_F2R1_FB10_Msk */
#define CAN_F2R1_FB10_Msk			REG_BIT_MASK(CAN_F2R1_FB10_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 10 (`CANx_F2R1.FB10`) bit mask alias @def CAN_F2R1_FB10 */
#define CAN_F2R1_FB10				CAN_F2R1_FB10_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 11 (`CANx_F2R1.FB11`) bit position @def CAN_F2R1_FB11_Pos */
#define CAN_F2R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 2 word 1 bit 11 (`CANx_F2R1.FB11`) bit mask @def CAN_F2R1_FB11_Msk */
#define CAN_F2R1_FB11_Msk			REG_BIT_MASK(CAN_F2R1_FB11_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 11 (`CANx_F2R1.FB11`) bit mask alias @def CAN_F2R1_FB11 */
#define CAN_F2R1_FB11				CAN_F2R1_FB11_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 12 (`CANx_F2R1.FB12`) bit position @def CAN_F2R1_FB12_Pos */
#define CAN_F2R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 2 word 1 bit 12 (`CANx_F2R1.FB12`) bit mask @def CAN_F2R1_FB12_Msk */
#define CAN_F2R1_FB12_Msk			REG_BIT_MASK(CAN_F2R1_FB12_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 12 (`CANx_F2R1.FB12`) bit mask alias @def CAN_F2R1_FB12 */
#define CAN_F2R1_FB12				CAN_F2R1_FB12_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 13 (`CANx_F2R1.FB13`) bit position @def CAN_F2R1_FB13_Pos */
#define CAN_F2R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 2 word 1 bit 13 (`CANx_F2R1.FB13`) bit mask @def CAN_F2R1_FB13_Msk */
#define CAN_F2R1_FB13_Msk			REG_BIT_MASK(CAN_F2R1_FB13_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 13 (`CANx_F2R1.FB13`) bit mask alias @def CAN_F2R1_FB13 */
#define CAN_F2R1_FB13				CAN_F2R1_FB13_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 14 (`CANx_F2R1.FB14`) bit position @def CAN_F2R1_FB14_Pos */
#define CAN_F2R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 2 word 1 bit 14 (`CANx_F2R1.FB14`) bit mask @def CAN_F2R1_FB14_Msk */
#define CAN_F2R1_FB14_Msk			REG_BIT_MASK(CAN_F2R1_FB14_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 14 (`CANx_F2R1.FB14`) bit mask alias @def CAN_F2R1_FB14 */
#define CAN_F2R1_FB14				CAN_F2R1_FB14_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 15 (`CANx_F2R1.FB15`) bit position @def CAN_F2R1_FB15_Pos */
#define CAN_F2R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 2 word 1 bit 15 (`CANx_F2R1.FB15`) bit mask @def CAN_F2R1_FB15_Msk */
#define CAN_F2R1_FB15_Msk			REG_BIT_MASK(CAN_F2R1_FB15_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 15 (`CANx_F2R1.FB15`) bit mask alias @def CAN_F2R1_FB15 */
#define CAN_F2R1_FB15				CAN_F2R1_FB15_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 16 (`CANx_F2R1.FB16`) bit position @def CAN_F2R1_FB16_Pos */
#define CAN_F2R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 2 word 1 bit 16 (`CANx_F2R1.FB16`) bit mask @def CAN_F2R1_FB16_Msk */
#define CAN_F2R1_FB16_Msk			REG_BIT_MASK(CAN_F2R1_FB16_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 16 (`CANx_F2R1.FB16`) bit mask alias @def CAN_F2R1_FB16 */
#define CAN_F2R1_FB16				CAN_F2R1_FB16_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 17 (`CANx_F2R1.FB17`) bit position @def CAN_F2R1_FB17_Pos */
#define CAN_F2R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 2 word 1 bit 17 (`CANx_F2R1.FB17`) bit mask @def CAN_F2R1_FB17_Msk */
#define CAN_F2R1_FB17_Msk			REG_BIT_MASK(CAN_F2R1_FB17_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 17 (`CANx_F2R1.FB17`) bit mask alias @def CAN_F2R1_FB17 */
#define CAN_F2R1_FB17				CAN_F2R1_FB17_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 18 (`CANx_F2R1.FB18`) bit position @def CAN_F2R1_FB18_Pos */
#define CAN_F2R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 2 word 1 bit 18 (`CANx_F2R1.FB18`) bit mask @def CAN_F2R1_FB18_Msk */
#define CAN_F2R1_FB18_Msk			REG_BIT_MASK(CAN_F2R1_FB18_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 18 (`CANx_F2R1.FB18`) bit mask alias @def CAN_F2R1_FB18 */
#define CAN_F2R1_FB18				CAN_F2R1_FB18_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 19 (`CANx_F2R1.FB19`) bit position @def CAN_F2R1_FB19_Pos */
#define CAN_F2R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 2 word 1 bit 19 (`CANx_F2R1.FB19`) bit mask @def CAN_F2R1_FB19_Msk */
#define CAN_F2R1_FB19_Msk			REG_BIT_MASK(CAN_F2R1_FB19_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 19 (`CANx_F2R1.FB19`) bit mask alias @def CAN_F2R1_FB19 */
#define CAN_F2R1_FB19				CAN_F2R1_FB19_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 20 (`CANx_F2R1.FB20`) bit position @def CAN_F2R1_FB20_Pos */
#define CAN_F2R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 2 word 1 bit 20 (`CANx_F2R1.FB20`) bit mask @def CAN_F2R1_FB20_Msk */
#define CAN_F2R1_FB20_Msk			REG_BIT_MASK(CAN_F2R1_FB20_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 20 (`CANx_F2R1.FB20`) bit mask alias @def CAN_F2R1_FB20 */
#define CAN_F2R1_FB20				CAN_F2R1_FB20_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 21 (`CANx_F2R1.FB21`) bit position @def CAN_F2R1_FB21_Pos */
#define CAN_F2R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 2 word 1 bit 21 (`CANx_F2R1.FB21`) bit mask @def CAN_F2R1_FB21_Msk */
#define CAN_F2R1_FB21_Msk			REG_BIT_MASK(CAN_F2R1_FB21_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 21 (`CANx_F2R1.FB21`) bit mask alias @def CAN_F2R1_FB21 */
#define CAN_F2R1_FB21				CAN_F2R1_FB21_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 22 (`CANx_F2R1.FB22`) bit position @def CAN_F2R1_FB22_Pos */
#define CAN_F2R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 2 word 1 bit 22 (`CANx_F2R1.FB22`) bit mask @def CAN_F2R1_FB22_Msk */
#define CAN_F2R1_FB22_Msk			REG_BIT_MASK(CAN_F2R1_FB22_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 22 (`CANx_F2R1.FB22`) bit mask alias @def CAN_F2R1_FB22 */
#define CAN_F2R1_FB22				CAN_F2R1_FB22_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 23 (`CANx_F2R1.FB23`) bit position @def CAN_F2R1_FB23_Pos */
#define CAN_F2R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 2 word 1 bit 23 (`CANx_F2R1.FB23`) bit mask @def CAN_F2R1_FB23_Msk */
#define CAN_F2R1_FB23_Msk			REG_BIT_MASK(CAN_F2R1_FB23_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 23 (`CANx_F2R1.FB23`) bit mask alias @def CAN_F2R1_FB23 */
#define CAN_F2R1_FB23				CAN_F2R1_FB23_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 24 (`CANx_F2R1.FB24`) bit position @def CAN_F2R1_FB24_Pos */
#define CAN_F2R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 2 word 1 bit 24 (`CANx_F2R1.FB24`) bit mask @def CAN_F2R1_FB24_Msk */
#define CAN_F2R1_FB24_Msk			REG_BIT_MASK(CAN_F2R1_FB24_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 24 (`CANx_F2R1.FB24`) bit mask alias @def CAN_F2R1_FB24 */
#define CAN_F2R1_FB24				CAN_F2R1_FB24_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 25 (`CANx_F2R1.FB25`) bit position @def CAN_F2R1_FB25_Pos */
#define CAN_F2R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 2 word 1 bit 25 (`CANx_F2R1.FB25`) bit mask @def CAN_F2R1_FB25_Msk */
#define CAN_F2R1_FB25_Msk			REG_BIT_MASK(CAN_F2R1_FB25_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 25 (`CANx_F2R1.FB25`) bit mask alias @def CAN_F2R1_FB25 */
#define CAN_F2R1_FB25				CAN_F2R1_FB25_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 26 (`CANx_F2R1.FB26`) bit position @def CAN_F2R1_FB26_Pos */
#define CAN_F2R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 2 word 1 bit 26 (`CANx_F2R1.FB26`) bit mask @def CAN_F2R1_FB26_Msk */
#define CAN_F2R1_FB26_Msk			REG_BIT_MASK(CAN_F2R1_FB26_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 26 (`CANx_F2R1.FB26`) bit mask alias @def CAN_F2R1_FB26 */
#define CAN_F2R1_FB26				CAN_F2R1_FB26_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 27 (`CANx_F2R1.FB27`) bit position @def CAN_F2R1_FB27_Pos */
#define CAN_F2R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 2 word 1 bit 27 (`CANx_F2R1.FB27`) bit mask @def CAN_F2R1_FB27_Msk */
#define CAN_F2R1_FB27_Msk			REG_BIT_MASK(CAN_F2R1_FB27_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 27 (`CANx_F2R1.FB27`) bit mask alias @def CAN_F2R1_FB27 */
#define CAN_F2R1_FB27				CAN_F2R1_FB27_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 28 (`CANx_F2R1.FB28`) bit position @def CAN_F2R1_FB28_Pos */
#define CAN_F2R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 2 word 1 bit 28 (`CANx_F2R1.FB28`) bit mask @def CAN_F2R1_FB28_Msk */
#define CAN_F2R1_FB28_Msk			REG_BIT_MASK(CAN_F2R1_FB28_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 28 (`CANx_F2R1.FB28`) bit mask alias @def CAN_F2R1_FB28 */
#define CAN_F2R1_FB28				CAN_F2R1_FB28_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 29 (`CANx_F2R1.FB29`) bit position @def CAN_F2R1_FB29_Pos */
#define CAN_F2R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 2 word 1 bit 29 (`CANx_F2R1.FB29`) bit mask @def CAN_F2R1_FB29_Msk */
#define CAN_F2R1_FB29_Msk			REG_BIT_MASK(CAN_F2R1_FB29_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 29 (`CANx_F2R1.FB29`) bit mask alias @def CAN_F2R1_FB29 */
#define CAN_F2R1_FB29				CAN_F2R1_FB29_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 30 (`CANx_F2R1.FB30`) bit position @def CAN_F2R1_FB30_Pos */
#define CAN_F2R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 2 word 1 bit 30 (`CANx_F2R1.FB30`) bit mask @def CAN_F2R1_FB30_Msk */
#define CAN_F2R1_FB30_Msk			REG_BIT_MASK(CAN_F2R1_FB30_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 30 (`CANx_F2R1.FB30`) bit mask alias @def CAN_F2R1_FB30 */
#define CAN_F2R1_FB30				CAN_F2R1_FB30_Msk

/** @brief Acceptance-filter bank 2 word 1 bit 31 (`CANx_F2R1.FB31`) bit position @def CAN_F2R1_FB31_Pos */
#define CAN_F2R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 2 word 1 bit 31 (`CANx_F2R1.FB31`) bit mask @def CAN_F2R1_FB31_Msk */
#define CAN_F2R1_FB31_Msk			REG_BIT_MASK(CAN_F2R1_FB31_Pos)
/** @brief Acceptance-filter bank 2 word 1 bit 31 (`CANx_F2R1.FB31`) bit mask alias @def CAN_F2R1_FB31 */
#define CAN_F2R1_FB31				CAN_F2R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F3R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 3 word 1 bit 0 (`CANx_F3R1.FB0`) bit position @def CAN_F3R1_FB0_Pos */
#define CAN_F3R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 3 word 1 bit 0 (`CANx_F3R1.FB0`) bit mask @def CAN_F3R1_FB0_Msk */
#define CAN_F3R1_FB0_Msk			REG_BIT_MASK(CAN_F3R1_FB0_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 0 (`CANx_F3R1.FB0`) bit mask alias @def CAN_F3R1_FB0 */
#define CAN_F3R1_FB0				CAN_F3R1_FB0_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 1 (`CANx_F3R1.FB1`) bit position @def CAN_F3R1_FB1_Pos */
#define CAN_F3R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 3 word 1 bit 1 (`CANx_F3R1.FB1`) bit mask @def CAN_F3R1_FB1_Msk */
#define CAN_F3R1_FB1_Msk			REG_BIT_MASK(CAN_F3R1_FB1_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 1 (`CANx_F3R1.FB1`) bit mask alias @def CAN_F3R1_FB1 */
#define CAN_F3R1_FB1				CAN_F3R1_FB1_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 2 (`CANx_F3R1.FB2`) bit position @def CAN_F3R1_FB2_Pos */
#define CAN_F3R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 3 word 1 bit 2 (`CANx_F3R1.FB2`) bit mask @def CAN_F3R1_FB2_Msk */
#define CAN_F3R1_FB2_Msk			REG_BIT_MASK(CAN_F3R1_FB2_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 2 (`CANx_F3R1.FB2`) bit mask alias @def CAN_F3R1_FB2 */
#define CAN_F3R1_FB2				CAN_F3R1_FB2_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 3 (`CANx_F3R1.FB3`) bit position @def CAN_F3R1_FB3_Pos */
#define CAN_F3R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 3 word 1 bit 3 (`CANx_F3R1.FB3`) bit mask @def CAN_F3R1_FB3_Msk */
#define CAN_F3R1_FB3_Msk			REG_BIT_MASK(CAN_F3R1_FB3_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 3 (`CANx_F3R1.FB3`) bit mask alias @def CAN_F3R1_FB3 */
#define CAN_F3R1_FB3				CAN_F3R1_FB3_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 4 (`CANx_F3R1.FB4`) bit position @def CAN_F3R1_FB4_Pos */
#define CAN_F3R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 3 word 1 bit 4 (`CANx_F3R1.FB4`) bit mask @def CAN_F3R1_FB4_Msk */
#define CAN_F3R1_FB4_Msk			REG_BIT_MASK(CAN_F3R1_FB4_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 4 (`CANx_F3R1.FB4`) bit mask alias @def CAN_F3R1_FB4 */
#define CAN_F3R1_FB4				CAN_F3R1_FB4_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 5 (`CANx_F3R1.FB5`) bit position @def CAN_F3R1_FB5_Pos */
#define CAN_F3R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 3 word 1 bit 5 (`CANx_F3R1.FB5`) bit mask @def CAN_F3R1_FB5_Msk */
#define CAN_F3R1_FB5_Msk			REG_BIT_MASK(CAN_F3R1_FB5_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 5 (`CANx_F3R1.FB5`) bit mask alias @def CAN_F3R1_FB5 */
#define CAN_F3R1_FB5				CAN_F3R1_FB5_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 6 (`CANx_F3R1.FB6`) bit position @def CAN_F3R1_FB6_Pos */
#define CAN_F3R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 3 word 1 bit 6 (`CANx_F3R1.FB6`) bit mask @def CAN_F3R1_FB6_Msk */
#define CAN_F3R1_FB6_Msk			REG_BIT_MASK(CAN_F3R1_FB6_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 6 (`CANx_F3R1.FB6`) bit mask alias @def CAN_F3R1_FB6 */
#define CAN_F3R1_FB6				CAN_F3R1_FB6_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 7 (`CANx_F3R1.FB7`) bit position @def CAN_F3R1_FB7_Pos */
#define CAN_F3R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 3 word 1 bit 7 (`CANx_F3R1.FB7`) bit mask @def CAN_F3R1_FB7_Msk */
#define CAN_F3R1_FB7_Msk			REG_BIT_MASK(CAN_F3R1_FB7_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 7 (`CANx_F3R1.FB7`) bit mask alias @def CAN_F3R1_FB7 */
#define CAN_F3R1_FB7				CAN_F3R1_FB7_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 8 (`CANx_F3R1.FB8`) bit position @def CAN_F3R1_FB8_Pos */
#define CAN_F3R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 3 word 1 bit 8 (`CANx_F3R1.FB8`) bit mask @def CAN_F3R1_FB8_Msk */
#define CAN_F3R1_FB8_Msk			REG_BIT_MASK(CAN_F3R1_FB8_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 8 (`CANx_F3R1.FB8`) bit mask alias @def CAN_F3R1_FB8 */
#define CAN_F3R1_FB8				CAN_F3R1_FB8_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 9 (`CANx_F3R1.FB9`) bit position @def CAN_F3R1_FB9_Pos */
#define CAN_F3R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 3 word 1 bit 9 (`CANx_F3R1.FB9`) bit mask @def CAN_F3R1_FB9_Msk */
#define CAN_F3R1_FB9_Msk			REG_BIT_MASK(CAN_F3R1_FB9_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 9 (`CANx_F3R1.FB9`) bit mask alias @def CAN_F3R1_FB9 */
#define CAN_F3R1_FB9				CAN_F3R1_FB9_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 10 (`CANx_F3R1.FB10`) bit position @def CAN_F3R1_FB10_Pos */
#define CAN_F3R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 3 word 1 bit 10 (`CANx_F3R1.FB10`) bit mask @def CAN_F3R1_FB10_Msk */
#define CAN_F3R1_FB10_Msk			REG_BIT_MASK(CAN_F3R1_FB10_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 10 (`CANx_F3R1.FB10`) bit mask alias @def CAN_F3R1_FB10 */
#define CAN_F3R1_FB10				CAN_F3R1_FB10_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 11 (`CANx_F3R1.FB11`) bit position @def CAN_F3R1_FB11_Pos */
#define CAN_F3R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 3 word 1 bit 11 (`CANx_F3R1.FB11`) bit mask @def CAN_F3R1_FB11_Msk */
#define CAN_F3R1_FB11_Msk			REG_BIT_MASK(CAN_F3R1_FB11_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 11 (`CANx_F3R1.FB11`) bit mask alias @def CAN_F3R1_FB11 */
#define CAN_F3R1_FB11				CAN_F3R1_FB11_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 12 (`CANx_F3R1.FB12`) bit position @def CAN_F3R1_FB12_Pos */
#define CAN_F3R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 3 word 1 bit 12 (`CANx_F3R1.FB12`) bit mask @def CAN_F3R1_FB12_Msk */
#define CAN_F3R1_FB12_Msk			REG_BIT_MASK(CAN_F3R1_FB12_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 12 (`CANx_F3R1.FB12`) bit mask alias @def CAN_F3R1_FB12 */
#define CAN_F3R1_FB12				CAN_F3R1_FB12_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 13 (`CANx_F3R1.FB13`) bit position @def CAN_F3R1_FB13_Pos */
#define CAN_F3R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 3 word 1 bit 13 (`CANx_F3R1.FB13`) bit mask @def CAN_F3R1_FB13_Msk */
#define CAN_F3R1_FB13_Msk			REG_BIT_MASK(CAN_F3R1_FB13_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 13 (`CANx_F3R1.FB13`) bit mask alias @def CAN_F3R1_FB13 */
#define CAN_F3R1_FB13				CAN_F3R1_FB13_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 14 (`CANx_F3R1.FB14`) bit position @def CAN_F3R1_FB14_Pos */
#define CAN_F3R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 3 word 1 bit 14 (`CANx_F3R1.FB14`) bit mask @def CAN_F3R1_FB14_Msk */
#define CAN_F3R1_FB14_Msk			REG_BIT_MASK(CAN_F3R1_FB14_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 14 (`CANx_F3R1.FB14`) bit mask alias @def CAN_F3R1_FB14 */
#define CAN_F3R1_FB14				CAN_F3R1_FB14_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 15 (`CANx_F3R1.FB15`) bit position @def CAN_F3R1_FB15_Pos */
#define CAN_F3R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 3 word 1 bit 15 (`CANx_F3R1.FB15`) bit mask @def CAN_F3R1_FB15_Msk */
#define CAN_F3R1_FB15_Msk			REG_BIT_MASK(CAN_F3R1_FB15_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 15 (`CANx_F3R1.FB15`) bit mask alias @def CAN_F3R1_FB15 */
#define CAN_F3R1_FB15				CAN_F3R1_FB15_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 16 (`CANx_F3R1.FB16`) bit position @def CAN_F3R1_FB16_Pos */
#define CAN_F3R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 3 word 1 bit 16 (`CANx_F3R1.FB16`) bit mask @def CAN_F3R1_FB16_Msk */
#define CAN_F3R1_FB16_Msk			REG_BIT_MASK(CAN_F3R1_FB16_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 16 (`CANx_F3R1.FB16`) bit mask alias @def CAN_F3R1_FB16 */
#define CAN_F3R1_FB16				CAN_F3R1_FB16_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 17 (`CANx_F3R1.FB17`) bit position @def CAN_F3R1_FB17_Pos */
#define CAN_F3R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 3 word 1 bit 17 (`CANx_F3R1.FB17`) bit mask @def CAN_F3R1_FB17_Msk */
#define CAN_F3R1_FB17_Msk			REG_BIT_MASK(CAN_F3R1_FB17_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 17 (`CANx_F3R1.FB17`) bit mask alias @def CAN_F3R1_FB17 */
#define CAN_F3R1_FB17				CAN_F3R1_FB17_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 18 (`CANx_F3R1.FB18`) bit position @def CAN_F3R1_FB18_Pos */
#define CAN_F3R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 3 word 1 bit 18 (`CANx_F3R1.FB18`) bit mask @def CAN_F3R1_FB18_Msk */
#define CAN_F3R1_FB18_Msk			REG_BIT_MASK(CAN_F3R1_FB18_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 18 (`CANx_F3R1.FB18`) bit mask alias @def CAN_F3R1_FB18 */
#define CAN_F3R1_FB18				CAN_F3R1_FB18_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 19 (`CANx_F3R1.FB19`) bit position @def CAN_F3R1_FB19_Pos */
#define CAN_F3R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 3 word 1 bit 19 (`CANx_F3R1.FB19`) bit mask @def CAN_F3R1_FB19_Msk */
#define CAN_F3R1_FB19_Msk			REG_BIT_MASK(CAN_F3R1_FB19_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 19 (`CANx_F3R1.FB19`) bit mask alias @def CAN_F3R1_FB19 */
#define CAN_F3R1_FB19				CAN_F3R1_FB19_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 20 (`CANx_F3R1.FB20`) bit position @def CAN_F3R1_FB20_Pos */
#define CAN_F3R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 3 word 1 bit 20 (`CANx_F3R1.FB20`) bit mask @def CAN_F3R1_FB20_Msk */
#define CAN_F3R1_FB20_Msk			REG_BIT_MASK(CAN_F3R1_FB20_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 20 (`CANx_F3R1.FB20`) bit mask alias @def CAN_F3R1_FB20 */
#define CAN_F3R1_FB20				CAN_F3R1_FB20_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 21 (`CANx_F3R1.FB21`) bit position @def CAN_F3R1_FB21_Pos */
#define CAN_F3R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 3 word 1 bit 21 (`CANx_F3R1.FB21`) bit mask @def CAN_F3R1_FB21_Msk */
#define CAN_F3R1_FB21_Msk			REG_BIT_MASK(CAN_F3R1_FB21_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 21 (`CANx_F3R1.FB21`) bit mask alias @def CAN_F3R1_FB21 */
#define CAN_F3R1_FB21				CAN_F3R1_FB21_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 22 (`CANx_F3R1.FB22`) bit position @def CAN_F3R1_FB22_Pos */
#define CAN_F3R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 3 word 1 bit 22 (`CANx_F3R1.FB22`) bit mask @def CAN_F3R1_FB22_Msk */
#define CAN_F3R1_FB22_Msk			REG_BIT_MASK(CAN_F3R1_FB22_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 22 (`CANx_F3R1.FB22`) bit mask alias @def CAN_F3R1_FB22 */
#define CAN_F3R1_FB22				CAN_F3R1_FB22_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 23 (`CANx_F3R1.FB23`) bit position @def CAN_F3R1_FB23_Pos */
#define CAN_F3R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 3 word 1 bit 23 (`CANx_F3R1.FB23`) bit mask @def CAN_F3R1_FB23_Msk */
#define CAN_F3R1_FB23_Msk			REG_BIT_MASK(CAN_F3R1_FB23_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 23 (`CANx_F3R1.FB23`) bit mask alias @def CAN_F3R1_FB23 */
#define CAN_F3R1_FB23				CAN_F3R1_FB23_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 24 (`CANx_F3R1.FB24`) bit position @def CAN_F3R1_FB24_Pos */
#define CAN_F3R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 3 word 1 bit 24 (`CANx_F3R1.FB24`) bit mask @def CAN_F3R1_FB24_Msk */
#define CAN_F3R1_FB24_Msk			REG_BIT_MASK(CAN_F3R1_FB24_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 24 (`CANx_F3R1.FB24`) bit mask alias @def CAN_F3R1_FB24 */
#define CAN_F3R1_FB24				CAN_F3R1_FB24_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 25 (`CANx_F3R1.FB25`) bit position @def CAN_F3R1_FB25_Pos */
#define CAN_F3R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 3 word 1 bit 25 (`CANx_F3R1.FB25`) bit mask @def CAN_F3R1_FB25_Msk */
#define CAN_F3R1_FB25_Msk			REG_BIT_MASK(CAN_F3R1_FB25_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 25 (`CANx_F3R1.FB25`) bit mask alias @def CAN_F3R1_FB25 */
#define CAN_F3R1_FB25				CAN_F3R1_FB25_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 26 (`CANx_F3R1.FB26`) bit position @def CAN_F3R1_FB26_Pos */
#define CAN_F3R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 3 word 1 bit 26 (`CANx_F3R1.FB26`) bit mask @def CAN_F3R1_FB26_Msk */
#define CAN_F3R1_FB26_Msk			REG_BIT_MASK(CAN_F3R1_FB26_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 26 (`CANx_F3R1.FB26`) bit mask alias @def CAN_F3R1_FB26 */
#define CAN_F3R1_FB26				CAN_F3R1_FB26_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 27 (`CANx_F3R1.FB27`) bit position @def CAN_F3R1_FB27_Pos */
#define CAN_F3R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 3 word 1 bit 27 (`CANx_F3R1.FB27`) bit mask @def CAN_F3R1_FB27_Msk */
#define CAN_F3R1_FB27_Msk			REG_BIT_MASK(CAN_F3R1_FB27_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 27 (`CANx_F3R1.FB27`) bit mask alias @def CAN_F3R1_FB27 */
#define CAN_F3R1_FB27				CAN_F3R1_FB27_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 28 (`CANx_F3R1.FB28`) bit position @def CAN_F3R1_FB28_Pos */
#define CAN_F3R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 3 word 1 bit 28 (`CANx_F3R1.FB28`) bit mask @def CAN_F3R1_FB28_Msk */
#define CAN_F3R1_FB28_Msk			REG_BIT_MASK(CAN_F3R1_FB28_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 28 (`CANx_F3R1.FB28`) bit mask alias @def CAN_F3R1_FB28 */
#define CAN_F3R1_FB28				CAN_F3R1_FB28_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 29 (`CANx_F3R1.FB29`) bit position @def CAN_F3R1_FB29_Pos */
#define CAN_F3R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 3 word 1 bit 29 (`CANx_F3R1.FB29`) bit mask @def CAN_F3R1_FB29_Msk */
#define CAN_F3R1_FB29_Msk			REG_BIT_MASK(CAN_F3R1_FB29_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 29 (`CANx_F3R1.FB29`) bit mask alias @def CAN_F3R1_FB29 */
#define CAN_F3R1_FB29				CAN_F3R1_FB29_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 30 (`CANx_F3R1.FB30`) bit position @def CAN_F3R1_FB30_Pos */
#define CAN_F3R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 3 word 1 bit 30 (`CANx_F3R1.FB30`) bit mask @def CAN_F3R1_FB30_Msk */
#define CAN_F3R1_FB30_Msk			REG_BIT_MASK(CAN_F3R1_FB30_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 30 (`CANx_F3R1.FB30`) bit mask alias @def CAN_F3R1_FB30 */
#define CAN_F3R1_FB30				CAN_F3R1_FB30_Msk

/** @brief Acceptance-filter bank 3 word 1 bit 31 (`CANx_F3R1.FB31`) bit position @def CAN_F3R1_FB31_Pos */
#define CAN_F3R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 3 word 1 bit 31 (`CANx_F3R1.FB31`) bit mask @def CAN_F3R1_FB31_Msk */
#define CAN_F3R1_FB31_Msk			REG_BIT_MASK(CAN_F3R1_FB31_Pos)
/** @brief Acceptance-filter bank 3 word 1 bit 31 (`CANx_F3R1.FB31`) bit mask alias @def CAN_F3R1_FB31 */
#define CAN_F3R1_FB31				CAN_F3R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F4R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 4 word 1 bit 0 (`CANx_F4R1.FB0`) bit position @def CAN_F4R1_FB0_Pos */
#define CAN_F4R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 4 word 1 bit 0 (`CANx_F4R1.FB0`) bit mask @def CAN_F4R1_FB0_Msk */
#define CAN_F4R1_FB0_Msk			REG_BIT_MASK(CAN_F4R1_FB0_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 0 (`CANx_F4R1.FB0`) bit mask alias @def CAN_F4R1_FB0 */
#define CAN_F4R1_FB0				CAN_F4R1_FB0_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 1 (`CANx_F4R1.FB1`) bit position @def CAN_F4R1_FB1_Pos */
#define CAN_F4R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 4 word 1 bit 1 (`CANx_F4R1.FB1`) bit mask @def CAN_F4R1_FB1_Msk */
#define CAN_F4R1_FB1_Msk			REG_BIT_MASK(CAN_F4R1_FB1_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 1 (`CANx_F4R1.FB1`) bit mask alias @def CAN_F4R1_FB1 */
#define CAN_F4R1_FB1				CAN_F4R1_FB1_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 2 (`CANx_F4R1.FB2`) bit position @def CAN_F4R1_FB2_Pos */
#define CAN_F4R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 4 word 1 bit 2 (`CANx_F4R1.FB2`) bit mask @def CAN_F4R1_FB2_Msk */
#define CAN_F4R1_FB2_Msk			REG_BIT_MASK(CAN_F4R1_FB2_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 2 (`CANx_F4R1.FB2`) bit mask alias @def CAN_F4R1_FB2 */
#define CAN_F4R1_FB2				CAN_F4R1_FB2_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 3 (`CANx_F4R1.FB3`) bit position @def CAN_F4R1_FB3_Pos */
#define CAN_F4R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 4 word 1 bit 3 (`CANx_F4R1.FB3`) bit mask @def CAN_F4R1_FB3_Msk */
#define CAN_F4R1_FB3_Msk			REG_BIT_MASK(CAN_F4R1_FB3_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 3 (`CANx_F4R1.FB3`) bit mask alias @def CAN_F4R1_FB3 */
#define CAN_F4R1_FB3				CAN_F4R1_FB3_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 4 (`CANx_F4R1.FB4`) bit position @def CAN_F4R1_FB4_Pos */
#define CAN_F4R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 4 word 1 bit 4 (`CANx_F4R1.FB4`) bit mask @def CAN_F4R1_FB4_Msk */
#define CAN_F4R1_FB4_Msk			REG_BIT_MASK(CAN_F4R1_FB4_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 4 (`CANx_F4R1.FB4`) bit mask alias @def CAN_F4R1_FB4 */
#define CAN_F4R1_FB4				CAN_F4R1_FB4_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 5 (`CANx_F4R1.FB5`) bit position @def CAN_F4R1_FB5_Pos */
#define CAN_F4R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 4 word 1 bit 5 (`CANx_F4R1.FB5`) bit mask @def CAN_F4R1_FB5_Msk */
#define CAN_F4R1_FB5_Msk			REG_BIT_MASK(CAN_F4R1_FB5_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 5 (`CANx_F4R1.FB5`) bit mask alias @def CAN_F4R1_FB5 */
#define CAN_F4R1_FB5				CAN_F4R1_FB5_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 6 (`CANx_F4R1.FB6`) bit position @def CAN_F4R1_FB6_Pos */
#define CAN_F4R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 4 word 1 bit 6 (`CANx_F4R1.FB6`) bit mask @def CAN_F4R1_FB6_Msk */
#define CAN_F4R1_FB6_Msk			REG_BIT_MASK(CAN_F4R1_FB6_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 6 (`CANx_F4R1.FB6`) bit mask alias @def CAN_F4R1_FB6 */
#define CAN_F4R1_FB6				CAN_F4R1_FB6_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 7 (`CANx_F4R1.FB7`) bit position @def CAN_F4R1_FB7_Pos */
#define CAN_F4R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 4 word 1 bit 7 (`CANx_F4R1.FB7`) bit mask @def CAN_F4R1_FB7_Msk */
#define CAN_F4R1_FB7_Msk			REG_BIT_MASK(CAN_F4R1_FB7_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 7 (`CANx_F4R1.FB7`) bit mask alias @def CAN_F4R1_FB7 */
#define CAN_F4R1_FB7				CAN_F4R1_FB7_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 8 (`CANx_F4R1.FB8`) bit position @def CAN_F4R1_FB8_Pos */
#define CAN_F4R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 4 word 1 bit 8 (`CANx_F4R1.FB8`) bit mask @def CAN_F4R1_FB8_Msk */
#define CAN_F4R1_FB8_Msk			REG_BIT_MASK(CAN_F4R1_FB8_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 8 (`CANx_F4R1.FB8`) bit mask alias @def CAN_F4R1_FB8 */
#define CAN_F4R1_FB8				CAN_F4R1_FB8_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 9 (`CANx_F4R1.FB9`) bit position @def CAN_F4R1_FB9_Pos */
#define CAN_F4R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 4 word 1 bit 9 (`CANx_F4R1.FB9`) bit mask @def CAN_F4R1_FB9_Msk */
#define CAN_F4R1_FB9_Msk			REG_BIT_MASK(CAN_F4R1_FB9_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 9 (`CANx_F4R1.FB9`) bit mask alias @def CAN_F4R1_FB9 */
#define CAN_F4R1_FB9				CAN_F4R1_FB9_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 10 (`CANx_F4R1.FB10`) bit position @def CAN_F4R1_FB10_Pos */
#define CAN_F4R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 4 word 1 bit 10 (`CANx_F4R1.FB10`) bit mask @def CAN_F4R1_FB10_Msk */
#define CAN_F4R1_FB10_Msk			REG_BIT_MASK(CAN_F4R1_FB10_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 10 (`CANx_F4R1.FB10`) bit mask alias @def CAN_F4R1_FB10 */
#define CAN_F4R1_FB10				CAN_F4R1_FB10_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 11 (`CANx_F4R1.FB11`) bit position @def CAN_F4R1_FB11_Pos */
#define CAN_F4R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 4 word 1 bit 11 (`CANx_F4R1.FB11`) bit mask @def CAN_F4R1_FB11_Msk */
#define CAN_F4R1_FB11_Msk			REG_BIT_MASK(CAN_F4R1_FB11_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 11 (`CANx_F4R1.FB11`) bit mask alias @def CAN_F4R1_FB11 */
#define CAN_F4R1_FB11				CAN_F4R1_FB11_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 12 (`CANx_F4R1.FB12`) bit position @def CAN_F4R1_FB12_Pos */
#define CAN_F4R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 4 word 1 bit 12 (`CANx_F4R1.FB12`) bit mask @def CAN_F4R1_FB12_Msk */
#define CAN_F4R1_FB12_Msk			REG_BIT_MASK(CAN_F4R1_FB12_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 12 (`CANx_F4R1.FB12`) bit mask alias @def CAN_F4R1_FB12 */
#define CAN_F4R1_FB12				CAN_F4R1_FB12_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 13 (`CANx_F4R1.FB13`) bit position @def CAN_F4R1_FB13_Pos */
#define CAN_F4R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 4 word 1 bit 13 (`CANx_F4R1.FB13`) bit mask @def CAN_F4R1_FB13_Msk */
#define CAN_F4R1_FB13_Msk			REG_BIT_MASK(CAN_F4R1_FB13_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 13 (`CANx_F4R1.FB13`) bit mask alias @def CAN_F4R1_FB13 */
#define CAN_F4R1_FB13				CAN_F4R1_FB13_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 14 (`CANx_F4R1.FB14`) bit position @def CAN_F4R1_FB14_Pos */
#define CAN_F4R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 4 word 1 bit 14 (`CANx_F4R1.FB14`) bit mask @def CAN_F4R1_FB14_Msk */
#define CAN_F4R1_FB14_Msk			REG_BIT_MASK(CAN_F4R1_FB14_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 14 (`CANx_F4R1.FB14`) bit mask alias @def CAN_F4R1_FB14 */
#define CAN_F4R1_FB14				CAN_F4R1_FB14_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 15 (`CANx_F4R1.FB15`) bit position @def CAN_F4R1_FB15_Pos */
#define CAN_F4R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 4 word 1 bit 15 (`CANx_F4R1.FB15`) bit mask @def CAN_F4R1_FB15_Msk */
#define CAN_F4R1_FB15_Msk			REG_BIT_MASK(CAN_F4R1_FB15_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 15 (`CANx_F4R1.FB15`) bit mask alias @def CAN_F4R1_FB15 */
#define CAN_F4R1_FB15				CAN_F4R1_FB15_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 16 (`CANx_F4R1.FB16`) bit position @def CAN_F4R1_FB16_Pos */
#define CAN_F4R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 4 word 1 bit 16 (`CANx_F4R1.FB16`) bit mask @def CAN_F4R1_FB16_Msk */
#define CAN_F4R1_FB16_Msk			REG_BIT_MASK(CAN_F4R1_FB16_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 16 (`CANx_F4R1.FB16`) bit mask alias @def CAN_F4R1_FB16 */
#define CAN_F4R1_FB16				CAN_F4R1_FB16_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 17 (`CANx_F4R1.FB17`) bit position @def CAN_F4R1_FB17_Pos */
#define CAN_F4R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 4 word 1 bit 17 (`CANx_F4R1.FB17`) bit mask @def CAN_F4R1_FB17_Msk */
#define CAN_F4R1_FB17_Msk			REG_BIT_MASK(CAN_F4R1_FB17_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 17 (`CANx_F4R1.FB17`) bit mask alias @def CAN_F4R1_FB17 */
#define CAN_F4R1_FB17				CAN_F4R1_FB17_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 18 (`CANx_F4R1.FB18`) bit position @def CAN_F4R1_FB18_Pos */
#define CAN_F4R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 4 word 1 bit 18 (`CANx_F4R1.FB18`) bit mask @def CAN_F4R1_FB18_Msk */
#define CAN_F4R1_FB18_Msk			REG_BIT_MASK(CAN_F4R1_FB18_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 18 (`CANx_F4R1.FB18`) bit mask alias @def CAN_F4R1_FB18 */
#define CAN_F4R1_FB18				CAN_F4R1_FB18_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 19 (`CANx_F4R1.FB19`) bit position @def CAN_F4R1_FB19_Pos */
#define CAN_F4R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 4 word 1 bit 19 (`CANx_F4R1.FB19`) bit mask @def CAN_F4R1_FB19_Msk */
#define CAN_F4R1_FB19_Msk			REG_BIT_MASK(CAN_F4R1_FB19_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 19 (`CANx_F4R1.FB19`) bit mask alias @def CAN_F4R1_FB19 */
#define CAN_F4R1_FB19				CAN_F4R1_FB19_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 20 (`CANx_F4R1.FB20`) bit position @def CAN_F4R1_FB20_Pos */
#define CAN_F4R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 4 word 1 bit 20 (`CANx_F4R1.FB20`) bit mask @def CAN_F4R1_FB20_Msk */
#define CAN_F4R1_FB20_Msk			REG_BIT_MASK(CAN_F4R1_FB20_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 20 (`CANx_F4R1.FB20`) bit mask alias @def CAN_F4R1_FB20 */
#define CAN_F4R1_FB20				CAN_F4R1_FB20_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 21 (`CANx_F4R1.FB21`) bit position @def CAN_F4R1_FB21_Pos */
#define CAN_F4R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 4 word 1 bit 21 (`CANx_F4R1.FB21`) bit mask @def CAN_F4R1_FB21_Msk */
#define CAN_F4R1_FB21_Msk			REG_BIT_MASK(CAN_F4R1_FB21_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 21 (`CANx_F4R1.FB21`) bit mask alias @def CAN_F4R1_FB21 */
#define CAN_F4R1_FB21				CAN_F4R1_FB21_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 22 (`CANx_F4R1.FB22`) bit position @def CAN_F4R1_FB22_Pos */
#define CAN_F4R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 4 word 1 bit 22 (`CANx_F4R1.FB22`) bit mask @def CAN_F4R1_FB22_Msk */
#define CAN_F4R1_FB22_Msk			REG_BIT_MASK(CAN_F4R1_FB22_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 22 (`CANx_F4R1.FB22`) bit mask alias @def CAN_F4R1_FB22 */
#define CAN_F4R1_FB22				CAN_F4R1_FB22_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 23 (`CANx_F4R1.FB23`) bit position @def CAN_F4R1_FB23_Pos */
#define CAN_F4R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 4 word 1 bit 23 (`CANx_F4R1.FB23`) bit mask @def CAN_F4R1_FB23_Msk */
#define CAN_F4R1_FB23_Msk			REG_BIT_MASK(CAN_F4R1_FB23_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 23 (`CANx_F4R1.FB23`) bit mask alias @def CAN_F4R1_FB23 */
#define CAN_F4R1_FB23				CAN_F4R1_FB23_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 24 (`CANx_F4R1.FB24`) bit position @def CAN_F4R1_FB24_Pos */
#define CAN_F4R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 4 word 1 bit 24 (`CANx_F4R1.FB24`) bit mask @def CAN_F4R1_FB24_Msk */
#define CAN_F4R1_FB24_Msk			REG_BIT_MASK(CAN_F4R1_FB24_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 24 (`CANx_F4R1.FB24`) bit mask alias @def CAN_F4R1_FB24 */
#define CAN_F4R1_FB24				CAN_F4R1_FB24_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 25 (`CANx_F4R1.FB25`) bit position @def CAN_F4R1_FB25_Pos */
#define CAN_F4R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 4 word 1 bit 25 (`CANx_F4R1.FB25`) bit mask @def CAN_F4R1_FB25_Msk */
#define CAN_F4R1_FB25_Msk			REG_BIT_MASK(CAN_F4R1_FB25_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 25 (`CANx_F4R1.FB25`) bit mask alias @def CAN_F4R1_FB25 */
#define CAN_F4R1_FB25				CAN_F4R1_FB25_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 26 (`CANx_F4R1.FB26`) bit position @def CAN_F4R1_FB26_Pos */
#define CAN_F4R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 4 word 1 bit 26 (`CANx_F4R1.FB26`) bit mask @def CAN_F4R1_FB26_Msk */
#define CAN_F4R1_FB26_Msk			REG_BIT_MASK(CAN_F4R1_FB26_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 26 (`CANx_F4R1.FB26`) bit mask alias @def CAN_F4R1_FB26 */
#define CAN_F4R1_FB26				CAN_F4R1_FB26_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 27 (`CANx_F4R1.FB27`) bit position @def CAN_F4R1_FB27_Pos */
#define CAN_F4R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 4 word 1 bit 27 (`CANx_F4R1.FB27`) bit mask @def CAN_F4R1_FB27_Msk */
#define CAN_F4R1_FB27_Msk			REG_BIT_MASK(CAN_F4R1_FB27_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 27 (`CANx_F4R1.FB27`) bit mask alias @def CAN_F4R1_FB27 */
#define CAN_F4R1_FB27				CAN_F4R1_FB27_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 28 (`CANx_F4R1.FB28`) bit position @def CAN_F4R1_FB28_Pos */
#define CAN_F4R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 4 word 1 bit 28 (`CANx_F4R1.FB28`) bit mask @def CAN_F4R1_FB28_Msk */
#define CAN_F4R1_FB28_Msk			REG_BIT_MASK(CAN_F4R1_FB28_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 28 (`CANx_F4R1.FB28`) bit mask alias @def CAN_F4R1_FB28 */
#define CAN_F4R1_FB28				CAN_F4R1_FB28_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 29 (`CANx_F4R1.FB29`) bit position @def CAN_F4R1_FB29_Pos */
#define CAN_F4R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 4 word 1 bit 29 (`CANx_F4R1.FB29`) bit mask @def CAN_F4R1_FB29_Msk */
#define CAN_F4R1_FB29_Msk			REG_BIT_MASK(CAN_F4R1_FB29_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 29 (`CANx_F4R1.FB29`) bit mask alias @def CAN_F4R1_FB29 */
#define CAN_F4R1_FB29				CAN_F4R1_FB29_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 30 (`CANx_F4R1.FB30`) bit position @def CAN_F4R1_FB30_Pos */
#define CAN_F4R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 4 word 1 bit 30 (`CANx_F4R1.FB30`) bit mask @def CAN_F4R1_FB30_Msk */
#define CAN_F4R1_FB30_Msk			REG_BIT_MASK(CAN_F4R1_FB30_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 30 (`CANx_F4R1.FB30`) bit mask alias @def CAN_F4R1_FB30 */
#define CAN_F4R1_FB30				CAN_F4R1_FB30_Msk

/** @brief Acceptance-filter bank 4 word 1 bit 31 (`CANx_F4R1.FB31`) bit position @def CAN_F4R1_FB31_Pos */
#define CAN_F4R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 4 word 1 bit 31 (`CANx_F4R1.FB31`) bit mask @def CAN_F4R1_FB31_Msk */
#define CAN_F4R1_FB31_Msk			REG_BIT_MASK(CAN_F4R1_FB31_Pos)
/** @brief Acceptance-filter bank 4 word 1 bit 31 (`CANx_F4R1.FB31`) bit mask alias @def CAN_F4R1_FB31 */
#define CAN_F4R1_FB31				CAN_F4R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F5R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 5 word 1 bit 0 (`CANx_F5R1.FB0`) bit position @def CAN_F5R1_FB0_Pos */
#define CAN_F5R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 5 word 1 bit 0 (`CANx_F5R1.FB0`) bit mask @def CAN_F5R1_FB0_Msk */
#define CAN_F5R1_FB0_Msk			REG_BIT_MASK(CAN_F5R1_FB0_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 0 (`CANx_F5R1.FB0`) bit mask alias @def CAN_F5R1_FB0 */
#define CAN_F5R1_FB0				CAN_F5R1_FB0_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 1 (`CANx_F5R1.FB1`) bit position @def CAN_F5R1_FB1_Pos */
#define CAN_F5R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 5 word 1 bit 1 (`CANx_F5R1.FB1`) bit mask @def CAN_F5R1_FB1_Msk */
#define CAN_F5R1_FB1_Msk			REG_BIT_MASK(CAN_F5R1_FB1_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 1 (`CANx_F5R1.FB1`) bit mask alias @def CAN_F5R1_FB1 */
#define CAN_F5R1_FB1				CAN_F5R1_FB1_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 2 (`CANx_F5R1.FB2`) bit position @def CAN_F5R1_FB2_Pos */
#define CAN_F5R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 5 word 1 bit 2 (`CANx_F5R1.FB2`) bit mask @def CAN_F5R1_FB2_Msk */
#define CAN_F5R1_FB2_Msk			REG_BIT_MASK(CAN_F5R1_FB2_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 2 (`CANx_F5R1.FB2`) bit mask alias @def CAN_F5R1_FB2 */
#define CAN_F5R1_FB2				CAN_F5R1_FB2_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 3 (`CANx_F5R1.FB3`) bit position @def CAN_F5R1_FB3_Pos */
#define CAN_F5R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 5 word 1 bit 3 (`CANx_F5R1.FB3`) bit mask @def CAN_F5R1_FB3_Msk */
#define CAN_F5R1_FB3_Msk			REG_BIT_MASK(CAN_F5R1_FB3_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 3 (`CANx_F5R1.FB3`) bit mask alias @def CAN_F5R1_FB3 */
#define CAN_F5R1_FB3				CAN_F5R1_FB3_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 4 (`CANx_F5R1.FB4`) bit position @def CAN_F5R1_FB4_Pos */
#define CAN_F5R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 5 word 1 bit 4 (`CANx_F5R1.FB4`) bit mask @def CAN_F5R1_FB4_Msk */
#define CAN_F5R1_FB4_Msk			REG_BIT_MASK(CAN_F5R1_FB4_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 4 (`CANx_F5R1.FB4`) bit mask alias @def CAN_F5R1_FB4 */
#define CAN_F5R1_FB4				CAN_F5R1_FB4_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 5 (`CANx_F5R1.FB5`) bit position @def CAN_F5R1_FB5_Pos */
#define CAN_F5R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 5 word 1 bit 5 (`CANx_F5R1.FB5`) bit mask @def CAN_F5R1_FB5_Msk */
#define CAN_F5R1_FB5_Msk			REG_BIT_MASK(CAN_F5R1_FB5_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 5 (`CANx_F5R1.FB5`) bit mask alias @def CAN_F5R1_FB5 */
#define CAN_F5R1_FB5				CAN_F5R1_FB5_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 6 (`CANx_F5R1.FB6`) bit position @def CAN_F5R1_FB6_Pos */
#define CAN_F5R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 5 word 1 bit 6 (`CANx_F5R1.FB6`) bit mask @def CAN_F5R1_FB6_Msk */
#define CAN_F5R1_FB6_Msk			REG_BIT_MASK(CAN_F5R1_FB6_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 6 (`CANx_F5R1.FB6`) bit mask alias @def CAN_F5R1_FB6 */
#define CAN_F5R1_FB6				CAN_F5R1_FB6_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 7 (`CANx_F5R1.FB7`) bit position @def CAN_F5R1_FB7_Pos */
#define CAN_F5R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 5 word 1 bit 7 (`CANx_F5R1.FB7`) bit mask @def CAN_F5R1_FB7_Msk */
#define CAN_F5R1_FB7_Msk			REG_BIT_MASK(CAN_F5R1_FB7_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 7 (`CANx_F5R1.FB7`) bit mask alias @def CAN_F5R1_FB7 */
#define CAN_F5R1_FB7				CAN_F5R1_FB7_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 8 (`CANx_F5R1.FB8`) bit position @def CAN_F5R1_FB8_Pos */
#define CAN_F5R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 5 word 1 bit 8 (`CANx_F5R1.FB8`) bit mask @def CAN_F5R1_FB8_Msk */
#define CAN_F5R1_FB8_Msk			REG_BIT_MASK(CAN_F5R1_FB8_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 8 (`CANx_F5R1.FB8`) bit mask alias @def CAN_F5R1_FB8 */
#define CAN_F5R1_FB8				CAN_F5R1_FB8_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 9 (`CANx_F5R1.FB9`) bit position @def CAN_F5R1_FB9_Pos */
#define CAN_F5R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 5 word 1 bit 9 (`CANx_F5R1.FB9`) bit mask @def CAN_F5R1_FB9_Msk */
#define CAN_F5R1_FB9_Msk			REG_BIT_MASK(CAN_F5R1_FB9_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 9 (`CANx_F5R1.FB9`) bit mask alias @def CAN_F5R1_FB9 */
#define CAN_F5R1_FB9				CAN_F5R1_FB9_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 10 (`CANx_F5R1.FB10`) bit position @def CAN_F5R1_FB10_Pos */
#define CAN_F5R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 5 word 1 bit 10 (`CANx_F5R1.FB10`) bit mask @def CAN_F5R1_FB10_Msk */
#define CAN_F5R1_FB10_Msk			REG_BIT_MASK(CAN_F5R1_FB10_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 10 (`CANx_F5R1.FB10`) bit mask alias @def CAN_F5R1_FB10 */
#define CAN_F5R1_FB10				CAN_F5R1_FB10_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 11 (`CANx_F5R1.FB11`) bit position @def CAN_F5R1_FB11_Pos */
#define CAN_F5R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 5 word 1 bit 11 (`CANx_F5R1.FB11`) bit mask @def CAN_F5R1_FB11_Msk */
#define CAN_F5R1_FB11_Msk			REG_BIT_MASK(CAN_F5R1_FB11_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 11 (`CANx_F5R1.FB11`) bit mask alias @def CAN_F5R1_FB11 */
#define CAN_F5R1_FB11				CAN_F5R1_FB11_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 12 (`CANx_F5R1.FB12`) bit position @def CAN_F5R1_FB12_Pos */
#define CAN_F5R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 5 word 1 bit 12 (`CANx_F5R1.FB12`) bit mask @def CAN_F5R1_FB12_Msk */
#define CAN_F5R1_FB12_Msk			REG_BIT_MASK(CAN_F5R1_FB12_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 12 (`CANx_F5R1.FB12`) bit mask alias @def CAN_F5R1_FB12 */
#define CAN_F5R1_FB12				CAN_F5R1_FB12_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 13 (`CANx_F5R1.FB13`) bit position @def CAN_F5R1_FB13_Pos */
#define CAN_F5R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 5 word 1 bit 13 (`CANx_F5R1.FB13`) bit mask @def CAN_F5R1_FB13_Msk */
#define CAN_F5R1_FB13_Msk			REG_BIT_MASK(CAN_F5R1_FB13_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 13 (`CANx_F5R1.FB13`) bit mask alias @def CAN_F5R1_FB13 */
#define CAN_F5R1_FB13				CAN_F5R1_FB13_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 14 (`CANx_F5R1.FB14`) bit position @def CAN_F5R1_FB14_Pos */
#define CAN_F5R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 5 word 1 bit 14 (`CANx_F5R1.FB14`) bit mask @def CAN_F5R1_FB14_Msk */
#define CAN_F5R1_FB14_Msk			REG_BIT_MASK(CAN_F5R1_FB14_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 14 (`CANx_F5R1.FB14`) bit mask alias @def CAN_F5R1_FB14 */
#define CAN_F5R1_FB14				CAN_F5R1_FB14_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 15 (`CANx_F5R1.FB15`) bit position @def CAN_F5R1_FB15_Pos */
#define CAN_F5R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 5 word 1 bit 15 (`CANx_F5R1.FB15`) bit mask @def CAN_F5R1_FB15_Msk */
#define CAN_F5R1_FB15_Msk			REG_BIT_MASK(CAN_F5R1_FB15_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 15 (`CANx_F5R1.FB15`) bit mask alias @def CAN_F5R1_FB15 */
#define CAN_F5R1_FB15				CAN_F5R1_FB15_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 16 (`CANx_F5R1.FB16`) bit position @def CAN_F5R1_FB16_Pos */
#define CAN_F5R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 5 word 1 bit 16 (`CANx_F5R1.FB16`) bit mask @def CAN_F5R1_FB16_Msk */
#define CAN_F5R1_FB16_Msk			REG_BIT_MASK(CAN_F5R1_FB16_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 16 (`CANx_F5R1.FB16`) bit mask alias @def CAN_F5R1_FB16 */
#define CAN_F5R1_FB16				CAN_F5R1_FB16_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 17 (`CANx_F5R1.FB17`) bit position @def CAN_F5R1_FB17_Pos */
#define CAN_F5R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 5 word 1 bit 17 (`CANx_F5R1.FB17`) bit mask @def CAN_F5R1_FB17_Msk */
#define CAN_F5R1_FB17_Msk			REG_BIT_MASK(CAN_F5R1_FB17_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 17 (`CANx_F5R1.FB17`) bit mask alias @def CAN_F5R1_FB17 */
#define CAN_F5R1_FB17				CAN_F5R1_FB17_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 18 (`CANx_F5R1.FB18`) bit position @def CAN_F5R1_FB18_Pos */
#define CAN_F5R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 5 word 1 bit 18 (`CANx_F5R1.FB18`) bit mask @def CAN_F5R1_FB18_Msk */
#define CAN_F5R1_FB18_Msk			REG_BIT_MASK(CAN_F5R1_FB18_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 18 (`CANx_F5R1.FB18`) bit mask alias @def CAN_F5R1_FB18 */
#define CAN_F5R1_FB18				CAN_F5R1_FB18_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 19 (`CANx_F5R1.FB19`) bit position @def CAN_F5R1_FB19_Pos */
#define CAN_F5R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 5 word 1 bit 19 (`CANx_F5R1.FB19`) bit mask @def CAN_F5R1_FB19_Msk */
#define CAN_F5R1_FB19_Msk			REG_BIT_MASK(CAN_F5R1_FB19_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 19 (`CANx_F5R1.FB19`) bit mask alias @def CAN_F5R1_FB19 */
#define CAN_F5R1_FB19				CAN_F5R1_FB19_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 20 (`CANx_F5R1.FB20`) bit position @def CAN_F5R1_FB20_Pos */
#define CAN_F5R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 5 word 1 bit 20 (`CANx_F5R1.FB20`) bit mask @def CAN_F5R1_FB20_Msk */
#define CAN_F5R1_FB20_Msk			REG_BIT_MASK(CAN_F5R1_FB20_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 20 (`CANx_F5R1.FB20`) bit mask alias @def CAN_F5R1_FB20 */
#define CAN_F5R1_FB20				CAN_F5R1_FB20_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 21 (`CANx_F5R1.FB21`) bit position @def CAN_F5R1_FB21_Pos */
#define CAN_F5R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 5 word 1 bit 21 (`CANx_F5R1.FB21`) bit mask @def CAN_F5R1_FB21_Msk */
#define CAN_F5R1_FB21_Msk			REG_BIT_MASK(CAN_F5R1_FB21_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 21 (`CANx_F5R1.FB21`) bit mask alias @def CAN_F5R1_FB21 */
#define CAN_F5R1_FB21				CAN_F5R1_FB21_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 22 (`CANx_F5R1.FB22`) bit position @def CAN_F5R1_FB22_Pos */
#define CAN_F5R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 5 word 1 bit 22 (`CANx_F5R1.FB22`) bit mask @def CAN_F5R1_FB22_Msk */
#define CAN_F5R1_FB22_Msk			REG_BIT_MASK(CAN_F5R1_FB22_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 22 (`CANx_F5R1.FB22`) bit mask alias @def CAN_F5R1_FB22 */
#define CAN_F5R1_FB22				CAN_F5R1_FB22_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 23 (`CANx_F5R1.FB23`) bit position @def CAN_F5R1_FB23_Pos */
#define CAN_F5R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 5 word 1 bit 23 (`CANx_F5R1.FB23`) bit mask @def CAN_F5R1_FB23_Msk */
#define CAN_F5R1_FB23_Msk			REG_BIT_MASK(CAN_F5R1_FB23_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 23 (`CANx_F5R1.FB23`) bit mask alias @def CAN_F5R1_FB23 */
#define CAN_F5R1_FB23				CAN_F5R1_FB23_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 24 (`CANx_F5R1.FB24`) bit position @def CAN_F5R1_FB24_Pos */
#define CAN_F5R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 5 word 1 bit 24 (`CANx_F5R1.FB24`) bit mask @def CAN_F5R1_FB24_Msk */
#define CAN_F5R1_FB24_Msk			REG_BIT_MASK(CAN_F5R1_FB24_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 24 (`CANx_F5R1.FB24`) bit mask alias @def CAN_F5R1_FB24 */
#define CAN_F5R1_FB24				CAN_F5R1_FB24_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 25 (`CANx_F5R1.FB25`) bit position @def CAN_F5R1_FB25_Pos */
#define CAN_F5R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 5 word 1 bit 25 (`CANx_F5R1.FB25`) bit mask @def CAN_F5R1_FB25_Msk */
#define CAN_F5R1_FB25_Msk			REG_BIT_MASK(CAN_F5R1_FB25_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 25 (`CANx_F5R1.FB25`) bit mask alias @def CAN_F5R1_FB25 */
#define CAN_F5R1_FB25				CAN_F5R1_FB25_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 26 (`CANx_F5R1.FB26`) bit position @def CAN_F5R1_FB26_Pos */
#define CAN_F5R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 5 word 1 bit 26 (`CANx_F5R1.FB26`) bit mask @def CAN_F5R1_FB26_Msk */
#define CAN_F5R1_FB26_Msk			REG_BIT_MASK(CAN_F5R1_FB26_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 26 (`CANx_F5R1.FB26`) bit mask alias @def CAN_F5R1_FB26 */
#define CAN_F5R1_FB26				CAN_F5R1_FB26_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 27 (`CANx_F5R1.FB27`) bit position @def CAN_F5R1_FB27_Pos */
#define CAN_F5R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 5 word 1 bit 27 (`CANx_F5R1.FB27`) bit mask @def CAN_F5R1_FB27_Msk */
#define CAN_F5R1_FB27_Msk			REG_BIT_MASK(CAN_F5R1_FB27_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 27 (`CANx_F5R1.FB27`) bit mask alias @def CAN_F5R1_FB27 */
#define CAN_F5R1_FB27				CAN_F5R1_FB27_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 28 (`CANx_F5R1.FB28`) bit position @def CAN_F5R1_FB28_Pos */
#define CAN_F5R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 5 word 1 bit 28 (`CANx_F5R1.FB28`) bit mask @def CAN_F5R1_FB28_Msk */
#define CAN_F5R1_FB28_Msk			REG_BIT_MASK(CAN_F5R1_FB28_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 28 (`CANx_F5R1.FB28`) bit mask alias @def CAN_F5R1_FB28 */
#define CAN_F5R1_FB28				CAN_F5R1_FB28_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 29 (`CANx_F5R1.FB29`) bit position @def CAN_F5R1_FB29_Pos */
#define CAN_F5R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 5 word 1 bit 29 (`CANx_F5R1.FB29`) bit mask @def CAN_F5R1_FB29_Msk */
#define CAN_F5R1_FB29_Msk			REG_BIT_MASK(CAN_F5R1_FB29_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 29 (`CANx_F5R1.FB29`) bit mask alias @def CAN_F5R1_FB29 */
#define CAN_F5R1_FB29				CAN_F5R1_FB29_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 30 (`CANx_F5R1.FB30`) bit position @def CAN_F5R1_FB30_Pos */
#define CAN_F5R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 5 word 1 bit 30 (`CANx_F5R1.FB30`) bit mask @def CAN_F5R1_FB30_Msk */
#define CAN_F5R1_FB30_Msk			REG_BIT_MASK(CAN_F5R1_FB30_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 30 (`CANx_F5R1.FB30`) bit mask alias @def CAN_F5R1_FB30 */
#define CAN_F5R1_FB30				CAN_F5R1_FB30_Msk

/** @brief Acceptance-filter bank 5 word 1 bit 31 (`CANx_F5R1.FB31`) bit position @def CAN_F5R1_FB31_Pos */
#define CAN_F5R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 5 word 1 bit 31 (`CANx_F5R1.FB31`) bit mask @def CAN_F5R1_FB31_Msk */
#define CAN_F5R1_FB31_Msk			REG_BIT_MASK(CAN_F5R1_FB31_Pos)
/** @brief Acceptance-filter bank 5 word 1 bit 31 (`CANx_F5R1.FB31`) bit mask alias @def CAN_F5R1_FB31 */
#define CAN_F5R1_FB31				CAN_F5R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F6R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 6 word 1 bit 0 (`CANx_F6R1.FB0`) bit position @def CAN_F6R1_FB0_Pos */
#define CAN_F6R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 6 word 1 bit 0 (`CANx_F6R1.FB0`) bit mask @def CAN_F6R1_FB0_Msk */
#define CAN_F6R1_FB0_Msk			REG_BIT_MASK(CAN_F6R1_FB0_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 0 (`CANx_F6R1.FB0`) bit mask alias @def CAN_F6R1_FB0 */
#define CAN_F6R1_FB0				CAN_F6R1_FB0_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 1 (`CANx_F6R1.FB1`) bit position @def CAN_F6R1_FB1_Pos */
#define CAN_F6R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 6 word 1 bit 1 (`CANx_F6R1.FB1`) bit mask @def CAN_F6R1_FB1_Msk */
#define CAN_F6R1_FB1_Msk			REG_BIT_MASK(CAN_F6R1_FB1_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 1 (`CANx_F6R1.FB1`) bit mask alias @def CAN_F6R1_FB1 */
#define CAN_F6R1_FB1				CAN_F6R1_FB1_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 2 (`CANx_F6R1.FB2`) bit position @def CAN_F6R1_FB2_Pos */
#define CAN_F6R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 6 word 1 bit 2 (`CANx_F6R1.FB2`) bit mask @def CAN_F6R1_FB2_Msk */
#define CAN_F6R1_FB2_Msk			REG_BIT_MASK(CAN_F6R1_FB2_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 2 (`CANx_F6R1.FB2`) bit mask alias @def CAN_F6R1_FB2 */
#define CAN_F6R1_FB2				CAN_F6R1_FB2_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 3 (`CANx_F6R1.FB3`) bit position @def CAN_F6R1_FB3_Pos */
#define CAN_F6R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 6 word 1 bit 3 (`CANx_F6R1.FB3`) bit mask @def CAN_F6R1_FB3_Msk */
#define CAN_F6R1_FB3_Msk			REG_BIT_MASK(CAN_F6R1_FB3_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 3 (`CANx_F6R1.FB3`) bit mask alias @def CAN_F6R1_FB3 */
#define CAN_F6R1_FB3				CAN_F6R1_FB3_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 4 (`CANx_F6R1.FB4`) bit position @def CAN_F6R1_FB4_Pos */
#define CAN_F6R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 6 word 1 bit 4 (`CANx_F6R1.FB4`) bit mask @def CAN_F6R1_FB4_Msk */
#define CAN_F6R1_FB4_Msk			REG_BIT_MASK(CAN_F6R1_FB4_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 4 (`CANx_F6R1.FB4`) bit mask alias @def CAN_F6R1_FB4 */
#define CAN_F6R1_FB4				CAN_F6R1_FB4_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 5 (`CANx_F6R1.FB5`) bit position @def CAN_F6R1_FB5_Pos */
#define CAN_F6R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 6 word 1 bit 5 (`CANx_F6R1.FB5`) bit mask @def CAN_F6R1_FB5_Msk */
#define CAN_F6R1_FB5_Msk			REG_BIT_MASK(CAN_F6R1_FB5_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 5 (`CANx_F6R1.FB5`) bit mask alias @def CAN_F6R1_FB5 */
#define CAN_F6R1_FB5				CAN_F6R1_FB5_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 6 (`CANx_F6R1.FB6`) bit position @def CAN_F6R1_FB6_Pos */
#define CAN_F6R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 6 word 1 bit 6 (`CANx_F6R1.FB6`) bit mask @def CAN_F6R1_FB6_Msk */
#define CAN_F6R1_FB6_Msk			REG_BIT_MASK(CAN_F6R1_FB6_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 6 (`CANx_F6R1.FB6`) bit mask alias @def CAN_F6R1_FB6 */
#define CAN_F6R1_FB6				CAN_F6R1_FB6_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 7 (`CANx_F6R1.FB7`) bit position @def CAN_F6R1_FB7_Pos */
#define CAN_F6R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 6 word 1 bit 7 (`CANx_F6R1.FB7`) bit mask @def CAN_F6R1_FB7_Msk */
#define CAN_F6R1_FB7_Msk			REG_BIT_MASK(CAN_F6R1_FB7_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 7 (`CANx_F6R1.FB7`) bit mask alias @def CAN_F6R1_FB7 */
#define CAN_F6R1_FB7				CAN_F6R1_FB7_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 8 (`CANx_F6R1.FB8`) bit position @def CAN_F6R1_FB8_Pos */
#define CAN_F6R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 6 word 1 bit 8 (`CANx_F6R1.FB8`) bit mask @def CAN_F6R1_FB8_Msk */
#define CAN_F6R1_FB8_Msk			REG_BIT_MASK(CAN_F6R1_FB8_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 8 (`CANx_F6R1.FB8`) bit mask alias @def CAN_F6R1_FB8 */
#define CAN_F6R1_FB8				CAN_F6R1_FB8_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 9 (`CANx_F6R1.FB9`) bit position @def CAN_F6R1_FB9_Pos */
#define CAN_F6R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 6 word 1 bit 9 (`CANx_F6R1.FB9`) bit mask @def CAN_F6R1_FB9_Msk */
#define CAN_F6R1_FB9_Msk			REG_BIT_MASK(CAN_F6R1_FB9_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 9 (`CANx_F6R1.FB9`) bit mask alias @def CAN_F6R1_FB9 */
#define CAN_F6R1_FB9				CAN_F6R1_FB9_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 10 (`CANx_F6R1.FB10`) bit position @def CAN_F6R1_FB10_Pos */
#define CAN_F6R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 6 word 1 bit 10 (`CANx_F6R1.FB10`) bit mask @def CAN_F6R1_FB10_Msk */
#define CAN_F6R1_FB10_Msk			REG_BIT_MASK(CAN_F6R1_FB10_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 10 (`CANx_F6R1.FB10`) bit mask alias @def CAN_F6R1_FB10 */
#define CAN_F6R1_FB10				CAN_F6R1_FB10_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 11 (`CANx_F6R1.FB11`) bit position @def CAN_F6R1_FB11_Pos */
#define CAN_F6R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 6 word 1 bit 11 (`CANx_F6R1.FB11`) bit mask @def CAN_F6R1_FB11_Msk */
#define CAN_F6R1_FB11_Msk			REG_BIT_MASK(CAN_F6R1_FB11_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 11 (`CANx_F6R1.FB11`) bit mask alias @def CAN_F6R1_FB11 */
#define CAN_F6R1_FB11				CAN_F6R1_FB11_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 12 (`CANx_F6R1.FB12`) bit position @def CAN_F6R1_FB12_Pos */
#define CAN_F6R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 6 word 1 bit 12 (`CANx_F6R1.FB12`) bit mask @def CAN_F6R1_FB12_Msk */
#define CAN_F6R1_FB12_Msk			REG_BIT_MASK(CAN_F6R1_FB12_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 12 (`CANx_F6R1.FB12`) bit mask alias @def CAN_F6R1_FB12 */
#define CAN_F6R1_FB12				CAN_F6R1_FB12_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 13 (`CANx_F6R1.FB13`) bit position @def CAN_F6R1_FB13_Pos */
#define CAN_F6R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 6 word 1 bit 13 (`CANx_F6R1.FB13`) bit mask @def CAN_F6R1_FB13_Msk */
#define CAN_F6R1_FB13_Msk			REG_BIT_MASK(CAN_F6R1_FB13_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 13 (`CANx_F6R1.FB13`) bit mask alias @def CAN_F6R1_FB13 */
#define CAN_F6R1_FB13				CAN_F6R1_FB13_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 14 (`CANx_F6R1.FB14`) bit position @def CAN_F6R1_FB14_Pos */
#define CAN_F6R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 6 word 1 bit 14 (`CANx_F6R1.FB14`) bit mask @def CAN_F6R1_FB14_Msk */
#define CAN_F6R1_FB14_Msk			REG_BIT_MASK(CAN_F6R1_FB14_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 14 (`CANx_F6R1.FB14`) bit mask alias @def CAN_F6R1_FB14 */
#define CAN_F6R1_FB14				CAN_F6R1_FB14_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 15 (`CANx_F6R1.FB15`) bit position @def CAN_F6R1_FB15_Pos */
#define CAN_F6R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 6 word 1 bit 15 (`CANx_F6R1.FB15`) bit mask @def CAN_F6R1_FB15_Msk */
#define CAN_F6R1_FB15_Msk			REG_BIT_MASK(CAN_F6R1_FB15_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 15 (`CANx_F6R1.FB15`) bit mask alias @def CAN_F6R1_FB15 */
#define CAN_F6R1_FB15				CAN_F6R1_FB15_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 16 (`CANx_F6R1.FB16`) bit position @def CAN_F6R1_FB16_Pos */
#define CAN_F6R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 6 word 1 bit 16 (`CANx_F6R1.FB16`) bit mask @def CAN_F6R1_FB16_Msk */
#define CAN_F6R1_FB16_Msk			REG_BIT_MASK(CAN_F6R1_FB16_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 16 (`CANx_F6R1.FB16`) bit mask alias @def CAN_F6R1_FB16 */
#define CAN_F6R1_FB16				CAN_F6R1_FB16_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 17 (`CANx_F6R1.FB17`) bit position @def CAN_F6R1_FB17_Pos */
#define CAN_F6R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 6 word 1 bit 17 (`CANx_F6R1.FB17`) bit mask @def CAN_F6R1_FB17_Msk */
#define CAN_F6R1_FB17_Msk			REG_BIT_MASK(CAN_F6R1_FB17_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 17 (`CANx_F6R1.FB17`) bit mask alias @def CAN_F6R1_FB17 */
#define CAN_F6R1_FB17				CAN_F6R1_FB17_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 18 (`CANx_F6R1.FB18`) bit position @def CAN_F6R1_FB18_Pos */
#define CAN_F6R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 6 word 1 bit 18 (`CANx_F6R1.FB18`) bit mask @def CAN_F6R1_FB18_Msk */
#define CAN_F6R1_FB18_Msk			REG_BIT_MASK(CAN_F6R1_FB18_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 18 (`CANx_F6R1.FB18`) bit mask alias @def CAN_F6R1_FB18 */
#define CAN_F6R1_FB18				CAN_F6R1_FB18_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 19 (`CANx_F6R1.FB19`) bit position @def CAN_F6R1_FB19_Pos */
#define CAN_F6R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 6 word 1 bit 19 (`CANx_F6R1.FB19`) bit mask @def CAN_F6R1_FB19_Msk */
#define CAN_F6R1_FB19_Msk			REG_BIT_MASK(CAN_F6R1_FB19_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 19 (`CANx_F6R1.FB19`) bit mask alias @def CAN_F6R1_FB19 */
#define CAN_F6R1_FB19				CAN_F6R1_FB19_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 20 (`CANx_F6R1.FB20`) bit position @def CAN_F6R1_FB20_Pos */
#define CAN_F6R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 6 word 1 bit 20 (`CANx_F6R1.FB20`) bit mask @def CAN_F6R1_FB20_Msk */
#define CAN_F6R1_FB20_Msk			REG_BIT_MASK(CAN_F6R1_FB20_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 20 (`CANx_F6R1.FB20`) bit mask alias @def CAN_F6R1_FB20 */
#define CAN_F6R1_FB20				CAN_F6R1_FB20_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 21 (`CANx_F6R1.FB21`) bit position @def CAN_F6R1_FB21_Pos */
#define CAN_F6R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 6 word 1 bit 21 (`CANx_F6R1.FB21`) bit mask @def CAN_F6R1_FB21_Msk */
#define CAN_F6R1_FB21_Msk			REG_BIT_MASK(CAN_F6R1_FB21_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 21 (`CANx_F6R1.FB21`) bit mask alias @def CAN_F6R1_FB21 */
#define CAN_F6R1_FB21				CAN_F6R1_FB21_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 22 (`CANx_F6R1.FB22`) bit position @def CAN_F6R1_FB22_Pos */
#define CAN_F6R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 6 word 1 bit 22 (`CANx_F6R1.FB22`) bit mask @def CAN_F6R1_FB22_Msk */
#define CAN_F6R1_FB22_Msk			REG_BIT_MASK(CAN_F6R1_FB22_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 22 (`CANx_F6R1.FB22`) bit mask alias @def CAN_F6R1_FB22 */
#define CAN_F6R1_FB22				CAN_F6R1_FB22_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 23 (`CANx_F6R1.FB23`) bit position @def CAN_F6R1_FB23_Pos */
#define CAN_F6R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 6 word 1 bit 23 (`CANx_F6R1.FB23`) bit mask @def CAN_F6R1_FB23_Msk */
#define CAN_F6R1_FB23_Msk			REG_BIT_MASK(CAN_F6R1_FB23_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 23 (`CANx_F6R1.FB23`) bit mask alias @def CAN_F6R1_FB23 */
#define CAN_F6R1_FB23				CAN_F6R1_FB23_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 24 (`CANx_F6R1.FB24`) bit position @def CAN_F6R1_FB24_Pos */
#define CAN_F6R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 6 word 1 bit 24 (`CANx_F6R1.FB24`) bit mask @def CAN_F6R1_FB24_Msk */
#define CAN_F6R1_FB24_Msk			REG_BIT_MASK(CAN_F6R1_FB24_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 24 (`CANx_F6R1.FB24`) bit mask alias @def CAN_F6R1_FB24 */
#define CAN_F6R1_FB24				CAN_F6R1_FB24_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 25 (`CANx_F6R1.FB25`) bit position @def CAN_F6R1_FB25_Pos */
#define CAN_F6R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 6 word 1 bit 25 (`CANx_F6R1.FB25`) bit mask @def CAN_F6R1_FB25_Msk */
#define CAN_F6R1_FB25_Msk			REG_BIT_MASK(CAN_F6R1_FB25_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 25 (`CANx_F6R1.FB25`) bit mask alias @def CAN_F6R1_FB25 */
#define CAN_F6R1_FB25				CAN_F6R1_FB25_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 26 (`CANx_F6R1.FB26`) bit position @def CAN_F6R1_FB26_Pos */
#define CAN_F6R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 6 word 1 bit 26 (`CANx_F6R1.FB26`) bit mask @def CAN_F6R1_FB26_Msk */
#define CAN_F6R1_FB26_Msk			REG_BIT_MASK(CAN_F6R1_FB26_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 26 (`CANx_F6R1.FB26`) bit mask alias @def CAN_F6R1_FB26 */
#define CAN_F6R1_FB26				CAN_F6R1_FB26_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 27 (`CANx_F6R1.FB27`) bit position @def CAN_F6R1_FB27_Pos */
#define CAN_F6R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 6 word 1 bit 27 (`CANx_F6R1.FB27`) bit mask @def CAN_F6R1_FB27_Msk */
#define CAN_F6R1_FB27_Msk			REG_BIT_MASK(CAN_F6R1_FB27_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 27 (`CANx_F6R1.FB27`) bit mask alias @def CAN_F6R1_FB27 */
#define CAN_F6R1_FB27				CAN_F6R1_FB27_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 28 (`CANx_F6R1.FB28`) bit position @def CAN_F6R1_FB28_Pos */
#define CAN_F6R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 6 word 1 bit 28 (`CANx_F6R1.FB28`) bit mask @def CAN_F6R1_FB28_Msk */
#define CAN_F6R1_FB28_Msk			REG_BIT_MASK(CAN_F6R1_FB28_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 28 (`CANx_F6R1.FB28`) bit mask alias @def CAN_F6R1_FB28 */
#define CAN_F6R1_FB28				CAN_F6R1_FB28_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 29 (`CANx_F6R1.FB29`) bit position @def CAN_F6R1_FB29_Pos */
#define CAN_F6R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 6 word 1 bit 29 (`CANx_F6R1.FB29`) bit mask @def CAN_F6R1_FB29_Msk */
#define CAN_F6R1_FB29_Msk			REG_BIT_MASK(CAN_F6R1_FB29_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 29 (`CANx_F6R1.FB29`) bit mask alias @def CAN_F6R1_FB29 */
#define CAN_F6R1_FB29				CAN_F6R1_FB29_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 30 (`CANx_F6R1.FB30`) bit position @def CAN_F6R1_FB30_Pos */
#define CAN_F6R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 6 word 1 bit 30 (`CANx_F6R1.FB30`) bit mask @def CAN_F6R1_FB30_Msk */
#define CAN_F6R1_FB30_Msk			REG_BIT_MASK(CAN_F6R1_FB30_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 30 (`CANx_F6R1.FB30`) bit mask alias @def CAN_F6R1_FB30 */
#define CAN_F6R1_FB30				CAN_F6R1_FB30_Msk

/** @brief Acceptance-filter bank 6 word 1 bit 31 (`CANx_F6R1.FB31`) bit position @def CAN_F6R1_FB31_Pos */
#define CAN_F6R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 6 word 1 bit 31 (`CANx_F6R1.FB31`) bit mask @def CAN_F6R1_FB31_Msk */
#define CAN_F6R1_FB31_Msk			REG_BIT_MASK(CAN_F6R1_FB31_Pos)
/** @brief Acceptance-filter bank 6 word 1 bit 31 (`CANx_F6R1.FB31`) bit mask alias @def CAN_F6R1_FB31 */
#define CAN_F6R1_FB31				CAN_F6R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F7R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 7 word 1 bit 0 (`CANx_F7R1.FB0`) bit position @def CAN_F7R1_FB0_Pos */
#define CAN_F7R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 7 word 1 bit 0 (`CANx_F7R1.FB0`) bit mask @def CAN_F7R1_FB0_Msk */
#define CAN_F7R1_FB0_Msk			REG_BIT_MASK(CAN_F7R1_FB0_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 0 (`CANx_F7R1.FB0`) bit mask alias @def CAN_F7R1_FB0 */
#define CAN_F7R1_FB0				CAN_F7R1_FB0_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 1 (`CANx_F7R1.FB1`) bit position @def CAN_F7R1_FB1_Pos */
#define CAN_F7R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 7 word 1 bit 1 (`CANx_F7R1.FB1`) bit mask @def CAN_F7R1_FB1_Msk */
#define CAN_F7R1_FB1_Msk			REG_BIT_MASK(CAN_F7R1_FB1_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 1 (`CANx_F7R1.FB1`) bit mask alias @def CAN_F7R1_FB1 */
#define CAN_F7R1_FB1				CAN_F7R1_FB1_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 2 (`CANx_F7R1.FB2`) bit position @def CAN_F7R1_FB2_Pos */
#define CAN_F7R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 7 word 1 bit 2 (`CANx_F7R1.FB2`) bit mask @def CAN_F7R1_FB2_Msk */
#define CAN_F7R1_FB2_Msk			REG_BIT_MASK(CAN_F7R1_FB2_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 2 (`CANx_F7R1.FB2`) bit mask alias @def CAN_F7R1_FB2 */
#define CAN_F7R1_FB2				CAN_F7R1_FB2_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 3 (`CANx_F7R1.FB3`) bit position @def CAN_F7R1_FB3_Pos */
#define CAN_F7R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 7 word 1 bit 3 (`CANx_F7R1.FB3`) bit mask @def CAN_F7R1_FB3_Msk */
#define CAN_F7R1_FB3_Msk			REG_BIT_MASK(CAN_F7R1_FB3_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 3 (`CANx_F7R1.FB3`) bit mask alias @def CAN_F7R1_FB3 */
#define CAN_F7R1_FB3				CAN_F7R1_FB3_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 4 (`CANx_F7R1.FB4`) bit position @def CAN_F7R1_FB4_Pos */
#define CAN_F7R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 7 word 1 bit 4 (`CANx_F7R1.FB4`) bit mask @def CAN_F7R1_FB4_Msk */
#define CAN_F7R1_FB4_Msk			REG_BIT_MASK(CAN_F7R1_FB4_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 4 (`CANx_F7R1.FB4`) bit mask alias @def CAN_F7R1_FB4 */
#define CAN_F7R1_FB4				CAN_F7R1_FB4_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 5 (`CANx_F7R1.FB5`) bit position @def CAN_F7R1_FB5_Pos */
#define CAN_F7R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 7 word 1 bit 5 (`CANx_F7R1.FB5`) bit mask @def CAN_F7R1_FB5_Msk */
#define CAN_F7R1_FB5_Msk			REG_BIT_MASK(CAN_F7R1_FB5_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 5 (`CANx_F7R1.FB5`) bit mask alias @def CAN_F7R1_FB5 */
#define CAN_F7R1_FB5				CAN_F7R1_FB5_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 6 (`CANx_F7R1.FB6`) bit position @def CAN_F7R1_FB6_Pos */
#define CAN_F7R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 7 word 1 bit 6 (`CANx_F7R1.FB6`) bit mask @def CAN_F7R1_FB6_Msk */
#define CAN_F7R1_FB6_Msk			REG_BIT_MASK(CAN_F7R1_FB6_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 6 (`CANx_F7R1.FB6`) bit mask alias @def CAN_F7R1_FB6 */
#define CAN_F7R1_FB6				CAN_F7R1_FB6_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 7 (`CANx_F7R1.FB7`) bit position @def CAN_F7R1_FB7_Pos */
#define CAN_F7R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 7 word 1 bit 7 (`CANx_F7R1.FB7`) bit mask @def CAN_F7R1_FB7_Msk */
#define CAN_F7R1_FB7_Msk			REG_BIT_MASK(CAN_F7R1_FB7_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 7 (`CANx_F7R1.FB7`) bit mask alias @def CAN_F7R1_FB7 */
#define CAN_F7R1_FB7				CAN_F7R1_FB7_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 8 (`CANx_F7R1.FB8`) bit position @def CAN_F7R1_FB8_Pos */
#define CAN_F7R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 7 word 1 bit 8 (`CANx_F7R1.FB8`) bit mask @def CAN_F7R1_FB8_Msk */
#define CAN_F7R1_FB8_Msk			REG_BIT_MASK(CAN_F7R1_FB8_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 8 (`CANx_F7R1.FB8`) bit mask alias @def CAN_F7R1_FB8 */
#define CAN_F7R1_FB8				CAN_F7R1_FB8_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 9 (`CANx_F7R1.FB9`) bit position @def CAN_F7R1_FB9_Pos */
#define CAN_F7R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 7 word 1 bit 9 (`CANx_F7R1.FB9`) bit mask @def CAN_F7R1_FB9_Msk */
#define CAN_F7R1_FB9_Msk			REG_BIT_MASK(CAN_F7R1_FB9_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 9 (`CANx_F7R1.FB9`) bit mask alias @def CAN_F7R1_FB9 */
#define CAN_F7R1_FB9				CAN_F7R1_FB9_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 10 (`CANx_F7R1.FB10`) bit position @def CAN_F7R1_FB10_Pos */
#define CAN_F7R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 7 word 1 bit 10 (`CANx_F7R1.FB10`) bit mask @def CAN_F7R1_FB10_Msk */
#define CAN_F7R1_FB10_Msk			REG_BIT_MASK(CAN_F7R1_FB10_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 10 (`CANx_F7R1.FB10`) bit mask alias @def CAN_F7R1_FB10 */
#define CAN_F7R1_FB10				CAN_F7R1_FB10_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 11 (`CANx_F7R1.FB11`) bit position @def CAN_F7R1_FB11_Pos */
#define CAN_F7R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 7 word 1 bit 11 (`CANx_F7R1.FB11`) bit mask @def CAN_F7R1_FB11_Msk */
#define CAN_F7R1_FB11_Msk			REG_BIT_MASK(CAN_F7R1_FB11_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 11 (`CANx_F7R1.FB11`) bit mask alias @def CAN_F7R1_FB11 */
#define CAN_F7R1_FB11				CAN_F7R1_FB11_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 12 (`CANx_F7R1.FB12`) bit position @def CAN_F7R1_FB12_Pos */
#define CAN_F7R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 7 word 1 bit 12 (`CANx_F7R1.FB12`) bit mask @def CAN_F7R1_FB12_Msk */
#define CAN_F7R1_FB12_Msk			REG_BIT_MASK(CAN_F7R1_FB12_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 12 (`CANx_F7R1.FB12`) bit mask alias @def CAN_F7R1_FB12 */
#define CAN_F7R1_FB12				CAN_F7R1_FB12_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 13 (`CANx_F7R1.FB13`) bit position @def CAN_F7R1_FB13_Pos */
#define CAN_F7R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 7 word 1 bit 13 (`CANx_F7R1.FB13`) bit mask @def CAN_F7R1_FB13_Msk */
#define CAN_F7R1_FB13_Msk			REG_BIT_MASK(CAN_F7R1_FB13_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 13 (`CANx_F7R1.FB13`) bit mask alias @def CAN_F7R1_FB13 */
#define CAN_F7R1_FB13				CAN_F7R1_FB13_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 14 (`CANx_F7R1.FB14`) bit position @def CAN_F7R1_FB14_Pos */
#define CAN_F7R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 7 word 1 bit 14 (`CANx_F7R1.FB14`) bit mask @def CAN_F7R1_FB14_Msk */
#define CAN_F7R1_FB14_Msk			REG_BIT_MASK(CAN_F7R1_FB14_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 14 (`CANx_F7R1.FB14`) bit mask alias @def CAN_F7R1_FB14 */
#define CAN_F7R1_FB14				CAN_F7R1_FB14_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 15 (`CANx_F7R1.FB15`) bit position @def CAN_F7R1_FB15_Pos */
#define CAN_F7R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 7 word 1 bit 15 (`CANx_F7R1.FB15`) bit mask @def CAN_F7R1_FB15_Msk */
#define CAN_F7R1_FB15_Msk			REG_BIT_MASK(CAN_F7R1_FB15_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 15 (`CANx_F7R1.FB15`) bit mask alias @def CAN_F7R1_FB15 */
#define CAN_F7R1_FB15				CAN_F7R1_FB15_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 16 (`CANx_F7R1.FB16`) bit position @def CAN_F7R1_FB16_Pos */
#define CAN_F7R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 7 word 1 bit 16 (`CANx_F7R1.FB16`) bit mask @def CAN_F7R1_FB16_Msk */
#define CAN_F7R1_FB16_Msk			REG_BIT_MASK(CAN_F7R1_FB16_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 16 (`CANx_F7R1.FB16`) bit mask alias @def CAN_F7R1_FB16 */
#define CAN_F7R1_FB16				CAN_F7R1_FB16_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 17 (`CANx_F7R1.FB17`) bit position @def CAN_F7R1_FB17_Pos */
#define CAN_F7R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 7 word 1 bit 17 (`CANx_F7R1.FB17`) bit mask @def CAN_F7R1_FB17_Msk */
#define CAN_F7R1_FB17_Msk			REG_BIT_MASK(CAN_F7R1_FB17_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 17 (`CANx_F7R1.FB17`) bit mask alias @def CAN_F7R1_FB17 */
#define CAN_F7R1_FB17				CAN_F7R1_FB17_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 18 (`CANx_F7R1.FB18`) bit position @def CAN_F7R1_FB18_Pos */
#define CAN_F7R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 7 word 1 bit 18 (`CANx_F7R1.FB18`) bit mask @def CAN_F7R1_FB18_Msk */
#define CAN_F7R1_FB18_Msk			REG_BIT_MASK(CAN_F7R1_FB18_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 18 (`CANx_F7R1.FB18`) bit mask alias @def CAN_F7R1_FB18 */
#define CAN_F7R1_FB18				CAN_F7R1_FB18_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 19 (`CANx_F7R1.FB19`) bit position @def CAN_F7R1_FB19_Pos */
#define CAN_F7R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 7 word 1 bit 19 (`CANx_F7R1.FB19`) bit mask @def CAN_F7R1_FB19_Msk */
#define CAN_F7R1_FB19_Msk			REG_BIT_MASK(CAN_F7R1_FB19_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 19 (`CANx_F7R1.FB19`) bit mask alias @def CAN_F7R1_FB19 */
#define CAN_F7R1_FB19				CAN_F7R1_FB19_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 20 (`CANx_F7R1.FB20`) bit position @def CAN_F7R1_FB20_Pos */
#define CAN_F7R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 7 word 1 bit 20 (`CANx_F7R1.FB20`) bit mask @def CAN_F7R1_FB20_Msk */
#define CAN_F7R1_FB20_Msk			REG_BIT_MASK(CAN_F7R1_FB20_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 20 (`CANx_F7R1.FB20`) bit mask alias @def CAN_F7R1_FB20 */
#define CAN_F7R1_FB20				CAN_F7R1_FB20_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 21 (`CANx_F7R1.FB21`) bit position @def CAN_F7R1_FB21_Pos */
#define CAN_F7R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 7 word 1 bit 21 (`CANx_F7R1.FB21`) bit mask @def CAN_F7R1_FB21_Msk */
#define CAN_F7R1_FB21_Msk			REG_BIT_MASK(CAN_F7R1_FB21_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 21 (`CANx_F7R1.FB21`) bit mask alias @def CAN_F7R1_FB21 */
#define CAN_F7R1_FB21				CAN_F7R1_FB21_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 22 (`CANx_F7R1.FB22`) bit position @def CAN_F7R1_FB22_Pos */
#define CAN_F7R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 7 word 1 bit 22 (`CANx_F7R1.FB22`) bit mask @def CAN_F7R1_FB22_Msk */
#define CAN_F7R1_FB22_Msk			REG_BIT_MASK(CAN_F7R1_FB22_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 22 (`CANx_F7R1.FB22`) bit mask alias @def CAN_F7R1_FB22 */
#define CAN_F7R1_FB22				CAN_F7R1_FB22_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 23 (`CANx_F7R1.FB23`) bit position @def CAN_F7R1_FB23_Pos */
#define CAN_F7R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 7 word 1 bit 23 (`CANx_F7R1.FB23`) bit mask @def CAN_F7R1_FB23_Msk */
#define CAN_F7R1_FB23_Msk			REG_BIT_MASK(CAN_F7R1_FB23_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 23 (`CANx_F7R1.FB23`) bit mask alias @def CAN_F7R1_FB23 */
#define CAN_F7R1_FB23				CAN_F7R1_FB23_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 24 (`CANx_F7R1.FB24`) bit position @def CAN_F7R1_FB24_Pos */
#define CAN_F7R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 7 word 1 bit 24 (`CANx_F7R1.FB24`) bit mask @def CAN_F7R1_FB24_Msk */
#define CAN_F7R1_FB24_Msk			REG_BIT_MASK(CAN_F7R1_FB24_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 24 (`CANx_F7R1.FB24`) bit mask alias @def CAN_F7R1_FB24 */
#define CAN_F7R1_FB24				CAN_F7R1_FB24_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 25 (`CANx_F7R1.FB25`) bit position @def CAN_F7R1_FB25_Pos */
#define CAN_F7R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 7 word 1 bit 25 (`CANx_F7R1.FB25`) bit mask @def CAN_F7R1_FB25_Msk */
#define CAN_F7R1_FB25_Msk			REG_BIT_MASK(CAN_F7R1_FB25_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 25 (`CANx_F7R1.FB25`) bit mask alias @def CAN_F7R1_FB25 */
#define CAN_F7R1_FB25				CAN_F7R1_FB25_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 26 (`CANx_F7R1.FB26`) bit position @def CAN_F7R1_FB26_Pos */
#define CAN_F7R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 7 word 1 bit 26 (`CANx_F7R1.FB26`) bit mask @def CAN_F7R1_FB26_Msk */
#define CAN_F7R1_FB26_Msk			REG_BIT_MASK(CAN_F7R1_FB26_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 26 (`CANx_F7R1.FB26`) bit mask alias @def CAN_F7R1_FB26 */
#define CAN_F7R1_FB26				CAN_F7R1_FB26_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 27 (`CANx_F7R1.FB27`) bit position @def CAN_F7R1_FB27_Pos */
#define CAN_F7R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 7 word 1 bit 27 (`CANx_F7R1.FB27`) bit mask @def CAN_F7R1_FB27_Msk */
#define CAN_F7R1_FB27_Msk			REG_BIT_MASK(CAN_F7R1_FB27_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 27 (`CANx_F7R1.FB27`) bit mask alias @def CAN_F7R1_FB27 */
#define CAN_F7R1_FB27				CAN_F7R1_FB27_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 28 (`CANx_F7R1.FB28`) bit position @def CAN_F7R1_FB28_Pos */
#define CAN_F7R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 7 word 1 bit 28 (`CANx_F7R1.FB28`) bit mask @def CAN_F7R1_FB28_Msk */
#define CAN_F7R1_FB28_Msk			REG_BIT_MASK(CAN_F7R1_FB28_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 28 (`CANx_F7R1.FB28`) bit mask alias @def CAN_F7R1_FB28 */
#define CAN_F7R1_FB28				CAN_F7R1_FB28_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 29 (`CANx_F7R1.FB29`) bit position @def CAN_F7R1_FB29_Pos */
#define CAN_F7R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 7 word 1 bit 29 (`CANx_F7R1.FB29`) bit mask @def CAN_F7R1_FB29_Msk */
#define CAN_F7R1_FB29_Msk			REG_BIT_MASK(CAN_F7R1_FB29_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 29 (`CANx_F7R1.FB29`) bit mask alias @def CAN_F7R1_FB29 */
#define CAN_F7R1_FB29				CAN_F7R1_FB29_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 30 (`CANx_F7R1.FB30`) bit position @def CAN_F7R1_FB30_Pos */
#define CAN_F7R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 7 word 1 bit 30 (`CANx_F7R1.FB30`) bit mask @def CAN_F7R1_FB30_Msk */
#define CAN_F7R1_FB30_Msk			REG_BIT_MASK(CAN_F7R1_FB30_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 30 (`CANx_F7R1.FB30`) bit mask alias @def CAN_F7R1_FB30 */
#define CAN_F7R1_FB30				CAN_F7R1_FB30_Msk

/** @brief Acceptance-filter bank 7 word 1 bit 31 (`CANx_F7R1.FB31`) bit position @def CAN_F7R1_FB31_Pos */
#define CAN_F7R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 7 word 1 bit 31 (`CANx_F7R1.FB31`) bit mask @def CAN_F7R1_FB31_Msk */
#define CAN_F7R1_FB31_Msk			REG_BIT_MASK(CAN_F7R1_FB31_Pos)
/** @brief Acceptance-filter bank 7 word 1 bit 31 (`CANx_F7R1.FB31`) bit mask alias @def CAN_F7R1_FB31 */
#define CAN_F7R1_FB31				CAN_F7R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F8R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 8 word 1 bit 0 (`CANx_F8R1.FB0`) bit position @def CAN_F8R1_FB0_Pos */
#define CAN_F8R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 8 word 1 bit 0 (`CANx_F8R1.FB0`) bit mask @def CAN_F8R1_FB0_Msk */
#define CAN_F8R1_FB0_Msk			REG_BIT_MASK(CAN_F8R1_FB0_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 0 (`CANx_F8R1.FB0`) bit mask alias @def CAN_F8R1_FB0 */
#define CAN_F8R1_FB0				CAN_F8R1_FB0_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 1 (`CANx_F8R1.FB1`) bit position @def CAN_F8R1_FB1_Pos */
#define CAN_F8R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 8 word 1 bit 1 (`CANx_F8R1.FB1`) bit mask @def CAN_F8R1_FB1_Msk */
#define CAN_F8R1_FB1_Msk			REG_BIT_MASK(CAN_F8R1_FB1_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 1 (`CANx_F8R1.FB1`) bit mask alias @def CAN_F8R1_FB1 */
#define CAN_F8R1_FB1				CAN_F8R1_FB1_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 2 (`CANx_F8R1.FB2`) bit position @def CAN_F8R1_FB2_Pos */
#define CAN_F8R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 8 word 1 bit 2 (`CANx_F8R1.FB2`) bit mask @def CAN_F8R1_FB2_Msk */
#define CAN_F8R1_FB2_Msk			REG_BIT_MASK(CAN_F8R1_FB2_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 2 (`CANx_F8R1.FB2`) bit mask alias @def CAN_F8R1_FB2 */
#define CAN_F8R1_FB2				CAN_F8R1_FB2_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 3 (`CANx_F8R1.FB3`) bit position @def CAN_F8R1_FB3_Pos */
#define CAN_F8R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 8 word 1 bit 3 (`CANx_F8R1.FB3`) bit mask @def CAN_F8R1_FB3_Msk */
#define CAN_F8R1_FB3_Msk			REG_BIT_MASK(CAN_F8R1_FB3_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 3 (`CANx_F8R1.FB3`) bit mask alias @def CAN_F8R1_FB3 */
#define CAN_F8R1_FB3				CAN_F8R1_FB3_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 4 (`CANx_F8R1.FB4`) bit position @def CAN_F8R1_FB4_Pos */
#define CAN_F8R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 8 word 1 bit 4 (`CANx_F8R1.FB4`) bit mask @def CAN_F8R1_FB4_Msk */
#define CAN_F8R1_FB4_Msk			REG_BIT_MASK(CAN_F8R1_FB4_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 4 (`CANx_F8R1.FB4`) bit mask alias @def CAN_F8R1_FB4 */
#define CAN_F8R1_FB4				CAN_F8R1_FB4_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 5 (`CANx_F8R1.FB5`) bit position @def CAN_F8R1_FB5_Pos */
#define CAN_F8R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 8 word 1 bit 5 (`CANx_F8R1.FB5`) bit mask @def CAN_F8R1_FB5_Msk */
#define CAN_F8R1_FB5_Msk			REG_BIT_MASK(CAN_F8R1_FB5_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 5 (`CANx_F8R1.FB5`) bit mask alias @def CAN_F8R1_FB5 */
#define CAN_F8R1_FB5				CAN_F8R1_FB5_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 6 (`CANx_F8R1.FB6`) bit position @def CAN_F8R1_FB6_Pos */
#define CAN_F8R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 8 word 1 bit 6 (`CANx_F8R1.FB6`) bit mask @def CAN_F8R1_FB6_Msk */
#define CAN_F8R1_FB6_Msk			REG_BIT_MASK(CAN_F8R1_FB6_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 6 (`CANx_F8R1.FB6`) bit mask alias @def CAN_F8R1_FB6 */
#define CAN_F8R1_FB6				CAN_F8R1_FB6_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 7 (`CANx_F8R1.FB7`) bit position @def CAN_F8R1_FB7_Pos */
#define CAN_F8R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 8 word 1 bit 7 (`CANx_F8R1.FB7`) bit mask @def CAN_F8R1_FB7_Msk */
#define CAN_F8R1_FB7_Msk			REG_BIT_MASK(CAN_F8R1_FB7_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 7 (`CANx_F8R1.FB7`) bit mask alias @def CAN_F8R1_FB7 */
#define CAN_F8R1_FB7				CAN_F8R1_FB7_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 8 (`CANx_F8R1.FB8`) bit position @def CAN_F8R1_FB8_Pos */
#define CAN_F8R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 8 word 1 bit 8 (`CANx_F8R1.FB8`) bit mask @def CAN_F8R1_FB8_Msk */
#define CAN_F8R1_FB8_Msk			REG_BIT_MASK(CAN_F8R1_FB8_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 8 (`CANx_F8R1.FB8`) bit mask alias @def CAN_F8R1_FB8 */
#define CAN_F8R1_FB8				CAN_F8R1_FB8_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 9 (`CANx_F8R1.FB9`) bit position @def CAN_F8R1_FB9_Pos */
#define CAN_F8R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 8 word 1 bit 9 (`CANx_F8R1.FB9`) bit mask @def CAN_F8R1_FB9_Msk */
#define CAN_F8R1_FB9_Msk			REG_BIT_MASK(CAN_F8R1_FB9_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 9 (`CANx_F8R1.FB9`) bit mask alias @def CAN_F8R1_FB9 */
#define CAN_F8R1_FB9				CAN_F8R1_FB9_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 10 (`CANx_F8R1.FB10`) bit position @def CAN_F8R1_FB10_Pos */
#define CAN_F8R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 8 word 1 bit 10 (`CANx_F8R1.FB10`) bit mask @def CAN_F8R1_FB10_Msk */
#define CAN_F8R1_FB10_Msk			REG_BIT_MASK(CAN_F8R1_FB10_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 10 (`CANx_F8R1.FB10`) bit mask alias @def CAN_F8R1_FB10 */
#define CAN_F8R1_FB10				CAN_F8R1_FB10_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 11 (`CANx_F8R1.FB11`) bit position @def CAN_F8R1_FB11_Pos */
#define CAN_F8R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 8 word 1 bit 11 (`CANx_F8R1.FB11`) bit mask @def CAN_F8R1_FB11_Msk */
#define CAN_F8R1_FB11_Msk			REG_BIT_MASK(CAN_F8R1_FB11_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 11 (`CANx_F8R1.FB11`) bit mask alias @def CAN_F8R1_FB11 */
#define CAN_F8R1_FB11				CAN_F8R1_FB11_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 12 (`CANx_F8R1.FB12`) bit position @def CAN_F8R1_FB12_Pos */
#define CAN_F8R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 8 word 1 bit 12 (`CANx_F8R1.FB12`) bit mask @def CAN_F8R1_FB12_Msk */
#define CAN_F8R1_FB12_Msk			REG_BIT_MASK(CAN_F8R1_FB12_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 12 (`CANx_F8R1.FB12`) bit mask alias @def CAN_F8R1_FB12 */
#define CAN_F8R1_FB12				CAN_F8R1_FB12_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 13 (`CANx_F8R1.FB13`) bit position @def CAN_F8R1_FB13_Pos */
#define CAN_F8R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 8 word 1 bit 13 (`CANx_F8R1.FB13`) bit mask @def CAN_F8R1_FB13_Msk */
#define CAN_F8R1_FB13_Msk			REG_BIT_MASK(CAN_F8R1_FB13_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 13 (`CANx_F8R1.FB13`) bit mask alias @def CAN_F8R1_FB13 */
#define CAN_F8R1_FB13				CAN_F8R1_FB13_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 14 (`CANx_F8R1.FB14`) bit position @def CAN_F8R1_FB14_Pos */
#define CAN_F8R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 8 word 1 bit 14 (`CANx_F8R1.FB14`) bit mask @def CAN_F8R1_FB14_Msk */
#define CAN_F8R1_FB14_Msk			REG_BIT_MASK(CAN_F8R1_FB14_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 14 (`CANx_F8R1.FB14`) bit mask alias @def CAN_F8R1_FB14 */
#define CAN_F8R1_FB14				CAN_F8R1_FB14_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 15 (`CANx_F8R1.FB15`) bit position @def CAN_F8R1_FB15_Pos */
#define CAN_F8R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 8 word 1 bit 15 (`CANx_F8R1.FB15`) bit mask @def CAN_F8R1_FB15_Msk */
#define CAN_F8R1_FB15_Msk			REG_BIT_MASK(CAN_F8R1_FB15_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 15 (`CANx_F8R1.FB15`) bit mask alias @def CAN_F8R1_FB15 */
#define CAN_F8R1_FB15				CAN_F8R1_FB15_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 16 (`CANx_F8R1.FB16`) bit position @def CAN_F8R1_FB16_Pos */
#define CAN_F8R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 8 word 1 bit 16 (`CANx_F8R1.FB16`) bit mask @def CAN_F8R1_FB16_Msk */
#define CAN_F8R1_FB16_Msk			REG_BIT_MASK(CAN_F8R1_FB16_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 16 (`CANx_F8R1.FB16`) bit mask alias @def CAN_F8R1_FB16 */
#define CAN_F8R1_FB16				CAN_F8R1_FB16_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 17 (`CANx_F8R1.FB17`) bit position @def CAN_F8R1_FB17_Pos */
#define CAN_F8R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 8 word 1 bit 17 (`CANx_F8R1.FB17`) bit mask @def CAN_F8R1_FB17_Msk */
#define CAN_F8R1_FB17_Msk			REG_BIT_MASK(CAN_F8R1_FB17_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 17 (`CANx_F8R1.FB17`) bit mask alias @def CAN_F8R1_FB17 */
#define CAN_F8R1_FB17				CAN_F8R1_FB17_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 18 (`CANx_F8R1.FB18`) bit position @def CAN_F8R1_FB18_Pos */
#define CAN_F8R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 8 word 1 bit 18 (`CANx_F8R1.FB18`) bit mask @def CAN_F8R1_FB18_Msk */
#define CAN_F8R1_FB18_Msk			REG_BIT_MASK(CAN_F8R1_FB18_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 18 (`CANx_F8R1.FB18`) bit mask alias @def CAN_F8R1_FB18 */
#define CAN_F8R1_FB18				CAN_F8R1_FB18_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 19 (`CANx_F8R1.FB19`) bit position @def CAN_F8R1_FB19_Pos */
#define CAN_F8R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 8 word 1 bit 19 (`CANx_F8R1.FB19`) bit mask @def CAN_F8R1_FB19_Msk */
#define CAN_F8R1_FB19_Msk			REG_BIT_MASK(CAN_F8R1_FB19_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 19 (`CANx_F8R1.FB19`) bit mask alias @def CAN_F8R1_FB19 */
#define CAN_F8R1_FB19				CAN_F8R1_FB19_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 20 (`CANx_F8R1.FB20`) bit position @def CAN_F8R1_FB20_Pos */
#define CAN_F8R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 8 word 1 bit 20 (`CANx_F8R1.FB20`) bit mask @def CAN_F8R1_FB20_Msk */
#define CAN_F8R1_FB20_Msk			REG_BIT_MASK(CAN_F8R1_FB20_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 20 (`CANx_F8R1.FB20`) bit mask alias @def CAN_F8R1_FB20 */
#define CAN_F8R1_FB20				CAN_F8R1_FB20_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 21 (`CANx_F8R1.FB21`) bit position @def CAN_F8R1_FB21_Pos */
#define CAN_F8R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 8 word 1 bit 21 (`CANx_F8R1.FB21`) bit mask @def CAN_F8R1_FB21_Msk */
#define CAN_F8R1_FB21_Msk			REG_BIT_MASK(CAN_F8R1_FB21_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 21 (`CANx_F8R1.FB21`) bit mask alias @def CAN_F8R1_FB21 */
#define CAN_F8R1_FB21				CAN_F8R1_FB21_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 22 (`CANx_F8R1.FB22`) bit position @def CAN_F8R1_FB22_Pos */
#define CAN_F8R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 8 word 1 bit 22 (`CANx_F8R1.FB22`) bit mask @def CAN_F8R1_FB22_Msk */
#define CAN_F8R1_FB22_Msk			REG_BIT_MASK(CAN_F8R1_FB22_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 22 (`CANx_F8R1.FB22`) bit mask alias @def CAN_F8R1_FB22 */
#define CAN_F8R1_FB22				CAN_F8R1_FB22_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 23 (`CANx_F8R1.FB23`) bit position @def CAN_F8R1_FB23_Pos */
#define CAN_F8R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 8 word 1 bit 23 (`CANx_F8R1.FB23`) bit mask @def CAN_F8R1_FB23_Msk */
#define CAN_F8R1_FB23_Msk			REG_BIT_MASK(CAN_F8R1_FB23_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 23 (`CANx_F8R1.FB23`) bit mask alias @def CAN_F8R1_FB23 */
#define CAN_F8R1_FB23				CAN_F8R1_FB23_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 24 (`CANx_F8R1.FB24`) bit position @def CAN_F8R1_FB24_Pos */
#define CAN_F8R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 8 word 1 bit 24 (`CANx_F8R1.FB24`) bit mask @def CAN_F8R1_FB24_Msk */
#define CAN_F8R1_FB24_Msk			REG_BIT_MASK(CAN_F8R1_FB24_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 24 (`CANx_F8R1.FB24`) bit mask alias @def CAN_F8R1_FB24 */
#define CAN_F8R1_FB24				CAN_F8R1_FB24_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 25 (`CANx_F8R1.FB25`) bit position @def CAN_F8R1_FB25_Pos */
#define CAN_F8R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 8 word 1 bit 25 (`CANx_F8R1.FB25`) bit mask @def CAN_F8R1_FB25_Msk */
#define CAN_F8R1_FB25_Msk			REG_BIT_MASK(CAN_F8R1_FB25_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 25 (`CANx_F8R1.FB25`) bit mask alias @def CAN_F8R1_FB25 */
#define CAN_F8R1_FB25				CAN_F8R1_FB25_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 26 (`CANx_F8R1.FB26`) bit position @def CAN_F8R1_FB26_Pos */
#define CAN_F8R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 8 word 1 bit 26 (`CANx_F8R1.FB26`) bit mask @def CAN_F8R1_FB26_Msk */
#define CAN_F8R1_FB26_Msk			REG_BIT_MASK(CAN_F8R1_FB26_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 26 (`CANx_F8R1.FB26`) bit mask alias @def CAN_F8R1_FB26 */
#define CAN_F8R1_FB26				CAN_F8R1_FB26_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 27 (`CANx_F8R1.FB27`) bit position @def CAN_F8R1_FB27_Pos */
#define CAN_F8R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 8 word 1 bit 27 (`CANx_F8R1.FB27`) bit mask @def CAN_F8R1_FB27_Msk */
#define CAN_F8R1_FB27_Msk			REG_BIT_MASK(CAN_F8R1_FB27_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 27 (`CANx_F8R1.FB27`) bit mask alias @def CAN_F8R1_FB27 */
#define CAN_F8R1_FB27				CAN_F8R1_FB27_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 28 (`CANx_F8R1.FB28`) bit position @def CAN_F8R1_FB28_Pos */
#define CAN_F8R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 8 word 1 bit 28 (`CANx_F8R1.FB28`) bit mask @def CAN_F8R1_FB28_Msk */
#define CAN_F8R1_FB28_Msk			REG_BIT_MASK(CAN_F8R1_FB28_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 28 (`CANx_F8R1.FB28`) bit mask alias @def CAN_F8R1_FB28 */
#define CAN_F8R1_FB28				CAN_F8R1_FB28_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 29 (`CANx_F8R1.FB29`) bit position @def CAN_F8R1_FB29_Pos */
#define CAN_F8R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 8 word 1 bit 29 (`CANx_F8R1.FB29`) bit mask @def CAN_F8R1_FB29_Msk */
#define CAN_F8R1_FB29_Msk			REG_BIT_MASK(CAN_F8R1_FB29_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 29 (`CANx_F8R1.FB29`) bit mask alias @def CAN_F8R1_FB29 */
#define CAN_F8R1_FB29				CAN_F8R1_FB29_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 30 (`CANx_F8R1.FB30`) bit position @def CAN_F8R1_FB30_Pos */
#define CAN_F8R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 8 word 1 bit 30 (`CANx_F8R1.FB30`) bit mask @def CAN_F8R1_FB30_Msk */
#define CAN_F8R1_FB30_Msk			REG_BIT_MASK(CAN_F8R1_FB30_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 30 (`CANx_F8R1.FB30`) bit mask alias @def CAN_F8R1_FB30 */
#define CAN_F8R1_FB30				CAN_F8R1_FB30_Msk

/** @brief Acceptance-filter bank 8 word 1 bit 31 (`CANx_F8R1.FB31`) bit position @def CAN_F8R1_FB31_Pos */
#define CAN_F8R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 8 word 1 bit 31 (`CANx_F8R1.FB31`) bit mask @def CAN_F8R1_FB31_Msk */
#define CAN_F8R1_FB31_Msk			REG_BIT_MASK(CAN_F8R1_FB31_Pos)
/** @brief Acceptance-filter bank 8 word 1 bit 31 (`CANx_F8R1.FB31`) bit mask alias @def CAN_F8R1_FB31 */
#define CAN_F8R1_FB31				CAN_F8R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F9R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 9 word 1 bit 0 (`CANx_F9R1.FB0`) bit position @def CAN_F9R1_FB0_Pos */
#define CAN_F9R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 9 word 1 bit 0 (`CANx_F9R1.FB0`) bit mask @def CAN_F9R1_FB0_Msk */
#define CAN_F9R1_FB0_Msk			REG_BIT_MASK(CAN_F9R1_FB0_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 0 (`CANx_F9R1.FB0`) bit mask alias @def CAN_F9R1_FB0 */
#define CAN_F9R1_FB0				CAN_F9R1_FB0_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 1 (`CANx_F9R1.FB1`) bit position @def CAN_F9R1_FB1_Pos */
#define CAN_F9R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 9 word 1 bit 1 (`CANx_F9R1.FB1`) bit mask @def CAN_F9R1_FB1_Msk */
#define CAN_F9R1_FB1_Msk			REG_BIT_MASK(CAN_F9R1_FB1_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 1 (`CANx_F9R1.FB1`) bit mask alias @def CAN_F9R1_FB1 */
#define CAN_F9R1_FB1				CAN_F9R1_FB1_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 2 (`CANx_F9R1.FB2`) bit position @def CAN_F9R1_FB2_Pos */
#define CAN_F9R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 9 word 1 bit 2 (`CANx_F9R1.FB2`) bit mask @def CAN_F9R1_FB2_Msk */
#define CAN_F9R1_FB2_Msk			REG_BIT_MASK(CAN_F9R1_FB2_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 2 (`CANx_F9R1.FB2`) bit mask alias @def CAN_F9R1_FB2 */
#define CAN_F9R1_FB2				CAN_F9R1_FB2_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 3 (`CANx_F9R1.FB3`) bit position @def CAN_F9R1_FB3_Pos */
#define CAN_F9R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 9 word 1 bit 3 (`CANx_F9R1.FB3`) bit mask @def CAN_F9R1_FB3_Msk */
#define CAN_F9R1_FB3_Msk			REG_BIT_MASK(CAN_F9R1_FB3_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 3 (`CANx_F9R1.FB3`) bit mask alias @def CAN_F9R1_FB3 */
#define CAN_F9R1_FB3				CAN_F9R1_FB3_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 4 (`CANx_F9R1.FB4`) bit position @def CAN_F9R1_FB4_Pos */
#define CAN_F9R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 9 word 1 bit 4 (`CANx_F9R1.FB4`) bit mask @def CAN_F9R1_FB4_Msk */
#define CAN_F9R1_FB4_Msk			REG_BIT_MASK(CAN_F9R1_FB4_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 4 (`CANx_F9R1.FB4`) bit mask alias @def CAN_F9R1_FB4 */
#define CAN_F9R1_FB4				CAN_F9R1_FB4_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 5 (`CANx_F9R1.FB5`) bit position @def CAN_F9R1_FB5_Pos */
#define CAN_F9R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 9 word 1 bit 5 (`CANx_F9R1.FB5`) bit mask @def CAN_F9R1_FB5_Msk */
#define CAN_F9R1_FB5_Msk			REG_BIT_MASK(CAN_F9R1_FB5_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 5 (`CANx_F9R1.FB5`) bit mask alias @def CAN_F9R1_FB5 */
#define CAN_F9R1_FB5				CAN_F9R1_FB5_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 6 (`CANx_F9R1.FB6`) bit position @def CAN_F9R1_FB6_Pos */
#define CAN_F9R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 9 word 1 bit 6 (`CANx_F9R1.FB6`) bit mask @def CAN_F9R1_FB6_Msk */
#define CAN_F9R1_FB6_Msk			REG_BIT_MASK(CAN_F9R1_FB6_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 6 (`CANx_F9R1.FB6`) bit mask alias @def CAN_F9R1_FB6 */
#define CAN_F9R1_FB6				CAN_F9R1_FB6_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 7 (`CANx_F9R1.FB7`) bit position @def CAN_F9R1_FB7_Pos */
#define CAN_F9R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 9 word 1 bit 7 (`CANx_F9R1.FB7`) bit mask @def CAN_F9R1_FB7_Msk */
#define CAN_F9R1_FB7_Msk			REG_BIT_MASK(CAN_F9R1_FB7_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 7 (`CANx_F9R1.FB7`) bit mask alias @def CAN_F9R1_FB7 */
#define CAN_F9R1_FB7				CAN_F9R1_FB7_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 8 (`CANx_F9R1.FB8`) bit position @def CAN_F9R1_FB8_Pos */
#define CAN_F9R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 9 word 1 bit 8 (`CANx_F9R1.FB8`) bit mask @def CAN_F9R1_FB8_Msk */
#define CAN_F9R1_FB8_Msk			REG_BIT_MASK(CAN_F9R1_FB8_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 8 (`CANx_F9R1.FB8`) bit mask alias @def CAN_F9R1_FB8 */
#define CAN_F9R1_FB8				CAN_F9R1_FB8_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 9 (`CANx_F9R1.FB9`) bit position @def CAN_F9R1_FB9_Pos */
#define CAN_F9R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 9 word 1 bit 9 (`CANx_F9R1.FB9`) bit mask @def CAN_F9R1_FB9_Msk */
#define CAN_F9R1_FB9_Msk			REG_BIT_MASK(CAN_F9R1_FB9_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 9 (`CANx_F9R1.FB9`) bit mask alias @def CAN_F9R1_FB9 */
#define CAN_F9R1_FB9				CAN_F9R1_FB9_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 10 (`CANx_F9R1.FB10`) bit position @def CAN_F9R1_FB10_Pos */
#define CAN_F9R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 9 word 1 bit 10 (`CANx_F9R1.FB10`) bit mask @def CAN_F9R1_FB10_Msk */
#define CAN_F9R1_FB10_Msk			REG_BIT_MASK(CAN_F9R1_FB10_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 10 (`CANx_F9R1.FB10`) bit mask alias @def CAN_F9R1_FB10 */
#define CAN_F9R1_FB10				CAN_F9R1_FB10_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 11 (`CANx_F9R1.FB11`) bit position @def CAN_F9R1_FB11_Pos */
#define CAN_F9R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 9 word 1 bit 11 (`CANx_F9R1.FB11`) bit mask @def CAN_F9R1_FB11_Msk */
#define CAN_F9R1_FB11_Msk			REG_BIT_MASK(CAN_F9R1_FB11_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 11 (`CANx_F9R1.FB11`) bit mask alias @def CAN_F9R1_FB11 */
#define CAN_F9R1_FB11				CAN_F9R1_FB11_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 12 (`CANx_F9R1.FB12`) bit position @def CAN_F9R1_FB12_Pos */
#define CAN_F9R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 9 word 1 bit 12 (`CANx_F9R1.FB12`) bit mask @def CAN_F9R1_FB12_Msk */
#define CAN_F9R1_FB12_Msk			REG_BIT_MASK(CAN_F9R1_FB12_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 12 (`CANx_F9R1.FB12`) bit mask alias @def CAN_F9R1_FB12 */
#define CAN_F9R1_FB12				CAN_F9R1_FB12_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 13 (`CANx_F9R1.FB13`) bit position @def CAN_F9R1_FB13_Pos */
#define CAN_F9R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 9 word 1 bit 13 (`CANx_F9R1.FB13`) bit mask @def CAN_F9R1_FB13_Msk */
#define CAN_F9R1_FB13_Msk			REG_BIT_MASK(CAN_F9R1_FB13_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 13 (`CANx_F9R1.FB13`) bit mask alias @def CAN_F9R1_FB13 */
#define CAN_F9R1_FB13				CAN_F9R1_FB13_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 14 (`CANx_F9R1.FB14`) bit position @def CAN_F9R1_FB14_Pos */
#define CAN_F9R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 9 word 1 bit 14 (`CANx_F9R1.FB14`) bit mask @def CAN_F9R1_FB14_Msk */
#define CAN_F9R1_FB14_Msk			REG_BIT_MASK(CAN_F9R1_FB14_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 14 (`CANx_F9R1.FB14`) bit mask alias @def CAN_F9R1_FB14 */
#define CAN_F9R1_FB14				CAN_F9R1_FB14_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 15 (`CANx_F9R1.FB15`) bit position @def CAN_F9R1_FB15_Pos */
#define CAN_F9R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 9 word 1 bit 15 (`CANx_F9R1.FB15`) bit mask @def CAN_F9R1_FB15_Msk */
#define CAN_F9R1_FB15_Msk			REG_BIT_MASK(CAN_F9R1_FB15_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 15 (`CANx_F9R1.FB15`) bit mask alias @def CAN_F9R1_FB15 */
#define CAN_F9R1_FB15				CAN_F9R1_FB15_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 16 (`CANx_F9R1.FB16`) bit position @def CAN_F9R1_FB16_Pos */
#define CAN_F9R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 9 word 1 bit 16 (`CANx_F9R1.FB16`) bit mask @def CAN_F9R1_FB16_Msk */
#define CAN_F9R1_FB16_Msk			REG_BIT_MASK(CAN_F9R1_FB16_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 16 (`CANx_F9R1.FB16`) bit mask alias @def CAN_F9R1_FB16 */
#define CAN_F9R1_FB16				CAN_F9R1_FB16_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 17 (`CANx_F9R1.FB17`) bit position @def CAN_F9R1_FB17_Pos */
#define CAN_F9R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 9 word 1 bit 17 (`CANx_F9R1.FB17`) bit mask @def CAN_F9R1_FB17_Msk */
#define CAN_F9R1_FB17_Msk			REG_BIT_MASK(CAN_F9R1_FB17_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 17 (`CANx_F9R1.FB17`) bit mask alias @def CAN_F9R1_FB17 */
#define CAN_F9R1_FB17				CAN_F9R1_FB17_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 18 (`CANx_F9R1.FB18`) bit position @def CAN_F9R1_FB18_Pos */
#define CAN_F9R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 9 word 1 bit 18 (`CANx_F9R1.FB18`) bit mask @def CAN_F9R1_FB18_Msk */
#define CAN_F9R1_FB18_Msk			REG_BIT_MASK(CAN_F9R1_FB18_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 18 (`CANx_F9R1.FB18`) bit mask alias @def CAN_F9R1_FB18 */
#define CAN_F9R1_FB18				CAN_F9R1_FB18_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 19 (`CANx_F9R1.FB19`) bit position @def CAN_F9R1_FB19_Pos */
#define CAN_F9R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 9 word 1 bit 19 (`CANx_F9R1.FB19`) bit mask @def CAN_F9R1_FB19_Msk */
#define CAN_F9R1_FB19_Msk			REG_BIT_MASK(CAN_F9R1_FB19_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 19 (`CANx_F9R1.FB19`) bit mask alias @def CAN_F9R1_FB19 */
#define CAN_F9R1_FB19				CAN_F9R1_FB19_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 20 (`CANx_F9R1.FB20`) bit position @def CAN_F9R1_FB20_Pos */
#define CAN_F9R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 9 word 1 bit 20 (`CANx_F9R1.FB20`) bit mask @def CAN_F9R1_FB20_Msk */
#define CAN_F9R1_FB20_Msk			REG_BIT_MASK(CAN_F9R1_FB20_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 20 (`CANx_F9R1.FB20`) bit mask alias @def CAN_F9R1_FB20 */
#define CAN_F9R1_FB20				CAN_F9R1_FB20_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 21 (`CANx_F9R1.FB21`) bit position @def CAN_F9R1_FB21_Pos */
#define CAN_F9R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 9 word 1 bit 21 (`CANx_F9R1.FB21`) bit mask @def CAN_F9R1_FB21_Msk */
#define CAN_F9R1_FB21_Msk			REG_BIT_MASK(CAN_F9R1_FB21_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 21 (`CANx_F9R1.FB21`) bit mask alias @def CAN_F9R1_FB21 */
#define CAN_F9R1_FB21				CAN_F9R1_FB21_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 22 (`CANx_F9R1.FB22`) bit position @def CAN_F9R1_FB22_Pos */
#define CAN_F9R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 9 word 1 bit 22 (`CANx_F9R1.FB22`) bit mask @def CAN_F9R1_FB22_Msk */
#define CAN_F9R1_FB22_Msk			REG_BIT_MASK(CAN_F9R1_FB22_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 22 (`CANx_F9R1.FB22`) bit mask alias @def CAN_F9R1_FB22 */
#define CAN_F9R1_FB22				CAN_F9R1_FB22_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 23 (`CANx_F9R1.FB23`) bit position @def CAN_F9R1_FB23_Pos */
#define CAN_F9R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 9 word 1 bit 23 (`CANx_F9R1.FB23`) bit mask @def CAN_F9R1_FB23_Msk */
#define CAN_F9R1_FB23_Msk			REG_BIT_MASK(CAN_F9R1_FB23_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 23 (`CANx_F9R1.FB23`) bit mask alias @def CAN_F9R1_FB23 */
#define CAN_F9R1_FB23				CAN_F9R1_FB23_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 24 (`CANx_F9R1.FB24`) bit position @def CAN_F9R1_FB24_Pos */
#define CAN_F9R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 9 word 1 bit 24 (`CANx_F9R1.FB24`) bit mask @def CAN_F9R1_FB24_Msk */
#define CAN_F9R1_FB24_Msk			REG_BIT_MASK(CAN_F9R1_FB24_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 24 (`CANx_F9R1.FB24`) bit mask alias @def CAN_F9R1_FB24 */
#define CAN_F9R1_FB24				CAN_F9R1_FB24_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 25 (`CANx_F9R1.FB25`) bit position @def CAN_F9R1_FB25_Pos */
#define CAN_F9R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 9 word 1 bit 25 (`CANx_F9R1.FB25`) bit mask @def CAN_F9R1_FB25_Msk */
#define CAN_F9R1_FB25_Msk			REG_BIT_MASK(CAN_F9R1_FB25_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 25 (`CANx_F9R1.FB25`) bit mask alias @def CAN_F9R1_FB25 */
#define CAN_F9R1_FB25				CAN_F9R1_FB25_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 26 (`CANx_F9R1.FB26`) bit position @def CAN_F9R1_FB26_Pos */
#define CAN_F9R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 9 word 1 bit 26 (`CANx_F9R1.FB26`) bit mask @def CAN_F9R1_FB26_Msk */
#define CAN_F9R1_FB26_Msk			REG_BIT_MASK(CAN_F9R1_FB26_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 26 (`CANx_F9R1.FB26`) bit mask alias @def CAN_F9R1_FB26 */
#define CAN_F9R1_FB26				CAN_F9R1_FB26_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 27 (`CANx_F9R1.FB27`) bit position @def CAN_F9R1_FB27_Pos */
#define CAN_F9R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 9 word 1 bit 27 (`CANx_F9R1.FB27`) bit mask @def CAN_F9R1_FB27_Msk */
#define CAN_F9R1_FB27_Msk			REG_BIT_MASK(CAN_F9R1_FB27_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 27 (`CANx_F9R1.FB27`) bit mask alias @def CAN_F9R1_FB27 */
#define CAN_F9R1_FB27				CAN_F9R1_FB27_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 28 (`CANx_F9R1.FB28`) bit position @def CAN_F9R1_FB28_Pos */
#define CAN_F9R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 9 word 1 bit 28 (`CANx_F9R1.FB28`) bit mask @def CAN_F9R1_FB28_Msk */
#define CAN_F9R1_FB28_Msk			REG_BIT_MASK(CAN_F9R1_FB28_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 28 (`CANx_F9R1.FB28`) bit mask alias @def CAN_F9R1_FB28 */
#define CAN_F9R1_FB28				CAN_F9R1_FB28_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 29 (`CANx_F9R1.FB29`) bit position @def CAN_F9R1_FB29_Pos */
#define CAN_F9R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 9 word 1 bit 29 (`CANx_F9R1.FB29`) bit mask @def CAN_F9R1_FB29_Msk */
#define CAN_F9R1_FB29_Msk			REG_BIT_MASK(CAN_F9R1_FB29_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 29 (`CANx_F9R1.FB29`) bit mask alias @def CAN_F9R1_FB29 */
#define CAN_F9R1_FB29				CAN_F9R1_FB29_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 30 (`CANx_F9R1.FB30`) bit position @def CAN_F9R1_FB30_Pos */
#define CAN_F9R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 9 word 1 bit 30 (`CANx_F9R1.FB30`) bit mask @def CAN_F9R1_FB30_Msk */
#define CAN_F9R1_FB30_Msk			REG_BIT_MASK(CAN_F9R1_FB30_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 30 (`CANx_F9R1.FB30`) bit mask alias @def CAN_F9R1_FB30 */
#define CAN_F9R1_FB30				CAN_F9R1_FB30_Msk

/** @brief Acceptance-filter bank 9 word 1 bit 31 (`CANx_F9R1.FB31`) bit position @def CAN_F9R1_FB31_Pos */
#define CAN_F9R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 9 word 1 bit 31 (`CANx_F9R1.FB31`) bit mask @def CAN_F9R1_FB31_Msk */
#define CAN_F9R1_FB31_Msk			REG_BIT_MASK(CAN_F9R1_FB31_Pos)
/** @brief Acceptance-filter bank 9 word 1 bit 31 (`CANx_F9R1.FB31`) bit mask alias @def CAN_F9R1_FB31 */
#define CAN_F9R1_FB31				CAN_F9R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F10R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 10 word 1 bit 0 (`CANx_F10R1.FB0`) bit position @def CAN_F10R1_FB0_Pos */
#define CAN_F10R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 10 word 1 bit 0 (`CANx_F10R1.FB0`) bit mask @def CAN_F10R1_FB0_Msk */
#define CAN_F10R1_FB0_Msk			REG_BIT_MASK(CAN_F10R1_FB0_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 0 (`CANx_F10R1.FB0`) bit mask alias @def CAN_F10R1_FB0 */
#define CAN_F10R1_FB0				CAN_F10R1_FB0_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 1 (`CANx_F10R1.FB1`) bit position @def CAN_F10R1_FB1_Pos */
#define CAN_F10R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 10 word 1 bit 1 (`CANx_F10R1.FB1`) bit mask @def CAN_F10R1_FB1_Msk */
#define CAN_F10R1_FB1_Msk			REG_BIT_MASK(CAN_F10R1_FB1_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 1 (`CANx_F10R1.FB1`) bit mask alias @def CAN_F10R1_FB1 */
#define CAN_F10R1_FB1				CAN_F10R1_FB1_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 2 (`CANx_F10R1.FB2`) bit position @def CAN_F10R1_FB2_Pos */
#define CAN_F10R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 10 word 1 bit 2 (`CANx_F10R1.FB2`) bit mask @def CAN_F10R1_FB2_Msk */
#define CAN_F10R1_FB2_Msk			REG_BIT_MASK(CAN_F10R1_FB2_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 2 (`CANx_F10R1.FB2`) bit mask alias @def CAN_F10R1_FB2 */
#define CAN_F10R1_FB2				CAN_F10R1_FB2_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 3 (`CANx_F10R1.FB3`) bit position @def CAN_F10R1_FB3_Pos */
#define CAN_F10R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 10 word 1 bit 3 (`CANx_F10R1.FB3`) bit mask @def CAN_F10R1_FB3_Msk */
#define CAN_F10R1_FB3_Msk			REG_BIT_MASK(CAN_F10R1_FB3_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 3 (`CANx_F10R1.FB3`) bit mask alias @def CAN_F10R1_FB3 */
#define CAN_F10R1_FB3				CAN_F10R1_FB3_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 4 (`CANx_F10R1.FB4`) bit position @def CAN_F10R1_FB4_Pos */
#define CAN_F10R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 10 word 1 bit 4 (`CANx_F10R1.FB4`) bit mask @def CAN_F10R1_FB4_Msk */
#define CAN_F10R1_FB4_Msk			REG_BIT_MASK(CAN_F10R1_FB4_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 4 (`CANx_F10R1.FB4`) bit mask alias @def CAN_F10R1_FB4 */
#define CAN_F10R1_FB4				CAN_F10R1_FB4_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 5 (`CANx_F10R1.FB5`) bit position @def CAN_F10R1_FB5_Pos */
#define CAN_F10R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 10 word 1 bit 5 (`CANx_F10R1.FB5`) bit mask @def CAN_F10R1_FB5_Msk */
#define CAN_F10R1_FB5_Msk			REG_BIT_MASK(CAN_F10R1_FB5_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 5 (`CANx_F10R1.FB5`) bit mask alias @def CAN_F10R1_FB5 */
#define CAN_F10R1_FB5				CAN_F10R1_FB5_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 6 (`CANx_F10R1.FB6`) bit position @def CAN_F10R1_FB6_Pos */
#define CAN_F10R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 10 word 1 bit 6 (`CANx_F10R1.FB6`) bit mask @def CAN_F10R1_FB6_Msk */
#define CAN_F10R1_FB6_Msk			REG_BIT_MASK(CAN_F10R1_FB6_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 6 (`CANx_F10R1.FB6`) bit mask alias @def CAN_F10R1_FB6 */
#define CAN_F10R1_FB6				CAN_F10R1_FB6_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 7 (`CANx_F10R1.FB7`) bit position @def CAN_F10R1_FB7_Pos */
#define CAN_F10R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 10 word 1 bit 7 (`CANx_F10R1.FB7`) bit mask @def CAN_F10R1_FB7_Msk */
#define CAN_F10R1_FB7_Msk			REG_BIT_MASK(CAN_F10R1_FB7_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 7 (`CANx_F10R1.FB7`) bit mask alias @def CAN_F10R1_FB7 */
#define CAN_F10R1_FB7				CAN_F10R1_FB7_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 8 (`CANx_F10R1.FB8`) bit position @def CAN_F10R1_FB8_Pos */
#define CAN_F10R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 10 word 1 bit 8 (`CANx_F10R1.FB8`) bit mask @def CAN_F10R1_FB8_Msk */
#define CAN_F10R1_FB8_Msk			REG_BIT_MASK(CAN_F10R1_FB8_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 8 (`CANx_F10R1.FB8`) bit mask alias @def CAN_F10R1_FB8 */
#define CAN_F10R1_FB8				CAN_F10R1_FB8_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 9 (`CANx_F10R1.FB9`) bit position @def CAN_F10R1_FB9_Pos */
#define CAN_F10R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 10 word 1 bit 9 (`CANx_F10R1.FB9`) bit mask @def CAN_F10R1_FB9_Msk */
#define CAN_F10R1_FB9_Msk			REG_BIT_MASK(CAN_F10R1_FB9_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 9 (`CANx_F10R1.FB9`) bit mask alias @def CAN_F10R1_FB9 */
#define CAN_F10R1_FB9				CAN_F10R1_FB9_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 10 (`CANx_F10R1.FB10`) bit position @def CAN_F10R1_FB10_Pos */
#define CAN_F10R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 10 word 1 bit 10 (`CANx_F10R1.FB10`) bit mask @def CAN_F10R1_FB10_Msk */
#define CAN_F10R1_FB10_Msk			REG_BIT_MASK(CAN_F10R1_FB10_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 10 (`CANx_F10R1.FB10`) bit mask alias @def CAN_F10R1_FB10 */
#define CAN_F10R1_FB10				CAN_F10R1_FB10_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 11 (`CANx_F10R1.FB11`) bit position @def CAN_F10R1_FB11_Pos */
#define CAN_F10R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 10 word 1 bit 11 (`CANx_F10R1.FB11`) bit mask @def CAN_F10R1_FB11_Msk */
#define CAN_F10R1_FB11_Msk			REG_BIT_MASK(CAN_F10R1_FB11_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 11 (`CANx_F10R1.FB11`) bit mask alias @def CAN_F10R1_FB11 */
#define CAN_F10R1_FB11				CAN_F10R1_FB11_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 12 (`CANx_F10R1.FB12`) bit position @def CAN_F10R1_FB12_Pos */
#define CAN_F10R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 10 word 1 bit 12 (`CANx_F10R1.FB12`) bit mask @def CAN_F10R1_FB12_Msk */
#define CAN_F10R1_FB12_Msk			REG_BIT_MASK(CAN_F10R1_FB12_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 12 (`CANx_F10R1.FB12`) bit mask alias @def CAN_F10R1_FB12 */
#define CAN_F10R1_FB12				CAN_F10R1_FB12_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 13 (`CANx_F10R1.FB13`) bit position @def CAN_F10R1_FB13_Pos */
#define CAN_F10R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 10 word 1 bit 13 (`CANx_F10R1.FB13`) bit mask @def CAN_F10R1_FB13_Msk */
#define CAN_F10R1_FB13_Msk			REG_BIT_MASK(CAN_F10R1_FB13_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 13 (`CANx_F10R1.FB13`) bit mask alias @def CAN_F10R1_FB13 */
#define CAN_F10R1_FB13				CAN_F10R1_FB13_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 14 (`CANx_F10R1.FB14`) bit position @def CAN_F10R1_FB14_Pos */
#define CAN_F10R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 10 word 1 bit 14 (`CANx_F10R1.FB14`) bit mask @def CAN_F10R1_FB14_Msk */
#define CAN_F10R1_FB14_Msk			REG_BIT_MASK(CAN_F10R1_FB14_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 14 (`CANx_F10R1.FB14`) bit mask alias @def CAN_F10R1_FB14 */
#define CAN_F10R1_FB14				CAN_F10R1_FB14_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 15 (`CANx_F10R1.FB15`) bit position @def CAN_F10R1_FB15_Pos */
#define CAN_F10R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 10 word 1 bit 15 (`CANx_F10R1.FB15`) bit mask @def CAN_F10R1_FB15_Msk */
#define CAN_F10R1_FB15_Msk			REG_BIT_MASK(CAN_F10R1_FB15_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 15 (`CANx_F10R1.FB15`) bit mask alias @def CAN_F10R1_FB15 */
#define CAN_F10R1_FB15				CAN_F10R1_FB15_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 16 (`CANx_F10R1.FB16`) bit position @def CAN_F10R1_FB16_Pos */
#define CAN_F10R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 10 word 1 bit 16 (`CANx_F10R1.FB16`) bit mask @def CAN_F10R1_FB16_Msk */
#define CAN_F10R1_FB16_Msk			REG_BIT_MASK(CAN_F10R1_FB16_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 16 (`CANx_F10R1.FB16`) bit mask alias @def CAN_F10R1_FB16 */
#define CAN_F10R1_FB16				CAN_F10R1_FB16_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 17 (`CANx_F10R1.FB17`) bit position @def CAN_F10R1_FB17_Pos */
#define CAN_F10R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 10 word 1 bit 17 (`CANx_F10R1.FB17`) bit mask @def CAN_F10R1_FB17_Msk */
#define CAN_F10R1_FB17_Msk			REG_BIT_MASK(CAN_F10R1_FB17_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 17 (`CANx_F10R1.FB17`) bit mask alias @def CAN_F10R1_FB17 */
#define CAN_F10R1_FB17				CAN_F10R1_FB17_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 18 (`CANx_F10R1.FB18`) bit position @def CAN_F10R1_FB18_Pos */
#define CAN_F10R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 10 word 1 bit 18 (`CANx_F10R1.FB18`) bit mask @def CAN_F10R1_FB18_Msk */
#define CAN_F10R1_FB18_Msk			REG_BIT_MASK(CAN_F10R1_FB18_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 18 (`CANx_F10R1.FB18`) bit mask alias @def CAN_F10R1_FB18 */
#define CAN_F10R1_FB18				CAN_F10R1_FB18_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 19 (`CANx_F10R1.FB19`) bit position @def CAN_F10R1_FB19_Pos */
#define CAN_F10R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 10 word 1 bit 19 (`CANx_F10R1.FB19`) bit mask @def CAN_F10R1_FB19_Msk */
#define CAN_F10R1_FB19_Msk			REG_BIT_MASK(CAN_F10R1_FB19_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 19 (`CANx_F10R1.FB19`) bit mask alias @def CAN_F10R1_FB19 */
#define CAN_F10R1_FB19				CAN_F10R1_FB19_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 20 (`CANx_F10R1.FB20`) bit position @def CAN_F10R1_FB20_Pos */
#define CAN_F10R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 10 word 1 bit 20 (`CANx_F10R1.FB20`) bit mask @def CAN_F10R1_FB20_Msk */
#define CAN_F10R1_FB20_Msk			REG_BIT_MASK(CAN_F10R1_FB20_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 20 (`CANx_F10R1.FB20`) bit mask alias @def CAN_F10R1_FB20 */
#define CAN_F10R1_FB20				CAN_F10R1_FB20_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 21 (`CANx_F10R1.FB21`) bit position @def CAN_F10R1_FB21_Pos */
#define CAN_F10R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 10 word 1 bit 21 (`CANx_F10R1.FB21`) bit mask @def CAN_F10R1_FB21_Msk */
#define CAN_F10R1_FB21_Msk			REG_BIT_MASK(CAN_F10R1_FB21_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 21 (`CANx_F10R1.FB21`) bit mask alias @def CAN_F10R1_FB21 */
#define CAN_F10R1_FB21				CAN_F10R1_FB21_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 22 (`CANx_F10R1.FB22`) bit position @def CAN_F10R1_FB22_Pos */
#define CAN_F10R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 10 word 1 bit 22 (`CANx_F10R1.FB22`) bit mask @def CAN_F10R1_FB22_Msk */
#define CAN_F10R1_FB22_Msk			REG_BIT_MASK(CAN_F10R1_FB22_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 22 (`CANx_F10R1.FB22`) bit mask alias @def CAN_F10R1_FB22 */
#define CAN_F10R1_FB22				CAN_F10R1_FB22_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 23 (`CANx_F10R1.FB23`) bit position @def CAN_F10R1_FB23_Pos */
#define CAN_F10R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 10 word 1 bit 23 (`CANx_F10R1.FB23`) bit mask @def CAN_F10R1_FB23_Msk */
#define CAN_F10R1_FB23_Msk			REG_BIT_MASK(CAN_F10R1_FB23_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 23 (`CANx_F10R1.FB23`) bit mask alias @def CAN_F10R1_FB23 */
#define CAN_F10R1_FB23				CAN_F10R1_FB23_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 24 (`CANx_F10R1.FB24`) bit position @def CAN_F10R1_FB24_Pos */
#define CAN_F10R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 10 word 1 bit 24 (`CANx_F10R1.FB24`) bit mask @def CAN_F10R1_FB24_Msk */
#define CAN_F10R1_FB24_Msk			REG_BIT_MASK(CAN_F10R1_FB24_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 24 (`CANx_F10R1.FB24`) bit mask alias @def CAN_F10R1_FB24 */
#define CAN_F10R1_FB24				CAN_F10R1_FB24_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 25 (`CANx_F10R1.FB25`) bit position @def CAN_F10R1_FB25_Pos */
#define CAN_F10R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 10 word 1 bit 25 (`CANx_F10R1.FB25`) bit mask @def CAN_F10R1_FB25_Msk */
#define CAN_F10R1_FB25_Msk			REG_BIT_MASK(CAN_F10R1_FB25_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 25 (`CANx_F10R1.FB25`) bit mask alias @def CAN_F10R1_FB25 */
#define CAN_F10R1_FB25				CAN_F10R1_FB25_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 26 (`CANx_F10R1.FB26`) bit position @def CAN_F10R1_FB26_Pos */
#define CAN_F10R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 10 word 1 bit 26 (`CANx_F10R1.FB26`) bit mask @def CAN_F10R1_FB26_Msk */
#define CAN_F10R1_FB26_Msk			REG_BIT_MASK(CAN_F10R1_FB26_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 26 (`CANx_F10R1.FB26`) bit mask alias @def CAN_F10R1_FB26 */
#define CAN_F10R1_FB26				CAN_F10R1_FB26_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 27 (`CANx_F10R1.FB27`) bit position @def CAN_F10R1_FB27_Pos */
#define CAN_F10R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 10 word 1 bit 27 (`CANx_F10R1.FB27`) bit mask @def CAN_F10R1_FB27_Msk */
#define CAN_F10R1_FB27_Msk			REG_BIT_MASK(CAN_F10R1_FB27_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 27 (`CANx_F10R1.FB27`) bit mask alias @def CAN_F10R1_FB27 */
#define CAN_F10R1_FB27				CAN_F10R1_FB27_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 28 (`CANx_F10R1.FB28`) bit position @def CAN_F10R1_FB28_Pos */
#define CAN_F10R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 10 word 1 bit 28 (`CANx_F10R1.FB28`) bit mask @def CAN_F10R1_FB28_Msk */
#define CAN_F10R1_FB28_Msk			REG_BIT_MASK(CAN_F10R1_FB28_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 28 (`CANx_F10R1.FB28`) bit mask alias @def CAN_F10R1_FB28 */
#define CAN_F10R1_FB28				CAN_F10R1_FB28_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 29 (`CANx_F10R1.FB29`) bit position @def CAN_F10R1_FB29_Pos */
#define CAN_F10R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 10 word 1 bit 29 (`CANx_F10R1.FB29`) bit mask @def CAN_F10R1_FB29_Msk */
#define CAN_F10R1_FB29_Msk			REG_BIT_MASK(CAN_F10R1_FB29_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 29 (`CANx_F10R1.FB29`) bit mask alias @def CAN_F10R1_FB29 */
#define CAN_F10R1_FB29				CAN_F10R1_FB29_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 30 (`CANx_F10R1.FB30`) bit position @def CAN_F10R1_FB30_Pos */
#define CAN_F10R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 10 word 1 bit 30 (`CANx_F10R1.FB30`) bit mask @def CAN_F10R1_FB30_Msk */
#define CAN_F10R1_FB30_Msk			REG_BIT_MASK(CAN_F10R1_FB30_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 30 (`CANx_F10R1.FB30`) bit mask alias @def CAN_F10R1_FB30 */
#define CAN_F10R1_FB30				CAN_F10R1_FB30_Msk

/** @brief Acceptance-filter bank 10 word 1 bit 31 (`CANx_F10R1.FB31`) bit position @def CAN_F10R1_FB31_Pos */
#define CAN_F10R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 10 word 1 bit 31 (`CANx_F10R1.FB31`) bit mask @def CAN_F10R1_FB31_Msk */
#define CAN_F10R1_FB31_Msk			REG_BIT_MASK(CAN_F10R1_FB31_Pos)
/** @brief Acceptance-filter bank 10 word 1 bit 31 (`CANx_F10R1.FB31`) bit mask alias @def CAN_F10R1_FB31 */
#define CAN_F10R1_FB31				CAN_F10R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F11R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 11 word 1 bit 0 (`CANx_F11R1.FB0`) bit position @def CAN_F11R1_FB0_Pos */
#define CAN_F11R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 11 word 1 bit 0 (`CANx_F11R1.FB0`) bit mask @def CAN_F11R1_FB0_Msk */
#define CAN_F11R1_FB0_Msk			REG_BIT_MASK(CAN_F11R1_FB0_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 0 (`CANx_F11R1.FB0`) bit mask alias @def CAN_F11R1_FB0 */
#define CAN_F11R1_FB0				CAN_F11R1_FB0_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 1 (`CANx_F11R1.FB1`) bit position @def CAN_F11R1_FB1_Pos */
#define CAN_F11R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 11 word 1 bit 1 (`CANx_F11R1.FB1`) bit mask @def CAN_F11R1_FB1_Msk */
#define CAN_F11R1_FB1_Msk			REG_BIT_MASK(CAN_F11R1_FB1_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 1 (`CANx_F11R1.FB1`) bit mask alias @def CAN_F11R1_FB1 */
#define CAN_F11R1_FB1				CAN_F11R1_FB1_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 2 (`CANx_F11R1.FB2`) bit position @def CAN_F11R1_FB2_Pos */
#define CAN_F11R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 11 word 1 bit 2 (`CANx_F11R1.FB2`) bit mask @def CAN_F11R1_FB2_Msk */
#define CAN_F11R1_FB2_Msk			REG_BIT_MASK(CAN_F11R1_FB2_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 2 (`CANx_F11R1.FB2`) bit mask alias @def CAN_F11R1_FB2 */
#define CAN_F11R1_FB2				CAN_F11R1_FB2_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 3 (`CANx_F11R1.FB3`) bit position @def CAN_F11R1_FB3_Pos */
#define CAN_F11R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 11 word 1 bit 3 (`CANx_F11R1.FB3`) bit mask @def CAN_F11R1_FB3_Msk */
#define CAN_F11R1_FB3_Msk			REG_BIT_MASK(CAN_F11R1_FB3_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 3 (`CANx_F11R1.FB3`) bit mask alias @def CAN_F11R1_FB3 */
#define CAN_F11R1_FB3				CAN_F11R1_FB3_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 4 (`CANx_F11R1.FB4`) bit position @def CAN_F11R1_FB4_Pos */
#define CAN_F11R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 11 word 1 bit 4 (`CANx_F11R1.FB4`) bit mask @def CAN_F11R1_FB4_Msk */
#define CAN_F11R1_FB4_Msk			REG_BIT_MASK(CAN_F11R1_FB4_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 4 (`CANx_F11R1.FB4`) bit mask alias @def CAN_F11R1_FB4 */
#define CAN_F11R1_FB4				CAN_F11R1_FB4_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 5 (`CANx_F11R1.FB5`) bit position @def CAN_F11R1_FB5_Pos */
#define CAN_F11R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 11 word 1 bit 5 (`CANx_F11R1.FB5`) bit mask @def CAN_F11R1_FB5_Msk */
#define CAN_F11R1_FB5_Msk			REG_BIT_MASK(CAN_F11R1_FB5_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 5 (`CANx_F11R1.FB5`) bit mask alias @def CAN_F11R1_FB5 */
#define CAN_F11R1_FB5				CAN_F11R1_FB5_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 6 (`CANx_F11R1.FB6`) bit position @def CAN_F11R1_FB6_Pos */
#define CAN_F11R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 11 word 1 bit 6 (`CANx_F11R1.FB6`) bit mask @def CAN_F11R1_FB6_Msk */
#define CAN_F11R1_FB6_Msk			REG_BIT_MASK(CAN_F11R1_FB6_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 6 (`CANx_F11R1.FB6`) bit mask alias @def CAN_F11R1_FB6 */
#define CAN_F11R1_FB6				CAN_F11R1_FB6_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 7 (`CANx_F11R1.FB7`) bit position @def CAN_F11R1_FB7_Pos */
#define CAN_F11R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 11 word 1 bit 7 (`CANx_F11R1.FB7`) bit mask @def CAN_F11R1_FB7_Msk */
#define CAN_F11R1_FB7_Msk			REG_BIT_MASK(CAN_F11R1_FB7_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 7 (`CANx_F11R1.FB7`) bit mask alias @def CAN_F11R1_FB7 */
#define CAN_F11R1_FB7				CAN_F11R1_FB7_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 8 (`CANx_F11R1.FB8`) bit position @def CAN_F11R1_FB8_Pos */
#define CAN_F11R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 11 word 1 bit 8 (`CANx_F11R1.FB8`) bit mask @def CAN_F11R1_FB8_Msk */
#define CAN_F11R1_FB8_Msk			REG_BIT_MASK(CAN_F11R1_FB8_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 8 (`CANx_F11R1.FB8`) bit mask alias @def CAN_F11R1_FB8 */
#define CAN_F11R1_FB8				CAN_F11R1_FB8_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 9 (`CANx_F11R1.FB9`) bit position @def CAN_F11R1_FB9_Pos */
#define CAN_F11R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 11 word 1 bit 9 (`CANx_F11R1.FB9`) bit mask @def CAN_F11R1_FB9_Msk */
#define CAN_F11R1_FB9_Msk			REG_BIT_MASK(CAN_F11R1_FB9_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 9 (`CANx_F11R1.FB9`) bit mask alias @def CAN_F11R1_FB9 */
#define CAN_F11R1_FB9				CAN_F11R1_FB9_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 10 (`CANx_F11R1.FB10`) bit position @def CAN_F11R1_FB10_Pos */
#define CAN_F11R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 11 word 1 bit 10 (`CANx_F11R1.FB10`) bit mask @def CAN_F11R1_FB10_Msk */
#define CAN_F11R1_FB10_Msk			REG_BIT_MASK(CAN_F11R1_FB10_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 10 (`CANx_F11R1.FB10`) bit mask alias @def CAN_F11R1_FB10 */
#define CAN_F11R1_FB10				CAN_F11R1_FB10_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 11 (`CANx_F11R1.FB11`) bit position @def CAN_F11R1_FB11_Pos */
#define CAN_F11R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 11 word 1 bit 11 (`CANx_F11R1.FB11`) bit mask @def CAN_F11R1_FB11_Msk */
#define CAN_F11R1_FB11_Msk			REG_BIT_MASK(CAN_F11R1_FB11_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 11 (`CANx_F11R1.FB11`) bit mask alias @def CAN_F11R1_FB11 */
#define CAN_F11R1_FB11				CAN_F11R1_FB11_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 12 (`CANx_F11R1.FB12`) bit position @def CAN_F11R1_FB12_Pos */
#define CAN_F11R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 11 word 1 bit 12 (`CANx_F11R1.FB12`) bit mask @def CAN_F11R1_FB12_Msk */
#define CAN_F11R1_FB12_Msk			REG_BIT_MASK(CAN_F11R1_FB12_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 12 (`CANx_F11R1.FB12`) bit mask alias @def CAN_F11R1_FB12 */
#define CAN_F11R1_FB12				CAN_F11R1_FB12_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 13 (`CANx_F11R1.FB13`) bit position @def CAN_F11R1_FB13_Pos */
#define CAN_F11R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 11 word 1 bit 13 (`CANx_F11R1.FB13`) bit mask @def CAN_F11R1_FB13_Msk */
#define CAN_F11R1_FB13_Msk			REG_BIT_MASK(CAN_F11R1_FB13_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 13 (`CANx_F11R1.FB13`) bit mask alias @def CAN_F11R1_FB13 */
#define CAN_F11R1_FB13				CAN_F11R1_FB13_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 14 (`CANx_F11R1.FB14`) bit position @def CAN_F11R1_FB14_Pos */
#define CAN_F11R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 11 word 1 bit 14 (`CANx_F11R1.FB14`) bit mask @def CAN_F11R1_FB14_Msk */
#define CAN_F11R1_FB14_Msk			REG_BIT_MASK(CAN_F11R1_FB14_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 14 (`CANx_F11R1.FB14`) bit mask alias @def CAN_F11R1_FB14 */
#define CAN_F11R1_FB14				CAN_F11R1_FB14_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 15 (`CANx_F11R1.FB15`) bit position @def CAN_F11R1_FB15_Pos */
#define CAN_F11R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 11 word 1 bit 15 (`CANx_F11R1.FB15`) bit mask @def CAN_F11R1_FB15_Msk */
#define CAN_F11R1_FB15_Msk			REG_BIT_MASK(CAN_F11R1_FB15_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 15 (`CANx_F11R1.FB15`) bit mask alias @def CAN_F11R1_FB15 */
#define CAN_F11R1_FB15				CAN_F11R1_FB15_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 16 (`CANx_F11R1.FB16`) bit position @def CAN_F11R1_FB16_Pos */
#define CAN_F11R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 11 word 1 bit 16 (`CANx_F11R1.FB16`) bit mask @def CAN_F11R1_FB16_Msk */
#define CAN_F11R1_FB16_Msk			REG_BIT_MASK(CAN_F11R1_FB16_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 16 (`CANx_F11R1.FB16`) bit mask alias @def CAN_F11R1_FB16 */
#define CAN_F11R1_FB16				CAN_F11R1_FB16_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 17 (`CANx_F11R1.FB17`) bit position @def CAN_F11R1_FB17_Pos */
#define CAN_F11R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 11 word 1 bit 17 (`CANx_F11R1.FB17`) bit mask @def CAN_F11R1_FB17_Msk */
#define CAN_F11R1_FB17_Msk			REG_BIT_MASK(CAN_F11R1_FB17_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 17 (`CANx_F11R1.FB17`) bit mask alias @def CAN_F11R1_FB17 */
#define CAN_F11R1_FB17				CAN_F11R1_FB17_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 18 (`CANx_F11R1.FB18`) bit position @def CAN_F11R1_FB18_Pos */
#define CAN_F11R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 11 word 1 bit 18 (`CANx_F11R1.FB18`) bit mask @def CAN_F11R1_FB18_Msk */
#define CAN_F11R1_FB18_Msk			REG_BIT_MASK(CAN_F11R1_FB18_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 18 (`CANx_F11R1.FB18`) bit mask alias @def CAN_F11R1_FB18 */
#define CAN_F11R1_FB18				CAN_F11R1_FB18_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 19 (`CANx_F11R1.FB19`) bit position @def CAN_F11R1_FB19_Pos */
#define CAN_F11R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 11 word 1 bit 19 (`CANx_F11R1.FB19`) bit mask @def CAN_F11R1_FB19_Msk */
#define CAN_F11R1_FB19_Msk			REG_BIT_MASK(CAN_F11R1_FB19_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 19 (`CANx_F11R1.FB19`) bit mask alias @def CAN_F11R1_FB19 */
#define CAN_F11R1_FB19				CAN_F11R1_FB19_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 20 (`CANx_F11R1.FB20`) bit position @def CAN_F11R1_FB20_Pos */
#define CAN_F11R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 11 word 1 bit 20 (`CANx_F11R1.FB20`) bit mask @def CAN_F11R1_FB20_Msk */
#define CAN_F11R1_FB20_Msk			REG_BIT_MASK(CAN_F11R1_FB20_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 20 (`CANx_F11R1.FB20`) bit mask alias @def CAN_F11R1_FB20 */
#define CAN_F11R1_FB20				CAN_F11R1_FB20_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 21 (`CANx_F11R1.FB21`) bit position @def CAN_F11R1_FB21_Pos */
#define CAN_F11R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 11 word 1 bit 21 (`CANx_F11R1.FB21`) bit mask @def CAN_F11R1_FB21_Msk */
#define CAN_F11R1_FB21_Msk			REG_BIT_MASK(CAN_F11R1_FB21_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 21 (`CANx_F11R1.FB21`) bit mask alias @def CAN_F11R1_FB21 */
#define CAN_F11R1_FB21				CAN_F11R1_FB21_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 22 (`CANx_F11R1.FB22`) bit position @def CAN_F11R1_FB22_Pos */
#define CAN_F11R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 11 word 1 bit 22 (`CANx_F11R1.FB22`) bit mask @def CAN_F11R1_FB22_Msk */
#define CAN_F11R1_FB22_Msk			REG_BIT_MASK(CAN_F11R1_FB22_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 22 (`CANx_F11R1.FB22`) bit mask alias @def CAN_F11R1_FB22 */
#define CAN_F11R1_FB22				CAN_F11R1_FB22_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 23 (`CANx_F11R1.FB23`) bit position @def CAN_F11R1_FB23_Pos */
#define CAN_F11R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 11 word 1 bit 23 (`CANx_F11R1.FB23`) bit mask @def CAN_F11R1_FB23_Msk */
#define CAN_F11R1_FB23_Msk			REG_BIT_MASK(CAN_F11R1_FB23_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 23 (`CANx_F11R1.FB23`) bit mask alias @def CAN_F11R1_FB23 */
#define CAN_F11R1_FB23				CAN_F11R1_FB23_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 24 (`CANx_F11R1.FB24`) bit position @def CAN_F11R1_FB24_Pos */
#define CAN_F11R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 11 word 1 bit 24 (`CANx_F11R1.FB24`) bit mask @def CAN_F11R1_FB24_Msk */
#define CAN_F11R1_FB24_Msk			REG_BIT_MASK(CAN_F11R1_FB24_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 24 (`CANx_F11R1.FB24`) bit mask alias @def CAN_F11R1_FB24 */
#define CAN_F11R1_FB24				CAN_F11R1_FB24_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 25 (`CANx_F11R1.FB25`) bit position @def CAN_F11R1_FB25_Pos */
#define CAN_F11R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 11 word 1 bit 25 (`CANx_F11R1.FB25`) bit mask @def CAN_F11R1_FB25_Msk */
#define CAN_F11R1_FB25_Msk			REG_BIT_MASK(CAN_F11R1_FB25_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 25 (`CANx_F11R1.FB25`) bit mask alias @def CAN_F11R1_FB25 */
#define CAN_F11R1_FB25				CAN_F11R1_FB25_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 26 (`CANx_F11R1.FB26`) bit position @def CAN_F11R1_FB26_Pos */
#define CAN_F11R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 11 word 1 bit 26 (`CANx_F11R1.FB26`) bit mask @def CAN_F11R1_FB26_Msk */
#define CAN_F11R1_FB26_Msk			REG_BIT_MASK(CAN_F11R1_FB26_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 26 (`CANx_F11R1.FB26`) bit mask alias @def CAN_F11R1_FB26 */
#define CAN_F11R1_FB26				CAN_F11R1_FB26_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 27 (`CANx_F11R1.FB27`) bit position @def CAN_F11R1_FB27_Pos */
#define CAN_F11R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 11 word 1 bit 27 (`CANx_F11R1.FB27`) bit mask @def CAN_F11R1_FB27_Msk */
#define CAN_F11R1_FB27_Msk			REG_BIT_MASK(CAN_F11R1_FB27_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 27 (`CANx_F11R1.FB27`) bit mask alias @def CAN_F11R1_FB27 */
#define CAN_F11R1_FB27				CAN_F11R1_FB27_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 28 (`CANx_F11R1.FB28`) bit position @def CAN_F11R1_FB28_Pos */
#define CAN_F11R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 11 word 1 bit 28 (`CANx_F11R1.FB28`) bit mask @def CAN_F11R1_FB28_Msk */
#define CAN_F11R1_FB28_Msk			REG_BIT_MASK(CAN_F11R1_FB28_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 28 (`CANx_F11R1.FB28`) bit mask alias @def CAN_F11R1_FB28 */
#define CAN_F11R1_FB28				CAN_F11R1_FB28_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 29 (`CANx_F11R1.FB29`) bit position @def CAN_F11R1_FB29_Pos */
#define CAN_F11R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 11 word 1 bit 29 (`CANx_F11R1.FB29`) bit mask @def CAN_F11R1_FB29_Msk */
#define CAN_F11R1_FB29_Msk			REG_BIT_MASK(CAN_F11R1_FB29_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 29 (`CANx_F11R1.FB29`) bit mask alias @def CAN_F11R1_FB29 */
#define CAN_F11R1_FB29				CAN_F11R1_FB29_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 30 (`CANx_F11R1.FB30`) bit position @def CAN_F11R1_FB30_Pos */
#define CAN_F11R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 11 word 1 bit 30 (`CANx_F11R1.FB30`) bit mask @def CAN_F11R1_FB30_Msk */
#define CAN_F11R1_FB30_Msk			REG_BIT_MASK(CAN_F11R1_FB30_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 30 (`CANx_F11R1.FB30`) bit mask alias @def CAN_F11R1_FB30 */
#define CAN_F11R1_FB30				CAN_F11R1_FB30_Msk

/** @brief Acceptance-filter bank 11 word 1 bit 31 (`CANx_F11R1.FB31`) bit position @def CAN_F11R1_FB31_Pos */
#define CAN_F11R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 11 word 1 bit 31 (`CANx_F11R1.FB31`) bit mask @def CAN_F11R1_FB31_Msk */
#define CAN_F11R1_FB31_Msk			REG_BIT_MASK(CAN_F11R1_FB31_Pos)
/** @brief Acceptance-filter bank 11 word 1 bit 31 (`CANx_F11R1.FB31`) bit mask alias @def CAN_F11R1_FB31 */
#define CAN_F11R1_FB31				CAN_F11R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F12R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 12 word 1 bit 0 (`CANx_F12R1.FB0`) bit position @def CAN_F12R1_FB0_Pos */
#define CAN_F12R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 12 word 1 bit 0 (`CANx_F12R1.FB0`) bit mask @def CAN_F12R1_FB0_Msk */
#define CAN_F12R1_FB0_Msk			REG_BIT_MASK(CAN_F12R1_FB0_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 0 (`CANx_F12R1.FB0`) bit mask alias @def CAN_F12R1_FB0 */
#define CAN_F12R1_FB0				CAN_F12R1_FB0_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 1 (`CANx_F12R1.FB1`) bit position @def CAN_F12R1_FB1_Pos */
#define CAN_F12R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 12 word 1 bit 1 (`CANx_F12R1.FB1`) bit mask @def CAN_F12R1_FB1_Msk */
#define CAN_F12R1_FB1_Msk			REG_BIT_MASK(CAN_F12R1_FB1_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 1 (`CANx_F12R1.FB1`) bit mask alias @def CAN_F12R1_FB1 */
#define CAN_F12R1_FB1				CAN_F12R1_FB1_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 2 (`CANx_F12R1.FB2`) bit position @def CAN_F12R1_FB2_Pos */
#define CAN_F12R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 12 word 1 bit 2 (`CANx_F12R1.FB2`) bit mask @def CAN_F12R1_FB2_Msk */
#define CAN_F12R1_FB2_Msk			REG_BIT_MASK(CAN_F12R1_FB2_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 2 (`CANx_F12R1.FB2`) bit mask alias @def CAN_F12R1_FB2 */
#define CAN_F12R1_FB2				CAN_F12R1_FB2_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 3 (`CANx_F12R1.FB3`) bit position @def CAN_F12R1_FB3_Pos */
#define CAN_F12R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 12 word 1 bit 3 (`CANx_F12R1.FB3`) bit mask @def CAN_F12R1_FB3_Msk */
#define CAN_F12R1_FB3_Msk			REG_BIT_MASK(CAN_F12R1_FB3_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 3 (`CANx_F12R1.FB3`) bit mask alias @def CAN_F12R1_FB3 */
#define CAN_F12R1_FB3				CAN_F12R1_FB3_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 4 (`CANx_F12R1.FB4`) bit position @def CAN_F12R1_FB4_Pos */
#define CAN_F12R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 12 word 1 bit 4 (`CANx_F12R1.FB4`) bit mask @def CAN_F12R1_FB4_Msk */
#define CAN_F12R1_FB4_Msk			REG_BIT_MASK(CAN_F12R1_FB4_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 4 (`CANx_F12R1.FB4`) bit mask alias @def CAN_F12R1_FB4 */
#define CAN_F12R1_FB4				CAN_F12R1_FB4_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 5 (`CANx_F12R1.FB5`) bit position @def CAN_F12R1_FB5_Pos */
#define CAN_F12R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 12 word 1 bit 5 (`CANx_F12R1.FB5`) bit mask @def CAN_F12R1_FB5_Msk */
#define CAN_F12R1_FB5_Msk			REG_BIT_MASK(CAN_F12R1_FB5_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 5 (`CANx_F12R1.FB5`) bit mask alias @def CAN_F12R1_FB5 */
#define CAN_F12R1_FB5				CAN_F12R1_FB5_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 6 (`CANx_F12R1.FB6`) bit position @def CAN_F12R1_FB6_Pos */
#define CAN_F12R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 12 word 1 bit 6 (`CANx_F12R1.FB6`) bit mask @def CAN_F12R1_FB6_Msk */
#define CAN_F12R1_FB6_Msk			REG_BIT_MASK(CAN_F12R1_FB6_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 6 (`CANx_F12R1.FB6`) bit mask alias @def CAN_F12R1_FB6 */
#define CAN_F12R1_FB6				CAN_F12R1_FB6_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 7 (`CANx_F12R1.FB7`) bit position @def CAN_F12R1_FB7_Pos */
#define CAN_F12R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 12 word 1 bit 7 (`CANx_F12R1.FB7`) bit mask @def CAN_F12R1_FB7_Msk */
#define CAN_F12R1_FB7_Msk			REG_BIT_MASK(CAN_F12R1_FB7_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 7 (`CANx_F12R1.FB7`) bit mask alias @def CAN_F12R1_FB7 */
#define CAN_F12R1_FB7				CAN_F12R1_FB7_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 8 (`CANx_F12R1.FB8`) bit position @def CAN_F12R1_FB8_Pos */
#define CAN_F12R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 12 word 1 bit 8 (`CANx_F12R1.FB8`) bit mask @def CAN_F12R1_FB8_Msk */
#define CAN_F12R1_FB8_Msk			REG_BIT_MASK(CAN_F12R1_FB8_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 8 (`CANx_F12R1.FB8`) bit mask alias @def CAN_F12R1_FB8 */
#define CAN_F12R1_FB8				CAN_F12R1_FB8_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 9 (`CANx_F12R1.FB9`) bit position @def CAN_F12R1_FB9_Pos */
#define CAN_F12R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 12 word 1 bit 9 (`CANx_F12R1.FB9`) bit mask @def CAN_F12R1_FB9_Msk */
#define CAN_F12R1_FB9_Msk			REG_BIT_MASK(CAN_F12R1_FB9_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 9 (`CANx_F12R1.FB9`) bit mask alias @def CAN_F12R1_FB9 */
#define CAN_F12R1_FB9				CAN_F12R1_FB9_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 10 (`CANx_F12R1.FB10`) bit position @def CAN_F12R1_FB10_Pos */
#define CAN_F12R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 12 word 1 bit 10 (`CANx_F12R1.FB10`) bit mask @def CAN_F12R1_FB10_Msk */
#define CAN_F12R1_FB10_Msk			REG_BIT_MASK(CAN_F12R1_FB10_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 10 (`CANx_F12R1.FB10`) bit mask alias @def CAN_F12R1_FB10 */
#define CAN_F12R1_FB10				CAN_F12R1_FB10_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 11 (`CANx_F12R1.FB11`) bit position @def CAN_F12R1_FB11_Pos */
#define CAN_F12R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 12 word 1 bit 11 (`CANx_F12R1.FB11`) bit mask @def CAN_F12R1_FB11_Msk */
#define CAN_F12R1_FB11_Msk			REG_BIT_MASK(CAN_F12R1_FB11_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 11 (`CANx_F12R1.FB11`) bit mask alias @def CAN_F12R1_FB11 */
#define CAN_F12R1_FB11				CAN_F12R1_FB11_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 12 (`CANx_F12R1.FB12`) bit position @def CAN_F12R1_FB12_Pos */
#define CAN_F12R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 12 word 1 bit 12 (`CANx_F12R1.FB12`) bit mask @def CAN_F12R1_FB12_Msk */
#define CAN_F12R1_FB12_Msk			REG_BIT_MASK(CAN_F12R1_FB12_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 12 (`CANx_F12R1.FB12`) bit mask alias @def CAN_F12R1_FB12 */
#define CAN_F12R1_FB12				CAN_F12R1_FB12_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 13 (`CANx_F12R1.FB13`) bit position @def CAN_F12R1_FB13_Pos */
#define CAN_F12R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 12 word 1 bit 13 (`CANx_F12R1.FB13`) bit mask @def CAN_F12R1_FB13_Msk */
#define CAN_F12R1_FB13_Msk			REG_BIT_MASK(CAN_F12R1_FB13_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 13 (`CANx_F12R1.FB13`) bit mask alias @def CAN_F12R1_FB13 */
#define CAN_F12R1_FB13				CAN_F12R1_FB13_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 14 (`CANx_F12R1.FB14`) bit position @def CAN_F12R1_FB14_Pos */
#define CAN_F12R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 12 word 1 bit 14 (`CANx_F12R1.FB14`) bit mask @def CAN_F12R1_FB14_Msk */
#define CAN_F12R1_FB14_Msk			REG_BIT_MASK(CAN_F12R1_FB14_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 14 (`CANx_F12R1.FB14`) bit mask alias @def CAN_F12R1_FB14 */
#define CAN_F12R1_FB14				CAN_F12R1_FB14_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 15 (`CANx_F12R1.FB15`) bit position @def CAN_F12R1_FB15_Pos */
#define CAN_F12R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 12 word 1 bit 15 (`CANx_F12R1.FB15`) bit mask @def CAN_F12R1_FB15_Msk */
#define CAN_F12R1_FB15_Msk			REG_BIT_MASK(CAN_F12R1_FB15_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 15 (`CANx_F12R1.FB15`) bit mask alias @def CAN_F12R1_FB15 */
#define CAN_F12R1_FB15				CAN_F12R1_FB15_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 16 (`CANx_F12R1.FB16`) bit position @def CAN_F12R1_FB16_Pos */
#define CAN_F12R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 12 word 1 bit 16 (`CANx_F12R1.FB16`) bit mask @def CAN_F12R1_FB16_Msk */
#define CAN_F12R1_FB16_Msk			REG_BIT_MASK(CAN_F12R1_FB16_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 16 (`CANx_F12R1.FB16`) bit mask alias @def CAN_F12R1_FB16 */
#define CAN_F12R1_FB16				CAN_F12R1_FB16_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 17 (`CANx_F12R1.FB17`) bit position @def CAN_F12R1_FB17_Pos */
#define CAN_F12R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 12 word 1 bit 17 (`CANx_F12R1.FB17`) bit mask @def CAN_F12R1_FB17_Msk */
#define CAN_F12R1_FB17_Msk			REG_BIT_MASK(CAN_F12R1_FB17_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 17 (`CANx_F12R1.FB17`) bit mask alias @def CAN_F12R1_FB17 */
#define CAN_F12R1_FB17				CAN_F12R1_FB17_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 18 (`CANx_F12R1.FB18`) bit position @def CAN_F12R1_FB18_Pos */
#define CAN_F12R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 12 word 1 bit 18 (`CANx_F12R1.FB18`) bit mask @def CAN_F12R1_FB18_Msk */
#define CAN_F12R1_FB18_Msk			REG_BIT_MASK(CAN_F12R1_FB18_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 18 (`CANx_F12R1.FB18`) bit mask alias @def CAN_F12R1_FB18 */
#define CAN_F12R1_FB18				CAN_F12R1_FB18_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 19 (`CANx_F12R1.FB19`) bit position @def CAN_F12R1_FB19_Pos */
#define CAN_F12R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 12 word 1 bit 19 (`CANx_F12R1.FB19`) bit mask @def CAN_F12R1_FB19_Msk */
#define CAN_F12R1_FB19_Msk			REG_BIT_MASK(CAN_F12R1_FB19_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 19 (`CANx_F12R1.FB19`) bit mask alias @def CAN_F12R1_FB19 */
#define CAN_F12R1_FB19				CAN_F12R1_FB19_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 20 (`CANx_F12R1.FB20`) bit position @def CAN_F12R1_FB20_Pos */
#define CAN_F12R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 12 word 1 bit 20 (`CANx_F12R1.FB20`) bit mask @def CAN_F12R1_FB20_Msk */
#define CAN_F12R1_FB20_Msk			REG_BIT_MASK(CAN_F12R1_FB20_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 20 (`CANx_F12R1.FB20`) bit mask alias @def CAN_F12R1_FB20 */
#define CAN_F12R1_FB20				CAN_F12R1_FB20_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 21 (`CANx_F12R1.FB21`) bit position @def CAN_F12R1_FB21_Pos */
#define CAN_F12R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 12 word 1 bit 21 (`CANx_F12R1.FB21`) bit mask @def CAN_F12R1_FB21_Msk */
#define CAN_F12R1_FB21_Msk			REG_BIT_MASK(CAN_F12R1_FB21_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 21 (`CANx_F12R1.FB21`) bit mask alias @def CAN_F12R1_FB21 */
#define CAN_F12R1_FB21				CAN_F12R1_FB21_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 22 (`CANx_F12R1.FB22`) bit position @def CAN_F12R1_FB22_Pos */
#define CAN_F12R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 12 word 1 bit 22 (`CANx_F12R1.FB22`) bit mask @def CAN_F12R1_FB22_Msk */
#define CAN_F12R1_FB22_Msk			REG_BIT_MASK(CAN_F12R1_FB22_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 22 (`CANx_F12R1.FB22`) bit mask alias @def CAN_F12R1_FB22 */
#define CAN_F12R1_FB22				CAN_F12R1_FB22_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 23 (`CANx_F12R1.FB23`) bit position @def CAN_F12R1_FB23_Pos */
#define CAN_F12R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 12 word 1 bit 23 (`CANx_F12R1.FB23`) bit mask @def CAN_F12R1_FB23_Msk */
#define CAN_F12R1_FB23_Msk			REG_BIT_MASK(CAN_F12R1_FB23_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 23 (`CANx_F12R1.FB23`) bit mask alias @def CAN_F12R1_FB23 */
#define CAN_F12R1_FB23				CAN_F12R1_FB23_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 24 (`CANx_F12R1.FB24`) bit position @def CAN_F12R1_FB24_Pos */
#define CAN_F12R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 12 word 1 bit 24 (`CANx_F12R1.FB24`) bit mask @def CAN_F12R1_FB24_Msk */
#define CAN_F12R1_FB24_Msk			REG_BIT_MASK(CAN_F12R1_FB24_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 24 (`CANx_F12R1.FB24`) bit mask alias @def CAN_F12R1_FB24 */
#define CAN_F12R1_FB24				CAN_F12R1_FB24_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 25 (`CANx_F12R1.FB25`) bit position @def CAN_F12R1_FB25_Pos */
#define CAN_F12R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 12 word 1 bit 25 (`CANx_F12R1.FB25`) bit mask @def CAN_F12R1_FB25_Msk */
#define CAN_F12R1_FB25_Msk			REG_BIT_MASK(CAN_F12R1_FB25_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 25 (`CANx_F12R1.FB25`) bit mask alias @def CAN_F12R1_FB25 */
#define CAN_F12R1_FB25				CAN_F12R1_FB25_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 26 (`CANx_F12R1.FB26`) bit position @def CAN_F12R1_FB26_Pos */
#define CAN_F12R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 12 word 1 bit 26 (`CANx_F12R1.FB26`) bit mask @def CAN_F12R1_FB26_Msk */
#define CAN_F12R1_FB26_Msk			REG_BIT_MASK(CAN_F12R1_FB26_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 26 (`CANx_F12R1.FB26`) bit mask alias @def CAN_F12R1_FB26 */
#define CAN_F12R1_FB26				CAN_F12R1_FB26_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 27 (`CANx_F12R1.FB27`) bit position @def CAN_F12R1_FB27_Pos */
#define CAN_F12R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 12 word 1 bit 27 (`CANx_F12R1.FB27`) bit mask @def CAN_F12R1_FB27_Msk */
#define CAN_F12R1_FB27_Msk			REG_BIT_MASK(CAN_F12R1_FB27_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 27 (`CANx_F12R1.FB27`) bit mask alias @def CAN_F12R1_FB27 */
#define CAN_F12R1_FB27				CAN_F12R1_FB27_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 28 (`CANx_F12R1.FB28`) bit position @def CAN_F12R1_FB28_Pos */
#define CAN_F12R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 12 word 1 bit 28 (`CANx_F12R1.FB28`) bit mask @def CAN_F12R1_FB28_Msk */
#define CAN_F12R1_FB28_Msk			REG_BIT_MASK(CAN_F12R1_FB28_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 28 (`CANx_F12R1.FB28`) bit mask alias @def CAN_F12R1_FB28 */
#define CAN_F12R1_FB28				CAN_F12R1_FB28_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 29 (`CANx_F12R1.FB29`) bit position @def CAN_F12R1_FB29_Pos */
#define CAN_F12R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 12 word 1 bit 29 (`CANx_F12R1.FB29`) bit mask @def CAN_F12R1_FB29_Msk */
#define CAN_F12R1_FB29_Msk			REG_BIT_MASK(CAN_F12R1_FB29_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 29 (`CANx_F12R1.FB29`) bit mask alias @def CAN_F12R1_FB29 */
#define CAN_F12R1_FB29				CAN_F12R1_FB29_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 30 (`CANx_F12R1.FB30`) bit position @def CAN_F12R1_FB30_Pos */
#define CAN_F12R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 12 word 1 bit 30 (`CANx_F12R1.FB30`) bit mask @def CAN_F12R1_FB30_Msk */
#define CAN_F12R1_FB30_Msk			REG_BIT_MASK(CAN_F12R1_FB30_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 30 (`CANx_F12R1.FB30`) bit mask alias @def CAN_F12R1_FB30 */
#define CAN_F12R1_FB30				CAN_F12R1_FB30_Msk

/** @brief Acceptance-filter bank 12 word 1 bit 31 (`CANx_F12R1.FB31`) bit position @def CAN_F12R1_FB31_Pos */
#define CAN_F12R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 12 word 1 bit 31 (`CANx_F12R1.FB31`) bit mask @def CAN_F12R1_FB31_Msk */
#define CAN_F12R1_FB31_Msk			REG_BIT_MASK(CAN_F12R1_FB31_Pos)
/** @brief Acceptance-filter bank 12 word 1 bit 31 (`CANx_F12R1.FB31`) bit mask alias @def CAN_F12R1_FB31 */
#define CAN_F12R1_FB31				CAN_F12R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F13R1
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 13 word 1 bit 0 (`CANx_F13R1.FB0`) bit position @def CAN_F13R1_FB0_Pos */
#define CAN_F13R1_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 13 word 1 bit 0 (`CANx_F13R1.FB0`) bit mask @def CAN_F13R1_FB0_Msk */
#define CAN_F13R1_FB0_Msk			REG_BIT_MASK(CAN_F13R1_FB0_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 0 (`CANx_F13R1.FB0`) bit mask alias @def CAN_F13R1_FB0 */
#define CAN_F13R1_FB0				CAN_F13R1_FB0_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 1 (`CANx_F13R1.FB1`) bit position @def CAN_F13R1_FB1_Pos */
#define CAN_F13R1_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 13 word 1 bit 1 (`CANx_F13R1.FB1`) bit mask @def CAN_F13R1_FB1_Msk */
#define CAN_F13R1_FB1_Msk			REG_BIT_MASK(CAN_F13R1_FB1_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 1 (`CANx_F13R1.FB1`) bit mask alias @def CAN_F13R1_FB1 */
#define CAN_F13R1_FB1				CAN_F13R1_FB1_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 2 (`CANx_F13R1.FB2`) bit position @def CAN_F13R1_FB2_Pos */
#define CAN_F13R1_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 13 word 1 bit 2 (`CANx_F13R1.FB2`) bit mask @def CAN_F13R1_FB2_Msk */
#define CAN_F13R1_FB2_Msk			REG_BIT_MASK(CAN_F13R1_FB2_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 2 (`CANx_F13R1.FB2`) bit mask alias @def CAN_F13R1_FB2 */
#define CAN_F13R1_FB2				CAN_F13R1_FB2_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 3 (`CANx_F13R1.FB3`) bit position @def CAN_F13R1_FB3_Pos */
#define CAN_F13R1_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 13 word 1 bit 3 (`CANx_F13R1.FB3`) bit mask @def CAN_F13R1_FB3_Msk */
#define CAN_F13R1_FB3_Msk			REG_BIT_MASK(CAN_F13R1_FB3_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 3 (`CANx_F13R1.FB3`) bit mask alias @def CAN_F13R1_FB3 */
#define CAN_F13R1_FB3				CAN_F13R1_FB3_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 4 (`CANx_F13R1.FB4`) bit position @def CAN_F13R1_FB4_Pos */
#define CAN_F13R1_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 13 word 1 bit 4 (`CANx_F13R1.FB4`) bit mask @def CAN_F13R1_FB4_Msk */
#define CAN_F13R1_FB4_Msk			REG_BIT_MASK(CAN_F13R1_FB4_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 4 (`CANx_F13R1.FB4`) bit mask alias @def CAN_F13R1_FB4 */
#define CAN_F13R1_FB4				CAN_F13R1_FB4_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 5 (`CANx_F13R1.FB5`) bit position @def CAN_F13R1_FB5_Pos */
#define CAN_F13R1_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 13 word 1 bit 5 (`CANx_F13R1.FB5`) bit mask @def CAN_F13R1_FB5_Msk */
#define CAN_F13R1_FB5_Msk			REG_BIT_MASK(CAN_F13R1_FB5_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 5 (`CANx_F13R1.FB5`) bit mask alias @def CAN_F13R1_FB5 */
#define CAN_F13R1_FB5				CAN_F13R1_FB5_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 6 (`CANx_F13R1.FB6`) bit position @def CAN_F13R1_FB6_Pos */
#define CAN_F13R1_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 13 word 1 bit 6 (`CANx_F13R1.FB6`) bit mask @def CAN_F13R1_FB6_Msk */
#define CAN_F13R1_FB6_Msk			REG_BIT_MASK(CAN_F13R1_FB6_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 6 (`CANx_F13R1.FB6`) bit mask alias @def CAN_F13R1_FB6 */
#define CAN_F13R1_FB6				CAN_F13R1_FB6_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 7 (`CANx_F13R1.FB7`) bit position @def CAN_F13R1_FB7_Pos */
#define CAN_F13R1_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 13 word 1 bit 7 (`CANx_F13R1.FB7`) bit mask @def CAN_F13R1_FB7_Msk */
#define CAN_F13R1_FB7_Msk			REG_BIT_MASK(CAN_F13R1_FB7_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 7 (`CANx_F13R1.FB7`) bit mask alias @def CAN_F13R1_FB7 */
#define CAN_F13R1_FB7				CAN_F13R1_FB7_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 8 (`CANx_F13R1.FB8`) bit position @def CAN_F13R1_FB8_Pos */
#define CAN_F13R1_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 13 word 1 bit 8 (`CANx_F13R1.FB8`) bit mask @def CAN_F13R1_FB8_Msk */
#define CAN_F13R1_FB8_Msk			REG_BIT_MASK(CAN_F13R1_FB8_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 8 (`CANx_F13R1.FB8`) bit mask alias @def CAN_F13R1_FB8 */
#define CAN_F13R1_FB8				CAN_F13R1_FB8_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 9 (`CANx_F13R1.FB9`) bit position @def CAN_F13R1_FB9_Pos */
#define CAN_F13R1_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 13 word 1 bit 9 (`CANx_F13R1.FB9`) bit mask @def CAN_F13R1_FB9_Msk */
#define CAN_F13R1_FB9_Msk			REG_BIT_MASK(CAN_F13R1_FB9_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 9 (`CANx_F13R1.FB9`) bit mask alias @def CAN_F13R1_FB9 */
#define CAN_F13R1_FB9				CAN_F13R1_FB9_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 10 (`CANx_F13R1.FB10`) bit position @def CAN_F13R1_FB10_Pos */
#define CAN_F13R1_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 13 word 1 bit 10 (`CANx_F13R1.FB10`) bit mask @def CAN_F13R1_FB10_Msk */
#define CAN_F13R1_FB10_Msk			REG_BIT_MASK(CAN_F13R1_FB10_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 10 (`CANx_F13R1.FB10`) bit mask alias @def CAN_F13R1_FB10 */
#define CAN_F13R1_FB10				CAN_F13R1_FB10_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 11 (`CANx_F13R1.FB11`) bit position @def CAN_F13R1_FB11_Pos */
#define CAN_F13R1_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 13 word 1 bit 11 (`CANx_F13R1.FB11`) bit mask @def CAN_F13R1_FB11_Msk */
#define CAN_F13R1_FB11_Msk			REG_BIT_MASK(CAN_F13R1_FB11_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 11 (`CANx_F13R1.FB11`) bit mask alias @def CAN_F13R1_FB11 */
#define CAN_F13R1_FB11				CAN_F13R1_FB11_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 12 (`CANx_F13R1.FB12`) bit position @def CAN_F13R1_FB12_Pos */
#define CAN_F13R1_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 13 word 1 bit 12 (`CANx_F13R1.FB12`) bit mask @def CAN_F13R1_FB12_Msk */
#define CAN_F13R1_FB12_Msk			REG_BIT_MASK(CAN_F13R1_FB12_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 12 (`CANx_F13R1.FB12`) bit mask alias @def CAN_F13R1_FB12 */
#define CAN_F13R1_FB12				CAN_F13R1_FB12_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 13 (`CANx_F13R1.FB13`) bit position @def CAN_F13R1_FB13_Pos */
#define CAN_F13R1_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 13 word 1 bit 13 (`CANx_F13R1.FB13`) bit mask @def CAN_F13R1_FB13_Msk */
#define CAN_F13R1_FB13_Msk			REG_BIT_MASK(CAN_F13R1_FB13_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 13 (`CANx_F13R1.FB13`) bit mask alias @def CAN_F13R1_FB13 */
#define CAN_F13R1_FB13				CAN_F13R1_FB13_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 14 (`CANx_F13R1.FB14`) bit position @def CAN_F13R1_FB14_Pos */
#define CAN_F13R1_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 13 word 1 bit 14 (`CANx_F13R1.FB14`) bit mask @def CAN_F13R1_FB14_Msk */
#define CAN_F13R1_FB14_Msk			REG_BIT_MASK(CAN_F13R1_FB14_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 14 (`CANx_F13R1.FB14`) bit mask alias @def CAN_F13R1_FB14 */
#define CAN_F13R1_FB14				CAN_F13R1_FB14_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 15 (`CANx_F13R1.FB15`) bit position @def CAN_F13R1_FB15_Pos */
#define CAN_F13R1_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 13 word 1 bit 15 (`CANx_F13R1.FB15`) bit mask @def CAN_F13R1_FB15_Msk */
#define CAN_F13R1_FB15_Msk			REG_BIT_MASK(CAN_F13R1_FB15_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 15 (`CANx_F13R1.FB15`) bit mask alias @def CAN_F13R1_FB15 */
#define CAN_F13R1_FB15				CAN_F13R1_FB15_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 16 (`CANx_F13R1.FB16`) bit position @def CAN_F13R1_FB16_Pos */
#define CAN_F13R1_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 13 word 1 bit 16 (`CANx_F13R1.FB16`) bit mask @def CAN_F13R1_FB16_Msk */
#define CAN_F13R1_FB16_Msk			REG_BIT_MASK(CAN_F13R1_FB16_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 16 (`CANx_F13R1.FB16`) bit mask alias @def CAN_F13R1_FB16 */
#define CAN_F13R1_FB16				CAN_F13R1_FB16_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 17 (`CANx_F13R1.FB17`) bit position @def CAN_F13R1_FB17_Pos */
#define CAN_F13R1_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 13 word 1 bit 17 (`CANx_F13R1.FB17`) bit mask @def CAN_F13R1_FB17_Msk */
#define CAN_F13R1_FB17_Msk			REG_BIT_MASK(CAN_F13R1_FB17_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 17 (`CANx_F13R1.FB17`) bit mask alias @def CAN_F13R1_FB17 */
#define CAN_F13R1_FB17				CAN_F13R1_FB17_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 18 (`CANx_F13R1.FB18`) bit position @def CAN_F13R1_FB18_Pos */
#define CAN_F13R1_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 13 word 1 bit 18 (`CANx_F13R1.FB18`) bit mask @def CAN_F13R1_FB18_Msk */
#define CAN_F13R1_FB18_Msk			REG_BIT_MASK(CAN_F13R1_FB18_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 18 (`CANx_F13R1.FB18`) bit mask alias @def CAN_F13R1_FB18 */
#define CAN_F13R1_FB18				CAN_F13R1_FB18_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 19 (`CANx_F13R1.FB19`) bit position @def CAN_F13R1_FB19_Pos */
#define CAN_F13R1_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 13 word 1 bit 19 (`CANx_F13R1.FB19`) bit mask @def CAN_F13R1_FB19_Msk */
#define CAN_F13R1_FB19_Msk			REG_BIT_MASK(CAN_F13R1_FB19_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 19 (`CANx_F13R1.FB19`) bit mask alias @def CAN_F13R1_FB19 */
#define CAN_F13R1_FB19				CAN_F13R1_FB19_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 20 (`CANx_F13R1.FB20`) bit position @def CAN_F13R1_FB20_Pos */
#define CAN_F13R1_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 13 word 1 bit 20 (`CANx_F13R1.FB20`) bit mask @def CAN_F13R1_FB20_Msk */
#define CAN_F13R1_FB20_Msk			REG_BIT_MASK(CAN_F13R1_FB20_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 20 (`CANx_F13R1.FB20`) bit mask alias @def CAN_F13R1_FB20 */
#define CAN_F13R1_FB20				CAN_F13R1_FB20_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 21 (`CANx_F13R1.FB21`) bit position @def CAN_F13R1_FB21_Pos */
#define CAN_F13R1_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 13 word 1 bit 21 (`CANx_F13R1.FB21`) bit mask @def CAN_F13R1_FB21_Msk */
#define CAN_F13R1_FB21_Msk			REG_BIT_MASK(CAN_F13R1_FB21_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 21 (`CANx_F13R1.FB21`) bit mask alias @def CAN_F13R1_FB21 */
#define CAN_F13R1_FB21				CAN_F13R1_FB21_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 22 (`CANx_F13R1.FB22`) bit position @def CAN_F13R1_FB22_Pos */
#define CAN_F13R1_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 13 word 1 bit 22 (`CANx_F13R1.FB22`) bit mask @def CAN_F13R1_FB22_Msk */
#define CAN_F13R1_FB22_Msk			REG_BIT_MASK(CAN_F13R1_FB22_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 22 (`CANx_F13R1.FB22`) bit mask alias @def CAN_F13R1_FB22 */
#define CAN_F13R1_FB22				CAN_F13R1_FB22_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 23 (`CANx_F13R1.FB23`) bit position @def CAN_F13R1_FB23_Pos */
#define CAN_F13R1_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 13 word 1 bit 23 (`CANx_F13R1.FB23`) bit mask @def CAN_F13R1_FB23_Msk */
#define CAN_F13R1_FB23_Msk			REG_BIT_MASK(CAN_F13R1_FB23_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 23 (`CANx_F13R1.FB23`) bit mask alias @def CAN_F13R1_FB23 */
#define CAN_F13R1_FB23				CAN_F13R1_FB23_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 24 (`CANx_F13R1.FB24`) bit position @def CAN_F13R1_FB24_Pos */
#define CAN_F13R1_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 13 word 1 bit 24 (`CANx_F13R1.FB24`) bit mask @def CAN_F13R1_FB24_Msk */
#define CAN_F13R1_FB24_Msk			REG_BIT_MASK(CAN_F13R1_FB24_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 24 (`CANx_F13R1.FB24`) bit mask alias @def CAN_F13R1_FB24 */
#define CAN_F13R1_FB24				CAN_F13R1_FB24_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 25 (`CANx_F13R1.FB25`) bit position @def CAN_F13R1_FB25_Pos */
#define CAN_F13R1_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 13 word 1 bit 25 (`CANx_F13R1.FB25`) bit mask @def CAN_F13R1_FB25_Msk */
#define CAN_F13R1_FB25_Msk			REG_BIT_MASK(CAN_F13R1_FB25_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 25 (`CANx_F13R1.FB25`) bit mask alias @def CAN_F13R1_FB25 */
#define CAN_F13R1_FB25				CAN_F13R1_FB25_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 26 (`CANx_F13R1.FB26`) bit position @def CAN_F13R1_FB26_Pos */
#define CAN_F13R1_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 13 word 1 bit 26 (`CANx_F13R1.FB26`) bit mask @def CAN_F13R1_FB26_Msk */
#define CAN_F13R1_FB26_Msk			REG_BIT_MASK(CAN_F13R1_FB26_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 26 (`CANx_F13R1.FB26`) bit mask alias @def CAN_F13R1_FB26 */
#define CAN_F13R1_FB26				CAN_F13R1_FB26_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 27 (`CANx_F13R1.FB27`) bit position @def CAN_F13R1_FB27_Pos */
#define CAN_F13R1_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 13 word 1 bit 27 (`CANx_F13R1.FB27`) bit mask @def CAN_F13R1_FB27_Msk */
#define CAN_F13R1_FB27_Msk			REG_BIT_MASK(CAN_F13R1_FB27_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 27 (`CANx_F13R1.FB27`) bit mask alias @def CAN_F13R1_FB27 */
#define CAN_F13R1_FB27				CAN_F13R1_FB27_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 28 (`CANx_F13R1.FB28`) bit position @def CAN_F13R1_FB28_Pos */
#define CAN_F13R1_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 13 word 1 bit 28 (`CANx_F13R1.FB28`) bit mask @def CAN_F13R1_FB28_Msk */
#define CAN_F13R1_FB28_Msk			REG_BIT_MASK(CAN_F13R1_FB28_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 28 (`CANx_F13R1.FB28`) bit mask alias @def CAN_F13R1_FB28 */
#define CAN_F13R1_FB28				CAN_F13R1_FB28_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 29 (`CANx_F13R1.FB29`) bit position @def CAN_F13R1_FB29_Pos */
#define CAN_F13R1_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 13 word 1 bit 29 (`CANx_F13R1.FB29`) bit mask @def CAN_F13R1_FB29_Msk */
#define CAN_F13R1_FB29_Msk			REG_BIT_MASK(CAN_F13R1_FB29_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 29 (`CANx_F13R1.FB29`) bit mask alias @def CAN_F13R1_FB29 */
#define CAN_F13R1_FB29				CAN_F13R1_FB29_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 30 (`CANx_F13R1.FB30`) bit position @def CAN_F13R1_FB30_Pos */
#define CAN_F13R1_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 13 word 1 bit 30 (`CANx_F13R1.FB30`) bit mask @def CAN_F13R1_FB30_Msk */
#define CAN_F13R1_FB30_Msk			REG_BIT_MASK(CAN_F13R1_FB30_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 30 (`CANx_F13R1.FB30`) bit mask alias @def CAN_F13R1_FB30 */
#define CAN_F13R1_FB30				CAN_F13R1_FB30_Msk

/** @brief Acceptance-filter bank 13 word 1 bit 31 (`CANx_F13R1.FB31`) bit position @def CAN_F13R1_FB31_Pos */
#define CAN_F13R1_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 13 word 1 bit 31 (`CANx_F13R1.FB31`) bit mask @def CAN_F13R1_FB31_Msk */
#define CAN_F13R1_FB31_Msk			REG_BIT_MASK(CAN_F13R1_FB31_Pos)
/** @brief Acceptance-filter bank 13 word 1 bit 31 (`CANx_F13R1.FB31`) bit mask alias @def CAN_F13R1_FB31 */
#define CAN_F13R1_FB31				CAN_F13R1_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F0R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 0 word 2 bit 0 (`CANx_F0R2.FB0`) bit position @def CAN_F0R2_FB0_Pos */
#define CAN_F0R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 0 word 2 bit 0 (`CANx_F0R2.FB0`) bit mask @def CAN_F0R2_FB0_Msk */
#define CAN_F0R2_FB0_Msk			REG_BIT_MASK(CAN_F0R2_FB0_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 0 (`CANx_F0R2.FB0`) bit mask alias @def CAN_F0R2_FB0 */
#define CAN_F0R2_FB0				CAN_F0R2_FB0_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 1 (`CANx_F0R2.FB1`) bit position @def CAN_F0R2_FB1_Pos */
#define CAN_F0R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 0 word 2 bit 1 (`CANx_F0R2.FB1`) bit mask @def CAN_F0R2_FB1_Msk */
#define CAN_F0R2_FB1_Msk			REG_BIT_MASK(CAN_F0R2_FB1_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 1 (`CANx_F0R2.FB1`) bit mask alias @def CAN_F0R2_FB1 */
#define CAN_F0R2_FB1				CAN_F0R2_FB1_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 2 (`CANx_F0R2.FB2`) bit position @def CAN_F0R2_FB2_Pos */
#define CAN_F0R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 0 word 2 bit 2 (`CANx_F0R2.FB2`) bit mask @def CAN_F0R2_FB2_Msk */
#define CAN_F0R2_FB2_Msk			REG_BIT_MASK(CAN_F0R2_FB2_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 2 (`CANx_F0R2.FB2`) bit mask alias @def CAN_F0R2_FB2 */
#define CAN_F0R2_FB2				CAN_F0R2_FB2_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 3 (`CANx_F0R2.FB3`) bit position @def CAN_F0R2_FB3_Pos */
#define CAN_F0R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 0 word 2 bit 3 (`CANx_F0R2.FB3`) bit mask @def CAN_F0R2_FB3_Msk */
#define CAN_F0R2_FB3_Msk			REG_BIT_MASK(CAN_F0R2_FB3_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 3 (`CANx_F0R2.FB3`) bit mask alias @def CAN_F0R2_FB3 */
#define CAN_F0R2_FB3				CAN_F0R2_FB3_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 4 (`CANx_F0R2.FB4`) bit position @def CAN_F0R2_FB4_Pos */
#define CAN_F0R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 0 word 2 bit 4 (`CANx_F0R2.FB4`) bit mask @def CAN_F0R2_FB4_Msk */
#define CAN_F0R2_FB4_Msk			REG_BIT_MASK(CAN_F0R2_FB4_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 4 (`CANx_F0R2.FB4`) bit mask alias @def CAN_F0R2_FB4 */
#define CAN_F0R2_FB4				CAN_F0R2_FB4_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 5 (`CANx_F0R2.FB5`) bit position @def CAN_F0R2_FB5_Pos */
#define CAN_F0R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 0 word 2 bit 5 (`CANx_F0R2.FB5`) bit mask @def CAN_F0R2_FB5_Msk */
#define CAN_F0R2_FB5_Msk			REG_BIT_MASK(CAN_F0R2_FB5_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 5 (`CANx_F0R2.FB5`) bit mask alias @def CAN_F0R2_FB5 */
#define CAN_F0R2_FB5				CAN_F0R2_FB5_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 6 (`CANx_F0R2.FB6`) bit position @def CAN_F0R2_FB6_Pos */
#define CAN_F0R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 0 word 2 bit 6 (`CANx_F0R2.FB6`) bit mask @def CAN_F0R2_FB6_Msk */
#define CAN_F0R2_FB6_Msk			REG_BIT_MASK(CAN_F0R2_FB6_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 6 (`CANx_F0R2.FB6`) bit mask alias @def CAN_F0R2_FB6 */
#define CAN_F0R2_FB6				CAN_F0R2_FB6_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 7 (`CANx_F0R2.FB7`) bit position @def CAN_F0R2_FB7_Pos */
#define CAN_F0R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 0 word 2 bit 7 (`CANx_F0R2.FB7`) bit mask @def CAN_F0R2_FB7_Msk */
#define CAN_F0R2_FB7_Msk			REG_BIT_MASK(CAN_F0R2_FB7_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 7 (`CANx_F0R2.FB7`) bit mask alias @def CAN_F0R2_FB7 */
#define CAN_F0R2_FB7				CAN_F0R2_FB7_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 8 (`CANx_F0R2.FB8`) bit position @def CAN_F0R2_FB8_Pos */
#define CAN_F0R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 0 word 2 bit 8 (`CANx_F0R2.FB8`) bit mask @def CAN_F0R2_FB8_Msk */
#define CAN_F0R2_FB8_Msk			REG_BIT_MASK(CAN_F0R2_FB8_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 8 (`CANx_F0R2.FB8`) bit mask alias @def CAN_F0R2_FB8 */
#define CAN_F0R2_FB8				CAN_F0R2_FB8_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 9 (`CANx_F0R2.FB9`) bit position @def CAN_F0R2_FB9_Pos */
#define CAN_F0R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 0 word 2 bit 9 (`CANx_F0R2.FB9`) bit mask @def CAN_F0R2_FB9_Msk */
#define CAN_F0R2_FB9_Msk			REG_BIT_MASK(CAN_F0R2_FB9_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 9 (`CANx_F0R2.FB9`) bit mask alias @def CAN_F0R2_FB9 */
#define CAN_F0R2_FB9				CAN_F0R2_FB9_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 10 (`CANx_F0R2.FB10`) bit position @def CAN_F0R2_FB10_Pos */
#define CAN_F0R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 0 word 2 bit 10 (`CANx_F0R2.FB10`) bit mask @def CAN_F0R2_FB10_Msk */
#define CAN_F0R2_FB10_Msk			REG_BIT_MASK(CAN_F0R2_FB10_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 10 (`CANx_F0R2.FB10`) bit mask alias @def CAN_F0R2_FB10 */
#define CAN_F0R2_FB10				CAN_F0R2_FB10_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 11 (`CANx_F0R2.FB11`) bit position @def CAN_F0R2_FB11_Pos */
#define CAN_F0R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 0 word 2 bit 11 (`CANx_F0R2.FB11`) bit mask @def CAN_F0R2_FB11_Msk */
#define CAN_F0R2_FB11_Msk			REG_BIT_MASK(CAN_F0R2_FB11_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 11 (`CANx_F0R2.FB11`) bit mask alias @def CAN_F0R2_FB11 */
#define CAN_F0R2_FB11				CAN_F0R2_FB11_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 12 (`CANx_F0R2.FB12`) bit position @def CAN_F0R2_FB12_Pos */
#define CAN_F0R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 0 word 2 bit 12 (`CANx_F0R2.FB12`) bit mask @def CAN_F0R2_FB12_Msk */
#define CAN_F0R2_FB12_Msk			REG_BIT_MASK(CAN_F0R2_FB12_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 12 (`CANx_F0R2.FB12`) bit mask alias @def CAN_F0R2_FB12 */
#define CAN_F0R2_FB12				CAN_F0R2_FB12_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 13 (`CANx_F0R2.FB13`) bit position @def CAN_F0R2_FB13_Pos */
#define CAN_F0R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 0 word 2 bit 13 (`CANx_F0R2.FB13`) bit mask @def CAN_F0R2_FB13_Msk */
#define CAN_F0R2_FB13_Msk			REG_BIT_MASK(CAN_F0R2_FB13_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 13 (`CANx_F0R2.FB13`) bit mask alias @def CAN_F0R2_FB13 */
#define CAN_F0R2_FB13				CAN_F0R2_FB13_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 14 (`CANx_F0R2.FB14`) bit position @def CAN_F0R2_FB14_Pos */
#define CAN_F0R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 0 word 2 bit 14 (`CANx_F0R2.FB14`) bit mask @def CAN_F0R2_FB14_Msk */
#define CAN_F0R2_FB14_Msk			REG_BIT_MASK(CAN_F0R2_FB14_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 14 (`CANx_F0R2.FB14`) bit mask alias @def CAN_F0R2_FB14 */
#define CAN_F0R2_FB14				CAN_F0R2_FB14_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 15 (`CANx_F0R2.FB15`) bit position @def CAN_F0R2_FB15_Pos */
#define CAN_F0R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 0 word 2 bit 15 (`CANx_F0R2.FB15`) bit mask @def CAN_F0R2_FB15_Msk */
#define CAN_F0R2_FB15_Msk			REG_BIT_MASK(CAN_F0R2_FB15_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 15 (`CANx_F0R2.FB15`) bit mask alias @def CAN_F0R2_FB15 */
#define CAN_F0R2_FB15				CAN_F0R2_FB15_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 16 (`CANx_F0R2.FB16`) bit position @def CAN_F0R2_FB16_Pos */
#define CAN_F0R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 0 word 2 bit 16 (`CANx_F0R2.FB16`) bit mask @def CAN_F0R2_FB16_Msk */
#define CAN_F0R2_FB16_Msk			REG_BIT_MASK(CAN_F0R2_FB16_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 16 (`CANx_F0R2.FB16`) bit mask alias @def CAN_F0R2_FB16 */
#define CAN_F0R2_FB16				CAN_F0R2_FB16_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 17 (`CANx_F0R2.FB17`) bit position @def CAN_F0R2_FB17_Pos */
#define CAN_F0R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 0 word 2 bit 17 (`CANx_F0R2.FB17`) bit mask @def CAN_F0R2_FB17_Msk */
#define CAN_F0R2_FB17_Msk			REG_BIT_MASK(CAN_F0R2_FB17_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 17 (`CANx_F0R2.FB17`) bit mask alias @def CAN_F0R2_FB17 */
#define CAN_F0R2_FB17				CAN_F0R2_FB17_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 18 (`CANx_F0R2.FB18`) bit position @def CAN_F0R2_FB18_Pos */
#define CAN_F0R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 0 word 2 bit 18 (`CANx_F0R2.FB18`) bit mask @def CAN_F0R2_FB18_Msk */
#define CAN_F0R2_FB18_Msk			REG_BIT_MASK(CAN_F0R2_FB18_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 18 (`CANx_F0R2.FB18`) bit mask alias @def CAN_F0R2_FB18 */
#define CAN_F0R2_FB18				CAN_F0R2_FB18_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 19 (`CANx_F0R2.FB19`) bit position @def CAN_F0R2_FB19_Pos */
#define CAN_F0R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 0 word 2 bit 19 (`CANx_F0R2.FB19`) bit mask @def CAN_F0R2_FB19_Msk */
#define CAN_F0R2_FB19_Msk			REG_BIT_MASK(CAN_F0R2_FB19_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 19 (`CANx_F0R2.FB19`) bit mask alias @def CAN_F0R2_FB19 */
#define CAN_F0R2_FB19				CAN_F0R2_FB19_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 20 (`CANx_F0R2.FB20`) bit position @def CAN_F0R2_FB20_Pos */
#define CAN_F0R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 0 word 2 bit 20 (`CANx_F0R2.FB20`) bit mask @def CAN_F0R2_FB20_Msk */
#define CAN_F0R2_FB20_Msk			REG_BIT_MASK(CAN_F0R2_FB20_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 20 (`CANx_F0R2.FB20`) bit mask alias @def CAN_F0R2_FB20 */
#define CAN_F0R2_FB20				CAN_F0R2_FB20_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 21 (`CANx_F0R2.FB21`) bit position @def CAN_F0R2_FB21_Pos */
#define CAN_F0R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 0 word 2 bit 21 (`CANx_F0R2.FB21`) bit mask @def CAN_F0R2_FB21_Msk */
#define CAN_F0R2_FB21_Msk			REG_BIT_MASK(CAN_F0R2_FB21_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 21 (`CANx_F0R2.FB21`) bit mask alias @def CAN_F0R2_FB21 */
#define CAN_F0R2_FB21				CAN_F0R2_FB21_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 22 (`CANx_F0R2.FB22`) bit position @def CAN_F0R2_FB22_Pos */
#define CAN_F0R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 0 word 2 bit 22 (`CANx_F0R2.FB22`) bit mask @def CAN_F0R2_FB22_Msk */
#define CAN_F0R2_FB22_Msk			REG_BIT_MASK(CAN_F0R2_FB22_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 22 (`CANx_F0R2.FB22`) bit mask alias @def CAN_F0R2_FB22 */
#define CAN_F0R2_FB22				CAN_F0R2_FB22_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 23 (`CANx_F0R2.FB23`) bit position @def CAN_F0R2_FB23_Pos */
#define CAN_F0R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 0 word 2 bit 23 (`CANx_F0R2.FB23`) bit mask @def CAN_F0R2_FB23_Msk */
#define CAN_F0R2_FB23_Msk			REG_BIT_MASK(CAN_F0R2_FB23_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 23 (`CANx_F0R2.FB23`) bit mask alias @def CAN_F0R2_FB23 */
#define CAN_F0R2_FB23				CAN_F0R2_FB23_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 24 (`CANx_F0R2.FB24`) bit position @def CAN_F0R2_FB24_Pos */
#define CAN_F0R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 0 word 2 bit 24 (`CANx_F0R2.FB24`) bit mask @def CAN_F0R2_FB24_Msk */
#define CAN_F0R2_FB24_Msk			REG_BIT_MASK(CAN_F0R2_FB24_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 24 (`CANx_F0R2.FB24`) bit mask alias @def CAN_F0R2_FB24 */
#define CAN_F0R2_FB24				CAN_F0R2_FB24_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 25 (`CANx_F0R2.FB25`) bit position @def CAN_F0R2_FB25_Pos */
#define CAN_F0R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 0 word 2 bit 25 (`CANx_F0R2.FB25`) bit mask @def CAN_F0R2_FB25_Msk */
#define CAN_F0R2_FB25_Msk			REG_BIT_MASK(CAN_F0R2_FB25_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 25 (`CANx_F0R2.FB25`) bit mask alias @def CAN_F0R2_FB25 */
#define CAN_F0R2_FB25				CAN_F0R2_FB25_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 26 (`CANx_F0R2.FB26`) bit position @def CAN_F0R2_FB26_Pos */
#define CAN_F0R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 0 word 2 bit 26 (`CANx_F0R2.FB26`) bit mask @def CAN_F0R2_FB26_Msk */
#define CAN_F0R2_FB26_Msk			REG_BIT_MASK(CAN_F0R2_FB26_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 26 (`CANx_F0R2.FB26`) bit mask alias @def CAN_F0R2_FB26 */
#define CAN_F0R2_FB26				CAN_F0R2_FB26_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 27 (`CANx_F0R2.FB27`) bit position @def CAN_F0R2_FB27_Pos */
#define CAN_F0R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 0 word 2 bit 27 (`CANx_F0R2.FB27`) bit mask @def CAN_F0R2_FB27_Msk */
#define CAN_F0R2_FB27_Msk			REG_BIT_MASK(CAN_F0R2_FB27_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 27 (`CANx_F0R2.FB27`) bit mask alias @def CAN_F0R2_FB27 */
#define CAN_F0R2_FB27				CAN_F0R2_FB27_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 28 (`CANx_F0R2.FB28`) bit position @def CAN_F0R2_FB28_Pos */
#define CAN_F0R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 0 word 2 bit 28 (`CANx_F0R2.FB28`) bit mask @def CAN_F0R2_FB28_Msk */
#define CAN_F0R2_FB28_Msk			REG_BIT_MASK(CAN_F0R2_FB28_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 28 (`CANx_F0R2.FB28`) bit mask alias @def CAN_F0R2_FB28 */
#define CAN_F0R2_FB28				CAN_F0R2_FB28_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 29 (`CANx_F0R2.FB29`) bit position @def CAN_F0R2_FB29_Pos */
#define CAN_F0R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 0 word 2 bit 29 (`CANx_F0R2.FB29`) bit mask @def CAN_F0R2_FB29_Msk */
#define CAN_F0R2_FB29_Msk			REG_BIT_MASK(CAN_F0R2_FB29_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 29 (`CANx_F0R2.FB29`) bit mask alias @def CAN_F0R2_FB29 */
#define CAN_F0R2_FB29				CAN_F0R2_FB29_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 30 (`CANx_F0R2.FB30`) bit position @def CAN_F0R2_FB30_Pos */
#define CAN_F0R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 0 word 2 bit 30 (`CANx_F0R2.FB30`) bit mask @def CAN_F0R2_FB30_Msk */
#define CAN_F0R2_FB30_Msk			REG_BIT_MASK(CAN_F0R2_FB30_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 30 (`CANx_F0R2.FB30`) bit mask alias @def CAN_F0R2_FB30 */
#define CAN_F0R2_FB30				CAN_F0R2_FB30_Msk

/** @brief Acceptance-filter bank 0 word 2 bit 31 (`CANx_F0R2.FB31`) bit position @def CAN_F0R2_FB31_Pos */
#define CAN_F0R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 0 word 2 bit 31 (`CANx_F0R2.FB31`) bit mask @def CAN_F0R2_FB31_Msk */
#define CAN_F0R2_FB31_Msk			REG_BIT_MASK(CAN_F0R2_FB31_Pos)
/** @brief Acceptance-filter bank 0 word 2 bit 31 (`CANx_F0R2.FB31`) bit mask alias @def CAN_F0R2_FB31 */
#define CAN_F0R2_FB31				CAN_F0R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F1R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 1 word 2 bit 0 (`CANx_F1R2.FB0`) bit position @def CAN_F1R2_FB0_Pos */
#define CAN_F1R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 1 word 2 bit 0 (`CANx_F1R2.FB0`) bit mask @def CAN_F1R2_FB0_Msk */
#define CAN_F1R2_FB0_Msk			REG_BIT_MASK(CAN_F1R2_FB0_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 0 (`CANx_F1R2.FB0`) bit mask alias @def CAN_F1R2_FB0 */
#define CAN_F1R2_FB0				CAN_F1R2_FB0_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 1 (`CANx_F1R2.FB1`) bit position @def CAN_F1R2_FB1_Pos */
#define CAN_F1R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 1 word 2 bit 1 (`CANx_F1R2.FB1`) bit mask @def CAN_F1R2_FB1_Msk */
#define CAN_F1R2_FB1_Msk			REG_BIT_MASK(CAN_F1R2_FB1_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 1 (`CANx_F1R2.FB1`) bit mask alias @def CAN_F1R2_FB1 */
#define CAN_F1R2_FB1				CAN_F1R2_FB1_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 2 (`CANx_F1R2.FB2`) bit position @def CAN_F1R2_FB2_Pos */
#define CAN_F1R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 1 word 2 bit 2 (`CANx_F1R2.FB2`) bit mask @def CAN_F1R2_FB2_Msk */
#define CAN_F1R2_FB2_Msk			REG_BIT_MASK(CAN_F1R2_FB2_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 2 (`CANx_F1R2.FB2`) bit mask alias @def CAN_F1R2_FB2 */
#define CAN_F1R2_FB2				CAN_F1R2_FB2_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 3 (`CANx_F1R2.FB3`) bit position @def CAN_F1R2_FB3_Pos */
#define CAN_F1R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 1 word 2 bit 3 (`CANx_F1R2.FB3`) bit mask @def CAN_F1R2_FB3_Msk */
#define CAN_F1R2_FB3_Msk			REG_BIT_MASK(CAN_F1R2_FB3_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 3 (`CANx_F1R2.FB3`) bit mask alias @def CAN_F1R2_FB3 */
#define CAN_F1R2_FB3				CAN_F1R2_FB3_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 4 (`CANx_F1R2.FB4`) bit position @def CAN_F1R2_FB4_Pos */
#define CAN_F1R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 1 word 2 bit 4 (`CANx_F1R2.FB4`) bit mask @def CAN_F1R2_FB4_Msk */
#define CAN_F1R2_FB4_Msk			REG_BIT_MASK(CAN_F1R2_FB4_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 4 (`CANx_F1R2.FB4`) bit mask alias @def CAN_F1R2_FB4 */
#define CAN_F1R2_FB4				CAN_F1R2_FB4_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 5 (`CANx_F1R2.FB5`) bit position @def CAN_F1R2_FB5_Pos */
#define CAN_F1R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 1 word 2 bit 5 (`CANx_F1R2.FB5`) bit mask @def CAN_F1R2_FB5_Msk */
#define CAN_F1R2_FB5_Msk			REG_BIT_MASK(CAN_F1R2_FB5_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 5 (`CANx_F1R2.FB5`) bit mask alias @def CAN_F1R2_FB5 */
#define CAN_F1R2_FB5				CAN_F1R2_FB5_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 6 (`CANx_F1R2.FB6`) bit position @def CAN_F1R2_FB6_Pos */
#define CAN_F1R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 1 word 2 bit 6 (`CANx_F1R2.FB6`) bit mask @def CAN_F1R2_FB6_Msk */
#define CAN_F1R2_FB6_Msk			REG_BIT_MASK(CAN_F1R2_FB6_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 6 (`CANx_F1R2.FB6`) bit mask alias @def CAN_F1R2_FB6 */
#define CAN_F1R2_FB6				CAN_F1R2_FB6_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 7 (`CANx_F1R2.FB7`) bit position @def CAN_F1R2_FB7_Pos */
#define CAN_F1R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 1 word 2 bit 7 (`CANx_F1R2.FB7`) bit mask @def CAN_F1R2_FB7_Msk */
#define CAN_F1R2_FB7_Msk			REG_BIT_MASK(CAN_F1R2_FB7_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 7 (`CANx_F1R2.FB7`) bit mask alias @def CAN_F1R2_FB7 */
#define CAN_F1R2_FB7				CAN_F1R2_FB7_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 8 (`CANx_F1R2.FB8`) bit position @def CAN_F1R2_FB8_Pos */
#define CAN_F1R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 1 word 2 bit 8 (`CANx_F1R2.FB8`) bit mask @def CAN_F1R2_FB8_Msk */
#define CAN_F1R2_FB8_Msk			REG_BIT_MASK(CAN_F1R2_FB8_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 8 (`CANx_F1R2.FB8`) bit mask alias @def CAN_F1R2_FB8 */
#define CAN_F1R2_FB8				CAN_F1R2_FB8_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 9 (`CANx_F1R2.FB9`) bit position @def CAN_F1R2_FB9_Pos */
#define CAN_F1R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 1 word 2 bit 9 (`CANx_F1R2.FB9`) bit mask @def CAN_F1R2_FB9_Msk */
#define CAN_F1R2_FB9_Msk			REG_BIT_MASK(CAN_F1R2_FB9_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 9 (`CANx_F1R2.FB9`) bit mask alias @def CAN_F1R2_FB9 */
#define CAN_F1R2_FB9				CAN_F1R2_FB9_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 10 (`CANx_F1R2.FB10`) bit position @def CAN_F1R2_FB10_Pos */
#define CAN_F1R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 1 word 2 bit 10 (`CANx_F1R2.FB10`) bit mask @def CAN_F1R2_FB10_Msk */
#define CAN_F1R2_FB10_Msk			REG_BIT_MASK(CAN_F1R2_FB10_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 10 (`CANx_F1R2.FB10`) bit mask alias @def CAN_F1R2_FB10 */
#define CAN_F1R2_FB10				CAN_F1R2_FB10_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 11 (`CANx_F1R2.FB11`) bit position @def CAN_F1R2_FB11_Pos */
#define CAN_F1R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 1 word 2 bit 11 (`CANx_F1R2.FB11`) bit mask @def CAN_F1R2_FB11_Msk */
#define CAN_F1R2_FB11_Msk			REG_BIT_MASK(CAN_F1R2_FB11_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 11 (`CANx_F1R2.FB11`) bit mask alias @def CAN_F1R2_FB11 */
#define CAN_F1R2_FB11				CAN_F1R2_FB11_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 12 (`CANx_F1R2.FB12`) bit position @def CAN_F1R2_FB12_Pos */
#define CAN_F1R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 1 word 2 bit 12 (`CANx_F1R2.FB12`) bit mask @def CAN_F1R2_FB12_Msk */
#define CAN_F1R2_FB12_Msk			REG_BIT_MASK(CAN_F1R2_FB12_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 12 (`CANx_F1R2.FB12`) bit mask alias @def CAN_F1R2_FB12 */
#define CAN_F1R2_FB12				CAN_F1R2_FB12_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 13 (`CANx_F1R2.FB13`) bit position @def CAN_F1R2_FB13_Pos */
#define CAN_F1R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 1 word 2 bit 13 (`CANx_F1R2.FB13`) bit mask @def CAN_F1R2_FB13_Msk */
#define CAN_F1R2_FB13_Msk			REG_BIT_MASK(CAN_F1R2_FB13_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 13 (`CANx_F1R2.FB13`) bit mask alias @def CAN_F1R2_FB13 */
#define CAN_F1R2_FB13				CAN_F1R2_FB13_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 14 (`CANx_F1R2.FB14`) bit position @def CAN_F1R2_FB14_Pos */
#define CAN_F1R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 1 word 2 bit 14 (`CANx_F1R2.FB14`) bit mask @def CAN_F1R2_FB14_Msk */
#define CAN_F1R2_FB14_Msk			REG_BIT_MASK(CAN_F1R2_FB14_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 14 (`CANx_F1R2.FB14`) bit mask alias @def CAN_F1R2_FB14 */
#define CAN_F1R2_FB14				CAN_F1R2_FB14_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 15 (`CANx_F1R2.FB15`) bit position @def CAN_F1R2_FB15_Pos */
#define CAN_F1R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 1 word 2 bit 15 (`CANx_F1R2.FB15`) bit mask @def CAN_F1R2_FB15_Msk */
#define CAN_F1R2_FB15_Msk			REG_BIT_MASK(CAN_F1R2_FB15_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 15 (`CANx_F1R2.FB15`) bit mask alias @def CAN_F1R2_FB15 */
#define CAN_F1R2_FB15				CAN_F1R2_FB15_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 16 (`CANx_F1R2.FB16`) bit position @def CAN_F1R2_FB16_Pos */
#define CAN_F1R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 1 word 2 bit 16 (`CANx_F1R2.FB16`) bit mask @def CAN_F1R2_FB16_Msk */
#define CAN_F1R2_FB16_Msk			REG_BIT_MASK(CAN_F1R2_FB16_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 16 (`CANx_F1R2.FB16`) bit mask alias @def CAN_F1R2_FB16 */
#define CAN_F1R2_FB16				CAN_F1R2_FB16_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 17 (`CANx_F1R2.FB17`) bit position @def CAN_F1R2_FB17_Pos */
#define CAN_F1R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 1 word 2 bit 17 (`CANx_F1R2.FB17`) bit mask @def CAN_F1R2_FB17_Msk */
#define CAN_F1R2_FB17_Msk			REG_BIT_MASK(CAN_F1R2_FB17_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 17 (`CANx_F1R2.FB17`) bit mask alias @def CAN_F1R2_FB17 */
#define CAN_F1R2_FB17				CAN_F1R2_FB17_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 18 (`CANx_F1R2.FB18`) bit position @def CAN_F1R2_FB18_Pos */
#define CAN_F1R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 1 word 2 bit 18 (`CANx_F1R2.FB18`) bit mask @def CAN_F1R2_FB18_Msk */
#define CAN_F1R2_FB18_Msk			REG_BIT_MASK(CAN_F1R2_FB18_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 18 (`CANx_F1R2.FB18`) bit mask alias @def CAN_F1R2_FB18 */
#define CAN_F1R2_FB18				CAN_F1R2_FB18_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 19 (`CANx_F1R2.FB19`) bit position @def CAN_F1R2_FB19_Pos */
#define CAN_F1R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 1 word 2 bit 19 (`CANx_F1R2.FB19`) bit mask @def CAN_F1R2_FB19_Msk */
#define CAN_F1R2_FB19_Msk			REG_BIT_MASK(CAN_F1R2_FB19_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 19 (`CANx_F1R2.FB19`) bit mask alias @def CAN_F1R2_FB19 */
#define CAN_F1R2_FB19				CAN_F1R2_FB19_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 20 (`CANx_F1R2.FB20`) bit position @def CAN_F1R2_FB20_Pos */
#define CAN_F1R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 1 word 2 bit 20 (`CANx_F1R2.FB20`) bit mask @def CAN_F1R2_FB20_Msk */
#define CAN_F1R2_FB20_Msk			REG_BIT_MASK(CAN_F1R2_FB20_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 20 (`CANx_F1R2.FB20`) bit mask alias @def CAN_F1R2_FB20 */
#define CAN_F1R2_FB20				CAN_F1R2_FB20_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 21 (`CANx_F1R2.FB21`) bit position @def CAN_F1R2_FB21_Pos */
#define CAN_F1R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 1 word 2 bit 21 (`CANx_F1R2.FB21`) bit mask @def CAN_F1R2_FB21_Msk */
#define CAN_F1R2_FB21_Msk			REG_BIT_MASK(CAN_F1R2_FB21_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 21 (`CANx_F1R2.FB21`) bit mask alias @def CAN_F1R2_FB21 */
#define CAN_F1R2_FB21				CAN_F1R2_FB21_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 22 (`CANx_F1R2.FB22`) bit position @def CAN_F1R2_FB22_Pos */
#define CAN_F1R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 1 word 2 bit 22 (`CANx_F1R2.FB22`) bit mask @def CAN_F1R2_FB22_Msk */
#define CAN_F1R2_FB22_Msk			REG_BIT_MASK(CAN_F1R2_FB22_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 22 (`CANx_F1R2.FB22`) bit mask alias @def CAN_F1R2_FB22 */
#define CAN_F1R2_FB22				CAN_F1R2_FB22_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 23 (`CANx_F1R2.FB23`) bit position @def CAN_F1R2_FB23_Pos */
#define CAN_F1R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 1 word 2 bit 23 (`CANx_F1R2.FB23`) bit mask @def CAN_F1R2_FB23_Msk */
#define CAN_F1R2_FB23_Msk			REG_BIT_MASK(CAN_F1R2_FB23_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 23 (`CANx_F1R2.FB23`) bit mask alias @def CAN_F1R2_FB23 */
#define CAN_F1R2_FB23				CAN_F1R2_FB23_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 24 (`CANx_F1R2.FB24`) bit position @def CAN_F1R2_FB24_Pos */
#define CAN_F1R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 1 word 2 bit 24 (`CANx_F1R2.FB24`) bit mask @def CAN_F1R2_FB24_Msk */
#define CAN_F1R2_FB24_Msk			REG_BIT_MASK(CAN_F1R2_FB24_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 24 (`CANx_F1R2.FB24`) bit mask alias @def CAN_F1R2_FB24 */
#define CAN_F1R2_FB24				CAN_F1R2_FB24_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 25 (`CANx_F1R2.FB25`) bit position @def CAN_F1R2_FB25_Pos */
#define CAN_F1R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 1 word 2 bit 25 (`CANx_F1R2.FB25`) bit mask @def CAN_F1R2_FB25_Msk */
#define CAN_F1R2_FB25_Msk			REG_BIT_MASK(CAN_F1R2_FB25_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 25 (`CANx_F1R2.FB25`) bit mask alias @def CAN_F1R2_FB25 */
#define CAN_F1R2_FB25				CAN_F1R2_FB25_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 26 (`CANx_F1R2.FB26`) bit position @def CAN_F1R2_FB26_Pos */
#define CAN_F1R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 1 word 2 bit 26 (`CANx_F1R2.FB26`) bit mask @def CAN_F1R2_FB26_Msk */
#define CAN_F1R2_FB26_Msk			REG_BIT_MASK(CAN_F1R2_FB26_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 26 (`CANx_F1R2.FB26`) bit mask alias @def CAN_F1R2_FB26 */
#define CAN_F1R2_FB26				CAN_F1R2_FB26_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 27 (`CANx_F1R2.FB27`) bit position @def CAN_F1R2_FB27_Pos */
#define CAN_F1R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 1 word 2 bit 27 (`CANx_F1R2.FB27`) bit mask @def CAN_F1R2_FB27_Msk */
#define CAN_F1R2_FB27_Msk			REG_BIT_MASK(CAN_F1R2_FB27_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 27 (`CANx_F1R2.FB27`) bit mask alias @def CAN_F1R2_FB27 */
#define CAN_F1R2_FB27				CAN_F1R2_FB27_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 28 (`CANx_F1R2.FB28`) bit position @def CAN_F1R2_FB28_Pos */
#define CAN_F1R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 1 word 2 bit 28 (`CANx_F1R2.FB28`) bit mask @def CAN_F1R2_FB28_Msk */
#define CAN_F1R2_FB28_Msk			REG_BIT_MASK(CAN_F1R2_FB28_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 28 (`CANx_F1R2.FB28`) bit mask alias @def CAN_F1R2_FB28 */
#define CAN_F1R2_FB28				CAN_F1R2_FB28_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 29 (`CANx_F1R2.FB29`) bit position @def CAN_F1R2_FB29_Pos */
#define CAN_F1R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 1 word 2 bit 29 (`CANx_F1R2.FB29`) bit mask @def CAN_F1R2_FB29_Msk */
#define CAN_F1R2_FB29_Msk			REG_BIT_MASK(CAN_F1R2_FB29_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 29 (`CANx_F1R2.FB29`) bit mask alias @def CAN_F1R2_FB29 */
#define CAN_F1R2_FB29				CAN_F1R2_FB29_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 30 (`CANx_F1R2.FB30`) bit position @def CAN_F1R2_FB30_Pos */
#define CAN_F1R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 1 word 2 bit 30 (`CANx_F1R2.FB30`) bit mask @def CAN_F1R2_FB30_Msk */
#define CAN_F1R2_FB30_Msk			REG_BIT_MASK(CAN_F1R2_FB30_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 30 (`CANx_F1R2.FB30`) bit mask alias @def CAN_F1R2_FB30 */
#define CAN_F1R2_FB30				CAN_F1R2_FB30_Msk

/** @brief Acceptance-filter bank 1 word 2 bit 31 (`CANx_F1R2.FB31`) bit position @def CAN_F1R2_FB31_Pos */
#define CAN_F1R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 1 word 2 bit 31 (`CANx_F1R2.FB31`) bit mask @def CAN_F1R2_FB31_Msk */
#define CAN_F1R2_FB31_Msk			REG_BIT_MASK(CAN_F1R2_FB31_Pos)
/** @brief Acceptance-filter bank 1 word 2 bit 31 (`CANx_F1R2.FB31`) bit mask alias @def CAN_F1R2_FB31 */
#define CAN_F1R2_FB31				CAN_F1R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F2R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 2 word 2 bit 0 (`CANx_F2R2.FB0`) bit position @def CAN_F2R2_FB0_Pos */
#define CAN_F2R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 2 word 2 bit 0 (`CANx_F2R2.FB0`) bit mask @def CAN_F2R2_FB0_Msk */
#define CAN_F2R2_FB0_Msk			REG_BIT_MASK(CAN_F2R2_FB0_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 0 (`CANx_F2R2.FB0`) bit mask alias @def CAN_F2R2_FB0 */
#define CAN_F2R2_FB0				CAN_F2R2_FB0_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 1 (`CANx_F2R2.FB1`) bit position @def CAN_F2R2_FB1_Pos */
#define CAN_F2R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 2 word 2 bit 1 (`CANx_F2R2.FB1`) bit mask @def CAN_F2R2_FB1_Msk */
#define CAN_F2R2_FB1_Msk			REG_BIT_MASK(CAN_F2R2_FB1_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 1 (`CANx_F2R2.FB1`) bit mask alias @def CAN_F2R2_FB1 */
#define CAN_F2R2_FB1				CAN_F2R2_FB1_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 2 (`CANx_F2R2.FB2`) bit position @def CAN_F2R2_FB2_Pos */
#define CAN_F2R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 2 word 2 bit 2 (`CANx_F2R2.FB2`) bit mask @def CAN_F2R2_FB2_Msk */
#define CAN_F2R2_FB2_Msk			REG_BIT_MASK(CAN_F2R2_FB2_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 2 (`CANx_F2R2.FB2`) bit mask alias @def CAN_F2R2_FB2 */
#define CAN_F2R2_FB2				CAN_F2R2_FB2_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 3 (`CANx_F2R2.FB3`) bit position @def CAN_F2R2_FB3_Pos */
#define CAN_F2R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 2 word 2 bit 3 (`CANx_F2R2.FB3`) bit mask @def CAN_F2R2_FB3_Msk */
#define CAN_F2R2_FB3_Msk			REG_BIT_MASK(CAN_F2R2_FB3_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 3 (`CANx_F2R2.FB3`) bit mask alias @def CAN_F2R2_FB3 */
#define CAN_F2R2_FB3				CAN_F2R2_FB3_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 4 (`CANx_F2R2.FB4`) bit position @def CAN_F2R2_FB4_Pos */
#define CAN_F2R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 2 word 2 bit 4 (`CANx_F2R2.FB4`) bit mask @def CAN_F2R2_FB4_Msk */
#define CAN_F2R2_FB4_Msk			REG_BIT_MASK(CAN_F2R2_FB4_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 4 (`CANx_F2R2.FB4`) bit mask alias @def CAN_F2R2_FB4 */
#define CAN_F2R2_FB4				CAN_F2R2_FB4_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 5 (`CANx_F2R2.FB5`) bit position @def CAN_F2R2_FB5_Pos */
#define CAN_F2R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 2 word 2 bit 5 (`CANx_F2R2.FB5`) bit mask @def CAN_F2R2_FB5_Msk */
#define CAN_F2R2_FB5_Msk			REG_BIT_MASK(CAN_F2R2_FB5_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 5 (`CANx_F2R2.FB5`) bit mask alias @def CAN_F2R2_FB5 */
#define CAN_F2R2_FB5				CAN_F2R2_FB5_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 6 (`CANx_F2R2.FB6`) bit position @def CAN_F2R2_FB6_Pos */
#define CAN_F2R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 2 word 2 bit 6 (`CANx_F2R2.FB6`) bit mask @def CAN_F2R2_FB6_Msk */
#define CAN_F2R2_FB6_Msk			REG_BIT_MASK(CAN_F2R2_FB6_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 6 (`CANx_F2R2.FB6`) bit mask alias @def CAN_F2R2_FB6 */
#define CAN_F2R2_FB6				CAN_F2R2_FB6_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 7 (`CANx_F2R2.FB7`) bit position @def CAN_F2R2_FB7_Pos */
#define CAN_F2R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 2 word 2 bit 7 (`CANx_F2R2.FB7`) bit mask @def CAN_F2R2_FB7_Msk */
#define CAN_F2R2_FB7_Msk			REG_BIT_MASK(CAN_F2R2_FB7_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 7 (`CANx_F2R2.FB7`) bit mask alias @def CAN_F2R2_FB7 */
#define CAN_F2R2_FB7				CAN_F2R2_FB7_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 8 (`CANx_F2R2.FB8`) bit position @def CAN_F2R2_FB8_Pos */
#define CAN_F2R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 2 word 2 bit 8 (`CANx_F2R2.FB8`) bit mask @def CAN_F2R2_FB8_Msk */
#define CAN_F2R2_FB8_Msk			REG_BIT_MASK(CAN_F2R2_FB8_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 8 (`CANx_F2R2.FB8`) bit mask alias @def CAN_F2R2_FB8 */
#define CAN_F2R2_FB8				CAN_F2R2_FB8_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 9 (`CANx_F2R2.FB9`) bit position @def CAN_F2R2_FB9_Pos */
#define CAN_F2R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 2 word 2 bit 9 (`CANx_F2R2.FB9`) bit mask @def CAN_F2R2_FB9_Msk */
#define CAN_F2R2_FB9_Msk			REG_BIT_MASK(CAN_F2R2_FB9_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 9 (`CANx_F2R2.FB9`) bit mask alias @def CAN_F2R2_FB9 */
#define CAN_F2R2_FB9				CAN_F2R2_FB9_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 10 (`CANx_F2R2.FB10`) bit position @def CAN_F2R2_FB10_Pos */
#define CAN_F2R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 2 word 2 bit 10 (`CANx_F2R2.FB10`) bit mask @def CAN_F2R2_FB10_Msk */
#define CAN_F2R2_FB10_Msk			REG_BIT_MASK(CAN_F2R2_FB10_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 10 (`CANx_F2R2.FB10`) bit mask alias @def CAN_F2R2_FB10 */
#define CAN_F2R2_FB10				CAN_F2R2_FB10_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 11 (`CANx_F2R2.FB11`) bit position @def CAN_F2R2_FB11_Pos */
#define CAN_F2R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 2 word 2 bit 11 (`CANx_F2R2.FB11`) bit mask @def CAN_F2R2_FB11_Msk */
#define CAN_F2R2_FB11_Msk			REG_BIT_MASK(CAN_F2R2_FB11_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 11 (`CANx_F2R2.FB11`) bit mask alias @def CAN_F2R2_FB11 */
#define CAN_F2R2_FB11				CAN_F2R2_FB11_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 12 (`CANx_F2R2.FB12`) bit position @def CAN_F2R2_FB12_Pos */
#define CAN_F2R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 2 word 2 bit 12 (`CANx_F2R2.FB12`) bit mask @def CAN_F2R2_FB12_Msk */
#define CAN_F2R2_FB12_Msk			REG_BIT_MASK(CAN_F2R2_FB12_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 12 (`CANx_F2R2.FB12`) bit mask alias @def CAN_F2R2_FB12 */
#define CAN_F2R2_FB12				CAN_F2R2_FB12_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 13 (`CANx_F2R2.FB13`) bit position @def CAN_F2R2_FB13_Pos */
#define CAN_F2R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 2 word 2 bit 13 (`CANx_F2R2.FB13`) bit mask @def CAN_F2R2_FB13_Msk */
#define CAN_F2R2_FB13_Msk			REG_BIT_MASK(CAN_F2R2_FB13_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 13 (`CANx_F2R2.FB13`) bit mask alias @def CAN_F2R2_FB13 */
#define CAN_F2R2_FB13				CAN_F2R2_FB13_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 14 (`CANx_F2R2.FB14`) bit position @def CAN_F2R2_FB14_Pos */
#define CAN_F2R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 2 word 2 bit 14 (`CANx_F2R2.FB14`) bit mask @def CAN_F2R2_FB14_Msk */
#define CAN_F2R2_FB14_Msk			REG_BIT_MASK(CAN_F2R2_FB14_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 14 (`CANx_F2R2.FB14`) bit mask alias @def CAN_F2R2_FB14 */
#define CAN_F2R2_FB14				CAN_F2R2_FB14_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 15 (`CANx_F2R2.FB15`) bit position @def CAN_F2R2_FB15_Pos */
#define CAN_F2R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 2 word 2 bit 15 (`CANx_F2R2.FB15`) bit mask @def CAN_F2R2_FB15_Msk */
#define CAN_F2R2_FB15_Msk			REG_BIT_MASK(CAN_F2R2_FB15_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 15 (`CANx_F2R2.FB15`) bit mask alias @def CAN_F2R2_FB15 */
#define CAN_F2R2_FB15				CAN_F2R2_FB15_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 16 (`CANx_F2R2.FB16`) bit position @def CAN_F2R2_FB16_Pos */
#define CAN_F2R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 2 word 2 bit 16 (`CANx_F2R2.FB16`) bit mask @def CAN_F2R2_FB16_Msk */
#define CAN_F2R2_FB16_Msk			REG_BIT_MASK(CAN_F2R2_FB16_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 16 (`CANx_F2R2.FB16`) bit mask alias @def CAN_F2R2_FB16 */
#define CAN_F2R2_FB16				CAN_F2R2_FB16_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 17 (`CANx_F2R2.FB17`) bit position @def CAN_F2R2_FB17_Pos */
#define CAN_F2R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 2 word 2 bit 17 (`CANx_F2R2.FB17`) bit mask @def CAN_F2R2_FB17_Msk */
#define CAN_F2R2_FB17_Msk			REG_BIT_MASK(CAN_F2R2_FB17_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 17 (`CANx_F2R2.FB17`) bit mask alias @def CAN_F2R2_FB17 */
#define CAN_F2R2_FB17				CAN_F2R2_FB17_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 18 (`CANx_F2R2.FB18`) bit position @def CAN_F2R2_FB18_Pos */
#define CAN_F2R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 2 word 2 bit 18 (`CANx_F2R2.FB18`) bit mask @def CAN_F2R2_FB18_Msk */
#define CAN_F2R2_FB18_Msk			REG_BIT_MASK(CAN_F2R2_FB18_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 18 (`CANx_F2R2.FB18`) bit mask alias @def CAN_F2R2_FB18 */
#define CAN_F2R2_FB18				CAN_F2R2_FB18_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 19 (`CANx_F2R2.FB19`) bit position @def CAN_F2R2_FB19_Pos */
#define CAN_F2R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 2 word 2 bit 19 (`CANx_F2R2.FB19`) bit mask @def CAN_F2R2_FB19_Msk */
#define CAN_F2R2_FB19_Msk			REG_BIT_MASK(CAN_F2R2_FB19_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 19 (`CANx_F2R2.FB19`) bit mask alias @def CAN_F2R2_FB19 */
#define CAN_F2R2_FB19				CAN_F2R2_FB19_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 20 (`CANx_F2R2.FB20`) bit position @def CAN_F2R2_FB20_Pos */
#define CAN_F2R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 2 word 2 bit 20 (`CANx_F2R2.FB20`) bit mask @def CAN_F2R2_FB20_Msk */
#define CAN_F2R2_FB20_Msk			REG_BIT_MASK(CAN_F2R2_FB20_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 20 (`CANx_F2R2.FB20`) bit mask alias @def CAN_F2R2_FB20 */
#define CAN_F2R2_FB20				CAN_F2R2_FB20_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 21 (`CANx_F2R2.FB21`) bit position @def CAN_F2R2_FB21_Pos */
#define CAN_F2R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 2 word 2 bit 21 (`CANx_F2R2.FB21`) bit mask @def CAN_F2R2_FB21_Msk */
#define CAN_F2R2_FB21_Msk			REG_BIT_MASK(CAN_F2R2_FB21_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 21 (`CANx_F2R2.FB21`) bit mask alias @def CAN_F2R2_FB21 */
#define CAN_F2R2_FB21				CAN_F2R2_FB21_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 22 (`CANx_F2R2.FB22`) bit position @def CAN_F2R2_FB22_Pos */
#define CAN_F2R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 2 word 2 bit 22 (`CANx_F2R2.FB22`) bit mask @def CAN_F2R2_FB22_Msk */
#define CAN_F2R2_FB22_Msk			REG_BIT_MASK(CAN_F2R2_FB22_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 22 (`CANx_F2R2.FB22`) bit mask alias @def CAN_F2R2_FB22 */
#define CAN_F2R2_FB22				CAN_F2R2_FB22_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 23 (`CANx_F2R2.FB23`) bit position @def CAN_F2R2_FB23_Pos */
#define CAN_F2R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 2 word 2 bit 23 (`CANx_F2R2.FB23`) bit mask @def CAN_F2R2_FB23_Msk */
#define CAN_F2R2_FB23_Msk			REG_BIT_MASK(CAN_F2R2_FB23_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 23 (`CANx_F2R2.FB23`) bit mask alias @def CAN_F2R2_FB23 */
#define CAN_F2R2_FB23				CAN_F2R2_FB23_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 24 (`CANx_F2R2.FB24`) bit position @def CAN_F2R2_FB24_Pos */
#define CAN_F2R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 2 word 2 bit 24 (`CANx_F2R2.FB24`) bit mask @def CAN_F2R2_FB24_Msk */
#define CAN_F2R2_FB24_Msk			REG_BIT_MASK(CAN_F2R2_FB24_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 24 (`CANx_F2R2.FB24`) bit mask alias @def CAN_F2R2_FB24 */
#define CAN_F2R2_FB24				CAN_F2R2_FB24_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 25 (`CANx_F2R2.FB25`) bit position @def CAN_F2R2_FB25_Pos */
#define CAN_F2R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 2 word 2 bit 25 (`CANx_F2R2.FB25`) bit mask @def CAN_F2R2_FB25_Msk */
#define CAN_F2R2_FB25_Msk			REG_BIT_MASK(CAN_F2R2_FB25_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 25 (`CANx_F2R2.FB25`) bit mask alias @def CAN_F2R2_FB25 */
#define CAN_F2R2_FB25				CAN_F2R2_FB25_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 26 (`CANx_F2R2.FB26`) bit position @def CAN_F2R2_FB26_Pos */
#define CAN_F2R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 2 word 2 bit 26 (`CANx_F2R2.FB26`) bit mask @def CAN_F2R2_FB26_Msk */
#define CAN_F2R2_FB26_Msk			REG_BIT_MASK(CAN_F2R2_FB26_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 26 (`CANx_F2R2.FB26`) bit mask alias @def CAN_F2R2_FB26 */
#define CAN_F2R2_FB26				CAN_F2R2_FB26_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 27 (`CANx_F2R2.FB27`) bit position @def CAN_F2R2_FB27_Pos */
#define CAN_F2R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 2 word 2 bit 27 (`CANx_F2R2.FB27`) bit mask @def CAN_F2R2_FB27_Msk */
#define CAN_F2R2_FB27_Msk			REG_BIT_MASK(CAN_F2R2_FB27_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 27 (`CANx_F2R2.FB27`) bit mask alias @def CAN_F2R2_FB27 */
#define CAN_F2R2_FB27				CAN_F2R2_FB27_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 28 (`CANx_F2R2.FB28`) bit position @def CAN_F2R2_FB28_Pos */
#define CAN_F2R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 2 word 2 bit 28 (`CANx_F2R2.FB28`) bit mask @def CAN_F2R2_FB28_Msk */
#define CAN_F2R2_FB28_Msk			REG_BIT_MASK(CAN_F2R2_FB28_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 28 (`CANx_F2R2.FB28`) bit mask alias @def CAN_F2R2_FB28 */
#define CAN_F2R2_FB28				CAN_F2R2_FB28_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 29 (`CANx_F2R2.FB29`) bit position @def CAN_F2R2_FB29_Pos */
#define CAN_F2R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 2 word 2 bit 29 (`CANx_F2R2.FB29`) bit mask @def CAN_F2R2_FB29_Msk */
#define CAN_F2R2_FB29_Msk			REG_BIT_MASK(CAN_F2R2_FB29_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 29 (`CANx_F2R2.FB29`) bit mask alias @def CAN_F2R2_FB29 */
#define CAN_F2R2_FB29				CAN_F2R2_FB29_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 30 (`CANx_F2R2.FB30`) bit position @def CAN_F2R2_FB30_Pos */
#define CAN_F2R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 2 word 2 bit 30 (`CANx_F2R2.FB30`) bit mask @def CAN_F2R2_FB30_Msk */
#define CAN_F2R2_FB30_Msk			REG_BIT_MASK(CAN_F2R2_FB30_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 30 (`CANx_F2R2.FB30`) bit mask alias @def CAN_F2R2_FB30 */
#define CAN_F2R2_FB30				CAN_F2R2_FB30_Msk

/** @brief Acceptance-filter bank 2 word 2 bit 31 (`CANx_F2R2.FB31`) bit position @def CAN_F2R2_FB31_Pos */
#define CAN_F2R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 2 word 2 bit 31 (`CANx_F2R2.FB31`) bit mask @def CAN_F2R2_FB31_Msk */
#define CAN_F2R2_FB31_Msk			REG_BIT_MASK(CAN_F2R2_FB31_Pos)
/** @brief Acceptance-filter bank 2 word 2 bit 31 (`CANx_F2R2.FB31`) bit mask alias @def CAN_F2R2_FB31 */
#define CAN_F2R2_FB31				CAN_F2R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F3R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 3 word 2 bit 0 (`CANx_F3R2.FB0`) bit position @def CAN_F3R2_FB0_Pos */
#define CAN_F3R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 3 word 2 bit 0 (`CANx_F3R2.FB0`) bit mask @def CAN_F3R2_FB0_Msk */
#define CAN_F3R2_FB0_Msk			REG_BIT_MASK(CAN_F3R2_FB0_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 0 (`CANx_F3R2.FB0`) bit mask alias @def CAN_F3R2_FB0 */
#define CAN_F3R2_FB0				CAN_F3R2_FB0_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 1 (`CANx_F3R2.FB1`) bit position @def CAN_F3R2_FB1_Pos */
#define CAN_F3R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 3 word 2 bit 1 (`CANx_F3R2.FB1`) bit mask @def CAN_F3R2_FB1_Msk */
#define CAN_F3R2_FB1_Msk			REG_BIT_MASK(CAN_F3R2_FB1_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 1 (`CANx_F3R2.FB1`) bit mask alias @def CAN_F3R2_FB1 */
#define CAN_F3R2_FB1				CAN_F3R2_FB1_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 2 (`CANx_F3R2.FB2`) bit position @def CAN_F3R2_FB2_Pos */
#define CAN_F3R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 3 word 2 bit 2 (`CANx_F3R2.FB2`) bit mask @def CAN_F3R2_FB2_Msk */
#define CAN_F3R2_FB2_Msk			REG_BIT_MASK(CAN_F3R2_FB2_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 2 (`CANx_F3R2.FB2`) bit mask alias @def CAN_F3R2_FB2 */
#define CAN_F3R2_FB2				CAN_F3R2_FB2_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 3 (`CANx_F3R2.FB3`) bit position @def CAN_F3R2_FB3_Pos */
#define CAN_F3R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 3 word 2 bit 3 (`CANx_F3R2.FB3`) bit mask @def CAN_F3R2_FB3_Msk */
#define CAN_F3R2_FB3_Msk			REG_BIT_MASK(CAN_F3R2_FB3_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 3 (`CANx_F3R2.FB3`) bit mask alias @def CAN_F3R2_FB3 */
#define CAN_F3R2_FB3				CAN_F3R2_FB3_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 4 (`CANx_F3R2.FB4`) bit position @def CAN_F3R2_FB4_Pos */
#define CAN_F3R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 3 word 2 bit 4 (`CANx_F3R2.FB4`) bit mask @def CAN_F3R2_FB4_Msk */
#define CAN_F3R2_FB4_Msk			REG_BIT_MASK(CAN_F3R2_FB4_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 4 (`CANx_F3R2.FB4`) bit mask alias @def CAN_F3R2_FB4 */
#define CAN_F3R2_FB4				CAN_F3R2_FB4_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 5 (`CANx_F3R2.FB5`) bit position @def CAN_F3R2_FB5_Pos */
#define CAN_F3R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 3 word 2 bit 5 (`CANx_F3R2.FB5`) bit mask @def CAN_F3R2_FB5_Msk */
#define CAN_F3R2_FB5_Msk			REG_BIT_MASK(CAN_F3R2_FB5_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 5 (`CANx_F3R2.FB5`) bit mask alias @def CAN_F3R2_FB5 */
#define CAN_F3R2_FB5				CAN_F3R2_FB5_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 6 (`CANx_F3R2.FB6`) bit position @def CAN_F3R2_FB6_Pos */
#define CAN_F3R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 3 word 2 bit 6 (`CANx_F3R2.FB6`) bit mask @def CAN_F3R2_FB6_Msk */
#define CAN_F3R2_FB6_Msk			REG_BIT_MASK(CAN_F3R2_FB6_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 6 (`CANx_F3R2.FB6`) bit mask alias @def CAN_F3R2_FB6 */
#define CAN_F3R2_FB6				CAN_F3R2_FB6_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 7 (`CANx_F3R2.FB7`) bit position @def CAN_F3R2_FB7_Pos */
#define CAN_F3R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 3 word 2 bit 7 (`CANx_F3R2.FB7`) bit mask @def CAN_F3R2_FB7_Msk */
#define CAN_F3R2_FB7_Msk			REG_BIT_MASK(CAN_F3R2_FB7_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 7 (`CANx_F3R2.FB7`) bit mask alias @def CAN_F3R2_FB7 */
#define CAN_F3R2_FB7				CAN_F3R2_FB7_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 8 (`CANx_F3R2.FB8`) bit position @def CAN_F3R2_FB8_Pos */
#define CAN_F3R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 3 word 2 bit 8 (`CANx_F3R2.FB8`) bit mask @def CAN_F3R2_FB8_Msk */
#define CAN_F3R2_FB8_Msk			REG_BIT_MASK(CAN_F3R2_FB8_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 8 (`CANx_F3R2.FB8`) bit mask alias @def CAN_F3R2_FB8 */
#define CAN_F3R2_FB8				CAN_F3R2_FB8_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 9 (`CANx_F3R2.FB9`) bit position @def CAN_F3R2_FB9_Pos */
#define CAN_F3R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 3 word 2 bit 9 (`CANx_F3R2.FB9`) bit mask @def CAN_F3R2_FB9_Msk */
#define CAN_F3R2_FB9_Msk			REG_BIT_MASK(CAN_F3R2_FB9_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 9 (`CANx_F3R2.FB9`) bit mask alias @def CAN_F3R2_FB9 */
#define CAN_F3R2_FB9				CAN_F3R2_FB9_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 10 (`CANx_F3R2.FB10`) bit position @def CAN_F3R2_FB10_Pos */
#define CAN_F3R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 3 word 2 bit 10 (`CANx_F3R2.FB10`) bit mask @def CAN_F3R2_FB10_Msk */
#define CAN_F3R2_FB10_Msk			REG_BIT_MASK(CAN_F3R2_FB10_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 10 (`CANx_F3R2.FB10`) bit mask alias @def CAN_F3R2_FB10 */
#define CAN_F3R2_FB10				CAN_F3R2_FB10_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 11 (`CANx_F3R2.FB11`) bit position @def CAN_F3R2_FB11_Pos */
#define CAN_F3R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 3 word 2 bit 11 (`CANx_F3R2.FB11`) bit mask @def CAN_F3R2_FB11_Msk */
#define CAN_F3R2_FB11_Msk			REG_BIT_MASK(CAN_F3R2_FB11_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 11 (`CANx_F3R2.FB11`) bit mask alias @def CAN_F3R2_FB11 */
#define CAN_F3R2_FB11				CAN_F3R2_FB11_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 12 (`CANx_F3R2.FB12`) bit position @def CAN_F3R2_FB12_Pos */
#define CAN_F3R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 3 word 2 bit 12 (`CANx_F3R2.FB12`) bit mask @def CAN_F3R2_FB12_Msk */
#define CAN_F3R2_FB12_Msk			REG_BIT_MASK(CAN_F3R2_FB12_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 12 (`CANx_F3R2.FB12`) bit mask alias @def CAN_F3R2_FB12 */
#define CAN_F3R2_FB12				CAN_F3R2_FB12_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 13 (`CANx_F3R2.FB13`) bit position @def CAN_F3R2_FB13_Pos */
#define CAN_F3R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 3 word 2 bit 13 (`CANx_F3R2.FB13`) bit mask @def CAN_F3R2_FB13_Msk */
#define CAN_F3R2_FB13_Msk			REG_BIT_MASK(CAN_F3R2_FB13_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 13 (`CANx_F3R2.FB13`) bit mask alias @def CAN_F3R2_FB13 */
#define CAN_F3R2_FB13				CAN_F3R2_FB13_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 14 (`CANx_F3R2.FB14`) bit position @def CAN_F3R2_FB14_Pos */
#define CAN_F3R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 3 word 2 bit 14 (`CANx_F3R2.FB14`) bit mask @def CAN_F3R2_FB14_Msk */
#define CAN_F3R2_FB14_Msk			REG_BIT_MASK(CAN_F3R2_FB14_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 14 (`CANx_F3R2.FB14`) bit mask alias @def CAN_F3R2_FB14 */
#define CAN_F3R2_FB14				CAN_F3R2_FB14_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 15 (`CANx_F3R2.FB15`) bit position @def CAN_F3R2_FB15_Pos */
#define CAN_F3R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 3 word 2 bit 15 (`CANx_F3R2.FB15`) bit mask @def CAN_F3R2_FB15_Msk */
#define CAN_F3R2_FB15_Msk			REG_BIT_MASK(CAN_F3R2_FB15_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 15 (`CANx_F3R2.FB15`) bit mask alias @def CAN_F3R2_FB15 */
#define CAN_F3R2_FB15				CAN_F3R2_FB15_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 16 (`CANx_F3R2.FB16`) bit position @def CAN_F3R2_FB16_Pos */
#define CAN_F3R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 3 word 2 bit 16 (`CANx_F3R2.FB16`) bit mask @def CAN_F3R2_FB16_Msk */
#define CAN_F3R2_FB16_Msk			REG_BIT_MASK(CAN_F3R2_FB16_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 16 (`CANx_F3R2.FB16`) bit mask alias @def CAN_F3R2_FB16 */
#define CAN_F3R2_FB16				CAN_F3R2_FB16_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 17 (`CANx_F3R2.FB17`) bit position @def CAN_F3R2_FB17_Pos */
#define CAN_F3R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 3 word 2 bit 17 (`CANx_F3R2.FB17`) bit mask @def CAN_F3R2_FB17_Msk */
#define CAN_F3R2_FB17_Msk			REG_BIT_MASK(CAN_F3R2_FB17_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 17 (`CANx_F3R2.FB17`) bit mask alias @def CAN_F3R2_FB17 */
#define CAN_F3R2_FB17				CAN_F3R2_FB17_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 18 (`CANx_F3R2.FB18`) bit position @def CAN_F3R2_FB18_Pos */
#define CAN_F3R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 3 word 2 bit 18 (`CANx_F3R2.FB18`) bit mask @def CAN_F3R2_FB18_Msk */
#define CAN_F3R2_FB18_Msk			REG_BIT_MASK(CAN_F3R2_FB18_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 18 (`CANx_F3R2.FB18`) bit mask alias @def CAN_F3R2_FB18 */
#define CAN_F3R2_FB18				CAN_F3R2_FB18_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 19 (`CANx_F3R2.FB19`) bit position @def CAN_F3R2_FB19_Pos */
#define CAN_F3R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 3 word 2 bit 19 (`CANx_F3R2.FB19`) bit mask @def CAN_F3R2_FB19_Msk */
#define CAN_F3R2_FB19_Msk			REG_BIT_MASK(CAN_F3R2_FB19_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 19 (`CANx_F3R2.FB19`) bit mask alias @def CAN_F3R2_FB19 */
#define CAN_F3R2_FB19				CAN_F3R2_FB19_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 20 (`CANx_F3R2.FB20`) bit position @def CAN_F3R2_FB20_Pos */
#define CAN_F3R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 3 word 2 bit 20 (`CANx_F3R2.FB20`) bit mask @def CAN_F3R2_FB20_Msk */
#define CAN_F3R2_FB20_Msk			REG_BIT_MASK(CAN_F3R2_FB20_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 20 (`CANx_F3R2.FB20`) bit mask alias @def CAN_F3R2_FB20 */
#define CAN_F3R2_FB20				CAN_F3R2_FB20_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 21 (`CANx_F3R2.FB21`) bit position @def CAN_F3R2_FB21_Pos */
#define CAN_F3R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 3 word 2 bit 21 (`CANx_F3R2.FB21`) bit mask @def CAN_F3R2_FB21_Msk */
#define CAN_F3R2_FB21_Msk			REG_BIT_MASK(CAN_F3R2_FB21_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 21 (`CANx_F3R2.FB21`) bit mask alias @def CAN_F3R2_FB21 */
#define CAN_F3R2_FB21				CAN_F3R2_FB21_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 22 (`CANx_F3R2.FB22`) bit position @def CAN_F3R2_FB22_Pos */
#define CAN_F3R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 3 word 2 bit 22 (`CANx_F3R2.FB22`) bit mask @def CAN_F3R2_FB22_Msk */
#define CAN_F3R2_FB22_Msk			REG_BIT_MASK(CAN_F3R2_FB22_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 22 (`CANx_F3R2.FB22`) bit mask alias @def CAN_F3R2_FB22 */
#define CAN_F3R2_FB22				CAN_F3R2_FB22_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 23 (`CANx_F3R2.FB23`) bit position @def CAN_F3R2_FB23_Pos */
#define CAN_F3R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 3 word 2 bit 23 (`CANx_F3R2.FB23`) bit mask @def CAN_F3R2_FB23_Msk */
#define CAN_F3R2_FB23_Msk			REG_BIT_MASK(CAN_F3R2_FB23_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 23 (`CANx_F3R2.FB23`) bit mask alias @def CAN_F3R2_FB23 */
#define CAN_F3R2_FB23				CAN_F3R2_FB23_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 24 (`CANx_F3R2.FB24`) bit position @def CAN_F3R2_FB24_Pos */
#define CAN_F3R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 3 word 2 bit 24 (`CANx_F3R2.FB24`) bit mask @def CAN_F3R2_FB24_Msk */
#define CAN_F3R2_FB24_Msk			REG_BIT_MASK(CAN_F3R2_FB24_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 24 (`CANx_F3R2.FB24`) bit mask alias @def CAN_F3R2_FB24 */
#define CAN_F3R2_FB24				CAN_F3R2_FB24_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 25 (`CANx_F3R2.FB25`) bit position @def CAN_F3R2_FB25_Pos */
#define CAN_F3R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 3 word 2 bit 25 (`CANx_F3R2.FB25`) bit mask @def CAN_F3R2_FB25_Msk */
#define CAN_F3R2_FB25_Msk			REG_BIT_MASK(CAN_F3R2_FB25_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 25 (`CANx_F3R2.FB25`) bit mask alias @def CAN_F3R2_FB25 */
#define CAN_F3R2_FB25				CAN_F3R2_FB25_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 26 (`CANx_F3R2.FB26`) bit position @def CAN_F3R2_FB26_Pos */
#define CAN_F3R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 3 word 2 bit 26 (`CANx_F3R2.FB26`) bit mask @def CAN_F3R2_FB26_Msk */
#define CAN_F3R2_FB26_Msk			REG_BIT_MASK(CAN_F3R2_FB26_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 26 (`CANx_F3R2.FB26`) bit mask alias @def CAN_F3R2_FB26 */
#define CAN_F3R2_FB26				CAN_F3R2_FB26_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 27 (`CANx_F3R2.FB27`) bit position @def CAN_F3R2_FB27_Pos */
#define CAN_F3R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 3 word 2 bit 27 (`CANx_F3R2.FB27`) bit mask @def CAN_F3R2_FB27_Msk */
#define CAN_F3R2_FB27_Msk			REG_BIT_MASK(CAN_F3R2_FB27_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 27 (`CANx_F3R2.FB27`) bit mask alias @def CAN_F3R2_FB27 */
#define CAN_F3R2_FB27				CAN_F3R2_FB27_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 28 (`CANx_F3R2.FB28`) bit position @def CAN_F3R2_FB28_Pos */
#define CAN_F3R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 3 word 2 bit 28 (`CANx_F3R2.FB28`) bit mask @def CAN_F3R2_FB28_Msk */
#define CAN_F3R2_FB28_Msk			REG_BIT_MASK(CAN_F3R2_FB28_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 28 (`CANx_F3R2.FB28`) bit mask alias @def CAN_F3R2_FB28 */
#define CAN_F3R2_FB28				CAN_F3R2_FB28_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 29 (`CANx_F3R2.FB29`) bit position @def CAN_F3R2_FB29_Pos */
#define CAN_F3R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 3 word 2 bit 29 (`CANx_F3R2.FB29`) bit mask @def CAN_F3R2_FB29_Msk */
#define CAN_F3R2_FB29_Msk			REG_BIT_MASK(CAN_F3R2_FB29_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 29 (`CANx_F3R2.FB29`) bit mask alias @def CAN_F3R2_FB29 */
#define CAN_F3R2_FB29				CAN_F3R2_FB29_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 30 (`CANx_F3R2.FB30`) bit position @def CAN_F3R2_FB30_Pos */
#define CAN_F3R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 3 word 2 bit 30 (`CANx_F3R2.FB30`) bit mask @def CAN_F3R2_FB30_Msk */
#define CAN_F3R2_FB30_Msk			REG_BIT_MASK(CAN_F3R2_FB30_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 30 (`CANx_F3R2.FB30`) bit mask alias @def CAN_F3R2_FB30 */
#define CAN_F3R2_FB30				CAN_F3R2_FB30_Msk

/** @brief Acceptance-filter bank 3 word 2 bit 31 (`CANx_F3R2.FB31`) bit position @def CAN_F3R2_FB31_Pos */
#define CAN_F3R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 3 word 2 bit 31 (`CANx_F3R2.FB31`) bit mask @def CAN_F3R2_FB31_Msk */
#define CAN_F3R2_FB31_Msk			REG_BIT_MASK(CAN_F3R2_FB31_Pos)
/** @brief Acceptance-filter bank 3 word 2 bit 31 (`CANx_F3R2.FB31`) bit mask alias @def CAN_F3R2_FB31 */
#define CAN_F3R2_FB31				CAN_F3R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F4R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 4 word 2 bit 0 (`CANx_F4R2.FB0`) bit position @def CAN_F4R2_FB0_Pos */
#define CAN_F4R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 4 word 2 bit 0 (`CANx_F4R2.FB0`) bit mask @def CAN_F4R2_FB0_Msk */
#define CAN_F4R2_FB0_Msk			REG_BIT_MASK(CAN_F4R2_FB0_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 0 (`CANx_F4R2.FB0`) bit mask alias @def CAN_F4R2_FB0 */
#define CAN_F4R2_FB0				CAN_F4R2_FB0_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 1 (`CANx_F4R2.FB1`) bit position @def CAN_F4R2_FB1_Pos */
#define CAN_F4R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 4 word 2 bit 1 (`CANx_F4R2.FB1`) bit mask @def CAN_F4R2_FB1_Msk */
#define CAN_F4R2_FB1_Msk			REG_BIT_MASK(CAN_F4R2_FB1_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 1 (`CANx_F4R2.FB1`) bit mask alias @def CAN_F4R2_FB1 */
#define CAN_F4R2_FB1				CAN_F4R2_FB1_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 2 (`CANx_F4R2.FB2`) bit position @def CAN_F4R2_FB2_Pos */
#define CAN_F4R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 4 word 2 bit 2 (`CANx_F4R2.FB2`) bit mask @def CAN_F4R2_FB2_Msk */
#define CAN_F4R2_FB2_Msk			REG_BIT_MASK(CAN_F4R2_FB2_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 2 (`CANx_F4R2.FB2`) bit mask alias @def CAN_F4R2_FB2 */
#define CAN_F4R2_FB2				CAN_F4R2_FB2_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 3 (`CANx_F4R2.FB3`) bit position @def CAN_F4R2_FB3_Pos */
#define CAN_F4R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 4 word 2 bit 3 (`CANx_F4R2.FB3`) bit mask @def CAN_F4R2_FB3_Msk */
#define CAN_F4R2_FB3_Msk			REG_BIT_MASK(CAN_F4R2_FB3_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 3 (`CANx_F4R2.FB3`) bit mask alias @def CAN_F4R2_FB3 */
#define CAN_F4R2_FB3				CAN_F4R2_FB3_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 4 (`CANx_F4R2.FB4`) bit position @def CAN_F4R2_FB4_Pos */
#define CAN_F4R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 4 word 2 bit 4 (`CANx_F4R2.FB4`) bit mask @def CAN_F4R2_FB4_Msk */
#define CAN_F4R2_FB4_Msk			REG_BIT_MASK(CAN_F4R2_FB4_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 4 (`CANx_F4R2.FB4`) bit mask alias @def CAN_F4R2_FB4 */
#define CAN_F4R2_FB4				CAN_F4R2_FB4_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 5 (`CANx_F4R2.FB5`) bit position @def CAN_F4R2_FB5_Pos */
#define CAN_F4R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 4 word 2 bit 5 (`CANx_F4R2.FB5`) bit mask @def CAN_F4R2_FB5_Msk */
#define CAN_F4R2_FB5_Msk			REG_BIT_MASK(CAN_F4R2_FB5_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 5 (`CANx_F4R2.FB5`) bit mask alias @def CAN_F4R2_FB5 */
#define CAN_F4R2_FB5				CAN_F4R2_FB5_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 6 (`CANx_F4R2.FB6`) bit position @def CAN_F4R2_FB6_Pos */
#define CAN_F4R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 4 word 2 bit 6 (`CANx_F4R2.FB6`) bit mask @def CAN_F4R2_FB6_Msk */
#define CAN_F4R2_FB6_Msk			REG_BIT_MASK(CAN_F4R2_FB6_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 6 (`CANx_F4R2.FB6`) bit mask alias @def CAN_F4R2_FB6 */
#define CAN_F4R2_FB6				CAN_F4R2_FB6_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 7 (`CANx_F4R2.FB7`) bit position @def CAN_F4R2_FB7_Pos */
#define CAN_F4R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 4 word 2 bit 7 (`CANx_F4R2.FB7`) bit mask @def CAN_F4R2_FB7_Msk */
#define CAN_F4R2_FB7_Msk			REG_BIT_MASK(CAN_F4R2_FB7_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 7 (`CANx_F4R2.FB7`) bit mask alias @def CAN_F4R2_FB7 */
#define CAN_F4R2_FB7				CAN_F4R2_FB7_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 8 (`CANx_F4R2.FB8`) bit position @def CAN_F4R2_FB8_Pos */
#define CAN_F4R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 4 word 2 bit 8 (`CANx_F4R2.FB8`) bit mask @def CAN_F4R2_FB8_Msk */
#define CAN_F4R2_FB8_Msk			REG_BIT_MASK(CAN_F4R2_FB8_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 8 (`CANx_F4R2.FB8`) bit mask alias @def CAN_F4R2_FB8 */
#define CAN_F4R2_FB8				CAN_F4R2_FB8_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 9 (`CANx_F4R2.FB9`) bit position @def CAN_F4R2_FB9_Pos */
#define CAN_F4R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 4 word 2 bit 9 (`CANx_F4R2.FB9`) bit mask @def CAN_F4R2_FB9_Msk */
#define CAN_F4R2_FB9_Msk			REG_BIT_MASK(CAN_F4R2_FB9_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 9 (`CANx_F4R2.FB9`) bit mask alias @def CAN_F4R2_FB9 */
#define CAN_F4R2_FB9				CAN_F4R2_FB9_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 10 (`CANx_F4R2.FB10`) bit position @def CAN_F4R2_FB10_Pos */
#define CAN_F4R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 4 word 2 bit 10 (`CANx_F4R2.FB10`) bit mask @def CAN_F4R2_FB10_Msk */
#define CAN_F4R2_FB10_Msk			REG_BIT_MASK(CAN_F4R2_FB10_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 10 (`CANx_F4R2.FB10`) bit mask alias @def CAN_F4R2_FB10 */
#define CAN_F4R2_FB10				CAN_F4R2_FB10_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 11 (`CANx_F4R2.FB11`) bit position @def CAN_F4R2_FB11_Pos */
#define CAN_F4R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 4 word 2 bit 11 (`CANx_F4R2.FB11`) bit mask @def CAN_F4R2_FB11_Msk */
#define CAN_F4R2_FB11_Msk			REG_BIT_MASK(CAN_F4R2_FB11_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 11 (`CANx_F4R2.FB11`) bit mask alias @def CAN_F4R2_FB11 */
#define CAN_F4R2_FB11				CAN_F4R2_FB11_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 12 (`CANx_F4R2.FB12`) bit position @def CAN_F4R2_FB12_Pos */
#define CAN_F4R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 4 word 2 bit 12 (`CANx_F4R2.FB12`) bit mask @def CAN_F4R2_FB12_Msk */
#define CAN_F4R2_FB12_Msk			REG_BIT_MASK(CAN_F4R2_FB12_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 12 (`CANx_F4R2.FB12`) bit mask alias @def CAN_F4R2_FB12 */
#define CAN_F4R2_FB12				CAN_F4R2_FB12_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 13 (`CANx_F4R2.FB13`) bit position @def CAN_F4R2_FB13_Pos */
#define CAN_F4R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 4 word 2 bit 13 (`CANx_F4R2.FB13`) bit mask @def CAN_F4R2_FB13_Msk */
#define CAN_F4R2_FB13_Msk			REG_BIT_MASK(CAN_F4R2_FB13_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 13 (`CANx_F4R2.FB13`) bit mask alias @def CAN_F4R2_FB13 */
#define CAN_F4R2_FB13				CAN_F4R2_FB13_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 14 (`CANx_F4R2.FB14`) bit position @def CAN_F4R2_FB14_Pos */
#define CAN_F4R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 4 word 2 bit 14 (`CANx_F4R2.FB14`) bit mask @def CAN_F4R2_FB14_Msk */
#define CAN_F4R2_FB14_Msk			REG_BIT_MASK(CAN_F4R2_FB14_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 14 (`CANx_F4R2.FB14`) bit mask alias @def CAN_F4R2_FB14 */
#define CAN_F4R2_FB14				CAN_F4R2_FB14_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 15 (`CANx_F4R2.FB15`) bit position @def CAN_F4R2_FB15_Pos */
#define CAN_F4R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 4 word 2 bit 15 (`CANx_F4R2.FB15`) bit mask @def CAN_F4R2_FB15_Msk */
#define CAN_F4R2_FB15_Msk			REG_BIT_MASK(CAN_F4R2_FB15_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 15 (`CANx_F4R2.FB15`) bit mask alias @def CAN_F4R2_FB15 */
#define CAN_F4R2_FB15				CAN_F4R2_FB15_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 16 (`CANx_F4R2.FB16`) bit position @def CAN_F4R2_FB16_Pos */
#define CAN_F4R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 4 word 2 bit 16 (`CANx_F4R2.FB16`) bit mask @def CAN_F4R2_FB16_Msk */
#define CAN_F4R2_FB16_Msk			REG_BIT_MASK(CAN_F4R2_FB16_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 16 (`CANx_F4R2.FB16`) bit mask alias @def CAN_F4R2_FB16 */
#define CAN_F4R2_FB16				CAN_F4R2_FB16_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 17 (`CANx_F4R2.FB17`) bit position @def CAN_F4R2_FB17_Pos */
#define CAN_F4R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 4 word 2 bit 17 (`CANx_F4R2.FB17`) bit mask @def CAN_F4R2_FB17_Msk */
#define CAN_F4R2_FB17_Msk			REG_BIT_MASK(CAN_F4R2_FB17_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 17 (`CANx_F4R2.FB17`) bit mask alias @def CAN_F4R2_FB17 */
#define CAN_F4R2_FB17				CAN_F4R2_FB17_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 18 (`CANx_F4R2.FB18`) bit position @def CAN_F4R2_FB18_Pos */
#define CAN_F4R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 4 word 2 bit 18 (`CANx_F4R2.FB18`) bit mask @def CAN_F4R2_FB18_Msk */
#define CAN_F4R2_FB18_Msk			REG_BIT_MASK(CAN_F4R2_FB18_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 18 (`CANx_F4R2.FB18`) bit mask alias @def CAN_F4R2_FB18 */
#define CAN_F4R2_FB18				CAN_F4R2_FB18_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 19 (`CANx_F4R2.FB19`) bit position @def CAN_F4R2_FB19_Pos */
#define CAN_F4R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 4 word 2 bit 19 (`CANx_F4R2.FB19`) bit mask @def CAN_F4R2_FB19_Msk */
#define CAN_F4R2_FB19_Msk			REG_BIT_MASK(CAN_F4R2_FB19_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 19 (`CANx_F4R2.FB19`) bit mask alias @def CAN_F4R2_FB19 */
#define CAN_F4R2_FB19				CAN_F4R2_FB19_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 20 (`CANx_F4R2.FB20`) bit position @def CAN_F4R2_FB20_Pos */
#define CAN_F4R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 4 word 2 bit 20 (`CANx_F4R2.FB20`) bit mask @def CAN_F4R2_FB20_Msk */
#define CAN_F4R2_FB20_Msk			REG_BIT_MASK(CAN_F4R2_FB20_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 20 (`CANx_F4R2.FB20`) bit mask alias @def CAN_F4R2_FB20 */
#define CAN_F4R2_FB20				CAN_F4R2_FB20_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 21 (`CANx_F4R2.FB21`) bit position @def CAN_F4R2_FB21_Pos */
#define CAN_F4R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 4 word 2 bit 21 (`CANx_F4R2.FB21`) bit mask @def CAN_F4R2_FB21_Msk */
#define CAN_F4R2_FB21_Msk			REG_BIT_MASK(CAN_F4R2_FB21_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 21 (`CANx_F4R2.FB21`) bit mask alias @def CAN_F4R2_FB21 */
#define CAN_F4R2_FB21				CAN_F4R2_FB21_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 22 (`CANx_F4R2.FB22`) bit position @def CAN_F4R2_FB22_Pos */
#define CAN_F4R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 4 word 2 bit 22 (`CANx_F4R2.FB22`) bit mask @def CAN_F4R2_FB22_Msk */
#define CAN_F4R2_FB22_Msk			REG_BIT_MASK(CAN_F4R2_FB22_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 22 (`CANx_F4R2.FB22`) bit mask alias @def CAN_F4R2_FB22 */
#define CAN_F4R2_FB22				CAN_F4R2_FB22_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 23 (`CANx_F4R2.FB23`) bit position @def CAN_F4R2_FB23_Pos */
#define CAN_F4R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 4 word 2 bit 23 (`CANx_F4R2.FB23`) bit mask @def CAN_F4R2_FB23_Msk */
#define CAN_F4R2_FB23_Msk			REG_BIT_MASK(CAN_F4R2_FB23_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 23 (`CANx_F4R2.FB23`) bit mask alias @def CAN_F4R2_FB23 */
#define CAN_F4R2_FB23				CAN_F4R2_FB23_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 24 (`CANx_F4R2.FB24`) bit position @def CAN_F4R2_FB24_Pos */
#define CAN_F4R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 4 word 2 bit 24 (`CANx_F4R2.FB24`) bit mask @def CAN_F4R2_FB24_Msk */
#define CAN_F4R2_FB24_Msk			REG_BIT_MASK(CAN_F4R2_FB24_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 24 (`CANx_F4R2.FB24`) bit mask alias @def CAN_F4R2_FB24 */
#define CAN_F4R2_FB24				CAN_F4R2_FB24_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 25 (`CANx_F4R2.FB25`) bit position @def CAN_F4R2_FB25_Pos */
#define CAN_F4R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 4 word 2 bit 25 (`CANx_F4R2.FB25`) bit mask @def CAN_F4R2_FB25_Msk */
#define CAN_F4R2_FB25_Msk			REG_BIT_MASK(CAN_F4R2_FB25_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 25 (`CANx_F4R2.FB25`) bit mask alias @def CAN_F4R2_FB25 */
#define CAN_F4R2_FB25				CAN_F4R2_FB25_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 26 (`CANx_F4R2.FB26`) bit position @def CAN_F4R2_FB26_Pos */
#define CAN_F4R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 4 word 2 bit 26 (`CANx_F4R2.FB26`) bit mask @def CAN_F4R2_FB26_Msk */
#define CAN_F4R2_FB26_Msk			REG_BIT_MASK(CAN_F4R2_FB26_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 26 (`CANx_F4R2.FB26`) bit mask alias @def CAN_F4R2_FB26 */
#define CAN_F4R2_FB26				CAN_F4R2_FB26_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 27 (`CANx_F4R2.FB27`) bit position @def CAN_F4R2_FB27_Pos */
#define CAN_F4R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 4 word 2 bit 27 (`CANx_F4R2.FB27`) bit mask @def CAN_F4R2_FB27_Msk */
#define CAN_F4R2_FB27_Msk			REG_BIT_MASK(CAN_F4R2_FB27_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 27 (`CANx_F4R2.FB27`) bit mask alias @def CAN_F4R2_FB27 */
#define CAN_F4R2_FB27				CAN_F4R2_FB27_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 28 (`CANx_F4R2.FB28`) bit position @def CAN_F4R2_FB28_Pos */
#define CAN_F4R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 4 word 2 bit 28 (`CANx_F4R2.FB28`) bit mask @def CAN_F4R2_FB28_Msk */
#define CAN_F4R2_FB28_Msk			REG_BIT_MASK(CAN_F4R2_FB28_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 28 (`CANx_F4R2.FB28`) bit mask alias @def CAN_F4R2_FB28 */
#define CAN_F4R2_FB28				CAN_F4R2_FB28_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 29 (`CANx_F4R2.FB29`) bit position @def CAN_F4R2_FB29_Pos */
#define CAN_F4R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 4 word 2 bit 29 (`CANx_F4R2.FB29`) bit mask @def CAN_F4R2_FB29_Msk */
#define CAN_F4R2_FB29_Msk			REG_BIT_MASK(CAN_F4R2_FB29_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 29 (`CANx_F4R2.FB29`) bit mask alias @def CAN_F4R2_FB29 */
#define CAN_F4R2_FB29				CAN_F4R2_FB29_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 30 (`CANx_F4R2.FB30`) bit position @def CAN_F4R2_FB30_Pos */
#define CAN_F4R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 4 word 2 bit 30 (`CANx_F4R2.FB30`) bit mask @def CAN_F4R2_FB30_Msk */
#define CAN_F4R2_FB30_Msk			REG_BIT_MASK(CAN_F4R2_FB30_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 30 (`CANx_F4R2.FB30`) bit mask alias @def CAN_F4R2_FB30 */
#define CAN_F4R2_FB30				CAN_F4R2_FB30_Msk

/** @brief Acceptance-filter bank 4 word 2 bit 31 (`CANx_F4R2.FB31`) bit position @def CAN_F4R2_FB31_Pos */
#define CAN_F4R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 4 word 2 bit 31 (`CANx_F4R2.FB31`) bit mask @def CAN_F4R2_FB31_Msk */
#define CAN_F4R2_FB31_Msk			REG_BIT_MASK(CAN_F4R2_FB31_Pos)
/** @brief Acceptance-filter bank 4 word 2 bit 31 (`CANx_F4R2.FB31`) bit mask alias @def CAN_F4R2_FB31 */
#define CAN_F4R2_FB31				CAN_F4R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F5R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 5 word 2 bit 0 (`CANx_F5R2.FB0`) bit position @def CAN_F5R2_FB0_Pos */
#define CAN_F5R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 5 word 2 bit 0 (`CANx_F5R2.FB0`) bit mask @def CAN_F5R2_FB0_Msk */
#define CAN_F5R2_FB0_Msk			REG_BIT_MASK(CAN_F5R2_FB0_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 0 (`CANx_F5R2.FB0`) bit mask alias @def CAN_F5R2_FB0 */
#define CAN_F5R2_FB0				CAN_F5R2_FB0_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 1 (`CANx_F5R2.FB1`) bit position @def CAN_F5R2_FB1_Pos */
#define CAN_F5R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 5 word 2 bit 1 (`CANx_F5R2.FB1`) bit mask @def CAN_F5R2_FB1_Msk */
#define CAN_F5R2_FB1_Msk			REG_BIT_MASK(CAN_F5R2_FB1_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 1 (`CANx_F5R2.FB1`) bit mask alias @def CAN_F5R2_FB1 */
#define CAN_F5R2_FB1				CAN_F5R2_FB1_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 2 (`CANx_F5R2.FB2`) bit position @def CAN_F5R2_FB2_Pos */
#define CAN_F5R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 5 word 2 bit 2 (`CANx_F5R2.FB2`) bit mask @def CAN_F5R2_FB2_Msk */
#define CAN_F5R2_FB2_Msk			REG_BIT_MASK(CAN_F5R2_FB2_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 2 (`CANx_F5R2.FB2`) bit mask alias @def CAN_F5R2_FB2 */
#define CAN_F5R2_FB2				CAN_F5R2_FB2_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 3 (`CANx_F5R2.FB3`) bit position @def CAN_F5R2_FB3_Pos */
#define CAN_F5R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 5 word 2 bit 3 (`CANx_F5R2.FB3`) bit mask @def CAN_F5R2_FB3_Msk */
#define CAN_F5R2_FB3_Msk			REG_BIT_MASK(CAN_F5R2_FB3_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 3 (`CANx_F5R2.FB3`) bit mask alias @def CAN_F5R2_FB3 */
#define CAN_F5R2_FB3				CAN_F5R2_FB3_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 4 (`CANx_F5R2.FB4`) bit position @def CAN_F5R2_FB4_Pos */
#define CAN_F5R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 5 word 2 bit 4 (`CANx_F5R2.FB4`) bit mask @def CAN_F5R2_FB4_Msk */
#define CAN_F5R2_FB4_Msk			REG_BIT_MASK(CAN_F5R2_FB4_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 4 (`CANx_F5R2.FB4`) bit mask alias @def CAN_F5R2_FB4 */
#define CAN_F5R2_FB4				CAN_F5R2_FB4_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 5 (`CANx_F5R2.FB5`) bit position @def CAN_F5R2_FB5_Pos */
#define CAN_F5R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 5 word 2 bit 5 (`CANx_F5R2.FB5`) bit mask @def CAN_F5R2_FB5_Msk */
#define CAN_F5R2_FB5_Msk			REG_BIT_MASK(CAN_F5R2_FB5_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 5 (`CANx_F5R2.FB5`) bit mask alias @def CAN_F5R2_FB5 */
#define CAN_F5R2_FB5				CAN_F5R2_FB5_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 6 (`CANx_F5R2.FB6`) bit position @def CAN_F5R2_FB6_Pos */
#define CAN_F5R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 5 word 2 bit 6 (`CANx_F5R2.FB6`) bit mask @def CAN_F5R2_FB6_Msk */
#define CAN_F5R2_FB6_Msk			REG_BIT_MASK(CAN_F5R2_FB6_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 6 (`CANx_F5R2.FB6`) bit mask alias @def CAN_F5R2_FB6 */
#define CAN_F5R2_FB6				CAN_F5R2_FB6_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 7 (`CANx_F5R2.FB7`) bit position @def CAN_F5R2_FB7_Pos */
#define CAN_F5R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 5 word 2 bit 7 (`CANx_F5R2.FB7`) bit mask @def CAN_F5R2_FB7_Msk */
#define CAN_F5R2_FB7_Msk			REG_BIT_MASK(CAN_F5R2_FB7_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 7 (`CANx_F5R2.FB7`) bit mask alias @def CAN_F5R2_FB7 */
#define CAN_F5R2_FB7				CAN_F5R2_FB7_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 8 (`CANx_F5R2.FB8`) bit position @def CAN_F5R2_FB8_Pos */
#define CAN_F5R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 5 word 2 bit 8 (`CANx_F5R2.FB8`) bit mask @def CAN_F5R2_FB8_Msk */
#define CAN_F5R2_FB8_Msk			REG_BIT_MASK(CAN_F5R2_FB8_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 8 (`CANx_F5R2.FB8`) bit mask alias @def CAN_F5R2_FB8 */
#define CAN_F5R2_FB8				CAN_F5R2_FB8_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 9 (`CANx_F5R2.FB9`) bit position @def CAN_F5R2_FB9_Pos */
#define CAN_F5R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 5 word 2 bit 9 (`CANx_F5R2.FB9`) bit mask @def CAN_F5R2_FB9_Msk */
#define CAN_F5R2_FB9_Msk			REG_BIT_MASK(CAN_F5R2_FB9_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 9 (`CANx_F5R2.FB9`) bit mask alias @def CAN_F5R2_FB9 */
#define CAN_F5R2_FB9				CAN_F5R2_FB9_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 10 (`CANx_F5R2.FB10`) bit position @def CAN_F5R2_FB10_Pos */
#define CAN_F5R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 5 word 2 bit 10 (`CANx_F5R2.FB10`) bit mask @def CAN_F5R2_FB10_Msk */
#define CAN_F5R2_FB10_Msk			REG_BIT_MASK(CAN_F5R2_FB10_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 10 (`CANx_F5R2.FB10`) bit mask alias @def CAN_F5R2_FB10 */
#define CAN_F5R2_FB10				CAN_F5R2_FB10_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 11 (`CANx_F5R2.FB11`) bit position @def CAN_F5R2_FB11_Pos */
#define CAN_F5R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 5 word 2 bit 11 (`CANx_F5R2.FB11`) bit mask @def CAN_F5R2_FB11_Msk */
#define CAN_F5R2_FB11_Msk			REG_BIT_MASK(CAN_F5R2_FB11_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 11 (`CANx_F5R2.FB11`) bit mask alias @def CAN_F5R2_FB11 */
#define CAN_F5R2_FB11				CAN_F5R2_FB11_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 12 (`CANx_F5R2.FB12`) bit position @def CAN_F5R2_FB12_Pos */
#define CAN_F5R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 5 word 2 bit 12 (`CANx_F5R2.FB12`) bit mask @def CAN_F5R2_FB12_Msk */
#define CAN_F5R2_FB12_Msk			REG_BIT_MASK(CAN_F5R2_FB12_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 12 (`CANx_F5R2.FB12`) bit mask alias @def CAN_F5R2_FB12 */
#define CAN_F5R2_FB12				CAN_F5R2_FB12_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 13 (`CANx_F5R2.FB13`) bit position @def CAN_F5R2_FB13_Pos */
#define CAN_F5R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 5 word 2 bit 13 (`CANx_F5R2.FB13`) bit mask @def CAN_F5R2_FB13_Msk */
#define CAN_F5R2_FB13_Msk			REG_BIT_MASK(CAN_F5R2_FB13_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 13 (`CANx_F5R2.FB13`) bit mask alias @def CAN_F5R2_FB13 */
#define CAN_F5R2_FB13				CAN_F5R2_FB13_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 14 (`CANx_F5R2.FB14`) bit position @def CAN_F5R2_FB14_Pos */
#define CAN_F5R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 5 word 2 bit 14 (`CANx_F5R2.FB14`) bit mask @def CAN_F5R2_FB14_Msk */
#define CAN_F5R2_FB14_Msk			REG_BIT_MASK(CAN_F5R2_FB14_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 14 (`CANx_F5R2.FB14`) bit mask alias @def CAN_F5R2_FB14 */
#define CAN_F5R2_FB14				CAN_F5R2_FB14_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 15 (`CANx_F5R2.FB15`) bit position @def CAN_F5R2_FB15_Pos */
#define CAN_F5R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 5 word 2 bit 15 (`CANx_F5R2.FB15`) bit mask @def CAN_F5R2_FB15_Msk */
#define CAN_F5R2_FB15_Msk			REG_BIT_MASK(CAN_F5R2_FB15_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 15 (`CANx_F5R2.FB15`) bit mask alias @def CAN_F5R2_FB15 */
#define CAN_F5R2_FB15				CAN_F5R2_FB15_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 16 (`CANx_F5R2.FB16`) bit position @def CAN_F5R2_FB16_Pos */
#define CAN_F5R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 5 word 2 bit 16 (`CANx_F5R2.FB16`) bit mask @def CAN_F5R2_FB16_Msk */
#define CAN_F5R2_FB16_Msk			REG_BIT_MASK(CAN_F5R2_FB16_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 16 (`CANx_F5R2.FB16`) bit mask alias @def CAN_F5R2_FB16 */
#define CAN_F5R2_FB16				CAN_F5R2_FB16_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 17 (`CANx_F5R2.FB17`) bit position @def CAN_F5R2_FB17_Pos */
#define CAN_F5R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 5 word 2 bit 17 (`CANx_F5R2.FB17`) bit mask @def CAN_F5R2_FB17_Msk */
#define CAN_F5R2_FB17_Msk			REG_BIT_MASK(CAN_F5R2_FB17_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 17 (`CANx_F5R2.FB17`) bit mask alias @def CAN_F5R2_FB17 */
#define CAN_F5R2_FB17				CAN_F5R2_FB17_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 18 (`CANx_F5R2.FB18`) bit position @def CAN_F5R2_FB18_Pos */
#define CAN_F5R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 5 word 2 bit 18 (`CANx_F5R2.FB18`) bit mask @def CAN_F5R2_FB18_Msk */
#define CAN_F5R2_FB18_Msk			REG_BIT_MASK(CAN_F5R2_FB18_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 18 (`CANx_F5R2.FB18`) bit mask alias @def CAN_F5R2_FB18 */
#define CAN_F5R2_FB18				CAN_F5R2_FB18_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 19 (`CANx_F5R2.FB19`) bit position @def CAN_F5R2_FB19_Pos */
#define CAN_F5R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 5 word 2 bit 19 (`CANx_F5R2.FB19`) bit mask @def CAN_F5R2_FB19_Msk */
#define CAN_F5R2_FB19_Msk			REG_BIT_MASK(CAN_F5R2_FB19_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 19 (`CANx_F5R2.FB19`) bit mask alias @def CAN_F5R2_FB19 */
#define CAN_F5R2_FB19				CAN_F5R2_FB19_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 20 (`CANx_F5R2.FB20`) bit position @def CAN_F5R2_FB20_Pos */
#define CAN_F5R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 5 word 2 bit 20 (`CANx_F5R2.FB20`) bit mask @def CAN_F5R2_FB20_Msk */
#define CAN_F5R2_FB20_Msk			REG_BIT_MASK(CAN_F5R2_FB20_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 20 (`CANx_F5R2.FB20`) bit mask alias @def CAN_F5R2_FB20 */
#define CAN_F5R2_FB20				CAN_F5R2_FB20_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 21 (`CANx_F5R2.FB21`) bit position @def CAN_F5R2_FB21_Pos */
#define CAN_F5R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 5 word 2 bit 21 (`CANx_F5R2.FB21`) bit mask @def CAN_F5R2_FB21_Msk */
#define CAN_F5R2_FB21_Msk			REG_BIT_MASK(CAN_F5R2_FB21_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 21 (`CANx_F5R2.FB21`) bit mask alias @def CAN_F5R2_FB21 */
#define CAN_F5R2_FB21				CAN_F5R2_FB21_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 22 (`CANx_F5R2.FB22`) bit position @def CAN_F5R2_FB22_Pos */
#define CAN_F5R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 5 word 2 bit 22 (`CANx_F5R2.FB22`) bit mask @def CAN_F5R2_FB22_Msk */
#define CAN_F5R2_FB22_Msk			REG_BIT_MASK(CAN_F5R2_FB22_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 22 (`CANx_F5R2.FB22`) bit mask alias @def CAN_F5R2_FB22 */
#define CAN_F5R2_FB22				CAN_F5R2_FB22_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 23 (`CANx_F5R2.FB23`) bit position @def CAN_F5R2_FB23_Pos */
#define CAN_F5R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 5 word 2 bit 23 (`CANx_F5R2.FB23`) bit mask @def CAN_F5R2_FB23_Msk */
#define CAN_F5R2_FB23_Msk			REG_BIT_MASK(CAN_F5R2_FB23_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 23 (`CANx_F5R2.FB23`) bit mask alias @def CAN_F5R2_FB23 */
#define CAN_F5R2_FB23				CAN_F5R2_FB23_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 24 (`CANx_F5R2.FB24`) bit position @def CAN_F5R2_FB24_Pos */
#define CAN_F5R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 5 word 2 bit 24 (`CANx_F5R2.FB24`) bit mask @def CAN_F5R2_FB24_Msk */
#define CAN_F5R2_FB24_Msk			REG_BIT_MASK(CAN_F5R2_FB24_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 24 (`CANx_F5R2.FB24`) bit mask alias @def CAN_F5R2_FB24 */
#define CAN_F5R2_FB24				CAN_F5R2_FB24_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 25 (`CANx_F5R2.FB25`) bit position @def CAN_F5R2_FB25_Pos */
#define CAN_F5R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 5 word 2 bit 25 (`CANx_F5R2.FB25`) bit mask @def CAN_F5R2_FB25_Msk */
#define CAN_F5R2_FB25_Msk			REG_BIT_MASK(CAN_F5R2_FB25_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 25 (`CANx_F5R2.FB25`) bit mask alias @def CAN_F5R2_FB25 */
#define CAN_F5R2_FB25				CAN_F5R2_FB25_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 26 (`CANx_F5R2.FB26`) bit position @def CAN_F5R2_FB26_Pos */
#define CAN_F5R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 5 word 2 bit 26 (`CANx_F5R2.FB26`) bit mask @def CAN_F5R2_FB26_Msk */
#define CAN_F5R2_FB26_Msk			REG_BIT_MASK(CAN_F5R2_FB26_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 26 (`CANx_F5R2.FB26`) bit mask alias @def CAN_F5R2_FB26 */
#define CAN_F5R2_FB26				CAN_F5R2_FB26_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 27 (`CANx_F5R2.FB27`) bit position @def CAN_F5R2_FB27_Pos */
#define CAN_F5R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 5 word 2 bit 27 (`CANx_F5R2.FB27`) bit mask @def CAN_F5R2_FB27_Msk */
#define CAN_F5R2_FB27_Msk			REG_BIT_MASK(CAN_F5R2_FB27_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 27 (`CANx_F5R2.FB27`) bit mask alias @def CAN_F5R2_FB27 */
#define CAN_F5R2_FB27				CAN_F5R2_FB27_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 28 (`CANx_F5R2.FB28`) bit position @def CAN_F5R2_FB28_Pos */
#define CAN_F5R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 5 word 2 bit 28 (`CANx_F5R2.FB28`) bit mask @def CAN_F5R2_FB28_Msk */
#define CAN_F5R2_FB28_Msk			REG_BIT_MASK(CAN_F5R2_FB28_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 28 (`CANx_F5R2.FB28`) bit mask alias @def CAN_F5R2_FB28 */
#define CAN_F5R2_FB28				CAN_F5R2_FB28_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 29 (`CANx_F5R2.FB29`) bit position @def CAN_F5R2_FB29_Pos */
#define CAN_F5R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 5 word 2 bit 29 (`CANx_F5R2.FB29`) bit mask @def CAN_F5R2_FB29_Msk */
#define CAN_F5R2_FB29_Msk			REG_BIT_MASK(CAN_F5R2_FB29_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 29 (`CANx_F5R2.FB29`) bit mask alias @def CAN_F5R2_FB29 */
#define CAN_F5R2_FB29				CAN_F5R2_FB29_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 30 (`CANx_F5R2.FB30`) bit position @def CAN_F5R2_FB30_Pos */
#define CAN_F5R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 5 word 2 bit 30 (`CANx_F5R2.FB30`) bit mask @def CAN_F5R2_FB30_Msk */
#define CAN_F5R2_FB30_Msk			REG_BIT_MASK(CAN_F5R2_FB30_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 30 (`CANx_F5R2.FB30`) bit mask alias @def CAN_F5R2_FB30 */
#define CAN_F5R2_FB30				CAN_F5R2_FB30_Msk

/** @brief Acceptance-filter bank 5 word 2 bit 31 (`CANx_F5R2.FB31`) bit position @def CAN_F5R2_FB31_Pos */
#define CAN_F5R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 5 word 2 bit 31 (`CANx_F5R2.FB31`) bit mask @def CAN_F5R2_FB31_Msk */
#define CAN_F5R2_FB31_Msk			REG_BIT_MASK(CAN_F5R2_FB31_Pos)
/** @brief Acceptance-filter bank 5 word 2 bit 31 (`CANx_F5R2.FB31`) bit mask alias @def CAN_F5R2_FB31 */
#define CAN_F5R2_FB31				CAN_F5R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F6R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 6 word 2 bit 0 (`CANx_F6R2.FB0`) bit position @def CAN_F6R2_FB0_Pos */
#define CAN_F6R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 6 word 2 bit 0 (`CANx_F6R2.FB0`) bit mask @def CAN_F6R2_FB0_Msk */
#define CAN_F6R2_FB0_Msk			REG_BIT_MASK(CAN_F6R2_FB0_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 0 (`CANx_F6R2.FB0`) bit mask alias @def CAN_F6R2_FB0 */
#define CAN_F6R2_FB0				CAN_F6R2_FB0_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 1 (`CANx_F6R2.FB1`) bit position @def CAN_F6R2_FB1_Pos */
#define CAN_F6R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 6 word 2 bit 1 (`CANx_F6R2.FB1`) bit mask @def CAN_F6R2_FB1_Msk */
#define CAN_F6R2_FB1_Msk			REG_BIT_MASK(CAN_F6R2_FB1_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 1 (`CANx_F6R2.FB1`) bit mask alias @def CAN_F6R2_FB1 */
#define CAN_F6R2_FB1				CAN_F6R2_FB1_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 2 (`CANx_F6R2.FB2`) bit position @def CAN_F6R2_FB2_Pos */
#define CAN_F6R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 6 word 2 bit 2 (`CANx_F6R2.FB2`) bit mask @def CAN_F6R2_FB2_Msk */
#define CAN_F6R2_FB2_Msk			REG_BIT_MASK(CAN_F6R2_FB2_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 2 (`CANx_F6R2.FB2`) bit mask alias @def CAN_F6R2_FB2 */
#define CAN_F6R2_FB2				CAN_F6R2_FB2_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 3 (`CANx_F6R2.FB3`) bit position @def CAN_F6R2_FB3_Pos */
#define CAN_F6R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 6 word 2 bit 3 (`CANx_F6R2.FB3`) bit mask @def CAN_F6R2_FB3_Msk */
#define CAN_F6R2_FB3_Msk			REG_BIT_MASK(CAN_F6R2_FB3_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 3 (`CANx_F6R2.FB3`) bit mask alias @def CAN_F6R2_FB3 */
#define CAN_F6R2_FB3				CAN_F6R2_FB3_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 4 (`CANx_F6R2.FB4`) bit position @def CAN_F6R2_FB4_Pos */
#define CAN_F6R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 6 word 2 bit 4 (`CANx_F6R2.FB4`) bit mask @def CAN_F6R2_FB4_Msk */
#define CAN_F6R2_FB4_Msk			REG_BIT_MASK(CAN_F6R2_FB4_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 4 (`CANx_F6R2.FB4`) bit mask alias @def CAN_F6R2_FB4 */
#define CAN_F6R2_FB4				CAN_F6R2_FB4_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 5 (`CANx_F6R2.FB5`) bit position @def CAN_F6R2_FB5_Pos */
#define CAN_F6R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 6 word 2 bit 5 (`CANx_F6R2.FB5`) bit mask @def CAN_F6R2_FB5_Msk */
#define CAN_F6R2_FB5_Msk			REG_BIT_MASK(CAN_F6R2_FB5_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 5 (`CANx_F6R2.FB5`) bit mask alias @def CAN_F6R2_FB5 */
#define CAN_F6R2_FB5				CAN_F6R2_FB5_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 6 (`CANx_F6R2.FB6`) bit position @def CAN_F6R2_FB6_Pos */
#define CAN_F6R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 6 word 2 bit 6 (`CANx_F6R2.FB6`) bit mask @def CAN_F6R2_FB6_Msk */
#define CAN_F6R2_FB6_Msk			REG_BIT_MASK(CAN_F6R2_FB6_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 6 (`CANx_F6R2.FB6`) bit mask alias @def CAN_F6R2_FB6 */
#define CAN_F6R2_FB6				CAN_F6R2_FB6_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 7 (`CANx_F6R2.FB7`) bit position @def CAN_F6R2_FB7_Pos */
#define CAN_F6R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 6 word 2 bit 7 (`CANx_F6R2.FB7`) bit mask @def CAN_F6R2_FB7_Msk */
#define CAN_F6R2_FB7_Msk			REG_BIT_MASK(CAN_F6R2_FB7_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 7 (`CANx_F6R2.FB7`) bit mask alias @def CAN_F6R2_FB7 */
#define CAN_F6R2_FB7				CAN_F6R2_FB7_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 8 (`CANx_F6R2.FB8`) bit position @def CAN_F6R2_FB8_Pos */
#define CAN_F6R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 6 word 2 bit 8 (`CANx_F6R2.FB8`) bit mask @def CAN_F6R2_FB8_Msk */
#define CAN_F6R2_FB8_Msk			REG_BIT_MASK(CAN_F6R2_FB8_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 8 (`CANx_F6R2.FB8`) bit mask alias @def CAN_F6R2_FB8 */
#define CAN_F6R2_FB8				CAN_F6R2_FB8_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 9 (`CANx_F6R2.FB9`) bit position @def CAN_F6R2_FB9_Pos */
#define CAN_F6R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 6 word 2 bit 9 (`CANx_F6R2.FB9`) bit mask @def CAN_F6R2_FB9_Msk */
#define CAN_F6R2_FB9_Msk			REG_BIT_MASK(CAN_F6R2_FB9_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 9 (`CANx_F6R2.FB9`) bit mask alias @def CAN_F6R2_FB9 */
#define CAN_F6R2_FB9				CAN_F6R2_FB9_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 10 (`CANx_F6R2.FB10`) bit position @def CAN_F6R2_FB10_Pos */
#define CAN_F6R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 6 word 2 bit 10 (`CANx_F6R2.FB10`) bit mask @def CAN_F6R2_FB10_Msk */
#define CAN_F6R2_FB10_Msk			REG_BIT_MASK(CAN_F6R2_FB10_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 10 (`CANx_F6R2.FB10`) bit mask alias @def CAN_F6R2_FB10 */
#define CAN_F6R2_FB10				CAN_F6R2_FB10_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 11 (`CANx_F6R2.FB11`) bit position @def CAN_F6R2_FB11_Pos */
#define CAN_F6R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 6 word 2 bit 11 (`CANx_F6R2.FB11`) bit mask @def CAN_F6R2_FB11_Msk */
#define CAN_F6R2_FB11_Msk			REG_BIT_MASK(CAN_F6R2_FB11_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 11 (`CANx_F6R2.FB11`) bit mask alias @def CAN_F6R2_FB11 */
#define CAN_F6R2_FB11				CAN_F6R2_FB11_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 12 (`CANx_F6R2.FB12`) bit position @def CAN_F6R2_FB12_Pos */
#define CAN_F6R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 6 word 2 bit 12 (`CANx_F6R2.FB12`) bit mask @def CAN_F6R2_FB12_Msk */
#define CAN_F6R2_FB12_Msk			REG_BIT_MASK(CAN_F6R2_FB12_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 12 (`CANx_F6R2.FB12`) bit mask alias @def CAN_F6R2_FB12 */
#define CAN_F6R2_FB12				CAN_F6R2_FB12_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 13 (`CANx_F6R2.FB13`) bit position @def CAN_F6R2_FB13_Pos */
#define CAN_F6R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 6 word 2 bit 13 (`CANx_F6R2.FB13`) bit mask @def CAN_F6R2_FB13_Msk */
#define CAN_F6R2_FB13_Msk			REG_BIT_MASK(CAN_F6R2_FB13_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 13 (`CANx_F6R2.FB13`) bit mask alias @def CAN_F6R2_FB13 */
#define CAN_F6R2_FB13				CAN_F6R2_FB13_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 14 (`CANx_F6R2.FB14`) bit position @def CAN_F6R2_FB14_Pos */
#define CAN_F6R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 6 word 2 bit 14 (`CANx_F6R2.FB14`) bit mask @def CAN_F6R2_FB14_Msk */
#define CAN_F6R2_FB14_Msk			REG_BIT_MASK(CAN_F6R2_FB14_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 14 (`CANx_F6R2.FB14`) bit mask alias @def CAN_F6R2_FB14 */
#define CAN_F6R2_FB14				CAN_F6R2_FB14_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 15 (`CANx_F6R2.FB15`) bit position @def CAN_F6R2_FB15_Pos */
#define CAN_F6R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 6 word 2 bit 15 (`CANx_F6R2.FB15`) bit mask @def CAN_F6R2_FB15_Msk */
#define CAN_F6R2_FB15_Msk			REG_BIT_MASK(CAN_F6R2_FB15_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 15 (`CANx_F6R2.FB15`) bit mask alias @def CAN_F6R2_FB15 */
#define CAN_F6R2_FB15				CAN_F6R2_FB15_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 16 (`CANx_F6R2.FB16`) bit position @def CAN_F6R2_FB16_Pos */
#define CAN_F6R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 6 word 2 bit 16 (`CANx_F6R2.FB16`) bit mask @def CAN_F6R2_FB16_Msk */
#define CAN_F6R2_FB16_Msk			REG_BIT_MASK(CAN_F6R2_FB16_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 16 (`CANx_F6R2.FB16`) bit mask alias @def CAN_F6R2_FB16 */
#define CAN_F6R2_FB16				CAN_F6R2_FB16_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 17 (`CANx_F6R2.FB17`) bit position @def CAN_F6R2_FB17_Pos */
#define CAN_F6R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 6 word 2 bit 17 (`CANx_F6R2.FB17`) bit mask @def CAN_F6R2_FB17_Msk */
#define CAN_F6R2_FB17_Msk			REG_BIT_MASK(CAN_F6R2_FB17_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 17 (`CANx_F6R2.FB17`) bit mask alias @def CAN_F6R2_FB17 */
#define CAN_F6R2_FB17				CAN_F6R2_FB17_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 18 (`CANx_F6R2.FB18`) bit position @def CAN_F6R2_FB18_Pos */
#define CAN_F6R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 6 word 2 bit 18 (`CANx_F6R2.FB18`) bit mask @def CAN_F6R2_FB18_Msk */
#define CAN_F6R2_FB18_Msk			REG_BIT_MASK(CAN_F6R2_FB18_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 18 (`CANx_F6R2.FB18`) bit mask alias @def CAN_F6R2_FB18 */
#define CAN_F6R2_FB18				CAN_F6R2_FB18_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 19 (`CANx_F6R2.FB19`) bit position @def CAN_F6R2_FB19_Pos */
#define CAN_F6R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 6 word 2 bit 19 (`CANx_F6R2.FB19`) bit mask @def CAN_F6R2_FB19_Msk */
#define CAN_F6R2_FB19_Msk			REG_BIT_MASK(CAN_F6R2_FB19_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 19 (`CANx_F6R2.FB19`) bit mask alias @def CAN_F6R2_FB19 */
#define CAN_F6R2_FB19				CAN_F6R2_FB19_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 20 (`CANx_F6R2.FB20`) bit position @def CAN_F6R2_FB20_Pos */
#define CAN_F6R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 6 word 2 bit 20 (`CANx_F6R2.FB20`) bit mask @def CAN_F6R2_FB20_Msk */
#define CAN_F6R2_FB20_Msk			REG_BIT_MASK(CAN_F6R2_FB20_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 20 (`CANx_F6R2.FB20`) bit mask alias @def CAN_F6R2_FB20 */
#define CAN_F6R2_FB20				CAN_F6R2_FB20_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 21 (`CANx_F6R2.FB21`) bit position @def CAN_F6R2_FB21_Pos */
#define CAN_F6R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 6 word 2 bit 21 (`CANx_F6R2.FB21`) bit mask @def CAN_F6R2_FB21_Msk */
#define CAN_F6R2_FB21_Msk			REG_BIT_MASK(CAN_F6R2_FB21_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 21 (`CANx_F6R2.FB21`) bit mask alias @def CAN_F6R2_FB21 */
#define CAN_F6R2_FB21				CAN_F6R2_FB21_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 22 (`CANx_F6R2.FB22`) bit position @def CAN_F6R2_FB22_Pos */
#define CAN_F6R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 6 word 2 bit 22 (`CANx_F6R2.FB22`) bit mask @def CAN_F6R2_FB22_Msk */
#define CAN_F6R2_FB22_Msk			REG_BIT_MASK(CAN_F6R2_FB22_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 22 (`CANx_F6R2.FB22`) bit mask alias @def CAN_F6R2_FB22 */
#define CAN_F6R2_FB22				CAN_F6R2_FB22_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 23 (`CANx_F6R2.FB23`) bit position @def CAN_F6R2_FB23_Pos */
#define CAN_F6R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 6 word 2 bit 23 (`CANx_F6R2.FB23`) bit mask @def CAN_F6R2_FB23_Msk */
#define CAN_F6R2_FB23_Msk			REG_BIT_MASK(CAN_F6R2_FB23_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 23 (`CANx_F6R2.FB23`) bit mask alias @def CAN_F6R2_FB23 */
#define CAN_F6R2_FB23				CAN_F6R2_FB23_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 24 (`CANx_F6R2.FB24`) bit position @def CAN_F6R2_FB24_Pos */
#define CAN_F6R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 6 word 2 bit 24 (`CANx_F6R2.FB24`) bit mask @def CAN_F6R2_FB24_Msk */
#define CAN_F6R2_FB24_Msk			REG_BIT_MASK(CAN_F6R2_FB24_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 24 (`CANx_F6R2.FB24`) bit mask alias @def CAN_F6R2_FB24 */
#define CAN_F6R2_FB24				CAN_F6R2_FB24_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 25 (`CANx_F6R2.FB25`) bit position @def CAN_F6R2_FB25_Pos */
#define CAN_F6R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 6 word 2 bit 25 (`CANx_F6R2.FB25`) bit mask @def CAN_F6R2_FB25_Msk */
#define CAN_F6R2_FB25_Msk			REG_BIT_MASK(CAN_F6R2_FB25_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 25 (`CANx_F6R2.FB25`) bit mask alias @def CAN_F6R2_FB25 */
#define CAN_F6R2_FB25				CAN_F6R2_FB25_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 26 (`CANx_F6R2.FB26`) bit position @def CAN_F6R2_FB26_Pos */
#define CAN_F6R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 6 word 2 bit 26 (`CANx_F6R2.FB26`) bit mask @def CAN_F6R2_FB26_Msk */
#define CAN_F6R2_FB26_Msk			REG_BIT_MASK(CAN_F6R2_FB26_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 26 (`CANx_F6R2.FB26`) bit mask alias @def CAN_F6R2_FB26 */
#define CAN_F6R2_FB26				CAN_F6R2_FB26_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 27 (`CANx_F6R2.FB27`) bit position @def CAN_F6R2_FB27_Pos */
#define CAN_F6R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 6 word 2 bit 27 (`CANx_F6R2.FB27`) bit mask @def CAN_F6R2_FB27_Msk */
#define CAN_F6R2_FB27_Msk			REG_BIT_MASK(CAN_F6R2_FB27_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 27 (`CANx_F6R2.FB27`) bit mask alias @def CAN_F6R2_FB27 */
#define CAN_F6R2_FB27				CAN_F6R2_FB27_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 28 (`CANx_F6R2.FB28`) bit position @def CAN_F6R2_FB28_Pos */
#define CAN_F6R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 6 word 2 bit 28 (`CANx_F6R2.FB28`) bit mask @def CAN_F6R2_FB28_Msk */
#define CAN_F6R2_FB28_Msk			REG_BIT_MASK(CAN_F6R2_FB28_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 28 (`CANx_F6R2.FB28`) bit mask alias @def CAN_F6R2_FB28 */
#define CAN_F6R2_FB28				CAN_F6R2_FB28_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 29 (`CANx_F6R2.FB29`) bit position @def CAN_F6R2_FB29_Pos */
#define CAN_F6R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 6 word 2 bit 29 (`CANx_F6R2.FB29`) bit mask @def CAN_F6R2_FB29_Msk */
#define CAN_F6R2_FB29_Msk			REG_BIT_MASK(CAN_F6R2_FB29_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 29 (`CANx_F6R2.FB29`) bit mask alias @def CAN_F6R2_FB29 */
#define CAN_F6R2_FB29				CAN_F6R2_FB29_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 30 (`CANx_F6R2.FB30`) bit position @def CAN_F6R2_FB30_Pos */
#define CAN_F6R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 6 word 2 bit 30 (`CANx_F6R2.FB30`) bit mask @def CAN_F6R2_FB30_Msk */
#define CAN_F6R2_FB30_Msk			REG_BIT_MASK(CAN_F6R2_FB30_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 30 (`CANx_F6R2.FB30`) bit mask alias @def CAN_F6R2_FB30 */
#define CAN_F6R2_FB30				CAN_F6R2_FB30_Msk

/** @brief Acceptance-filter bank 6 word 2 bit 31 (`CANx_F6R2.FB31`) bit position @def CAN_F6R2_FB31_Pos */
#define CAN_F6R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 6 word 2 bit 31 (`CANx_F6R2.FB31`) bit mask @def CAN_F6R2_FB31_Msk */
#define CAN_F6R2_FB31_Msk			REG_BIT_MASK(CAN_F6R2_FB31_Pos)
/** @brief Acceptance-filter bank 6 word 2 bit 31 (`CANx_F6R2.FB31`) bit mask alias @def CAN_F6R2_FB31 */
#define CAN_F6R2_FB31				CAN_F6R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F7R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 7 word 2 bit 0 (`CANx_F7R2.FB0`) bit position @def CAN_F7R2_FB0_Pos */
#define CAN_F7R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 7 word 2 bit 0 (`CANx_F7R2.FB0`) bit mask @def CAN_F7R2_FB0_Msk */
#define CAN_F7R2_FB0_Msk			REG_BIT_MASK(CAN_F7R2_FB0_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 0 (`CANx_F7R2.FB0`) bit mask alias @def CAN_F7R2_FB0 */
#define CAN_F7R2_FB0				CAN_F7R2_FB0_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 1 (`CANx_F7R2.FB1`) bit position @def CAN_F7R2_FB1_Pos */
#define CAN_F7R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 7 word 2 bit 1 (`CANx_F7R2.FB1`) bit mask @def CAN_F7R2_FB1_Msk */
#define CAN_F7R2_FB1_Msk			REG_BIT_MASK(CAN_F7R2_FB1_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 1 (`CANx_F7R2.FB1`) bit mask alias @def CAN_F7R2_FB1 */
#define CAN_F7R2_FB1				CAN_F7R2_FB1_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 2 (`CANx_F7R2.FB2`) bit position @def CAN_F7R2_FB2_Pos */
#define CAN_F7R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 7 word 2 bit 2 (`CANx_F7R2.FB2`) bit mask @def CAN_F7R2_FB2_Msk */
#define CAN_F7R2_FB2_Msk			REG_BIT_MASK(CAN_F7R2_FB2_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 2 (`CANx_F7R2.FB2`) bit mask alias @def CAN_F7R2_FB2 */
#define CAN_F7R2_FB2				CAN_F7R2_FB2_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 3 (`CANx_F7R2.FB3`) bit position @def CAN_F7R2_FB3_Pos */
#define CAN_F7R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 7 word 2 bit 3 (`CANx_F7R2.FB3`) bit mask @def CAN_F7R2_FB3_Msk */
#define CAN_F7R2_FB3_Msk			REG_BIT_MASK(CAN_F7R2_FB3_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 3 (`CANx_F7R2.FB3`) bit mask alias @def CAN_F7R2_FB3 */
#define CAN_F7R2_FB3				CAN_F7R2_FB3_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 4 (`CANx_F7R2.FB4`) bit position @def CAN_F7R2_FB4_Pos */
#define CAN_F7R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 7 word 2 bit 4 (`CANx_F7R2.FB4`) bit mask @def CAN_F7R2_FB4_Msk */
#define CAN_F7R2_FB4_Msk			REG_BIT_MASK(CAN_F7R2_FB4_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 4 (`CANx_F7R2.FB4`) bit mask alias @def CAN_F7R2_FB4 */
#define CAN_F7R2_FB4				CAN_F7R2_FB4_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 5 (`CANx_F7R2.FB5`) bit position @def CAN_F7R2_FB5_Pos */
#define CAN_F7R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 7 word 2 bit 5 (`CANx_F7R2.FB5`) bit mask @def CAN_F7R2_FB5_Msk */
#define CAN_F7R2_FB5_Msk			REG_BIT_MASK(CAN_F7R2_FB5_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 5 (`CANx_F7R2.FB5`) bit mask alias @def CAN_F7R2_FB5 */
#define CAN_F7R2_FB5				CAN_F7R2_FB5_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 6 (`CANx_F7R2.FB6`) bit position @def CAN_F7R2_FB6_Pos */
#define CAN_F7R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 7 word 2 bit 6 (`CANx_F7R2.FB6`) bit mask @def CAN_F7R2_FB6_Msk */
#define CAN_F7R2_FB6_Msk			REG_BIT_MASK(CAN_F7R2_FB6_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 6 (`CANx_F7R2.FB6`) bit mask alias @def CAN_F7R2_FB6 */
#define CAN_F7R2_FB6				CAN_F7R2_FB6_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 7 (`CANx_F7R2.FB7`) bit position @def CAN_F7R2_FB7_Pos */
#define CAN_F7R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 7 word 2 bit 7 (`CANx_F7R2.FB7`) bit mask @def CAN_F7R2_FB7_Msk */
#define CAN_F7R2_FB7_Msk			REG_BIT_MASK(CAN_F7R2_FB7_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 7 (`CANx_F7R2.FB7`) bit mask alias @def CAN_F7R2_FB7 */
#define CAN_F7R2_FB7				CAN_F7R2_FB7_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 8 (`CANx_F7R2.FB8`) bit position @def CAN_F7R2_FB8_Pos */
#define CAN_F7R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 7 word 2 bit 8 (`CANx_F7R2.FB8`) bit mask @def CAN_F7R2_FB8_Msk */
#define CAN_F7R2_FB8_Msk			REG_BIT_MASK(CAN_F7R2_FB8_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 8 (`CANx_F7R2.FB8`) bit mask alias @def CAN_F7R2_FB8 */
#define CAN_F7R2_FB8				CAN_F7R2_FB8_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 9 (`CANx_F7R2.FB9`) bit position @def CAN_F7R2_FB9_Pos */
#define CAN_F7R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 7 word 2 bit 9 (`CANx_F7R2.FB9`) bit mask @def CAN_F7R2_FB9_Msk */
#define CAN_F7R2_FB9_Msk			REG_BIT_MASK(CAN_F7R2_FB9_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 9 (`CANx_F7R2.FB9`) bit mask alias @def CAN_F7R2_FB9 */
#define CAN_F7R2_FB9				CAN_F7R2_FB9_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 10 (`CANx_F7R2.FB10`) bit position @def CAN_F7R2_FB10_Pos */
#define CAN_F7R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 7 word 2 bit 10 (`CANx_F7R2.FB10`) bit mask @def CAN_F7R2_FB10_Msk */
#define CAN_F7R2_FB10_Msk			REG_BIT_MASK(CAN_F7R2_FB10_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 10 (`CANx_F7R2.FB10`) bit mask alias @def CAN_F7R2_FB10 */
#define CAN_F7R2_FB10				CAN_F7R2_FB10_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 11 (`CANx_F7R2.FB11`) bit position @def CAN_F7R2_FB11_Pos */
#define CAN_F7R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 7 word 2 bit 11 (`CANx_F7R2.FB11`) bit mask @def CAN_F7R2_FB11_Msk */
#define CAN_F7R2_FB11_Msk			REG_BIT_MASK(CAN_F7R2_FB11_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 11 (`CANx_F7R2.FB11`) bit mask alias @def CAN_F7R2_FB11 */
#define CAN_F7R2_FB11				CAN_F7R2_FB11_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 12 (`CANx_F7R2.FB12`) bit position @def CAN_F7R2_FB12_Pos */
#define CAN_F7R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 7 word 2 bit 12 (`CANx_F7R2.FB12`) bit mask @def CAN_F7R2_FB12_Msk */
#define CAN_F7R2_FB12_Msk			REG_BIT_MASK(CAN_F7R2_FB12_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 12 (`CANx_F7R2.FB12`) bit mask alias @def CAN_F7R2_FB12 */
#define CAN_F7R2_FB12				CAN_F7R2_FB12_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 13 (`CANx_F7R2.FB13`) bit position @def CAN_F7R2_FB13_Pos */
#define CAN_F7R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 7 word 2 bit 13 (`CANx_F7R2.FB13`) bit mask @def CAN_F7R2_FB13_Msk */
#define CAN_F7R2_FB13_Msk			REG_BIT_MASK(CAN_F7R2_FB13_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 13 (`CANx_F7R2.FB13`) bit mask alias @def CAN_F7R2_FB13 */
#define CAN_F7R2_FB13				CAN_F7R2_FB13_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 14 (`CANx_F7R2.FB14`) bit position @def CAN_F7R2_FB14_Pos */
#define CAN_F7R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 7 word 2 bit 14 (`CANx_F7R2.FB14`) bit mask @def CAN_F7R2_FB14_Msk */
#define CAN_F7R2_FB14_Msk			REG_BIT_MASK(CAN_F7R2_FB14_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 14 (`CANx_F7R2.FB14`) bit mask alias @def CAN_F7R2_FB14 */
#define CAN_F7R2_FB14				CAN_F7R2_FB14_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 15 (`CANx_F7R2.FB15`) bit position @def CAN_F7R2_FB15_Pos */
#define CAN_F7R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 7 word 2 bit 15 (`CANx_F7R2.FB15`) bit mask @def CAN_F7R2_FB15_Msk */
#define CAN_F7R2_FB15_Msk			REG_BIT_MASK(CAN_F7R2_FB15_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 15 (`CANx_F7R2.FB15`) bit mask alias @def CAN_F7R2_FB15 */
#define CAN_F7R2_FB15				CAN_F7R2_FB15_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 16 (`CANx_F7R2.FB16`) bit position @def CAN_F7R2_FB16_Pos */
#define CAN_F7R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 7 word 2 bit 16 (`CANx_F7R2.FB16`) bit mask @def CAN_F7R2_FB16_Msk */
#define CAN_F7R2_FB16_Msk			REG_BIT_MASK(CAN_F7R2_FB16_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 16 (`CANx_F7R2.FB16`) bit mask alias @def CAN_F7R2_FB16 */
#define CAN_F7R2_FB16				CAN_F7R2_FB16_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 17 (`CANx_F7R2.FB17`) bit position @def CAN_F7R2_FB17_Pos */
#define CAN_F7R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 7 word 2 bit 17 (`CANx_F7R2.FB17`) bit mask @def CAN_F7R2_FB17_Msk */
#define CAN_F7R2_FB17_Msk			REG_BIT_MASK(CAN_F7R2_FB17_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 17 (`CANx_F7R2.FB17`) bit mask alias @def CAN_F7R2_FB17 */
#define CAN_F7R2_FB17				CAN_F7R2_FB17_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 18 (`CANx_F7R2.FB18`) bit position @def CAN_F7R2_FB18_Pos */
#define CAN_F7R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 7 word 2 bit 18 (`CANx_F7R2.FB18`) bit mask @def CAN_F7R2_FB18_Msk */
#define CAN_F7R2_FB18_Msk			REG_BIT_MASK(CAN_F7R2_FB18_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 18 (`CANx_F7R2.FB18`) bit mask alias @def CAN_F7R2_FB18 */
#define CAN_F7R2_FB18				CAN_F7R2_FB18_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 19 (`CANx_F7R2.FB19`) bit position @def CAN_F7R2_FB19_Pos */
#define CAN_F7R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 7 word 2 bit 19 (`CANx_F7R2.FB19`) bit mask @def CAN_F7R2_FB19_Msk */
#define CAN_F7R2_FB19_Msk			REG_BIT_MASK(CAN_F7R2_FB19_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 19 (`CANx_F7R2.FB19`) bit mask alias @def CAN_F7R2_FB19 */
#define CAN_F7R2_FB19				CAN_F7R2_FB19_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 20 (`CANx_F7R2.FB20`) bit position @def CAN_F7R2_FB20_Pos */
#define CAN_F7R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 7 word 2 bit 20 (`CANx_F7R2.FB20`) bit mask @def CAN_F7R2_FB20_Msk */
#define CAN_F7R2_FB20_Msk			REG_BIT_MASK(CAN_F7R2_FB20_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 20 (`CANx_F7R2.FB20`) bit mask alias @def CAN_F7R2_FB20 */
#define CAN_F7R2_FB20				CAN_F7R2_FB20_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 21 (`CANx_F7R2.FB21`) bit position @def CAN_F7R2_FB21_Pos */
#define CAN_F7R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 7 word 2 bit 21 (`CANx_F7R2.FB21`) bit mask @def CAN_F7R2_FB21_Msk */
#define CAN_F7R2_FB21_Msk			REG_BIT_MASK(CAN_F7R2_FB21_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 21 (`CANx_F7R2.FB21`) bit mask alias @def CAN_F7R2_FB21 */
#define CAN_F7R2_FB21				CAN_F7R2_FB21_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 22 (`CANx_F7R2.FB22`) bit position @def CAN_F7R2_FB22_Pos */
#define CAN_F7R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 7 word 2 bit 22 (`CANx_F7R2.FB22`) bit mask @def CAN_F7R2_FB22_Msk */
#define CAN_F7R2_FB22_Msk			REG_BIT_MASK(CAN_F7R2_FB22_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 22 (`CANx_F7R2.FB22`) bit mask alias @def CAN_F7R2_FB22 */
#define CAN_F7R2_FB22				CAN_F7R2_FB22_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 23 (`CANx_F7R2.FB23`) bit position @def CAN_F7R2_FB23_Pos */
#define CAN_F7R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 7 word 2 bit 23 (`CANx_F7R2.FB23`) bit mask @def CAN_F7R2_FB23_Msk */
#define CAN_F7R2_FB23_Msk			REG_BIT_MASK(CAN_F7R2_FB23_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 23 (`CANx_F7R2.FB23`) bit mask alias @def CAN_F7R2_FB23 */
#define CAN_F7R2_FB23				CAN_F7R2_FB23_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 24 (`CANx_F7R2.FB24`) bit position @def CAN_F7R2_FB24_Pos */
#define CAN_F7R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 7 word 2 bit 24 (`CANx_F7R2.FB24`) bit mask @def CAN_F7R2_FB24_Msk */
#define CAN_F7R2_FB24_Msk			REG_BIT_MASK(CAN_F7R2_FB24_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 24 (`CANx_F7R2.FB24`) bit mask alias @def CAN_F7R2_FB24 */
#define CAN_F7R2_FB24				CAN_F7R2_FB24_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 25 (`CANx_F7R2.FB25`) bit position @def CAN_F7R2_FB25_Pos */
#define CAN_F7R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 7 word 2 bit 25 (`CANx_F7R2.FB25`) bit mask @def CAN_F7R2_FB25_Msk */
#define CAN_F7R2_FB25_Msk			REG_BIT_MASK(CAN_F7R2_FB25_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 25 (`CANx_F7R2.FB25`) bit mask alias @def CAN_F7R2_FB25 */
#define CAN_F7R2_FB25				CAN_F7R2_FB25_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 26 (`CANx_F7R2.FB26`) bit position @def CAN_F7R2_FB26_Pos */
#define CAN_F7R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 7 word 2 bit 26 (`CANx_F7R2.FB26`) bit mask @def CAN_F7R2_FB26_Msk */
#define CAN_F7R2_FB26_Msk			REG_BIT_MASK(CAN_F7R2_FB26_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 26 (`CANx_F7R2.FB26`) bit mask alias @def CAN_F7R2_FB26 */
#define CAN_F7R2_FB26				CAN_F7R2_FB26_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 27 (`CANx_F7R2.FB27`) bit position @def CAN_F7R2_FB27_Pos */
#define CAN_F7R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 7 word 2 bit 27 (`CANx_F7R2.FB27`) bit mask @def CAN_F7R2_FB27_Msk */
#define CAN_F7R2_FB27_Msk			REG_BIT_MASK(CAN_F7R2_FB27_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 27 (`CANx_F7R2.FB27`) bit mask alias @def CAN_F7R2_FB27 */
#define CAN_F7R2_FB27				CAN_F7R2_FB27_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 28 (`CANx_F7R2.FB28`) bit position @def CAN_F7R2_FB28_Pos */
#define CAN_F7R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 7 word 2 bit 28 (`CANx_F7R2.FB28`) bit mask @def CAN_F7R2_FB28_Msk */
#define CAN_F7R2_FB28_Msk			REG_BIT_MASK(CAN_F7R2_FB28_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 28 (`CANx_F7R2.FB28`) bit mask alias @def CAN_F7R2_FB28 */
#define CAN_F7R2_FB28				CAN_F7R2_FB28_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 29 (`CANx_F7R2.FB29`) bit position @def CAN_F7R2_FB29_Pos */
#define CAN_F7R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 7 word 2 bit 29 (`CANx_F7R2.FB29`) bit mask @def CAN_F7R2_FB29_Msk */
#define CAN_F7R2_FB29_Msk			REG_BIT_MASK(CAN_F7R2_FB29_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 29 (`CANx_F7R2.FB29`) bit mask alias @def CAN_F7R2_FB29 */
#define CAN_F7R2_FB29				CAN_F7R2_FB29_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 30 (`CANx_F7R2.FB30`) bit position @def CAN_F7R2_FB30_Pos */
#define CAN_F7R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 7 word 2 bit 30 (`CANx_F7R2.FB30`) bit mask @def CAN_F7R2_FB30_Msk */
#define CAN_F7R2_FB30_Msk			REG_BIT_MASK(CAN_F7R2_FB30_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 30 (`CANx_F7R2.FB30`) bit mask alias @def CAN_F7R2_FB30 */
#define CAN_F7R2_FB30				CAN_F7R2_FB30_Msk

/** @brief Acceptance-filter bank 7 word 2 bit 31 (`CANx_F7R2.FB31`) bit position @def CAN_F7R2_FB31_Pos */
#define CAN_F7R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 7 word 2 bit 31 (`CANx_F7R2.FB31`) bit mask @def CAN_F7R2_FB31_Msk */
#define CAN_F7R2_FB31_Msk			REG_BIT_MASK(CAN_F7R2_FB31_Pos)
/** @brief Acceptance-filter bank 7 word 2 bit 31 (`CANx_F7R2.FB31`) bit mask alias @def CAN_F7R2_FB31 */
#define CAN_F7R2_FB31				CAN_F7R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F8R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 8 word 2 bit 0 (`CANx_F8R2.FB0`) bit position @def CAN_F8R2_FB0_Pos */
#define CAN_F8R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 8 word 2 bit 0 (`CANx_F8R2.FB0`) bit mask @def CAN_F8R2_FB0_Msk */
#define CAN_F8R2_FB0_Msk			REG_BIT_MASK(CAN_F8R2_FB0_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 0 (`CANx_F8R2.FB0`) bit mask alias @def CAN_F8R2_FB0 */
#define CAN_F8R2_FB0				CAN_F8R2_FB0_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 1 (`CANx_F8R2.FB1`) bit position @def CAN_F8R2_FB1_Pos */
#define CAN_F8R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 8 word 2 bit 1 (`CANx_F8R2.FB1`) bit mask @def CAN_F8R2_FB1_Msk */
#define CAN_F8R2_FB1_Msk			REG_BIT_MASK(CAN_F8R2_FB1_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 1 (`CANx_F8R2.FB1`) bit mask alias @def CAN_F8R2_FB1 */
#define CAN_F8R2_FB1				CAN_F8R2_FB1_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 2 (`CANx_F8R2.FB2`) bit position @def CAN_F8R2_FB2_Pos */
#define CAN_F8R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 8 word 2 bit 2 (`CANx_F8R2.FB2`) bit mask @def CAN_F8R2_FB2_Msk */
#define CAN_F8R2_FB2_Msk			REG_BIT_MASK(CAN_F8R2_FB2_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 2 (`CANx_F8R2.FB2`) bit mask alias @def CAN_F8R2_FB2 */
#define CAN_F8R2_FB2				CAN_F8R2_FB2_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 3 (`CANx_F8R2.FB3`) bit position @def CAN_F8R2_FB3_Pos */
#define CAN_F8R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 8 word 2 bit 3 (`CANx_F8R2.FB3`) bit mask @def CAN_F8R2_FB3_Msk */
#define CAN_F8R2_FB3_Msk			REG_BIT_MASK(CAN_F8R2_FB3_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 3 (`CANx_F8R2.FB3`) bit mask alias @def CAN_F8R2_FB3 */
#define CAN_F8R2_FB3				CAN_F8R2_FB3_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 4 (`CANx_F8R2.FB4`) bit position @def CAN_F8R2_FB4_Pos */
#define CAN_F8R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 8 word 2 bit 4 (`CANx_F8R2.FB4`) bit mask @def CAN_F8R2_FB4_Msk */
#define CAN_F8R2_FB4_Msk			REG_BIT_MASK(CAN_F8R2_FB4_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 4 (`CANx_F8R2.FB4`) bit mask alias @def CAN_F8R2_FB4 */
#define CAN_F8R2_FB4				CAN_F8R2_FB4_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 5 (`CANx_F8R2.FB5`) bit position @def CAN_F8R2_FB5_Pos */
#define CAN_F8R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 8 word 2 bit 5 (`CANx_F8R2.FB5`) bit mask @def CAN_F8R2_FB5_Msk */
#define CAN_F8R2_FB5_Msk			REG_BIT_MASK(CAN_F8R2_FB5_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 5 (`CANx_F8R2.FB5`) bit mask alias @def CAN_F8R2_FB5 */
#define CAN_F8R2_FB5				CAN_F8R2_FB5_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 6 (`CANx_F8R2.FB6`) bit position @def CAN_F8R2_FB6_Pos */
#define CAN_F8R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 8 word 2 bit 6 (`CANx_F8R2.FB6`) bit mask @def CAN_F8R2_FB6_Msk */
#define CAN_F8R2_FB6_Msk			REG_BIT_MASK(CAN_F8R2_FB6_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 6 (`CANx_F8R2.FB6`) bit mask alias @def CAN_F8R2_FB6 */
#define CAN_F8R2_FB6				CAN_F8R2_FB6_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 7 (`CANx_F8R2.FB7`) bit position @def CAN_F8R2_FB7_Pos */
#define CAN_F8R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 8 word 2 bit 7 (`CANx_F8R2.FB7`) bit mask @def CAN_F8R2_FB7_Msk */
#define CAN_F8R2_FB7_Msk			REG_BIT_MASK(CAN_F8R2_FB7_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 7 (`CANx_F8R2.FB7`) bit mask alias @def CAN_F8R2_FB7 */
#define CAN_F8R2_FB7				CAN_F8R2_FB7_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 8 (`CANx_F8R2.FB8`) bit position @def CAN_F8R2_FB8_Pos */
#define CAN_F8R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 8 word 2 bit 8 (`CANx_F8R2.FB8`) bit mask @def CAN_F8R2_FB8_Msk */
#define CAN_F8R2_FB8_Msk			REG_BIT_MASK(CAN_F8R2_FB8_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 8 (`CANx_F8R2.FB8`) bit mask alias @def CAN_F8R2_FB8 */
#define CAN_F8R2_FB8				CAN_F8R2_FB8_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 9 (`CANx_F8R2.FB9`) bit position @def CAN_F8R2_FB9_Pos */
#define CAN_F8R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 8 word 2 bit 9 (`CANx_F8R2.FB9`) bit mask @def CAN_F8R2_FB9_Msk */
#define CAN_F8R2_FB9_Msk			REG_BIT_MASK(CAN_F8R2_FB9_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 9 (`CANx_F8R2.FB9`) bit mask alias @def CAN_F8R2_FB9 */
#define CAN_F8R2_FB9				CAN_F8R2_FB9_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 10 (`CANx_F8R2.FB10`) bit position @def CAN_F8R2_FB10_Pos */
#define CAN_F8R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 8 word 2 bit 10 (`CANx_F8R2.FB10`) bit mask @def CAN_F8R2_FB10_Msk */
#define CAN_F8R2_FB10_Msk			REG_BIT_MASK(CAN_F8R2_FB10_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 10 (`CANx_F8R2.FB10`) bit mask alias @def CAN_F8R2_FB10 */
#define CAN_F8R2_FB10				CAN_F8R2_FB10_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 11 (`CANx_F8R2.FB11`) bit position @def CAN_F8R2_FB11_Pos */
#define CAN_F8R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 8 word 2 bit 11 (`CANx_F8R2.FB11`) bit mask @def CAN_F8R2_FB11_Msk */
#define CAN_F8R2_FB11_Msk			REG_BIT_MASK(CAN_F8R2_FB11_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 11 (`CANx_F8R2.FB11`) bit mask alias @def CAN_F8R2_FB11 */
#define CAN_F8R2_FB11				CAN_F8R2_FB11_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 12 (`CANx_F8R2.FB12`) bit position @def CAN_F8R2_FB12_Pos */
#define CAN_F8R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 8 word 2 bit 12 (`CANx_F8R2.FB12`) bit mask @def CAN_F8R2_FB12_Msk */
#define CAN_F8R2_FB12_Msk			REG_BIT_MASK(CAN_F8R2_FB12_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 12 (`CANx_F8R2.FB12`) bit mask alias @def CAN_F8R2_FB12 */
#define CAN_F8R2_FB12				CAN_F8R2_FB12_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 13 (`CANx_F8R2.FB13`) bit position @def CAN_F8R2_FB13_Pos */
#define CAN_F8R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 8 word 2 bit 13 (`CANx_F8R2.FB13`) bit mask @def CAN_F8R2_FB13_Msk */
#define CAN_F8R2_FB13_Msk			REG_BIT_MASK(CAN_F8R2_FB13_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 13 (`CANx_F8R2.FB13`) bit mask alias @def CAN_F8R2_FB13 */
#define CAN_F8R2_FB13				CAN_F8R2_FB13_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 14 (`CANx_F8R2.FB14`) bit position @def CAN_F8R2_FB14_Pos */
#define CAN_F8R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 8 word 2 bit 14 (`CANx_F8R2.FB14`) bit mask @def CAN_F8R2_FB14_Msk */
#define CAN_F8R2_FB14_Msk			REG_BIT_MASK(CAN_F8R2_FB14_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 14 (`CANx_F8R2.FB14`) bit mask alias @def CAN_F8R2_FB14 */
#define CAN_F8R2_FB14				CAN_F8R2_FB14_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 15 (`CANx_F8R2.FB15`) bit position @def CAN_F8R2_FB15_Pos */
#define CAN_F8R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 8 word 2 bit 15 (`CANx_F8R2.FB15`) bit mask @def CAN_F8R2_FB15_Msk */
#define CAN_F8R2_FB15_Msk			REG_BIT_MASK(CAN_F8R2_FB15_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 15 (`CANx_F8R2.FB15`) bit mask alias @def CAN_F8R2_FB15 */
#define CAN_F8R2_FB15				CAN_F8R2_FB15_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 16 (`CANx_F8R2.FB16`) bit position @def CAN_F8R2_FB16_Pos */
#define CAN_F8R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 8 word 2 bit 16 (`CANx_F8R2.FB16`) bit mask @def CAN_F8R2_FB16_Msk */
#define CAN_F8R2_FB16_Msk			REG_BIT_MASK(CAN_F8R2_FB16_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 16 (`CANx_F8R2.FB16`) bit mask alias @def CAN_F8R2_FB16 */
#define CAN_F8R2_FB16				CAN_F8R2_FB16_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 17 (`CANx_F8R2.FB17`) bit position @def CAN_F8R2_FB17_Pos */
#define CAN_F8R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 8 word 2 bit 17 (`CANx_F8R2.FB17`) bit mask @def CAN_F8R2_FB17_Msk */
#define CAN_F8R2_FB17_Msk			REG_BIT_MASK(CAN_F8R2_FB17_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 17 (`CANx_F8R2.FB17`) bit mask alias @def CAN_F8R2_FB17 */
#define CAN_F8R2_FB17				CAN_F8R2_FB17_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 18 (`CANx_F8R2.FB18`) bit position @def CAN_F8R2_FB18_Pos */
#define CAN_F8R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 8 word 2 bit 18 (`CANx_F8R2.FB18`) bit mask @def CAN_F8R2_FB18_Msk */
#define CAN_F8R2_FB18_Msk			REG_BIT_MASK(CAN_F8R2_FB18_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 18 (`CANx_F8R2.FB18`) bit mask alias @def CAN_F8R2_FB18 */
#define CAN_F8R2_FB18				CAN_F8R2_FB18_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 19 (`CANx_F8R2.FB19`) bit position @def CAN_F8R2_FB19_Pos */
#define CAN_F8R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 8 word 2 bit 19 (`CANx_F8R2.FB19`) bit mask @def CAN_F8R2_FB19_Msk */
#define CAN_F8R2_FB19_Msk			REG_BIT_MASK(CAN_F8R2_FB19_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 19 (`CANx_F8R2.FB19`) bit mask alias @def CAN_F8R2_FB19 */
#define CAN_F8R2_FB19				CAN_F8R2_FB19_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 20 (`CANx_F8R2.FB20`) bit position @def CAN_F8R2_FB20_Pos */
#define CAN_F8R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 8 word 2 bit 20 (`CANx_F8R2.FB20`) bit mask @def CAN_F8R2_FB20_Msk */
#define CAN_F8R2_FB20_Msk			REG_BIT_MASK(CAN_F8R2_FB20_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 20 (`CANx_F8R2.FB20`) bit mask alias @def CAN_F8R2_FB20 */
#define CAN_F8R2_FB20				CAN_F8R2_FB20_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 21 (`CANx_F8R2.FB21`) bit position @def CAN_F8R2_FB21_Pos */
#define CAN_F8R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 8 word 2 bit 21 (`CANx_F8R2.FB21`) bit mask @def CAN_F8R2_FB21_Msk */
#define CAN_F8R2_FB21_Msk			REG_BIT_MASK(CAN_F8R2_FB21_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 21 (`CANx_F8R2.FB21`) bit mask alias @def CAN_F8R2_FB21 */
#define CAN_F8R2_FB21				CAN_F8R2_FB21_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 22 (`CANx_F8R2.FB22`) bit position @def CAN_F8R2_FB22_Pos */
#define CAN_F8R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 8 word 2 bit 22 (`CANx_F8R2.FB22`) bit mask @def CAN_F8R2_FB22_Msk */
#define CAN_F8R2_FB22_Msk			REG_BIT_MASK(CAN_F8R2_FB22_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 22 (`CANx_F8R2.FB22`) bit mask alias @def CAN_F8R2_FB22 */
#define CAN_F8R2_FB22				CAN_F8R2_FB22_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 23 (`CANx_F8R2.FB23`) bit position @def CAN_F8R2_FB23_Pos */
#define CAN_F8R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 8 word 2 bit 23 (`CANx_F8R2.FB23`) bit mask @def CAN_F8R2_FB23_Msk */
#define CAN_F8R2_FB23_Msk			REG_BIT_MASK(CAN_F8R2_FB23_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 23 (`CANx_F8R2.FB23`) bit mask alias @def CAN_F8R2_FB23 */
#define CAN_F8R2_FB23				CAN_F8R2_FB23_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 24 (`CANx_F8R2.FB24`) bit position @def CAN_F8R2_FB24_Pos */
#define CAN_F8R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 8 word 2 bit 24 (`CANx_F8R2.FB24`) bit mask @def CAN_F8R2_FB24_Msk */
#define CAN_F8R2_FB24_Msk			REG_BIT_MASK(CAN_F8R2_FB24_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 24 (`CANx_F8R2.FB24`) bit mask alias @def CAN_F8R2_FB24 */
#define CAN_F8R2_FB24				CAN_F8R2_FB24_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 25 (`CANx_F8R2.FB25`) bit position @def CAN_F8R2_FB25_Pos */
#define CAN_F8R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 8 word 2 bit 25 (`CANx_F8R2.FB25`) bit mask @def CAN_F8R2_FB25_Msk */
#define CAN_F8R2_FB25_Msk			REG_BIT_MASK(CAN_F8R2_FB25_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 25 (`CANx_F8R2.FB25`) bit mask alias @def CAN_F8R2_FB25 */
#define CAN_F8R2_FB25				CAN_F8R2_FB25_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 26 (`CANx_F8R2.FB26`) bit position @def CAN_F8R2_FB26_Pos */
#define CAN_F8R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 8 word 2 bit 26 (`CANx_F8R2.FB26`) bit mask @def CAN_F8R2_FB26_Msk */
#define CAN_F8R2_FB26_Msk			REG_BIT_MASK(CAN_F8R2_FB26_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 26 (`CANx_F8R2.FB26`) bit mask alias @def CAN_F8R2_FB26 */
#define CAN_F8R2_FB26				CAN_F8R2_FB26_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 27 (`CANx_F8R2.FB27`) bit position @def CAN_F8R2_FB27_Pos */
#define CAN_F8R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 8 word 2 bit 27 (`CANx_F8R2.FB27`) bit mask @def CAN_F8R2_FB27_Msk */
#define CAN_F8R2_FB27_Msk			REG_BIT_MASK(CAN_F8R2_FB27_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 27 (`CANx_F8R2.FB27`) bit mask alias @def CAN_F8R2_FB27 */
#define CAN_F8R2_FB27				CAN_F8R2_FB27_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 28 (`CANx_F8R2.FB28`) bit position @def CAN_F8R2_FB28_Pos */
#define CAN_F8R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 8 word 2 bit 28 (`CANx_F8R2.FB28`) bit mask @def CAN_F8R2_FB28_Msk */
#define CAN_F8R2_FB28_Msk			REG_BIT_MASK(CAN_F8R2_FB28_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 28 (`CANx_F8R2.FB28`) bit mask alias @def CAN_F8R2_FB28 */
#define CAN_F8R2_FB28				CAN_F8R2_FB28_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 29 (`CANx_F8R2.FB29`) bit position @def CAN_F8R2_FB29_Pos */
#define CAN_F8R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 8 word 2 bit 29 (`CANx_F8R2.FB29`) bit mask @def CAN_F8R2_FB29_Msk */
#define CAN_F8R2_FB29_Msk			REG_BIT_MASK(CAN_F8R2_FB29_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 29 (`CANx_F8R2.FB29`) bit mask alias @def CAN_F8R2_FB29 */
#define CAN_F8R2_FB29				CAN_F8R2_FB29_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 30 (`CANx_F8R2.FB30`) bit position @def CAN_F8R2_FB30_Pos */
#define CAN_F8R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 8 word 2 bit 30 (`CANx_F8R2.FB30`) bit mask @def CAN_F8R2_FB30_Msk */
#define CAN_F8R2_FB30_Msk			REG_BIT_MASK(CAN_F8R2_FB30_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 30 (`CANx_F8R2.FB30`) bit mask alias @def CAN_F8R2_FB30 */
#define CAN_F8R2_FB30				CAN_F8R2_FB30_Msk

/** @brief Acceptance-filter bank 8 word 2 bit 31 (`CANx_F8R2.FB31`) bit position @def CAN_F8R2_FB31_Pos */
#define CAN_F8R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 8 word 2 bit 31 (`CANx_F8R2.FB31`) bit mask @def CAN_F8R2_FB31_Msk */
#define CAN_F8R2_FB31_Msk			REG_BIT_MASK(CAN_F8R2_FB31_Pos)
/** @brief Acceptance-filter bank 8 word 2 bit 31 (`CANx_F8R2.FB31`) bit mask alias @def CAN_F8R2_FB31 */
#define CAN_F8R2_FB31				CAN_F8R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F9R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 9 word 2 bit 0 (`CANx_F9R2.FB0`) bit position @def CAN_F9R2_FB0_Pos */
#define CAN_F9R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 9 word 2 bit 0 (`CANx_F9R2.FB0`) bit mask @def CAN_F9R2_FB0_Msk */
#define CAN_F9R2_FB0_Msk			REG_BIT_MASK(CAN_F9R2_FB0_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 0 (`CANx_F9R2.FB0`) bit mask alias @def CAN_F9R2_FB0 */
#define CAN_F9R2_FB0				CAN_F9R2_FB0_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 1 (`CANx_F9R2.FB1`) bit position @def CAN_F9R2_FB1_Pos */
#define CAN_F9R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 9 word 2 bit 1 (`CANx_F9R2.FB1`) bit mask @def CAN_F9R2_FB1_Msk */
#define CAN_F9R2_FB1_Msk			REG_BIT_MASK(CAN_F9R2_FB1_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 1 (`CANx_F9R2.FB1`) bit mask alias @def CAN_F9R2_FB1 */
#define CAN_F9R2_FB1				CAN_F9R2_FB1_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 2 (`CANx_F9R2.FB2`) bit position @def CAN_F9R2_FB2_Pos */
#define CAN_F9R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 9 word 2 bit 2 (`CANx_F9R2.FB2`) bit mask @def CAN_F9R2_FB2_Msk */
#define CAN_F9R2_FB2_Msk			REG_BIT_MASK(CAN_F9R2_FB2_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 2 (`CANx_F9R2.FB2`) bit mask alias @def CAN_F9R2_FB2 */
#define CAN_F9R2_FB2				CAN_F9R2_FB2_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 3 (`CANx_F9R2.FB3`) bit position @def CAN_F9R2_FB3_Pos */
#define CAN_F9R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 9 word 2 bit 3 (`CANx_F9R2.FB3`) bit mask @def CAN_F9R2_FB3_Msk */
#define CAN_F9R2_FB3_Msk			REG_BIT_MASK(CAN_F9R2_FB3_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 3 (`CANx_F9R2.FB3`) bit mask alias @def CAN_F9R2_FB3 */
#define CAN_F9R2_FB3				CAN_F9R2_FB3_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 4 (`CANx_F9R2.FB4`) bit position @def CAN_F9R2_FB4_Pos */
#define CAN_F9R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 9 word 2 bit 4 (`CANx_F9R2.FB4`) bit mask @def CAN_F9R2_FB4_Msk */
#define CAN_F9R2_FB4_Msk			REG_BIT_MASK(CAN_F9R2_FB4_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 4 (`CANx_F9R2.FB4`) bit mask alias @def CAN_F9R2_FB4 */
#define CAN_F9R2_FB4				CAN_F9R2_FB4_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 5 (`CANx_F9R2.FB5`) bit position @def CAN_F9R2_FB5_Pos */
#define CAN_F9R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 9 word 2 bit 5 (`CANx_F9R2.FB5`) bit mask @def CAN_F9R2_FB5_Msk */
#define CAN_F9R2_FB5_Msk			REG_BIT_MASK(CAN_F9R2_FB5_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 5 (`CANx_F9R2.FB5`) bit mask alias @def CAN_F9R2_FB5 */
#define CAN_F9R2_FB5				CAN_F9R2_FB5_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 6 (`CANx_F9R2.FB6`) bit position @def CAN_F9R2_FB6_Pos */
#define CAN_F9R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 9 word 2 bit 6 (`CANx_F9R2.FB6`) bit mask @def CAN_F9R2_FB6_Msk */
#define CAN_F9R2_FB6_Msk			REG_BIT_MASK(CAN_F9R2_FB6_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 6 (`CANx_F9R2.FB6`) bit mask alias @def CAN_F9R2_FB6 */
#define CAN_F9R2_FB6				CAN_F9R2_FB6_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 7 (`CANx_F9R2.FB7`) bit position @def CAN_F9R2_FB7_Pos */
#define CAN_F9R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 9 word 2 bit 7 (`CANx_F9R2.FB7`) bit mask @def CAN_F9R2_FB7_Msk */
#define CAN_F9R2_FB7_Msk			REG_BIT_MASK(CAN_F9R2_FB7_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 7 (`CANx_F9R2.FB7`) bit mask alias @def CAN_F9R2_FB7 */
#define CAN_F9R2_FB7				CAN_F9R2_FB7_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 8 (`CANx_F9R2.FB8`) bit position @def CAN_F9R2_FB8_Pos */
#define CAN_F9R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 9 word 2 bit 8 (`CANx_F9R2.FB8`) bit mask @def CAN_F9R2_FB8_Msk */
#define CAN_F9R2_FB8_Msk			REG_BIT_MASK(CAN_F9R2_FB8_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 8 (`CANx_F9R2.FB8`) bit mask alias @def CAN_F9R2_FB8 */
#define CAN_F9R2_FB8				CAN_F9R2_FB8_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 9 (`CANx_F9R2.FB9`) bit position @def CAN_F9R2_FB9_Pos */
#define CAN_F9R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 9 word 2 bit 9 (`CANx_F9R2.FB9`) bit mask @def CAN_F9R2_FB9_Msk */
#define CAN_F9R2_FB9_Msk			REG_BIT_MASK(CAN_F9R2_FB9_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 9 (`CANx_F9R2.FB9`) bit mask alias @def CAN_F9R2_FB9 */
#define CAN_F9R2_FB9				CAN_F9R2_FB9_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 10 (`CANx_F9R2.FB10`) bit position @def CAN_F9R2_FB10_Pos */
#define CAN_F9R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 9 word 2 bit 10 (`CANx_F9R2.FB10`) bit mask @def CAN_F9R2_FB10_Msk */
#define CAN_F9R2_FB10_Msk			REG_BIT_MASK(CAN_F9R2_FB10_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 10 (`CANx_F9R2.FB10`) bit mask alias @def CAN_F9R2_FB10 */
#define CAN_F9R2_FB10				CAN_F9R2_FB10_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 11 (`CANx_F9R2.FB11`) bit position @def CAN_F9R2_FB11_Pos */
#define CAN_F9R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 9 word 2 bit 11 (`CANx_F9R2.FB11`) bit mask @def CAN_F9R2_FB11_Msk */
#define CAN_F9R2_FB11_Msk			REG_BIT_MASK(CAN_F9R2_FB11_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 11 (`CANx_F9R2.FB11`) bit mask alias @def CAN_F9R2_FB11 */
#define CAN_F9R2_FB11				CAN_F9R2_FB11_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 12 (`CANx_F9R2.FB12`) bit position @def CAN_F9R2_FB12_Pos */
#define CAN_F9R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 9 word 2 bit 12 (`CANx_F9R2.FB12`) bit mask @def CAN_F9R2_FB12_Msk */
#define CAN_F9R2_FB12_Msk			REG_BIT_MASK(CAN_F9R2_FB12_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 12 (`CANx_F9R2.FB12`) bit mask alias @def CAN_F9R2_FB12 */
#define CAN_F9R2_FB12				CAN_F9R2_FB12_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 13 (`CANx_F9R2.FB13`) bit position @def CAN_F9R2_FB13_Pos */
#define CAN_F9R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 9 word 2 bit 13 (`CANx_F9R2.FB13`) bit mask @def CAN_F9R2_FB13_Msk */
#define CAN_F9R2_FB13_Msk			REG_BIT_MASK(CAN_F9R2_FB13_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 13 (`CANx_F9R2.FB13`) bit mask alias @def CAN_F9R2_FB13 */
#define CAN_F9R2_FB13				CAN_F9R2_FB13_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 14 (`CANx_F9R2.FB14`) bit position @def CAN_F9R2_FB14_Pos */
#define CAN_F9R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 9 word 2 bit 14 (`CANx_F9R2.FB14`) bit mask @def CAN_F9R2_FB14_Msk */
#define CAN_F9R2_FB14_Msk			REG_BIT_MASK(CAN_F9R2_FB14_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 14 (`CANx_F9R2.FB14`) bit mask alias @def CAN_F9R2_FB14 */
#define CAN_F9R2_FB14				CAN_F9R2_FB14_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 15 (`CANx_F9R2.FB15`) bit position @def CAN_F9R2_FB15_Pos */
#define CAN_F9R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 9 word 2 bit 15 (`CANx_F9R2.FB15`) bit mask @def CAN_F9R2_FB15_Msk */
#define CAN_F9R2_FB15_Msk			REG_BIT_MASK(CAN_F9R2_FB15_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 15 (`CANx_F9R2.FB15`) bit mask alias @def CAN_F9R2_FB15 */
#define CAN_F9R2_FB15				CAN_F9R2_FB15_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 16 (`CANx_F9R2.FB16`) bit position @def CAN_F9R2_FB16_Pos */
#define CAN_F9R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 9 word 2 bit 16 (`CANx_F9R2.FB16`) bit mask @def CAN_F9R2_FB16_Msk */
#define CAN_F9R2_FB16_Msk			REG_BIT_MASK(CAN_F9R2_FB16_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 16 (`CANx_F9R2.FB16`) bit mask alias @def CAN_F9R2_FB16 */
#define CAN_F9R2_FB16				CAN_F9R2_FB16_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 17 (`CANx_F9R2.FB17`) bit position @def CAN_F9R2_FB17_Pos */
#define CAN_F9R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 9 word 2 bit 17 (`CANx_F9R2.FB17`) bit mask @def CAN_F9R2_FB17_Msk */
#define CAN_F9R2_FB17_Msk			REG_BIT_MASK(CAN_F9R2_FB17_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 17 (`CANx_F9R2.FB17`) bit mask alias @def CAN_F9R2_FB17 */
#define CAN_F9R2_FB17				CAN_F9R2_FB17_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 18 (`CANx_F9R2.FB18`) bit position @def CAN_F9R2_FB18_Pos */
#define CAN_F9R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 9 word 2 bit 18 (`CANx_F9R2.FB18`) bit mask @def CAN_F9R2_FB18_Msk */
#define CAN_F9R2_FB18_Msk			REG_BIT_MASK(CAN_F9R2_FB18_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 18 (`CANx_F9R2.FB18`) bit mask alias @def CAN_F9R2_FB18 */
#define CAN_F9R2_FB18				CAN_F9R2_FB18_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 19 (`CANx_F9R2.FB19`) bit position @def CAN_F9R2_FB19_Pos */
#define CAN_F9R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 9 word 2 bit 19 (`CANx_F9R2.FB19`) bit mask @def CAN_F9R2_FB19_Msk */
#define CAN_F9R2_FB19_Msk			REG_BIT_MASK(CAN_F9R2_FB19_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 19 (`CANx_F9R2.FB19`) bit mask alias @def CAN_F9R2_FB19 */
#define CAN_F9R2_FB19				CAN_F9R2_FB19_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 20 (`CANx_F9R2.FB20`) bit position @def CAN_F9R2_FB20_Pos */
#define CAN_F9R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 9 word 2 bit 20 (`CANx_F9R2.FB20`) bit mask @def CAN_F9R2_FB20_Msk */
#define CAN_F9R2_FB20_Msk			REG_BIT_MASK(CAN_F9R2_FB20_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 20 (`CANx_F9R2.FB20`) bit mask alias @def CAN_F9R2_FB20 */
#define CAN_F9R2_FB20				CAN_F9R2_FB20_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 21 (`CANx_F9R2.FB21`) bit position @def CAN_F9R2_FB21_Pos */
#define CAN_F9R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 9 word 2 bit 21 (`CANx_F9R2.FB21`) bit mask @def CAN_F9R2_FB21_Msk */
#define CAN_F9R2_FB21_Msk			REG_BIT_MASK(CAN_F9R2_FB21_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 21 (`CANx_F9R2.FB21`) bit mask alias @def CAN_F9R2_FB21 */
#define CAN_F9R2_FB21				CAN_F9R2_FB21_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 22 (`CANx_F9R2.FB22`) bit position @def CAN_F9R2_FB22_Pos */
#define CAN_F9R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 9 word 2 bit 22 (`CANx_F9R2.FB22`) bit mask @def CAN_F9R2_FB22_Msk */
#define CAN_F9R2_FB22_Msk			REG_BIT_MASK(CAN_F9R2_FB22_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 22 (`CANx_F9R2.FB22`) bit mask alias @def CAN_F9R2_FB22 */
#define CAN_F9R2_FB22				CAN_F9R2_FB22_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 23 (`CANx_F9R2.FB23`) bit position @def CAN_F9R2_FB23_Pos */
#define CAN_F9R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 9 word 2 bit 23 (`CANx_F9R2.FB23`) bit mask @def CAN_F9R2_FB23_Msk */
#define CAN_F9R2_FB23_Msk			REG_BIT_MASK(CAN_F9R2_FB23_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 23 (`CANx_F9R2.FB23`) bit mask alias @def CAN_F9R2_FB23 */
#define CAN_F9R2_FB23				CAN_F9R2_FB23_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 24 (`CANx_F9R2.FB24`) bit position @def CAN_F9R2_FB24_Pos */
#define CAN_F9R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 9 word 2 bit 24 (`CANx_F9R2.FB24`) bit mask @def CAN_F9R2_FB24_Msk */
#define CAN_F9R2_FB24_Msk			REG_BIT_MASK(CAN_F9R2_FB24_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 24 (`CANx_F9R2.FB24`) bit mask alias @def CAN_F9R2_FB24 */
#define CAN_F9R2_FB24				CAN_F9R2_FB24_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 25 (`CANx_F9R2.FB25`) bit position @def CAN_F9R2_FB25_Pos */
#define CAN_F9R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 9 word 2 bit 25 (`CANx_F9R2.FB25`) bit mask @def CAN_F9R2_FB25_Msk */
#define CAN_F9R2_FB25_Msk			REG_BIT_MASK(CAN_F9R2_FB25_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 25 (`CANx_F9R2.FB25`) bit mask alias @def CAN_F9R2_FB25 */
#define CAN_F9R2_FB25				CAN_F9R2_FB25_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 26 (`CANx_F9R2.FB26`) bit position @def CAN_F9R2_FB26_Pos */
#define CAN_F9R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 9 word 2 bit 26 (`CANx_F9R2.FB26`) bit mask @def CAN_F9R2_FB26_Msk */
#define CAN_F9R2_FB26_Msk			REG_BIT_MASK(CAN_F9R2_FB26_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 26 (`CANx_F9R2.FB26`) bit mask alias @def CAN_F9R2_FB26 */
#define CAN_F9R2_FB26				CAN_F9R2_FB26_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 27 (`CANx_F9R2.FB27`) bit position @def CAN_F9R2_FB27_Pos */
#define CAN_F9R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 9 word 2 bit 27 (`CANx_F9R2.FB27`) bit mask @def CAN_F9R2_FB27_Msk */
#define CAN_F9R2_FB27_Msk			REG_BIT_MASK(CAN_F9R2_FB27_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 27 (`CANx_F9R2.FB27`) bit mask alias @def CAN_F9R2_FB27 */
#define CAN_F9R2_FB27				CAN_F9R2_FB27_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 28 (`CANx_F9R2.FB28`) bit position @def CAN_F9R2_FB28_Pos */
#define CAN_F9R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 9 word 2 bit 28 (`CANx_F9R2.FB28`) bit mask @def CAN_F9R2_FB28_Msk */
#define CAN_F9R2_FB28_Msk			REG_BIT_MASK(CAN_F9R2_FB28_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 28 (`CANx_F9R2.FB28`) bit mask alias @def CAN_F9R2_FB28 */
#define CAN_F9R2_FB28				CAN_F9R2_FB28_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 29 (`CANx_F9R2.FB29`) bit position @def CAN_F9R2_FB29_Pos */
#define CAN_F9R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 9 word 2 bit 29 (`CANx_F9R2.FB29`) bit mask @def CAN_F9R2_FB29_Msk */
#define CAN_F9R2_FB29_Msk			REG_BIT_MASK(CAN_F9R2_FB29_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 29 (`CANx_F9R2.FB29`) bit mask alias @def CAN_F9R2_FB29 */
#define CAN_F9R2_FB29				CAN_F9R2_FB29_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 30 (`CANx_F9R2.FB30`) bit position @def CAN_F9R2_FB30_Pos */
#define CAN_F9R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 9 word 2 bit 30 (`CANx_F9R2.FB30`) bit mask @def CAN_F9R2_FB30_Msk */
#define CAN_F9R2_FB30_Msk			REG_BIT_MASK(CAN_F9R2_FB30_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 30 (`CANx_F9R2.FB30`) bit mask alias @def CAN_F9R2_FB30 */
#define CAN_F9R2_FB30				CAN_F9R2_FB30_Msk

/** @brief Acceptance-filter bank 9 word 2 bit 31 (`CANx_F9R2.FB31`) bit position @def CAN_F9R2_FB31_Pos */
#define CAN_F9R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 9 word 2 bit 31 (`CANx_F9R2.FB31`) bit mask @def CAN_F9R2_FB31_Msk */
#define CAN_F9R2_FB31_Msk			REG_BIT_MASK(CAN_F9R2_FB31_Pos)
/** @brief Acceptance-filter bank 9 word 2 bit 31 (`CANx_F9R2.FB31`) bit mask alias @def CAN_F9R2_FB31 */
#define CAN_F9R2_FB31				CAN_F9R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F10R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 10 word 2 bit 0 (`CANx_F10R2.FB0`) bit position @def CAN_F10R2_FB0_Pos */
#define CAN_F10R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 10 word 2 bit 0 (`CANx_F10R2.FB0`) bit mask @def CAN_F10R2_FB0_Msk */
#define CAN_F10R2_FB0_Msk			REG_BIT_MASK(CAN_F10R2_FB0_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 0 (`CANx_F10R2.FB0`) bit mask alias @def CAN_F10R2_FB0 */
#define CAN_F10R2_FB0				CAN_F10R2_FB0_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 1 (`CANx_F10R2.FB1`) bit position @def CAN_F10R2_FB1_Pos */
#define CAN_F10R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 10 word 2 bit 1 (`CANx_F10R2.FB1`) bit mask @def CAN_F10R2_FB1_Msk */
#define CAN_F10R2_FB1_Msk			REG_BIT_MASK(CAN_F10R2_FB1_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 1 (`CANx_F10R2.FB1`) bit mask alias @def CAN_F10R2_FB1 */
#define CAN_F10R2_FB1				CAN_F10R2_FB1_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 2 (`CANx_F10R2.FB2`) bit position @def CAN_F10R2_FB2_Pos */
#define CAN_F10R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 10 word 2 bit 2 (`CANx_F10R2.FB2`) bit mask @def CAN_F10R2_FB2_Msk */
#define CAN_F10R2_FB2_Msk			REG_BIT_MASK(CAN_F10R2_FB2_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 2 (`CANx_F10R2.FB2`) bit mask alias @def CAN_F10R2_FB2 */
#define CAN_F10R2_FB2				CAN_F10R2_FB2_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 3 (`CANx_F10R2.FB3`) bit position @def CAN_F10R2_FB3_Pos */
#define CAN_F10R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 10 word 2 bit 3 (`CANx_F10R2.FB3`) bit mask @def CAN_F10R2_FB3_Msk */
#define CAN_F10R2_FB3_Msk			REG_BIT_MASK(CAN_F10R2_FB3_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 3 (`CANx_F10R2.FB3`) bit mask alias @def CAN_F10R2_FB3 */
#define CAN_F10R2_FB3				CAN_F10R2_FB3_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 4 (`CANx_F10R2.FB4`) bit position @def CAN_F10R2_FB4_Pos */
#define CAN_F10R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 10 word 2 bit 4 (`CANx_F10R2.FB4`) bit mask @def CAN_F10R2_FB4_Msk */
#define CAN_F10R2_FB4_Msk			REG_BIT_MASK(CAN_F10R2_FB4_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 4 (`CANx_F10R2.FB4`) bit mask alias @def CAN_F10R2_FB4 */
#define CAN_F10R2_FB4				CAN_F10R2_FB4_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 5 (`CANx_F10R2.FB5`) bit position @def CAN_F10R2_FB5_Pos */
#define CAN_F10R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 10 word 2 bit 5 (`CANx_F10R2.FB5`) bit mask @def CAN_F10R2_FB5_Msk */
#define CAN_F10R2_FB5_Msk			REG_BIT_MASK(CAN_F10R2_FB5_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 5 (`CANx_F10R2.FB5`) bit mask alias @def CAN_F10R2_FB5 */
#define CAN_F10R2_FB5				CAN_F10R2_FB5_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 6 (`CANx_F10R2.FB6`) bit position @def CAN_F10R2_FB6_Pos */
#define CAN_F10R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 10 word 2 bit 6 (`CANx_F10R2.FB6`) bit mask @def CAN_F10R2_FB6_Msk */
#define CAN_F10R2_FB6_Msk			REG_BIT_MASK(CAN_F10R2_FB6_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 6 (`CANx_F10R2.FB6`) bit mask alias @def CAN_F10R2_FB6 */
#define CAN_F10R2_FB6				CAN_F10R2_FB6_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 7 (`CANx_F10R2.FB7`) bit position @def CAN_F10R2_FB7_Pos */
#define CAN_F10R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 10 word 2 bit 7 (`CANx_F10R2.FB7`) bit mask @def CAN_F10R2_FB7_Msk */
#define CAN_F10R2_FB7_Msk			REG_BIT_MASK(CAN_F10R2_FB7_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 7 (`CANx_F10R2.FB7`) bit mask alias @def CAN_F10R2_FB7 */
#define CAN_F10R2_FB7				CAN_F10R2_FB7_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 8 (`CANx_F10R2.FB8`) bit position @def CAN_F10R2_FB8_Pos */
#define CAN_F10R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 10 word 2 bit 8 (`CANx_F10R2.FB8`) bit mask @def CAN_F10R2_FB8_Msk */
#define CAN_F10R2_FB8_Msk			REG_BIT_MASK(CAN_F10R2_FB8_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 8 (`CANx_F10R2.FB8`) bit mask alias @def CAN_F10R2_FB8 */
#define CAN_F10R2_FB8				CAN_F10R2_FB8_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 9 (`CANx_F10R2.FB9`) bit position @def CAN_F10R2_FB9_Pos */
#define CAN_F10R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 10 word 2 bit 9 (`CANx_F10R2.FB9`) bit mask @def CAN_F10R2_FB9_Msk */
#define CAN_F10R2_FB9_Msk			REG_BIT_MASK(CAN_F10R2_FB9_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 9 (`CANx_F10R2.FB9`) bit mask alias @def CAN_F10R2_FB9 */
#define CAN_F10R2_FB9				CAN_F10R2_FB9_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 10 (`CANx_F10R2.FB10`) bit position @def CAN_F10R2_FB10_Pos */
#define CAN_F10R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 10 word 2 bit 10 (`CANx_F10R2.FB10`) bit mask @def CAN_F10R2_FB10_Msk */
#define CAN_F10R2_FB10_Msk			REG_BIT_MASK(CAN_F10R2_FB10_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 10 (`CANx_F10R2.FB10`) bit mask alias @def CAN_F10R2_FB10 */
#define CAN_F10R2_FB10				CAN_F10R2_FB10_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 11 (`CANx_F10R2.FB11`) bit position @def CAN_F10R2_FB11_Pos */
#define CAN_F10R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 10 word 2 bit 11 (`CANx_F10R2.FB11`) bit mask @def CAN_F10R2_FB11_Msk */
#define CAN_F10R2_FB11_Msk			REG_BIT_MASK(CAN_F10R2_FB11_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 11 (`CANx_F10R2.FB11`) bit mask alias @def CAN_F10R2_FB11 */
#define CAN_F10R2_FB11				CAN_F10R2_FB11_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 12 (`CANx_F10R2.FB12`) bit position @def CAN_F10R2_FB12_Pos */
#define CAN_F10R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 10 word 2 bit 12 (`CANx_F10R2.FB12`) bit mask @def CAN_F10R2_FB12_Msk */
#define CAN_F10R2_FB12_Msk			REG_BIT_MASK(CAN_F10R2_FB12_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 12 (`CANx_F10R2.FB12`) bit mask alias @def CAN_F10R2_FB12 */
#define CAN_F10R2_FB12				CAN_F10R2_FB12_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 13 (`CANx_F10R2.FB13`) bit position @def CAN_F10R2_FB13_Pos */
#define CAN_F10R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 10 word 2 bit 13 (`CANx_F10R2.FB13`) bit mask @def CAN_F10R2_FB13_Msk */
#define CAN_F10R2_FB13_Msk			REG_BIT_MASK(CAN_F10R2_FB13_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 13 (`CANx_F10R2.FB13`) bit mask alias @def CAN_F10R2_FB13 */
#define CAN_F10R2_FB13				CAN_F10R2_FB13_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 14 (`CANx_F10R2.FB14`) bit position @def CAN_F10R2_FB14_Pos */
#define CAN_F10R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 10 word 2 bit 14 (`CANx_F10R2.FB14`) bit mask @def CAN_F10R2_FB14_Msk */
#define CAN_F10R2_FB14_Msk			REG_BIT_MASK(CAN_F10R2_FB14_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 14 (`CANx_F10R2.FB14`) bit mask alias @def CAN_F10R2_FB14 */
#define CAN_F10R2_FB14				CAN_F10R2_FB14_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 15 (`CANx_F10R2.FB15`) bit position @def CAN_F10R2_FB15_Pos */
#define CAN_F10R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 10 word 2 bit 15 (`CANx_F10R2.FB15`) bit mask @def CAN_F10R2_FB15_Msk */
#define CAN_F10R2_FB15_Msk			REG_BIT_MASK(CAN_F10R2_FB15_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 15 (`CANx_F10R2.FB15`) bit mask alias @def CAN_F10R2_FB15 */
#define CAN_F10R2_FB15				CAN_F10R2_FB15_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 16 (`CANx_F10R2.FB16`) bit position @def CAN_F10R2_FB16_Pos */
#define CAN_F10R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 10 word 2 bit 16 (`CANx_F10R2.FB16`) bit mask @def CAN_F10R2_FB16_Msk */
#define CAN_F10R2_FB16_Msk			REG_BIT_MASK(CAN_F10R2_FB16_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 16 (`CANx_F10R2.FB16`) bit mask alias @def CAN_F10R2_FB16 */
#define CAN_F10R2_FB16				CAN_F10R2_FB16_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 17 (`CANx_F10R2.FB17`) bit position @def CAN_F10R2_FB17_Pos */
#define CAN_F10R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 10 word 2 bit 17 (`CANx_F10R2.FB17`) bit mask @def CAN_F10R2_FB17_Msk */
#define CAN_F10R2_FB17_Msk			REG_BIT_MASK(CAN_F10R2_FB17_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 17 (`CANx_F10R2.FB17`) bit mask alias @def CAN_F10R2_FB17 */
#define CAN_F10R2_FB17				CAN_F10R2_FB17_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 18 (`CANx_F10R2.FB18`) bit position @def CAN_F10R2_FB18_Pos */
#define CAN_F10R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 10 word 2 bit 18 (`CANx_F10R2.FB18`) bit mask @def CAN_F10R2_FB18_Msk */
#define CAN_F10R2_FB18_Msk			REG_BIT_MASK(CAN_F10R2_FB18_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 18 (`CANx_F10R2.FB18`) bit mask alias @def CAN_F10R2_FB18 */
#define CAN_F10R2_FB18				CAN_F10R2_FB18_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 19 (`CANx_F10R2.FB19`) bit position @def CAN_F10R2_FB19_Pos */
#define CAN_F10R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 10 word 2 bit 19 (`CANx_F10R2.FB19`) bit mask @def CAN_F10R2_FB19_Msk */
#define CAN_F10R2_FB19_Msk			REG_BIT_MASK(CAN_F10R2_FB19_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 19 (`CANx_F10R2.FB19`) bit mask alias @def CAN_F10R2_FB19 */
#define CAN_F10R2_FB19				CAN_F10R2_FB19_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 20 (`CANx_F10R2.FB20`) bit position @def CAN_F10R2_FB20_Pos */
#define CAN_F10R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 10 word 2 bit 20 (`CANx_F10R2.FB20`) bit mask @def CAN_F10R2_FB20_Msk */
#define CAN_F10R2_FB20_Msk			REG_BIT_MASK(CAN_F10R2_FB20_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 20 (`CANx_F10R2.FB20`) bit mask alias @def CAN_F10R2_FB20 */
#define CAN_F10R2_FB20				CAN_F10R2_FB20_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 21 (`CANx_F10R2.FB21`) bit position @def CAN_F10R2_FB21_Pos */
#define CAN_F10R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 10 word 2 bit 21 (`CANx_F10R2.FB21`) bit mask @def CAN_F10R2_FB21_Msk */
#define CAN_F10R2_FB21_Msk			REG_BIT_MASK(CAN_F10R2_FB21_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 21 (`CANx_F10R2.FB21`) bit mask alias @def CAN_F10R2_FB21 */
#define CAN_F10R2_FB21				CAN_F10R2_FB21_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 22 (`CANx_F10R2.FB22`) bit position @def CAN_F10R2_FB22_Pos */
#define CAN_F10R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 10 word 2 bit 22 (`CANx_F10R2.FB22`) bit mask @def CAN_F10R2_FB22_Msk */
#define CAN_F10R2_FB22_Msk			REG_BIT_MASK(CAN_F10R2_FB22_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 22 (`CANx_F10R2.FB22`) bit mask alias @def CAN_F10R2_FB22 */
#define CAN_F10R2_FB22				CAN_F10R2_FB22_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 23 (`CANx_F10R2.FB23`) bit position @def CAN_F10R2_FB23_Pos */
#define CAN_F10R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 10 word 2 bit 23 (`CANx_F10R2.FB23`) bit mask @def CAN_F10R2_FB23_Msk */
#define CAN_F10R2_FB23_Msk			REG_BIT_MASK(CAN_F10R2_FB23_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 23 (`CANx_F10R2.FB23`) bit mask alias @def CAN_F10R2_FB23 */
#define CAN_F10R2_FB23				CAN_F10R2_FB23_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 24 (`CANx_F10R2.FB24`) bit position @def CAN_F10R2_FB24_Pos */
#define CAN_F10R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 10 word 2 bit 24 (`CANx_F10R2.FB24`) bit mask @def CAN_F10R2_FB24_Msk */
#define CAN_F10R2_FB24_Msk			REG_BIT_MASK(CAN_F10R2_FB24_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 24 (`CANx_F10R2.FB24`) bit mask alias @def CAN_F10R2_FB24 */
#define CAN_F10R2_FB24				CAN_F10R2_FB24_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 25 (`CANx_F10R2.FB25`) bit position @def CAN_F10R2_FB25_Pos */
#define CAN_F10R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 10 word 2 bit 25 (`CANx_F10R2.FB25`) bit mask @def CAN_F10R2_FB25_Msk */
#define CAN_F10R2_FB25_Msk			REG_BIT_MASK(CAN_F10R2_FB25_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 25 (`CANx_F10R2.FB25`) bit mask alias @def CAN_F10R2_FB25 */
#define CAN_F10R2_FB25				CAN_F10R2_FB25_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 26 (`CANx_F10R2.FB26`) bit position @def CAN_F10R2_FB26_Pos */
#define CAN_F10R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 10 word 2 bit 26 (`CANx_F10R2.FB26`) bit mask @def CAN_F10R2_FB26_Msk */
#define CAN_F10R2_FB26_Msk			REG_BIT_MASK(CAN_F10R2_FB26_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 26 (`CANx_F10R2.FB26`) bit mask alias @def CAN_F10R2_FB26 */
#define CAN_F10R2_FB26				CAN_F10R2_FB26_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 27 (`CANx_F10R2.FB27`) bit position @def CAN_F10R2_FB27_Pos */
#define CAN_F10R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 10 word 2 bit 27 (`CANx_F10R2.FB27`) bit mask @def CAN_F10R2_FB27_Msk */
#define CAN_F10R2_FB27_Msk			REG_BIT_MASK(CAN_F10R2_FB27_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 27 (`CANx_F10R2.FB27`) bit mask alias @def CAN_F10R2_FB27 */
#define CAN_F10R2_FB27				CAN_F10R2_FB27_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 28 (`CANx_F10R2.FB28`) bit position @def CAN_F10R2_FB28_Pos */
#define CAN_F10R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 10 word 2 bit 28 (`CANx_F10R2.FB28`) bit mask @def CAN_F10R2_FB28_Msk */
#define CAN_F10R2_FB28_Msk			REG_BIT_MASK(CAN_F10R2_FB28_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 28 (`CANx_F10R2.FB28`) bit mask alias @def CAN_F10R2_FB28 */
#define CAN_F10R2_FB28				CAN_F10R2_FB28_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 29 (`CANx_F10R2.FB29`) bit position @def CAN_F10R2_FB29_Pos */
#define CAN_F10R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 10 word 2 bit 29 (`CANx_F10R2.FB29`) bit mask @def CAN_F10R2_FB29_Msk */
#define CAN_F10R2_FB29_Msk			REG_BIT_MASK(CAN_F10R2_FB29_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 29 (`CANx_F10R2.FB29`) bit mask alias @def CAN_F10R2_FB29 */
#define CAN_F10R2_FB29				CAN_F10R2_FB29_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 30 (`CANx_F10R2.FB30`) bit position @def CAN_F10R2_FB30_Pos */
#define CAN_F10R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 10 word 2 bit 30 (`CANx_F10R2.FB30`) bit mask @def CAN_F10R2_FB30_Msk */
#define CAN_F10R2_FB30_Msk			REG_BIT_MASK(CAN_F10R2_FB30_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 30 (`CANx_F10R2.FB30`) bit mask alias @def CAN_F10R2_FB30 */
#define CAN_F10R2_FB30				CAN_F10R2_FB30_Msk

/** @brief Acceptance-filter bank 10 word 2 bit 31 (`CANx_F10R2.FB31`) bit position @def CAN_F10R2_FB31_Pos */
#define CAN_F10R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 10 word 2 bit 31 (`CANx_F10R2.FB31`) bit mask @def CAN_F10R2_FB31_Msk */
#define CAN_F10R2_FB31_Msk			REG_BIT_MASK(CAN_F10R2_FB31_Pos)
/** @brief Acceptance-filter bank 10 word 2 bit 31 (`CANx_F10R2.FB31`) bit mask alias @def CAN_F10R2_FB31 */
#define CAN_F10R2_FB31				CAN_F10R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F11R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 11 word 2 bit 0 (`CANx_F11R2.FB0`) bit position @def CAN_F11R2_FB0_Pos */
#define CAN_F11R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 11 word 2 bit 0 (`CANx_F11R2.FB0`) bit mask @def CAN_F11R2_FB0_Msk */
#define CAN_F11R2_FB0_Msk			REG_BIT_MASK(CAN_F11R2_FB0_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 0 (`CANx_F11R2.FB0`) bit mask alias @def CAN_F11R2_FB0 */
#define CAN_F11R2_FB0				CAN_F11R2_FB0_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 1 (`CANx_F11R2.FB1`) bit position @def CAN_F11R2_FB1_Pos */
#define CAN_F11R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 11 word 2 bit 1 (`CANx_F11R2.FB1`) bit mask @def CAN_F11R2_FB1_Msk */
#define CAN_F11R2_FB1_Msk			REG_BIT_MASK(CAN_F11R2_FB1_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 1 (`CANx_F11R2.FB1`) bit mask alias @def CAN_F11R2_FB1 */
#define CAN_F11R2_FB1				CAN_F11R2_FB1_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 2 (`CANx_F11R2.FB2`) bit position @def CAN_F11R2_FB2_Pos */
#define CAN_F11R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 11 word 2 bit 2 (`CANx_F11R2.FB2`) bit mask @def CAN_F11R2_FB2_Msk */
#define CAN_F11R2_FB2_Msk			REG_BIT_MASK(CAN_F11R2_FB2_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 2 (`CANx_F11R2.FB2`) bit mask alias @def CAN_F11R2_FB2 */
#define CAN_F11R2_FB2				CAN_F11R2_FB2_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 3 (`CANx_F11R2.FB3`) bit position @def CAN_F11R2_FB3_Pos */
#define CAN_F11R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 11 word 2 bit 3 (`CANx_F11R2.FB3`) bit mask @def CAN_F11R2_FB3_Msk */
#define CAN_F11R2_FB3_Msk			REG_BIT_MASK(CAN_F11R2_FB3_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 3 (`CANx_F11R2.FB3`) bit mask alias @def CAN_F11R2_FB3 */
#define CAN_F11R2_FB3				CAN_F11R2_FB3_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 4 (`CANx_F11R2.FB4`) bit position @def CAN_F11R2_FB4_Pos */
#define CAN_F11R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 11 word 2 bit 4 (`CANx_F11R2.FB4`) bit mask @def CAN_F11R2_FB4_Msk */
#define CAN_F11R2_FB4_Msk			REG_BIT_MASK(CAN_F11R2_FB4_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 4 (`CANx_F11R2.FB4`) bit mask alias @def CAN_F11R2_FB4 */
#define CAN_F11R2_FB4				CAN_F11R2_FB4_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 5 (`CANx_F11R2.FB5`) bit position @def CAN_F11R2_FB5_Pos */
#define CAN_F11R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 11 word 2 bit 5 (`CANx_F11R2.FB5`) bit mask @def CAN_F11R2_FB5_Msk */
#define CAN_F11R2_FB5_Msk			REG_BIT_MASK(CAN_F11R2_FB5_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 5 (`CANx_F11R2.FB5`) bit mask alias @def CAN_F11R2_FB5 */
#define CAN_F11R2_FB5				CAN_F11R2_FB5_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 6 (`CANx_F11R2.FB6`) bit position @def CAN_F11R2_FB6_Pos */
#define CAN_F11R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 11 word 2 bit 6 (`CANx_F11R2.FB6`) bit mask @def CAN_F11R2_FB6_Msk */
#define CAN_F11R2_FB6_Msk			REG_BIT_MASK(CAN_F11R2_FB6_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 6 (`CANx_F11R2.FB6`) bit mask alias @def CAN_F11R2_FB6 */
#define CAN_F11R2_FB6				CAN_F11R2_FB6_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 7 (`CANx_F11R2.FB7`) bit position @def CAN_F11R2_FB7_Pos */
#define CAN_F11R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 11 word 2 bit 7 (`CANx_F11R2.FB7`) bit mask @def CAN_F11R2_FB7_Msk */
#define CAN_F11R2_FB7_Msk			REG_BIT_MASK(CAN_F11R2_FB7_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 7 (`CANx_F11R2.FB7`) bit mask alias @def CAN_F11R2_FB7 */
#define CAN_F11R2_FB7				CAN_F11R2_FB7_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 8 (`CANx_F11R2.FB8`) bit position @def CAN_F11R2_FB8_Pos */
#define CAN_F11R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 11 word 2 bit 8 (`CANx_F11R2.FB8`) bit mask @def CAN_F11R2_FB8_Msk */
#define CAN_F11R2_FB8_Msk			REG_BIT_MASK(CAN_F11R2_FB8_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 8 (`CANx_F11R2.FB8`) bit mask alias @def CAN_F11R2_FB8 */
#define CAN_F11R2_FB8				CAN_F11R2_FB8_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 9 (`CANx_F11R2.FB9`) bit position @def CAN_F11R2_FB9_Pos */
#define CAN_F11R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 11 word 2 bit 9 (`CANx_F11R2.FB9`) bit mask @def CAN_F11R2_FB9_Msk */
#define CAN_F11R2_FB9_Msk			REG_BIT_MASK(CAN_F11R2_FB9_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 9 (`CANx_F11R2.FB9`) bit mask alias @def CAN_F11R2_FB9 */
#define CAN_F11R2_FB9				CAN_F11R2_FB9_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 10 (`CANx_F11R2.FB10`) bit position @def CAN_F11R2_FB10_Pos */
#define CAN_F11R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 11 word 2 bit 10 (`CANx_F11R2.FB10`) bit mask @def CAN_F11R2_FB10_Msk */
#define CAN_F11R2_FB10_Msk			REG_BIT_MASK(CAN_F11R2_FB10_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 10 (`CANx_F11R2.FB10`) bit mask alias @def CAN_F11R2_FB10 */
#define CAN_F11R2_FB10				CAN_F11R2_FB10_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 11 (`CANx_F11R2.FB11`) bit position @def CAN_F11R2_FB11_Pos */
#define CAN_F11R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 11 word 2 bit 11 (`CANx_F11R2.FB11`) bit mask @def CAN_F11R2_FB11_Msk */
#define CAN_F11R2_FB11_Msk			REG_BIT_MASK(CAN_F11R2_FB11_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 11 (`CANx_F11R2.FB11`) bit mask alias @def CAN_F11R2_FB11 */
#define CAN_F11R2_FB11				CAN_F11R2_FB11_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 12 (`CANx_F11R2.FB12`) bit position @def CAN_F11R2_FB12_Pos */
#define CAN_F11R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 11 word 2 bit 12 (`CANx_F11R2.FB12`) bit mask @def CAN_F11R2_FB12_Msk */
#define CAN_F11R2_FB12_Msk			REG_BIT_MASK(CAN_F11R2_FB12_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 12 (`CANx_F11R2.FB12`) bit mask alias @def CAN_F11R2_FB12 */
#define CAN_F11R2_FB12				CAN_F11R2_FB12_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 13 (`CANx_F11R2.FB13`) bit position @def CAN_F11R2_FB13_Pos */
#define CAN_F11R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 11 word 2 bit 13 (`CANx_F11R2.FB13`) bit mask @def CAN_F11R2_FB13_Msk */
#define CAN_F11R2_FB13_Msk			REG_BIT_MASK(CAN_F11R2_FB13_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 13 (`CANx_F11R2.FB13`) bit mask alias @def CAN_F11R2_FB13 */
#define CAN_F11R2_FB13				CAN_F11R2_FB13_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 14 (`CANx_F11R2.FB14`) bit position @def CAN_F11R2_FB14_Pos */
#define CAN_F11R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 11 word 2 bit 14 (`CANx_F11R2.FB14`) bit mask @def CAN_F11R2_FB14_Msk */
#define CAN_F11R2_FB14_Msk			REG_BIT_MASK(CAN_F11R2_FB14_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 14 (`CANx_F11R2.FB14`) bit mask alias @def CAN_F11R2_FB14 */
#define CAN_F11R2_FB14				CAN_F11R2_FB14_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 15 (`CANx_F11R2.FB15`) bit position @def CAN_F11R2_FB15_Pos */
#define CAN_F11R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 11 word 2 bit 15 (`CANx_F11R2.FB15`) bit mask @def CAN_F11R2_FB15_Msk */
#define CAN_F11R2_FB15_Msk			REG_BIT_MASK(CAN_F11R2_FB15_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 15 (`CANx_F11R2.FB15`) bit mask alias @def CAN_F11R2_FB15 */
#define CAN_F11R2_FB15				CAN_F11R2_FB15_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 16 (`CANx_F11R2.FB16`) bit position @def CAN_F11R2_FB16_Pos */
#define CAN_F11R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 11 word 2 bit 16 (`CANx_F11R2.FB16`) bit mask @def CAN_F11R2_FB16_Msk */
#define CAN_F11R2_FB16_Msk			REG_BIT_MASK(CAN_F11R2_FB16_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 16 (`CANx_F11R2.FB16`) bit mask alias @def CAN_F11R2_FB16 */
#define CAN_F11R2_FB16				CAN_F11R2_FB16_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 17 (`CANx_F11R2.FB17`) bit position @def CAN_F11R2_FB17_Pos */
#define CAN_F11R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 11 word 2 bit 17 (`CANx_F11R2.FB17`) bit mask @def CAN_F11R2_FB17_Msk */
#define CAN_F11R2_FB17_Msk			REG_BIT_MASK(CAN_F11R2_FB17_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 17 (`CANx_F11R2.FB17`) bit mask alias @def CAN_F11R2_FB17 */
#define CAN_F11R2_FB17				CAN_F11R2_FB17_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 18 (`CANx_F11R2.FB18`) bit position @def CAN_F11R2_FB18_Pos */
#define CAN_F11R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 11 word 2 bit 18 (`CANx_F11R2.FB18`) bit mask @def CAN_F11R2_FB18_Msk */
#define CAN_F11R2_FB18_Msk			REG_BIT_MASK(CAN_F11R2_FB18_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 18 (`CANx_F11R2.FB18`) bit mask alias @def CAN_F11R2_FB18 */
#define CAN_F11R2_FB18				CAN_F11R2_FB18_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 19 (`CANx_F11R2.FB19`) bit position @def CAN_F11R2_FB19_Pos */
#define CAN_F11R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 11 word 2 bit 19 (`CANx_F11R2.FB19`) bit mask @def CAN_F11R2_FB19_Msk */
#define CAN_F11R2_FB19_Msk			REG_BIT_MASK(CAN_F11R2_FB19_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 19 (`CANx_F11R2.FB19`) bit mask alias @def CAN_F11R2_FB19 */
#define CAN_F11R2_FB19				CAN_F11R2_FB19_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 20 (`CANx_F11R2.FB20`) bit position @def CAN_F11R2_FB20_Pos */
#define CAN_F11R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 11 word 2 bit 20 (`CANx_F11R2.FB20`) bit mask @def CAN_F11R2_FB20_Msk */
#define CAN_F11R2_FB20_Msk			REG_BIT_MASK(CAN_F11R2_FB20_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 20 (`CANx_F11R2.FB20`) bit mask alias @def CAN_F11R2_FB20 */
#define CAN_F11R2_FB20				CAN_F11R2_FB20_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 21 (`CANx_F11R2.FB21`) bit position @def CAN_F11R2_FB21_Pos */
#define CAN_F11R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 11 word 2 bit 21 (`CANx_F11R2.FB21`) bit mask @def CAN_F11R2_FB21_Msk */
#define CAN_F11R2_FB21_Msk			REG_BIT_MASK(CAN_F11R2_FB21_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 21 (`CANx_F11R2.FB21`) bit mask alias @def CAN_F11R2_FB21 */
#define CAN_F11R2_FB21				CAN_F11R2_FB21_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 22 (`CANx_F11R2.FB22`) bit position @def CAN_F11R2_FB22_Pos */
#define CAN_F11R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 11 word 2 bit 22 (`CANx_F11R2.FB22`) bit mask @def CAN_F11R2_FB22_Msk */
#define CAN_F11R2_FB22_Msk			REG_BIT_MASK(CAN_F11R2_FB22_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 22 (`CANx_F11R2.FB22`) bit mask alias @def CAN_F11R2_FB22 */
#define CAN_F11R2_FB22				CAN_F11R2_FB22_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 23 (`CANx_F11R2.FB23`) bit position @def CAN_F11R2_FB23_Pos */
#define CAN_F11R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 11 word 2 bit 23 (`CANx_F11R2.FB23`) bit mask @def CAN_F11R2_FB23_Msk */
#define CAN_F11R2_FB23_Msk			REG_BIT_MASK(CAN_F11R2_FB23_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 23 (`CANx_F11R2.FB23`) bit mask alias @def CAN_F11R2_FB23 */
#define CAN_F11R2_FB23				CAN_F11R2_FB23_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 24 (`CANx_F11R2.FB24`) bit position @def CAN_F11R2_FB24_Pos */
#define CAN_F11R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 11 word 2 bit 24 (`CANx_F11R2.FB24`) bit mask @def CAN_F11R2_FB24_Msk */
#define CAN_F11R2_FB24_Msk			REG_BIT_MASK(CAN_F11R2_FB24_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 24 (`CANx_F11R2.FB24`) bit mask alias @def CAN_F11R2_FB24 */
#define CAN_F11R2_FB24				CAN_F11R2_FB24_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 25 (`CANx_F11R2.FB25`) bit position @def CAN_F11R2_FB25_Pos */
#define CAN_F11R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 11 word 2 bit 25 (`CANx_F11R2.FB25`) bit mask @def CAN_F11R2_FB25_Msk */
#define CAN_F11R2_FB25_Msk			REG_BIT_MASK(CAN_F11R2_FB25_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 25 (`CANx_F11R2.FB25`) bit mask alias @def CAN_F11R2_FB25 */
#define CAN_F11R2_FB25				CAN_F11R2_FB25_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 26 (`CANx_F11R2.FB26`) bit position @def CAN_F11R2_FB26_Pos */
#define CAN_F11R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 11 word 2 bit 26 (`CANx_F11R2.FB26`) bit mask @def CAN_F11R2_FB26_Msk */
#define CAN_F11R2_FB26_Msk			REG_BIT_MASK(CAN_F11R2_FB26_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 26 (`CANx_F11R2.FB26`) bit mask alias @def CAN_F11R2_FB26 */
#define CAN_F11R2_FB26				CAN_F11R2_FB26_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 27 (`CANx_F11R2.FB27`) bit position @def CAN_F11R2_FB27_Pos */
#define CAN_F11R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 11 word 2 bit 27 (`CANx_F11R2.FB27`) bit mask @def CAN_F11R2_FB27_Msk */
#define CAN_F11R2_FB27_Msk			REG_BIT_MASK(CAN_F11R2_FB27_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 27 (`CANx_F11R2.FB27`) bit mask alias @def CAN_F11R2_FB27 */
#define CAN_F11R2_FB27				CAN_F11R2_FB27_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 28 (`CANx_F11R2.FB28`) bit position @def CAN_F11R2_FB28_Pos */
#define CAN_F11R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 11 word 2 bit 28 (`CANx_F11R2.FB28`) bit mask @def CAN_F11R2_FB28_Msk */
#define CAN_F11R2_FB28_Msk			REG_BIT_MASK(CAN_F11R2_FB28_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 28 (`CANx_F11R2.FB28`) bit mask alias @def CAN_F11R2_FB28 */
#define CAN_F11R2_FB28				CAN_F11R2_FB28_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 29 (`CANx_F11R2.FB29`) bit position @def CAN_F11R2_FB29_Pos */
#define CAN_F11R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 11 word 2 bit 29 (`CANx_F11R2.FB29`) bit mask @def CAN_F11R2_FB29_Msk */
#define CAN_F11R2_FB29_Msk			REG_BIT_MASK(CAN_F11R2_FB29_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 29 (`CANx_F11R2.FB29`) bit mask alias @def CAN_F11R2_FB29 */
#define CAN_F11R2_FB29				CAN_F11R2_FB29_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 30 (`CANx_F11R2.FB30`) bit position @def CAN_F11R2_FB30_Pos */
#define CAN_F11R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 11 word 2 bit 30 (`CANx_F11R2.FB30`) bit mask @def CAN_F11R2_FB30_Msk */
#define CAN_F11R2_FB30_Msk			REG_BIT_MASK(CAN_F11R2_FB30_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 30 (`CANx_F11R2.FB30`) bit mask alias @def CAN_F11R2_FB30 */
#define CAN_F11R2_FB30				CAN_F11R2_FB30_Msk

/** @brief Acceptance-filter bank 11 word 2 bit 31 (`CANx_F11R2.FB31`) bit position @def CAN_F11R2_FB31_Pos */
#define CAN_F11R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 11 word 2 bit 31 (`CANx_F11R2.FB31`) bit mask @def CAN_F11R2_FB31_Msk */
#define CAN_F11R2_FB31_Msk			REG_BIT_MASK(CAN_F11R2_FB31_Pos)
/** @brief Acceptance-filter bank 11 word 2 bit 31 (`CANx_F11R2.FB31`) bit mask alias @def CAN_F11R2_FB31 */
#define CAN_F11R2_FB31				CAN_F11R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F12R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 12 word 2 bit 0 (`CANx_F12R2.FB0`) bit position @def CAN_F12R2_FB0_Pos */
#define CAN_F12R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 12 word 2 bit 0 (`CANx_F12R2.FB0`) bit mask @def CAN_F12R2_FB0_Msk */
#define CAN_F12R2_FB0_Msk			REG_BIT_MASK(CAN_F12R2_FB0_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 0 (`CANx_F12R2.FB0`) bit mask alias @def CAN_F12R2_FB0 */
#define CAN_F12R2_FB0				CAN_F12R2_FB0_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 1 (`CANx_F12R2.FB1`) bit position @def CAN_F12R2_FB1_Pos */
#define CAN_F12R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 12 word 2 bit 1 (`CANx_F12R2.FB1`) bit mask @def CAN_F12R2_FB1_Msk */
#define CAN_F12R2_FB1_Msk			REG_BIT_MASK(CAN_F12R2_FB1_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 1 (`CANx_F12R2.FB1`) bit mask alias @def CAN_F12R2_FB1 */
#define CAN_F12R2_FB1				CAN_F12R2_FB1_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 2 (`CANx_F12R2.FB2`) bit position @def CAN_F12R2_FB2_Pos */
#define CAN_F12R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 12 word 2 bit 2 (`CANx_F12R2.FB2`) bit mask @def CAN_F12R2_FB2_Msk */
#define CAN_F12R2_FB2_Msk			REG_BIT_MASK(CAN_F12R2_FB2_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 2 (`CANx_F12R2.FB2`) bit mask alias @def CAN_F12R2_FB2 */
#define CAN_F12R2_FB2				CAN_F12R2_FB2_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 3 (`CANx_F12R2.FB3`) bit position @def CAN_F12R2_FB3_Pos */
#define CAN_F12R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 12 word 2 bit 3 (`CANx_F12R2.FB3`) bit mask @def CAN_F12R2_FB3_Msk */
#define CAN_F12R2_FB3_Msk			REG_BIT_MASK(CAN_F12R2_FB3_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 3 (`CANx_F12R2.FB3`) bit mask alias @def CAN_F12R2_FB3 */
#define CAN_F12R2_FB3				CAN_F12R2_FB3_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 4 (`CANx_F12R2.FB4`) bit position @def CAN_F12R2_FB4_Pos */
#define CAN_F12R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 12 word 2 bit 4 (`CANx_F12R2.FB4`) bit mask @def CAN_F12R2_FB4_Msk */
#define CAN_F12R2_FB4_Msk			REG_BIT_MASK(CAN_F12R2_FB4_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 4 (`CANx_F12R2.FB4`) bit mask alias @def CAN_F12R2_FB4 */
#define CAN_F12R2_FB4				CAN_F12R2_FB4_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 5 (`CANx_F12R2.FB5`) bit position @def CAN_F12R2_FB5_Pos */
#define CAN_F12R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 12 word 2 bit 5 (`CANx_F12R2.FB5`) bit mask @def CAN_F12R2_FB5_Msk */
#define CAN_F12R2_FB5_Msk			REG_BIT_MASK(CAN_F12R2_FB5_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 5 (`CANx_F12R2.FB5`) bit mask alias @def CAN_F12R2_FB5 */
#define CAN_F12R2_FB5				CAN_F12R2_FB5_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 6 (`CANx_F12R2.FB6`) bit position @def CAN_F12R2_FB6_Pos */
#define CAN_F12R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 12 word 2 bit 6 (`CANx_F12R2.FB6`) bit mask @def CAN_F12R2_FB6_Msk */
#define CAN_F12R2_FB6_Msk			REG_BIT_MASK(CAN_F12R2_FB6_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 6 (`CANx_F12R2.FB6`) bit mask alias @def CAN_F12R2_FB6 */
#define CAN_F12R2_FB6				CAN_F12R2_FB6_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 7 (`CANx_F12R2.FB7`) bit position @def CAN_F12R2_FB7_Pos */
#define CAN_F12R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 12 word 2 bit 7 (`CANx_F12R2.FB7`) bit mask @def CAN_F12R2_FB7_Msk */
#define CAN_F12R2_FB7_Msk			REG_BIT_MASK(CAN_F12R2_FB7_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 7 (`CANx_F12R2.FB7`) bit mask alias @def CAN_F12R2_FB7 */
#define CAN_F12R2_FB7				CAN_F12R2_FB7_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 8 (`CANx_F12R2.FB8`) bit position @def CAN_F12R2_FB8_Pos */
#define CAN_F12R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 12 word 2 bit 8 (`CANx_F12R2.FB8`) bit mask @def CAN_F12R2_FB8_Msk */
#define CAN_F12R2_FB8_Msk			REG_BIT_MASK(CAN_F12R2_FB8_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 8 (`CANx_F12R2.FB8`) bit mask alias @def CAN_F12R2_FB8 */
#define CAN_F12R2_FB8				CAN_F12R2_FB8_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 9 (`CANx_F12R2.FB9`) bit position @def CAN_F12R2_FB9_Pos */
#define CAN_F12R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 12 word 2 bit 9 (`CANx_F12R2.FB9`) bit mask @def CAN_F12R2_FB9_Msk */
#define CAN_F12R2_FB9_Msk			REG_BIT_MASK(CAN_F12R2_FB9_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 9 (`CANx_F12R2.FB9`) bit mask alias @def CAN_F12R2_FB9 */
#define CAN_F12R2_FB9				CAN_F12R2_FB9_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 10 (`CANx_F12R2.FB10`) bit position @def CAN_F12R2_FB10_Pos */
#define CAN_F12R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 12 word 2 bit 10 (`CANx_F12R2.FB10`) bit mask @def CAN_F12R2_FB10_Msk */
#define CAN_F12R2_FB10_Msk			REG_BIT_MASK(CAN_F12R2_FB10_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 10 (`CANx_F12R2.FB10`) bit mask alias @def CAN_F12R2_FB10 */
#define CAN_F12R2_FB10				CAN_F12R2_FB10_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 11 (`CANx_F12R2.FB11`) bit position @def CAN_F12R2_FB11_Pos */
#define CAN_F12R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 12 word 2 bit 11 (`CANx_F12R2.FB11`) bit mask @def CAN_F12R2_FB11_Msk */
#define CAN_F12R2_FB11_Msk			REG_BIT_MASK(CAN_F12R2_FB11_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 11 (`CANx_F12R2.FB11`) bit mask alias @def CAN_F12R2_FB11 */
#define CAN_F12R2_FB11				CAN_F12R2_FB11_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 12 (`CANx_F12R2.FB12`) bit position @def CAN_F12R2_FB12_Pos */
#define CAN_F12R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 12 word 2 bit 12 (`CANx_F12R2.FB12`) bit mask @def CAN_F12R2_FB12_Msk */
#define CAN_F12R2_FB12_Msk			REG_BIT_MASK(CAN_F12R2_FB12_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 12 (`CANx_F12R2.FB12`) bit mask alias @def CAN_F12R2_FB12 */
#define CAN_F12R2_FB12				CAN_F12R2_FB12_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 13 (`CANx_F12R2.FB13`) bit position @def CAN_F12R2_FB13_Pos */
#define CAN_F12R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 12 word 2 bit 13 (`CANx_F12R2.FB13`) bit mask @def CAN_F12R2_FB13_Msk */
#define CAN_F12R2_FB13_Msk			REG_BIT_MASK(CAN_F12R2_FB13_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 13 (`CANx_F12R2.FB13`) bit mask alias @def CAN_F12R2_FB13 */
#define CAN_F12R2_FB13				CAN_F12R2_FB13_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 14 (`CANx_F12R2.FB14`) bit position @def CAN_F12R2_FB14_Pos */
#define CAN_F12R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 12 word 2 bit 14 (`CANx_F12R2.FB14`) bit mask @def CAN_F12R2_FB14_Msk */
#define CAN_F12R2_FB14_Msk			REG_BIT_MASK(CAN_F12R2_FB14_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 14 (`CANx_F12R2.FB14`) bit mask alias @def CAN_F12R2_FB14 */
#define CAN_F12R2_FB14				CAN_F12R2_FB14_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 15 (`CANx_F12R2.FB15`) bit position @def CAN_F12R2_FB15_Pos */
#define CAN_F12R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 12 word 2 bit 15 (`CANx_F12R2.FB15`) bit mask @def CAN_F12R2_FB15_Msk */
#define CAN_F12R2_FB15_Msk			REG_BIT_MASK(CAN_F12R2_FB15_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 15 (`CANx_F12R2.FB15`) bit mask alias @def CAN_F12R2_FB15 */
#define CAN_F12R2_FB15				CAN_F12R2_FB15_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 16 (`CANx_F12R2.FB16`) bit position @def CAN_F12R2_FB16_Pos */
#define CAN_F12R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 12 word 2 bit 16 (`CANx_F12R2.FB16`) bit mask @def CAN_F12R2_FB16_Msk */
#define CAN_F12R2_FB16_Msk			REG_BIT_MASK(CAN_F12R2_FB16_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 16 (`CANx_F12R2.FB16`) bit mask alias @def CAN_F12R2_FB16 */
#define CAN_F12R2_FB16				CAN_F12R2_FB16_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 17 (`CANx_F12R2.FB17`) bit position @def CAN_F12R2_FB17_Pos */
#define CAN_F12R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 12 word 2 bit 17 (`CANx_F12R2.FB17`) bit mask @def CAN_F12R2_FB17_Msk */
#define CAN_F12R2_FB17_Msk			REG_BIT_MASK(CAN_F12R2_FB17_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 17 (`CANx_F12R2.FB17`) bit mask alias @def CAN_F12R2_FB17 */
#define CAN_F12R2_FB17				CAN_F12R2_FB17_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 18 (`CANx_F12R2.FB18`) bit position @def CAN_F12R2_FB18_Pos */
#define CAN_F12R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 12 word 2 bit 18 (`CANx_F12R2.FB18`) bit mask @def CAN_F12R2_FB18_Msk */
#define CAN_F12R2_FB18_Msk			REG_BIT_MASK(CAN_F12R2_FB18_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 18 (`CANx_F12R2.FB18`) bit mask alias @def CAN_F12R2_FB18 */
#define CAN_F12R2_FB18				CAN_F12R2_FB18_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 19 (`CANx_F12R2.FB19`) bit position @def CAN_F12R2_FB19_Pos */
#define CAN_F12R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 12 word 2 bit 19 (`CANx_F12R2.FB19`) bit mask @def CAN_F12R2_FB19_Msk */
#define CAN_F12R2_FB19_Msk			REG_BIT_MASK(CAN_F12R2_FB19_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 19 (`CANx_F12R2.FB19`) bit mask alias @def CAN_F12R2_FB19 */
#define CAN_F12R2_FB19				CAN_F12R2_FB19_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 20 (`CANx_F12R2.FB20`) bit position @def CAN_F12R2_FB20_Pos */
#define CAN_F12R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 12 word 2 bit 20 (`CANx_F12R2.FB20`) bit mask @def CAN_F12R2_FB20_Msk */
#define CAN_F12R2_FB20_Msk			REG_BIT_MASK(CAN_F12R2_FB20_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 20 (`CANx_F12R2.FB20`) bit mask alias @def CAN_F12R2_FB20 */
#define CAN_F12R2_FB20				CAN_F12R2_FB20_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 21 (`CANx_F12R2.FB21`) bit position @def CAN_F12R2_FB21_Pos */
#define CAN_F12R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 12 word 2 bit 21 (`CANx_F12R2.FB21`) bit mask @def CAN_F12R2_FB21_Msk */
#define CAN_F12R2_FB21_Msk			REG_BIT_MASK(CAN_F12R2_FB21_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 21 (`CANx_F12R2.FB21`) bit mask alias @def CAN_F12R2_FB21 */
#define CAN_F12R2_FB21				CAN_F12R2_FB21_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 22 (`CANx_F12R2.FB22`) bit position @def CAN_F12R2_FB22_Pos */
#define CAN_F12R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 12 word 2 bit 22 (`CANx_F12R2.FB22`) bit mask @def CAN_F12R2_FB22_Msk */
#define CAN_F12R2_FB22_Msk			REG_BIT_MASK(CAN_F12R2_FB22_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 22 (`CANx_F12R2.FB22`) bit mask alias @def CAN_F12R2_FB22 */
#define CAN_F12R2_FB22				CAN_F12R2_FB22_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 23 (`CANx_F12R2.FB23`) bit position @def CAN_F12R2_FB23_Pos */
#define CAN_F12R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 12 word 2 bit 23 (`CANx_F12R2.FB23`) bit mask @def CAN_F12R2_FB23_Msk */
#define CAN_F12R2_FB23_Msk			REG_BIT_MASK(CAN_F12R2_FB23_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 23 (`CANx_F12R2.FB23`) bit mask alias @def CAN_F12R2_FB23 */
#define CAN_F12R2_FB23				CAN_F12R2_FB23_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 24 (`CANx_F12R2.FB24`) bit position @def CAN_F12R2_FB24_Pos */
#define CAN_F12R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 12 word 2 bit 24 (`CANx_F12R2.FB24`) bit mask @def CAN_F12R2_FB24_Msk */
#define CAN_F12R2_FB24_Msk			REG_BIT_MASK(CAN_F12R2_FB24_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 24 (`CANx_F12R2.FB24`) bit mask alias @def CAN_F12R2_FB24 */
#define CAN_F12R2_FB24				CAN_F12R2_FB24_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 25 (`CANx_F12R2.FB25`) bit position @def CAN_F12R2_FB25_Pos */
#define CAN_F12R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 12 word 2 bit 25 (`CANx_F12R2.FB25`) bit mask @def CAN_F12R2_FB25_Msk */
#define CAN_F12R2_FB25_Msk			REG_BIT_MASK(CAN_F12R2_FB25_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 25 (`CANx_F12R2.FB25`) bit mask alias @def CAN_F12R2_FB25 */
#define CAN_F12R2_FB25				CAN_F12R2_FB25_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 26 (`CANx_F12R2.FB26`) bit position @def CAN_F12R2_FB26_Pos */
#define CAN_F12R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 12 word 2 bit 26 (`CANx_F12R2.FB26`) bit mask @def CAN_F12R2_FB26_Msk */
#define CAN_F12R2_FB26_Msk			REG_BIT_MASK(CAN_F12R2_FB26_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 26 (`CANx_F12R2.FB26`) bit mask alias @def CAN_F12R2_FB26 */
#define CAN_F12R2_FB26				CAN_F12R2_FB26_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 27 (`CANx_F12R2.FB27`) bit position @def CAN_F12R2_FB27_Pos */
#define CAN_F12R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 12 word 2 bit 27 (`CANx_F12R2.FB27`) bit mask @def CAN_F12R2_FB27_Msk */
#define CAN_F12R2_FB27_Msk			REG_BIT_MASK(CAN_F12R2_FB27_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 27 (`CANx_F12R2.FB27`) bit mask alias @def CAN_F12R2_FB27 */
#define CAN_F12R2_FB27				CAN_F12R2_FB27_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 28 (`CANx_F12R2.FB28`) bit position @def CAN_F12R2_FB28_Pos */
#define CAN_F12R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 12 word 2 bit 28 (`CANx_F12R2.FB28`) bit mask @def CAN_F12R2_FB28_Msk */
#define CAN_F12R2_FB28_Msk			REG_BIT_MASK(CAN_F12R2_FB28_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 28 (`CANx_F12R2.FB28`) bit mask alias @def CAN_F12R2_FB28 */
#define CAN_F12R2_FB28				CAN_F12R2_FB28_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 29 (`CANx_F12R2.FB29`) bit position @def CAN_F12R2_FB29_Pos */
#define CAN_F12R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 12 word 2 bit 29 (`CANx_F12R2.FB29`) bit mask @def CAN_F12R2_FB29_Msk */
#define CAN_F12R2_FB29_Msk			REG_BIT_MASK(CAN_F12R2_FB29_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 29 (`CANx_F12R2.FB29`) bit mask alias @def CAN_F12R2_FB29 */
#define CAN_F12R2_FB29				CAN_F12R2_FB29_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 30 (`CANx_F12R2.FB30`) bit position @def CAN_F12R2_FB30_Pos */
#define CAN_F12R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 12 word 2 bit 30 (`CANx_F12R2.FB30`) bit mask @def CAN_F12R2_FB30_Msk */
#define CAN_F12R2_FB30_Msk			REG_BIT_MASK(CAN_F12R2_FB30_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 30 (`CANx_F12R2.FB30`) bit mask alias @def CAN_F12R2_FB30 */
#define CAN_F12R2_FB30				CAN_F12R2_FB30_Msk

/** @brief Acceptance-filter bank 12 word 2 bit 31 (`CANx_F12R2.FB31`) bit position @def CAN_F12R2_FB31_Pos */
#define CAN_F12R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 12 word 2 bit 31 (`CANx_F12R2.FB31`) bit mask @def CAN_F12R2_FB31_Msk */
#define CAN_F12R2_FB31_Msk			REG_BIT_MASK(CAN_F12R2_FB31_Pos)
/** @brief Acceptance-filter bank 12 word 2 bit 31 (`CANx_F12R2.FB31`) bit mask alias @def CAN_F12R2_FB31 */
#define CAN_F12R2_FB31				CAN_F12R2_FB31_Msk

// ---------------------------------------------------------------------------------------------------- //
// CAN_F13R2
// ---------------------------------------------------------------------------------------------------- //
/** @brief Acceptance-filter bank 13 word 2 bit 0 (`CANx_F13R2.FB0`) bit position @def CAN_F13R2_FB0_Pos */
#define CAN_F13R2_FB0_Pos			((reg_bit_pos_t) 0U)
/** @brief Acceptance-filter bank 13 word 2 bit 0 (`CANx_F13R2.FB0`) bit mask @def CAN_F13R2_FB0_Msk */
#define CAN_F13R2_FB0_Msk			REG_BIT_MASK(CAN_F13R2_FB0_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 0 (`CANx_F13R2.FB0`) bit mask alias @def CAN_F13R2_FB0 */
#define CAN_F13R2_FB0				CAN_F13R2_FB0_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 1 (`CANx_F13R2.FB1`) bit position @def CAN_F13R2_FB1_Pos */
#define CAN_F13R2_FB1_Pos			((reg_bit_pos_t) 1U)
/** @brief Acceptance-filter bank 13 word 2 bit 1 (`CANx_F13R2.FB1`) bit mask @def CAN_F13R2_FB1_Msk */
#define CAN_F13R2_FB1_Msk			REG_BIT_MASK(CAN_F13R2_FB1_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 1 (`CANx_F13R2.FB1`) bit mask alias @def CAN_F13R2_FB1 */
#define CAN_F13R2_FB1				CAN_F13R2_FB1_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 2 (`CANx_F13R2.FB2`) bit position @def CAN_F13R2_FB2_Pos */
#define CAN_F13R2_FB2_Pos			((reg_bit_pos_t) 2U)
/** @brief Acceptance-filter bank 13 word 2 bit 2 (`CANx_F13R2.FB2`) bit mask @def CAN_F13R2_FB2_Msk */
#define CAN_F13R2_FB2_Msk			REG_BIT_MASK(CAN_F13R2_FB2_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 2 (`CANx_F13R2.FB2`) bit mask alias @def CAN_F13R2_FB2 */
#define CAN_F13R2_FB2				CAN_F13R2_FB2_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 3 (`CANx_F13R2.FB3`) bit position @def CAN_F13R2_FB3_Pos */
#define CAN_F13R2_FB3_Pos			((reg_bit_pos_t) 3U)
/** @brief Acceptance-filter bank 13 word 2 bit 3 (`CANx_F13R2.FB3`) bit mask @def CAN_F13R2_FB3_Msk */
#define CAN_F13R2_FB3_Msk			REG_BIT_MASK(CAN_F13R2_FB3_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 3 (`CANx_F13R2.FB3`) bit mask alias @def CAN_F13R2_FB3 */
#define CAN_F13R2_FB3				CAN_F13R2_FB3_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 4 (`CANx_F13R2.FB4`) bit position @def CAN_F13R2_FB4_Pos */
#define CAN_F13R2_FB4_Pos			((reg_bit_pos_t) 4U)
/** @brief Acceptance-filter bank 13 word 2 bit 4 (`CANx_F13R2.FB4`) bit mask @def CAN_F13R2_FB4_Msk */
#define CAN_F13R2_FB4_Msk			REG_BIT_MASK(CAN_F13R2_FB4_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 4 (`CANx_F13R2.FB4`) bit mask alias @def CAN_F13R2_FB4 */
#define CAN_F13R2_FB4				CAN_F13R2_FB4_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 5 (`CANx_F13R2.FB5`) bit position @def CAN_F13R2_FB5_Pos */
#define CAN_F13R2_FB5_Pos			((reg_bit_pos_t) 5U)
/** @brief Acceptance-filter bank 13 word 2 bit 5 (`CANx_F13R2.FB5`) bit mask @def CAN_F13R2_FB5_Msk */
#define CAN_F13R2_FB5_Msk			REG_BIT_MASK(CAN_F13R2_FB5_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 5 (`CANx_F13R2.FB5`) bit mask alias @def CAN_F13R2_FB5 */
#define CAN_F13R2_FB5				CAN_F13R2_FB5_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 6 (`CANx_F13R2.FB6`) bit position @def CAN_F13R2_FB6_Pos */
#define CAN_F13R2_FB6_Pos			((reg_bit_pos_t) 6U)
/** @brief Acceptance-filter bank 13 word 2 bit 6 (`CANx_F13R2.FB6`) bit mask @def CAN_F13R2_FB6_Msk */
#define CAN_F13R2_FB6_Msk			REG_BIT_MASK(CAN_F13R2_FB6_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 6 (`CANx_F13R2.FB6`) bit mask alias @def CAN_F13R2_FB6 */
#define CAN_F13R2_FB6				CAN_F13R2_FB6_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 7 (`CANx_F13R2.FB7`) bit position @def CAN_F13R2_FB7_Pos */
#define CAN_F13R2_FB7_Pos			((reg_bit_pos_t) 7U)
/** @brief Acceptance-filter bank 13 word 2 bit 7 (`CANx_F13R2.FB7`) bit mask @def CAN_F13R2_FB7_Msk */
#define CAN_F13R2_FB7_Msk			REG_BIT_MASK(CAN_F13R2_FB7_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 7 (`CANx_F13R2.FB7`) bit mask alias @def CAN_F13R2_FB7 */
#define CAN_F13R2_FB7				CAN_F13R2_FB7_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 8 (`CANx_F13R2.FB8`) bit position @def CAN_F13R2_FB8_Pos */
#define CAN_F13R2_FB8_Pos			((reg_bit_pos_t) 8U)
/** @brief Acceptance-filter bank 13 word 2 bit 8 (`CANx_F13R2.FB8`) bit mask @def CAN_F13R2_FB8_Msk */
#define CAN_F13R2_FB8_Msk			REG_BIT_MASK(CAN_F13R2_FB8_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 8 (`CANx_F13R2.FB8`) bit mask alias @def CAN_F13R2_FB8 */
#define CAN_F13R2_FB8				CAN_F13R2_FB8_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 9 (`CANx_F13R2.FB9`) bit position @def CAN_F13R2_FB9_Pos */
#define CAN_F13R2_FB9_Pos			((reg_bit_pos_t) 9U)
/** @brief Acceptance-filter bank 13 word 2 bit 9 (`CANx_F13R2.FB9`) bit mask @def CAN_F13R2_FB9_Msk */
#define CAN_F13R2_FB9_Msk			REG_BIT_MASK(CAN_F13R2_FB9_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 9 (`CANx_F13R2.FB9`) bit mask alias @def CAN_F13R2_FB9 */
#define CAN_F13R2_FB9				CAN_F13R2_FB9_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 10 (`CANx_F13R2.FB10`) bit position @def CAN_F13R2_FB10_Pos */
#define CAN_F13R2_FB10_Pos			((reg_bit_pos_t) 10U)
/** @brief Acceptance-filter bank 13 word 2 bit 10 (`CANx_F13R2.FB10`) bit mask @def CAN_F13R2_FB10_Msk */
#define CAN_F13R2_FB10_Msk			REG_BIT_MASK(CAN_F13R2_FB10_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 10 (`CANx_F13R2.FB10`) bit mask alias @def CAN_F13R2_FB10 */
#define CAN_F13R2_FB10				CAN_F13R2_FB10_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 11 (`CANx_F13R2.FB11`) bit position @def CAN_F13R2_FB11_Pos */
#define CAN_F13R2_FB11_Pos			((reg_bit_pos_t) 11U)
/** @brief Acceptance-filter bank 13 word 2 bit 11 (`CANx_F13R2.FB11`) bit mask @def CAN_F13R2_FB11_Msk */
#define CAN_F13R2_FB11_Msk			REG_BIT_MASK(CAN_F13R2_FB11_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 11 (`CANx_F13R2.FB11`) bit mask alias @def CAN_F13R2_FB11 */
#define CAN_F13R2_FB11				CAN_F13R2_FB11_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 12 (`CANx_F13R2.FB12`) bit position @def CAN_F13R2_FB12_Pos */
#define CAN_F13R2_FB12_Pos			((reg_bit_pos_t) 12U)
/** @brief Acceptance-filter bank 13 word 2 bit 12 (`CANx_F13R2.FB12`) bit mask @def CAN_F13R2_FB12_Msk */
#define CAN_F13R2_FB12_Msk			REG_BIT_MASK(CAN_F13R2_FB12_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 12 (`CANx_F13R2.FB12`) bit mask alias @def CAN_F13R2_FB12 */
#define CAN_F13R2_FB12				CAN_F13R2_FB12_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 13 (`CANx_F13R2.FB13`) bit position @def CAN_F13R2_FB13_Pos */
#define CAN_F13R2_FB13_Pos			((reg_bit_pos_t) 13U)
/** @brief Acceptance-filter bank 13 word 2 bit 13 (`CANx_F13R2.FB13`) bit mask @def CAN_F13R2_FB13_Msk */
#define CAN_F13R2_FB13_Msk			REG_BIT_MASK(CAN_F13R2_FB13_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 13 (`CANx_F13R2.FB13`) bit mask alias @def CAN_F13R2_FB13 */
#define CAN_F13R2_FB13				CAN_F13R2_FB13_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 14 (`CANx_F13R2.FB14`) bit position @def CAN_F13R2_FB14_Pos */
#define CAN_F13R2_FB14_Pos			((reg_bit_pos_t) 14U)
/** @brief Acceptance-filter bank 13 word 2 bit 14 (`CANx_F13R2.FB14`) bit mask @def CAN_F13R2_FB14_Msk */
#define CAN_F13R2_FB14_Msk			REG_BIT_MASK(CAN_F13R2_FB14_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 14 (`CANx_F13R2.FB14`) bit mask alias @def CAN_F13R2_FB14 */
#define CAN_F13R2_FB14				CAN_F13R2_FB14_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 15 (`CANx_F13R2.FB15`) bit position @def CAN_F13R2_FB15_Pos */
#define CAN_F13R2_FB15_Pos			((reg_bit_pos_t) 15U)
/** @brief Acceptance-filter bank 13 word 2 bit 15 (`CANx_F13R2.FB15`) bit mask @def CAN_F13R2_FB15_Msk */
#define CAN_F13R2_FB15_Msk			REG_BIT_MASK(CAN_F13R2_FB15_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 15 (`CANx_F13R2.FB15`) bit mask alias @def CAN_F13R2_FB15 */
#define CAN_F13R2_FB15				CAN_F13R2_FB15_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 16 (`CANx_F13R2.FB16`) bit position @def CAN_F13R2_FB16_Pos */
#define CAN_F13R2_FB16_Pos			((reg_bit_pos_t) 16U)
/** @brief Acceptance-filter bank 13 word 2 bit 16 (`CANx_F13R2.FB16`) bit mask @def CAN_F13R2_FB16_Msk */
#define CAN_F13R2_FB16_Msk			REG_BIT_MASK(CAN_F13R2_FB16_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 16 (`CANx_F13R2.FB16`) bit mask alias @def CAN_F13R2_FB16 */
#define CAN_F13R2_FB16				CAN_F13R2_FB16_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 17 (`CANx_F13R2.FB17`) bit position @def CAN_F13R2_FB17_Pos */
#define CAN_F13R2_FB17_Pos			((reg_bit_pos_t) 17U)
/** @brief Acceptance-filter bank 13 word 2 bit 17 (`CANx_F13R2.FB17`) bit mask @def CAN_F13R2_FB17_Msk */
#define CAN_F13R2_FB17_Msk			REG_BIT_MASK(CAN_F13R2_FB17_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 17 (`CANx_F13R2.FB17`) bit mask alias @def CAN_F13R2_FB17 */
#define CAN_F13R2_FB17				CAN_F13R2_FB17_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 18 (`CANx_F13R2.FB18`) bit position @def CAN_F13R2_FB18_Pos */
#define CAN_F13R2_FB18_Pos			((reg_bit_pos_t) 18U)
/** @brief Acceptance-filter bank 13 word 2 bit 18 (`CANx_F13R2.FB18`) bit mask @def CAN_F13R2_FB18_Msk */
#define CAN_F13R2_FB18_Msk			REG_BIT_MASK(CAN_F13R2_FB18_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 18 (`CANx_F13R2.FB18`) bit mask alias @def CAN_F13R2_FB18 */
#define CAN_F13R2_FB18				CAN_F13R2_FB18_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 19 (`CANx_F13R2.FB19`) bit position @def CAN_F13R2_FB19_Pos */
#define CAN_F13R2_FB19_Pos			((reg_bit_pos_t) 19U)
/** @brief Acceptance-filter bank 13 word 2 bit 19 (`CANx_F13R2.FB19`) bit mask @def CAN_F13R2_FB19_Msk */
#define CAN_F13R2_FB19_Msk			REG_BIT_MASK(CAN_F13R2_FB19_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 19 (`CANx_F13R2.FB19`) bit mask alias @def CAN_F13R2_FB19 */
#define CAN_F13R2_FB19				CAN_F13R2_FB19_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 20 (`CANx_F13R2.FB20`) bit position @def CAN_F13R2_FB20_Pos */
#define CAN_F13R2_FB20_Pos			((reg_bit_pos_t) 20U)
/** @brief Acceptance-filter bank 13 word 2 bit 20 (`CANx_F13R2.FB20`) bit mask @def CAN_F13R2_FB20_Msk */
#define CAN_F13R2_FB20_Msk			REG_BIT_MASK(CAN_F13R2_FB20_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 20 (`CANx_F13R2.FB20`) bit mask alias @def CAN_F13R2_FB20 */
#define CAN_F13R2_FB20				CAN_F13R2_FB20_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 21 (`CANx_F13R2.FB21`) bit position @def CAN_F13R2_FB21_Pos */
#define CAN_F13R2_FB21_Pos			((reg_bit_pos_t) 21U)
/** @brief Acceptance-filter bank 13 word 2 bit 21 (`CANx_F13R2.FB21`) bit mask @def CAN_F13R2_FB21_Msk */
#define CAN_F13R2_FB21_Msk			REG_BIT_MASK(CAN_F13R2_FB21_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 21 (`CANx_F13R2.FB21`) bit mask alias @def CAN_F13R2_FB21 */
#define CAN_F13R2_FB21				CAN_F13R2_FB21_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 22 (`CANx_F13R2.FB22`) bit position @def CAN_F13R2_FB22_Pos */
#define CAN_F13R2_FB22_Pos			((reg_bit_pos_t) 22U)
/** @brief Acceptance-filter bank 13 word 2 bit 22 (`CANx_F13R2.FB22`) bit mask @def CAN_F13R2_FB22_Msk */
#define CAN_F13R2_FB22_Msk			REG_BIT_MASK(CAN_F13R2_FB22_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 22 (`CANx_F13R2.FB22`) bit mask alias @def CAN_F13R2_FB22 */
#define CAN_F13R2_FB22				CAN_F13R2_FB22_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 23 (`CANx_F13R2.FB23`) bit position @def CAN_F13R2_FB23_Pos */
#define CAN_F13R2_FB23_Pos			((reg_bit_pos_t) 23U)
/** @brief Acceptance-filter bank 13 word 2 bit 23 (`CANx_F13R2.FB23`) bit mask @def CAN_F13R2_FB23_Msk */
#define CAN_F13R2_FB23_Msk			REG_BIT_MASK(CAN_F13R2_FB23_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 23 (`CANx_F13R2.FB23`) bit mask alias @def CAN_F13R2_FB23 */
#define CAN_F13R2_FB23				CAN_F13R2_FB23_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 24 (`CANx_F13R2.FB24`) bit position @def CAN_F13R2_FB24_Pos */
#define CAN_F13R2_FB24_Pos			((reg_bit_pos_t) 24U)
/** @brief Acceptance-filter bank 13 word 2 bit 24 (`CANx_F13R2.FB24`) bit mask @def CAN_F13R2_FB24_Msk */
#define CAN_F13R2_FB24_Msk			REG_BIT_MASK(CAN_F13R2_FB24_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 24 (`CANx_F13R2.FB24`) bit mask alias @def CAN_F13R2_FB24 */
#define CAN_F13R2_FB24				CAN_F13R2_FB24_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 25 (`CANx_F13R2.FB25`) bit position @def CAN_F13R2_FB25_Pos */
#define CAN_F13R2_FB25_Pos			((reg_bit_pos_t) 25U)
/** @brief Acceptance-filter bank 13 word 2 bit 25 (`CANx_F13R2.FB25`) bit mask @def CAN_F13R2_FB25_Msk */
#define CAN_F13R2_FB25_Msk			REG_BIT_MASK(CAN_F13R2_FB25_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 25 (`CANx_F13R2.FB25`) bit mask alias @def CAN_F13R2_FB25 */
#define CAN_F13R2_FB25				CAN_F13R2_FB25_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 26 (`CANx_F13R2.FB26`) bit position @def CAN_F13R2_FB26_Pos */
#define CAN_F13R2_FB26_Pos			((reg_bit_pos_t) 26U)
/** @brief Acceptance-filter bank 13 word 2 bit 26 (`CANx_F13R2.FB26`) bit mask @def CAN_F13R2_FB26_Msk */
#define CAN_F13R2_FB26_Msk			REG_BIT_MASK(CAN_F13R2_FB26_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 26 (`CANx_F13R2.FB26`) bit mask alias @def CAN_F13R2_FB26 */
#define CAN_F13R2_FB26				CAN_F13R2_FB26_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 27 (`CANx_F13R2.FB27`) bit position @def CAN_F13R2_FB27_Pos */
#define CAN_F13R2_FB27_Pos			((reg_bit_pos_t) 27U)
/** @brief Acceptance-filter bank 13 word 2 bit 27 (`CANx_F13R2.FB27`) bit mask @def CAN_F13R2_FB27_Msk */
#define CAN_F13R2_FB27_Msk			REG_BIT_MASK(CAN_F13R2_FB27_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 27 (`CANx_F13R2.FB27`) bit mask alias @def CAN_F13R2_FB27 */
#define CAN_F13R2_FB27				CAN_F13R2_FB27_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 28 (`CANx_F13R2.FB28`) bit position @def CAN_F13R2_FB28_Pos */
#define CAN_F13R2_FB28_Pos			((reg_bit_pos_t) 28U)
/** @brief Acceptance-filter bank 13 word 2 bit 28 (`CANx_F13R2.FB28`) bit mask @def CAN_F13R2_FB28_Msk */
#define CAN_F13R2_FB28_Msk			REG_BIT_MASK(CAN_F13R2_FB28_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 28 (`CANx_F13R2.FB28`) bit mask alias @def CAN_F13R2_FB28 */
#define CAN_F13R2_FB28				CAN_F13R2_FB28_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 29 (`CANx_F13R2.FB29`) bit position @def CAN_F13R2_FB29_Pos */
#define CAN_F13R2_FB29_Pos			((reg_bit_pos_t) 29U)
/** @brief Acceptance-filter bank 13 word 2 bit 29 (`CANx_F13R2.FB29`) bit mask @def CAN_F13R2_FB29_Msk */
#define CAN_F13R2_FB29_Msk			REG_BIT_MASK(CAN_F13R2_FB29_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 29 (`CANx_F13R2.FB29`) bit mask alias @def CAN_F13R2_FB29 */
#define CAN_F13R2_FB29				CAN_F13R2_FB29_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 30 (`CANx_F13R2.FB30`) bit position @def CAN_F13R2_FB30_Pos */
#define CAN_F13R2_FB30_Pos			((reg_bit_pos_t) 30U)
/** @brief Acceptance-filter bank 13 word 2 bit 30 (`CANx_F13R2.FB30`) bit mask @def CAN_F13R2_FB30_Msk */
#define CAN_F13R2_FB30_Msk			REG_BIT_MASK(CAN_F13R2_FB30_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 30 (`CANx_F13R2.FB30`) bit mask alias @def CAN_F13R2_FB30 */
#define CAN_F13R2_FB30				CAN_F13R2_FB30_Msk

/** @brief Acceptance-filter bank 13 word 2 bit 31 (`CANx_F13R2.FB31`) bit position @def CAN_F13R2_FB31_Pos */
#define CAN_F13R2_FB31_Pos			((reg_bit_pos_t) 31U)
/** @brief Acceptance-filter bank 13 word 2 bit 31 (`CANx_F13R2.FB31`) bit mask @def CAN_F13R2_FB31_Msk */
#define CAN_F13R2_FB31_Msk			REG_BIT_MASK(CAN_F13R2_FB31_Pos)
/** @brief Acceptance-filter bank 13 word 2 bit 31 (`CANx_F13R2.FB31`) bit mask alias @def CAN_F13R2_FB31 */
#define CAN_F13R2_FB31				CAN_F13R2_FB31_Msk

/** @} */ // CAN_01_RegisterLayer_00_RegisterDefines

// ==================================================================================================== //
// bxCAN Register Map
// ==================================================================================================== //

/**
 * @defgroup CAN_01_RegisterLayer_01_RegisterMap bxCAN Register Map
 * @ingroup CAN_01_RegisterLayer
 * @brief Memory-mapped CAN1 control, mailbox, FIFO, and filter-bank layout
 * @details
 * Every physical word exposes a full-width `.REG` transaction image and a
 * `.BIT` placement view. Driver and LL transactions must use `.REG` whenever
 * a register mixes stored state with write-zero-to-clear, write-one-to-clear,
 * or action semantics.
 * @{
 */

/**
 * @brief Describes one bxCAN transmit mailbox
 * @details
 * CAN1 implements three instances at offsets `0x180`, `0x190`, and `0x1A0`.
 * Software stages identifier, metadata, and payload before setting `TXRQ`.
 * Hardware owns the mailbox contents while the request remains pending.
 * @struct CAN_TxMailBox_TypeDef
 */
typedef volatile struct __CAN_TxMailBox_TypeDef
{
	/**
	 * @section CAN_TxMailBox_TypeDef_TIR Transmit Mailbox Identifier Register (TIR)
	 * @brief [R/W and action] Identifier, frame type, and transmission request
	 * @details `TXRQ` hands the completely staged mailbox to hardware.
	 */
	union CAN_TIR
	{
		/** @brief Full 32-bit transmit identifier and request image */
		_IO REG;
		/** @brief Named transmit identifier and request bitfield view */
		struct
		{
			_IO TXRQ : 1;												/**< Transmission-request action/state */
			_IO RTR : 1;												/**< Data-frame or remote-frame selection */
			_IO IDE : 1;												/**< Standard or extended identifier selection */
			_IO EXID : 18;												/**< Extended identifier portion */
			_IO STID : 11;												/**< Standard identifier or extended identifier prefix */
		} BIT;
	} TIR;																/**< Transmit identifier image and request action view */

	/**
	 * @section CAN_TxMailBox_TypeDef_TDTR Transmit Mailbox Data Length and Time Register (TDTR)
	 * @brief [R/W] Payload length and time-triggered metadata
	 */
	union CAN_TDTR
	{
		/** @brief Full 32-bit transmit length and timestamp image */
		_IO REG;
		/** @brief Named transmit length and timestamp bitfield view */
		struct
		{
			_IO DLC : 4;												/**< Data length code in the range 0 through 8 */
			_IO reserved_1 : 4;											/**< Reserved */
			_IO TGT : 1;												/**< Global-time transmission request */
			_IO reserved_2 : 7;											/**< Reserved */
			_IO TIME : 16;												/**< Transmit timestamp in time-triggered mode */
		} BIT;
	} TDTR;																/**< Transmit length and timestamp image and named-field views */

	/**
	 * @section CAN_TxMailBox_TypeDef_TDLR Transmit Mailbox Data Low Register (TDLR)
	 * @brief [R/W data port] Payload bytes 0 through 3
	 */
	union CAN_TDLR
	{
		/** @brief Full 32-bit low transmit-payload image */
		_IO REG;
		/** @brief Named low transmit-payload byte view */
		struct
		{
			_IO DATA0 : 8;												/**< Payload byte 0 */
			_IO DATA1 : 8;												/**< Payload byte 1 */
			_IO DATA2 : 8;												/**< Payload byte 2 */
			_IO DATA3 : 8;												/**< Payload byte 3 */
		} BIT;
	} TDLR;																/**< Low transmit-payload image and byte views */

	/**
	 * @section CAN_TxMailBox_TypeDef_TDHR Transmit Mailbox Data High Register (TDHR)
	 * @brief [R/W data port] Payload bytes 4 through 7
	 */
	union CAN_TDHR
	{
		/** @brief Full 32-bit high transmit-payload image */
		_IO REG;
		/** @brief Named high transmit-payload byte view */
		struct
		{
			_IO DATA4 : 8;												/**< Payload byte 4 */
			_IO DATA5 : 8;												/**< Payload byte 5 */
			_IO DATA6 : 8;												/**< Payload byte 6 */
			_IO DATA7 : 8;												/**< Payload byte 7 */
		} BIT;
	} TDHR;																/**< High transmit-payload image and byte views */
} CAN_TxMailBox_TypeDef;

/**
 * @brief Describes one bxCAN receive FIFO output mailbox
 * @details
 * The two instances at offsets `0x1B0` and `0x1C0` expose the oldest message
 * in receive FIFO 0 and FIFO 1. Their images remain read-only; releasing the
 * consumed entry is an action through `RF0R.RFOM0` or `RF1R.RFOM1`.
 * @struct CAN_FIFOMailBox_TypeDef
 */
typedef volatile struct __CAN_FIFOMailBox_TypeDef
{
	/**
	 * @section CAN_FIFOMailBox_TypeDef_RIR Receive FIFO Mailbox Identifier Register (RIR)
	 * @brief [R] Received identifier and frame type
	 */
	union CAN_RIR
	{
		/** @brief Full 32-bit received identifier image */
		_I REG;
		/** @brief Named received identifier bitfield view */
		struct
		{
			_I reserved_1 : 1;											/**< Reserved */
			_I RTR : 1;													/**< Received data-frame or remote-frame state */
			_I IDE : 1;													/**< Received standard or extended identifier state */
			_I EXID : 18;												/**< Received extended identifier portion */
			_I STID : 11;												/**< Received standard identifier or extended identifier prefix */
		} BIT;
	} RIR;																/**< Received identifier observation and named-field views */

	/**
	 * @section CAN_FIFOMailBox_TypeDef_RDTR Receive FIFO Mailbox Data Length and Time Register (RDTR)
	 * @brief [R] Received payload length, filter match, and timestamp metadata
	 */
	union CAN_RDTR
	{
		/** @brief Full 32-bit receive metadata image */
		_I REG;
		/** @brief Named receive metadata bitfield view */
		struct
		{
			_I DLC : 4;													/**< Received data length code */
			_I reserved_1 : 4;											/**< Reserved */
			_I FMI : 8;													/**< Filter match index */
			_I TIME : 16;												/**< Receive timestamp in time-triggered mode */
		} BIT;
	} RDTR;																/**< Receive metadata observation and named-field views */

	/**
	 * @section CAN_FIFOMailBox_TypeDef_RDLR Receive FIFO Mailbox Data Low Register (RDLR)
	 * @brief [R data port] Received payload bytes 0 through 3
	 */
	union CAN_RDLR
	{
		/** @brief Full 32-bit low received-payload image */
		_I REG;
		/** @brief Named low received-payload byte view */
		struct
		{
			_I DATA0 : 8;												/**< Received payload byte 0 */
			_I DATA1 : 8;												/**< Received payload byte 1 */
			_I DATA2 : 8;												/**< Received payload byte 2 */
			_I DATA3 : 8;												/**< Received payload byte 3 */
		} BIT;
	} RDLR;																/**< Low received-payload observation and byte views */

	/**
	 * @section CAN_FIFOMailBox_TypeDef_RDHR Receive FIFO Mailbox Data High Register (RDHR)
	 * @brief [R data port] Received payload bytes 4 through 7
	 */
	union CAN_RDHR
	{
		/** @brief Full 32-bit high received-payload image */
		_I REG;
		/** @brief Named high received-payload byte view */
		struct
		{
			_I DATA4 : 8;												/**< Received payload byte 4 */
			_I DATA5 : 8;												/**< Received payload byte 5 */
			_I DATA6 : 8;												/**< Received payload byte 6 */
			_I DATA7 : 8;												/**< Received payload byte 7 */
		} BIT;
	} RDHR;																/**< High received-payload observation and byte views */
} CAN_FIFOMailBox_TypeDef;

/**
 * @brief Describes one pair of bxCAN acceptance-filter words
 * @details
 * The meaning of each 32-bit word depends on that bank's scale and identifier
 * list/mask selection. Packing policy therefore belongs above this raw Core
 * representation.
 * @struct CAN_FilterRegister_TypeDef
 */
typedef volatile struct __CAN_FilterRegister_TypeDef
{
	union CAN_FR1
	{
		/** @brief Full 32-bit filter-bank word 1 image */
		_IO REG;
		/** @brief Named full-width filter-bank word 1 view */
		struct
		{
			_IO FB : 32;												/**< Filter-bank word 1 payload */
		} BIT;
	} FR1;																/**< Filter-bank word 1 image and full-width view */

	union CAN_FR2
	{
		/** @brief Full 32-bit filter-bank word 2 image */
		_IO REG;
		/** @brief Named full-width filter-bank word 2 view */
		struct
		{
			_IO FB : 32;												/**< Filter-bank word 2 payload */
		} BIT;
	} FR2;																/**< Filter-bank word 2 image and full-width view */
} CAN_FilterRegister_TypeDef;

/**
 * @brief Maps the complete STM32F103C8T6 CAN1 register bank
 * @details
 * Reserved arrays preserve the hardware gaps between controller state,
 * mailbox windows, filter control, and filter-bank storage. Indexed arrays
 * provide one definition for each repeated hardware domain while preserving
 * the exact physical spacing.
 * @see RM0008 Section 24.9 bxCAN registers
 * @struct CAN_TypeDef
 */
typedef volatile struct __CAN_TypeDef
{
	/**
	 * @section CAN_TypeDef_MCR CAN Master Control Register (MCR)
	 * @brief [R/W and action] Lifecycle requests and controller-wide policy
	 * @details `INRQ`, `SLEEP`, and `RESET` initiate hardware state transitions.
	 */
	union CAN_MCR
	{
		/** @brief Full 32-bit CAN master-control image */
		_IO REG;
		/** @brief Named CAN master-control bitfield view */
		struct
		{
			_IO INRQ : 1;												/**< Initialization-mode request */
			_IO SLEEP : 1;												/**< Sleep-mode request */
			_IO TXFP : 1;												/**< Identifier-order or request-order transmit priority */
			_IO RFLM : 1;												/**< Receive FIFO overwrite or lock policy */
			_IO NART : 1;												/**< Automatic retransmission suppression */
			_IO AWUM : 1;												/**< Automatic wake-up on bus activity */
			_IO ABOM : 1;												/**< Automatic bus-off recovery */
			_IO TTCM : 1;												/**< Time-triggered communication mode */
			_IO reserved_1 : 7;											/**< Reserved */
			_IO RESET : 1;												/**< Software master-reset action */
			_IO DBF : 1;												/**< Freeze CAN operation during debug halt */
			_IO reserved_2 : 15;										/**< Reserved */
		} BIT;
	} MCR;																/**< CAN lifecycle and policy image and named-field views */

	/**
	 * @section CAN_TypeDef_MSR CAN Master Status Register (MSR)
	 * @brief [R and write-zero-to-clear] Lifecycle acknowledgements and status-change events
	 * @details `ERRI`, `WKUI`, and `SLAKI` clear when software writes zero.
	 */
	union CAN_MSR
	{
		/** @brief Full 32-bit CAN master-status image */
		_IO REG;
		/** @brief Named CAN master-status bitfield view */
		struct
		{
			_IO INAK : 1;												/**< Initialization-mode acknowledgement */
			_IO SLAK : 1;												/**< Sleep-mode acknowledgement */
			_IO ERRI : 1;												/**< Error event; write zero to clear */
			_IO WKUI : 1;												/**< Wake-up event; write zero to clear */
			_IO SLAKI : 1;												/**< Sleep acknowledgement event; write zero to clear */
			_IO reserved_1 : 3;											/**< Reserved */
			_IO TXM : 1;												/**< Controller currently transmitting */
			_IO RXM : 1;												/**< Controller currently receiving */
			_IO SAMP : 1;												/**< Last sampled CAN_RX level */
			_IO RX : 1;													/**< Current CAN_RX level */
			_IO reserved_2 : 20;										/**< Reserved */
		} BIT;
	} MSR;																/**< CAN lifecycle and event observation and acknowledgement views */

	/**
	 * @section CAN_TypeDef_TSR CAN Transmit Status Register (TSR)
	 * @brief [R, write-one-to-clear, and action] Mailbox completion, errors, aborts, and availability
	 * @details
	 * Writing one to `RQCPx` acknowledges that mailbox's completion state;
	 * writing one to `ABRQx` requests cancellation. Use full-register semantic
	 * writes rather than generic read-modify-write operations.
	 */
	union CAN_TSR
	{
		/** @brief Full 32-bit CAN transmit-status and action image */
		_IO REG;
		/** @brief Named CAN transmit-status and action bitfield view */
		struct
		{
			_IO RQCP0 : 1;												/**< Mailbox 0 request-complete event; write one to clear */
			_IO TXOK0 : 1;												/**< Mailbox 0 successful-transmission event */
			_IO ALST0 : 1;												/**< Mailbox 0 arbitration-lost event */
			_IO TERR0 : 1;												/**< Mailbox 0 transmission-error event */
			_IO reserved_1 : 3;											/**< Reserved */
			_IO ABRQ0 : 1;												/**< Mailbox 0 abort-request action */
			_IO RQCP1 : 1;												/**< Mailbox 1 request-complete event; write one to clear */
			_IO TXOK1 : 1;												/**< Mailbox 1 successful-transmission event */
			_IO ALST1 : 1;												/**< Mailbox 1 arbitration-lost event */
			_IO TERR1 : 1;												/**< Mailbox 1 transmission-error event */
			_IO reserved_2 : 3;											/**< Reserved */
			_IO ABRQ1 : 1;												/**< Mailbox 1 abort-request action */
			_IO RQCP2 : 1;												/**< Mailbox 2 request-complete event; write one to clear */
			_IO TXOK2 : 1;												/**< Mailbox 2 successful-transmission event */
			_IO ALST2 : 1;												/**< Mailbox 2 arbitration-lost event */
			_IO TERR2 : 1;												/**< Mailbox 2 transmission-error event */
			_IO reserved_3 : 3;											/**< Reserved */
			_IO ABRQ2 : 1;												/**< Mailbox 2 abort-request action */
			_IO CODE : 2;												/**< Lowest-priority empty mailbox code */
			_IO TME0 : 1;												/**< Transmit mailbox 0 empty state */
			_IO TME1 : 1;												/**< Transmit mailbox 1 empty state */
			_IO TME2 : 1;												/**< Transmit mailbox 2 empty state */
			_IO LOW0 : 1;												/**< Mailbox 0 has lowest priority */
			_IO LOW1 : 1;												/**< Mailbox 1 has lowest priority */
			_IO LOW2 : 1;												/**< Mailbox 2 has lowest priority */
		} BIT;
	} TSR;																/**< Transmit completion, error, abort, and availability views */

	/**
	 * @section CAN_TypeDef_RF0R CAN Receive FIFO 0 Register (RF0R)
	 * @brief [R, write-zero-to-clear, and action] FIFO 0 depth, full/overrun events, and release
	 */
	union CAN_RF0R
	{
		/** @brief Full 32-bit receive FIFO 0 status and action image */
		_IO REG;
		/** @brief Named receive FIFO 0 status and action bitfield view */
		struct
		{
			_IO FMP0 : 2;												/**< FIFO 0 pending-message count */
			_IO reserved_1 : 1;											/**< Reserved */
			_IO FULL0 : 1;												/**< FIFO 0 full event; write zero to clear */
			_IO FOVR0 : 1;												/**< FIFO 0 overrun event; write zero to clear */
			_IO RFOM0 : 1;												/**< FIFO 0 output-mailbox release action */
			_IO reserved_2 : 26;										/**< Reserved */
		} BIT;
	} RF0R;																/**< Receive FIFO 0 status, event, and release views */

	/**
	 * @section CAN_TypeDef_RF1R CAN Receive FIFO 1 Register (RF1R)
	 * @brief [R, write-zero-to-clear, and action] FIFO 1 depth, full/overrun events, and release
	 */
	union CAN_RF1R
	{
		/** @brief Full 32-bit receive FIFO 1 status and action image */
		_IO REG;
		/** @brief Named receive FIFO 1 status and action bitfield view */
		struct
		{
			_IO FMP1 : 2;												/**< FIFO 1 pending-message count */
			_IO reserved_1 : 1;											/**< Reserved */
			_IO FULL1 : 1;												/**< FIFO 1 full event; write zero to clear */
			_IO FOVR1 : 1;												/**< FIFO 1 overrun event; write zero to clear */
			_IO RFOM1 : 1;												/**< FIFO 1 output-mailbox release action */
			_IO reserved_2 : 26;										/**< Reserved */
		} BIT;
	} RF1R;																/**< Receive FIFO 1 status, event, and release views */

	/**
	 * @section CAN_TypeDef_IER CAN Interrupt Enable Register (IER)
	 * @brief [R/W] Peripheral interrupt-request source gates
	 * @details NVIC delivery, priority, pending, and active states remain separate.
	 */
	union CAN_IER
	{
		/** @brief Full 32-bit CAN interrupt-source image */
		_IO REG;
		/** @brief Named CAN interrupt-source bitfield view */
		struct
		{
			_IO TMEIE : 1;												/**< Transmit-mailbox-empty interrupt-request enable */
			_IO FMPIE0 : 1;												/**< FIFO 0 message-pending interrupt-request enable */
			_IO FFIE0 : 1;												/**< FIFO 0 full interrupt-request enable */
			_IO FOVIE0 : 1;												/**< FIFO 0 overrun interrupt-request enable */
			_IO FMPIE1 : 1;												/**< FIFO 1 message-pending interrupt-request enable */
			_IO FFIE1 : 1;												/**< FIFO 1 full interrupt-request enable */
			_IO FOVIE1 : 1;												/**< FIFO 1 overrun interrupt-request enable */
			_IO reserved_1 : 1;											/**< Reserved */
			_IO EWGIE : 1;												/**< Error-warning interrupt-request enable */
			_IO EPVIE : 1;												/**< Error-passive interrupt-request enable */
			_IO BOFIE : 1;												/**< Bus-off interrupt-request enable */
			_IO LECIE : 1;												/**< Last-error-code interrupt-request enable */
			_IO reserved_2 : 3;											/**< Reserved */
			_IO ERRIE : 1;												/**< Error interrupt-request master enable */
			_IO WKUIE : 1;												/**< Wake-up interrupt-request enable */
			_IO SLKIE : 1;												/**< Sleep interrupt-request enable */
			_IO reserved_3 : 14;										/**< Reserved */
		} BIT;
	} IER;																/**< CAN interrupt-source gate image and named-field views */

	/**
	 * @section CAN_TypeDef_ESR CAN Error Status Register (ESR)
	 * @brief [R and limited R/W] Error state, last error code, and protocol counters
	 */
	union CAN_ESR
	{
		/** @brief Full 32-bit CAN error-state image */
		_IO REG;
		/** @brief Named CAN error-state bitfield view */
		struct
		{
			_IO EWGF : 1;												/**< Error-warning state */
			_IO EPVF : 1;												/**< Error-passive state */
			_IO BOFF : 1;												/**< Bus-off state */
			_IO reserved_1 : 1;											/**< Reserved */
			_IO LEC : 3;												/**< Last protocol error code */
			_IO reserved_2 : 9;											/**< Reserved */
			_IO TEC : 8;												/**< Least-significant eight transmit-error-counter bits */
			_IO REC : 8;												/**< Receive-error counter */
		} BIT;
	} ESR;																/**< CAN error-state, error-code, and counter views */

	/**
	 * @section CAN_TypeDef_BTR CAN Bit Timing Register (BTR)
	 * @brief [R/W in initialization mode] Nominal bit timing and test modes
	 */
	union CAN_BTR
	{
		/** @brief Full 32-bit CAN bit-timing image */
		_IO REG;
		/** @brief Named CAN bit-timing bitfield view */
		struct
		{
			_IO BRP : 10;												/**< Baud-rate prescaler minus one */
			_IO reserved_1 : 6;											/**< Reserved */
			_IO TS1 : 4;												/**< Time segment 1 length minus one */
			_IO TS2 : 3;												/**< Time segment 2 length minus one */
			_IO reserved_2 : 1;											/**< Reserved */
			_IO SJW : 2;												/**< Resynchronization jump width minus one */
			_IO reserved_3 : 4;											/**< Reserved */
			_IO LBKM : 1;												/**< Internal loopback mode */
			_IO SILM : 1;												/**< Silent bus-monitoring mode */
		} BIT;
	} BTR;																/**< CAN nominal bit-timing and test-mode views */

	_IO reserved_1[88];													/**< Reserved gap from `0x020` through `0x17C` */
	CAN_TxMailBox_TypeDef TX_MAILBOX[CAN_TX_MAILBOX_COUNT];				/**< Three transmit mailbox windows */
	CAN_FIFOMailBox_TypeDef RX_FIFO[CAN_RX_FIFO_COUNT];					/**< Two receive FIFO output windows */
	_IO reserved_2[12];													/**< Reserved gap from `0x1D0` through `0x1FC` */

	/**
	 * @section CAN_TypeDef_FMR CAN Filter Master Register (FMR)
	 * @brief [R/W and action] Acceptance-filter initialization mode
	 */
	union CAN_FMR
	{
		/** @brief Full 32-bit filter-master image */
		_IO REG;
		/** @brief Named filter-master bitfield view */
		struct
		{
			_IO FINIT : 1;												/**< Filter initialization-mode request/state */
			_IO reserved_1 : 31;										/**< Reserved on STM32F103C8T6 */
		} BIT;
	} FMR;																/**< Filter initialization-mode image and named-field views */

	/**
	 * @section CAN_TypeDef_FM1R CAN Filter Mode Register (FM1R)
	 * @brief [R/W in filter initialization mode] Identifier-mask or identifier-list mode per bank
	 */
	union CAN_FM1R
	{
		/** @brief Full 32-bit filter-mode image */
		_IO REG;
		/** @brief Named filter-mode bitfield view */
		struct
		{
			_IO FBM : 14;												/**< Filter-bank list-mode selectors */
			_IO reserved_1 : 18;										/**< Reserved */
		} BIT;
	} FM1R;																/**< Filter mode image and bank-selector views */

	_IO reserved_3;														/**< Reserved word at offset `0x208` */

	/**
	 * @section CAN_TypeDef_FS1R CAN Filter Scale Register (FS1R)
	 * @brief [R/W in filter initialization mode] Dual-16-bit or single-32-bit scale per bank
	 */
	union CAN_FS1R
	{
		/** @brief Full 32-bit filter-scale image */
		_IO REG;
		/** @brief Named filter-scale bitfield view */
		struct
		{
			_IO FSC : 14;												/**< Filter-bank 32-bit-scale selectors */
			_IO reserved_1 : 18;										/**< Reserved */
		} BIT;
	} FS1R;																/**< Filter scale image and bank-selector views */

	_IO reserved_4;														/**< Reserved word at offset `0x210` */

	/**
	 * @section CAN_TypeDef_FFA1R CAN Filter FIFO Assignment Register (FFA1R)
	 * @brief [R/W in filter initialization mode] Receive FIFO destination per bank
	 */
	union CAN_FFA1R
	{
		/** @brief Full 32-bit filter FIFO-assignment image */
		_IO REG;
		/** @brief Named filter FIFO-assignment bitfield view */
		struct
		{
			_IO FFA : 14;												/**< Filter-bank FIFO 0 or FIFO 1 assignments */
			_IO reserved_1 : 18;										/**< Reserved */
		} BIT;
	} FFA1R;															/**< Filter FIFO-assignment image and bank-selector views */

	_IO reserved_5;														/**< Reserved word at offset `0x218` */

	/**
	 * @section CAN_TypeDef_FA1R CAN Filter Activation Register (FA1R)
	 * @brief [R/W in filter initialization mode] Acceptance-filter activation per bank
	 */
	union CAN_FA1R
	{
		/** @brief Full 32-bit filter-activation image */
		_IO REG;
		/** @brief Named filter-activation bitfield view */
		struct
		{
			_IO FACT : 14;												/**< Filter-bank activation selectors */
			_IO reserved_1 : 18;										/**< Reserved */
		} BIT;
	} FA1R;																/**< Filter activation image and bank-selector views */

	_IO reserved_6[8];													/**< Reserved gap from `0x220` through `0x23C` */
	CAN_FilterRegister_TypeDef FILTER_BANK[CAN_FILTER_BANK_COUNT];		/**< Fourteen filter-bank word pairs */
} CAN_TypeDef;

/** @} */ // CAN_01_RegisterLayer_01_RegisterMap

/** @} */ // CAN_01_RegisterLayer

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_CAN_H_ */
