/**
 * @file stm32f1xx_flash.h
 * @author Shrey Shah
 * @brief STM32F1 Flash Memory Interface Register-Layer Definitions
 * @version v1.1
 * @date 23-08-2026
 * @details
 * This file is the canonical Core-layer owner of the STM32F103C8T6 Flash
 * memory interface register map, raw register-field positions, masks, key
 * values, and option-byte field definitions. It depends only on
 * `stm32f1xx_utils.h`; Flash access policy and clock-transition sequencing
 * remain responsibilities of higher layers such as the RCC Driver.
 */

// Header Guards
#ifndef STM32F1XX_FLASH_H_
#define STM32F1XX_FLASH_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx_utils.h"

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup FLASH Flash Memory Interface (FLASH)
 * @brief STM32F1 Flash access timing, erase/program control, status, and option-byte infrastructure
 * @details
 * RM0008 describes the Flash memory interface as the hardware block that:
 * - controls instruction-fetch latency and prefetch through `FLASH_ACR`,
 * - unlocks main Flash and option-byte operations through keyed write ports,
 * - reports programming state and completion/error events through `FLASH_SR`,
 * - selects programming, page erase, mass erase, and option-byte operations
 *   through `FLASH_CR`,
 * - receives the page erase address through `FLASH_AR`,
 * - publishes loaded option-byte state through `FLASH_OBR` and `FLASH_WRPR`.
 *
 * @section FLASH_RegisterLayoutBrief Register Layout Brief
 * <table>
 * <tr><th>Register</th><th>Offset</th><th>Primary Practical Role</th></tr>
 * <tr><td><code>FLASH_ACR</code></td><td><code>0x00</code></td><td>Read latency, half-cycle access, and prefetch control/status</td></tr>
 * <tr><td><code>FLASH_KEYR</code></td><td><code>0x04</code></td><td>Main Flash program/erase unlock key port</td></tr>
 * <tr><td><code>FLASH_OPTKEYR</code></td><td><code>0x08</code></td><td>Option-byte unlock key port</td></tr>
 * <tr><td><code>FLASH_SR</code></td><td><code>0x0C</code></td><td>Busy, programming error, write-protection error, and completion state</td></tr>
 * <tr><td><code>FLASH_CR</code></td><td><code>0x10</code></td><td>Program/erase selection, start, locking, and interrupt-source control</td></tr>
 * <tr><td><code>FLASH_AR</code></td><td><code>0x14</code></td><td>Target address for page erase</td></tr>
 * <tr><td><code>FLASH_OBR</code></td><td><code>0x1C</code></td><td>Loaded read-protection, user, and data option-byte state</td></tr>
 * <tr><td><code>FLASH_WRPR</code></td><td><code>0x20</code></td><td>Loaded Flash write-protection state</td></tr>
 * </table>
 *
 * The separately mapped option-byte storage exposes each value together with
 * its hardware complement. Its raw symbols are owned here because those
 * values are consumed by the same Flash programming infrastructure, but the
 * option-byte storage is not part of @ref FLASH_TypeDef.
 *
 * This codebase currently documents Flash through two ownership levels:
 * - Register layer: @ref `stm32f1xx_flash.h`
 * - Clock-transition policy and orchestration: @ref `rcc.h`
 */

/**
 * @defgroup FLASH_01_RegisterLayer Flash Register Layer
 * @ingroup FLASH
 * @brief Raw STM32F1 Flash register structures, field definitions, and key values
 * @details
 * This layer mirrors the hardware-visible Flash register model. It owns raw
 * register vocabulary only; validation, timing policy, unlock sequencing,
 * polling, and error handling belong above this Core register layer.
 */

/**
 * @addtogroup FLASH_01_RegisterLayer
 * @{
 */

// ==================================================================================================== //
//										Flash Register Defines										//
// ==================================================================================================== //

/**
 * @defgroup FLASH_01_RegisterLayer_00_RegisterDefines Flash Register Bit Positions, Masks, and Values
 * @ingroup FLASH_01_RegisterLayer
 * @brief Raw Flash interface and option-byte register vocabulary
 * @details
 * Single-bit fields expose a position, a mask built with @ref REG_BIT_MASK,
 * and an unsuffixed mask alias. Multi-bit fields additionally expose a width
 * and use @ref REG_FIELD_MASK. Full 32-bit fields retain an explicit mask
 * because @ref REG_FIELD_MASK accepts widths only through `31U`.
 *
 * Key constants and field selector values are positioned values, not masks;
 * they therefore use @ref REG_FIELD_VALUE without misleading `_Msk` aliases.
 * @{
 */

// ---------------------------------------------------------------------------------------------------- //
//											FLASH_ACR											//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Flash read latency (`FLASH_ACR.LATENCY[2:0]`) field position @def FLASH_ACR_LATENCY_Pos */
#define FLASH_ACR_LATENCY_Pos				((reg_bit_pos_t) 0U)
/** @brief Flash read latency (`FLASH_ACR.LATENCY[2:0]`) field width @def FLASH_ACR_LATENCY_Width */
#define FLASH_ACR_LATENCY_Width				((reg_field_width_t) 3U)
/** @brief Flash read latency (`FLASH_ACR.LATENCY[2:0]`) field mask @def FLASH_ACR_LATENCY_Msk */
#define FLASH_ACR_LATENCY_Msk				REG_FIELD_MASK(FLASH_ACR_LATENCY_Pos, FLASH_ACR_LATENCY_Width)
/** @brief Flash read latency (`FLASH_ACR.LATENCY[2:0]`) field mask alias @def FLASH_ACR_LATENCY */
#define FLASH_ACR_LATENCY					FLASH_ACR_LATENCY_Msk
/** @brief Flash read latency raw value: zero wait states @def FLASH_ACR_LATENCY_0 */
#define FLASH_ACR_LATENCY_0					REG_FIELD_VALUE(FLASH_ACR_LATENCY_Pos, 0x00UL)
/** @brief Flash read latency raw value: one wait state @def FLASH_ACR_LATENCY_1 */
#define FLASH_ACR_LATENCY_1					REG_FIELD_VALUE(FLASH_ACR_LATENCY_Pos, 0x01UL)
/** @brief Flash read latency raw value: two wait states @def FLASH_ACR_LATENCY_2 */
#define FLASH_ACR_LATENCY_2					REG_FIELD_VALUE(FLASH_ACR_LATENCY_Pos, 0x02UL)

