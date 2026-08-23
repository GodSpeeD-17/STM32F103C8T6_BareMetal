/**
 * @file stm32f1xx_defines.h
 * @brief STM32F103C8T6 Core, register-field, and selector macros
 */

// Header Guards
#ifndef STM32F1XX_DEFINES_H_
#define STM32F1XX_DEFINES_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx_utils.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief STM32F103C8T6 Core and peripheral symbolic definitions
 * @defgroup STM32F1xx_Defines STM32F103C8T6 Symbolic Definitions
 * @ingroup STM32F1xx
 * @details
 * This group contains Core and peripheral register-field positions, masks,
 * and selector values shared by the device register model.
 * Single-bit fields expose `_Pos`, `_Msk`, and an unsuffixed mask alias.
 * Multi-bit fields additionally expose `_Width`; full-register fields retain
 * an explicit 32-bit mask because `REG_FIELD_MASK()` accepts widths through
 * `31U`.
 * @{
 */

// ==================================================================================================== //
//								Cyclic Redundancy Check (CRC) Register Defines							//
// ==================================================================================================== //

// ----------------------------------- CRC_DR Register Bit Defines ------------------------------------ //
/** @brief Bit position of the `CRC_DR_DR` field @def CRC_DR_DR_Pos */
#define CRC_DR_DR_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CRC_DR_DR` field @def CRC_DR_DR_Width */
#define CRC_DR_DR_Width			((reg_field_width_t) 32U)
/** @brief Register-positioned mask for the `CRC_DR_DR` field @def CRC_DR_DR_Msk */
#define CRC_DR_DR_Msk			((reg) 0xFFFFFFFFUL)
/** @brief Data register bits @def CRC_DR_DR */
#define CRC_DR_DR				CRC_DR_DR_Msk

// ----------------------------------- CRC_IDR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CRC_IDR_IDR` field @def CRC_IDR_IDR_Pos */
#define CRC_IDR_IDR_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CRC_IDR_IDR` field @def CRC_IDR_IDR_Width */
#define CRC_IDR_IDR_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CRC_IDR_IDR` field @def CRC_IDR_IDR_Msk */
#define CRC_IDR_IDR_Msk			REG_FIELD_MASK(CRC_IDR_IDR_Pos, CRC_IDR_IDR_Width)
/** @brief General-purpose 8-bit data register bits @def CRC_IDR_IDR */
#define CRC_IDR_IDR				CRC_IDR_IDR_Msk

// ----------------------------------- CRC_CR Register Bit Defines ------------------------------------ //
/** @brief Bit position of the `CRC_CR_RESET` field @def CRC_CR_RESET_Pos */
#define CRC_CR_RESET_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CRC_CR_RESET` field @def CRC_CR_RESET_Msk */
#define CRC_CR_RESET_Msk		REG_BIT_MASK(CRC_CR_RESET_Pos)
/** @brief RESET bit @def CRC_CR_RESET */
#define CRC_CR_RESET			CRC_CR_RESET_Msk

// ==================================================================================================== //
//									Power Control (PWR) Register Defines								//
// ==================================================================================================== //

// ----------------------------------- PWR_CR Register Bit Defines ------------------------------------ //
/** @brief Bit position of the `PWR_CR_LPDS` field @def PWR_CR_LPDS_Pos */
#define PWR_CR_LPDS_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `PWR_CR_LPDS` field @def PWR_CR_LPDS_Msk */
#define PWR_CR_LPDS_Msk			REG_BIT_MASK(PWR_CR_LPDS_Pos)
/** @brief Low-Power Deepsleep @def PWR_CR_LPDS */
#define PWR_CR_LPDS				PWR_CR_LPDS_Msk
/** @brief Bit position of the `PWR_CR_PDDS` field @def PWR_CR_PDDS_Pos */
#define PWR_CR_PDDS_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `PWR_CR_PDDS` field @def PWR_CR_PDDS_Msk */
#define PWR_CR_PDDS_Msk			REG_BIT_MASK(PWR_CR_PDDS_Pos)
/** @brief Power Down Deepsleep @def PWR_CR_PDDS */
#define PWR_CR_PDDS				PWR_CR_PDDS_Msk
/** @brief Bit position of the `PWR_CR_CWUF` field @def PWR_CR_CWUF_Pos */
#define PWR_CR_CWUF_Pos			((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `PWR_CR_CWUF` field @def PWR_CR_CWUF_Msk */
#define PWR_CR_CWUF_Msk			REG_BIT_MASK(PWR_CR_CWUF_Pos)
/** @brief Clear Wakeup Flag @def PWR_CR_CWUF */
#define PWR_CR_CWUF				PWR_CR_CWUF_Msk
/** @brief Bit position of the `PWR_CR_CSBF` field @def PWR_CR_CSBF_Pos */
#define PWR_CR_CSBF_Pos			((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `PWR_CR_CSBF` field @def PWR_CR_CSBF_Msk */
#define PWR_CR_CSBF_Msk			REG_BIT_MASK(PWR_CR_CSBF_Pos)
/** @brief Clear Standby Flag @def PWR_CR_CSBF */
#define PWR_CR_CSBF				PWR_CR_CSBF_Msk
/** @brief Bit position of the `PWR_CR_PVDE` field @def PWR_CR_PVDE_Pos */
#define PWR_CR_PVDE_Pos			((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `PWR_CR_PVDE` field @def PWR_CR_PVDE_Msk */
#define PWR_CR_PVDE_Msk			REG_BIT_MASK(PWR_CR_PVDE_Pos)
/** @brief Power Voltage Detector Enable @def PWR_CR_PVDE */
#define PWR_CR_PVDE				PWR_CR_PVDE_Msk

/** @brief Bit position of the `PWR_CR_PLS` field @def PWR_CR_PLS_Pos */
#define PWR_CR_PLS_Pos			((reg_bit_pos_t) 5U)
/** @brief Width of the `PWR_CR_PLS` field @def PWR_CR_PLS_Width */
#define PWR_CR_PLS_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `PWR_CR_PLS` field @def PWR_CR_PLS_Msk */
#define PWR_CR_PLS_Msk			REG_FIELD_MASK(PWR_CR_PLS_Pos, PWR_CR_PLS_Width)
/** @brief PLS[2:0] bits (PVD Level Selection) @def PWR_CR_PLS */
#define PWR_CR_PLS				PWR_CR_PLS_Msk
/** @brief Register or selector value represented by `PWR_CR_PLS_0` @def PWR_CR_PLS_0 */
#define PWR_CR_PLS_0			(0x1UL << PWR_CR_PLS_Pos)
/** @brief Register or selector value represented by `PWR_CR_PLS_1` @def PWR_CR_PLS_1 */
#define PWR_CR_PLS_1			(0x2UL << PWR_CR_PLS_Pos)
/** @brief Register or selector value represented by `PWR_CR_PLS_2` @def PWR_CR_PLS_2 */
#define PWR_CR_PLS_2			(0x4UL << PWR_CR_PLS_Pos)

// ---------------------------------- PWR PVD Level Selector Defines ---------------------------------- //
/** @brief PVD level 2.2V @def PWR_CR_PLS_LEV0 */
#define PWR_CR_PLS_LEV0			(0x00000000UL)
/** @brief PVD level 2.3V @def PWR_CR_PLS_LEV1 */
#define PWR_CR_PLS_LEV1			(0x00000020UL)
/** @brief PVD level 2.4V @def PWR_CR_PLS_LEV2 */
#define PWR_CR_PLS_LEV2			(0x00000040UL)
/** @brief PVD level 2.5V @def PWR_CR_PLS_LEV3 */
#define PWR_CR_PLS_LEV3			(0x00000060UL)
/** @brief PVD level 2.6V @def PWR_CR_PLS_LEV4 */
#define PWR_CR_PLS_LEV4			(0x00000080UL)
/** @brief PVD level 2.7V @def PWR_CR_PLS_LEV5 */
#define PWR_CR_PLS_LEV5			(0x000000A0UL)
/** @brief PVD level 2.8V @def PWR_CR_PLS_LEV6 */
#define PWR_CR_PLS_LEV6			(0x000000C0UL)
/** @brief PVD level 2.9V @def PWR_CR_PLS_LEV7 */
#define PWR_CR_PLS_LEV7			(0x000000E0UL)

// ----------------------------------- Legacy Compatibility Defines ----------------------------------- //
/** @brief Register or selector value represented by `PWR_CR_PLS_2V2` @def PWR_CR_PLS_2V2 */
#define PWR_CR_PLS_2V2			PWR_CR_PLS_LEV0
/** @brief Register or selector value represented by `PWR_CR_PLS_2V3` @def PWR_CR_PLS_2V3 */
#define PWR_CR_PLS_2V3			PWR_CR_PLS_LEV1
/** @brief Register or selector value represented by `PWR_CR_PLS_2V4` @def PWR_CR_PLS_2V4 */
#define PWR_CR_PLS_2V4			PWR_CR_PLS_LEV2
/** @brief Register or selector value represented by `PWR_CR_PLS_2V5` @def PWR_CR_PLS_2V5 */
#define PWR_CR_PLS_2V5			PWR_CR_PLS_LEV3
/** @brief Register or selector value represented by `PWR_CR_PLS_2V6` @def PWR_CR_PLS_2V6 */
#define PWR_CR_PLS_2V6			PWR_CR_PLS_LEV4
/** @brief Register or selector value represented by `PWR_CR_PLS_2V7` @def PWR_CR_PLS_2V7 */
#define PWR_CR_PLS_2V7			PWR_CR_PLS_LEV5
/** @brief Register or selector value represented by `PWR_CR_PLS_2V8` @def PWR_CR_PLS_2V8 */
#define PWR_CR_PLS_2V8			PWR_CR_PLS_LEV6
/** @brief Register or selector value represented by `PWR_CR_PLS_2V9` @def PWR_CR_PLS_2V9 */
#define PWR_CR_PLS_2V9			PWR_CR_PLS_LEV7

/** @brief Bit position of the `PWR_CR_DBP` field @def PWR_CR_DBP_Pos */
#define PWR_CR_DBP_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `PWR_CR_DBP` field @def PWR_CR_DBP_Msk */
#define PWR_CR_DBP_Msk			REG_BIT_MASK(PWR_CR_DBP_Pos)
/** @brief Disable Backup Domain write protection @def PWR_CR_DBP */
#define PWR_CR_DBP				PWR_CR_DBP_Msk

// ----------------------------------- PWR_CSR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `PWR_CSR_WUF` field @def PWR_CSR_WUF_Pos */
#define PWR_CSR_WUF_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `PWR_CSR_WUF` field @def PWR_CSR_WUF_Msk */
#define PWR_CSR_WUF_Msk			REG_BIT_MASK(PWR_CSR_WUF_Pos)
/** @brief Wakeup Flag @def PWR_CSR_WUF */
#define PWR_CSR_WUF				PWR_CSR_WUF_Msk
/** @brief Bit position of the `PWR_CSR_SBF` field @def PWR_CSR_SBF_Pos */
#define PWR_CSR_SBF_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `PWR_CSR_SBF` field @def PWR_CSR_SBF_Msk */
#define PWR_CSR_SBF_Msk			REG_BIT_MASK(PWR_CSR_SBF_Pos)
/** @brief Standby Flag @def PWR_CSR_SBF */
#define PWR_CSR_SBF				PWR_CSR_SBF_Msk
/** @brief Bit position of the `PWR_CSR_PVDO` field @def PWR_CSR_PVDO_Pos */
#define PWR_CSR_PVDO_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `PWR_CSR_PVDO` field @def PWR_CSR_PVDO_Msk */
#define PWR_CSR_PVDO_Msk		REG_BIT_MASK(PWR_CSR_PVDO_Pos)
/** @brief PVD Output @def PWR_CSR_PVDO */
#define PWR_CSR_PVDO			PWR_CSR_PVDO_Msk
/** @brief Bit position of the `PWR_CSR_EWUP` field @def PWR_CSR_EWUP_Pos */
#define PWR_CSR_EWUP_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `PWR_CSR_EWUP` field @def PWR_CSR_EWUP_Msk */
#define PWR_CSR_EWUP_Msk		REG_BIT_MASK(PWR_CSR_EWUP_Pos)
/** @brief Enable WKUP pin @def PWR_CSR_EWUP */
#define PWR_CSR_EWUP			PWR_CSR_EWUP_Msk

// ==================================================================================================== //
//										Backup (BKP) Register Defines									//
// ==================================================================================================== //

// ----------------------------------- BKP_DR1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `BKP_DR1_D` field @def BKP_DR1_D_Pos */
#define BKP_DR1_D_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `BKP_DR1_D` field @def BKP_DR1_D_Width */
#define BKP_DR1_D_Width			((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `BKP_DR1_D` field @def BKP_DR1_D_Msk */
#define BKP_DR1_D_Msk			REG_FIELD_MASK(BKP_DR1_D_Pos, BKP_DR1_D_Width)
/** @brief Backup data @def BKP_DR1_D */
#define BKP_DR1_D				BKP_DR1_D_Msk

// ----------------------------------- BKP_DR2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `BKP_DR2_D` field @def BKP_DR2_D_Pos */
#define BKP_DR2_D_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `BKP_DR2_D` field @def BKP_DR2_D_Width */
#define BKP_DR2_D_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `BKP_DR2_D` field @def BKP_DR2_D_Msk */
#define BKP_DR2_D_Msk		REG_FIELD_MASK(BKP_DR2_D_Pos, BKP_DR2_D_Width)
/** @brief Backup data @def BKP_DR2_D */
#define BKP_DR2_D			BKP_DR2_D_Msk

// ----------------------------------- BKP_DR3 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `BKP_DR3_D` field @def BKP_DR3_D_Pos */
#define BKP_DR3_D_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `BKP_DR3_D` field @def BKP_DR3_D_Width */
#define BKP_DR3_D_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `BKP_DR3_D` field @def BKP_DR3_D_Msk */
#define BKP_DR3_D_Msk		REG_FIELD_MASK(BKP_DR3_D_Pos, BKP_DR3_D_Width)
/** @brief Backup data @def BKP_DR3_D */
#define BKP_DR3_D			BKP_DR3_D_Msk

// ----------------------------------- BKP_DR4 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `BKP_DR4_D` field @def BKP_DR4_D_Pos */
#define BKP_DR4_D_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `BKP_DR4_D` field @def BKP_DR4_D_Width */
#define BKP_DR4_D_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `BKP_DR4_D` field @def BKP_DR4_D_Msk */
#define BKP_DR4_D_Msk		REG_FIELD_MASK(BKP_DR4_D_Pos, BKP_DR4_D_Width)
/** @brief Backup data @def BKP_DR4_D */
#define BKP_DR4_D			BKP_DR4_D_Msk

// ----------------------------------- BKP_DR5 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `BKP_DR5_D` field @def BKP_DR5_D_Pos */
#define BKP_DR5_D_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `BKP_DR5_D` field @def BKP_DR5_D_Width */
#define BKP_DR5_D_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `BKP_DR5_D` field @def BKP_DR5_D_Msk */
#define BKP_DR5_D_Msk		REG_FIELD_MASK(BKP_DR5_D_Pos, BKP_DR5_D_Width)
/** @brief Backup data @def BKP_DR5_D */
#define BKP_DR5_D			BKP_DR5_D_Msk

// ----------------------------------- BKP_DR6 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `BKP_DR6_D` field @def BKP_DR6_D_Pos */
#define BKP_DR6_D_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `BKP_DR6_D` field @def BKP_DR6_D_Width */
#define BKP_DR6_D_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `BKP_DR6_D` field @def BKP_DR6_D_Msk */
#define BKP_DR6_D_Msk		REG_FIELD_MASK(BKP_DR6_D_Pos, BKP_DR6_D_Width)
/** @brief Backup data @def BKP_DR6_D */
#define BKP_DR6_D			BKP_DR6_D_Msk

// ----------------------------------- BKP_DR7 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `BKP_DR7_D` field @def BKP_DR7_D_Pos */
#define BKP_DR7_D_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `BKP_DR7_D` field @def BKP_DR7_D_Width */
#define BKP_DR7_D_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `BKP_DR7_D` field @def BKP_DR7_D_Msk */
#define BKP_DR7_D_Msk		REG_FIELD_MASK(BKP_DR7_D_Pos, BKP_DR7_D_Width)
/** @brief Backup data @def BKP_DR7_D */
#define BKP_DR7_D			BKP_DR7_D_Msk

// ----------------------------------- BKP_DR8 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `BKP_DR8_D` field @def BKP_DR8_D_Pos */
#define BKP_DR8_D_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `BKP_DR8_D` field @def BKP_DR8_D_Width */
#define BKP_DR8_D_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `BKP_DR8_D` field @def BKP_DR8_D_Msk */
#define BKP_DR8_D_Msk		REG_FIELD_MASK(BKP_DR8_D_Pos, BKP_DR8_D_Width)
/** @brief Backup data @def BKP_DR8_D */
#define BKP_DR8_D			BKP_DR8_D_Msk

// ----------------------------------- BKP_DR9 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `BKP_DR9_D` field @def BKP_DR9_D_Pos */
#define BKP_DR9_D_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `BKP_DR9_D` field @def BKP_DR9_D_Width */
#define BKP_DR9_D_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `BKP_DR9_D` field @def BKP_DR9_D_Msk */
#define BKP_DR9_D_Msk		REG_FIELD_MASK(BKP_DR9_D_Pos, BKP_DR9_D_Width)
/** @brief Backup data @def BKP_DR9_D */
#define BKP_DR9_D			BKP_DR9_D_Msk

// ---------------------------------- BKP_DR10 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `BKP_DR10_D` field @def BKP_DR10_D_Pos */
#define BKP_DR10_D_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `BKP_DR10_D` field @def BKP_DR10_D_Width */
#define BKP_DR10_D_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `BKP_DR10_D` field @def BKP_DR10_D_Msk */
#define BKP_DR10_D_Msk			REG_FIELD_MASK(BKP_DR10_D_Pos, BKP_DR10_D_Width)
/** @brief Backup data @def BKP_DR10_D */
#define BKP_DR10_D				BKP_DR10_D_Msk

/** @brief Register or selector value represented by `RTC_BKP_NUMBER` @def RTC_BKP_NUMBER */
#define RTC_BKP_NUMBER			10

// ---------------------------------- BKP_RTCCR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `BKP_RTCCR_CAL` field @def BKP_RTCCR_CAL_Pos */
#define BKP_RTCCR_CAL_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `BKP_RTCCR_CAL` field @def BKP_RTCCR_CAL_Width */
#define BKP_RTCCR_CAL_Width		((reg_field_width_t) 7U)
/** @brief Register-positioned mask for the `BKP_RTCCR_CAL` field @def BKP_RTCCR_CAL_Msk */
#define BKP_RTCCR_CAL_Msk		REG_FIELD_MASK(BKP_RTCCR_CAL_Pos, BKP_RTCCR_CAL_Width)
/** @brief Calibration value @def BKP_RTCCR_CAL */
#define BKP_RTCCR_CAL			BKP_RTCCR_CAL_Msk
/** @brief Bit position of the `BKP_RTCCR_CCO` field @def BKP_RTCCR_CCO_Pos */
#define BKP_RTCCR_CCO_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `BKP_RTCCR_CCO` field @def BKP_RTCCR_CCO_Msk */
#define BKP_RTCCR_CCO_Msk		REG_BIT_MASK(BKP_RTCCR_CCO_Pos)
/** @brief Calibration Clock Output @def BKP_RTCCR_CCO */
#define BKP_RTCCR_CCO			BKP_RTCCR_CCO_Msk
/** @brief Bit position of the `BKP_RTCCR_ASOE` field @def BKP_RTCCR_ASOE_Pos */
#define BKP_RTCCR_ASOE_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `BKP_RTCCR_ASOE` field @def BKP_RTCCR_ASOE_Msk */
#define BKP_RTCCR_ASOE_Msk		REG_BIT_MASK(BKP_RTCCR_ASOE_Pos)
/** @brief Alarm or Second Output Enable @def BKP_RTCCR_ASOE */
#define BKP_RTCCR_ASOE			BKP_RTCCR_ASOE_Msk
/** @brief Bit position of the `BKP_RTCCR_ASOS` field @def BKP_RTCCR_ASOS_Pos */
#define BKP_RTCCR_ASOS_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `BKP_RTCCR_ASOS` field @def BKP_RTCCR_ASOS_Msk */
#define BKP_RTCCR_ASOS_Msk		REG_BIT_MASK(BKP_RTCCR_ASOS_Pos)
/** @brief Alarm or Second Output Selection @def BKP_RTCCR_ASOS */
#define BKP_RTCCR_ASOS			BKP_RTCCR_ASOS_Msk

// ----------------------------------- BKP_CR Register Bit Defines ------------------------------------ //
/** @brief Bit position of the `BKP_CR_TPE` field @def BKP_CR_TPE_Pos */
#define BKP_CR_TPE_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `BKP_CR_TPE` field @def BKP_CR_TPE_Msk */
#define BKP_CR_TPE_Msk		REG_BIT_MASK(BKP_CR_TPE_Pos)
/** @brief TAMPER pin enable @def BKP_CR_TPE */
#define BKP_CR_TPE			BKP_CR_TPE_Msk
/** @brief Bit position of the `BKP_CR_TPAL` field @def BKP_CR_TPAL_Pos */
#define BKP_CR_TPAL_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `BKP_CR_TPAL` field @def BKP_CR_TPAL_Msk */
#define BKP_CR_TPAL_Msk		REG_BIT_MASK(BKP_CR_TPAL_Pos)
/** @brief TAMPER pin active level @def BKP_CR_TPAL */
#define BKP_CR_TPAL			BKP_CR_TPAL_Msk

// ----------------------------------- BKP_CSR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `BKP_CSR_CTE` field @def BKP_CSR_CTE_Pos */
#define BKP_CSR_CTE_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `BKP_CSR_CTE` field @def BKP_CSR_CTE_Msk */
#define BKP_CSR_CTE_Msk			REG_BIT_MASK(BKP_CSR_CTE_Pos)
/** @brief Clear Tamper event @def BKP_CSR_CTE */
#define BKP_CSR_CTE				BKP_CSR_CTE_Msk
/** @brief Bit position of the `BKP_CSR_CTI` field @def BKP_CSR_CTI_Pos */
#define BKP_CSR_CTI_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `BKP_CSR_CTI` field @def BKP_CSR_CTI_Msk */
#define BKP_CSR_CTI_Msk			REG_BIT_MASK(BKP_CSR_CTI_Pos)
/** @brief Clear Tamper Interrupt @def BKP_CSR_CTI */
#define BKP_CSR_CTI				BKP_CSR_CTI_Msk
/** @brief Bit position of the `BKP_CSR_TPIE` field @def BKP_CSR_TPIE_Pos */
#define BKP_CSR_TPIE_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `BKP_CSR_TPIE` field @def BKP_CSR_TPIE_Msk */
#define BKP_CSR_TPIE_Msk		REG_BIT_MASK(BKP_CSR_TPIE_Pos)
/** @brief TAMPER Pin interrupt enable @def BKP_CSR_TPIE */
#define BKP_CSR_TPIE			BKP_CSR_TPIE_Msk
/** @brief Bit position of the `BKP_CSR_TEF` field @def BKP_CSR_TEF_Pos */
#define BKP_CSR_TEF_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `BKP_CSR_TEF` field @def BKP_CSR_TEF_Msk */
#define BKP_CSR_TEF_Msk			REG_BIT_MASK(BKP_CSR_TEF_Pos)
/** @brief Tamper Event Flag @def BKP_CSR_TEF */
#define BKP_CSR_TEF				BKP_CSR_TEF_Msk
/** @brief Bit position of the `BKP_CSR_TIF` field @def BKP_CSR_TIF_Pos */
#define BKP_CSR_TIF_Pos			((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `BKP_CSR_TIF` field @def BKP_CSR_TIF_Msk */
#define BKP_CSR_TIF_Msk			REG_BIT_MASK(BKP_CSR_TIF_Pos)
/** @brief Tamper Interrupt Flag @def BKP_CSR_TIF */
#define BKP_CSR_TIF				BKP_CSR_TIF_Msk

// ==================================================================================================== //
//										DMA Controller Register Defines									//
// ==================================================================================================== //

// ----------------------------------- DMA_ISR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `DMA_ISR_GIF1` field @def DMA_ISR_GIF1_Pos */
#define DMA_ISR_GIF1_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `DMA_ISR_GIF1` field @def DMA_ISR_GIF1_Msk */
#define DMA_ISR_GIF1_Msk		REG_BIT_MASK(DMA_ISR_GIF1_Pos)
/** @brief Channel 1 Global interrupt flag @def DMA_ISR_GIF1 */
#define DMA_ISR_GIF1			DMA_ISR_GIF1_Msk
/** @brief Bit position of the `DMA_ISR_TCIF1` field @def DMA_ISR_TCIF1_Pos */
#define DMA_ISR_TCIF1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `DMA_ISR_TCIF1` field @def DMA_ISR_TCIF1_Msk */
#define DMA_ISR_TCIF1_Msk		REG_BIT_MASK(DMA_ISR_TCIF1_Pos)
/** @brief Channel 1 Transfer Complete flag @def DMA_ISR_TCIF1 */
#define DMA_ISR_TCIF1			DMA_ISR_TCIF1_Msk
/** @brief Bit position of the `DMA_ISR_HTIF1` field @def DMA_ISR_HTIF1_Pos */
#define DMA_ISR_HTIF1_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `DMA_ISR_HTIF1` field @def DMA_ISR_HTIF1_Msk */
#define DMA_ISR_HTIF1_Msk		REG_BIT_MASK(DMA_ISR_HTIF1_Pos)
/** @brief Channel 1 Half Transfer flag @def DMA_ISR_HTIF1 */
#define DMA_ISR_HTIF1			DMA_ISR_HTIF1_Msk
/** @brief Bit position of the `DMA_ISR_TEIF1` field @def DMA_ISR_TEIF1_Pos */
#define DMA_ISR_TEIF1_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `DMA_ISR_TEIF1` field @def DMA_ISR_TEIF1_Msk */
#define DMA_ISR_TEIF1_Msk		REG_BIT_MASK(DMA_ISR_TEIF1_Pos)
/** @brief Channel 1 Transfer Error flag @def DMA_ISR_TEIF1 */
#define DMA_ISR_TEIF1			DMA_ISR_TEIF1_Msk
/** @brief Bit position of the `DMA_ISR_GIF2` field @def DMA_ISR_GIF2_Pos */
#define DMA_ISR_GIF2_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `DMA_ISR_GIF2` field @def DMA_ISR_GIF2_Msk */
#define DMA_ISR_GIF2_Msk		REG_BIT_MASK(DMA_ISR_GIF2_Pos)
/** @brief Channel 2 Global interrupt flag @def DMA_ISR_GIF2 */
#define DMA_ISR_GIF2			DMA_ISR_GIF2_Msk
/** @brief Bit position of the `DMA_ISR_TCIF2` field @def DMA_ISR_TCIF2_Pos */
#define DMA_ISR_TCIF2_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `DMA_ISR_TCIF2` field @def DMA_ISR_TCIF2_Msk */
#define DMA_ISR_TCIF2_Msk		REG_BIT_MASK(DMA_ISR_TCIF2_Pos)
/** @brief Channel 2 Transfer Complete flag @def DMA_ISR_TCIF2 */
#define DMA_ISR_TCIF2			DMA_ISR_TCIF2_Msk
/** @brief Bit position of the `DMA_ISR_HTIF2` field @def DMA_ISR_HTIF2_Pos */
#define DMA_ISR_HTIF2_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `DMA_ISR_HTIF2` field @def DMA_ISR_HTIF2_Msk */
#define DMA_ISR_HTIF2_Msk		REG_BIT_MASK(DMA_ISR_HTIF2_Pos)
/** @brief Channel 2 Half Transfer flag @def DMA_ISR_HTIF2 */
#define DMA_ISR_HTIF2			DMA_ISR_HTIF2_Msk
/** @brief Bit position of the `DMA_ISR_TEIF2` field @def DMA_ISR_TEIF2_Pos */
#define DMA_ISR_TEIF2_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `DMA_ISR_TEIF2` field @def DMA_ISR_TEIF2_Msk */
#define DMA_ISR_TEIF2_Msk		REG_BIT_MASK(DMA_ISR_TEIF2_Pos)
/** @brief Channel 2 Transfer Error flag @def DMA_ISR_TEIF2 */
#define DMA_ISR_TEIF2			DMA_ISR_TEIF2_Msk
/** @brief Bit position of the `DMA_ISR_GIF3` field @def DMA_ISR_GIF3_Pos */
#define DMA_ISR_GIF3_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `DMA_ISR_GIF3` field @def DMA_ISR_GIF3_Msk */
#define DMA_ISR_GIF3_Msk		REG_BIT_MASK(DMA_ISR_GIF3_Pos)
/** @brief Channel 3 Global interrupt flag @def DMA_ISR_GIF3 */
#define DMA_ISR_GIF3			DMA_ISR_GIF3_Msk
/** @brief Bit position of the `DMA_ISR_TCIF3` field @def DMA_ISR_TCIF3_Pos */
#define DMA_ISR_TCIF3_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `DMA_ISR_TCIF3` field @def DMA_ISR_TCIF3_Msk */
#define DMA_ISR_TCIF3_Msk		REG_BIT_MASK(DMA_ISR_TCIF3_Pos)
/** @brief Channel 3 Transfer Complete flag @def DMA_ISR_TCIF3 */
#define DMA_ISR_TCIF3			DMA_ISR_TCIF3_Msk
/** @brief Bit position of the `DMA_ISR_HTIF3` field @def DMA_ISR_HTIF3_Pos */
#define DMA_ISR_HTIF3_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `DMA_ISR_HTIF3` field @def DMA_ISR_HTIF3_Msk */
#define DMA_ISR_HTIF3_Msk		REG_BIT_MASK(DMA_ISR_HTIF3_Pos)
/** @brief Channel 3 Half Transfer flag @def DMA_ISR_HTIF3 */
#define DMA_ISR_HTIF3			DMA_ISR_HTIF3_Msk
/** @brief Bit position of the `DMA_ISR_TEIF3` field @def DMA_ISR_TEIF3_Pos */
#define DMA_ISR_TEIF3_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `DMA_ISR_TEIF3` field @def DMA_ISR_TEIF3_Msk */
#define DMA_ISR_TEIF3_Msk		REG_BIT_MASK(DMA_ISR_TEIF3_Pos)
/** @brief Channel 3 Transfer Error flag @def DMA_ISR_TEIF3 */
#define DMA_ISR_TEIF3			DMA_ISR_TEIF3_Msk
/** @brief Bit position of the `DMA_ISR_GIF4` field @def DMA_ISR_GIF4_Pos */
#define DMA_ISR_GIF4_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `DMA_ISR_GIF4` field @def DMA_ISR_GIF4_Msk */
#define DMA_ISR_GIF4_Msk		REG_BIT_MASK(DMA_ISR_GIF4_Pos)
/** @brief Channel 4 Global interrupt flag @def DMA_ISR_GIF4 */
#define DMA_ISR_GIF4			DMA_ISR_GIF4_Msk
/** @brief Bit position of the `DMA_ISR_TCIF4` field @def DMA_ISR_TCIF4_Pos */
#define DMA_ISR_TCIF4_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `DMA_ISR_TCIF4` field @def DMA_ISR_TCIF4_Msk */
#define DMA_ISR_TCIF4_Msk		REG_BIT_MASK(DMA_ISR_TCIF4_Pos)
/** @brief Channel 4 Transfer Complete flag @def DMA_ISR_TCIF4 */
#define DMA_ISR_TCIF4			DMA_ISR_TCIF4_Msk
/** @brief Bit position of the `DMA_ISR_HTIF4` field @def DMA_ISR_HTIF4_Pos */
#define DMA_ISR_HTIF4_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `DMA_ISR_HTIF4` field @def DMA_ISR_HTIF4_Msk */
#define DMA_ISR_HTIF4_Msk		REG_BIT_MASK(DMA_ISR_HTIF4_Pos)
/** @brief Channel 4 Half Transfer flag @def DMA_ISR_HTIF4 */
#define DMA_ISR_HTIF4			DMA_ISR_HTIF4_Msk
/** @brief Bit position of the `DMA_ISR_TEIF4` field @def DMA_ISR_TEIF4_Pos */
#define DMA_ISR_TEIF4_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `DMA_ISR_TEIF4` field @def DMA_ISR_TEIF4_Msk */
#define DMA_ISR_TEIF4_Msk		REG_BIT_MASK(DMA_ISR_TEIF4_Pos)
/** @brief Channel 4 Transfer Error flag @def DMA_ISR_TEIF4 */
#define DMA_ISR_TEIF4			DMA_ISR_TEIF4_Msk
/** @brief Bit position of the `DMA_ISR_GIF5` field @def DMA_ISR_GIF5_Pos */
#define DMA_ISR_GIF5_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `DMA_ISR_GIF5` field @def DMA_ISR_GIF5_Msk */
#define DMA_ISR_GIF5_Msk		REG_BIT_MASK(DMA_ISR_GIF5_Pos)
/** @brief Channel 5 Global interrupt flag @def DMA_ISR_GIF5 */
#define DMA_ISR_GIF5			DMA_ISR_GIF5_Msk
/** @brief Bit position of the `DMA_ISR_TCIF5` field @def DMA_ISR_TCIF5_Pos */
#define DMA_ISR_TCIF5_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `DMA_ISR_TCIF5` field @def DMA_ISR_TCIF5_Msk */
#define DMA_ISR_TCIF5_Msk		REG_BIT_MASK(DMA_ISR_TCIF5_Pos)
/** @brief Channel 5 Transfer Complete flag @def DMA_ISR_TCIF5 */
#define DMA_ISR_TCIF5			DMA_ISR_TCIF5_Msk
/** @brief Bit position of the `DMA_ISR_HTIF5` field @def DMA_ISR_HTIF5_Pos */
#define DMA_ISR_HTIF5_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `DMA_ISR_HTIF5` field @def DMA_ISR_HTIF5_Msk */
#define DMA_ISR_HTIF5_Msk		REG_BIT_MASK(DMA_ISR_HTIF5_Pos)
/** @brief Channel 5 Half Transfer flag @def DMA_ISR_HTIF5 */
#define DMA_ISR_HTIF5			DMA_ISR_HTIF5_Msk
/** @brief Bit position of the `DMA_ISR_TEIF5` field @def DMA_ISR_TEIF5_Pos */
#define DMA_ISR_TEIF5_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `DMA_ISR_TEIF5` field @def DMA_ISR_TEIF5_Msk */
#define DMA_ISR_TEIF5_Msk		REG_BIT_MASK(DMA_ISR_TEIF5_Pos)
/** @brief Channel 5 Transfer Error flag @def DMA_ISR_TEIF5 */
#define DMA_ISR_TEIF5			DMA_ISR_TEIF5_Msk
/** @brief Bit position of the `DMA_ISR_GIF6` field @def DMA_ISR_GIF6_Pos */
#define DMA_ISR_GIF6_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `DMA_ISR_GIF6` field @def DMA_ISR_GIF6_Msk */
#define DMA_ISR_GIF6_Msk		REG_BIT_MASK(DMA_ISR_GIF6_Pos)
/** @brief Channel 6 Global interrupt flag @def DMA_ISR_GIF6 */
#define DMA_ISR_GIF6			DMA_ISR_GIF6_Msk
/** @brief Bit position of the `DMA_ISR_TCIF6` field @def DMA_ISR_TCIF6_Pos */
#define DMA_ISR_TCIF6_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `DMA_ISR_TCIF6` field @def DMA_ISR_TCIF6_Msk */
#define DMA_ISR_TCIF6_Msk		REG_BIT_MASK(DMA_ISR_TCIF6_Pos)
/** @brief Channel 6 Transfer Complete flag @def DMA_ISR_TCIF6 */
#define DMA_ISR_TCIF6			DMA_ISR_TCIF6_Msk
/** @brief Bit position of the `DMA_ISR_HTIF6` field @def DMA_ISR_HTIF6_Pos */
#define DMA_ISR_HTIF6_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `DMA_ISR_HTIF6` field @def DMA_ISR_HTIF6_Msk */
#define DMA_ISR_HTIF6_Msk		REG_BIT_MASK(DMA_ISR_HTIF6_Pos)
/** @brief Channel 6 Half Transfer flag @def DMA_ISR_HTIF6 */
#define DMA_ISR_HTIF6			DMA_ISR_HTIF6_Msk
/** @brief Bit position of the `DMA_ISR_TEIF6` field @def DMA_ISR_TEIF6_Pos */
#define DMA_ISR_TEIF6_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `DMA_ISR_TEIF6` field @def DMA_ISR_TEIF6_Msk */
#define DMA_ISR_TEIF6_Msk		REG_BIT_MASK(DMA_ISR_TEIF6_Pos)
/** @brief Channel 6 Transfer Error flag @def DMA_ISR_TEIF6 */
#define DMA_ISR_TEIF6			DMA_ISR_TEIF6_Msk
/** @brief Bit position of the `DMA_ISR_GIF7` field @def DMA_ISR_GIF7_Pos */
#define DMA_ISR_GIF7_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `DMA_ISR_GIF7` field @def DMA_ISR_GIF7_Msk */
#define DMA_ISR_GIF7_Msk		REG_BIT_MASK(DMA_ISR_GIF7_Pos)
/** @brief Channel 7 Global interrupt flag @def DMA_ISR_GIF7 */
#define DMA_ISR_GIF7			DMA_ISR_GIF7_Msk
/** @brief Bit position of the `DMA_ISR_TCIF7` field @def DMA_ISR_TCIF7_Pos */
#define DMA_ISR_TCIF7_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `DMA_ISR_TCIF7` field @def DMA_ISR_TCIF7_Msk */
#define DMA_ISR_TCIF7_Msk		REG_BIT_MASK(DMA_ISR_TCIF7_Pos)
/** @brief Channel 7 Transfer Complete flag @def DMA_ISR_TCIF7 */
#define DMA_ISR_TCIF7			DMA_ISR_TCIF7_Msk
/** @brief Bit position of the `DMA_ISR_HTIF7` field @def DMA_ISR_HTIF7_Pos */
#define DMA_ISR_HTIF7_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `DMA_ISR_HTIF7` field @def DMA_ISR_HTIF7_Msk */
#define DMA_ISR_HTIF7_Msk		REG_BIT_MASK(DMA_ISR_HTIF7_Pos)
/** @brief Channel 7 Half Transfer flag @def DMA_ISR_HTIF7 */
#define DMA_ISR_HTIF7			DMA_ISR_HTIF7_Msk
/** @brief Bit position of the `DMA_ISR_TEIF7` field @def DMA_ISR_TEIF7_Pos */
#define DMA_ISR_TEIF7_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `DMA_ISR_TEIF7` field @def DMA_ISR_TEIF7_Msk */
#define DMA_ISR_TEIF7_Msk		REG_BIT_MASK(DMA_ISR_TEIF7_Pos)
/** @brief Channel 7 Transfer Error flag @def DMA_ISR_TEIF7 */
#define DMA_ISR_TEIF7			DMA_ISR_TEIF7_Msk

// ---------------------------------- DMA_IFCR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `DMA_IFCR_CGIF1` field @def DMA_IFCR_CGIF1_Pos */
#define DMA_IFCR_CGIF1_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `DMA_IFCR_CGIF1` field @def DMA_IFCR_CGIF1_Msk */
#define DMA_IFCR_CGIF1_Msk		REG_BIT_MASK(DMA_IFCR_CGIF1_Pos)
/** @brief Channel 1 Global interrupt clear @def DMA_IFCR_CGIF1 */
#define DMA_IFCR_CGIF1			DMA_IFCR_CGIF1_Msk
/** @brief Bit position of the `DMA_IFCR_CTCIF1` field @def DMA_IFCR_CTCIF1_Pos */
#define DMA_IFCR_CTCIF1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTCIF1` field @def DMA_IFCR_CTCIF1_Msk */
#define DMA_IFCR_CTCIF1_Msk		REG_BIT_MASK(DMA_IFCR_CTCIF1_Pos)
/** @brief Channel 1 Transfer Complete clear @def DMA_IFCR_CTCIF1 */
#define DMA_IFCR_CTCIF1			DMA_IFCR_CTCIF1_Msk
/** @brief Bit position of the `DMA_IFCR_CHTIF1` field @def DMA_IFCR_CHTIF1_Pos */
#define DMA_IFCR_CHTIF1_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `DMA_IFCR_CHTIF1` field @def DMA_IFCR_CHTIF1_Msk */
#define DMA_IFCR_CHTIF1_Msk		REG_BIT_MASK(DMA_IFCR_CHTIF1_Pos)
/** @brief Channel 1 Half Transfer clear @def DMA_IFCR_CHTIF1 */
#define DMA_IFCR_CHTIF1			DMA_IFCR_CHTIF1_Msk
/** @brief Bit position of the `DMA_IFCR_CTEIF1` field @def DMA_IFCR_CTEIF1_Pos */
#define DMA_IFCR_CTEIF1_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTEIF1` field @def DMA_IFCR_CTEIF1_Msk */
#define DMA_IFCR_CTEIF1_Msk		REG_BIT_MASK(DMA_IFCR_CTEIF1_Pos)
/** @brief Channel 1 Transfer Error clear @def DMA_IFCR_CTEIF1 */
#define DMA_IFCR_CTEIF1			DMA_IFCR_CTEIF1_Msk
/** @brief Bit position of the `DMA_IFCR_CGIF2` field @def DMA_IFCR_CGIF2_Pos */
#define DMA_IFCR_CGIF2_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `DMA_IFCR_CGIF2` field @def DMA_IFCR_CGIF2_Msk */
#define DMA_IFCR_CGIF2_Msk		REG_BIT_MASK(DMA_IFCR_CGIF2_Pos)
/** @brief Channel 2 Global interrupt clear @def DMA_IFCR_CGIF2 */
#define DMA_IFCR_CGIF2			DMA_IFCR_CGIF2_Msk
/** @brief Bit position of the `DMA_IFCR_CTCIF2` field @def DMA_IFCR_CTCIF2_Pos */
#define DMA_IFCR_CTCIF2_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTCIF2` field @def DMA_IFCR_CTCIF2_Msk */
#define DMA_IFCR_CTCIF2_Msk		REG_BIT_MASK(DMA_IFCR_CTCIF2_Pos)
/** @brief Channel 2 Transfer Complete clear @def DMA_IFCR_CTCIF2 */
#define DMA_IFCR_CTCIF2			DMA_IFCR_CTCIF2_Msk
/** @brief Bit position of the `DMA_IFCR_CHTIF2` field @def DMA_IFCR_CHTIF2_Pos */
#define DMA_IFCR_CHTIF2_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `DMA_IFCR_CHTIF2` field @def DMA_IFCR_CHTIF2_Msk */
#define DMA_IFCR_CHTIF2_Msk		REG_BIT_MASK(DMA_IFCR_CHTIF2_Pos)
/** @brief Channel 2 Half Transfer clear @def DMA_IFCR_CHTIF2 */
#define DMA_IFCR_CHTIF2			DMA_IFCR_CHTIF2_Msk
/** @brief Bit position of the `DMA_IFCR_CTEIF2` field @def DMA_IFCR_CTEIF2_Pos */
#define DMA_IFCR_CTEIF2_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTEIF2` field @def DMA_IFCR_CTEIF2_Msk */
#define DMA_IFCR_CTEIF2_Msk		REG_BIT_MASK(DMA_IFCR_CTEIF2_Pos)
/** @brief Channel 2 Transfer Error clear @def DMA_IFCR_CTEIF2 */
#define DMA_IFCR_CTEIF2			DMA_IFCR_CTEIF2_Msk
/** @brief Bit position of the `DMA_IFCR_CGIF3` field @def DMA_IFCR_CGIF3_Pos */
#define DMA_IFCR_CGIF3_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `DMA_IFCR_CGIF3` field @def DMA_IFCR_CGIF3_Msk */
#define DMA_IFCR_CGIF3_Msk		REG_BIT_MASK(DMA_IFCR_CGIF3_Pos)
/** @brief Channel 3 Global interrupt clear @def DMA_IFCR_CGIF3 */
#define DMA_IFCR_CGIF3			DMA_IFCR_CGIF3_Msk
/** @brief Bit position of the `DMA_IFCR_CTCIF3` field @def DMA_IFCR_CTCIF3_Pos */
#define DMA_IFCR_CTCIF3_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTCIF3` field @def DMA_IFCR_CTCIF3_Msk */
#define DMA_IFCR_CTCIF3_Msk		REG_BIT_MASK(DMA_IFCR_CTCIF3_Pos)
/** @brief Channel 3 Transfer Complete clear @def DMA_IFCR_CTCIF3 */
#define DMA_IFCR_CTCIF3			DMA_IFCR_CTCIF3_Msk
/** @brief Bit position of the `DMA_IFCR_CHTIF3` field @def DMA_IFCR_CHTIF3_Pos */
#define DMA_IFCR_CHTIF3_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `DMA_IFCR_CHTIF3` field @def DMA_IFCR_CHTIF3_Msk */
#define DMA_IFCR_CHTIF3_Msk		REG_BIT_MASK(DMA_IFCR_CHTIF3_Pos)
/** @brief Channel 3 Half Transfer clear @def DMA_IFCR_CHTIF3 */
#define DMA_IFCR_CHTIF3			DMA_IFCR_CHTIF3_Msk
/** @brief Bit position of the `DMA_IFCR_CTEIF3` field @def DMA_IFCR_CTEIF3_Pos */
#define DMA_IFCR_CTEIF3_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTEIF3` field @def DMA_IFCR_CTEIF3_Msk */
#define DMA_IFCR_CTEIF3_Msk		REG_BIT_MASK(DMA_IFCR_CTEIF3_Pos)
/** @brief Channel 3 Transfer Error clear @def DMA_IFCR_CTEIF3 */
#define DMA_IFCR_CTEIF3			DMA_IFCR_CTEIF3_Msk
/** @brief Bit position of the `DMA_IFCR_CGIF4` field @def DMA_IFCR_CGIF4_Pos */
#define DMA_IFCR_CGIF4_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `DMA_IFCR_CGIF4` field @def DMA_IFCR_CGIF4_Msk */
#define DMA_IFCR_CGIF4_Msk		REG_BIT_MASK(DMA_IFCR_CGIF4_Pos)
/** @brief Channel 4 Global interrupt clear @def DMA_IFCR_CGIF4 */
#define DMA_IFCR_CGIF4			DMA_IFCR_CGIF4_Msk
/** @brief Bit position of the `DMA_IFCR_CTCIF4` field @def DMA_IFCR_CTCIF4_Pos */
#define DMA_IFCR_CTCIF4_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTCIF4` field @def DMA_IFCR_CTCIF4_Msk */
#define DMA_IFCR_CTCIF4_Msk		REG_BIT_MASK(DMA_IFCR_CTCIF4_Pos)
/** @brief Channel 4 Transfer Complete clear @def DMA_IFCR_CTCIF4 */
#define DMA_IFCR_CTCIF4			DMA_IFCR_CTCIF4_Msk
/** @brief Bit position of the `DMA_IFCR_CHTIF4` field @def DMA_IFCR_CHTIF4_Pos */
#define DMA_IFCR_CHTIF4_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `DMA_IFCR_CHTIF4` field @def DMA_IFCR_CHTIF4_Msk */
#define DMA_IFCR_CHTIF4_Msk		REG_BIT_MASK(DMA_IFCR_CHTIF4_Pos)
/** @brief Channel 4 Half Transfer clear @def DMA_IFCR_CHTIF4 */
#define DMA_IFCR_CHTIF4			DMA_IFCR_CHTIF4_Msk
/** @brief Bit position of the `DMA_IFCR_CTEIF4` field @def DMA_IFCR_CTEIF4_Pos */
#define DMA_IFCR_CTEIF4_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTEIF4` field @def DMA_IFCR_CTEIF4_Msk */
#define DMA_IFCR_CTEIF4_Msk		REG_BIT_MASK(DMA_IFCR_CTEIF4_Pos)
/** @brief Channel 4 Transfer Error clear @def DMA_IFCR_CTEIF4 */
#define DMA_IFCR_CTEIF4			DMA_IFCR_CTEIF4_Msk
/** @brief Bit position of the `DMA_IFCR_CGIF5` field @def DMA_IFCR_CGIF5_Pos */
#define DMA_IFCR_CGIF5_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `DMA_IFCR_CGIF5` field @def DMA_IFCR_CGIF5_Msk */
#define DMA_IFCR_CGIF5_Msk		REG_BIT_MASK(DMA_IFCR_CGIF5_Pos)
/** @brief Channel 5 Global interrupt clear @def DMA_IFCR_CGIF5 */
#define DMA_IFCR_CGIF5			DMA_IFCR_CGIF5_Msk
/** @brief Bit position of the `DMA_IFCR_CTCIF5` field @def DMA_IFCR_CTCIF5_Pos */
#define DMA_IFCR_CTCIF5_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTCIF5` field @def DMA_IFCR_CTCIF5_Msk */
#define DMA_IFCR_CTCIF5_Msk		REG_BIT_MASK(DMA_IFCR_CTCIF5_Pos)
/** @brief Channel 5 Transfer Complete clear @def DMA_IFCR_CTCIF5 */
#define DMA_IFCR_CTCIF5			DMA_IFCR_CTCIF5_Msk
/** @brief Bit position of the `DMA_IFCR_CHTIF5` field @def DMA_IFCR_CHTIF5_Pos */
#define DMA_IFCR_CHTIF5_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `DMA_IFCR_CHTIF5` field @def DMA_IFCR_CHTIF5_Msk */
#define DMA_IFCR_CHTIF5_Msk		REG_BIT_MASK(DMA_IFCR_CHTIF5_Pos)
/** @brief Channel 5 Half Transfer clear @def DMA_IFCR_CHTIF5 */
#define DMA_IFCR_CHTIF5			DMA_IFCR_CHTIF5_Msk
/** @brief Bit position of the `DMA_IFCR_CTEIF5` field @def DMA_IFCR_CTEIF5_Pos */
#define DMA_IFCR_CTEIF5_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTEIF5` field @def DMA_IFCR_CTEIF5_Msk */
#define DMA_IFCR_CTEIF5_Msk		REG_BIT_MASK(DMA_IFCR_CTEIF5_Pos)
/** @brief Channel 5 Transfer Error clear @def DMA_IFCR_CTEIF5 */
#define DMA_IFCR_CTEIF5			DMA_IFCR_CTEIF5_Msk
/** @brief Bit position of the `DMA_IFCR_CGIF6` field @def DMA_IFCR_CGIF6_Pos */
#define DMA_IFCR_CGIF6_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `DMA_IFCR_CGIF6` field @def DMA_IFCR_CGIF6_Msk */
#define DMA_IFCR_CGIF6_Msk		REG_BIT_MASK(DMA_IFCR_CGIF6_Pos)
/** @brief Channel 6 Global interrupt clear @def DMA_IFCR_CGIF6 */
#define DMA_IFCR_CGIF6			DMA_IFCR_CGIF6_Msk
/** @brief Bit position of the `DMA_IFCR_CTCIF6` field @def DMA_IFCR_CTCIF6_Pos */
#define DMA_IFCR_CTCIF6_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTCIF6` field @def DMA_IFCR_CTCIF6_Msk */
#define DMA_IFCR_CTCIF6_Msk		REG_BIT_MASK(DMA_IFCR_CTCIF6_Pos)
/** @brief Channel 6 Transfer Complete clear @def DMA_IFCR_CTCIF6 */
#define DMA_IFCR_CTCIF6			DMA_IFCR_CTCIF6_Msk
/** @brief Bit position of the `DMA_IFCR_CHTIF6` field @def DMA_IFCR_CHTIF6_Pos */
#define DMA_IFCR_CHTIF6_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `DMA_IFCR_CHTIF6` field @def DMA_IFCR_CHTIF6_Msk */
#define DMA_IFCR_CHTIF6_Msk		REG_BIT_MASK(DMA_IFCR_CHTIF6_Pos)
/** @brief Channel 6 Half Transfer clear @def DMA_IFCR_CHTIF6 */
#define DMA_IFCR_CHTIF6			DMA_IFCR_CHTIF6_Msk
/** @brief Bit position of the `DMA_IFCR_CTEIF6` field @def DMA_IFCR_CTEIF6_Pos */
#define DMA_IFCR_CTEIF6_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTEIF6` field @def DMA_IFCR_CTEIF6_Msk */
#define DMA_IFCR_CTEIF6_Msk		REG_BIT_MASK(DMA_IFCR_CTEIF6_Pos)
/** @brief Channel 6 Transfer Error clear @def DMA_IFCR_CTEIF6 */
#define DMA_IFCR_CTEIF6			DMA_IFCR_CTEIF6_Msk
/** @brief Bit position of the `DMA_IFCR_CGIF7` field @def DMA_IFCR_CGIF7_Pos */
#define DMA_IFCR_CGIF7_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `DMA_IFCR_CGIF7` field @def DMA_IFCR_CGIF7_Msk */
#define DMA_IFCR_CGIF7_Msk		REG_BIT_MASK(DMA_IFCR_CGIF7_Pos)
/** @brief Channel 7 Global interrupt clear @def DMA_IFCR_CGIF7 */
#define DMA_IFCR_CGIF7			DMA_IFCR_CGIF7_Msk
/** @brief Bit position of the `DMA_IFCR_CTCIF7` field @def DMA_IFCR_CTCIF7_Pos */
#define DMA_IFCR_CTCIF7_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTCIF7` field @def DMA_IFCR_CTCIF7_Msk */
#define DMA_IFCR_CTCIF7_Msk		REG_BIT_MASK(DMA_IFCR_CTCIF7_Pos)
/** @brief Channel 7 Transfer Complete clear @def DMA_IFCR_CTCIF7 */
#define DMA_IFCR_CTCIF7			DMA_IFCR_CTCIF7_Msk
/** @brief Bit position of the `DMA_IFCR_CHTIF7` field @def DMA_IFCR_CHTIF7_Pos */
#define DMA_IFCR_CHTIF7_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `DMA_IFCR_CHTIF7` field @def DMA_IFCR_CHTIF7_Msk */
#define DMA_IFCR_CHTIF7_Msk		REG_BIT_MASK(DMA_IFCR_CHTIF7_Pos)
/** @brief Channel 7 Half Transfer clear @def DMA_IFCR_CHTIF7 */
#define DMA_IFCR_CHTIF7			DMA_IFCR_CHTIF7_Msk
/** @brief Bit position of the `DMA_IFCR_CTEIF7` field @def DMA_IFCR_CTEIF7_Pos */
#define DMA_IFCR_CTEIF7_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `DMA_IFCR_CTEIF7` field @def DMA_IFCR_CTEIF7_Msk */
#define DMA_IFCR_CTEIF7_Msk		REG_BIT_MASK(DMA_IFCR_CTEIF7_Pos)
/** @brief Channel 7 Transfer Error clear @def DMA_IFCR_CTEIF7 */
#define DMA_IFCR_CTEIF7			DMA_IFCR_CTEIF7_Msk

// ----------------------------------- DMA_CCR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `DMA_CCR_EN` field @def DMA_CCR_EN_Pos */
#define DMA_CCR_EN_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `DMA_CCR_EN` field @def DMA_CCR_EN_Msk */
#define DMA_CCR_EN_Msk			REG_BIT_MASK(DMA_CCR_EN_Pos)
/** @brief Channel enable @def DMA_CCR_EN */
#define DMA_CCR_EN				DMA_CCR_EN_Msk
/** @brief Bit position of the `DMA_CCR_TCIE` field @def DMA_CCR_TCIE_Pos */
#define DMA_CCR_TCIE_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `DMA_CCR_TCIE` field @def DMA_CCR_TCIE_Msk */
#define DMA_CCR_TCIE_Msk		REG_BIT_MASK(DMA_CCR_TCIE_Pos)
/** @brief Transfer complete interrupt enable @def DMA_CCR_TCIE */
#define DMA_CCR_TCIE			DMA_CCR_TCIE_Msk
/** @brief Bit position of the `DMA_CCR_HTIE` field @def DMA_CCR_HTIE_Pos */
#define DMA_CCR_HTIE_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `DMA_CCR_HTIE` field @def DMA_CCR_HTIE_Msk */
#define DMA_CCR_HTIE_Msk		REG_BIT_MASK(DMA_CCR_HTIE_Pos)
/** @brief Half Transfer interrupt enable @def DMA_CCR_HTIE */
#define DMA_CCR_HTIE			DMA_CCR_HTIE_Msk
/** @brief Bit position of the `DMA_CCR_TEIE` field @def DMA_CCR_TEIE_Pos */
#define DMA_CCR_TEIE_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `DMA_CCR_TEIE` field @def DMA_CCR_TEIE_Msk */
#define DMA_CCR_TEIE_Msk		REG_BIT_MASK(DMA_CCR_TEIE_Pos)
/** @brief Transfer error interrupt enable @def DMA_CCR_TEIE */
#define DMA_CCR_TEIE			DMA_CCR_TEIE_Msk
/** @brief Bit position of the `DMA_CCR_DIR` field @def DMA_CCR_DIR_Pos */
#define DMA_CCR_DIR_Pos			((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `DMA_CCR_DIR` field @def DMA_CCR_DIR_Msk */
#define DMA_CCR_DIR_Msk			REG_BIT_MASK(DMA_CCR_DIR_Pos)
/** @brief Data transfer direction @def DMA_CCR_DIR */
#define DMA_CCR_DIR				DMA_CCR_DIR_Msk
/** @brief Bit position of the `DMA_CCR_CIRC` field @def DMA_CCR_CIRC_Pos */
#define DMA_CCR_CIRC_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `DMA_CCR_CIRC` field @def DMA_CCR_CIRC_Msk */
#define DMA_CCR_CIRC_Msk		REG_BIT_MASK(DMA_CCR_CIRC_Pos)
/** @brief Circular mode @def DMA_CCR_CIRC */
#define DMA_CCR_CIRC			DMA_CCR_CIRC_Msk
/** @brief Bit position of the `DMA_CCR_PINC` field @def DMA_CCR_PINC_Pos */
#define DMA_CCR_PINC_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `DMA_CCR_PINC` field @def DMA_CCR_PINC_Msk */
#define DMA_CCR_PINC_Msk		REG_BIT_MASK(DMA_CCR_PINC_Pos)
/** @brief Peripheral increment mode @def DMA_CCR_PINC */
#define DMA_CCR_PINC			DMA_CCR_PINC_Msk
/** @brief Bit position of the `DMA_CCR_MINC` field @def DMA_CCR_MINC_Pos */
#define DMA_CCR_MINC_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `DMA_CCR_MINC` field @def DMA_CCR_MINC_Msk */
#define DMA_CCR_MINC_Msk		REG_BIT_MASK(DMA_CCR_MINC_Pos)
/** @brief Memory increment mode @def DMA_CCR_MINC */
#define DMA_CCR_MINC			DMA_CCR_MINC_Msk

/** @brief Bit position of the `DMA_CCR_PSIZE` field @def DMA_CCR_PSIZE_Pos */
#define DMA_CCR_PSIZE_Pos		((reg_bit_pos_t) 8U)
/** @brief Width of the `DMA_CCR_PSIZE` field @def DMA_CCR_PSIZE_Width */
#define DMA_CCR_PSIZE_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `DMA_CCR_PSIZE` field @def DMA_CCR_PSIZE_Msk */
#define DMA_CCR_PSIZE_Msk		REG_FIELD_MASK(DMA_CCR_PSIZE_Pos, DMA_CCR_PSIZE_Width)
/** @brief PSIZE[1:0] bits (Peripheral size) @def DMA_CCR_PSIZE */
#define DMA_CCR_PSIZE			DMA_CCR_PSIZE_Msk
/** @brief Register or selector value represented by `DMA_CCR_PSIZE_0` @def DMA_CCR_PSIZE_0 */
#define DMA_CCR_PSIZE_0			(0x1UL << DMA_CCR_PSIZE_Pos)
/** @brief Register or selector value represented by `DMA_CCR_PSIZE_1` @def DMA_CCR_PSIZE_1 */
#define DMA_CCR_PSIZE_1			(0x2UL << DMA_CCR_PSIZE_Pos)

/** @brief Bit position of the `DMA_CCR_MSIZE` field @def DMA_CCR_MSIZE_Pos */
#define DMA_CCR_MSIZE_Pos		((reg_bit_pos_t) 10U)
/** @brief Width of the `DMA_CCR_MSIZE` field @def DMA_CCR_MSIZE_Width */
#define DMA_CCR_MSIZE_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `DMA_CCR_MSIZE` field @def DMA_CCR_MSIZE_Msk */
#define DMA_CCR_MSIZE_Msk		REG_FIELD_MASK(DMA_CCR_MSIZE_Pos, DMA_CCR_MSIZE_Width)
/** @brief MSIZE[1:0] bits (Memory size) @def DMA_CCR_MSIZE */
#define DMA_CCR_MSIZE			DMA_CCR_MSIZE_Msk
/** @brief Register or selector value represented by `DMA_CCR_MSIZE_0` @def DMA_CCR_MSIZE_0 */
#define DMA_CCR_MSIZE_0			(0x1UL << DMA_CCR_MSIZE_Pos)
/** @brief Register or selector value represented by `DMA_CCR_MSIZE_1` @def DMA_CCR_MSIZE_1 */
#define DMA_CCR_MSIZE_1			(0x2UL << DMA_CCR_MSIZE_Pos)

/** @brief Bit position of the `DMA_CCR_PL` field @def DMA_CCR_PL_Pos */
#define DMA_CCR_PL_Pos			((reg_bit_pos_t) 12U)
/** @brief Width of the `DMA_CCR_PL` field @def DMA_CCR_PL_Width */
#define DMA_CCR_PL_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `DMA_CCR_PL` field @def DMA_CCR_PL_Msk */
#define DMA_CCR_PL_Msk			REG_FIELD_MASK(DMA_CCR_PL_Pos, DMA_CCR_PL_Width)
/** @brief PL[1:0] bits(Channel Priority level) @def DMA_CCR_PL */
#define DMA_CCR_PL				DMA_CCR_PL_Msk
/** @brief Register or selector value represented by `DMA_CCR_PL_0` @def DMA_CCR_PL_0 */
#define DMA_CCR_PL_0			(0x1UL << DMA_CCR_PL_Pos)
/** @brief Register or selector value represented by `DMA_CCR_PL_1` @def DMA_CCR_PL_1 */
#define DMA_CCR_PL_1			(0x2UL << DMA_CCR_PL_Pos)

/** @brief Bit position of the `DMA_CCR_MEM2MEM` field @def DMA_CCR_MEM2MEM_Pos */
#define DMA_CCR_MEM2MEM_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `DMA_CCR_MEM2MEM` field @def DMA_CCR_MEM2MEM_Msk */
#define DMA_CCR_MEM2MEM_Msk		REG_BIT_MASK(DMA_CCR_MEM2MEM_Pos)
/** @brief Memory to memory mode @def DMA_CCR_MEM2MEM */
#define DMA_CCR_MEM2MEM			DMA_CCR_MEM2MEM_Msk

// ---------------------------------- DMA_CNDTR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `DMA_CNDTR_NDT` field @def DMA_CNDTR_NDT_Pos */
#define DMA_CNDTR_NDT_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `DMA_CNDTR_NDT` field @def DMA_CNDTR_NDT_Width */
#define DMA_CNDTR_NDT_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `DMA_CNDTR_NDT` field @def DMA_CNDTR_NDT_Msk */
#define DMA_CNDTR_NDT_Msk		REG_FIELD_MASK(DMA_CNDTR_NDT_Pos, DMA_CNDTR_NDT_Width)
/** @brief Number of data to Transfer @def DMA_CNDTR_NDT */
#define DMA_CNDTR_NDT			DMA_CNDTR_NDT_Msk

// ---------------------------------- DMA_CPAR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `DMA_CPAR_PA` field @def DMA_CPAR_PA_Pos */
#define DMA_CPAR_PA_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `DMA_CPAR_PA` field @def DMA_CPAR_PA_Width */
#define DMA_CPAR_PA_Width		((reg_field_width_t) 32U)
/** @brief Register-positioned mask for the `DMA_CPAR_PA` field @def DMA_CPAR_PA_Msk */
#define DMA_CPAR_PA_Msk			((reg) 0xFFFFFFFFUL)
/** @brief Peripheral Address @def DMA_CPAR_PA */
#define DMA_CPAR_PA				DMA_CPAR_PA_Msk

// ---------------------------------- DMA_CMAR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `DMA_CMAR_MA` field @def DMA_CMAR_MA_Pos */
#define DMA_CMAR_MA_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `DMA_CMAR_MA` field @def DMA_CMAR_MA_Width */
#define DMA_CMAR_MA_Width		((reg_field_width_t) 32U)
/** @brief Register-positioned mask for the `DMA_CMAR_MA` field @def DMA_CMAR_MA_Msk */
#define DMA_CMAR_MA_Msk			((reg) 0xFFFFFFFFUL)
/** @brief Memory Address @def DMA_CMAR_MA */
#define DMA_CMAR_MA				DMA_CMAR_MA_Msk

// ==================================================================================================== //
//									Real-Time Clock (RTC) Register Defines								//
// ==================================================================================================== //

// ----------------------------------- RTC_CRH Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `RTC_CRH_SECIE` field @def RTC_CRH_SECIE_Pos */
#define RTC_CRH_SECIE_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `RTC_CRH_SECIE` field @def RTC_CRH_SECIE_Msk */
#define RTC_CRH_SECIE_Msk		REG_BIT_MASK(RTC_CRH_SECIE_Pos)
/** @brief Second Interrupt Enable @def RTC_CRH_SECIE */
#define RTC_CRH_SECIE			RTC_CRH_SECIE_Msk
/** @brief Bit position of the `RTC_CRH_ALRIE` field @def RTC_CRH_ALRIE_Pos */
#define RTC_CRH_ALRIE_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `RTC_CRH_ALRIE` field @def RTC_CRH_ALRIE_Msk */
#define RTC_CRH_ALRIE_Msk		REG_BIT_MASK(RTC_CRH_ALRIE_Pos)
/** @brief Alarm Interrupt Enable @def RTC_CRH_ALRIE */
#define RTC_CRH_ALRIE			RTC_CRH_ALRIE_Msk
/** @brief Bit position of the `RTC_CRH_OWIE` field @def RTC_CRH_OWIE_Pos */
#define RTC_CRH_OWIE_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `RTC_CRH_OWIE` field @def RTC_CRH_OWIE_Msk */
#define RTC_CRH_OWIE_Msk		REG_BIT_MASK(RTC_CRH_OWIE_Pos)
/** @brief OverfloW Interrupt Enable @def RTC_CRH_OWIE */
#define RTC_CRH_OWIE			RTC_CRH_OWIE_Msk

// ----------------------------------- RTC_CRL Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `RTC_CRL_SECF` field @def RTC_CRL_SECF_Pos */
#define RTC_CRL_SECF_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `RTC_CRL_SECF` field @def RTC_CRL_SECF_Msk */
#define RTC_CRL_SECF_Msk		REG_BIT_MASK(RTC_CRL_SECF_Pos)
/** @brief Second Flag @def RTC_CRL_SECF */
#define RTC_CRL_SECF			RTC_CRL_SECF_Msk
/** @brief Bit position of the `RTC_CRL_ALRF` field @def RTC_CRL_ALRF_Pos */
#define RTC_CRL_ALRF_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `RTC_CRL_ALRF` field @def RTC_CRL_ALRF_Msk */
#define RTC_CRL_ALRF_Msk		REG_BIT_MASK(RTC_CRL_ALRF_Pos)
/** @brief Alarm Flag @def RTC_CRL_ALRF */
#define RTC_CRL_ALRF			RTC_CRL_ALRF_Msk
/** @brief Bit position of the `RTC_CRL_OWF` field @def RTC_CRL_OWF_Pos */
#define RTC_CRL_OWF_Pos			((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `RTC_CRL_OWF` field @def RTC_CRL_OWF_Msk */
#define RTC_CRL_OWF_Msk			REG_BIT_MASK(RTC_CRL_OWF_Pos)
/** @brief OverfloW Flag @def RTC_CRL_OWF */
#define RTC_CRL_OWF				RTC_CRL_OWF_Msk
/** @brief Bit position of the `RTC_CRL_RSF` field @def RTC_CRL_RSF_Pos */
#define RTC_CRL_RSF_Pos			((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `RTC_CRL_RSF` field @def RTC_CRL_RSF_Msk */
#define RTC_CRL_RSF_Msk			REG_BIT_MASK(RTC_CRL_RSF_Pos)
/** @brief Registers Synchronized Flag @def RTC_CRL_RSF */
#define RTC_CRL_RSF				RTC_CRL_RSF_Msk
/** @brief Bit position of the `RTC_CRL_CNF` field @def RTC_CRL_CNF_Pos */
#define RTC_CRL_CNF_Pos			((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `RTC_CRL_CNF` field @def RTC_CRL_CNF_Msk */
#define RTC_CRL_CNF_Msk			REG_BIT_MASK(RTC_CRL_CNF_Pos)
/** @brief Configuration Flag @def RTC_CRL_CNF */
#define RTC_CRL_CNF				RTC_CRL_CNF_Msk
/** @brief Bit position of the `RTC_CRL_RTOFF` field @def RTC_CRL_RTOFF_Pos */
#define RTC_CRL_RTOFF_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `RTC_CRL_RTOFF` field @def RTC_CRL_RTOFF_Msk */
#define RTC_CRL_RTOFF_Msk		REG_BIT_MASK(RTC_CRL_RTOFF_Pos)
/** @brief RTC operation OFF @def RTC_CRL_RTOFF */
#define RTC_CRL_RTOFF			RTC_CRL_RTOFF_Msk

// ---------------------------------- RTC_PRLH Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `RTC_PRLH_PRL` field @def RTC_PRLH_PRL_Pos */
#define RTC_PRLH_PRL_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `RTC_PRLH_PRL` field @def RTC_PRLH_PRL_Width */
#define RTC_PRLH_PRL_Width		((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `RTC_PRLH_PRL` field @def RTC_PRLH_PRL_Msk */
#define RTC_PRLH_PRL_Msk		REG_FIELD_MASK(RTC_PRLH_PRL_Pos, RTC_PRLH_PRL_Width)
/** @brief RTC Prescaler Reload Value High @def RTC_PRLH_PRL */
#define RTC_PRLH_PRL			RTC_PRLH_PRL_Msk

// ---------------------------------- RTC_PRLL Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `RTC_PRLL_PRL` field @def RTC_PRLL_PRL_Pos */
#define RTC_PRLL_PRL_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `RTC_PRLL_PRL` field @def RTC_PRLL_PRL_Width */
#define RTC_PRLL_PRL_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `RTC_PRLL_PRL` field @def RTC_PRLL_PRL_Msk */
#define RTC_PRLL_PRL_Msk		REG_FIELD_MASK(RTC_PRLL_PRL_Pos, RTC_PRLL_PRL_Width)
/** @brief RTC Prescaler Reload Value Low @def RTC_PRLL_PRL */
#define RTC_PRLL_PRL			RTC_PRLL_PRL_Msk

// ---------------------------------- RTC_DIVH Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `RTC_DIVH_RTC_DIV` field @def RTC_DIVH_RTC_DIV_Pos */
#define RTC_DIVH_RTC_DIV_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `RTC_DIVH_RTC_DIV` field @def RTC_DIVH_RTC_DIV_Width */
#define RTC_DIVH_RTC_DIV_Width		((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `RTC_DIVH_RTC_DIV` field @def RTC_DIVH_RTC_DIV_Msk */
#define RTC_DIVH_RTC_DIV_Msk		REG_FIELD_MASK(RTC_DIVH_RTC_DIV_Pos, RTC_DIVH_RTC_DIV_Width)
/** @brief RTC Clock Divider High @def RTC_DIVH_RTC_DIV */
#define RTC_DIVH_RTC_DIV			RTC_DIVH_RTC_DIV_Msk

// ---------------------------------- RTC_DIVL Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `RTC_DIVL_RTC_DIV` field @def RTC_DIVL_RTC_DIV_Pos */
#define RTC_DIVL_RTC_DIV_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `RTC_DIVL_RTC_DIV` field @def RTC_DIVL_RTC_DIV_Width */
#define RTC_DIVL_RTC_DIV_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `RTC_DIVL_RTC_DIV` field @def RTC_DIVL_RTC_DIV_Msk */
#define RTC_DIVL_RTC_DIV_Msk		REG_FIELD_MASK(RTC_DIVL_RTC_DIV_Pos, RTC_DIVL_RTC_DIV_Width)
/** @brief RTC Clock Divider Low @def RTC_DIVL_RTC_DIV */
#define RTC_DIVL_RTC_DIV			RTC_DIVL_RTC_DIV_Msk

// ---------------------------------- RTC_CNTH Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `RTC_CNTH_RTC_CNT` field @def RTC_CNTH_RTC_CNT_Pos */
#define RTC_CNTH_RTC_CNT_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `RTC_CNTH_RTC_CNT` field @def RTC_CNTH_RTC_CNT_Width */
#define RTC_CNTH_RTC_CNT_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `RTC_CNTH_RTC_CNT` field @def RTC_CNTH_RTC_CNT_Msk */
#define RTC_CNTH_RTC_CNT_Msk		REG_FIELD_MASK(RTC_CNTH_RTC_CNT_Pos, RTC_CNTH_RTC_CNT_Width)
/** @brief RTC Counter High @def RTC_CNTH_RTC_CNT */
#define RTC_CNTH_RTC_CNT			RTC_CNTH_RTC_CNT_Msk

// ---------------------------------- RTC_CNTL Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `RTC_CNTL_RTC_CNT` field @def RTC_CNTL_RTC_CNT_Pos */
#define RTC_CNTL_RTC_CNT_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `RTC_CNTL_RTC_CNT` field @def RTC_CNTL_RTC_CNT_Width */
#define RTC_CNTL_RTC_CNT_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `RTC_CNTL_RTC_CNT` field @def RTC_CNTL_RTC_CNT_Msk */
#define RTC_CNTL_RTC_CNT_Msk		REG_FIELD_MASK(RTC_CNTL_RTC_CNT_Pos, RTC_CNTL_RTC_CNT_Width)
/** @brief RTC Counter Low @def RTC_CNTL_RTC_CNT */
#define RTC_CNTL_RTC_CNT			RTC_CNTL_RTC_CNT_Msk

// ---------------------------------- RTC_ALRH Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `RTC_ALRH_RTC_ALR` field @def RTC_ALRH_RTC_ALR_Pos */
#define RTC_ALRH_RTC_ALR_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `RTC_ALRH_RTC_ALR` field @def RTC_ALRH_RTC_ALR_Width */
#define RTC_ALRH_RTC_ALR_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `RTC_ALRH_RTC_ALR` field @def RTC_ALRH_RTC_ALR_Msk */
#define RTC_ALRH_RTC_ALR_Msk		REG_FIELD_MASK(RTC_ALRH_RTC_ALR_Pos, RTC_ALRH_RTC_ALR_Width)
/** @brief RTC Alarm High @def RTC_ALRH_RTC_ALR */
#define RTC_ALRH_RTC_ALR			RTC_ALRH_RTC_ALR_Msk

// ---------------------------------- RTC_ALRL Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `RTC_ALRL_RTC_ALR` field @def RTC_ALRL_RTC_ALR_Pos */
#define RTC_ALRL_RTC_ALR_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `RTC_ALRL_RTC_ALR` field @def RTC_ALRL_RTC_ALR_Width */
#define RTC_ALRL_RTC_ALR_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `RTC_ALRL_RTC_ALR` field @def RTC_ALRL_RTC_ALR_Msk */
#define RTC_ALRL_RTC_ALR_Msk		REG_FIELD_MASK(RTC_ALRL_RTC_ALR_Pos, RTC_ALRL_RTC_ALR_Width)
/** @brief RTC Alarm Low @def RTC_ALRL_RTC_ALR */
#define RTC_ALRL_RTC_ALR			RTC_ALRL_RTC_ALR_Msk

// ==================================================================================================== //
//								Independent Watchdog (IWDG) Register Defines							//
// ==================================================================================================== //

// ----------------------------------- IWDG_KR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `IWDG_KR_KEY` field @def IWDG_KR_KEY_Pos */
#define IWDG_KR_KEY_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `IWDG_KR_KEY` field @def IWDG_KR_KEY_Width */
#define IWDG_KR_KEY_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `IWDG_KR_KEY` field @def IWDG_KR_KEY_Msk */
#define IWDG_KR_KEY_Msk			REG_FIELD_MASK(IWDG_KR_KEY_Pos, IWDG_KR_KEY_Width)
/** @brief Key value (write only, read 0000h) @def IWDG_KR_KEY */
#define IWDG_KR_KEY				IWDG_KR_KEY_Msk

// ----------------------------------- IWDG_PR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `IWDG_PR_PR` field @def IWDG_PR_PR_Pos */
#define IWDG_PR_PR_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `IWDG_PR_PR` field @def IWDG_PR_PR_Width */
#define IWDG_PR_PR_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `IWDG_PR_PR` field @def IWDG_PR_PR_Msk */
#define IWDG_PR_PR_Msk			REG_FIELD_MASK(IWDG_PR_PR_Pos, IWDG_PR_PR_Width)
/** @brief PR[2:0] (Prescaler divider) @def IWDG_PR_PR */
#define IWDG_PR_PR				IWDG_PR_PR_Msk
/** @brief Register or selector value represented by `IWDG_PR_PR_0` @def IWDG_PR_PR_0 */
#define IWDG_PR_PR_0			(0x1UL << IWDG_PR_PR_Pos)
/** @brief Register or selector value represented by `IWDG_PR_PR_1` @def IWDG_PR_PR_1 */
#define IWDG_PR_PR_1			(0x2UL << IWDG_PR_PR_Pos)
/** @brief Register or selector value represented by `IWDG_PR_PR_2` @def IWDG_PR_PR_2 */
#define IWDG_PR_PR_2			(0x4UL << IWDG_PR_PR_Pos)

// ---------------------------------- IWDG_RLR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `IWDG_RLR_RL` field @def IWDG_RLR_RL_Pos */
#define IWDG_RLR_RL_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `IWDG_RLR_RL` field @def IWDG_RLR_RL_Width */
#define IWDG_RLR_RL_Width		((reg_field_width_t) 12U)
/** @brief Register-positioned mask for the `IWDG_RLR_RL` field @def IWDG_RLR_RL_Msk */
#define IWDG_RLR_RL_Msk			REG_FIELD_MASK(IWDG_RLR_RL_Pos, IWDG_RLR_RL_Width)
/** @brief Watchdog counter reload value @def IWDG_RLR_RL */
#define IWDG_RLR_RL				IWDG_RLR_RL_Msk

// ----------------------------------- IWDG_SR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `IWDG_SR_PVU` field @def IWDG_SR_PVU_Pos */
#define IWDG_SR_PVU_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `IWDG_SR_PVU` field @def IWDG_SR_PVU_Msk */
#define IWDG_SR_PVU_Msk		REG_BIT_MASK(IWDG_SR_PVU_Pos)
/** @brief Watchdog prescaler value update @def IWDG_SR_PVU */
#define IWDG_SR_PVU			IWDG_SR_PVU_Msk
/** @brief Bit position of the `IWDG_SR_RVU` field @def IWDG_SR_RVU_Pos */
#define IWDG_SR_RVU_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `IWDG_SR_RVU` field @def IWDG_SR_RVU_Msk */
#define IWDG_SR_RVU_Msk		REG_BIT_MASK(IWDG_SR_RVU_Pos)
/** @brief Watchdog counter reload value update @def IWDG_SR_RVU */
#define IWDG_SR_RVU			IWDG_SR_RVU_Msk

// ==================================================================================================== //
//									Window Watchdog (WWDG) Register Defines								//
// ==================================================================================================== //

// ----------------------------------- WWDG_CR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `WWDG_CR_T` field @def WWDG_CR_T_Pos */
#define WWDG_CR_T_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `WWDG_CR_T` field @def WWDG_CR_T_Width */
#define WWDG_CR_T_Width		((reg_field_width_t) 7U)
/** @brief Register-positioned mask for the `WWDG_CR_T` field @def WWDG_CR_T_Msk */
#define WWDG_CR_T_Msk		REG_FIELD_MASK(WWDG_CR_T_Pos, WWDG_CR_T_Width)
/** @brief T[6:0] bits (7-Bit counter (MSB to LSB)) @def WWDG_CR_T */
#define WWDG_CR_T			WWDG_CR_T_Msk
/** @brief Register or selector value represented by `WWDG_CR_T_0` @def WWDG_CR_T_0 */
#define WWDG_CR_T_0			(0x01UL << WWDG_CR_T_Pos)
/** @brief Register or selector value represented by `WWDG_CR_T_1` @def WWDG_CR_T_1 */
#define WWDG_CR_T_1			(0x02UL << WWDG_CR_T_Pos)
/** @brief Register or selector value represented by `WWDG_CR_T_2` @def WWDG_CR_T_2 */
#define WWDG_CR_T_2			(0x04UL << WWDG_CR_T_Pos)
/** @brief Register or selector value represented by `WWDG_CR_T_3` @def WWDG_CR_T_3 */
#define WWDG_CR_T_3			(0x08UL << WWDG_CR_T_Pos)
/** @brief Register or selector value represented by `WWDG_CR_T_4` @def WWDG_CR_T_4 */
#define WWDG_CR_T_4			(0x10UL << WWDG_CR_T_Pos)
/** @brief Register or selector value represented by `WWDG_CR_T_5` @def WWDG_CR_T_5 */
#define WWDG_CR_T_5			(0x20UL << WWDG_CR_T_Pos)
/** @brief Register or selector value represented by `WWDG_CR_T_6` @def WWDG_CR_T_6 */
#define WWDG_CR_T_6			(0x40UL << WWDG_CR_T_Pos)

// ----------------------------------- Legacy Compatibility Defines ----------------------------------- //
/** @brief Register or selector value represented by `WWDG_CR_T0` @def WWDG_CR_T0 */
#define WWDG_CR_T0				WWDG_CR_T_0
/** @brief Register or selector value represented by `WWDG_CR_T1` @def WWDG_CR_T1 */
#define WWDG_CR_T1				WWDG_CR_T_1
/** @brief Register or selector value represented by `WWDG_CR_T2` @def WWDG_CR_T2 */
#define WWDG_CR_T2				WWDG_CR_T_2
/** @brief Register or selector value represented by `WWDG_CR_T3` @def WWDG_CR_T3 */
#define WWDG_CR_T3				WWDG_CR_T_3
/** @brief Register or selector value represented by `WWDG_CR_T4` @def WWDG_CR_T4 */
#define WWDG_CR_T4				WWDG_CR_T_4
/** @brief Register or selector value represented by `WWDG_CR_T5` @def WWDG_CR_T5 */
#define WWDG_CR_T5				WWDG_CR_T_5
/** @brief Register or selector value represented by `WWDG_CR_T6` @def WWDG_CR_T6 */
#define WWDG_CR_T6				WWDG_CR_T_6

/** @brief Bit position of the `WWDG_CR_WDGA` field @def WWDG_CR_WDGA_Pos */
#define WWDG_CR_WDGA_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `WWDG_CR_WDGA` field @def WWDG_CR_WDGA_Msk */
#define WWDG_CR_WDGA_Msk		REG_BIT_MASK(WWDG_CR_WDGA_Pos)
/** @brief Activation bit @def WWDG_CR_WDGA */
#define WWDG_CR_WDGA			WWDG_CR_WDGA_Msk

// ---------------------------------- WWDG_CFR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `WWDG_CFR_W` field @def WWDG_CFR_W_Pos */
#define WWDG_CFR_W_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `WWDG_CFR_W` field @def WWDG_CFR_W_Width */
#define WWDG_CFR_W_Width		((reg_field_width_t) 7U)
/** @brief Register-positioned mask for the `WWDG_CFR_W` field @def WWDG_CFR_W_Msk */
#define WWDG_CFR_W_Msk			REG_FIELD_MASK(WWDG_CFR_W_Pos, WWDG_CFR_W_Width)
/** @brief W[6:0] bits (7-bit window value) @def WWDG_CFR_W */
#define WWDG_CFR_W				WWDG_CFR_W_Msk
/** @brief Register or selector value represented by `WWDG_CFR_W_0` @def WWDG_CFR_W_0 */
#define WWDG_CFR_W_0			(0x01UL << WWDG_CFR_W_Pos)
/** @brief Register or selector value represented by `WWDG_CFR_W_1` @def WWDG_CFR_W_1 */
#define WWDG_CFR_W_1			(0x02UL << WWDG_CFR_W_Pos)
/** @brief Register or selector value represented by `WWDG_CFR_W_2` @def WWDG_CFR_W_2 */
#define WWDG_CFR_W_2			(0x04UL << WWDG_CFR_W_Pos)
/** @brief Register or selector value represented by `WWDG_CFR_W_3` @def WWDG_CFR_W_3 */
#define WWDG_CFR_W_3			(0x08UL << WWDG_CFR_W_Pos)
/** @brief Register or selector value represented by `WWDG_CFR_W_4` @def WWDG_CFR_W_4 */
#define WWDG_CFR_W_4			(0x10UL << WWDG_CFR_W_Pos)
/** @brief Register or selector value represented by `WWDG_CFR_W_5` @def WWDG_CFR_W_5 */
#define WWDG_CFR_W_5			(0x20UL << WWDG_CFR_W_Pos)
/** @brief Register or selector value represented by `WWDG_CFR_W_6` @def WWDG_CFR_W_6 */
#define WWDG_CFR_W_6			(0x40UL << WWDG_CFR_W_Pos)

// ----------------------------------- Legacy Compatibility Defines ----------------------------------- //
/** @brief Register or selector value represented by `WWDG_CFR_W0` @def WWDG_CFR_W0 */
#define WWDG_CFR_W0					WWDG_CFR_W_0
/** @brief Register or selector value represented by `WWDG_CFR_W1` @def WWDG_CFR_W1 */
#define WWDG_CFR_W1					WWDG_CFR_W_1
/** @brief Register or selector value represented by `WWDG_CFR_W2` @def WWDG_CFR_W2 */
#define WWDG_CFR_W2					WWDG_CFR_W_2
/** @brief Register or selector value represented by `WWDG_CFR_W3` @def WWDG_CFR_W3 */
#define WWDG_CFR_W3					WWDG_CFR_W_3
/** @brief Register or selector value represented by `WWDG_CFR_W4` @def WWDG_CFR_W4 */
#define WWDG_CFR_W4					WWDG_CFR_W_4
/** @brief Register or selector value represented by `WWDG_CFR_W5` @def WWDG_CFR_W5 */
#define WWDG_CFR_W5					WWDG_CFR_W_5
/** @brief Register or selector value represented by `WWDG_CFR_W6` @def WWDG_CFR_W6 */
#define WWDG_CFR_W6					WWDG_CFR_W_6

/** @brief Bit position of the `WWDG_CFR_WDGTB` field @def WWDG_CFR_WDGTB_Pos */
#define WWDG_CFR_WDGTB_Pos			((reg_bit_pos_t) 7U)
/** @brief Width of the `WWDG_CFR_WDGTB` field @def WWDG_CFR_WDGTB_Width */
#define WWDG_CFR_WDGTB_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `WWDG_CFR_WDGTB` field @def WWDG_CFR_WDGTB_Msk */
#define WWDG_CFR_WDGTB_Msk			REG_FIELD_MASK(WWDG_CFR_WDGTB_Pos, WWDG_CFR_WDGTB_Width)
/** @brief WDGTB[1:0] bits (Timer Base) @def WWDG_CFR_WDGTB */
#define WWDG_CFR_WDGTB				WWDG_CFR_WDGTB_Msk
/** @brief Register or selector value represented by `WWDG_CFR_WDGTB_0` @def WWDG_CFR_WDGTB_0 */
#define WWDG_CFR_WDGTB_0			(0x1UL << WWDG_CFR_WDGTB_Pos)
/** @brief Register or selector value represented by `WWDG_CFR_WDGTB_1` @def WWDG_CFR_WDGTB_1 */
#define WWDG_CFR_WDGTB_1			(0x2UL << WWDG_CFR_WDGTB_Pos)

// ----------------------------------- Legacy Compatibility Defines ----------------------------------- //
/** @brief Register or selector value represented by `WWDG_CFR_WDGTB0` @def WWDG_CFR_WDGTB0 */
#define WWDG_CFR_WDGTB0			WWDG_CFR_WDGTB_0
/** @brief Register or selector value represented by `WWDG_CFR_WDGTB1` @def WWDG_CFR_WDGTB1 */
#define WWDG_CFR_WDGTB1			WWDG_CFR_WDGTB_1

/** @brief Bit position of the `WWDG_CFR_EWI` field @def WWDG_CFR_EWI_Pos */
#define WWDG_CFR_EWI_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `WWDG_CFR_EWI` field @def WWDG_CFR_EWI_Msk */
#define WWDG_CFR_EWI_Msk		REG_BIT_MASK(WWDG_CFR_EWI_Pos)
/** @brief Early Wakeup Interrupt @def WWDG_CFR_EWI */
#define WWDG_CFR_EWI			WWDG_CFR_EWI_Msk

// ----------------------------------- WWDG_SR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `WWDG_SR_EWIF` field @def WWDG_SR_EWIF_Pos */
#define WWDG_SR_EWIF_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `WWDG_SR_EWIF` field @def WWDG_SR_EWIF_Msk */
#define WWDG_SR_EWIF_Msk		REG_BIT_MASK(WWDG_SR_EWIF_Pos)
/** @brief Early Wakeup Interrupt Flag @def WWDG_SR_EWIF */
#define WWDG_SR_EWIF			WWDG_SR_EWIF_Msk

// ==================================================================================================== //
//									USB Full-Speed Device Register Defines								//
// ==================================================================================================== //

// ------------------------------ USB Endpoint Register Address Defines ------------------------------- //
/** @brief Endpoint 0 register address @def USB_EP0R */
#define USB_EP0R		USB_BASE
/** @brief Endpoint 1 register address @def USB_EP1R */
#define USB_EP1R		(USB_BASE + 0x00000004)
/** @brief Endpoint 2 register address @def USB_EP2R */
#define USB_EP2R		(USB_BASE + 0x00000008)
/** @brief Endpoint 3 register address @def USB_EP3R */
#define USB_EP3R		(USB_BASE + 0x0000000C)
/** @brief Endpoint 4 register address @def USB_EP4R */
#define USB_EP4R		(USB_BASE + 0x00000010)
/** @brief Endpoint 5 register address @def USB_EP5R */
#define USB_EP5R		(USB_BASE + 0x00000014)
/** @brief Endpoint 6 register address @def USB_EP6R */
#define USB_EP6R		(USB_BASE + 0x00000018)
/** @brief Endpoint 7 register address @def USB_EP7R */
#define USB_EP7R		(USB_BASE + 0x0000001C)

// -------------------------------- USB Endpoint Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_EPADDR_FIELD` field @def USB_EPADDR_FIELD_Pos */
#define USB_EPADDR_FIELD_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_EPADDR_FIELD` field @def USB_EPADDR_FIELD_Width */
#define USB_EPADDR_FIELD_Width		((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `USB_EPADDR_FIELD` field @def USB_EPADDR_FIELD_Msk */
#define USB_EPADDR_FIELD_Msk		REG_FIELD_MASK(USB_EPADDR_FIELD_Pos, USB_EPADDR_FIELD_Width)
/** @brief EndPoint ADDRess FIELD @def USB_EPADDR_FIELD */
#define USB_EPADDR_FIELD			USB_EPADDR_FIELD_Msk
/** @brief Bit position of the `USB_EPTX_STAT` field @def USB_EPTX_STAT_Pos */
#define USB_EPTX_STAT_Pos			((reg_bit_pos_t) 4U)
/** @brief Width of the `USB_EPTX_STAT` field @def USB_EPTX_STAT_Width */
#define USB_EPTX_STAT_Width			((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EPTX_STAT` field @def USB_EPTX_STAT_Msk */
#define USB_EPTX_STAT_Msk			REG_FIELD_MASK(USB_EPTX_STAT_Pos, USB_EPTX_STAT_Width)
/** @brief EndPoint TX STATus bit field @def USB_EPTX_STAT */
#define USB_EPTX_STAT				USB_EPTX_STAT_Msk
/** @brief Bit position of the `USB_EP_DTOG_TX` field @def USB_EP_DTOG_TX_Pos */
#define USB_EP_DTOG_TX_Pos			((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USB_EP_DTOG_TX` field @def USB_EP_DTOG_TX_Msk */
#define USB_EP_DTOG_TX_Msk			REG_BIT_MASK(USB_EP_DTOG_TX_Pos)
/** @brief EndPoint Data TOGGLE TX @def USB_EP_DTOG_TX */
#define USB_EP_DTOG_TX				USB_EP_DTOG_TX_Msk
/** @brief Bit position of the `USB_EP_CTR_TX` field @def USB_EP_CTR_TX_Pos */
#define USB_EP_CTR_TX_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USB_EP_CTR_TX` field @def USB_EP_CTR_TX_Msk */
#define USB_EP_CTR_TX_Msk			REG_BIT_MASK(USB_EP_CTR_TX_Pos)
/** @brief EndPoint Correct TRansfer TX @def USB_EP_CTR_TX */
#define USB_EP_CTR_TX				USB_EP_CTR_TX_Msk
/** @brief Bit position of the `USB_EP_KIND` field @def USB_EP_KIND_Pos */
#define USB_EP_KIND_Pos				((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USB_EP_KIND` field @def USB_EP_KIND_Msk */
#define USB_EP_KIND_Msk				REG_BIT_MASK(USB_EP_KIND_Pos)
/** @brief EndPoint KIND @def USB_EP_KIND */
#define USB_EP_KIND					USB_EP_KIND_Msk
/** @brief Bit position of the `USB_EP_T_FIELD` field @def USB_EP_T_FIELD_Pos */
#define USB_EP_T_FIELD_Pos			((reg_bit_pos_t) 9U)
/** @brief Width of the `USB_EP_T_FIELD` field @def USB_EP_T_FIELD_Width */
#define USB_EP_T_FIELD_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP_T_FIELD` field @def USB_EP_T_FIELD_Msk */
#define USB_EP_T_FIELD_Msk			REG_FIELD_MASK(USB_EP_T_FIELD_Pos, USB_EP_T_FIELD_Width)
/** @brief EndPoint TYPE @def USB_EP_T_FIELD */
#define USB_EP_T_FIELD				USB_EP_T_FIELD_Msk
/** @brief Bit position of the `USB_EP_SETUP` field @def USB_EP_SETUP_Pos */
#define USB_EP_SETUP_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USB_EP_SETUP` field @def USB_EP_SETUP_Msk */
#define USB_EP_SETUP_Msk			REG_BIT_MASK(USB_EP_SETUP_Pos)
/** @brief EndPoint SETUP @def USB_EP_SETUP */
#define USB_EP_SETUP				USB_EP_SETUP_Msk
/** @brief Bit position of the `USB_EPRX_STAT` field @def USB_EPRX_STAT_Pos */
#define USB_EPRX_STAT_Pos			((reg_bit_pos_t) 12U)
/** @brief Width of the `USB_EPRX_STAT` field @def USB_EPRX_STAT_Width */
#define USB_EPRX_STAT_Width			((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EPRX_STAT` field @def USB_EPRX_STAT_Msk */
#define USB_EPRX_STAT_Msk			REG_FIELD_MASK(USB_EPRX_STAT_Pos, USB_EPRX_STAT_Width)
/** @brief EndPoint RX STATus bit field @def USB_EPRX_STAT */
#define USB_EPRX_STAT				USB_EPRX_STAT_Msk
/** @brief Bit position of the `USB_EP_DTOG_RX` field @def USB_EP_DTOG_RX_Pos */
#define USB_EP_DTOG_RX_Pos			((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USB_EP_DTOG_RX` field @def USB_EP_DTOG_RX_Msk */
#define USB_EP_DTOG_RX_Msk			REG_BIT_MASK(USB_EP_DTOG_RX_Pos)
/** @brief EndPoint Data TOGGLE RX @def USB_EP_DTOG_RX */
#define USB_EP_DTOG_RX				USB_EP_DTOG_RX_Msk
/** @brief Bit position of the `USB_EP_CTR_RX` field @def USB_EP_CTR_RX_Pos */
#define USB_EP_CTR_RX_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_EP_CTR_RX` field @def USB_EP_CTR_RX_Msk */
#define USB_EP_CTR_RX_Msk			REG_BIT_MASK(USB_EP_CTR_RX_Pos)
/** @brief EndPoint Correct TRansfer RX @def USB_EP_CTR_RX */
#define USB_EP_CTR_RX				USB_EP_CTR_RX_Msk

// -------------------------------- USB Endpoint Register Mask Defines -------------------------------- //
/** @brief Register or selector value represented by `USB_EPREG_MASK` @def USB_EPREG_MASK */
#define USB_EPREG_MASK				(USB_EP_CTR_RX|USB_EP_SETUP|USB_EP_T_FIELD|USB_EP_KIND|USB_EP_CTR_TX|USB_EPADDR_FIELD)
																			 /* EP_TYPE[1:0] EndPoint TYPE */
/** @brief Bit position of the `USB_EP_TYPE_MASK` field @def USB_EP_TYPE_MASK_Pos */
#define USB_EP_TYPE_MASK_Pos		((reg_bit_pos_t) 9U)
/** @brief Width of the `USB_EP_TYPE_MASK` field @def USB_EP_TYPE_MASK_Width */
#define USB_EP_TYPE_MASK_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP_TYPE_MASK` field @def USB_EP_TYPE_MASK_Msk */
#define USB_EP_TYPE_MASK_Msk		REG_FIELD_MASK(USB_EP_TYPE_MASK_Pos, USB_EP_TYPE_MASK_Width)
/** @brief EndPoint TYPE Mask @def USB_EP_TYPE_MASK */
#define USB_EP_TYPE_MASK			USB_EP_TYPE_MASK_Msk
/** @brief EndPoint BULK @def USB_EP_BULK */
#define USB_EP_BULK					0x00000000U
/** @brief EndPoint CONTROL @def USB_EP_CONTROL */
#define USB_EP_CONTROL				0x00000200U
/** @brief EndPoint ISOCHRONOUS @def USB_EP_ISOCHRONOUS */
#define USB_EP_ISOCHRONOUS			0x00000400U
/** @brief EndPoint INTERRUPT @def USB_EP_INTERRUPT */
#define USB_EP_INTERRUPT			0x00000600U
/** @brief Register or selector value represented by `USB_EP_T_MASK` @def USB_EP_T_MASK */
#define USB_EP_T_MASK				(~USB_EP_T_FIELD & USB_EPREG_MASK)

/** @brief EP_KIND EndPoint KIND @def USB_EPKIND_MASK */
#define USB_EPKIND_MASK				(~USB_EP_KIND & USB_EPREG_MASK)
																				 /* STAT_TX[1:0] STATus for TX transfer */
/** @brief EndPoint TX DISabled @def USB_EP_TX_DIS */
#define USB_EP_TX_DIS				0x00000000U
/** @brief EndPoint TX STALLed @def USB_EP_TX_STALL */
#define USB_EP_TX_STALL				0x00000010U
/** @brief EndPoint TX NAKed @def USB_EP_TX_NAK */
#define USB_EP_TX_NAK				0x00000020U
/** @brief EndPoint TX VALID @def USB_EP_TX_VALID */
#define USB_EP_TX_VALID				0x00000030U
/** @brief EndPoint TX Data TOGgle bit1 @def USB_EPTX_DTOG1 */
#define USB_EPTX_DTOG1				0x00000010U
/** @brief EndPoint TX Data TOGgle bit2 @def USB_EPTX_DTOG2 */
#define USB_EPTX_DTOG2				0x00000020U
/** @brief Register or selector value represented by `USB_EPTX_DTOGMASK` @def USB_EPTX_DTOGMASK */
#define USB_EPTX_DTOGMASK			(USB_EPTX_STAT|USB_EPREG_MASK)
																				 /* STAT_RX[1:0] STATus for RX transfer */
/** @brief EndPoint RX DISabled @def USB_EP_RX_DIS */
#define USB_EP_RX_DIS				0x00000000U
/** @brief EndPoint RX STALLed @def USB_EP_RX_STALL */
#define USB_EP_RX_STALL				0x00001000U
/** @brief EndPoint RX NAKed @def USB_EP_RX_NAK */
#define USB_EP_RX_NAK				0x00002000U
/** @brief EndPoint RX VALID @def USB_EP_RX_VALID */
#define USB_EP_RX_VALID				0x00003000U
/** @brief EndPoint RX Data TOGgle bit1 @def USB_EPRX_DTOG1 */
#define USB_EPRX_DTOG1				0x00001000U
/** @brief EndPoint RX Data TOGgle bit1 @def USB_EPRX_DTOG2 */
#define USB_EPRX_DTOG2				0x00002000U
/** @brief Register or selector value represented by `USB_EPRX_DTOGMASK` @def USB_EPRX_DTOGMASK */
#define USB_EPRX_DTOGMASK			(USB_EPRX_STAT|USB_EPREG_MASK)

// ---------------------------------- USB_EP0R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USB_EP0R_EA` field @def USB_EP0R_EA_Pos */
#define USB_EP0R_EA_Pos				((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_EP0R_EA` field @def USB_EP0R_EA_Width */
#define USB_EP0R_EA_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `USB_EP0R_EA` field @def USB_EP0R_EA_Msk */
#define USB_EP0R_EA_Msk				REG_FIELD_MASK(USB_EP0R_EA_Pos, USB_EP0R_EA_Width)
/** @brief Endpoint Address @def USB_EP0R_EA */
#define USB_EP0R_EA					USB_EP0R_EA_Msk

/** @brief Bit position of the `USB_EP0R_STAT_TX` field @def USB_EP0R_STAT_TX_Pos */
#define USB_EP0R_STAT_TX_Pos		((reg_bit_pos_t) 4U)
/** @brief Width of the `USB_EP0R_STAT_TX` field @def USB_EP0R_STAT_TX_Width */
#define USB_EP0R_STAT_TX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP0R_STAT_TX` field @def USB_EP0R_STAT_TX_Msk */
#define USB_EP0R_STAT_TX_Msk		REG_FIELD_MASK(USB_EP0R_STAT_TX_Pos, USB_EP0R_STAT_TX_Width)
/** @brief STAT_TX[1:0] bits (Status bits, for transmission transfers) @def USB_EP0R_STAT_TX */
#define USB_EP0R_STAT_TX			USB_EP0R_STAT_TX_Msk
/** @brief Register or selector value represented by `USB_EP0R_STAT_TX_0` @def USB_EP0R_STAT_TX_0 */
#define USB_EP0R_STAT_TX_0			(0x1UL << USB_EP0R_STAT_TX_Pos)
/** @brief Register or selector value represented by `USB_EP0R_STAT_TX_1` @def USB_EP0R_STAT_TX_1 */
#define USB_EP0R_STAT_TX_1			(0x2UL << USB_EP0R_STAT_TX_Pos)

/** @brief Bit position of the `USB_EP0R_DTOG_TX` field @def USB_EP0R_DTOG_TX_Pos */
#define USB_EP0R_DTOG_TX_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USB_EP0R_DTOG_TX` field @def USB_EP0R_DTOG_TX_Msk */
#define USB_EP0R_DTOG_TX_Msk		REG_BIT_MASK(USB_EP0R_DTOG_TX_Pos)
/** @brief Data Toggle, for transmission transfers @def USB_EP0R_DTOG_TX */
#define USB_EP0R_DTOG_TX			USB_EP0R_DTOG_TX_Msk
/** @brief Bit position of the `USB_EP0R_CTR_TX` field @def USB_EP0R_CTR_TX_Pos */
#define USB_EP0R_CTR_TX_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USB_EP0R_CTR_TX` field @def USB_EP0R_CTR_TX_Msk */
#define USB_EP0R_CTR_TX_Msk			REG_BIT_MASK(USB_EP0R_CTR_TX_Pos)
/** @brief Correct Transfer for transmission @def USB_EP0R_CTR_TX */
#define USB_EP0R_CTR_TX				USB_EP0R_CTR_TX_Msk
/** @brief Bit position of the `USB_EP0R_EP_KIND` field @def USB_EP0R_EP_KIND_Pos */
#define USB_EP0R_EP_KIND_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USB_EP0R_EP_KIND` field @def USB_EP0R_EP_KIND_Msk */
#define USB_EP0R_EP_KIND_Msk		REG_BIT_MASK(USB_EP0R_EP_KIND_Pos)
/** @brief Endpoint Kind @def USB_EP0R_EP_KIND */
#define USB_EP0R_EP_KIND			USB_EP0R_EP_KIND_Msk

/** @brief Bit position of the `USB_EP0R_EP_TYPE` field @def USB_EP0R_EP_TYPE_Pos */
#define USB_EP0R_EP_TYPE_Pos		((reg_bit_pos_t) 9U)
/** @brief Width of the `USB_EP0R_EP_TYPE` field @def USB_EP0R_EP_TYPE_Width */
#define USB_EP0R_EP_TYPE_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP0R_EP_TYPE` field @def USB_EP0R_EP_TYPE_Msk */
#define USB_EP0R_EP_TYPE_Msk		REG_FIELD_MASK(USB_EP0R_EP_TYPE_Pos, USB_EP0R_EP_TYPE_Width)
/** @brief EP_TYPE[1:0] bits (Endpoint type) @def USB_EP0R_EP_TYPE */
#define USB_EP0R_EP_TYPE			USB_EP0R_EP_TYPE_Msk
/** @brief Register or selector value represented by `USB_EP0R_EP_TYPE_0` @def USB_EP0R_EP_TYPE_0 */
#define USB_EP0R_EP_TYPE_0			(0x1UL << USB_EP0R_EP_TYPE_Pos)
/** @brief Register or selector value represented by `USB_EP0R_EP_TYPE_1` @def USB_EP0R_EP_TYPE_1 */
#define USB_EP0R_EP_TYPE_1			(0x2UL << USB_EP0R_EP_TYPE_Pos)

/** @brief Bit position of the `USB_EP0R_SETUP` field @def USB_EP0R_SETUP_Pos */
#define USB_EP0R_SETUP_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USB_EP0R_SETUP` field @def USB_EP0R_SETUP_Msk */
#define USB_EP0R_SETUP_Msk			REG_BIT_MASK(USB_EP0R_SETUP_Pos)
/** @brief Setup transaction completed @def USB_EP0R_SETUP */
#define USB_EP0R_SETUP				USB_EP0R_SETUP_Msk

/** @brief Bit position of the `USB_EP0R_STAT_RX` field @def USB_EP0R_STAT_RX_Pos */
#define USB_EP0R_STAT_RX_Pos		((reg_bit_pos_t) 12U)
/** @brief Width of the `USB_EP0R_STAT_RX` field @def USB_EP0R_STAT_RX_Width */
#define USB_EP0R_STAT_RX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP0R_STAT_RX` field @def USB_EP0R_STAT_RX_Msk */
#define USB_EP0R_STAT_RX_Msk		REG_FIELD_MASK(USB_EP0R_STAT_RX_Pos, USB_EP0R_STAT_RX_Width)
/** @brief STAT_RX[1:0] bits (Status bits, for reception transfers) @def USB_EP0R_STAT_RX */
#define USB_EP0R_STAT_RX			USB_EP0R_STAT_RX_Msk
/** @brief Register or selector value represented by `USB_EP0R_STAT_RX_0` @def USB_EP0R_STAT_RX_0 */
#define USB_EP0R_STAT_RX_0			(0x1UL << USB_EP0R_STAT_RX_Pos)
/** @brief Register or selector value represented by `USB_EP0R_STAT_RX_1` @def USB_EP0R_STAT_RX_1 */
#define USB_EP0R_STAT_RX_1			(0x2UL << USB_EP0R_STAT_RX_Pos)

/** @brief Bit position of the `USB_EP0R_DTOG_RX` field @def USB_EP0R_DTOG_RX_Pos */
#define USB_EP0R_DTOG_RX_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USB_EP0R_DTOG_RX` field @def USB_EP0R_DTOG_RX_Msk */
#define USB_EP0R_DTOG_RX_Msk		REG_BIT_MASK(USB_EP0R_DTOG_RX_Pos)
/** @brief Data Toggle, for reception transfers @def USB_EP0R_DTOG_RX */
#define USB_EP0R_DTOG_RX			USB_EP0R_DTOG_RX_Msk
/** @brief Bit position of the `USB_EP0R_CTR_RX` field @def USB_EP0R_CTR_RX_Pos */
#define USB_EP0R_CTR_RX_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_EP0R_CTR_RX` field @def USB_EP0R_CTR_RX_Msk */
#define USB_EP0R_CTR_RX_Msk			REG_BIT_MASK(USB_EP0R_CTR_RX_Pos)
/** @brief Correct Transfer for reception @def USB_EP0R_CTR_RX */
#define USB_EP0R_CTR_RX				USB_EP0R_CTR_RX_Msk

// ---------------------------------- USB_EP1R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USB_EP1R_EA` field @def USB_EP1R_EA_Pos */
#define USB_EP1R_EA_Pos				((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_EP1R_EA` field @def USB_EP1R_EA_Width */
#define USB_EP1R_EA_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `USB_EP1R_EA` field @def USB_EP1R_EA_Msk */
#define USB_EP1R_EA_Msk				REG_FIELD_MASK(USB_EP1R_EA_Pos, USB_EP1R_EA_Width)
/** @brief Endpoint Address @def USB_EP1R_EA */
#define USB_EP1R_EA					USB_EP1R_EA_Msk

/** @brief Bit position of the `USB_EP1R_STAT_TX` field @def USB_EP1R_STAT_TX_Pos */
#define USB_EP1R_STAT_TX_Pos		((reg_bit_pos_t) 4U)
/** @brief Width of the `USB_EP1R_STAT_TX` field @def USB_EP1R_STAT_TX_Width */
#define USB_EP1R_STAT_TX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP1R_STAT_TX` field @def USB_EP1R_STAT_TX_Msk */
#define USB_EP1R_STAT_TX_Msk		REG_FIELD_MASK(USB_EP1R_STAT_TX_Pos, USB_EP1R_STAT_TX_Width)
/** @brief STAT_TX[1:0] bits (Status bits, for transmission transfers) @def USB_EP1R_STAT_TX */
#define USB_EP1R_STAT_TX			USB_EP1R_STAT_TX_Msk
/** @brief Register or selector value represented by `USB_EP1R_STAT_TX_0` @def USB_EP1R_STAT_TX_0 */
#define USB_EP1R_STAT_TX_0			(0x1UL << USB_EP1R_STAT_TX_Pos)
/** @brief Register or selector value represented by `USB_EP1R_STAT_TX_1` @def USB_EP1R_STAT_TX_1 */
#define USB_EP1R_STAT_TX_1			(0x2UL << USB_EP1R_STAT_TX_Pos)

/** @brief Bit position of the `USB_EP1R_DTOG_TX` field @def USB_EP1R_DTOG_TX_Pos */
#define USB_EP1R_DTOG_TX_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USB_EP1R_DTOG_TX` field @def USB_EP1R_DTOG_TX_Msk */
#define USB_EP1R_DTOG_TX_Msk		REG_BIT_MASK(USB_EP1R_DTOG_TX_Pos)
/** @brief Data Toggle, for transmission transfers @def USB_EP1R_DTOG_TX */
#define USB_EP1R_DTOG_TX			USB_EP1R_DTOG_TX_Msk
/** @brief Bit position of the `USB_EP1R_CTR_TX` field @def USB_EP1R_CTR_TX_Pos */
#define USB_EP1R_CTR_TX_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USB_EP1R_CTR_TX` field @def USB_EP1R_CTR_TX_Msk */
#define USB_EP1R_CTR_TX_Msk			REG_BIT_MASK(USB_EP1R_CTR_TX_Pos)
/** @brief Correct Transfer for transmission @def USB_EP1R_CTR_TX */
#define USB_EP1R_CTR_TX				USB_EP1R_CTR_TX_Msk
/** @brief Bit position of the `USB_EP1R_EP_KIND` field @def USB_EP1R_EP_KIND_Pos */
#define USB_EP1R_EP_KIND_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USB_EP1R_EP_KIND` field @def USB_EP1R_EP_KIND_Msk */
#define USB_EP1R_EP_KIND_Msk		REG_BIT_MASK(USB_EP1R_EP_KIND_Pos)
/** @brief Endpoint Kind @def USB_EP1R_EP_KIND */
#define USB_EP1R_EP_KIND			USB_EP1R_EP_KIND_Msk

/** @brief Bit position of the `USB_EP1R_EP_TYPE` field @def USB_EP1R_EP_TYPE_Pos */
#define USB_EP1R_EP_TYPE_Pos		((reg_bit_pos_t) 9U)
/** @brief Width of the `USB_EP1R_EP_TYPE` field @def USB_EP1R_EP_TYPE_Width */
#define USB_EP1R_EP_TYPE_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP1R_EP_TYPE` field @def USB_EP1R_EP_TYPE_Msk */
#define USB_EP1R_EP_TYPE_Msk		REG_FIELD_MASK(USB_EP1R_EP_TYPE_Pos, USB_EP1R_EP_TYPE_Width)
/** @brief EP_TYPE[1:0] bits (Endpoint type) @def USB_EP1R_EP_TYPE */
#define USB_EP1R_EP_TYPE			USB_EP1R_EP_TYPE_Msk
/** @brief Register or selector value represented by `USB_EP1R_EP_TYPE_0` @def USB_EP1R_EP_TYPE_0 */
#define USB_EP1R_EP_TYPE_0			(0x1UL << USB_EP1R_EP_TYPE_Pos)
/** @brief Register or selector value represented by `USB_EP1R_EP_TYPE_1` @def USB_EP1R_EP_TYPE_1 */
#define USB_EP1R_EP_TYPE_1			(0x2UL << USB_EP1R_EP_TYPE_Pos)

/** @brief Bit position of the `USB_EP1R_SETUP` field @def USB_EP1R_SETUP_Pos */
#define USB_EP1R_SETUP_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USB_EP1R_SETUP` field @def USB_EP1R_SETUP_Msk */
#define USB_EP1R_SETUP_Msk			REG_BIT_MASK(USB_EP1R_SETUP_Pos)
/** @brief Setup transaction completed @def USB_EP1R_SETUP */
#define USB_EP1R_SETUP				USB_EP1R_SETUP_Msk

/** @brief Bit position of the `USB_EP1R_STAT_RX` field @def USB_EP1R_STAT_RX_Pos */
#define USB_EP1R_STAT_RX_Pos		((reg_bit_pos_t) 12U)
/** @brief Width of the `USB_EP1R_STAT_RX` field @def USB_EP1R_STAT_RX_Width */
#define USB_EP1R_STAT_RX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP1R_STAT_RX` field @def USB_EP1R_STAT_RX_Msk */
#define USB_EP1R_STAT_RX_Msk		REG_FIELD_MASK(USB_EP1R_STAT_RX_Pos, USB_EP1R_STAT_RX_Width)
/** @brief STAT_RX[1:0] bits (Status bits, for reception transfers) @def USB_EP1R_STAT_RX */
#define USB_EP1R_STAT_RX			USB_EP1R_STAT_RX_Msk
/** @brief Register or selector value represented by `USB_EP1R_STAT_RX_0` @def USB_EP1R_STAT_RX_0 */
#define USB_EP1R_STAT_RX_0			(0x1UL << USB_EP1R_STAT_RX_Pos)
/** @brief Register or selector value represented by `USB_EP1R_STAT_RX_1` @def USB_EP1R_STAT_RX_1 */
#define USB_EP1R_STAT_RX_1			(0x2UL << USB_EP1R_STAT_RX_Pos)

/** @brief Bit position of the `USB_EP1R_DTOG_RX` field @def USB_EP1R_DTOG_RX_Pos */
#define USB_EP1R_DTOG_RX_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USB_EP1R_DTOG_RX` field @def USB_EP1R_DTOG_RX_Msk */
#define USB_EP1R_DTOG_RX_Msk		REG_BIT_MASK(USB_EP1R_DTOG_RX_Pos)
/** @brief Data Toggle, for reception transfers @def USB_EP1R_DTOG_RX */
#define USB_EP1R_DTOG_RX			USB_EP1R_DTOG_RX_Msk
/** @brief Bit position of the `USB_EP1R_CTR_RX` field @def USB_EP1R_CTR_RX_Pos */
#define USB_EP1R_CTR_RX_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_EP1R_CTR_RX` field @def USB_EP1R_CTR_RX_Msk */
#define USB_EP1R_CTR_RX_Msk			REG_BIT_MASK(USB_EP1R_CTR_RX_Pos)
/** @brief Correct Transfer for reception @def USB_EP1R_CTR_RX */
#define USB_EP1R_CTR_RX				USB_EP1R_CTR_RX_Msk

// ---------------------------------- USB_EP2R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USB_EP2R_EA` field @def USB_EP2R_EA_Pos */
#define USB_EP2R_EA_Pos				((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_EP2R_EA` field @def USB_EP2R_EA_Width */
#define USB_EP2R_EA_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `USB_EP2R_EA` field @def USB_EP2R_EA_Msk */
#define USB_EP2R_EA_Msk				REG_FIELD_MASK(USB_EP2R_EA_Pos, USB_EP2R_EA_Width)
/** @brief Endpoint Address @def USB_EP2R_EA */
#define USB_EP2R_EA					USB_EP2R_EA_Msk

/** @brief Bit position of the `USB_EP2R_STAT_TX` field @def USB_EP2R_STAT_TX_Pos */
#define USB_EP2R_STAT_TX_Pos		((reg_bit_pos_t) 4U)
/** @brief Width of the `USB_EP2R_STAT_TX` field @def USB_EP2R_STAT_TX_Width */
#define USB_EP2R_STAT_TX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP2R_STAT_TX` field @def USB_EP2R_STAT_TX_Msk */
#define USB_EP2R_STAT_TX_Msk		REG_FIELD_MASK(USB_EP2R_STAT_TX_Pos, USB_EP2R_STAT_TX_Width)
/** @brief STAT_TX[1:0] bits (Status bits, for transmission transfers) @def USB_EP2R_STAT_TX */
#define USB_EP2R_STAT_TX			USB_EP2R_STAT_TX_Msk
/** @brief Register or selector value represented by `USB_EP2R_STAT_TX_0` @def USB_EP2R_STAT_TX_0 */
#define USB_EP2R_STAT_TX_0			(0x1UL << USB_EP2R_STAT_TX_Pos)
/** @brief Register or selector value represented by `USB_EP2R_STAT_TX_1` @def USB_EP2R_STAT_TX_1 */
#define USB_EP2R_STAT_TX_1			(0x2UL << USB_EP2R_STAT_TX_Pos)

/** @brief Bit position of the `USB_EP2R_DTOG_TX` field @def USB_EP2R_DTOG_TX_Pos */
#define USB_EP2R_DTOG_TX_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USB_EP2R_DTOG_TX` field @def USB_EP2R_DTOG_TX_Msk */
#define USB_EP2R_DTOG_TX_Msk		REG_BIT_MASK(USB_EP2R_DTOG_TX_Pos)
/** @brief Data Toggle, for transmission transfers @def USB_EP2R_DTOG_TX */
#define USB_EP2R_DTOG_TX			USB_EP2R_DTOG_TX_Msk
/** @brief Bit position of the `USB_EP2R_CTR_TX` field @def USB_EP2R_CTR_TX_Pos */
#define USB_EP2R_CTR_TX_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USB_EP2R_CTR_TX` field @def USB_EP2R_CTR_TX_Msk */
#define USB_EP2R_CTR_TX_Msk			REG_BIT_MASK(USB_EP2R_CTR_TX_Pos)
/** @brief Correct Transfer for transmission @def USB_EP2R_CTR_TX */
#define USB_EP2R_CTR_TX				USB_EP2R_CTR_TX_Msk
/** @brief Bit position of the `USB_EP2R_EP_KIND` field @def USB_EP2R_EP_KIND_Pos */
#define USB_EP2R_EP_KIND_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USB_EP2R_EP_KIND` field @def USB_EP2R_EP_KIND_Msk */
#define USB_EP2R_EP_KIND_Msk		REG_BIT_MASK(USB_EP2R_EP_KIND_Pos)
/** @brief Endpoint Kind @def USB_EP2R_EP_KIND */
#define USB_EP2R_EP_KIND			USB_EP2R_EP_KIND_Msk

/** @brief Bit position of the `USB_EP2R_EP_TYPE` field @def USB_EP2R_EP_TYPE_Pos */
#define USB_EP2R_EP_TYPE_Pos		((reg_bit_pos_t) 9U)
/** @brief Width of the `USB_EP2R_EP_TYPE` field @def USB_EP2R_EP_TYPE_Width */
#define USB_EP2R_EP_TYPE_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP2R_EP_TYPE` field @def USB_EP2R_EP_TYPE_Msk */
#define USB_EP2R_EP_TYPE_Msk		REG_FIELD_MASK(USB_EP2R_EP_TYPE_Pos, USB_EP2R_EP_TYPE_Width)
/** @brief EP_TYPE[1:0] bits (Endpoint type) @def USB_EP2R_EP_TYPE */
#define USB_EP2R_EP_TYPE			USB_EP2R_EP_TYPE_Msk
/** @brief Register or selector value represented by `USB_EP2R_EP_TYPE_0` @def USB_EP2R_EP_TYPE_0 */
#define USB_EP2R_EP_TYPE_0			(0x1UL << USB_EP2R_EP_TYPE_Pos)
/** @brief Register or selector value represented by `USB_EP2R_EP_TYPE_1` @def USB_EP2R_EP_TYPE_1 */
#define USB_EP2R_EP_TYPE_1			(0x2UL << USB_EP2R_EP_TYPE_Pos)

/** @brief Bit position of the `USB_EP2R_SETUP` field @def USB_EP2R_SETUP_Pos */
#define USB_EP2R_SETUP_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USB_EP2R_SETUP` field @def USB_EP2R_SETUP_Msk */
#define USB_EP2R_SETUP_Msk			REG_BIT_MASK(USB_EP2R_SETUP_Pos)
/** @brief Setup transaction completed @def USB_EP2R_SETUP */
#define USB_EP2R_SETUP				USB_EP2R_SETUP_Msk

/** @brief Bit position of the `USB_EP2R_STAT_RX` field @def USB_EP2R_STAT_RX_Pos */
#define USB_EP2R_STAT_RX_Pos		((reg_bit_pos_t) 12U)
/** @brief Width of the `USB_EP2R_STAT_RX` field @def USB_EP2R_STAT_RX_Width */
#define USB_EP2R_STAT_RX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP2R_STAT_RX` field @def USB_EP2R_STAT_RX_Msk */
#define USB_EP2R_STAT_RX_Msk		REG_FIELD_MASK(USB_EP2R_STAT_RX_Pos, USB_EP2R_STAT_RX_Width)
/** @brief STAT_RX[1:0] bits (Status bits, for reception transfers) @def USB_EP2R_STAT_RX */
#define USB_EP2R_STAT_RX			USB_EP2R_STAT_RX_Msk
/** @brief Register or selector value represented by `USB_EP2R_STAT_RX_0` @def USB_EP2R_STAT_RX_0 */
#define USB_EP2R_STAT_RX_0			(0x1UL << USB_EP2R_STAT_RX_Pos)
/** @brief Register or selector value represented by `USB_EP2R_STAT_RX_1` @def USB_EP2R_STAT_RX_1 */
#define USB_EP2R_STAT_RX_1			(0x2UL << USB_EP2R_STAT_RX_Pos)

/** @brief Bit position of the `USB_EP2R_DTOG_RX` field @def USB_EP2R_DTOG_RX_Pos */
#define USB_EP2R_DTOG_RX_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USB_EP2R_DTOG_RX` field @def USB_EP2R_DTOG_RX_Msk */
#define USB_EP2R_DTOG_RX_Msk		REG_BIT_MASK(USB_EP2R_DTOG_RX_Pos)
/** @brief Data Toggle, for reception transfers @def USB_EP2R_DTOG_RX */
#define USB_EP2R_DTOG_RX			USB_EP2R_DTOG_RX_Msk
/** @brief Bit position of the `USB_EP2R_CTR_RX` field @def USB_EP2R_CTR_RX_Pos */
#define USB_EP2R_CTR_RX_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_EP2R_CTR_RX` field @def USB_EP2R_CTR_RX_Msk */
#define USB_EP2R_CTR_RX_Msk			REG_BIT_MASK(USB_EP2R_CTR_RX_Pos)
/** @brief Correct Transfer for reception @def USB_EP2R_CTR_RX */
#define USB_EP2R_CTR_RX				USB_EP2R_CTR_RX_Msk

// ---------------------------------- USB_EP3R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USB_EP3R_EA` field @def USB_EP3R_EA_Pos */
#define USB_EP3R_EA_Pos				((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_EP3R_EA` field @def USB_EP3R_EA_Width */
#define USB_EP3R_EA_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `USB_EP3R_EA` field @def USB_EP3R_EA_Msk */
#define USB_EP3R_EA_Msk				REG_FIELD_MASK(USB_EP3R_EA_Pos, USB_EP3R_EA_Width)
/** @brief Endpoint Address @def USB_EP3R_EA */
#define USB_EP3R_EA					USB_EP3R_EA_Msk

/** @brief Bit position of the `USB_EP3R_STAT_TX` field @def USB_EP3R_STAT_TX_Pos */
#define USB_EP3R_STAT_TX_Pos		((reg_bit_pos_t) 4U)
/** @brief Width of the `USB_EP3R_STAT_TX` field @def USB_EP3R_STAT_TX_Width */
#define USB_EP3R_STAT_TX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP3R_STAT_TX` field @def USB_EP3R_STAT_TX_Msk */
#define USB_EP3R_STAT_TX_Msk		REG_FIELD_MASK(USB_EP3R_STAT_TX_Pos, USB_EP3R_STAT_TX_Width)
/** @brief STAT_TX[1:0] bits (Status bits, for transmission transfers) @def USB_EP3R_STAT_TX */
#define USB_EP3R_STAT_TX			USB_EP3R_STAT_TX_Msk
/** @brief Register or selector value represented by `USB_EP3R_STAT_TX_0` @def USB_EP3R_STAT_TX_0 */
#define USB_EP3R_STAT_TX_0			(0x1UL << USB_EP3R_STAT_TX_Pos)
/** @brief Register or selector value represented by `USB_EP3R_STAT_TX_1` @def USB_EP3R_STAT_TX_1 */
#define USB_EP3R_STAT_TX_1			(0x2UL << USB_EP3R_STAT_TX_Pos)

/** @brief Bit position of the `USB_EP3R_DTOG_TX` field @def USB_EP3R_DTOG_TX_Pos */
#define USB_EP3R_DTOG_TX_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USB_EP3R_DTOG_TX` field @def USB_EP3R_DTOG_TX_Msk */
#define USB_EP3R_DTOG_TX_Msk		REG_BIT_MASK(USB_EP3R_DTOG_TX_Pos)
/** @brief Data Toggle, for transmission transfers @def USB_EP3R_DTOG_TX */
#define USB_EP3R_DTOG_TX			USB_EP3R_DTOG_TX_Msk
/** @brief Bit position of the `USB_EP3R_CTR_TX` field @def USB_EP3R_CTR_TX_Pos */
#define USB_EP3R_CTR_TX_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USB_EP3R_CTR_TX` field @def USB_EP3R_CTR_TX_Msk */
#define USB_EP3R_CTR_TX_Msk			REG_BIT_MASK(USB_EP3R_CTR_TX_Pos)
/** @brief Correct Transfer for transmission @def USB_EP3R_CTR_TX */
#define USB_EP3R_CTR_TX				USB_EP3R_CTR_TX_Msk
/** @brief Bit position of the `USB_EP3R_EP_KIND` field @def USB_EP3R_EP_KIND_Pos */
#define USB_EP3R_EP_KIND_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USB_EP3R_EP_KIND` field @def USB_EP3R_EP_KIND_Msk */
#define USB_EP3R_EP_KIND_Msk		REG_BIT_MASK(USB_EP3R_EP_KIND_Pos)
/** @brief Endpoint Kind @def USB_EP3R_EP_KIND */
#define USB_EP3R_EP_KIND			USB_EP3R_EP_KIND_Msk

/** @brief Bit position of the `USB_EP3R_EP_TYPE` field @def USB_EP3R_EP_TYPE_Pos */
#define USB_EP3R_EP_TYPE_Pos		((reg_bit_pos_t) 9U)
/** @brief Width of the `USB_EP3R_EP_TYPE` field @def USB_EP3R_EP_TYPE_Width */
#define USB_EP3R_EP_TYPE_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP3R_EP_TYPE` field @def USB_EP3R_EP_TYPE_Msk */
#define USB_EP3R_EP_TYPE_Msk		REG_FIELD_MASK(USB_EP3R_EP_TYPE_Pos, USB_EP3R_EP_TYPE_Width)
/** @brief EP_TYPE[1:0] bits (Endpoint type) @def USB_EP3R_EP_TYPE */
#define USB_EP3R_EP_TYPE			USB_EP3R_EP_TYPE_Msk
/** @brief Register or selector value represented by `USB_EP3R_EP_TYPE_0` @def USB_EP3R_EP_TYPE_0 */
#define USB_EP3R_EP_TYPE_0			(0x1UL << USB_EP3R_EP_TYPE_Pos)
/** @brief Register or selector value represented by `USB_EP3R_EP_TYPE_1` @def USB_EP3R_EP_TYPE_1 */
#define USB_EP3R_EP_TYPE_1			(0x2UL << USB_EP3R_EP_TYPE_Pos)

/** @brief Bit position of the `USB_EP3R_SETUP` field @def USB_EP3R_SETUP_Pos */
#define USB_EP3R_SETUP_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USB_EP3R_SETUP` field @def USB_EP3R_SETUP_Msk */
#define USB_EP3R_SETUP_Msk			REG_BIT_MASK(USB_EP3R_SETUP_Pos)
/** @brief Setup transaction completed @def USB_EP3R_SETUP */
#define USB_EP3R_SETUP				USB_EP3R_SETUP_Msk

/** @brief Bit position of the `USB_EP3R_STAT_RX` field @def USB_EP3R_STAT_RX_Pos */
#define USB_EP3R_STAT_RX_Pos		((reg_bit_pos_t) 12U)
/** @brief Width of the `USB_EP3R_STAT_RX` field @def USB_EP3R_STAT_RX_Width */
#define USB_EP3R_STAT_RX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP3R_STAT_RX` field @def USB_EP3R_STAT_RX_Msk */
#define USB_EP3R_STAT_RX_Msk		REG_FIELD_MASK(USB_EP3R_STAT_RX_Pos, USB_EP3R_STAT_RX_Width)
/** @brief STAT_RX[1:0] bits (Status bits, for reception transfers) @def USB_EP3R_STAT_RX */
#define USB_EP3R_STAT_RX			USB_EP3R_STAT_RX_Msk
/** @brief Register or selector value represented by `USB_EP3R_STAT_RX_0` @def USB_EP3R_STAT_RX_0 */
#define USB_EP3R_STAT_RX_0			(0x1UL << USB_EP3R_STAT_RX_Pos)
/** @brief Register or selector value represented by `USB_EP3R_STAT_RX_1` @def USB_EP3R_STAT_RX_1 */
#define USB_EP3R_STAT_RX_1			(0x2UL << USB_EP3R_STAT_RX_Pos)

/** @brief Bit position of the `USB_EP3R_DTOG_RX` field @def USB_EP3R_DTOG_RX_Pos */
#define USB_EP3R_DTOG_RX_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USB_EP3R_DTOG_RX` field @def USB_EP3R_DTOG_RX_Msk */
#define USB_EP3R_DTOG_RX_Msk		REG_BIT_MASK(USB_EP3R_DTOG_RX_Pos)
/** @brief Data Toggle, for reception transfers @def USB_EP3R_DTOG_RX */
#define USB_EP3R_DTOG_RX			USB_EP3R_DTOG_RX_Msk
/** @brief Bit position of the `USB_EP3R_CTR_RX` field @def USB_EP3R_CTR_RX_Pos */
#define USB_EP3R_CTR_RX_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_EP3R_CTR_RX` field @def USB_EP3R_CTR_RX_Msk */
#define USB_EP3R_CTR_RX_Msk			REG_BIT_MASK(USB_EP3R_CTR_RX_Pos)
/** @brief Correct Transfer for reception @def USB_EP3R_CTR_RX */
#define USB_EP3R_CTR_RX				USB_EP3R_CTR_RX_Msk

// ---------------------------------- USB_EP4R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USB_EP4R_EA` field @def USB_EP4R_EA_Pos */
#define USB_EP4R_EA_Pos				((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_EP4R_EA` field @def USB_EP4R_EA_Width */
#define USB_EP4R_EA_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `USB_EP4R_EA` field @def USB_EP4R_EA_Msk */
#define USB_EP4R_EA_Msk				REG_FIELD_MASK(USB_EP4R_EA_Pos, USB_EP4R_EA_Width)
/** @brief Endpoint Address @def USB_EP4R_EA */
#define USB_EP4R_EA					USB_EP4R_EA_Msk

/** @brief Bit position of the `USB_EP4R_STAT_TX` field @def USB_EP4R_STAT_TX_Pos */
#define USB_EP4R_STAT_TX_Pos		((reg_bit_pos_t) 4U)
/** @brief Width of the `USB_EP4R_STAT_TX` field @def USB_EP4R_STAT_TX_Width */
#define USB_EP4R_STAT_TX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP4R_STAT_TX` field @def USB_EP4R_STAT_TX_Msk */
#define USB_EP4R_STAT_TX_Msk		REG_FIELD_MASK(USB_EP4R_STAT_TX_Pos, USB_EP4R_STAT_TX_Width)
/** @brief STAT_TX[1:0] bits (Status bits, for transmission transfers) @def USB_EP4R_STAT_TX */
#define USB_EP4R_STAT_TX			USB_EP4R_STAT_TX_Msk
/** @brief Register or selector value represented by `USB_EP4R_STAT_TX_0` @def USB_EP4R_STAT_TX_0 */
#define USB_EP4R_STAT_TX_0			(0x1UL << USB_EP4R_STAT_TX_Pos)
/** @brief Register or selector value represented by `USB_EP4R_STAT_TX_1` @def USB_EP4R_STAT_TX_1 */
#define USB_EP4R_STAT_TX_1			(0x2UL << USB_EP4R_STAT_TX_Pos)

/** @brief Bit position of the `USB_EP4R_DTOG_TX` field @def USB_EP4R_DTOG_TX_Pos */
#define USB_EP4R_DTOG_TX_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USB_EP4R_DTOG_TX` field @def USB_EP4R_DTOG_TX_Msk */
#define USB_EP4R_DTOG_TX_Msk		REG_BIT_MASK(USB_EP4R_DTOG_TX_Pos)
/** @brief Data Toggle, for transmission transfers @def USB_EP4R_DTOG_TX */
#define USB_EP4R_DTOG_TX			USB_EP4R_DTOG_TX_Msk
/** @brief Bit position of the `USB_EP4R_CTR_TX` field @def USB_EP4R_CTR_TX_Pos */
#define USB_EP4R_CTR_TX_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USB_EP4R_CTR_TX` field @def USB_EP4R_CTR_TX_Msk */
#define USB_EP4R_CTR_TX_Msk			REG_BIT_MASK(USB_EP4R_CTR_TX_Pos)
/** @brief Correct Transfer for transmission @def USB_EP4R_CTR_TX */
#define USB_EP4R_CTR_TX				USB_EP4R_CTR_TX_Msk
/** @brief Bit position of the `USB_EP4R_EP_KIND` field @def USB_EP4R_EP_KIND_Pos */
#define USB_EP4R_EP_KIND_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USB_EP4R_EP_KIND` field @def USB_EP4R_EP_KIND_Msk */
#define USB_EP4R_EP_KIND_Msk		REG_BIT_MASK(USB_EP4R_EP_KIND_Pos)
/** @brief Endpoint Kind @def USB_EP4R_EP_KIND */
#define USB_EP4R_EP_KIND			USB_EP4R_EP_KIND_Msk

/** @brief Bit position of the `USB_EP4R_EP_TYPE` field @def USB_EP4R_EP_TYPE_Pos */
#define USB_EP4R_EP_TYPE_Pos		((reg_bit_pos_t) 9U)
/** @brief Width of the `USB_EP4R_EP_TYPE` field @def USB_EP4R_EP_TYPE_Width */
#define USB_EP4R_EP_TYPE_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP4R_EP_TYPE` field @def USB_EP4R_EP_TYPE_Msk */
#define USB_EP4R_EP_TYPE_Msk		REG_FIELD_MASK(USB_EP4R_EP_TYPE_Pos, USB_EP4R_EP_TYPE_Width)
/** @brief EP_TYPE[1:0] bits (Endpoint type) @def USB_EP4R_EP_TYPE */
#define USB_EP4R_EP_TYPE			USB_EP4R_EP_TYPE_Msk
/** @brief Register or selector value represented by `USB_EP4R_EP_TYPE_0` @def USB_EP4R_EP_TYPE_0 */
#define USB_EP4R_EP_TYPE_0			(0x1UL << USB_EP4R_EP_TYPE_Pos)
/** @brief Register or selector value represented by `USB_EP4R_EP_TYPE_1` @def USB_EP4R_EP_TYPE_1 */
#define USB_EP4R_EP_TYPE_1			(0x2UL << USB_EP4R_EP_TYPE_Pos)

/** @brief Bit position of the `USB_EP4R_SETUP` field @def USB_EP4R_SETUP_Pos */
#define USB_EP4R_SETUP_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USB_EP4R_SETUP` field @def USB_EP4R_SETUP_Msk */
#define USB_EP4R_SETUP_Msk			REG_BIT_MASK(USB_EP4R_SETUP_Pos)
/** @brief Setup transaction completed @def USB_EP4R_SETUP */
#define USB_EP4R_SETUP				USB_EP4R_SETUP_Msk

/** @brief Bit position of the `USB_EP4R_STAT_RX` field @def USB_EP4R_STAT_RX_Pos */
#define USB_EP4R_STAT_RX_Pos		((reg_bit_pos_t) 12U)
/** @brief Width of the `USB_EP4R_STAT_RX` field @def USB_EP4R_STAT_RX_Width */
#define USB_EP4R_STAT_RX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP4R_STAT_RX` field @def USB_EP4R_STAT_RX_Msk */
#define USB_EP4R_STAT_RX_Msk		REG_FIELD_MASK(USB_EP4R_STAT_RX_Pos, USB_EP4R_STAT_RX_Width)
/** @brief STAT_RX[1:0] bits (Status bits, for reception transfers) @def USB_EP4R_STAT_RX */
#define USB_EP4R_STAT_RX			USB_EP4R_STAT_RX_Msk
/** @brief Register or selector value represented by `USB_EP4R_STAT_RX_0` @def USB_EP4R_STAT_RX_0 */
#define USB_EP4R_STAT_RX_0			(0x1UL << USB_EP4R_STAT_RX_Pos)
/** @brief Register or selector value represented by `USB_EP4R_STAT_RX_1` @def USB_EP4R_STAT_RX_1 */
#define USB_EP4R_STAT_RX_1			(0x2UL << USB_EP4R_STAT_RX_Pos)

/** @brief Bit position of the `USB_EP4R_DTOG_RX` field @def USB_EP4R_DTOG_RX_Pos */
#define USB_EP4R_DTOG_RX_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USB_EP4R_DTOG_RX` field @def USB_EP4R_DTOG_RX_Msk */
#define USB_EP4R_DTOG_RX_Msk		REG_BIT_MASK(USB_EP4R_DTOG_RX_Pos)
/** @brief Data Toggle, for reception transfers @def USB_EP4R_DTOG_RX */
#define USB_EP4R_DTOG_RX			USB_EP4R_DTOG_RX_Msk
/** @brief Bit position of the `USB_EP4R_CTR_RX` field @def USB_EP4R_CTR_RX_Pos */
#define USB_EP4R_CTR_RX_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_EP4R_CTR_RX` field @def USB_EP4R_CTR_RX_Msk */
#define USB_EP4R_CTR_RX_Msk			REG_BIT_MASK(USB_EP4R_CTR_RX_Pos)
/** @brief Correct Transfer for reception @def USB_EP4R_CTR_RX */
#define USB_EP4R_CTR_RX				USB_EP4R_CTR_RX_Msk

// ---------------------------------- USB_EP5R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USB_EP5R_EA` field @def USB_EP5R_EA_Pos */
#define USB_EP5R_EA_Pos				((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_EP5R_EA` field @def USB_EP5R_EA_Width */
#define USB_EP5R_EA_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `USB_EP5R_EA` field @def USB_EP5R_EA_Msk */
#define USB_EP5R_EA_Msk				REG_FIELD_MASK(USB_EP5R_EA_Pos, USB_EP5R_EA_Width)
/** @brief Endpoint Address @def USB_EP5R_EA */
#define USB_EP5R_EA					USB_EP5R_EA_Msk

/** @brief Bit position of the `USB_EP5R_STAT_TX` field @def USB_EP5R_STAT_TX_Pos */
#define USB_EP5R_STAT_TX_Pos		((reg_bit_pos_t) 4U)
/** @brief Width of the `USB_EP5R_STAT_TX` field @def USB_EP5R_STAT_TX_Width */
#define USB_EP5R_STAT_TX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP5R_STAT_TX` field @def USB_EP5R_STAT_TX_Msk */
#define USB_EP5R_STAT_TX_Msk		REG_FIELD_MASK(USB_EP5R_STAT_TX_Pos, USB_EP5R_STAT_TX_Width)
/** @brief STAT_TX[1:0] bits (Status bits, for transmission transfers) @def USB_EP5R_STAT_TX */
#define USB_EP5R_STAT_TX			USB_EP5R_STAT_TX_Msk
/** @brief Register or selector value represented by `USB_EP5R_STAT_TX_0` @def USB_EP5R_STAT_TX_0 */
#define USB_EP5R_STAT_TX_0			(0x1UL << USB_EP5R_STAT_TX_Pos)
/** @brief Register or selector value represented by `USB_EP5R_STAT_TX_1` @def USB_EP5R_STAT_TX_1 */
#define USB_EP5R_STAT_TX_1			(0x2UL << USB_EP5R_STAT_TX_Pos)

/** @brief Bit position of the `USB_EP5R_DTOG_TX` field @def USB_EP5R_DTOG_TX_Pos */
#define USB_EP5R_DTOG_TX_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USB_EP5R_DTOG_TX` field @def USB_EP5R_DTOG_TX_Msk */
#define USB_EP5R_DTOG_TX_Msk		REG_BIT_MASK(USB_EP5R_DTOG_TX_Pos)
/** @brief Data Toggle, for transmission transfers @def USB_EP5R_DTOG_TX */
#define USB_EP5R_DTOG_TX			USB_EP5R_DTOG_TX_Msk
/** @brief Bit position of the `USB_EP5R_CTR_TX` field @def USB_EP5R_CTR_TX_Pos */
#define USB_EP5R_CTR_TX_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USB_EP5R_CTR_TX` field @def USB_EP5R_CTR_TX_Msk */
#define USB_EP5R_CTR_TX_Msk			REG_BIT_MASK(USB_EP5R_CTR_TX_Pos)
/** @brief Correct Transfer for transmission @def USB_EP5R_CTR_TX */
#define USB_EP5R_CTR_TX				USB_EP5R_CTR_TX_Msk
/** @brief Bit position of the `USB_EP5R_EP_KIND` field @def USB_EP5R_EP_KIND_Pos */
#define USB_EP5R_EP_KIND_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USB_EP5R_EP_KIND` field @def USB_EP5R_EP_KIND_Msk */
#define USB_EP5R_EP_KIND_Msk		REG_BIT_MASK(USB_EP5R_EP_KIND_Pos)
/** @brief Endpoint Kind @def USB_EP5R_EP_KIND */
#define USB_EP5R_EP_KIND			USB_EP5R_EP_KIND_Msk

/** @brief Bit position of the `USB_EP5R_EP_TYPE` field @def USB_EP5R_EP_TYPE_Pos */
#define USB_EP5R_EP_TYPE_Pos		((reg_bit_pos_t) 9U)
/** @brief Width of the `USB_EP5R_EP_TYPE` field @def USB_EP5R_EP_TYPE_Width */
#define USB_EP5R_EP_TYPE_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP5R_EP_TYPE` field @def USB_EP5R_EP_TYPE_Msk */
#define USB_EP5R_EP_TYPE_Msk		REG_FIELD_MASK(USB_EP5R_EP_TYPE_Pos, USB_EP5R_EP_TYPE_Width)
/** @brief EP_TYPE[1:0] bits (Endpoint type) @def USB_EP5R_EP_TYPE */
#define USB_EP5R_EP_TYPE			USB_EP5R_EP_TYPE_Msk
/** @brief Register or selector value represented by `USB_EP5R_EP_TYPE_0` @def USB_EP5R_EP_TYPE_0 */
#define USB_EP5R_EP_TYPE_0			(0x1UL << USB_EP5R_EP_TYPE_Pos)
/** @brief Register or selector value represented by `USB_EP5R_EP_TYPE_1` @def USB_EP5R_EP_TYPE_1 */
#define USB_EP5R_EP_TYPE_1			(0x2UL << USB_EP5R_EP_TYPE_Pos)

/** @brief Bit position of the `USB_EP5R_SETUP` field @def USB_EP5R_SETUP_Pos */
#define USB_EP5R_SETUP_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USB_EP5R_SETUP` field @def USB_EP5R_SETUP_Msk */
#define USB_EP5R_SETUP_Msk			REG_BIT_MASK(USB_EP5R_SETUP_Pos)
/** @brief Setup transaction completed @def USB_EP5R_SETUP */
#define USB_EP5R_SETUP				USB_EP5R_SETUP_Msk

/** @brief Bit position of the `USB_EP5R_STAT_RX` field @def USB_EP5R_STAT_RX_Pos */
#define USB_EP5R_STAT_RX_Pos		((reg_bit_pos_t) 12U)
/** @brief Width of the `USB_EP5R_STAT_RX` field @def USB_EP5R_STAT_RX_Width */
#define USB_EP5R_STAT_RX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP5R_STAT_RX` field @def USB_EP5R_STAT_RX_Msk */
#define USB_EP5R_STAT_RX_Msk		REG_FIELD_MASK(USB_EP5R_STAT_RX_Pos, USB_EP5R_STAT_RX_Width)
/** @brief STAT_RX[1:0] bits (Status bits, for reception transfers) @def USB_EP5R_STAT_RX */
#define USB_EP5R_STAT_RX			USB_EP5R_STAT_RX_Msk
/** @brief Register or selector value represented by `USB_EP5R_STAT_RX_0` @def USB_EP5R_STAT_RX_0 */
#define USB_EP5R_STAT_RX_0			(0x1UL << USB_EP5R_STAT_RX_Pos)
/** @brief Register or selector value represented by `USB_EP5R_STAT_RX_1` @def USB_EP5R_STAT_RX_1 */
#define USB_EP5R_STAT_RX_1			(0x2UL << USB_EP5R_STAT_RX_Pos)

/** @brief Bit position of the `USB_EP5R_DTOG_RX` field @def USB_EP5R_DTOG_RX_Pos */
#define USB_EP5R_DTOG_RX_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USB_EP5R_DTOG_RX` field @def USB_EP5R_DTOG_RX_Msk */
#define USB_EP5R_DTOG_RX_Msk		REG_BIT_MASK(USB_EP5R_DTOG_RX_Pos)
/** @brief Data Toggle, for reception transfers @def USB_EP5R_DTOG_RX */
#define USB_EP5R_DTOG_RX			USB_EP5R_DTOG_RX_Msk
/** @brief Bit position of the `USB_EP5R_CTR_RX` field @def USB_EP5R_CTR_RX_Pos */
#define USB_EP5R_CTR_RX_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_EP5R_CTR_RX` field @def USB_EP5R_CTR_RX_Msk */
#define USB_EP5R_CTR_RX_Msk			REG_BIT_MASK(USB_EP5R_CTR_RX_Pos)
/** @brief Correct Transfer for reception @def USB_EP5R_CTR_RX */
#define USB_EP5R_CTR_RX				USB_EP5R_CTR_RX_Msk

// ---------------------------------- USB_EP6R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USB_EP6R_EA` field @def USB_EP6R_EA_Pos */
#define USB_EP6R_EA_Pos				((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_EP6R_EA` field @def USB_EP6R_EA_Width */
#define USB_EP6R_EA_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `USB_EP6R_EA` field @def USB_EP6R_EA_Msk */
#define USB_EP6R_EA_Msk				REG_FIELD_MASK(USB_EP6R_EA_Pos, USB_EP6R_EA_Width)
/** @brief Endpoint Address @def USB_EP6R_EA */
#define USB_EP6R_EA					USB_EP6R_EA_Msk

/** @brief Bit position of the `USB_EP6R_STAT_TX` field @def USB_EP6R_STAT_TX_Pos */
#define USB_EP6R_STAT_TX_Pos		((reg_bit_pos_t) 4U)
/** @brief Width of the `USB_EP6R_STAT_TX` field @def USB_EP6R_STAT_TX_Width */
#define USB_EP6R_STAT_TX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP6R_STAT_TX` field @def USB_EP6R_STAT_TX_Msk */
#define USB_EP6R_STAT_TX_Msk		REG_FIELD_MASK(USB_EP6R_STAT_TX_Pos, USB_EP6R_STAT_TX_Width)
/** @brief STAT_TX[1:0] bits (Status bits, for transmission transfers) @def USB_EP6R_STAT_TX */
#define USB_EP6R_STAT_TX			USB_EP6R_STAT_TX_Msk
/** @brief Register or selector value represented by `USB_EP6R_STAT_TX_0` @def USB_EP6R_STAT_TX_0 */
#define USB_EP6R_STAT_TX_0			(0x1UL << USB_EP6R_STAT_TX_Pos)
/** @brief Register or selector value represented by `USB_EP6R_STAT_TX_1` @def USB_EP6R_STAT_TX_1 */
#define USB_EP6R_STAT_TX_1			(0x2UL << USB_EP6R_STAT_TX_Pos)

/** @brief Bit position of the `USB_EP6R_DTOG_TX` field @def USB_EP6R_DTOG_TX_Pos */
#define USB_EP6R_DTOG_TX_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USB_EP6R_DTOG_TX` field @def USB_EP6R_DTOG_TX_Msk */
#define USB_EP6R_DTOG_TX_Msk		REG_BIT_MASK(USB_EP6R_DTOG_TX_Pos)
/** @brief Data Toggle, for transmission transfers @def USB_EP6R_DTOG_TX */
#define USB_EP6R_DTOG_TX			USB_EP6R_DTOG_TX_Msk
/** @brief Bit position of the `USB_EP6R_CTR_TX` field @def USB_EP6R_CTR_TX_Pos */
#define USB_EP6R_CTR_TX_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USB_EP6R_CTR_TX` field @def USB_EP6R_CTR_TX_Msk */
#define USB_EP6R_CTR_TX_Msk			REG_BIT_MASK(USB_EP6R_CTR_TX_Pos)
/** @brief Correct Transfer for transmission @def USB_EP6R_CTR_TX */
#define USB_EP6R_CTR_TX				USB_EP6R_CTR_TX_Msk
/** @brief Bit position of the `USB_EP6R_EP_KIND` field @def USB_EP6R_EP_KIND_Pos */
#define USB_EP6R_EP_KIND_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USB_EP6R_EP_KIND` field @def USB_EP6R_EP_KIND_Msk */
#define USB_EP6R_EP_KIND_Msk		REG_BIT_MASK(USB_EP6R_EP_KIND_Pos)
/** @brief Endpoint Kind @def USB_EP6R_EP_KIND */
#define USB_EP6R_EP_KIND			USB_EP6R_EP_KIND_Msk

/** @brief Bit position of the `USB_EP6R_EP_TYPE` field @def USB_EP6R_EP_TYPE_Pos */
#define USB_EP6R_EP_TYPE_Pos		((reg_bit_pos_t) 9U)
/** @brief Width of the `USB_EP6R_EP_TYPE` field @def USB_EP6R_EP_TYPE_Width */
#define USB_EP6R_EP_TYPE_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP6R_EP_TYPE` field @def USB_EP6R_EP_TYPE_Msk */
#define USB_EP6R_EP_TYPE_Msk		REG_FIELD_MASK(USB_EP6R_EP_TYPE_Pos, USB_EP6R_EP_TYPE_Width)
/** @brief EP_TYPE[1:0] bits (Endpoint type) @def USB_EP6R_EP_TYPE */
#define USB_EP6R_EP_TYPE			USB_EP6R_EP_TYPE_Msk
/** @brief Register or selector value represented by `USB_EP6R_EP_TYPE_0` @def USB_EP6R_EP_TYPE_0 */
#define USB_EP6R_EP_TYPE_0			(0x1UL << USB_EP6R_EP_TYPE_Pos)
/** @brief Register or selector value represented by `USB_EP6R_EP_TYPE_1` @def USB_EP6R_EP_TYPE_1 */
#define USB_EP6R_EP_TYPE_1			(0x2UL << USB_EP6R_EP_TYPE_Pos)

/** @brief Bit position of the `USB_EP6R_SETUP` field @def USB_EP6R_SETUP_Pos */
#define USB_EP6R_SETUP_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USB_EP6R_SETUP` field @def USB_EP6R_SETUP_Msk */
#define USB_EP6R_SETUP_Msk			REG_BIT_MASK(USB_EP6R_SETUP_Pos)
/** @brief Setup transaction completed @def USB_EP6R_SETUP */
#define USB_EP6R_SETUP				USB_EP6R_SETUP_Msk

/** @brief Bit position of the `USB_EP6R_STAT_RX` field @def USB_EP6R_STAT_RX_Pos */
#define USB_EP6R_STAT_RX_Pos		((reg_bit_pos_t) 12U)
/** @brief Width of the `USB_EP6R_STAT_RX` field @def USB_EP6R_STAT_RX_Width */
#define USB_EP6R_STAT_RX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP6R_STAT_RX` field @def USB_EP6R_STAT_RX_Msk */
#define USB_EP6R_STAT_RX_Msk		REG_FIELD_MASK(USB_EP6R_STAT_RX_Pos, USB_EP6R_STAT_RX_Width)
/** @brief STAT_RX[1:0] bits (Status bits, for reception transfers) @def USB_EP6R_STAT_RX */
#define USB_EP6R_STAT_RX			USB_EP6R_STAT_RX_Msk
/** @brief Register or selector value represented by `USB_EP6R_STAT_RX_0` @def USB_EP6R_STAT_RX_0 */
#define USB_EP6R_STAT_RX_0			(0x1UL << USB_EP6R_STAT_RX_Pos)
/** @brief Register or selector value represented by `USB_EP6R_STAT_RX_1` @def USB_EP6R_STAT_RX_1 */
#define USB_EP6R_STAT_RX_1			(0x2UL << USB_EP6R_STAT_RX_Pos)

/** @brief Bit position of the `USB_EP6R_DTOG_RX` field @def USB_EP6R_DTOG_RX_Pos */
#define USB_EP6R_DTOG_RX_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USB_EP6R_DTOG_RX` field @def USB_EP6R_DTOG_RX_Msk */
#define USB_EP6R_DTOG_RX_Msk		REG_BIT_MASK(USB_EP6R_DTOG_RX_Pos)
/** @brief Data Toggle, for reception transfers @def USB_EP6R_DTOG_RX */
#define USB_EP6R_DTOG_RX			USB_EP6R_DTOG_RX_Msk
/** @brief Bit position of the `USB_EP6R_CTR_RX` field @def USB_EP6R_CTR_RX_Pos */
#define USB_EP6R_CTR_RX_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_EP6R_CTR_RX` field @def USB_EP6R_CTR_RX_Msk */
#define USB_EP6R_CTR_RX_Msk			REG_BIT_MASK(USB_EP6R_CTR_RX_Pos)
/** @brief Correct Transfer for reception @def USB_EP6R_CTR_RX */
#define USB_EP6R_CTR_RX				USB_EP6R_CTR_RX_Msk

// ---------------------------------- USB_EP7R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USB_EP7R_EA` field @def USB_EP7R_EA_Pos */
#define USB_EP7R_EA_Pos				((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_EP7R_EA` field @def USB_EP7R_EA_Width */
#define USB_EP7R_EA_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `USB_EP7R_EA` field @def USB_EP7R_EA_Msk */
#define USB_EP7R_EA_Msk				REG_FIELD_MASK(USB_EP7R_EA_Pos, USB_EP7R_EA_Width)
/** @brief Endpoint Address @def USB_EP7R_EA */
#define USB_EP7R_EA					USB_EP7R_EA_Msk

/** @brief Bit position of the `USB_EP7R_STAT_TX` field @def USB_EP7R_STAT_TX_Pos */
#define USB_EP7R_STAT_TX_Pos		((reg_bit_pos_t) 4U)
/** @brief Width of the `USB_EP7R_STAT_TX` field @def USB_EP7R_STAT_TX_Width */
#define USB_EP7R_STAT_TX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP7R_STAT_TX` field @def USB_EP7R_STAT_TX_Msk */
#define USB_EP7R_STAT_TX_Msk		REG_FIELD_MASK(USB_EP7R_STAT_TX_Pos, USB_EP7R_STAT_TX_Width)
/** @brief STAT_TX[1:0] bits (Status bits, for transmission transfers) @def USB_EP7R_STAT_TX */
#define USB_EP7R_STAT_TX			USB_EP7R_STAT_TX_Msk
/** @brief Register or selector value represented by `USB_EP7R_STAT_TX_0` @def USB_EP7R_STAT_TX_0 */
#define USB_EP7R_STAT_TX_0			(0x1UL << USB_EP7R_STAT_TX_Pos)
/** @brief Register or selector value represented by `USB_EP7R_STAT_TX_1` @def USB_EP7R_STAT_TX_1 */
#define USB_EP7R_STAT_TX_1			(0x2UL << USB_EP7R_STAT_TX_Pos)

/** @brief Bit position of the `USB_EP7R_DTOG_TX` field @def USB_EP7R_DTOG_TX_Pos */
#define USB_EP7R_DTOG_TX_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USB_EP7R_DTOG_TX` field @def USB_EP7R_DTOG_TX_Msk */
#define USB_EP7R_DTOG_TX_Msk		REG_BIT_MASK(USB_EP7R_DTOG_TX_Pos)
/** @brief Data Toggle, for transmission transfers @def USB_EP7R_DTOG_TX */
#define USB_EP7R_DTOG_TX			USB_EP7R_DTOG_TX_Msk
/** @brief Bit position of the `USB_EP7R_CTR_TX` field @def USB_EP7R_CTR_TX_Pos */
#define USB_EP7R_CTR_TX_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USB_EP7R_CTR_TX` field @def USB_EP7R_CTR_TX_Msk */
#define USB_EP7R_CTR_TX_Msk			REG_BIT_MASK(USB_EP7R_CTR_TX_Pos)
/** @brief Correct Transfer for transmission @def USB_EP7R_CTR_TX */
#define USB_EP7R_CTR_TX				USB_EP7R_CTR_TX_Msk
/** @brief Bit position of the `USB_EP7R_EP_KIND` field @def USB_EP7R_EP_KIND_Pos */
#define USB_EP7R_EP_KIND_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USB_EP7R_EP_KIND` field @def USB_EP7R_EP_KIND_Msk */
#define USB_EP7R_EP_KIND_Msk		REG_BIT_MASK(USB_EP7R_EP_KIND_Pos)
/** @brief Endpoint Kind @def USB_EP7R_EP_KIND */
#define USB_EP7R_EP_KIND			USB_EP7R_EP_KIND_Msk

/** @brief Bit position of the `USB_EP7R_EP_TYPE` field @def USB_EP7R_EP_TYPE_Pos */
#define USB_EP7R_EP_TYPE_Pos		((reg_bit_pos_t) 9U)
/** @brief Width of the `USB_EP7R_EP_TYPE` field @def USB_EP7R_EP_TYPE_Width */
#define USB_EP7R_EP_TYPE_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP7R_EP_TYPE` field @def USB_EP7R_EP_TYPE_Msk */
#define USB_EP7R_EP_TYPE_Msk		REG_FIELD_MASK(USB_EP7R_EP_TYPE_Pos, USB_EP7R_EP_TYPE_Width)
/** @brief EP_TYPE[1:0] bits (Endpoint type) @def USB_EP7R_EP_TYPE */
#define USB_EP7R_EP_TYPE			USB_EP7R_EP_TYPE_Msk
/** @brief Register or selector value represented by `USB_EP7R_EP_TYPE_0` @def USB_EP7R_EP_TYPE_0 */
#define USB_EP7R_EP_TYPE_0			(0x1UL << USB_EP7R_EP_TYPE_Pos)
/** @brief Register or selector value represented by `USB_EP7R_EP_TYPE_1` @def USB_EP7R_EP_TYPE_1 */
#define USB_EP7R_EP_TYPE_1			(0x2UL << USB_EP7R_EP_TYPE_Pos)

/** @brief Bit position of the `USB_EP7R_SETUP` field @def USB_EP7R_SETUP_Pos */
#define USB_EP7R_SETUP_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USB_EP7R_SETUP` field @def USB_EP7R_SETUP_Msk */
#define USB_EP7R_SETUP_Msk			REG_BIT_MASK(USB_EP7R_SETUP_Pos)
/** @brief Setup transaction completed @def USB_EP7R_SETUP */
#define USB_EP7R_SETUP				USB_EP7R_SETUP_Msk

/** @brief Bit position of the `USB_EP7R_STAT_RX` field @def USB_EP7R_STAT_RX_Pos */
#define USB_EP7R_STAT_RX_Pos		((reg_bit_pos_t) 12U)
/** @brief Width of the `USB_EP7R_STAT_RX` field @def USB_EP7R_STAT_RX_Width */
#define USB_EP7R_STAT_RX_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_EP7R_STAT_RX` field @def USB_EP7R_STAT_RX_Msk */
#define USB_EP7R_STAT_RX_Msk		REG_FIELD_MASK(USB_EP7R_STAT_RX_Pos, USB_EP7R_STAT_RX_Width)
/** @brief STAT_RX[1:0] bits (Status bits, for reception transfers) @def USB_EP7R_STAT_RX */
#define USB_EP7R_STAT_RX			USB_EP7R_STAT_RX_Msk
/** @brief Register or selector value represented by `USB_EP7R_STAT_RX_0` @def USB_EP7R_STAT_RX_0 */
#define USB_EP7R_STAT_RX_0			(0x1UL << USB_EP7R_STAT_RX_Pos)
/** @brief Register or selector value represented by `USB_EP7R_STAT_RX_1` @def USB_EP7R_STAT_RX_1 */
#define USB_EP7R_STAT_RX_1			(0x2UL << USB_EP7R_STAT_RX_Pos)

/** @brief Bit position of the `USB_EP7R_DTOG_RX` field @def USB_EP7R_DTOG_RX_Pos */
#define USB_EP7R_DTOG_RX_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USB_EP7R_DTOG_RX` field @def USB_EP7R_DTOG_RX_Msk */
#define USB_EP7R_DTOG_RX_Msk		REG_BIT_MASK(USB_EP7R_DTOG_RX_Pos)
/** @brief Data Toggle, for reception transfers @def USB_EP7R_DTOG_RX */
#define USB_EP7R_DTOG_RX			USB_EP7R_DTOG_RX_Msk
/** @brief Bit position of the `USB_EP7R_CTR_RX` field @def USB_EP7R_CTR_RX_Pos */
#define USB_EP7R_CTR_RX_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_EP7R_CTR_RX` field @def USB_EP7R_CTR_RX_Msk */
#define USB_EP7R_CTR_RX_Msk			REG_BIT_MASK(USB_EP7R_CTR_RX_Pos)
/** @brief Correct Transfer for reception @def USB_EP7R_CTR_RX */
#define USB_EP7R_CTR_RX				USB_EP7R_CTR_RX_Msk

// ----------------------------------- USB Common Register Defines ------------------------------------ //
// ---------------------------------- USB_CNTR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USB_CNTR_FRES` field @def USB_CNTR_FRES_Pos */
#define USB_CNTR_FRES_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `USB_CNTR_FRES` field @def USB_CNTR_FRES_Msk */
#define USB_CNTR_FRES_Msk			REG_BIT_MASK(USB_CNTR_FRES_Pos)
/** @brief Force USB Reset @def USB_CNTR_FRES */
#define USB_CNTR_FRES				USB_CNTR_FRES_Msk
/** @brief Bit position of the `USB_CNTR_PDWN` field @def USB_CNTR_PDWN_Pos */
#define USB_CNTR_PDWN_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `USB_CNTR_PDWN` field @def USB_CNTR_PDWN_Msk */
#define USB_CNTR_PDWN_Msk			REG_BIT_MASK(USB_CNTR_PDWN_Pos)
/** @brief Power down @def USB_CNTR_PDWN */
#define USB_CNTR_PDWN				USB_CNTR_PDWN_Msk
/** @brief Bit position of the `USB_CNTR_LP_MODE` field @def USB_CNTR_LP_MODE_Pos */
#define USB_CNTR_LP_MODE_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `USB_CNTR_LP_MODE` field @def USB_CNTR_LP_MODE_Msk */
#define USB_CNTR_LP_MODE_Msk		REG_BIT_MASK(USB_CNTR_LP_MODE_Pos)
/** @brief Low-power mode @def USB_CNTR_LP_MODE */
#define USB_CNTR_LP_MODE			USB_CNTR_LP_MODE_Msk
/** @brief Bit position of the `USB_CNTR_FSUSP` field @def USB_CNTR_FSUSP_Pos */
#define USB_CNTR_FSUSP_Pos			((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `USB_CNTR_FSUSP` field @def USB_CNTR_FSUSP_Msk */
#define USB_CNTR_FSUSP_Msk			REG_BIT_MASK(USB_CNTR_FSUSP_Pos)
/** @brief Force suspend @def USB_CNTR_FSUSP */
#define USB_CNTR_FSUSP				USB_CNTR_FSUSP_Msk
/** @brief Bit position of the `USB_CNTR_RESUME` field @def USB_CNTR_RESUME_Pos */
#define USB_CNTR_RESUME_Pos			((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `USB_CNTR_RESUME` field @def USB_CNTR_RESUME_Msk */
#define USB_CNTR_RESUME_Msk			REG_BIT_MASK(USB_CNTR_RESUME_Pos)
/** @brief Resume request @def USB_CNTR_RESUME */
#define USB_CNTR_RESUME				USB_CNTR_RESUME_Msk
/** @brief Bit position of the `USB_CNTR_ESOFM` field @def USB_CNTR_ESOFM_Pos */
#define USB_CNTR_ESOFM_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USB_CNTR_ESOFM` field @def USB_CNTR_ESOFM_Msk */
#define USB_CNTR_ESOFM_Msk			REG_BIT_MASK(USB_CNTR_ESOFM_Pos)
/** @brief Expected Start Of Frame Interrupt Mask @def USB_CNTR_ESOFM */
#define USB_CNTR_ESOFM				USB_CNTR_ESOFM_Msk
/** @brief Bit position of the `USB_CNTR_SOFM` field @def USB_CNTR_SOFM_Pos */
#define USB_CNTR_SOFM_Pos			((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `USB_CNTR_SOFM` field @def USB_CNTR_SOFM_Msk */
#define USB_CNTR_SOFM_Msk			REG_BIT_MASK(USB_CNTR_SOFM_Pos)
/** @brief Start Of Frame Interrupt Mask @def USB_CNTR_SOFM */
#define USB_CNTR_SOFM				USB_CNTR_SOFM_Msk
/** @brief Bit position of the `USB_CNTR_RESETM` field @def USB_CNTR_RESETM_Pos */
#define USB_CNTR_RESETM_Pos			((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `USB_CNTR_RESETM` field @def USB_CNTR_RESETM_Msk */
#define USB_CNTR_RESETM_Msk			REG_BIT_MASK(USB_CNTR_RESETM_Pos)
/** @brief RESET Interrupt Mask @def USB_CNTR_RESETM */
#define USB_CNTR_RESETM				USB_CNTR_RESETM_Msk
/** @brief Bit position of the `USB_CNTR_SUSPM` field @def USB_CNTR_SUSPM_Pos */
#define USB_CNTR_SUSPM_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USB_CNTR_SUSPM` field @def USB_CNTR_SUSPM_Msk */
#define USB_CNTR_SUSPM_Msk			REG_BIT_MASK(USB_CNTR_SUSPM_Pos)
/** @brief Suspend mode Interrupt Mask @def USB_CNTR_SUSPM */
#define USB_CNTR_SUSPM				USB_CNTR_SUSPM_Msk
/** @brief Bit position of the `USB_CNTR_WKUPM` field @def USB_CNTR_WKUPM_Pos */
#define USB_CNTR_WKUPM_Pos			((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `USB_CNTR_WKUPM` field @def USB_CNTR_WKUPM_Msk */
#define USB_CNTR_WKUPM_Msk			REG_BIT_MASK(USB_CNTR_WKUPM_Pos)
/** @brief Wakeup Interrupt Mask @def USB_CNTR_WKUPM */
#define USB_CNTR_WKUPM				USB_CNTR_WKUPM_Msk
/** @brief Bit position of the `USB_CNTR_ERRM` field @def USB_CNTR_ERRM_Pos */
#define USB_CNTR_ERRM_Pos			((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `USB_CNTR_ERRM` field @def USB_CNTR_ERRM_Msk */
#define USB_CNTR_ERRM_Msk			REG_BIT_MASK(USB_CNTR_ERRM_Pos)
/** @brief Error Interrupt Mask @def USB_CNTR_ERRM */
#define USB_CNTR_ERRM				USB_CNTR_ERRM_Msk
/** @brief Bit position of the `USB_CNTR_PMAOVRM` field @def USB_CNTR_PMAOVRM_Pos */
#define USB_CNTR_PMAOVRM_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USB_CNTR_PMAOVRM` field @def USB_CNTR_PMAOVRM_Msk */
#define USB_CNTR_PMAOVRM_Msk		REG_BIT_MASK(USB_CNTR_PMAOVRM_Pos)
/** @brief Packet Memory Area Over / Underrun Interrupt Mask @def USB_CNTR_PMAOVRM */
#define USB_CNTR_PMAOVRM			USB_CNTR_PMAOVRM_Msk
/** @brief Bit position of the `USB_CNTR_CTRM` field @def USB_CNTR_CTRM_Pos */
#define USB_CNTR_CTRM_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_CNTR_CTRM` field @def USB_CNTR_CTRM_Msk */
#define USB_CNTR_CTRM_Msk			REG_BIT_MASK(USB_CNTR_CTRM_Pos)
/** @brief Correct Transfer Interrupt Mask @def USB_CNTR_CTRM */
#define USB_CNTR_CTRM				USB_CNTR_CTRM_Msk

// ---------------------------------- USB_ISTR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USB_ISTR_EP_ID` field @def USB_ISTR_EP_ID_Pos */
#define USB_ISTR_EP_ID_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_ISTR_EP_ID` field @def USB_ISTR_EP_ID_Width */
#define USB_ISTR_EP_ID_Width		((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `USB_ISTR_EP_ID` field @def USB_ISTR_EP_ID_Msk */
#define USB_ISTR_EP_ID_Msk			REG_FIELD_MASK(USB_ISTR_EP_ID_Pos, USB_ISTR_EP_ID_Width)
/** @brief Endpoint Identifier @def USB_ISTR_EP_ID */
#define USB_ISTR_EP_ID				USB_ISTR_EP_ID_Msk
/** @brief Bit position of the `USB_ISTR_DIR` field @def USB_ISTR_DIR_Pos */
#define USB_ISTR_DIR_Pos			((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `USB_ISTR_DIR` field @def USB_ISTR_DIR_Msk */
#define USB_ISTR_DIR_Msk			REG_BIT_MASK(USB_ISTR_DIR_Pos)
/** @brief Direction of transaction @def USB_ISTR_DIR */
#define USB_ISTR_DIR				USB_ISTR_DIR_Msk
/** @brief Bit position of the `USB_ISTR_ESOF` field @def USB_ISTR_ESOF_Pos */
#define USB_ISTR_ESOF_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USB_ISTR_ESOF` field @def USB_ISTR_ESOF_Msk */
#define USB_ISTR_ESOF_Msk			REG_BIT_MASK(USB_ISTR_ESOF_Pos)
/** @brief Expected Start Of Frame @def USB_ISTR_ESOF */
#define USB_ISTR_ESOF				USB_ISTR_ESOF_Msk
/** @brief Bit position of the `USB_ISTR_SOF` field @def USB_ISTR_SOF_Pos */
#define USB_ISTR_SOF_Pos			((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `USB_ISTR_SOF` field @def USB_ISTR_SOF_Msk */
#define USB_ISTR_SOF_Msk			REG_BIT_MASK(USB_ISTR_SOF_Pos)
/** @brief Start Of Frame @def USB_ISTR_SOF */
#define USB_ISTR_SOF				USB_ISTR_SOF_Msk
/** @brief Bit position of the `USB_ISTR_RESET` field @def USB_ISTR_RESET_Pos */
#define USB_ISTR_RESET_Pos			((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `USB_ISTR_RESET` field @def USB_ISTR_RESET_Msk */
#define USB_ISTR_RESET_Msk			REG_BIT_MASK(USB_ISTR_RESET_Pos)
/** @brief USB RESET request @def USB_ISTR_RESET */
#define USB_ISTR_RESET				USB_ISTR_RESET_Msk
/** @brief Bit position of the `USB_ISTR_SUSP` field @def USB_ISTR_SUSP_Pos */
#define USB_ISTR_SUSP_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USB_ISTR_SUSP` field @def USB_ISTR_SUSP_Msk */
#define USB_ISTR_SUSP_Msk			REG_BIT_MASK(USB_ISTR_SUSP_Pos)
/** @brief Suspend mode request @def USB_ISTR_SUSP */
#define USB_ISTR_SUSP				USB_ISTR_SUSP_Msk
/** @brief Bit position of the `USB_ISTR_WKUP` field @def USB_ISTR_WKUP_Pos */
#define USB_ISTR_WKUP_Pos			((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `USB_ISTR_WKUP` field @def USB_ISTR_WKUP_Msk */
#define USB_ISTR_WKUP_Msk			REG_BIT_MASK(USB_ISTR_WKUP_Pos)
/** @brief Wake up @def USB_ISTR_WKUP */
#define USB_ISTR_WKUP				USB_ISTR_WKUP_Msk
/** @brief Bit position of the `USB_ISTR_ERR` field @def USB_ISTR_ERR_Pos */
#define USB_ISTR_ERR_Pos			((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `USB_ISTR_ERR` field @def USB_ISTR_ERR_Msk */
#define USB_ISTR_ERR_Msk			REG_BIT_MASK(USB_ISTR_ERR_Pos)
/** @brief Error @def USB_ISTR_ERR */
#define USB_ISTR_ERR				USB_ISTR_ERR_Msk
/** @brief Bit position of the `USB_ISTR_PMAOVR` field @def USB_ISTR_PMAOVR_Pos */
#define USB_ISTR_PMAOVR_Pos			((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USB_ISTR_PMAOVR` field @def USB_ISTR_PMAOVR_Msk */
#define USB_ISTR_PMAOVR_Msk			REG_BIT_MASK(USB_ISTR_PMAOVR_Pos)
/** @brief Packet Memory Area Over / Underrun @def USB_ISTR_PMAOVR */
#define USB_ISTR_PMAOVR				USB_ISTR_PMAOVR_Msk
/** @brief Bit position of the `USB_ISTR_CTR` field @def USB_ISTR_CTR_Pos */
#define USB_ISTR_CTR_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_ISTR_CTR` field @def USB_ISTR_CTR_Msk */
#define USB_ISTR_CTR_Msk			REG_BIT_MASK(USB_ISTR_CTR_Pos)
/** @brief Correct Transfer @def USB_ISTR_CTR */
#define USB_ISTR_CTR				USB_ISTR_CTR_Msk

// ----------------------------------- USB_FNR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USB_FNR_FN` field @def USB_FNR_FN_Pos */
#define USB_FNR_FN_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_FNR_FN` field @def USB_FNR_FN_Width */
#define USB_FNR_FN_Width		((reg_field_width_t) 11U)
/** @brief Register-positioned mask for the `USB_FNR_FN` field @def USB_FNR_FN_Msk */
#define USB_FNR_FN_Msk			REG_FIELD_MASK(USB_FNR_FN_Pos, USB_FNR_FN_Width)
/** @brief Frame Number @def USB_FNR_FN */
#define USB_FNR_FN				USB_FNR_FN_Msk
/** @brief Bit position of the `USB_FNR_LSOF` field @def USB_FNR_LSOF_Pos */
#define USB_FNR_LSOF_Pos		((reg_bit_pos_t) 11U)
/** @brief Width of the `USB_FNR_LSOF` field @def USB_FNR_LSOF_Width */
#define USB_FNR_LSOF_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USB_FNR_LSOF` field @def USB_FNR_LSOF_Msk */
#define USB_FNR_LSOF_Msk		REG_FIELD_MASK(USB_FNR_LSOF_Pos, USB_FNR_LSOF_Width)
/** @brief Lost SOF @def USB_FNR_LSOF */
#define USB_FNR_LSOF			USB_FNR_LSOF_Msk
/** @brief Bit position of the `USB_FNR_LCK` field @def USB_FNR_LCK_Pos */
#define USB_FNR_LCK_Pos			((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `USB_FNR_LCK` field @def USB_FNR_LCK_Msk */
#define USB_FNR_LCK_Msk			REG_BIT_MASK(USB_FNR_LCK_Pos)
/** @brief Locked @def USB_FNR_LCK */
#define USB_FNR_LCK				USB_FNR_LCK_Msk
/** @brief Bit position of the `USB_FNR_RXDM` field @def USB_FNR_RXDM_Pos */
#define USB_FNR_RXDM_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USB_FNR_RXDM` field @def USB_FNR_RXDM_Msk */
#define USB_FNR_RXDM_Msk		REG_BIT_MASK(USB_FNR_RXDM_Pos)
/** @brief Receive Data - Line Status @def USB_FNR_RXDM */
#define USB_FNR_RXDM			USB_FNR_RXDM_Msk
/** @brief Bit position of the `USB_FNR_RXDP` field @def USB_FNR_RXDP_Pos */
#define USB_FNR_RXDP_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_FNR_RXDP` field @def USB_FNR_RXDP_Msk */
#define USB_FNR_RXDP_Msk		REG_BIT_MASK(USB_FNR_RXDP_Pos)
/** @brief Receive Data + Line Status @def USB_FNR_RXDP */
#define USB_FNR_RXDP			USB_FNR_RXDP_Msk

// ---------------------------------- USB_DADDR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `USB_DADDR_ADD` field @def USB_DADDR_ADD_Pos */
#define USB_DADDR_ADD_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_DADDR_ADD` field @def USB_DADDR_ADD_Width */
#define USB_DADDR_ADD_Width		((reg_field_width_t) 7U)
/** @brief Register-positioned mask for the `USB_DADDR_ADD` field @def USB_DADDR_ADD_Msk */
#define USB_DADDR_ADD_Msk		REG_FIELD_MASK(USB_DADDR_ADD_Pos, USB_DADDR_ADD_Width)
/** @brief ADD[6:0] bits (Device Address) @def USB_DADDR_ADD */
#define USB_DADDR_ADD			USB_DADDR_ADD_Msk
/** @brief Bit position of the `USB_DADDR_ADD0` field @def USB_DADDR_ADD0_Pos */
#define USB_DADDR_ADD0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `USB_DADDR_ADD0` field @def USB_DADDR_ADD0_Msk */
#define USB_DADDR_ADD0_Msk		REG_BIT_MASK(USB_DADDR_ADD0_Pos)
/** @brief Bit 0 @def USB_DADDR_ADD0 */
#define USB_DADDR_ADD0			USB_DADDR_ADD0_Msk
/** @brief Bit position of the `USB_DADDR_ADD1` field @def USB_DADDR_ADD1_Pos */
#define USB_DADDR_ADD1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `USB_DADDR_ADD1` field @def USB_DADDR_ADD1_Msk */
#define USB_DADDR_ADD1_Msk		REG_BIT_MASK(USB_DADDR_ADD1_Pos)
/** @brief Bit 1 @def USB_DADDR_ADD1 */
#define USB_DADDR_ADD1			USB_DADDR_ADD1_Msk
/** @brief Bit position of the `USB_DADDR_ADD2` field @def USB_DADDR_ADD2_Pos */
#define USB_DADDR_ADD2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `USB_DADDR_ADD2` field @def USB_DADDR_ADD2_Msk */
#define USB_DADDR_ADD2_Msk		REG_BIT_MASK(USB_DADDR_ADD2_Pos)
/** @brief Bit 2 @def USB_DADDR_ADD2 */
#define USB_DADDR_ADD2			USB_DADDR_ADD2_Msk
/** @brief Bit position of the `USB_DADDR_ADD3` field @def USB_DADDR_ADD3_Pos */
#define USB_DADDR_ADD3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `USB_DADDR_ADD3` field @def USB_DADDR_ADD3_Msk */
#define USB_DADDR_ADD3_Msk		REG_BIT_MASK(USB_DADDR_ADD3_Pos)
/** @brief Bit 3 @def USB_DADDR_ADD3 */
#define USB_DADDR_ADD3			USB_DADDR_ADD3_Msk
/** @brief Bit position of the `USB_DADDR_ADD4` field @def USB_DADDR_ADD4_Pos */
#define USB_DADDR_ADD4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `USB_DADDR_ADD4` field @def USB_DADDR_ADD4_Msk */
#define USB_DADDR_ADD4_Msk		REG_BIT_MASK(USB_DADDR_ADD4_Pos)
/** @brief Bit 4 @def USB_DADDR_ADD4 */
#define USB_DADDR_ADD4			USB_DADDR_ADD4_Msk
/** @brief Bit position of the `USB_DADDR_ADD5` field @def USB_DADDR_ADD5_Pos */
#define USB_DADDR_ADD5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `USB_DADDR_ADD5` field @def USB_DADDR_ADD5_Msk */
#define USB_DADDR_ADD5_Msk		REG_BIT_MASK(USB_DADDR_ADD5_Pos)
/** @brief Bit 5 @def USB_DADDR_ADD5 */
#define USB_DADDR_ADD5			USB_DADDR_ADD5_Msk
/** @brief Bit position of the `USB_DADDR_ADD6` field @def USB_DADDR_ADD6_Pos */
#define USB_DADDR_ADD6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USB_DADDR_ADD6` field @def USB_DADDR_ADD6_Msk */
#define USB_DADDR_ADD6_Msk		REG_BIT_MASK(USB_DADDR_ADD6_Pos)
/** @brief Bit 6 @def USB_DADDR_ADD6 */
#define USB_DADDR_ADD6			USB_DADDR_ADD6_Msk

/** @brief Bit position of the `USB_DADDR_EF` field @def USB_DADDR_EF_Pos */
#define USB_DADDR_EF_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USB_DADDR_EF` field @def USB_DADDR_EF_Msk */
#define USB_DADDR_EF_Msk		REG_BIT_MASK(USB_DADDR_EF_Pos)
/** @brief Enable Function @def USB_DADDR_EF */
#define USB_DADDR_EF			USB_DADDR_EF_Msk

// --------------------------------- USB_BTABLE Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `USB_BTABLE_BTABLE` field @def USB_BTABLE_BTABLE_Pos */
#define USB_BTABLE_BTABLE_Pos		((reg_bit_pos_t) 3U)
/** @brief Width of the `USB_BTABLE_BTABLE` field @def USB_BTABLE_BTABLE_Width */
#define USB_BTABLE_BTABLE_Width		((reg_field_width_t) 13U)
/** @brief Register-positioned mask for the `USB_BTABLE_BTABLE` field @def USB_BTABLE_BTABLE_Msk */
#define USB_BTABLE_BTABLE_Msk		REG_FIELD_MASK(USB_BTABLE_BTABLE_Pos, USB_BTABLE_BTABLE_Width)
/** @brief Buffer Table @def USB_BTABLE_BTABLE */
#define USB_BTABLE_BTABLE			USB_BTABLE_BTABLE_Msk

// ------------------------------- USB Buffer Descriptor Table Defines -------------------------------- //
// -------------------------------- USB_ADDR0_TX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR0_TX_ADDR0_TX` field @def USB_ADDR0_TX_ADDR0_TX_Pos */
#define USB_ADDR0_TX_ADDR0_TX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR0_TX_ADDR0_TX` field @def USB_ADDR0_TX_ADDR0_TX_Width */
#define USB_ADDR0_TX_ADDR0_TX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR0_TX_ADDR0_TX` field @def USB_ADDR0_TX_ADDR0_TX_Msk */
#define USB_ADDR0_TX_ADDR0_TX_Msk		REG_FIELD_MASK(USB_ADDR0_TX_ADDR0_TX_Pos, USB_ADDR0_TX_ADDR0_TX_Width)
/** @brief Transmission Buffer Address 0 @def USB_ADDR0_TX_ADDR0_TX */
#define USB_ADDR0_TX_ADDR0_TX			USB_ADDR0_TX_ADDR0_TX_Msk

// -------------------------------- USB_ADDR1_TX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR1_TX_ADDR1_TX` field @def USB_ADDR1_TX_ADDR1_TX_Pos */
#define USB_ADDR1_TX_ADDR1_TX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR1_TX_ADDR1_TX` field @def USB_ADDR1_TX_ADDR1_TX_Width */
#define USB_ADDR1_TX_ADDR1_TX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR1_TX_ADDR1_TX` field @def USB_ADDR1_TX_ADDR1_TX_Msk */
#define USB_ADDR1_TX_ADDR1_TX_Msk		REG_FIELD_MASK(USB_ADDR1_TX_ADDR1_TX_Pos, USB_ADDR1_TX_ADDR1_TX_Width)
/** @brief Transmission Buffer Address 1 @def USB_ADDR1_TX_ADDR1_TX */
#define USB_ADDR1_TX_ADDR1_TX			USB_ADDR1_TX_ADDR1_TX_Msk

// -------------------------------- USB_ADDR2_TX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR2_TX_ADDR2_TX` field @def USB_ADDR2_TX_ADDR2_TX_Pos */
#define USB_ADDR2_TX_ADDR2_TX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR2_TX_ADDR2_TX` field @def USB_ADDR2_TX_ADDR2_TX_Width */
#define USB_ADDR2_TX_ADDR2_TX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR2_TX_ADDR2_TX` field @def USB_ADDR2_TX_ADDR2_TX_Msk */
#define USB_ADDR2_TX_ADDR2_TX_Msk		REG_FIELD_MASK(USB_ADDR2_TX_ADDR2_TX_Pos, USB_ADDR2_TX_ADDR2_TX_Width)
/** @brief Transmission Buffer Address 2 @def USB_ADDR2_TX_ADDR2_TX */
#define USB_ADDR2_TX_ADDR2_TX			USB_ADDR2_TX_ADDR2_TX_Msk

// -------------------------------- USB_ADDR3_TX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR3_TX_ADDR3_TX` field @def USB_ADDR3_TX_ADDR3_TX_Pos */
#define USB_ADDR3_TX_ADDR3_TX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR3_TX_ADDR3_TX` field @def USB_ADDR3_TX_ADDR3_TX_Width */
#define USB_ADDR3_TX_ADDR3_TX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR3_TX_ADDR3_TX` field @def USB_ADDR3_TX_ADDR3_TX_Msk */
#define USB_ADDR3_TX_ADDR3_TX_Msk		REG_FIELD_MASK(USB_ADDR3_TX_ADDR3_TX_Pos, USB_ADDR3_TX_ADDR3_TX_Width)
/** @brief Transmission Buffer Address 3 @def USB_ADDR3_TX_ADDR3_TX */
#define USB_ADDR3_TX_ADDR3_TX			USB_ADDR3_TX_ADDR3_TX_Msk

// -------------------------------- USB_ADDR4_TX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR4_TX_ADDR4_TX` field @def USB_ADDR4_TX_ADDR4_TX_Pos */
#define USB_ADDR4_TX_ADDR4_TX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR4_TX_ADDR4_TX` field @def USB_ADDR4_TX_ADDR4_TX_Width */
#define USB_ADDR4_TX_ADDR4_TX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR4_TX_ADDR4_TX` field @def USB_ADDR4_TX_ADDR4_TX_Msk */
#define USB_ADDR4_TX_ADDR4_TX_Msk		REG_FIELD_MASK(USB_ADDR4_TX_ADDR4_TX_Pos, USB_ADDR4_TX_ADDR4_TX_Width)
/** @brief Transmission Buffer Address 4 @def USB_ADDR4_TX_ADDR4_TX */
#define USB_ADDR4_TX_ADDR4_TX			USB_ADDR4_TX_ADDR4_TX_Msk

// -------------------------------- USB_ADDR5_TX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR5_TX_ADDR5_TX` field @def USB_ADDR5_TX_ADDR5_TX_Pos */
#define USB_ADDR5_TX_ADDR5_TX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR5_TX_ADDR5_TX` field @def USB_ADDR5_TX_ADDR5_TX_Width */
#define USB_ADDR5_TX_ADDR5_TX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR5_TX_ADDR5_TX` field @def USB_ADDR5_TX_ADDR5_TX_Msk */
#define USB_ADDR5_TX_ADDR5_TX_Msk		REG_FIELD_MASK(USB_ADDR5_TX_ADDR5_TX_Pos, USB_ADDR5_TX_ADDR5_TX_Width)
/** @brief Transmission Buffer Address 5 @def USB_ADDR5_TX_ADDR5_TX */
#define USB_ADDR5_TX_ADDR5_TX			USB_ADDR5_TX_ADDR5_TX_Msk

// -------------------------------- USB_ADDR6_TX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR6_TX_ADDR6_TX` field @def USB_ADDR6_TX_ADDR6_TX_Pos */
#define USB_ADDR6_TX_ADDR6_TX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR6_TX_ADDR6_TX` field @def USB_ADDR6_TX_ADDR6_TX_Width */
#define USB_ADDR6_TX_ADDR6_TX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR6_TX_ADDR6_TX` field @def USB_ADDR6_TX_ADDR6_TX_Msk */
#define USB_ADDR6_TX_ADDR6_TX_Msk		REG_FIELD_MASK(USB_ADDR6_TX_ADDR6_TX_Pos, USB_ADDR6_TX_ADDR6_TX_Width)
/** @brief Transmission Buffer Address 6 @def USB_ADDR6_TX_ADDR6_TX */
#define USB_ADDR6_TX_ADDR6_TX			USB_ADDR6_TX_ADDR6_TX_Msk

// -------------------------------- USB_ADDR7_TX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR7_TX_ADDR7_TX` field @def USB_ADDR7_TX_ADDR7_TX_Pos */
#define USB_ADDR7_TX_ADDR7_TX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR7_TX_ADDR7_TX` field @def USB_ADDR7_TX_ADDR7_TX_Width */
#define USB_ADDR7_TX_ADDR7_TX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR7_TX_ADDR7_TX` field @def USB_ADDR7_TX_ADDR7_TX_Msk */
#define USB_ADDR7_TX_ADDR7_TX_Msk		REG_FIELD_MASK(USB_ADDR7_TX_ADDR7_TX_Pos, USB_ADDR7_TX_ADDR7_TX_Width)
/** @brief Transmission Buffer Address 7 @def USB_ADDR7_TX_ADDR7_TX */
#define USB_ADDR7_TX_ADDR7_TX			USB_ADDR7_TX_ADDR7_TX_Msk

// ----------------------------- USB Transmission Count Register Defines ------------------------------ //

// -------------------------------- USB_COUNT0_TX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT0_TX_COUNT0_TX` field @def USB_COUNT0_TX_COUNT0_TX_Pos */
#define USB_COUNT0_TX_COUNT0_TX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT0_TX_COUNT0_TX` field @def USB_COUNT0_TX_COUNT0_TX_Width */
#define USB_COUNT0_TX_COUNT0_TX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT0_TX_COUNT0_TX` field @def USB_COUNT0_TX_COUNT0_TX_Msk */
#define USB_COUNT0_TX_COUNT0_TX_Msk			REG_FIELD_MASK(USB_COUNT0_TX_COUNT0_TX_Pos, USB_COUNT0_TX_COUNT0_TX_Width)
/** @brief Transmission Byte Count 0 @def USB_COUNT0_TX_COUNT0_TX */
#define USB_COUNT0_TX_COUNT0_TX				USB_COUNT0_TX_COUNT0_TX_Msk

// -------------------------------- USB_COUNT1_TX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT1_TX_COUNT1_TX` field @def USB_COUNT1_TX_COUNT1_TX_Pos */
#define USB_COUNT1_TX_COUNT1_TX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT1_TX_COUNT1_TX` field @def USB_COUNT1_TX_COUNT1_TX_Width */
#define USB_COUNT1_TX_COUNT1_TX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT1_TX_COUNT1_TX` field @def USB_COUNT1_TX_COUNT1_TX_Msk */
#define USB_COUNT1_TX_COUNT1_TX_Msk			REG_FIELD_MASK(USB_COUNT1_TX_COUNT1_TX_Pos, USB_COUNT1_TX_COUNT1_TX_Width)
/** @brief Transmission Byte Count 1 @def USB_COUNT1_TX_COUNT1_TX */
#define USB_COUNT1_TX_COUNT1_TX				USB_COUNT1_TX_COUNT1_TX_Msk

// -------------------------------- USB_COUNT2_TX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT2_TX_COUNT2_TX` field @def USB_COUNT2_TX_COUNT2_TX_Pos */
#define USB_COUNT2_TX_COUNT2_TX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT2_TX_COUNT2_TX` field @def USB_COUNT2_TX_COUNT2_TX_Width */
#define USB_COUNT2_TX_COUNT2_TX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT2_TX_COUNT2_TX` field @def USB_COUNT2_TX_COUNT2_TX_Msk */
#define USB_COUNT2_TX_COUNT2_TX_Msk			REG_FIELD_MASK(USB_COUNT2_TX_COUNT2_TX_Pos, USB_COUNT2_TX_COUNT2_TX_Width)
/** @brief Transmission Byte Count 2 @def USB_COUNT2_TX_COUNT2_TX */
#define USB_COUNT2_TX_COUNT2_TX				USB_COUNT2_TX_COUNT2_TX_Msk

// -------------------------------- USB_COUNT3_TX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT3_TX_COUNT3_TX` field @def USB_COUNT3_TX_COUNT3_TX_Pos */
#define USB_COUNT3_TX_COUNT3_TX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT3_TX_COUNT3_TX` field @def USB_COUNT3_TX_COUNT3_TX_Width */
#define USB_COUNT3_TX_COUNT3_TX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT3_TX_COUNT3_TX` field @def USB_COUNT3_TX_COUNT3_TX_Msk */
#define USB_COUNT3_TX_COUNT3_TX_Msk			REG_FIELD_MASK(USB_COUNT3_TX_COUNT3_TX_Pos, USB_COUNT3_TX_COUNT3_TX_Width)
/** @brief Transmission Byte Count 3 @def USB_COUNT3_TX_COUNT3_TX */
#define USB_COUNT3_TX_COUNT3_TX				USB_COUNT3_TX_COUNT3_TX_Msk

// -------------------------------- USB_COUNT4_TX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT4_TX_COUNT4_TX` field @def USB_COUNT4_TX_COUNT4_TX_Pos */
#define USB_COUNT4_TX_COUNT4_TX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT4_TX_COUNT4_TX` field @def USB_COUNT4_TX_COUNT4_TX_Width */
#define USB_COUNT4_TX_COUNT4_TX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT4_TX_COUNT4_TX` field @def USB_COUNT4_TX_COUNT4_TX_Msk */
#define USB_COUNT4_TX_COUNT4_TX_Msk			REG_FIELD_MASK(USB_COUNT4_TX_COUNT4_TX_Pos, USB_COUNT4_TX_COUNT4_TX_Width)
/** @brief Transmission Byte Count 4 @def USB_COUNT4_TX_COUNT4_TX */
#define USB_COUNT4_TX_COUNT4_TX				USB_COUNT4_TX_COUNT4_TX_Msk

// -------------------------------- USB_COUNT5_TX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT5_TX_COUNT5_TX` field @def USB_COUNT5_TX_COUNT5_TX_Pos */
#define USB_COUNT5_TX_COUNT5_TX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT5_TX_COUNT5_TX` field @def USB_COUNT5_TX_COUNT5_TX_Width */
#define USB_COUNT5_TX_COUNT5_TX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT5_TX_COUNT5_TX` field @def USB_COUNT5_TX_COUNT5_TX_Msk */
#define USB_COUNT5_TX_COUNT5_TX_Msk			REG_FIELD_MASK(USB_COUNT5_TX_COUNT5_TX_Pos, USB_COUNT5_TX_COUNT5_TX_Width)
/** @brief Transmission Byte Count 5 @def USB_COUNT5_TX_COUNT5_TX */
#define USB_COUNT5_TX_COUNT5_TX				USB_COUNT5_TX_COUNT5_TX_Msk

// -------------------------------- USB_COUNT6_TX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT6_TX_COUNT6_TX` field @def USB_COUNT6_TX_COUNT6_TX_Pos */
#define USB_COUNT6_TX_COUNT6_TX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT6_TX_COUNT6_TX` field @def USB_COUNT6_TX_COUNT6_TX_Width */
#define USB_COUNT6_TX_COUNT6_TX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT6_TX_COUNT6_TX` field @def USB_COUNT6_TX_COUNT6_TX_Msk */
#define USB_COUNT6_TX_COUNT6_TX_Msk			REG_FIELD_MASK(USB_COUNT6_TX_COUNT6_TX_Pos, USB_COUNT6_TX_COUNT6_TX_Width)
/** @brief Transmission Byte Count 6 @def USB_COUNT6_TX_COUNT6_TX */
#define USB_COUNT6_TX_COUNT6_TX				USB_COUNT6_TX_COUNT6_TX_Msk

// -------------------------------- USB_COUNT7_TX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT7_TX_COUNT7_TX` field @def USB_COUNT7_TX_COUNT7_TX_Pos */
#define USB_COUNT7_TX_COUNT7_TX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT7_TX_COUNT7_TX` field @def USB_COUNT7_TX_COUNT7_TX_Width */
#define USB_COUNT7_TX_COUNT7_TX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT7_TX_COUNT7_TX` field @def USB_COUNT7_TX_COUNT7_TX_Msk */
#define USB_COUNT7_TX_COUNT7_TX_Msk			REG_FIELD_MASK(USB_COUNT7_TX_COUNT7_TX_Pos, USB_COUNT7_TX_COUNT7_TX_Width)
/** @brief Transmission Byte Count 7 @def USB_COUNT7_TX_COUNT7_TX */
#define USB_COUNT7_TX_COUNT7_TX				USB_COUNT7_TX_COUNT7_TX_Msk

// -------------------------- USB Packed Transmission Count Register Defines -------------------------- //

// ------------------------------- USB_COUNT0_TX_0 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 0 (low) @def USB_COUNT0_TX_0_COUNT0_TX_0 */
#define USB_COUNT0_TX_0_COUNT0_TX_0		0x000003FFU

// ------------------------------- USB_COUNT0_TX_1 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 0 (high) @def USB_COUNT0_TX_1_COUNT0_TX_1 */
#define USB_COUNT0_TX_1_COUNT0_TX_1		0x03FF0000U

// ------------------------------- USB_COUNT1_TX_0 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 1 (low) @def USB_COUNT1_TX_0_COUNT1_TX_0 */
#define USB_COUNT1_TX_0_COUNT1_TX_0		0x000003FFU

// ------------------------------- USB_COUNT1_TX_1 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 1 (high) @def USB_COUNT1_TX_1_COUNT1_TX_1 */
#define USB_COUNT1_TX_1_COUNT1_TX_1		0x03FF0000U

// ------------------------------- USB_COUNT2_TX_0 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 2 (low) @def USB_COUNT2_TX_0_COUNT2_TX_0 */
#define USB_COUNT2_TX_0_COUNT2_TX_0		0x000003FFU

// ------------------------------- USB_COUNT2_TX_1 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 2 (high) @def USB_COUNT2_TX_1_COUNT2_TX_1 */
#define USB_COUNT2_TX_1_COUNT2_TX_1		0x03FF0000U

// ------------------------------- USB_COUNT3_TX_0 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 3 (low) @def USB_COUNT3_TX_0_COUNT3_TX_0 */
#define USB_COUNT3_TX_0_COUNT3_TX_0		0x000003FFU

// ------------------------------- USB_COUNT3_TX_1 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 3 (high) @def USB_COUNT3_TX_1_COUNT3_TX_1 */
#define USB_COUNT3_TX_1_COUNT3_TX_1		0x03FF0000U

// ------------------------------- USB_COUNT4_TX_0 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 4 (low) @def USB_COUNT4_TX_0_COUNT4_TX_0 */
#define USB_COUNT4_TX_0_COUNT4_TX_0		0x000003FFU

// ------------------------------- USB_COUNT4_TX_1 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 4 (high) @def USB_COUNT4_TX_1_COUNT4_TX_1 */
#define USB_COUNT4_TX_1_COUNT4_TX_1		0x03FF0000U

// ------------------------------- USB_COUNT5_TX_0 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 5 (low) @def USB_COUNT5_TX_0_COUNT5_TX_0 */
#define USB_COUNT5_TX_0_COUNT5_TX_0		0x000003FFU

// ------------------------------- USB_COUNT5_TX_1 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 5 (high) @def USB_COUNT5_TX_1_COUNT5_TX_1 */
#define USB_COUNT5_TX_1_COUNT5_TX_1		0x03FF0000U

// ------------------------------- USB_COUNT6_TX_0 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 6 (low) @def USB_COUNT6_TX_0_COUNT6_TX_0 */
#define USB_COUNT6_TX_0_COUNT6_TX_0		0x000003FFU

// ------------------------------- USB_COUNT6_TX_1 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 6 (high) @def USB_COUNT6_TX_1_COUNT6_TX_1 */
#define USB_COUNT6_TX_1_COUNT6_TX_1		0x03FF0000U

// ------------------------------- USB_COUNT7_TX_0 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 7 (low) @def USB_COUNT7_TX_0_COUNT7_TX_0 */
#define USB_COUNT7_TX_0_COUNT7_TX_0		0x000003FFU

// ------------------------------- USB_COUNT7_TX_1 Register Bit Defines ------------------------------- //
/** @brief Transmission Byte Count 7 (high) @def USB_COUNT7_TX_1_COUNT7_TX_1 */
#define USB_COUNT7_TX_1_COUNT7_TX_1		0x03FF0000U

// ------------------------------ USB Reception Address Register Defines ------------------------------ //

// -------------------------------- USB_ADDR0_RX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR0_RX_ADDR0_RX` field @def USB_ADDR0_RX_ADDR0_RX_Pos */
#define USB_ADDR0_RX_ADDR0_RX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR0_RX_ADDR0_RX` field @def USB_ADDR0_RX_ADDR0_RX_Width */
#define USB_ADDR0_RX_ADDR0_RX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR0_RX_ADDR0_RX` field @def USB_ADDR0_RX_ADDR0_RX_Msk */
#define USB_ADDR0_RX_ADDR0_RX_Msk		REG_FIELD_MASK(USB_ADDR0_RX_ADDR0_RX_Pos, USB_ADDR0_RX_ADDR0_RX_Width)
/** @brief Reception Buffer Address 0 @def USB_ADDR0_RX_ADDR0_RX */
#define USB_ADDR0_RX_ADDR0_RX			USB_ADDR0_RX_ADDR0_RX_Msk

// -------------------------------- USB_ADDR1_RX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR1_RX_ADDR1_RX` field @def USB_ADDR1_RX_ADDR1_RX_Pos */
#define USB_ADDR1_RX_ADDR1_RX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR1_RX_ADDR1_RX` field @def USB_ADDR1_RX_ADDR1_RX_Width */
#define USB_ADDR1_RX_ADDR1_RX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR1_RX_ADDR1_RX` field @def USB_ADDR1_RX_ADDR1_RX_Msk */
#define USB_ADDR1_RX_ADDR1_RX_Msk		REG_FIELD_MASK(USB_ADDR1_RX_ADDR1_RX_Pos, USB_ADDR1_RX_ADDR1_RX_Width)
/** @brief Reception Buffer Address 1 @def USB_ADDR1_RX_ADDR1_RX */
#define USB_ADDR1_RX_ADDR1_RX			USB_ADDR1_RX_ADDR1_RX_Msk

// -------------------------------- USB_ADDR2_RX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR2_RX_ADDR2_RX` field @def USB_ADDR2_RX_ADDR2_RX_Pos */
#define USB_ADDR2_RX_ADDR2_RX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR2_RX_ADDR2_RX` field @def USB_ADDR2_RX_ADDR2_RX_Width */
#define USB_ADDR2_RX_ADDR2_RX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR2_RX_ADDR2_RX` field @def USB_ADDR2_RX_ADDR2_RX_Msk */
#define USB_ADDR2_RX_ADDR2_RX_Msk		REG_FIELD_MASK(USB_ADDR2_RX_ADDR2_RX_Pos, USB_ADDR2_RX_ADDR2_RX_Width)
/** @brief Reception Buffer Address 2 @def USB_ADDR2_RX_ADDR2_RX */
#define USB_ADDR2_RX_ADDR2_RX			USB_ADDR2_RX_ADDR2_RX_Msk

// -------------------------------- USB_ADDR3_RX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR3_RX_ADDR3_RX` field @def USB_ADDR3_RX_ADDR3_RX_Pos */
#define USB_ADDR3_RX_ADDR3_RX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR3_RX_ADDR3_RX` field @def USB_ADDR3_RX_ADDR3_RX_Width */
#define USB_ADDR3_RX_ADDR3_RX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR3_RX_ADDR3_RX` field @def USB_ADDR3_RX_ADDR3_RX_Msk */
#define USB_ADDR3_RX_ADDR3_RX_Msk		REG_FIELD_MASK(USB_ADDR3_RX_ADDR3_RX_Pos, USB_ADDR3_RX_ADDR3_RX_Width)
/** @brief Reception Buffer Address 3 @def USB_ADDR3_RX_ADDR3_RX */
#define USB_ADDR3_RX_ADDR3_RX			USB_ADDR3_RX_ADDR3_RX_Msk

// -------------------------------- USB_ADDR4_RX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR4_RX_ADDR4_RX` field @def USB_ADDR4_RX_ADDR4_RX_Pos */
#define USB_ADDR4_RX_ADDR4_RX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR4_RX_ADDR4_RX` field @def USB_ADDR4_RX_ADDR4_RX_Width */
#define USB_ADDR4_RX_ADDR4_RX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR4_RX_ADDR4_RX` field @def USB_ADDR4_RX_ADDR4_RX_Msk */
#define USB_ADDR4_RX_ADDR4_RX_Msk		REG_FIELD_MASK(USB_ADDR4_RX_ADDR4_RX_Pos, USB_ADDR4_RX_ADDR4_RX_Width)
/** @brief Reception Buffer Address 4 @def USB_ADDR4_RX_ADDR4_RX */
#define USB_ADDR4_RX_ADDR4_RX			USB_ADDR4_RX_ADDR4_RX_Msk

// -------------------------------- USB_ADDR5_RX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR5_RX_ADDR5_RX` field @def USB_ADDR5_RX_ADDR5_RX_Pos */
#define USB_ADDR5_RX_ADDR5_RX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR5_RX_ADDR5_RX` field @def USB_ADDR5_RX_ADDR5_RX_Width */
#define USB_ADDR5_RX_ADDR5_RX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR5_RX_ADDR5_RX` field @def USB_ADDR5_RX_ADDR5_RX_Msk */
#define USB_ADDR5_RX_ADDR5_RX_Msk		REG_FIELD_MASK(USB_ADDR5_RX_ADDR5_RX_Pos, USB_ADDR5_RX_ADDR5_RX_Width)
/** @brief Reception Buffer Address 5 @def USB_ADDR5_RX_ADDR5_RX */
#define USB_ADDR5_RX_ADDR5_RX			USB_ADDR5_RX_ADDR5_RX_Msk

// -------------------------------- USB_ADDR6_RX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR6_RX_ADDR6_RX` field @def USB_ADDR6_RX_ADDR6_RX_Pos */
#define USB_ADDR6_RX_ADDR6_RX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR6_RX_ADDR6_RX` field @def USB_ADDR6_RX_ADDR6_RX_Width */
#define USB_ADDR6_RX_ADDR6_RX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR6_RX_ADDR6_RX` field @def USB_ADDR6_RX_ADDR6_RX_Msk */
#define USB_ADDR6_RX_ADDR6_RX_Msk		REG_FIELD_MASK(USB_ADDR6_RX_ADDR6_RX_Pos, USB_ADDR6_RX_ADDR6_RX_Width)
/** @brief Reception Buffer Address 6 @def USB_ADDR6_RX_ADDR6_RX */
#define USB_ADDR6_RX_ADDR6_RX			USB_ADDR6_RX_ADDR6_RX_Msk

// -------------------------------- USB_ADDR7_RX Register Bit Defines --------------------------------- //
/** @brief Bit position of the `USB_ADDR7_RX_ADDR7_RX` field @def USB_ADDR7_RX_ADDR7_RX_Pos */
#define USB_ADDR7_RX_ADDR7_RX_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `USB_ADDR7_RX_ADDR7_RX` field @def USB_ADDR7_RX_ADDR7_RX_Width */
#define USB_ADDR7_RX_ADDR7_RX_Width		((reg_field_width_t) 15U)
/** @brief Register-positioned mask for the `USB_ADDR7_RX_ADDR7_RX` field @def USB_ADDR7_RX_ADDR7_RX_Msk */
#define USB_ADDR7_RX_ADDR7_RX_Msk		REG_FIELD_MASK(USB_ADDR7_RX_ADDR7_RX_Pos, USB_ADDR7_RX_ADDR7_RX_Width)
/** @brief Reception Buffer Address 7 @def USB_ADDR7_RX_ADDR7_RX */
#define USB_ADDR7_RX_ADDR7_RX			USB_ADDR7_RX_ADDR7_RX_Msk

// ------------------------------- USB Reception Count Register Defines ------------------------------- //

// -------------------------------- USB_COUNT0_RX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT0_RX_COUNT0_RX` field @def USB_COUNT0_RX_COUNT0_RX_Pos */
#define USB_COUNT0_RX_COUNT0_RX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT0_RX_COUNT0_RX` field @def USB_COUNT0_RX_COUNT0_RX_Width */
#define USB_COUNT0_RX_COUNT0_RX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT0_RX_COUNT0_RX` field @def USB_COUNT0_RX_COUNT0_RX_Msk */
#define USB_COUNT0_RX_COUNT0_RX_Msk			REG_FIELD_MASK(USB_COUNT0_RX_COUNT0_RX_Pos, USB_COUNT0_RX_COUNT0_RX_Width)
/** @brief Reception Byte Count @def USB_COUNT0_RX_COUNT0_RX */
#define USB_COUNT0_RX_COUNT0_RX				USB_COUNT0_RX_COUNT0_RX_Msk

/** @brief Bit position of the `USB_COUNT0_RX_NUM_BLOCK` field @def USB_COUNT0_RX_NUM_BLOCK_Pos */
#define USB_COUNT0_RX_NUM_BLOCK_Pos			((reg_bit_pos_t) 10U)
/** @brief Width of the `USB_COUNT0_RX_NUM_BLOCK` field @def USB_COUNT0_RX_NUM_BLOCK_Width */
#define USB_COUNT0_RX_NUM_BLOCK_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `USB_COUNT0_RX_NUM_BLOCK` field @def USB_COUNT0_RX_NUM_BLOCK_Msk */
#define USB_COUNT0_RX_NUM_BLOCK_Msk			REG_FIELD_MASK(USB_COUNT0_RX_NUM_BLOCK_Pos, USB_COUNT0_RX_NUM_BLOCK_Width)
/** @brief NUM_BLOCK[4:0] bits (Number of blocks) @def USB_COUNT0_RX_NUM_BLOCK */
#define USB_COUNT0_RX_NUM_BLOCK				USB_COUNT0_RX_NUM_BLOCK_Msk
/** @brief Register or selector value represented by `USB_COUNT0_RX_NUM_BLOCK_0` @def USB_COUNT0_RX_NUM_BLOCK_0 */
#define USB_COUNT0_RX_NUM_BLOCK_0			(0x01UL << USB_COUNT0_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT0_RX_NUM_BLOCK_1` @def USB_COUNT0_RX_NUM_BLOCK_1 */
#define USB_COUNT0_RX_NUM_BLOCK_1			(0x02UL << USB_COUNT0_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT0_RX_NUM_BLOCK_2` @def USB_COUNT0_RX_NUM_BLOCK_2 */
#define USB_COUNT0_RX_NUM_BLOCK_2			(0x04UL << USB_COUNT0_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT0_RX_NUM_BLOCK_3` @def USB_COUNT0_RX_NUM_BLOCK_3 */
#define USB_COUNT0_RX_NUM_BLOCK_3			(0x08UL << USB_COUNT0_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT0_RX_NUM_BLOCK_4` @def USB_COUNT0_RX_NUM_BLOCK_4 */
#define USB_COUNT0_RX_NUM_BLOCK_4			(0x10UL << USB_COUNT0_RX_NUM_BLOCK_Pos)

/** @brief Bit position of the `USB_COUNT0_RX_BLSIZE` field @def USB_COUNT0_RX_BLSIZE_Pos */
#define USB_COUNT0_RX_BLSIZE_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_COUNT0_RX_BLSIZE` field @def USB_COUNT0_RX_BLSIZE_Msk */
#define USB_COUNT0_RX_BLSIZE_Msk			REG_BIT_MASK(USB_COUNT0_RX_BLSIZE_Pos)
/** @brief BLock SIZE @def USB_COUNT0_RX_BLSIZE */
#define USB_COUNT0_RX_BLSIZE				USB_COUNT0_RX_BLSIZE_Msk

// -------------------------------- USB_COUNT1_RX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT1_RX_COUNT1_RX` field @def USB_COUNT1_RX_COUNT1_RX_Pos */
#define USB_COUNT1_RX_COUNT1_RX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT1_RX_COUNT1_RX` field @def USB_COUNT1_RX_COUNT1_RX_Width */
#define USB_COUNT1_RX_COUNT1_RX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT1_RX_COUNT1_RX` field @def USB_COUNT1_RX_COUNT1_RX_Msk */
#define USB_COUNT1_RX_COUNT1_RX_Msk			REG_FIELD_MASK(USB_COUNT1_RX_COUNT1_RX_Pos, USB_COUNT1_RX_COUNT1_RX_Width)
/** @brief Reception Byte Count @def USB_COUNT1_RX_COUNT1_RX */
#define USB_COUNT1_RX_COUNT1_RX				USB_COUNT1_RX_COUNT1_RX_Msk

/** @brief Bit position of the `USB_COUNT1_RX_NUM_BLOCK` field @def USB_COUNT1_RX_NUM_BLOCK_Pos */
#define USB_COUNT1_RX_NUM_BLOCK_Pos			((reg_bit_pos_t) 10U)
/** @brief Width of the `USB_COUNT1_RX_NUM_BLOCK` field @def USB_COUNT1_RX_NUM_BLOCK_Width */
#define USB_COUNT1_RX_NUM_BLOCK_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `USB_COUNT1_RX_NUM_BLOCK` field @def USB_COUNT1_RX_NUM_BLOCK_Msk */
#define USB_COUNT1_RX_NUM_BLOCK_Msk			REG_FIELD_MASK(USB_COUNT1_RX_NUM_BLOCK_Pos, USB_COUNT1_RX_NUM_BLOCK_Width)
/** @brief NUM_BLOCK[4:0] bits (Number of blocks) @def USB_COUNT1_RX_NUM_BLOCK */
#define USB_COUNT1_RX_NUM_BLOCK				USB_COUNT1_RX_NUM_BLOCK_Msk
/** @brief Register or selector value represented by `USB_COUNT1_RX_NUM_BLOCK_0` @def USB_COUNT1_RX_NUM_BLOCK_0 */
#define USB_COUNT1_RX_NUM_BLOCK_0			(0x01UL << USB_COUNT1_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT1_RX_NUM_BLOCK_1` @def USB_COUNT1_RX_NUM_BLOCK_1 */
#define USB_COUNT1_RX_NUM_BLOCK_1			(0x02UL << USB_COUNT1_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT1_RX_NUM_BLOCK_2` @def USB_COUNT1_RX_NUM_BLOCK_2 */
#define USB_COUNT1_RX_NUM_BLOCK_2			(0x04UL << USB_COUNT1_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT1_RX_NUM_BLOCK_3` @def USB_COUNT1_RX_NUM_BLOCK_3 */
#define USB_COUNT1_RX_NUM_BLOCK_3			(0x08UL << USB_COUNT1_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT1_RX_NUM_BLOCK_4` @def USB_COUNT1_RX_NUM_BLOCK_4 */
#define USB_COUNT1_RX_NUM_BLOCK_4			(0x10UL << USB_COUNT1_RX_NUM_BLOCK_Pos)

/** @brief Bit position of the `USB_COUNT1_RX_BLSIZE` field @def USB_COUNT1_RX_BLSIZE_Pos */
#define USB_COUNT1_RX_BLSIZE_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_COUNT1_RX_BLSIZE` field @def USB_COUNT1_RX_BLSIZE_Msk */
#define USB_COUNT1_RX_BLSIZE_Msk			REG_BIT_MASK(USB_COUNT1_RX_BLSIZE_Pos)
/** @brief BLock SIZE @def USB_COUNT1_RX_BLSIZE */
#define USB_COUNT1_RX_BLSIZE				USB_COUNT1_RX_BLSIZE_Msk

// -------------------------------- USB_COUNT2_RX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT2_RX_COUNT2_RX` field @def USB_COUNT2_RX_COUNT2_RX_Pos */
#define USB_COUNT2_RX_COUNT2_RX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT2_RX_COUNT2_RX` field @def USB_COUNT2_RX_COUNT2_RX_Width */
#define USB_COUNT2_RX_COUNT2_RX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT2_RX_COUNT2_RX` field @def USB_COUNT2_RX_COUNT2_RX_Msk */
#define USB_COUNT2_RX_COUNT2_RX_Msk			REG_FIELD_MASK(USB_COUNT2_RX_COUNT2_RX_Pos, USB_COUNT2_RX_COUNT2_RX_Width)
/** @brief Reception Byte Count @def USB_COUNT2_RX_COUNT2_RX */
#define USB_COUNT2_RX_COUNT2_RX				USB_COUNT2_RX_COUNT2_RX_Msk

/** @brief Bit position of the `USB_COUNT2_RX_NUM_BLOCK` field @def USB_COUNT2_RX_NUM_BLOCK_Pos */
#define USB_COUNT2_RX_NUM_BLOCK_Pos			((reg_bit_pos_t) 10U)
/** @brief Width of the `USB_COUNT2_RX_NUM_BLOCK` field @def USB_COUNT2_RX_NUM_BLOCK_Width */
#define USB_COUNT2_RX_NUM_BLOCK_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `USB_COUNT2_RX_NUM_BLOCK` field @def USB_COUNT2_RX_NUM_BLOCK_Msk */
#define USB_COUNT2_RX_NUM_BLOCK_Msk			REG_FIELD_MASK(USB_COUNT2_RX_NUM_BLOCK_Pos, USB_COUNT2_RX_NUM_BLOCK_Width)
/** @brief NUM_BLOCK[4:0] bits (Number of blocks) @def USB_COUNT2_RX_NUM_BLOCK */
#define USB_COUNT2_RX_NUM_BLOCK				USB_COUNT2_RX_NUM_BLOCK_Msk
/** @brief Register or selector value represented by `USB_COUNT2_RX_NUM_BLOCK_0` @def USB_COUNT2_RX_NUM_BLOCK_0 */
#define USB_COUNT2_RX_NUM_BLOCK_0			(0x01UL << USB_COUNT2_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT2_RX_NUM_BLOCK_1` @def USB_COUNT2_RX_NUM_BLOCK_1 */
#define USB_COUNT2_RX_NUM_BLOCK_1			(0x02UL << USB_COUNT2_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT2_RX_NUM_BLOCK_2` @def USB_COUNT2_RX_NUM_BLOCK_2 */
#define USB_COUNT2_RX_NUM_BLOCK_2			(0x04UL << USB_COUNT2_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT2_RX_NUM_BLOCK_3` @def USB_COUNT2_RX_NUM_BLOCK_3 */
#define USB_COUNT2_RX_NUM_BLOCK_3			(0x08UL << USB_COUNT2_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT2_RX_NUM_BLOCK_4` @def USB_COUNT2_RX_NUM_BLOCK_4 */
#define USB_COUNT2_RX_NUM_BLOCK_4			(0x10UL << USB_COUNT2_RX_NUM_BLOCK_Pos)

/** @brief Bit position of the `USB_COUNT2_RX_BLSIZE` field @def USB_COUNT2_RX_BLSIZE_Pos */
#define USB_COUNT2_RX_BLSIZE_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_COUNT2_RX_BLSIZE` field @def USB_COUNT2_RX_BLSIZE_Msk */
#define USB_COUNT2_RX_BLSIZE_Msk			REG_BIT_MASK(USB_COUNT2_RX_BLSIZE_Pos)
/** @brief BLock SIZE @def USB_COUNT2_RX_BLSIZE */
#define USB_COUNT2_RX_BLSIZE				USB_COUNT2_RX_BLSIZE_Msk

// -------------------------------- USB_COUNT3_RX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT3_RX_COUNT3_RX` field @def USB_COUNT3_RX_COUNT3_RX_Pos */
#define USB_COUNT3_RX_COUNT3_RX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT3_RX_COUNT3_RX` field @def USB_COUNT3_RX_COUNT3_RX_Width */
#define USB_COUNT3_RX_COUNT3_RX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT3_RX_COUNT3_RX` field @def USB_COUNT3_RX_COUNT3_RX_Msk */
#define USB_COUNT3_RX_COUNT3_RX_Msk			REG_FIELD_MASK(USB_COUNT3_RX_COUNT3_RX_Pos, USB_COUNT3_RX_COUNT3_RX_Width)
/** @brief Reception Byte Count @def USB_COUNT3_RX_COUNT3_RX */
#define USB_COUNT3_RX_COUNT3_RX				USB_COUNT3_RX_COUNT3_RX_Msk

/** @brief Bit position of the `USB_COUNT3_RX_NUM_BLOCK` field @def USB_COUNT3_RX_NUM_BLOCK_Pos */
#define USB_COUNT3_RX_NUM_BLOCK_Pos			((reg_bit_pos_t) 10U)
/** @brief Width of the `USB_COUNT3_RX_NUM_BLOCK` field @def USB_COUNT3_RX_NUM_BLOCK_Width */
#define USB_COUNT3_RX_NUM_BLOCK_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `USB_COUNT3_RX_NUM_BLOCK` field @def USB_COUNT3_RX_NUM_BLOCK_Msk */
#define USB_COUNT3_RX_NUM_BLOCK_Msk			REG_FIELD_MASK(USB_COUNT3_RX_NUM_BLOCK_Pos, USB_COUNT3_RX_NUM_BLOCK_Width)
/** @brief NUM_BLOCK[4:0] bits (Number of blocks) @def USB_COUNT3_RX_NUM_BLOCK */
#define USB_COUNT3_RX_NUM_BLOCK				USB_COUNT3_RX_NUM_BLOCK_Msk
/** @brief Register or selector value represented by `USB_COUNT3_RX_NUM_BLOCK_0` @def USB_COUNT3_RX_NUM_BLOCK_0 */
#define USB_COUNT3_RX_NUM_BLOCK_0			(0x01UL << USB_COUNT3_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT3_RX_NUM_BLOCK_1` @def USB_COUNT3_RX_NUM_BLOCK_1 */
#define USB_COUNT3_RX_NUM_BLOCK_1			(0x02UL << USB_COUNT3_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT3_RX_NUM_BLOCK_2` @def USB_COUNT3_RX_NUM_BLOCK_2 */
#define USB_COUNT3_RX_NUM_BLOCK_2			(0x04UL << USB_COUNT3_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT3_RX_NUM_BLOCK_3` @def USB_COUNT3_RX_NUM_BLOCK_3 */
#define USB_COUNT3_RX_NUM_BLOCK_3			(0x08UL << USB_COUNT3_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT3_RX_NUM_BLOCK_4` @def USB_COUNT3_RX_NUM_BLOCK_4 */
#define USB_COUNT3_RX_NUM_BLOCK_4			(0x10UL << USB_COUNT3_RX_NUM_BLOCK_Pos)

/** @brief Bit position of the `USB_COUNT3_RX_BLSIZE` field @def USB_COUNT3_RX_BLSIZE_Pos */
#define USB_COUNT3_RX_BLSIZE_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_COUNT3_RX_BLSIZE` field @def USB_COUNT3_RX_BLSIZE_Msk */
#define USB_COUNT3_RX_BLSIZE_Msk			REG_BIT_MASK(USB_COUNT3_RX_BLSIZE_Pos)
/** @brief BLock SIZE @def USB_COUNT3_RX_BLSIZE */
#define USB_COUNT3_RX_BLSIZE				USB_COUNT3_RX_BLSIZE_Msk

// -------------------------------- USB_COUNT4_RX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT4_RX_COUNT4_RX` field @def USB_COUNT4_RX_COUNT4_RX_Pos */
#define USB_COUNT4_RX_COUNT4_RX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT4_RX_COUNT4_RX` field @def USB_COUNT4_RX_COUNT4_RX_Width */
#define USB_COUNT4_RX_COUNT4_RX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT4_RX_COUNT4_RX` field @def USB_COUNT4_RX_COUNT4_RX_Msk */
#define USB_COUNT4_RX_COUNT4_RX_Msk			REG_FIELD_MASK(USB_COUNT4_RX_COUNT4_RX_Pos, USB_COUNT4_RX_COUNT4_RX_Width)
/** @brief Reception Byte Count @def USB_COUNT4_RX_COUNT4_RX */
#define USB_COUNT4_RX_COUNT4_RX				USB_COUNT4_RX_COUNT4_RX_Msk

/** @brief Bit position of the `USB_COUNT4_RX_NUM_BLOCK` field @def USB_COUNT4_RX_NUM_BLOCK_Pos */
#define USB_COUNT4_RX_NUM_BLOCK_Pos			((reg_bit_pos_t) 10U)
/** @brief Width of the `USB_COUNT4_RX_NUM_BLOCK` field @def USB_COUNT4_RX_NUM_BLOCK_Width */
#define USB_COUNT4_RX_NUM_BLOCK_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `USB_COUNT4_RX_NUM_BLOCK` field @def USB_COUNT4_RX_NUM_BLOCK_Msk */
#define USB_COUNT4_RX_NUM_BLOCK_Msk			REG_FIELD_MASK(USB_COUNT4_RX_NUM_BLOCK_Pos, USB_COUNT4_RX_NUM_BLOCK_Width)
/** @brief NUM_BLOCK[4:0] bits (Number of blocks) @def USB_COUNT4_RX_NUM_BLOCK */
#define USB_COUNT4_RX_NUM_BLOCK				USB_COUNT4_RX_NUM_BLOCK_Msk
/** @brief Register or selector value represented by `USB_COUNT4_RX_NUM_BLOCK_0` @def USB_COUNT4_RX_NUM_BLOCK_0 */
#define USB_COUNT4_RX_NUM_BLOCK_0			(0x01UL << USB_COUNT4_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT4_RX_NUM_BLOCK_1` @def USB_COUNT4_RX_NUM_BLOCK_1 */
#define USB_COUNT4_RX_NUM_BLOCK_1			(0x02UL << USB_COUNT4_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT4_RX_NUM_BLOCK_2` @def USB_COUNT4_RX_NUM_BLOCK_2 */
#define USB_COUNT4_RX_NUM_BLOCK_2			(0x04UL << USB_COUNT4_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT4_RX_NUM_BLOCK_3` @def USB_COUNT4_RX_NUM_BLOCK_3 */
#define USB_COUNT4_RX_NUM_BLOCK_3			(0x08UL << USB_COUNT4_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT4_RX_NUM_BLOCK_4` @def USB_COUNT4_RX_NUM_BLOCK_4 */
#define USB_COUNT4_RX_NUM_BLOCK_4			(0x10UL << USB_COUNT4_RX_NUM_BLOCK_Pos)

/** @brief Bit position of the `USB_COUNT4_RX_BLSIZE` field @def USB_COUNT4_RX_BLSIZE_Pos */
#define USB_COUNT4_RX_BLSIZE_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_COUNT4_RX_BLSIZE` field @def USB_COUNT4_RX_BLSIZE_Msk */
#define USB_COUNT4_RX_BLSIZE_Msk			REG_BIT_MASK(USB_COUNT4_RX_BLSIZE_Pos)
/** @brief BLock SIZE @def USB_COUNT4_RX_BLSIZE */
#define USB_COUNT4_RX_BLSIZE				USB_COUNT4_RX_BLSIZE_Msk

// -------------------------------- USB_COUNT5_RX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT5_RX_COUNT5_RX` field @def USB_COUNT5_RX_COUNT5_RX_Pos */
#define USB_COUNT5_RX_COUNT5_RX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT5_RX_COUNT5_RX` field @def USB_COUNT5_RX_COUNT5_RX_Width */
#define USB_COUNT5_RX_COUNT5_RX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT5_RX_COUNT5_RX` field @def USB_COUNT5_RX_COUNT5_RX_Msk */
#define USB_COUNT5_RX_COUNT5_RX_Msk			REG_FIELD_MASK(USB_COUNT5_RX_COUNT5_RX_Pos, USB_COUNT5_RX_COUNT5_RX_Width)
/** @brief Reception Byte Count @def USB_COUNT5_RX_COUNT5_RX */
#define USB_COUNT5_RX_COUNT5_RX				USB_COUNT5_RX_COUNT5_RX_Msk

/** @brief Bit position of the `USB_COUNT5_RX_NUM_BLOCK` field @def USB_COUNT5_RX_NUM_BLOCK_Pos */
#define USB_COUNT5_RX_NUM_BLOCK_Pos			((reg_bit_pos_t) 10U)
/** @brief Width of the `USB_COUNT5_RX_NUM_BLOCK` field @def USB_COUNT5_RX_NUM_BLOCK_Width */
#define USB_COUNT5_RX_NUM_BLOCK_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `USB_COUNT5_RX_NUM_BLOCK` field @def USB_COUNT5_RX_NUM_BLOCK_Msk */
#define USB_COUNT5_RX_NUM_BLOCK_Msk			REG_FIELD_MASK(USB_COUNT5_RX_NUM_BLOCK_Pos, USB_COUNT5_RX_NUM_BLOCK_Width)
/** @brief NUM_BLOCK[4:0] bits (Number of blocks) @def USB_COUNT5_RX_NUM_BLOCK */
#define USB_COUNT5_RX_NUM_BLOCK				USB_COUNT5_RX_NUM_BLOCK_Msk
/** @brief Register or selector value represented by `USB_COUNT5_RX_NUM_BLOCK_0` @def USB_COUNT5_RX_NUM_BLOCK_0 */
#define USB_COUNT5_RX_NUM_BLOCK_0			(0x01UL << USB_COUNT5_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT5_RX_NUM_BLOCK_1` @def USB_COUNT5_RX_NUM_BLOCK_1 */
#define USB_COUNT5_RX_NUM_BLOCK_1			(0x02UL << USB_COUNT5_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT5_RX_NUM_BLOCK_2` @def USB_COUNT5_RX_NUM_BLOCK_2 */
#define USB_COUNT5_RX_NUM_BLOCK_2			(0x04UL << USB_COUNT5_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT5_RX_NUM_BLOCK_3` @def USB_COUNT5_RX_NUM_BLOCK_3 */
#define USB_COUNT5_RX_NUM_BLOCK_3			(0x08UL << USB_COUNT5_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT5_RX_NUM_BLOCK_4` @def USB_COUNT5_RX_NUM_BLOCK_4 */
#define USB_COUNT5_RX_NUM_BLOCK_4			(0x10UL << USB_COUNT5_RX_NUM_BLOCK_Pos)

/** @brief Bit position of the `USB_COUNT5_RX_BLSIZE` field @def USB_COUNT5_RX_BLSIZE_Pos */
#define USB_COUNT5_RX_BLSIZE_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_COUNT5_RX_BLSIZE` field @def USB_COUNT5_RX_BLSIZE_Msk */
#define USB_COUNT5_RX_BLSIZE_Msk			REG_BIT_MASK(USB_COUNT5_RX_BLSIZE_Pos)
/** @brief BLock SIZE @def USB_COUNT5_RX_BLSIZE */
#define USB_COUNT5_RX_BLSIZE				USB_COUNT5_RX_BLSIZE_Msk

// -------------------------------- USB_COUNT6_RX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT6_RX_COUNT6_RX` field @def USB_COUNT6_RX_COUNT6_RX_Pos */
#define USB_COUNT6_RX_COUNT6_RX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT6_RX_COUNT6_RX` field @def USB_COUNT6_RX_COUNT6_RX_Width */
#define USB_COUNT6_RX_COUNT6_RX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT6_RX_COUNT6_RX` field @def USB_COUNT6_RX_COUNT6_RX_Msk */
#define USB_COUNT6_RX_COUNT6_RX_Msk			REG_FIELD_MASK(USB_COUNT6_RX_COUNT6_RX_Pos, USB_COUNT6_RX_COUNT6_RX_Width)
/** @brief Reception Byte Count @def USB_COUNT6_RX_COUNT6_RX */
#define USB_COUNT6_RX_COUNT6_RX				USB_COUNT6_RX_COUNT6_RX_Msk

/** @brief Bit position of the `USB_COUNT6_RX_NUM_BLOCK` field @def USB_COUNT6_RX_NUM_BLOCK_Pos */
#define USB_COUNT6_RX_NUM_BLOCK_Pos			((reg_bit_pos_t) 10U)
/** @brief Width of the `USB_COUNT6_RX_NUM_BLOCK` field @def USB_COUNT6_RX_NUM_BLOCK_Width */
#define USB_COUNT6_RX_NUM_BLOCK_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `USB_COUNT6_RX_NUM_BLOCK` field @def USB_COUNT6_RX_NUM_BLOCK_Msk */
#define USB_COUNT6_RX_NUM_BLOCK_Msk			REG_FIELD_MASK(USB_COUNT6_RX_NUM_BLOCK_Pos, USB_COUNT6_RX_NUM_BLOCK_Width)
/** @brief NUM_BLOCK[4:0] bits (Number of blocks) @def USB_COUNT6_RX_NUM_BLOCK */
#define USB_COUNT6_RX_NUM_BLOCK				USB_COUNT6_RX_NUM_BLOCK_Msk
/** @brief Register or selector value represented by `USB_COUNT6_RX_NUM_BLOCK_0` @def USB_COUNT6_RX_NUM_BLOCK_0 */
#define USB_COUNT6_RX_NUM_BLOCK_0			(0x01UL << USB_COUNT6_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT6_RX_NUM_BLOCK_1` @def USB_COUNT6_RX_NUM_BLOCK_1 */
#define USB_COUNT6_RX_NUM_BLOCK_1			(0x02UL << USB_COUNT6_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT6_RX_NUM_BLOCK_2` @def USB_COUNT6_RX_NUM_BLOCK_2 */
#define USB_COUNT6_RX_NUM_BLOCK_2			(0x04UL << USB_COUNT6_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT6_RX_NUM_BLOCK_3` @def USB_COUNT6_RX_NUM_BLOCK_3 */
#define USB_COUNT6_RX_NUM_BLOCK_3			(0x08UL << USB_COUNT6_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT6_RX_NUM_BLOCK_4` @def USB_COUNT6_RX_NUM_BLOCK_4 */
#define USB_COUNT6_RX_NUM_BLOCK_4			(0x10UL << USB_COUNT6_RX_NUM_BLOCK_Pos)

/** @brief Bit position of the `USB_COUNT6_RX_BLSIZE` field @def USB_COUNT6_RX_BLSIZE_Pos */
#define USB_COUNT6_RX_BLSIZE_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_COUNT6_RX_BLSIZE` field @def USB_COUNT6_RX_BLSIZE_Msk */
#define USB_COUNT6_RX_BLSIZE_Msk			REG_BIT_MASK(USB_COUNT6_RX_BLSIZE_Pos)
/** @brief BLock SIZE @def USB_COUNT6_RX_BLSIZE */
#define USB_COUNT6_RX_BLSIZE				USB_COUNT6_RX_BLSIZE_Msk

// -------------------------------- USB_COUNT7_RX Register Bit Defines -------------------------------- //
/** @brief Bit position of the `USB_COUNT7_RX_COUNT7_RX` field @def USB_COUNT7_RX_COUNT7_RX_Pos */
#define USB_COUNT7_RX_COUNT7_RX_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USB_COUNT7_RX_COUNT7_RX` field @def USB_COUNT7_RX_COUNT7_RX_Width */
#define USB_COUNT7_RX_COUNT7_RX_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `USB_COUNT7_RX_COUNT7_RX` field @def USB_COUNT7_RX_COUNT7_RX_Msk */
#define USB_COUNT7_RX_COUNT7_RX_Msk			REG_FIELD_MASK(USB_COUNT7_RX_COUNT7_RX_Pos, USB_COUNT7_RX_COUNT7_RX_Width)
/** @brief Reception Byte Count @def USB_COUNT7_RX_COUNT7_RX */
#define USB_COUNT7_RX_COUNT7_RX				USB_COUNT7_RX_COUNT7_RX_Msk

/** @brief Bit position of the `USB_COUNT7_RX_NUM_BLOCK` field @def USB_COUNT7_RX_NUM_BLOCK_Pos */
#define USB_COUNT7_RX_NUM_BLOCK_Pos			((reg_bit_pos_t) 10U)
/** @brief Width of the `USB_COUNT7_RX_NUM_BLOCK` field @def USB_COUNT7_RX_NUM_BLOCK_Width */
#define USB_COUNT7_RX_NUM_BLOCK_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `USB_COUNT7_RX_NUM_BLOCK` field @def USB_COUNT7_RX_NUM_BLOCK_Msk */
#define USB_COUNT7_RX_NUM_BLOCK_Msk			REG_FIELD_MASK(USB_COUNT7_RX_NUM_BLOCK_Pos, USB_COUNT7_RX_NUM_BLOCK_Width)
/** @brief NUM_BLOCK[4:0] bits (Number of blocks) @def USB_COUNT7_RX_NUM_BLOCK */
#define USB_COUNT7_RX_NUM_BLOCK				USB_COUNT7_RX_NUM_BLOCK_Msk
/** @brief Register or selector value represented by `USB_COUNT7_RX_NUM_BLOCK_0` @def USB_COUNT7_RX_NUM_BLOCK_0 */
#define USB_COUNT7_RX_NUM_BLOCK_0			(0x01UL << USB_COUNT7_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT7_RX_NUM_BLOCK_1` @def USB_COUNT7_RX_NUM_BLOCK_1 */
#define USB_COUNT7_RX_NUM_BLOCK_1			(0x02UL << USB_COUNT7_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT7_RX_NUM_BLOCK_2` @def USB_COUNT7_RX_NUM_BLOCK_2 */
#define USB_COUNT7_RX_NUM_BLOCK_2			(0x04UL << USB_COUNT7_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT7_RX_NUM_BLOCK_3` @def USB_COUNT7_RX_NUM_BLOCK_3 */
#define USB_COUNT7_RX_NUM_BLOCK_3			(0x08UL << USB_COUNT7_RX_NUM_BLOCK_Pos)
/** @brief Register or selector value represented by `USB_COUNT7_RX_NUM_BLOCK_4` @def USB_COUNT7_RX_NUM_BLOCK_4 */
#define USB_COUNT7_RX_NUM_BLOCK_4			(0x10UL << USB_COUNT7_RX_NUM_BLOCK_Pos)

/** @brief Bit position of the `USB_COUNT7_RX_BLSIZE` field @def USB_COUNT7_RX_BLSIZE_Pos */
#define USB_COUNT7_RX_BLSIZE_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `USB_COUNT7_RX_BLSIZE` field @def USB_COUNT7_RX_BLSIZE_Msk */
#define USB_COUNT7_RX_BLSIZE_Msk			REG_BIT_MASK(USB_COUNT7_RX_BLSIZE_Pos)
/** @brief BLock SIZE @def USB_COUNT7_RX_BLSIZE */
#define USB_COUNT7_RX_BLSIZE				USB_COUNT7_RX_BLSIZE_Msk

// --------------------------- USB Packed Reception Count Register Defines ---------------------------- //

// ------------------------------- USB_COUNT0_RX_0 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (low) @def USB_COUNT0_RX_0_COUNT0_RX_0 */
#define USB_COUNT0_RX_0_COUNT0_RX_0			0x000003FFU

/** @brief NUM_BLOCK_0[4:0] bits (Number of blocks) (low) @def USB_COUNT0_RX_0_NUM_BLOCK_0 */
#define USB_COUNT0_RX_0_NUM_BLOCK_0			0x00007C00U
/** @brief Bit 0 @def USB_COUNT0_RX_0_NUM_BLOCK_0_0 */
#define USB_COUNT0_RX_0_NUM_BLOCK_0_0		0x00000400U
/** @brief Bit 1 @def USB_COUNT0_RX_0_NUM_BLOCK_0_1 */
#define USB_COUNT0_RX_0_NUM_BLOCK_0_1		0x00000800U
/** @brief Bit 2 @def USB_COUNT0_RX_0_NUM_BLOCK_0_2 */
#define USB_COUNT0_RX_0_NUM_BLOCK_0_2		0x00001000U
/** @brief Bit 3 @def USB_COUNT0_RX_0_NUM_BLOCK_0_3 */
#define USB_COUNT0_RX_0_NUM_BLOCK_0_3		0x00002000U
/** @brief Bit 4 @def USB_COUNT0_RX_0_NUM_BLOCK_0_4 */
#define USB_COUNT0_RX_0_NUM_BLOCK_0_4		0x00004000U

/** @brief BLock SIZE (low) @def USB_COUNT0_RX_0_BLSIZE_0 */
#define USB_COUNT0_RX_0_BLSIZE_0			0x00008000U

// ------------------------------- USB_COUNT0_RX_1 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (high) @def USB_COUNT0_RX_1_COUNT0_RX_1 */
#define USB_COUNT0_RX_1_COUNT0_RX_1			0x03FF0000U

/** @brief NUM_BLOCK_1[4:0] bits (Number of blocks) (high) @def USB_COUNT0_RX_1_NUM_BLOCK_1 */
#define USB_COUNT0_RX_1_NUM_BLOCK_1			0x7C000000U
/** @brief Bit 1 @def USB_COUNT0_RX_1_NUM_BLOCK_1_0 */
#define USB_COUNT0_RX_1_NUM_BLOCK_1_0		0x04000000U
/** @brief Bit 1 @def USB_COUNT0_RX_1_NUM_BLOCK_1_1 */
#define USB_COUNT0_RX_1_NUM_BLOCK_1_1		0x08000000U
/** @brief Bit 2 @def USB_COUNT0_RX_1_NUM_BLOCK_1_2 */
#define USB_COUNT0_RX_1_NUM_BLOCK_1_2		0x10000000U
/** @brief Bit 3 @def USB_COUNT0_RX_1_NUM_BLOCK_1_3 */
#define USB_COUNT0_RX_1_NUM_BLOCK_1_3		0x20000000U
/** @brief Bit 4 @def USB_COUNT0_RX_1_NUM_BLOCK_1_4 */
#define USB_COUNT0_RX_1_NUM_BLOCK_1_4		0x40000000U

/** @brief BLock SIZE (high) @def USB_COUNT0_RX_1_BLSIZE_1 */
#define USB_COUNT0_RX_1_BLSIZE_1			0x80000000U

// ------------------------------- USB_COUNT1_RX_0 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (low) @def USB_COUNT1_RX_0_COUNT1_RX_0 */
#define USB_COUNT1_RX_0_COUNT1_RX_0			0x000003FFU

/** @brief NUM_BLOCK_0[4:0] bits (Number of blocks) (low) @def USB_COUNT1_RX_0_NUM_BLOCK_0 */
#define USB_COUNT1_RX_0_NUM_BLOCK_0			0x00007C00U
/** @brief Bit 0 @def USB_COUNT1_RX_0_NUM_BLOCK_0_0 */
#define USB_COUNT1_RX_0_NUM_BLOCK_0_0		0x00000400U
/** @brief Bit 1 @def USB_COUNT1_RX_0_NUM_BLOCK_0_1 */
#define USB_COUNT1_RX_0_NUM_BLOCK_0_1		0x00000800U
/** @brief Bit 2 @def USB_COUNT1_RX_0_NUM_BLOCK_0_2 */
#define USB_COUNT1_RX_0_NUM_BLOCK_0_2		0x00001000U
/** @brief Bit 3 @def USB_COUNT1_RX_0_NUM_BLOCK_0_3 */
#define USB_COUNT1_RX_0_NUM_BLOCK_0_3		0x00002000U
/** @brief Bit 4 @def USB_COUNT1_RX_0_NUM_BLOCK_0_4 */
#define USB_COUNT1_RX_0_NUM_BLOCK_0_4		0x00004000U

/** @brief BLock SIZE (low) @def USB_COUNT1_RX_0_BLSIZE_0 */
#define USB_COUNT1_RX_0_BLSIZE_0			0x00008000U

// ------------------------------- USB_COUNT1_RX_1 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (high) @def USB_COUNT1_RX_1_COUNT1_RX_1 */
#define USB_COUNT1_RX_1_COUNT1_RX_1			0x03FF0000U

/** @brief NUM_BLOCK_1[4:0] bits (Number of blocks) (high) @def USB_COUNT1_RX_1_NUM_BLOCK_1 */
#define USB_COUNT1_RX_1_NUM_BLOCK_1			0x7C000000U
/** @brief Bit 0 @def USB_COUNT1_RX_1_NUM_BLOCK_1_0 */
#define USB_COUNT1_RX_1_NUM_BLOCK_1_0		0x04000000U
/** @brief Bit 1 @def USB_COUNT1_RX_1_NUM_BLOCK_1_1 */
#define USB_COUNT1_RX_1_NUM_BLOCK_1_1		0x08000000U
/** @brief Bit 2 @def USB_COUNT1_RX_1_NUM_BLOCK_1_2 */
#define USB_COUNT1_RX_1_NUM_BLOCK_1_2		0x10000000U
/** @brief Bit 3 @def USB_COUNT1_RX_1_NUM_BLOCK_1_3 */
#define USB_COUNT1_RX_1_NUM_BLOCK_1_3		0x20000000U
/** @brief Bit 4 @def USB_COUNT1_RX_1_NUM_BLOCK_1_4 */
#define USB_COUNT1_RX_1_NUM_BLOCK_1_4		0x40000000U

/** @brief BLock SIZE (high) @def USB_COUNT1_RX_1_BLSIZE_1 */
#define USB_COUNT1_RX_1_BLSIZE_1			0x80000000U

// ------------------------------- USB_COUNT2_RX_0 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (low) @def USB_COUNT2_RX_0_COUNT2_RX_0 */
#define USB_COUNT2_RX_0_COUNT2_RX_0			0x000003FFU

/** @brief NUM_BLOCK_0[4:0] bits (Number of blocks) (low) @def USB_COUNT2_RX_0_NUM_BLOCK_0 */
#define USB_COUNT2_RX_0_NUM_BLOCK_0			0x00007C00U
/** @brief Bit 0 @def USB_COUNT2_RX_0_NUM_BLOCK_0_0 */
#define USB_COUNT2_RX_0_NUM_BLOCK_0_0		0x00000400U
/** @brief Bit 1 @def USB_COUNT2_RX_0_NUM_BLOCK_0_1 */
#define USB_COUNT2_RX_0_NUM_BLOCK_0_1		0x00000800U
/** @brief Bit 2 @def USB_COUNT2_RX_0_NUM_BLOCK_0_2 */
#define USB_COUNT2_RX_0_NUM_BLOCK_0_2		0x00001000U
/** @brief Bit 3 @def USB_COUNT2_RX_0_NUM_BLOCK_0_3 */
#define USB_COUNT2_RX_0_NUM_BLOCK_0_3		0x00002000U
/** @brief Bit 4 @def USB_COUNT2_RX_0_NUM_BLOCK_0_4 */
#define USB_COUNT2_RX_0_NUM_BLOCK_0_4		0x00004000U

/** @brief BLock SIZE (low) @def USB_COUNT2_RX_0_BLSIZE_0 */
#define USB_COUNT2_RX_0_BLSIZE_0			0x00008000U

// ------------------------------- USB_COUNT2_RX_1 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (high) @def USB_COUNT2_RX_1_COUNT2_RX_1 */
#define USB_COUNT2_RX_1_COUNT2_RX_1			0x03FF0000U

/** @brief NUM_BLOCK_1[4:0] bits (Number of blocks) (high) @def USB_COUNT2_RX_1_NUM_BLOCK_1 */
#define USB_COUNT2_RX_1_NUM_BLOCK_1			0x7C000000U
/** @brief Bit 0 @def USB_COUNT2_RX_1_NUM_BLOCK_1_0 */
#define USB_COUNT2_RX_1_NUM_BLOCK_1_0		0x04000000U
/** @brief Bit 1 @def USB_COUNT2_RX_1_NUM_BLOCK_1_1 */
#define USB_COUNT2_RX_1_NUM_BLOCK_1_1		0x08000000U
/** @brief Bit 2 @def USB_COUNT2_RX_1_NUM_BLOCK_1_2 */
#define USB_COUNT2_RX_1_NUM_BLOCK_1_2		0x10000000U
/** @brief Bit 3 @def USB_COUNT2_RX_1_NUM_BLOCK_1_3 */
#define USB_COUNT2_RX_1_NUM_BLOCK_1_3		0x20000000U
/** @brief Bit 4 @def USB_COUNT2_RX_1_NUM_BLOCK_1_4 */
#define USB_COUNT2_RX_1_NUM_BLOCK_1_4		0x40000000U

/** @brief BLock SIZE (high) @def USB_COUNT2_RX_1_BLSIZE_1 */
#define USB_COUNT2_RX_1_BLSIZE_1			0x80000000U

// ------------------------------- USB_COUNT3_RX_0 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (low) @def USB_COUNT3_RX_0_COUNT3_RX_0 */
#define USB_COUNT3_RX_0_COUNT3_RX_0			0x000003FFU

/** @brief NUM_BLOCK_0[4:0] bits (Number of blocks) (low) @def USB_COUNT3_RX_0_NUM_BLOCK_0 */
#define USB_COUNT3_RX_0_NUM_BLOCK_0			0x00007C00U
/** @brief Bit 0 @def USB_COUNT3_RX_0_NUM_BLOCK_0_0 */
#define USB_COUNT3_RX_0_NUM_BLOCK_0_0		0x00000400U
/** @brief Bit 1 @def USB_COUNT3_RX_0_NUM_BLOCK_0_1 */
#define USB_COUNT3_RX_0_NUM_BLOCK_0_1		0x00000800U
/** @brief Bit 2 @def USB_COUNT3_RX_0_NUM_BLOCK_0_2 */
#define USB_COUNT3_RX_0_NUM_BLOCK_0_2		0x00001000U
/** @brief Bit 3 @def USB_COUNT3_RX_0_NUM_BLOCK_0_3 */
#define USB_COUNT3_RX_0_NUM_BLOCK_0_3		0x00002000U
/** @brief Bit 4 @def USB_COUNT3_RX_0_NUM_BLOCK_0_4 */
#define USB_COUNT3_RX_0_NUM_BLOCK_0_4		0x00004000U

/** @brief BLock SIZE (low) @def USB_COUNT3_RX_0_BLSIZE_0 */
#define USB_COUNT3_RX_0_BLSIZE_0			0x00008000U

// ------------------------------- USB_COUNT3_RX_1 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (high) @def USB_COUNT3_RX_1_COUNT3_RX_1 */
#define USB_COUNT3_RX_1_COUNT3_RX_1			0x03FF0000U

/** @brief NUM_BLOCK_1[4:0] bits (Number of blocks) (high) @def USB_COUNT3_RX_1_NUM_BLOCK_1 */
#define USB_COUNT3_RX_1_NUM_BLOCK_1			0x7C000000U
/** @brief Bit 0 @def USB_COUNT3_RX_1_NUM_BLOCK_1_0 */
#define USB_COUNT3_RX_1_NUM_BLOCK_1_0		0x04000000U
/** @brief Bit 1 @def USB_COUNT3_RX_1_NUM_BLOCK_1_1 */
#define USB_COUNT3_RX_1_NUM_BLOCK_1_1		0x08000000U
/** @brief Bit 2 @def USB_COUNT3_RX_1_NUM_BLOCK_1_2 */
#define USB_COUNT3_RX_1_NUM_BLOCK_1_2		0x10000000U
/** @brief Bit 3 @def USB_COUNT3_RX_1_NUM_BLOCK_1_3 */
#define USB_COUNT3_RX_1_NUM_BLOCK_1_3		0x20000000U
/** @brief Bit 4 @def USB_COUNT3_RX_1_NUM_BLOCK_1_4 */
#define USB_COUNT3_RX_1_NUM_BLOCK_1_4		0x40000000U

/** @brief BLock SIZE (high) @def USB_COUNT3_RX_1_BLSIZE_1 */
#define USB_COUNT3_RX_1_BLSIZE_1			0x80000000U

// ------------------------------- USB_COUNT4_RX_0 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (low) @def USB_COUNT4_RX_0_COUNT4_RX_0 */
#define USB_COUNT4_RX_0_COUNT4_RX_0			0x000003FFU

/** @brief NUM_BLOCK_0[4:0] bits (Number of blocks) (low) @def USB_COUNT4_RX_0_NUM_BLOCK_0 */
#define USB_COUNT4_RX_0_NUM_BLOCK_0			0x00007C00U
/** @brief Bit 0 @def USB_COUNT4_RX_0_NUM_BLOCK_0_0 */
#define USB_COUNT4_RX_0_NUM_BLOCK_0_0		0x00000400U
/** @brief Bit 1 @def USB_COUNT4_RX_0_NUM_BLOCK_0_1 */
#define USB_COUNT4_RX_0_NUM_BLOCK_0_1		0x00000800U
/** @brief Bit 2 @def USB_COUNT4_RX_0_NUM_BLOCK_0_2 */
#define USB_COUNT4_RX_0_NUM_BLOCK_0_2		0x00001000U
/** @brief Bit 3 @def USB_COUNT4_RX_0_NUM_BLOCK_0_3 */
#define USB_COUNT4_RX_0_NUM_BLOCK_0_3		0x00002000U
/** @brief Bit 4 @def USB_COUNT4_RX_0_NUM_BLOCK_0_4 */
#define USB_COUNT4_RX_0_NUM_BLOCK_0_4		0x00004000U

/** @brief BLock SIZE (low) @def USB_COUNT4_RX_0_BLSIZE_0 */
#define USB_COUNT4_RX_0_BLSIZE_0			0x00008000U

// ------------------------------- USB_COUNT4_RX_1 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (high) @def USB_COUNT4_RX_1_COUNT4_RX_1 */
#define USB_COUNT4_RX_1_COUNT4_RX_1			0x03FF0000U

/** @brief NUM_BLOCK_1[4:0] bits (Number of blocks) (high) @def USB_COUNT4_RX_1_NUM_BLOCK_1 */
#define USB_COUNT4_RX_1_NUM_BLOCK_1			0x7C000000U
/** @brief Bit 0 @def USB_COUNT4_RX_1_NUM_BLOCK_1_0 */
#define USB_COUNT4_RX_1_NUM_BLOCK_1_0		0x04000000U
/** @brief Bit 1 @def USB_COUNT4_RX_1_NUM_BLOCK_1_1 */
#define USB_COUNT4_RX_1_NUM_BLOCK_1_1		0x08000000U
/** @brief Bit 2 @def USB_COUNT4_RX_1_NUM_BLOCK_1_2 */
#define USB_COUNT4_RX_1_NUM_BLOCK_1_2		0x10000000U
/** @brief Bit 3 @def USB_COUNT4_RX_1_NUM_BLOCK_1_3 */
#define USB_COUNT4_RX_1_NUM_BLOCK_1_3		0x20000000U
/** @brief Bit 4 @def USB_COUNT4_RX_1_NUM_BLOCK_1_4 */
#define USB_COUNT4_RX_1_NUM_BLOCK_1_4		0x40000000U

/** @brief BLock SIZE (high) @def USB_COUNT4_RX_1_BLSIZE_1 */
#define USB_COUNT4_RX_1_BLSIZE_1			0x80000000U

// ------------------------------- USB_COUNT5_RX_0 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (low) @def USB_COUNT5_RX_0_COUNT5_RX_0 */
#define USB_COUNT5_RX_0_COUNT5_RX_0			0x000003FFU

/** @brief NUM_BLOCK_0[4:0] bits (Number of blocks) (low) @def USB_COUNT5_RX_0_NUM_BLOCK_0 */
#define USB_COUNT5_RX_0_NUM_BLOCK_0			0x00007C00U
/** @brief Bit 0 @def USB_COUNT5_RX_0_NUM_BLOCK_0_0 */
#define USB_COUNT5_RX_0_NUM_BLOCK_0_0		0x00000400U
/** @brief Bit 1 @def USB_COUNT5_RX_0_NUM_BLOCK_0_1 */
#define USB_COUNT5_RX_0_NUM_BLOCK_0_1		0x00000800U
/** @brief Bit 2 @def USB_COUNT5_RX_0_NUM_BLOCK_0_2 */
#define USB_COUNT5_RX_0_NUM_BLOCK_0_2		0x00001000U
/** @brief Bit 3 @def USB_COUNT5_RX_0_NUM_BLOCK_0_3 */
#define USB_COUNT5_RX_0_NUM_BLOCK_0_3		0x00002000U
/** @brief Bit 4 @def USB_COUNT5_RX_0_NUM_BLOCK_0_4 */
#define USB_COUNT5_RX_0_NUM_BLOCK_0_4		0x00004000U

/** @brief BLock SIZE (low) @def USB_COUNT5_RX_0_BLSIZE_0 */
#define USB_COUNT5_RX_0_BLSIZE_0			0x00008000U

// ------------------------------- USB_COUNT5_RX_1 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (high) @def USB_COUNT5_RX_1_COUNT5_RX_1 */
#define USB_COUNT5_RX_1_COUNT5_RX_1			0x03FF0000U

/** @brief NUM_BLOCK_1[4:0] bits (Number of blocks) (high) @def USB_COUNT5_RX_1_NUM_BLOCK_1 */
#define USB_COUNT5_RX_1_NUM_BLOCK_1			0x7C000000U
/** @brief Bit 0 @def USB_COUNT5_RX_1_NUM_BLOCK_1_0 */
#define USB_COUNT5_RX_1_NUM_BLOCK_1_0		0x04000000U
/** @brief Bit 1 @def USB_COUNT5_RX_1_NUM_BLOCK_1_1 */
#define USB_COUNT5_RX_1_NUM_BLOCK_1_1		0x08000000U
/** @brief Bit 2 @def USB_COUNT5_RX_1_NUM_BLOCK_1_2 */
#define USB_COUNT5_RX_1_NUM_BLOCK_1_2		0x10000000U
/** @brief Bit 3 @def USB_COUNT5_RX_1_NUM_BLOCK_1_3 */
#define USB_COUNT5_RX_1_NUM_BLOCK_1_3		0x20000000U
/** @brief Bit 4 @def USB_COUNT5_RX_1_NUM_BLOCK_1_4 */
#define USB_COUNT5_RX_1_NUM_BLOCK_1_4		0x40000000U

/** @brief BLock SIZE (high) @def USB_COUNT5_RX_1_BLSIZE_1 */
#define USB_COUNT5_RX_1_BLSIZE_1			0x80000000U

// ------------------------------- USB_COUNT6_RX_0 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (low) @def USB_COUNT6_RX_0_COUNT6_RX_0 */
#define USB_COUNT6_RX_0_COUNT6_RX_0			0x000003FFU

/** @brief NUM_BLOCK_0[4:0] bits (Number of blocks) (low) @def USB_COUNT6_RX_0_NUM_BLOCK_0 */
#define USB_COUNT6_RX_0_NUM_BLOCK_0			0x00007C00U
/** @brief Bit 0 @def USB_COUNT6_RX_0_NUM_BLOCK_0_0 */
#define USB_COUNT6_RX_0_NUM_BLOCK_0_0		0x00000400U
/** @brief Bit 1 @def USB_COUNT6_RX_0_NUM_BLOCK_0_1 */
#define USB_COUNT6_RX_0_NUM_BLOCK_0_1		0x00000800U
/** @brief Bit 2 @def USB_COUNT6_RX_0_NUM_BLOCK_0_2 */
#define USB_COUNT6_RX_0_NUM_BLOCK_0_2		0x00001000U
/** @brief Bit 3 @def USB_COUNT6_RX_0_NUM_BLOCK_0_3 */
#define USB_COUNT6_RX_0_NUM_BLOCK_0_3		0x00002000U
/** @brief Bit 4 @def USB_COUNT6_RX_0_NUM_BLOCK_0_4 */
#define USB_COUNT6_RX_0_NUM_BLOCK_0_4		0x00004000U

/** @brief BLock SIZE (low) @def USB_COUNT6_RX_0_BLSIZE_0 */
#define USB_COUNT6_RX_0_BLSIZE_0			0x00008000U

// ------------------------------- USB_COUNT6_RX_1 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (high) @def USB_COUNT6_RX_1_COUNT6_RX_1 */
#define USB_COUNT6_RX_1_COUNT6_RX_1			0x03FF0000U

/** @brief NUM_BLOCK_1[4:0] bits (Number of blocks) (high) @def USB_COUNT6_RX_1_NUM_BLOCK_1 */
#define USB_COUNT6_RX_1_NUM_BLOCK_1			0x7C000000U
/** @brief Bit 0 @def USB_COUNT6_RX_1_NUM_BLOCK_1_0 */
#define USB_COUNT6_RX_1_NUM_BLOCK_1_0		0x04000000U
/** @brief Bit 1 @def USB_COUNT6_RX_1_NUM_BLOCK_1_1 */
#define USB_COUNT6_RX_1_NUM_BLOCK_1_1		0x08000000U
/** @brief Bit 2 @def USB_COUNT6_RX_1_NUM_BLOCK_1_2 */
#define USB_COUNT6_RX_1_NUM_BLOCK_1_2		0x10000000U
/** @brief Bit 3 @def USB_COUNT6_RX_1_NUM_BLOCK_1_3 */
#define USB_COUNT6_RX_1_NUM_BLOCK_1_3		0x20000000U
/** @brief Bit 4 @def USB_COUNT6_RX_1_NUM_BLOCK_1_4 */
#define USB_COUNT6_RX_1_NUM_BLOCK_1_4		0x40000000U

/** @brief BLock SIZE (high) @def USB_COUNT6_RX_1_BLSIZE_1 */
#define USB_COUNT6_RX_1_BLSIZE_1			0x80000000U

// ------------------------------- USB_COUNT7_RX_0 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (low) @def USB_COUNT7_RX_0_COUNT7_RX_0 */
#define USB_COUNT7_RX_0_COUNT7_RX_0			0x000003FFU

/** @brief NUM_BLOCK_0[4:0] bits (Number of blocks) (low) @def USB_COUNT7_RX_0_NUM_BLOCK_0 */
#define USB_COUNT7_RX_0_NUM_BLOCK_0			0x00007C00U
/** @brief Bit 0 @def USB_COUNT7_RX_0_NUM_BLOCK_0_0 */
#define USB_COUNT7_RX_0_NUM_BLOCK_0_0		0x00000400U
/** @brief Bit 1 @def USB_COUNT7_RX_0_NUM_BLOCK_0_1 */
#define USB_COUNT7_RX_0_NUM_BLOCK_0_1		0x00000800U
/** @brief Bit 2 @def USB_COUNT7_RX_0_NUM_BLOCK_0_2 */
#define USB_COUNT7_RX_0_NUM_BLOCK_0_2		0x00001000U
/** @brief Bit 3 @def USB_COUNT7_RX_0_NUM_BLOCK_0_3 */
#define USB_COUNT7_RX_0_NUM_BLOCK_0_3		0x00002000U
/** @brief Bit 4 @def USB_COUNT7_RX_0_NUM_BLOCK_0_4 */
#define USB_COUNT7_RX_0_NUM_BLOCK_0_4		0x00004000U

/** @brief BLock SIZE (low) @def USB_COUNT7_RX_0_BLSIZE_0 */
#define USB_COUNT7_RX_0_BLSIZE_0			0x00008000U

// ------------------------------- USB_COUNT7_RX_1 Register Bit Defines ------------------------------- //
/** @brief Reception Byte Count (high) @def USB_COUNT7_RX_1_COUNT7_RX_1 */
#define USB_COUNT7_RX_1_COUNT7_RX_1			0x03FF0000U

/** @brief NUM_BLOCK_1[4:0] bits (Number of blocks) (high) @def USB_COUNT7_RX_1_NUM_BLOCK_1 */
#define USB_COUNT7_RX_1_NUM_BLOCK_1			0x7C000000U
/** @brief Bit 0 @def USB_COUNT7_RX_1_NUM_BLOCK_1_0 */
#define USB_COUNT7_RX_1_NUM_BLOCK_1_0		0x04000000U
/** @brief Bit 1 @def USB_COUNT7_RX_1_NUM_BLOCK_1_1 */
#define USB_COUNT7_RX_1_NUM_BLOCK_1_1		0x08000000U
/** @brief Bit 2 @def USB_COUNT7_RX_1_NUM_BLOCK_1_2 */
#define USB_COUNT7_RX_1_NUM_BLOCK_1_2		0x10000000U
/** @brief Bit 3 @def USB_COUNT7_RX_1_NUM_BLOCK_1_3 */
#define USB_COUNT7_RX_1_NUM_BLOCK_1_3		0x20000000U
/** @brief Bit 4 @def USB_COUNT7_RX_1_NUM_BLOCK_1_4 */
#define USB_COUNT7_RX_1_NUM_BLOCK_1_4		0x40000000U

/** @brief BLock SIZE (high) @def USB_COUNT7_RX_1_BLSIZE_1 */
#define USB_COUNT7_RX_1_BLSIZE_1			0x80000000U

// ==================================================================================================== //
// ==================================================================================================== //
//										Debug MCU Register Defines										//
// ==================================================================================================== //

// -------------------------------- DBGMCU_IDCODE Register Bit Defines -------------------------------- //
/** @brief Bit position of the `DBGMCU_IDCODE_DEV_ID` field @def DBGMCU_IDCODE_DEV_ID_Pos */
#define DBGMCU_IDCODE_DEV_ID_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `DBGMCU_IDCODE_DEV_ID` field @def DBGMCU_IDCODE_DEV_ID_Width */
#define DBGMCU_IDCODE_DEV_ID_Width		((reg_field_width_t) 12U)
/** @brief Register-positioned mask for the `DBGMCU_IDCODE_DEV_ID` field @def DBGMCU_IDCODE_DEV_ID_Msk */
#define DBGMCU_IDCODE_DEV_ID_Msk		REG_FIELD_MASK(DBGMCU_IDCODE_DEV_ID_Pos, DBGMCU_IDCODE_DEV_ID_Width)
/** @brief Device Identifier @def DBGMCU_IDCODE_DEV_ID */
#define DBGMCU_IDCODE_DEV_ID			DBGMCU_IDCODE_DEV_ID_Msk

/** @brief Bit position of the `DBGMCU_IDCODE_REV_ID` field @def DBGMCU_IDCODE_REV_ID_Pos */
#define DBGMCU_IDCODE_REV_ID_Pos		((reg_bit_pos_t) 16U)
/** @brief Width of the `DBGMCU_IDCODE_REV_ID` field @def DBGMCU_IDCODE_REV_ID_Width */
#define DBGMCU_IDCODE_REV_ID_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `DBGMCU_IDCODE_REV_ID` field @def DBGMCU_IDCODE_REV_ID_Msk */
#define DBGMCU_IDCODE_REV_ID_Msk		REG_FIELD_MASK(DBGMCU_IDCODE_REV_ID_Pos, DBGMCU_IDCODE_REV_ID_Width)
/** @brief REV_ID[15:0] bits (Revision Identifier) @def DBGMCU_IDCODE_REV_ID */
#define DBGMCU_IDCODE_REV_ID			DBGMCU_IDCODE_REV_ID_Msk
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_0` @def DBGMCU_IDCODE_REV_ID_0 */
#define DBGMCU_IDCODE_REV_ID_0			(0x0001UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_1` @def DBGMCU_IDCODE_REV_ID_1 */
#define DBGMCU_IDCODE_REV_ID_1			(0x0002UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_2` @def DBGMCU_IDCODE_REV_ID_2 */
#define DBGMCU_IDCODE_REV_ID_2			(0x0004UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_3` @def DBGMCU_IDCODE_REV_ID_3 */
#define DBGMCU_IDCODE_REV_ID_3			(0x0008UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_4` @def DBGMCU_IDCODE_REV_ID_4 */
#define DBGMCU_IDCODE_REV_ID_4			(0x0010UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_5` @def DBGMCU_IDCODE_REV_ID_5 */
#define DBGMCU_IDCODE_REV_ID_5			(0x0020UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_6` @def DBGMCU_IDCODE_REV_ID_6 */
#define DBGMCU_IDCODE_REV_ID_6			(0x0040UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_7` @def DBGMCU_IDCODE_REV_ID_7 */
#define DBGMCU_IDCODE_REV_ID_7			(0x0080UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_8` @def DBGMCU_IDCODE_REV_ID_8 */
#define DBGMCU_IDCODE_REV_ID_8			(0x0100UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_9` @def DBGMCU_IDCODE_REV_ID_9 */
#define DBGMCU_IDCODE_REV_ID_9			(0x0200UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_10` @def DBGMCU_IDCODE_REV_ID_10 */
#define DBGMCU_IDCODE_REV_ID_10			(0x0400UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_11` @def DBGMCU_IDCODE_REV_ID_11 */
#define DBGMCU_IDCODE_REV_ID_11			(0x0800UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_12` @def DBGMCU_IDCODE_REV_ID_12 */
#define DBGMCU_IDCODE_REV_ID_12			(0x1000UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_13` @def DBGMCU_IDCODE_REV_ID_13 */
#define DBGMCU_IDCODE_REV_ID_13			(0x2000UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_14` @def DBGMCU_IDCODE_REV_ID_14 */
#define DBGMCU_IDCODE_REV_ID_14			(0x4000UL << DBGMCU_IDCODE_REV_ID_Pos)
/** @brief Register or selector value represented by `DBGMCU_IDCODE_REV_ID_15` @def DBGMCU_IDCODE_REV_ID_15 */
#define DBGMCU_IDCODE_REV_ID_15			(0x8000UL << DBGMCU_IDCODE_REV_ID_Pos)

// ---------------------------------- DBGMCU_CR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `DBGMCU_CR_DBG_SLEEP` field @def DBGMCU_CR_DBG_SLEEP_Pos */
#define DBGMCU_CR_DBG_SLEEP_Pos						((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `DBGMCU_CR_DBG_SLEEP` field @def DBGMCU_CR_DBG_SLEEP_Msk */
#define DBGMCU_CR_DBG_SLEEP_Msk						REG_BIT_MASK(DBGMCU_CR_DBG_SLEEP_Pos)
/** @brief Debug Sleep Mode @def DBGMCU_CR_DBG_SLEEP */
#define DBGMCU_CR_DBG_SLEEP							DBGMCU_CR_DBG_SLEEP_Msk
/** @brief Bit position of the `DBGMCU_CR_DBG_STOP` field @def DBGMCU_CR_DBG_STOP_Pos */
#define DBGMCU_CR_DBG_STOP_Pos						((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `DBGMCU_CR_DBG_STOP` field @def DBGMCU_CR_DBG_STOP_Msk */
#define DBGMCU_CR_DBG_STOP_Msk						REG_BIT_MASK(DBGMCU_CR_DBG_STOP_Pos)
/** @brief Debug Stop Mode @def DBGMCU_CR_DBG_STOP */
#define DBGMCU_CR_DBG_STOP							DBGMCU_CR_DBG_STOP_Msk
/** @brief Bit position of the `DBGMCU_CR_DBG_STANDBY` field @def DBGMCU_CR_DBG_STANDBY_Pos */
#define DBGMCU_CR_DBG_STANDBY_Pos					((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `DBGMCU_CR_DBG_STANDBY` field @def DBGMCU_CR_DBG_STANDBY_Msk */
#define DBGMCU_CR_DBG_STANDBY_Msk					REG_BIT_MASK(DBGMCU_CR_DBG_STANDBY_Pos)
/** @brief Debug Standby mode @def DBGMCU_CR_DBG_STANDBY */
#define DBGMCU_CR_DBG_STANDBY						DBGMCU_CR_DBG_STANDBY_Msk
/** @brief Bit position of the `DBGMCU_CR_TRACE_IOEN` field @def DBGMCU_CR_TRACE_IOEN_Pos */
#define DBGMCU_CR_TRACE_IOEN_Pos					((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `DBGMCU_CR_TRACE_IOEN` field @def DBGMCU_CR_TRACE_IOEN_Msk */
#define DBGMCU_CR_TRACE_IOEN_Msk					REG_BIT_MASK(DBGMCU_CR_TRACE_IOEN_Pos)
/** @brief Trace Pin Assignment Control @def DBGMCU_CR_TRACE_IOEN */
#define DBGMCU_CR_TRACE_IOEN						DBGMCU_CR_TRACE_IOEN_Msk

/** @brief Bit position of the `DBGMCU_CR_TRACE_MODE` field @def DBGMCU_CR_TRACE_MODE_Pos */
#define DBGMCU_CR_TRACE_MODE_Pos					((reg_bit_pos_t) 6U)
/** @brief Width of the `DBGMCU_CR_TRACE_MODE` field @def DBGMCU_CR_TRACE_MODE_Width */
#define DBGMCU_CR_TRACE_MODE_Width					((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `DBGMCU_CR_TRACE_MODE` field @def DBGMCU_CR_TRACE_MODE_Msk */
#define DBGMCU_CR_TRACE_MODE_Msk					REG_FIELD_MASK(DBGMCU_CR_TRACE_MODE_Pos, DBGMCU_CR_TRACE_MODE_Width)
/** @brief TRACE_MODE[1:0] bits (Trace Pin Assignment Control) @def DBGMCU_CR_TRACE_MODE */
#define DBGMCU_CR_TRACE_MODE						DBGMCU_CR_TRACE_MODE_Msk
/** @brief Register or selector value represented by `DBGMCU_CR_TRACE_MODE_0` @def DBGMCU_CR_TRACE_MODE_0 */
#define DBGMCU_CR_TRACE_MODE_0						(0x1UL << DBGMCU_CR_TRACE_MODE_Pos)
/** @brief Register or selector value represented by `DBGMCU_CR_TRACE_MODE_1` @def DBGMCU_CR_TRACE_MODE_1 */
#define DBGMCU_CR_TRACE_MODE_1						(0x2UL << DBGMCU_CR_TRACE_MODE_Pos)

/** @brief Bit position of the `DBGMCU_CR_DBG_IWDG_STOP` field @def DBGMCU_CR_DBG_IWDG_STOP_Pos */
#define DBGMCU_CR_DBG_IWDG_STOP_Pos					((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `DBGMCU_CR_DBG_IWDG_STOP` field @def DBGMCU_CR_DBG_IWDG_STOP_Msk */
#define DBGMCU_CR_DBG_IWDG_STOP_Msk					REG_BIT_MASK(DBGMCU_CR_DBG_IWDG_STOP_Pos)
/** @brief Debug Independent Watchdog stopped when Core is halted @def DBGMCU_CR_DBG_IWDG_STOP */
#define DBGMCU_CR_DBG_IWDG_STOP						DBGMCU_CR_DBG_IWDG_STOP_Msk
/** @brief Bit position of the `DBGMCU_CR_DBG_WWDG_STOP` field @def DBGMCU_CR_DBG_WWDG_STOP_Pos */
#define DBGMCU_CR_DBG_WWDG_STOP_Pos					((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `DBGMCU_CR_DBG_WWDG_STOP` field @def DBGMCU_CR_DBG_WWDG_STOP_Msk */
#define DBGMCU_CR_DBG_WWDG_STOP_Msk					REG_BIT_MASK(DBGMCU_CR_DBG_WWDG_STOP_Pos)
/** @brief Debug Window Watchdog stopped when Core is halted @def DBGMCU_CR_DBG_WWDG_STOP */
#define DBGMCU_CR_DBG_WWDG_STOP						DBGMCU_CR_DBG_WWDG_STOP_Msk
/** @brief Bit position of the `DBGMCU_CR_DBG_TIM1_STOP` field @def DBGMCU_CR_DBG_TIM1_STOP_Pos */
#define DBGMCU_CR_DBG_TIM1_STOP_Pos					((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `DBGMCU_CR_DBG_TIM1_STOP` field @def DBGMCU_CR_DBG_TIM1_STOP_Msk */
#define DBGMCU_CR_DBG_TIM1_STOP_Msk					REG_BIT_MASK(DBGMCU_CR_DBG_TIM1_STOP_Pos)
/** @brief TIM1 counter stopped when core is halted @def DBGMCU_CR_DBG_TIM1_STOP */
#define DBGMCU_CR_DBG_TIM1_STOP						DBGMCU_CR_DBG_TIM1_STOP_Msk
/** @brief Bit position of the `DBGMCU_CR_DBG_TIM2_STOP` field @def DBGMCU_CR_DBG_TIM2_STOP_Pos */
#define DBGMCU_CR_DBG_TIM2_STOP_Pos					((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `DBGMCU_CR_DBG_TIM2_STOP` field @def DBGMCU_CR_DBG_TIM2_STOP_Msk */
#define DBGMCU_CR_DBG_TIM2_STOP_Msk					REG_BIT_MASK(DBGMCU_CR_DBG_TIM2_STOP_Pos)
/** @brief TIM2 counter stopped when core is halted @def DBGMCU_CR_DBG_TIM2_STOP */
#define DBGMCU_CR_DBG_TIM2_STOP						DBGMCU_CR_DBG_TIM2_STOP_Msk
/** @brief Bit position of the `DBGMCU_CR_DBG_TIM3_STOP` field @def DBGMCU_CR_DBG_TIM3_STOP_Pos */
#define DBGMCU_CR_DBG_TIM3_STOP_Pos					((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `DBGMCU_CR_DBG_TIM3_STOP` field @def DBGMCU_CR_DBG_TIM3_STOP_Msk */
#define DBGMCU_CR_DBG_TIM3_STOP_Msk					REG_BIT_MASK(DBGMCU_CR_DBG_TIM3_STOP_Pos)
/** @brief TIM3 counter stopped when core is halted @def DBGMCU_CR_DBG_TIM3_STOP */
#define DBGMCU_CR_DBG_TIM3_STOP						DBGMCU_CR_DBG_TIM3_STOP_Msk
/** @brief Bit position of the `DBGMCU_CR_DBG_TIM4_STOP` field @def DBGMCU_CR_DBG_TIM4_STOP_Pos */
#define DBGMCU_CR_DBG_TIM4_STOP_Pos					((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `DBGMCU_CR_DBG_TIM4_STOP` field @def DBGMCU_CR_DBG_TIM4_STOP_Msk */
#define DBGMCU_CR_DBG_TIM4_STOP_Msk					REG_BIT_MASK(DBGMCU_CR_DBG_TIM4_STOP_Pos)
/** @brief TIM4 counter stopped when core is halted @def DBGMCU_CR_DBG_TIM4_STOP */
#define DBGMCU_CR_DBG_TIM4_STOP						DBGMCU_CR_DBG_TIM4_STOP_Msk
/** @brief Bit position of the `DBGMCU_CR_DBG_CAN1_STOP` field @def DBGMCU_CR_DBG_CAN1_STOP_Pos */
#define DBGMCU_CR_DBG_CAN1_STOP_Pos					((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `DBGMCU_CR_DBG_CAN1_STOP` field @def DBGMCU_CR_DBG_CAN1_STOP_Msk */
#define DBGMCU_CR_DBG_CAN1_STOP_Msk					REG_BIT_MASK(DBGMCU_CR_DBG_CAN1_STOP_Pos)
/** @brief Debug CAN1 stopped when Core is halted @def DBGMCU_CR_DBG_CAN1_STOP */
#define DBGMCU_CR_DBG_CAN1_STOP						DBGMCU_CR_DBG_CAN1_STOP_Msk
/** @brief Bit position of the `DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT` field @def DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT_Pos */
#define DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT` field @def DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT_Msk */
#define DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT_Msk		REG_BIT_MASK(DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT_Pos)
/** @brief SMBUS timeout mode stopped when Core is halted @def DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT */
#define DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT			DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT_Msk
/** @brief Bit position of the `DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT` field @def DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT_Pos */
#define DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT` field @def DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT_Msk */
#define DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT_Msk		REG_BIT_MASK(DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT_Pos)
/** @brief SMBUS timeout mode stopped when Core is halted @def DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT */
#define DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT			DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT_Msk

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_DEFINES_H_ */
