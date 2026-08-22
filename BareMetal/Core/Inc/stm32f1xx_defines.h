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
 * The legacy `RDP_KEY_Msk`, `FLASH_KEY1_Msk`, and `FLASH_KEY2_Msk` identifiers
 * remain positioned key values—not field masks—and therefore expose no width.
 * @{
 */

// ==================================================================================================== //
//								Cyclic Redundancy Check (CRC) Register Defines							//
// ==================================================================================================== //

// ----------------------------------- CRC_DR Register Bit Defines ------------------------------------ //
/** @brief Bit position of the `CRC_DR_DR` field @def CRC_DR_DR_Pos */
#define CRC_DR_DR_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `CRC_DR_DR` field @def CRC_DR_DR_Width */
#define CRC_DR_DR_Width		((reg_field_width_t) 32U)
/** @brief Register-positioned mask for the `CRC_DR_DR` field @def CRC_DR_DR_Msk */
#define CRC_DR_DR_Msk		((reg) 0xFFFFFFFFUL)
/** @brief Data register bits @def CRC_DR_DR */
#define CRC_DR_DR			CRC_DR_DR_Msk

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
#define PWR_CR_PLS_LEV0		0x00000000U
/** @brief PVD level 2.3V @def PWR_CR_PLS_LEV1 */
#define PWR_CR_PLS_LEV1		0x00000020U
/** @brief PVD level 2.4V @def PWR_CR_PLS_LEV2 */
#define PWR_CR_PLS_LEV2		0x00000040U
/** @brief PVD level 2.5V @def PWR_CR_PLS_LEV3 */
#define PWR_CR_PLS_LEV3		0x00000060U
/** @brief PVD level 2.6V @def PWR_CR_PLS_LEV4 */
#define PWR_CR_PLS_LEV4		0x00000080U
/** @brief PVD level 2.7V @def PWR_CR_PLS_LEV5 */
#define PWR_CR_PLS_LEV5		0x000000A0U
/** @brief PVD level 2.8V @def PWR_CR_PLS_LEV6 */
#define PWR_CR_PLS_LEV6		0x000000C0U
/** @brief PVD level 2.9V @def PWR_CR_PLS_LEV7 */
#define PWR_CR_PLS_LEV7		0x000000E0U

// ----------------------------------- Legacy Compatibility Defines ----------------------------------- //
/** @brief Register or selector value represented by `PWR_CR_PLS_2V2` @def PWR_CR_PLS_2V2 */
#define PWR_CR_PLS_2V2		PWR_CR_PLS_LEV0
/** @brief Register or selector value represented by `PWR_CR_PLS_2V3` @def PWR_CR_PLS_2V3 */
#define PWR_CR_PLS_2V3		PWR_CR_PLS_LEV1
/** @brief Register or selector value represented by `PWR_CR_PLS_2V4` @def PWR_CR_PLS_2V4 */
#define PWR_CR_PLS_2V4		PWR_CR_PLS_LEV2
/** @brief Register or selector value represented by `PWR_CR_PLS_2V5` @def PWR_CR_PLS_2V5 */
#define PWR_CR_PLS_2V5		PWR_CR_PLS_LEV3
/** @brief Register or selector value represented by `PWR_CR_PLS_2V6` @def PWR_CR_PLS_2V6 */
#define PWR_CR_PLS_2V6		PWR_CR_PLS_LEV4
/** @brief Register or selector value represented by `PWR_CR_PLS_2V7` @def PWR_CR_PLS_2V7 */
#define PWR_CR_PLS_2V7		PWR_CR_PLS_LEV5
/** @brief Register or selector value represented by `PWR_CR_PLS_2V8` @def PWR_CR_PLS_2V8 */
#define PWR_CR_PLS_2V8		PWR_CR_PLS_LEV6
/** @brief Register or selector value represented by `PWR_CR_PLS_2V9` @def PWR_CR_PLS_2V9 */
#define PWR_CR_PLS_2V9		PWR_CR_PLS_LEV7

/** @brief Bit position of the `PWR_CR_DBP` field @def PWR_CR_DBP_Pos */
#define PWR_CR_DBP_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `PWR_CR_DBP` field @def PWR_CR_DBP_Msk */
#define PWR_CR_DBP_Msk		REG_BIT_MASK(PWR_CR_DBP_Pos)
/** @brief Disable Backup Domain write protection @def PWR_CR_DBP */
#define PWR_CR_DBP			PWR_CR_DBP_Msk

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
#define BKP_DR1_D_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `BKP_DR1_D` field @def BKP_DR1_D_Width */
#define BKP_DR1_D_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `BKP_DR1_D` field @def BKP_DR1_D_Msk */
#define BKP_DR1_D_Msk		REG_FIELD_MASK(BKP_DR1_D_Pos, BKP_DR1_D_Width)
/** @brief Backup data @def BKP_DR1_D */
#define BKP_DR1_D			BKP_DR1_D_Msk

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
//							Analog-to-Digital Converter (ADC) Register Defines							//
// ==================================================================================================== //

/*
 * @brief Specific device feature definitions (not present on all devices in the STM32F1 family)
 */
/** @brief ADC feature available only on specific devices: multimode available on devices with several ADC instances @def ADC_MULTIMODE_SUPPORT */
#define ADC_MULTIMODE_SUPPORT

// ----------------------------------- ADC_SR Register Bit Defines ------------------------------------ //
/** @brief Bit position of the `ADC_SR_AWD` field @def ADC_SR_AWD_Pos */
#define ADC_SR_AWD_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `ADC_SR_AWD` field @def ADC_SR_AWD_Msk */
#define ADC_SR_AWD_Msk			REG_BIT_MASK(ADC_SR_AWD_Pos)
/** @brief ADC analog watchdog 1 flag @def ADC_SR_AWD */
#define ADC_SR_AWD				ADC_SR_AWD_Msk
/** @brief Bit position of the `ADC_SR_EOS` field @def ADC_SR_EOS_Pos */
#define ADC_SR_EOS_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `ADC_SR_EOS` field @def ADC_SR_EOS_Msk */
#define ADC_SR_EOS_Msk			REG_BIT_MASK(ADC_SR_EOS_Pos)
/** @brief ADC group regular end of sequence conversions flag @def ADC_SR_EOS */
#define ADC_SR_EOS				ADC_SR_EOS_Msk
/** @brief Bit position of the `ADC_SR_JEOS` field @def ADC_SR_JEOS_Pos */
#define ADC_SR_JEOS_Pos			((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `ADC_SR_JEOS` field @def ADC_SR_JEOS_Msk */
#define ADC_SR_JEOS_Msk			REG_BIT_MASK(ADC_SR_JEOS_Pos)
/** @brief ADC group injected end of sequence conversions flag @def ADC_SR_JEOS */
#define ADC_SR_JEOS				ADC_SR_JEOS_Msk
/** @brief Bit position of the `ADC_SR_JSTRT` field @def ADC_SR_JSTRT_Pos */
#define ADC_SR_JSTRT_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `ADC_SR_JSTRT` field @def ADC_SR_JSTRT_Msk */
#define ADC_SR_JSTRT_Msk		REG_BIT_MASK(ADC_SR_JSTRT_Pos)
/** @brief ADC group injected conversion start flag @def ADC_SR_JSTRT */
#define ADC_SR_JSTRT			ADC_SR_JSTRT_Msk
/** @brief Bit position of the `ADC_SR_STRT` field @def ADC_SR_STRT_Pos */
#define ADC_SR_STRT_Pos			((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `ADC_SR_STRT` field @def ADC_SR_STRT_Msk */
#define ADC_SR_STRT_Msk			REG_BIT_MASK(ADC_SR_STRT_Pos)
/** @brief ADC group regular conversion start flag @def ADC_SR_STRT */
#define ADC_SR_STRT				ADC_SR_STRT_Msk

// ----------------------------------- Legacy Compatibility Defines ----------------------------------- //
/** @brief Register or selector value represented by `ADC_SR_EOC` @def ADC_SR_EOC */
#define ADC_SR_EOC		(ADC_SR_EOS)
/** @brief Register or selector value represented by `ADC_SR_JEOC` @def ADC_SR_JEOC */
#define ADC_SR_JEOC		(ADC_SR_JEOS)

// ----------------------------------- ADC_CR1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `ADC_CR1_AWDCH` field @def ADC_CR1_AWDCH_Pos */
#define ADC_CR1_AWDCH_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_CR1_AWDCH` field @def ADC_CR1_AWDCH_Width */
#define ADC_CR1_AWDCH_Width			((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_CR1_AWDCH` field @def ADC_CR1_AWDCH_Msk */
#define ADC_CR1_AWDCH_Msk			REG_FIELD_MASK(ADC_CR1_AWDCH_Pos, ADC_CR1_AWDCH_Width)
/** @brief ADC analog watchdog 1 monitored channel selection @def ADC_CR1_AWDCH */
#define ADC_CR1_AWDCH				ADC_CR1_AWDCH_Msk
/** @brief Register or selector value represented by `ADC_CR1_AWDCH_0` @def ADC_CR1_AWDCH_0 */
#define ADC_CR1_AWDCH_0				(0x01UL << ADC_CR1_AWDCH_Pos)
/** @brief Register or selector value represented by `ADC_CR1_AWDCH_1` @def ADC_CR1_AWDCH_1 */
#define ADC_CR1_AWDCH_1				(0x02UL << ADC_CR1_AWDCH_Pos)
/** @brief Register or selector value represented by `ADC_CR1_AWDCH_2` @def ADC_CR1_AWDCH_2 */
#define ADC_CR1_AWDCH_2				(0x04UL << ADC_CR1_AWDCH_Pos)
/** @brief Register or selector value represented by `ADC_CR1_AWDCH_3` @def ADC_CR1_AWDCH_3 */
#define ADC_CR1_AWDCH_3				(0x08UL << ADC_CR1_AWDCH_Pos)
/** @brief Register or selector value represented by `ADC_CR1_AWDCH_4` @def ADC_CR1_AWDCH_4 */
#define ADC_CR1_AWDCH_4				(0x10UL << ADC_CR1_AWDCH_Pos)

/** @brief Bit position of the `ADC_CR1_EOSIE` field @def ADC_CR1_EOSIE_Pos */
#define ADC_CR1_EOSIE_Pos			((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `ADC_CR1_EOSIE` field @def ADC_CR1_EOSIE_Msk */
#define ADC_CR1_EOSIE_Msk			REG_BIT_MASK(ADC_CR1_EOSIE_Pos)
/** @brief ADC group regular end of sequence conversions interrupt @def ADC_CR1_EOSIE */
#define ADC_CR1_EOSIE				ADC_CR1_EOSIE_Msk
/** @brief Bit position of the `ADC_CR1_AWDIE` field @def ADC_CR1_AWDIE_Pos */
#define ADC_CR1_AWDIE_Pos			((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `ADC_CR1_AWDIE` field @def ADC_CR1_AWDIE_Msk */
#define ADC_CR1_AWDIE_Msk			REG_BIT_MASK(ADC_CR1_AWDIE_Pos)
/** @brief ADC analog watchdog 1 interrupt @def ADC_CR1_AWDIE */
#define ADC_CR1_AWDIE				ADC_CR1_AWDIE_Msk
/** @brief Bit position of the `ADC_CR1_JEOSIE` field @def ADC_CR1_JEOSIE_Pos */
#define ADC_CR1_JEOSIE_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `ADC_CR1_JEOSIE` field @def ADC_CR1_JEOSIE_Msk */
#define ADC_CR1_JEOSIE_Msk			REG_BIT_MASK(ADC_CR1_JEOSIE_Pos)
/** @brief ADC group injected end of sequence conversions interrupt @def ADC_CR1_JEOSIE */
#define ADC_CR1_JEOSIE				ADC_CR1_JEOSIE_Msk
/** @brief Bit position of the `ADC_CR1_SCAN` field @def ADC_CR1_SCAN_Pos */
#define ADC_CR1_SCAN_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `ADC_CR1_SCAN` field @def ADC_CR1_SCAN_Msk */
#define ADC_CR1_SCAN_Msk			REG_BIT_MASK(ADC_CR1_SCAN_Pos)
/** @brief ADC scan mode @def ADC_CR1_SCAN */
#define ADC_CR1_SCAN				ADC_CR1_SCAN_Msk
/** @brief Bit position of the `ADC_CR1_AWDSGL` field @def ADC_CR1_AWDSGL_Pos */
#define ADC_CR1_AWDSGL_Pos			((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `ADC_CR1_AWDSGL` field @def ADC_CR1_AWDSGL_Msk */
#define ADC_CR1_AWDSGL_Msk			REG_BIT_MASK(ADC_CR1_AWDSGL_Pos)
/** @brief ADC analog watchdog 1 monitoring a single channel or all channels @def ADC_CR1_AWDSGL */
#define ADC_CR1_AWDSGL				ADC_CR1_AWDSGL_Msk
/** @brief Bit position of the `ADC_CR1_JAUTO` field @def ADC_CR1_JAUTO_Pos */
#define ADC_CR1_JAUTO_Pos			((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `ADC_CR1_JAUTO` field @def ADC_CR1_JAUTO_Msk */
#define ADC_CR1_JAUTO_Msk			REG_BIT_MASK(ADC_CR1_JAUTO_Pos)
/** @brief ADC group injected automatic trigger mode @def ADC_CR1_JAUTO */
#define ADC_CR1_JAUTO				ADC_CR1_JAUTO_Msk
/** @brief Bit position of the `ADC_CR1_DISCEN` field @def ADC_CR1_DISCEN_Pos */
#define ADC_CR1_DISCEN_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `ADC_CR1_DISCEN` field @def ADC_CR1_DISCEN_Msk */
#define ADC_CR1_DISCEN_Msk			REG_BIT_MASK(ADC_CR1_DISCEN_Pos)
/** @brief ADC group regular sequencer discontinuous mode @def ADC_CR1_DISCEN */
#define ADC_CR1_DISCEN				ADC_CR1_DISCEN_Msk
/** @brief Bit position of the `ADC_CR1_JDISCEN` field @def ADC_CR1_JDISCEN_Pos */
#define ADC_CR1_JDISCEN_Pos			((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `ADC_CR1_JDISCEN` field @def ADC_CR1_JDISCEN_Msk */
#define ADC_CR1_JDISCEN_Msk			REG_BIT_MASK(ADC_CR1_JDISCEN_Pos)
/** @brief ADC group injected sequencer discontinuous mode @def ADC_CR1_JDISCEN */
#define ADC_CR1_JDISCEN				ADC_CR1_JDISCEN_Msk

/** @brief Bit position of the `ADC_CR1_DISCNUM` field @def ADC_CR1_DISCNUM_Pos */
#define ADC_CR1_DISCNUM_Pos			((reg_bit_pos_t) 13U)
/** @brief Width of the `ADC_CR1_DISCNUM` field @def ADC_CR1_DISCNUM_Width */
#define ADC_CR1_DISCNUM_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_CR1_DISCNUM` field @def ADC_CR1_DISCNUM_Msk */
#define ADC_CR1_DISCNUM_Msk			REG_FIELD_MASK(ADC_CR1_DISCNUM_Pos, ADC_CR1_DISCNUM_Width)
/** @brief ADC group regular sequencer discontinuous number of ranks @def ADC_CR1_DISCNUM */
#define ADC_CR1_DISCNUM				ADC_CR1_DISCNUM_Msk
/** @brief Register or selector value represented by `ADC_CR1_DISCNUM_0` @def ADC_CR1_DISCNUM_0 */
#define ADC_CR1_DISCNUM_0			(0x1UL << ADC_CR1_DISCNUM_Pos)
/** @brief Register or selector value represented by `ADC_CR1_DISCNUM_1` @def ADC_CR1_DISCNUM_1 */
#define ADC_CR1_DISCNUM_1			(0x2UL << ADC_CR1_DISCNUM_Pos)
/** @brief Register or selector value represented by `ADC_CR1_DISCNUM_2` @def ADC_CR1_DISCNUM_2 */
#define ADC_CR1_DISCNUM_2			(0x4UL << ADC_CR1_DISCNUM_Pos)

/** @brief Bit position of the `ADC_CR1_DUALMOD` field @def ADC_CR1_DUALMOD_Pos */
#define ADC_CR1_DUALMOD_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `ADC_CR1_DUALMOD` field @def ADC_CR1_DUALMOD_Width */
#define ADC_CR1_DUALMOD_Width		((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `ADC_CR1_DUALMOD` field @def ADC_CR1_DUALMOD_Msk */
#define ADC_CR1_DUALMOD_Msk			REG_FIELD_MASK(ADC_CR1_DUALMOD_Pos, ADC_CR1_DUALMOD_Width)
/** @brief ADC multimode mode selection @def ADC_CR1_DUALMOD */
#define ADC_CR1_DUALMOD				ADC_CR1_DUALMOD_Msk
/** @brief Register or selector value represented by `ADC_CR1_DUALMOD_0` @def ADC_CR1_DUALMOD_0 */
#define ADC_CR1_DUALMOD_0			(0x1UL << ADC_CR1_DUALMOD_Pos)
/** @brief Register or selector value represented by `ADC_CR1_DUALMOD_1` @def ADC_CR1_DUALMOD_1 */
#define ADC_CR1_DUALMOD_1			(0x2UL << ADC_CR1_DUALMOD_Pos)
/** @brief Register or selector value represented by `ADC_CR1_DUALMOD_2` @def ADC_CR1_DUALMOD_2 */
#define ADC_CR1_DUALMOD_2			(0x4UL << ADC_CR1_DUALMOD_Pos)
/** @brief Register or selector value represented by `ADC_CR1_DUALMOD_3` @def ADC_CR1_DUALMOD_3 */
#define ADC_CR1_DUALMOD_3			(0x8UL << ADC_CR1_DUALMOD_Pos)

/** @brief Bit position of the `ADC_CR1_JAWDEN` field @def ADC_CR1_JAWDEN_Pos */
#define ADC_CR1_JAWDEN_Pos			((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `ADC_CR1_JAWDEN` field @def ADC_CR1_JAWDEN_Msk */
#define ADC_CR1_JAWDEN_Msk			REG_BIT_MASK(ADC_CR1_JAWDEN_Pos)
/** @brief ADC analog watchdog 1 enable on scope ADC group injected @def ADC_CR1_JAWDEN */
#define ADC_CR1_JAWDEN				ADC_CR1_JAWDEN_Msk
/** @brief Bit position of the `ADC_CR1_AWDEN` field @def ADC_CR1_AWDEN_Pos */
#define ADC_CR1_AWDEN_Pos			((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `ADC_CR1_AWDEN` field @def ADC_CR1_AWDEN_Msk */
#define ADC_CR1_AWDEN_Msk			REG_BIT_MASK(ADC_CR1_AWDEN_Pos)
/** @brief ADC analog watchdog 1 enable on scope ADC group regular @def ADC_CR1_AWDEN */
#define ADC_CR1_AWDEN				ADC_CR1_AWDEN_Msk

// ----------------------------------- Legacy Compatibility Defines ----------------------------------- //
/** @brief Register or selector value represented by `ADC_CR1_EOCIE` @def ADC_CR1_EOCIE */
#define ADC_CR1_EOCIE		(ADC_CR1_EOSIE)
/** @brief Register or selector value represented by `ADC_CR1_JEOCIE` @def ADC_CR1_JEOCIE */
#define ADC_CR1_JEOCIE		(ADC_CR1_JEOSIE)

// ----------------------------------- ADC_CR2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `ADC_CR2_ADON` field @def ADC_CR2_ADON_Pos */
#define ADC_CR2_ADON_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `ADC_CR2_ADON` field @def ADC_CR2_ADON_Msk */
#define ADC_CR2_ADON_Msk			REG_BIT_MASK(ADC_CR2_ADON_Pos)
/** @brief ADC enable @def ADC_CR2_ADON */
#define ADC_CR2_ADON				ADC_CR2_ADON_Msk
/** @brief Bit position of the `ADC_CR2_CONT` field @def ADC_CR2_CONT_Pos */
#define ADC_CR2_CONT_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `ADC_CR2_CONT` field @def ADC_CR2_CONT_Msk */
#define ADC_CR2_CONT_Msk			REG_BIT_MASK(ADC_CR2_CONT_Pos)
/** @brief ADC group regular continuous conversion mode @def ADC_CR2_CONT */
#define ADC_CR2_CONT				ADC_CR2_CONT_Msk
/** @brief Bit position of the `ADC_CR2_CAL` field @def ADC_CR2_CAL_Pos */
#define ADC_CR2_CAL_Pos				((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `ADC_CR2_CAL` field @def ADC_CR2_CAL_Msk */
#define ADC_CR2_CAL_Msk				REG_BIT_MASK(ADC_CR2_CAL_Pos)
/** @brief ADC calibration start @def ADC_CR2_CAL */
#define ADC_CR2_CAL					ADC_CR2_CAL_Msk
/** @brief Bit position of the `ADC_CR2_RSTCAL` field @def ADC_CR2_RSTCAL_Pos */
#define ADC_CR2_RSTCAL_Pos			((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `ADC_CR2_RSTCAL` field @def ADC_CR2_RSTCAL_Msk */
#define ADC_CR2_RSTCAL_Msk			REG_BIT_MASK(ADC_CR2_RSTCAL_Pos)
/** @brief ADC calibration reset @def ADC_CR2_RSTCAL */
#define ADC_CR2_RSTCAL				ADC_CR2_RSTCAL_Msk
/** @brief Bit position of the `ADC_CR2_DMA` field @def ADC_CR2_DMA_Pos */
#define ADC_CR2_DMA_Pos				((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `ADC_CR2_DMA` field @def ADC_CR2_DMA_Msk */
#define ADC_CR2_DMA_Msk				REG_BIT_MASK(ADC_CR2_DMA_Pos)
/** @brief ADC DMA transfer enable @def ADC_CR2_DMA */
#define ADC_CR2_DMA					ADC_CR2_DMA_Msk
/** @brief Bit position of the `ADC_CR2_ALIGN` field @def ADC_CR2_ALIGN_Pos */
#define ADC_CR2_ALIGN_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `ADC_CR2_ALIGN` field @def ADC_CR2_ALIGN_Msk */
#define ADC_CR2_ALIGN_Msk			REG_BIT_MASK(ADC_CR2_ALIGN_Pos)
/** @brief ADC data alignement @def ADC_CR2_ALIGN */
#define ADC_CR2_ALIGN				ADC_CR2_ALIGN_Msk

/** @brief Bit position of the `ADC_CR2_JEXTSEL` field @def ADC_CR2_JEXTSEL_Pos */
#define ADC_CR2_JEXTSEL_Pos			((reg_bit_pos_t) 12U)
/** @brief Width of the `ADC_CR2_JEXTSEL` field @def ADC_CR2_JEXTSEL_Width */
#define ADC_CR2_JEXTSEL_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_CR2_JEXTSEL` field @def ADC_CR2_JEXTSEL_Msk */
#define ADC_CR2_JEXTSEL_Msk			REG_FIELD_MASK(ADC_CR2_JEXTSEL_Pos, ADC_CR2_JEXTSEL_Width)
/** @brief ADC group injected external trigger source @def ADC_CR2_JEXTSEL */
#define ADC_CR2_JEXTSEL				ADC_CR2_JEXTSEL_Msk
/** @brief Register or selector value represented by `ADC_CR2_JEXTSEL_0` @def ADC_CR2_JEXTSEL_0 */
#define ADC_CR2_JEXTSEL_0			(0x1UL << ADC_CR2_JEXTSEL_Pos)
/** @brief Register or selector value represented by `ADC_CR2_JEXTSEL_1` @def ADC_CR2_JEXTSEL_1 */
#define ADC_CR2_JEXTSEL_1			(0x2UL << ADC_CR2_JEXTSEL_Pos)
/** @brief Register or selector value represented by `ADC_CR2_JEXTSEL_2` @def ADC_CR2_JEXTSEL_2 */
#define ADC_CR2_JEXTSEL_2			(0x4UL << ADC_CR2_JEXTSEL_Pos)

/** @brief Bit position of the `ADC_CR2_JEXTTRIG` field @def ADC_CR2_JEXTTRIG_Pos */
#define ADC_CR2_JEXTTRIG_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `ADC_CR2_JEXTTRIG` field @def ADC_CR2_JEXTTRIG_Msk */
#define ADC_CR2_JEXTTRIG_Msk		REG_BIT_MASK(ADC_CR2_JEXTTRIG_Pos)
/** @brief ADC group injected external trigger enable @def ADC_CR2_JEXTTRIG */
#define ADC_CR2_JEXTTRIG			ADC_CR2_JEXTTRIG_Msk

/** @brief Bit position of the `ADC_CR2_EXTSEL` field @def ADC_CR2_EXTSEL_Pos */
#define ADC_CR2_EXTSEL_Pos			((reg_bit_pos_t) 17U)
/** @brief Width of the `ADC_CR2_EXTSEL` field @def ADC_CR2_EXTSEL_Width */
#define ADC_CR2_EXTSEL_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_CR2_EXTSEL` field @def ADC_CR2_EXTSEL_Msk */
#define ADC_CR2_EXTSEL_Msk			REG_FIELD_MASK(ADC_CR2_EXTSEL_Pos, ADC_CR2_EXTSEL_Width)
/** @brief ADC group regular external trigger source @def ADC_CR2_EXTSEL */
#define ADC_CR2_EXTSEL				ADC_CR2_EXTSEL_Msk
/** @brief Register or selector value represented by `ADC_CR2_EXTSEL_0` @def ADC_CR2_EXTSEL_0 */
#define ADC_CR2_EXTSEL_0			(0x1UL << ADC_CR2_EXTSEL_Pos)
/** @brief Register or selector value represented by `ADC_CR2_EXTSEL_1` @def ADC_CR2_EXTSEL_1 */
#define ADC_CR2_EXTSEL_1			(0x2UL << ADC_CR2_EXTSEL_Pos)
/** @brief Register or selector value represented by `ADC_CR2_EXTSEL_2` @def ADC_CR2_EXTSEL_2 */
#define ADC_CR2_EXTSEL_2			(0x4UL << ADC_CR2_EXTSEL_Pos)

/** @brief Bit position of the `ADC_CR2_EXTTRIG` field @def ADC_CR2_EXTTRIG_Pos */
#define ADC_CR2_EXTTRIG_Pos			((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `ADC_CR2_EXTTRIG` field @def ADC_CR2_EXTTRIG_Msk */
#define ADC_CR2_EXTTRIG_Msk			REG_BIT_MASK(ADC_CR2_EXTTRIG_Pos)
/** @brief ADC group regular external trigger enable @def ADC_CR2_EXTTRIG */
#define ADC_CR2_EXTTRIG				ADC_CR2_EXTTRIG_Msk
/** @brief Bit position of the `ADC_CR2_JSWSTART` field @def ADC_CR2_JSWSTART_Pos */
#define ADC_CR2_JSWSTART_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `ADC_CR2_JSWSTART` field @def ADC_CR2_JSWSTART_Msk */
#define ADC_CR2_JSWSTART_Msk		REG_BIT_MASK(ADC_CR2_JSWSTART_Pos)
/** @brief ADC group injected conversion start @def ADC_CR2_JSWSTART */
#define ADC_CR2_JSWSTART			ADC_CR2_JSWSTART_Msk
/** @brief Bit position of the `ADC_CR2_SWSTART` field @def ADC_CR2_SWSTART_Pos */
#define ADC_CR2_SWSTART_Pos			((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `ADC_CR2_SWSTART` field @def ADC_CR2_SWSTART_Msk */
#define ADC_CR2_SWSTART_Msk			REG_BIT_MASK(ADC_CR2_SWSTART_Pos)
/** @brief ADC group regular conversion start @def ADC_CR2_SWSTART */
#define ADC_CR2_SWSTART				ADC_CR2_SWSTART_Msk
/** @brief Bit position of the `ADC_CR2_TSVREFE` field @def ADC_CR2_TSVREFE_Pos */
#define ADC_CR2_TSVREFE_Pos			((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `ADC_CR2_TSVREFE` field @def ADC_CR2_TSVREFE_Msk */
#define ADC_CR2_TSVREFE_Msk			REG_BIT_MASK(ADC_CR2_TSVREFE_Pos)
/** @brief ADC internal path to VrefInt and temperature sensor enable @def ADC_CR2_TSVREFE */
#define ADC_CR2_TSVREFE				ADC_CR2_TSVREFE_Msk

// ---------------------------------- ADC_SMPR1 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `ADC_SMPR1_SMP10` field @def ADC_SMPR1_SMP10_Pos */
#define ADC_SMPR1_SMP10_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_SMPR1_SMP10` field @def ADC_SMPR1_SMP10_Width */
#define ADC_SMPR1_SMP10_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR1_SMP10` field @def ADC_SMPR1_SMP10_Msk */
#define ADC_SMPR1_SMP10_Msk			REG_FIELD_MASK(ADC_SMPR1_SMP10_Pos, ADC_SMPR1_SMP10_Width)
/** @brief ADC channel 10 sampling time selection @def ADC_SMPR1_SMP10 */
#define ADC_SMPR1_SMP10				ADC_SMPR1_SMP10_Msk
/** @brief Register or selector value represented by `ADC_SMPR1_SMP10_0` @def ADC_SMPR1_SMP10_0 */
#define ADC_SMPR1_SMP10_0			(0x1UL << ADC_SMPR1_SMP10_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP10_1` @def ADC_SMPR1_SMP10_1 */
#define ADC_SMPR1_SMP10_1			(0x2UL << ADC_SMPR1_SMP10_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP10_2` @def ADC_SMPR1_SMP10_2 */
#define ADC_SMPR1_SMP10_2			(0x4UL << ADC_SMPR1_SMP10_Pos)

/** @brief Bit position of the `ADC_SMPR1_SMP11` field @def ADC_SMPR1_SMP11_Pos */
#define ADC_SMPR1_SMP11_Pos			((reg_bit_pos_t) 3U)
/** @brief Width of the `ADC_SMPR1_SMP11` field @def ADC_SMPR1_SMP11_Width */
#define ADC_SMPR1_SMP11_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR1_SMP11` field @def ADC_SMPR1_SMP11_Msk */
#define ADC_SMPR1_SMP11_Msk			REG_FIELD_MASK(ADC_SMPR1_SMP11_Pos, ADC_SMPR1_SMP11_Width)
/** @brief ADC channel 11 sampling time selection @def ADC_SMPR1_SMP11 */
#define ADC_SMPR1_SMP11				ADC_SMPR1_SMP11_Msk
/** @brief Register or selector value represented by `ADC_SMPR1_SMP11_0` @def ADC_SMPR1_SMP11_0 */
#define ADC_SMPR1_SMP11_0			(0x1UL << ADC_SMPR1_SMP11_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP11_1` @def ADC_SMPR1_SMP11_1 */
#define ADC_SMPR1_SMP11_1			(0x2UL << ADC_SMPR1_SMP11_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP11_2` @def ADC_SMPR1_SMP11_2 */
#define ADC_SMPR1_SMP11_2			(0x4UL << ADC_SMPR1_SMP11_Pos)

/** @brief Bit position of the `ADC_SMPR1_SMP12` field @def ADC_SMPR1_SMP12_Pos */
#define ADC_SMPR1_SMP12_Pos			((reg_bit_pos_t) 6U)
/** @brief Width of the `ADC_SMPR1_SMP12` field @def ADC_SMPR1_SMP12_Width */
#define ADC_SMPR1_SMP12_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR1_SMP12` field @def ADC_SMPR1_SMP12_Msk */
#define ADC_SMPR1_SMP12_Msk			REG_FIELD_MASK(ADC_SMPR1_SMP12_Pos, ADC_SMPR1_SMP12_Width)
/** @brief ADC channel 12 sampling time selection @def ADC_SMPR1_SMP12 */
#define ADC_SMPR1_SMP12				ADC_SMPR1_SMP12_Msk
/** @brief Register or selector value represented by `ADC_SMPR1_SMP12_0` @def ADC_SMPR1_SMP12_0 */
#define ADC_SMPR1_SMP12_0			(0x1UL << ADC_SMPR1_SMP12_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP12_1` @def ADC_SMPR1_SMP12_1 */
#define ADC_SMPR1_SMP12_1			(0x2UL << ADC_SMPR1_SMP12_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP12_2` @def ADC_SMPR1_SMP12_2 */
#define ADC_SMPR1_SMP12_2			(0x4UL << ADC_SMPR1_SMP12_Pos)

/** @brief Bit position of the `ADC_SMPR1_SMP13` field @def ADC_SMPR1_SMP13_Pos */
#define ADC_SMPR1_SMP13_Pos			((reg_bit_pos_t) 9U)
/** @brief Width of the `ADC_SMPR1_SMP13` field @def ADC_SMPR1_SMP13_Width */
#define ADC_SMPR1_SMP13_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR1_SMP13` field @def ADC_SMPR1_SMP13_Msk */
#define ADC_SMPR1_SMP13_Msk			REG_FIELD_MASK(ADC_SMPR1_SMP13_Pos, ADC_SMPR1_SMP13_Width)
/** @brief ADC channel 13 sampling time selection @def ADC_SMPR1_SMP13 */
#define ADC_SMPR1_SMP13				ADC_SMPR1_SMP13_Msk
/** @brief Register or selector value represented by `ADC_SMPR1_SMP13_0` @def ADC_SMPR1_SMP13_0 */
#define ADC_SMPR1_SMP13_0			(0x1UL << ADC_SMPR1_SMP13_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP13_1` @def ADC_SMPR1_SMP13_1 */
#define ADC_SMPR1_SMP13_1			(0x2UL << ADC_SMPR1_SMP13_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP13_2` @def ADC_SMPR1_SMP13_2 */
#define ADC_SMPR1_SMP13_2			(0x4UL << ADC_SMPR1_SMP13_Pos)

/** @brief Bit position of the `ADC_SMPR1_SMP14` field @def ADC_SMPR1_SMP14_Pos */
#define ADC_SMPR1_SMP14_Pos			((reg_bit_pos_t) 12U)
/** @brief Width of the `ADC_SMPR1_SMP14` field @def ADC_SMPR1_SMP14_Width */
#define ADC_SMPR1_SMP14_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR1_SMP14` field @def ADC_SMPR1_SMP14_Msk */
#define ADC_SMPR1_SMP14_Msk			REG_FIELD_MASK(ADC_SMPR1_SMP14_Pos, ADC_SMPR1_SMP14_Width)
/** @brief ADC channel 14 sampling time selection @def ADC_SMPR1_SMP14 */
#define ADC_SMPR1_SMP14				ADC_SMPR1_SMP14_Msk
/** @brief Register or selector value represented by `ADC_SMPR1_SMP14_0` @def ADC_SMPR1_SMP14_0 */
#define ADC_SMPR1_SMP14_0			(0x1UL << ADC_SMPR1_SMP14_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP14_1` @def ADC_SMPR1_SMP14_1 */
#define ADC_SMPR1_SMP14_1			(0x2UL << ADC_SMPR1_SMP14_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP14_2` @def ADC_SMPR1_SMP14_2 */
#define ADC_SMPR1_SMP14_2			(0x4UL << ADC_SMPR1_SMP14_Pos)

/** @brief Bit position of the `ADC_SMPR1_SMP15` field @def ADC_SMPR1_SMP15_Pos */
#define ADC_SMPR1_SMP15_Pos			((reg_bit_pos_t) 15U)
/** @brief Width of the `ADC_SMPR1_SMP15` field @def ADC_SMPR1_SMP15_Width */
#define ADC_SMPR1_SMP15_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR1_SMP15` field @def ADC_SMPR1_SMP15_Msk */
#define ADC_SMPR1_SMP15_Msk			REG_FIELD_MASK(ADC_SMPR1_SMP15_Pos, ADC_SMPR1_SMP15_Width)
/** @brief ADC channel 15 sampling time selection @def ADC_SMPR1_SMP15 */
#define ADC_SMPR1_SMP15				ADC_SMPR1_SMP15_Msk
/** @brief Register or selector value represented by `ADC_SMPR1_SMP15_0` @def ADC_SMPR1_SMP15_0 */
#define ADC_SMPR1_SMP15_0			(0x1UL << ADC_SMPR1_SMP15_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP15_1` @def ADC_SMPR1_SMP15_1 */
#define ADC_SMPR1_SMP15_1			(0x2UL << ADC_SMPR1_SMP15_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP15_2` @def ADC_SMPR1_SMP15_2 */
#define ADC_SMPR1_SMP15_2			(0x4UL << ADC_SMPR1_SMP15_Pos)

/** @brief Bit position of the `ADC_SMPR1_SMP16` field @def ADC_SMPR1_SMP16_Pos */
#define ADC_SMPR1_SMP16_Pos			((reg_bit_pos_t) 18U)
/** @brief Width of the `ADC_SMPR1_SMP16` field @def ADC_SMPR1_SMP16_Width */
#define ADC_SMPR1_SMP16_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR1_SMP16` field @def ADC_SMPR1_SMP16_Msk */
#define ADC_SMPR1_SMP16_Msk			REG_FIELD_MASK(ADC_SMPR1_SMP16_Pos, ADC_SMPR1_SMP16_Width)
/** @brief ADC channel 16 sampling time selection @def ADC_SMPR1_SMP16 */
#define ADC_SMPR1_SMP16				ADC_SMPR1_SMP16_Msk
/** @brief Register or selector value represented by `ADC_SMPR1_SMP16_0` @def ADC_SMPR1_SMP16_0 */
#define ADC_SMPR1_SMP16_0			(0x1UL << ADC_SMPR1_SMP16_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP16_1` @def ADC_SMPR1_SMP16_1 */
#define ADC_SMPR1_SMP16_1			(0x2UL << ADC_SMPR1_SMP16_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP16_2` @def ADC_SMPR1_SMP16_2 */
#define ADC_SMPR1_SMP16_2			(0x4UL << ADC_SMPR1_SMP16_Pos)

/** @brief Bit position of the `ADC_SMPR1_SMP17` field @def ADC_SMPR1_SMP17_Pos */
#define ADC_SMPR1_SMP17_Pos			((reg_bit_pos_t) 21U)
/** @brief Width of the `ADC_SMPR1_SMP17` field @def ADC_SMPR1_SMP17_Width */
#define ADC_SMPR1_SMP17_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR1_SMP17` field @def ADC_SMPR1_SMP17_Msk */
#define ADC_SMPR1_SMP17_Msk			REG_FIELD_MASK(ADC_SMPR1_SMP17_Pos, ADC_SMPR1_SMP17_Width)
/** @brief ADC channel 17 sampling time selection @def ADC_SMPR1_SMP17 */
#define ADC_SMPR1_SMP17				ADC_SMPR1_SMP17_Msk
/** @brief Register or selector value represented by `ADC_SMPR1_SMP17_0` @def ADC_SMPR1_SMP17_0 */
#define ADC_SMPR1_SMP17_0			(0x1UL << ADC_SMPR1_SMP17_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP17_1` @def ADC_SMPR1_SMP17_1 */
#define ADC_SMPR1_SMP17_1			(0x2UL << ADC_SMPR1_SMP17_Pos)
/** @brief Register or selector value represented by `ADC_SMPR1_SMP17_2` @def ADC_SMPR1_SMP17_2 */
#define ADC_SMPR1_SMP17_2			(0x4UL << ADC_SMPR1_SMP17_Pos)

// ---------------------------------- ADC_SMPR2 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `ADC_SMPR2_SMP0` field @def ADC_SMPR2_SMP0_Pos */
#define ADC_SMPR2_SMP0_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_SMPR2_SMP0` field @def ADC_SMPR2_SMP0_Width */
#define ADC_SMPR2_SMP0_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR2_SMP0` field @def ADC_SMPR2_SMP0_Msk */
#define ADC_SMPR2_SMP0_Msk			REG_FIELD_MASK(ADC_SMPR2_SMP0_Pos, ADC_SMPR2_SMP0_Width)
/** @brief ADC channel 0 sampling time selection @def ADC_SMPR2_SMP0 */
#define ADC_SMPR2_SMP0				ADC_SMPR2_SMP0_Msk
/** @brief Register or selector value represented by `ADC_SMPR2_SMP0_0` @def ADC_SMPR2_SMP0_0 */
#define ADC_SMPR2_SMP0_0			(0x1UL << ADC_SMPR2_SMP0_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP0_1` @def ADC_SMPR2_SMP0_1 */
#define ADC_SMPR2_SMP0_1			(0x2UL << ADC_SMPR2_SMP0_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP0_2` @def ADC_SMPR2_SMP0_2 */
#define ADC_SMPR2_SMP0_2			(0x4UL << ADC_SMPR2_SMP0_Pos)

/** @brief Bit position of the `ADC_SMPR2_SMP1` field @def ADC_SMPR2_SMP1_Pos */
#define ADC_SMPR2_SMP1_Pos			((reg_bit_pos_t) 3U)
/** @brief Width of the `ADC_SMPR2_SMP1` field @def ADC_SMPR2_SMP1_Width */
#define ADC_SMPR2_SMP1_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR2_SMP1` field @def ADC_SMPR2_SMP1_Msk */
#define ADC_SMPR2_SMP1_Msk			REG_FIELD_MASK(ADC_SMPR2_SMP1_Pos, ADC_SMPR2_SMP1_Width)
/** @brief ADC channel 1 sampling time selection @def ADC_SMPR2_SMP1 */
#define ADC_SMPR2_SMP1				ADC_SMPR2_SMP1_Msk
/** @brief Register or selector value represented by `ADC_SMPR2_SMP1_0` @def ADC_SMPR2_SMP1_0 */
#define ADC_SMPR2_SMP1_0			(0x1UL << ADC_SMPR2_SMP1_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP1_1` @def ADC_SMPR2_SMP1_1 */
#define ADC_SMPR2_SMP1_1			(0x2UL << ADC_SMPR2_SMP1_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP1_2` @def ADC_SMPR2_SMP1_2 */
#define ADC_SMPR2_SMP1_2			(0x4UL << ADC_SMPR2_SMP1_Pos)

/** @brief Bit position of the `ADC_SMPR2_SMP2` field @def ADC_SMPR2_SMP2_Pos */
#define ADC_SMPR2_SMP2_Pos			((reg_bit_pos_t) 6U)
/** @brief Width of the `ADC_SMPR2_SMP2` field @def ADC_SMPR2_SMP2_Width */
#define ADC_SMPR2_SMP2_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR2_SMP2` field @def ADC_SMPR2_SMP2_Msk */
#define ADC_SMPR2_SMP2_Msk			REG_FIELD_MASK(ADC_SMPR2_SMP2_Pos, ADC_SMPR2_SMP2_Width)
/** @brief ADC channel 2 sampling time selection @def ADC_SMPR2_SMP2 */
#define ADC_SMPR2_SMP2				ADC_SMPR2_SMP2_Msk
/** @brief Register or selector value represented by `ADC_SMPR2_SMP2_0` @def ADC_SMPR2_SMP2_0 */
#define ADC_SMPR2_SMP2_0			(0x1UL << ADC_SMPR2_SMP2_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP2_1` @def ADC_SMPR2_SMP2_1 */
#define ADC_SMPR2_SMP2_1			(0x2UL << ADC_SMPR2_SMP2_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP2_2` @def ADC_SMPR2_SMP2_2 */
#define ADC_SMPR2_SMP2_2			(0x4UL << ADC_SMPR2_SMP2_Pos)

/** @brief Bit position of the `ADC_SMPR2_SMP3` field @def ADC_SMPR2_SMP3_Pos */
#define ADC_SMPR2_SMP3_Pos			((reg_bit_pos_t) 9U)
/** @brief Width of the `ADC_SMPR2_SMP3` field @def ADC_SMPR2_SMP3_Width */
#define ADC_SMPR2_SMP3_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR2_SMP3` field @def ADC_SMPR2_SMP3_Msk */
#define ADC_SMPR2_SMP3_Msk			REG_FIELD_MASK(ADC_SMPR2_SMP3_Pos, ADC_SMPR2_SMP3_Width)
/** @brief ADC channel 3 sampling time selection @def ADC_SMPR2_SMP3 */
#define ADC_SMPR2_SMP3				ADC_SMPR2_SMP3_Msk
/** @brief Register or selector value represented by `ADC_SMPR2_SMP3_0` @def ADC_SMPR2_SMP3_0 */
#define ADC_SMPR2_SMP3_0			(0x1UL << ADC_SMPR2_SMP3_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP3_1` @def ADC_SMPR2_SMP3_1 */
#define ADC_SMPR2_SMP3_1			(0x2UL << ADC_SMPR2_SMP3_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP3_2` @def ADC_SMPR2_SMP3_2 */
#define ADC_SMPR2_SMP3_2			(0x4UL << ADC_SMPR2_SMP3_Pos)

/** @brief Bit position of the `ADC_SMPR2_SMP4` field @def ADC_SMPR2_SMP4_Pos */
#define ADC_SMPR2_SMP4_Pos			((reg_bit_pos_t) 12U)
/** @brief Width of the `ADC_SMPR2_SMP4` field @def ADC_SMPR2_SMP4_Width */
#define ADC_SMPR2_SMP4_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR2_SMP4` field @def ADC_SMPR2_SMP4_Msk */
#define ADC_SMPR2_SMP4_Msk			REG_FIELD_MASK(ADC_SMPR2_SMP4_Pos, ADC_SMPR2_SMP4_Width)
/** @brief ADC channel 4 sampling time selection @def ADC_SMPR2_SMP4 */
#define ADC_SMPR2_SMP4				ADC_SMPR2_SMP4_Msk
/** @brief Register or selector value represented by `ADC_SMPR2_SMP4_0` @def ADC_SMPR2_SMP4_0 */
#define ADC_SMPR2_SMP4_0			(0x1UL << ADC_SMPR2_SMP4_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP4_1` @def ADC_SMPR2_SMP4_1 */
#define ADC_SMPR2_SMP4_1			(0x2UL << ADC_SMPR2_SMP4_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP4_2` @def ADC_SMPR2_SMP4_2 */
#define ADC_SMPR2_SMP4_2			(0x4UL << ADC_SMPR2_SMP4_Pos)

/** @brief Bit position of the `ADC_SMPR2_SMP5` field @def ADC_SMPR2_SMP5_Pos */
#define ADC_SMPR2_SMP5_Pos			((reg_bit_pos_t) 15U)
/** @brief Width of the `ADC_SMPR2_SMP5` field @def ADC_SMPR2_SMP5_Width */
#define ADC_SMPR2_SMP5_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR2_SMP5` field @def ADC_SMPR2_SMP5_Msk */
#define ADC_SMPR2_SMP5_Msk			REG_FIELD_MASK(ADC_SMPR2_SMP5_Pos, ADC_SMPR2_SMP5_Width)
/** @brief ADC channel 5 sampling time selection @def ADC_SMPR2_SMP5 */
#define ADC_SMPR2_SMP5				ADC_SMPR2_SMP5_Msk
/** @brief Register or selector value represented by `ADC_SMPR2_SMP5_0` @def ADC_SMPR2_SMP5_0 */
#define ADC_SMPR2_SMP5_0			(0x1UL << ADC_SMPR2_SMP5_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP5_1` @def ADC_SMPR2_SMP5_1 */
#define ADC_SMPR2_SMP5_1			(0x2UL << ADC_SMPR2_SMP5_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP5_2` @def ADC_SMPR2_SMP5_2 */
#define ADC_SMPR2_SMP5_2			(0x4UL << ADC_SMPR2_SMP5_Pos)

/** @brief Bit position of the `ADC_SMPR2_SMP6` field @def ADC_SMPR2_SMP6_Pos */
#define ADC_SMPR2_SMP6_Pos			((reg_bit_pos_t) 18U)
/** @brief Width of the `ADC_SMPR2_SMP6` field @def ADC_SMPR2_SMP6_Width */
#define ADC_SMPR2_SMP6_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR2_SMP6` field @def ADC_SMPR2_SMP6_Msk */
#define ADC_SMPR2_SMP6_Msk			REG_FIELD_MASK(ADC_SMPR2_SMP6_Pos, ADC_SMPR2_SMP6_Width)
/** @brief ADC channel 6 sampling time selection @def ADC_SMPR2_SMP6 */
#define ADC_SMPR2_SMP6				ADC_SMPR2_SMP6_Msk
/** @brief Register or selector value represented by `ADC_SMPR2_SMP6_0` @def ADC_SMPR2_SMP6_0 */
#define ADC_SMPR2_SMP6_0			(0x1UL << ADC_SMPR2_SMP6_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP6_1` @def ADC_SMPR2_SMP6_1 */
#define ADC_SMPR2_SMP6_1			(0x2UL << ADC_SMPR2_SMP6_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP6_2` @def ADC_SMPR2_SMP6_2 */
#define ADC_SMPR2_SMP6_2			(0x4UL << ADC_SMPR2_SMP6_Pos)

/** @brief Bit position of the `ADC_SMPR2_SMP7` field @def ADC_SMPR2_SMP7_Pos */
#define ADC_SMPR2_SMP7_Pos			((reg_bit_pos_t) 21U)
/** @brief Width of the `ADC_SMPR2_SMP7` field @def ADC_SMPR2_SMP7_Width */
#define ADC_SMPR2_SMP7_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR2_SMP7` field @def ADC_SMPR2_SMP7_Msk */
#define ADC_SMPR2_SMP7_Msk			REG_FIELD_MASK(ADC_SMPR2_SMP7_Pos, ADC_SMPR2_SMP7_Width)
/** @brief ADC channel 7 sampling time selection @def ADC_SMPR2_SMP7 */
#define ADC_SMPR2_SMP7				ADC_SMPR2_SMP7_Msk
/** @brief Register or selector value represented by `ADC_SMPR2_SMP7_0` @def ADC_SMPR2_SMP7_0 */
#define ADC_SMPR2_SMP7_0			(0x1UL << ADC_SMPR2_SMP7_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP7_1` @def ADC_SMPR2_SMP7_1 */
#define ADC_SMPR2_SMP7_1			(0x2UL << ADC_SMPR2_SMP7_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP7_2` @def ADC_SMPR2_SMP7_2 */
#define ADC_SMPR2_SMP7_2			(0x4UL << ADC_SMPR2_SMP7_Pos)

/** @brief Bit position of the `ADC_SMPR2_SMP8` field @def ADC_SMPR2_SMP8_Pos */
#define ADC_SMPR2_SMP8_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `ADC_SMPR2_SMP8` field @def ADC_SMPR2_SMP8_Width */
#define ADC_SMPR2_SMP8_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR2_SMP8` field @def ADC_SMPR2_SMP8_Msk */
#define ADC_SMPR2_SMP8_Msk			REG_FIELD_MASK(ADC_SMPR2_SMP8_Pos, ADC_SMPR2_SMP8_Width)
/** @brief ADC channel 8 sampling time selection @def ADC_SMPR2_SMP8 */
#define ADC_SMPR2_SMP8				ADC_SMPR2_SMP8_Msk
/** @brief Register or selector value represented by `ADC_SMPR2_SMP8_0` @def ADC_SMPR2_SMP8_0 */
#define ADC_SMPR2_SMP8_0			(0x1UL << ADC_SMPR2_SMP8_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP8_1` @def ADC_SMPR2_SMP8_1 */
#define ADC_SMPR2_SMP8_1			(0x2UL << ADC_SMPR2_SMP8_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP8_2` @def ADC_SMPR2_SMP8_2 */
#define ADC_SMPR2_SMP8_2			(0x4UL << ADC_SMPR2_SMP8_Pos)

/** @brief Bit position of the `ADC_SMPR2_SMP9` field @def ADC_SMPR2_SMP9_Pos */
#define ADC_SMPR2_SMP9_Pos			((reg_bit_pos_t) 27U)
/** @brief Width of the `ADC_SMPR2_SMP9` field @def ADC_SMPR2_SMP9_Width */
#define ADC_SMPR2_SMP9_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `ADC_SMPR2_SMP9` field @def ADC_SMPR2_SMP9_Msk */
#define ADC_SMPR2_SMP9_Msk			REG_FIELD_MASK(ADC_SMPR2_SMP9_Pos, ADC_SMPR2_SMP9_Width)
/** @brief ADC channel 9 sampling time selection @def ADC_SMPR2_SMP9 */
#define ADC_SMPR2_SMP9				ADC_SMPR2_SMP9_Msk
/** @brief Register or selector value represented by `ADC_SMPR2_SMP9_0` @def ADC_SMPR2_SMP9_0 */
#define ADC_SMPR2_SMP9_0			(0x1UL << ADC_SMPR2_SMP9_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP9_1` @def ADC_SMPR2_SMP9_1 */
#define ADC_SMPR2_SMP9_1			(0x2UL << ADC_SMPR2_SMP9_Pos)
/** @brief Register or selector value represented by `ADC_SMPR2_SMP9_2` @def ADC_SMPR2_SMP9_2 */
#define ADC_SMPR2_SMP9_2			(0x4UL << ADC_SMPR2_SMP9_Pos)

// ---------------------------------- ADC_JOFR1 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `ADC_JOFR1_JOFFSET1` field @def ADC_JOFR1_JOFFSET1_Pos */
#define ADC_JOFR1_JOFFSET1_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_JOFR1_JOFFSET1` field @def ADC_JOFR1_JOFFSET1_Width */
#define ADC_JOFR1_JOFFSET1_Width		((reg_field_width_t) 12U)
/** @brief Register-positioned mask for the `ADC_JOFR1_JOFFSET1` field @def ADC_JOFR1_JOFFSET1_Msk */
#define ADC_JOFR1_JOFFSET1_Msk			REG_FIELD_MASK(ADC_JOFR1_JOFFSET1_Pos, ADC_JOFR1_JOFFSET1_Width)
/** @brief ADC group injected sequencer rank 1 offset value @def ADC_JOFR1_JOFFSET1 */
#define ADC_JOFR1_JOFFSET1				ADC_JOFR1_JOFFSET1_Msk

// ---------------------------------- ADC_JOFR2 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `ADC_JOFR2_JOFFSET2` field @def ADC_JOFR2_JOFFSET2_Pos */
#define ADC_JOFR2_JOFFSET2_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_JOFR2_JOFFSET2` field @def ADC_JOFR2_JOFFSET2_Width */
#define ADC_JOFR2_JOFFSET2_Width		((reg_field_width_t) 12U)
/** @brief Register-positioned mask for the `ADC_JOFR2_JOFFSET2` field @def ADC_JOFR2_JOFFSET2_Msk */
#define ADC_JOFR2_JOFFSET2_Msk			REG_FIELD_MASK(ADC_JOFR2_JOFFSET2_Pos, ADC_JOFR2_JOFFSET2_Width)
/** @brief ADC group injected sequencer rank 2 offset value @def ADC_JOFR2_JOFFSET2 */
#define ADC_JOFR2_JOFFSET2				ADC_JOFR2_JOFFSET2_Msk

// ---------------------------------- ADC_JOFR3 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `ADC_JOFR3_JOFFSET3` field @def ADC_JOFR3_JOFFSET3_Pos */
#define ADC_JOFR3_JOFFSET3_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_JOFR3_JOFFSET3` field @def ADC_JOFR3_JOFFSET3_Width */
#define ADC_JOFR3_JOFFSET3_Width		((reg_field_width_t) 12U)
/** @brief Register-positioned mask for the `ADC_JOFR3_JOFFSET3` field @def ADC_JOFR3_JOFFSET3_Msk */
#define ADC_JOFR3_JOFFSET3_Msk			REG_FIELD_MASK(ADC_JOFR3_JOFFSET3_Pos, ADC_JOFR3_JOFFSET3_Width)
/** @brief ADC group injected sequencer rank 3 offset value @def ADC_JOFR3_JOFFSET3 */
#define ADC_JOFR3_JOFFSET3				ADC_JOFR3_JOFFSET3_Msk

// ---------------------------------- ADC_JOFR4 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `ADC_JOFR4_JOFFSET4` field @def ADC_JOFR4_JOFFSET4_Pos */
#define ADC_JOFR4_JOFFSET4_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_JOFR4_JOFFSET4` field @def ADC_JOFR4_JOFFSET4_Width */
#define ADC_JOFR4_JOFFSET4_Width		((reg_field_width_t) 12U)
/** @brief Register-positioned mask for the `ADC_JOFR4_JOFFSET4` field @def ADC_JOFR4_JOFFSET4_Msk */
#define ADC_JOFR4_JOFFSET4_Msk			REG_FIELD_MASK(ADC_JOFR4_JOFFSET4_Pos, ADC_JOFR4_JOFFSET4_Width)
/** @brief ADC group injected sequencer rank 4 offset value @def ADC_JOFR4_JOFFSET4 */
#define ADC_JOFR4_JOFFSET4				ADC_JOFR4_JOFFSET4_Msk

// ----------------------------------- ADC_HTR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `ADC_HTR_HT` field @def ADC_HTR_HT_Pos */
#define ADC_HTR_HT_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_HTR_HT` field @def ADC_HTR_HT_Width */
#define ADC_HTR_HT_Width		((reg_field_width_t) 12U)
/** @brief Register-positioned mask for the `ADC_HTR_HT` field @def ADC_HTR_HT_Msk */
#define ADC_HTR_HT_Msk			REG_FIELD_MASK(ADC_HTR_HT_Pos, ADC_HTR_HT_Width)
/** @brief ADC analog watchdog 1 threshold high @def ADC_HTR_HT */
#define ADC_HTR_HT				ADC_HTR_HT_Msk

// ----------------------------------- ADC_LTR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `ADC_LTR_LT` field @def ADC_LTR_LT_Pos */
#define ADC_LTR_LT_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_LTR_LT` field @def ADC_LTR_LT_Width */
#define ADC_LTR_LT_Width		((reg_field_width_t) 12U)
/** @brief Register-positioned mask for the `ADC_LTR_LT` field @def ADC_LTR_LT_Msk */
#define ADC_LTR_LT_Msk			REG_FIELD_MASK(ADC_LTR_LT_Pos, ADC_LTR_LT_Width)
/** @brief ADC analog watchdog 1 threshold low @def ADC_LTR_LT */
#define ADC_LTR_LT				ADC_LTR_LT_Msk

// ---------------------------------- ADC_SQR1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `ADC_SQR1_SQ13` field @def ADC_SQR1_SQ13_Pos */
#define ADC_SQR1_SQ13_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_SQR1_SQ13` field @def ADC_SQR1_SQ13_Width */
#define ADC_SQR1_SQ13_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR1_SQ13` field @def ADC_SQR1_SQ13_Msk */
#define ADC_SQR1_SQ13_Msk		REG_FIELD_MASK(ADC_SQR1_SQ13_Pos, ADC_SQR1_SQ13_Width)
/** @brief ADC group regular sequencer rank 13 @def ADC_SQR1_SQ13 */
#define ADC_SQR1_SQ13			ADC_SQR1_SQ13_Msk
/** @brief Register or selector value represented by `ADC_SQR1_SQ13_0` @def ADC_SQR1_SQ13_0 */
#define ADC_SQR1_SQ13_0			(0x01UL << ADC_SQR1_SQ13_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ13_1` @def ADC_SQR1_SQ13_1 */
#define ADC_SQR1_SQ13_1			(0x02UL << ADC_SQR1_SQ13_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ13_2` @def ADC_SQR1_SQ13_2 */
#define ADC_SQR1_SQ13_2			(0x04UL << ADC_SQR1_SQ13_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ13_3` @def ADC_SQR1_SQ13_3 */
#define ADC_SQR1_SQ13_3			(0x08UL << ADC_SQR1_SQ13_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ13_4` @def ADC_SQR1_SQ13_4 */
#define ADC_SQR1_SQ13_4			(0x10UL << ADC_SQR1_SQ13_Pos)

/** @brief Bit position of the `ADC_SQR1_SQ14` field @def ADC_SQR1_SQ14_Pos */
#define ADC_SQR1_SQ14_Pos		((reg_bit_pos_t) 5U)
/** @brief Width of the `ADC_SQR1_SQ14` field @def ADC_SQR1_SQ14_Width */
#define ADC_SQR1_SQ14_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR1_SQ14` field @def ADC_SQR1_SQ14_Msk */
#define ADC_SQR1_SQ14_Msk		REG_FIELD_MASK(ADC_SQR1_SQ14_Pos, ADC_SQR1_SQ14_Width)
/** @brief ADC group regular sequencer rank 14 @def ADC_SQR1_SQ14 */
#define ADC_SQR1_SQ14			ADC_SQR1_SQ14_Msk
/** @brief Register or selector value represented by `ADC_SQR1_SQ14_0` @def ADC_SQR1_SQ14_0 */
#define ADC_SQR1_SQ14_0			(0x01UL << ADC_SQR1_SQ14_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ14_1` @def ADC_SQR1_SQ14_1 */
#define ADC_SQR1_SQ14_1			(0x02UL << ADC_SQR1_SQ14_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ14_2` @def ADC_SQR1_SQ14_2 */
#define ADC_SQR1_SQ14_2			(0x04UL << ADC_SQR1_SQ14_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ14_3` @def ADC_SQR1_SQ14_3 */
#define ADC_SQR1_SQ14_3			(0x08UL << ADC_SQR1_SQ14_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ14_4` @def ADC_SQR1_SQ14_4 */
#define ADC_SQR1_SQ14_4			(0x10UL << ADC_SQR1_SQ14_Pos)

/** @brief Bit position of the `ADC_SQR1_SQ15` field @def ADC_SQR1_SQ15_Pos */
#define ADC_SQR1_SQ15_Pos		((reg_bit_pos_t) 10U)
/** @brief Width of the `ADC_SQR1_SQ15` field @def ADC_SQR1_SQ15_Width */
#define ADC_SQR1_SQ15_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR1_SQ15` field @def ADC_SQR1_SQ15_Msk */
#define ADC_SQR1_SQ15_Msk		REG_FIELD_MASK(ADC_SQR1_SQ15_Pos, ADC_SQR1_SQ15_Width)
/** @brief ADC group regular sequencer rank 15 @def ADC_SQR1_SQ15 */
#define ADC_SQR1_SQ15			ADC_SQR1_SQ15_Msk
/** @brief Register or selector value represented by `ADC_SQR1_SQ15_0` @def ADC_SQR1_SQ15_0 */
#define ADC_SQR1_SQ15_0			(0x01UL << ADC_SQR1_SQ15_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ15_1` @def ADC_SQR1_SQ15_1 */
#define ADC_SQR1_SQ15_1			(0x02UL << ADC_SQR1_SQ15_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ15_2` @def ADC_SQR1_SQ15_2 */
#define ADC_SQR1_SQ15_2			(0x04UL << ADC_SQR1_SQ15_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ15_3` @def ADC_SQR1_SQ15_3 */
#define ADC_SQR1_SQ15_3			(0x08UL << ADC_SQR1_SQ15_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ15_4` @def ADC_SQR1_SQ15_4 */
#define ADC_SQR1_SQ15_4			(0x10UL << ADC_SQR1_SQ15_Pos)

/** @brief Bit position of the `ADC_SQR1_SQ16` field @def ADC_SQR1_SQ16_Pos */
#define ADC_SQR1_SQ16_Pos		((reg_bit_pos_t) 15U)
/** @brief Width of the `ADC_SQR1_SQ16` field @def ADC_SQR1_SQ16_Width */
#define ADC_SQR1_SQ16_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR1_SQ16` field @def ADC_SQR1_SQ16_Msk */
#define ADC_SQR1_SQ16_Msk		REG_FIELD_MASK(ADC_SQR1_SQ16_Pos, ADC_SQR1_SQ16_Width)
/** @brief ADC group regular sequencer rank 16 @def ADC_SQR1_SQ16 */
#define ADC_SQR1_SQ16			ADC_SQR1_SQ16_Msk
/** @brief Register or selector value represented by `ADC_SQR1_SQ16_0` @def ADC_SQR1_SQ16_0 */
#define ADC_SQR1_SQ16_0			(0x01UL << ADC_SQR1_SQ16_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ16_1` @def ADC_SQR1_SQ16_1 */
#define ADC_SQR1_SQ16_1			(0x02UL << ADC_SQR1_SQ16_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ16_2` @def ADC_SQR1_SQ16_2 */
#define ADC_SQR1_SQ16_2			(0x04UL << ADC_SQR1_SQ16_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ16_3` @def ADC_SQR1_SQ16_3 */
#define ADC_SQR1_SQ16_3			(0x08UL << ADC_SQR1_SQ16_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_SQ16_4` @def ADC_SQR1_SQ16_4 */
#define ADC_SQR1_SQ16_4			(0x10UL << ADC_SQR1_SQ16_Pos)

/** @brief Bit position of the `ADC_SQR1_L` field @def ADC_SQR1_L_Pos */
#define ADC_SQR1_L_Pos			((reg_bit_pos_t) 20U)
/** @brief Width of the `ADC_SQR1_L` field @def ADC_SQR1_L_Width */
#define ADC_SQR1_L_Width		((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `ADC_SQR1_L` field @def ADC_SQR1_L_Msk */
#define ADC_SQR1_L_Msk			REG_FIELD_MASK(ADC_SQR1_L_Pos, ADC_SQR1_L_Width)
/** @brief ADC group regular sequencer scan length @def ADC_SQR1_L */
#define ADC_SQR1_L				ADC_SQR1_L_Msk
/** @brief Register or selector value represented by `ADC_SQR1_L_0` @def ADC_SQR1_L_0 */
#define ADC_SQR1_L_0			(0x1UL << ADC_SQR1_L_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_L_1` @def ADC_SQR1_L_1 */
#define ADC_SQR1_L_1			(0x2UL << ADC_SQR1_L_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_L_2` @def ADC_SQR1_L_2 */
#define ADC_SQR1_L_2			(0x4UL << ADC_SQR1_L_Pos)
/** @brief Register or selector value represented by `ADC_SQR1_L_3` @def ADC_SQR1_L_3 */
#define ADC_SQR1_L_3			(0x8UL << ADC_SQR1_L_Pos)

// ---------------------------------- ADC_SQR2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `ADC_SQR2_SQ7` field @def ADC_SQR2_SQ7_Pos */
#define ADC_SQR2_SQ7_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_SQR2_SQ7` field @def ADC_SQR2_SQ7_Width */
#define ADC_SQR2_SQ7_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR2_SQ7` field @def ADC_SQR2_SQ7_Msk */
#define ADC_SQR2_SQ7_Msk		REG_FIELD_MASK(ADC_SQR2_SQ7_Pos, ADC_SQR2_SQ7_Width)
/** @brief ADC group regular sequencer rank 7 @def ADC_SQR2_SQ7 */
#define ADC_SQR2_SQ7			ADC_SQR2_SQ7_Msk
/** @brief Register or selector value represented by `ADC_SQR2_SQ7_0` @def ADC_SQR2_SQ7_0 */
#define ADC_SQR2_SQ7_0			(0x01UL << ADC_SQR2_SQ7_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ7_1` @def ADC_SQR2_SQ7_1 */
#define ADC_SQR2_SQ7_1			(0x02UL << ADC_SQR2_SQ7_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ7_2` @def ADC_SQR2_SQ7_2 */
#define ADC_SQR2_SQ7_2			(0x04UL << ADC_SQR2_SQ7_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ7_3` @def ADC_SQR2_SQ7_3 */
#define ADC_SQR2_SQ7_3			(0x08UL << ADC_SQR2_SQ7_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ7_4` @def ADC_SQR2_SQ7_4 */
#define ADC_SQR2_SQ7_4			(0x10UL << ADC_SQR2_SQ7_Pos)

/** @brief Bit position of the `ADC_SQR2_SQ8` field @def ADC_SQR2_SQ8_Pos */
#define ADC_SQR2_SQ8_Pos		((reg_bit_pos_t) 5U)
/** @brief Width of the `ADC_SQR2_SQ8` field @def ADC_SQR2_SQ8_Width */
#define ADC_SQR2_SQ8_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR2_SQ8` field @def ADC_SQR2_SQ8_Msk */
#define ADC_SQR2_SQ8_Msk		REG_FIELD_MASK(ADC_SQR2_SQ8_Pos, ADC_SQR2_SQ8_Width)
/** @brief ADC group regular sequencer rank 8 @def ADC_SQR2_SQ8 */
#define ADC_SQR2_SQ8			ADC_SQR2_SQ8_Msk
/** @brief Register or selector value represented by `ADC_SQR2_SQ8_0` @def ADC_SQR2_SQ8_0 */
#define ADC_SQR2_SQ8_0			(0x01UL << ADC_SQR2_SQ8_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ8_1` @def ADC_SQR2_SQ8_1 */
#define ADC_SQR2_SQ8_1			(0x02UL << ADC_SQR2_SQ8_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ8_2` @def ADC_SQR2_SQ8_2 */
#define ADC_SQR2_SQ8_2			(0x04UL << ADC_SQR2_SQ8_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ8_3` @def ADC_SQR2_SQ8_3 */
#define ADC_SQR2_SQ8_3			(0x08UL << ADC_SQR2_SQ8_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ8_4` @def ADC_SQR2_SQ8_4 */
#define ADC_SQR2_SQ8_4			(0x10UL << ADC_SQR2_SQ8_Pos)

/** @brief Bit position of the `ADC_SQR2_SQ9` field @def ADC_SQR2_SQ9_Pos */
#define ADC_SQR2_SQ9_Pos		((reg_bit_pos_t) 10U)
/** @brief Width of the `ADC_SQR2_SQ9` field @def ADC_SQR2_SQ9_Width */
#define ADC_SQR2_SQ9_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR2_SQ9` field @def ADC_SQR2_SQ9_Msk */
#define ADC_SQR2_SQ9_Msk		REG_FIELD_MASK(ADC_SQR2_SQ9_Pos, ADC_SQR2_SQ9_Width)
/** @brief ADC group regular sequencer rank 9 @def ADC_SQR2_SQ9 */
#define ADC_SQR2_SQ9			ADC_SQR2_SQ9_Msk
/** @brief Register or selector value represented by `ADC_SQR2_SQ9_0` @def ADC_SQR2_SQ9_0 */
#define ADC_SQR2_SQ9_0			(0x01UL << ADC_SQR2_SQ9_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ9_1` @def ADC_SQR2_SQ9_1 */
#define ADC_SQR2_SQ9_1			(0x02UL << ADC_SQR2_SQ9_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ9_2` @def ADC_SQR2_SQ9_2 */
#define ADC_SQR2_SQ9_2			(0x04UL << ADC_SQR2_SQ9_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ9_3` @def ADC_SQR2_SQ9_3 */
#define ADC_SQR2_SQ9_3			(0x08UL << ADC_SQR2_SQ9_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ9_4` @def ADC_SQR2_SQ9_4 */
#define ADC_SQR2_SQ9_4			(0x10UL << ADC_SQR2_SQ9_Pos)

/** @brief Bit position of the `ADC_SQR2_SQ10` field @def ADC_SQR2_SQ10_Pos */
#define ADC_SQR2_SQ10_Pos		((reg_bit_pos_t) 15U)
/** @brief Width of the `ADC_SQR2_SQ10` field @def ADC_SQR2_SQ10_Width */
#define ADC_SQR2_SQ10_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR2_SQ10` field @def ADC_SQR2_SQ10_Msk */
#define ADC_SQR2_SQ10_Msk		REG_FIELD_MASK(ADC_SQR2_SQ10_Pos, ADC_SQR2_SQ10_Width)
/** @brief ADC group regular sequencer rank 10 @def ADC_SQR2_SQ10 */
#define ADC_SQR2_SQ10			ADC_SQR2_SQ10_Msk
/** @brief Register or selector value represented by `ADC_SQR2_SQ10_0` @def ADC_SQR2_SQ10_0 */
#define ADC_SQR2_SQ10_0			(0x01UL << ADC_SQR2_SQ10_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ10_1` @def ADC_SQR2_SQ10_1 */
#define ADC_SQR2_SQ10_1			(0x02UL << ADC_SQR2_SQ10_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ10_2` @def ADC_SQR2_SQ10_2 */
#define ADC_SQR2_SQ10_2			(0x04UL << ADC_SQR2_SQ10_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ10_3` @def ADC_SQR2_SQ10_3 */
#define ADC_SQR2_SQ10_3			(0x08UL << ADC_SQR2_SQ10_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ10_4` @def ADC_SQR2_SQ10_4 */
#define ADC_SQR2_SQ10_4			(0x10UL << ADC_SQR2_SQ10_Pos)

/** @brief Bit position of the `ADC_SQR2_SQ11` field @def ADC_SQR2_SQ11_Pos */
#define ADC_SQR2_SQ11_Pos		((reg_bit_pos_t) 20U)
/** @brief Width of the `ADC_SQR2_SQ11` field @def ADC_SQR2_SQ11_Width */
#define ADC_SQR2_SQ11_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR2_SQ11` field @def ADC_SQR2_SQ11_Msk */
#define ADC_SQR2_SQ11_Msk		REG_FIELD_MASK(ADC_SQR2_SQ11_Pos, ADC_SQR2_SQ11_Width)
/** @brief ADC group regular sequencer rank 1 @def ADC_SQR2_SQ11 */
#define ADC_SQR2_SQ11			ADC_SQR2_SQ11_Msk
/** @brief Register or selector value represented by `ADC_SQR2_SQ11_0` @def ADC_SQR2_SQ11_0 */
#define ADC_SQR2_SQ11_0			(0x01UL << ADC_SQR2_SQ11_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ11_1` @def ADC_SQR2_SQ11_1 */
#define ADC_SQR2_SQ11_1			(0x02UL << ADC_SQR2_SQ11_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ11_2` @def ADC_SQR2_SQ11_2 */
#define ADC_SQR2_SQ11_2			(0x04UL << ADC_SQR2_SQ11_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ11_3` @def ADC_SQR2_SQ11_3 */
#define ADC_SQR2_SQ11_3			(0x08UL << ADC_SQR2_SQ11_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ11_4` @def ADC_SQR2_SQ11_4 */
#define ADC_SQR2_SQ11_4			(0x10UL << ADC_SQR2_SQ11_Pos)

/** @brief Bit position of the `ADC_SQR2_SQ12` field @def ADC_SQR2_SQ12_Pos */
#define ADC_SQR2_SQ12_Pos		((reg_bit_pos_t) 25U)
/** @brief Width of the `ADC_SQR2_SQ12` field @def ADC_SQR2_SQ12_Width */
#define ADC_SQR2_SQ12_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR2_SQ12` field @def ADC_SQR2_SQ12_Msk */
#define ADC_SQR2_SQ12_Msk		REG_FIELD_MASK(ADC_SQR2_SQ12_Pos, ADC_SQR2_SQ12_Width)
/** @brief ADC group regular sequencer rank 12 @def ADC_SQR2_SQ12 */
#define ADC_SQR2_SQ12			ADC_SQR2_SQ12_Msk
/** @brief Register or selector value represented by `ADC_SQR2_SQ12_0` @def ADC_SQR2_SQ12_0 */
#define ADC_SQR2_SQ12_0			(0x01UL << ADC_SQR2_SQ12_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ12_1` @def ADC_SQR2_SQ12_1 */
#define ADC_SQR2_SQ12_1			(0x02UL << ADC_SQR2_SQ12_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ12_2` @def ADC_SQR2_SQ12_2 */
#define ADC_SQR2_SQ12_2			(0x04UL << ADC_SQR2_SQ12_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ12_3` @def ADC_SQR2_SQ12_3 */
#define ADC_SQR2_SQ12_3			(0x08UL << ADC_SQR2_SQ12_Pos)
/** @brief Register or selector value represented by `ADC_SQR2_SQ12_4` @def ADC_SQR2_SQ12_4 */
#define ADC_SQR2_SQ12_4			(0x10UL << ADC_SQR2_SQ12_Pos)

// ---------------------------------- ADC_SQR3 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `ADC_SQR3_SQ1` field @def ADC_SQR3_SQ1_Pos */
#define ADC_SQR3_SQ1_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_SQR3_SQ1` field @def ADC_SQR3_SQ1_Width */
#define ADC_SQR3_SQ1_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR3_SQ1` field @def ADC_SQR3_SQ1_Msk */
#define ADC_SQR3_SQ1_Msk		REG_FIELD_MASK(ADC_SQR3_SQ1_Pos, ADC_SQR3_SQ1_Width)
/** @brief ADC group regular sequencer rank 1 @def ADC_SQR3_SQ1 */
#define ADC_SQR3_SQ1			ADC_SQR3_SQ1_Msk
/** @brief Register or selector value represented by `ADC_SQR3_SQ1_0` @def ADC_SQR3_SQ1_0 */
#define ADC_SQR3_SQ1_0			(0x01UL << ADC_SQR3_SQ1_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ1_1` @def ADC_SQR3_SQ1_1 */
#define ADC_SQR3_SQ1_1			(0x02UL << ADC_SQR3_SQ1_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ1_2` @def ADC_SQR3_SQ1_2 */
#define ADC_SQR3_SQ1_2			(0x04UL << ADC_SQR3_SQ1_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ1_3` @def ADC_SQR3_SQ1_3 */
#define ADC_SQR3_SQ1_3			(0x08UL << ADC_SQR3_SQ1_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ1_4` @def ADC_SQR3_SQ1_4 */
#define ADC_SQR3_SQ1_4			(0x10UL << ADC_SQR3_SQ1_Pos)

/** @brief Bit position of the `ADC_SQR3_SQ2` field @def ADC_SQR3_SQ2_Pos */
#define ADC_SQR3_SQ2_Pos		((reg_bit_pos_t) 5U)
/** @brief Width of the `ADC_SQR3_SQ2` field @def ADC_SQR3_SQ2_Width */
#define ADC_SQR3_SQ2_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR3_SQ2` field @def ADC_SQR3_SQ2_Msk */
#define ADC_SQR3_SQ2_Msk		REG_FIELD_MASK(ADC_SQR3_SQ2_Pos, ADC_SQR3_SQ2_Width)
/** @brief ADC group regular sequencer rank 2 @def ADC_SQR3_SQ2 */
#define ADC_SQR3_SQ2			ADC_SQR3_SQ2_Msk
/** @brief Register or selector value represented by `ADC_SQR3_SQ2_0` @def ADC_SQR3_SQ2_0 */
#define ADC_SQR3_SQ2_0			(0x01UL << ADC_SQR3_SQ2_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ2_1` @def ADC_SQR3_SQ2_1 */
#define ADC_SQR3_SQ2_1			(0x02UL << ADC_SQR3_SQ2_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ2_2` @def ADC_SQR3_SQ2_2 */
#define ADC_SQR3_SQ2_2			(0x04UL << ADC_SQR3_SQ2_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ2_3` @def ADC_SQR3_SQ2_3 */
#define ADC_SQR3_SQ2_3			(0x08UL << ADC_SQR3_SQ2_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ2_4` @def ADC_SQR3_SQ2_4 */
#define ADC_SQR3_SQ2_4			(0x10UL << ADC_SQR3_SQ2_Pos)

/** @brief Bit position of the `ADC_SQR3_SQ3` field @def ADC_SQR3_SQ3_Pos */
#define ADC_SQR3_SQ3_Pos		((reg_bit_pos_t) 10U)
/** @brief Width of the `ADC_SQR3_SQ3` field @def ADC_SQR3_SQ3_Width */
#define ADC_SQR3_SQ3_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR3_SQ3` field @def ADC_SQR3_SQ3_Msk */
#define ADC_SQR3_SQ3_Msk		REG_FIELD_MASK(ADC_SQR3_SQ3_Pos, ADC_SQR3_SQ3_Width)
/** @brief ADC group regular sequencer rank 3 @def ADC_SQR3_SQ3 */
#define ADC_SQR3_SQ3			ADC_SQR3_SQ3_Msk
/** @brief Register or selector value represented by `ADC_SQR3_SQ3_0` @def ADC_SQR3_SQ3_0 */
#define ADC_SQR3_SQ3_0			(0x01UL << ADC_SQR3_SQ3_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ3_1` @def ADC_SQR3_SQ3_1 */
#define ADC_SQR3_SQ3_1			(0x02UL << ADC_SQR3_SQ3_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ3_2` @def ADC_SQR3_SQ3_2 */
#define ADC_SQR3_SQ3_2			(0x04UL << ADC_SQR3_SQ3_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ3_3` @def ADC_SQR3_SQ3_3 */
#define ADC_SQR3_SQ3_3			(0x08UL << ADC_SQR3_SQ3_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ3_4` @def ADC_SQR3_SQ3_4 */
#define ADC_SQR3_SQ3_4			(0x10UL << ADC_SQR3_SQ3_Pos)

/** @brief Bit position of the `ADC_SQR3_SQ4` field @def ADC_SQR3_SQ4_Pos */
#define ADC_SQR3_SQ4_Pos		((reg_bit_pos_t) 15U)
/** @brief Width of the `ADC_SQR3_SQ4` field @def ADC_SQR3_SQ4_Width */
#define ADC_SQR3_SQ4_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR3_SQ4` field @def ADC_SQR3_SQ4_Msk */
#define ADC_SQR3_SQ4_Msk		REG_FIELD_MASK(ADC_SQR3_SQ4_Pos, ADC_SQR3_SQ4_Width)
/** @brief ADC group regular sequencer rank 4 @def ADC_SQR3_SQ4 */
#define ADC_SQR3_SQ4			ADC_SQR3_SQ4_Msk
/** @brief Register or selector value represented by `ADC_SQR3_SQ4_0` @def ADC_SQR3_SQ4_0 */
#define ADC_SQR3_SQ4_0			(0x01UL << ADC_SQR3_SQ4_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ4_1` @def ADC_SQR3_SQ4_1 */
#define ADC_SQR3_SQ4_1			(0x02UL << ADC_SQR3_SQ4_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ4_2` @def ADC_SQR3_SQ4_2 */
#define ADC_SQR3_SQ4_2			(0x04UL << ADC_SQR3_SQ4_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ4_3` @def ADC_SQR3_SQ4_3 */
#define ADC_SQR3_SQ4_3			(0x08UL << ADC_SQR3_SQ4_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ4_4` @def ADC_SQR3_SQ4_4 */
#define ADC_SQR3_SQ4_4			(0x10UL << ADC_SQR3_SQ4_Pos)

/** @brief Bit position of the `ADC_SQR3_SQ5` field @def ADC_SQR3_SQ5_Pos */
#define ADC_SQR3_SQ5_Pos		((reg_bit_pos_t) 20U)
/** @brief Width of the `ADC_SQR3_SQ5` field @def ADC_SQR3_SQ5_Width */
#define ADC_SQR3_SQ5_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR3_SQ5` field @def ADC_SQR3_SQ5_Msk */
#define ADC_SQR3_SQ5_Msk		REG_FIELD_MASK(ADC_SQR3_SQ5_Pos, ADC_SQR3_SQ5_Width)
/** @brief ADC group regular sequencer rank 5 @def ADC_SQR3_SQ5 */
#define ADC_SQR3_SQ5			ADC_SQR3_SQ5_Msk
/** @brief Register or selector value represented by `ADC_SQR3_SQ5_0` @def ADC_SQR3_SQ5_0 */
#define ADC_SQR3_SQ5_0			(0x01UL << ADC_SQR3_SQ5_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ5_1` @def ADC_SQR3_SQ5_1 */
#define ADC_SQR3_SQ5_1			(0x02UL << ADC_SQR3_SQ5_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ5_2` @def ADC_SQR3_SQ5_2 */
#define ADC_SQR3_SQ5_2			(0x04UL << ADC_SQR3_SQ5_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ5_3` @def ADC_SQR3_SQ5_3 */
#define ADC_SQR3_SQ5_3			(0x08UL << ADC_SQR3_SQ5_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ5_4` @def ADC_SQR3_SQ5_4 */
#define ADC_SQR3_SQ5_4			(0x10UL << ADC_SQR3_SQ5_Pos)

/** @brief Bit position of the `ADC_SQR3_SQ6` field @def ADC_SQR3_SQ6_Pos */
#define ADC_SQR3_SQ6_Pos		((reg_bit_pos_t) 25U)
/** @brief Width of the `ADC_SQR3_SQ6` field @def ADC_SQR3_SQ6_Width */
#define ADC_SQR3_SQ6_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_SQR3_SQ6` field @def ADC_SQR3_SQ6_Msk */
#define ADC_SQR3_SQ6_Msk		REG_FIELD_MASK(ADC_SQR3_SQ6_Pos, ADC_SQR3_SQ6_Width)
/** @brief ADC group regular sequencer rank 6 @def ADC_SQR3_SQ6 */
#define ADC_SQR3_SQ6			ADC_SQR3_SQ6_Msk
/** @brief Register or selector value represented by `ADC_SQR3_SQ6_0` @def ADC_SQR3_SQ6_0 */
#define ADC_SQR3_SQ6_0			(0x01UL << ADC_SQR3_SQ6_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ6_1` @def ADC_SQR3_SQ6_1 */
#define ADC_SQR3_SQ6_1			(0x02UL << ADC_SQR3_SQ6_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ6_2` @def ADC_SQR3_SQ6_2 */
#define ADC_SQR3_SQ6_2			(0x04UL << ADC_SQR3_SQ6_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ6_3` @def ADC_SQR3_SQ6_3 */
#define ADC_SQR3_SQ6_3			(0x08UL << ADC_SQR3_SQ6_Pos)
/** @brief Register or selector value represented by `ADC_SQR3_SQ6_4` @def ADC_SQR3_SQ6_4 */
#define ADC_SQR3_SQ6_4			(0x10UL << ADC_SQR3_SQ6_Pos)

// ---------------------------------- ADC_JSQR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `ADC_JSQR_JSQ1` field @def ADC_JSQR_JSQ1_Pos */
#define ADC_JSQR_JSQ1_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_JSQR_JSQ1` field @def ADC_JSQR_JSQ1_Width */
#define ADC_JSQR_JSQ1_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_JSQR_JSQ1` field @def ADC_JSQR_JSQ1_Msk */
#define ADC_JSQR_JSQ1_Msk		REG_FIELD_MASK(ADC_JSQR_JSQ1_Pos, ADC_JSQR_JSQ1_Width)
/** @brief ADC group injected sequencer rank 1 @def ADC_JSQR_JSQ1 */
#define ADC_JSQR_JSQ1			ADC_JSQR_JSQ1_Msk
/** @brief Register or selector value represented by `ADC_JSQR_JSQ1_0` @def ADC_JSQR_JSQ1_0 */
#define ADC_JSQR_JSQ1_0			(0x01UL << ADC_JSQR_JSQ1_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ1_1` @def ADC_JSQR_JSQ1_1 */
#define ADC_JSQR_JSQ1_1			(0x02UL << ADC_JSQR_JSQ1_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ1_2` @def ADC_JSQR_JSQ1_2 */
#define ADC_JSQR_JSQ1_2			(0x04UL << ADC_JSQR_JSQ1_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ1_3` @def ADC_JSQR_JSQ1_3 */
#define ADC_JSQR_JSQ1_3			(0x08UL << ADC_JSQR_JSQ1_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ1_4` @def ADC_JSQR_JSQ1_4 */
#define ADC_JSQR_JSQ1_4			(0x10UL << ADC_JSQR_JSQ1_Pos)

/** @brief Bit position of the `ADC_JSQR_JSQ2` field @def ADC_JSQR_JSQ2_Pos */
#define ADC_JSQR_JSQ2_Pos		((reg_bit_pos_t) 5U)
/** @brief Width of the `ADC_JSQR_JSQ2` field @def ADC_JSQR_JSQ2_Width */
#define ADC_JSQR_JSQ2_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_JSQR_JSQ2` field @def ADC_JSQR_JSQ2_Msk */
#define ADC_JSQR_JSQ2_Msk		REG_FIELD_MASK(ADC_JSQR_JSQ2_Pos, ADC_JSQR_JSQ2_Width)
/** @brief ADC group injected sequencer rank 2 @def ADC_JSQR_JSQ2 */
#define ADC_JSQR_JSQ2			ADC_JSQR_JSQ2_Msk
/** @brief Register or selector value represented by `ADC_JSQR_JSQ2_0` @def ADC_JSQR_JSQ2_0 */
#define ADC_JSQR_JSQ2_0			(0x01UL << ADC_JSQR_JSQ2_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ2_1` @def ADC_JSQR_JSQ2_1 */
#define ADC_JSQR_JSQ2_1			(0x02UL << ADC_JSQR_JSQ2_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ2_2` @def ADC_JSQR_JSQ2_2 */
#define ADC_JSQR_JSQ2_2			(0x04UL << ADC_JSQR_JSQ2_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ2_3` @def ADC_JSQR_JSQ2_3 */
#define ADC_JSQR_JSQ2_3			(0x08UL << ADC_JSQR_JSQ2_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ2_4` @def ADC_JSQR_JSQ2_4 */
#define ADC_JSQR_JSQ2_4			(0x10UL << ADC_JSQR_JSQ2_Pos)

/** @brief Bit position of the `ADC_JSQR_JSQ3` field @def ADC_JSQR_JSQ3_Pos */
#define ADC_JSQR_JSQ3_Pos		((reg_bit_pos_t) 10U)
/** @brief Width of the `ADC_JSQR_JSQ3` field @def ADC_JSQR_JSQ3_Width */
#define ADC_JSQR_JSQ3_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_JSQR_JSQ3` field @def ADC_JSQR_JSQ3_Msk */
#define ADC_JSQR_JSQ3_Msk		REG_FIELD_MASK(ADC_JSQR_JSQ3_Pos, ADC_JSQR_JSQ3_Width)
/** @brief ADC group injected sequencer rank 3 @def ADC_JSQR_JSQ3 */
#define ADC_JSQR_JSQ3			ADC_JSQR_JSQ3_Msk
/** @brief Register or selector value represented by `ADC_JSQR_JSQ3_0` @def ADC_JSQR_JSQ3_0 */
#define ADC_JSQR_JSQ3_0			(0x01UL << ADC_JSQR_JSQ3_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ3_1` @def ADC_JSQR_JSQ3_1 */
#define ADC_JSQR_JSQ3_1			(0x02UL << ADC_JSQR_JSQ3_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ3_2` @def ADC_JSQR_JSQ3_2 */
#define ADC_JSQR_JSQ3_2			(0x04UL << ADC_JSQR_JSQ3_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ3_3` @def ADC_JSQR_JSQ3_3 */
#define ADC_JSQR_JSQ3_3			(0x08UL << ADC_JSQR_JSQ3_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ3_4` @def ADC_JSQR_JSQ3_4 */
#define ADC_JSQR_JSQ3_4			(0x10UL << ADC_JSQR_JSQ3_Pos)

/** @brief Bit position of the `ADC_JSQR_JSQ4` field @def ADC_JSQR_JSQ4_Pos */
#define ADC_JSQR_JSQ4_Pos		((reg_bit_pos_t) 15U)
/** @brief Width of the `ADC_JSQR_JSQ4` field @def ADC_JSQR_JSQ4_Width */
#define ADC_JSQR_JSQ4_Width		((reg_field_width_t) 5U)
/** @brief Register-positioned mask for the `ADC_JSQR_JSQ4` field @def ADC_JSQR_JSQ4_Msk */
#define ADC_JSQR_JSQ4_Msk		REG_FIELD_MASK(ADC_JSQR_JSQ4_Pos, ADC_JSQR_JSQ4_Width)
/** @brief ADC group injected sequencer rank 4 @def ADC_JSQR_JSQ4 */
#define ADC_JSQR_JSQ4			ADC_JSQR_JSQ4_Msk
/** @brief Register or selector value represented by `ADC_JSQR_JSQ4_0` @def ADC_JSQR_JSQ4_0 */
#define ADC_JSQR_JSQ4_0			(0x01UL << ADC_JSQR_JSQ4_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ4_1` @def ADC_JSQR_JSQ4_1 */
#define ADC_JSQR_JSQ4_1			(0x02UL << ADC_JSQR_JSQ4_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ4_2` @def ADC_JSQR_JSQ4_2 */
#define ADC_JSQR_JSQ4_2			(0x04UL << ADC_JSQR_JSQ4_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ4_3` @def ADC_JSQR_JSQ4_3 */
#define ADC_JSQR_JSQ4_3			(0x08UL << ADC_JSQR_JSQ4_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JSQ4_4` @def ADC_JSQR_JSQ4_4 */
#define ADC_JSQR_JSQ4_4			(0x10UL << ADC_JSQR_JSQ4_Pos)

/** @brief Bit position of the `ADC_JSQR_JL` field @def ADC_JSQR_JL_Pos */
#define ADC_JSQR_JL_Pos			((reg_bit_pos_t) 20U)
/** @brief Width of the `ADC_JSQR_JL` field @def ADC_JSQR_JL_Width */
#define ADC_JSQR_JL_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `ADC_JSQR_JL` field @def ADC_JSQR_JL_Msk */
#define ADC_JSQR_JL_Msk			REG_FIELD_MASK(ADC_JSQR_JL_Pos, ADC_JSQR_JL_Width)
/** @brief ADC group injected sequencer scan length @def ADC_JSQR_JL */
#define ADC_JSQR_JL				ADC_JSQR_JL_Msk
/** @brief Register or selector value represented by `ADC_JSQR_JL_0` @def ADC_JSQR_JL_0 */
#define ADC_JSQR_JL_0			(0x1UL << ADC_JSQR_JL_Pos)
/** @brief Register or selector value represented by `ADC_JSQR_JL_1` @def ADC_JSQR_JL_1 */
#define ADC_JSQR_JL_1			(0x2UL << ADC_JSQR_JL_Pos)

// ---------------------------------- ADC_JDR1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `ADC_JDR1_JDATA` field @def ADC_JDR1_JDATA_Pos */
#define ADC_JDR1_JDATA_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_JDR1_JDATA` field @def ADC_JDR1_JDATA_Width */
#define ADC_JDR1_JDATA_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `ADC_JDR1_JDATA` field @def ADC_JDR1_JDATA_Msk */
#define ADC_JDR1_JDATA_Msk			REG_FIELD_MASK(ADC_JDR1_JDATA_Pos, ADC_JDR1_JDATA_Width)
/** @brief ADC group injected sequencer rank 1 conversion data @def ADC_JDR1_JDATA */
#define ADC_JDR1_JDATA				ADC_JDR1_JDATA_Msk

// ---------------------------------- ADC_JDR2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `ADC_JDR2_JDATA` field @def ADC_JDR2_JDATA_Pos */
#define ADC_JDR2_JDATA_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_JDR2_JDATA` field @def ADC_JDR2_JDATA_Width */
#define ADC_JDR2_JDATA_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `ADC_JDR2_JDATA` field @def ADC_JDR2_JDATA_Msk */
#define ADC_JDR2_JDATA_Msk			REG_FIELD_MASK(ADC_JDR2_JDATA_Pos, ADC_JDR2_JDATA_Width)
/** @brief ADC group injected sequencer rank 2 conversion data @def ADC_JDR2_JDATA */
#define ADC_JDR2_JDATA				ADC_JDR2_JDATA_Msk

// ---------------------------------- ADC_JDR3 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `ADC_JDR3_JDATA` field @def ADC_JDR3_JDATA_Pos */
#define ADC_JDR3_JDATA_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_JDR3_JDATA` field @def ADC_JDR3_JDATA_Width */
#define ADC_JDR3_JDATA_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `ADC_JDR3_JDATA` field @def ADC_JDR3_JDATA_Msk */
#define ADC_JDR3_JDATA_Msk			REG_FIELD_MASK(ADC_JDR3_JDATA_Pos, ADC_JDR3_JDATA_Width)
/** @brief ADC group injected sequencer rank 3 conversion data @def ADC_JDR3_JDATA */
#define ADC_JDR3_JDATA				ADC_JDR3_JDATA_Msk

// ---------------------------------- ADC_JDR4 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `ADC_JDR4_JDATA` field @def ADC_JDR4_JDATA_Pos */
#define ADC_JDR4_JDATA_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_JDR4_JDATA` field @def ADC_JDR4_JDATA_Width */
#define ADC_JDR4_JDATA_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `ADC_JDR4_JDATA` field @def ADC_JDR4_JDATA_Msk */
#define ADC_JDR4_JDATA_Msk			REG_FIELD_MASK(ADC_JDR4_JDATA_Pos, ADC_JDR4_JDATA_Width)
/** @brief ADC group injected sequencer rank 4 conversion data @def ADC_JDR4_JDATA */
#define ADC_JDR4_JDATA				ADC_JDR4_JDATA_Msk

// ----------------------------------- ADC_DR Register Bit Defines ------------------------------------ //
/** @brief Bit position of the `ADC_DR_DATA` field @def ADC_DR_DATA_Pos */
#define ADC_DR_DATA_Pos				((reg_bit_pos_t) 0U)
/** @brief Width of the `ADC_DR_DATA` field @def ADC_DR_DATA_Width */
#define ADC_DR_DATA_Width			((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `ADC_DR_DATA` field @def ADC_DR_DATA_Msk */
#define ADC_DR_DATA_Msk				REG_FIELD_MASK(ADC_DR_DATA_Pos, ADC_DR_DATA_Width)
/** @brief ADC group regular conversion data @def ADC_DR_DATA */
#define ADC_DR_DATA					ADC_DR_DATA_Msk
/** @brief Bit position of the `ADC_DR_ADC2DATA` field @def ADC_DR_ADC2DATA_Pos */
#define ADC_DR_ADC2DATA_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `ADC_DR_ADC2DATA` field @def ADC_DR_ADC2DATA_Width */
#define ADC_DR_ADC2DATA_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `ADC_DR_ADC2DATA` field @def ADC_DR_ADC2DATA_Msk */
#define ADC_DR_ADC2DATA_Msk			REG_FIELD_MASK(ADC_DR_ADC2DATA_Pos, ADC_DR_ADC2DATA_Width)
/** @brief ADC group regular conversion data for ADC slave, in multimode @def ADC_DR_ADC2DATA */
#define ADC_DR_ADC2DATA				ADC_DR_ADC2DATA_Msk

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
//								Controller Area Network (CAN) Register Defines							//
// ==================================================================================================== //

// ----------------------------- CAN Control and Status Register Defines ------------------------------ //
// ----------------------------------- CAN_MCR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_MCR_INRQ` field @def CAN_MCR_INRQ_Pos */
#define CAN_MCR_INRQ_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_MCR_INRQ` field @def CAN_MCR_INRQ_Msk */
#define CAN_MCR_INRQ_Msk		REG_BIT_MASK(CAN_MCR_INRQ_Pos)
/** @brief Initialization Request @def CAN_MCR_INRQ */
#define CAN_MCR_INRQ			CAN_MCR_INRQ_Msk
/** @brief Bit position of the `CAN_MCR_SLEEP` field @def CAN_MCR_SLEEP_Pos */
#define CAN_MCR_SLEEP_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_MCR_SLEEP` field @def CAN_MCR_SLEEP_Msk */
#define CAN_MCR_SLEEP_Msk		REG_BIT_MASK(CAN_MCR_SLEEP_Pos)
/** @brief Sleep Mode Request @def CAN_MCR_SLEEP */
#define CAN_MCR_SLEEP			CAN_MCR_SLEEP_Msk
/** @brief Bit position of the `CAN_MCR_TXFP` field @def CAN_MCR_TXFP_Pos */
#define CAN_MCR_TXFP_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_MCR_TXFP` field @def CAN_MCR_TXFP_Msk */
#define CAN_MCR_TXFP_Msk		REG_BIT_MASK(CAN_MCR_TXFP_Pos)
/** @brief Transmit FIFO Priority @def CAN_MCR_TXFP */
#define CAN_MCR_TXFP			CAN_MCR_TXFP_Msk
/** @brief Bit position of the `CAN_MCR_RFLM` field @def CAN_MCR_RFLM_Pos */
#define CAN_MCR_RFLM_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_MCR_RFLM` field @def CAN_MCR_RFLM_Msk */
#define CAN_MCR_RFLM_Msk		REG_BIT_MASK(CAN_MCR_RFLM_Pos)
/** @brief Receive FIFO Locked Mode @def CAN_MCR_RFLM */
#define CAN_MCR_RFLM			CAN_MCR_RFLM_Msk
/** @brief Bit position of the `CAN_MCR_NART` field @def CAN_MCR_NART_Pos */
#define CAN_MCR_NART_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_MCR_NART` field @def CAN_MCR_NART_Msk */
#define CAN_MCR_NART_Msk		REG_BIT_MASK(CAN_MCR_NART_Pos)
/** @brief No Automatic Retransmission @def CAN_MCR_NART */
#define CAN_MCR_NART			CAN_MCR_NART_Msk
/** @brief Bit position of the `CAN_MCR_AWUM` field @def CAN_MCR_AWUM_Pos */
#define CAN_MCR_AWUM_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_MCR_AWUM` field @def CAN_MCR_AWUM_Msk */
#define CAN_MCR_AWUM_Msk		REG_BIT_MASK(CAN_MCR_AWUM_Pos)
/** @brief Automatic Wakeup Mode @def CAN_MCR_AWUM */
#define CAN_MCR_AWUM			CAN_MCR_AWUM_Msk
/** @brief Bit position of the `CAN_MCR_ABOM` field @def CAN_MCR_ABOM_Pos */
#define CAN_MCR_ABOM_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_MCR_ABOM` field @def CAN_MCR_ABOM_Msk */
#define CAN_MCR_ABOM_Msk		REG_BIT_MASK(CAN_MCR_ABOM_Pos)
/** @brief Automatic Bus-Off Management @def CAN_MCR_ABOM */
#define CAN_MCR_ABOM			CAN_MCR_ABOM_Msk
/** @brief Bit position of the `CAN_MCR_TTCM` field @def CAN_MCR_TTCM_Pos */
#define CAN_MCR_TTCM_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_MCR_TTCM` field @def CAN_MCR_TTCM_Msk */
#define CAN_MCR_TTCM_Msk		REG_BIT_MASK(CAN_MCR_TTCM_Pos)
/** @brief Time Triggered Communication Mode @def CAN_MCR_TTCM */
#define CAN_MCR_TTCM			CAN_MCR_TTCM_Msk
/** @brief Bit position of the `CAN_MCR_RESET` field @def CAN_MCR_RESET_Pos */
#define CAN_MCR_RESET_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_MCR_RESET` field @def CAN_MCR_RESET_Msk */
#define CAN_MCR_RESET_Msk		REG_BIT_MASK(CAN_MCR_RESET_Pos)
/** @brief CAN software master reset @def CAN_MCR_RESET */
#define CAN_MCR_RESET			CAN_MCR_RESET_Msk
/** @brief Bit position of the `CAN_MCR_DBF` field @def CAN_MCR_DBF_Pos */
#define CAN_MCR_DBF_Pos			((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_MCR_DBF` field @def CAN_MCR_DBF_Msk */
#define CAN_MCR_DBF_Msk			REG_BIT_MASK(CAN_MCR_DBF_Pos)
/** @brief CAN Debug freeze @def CAN_MCR_DBF */
#define CAN_MCR_DBF				CAN_MCR_DBF_Msk

// ----------------------------------- CAN_MSR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_MSR_INAK` field @def CAN_MSR_INAK_Pos */
#define CAN_MSR_INAK_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_MSR_INAK` field @def CAN_MSR_INAK_Msk */
#define CAN_MSR_INAK_Msk		REG_BIT_MASK(CAN_MSR_INAK_Pos)
/** @brief Initialization Acknowledge @def CAN_MSR_INAK */
#define CAN_MSR_INAK			CAN_MSR_INAK_Msk
/** @brief Bit position of the `CAN_MSR_SLAK` field @def CAN_MSR_SLAK_Pos */
#define CAN_MSR_SLAK_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_MSR_SLAK` field @def CAN_MSR_SLAK_Msk */
#define CAN_MSR_SLAK_Msk		REG_BIT_MASK(CAN_MSR_SLAK_Pos)
/** @brief Sleep Acknowledge @def CAN_MSR_SLAK */
#define CAN_MSR_SLAK			CAN_MSR_SLAK_Msk
/** @brief Bit position of the `CAN_MSR_ERRI` field @def CAN_MSR_ERRI_Pos */
#define CAN_MSR_ERRI_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_MSR_ERRI` field @def CAN_MSR_ERRI_Msk */
#define CAN_MSR_ERRI_Msk		REG_BIT_MASK(CAN_MSR_ERRI_Pos)
/** @brief Error Interrupt @def CAN_MSR_ERRI */
#define CAN_MSR_ERRI			CAN_MSR_ERRI_Msk
/** @brief Bit position of the `CAN_MSR_WKUI` field @def CAN_MSR_WKUI_Pos */
#define CAN_MSR_WKUI_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_MSR_WKUI` field @def CAN_MSR_WKUI_Msk */
#define CAN_MSR_WKUI_Msk		REG_BIT_MASK(CAN_MSR_WKUI_Pos)
/** @brief Wakeup Interrupt @def CAN_MSR_WKUI */
#define CAN_MSR_WKUI			CAN_MSR_WKUI_Msk
/** @brief Bit position of the `CAN_MSR_SLAKI` field @def CAN_MSR_SLAKI_Pos */
#define CAN_MSR_SLAKI_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_MSR_SLAKI` field @def CAN_MSR_SLAKI_Msk */
#define CAN_MSR_SLAKI_Msk		REG_BIT_MASK(CAN_MSR_SLAKI_Pos)
/** @brief Sleep Acknowledge Interrupt @def CAN_MSR_SLAKI */
#define CAN_MSR_SLAKI			CAN_MSR_SLAKI_Msk
/** @brief Bit position of the `CAN_MSR_TXM` field @def CAN_MSR_TXM_Pos */
#define CAN_MSR_TXM_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_MSR_TXM` field @def CAN_MSR_TXM_Msk */
#define CAN_MSR_TXM_Msk			REG_BIT_MASK(CAN_MSR_TXM_Pos)
/** @brief Transmit Mode @def CAN_MSR_TXM */
#define CAN_MSR_TXM				CAN_MSR_TXM_Msk
/** @brief Bit position of the `CAN_MSR_RXM` field @def CAN_MSR_RXM_Pos */
#define CAN_MSR_RXM_Pos			((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_MSR_RXM` field @def CAN_MSR_RXM_Msk */
#define CAN_MSR_RXM_Msk			REG_BIT_MASK(CAN_MSR_RXM_Pos)
/** @brief Receive Mode @def CAN_MSR_RXM */
#define CAN_MSR_RXM				CAN_MSR_RXM_Msk
/** @brief Bit position of the `CAN_MSR_SAMP` field @def CAN_MSR_SAMP_Pos */
#define CAN_MSR_SAMP_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_MSR_SAMP` field @def CAN_MSR_SAMP_Msk */
#define CAN_MSR_SAMP_Msk		REG_BIT_MASK(CAN_MSR_SAMP_Pos)
/** @brief Last Sample Point @def CAN_MSR_SAMP */
#define CAN_MSR_SAMP			CAN_MSR_SAMP_Msk
/** @brief Bit position of the `CAN_MSR_RX` field @def CAN_MSR_RX_Pos */
#define CAN_MSR_RX_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_MSR_RX` field @def CAN_MSR_RX_Msk */
#define CAN_MSR_RX_Msk			REG_BIT_MASK(CAN_MSR_RX_Pos)
/** @brief CAN Rx Signal @def CAN_MSR_RX */
#define CAN_MSR_RX				CAN_MSR_RX_Msk

// ----------------------------------- CAN_TSR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_TSR_RQCP0` field @def CAN_TSR_RQCP0_Pos */
#define CAN_TSR_RQCP0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_TSR_RQCP0` field @def CAN_TSR_RQCP0_Msk */
#define CAN_TSR_RQCP0_Msk		REG_BIT_MASK(CAN_TSR_RQCP0_Pos)
/** @brief Request Completed Mailbox0 @def CAN_TSR_RQCP0 */
#define CAN_TSR_RQCP0			CAN_TSR_RQCP0_Msk
/** @brief Bit position of the `CAN_TSR_TXOK0` field @def CAN_TSR_TXOK0_Pos */
#define CAN_TSR_TXOK0_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_TSR_TXOK0` field @def CAN_TSR_TXOK0_Msk */
#define CAN_TSR_TXOK0_Msk		REG_BIT_MASK(CAN_TSR_TXOK0_Pos)
/** @brief Transmission OK of Mailbox0 @def CAN_TSR_TXOK0 */
#define CAN_TSR_TXOK0			CAN_TSR_TXOK0_Msk
/** @brief Bit position of the `CAN_TSR_ALST0` field @def CAN_TSR_ALST0_Pos */
#define CAN_TSR_ALST0_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_TSR_ALST0` field @def CAN_TSR_ALST0_Msk */
#define CAN_TSR_ALST0_Msk		REG_BIT_MASK(CAN_TSR_ALST0_Pos)
/** @brief Arbitration Lost for Mailbox0 @def CAN_TSR_ALST0 */
#define CAN_TSR_ALST0			CAN_TSR_ALST0_Msk
/** @brief Bit position of the `CAN_TSR_TERR0` field @def CAN_TSR_TERR0_Pos */
#define CAN_TSR_TERR0_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_TSR_TERR0` field @def CAN_TSR_TERR0_Msk */
#define CAN_TSR_TERR0_Msk		REG_BIT_MASK(CAN_TSR_TERR0_Pos)
/** @brief Transmission Error of Mailbox0 @def CAN_TSR_TERR0 */
#define CAN_TSR_TERR0			CAN_TSR_TERR0_Msk
/** @brief Bit position of the `CAN_TSR_ABRQ0` field @def CAN_TSR_ABRQ0_Pos */
#define CAN_TSR_ABRQ0_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_TSR_ABRQ0` field @def CAN_TSR_ABRQ0_Msk */
#define CAN_TSR_ABRQ0_Msk		REG_BIT_MASK(CAN_TSR_ABRQ0_Pos)
/** @brief Abort Request for Mailbox0 @def CAN_TSR_ABRQ0 */
#define CAN_TSR_ABRQ0			CAN_TSR_ABRQ0_Msk
/** @brief Bit position of the `CAN_TSR_RQCP1` field @def CAN_TSR_RQCP1_Pos */
#define CAN_TSR_RQCP1_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_TSR_RQCP1` field @def CAN_TSR_RQCP1_Msk */
#define CAN_TSR_RQCP1_Msk		REG_BIT_MASK(CAN_TSR_RQCP1_Pos)
/** @brief Request Completed Mailbox1 @def CAN_TSR_RQCP1 */
#define CAN_TSR_RQCP1			CAN_TSR_RQCP1_Msk
/** @brief Bit position of the `CAN_TSR_TXOK1` field @def CAN_TSR_TXOK1_Pos */
#define CAN_TSR_TXOK1_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_TSR_TXOK1` field @def CAN_TSR_TXOK1_Msk */
#define CAN_TSR_TXOK1_Msk		REG_BIT_MASK(CAN_TSR_TXOK1_Pos)
/** @brief Transmission OK of Mailbox1 @def CAN_TSR_TXOK1 */
#define CAN_TSR_TXOK1			CAN_TSR_TXOK1_Msk
/** @brief Bit position of the `CAN_TSR_ALST1` field @def CAN_TSR_ALST1_Pos */
#define CAN_TSR_ALST1_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_TSR_ALST1` field @def CAN_TSR_ALST1_Msk */
#define CAN_TSR_ALST1_Msk		REG_BIT_MASK(CAN_TSR_ALST1_Pos)
/** @brief Arbitration Lost for Mailbox1 @def CAN_TSR_ALST1 */
#define CAN_TSR_ALST1			CAN_TSR_ALST1_Msk
/** @brief Bit position of the `CAN_TSR_TERR1` field @def CAN_TSR_TERR1_Pos */
#define CAN_TSR_TERR1_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_TSR_TERR1` field @def CAN_TSR_TERR1_Msk */
#define CAN_TSR_TERR1_Msk		REG_BIT_MASK(CAN_TSR_TERR1_Pos)
/** @brief Transmission Error of Mailbox1 @def CAN_TSR_TERR1 */
#define CAN_TSR_TERR1			CAN_TSR_TERR1_Msk
/** @brief Bit position of the `CAN_TSR_ABRQ1` field @def CAN_TSR_ABRQ1_Pos */
#define CAN_TSR_ABRQ1_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_TSR_ABRQ1` field @def CAN_TSR_ABRQ1_Msk */
#define CAN_TSR_ABRQ1_Msk		REG_BIT_MASK(CAN_TSR_ABRQ1_Pos)
/** @brief Abort Request for Mailbox 1 @def CAN_TSR_ABRQ1 */
#define CAN_TSR_ABRQ1			CAN_TSR_ABRQ1_Msk
/** @brief Bit position of the `CAN_TSR_RQCP2` field @def CAN_TSR_RQCP2_Pos */
#define CAN_TSR_RQCP2_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_TSR_RQCP2` field @def CAN_TSR_RQCP2_Msk */
#define CAN_TSR_RQCP2_Msk		REG_BIT_MASK(CAN_TSR_RQCP2_Pos)
/** @brief Request Completed Mailbox2 @def CAN_TSR_RQCP2 */
#define CAN_TSR_RQCP2			CAN_TSR_RQCP2_Msk
/** @brief Bit position of the `CAN_TSR_TXOK2` field @def CAN_TSR_TXOK2_Pos */
#define CAN_TSR_TXOK2_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_TSR_TXOK2` field @def CAN_TSR_TXOK2_Msk */
#define CAN_TSR_TXOK2_Msk		REG_BIT_MASK(CAN_TSR_TXOK2_Pos)
/** @brief Transmission OK of Mailbox 2 @def CAN_TSR_TXOK2 */
#define CAN_TSR_TXOK2			CAN_TSR_TXOK2_Msk
/** @brief Bit position of the `CAN_TSR_ALST2` field @def CAN_TSR_ALST2_Pos */
#define CAN_TSR_ALST2_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_TSR_ALST2` field @def CAN_TSR_ALST2_Msk */
#define CAN_TSR_ALST2_Msk		REG_BIT_MASK(CAN_TSR_ALST2_Pos)
/** @brief Arbitration Lost for mailbox 2 @def CAN_TSR_ALST2 */
#define CAN_TSR_ALST2			CAN_TSR_ALST2_Msk
/** @brief Bit position of the `CAN_TSR_TERR2` field @def CAN_TSR_TERR2_Pos */
#define CAN_TSR_TERR2_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_TSR_TERR2` field @def CAN_TSR_TERR2_Msk */
#define CAN_TSR_TERR2_Msk		REG_BIT_MASK(CAN_TSR_TERR2_Pos)
/** @brief Transmission Error of Mailbox 2 @def CAN_TSR_TERR2 */
#define CAN_TSR_TERR2			CAN_TSR_TERR2_Msk
/** @brief Bit position of the `CAN_TSR_ABRQ2` field @def CAN_TSR_ABRQ2_Pos */
#define CAN_TSR_ABRQ2_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_TSR_ABRQ2` field @def CAN_TSR_ABRQ2_Msk */
#define CAN_TSR_ABRQ2_Msk		REG_BIT_MASK(CAN_TSR_ABRQ2_Pos)
/** @brief Abort Request for Mailbox 2 @def CAN_TSR_ABRQ2 */
#define CAN_TSR_ABRQ2			CAN_TSR_ABRQ2_Msk
/** @brief Bit position of the `CAN_TSR_CODE` field @def CAN_TSR_CODE_Pos */
#define CAN_TSR_CODE_Pos		((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_TSR_CODE` field @def CAN_TSR_CODE_Width */
#define CAN_TSR_CODE_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `CAN_TSR_CODE` field @def CAN_TSR_CODE_Msk */
#define CAN_TSR_CODE_Msk		REG_FIELD_MASK(CAN_TSR_CODE_Pos, CAN_TSR_CODE_Width)
/** @brief Mailbox Code @def CAN_TSR_CODE */
#define CAN_TSR_CODE			CAN_TSR_CODE_Msk

/** @brief Bit position of the `CAN_TSR_TME` field @def CAN_TSR_TME_Pos */
#define CAN_TSR_TME_Pos			((reg_bit_pos_t) 26U)
/** @brief Width of the `CAN_TSR_TME` field @def CAN_TSR_TME_Width */
#define CAN_TSR_TME_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `CAN_TSR_TME` field @def CAN_TSR_TME_Msk */
#define CAN_TSR_TME_Msk			REG_FIELD_MASK(CAN_TSR_TME_Pos, CAN_TSR_TME_Width)
/** @brief TME[2:0] bits @def CAN_TSR_TME */
#define CAN_TSR_TME				CAN_TSR_TME_Msk
/** @brief Bit position of the `CAN_TSR_TME0` field @def CAN_TSR_TME0_Pos */
#define CAN_TSR_TME0_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_TSR_TME0` field @def CAN_TSR_TME0_Msk */
#define CAN_TSR_TME0_Msk		REG_BIT_MASK(CAN_TSR_TME0_Pos)
/** @brief Transmit Mailbox 0 Empty @def CAN_TSR_TME0 */
#define CAN_TSR_TME0			CAN_TSR_TME0_Msk
/** @brief Bit position of the `CAN_TSR_TME1` field @def CAN_TSR_TME1_Pos */
#define CAN_TSR_TME1_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_TSR_TME1` field @def CAN_TSR_TME1_Msk */
#define CAN_TSR_TME1_Msk		REG_BIT_MASK(CAN_TSR_TME1_Pos)
/** @brief Transmit Mailbox 1 Empty @def CAN_TSR_TME1 */
#define CAN_TSR_TME1			CAN_TSR_TME1_Msk
/** @brief Bit position of the `CAN_TSR_TME2` field @def CAN_TSR_TME2_Pos */
#define CAN_TSR_TME2_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_TSR_TME2` field @def CAN_TSR_TME2_Msk */
#define CAN_TSR_TME2_Msk		REG_BIT_MASK(CAN_TSR_TME2_Pos)
/** @brief Transmit Mailbox 2 Empty @def CAN_TSR_TME2 */
#define CAN_TSR_TME2			CAN_TSR_TME2_Msk

/** @brief Bit position of the `CAN_TSR_LOW` field @def CAN_TSR_LOW_Pos */
#define CAN_TSR_LOW_Pos			((reg_bit_pos_t) 29U)
/** @brief Width of the `CAN_TSR_LOW` field @def CAN_TSR_LOW_Width */
#define CAN_TSR_LOW_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `CAN_TSR_LOW` field @def CAN_TSR_LOW_Msk */
#define CAN_TSR_LOW_Msk			REG_FIELD_MASK(CAN_TSR_LOW_Pos, CAN_TSR_LOW_Width)
/** @brief LOW[2:0] bits @def CAN_TSR_LOW */
#define CAN_TSR_LOW				CAN_TSR_LOW_Msk
/** @brief Bit position of the `CAN_TSR_LOW0` field @def CAN_TSR_LOW0_Pos */
#define CAN_TSR_LOW0_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_TSR_LOW0` field @def CAN_TSR_LOW0_Msk */
#define CAN_TSR_LOW0_Msk		REG_BIT_MASK(CAN_TSR_LOW0_Pos)
/** @brief Lowest Priority Flag for Mailbox 0 @def CAN_TSR_LOW0 */
#define CAN_TSR_LOW0			CAN_TSR_LOW0_Msk
/** @brief Bit position of the `CAN_TSR_LOW1` field @def CAN_TSR_LOW1_Pos */
#define CAN_TSR_LOW1_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_TSR_LOW1` field @def CAN_TSR_LOW1_Msk */
#define CAN_TSR_LOW1_Msk		REG_BIT_MASK(CAN_TSR_LOW1_Pos)
/** @brief Lowest Priority Flag for Mailbox 1 @def CAN_TSR_LOW1 */
#define CAN_TSR_LOW1			CAN_TSR_LOW1_Msk
/** @brief Bit position of the `CAN_TSR_LOW2` field @def CAN_TSR_LOW2_Pos */
#define CAN_TSR_LOW2_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_TSR_LOW2` field @def CAN_TSR_LOW2_Msk */
#define CAN_TSR_LOW2_Msk		REG_BIT_MASK(CAN_TSR_LOW2_Pos)
/** @brief Lowest Priority Flag for Mailbox 2 @def CAN_TSR_LOW2 */
#define CAN_TSR_LOW2			CAN_TSR_LOW2_Msk

// ---------------------------------- CAN_RF0R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_RF0R_FMP0` field @def CAN_RF0R_FMP0_Pos */
#define CAN_RF0R_FMP0_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_RF0R_FMP0` field @def CAN_RF0R_FMP0_Width */
#define CAN_RF0R_FMP0_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `CAN_RF0R_FMP0` field @def CAN_RF0R_FMP0_Msk */
#define CAN_RF0R_FMP0_Msk		REG_FIELD_MASK(CAN_RF0R_FMP0_Pos, CAN_RF0R_FMP0_Width)
/** @brief FIFO 0 Message Pending @def CAN_RF0R_FMP0 */
#define CAN_RF0R_FMP0			CAN_RF0R_FMP0_Msk
/** @brief Bit position of the `CAN_RF0R_FULL0` field @def CAN_RF0R_FULL0_Pos */
#define CAN_RF0R_FULL0_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_RF0R_FULL0` field @def CAN_RF0R_FULL0_Msk */
#define CAN_RF0R_FULL0_Msk		REG_BIT_MASK(CAN_RF0R_FULL0_Pos)
/** @brief FIFO 0 Full @def CAN_RF0R_FULL0 */
#define CAN_RF0R_FULL0			CAN_RF0R_FULL0_Msk
/** @brief Bit position of the `CAN_RF0R_FOVR0` field @def CAN_RF0R_FOVR0_Pos */
#define CAN_RF0R_FOVR0_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_RF0R_FOVR0` field @def CAN_RF0R_FOVR0_Msk */
#define CAN_RF0R_FOVR0_Msk		REG_BIT_MASK(CAN_RF0R_FOVR0_Pos)
/** @brief FIFO 0 Overrun @def CAN_RF0R_FOVR0 */
#define CAN_RF0R_FOVR0			CAN_RF0R_FOVR0_Msk
/** @brief Bit position of the `CAN_RF0R_RFOM0` field @def CAN_RF0R_RFOM0_Pos */
#define CAN_RF0R_RFOM0_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_RF0R_RFOM0` field @def CAN_RF0R_RFOM0_Msk */
#define CAN_RF0R_RFOM0_Msk		REG_BIT_MASK(CAN_RF0R_RFOM0_Pos)
/** @brief Release FIFO 0 Output Mailbox @def CAN_RF0R_RFOM0 */
#define CAN_RF0R_RFOM0			CAN_RF0R_RFOM0_Msk

// ---------------------------------- CAN_RF1R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_RF1R_FMP1` field @def CAN_RF1R_FMP1_Pos */
#define CAN_RF1R_FMP1_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_RF1R_FMP1` field @def CAN_RF1R_FMP1_Width */
#define CAN_RF1R_FMP1_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `CAN_RF1R_FMP1` field @def CAN_RF1R_FMP1_Msk */
#define CAN_RF1R_FMP1_Msk		REG_FIELD_MASK(CAN_RF1R_FMP1_Pos, CAN_RF1R_FMP1_Width)
/** @brief FIFO 1 Message Pending @def CAN_RF1R_FMP1 */
#define CAN_RF1R_FMP1			CAN_RF1R_FMP1_Msk
/** @brief Bit position of the `CAN_RF1R_FULL1` field @def CAN_RF1R_FULL1_Pos */
#define CAN_RF1R_FULL1_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_RF1R_FULL1` field @def CAN_RF1R_FULL1_Msk */
#define CAN_RF1R_FULL1_Msk		REG_BIT_MASK(CAN_RF1R_FULL1_Pos)
/** @brief FIFO 1 Full @def CAN_RF1R_FULL1 */
#define CAN_RF1R_FULL1			CAN_RF1R_FULL1_Msk
/** @brief Bit position of the `CAN_RF1R_FOVR1` field @def CAN_RF1R_FOVR1_Pos */
#define CAN_RF1R_FOVR1_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_RF1R_FOVR1` field @def CAN_RF1R_FOVR1_Msk */
#define CAN_RF1R_FOVR1_Msk		REG_BIT_MASK(CAN_RF1R_FOVR1_Pos)
/** @brief FIFO 1 Overrun @def CAN_RF1R_FOVR1 */
#define CAN_RF1R_FOVR1			CAN_RF1R_FOVR1_Msk
/** @brief Bit position of the `CAN_RF1R_RFOM1` field @def CAN_RF1R_RFOM1_Pos */
#define CAN_RF1R_RFOM1_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_RF1R_RFOM1` field @def CAN_RF1R_RFOM1_Msk */
#define CAN_RF1R_RFOM1_Msk		REG_BIT_MASK(CAN_RF1R_RFOM1_Pos)
/** @brief Release FIFO 1 Output Mailbox @def CAN_RF1R_RFOM1 */
#define CAN_RF1R_RFOM1			CAN_RF1R_RFOM1_Msk

// ----------------------------------- CAN_IER Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_IER_TMEIE` field @def CAN_IER_TMEIE_Pos */
#define CAN_IER_TMEIE_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_IER_TMEIE` field @def CAN_IER_TMEIE_Msk */
#define CAN_IER_TMEIE_Msk		REG_BIT_MASK(CAN_IER_TMEIE_Pos)
/** @brief Transmit Mailbox Empty Interrupt Enable @def CAN_IER_TMEIE */
#define CAN_IER_TMEIE			CAN_IER_TMEIE_Msk
/** @brief Bit position of the `CAN_IER_FMPIE0` field @def CAN_IER_FMPIE0_Pos */
#define CAN_IER_FMPIE0_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_IER_FMPIE0` field @def CAN_IER_FMPIE0_Msk */
#define CAN_IER_FMPIE0_Msk		REG_BIT_MASK(CAN_IER_FMPIE0_Pos)
/** @brief FIFO Message Pending Interrupt Enable @def CAN_IER_FMPIE0 */
#define CAN_IER_FMPIE0			CAN_IER_FMPIE0_Msk
/** @brief Bit position of the `CAN_IER_FFIE0` field @def CAN_IER_FFIE0_Pos */
#define CAN_IER_FFIE0_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_IER_FFIE0` field @def CAN_IER_FFIE0_Msk */
#define CAN_IER_FFIE0_Msk		REG_BIT_MASK(CAN_IER_FFIE0_Pos)
/** @brief FIFO Full Interrupt Enable @def CAN_IER_FFIE0 */
#define CAN_IER_FFIE0			CAN_IER_FFIE0_Msk
/** @brief Bit position of the `CAN_IER_FOVIE0` field @def CAN_IER_FOVIE0_Pos */
#define CAN_IER_FOVIE0_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_IER_FOVIE0` field @def CAN_IER_FOVIE0_Msk */
#define CAN_IER_FOVIE0_Msk		REG_BIT_MASK(CAN_IER_FOVIE0_Pos)
/** @brief FIFO Overrun Interrupt Enable @def CAN_IER_FOVIE0 */
#define CAN_IER_FOVIE0			CAN_IER_FOVIE0_Msk
/** @brief Bit position of the `CAN_IER_FMPIE1` field @def CAN_IER_FMPIE1_Pos */
#define CAN_IER_FMPIE1_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_IER_FMPIE1` field @def CAN_IER_FMPIE1_Msk */
#define CAN_IER_FMPIE1_Msk		REG_BIT_MASK(CAN_IER_FMPIE1_Pos)
/** @brief FIFO Message Pending Interrupt Enable @def CAN_IER_FMPIE1 */
#define CAN_IER_FMPIE1			CAN_IER_FMPIE1_Msk
/** @brief Bit position of the `CAN_IER_FFIE1` field @def CAN_IER_FFIE1_Pos */
#define CAN_IER_FFIE1_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_IER_FFIE1` field @def CAN_IER_FFIE1_Msk */
#define CAN_IER_FFIE1_Msk		REG_BIT_MASK(CAN_IER_FFIE1_Pos)
/** @brief FIFO Full Interrupt Enable @def CAN_IER_FFIE1 */
#define CAN_IER_FFIE1			CAN_IER_FFIE1_Msk
/** @brief Bit position of the `CAN_IER_FOVIE1` field @def CAN_IER_FOVIE1_Pos */
#define CAN_IER_FOVIE1_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_IER_FOVIE1` field @def CAN_IER_FOVIE1_Msk */
#define CAN_IER_FOVIE1_Msk		REG_BIT_MASK(CAN_IER_FOVIE1_Pos)
/** @brief FIFO Overrun Interrupt Enable @def CAN_IER_FOVIE1 */
#define CAN_IER_FOVIE1			CAN_IER_FOVIE1_Msk
/** @brief Bit position of the `CAN_IER_EWGIE` field @def CAN_IER_EWGIE_Pos */
#define CAN_IER_EWGIE_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_IER_EWGIE` field @def CAN_IER_EWGIE_Msk */
#define CAN_IER_EWGIE_Msk		REG_BIT_MASK(CAN_IER_EWGIE_Pos)
/** @brief Error Warning Interrupt Enable @def CAN_IER_EWGIE */
#define CAN_IER_EWGIE			CAN_IER_EWGIE_Msk
/** @brief Bit position of the `CAN_IER_EPVIE` field @def CAN_IER_EPVIE_Pos */
#define CAN_IER_EPVIE_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_IER_EPVIE` field @def CAN_IER_EPVIE_Msk */
#define CAN_IER_EPVIE_Msk		REG_BIT_MASK(CAN_IER_EPVIE_Pos)
/** @brief Error Passive Interrupt Enable @def CAN_IER_EPVIE */
#define CAN_IER_EPVIE			CAN_IER_EPVIE_Msk
/** @brief Bit position of the `CAN_IER_BOFIE` field @def CAN_IER_BOFIE_Pos */
#define CAN_IER_BOFIE_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_IER_BOFIE` field @def CAN_IER_BOFIE_Msk */
#define CAN_IER_BOFIE_Msk		REG_BIT_MASK(CAN_IER_BOFIE_Pos)
/** @brief Bus-Off Interrupt Enable @def CAN_IER_BOFIE */
#define CAN_IER_BOFIE			CAN_IER_BOFIE_Msk
/** @brief Bit position of the `CAN_IER_LECIE` field @def CAN_IER_LECIE_Pos */
#define CAN_IER_LECIE_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_IER_LECIE` field @def CAN_IER_LECIE_Msk */
#define CAN_IER_LECIE_Msk		REG_BIT_MASK(CAN_IER_LECIE_Pos)
/** @brief Last Error Code Interrupt Enable @def CAN_IER_LECIE */
#define CAN_IER_LECIE			CAN_IER_LECIE_Msk
/** @brief Bit position of the `CAN_IER_ERRIE` field @def CAN_IER_ERRIE_Pos */
#define CAN_IER_ERRIE_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_IER_ERRIE` field @def CAN_IER_ERRIE_Msk */
#define CAN_IER_ERRIE_Msk		REG_BIT_MASK(CAN_IER_ERRIE_Pos)
/** @brief Error Interrupt Enable @def CAN_IER_ERRIE */
#define CAN_IER_ERRIE			CAN_IER_ERRIE_Msk
/** @brief Bit position of the `CAN_IER_WKUIE` field @def CAN_IER_WKUIE_Pos */
#define CAN_IER_WKUIE_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_IER_WKUIE` field @def CAN_IER_WKUIE_Msk */
#define CAN_IER_WKUIE_Msk		REG_BIT_MASK(CAN_IER_WKUIE_Pos)
/** @brief Wakeup Interrupt Enable @def CAN_IER_WKUIE */
#define CAN_IER_WKUIE			CAN_IER_WKUIE_Msk
/** @brief Bit position of the `CAN_IER_SLKIE` field @def CAN_IER_SLKIE_Pos */
#define CAN_IER_SLKIE_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_IER_SLKIE` field @def CAN_IER_SLKIE_Msk */
#define CAN_IER_SLKIE_Msk		REG_BIT_MASK(CAN_IER_SLKIE_Pos)
/** @brief Sleep Interrupt Enable @def CAN_IER_SLKIE */
#define CAN_IER_SLKIE			CAN_IER_SLKIE_Msk

// ----------------------------------- CAN_ESR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_ESR_EWGF` field @def CAN_ESR_EWGF_Pos */
#define CAN_ESR_EWGF_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_ESR_EWGF` field @def CAN_ESR_EWGF_Msk */
#define CAN_ESR_EWGF_Msk		REG_BIT_MASK(CAN_ESR_EWGF_Pos)
/** @brief Error Warning Flag @def CAN_ESR_EWGF */
#define CAN_ESR_EWGF			CAN_ESR_EWGF_Msk
/** @brief Bit position of the `CAN_ESR_EPVF` field @def CAN_ESR_EPVF_Pos */
#define CAN_ESR_EPVF_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_ESR_EPVF` field @def CAN_ESR_EPVF_Msk */
#define CAN_ESR_EPVF_Msk		REG_BIT_MASK(CAN_ESR_EPVF_Pos)
/** @brief Error Passive Flag @def CAN_ESR_EPVF */
#define CAN_ESR_EPVF			CAN_ESR_EPVF_Msk
/** @brief Bit position of the `CAN_ESR_BOFF` field @def CAN_ESR_BOFF_Pos */
#define CAN_ESR_BOFF_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_ESR_BOFF` field @def CAN_ESR_BOFF_Msk */
#define CAN_ESR_BOFF_Msk		REG_BIT_MASK(CAN_ESR_BOFF_Pos)
/** @brief Bus-Off Flag @def CAN_ESR_BOFF */
#define CAN_ESR_BOFF			CAN_ESR_BOFF_Msk

/** @brief Bit position of the `CAN_ESR_LEC` field @def CAN_ESR_LEC_Pos */
#define CAN_ESR_LEC_Pos			((reg_bit_pos_t) 4U)
/** @brief Width of the `CAN_ESR_LEC` field @def CAN_ESR_LEC_Width */
#define CAN_ESR_LEC_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `CAN_ESR_LEC` field @def CAN_ESR_LEC_Msk */
#define CAN_ESR_LEC_Msk			REG_FIELD_MASK(CAN_ESR_LEC_Pos, CAN_ESR_LEC_Width)
/** @brief LEC[2:0] bits (Last Error Code) @def CAN_ESR_LEC */
#define CAN_ESR_LEC				CAN_ESR_LEC_Msk
/** @brief Register or selector value represented by `CAN_ESR_LEC_0` @def CAN_ESR_LEC_0 */
#define CAN_ESR_LEC_0			(0x1UL << CAN_ESR_LEC_Pos)
/** @brief Register or selector value represented by `CAN_ESR_LEC_1` @def CAN_ESR_LEC_1 */
#define CAN_ESR_LEC_1			(0x2UL << CAN_ESR_LEC_Pos)
/** @brief Register or selector value represented by `CAN_ESR_LEC_2` @def CAN_ESR_LEC_2 */
#define CAN_ESR_LEC_2			(0x4UL << CAN_ESR_LEC_Pos)

/** @brief Bit position of the `CAN_ESR_TEC` field @def CAN_ESR_TEC_Pos */
#define CAN_ESR_TEC_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_ESR_TEC` field @def CAN_ESR_TEC_Width */
#define CAN_ESR_TEC_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_ESR_TEC` field @def CAN_ESR_TEC_Msk */
#define CAN_ESR_TEC_Msk			REG_FIELD_MASK(CAN_ESR_TEC_Pos, CAN_ESR_TEC_Width)
/** @brief Least significant byte of the 9-bit Transmit Error Counter @def CAN_ESR_TEC */
#define CAN_ESR_TEC				CAN_ESR_TEC_Msk
/** @brief Bit position of the `CAN_ESR_REC` field @def CAN_ESR_REC_Pos */
#define CAN_ESR_REC_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_ESR_REC` field @def CAN_ESR_REC_Width */
#define CAN_ESR_REC_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_ESR_REC` field @def CAN_ESR_REC_Msk */
#define CAN_ESR_REC_Msk			REG_FIELD_MASK(CAN_ESR_REC_Pos, CAN_ESR_REC_Width)
/** @brief Receive Error Counter @def CAN_ESR_REC */
#define CAN_ESR_REC				CAN_ESR_REC_Msk

// ----------------------------------- CAN_BTR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_BTR_BRP` field @def CAN_BTR_BRP_Pos */
#define CAN_BTR_BRP_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_BTR_BRP` field @def CAN_BTR_BRP_Width */
#define CAN_BTR_BRP_Width		((reg_field_width_t) 10U)
/** @brief Register-positioned mask for the `CAN_BTR_BRP` field @def CAN_BTR_BRP_Msk */
#define CAN_BTR_BRP_Msk			REG_FIELD_MASK(CAN_BTR_BRP_Pos, CAN_BTR_BRP_Width)
/** @brief Baud Rate Prescaler @def CAN_BTR_BRP */
#define CAN_BTR_BRP				CAN_BTR_BRP_Msk
/** @brief Bit position of the `CAN_BTR_TS1` field @def CAN_BTR_TS1_Pos */
#define CAN_BTR_TS1_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_BTR_TS1` field @def CAN_BTR_TS1_Width */
#define CAN_BTR_TS1_Width		((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `CAN_BTR_TS1` field @def CAN_BTR_TS1_Msk */
#define CAN_BTR_TS1_Msk			REG_FIELD_MASK(CAN_BTR_TS1_Pos, CAN_BTR_TS1_Width)
/** @brief Time Segment 1 @def CAN_BTR_TS1 */
#define CAN_BTR_TS1				CAN_BTR_TS1_Msk
/** @brief Register or selector value represented by `CAN_BTR_TS1_0` @def CAN_BTR_TS1_0 */
#define CAN_BTR_TS1_0			(0x1UL << CAN_BTR_TS1_Pos)
/** @brief Register or selector value represented by `CAN_BTR_TS1_1` @def CAN_BTR_TS1_1 */
#define CAN_BTR_TS1_1			(0x2UL << CAN_BTR_TS1_Pos)
/** @brief Register or selector value represented by `CAN_BTR_TS1_2` @def CAN_BTR_TS1_2 */
#define CAN_BTR_TS1_2			(0x4UL << CAN_BTR_TS1_Pos)
/** @brief Register or selector value represented by `CAN_BTR_TS1_3` @def CAN_BTR_TS1_3 */
#define CAN_BTR_TS1_3			(0x8UL << CAN_BTR_TS1_Pos)
/** @brief Bit position of the `CAN_BTR_TS2` field @def CAN_BTR_TS2_Pos */
#define CAN_BTR_TS2_Pos			((reg_bit_pos_t) 20U)
/** @brief Width of the `CAN_BTR_TS2` field @def CAN_BTR_TS2_Width */
#define CAN_BTR_TS2_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `CAN_BTR_TS2` field @def CAN_BTR_TS2_Msk */
#define CAN_BTR_TS2_Msk			REG_FIELD_MASK(CAN_BTR_TS2_Pos, CAN_BTR_TS2_Width)
/** @brief Time Segment 2 @def CAN_BTR_TS2 */
#define CAN_BTR_TS2				CAN_BTR_TS2_Msk
/** @brief Register or selector value represented by `CAN_BTR_TS2_0` @def CAN_BTR_TS2_0 */
#define CAN_BTR_TS2_0			(0x1UL << CAN_BTR_TS2_Pos)
/** @brief Register or selector value represented by `CAN_BTR_TS2_1` @def CAN_BTR_TS2_1 */
#define CAN_BTR_TS2_1			(0x2UL << CAN_BTR_TS2_Pos)
/** @brief Register or selector value represented by `CAN_BTR_TS2_2` @def CAN_BTR_TS2_2 */
#define CAN_BTR_TS2_2			(0x4UL << CAN_BTR_TS2_Pos)
/** @brief Bit position of the `CAN_BTR_SJW` field @def CAN_BTR_SJW_Pos */
#define CAN_BTR_SJW_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_BTR_SJW` field @def CAN_BTR_SJW_Width */
#define CAN_BTR_SJW_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `CAN_BTR_SJW` field @def CAN_BTR_SJW_Msk */
#define CAN_BTR_SJW_Msk			REG_FIELD_MASK(CAN_BTR_SJW_Pos, CAN_BTR_SJW_Width)
/** @brief Resynchronization Jump Width @def CAN_BTR_SJW */
#define CAN_BTR_SJW				CAN_BTR_SJW_Msk
/** @brief Register or selector value represented by `CAN_BTR_SJW_0` @def CAN_BTR_SJW_0 */
#define CAN_BTR_SJW_0			(0x1UL << CAN_BTR_SJW_Pos)
/** @brief Register or selector value represented by `CAN_BTR_SJW_1` @def CAN_BTR_SJW_1 */
#define CAN_BTR_SJW_1			(0x2UL << CAN_BTR_SJW_Pos)
/** @brief Bit position of the `CAN_BTR_LBKM` field @def CAN_BTR_LBKM_Pos */
#define CAN_BTR_LBKM_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_BTR_LBKM` field @def CAN_BTR_LBKM_Msk */
#define CAN_BTR_LBKM_Msk		REG_BIT_MASK(CAN_BTR_LBKM_Pos)
/** @brief Loop Back Mode (Debug) @def CAN_BTR_LBKM */
#define CAN_BTR_LBKM			CAN_BTR_LBKM_Msk
/** @brief Bit position of the `CAN_BTR_SILM` field @def CAN_BTR_SILM_Pos */
#define CAN_BTR_SILM_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_BTR_SILM` field @def CAN_BTR_SILM_Msk */
#define CAN_BTR_SILM_Msk		REG_BIT_MASK(CAN_BTR_SILM_Pos)
/** @brief Silent Mode @def CAN_BTR_SILM */
#define CAN_BTR_SILM			CAN_BTR_SILM_Msk

// ----------------------------------- CAN Mailbox Register Defines ----------------------------------- //
// ---------------------------------- CAN_TI0R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_TI0R_TXRQ` field @def CAN_TI0R_TXRQ_Pos */
#define CAN_TI0R_TXRQ_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_TI0R_TXRQ` field @def CAN_TI0R_TXRQ_Msk */
#define CAN_TI0R_TXRQ_Msk		REG_BIT_MASK(CAN_TI0R_TXRQ_Pos)
/** @brief Transmit Mailbox Request @def CAN_TI0R_TXRQ */
#define CAN_TI0R_TXRQ			CAN_TI0R_TXRQ_Msk
/** @brief Bit position of the `CAN_TI0R_RTR` field @def CAN_TI0R_RTR_Pos */
#define CAN_TI0R_RTR_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_TI0R_RTR` field @def CAN_TI0R_RTR_Msk */
#define CAN_TI0R_RTR_Msk		REG_BIT_MASK(CAN_TI0R_RTR_Pos)
/** @brief Remote Transmission Request @def CAN_TI0R_RTR */
#define CAN_TI0R_RTR			CAN_TI0R_RTR_Msk
/** @brief Bit position of the `CAN_TI0R_IDE` field @def CAN_TI0R_IDE_Pos */
#define CAN_TI0R_IDE_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_TI0R_IDE` field @def CAN_TI0R_IDE_Msk */
#define CAN_TI0R_IDE_Msk		REG_BIT_MASK(CAN_TI0R_IDE_Pos)
/** @brief Identifier Extension @def CAN_TI0R_IDE */
#define CAN_TI0R_IDE			CAN_TI0R_IDE_Msk
/** @brief Bit position of the `CAN_TI0R_EXID` field @def CAN_TI0R_EXID_Pos */
#define CAN_TI0R_EXID_Pos		((reg_bit_pos_t) 3U)
/** @brief Width of the `CAN_TI0R_EXID` field @def CAN_TI0R_EXID_Width */
#define CAN_TI0R_EXID_Width		((reg_field_width_t) 18U)
/** @brief Register-positioned mask for the `CAN_TI0R_EXID` field @def CAN_TI0R_EXID_Msk */
#define CAN_TI0R_EXID_Msk		REG_FIELD_MASK(CAN_TI0R_EXID_Pos, CAN_TI0R_EXID_Width)
/** @brief Extended Identifier @def CAN_TI0R_EXID */
#define CAN_TI0R_EXID			CAN_TI0R_EXID_Msk
/** @brief Bit position of the `CAN_TI0R_STID` field @def CAN_TI0R_STID_Pos */
#define CAN_TI0R_STID_Pos		((reg_bit_pos_t) 21U)
/** @brief Width of the `CAN_TI0R_STID` field @def CAN_TI0R_STID_Width */
#define CAN_TI0R_STID_Width		((reg_field_width_t) 11U)
/** @brief Register-positioned mask for the `CAN_TI0R_STID` field @def CAN_TI0R_STID_Msk */
#define CAN_TI0R_STID_Msk		REG_FIELD_MASK(CAN_TI0R_STID_Pos, CAN_TI0R_STID_Width)
/** @brief Standard Identifier or Extended Identifier @def CAN_TI0R_STID */
#define CAN_TI0R_STID			CAN_TI0R_STID_Msk

// ---------------------------------- CAN_TDT0R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_TDT0R_DLC` field @def CAN_TDT0R_DLC_Pos */
#define CAN_TDT0R_DLC_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_TDT0R_DLC` field @def CAN_TDT0R_DLC_Width */
#define CAN_TDT0R_DLC_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `CAN_TDT0R_DLC` field @def CAN_TDT0R_DLC_Msk */
#define CAN_TDT0R_DLC_Msk			REG_FIELD_MASK(CAN_TDT0R_DLC_Pos, CAN_TDT0R_DLC_Width)
/** @brief Data Length Code @def CAN_TDT0R_DLC */
#define CAN_TDT0R_DLC				CAN_TDT0R_DLC_Msk
/** @brief Bit position of the `CAN_TDT0R_TGT` field @def CAN_TDT0R_TGT_Pos */
#define CAN_TDT0R_TGT_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDT0R_TGT` field @def CAN_TDT0R_TGT_Msk */
#define CAN_TDT0R_TGT_Msk			REG_BIT_MASK(CAN_TDT0R_TGT_Pos)
/** @brief Transmit Global Time @def CAN_TDT0R_TGT */
#define CAN_TDT0R_TGT				CAN_TDT0R_TGT_Msk
/** @brief Bit position of the `CAN_TDT0R_TIME` field @def CAN_TDT0R_TIME_Pos */
#define CAN_TDT0R_TIME_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_TDT0R_TIME` field @def CAN_TDT0R_TIME_Width */
#define CAN_TDT0R_TIME_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `CAN_TDT0R_TIME` field @def CAN_TDT0R_TIME_Msk */
#define CAN_TDT0R_TIME_Msk			REG_FIELD_MASK(CAN_TDT0R_TIME_Pos, CAN_TDT0R_TIME_Width)
/** @brief Message Time Stamp @def CAN_TDT0R_TIME */
#define CAN_TDT0R_TIME				CAN_TDT0R_TIME_Msk

// ---------------------------------- CAN_TDL0R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_TDL0R_DATA0` field @def CAN_TDL0R_DATA0_Pos */
#define CAN_TDL0R_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_TDL0R_DATA0` field @def CAN_TDL0R_DATA0_Width */
#define CAN_TDL0R_DATA0_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDL0R_DATA0` field @def CAN_TDL0R_DATA0_Msk */
#define CAN_TDL0R_DATA0_Msk			REG_FIELD_MASK(CAN_TDL0R_DATA0_Pos, CAN_TDL0R_DATA0_Width)
/** @brief Data byte 0 @def CAN_TDL0R_DATA0 */
#define CAN_TDL0R_DATA0				CAN_TDL0R_DATA0_Msk
/** @brief Bit position of the `CAN_TDL0R_DATA1` field @def CAN_TDL0R_DATA1_Pos */
#define CAN_TDL0R_DATA1_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_TDL0R_DATA1` field @def CAN_TDL0R_DATA1_Width */
#define CAN_TDL0R_DATA1_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDL0R_DATA1` field @def CAN_TDL0R_DATA1_Msk */
#define CAN_TDL0R_DATA1_Msk			REG_FIELD_MASK(CAN_TDL0R_DATA1_Pos, CAN_TDL0R_DATA1_Width)
/** @brief Data byte 1 @def CAN_TDL0R_DATA1 */
#define CAN_TDL0R_DATA1				CAN_TDL0R_DATA1_Msk
/** @brief Bit position of the `CAN_TDL0R_DATA2` field @def CAN_TDL0R_DATA2_Pos */
#define CAN_TDL0R_DATA2_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_TDL0R_DATA2` field @def CAN_TDL0R_DATA2_Width */
#define CAN_TDL0R_DATA2_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDL0R_DATA2` field @def CAN_TDL0R_DATA2_Msk */
#define CAN_TDL0R_DATA2_Msk			REG_FIELD_MASK(CAN_TDL0R_DATA2_Pos, CAN_TDL0R_DATA2_Width)
/** @brief Data byte 2 @def CAN_TDL0R_DATA2 */
#define CAN_TDL0R_DATA2				CAN_TDL0R_DATA2_Msk
/** @brief Bit position of the `CAN_TDL0R_DATA3` field @def CAN_TDL0R_DATA3_Pos */
#define CAN_TDL0R_DATA3_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_TDL0R_DATA3` field @def CAN_TDL0R_DATA3_Width */
#define CAN_TDL0R_DATA3_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDL0R_DATA3` field @def CAN_TDL0R_DATA3_Msk */
#define CAN_TDL0R_DATA3_Msk			REG_FIELD_MASK(CAN_TDL0R_DATA3_Pos, CAN_TDL0R_DATA3_Width)
/** @brief Data byte 3 @def CAN_TDL0R_DATA3 */
#define CAN_TDL0R_DATA3				CAN_TDL0R_DATA3_Msk

// ---------------------------------- CAN_TDH0R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_TDH0R_DATA4` field @def CAN_TDH0R_DATA4_Pos */
#define CAN_TDH0R_DATA4_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_TDH0R_DATA4` field @def CAN_TDH0R_DATA4_Width */
#define CAN_TDH0R_DATA4_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDH0R_DATA4` field @def CAN_TDH0R_DATA4_Msk */
#define CAN_TDH0R_DATA4_Msk			REG_FIELD_MASK(CAN_TDH0R_DATA4_Pos, CAN_TDH0R_DATA4_Width)
/** @brief Data byte 4 @def CAN_TDH0R_DATA4 */
#define CAN_TDH0R_DATA4				CAN_TDH0R_DATA4_Msk
/** @brief Bit position of the `CAN_TDH0R_DATA5` field @def CAN_TDH0R_DATA5_Pos */
#define CAN_TDH0R_DATA5_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_TDH0R_DATA5` field @def CAN_TDH0R_DATA5_Width */
#define CAN_TDH0R_DATA5_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDH0R_DATA5` field @def CAN_TDH0R_DATA5_Msk */
#define CAN_TDH0R_DATA5_Msk			REG_FIELD_MASK(CAN_TDH0R_DATA5_Pos, CAN_TDH0R_DATA5_Width)
/** @brief Data byte 5 @def CAN_TDH0R_DATA5 */
#define CAN_TDH0R_DATA5				CAN_TDH0R_DATA5_Msk
/** @brief Bit position of the `CAN_TDH0R_DATA6` field @def CAN_TDH0R_DATA6_Pos */
#define CAN_TDH0R_DATA6_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_TDH0R_DATA6` field @def CAN_TDH0R_DATA6_Width */
#define CAN_TDH0R_DATA6_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDH0R_DATA6` field @def CAN_TDH0R_DATA6_Msk */
#define CAN_TDH0R_DATA6_Msk			REG_FIELD_MASK(CAN_TDH0R_DATA6_Pos, CAN_TDH0R_DATA6_Width)
/** @brief Data byte 6 @def CAN_TDH0R_DATA6 */
#define CAN_TDH0R_DATA6				CAN_TDH0R_DATA6_Msk
/** @brief Bit position of the `CAN_TDH0R_DATA7` field @def CAN_TDH0R_DATA7_Pos */
#define CAN_TDH0R_DATA7_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_TDH0R_DATA7` field @def CAN_TDH0R_DATA7_Width */
#define CAN_TDH0R_DATA7_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDH0R_DATA7` field @def CAN_TDH0R_DATA7_Msk */
#define CAN_TDH0R_DATA7_Msk			REG_FIELD_MASK(CAN_TDH0R_DATA7_Pos, CAN_TDH0R_DATA7_Width)
/** @brief Data byte 7 @def CAN_TDH0R_DATA7 */
#define CAN_TDH0R_DATA7				CAN_TDH0R_DATA7_Msk

// ---------------------------------- CAN_TI1R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_TI1R_TXRQ` field @def CAN_TI1R_TXRQ_Pos */
#define CAN_TI1R_TXRQ_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_TI1R_TXRQ` field @def CAN_TI1R_TXRQ_Msk */
#define CAN_TI1R_TXRQ_Msk		REG_BIT_MASK(CAN_TI1R_TXRQ_Pos)
/** @brief Transmit Mailbox Request @def CAN_TI1R_TXRQ */
#define CAN_TI1R_TXRQ			CAN_TI1R_TXRQ_Msk
/** @brief Bit position of the `CAN_TI1R_RTR` field @def CAN_TI1R_RTR_Pos */
#define CAN_TI1R_RTR_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_TI1R_RTR` field @def CAN_TI1R_RTR_Msk */
#define CAN_TI1R_RTR_Msk		REG_BIT_MASK(CAN_TI1R_RTR_Pos)
/** @brief Remote Transmission Request @def CAN_TI1R_RTR */
#define CAN_TI1R_RTR			CAN_TI1R_RTR_Msk
/** @brief Bit position of the `CAN_TI1R_IDE` field @def CAN_TI1R_IDE_Pos */
#define CAN_TI1R_IDE_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_TI1R_IDE` field @def CAN_TI1R_IDE_Msk */
#define CAN_TI1R_IDE_Msk		REG_BIT_MASK(CAN_TI1R_IDE_Pos)
/** @brief Identifier Extension @def CAN_TI1R_IDE */
#define CAN_TI1R_IDE			CAN_TI1R_IDE_Msk
/** @brief Bit position of the `CAN_TI1R_EXID` field @def CAN_TI1R_EXID_Pos */
#define CAN_TI1R_EXID_Pos		((reg_bit_pos_t) 3U)
/** @brief Width of the `CAN_TI1R_EXID` field @def CAN_TI1R_EXID_Width */
#define CAN_TI1R_EXID_Width		((reg_field_width_t) 18U)
/** @brief Register-positioned mask for the `CAN_TI1R_EXID` field @def CAN_TI1R_EXID_Msk */
#define CAN_TI1R_EXID_Msk		REG_FIELD_MASK(CAN_TI1R_EXID_Pos, CAN_TI1R_EXID_Width)
/** @brief Extended Identifier @def CAN_TI1R_EXID */
#define CAN_TI1R_EXID			CAN_TI1R_EXID_Msk
/** @brief Bit position of the `CAN_TI1R_STID` field @def CAN_TI1R_STID_Pos */
#define CAN_TI1R_STID_Pos		((reg_bit_pos_t) 21U)
/** @brief Width of the `CAN_TI1R_STID` field @def CAN_TI1R_STID_Width */
#define CAN_TI1R_STID_Width		((reg_field_width_t) 11U)
/** @brief Register-positioned mask for the `CAN_TI1R_STID` field @def CAN_TI1R_STID_Msk */
#define CAN_TI1R_STID_Msk		REG_FIELD_MASK(CAN_TI1R_STID_Pos, CAN_TI1R_STID_Width)
/** @brief Standard Identifier or Extended Identifier @def CAN_TI1R_STID */
#define CAN_TI1R_STID			CAN_TI1R_STID_Msk

// ---------------------------------- CAN_TDT1R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_TDT1R_DLC` field @def CAN_TDT1R_DLC_Pos */
#define CAN_TDT1R_DLC_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_TDT1R_DLC` field @def CAN_TDT1R_DLC_Width */
#define CAN_TDT1R_DLC_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `CAN_TDT1R_DLC` field @def CAN_TDT1R_DLC_Msk */
#define CAN_TDT1R_DLC_Msk			REG_FIELD_MASK(CAN_TDT1R_DLC_Pos, CAN_TDT1R_DLC_Width)
/** @brief Data Length Code @def CAN_TDT1R_DLC */
#define CAN_TDT1R_DLC				CAN_TDT1R_DLC_Msk
/** @brief Bit position of the `CAN_TDT1R_TGT` field @def CAN_TDT1R_TGT_Pos */
#define CAN_TDT1R_TGT_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDT1R_TGT` field @def CAN_TDT1R_TGT_Msk */
#define CAN_TDT1R_TGT_Msk			REG_BIT_MASK(CAN_TDT1R_TGT_Pos)
/** @brief Transmit Global Time @def CAN_TDT1R_TGT */
#define CAN_TDT1R_TGT				CAN_TDT1R_TGT_Msk
/** @brief Bit position of the `CAN_TDT1R_TIME` field @def CAN_TDT1R_TIME_Pos */
#define CAN_TDT1R_TIME_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_TDT1R_TIME` field @def CAN_TDT1R_TIME_Width */
#define CAN_TDT1R_TIME_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `CAN_TDT1R_TIME` field @def CAN_TDT1R_TIME_Msk */
#define CAN_TDT1R_TIME_Msk			REG_FIELD_MASK(CAN_TDT1R_TIME_Pos, CAN_TDT1R_TIME_Width)
/** @brief Message Time Stamp @def CAN_TDT1R_TIME */
#define CAN_TDT1R_TIME				CAN_TDT1R_TIME_Msk

// ---------------------------------- CAN_TDL1R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_TDL1R_DATA0` field @def CAN_TDL1R_DATA0_Pos */
#define CAN_TDL1R_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_TDL1R_DATA0` field @def CAN_TDL1R_DATA0_Width */
#define CAN_TDL1R_DATA0_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDL1R_DATA0` field @def CAN_TDL1R_DATA0_Msk */
#define CAN_TDL1R_DATA0_Msk			REG_FIELD_MASK(CAN_TDL1R_DATA0_Pos, CAN_TDL1R_DATA0_Width)
/** @brief Data byte 0 @def CAN_TDL1R_DATA0 */
#define CAN_TDL1R_DATA0				CAN_TDL1R_DATA0_Msk
/** @brief Bit position of the `CAN_TDL1R_DATA1` field @def CAN_TDL1R_DATA1_Pos */
#define CAN_TDL1R_DATA1_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_TDL1R_DATA1` field @def CAN_TDL1R_DATA1_Width */
#define CAN_TDL1R_DATA1_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDL1R_DATA1` field @def CAN_TDL1R_DATA1_Msk */
#define CAN_TDL1R_DATA1_Msk			REG_FIELD_MASK(CAN_TDL1R_DATA1_Pos, CAN_TDL1R_DATA1_Width)
/** @brief Data byte 1 @def CAN_TDL1R_DATA1 */
#define CAN_TDL1R_DATA1				CAN_TDL1R_DATA1_Msk
/** @brief Bit position of the `CAN_TDL1R_DATA2` field @def CAN_TDL1R_DATA2_Pos */
#define CAN_TDL1R_DATA2_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_TDL1R_DATA2` field @def CAN_TDL1R_DATA2_Width */
#define CAN_TDL1R_DATA2_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDL1R_DATA2` field @def CAN_TDL1R_DATA2_Msk */
#define CAN_TDL1R_DATA2_Msk			REG_FIELD_MASK(CAN_TDL1R_DATA2_Pos, CAN_TDL1R_DATA2_Width)
/** @brief Data byte 2 @def CAN_TDL1R_DATA2 */
#define CAN_TDL1R_DATA2				CAN_TDL1R_DATA2_Msk
/** @brief Bit position of the `CAN_TDL1R_DATA3` field @def CAN_TDL1R_DATA3_Pos */
#define CAN_TDL1R_DATA3_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_TDL1R_DATA3` field @def CAN_TDL1R_DATA3_Width */
#define CAN_TDL1R_DATA3_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDL1R_DATA3` field @def CAN_TDL1R_DATA3_Msk */
#define CAN_TDL1R_DATA3_Msk			REG_FIELD_MASK(CAN_TDL1R_DATA3_Pos, CAN_TDL1R_DATA3_Width)
/** @brief Data byte 3 @def CAN_TDL1R_DATA3 */
#define CAN_TDL1R_DATA3				CAN_TDL1R_DATA3_Msk

// ---------------------------------- CAN_TDH1R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_TDH1R_DATA4` field @def CAN_TDH1R_DATA4_Pos */
#define CAN_TDH1R_DATA4_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_TDH1R_DATA4` field @def CAN_TDH1R_DATA4_Width */
#define CAN_TDH1R_DATA4_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDH1R_DATA4` field @def CAN_TDH1R_DATA4_Msk */
#define CAN_TDH1R_DATA4_Msk			REG_FIELD_MASK(CAN_TDH1R_DATA4_Pos, CAN_TDH1R_DATA4_Width)
/** @brief Data byte 4 @def CAN_TDH1R_DATA4 */
#define CAN_TDH1R_DATA4				CAN_TDH1R_DATA4_Msk
/** @brief Bit position of the `CAN_TDH1R_DATA5` field @def CAN_TDH1R_DATA5_Pos */
#define CAN_TDH1R_DATA5_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_TDH1R_DATA5` field @def CAN_TDH1R_DATA5_Width */
#define CAN_TDH1R_DATA5_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDH1R_DATA5` field @def CAN_TDH1R_DATA5_Msk */
#define CAN_TDH1R_DATA5_Msk			REG_FIELD_MASK(CAN_TDH1R_DATA5_Pos, CAN_TDH1R_DATA5_Width)
/** @brief Data byte 5 @def CAN_TDH1R_DATA5 */
#define CAN_TDH1R_DATA5				CAN_TDH1R_DATA5_Msk
/** @brief Bit position of the `CAN_TDH1R_DATA6` field @def CAN_TDH1R_DATA6_Pos */
#define CAN_TDH1R_DATA6_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_TDH1R_DATA6` field @def CAN_TDH1R_DATA6_Width */
#define CAN_TDH1R_DATA6_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDH1R_DATA6` field @def CAN_TDH1R_DATA6_Msk */
#define CAN_TDH1R_DATA6_Msk			REG_FIELD_MASK(CAN_TDH1R_DATA6_Pos, CAN_TDH1R_DATA6_Width)
/** @brief Data byte 6 @def CAN_TDH1R_DATA6 */
#define CAN_TDH1R_DATA6				CAN_TDH1R_DATA6_Msk
/** @brief Bit position of the `CAN_TDH1R_DATA7` field @def CAN_TDH1R_DATA7_Pos */
#define CAN_TDH1R_DATA7_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_TDH1R_DATA7` field @def CAN_TDH1R_DATA7_Width */
#define CAN_TDH1R_DATA7_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDH1R_DATA7` field @def CAN_TDH1R_DATA7_Msk */
#define CAN_TDH1R_DATA7_Msk			REG_FIELD_MASK(CAN_TDH1R_DATA7_Pos, CAN_TDH1R_DATA7_Width)
/** @brief Data byte 7 @def CAN_TDH1R_DATA7 */
#define CAN_TDH1R_DATA7				CAN_TDH1R_DATA7_Msk

// ---------------------------------- CAN_TI2R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_TI2R_TXRQ` field @def CAN_TI2R_TXRQ_Pos */
#define CAN_TI2R_TXRQ_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_TI2R_TXRQ` field @def CAN_TI2R_TXRQ_Msk */
#define CAN_TI2R_TXRQ_Msk		REG_BIT_MASK(CAN_TI2R_TXRQ_Pos)
/** @brief Transmit Mailbox Request @def CAN_TI2R_TXRQ */
#define CAN_TI2R_TXRQ			CAN_TI2R_TXRQ_Msk
/** @brief Bit position of the `CAN_TI2R_RTR` field @def CAN_TI2R_RTR_Pos */
#define CAN_TI2R_RTR_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_TI2R_RTR` field @def CAN_TI2R_RTR_Msk */
#define CAN_TI2R_RTR_Msk		REG_BIT_MASK(CAN_TI2R_RTR_Pos)
/** @brief Remote Transmission Request @def CAN_TI2R_RTR */
#define CAN_TI2R_RTR			CAN_TI2R_RTR_Msk
/** @brief Bit position of the `CAN_TI2R_IDE` field @def CAN_TI2R_IDE_Pos */
#define CAN_TI2R_IDE_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_TI2R_IDE` field @def CAN_TI2R_IDE_Msk */
#define CAN_TI2R_IDE_Msk		REG_BIT_MASK(CAN_TI2R_IDE_Pos)
/** @brief Identifier Extension @def CAN_TI2R_IDE */
#define CAN_TI2R_IDE			CAN_TI2R_IDE_Msk
/** @brief Bit position of the `CAN_TI2R_EXID` field @def CAN_TI2R_EXID_Pos */
#define CAN_TI2R_EXID_Pos		((reg_bit_pos_t) 3U)
/** @brief Width of the `CAN_TI2R_EXID` field @def CAN_TI2R_EXID_Width */
#define CAN_TI2R_EXID_Width		((reg_field_width_t) 18U)
/** @brief Register-positioned mask for the `CAN_TI2R_EXID` field @def CAN_TI2R_EXID_Msk */
#define CAN_TI2R_EXID_Msk		REG_FIELD_MASK(CAN_TI2R_EXID_Pos, CAN_TI2R_EXID_Width)
/** @brief Extended identifier @def CAN_TI2R_EXID */
#define CAN_TI2R_EXID			CAN_TI2R_EXID_Msk
/** @brief Bit position of the `CAN_TI2R_STID` field @def CAN_TI2R_STID_Pos */
#define CAN_TI2R_STID_Pos		((reg_bit_pos_t) 21U)
/** @brief Width of the `CAN_TI2R_STID` field @def CAN_TI2R_STID_Width */
#define CAN_TI2R_STID_Width		((reg_field_width_t) 11U)
/** @brief Register-positioned mask for the `CAN_TI2R_STID` field @def CAN_TI2R_STID_Msk */
#define CAN_TI2R_STID_Msk		REG_FIELD_MASK(CAN_TI2R_STID_Pos, CAN_TI2R_STID_Width)
/** @brief Standard Identifier or Extended Identifier @def CAN_TI2R_STID */
#define CAN_TI2R_STID			CAN_TI2R_STID_Msk

// ---------------------------------- CAN_TDT2R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_TDT2R_DLC` field @def CAN_TDT2R_DLC_Pos */
#define CAN_TDT2R_DLC_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_TDT2R_DLC` field @def CAN_TDT2R_DLC_Width */
#define CAN_TDT2R_DLC_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `CAN_TDT2R_DLC` field @def CAN_TDT2R_DLC_Msk */
#define CAN_TDT2R_DLC_Msk			REG_FIELD_MASK(CAN_TDT2R_DLC_Pos, CAN_TDT2R_DLC_Width)
/** @brief Data Length Code @def CAN_TDT2R_DLC */
#define CAN_TDT2R_DLC				CAN_TDT2R_DLC_Msk
/** @brief Bit position of the `CAN_TDT2R_TGT` field @def CAN_TDT2R_TGT_Pos */
#define CAN_TDT2R_TGT_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDT2R_TGT` field @def CAN_TDT2R_TGT_Msk */
#define CAN_TDT2R_TGT_Msk			REG_BIT_MASK(CAN_TDT2R_TGT_Pos)
/** @brief Transmit Global Time @def CAN_TDT2R_TGT */
#define CAN_TDT2R_TGT				CAN_TDT2R_TGT_Msk
/** @brief Bit position of the `CAN_TDT2R_TIME` field @def CAN_TDT2R_TIME_Pos */
#define CAN_TDT2R_TIME_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_TDT2R_TIME` field @def CAN_TDT2R_TIME_Width */
#define CAN_TDT2R_TIME_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `CAN_TDT2R_TIME` field @def CAN_TDT2R_TIME_Msk */
#define CAN_TDT2R_TIME_Msk			REG_FIELD_MASK(CAN_TDT2R_TIME_Pos, CAN_TDT2R_TIME_Width)
/** @brief Message Time Stamp @def CAN_TDT2R_TIME */
#define CAN_TDT2R_TIME				CAN_TDT2R_TIME_Msk

// ---------------------------------- CAN_TDL2R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_TDL2R_DATA0` field @def CAN_TDL2R_DATA0_Pos */
#define CAN_TDL2R_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_TDL2R_DATA0` field @def CAN_TDL2R_DATA0_Width */
#define CAN_TDL2R_DATA0_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDL2R_DATA0` field @def CAN_TDL2R_DATA0_Msk */
#define CAN_TDL2R_DATA0_Msk			REG_FIELD_MASK(CAN_TDL2R_DATA0_Pos, CAN_TDL2R_DATA0_Width)
/** @brief Data byte 0 @def CAN_TDL2R_DATA0 */
#define CAN_TDL2R_DATA0				CAN_TDL2R_DATA0_Msk
/** @brief Bit position of the `CAN_TDL2R_DATA1` field @def CAN_TDL2R_DATA1_Pos */
#define CAN_TDL2R_DATA1_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_TDL2R_DATA1` field @def CAN_TDL2R_DATA1_Width */
#define CAN_TDL2R_DATA1_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDL2R_DATA1` field @def CAN_TDL2R_DATA1_Msk */
#define CAN_TDL2R_DATA1_Msk			REG_FIELD_MASK(CAN_TDL2R_DATA1_Pos, CAN_TDL2R_DATA1_Width)
/** @brief Data byte 1 @def CAN_TDL2R_DATA1 */
#define CAN_TDL2R_DATA1				CAN_TDL2R_DATA1_Msk
/** @brief Bit position of the `CAN_TDL2R_DATA2` field @def CAN_TDL2R_DATA2_Pos */
#define CAN_TDL2R_DATA2_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_TDL2R_DATA2` field @def CAN_TDL2R_DATA2_Width */
#define CAN_TDL2R_DATA2_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDL2R_DATA2` field @def CAN_TDL2R_DATA2_Msk */
#define CAN_TDL2R_DATA2_Msk			REG_FIELD_MASK(CAN_TDL2R_DATA2_Pos, CAN_TDL2R_DATA2_Width)
/** @brief Data byte 2 @def CAN_TDL2R_DATA2 */
#define CAN_TDL2R_DATA2				CAN_TDL2R_DATA2_Msk
/** @brief Bit position of the `CAN_TDL2R_DATA3` field @def CAN_TDL2R_DATA3_Pos */
#define CAN_TDL2R_DATA3_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_TDL2R_DATA3` field @def CAN_TDL2R_DATA3_Width */
#define CAN_TDL2R_DATA3_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDL2R_DATA3` field @def CAN_TDL2R_DATA3_Msk */
#define CAN_TDL2R_DATA3_Msk			REG_FIELD_MASK(CAN_TDL2R_DATA3_Pos, CAN_TDL2R_DATA3_Width)
/** @brief Data byte 3 @def CAN_TDL2R_DATA3 */
#define CAN_TDL2R_DATA3				CAN_TDL2R_DATA3_Msk

// ---------------------------------- CAN_TDH2R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_TDH2R_DATA4` field @def CAN_TDH2R_DATA4_Pos */
#define CAN_TDH2R_DATA4_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_TDH2R_DATA4` field @def CAN_TDH2R_DATA4_Width */
#define CAN_TDH2R_DATA4_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDH2R_DATA4` field @def CAN_TDH2R_DATA4_Msk */
#define CAN_TDH2R_DATA4_Msk			REG_FIELD_MASK(CAN_TDH2R_DATA4_Pos, CAN_TDH2R_DATA4_Width)
/** @brief Data byte 4 @def CAN_TDH2R_DATA4 */
#define CAN_TDH2R_DATA4				CAN_TDH2R_DATA4_Msk
/** @brief Bit position of the `CAN_TDH2R_DATA5` field @def CAN_TDH2R_DATA5_Pos */
#define CAN_TDH2R_DATA5_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_TDH2R_DATA5` field @def CAN_TDH2R_DATA5_Width */
#define CAN_TDH2R_DATA5_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDH2R_DATA5` field @def CAN_TDH2R_DATA5_Msk */
#define CAN_TDH2R_DATA5_Msk			REG_FIELD_MASK(CAN_TDH2R_DATA5_Pos, CAN_TDH2R_DATA5_Width)
/** @brief Data byte 5 @def CAN_TDH2R_DATA5 */
#define CAN_TDH2R_DATA5				CAN_TDH2R_DATA5_Msk
/** @brief Bit position of the `CAN_TDH2R_DATA6` field @def CAN_TDH2R_DATA6_Pos */
#define CAN_TDH2R_DATA6_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_TDH2R_DATA6` field @def CAN_TDH2R_DATA6_Width */
#define CAN_TDH2R_DATA6_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDH2R_DATA6` field @def CAN_TDH2R_DATA6_Msk */
#define CAN_TDH2R_DATA6_Msk			REG_FIELD_MASK(CAN_TDH2R_DATA6_Pos, CAN_TDH2R_DATA6_Width)
/** @brief Data byte 6 @def CAN_TDH2R_DATA6 */
#define CAN_TDH2R_DATA6				CAN_TDH2R_DATA6_Msk
/** @brief Bit position of the `CAN_TDH2R_DATA7` field @def CAN_TDH2R_DATA7_Pos */
#define CAN_TDH2R_DATA7_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_TDH2R_DATA7` field @def CAN_TDH2R_DATA7_Width */
#define CAN_TDH2R_DATA7_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_TDH2R_DATA7` field @def CAN_TDH2R_DATA7_Msk */
#define CAN_TDH2R_DATA7_Msk			REG_FIELD_MASK(CAN_TDH2R_DATA7_Pos, CAN_TDH2R_DATA7_Width)
/** @brief Data byte 7 @def CAN_TDH2R_DATA7 */
#define CAN_TDH2R_DATA7				CAN_TDH2R_DATA7_Msk

// ---------------------------------- CAN_RI0R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_RI0R_RTR` field @def CAN_RI0R_RTR_Pos */
#define CAN_RI0R_RTR_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_RI0R_RTR` field @def CAN_RI0R_RTR_Msk */
#define CAN_RI0R_RTR_Msk		REG_BIT_MASK(CAN_RI0R_RTR_Pos)
/** @brief Remote Transmission Request @def CAN_RI0R_RTR */
#define CAN_RI0R_RTR			CAN_RI0R_RTR_Msk
/** @brief Bit position of the `CAN_RI0R_IDE` field @def CAN_RI0R_IDE_Pos */
#define CAN_RI0R_IDE_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_RI0R_IDE` field @def CAN_RI0R_IDE_Msk */
#define CAN_RI0R_IDE_Msk		REG_BIT_MASK(CAN_RI0R_IDE_Pos)
/** @brief Identifier Extension @def CAN_RI0R_IDE */
#define CAN_RI0R_IDE			CAN_RI0R_IDE_Msk
/** @brief Bit position of the `CAN_RI0R_EXID` field @def CAN_RI0R_EXID_Pos */
#define CAN_RI0R_EXID_Pos		((reg_bit_pos_t) 3U)
/** @brief Width of the `CAN_RI0R_EXID` field @def CAN_RI0R_EXID_Width */
#define CAN_RI0R_EXID_Width		((reg_field_width_t) 18U)
/** @brief Register-positioned mask for the `CAN_RI0R_EXID` field @def CAN_RI0R_EXID_Msk */
#define CAN_RI0R_EXID_Msk		REG_FIELD_MASK(CAN_RI0R_EXID_Pos, CAN_RI0R_EXID_Width)
/** @brief Extended Identifier @def CAN_RI0R_EXID */
#define CAN_RI0R_EXID			CAN_RI0R_EXID_Msk
/** @brief Bit position of the `CAN_RI0R_STID` field @def CAN_RI0R_STID_Pos */
#define CAN_RI0R_STID_Pos		((reg_bit_pos_t) 21U)
/** @brief Width of the `CAN_RI0R_STID` field @def CAN_RI0R_STID_Width */
#define CAN_RI0R_STID_Width		((reg_field_width_t) 11U)
/** @brief Register-positioned mask for the `CAN_RI0R_STID` field @def CAN_RI0R_STID_Msk */
#define CAN_RI0R_STID_Msk		REG_FIELD_MASK(CAN_RI0R_STID_Pos, CAN_RI0R_STID_Width)
/** @brief Standard Identifier or Extended Identifier @def CAN_RI0R_STID */
#define CAN_RI0R_STID			CAN_RI0R_STID_Msk

// ---------------------------------- CAN_RDT0R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_RDT0R_DLC` field @def CAN_RDT0R_DLC_Pos */
#define CAN_RDT0R_DLC_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_RDT0R_DLC` field @def CAN_RDT0R_DLC_Width */
#define CAN_RDT0R_DLC_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `CAN_RDT0R_DLC` field @def CAN_RDT0R_DLC_Msk */
#define CAN_RDT0R_DLC_Msk			REG_FIELD_MASK(CAN_RDT0R_DLC_Pos, CAN_RDT0R_DLC_Width)
/** @brief Data Length Code @def CAN_RDT0R_DLC */
#define CAN_RDT0R_DLC				CAN_RDT0R_DLC_Msk
/** @brief Bit position of the `CAN_RDT0R_FMI` field @def CAN_RDT0R_FMI_Pos */
#define CAN_RDT0R_FMI_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_RDT0R_FMI` field @def CAN_RDT0R_FMI_Width */
#define CAN_RDT0R_FMI_Width			((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDT0R_FMI` field @def CAN_RDT0R_FMI_Msk */
#define CAN_RDT0R_FMI_Msk			REG_FIELD_MASK(CAN_RDT0R_FMI_Pos, CAN_RDT0R_FMI_Width)
/** @brief Filter Match Index @def CAN_RDT0R_FMI */
#define CAN_RDT0R_FMI				CAN_RDT0R_FMI_Msk
/** @brief Bit position of the `CAN_RDT0R_TIME` field @def CAN_RDT0R_TIME_Pos */
#define CAN_RDT0R_TIME_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_RDT0R_TIME` field @def CAN_RDT0R_TIME_Width */
#define CAN_RDT0R_TIME_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `CAN_RDT0R_TIME` field @def CAN_RDT0R_TIME_Msk */
#define CAN_RDT0R_TIME_Msk			REG_FIELD_MASK(CAN_RDT0R_TIME_Pos, CAN_RDT0R_TIME_Width)
/** @brief Message Time Stamp @def CAN_RDT0R_TIME */
#define CAN_RDT0R_TIME				CAN_RDT0R_TIME_Msk

// ---------------------------------- CAN_RDL0R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_RDL0R_DATA0` field @def CAN_RDL0R_DATA0_Pos */
#define CAN_RDL0R_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_RDL0R_DATA0` field @def CAN_RDL0R_DATA0_Width */
#define CAN_RDL0R_DATA0_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDL0R_DATA0` field @def CAN_RDL0R_DATA0_Msk */
#define CAN_RDL0R_DATA0_Msk			REG_FIELD_MASK(CAN_RDL0R_DATA0_Pos, CAN_RDL0R_DATA0_Width)
/** @brief Data byte 0 @def CAN_RDL0R_DATA0 */
#define CAN_RDL0R_DATA0				CAN_RDL0R_DATA0_Msk
/** @brief Bit position of the `CAN_RDL0R_DATA1` field @def CAN_RDL0R_DATA1_Pos */
#define CAN_RDL0R_DATA1_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_RDL0R_DATA1` field @def CAN_RDL0R_DATA1_Width */
#define CAN_RDL0R_DATA1_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDL0R_DATA1` field @def CAN_RDL0R_DATA1_Msk */
#define CAN_RDL0R_DATA1_Msk			REG_FIELD_MASK(CAN_RDL0R_DATA1_Pos, CAN_RDL0R_DATA1_Width)
/** @brief Data byte 1 @def CAN_RDL0R_DATA1 */
#define CAN_RDL0R_DATA1				CAN_RDL0R_DATA1_Msk
/** @brief Bit position of the `CAN_RDL0R_DATA2` field @def CAN_RDL0R_DATA2_Pos */
#define CAN_RDL0R_DATA2_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_RDL0R_DATA2` field @def CAN_RDL0R_DATA2_Width */
#define CAN_RDL0R_DATA2_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDL0R_DATA2` field @def CAN_RDL0R_DATA2_Msk */
#define CAN_RDL0R_DATA2_Msk			REG_FIELD_MASK(CAN_RDL0R_DATA2_Pos, CAN_RDL0R_DATA2_Width)
/** @brief Data byte 2 @def CAN_RDL0R_DATA2 */
#define CAN_RDL0R_DATA2				CAN_RDL0R_DATA2_Msk
/** @brief Bit position of the `CAN_RDL0R_DATA3` field @def CAN_RDL0R_DATA3_Pos */
#define CAN_RDL0R_DATA3_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_RDL0R_DATA3` field @def CAN_RDL0R_DATA3_Width */
#define CAN_RDL0R_DATA3_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDL0R_DATA3` field @def CAN_RDL0R_DATA3_Msk */
#define CAN_RDL0R_DATA3_Msk			REG_FIELD_MASK(CAN_RDL0R_DATA3_Pos, CAN_RDL0R_DATA3_Width)
/** @brief Data byte 3 @def CAN_RDL0R_DATA3 */
#define CAN_RDL0R_DATA3				CAN_RDL0R_DATA3_Msk

// ---------------------------------- CAN_RDH0R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_RDH0R_DATA4` field @def CAN_RDH0R_DATA4_Pos */
#define CAN_RDH0R_DATA4_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_RDH0R_DATA4` field @def CAN_RDH0R_DATA4_Width */
#define CAN_RDH0R_DATA4_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDH0R_DATA4` field @def CAN_RDH0R_DATA4_Msk */
#define CAN_RDH0R_DATA4_Msk			REG_FIELD_MASK(CAN_RDH0R_DATA4_Pos, CAN_RDH0R_DATA4_Width)
/** @brief Data byte 4 @def CAN_RDH0R_DATA4 */
#define CAN_RDH0R_DATA4				CAN_RDH0R_DATA4_Msk
/** @brief Bit position of the `CAN_RDH0R_DATA5` field @def CAN_RDH0R_DATA5_Pos */
#define CAN_RDH0R_DATA5_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_RDH0R_DATA5` field @def CAN_RDH0R_DATA5_Width */
#define CAN_RDH0R_DATA5_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDH0R_DATA5` field @def CAN_RDH0R_DATA5_Msk */
#define CAN_RDH0R_DATA5_Msk			REG_FIELD_MASK(CAN_RDH0R_DATA5_Pos, CAN_RDH0R_DATA5_Width)
/** @brief Data byte 5 @def CAN_RDH0R_DATA5 */
#define CAN_RDH0R_DATA5				CAN_RDH0R_DATA5_Msk
/** @brief Bit position of the `CAN_RDH0R_DATA6` field @def CAN_RDH0R_DATA6_Pos */
#define CAN_RDH0R_DATA6_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_RDH0R_DATA6` field @def CAN_RDH0R_DATA6_Width */
#define CAN_RDH0R_DATA6_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDH0R_DATA6` field @def CAN_RDH0R_DATA6_Msk */
#define CAN_RDH0R_DATA6_Msk			REG_FIELD_MASK(CAN_RDH0R_DATA6_Pos, CAN_RDH0R_DATA6_Width)
/** @brief Data byte 6 @def CAN_RDH0R_DATA6 */
#define CAN_RDH0R_DATA6				CAN_RDH0R_DATA6_Msk
/** @brief Bit position of the `CAN_RDH0R_DATA7` field @def CAN_RDH0R_DATA7_Pos */
#define CAN_RDH0R_DATA7_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_RDH0R_DATA7` field @def CAN_RDH0R_DATA7_Width */
#define CAN_RDH0R_DATA7_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDH0R_DATA7` field @def CAN_RDH0R_DATA7_Msk */
#define CAN_RDH0R_DATA7_Msk			REG_FIELD_MASK(CAN_RDH0R_DATA7_Pos, CAN_RDH0R_DATA7_Width)
/** @brief Data byte 7 @def CAN_RDH0R_DATA7 */
#define CAN_RDH0R_DATA7				CAN_RDH0R_DATA7_Msk

// ---------------------------------- CAN_RI1R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_RI1R_RTR` field @def CAN_RI1R_RTR_Pos */
#define CAN_RI1R_RTR_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_RI1R_RTR` field @def CAN_RI1R_RTR_Msk */
#define CAN_RI1R_RTR_Msk		REG_BIT_MASK(CAN_RI1R_RTR_Pos)
/** @brief Remote Transmission Request @def CAN_RI1R_RTR */
#define CAN_RI1R_RTR			CAN_RI1R_RTR_Msk
/** @brief Bit position of the `CAN_RI1R_IDE` field @def CAN_RI1R_IDE_Pos */
#define CAN_RI1R_IDE_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_RI1R_IDE` field @def CAN_RI1R_IDE_Msk */
#define CAN_RI1R_IDE_Msk		REG_BIT_MASK(CAN_RI1R_IDE_Pos)
/** @brief Identifier Extension @def CAN_RI1R_IDE */
#define CAN_RI1R_IDE			CAN_RI1R_IDE_Msk
/** @brief Bit position of the `CAN_RI1R_EXID` field @def CAN_RI1R_EXID_Pos */
#define CAN_RI1R_EXID_Pos		((reg_bit_pos_t) 3U)
/** @brief Width of the `CAN_RI1R_EXID` field @def CAN_RI1R_EXID_Width */
#define CAN_RI1R_EXID_Width		((reg_field_width_t) 18U)
/** @brief Register-positioned mask for the `CAN_RI1R_EXID` field @def CAN_RI1R_EXID_Msk */
#define CAN_RI1R_EXID_Msk		REG_FIELD_MASK(CAN_RI1R_EXID_Pos, CAN_RI1R_EXID_Width)
/** @brief Extended identifier @def CAN_RI1R_EXID */
#define CAN_RI1R_EXID			CAN_RI1R_EXID_Msk
/** @brief Bit position of the `CAN_RI1R_STID` field @def CAN_RI1R_STID_Pos */
#define CAN_RI1R_STID_Pos		((reg_bit_pos_t) 21U)
/** @brief Width of the `CAN_RI1R_STID` field @def CAN_RI1R_STID_Width */
#define CAN_RI1R_STID_Width		((reg_field_width_t) 11U)
/** @brief Register-positioned mask for the `CAN_RI1R_STID` field @def CAN_RI1R_STID_Msk */
#define CAN_RI1R_STID_Msk		REG_FIELD_MASK(CAN_RI1R_STID_Pos, CAN_RI1R_STID_Width)
/** @brief Standard Identifier or Extended Identifier @def CAN_RI1R_STID */
#define CAN_RI1R_STID			CAN_RI1R_STID_Msk

// ---------------------------------- CAN_RDT1R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_RDT1R_DLC` field @def CAN_RDT1R_DLC_Pos */
#define CAN_RDT1R_DLC_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_RDT1R_DLC` field @def CAN_RDT1R_DLC_Width */
#define CAN_RDT1R_DLC_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `CAN_RDT1R_DLC` field @def CAN_RDT1R_DLC_Msk */
#define CAN_RDT1R_DLC_Msk			REG_FIELD_MASK(CAN_RDT1R_DLC_Pos, CAN_RDT1R_DLC_Width)
/** @brief Data Length Code @def CAN_RDT1R_DLC */
#define CAN_RDT1R_DLC				CAN_RDT1R_DLC_Msk
/** @brief Bit position of the `CAN_RDT1R_FMI` field @def CAN_RDT1R_FMI_Pos */
#define CAN_RDT1R_FMI_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_RDT1R_FMI` field @def CAN_RDT1R_FMI_Width */
#define CAN_RDT1R_FMI_Width			((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDT1R_FMI` field @def CAN_RDT1R_FMI_Msk */
#define CAN_RDT1R_FMI_Msk			REG_FIELD_MASK(CAN_RDT1R_FMI_Pos, CAN_RDT1R_FMI_Width)
/** @brief Filter Match Index @def CAN_RDT1R_FMI */
#define CAN_RDT1R_FMI				CAN_RDT1R_FMI_Msk
/** @brief Bit position of the `CAN_RDT1R_TIME` field @def CAN_RDT1R_TIME_Pos */
#define CAN_RDT1R_TIME_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_RDT1R_TIME` field @def CAN_RDT1R_TIME_Width */
#define CAN_RDT1R_TIME_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `CAN_RDT1R_TIME` field @def CAN_RDT1R_TIME_Msk */
#define CAN_RDT1R_TIME_Msk			REG_FIELD_MASK(CAN_RDT1R_TIME_Pos, CAN_RDT1R_TIME_Width)
/** @brief Message Time Stamp @def CAN_RDT1R_TIME */
#define CAN_RDT1R_TIME				CAN_RDT1R_TIME_Msk

// ---------------------------------- CAN_RDL1R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_RDL1R_DATA0` field @def CAN_RDL1R_DATA0_Pos */
#define CAN_RDL1R_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_RDL1R_DATA0` field @def CAN_RDL1R_DATA0_Width */
#define CAN_RDL1R_DATA0_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDL1R_DATA0` field @def CAN_RDL1R_DATA0_Msk */
#define CAN_RDL1R_DATA0_Msk			REG_FIELD_MASK(CAN_RDL1R_DATA0_Pos, CAN_RDL1R_DATA0_Width)
/** @brief Data byte 0 @def CAN_RDL1R_DATA0 */
#define CAN_RDL1R_DATA0				CAN_RDL1R_DATA0_Msk
/** @brief Bit position of the `CAN_RDL1R_DATA1` field @def CAN_RDL1R_DATA1_Pos */
#define CAN_RDL1R_DATA1_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_RDL1R_DATA1` field @def CAN_RDL1R_DATA1_Width */
#define CAN_RDL1R_DATA1_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDL1R_DATA1` field @def CAN_RDL1R_DATA1_Msk */
#define CAN_RDL1R_DATA1_Msk			REG_FIELD_MASK(CAN_RDL1R_DATA1_Pos, CAN_RDL1R_DATA1_Width)
/** @brief Data byte 1 @def CAN_RDL1R_DATA1 */
#define CAN_RDL1R_DATA1				CAN_RDL1R_DATA1_Msk
/** @brief Bit position of the `CAN_RDL1R_DATA2` field @def CAN_RDL1R_DATA2_Pos */
#define CAN_RDL1R_DATA2_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_RDL1R_DATA2` field @def CAN_RDL1R_DATA2_Width */
#define CAN_RDL1R_DATA2_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDL1R_DATA2` field @def CAN_RDL1R_DATA2_Msk */
#define CAN_RDL1R_DATA2_Msk			REG_FIELD_MASK(CAN_RDL1R_DATA2_Pos, CAN_RDL1R_DATA2_Width)
/** @brief Data byte 2 @def CAN_RDL1R_DATA2 */
#define CAN_RDL1R_DATA2				CAN_RDL1R_DATA2_Msk
/** @brief Bit position of the `CAN_RDL1R_DATA3` field @def CAN_RDL1R_DATA3_Pos */
#define CAN_RDL1R_DATA3_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_RDL1R_DATA3` field @def CAN_RDL1R_DATA3_Width */
#define CAN_RDL1R_DATA3_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDL1R_DATA3` field @def CAN_RDL1R_DATA3_Msk */
#define CAN_RDL1R_DATA3_Msk			REG_FIELD_MASK(CAN_RDL1R_DATA3_Pos, CAN_RDL1R_DATA3_Width)
/** @brief Data byte 3 @def CAN_RDL1R_DATA3 */
#define CAN_RDL1R_DATA3				CAN_RDL1R_DATA3_Msk

// ---------------------------------- CAN_RDH1R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_RDH1R_DATA4` field @def CAN_RDH1R_DATA4_Pos */
#define CAN_RDH1R_DATA4_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_RDH1R_DATA4` field @def CAN_RDH1R_DATA4_Width */
#define CAN_RDH1R_DATA4_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDH1R_DATA4` field @def CAN_RDH1R_DATA4_Msk */
#define CAN_RDH1R_DATA4_Msk			REG_FIELD_MASK(CAN_RDH1R_DATA4_Pos, CAN_RDH1R_DATA4_Width)
/** @brief Data byte 4 @def CAN_RDH1R_DATA4 */
#define CAN_RDH1R_DATA4				CAN_RDH1R_DATA4_Msk
/** @brief Bit position of the `CAN_RDH1R_DATA5` field @def CAN_RDH1R_DATA5_Pos */
#define CAN_RDH1R_DATA5_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_RDH1R_DATA5` field @def CAN_RDH1R_DATA5_Width */
#define CAN_RDH1R_DATA5_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDH1R_DATA5` field @def CAN_RDH1R_DATA5_Msk */
#define CAN_RDH1R_DATA5_Msk			REG_FIELD_MASK(CAN_RDH1R_DATA5_Pos, CAN_RDH1R_DATA5_Width)
/** @brief Data byte 5 @def CAN_RDH1R_DATA5 */
#define CAN_RDH1R_DATA5				CAN_RDH1R_DATA5_Msk
/** @brief Bit position of the `CAN_RDH1R_DATA6` field @def CAN_RDH1R_DATA6_Pos */
#define CAN_RDH1R_DATA6_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `CAN_RDH1R_DATA6` field @def CAN_RDH1R_DATA6_Width */
#define CAN_RDH1R_DATA6_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDH1R_DATA6` field @def CAN_RDH1R_DATA6_Msk */
#define CAN_RDH1R_DATA6_Msk			REG_FIELD_MASK(CAN_RDH1R_DATA6_Pos, CAN_RDH1R_DATA6_Width)
/** @brief Data byte 6 @def CAN_RDH1R_DATA6 */
#define CAN_RDH1R_DATA6				CAN_RDH1R_DATA6_Msk
/** @brief Bit position of the `CAN_RDH1R_DATA7` field @def CAN_RDH1R_DATA7_Pos */
#define CAN_RDH1R_DATA7_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `CAN_RDH1R_DATA7` field @def CAN_RDH1R_DATA7_Width */
#define CAN_RDH1R_DATA7_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `CAN_RDH1R_DATA7` field @def CAN_RDH1R_DATA7_Msk */
#define CAN_RDH1R_DATA7_Msk			REG_FIELD_MASK(CAN_RDH1R_DATA7_Pos, CAN_RDH1R_DATA7_Width)
/** @brief Data byte 7 @def CAN_RDH1R_DATA7 */
#define CAN_RDH1R_DATA7				CAN_RDH1R_DATA7_Msk

// ----------------------------------- CAN Filter Register Defines ------------------------------------ //
// ----------------------------------- CAN_FMR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_FMR_FINIT` field @def CAN_FMR_FINIT_Pos */
#define CAN_FMR_FINIT_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_FMR_FINIT` field @def CAN_FMR_FINIT_Msk */
#define CAN_FMR_FINIT_Msk			REG_BIT_MASK(CAN_FMR_FINIT_Pos)
/** @brief Filter Init Mode @def CAN_FMR_FINIT */
#define CAN_FMR_FINIT				CAN_FMR_FINIT_Msk
/** @brief Bit position of the `CAN_FMR_CAN2SB` field @def CAN_FMR_CAN2SB_Pos */
#define CAN_FMR_CAN2SB_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `CAN_FMR_CAN2SB` field @def CAN_FMR_CAN2SB_Width */
#define CAN_FMR_CAN2SB_Width		((reg_field_width_t) 6U)
/** @brief Register-positioned mask for the `CAN_FMR_CAN2SB` field @def CAN_FMR_CAN2SB_Msk */
#define CAN_FMR_CAN2SB_Msk			REG_FIELD_MASK(CAN_FMR_CAN2SB_Pos, CAN_FMR_CAN2SB_Width)
/** @brief CAN2 start bank @def CAN_FMR_CAN2SB */
#define CAN_FMR_CAN2SB				CAN_FMR_CAN2SB_Msk

// ---------------------------------- CAN_FM1R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_FM1R_FBM` field @def CAN_FM1R_FBM_Pos */
#define CAN_FM1R_FBM_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_FM1R_FBM` field @def CAN_FM1R_FBM_Width */
#define CAN_FM1R_FBM_Width		((reg_field_width_t) 14U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM` field @def CAN_FM1R_FBM_Msk */
#define CAN_FM1R_FBM_Msk		REG_FIELD_MASK(CAN_FM1R_FBM_Pos, CAN_FM1R_FBM_Width)
/** @brief Filter Mode @def CAN_FM1R_FBM */
#define CAN_FM1R_FBM			CAN_FM1R_FBM_Msk
/** @brief Bit position of the `CAN_FM1R_FBM0` field @def CAN_FM1R_FBM0_Pos */
#define CAN_FM1R_FBM0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM0` field @def CAN_FM1R_FBM0_Msk */
#define CAN_FM1R_FBM0_Msk		REG_BIT_MASK(CAN_FM1R_FBM0_Pos)
/** @brief Filter Init Mode for filter 0 @def CAN_FM1R_FBM0 */
#define CAN_FM1R_FBM0			CAN_FM1R_FBM0_Msk
/** @brief Bit position of the `CAN_FM1R_FBM1` field @def CAN_FM1R_FBM1_Pos */
#define CAN_FM1R_FBM1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM1` field @def CAN_FM1R_FBM1_Msk */
#define CAN_FM1R_FBM1_Msk		REG_BIT_MASK(CAN_FM1R_FBM1_Pos)
/** @brief Filter Init Mode for filter 1 @def CAN_FM1R_FBM1 */
#define CAN_FM1R_FBM1			CAN_FM1R_FBM1_Msk
/** @brief Bit position of the `CAN_FM1R_FBM2` field @def CAN_FM1R_FBM2_Pos */
#define CAN_FM1R_FBM2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM2` field @def CAN_FM1R_FBM2_Msk */
#define CAN_FM1R_FBM2_Msk		REG_BIT_MASK(CAN_FM1R_FBM2_Pos)
/** @brief Filter Init Mode for filter 2 @def CAN_FM1R_FBM2 */
#define CAN_FM1R_FBM2			CAN_FM1R_FBM2_Msk
/** @brief Bit position of the `CAN_FM1R_FBM3` field @def CAN_FM1R_FBM3_Pos */
#define CAN_FM1R_FBM3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM3` field @def CAN_FM1R_FBM3_Msk */
#define CAN_FM1R_FBM3_Msk		REG_BIT_MASK(CAN_FM1R_FBM3_Pos)
/** @brief Filter Init Mode for filter 3 @def CAN_FM1R_FBM3 */
#define CAN_FM1R_FBM3			CAN_FM1R_FBM3_Msk
/** @brief Bit position of the `CAN_FM1R_FBM4` field @def CAN_FM1R_FBM4_Pos */
#define CAN_FM1R_FBM4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM4` field @def CAN_FM1R_FBM4_Msk */
#define CAN_FM1R_FBM4_Msk		REG_BIT_MASK(CAN_FM1R_FBM4_Pos)
/** @brief Filter Init Mode for filter 4 @def CAN_FM1R_FBM4 */
#define CAN_FM1R_FBM4			CAN_FM1R_FBM4_Msk
/** @brief Bit position of the `CAN_FM1R_FBM5` field @def CAN_FM1R_FBM5_Pos */
#define CAN_FM1R_FBM5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM5` field @def CAN_FM1R_FBM5_Msk */
#define CAN_FM1R_FBM5_Msk		REG_BIT_MASK(CAN_FM1R_FBM5_Pos)
/** @brief Filter Init Mode for filter 5 @def CAN_FM1R_FBM5 */
#define CAN_FM1R_FBM5			CAN_FM1R_FBM5_Msk
/** @brief Bit position of the `CAN_FM1R_FBM6` field @def CAN_FM1R_FBM6_Pos */
#define CAN_FM1R_FBM6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM6` field @def CAN_FM1R_FBM6_Msk */
#define CAN_FM1R_FBM6_Msk		REG_BIT_MASK(CAN_FM1R_FBM6_Pos)
/** @brief Filter Init Mode for filter 6 @def CAN_FM1R_FBM6 */
#define CAN_FM1R_FBM6			CAN_FM1R_FBM6_Msk
/** @brief Bit position of the `CAN_FM1R_FBM7` field @def CAN_FM1R_FBM7_Pos */
#define CAN_FM1R_FBM7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM7` field @def CAN_FM1R_FBM7_Msk */
#define CAN_FM1R_FBM7_Msk		REG_BIT_MASK(CAN_FM1R_FBM7_Pos)
/** @brief Filter Init Mode for filter 7 @def CAN_FM1R_FBM7 */
#define CAN_FM1R_FBM7			CAN_FM1R_FBM7_Msk
/** @brief Bit position of the `CAN_FM1R_FBM8` field @def CAN_FM1R_FBM8_Pos */
#define CAN_FM1R_FBM8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM8` field @def CAN_FM1R_FBM8_Msk */
#define CAN_FM1R_FBM8_Msk		REG_BIT_MASK(CAN_FM1R_FBM8_Pos)
/** @brief Filter Init Mode for filter 8 @def CAN_FM1R_FBM8 */
#define CAN_FM1R_FBM8			CAN_FM1R_FBM8_Msk
/** @brief Bit position of the `CAN_FM1R_FBM9` field @def CAN_FM1R_FBM9_Pos */
#define CAN_FM1R_FBM9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM9` field @def CAN_FM1R_FBM9_Msk */
#define CAN_FM1R_FBM9_Msk		REG_BIT_MASK(CAN_FM1R_FBM9_Pos)
/** @brief Filter Init Mode for filter 9 @def CAN_FM1R_FBM9 */
#define CAN_FM1R_FBM9			CAN_FM1R_FBM9_Msk
/** @brief Bit position of the `CAN_FM1R_FBM10` field @def CAN_FM1R_FBM10_Pos */
#define CAN_FM1R_FBM10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM10` field @def CAN_FM1R_FBM10_Msk */
#define CAN_FM1R_FBM10_Msk		REG_BIT_MASK(CAN_FM1R_FBM10_Pos)
/** @brief Filter Init Mode for filter 10 @def CAN_FM1R_FBM10 */
#define CAN_FM1R_FBM10			CAN_FM1R_FBM10_Msk
/** @brief Bit position of the `CAN_FM1R_FBM11` field @def CAN_FM1R_FBM11_Pos */
#define CAN_FM1R_FBM11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM11` field @def CAN_FM1R_FBM11_Msk */
#define CAN_FM1R_FBM11_Msk		REG_BIT_MASK(CAN_FM1R_FBM11_Pos)
/** @brief Filter Init Mode for filter 11 @def CAN_FM1R_FBM11 */
#define CAN_FM1R_FBM11			CAN_FM1R_FBM11_Msk
/** @brief Bit position of the `CAN_FM1R_FBM12` field @def CAN_FM1R_FBM12_Pos */
#define CAN_FM1R_FBM12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM12` field @def CAN_FM1R_FBM12_Msk */
#define CAN_FM1R_FBM12_Msk		REG_BIT_MASK(CAN_FM1R_FBM12_Pos)
/** @brief Filter Init Mode for filter 12 @def CAN_FM1R_FBM12 */
#define CAN_FM1R_FBM12			CAN_FM1R_FBM12_Msk
/** @brief Bit position of the `CAN_FM1R_FBM13` field @def CAN_FM1R_FBM13_Pos */
#define CAN_FM1R_FBM13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_FM1R_FBM13` field @def CAN_FM1R_FBM13_Msk */
#define CAN_FM1R_FBM13_Msk		REG_BIT_MASK(CAN_FM1R_FBM13_Pos)
/** @brief Filter Init Mode for filter 13 @def CAN_FM1R_FBM13 */
#define CAN_FM1R_FBM13			CAN_FM1R_FBM13_Msk

// ---------------------------------- CAN_FS1R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_FS1R_FSC` field @def CAN_FS1R_FSC_Pos */
#define CAN_FS1R_FSC_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_FS1R_FSC` field @def CAN_FS1R_FSC_Width */
#define CAN_FS1R_FSC_Width		((reg_field_width_t) 14U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC` field @def CAN_FS1R_FSC_Msk */
#define CAN_FS1R_FSC_Msk		REG_FIELD_MASK(CAN_FS1R_FSC_Pos, CAN_FS1R_FSC_Width)
/** @brief Filter Scale Configuration @def CAN_FS1R_FSC */
#define CAN_FS1R_FSC			CAN_FS1R_FSC_Msk
/** @brief Bit position of the `CAN_FS1R_FSC0` field @def CAN_FS1R_FSC0_Pos */
#define CAN_FS1R_FSC0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC0` field @def CAN_FS1R_FSC0_Msk */
#define CAN_FS1R_FSC0_Msk		REG_BIT_MASK(CAN_FS1R_FSC0_Pos)
/** @brief Filter Scale Configuration for filter 0 @def CAN_FS1R_FSC0 */
#define CAN_FS1R_FSC0			CAN_FS1R_FSC0_Msk
/** @brief Bit position of the `CAN_FS1R_FSC1` field @def CAN_FS1R_FSC1_Pos */
#define CAN_FS1R_FSC1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC1` field @def CAN_FS1R_FSC1_Msk */
#define CAN_FS1R_FSC1_Msk		REG_BIT_MASK(CAN_FS1R_FSC1_Pos)
/** @brief Filter Scale Configuration for filter 1 @def CAN_FS1R_FSC1 */
#define CAN_FS1R_FSC1			CAN_FS1R_FSC1_Msk
/** @brief Bit position of the `CAN_FS1R_FSC2` field @def CAN_FS1R_FSC2_Pos */
#define CAN_FS1R_FSC2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC2` field @def CAN_FS1R_FSC2_Msk */
#define CAN_FS1R_FSC2_Msk		REG_BIT_MASK(CAN_FS1R_FSC2_Pos)
/** @brief Filter Scale Configuration for filter 2 @def CAN_FS1R_FSC2 */
#define CAN_FS1R_FSC2			CAN_FS1R_FSC2_Msk
/** @brief Bit position of the `CAN_FS1R_FSC3` field @def CAN_FS1R_FSC3_Pos */
#define CAN_FS1R_FSC3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC3` field @def CAN_FS1R_FSC3_Msk */
#define CAN_FS1R_FSC3_Msk		REG_BIT_MASK(CAN_FS1R_FSC3_Pos)
/** @brief Filter Scale Configuration for filter 3 @def CAN_FS1R_FSC3 */
#define CAN_FS1R_FSC3			CAN_FS1R_FSC3_Msk
/** @brief Bit position of the `CAN_FS1R_FSC4` field @def CAN_FS1R_FSC4_Pos */
#define CAN_FS1R_FSC4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC4` field @def CAN_FS1R_FSC4_Msk */
#define CAN_FS1R_FSC4_Msk		REG_BIT_MASK(CAN_FS1R_FSC4_Pos)
/** @brief Filter Scale Configuration for filter 4 @def CAN_FS1R_FSC4 */
#define CAN_FS1R_FSC4			CAN_FS1R_FSC4_Msk
/** @brief Bit position of the `CAN_FS1R_FSC5` field @def CAN_FS1R_FSC5_Pos */
#define CAN_FS1R_FSC5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC5` field @def CAN_FS1R_FSC5_Msk */
#define CAN_FS1R_FSC5_Msk		REG_BIT_MASK(CAN_FS1R_FSC5_Pos)
/** @brief Filter Scale Configuration for filter 5 @def CAN_FS1R_FSC5 */
#define CAN_FS1R_FSC5			CAN_FS1R_FSC5_Msk
/** @brief Bit position of the `CAN_FS1R_FSC6` field @def CAN_FS1R_FSC6_Pos */
#define CAN_FS1R_FSC6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC6` field @def CAN_FS1R_FSC6_Msk */
#define CAN_FS1R_FSC6_Msk		REG_BIT_MASK(CAN_FS1R_FSC6_Pos)
/** @brief Filter Scale Configuration for filter 6 @def CAN_FS1R_FSC6 */
#define CAN_FS1R_FSC6			CAN_FS1R_FSC6_Msk
/** @brief Bit position of the `CAN_FS1R_FSC7` field @def CAN_FS1R_FSC7_Pos */
#define CAN_FS1R_FSC7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC7` field @def CAN_FS1R_FSC7_Msk */
#define CAN_FS1R_FSC7_Msk		REG_BIT_MASK(CAN_FS1R_FSC7_Pos)
/** @brief Filter Scale Configuration for filter 7 @def CAN_FS1R_FSC7 */
#define CAN_FS1R_FSC7			CAN_FS1R_FSC7_Msk
/** @brief Bit position of the `CAN_FS1R_FSC8` field @def CAN_FS1R_FSC8_Pos */
#define CAN_FS1R_FSC8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC8` field @def CAN_FS1R_FSC8_Msk */
#define CAN_FS1R_FSC8_Msk		REG_BIT_MASK(CAN_FS1R_FSC8_Pos)
/** @brief Filter Scale Configuration for filter 8 @def CAN_FS1R_FSC8 */
#define CAN_FS1R_FSC8			CAN_FS1R_FSC8_Msk
/** @brief Bit position of the `CAN_FS1R_FSC9` field @def CAN_FS1R_FSC9_Pos */
#define CAN_FS1R_FSC9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC9` field @def CAN_FS1R_FSC9_Msk */
#define CAN_FS1R_FSC9_Msk		REG_BIT_MASK(CAN_FS1R_FSC9_Pos)
/** @brief Filter Scale Configuration for filter 9 @def CAN_FS1R_FSC9 */
#define CAN_FS1R_FSC9			CAN_FS1R_FSC9_Msk
/** @brief Bit position of the `CAN_FS1R_FSC10` field @def CAN_FS1R_FSC10_Pos */
#define CAN_FS1R_FSC10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC10` field @def CAN_FS1R_FSC10_Msk */
#define CAN_FS1R_FSC10_Msk		REG_BIT_MASK(CAN_FS1R_FSC10_Pos)
/** @brief Filter Scale Configuration for filter 10 @def CAN_FS1R_FSC10 */
#define CAN_FS1R_FSC10			CAN_FS1R_FSC10_Msk
/** @brief Bit position of the `CAN_FS1R_FSC11` field @def CAN_FS1R_FSC11_Pos */
#define CAN_FS1R_FSC11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC11` field @def CAN_FS1R_FSC11_Msk */
#define CAN_FS1R_FSC11_Msk		REG_BIT_MASK(CAN_FS1R_FSC11_Pos)
/** @brief Filter Scale Configuration for filter 11 @def CAN_FS1R_FSC11 */
#define CAN_FS1R_FSC11			CAN_FS1R_FSC11_Msk
/** @brief Bit position of the `CAN_FS1R_FSC12` field @def CAN_FS1R_FSC12_Pos */
#define CAN_FS1R_FSC12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC12` field @def CAN_FS1R_FSC12_Msk */
#define CAN_FS1R_FSC12_Msk		REG_BIT_MASK(CAN_FS1R_FSC12_Pos)
/** @brief Filter Scale Configuration for filter 12 @def CAN_FS1R_FSC12 */
#define CAN_FS1R_FSC12			CAN_FS1R_FSC12_Msk
/** @brief Bit position of the `CAN_FS1R_FSC13` field @def CAN_FS1R_FSC13_Pos */
#define CAN_FS1R_FSC13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_FS1R_FSC13` field @def CAN_FS1R_FSC13_Msk */
#define CAN_FS1R_FSC13_Msk		REG_BIT_MASK(CAN_FS1R_FSC13_Pos)
/** @brief Filter Scale Configuration for filter 13 @def CAN_FS1R_FSC13 */
#define CAN_FS1R_FSC13			CAN_FS1R_FSC13_Msk

// ---------------------------------- CAN_FFA1R Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_FFA1R_FFA` field @def CAN_FFA1R_FFA_Pos */
#define CAN_FFA1R_FFA_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_FFA1R_FFA` field @def CAN_FFA1R_FFA_Width */
#define CAN_FFA1R_FFA_Width		((reg_field_width_t) 14U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA` field @def CAN_FFA1R_FFA_Msk */
#define CAN_FFA1R_FFA_Msk		REG_FIELD_MASK(CAN_FFA1R_FFA_Pos, CAN_FFA1R_FFA_Width)
/** @brief Filter FIFO Assignment @def CAN_FFA1R_FFA */
#define CAN_FFA1R_FFA			CAN_FFA1R_FFA_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA0` field @def CAN_FFA1R_FFA0_Pos */
#define CAN_FFA1R_FFA0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA0` field @def CAN_FFA1R_FFA0_Msk */
#define CAN_FFA1R_FFA0_Msk		REG_BIT_MASK(CAN_FFA1R_FFA0_Pos)
/** @brief Filter FIFO Assignment for filter 0 @def CAN_FFA1R_FFA0 */
#define CAN_FFA1R_FFA0			CAN_FFA1R_FFA0_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA1` field @def CAN_FFA1R_FFA1_Pos */
#define CAN_FFA1R_FFA1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA1` field @def CAN_FFA1R_FFA1_Msk */
#define CAN_FFA1R_FFA1_Msk		REG_BIT_MASK(CAN_FFA1R_FFA1_Pos)
/** @brief Filter FIFO Assignment for filter 1 @def CAN_FFA1R_FFA1 */
#define CAN_FFA1R_FFA1			CAN_FFA1R_FFA1_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA2` field @def CAN_FFA1R_FFA2_Pos */
#define CAN_FFA1R_FFA2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA2` field @def CAN_FFA1R_FFA2_Msk */
#define CAN_FFA1R_FFA2_Msk		REG_BIT_MASK(CAN_FFA1R_FFA2_Pos)
/** @brief Filter FIFO Assignment for filter 2 @def CAN_FFA1R_FFA2 */
#define CAN_FFA1R_FFA2			CAN_FFA1R_FFA2_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA3` field @def CAN_FFA1R_FFA3_Pos */
#define CAN_FFA1R_FFA3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA3` field @def CAN_FFA1R_FFA3_Msk */
#define CAN_FFA1R_FFA3_Msk		REG_BIT_MASK(CAN_FFA1R_FFA3_Pos)
/** @brief Filter FIFO Assignment for filter 3 @def CAN_FFA1R_FFA3 */
#define CAN_FFA1R_FFA3			CAN_FFA1R_FFA3_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA4` field @def CAN_FFA1R_FFA4_Pos */
#define CAN_FFA1R_FFA4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA4` field @def CAN_FFA1R_FFA4_Msk */
#define CAN_FFA1R_FFA4_Msk		REG_BIT_MASK(CAN_FFA1R_FFA4_Pos)
/** @brief Filter FIFO Assignment for filter 4 @def CAN_FFA1R_FFA4 */
#define CAN_FFA1R_FFA4			CAN_FFA1R_FFA4_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA5` field @def CAN_FFA1R_FFA5_Pos */
#define CAN_FFA1R_FFA5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA5` field @def CAN_FFA1R_FFA5_Msk */
#define CAN_FFA1R_FFA5_Msk		REG_BIT_MASK(CAN_FFA1R_FFA5_Pos)
/** @brief Filter FIFO Assignment for filter 5 @def CAN_FFA1R_FFA5 */
#define CAN_FFA1R_FFA5			CAN_FFA1R_FFA5_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA6` field @def CAN_FFA1R_FFA6_Pos */
#define CAN_FFA1R_FFA6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA6` field @def CAN_FFA1R_FFA6_Msk */
#define CAN_FFA1R_FFA6_Msk		REG_BIT_MASK(CAN_FFA1R_FFA6_Pos)
/** @brief Filter FIFO Assignment for filter 6 @def CAN_FFA1R_FFA6 */
#define CAN_FFA1R_FFA6			CAN_FFA1R_FFA6_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA7` field @def CAN_FFA1R_FFA7_Pos */
#define CAN_FFA1R_FFA7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA7` field @def CAN_FFA1R_FFA7_Msk */
#define CAN_FFA1R_FFA7_Msk		REG_BIT_MASK(CAN_FFA1R_FFA7_Pos)
/** @brief Filter FIFO Assignment for filter 7 @def CAN_FFA1R_FFA7 */
#define CAN_FFA1R_FFA7			CAN_FFA1R_FFA7_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA8` field @def CAN_FFA1R_FFA8_Pos */
#define CAN_FFA1R_FFA8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA8` field @def CAN_FFA1R_FFA8_Msk */
#define CAN_FFA1R_FFA8_Msk		REG_BIT_MASK(CAN_FFA1R_FFA8_Pos)
/** @brief Filter FIFO Assignment for filter 8 @def CAN_FFA1R_FFA8 */
#define CAN_FFA1R_FFA8			CAN_FFA1R_FFA8_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA9` field @def CAN_FFA1R_FFA9_Pos */
#define CAN_FFA1R_FFA9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA9` field @def CAN_FFA1R_FFA9_Msk */
#define CAN_FFA1R_FFA9_Msk		REG_BIT_MASK(CAN_FFA1R_FFA9_Pos)
/** @brief Filter FIFO Assignment for filter 9 @def CAN_FFA1R_FFA9 */
#define CAN_FFA1R_FFA9			CAN_FFA1R_FFA9_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA10` field @def CAN_FFA1R_FFA10_Pos */
#define CAN_FFA1R_FFA10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA10` field @def CAN_FFA1R_FFA10_Msk */
#define CAN_FFA1R_FFA10_Msk		REG_BIT_MASK(CAN_FFA1R_FFA10_Pos)
/** @brief Filter FIFO Assignment for filter 10 @def CAN_FFA1R_FFA10 */
#define CAN_FFA1R_FFA10			CAN_FFA1R_FFA10_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA11` field @def CAN_FFA1R_FFA11_Pos */
#define CAN_FFA1R_FFA11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA11` field @def CAN_FFA1R_FFA11_Msk */
#define CAN_FFA1R_FFA11_Msk		REG_BIT_MASK(CAN_FFA1R_FFA11_Pos)
/** @brief Filter FIFO Assignment for filter 11 @def CAN_FFA1R_FFA11 */
#define CAN_FFA1R_FFA11			CAN_FFA1R_FFA11_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA12` field @def CAN_FFA1R_FFA12_Pos */
#define CAN_FFA1R_FFA12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA12` field @def CAN_FFA1R_FFA12_Msk */
#define CAN_FFA1R_FFA12_Msk		REG_BIT_MASK(CAN_FFA1R_FFA12_Pos)
/** @brief Filter FIFO Assignment for filter 12 @def CAN_FFA1R_FFA12 */
#define CAN_FFA1R_FFA12			CAN_FFA1R_FFA12_Msk
/** @brief Bit position of the `CAN_FFA1R_FFA13` field @def CAN_FFA1R_FFA13_Pos */
#define CAN_FFA1R_FFA13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_FFA1R_FFA13` field @def CAN_FFA1R_FFA13_Msk */
#define CAN_FFA1R_FFA13_Msk		REG_BIT_MASK(CAN_FFA1R_FFA13_Pos)
/** @brief Filter FIFO Assignment for filter 13 @def CAN_FFA1R_FFA13 */
#define CAN_FFA1R_FFA13			CAN_FFA1R_FFA13_Msk

// ---------------------------------- CAN_FA1R Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_FA1R_FACT` field @def CAN_FA1R_FACT_Pos */
#define CAN_FA1R_FACT_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `CAN_FA1R_FACT` field @def CAN_FA1R_FACT_Width */
#define CAN_FA1R_FACT_Width		((reg_field_width_t) 14U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT` field @def CAN_FA1R_FACT_Msk */
#define CAN_FA1R_FACT_Msk		REG_FIELD_MASK(CAN_FA1R_FACT_Pos, CAN_FA1R_FACT_Width)
/** @brief Filter Active @def CAN_FA1R_FACT */
#define CAN_FA1R_FACT			CAN_FA1R_FACT_Msk
/** @brief Bit position of the `CAN_FA1R_FACT0` field @def CAN_FA1R_FACT0_Pos */
#define CAN_FA1R_FACT0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT0` field @def CAN_FA1R_FACT0_Msk */
#define CAN_FA1R_FACT0_Msk		REG_BIT_MASK(CAN_FA1R_FACT0_Pos)
/** @brief Filter 0 Active @def CAN_FA1R_FACT0 */
#define CAN_FA1R_FACT0			CAN_FA1R_FACT0_Msk
/** @brief Bit position of the `CAN_FA1R_FACT1` field @def CAN_FA1R_FACT1_Pos */
#define CAN_FA1R_FACT1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT1` field @def CAN_FA1R_FACT1_Msk */
#define CAN_FA1R_FACT1_Msk		REG_BIT_MASK(CAN_FA1R_FACT1_Pos)
/** @brief Filter 1 Active @def CAN_FA1R_FACT1 */
#define CAN_FA1R_FACT1			CAN_FA1R_FACT1_Msk
/** @brief Bit position of the `CAN_FA1R_FACT2` field @def CAN_FA1R_FACT2_Pos */
#define CAN_FA1R_FACT2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT2` field @def CAN_FA1R_FACT2_Msk */
#define CAN_FA1R_FACT2_Msk		REG_BIT_MASK(CAN_FA1R_FACT2_Pos)
/** @brief Filter 2 Active @def CAN_FA1R_FACT2 */
#define CAN_FA1R_FACT2			CAN_FA1R_FACT2_Msk
/** @brief Bit position of the `CAN_FA1R_FACT3` field @def CAN_FA1R_FACT3_Pos */
#define CAN_FA1R_FACT3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT3` field @def CAN_FA1R_FACT3_Msk */
#define CAN_FA1R_FACT3_Msk		REG_BIT_MASK(CAN_FA1R_FACT3_Pos)
/** @brief Filter 3 Active @def CAN_FA1R_FACT3 */
#define CAN_FA1R_FACT3			CAN_FA1R_FACT3_Msk
/** @brief Bit position of the `CAN_FA1R_FACT4` field @def CAN_FA1R_FACT4_Pos */
#define CAN_FA1R_FACT4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT4` field @def CAN_FA1R_FACT4_Msk */
#define CAN_FA1R_FACT4_Msk		REG_BIT_MASK(CAN_FA1R_FACT4_Pos)
/** @brief Filter 4 Active @def CAN_FA1R_FACT4 */
#define CAN_FA1R_FACT4			CAN_FA1R_FACT4_Msk
/** @brief Bit position of the `CAN_FA1R_FACT5` field @def CAN_FA1R_FACT5_Pos */
#define CAN_FA1R_FACT5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT5` field @def CAN_FA1R_FACT5_Msk */
#define CAN_FA1R_FACT5_Msk		REG_BIT_MASK(CAN_FA1R_FACT5_Pos)
/** @brief Filter 5 Active @def CAN_FA1R_FACT5 */
#define CAN_FA1R_FACT5			CAN_FA1R_FACT5_Msk
/** @brief Bit position of the `CAN_FA1R_FACT6` field @def CAN_FA1R_FACT6_Pos */
#define CAN_FA1R_FACT6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT6` field @def CAN_FA1R_FACT6_Msk */
#define CAN_FA1R_FACT6_Msk		REG_BIT_MASK(CAN_FA1R_FACT6_Pos)
/** @brief Filter 6 Active @def CAN_FA1R_FACT6 */
#define CAN_FA1R_FACT6			CAN_FA1R_FACT6_Msk
/** @brief Bit position of the `CAN_FA1R_FACT7` field @def CAN_FA1R_FACT7_Pos */
#define CAN_FA1R_FACT7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT7` field @def CAN_FA1R_FACT7_Msk */
#define CAN_FA1R_FACT7_Msk		REG_BIT_MASK(CAN_FA1R_FACT7_Pos)
/** @brief Filter 7 Active @def CAN_FA1R_FACT7 */
#define CAN_FA1R_FACT7			CAN_FA1R_FACT7_Msk
/** @brief Bit position of the `CAN_FA1R_FACT8` field @def CAN_FA1R_FACT8_Pos */
#define CAN_FA1R_FACT8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT8` field @def CAN_FA1R_FACT8_Msk */
#define CAN_FA1R_FACT8_Msk		REG_BIT_MASK(CAN_FA1R_FACT8_Pos)
/** @brief Filter 8 Active @def CAN_FA1R_FACT8 */
#define CAN_FA1R_FACT8			CAN_FA1R_FACT8_Msk
/** @brief Bit position of the `CAN_FA1R_FACT9` field @def CAN_FA1R_FACT9_Pos */
#define CAN_FA1R_FACT9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT9` field @def CAN_FA1R_FACT9_Msk */
#define CAN_FA1R_FACT9_Msk		REG_BIT_MASK(CAN_FA1R_FACT9_Pos)
/** @brief Filter 9 Active @def CAN_FA1R_FACT9 */
#define CAN_FA1R_FACT9			CAN_FA1R_FACT9_Msk
/** @brief Bit position of the `CAN_FA1R_FACT10` field @def CAN_FA1R_FACT10_Pos */
#define CAN_FA1R_FACT10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT10` field @def CAN_FA1R_FACT10_Msk */
#define CAN_FA1R_FACT10_Msk		REG_BIT_MASK(CAN_FA1R_FACT10_Pos)
/** @brief Filter 10 Active @def CAN_FA1R_FACT10 */
#define CAN_FA1R_FACT10			CAN_FA1R_FACT10_Msk
/** @brief Bit position of the `CAN_FA1R_FACT11` field @def CAN_FA1R_FACT11_Pos */
#define CAN_FA1R_FACT11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT11` field @def CAN_FA1R_FACT11_Msk */
#define CAN_FA1R_FACT11_Msk		REG_BIT_MASK(CAN_FA1R_FACT11_Pos)
/** @brief Filter 11 Active @def CAN_FA1R_FACT11 */
#define CAN_FA1R_FACT11			CAN_FA1R_FACT11_Msk
/** @brief Bit position of the `CAN_FA1R_FACT12` field @def CAN_FA1R_FACT12_Pos */
#define CAN_FA1R_FACT12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT12` field @def CAN_FA1R_FACT12_Msk */
#define CAN_FA1R_FACT12_Msk		REG_BIT_MASK(CAN_FA1R_FACT12_Pos)
/** @brief Filter 12 Active @def CAN_FA1R_FACT12 */
#define CAN_FA1R_FACT12			CAN_FA1R_FACT12_Msk
/** @brief Bit position of the `CAN_FA1R_FACT13` field @def CAN_FA1R_FACT13_Pos */
#define CAN_FA1R_FACT13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_FA1R_FACT13` field @def CAN_FA1R_FACT13_Msk */
#define CAN_FA1R_FACT13_Msk		REG_BIT_MASK(CAN_FA1R_FACT13_Pos)
/** @brief Filter 13 Active @def CAN_FA1R_FACT13 */
#define CAN_FA1R_FACT13			CAN_FA1R_FACT13_Msk

// ---------------------------------- CAN_F0R1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F0R1_FB0` field @def CAN_F0R1_FB0_Pos */
#define CAN_F0R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB0` field @def CAN_F0R1_FB0_Msk */
#define CAN_F0R1_FB0_Msk		REG_BIT_MASK(CAN_F0R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F0R1_FB0 */
#define CAN_F0R1_FB0			CAN_F0R1_FB0_Msk
/** @brief Bit position of the `CAN_F0R1_FB1` field @def CAN_F0R1_FB1_Pos */
#define CAN_F0R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB1` field @def CAN_F0R1_FB1_Msk */
#define CAN_F0R1_FB1_Msk		REG_BIT_MASK(CAN_F0R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F0R1_FB1 */
#define CAN_F0R1_FB1			CAN_F0R1_FB1_Msk
/** @brief Bit position of the `CAN_F0R1_FB2` field @def CAN_F0R1_FB2_Pos */
#define CAN_F0R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB2` field @def CAN_F0R1_FB2_Msk */
#define CAN_F0R1_FB2_Msk		REG_BIT_MASK(CAN_F0R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F0R1_FB2 */
#define CAN_F0R1_FB2			CAN_F0R1_FB2_Msk
/** @brief Bit position of the `CAN_F0R1_FB3` field @def CAN_F0R1_FB3_Pos */
#define CAN_F0R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB3` field @def CAN_F0R1_FB3_Msk */
#define CAN_F0R1_FB3_Msk		REG_BIT_MASK(CAN_F0R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F0R1_FB3 */
#define CAN_F0R1_FB3			CAN_F0R1_FB3_Msk
/** @brief Bit position of the `CAN_F0R1_FB4` field @def CAN_F0R1_FB4_Pos */
#define CAN_F0R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB4` field @def CAN_F0R1_FB4_Msk */
#define CAN_F0R1_FB4_Msk		REG_BIT_MASK(CAN_F0R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F0R1_FB4 */
#define CAN_F0R1_FB4			CAN_F0R1_FB4_Msk
/** @brief Bit position of the `CAN_F0R1_FB5` field @def CAN_F0R1_FB5_Pos */
#define CAN_F0R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB5` field @def CAN_F0R1_FB5_Msk */
#define CAN_F0R1_FB5_Msk		REG_BIT_MASK(CAN_F0R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F0R1_FB5 */
#define CAN_F0R1_FB5			CAN_F0R1_FB5_Msk
/** @brief Bit position of the `CAN_F0R1_FB6` field @def CAN_F0R1_FB6_Pos */
#define CAN_F0R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB6` field @def CAN_F0R1_FB6_Msk */
#define CAN_F0R1_FB6_Msk		REG_BIT_MASK(CAN_F0R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F0R1_FB6 */
#define CAN_F0R1_FB6			CAN_F0R1_FB6_Msk
/** @brief Bit position of the `CAN_F0R1_FB7` field @def CAN_F0R1_FB7_Pos */
#define CAN_F0R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB7` field @def CAN_F0R1_FB7_Msk */
#define CAN_F0R1_FB7_Msk		REG_BIT_MASK(CAN_F0R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F0R1_FB7 */
#define CAN_F0R1_FB7			CAN_F0R1_FB7_Msk
/** @brief Bit position of the `CAN_F0R1_FB8` field @def CAN_F0R1_FB8_Pos */
#define CAN_F0R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB8` field @def CAN_F0R1_FB8_Msk */
#define CAN_F0R1_FB8_Msk		REG_BIT_MASK(CAN_F0R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F0R1_FB8 */
#define CAN_F0R1_FB8			CAN_F0R1_FB8_Msk
/** @brief Bit position of the `CAN_F0R1_FB9` field @def CAN_F0R1_FB9_Pos */
#define CAN_F0R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB9` field @def CAN_F0R1_FB9_Msk */
#define CAN_F0R1_FB9_Msk		REG_BIT_MASK(CAN_F0R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F0R1_FB9 */
#define CAN_F0R1_FB9			CAN_F0R1_FB9_Msk
/** @brief Bit position of the `CAN_F0R1_FB10` field @def CAN_F0R1_FB10_Pos */
#define CAN_F0R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB10` field @def CAN_F0R1_FB10_Msk */
#define CAN_F0R1_FB10_Msk		REG_BIT_MASK(CAN_F0R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F0R1_FB10 */
#define CAN_F0R1_FB10			CAN_F0R1_FB10_Msk
/** @brief Bit position of the `CAN_F0R1_FB11` field @def CAN_F0R1_FB11_Pos */
#define CAN_F0R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB11` field @def CAN_F0R1_FB11_Msk */
#define CAN_F0R1_FB11_Msk		REG_BIT_MASK(CAN_F0R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F0R1_FB11 */
#define CAN_F0R1_FB11			CAN_F0R1_FB11_Msk
/** @brief Bit position of the `CAN_F0R1_FB12` field @def CAN_F0R1_FB12_Pos */
#define CAN_F0R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB12` field @def CAN_F0R1_FB12_Msk */
#define CAN_F0R1_FB12_Msk		REG_BIT_MASK(CAN_F0R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F0R1_FB12 */
#define CAN_F0R1_FB12			CAN_F0R1_FB12_Msk
/** @brief Bit position of the `CAN_F0R1_FB13` field @def CAN_F0R1_FB13_Pos */
#define CAN_F0R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB13` field @def CAN_F0R1_FB13_Msk */
#define CAN_F0R1_FB13_Msk		REG_BIT_MASK(CAN_F0R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F0R1_FB13 */
#define CAN_F0R1_FB13			CAN_F0R1_FB13_Msk
/** @brief Bit position of the `CAN_F0R1_FB14` field @def CAN_F0R1_FB14_Pos */
#define CAN_F0R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB14` field @def CAN_F0R1_FB14_Msk */
#define CAN_F0R1_FB14_Msk		REG_BIT_MASK(CAN_F0R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F0R1_FB14 */
#define CAN_F0R1_FB14			CAN_F0R1_FB14_Msk
/** @brief Bit position of the `CAN_F0R1_FB15` field @def CAN_F0R1_FB15_Pos */
#define CAN_F0R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB15` field @def CAN_F0R1_FB15_Msk */
#define CAN_F0R1_FB15_Msk		REG_BIT_MASK(CAN_F0R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F0R1_FB15 */
#define CAN_F0R1_FB15			CAN_F0R1_FB15_Msk
/** @brief Bit position of the `CAN_F0R1_FB16` field @def CAN_F0R1_FB16_Pos */
#define CAN_F0R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB16` field @def CAN_F0R1_FB16_Msk */
#define CAN_F0R1_FB16_Msk		REG_BIT_MASK(CAN_F0R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F0R1_FB16 */
#define CAN_F0R1_FB16			CAN_F0R1_FB16_Msk
/** @brief Bit position of the `CAN_F0R1_FB17` field @def CAN_F0R1_FB17_Pos */
#define CAN_F0R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB17` field @def CAN_F0R1_FB17_Msk */
#define CAN_F0R1_FB17_Msk		REG_BIT_MASK(CAN_F0R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F0R1_FB17 */
#define CAN_F0R1_FB17			CAN_F0R1_FB17_Msk
/** @brief Bit position of the `CAN_F0R1_FB18` field @def CAN_F0R1_FB18_Pos */
#define CAN_F0R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB18` field @def CAN_F0R1_FB18_Msk */
#define CAN_F0R1_FB18_Msk		REG_BIT_MASK(CAN_F0R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F0R1_FB18 */
#define CAN_F0R1_FB18			CAN_F0R1_FB18_Msk
/** @brief Bit position of the `CAN_F0R1_FB19` field @def CAN_F0R1_FB19_Pos */
#define CAN_F0R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB19` field @def CAN_F0R1_FB19_Msk */
#define CAN_F0R1_FB19_Msk		REG_BIT_MASK(CAN_F0R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F0R1_FB19 */
#define CAN_F0R1_FB19			CAN_F0R1_FB19_Msk
/** @brief Bit position of the `CAN_F0R1_FB20` field @def CAN_F0R1_FB20_Pos */
#define CAN_F0R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB20` field @def CAN_F0R1_FB20_Msk */
#define CAN_F0R1_FB20_Msk		REG_BIT_MASK(CAN_F0R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F0R1_FB20 */
#define CAN_F0R1_FB20			CAN_F0R1_FB20_Msk
/** @brief Bit position of the `CAN_F0R1_FB21` field @def CAN_F0R1_FB21_Pos */
#define CAN_F0R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB21` field @def CAN_F0R1_FB21_Msk */
#define CAN_F0R1_FB21_Msk		REG_BIT_MASK(CAN_F0R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F0R1_FB21 */
#define CAN_F0R1_FB21			CAN_F0R1_FB21_Msk
/** @brief Bit position of the `CAN_F0R1_FB22` field @def CAN_F0R1_FB22_Pos */
#define CAN_F0R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB22` field @def CAN_F0R1_FB22_Msk */
#define CAN_F0R1_FB22_Msk		REG_BIT_MASK(CAN_F0R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F0R1_FB22 */
#define CAN_F0R1_FB22			CAN_F0R1_FB22_Msk
/** @brief Bit position of the `CAN_F0R1_FB23` field @def CAN_F0R1_FB23_Pos */
#define CAN_F0R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB23` field @def CAN_F0R1_FB23_Msk */
#define CAN_F0R1_FB23_Msk		REG_BIT_MASK(CAN_F0R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F0R1_FB23 */
#define CAN_F0R1_FB23			CAN_F0R1_FB23_Msk
/** @brief Bit position of the `CAN_F0R1_FB24` field @def CAN_F0R1_FB24_Pos */
#define CAN_F0R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB24` field @def CAN_F0R1_FB24_Msk */
#define CAN_F0R1_FB24_Msk		REG_BIT_MASK(CAN_F0R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F0R1_FB24 */
#define CAN_F0R1_FB24			CAN_F0R1_FB24_Msk
/** @brief Bit position of the `CAN_F0R1_FB25` field @def CAN_F0R1_FB25_Pos */
#define CAN_F0R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB25` field @def CAN_F0R1_FB25_Msk */
#define CAN_F0R1_FB25_Msk		REG_BIT_MASK(CAN_F0R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F0R1_FB25 */
#define CAN_F0R1_FB25			CAN_F0R1_FB25_Msk
/** @brief Bit position of the `CAN_F0R1_FB26` field @def CAN_F0R1_FB26_Pos */
#define CAN_F0R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB26` field @def CAN_F0R1_FB26_Msk */
#define CAN_F0R1_FB26_Msk		REG_BIT_MASK(CAN_F0R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F0R1_FB26 */
#define CAN_F0R1_FB26			CAN_F0R1_FB26_Msk
/** @brief Bit position of the `CAN_F0R1_FB27` field @def CAN_F0R1_FB27_Pos */
#define CAN_F0R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB27` field @def CAN_F0R1_FB27_Msk */
#define CAN_F0R1_FB27_Msk		REG_BIT_MASK(CAN_F0R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F0R1_FB27 */
#define CAN_F0R1_FB27			CAN_F0R1_FB27_Msk
/** @brief Bit position of the `CAN_F0R1_FB28` field @def CAN_F0R1_FB28_Pos */
#define CAN_F0R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB28` field @def CAN_F0R1_FB28_Msk */
#define CAN_F0R1_FB28_Msk		REG_BIT_MASK(CAN_F0R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F0R1_FB28 */
#define CAN_F0R1_FB28			CAN_F0R1_FB28_Msk
/** @brief Bit position of the `CAN_F0R1_FB29` field @def CAN_F0R1_FB29_Pos */
#define CAN_F0R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB29` field @def CAN_F0R1_FB29_Msk */
#define CAN_F0R1_FB29_Msk		REG_BIT_MASK(CAN_F0R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F0R1_FB29 */
#define CAN_F0R1_FB29			CAN_F0R1_FB29_Msk
/** @brief Bit position of the `CAN_F0R1_FB30` field @def CAN_F0R1_FB30_Pos */
#define CAN_F0R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB30` field @def CAN_F0R1_FB30_Msk */
#define CAN_F0R1_FB30_Msk		REG_BIT_MASK(CAN_F0R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F0R1_FB30 */
#define CAN_F0R1_FB30			CAN_F0R1_FB30_Msk
/** @brief Bit position of the `CAN_F0R1_FB31` field @def CAN_F0R1_FB31_Pos */
#define CAN_F0R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F0R1_FB31` field @def CAN_F0R1_FB31_Msk */
#define CAN_F0R1_FB31_Msk		REG_BIT_MASK(CAN_F0R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F0R1_FB31 */
#define CAN_F0R1_FB31			CAN_F0R1_FB31_Msk

// ---------------------------------- CAN_F1R1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F1R1_FB0` field @def CAN_F1R1_FB0_Pos */
#define CAN_F1R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB0` field @def CAN_F1R1_FB0_Msk */
#define CAN_F1R1_FB0_Msk		REG_BIT_MASK(CAN_F1R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F1R1_FB0 */
#define CAN_F1R1_FB0			CAN_F1R1_FB0_Msk
/** @brief Bit position of the `CAN_F1R1_FB1` field @def CAN_F1R1_FB1_Pos */
#define CAN_F1R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB1` field @def CAN_F1R1_FB1_Msk */
#define CAN_F1R1_FB1_Msk		REG_BIT_MASK(CAN_F1R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F1R1_FB1 */
#define CAN_F1R1_FB1			CAN_F1R1_FB1_Msk
/** @brief Bit position of the `CAN_F1R1_FB2` field @def CAN_F1R1_FB2_Pos */
#define CAN_F1R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB2` field @def CAN_F1R1_FB2_Msk */
#define CAN_F1R1_FB2_Msk		REG_BIT_MASK(CAN_F1R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F1R1_FB2 */
#define CAN_F1R1_FB2			CAN_F1R1_FB2_Msk
/** @brief Bit position of the `CAN_F1R1_FB3` field @def CAN_F1R1_FB3_Pos */
#define CAN_F1R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB3` field @def CAN_F1R1_FB3_Msk */
#define CAN_F1R1_FB3_Msk		REG_BIT_MASK(CAN_F1R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F1R1_FB3 */
#define CAN_F1R1_FB3			CAN_F1R1_FB3_Msk
/** @brief Bit position of the `CAN_F1R1_FB4` field @def CAN_F1R1_FB4_Pos */
#define CAN_F1R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB4` field @def CAN_F1R1_FB4_Msk */
#define CAN_F1R1_FB4_Msk		REG_BIT_MASK(CAN_F1R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F1R1_FB4 */
#define CAN_F1R1_FB4			CAN_F1R1_FB4_Msk
/** @brief Bit position of the `CAN_F1R1_FB5` field @def CAN_F1R1_FB5_Pos */
#define CAN_F1R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB5` field @def CAN_F1R1_FB5_Msk */
#define CAN_F1R1_FB5_Msk		REG_BIT_MASK(CAN_F1R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F1R1_FB5 */
#define CAN_F1R1_FB5			CAN_F1R1_FB5_Msk
/** @brief Bit position of the `CAN_F1R1_FB6` field @def CAN_F1R1_FB6_Pos */
#define CAN_F1R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB6` field @def CAN_F1R1_FB6_Msk */
#define CAN_F1R1_FB6_Msk		REG_BIT_MASK(CAN_F1R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F1R1_FB6 */
#define CAN_F1R1_FB6			CAN_F1R1_FB6_Msk
/** @brief Bit position of the `CAN_F1R1_FB7` field @def CAN_F1R1_FB7_Pos */
#define CAN_F1R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB7` field @def CAN_F1R1_FB7_Msk */
#define CAN_F1R1_FB7_Msk		REG_BIT_MASK(CAN_F1R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F1R1_FB7 */
#define CAN_F1R1_FB7			CAN_F1R1_FB7_Msk
/** @brief Bit position of the `CAN_F1R1_FB8` field @def CAN_F1R1_FB8_Pos */
#define CAN_F1R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB8` field @def CAN_F1R1_FB8_Msk */
#define CAN_F1R1_FB8_Msk		REG_BIT_MASK(CAN_F1R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F1R1_FB8 */
#define CAN_F1R1_FB8			CAN_F1R1_FB8_Msk
/** @brief Bit position of the `CAN_F1R1_FB9` field @def CAN_F1R1_FB9_Pos */
#define CAN_F1R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB9` field @def CAN_F1R1_FB9_Msk */
#define CAN_F1R1_FB9_Msk		REG_BIT_MASK(CAN_F1R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F1R1_FB9 */
#define CAN_F1R1_FB9			CAN_F1R1_FB9_Msk
/** @brief Bit position of the `CAN_F1R1_FB10` field @def CAN_F1R1_FB10_Pos */
#define CAN_F1R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB10` field @def CAN_F1R1_FB10_Msk */
#define CAN_F1R1_FB10_Msk		REG_BIT_MASK(CAN_F1R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F1R1_FB10 */
#define CAN_F1R1_FB10			CAN_F1R1_FB10_Msk
/** @brief Bit position of the `CAN_F1R1_FB11` field @def CAN_F1R1_FB11_Pos */
#define CAN_F1R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB11` field @def CAN_F1R1_FB11_Msk */
#define CAN_F1R1_FB11_Msk		REG_BIT_MASK(CAN_F1R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F1R1_FB11 */
#define CAN_F1R1_FB11			CAN_F1R1_FB11_Msk
/** @brief Bit position of the `CAN_F1R1_FB12` field @def CAN_F1R1_FB12_Pos */
#define CAN_F1R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB12` field @def CAN_F1R1_FB12_Msk */
#define CAN_F1R1_FB12_Msk		REG_BIT_MASK(CAN_F1R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F1R1_FB12 */
#define CAN_F1R1_FB12			CAN_F1R1_FB12_Msk
/** @brief Bit position of the `CAN_F1R1_FB13` field @def CAN_F1R1_FB13_Pos */
#define CAN_F1R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB13` field @def CAN_F1R1_FB13_Msk */
#define CAN_F1R1_FB13_Msk		REG_BIT_MASK(CAN_F1R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F1R1_FB13 */
#define CAN_F1R1_FB13			CAN_F1R1_FB13_Msk
/** @brief Bit position of the `CAN_F1R1_FB14` field @def CAN_F1R1_FB14_Pos */
#define CAN_F1R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB14` field @def CAN_F1R1_FB14_Msk */
#define CAN_F1R1_FB14_Msk		REG_BIT_MASK(CAN_F1R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F1R1_FB14 */
#define CAN_F1R1_FB14			CAN_F1R1_FB14_Msk
/** @brief Bit position of the `CAN_F1R1_FB15` field @def CAN_F1R1_FB15_Pos */
#define CAN_F1R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB15` field @def CAN_F1R1_FB15_Msk */
#define CAN_F1R1_FB15_Msk		REG_BIT_MASK(CAN_F1R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F1R1_FB15 */
#define CAN_F1R1_FB15			CAN_F1R1_FB15_Msk
/** @brief Bit position of the `CAN_F1R1_FB16` field @def CAN_F1R1_FB16_Pos */
#define CAN_F1R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB16` field @def CAN_F1R1_FB16_Msk */
#define CAN_F1R1_FB16_Msk		REG_BIT_MASK(CAN_F1R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F1R1_FB16 */
#define CAN_F1R1_FB16			CAN_F1R1_FB16_Msk
/** @brief Bit position of the `CAN_F1R1_FB17` field @def CAN_F1R1_FB17_Pos */
#define CAN_F1R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB17` field @def CAN_F1R1_FB17_Msk */
#define CAN_F1R1_FB17_Msk		REG_BIT_MASK(CAN_F1R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F1R1_FB17 */
#define CAN_F1R1_FB17			CAN_F1R1_FB17_Msk
/** @brief Bit position of the `CAN_F1R1_FB18` field @def CAN_F1R1_FB18_Pos */
#define CAN_F1R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB18` field @def CAN_F1R1_FB18_Msk */
#define CAN_F1R1_FB18_Msk		REG_BIT_MASK(CAN_F1R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F1R1_FB18 */
#define CAN_F1R1_FB18			CAN_F1R1_FB18_Msk
/** @brief Bit position of the `CAN_F1R1_FB19` field @def CAN_F1R1_FB19_Pos */
#define CAN_F1R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB19` field @def CAN_F1R1_FB19_Msk */
#define CAN_F1R1_FB19_Msk		REG_BIT_MASK(CAN_F1R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F1R1_FB19 */
#define CAN_F1R1_FB19			CAN_F1R1_FB19_Msk
/** @brief Bit position of the `CAN_F1R1_FB20` field @def CAN_F1R1_FB20_Pos */
#define CAN_F1R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB20` field @def CAN_F1R1_FB20_Msk */
#define CAN_F1R1_FB20_Msk		REG_BIT_MASK(CAN_F1R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F1R1_FB20 */
#define CAN_F1R1_FB20			CAN_F1R1_FB20_Msk
/** @brief Bit position of the `CAN_F1R1_FB21` field @def CAN_F1R1_FB21_Pos */
#define CAN_F1R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB21` field @def CAN_F1R1_FB21_Msk */
#define CAN_F1R1_FB21_Msk		REG_BIT_MASK(CAN_F1R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F1R1_FB21 */
#define CAN_F1R1_FB21			CAN_F1R1_FB21_Msk
/** @brief Bit position of the `CAN_F1R1_FB22` field @def CAN_F1R1_FB22_Pos */
#define CAN_F1R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB22` field @def CAN_F1R1_FB22_Msk */
#define CAN_F1R1_FB22_Msk		REG_BIT_MASK(CAN_F1R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F1R1_FB22 */
#define CAN_F1R1_FB22			CAN_F1R1_FB22_Msk
/** @brief Bit position of the `CAN_F1R1_FB23` field @def CAN_F1R1_FB23_Pos */
#define CAN_F1R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB23` field @def CAN_F1R1_FB23_Msk */
#define CAN_F1R1_FB23_Msk		REG_BIT_MASK(CAN_F1R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F1R1_FB23 */
#define CAN_F1R1_FB23			CAN_F1R1_FB23_Msk
/** @brief Bit position of the `CAN_F1R1_FB24` field @def CAN_F1R1_FB24_Pos */
#define CAN_F1R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB24` field @def CAN_F1R1_FB24_Msk */
#define CAN_F1R1_FB24_Msk		REG_BIT_MASK(CAN_F1R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F1R1_FB24 */
#define CAN_F1R1_FB24			CAN_F1R1_FB24_Msk
/** @brief Bit position of the `CAN_F1R1_FB25` field @def CAN_F1R1_FB25_Pos */
#define CAN_F1R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB25` field @def CAN_F1R1_FB25_Msk */
#define CAN_F1R1_FB25_Msk		REG_BIT_MASK(CAN_F1R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F1R1_FB25 */
#define CAN_F1R1_FB25			CAN_F1R1_FB25_Msk
/** @brief Bit position of the `CAN_F1R1_FB26` field @def CAN_F1R1_FB26_Pos */
#define CAN_F1R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB26` field @def CAN_F1R1_FB26_Msk */
#define CAN_F1R1_FB26_Msk		REG_BIT_MASK(CAN_F1R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F1R1_FB26 */
#define CAN_F1R1_FB26			CAN_F1R1_FB26_Msk
/** @brief Bit position of the `CAN_F1R1_FB27` field @def CAN_F1R1_FB27_Pos */
#define CAN_F1R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB27` field @def CAN_F1R1_FB27_Msk */
#define CAN_F1R1_FB27_Msk		REG_BIT_MASK(CAN_F1R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F1R1_FB27 */
#define CAN_F1R1_FB27			CAN_F1R1_FB27_Msk
/** @brief Bit position of the `CAN_F1R1_FB28` field @def CAN_F1R1_FB28_Pos */
#define CAN_F1R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB28` field @def CAN_F1R1_FB28_Msk */
#define CAN_F1R1_FB28_Msk		REG_BIT_MASK(CAN_F1R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F1R1_FB28 */
#define CAN_F1R1_FB28			CAN_F1R1_FB28_Msk
/** @brief Bit position of the `CAN_F1R1_FB29` field @def CAN_F1R1_FB29_Pos */
#define CAN_F1R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB29` field @def CAN_F1R1_FB29_Msk */
#define CAN_F1R1_FB29_Msk		REG_BIT_MASK(CAN_F1R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F1R1_FB29 */
#define CAN_F1R1_FB29			CAN_F1R1_FB29_Msk
/** @brief Bit position of the `CAN_F1R1_FB30` field @def CAN_F1R1_FB30_Pos */
#define CAN_F1R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB30` field @def CAN_F1R1_FB30_Msk */
#define CAN_F1R1_FB30_Msk		REG_BIT_MASK(CAN_F1R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F1R1_FB30 */
#define CAN_F1R1_FB30			CAN_F1R1_FB30_Msk
/** @brief Bit position of the `CAN_F1R1_FB31` field @def CAN_F1R1_FB31_Pos */
#define CAN_F1R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F1R1_FB31` field @def CAN_F1R1_FB31_Msk */
#define CAN_F1R1_FB31_Msk		REG_BIT_MASK(CAN_F1R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F1R1_FB31 */
#define CAN_F1R1_FB31			CAN_F1R1_FB31_Msk

// ---------------------------------- CAN_F2R1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F2R1_FB0` field @def CAN_F2R1_FB0_Pos */
#define CAN_F2R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB0` field @def CAN_F2R1_FB0_Msk */
#define CAN_F2R1_FB0_Msk		REG_BIT_MASK(CAN_F2R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F2R1_FB0 */
#define CAN_F2R1_FB0			CAN_F2R1_FB0_Msk
/** @brief Bit position of the `CAN_F2R1_FB1` field @def CAN_F2R1_FB1_Pos */
#define CAN_F2R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB1` field @def CAN_F2R1_FB1_Msk */
#define CAN_F2R1_FB1_Msk		REG_BIT_MASK(CAN_F2R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F2R1_FB1 */
#define CAN_F2R1_FB1			CAN_F2R1_FB1_Msk
/** @brief Bit position of the `CAN_F2R1_FB2` field @def CAN_F2R1_FB2_Pos */
#define CAN_F2R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB2` field @def CAN_F2R1_FB2_Msk */
#define CAN_F2R1_FB2_Msk		REG_BIT_MASK(CAN_F2R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F2R1_FB2 */
#define CAN_F2R1_FB2			CAN_F2R1_FB2_Msk
/** @brief Bit position of the `CAN_F2R1_FB3` field @def CAN_F2R1_FB3_Pos */
#define CAN_F2R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB3` field @def CAN_F2R1_FB3_Msk */
#define CAN_F2R1_FB3_Msk		REG_BIT_MASK(CAN_F2R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F2R1_FB3 */
#define CAN_F2R1_FB3			CAN_F2R1_FB3_Msk
/** @brief Bit position of the `CAN_F2R1_FB4` field @def CAN_F2R1_FB4_Pos */
#define CAN_F2R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB4` field @def CAN_F2R1_FB4_Msk */
#define CAN_F2R1_FB4_Msk		REG_BIT_MASK(CAN_F2R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F2R1_FB4 */
#define CAN_F2R1_FB4			CAN_F2R1_FB4_Msk
/** @brief Bit position of the `CAN_F2R1_FB5` field @def CAN_F2R1_FB5_Pos */
#define CAN_F2R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB5` field @def CAN_F2R1_FB5_Msk */
#define CAN_F2R1_FB5_Msk		REG_BIT_MASK(CAN_F2R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F2R1_FB5 */
#define CAN_F2R1_FB5			CAN_F2R1_FB5_Msk
/** @brief Bit position of the `CAN_F2R1_FB6` field @def CAN_F2R1_FB6_Pos */
#define CAN_F2R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB6` field @def CAN_F2R1_FB6_Msk */
#define CAN_F2R1_FB6_Msk		REG_BIT_MASK(CAN_F2R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F2R1_FB6 */
#define CAN_F2R1_FB6			CAN_F2R1_FB6_Msk
/** @brief Bit position of the `CAN_F2R1_FB7` field @def CAN_F2R1_FB7_Pos */
#define CAN_F2R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB7` field @def CAN_F2R1_FB7_Msk */
#define CAN_F2R1_FB7_Msk		REG_BIT_MASK(CAN_F2R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F2R1_FB7 */
#define CAN_F2R1_FB7			CAN_F2R1_FB7_Msk
/** @brief Bit position of the `CAN_F2R1_FB8` field @def CAN_F2R1_FB8_Pos */
#define CAN_F2R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB8` field @def CAN_F2R1_FB8_Msk */
#define CAN_F2R1_FB8_Msk		REG_BIT_MASK(CAN_F2R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F2R1_FB8 */
#define CAN_F2R1_FB8			CAN_F2R1_FB8_Msk
/** @brief Bit position of the `CAN_F2R1_FB9` field @def CAN_F2R1_FB9_Pos */
#define CAN_F2R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB9` field @def CAN_F2R1_FB9_Msk */
#define CAN_F2R1_FB9_Msk		REG_BIT_MASK(CAN_F2R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F2R1_FB9 */
#define CAN_F2R1_FB9			CAN_F2R1_FB9_Msk
/** @brief Bit position of the `CAN_F2R1_FB10` field @def CAN_F2R1_FB10_Pos */
#define CAN_F2R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB10` field @def CAN_F2R1_FB10_Msk */
#define CAN_F2R1_FB10_Msk		REG_BIT_MASK(CAN_F2R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F2R1_FB10 */
#define CAN_F2R1_FB10			CAN_F2R1_FB10_Msk
/** @brief Bit position of the `CAN_F2R1_FB11` field @def CAN_F2R1_FB11_Pos */
#define CAN_F2R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB11` field @def CAN_F2R1_FB11_Msk */
#define CAN_F2R1_FB11_Msk		REG_BIT_MASK(CAN_F2R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F2R1_FB11 */
#define CAN_F2R1_FB11			CAN_F2R1_FB11_Msk
/** @brief Bit position of the `CAN_F2R1_FB12` field @def CAN_F2R1_FB12_Pos */
#define CAN_F2R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB12` field @def CAN_F2R1_FB12_Msk */
#define CAN_F2R1_FB12_Msk		REG_BIT_MASK(CAN_F2R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F2R1_FB12 */
#define CAN_F2R1_FB12			CAN_F2R1_FB12_Msk
/** @brief Bit position of the `CAN_F2R1_FB13` field @def CAN_F2R1_FB13_Pos */
#define CAN_F2R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB13` field @def CAN_F2R1_FB13_Msk */
#define CAN_F2R1_FB13_Msk		REG_BIT_MASK(CAN_F2R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F2R1_FB13 */
#define CAN_F2R1_FB13			CAN_F2R1_FB13_Msk
/** @brief Bit position of the `CAN_F2R1_FB14` field @def CAN_F2R1_FB14_Pos */
#define CAN_F2R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB14` field @def CAN_F2R1_FB14_Msk */
#define CAN_F2R1_FB14_Msk		REG_BIT_MASK(CAN_F2R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F2R1_FB14 */
#define CAN_F2R1_FB14			CAN_F2R1_FB14_Msk
/** @brief Bit position of the `CAN_F2R1_FB15` field @def CAN_F2R1_FB15_Pos */
#define CAN_F2R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB15` field @def CAN_F2R1_FB15_Msk */
#define CAN_F2R1_FB15_Msk		REG_BIT_MASK(CAN_F2R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F2R1_FB15 */
#define CAN_F2R1_FB15			CAN_F2R1_FB15_Msk
/** @brief Bit position of the `CAN_F2R1_FB16` field @def CAN_F2R1_FB16_Pos */
#define CAN_F2R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB16` field @def CAN_F2R1_FB16_Msk */
#define CAN_F2R1_FB16_Msk		REG_BIT_MASK(CAN_F2R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F2R1_FB16 */
#define CAN_F2R1_FB16			CAN_F2R1_FB16_Msk
/** @brief Bit position of the `CAN_F2R1_FB17` field @def CAN_F2R1_FB17_Pos */
#define CAN_F2R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB17` field @def CAN_F2R1_FB17_Msk */
#define CAN_F2R1_FB17_Msk		REG_BIT_MASK(CAN_F2R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F2R1_FB17 */
#define CAN_F2R1_FB17			CAN_F2R1_FB17_Msk
/** @brief Bit position of the `CAN_F2R1_FB18` field @def CAN_F2R1_FB18_Pos */
#define CAN_F2R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB18` field @def CAN_F2R1_FB18_Msk */
#define CAN_F2R1_FB18_Msk		REG_BIT_MASK(CAN_F2R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F2R1_FB18 */
#define CAN_F2R1_FB18			CAN_F2R1_FB18_Msk
/** @brief Bit position of the `CAN_F2R1_FB19` field @def CAN_F2R1_FB19_Pos */
#define CAN_F2R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB19` field @def CAN_F2R1_FB19_Msk */
#define CAN_F2R1_FB19_Msk		REG_BIT_MASK(CAN_F2R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F2R1_FB19 */
#define CAN_F2R1_FB19			CAN_F2R1_FB19_Msk
/** @brief Bit position of the `CAN_F2R1_FB20` field @def CAN_F2R1_FB20_Pos */
#define CAN_F2R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB20` field @def CAN_F2R1_FB20_Msk */
#define CAN_F2R1_FB20_Msk		REG_BIT_MASK(CAN_F2R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F2R1_FB20 */
#define CAN_F2R1_FB20			CAN_F2R1_FB20_Msk
/** @brief Bit position of the `CAN_F2R1_FB21` field @def CAN_F2R1_FB21_Pos */
#define CAN_F2R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB21` field @def CAN_F2R1_FB21_Msk */
#define CAN_F2R1_FB21_Msk		REG_BIT_MASK(CAN_F2R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F2R1_FB21 */
#define CAN_F2R1_FB21			CAN_F2R1_FB21_Msk
/** @brief Bit position of the `CAN_F2R1_FB22` field @def CAN_F2R1_FB22_Pos */
#define CAN_F2R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB22` field @def CAN_F2R1_FB22_Msk */
#define CAN_F2R1_FB22_Msk		REG_BIT_MASK(CAN_F2R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F2R1_FB22 */
#define CAN_F2R1_FB22			CAN_F2R1_FB22_Msk
/** @brief Bit position of the `CAN_F2R1_FB23` field @def CAN_F2R1_FB23_Pos */
#define CAN_F2R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB23` field @def CAN_F2R1_FB23_Msk */
#define CAN_F2R1_FB23_Msk		REG_BIT_MASK(CAN_F2R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F2R1_FB23 */
#define CAN_F2R1_FB23			CAN_F2R1_FB23_Msk
/** @brief Bit position of the `CAN_F2R1_FB24` field @def CAN_F2R1_FB24_Pos */
#define CAN_F2R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB24` field @def CAN_F2R1_FB24_Msk */
#define CAN_F2R1_FB24_Msk		REG_BIT_MASK(CAN_F2R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F2R1_FB24 */
#define CAN_F2R1_FB24			CAN_F2R1_FB24_Msk
/** @brief Bit position of the `CAN_F2R1_FB25` field @def CAN_F2R1_FB25_Pos */
#define CAN_F2R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB25` field @def CAN_F2R1_FB25_Msk */
#define CAN_F2R1_FB25_Msk		REG_BIT_MASK(CAN_F2R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F2R1_FB25 */
#define CAN_F2R1_FB25			CAN_F2R1_FB25_Msk
/** @brief Bit position of the `CAN_F2R1_FB26` field @def CAN_F2R1_FB26_Pos */
#define CAN_F2R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB26` field @def CAN_F2R1_FB26_Msk */
#define CAN_F2R1_FB26_Msk		REG_BIT_MASK(CAN_F2R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F2R1_FB26 */
#define CAN_F2R1_FB26			CAN_F2R1_FB26_Msk
/** @brief Bit position of the `CAN_F2R1_FB27` field @def CAN_F2R1_FB27_Pos */
#define CAN_F2R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB27` field @def CAN_F2R1_FB27_Msk */
#define CAN_F2R1_FB27_Msk		REG_BIT_MASK(CAN_F2R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F2R1_FB27 */
#define CAN_F2R1_FB27			CAN_F2R1_FB27_Msk
/** @brief Bit position of the `CAN_F2R1_FB28` field @def CAN_F2R1_FB28_Pos */
#define CAN_F2R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB28` field @def CAN_F2R1_FB28_Msk */
#define CAN_F2R1_FB28_Msk		REG_BIT_MASK(CAN_F2R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F2R1_FB28 */
#define CAN_F2R1_FB28			CAN_F2R1_FB28_Msk
/** @brief Bit position of the `CAN_F2R1_FB29` field @def CAN_F2R1_FB29_Pos */
#define CAN_F2R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB29` field @def CAN_F2R1_FB29_Msk */
#define CAN_F2R1_FB29_Msk		REG_BIT_MASK(CAN_F2R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F2R1_FB29 */
#define CAN_F2R1_FB29			CAN_F2R1_FB29_Msk
/** @brief Bit position of the `CAN_F2R1_FB30` field @def CAN_F2R1_FB30_Pos */
#define CAN_F2R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB30` field @def CAN_F2R1_FB30_Msk */
#define CAN_F2R1_FB30_Msk		REG_BIT_MASK(CAN_F2R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F2R1_FB30 */
#define CAN_F2R1_FB30			CAN_F2R1_FB30_Msk
/** @brief Bit position of the `CAN_F2R1_FB31` field @def CAN_F2R1_FB31_Pos */
#define CAN_F2R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F2R1_FB31` field @def CAN_F2R1_FB31_Msk */
#define CAN_F2R1_FB31_Msk		REG_BIT_MASK(CAN_F2R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F2R1_FB31 */
#define CAN_F2R1_FB31			CAN_F2R1_FB31_Msk

// ---------------------------------- CAN_F3R1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F3R1_FB0` field @def CAN_F3R1_FB0_Pos */
#define CAN_F3R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB0` field @def CAN_F3R1_FB0_Msk */
#define CAN_F3R1_FB0_Msk		REG_BIT_MASK(CAN_F3R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F3R1_FB0 */
#define CAN_F3R1_FB0			CAN_F3R1_FB0_Msk
/** @brief Bit position of the `CAN_F3R1_FB1` field @def CAN_F3R1_FB1_Pos */
#define CAN_F3R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB1` field @def CAN_F3R1_FB1_Msk */
#define CAN_F3R1_FB1_Msk		REG_BIT_MASK(CAN_F3R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F3R1_FB1 */
#define CAN_F3R1_FB1			CAN_F3R1_FB1_Msk
/** @brief Bit position of the `CAN_F3R1_FB2` field @def CAN_F3R1_FB2_Pos */
#define CAN_F3R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB2` field @def CAN_F3R1_FB2_Msk */
#define CAN_F3R1_FB2_Msk		REG_BIT_MASK(CAN_F3R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F3R1_FB2 */
#define CAN_F3R1_FB2			CAN_F3R1_FB2_Msk
/** @brief Bit position of the `CAN_F3R1_FB3` field @def CAN_F3R1_FB3_Pos */
#define CAN_F3R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB3` field @def CAN_F3R1_FB3_Msk */
#define CAN_F3R1_FB3_Msk		REG_BIT_MASK(CAN_F3R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F3R1_FB3 */
#define CAN_F3R1_FB3			CAN_F3R1_FB3_Msk
/** @brief Bit position of the `CAN_F3R1_FB4` field @def CAN_F3R1_FB4_Pos */
#define CAN_F3R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB4` field @def CAN_F3R1_FB4_Msk */
#define CAN_F3R1_FB4_Msk		REG_BIT_MASK(CAN_F3R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F3R1_FB4 */
#define CAN_F3R1_FB4			CAN_F3R1_FB4_Msk
/** @brief Bit position of the `CAN_F3R1_FB5` field @def CAN_F3R1_FB5_Pos */
#define CAN_F3R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB5` field @def CAN_F3R1_FB5_Msk */
#define CAN_F3R1_FB5_Msk		REG_BIT_MASK(CAN_F3R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F3R1_FB5 */
#define CAN_F3R1_FB5			CAN_F3R1_FB5_Msk
/** @brief Bit position of the `CAN_F3R1_FB6` field @def CAN_F3R1_FB6_Pos */
#define CAN_F3R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB6` field @def CAN_F3R1_FB6_Msk */
#define CAN_F3R1_FB6_Msk		REG_BIT_MASK(CAN_F3R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F3R1_FB6 */
#define CAN_F3R1_FB6			CAN_F3R1_FB6_Msk
/** @brief Bit position of the `CAN_F3R1_FB7` field @def CAN_F3R1_FB7_Pos */
#define CAN_F3R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB7` field @def CAN_F3R1_FB7_Msk */
#define CAN_F3R1_FB7_Msk		REG_BIT_MASK(CAN_F3R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F3R1_FB7 */
#define CAN_F3R1_FB7			CAN_F3R1_FB7_Msk
/** @brief Bit position of the `CAN_F3R1_FB8` field @def CAN_F3R1_FB8_Pos */
#define CAN_F3R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB8` field @def CAN_F3R1_FB8_Msk */
#define CAN_F3R1_FB8_Msk		REG_BIT_MASK(CAN_F3R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F3R1_FB8 */
#define CAN_F3R1_FB8			CAN_F3R1_FB8_Msk
/** @brief Bit position of the `CAN_F3R1_FB9` field @def CAN_F3R1_FB9_Pos */
#define CAN_F3R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB9` field @def CAN_F3R1_FB9_Msk */
#define CAN_F3R1_FB9_Msk		REG_BIT_MASK(CAN_F3R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F3R1_FB9 */
#define CAN_F3R1_FB9			CAN_F3R1_FB9_Msk
/** @brief Bit position of the `CAN_F3R1_FB10` field @def CAN_F3R1_FB10_Pos */
#define CAN_F3R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB10` field @def CAN_F3R1_FB10_Msk */
#define CAN_F3R1_FB10_Msk		REG_BIT_MASK(CAN_F3R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F3R1_FB10 */
#define CAN_F3R1_FB10			CAN_F3R1_FB10_Msk
/** @brief Bit position of the `CAN_F3R1_FB11` field @def CAN_F3R1_FB11_Pos */
#define CAN_F3R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB11` field @def CAN_F3R1_FB11_Msk */
#define CAN_F3R1_FB11_Msk		REG_BIT_MASK(CAN_F3R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F3R1_FB11 */
#define CAN_F3R1_FB11			CAN_F3R1_FB11_Msk
/** @brief Bit position of the `CAN_F3R1_FB12` field @def CAN_F3R1_FB12_Pos */
#define CAN_F3R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB12` field @def CAN_F3R1_FB12_Msk */
#define CAN_F3R1_FB12_Msk		REG_BIT_MASK(CAN_F3R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F3R1_FB12 */
#define CAN_F3R1_FB12			CAN_F3R1_FB12_Msk
/** @brief Bit position of the `CAN_F3R1_FB13` field @def CAN_F3R1_FB13_Pos */
#define CAN_F3R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB13` field @def CAN_F3R1_FB13_Msk */
#define CAN_F3R1_FB13_Msk		REG_BIT_MASK(CAN_F3R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F3R1_FB13 */
#define CAN_F3R1_FB13			CAN_F3R1_FB13_Msk
/** @brief Bit position of the `CAN_F3R1_FB14` field @def CAN_F3R1_FB14_Pos */
#define CAN_F3R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB14` field @def CAN_F3R1_FB14_Msk */
#define CAN_F3R1_FB14_Msk		REG_BIT_MASK(CAN_F3R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F3R1_FB14 */
#define CAN_F3R1_FB14			CAN_F3R1_FB14_Msk
/** @brief Bit position of the `CAN_F3R1_FB15` field @def CAN_F3R1_FB15_Pos */
#define CAN_F3R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB15` field @def CAN_F3R1_FB15_Msk */
#define CAN_F3R1_FB15_Msk		REG_BIT_MASK(CAN_F3R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F3R1_FB15 */
#define CAN_F3R1_FB15			CAN_F3R1_FB15_Msk
/** @brief Bit position of the `CAN_F3R1_FB16` field @def CAN_F3R1_FB16_Pos */
#define CAN_F3R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB16` field @def CAN_F3R1_FB16_Msk */
#define CAN_F3R1_FB16_Msk		REG_BIT_MASK(CAN_F3R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F3R1_FB16 */
#define CAN_F3R1_FB16			CAN_F3R1_FB16_Msk
/** @brief Bit position of the `CAN_F3R1_FB17` field @def CAN_F3R1_FB17_Pos */
#define CAN_F3R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB17` field @def CAN_F3R1_FB17_Msk */
#define CAN_F3R1_FB17_Msk		REG_BIT_MASK(CAN_F3R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F3R1_FB17 */
#define CAN_F3R1_FB17			CAN_F3R1_FB17_Msk
/** @brief Bit position of the `CAN_F3R1_FB18` field @def CAN_F3R1_FB18_Pos */
#define CAN_F3R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB18` field @def CAN_F3R1_FB18_Msk */
#define CAN_F3R1_FB18_Msk		REG_BIT_MASK(CAN_F3R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F3R1_FB18 */
#define CAN_F3R1_FB18			CAN_F3R1_FB18_Msk
/** @brief Bit position of the `CAN_F3R1_FB19` field @def CAN_F3R1_FB19_Pos */
#define CAN_F3R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB19` field @def CAN_F3R1_FB19_Msk */
#define CAN_F3R1_FB19_Msk		REG_BIT_MASK(CAN_F3R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F3R1_FB19 */
#define CAN_F3R1_FB19			CAN_F3R1_FB19_Msk
/** @brief Bit position of the `CAN_F3R1_FB20` field @def CAN_F3R1_FB20_Pos */
#define CAN_F3R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB20` field @def CAN_F3R1_FB20_Msk */
#define CAN_F3R1_FB20_Msk		REG_BIT_MASK(CAN_F3R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F3R1_FB20 */
#define CAN_F3R1_FB20			CAN_F3R1_FB20_Msk
/** @brief Bit position of the `CAN_F3R1_FB21` field @def CAN_F3R1_FB21_Pos */
#define CAN_F3R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB21` field @def CAN_F3R1_FB21_Msk */
#define CAN_F3R1_FB21_Msk		REG_BIT_MASK(CAN_F3R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F3R1_FB21 */
#define CAN_F3R1_FB21			CAN_F3R1_FB21_Msk
/** @brief Bit position of the `CAN_F3R1_FB22` field @def CAN_F3R1_FB22_Pos */
#define CAN_F3R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB22` field @def CAN_F3R1_FB22_Msk */
#define CAN_F3R1_FB22_Msk		REG_BIT_MASK(CAN_F3R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F3R1_FB22 */
#define CAN_F3R1_FB22			CAN_F3R1_FB22_Msk
/** @brief Bit position of the `CAN_F3R1_FB23` field @def CAN_F3R1_FB23_Pos */
#define CAN_F3R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB23` field @def CAN_F3R1_FB23_Msk */
#define CAN_F3R1_FB23_Msk		REG_BIT_MASK(CAN_F3R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F3R1_FB23 */
#define CAN_F3R1_FB23			CAN_F3R1_FB23_Msk
/** @brief Bit position of the `CAN_F3R1_FB24` field @def CAN_F3R1_FB24_Pos */
#define CAN_F3R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB24` field @def CAN_F3R1_FB24_Msk */
#define CAN_F3R1_FB24_Msk		REG_BIT_MASK(CAN_F3R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F3R1_FB24 */
#define CAN_F3R1_FB24			CAN_F3R1_FB24_Msk
/** @brief Bit position of the `CAN_F3R1_FB25` field @def CAN_F3R1_FB25_Pos */
#define CAN_F3R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB25` field @def CAN_F3R1_FB25_Msk */
#define CAN_F3R1_FB25_Msk		REG_BIT_MASK(CAN_F3R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F3R1_FB25 */
#define CAN_F3R1_FB25			CAN_F3R1_FB25_Msk
/** @brief Bit position of the `CAN_F3R1_FB26` field @def CAN_F3R1_FB26_Pos */
#define CAN_F3R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB26` field @def CAN_F3R1_FB26_Msk */
#define CAN_F3R1_FB26_Msk		REG_BIT_MASK(CAN_F3R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F3R1_FB26 */
#define CAN_F3R1_FB26			CAN_F3R1_FB26_Msk
/** @brief Bit position of the `CAN_F3R1_FB27` field @def CAN_F3R1_FB27_Pos */
#define CAN_F3R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB27` field @def CAN_F3R1_FB27_Msk */
#define CAN_F3R1_FB27_Msk		REG_BIT_MASK(CAN_F3R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F3R1_FB27 */
#define CAN_F3R1_FB27			CAN_F3R1_FB27_Msk
/** @brief Bit position of the `CAN_F3R1_FB28` field @def CAN_F3R1_FB28_Pos */
#define CAN_F3R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB28` field @def CAN_F3R1_FB28_Msk */
#define CAN_F3R1_FB28_Msk		REG_BIT_MASK(CAN_F3R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F3R1_FB28 */
#define CAN_F3R1_FB28			CAN_F3R1_FB28_Msk
/** @brief Bit position of the `CAN_F3R1_FB29` field @def CAN_F3R1_FB29_Pos */
#define CAN_F3R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB29` field @def CAN_F3R1_FB29_Msk */
#define CAN_F3R1_FB29_Msk		REG_BIT_MASK(CAN_F3R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F3R1_FB29 */
#define CAN_F3R1_FB29			CAN_F3R1_FB29_Msk
/** @brief Bit position of the `CAN_F3R1_FB30` field @def CAN_F3R1_FB30_Pos */
#define CAN_F3R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB30` field @def CAN_F3R1_FB30_Msk */
#define CAN_F3R1_FB30_Msk		REG_BIT_MASK(CAN_F3R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F3R1_FB30 */
#define CAN_F3R1_FB30			CAN_F3R1_FB30_Msk
/** @brief Bit position of the `CAN_F3R1_FB31` field @def CAN_F3R1_FB31_Pos */
#define CAN_F3R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F3R1_FB31` field @def CAN_F3R1_FB31_Msk */
#define CAN_F3R1_FB31_Msk		REG_BIT_MASK(CAN_F3R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F3R1_FB31 */
#define CAN_F3R1_FB31			CAN_F3R1_FB31_Msk

// ---------------------------------- CAN_F4R1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F4R1_FB0` field @def CAN_F4R1_FB0_Pos */
#define CAN_F4R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB0` field @def CAN_F4R1_FB0_Msk */
#define CAN_F4R1_FB0_Msk		REG_BIT_MASK(CAN_F4R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F4R1_FB0 */
#define CAN_F4R1_FB0			CAN_F4R1_FB0_Msk
/** @brief Bit position of the `CAN_F4R1_FB1` field @def CAN_F4R1_FB1_Pos */
#define CAN_F4R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB1` field @def CAN_F4R1_FB1_Msk */
#define CAN_F4R1_FB1_Msk		REG_BIT_MASK(CAN_F4R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F4R1_FB1 */
#define CAN_F4R1_FB1			CAN_F4R1_FB1_Msk
/** @brief Bit position of the `CAN_F4R1_FB2` field @def CAN_F4R1_FB2_Pos */
#define CAN_F4R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB2` field @def CAN_F4R1_FB2_Msk */
#define CAN_F4R1_FB2_Msk		REG_BIT_MASK(CAN_F4R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F4R1_FB2 */
#define CAN_F4R1_FB2			CAN_F4R1_FB2_Msk
/** @brief Bit position of the `CAN_F4R1_FB3` field @def CAN_F4R1_FB3_Pos */
#define CAN_F4R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB3` field @def CAN_F4R1_FB3_Msk */
#define CAN_F4R1_FB3_Msk		REG_BIT_MASK(CAN_F4R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F4R1_FB3 */
#define CAN_F4R1_FB3			CAN_F4R1_FB3_Msk
/** @brief Bit position of the `CAN_F4R1_FB4` field @def CAN_F4R1_FB4_Pos */
#define CAN_F4R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB4` field @def CAN_F4R1_FB4_Msk */
#define CAN_F4R1_FB4_Msk		REG_BIT_MASK(CAN_F4R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F4R1_FB4 */
#define CAN_F4R1_FB4			CAN_F4R1_FB4_Msk
/** @brief Bit position of the `CAN_F4R1_FB5` field @def CAN_F4R1_FB5_Pos */
#define CAN_F4R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB5` field @def CAN_F4R1_FB5_Msk */
#define CAN_F4R1_FB5_Msk		REG_BIT_MASK(CAN_F4R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F4R1_FB5 */
#define CAN_F4R1_FB5			CAN_F4R1_FB5_Msk
/** @brief Bit position of the `CAN_F4R1_FB6` field @def CAN_F4R1_FB6_Pos */
#define CAN_F4R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB6` field @def CAN_F4R1_FB6_Msk */
#define CAN_F4R1_FB6_Msk		REG_BIT_MASK(CAN_F4R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F4R1_FB6 */
#define CAN_F4R1_FB6			CAN_F4R1_FB6_Msk
/** @brief Bit position of the `CAN_F4R1_FB7` field @def CAN_F4R1_FB7_Pos */
#define CAN_F4R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB7` field @def CAN_F4R1_FB7_Msk */
#define CAN_F4R1_FB7_Msk		REG_BIT_MASK(CAN_F4R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F4R1_FB7 */
#define CAN_F4R1_FB7			CAN_F4R1_FB7_Msk
/** @brief Bit position of the `CAN_F4R1_FB8` field @def CAN_F4R1_FB8_Pos */
#define CAN_F4R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB8` field @def CAN_F4R1_FB8_Msk */
#define CAN_F4R1_FB8_Msk		REG_BIT_MASK(CAN_F4R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F4R1_FB8 */
#define CAN_F4R1_FB8			CAN_F4R1_FB8_Msk
/** @brief Bit position of the `CAN_F4R1_FB9` field @def CAN_F4R1_FB9_Pos */
#define CAN_F4R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB9` field @def CAN_F4R1_FB9_Msk */
#define CAN_F4R1_FB9_Msk		REG_BIT_MASK(CAN_F4R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F4R1_FB9 */
#define CAN_F4R1_FB9			CAN_F4R1_FB9_Msk
/** @brief Bit position of the `CAN_F4R1_FB10` field @def CAN_F4R1_FB10_Pos */
#define CAN_F4R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB10` field @def CAN_F4R1_FB10_Msk */
#define CAN_F4R1_FB10_Msk		REG_BIT_MASK(CAN_F4R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F4R1_FB10 */
#define CAN_F4R1_FB10			CAN_F4R1_FB10_Msk
/** @brief Bit position of the `CAN_F4R1_FB11` field @def CAN_F4R1_FB11_Pos */
#define CAN_F4R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB11` field @def CAN_F4R1_FB11_Msk */
#define CAN_F4R1_FB11_Msk		REG_BIT_MASK(CAN_F4R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F4R1_FB11 */
#define CAN_F4R1_FB11			CAN_F4R1_FB11_Msk
/** @brief Bit position of the `CAN_F4R1_FB12` field @def CAN_F4R1_FB12_Pos */
#define CAN_F4R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB12` field @def CAN_F4R1_FB12_Msk */
#define CAN_F4R1_FB12_Msk		REG_BIT_MASK(CAN_F4R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F4R1_FB12 */
#define CAN_F4R1_FB12			CAN_F4R1_FB12_Msk
/** @brief Bit position of the `CAN_F4R1_FB13` field @def CAN_F4R1_FB13_Pos */
#define CAN_F4R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB13` field @def CAN_F4R1_FB13_Msk */
#define CAN_F4R1_FB13_Msk		REG_BIT_MASK(CAN_F4R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F4R1_FB13 */
#define CAN_F4R1_FB13			CAN_F4R1_FB13_Msk
/** @brief Bit position of the `CAN_F4R1_FB14` field @def CAN_F4R1_FB14_Pos */
#define CAN_F4R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB14` field @def CAN_F4R1_FB14_Msk */
#define CAN_F4R1_FB14_Msk		REG_BIT_MASK(CAN_F4R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F4R1_FB14 */
#define CAN_F4R1_FB14			CAN_F4R1_FB14_Msk
/** @brief Bit position of the `CAN_F4R1_FB15` field @def CAN_F4R1_FB15_Pos */
#define CAN_F4R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB15` field @def CAN_F4R1_FB15_Msk */
#define CAN_F4R1_FB15_Msk		REG_BIT_MASK(CAN_F4R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F4R1_FB15 */
#define CAN_F4R1_FB15			CAN_F4R1_FB15_Msk
/** @brief Bit position of the `CAN_F4R1_FB16` field @def CAN_F4R1_FB16_Pos */
#define CAN_F4R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB16` field @def CAN_F4R1_FB16_Msk */
#define CAN_F4R1_FB16_Msk		REG_BIT_MASK(CAN_F4R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F4R1_FB16 */
#define CAN_F4R1_FB16			CAN_F4R1_FB16_Msk
/** @brief Bit position of the `CAN_F4R1_FB17` field @def CAN_F4R1_FB17_Pos */
#define CAN_F4R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB17` field @def CAN_F4R1_FB17_Msk */
#define CAN_F4R1_FB17_Msk		REG_BIT_MASK(CAN_F4R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F4R1_FB17 */
#define CAN_F4R1_FB17			CAN_F4R1_FB17_Msk
/** @brief Bit position of the `CAN_F4R1_FB18` field @def CAN_F4R1_FB18_Pos */
#define CAN_F4R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB18` field @def CAN_F4R1_FB18_Msk */
#define CAN_F4R1_FB18_Msk		REG_BIT_MASK(CAN_F4R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F4R1_FB18 */
#define CAN_F4R1_FB18			CAN_F4R1_FB18_Msk
/** @brief Bit position of the `CAN_F4R1_FB19` field @def CAN_F4R1_FB19_Pos */
#define CAN_F4R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB19` field @def CAN_F4R1_FB19_Msk */
#define CAN_F4R1_FB19_Msk		REG_BIT_MASK(CAN_F4R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F4R1_FB19 */
#define CAN_F4R1_FB19			CAN_F4R1_FB19_Msk
/** @brief Bit position of the `CAN_F4R1_FB20` field @def CAN_F4R1_FB20_Pos */
#define CAN_F4R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB20` field @def CAN_F4R1_FB20_Msk */
#define CAN_F4R1_FB20_Msk		REG_BIT_MASK(CAN_F4R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F4R1_FB20 */
#define CAN_F4R1_FB20			CAN_F4R1_FB20_Msk
/** @brief Bit position of the `CAN_F4R1_FB21` field @def CAN_F4R1_FB21_Pos */
#define CAN_F4R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB21` field @def CAN_F4R1_FB21_Msk */
#define CAN_F4R1_FB21_Msk		REG_BIT_MASK(CAN_F4R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F4R1_FB21 */
#define CAN_F4R1_FB21			CAN_F4R1_FB21_Msk
/** @brief Bit position of the `CAN_F4R1_FB22` field @def CAN_F4R1_FB22_Pos */
#define CAN_F4R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB22` field @def CAN_F4R1_FB22_Msk */
#define CAN_F4R1_FB22_Msk		REG_BIT_MASK(CAN_F4R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F4R1_FB22 */
#define CAN_F4R1_FB22			CAN_F4R1_FB22_Msk
/** @brief Bit position of the `CAN_F4R1_FB23` field @def CAN_F4R1_FB23_Pos */
#define CAN_F4R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB23` field @def CAN_F4R1_FB23_Msk */
#define CAN_F4R1_FB23_Msk		REG_BIT_MASK(CAN_F4R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F4R1_FB23 */
#define CAN_F4R1_FB23			CAN_F4R1_FB23_Msk
/** @brief Bit position of the `CAN_F4R1_FB24` field @def CAN_F4R1_FB24_Pos */
#define CAN_F4R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB24` field @def CAN_F4R1_FB24_Msk */
#define CAN_F4R1_FB24_Msk		REG_BIT_MASK(CAN_F4R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F4R1_FB24 */
#define CAN_F4R1_FB24			CAN_F4R1_FB24_Msk
/** @brief Bit position of the `CAN_F4R1_FB25` field @def CAN_F4R1_FB25_Pos */
#define CAN_F4R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB25` field @def CAN_F4R1_FB25_Msk */
#define CAN_F4R1_FB25_Msk		REG_BIT_MASK(CAN_F4R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F4R1_FB25 */
#define CAN_F4R1_FB25			CAN_F4R1_FB25_Msk
/** @brief Bit position of the `CAN_F4R1_FB26` field @def CAN_F4R1_FB26_Pos */
#define CAN_F4R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB26` field @def CAN_F4R1_FB26_Msk */
#define CAN_F4R1_FB26_Msk		REG_BIT_MASK(CAN_F4R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F4R1_FB26 */
#define CAN_F4R1_FB26			CAN_F4R1_FB26_Msk
/** @brief Bit position of the `CAN_F4R1_FB27` field @def CAN_F4R1_FB27_Pos */
#define CAN_F4R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB27` field @def CAN_F4R1_FB27_Msk */
#define CAN_F4R1_FB27_Msk		REG_BIT_MASK(CAN_F4R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F4R1_FB27 */
#define CAN_F4R1_FB27			CAN_F4R1_FB27_Msk
/** @brief Bit position of the `CAN_F4R1_FB28` field @def CAN_F4R1_FB28_Pos */
#define CAN_F4R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB28` field @def CAN_F4R1_FB28_Msk */
#define CAN_F4R1_FB28_Msk		REG_BIT_MASK(CAN_F4R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F4R1_FB28 */
#define CAN_F4R1_FB28			CAN_F4R1_FB28_Msk
/** @brief Bit position of the `CAN_F4R1_FB29` field @def CAN_F4R1_FB29_Pos */
#define CAN_F4R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB29` field @def CAN_F4R1_FB29_Msk */
#define CAN_F4R1_FB29_Msk		REG_BIT_MASK(CAN_F4R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F4R1_FB29 */
#define CAN_F4R1_FB29			CAN_F4R1_FB29_Msk
/** @brief Bit position of the `CAN_F4R1_FB30` field @def CAN_F4R1_FB30_Pos */
#define CAN_F4R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB30` field @def CAN_F4R1_FB30_Msk */
#define CAN_F4R1_FB30_Msk		REG_BIT_MASK(CAN_F4R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F4R1_FB30 */
#define CAN_F4R1_FB30			CAN_F4R1_FB30_Msk
/** @brief Bit position of the `CAN_F4R1_FB31` field @def CAN_F4R1_FB31_Pos */
#define CAN_F4R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F4R1_FB31` field @def CAN_F4R1_FB31_Msk */
#define CAN_F4R1_FB31_Msk		REG_BIT_MASK(CAN_F4R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F4R1_FB31 */
#define CAN_F4R1_FB31			CAN_F4R1_FB31_Msk

// ---------------------------------- CAN_F5R1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F5R1_FB0` field @def CAN_F5R1_FB0_Pos */
#define CAN_F5R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB0` field @def CAN_F5R1_FB0_Msk */
#define CAN_F5R1_FB0_Msk		REG_BIT_MASK(CAN_F5R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F5R1_FB0 */
#define CAN_F5R1_FB0			CAN_F5R1_FB0_Msk
/** @brief Bit position of the `CAN_F5R1_FB1` field @def CAN_F5R1_FB1_Pos */
#define CAN_F5R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB1` field @def CAN_F5R1_FB1_Msk */
#define CAN_F5R1_FB1_Msk		REG_BIT_MASK(CAN_F5R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F5R1_FB1 */
#define CAN_F5R1_FB1			CAN_F5R1_FB1_Msk
/** @brief Bit position of the `CAN_F5R1_FB2` field @def CAN_F5R1_FB2_Pos */
#define CAN_F5R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB2` field @def CAN_F5R1_FB2_Msk */
#define CAN_F5R1_FB2_Msk		REG_BIT_MASK(CAN_F5R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F5R1_FB2 */
#define CAN_F5R1_FB2			CAN_F5R1_FB2_Msk
/** @brief Bit position of the `CAN_F5R1_FB3` field @def CAN_F5R1_FB3_Pos */
#define CAN_F5R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB3` field @def CAN_F5R1_FB3_Msk */
#define CAN_F5R1_FB3_Msk		REG_BIT_MASK(CAN_F5R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F5R1_FB3 */
#define CAN_F5R1_FB3			CAN_F5R1_FB3_Msk
/** @brief Bit position of the `CAN_F5R1_FB4` field @def CAN_F5R1_FB4_Pos */
#define CAN_F5R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB4` field @def CAN_F5R1_FB4_Msk */
#define CAN_F5R1_FB4_Msk		REG_BIT_MASK(CAN_F5R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F5R1_FB4 */
#define CAN_F5R1_FB4			CAN_F5R1_FB4_Msk
/** @brief Bit position of the `CAN_F5R1_FB5` field @def CAN_F5R1_FB5_Pos */
#define CAN_F5R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB5` field @def CAN_F5R1_FB5_Msk */
#define CAN_F5R1_FB5_Msk		REG_BIT_MASK(CAN_F5R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F5R1_FB5 */
#define CAN_F5R1_FB5			CAN_F5R1_FB5_Msk
/** @brief Bit position of the `CAN_F5R1_FB6` field @def CAN_F5R1_FB6_Pos */
#define CAN_F5R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB6` field @def CAN_F5R1_FB6_Msk */
#define CAN_F5R1_FB6_Msk		REG_BIT_MASK(CAN_F5R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F5R1_FB6 */
#define CAN_F5R1_FB6			CAN_F5R1_FB6_Msk
/** @brief Bit position of the `CAN_F5R1_FB7` field @def CAN_F5R1_FB7_Pos */
#define CAN_F5R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB7` field @def CAN_F5R1_FB7_Msk */
#define CAN_F5R1_FB7_Msk		REG_BIT_MASK(CAN_F5R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F5R1_FB7 */
#define CAN_F5R1_FB7			CAN_F5R1_FB7_Msk
/** @brief Bit position of the `CAN_F5R1_FB8` field @def CAN_F5R1_FB8_Pos */
#define CAN_F5R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB8` field @def CAN_F5R1_FB8_Msk */
#define CAN_F5R1_FB8_Msk		REG_BIT_MASK(CAN_F5R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F5R1_FB8 */
#define CAN_F5R1_FB8			CAN_F5R1_FB8_Msk
/** @brief Bit position of the `CAN_F5R1_FB9` field @def CAN_F5R1_FB9_Pos */
#define CAN_F5R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB9` field @def CAN_F5R1_FB9_Msk */
#define CAN_F5R1_FB9_Msk		REG_BIT_MASK(CAN_F5R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F5R1_FB9 */
#define CAN_F5R1_FB9			CAN_F5R1_FB9_Msk
/** @brief Bit position of the `CAN_F5R1_FB10` field @def CAN_F5R1_FB10_Pos */
#define CAN_F5R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB10` field @def CAN_F5R1_FB10_Msk */
#define CAN_F5R1_FB10_Msk		REG_BIT_MASK(CAN_F5R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F5R1_FB10 */
#define CAN_F5R1_FB10			CAN_F5R1_FB10_Msk
/** @brief Bit position of the `CAN_F5R1_FB11` field @def CAN_F5R1_FB11_Pos */
#define CAN_F5R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB11` field @def CAN_F5R1_FB11_Msk */
#define CAN_F5R1_FB11_Msk		REG_BIT_MASK(CAN_F5R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F5R1_FB11 */
#define CAN_F5R1_FB11			CAN_F5R1_FB11_Msk
/** @brief Bit position of the `CAN_F5R1_FB12` field @def CAN_F5R1_FB12_Pos */
#define CAN_F5R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB12` field @def CAN_F5R1_FB12_Msk */
#define CAN_F5R1_FB12_Msk		REG_BIT_MASK(CAN_F5R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F5R1_FB12 */
#define CAN_F5R1_FB12			CAN_F5R1_FB12_Msk
/** @brief Bit position of the `CAN_F5R1_FB13` field @def CAN_F5R1_FB13_Pos */
#define CAN_F5R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB13` field @def CAN_F5R1_FB13_Msk */
#define CAN_F5R1_FB13_Msk		REG_BIT_MASK(CAN_F5R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F5R1_FB13 */
#define CAN_F5R1_FB13			CAN_F5R1_FB13_Msk
/** @brief Bit position of the `CAN_F5R1_FB14` field @def CAN_F5R1_FB14_Pos */
#define CAN_F5R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB14` field @def CAN_F5R1_FB14_Msk */
#define CAN_F5R1_FB14_Msk		REG_BIT_MASK(CAN_F5R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F5R1_FB14 */
#define CAN_F5R1_FB14			CAN_F5R1_FB14_Msk
/** @brief Bit position of the `CAN_F5R1_FB15` field @def CAN_F5R1_FB15_Pos */
#define CAN_F5R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB15` field @def CAN_F5R1_FB15_Msk */
#define CAN_F5R1_FB15_Msk		REG_BIT_MASK(CAN_F5R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F5R1_FB15 */
#define CAN_F5R1_FB15			CAN_F5R1_FB15_Msk
/** @brief Bit position of the `CAN_F5R1_FB16` field @def CAN_F5R1_FB16_Pos */
#define CAN_F5R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB16` field @def CAN_F5R1_FB16_Msk */
#define CAN_F5R1_FB16_Msk		REG_BIT_MASK(CAN_F5R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F5R1_FB16 */
#define CAN_F5R1_FB16			CAN_F5R1_FB16_Msk
/** @brief Bit position of the `CAN_F5R1_FB17` field @def CAN_F5R1_FB17_Pos */
#define CAN_F5R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB17` field @def CAN_F5R1_FB17_Msk */
#define CAN_F5R1_FB17_Msk		REG_BIT_MASK(CAN_F5R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F5R1_FB17 */
#define CAN_F5R1_FB17			CAN_F5R1_FB17_Msk
/** @brief Bit position of the `CAN_F5R1_FB18` field @def CAN_F5R1_FB18_Pos */
#define CAN_F5R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB18` field @def CAN_F5R1_FB18_Msk */
#define CAN_F5R1_FB18_Msk		REG_BIT_MASK(CAN_F5R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F5R1_FB18 */
#define CAN_F5R1_FB18			CAN_F5R1_FB18_Msk
/** @brief Bit position of the `CAN_F5R1_FB19` field @def CAN_F5R1_FB19_Pos */
#define CAN_F5R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB19` field @def CAN_F5R1_FB19_Msk */
#define CAN_F5R1_FB19_Msk		REG_BIT_MASK(CAN_F5R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F5R1_FB19 */
#define CAN_F5R1_FB19			CAN_F5R1_FB19_Msk
/** @brief Bit position of the `CAN_F5R1_FB20` field @def CAN_F5R1_FB20_Pos */
#define CAN_F5R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB20` field @def CAN_F5R1_FB20_Msk */
#define CAN_F5R1_FB20_Msk		REG_BIT_MASK(CAN_F5R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F5R1_FB20 */
#define CAN_F5R1_FB20			CAN_F5R1_FB20_Msk
/** @brief Bit position of the `CAN_F5R1_FB21` field @def CAN_F5R1_FB21_Pos */
#define CAN_F5R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB21` field @def CAN_F5R1_FB21_Msk */
#define CAN_F5R1_FB21_Msk		REG_BIT_MASK(CAN_F5R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F5R1_FB21 */
#define CAN_F5R1_FB21			CAN_F5R1_FB21_Msk
/** @brief Bit position of the `CAN_F5R1_FB22` field @def CAN_F5R1_FB22_Pos */
#define CAN_F5R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB22` field @def CAN_F5R1_FB22_Msk */
#define CAN_F5R1_FB22_Msk		REG_BIT_MASK(CAN_F5R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F5R1_FB22 */
#define CAN_F5R1_FB22			CAN_F5R1_FB22_Msk
/** @brief Bit position of the `CAN_F5R1_FB23` field @def CAN_F5R1_FB23_Pos */
#define CAN_F5R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB23` field @def CAN_F5R1_FB23_Msk */
#define CAN_F5R1_FB23_Msk		REG_BIT_MASK(CAN_F5R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F5R1_FB23 */
#define CAN_F5R1_FB23			CAN_F5R1_FB23_Msk
/** @brief Bit position of the `CAN_F5R1_FB24` field @def CAN_F5R1_FB24_Pos */
#define CAN_F5R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB24` field @def CAN_F5R1_FB24_Msk */
#define CAN_F5R1_FB24_Msk		REG_BIT_MASK(CAN_F5R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F5R1_FB24 */
#define CAN_F5R1_FB24			CAN_F5R1_FB24_Msk
/** @brief Bit position of the `CAN_F5R1_FB25` field @def CAN_F5R1_FB25_Pos */
#define CAN_F5R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB25` field @def CAN_F5R1_FB25_Msk */
#define CAN_F5R1_FB25_Msk		REG_BIT_MASK(CAN_F5R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F5R1_FB25 */
#define CAN_F5R1_FB25			CAN_F5R1_FB25_Msk
/** @brief Bit position of the `CAN_F5R1_FB26` field @def CAN_F5R1_FB26_Pos */
#define CAN_F5R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB26` field @def CAN_F5R1_FB26_Msk */
#define CAN_F5R1_FB26_Msk		REG_BIT_MASK(CAN_F5R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F5R1_FB26 */
#define CAN_F5R1_FB26			CAN_F5R1_FB26_Msk
/** @brief Bit position of the `CAN_F5R1_FB27` field @def CAN_F5R1_FB27_Pos */
#define CAN_F5R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB27` field @def CAN_F5R1_FB27_Msk */
#define CAN_F5R1_FB27_Msk		REG_BIT_MASK(CAN_F5R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F5R1_FB27 */
#define CAN_F5R1_FB27			CAN_F5R1_FB27_Msk
/** @brief Bit position of the `CAN_F5R1_FB28` field @def CAN_F5R1_FB28_Pos */
#define CAN_F5R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB28` field @def CAN_F5R1_FB28_Msk */
#define CAN_F5R1_FB28_Msk		REG_BIT_MASK(CAN_F5R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F5R1_FB28 */
#define CAN_F5R1_FB28			CAN_F5R1_FB28_Msk
/** @brief Bit position of the `CAN_F5R1_FB29` field @def CAN_F5R1_FB29_Pos */
#define CAN_F5R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB29` field @def CAN_F5R1_FB29_Msk */
#define CAN_F5R1_FB29_Msk		REG_BIT_MASK(CAN_F5R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F5R1_FB29 */
#define CAN_F5R1_FB29			CAN_F5R1_FB29_Msk
/** @brief Bit position of the `CAN_F5R1_FB30` field @def CAN_F5R1_FB30_Pos */
#define CAN_F5R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB30` field @def CAN_F5R1_FB30_Msk */
#define CAN_F5R1_FB30_Msk		REG_BIT_MASK(CAN_F5R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F5R1_FB30 */
#define CAN_F5R1_FB30			CAN_F5R1_FB30_Msk
/** @brief Bit position of the `CAN_F5R1_FB31` field @def CAN_F5R1_FB31_Pos */
#define CAN_F5R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F5R1_FB31` field @def CAN_F5R1_FB31_Msk */
#define CAN_F5R1_FB31_Msk		REG_BIT_MASK(CAN_F5R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F5R1_FB31 */
#define CAN_F5R1_FB31			CAN_F5R1_FB31_Msk

// ---------------------------------- CAN_F6R1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F6R1_FB0` field @def CAN_F6R1_FB0_Pos */
#define CAN_F6R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB0` field @def CAN_F6R1_FB0_Msk */
#define CAN_F6R1_FB0_Msk		REG_BIT_MASK(CAN_F6R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F6R1_FB0 */
#define CAN_F6R1_FB0			CAN_F6R1_FB0_Msk
/** @brief Bit position of the `CAN_F6R1_FB1` field @def CAN_F6R1_FB1_Pos */
#define CAN_F6R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB1` field @def CAN_F6R1_FB1_Msk */
#define CAN_F6R1_FB1_Msk		REG_BIT_MASK(CAN_F6R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F6R1_FB1 */
#define CAN_F6R1_FB1			CAN_F6R1_FB1_Msk
/** @brief Bit position of the `CAN_F6R1_FB2` field @def CAN_F6R1_FB2_Pos */
#define CAN_F6R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB2` field @def CAN_F6R1_FB2_Msk */
#define CAN_F6R1_FB2_Msk		REG_BIT_MASK(CAN_F6R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F6R1_FB2 */
#define CAN_F6R1_FB2			CAN_F6R1_FB2_Msk
/** @brief Bit position of the `CAN_F6R1_FB3` field @def CAN_F6R1_FB3_Pos */
#define CAN_F6R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB3` field @def CAN_F6R1_FB3_Msk */
#define CAN_F6R1_FB3_Msk		REG_BIT_MASK(CAN_F6R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F6R1_FB3 */
#define CAN_F6R1_FB3			CAN_F6R1_FB3_Msk
/** @brief Bit position of the `CAN_F6R1_FB4` field @def CAN_F6R1_FB4_Pos */
#define CAN_F6R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB4` field @def CAN_F6R1_FB4_Msk */
#define CAN_F6R1_FB4_Msk		REG_BIT_MASK(CAN_F6R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F6R1_FB4 */
#define CAN_F6R1_FB4			CAN_F6R1_FB4_Msk
/** @brief Bit position of the `CAN_F6R1_FB5` field @def CAN_F6R1_FB5_Pos */
#define CAN_F6R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB5` field @def CAN_F6R1_FB5_Msk */
#define CAN_F6R1_FB5_Msk		REG_BIT_MASK(CAN_F6R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F6R1_FB5 */
#define CAN_F6R1_FB5			CAN_F6R1_FB5_Msk
/** @brief Bit position of the `CAN_F6R1_FB6` field @def CAN_F6R1_FB6_Pos */
#define CAN_F6R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB6` field @def CAN_F6R1_FB6_Msk */
#define CAN_F6R1_FB6_Msk		REG_BIT_MASK(CAN_F6R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F6R1_FB6 */
#define CAN_F6R1_FB6			CAN_F6R1_FB6_Msk
/** @brief Bit position of the `CAN_F6R1_FB7` field @def CAN_F6R1_FB7_Pos */
#define CAN_F6R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB7` field @def CAN_F6R1_FB7_Msk */
#define CAN_F6R1_FB7_Msk		REG_BIT_MASK(CAN_F6R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F6R1_FB7 */
#define CAN_F6R1_FB7			CAN_F6R1_FB7_Msk
/** @brief Bit position of the `CAN_F6R1_FB8` field @def CAN_F6R1_FB8_Pos */
#define CAN_F6R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB8` field @def CAN_F6R1_FB8_Msk */
#define CAN_F6R1_FB8_Msk		REG_BIT_MASK(CAN_F6R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F6R1_FB8 */
#define CAN_F6R1_FB8			CAN_F6R1_FB8_Msk
/** @brief Bit position of the `CAN_F6R1_FB9` field @def CAN_F6R1_FB9_Pos */
#define CAN_F6R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB9` field @def CAN_F6R1_FB9_Msk */
#define CAN_F6R1_FB9_Msk		REG_BIT_MASK(CAN_F6R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F6R1_FB9 */
#define CAN_F6R1_FB9			CAN_F6R1_FB9_Msk
/** @brief Bit position of the `CAN_F6R1_FB10` field @def CAN_F6R1_FB10_Pos */
#define CAN_F6R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB10` field @def CAN_F6R1_FB10_Msk */
#define CAN_F6R1_FB10_Msk		REG_BIT_MASK(CAN_F6R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F6R1_FB10 */
#define CAN_F6R1_FB10			CAN_F6R1_FB10_Msk
/** @brief Bit position of the `CAN_F6R1_FB11` field @def CAN_F6R1_FB11_Pos */
#define CAN_F6R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB11` field @def CAN_F6R1_FB11_Msk */
#define CAN_F6R1_FB11_Msk		REG_BIT_MASK(CAN_F6R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F6R1_FB11 */
#define CAN_F6R1_FB11			CAN_F6R1_FB11_Msk
/** @brief Bit position of the `CAN_F6R1_FB12` field @def CAN_F6R1_FB12_Pos */
#define CAN_F6R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB12` field @def CAN_F6R1_FB12_Msk */
#define CAN_F6R1_FB12_Msk		REG_BIT_MASK(CAN_F6R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F6R1_FB12 */
#define CAN_F6R1_FB12			CAN_F6R1_FB12_Msk
/** @brief Bit position of the `CAN_F6R1_FB13` field @def CAN_F6R1_FB13_Pos */
#define CAN_F6R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB13` field @def CAN_F6R1_FB13_Msk */
#define CAN_F6R1_FB13_Msk		REG_BIT_MASK(CAN_F6R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F6R1_FB13 */
#define CAN_F6R1_FB13			CAN_F6R1_FB13_Msk
/** @brief Bit position of the `CAN_F6R1_FB14` field @def CAN_F6R1_FB14_Pos */
#define CAN_F6R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB14` field @def CAN_F6R1_FB14_Msk */
#define CAN_F6R1_FB14_Msk		REG_BIT_MASK(CAN_F6R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F6R1_FB14 */
#define CAN_F6R1_FB14			CAN_F6R1_FB14_Msk
/** @brief Bit position of the `CAN_F6R1_FB15` field @def CAN_F6R1_FB15_Pos */
#define CAN_F6R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB15` field @def CAN_F6R1_FB15_Msk */
#define CAN_F6R1_FB15_Msk		REG_BIT_MASK(CAN_F6R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F6R1_FB15 */
#define CAN_F6R1_FB15			CAN_F6R1_FB15_Msk
/** @brief Bit position of the `CAN_F6R1_FB16` field @def CAN_F6R1_FB16_Pos */
#define CAN_F6R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB16` field @def CAN_F6R1_FB16_Msk */
#define CAN_F6R1_FB16_Msk		REG_BIT_MASK(CAN_F6R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F6R1_FB16 */
#define CAN_F6R1_FB16			CAN_F6R1_FB16_Msk
/** @brief Bit position of the `CAN_F6R1_FB17` field @def CAN_F6R1_FB17_Pos */
#define CAN_F6R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB17` field @def CAN_F6R1_FB17_Msk */
#define CAN_F6R1_FB17_Msk		REG_BIT_MASK(CAN_F6R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F6R1_FB17 */
#define CAN_F6R1_FB17			CAN_F6R1_FB17_Msk
/** @brief Bit position of the `CAN_F6R1_FB18` field @def CAN_F6R1_FB18_Pos */
#define CAN_F6R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB18` field @def CAN_F6R1_FB18_Msk */
#define CAN_F6R1_FB18_Msk		REG_BIT_MASK(CAN_F6R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F6R1_FB18 */
#define CAN_F6R1_FB18			CAN_F6R1_FB18_Msk
/** @brief Bit position of the `CAN_F6R1_FB19` field @def CAN_F6R1_FB19_Pos */
#define CAN_F6R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB19` field @def CAN_F6R1_FB19_Msk */
#define CAN_F6R1_FB19_Msk		REG_BIT_MASK(CAN_F6R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F6R1_FB19 */
#define CAN_F6R1_FB19			CAN_F6R1_FB19_Msk
/** @brief Bit position of the `CAN_F6R1_FB20` field @def CAN_F6R1_FB20_Pos */
#define CAN_F6R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB20` field @def CAN_F6R1_FB20_Msk */
#define CAN_F6R1_FB20_Msk		REG_BIT_MASK(CAN_F6R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F6R1_FB20 */
#define CAN_F6R1_FB20			CAN_F6R1_FB20_Msk
/** @brief Bit position of the `CAN_F6R1_FB21` field @def CAN_F6R1_FB21_Pos */
#define CAN_F6R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB21` field @def CAN_F6R1_FB21_Msk */
#define CAN_F6R1_FB21_Msk		REG_BIT_MASK(CAN_F6R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F6R1_FB21 */
#define CAN_F6R1_FB21			CAN_F6R1_FB21_Msk
/** @brief Bit position of the `CAN_F6R1_FB22` field @def CAN_F6R1_FB22_Pos */
#define CAN_F6R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB22` field @def CAN_F6R1_FB22_Msk */
#define CAN_F6R1_FB22_Msk		REG_BIT_MASK(CAN_F6R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F6R1_FB22 */
#define CAN_F6R1_FB22			CAN_F6R1_FB22_Msk
/** @brief Bit position of the `CAN_F6R1_FB23` field @def CAN_F6R1_FB23_Pos */
#define CAN_F6R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB23` field @def CAN_F6R1_FB23_Msk */
#define CAN_F6R1_FB23_Msk		REG_BIT_MASK(CAN_F6R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F6R1_FB23 */
#define CAN_F6R1_FB23			CAN_F6R1_FB23_Msk
/** @brief Bit position of the `CAN_F6R1_FB24` field @def CAN_F6R1_FB24_Pos */
#define CAN_F6R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB24` field @def CAN_F6R1_FB24_Msk */
#define CAN_F6R1_FB24_Msk		REG_BIT_MASK(CAN_F6R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F6R1_FB24 */
#define CAN_F6R1_FB24			CAN_F6R1_FB24_Msk
/** @brief Bit position of the `CAN_F6R1_FB25` field @def CAN_F6R1_FB25_Pos */
#define CAN_F6R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB25` field @def CAN_F6R1_FB25_Msk */
#define CAN_F6R1_FB25_Msk		REG_BIT_MASK(CAN_F6R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F6R1_FB25 */
#define CAN_F6R1_FB25			CAN_F6R1_FB25_Msk
/** @brief Bit position of the `CAN_F6R1_FB26` field @def CAN_F6R1_FB26_Pos */
#define CAN_F6R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB26` field @def CAN_F6R1_FB26_Msk */
#define CAN_F6R1_FB26_Msk		REG_BIT_MASK(CAN_F6R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F6R1_FB26 */
#define CAN_F6R1_FB26			CAN_F6R1_FB26_Msk
/** @brief Bit position of the `CAN_F6R1_FB27` field @def CAN_F6R1_FB27_Pos */
#define CAN_F6R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB27` field @def CAN_F6R1_FB27_Msk */
#define CAN_F6R1_FB27_Msk		REG_BIT_MASK(CAN_F6R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F6R1_FB27 */
#define CAN_F6R1_FB27			CAN_F6R1_FB27_Msk
/** @brief Bit position of the `CAN_F6R1_FB28` field @def CAN_F6R1_FB28_Pos */
#define CAN_F6R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB28` field @def CAN_F6R1_FB28_Msk */
#define CAN_F6R1_FB28_Msk		REG_BIT_MASK(CAN_F6R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F6R1_FB28 */
#define CAN_F6R1_FB28			CAN_F6R1_FB28_Msk
/** @brief Bit position of the `CAN_F6R1_FB29` field @def CAN_F6R1_FB29_Pos */
#define CAN_F6R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB29` field @def CAN_F6R1_FB29_Msk */
#define CAN_F6R1_FB29_Msk		REG_BIT_MASK(CAN_F6R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F6R1_FB29 */
#define CAN_F6R1_FB29			CAN_F6R1_FB29_Msk
/** @brief Bit position of the `CAN_F6R1_FB30` field @def CAN_F6R1_FB30_Pos */
#define CAN_F6R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB30` field @def CAN_F6R1_FB30_Msk */
#define CAN_F6R1_FB30_Msk		REG_BIT_MASK(CAN_F6R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F6R1_FB30 */
#define CAN_F6R1_FB30			CAN_F6R1_FB30_Msk
/** @brief Bit position of the `CAN_F6R1_FB31` field @def CAN_F6R1_FB31_Pos */
#define CAN_F6R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F6R1_FB31` field @def CAN_F6R1_FB31_Msk */
#define CAN_F6R1_FB31_Msk		REG_BIT_MASK(CAN_F6R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F6R1_FB31 */
#define CAN_F6R1_FB31			CAN_F6R1_FB31_Msk

// ---------------------------------- CAN_F7R1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F7R1_FB0` field @def CAN_F7R1_FB0_Pos */
#define CAN_F7R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB0` field @def CAN_F7R1_FB0_Msk */
#define CAN_F7R1_FB0_Msk		REG_BIT_MASK(CAN_F7R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F7R1_FB0 */
#define CAN_F7R1_FB0			CAN_F7R1_FB0_Msk
/** @brief Bit position of the `CAN_F7R1_FB1` field @def CAN_F7R1_FB1_Pos */
#define CAN_F7R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB1` field @def CAN_F7R1_FB1_Msk */
#define CAN_F7R1_FB1_Msk		REG_BIT_MASK(CAN_F7R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F7R1_FB1 */
#define CAN_F7R1_FB1			CAN_F7R1_FB1_Msk
/** @brief Bit position of the `CAN_F7R1_FB2` field @def CAN_F7R1_FB2_Pos */
#define CAN_F7R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB2` field @def CAN_F7R1_FB2_Msk */
#define CAN_F7R1_FB2_Msk		REG_BIT_MASK(CAN_F7R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F7R1_FB2 */
#define CAN_F7R1_FB2			CAN_F7R1_FB2_Msk
/** @brief Bit position of the `CAN_F7R1_FB3` field @def CAN_F7R1_FB3_Pos */
#define CAN_F7R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB3` field @def CAN_F7R1_FB3_Msk */
#define CAN_F7R1_FB3_Msk		REG_BIT_MASK(CAN_F7R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F7R1_FB3 */
#define CAN_F7R1_FB3			CAN_F7R1_FB3_Msk
/** @brief Bit position of the `CAN_F7R1_FB4` field @def CAN_F7R1_FB4_Pos */
#define CAN_F7R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB4` field @def CAN_F7R1_FB4_Msk */
#define CAN_F7R1_FB4_Msk		REG_BIT_MASK(CAN_F7R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F7R1_FB4 */
#define CAN_F7R1_FB4			CAN_F7R1_FB4_Msk
/** @brief Bit position of the `CAN_F7R1_FB5` field @def CAN_F7R1_FB5_Pos */
#define CAN_F7R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB5` field @def CAN_F7R1_FB5_Msk */
#define CAN_F7R1_FB5_Msk		REG_BIT_MASK(CAN_F7R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F7R1_FB5 */
#define CAN_F7R1_FB5			CAN_F7R1_FB5_Msk
/** @brief Bit position of the `CAN_F7R1_FB6` field @def CAN_F7R1_FB6_Pos */
#define CAN_F7R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB6` field @def CAN_F7R1_FB6_Msk */
#define CAN_F7R1_FB6_Msk		REG_BIT_MASK(CAN_F7R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F7R1_FB6 */
#define CAN_F7R1_FB6			CAN_F7R1_FB6_Msk
/** @brief Bit position of the `CAN_F7R1_FB7` field @def CAN_F7R1_FB7_Pos */
#define CAN_F7R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB7` field @def CAN_F7R1_FB7_Msk */
#define CAN_F7R1_FB7_Msk		REG_BIT_MASK(CAN_F7R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F7R1_FB7 */
#define CAN_F7R1_FB7			CAN_F7R1_FB7_Msk
/** @brief Bit position of the `CAN_F7R1_FB8` field @def CAN_F7R1_FB8_Pos */
#define CAN_F7R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB8` field @def CAN_F7R1_FB8_Msk */
#define CAN_F7R1_FB8_Msk		REG_BIT_MASK(CAN_F7R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F7R1_FB8 */
#define CAN_F7R1_FB8			CAN_F7R1_FB8_Msk
/** @brief Bit position of the `CAN_F7R1_FB9` field @def CAN_F7R1_FB9_Pos */
#define CAN_F7R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB9` field @def CAN_F7R1_FB9_Msk */
#define CAN_F7R1_FB9_Msk		REG_BIT_MASK(CAN_F7R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F7R1_FB9 */
#define CAN_F7R1_FB9			CAN_F7R1_FB9_Msk
/** @brief Bit position of the `CAN_F7R1_FB10` field @def CAN_F7R1_FB10_Pos */
#define CAN_F7R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB10` field @def CAN_F7R1_FB10_Msk */
#define CAN_F7R1_FB10_Msk		REG_BIT_MASK(CAN_F7R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F7R1_FB10 */
#define CAN_F7R1_FB10			CAN_F7R1_FB10_Msk
/** @brief Bit position of the `CAN_F7R1_FB11` field @def CAN_F7R1_FB11_Pos */
#define CAN_F7R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB11` field @def CAN_F7R1_FB11_Msk */
#define CAN_F7R1_FB11_Msk		REG_BIT_MASK(CAN_F7R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F7R1_FB11 */
#define CAN_F7R1_FB11			CAN_F7R1_FB11_Msk
/** @brief Bit position of the `CAN_F7R1_FB12` field @def CAN_F7R1_FB12_Pos */
#define CAN_F7R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB12` field @def CAN_F7R1_FB12_Msk */
#define CAN_F7R1_FB12_Msk		REG_BIT_MASK(CAN_F7R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F7R1_FB12 */
#define CAN_F7R1_FB12			CAN_F7R1_FB12_Msk
/** @brief Bit position of the `CAN_F7R1_FB13` field @def CAN_F7R1_FB13_Pos */
#define CAN_F7R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB13` field @def CAN_F7R1_FB13_Msk */
#define CAN_F7R1_FB13_Msk		REG_BIT_MASK(CAN_F7R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F7R1_FB13 */
#define CAN_F7R1_FB13			CAN_F7R1_FB13_Msk
/** @brief Bit position of the `CAN_F7R1_FB14` field @def CAN_F7R1_FB14_Pos */
#define CAN_F7R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB14` field @def CAN_F7R1_FB14_Msk */
#define CAN_F7R1_FB14_Msk		REG_BIT_MASK(CAN_F7R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F7R1_FB14 */
#define CAN_F7R1_FB14			CAN_F7R1_FB14_Msk
/** @brief Bit position of the `CAN_F7R1_FB15` field @def CAN_F7R1_FB15_Pos */
#define CAN_F7R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB15` field @def CAN_F7R1_FB15_Msk */
#define CAN_F7R1_FB15_Msk		REG_BIT_MASK(CAN_F7R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F7R1_FB15 */
#define CAN_F7R1_FB15			CAN_F7R1_FB15_Msk
/** @brief Bit position of the `CAN_F7R1_FB16` field @def CAN_F7R1_FB16_Pos */
#define CAN_F7R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB16` field @def CAN_F7R1_FB16_Msk */
#define CAN_F7R1_FB16_Msk		REG_BIT_MASK(CAN_F7R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F7R1_FB16 */
#define CAN_F7R1_FB16			CAN_F7R1_FB16_Msk
/** @brief Bit position of the `CAN_F7R1_FB17` field @def CAN_F7R1_FB17_Pos */
#define CAN_F7R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB17` field @def CAN_F7R1_FB17_Msk */
#define CAN_F7R1_FB17_Msk		REG_BIT_MASK(CAN_F7R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F7R1_FB17 */
#define CAN_F7R1_FB17			CAN_F7R1_FB17_Msk
/** @brief Bit position of the `CAN_F7R1_FB18` field @def CAN_F7R1_FB18_Pos */
#define CAN_F7R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB18` field @def CAN_F7R1_FB18_Msk */
#define CAN_F7R1_FB18_Msk		REG_BIT_MASK(CAN_F7R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F7R1_FB18 */
#define CAN_F7R1_FB18			CAN_F7R1_FB18_Msk
/** @brief Bit position of the `CAN_F7R1_FB19` field @def CAN_F7R1_FB19_Pos */
#define CAN_F7R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB19` field @def CAN_F7R1_FB19_Msk */
#define CAN_F7R1_FB19_Msk		REG_BIT_MASK(CAN_F7R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F7R1_FB19 */
#define CAN_F7R1_FB19			CAN_F7R1_FB19_Msk
/** @brief Bit position of the `CAN_F7R1_FB20` field @def CAN_F7R1_FB20_Pos */
#define CAN_F7R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB20` field @def CAN_F7R1_FB20_Msk */
#define CAN_F7R1_FB20_Msk		REG_BIT_MASK(CAN_F7R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F7R1_FB20 */
#define CAN_F7R1_FB20			CAN_F7R1_FB20_Msk
/** @brief Bit position of the `CAN_F7R1_FB21` field @def CAN_F7R1_FB21_Pos */
#define CAN_F7R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB21` field @def CAN_F7R1_FB21_Msk */
#define CAN_F7R1_FB21_Msk		REG_BIT_MASK(CAN_F7R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F7R1_FB21 */
#define CAN_F7R1_FB21			CAN_F7R1_FB21_Msk
/** @brief Bit position of the `CAN_F7R1_FB22` field @def CAN_F7R1_FB22_Pos */
#define CAN_F7R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB22` field @def CAN_F7R1_FB22_Msk */
#define CAN_F7R1_FB22_Msk		REG_BIT_MASK(CAN_F7R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F7R1_FB22 */
#define CAN_F7R1_FB22			CAN_F7R1_FB22_Msk
/** @brief Bit position of the `CAN_F7R1_FB23` field @def CAN_F7R1_FB23_Pos */
#define CAN_F7R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB23` field @def CAN_F7R1_FB23_Msk */
#define CAN_F7R1_FB23_Msk		REG_BIT_MASK(CAN_F7R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F7R1_FB23 */
#define CAN_F7R1_FB23			CAN_F7R1_FB23_Msk
/** @brief Bit position of the `CAN_F7R1_FB24` field @def CAN_F7R1_FB24_Pos */
#define CAN_F7R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB24` field @def CAN_F7R1_FB24_Msk */
#define CAN_F7R1_FB24_Msk		REG_BIT_MASK(CAN_F7R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F7R1_FB24 */
#define CAN_F7R1_FB24			CAN_F7R1_FB24_Msk
/** @brief Bit position of the `CAN_F7R1_FB25` field @def CAN_F7R1_FB25_Pos */
#define CAN_F7R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB25` field @def CAN_F7R1_FB25_Msk */
#define CAN_F7R1_FB25_Msk		REG_BIT_MASK(CAN_F7R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F7R1_FB25 */
#define CAN_F7R1_FB25			CAN_F7R1_FB25_Msk
/** @brief Bit position of the `CAN_F7R1_FB26` field @def CAN_F7R1_FB26_Pos */
#define CAN_F7R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB26` field @def CAN_F7R1_FB26_Msk */
#define CAN_F7R1_FB26_Msk		REG_BIT_MASK(CAN_F7R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F7R1_FB26 */
#define CAN_F7R1_FB26			CAN_F7R1_FB26_Msk
/** @brief Bit position of the `CAN_F7R1_FB27` field @def CAN_F7R1_FB27_Pos */
#define CAN_F7R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB27` field @def CAN_F7R1_FB27_Msk */
#define CAN_F7R1_FB27_Msk		REG_BIT_MASK(CAN_F7R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F7R1_FB27 */
#define CAN_F7R1_FB27			CAN_F7R1_FB27_Msk
/** @brief Bit position of the `CAN_F7R1_FB28` field @def CAN_F7R1_FB28_Pos */
#define CAN_F7R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB28` field @def CAN_F7R1_FB28_Msk */
#define CAN_F7R1_FB28_Msk		REG_BIT_MASK(CAN_F7R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F7R1_FB28 */
#define CAN_F7R1_FB28			CAN_F7R1_FB28_Msk
/** @brief Bit position of the `CAN_F7R1_FB29` field @def CAN_F7R1_FB29_Pos */
#define CAN_F7R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB29` field @def CAN_F7R1_FB29_Msk */
#define CAN_F7R1_FB29_Msk		REG_BIT_MASK(CAN_F7R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F7R1_FB29 */
#define CAN_F7R1_FB29			CAN_F7R1_FB29_Msk
/** @brief Bit position of the `CAN_F7R1_FB30` field @def CAN_F7R1_FB30_Pos */
#define CAN_F7R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB30` field @def CAN_F7R1_FB30_Msk */
#define CAN_F7R1_FB30_Msk		REG_BIT_MASK(CAN_F7R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F7R1_FB30 */
#define CAN_F7R1_FB30			CAN_F7R1_FB30_Msk
/** @brief Bit position of the `CAN_F7R1_FB31` field @def CAN_F7R1_FB31_Pos */
#define CAN_F7R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F7R1_FB31` field @def CAN_F7R1_FB31_Msk */
#define CAN_F7R1_FB31_Msk		REG_BIT_MASK(CAN_F7R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F7R1_FB31 */
#define CAN_F7R1_FB31			CAN_F7R1_FB31_Msk

// ---------------------------------- CAN_F8R1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F8R1_FB0` field @def CAN_F8R1_FB0_Pos */
#define CAN_F8R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB0` field @def CAN_F8R1_FB0_Msk */
#define CAN_F8R1_FB0_Msk		REG_BIT_MASK(CAN_F8R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F8R1_FB0 */
#define CAN_F8R1_FB0			CAN_F8R1_FB0_Msk
/** @brief Bit position of the `CAN_F8R1_FB1` field @def CAN_F8R1_FB1_Pos */
#define CAN_F8R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB1` field @def CAN_F8R1_FB1_Msk */
#define CAN_F8R1_FB1_Msk		REG_BIT_MASK(CAN_F8R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F8R1_FB1 */
#define CAN_F8R1_FB1			CAN_F8R1_FB1_Msk
/** @brief Bit position of the `CAN_F8R1_FB2` field @def CAN_F8R1_FB2_Pos */
#define CAN_F8R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB2` field @def CAN_F8R1_FB2_Msk */
#define CAN_F8R1_FB2_Msk		REG_BIT_MASK(CAN_F8R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F8R1_FB2 */
#define CAN_F8R1_FB2			CAN_F8R1_FB2_Msk
/** @brief Bit position of the `CAN_F8R1_FB3` field @def CAN_F8R1_FB3_Pos */
#define CAN_F8R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB3` field @def CAN_F8R1_FB3_Msk */
#define CAN_F8R1_FB3_Msk		REG_BIT_MASK(CAN_F8R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F8R1_FB3 */
#define CAN_F8R1_FB3			CAN_F8R1_FB3_Msk
/** @brief Bit position of the `CAN_F8R1_FB4` field @def CAN_F8R1_FB4_Pos */
#define CAN_F8R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB4` field @def CAN_F8R1_FB4_Msk */
#define CAN_F8R1_FB4_Msk		REG_BIT_MASK(CAN_F8R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F8R1_FB4 */
#define CAN_F8R1_FB4			CAN_F8R1_FB4_Msk
/** @brief Bit position of the `CAN_F8R1_FB5` field @def CAN_F8R1_FB5_Pos */
#define CAN_F8R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB5` field @def CAN_F8R1_FB5_Msk */
#define CAN_F8R1_FB5_Msk		REG_BIT_MASK(CAN_F8R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F8R1_FB5 */
#define CAN_F8R1_FB5			CAN_F8R1_FB5_Msk
/** @brief Bit position of the `CAN_F8R1_FB6` field @def CAN_F8R1_FB6_Pos */
#define CAN_F8R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB6` field @def CAN_F8R1_FB6_Msk */
#define CAN_F8R1_FB6_Msk		REG_BIT_MASK(CAN_F8R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F8R1_FB6 */
#define CAN_F8R1_FB6			CAN_F8R1_FB6_Msk
/** @brief Bit position of the `CAN_F8R1_FB7` field @def CAN_F8R1_FB7_Pos */
#define CAN_F8R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB7` field @def CAN_F8R1_FB7_Msk */
#define CAN_F8R1_FB7_Msk		REG_BIT_MASK(CAN_F8R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F8R1_FB7 */
#define CAN_F8R1_FB7			CAN_F8R1_FB7_Msk
/** @brief Bit position of the `CAN_F8R1_FB8` field @def CAN_F8R1_FB8_Pos */
#define CAN_F8R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB8` field @def CAN_F8R1_FB8_Msk */
#define CAN_F8R1_FB8_Msk		REG_BIT_MASK(CAN_F8R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F8R1_FB8 */
#define CAN_F8R1_FB8			CAN_F8R1_FB8_Msk
/** @brief Bit position of the `CAN_F8R1_FB9` field @def CAN_F8R1_FB9_Pos */
#define CAN_F8R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB9` field @def CAN_F8R1_FB9_Msk */
#define CAN_F8R1_FB9_Msk		REG_BIT_MASK(CAN_F8R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F8R1_FB9 */
#define CAN_F8R1_FB9			CAN_F8R1_FB9_Msk
/** @brief Bit position of the `CAN_F8R1_FB10` field @def CAN_F8R1_FB10_Pos */
#define CAN_F8R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB10` field @def CAN_F8R1_FB10_Msk */
#define CAN_F8R1_FB10_Msk		REG_BIT_MASK(CAN_F8R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F8R1_FB10 */
#define CAN_F8R1_FB10			CAN_F8R1_FB10_Msk
/** @brief Bit position of the `CAN_F8R1_FB11` field @def CAN_F8R1_FB11_Pos */
#define CAN_F8R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB11` field @def CAN_F8R1_FB11_Msk */
#define CAN_F8R1_FB11_Msk		REG_BIT_MASK(CAN_F8R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F8R1_FB11 */
#define CAN_F8R1_FB11			CAN_F8R1_FB11_Msk
/** @brief Bit position of the `CAN_F8R1_FB12` field @def CAN_F8R1_FB12_Pos */
#define CAN_F8R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB12` field @def CAN_F8R1_FB12_Msk */
#define CAN_F8R1_FB12_Msk		REG_BIT_MASK(CAN_F8R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F8R1_FB12 */
#define CAN_F8R1_FB12			CAN_F8R1_FB12_Msk
/** @brief Bit position of the `CAN_F8R1_FB13` field @def CAN_F8R1_FB13_Pos */
#define CAN_F8R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB13` field @def CAN_F8R1_FB13_Msk */
#define CAN_F8R1_FB13_Msk		REG_BIT_MASK(CAN_F8R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F8R1_FB13 */
#define CAN_F8R1_FB13			CAN_F8R1_FB13_Msk
/** @brief Bit position of the `CAN_F8R1_FB14` field @def CAN_F8R1_FB14_Pos */
#define CAN_F8R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB14` field @def CAN_F8R1_FB14_Msk */
#define CAN_F8R1_FB14_Msk		REG_BIT_MASK(CAN_F8R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F8R1_FB14 */
#define CAN_F8R1_FB14			CAN_F8R1_FB14_Msk
/** @brief Bit position of the `CAN_F8R1_FB15` field @def CAN_F8R1_FB15_Pos */
#define CAN_F8R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB15` field @def CAN_F8R1_FB15_Msk */
#define CAN_F8R1_FB15_Msk		REG_BIT_MASK(CAN_F8R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F8R1_FB15 */
#define CAN_F8R1_FB15			CAN_F8R1_FB15_Msk
/** @brief Bit position of the `CAN_F8R1_FB16` field @def CAN_F8R1_FB16_Pos */
#define CAN_F8R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB16` field @def CAN_F8R1_FB16_Msk */
#define CAN_F8R1_FB16_Msk		REG_BIT_MASK(CAN_F8R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F8R1_FB16 */
#define CAN_F8R1_FB16			CAN_F8R1_FB16_Msk
/** @brief Bit position of the `CAN_F8R1_FB17` field @def CAN_F8R1_FB17_Pos */
#define CAN_F8R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB17` field @def CAN_F8R1_FB17_Msk */
#define CAN_F8R1_FB17_Msk		REG_BIT_MASK(CAN_F8R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F8R1_FB17 */
#define CAN_F8R1_FB17			CAN_F8R1_FB17_Msk
/** @brief Bit position of the `CAN_F8R1_FB18` field @def CAN_F8R1_FB18_Pos */
#define CAN_F8R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB18` field @def CAN_F8R1_FB18_Msk */
#define CAN_F8R1_FB18_Msk		REG_BIT_MASK(CAN_F8R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F8R1_FB18 */
#define CAN_F8R1_FB18			CAN_F8R1_FB18_Msk
/** @brief Bit position of the `CAN_F8R1_FB19` field @def CAN_F8R1_FB19_Pos */
#define CAN_F8R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB19` field @def CAN_F8R1_FB19_Msk */
#define CAN_F8R1_FB19_Msk		REG_BIT_MASK(CAN_F8R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F8R1_FB19 */
#define CAN_F8R1_FB19			CAN_F8R1_FB19_Msk
/** @brief Bit position of the `CAN_F8R1_FB20` field @def CAN_F8R1_FB20_Pos */
#define CAN_F8R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB20` field @def CAN_F8R1_FB20_Msk */
#define CAN_F8R1_FB20_Msk		REG_BIT_MASK(CAN_F8R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F8R1_FB20 */
#define CAN_F8R1_FB20			CAN_F8R1_FB20_Msk
/** @brief Bit position of the `CAN_F8R1_FB21` field @def CAN_F8R1_FB21_Pos */
#define CAN_F8R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB21` field @def CAN_F8R1_FB21_Msk */
#define CAN_F8R1_FB21_Msk		REG_BIT_MASK(CAN_F8R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F8R1_FB21 */
#define CAN_F8R1_FB21			CAN_F8R1_FB21_Msk
/** @brief Bit position of the `CAN_F8R1_FB22` field @def CAN_F8R1_FB22_Pos */
#define CAN_F8R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB22` field @def CAN_F8R1_FB22_Msk */
#define CAN_F8R1_FB22_Msk		REG_BIT_MASK(CAN_F8R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F8R1_FB22 */
#define CAN_F8R1_FB22			CAN_F8R1_FB22_Msk
/** @brief Bit position of the `CAN_F8R1_FB23` field @def CAN_F8R1_FB23_Pos */
#define CAN_F8R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB23` field @def CAN_F8R1_FB23_Msk */
#define CAN_F8R1_FB23_Msk		REG_BIT_MASK(CAN_F8R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F8R1_FB23 */
#define CAN_F8R1_FB23			CAN_F8R1_FB23_Msk
/** @brief Bit position of the `CAN_F8R1_FB24` field @def CAN_F8R1_FB24_Pos */
#define CAN_F8R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB24` field @def CAN_F8R1_FB24_Msk */
#define CAN_F8R1_FB24_Msk		REG_BIT_MASK(CAN_F8R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F8R1_FB24 */
#define CAN_F8R1_FB24			CAN_F8R1_FB24_Msk
/** @brief Bit position of the `CAN_F8R1_FB25` field @def CAN_F8R1_FB25_Pos */
#define CAN_F8R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB25` field @def CAN_F8R1_FB25_Msk */
#define CAN_F8R1_FB25_Msk		REG_BIT_MASK(CAN_F8R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F8R1_FB25 */
#define CAN_F8R1_FB25			CAN_F8R1_FB25_Msk
/** @brief Bit position of the `CAN_F8R1_FB26` field @def CAN_F8R1_FB26_Pos */
#define CAN_F8R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB26` field @def CAN_F8R1_FB26_Msk */
#define CAN_F8R1_FB26_Msk		REG_BIT_MASK(CAN_F8R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F8R1_FB26 */
#define CAN_F8R1_FB26			CAN_F8R1_FB26_Msk
/** @brief Bit position of the `CAN_F8R1_FB27` field @def CAN_F8R1_FB27_Pos */
#define CAN_F8R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB27` field @def CAN_F8R1_FB27_Msk */
#define CAN_F8R1_FB27_Msk		REG_BIT_MASK(CAN_F8R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F8R1_FB27 */
#define CAN_F8R1_FB27			CAN_F8R1_FB27_Msk
/** @brief Bit position of the `CAN_F8R1_FB28` field @def CAN_F8R1_FB28_Pos */
#define CAN_F8R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB28` field @def CAN_F8R1_FB28_Msk */
#define CAN_F8R1_FB28_Msk		REG_BIT_MASK(CAN_F8R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F8R1_FB28 */
#define CAN_F8R1_FB28			CAN_F8R1_FB28_Msk
/** @brief Bit position of the `CAN_F8R1_FB29` field @def CAN_F8R1_FB29_Pos */
#define CAN_F8R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB29` field @def CAN_F8R1_FB29_Msk */
#define CAN_F8R1_FB29_Msk		REG_BIT_MASK(CAN_F8R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F8R1_FB29 */
#define CAN_F8R1_FB29			CAN_F8R1_FB29_Msk
/** @brief Bit position of the `CAN_F8R1_FB30` field @def CAN_F8R1_FB30_Pos */
#define CAN_F8R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB30` field @def CAN_F8R1_FB30_Msk */
#define CAN_F8R1_FB30_Msk		REG_BIT_MASK(CAN_F8R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F8R1_FB30 */
#define CAN_F8R1_FB30			CAN_F8R1_FB30_Msk
/** @brief Bit position of the `CAN_F8R1_FB31` field @def CAN_F8R1_FB31_Pos */
#define CAN_F8R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F8R1_FB31` field @def CAN_F8R1_FB31_Msk */
#define CAN_F8R1_FB31_Msk		REG_BIT_MASK(CAN_F8R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F8R1_FB31 */
#define CAN_F8R1_FB31			CAN_F8R1_FB31_Msk

// ---------------------------------- CAN_F9R1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F9R1_FB0` field @def CAN_F9R1_FB0_Pos */
#define CAN_F9R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB0` field @def CAN_F9R1_FB0_Msk */
#define CAN_F9R1_FB0_Msk		REG_BIT_MASK(CAN_F9R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F9R1_FB0 */
#define CAN_F9R1_FB0			CAN_F9R1_FB0_Msk
/** @brief Bit position of the `CAN_F9R1_FB1` field @def CAN_F9R1_FB1_Pos */
#define CAN_F9R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB1` field @def CAN_F9R1_FB1_Msk */
#define CAN_F9R1_FB1_Msk		REG_BIT_MASK(CAN_F9R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F9R1_FB1 */
#define CAN_F9R1_FB1			CAN_F9R1_FB1_Msk
/** @brief Bit position of the `CAN_F9R1_FB2` field @def CAN_F9R1_FB2_Pos */
#define CAN_F9R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB2` field @def CAN_F9R1_FB2_Msk */
#define CAN_F9R1_FB2_Msk		REG_BIT_MASK(CAN_F9R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F9R1_FB2 */
#define CAN_F9R1_FB2			CAN_F9R1_FB2_Msk
/** @brief Bit position of the `CAN_F9R1_FB3` field @def CAN_F9R1_FB3_Pos */
#define CAN_F9R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB3` field @def CAN_F9R1_FB3_Msk */
#define CAN_F9R1_FB3_Msk		REG_BIT_MASK(CAN_F9R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F9R1_FB3 */
#define CAN_F9R1_FB3			CAN_F9R1_FB3_Msk
/** @brief Bit position of the `CAN_F9R1_FB4` field @def CAN_F9R1_FB4_Pos */
#define CAN_F9R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB4` field @def CAN_F9R1_FB4_Msk */
#define CAN_F9R1_FB4_Msk		REG_BIT_MASK(CAN_F9R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F9R1_FB4 */
#define CAN_F9R1_FB4			CAN_F9R1_FB4_Msk
/** @brief Bit position of the `CAN_F9R1_FB5` field @def CAN_F9R1_FB5_Pos */
#define CAN_F9R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB5` field @def CAN_F9R1_FB5_Msk */
#define CAN_F9R1_FB5_Msk		REG_BIT_MASK(CAN_F9R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F9R1_FB5 */
#define CAN_F9R1_FB5			CAN_F9R1_FB5_Msk
/** @brief Bit position of the `CAN_F9R1_FB6` field @def CAN_F9R1_FB6_Pos */
#define CAN_F9R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB6` field @def CAN_F9R1_FB6_Msk */
#define CAN_F9R1_FB6_Msk		REG_BIT_MASK(CAN_F9R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F9R1_FB6 */
#define CAN_F9R1_FB6			CAN_F9R1_FB6_Msk
/** @brief Bit position of the `CAN_F9R1_FB7` field @def CAN_F9R1_FB7_Pos */
#define CAN_F9R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB7` field @def CAN_F9R1_FB7_Msk */
#define CAN_F9R1_FB7_Msk		REG_BIT_MASK(CAN_F9R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F9R1_FB7 */
#define CAN_F9R1_FB7			CAN_F9R1_FB7_Msk
/** @brief Bit position of the `CAN_F9R1_FB8` field @def CAN_F9R1_FB8_Pos */
#define CAN_F9R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB8` field @def CAN_F9R1_FB8_Msk */
#define CAN_F9R1_FB8_Msk		REG_BIT_MASK(CAN_F9R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F9R1_FB8 */
#define CAN_F9R1_FB8			CAN_F9R1_FB8_Msk
/** @brief Bit position of the `CAN_F9R1_FB9` field @def CAN_F9R1_FB9_Pos */
#define CAN_F9R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB9` field @def CAN_F9R1_FB9_Msk */
#define CAN_F9R1_FB9_Msk		REG_BIT_MASK(CAN_F9R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F9R1_FB9 */
#define CAN_F9R1_FB9			CAN_F9R1_FB9_Msk
/** @brief Bit position of the `CAN_F9R1_FB10` field @def CAN_F9R1_FB10_Pos */
#define CAN_F9R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB10` field @def CAN_F9R1_FB10_Msk */
#define CAN_F9R1_FB10_Msk		REG_BIT_MASK(CAN_F9R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F9R1_FB10 */
#define CAN_F9R1_FB10			CAN_F9R1_FB10_Msk
/** @brief Bit position of the `CAN_F9R1_FB11` field @def CAN_F9R1_FB11_Pos */
#define CAN_F9R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB11` field @def CAN_F9R1_FB11_Msk */
#define CAN_F9R1_FB11_Msk		REG_BIT_MASK(CAN_F9R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F9R1_FB11 */
#define CAN_F9R1_FB11			CAN_F9R1_FB11_Msk
/** @brief Bit position of the `CAN_F9R1_FB12` field @def CAN_F9R1_FB12_Pos */
#define CAN_F9R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB12` field @def CAN_F9R1_FB12_Msk */
#define CAN_F9R1_FB12_Msk		REG_BIT_MASK(CAN_F9R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F9R1_FB12 */
#define CAN_F9R1_FB12			CAN_F9R1_FB12_Msk
/** @brief Bit position of the `CAN_F9R1_FB13` field @def CAN_F9R1_FB13_Pos */
#define CAN_F9R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB13` field @def CAN_F9R1_FB13_Msk */
#define CAN_F9R1_FB13_Msk		REG_BIT_MASK(CAN_F9R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F9R1_FB13 */
#define CAN_F9R1_FB13			CAN_F9R1_FB13_Msk
/** @brief Bit position of the `CAN_F9R1_FB14` field @def CAN_F9R1_FB14_Pos */
#define CAN_F9R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB14` field @def CAN_F9R1_FB14_Msk */
#define CAN_F9R1_FB14_Msk		REG_BIT_MASK(CAN_F9R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F9R1_FB14 */
#define CAN_F9R1_FB14			CAN_F9R1_FB14_Msk
/** @brief Bit position of the `CAN_F9R1_FB15` field @def CAN_F9R1_FB15_Pos */
#define CAN_F9R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB15` field @def CAN_F9R1_FB15_Msk */
#define CAN_F9R1_FB15_Msk		REG_BIT_MASK(CAN_F9R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F9R1_FB15 */
#define CAN_F9R1_FB15			CAN_F9R1_FB15_Msk
/** @brief Bit position of the `CAN_F9R1_FB16` field @def CAN_F9R1_FB16_Pos */
#define CAN_F9R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB16` field @def CAN_F9R1_FB16_Msk */
#define CAN_F9R1_FB16_Msk		REG_BIT_MASK(CAN_F9R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F9R1_FB16 */
#define CAN_F9R1_FB16			CAN_F9R1_FB16_Msk
/** @brief Bit position of the `CAN_F9R1_FB17` field @def CAN_F9R1_FB17_Pos */
#define CAN_F9R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB17` field @def CAN_F9R1_FB17_Msk */
#define CAN_F9R1_FB17_Msk		REG_BIT_MASK(CAN_F9R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F9R1_FB17 */
#define CAN_F9R1_FB17			CAN_F9R1_FB17_Msk
/** @brief Bit position of the `CAN_F9R1_FB18` field @def CAN_F9R1_FB18_Pos */
#define CAN_F9R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB18` field @def CAN_F9R1_FB18_Msk */
#define CAN_F9R1_FB18_Msk		REG_BIT_MASK(CAN_F9R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F9R1_FB18 */
#define CAN_F9R1_FB18			CAN_F9R1_FB18_Msk
/** @brief Bit position of the `CAN_F9R1_FB19` field @def CAN_F9R1_FB19_Pos */
#define CAN_F9R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB19` field @def CAN_F9R1_FB19_Msk */
#define CAN_F9R1_FB19_Msk		REG_BIT_MASK(CAN_F9R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F9R1_FB19 */
#define CAN_F9R1_FB19			CAN_F9R1_FB19_Msk
/** @brief Bit position of the `CAN_F9R1_FB20` field @def CAN_F9R1_FB20_Pos */
#define CAN_F9R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB20` field @def CAN_F9R1_FB20_Msk */
#define CAN_F9R1_FB20_Msk		REG_BIT_MASK(CAN_F9R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F9R1_FB20 */
#define CAN_F9R1_FB20			CAN_F9R1_FB20_Msk
/** @brief Bit position of the `CAN_F9R1_FB21` field @def CAN_F9R1_FB21_Pos */
#define CAN_F9R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB21` field @def CAN_F9R1_FB21_Msk */
#define CAN_F9R1_FB21_Msk		REG_BIT_MASK(CAN_F9R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F9R1_FB21 */
#define CAN_F9R1_FB21			CAN_F9R1_FB21_Msk
/** @brief Bit position of the `CAN_F9R1_FB22` field @def CAN_F9R1_FB22_Pos */
#define CAN_F9R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB22` field @def CAN_F9R1_FB22_Msk */
#define CAN_F9R1_FB22_Msk		REG_BIT_MASK(CAN_F9R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F9R1_FB22 */
#define CAN_F9R1_FB22			CAN_F9R1_FB22_Msk
/** @brief Bit position of the `CAN_F9R1_FB23` field @def CAN_F9R1_FB23_Pos */
#define CAN_F9R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB23` field @def CAN_F9R1_FB23_Msk */
#define CAN_F9R1_FB23_Msk		REG_BIT_MASK(CAN_F9R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F9R1_FB23 */
#define CAN_F9R1_FB23			CAN_F9R1_FB23_Msk
/** @brief Bit position of the `CAN_F9R1_FB24` field @def CAN_F9R1_FB24_Pos */
#define CAN_F9R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB24` field @def CAN_F9R1_FB24_Msk */
#define CAN_F9R1_FB24_Msk		REG_BIT_MASK(CAN_F9R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F9R1_FB24 */
#define CAN_F9R1_FB24			CAN_F9R1_FB24_Msk
/** @brief Bit position of the `CAN_F9R1_FB25` field @def CAN_F9R1_FB25_Pos */
#define CAN_F9R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB25` field @def CAN_F9R1_FB25_Msk */
#define CAN_F9R1_FB25_Msk		REG_BIT_MASK(CAN_F9R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F9R1_FB25 */
#define CAN_F9R1_FB25			CAN_F9R1_FB25_Msk
/** @brief Bit position of the `CAN_F9R1_FB26` field @def CAN_F9R1_FB26_Pos */
#define CAN_F9R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB26` field @def CAN_F9R1_FB26_Msk */
#define CAN_F9R1_FB26_Msk		REG_BIT_MASK(CAN_F9R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F9R1_FB26 */
#define CAN_F9R1_FB26			CAN_F9R1_FB26_Msk
/** @brief Bit position of the `CAN_F9R1_FB27` field @def CAN_F9R1_FB27_Pos */
#define CAN_F9R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB27` field @def CAN_F9R1_FB27_Msk */
#define CAN_F9R1_FB27_Msk		REG_BIT_MASK(CAN_F9R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F9R1_FB27 */
#define CAN_F9R1_FB27			CAN_F9R1_FB27_Msk
/** @brief Bit position of the `CAN_F9R1_FB28` field @def CAN_F9R1_FB28_Pos */
#define CAN_F9R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB28` field @def CAN_F9R1_FB28_Msk */
#define CAN_F9R1_FB28_Msk		REG_BIT_MASK(CAN_F9R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F9R1_FB28 */
#define CAN_F9R1_FB28			CAN_F9R1_FB28_Msk
/** @brief Bit position of the `CAN_F9R1_FB29` field @def CAN_F9R1_FB29_Pos */
#define CAN_F9R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB29` field @def CAN_F9R1_FB29_Msk */
#define CAN_F9R1_FB29_Msk		REG_BIT_MASK(CAN_F9R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F9R1_FB29 */
#define CAN_F9R1_FB29			CAN_F9R1_FB29_Msk
/** @brief Bit position of the `CAN_F9R1_FB30` field @def CAN_F9R1_FB30_Pos */
#define CAN_F9R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB30` field @def CAN_F9R1_FB30_Msk */
#define CAN_F9R1_FB30_Msk		REG_BIT_MASK(CAN_F9R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F9R1_FB30 */
#define CAN_F9R1_FB30			CAN_F9R1_FB30_Msk
/** @brief Bit position of the `CAN_F9R1_FB31` field @def CAN_F9R1_FB31_Pos */
#define CAN_F9R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F9R1_FB31` field @def CAN_F9R1_FB31_Msk */
#define CAN_F9R1_FB31_Msk		REG_BIT_MASK(CAN_F9R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F9R1_FB31 */
#define CAN_F9R1_FB31			CAN_F9R1_FB31_Msk

// ---------------------------------- CAN_F10R1 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_F10R1_FB0` field @def CAN_F10R1_FB0_Pos */
#define CAN_F10R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB0` field @def CAN_F10R1_FB0_Msk */
#define CAN_F10R1_FB0_Msk		REG_BIT_MASK(CAN_F10R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F10R1_FB0 */
#define CAN_F10R1_FB0			CAN_F10R1_FB0_Msk
/** @brief Bit position of the `CAN_F10R1_FB1` field @def CAN_F10R1_FB1_Pos */
#define CAN_F10R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB1` field @def CAN_F10R1_FB1_Msk */
#define CAN_F10R1_FB1_Msk		REG_BIT_MASK(CAN_F10R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F10R1_FB1 */
#define CAN_F10R1_FB1			CAN_F10R1_FB1_Msk
/** @brief Bit position of the `CAN_F10R1_FB2` field @def CAN_F10R1_FB2_Pos */
#define CAN_F10R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB2` field @def CAN_F10R1_FB2_Msk */
#define CAN_F10R1_FB2_Msk		REG_BIT_MASK(CAN_F10R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F10R1_FB2 */
#define CAN_F10R1_FB2			CAN_F10R1_FB2_Msk
/** @brief Bit position of the `CAN_F10R1_FB3` field @def CAN_F10R1_FB3_Pos */
#define CAN_F10R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB3` field @def CAN_F10R1_FB3_Msk */
#define CAN_F10R1_FB3_Msk		REG_BIT_MASK(CAN_F10R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F10R1_FB3 */
#define CAN_F10R1_FB3			CAN_F10R1_FB3_Msk
/** @brief Bit position of the `CAN_F10R1_FB4` field @def CAN_F10R1_FB4_Pos */
#define CAN_F10R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB4` field @def CAN_F10R1_FB4_Msk */
#define CAN_F10R1_FB4_Msk		REG_BIT_MASK(CAN_F10R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F10R1_FB4 */
#define CAN_F10R1_FB4			CAN_F10R1_FB4_Msk
/** @brief Bit position of the `CAN_F10R1_FB5` field @def CAN_F10R1_FB5_Pos */
#define CAN_F10R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB5` field @def CAN_F10R1_FB5_Msk */
#define CAN_F10R1_FB5_Msk		REG_BIT_MASK(CAN_F10R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F10R1_FB5 */
#define CAN_F10R1_FB5			CAN_F10R1_FB5_Msk
/** @brief Bit position of the `CAN_F10R1_FB6` field @def CAN_F10R1_FB6_Pos */
#define CAN_F10R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB6` field @def CAN_F10R1_FB6_Msk */
#define CAN_F10R1_FB6_Msk		REG_BIT_MASK(CAN_F10R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F10R1_FB6 */
#define CAN_F10R1_FB6			CAN_F10R1_FB6_Msk
/** @brief Bit position of the `CAN_F10R1_FB7` field @def CAN_F10R1_FB7_Pos */
#define CAN_F10R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB7` field @def CAN_F10R1_FB7_Msk */
#define CAN_F10R1_FB7_Msk		REG_BIT_MASK(CAN_F10R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F10R1_FB7 */
#define CAN_F10R1_FB7			CAN_F10R1_FB7_Msk
/** @brief Bit position of the `CAN_F10R1_FB8` field @def CAN_F10R1_FB8_Pos */
#define CAN_F10R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB8` field @def CAN_F10R1_FB8_Msk */
#define CAN_F10R1_FB8_Msk		REG_BIT_MASK(CAN_F10R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F10R1_FB8 */
#define CAN_F10R1_FB8			CAN_F10R1_FB8_Msk
/** @brief Bit position of the `CAN_F10R1_FB9` field @def CAN_F10R1_FB9_Pos */
#define CAN_F10R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB9` field @def CAN_F10R1_FB9_Msk */
#define CAN_F10R1_FB9_Msk		REG_BIT_MASK(CAN_F10R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F10R1_FB9 */
#define CAN_F10R1_FB9			CAN_F10R1_FB9_Msk
/** @brief Bit position of the `CAN_F10R1_FB10` field @def CAN_F10R1_FB10_Pos */
#define CAN_F10R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB10` field @def CAN_F10R1_FB10_Msk */
#define CAN_F10R1_FB10_Msk		REG_BIT_MASK(CAN_F10R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F10R1_FB10 */
#define CAN_F10R1_FB10			CAN_F10R1_FB10_Msk
/** @brief Bit position of the `CAN_F10R1_FB11` field @def CAN_F10R1_FB11_Pos */
#define CAN_F10R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB11` field @def CAN_F10R1_FB11_Msk */
#define CAN_F10R1_FB11_Msk		REG_BIT_MASK(CAN_F10R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F10R1_FB11 */
#define CAN_F10R1_FB11			CAN_F10R1_FB11_Msk
/** @brief Bit position of the `CAN_F10R1_FB12` field @def CAN_F10R1_FB12_Pos */
#define CAN_F10R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB12` field @def CAN_F10R1_FB12_Msk */
#define CAN_F10R1_FB12_Msk		REG_BIT_MASK(CAN_F10R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F10R1_FB12 */
#define CAN_F10R1_FB12			CAN_F10R1_FB12_Msk
/** @brief Bit position of the `CAN_F10R1_FB13` field @def CAN_F10R1_FB13_Pos */
#define CAN_F10R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB13` field @def CAN_F10R1_FB13_Msk */
#define CAN_F10R1_FB13_Msk		REG_BIT_MASK(CAN_F10R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F10R1_FB13 */
#define CAN_F10R1_FB13			CAN_F10R1_FB13_Msk
/** @brief Bit position of the `CAN_F10R1_FB14` field @def CAN_F10R1_FB14_Pos */
#define CAN_F10R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB14` field @def CAN_F10R1_FB14_Msk */
#define CAN_F10R1_FB14_Msk		REG_BIT_MASK(CAN_F10R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F10R1_FB14 */
#define CAN_F10R1_FB14			CAN_F10R1_FB14_Msk
/** @brief Bit position of the `CAN_F10R1_FB15` field @def CAN_F10R1_FB15_Pos */
#define CAN_F10R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB15` field @def CAN_F10R1_FB15_Msk */
#define CAN_F10R1_FB15_Msk		REG_BIT_MASK(CAN_F10R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F10R1_FB15 */
#define CAN_F10R1_FB15			CAN_F10R1_FB15_Msk
/** @brief Bit position of the `CAN_F10R1_FB16` field @def CAN_F10R1_FB16_Pos */
#define CAN_F10R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB16` field @def CAN_F10R1_FB16_Msk */
#define CAN_F10R1_FB16_Msk		REG_BIT_MASK(CAN_F10R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F10R1_FB16 */
#define CAN_F10R1_FB16			CAN_F10R1_FB16_Msk
/** @brief Bit position of the `CAN_F10R1_FB17` field @def CAN_F10R1_FB17_Pos */
#define CAN_F10R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB17` field @def CAN_F10R1_FB17_Msk */
#define CAN_F10R1_FB17_Msk		REG_BIT_MASK(CAN_F10R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F10R1_FB17 */
#define CAN_F10R1_FB17			CAN_F10R1_FB17_Msk
/** @brief Bit position of the `CAN_F10R1_FB18` field @def CAN_F10R1_FB18_Pos */
#define CAN_F10R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB18` field @def CAN_F10R1_FB18_Msk */
#define CAN_F10R1_FB18_Msk		REG_BIT_MASK(CAN_F10R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F10R1_FB18 */
#define CAN_F10R1_FB18			CAN_F10R1_FB18_Msk
/** @brief Bit position of the `CAN_F10R1_FB19` field @def CAN_F10R1_FB19_Pos */
#define CAN_F10R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB19` field @def CAN_F10R1_FB19_Msk */
#define CAN_F10R1_FB19_Msk		REG_BIT_MASK(CAN_F10R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F10R1_FB19 */
#define CAN_F10R1_FB19			CAN_F10R1_FB19_Msk
/** @brief Bit position of the `CAN_F10R1_FB20` field @def CAN_F10R1_FB20_Pos */
#define CAN_F10R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB20` field @def CAN_F10R1_FB20_Msk */
#define CAN_F10R1_FB20_Msk		REG_BIT_MASK(CAN_F10R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F10R1_FB20 */
#define CAN_F10R1_FB20			CAN_F10R1_FB20_Msk
/** @brief Bit position of the `CAN_F10R1_FB21` field @def CAN_F10R1_FB21_Pos */
#define CAN_F10R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB21` field @def CAN_F10R1_FB21_Msk */
#define CAN_F10R1_FB21_Msk		REG_BIT_MASK(CAN_F10R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F10R1_FB21 */
#define CAN_F10R1_FB21			CAN_F10R1_FB21_Msk
/** @brief Bit position of the `CAN_F10R1_FB22` field @def CAN_F10R1_FB22_Pos */
#define CAN_F10R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB22` field @def CAN_F10R1_FB22_Msk */
#define CAN_F10R1_FB22_Msk		REG_BIT_MASK(CAN_F10R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F10R1_FB22 */
#define CAN_F10R1_FB22			CAN_F10R1_FB22_Msk
/** @brief Bit position of the `CAN_F10R1_FB23` field @def CAN_F10R1_FB23_Pos */
#define CAN_F10R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB23` field @def CAN_F10R1_FB23_Msk */
#define CAN_F10R1_FB23_Msk		REG_BIT_MASK(CAN_F10R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F10R1_FB23 */
#define CAN_F10R1_FB23			CAN_F10R1_FB23_Msk
/** @brief Bit position of the `CAN_F10R1_FB24` field @def CAN_F10R1_FB24_Pos */
#define CAN_F10R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB24` field @def CAN_F10R1_FB24_Msk */
#define CAN_F10R1_FB24_Msk		REG_BIT_MASK(CAN_F10R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F10R1_FB24 */
#define CAN_F10R1_FB24			CAN_F10R1_FB24_Msk
/** @brief Bit position of the `CAN_F10R1_FB25` field @def CAN_F10R1_FB25_Pos */
#define CAN_F10R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB25` field @def CAN_F10R1_FB25_Msk */
#define CAN_F10R1_FB25_Msk		REG_BIT_MASK(CAN_F10R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F10R1_FB25 */
#define CAN_F10R1_FB25			CAN_F10R1_FB25_Msk
/** @brief Bit position of the `CAN_F10R1_FB26` field @def CAN_F10R1_FB26_Pos */
#define CAN_F10R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB26` field @def CAN_F10R1_FB26_Msk */
#define CAN_F10R1_FB26_Msk		REG_BIT_MASK(CAN_F10R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F10R1_FB26 */
#define CAN_F10R1_FB26			CAN_F10R1_FB26_Msk
/** @brief Bit position of the `CAN_F10R1_FB27` field @def CAN_F10R1_FB27_Pos */
#define CAN_F10R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB27` field @def CAN_F10R1_FB27_Msk */
#define CAN_F10R1_FB27_Msk		REG_BIT_MASK(CAN_F10R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F10R1_FB27 */
#define CAN_F10R1_FB27			CAN_F10R1_FB27_Msk
/** @brief Bit position of the `CAN_F10R1_FB28` field @def CAN_F10R1_FB28_Pos */
#define CAN_F10R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB28` field @def CAN_F10R1_FB28_Msk */
#define CAN_F10R1_FB28_Msk		REG_BIT_MASK(CAN_F10R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F10R1_FB28 */
#define CAN_F10R1_FB28			CAN_F10R1_FB28_Msk
/** @brief Bit position of the `CAN_F10R1_FB29` field @def CAN_F10R1_FB29_Pos */
#define CAN_F10R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB29` field @def CAN_F10R1_FB29_Msk */
#define CAN_F10R1_FB29_Msk		REG_BIT_MASK(CAN_F10R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F10R1_FB29 */
#define CAN_F10R1_FB29			CAN_F10R1_FB29_Msk
/** @brief Bit position of the `CAN_F10R1_FB30` field @def CAN_F10R1_FB30_Pos */
#define CAN_F10R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB30` field @def CAN_F10R1_FB30_Msk */
#define CAN_F10R1_FB30_Msk		REG_BIT_MASK(CAN_F10R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F10R1_FB30 */
#define CAN_F10R1_FB30			CAN_F10R1_FB30_Msk
/** @brief Bit position of the `CAN_F10R1_FB31` field @def CAN_F10R1_FB31_Pos */
#define CAN_F10R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F10R1_FB31` field @def CAN_F10R1_FB31_Msk */
#define CAN_F10R1_FB31_Msk		REG_BIT_MASK(CAN_F10R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F10R1_FB31 */
#define CAN_F10R1_FB31			CAN_F10R1_FB31_Msk

// ---------------------------------- CAN_F11R1 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_F11R1_FB0` field @def CAN_F11R1_FB0_Pos */
#define CAN_F11R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB0` field @def CAN_F11R1_FB0_Msk */
#define CAN_F11R1_FB0_Msk		REG_BIT_MASK(CAN_F11R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F11R1_FB0 */
#define CAN_F11R1_FB0			CAN_F11R1_FB0_Msk
/** @brief Bit position of the `CAN_F11R1_FB1` field @def CAN_F11R1_FB1_Pos */
#define CAN_F11R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB1` field @def CAN_F11R1_FB1_Msk */
#define CAN_F11R1_FB1_Msk		REG_BIT_MASK(CAN_F11R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F11R1_FB1 */
#define CAN_F11R1_FB1			CAN_F11R1_FB1_Msk
/** @brief Bit position of the `CAN_F11R1_FB2` field @def CAN_F11R1_FB2_Pos */
#define CAN_F11R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB2` field @def CAN_F11R1_FB2_Msk */
#define CAN_F11R1_FB2_Msk		REG_BIT_MASK(CAN_F11R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F11R1_FB2 */
#define CAN_F11R1_FB2			CAN_F11R1_FB2_Msk
/** @brief Bit position of the `CAN_F11R1_FB3` field @def CAN_F11R1_FB3_Pos */
#define CAN_F11R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB3` field @def CAN_F11R1_FB3_Msk */
#define CAN_F11R1_FB3_Msk		REG_BIT_MASK(CAN_F11R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F11R1_FB3 */
#define CAN_F11R1_FB3			CAN_F11R1_FB3_Msk
/** @brief Bit position of the `CAN_F11R1_FB4` field @def CAN_F11R1_FB4_Pos */
#define CAN_F11R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB4` field @def CAN_F11R1_FB4_Msk */
#define CAN_F11R1_FB4_Msk		REG_BIT_MASK(CAN_F11R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F11R1_FB4 */
#define CAN_F11R1_FB4			CAN_F11R1_FB4_Msk
/** @brief Bit position of the `CAN_F11R1_FB5` field @def CAN_F11R1_FB5_Pos */
#define CAN_F11R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB5` field @def CAN_F11R1_FB5_Msk */
#define CAN_F11R1_FB5_Msk		REG_BIT_MASK(CAN_F11R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F11R1_FB5 */
#define CAN_F11R1_FB5			CAN_F11R1_FB5_Msk
/** @brief Bit position of the `CAN_F11R1_FB6` field @def CAN_F11R1_FB6_Pos */
#define CAN_F11R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB6` field @def CAN_F11R1_FB6_Msk */
#define CAN_F11R1_FB6_Msk		REG_BIT_MASK(CAN_F11R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F11R1_FB6 */
#define CAN_F11R1_FB6			CAN_F11R1_FB6_Msk
/** @brief Bit position of the `CAN_F11R1_FB7` field @def CAN_F11R1_FB7_Pos */
#define CAN_F11R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB7` field @def CAN_F11R1_FB7_Msk */
#define CAN_F11R1_FB7_Msk		REG_BIT_MASK(CAN_F11R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F11R1_FB7 */
#define CAN_F11R1_FB7			CAN_F11R1_FB7_Msk
/** @brief Bit position of the `CAN_F11R1_FB8` field @def CAN_F11R1_FB8_Pos */
#define CAN_F11R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB8` field @def CAN_F11R1_FB8_Msk */
#define CAN_F11R1_FB8_Msk		REG_BIT_MASK(CAN_F11R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F11R1_FB8 */
#define CAN_F11R1_FB8			CAN_F11R1_FB8_Msk
/** @brief Bit position of the `CAN_F11R1_FB9` field @def CAN_F11R1_FB9_Pos */
#define CAN_F11R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB9` field @def CAN_F11R1_FB9_Msk */
#define CAN_F11R1_FB9_Msk		REG_BIT_MASK(CAN_F11R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F11R1_FB9 */
#define CAN_F11R1_FB9			CAN_F11R1_FB9_Msk
/** @brief Bit position of the `CAN_F11R1_FB10` field @def CAN_F11R1_FB10_Pos */
#define CAN_F11R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB10` field @def CAN_F11R1_FB10_Msk */
#define CAN_F11R1_FB10_Msk		REG_BIT_MASK(CAN_F11R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F11R1_FB10 */
#define CAN_F11R1_FB10			CAN_F11R1_FB10_Msk
/** @brief Bit position of the `CAN_F11R1_FB11` field @def CAN_F11R1_FB11_Pos */
#define CAN_F11R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB11` field @def CAN_F11R1_FB11_Msk */
#define CAN_F11R1_FB11_Msk		REG_BIT_MASK(CAN_F11R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F11R1_FB11 */
#define CAN_F11R1_FB11			CAN_F11R1_FB11_Msk
/** @brief Bit position of the `CAN_F11R1_FB12` field @def CAN_F11R1_FB12_Pos */
#define CAN_F11R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB12` field @def CAN_F11R1_FB12_Msk */
#define CAN_F11R1_FB12_Msk		REG_BIT_MASK(CAN_F11R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F11R1_FB12 */
#define CAN_F11R1_FB12			CAN_F11R1_FB12_Msk
/** @brief Bit position of the `CAN_F11R1_FB13` field @def CAN_F11R1_FB13_Pos */
#define CAN_F11R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB13` field @def CAN_F11R1_FB13_Msk */
#define CAN_F11R1_FB13_Msk		REG_BIT_MASK(CAN_F11R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F11R1_FB13 */
#define CAN_F11R1_FB13			CAN_F11R1_FB13_Msk
/** @brief Bit position of the `CAN_F11R1_FB14` field @def CAN_F11R1_FB14_Pos */
#define CAN_F11R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB14` field @def CAN_F11R1_FB14_Msk */
#define CAN_F11R1_FB14_Msk		REG_BIT_MASK(CAN_F11R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F11R1_FB14 */
#define CAN_F11R1_FB14			CAN_F11R1_FB14_Msk
/** @brief Bit position of the `CAN_F11R1_FB15` field @def CAN_F11R1_FB15_Pos */
#define CAN_F11R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB15` field @def CAN_F11R1_FB15_Msk */
#define CAN_F11R1_FB15_Msk		REG_BIT_MASK(CAN_F11R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F11R1_FB15 */
#define CAN_F11R1_FB15			CAN_F11R1_FB15_Msk
/** @brief Bit position of the `CAN_F11R1_FB16` field @def CAN_F11R1_FB16_Pos */
#define CAN_F11R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB16` field @def CAN_F11R1_FB16_Msk */
#define CAN_F11R1_FB16_Msk		REG_BIT_MASK(CAN_F11R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F11R1_FB16 */
#define CAN_F11R1_FB16			CAN_F11R1_FB16_Msk
/** @brief Bit position of the `CAN_F11R1_FB17` field @def CAN_F11R1_FB17_Pos */
#define CAN_F11R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB17` field @def CAN_F11R1_FB17_Msk */
#define CAN_F11R1_FB17_Msk		REG_BIT_MASK(CAN_F11R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F11R1_FB17 */
#define CAN_F11R1_FB17			CAN_F11R1_FB17_Msk
/** @brief Bit position of the `CAN_F11R1_FB18` field @def CAN_F11R1_FB18_Pos */
#define CAN_F11R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB18` field @def CAN_F11R1_FB18_Msk */
#define CAN_F11R1_FB18_Msk		REG_BIT_MASK(CAN_F11R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F11R1_FB18 */
#define CAN_F11R1_FB18			CAN_F11R1_FB18_Msk
/** @brief Bit position of the `CAN_F11R1_FB19` field @def CAN_F11R1_FB19_Pos */
#define CAN_F11R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB19` field @def CAN_F11R1_FB19_Msk */
#define CAN_F11R1_FB19_Msk		REG_BIT_MASK(CAN_F11R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F11R1_FB19 */
#define CAN_F11R1_FB19			CAN_F11R1_FB19_Msk
/** @brief Bit position of the `CAN_F11R1_FB20` field @def CAN_F11R1_FB20_Pos */
#define CAN_F11R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB20` field @def CAN_F11R1_FB20_Msk */
#define CAN_F11R1_FB20_Msk		REG_BIT_MASK(CAN_F11R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F11R1_FB20 */
#define CAN_F11R1_FB20			CAN_F11R1_FB20_Msk
/** @brief Bit position of the `CAN_F11R1_FB21` field @def CAN_F11R1_FB21_Pos */
#define CAN_F11R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB21` field @def CAN_F11R1_FB21_Msk */
#define CAN_F11R1_FB21_Msk		REG_BIT_MASK(CAN_F11R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F11R1_FB21 */
#define CAN_F11R1_FB21			CAN_F11R1_FB21_Msk
/** @brief Bit position of the `CAN_F11R1_FB22` field @def CAN_F11R1_FB22_Pos */
#define CAN_F11R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB22` field @def CAN_F11R1_FB22_Msk */
#define CAN_F11R1_FB22_Msk		REG_BIT_MASK(CAN_F11R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F11R1_FB22 */
#define CAN_F11R1_FB22			CAN_F11R1_FB22_Msk
/** @brief Bit position of the `CAN_F11R1_FB23` field @def CAN_F11R1_FB23_Pos */
#define CAN_F11R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB23` field @def CAN_F11R1_FB23_Msk */
#define CAN_F11R1_FB23_Msk		REG_BIT_MASK(CAN_F11R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F11R1_FB23 */
#define CAN_F11R1_FB23			CAN_F11R1_FB23_Msk
/** @brief Bit position of the `CAN_F11R1_FB24` field @def CAN_F11R1_FB24_Pos */
#define CAN_F11R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB24` field @def CAN_F11R1_FB24_Msk */
#define CAN_F11R1_FB24_Msk		REG_BIT_MASK(CAN_F11R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F11R1_FB24 */
#define CAN_F11R1_FB24			CAN_F11R1_FB24_Msk
/** @brief Bit position of the `CAN_F11R1_FB25` field @def CAN_F11R1_FB25_Pos */
#define CAN_F11R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB25` field @def CAN_F11R1_FB25_Msk */
#define CAN_F11R1_FB25_Msk		REG_BIT_MASK(CAN_F11R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F11R1_FB25 */
#define CAN_F11R1_FB25			CAN_F11R1_FB25_Msk
/** @brief Bit position of the `CAN_F11R1_FB26` field @def CAN_F11R1_FB26_Pos */
#define CAN_F11R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB26` field @def CAN_F11R1_FB26_Msk */
#define CAN_F11R1_FB26_Msk		REG_BIT_MASK(CAN_F11R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F11R1_FB26 */
#define CAN_F11R1_FB26			CAN_F11R1_FB26_Msk
/** @brief Bit position of the `CAN_F11R1_FB27` field @def CAN_F11R1_FB27_Pos */
#define CAN_F11R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB27` field @def CAN_F11R1_FB27_Msk */
#define CAN_F11R1_FB27_Msk		REG_BIT_MASK(CAN_F11R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F11R1_FB27 */
#define CAN_F11R1_FB27			CAN_F11R1_FB27_Msk
/** @brief Bit position of the `CAN_F11R1_FB28` field @def CAN_F11R1_FB28_Pos */
#define CAN_F11R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB28` field @def CAN_F11R1_FB28_Msk */
#define CAN_F11R1_FB28_Msk		REG_BIT_MASK(CAN_F11R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F11R1_FB28 */
#define CAN_F11R1_FB28			CAN_F11R1_FB28_Msk
/** @brief Bit position of the `CAN_F11R1_FB29` field @def CAN_F11R1_FB29_Pos */
#define CAN_F11R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB29` field @def CAN_F11R1_FB29_Msk */
#define CAN_F11R1_FB29_Msk		REG_BIT_MASK(CAN_F11R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F11R1_FB29 */
#define CAN_F11R1_FB29			CAN_F11R1_FB29_Msk
/** @brief Bit position of the `CAN_F11R1_FB30` field @def CAN_F11R1_FB30_Pos */
#define CAN_F11R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB30` field @def CAN_F11R1_FB30_Msk */
#define CAN_F11R1_FB30_Msk		REG_BIT_MASK(CAN_F11R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F11R1_FB30 */
#define CAN_F11R1_FB30			CAN_F11R1_FB30_Msk
/** @brief Bit position of the `CAN_F11R1_FB31` field @def CAN_F11R1_FB31_Pos */
#define CAN_F11R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F11R1_FB31` field @def CAN_F11R1_FB31_Msk */
#define CAN_F11R1_FB31_Msk		REG_BIT_MASK(CAN_F11R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F11R1_FB31 */
#define CAN_F11R1_FB31			CAN_F11R1_FB31_Msk

// ---------------------------------- CAN_F12R1 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_F12R1_FB0` field @def CAN_F12R1_FB0_Pos */
#define CAN_F12R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB0` field @def CAN_F12R1_FB0_Msk */
#define CAN_F12R1_FB0_Msk		REG_BIT_MASK(CAN_F12R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F12R1_FB0 */
#define CAN_F12R1_FB0			CAN_F12R1_FB0_Msk
/** @brief Bit position of the `CAN_F12R1_FB1` field @def CAN_F12R1_FB1_Pos */
#define CAN_F12R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB1` field @def CAN_F12R1_FB1_Msk */
#define CAN_F12R1_FB1_Msk		REG_BIT_MASK(CAN_F12R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F12R1_FB1 */
#define CAN_F12R1_FB1			CAN_F12R1_FB1_Msk
/** @brief Bit position of the `CAN_F12R1_FB2` field @def CAN_F12R1_FB2_Pos */
#define CAN_F12R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB2` field @def CAN_F12R1_FB2_Msk */
#define CAN_F12R1_FB2_Msk		REG_BIT_MASK(CAN_F12R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F12R1_FB2 */
#define CAN_F12R1_FB2			CAN_F12R1_FB2_Msk
/** @brief Bit position of the `CAN_F12R1_FB3` field @def CAN_F12R1_FB3_Pos */
#define CAN_F12R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB3` field @def CAN_F12R1_FB3_Msk */
#define CAN_F12R1_FB3_Msk		REG_BIT_MASK(CAN_F12R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F12R1_FB3 */
#define CAN_F12R1_FB3			CAN_F12R1_FB3_Msk
/** @brief Bit position of the `CAN_F12R1_FB4` field @def CAN_F12R1_FB4_Pos */
#define CAN_F12R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB4` field @def CAN_F12R1_FB4_Msk */
#define CAN_F12R1_FB4_Msk		REG_BIT_MASK(CAN_F12R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F12R1_FB4 */
#define CAN_F12R1_FB4			CAN_F12R1_FB4_Msk
/** @brief Bit position of the `CAN_F12R1_FB5` field @def CAN_F12R1_FB5_Pos */
#define CAN_F12R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB5` field @def CAN_F12R1_FB5_Msk */
#define CAN_F12R1_FB5_Msk		REG_BIT_MASK(CAN_F12R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F12R1_FB5 */
#define CAN_F12R1_FB5			CAN_F12R1_FB5_Msk
/** @brief Bit position of the `CAN_F12R1_FB6` field @def CAN_F12R1_FB6_Pos */
#define CAN_F12R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB6` field @def CAN_F12R1_FB6_Msk */
#define CAN_F12R1_FB6_Msk		REG_BIT_MASK(CAN_F12R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F12R1_FB6 */
#define CAN_F12R1_FB6			CAN_F12R1_FB6_Msk
/** @brief Bit position of the `CAN_F12R1_FB7` field @def CAN_F12R1_FB7_Pos */
#define CAN_F12R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB7` field @def CAN_F12R1_FB7_Msk */
#define CAN_F12R1_FB7_Msk		REG_BIT_MASK(CAN_F12R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F12R1_FB7 */
#define CAN_F12R1_FB7			CAN_F12R1_FB7_Msk
/** @brief Bit position of the `CAN_F12R1_FB8` field @def CAN_F12R1_FB8_Pos */
#define CAN_F12R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB8` field @def CAN_F12R1_FB8_Msk */
#define CAN_F12R1_FB8_Msk		REG_BIT_MASK(CAN_F12R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F12R1_FB8 */
#define CAN_F12R1_FB8			CAN_F12R1_FB8_Msk
/** @brief Bit position of the `CAN_F12R1_FB9` field @def CAN_F12R1_FB9_Pos */
#define CAN_F12R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB9` field @def CAN_F12R1_FB9_Msk */
#define CAN_F12R1_FB9_Msk		REG_BIT_MASK(CAN_F12R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F12R1_FB9 */
#define CAN_F12R1_FB9			CAN_F12R1_FB9_Msk
/** @brief Bit position of the `CAN_F12R1_FB10` field @def CAN_F12R1_FB10_Pos */
#define CAN_F12R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB10` field @def CAN_F12R1_FB10_Msk */
#define CAN_F12R1_FB10_Msk		REG_BIT_MASK(CAN_F12R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F12R1_FB10 */
#define CAN_F12R1_FB10			CAN_F12R1_FB10_Msk
/** @brief Bit position of the `CAN_F12R1_FB11` field @def CAN_F12R1_FB11_Pos */
#define CAN_F12R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB11` field @def CAN_F12R1_FB11_Msk */
#define CAN_F12R1_FB11_Msk		REG_BIT_MASK(CAN_F12R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F12R1_FB11 */
#define CAN_F12R1_FB11			CAN_F12R1_FB11_Msk
/** @brief Bit position of the `CAN_F12R1_FB12` field @def CAN_F12R1_FB12_Pos */
#define CAN_F12R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB12` field @def CAN_F12R1_FB12_Msk */
#define CAN_F12R1_FB12_Msk		REG_BIT_MASK(CAN_F12R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F12R1_FB12 */
#define CAN_F12R1_FB12			CAN_F12R1_FB12_Msk
/** @brief Bit position of the `CAN_F12R1_FB13` field @def CAN_F12R1_FB13_Pos */
#define CAN_F12R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB13` field @def CAN_F12R1_FB13_Msk */
#define CAN_F12R1_FB13_Msk		REG_BIT_MASK(CAN_F12R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F12R1_FB13 */
#define CAN_F12R1_FB13			CAN_F12R1_FB13_Msk
/** @brief Bit position of the `CAN_F12R1_FB14` field @def CAN_F12R1_FB14_Pos */
#define CAN_F12R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB14` field @def CAN_F12R1_FB14_Msk */
#define CAN_F12R1_FB14_Msk		REG_BIT_MASK(CAN_F12R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F12R1_FB14 */
#define CAN_F12R1_FB14			CAN_F12R1_FB14_Msk
/** @brief Bit position of the `CAN_F12R1_FB15` field @def CAN_F12R1_FB15_Pos */
#define CAN_F12R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB15` field @def CAN_F12R1_FB15_Msk */
#define CAN_F12R1_FB15_Msk		REG_BIT_MASK(CAN_F12R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F12R1_FB15 */
#define CAN_F12R1_FB15			CAN_F12R1_FB15_Msk
/** @brief Bit position of the `CAN_F12R1_FB16` field @def CAN_F12R1_FB16_Pos */
#define CAN_F12R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB16` field @def CAN_F12R1_FB16_Msk */
#define CAN_F12R1_FB16_Msk		REG_BIT_MASK(CAN_F12R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F12R1_FB16 */
#define CAN_F12R1_FB16			CAN_F12R1_FB16_Msk
/** @brief Bit position of the `CAN_F12R1_FB17` field @def CAN_F12R1_FB17_Pos */
#define CAN_F12R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB17` field @def CAN_F12R1_FB17_Msk */
#define CAN_F12R1_FB17_Msk		REG_BIT_MASK(CAN_F12R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F12R1_FB17 */
#define CAN_F12R1_FB17			CAN_F12R1_FB17_Msk
/** @brief Bit position of the `CAN_F12R1_FB18` field @def CAN_F12R1_FB18_Pos */
#define CAN_F12R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB18` field @def CAN_F12R1_FB18_Msk */
#define CAN_F12R1_FB18_Msk		REG_BIT_MASK(CAN_F12R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F12R1_FB18 */
#define CAN_F12R1_FB18			CAN_F12R1_FB18_Msk
/** @brief Bit position of the `CAN_F12R1_FB19` field @def CAN_F12R1_FB19_Pos */
#define CAN_F12R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB19` field @def CAN_F12R1_FB19_Msk */
#define CAN_F12R1_FB19_Msk		REG_BIT_MASK(CAN_F12R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F12R1_FB19 */
#define CAN_F12R1_FB19			CAN_F12R1_FB19_Msk
/** @brief Bit position of the `CAN_F12R1_FB20` field @def CAN_F12R1_FB20_Pos */
#define CAN_F12R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB20` field @def CAN_F12R1_FB20_Msk */
#define CAN_F12R1_FB20_Msk		REG_BIT_MASK(CAN_F12R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F12R1_FB20 */
#define CAN_F12R1_FB20			CAN_F12R1_FB20_Msk
/** @brief Bit position of the `CAN_F12R1_FB21` field @def CAN_F12R1_FB21_Pos */
#define CAN_F12R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB21` field @def CAN_F12R1_FB21_Msk */
#define CAN_F12R1_FB21_Msk		REG_BIT_MASK(CAN_F12R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F12R1_FB21 */
#define CAN_F12R1_FB21			CAN_F12R1_FB21_Msk
/** @brief Bit position of the `CAN_F12R1_FB22` field @def CAN_F12R1_FB22_Pos */
#define CAN_F12R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB22` field @def CAN_F12R1_FB22_Msk */
#define CAN_F12R1_FB22_Msk		REG_BIT_MASK(CAN_F12R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F12R1_FB22 */
#define CAN_F12R1_FB22			CAN_F12R1_FB22_Msk
/** @brief Bit position of the `CAN_F12R1_FB23` field @def CAN_F12R1_FB23_Pos */
#define CAN_F12R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB23` field @def CAN_F12R1_FB23_Msk */
#define CAN_F12R1_FB23_Msk		REG_BIT_MASK(CAN_F12R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F12R1_FB23 */
#define CAN_F12R1_FB23			CAN_F12R1_FB23_Msk
/** @brief Bit position of the `CAN_F12R1_FB24` field @def CAN_F12R1_FB24_Pos */
#define CAN_F12R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB24` field @def CAN_F12R1_FB24_Msk */
#define CAN_F12R1_FB24_Msk		REG_BIT_MASK(CAN_F12R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F12R1_FB24 */
#define CAN_F12R1_FB24			CAN_F12R1_FB24_Msk
/** @brief Bit position of the `CAN_F12R1_FB25` field @def CAN_F12R1_FB25_Pos */
#define CAN_F12R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB25` field @def CAN_F12R1_FB25_Msk */
#define CAN_F12R1_FB25_Msk		REG_BIT_MASK(CAN_F12R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F12R1_FB25 */
#define CAN_F12R1_FB25			CAN_F12R1_FB25_Msk
/** @brief Bit position of the `CAN_F12R1_FB26` field @def CAN_F12R1_FB26_Pos */
#define CAN_F12R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB26` field @def CAN_F12R1_FB26_Msk */
#define CAN_F12R1_FB26_Msk		REG_BIT_MASK(CAN_F12R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F12R1_FB26 */
#define CAN_F12R1_FB26			CAN_F12R1_FB26_Msk
/** @brief Bit position of the `CAN_F12R1_FB27` field @def CAN_F12R1_FB27_Pos */
#define CAN_F12R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB27` field @def CAN_F12R1_FB27_Msk */
#define CAN_F12R1_FB27_Msk		REG_BIT_MASK(CAN_F12R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F12R1_FB27 */
#define CAN_F12R1_FB27			CAN_F12R1_FB27_Msk
/** @brief Bit position of the `CAN_F12R1_FB28` field @def CAN_F12R1_FB28_Pos */
#define CAN_F12R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB28` field @def CAN_F12R1_FB28_Msk */
#define CAN_F12R1_FB28_Msk		REG_BIT_MASK(CAN_F12R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F12R1_FB28 */
#define CAN_F12R1_FB28			CAN_F12R1_FB28_Msk
/** @brief Bit position of the `CAN_F12R1_FB29` field @def CAN_F12R1_FB29_Pos */
#define CAN_F12R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB29` field @def CAN_F12R1_FB29_Msk */
#define CAN_F12R1_FB29_Msk		REG_BIT_MASK(CAN_F12R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F12R1_FB29 */
#define CAN_F12R1_FB29			CAN_F12R1_FB29_Msk
/** @brief Bit position of the `CAN_F12R1_FB30` field @def CAN_F12R1_FB30_Pos */
#define CAN_F12R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB30` field @def CAN_F12R1_FB30_Msk */
#define CAN_F12R1_FB30_Msk		REG_BIT_MASK(CAN_F12R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F12R1_FB30 */
#define CAN_F12R1_FB30			CAN_F12R1_FB30_Msk
/** @brief Bit position of the `CAN_F12R1_FB31` field @def CAN_F12R1_FB31_Pos */
#define CAN_F12R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F12R1_FB31` field @def CAN_F12R1_FB31_Msk */
#define CAN_F12R1_FB31_Msk		REG_BIT_MASK(CAN_F12R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F12R1_FB31 */
#define CAN_F12R1_FB31			CAN_F12R1_FB31_Msk

// ---------------------------------- CAN_F13R1 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_F13R1_FB0` field @def CAN_F13R1_FB0_Pos */
#define CAN_F13R1_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB0` field @def CAN_F13R1_FB0_Msk */
#define CAN_F13R1_FB0_Msk		REG_BIT_MASK(CAN_F13R1_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F13R1_FB0 */
#define CAN_F13R1_FB0			CAN_F13R1_FB0_Msk
/** @brief Bit position of the `CAN_F13R1_FB1` field @def CAN_F13R1_FB1_Pos */
#define CAN_F13R1_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB1` field @def CAN_F13R1_FB1_Msk */
#define CAN_F13R1_FB1_Msk		REG_BIT_MASK(CAN_F13R1_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F13R1_FB1 */
#define CAN_F13R1_FB1			CAN_F13R1_FB1_Msk
/** @brief Bit position of the `CAN_F13R1_FB2` field @def CAN_F13R1_FB2_Pos */
#define CAN_F13R1_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB2` field @def CAN_F13R1_FB2_Msk */
#define CAN_F13R1_FB2_Msk		REG_BIT_MASK(CAN_F13R1_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F13R1_FB2 */
#define CAN_F13R1_FB2			CAN_F13R1_FB2_Msk
/** @brief Bit position of the `CAN_F13R1_FB3` field @def CAN_F13R1_FB3_Pos */
#define CAN_F13R1_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB3` field @def CAN_F13R1_FB3_Msk */
#define CAN_F13R1_FB3_Msk		REG_BIT_MASK(CAN_F13R1_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F13R1_FB3 */
#define CAN_F13R1_FB3			CAN_F13R1_FB3_Msk
/** @brief Bit position of the `CAN_F13R1_FB4` field @def CAN_F13R1_FB4_Pos */
#define CAN_F13R1_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB4` field @def CAN_F13R1_FB4_Msk */
#define CAN_F13R1_FB4_Msk		REG_BIT_MASK(CAN_F13R1_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F13R1_FB4 */
#define CAN_F13R1_FB4			CAN_F13R1_FB4_Msk
/** @brief Bit position of the `CAN_F13R1_FB5` field @def CAN_F13R1_FB5_Pos */
#define CAN_F13R1_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB5` field @def CAN_F13R1_FB5_Msk */
#define CAN_F13R1_FB5_Msk		REG_BIT_MASK(CAN_F13R1_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F13R1_FB5 */
#define CAN_F13R1_FB5			CAN_F13R1_FB5_Msk
/** @brief Bit position of the `CAN_F13R1_FB6` field @def CAN_F13R1_FB6_Pos */
#define CAN_F13R1_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB6` field @def CAN_F13R1_FB6_Msk */
#define CAN_F13R1_FB6_Msk		REG_BIT_MASK(CAN_F13R1_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F13R1_FB6 */
#define CAN_F13R1_FB6			CAN_F13R1_FB6_Msk
/** @brief Bit position of the `CAN_F13R1_FB7` field @def CAN_F13R1_FB7_Pos */
#define CAN_F13R1_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB7` field @def CAN_F13R1_FB7_Msk */
#define CAN_F13R1_FB7_Msk		REG_BIT_MASK(CAN_F13R1_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F13R1_FB7 */
#define CAN_F13R1_FB7			CAN_F13R1_FB7_Msk
/** @brief Bit position of the `CAN_F13R1_FB8` field @def CAN_F13R1_FB8_Pos */
#define CAN_F13R1_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB8` field @def CAN_F13R1_FB8_Msk */
#define CAN_F13R1_FB8_Msk		REG_BIT_MASK(CAN_F13R1_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F13R1_FB8 */
#define CAN_F13R1_FB8			CAN_F13R1_FB8_Msk
/** @brief Bit position of the `CAN_F13R1_FB9` field @def CAN_F13R1_FB9_Pos */
#define CAN_F13R1_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB9` field @def CAN_F13R1_FB9_Msk */
#define CAN_F13R1_FB9_Msk		REG_BIT_MASK(CAN_F13R1_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F13R1_FB9 */
#define CAN_F13R1_FB9			CAN_F13R1_FB9_Msk
/** @brief Bit position of the `CAN_F13R1_FB10` field @def CAN_F13R1_FB10_Pos */
#define CAN_F13R1_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB10` field @def CAN_F13R1_FB10_Msk */
#define CAN_F13R1_FB10_Msk		REG_BIT_MASK(CAN_F13R1_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F13R1_FB10 */
#define CAN_F13R1_FB10			CAN_F13R1_FB10_Msk
/** @brief Bit position of the `CAN_F13R1_FB11` field @def CAN_F13R1_FB11_Pos */
#define CAN_F13R1_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB11` field @def CAN_F13R1_FB11_Msk */
#define CAN_F13R1_FB11_Msk		REG_BIT_MASK(CAN_F13R1_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F13R1_FB11 */
#define CAN_F13R1_FB11			CAN_F13R1_FB11_Msk
/** @brief Bit position of the `CAN_F13R1_FB12` field @def CAN_F13R1_FB12_Pos */
#define CAN_F13R1_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB12` field @def CAN_F13R1_FB12_Msk */
#define CAN_F13R1_FB12_Msk		REG_BIT_MASK(CAN_F13R1_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F13R1_FB12 */
#define CAN_F13R1_FB12			CAN_F13R1_FB12_Msk
/** @brief Bit position of the `CAN_F13R1_FB13` field @def CAN_F13R1_FB13_Pos */
#define CAN_F13R1_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB13` field @def CAN_F13R1_FB13_Msk */
#define CAN_F13R1_FB13_Msk		REG_BIT_MASK(CAN_F13R1_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F13R1_FB13 */
#define CAN_F13R1_FB13			CAN_F13R1_FB13_Msk
/** @brief Bit position of the `CAN_F13R1_FB14` field @def CAN_F13R1_FB14_Pos */
#define CAN_F13R1_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB14` field @def CAN_F13R1_FB14_Msk */
#define CAN_F13R1_FB14_Msk		REG_BIT_MASK(CAN_F13R1_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F13R1_FB14 */
#define CAN_F13R1_FB14			CAN_F13R1_FB14_Msk
/** @brief Bit position of the `CAN_F13R1_FB15` field @def CAN_F13R1_FB15_Pos */
#define CAN_F13R1_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB15` field @def CAN_F13R1_FB15_Msk */
#define CAN_F13R1_FB15_Msk		REG_BIT_MASK(CAN_F13R1_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F13R1_FB15 */
#define CAN_F13R1_FB15			CAN_F13R1_FB15_Msk
/** @brief Bit position of the `CAN_F13R1_FB16` field @def CAN_F13R1_FB16_Pos */
#define CAN_F13R1_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB16` field @def CAN_F13R1_FB16_Msk */
#define CAN_F13R1_FB16_Msk		REG_BIT_MASK(CAN_F13R1_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F13R1_FB16 */
#define CAN_F13R1_FB16			CAN_F13R1_FB16_Msk
/** @brief Bit position of the `CAN_F13R1_FB17` field @def CAN_F13R1_FB17_Pos */
#define CAN_F13R1_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB17` field @def CAN_F13R1_FB17_Msk */
#define CAN_F13R1_FB17_Msk		REG_BIT_MASK(CAN_F13R1_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F13R1_FB17 */
#define CAN_F13R1_FB17			CAN_F13R1_FB17_Msk
/** @brief Bit position of the `CAN_F13R1_FB18` field @def CAN_F13R1_FB18_Pos */
#define CAN_F13R1_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB18` field @def CAN_F13R1_FB18_Msk */
#define CAN_F13R1_FB18_Msk		REG_BIT_MASK(CAN_F13R1_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F13R1_FB18 */
#define CAN_F13R1_FB18			CAN_F13R1_FB18_Msk
/** @brief Bit position of the `CAN_F13R1_FB19` field @def CAN_F13R1_FB19_Pos */
#define CAN_F13R1_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB19` field @def CAN_F13R1_FB19_Msk */
#define CAN_F13R1_FB19_Msk		REG_BIT_MASK(CAN_F13R1_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F13R1_FB19 */
#define CAN_F13R1_FB19			CAN_F13R1_FB19_Msk
/** @brief Bit position of the `CAN_F13R1_FB20` field @def CAN_F13R1_FB20_Pos */
#define CAN_F13R1_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB20` field @def CAN_F13R1_FB20_Msk */
#define CAN_F13R1_FB20_Msk		REG_BIT_MASK(CAN_F13R1_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F13R1_FB20 */
#define CAN_F13R1_FB20			CAN_F13R1_FB20_Msk
/** @brief Bit position of the `CAN_F13R1_FB21` field @def CAN_F13R1_FB21_Pos */
#define CAN_F13R1_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB21` field @def CAN_F13R1_FB21_Msk */
#define CAN_F13R1_FB21_Msk		REG_BIT_MASK(CAN_F13R1_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F13R1_FB21 */
#define CAN_F13R1_FB21			CAN_F13R1_FB21_Msk
/** @brief Bit position of the `CAN_F13R1_FB22` field @def CAN_F13R1_FB22_Pos */
#define CAN_F13R1_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB22` field @def CAN_F13R1_FB22_Msk */
#define CAN_F13R1_FB22_Msk		REG_BIT_MASK(CAN_F13R1_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F13R1_FB22 */
#define CAN_F13R1_FB22			CAN_F13R1_FB22_Msk
/** @brief Bit position of the `CAN_F13R1_FB23` field @def CAN_F13R1_FB23_Pos */
#define CAN_F13R1_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB23` field @def CAN_F13R1_FB23_Msk */
#define CAN_F13R1_FB23_Msk		REG_BIT_MASK(CAN_F13R1_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F13R1_FB23 */
#define CAN_F13R1_FB23			CAN_F13R1_FB23_Msk
/** @brief Bit position of the `CAN_F13R1_FB24` field @def CAN_F13R1_FB24_Pos */
#define CAN_F13R1_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB24` field @def CAN_F13R1_FB24_Msk */
#define CAN_F13R1_FB24_Msk		REG_BIT_MASK(CAN_F13R1_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F13R1_FB24 */
#define CAN_F13R1_FB24			CAN_F13R1_FB24_Msk
/** @brief Bit position of the `CAN_F13R1_FB25` field @def CAN_F13R1_FB25_Pos */
#define CAN_F13R1_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB25` field @def CAN_F13R1_FB25_Msk */
#define CAN_F13R1_FB25_Msk		REG_BIT_MASK(CAN_F13R1_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F13R1_FB25 */
#define CAN_F13R1_FB25			CAN_F13R1_FB25_Msk
/** @brief Bit position of the `CAN_F13R1_FB26` field @def CAN_F13R1_FB26_Pos */
#define CAN_F13R1_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB26` field @def CAN_F13R1_FB26_Msk */
#define CAN_F13R1_FB26_Msk		REG_BIT_MASK(CAN_F13R1_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F13R1_FB26 */
#define CAN_F13R1_FB26			CAN_F13R1_FB26_Msk
/** @brief Bit position of the `CAN_F13R1_FB27` field @def CAN_F13R1_FB27_Pos */
#define CAN_F13R1_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB27` field @def CAN_F13R1_FB27_Msk */
#define CAN_F13R1_FB27_Msk		REG_BIT_MASK(CAN_F13R1_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F13R1_FB27 */
#define CAN_F13R1_FB27			CAN_F13R1_FB27_Msk
/** @brief Bit position of the `CAN_F13R1_FB28` field @def CAN_F13R1_FB28_Pos */
#define CAN_F13R1_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB28` field @def CAN_F13R1_FB28_Msk */
#define CAN_F13R1_FB28_Msk		REG_BIT_MASK(CAN_F13R1_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F13R1_FB28 */
#define CAN_F13R1_FB28			CAN_F13R1_FB28_Msk
/** @brief Bit position of the `CAN_F13R1_FB29` field @def CAN_F13R1_FB29_Pos */
#define CAN_F13R1_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB29` field @def CAN_F13R1_FB29_Msk */
#define CAN_F13R1_FB29_Msk		REG_BIT_MASK(CAN_F13R1_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F13R1_FB29 */
#define CAN_F13R1_FB29			CAN_F13R1_FB29_Msk
/** @brief Bit position of the `CAN_F13R1_FB30` field @def CAN_F13R1_FB30_Pos */
#define CAN_F13R1_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB30` field @def CAN_F13R1_FB30_Msk */
#define CAN_F13R1_FB30_Msk		REG_BIT_MASK(CAN_F13R1_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F13R1_FB30 */
#define CAN_F13R1_FB30			CAN_F13R1_FB30_Msk
/** @brief Bit position of the `CAN_F13R1_FB31` field @def CAN_F13R1_FB31_Pos */
#define CAN_F13R1_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F13R1_FB31` field @def CAN_F13R1_FB31_Msk */
#define CAN_F13R1_FB31_Msk		REG_BIT_MASK(CAN_F13R1_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F13R1_FB31 */
#define CAN_F13R1_FB31			CAN_F13R1_FB31_Msk

// ---------------------------------- CAN_F0R2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F0R2_FB0` field @def CAN_F0R2_FB0_Pos */
#define CAN_F0R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB0` field @def CAN_F0R2_FB0_Msk */
#define CAN_F0R2_FB0_Msk		REG_BIT_MASK(CAN_F0R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F0R2_FB0 */
#define CAN_F0R2_FB0			CAN_F0R2_FB0_Msk
/** @brief Bit position of the `CAN_F0R2_FB1` field @def CAN_F0R2_FB1_Pos */
#define CAN_F0R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB1` field @def CAN_F0R2_FB1_Msk */
#define CAN_F0R2_FB1_Msk		REG_BIT_MASK(CAN_F0R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F0R2_FB1 */
#define CAN_F0R2_FB1			CAN_F0R2_FB1_Msk
/** @brief Bit position of the `CAN_F0R2_FB2` field @def CAN_F0R2_FB2_Pos */
#define CAN_F0R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB2` field @def CAN_F0R2_FB2_Msk */
#define CAN_F0R2_FB2_Msk		REG_BIT_MASK(CAN_F0R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F0R2_FB2 */
#define CAN_F0R2_FB2			CAN_F0R2_FB2_Msk
/** @brief Bit position of the `CAN_F0R2_FB3` field @def CAN_F0R2_FB3_Pos */
#define CAN_F0R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB3` field @def CAN_F0R2_FB3_Msk */
#define CAN_F0R2_FB3_Msk		REG_BIT_MASK(CAN_F0R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F0R2_FB3 */
#define CAN_F0R2_FB3			CAN_F0R2_FB3_Msk
/** @brief Bit position of the `CAN_F0R2_FB4` field @def CAN_F0R2_FB4_Pos */
#define CAN_F0R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB4` field @def CAN_F0R2_FB4_Msk */
#define CAN_F0R2_FB4_Msk		REG_BIT_MASK(CAN_F0R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F0R2_FB4 */
#define CAN_F0R2_FB4			CAN_F0R2_FB4_Msk
/** @brief Bit position of the `CAN_F0R2_FB5` field @def CAN_F0R2_FB5_Pos */
#define CAN_F0R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB5` field @def CAN_F0R2_FB5_Msk */
#define CAN_F0R2_FB5_Msk		REG_BIT_MASK(CAN_F0R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F0R2_FB5 */
#define CAN_F0R2_FB5			CAN_F0R2_FB5_Msk
/** @brief Bit position of the `CAN_F0R2_FB6` field @def CAN_F0R2_FB6_Pos */
#define CAN_F0R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB6` field @def CAN_F0R2_FB6_Msk */
#define CAN_F0R2_FB6_Msk		REG_BIT_MASK(CAN_F0R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F0R2_FB6 */
#define CAN_F0R2_FB6			CAN_F0R2_FB6_Msk
/** @brief Bit position of the `CAN_F0R2_FB7` field @def CAN_F0R2_FB7_Pos */
#define CAN_F0R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB7` field @def CAN_F0R2_FB7_Msk */
#define CAN_F0R2_FB7_Msk		REG_BIT_MASK(CAN_F0R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F0R2_FB7 */
#define CAN_F0R2_FB7			CAN_F0R2_FB7_Msk
/** @brief Bit position of the `CAN_F0R2_FB8` field @def CAN_F0R2_FB8_Pos */
#define CAN_F0R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB8` field @def CAN_F0R2_FB8_Msk */
#define CAN_F0R2_FB8_Msk		REG_BIT_MASK(CAN_F0R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F0R2_FB8 */
#define CAN_F0R2_FB8			CAN_F0R2_FB8_Msk
/** @brief Bit position of the `CAN_F0R2_FB9` field @def CAN_F0R2_FB9_Pos */
#define CAN_F0R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB9` field @def CAN_F0R2_FB9_Msk */
#define CAN_F0R2_FB9_Msk		REG_BIT_MASK(CAN_F0R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F0R2_FB9 */
#define CAN_F0R2_FB9			CAN_F0R2_FB9_Msk
/** @brief Bit position of the `CAN_F0R2_FB10` field @def CAN_F0R2_FB10_Pos */
#define CAN_F0R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB10` field @def CAN_F0R2_FB10_Msk */
#define CAN_F0R2_FB10_Msk		REG_BIT_MASK(CAN_F0R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F0R2_FB10 */
#define CAN_F0R2_FB10			CAN_F0R2_FB10_Msk
/** @brief Bit position of the `CAN_F0R2_FB11` field @def CAN_F0R2_FB11_Pos */
#define CAN_F0R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB11` field @def CAN_F0R2_FB11_Msk */
#define CAN_F0R2_FB11_Msk		REG_BIT_MASK(CAN_F0R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F0R2_FB11 */
#define CAN_F0R2_FB11			CAN_F0R2_FB11_Msk
/** @brief Bit position of the `CAN_F0R2_FB12` field @def CAN_F0R2_FB12_Pos */
#define CAN_F0R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB12` field @def CAN_F0R2_FB12_Msk */
#define CAN_F0R2_FB12_Msk		REG_BIT_MASK(CAN_F0R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F0R2_FB12 */
#define CAN_F0R2_FB12			CAN_F0R2_FB12_Msk
/** @brief Bit position of the `CAN_F0R2_FB13` field @def CAN_F0R2_FB13_Pos */
#define CAN_F0R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB13` field @def CAN_F0R2_FB13_Msk */
#define CAN_F0R2_FB13_Msk		REG_BIT_MASK(CAN_F0R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F0R2_FB13 */
#define CAN_F0R2_FB13			CAN_F0R2_FB13_Msk
/** @brief Bit position of the `CAN_F0R2_FB14` field @def CAN_F0R2_FB14_Pos */
#define CAN_F0R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB14` field @def CAN_F0R2_FB14_Msk */
#define CAN_F0R2_FB14_Msk		REG_BIT_MASK(CAN_F0R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F0R2_FB14 */
#define CAN_F0R2_FB14			CAN_F0R2_FB14_Msk
/** @brief Bit position of the `CAN_F0R2_FB15` field @def CAN_F0R2_FB15_Pos */
#define CAN_F0R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB15` field @def CAN_F0R2_FB15_Msk */
#define CAN_F0R2_FB15_Msk		REG_BIT_MASK(CAN_F0R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F0R2_FB15 */
#define CAN_F0R2_FB15			CAN_F0R2_FB15_Msk
/** @brief Bit position of the `CAN_F0R2_FB16` field @def CAN_F0R2_FB16_Pos */
#define CAN_F0R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB16` field @def CAN_F0R2_FB16_Msk */
#define CAN_F0R2_FB16_Msk		REG_BIT_MASK(CAN_F0R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F0R2_FB16 */
#define CAN_F0R2_FB16			CAN_F0R2_FB16_Msk
/** @brief Bit position of the `CAN_F0R2_FB17` field @def CAN_F0R2_FB17_Pos */
#define CAN_F0R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB17` field @def CAN_F0R2_FB17_Msk */
#define CAN_F0R2_FB17_Msk		REG_BIT_MASK(CAN_F0R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F0R2_FB17 */
#define CAN_F0R2_FB17			CAN_F0R2_FB17_Msk
/** @brief Bit position of the `CAN_F0R2_FB18` field @def CAN_F0R2_FB18_Pos */
#define CAN_F0R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB18` field @def CAN_F0R2_FB18_Msk */
#define CAN_F0R2_FB18_Msk		REG_BIT_MASK(CAN_F0R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F0R2_FB18 */
#define CAN_F0R2_FB18			CAN_F0R2_FB18_Msk
/** @brief Bit position of the `CAN_F0R2_FB19` field @def CAN_F0R2_FB19_Pos */
#define CAN_F0R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB19` field @def CAN_F0R2_FB19_Msk */
#define CAN_F0R2_FB19_Msk		REG_BIT_MASK(CAN_F0R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F0R2_FB19 */
#define CAN_F0R2_FB19			CAN_F0R2_FB19_Msk
/** @brief Bit position of the `CAN_F0R2_FB20` field @def CAN_F0R2_FB20_Pos */
#define CAN_F0R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB20` field @def CAN_F0R2_FB20_Msk */
#define CAN_F0R2_FB20_Msk		REG_BIT_MASK(CAN_F0R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F0R2_FB20 */
#define CAN_F0R2_FB20			CAN_F0R2_FB20_Msk
/** @brief Bit position of the `CAN_F0R2_FB21` field @def CAN_F0R2_FB21_Pos */
#define CAN_F0R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB21` field @def CAN_F0R2_FB21_Msk */
#define CAN_F0R2_FB21_Msk		REG_BIT_MASK(CAN_F0R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F0R2_FB21 */
#define CAN_F0R2_FB21			CAN_F0R2_FB21_Msk
/** @brief Bit position of the `CAN_F0R2_FB22` field @def CAN_F0R2_FB22_Pos */
#define CAN_F0R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB22` field @def CAN_F0R2_FB22_Msk */
#define CAN_F0R2_FB22_Msk		REG_BIT_MASK(CAN_F0R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F0R2_FB22 */
#define CAN_F0R2_FB22			CAN_F0R2_FB22_Msk
/** @brief Bit position of the `CAN_F0R2_FB23` field @def CAN_F0R2_FB23_Pos */
#define CAN_F0R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB23` field @def CAN_F0R2_FB23_Msk */
#define CAN_F0R2_FB23_Msk		REG_BIT_MASK(CAN_F0R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F0R2_FB23 */
#define CAN_F0R2_FB23			CAN_F0R2_FB23_Msk
/** @brief Bit position of the `CAN_F0R2_FB24` field @def CAN_F0R2_FB24_Pos */
#define CAN_F0R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB24` field @def CAN_F0R2_FB24_Msk */
#define CAN_F0R2_FB24_Msk		REG_BIT_MASK(CAN_F0R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F0R2_FB24 */
#define CAN_F0R2_FB24			CAN_F0R2_FB24_Msk
/** @brief Bit position of the `CAN_F0R2_FB25` field @def CAN_F0R2_FB25_Pos */
#define CAN_F0R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB25` field @def CAN_F0R2_FB25_Msk */
#define CAN_F0R2_FB25_Msk		REG_BIT_MASK(CAN_F0R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F0R2_FB25 */
#define CAN_F0R2_FB25			CAN_F0R2_FB25_Msk
/** @brief Bit position of the `CAN_F0R2_FB26` field @def CAN_F0R2_FB26_Pos */
#define CAN_F0R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB26` field @def CAN_F0R2_FB26_Msk */
#define CAN_F0R2_FB26_Msk		REG_BIT_MASK(CAN_F0R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F0R2_FB26 */
#define CAN_F0R2_FB26			CAN_F0R2_FB26_Msk
/** @brief Bit position of the `CAN_F0R2_FB27` field @def CAN_F0R2_FB27_Pos */
#define CAN_F0R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB27` field @def CAN_F0R2_FB27_Msk */
#define CAN_F0R2_FB27_Msk		REG_BIT_MASK(CAN_F0R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F0R2_FB27 */
#define CAN_F0R2_FB27			CAN_F0R2_FB27_Msk
/** @brief Bit position of the `CAN_F0R2_FB28` field @def CAN_F0R2_FB28_Pos */
#define CAN_F0R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB28` field @def CAN_F0R2_FB28_Msk */
#define CAN_F0R2_FB28_Msk		REG_BIT_MASK(CAN_F0R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F0R2_FB28 */
#define CAN_F0R2_FB28			CAN_F0R2_FB28_Msk
/** @brief Bit position of the `CAN_F0R2_FB29` field @def CAN_F0R2_FB29_Pos */
#define CAN_F0R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB29` field @def CAN_F0R2_FB29_Msk */
#define CAN_F0R2_FB29_Msk		REG_BIT_MASK(CAN_F0R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F0R2_FB29 */
#define CAN_F0R2_FB29			CAN_F0R2_FB29_Msk
/** @brief Bit position of the `CAN_F0R2_FB30` field @def CAN_F0R2_FB30_Pos */
#define CAN_F0R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB30` field @def CAN_F0R2_FB30_Msk */
#define CAN_F0R2_FB30_Msk		REG_BIT_MASK(CAN_F0R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F0R2_FB30 */
#define CAN_F0R2_FB30			CAN_F0R2_FB30_Msk
/** @brief Bit position of the `CAN_F0R2_FB31` field @def CAN_F0R2_FB31_Pos */
#define CAN_F0R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F0R2_FB31` field @def CAN_F0R2_FB31_Msk */
#define CAN_F0R2_FB31_Msk		REG_BIT_MASK(CAN_F0R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F0R2_FB31 */
#define CAN_F0R2_FB31			CAN_F0R2_FB31_Msk

// ---------------------------------- CAN_F1R2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F1R2_FB0` field @def CAN_F1R2_FB0_Pos */
#define CAN_F1R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB0` field @def CAN_F1R2_FB0_Msk */
#define CAN_F1R2_FB0_Msk		REG_BIT_MASK(CAN_F1R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F1R2_FB0 */
#define CAN_F1R2_FB0			CAN_F1R2_FB0_Msk
/** @brief Bit position of the `CAN_F1R2_FB1` field @def CAN_F1R2_FB1_Pos */
#define CAN_F1R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB1` field @def CAN_F1R2_FB1_Msk */
#define CAN_F1R2_FB1_Msk		REG_BIT_MASK(CAN_F1R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F1R2_FB1 */
#define CAN_F1R2_FB1			CAN_F1R2_FB1_Msk
/** @brief Bit position of the `CAN_F1R2_FB2` field @def CAN_F1R2_FB2_Pos */
#define CAN_F1R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB2` field @def CAN_F1R2_FB2_Msk */
#define CAN_F1R2_FB2_Msk		REG_BIT_MASK(CAN_F1R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F1R2_FB2 */
#define CAN_F1R2_FB2			CAN_F1R2_FB2_Msk
/** @brief Bit position of the `CAN_F1R2_FB3` field @def CAN_F1R2_FB3_Pos */
#define CAN_F1R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB3` field @def CAN_F1R2_FB3_Msk */
#define CAN_F1R2_FB3_Msk		REG_BIT_MASK(CAN_F1R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F1R2_FB3 */
#define CAN_F1R2_FB3			CAN_F1R2_FB3_Msk
/** @brief Bit position of the `CAN_F1R2_FB4` field @def CAN_F1R2_FB4_Pos */
#define CAN_F1R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB4` field @def CAN_F1R2_FB4_Msk */
#define CAN_F1R2_FB4_Msk		REG_BIT_MASK(CAN_F1R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F1R2_FB4 */
#define CAN_F1R2_FB4			CAN_F1R2_FB4_Msk
/** @brief Bit position of the `CAN_F1R2_FB5` field @def CAN_F1R2_FB5_Pos */
#define CAN_F1R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB5` field @def CAN_F1R2_FB5_Msk */
#define CAN_F1R2_FB5_Msk		REG_BIT_MASK(CAN_F1R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F1R2_FB5 */
#define CAN_F1R2_FB5			CAN_F1R2_FB5_Msk
/** @brief Bit position of the `CAN_F1R2_FB6` field @def CAN_F1R2_FB6_Pos */
#define CAN_F1R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB6` field @def CAN_F1R2_FB6_Msk */
#define CAN_F1R2_FB6_Msk		REG_BIT_MASK(CAN_F1R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F1R2_FB6 */
#define CAN_F1R2_FB6			CAN_F1R2_FB6_Msk
/** @brief Bit position of the `CAN_F1R2_FB7` field @def CAN_F1R2_FB7_Pos */
#define CAN_F1R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB7` field @def CAN_F1R2_FB7_Msk */
#define CAN_F1R2_FB7_Msk		REG_BIT_MASK(CAN_F1R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F1R2_FB7 */
#define CAN_F1R2_FB7			CAN_F1R2_FB7_Msk
/** @brief Bit position of the `CAN_F1R2_FB8` field @def CAN_F1R2_FB8_Pos */
#define CAN_F1R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB8` field @def CAN_F1R2_FB8_Msk */
#define CAN_F1R2_FB8_Msk		REG_BIT_MASK(CAN_F1R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F1R2_FB8 */
#define CAN_F1R2_FB8			CAN_F1R2_FB8_Msk
/** @brief Bit position of the `CAN_F1R2_FB9` field @def CAN_F1R2_FB9_Pos */
#define CAN_F1R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB9` field @def CAN_F1R2_FB9_Msk */
#define CAN_F1R2_FB9_Msk		REG_BIT_MASK(CAN_F1R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F1R2_FB9 */
#define CAN_F1R2_FB9			CAN_F1R2_FB9_Msk
/** @brief Bit position of the `CAN_F1R2_FB10` field @def CAN_F1R2_FB10_Pos */
#define CAN_F1R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB10` field @def CAN_F1R2_FB10_Msk */
#define CAN_F1R2_FB10_Msk		REG_BIT_MASK(CAN_F1R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F1R2_FB10 */
#define CAN_F1R2_FB10			CAN_F1R2_FB10_Msk
/** @brief Bit position of the `CAN_F1R2_FB11` field @def CAN_F1R2_FB11_Pos */
#define CAN_F1R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB11` field @def CAN_F1R2_FB11_Msk */
#define CAN_F1R2_FB11_Msk		REG_BIT_MASK(CAN_F1R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F1R2_FB11 */
#define CAN_F1R2_FB11			CAN_F1R2_FB11_Msk
/** @brief Bit position of the `CAN_F1R2_FB12` field @def CAN_F1R2_FB12_Pos */
#define CAN_F1R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB12` field @def CAN_F1R2_FB12_Msk */
#define CAN_F1R2_FB12_Msk		REG_BIT_MASK(CAN_F1R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F1R2_FB12 */
#define CAN_F1R2_FB12			CAN_F1R2_FB12_Msk
/** @brief Bit position of the `CAN_F1R2_FB13` field @def CAN_F1R2_FB13_Pos */
#define CAN_F1R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB13` field @def CAN_F1R2_FB13_Msk */
#define CAN_F1R2_FB13_Msk		REG_BIT_MASK(CAN_F1R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F1R2_FB13 */
#define CAN_F1R2_FB13			CAN_F1R2_FB13_Msk
/** @brief Bit position of the `CAN_F1R2_FB14` field @def CAN_F1R2_FB14_Pos */
#define CAN_F1R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB14` field @def CAN_F1R2_FB14_Msk */
#define CAN_F1R2_FB14_Msk		REG_BIT_MASK(CAN_F1R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F1R2_FB14 */
#define CAN_F1R2_FB14			CAN_F1R2_FB14_Msk
/** @brief Bit position of the `CAN_F1R2_FB15` field @def CAN_F1R2_FB15_Pos */
#define CAN_F1R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB15` field @def CAN_F1R2_FB15_Msk */
#define CAN_F1R2_FB15_Msk		REG_BIT_MASK(CAN_F1R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F1R2_FB15 */
#define CAN_F1R2_FB15			CAN_F1R2_FB15_Msk
/** @brief Bit position of the `CAN_F1R2_FB16` field @def CAN_F1R2_FB16_Pos */
#define CAN_F1R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB16` field @def CAN_F1R2_FB16_Msk */
#define CAN_F1R2_FB16_Msk		REG_BIT_MASK(CAN_F1R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F1R2_FB16 */
#define CAN_F1R2_FB16			CAN_F1R2_FB16_Msk
/** @brief Bit position of the `CAN_F1R2_FB17` field @def CAN_F1R2_FB17_Pos */
#define CAN_F1R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB17` field @def CAN_F1R2_FB17_Msk */
#define CAN_F1R2_FB17_Msk		REG_BIT_MASK(CAN_F1R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F1R2_FB17 */
#define CAN_F1R2_FB17			CAN_F1R2_FB17_Msk
/** @brief Bit position of the `CAN_F1R2_FB18` field @def CAN_F1R2_FB18_Pos */
#define CAN_F1R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB18` field @def CAN_F1R2_FB18_Msk */
#define CAN_F1R2_FB18_Msk		REG_BIT_MASK(CAN_F1R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F1R2_FB18 */
#define CAN_F1R2_FB18			CAN_F1R2_FB18_Msk
/** @brief Bit position of the `CAN_F1R2_FB19` field @def CAN_F1R2_FB19_Pos */
#define CAN_F1R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB19` field @def CAN_F1R2_FB19_Msk */
#define CAN_F1R2_FB19_Msk		REG_BIT_MASK(CAN_F1R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F1R2_FB19 */
#define CAN_F1R2_FB19			CAN_F1R2_FB19_Msk
/** @brief Bit position of the `CAN_F1R2_FB20` field @def CAN_F1R2_FB20_Pos */
#define CAN_F1R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB20` field @def CAN_F1R2_FB20_Msk */
#define CAN_F1R2_FB20_Msk		REG_BIT_MASK(CAN_F1R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F1R2_FB20 */
#define CAN_F1R2_FB20			CAN_F1R2_FB20_Msk
/** @brief Bit position of the `CAN_F1R2_FB21` field @def CAN_F1R2_FB21_Pos */
#define CAN_F1R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB21` field @def CAN_F1R2_FB21_Msk */
#define CAN_F1R2_FB21_Msk		REG_BIT_MASK(CAN_F1R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F1R2_FB21 */
#define CAN_F1R2_FB21			CAN_F1R2_FB21_Msk
/** @brief Bit position of the `CAN_F1R2_FB22` field @def CAN_F1R2_FB22_Pos */
#define CAN_F1R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB22` field @def CAN_F1R2_FB22_Msk */
#define CAN_F1R2_FB22_Msk		REG_BIT_MASK(CAN_F1R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F1R2_FB22 */
#define CAN_F1R2_FB22			CAN_F1R2_FB22_Msk
/** @brief Bit position of the `CAN_F1R2_FB23` field @def CAN_F1R2_FB23_Pos */
#define CAN_F1R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB23` field @def CAN_F1R2_FB23_Msk */
#define CAN_F1R2_FB23_Msk		REG_BIT_MASK(CAN_F1R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F1R2_FB23 */
#define CAN_F1R2_FB23			CAN_F1R2_FB23_Msk
/** @brief Bit position of the `CAN_F1R2_FB24` field @def CAN_F1R2_FB24_Pos */
#define CAN_F1R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB24` field @def CAN_F1R2_FB24_Msk */
#define CAN_F1R2_FB24_Msk		REG_BIT_MASK(CAN_F1R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F1R2_FB24 */
#define CAN_F1R2_FB24			CAN_F1R2_FB24_Msk
/** @brief Bit position of the `CAN_F1R2_FB25` field @def CAN_F1R2_FB25_Pos */
#define CAN_F1R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB25` field @def CAN_F1R2_FB25_Msk */
#define CAN_F1R2_FB25_Msk		REG_BIT_MASK(CAN_F1R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F1R2_FB25 */
#define CAN_F1R2_FB25			CAN_F1R2_FB25_Msk
/** @brief Bit position of the `CAN_F1R2_FB26` field @def CAN_F1R2_FB26_Pos */
#define CAN_F1R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB26` field @def CAN_F1R2_FB26_Msk */
#define CAN_F1R2_FB26_Msk		REG_BIT_MASK(CAN_F1R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F1R2_FB26 */
#define CAN_F1R2_FB26			CAN_F1R2_FB26_Msk
/** @brief Bit position of the `CAN_F1R2_FB27` field @def CAN_F1R2_FB27_Pos */
#define CAN_F1R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB27` field @def CAN_F1R2_FB27_Msk */
#define CAN_F1R2_FB27_Msk		REG_BIT_MASK(CAN_F1R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F1R2_FB27 */
#define CAN_F1R2_FB27			CAN_F1R2_FB27_Msk
/** @brief Bit position of the `CAN_F1R2_FB28` field @def CAN_F1R2_FB28_Pos */
#define CAN_F1R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB28` field @def CAN_F1R2_FB28_Msk */
#define CAN_F1R2_FB28_Msk		REG_BIT_MASK(CAN_F1R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F1R2_FB28 */
#define CAN_F1R2_FB28			CAN_F1R2_FB28_Msk
/** @brief Bit position of the `CAN_F1R2_FB29` field @def CAN_F1R2_FB29_Pos */
#define CAN_F1R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB29` field @def CAN_F1R2_FB29_Msk */
#define CAN_F1R2_FB29_Msk		REG_BIT_MASK(CAN_F1R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F1R2_FB29 */
#define CAN_F1R2_FB29			CAN_F1R2_FB29_Msk
/** @brief Bit position of the `CAN_F1R2_FB30` field @def CAN_F1R2_FB30_Pos */
#define CAN_F1R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB30` field @def CAN_F1R2_FB30_Msk */
#define CAN_F1R2_FB30_Msk		REG_BIT_MASK(CAN_F1R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F1R2_FB30 */
#define CAN_F1R2_FB30			CAN_F1R2_FB30_Msk
/** @brief Bit position of the `CAN_F1R2_FB31` field @def CAN_F1R2_FB31_Pos */
#define CAN_F1R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F1R2_FB31` field @def CAN_F1R2_FB31_Msk */
#define CAN_F1R2_FB31_Msk		REG_BIT_MASK(CAN_F1R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F1R2_FB31 */
#define CAN_F1R2_FB31			CAN_F1R2_FB31_Msk

// ---------------------------------- CAN_F2R2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F2R2_FB0` field @def CAN_F2R2_FB0_Pos */
#define CAN_F2R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB0` field @def CAN_F2R2_FB0_Msk */
#define CAN_F2R2_FB0_Msk		REG_BIT_MASK(CAN_F2R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F2R2_FB0 */
#define CAN_F2R2_FB0			CAN_F2R2_FB0_Msk
/** @brief Bit position of the `CAN_F2R2_FB1` field @def CAN_F2R2_FB1_Pos */
#define CAN_F2R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB1` field @def CAN_F2R2_FB1_Msk */
#define CAN_F2R2_FB1_Msk		REG_BIT_MASK(CAN_F2R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F2R2_FB1 */
#define CAN_F2R2_FB1			CAN_F2R2_FB1_Msk
/** @brief Bit position of the `CAN_F2R2_FB2` field @def CAN_F2R2_FB2_Pos */
#define CAN_F2R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB2` field @def CAN_F2R2_FB2_Msk */
#define CAN_F2R2_FB2_Msk		REG_BIT_MASK(CAN_F2R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F2R2_FB2 */
#define CAN_F2R2_FB2			CAN_F2R2_FB2_Msk
/** @brief Bit position of the `CAN_F2R2_FB3` field @def CAN_F2R2_FB3_Pos */
#define CAN_F2R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB3` field @def CAN_F2R2_FB3_Msk */
#define CAN_F2R2_FB3_Msk		REG_BIT_MASK(CAN_F2R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F2R2_FB3 */
#define CAN_F2R2_FB3			CAN_F2R2_FB3_Msk
/** @brief Bit position of the `CAN_F2R2_FB4` field @def CAN_F2R2_FB4_Pos */
#define CAN_F2R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB4` field @def CAN_F2R2_FB4_Msk */
#define CAN_F2R2_FB4_Msk		REG_BIT_MASK(CAN_F2R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F2R2_FB4 */
#define CAN_F2R2_FB4			CAN_F2R2_FB4_Msk
/** @brief Bit position of the `CAN_F2R2_FB5` field @def CAN_F2R2_FB5_Pos */
#define CAN_F2R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB5` field @def CAN_F2R2_FB5_Msk */
#define CAN_F2R2_FB5_Msk		REG_BIT_MASK(CAN_F2R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F2R2_FB5 */
#define CAN_F2R2_FB5			CAN_F2R2_FB5_Msk
/** @brief Bit position of the `CAN_F2R2_FB6` field @def CAN_F2R2_FB6_Pos */
#define CAN_F2R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB6` field @def CAN_F2R2_FB6_Msk */
#define CAN_F2R2_FB6_Msk		REG_BIT_MASK(CAN_F2R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F2R2_FB6 */
#define CAN_F2R2_FB6			CAN_F2R2_FB6_Msk
/** @brief Bit position of the `CAN_F2R2_FB7` field @def CAN_F2R2_FB7_Pos */
#define CAN_F2R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB7` field @def CAN_F2R2_FB7_Msk */
#define CAN_F2R2_FB7_Msk		REG_BIT_MASK(CAN_F2R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F2R2_FB7 */
#define CAN_F2R2_FB7			CAN_F2R2_FB7_Msk
/** @brief Bit position of the `CAN_F2R2_FB8` field @def CAN_F2R2_FB8_Pos */
#define CAN_F2R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB8` field @def CAN_F2R2_FB8_Msk */
#define CAN_F2R2_FB8_Msk		REG_BIT_MASK(CAN_F2R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F2R2_FB8 */
#define CAN_F2R2_FB8			CAN_F2R2_FB8_Msk
/** @brief Bit position of the `CAN_F2R2_FB9` field @def CAN_F2R2_FB9_Pos */
#define CAN_F2R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB9` field @def CAN_F2R2_FB9_Msk */
#define CAN_F2R2_FB9_Msk		REG_BIT_MASK(CAN_F2R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F2R2_FB9 */
#define CAN_F2R2_FB9			CAN_F2R2_FB9_Msk
/** @brief Bit position of the `CAN_F2R2_FB10` field @def CAN_F2R2_FB10_Pos */
#define CAN_F2R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB10` field @def CAN_F2R2_FB10_Msk */
#define CAN_F2R2_FB10_Msk		REG_BIT_MASK(CAN_F2R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F2R2_FB10 */
#define CAN_F2R2_FB10			CAN_F2R2_FB10_Msk
/** @brief Bit position of the `CAN_F2R2_FB11` field @def CAN_F2R2_FB11_Pos */
#define CAN_F2R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB11` field @def CAN_F2R2_FB11_Msk */
#define CAN_F2R2_FB11_Msk		REG_BIT_MASK(CAN_F2R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F2R2_FB11 */
#define CAN_F2R2_FB11			CAN_F2R2_FB11_Msk
/** @brief Bit position of the `CAN_F2R2_FB12` field @def CAN_F2R2_FB12_Pos */
#define CAN_F2R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB12` field @def CAN_F2R2_FB12_Msk */
#define CAN_F2R2_FB12_Msk		REG_BIT_MASK(CAN_F2R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F2R2_FB12 */
#define CAN_F2R2_FB12			CAN_F2R2_FB12_Msk
/** @brief Bit position of the `CAN_F2R2_FB13` field @def CAN_F2R2_FB13_Pos */
#define CAN_F2R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB13` field @def CAN_F2R2_FB13_Msk */
#define CAN_F2R2_FB13_Msk		REG_BIT_MASK(CAN_F2R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F2R2_FB13 */
#define CAN_F2R2_FB13			CAN_F2R2_FB13_Msk
/** @brief Bit position of the `CAN_F2R2_FB14` field @def CAN_F2R2_FB14_Pos */
#define CAN_F2R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB14` field @def CAN_F2R2_FB14_Msk */
#define CAN_F2R2_FB14_Msk		REG_BIT_MASK(CAN_F2R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F2R2_FB14 */
#define CAN_F2R2_FB14			CAN_F2R2_FB14_Msk
/** @brief Bit position of the `CAN_F2R2_FB15` field @def CAN_F2R2_FB15_Pos */
#define CAN_F2R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB15` field @def CAN_F2R2_FB15_Msk */
#define CAN_F2R2_FB15_Msk		REG_BIT_MASK(CAN_F2R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F2R2_FB15 */
#define CAN_F2R2_FB15			CAN_F2R2_FB15_Msk
/** @brief Bit position of the `CAN_F2R2_FB16` field @def CAN_F2R2_FB16_Pos */
#define CAN_F2R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB16` field @def CAN_F2R2_FB16_Msk */
#define CAN_F2R2_FB16_Msk		REG_BIT_MASK(CAN_F2R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F2R2_FB16 */
#define CAN_F2R2_FB16			CAN_F2R2_FB16_Msk
/** @brief Bit position of the `CAN_F2R2_FB17` field @def CAN_F2R2_FB17_Pos */
#define CAN_F2R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB17` field @def CAN_F2R2_FB17_Msk */
#define CAN_F2R2_FB17_Msk		REG_BIT_MASK(CAN_F2R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F2R2_FB17 */
#define CAN_F2R2_FB17			CAN_F2R2_FB17_Msk
/** @brief Bit position of the `CAN_F2R2_FB18` field @def CAN_F2R2_FB18_Pos */
#define CAN_F2R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB18` field @def CAN_F2R2_FB18_Msk */
#define CAN_F2R2_FB18_Msk		REG_BIT_MASK(CAN_F2R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F2R2_FB18 */
#define CAN_F2R2_FB18			CAN_F2R2_FB18_Msk
/** @brief Bit position of the `CAN_F2R2_FB19` field @def CAN_F2R2_FB19_Pos */
#define CAN_F2R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB19` field @def CAN_F2R2_FB19_Msk */
#define CAN_F2R2_FB19_Msk		REG_BIT_MASK(CAN_F2R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F2R2_FB19 */
#define CAN_F2R2_FB19			CAN_F2R2_FB19_Msk
/** @brief Bit position of the `CAN_F2R2_FB20` field @def CAN_F2R2_FB20_Pos */
#define CAN_F2R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB20` field @def CAN_F2R2_FB20_Msk */
#define CAN_F2R2_FB20_Msk		REG_BIT_MASK(CAN_F2R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F2R2_FB20 */
#define CAN_F2R2_FB20			CAN_F2R2_FB20_Msk
/** @brief Bit position of the `CAN_F2R2_FB21` field @def CAN_F2R2_FB21_Pos */
#define CAN_F2R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB21` field @def CAN_F2R2_FB21_Msk */
#define CAN_F2R2_FB21_Msk		REG_BIT_MASK(CAN_F2R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F2R2_FB21 */
#define CAN_F2R2_FB21			CAN_F2R2_FB21_Msk
/** @brief Bit position of the `CAN_F2R2_FB22` field @def CAN_F2R2_FB22_Pos */
#define CAN_F2R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB22` field @def CAN_F2R2_FB22_Msk */
#define CAN_F2R2_FB22_Msk		REG_BIT_MASK(CAN_F2R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F2R2_FB22 */
#define CAN_F2R2_FB22			CAN_F2R2_FB22_Msk
/** @brief Bit position of the `CAN_F2R2_FB23` field @def CAN_F2R2_FB23_Pos */
#define CAN_F2R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB23` field @def CAN_F2R2_FB23_Msk */
#define CAN_F2R2_FB23_Msk		REG_BIT_MASK(CAN_F2R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F2R2_FB23 */
#define CAN_F2R2_FB23			CAN_F2R2_FB23_Msk
/** @brief Bit position of the `CAN_F2R2_FB24` field @def CAN_F2R2_FB24_Pos */
#define CAN_F2R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB24` field @def CAN_F2R2_FB24_Msk */
#define CAN_F2R2_FB24_Msk		REG_BIT_MASK(CAN_F2R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F2R2_FB24 */
#define CAN_F2R2_FB24			CAN_F2R2_FB24_Msk
/** @brief Bit position of the `CAN_F2R2_FB25` field @def CAN_F2R2_FB25_Pos */
#define CAN_F2R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB25` field @def CAN_F2R2_FB25_Msk */
#define CAN_F2R2_FB25_Msk		REG_BIT_MASK(CAN_F2R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F2R2_FB25 */
#define CAN_F2R2_FB25			CAN_F2R2_FB25_Msk
/** @brief Bit position of the `CAN_F2R2_FB26` field @def CAN_F2R2_FB26_Pos */
#define CAN_F2R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB26` field @def CAN_F2R2_FB26_Msk */
#define CAN_F2R2_FB26_Msk		REG_BIT_MASK(CAN_F2R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F2R2_FB26 */
#define CAN_F2R2_FB26			CAN_F2R2_FB26_Msk
/** @brief Bit position of the `CAN_F2R2_FB27` field @def CAN_F2R2_FB27_Pos */
#define CAN_F2R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB27` field @def CAN_F2R2_FB27_Msk */
#define CAN_F2R2_FB27_Msk		REG_BIT_MASK(CAN_F2R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F2R2_FB27 */
#define CAN_F2R2_FB27			CAN_F2R2_FB27_Msk
/** @brief Bit position of the `CAN_F2R2_FB28` field @def CAN_F2R2_FB28_Pos */
#define CAN_F2R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB28` field @def CAN_F2R2_FB28_Msk */
#define CAN_F2R2_FB28_Msk		REG_BIT_MASK(CAN_F2R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F2R2_FB28 */
#define CAN_F2R2_FB28			CAN_F2R2_FB28_Msk
/** @brief Bit position of the `CAN_F2R2_FB29` field @def CAN_F2R2_FB29_Pos */
#define CAN_F2R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB29` field @def CAN_F2R2_FB29_Msk */
#define CAN_F2R2_FB29_Msk		REG_BIT_MASK(CAN_F2R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F2R2_FB29 */
#define CAN_F2R2_FB29			CAN_F2R2_FB29_Msk
/** @brief Bit position of the `CAN_F2R2_FB30` field @def CAN_F2R2_FB30_Pos */
#define CAN_F2R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB30` field @def CAN_F2R2_FB30_Msk */
#define CAN_F2R2_FB30_Msk		REG_BIT_MASK(CAN_F2R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F2R2_FB30 */
#define CAN_F2R2_FB30			CAN_F2R2_FB30_Msk
/** @brief Bit position of the `CAN_F2R2_FB31` field @def CAN_F2R2_FB31_Pos */
#define CAN_F2R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F2R2_FB31` field @def CAN_F2R2_FB31_Msk */
#define CAN_F2R2_FB31_Msk		REG_BIT_MASK(CAN_F2R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F2R2_FB31 */
#define CAN_F2R2_FB31			CAN_F2R2_FB31_Msk

// ---------------------------------- CAN_F3R2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F3R2_FB0` field @def CAN_F3R2_FB0_Pos */
#define CAN_F3R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB0` field @def CAN_F3R2_FB0_Msk */
#define CAN_F3R2_FB0_Msk		REG_BIT_MASK(CAN_F3R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F3R2_FB0 */
#define CAN_F3R2_FB0			CAN_F3R2_FB0_Msk
/** @brief Bit position of the `CAN_F3R2_FB1` field @def CAN_F3R2_FB1_Pos */
#define CAN_F3R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB1` field @def CAN_F3R2_FB1_Msk */
#define CAN_F3R2_FB1_Msk		REG_BIT_MASK(CAN_F3R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F3R2_FB1 */
#define CAN_F3R2_FB1			CAN_F3R2_FB1_Msk
/** @brief Bit position of the `CAN_F3R2_FB2` field @def CAN_F3R2_FB2_Pos */
#define CAN_F3R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB2` field @def CAN_F3R2_FB2_Msk */
#define CAN_F3R2_FB2_Msk		REG_BIT_MASK(CAN_F3R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F3R2_FB2 */
#define CAN_F3R2_FB2			CAN_F3R2_FB2_Msk
/** @brief Bit position of the `CAN_F3R2_FB3` field @def CAN_F3R2_FB3_Pos */
#define CAN_F3R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB3` field @def CAN_F3R2_FB3_Msk */
#define CAN_F3R2_FB3_Msk		REG_BIT_MASK(CAN_F3R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F3R2_FB3 */
#define CAN_F3R2_FB3			CAN_F3R2_FB3_Msk
/** @brief Bit position of the `CAN_F3R2_FB4` field @def CAN_F3R2_FB4_Pos */
#define CAN_F3R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB4` field @def CAN_F3R2_FB4_Msk */
#define CAN_F3R2_FB4_Msk		REG_BIT_MASK(CAN_F3R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F3R2_FB4 */
#define CAN_F3R2_FB4			CAN_F3R2_FB4_Msk
/** @brief Bit position of the `CAN_F3R2_FB5` field @def CAN_F3R2_FB5_Pos */
#define CAN_F3R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB5` field @def CAN_F3R2_FB5_Msk */
#define CAN_F3R2_FB5_Msk		REG_BIT_MASK(CAN_F3R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F3R2_FB5 */
#define CAN_F3R2_FB5			CAN_F3R2_FB5_Msk
/** @brief Bit position of the `CAN_F3R2_FB6` field @def CAN_F3R2_FB6_Pos */
#define CAN_F3R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB6` field @def CAN_F3R2_FB6_Msk */
#define CAN_F3R2_FB6_Msk		REG_BIT_MASK(CAN_F3R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F3R2_FB6 */
#define CAN_F3R2_FB6			CAN_F3R2_FB6_Msk
/** @brief Bit position of the `CAN_F3R2_FB7` field @def CAN_F3R2_FB7_Pos */
#define CAN_F3R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB7` field @def CAN_F3R2_FB7_Msk */
#define CAN_F3R2_FB7_Msk		REG_BIT_MASK(CAN_F3R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F3R2_FB7 */
#define CAN_F3R2_FB7			CAN_F3R2_FB7_Msk
/** @brief Bit position of the `CAN_F3R2_FB8` field @def CAN_F3R2_FB8_Pos */
#define CAN_F3R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB8` field @def CAN_F3R2_FB8_Msk */
#define CAN_F3R2_FB8_Msk		REG_BIT_MASK(CAN_F3R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F3R2_FB8 */
#define CAN_F3R2_FB8			CAN_F3R2_FB8_Msk
/** @brief Bit position of the `CAN_F3R2_FB9` field @def CAN_F3R2_FB9_Pos */
#define CAN_F3R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB9` field @def CAN_F3R2_FB9_Msk */
#define CAN_F3R2_FB9_Msk		REG_BIT_MASK(CAN_F3R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F3R2_FB9 */
#define CAN_F3R2_FB9			CAN_F3R2_FB9_Msk
/** @brief Bit position of the `CAN_F3R2_FB10` field @def CAN_F3R2_FB10_Pos */
#define CAN_F3R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB10` field @def CAN_F3R2_FB10_Msk */
#define CAN_F3R2_FB10_Msk		REG_BIT_MASK(CAN_F3R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F3R2_FB10 */
#define CAN_F3R2_FB10			CAN_F3R2_FB10_Msk
/** @brief Bit position of the `CAN_F3R2_FB11` field @def CAN_F3R2_FB11_Pos */
#define CAN_F3R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB11` field @def CAN_F3R2_FB11_Msk */
#define CAN_F3R2_FB11_Msk		REG_BIT_MASK(CAN_F3R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F3R2_FB11 */
#define CAN_F3R2_FB11			CAN_F3R2_FB11_Msk
/** @brief Bit position of the `CAN_F3R2_FB12` field @def CAN_F3R2_FB12_Pos */
#define CAN_F3R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB12` field @def CAN_F3R2_FB12_Msk */
#define CAN_F3R2_FB12_Msk		REG_BIT_MASK(CAN_F3R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F3R2_FB12 */
#define CAN_F3R2_FB12			CAN_F3R2_FB12_Msk
/** @brief Bit position of the `CAN_F3R2_FB13` field @def CAN_F3R2_FB13_Pos */
#define CAN_F3R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB13` field @def CAN_F3R2_FB13_Msk */
#define CAN_F3R2_FB13_Msk		REG_BIT_MASK(CAN_F3R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F3R2_FB13 */
#define CAN_F3R2_FB13			CAN_F3R2_FB13_Msk
/** @brief Bit position of the `CAN_F3R2_FB14` field @def CAN_F3R2_FB14_Pos */
#define CAN_F3R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB14` field @def CAN_F3R2_FB14_Msk */
#define CAN_F3R2_FB14_Msk		REG_BIT_MASK(CAN_F3R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F3R2_FB14 */
#define CAN_F3R2_FB14			CAN_F3R2_FB14_Msk
/** @brief Bit position of the `CAN_F3R2_FB15` field @def CAN_F3R2_FB15_Pos */
#define CAN_F3R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB15` field @def CAN_F3R2_FB15_Msk */
#define CAN_F3R2_FB15_Msk		REG_BIT_MASK(CAN_F3R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F3R2_FB15 */
#define CAN_F3R2_FB15			CAN_F3R2_FB15_Msk
/** @brief Bit position of the `CAN_F3R2_FB16` field @def CAN_F3R2_FB16_Pos */
#define CAN_F3R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB16` field @def CAN_F3R2_FB16_Msk */
#define CAN_F3R2_FB16_Msk		REG_BIT_MASK(CAN_F3R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F3R2_FB16 */
#define CAN_F3R2_FB16			CAN_F3R2_FB16_Msk
/** @brief Bit position of the `CAN_F3R2_FB17` field @def CAN_F3R2_FB17_Pos */
#define CAN_F3R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB17` field @def CAN_F3R2_FB17_Msk */
#define CAN_F3R2_FB17_Msk		REG_BIT_MASK(CAN_F3R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F3R2_FB17 */
#define CAN_F3R2_FB17			CAN_F3R2_FB17_Msk
/** @brief Bit position of the `CAN_F3R2_FB18` field @def CAN_F3R2_FB18_Pos */
#define CAN_F3R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB18` field @def CAN_F3R2_FB18_Msk */
#define CAN_F3R2_FB18_Msk		REG_BIT_MASK(CAN_F3R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F3R2_FB18 */
#define CAN_F3R2_FB18			CAN_F3R2_FB18_Msk
/** @brief Bit position of the `CAN_F3R2_FB19` field @def CAN_F3R2_FB19_Pos */
#define CAN_F3R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB19` field @def CAN_F3R2_FB19_Msk */
#define CAN_F3R2_FB19_Msk		REG_BIT_MASK(CAN_F3R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F3R2_FB19 */
#define CAN_F3R2_FB19			CAN_F3R2_FB19_Msk
/** @brief Bit position of the `CAN_F3R2_FB20` field @def CAN_F3R2_FB20_Pos */
#define CAN_F3R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB20` field @def CAN_F3R2_FB20_Msk */
#define CAN_F3R2_FB20_Msk		REG_BIT_MASK(CAN_F3R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F3R2_FB20 */
#define CAN_F3R2_FB20			CAN_F3R2_FB20_Msk
/** @brief Bit position of the `CAN_F3R2_FB21` field @def CAN_F3R2_FB21_Pos */
#define CAN_F3R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB21` field @def CAN_F3R2_FB21_Msk */
#define CAN_F3R2_FB21_Msk		REG_BIT_MASK(CAN_F3R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F3R2_FB21 */
#define CAN_F3R2_FB21			CAN_F3R2_FB21_Msk
/** @brief Bit position of the `CAN_F3R2_FB22` field @def CAN_F3R2_FB22_Pos */
#define CAN_F3R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB22` field @def CAN_F3R2_FB22_Msk */
#define CAN_F3R2_FB22_Msk		REG_BIT_MASK(CAN_F3R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F3R2_FB22 */
#define CAN_F3R2_FB22			CAN_F3R2_FB22_Msk
/** @brief Bit position of the `CAN_F3R2_FB23` field @def CAN_F3R2_FB23_Pos */
#define CAN_F3R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB23` field @def CAN_F3R2_FB23_Msk */
#define CAN_F3R2_FB23_Msk		REG_BIT_MASK(CAN_F3R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F3R2_FB23 */
#define CAN_F3R2_FB23			CAN_F3R2_FB23_Msk
/** @brief Bit position of the `CAN_F3R2_FB24` field @def CAN_F3R2_FB24_Pos */
#define CAN_F3R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB24` field @def CAN_F3R2_FB24_Msk */
#define CAN_F3R2_FB24_Msk		REG_BIT_MASK(CAN_F3R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F3R2_FB24 */
#define CAN_F3R2_FB24			CAN_F3R2_FB24_Msk
/** @brief Bit position of the `CAN_F3R2_FB25` field @def CAN_F3R2_FB25_Pos */
#define CAN_F3R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB25` field @def CAN_F3R2_FB25_Msk */
#define CAN_F3R2_FB25_Msk		REG_BIT_MASK(CAN_F3R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F3R2_FB25 */
#define CAN_F3R2_FB25			CAN_F3R2_FB25_Msk
/** @brief Bit position of the `CAN_F3R2_FB26` field @def CAN_F3R2_FB26_Pos */
#define CAN_F3R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB26` field @def CAN_F3R2_FB26_Msk */
#define CAN_F3R2_FB26_Msk		REG_BIT_MASK(CAN_F3R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F3R2_FB26 */
#define CAN_F3R2_FB26			CAN_F3R2_FB26_Msk
/** @brief Bit position of the `CAN_F3R2_FB27` field @def CAN_F3R2_FB27_Pos */
#define CAN_F3R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB27` field @def CAN_F3R2_FB27_Msk */
#define CAN_F3R2_FB27_Msk		REG_BIT_MASK(CAN_F3R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F3R2_FB27 */
#define CAN_F3R2_FB27			CAN_F3R2_FB27_Msk
/** @brief Bit position of the `CAN_F3R2_FB28` field @def CAN_F3R2_FB28_Pos */
#define CAN_F3R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB28` field @def CAN_F3R2_FB28_Msk */
#define CAN_F3R2_FB28_Msk		REG_BIT_MASK(CAN_F3R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F3R2_FB28 */
#define CAN_F3R2_FB28			CAN_F3R2_FB28_Msk
/** @brief Bit position of the `CAN_F3R2_FB29` field @def CAN_F3R2_FB29_Pos */
#define CAN_F3R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB29` field @def CAN_F3R2_FB29_Msk */
#define CAN_F3R2_FB29_Msk		REG_BIT_MASK(CAN_F3R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F3R2_FB29 */
#define CAN_F3R2_FB29			CAN_F3R2_FB29_Msk
/** @brief Bit position of the `CAN_F3R2_FB30` field @def CAN_F3R2_FB30_Pos */
#define CAN_F3R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB30` field @def CAN_F3R2_FB30_Msk */
#define CAN_F3R2_FB30_Msk		REG_BIT_MASK(CAN_F3R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F3R2_FB30 */
#define CAN_F3R2_FB30			CAN_F3R2_FB30_Msk
/** @brief Bit position of the `CAN_F3R2_FB31` field @def CAN_F3R2_FB31_Pos */
#define CAN_F3R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F3R2_FB31` field @def CAN_F3R2_FB31_Msk */
#define CAN_F3R2_FB31_Msk		REG_BIT_MASK(CAN_F3R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F3R2_FB31 */
#define CAN_F3R2_FB31			CAN_F3R2_FB31_Msk

// ---------------------------------- CAN_F4R2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F4R2_FB0` field @def CAN_F4R2_FB0_Pos */
#define CAN_F4R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB0` field @def CAN_F4R2_FB0_Msk */
#define CAN_F4R2_FB0_Msk		REG_BIT_MASK(CAN_F4R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F4R2_FB0 */
#define CAN_F4R2_FB0			CAN_F4R2_FB0_Msk
/** @brief Bit position of the `CAN_F4R2_FB1` field @def CAN_F4R2_FB1_Pos */
#define CAN_F4R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB1` field @def CAN_F4R2_FB1_Msk */
#define CAN_F4R2_FB1_Msk		REG_BIT_MASK(CAN_F4R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F4R2_FB1 */
#define CAN_F4R2_FB1			CAN_F4R2_FB1_Msk
/** @brief Bit position of the `CAN_F4R2_FB2` field @def CAN_F4R2_FB2_Pos */
#define CAN_F4R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB2` field @def CAN_F4R2_FB2_Msk */
#define CAN_F4R2_FB2_Msk		REG_BIT_MASK(CAN_F4R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F4R2_FB2 */
#define CAN_F4R2_FB2			CAN_F4R2_FB2_Msk
/** @brief Bit position of the `CAN_F4R2_FB3` field @def CAN_F4R2_FB3_Pos */
#define CAN_F4R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB3` field @def CAN_F4R2_FB3_Msk */
#define CAN_F4R2_FB3_Msk		REG_BIT_MASK(CAN_F4R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F4R2_FB3 */
#define CAN_F4R2_FB3			CAN_F4R2_FB3_Msk
/** @brief Bit position of the `CAN_F4R2_FB4` field @def CAN_F4R2_FB4_Pos */
#define CAN_F4R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB4` field @def CAN_F4R2_FB4_Msk */
#define CAN_F4R2_FB4_Msk		REG_BIT_MASK(CAN_F4R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F4R2_FB4 */
#define CAN_F4R2_FB4			CAN_F4R2_FB4_Msk
/** @brief Bit position of the `CAN_F4R2_FB5` field @def CAN_F4R2_FB5_Pos */
#define CAN_F4R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB5` field @def CAN_F4R2_FB5_Msk */
#define CAN_F4R2_FB5_Msk		REG_BIT_MASK(CAN_F4R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F4R2_FB5 */
#define CAN_F4R2_FB5			CAN_F4R2_FB5_Msk
/** @brief Bit position of the `CAN_F4R2_FB6` field @def CAN_F4R2_FB6_Pos */
#define CAN_F4R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB6` field @def CAN_F4R2_FB6_Msk */
#define CAN_F4R2_FB6_Msk		REG_BIT_MASK(CAN_F4R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F4R2_FB6 */
#define CAN_F4R2_FB6			CAN_F4R2_FB6_Msk
/** @brief Bit position of the `CAN_F4R2_FB7` field @def CAN_F4R2_FB7_Pos */
#define CAN_F4R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB7` field @def CAN_F4R2_FB7_Msk */
#define CAN_F4R2_FB7_Msk		REG_BIT_MASK(CAN_F4R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F4R2_FB7 */
#define CAN_F4R2_FB7			CAN_F4R2_FB7_Msk
/** @brief Bit position of the `CAN_F4R2_FB8` field @def CAN_F4R2_FB8_Pos */
#define CAN_F4R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB8` field @def CAN_F4R2_FB8_Msk */
#define CAN_F4R2_FB8_Msk		REG_BIT_MASK(CAN_F4R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F4R2_FB8 */
#define CAN_F4R2_FB8			CAN_F4R2_FB8_Msk
/** @brief Bit position of the `CAN_F4R2_FB9` field @def CAN_F4R2_FB9_Pos */
#define CAN_F4R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB9` field @def CAN_F4R2_FB9_Msk */
#define CAN_F4R2_FB9_Msk		REG_BIT_MASK(CAN_F4R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F4R2_FB9 */
#define CAN_F4R2_FB9			CAN_F4R2_FB9_Msk
/** @brief Bit position of the `CAN_F4R2_FB10` field @def CAN_F4R2_FB10_Pos */
#define CAN_F4R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB10` field @def CAN_F4R2_FB10_Msk */
#define CAN_F4R2_FB10_Msk		REG_BIT_MASK(CAN_F4R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F4R2_FB10 */
#define CAN_F4R2_FB10			CAN_F4R2_FB10_Msk
/** @brief Bit position of the `CAN_F4R2_FB11` field @def CAN_F4R2_FB11_Pos */
#define CAN_F4R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB11` field @def CAN_F4R2_FB11_Msk */
#define CAN_F4R2_FB11_Msk		REG_BIT_MASK(CAN_F4R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F4R2_FB11 */
#define CAN_F4R2_FB11			CAN_F4R2_FB11_Msk
/** @brief Bit position of the `CAN_F4R2_FB12` field @def CAN_F4R2_FB12_Pos */
#define CAN_F4R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB12` field @def CAN_F4R2_FB12_Msk */
#define CAN_F4R2_FB12_Msk		REG_BIT_MASK(CAN_F4R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F4R2_FB12 */
#define CAN_F4R2_FB12			CAN_F4R2_FB12_Msk
/** @brief Bit position of the `CAN_F4R2_FB13` field @def CAN_F4R2_FB13_Pos */
#define CAN_F4R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB13` field @def CAN_F4R2_FB13_Msk */
#define CAN_F4R2_FB13_Msk		REG_BIT_MASK(CAN_F4R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F4R2_FB13 */
#define CAN_F4R2_FB13			CAN_F4R2_FB13_Msk
/** @brief Bit position of the `CAN_F4R2_FB14` field @def CAN_F4R2_FB14_Pos */
#define CAN_F4R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB14` field @def CAN_F4R2_FB14_Msk */
#define CAN_F4R2_FB14_Msk		REG_BIT_MASK(CAN_F4R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F4R2_FB14 */
#define CAN_F4R2_FB14			CAN_F4R2_FB14_Msk
/** @brief Bit position of the `CAN_F4R2_FB15` field @def CAN_F4R2_FB15_Pos */
#define CAN_F4R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB15` field @def CAN_F4R2_FB15_Msk */
#define CAN_F4R2_FB15_Msk		REG_BIT_MASK(CAN_F4R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F4R2_FB15 */
#define CAN_F4R2_FB15			CAN_F4R2_FB15_Msk
/** @brief Bit position of the `CAN_F4R2_FB16` field @def CAN_F4R2_FB16_Pos */
#define CAN_F4R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB16` field @def CAN_F4R2_FB16_Msk */
#define CAN_F4R2_FB16_Msk		REG_BIT_MASK(CAN_F4R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F4R2_FB16 */
#define CAN_F4R2_FB16			CAN_F4R2_FB16_Msk
/** @brief Bit position of the `CAN_F4R2_FB17` field @def CAN_F4R2_FB17_Pos */
#define CAN_F4R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB17` field @def CAN_F4R2_FB17_Msk */
#define CAN_F4R2_FB17_Msk		REG_BIT_MASK(CAN_F4R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F4R2_FB17 */
#define CAN_F4R2_FB17			CAN_F4R2_FB17_Msk
/** @brief Bit position of the `CAN_F4R2_FB18` field @def CAN_F4R2_FB18_Pos */
#define CAN_F4R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB18` field @def CAN_F4R2_FB18_Msk */
#define CAN_F4R2_FB18_Msk		REG_BIT_MASK(CAN_F4R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F4R2_FB18 */
#define CAN_F4R2_FB18			CAN_F4R2_FB18_Msk
/** @brief Bit position of the `CAN_F4R2_FB19` field @def CAN_F4R2_FB19_Pos */
#define CAN_F4R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB19` field @def CAN_F4R2_FB19_Msk */
#define CAN_F4R2_FB19_Msk		REG_BIT_MASK(CAN_F4R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F4R2_FB19 */
#define CAN_F4R2_FB19			CAN_F4R2_FB19_Msk
/** @brief Bit position of the `CAN_F4R2_FB20` field @def CAN_F4R2_FB20_Pos */
#define CAN_F4R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB20` field @def CAN_F4R2_FB20_Msk */
#define CAN_F4R2_FB20_Msk		REG_BIT_MASK(CAN_F4R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F4R2_FB20 */
#define CAN_F4R2_FB20			CAN_F4R2_FB20_Msk
/** @brief Bit position of the `CAN_F4R2_FB21` field @def CAN_F4R2_FB21_Pos */
#define CAN_F4R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB21` field @def CAN_F4R2_FB21_Msk */
#define CAN_F4R2_FB21_Msk		REG_BIT_MASK(CAN_F4R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F4R2_FB21 */
#define CAN_F4R2_FB21			CAN_F4R2_FB21_Msk
/** @brief Bit position of the `CAN_F4R2_FB22` field @def CAN_F4R2_FB22_Pos */
#define CAN_F4R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB22` field @def CAN_F4R2_FB22_Msk */
#define CAN_F4R2_FB22_Msk		REG_BIT_MASK(CAN_F4R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F4R2_FB22 */
#define CAN_F4R2_FB22			CAN_F4R2_FB22_Msk
/** @brief Bit position of the `CAN_F4R2_FB23` field @def CAN_F4R2_FB23_Pos */
#define CAN_F4R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB23` field @def CAN_F4R2_FB23_Msk */
#define CAN_F4R2_FB23_Msk		REG_BIT_MASK(CAN_F4R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F4R2_FB23 */
#define CAN_F4R2_FB23			CAN_F4R2_FB23_Msk
/** @brief Bit position of the `CAN_F4R2_FB24` field @def CAN_F4R2_FB24_Pos */
#define CAN_F4R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB24` field @def CAN_F4R2_FB24_Msk */
#define CAN_F4R2_FB24_Msk		REG_BIT_MASK(CAN_F4R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F4R2_FB24 */
#define CAN_F4R2_FB24			CAN_F4R2_FB24_Msk
/** @brief Bit position of the `CAN_F4R2_FB25` field @def CAN_F4R2_FB25_Pos */
#define CAN_F4R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB25` field @def CAN_F4R2_FB25_Msk */
#define CAN_F4R2_FB25_Msk		REG_BIT_MASK(CAN_F4R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F4R2_FB25 */
#define CAN_F4R2_FB25			CAN_F4R2_FB25_Msk
/** @brief Bit position of the `CAN_F4R2_FB26` field @def CAN_F4R2_FB26_Pos */
#define CAN_F4R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB26` field @def CAN_F4R2_FB26_Msk */
#define CAN_F4R2_FB26_Msk		REG_BIT_MASK(CAN_F4R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F4R2_FB26 */
#define CAN_F4R2_FB26			CAN_F4R2_FB26_Msk
/** @brief Bit position of the `CAN_F4R2_FB27` field @def CAN_F4R2_FB27_Pos */
#define CAN_F4R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB27` field @def CAN_F4R2_FB27_Msk */
#define CAN_F4R2_FB27_Msk		REG_BIT_MASK(CAN_F4R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F4R2_FB27 */
#define CAN_F4R2_FB27			CAN_F4R2_FB27_Msk
/** @brief Bit position of the `CAN_F4R2_FB28` field @def CAN_F4R2_FB28_Pos */
#define CAN_F4R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB28` field @def CAN_F4R2_FB28_Msk */
#define CAN_F4R2_FB28_Msk		REG_BIT_MASK(CAN_F4R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F4R2_FB28 */
#define CAN_F4R2_FB28			CAN_F4R2_FB28_Msk
/** @brief Bit position of the `CAN_F4R2_FB29` field @def CAN_F4R2_FB29_Pos */
#define CAN_F4R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB29` field @def CAN_F4R2_FB29_Msk */
#define CAN_F4R2_FB29_Msk		REG_BIT_MASK(CAN_F4R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F4R2_FB29 */
#define CAN_F4R2_FB29			CAN_F4R2_FB29_Msk
/** @brief Bit position of the `CAN_F4R2_FB30` field @def CAN_F4R2_FB30_Pos */
#define CAN_F4R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB30` field @def CAN_F4R2_FB30_Msk */
#define CAN_F4R2_FB30_Msk		REG_BIT_MASK(CAN_F4R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F4R2_FB30 */
#define CAN_F4R2_FB30			CAN_F4R2_FB30_Msk
/** @brief Bit position of the `CAN_F4R2_FB31` field @def CAN_F4R2_FB31_Pos */
#define CAN_F4R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F4R2_FB31` field @def CAN_F4R2_FB31_Msk */
#define CAN_F4R2_FB31_Msk		REG_BIT_MASK(CAN_F4R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F4R2_FB31 */
#define CAN_F4R2_FB31			CAN_F4R2_FB31_Msk

// ---------------------------------- CAN_F5R2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F5R2_FB0` field @def CAN_F5R2_FB0_Pos */
#define CAN_F5R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB0` field @def CAN_F5R2_FB0_Msk */
#define CAN_F5R2_FB0_Msk		REG_BIT_MASK(CAN_F5R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F5R2_FB0 */
#define CAN_F5R2_FB0			CAN_F5R2_FB0_Msk
/** @brief Bit position of the `CAN_F5R2_FB1` field @def CAN_F5R2_FB1_Pos */
#define CAN_F5R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB1` field @def CAN_F5R2_FB1_Msk */
#define CAN_F5R2_FB1_Msk		REG_BIT_MASK(CAN_F5R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F5R2_FB1 */
#define CAN_F5R2_FB1			CAN_F5R2_FB1_Msk
/** @brief Bit position of the `CAN_F5R2_FB2` field @def CAN_F5R2_FB2_Pos */
#define CAN_F5R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB2` field @def CAN_F5R2_FB2_Msk */
#define CAN_F5R2_FB2_Msk		REG_BIT_MASK(CAN_F5R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F5R2_FB2 */
#define CAN_F5R2_FB2			CAN_F5R2_FB2_Msk
/** @brief Bit position of the `CAN_F5R2_FB3` field @def CAN_F5R2_FB3_Pos */
#define CAN_F5R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB3` field @def CAN_F5R2_FB3_Msk */
#define CAN_F5R2_FB3_Msk		REG_BIT_MASK(CAN_F5R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F5R2_FB3 */
#define CAN_F5R2_FB3			CAN_F5R2_FB3_Msk
/** @brief Bit position of the `CAN_F5R2_FB4` field @def CAN_F5R2_FB4_Pos */
#define CAN_F5R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB4` field @def CAN_F5R2_FB4_Msk */
#define CAN_F5R2_FB4_Msk		REG_BIT_MASK(CAN_F5R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F5R2_FB4 */
#define CAN_F5R2_FB4			CAN_F5R2_FB4_Msk
/** @brief Bit position of the `CAN_F5R2_FB5` field @def CAN_F5R2_FB5_Pos */
#define CAN_F5R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB5` field @def CAN_F5R2_FB5_Msk */
#define CAN_F5R2_FB5_Msk		REG_BIT_MASK(CAN_F5R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F5R2_FB5 */
#define CAN_F5R2_FB5			CAN_F5R2_FB5_Msk
/** @brief Bit position of the `CAN_F5R2_FB6` field @def CAN_F5R2_FB6_Pos */
#define CAN_F5R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB6` field @def CAN_F5R2_FB6_Msk */
#define CAN_F5R2_FB6_Msk		REG_BIT_MASK(CAN_F5R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F5R2_FB6 */
#define CAN_F5R2_FB6			CAN_F5R2_FB6_Msk
/** @brief Bit position of the `CAN_F5R2_FB7` field @def CAN_F5R2_FB7_Pos */
#define CAN_F5R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB7` field @def CAN_F5R2_FB7_Msk */
#define CAN_F5R2_FB7_Msk		REG_BIT_MASK(CAN_F5R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F5R2_FB7 */
#define CAN_F5R2_FB7			CAN_F5R2_FB7_Msk
/** @brief Bit position of the `CAN_F5R2_FB8` field @def CAN_F5R2_FB8_Pos */
#define CAN_F5R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB8` field @def CAN_F5R2_FB8_Msk */
#define CAN_F5R2_FB8_Msk		REG_BIT_MASK(CAN_F5R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F5R2_FB8 */
#define CAN_F5R2_FB8			CAN_F5R2_FB8_Msk
/** @brief Bit position of the `CAN_F5R2_FB9` field @def CAN_F5R2_FB9_Pos */
#define CAN_F5R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB9` field @def CAN_F5R2_FB9_Msk */
#define CAN_F5R2_FB9_Msk		REG_BIT_MASK(CAN_F5R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F5R2_FB9 */
#define CAN_F5R2_FB9			CAN_F5R2_FB9_Msk
/** @brief Bit position of the `CAN_F5R2_FB10` field @def CAN_F5R2_FB10_Pos */
#define CAN_F5R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB10` field @def CAN_F5R2_FB10_Msk */
#define CAN_F5R2_FB10_Msk		REG_BIT_MASK(CAN_F5R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F5R2_FB10 */
#define CAN_F5R2_FB10			CAN_F5R2_FB10_Msk
/** @brief Bit position of the `CAN_F5R2_FB11` field @def CAN_F5R2_FB11_Pos */
#define CAN_F5R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB11` field @def CAN_F5R2_FB11_Msk */
#define CAN_F5R2_FB11_Msk		REG_BIT_MASK(CAN_F5R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F5R2_FB11 */
#define CAN_F5R2_FB11			CAN_F5R2_FB11_Msk
/** @brief Bit position of the `CAN_F5R2_FB12` field @def CAN_F5R2_FB12_Pos */
#define CAN_F5R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB12` field @def CAN_F5R2_FB12_Msk */
#define CAN_F5R2_FB12_Msk		REG_BIT_MASK(CAN_F5R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F5R2_FB12 */
#define CAN_F5R2_FB12			CAN_F5R2_FB12_Msk
/** @brief Bit position of the `CAN_F5R2_FB13` field @def CAN_F5R2_FB13_Pos */
#define CAN_F5R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB13` field @def CAN_F5R2_FB13_Msk */
#define CAN_F5R2_FB13_Msk		REG_BIT_MASK(CAN_F5R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F5R2_FB13 */
#define CAN_F5R2_FB13			CAN_F5R2_FB13_Msk
/** @brief Bit position of the `CAN_F5R2_FB14` field @def CAN_F5R2_FB14_Pos */
#define CAN_F5R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB14` field @def CAN_F5R2_FB14_Msk */
#define CAN_F5R2_FB14_Msk		REG_BIT_MASK(CAN_F5R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F5R2_FB14 */
#define CAN_F5R2_FB14			CAN_F5R2_FB14_Msk
/** @brief Bit position of the `CAN_F5R2_FB15` field @def CAN_F5R2_FB15_Pos */
#define CAN_F5R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB15` field @def CAN_F5R2_FB15_Msk */
#define CAN_F5R2_FB15_Msk		REG_BIT_MASK(CAN_F5R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F5R2_FB15 */
#define CAN_F5R2_FB15			CAN_F5R2_FB15_Msk
/** @brief Bit position of the `CAN_F5R2_FB16` field @def CAN_F5R2_FB16_Pos */
#define CAN_F5R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB16` field @def CAN_F5R2_FB16_Msk */
#define CAN_F5R2_FB16_Msk		REG_BIT_MASK(CAN_F5R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F5R2_FB16 */
#define CAN_F5R2_FB16			CAN_F5R2_FB16_Msk
/** @brief Bit position of the `CAN_F5R2_FB17` field @def CAN_F5R2_FB17_Pos */
#define CAN_F5R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB17` field @def CAN_F5R2_FB17_Msk */
#define CAN_F5R2_FB17_Msk		REG_BIT_MASK(CAN_F5R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F5R2_FB17 */
#define CAN_F5R2_FB17			CAN_F5R2_FB17_Msk
/** @brief Bit position of the `CAN_F5R2_FB18` field @def CAN_F5R2_FB18_Pos */
#define CAN_F5R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB18` field @def CAN_F5R2_FB18_Msk */
#define CAN_F5R2_FB18_Msk		REG_BIT_MASK(CAN_F5R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F5R2_FB18 */
#define CAN_F5R2_FB18			CAN_F5R2_FB18_Msk
/** @brief Bit position of the `CAN_F5R2_FB19` field @def CAN_F5R2_FB19_Pos */
#define CAN_F5R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB19` field @def CAN_F5R2_FB19_Msk */
#define CAN_F5R2_FB19_Msk		REG_BIT_MASK(CAN_F5R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F5R2_FB19 */
#define CAN_F5R2_FB19			CAN_F5R2_FB19_Msk
/** @brief Bit position of the `CAN_F5R2_FB20` field @def CAN_F5R2_FB20_Pos */
#define CAN_F5R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB20` field @def CAN_F5R2_FB20_Msk */
#define CAN_F5R2_FB20_Msk		REG_BIT_MASK(CAN_F5R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F5R2_FB20 */
#define CAN_F5R2_FB20			CAN_F5R2_FB20_Msk
/** @brief Bit position of the `CAN_F5R2_FB21` field @def CAN_F5R2_FB21_Pos */
#define CAN_F5R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB21` field @def CAN_F5R2_FB21_Msk */
#define CAN_F5R2_FB21_Msk		REG_BIT_MASK(CAN_F5R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F5R2_FB21 */
#define CAN_F5R2_FB21			CAN_F5R2_FB21_Msk
/** @brief Bit position of the `CAN_F5R2_FB22` field @def CAN_F5R2_FB22_Pos */
#define CAN_F5R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB22` field @def CAN_F5R2_FB22_Msk */
#define CAN_F5R2_FB22_Msk		REG_BIT_MASK(CAN_F5R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F5R2_FB22 */
#define CAN_F5R2_FB22			CAN_F5R2_FB22_Msk
/** @brief Bit position of the `CAN_F5R2_FB23` field @def CAN_F5R2_FB23_Pos */
#define CAN_F5R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB23` field @def CAN_F5R2_FB23_Msk */
#define CAN_F5R2_FB23_Msk		REG_BIT_MASK(CAN_F5R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F5R2_FB23 */
#define CAN_F5R2_FB23			CAN_F5R2_FB23_Msk
/** @brief Bit position of the `CAN_F5R2_FB24` field @def CAN_F5R2_FB24_Pos */
#define CAN_F5R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB24` field @def CAN_F5R2_FB24_Msk */
#define CAN_F5R2_FB24_Msk		REG_BIT_MASK(CAN_F5R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F5R2_FB24 */
#define CAN_F5R2_FB24			CAN_F5R2_FB24_Msk
/** @brief Bit position of the `CAN_F5R2_FB25` field @def CAN_F5R2_FB25_Pos */
#define CAN_F5R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB25` field @def CAN_F5R2_FB25_Msk */
#define CAN_F5R2_FB25_Msk		REG_BIT_MASK(CAN_F5R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F5R2_FB25 */
#define CAN_F5R2_FB25			CAN_F5R2_FB25_Msk
/** @brief Bit position of the `CAN_F5R2_FB26` field @def CAN_F5R2_FB26_Pos */
#define CAN_F5R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB26` field @def CAN_F5R2_FB26_Msk */
#define CAN_F5R2_FB26_Msk		REG_BIT_MASK(CAN_F5R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F5R2_FB26 */
#define CAN_F5R2_FB26			CAN_F5R2_FB26_Msk
/** @brief Bit position of the `CAN_F5R2_FB27` field @def CAN_F5R2_FB27_Pos */
#define CAN_F5R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB27` field @def CAN_F5R2_FB27_Msk */
#define CAN_F5R2_FB27_Msk		REG_BIT_MASK(CAN_F5R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F5R2_FB27 */
#define CAN_F5R2_FB27			CAN_F5R2_FB27_Msk
/** @brief Bit position of the `CAN_F5R2_FB28` field @def CAN_F5R2_FB28_Pos */
#define CAN_F5R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB28` field @def CAN_F5R2_FB28_Msk */
#define CAN_F5R2_FB28_Msk		REG_BIT_MASK(CAN_F5R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F5R2_FB28 */
#define CAN_F5R2_FB28			CAN_F5R2_FB28_Msk
/** @brief Bit position of the `CAN_F5R2_FB29` field @def CAN_F5R2_FB29_Pos */
#define CAN_F5R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB29` field @def CAN_F5R2_FB29_Msk */
#define CAN_F5R2_FB29_Msk		REG_BIT_MASK(CAN_F5R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F5R2_FB29 */
#define CAN_F5R2_FB29			CAN_F5R2_FB29_Msk
/** @brief Bit position of the `CAN_F5R2_FB30` field @def CAN_F5R2_FB30_Pos */
#define CAN_F5R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB30` field @def CAN_F5R2_FB30_Msk */
#define CAN_F5R2_FB30_Msk		REG_BIT_MASK(CAN_F5R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F5R2_FB30 */
#define CAN_F5R2_FB30			CAN_F5R2_FB30_Msk
/** @brief Bit position of the `CAN_F5R2_FB31` field @def CAN_F5R2_FB31_Pos */
#define CAN_F5R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F5R2_FB31` field @def CAN_F5R2_FB31_Msk */
#define CAN_F5R2_FB31_Msk		REG_BIT_MASK(CAN_F5R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F5R2_FB31 */
#define CAN_F5R2_FB31			CAN_F5R2_FB31_Msk

// ---------------------------------- CAN_F6R2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F6R2_FB0` field @def CAN_F6R2_FB0_Pos */
#define CAN_F6R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB0` field @def CAN_F6R2_FB0_Msk */
#define CAN_F6R2_FB0_Msk		REG_BIT_MASK(CAN_F6R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F6R2_FB0 */
#define CAN_F6R2_FB0			CAN_F6R2_FB0_Msk
/** @brief Bit position of the `CAN_F6R2_FB1` field @def CAN_F6R2_FB1_Pos */
#define CAN_F6R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB1` field @def CAN_F6R2_FB1_Msk */
#define CAN_F6R2_FB1_Msk		REG_BIT_MASK(CAN_F6R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F6R2_FB1 */
#define CAN_F6R2_FB1			CAN_F6R2_FB1_Msk
/** @brief Bit position of the `CAN_F6R2_FB2` field @def CAN_F6R2_FB2_Pos */
#define CAN_F6R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB2` field @def CAN_F6R2_FB2_Msk */
#define CAN_F6R2_FB2_Msk		REG_BIT_MASK(CAN_F6R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F6R2_FB2 */
#define CAN_F6R2_FB2			CAN_F6R2_FB2_Msk
/** @brief Bit position of the `CAN_F6R2_FB3` field @def CAN_F6R2_FB3_Pos */
#define CAN_F6R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB3` field @def CAN_F6R2_FB3_Msk */
#define CAN_F6R2_FB3_Msk		REG_BIT_MASK(CAN_F6R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F6R2_FB3 */
#define CAN_F6R2_FB3			CAN_F6R2_FB3_Msk
/** @brief Bit position of the `CAN_F6R2_FB4` field @def CAN_F6R2_FB4_Pos */
#define CAN_F6R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB4` field @def CAN_F6R2_FB4_Msk */
#define CAN_F6R2_FB4_Msk		REG_BIT_MASK(CAN_F6R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F6R2_FB4 */
#define CAN_F6R2_FB4			CAN_F6R2_FB4_Msk
/** @brief Bit position of the `CAN_F6R2_FB5` field @def CAN_F6R2_FB5_Pos */
#define CAN_F6R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB5` field @def CAN_F6R2_FB5_Msk */
#define CAN_F6R2_FB5_Msk		REG_BIT_MASK(CAN_F6R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F6R2_FB5 */
#define CAN_F6R2_FB5			CAN_F6R2_FB5_Msk
/** @brief Bit position of the `CAN_F6R2_FB6` field @def CAN_F6R2_FB6_Pos */
#define CAN_F6R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB6` field @def CAN_F6R2_FB6_Msk */
#define CAN_F6R2_FB6_Msk		REG_BIT_MASK(CAN_F6R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F6R2_FB6 */
#define CAN_F6R2_FB6			CAN_F6R2_FB6_Msk
/** @brief Bit position of the `CAN_F6R2_FB7` field @def CAN_F6R2_FB7_Pos */
#define CAN_F6R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB7` field @def CAN_F6R2_FB7_Msk */
#define CAN_F6R2_FB7_Msk		REG_BIT_MASK(CAN_F6R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F6R2_FB7 */
#define CAN_F6R2_FB7			CAN_F6R2_FB7_Msk
/** @brief Bit position of the `CAN_F6R2_FB8` field @def CAN_F6R2_FB8_Pos */
#define CAN_F6R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB8` field @def CAN_F6R2_FB8_Msk */
#define CAN_F6R2_FB8_Msk		REG_BIT_MASK(CAN_F6R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F6R2_FB8 */
#define CAN_F6R2_FB8			CAN_F6R2_FB8_Msk
/** @brief Bit position of the `CAN_F6R2_FB9` field @def CAN_F6R2_FB9_Pos */
#define CAN_F6R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB9` field @def CAN_F6R2_FB9_Msk */
#define CAN_F6R2_FB9_Msk		REG_BIT_MASK(CAN_F6R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F6R2_FB9 */
#define CAN_F6R2_FB9			CAN_F6R2_FB9_Msk
/** @brief Bit position of the `CAN_F6R2_FB10` field @def CAN_F6R2_FB10_Pos */
#define CAN_F6R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB10` field @def CAN_F6R2_FB10_Msk */
#define CAN_F6R2_FB10_Msk		REG_BIT_MASK(CAN_F6R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F6R2_FB10 */
#define CAN_F6R2_FB10			CAN_F6R2_FB10_Msk
/** @brief Bit position of the `CAN_F6R2_FB11` field @def CAN_F6R2_FB11_Pos */
#define CAN_F6R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB11` field @def CAN_F6R2_FB11_Msk */
#define CAN_F6R2_FB11_Msk		REG_BIT_MASK(CAN_F6R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F6R2_FB11 */
#define CAN_F6R2_FB11			CAN_F6R2_FB11_Msk
/** @brief Bit position of the `CAN_F6R2_FB12` field @def CAN_F6R2_FB12_Pos */
#define CAN_F6R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB12` field @def CAN_F6R2_FB12_Msk */
#define CAN_F6R2_FB12_Msk		REG_BIT_MASK(CAN_F6R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F6R2_FB12 */
#define CAN_F6R2_FB12			CAN_F6R2_FB12_Msk
/** @brief Bit position of the `CAN_F6R2_FB13` field @def CAN_F6R2_FB13_Pos */
#define CAN_F6R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB13` field @def CAN_F6R2_FB13_Msk */
#define CAN_F6R2_FB13_Msk		REG_BIT_MASK(CAN_F6R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F6R2_FB13 */
#define CAN_F6R2_FB13			CAN_F6R2_FB13_Msk
/** @brief Bit position of the `CAN_F6R2_FB14` field @def CAN_F6R2_FB14_Pos */
#define CAN_F6R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB14` field @def CAN_F6R2_FB14_Msk */
#define CAN_F6R2_FB14_Msk		REG_BIT_MASK(CAN_F6R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F6R2_FB14 */
#define CAN_F6R2_FB14			CAN_F6R2_FB14_Msk
/** @brief Bit position of the `CAN_F6R2_FB15` field @def CAN_F6R2_FB15_Pos */
#define CAN_F6R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB15` field @def CAN_F6R2_FB15_Msk */
#define CAN_F6R2_FB15_Msk		REG_BIT_MASK(CAN_F6R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F6R2_FB15 */
#define CAN_F6R2_FB15			CAN_F6R2_FB15_Msk
/** @brief Bit position of the `CAN_F6R2_FB16` field @def CAN_F6R2_FB16_Pos */
#define CAN_F6R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB16` field @def CAN_F6R2_FB16_Msk */
#define CAN_F6R2_FB16_Msk		REG_BIT_MASK(CAN_F6R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F6R2_FB16 */
#define CAN_F6R2_FB16			CAN_F6R2_FB16_Msk
/** @brief Bit position of the `CAN_F6R2_FB17` field @def CAN_F6R2_FB17_Pos */
#define CAN_F6R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB17` field @def CAN_F6R2_FB17_Msk */
#define CAN_F6R2_FB17_Msk		REG_BIT_MASK(CAN_F6R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F6R2_FB17 */
#define CAN_F6R2_FB17			CAN_F6R2_FB17_Msk
/** @brief Bit position of the `CAN_F6R2_FB18` field @def CAN_F6R2_FB18_Pos */
#define CAN_F6R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB18` field @def CAN_F6R2_FB18_Msk */
#define CAN_F6R2_FB18_Msk		REG_BIT_MASK(CAN_F6R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F6R2_FB18 */
#define CAN_F6R2_FB18			CAN_F6R2_FB18_Msk
/** @brief Bit position of the `CAN_F6R2_FB19` field @def CAN_F6R2_FB19_Pos */
#define CAN_F6R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB19` field @def CAN_F6R2_FB19_Msk */
#define CAN_F6R2_FB19_Msk		REG_BIT_MASK(CAN_F6R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F6R2_FB19 */
#define CAN_F6R2_FB19			CAN_F6R2_FB19_Msk
/** @brief Bit position of the `CAN_F6R2_FB20` field @def CAN_F6R2_FB20_Pos */
#define CAN_F6R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB20` field @def CAN_F6R2_FB20_Msk */
#define CAN_F6R2_FB20_Msk		REG_BIT_MASK(CAN_F6R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F6R2_FB20 */
#define CAN_F6R2_FB20			CAN_F6R2_FB20_Msk
/** @brief Bit position of the `CAN_F6R2_FB21` field @def CAN_F6R2_FB21_Pos */
#define CAN_F6R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB21` field @def CAN_F6R2_FB21_Msk */
#define CAN_F6R2_FB21_Msk		REG_BIT_MASK(CAN_F6R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F6R2_FB21 */
#define CAN_F6R2_FB21			CAN_F6R2_FB21_Msk
/** @brief Bit position of the `CAN_F6R2_FB22` field @def CAN_F6R2_FB22_Pos */
#define CAN_F6R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB22` field @def CAN_F6R2_FB22_Msk */
#define CAN_F6R2_FB22_Msk		REG_BIT_MASK(CAN_F6R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F6R2_FB22 */
#define CAN_F6R2_FB22			CAN_F6R2_FB22_Msk
/** @brief Bit position of the `CAN_F6R2_FB23` field @def CAN_F6R2_FB23_Pos */
#define CAN_F6R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB23` field @def CAN_F6R2_FB23_Msk */
#define CAN_F6R2_FB23_Msk		REG_BIT_MASK(CAN_F6R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F6R2_FB23 */
#define CAN_F6R2_FB23			CAN_F6R2_FB23_Msk
/** @brief Bit position of the `CAN_F6R2_FB24` field @def CAN_F6R2_FB24_Pos */
#define CAN_F6R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB24` field @def CAN_F6R2_FB24_Msk */
#define CAN_F6R2_FB24_Msk		REG_BIT_MASK(CAN_F6R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F6R2_FB24 */
#define CAN_F6R2_FB24			CAN_F6R2_FB24_Msk
/** @brief Bit position of the `CAN_F6R2_FB25` field @def CAN_F6R2_FB25_Pos */
#define CAN_F6R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB25` field @def CAN_F6R2_FB25_Msk */
#define CAN_F6R2_FB25_Msk		REG_BIT_MASK(CAN_F6R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F6R2_FB25 */
#define CAN_F6R2_FB25			CAN_F6R2_FB25_Msk
/** @brief Bit position of the `CAN_F6R2_FB26` field @def CAN_F6R2_FB26_Pos */
#define CAN_F6R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB26` field @def CAN_F6R2_FB26_Msk */
#define CAN_F6R2_FB26_Msk		REG_BIT_MASK(CAN_F6R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F6R2_FB26 */
#define CAN_F6R2_FB26			CAN_F6R2_FB26_Msk
/** @brief Bit position of the `CAN_F6R2_FB27` field @def CAN_F6R2_FB27_Pos */
#define CAN_F6R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB27` field @def CAN_F6R2_FB27_Msk */
#define CAN_F6R2_FB27_Msk		REG_BIT_MASK(CAN_F6R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F6R2_FB27 */
#define CAN_F6R2_FB27			CAN_F6R2_FB27_Msk
/** @brief Bit position of the `CAN_F6R2_FB28` field @def CAN_F6R2_FB28_Pos */
#define CAN_F6R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB28` field @def CAN_F6R2_FB28_Msk */
#define CAN_F6R2_FB28_Msk		REG_BIT_MASK(CAN_F6R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F6R2_FB28 */
#define CAN_F6R2_FB28			CAN_F6R2_FB28_Msk
/** @brief Bit position of the `CAN_F6R2_FB29` field @def CAN_F6R2_FB29_Pos */
#define CAN_F6R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB29` field @def CAN_F6R2_FB29_Msk */
#define CAN_F6R2_FB29_Msk		REG_BIT_MASK(CAN_F6R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F6R2_FB29 */
#define CAN_F6R2_FB29			CAN_F6R2_FB29_Msk
/** @brief Bit position of the `CAN_F6R2_FB30` field @def CAN_F6R2_FB30_Pos */
#define CAN_F6R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB30` field @def CAN_F6R2_FB30_Msk */
#define CAN_F6R2_FB30_Msk		REG_BIT_MASK(CAN_F6R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F6R2_FB30 */
#define CAN_F6R2_FB30			CAN_F6R2_FB30_Msk
/** @brief Bit position of the `CAN_F6R2_FB31` field @def CAN_F6R2_FB31_Pos */
#define CAN_F6R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F6R2_FB31` field @def CAN_F6R2_FB31_Msk */
#define CAN_F6R2_FB31_Msk		REG_BIT_MASK(CAN_F6R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F6R2_FB31 */
#define CAN_F6R2_FB31			CAN_F6R2_FB31_Msk

// ---------------------------------- CAN_F7R2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F7R2_FB0` field @def CAN_F7R2_FB0_Pos */
#define CAN_F7R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB0` field @def CAN_F7R2_FB0_Msk */
#define CAN_F7R2_FB0_Msk		REG_BIT_MASK(CAN_F7R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F7R2_FB0 */
#define CAN_F7R2_FB0			CAN_F7R2_FB0_Msk
/** @brief Bit position of the `CAN_F7R2_FB1` field @def CAN_F7R2_FB1_Pos */
#define CAN_F7R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB1` field @def CAN_F7R2_FB1_Msk */
#define CAN_F7R2_FB1_Msk		REG_BIT_MASK(CAN_F7R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F7R2_FB1 */
#define CAN_F7R2_FB1			CAN_F7R2_FB1_Msk
/** @brief Bit position of the `CAN_F7R2_FB2` field @def CAN_F7R2_FB2_Pos */
#define CAN_F7R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB2` field @def CAN_F7R2_FB2_Msk */
#define CAN_F7R2_FB2_Msk		REG_BIT_MASK(CAN_F7R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F7R2_FB2 */
#define CAN_F7R2_FB2			CAN_F7R2_FB2_Msk
/** @brief Bit position of the `CAN_F7R2_FB3` field @def CAN_F7R2_FB3_Pos */
#define CAN_F7R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB3` field @def CAN_F7R2_FB3_Msk */
#define CAN_F7R2_FB3_Msk		REG_BIT_MASK(CAN_F7R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F7R2_FB3 */
#define CAN_F7R2_FB3			CAN_F7R2_FB3_Msk
/** @brief Bit position of the `CAN_F7R2_FB4` field @def CAN_F7R2_FB4_Pos */
#define CAN_F7R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB4` field @def CAN_F7R2_FB4_Msk */
#define CAN_F7R2_FB4_Msk		REG_BIT_MASK(CAN_F7R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F7R2_FB4 */
#define CAN_F7R2_FB4			CAN_F7R2_FB4_Msk
/** @brief Bit position of the `CAN_F7R2_FB5` field @def CAN_F7R2_FB5_Pos */
#define CAN_F7R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB5` field @def CAN_F7R2_FB5_Msk */
#define CAN_F7R2_FB5_Msk		REG_BIT_MASK(CAN_F7R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F7R2_FB5 */
#define CAN_F7R2_FB5			CAN_F7R2_FB5_Msk
/** @brief Bit position of the `CAN_F7R2_FB6` field @def CAN_F7R2_FB6_Pos */
#define CAN_F7R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB6` field @def CAN_F7R2_FB6_Msk */
#define CAN_F7R2_FB6_Msk		REG_BIT_MASK(CAN_F7R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F7R2_FB6 */
#define CAN_F7R2_FB6			CAN_F7R2_FB6_Msk
/** @brief Bit position of the `CAN_F7R2_FB7` field @def CAN_F7R2_FB7_Pos */
#define CAN_F7R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB7` field @def CAN_F7R2_FB7_Msk */
#define CAN_F7R2_FB7_Msk		REG_BIT_MASK(CAN_F7R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F7R2_FB7 */
#define CAN_F7R2_FB7			CAN_F7R2_FB7_Msk
/** @brief Bit position of the `CAN_F7R2_FB8` field @def CAN_F7R2_FB8_Pos */
#define CAN_F7R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB8` field @def CAN_F7R2_FB8_Msk */
#define CAN_F7R2_FB8_Msk		REG_BIT_MASK(CAN_F7R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F7R2_FB8 */
#define CAN_F7R2_FB8			CAN_F7R2_FB8_Msk
/** @brief Bit position of the `CAN_F7R2_FB9` field @def CAN_F7R2_FB9_Pos */
#define CAN_F7R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB9` field @def CAN_F7R2_FB9_Msk */
#define CAN_F7R2_FB9_Msk		REG_BIT_MASK(CAN_F7R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F7R2_FB9 */
#define CAN_F7R2_FB9			CAN_F7R2_FB9_Msk
/** @brief Bit position of the `CAN_F7R2_FB10` field @def CAN_F7R2_FB10_Pos */
#define CAN_F7R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB10` field @def CAN_F7R2_FB10_Msk */
#define CAN_F7R2_FB10_Msk		REG_BIT_MASK(CAN_F7R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F7R2_FB10 */
#define CAN_F7R2_FB10			CAN_F7R2_FB10_Msk
/** @brief Bit position of the `CAN_F7R2_FB11` field @def CAN_F7R2_FB11_Pos */
#define CAN_F7R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB11` field @def CAN_F7R2_FB11_Msk */
#define CAN_F7R2_FB11_Msk		REG_BIT_MASK(CAN_F7R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F7R2_FB11 */
#define CAN_F7R2_FB11			CAN_F7R2_FB11_Msk
/** @brief Bit position of the `CAN_F7R2_FB12` field @def CAN_F7R2_FB12_Pos */
#define CAN_F7R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB12` field @def CAN_F7R2_FB12_Msk */
#define CAN_F7R2_FB12_Msk		REG_BIT_MASK(CAN_F7R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F7R2_FB12 */
#define CAN_F7R2_FB12			CAN_F7R2_FB12_Msk
/** @brief Bit position of the `CAN_F7R2_FB13` field @def CAN_F7R2_FB13_Pos */
#define CAN_F7R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB13` field @def CAN_F7R2_FB13_Msk */
#define CAN_F7R2_FB13_Msk		REG_BIT_MASK(CAN_F7R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F7R2_FB13 */
#define CAN_F7R2_FB13			CAN_F7R2_FB13_Msk
/** @brief Bit position of the `CAN_F7R2_FB14` field @def CAN_F7R2_FB14_Pos */
#define CAN_F7R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB14` field @def CAN_F7R2_FB14_Msk */
#define CAN_F7R2_FB14_Msk		REG_BIT_MASK(CAN_F7R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F7R2_FB14 */
#define CAN_F7R2_FB14			CAN_F7R2_FB14_Msk
/** @brief Bit position of the `CAN_F7R2_FB15` field @def CAN_F7R2_FB15_Pos */
#define CAN_F7R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB15` field @def CAN_F7R2_FB15_Msk */
#define CAN_F7R2_FB15_Msk		REG_BIT_MASK(CAN_F7R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F7R2_FB15 */
#define CAN_F7R2_FB15			CAN_F7R2_FB15_Msk
/** @brief Bit position of the `CAN_F7R2_FB16` field @def CAN_F7R2_FB16_Pos */
#define CAN_F7R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB16` field @def CAN_F7R2_FB16_Msk */
#define CAN_F7R2_FB16_Msk		REG_BIT_MASK(CAN_F7R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F7R2_FB16 */
#define CAN_F7R2_FB16			CAN_F7R2_FB16_Msk
/** @brief Bit position of the `CAN_F7R2_FB17` field @def CAN_F7R2_FB17_Pos */
#define CAN_F7R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB17` field @def CAN_F7R2_FB17_Msk */
#define CAN_F7R2_FB17_Msk		REG_BIT_MASK(CAN_F7R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F7R2_FB17 */
#define CAN_F7R2_FB17			CAN_F7R2_FB17_Msk
/** @brief Bit position of the `CAN_F7R2_FB18` field @def CAN_F7R2_FB18_Pos */
#define CAN_F7R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB18` field @def CAN_F7R2_FB18_Msk */
#define CAN_F7R2_FB18_Msk		REG_BIT_MASK(CAN_F7R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F7R2_FB18 */
#define CAN_F7R2_FB18			CAN_F7R2_FB18_Msk
/** @brief Bit position of the `CAN_F7R2_FB19` field @def CAN_F7R2_FB19_Pos */
#define CAN_F7R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB19` field @def CAN_F7R2_FB19_Msk */
#define CAN_F7R2_FB19_Msk		REG_BIT_MASK(CAN_F7R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F7R2_FB19 */
#define CAN_F7R2_FB19			CAN_F7R2_FB19_Msk
/** @brief Bit position of the `CAN_F7R2_FB20` field @def CAN_F7R2_FB20_Pos */
#define CAN_F7R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB20` field @def CAN_F7R2_FB20_Msk */
#define CAN_F7R2_FB20_Msk		REG_BIT_MASK(CAN_F7R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F7R2_FB20 */
#define CAN_F7R2_FB20			CAN_F7R2_FB20_Msk
/** @brief Bit position of the `CAN_F7R2_FB21` field @def CAN_F7R2_FB21_Pos */
#define CAN_F7R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB21` field @def CAN_F7R2_FB21_Msk */
#define CAN_F7R2_FB21_Msk		REG_BIT_MASK(CAN_F7R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F7R2_FB21 */
#define CAN_F7R2_FB21			CAN_F7R2_FB21_Msk
/** @brief Bit position of the `CAN_F7R2_FB22` field @def CAN_F7R2_FB22_Pos */
#define CAN_F7R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB22` field @def CAN_F7R2_FB22_Msk */
#define CAN_F7R2_FB22_Msk		REG_BIT_MASK(CAN_F7R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F7R2_FB22 */
#define CAN_F7R2_FB22			CAN_F7R2_FB22_Msk
/** @brief Bit position of the `CAN_F7R2_FB23` field @def CAN_F7R2_FB23_Pos */
#define CAN_F7R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB23` field @def CAN_F7R2_FB23_Msk */
#define CAN_F7R2_FB23_Msk		REG_BIT_MASK(CAN_F7R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F7R2_FB23 */
#define CAN_F7R2_FB23			CAN_F7R2_FB23_Msk
/** @brief Bit position of the `CAN_F7R2_FB24` field @def CAN_F7R2_FB24_Pos */
#define CAN_F7R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB24` field @def CAN_F7R2_FB24_Msk */
#define CAN_F7R2_FB24_Msk		REG_BIT_MASK(CAN_F7R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F7R2_FB24 */
#define CAN_F7R2_FB24			CAN_F7R2_FB24_Msk
/** @brief Bit position of the `CAN_F7R2_FB25` field @def CAN_F7R2_FB25_Pos */
#define CAN_F7R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB25` field @def CAN_F7R2_FB25_Msk */
#define CAN_F7R2_FB25_Msk		REG_BIT_MASK(CAN_F7R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F7R2_FB25 */
#define CAN_F7R2_FB25			CAN_F7R2_FB25_Msk
/** @brief Bit position of the `CAN_F7R2_FB26` field @def CAN_F7R2_FB26_Pos */
#define CAN_F7R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB26` field @def CAN_F7R2_FB26_Msk */
#define CAN_F7R2_FB26_Msk		REG_BIT_MASK(CAN_F7R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F7R2_FB26 */
#define CAN_F7R2_FB26			CAN_F7R2_FB26_Msk
/** @brief Bit position of the `CAN_F7R2_FB27` field @def CAN_F7R2_FB27_Pos */
#define CAN_F7R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB27` field @def CAN_F7R2_FB27_Msk */
#define CAN_F7R2_FB27_Msk		REG_BIT_MASK(CAN_F7R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F7R2_FB27 */
#define CAN_F7R2_FB27			CAN_F7R2_FB27_Msk
/** @brief Bit position of the `CAN_F7R2_FB28` field @def CAN_F7R2_FB28_Pos */
#define CAN_F7R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB28` field @def CAN_F7R2_FB28_Msk */
#define CAN_F7R2_FB28_Msk		REG_BIT_MASK(CAN_F7R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F7R2_FB28 */
#define CAN_F7R2_FB28			CAN_F7R2_FB28_Msk
/** @brief Bit position of the `CAN_F7R2_FB29` field @def CAN_F7R2_FB29_Pos */
#define CAN_F7R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB29` field @def CAN_F7R2_FB29_Msk */
#define CAN_F7R2_FB29_Msk		REG_BIT_MASK(CAN_F7R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F7R2_FB29 */
#define CAN_F7R2_FB29			CAN_F7R2_FB29_Msk
/** @brief Bit position of the `CAN_F7R2_FB30` field @def CAN_F7R2_FB30_Pos */
#define CAN_F7R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB30` field @def CAN_F7R2_FB30_Msk */
#define CAN_F7R2_FB30_Msk		REG_BIT_MASK(CAN_F7R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F7R2_FB30 */
#define CAN_F7R2_FB30			CAN_F7R2_FB30_Msk
/** @brief Bit position of the `CAN_F7R2_FB31` field @def CAN_F7R2_FB31_Pos */
#define CAN_F7R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F7R2_FB31` field @def CAN_F7R2_FB31_Msk */
#define CAN_F7R2_FB31_Msk		REG_BIT_MASK(CAN_F7R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F7R2_FB31 */
#define CAN_F7R2_FB31			CAN_F7R2_FB31_Msk

// ---------------------------------- CAN_F8R2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F8R2_FB0` field @def CAN_F8R2_FB0_Pos */
#define CAN_F8R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB0` field @def CAN_F8R2_FB0_Msk */
#define CAN_F8R2_FB0_Msk		REG_BIT_MASK(CAN_F8R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F8R2_FB0 */
#define CAN_F8R2_FB0			CAN_F8R2_FB0_Msk
/** @brief Bit position of the `CAN_F8R2_FB1` field @def CAN_F8R2_FB1_Pos */
#define CAN_F8R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB1` field @def CAN_F8R2_FB1_Msk */
#define CAN_F8R2_FB1_Msk		REG_BIT_MASK(CAN_F8R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F8R2_FB1 */
#define CAN_F8R2_FB1			CAN_F8R2_FB1_Msk
/** @brief Bit position of the `CAN_F8R2_FB2` field @def CAN_F8R2_FB2_Pos */
#define CAN_F8R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB2` field @def CAN_F8R2_FB2_Msk */
#define CAN_F8R2_FB2_Msk		REG_BIT_MASK(CAN_F8R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F8R2_FB2 */
#define CAN_F8R2_FB2			CAN_F8R2_FB2_Msk
/** @brief Bit position of the `CAN_F8R2_FB3` field @def CAN_F8R2_FB3_Pos */
#define CAN_F8R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB3` field @def CAN_F8R2_FB3_Msk */
#define CAN_F8R2_FB3_Msk		REG_BIT_MASK(CAN_F8R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F8R2_FB3 */
#define CAN_F8R2_FB3			CAN_F8R2_FB3_Msk
/** @brief Bit position of the `CAN_F8R2_FB4` field @def CAN_F8R2_FB4_Pos */
#define CAN_F8R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB4` field @def CAN_F8R2_FB4_Msk */
#define CAN_F8R2_FB4_Msk		REG_BIT_MASK(CAN_F8R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F8R2_FB4 */
#define CAN_F8R2_FB4			CAN_F8R2_FB4_Msk
/** @brief Bit position of the `CAN_F8R2_FB5` field @def CAN_F8R2_FB5_Pos */
#define CAN_F8R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB5` field @def CAN_F8R2_FB5_Msk */
#define CAN_F8R2_FB5_Msk		REG_BIT_MASK(CAN_F8R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F8R2_FB5 */
#define CAN_F8R2_FB5			CAN_F8R2_FB5_Msk
/** @brief Bit position of the `CAN_F8R2_FB6` field @def CAN_F8R2_FB6_Pos */
#define CAN_F8R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB6` field @def CAN_F8R2_FB6_Msk */
#define CAN_F8R2_FB6_Msk		REG_BIT_MASK(CAN_F8R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F8R2_FB6 */
#define CAN_F8R2_FB6			CAN_F8R2_FB6_Msk
/** @brief Bit position of the `CAN_F8R2_FB7` field @def CAN_F8R2_FB7_Pos */
#define CAN_F8R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB7` field @def CAN_F8R2_FB7_Msk */
#define CAN_F8R2_FB7_Msk		REG_BIT_MASK(CAN_F8R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F8R2_FB7 */
#define CAN_F8R2_FB7			CAN_F8R2_FB7_Msk
/** @brief Bit position of the `CAN_F8R2_FB8` field @def CAN_F8R2_FB8_Pos */
#define CAN_F8R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB8` field @def CAN_F8R2_FB8_Msk */
#define CAN_F8R2_FB8_Msk		REG_BIT_MASK(CAN_F8R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F8R2_FB8 */
#define CAN_F8R2_FB8			CAN_F8R2_FB8_Msk
/** @brief Bit position of the `CAN_F8R2_FB9` field @def CAN_F8R2_FB9_Pos */
#define CAN_F8R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB9` field @def CAN_F8R2_FB9_Msk */
#define CAN_F8R2_FB9_Msk		REG_BIT_MASK(CAN_F8R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F8R2_FB9 */
#define CAN_F8R2_FB9			CAN_F8R2_FB9_Msk
/** @brief Bit position of the `CAN_F8R2_FB10` field @def CAN_F8R2_FB10_Pos */
#define CAN_F8R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB10` field @def CAN_F8R2_FB10_Msk */
#define CAN_F8R2_FB10_Msk		REG_BIT_MASK(CAN_F8R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F8R2_FB10 */
#define CAN_F8R2_FB10			CAN_F8R2_FB10_Msk
/** @brief Bit position of the `CAN_F8R2_FB11` field @def CAN_F8R2_FB11_Pos */
#define CAN_F8R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB11` field @def CAN_F8R2_FB11_Msk */
#define CAN_F8R2_FB11_Msk		REG_BIT_MASK(CAN_F8R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F8R2_FB11 */
#define CAN_F8R2_FB11			CAN_F8R2_FB11_Msk
/** @brief Bit position of the `CAN_F8R2_FB12` field @def CAN_F8R2_FB12_Pos */
#define CAN_F8R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB12` field @def CAN_F8R2_FB12_Msk */
#define CAN_F8R2_FB12_Msk		REG_BIT_MASK(CAN_F8R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F8R2_FB12 */
#define CAN_F8R2_FB12			CAN_F8R2_FB12_Msk
/** @brief Bit position of the `CAN_F8R2_FB13` field @def CAN_F8R2_FB13_Pos */
#define CAN_F8R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB13` field @def CAN_F8R2_FB13_Msk */
#define CAN_F8R2_FB13_Msk		REG_BIT_MASK(CAN_F8R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F8R2_FB13 */
#define CAN_F8R2_FB13			CAN_F8R2_FB13_Msk
/** @brief Bit position of the `CAN_F8R2_FB14` field @def CAN_F8R2_FB14_Pos */
#define CAN_F8R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB14` field @def CAN_F8R2_FB14_Msk */
#define CAN_F8R2_FB14_Msk		REG_BIT_MASK(CAN_F8R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F8R2_FB14 */
#define CAN_F8R2_FB14			CAN_F8R2_FB14_Msk
/** @brief Bit position of the `CAN_F8R2_FB15` field @def CAN_F8R2_FB15_Pos */
#define CAN_F8R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB15` field @def CAN_F8R2_FB15_Msk */
#define CAN_F8R2_FB15_Msk		REG_BIT_MASK(CAN_F8R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F8R2_FB15 */
#define CAN_F8R2_FB15			CAN_F8R2_FB15_Msk
/** @brief Bit position of the `CAN_F8R2_FB16` field @def CAN_F8R2_FB16_Pos */
#define CAN_F8R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB16` field @def CAN_F8R2_FB16_Msk */
#define CAN_F8R2_FB16_Msk		REG_BIT_MASK(CAN_F8R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F8R2_FB16 */
#define CAN_F8R2_FB16			CAN_F8R2_FB16_Msk
/** @brief Bit position of the `CAN_F8R2_FB17` field @def CAN_F8R2_FB17_Pos */
#define CAN_F8R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB17` field @def CAN_F8R2_FB17_Msk */
#define CAN_F8R2_FB17_Msk		REG_BIT_MASK(CAN_F8R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F8R2_FB17 */
#define CAN_F8R2_FB17			CAN_F8R2_FB17_Msk
/** @brief Bit position of the `CAN_F8R2_FB18` field @def CAN_F8R2_FB18_Pos */
#define CAN_F8R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB18` field @def CAN_F8R2_FB18_Msk */
#define CAN_F8R2_FB18_Msk		REG_BIT_MASK(CAN_F8R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F8R2_FB18 */
#define CAN_F8R2_FB18			CAN_F8R2_FB18_Msk
/** @brief Bit position of the `CAN_F8R2_FB19` field @def CAN_F8R2_FB19_Pos */
#define CAN_F8R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB19` field @def CAN_F8R2_FB19_Msk */
#define CAN_F8R2_FB19_Msk		REG_BIT_MASK(CAN_F8R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F8R2_FB19 */
#define CAN_F8R2_FB19			CAN_F8R2_FB19_Msk
/** @brief Bit position of the `CAN_F8R2_FB20` field @def CAN_F8R2_FB20_Pos */
#define CAN_F8R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB20` field @def CAN_F8R2_FB20_Msk */
#define CAN_F8R2_FB20_Msk		REG_BIT_MASK(CAN_F8R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F8R2_FB20 */
#define CAN_F8R2_FB20			CAN_F8R2_FB20_Msk
/** @brief Bit position of the `CAN_F8R2_FB21` field @def CAN_F8R2_FB21_Pos */
#define CAN_F8R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB21` field @def CAN_F8R2_FB21_Msk */
#define CAN_F8R2_FB21_Msk		REG_BIT_MASK(CAN_F8R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F8R2_FB21 */
#define CAN_F8R2_FB21			CAN_F8R2_FB21_Msk
/** @brief Bit position of the `CAN_F8R2_FB22` field @def CAN_F8R2_FB22_Pos */
#define CAN_F8R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB22` field @def CAN_F8R2_FB22_Msk */
#define CAN_F8R2_FB22_Msk		REG_BIT_MASK(CAN_F8R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F8R2_FB22 */
#define CAN_F8R2_FB22			CAN_F8R2_FB22_Msk
/** @brief Bit position of the `CAN_F8R2_FB23` field @def CAN_F8R2_FB23_Pos */
#define CAN_F8R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB23` field @def CAN_F8R2_FB23_Msk */
#define CAN_F8R2_FB23_Msk		REG_BIT_MASK(CAN_F8R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F8R2_FB23 */
#define CAN_F8R2_FB23			CAN_F8R2_FB23_Msk
/** @brief Bit position of the `CAN_F8R2_FB24` field @def CAN_F8R2_FB24_Pos */
#define CAN_F8R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB24` field @def CAN_F8R2_FB24_Msk */
#define CAN_F8R2_FB24_Msk		REG_BIT_MASK(CAN_F8R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F8R2_FB24 */
#define CAN_F8R2_FB24			CAN_F8R2_FB24_Msk
/** @brief Bit position of the `CAN_F8R2_FB25` field @def CAN_F8R2_FB25_Pos */
#define CAN_F8R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB25` field @def CAN_F8R2_FB25_Msk */
#define CAN_F8R2_FB25_Msk		REG_BIT_MASK(CAN_F8R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F8R2_FB25 */
#define CAN_F8R2_FB25			CAN_F8R2_FB25_Msk
/** @brief Bit position of the `CAN_F8R2_FB26` field @def CAN_F8R2_FB26_Pos */
#define CAN_F8R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB26` field @def CAN_F8R2_FB26_Msk */
#define CAN_F8R2_FB26_Msk		REG_BIT_MASK(CAN_F8R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F8R2_FB26 */
#define CAN_F8R2_FB26			CAN_F8R2_FB26_Msk
/** @brief Bit position of the `CAN_F8R2_FB27` field @def CAN_F8R2_FB27_Pos */
#define CAN_F8R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB27` field @def CAN_F8R2_FB27_Msk */
#define CAN_F8R2_FB27_Msk		REG_BIT_MASK(CAN_F8R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F8R2_FB27 */
#define CAN_F8R2_FB27			CAN_F8R2_FB27_Msk
/** @brief Bit position of the `CAN_F8R2_FB28` field @def CAN_F8R2_FB28_Pos */
#define CAN_F8R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB28` field @def CAN_F8R2_FB28_Msk */
#define CAN_F8R2_FB28_Msk		REG_BIT_MASK(CAN_F8R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F8R2_FB28 */
#define CAN_F8R2_FB28			CAN_F8R2_FB28_Msk
/** @brief Bit position of the `CAN_F8R2_FB29` field @def CAN_F8R2_FB29_Pos */
#define CAN_F8R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB29` field @def CAN_F8R2_FB29_Msk */
#define CAN_F8R2_FB29_Msk		REG_BIT_MASK(CAN_F8R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F8R2_FB29 */
#define CAN_F8R2_FB29			CAN_F8R2_FB29_Msk
/** @brief Bit position of the `CAN_F8R2_FB30` field @def CAN_F8R2_FB30_Pos */
#define CAN_F8R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB30` field @def CAN_F8R2_FB30_Msk */
#define CAN_F8R2_FB30_Msk		REG_BIT_MASK(CAN_F8R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F8R2_FB30 */
#define CAN_F8R2_FB30			CAN_F8R2_FB30_Msk
/** @brief Bit position of the `CAN_F8R2_FB31` field @def CAN_F8R2_FB31_Pos */
#define CAN_F8R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F8R2_FB31` field @def CAN_F8R2_FB31_Msk */
#define CAN_F8R2_FB31_Msk		REG_BIT_MASK(CAN_F8R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F8R2_FB31 */
#define CAN_F8R2_FB31			CAN_F8R2_FB31_Msk

// ---------------------------------- CAN_F9R2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `CAN_F9R2_FB0` field @def CAN_F9R2_FB0_Pos */
#define CAN_F9R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB0` field @def CAN_F9R2_FB0_Msk */
#define CAN_F9R2_FB0_Msk		REG_BIT_MASK(CAN_F9R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F9R2_FB0 */
#define CAN_F9R2_FB0			CAN_F9R2_FB0_Msk
/** @brief Bit position of the `CAN_F9R2_FB1` field @def CAN_F9R2_FB1_Pos */
#define CAN_F9R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB1` field @def CAN_F9R2_FB1_Msk */
#define CAN_F9R2_FB1_Msk		REG_BIT_MASK(CAN_F9R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F9R2_FB1 */
#define CAN_F9R2_FB1			CAN_F9R2_FB1_Msk
/** @brief Bit position of the `CAN_F9R2_FB2` field @def CAN_F9R2_FB2_Pos */
#define CAN_F9R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB2` field @def CAN_F9R2_FB2_Msk */
#define CAN_F9R2_FB2_Msk		REG_BIT_MASK(CAN_F9R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F9R2_FB2 */
#define CAN_F9R2_FB2			CAN_F9R2_FB2_Msk
/** @brief Bit position of the `CAN_F9R2_FB3` field @def CAN_F9R2_FB3_Pos */
#define CAN_F9R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB3` field @def CAN_F9R2_FB3_Msk */
#define CAN_F9R2_FB3_Msk		REG_BIT_MASK(CAN_F9R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F9R2_FB3 */
#define CAN_F9R2_FB3			CAN_F9R2_FB3_Msk
/** @brief Bit position of the `CAN_F9R2_FB4` field @def CAN_F9R2_FB4_Pos */
#define CAN_F9R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB4` field @def CAN_F9R2_FB4_Msk */
#define CAN_F9R2_FB4_Msk		REG_BIT_MASK(CAN_F9R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F9R2_FB4 */
#define CAN_F9R2_FB4			CAN_F9R2_FB4_Msk
/** @brief Bit position of the `CAN_F9R2_FB5` field @def CAN_F9R2_FB5_Pos */
#define CAN_F9R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB5` field @def CAN_F9R2_FB5_Msk */
#define CAN_F9R2_FB5_Msk		REG_BIT_MASK(CAN_F9R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F9R2_FB5 */
#define CAN_F9R2_FB5			CAN_F9R2_FB5_Msk
/** @brief Bit position of the `CAN_F9R2_FB6` field @def CAN_F9R2_FB6_Pos */
#define CAN_F9R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB6` field @def CAN_F9R2_FB6_Msk */
#define CAN_F9R2_FB6_Msk		REG_BIT_MASK(CAN_F9R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F9R2_FB6 */
#define CAN_F9R2_FB6			CAN_F9R2_FB6_Msk
/** @brief Bit position of the `CAN_F9R2_FB7` field @def CAN_F9R2_FB7_Pos */
#define CAN_F9R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB7` field @def CAN_F9R2_FB7_Msk */
#define CAN_F9R2_FB7_Msk		REG_BIT_MASK(CAN_F9R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F9R2_FB7 */
#define CAN_F9R2_FB7			CAN_F9R2_FB7_Msk
/** @brief Bit position of the `CAN_F9R2_FB8` field @def CAN_F9R2_FB8_Pos */
#define CAN_F9R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB8` field @def CAN_F9R2_FB8_Msk */
#define CAN_F9R2_FB8_Msk		REG_BIT_MASK(CAN_F9R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F9R2_FB8 */
#define CAN_F9R2_FB8			CAN_F9R2_FB8_Msk
/** @brief Bit position of the `CAN_F9R2_FB9` field @def CAN_F9R2_FB9_Pos */
#define CAN_F9R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB9` field @def CAN_F9R2_FB9_Msk */
#define CAN_F9R2_FB9_Msk		REG_BIT_MASK(CAN_F9R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F9R2_FB9 */
#define CAN_F9R2_FB9			CAN_F9R2_FB9_Msk
/** @brief Bit position of the `CAN_F9R2_FB10` field @def CAN_F9R2_FB10_Pos */
#define CAN_F9R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB10` field @def CAN_F9R2_FB10_Msk */
#define CAN_F9R2_FB10_Msk		REG_BIT_MASK(CAN_F9R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F9R2_FB10 */
#define CAN_F9R2_FB10			CAN_F9R2_FB10_Msk
/** @brief Bit position of the `CAN_F9R2_FB11` field @def CAN_F9R2_FB11_Pos */
#define CAN_F9R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB11` field @def CAN_F9R2_FB11_Msk */
#define CAN_F9R2_FB11_Msk		REG_BIT_MASK(CAN_F9R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F9R2_FB11 */
#define CAN_F9R2_FB11			CAN_F9R2_FB11_Msk
/** @brief Bit position of the `CAN_F9R2_FB12` field @def CAN_F9R2_FB12_Pos */
#define CAN_F9R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB12` field @def CAN_F9R2_FB12_Msk */
#define CAN_F9R2_FB12_Msk		REG_BIT_MASK(CAN_F9R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F9R2_FB12 */
#define CAN_F9R2_FB12			CAN_F9R2_FB12_Msk
/** @brief Bit position of the `CAN_F9R2_FB13` field @def CAN_F9R2_FB13_Pos */
#define CAN_F9R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB13` field @def CAN_F9R2_FB13_Msk */
#define CAN_F9R2_FB13_Msk		REG_BIT_MASK(CAN_F9R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F9R2_FB13 */
#define CAN_F9R2_FB13			CAN_F9R2_FB13_Msk
/** @brief Bit position of the `CAN_F9R2_FB14` field @def CAN_F9R2_FB14_Pos */
#define CAN_F9R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB14` field @def CAN_F9R2_FB14_Msk */
#define CAN_F9R2_FB14_Msk		REG_BIT_MASK(CAN_F9R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F9R2_FB14 */
#define CAN_F9R2_FB14			CAN_F9R2_FB14_Msk
/** @brief Bit position of the `CAN_F9R2_FB15` field @def CAN_F9R2_FB15_Pos */
#define CAN_F9R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB15` field @def CAN_F9R2_FB15_Msk */
#define CAN_F9R2_FB15_Msk		REG_BIT_MASK(CAN_F9R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F9R2_FB15 */
#define CAN_F9R2_FB15			CAN_F9R2_FB15_Msk
/** @brief Bit position of the `CAN_F9R2_FB16` field @def CAN_F9R2_FB16_Pos */
#define CAN_F9R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB16` field @def CAN_F9R2_FB16_Msk */
#define CAN_F9R2_FB16_Msk		REG_BIT_MASK(CAN_F9R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F9R2_FB16 */
#define CAN_F9R2_FB16			CAN_F9R2_FB16_Msk
/** @brief Bit position of the `CAN_F9R2_FB17` field @def CAN_F9R2_FB17_Pos */
#define CAN_F9R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB17` field @def CAN_F9R2_FB17_Msk */
#define CAN_F9R2_FB17_Msk		REG_BIT_MASK(CAN_F9R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F9R2_FB17 */
#define CAN_F9R2_FB17			CAN_F9R2_FB17_Msk
/** @brief Bit position of the `CAN_F9R2_FB18` field @def CAN_F9R2_FB18_Pos */
#define CAN_F9R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB18` field @def CAN_F9R2_FB18_Msk */
#define CAN_F9R2_FB18_Msk		REG_BIT_MASK(CAN_F9R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F9R2_FB18 */
#define CAN_F9R2_FB18			CAN_F9R2_FB18_Msk
/** @brief Bit position of the `CAN_F9R2_FB19` field @def CAN_F9R2_FB19_Pos */
#define CAN_F9R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB19` field @def CAN_F9R2_FB19_Msk */
#define CAN_F9R2_FB19_Msk		REG_BIT_MASK(CAN_F9R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F9R2_FB19 */
#define CAN_F9R2_FB19			CAN_F9R2_FB19_Msk
/** @brief Bit position of the `CAN_F9R2_FB20` field @def CAN_F9R2_FB20_Pos */
#define CAN_F9R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB20` field @def CAN_F9R2_FB20_Msk */
#define CAN_F9R2_FB20_Msk		REG_BIT_MASK(CAN_F9R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F9R2_FB20 */
#define CAN_F9R2_FB20			CAN_F9R2_FB20_Msk
/** @brief Bit position of the `CAN_F9R2_FB21` field @def CAN_F9R2_FB21_Pos */
#define CAN_F9R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB21` field @def CAN_F9R2_FB21_Msk */
#define CAN_F9R2_FB21_Msk		REG_BIT_MASK(CAN_F9R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F9R2_FB21 */
#define CAN_F9R2_FB21			CAN_F9R2_FB21_Msk
/** @brief Bit position of the `CAN_F9R2_FB22` field @def CAN_F9R2_FB22_Pos */
#define CAN_F9R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB22` field @def CAN_F9R2_FB22_Msk */
#define CAN_F9R2_FB22_Msk		REG_BIT_MASK(CAN_F9R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F9R2_FB22 */
#define CAN_F9R2_FB22			CAN_F9R2_FB22_Msk
/** @brief Bit position of the `CAN_F9R2_FB23` field @def CAN_F9R2_FB23_Pos */
#define CAN_F9R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB23` field @def CAN_F9R2_FB23_Msk */
#define CAN_F9R2_FB23_Msk		REG_BIT_MASK(CAN_F9R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F9R2_FB23 */
#define CAN_F9R2_FB23			CAN_F9R2_FB23_Msk
/** @brief Bit position of the `CAN_F9R2_FB24` field @def CAN_F9R2_FB24_Pos */
#define CAN_F9R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB24` field @def CAN_F9R2_FB24_Msk */
#define CAN_F9R2_FB24_Msk		REG_BIT_MASK(CAN_F9R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F9R2_FB24 */
#define CAN_F9R2_FB24			CAN_F9R2_FB24_Msk
/** @brief Bit position of the `CAN_F9R2_FB25` field @def CAN_F9R2_FB25_Pos */
#define CAN_F9R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB25` field @def CAN_F9R2_FB25_Msk */
#define CAN_F9R2_FB25_Msk		REG_BIT_MASK(CAN_F9R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F9R2_FB25 */
#define CAN_F9R2_FB25			CAN_F9R2_FB25_Msk
/** @brief Bit position of the `CAN_F9R2_FB26` field @def CAN_F9R2_FB26_Pos */
#define CAN_F9R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB26` field @def CAN_F9R2_FB26_Msk */
#define CAN_F9R2_FB26_Msk		REG_BIT_MASK(CAN_F9R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F9R2_FB26 */
#define CAN_F9R2_FB26			CAN_F9R2_FB26_Msk
/** @brief Bit position of the `CAN_F9R2_FB27` field @def CAN_F9R2_FB27_Pos */
#define CAN_F9R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB27` field @def CAN_F9R2_FB27_Msk */
#define CAN_F9R2_FB27_Msk		REG_BIT_MASK(CAN_F9R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F9R2_FB27 */
#define CAN_F9R2_FB27			CAN_F9R2_FB27_Msk
/** @brief Bit position of the `CAN_F9R2_FB28` field @def CAN_F9R2_FB28_Pos */
#define CAN_F9R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB28` field @def CAN_F9R2_FB28_Msk */
#define CAN_F9R2_FB28_Msk		REG_BIT_MASK(CAN_F9R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F9R2_FB28 */
#define CAN_F9R2_FB28			CAN_F9R2_FB28_Msk
/** @brief Bit position of the `CAN_F9R2_FB29` field @def CAN_F9R2_FB29_Pos */
#define CAN_F9R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB29` field @def CAN_F9R2_FB29_Msk */
#define CAN_F9R2_FB29_Msk		REG_BIT_MASK(CAN_F9R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F9R2_FB29 */
#define CAN_F9R2_FB29			CAN_F9R2_FB29_Msk
/** @brief Bit position of the `CAN_F9R2_FB30` field @def CAN_F9R2_FB30_Pos */
#define CAN_F9R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB30` field @def CAN_F9R2_FB30_Msk */
#define CAN_F9R2_FB30_Msk		REG_BIT_MASK(CAN_F9R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F9R2_FB30 */
#define CAN_F9R2_FB30			CAN_F9R2_FB30_Msk
/** @brief Bit position of the `CAN_F9R2_FB31` field @def CAN_F9R2_FB31_Pos */
#define CAN_F9R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F9R2_FB31` field @def CAN_F9R2_FB31_Msk */
#define CAN_F9R2_FB31_Msk		REG_BIT_MASK(CAN_F9R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F9R2_FB31 */
#define CAN_F9R2_FB31			CAN_F9R2_FB31_Msk

// ---------------------------------- CAN_F10R2 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_F10R2_FB0` field @def CAN_F10R2_FB0_Pos */
#define CAN_F10R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB0` field @def CAN_F10R2_FB0_Msk */
#define CAN_F10R2_FB0_Msk		REG_BIT_MASK(CAN_F10R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F10R2_FB0 */
#define CAN_F10R2_FB0			CAN_F10R2_FB0_Msk
/** @brief Bit position of the `CAN_F10R2_FB1` field @def CAN_F10R2_FB1_Pos */
#define CAN_F10R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB1` field @def CAN_F10R2_FB1_Msk */
#define CAN_F10R2_FB1_Msk		REG_BIT_MASK(CAN_F10R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F10R2_FB1 */
#define CAN_F10R2_FB1			CAN_F10R2_FB1_Msk
/** @brief Bit position of the `CAN_F10R2_FB2` field @def CAN_F10R2_FB2_Pos */
#define CAN_F10R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB2` field @def CAN_F10R2_FB2_Msk */
#define CAN_F10R2_FB2_Msk		REG_BIT_MASK(CAN_F10R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F10R2_FB2 */
#define CAN_F10R2_FB2			CAN_F10R2_FB2_Msk
/** @brief Bit position of the `CAN_F10R2_FB3` field @def CAN_F10R2_FB3_Pos */
#define CAN_F10R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB3` field @def CAN_F10R2_FB3_Msk */
#define CAN_F10R2_FB3_Msk		REG_BIT_MASK(CAN_F10R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F10R2_FB3 */
#define CAN_F10R2_FB3			CAN_F10R2_FB3_Msk
/** @brief Bit position of the `CAN_F10R2_FB4` field @def CAN_F10R2_FB4_Pos */
#define CAN_F10R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB4` field @def CAN_F10R2_FB4_Msk */
#define CAN_F10R2_FB4_Msk		REG_BIT_MASK(CAN_F10R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F10R2_FB4 */
#define CAN_F10R2_FB4			CAN_F10R2_FB4_Msk
/** @brief Bit position of the `CAN_F10R2_FB5` field @def CAN_F10R2_FB5_Pos */
#define CAN_F10R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB5` field @def CAN_F10R2_FB5_Msk */
#define CAN_F10R2_FB5_Msk		REG_BIT_MASK(CAN_F10R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F10R2_FB5 */
#define CAN_F10R2_FB5			CAN_F10R2_FB5_Msk
/** @brief Bit position of the `CAN_F10R2_FB6` field @def CAN_F10R2_FB6_Pos */
#define CAN_F10R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB6` field @def CAN_F10R2_FB6_Msk */
#define CAN_F10R2_FB6_Msk		REG_BIT_MASK(CAN_F10R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F10R2_FB6 */
#define CAN_F10R2_FB6			CAN_F10R2_FB6_Msk
/** @brief Bit position of the `CAN_F10R2_FB7` field @def CAN_F10R2_FB7_Pos */
#define CAN_F10R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB7` field @def CAN_F10R2_FB7_Msk */
#define CAN_F10R2_FB7_Msk		REG_BIT_MASK(CAN_F10R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F10R2_FB7 */
#define CAN_F10R2_FB7			CAN_F10R2_FB7_Msk
/** @brief Bit position of the `CAN_F10R2_FB8` field @def CAN_F10R2_FB8_Pos */
#define CAN_F10R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB8` field @def CAN_F10R2_FB8_Msk */
#define CAN_F10R2_FB8_Msk		REG_BIT_MASK(CAN_F10R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F10R2_FB8 */
#define CAN_F10R2_FB8			CAN_F10R2_FB8_Msk
/** @brief Bit position of the `CAN_F10R2_FB9` field @def CAN_F10R2_FB9_Pos */
#define CAN_F10R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB9` field @def CAN_F10R2_FB9_Msk */
#define CAN_F10R2_FB9_Msk		REG_BIT_MASK(CAN_F10R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F10R2_FB9 */
#define CAN_F10R2_FB9			CAN_F10R2_FB9_Msk
/** @brief Bit position of the `CAN_F10R2_FB10` field @def CAN_F10R2_FB10_Pos */
#define CAN_F10R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB10` field @def CAN_F10R2_FB10_Msk */
#define CAN_F10R2_FB10_Msk		REG_BIT_MASK(CAN_F10R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F10R2_FB10 */
#define CAN_F10R2_FB10			CAN_F10R2_FB10_Msk
/** @brief Bit position of the `CAN_F10R2_FB11` field @def CAN_F10R2_FB11_Pos */
#define CAN_F10R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB11` field @def CAN_F10R2_FB11_Msk */
#define CAN_F10R2_FB11_Msk		REG_BIT_MASK(CAN_F10R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F10R2_FB11 */
#define CAN_F10R2_FB11			CAN_F10R2_FB11_Msk
/** @brief Bit position of the `CAN_F10R2_FB12` field @def CAN_F10R2_FB12_Pos */
#define CAN_F10R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB12` field @def CAN_F10R2_FB12_Msk */
#define CAN_F10R2_FB12_Msk		REG_BIT_MASK(CAN_F10R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F10R2_FB12 */
#define CAN_F10R2_FB12			CAN_F10R2_FB12_Msk
/** @brief Bit position of the `CAN_F10R2_FB13` field @def CAN_F10R2_FB13_Pos */
#define CAN_F10R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB13` field @def CAN_F10R2_FB13_Msk */
#define CAN_F10R2_FB13_Msk		REG_BIT_MASK(CAN_F10R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F10R2_FB13 */
#define CAN_F10R2_FB13			CAN_F10R2_FB13_Msk
/** @brief Bit position of the `CAN_F10R2_FB14` field @def CAN_F10R2_FB14_Pos */
#define CAN_F10R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB14` field @def CAN_F10R2_FB14_Msk */
#define CAN_F10R2_FB14_Msk		REG_BIT_MASK(CAN_F10R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F10R2_FB14 */
#define CAN_F10R2_FB14			CAN_F10R2_FB14_Msk
/** @brief Bit position of the `CAN_F10R2_FB15` field @def CAN_F10R2_FB15_Pos */
#define CAN_F10R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB15` field @def CAN_F10R2_FB15_Msk */
#define CAN_F10R2_FB15_Msk		REG_BIT_MASK(CAN_F10R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F10R2_FB15 */
#define CAN_F10R2_FB15			CAN_F10R2_FB15_Msk
/** @brief Bit position of the `CAN_F10R2_FB16` field @def CAN_F10R2_FB16_Pos */
#define CAN_F10R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB16` field @def CAN_F10R2_FB16_Msk */
#define CAN_F10R2_FB16_Msk		REG_BIT_MASK(CAN_F10R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F10R2_FB16 */
#define CAN_F10R2_FB16			CAN_F10R2_FB16_Msk
/** @brief Bit position of the `CAN_F10R2_FB17` field @def CAN_F10R2_FB17_Pos */
#define CAN_F10R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB17` field @def CAN_F10R2_FB17_Msk */
#define CAN_F10R2_FB17_Msk		REG_BIT_MASK(CAN_F10R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F10R2_FB17 */
#define CAN_F10R2_FB17			CAN_F10R2_FB17_Msk
/** @brief Bit position of the `CAN_F10R2_FB18` field @def CAN_F10R2_FB18_Pos */
#define CAN_F10R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB18` field @def CAN_F10R2_FB18_Msk */
#define CAN_F10R2_FB18_Msk		REG_BIT_MASK(CAN_F10R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F10R2_FB18 */
#define CAN_F10R2_FB18			CAN_F10R2_FB18_Msk
/** @brief Bit position of the `CAN_F10R2_FB19` field @def CAN_F10R2_FB19_Pos */
#define CAN_F10R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB19` field @def CAN_F10R2_FB19_Msk */
#define CAN_F10R2_FB19_Msk		REG_BIT_MASK(CAN_F10R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F10R2_FB19 */
#define CAN_F10R2_FB19			CAN_F10R2_FB19_Msk
/** @brief Bit position of the `CAN_F10R2_FB20` field @def CAN_F10R2_FB20_Pos */
#define CAN_F10R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB20` field @def CAN_F10R2_FB20_Msk */
#define CAN_F10R2_FB20_Msk		REG_BIT_MASK(CAN_F10R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F10R2_FB20 */
#define CAN_F10R2_FB20			CAN_F10R2_FB20_Msk
/** @brief Bit position of the `CAN_F10R2_FB21` field @def CAN_F10R2_FB21_Pos */
#define CAN_F10R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB21` field @def CAN_F10R2_FB21_Msk */
#define CAN_F10R2_FB21_Msk		REG_BIT_MASK(CAN_F10R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F10R2_FB21 */
#define CAN_F10R2_FB21			CAN_F10R2_FB21_Msk
/** @brief Bit position of the `CAN_F10R2_FB22` field @def CAN_F10R2_FB22_Pos */
#define CAN_F10R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB22` field @def CAN_F10R2_FB22_Msk */
#define CAN_F10R2_FB22_Msk		REG_BIT_MASK(CAN_F10R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F10R2_FB22 */
#define CAN_F10R2_FB22			CAN_F10R2_FB22_Msk
/** @brief Bit position of the `CAN_F10R2_FB23` field @def CAN_F10R2_FB23_Pos */
#define CAN_F10R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB23` field @def CAN_F10R2_FB23_Msk */
#define CAN_F10R2_FB23_Msk		REG_BIT_MASK(CAN_F10R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F10R2_FB23 */
#define CAN_F10R2_FB23			CAN_F10R2_FB23_Msk
/** @brief Bit position of the `CAN_F10R2_FB24` field @def CAN_F10R2_FB24_Pos */
#define CAN_F10R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB24` field @def CAN_F10R2_FB24_Msk */
#define CAN_F10R2_FB24_Msk		REG_BIT_MASK(CAN_F10R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F10R2_FB24 */
#define CAN_F10R2_FB24			CAN_F10R2_FB24_Msk
/** @brief Bit position of the `CAN_F10R2_FB25` field @def CAN_F10R2_FB25_Pos */
#define CAN_F10R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB25` field @def CAN_F10R2_FB25_Msk */
#define CAN_F10R2_FB25_Msk		REG_BIT_MASK(CAN_F10R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F10R2_FB25 */
#define CAN_F10R2_FB25			CAN_F10R2_FB25_Msk
/** @brief Bit position of the `CAN_F10R2_FB26` field @def CAN_F10R2_FB26_Pos */
#define CAN_F10R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB26` field @def CAN_F10R2_FB26_Msk */
#define CAN_F10R2_FB26_Msk		REG_BIT_MASK(CAN_F10R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F10R2_FB26 */
#define CAN_F10R2_FB26			CAN_F10R2_FB26_Msk
/** @brief Bit position of the `CAN_F10R2_FB27` field @def CAN_F10R2_FB27_Pos */
#define CAN_F10R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB27` field @def CAN_F10R2_FB27_Msk */
#define CAN_F10R2_FB27_Msk		REG_BIT_MASK(CAN_F10R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F10R2_FB27 */
#define CAN_F10R2_FB27			CAN_F10R2_FB27_Msk
/** @brief Bit position of the `CAN_F10R2_FB28` field @def CAN_F10R2_FB28_Pos */
#define CAN_F10R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB28` field @def CAN_F10R2_FB28_Msk */
#define CAN_F10R2_FB28_Msk		REG_BIT_MASK(CAN_F10R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F10R2_FB28 */
#define CAN_F10R2_FB28			CAN_F10R2_FB28_Msk
/** @brief Bit position of the `CAN_F10R2_FB29` field @def CAN_F10R2_FB29_Pos */
#define CAN_F10R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB29` field @def CAN_F10R2_FB29_Msk */
#define CAN_F10R2_FB29_Msk		REG_BIT_MASK(CAN_F10R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F10R2_FB29 */
#define CAN_F10R2_FB29			CAN_F10R2_FB29_Msk
/** @brief Bit position of the `CAN_F10R2_FB30` field @def CAN_F10R2_FB30_Pos */
#define CAN_F10R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB30` field @def CAN_F10R2_FB30_Msk */
#define CAN_F10R2_FB30_Msk		REG_BIT_MASK(CAN_F10R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F10R2_FB30 */
#define CAN_F10R2_FB30			CAN_F10R2_FB30_Msk
/** @brief Bit position of the `CAN_F10R2_FB31` field @def CAN_F10R2_FB31_Pos */
#define CAN_F10R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F10R2_FB31` field @def CAN_F10R2_FB31_Msk */
#define CAN_F10R2_FB31_Msk		REG_BIT_MASK(CAN_F10R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F10R2_FB31 */
#define CAN_F10R2_FB31			CAN_F10R2_FB31_Msk

// ---------------------------------- CAN_F11R2 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_F11R2_FB0` field @def CAN_F11R2_FB0_Pos */
#define CAN_F11R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB0` field @def CAN_F11R2_FB0_Msk */
#define CAN_F11R2_FB0_Msk		REG_BIT_MASK(CAN_F11R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F11R2_FB0 */
#define CAN_F11R2_FB0			CAN_F11R2_FB0_Msk
/** @brief Bit position of the `CAN_F11R2_FB1` field @def CAN_F11R2_FB1_Pos */
#define CAN_F11R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB1` field @def CAN_F11R2_FB1_Msk */
#define CAN_F11R2_FB1_Msk		REG_BIT_MASK(CAN_F11R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F11R2_FB1 */
#define CAN_F11R2_FB1			CAN_F11R2_FB1_Msk
/** @brief Bit position of the `CAN_F11R2_FB2` field @def CAN_F11R2_FB2_Pos */
#define CAN_F11R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB2` field @def CAN_F11R2_FB2_Msk */
#define CAN_F11R2_FB2_Msk		REG_BIT_MASK(CAN_F11R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F11R2_FB2 */
#define CAN_F11R2_FB2			CAN_F11R2_FB2_Msk
/** @brief Bit position of the `CAN_F11R2_FB3` field @def CAN_F11R2_FB3_Pos */
#define CAN_F11R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB3` field @def CAN_F11R2_FB3_Msk */
#define CAN_F11R2_FB3_Msk		REG_BIT_MASK(CAN_F11R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F11R2_FB3 */
#define CAN_F11R2_FB3			CAN_F11R2_FB3_Msk
/** @brief Bit position of the `CAN_F11R2_FB4` field @def CAN_F11R2_FB4_Pos */
#define CAN_F11R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB4` field @def CAN_F11R2_FB4_Msk */
#define CAN_F11R2_FB4_Msk		REG_BIT_MASK(CAN_F11R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F11R2_FB4 */
#define CAN_F11R2_FB4			CAN_F11R2_FB4_Msk
/** @brief Bit position of the `CAN_F11R2_FB5` field @def CAN_F11R2_FB5_Pos */
#define CAN_F11R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB5` field @def CAN_F11R2_FB5_Msk */
#define CAN_F11R2_FB5_Msk		REG_BIT_MASK(CAN_F11R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F11R2_FB5 */
#define CAN_F11R2_FB5			CAN_F11R2_FB5_Msk
/** @brief Bit position of the `CAN_F11R2_FB6` field @def CAN_F11R2_FB6_Pos */
#define CAN_F11R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB6` field @def CAN_F11R2_FB6_Msk */
#define CAN_F11R2_FB6_Msk		REG_BIT_MASK(CAN_F11R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F11R2_FB6 */
#define CAN_F11R2_FB6			CAN_F11R2_FB6_Msk
/** @brief Bit position of the `CAN_F11R2_FB7` field @def CAN_F11R2_FB7_Pos */
#define CAN_F11R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB7` field @def CAN_F11R2_FB7_Msk */
#define CAN_F11R2_FB7_Msk		REG_BIT_MASK(CAN_F11R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F11R2_FB7 */
#define CAN_F11R2_FB7			CAN_F11R2_FB7_Msk
/** @brief Bit position of the `CAN_F11R2_FB8` field @def CAN_F11R2_FB8_Pos */
#define CAN_F11R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB8` field @def CAN_F11R2_FB8_Msk */
#define CAN_F11R2_FB8_Msk		REG_BIT_MASK(CAN_F11R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F11R2_FB8 */
#define CAN_F11R2_FB8			CAN_F11R2_FB8_Msk
/** @brief Bit position of the `CAN_F11R2_FB9` field @def CAN_F11R2_FB9_Pos */
#define CAN_F11R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB9` field @def CAN_F11R2_FB9_Msk */
#define CAN_F11R2_FB9_Msk		REG_BIT_MASK(CAN_F11R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F11R2_FB9 */
#define CAN_F11R2_FB9			CAN_F11R2_FB9_Msk
/** @brief Bit position of the `CAN_F11R2_FB10` field @def CAN_F11R2_FB10_Pos */
#define CAN_F11R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB10` field @def CAN_F11R2_FB10_Msk */
#define CAN_F11R2_FB10_Msk		REG_BIT_MASK(CAN_F11R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F11R2_FB10 */
#define CAN_F11R2_FB10			CAN_F11R2_FB10_Msk
/** @brief Bit position of the `CAN_F11R2_FB11` field @def CAN_F11R2_FB11_Pos */
#define CAN_F11R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB11` field @def CAN_F11R2_FB11_Msk */
#define CAN_F11R2_FB11_Msk		REG_BIT_MASK(CAN_F11R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F11R2_FB11 */
#define CAN_F11R2_FB11			CAN_F11R2_FB11_Msk
/** @brief Bit position of the `CAN_F11R2_FB12` field @def CAN_F11R2_FB12_Pos */
#define CAN_F11R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB12` field @def CAN_F11R2_FB12_Msk */
#define CAN_F11R2_FB12_Msk		REG_BIT_MASK(CAN_F11R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F11R2_FB12 */
#define CAN_F11R2_FB12			CAN_F11R2_FB12_Msk
/** @brief Bit position of the `CAN_F11R2_FB13` field @def CAN_F11R2_FB13_Pos */
#define CAN_F11R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB13` field @def CAN_F11R2_FB13_Msk */
#define CAN_F11R2_FB13_Msk		REG_BIT_MASK(CAN_F11R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F11R2_FB13 */
#define CAN_F11R2_FB13			CAN_F11R2_FB13_Msk
/** @brief Bit position of the `CAN_F11R2_FB14` field @def CAN_F11R2_FB14_Pos */
#define CAN_F11R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB14` field @def CAN_F11R2_FB14_Msk */
#define CAN_F11R2_FB14_Msk		REG_BIT_MASK(CAN_F11R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F11R2_FB14 */
#define CAN_F11R2_FB14			CAN_F11R2_FB14_Msk
/** @brief Bit position of the `CAN_F11R2_FB15` field @def CAN_F11R2_FB15_Pos */
#define CAN_F11R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB15` field @def CAN_F11R2_FB15_Msk */
#define CAN_F11R2_FB15_Msk		REG_BIT_MASK(CAN_F11R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F11R2_FB15 */
#define CAN_F11R2_FB15			CAN_F11R2_FB15_Msk
/** @brief Bit position of the `CAN_F11R2_FB16` field @def CAN_F11R2_FB16_Pos */
#define CAN_F11R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB16` field @def CAN_F11R2_FB16_Msk */
#define CAN_F11R2_FB16_Msk		REG_BIT_MASK(CAN_F11R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F11R2_FB16 */
#define CAN_F11R2_FB16			CAN_F11R2_FB16_Msk
/** @brief Bit position of the `CAN_F11R2_FB17` field @def CAN_F11R2_FB17_Pos */
#define CAN_F11R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB17` field @def CAN_F11R2_FB17_Msk */
#define CAN_F11R2_FB17_Msk		REG_BIT_MASK(CAN_F11R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F11R2_FB17 */
#define CAN_F11R2_FB17			CAN_F11R2_FB17_Msk
/** @brief Bit position of the `CAN_F11R2_FB18` field @def CAN_F11R2_FB18_Pos */
#define CAN_F11R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB18` field @def CAN_F11R2_FB18_Msk */
#define CAN_F11R2_FB18_Msk		REG_BIT_MASK(CAN_F11R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F11R2_FB18 */
#define CAN_F11R2_FB18			CAN_F11R2_FB18_Msk
/** @brief Bit position of the `CAN_F11R2_FB19` field @def CAN_F11R2_FB19_Pos */
#define CAN_F11R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB19` field @def CAN_F11R2_FB19_Msk */
#define CAN_F11R2_FB19_Msk		REG_BIT_MASK(CAN_F11R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F11R2_FB19 */
#define CAN_F11R2_FB19			CAN_F11R2_FB19_Msk
/** @brief Bit position of the `CAN_F11R2_FB20` field @def CAN_F11R2_FB20_Pos */
#define CAN_F11R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB20` field @def CAN_F11R2_FB20_Msk */
#define CAN_F11R2_FB20_Msk		REG_BIT_MASK(CAN_F11R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F11R2_FB20 */
#define CAN_F11R2_FB20			CAN_F11R2_FB20_Msk
/** @brief Bit position of the `CAN_F11R2_FB21` field @def CAN_F11R2_FB21_Pos */
#define CAN_F11R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB21` field @def CAN_F11R2_FB21_Msk */
#define CAN_F11R2_FB21_Msk		REG_BIT_MASK(CAN_F11R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F11R2_FB21 */
#define CAN_F11R2_FB21			CAN_F11R2_FB21_Msk
/** @brief Bit position of the `CAN_F11R2_FB22` field @def CAN_F11R2_FB22_Pos */
#define CAN_F11R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB22` field @def CAN_F11R2_FB22_Msk */
#define CAN_F11R2_FB22_Msk		REG_BIT_MASK(CAN_F11R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F11R2_FB22 */
#define CAN_F11R2_FB22			CAN_F11R2_FB22_Msk
/** @brief Bit position of the `CAN_F11R2_FB23` field @def CAN_F11R2_FB23_Pos */
#define CAN_F11R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB23` field @def CAN_F11R2_FB23_Msk */
#define CAN_F11R2_FB23_Msk		REG_BIT_MASK(CAN_F11R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F11R2_FB23 */
#define CAN_F11R2_FB23			CAN_F11R2_FB23_Msk
/** @brief Bit position of the `CAN_F11R2_FB24` field @def CAN_F11R2_FB24_Pos */
#define CAN_F11R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB24` field @def CAN_F11R2_FB24_Msk */
#define CAN_F11R2_FB24_Msk		REG_BIT_MASK(CAN_F11R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F11R2_FB24 */
#define CAN_F11R2_FB24			CAN_F11R2_FB24_Msk
/** @brief Bit position of the `CAN_F11R2_FB25` field @def CAN_F11R2_FB25_Pos */
#define CAN_F11R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB25` field @def CAN_F11R2_FB25_Msk */
#define CAN_F11R2_FB25_Msk		REG_BIT_MASK(CAN_F11R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F11R2_FB25 */
#define CAN_F11R2_FB25			CAN_F11R2_FB25_Msk
/** @brief Bit position of the `CAN_F11R2_FB26` field @def CAN_F11R2_FB26_Pos */
#define CAN_F11R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB26` field @def CAN_F11R2_FB26_Msk */
#define CAN_F11R2_FB26_Msk		REG_BIT_MASK(CAN_F11R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F11R2_FB26 */
#define CAN_F11R2_FB26			CAN_F11R2_FB26_Msk
/** @brief Bit position of the `CAN_F11R2_FB27` field @def CAN_F11R2_FB27_Pos */
#define CAN_F11R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB27` field @def CAN_F11R2_FB27_Msk */
#define CAN_F11R2_FB27_Msk		REG_BIT_MASK(CAN_F11R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F11R2_FB27 */
#define CAN_F11R2_FB27			CAN_F11R2_FB27_Msk
/** @brief Bit position of the `CAN_F11R2_FB28` field @def CAN_F11R2_FB28_Pos */
#define CAN_F11R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB28` field @def CAN_F11R2_FB28_Msk */
#define CAN_F11R2_FB28_Msk		REG_BIT_MASK(CAN_F11R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F11R2_FB28 */
#define CAN_F11R2_FB28			CAN_F11R2_FB28_Msk
/** @brief Bit position of the `CAN_F11R2_FB29` field @def CAN_F11R2_FB29_Pos */
#define CAN_F11R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB29` field @def CAN_F11R2_FB29_Msk */
#define CAN_F11R2_FB29_Msk		REG_BIT_MASK(CAN_F11R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F11R2_FB29 */
#define CAN_F11R2_FB29			CAN_F11R2_FB29_Msk
/** @brief Bit position of the `CAN_F11R2_FB30` field @def CAN_F11R2_FB30_Pos */
#define CAN_F11R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB30` field @def CAN_F11R2_FB30_Msk */
#define CAN_F11R2_FB30_Msk		REG_BIT_MASK(CAN_F11R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F11R2_FB30 */
#define CAN_F11R2_FB30			CAN_F11R2_FB30_Msk
/** @brief Bit position of the `CAN_F11R2_FB31` field @def CAN_F11R2_FB31_Pos */
#define CAN_F11R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F11R2_FB31` field @def CAN_F11R2_FB31_Msk */
#define CAN_F11R2_FB31_Msk		REG_BIT_MASK(CAN_F11R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F11R2_FB31 */
#define CAN_F11R2_FB31			CAN_F11R2_FB31_Msk

// ---------------------------------- CAN_F12R2 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_F12R2_FB0` field @def CAN_F12R2_FB0_Pos */
#define CAN_F12R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB0` field @def CAN_F12R2_FB0_Msk */
#define CAN_F12R2_FB0_Msk		REG_BIT_MASK(CAN_F12R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F12R2_FB0 */
#define CAN_F12R2_FB0			CAN_F12R2_FB0_Msk
/** @brief Bit position of the `CAN_F12R2_FB1` field @def CAN_F12R2_FB1_Pos */
#define CAN_F12R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB1` field @def CAN_F12R2_FB1_Msk */
#define CAN_F12R2_FB1_Msk		REG_BIT_MASK(CAN_F12R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F12R2_FB1 */
#define CAN_F12R2_FB1			CAN_F12R2_FB1_Msk
/** @brief Bit position of the `CAN_F12R2_FB2` field @def CAN_F12R2_FB2_Pos */
#define CAN_F12R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB2` field @def CAN_F12R2_FB2_Msk */
#define CAN_F12R2_FB2_Msk		REG_BIT_MASK(CAN_F12R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F12R2_FB2 */
#define CAN_F12R2_FB2			CAN_F12R2_FB2_Msk
/** @brief Bit position of the `CAN_F12R2_FB3` field @def CAN_F12R2_FB3_Pos */
#define CAN_F12R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB3` field @def CAN_F12R2_FB3_Msk */
#define CAN_F12R2_FB3_Msk		REG_BIT_MASK(CAN_F12R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F12R2_FB3 */
#define CAN_F12R2_FB3			CAN_F12R2_FB3_Msk
/** @brief Bit position of the `CAN_F12R2_FB4` field @def CAN_F12R2_FB4_Pos */
#define CAN_F12R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB4` field @def CAN_F12R2_FB4_Msk */
#define CAN_F12R2_FB4_Msk		REG_BIT_MASK(CAN_F12R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F12R2_FB4 */
#define CAN_F12R2_FB4			CAN_F12R2_FB4_Msk
/** @brief Bit position of the `CAN_F12R2_FB5` field @def CAN_F12R2_FB5_Pos */
#define CAN_F12R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB5` field @def CAN_F12R2_FB5_Msk */
#define CAN_F12R2_FB5_Msk		REG_BIT_MASK(CAN_F12R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F12R2_FB5 */
#define CAN_F12R2_FB5			CAN_F12R2_FB5_Msk
/** @brief Bit position of the `CAN_F12R2_FB6` field @def CAN_F12R2_FB6_Pos */
#define CAN_F12R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB6` field @def CAN_F12R2_FB6_Msk */
#define CAN_F12R2_FB6_Msk		REG_BIT_MASK(CAN_F12R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F12R2_FB6 */
#define CAN_F12R2_FB6			CAN_F12R2_FB6_Msk
/** @brief Bit position of the `CAN_F12R2_FB7` field @def CAN_F12R2_FB7_Pos */
#define CAN_F12R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB7` field @def CAN_F12R2_FB7_Msk */
#define CAN_F12R2_FB7_Msk		REG_BIT_MASK(CAN_F12R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F12R2_FB7 */
#define CAN_F12R2_FB7			CAN_F12R2_FB7_Msk
/** @brief Bit position of the `CAN_F12R2_FB8` field @def CAN_F12R2_FB8_Pos */
#define CAN_F12R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB8` field @def CAN_F12R2_FB8_Msk */
#define CAN_F12R2_FB8_Msk		REG_BIT_MASK(CAN_F12R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F12R2_FB8 */
#define CAN_F12R2_FB8			CAN_F12R2_FB8_Msk
/** @brief Bit position of the `CAN_F12R2_FB9` field @def CAN_F12R2_FB9_Pos */
#define CAN_F12R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB9` field @def CAN_F12R2_FB9_Msk */
#define CAN_F12R2_FB9_Msk		REG_BIT_MASK(CAN_F12R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F12R2_FB9 */
#define CAN_F12R2_FB9			CAN_F12R2_FB9_Msk
/** @brief Bit position of the `CAN_F12R2_FB10` field @def CAN_F12R2_FB10_Pos */
#define CAN_F12R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB10` field @def CAN_F12R2_FB10_Msk */
#define CAN_F12R2_FB10_Msk		REG_BIT_MASK(CAN_F12R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F12R2_FB10 */
#define CAN_F12R2_FB10			CAN_F12R2_FB10_Msk
/** @brief Bit position of the `CAN_F12R2_FB11` field @def CAN_F12R2_FB11_Pos */
#define CAN_F12R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB11` field @def CAN_F12R2_FB11_Msk */
#define CAN_F12R2_FB11_Msk		REG_BIT_MASK(CAN_F12R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F12R2_FB11 */
#define CAN_F12R2_FB11			CAN_F12R2_FB11_Msk
/** @brief Bit position of the `CAN_F12R2_FB12` field @def CAN_F12R2_FB12_Pos */
#define CAN_F12R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB12` field @def CAN_F12R2_FB12_Msk */
#define CAN_F12R2_FB12_Msk		REG_BIT_MASK(CAN_F12R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F12R2_FB12 */
#define CAN_F12R2_FB12			CAN_F12R2_FB12_Msk
/** @brief Bit position of the `CAN_F12R2_FB13` field @def CAN_F12R2_FB13_Pos */
#define CAN_F12R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB13` field @def CAN_F12R2_FB13_Msk */
#define CAN_F12R2_FB13_Msk		REG_BIT_MASK(CAN_F12R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F12R2_FB13 */
#define CAN_F12R2_FB13			CAN_F12R2_FB13_Msk
/** @brief Bit position of the `CAN_F12R2_FB14` field @def CAN_F12R2_FB14_Pos */
#define CAN_F12R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB14` field @def CAN_F12R2_FB14_Msk */
#define CAN_F12R2_FB14_Msk		REG_BIT_MASK(CAN_F12R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F12R2_FB14 */
#define CAN_F12R2_FB14			CAN_F12R2_FB14_Msk
/** @brief Bit position of the `CAN_F12R2_FB15` field @def CAN_F12R2_FB15_Pos */
#define CAN_F12R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB15` field @def CAN_F12R2_FB15_Msk */
#define CAN_F12R2_FB15_Msk		REG_BIT_MASK(CAN_F12R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F12R2_FB15 */
#define CAN_F12R2_FB15			CAN_F12R2_FB15_Msk
/** @brief Bit position of the `CAN_F12R2_FB16` field @def CAN_F12R2_FB16_Pos */
#define CAN_F12R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB16` field @def CAN_F12R2_FB16_Msk */
#define CAN_F12R2_FB16_Msk		REG_BIT_MASK(CAN_F12R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F12R2_FB16 */
#define CAN_F12R2_FB16			CAN_F12R2_FB16_Msk
/** @brief Bit position of the `CAN_F12R2_FB17` field @def CAN_F12R2_FB17_Pos */
#define CAN_F12R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB17` field @def CAN_F12R2_FB17_Msk */
#define CAN_F12R2_FB17_Msk		REG_BIT_MASK(CAN_F12R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F12R2_FB17 */
#define CAN_F12R2_FB17			CAN_F12R2_FB17_Msk
/** @brief Bit position of the `CAN_F12R2_FB18` field @def CAN_F12R2_FB18_Pos */
#define CAN_F12R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB18` field @def CAN_F12R2_FB18_Msk */
#define CAN_F12R2_FB18_Msk		REG_BIT_MASK(CAN_F12R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F12R2_FB18 */
#define CAN_F12R2_FB18			CAN_F12R2_FB18_Msk
/** @brief Bit position of the `CAN_F12R2_FB19` field @def CAN_F12R2_FB19_Pos */
#define CAN_F12R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB19` field @def CAN_F12R2_FB19_Msk */
#define CAN_F12R2_FB19_Msk		REG_BIT_MASK(CAN_F12R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F12R2_FB19 */
#define CAN_F12R2_FB19			CAN_F12R2_FB19_Msk
/** @brief Bit position of the `CAN_F12R2_FB20` field @def CAN_F12R2_FB20_Pos */
#define CAN_F12R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB20` field @def CAN_F12R2_FB20_Msk */
#define CAN_F12R2_FB20_Msk		REG_BIT_MASK(CAN_F12R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F12R2_FB20 */
#define CAN_F12R2_FB20			CAN_F12R2_FB20_Msk
/** @brief Bit position of the `CAN_F12R2_FB21` field @def CAN_F12R2_FB21_Pos */
#define CAN_F12R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB21` field @def CAN_F12R2_FB21_Msk */
#define CAN_F12R2_FB21_Msk		REG_BIT_MASK(CAN_F12R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F12R2_FB21 */
#define CAN_F12R2_FB21			CAN_F12R2_FB21_Msk
/** @brief Bit position of the `CAN_F12R2_FB22` field @def CAN_F12R2_FB22_Pos */
#define CAN_F12R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB22` field @def CAN_F12R2_FB22_Msk */
#define CAN_F12R2_FB22_Msk		REG_BIT_MASK(CAN_F12R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F12R2_FB22 */
#define CAN_F12R2_FB22			CAN_F12R2_FB22_Msk
/** @brief Bit position of the `CAN_F12R2_FB23` field @def CAN_F12R2_FB23_Pos */
#define CAN_F12R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB23` field @def CAN_F12R2_FB23_Msk */
#define CAN_F12R2_FB23_Msk		REG_BIT_MASK(CAN_F12R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F12R2_FB23 */
#define CAN_F12R2_FB23			CAN_F12R2_FB23_Msk
/** @brief Bit position of the `CAN_F12R2_FB24` field @def CAN_F12R2_FB24_Pos */
#define CAN_F12R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB24` field @def CAN_F12R2_FB24_Msk */
#define CAN_F12R2_FB24_Msk		REG_BIT_MASK(CAN_F12R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F12R2_FB24 */
#define CAN_F12R2_FB24			CAN_F12R2_FB24_Msk
/** @brief Bit position of the `CAN_F12R2_FB25` field @def CAN_F12R2_FB25_Pos */
#define CAN_F12R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB25` field @def CAN_F12R2_FB25_Msk */
#define CAN_F12R2_FB25_Msk		REG_BIT_MASK(CAN_F12R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F12R2_FB25 */
#define CAN_F12R2_FB25			CAN_F12R2_FB25_Msk
/** @brief Bit position of the `CAN_F12R2_FB26` field @def CAN_F12R2_FB26_Pos */
#define CAN_F12R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB26` field @def CAN_F12R2_FB26_Msk */
#define CAN_F12R2_FB26_Msk		REG_BIT_MASK(CAN_F12R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F12R2_FB26 */
#define CAN_F12R2_FB26			CAN_F12R2_FB26_Msk
/** @brief Bit position of the `CAN_F12R2_FB27` field @def CAN_F12R2_FB27_Pos */
#define CAN_F12R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB27` field @def CAN_F12R2_FB27_Msk */
#define CAN_F12R2_FB27_Msk		REG_BIT_MASK(CAN_F12R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F12R2_FB27 */
#define CAN_F12R2_FB27			CAN_F12R2_FB27_Msk
/** @brief Bit position of the `CAN_F12R2_FB28` field @def CAN_F12R2_FB28_Pos */
#define CAN_F12R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB28` field @def CAN_F12R2_FB28_Msk */
#define CAN_F12R2_FB28_Msk		REG_BIT_MASK(CAN_F12R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F12R2_FB28 */
#define CAN_F12R2_FB28			CAN_F12R2_FB28_Msk
/** @brief Bit position of the `CAN_F12R2_FB29` field @def CAN_F12R2_FB29_Pos */
#define CAN_F12R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB29` field @def CAN_F12R2_FB29_Msk */
#define CAN_F12R2_FB29_Msk		REG_BIT_MASK(CAN_F12R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F12R2_FB29 */
#define CAN_F12R2_FB29			CAN_F12R2_FB29_Msk
/** @brief Bit position of the `CAN_F12R2_FB30` field @def CAN_F12R2_FB30_Pos */
#define CAN_F12R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB30` field @def CAN_F12R2_FB30_Msk */
#define CAN_F12R2_FB30_Msk		REG_BIT_MASK(CAN_F12R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F12R2_FB30 */
#define CAN_F12R2_FB30			CAN_F12R2_FB30_Msk
/** @brief Bit position of the `CAN_F12R2_FB31` field @def CAN_F12R2_FB31_Pos */
#define CAN_F12R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F12R2_FB31` field @def CAN_F12R2_FB31_Msk */
#define CAN_F12R2_FB31_Msk		REG_BIT_MASK(CAN_F12R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F12R2_FB31 */
#define CAN_F12R2_FB31			CAN_F12R2_FB31_Msk

// ---------------------------------- CAN_F13R2 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `CAN_F13R2_FB0` field @def CAN_F13R2_FB0_Pos */
#define CAN_F13R2_FB0_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB0` field @def CAN_F13R2_FB0_Msk */
#define CAN_F13R2_FB0_Msk		REG_BIT_MASK(CAN_F13R2_FB0_Pos)
/** @brief Filter bit 0 @def CAN_F13R2_FB0 */
#define CAN_F13R2_FB0			CAN_F13R2_FB0_Msk
/** @brief Bit position of the `CAN_F13R2_FB1` field @def CAN_F13R2_FB1_Pos */
#define CAN_F13R2_FB1_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB1` field @def CAN_F13R2_FB1_Msk */
#define CAN_F13R2_FB1_Msk		REG_BIT_MASK(CAN_F13R2_FB1_Pos)
/** @brief Filter bit 1 @def CAN_F13R2_FB1 */
#define CAN_F13R2_FB1			CAN_F13R2_FB1_Msk
/** @brief Bit position of the `CAN_F13R2_FB2` field @def CAN_F13R2_FB2_Pos */
#define CAN_F13R2_FB2_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB2` field @def CAN_F13R2_FB2_Msk */
#define CAN_F13R2_FB2_Msk		REG_BIT_MASK(CAN_F13R2_FB2_Pos)
/** @brief Filter bit 2 @def CAN_F13R2_FB2 */
#define CAN_F13R2_FB2			CAN_F13R2_FB2_Msk
/** @brief Bit position of the `CAN_F13R2_FB3` field @def CAN_F13R2_FB3_Pos */
#define CAN_F13R2_FB3_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB3` field @def CAN_F13R2_FB3_Msk */
#define CAN_F13R2_FB3_Msk		REG_BIT_MASK(CAN_F13R2_FB3_Pos)
/** @brief Filter bit 3 @def CAN_F13R2_FB3 */
#define CAN_F13R2_FB3			CAN_F13R2_FB3_Msk
/** @brief Bit position of the `CAN_F13R2_FB4` field @def CAN_F13R2_FB4_Pos */
#define CAN_F13R2_FB4_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB4` field @def CAN_F13R2_FB4_Msk */
#define CAN_F13R2_FB4_Msk		REG_BIT_MASK(CAN_F13R2_FB4_Pos)
/** @brief Filter bit 4 @def CAN_F13R2_FB4 */
#define CAN_F13R2_FB4			CAN_F13R2_FB4_Msk
/** @brief Bit position of the `CAN_F13R2_FB5` field @def CAN_F13R2_FB5_Pos */
#define CAN_F13R2_FB5_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB5` field @def CAN_F13R2_FB5_Msk */
#define CAN_F13R2_FB5_Msk		REG_BIT_MASK(CAN_F13R2_FB5_Pos)
/** @brief Filter bit 5 @def CAN_F13R2_FB5 */
#define CAN_F13R2_FB5			CAN_F13R2_FB5_Msk
/** @brief Bit position of the `CAN_F13R2_FB6` field @def CAN_F13R2_FB6_Pos */
#define CAN_F13R2_FB6_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB6` field @def CAN_F13R2_FB6_Msk */
#define CAN_F13R2_FB6_Msk		REG_BIT_MASK(CAN_F13R2_FB6_Pos)
/** @brief Filter bit 6 @def CAN_F13R2_FB6 */
#define CAN_F13R2_FB6			CAN_F13R2_FB6_Msk
/** @brief Bit position of the `CAN_F13R2_FB7` field @def CAN_F13R2_FB7_Pos */
#define CAN_F13R2_FB7_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB7` field @def CAN_F13R2_FB7_Msk */
#define CAN_F13R2_FB7_Msk		REG_BIT_MASK(CAN_F13R2_FB7_Pos)
/** @brief Filter bit 7 @def CAN_F13R2_FB7 */
#define CAN_F13R2_FB7			CAN_F13R2_FB7_Msk
/** @brief Bit position of the `CAN_F13R2_FB8` field @def CAN_F13R2_FB8_Pos */
#define CAN_F13R2_FB8_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB8` field @def CAN_F13R2_FB8_Msk */
#define CAN_F13R2_FB8_Msk		REG_BIT_MASK(CAN_F13R2_FB8_Pos)
/** @brief Filter bit 8 @def CAN_F13R2_FB8 */
#define CAN_F13R2_FB8			CAN_F13R2_FB8_Msk
/** @brief Bit position of the `CAN_F13R2_FB9` field @def CAN_F13R2_FB9_Pos */
#define CAN_F13R2_FB9_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB9` field @def CAN_F13R2_FB9_Msk */
#define CAN_F13R2_FB9_Msk		REG_BIT_MASK(CAN_F13R2_FB9_Pos)
/** @brief Filter bit 9 @def CAN_F13R2_FB9 */
#define CAN_F13R2_FB9			CAN_F13R2_FB9_Msk
/** @brief Bit position of the `CAN_F13R2_FB10` field @def CAN_F13R2_FB10_Pos */
#define CAN_F13R2_FB10_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB10` field @def CAN_F13R2_FB10_Msk */
#define CAN_F13R2_FB10_Msk		REG_BIT_MASK(CAN_F13R2_FB10_Pos)
/** @brief Filter bit 10 @def CAN_F13R2_FB10 */
#define CAN_F13R2_FB10			CAN_F13R2_FB10_Msk
/** @brief Bit position of the `CAN_F13R2_FB11` field @def CAN_F13R2_FB11_Pos */
#define CAN_F13R2_FB11_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB11` field @def CAN_F13R2_FB11_Msk */
#define CAN_F13R2_FB11_Msk		REG_BIT_MASK(CAN_F13R2_FB11_Pos)
/** @brief Filter bit 11 @def CAN_F13R2_FB11 */
#define CAN_F13R2_FB11			CAN_F13R2_FB11_Msk
/** @brief Bit position of the `CAN_F13R2_FB12` field @def CAN_F13R2_FB12_Pos */
#define CAN_F13R2_FB12_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB12` field @def CAN_F13R2_FB12_Msk */
#define CAN_F13R2_FB12_Msk		REG_BIT_MASK(CAN_F13R2_FB12_Pos)
/** @brief Filter bit 12 @def CAN_F13R2_FB12 */
#define CAN_F13R2_FB12			CAN_F13R2_FB12_Msk
/** @brief Bit position of the `CAN_F13R2_FB13` field @def CAN_F13R2_FB13_Pos */
#define CAN_F13R2_FB13_Pos		((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB13` field @def CAN_F13R2_FB13_Msk */
#define CAN_F13R2_FB13_Msk		REG_BIT_MASK(CAN_F13R2_FB13_Pos)
/** @brief Filter bit 13 @def CAN_F13R2_FB13 */
#define CAN_F13R2_FB13			CAN_F13R2_FB13_Msk
/** @brief Bit position of the `CAN_F13R2_FB14` field @def CAN_F13R2_FB14_Pos */
#define CAN_F13R2_FB14_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB14` field @def CAN_F13R2_FB14_Msk */
#define CAN_F13R2_FB14_Msk		REG_BIT_MASK(CAN_F13R2_FB14_Pos)
/** @brief Filter bit 14 @def CAN_F13R2_FB14 */
#define CAN_F13R2_FB14			CAN_F13R2_FB14_Msk
/** @brief Bit position of the `CAN_F13R2_FB15` field @def CAN_F13R2_FB15_Pos */
#define CAN_F13R2_FB15_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB15` field @def CAN_F13R2_FB15_Msk */
#define CAN_F13R2_FB15_Msk		REG_BIT_MASK(CAN_F13R2_FB15_Pos)
/** @brief Filter bit 15 @def CAN_F13R2_FB15 */
#define CAN_F13R2_FB15			CAN_F13R2_FB15_Msk
/** @brief Bit position of the `CAN_F13R2_FB16` field @def CAN_F13R2_FB16_Pos */
#define CAN_F13R2_FB16_Pos		((reg_bit_pos_t) 16U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB16` field @def CAN_F13R2_FB16_Msk */
#define CAN_F13R2_FB16_Msk		REG_BIT_MASK(CAN_F13R2_FB16_Pos)
/** @brief Filter bit 16 @def CAN_F13R2_FB16 */
#define CAN_F13R2_FB16			CAN_F13R2_FB16_Msk
/** @brief Bit position of the `CAN_F13R2_FB17` field @def CAN_F13R2_FB17_Pos */
#define CAN_F13R2_FB17_Pos		((reg_bit_pos_t) 17U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB17` field @def CAN_F13R2_FB17_Msk */
#define CAN_F13R2_FB17_Msk		REG_BIT_MASK(CAN_F13R2_FB17_Pos)
/** @brief Filter bit 17 @def CAN_F13R2_FB17 */
#define CAN_F13R2_FB17			CAN_F13R2_FB17_Msk
/** @brief Bit position of the `CAN_F13R2_FB18` field @def CAN_F13R2_FB18_Pos */
#define CAN_F13R2_FB18_Pos		((reg_bit_pos_t) 18U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB18` field @def CAN_F13R2_FB18_Msk */
#define CAN_F13R2_FB18_Msk		REG_BIT_MASK(CAN_F13R2_FB18_Pos)
/** @brief Filter bit 18 @def CAN_F13R2_FB18 */
#define CAN_F13R2_FB18			CAN_F13R2_FB18_Msk
/** @brief Bit position of the `CAN_F13R2_FB19` field @def CAN_F13R2_FB19_Pos */
#define CAN_F13R2_FB19_Pos		((reg_bit_pos_t) 19U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB19` field @def CAN_F13R2_FB19_Msk */
#define CAN_F13R2_FB19_Msk		REG_BIT_MASK(CAN_F13R2_FB19_Pos)
/** @brief Filter bit 19 @def CAN_F13R2_FB19 */
#define CAN_F13R2_FB19			CAN_F13R2_FB19_Msk
/** @brief Bit position of the `CAN_F13R2_FB20` field @def CAN_F13R2_FB20_Pos */
#define CAN_F13R2_FB20_Pos		((reg_bit_pos_t) 20U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB20` field @def CAN_F13R2_FB20_Msk */
#define CAN_F13R2_FB20_Msk		REG_BIT_MASK(CAN_F13R2_FB20_Pos)
/** @brief Filter bit 20 @def CAN_F13R2_FB20 */
#define CAN_F13R2_FB20			CAN_F13R2_FB20_Msk
/** @brief Bit position of the `CAN_F13R2_FB21` field @def CAN_F13R2_FB21_Pos */
#define CAN_F13R2_FB21_Pos		((reg_bit_pos_t) 21U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB21` field @def CAN_F13R2_FB21_Msk */
#define CAN_F13R2_FB21_Msk		REG_BIT_MASK(CAN_F13R2_FB21_Pos)
/** @brief Filter bit 21 @def CAN_F13R2_FB21 */
#define CAN_F13R2_FB21			CAN_F13R2_FB21_Msk
/** @brief Bit position of the `CAN_F13R2_FB22` field @def CAN_F13R2_FB22_Pos */
#define CAN_F13R2_FB22_Pos		((reg_bit_pos_t) 22U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB22` field @def CAN_F13R2_FB22_Msk */
#define CAN_F13R2_FB22_Msk		REG_BIT_MASK(CAN_F13R2_FB22_Pos)
/** @brief Filter bit 22 @def CAN_F13R2_FB22 */
#define CAN_F13R2_FB22			CAN_F13R2_FB22_Msk
/** @brief Bit position of the `CAN_F13R2_FB23` field @def CAN_F13R2_FB23_Pos */
#define CAN_F13R2_FB23_Pos		((reg_bit_pos_t) 23U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB23` field @def CAN_F13R2_FB23_Msk */
#define CAN_F13R2_FB23_Msk		REG_BIT_MASK(CAN_F13R2_FB23_Pos)
/** @brief Filter bit 23 @def CAN_F13R2_FB23 */
#define CAN_F13R2_FB23			CAN_F13R2_FB23_Msk
/** @brief Bit position of the `CAN_F13R2_FB24` field @def CAN_F13R2_FB24_Pos */
#define CAN_F13R2_FB24_Pos		((reg_bit_pos_t) 24U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB24` field @def CAN_F13R2_FB24_Msk */
#define CAN_F13R2_FB24_Msk		REG_BIT_MASK(CAN_F13R2_FB24_Pos)
/** @brief Filter bit 24 @def CAN_F13R2_FB24 */
#define CAN_F13R2_FB24			CAN_F13R2_FB24_Msk
/** @brief Bit position of the `CAN_F13R2_FB25` field @def CAN_F13R2_FB25_Pos */
#define CAN_F13R2_FB25_Pos		((reg_bit_pos_t) 25U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB25` field @def CAN_F13R2_FB25_Msk */
#define CAN_F13R2_FB25_Msk		REG_BIT_MASK(CAN_F13R2_FB25_Pos)
/** @brief Filter bit 25 @def CAN_F13R2_FB25 */
#define CAN_F13R2_FB25			CAN_F13R2_FB25_Msk
/** @brief Bit position of the `CAN_F13R2_FB26` field @def CAN_F13R2_FB26_Pos */
#define CAN_F13R2_FB26_Pos		((reg_bit_pos_t) 26U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB26` field @def CAN_F13R2_FB26_Msk */
#define CAN_F13R2_FB26_Msk		REG_BIT_MASK(CAN_F13R2_FB26_Pos)
/** @brief Filter bit 26 @def CAN_F13R2_FB26 */
#define CAN_F13R2_FB26			CAN_F13R2_FB26_Msk
/** @brief Bit position of the `CAN_F13R2_FB27` field @def CAN_F13R2_FB27_Pos */
#define CAN_F13R2_FB27_Pos		((reg_bit_pos_t) 27U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB27` field @def CAN_F13R2_FB27_Msk */
#define CAN_F13R2_FB27_Msk		REG_BIT_MASK(CAN_F13R2_FB27_Pos)
/** @brief Filter bit 27 @def CAN_F13R2_FB27 */
#define CAN_F13R2_FB27			CAN_F13R2_FB27_Msk
/** @brief Bit position of the `CAN_F13R2_FB28` field @def CAN_F13R2_FB28_Pos */
#define CAN_F13R2_FB28_Pos		((reg_bit_pos_t) 28U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB28` field @def CAN_F13R2_FB28_Msk */
#define CAN_F13R2_FB28_Msk		REG_BIT_MASK(CAN_F13R2_FB28_Pos)
/** @brief Filter bit 28 @def CAN_F13R2_FB28 */
#define CAN_F13R2_FB28			CAN_F13R2_FB28_Msk
/** @brief Bit position of the `CAN_F13R2_FB29` field @def CAN_F13R2_FB29_Pos */
#define CAN_F13R2_FB29_Pos		((reg_bit_pos_t) 29U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB29` field @def CAN_F13R2_FB29_Msk */
#define CAN_F13R2_FB29_Msk		REG_BIT_MASK(CAN_F13R2_FB29_Pos)
/** @brief Filter bit 29 @def CAN_F13R2_FB29 */
#define CAN_F13R2_FB29			CAN_F13R2_FB29_Msk
/** @brief Bit position of the `CAN_F13R2_FB30` field @def CAN_F13R2_FB30_Pos */
#define CAN_F13R2_FB30_Pos		((reg_bit_pos_t) 30U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB30` field @def CAN_F13R2_FB30_Msk */
#define CAN_F13R2_FB30_Msk		REG_BIT_MASK(CAN_F13R2_FB30_Pos)
/** @brief Filter bit 30 @def CAN_F13R2_FB30 */
#define CAN_F13R2_FB30			CAN_F13R2_FB30_Msk
/** @brief Bit position of the `CAN_F13R2_FB31` field @def CAN_F13R2_FB31_Pos */
#define CAN_F13R2_FB31_Pos		((reg_bit_pos_t) 31U)
/** @brief Register-positioned mask for the `CAN_F13R2_FB31` field @def CAN_F13R2_FB31_Msk */
#define CAN_F13R2_FB31_Msk		REG_BIT_MASK(CAN_F13R2_FB31_Pos)
/** @brief Filter bit 31 @def CAN_F13R2_FB31 */
#define CAN_F13R2_FB31			CAN_F13R2_FB31_Msk

// ==================================================================================================== //
//							Serial Peripheral Interface (SPI) Register Defines							//
// ==================================================================================================== //

// ----------------------------------- SPI_CR1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `SPI_CR1_CPHA` field @def SPI_CR1_CPHA_Pos */
#define SPI_CR1_CPHA_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `SPI_CR1_CPHA` field @def SPI_CR1_CPHA_Msk */
#define SPI_CR1_CPHA_Msk			REG_BIT_MASK(SPI_CR1_CPHA_Pos)
/** @brief Clock Phase @def SPI_CR1_CPHA */
#define SPI_CR1_CPHA				SPI_CR1_CPHA_Msk
/** @brief Bit position of the `SPI_CR1_CPOL` field @def SPI_CR1_CPOL_Pos */
#define SPI_CR1_CPOL_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `SPI_CR1_CPOL` field @def SPI_CR1_CPOL_Msk */
#define SPI_CR1_CPOL_Msk			REG_BIT_MASK(SPI_CR1_CPOL_Pos)
/** @brief Clock Polarity @def SPI_CR1_CPOL */
#define SPI_CR1_CPOL				SPI_CR1_CPOL_Msk
/** @brief Bit position of the `SPI_CR1_MSTR` field @def SPI_CR1_MSTR_Pos */
#define SPI_CR1_MSTR_Pos			((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `SPI_CR1_MSTR` field @def SPI_CR1_MSTR_Msk */
#define SPI_CR1_MSTR_Msk			REG_BIT_MASK(SPI_CR1_MSTR_Pos)
/** @brief Master Selection @def SPI_CR1_MSTR */
#define SPI_CR1_MSTR				SPI_CR1_MSTR_Msk

/** @brief Bit position of the `SPI_CR1_BR` field @def SPI_CR1_BR_Pos */
#define SPI_CR1_BR_Pos				((reg_bit_pos_t) 3U)
/** @brief Width of the `SPI_CR1_BR` field @def SPI_CR1_BR_Width */
#define SPI_CR1_BR_Width			((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `SPI_CR1_BR` field @def SPI_CR1_BR_Msk */
#define SPI_CR1_BR_Msk				REG_FIELD_MASK(SPI_CR1_BR_Pos, SPI_CR1_BR_Width)
/** @brief BR[2:0] bits (Baud Rate Control) @def SPI_CR1_BR */
#define SPI_CR1_BR					SPI_CR1_BR_Msk
/** @brief Register or selector value represented by `SPI_CR1_BR_0` @def SPI_CR1_BR_0 */
#define SPI_CR1_BR_0				(0x1UL << SPI_CR1_BR_Pos)
/** @brief Register or selector value represented by `SPI_CR1_BR_1` @def SPI_CR1_BR_1 */
#define SPI_CR1_BR_1				(0x2UL << SPI_CR1_BR_Pos)
/** @brief Register or selector value represented by `SPI_CR1_BR_2` @def SPI_CR1_BR_2 */
#define SPI_CR1_BR_2				(0x4UL << SPI_CR1_BR_Pos)

/** @brief Bit position of the `SPI_CR1_SPE` field @def SPI_CR1_SPE_Pos */
#define SPI_CR1_SPE_Pos				((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `SPI_CR1_SPE` field @def SPI_CR1_SPE_Msk */
#define SPI_CR1_SPE_Msk				REG_BIT_MASK(SPI_CR1_SPE_Pos)
/** @brief SPI Enable @def SPI_CR1_SPE */
#define SPI_CR1_SPE					SPI_CR1_SPE_Msk
/** @brief Bit position of the `SPI_CR1_LSBFIRST` field @def SPI_CR1_LSBFIRST_Pos */
#define SPI_CR1_LSBFIRST_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `SPI_CR1_LSBFIRST` field @def SPI_CR1_LSBFIRST_Msk */
#define SPI_CR1_LSBFIRST_Msk		REG_BIT_MASK(SPI_CR1_LSBFIRST_Pos)
/** @brief Frame Format @def SPI_CR1_LSBFIRST */
#define SPI_CR1_LSBFIRST			SPI_CR1_LSBFIRST_Msk
/** @brief Bit position of the `SPI_CR1_SSI` field @def SPI_CR1_SSI_Pos */
#define SPI_CR1_SSI_Pos				((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `SPI_CR1_SSI` field @def SPI_CR1_SSI_Msk */
#define SPI_CR1_SSI_Msk				REG_BIT_MASK(SPI_CR1_SSI_Pos)
/** @brief Internal slave select @def SPI_CR1_SSI */
#define SPI_CR1_SSI					SPI_CR1_SSI_Msk
/** @brief Bit position of the `SPI_CR1_SSM` field @def SPI_CR1_SSM_Pos */
#define SPI_CR1_SSM_Pos				((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `SPI_CR1_SSM` field @def SPI_CR1_SSM_Msk */
#define SPI_CR1_SSM_Msk				REG_BIT_MASK(SPI_CR1_SSM_Pos)
/** @brief Software slave management @def SPI_CR1_SSM */
#define SPI_CR1_SSM					SPI_CR1_SSM_Msk
/** @brief Bit position of the `SPI_CR1_RXONLY` field @def SPI_CR1_RXONLY_Pos */
#define SPI_CR1_RXONLY_Pos			((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `SPI_CR1_RXONLY` field @def SPI_CR1_RXONLY_Msk */
#define SPI_CR1_RXONLY_Msk			REG_BIT_MASK(SPI_CR1_RXONLY_Pos)
/** @brief Receive only @def SPI_CR1_RXONLY */
#define SPI_CR1_RXONLY				SPI_CR1_RXONLY_Msk
/** @brief Bit position of the `SPI_CR1_DFF` field @def SPI_CR1_DFF_Pos */
#define SPI_CR1_DFF_Pos				((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `SPI_CR1_DFF` field @def SPI_CR1_DFF_Msk */
#define SPI_CR1_DFF_Msk				REG_BIT_MASK(SPI_CR1_DFF_Pos)
/** @brief Data Frame Format @def SPI_CR1_DFF */
#define SPI_CR1_DFF					SPI_CR1_DFF_Msk
/** @brief Bit position of the `SPI_CR1_CRCNEXT` field @def SPI_CR1_CRCNEXT_Pos */
#define SPI_CR1_CRCNEXT_Pos			((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `SPI_CR1_CRCNEXT` field @def SPI_CR1_CRCNEXT_Msk */
#define SPI_CR1_CRCNEXT_Msk			REG_BIT_MASK(SPI_CR1_CRCNEXT_Pos)
/** @brief Transmit CRC next @def SPI_CR1_CRCNEXT */
#define SPI_CR1_CRCNEXT				SPI_CR1_CRCNEXT_Msk
/** @brief Bit position of the `SPI_CR1_CRCEN` field @def SPI_CR1_CRCEN_Pos */
#define SPI_CR1_CRCEN_Pos			((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `SPI_CR1_CRCEN` field @def SPI_CR1_CRCEN_Msk */
#define SPI_CR1_CRCEN_Msk			REG_BIT_MASK(SPI_CR1_CRCEN_Pos)
/** @brief Hardware CRC calculation enable @def SPI_CR1_CRCEN */
#define SPI_CR1_CRCEN				SPI_CR1_CRCEN_Msk
/** @brief Bit position of the `SPI_CR1_BIDIOE` field @def SPI_CR1_BIDIOE_Pos */
#define SPI_CR1_BIDIOE_Pos			((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `SPI_CR1_BIDIOE` field @def SPI_CR1_BIDIOE_Msk */
#define SPI_CR1_BIDIOE_Msk			REG_BIT_MASK(SPI_CR1_BIDIOE_Pos)
/** @brief Output enable in bidirectional mode @def SPI_CR1_BIDIOE */
#define SPI_CR1_BIDIOE				SPI_CR1_BIDIOE_Msk
/** @brief Bit position of the `SPI_CR1_BIDIMODE` field @def SPI_CR1_BIDIMODE_Pos */
#define SPI_CR1_BIDIMODE_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `SPI_CR1_BIDIMODE` field @def SPI_CR1_BIDIMODE_Msk */
#define SPI_CR1_BIDIMODE_Msk		REG_BIT_MASK(SPI_CR1_BIDIMODE_Pos)
/** @brief Bidirectional data mode enable @def SPI_CR1_BIDIMODE */
#define SPI_CR1_BIDIMODE			SPI_CR1_BIDIMODE_Msk

// ----------------------------------- SPI_CR2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `SPI_CR2_RXDMAEN` field @def SPI_CR2_RXDMAEN_Pos */
#define SPI_CR2_RXDMAEN_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `SPI_CR2_RXDMAEN` field @def SPI_CR2_RXDMAEN_Msk */
#define SPI_CR2_RXDMAEN_Msk		REG_BIT_MASK(SPI_CR2_RXDMAEN_Pos)
/** @brief Rx Buffer DMA Enable @def SPI_CR2_RXDMAEN */
#define SPI_CR2_RXDMAEN			SPI_CR2_RXDMAEN_Msk
/** @brief Bit position of the `SPI_CR2_TXDMAEN` field @def SPI_CR2_TXDMAEN_Pos */
#define SPI_CR2_TXDMAEN_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `SPI_CR2_TXDMAEN` field @def SPI_CR2_TXDMAEN_Msk */
#define SPI_CR2_TXDMAEN_Msk		REG_BIT_MASK(SPI_CR2_TXDMAEN_Pos)
/** @brief Tx Buffer DMA Enable @def SPI_CR2_TXDMAEN */
#define SPI_CR2_TXDMAEN			SPI_CR2_TXDMAEN_Msk
/** @brief Bit position of the `SPI_CR2_SSOE` field @def SPI_CR2_SSOE_Pos */
#define SPI_CR2_SSOE_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `SPI_CR2_SSOE` field @def SPI_CR2_SSOE_Msk */
#define SPI_CR2_SSOE_Msk		REG_BIT_MASK(SPI_CR2_SSOE_Pos)
/** @brief SS Output Enable @def SPI_CR2_SSOE */
#define SPI_CR2_SSOE			SPI_CR2_SSOE_Msk
/** @brief Bit position of the `SPI_CR2_ERRIE` field @def SPI_CR2_ERRIE_Pos */
#define SPI_CR2_ERRIE_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `SPI_CR2_ERRIE` field @def SPI_CR2_ERRIE_Msk */
#define SPI_CR2_ERRIE_Msk		REG_BIT_MASK(SPI_CR2_ERRIE_Pos)
/** @brief Error Interrupt Enable @def SPI_CR2_ERRIE */
#define SPI_CR2_ERRIE			SPI_CR2_ERRIE_Msk
/** @brief Bit position of the `SPI_CR2_RXNEIE` field @def SPI_CR2_RXNEIE_Pos */
#define SPI_CR2_RXNEIE_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `SPI_CR2_RXNEIE` field @def SPI_CR2_RXNEIE_Msk */
#define SPI_CR2_RXNEIE_Msk		REG_BIT_MASK(SPI_CR2_RXNEIE_Pos)
/** @brief RX buffer Not Empty Interrupt Enable @def SPI_CR2_RXNEIE */
#define SPI_CR2_RXNEIE			SPI_CR2_RXNEIE_Msk
/** @brief Bit position of the `SPI_CR2_TXEIE` field @def SPI_CR2_TXEIE_Pos */
#define SPI_CR2_TXEIE_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `SPI_CR2_TXEIE` field @def SPI_CR2_TXEIE_Msk */
#define SPI_CR2_TXEIE_Msk		REG_BIT_MASK(SPI_CR2_TXEIE_Pos)
/** @brief Tx buffer Empty Interrupt Enable @def SPI_CR2_TXEIE */
#define SPI_CR2_TXEIE			SPI_CR2_TXEIE_Msk

// ----------------------------------- SPI_SR Register Bit Defines ------------------------------------ //
/** @brief Bit position of the `SPI_SR_RXNE` field @def SPI_SR_RXNE_Pos */
#define SPI_SR_RXNE_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `SPI_SR_RXNE` field @def SPI_SR_RXNE_Msk */
#define SPI_SR_RXNE_Msk			REG_BIT_MASK(SPI_SR_RXNE_Pos)
/** @brief Receive buffer Not Empty @def SPI_SR_RXNE */
#define SPI_SR_RXNE				SPI_SR_RXNE_Msk
/** @brief Bit position of the `SPI_SR_TXE` field @def SPI_SR_TXE_Pos */
#define SPI_SR_TXE_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `SPI_SR_TXE` field @def SPI_SR_TXE_Msk */
#define SPI_SR_TXE_Msk			REG_BIT_MASK(SPI_SR_TXE_Pos)
/** @brief Transmit buffer Empty @def SPI_SR_TXE */
#define SPI_SR_TXE				SPI_SR_TXE_Msk
/** @brief Bit position of the `SPI_SR_CHSIDE` field @def SPI_SR_CHSIDE_Pos */
#define SPI_SR_CHSIDE_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `SPI_SR_CHSIDE` field @def SPI_SR_CHSIDE_Msk */
#define SPI_SR_CHSIDE_Msk		REG_BIT_MASK(SPI_SR_CHSIDE_Pos)
/** @brief Channel side @def SPI_SR_CHSIDE */
#define SPI_SR_CHSIDE			SPI_SR_CHSIDE_Msk
/** @brief Bit position of the `SPI_SR_UDR` field @def SPI_SR_UDR_Pos */
#define SPI_SR_UDR_Pos			((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `SPI_SR_UDR` field @def SPI_SR_UDR_Msk */
#define SPI_SR_UDR_Msk			REG_BIT_MASK(SPI_SR_UDR_Pos)
/** @brief Underrun flag @def SPI_SR_UDR */
#define SPI_SR_UDR				SPI_SR_UDR_Msk
/** @brief Bit position of the `SPI_SR_CRCERR` field @def SPI_SR_CRCERR_Pos */
#define SPI_SR_CRCERR_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `SPI_SR_CRCERR` field @def SPI_SR_CRCERR_Msk */
#define SPI_SR_CRCERR_Msk		REG_BIT_MASK(SPI_SR_CRCERR_Pos)
/** @brief CRC Error flag @def SPI_SR_CRCERR */
#define SPI_SR_CRCERR			SPI_SR_CRCERR_Msk
/** @brief Bit position of the `SPI_SR_MODF` field @def SPI_SR_MODF_Pos */
#define SPI_SR_MODF_Pos			((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `SPI_SR_MODF` field @def SPI_SR_MODF_Msk */
#define SPI_SR_MODF_Msk			REG_BIT_MASK(SPI_SR_MODF_Pos)
/** @brief Mode fault @def SPI_SR_MODF */
#define SPI_SR_MODF				SPI_SR_MODF_Msk
/** @brief Bit position of the `SPI_SR_OVR` field @def SPI_SR_OVR_Pos */
#define SPI_SR_OVR_Pos			((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `SPI_SR_OVR` field @def SPI_SR_OVR_Msk */
#define SPI_SR_OVR_Msk			REG_BIT_MASK(SPI_SR_OVR_Pos)
/** @brief Overrun flag @def SPI_SR_OVR */
#define SPI_SR_OVR				SPI_SR_OVR_Msk
/** @brief Bit position of the `SPI_SR_BSY` field @def SPI_SR_BSY_Pos */
#define SPI_SR_BSY_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `SPI_SR_BSY` field @def SPI_SR_BSY_Msk */
#define SPI_SR_BSY_Msk			REG_BIT_MASK(SPI_SR_BSY_Pos)
/** @brief Busy flag @def SPI_SR_BSY */
#define SPI_SR_BSY				SPI_SR_BSY_Msk

// ----------------------------------- SPI_DR Register Bit Defines ------------------------------------ //
/** @brief Bit position of the `SPI_DR_DR` field @def SPI_DR_DR_Pos */
#define SPI_DR_DR_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `SPI_DR_DR` field @def SPI_DR_DR_Width */
#define SPI_DR_DR_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `SPI_DR_DR` field @def SPI_DR_DR_Msk */
#define SPI_DR_DR_Msk		REG_FIELD_MASK(SPI_DR_DR_Pos, SPI_DR_DR_Width)
/** @brief Data Register @def SPI_DR_DR */
#define SPI_DR_DR			SPI_DR_DR_Msk

// ---------------------------------- SPI_CRCPR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `SPI_CRCPR_CRCPOLY` field @def SPI_CRCPR_CRCPOLY_Pos */
#define SPI_CRCPR_CRCPOLY_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `SPI_CRCPR_CRCPOLY` field @def SPI_CRCPR_CRCPOLY_Width */
#define SPI_CRCPR_CRCPOLY_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `SPI_CRCPR_CRCPOLY` field @def SPI_CRCPR_CRCPOLY_Msk */
#define SPI_CRCPR_CRCPOLY_Msk		REG_FIELD_MASK(SPI_CRCPR_CRCPOLY_Pos, SPI_CRCPR_CRCPOLY_Width)
/** @brief CRC polynomial register @def SPI_CRCPR_CRCPOLY */
#define SPI_CRCPR_CRCPOLY			SPI_CRCPR_CRCPOLY_Msk

// --------------------------------- SPI_RXCRCR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `SPI_RXCRCR_RXCRC` field @def SPI_RXCRCR_RXCRC_Pos */
#define SPI_RXCRCR_RXCRC_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `SPI_RXCRCR_RXCRC` field @def SPI_RXCRCR_RXCRC_Width */
#define SPI_RXCRCR_RXCRC_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `SPI_RXCRCR_RXCRC` field @def SPI_RXCRCR_RXCRC_Msk */
#define SPI_RXCRCR_RXCRC_Msk		REG_FIELD_MASK(SPI_RXCRCR_RXCRC_Pos, SPI_RXCRCR_RXCRC_Width)
/** @brief Rx CRC Register @def SPI_RXCRCR_RXCRC */
#define SPI_RXCRCR_RXCRC			SPI_RXCRCR_RXCRC_Msk

// --------------------------------- SPI_TXCRCR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `SPI_TXCRCR_TXCRC` field @def SPI_TXCRCR_TXCRC_Pos */
#define SPI_TXCRCR_TXCRC_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `SPI_TXCRCR_TXCRC` field @def SPI_TXCRCR_TXCRC_Width */
#define SPI_TXCRCR_TXCRC_Width		((reg_field_width_t) 16U)
/** @brief Register-positioned mask for the `SPI_TXCRCR_TXCRC` field @def SPI_TXCRCR_TXCRC_Msk */
#define SPI_TXCRCR_TXCRC_Msk		REG_FIELD_MASK(SPI_TXCRCR_TXCRC_Pos, SPI_TXCRCR_TXCRC_Width)
/** @brief Tx CRC Register @def SPI_TXCRCR_TXCRC */
#define SPI_TXCRCR_TXCRC			SPI_TXCRCR_TXCRC_Msk

/** @brief Bit position of the `SPI_I2SCFGR_I2SMOD` field @def SPI_I2SCFGR_I2SMOD_Pos */
#define SPI_I2SCFGR_I2SMOD_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `SPI_I2SCFGR_I2SMOD` field @def SPI_I2SCFGR_I2SMOD_Msk */
#define SPI_I2SCFGR_I2SMOD_Msk		REG_BIT_MASK(SPI_I2SCFGR_I2SMOD_Pos)
/** @brief I2S mode selection @def SPI_I2SCFGR_I2SMOD */
#define SPI_I2SCFGR_I2SMOD			SPI_I2SCFGR_I2SMOD_Msk

// ==================================================================================================== //
//								Inter-Integrated Circuit (I2C) Register Defines							//
// ==================================================================================================== //

// ----------------------------------- I2C_CR1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `I2C_CR1_PE` field @def I2C_CR1_PE_Pos */
#define I2C_CR1_PE_Pos				((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `I2C_CR1_PE` field @def I2C_CR1_PE_Msk */
#define I2C_CR1_PE_Msk				REG_BIT_MASK(I2C_CR1_PE_Pos)
/** @brief Peripheral Enable @def I2C_CR1_PE */
#define I2C_CR1_PE					I2C_CR1_PE_Msk
/** @brief Bit position of the `I2C_CR1_SMBUS` field @def I2C_CR1_SMBUS_Pos */
#define I2C_CR1_SMBUS_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `I2C_CR1_SMBUS` field @def I2C_CR1_SMBUS_Msk */
#define I2C_CR1_SMBUS_Msk			REG_BIT_MASK(I2C_CR1_SMBUS_Pos)
/** @brief SMBus Mode @def I2C_CR1_SMBUS */
#define I2C_CR1_SMBUS				I2C_CR1_SMBUS_Msk
/** @brief Bit position of the `I2C_CR1_SMBTYPE` field @def I2C_CR1_SMBTYPE_Pos */
#define I2C_CR1_SMBTYPE_Pos			((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `I2C_CR1_SMBTYPE` field @def I2C_CR1_SMBTYPE_Msk */
#define I2C_CR1_SMBTYPE_Msk			REG_BIT_MASK(I2C_CR1_SMBTYPE_Pos)
/** @brief SMBus Type @def I2C_CR1_SMBTYPE */
#define I2C_CR1_SMBTYPE				I2C_CR1_SMBTYPE_Msk
/** @brief Bit position of the `I2C_CR1_ENARP` field @def I2C_CR1_ENARP_Pos */
#define I2C_CR1_ENARP_Pos			((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `I2C_CR1_ENARP` field @def I2C_CR1_ENARP_Msk */
#define I2C_CR1_ENARP_Msk			REG_BIT_MASK(I2C_CR1_ENARP_Pos)
/** @brief ARP Enable @def I2C_CR1_ENARP */
#define I2C_CR1_ENARP				I2C_CR1_ENARP_Msk
/** @brief Bit position of the `I2C_CR1_ENPEC` field @def I2C_CR1_ENPEC_Pos */
#define I2C_CR1_ENPEC_Pos			((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `I2C_CR1_ENPEC` field @def I2C_CR1_ENPEC_Msk */
#define I2C_CR1_ENPEC_Msk			REG_BIT_MASK(I2C_CR1_ENPEC_Pos)
/** @brief PEC Enable @def I2C_CR1_ENPEC */
#define I2C_CR1_ENPEC				I2C_CR1_ENPEC_Msk
/** @brief Bit position of the `I2C_CR1_ENGC` field @def I2C_CR1_ENGC_Pos */
#define I2C_CR1_ENGC_Pos			((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `I2C_CR1_ENGC` field @def I2C_CR1_ENGC_Msk */
#define I2C_CR1_ENGC_Msk			REG_BIT_MASK(I2C_CR1_ENGC_Pos)
/** @brief General Call Enable @def I2C_CR1_ENGC */
#define I2C_CR1_ENGC				I2C_CR1_ENGC_Msk
/** @brief Bit position of the `I2C_CR1_NOSTRETCH` field @def I2C_CR1_NOSTRETCH_Pos */
#define I2C_CR1_NOSTRETCH_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `I2C_CR1_NOSTRETCH` field @def I2C_CR1_NOSTRETCH_Msk */
#define I2C_CR1_NOSTRETCH_Msk		REG_BIT_MASK(I2C_CR1_NOSTRETCH_Pos)
/** @brief Clock Stretching Disable (Slave mode) @def I2C_CR1_NOSTRETCH */
#define I2C_CR1_NOSTRETCH			I2C_CR1_NOSTRETCH_Msk
/** @brief Bit position of the `I2C_CR1_START` field @def I2C_CR1_START_Pos */
#define I2C_CR1_START_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `I2C_CR1_START` field @def I2C_CR1_START_Msk */
#define I2C_CR1_START_Msk			REG_BIT_MASK(I2C_CR1_START_Pos)
/** @brief Start Generation @def I2C_CR1_START */
#define I2C_CR1_START				I2C_CR1_START_Msk
/** @brief Bit position of the `I2C_CR1_STOP` field @def I2C_CR1_STOP_Pos */
#define I2C_CR1_STOP_Pos			((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `I2C_CR1_STOP` field @def I2C_CR1_STOP_Msk */
#define I2C_CR1_STOP_Msk			REG_BIT_MASK(I2C_CR1_STOP_Pos)
/** @brief Stop Generation @def I2C_CR1_STOP */
#define I2C_CR1_STOP				I2C_CR1_STOP_Msk
/** @brief Bit position of the `I2C_CR1_ACK` field @def I2C_CR1_ACK_Pos */
#define I2C_CR1_ACK_Pos				((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `I2C_CR1_ACK` field @def I2C_CR1_ACK_Msk */
#define I2C_CR1_ACK_Msk				REG_BIT_MASK(I2C_CR1_ACK_Pos)
/** @brief Acknowledge Enable @def I2C_CR1_ACK */
#define I2C_CR1_ACK					I2C_CR1_ACK_Msk
/** @brief Bit position of the `I2C_CR1_POS` field @def I2C_CR1_POS_Pos */
#define I2C_CR1_POS_Pos				((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `I2C_CR1_POS` field @def I2C_CR1_POS_Msk */
#define I2C_CR1_POS_Msk				REG_BIT_MASK(I2C_CR1_POS_Pos)
/** @brief Acknowledge/PEC Position (for data reception) @def I2C_CR1_POS */
#define I2C_CR1_POS					I2C_CR1_POS_Msk
/** @brief Bit position of the `I2C_CR1_PEC` field @def I2C_CR1_PEC_Pos */
#define I2C_CR1_PEC_Pos				((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `I2C_CR1_PEC` field @def I2C_CR1_PEC_Msk */
#define I2C_CR1_PEC_Msk				REG_BIT_MASK(I2C_CR1_PEC_Pos)
/** @brief Packet Error Checking @def I2C_CR1_PEC */
#define I2C_CR1_PEC					I2C_CR1_PEC_Msk
/** @brief Bit position of the `I2C_CR1_ALERT` field @def I2C_CR1_ALERT_Pos */
#define I2C_CR1_ALERT_Pos			((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `I2C_CR1_ALERT` field @def I2C_CR1_ALERT_Msk */
#define I2C_CR1_ALERT_Msk			REG_BIT_MASK(I2C_CR1_ALERT_Pos)
/** @brief SMBus Alert @def I2C_CR1_ALERT */
#define I2C_CR1_ALERT				I2C_CR1_ALERT_Msk
/** @brief Bit position of the `I2C_CR1_SWRST` field @def I2C_CR1_SWRST_Pos */
#define I2C_CR1_SWRST_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `I2C_CR1_SWRST` field @def I2C_CR1_SWRST_Msk */
#define I2C_CR1_SWRST_Msk			REG_BIT_MASK(I2C_CR1_SWRST_Pos)
/** @brief Software Reset @def I2C_CR1_SWRST */
#define I2C_CR1_SWRST				I2C_CR1_SWRST_Msk

// ----------------------------------- I2C_CR2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `I2C_CR2_FREQ` field @def I2C_CR2_FREQ_Pos */
#define I2C_CR2_FREQ_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `I2C_CR2_FREQ` field @def I2C_CR2_FREQ_Width */
#define I2C_CR2_FREQ_Width		((reg_field_width_t) 6U)
/** @brief Register-positioned mask for the `I2C_CR2_FREQ` field @def I2C_CR2_FREQ_Msk */
#define I2C_CR2_FREQ_Msk		REG_FIELD_MASK(I2C_CR2_FREQ_Pos, I2C_CR2_FREQ_Width)
/** @brief FREQ[5:0] bits (Peripheral Clock Frequency) @def I2C_CR2_FREQ */
#define I2C_CR2_FREQ			I2C_CR2_FREQ_Msk
/** @brief Register or selector value represented by `I2C_CR2_FREQ_0` @def I2C_CR2_FREQ_0 */
#define I2C_CR2_FREQ_0			(0x01UL << I2C_CR2_FREQ_Pos)
/** @brief Register or selector value represented by `I2C_CR2_FREQ_1` @def I2C_CR2_FREQ_1 */
#define I2C_CR2_FREQ_1			(0x02UL << I2C_CR2_FREQ_Pos)
/** @brief Register or selector value represented by `I2C_CR2_FREQ_2` @def I2C_CR2_FREQ_2 */
#define I2C_CR2_FREQ_2			(0x04UL << I2C_CR2_FREQ_Pos)
/** @brief Register or selector value represented by `I2C_CR2_FREQ_3` @def I2C_CR2_FREQ_3 */
#define I2C_CR2_FREQ_3			(0x08UL << I2C_CR2_FREQ_Pos)
/** @brief Register or selector value represented by `I2C_CR2_FREQ_4` @def I2C_CR2_FREQ_4 */
#define I2C_CR2_FREQ_4			(0x10UL << I2C_CR2_FREQ_Pos)
/** @brief Register or selector value represented by `I2C_CR2_FREQ_5` @def I2C_CR2_FREQ_5 */
#define I2C_CR2_FREQ_5			(0x20UL << I2C_CR2_FREQ_Pos)

/** @brief Bit position of the `I2C_CR2_ITERREN` field @def I2C_CR2_ITERREN_Pos */
#define I2C_CR2_ITERREN_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `I2C_CR2_ITERREN` field @def I2C_CR2_ITERREN_Msk */
#define I2C_CR2_ITERREN_Msk		REG_BIT_MASK(I2C_CR2_ITERREN_Pos)
/** @brief Error Interrupt Enable @def I2C_CR2_ITERREN */
#define I2C_CR2_ITERREN			I2C_CR2_ITERREN_Msk
/** @brief Bit position of the `I2C_CR2_ITEVTEN` field @def I2C_CR2_ITEVTEN_Pos */
#define I2C_CR2_ITEVTEN_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `I2C_CR2_ITEVTEN` field @def I2C_CR2_ITEVTEN_Msk */
#define I2C_CR2_ITEVTEN_Msk		REG_BIT_MASK(I2C_CR2_ITEVTEN_Pos)
/** @brief Event Interrupt Enable @def I2C_CR2_ITEVTEN */
#define I2C_CR2_ITEVTEN			I2C_CR2_ITEVTEN_Msk
/** @brief Bit position of the `I2C_CR2_ITBUFEN` field @def I2C_CR2_ITBUFEN_Pos */
#define I2C_CR2_ITBUFEN_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `I2C_CR2_ITBUFEN` field @def I2C_CR2_ITBUFEN_Msk */
#define I2C_CR2_ITBUFEN_Msk		REG_BIT_MASK(I2C_CR2_ITBUFEN_Pos)
/** @brief Buffer Interrupt Enable @def I2C_CR2_ITBUFEN */
#define I2C_CR2_ITBUFEN			I2C_CR2_ITBUFEN_Msk
/** @brief Bit position of the `I2C_CR2_DMAEN` field @def I2C_CR2_DMAEN_Pos */
#define I2C_CR2_DMAEN_Pos		((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `I2C_CR2_DMAEN` field @def I2C_CR2_DMAEN_Msk */
#define I2C_CR2_DMAEN_Msk		REG_BIT_MASK(I2C_CR2_DMAEN_Pos)
/** @brief DMA Requests Enable @def I2C_CR2_DMAEN */
#define I2C_CR2_DMAEN			I2C_CR2_DMAEN_Msk
/** @brief Bit position of the `I2C_CR2_LAST` field @def I2C_CR2_LAST_Pos */
#define I2C_CR2_LAST_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `I2C_CR2_LAST` field @def I2C_CR2_LAST_Msk */
#define I2C_CR2_LAST_Msk		REG_BIT_MASK(I2C_CR2_LAST_Pos)
/** @brief DMA Last Transfer @def I2C_CR2_LAST */
#define I2C_CR2_LAST			I2C_CR2_LAST_Msk

// ---------------------------------- I2C_OAR1 Register Bit Defines ----------------------------------- //
/** @brief Interface Address @def I2C_OAR1_ADD1_7 */
#define I2C_OAR1_ADD1_7				0x000000FEU
/** @brief Interface Address @def I2C_OAR1_ADD8_9 */
#define I2C_OAR1_ADD8_9				0x00000300U

/** @brief Bit position of the `I2C_OAR1_ADD0` field @def I2C_OAR1_ADD0_Pos */
#define I2C_OAR1_ADD0_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `I2C_OAR1_ADD0` field @def I2C_OAR1_ADD0_Msk */
#define I2C_OAR1_ADD0_Msk			REG_BIT_MASK(I2C_OAR1_ADD0_Pos)
/** @brief Bit 0 @def I2C_OAR1_ADD0 */
#define I2C_OAR1_ADD0				I2C_OAR1_ADD0_Msk
/** @brief Bit position of the `I2C_OAR1_ADD1` field @def I2C_OAR1_ADD1_Pos */
#define I2C_OAR1_ADD1_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `I2C_OAR1_ADD1` field @def I2C_OAR1_ADD1_Msk */
#define I2C_OAR1_ADD1_Msk			REG_BIT_MASK(I2C_OAR1_ADD1_Pos)
/** @brief Bit 1 @def I2C_OAR1_ADD1 */
#define I2C_OAR1_ADD1				I2C_OAR1_ADD1_Msk
/** @brief Bit position of the `I2C_OAR1_ADD2` field @def I2C_OAR1_ADD2_Pos */
#define I2C_OAR1_ADD2_Pos			((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `I2C_OAR1_ADD2` field @def I2C_OAR1_ADD2_Msk */
#define I2C_OAR1_ADD2_Msk			REG_BIT_MASK(I2C_OAR1_ADD2_Pos)
/** @brief Bit 2 @def I2C_OAR1_ADD2 */
#define I2C_OAR1_ADD2				I2C_OAR1_ADD2_Msk
/** @brief Bit position of the `I2C_OAR1_ADD3` field @def I2C_OAR1_ADD3_Pos */
#define I2C_OAR1_ADD3_Pos			((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `I2C_OAR1_ADD3` field @def I2C_OAR1_ADD3_Msk */
#define I2C_OAR1_ADD3_Msk			REG_BIT_MASK(I2C_OAR1_ADD3_Pos)
/** @brief Bit 3 @def I2C_OAR1_ADD3 */
#define I2C_OAR1_ADD3				I2C_OAR1_ADD3_Msk
/** @brief Bit position of the `I2C_OAR1_ADD4` field @def I2C_OAR1_ADD4_Pos */
#define I2C_OAR1_ADD4_Pos			((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `I2C_OAR1_ADD4` field @def I2C_OAR1_ADD4_Msk */
#define I2C_OAR1_ADD4_Msk			REG_BIT_MASK(I2C_OAR1_ADD4_Pos)
/** @brief Bit 4 @def I2C_OAR1_ADD4 */
#define I2C_OAR1_ADD4				I2C_OAR1_ADD4_Msk
/** @brief Bit position of the `I2C_OAR1_ADD5` field @def I2C_OAR1_ADD5_Pos */
#define I2C_OAR1_ADD5_Pos			((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `I2C_OAR1_ADD5` field @def I2C_OAR1_ADD5_Msk */
#define I2C_OAR1_ADD5_Msk			REG_BIT_MASK(I2C_OAR1_ADD5_Pos)
/** @brief Bit 5 @def I2C_OAR1_ADD5 */
#define I2C_OAR1_ADD5				I2C_OAR1_ADD5_Msk
/** @brief Bit position of the `I2C_OAR1_ADD6` field @def I2C_OAR1_ADD6_Pos */
#define I2C_OAR1_ADD6_Pos			((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `I2C_OAR1_ADD6` field @def I2C_OAR1_ADD6_Msk */
#define I2C_OAR1_ADD6_Msk			REG_BIT_MASK(I2C_OAR1_ADD6_Pos)
/** @brief Bit 6 @def I2C_OAR1_ADD6 */
#define I2C_OAR1_ADD6				I2C_OAR1_ADD6_Msk
/** @brief Bit position of the `I2C_OAR1_ADD7` field @def I2C_OAR1_ADD7_Pos */
#define I2C_OAR1_ADD7_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `I2C_OAR1_ADD7` field @def I2C_OAR1_ADD7_Msk */
#define I2C_OAR1_ADD7_Msk			REG_BIT_MASK(I2C_OAR1_ADD7_Pos)
/** @brief Bit 7 @def I2C_OAR1_ADD7 */
#define I2C_OAR1_ADD7				I2C_OAR1_ADD7_Msk
/** @brief Bit position of the `I2C_OAR1_ADD8` field @def I2C_OAR1_ADD8_Pos */
#define I2C_OAR1_ADD8_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `I2C_OAR1_ADD8` field @def I2C_OAR1_ADD8_Msk */
#define I2C_OAR1_ADD8_Msk			REG_BIT_MASK(I2C_OAR1_ADD8_Pos)
/** @brief Bit 8 @def I2C_OAR1_ADD8 */
#define I2C_OAR1_ADD8				I2C_OAR1_ADD8_Msk
/** @brief Bit position of the `I2C_OAR1_ADD9` field @def I2C_OAR1_ADD9_Pos */
#define I2C_OAR1_ADD9_Pos			((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `I2C_OAR1_ADD9` field @def I2C_OAR1_ADD9_Msk */
#define I2C_OAR1_ADD9_Msk			REG_BIT_MASK(I2C_OAR1_ADD9_Pos)
/** @brief Bit 9 @def I2C_OAR1_ADD9 */
#define I2C_OAR1_ADD9				I2C_OAR1_ADD9_Msk

/** @brief Bit position of the `I2C_OAR1_ADDMODE` field @def I2C_OAR1_ADDMODE_Pos */
#define I2C_OAR1_ADDMODE_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `I2C_OAR1_ADDMODE` field @def I2C_OAR1_ADDMODE_Msk */
#define I2C_OAR1_ADDMODE_Msk		REG_BIT_MASK(I2C_OAR1_ADDMODE_Pos)
/** @brief Addressing Mode (Slave mode) @def I2C_OAR1_ADDMODE */
#define I2C_OAR1_ADDMODE			I2C_OAR1_ADDMODE_Msk

// ---------------------------------- I2C_OAR2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `I2C_OAR2_ENDUAL` field @def I2C_OAR2_ENDUAL_Pos */
#define I2C_OAR2_ENDUAL_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `I2C_OAR2_ENDUAL` field @def I2C_OAR2_ENDUAL_Msk */
#define I2C_OAR2_ENDUAL_Msk		REG_BIT_MASK(I2C_OAR2_ENDUAL_Pos)
/** @brief Dual addressing mode enable @def I2C_OAR2_ENDUAL */
#define I2C_OAR2_ENDUAL			I2C_OAR2_ENDUAL_Msk
/** @brief Bit position of the `I2C_OAR2_ADD2` field @def I2C_OAR2_ADD2_Pos */
#define I2C_OAR2_ADD2_Pos		((reg_bit_pos_t) 1U)
/** @brief Width of the `I2C_OAR2_ADD2` field @def I2C_OAR2_ADD2_Width */
#define I2C_OAR2_ADD2_Width		((reg_field_width_t) 7U)
/** @brief Register-positioned mask for the `I2C_OAR2_ADD2` field @def I2C_OAR2_ADD2_Msk */
#define I2C_OAR2_ADD2_Msk		REG_FIELD_MASK(I2C_OAR2_ADD2_Pos, I2C_OAR2_ADD2_Width)
/** @brief Interface address @def I2C_OAR2_ADD2 */
#define I2C_OAR2_ADD2			I2C_OAR2_ADD2_Msk

// ----------------------------------- I2C_DR Register Bit Defines ------------------------------------ //
/** @brief Bit position of the `I2C_DR_DR` field @def I2C_DR_DR_Pos */
#define I2C_DR_DR_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `I2C_DR_DR` field @def I2C_DR_DR_Width */
#define I2C_DR_DR_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `I2C_DR_DR` field @def I2C_DR_DR_Msk */
#define I2C_DR_DR_Msk		REG_FIELD_MASK(I2C_DR_DR_Pos, I2C_DR_DR_Width)
/** @brief 8-bit Data Register @def I2C_DR_DR */
#define I2C_DR_DR			I2C_DR_DR_Msk

// ----------------------------------- I2C_SR1 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `I2C_SR1_SB` field @def I2C_SR1_SB_Pos */
#define I2C_SR1_SB_Pos				((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `I2C_SR1_SB` field @def I2C_SR1_SB_Msk */
#define I2C_SR1_SB_Msk				REG_BIT_MASK(I2C_SR1_SB_Pos)
/** @brief Start Bit (Master mode) @def I2C_SR1_SB */
#define I2C_SR1_SB					I2C_SR1_SB_Msk
/** @brief Bit position of the `I2C_SR1_ADDR` field @def I2C_SR1_ADDR_Pos */
#define I2C_SR1_ADDR_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `I2C_SR1_ADDR` field @def I2C_SR1_ADDR_Msk */
#define I2C_SR1_ADDR_Msk			REG_BIT_MASK(I2C_SR1_ADDR_Pos)
/** @brief Address sent (master mode)/matched (slave mode) @def I2C_SR1_ADDR */
#define I2C_SR1_ADDR				I2C_SR1_ADDR_Msk
/** @brief Bit position of the `I2C_SR1_BTF` field @def I2C_SR1_BTF_Pos */
#define I2C_SR1_BTF_Pos				((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `I2C_SR1_BTF` field @def I2C_SR1_BTF_Msk */
#define I2C_SR1_BTF_Msk				REG_BIT_MASK(I2C_SR1_BTF_Pos)
/** @brief Byte Transfer Finished @def I2C_SR1_BTF */
#define I2C_SR1_BTF					I2C_SR1_BTF_Msk
/** @brief Bit position of the `I2C_SR1_ADD10` field @def I2C_SR1_ADD10_Pos */
#define I2C_SR1_ADD10_Pos			((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `I2C_SR1_ADD10` field @def I2C_SR1_ADD10_Msk */
#define I2C_SR1_ADD10_Msk			REG_BIT_MASK(I2C_SR1_ADD10_Pos)
/** @brief 10-bit header sent (Master mode) @def I2C_SR1_ADD10 */
#define I2C_SR1_ADD10				I2C_SR1_ADD10_Msk
/** @brief Bit position of the `I2C_SR1_STOPF` field @def I2C_SR1_STOPF_Pos */
#define I2C_SR1_STOPF_Pos			((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `I2C_SR1_STOPF` field @def I2C_SR1_STOPF_Msk */
#define I2C_SR1_STOPF_Msk			REG_BIT_MASK(I2C_SR1_STOPF_Pos)
/** @brief Stop detection (Slave mode) @def I2C_SR1_STOPF */
#define I2C_SR1_STOPF				I2C_SR1_STOPF_Msk
/** @brief Bit position of the `I2C_SR1_RXNE` field @def I2C_SR1_RXNE_Pos */
#define I2C_SR1_RXNE_Pos			((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `I2C_SR1_RXNE` field @def I2C_SR1_RXNE_Msk */
#define I2C_SR1_RXNE_Msk			REG_BIT_MASK(I2C_SR1_RXNE_Pos)
/** @brief Data Register not Empty (receivers) @def I2C_SR1_RXNE */
#define I2C_SR1_RXNE				I2C_SR1_RXNE_Msk
/** @brief Bit position of the `I2C_SR1_TXE` field @def I2C_SR1_TXE_Pos */
#define I2C_SR1_TXE_Pos				((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `I2C_SR1_TXE` field @def I2C_SR1_TXE_Msk */
#define I2C_SR1_TXE_Msk				REG_BIT_MASK(I2C_SR1_TXE_Pos)
/** @brief Data Register Empty (transmitters) @def I2C_SR1_TXE */
#define I2C_SR1_TXE					I2C_SR1_TXE_Msk
/** @brief Bit position of the `I2C_SR1_BERR` field @def I2C_SR1_BERR_Pos */
#define I2C_SR1_BERR_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `I2C_SR1_BERR` field @def I2C_SR1_BERR_Msk */
#define I2C_SR1_BERR_Msk			REG_BIT_MASK(I2C_SR1_BERR_Pos)
/** @brief Bus Error @def I2C_SR1_BERR */
#define I2C_SR1_BERR				I2C_SR1_BERR_Msk
/** @brief Bit position of the `I2C_SR1_ARLO` field @def I2C_SR1_ARLO_Pos */
#define I2C_SR1_ARLO_Pos			((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `I2C_SR1_ARLO` field @def I2C_SR1_ARLO_Msk */
#define I2C_SR1_ARLO_Msk			REG_BIT_MASK(I2C_SR1_ARLO_Pos)
/** @brief Arbitration Lost (master mode) @def I2C_SR1_ARLO */
#define I2C_SR1_ARLO				I2C_SR1_ARLO_Msk
/** @brief Bit position of the `I2C_SR1_AF` field @def I2C_SR1_AF_Pos */
#define I2C_SR1_AF_Pos				((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `I2C_SR1_AF` field @def I2C_SR1_AF_Msk */
#define I2C_SR1_AF_Msk				REG_BIT_MASK(I2C_SR1_AF_Pos)
/** @brief Acknowledge Failure @def I2C_SR1_AF */
#define I2C_SR1_AF					I2C_SR1_AF_Msk
/** @brief Bit position of the `I2C_SR1_OVR` field @def I2C_SR1_OVR_Pos */
#define I2C_SR1_OVR_Pos				((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `I2C_SR1_OVR` field @def I2C_SR1_OVR_Msk */
#define I2C_SR1_OVR_Msk				REG_BIT_MASK(I2C_SR1_OVR_Pos)
/** @brief Overrun/Underrun @def I2C_SR1_OVR */
#define I2C_SR1_OVR					I2C_SR1_OVR_Msk
/** @brief Bit position of the `I2C_SR1_PECERR` field @def I2C_SR1_PECERR_Pos */
#define I2C_SR1_PECERR_Pos			((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `I2C_SR1_PECERR` field @def I2C_SR1_PECERR_Msk */
#define I2C_SR1_PECERR_Msk			REG_BIT_MASK(I2C_SR1_PECERR_Pos)
/** @brief PEC Error in reception @def I2C_SR1_PECERR */
#define I2C_SR1_PECERR				I2C_SR1_PECERR_Msk
/** @brief Bit position of the `I2C_SR1_TIMEOUT` field @def I2C_SR1_TIMEOUT_Pos */
#define I2C_SR1_TIMEOUT_Pos			((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `I2C_SR1_TIMEOUT` field @def I2C_SR1_TIMEOUT_Msk */
#define I2C_SR1_TIMEOUT_Msk			REG_BIT_MASK(I2C_SR1_TIMEOUT_Pos)
/** @brief Timeout or Tlow Error @def I2C_SR1_TIMEOUT */
#define I2C_SR1_TIMEOUT				I2C_SR1_TIMEOUT_Msk
/** @brief Bit position of the `I2C_SR1_SMBALERT` field @def I2C_SR1_SMBALERT_Pos */
#define I2C_SR1_SMBALERT_Pos		((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `I2C_SR1_SMBALERT` field @def I2C_SR1_SMBALERT_Msk */
#define I2C_SR1_SMBALERT_Msk		REG_BIT_MASK(I2C_SR1_SMBALERT_Pos)
/** @brief SMBus Alert @def I2C_SR1_SMBALERT */
#define I2C_SR1_SMBALERT			I2C_SR1_SMBALERT_Msk

// ----------------------------------- I2C_SR2 Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `I2C_SR2_MSL` field @def I2C_SR2_MSL_Pos */
#define I2C_SR2_MSL_Pos				((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `I2C_SR2_MSL` field @def I2C_SR2_MSL_Msk */
#define I2C_SR2_MSL_Msk				REG_BIT_MASK(I2C_SR2_MSL_Pos)
/** @brief Master/Slave @def I2C_SR2_MSL */
#define I2C_SR2_MSL					I2C_SR2_MSL_Msk
/** @brief Bit position of the `I2C_SR2_BUSY` field @def I2C_SR2_BUSY_Pos */
#define I2C_SR2_BUSY_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `I2C_SR2_BUSY` field @def I2C_SR2_BUSY_Msk */
#define I2C_SR2_BUSY_Msk			REG_BIT_MASK(I2C_SR2_BUSY_Pos)
/** @brief Bus Busy @def I2C_SR2_BUSY */
#define I2C_SR2_BUSY				I2C_SR2_BUSY_Msk
/** @brief Bit position of the `I2C_SR2_TRA` field @def I2C_SR2_TRA_Pos */
#define I2C_SR2_TRA_Pos				((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `I2C_SR2_TRA` field @def I2C_SR2_TRA_Msk */
#define I2C_SR2_TRA_Msk				REG_BIT_MASK(I2C_SR2_TRA_Pos)
/** @brief Transmitter/Receiver @def I2C_SR2_TRA */
#define I2C_SR2_TRA					I2C_SR2_TRA_Msk
/** @brief Bit position of the `I2C_SR2_GENCALL` field @def I2C_SR2_GENCALL_Pos */
#define I2C_SR2_GENCALL_Pos			((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `I2C_SR2_GENCALL` field @def I2C_SR2_GENCALL_Msk */
#define I2C_SR2_GENCALL_Msk			REG_BIT_MASK(I2C_SR2_GENCALL_Pos)
/** @brief General Call Address (Slave mode) @def I2C_SR2_GENCALL */
#define I2C_SR2_GENCALL				I2C_SR2_GENCALL_Msk
/** @brief Bit position of the `I2C_SR2_SMBDEFAULT` field @def I2C_SR2_SMBDEFAULT_Pos */
#define I2C_SR2_SMBDEFAULT_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `I2C_SR2_SMBDEFAULT` field @def I2C_SR2_SMBDEFAULT_Msk */
#define I2C_SR2_SMBDEFAULT_Msk		REG_BIT_MASK(I2C_SR2_SMBDEFAULT_Pos)
/** @brief SMBus Device Default Address (Slave mode) @def I2C_SR2_SMBDEFAULT */
#define I2C_SR2_SMBDEFAULT			I2C_SR2_SMBDEFAULT_Msk
/** @brief Bit position of the `I2C_SR2_SMBHOST` field @def I2C_SR2_SMBHOST_Pos */
#define I2C_SR2_SMBHOST_Pos			((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `I2C_SR2_SMBHOST` field @def I2C_SR2_SMBHOST_Msk */
#define I2C_SR2_SMBHOST_Msk			REG_BIT_MASK(I2C_SR2_SMBHOST_Pos)
/** @brief SMBus Host Header (Slave mode) @def I2C_SR2_SMBHOST */
#define I2C_SR2_SMBHOST				I2C_SR2_SMBHOST_Msk
/** @brief Bit position of the `I2C_SR2_DUALF` field @def I2C_SR2_DUALF_Pos */
#define I2C_SR2_DUALF_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `I2C_SR2_DUALF` field @def I2C_SR2_DUALF_Msk */
#define I2C_SR2_DUALF_Msk			REG_BIT_MASK(I2C_SR2_DUALF_Pos)
/** @brief Dual Flag (Slave mode) @def I2C_SR2_DUALF */
#define I2C_SR2_DUALF				I2C_SR2_DUALF_Msk
/** @brief Bit position of the `I2C_SR2_PEC` field @def I2C_SR2_PEC_Pos */
#define I2C_SR2_PEC_Pos				((reg_bit_pos_t) 8U)
/** @brief Width of the `I2C_SR2_PEC` field @def I2C_SR2_PEC_Width */
#define I2C_SR2_PEC_Width			((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `I2C_SR2_PEC` field @def I2C_SR2_PEC_Msk */
#define I2C_SR2_PEC_Msk				REG_FIELD_MASK(I2C_SR2_PEC_Pos, I2C_SR2_PEC_Width)
/** @brief Packet Error Checking Register @def I2C_SR2_PEC */
#define I2C_SR2_PEC					I2C_SR2_PEC_Msk

// ----------------------------------- I2C_CCR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `I2C_CCR_CCR` field @def I2C_CCR_CCR_Pos */
#define I2C_CCR_CCR_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `I2C_CCR_CCR` field @def I2C_CCR_CCR_Width */
#define I2C_CCR_CCR_Width		((reg_field_width_t) 12U)
/** @brief Register-positioned mask for the `I2C_CCR_CCR` field @def I2C_CCR_CCR_Msk */
#define I2C_CCR_CCR_Msk			REG_FIELD_MASK(I2C_CCR_CCR_Pos, I2C_CCR_CCR_Width)
/** @brief Clock Control Register in Fast/Standard mode (Master mode) @def I2C_CCR_CCR */
#define I2C_CCR_CCR				I2C_CCR_CCR_Msk
/** @brief Bit position of the `I2C_CCR_DUTY` field @def I2C_CCR_DUTY_Pos */
#define I2C_CCR_DUTY_Pos		((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `I2C_CCR_DUTY` field @def I2C_CCR_DUTY_Msk */
#define I2C_CCR_DUTY_Msk		REG_BIT_MASK(I2C_CCR_DUTY_Pos)
/** @brief Fast Mode Duty Cycle @def I2C_CCR_DUTY */
#define I2C_CCR_DUTY			I2C_CCR_DUTY_Msk
/** @brief Bit position of the `I2C_CCR_FS` field @def I2C_CCR_FS_Pos */
#define I2C_CCR_FS_Pos			((reg_bit_pos_t) 15U)
/** @brief Register-positioned mask for the `I2C_CCR_FS` field @def I2C_CCR_FS_Msk */
#define I2C_CCR_FS_Msk			REG_BIT_MASK(I2C_CCR_FS_Pos)
/** @brief I2C Master Mode Selection @def I2C_CCR_FS */
#define I2C_CCR_FS				I2C_CCR_FS_Msk

// ---------------------------------- I2C_TRISE Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `I2C_TRISE_TRISE` field @def I2C_TRISE_TRISE_Pos */
#define I2C_TRISE_TRISE_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `I2C_TRISE_TRISE` field @def I2C_TRISE_TRISE_Width */
#define I2C_TRISE_TRISE_Width		((reg_field_width_t) 6U)
/** @brief Register-positioned mask for the `I2C_TRISE_TRISE` field @def I2C_TRISE_TRISE_Msk */
#define I2C_TRISE_TRISE_Msk			REG_FIELD_MASK(I2C_TRISE_TRISE_Pos, I2C_TRISE_TRISE_Width)
/** @brief Maximum Rise Time in Fast/Standard mode (Master mode) @def I2C_TRISE_TRISE */
#define I2C_TRISE_TRISE				I2C_TRISE_TRISE_Msk

// ==================================================================================================== //
//											USART Register Defines										//
// ==================================================================================================== //

// ---------------------------------- USART_SR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USART_SR_PE` field @def USART_SR_PE_Pos */
#define USART_SR_PE_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `USART_SR_PE` field @def USART_SR_PE_Msk */
#define USART_SR_PE_Msk			REG_BIT_MASK(USART_SR_PE_Pos)
/** @brief Parity Error @def USART_SR_PE */
#define USART_SR_PE				USART_SR_PE_Msk
/** @brief Bit position of the `USART_SR_FE` field @def USART_SR_FE_Pos */
#define USART_SR_FE_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `USART_SR_FE` field @def USART_SR_FE_Msk */
#define USART_SR_FE_Msk			REG_BIT_MASK(USART_SR_FE_Pos)
/** @brief Framing Error @def USART_SR_FE */
#define USART_SR_FE				USART_SR_FE_Msk
/** @brief Bit position of the `USART_SR_NE` field @def USART_SR_NE_Pos */
#define USART_SR_NE_Pos			((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `USART_SR_NE` field @def USART_SR_NE_Msk */
#define USART_SR_NE_Msk			REG_BIT_MASK(USART_SR_NE_Pos)
/** @brief Noise Error Flag @def USART_SR_NE */
#define USART_SR_NE				USART_SR_NE_Msk
/** @brief Bit position of the `USART_SR_ORE` field @def USART_SR_ORE_Pos */
#define USART_SR_ORE_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `USART_SR_ORE` field @def USART_SR_ORE_Msk */
#define USART_SR_ORE_Msk		REG_BIT_MASK(USART_SR_ORE_Pos)
/** @brief OverRun Error @def USART_SR_ORE */
#define USART_SR_ORE			USART_SR_ORE_Msk
/** @brief Bit position of the `USART_SR_IDLE` field @def USART_SR_IDLE_Pos */
#define USART_SR_IDLE_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `USART_SR_IDLE` field @def USART_SR_IDLE_Msk */
#define USART_SR_IDLE_Msk		REG_BIT_MASK(USART_SR_IDLE_Pos)
/** @brief IDLE line detected @def USART_SR_IDLE */
#define USART_SR_IDLE			USART_SR_IDLE_Msk
/** @brief Bit position of the `USART_SR_RXNE` field @def USART_SR_RXNE_Pos */
#define USART_SR_RXNE_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `USART_SR_RXNE` field @def USART_SR_RXNE_Msk */
#define USART_SR_RXNE_Msk		REG_BIT_MASK(USART_SR_RXNE_Pos)
/** @brief Read Data Register Not Empty @def USART_SR_RXNE */
#define USART_SR_RXNE			USART_SR_RXNE_Msk
/** @brief Bit position of the `USART_SR_TC` field @def USART_SR_TC_Pos */
#define USART_SR_TC_Pos			((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USART_SR_TC` field @def USART_SR_TC_Msk */
#define USART_SR_TC_Msk			REG_BIT_MASK(USART_SR_TC_Pos)
/** @brief Transmission Complete @def USART_SR_TC */
#define USART_SR_TC				USART_SR_TC_Msk
/** @brief Bit position of the `USART_SR_TXE` field @def USART_SR_TXE_Pos */
#define USART_SR_TXE_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USART_SR_TXE` field @def USART_SR_TXE_Msk */
#define USART_SR_TXE_Msk		REG_BIT_MASK(USART_SR_TXE_Pos)
/** @brief Transmit Data Register Empty @def USART_SR_TXE */
#define USART_SR_TXE			USART_SR_TXE_Msk
/** @brief Bit position of the `USART_SR_LBD` field @def USART_SR_LBD_Pos */
#define USART_SR_LBD_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USART_SR_LBD` field @def USART_SR_LBD_Msk */
#define USART_SR_LBD_Msk		REG_BIT_MASK(USART_SR_LBD_Pos)
/** @brief LIN Break Detection Flag @def USART_SR_LBD */
#define USART_SR_LBD			USART_SR_LBD_Msk
/** @brief Bit position of the `USART_SR_CTS` field @def USART_SR_CTS_Pos */
#define USART_SR_CTS_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `USART_SR_CTS` field @def USART_SR_CTS_Msk */
#define USART_SR_CTS_Msk		REG_BIT_MASK(USART_SR_CTS_Pos)
/** @brief CTS Flag @def USART_SR_CTS */
#define USART_SR_CTS			USART_SR_CTS_Msk

// ---------------------------------- USART_DR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `USART_DR_DR` field @def USART_DR_DR_Pos */
#define USART_DR_DR_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USART_DR_DR` field @def USART_DR_DR_Width */
#define USART_DR_DR_Width		((reg_field_width_t) 9U)
/** @brief Register-positioned mask for the `USART_DR_DR` field @def USART_DR_DR_Msk */
#define USART_DR_DR_Msk			REG_FIELD_MASK(USART_DR_DR_Pos, USART_DR_DR_Width)
/** @brief Data value @def USART_DR_DR */
#define USART_DR_DR				USART_DR_DR_Msk

// ---------------------------------- USART_BRR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `USART_BRR_DIV_Fraction` field @def USART_BRR_DIV_Fraction_Pos */
#define USART_BRR_DIV_Fraction_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USART_BRR_DIV_Fraction` field @def USART_BRR_DIV_Fraction_Width */
#define USART_BRR_DIV_Fraction_Width		((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `USART_BRR_DIV_Fraction` field @def USART_BRR_DIV_Fraction_Msk */
#define USART_BRR_DIV_Fraction_Msk			REG_FIELD_MASK(USART_BRR_DIV_Fraction_Pos, USART_BRR_DIV_Fraction_Width)
/** @brief Fraction of USARTDIV @def USART_BRR_DIV_Fraction */
#define USART_BRR_DIV_Fraction				USART_BRR_DIV_Fraction_Msk
/** @brief Bit position of the `USART_BRR_DIV_Mantissa` field @def USART_BRR_DIV_Mantissa_Pos */
#define USART_BRR_DIV_Mantissa_Pos			((reg_bit_pos_t) 4U)
/** @brief Width of the `USART_BRR_DIV_Mantissa` field @def USART_BRR_DIV_Mantissa_Width */
#define USART_BRR_DIV_Mantissa_Width		((reg_field_width_t) 12U)
/** @brief Register-positioned mask for the `USART_BRR_DIV_Mantissa` field @def USART_BRR_DIV_Mantissa_Msk */
#define USART_BRR_DIV_Mantissa_Msk			REG_FIELD_MASK(USART_BRR_DIV_Mantissa_Pos, USART_BRR_DIV_Mantissa_Width)
/** @brief Mantissa of USARTDIV @def USART_BRR_DIV_Mantissa */
#define USART_BRR_DIV_Mantissa				USART_BRR_DIV_Mantissa_Msk

// ---------------------------------- USART_CR1 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `USART_CR1_SBK` field @def USART_CR1_SBK_Pos */
#define USART_CR1_SBK_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `USART_CR1_SBK` field @def USART_CR1_SBK_Msk */
#define USART_CR1_SBK_Msk			REG_BIT_MASK(USART_CR1_SBK_Pos)
/** @brief Send Break @def USART_CR1_SBK */
#define USART_CR1_SBK				USART_CR1_SBK_Msk
/** @brief Bit position of the `USART_CR1_RWU` field @def USART_CR1_RWU_Pos */
#define USART_CR1_RWU_Pos			((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `USART_CR1_RWU` field @def USART_CR1_RWU_Msk */
#define USART_CR1_RWU_Msk			REG_BIT_MASK(USART_CR1_RWU_Pos)
/** @brief Receiver wakeup @def USART_CR1_RWU */
#define USART_CR1_RWU				USART_CR1_RWU_Msk
/** @brief Bit position of the `USART_CR1_RE` field @def USART_CR1_RE_Pos */
#define USART_CR1_RE_Pos			((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `USART_CR1_RE` field @def USART_CR1_RE_Msk */
#define USART_CR1_RE_Msk			REG_BIT_MASK(USART_CR1_RE_Pos)
/** @brief Receiver Enable @def USART_CR1_RE */
#define USART_CR1_RE				USART_CR1_RE_Msk
/** @brief Bit position of the `USART_CR1_TE` field @def USART_CR1_TE_Pos */
#define USART_CR1_TE_Pos			((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `USART_CR1_TE` field @def USART_CR1_TE_Msk */
#define USART_CR1_TE_Msk			REG_BIT_MASK(USART_CR1_TE_Pos)
/** @brief Transmitter Enable @def USART_CR1_TE */
#define USART_CR1_TE				USART_CR1_TE_Msk
/** @brief Bit position of the `USART_CR1_IDLEIE` field @def USART_CR1_IDLEIE_Pos */
#define USART_CR1_IDLEIE_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `USART_CR1_IDLEIE` field @def USART_CR1_IDLEIE_Msk */
#define USART_CR1_IDLEIE_Msk		REG_BIT_MASK(USART_CR1_IDLEIE_Pos)
/** @brief IDLE Interrupt Enable @def USART_CR1_IDLEIE */
#define USART_CR1_IDLEIE			USART_CR1_IDLEIE_Msk
/** @brief Bit position of the `USART_CR1_RXNEIE` field @def USART_CR1_RXNEIE_Pos */
#define USART_CR1_RXNEIE_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `USART_CR1_RXNEIE` field @def USART_CR1_RXNEIE_Msk */
#define USART_CR1_RXNEIE_Msk		REG_BIT_MASK(USART_CR1_RXNEIE_Pos)
/** @brief RXNE Interrupt Enable @def USART_CR1_RXNEIE */
#define USART_CR1_RXNEIE			USART_CR1_RXNEIE_Msk
/** @brief Bit position of the `USART_CR1_TCIE` field @def USART_CR1_TCIE_Pos */
#define USART_CR1_TCIE_Pos			((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USART_CR1_TCIE` field @def USART_CR1_TCIE_Msk */
#define USART_CR1_TCIE_Msk			REG_BIT_MASK(USART_CR1_TCIE_Pos)
/** @brief Transmission Complete Interrupt Enable @def USART_CR1_TCIE */
#define USART_CR1_TCIE				USART_CR1_TCIE_Msk
/** @brief Bit position of the `USART_CR1_TXEIE` field @def USART_CR1_TXEIE_Pos */
#define USART_CR1_TXEIE_Pos			((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USART_CR1_TXEIE` field @def USART_CR1_TXEIE_Msk */
#define USART_CR1_TXEIE_Msk			REG_BIT_MASK(USART_CR1_TXEIE_Pos)
/** @brief PE Interrupt Enable @def USART_CR1_TXEIE */
#define USART_CR1_TXEIE				USART_CR1_TXEIE_Msk
/** @brief Bit position of the `USART_CR1_PEIE` field @def USART_CR1_PEIE_Pos */
#define USART_CR1_PEIE_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USART_CR1_PEIE` field @def USART_CR1_PEIE_Msk */
#define USART_CR1_PEIE_Msk			REG_BIT_MASK(USART_CR1_PEIE_Pos)
/** @brief PE Interrupt Enable @def USART_CR1_PEIE */
#define USART_CR1_PEIE				USART_CR1_PEIE_Msk
/** @brief Bit position of the `USART_CR1_PS` field @def USART_CR1_PS_Pos */
#define USART_CR1_PS_Pos			((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `USART_CR1_PS` field @def USART_CR1_PS_Msk */
#define USART_CR1_PS_Msk			REG_BIT_MASK(USART_CR1_PS_Pos)
/** @brief Parity Selection @def USART_CR1_PS */
#define USART_CR1_PS				USART_CR1_PS_Msk
/** @brief Bit position of the `USART_CR1_PCE` field @def USART_CR1_PCE_Pos */
#define USART_CR1_PCE_Pos			((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `USART_CR1_PCE` field @def USART_CR1_PCE_Msk */
#define USART_CR1_PCE_Msk			REG_BIT_MASK(USART_CR1_PCE_Pos)
/** @brief Parity Control Enable @def USART_CR1_PCE */
#define USART_CR1_PCE				USART_CR1_PCE_Msk
/** @brief Bit position of the `USART_CR1_WAKE` field @def USART_CR1_WAKE_Pos */
#define USART_CR1_WAKE_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USART_CR1_WAKE` field @def USART_CR1_WAKE_Msk */
#define USART_CR1_WAKE_Msk			REG_BIT_MASK(USART_CR1_WAKE_Pos)
/** @brief Wakeup method @def USART_CR1_WAKE */
#define USART_CR1_WAKE				USART_CR1_WAKE_Msk
/** @brief Bit position of the `USART_CR1_M` field @def USART_CR1_M_Pos */
#define USART_CR1_M_Pos				((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `USART_CR1_M` field @def USART_CR1_M_Msk */
#define USART_CR1_M_Msk				REG_BIT_MASK(USART_CR1_M_Pos)
/** @brief Word length @def USART_CR1_M */
#define USART_CR1_M					USART_CR1_M_Msk
/** @brief Bit position of the `USART_CR1_UE` field @def USART_CR1_UE_Pos */
#define USART_CR1_UE_Pos			((reg_bit_pos_t) 13U)
/** @brief Register-positioned mask for the `USART_CR1_UE` field @def USART_CR1_UE_Msk */
#define USART_CR1_UE_Msk			REG_BIT_MASK(USART_CR1_UE_Pos)
/** @brief USART Enable @def USART_CR1_UE */
#define USART_CR1_UE				USART_CR1_UE_Msk

// ---------------------------------- USART_CR2 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `USART_CR2_ADD` field @def USART_CR2_ADD_Pos */
#define USART_CR2_ADD_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USART_CR2_ADD` field @def USART_CR2_ADD_Width */
#define USART_CR2_ADD_Width			((reg_field_width_t) 4U)
/** @brief Register-positioned mask for the `USART_CR2_ADD` field @def USART_CR2_ADD_Msk */
#define USART_CR2_ADD_Msk			REG_FIELD_MASK(USART_CR2_ADD_Pos, USART_CR2_ADD_Width)
/** @brief Address of the USART node @def USART_CR2_ADD */
#define USART_CR2_ADD				USART_CR2_ADD_Msk
/** @brief Bit position of the `USART_CR2_LBDL` field @def USART_CR2_LBDL_Pos */
#define USART_CR2_LBDL_Pos			((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `USART_CR2_LBDL` field @def USART_CR2_LBDL_Msk */
#define USART_CR2_LBDL_Msk			REG_BIT_MASK(USART_CR2_LBDL_Pos)
/** @brief LIN Break Detection Length @def USART_CR2_LBDL */
#define USART_CR2_LBDL				USART_CR2_LBDL_Msk
/** @brief Bit position of the `USART_CR2_LBDIE` field @def USART_CR2_LBDIE_Pos */
#define USART_CR2_LBDIE_Pos			((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USART_CR2_LBDIE` field @def USART_CR2_LBDIE_Msk */
#define USART_CR2_LBDIE_Msk			REG_BIT_MASK(USART_CR2_LBDIE_Pos)
/** @brief LIN Break Detection Interrupt Enable @def USART_CR2_LBDIE */
#define USART_CR2_LBDIE				USART_CR2_LBDIE_Msk
/** @brief Bit position of the `USART_CR2_LBCL` field @def USART_CR2_LBCL_Pos */
#define USART_CR2_LBCL_Pos			((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USART_CR2_LBCL` field @def USART_CR2_LBCL_Msk */
#define USART_CR2_LBCL_Msk			REG_BIT_MASK(USART_CR2_LBCL_Pos)
/** @brief Last Bit Clock pulse @def USART_CR2_LBCL */
#define USART_CR2_LBCL				USART_CR2_LBCL_Msk
/** @brief Bit position of the `USART_CR2_CPHA` field @def USART_CR2_CPHA_Pos */
#define USART_CR2_CPHA_Pos			((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `USART_CR2_CPHA` field @def USART_CR2_CPHA_Msk */
#define USART_CR2_CPHA_Msk			REG_BIT_MASK(USART_CR2_CPHA_Pos)
/** @brief Clock Phase @def USART_CR2_CPHA */
#define USART_CR2_CPHA				USART_CR2_CPHA_Msk
/** @brief Bit position of the `USART_CR2_CPOL` field @def USART_CR2_CPOL_Pos */
#define USART_CR2_CPOL_Pos			((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `USART_CR2_CPOL` field @def USART_CR2_CPOL_Msk */
#define USART_CR2_CPOL_Msk			REG_BIT_MASK(USART_CR2_CPOL_Pos)
/** @brief Clock Polarity @def USART_CR2_CPOL */
#define USART_CR2_CPOL				USART_CR2_CPOL_Msk
/** @brief Bit position of the `USART_CR2_CLKEN` field @def USART_CR2_CLKEN_Pos */
#define USART_CR2_CLKEN_Pos			((reg_bit_pos_t) 11U)
/** @brief Register-positioned mask for the `USART_CR2_CLKEN` field @def USART_CR2_CLKEN_Msk */
#define USART_CR2_CLKEN_Msk			REG_BIT_MASK(USART_CR2_CLKEN_Pos)
/** @brief Clock Enable @def USART_CR2_CLKEN */
#define USART_CR2_CLKEN				USART_CR2_CLKEN_Msk

/** @brief Bit position of the `USART_CR2_STOP` field @def USART_CR2_STOP_Pos */
#define USART_CR2_STOP_Pos			((reg_bit_pos_t) 12U)
/** @brief Width of the `USART_CR2_STOP` field @def USART_CR2_STOP_Width */
#define USART_CR2_STOP_Width		((reg_field_width_t) 2U)
/** @brief Register-positioned mask for the `USART_CR2_STOP` field @def USART_CR2_STOP_Msk */
#define USART_CR2_STOP_Msk			REG_FIELD_MASK(USART_CR2_STOP_Pos, USART_CR2_STOP_Width)
/** @brief STOP[1:0] bits (STOP bits) @def USART_CR2_STOP */
#define USART_CR2_STOP				USART_CR2_STOP_Msk
/** @brief Register or selector value represented by `USART_CR2_STOP_0` @def USART_CR2_STOP_0 */
#define USART_CR2_STOP_0			(0x1UL << USART_CR2_STOP_Pos)
/** @brief Register or selector value represented by `USART_CR2_STOP_1` @def USART_CR2_STOP_1 */
#define USART_CR2_STOP_1			(0x2UL << USART_CR2_STOP_Pos)

/** @brief Bit position of the `USART_CR2_LINEN` field @def USART_CR2_LINEN_Pos */
#define USART_CR2_LINEN_Pos			((reg_bit_pos_t) 14U)
/** @brief Register-positioned mask for the `USART_CR2_LINEN` field @def USART_CR2_LINEN_Msk */
#define USART_CR2_LINEN_Msk			REG_BIT_MASK(USART_CR2_LINEN_Pos)
/** @brief LIN mode enable @def USART_CR2_LINEN */
#define USART_CR2_LINEN				USART_CR2_LINEN_Msk

// ---------------------------------- USART_CR3 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `USART_CR3_EIE` field @def USART_CR3_EIE_Pos */
#define USART_CR3_EIE_Pos		((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `USART_CR3_EIE` field @def USART_CR3_EIE_Msk */
#define USART_CR3_EIE_Msk		REG_BIT_MASK(USART_CR3_EIE_Pos)
/** @brief Error Interrupt Enable @def USART_CR3_EIE */
#define USART_CR3_EIE			USART_CR3_EIE_Msk
/** @brief Bit position of the `USART_CR3_IREN` field @def USART_CR3_IREN_Pos */
#define USART_CR3_IREN_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `USART_CR3_IREN` field @def USART_CR3_IREN_Msk */
#define USART_CR3_IREN_Msk		REG_BIT_MASK(USART_CR3_IREN_Pos)
/** @brief IrDA mode Enable @def USART_CR3_IREN */
#define USART_CR3_IREN			USART_CR3_IREN_Msk
/** @brief Bit position of the `USART_CR3_IRLP` field @def USART_CR3_IRLP_Pos */
#define USART_CR3_IRLP_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `USART_CR3_IRLP` field @def USART_CR3_IRLP_Msk */
#define USART_CR3_IRLP_Msk		REG_BIT_MASK(USART_CR3_IRLP_Pos)
/** @brief IrDA Low-Power @def USART_CR3_IRLP */
#define USART_CR3_IRLP			USART_CR3_IRLP_Msk
/** @brief Bit position of the `USART_CR3_HDSEL` field @def USART_CR3_HDSEL_Pos */
#define USART_CR3_HDSEL_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `USART_CR3_HDSEL` field @def USART_CR3_HDSEL_Msk */
#define USART_CR3_HDSEL_Msk		REG_BIT_MASK(USART_CR3_HDSEL_Pos)
/** @brief Half-Duplex Selection @def USART_CR3_HDSEL */
#define USART_CR3_HDSEL			USART_CR3_HDSEL_Msk
/** @brief Bit position of the `USART_CR3_NACK` field @def USART_CR3_NACK_Pos */
#define USART_CR3_NACK_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `USART_CR3_NACK` field @def USART_CR3_NACK_Msk */
#define USART_CR3_NACK_Msk		REG_BIT_MASK(USART_CR3_NACK_Pos)
/** @brief Smartcard NACK enable @def USART_CR3_NACK */
#define USART_CR3_NACK			USART_CR3_NACK_Msk
/** @brief Bit position of the `USART_CR3_SCEN` field @def USART_CR3_SCEN_Pos */
#define USART_CR3_SCEN_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `USART_CR3_SCEN` field @def USART_CR3_SCEN_Msk */
#define USART_CR3_SCEN_Msk		REG_BIT_MASK(USART_CR3_SCEN_Pos)
/** @brief Smartcard mode enable @def USART_CR3_SCEN */
#define USART_CR3_SCEN			USART_CR3_SCEN_Msk
/** @brief Bit position of the `USART_CR3_DMAR` field @def USART_CR3_DMAR_Pos */
#define USART_CR3_DMAR_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `USART_CR3_DMAR` field @def USART_CR3_DMAR_Msk */
#define USART_CR3_DMAR_Msk		REG_BIT_MASK(USART_CR3_DMAR_Pos)
/** @brief DMA Enable Receiver @def USART_CR3_DMAR */
#define USART_CR3_DMAR			USART_CR3_DMAR_Msk
/** @brief Bit position of the `USART_CR3_DMAT` field @def USART_CR3_DMAT_Pos */
#define USART_CR3_DMAT_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `USART_CR3_DMAT` field @def USART_CR3_DMAT_Msk */
#define USART_CR3_DMAT_Msk		REG_BIT_MASK(USART_CR3_DMAT_Pos)
/** @brief DMA Enable Transmitter @def USART_CR3_DMAT */
#define USART_CR3_DMAT			USART_CR3_DMAT_Msk
/** @brief Bit position of the `USART_CR3_RTSE` field @def USART_CR3_RTSE_Pos */
#define USART_CR3_RTSE_Pos		((reg_bit_pos_t) 8U)
/** @brief Register-positioned mask for the `USART_CR3_RTSE` field @def USART_CR3_RTSE_Msk */
#define USART_CR3_RTSE_Msk		REG_BIT_MASK(USART_CR3_RTSE_Pos)
/** @brief RTS Enable @def USART_CR3_RTSE */
#define USART_CR3_RTSE			USART_CR3_RTSE_Msk
/** @brief Bit position of the `USART_CR3_CTSE` field @def USART_CR3_CTSE_Pos */
#define USART_CR3_CTSE_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `USART_CR3_CTSE` field @def USART_CR3_CTSE_Msk */
#define USART_CR3_CTSE_Msk		REG_BIT_MASK(USART_CR3_CTSE_Pos)
/** @brief CTS Enable @def USART_CR3_CTSE */
#define USART_CR3_CTSE			USART_CR3_CTSE_Msk
/** @brief Bit position of the `USART_CR3_CTSIE` field @def USART_CR3_CTSIE_Pos */
#define USART_CR3_CTSIE_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `USART_CR3_CTSIE` field @def USART_CR3_CTSIE_Msk */
#define USART_CR3_CTSIE_Msk		REG_BIT_MASK(USART_CR3_CTSIE_Pos)
/** @brief CTS Interrupt Enable @def USART_CR3_CTSIE */
#define USART_CR3_CTSIE			USART_CR3_CTSIE_Msk

// --------------------------------- USART_GTPR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `USART_GTPR_PSC` field @def USART_GTPR_PSC_Pos */
#define USART_GTPR_PSC_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `USART_GTPR_PSC` field @def USART_GTPR_PSC_Width */
#define USART_GTPR_PSC_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `USART_GTPR_PSC` field @def USART_GTPR_PSC_Msk */
#define USART_GTPR_PSC_Msk			REG_FIELD_MASK(USART_GTPR_PSC_Pos, USART_GTPR_PSC_Width)
/** @brief PSC[7:0] bits (Prescaler value) @def USART_GTPR_PSC */
#define USART_GTPR_PSC				USART_GTPR_PSC_Msk
/** @brief Register or selector value represented by `USART_GTPR_PSC_0` @def USART_GTPR_PSC_0 */
#define USART_GTPR_PSC_0			(0x01UL << USART_GTPR_PSC_Pos)
/** @brief Register or selector value represented by `USART_GTPR_PSC_1` @def USART_GTPR_PSC_1 */
#define USART_GTPR_PSC_1			(0x02UL << USART_GTPR_PSC_Pos)
/** @brief Register or selector value represented by `USART_GTPR_PSC_2` @def USART_GTPR_PSC_2 */
#define USART_GTPR_PSC_2			(0x04UL << USART_GTPR_PSC_Pos)
/** @brief Register or selector value represented by `USART_GTPR_PSC_3` @def USART_GTPR_PSC_3 */
#define USART_GTPR_PSC_3			(0x08UL << USART_GTPR_PSC_Pos)
/** @brief Register or selector value represented by `USART_GTPR_PSC_4` @def USART_GTPR_PSC_4 */
#define USART_GTPR_PSC_4			(0x10UL << USART_GTPR_PSC_Pos)
/** @brief Register or selector value represented by `USART_GTPR_PSC_5` @def USART_GTPR_PSC_5 */
#define USART_GTPR_PSC_5			(0x20UL << USART_GTPR_PSC_Pos)
/** @brief Register or selector value represented by `USART_GTPR_PSC_6` @def USART_GTPR_PSC_6 */
#define USART_GTPR_PSC_6			(0x40UL << USART_GTPR_PSC_Pos)
/** @brief Register or selector value represented by `USART_GTPR_PSC_7` @def USART_GTPR_PSC_7 */
#define USART_GTPR_PSC_7			(0x80UL << USART_GTPR_PSC_Pos)

/** @brief Bit position of the `USART_GTPR_GT` field @def USART_GTPR_GT_Pos */
#define USART_GTPR_GT_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `USART_GTPR_GT` field @def USART_GTPR_GT_Width */
#define USART_GTPR_GT_Width			((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `USART_GTPR_GT` field @def USART_GTPR_GT_Msk */
#define USART_GTPR_GT_Msk			REG_FIELD_MASK(USART_GTPR_GT_Pos, USART_GTPR_GT_Width)
/** @brief Guard time value @def USART_GTPR_GT */
#define USART_GTPR_GT				USART_GTPR_GT_Msk

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

// ==================================================================================================== //
//									Flash and Option-Byte Register Defines								//
// ==================================================================================================== //

// ---------------------------------- FLASH_ACR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `FLASH_ACR_LATENCY` field @def FLASH_ACR_LATENCY_Pos */
#define FLASH_ACR_LATENCY_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `FLASH_ACR_LATENCY` field @def FLASH_ACR_LATENCY_Width */
#define FLASH_ACR_LATENCY_Width		((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `FLASH_ACR_LATENCY` field @def FLASH_ACR_LATENCY_Msk */
#define FLASH_ACR_LATENCY_Msk		REG_FIELD_MASK(FLASH_ACR_LATENCY_Pos, FLASH_ACR_LATENCY_Width)
/** @brief LATENCY[2:0] bits (Latency) @def FLASH_ACR_LATENCY */
#define FLASH_ACR_LATENCY			FLASH_ACR_LATENCY_Msk
/** @brief Register or selector value represented by `FLASH_ACR_LATENCY_0` @def FLASH_ACR_LATENCY_0 */
#define FLASH_ACR_LATENCY_0			(0x0UL << FLASH_ACR_LATENCY_Pos)
/** @brief Register or selector value represented by `FLASH_ACR_LATENCY_1` @def FLASH_ACR_LATENCY_1 */
#define FLASH_ACR_LATENCY_1			(0x1UL << FLASH_ACR_LATENCY_Pos)
/** @brief Register or selector value represented by `FLASH_ACR_LATENCY_2` @def FLASH_ACR_LATENCY_2 */
#define FLASH_ACR_LATENCY_2			(0x2UL << FLASH_ACR_LATENCY_Pos)

/** @brief Bit position of the `FLASH_ACR_HLFCYA` field @def FLASH_ACR_HLFCYA_Pos */
#define FLASH_ACR_HLFCYA_Pos		((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `FLASH_ACR_HLFCYA` field @def FLASH_ACR_HLFCYA_Msk */
#define FLASH_ACR_HLFCYA_Msk		REG_BIT_MASK(FLASH_ACR_HLFCYA_Pos)
/** @brief Flash Half Cycle Access Enable @def FLASH_ACR_HLFCYA */
#define FLASH_ACR_HLFCYA			FLASH_ACR_HLFCYA_Msk
/** @brief Bit position of the `FLASH_ACR_PRFTBE` field @def FLASH_ACR_PRFTBE_Pos */
#define FLASH_ACR_PRFTBE_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `FLASH_ACR_PRFTBE` field @def FLASH_ACR_PRFTBE_Msk */
#define FLASH_ACR_PRFTBE_Msk		REG_BIT_MASK(FLASH_ACR_PRFTBE_Pos)
/** @brief Prefetch Buffer Enable @def FLASH_ACR_PRFTBE */
#define FLASH_ACR_PRFTBE			FLASH_ACR_PRFTBE_Msk
/** @brief Bit position of the `FLASH_ACR_PRFTBS` field @def FLASH_ACR_PRFTBS_Pos */
#define FLASH_ACR_PRFTBS_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `FLASH_ACR_PRFTBS` field @def FLASH_ACR_PRFTBS_Msk */
#define FLASH_ACR_PRFTBS_Msk		REG_BIT_MASK(FLASH_ACR_PRFTBS_Pos)
/** @brief Prefetch Buffer Status @def FLASH_ACR_PRFTBS */
#define FLASH_ACR_PRFTBS			FLASH_ACR_PRFTBS_Msk

// --------------------------------- FLASH_KEYR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `FLASH_KEYR_FKEYR` field @def FLASH_KEYR_FKEYR_Pos */
#define FLASH_KEYR_FKEYR_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `FLASH_KEYR_FKEYR` field @def FLASH_KEYR_FKEYR_Width */
#define FLASH_KEYR_FKEYR_Width		((reg_field_width_t) 32U)
/** @brief Register-positioned mask for the `FLASH_KEYR_FKEYR` field @def FLASH_KEYR_FKEYR_Msk */
#define FLASH_KEYR_FKEYR_Msk		((reg) 0xFFFFFFFFUL)
/** @brief FPEC Key @def FLASH_KEYR_FKEYR */
#define FLASH_KEYR_FKEYR			FLASH_KEYR_FKEYR_Msk

/** @brief Bit position of the `RDP_KEY` field @def RDP_KEY_Pos */
#define RDP_KEY_Pos					((reg_bit_pos_t) 0U)
/** @brief Legacy register-positioned RDP key value @def RDP_KEY_Msk */
#define RDP_KEY_Msk					(0xA5UL << RDP_KEY_Pos)
/** @brief RDP Key @def RDP_KEY */
#define RDP_KEY						RDP_KEY_Msk
/** @brief Bit position of the `FLASH_KEY1` field @def FLASH_KEY1_Pos */
#define FLASH_KEY1_Pos				((reg_bit_pos_t) 0U)
/** @brief Legacy register-positioned first Flash key value @def FLASH_KEY1_Msk */
#define FLASH_KEY1_Msk				(0x45670123UL << FLASH_KEY1_Pos)
/** @brief FPEC Key1 @def FLASH_KEY1 */
#define FLASH_KEY1					FLASH_KEY1_Msk
/** @brief Bit position of the `FLASH_KEY2` field @def FLASH_KEY2_Pos */
#define FLASH_KEY2_Pos				((reg_bit_pos_t) 0U)
/** @brief Legacy register-positioned second Flash key value @def FLASH_KEY2_Msk */
#define FLASH_KEY2_Msk				(0xCDEF89ABUL << FLASH_KEY2_Pos)
/** @brief FPEC Key2 @def FLASH_KEY2 */
#define FLASH_KEY2					FLASH_KEY2_Msk

// -------------------------------- FLASH_OPTKEYR Register Bit Defines -------------------------------- //
/** @brief Bit position of the `FLASH_OPTKEYR_OPTKEYR` field @def FLASH_OPTKEYR_OPTKEYR_Pos */
#define FLASH_OPTKEYR_OPTKEYR_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `FLASH_OPTKEYR_OPTKEYR` field @def FLASH_OPTKEYR_OPTKEYR_Width */
#define FLASH_OPTKEYR_OPTKEYR_Width		((reg_field_width_t) 32U)
/** @brief Register-positioned mask for the `FLASH_OPTKEYR_OPTKEYR` field @def FLASH_OPTKEYR_OPTKEYR_Msk */
#define FLASH_OPTKEYR_OPTKEYR_Msk		((reg) 0xFFFFFFFFUL)
/** @brief Option Byte Key @def FLASH_OPTKEYR_OPTKEYR */
#define FLASH_OPTKEYR_OPTKEYR			FLASH_OPTKEYR_OPTKEYR_Msk

/** @brief Option Byte Key1 @def FLASH_OPTKEY1 */
#define FLASH_OPTKEY1					FLASH_KEY1
/** @brief Option Byte Key2 @def FLASH_OPTKEY2 */
#define FLASH_OPTKEY2					FLASH_KEY2

// ---------------------------------- FLASH_SR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `FLASH_SR_BSY` field @def FLASH_SR_BSY_Pos */
#define FLASH_SR_BSY_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `FLASH_SR_BSY` field @def FLASH_SR_BSY_Msk */
#define FLASH_SR_BSY_Msk			REG_BIT_MASK(FLASH_SR_BSY_Pos)
/** @brief Busy @def FLASH_SR_BSY */
#define FLASH_SR_BSY				FLASH_SR_BSY_Msk
/** @brief Bit position of the `FLASH_SR_PGERR` field @def FLASH_SR_PGERR_Pos */
#define FLASH_SR_PGERR_Pos			((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `FLASH_SR_PGERR` field @def FLASH_SR_PGERR_Msk */
#define FLASH_SR_PGERR_Msk			REG_BIT_MASK(FLASH_SR_PGERR_Pos)
/** @brief Programming Error @def FLASH_SR_PGERR */
#define FLASH_SR_PGERR				FLASH_SR_PGERR_Msk
/** @brief Bit position of the `FLASH_SR_WRPRTERR` field @def FLASH_SR_WRPRTERR_Pos */
#define FLASH_SR_WRPRTERR_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `FLASH_SR_WRPRTERR` field @def FLASH_SR_WRPRTERR_Msk */
#define FLASH_SR_WRPRTERR_Msk		REG_BIT_MASK(FLASH_SR_WRPRTERR_Pos)
/** @brief Write Protection Error @def FLASH_SR_WRPRTERR */
#define FLASH_SR_WRPRTERR			FLASH_SR_WRPRTERR_Msk
/** @brief Bit position of the `FLASH_SR_EOP` field @def FLASH_SR_EOP_Pos */
#define FLASH_SR_EOP_Pos			((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `FLASH_SR_EOP` field @def FLASH_SR_EOP_Msk */
#define FLASH_SR_EOP_Msk			REG_BIT_MASK(FLASH_SR_EOP_Pos)
/** @brief End of operation @def FLASH_SR_EOP */
#define FLASH_SR_EOP				FLASH_SR_EOP_Msk

// ---------------------------------- FLASH_CR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `FLASH_CR_PG` field @def FLASH_CR_PG_Pos */
#define FLASH_CR_PG_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `FLASH_CR_PG` field @def FLASH_CR_PG_Msk */
#define FLASH_CR_PG_Msk			REG_BIT_MASK(FLASH_CR_PG_Pos)
/** @brief Programming @def FLASH_CR_PG */
#define FLASH_CR_PG				FLASH_CR_PG_Msk
/** @brief Bit position of the `FLASH_CR_PER` field @def FLASH_CR_PER_Pos */
#define FLASH_CR_PER_Pos		((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `FLASH_CR_PER` field @def FLASH_CR_PER_Msk */
#define FLASH_CR_PER_Msk		REG_BIT_MASK(FLASH_CR_PER_Pos)
/** @brief Page Erase @def FLASH_CR_PER */
#define FLASH_CR_PER			FLASH_CR_PER_Msk
/** @brief Bit position of the `FLASH_CR_MER` field @def FLASH_CR_MER_Pos */
#define FLASH_CR_MER_Pos		((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `FLASH_CR_MER` field @def FLASH_CR_MER_Msk */
#define FLASH_CR_MER_Msk		REG_BIT_MASK(FLASH_CR_MER_Pos)
/** @brief Mass Erase @def FLASH_CR_MER */
#define FLASH_CR_MER			FLASH_CR_MER_Msk
/** @brief Bit position of the `FLASH_CR_OPTPG` field @def FLASH_CR_OPTPG_Pos */
#define FLASH_CR_OPTPG_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `FLASH_CR_OPTPG` field @def FLASH_CR_OPTPG_Msk */
#define FLASH_CR_OPTPG_Msk		REG_BIT_MASK(FLASH_CR_OPTPG_Pos)
/** @brief Option Byte Programming @def FLASH_CR_OPTPG */
#define FLASH_CR_OPTPG			FLASH_CR_OPTPG_Msk
/** @brief Bit position of the `FLASH_CR_OPTER` field @def FLASH_CR_OPTER_Pos */
#define FLASH_CR_OPTER_Pos		((reg_bit_pos_t) 5U)
/** @brief Register-positioned mask for the `FLASH_CR_OPTER` field @def FLASH_CR_OPTER_Msk */
#define FLASH_CR_OPTER_Msk		REG_BIT_MASK(FLASH_CR_OPTER_Pos)
/** @brief Option Byte Erase @def FLASH_CR_OPTER */
#define FLASH_CR_OPTER			FLASH_CR_OPTER_Msk
/** @brief Bit position of the `FLASH_CR_STRT` field @def FLASH_CR_STRT_Pos */
#define FLASH_CR_STRT_Pos		((reg_bit_pos_t) 6U)
/** @brief Register-positioned mask for the `FLASH_CR_STRT` field @def FLASH_CR_STRT_Msk */
#define FLASH_CR_STRT_Msk		REG_BIT_MASK(FLASH_CR_STRT_Pos)
/** @brief Start @def FLASH_CR_STRT */
#define FLASH_CR_STRT			FLASH_CR_STRT_Msk
/** @brief Bit position of the `FLASH_CR_LOCK` field @def FLASH_CR_LOCK_Pos */
#define FLASH_CR_LOCK_Pos		((reg_bit_pos_t) 7U)
/** @brief Register-positioned mask for the `FLASH_CR_LOCK` field @def FLASH_CR_LOCK_Msk */
#define FLASH_CR_LOCK_Msk		REG_BIT_MASK(FLASH_CR_LOCK_Pos)
/** @brief Lock @def FLASH_CR_LOCK */
#define FLASH_CR_LOCK			FLASH_CR_LOCK_Msk
/** @brief Bit position of the `FLASH_CR_OPTWRE` field @def FLASH_CR_OPTWRE_Pos */
#define FLASH_CR_OPTWRE_Pos		((reg_bit_pos_t) 9U)
/** @brief Register-positioned mask for the `FLASH_CR_OPTWRE` field @def FLASH_CR_OPTWRE_Msk */
#define FLASH_CR_OPTWRE_Msk		REG_BIT_MASK(FLASH_CR_OPTWRE_Pos)
/** @brief Option Bytes Write Enable @def FLASH_CR_OPTWRE */
#define FLASH_CR_OPTWRE			FLASH_CR_OPTWRE_Msk
/** @brief Bit position of the `FLASH_CR_ERRIE` field @def FLASH_CR_ERRIE_Pos */
#define FLASH_CR_ERRIE_Pos		((reg_bit_pos_t) 10U)
/** @brief Register-positioned mask for the `FLASH_CR_ERRIE` field @def FLASH_CR_ERRIE_Msk */
#define FLASH_CR_ERRIE_Msk		REG_BIT_MASK(FLASH_CR_ERRIE_Pos)
/** @brief Error Interrupt Enable @def FLASH_CR_ERRIE */
#define FLASH_CR_ERRIE			FLASH_CR_ERRIE_Msk
/** @brief Bit position of the `FLASH_CR_EOPIE` field @def FLASH_CR_EOPIE_Pos */
#define FLASH_CR_EOPIE_Pos		((reg_bit_pos_t) 12U)
/** @brief Register-positioned mask for the `FLASH_CR_EOPIE` field @def FLASH_CR_EOPIE_Msk */
#define FLASH_CR_EOPIE_Msk		REG_BIT_MASK(FLASH_CR_EOPIE_Pos)
/** @brief End of operation interrupt enable @def FLASH_CR_EOPIE */
#define FLASH_CR_EOPIE			FLASH_CR_EOPIE_Msk

// ---------------------------------- FLASH_AR Register Bit Defines ----------------------------------- //
/** @brief Bit position of the `FLASH_AR_FAR` field @def FLASH_AR_FAR_Pos */
#define FLASH_AR_FAR_Pos		((reg_bit_pos_t) 0U)
/** @brief Width of the `FLASH_AR_FAR` field @def FLASH_AR_FAR_Width */
#define FLASH_AR_FAR_Width		((reg_field_width_t) 32U)
/** @brief Register-positioned mask for the `FLASH_AR_FAR` field @def FLASH_AR_FAR_Msk */
#define FLASH_AR_FAR_Msk		((reg) 0xFFFFFFFFUL)
/** @brief Flash Address @def FLASH_AR_FAR */
#define FLASH_AR_FAR			FLASH_AR_FAR_Msk

// ---------------------------------- FLASH_OBR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `FLASH_OBR_OPTERR` field @def FLASH_OBR_OPTERR_Pos */
#define FLASH_OBR_OPTERR_Pos			((reg_bit_pos_t) 0U)
/** @brief Register-positioned mask for the `FLASH_OBR_OPTERR` field @def FLASH_OBR_OPTERR_Msk */
#define FLASH_OBR_OPTERR_Msk			REG_BIT_MASK(FLASH_OBR_OPTERR_Pos)
/** @brief Option Byte Error @def FLASH_OBR_OPTERR */
#define FLASH_OBR_OPTERR				FLASH_OBR_OPTERR_Msk
/** @brief Bit position of the `FLASH_OBR_RDPRT` field @def FLASH_OBR_RDPRT_Pos */
#define FLASH_OBR_RDPRT_Pos				((reg_bit_pos_t) 1U)
/** @brief Register-positioned mask for the `FLASH_OBR_RDPRT` field @def FLASH_OBR_RDPRT_Msk */
#define FLASH_OBR_RDPRT_Msk				REG_BIT_MASK(FLASH_OBR_RDPRT_Pos)
/** @brief Read protection @def FLASH_OBR_RDPRT */
#define FLASH_OBR_RDPRT					FLASH_OBR_RDPRT_Msk

/** @brief Bit position of the `FLASH_OBR_USER` field @def FLASH_OBR_USER_Pos */
#define FLASH_OBR_USER_Pos				((reg_bit_pos_t) 2U)
/** @brief Width of the `FLASH_OBR_USER` field @def FLASH_OBR_USER_Width */
#define FLASH_OBR_USER_Width			((reg_field_width_t) 3U)
/** @brief Register-positioned mask for the `FLASH_OBR_USER` field @def FLASH_OBR_USER_Msk */
#define FLASH_OBR_USER_Msk				REG_FIELD_MASK(FLASH_OBR_USER_Pos, FLASH_OBR_USER_Width)
/** @brief User Option Bytes @def FLASH_OBR_USER */
#define FLASH_OBR_USER					FLASH_OBR_USER_Msk
/** @brief Bit position of the `FLASH_OBR_IWDG_SW` field @def FLASH_OBR_IWDG_SW_Pos */
#define FLASH_OBR_IWDG_SW_Pos			((reg_bit_pos_t) 2U)
/** @brief Register-positioned mask for the `FLASH_OBR_IWDG_SW` field @def FLASH_OBR_IWDG_SW_Msk */
#define FLASH_OBR_IWDG_SW_Msk			REG_BIT_MASK(FLASH_OBR_IWDG_SW_Pos)
/** @brief IWDG SW @def FLASH_OBR_IWDG_SW */
#define FLASH_OBR_IWDG_SW				FLASH_OBR_IWDG_SW_Msk
/** @brief Bit position of the `FLASH_OBR_nRST_STOP` field @def FLASH_OBR_nRST_STOP_Pos */
#define FLASH_OBR_nRST_STOP_Pos			((reg_bit_pos_t) 3U)
/** @brief Register-positioned mask for the `FLASH_OBR_nRST_STOP` field @def FLASH_OBR_nRST_STOP_Msk */
#define FLASH_OBR_nRST_STOP_Msk			REG_BIT_MASK(FLASH_OBR_nRST_STOP_Pos)
/** @brief nRST_STOP @def FLASH_OBR_nRST_STOP */
#define FLASH_OBR_nRST_STOP				FLASH_OBR_nRST_STOP_Msk
/** @brief Bit position of the `FLASH_OBR_nRST_STDBY` field @def FLASH_OBR_nRST_STDBY_Pos */
#define FLASH_OBR_nRST_STDBY_Pos		((reg_bit_pos_t) 4U)
/** @brief Register-positioned mask for the `FLASH_OBR_nRST_STDBY` field @def FLASH_OBR_nRST_STDBY_Msk */
#define FLASH_OBR_nRST_STDBY_Msk		REG_BIT_MASK(FLASH_OBR_nRST_STDBY_Pos)
/** @brief nRST_STDBY @def FLASH_OBR_nRST_STDBY */
#define FLASH_OBR_nRST_STDBY			FLASH_OBR_nRST_STDBY_Msk
/** @brief Bit position of the `FLASH_OBR_DATA0` field @def FLASH_OBR_DATA0_Pos */
#define FLASH_OBR_DATA0_Pos				((reg_bit_pos_t) 10U)
/** @brief Width of the `FLASH_OBR_DATA0` field @def FLASH_OBR_DATA0_Width */
#define FLASH_OBR_DATA0_Width			((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_OBR_DATA0` field @def FLASH_OBR_DATA0_Msk */
#define FLASH_OBR_DATA0_Msk				REG_FIELD_MASK(FLASH_OBR_DATA0_Pos, FLASH_OBR_DATA0_Width)
/** @brief Data0 @def FLASH_OBR_DATA0 */
#define FLASH_OBR_DATA0					FLASH_OBR_DATA0_Msk
/** @brief Bit position of the `FLASH_OBR_DATA1` field @def FLASH_OBR_DATA1_Pos */
#define FLASH_OBR_DATA1_Pos				((reg_bit_pos_t) 18U)
/** @brief Width of the `FLASH_OBR_DATA1` field @def FLASH_OBR_DATA1_Width */
#define FLASH_OBR_DATA1_Width			((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_OBR_DATA1` field @def FLASH_OBR_DATA1_Msk */
#define FLASH_OBR_DATA1_Msk				REG_FIELD_MASK(FLASH_OBR_DATA1_Pos, FLASH_OBR_DATA1_Width)
/** @brief Data1 @def FLASH_OBR_DATA1 */
#define FLASH_OBR_DATA1					FLASH_OBR_DATA1_Msk

// --------------------------------- FLASH_WRPR Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `FLASH_WRPR_WRP` field @def FLASH_WRPR_WRP_Pos */
#define FLASH_WRPR_WRP_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `FLASH_WRPR_WRP` field @def FLASH_WRPR_WRP_Width */
#define FLASH_WRPR_WRP_Width		((reg_field_width_t) 32U)
/** @brief Register-positioned mask for the `FLASH_WRPR_WRP` field @def FLASH_WRPR_WRP_Msk */
#define FLASH_WRPR_WRP_Msk			((reg) 0xFFFFFFFFUL)
/** @brief Write Protect @def FLASH_WRPR_WRP */
#define FLASH_WRPR_WRP				FLASH_WRPR_WRP_Msk

// -------------------------------- Flash Option-Byte Register Defines -------------------------------- //

// ---------------------------------- FLASH_RDP Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `FLASH_RDP_RDP` field @def FLASH_RDP_RDP_Pos */
#define FLASH_RDP_RDP_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `FLASH_RDP_RDP` field @def FLASH_RDP_RDP_Width */
#define FLASH_RDP_RDP_Width			((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_RDP_RDP` field @def FLASH_RDP_RDP_Msk */
#define FLASH_RDP_RDP_Msk			REG_FIELD_MASK(FLASH_RDP_RDP_Pos, FLASH_RDP_RDP_Width)
/** @brief Read protection option byte @def FLASH_RDP_RDP */
#define FLASH_RDP_RDP				FLASH_RDP_RDP_Msk
/** @brief Bit position of the `FLASH_RDP_nRDP` field @def FLASH_RDP_nRDP_Pos */
#define FLASH_RDP_nRDP_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `FLASH_RDP_nRDP` field @def FLASH_RDP_nRDP_Width */
#define FLASH_RDP_nRDP_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_RDP_nRDP` field @def FLASH_RDP_nRDP_Msk */
#define FLASH_RDP_nRDP_Msk			REG_FIELD_MASK(FLASH_RDP_nRDP_Pos, FLASH_RDP_nRDP_Width)
/** @brief Read protection complemented option byte @def FLASH_RDP_nRDP */
#define FLASH_RDP_nRDP				FLASH_RDP_nRDP_Msk

// --------------------------------- FLASH_USER Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `FLASH_USER_USER` field @def FLASH_USER_USER_Pos */
#define FLASH_USER_USER_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `FLASH_USER_USER` field @def FLASH_USER_USER_Width */
#define FLASH_USER_USER_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_USER_USER` field @def FLASH_USER_USER_Msk */
#define FLASH_USER_USER_Msk			REG_FIELD_MASK(FLASH_USER_USER_Pos, FLASH_USER_USER_Width)
/** @brief User option byte @def FLASH_USER_USER */
#define FLASH_USER_USER				FLASH_USER_USER_Msk
/** @brief Bit position of the `FLASH_USER_nUSER` field @def FLASH_USER_nUSER_Pos */
#define FLASH_USER_nUSER_Pos		((reg_bit_pos_t) 24U)
/** @brief Width of the `FLASH_USER_nUSER` field @def FLASH_USER_nUSER_Width */
#define FLASH_USER_nUSER_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_USER_nUSER` field @def FLASH_USER_nUSER_Msk */
#define FLASH_USER_nUSER_Msk		REG_FIELD_MASK(FLASH_USER_nUSER_Pos, FLASH_USER_nUSER_Width)
/** @brief User complemented option byte @def FLASH_USER_nUSER */
#define FLASH_USER_nUSER			FLASH_USER_nUSER_Msk

// --------------------------------- FLASH_Data0 Register Bit Defines --------------------------------- //
/** @brief Bit position of the `FLASH_DATA0_DATA0` field @def FLASH_DATA0_DATA0_Pos */
#define FLASH_DATA0_DATA0_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `FLASH_DATA0_DATA0` field @def FLASH_DATA0_DATA0_Width */
#define FLASH_DATA0_DATA0_Width			((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_DATA0_DATA0` field @def FLASH_DATA0_DATA0_Msk */
#define FLASH_DATA0_DATA0_Msk			REG_FIELD_MASK(FLASH_DATA0_DATA0_Pos, FLASH_DATA0_DATA0_Width)
/** @brief User data storage option byte @def FLASH_DATA0_DATA0 */
#define FLASH_DATA0_DATA0				FLASH_DATA0_DATA0_Msk
/** @brief Bit position of the `FLASH_DATA0_nDATA0` field @def FLASH_DATA0_nDATA0_Pos */
#define FLASH_DATA0_nDATA0_Pos			((reg_bit_pos_t) 8U)
/** @brief Width of the `FLASH_DATA0_nDATA0` field @def FLASH_DATA0_nDATA0_Width */
#define FLASH_DATA0_nDATA0_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_DATA0_nDATA0` field @def FLASH_DATA0_nDATA0_Msk */
#define FLASH_DATA0_nDATA0_Msk			REG_FIELD_MASK(FLASH_DATA0_nDATA0_Pos, FLASH_DATA0_nDATA0_Width)
/** @brief User data storage complemented option byte @def FLASH_DATA0_nDATA0 */
#define FLASH_DATA0_nDATA0				FLASH_DATA0_nDATA0_Msk

// --------------------------------- FLASH_Data1 Register Bit Defines --------------------------------- //
/** @brief Bit position of the `FLASH_DATA1_DATA1` field @def FLASH_DATA1_DATA1_Pos */
#define FLASH_DATA1_DATA1_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `FLASH_DATA1_DATA1` field @def FLASH_DATA1_DATA1_Width */
#define FLASH_DATA1_DATA1_Width			((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_DATA1_DATA1` field @def FLASH_DATA1_DATA1_Msk */
#define FLASH_DATA1_DATA1_Msk			REG_FIELD_MASK(FLASH_DATA1_DATA1_Pos, FLASH_DATA1_DATA1_Width)
/** @brief User data storage option byte @def FLASH_DATA1_DATA1 */
#define FLASH_DATA1_DATA1				FLASH_DATA1_DATA1_Msk
/** @brief Bit position of the `FLASH_DATA1_nDATA1` field @def FLASH_DATA1_nDATA1_Pos */
#define FLASH_DATA1_nDATA1_Pos			((reg_bit_pos_t) 24U)
/** @brief Width of the `FLASH_DATA1_nDATA1` field @def FLASH_DATA1_nDATA1_Width */
#define FLASH_DATA1_nDATA1_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_DATA1_nDATA1` field @def FLASH_DATA1_nDATA1_Msk */
#define FLASH_DATA1_nDATA1_Msk			REG_FIELD_MASK(FLASH_DATA1_nDATA1_Pos, FLASH_DATA1_nDATA1_Width)
/** @brief User data storage complemented option byte @def FLASH_DATA1_nDATA1 */
#define FLASH_DATA1_nDATA1				FLASH_DATA1_nDATA1_Msk

// --------------------------------- FLASH_WRP0 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `FLASH_WRP0_WRP0` field @def FLASH_WRP0_WRP0_Pos */
#define FLASH_WRP0_WRP0_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `FLASH_WRP0_WRP0` field @def FLASH_WRP0_WRP0_Width */
#define FLASH_WRP0_WRP0_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_WRP0_WRP0` field @def FLASH_WRP0_WRP0_Msk */
#define FLASH_WRP0_WRP0_Msk			REG_FIELD_MASK(FLASH_WRP0_WRP0_Pos, FLASH_WRP0_WRP0_Width)
/** @brief Flash memory write protection option bytes @def FLASH_WRP0_WRP0 */
#define FLASH_WRP0_WRP0				FLASH_WRP0_WRP0_Msk
/** @brief Bit position of the `FLASH_WRP0_nWRP0` field @def FLASH_WRP0_nWRP0_Pos */
#define FLASH_WRP0_nWRP0_Pos		((reg_bit_pos_t) 8U)
/** @brief Width of the `FLASH_WRP0_nWRP0` field @def FLASH_WRP0_nWRP0_Width */
#define FLASH_WRP0_nWRP0_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_WRP0_nWRP0` field @def FLASH_WRP0_nWRP0_Msk */
#define FLASH_WRP0_nWRP0_Msk		REG_FIELD_MASK(FLASH_WRP0_nWRP0_Pos, FLASH_WRP0_nWRP0_Width)
/** @brief Flash memory write protection complemented option bytes @def FLASH_WRP0_nWRP0 */
#define FLASH_WRP0_nWRP0			FLASH_WRP0_nWRP0_Msk

// --------------------------------- FLASH_WRP1 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `FLASH_WRP1_WRP1` field @def FLASH_WRP1_WRP1_Pos */
#define FLASH_WRP1_WRP1_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `FLASH_WRP1_WRP1` field @def FLASH_WRP1_WRP1_Width */
#define FLASH_WRP1_WRP1_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_WRP1_WRP1` field @def FLASH_WRP1_WRP1_Msk */
#define FLASH_WRP1_WRP1_Msk			REG_FIELD_MASK(FLASH_WRP1_WRP1_Pos, FLASH_WRP1_WRP1_Width)
/** @brief Flash memory write protection option bytes @def FLASH_WRP1_WRP1 */
#define FLASH_WRP1_WRP1				FLASH_WRP1_WRP1_Msk
/** @brief Bit position of the `FLASH_WRP1_nWRP1` field @def FLASH_WRP1_nWRP1_Pos */
#define FLASH_WRP1_nWRP1_Pos		((reg_bit_pos_t) 24U)
/** @brief Width of the `FLASH_WRP1_nWRP1` field @def FLASH_WRP1_nWRP1_Width */
#define FLASH_WRP1_nWRP1_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_WRP1_nWRP1` field @def FLASH_WRP1_nWRP1_Msk */
#define FLASH_WRP1_nWRP1_Msk		REG_FIELD_MASK(FLASH_WRP1_nWRP1_Pos, FLASH_WRP1_nWRP1_Width)
/** @brief Flash memory write protection complemented option bytes @def FLASH_WRP1_nWRP1 */
#define FLASH_WRP1_nWRP1			FLASH_WRP1_nWRP1_Msk

// --------------------------------- FLASH_WRP2 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `FLASH_WRP2_WRP2` field @def FLASH_WRP2_WRP2_Pos */
#define FLASH_WRP2_WRP2_Pos			((reg_bit_pos_t) 0U)
/** @brief Width of the `FLASH_WRP2_WRP2` field @def FLASH_WRP2_WRP2_Width */
#define FLASH_WRP2_WRP2_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_WRP2_WRP2` field @def FLASH_WRP2_WRP2_Msk */
#define FLASH_WRP2_WRP2_Msk			REG_FIELD_MASK(FLASH_WRP2_WRP2_Pos, FLASH_WRP2_WRP2_Width)
/** @brief Flash memory write protection option bytes @def FLASH_WRP2_WRP2 */
#define FLASH_WRP2_WRP2				FLASH_WRP2_WRP2_Msk
/** @brief Bit position of the `FLASH_WRP2_nWRP2` field @def FLASH_WRP2_nWRP2_Pos */
#define FLASH_WRP2_nWRP2_Pos		((reg_bit_pos_t) 8U)
/** @brief Width of the `FLASH_WRP2_nWRP2` field @def FLASH_WRP2_nWRP2_Width */
#define FLASH_WRP2_nWRP2_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_WRP2_nWRP2` field @def FLASH_WRP2_nWRP2_Msk */
#define FLASH_WRP2_nWRP2_Msk		REG_FIELD_MASK(FLASH_WRP2_nWRP2_Pos, FLASH_WRP2_nWRP2_Width)
/** @brief Flash memory write protection complemented option bytes @def FLASH_WRP2_nWRP2 */
#define FLASH_WRP2_nWRP2			FLASH_WRP2_nWRP2_Msk

// --------------------------------- FLASH_WRP3 Register Bit Defines ---------------------------------- //
/** @brief Bit position of the `FLASH_WRP3_WRP3` field @def FLASH_WRP3_WRP3_Pos */
#define FLASH_WRP3_WRP3_Pos			((reg_bit_pos_t) 16U)
/** @brief Width of the `FLASH_WRP3_WRP3` field @def FLASH_WRP3_WRP3_Width */
#define FLASH_WRP3_WRP3_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_WRP3_WRP3` field @def FLASH_WRP3_WRP3_Msk */
#define FLASH_WRP3_WRP3_Msk			REG_FIELD_MASK(FLASH_WRP3_WRP3_Pos, FLASH_WRP3_WRP3_Width)
/** @brief Flash memory write protection option bytes @def FLASH_WRP3_WRP3 */
#define FLASH_WRP3_WRP3				FLASH_WRP3_WRP3_Msk
/** @brief Bit position of the `FLASH_WRP3_nWRP3` field @def FLASH_WRP3_nWRP3_Pos */
#define FLASH_WRP3_nWRP3_Pos		((reg_bit_pos_t) 24U)
/** @brief Width of the `FLASH_WRP3_nWRP3` field @def FLASH_WRP3_nWRP3_Width */
#define FLASH_WRP3_nWRP3_Width		((reg_field_width_t) 8U)
/** @brief Register-positioned mask for the `FLASH_WRP3_nWRP3` field @def FLASH_WRP3_nWRP3_Msk */
#define FLASH_WRP3_nWRP3_Msk		REG_FIELD_MASK(FLASH_WRP3_nWRP3_Pos, FLASH_WRP3_nWRP3_Width)
/** @brief Flash memory write protection complemented option bytes @def FLASH_WRP3_nWRP3 */
#define FLASH_WRP3_nWRP3			FLASH_WRP3_nWRP3_Msk

/** @} */ // STM32F1xx_Defines

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_DEFINES_H_ */