/** @brief Flash half-cycle access enable (`FLASH_ACR.HLFCYA`) bit position @def FLASH_ACR_HLFCYA_Pos */
#define FLASH_ACR_HLFCYA_Pos				((reg_bit_pos_t) 3U)
/** @brief Flash half-cycle access enable (`FLASH_ACR.HLFCYA`) bit mask @def FLASH_ACR_HLFCYA_Msk */
#define FLASH_ACR_HLFCYA_Msk				REG_BIT_MASK(FLASH_ACR_HLFCYA_Pos)
/** @brief Flash half-cycle access enable (`FLASH_ACR.HLFCYA`) bit mask alias @def FLASH_ACR_HLFCYA */
#define FLASH_ACR_HLFCYA					FLASH_ACR_HLFCYA_Msk

/** @brief Prefetch buffer enable (`FLASH_ACR.PRFTBE`) bit position @def FLASH_ACR_PRFTBE_Pos */
#define FLASH_ACR_PRFTBE_Pos				((reg_bit_pos_t) 4U)
/** @brief Prefetch buffer enable (`FLASH_ACR.PRFTBE`) bit mask @def FLASH_ACR_PRFTBE_Msk */
#define FLASH_ACR_PRFTBE_Msk				REG_BIT_MASK(FLASH_ACR_PRFTBE_Pos)
/** @brief Prefetch buffer enable (`FLASH_ACR.PRFTBE`) bit mask alias @def FLASH_ACR_PRFTBE */
#define FLASH_ACR_PRFTBE					FLASH_ACR_PRFTBE_Msk

/** @brief Prefetch buffer status (`FLASH_ACR.PRFTBS`) bit position @def FLASH_ACR_PRFTBS_Pos */
#define FLASH_ACR_PRFTBS_Pos				((reg_bit_pos_t) 5U)
/** @brief Prefetch buffer status (`FLASH_ACR.PRFTBS`) bit mask @def FLASH_ACR_PRFTBS_Msk */
#define FLASH_ACR_PRFTBS_Msk				REG_BIT_MASK(FLASH_ACR_PRFTBS_Pos)
/** @brief Prefetch buffer status (`FLASH_ACR.PRFTBS`) bit mask alias @def FLASH_ACR_PRFTBS */
#define FLASH_ACR_PRFTBS					FLASH_ACR_PRFTBS_Msk

// ---------------------------------------------------------------------------------------------------- //
//											FLASH_KEYR											//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Main Flash unlock key (`FLASH_KEYR.FKEYR[31:0]`) field position @def FLASH_KEYR_FKEYR_Pos */
#define FLASH_KEYR_FKEYR_Pos				((reg_bit_pos_t) 0U)
/** @brief Main Flash unlock key (`FLASH_KEYR.FKEYR[31:0]`) field width @def FLASH_KEYR_FKEYR_Width */
#define FLASH_KEYR_FKEYR_Width				((reg_field_width_t) 32U)
/** @brief Main Flash unlock key (`FLASH_KEYR.FKEYR[31:0]`) field mask @def FLASH_KEYR_FKEYR_Msk */
#define FLASH_KEYR_FKEYR_Msk				((reg) 0xFFFFFFFFUL)
/** @brief Main Flash unlock key (`FLASH_KEYR.FKEYR[31:0]`) field mask alias @def FLASH_KEYR_FKEYR */
#define FLASH_KEYR_FKEYR					FLASH_KEYR_FKEYR_Msk

/** @brief Read-protection option-byte key field position @def RDP_KEY_Pos */
#define RDP_KEY_Pos							((reg_bit_pos_t) 0U)
/** @brief Read-protection option-byte positioned key value compatibility alias @def RDP_KEY_Msk */
#define RDP_KEY_Msk							REG_FIELD_VALUE(RDP_KEY_Pos, 0xA5UL)
/** @brief Read-protection option-byte key value alias @def RDP_KEY */
#define RDP_KEY								RDP_KEY_Msk

/** @brief First main Flash unlock key field position @def FLASH_KEY1_Pos */
#define FLASH_KEY1_Pos						FLASH_KEYR_FKEYR_Pos
/** @brief First main Flash unlock positioned key value compatibility alias @def FLASH_KEY1_Msk */
#define FLASH_KEY1_Msk						REG_FIELD_VALUE(FLASH_KEY1_Pos, 0x45670123UL)
/** @brief First main Flash unlock key value alias @def FLASH_KEY1 */
#define FLASH_KEY1							FLASH_KEY1_Msk

/** @brief Second main Flash unlock key field position @def FLASH_KEY2_Pos */
#define FLASH_KEY2_Pos						FLASH_KEYR_FKEYR_Pos
/** @brief Second main Flash unlock positioned key value compatibility alias @def FLASH_KEY2_Msk */
#define FLASH_KEY2_Msk						REG_FIELD_VALUE(FLASH_KEY2_Pos, 0xCDEF89ABUL)
/** @brief Second main Flash unlock key value alias @def FLASH_KEY2 */
#define FLASH_KEY2							FLASH_KEY2_Msk

// ---------------------------------------------------------------------------------------------------- //
//										FLASH_OPTKEYR										//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Option-byte unlock key (`FLASH_OPTKEYR.OPTKEYR[31:0]`) field position @def FLASH_OPTKEYR_OPTKEYR_Pos */
#define FLASH_OPTKEYR_OPTKEYR_Pos			((reg_bit_pos_t) 0U)
/** @brief Option-byte unlock key (`FLASH_OPTKEYR.OPTKEYR[31:0]`) field width @def FLASH_OPTKEYR_OPTKEYR_Width */
#define FLASH_OPTKEYR_OPTKEYR_Width			((reg_field_width_t) 32U)
/** @brief Option-byte unlock key (`FLASH_OPTKEYR.OPTKEYR[31:0]`) field mask @def FLASH_OPTKEYR_OPTKEYR_Msk */
#define FLASH_OPTKEYR_OPTKEYR_Msk			((reg) 0xFFFFFFFFUL)
/** @brief Option-byte unlock key (`FLASH_OPTKEYR.OPTKEYR[31:0]`) field mask alias @def FLASH_OPTKEYR_OPTKEYR */
#define FLASH_OPTKEYR_OPTKEYR				FLASH_OPTKEYR_OPTKEYR_Msk
/** @brief First option-byte unlock key value @def FLASH_OPTKEY1 */
#define FLASH_OPTKEY1						FLASH_KEY1
/** @brief Second option-byte unlock key value @def FLASH_OPTKEY2 */
#define FLASH_OPTKEY2						FLASH_KEY2

// ---------------------------------------------------------------------------------------------------- //
//											FLASH_SR											//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Flash operation busy (`FLASH_SR.BSY`) bit position @def FLASH_SR_BSY_Pos */
#define FLASH_SR_BSY_Pos						((reg_bit_pos_t) 0U)
/** @brief Flash operation busy (`FLASH_SR.BSY`) bit mask @def FLASH_SR_BSY_Msk */
#define FLASH_SR_BSY_Msk						REG_BIT_MASK(FLASH_SR_BSY_Pos)
/** @brief Flash operation busy (`FLASH_SR.BSY`) bit mask alias @def FLASH_SR_BSY */
#define FLASH_SR_BSY							FLASH_SR_BSY_Msk

/** @brief Programming error (`FLASH_SR.PGERR`) bit position @def FLASH_SR_PGERR_Pos */
#define FLASH_SR_PGERR_Pos					((reg_bit_pos_t) 2U)
/** @brief Programming error (`FLASH_SR.PGERR`) bit mask @def FLASH_SR_PGERR_Msk */
#define FLASH_SR_PGERR_Msk					REG_BIT_MASK(FLASH_SR_PGERR_Pos)
/** @brief Programming error (`FLASH_SR.PGERR`) bit mask alias @def FLASH_SR_PGERR */
#define FLASH_SR_PGERR						FLASH_SR_PGERR_Msk

/** @brief Write-protection error (`FLASH_SR.WRPRTERR`) bit position @def FLASH_SR_WRPRTERR_Pos */
#define FLASH_SR_WRPRTERR_Pos				((reg_bit_pos_t) 4U)
/** @brief Write-protection error (`FLASH_SR.WRPRTERR`) bit mask @def FLASH_SR_WRPRTERR_Msk */
#define FLASH_SR_WRPRTERR_Msk				REG_BIT_MASK(FLASH_SR_WRPRTERR_Pos)
/** @brief Write-protection error (`FLASH_SR.WRPRTERR`) bit mask alias @def FLASH_SR_WRPRTERR */
#define FLASH_SR_WRPRTERR					FLASH_SR_WRPRTERR_Msk

/** @brief End-of-operation event (`FLASH_SR.EOP`) bit position @def FLASH_SR_EOP_Pos */
#define FLASH_SR_EOP_Pos						((reg_bit_pos_t) 5U)
/** @brief End-of-operation event (`FLASH_SR.EOP`) bit mask @def FLASH_SR_EOP_Msk */
#define FLASH_SR_EOP_Msk						REG_BIT_MASK(FLASH_SR_EOP_Pos)
/** @brief End-of-operation event (`FLASH_SR.EOP`) bit mask alias @def FLASH_SR_EOP */
#define FLASH_SR_EOP							FLASH_SR_EOP_Msk

// ---------------------------------------------------------------------------------------------------- //
//											FLASH_CR											//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Flash programming enable (`FLASH_CR.PG`) bit position @def FLASH_CR_PG_Pos */
#define FLASH_CR_PG_Pos						((reg_bit_pos_t) 0U)
/** @brief Flash programming enable (`FLASH_CR.PG`) bit mask @def FLASH_CR_PG_Msk */
#define FLASH_CR_PG_Msk						REG_BIT_MASK(FLASH_CR_PG_Pos)
/** @brief Flash programming enable (`FLASH_CR.PG`) bit mask alias @def FLASH_CR_PG */
#define FLASH_CR_PG							FLASH_CR_PG_Msk

/** @brief Page erase enable (`FLASH_CR.PER`) bit position @def FLASH_CR_PER_Pos */
#define FLASH_CR_PER_Pos						((reg_bit_pos_t) 1U)
/** @brief Page erase enable (`FLASH_CR.PER`) bit mask @def FLASH_CR_PER_Msk */
#define FLASH_CR_PER_Msk						REG_BIT_MASK(FLASH_CR_PER_Pos)
/** @brief Page erase enable (`FLASH_CR.PER`) bit mask alias @def FLASH_CR_PER */
#define FLASH_CR_PER							FLASH_CR_PER_Msk

/** @brief Mass erase enable (`FLASH_CR.MER`) bit position @def FLASH_CR_MER_Pos */
#define FLASH_CR_MER_Pos						((reg_bit_pos_t) 2U)
/** @brief Mass erase enable (`FLASH_CR.MER`) bit mask @def FLASH_CR_MER_Msk */
#define FLASH_CR_MER_Msk						REG_BIT_MASK(FLASH_CR_MER_Pos)
/** @brief Mass erase enable (`FLASH_CR.MER`) bit mask alias @def FLASH_CR_MER */
#define FLASH_CR_MER							FLASH_CR_MER_Msk

/** @brief Option-byte programming enable (`FLASH_CR.OPTPG`) bit position @def FLASH_CR_OPTPG_Pos */
#define FLASH_CR_OPTPG_Pos					((reg_bit_pos_t) 4U)
/** @brief Option-byte programming enable (`FLASH_CR.OPTPG`) bit mask @def FLASH_CR_OPTPG_Msk */
#define FLASH_CR_OPTPG_Msk					REG_BIT_MASK(FLASH_CR_OPTPG_Pos)
/** @brief Option-byte programming enable (`FLASH_CR.OPTPG`) bit mask alias @def FLASH_CR_OPTPG */
#define FLASH_CR_OPTPG						FLASH_CR_OPTPG_Msk

/** @brief Option-byte erase enable (`FLASH_CR.OPTER`) bit position @def FLASH_CR_OPTER_Pos */
#define FLASH_CR_OPTER_Pos					((reg_bit_pos_t) 5U)
/** @brief Option-byte erase enable (`FLASH_CR.OPTER`) bit mask @def FLASH_CR_OPTER_Msk */
#define FLASH_CR_OPTER_Msk					REG_BIT_MASK(FLASH_CR_OPTER_Pos)
/** @brief Option-byte erase enable (`FLASH_CR.OPTER`) bit mask alias @def FLASH_CR_OPTER */
#define FLASH_CR_OPTER						FLASH_CR_OPTER_Msk

/** @brief Erase operation start (`FLASH_CR.STRT`) bit position @def FLASH_CR_STRT_Pos */
#define FLASH_CR_STRT_Pos					((reg_bit_pos_t) 6U)
/** @brief Erase operation start (`FLASH_CR.STRT`) bit mask @def FLASH_CR_STRT_Msk */
#define FLASH_CR_STRT_Msk					REG_BIT_MASK(FLASH_CR_STRT_Pos)
/** @brief Erase operation start (`FLASH_CR.STRT`) bit mask alias @def FLASH_CR_STRT */
#define FLASH_CR_STRT						FLASH_CR_STRT_Msk

/** @brief Main Flash program/erase lock (`FLASH_CR.LOCK`) bit position @def FLASH_CR_LOCK_Pos */
#define FLASH_CR_LOCK_Pos					((reg_bit_pos_t) 7U)
/** @brief Main Flash program/erase lock (`FLASH_CR.LOCK`) bit mask @def FLASH_CR_LOCK_Msk */
#define FLASH_CR_LOCK_Msk					REG_BIT_MASK(FLASH_CR_LOCK_Pos)
/** @brief Main Flash program/erase lock (`FLASH_CR.LOCK`) bit mask alias @def FLASH_CR_LOCK */
#define FLASH_CR_LOCK						FLASH_CR_LOCK_Msk

/** @brief Option-byte write enable (`FLASH_CR.OPTWRE`) bit position @def FLASH_CR_OPTWRE_Pos */
#define FLASH_CR_OPTWRE_Pos					((reg_bit_pos_t) 9U)
/** @brief Option-byte write enable (`FLASH_CR.OPTWRE`) bit mask @def FLASH_CR_OPTWRE_Msk */
#define FLASH_CR_OPTWRE_Msk					REG_BIT_MASK(FLASH_CR_OPTWRE_Pos)
/** @brief Option-byte write enable (`FLASH_CR.OPTWRE`) bit mask alias @def FLASH_CR_OPTWRE */
#define FLASH_CR_OPTWRE						FLASH_CR_OPTWRE_Msk

/** @brief Flash error interrupt enable (`FLASH_CR.ERRIE`) bit position @def FLASH_CR_ERRIE_Pos */
#define FLASH_CR_ERRIE_Pos					((reg_bit_pos_t) 10U)
/** @brief Flash error interrupt enable (`FLASH_CR.ERRIE`) bit mask @def FLASH_CR_ERRIE_Msk */
#define FLASH_CR_ERRIE_Msk					REG_BIT_MASK(FLASH_CR_ERRIE_Pos)
/** @brief Flash error interrupt enable (`FLASH_CR.ERRIE`) bit mask alias @def FLASH_CR_ERRIE */
#define FLASH_CR_ERRIE						FLASH_CR_ERRIE_Msk

/** @brief End-of-operation interrupt enable (`FLASH_CR.EOPIE`) bit position @def FLASH_CR_EOPIE_Pos */
#define FLASH_CR_EOPIE_Pos					((reg_bit_pos_t) 12U)
/** @brief End-of-operation interrupt enable (`FLASH_CR.EOPIE`) bit mask @def FLASH_CR_EOPIE_Msk */
#define FLASH_CR_EOPIE_Msk					REG_BIT_MASK(FLASH_CR_EOPIE_Pos)
/** @brief End-of-operation interrupt enable (`FLASH_CR.EOPIE`) bit mask alias @def FLASH_CR_EOPIE */
#define FLASH_CR_EOPIE						FLASH_CR_EOPIE_Msk

// ---------------------------------------------------------------------------------------------------- //
//											FLASH_AR											//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Page erase address (`FLASH_AR.FAR[31:0]`) field position @def FLASH_AR_FAR_Pos */
#define FLASH_AR_FAR_Pos						((reg_bit_pos_t) 0U)
/** @brief Page erase address (`FLASH_AR.FAR[31:0]`) field width @def FLASH_AR_FAR_Width */
#define FLASH_AR_FAR_Width					((reg_field_width_t) 32U)
/** @brief Page erase address (`FLASH_AR.FAR[31:0]`) field mask @def FLASH_AR_FAR_Msk */
#define FLASH_AR_FAR_Msk						((reg) 0xFFFFFFFFUL)
/** @brief Page erase address (`FLASH_AR.FAR[31:0]`) field mask alias @def FLASH_AR_FAR */
#define FLASH_AR_FAR							FLASH_AR_FAR_Msk

// ---------------------------------------------------------------------------------------------------- //
//											FLASH_OBR											//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Option-byte loading error (`FLASH_OBR.OPTERR`) bit position @def FLASH_OBR_OPTERR_Pos */
#define FLASH_OBR_OPTERR_Pos					((reg_bit_pos_t) 0U)
/** @brief Option-byte loading error (`FLASH_OBR.OPTERR`) bit mask @def FLASH_OBR_OPTERR_Msk */
#define FLASH_OBR_OPTERR_Msk					REG_BIT_MASK(FLASH_OBR_OPTERR_Pos)
/** @brief Option-byte loading error (`FLASH_OBR.OPTERR`) bit mask alias @def FLASH_OBR_OPTERR */
#define FLASH_OBR_OPTERR						FLASH_OBR_OPTERR_Msk

/** @brief Read-protection state (`FLASH_OBR.RDPRT`) bit position @def FLASH_OBR_RDPRT_Pos */
#define FLASH_OBR_RDPRT_Pos					((reg_bit_pos_t) 1U)
/** @brief Read-protection state (`FLASH_OBR.RDPRT`) bit mask @def FLASH_OBR_RDPRT_Msk */
#define FLASH_OBR_RDPRT_Msk					REG_BIT_MASK(FLASH_OBR_RDPRT_Pos)
/** @brief Read-protection state (`FLASH_OBR.RDPRT`) bit mask alias @def FLASH_OBR_RDPRT */
#define FLASH_OBR_RDPRT						FLASH_OBR_RDPRT_Msk

/** @brief Loaded user option bytes (`FLASH_OBR.USER[2:0]`) field position @def FLASH_OBR_USER_Pos */
#define FLASH_OBR_USER_Pos						((reg_bit_pos_t) 2U)
/** @brief Loaded user option bytes (`FLASH_OBR.USER[2:0]`) field width @def FLASH_OBR_USER_Width */
#define FLASH_OBR_USER_Width					((reg_field_width_t) 3U)
/** @brief Loaded user option bytes (`FLASH_OBR.USER[2:0]`) field mask @def FLASH_OBR_USER_Msk */
#define FLASH_OBR_USER_Msk						REG_FIELD_MASK(FLASH_OBR_USER_Pos, FLASH_OBR_USER_Width)
/** @brief Loaded user option bytes (`FLASH_OBR.USER[2:0]`) field mask alias @def FLASH_OBR_USER */
#define FLASH_OBR_USER							FLASH_OBR_USER_Msk

/** @brief Hardware/software watchdog selection (`FLASH_OBR.IWDG_SW`) bit position @def FLASH_OBR_IWDG_SW_Pos */
#define FLASH_OBR_IWDG_SW_Pos				((reg_bit_pos_t) 2U)
/** @brief Hardware/software watchdog selection (`FLASH_OBR.IWDG_SW`) bit mask @def FLASH_OBR_IWDG_SW_Msk */
#define FLASH_OBR_IWDG_SW_Msk				REG_BIT_MASK(FLASH_OBR_IWDG_SW_Pos)
/** @brief Hardware/software watchdog selection (`FLASH_OBR.IWDG_SW`) bit mask alias @def FLASH_OBR_IWDG_SW */
#define FLASH_OBR_IWDG_SW					FLASH_OBR_IWDG_SW_Msk

/** @brief Reset generation in Stop mode (`FLASH_OBR.nRST_STOP`) bit position @def FLASH_OBR_nRST_STOP_Pos */
#define FLASH_OBR_nRST_STOP_Pos				((reg_bit_pos_t) 3U)
/** @brief Reset generation in Stop mode (`FLASH_OBR.nRST_STOP`) bit mask @def FLASH_OBR_nRST_STOP_Msk */
#define FLASH_OBR_nRST_STOP_Msk				REG_BIT_MASK(FLASH_OBR_nRST_STOP_Pos)
/** @brief Reset generation in Stop mode (`FLASH_OBR.nRST_STOP`) bit mask alias @def FLASH_OBR_nRST_STOP */
#define FLASH_OBR_nRST_STOP					FLASH_OBR_nRST_STOP_Msk

/** @brief Reset generation in Standby mode (`FLASH_OBR.nRST_STDBY`) bit position @def FLASH_OBR_nRST_STDBY_Pos */
#define FLASH_OBR_nRST_STDBY_Pos			((reg_bit_pos_t) 4U)
/** @brief Reset generation in Standby mode (`FLASH_OBR.nRST_STDBY`) bit mask @def FLASH_OBR_nRST_STDBY_Msk */
#define FLASH_OBR_nRST_STDBY_Msk			REG_BIT_MASK(FLASH_OBR_nRST_STDBY_Pos)
/** @brief Reset generation in Standby mode (`FLASH_OBR.nRST_STDBY`) bit mask alias @def FLASH_OBR_nRST_STDBY */
#define FLASH_OBR_nRST_STDBY				FLASH_OBR_nRST_STDBY_Msk

/** @brief Loaded user data byte 0 (`FLASH_OBR.DATA0[7:0]`) field position @def FLASH_OBR_DATA0_Pos */
#define FLASH_OBR_DATA0_Pos					((reg_bit_pos_t) 10U)
/** @brief Loaded user data byte 0 (`FLASH_OBR.DATA0[7:0]`) field width @def FLASH_OBR_DATA0_Width */
#define FLASH_OBR_DATA0_Width				((reg_field_width_t) 8U)
/** @brief Loaded user data byte 0 (`FLASH_OBR.DATA0[7:0]`) field mask @def FLASH_OBR_DATA0_Msk */
#define FLASH_OBR_DATA0_Msk					REG_FIELD_MASK(FLASH_OBR_DATA0_Pos, FLASH_OBR_DATA0_Width)
/** @brief Loaded user data byte 0 (`FLASH_OBR.DATA0[7:0]`) field mask alias @def FLASH_OBR_DATA0 */
#define FLASH_OBR_DATA0						FLASH_OBR_DATA0_Msk

/** @brief Loaded user data byte 1 (`FLASH_OBR.DATA1[7:0]`) field position @def FLASH_OBR_DATA1_Pos */
#define FLASH_OBR_DATA1_Pos					((reg_bit_pos_t) 18U)
/** @brief Loaded user data byte 1 (`FLASH_OBR.DATA1[7:0]`) field width @def FLASH_OBR_DATA1_Width */
#define FLASH_OBR_DATA1_Width				((reg_field_width_t) 8U)
/** @brief Loaded user data byte 1 (`FLASH_OBR.DATA1[7:0]`) field mask @def FLASH_OBR_DATA1_Msk */
#define FLASH_OBR_DATA1_Msk					REG_FIELD_MASK(FLASH_OBR_DATA1_Pos, FLASH_OBR_DATA1_Width)
/** @brief Loaded user data byte 1 (`FLASH_OBR.DATA1[7:0]`) field mask alias @def FLASH_OBR_DATA1 */
#define FLASH_OBR_DATA1						FLASH_OBR_DATA1_Msk

// ---------------------------------------------------------------------------------------------------- //
//											FLASH_WRPR										//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Loaded write-protection state (`FLASH_WRPR.WRP[31:0]`) field position @def FLASH_WRPR_WRP_Pos */
#define FLASH_WRPR_WRP_Pos					((reg_bit_pos_t) 0U)
/** @brief Loaded write-protection state (`FLASH_WRPR.WRP[31:0]`) field width @def FLASH_WRPR_WRP_Width */
#define FLASH_WRPR_WRP_Width					((reg_field_width_t) 32U)
/** @brief Loaded write-protection state (`FLASH_WRPR.WRP[31:0]`) field mask @def FLASH_WRPR_WRP_Msk */
#define FLASH_WRPR_WRP_Msk					((reg) 0xFFFFFFFFUL)
/** @brief Loaded write-protection state (`FLASH_WRPR.WRP[31:0]`) field mask alias @def FLASH_WRPR_WRP */
#define FLASH_WRPR_WRP						FLASH_WRPR_WRP_Msk

// ---------------------------------------------------------------------------------------------------- //
//									Flash Option-Byte Storage									//
// ---------------------------------------------------------------------------------------------------- //

/** @brief Read-protection option byte field position in its 32-bit storage word @def FLASH_RDP_RDP_Pos */
#define FLASH_RDP_RDP_Pos						((reg_bit_pos_t) 0U)
/** @brief Read-protection option byte field width @def FLASH_RDP_RDP_Width */
#define FLASH_RDP_RDP_Width					((reg_field_width_t) 8U)
/** @brief Read-protection option byte field mask @def FLASH_RDP_RDP_Msk */
#define FLASH_RDP_RDP_Msk						REG_FIELD_MASK(FLASH_RDP_RDP_Pos, FLASH_RDP_RDP_Width)
/** @brief Read-protection option byte field mask alias @def FLASH_RDP_RDP */
#define FLASH_RDP_RDP							FLASH_RDP_RDP_Msk
/** @brief Complemented read-protection option byte field position @def FLASH_RDP_nRDP_Pos */
#define FLASH_RDP_nRDP_Pos					((reg_bit_pos_t) 8U)
/** @brief Complemented read-protection option byte field width @def FLASH_RDP_nRDP_Width */
#define FLASH_RDP_nRDP_Width					((reg_field_width_t) 8U)
/** @brief Complemented read-protection option byte field mask @def FLASH_RDP_nRDP_Msk */
#define FLASH_RDP_nRDP_Msk					REG_FIELD_MASK(FLASH_RDP_nRDP_Pos, FLASH_RDP_nRDP_Width)
/** @brief Complemented read-protection option byte field mask alias @def FLASH_RDP_nRDP */
#define FLASH_RDP_nRDP						FLASH_RDP_nRDP_Msk

/** @brief User option byte field position in its 32-bit storage word @def FLASH_USER_USER_Pos */
#define FLASH_USER_USER_Pos					((reg_bit_pos_t) 16U)
/** @brief User option byte field width @def FLASH_USER_USER_Width */
#define FLASH_USER_USER_Width				((reg_field_width_t) 8U)
/** @brief User option byte field mask @def FLASH_USER_USER_Msk */
#define FLASH_USER_USER_Msk					REG_FIELD_MASK(FLASH_USER_USER_Pos, FLASH_USER_USER_Width)
/** @brief User option byte field mask alias @def FLASH_USER_USER */
#define FLASH_USER_USER						FLASH_USER_USER_Msk
/** @brief Complemented user option byte field position @def FLASH_USER_nUSER_Pos */
#define FLASH_USER_nUSER_Pos				((reg_bit_pos_t) 24U)
/** @brief Complemented user option byte field width @def FLASH_USER_nUSER_Width */
#define FLASH_USER_nUSER_Width				((reg_field_width_t) 8U)
/** @brief Complemented user option byte field mask @def FLASH_USER_nUSER_Msk */
#define FLASH_USER_nUSER_Msk				REG_FIELD_MASK(FLASH_USER_nUSER_Pos, FLASH_USER_nUSER_Width)
/** @brief Complemented user option byte field mask alias @def FLASH_USER_nUSER */
#define FLASH_USER_nUSER					FLASH_USER_nUSER_Msk

/** @brief User data option byte 0 field position in its 32-bit storage word @def FLASH_DATA0_DATA0_Pos */
#define FLASH_DATA0_DATA0_Pos				((reg_bit_pos_t) 0U)
/** @brief User data option byte 0 field width @def FLASH_DATA0_DATA0_Width */
#define FLASH_DATA0_DATA0_Width				((reg_field_width_t) 8U)
/** @brief User data option byte 0 field mask @def FLASH_DATA0_DATA0_Msk */
#define FLASH_DATA0_DATA0_Msk				REG_FIELD_MASK(FLASH_DATA0_DATA0_Pos, FLASH_DATA0_DATA0_Width)
/** @brief User data option byte 0 field mask alias @def FLASH_DATA0_DATA0 */
#define FLASH_DATA0_DATA0					FLASH_DATA0_DATA0_Msk
/** @brief Complemented user data option byte 0 field position @def FLASH_DATA0_nDATA0_Pos */
#define FLASH_DATA0_nDATA0_Pos				((reg_bit_pos_t) 8U)
/** @brief Complemented user data option byte 0 field width @def FLASH_DATA0_nDATA0_Width */
#define FLASH_DATA0_nDATA0_Width			((reg_field_width_t) 8U)
/** @brief Complemented user data option byte 0 field mask @def FLASH_DATA0_nDATA0_Msk */
#define FLASH_DATA0_nDATA0_Msk				REG_FIELD_MASK(FLASH_DATA0_nDATA0_Pos, FLASH_DATA0_nDATA0_Width)
/** @brief Complemented user data option byte 0 field mask alias @def FLASH_DATA0_nDATA0 */
#define FLASH_DATA0_nDATA0					FLASH_DATA0_nDATA0_Msk

/** @brief User data option byte 1 field position in its 32-bit storage word @def FLASH_DATA1_DATA1_Pos */
#define FLASH_DATA1_DATA1_Pos				((reg_bit_pos_t) 16U)
/** @brief User data option byte 1 field width @def FLASH_DATA1_DATA1_Width */
#define FLASH_DATA1_DATA1_Width				((reg_field_width_t) 8U)
/** @brief User data option byte 1 field mask @def FLASH_DATA1_DATA1_Msk */
#define FLASH_DATA1_DATA1_Msk				REG_FIELD_MASK(FLASH_DATA1_DATA1_Pos, FLASH_DATA1_DATA1_Width)
/** @brief User data option byte 1 field mask alias @def FLASH_DATA1_DATA1 */
#define FLASH_DATA1_DATA1					FLASH_DATA1_DATA1_Msk
/** @brief Complemented user data option byte 1 field position @def FLASH_DATA1_nDATA1_Pos */
#define FLASH_DATA1_nDATA1_Pos				((reg_bit_pos_t) 24U)
/** @brief Complemented user data option byte 1 field width @def FLASH_DATA1_nDATA1_Width */
#define FLASH_DATA1_nDATA1_Width			((reg_field_width_t) 8U)
/** @brief Complemented user data option byte 1 field mask @def FLASH_DATA1_nDATA1_Msk */
#define FLASH_DATA1_nDATA1_Msk				REG_FIELD_MASK(FLASH_DATA1_nDATA1_Pos, FLASH_DATA1_nDATA1_Width)
/** @brief Complemented user data option byte 1 field mask alias @def FLASH_DATA1_nDATA1 */
#define FLASH_DATA1_nDATA1					FLASH_DATA1_nDATA1_Msk

/** @brief Write-protection option byte 0 field position in its 32-bit storage word @def FLASH_WRP0_WRP0_Pos */
#define FLASH_WRP0_WRP0_Pos					((reg_bit_pos_t) 0U)
/** @brief Write-protection option byte 0 field width @def FLASH_WRP0_WRP0_Width */
#define FLASH_WRP0_WRP0_Width				((reg_field_width_t) 8U)
/** @brief Write-protection option byte 0 field mask @def FLASH_WRP0_WRP0_Msk */
#define FLASH_WRP0_WRP0_Msk					REG_FIELD_MASK(FLASH_WRP0_WRP0_Pos, FLASH_WRP0_WRP0_Width)
/** @brief Write-protection option byte 0 field mask alias @def FLASH_WRP0_WRP0 */
#define FLASH_WRP0_WRP0						FLASH_WRP0_WRP0_Msk
/** @brief Complemented write-protection option byte 0 field position @def FLASH_WRP0_nWRP0_Pos */
#define FLASH_WRP0_nWRP0_Pos				((reg_bit_pos_t) 8U)
/** @brief Complemented write-protection option byte 0 field width @def FLASH_WRP0_nWRP0_Width */
#define FLASH_WRP0_nWRP0_Width				((reg_field_width_t) 8U)
/** @brief Complemented write-protection option byte 0 field mask @def FLASH_WRP0_nWRP0_Msk */
#define FLASH_WRP0_nWRP0_Msk				REG_FIELD_MASK(FLASH_WRP0_nWRP0_Pos, FLASH_WRP0_nWRP0_Width)
/** @brief Complemented write-protection option byte 0 field mask alias @def FLASH_WRP0_nWRP0 */
#define FLASH_WRP0_nWRP0					FLASH_WRP0_nWRP0_Msk

/** @brief Write-protection option byte 1 field position in its 32-bit storage word @def FLASH_WRP1_WRP1_Pos */
#define FLASH_WRP1_WRP1_Pos					((reg_bit_pos_t) 16U)
/** @brief Write-protection option byte 1 field width @def FLASH_WRP1_WRP1_Width */
#define FLASH_WRP1_WRP1_Width				((reg_field_width_t) 8U)
/** @brief Write-protection option byte 1 field mask @def FLASH_WRP1_WRP1_Msk */
#define FLASH_WRP1_WRP1_Msk					REG_FIELD_MASK(FLASH_WRP1_WRP1_Pos, FLASH_WRP1_WRP1_Width)
/** @brief Write-protection option byte 1 field mask alias @def FLASH_WRP1_WRP1 */
#define FLASH_WRP1_WRP1						FLASH_WRP1_WRP1_Msk
/** @brief Complemented write-protection option byte 1 field position @def FLASH_WRP1_nWRP1_Pos */
#define FLASH_WRP1_nWRP1_Pos				((reg_bit_pos_t) 24U)
/** @brief Complemented write-protection option byte 1 field width @def FLASH_WRP1_nWRP1_Width */
#define FLASH_WRP1_nWRP1_Width				((reg_field_width_t) 8U)
/** @brief Complemented write-protection option byte 1 field mask @def FLASH_WRP1_nWRP1_Msk */
#define FLASH_WRP1_nWRP1_Msk				REG_FIELD_MASK(FLASH_WRP1_nWRP1_Pos, FLASH_WRP1_nWRP1_Width)
/** @brief Complemented write-protection option byte 1 field mask alias @def FLASH_WRP1_nWRP1 */
#define FLASH_WRP1_nWRP1					FLASH_WRP1_nWRP1_Msk

/** @brief Write-protection option byte 2 field position in its 32-bit storage word @def FLASH_WRP2_WRP2_Pos */
#define FLASH_WRP2_WRP2_Pos					((reg_bit_pos_t) 0U)
/** @brief Write-protection option byte 2 field width @def FLASH_WRP2_WRP2_Width */
#define FLASH_WRP2_WRP2_Width				((reg_field_width_t) 8U)
/** @brief Write-protection option byte 2 field mask @def FLASH_WRP2_WRP2_Msk */
#define FLASH_WRP2_WRP2_Msk					REG_FIELD_MASK(FLASH_WRP2_WRP2_Pos, FLASH_WRP2_WRP2_Width)
/** @brief Write-protection option byte 2 field mask alias @def FLASH_WRP2_WRP2 */
#define FLASH_WRP2_WRP2						FLASH_WRP2_WRP2_Msk
/** @brief Complemented write-protection option byte 2 field position @def FLASH_WRP2_nWRP2_Pos */
#define FLASH_WRP2_nWRP2_Pos				((reg_bit_pos_t) 8U)
/** @brief Complemented write-protection option byte 2 field width @def FLASH_WRP2_nWRP2_Width */
#define FLASH_WRP2_nWRP2_Width				((reg_field_width_t) 8U)
/** @brief Complemented write-protection option byte 2 field mask @def FLASH_WRP2_nWRP2_Msk */
#define FLASH_WRP2_nWRP2_Msk				REG_FIELD_MASK(FLASH_WRP2_nWRP2_Pos, FLASH_WRP2_nWRP2_Width)
/** @brief Complemented write-protection option byte 2 field mask alias @def FLASH_WRP2_nWRP2 */
#define FLASH_WRP2_nWRP2					FLASH_WRP2_nWRP2_Msk

/** @brief Write-protection option byte 3 field position in its 32-bit storage word @def FLASH_WRP3_WRP3_Pos */
#define FLASH_WRP3_WRP3_Pos					((reg_bit_pos_t) 16U)
/** @brief Write-protection option byte 3 field width @def FLASH_WRP3_WRP3_Width */
#define FLASH_WRP3_WRP3_Width				((reg_field_width_t) 8U)
/** @brief Write-protection option byte 3 field mask @def FLASH_WRP3_WRP3_Msk */
#define FLASH_WRP3_WRP3_Msk					REG_FIELD_MASK(FLASH_WRP3_WRP3_Pos, FLASH_WRP3_WRP3_Width)
/** @brief Write-protection option byte 3 field mask alias @def FLASH_WRP3_WRP3 */
#define FLASH_WRP3_WRP3						FLASH_WRP3_WRP3_Msk
/** @brief Complemented write-protection option byte 3 field position @def FLASH_WRP3_nWRP3_Pos */
#define FLASH_WRP3_nWRP3_Pos				((reg_bit_pos_t) 24U)
/** @brief Complemented write-protection option byte 3 field width @def FLASH_WRP3_nWRP3_Width */
#define FLASH_WRP3_nWRP3_Width				((reg_field_width_t) 8U)
/** @brief Complemented write-protection option byte 3 field mask @def FLASH_WRP3_nWRP3_Msk */
#define FLASH_WRP3_nWRP3_Msk				REG_FIELD_MASK(FLASH_WRP3_nWRP3_Pos, FLASH_WRP3_nWRP3_Width)
/** @brief Complemented write-protection option byte 3 field mask alias @def FLASH_WRP3_nWRP3 */
#define FLASH_WRP3_nWRP3					FLASH_WRP3_nWRP3_Msk

/** @} */ // FLASH_01_RegisterLayer_00_RegisterDefines

// ==================================================================================================== //
//										Flash Register Map										//
// ==================================================================================================== //

/**
 * @defgroup FLASH_01_RegisterLayer_01_RegisterMap Flash Register Block Map
 * @ingroup FLASH_01_RegisterLayer
 * @brief Memory-mapped Flash interface register block and practical register layout
 * @details
 * @ref FLASH_TypeDef is the raw peripheral view consumed by register-near
 * code. Full-register `.REG` members support image-based operations while
 * `.BIT` members expose named hardware fields for direct inspection.
 * Reserved words are retained so every later member remains at its hardware
 * offset.
 * @{
 */

/**
 * @brief Flash memory interface register block structure
 * @details
 * Complete STM32F103C8T6 Flash interface register map at @ref FLASH_BASE_ADDR.
 * The separately mapped option-byte storage is intentionally excluded from
 * this peripheral structure.
 * @see RM0008 Section 3.5 Flash registers
 * @struct FLASH_TypeDef
 */
typedef struct FLASH_TypeDef
{
	/**
	 * @section FLASH_TypeDef_ACR Flash Access Control Register (ACR)
	 * @brief [R/W and R] Flash read timing and prefetch configuration/status
	 * @details
	 * `LATENCY`, `HLFCYA`, and `PRFTBE` are configuration state. `PRFTBS` is a
	 * read-only observation of the active prefetch-buffer state.
	 */
	union
	{
		/** @brief Full 32-bit `FLASH_ACR` register image */
		_IO REG;
		/** @brief Named `FLASH_ACR` bitfield view */
		struct
		{
			_IO LATENCY : 3;		/**< Flash read latency */
			_IO HLFCYA : 1;		/**< Flash half-cycle access enable */
			_IO PRFTBE : 1;		/**< Prefetch buffer enable */
			_I PRFTBS : 1;			/**< Prefetch buffer status */
			_I reserved_1 : 26;	/**< Reserved */
		} BIT;
	} ACR;

	/**
	 * @section FLASH_TypeDef_KEYR Flash Key Register (KEYR)
	 * @brief [W] Main Flash program/erase unlock key port
	 * @details
	 * This register is a keyed action port, not persistent configuration state.
	 * Writing @ref `FLASH_KEY1` followed by @ref `FLASH_KEY2` unlocks main Flash
	 * program/erase control when `FLASH_CR.LOCK` is set.
	 */
	union
	{
		/** @brief Full 32-bit `FLASH_KEYR` write image */
		_O REG;
		/** @brief Named `FLASH_KEYR` bitfield view */
		struct
		{
			_O FKEYR : 32;	/**< Main Flash unlock key payload */
		} BIT;
	} KEYR;

	/**
	 * @section FLASH_TypeDef_OPTKEYR Flash Option Key Register (OPTKEYR)
	 * @brief [W] Option-byte programming unlock key port
	 * @details
	 * This register is a keyed action port. Writing @ref `FLASH_OPTKEY1`
	 * followed by @ref `FLASH_OPTKEY2` enables option-byte write control after
	 * the main Flash interface has been unlocked.
	 */
	union
	{
		/** @brief Full 32-bit `FLASH_OPTKEYR` write image */
		_O REG;
		/** @brief Named `FLASH_OPTKEYR` bitfield view */
		struct
		{
			_O OPTKEYR : 32;	/**< Option-byte unlock key payload */
		} BIT;
	} OPTKEYR;

	/**
	 * @section FLASH_TypeDef_SR Flash Status Register (SR)
	 * @brief [R and W1C] Flash operation state, error events, and completion event
	 * @details
	 * `BSY` is read-only operation state. `PGERR`, `WRPRTERR`, and `EOP` are
	 * latched events cleared by writing `1` to the corresponding bit; a generic
	 * read-modify-write clear must not be used for these W1C fields.
	 */
	union
	{
		/** @brief Full 32-bit `FLASH_SR` status and W1C event image */
		_IO REG;
		/** @brief Named `FLASH_SR` bitfield view */
		struct
		{
			_I BSY : 1;			/**< Flash operation busy */
			_I reserved_1 : 1;	/**< Reserved */
			_IO PGERR : 1;		/**< Programming error event; write one to clear */
			_I reserved_2 : 1;	/**< Reserved */
			_IO WRPRTERR : 1;	/**< Write-protection error event; write one to clear */
			_IO EOP : 1;			/**< End-of-operation event; write one to clear */
			_I reserved_3 : 26;	/**< Reserved */
		} BIT;
	} SR;

	/**
	 * @section FLASH_TypeDef_CR Flash Control Register (CR)
	 * @brief [R/W] Flash program/erase mode, start action, locking, and interrupt-source control
	 * @details
	 * This register selects one program/erase operation, starts erase actions,
	 * locks the main Flash interface, exposes option-byte write enable state,
	 * and gates Flash error/end-of-operation interrupt requests.
	 */
	union
	{
		/** @brief Full 32-bit `FLASH_CR` register image */
		_IO REG;
		/** @brief Named `FLASH_CR` bitfield view */
		struct
		{
			_IO PG : 1;			/**< Flash programming enable */
			_IO PER : 1;			/**< Page erase enable */
			_IO MER : 1;			/**< Mass erase enable */
			_IO reserved_1 : 1;	/**< Reserved */
			_IO OPTPG : 1;		/**< Option-byte programming enable */
			_IO OPTER : 1;		/**< Option-byte erase enable */
			_IO STRT : 1;			/**< Erase operation start action */
			_IO LOCK : 1;			/**< Main Flash program/erase lock */
			_IO reserved_2 : 1;	/**< Reserved */
			_IO OPTWRE : 1;		/**< Option-byte write enable state */
			_IO ERRIE : 1;		/**< Flash error interrupt enable */
			_IO reserved_3 : 1;	/**< Reserved */
			_IO EOPIE : 1;		/**< End-of-operation interrupt enable */
			_IO reserved_4 : 19;	/**< Reserved */
		} BIT;
	} CR;

	/**
	 * @section FLASH_TypeDef_AR Flash Address Register (AR)
	 * @brief [R/W] Page erase target address
	 * @details
	 * `FLASH_AR` receives the start address of the Flash page selected for a
	 * page erase operation before `FLASH_CR.STRT` is asserted.
	 */
	union
	{
		/** @brief Full 32-bit `FLASH_AR` register image */
		_IO REG;
		/** @brief Named `FLASH_AR` bitfield view */
		struct
		{
			_IO FAR : 32;	/**< Page erase target address */
		} BIT;
	} AR;

	/** @brief Reserved word at offset `0x18` */
	_IO RESERVED;

	/**
	 * @section FLASH_TypeDef_OBR Flash Option Byte Register (OBR)
	 * @brief [R] Option-byte loading status and loaded option-byte values
	 * @details
	 * `FLASH_OBR` reports option-byte load validity, read-protection state,
	 * user policy, and the two loaded user-data bytes. It is an observation of
	 * option-byte state, not the option-byte programming storage itself.
	 */
	union
	{
		/** @brief Full 32-bit `FLASH_OBR` register image */
		_I REG;
		/** @brief Named `FLASH_OBR` bitfield view */
		struct
		{
			_I OPTERR : 1;		/**< Option-byte loading error */
			_I RDPRT : 1;		/**< Read-protection state */
			_I USER : 3;			/**< Loaded user option bytes */
			_I reserved_1 : 5;	/**< Reserved */
			_I DATA0 : 8;		/**< Loaded user data byte 0 */
			_I DATA1 : 8;		/**< Loaded user data byte 1 */
			_I reserved_2 : 6;	/**< Reserved */
		} BIT;
	} OBR;

	/**
	 * @section FLASH_TypeDef_WRPR Flash Write Protection Register (WRPR)
	 * @brief [R] Loaded Flash write-protection state
	 * @details
	 * Each cleared `WRP` bit reports that the corresponding Flash page group is
	 * write-protected by the loaded option-byte configuration.
	 */
	union
	{
		/** @brief Full 32-bit `FLASH_WRPR` register image */
		_I REG;
		/** @brief Named `FLASH_WRPR` bitfield view */
		struct
		{
			_I WRP : 32;	/**< Loaded write-protection state */
		} BIT;
	} WRPR;
} FLASH_TypeDef;

/** @} */ // FLASH_01_RegisterLayer_01_RegisterMap

/** @} */ // FLASH_01_RegisterLayer

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_FLASH_H_ */
