/**
 * @file stm32f1xx_gpio.h
 * @author Shrey Shah
 * @brief STM32F1 GPIO Register-Layer Definitions
 * @version v1.2
 * @date 28-03-2026
 */
#ifndef STM32F1XX_GPIO_H_
#define STM32F1XX_GPIO_H_

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------
#include "stm32f1xx_utils.h"

/**
 * @defgroup GPIO General Purpose Input/Output (GPIO)
 * @brief STM32F1 digital I/O configuration, data, atomic set/reset, and lock infrastructure
 * @details
 * RM0008 Section 9 describes GPIO as the hardware block that:
 * - configures each pin through CRL and CRH MODE/CNF fields,
 * - samples input state through IDR,
 * - drives output state through ODR,
 * - performs atomic output transitions through BSRR and BRR,
 * - locks pin configuration through LCKR.
 *
 * @section GPIO_RegisterLayoutBrief Register Layout Brief
 * <table>
 * <tr><th>Register</th><th>Offset</th><th>Primary Practical Role</th></tr>
 * <tr><td><code>GPIOx_CRL</code></td><td><code>0x00</code></td><td>MODE/CNF control for pins 0-7</td></tr>
 * <tr><td><code>GPIOx_CRH</code></td><td><code>0x04</code></td><td>MODE/CNF control for pins 8-15</td></tr>
 * <tr><td><code>GPIOx_IDR</code></td><td><code>0x08</code></td><td>Input sampling for all 16 pins</td></tr>
 * <tr><td><code>GPIOx_ODR</code></td><td><code>0x0C</code></td><td>Latched output state for all 16 pins</td></tr>
 * <tr><td><code>GPIOx_BSRR</code></td><td><code>0x10</code></td><td>Atomic set/reset write path</td></tr>
 * <tr><td><code>GPIOx_BRR</code></td><td><code>0x14</code></td><td>Legacy reset-only write path</td></tr>
 * <tr><td><code>GPIOx_LCKR</code></td><td><code>0x18</code></td><td>Configuration lock handshake and status</td></tr>
 * </table>
 *
 * This codebase documents GPIO in three software layers in execution order:
 * - Register layer: @ref `stm32f1xx_gpio.h`
 * - Low-level control layer: @ref `gpio_ll.h`
 * - Driver/orchestration layer: @ref `gpio.h`
 */

/**
 * @defgroup GPIO_01_RegisterLayer GPIO Register Layer
 * @ingroup GPIO
 * @brief Raw GPIO register structures, field encodings, and device-level constants
 * @details
 * This layer mirrors the hardware-visible GPIO chapter from the reference manual.
 * It is intentionally close to the register map so the LL layer can program the
 * hardware without re-describing MODE/CNF bit positions, data bits, or lock bits.
 */

/**
 * @defgroup GPIO_02_LL GPIO Low-Level Control Layer
 * @ingroup GPIO
 * @brief Register-near GPIO control interface used by the driver layer
 * @details
 * This layer converts raw GPIO register definitions into typed operations that directly
 * express hardware actions such as CRL/CRH staging, IDR sampling, ODR programming,
 * atomic BSRR transitions, and LCKR lock sequencing.
 */

/**
 * @defgroup GPIO_03_Driver GPIO Driver Layer
 * @ingroup GPIO
 * @brief Validated GPIO orchestration layer built on top of `gpio_ll.h`
 * @details
 * This layer turns public pin configuration requests into validated GPIO state changes.
 * It owns selector vocabulary, compatibility checks, configuration planning, and
 * public runtime query APIs.
 */

/**
 * @addtogroup GPIO_01_RegisterLayer
 * @{
 */

/**
 * @brief GPIO register-block spacing constant
 * @def GPIO_PERIPHERAL_SIZE
 * @details
 * Each GPIO instance occupies a fixed 1 KiB address window in the APB2 memory map
 * even though the visible register block is smaller. This constant is used when
 * deriving instance-relative positions from the memory map.
 */
#define GPIO_PERIPHERAL_SIZE					((uint32_t) 0x400UL)

// ------------------------------------------------------------------------------------------
// GPIO_CRL (Port Configuration Register Low)
// ------------------------------------------------------------------------------------------

/**
 * @brief GPIO Low-Port Configuration Register Definitions
 * @defgroup GPIO_01_RegisterLayer_01_PortConfigLow GPIO Port Configuration Register Low
 * @ingroup GPIO_01_RegisterLayer
 * @details
 * @section GPIO_CRL_Theory Theory and Practical Role
 * This page documents `GPIOx_CRL`, which configures the practical electrical
 * behavior of pins 0-7. Each pin owns one 4-bit slot where `MODE` selects input
 * versus output speed and `CNF` selects the raw input/output topology.
 *
 * @section GPIO_CRL_Macros Register-Specific Macros
 * The macro definitions below expose the raw bit positions, masks, and
 * convenience aliases used by the LL layer when it needs direct symbolic access
 * to `GPIOx_CRL`.
 *
 * @section GPIO_CRL_Union Register Union View
 * The `union GPIO_CRL` view inside @ref GPIO_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ MODE (Port Mode Bits for Pins 0-7) ------ // 
/** @brief GPIO_CRL_MODE Position @def GPIO_CRL_MODE_Pos */
#define GPIO_CRL_MODE_Pos			(0U)
/** @brief GPIO_CRL_MODE Mask @def GPIO_CRL_MODE_Msk */
#define GPIO_CRL_MODE_Msk			(BIT_VALUE(0x33333333UL, GPIO_CRL_MODE_Pos))
/** @brief Port Mode Bits @def GPIO_CRL_MODE */
#define GPIO_CRL_MODE				GPIO_CRL_MODE_Msk

/** @brief GPIO_CRL_MODE0 Position @def GPIO_CRL_MODE0_Pos */
#define GPIO_CRL_MODE0_Pos			(0U)
/** @brief GPIO_CRL_MODE0 Mask @def GPIO_CRL_MODE0_Msk */
#define GPIO_CRL_MODE0_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_MODE0_Pos))
/** @brief MODE0 @def GPIO_CRL_MODE0 */
#define GPIO_CRL_MODE0				GPIO_CRL_MODE0_Msk
/** @brief MODE0 0 @def GPIO_CRL_MODE0_0 */
#define GPIO_CRL_MODE0_0			(BIT_VALUE(0x1UL, GPIO_CRL_MODE0_Pos))
/** @brief MODE0 1 @def GPIO_CRL_MODE0_1 */
#define GPIO_CRL_MODE0_1			(BIT_VALUE(0x2UL, GPIO_CRL_MODE0_Pos))

/** @brief GPIO_CRL_MODE1 Position @def GPIO_CRL_MODE1_Pos */
#define GPIO_CRL_MODE1_Pos			(4U)
/** @brief GPIO_CRL_MODE1 Mask @def GPIO_CRL_MODE1_Msk */
#define GPIO_CRL_MODE1_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_MODE1_Pos))
/** @brief MODE1 @def GPIO_CRL_MODE1 */
#define GPIO_CRL_MODE1				GPIO_CRL_MODE1_Msk
/** @brief MODE1 0 @def GPIO_CRL_MODE1_0 */
#define GPIO_CRL_MODE1_0			(BIT_VALUE(0x1UL, GPIO_CRL_MODE1_Pos))
/** @brief MODE1 1 @def GPIO_CRL_MODE1_1 */
#define GPIO_CRL_MODE1_1			(BIT_VALUE(0x2UL, GPIO_CRL_MODE1_Pos))

/** @brief GPIO_CRL_MODE2 Position @def GPIO_CRL_MODE2_Pos */
#define GPIO_CRL_MODE2_Pos			(8U)
/** @brief GPIO_CRL_MODE2 Mask @def GPIO_CRL_MODE2_Msk */
#define GPIO_CRL_MODE2_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_MODE2_Pos))
/** @brief MODE2 @def GPIO_CRL_MODE2 */
#define GPIO_CRL_MODE2				GPIO_CRL_MODE2_Msk
/** @brief MODE2 0 @def GPIO_CRL_MODE2_0 */
#define GPIO_CRL_MODE2_0			(BIT_VALUE(0x1UL, GPIO_CRL_MODE2_Pos))
/** @brief MODE2 1 @def GPIO_CRL_MODE2_1 */
#define GPIO_CRL_MODE2_1			(BIT_VALUE(0x2UL, GPIO_CRL_MODE2_Pos))

/** @brief GPIO_CRL_MODE3 Position @def GPIO_CRL_MODE3_Pos */
#define GPIO_CRL_MODE3_Pos			(12U)
/** @brief GPIO_CRL_MODE3 Mask @def GPIO_CRL_MODE3_Msk */
#define GPIO_CRL_MODE3_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_MODE3_Pos))
/** @brief MODE3 @def GPIO_CRL_MODE3 */
#define GPIO_CRL_MODE3				GPIO_CRL_MODE3_Msk
/** @brief MODE3 0 @def GPIO_CRL_MODE3_0 */
#define GPIO_CRL_MODE3_0			(BIT_VALUE(0x1UL, GPIO_CRL_MODE3_Pos))
/** @brief MODE3 1 @def GPIO_CRL_MODE3_1 */
#define GPIO_CRL_MODE3_1			(BIT_VALUE(0x2UL, GPIO_CRL_MODE3_Pos))

/** @brief GPIO_CRL_MODE4 Position @def GPIO_CRL_MODE4_Pos */
#define GPIO_CRL_MODE4_Pos			(16U)
/** @brief GPIO_CRL_MODE4 Mask @def GPIO_CRL_MODE4_Msk */
#define GPIO_CRL_MODE4_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_MODE4_Pos))
/** @brief MODE4 @def GPIO_CRL_MODE4 */
#define GPIO_CRL_MODE4				GPIO_CRL_MODE4_Msk
/** @brief MODE4 0 @def GPIO_CRL_MODE4_0 */
#define GPIO_CRL_MODE4_0			(BIT_VALUE(0x1UL, GPIO_CRL_MODE4_Pos))
/** @brief MODE4 1 @def GPIO_CRL_MODE4_1 */
#define GPIO_CRL_MODE4_1			(BIT_VALUE(0x2UL, GPIO_CRL_MODE4_Pos))

/** @brief GPIO_CRL_MODE5 Position @def GPIO_CRL_MODE5_Pos */
#define GPIO_CRL_MODE5_Pos			(20U)
/** @brief GPIO_CRL_MODE5 Mask @def GPIO_CRL_MODE5_Msk */
#define GPIO_CRL_MODE5_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_MODE5_Pos))
/** @brief MODE5 @def GPIO_CRL_MODE5 */
#define GPIO_CRL_MODE5				GPIO_CRL_MODE5_Msk
/** @brief MODE5 0 @def GPIO_CRL_MODE5_0 */
#define GPIO_CRL_MODE5_0			(BIT_VALUE(0x1UL, GPIO_CRL_MODE5_Pos))
/** @brief MODE5 1 @def GPIO_CRL_MODE5_1 */
#define GPIO_CRL_MODE5_1			(BIT_VALUE(0x2UL, GPIO_CRL_MODE5_Pos))

/** @brief GPIO_CRL_MODE6 Position @def GPIO_CRL_MODE6_Pos */
#define GPIO_CRL_MODE6_Pos			(24U)
/** @brief GPIO_CRL_MODE6 Mask @def GPIO_CRL_MODE6_Msk */
#define GPIO_CRL_MODE6_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_MODE6_Pos))
/** @brief MODE6 @def GPIO_CRL_MODE6 */
#define GPIO_CRL_MODE6				GPIO_CRL_MODE6_Msk
/** @brief MODE6 0 @def GPIO_CRL_MODE6_0 */
#define GPIO_CRL_MODE6_0			(BIT_VALUE(0x1UL, GPIO_CRL_MODE6_Pos))
/** @brief MODE6 1 @def GPIO_CRL_MODE6_1 */
#define GPIO_CRL_MODE6_1			(BIT_VALUE(0x2UL, GPIO_CRL_MODE6_Pos))

/** @brief GPIO_CRL_MODE7 Position @def GPIO_CRL_MODE7_Pos */
#define GPIO_CRL_MODE7_Pos			(28U)
/** @brief GPIO_CRL_MODE7 Mask @def GPIO_CRL_MODE7_Msk */
#define GPIO_CRL_MODE7_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_MODE7_Pos))
/** @brief MODE7 @def GPIO_CRL_MODE7 */
#define GPIO_CRL_MODE7				GPIO_CRL_MODE7_Msk
/** @brief MODE7 0 @def GPIO_CRL_MODE7_0 */
#define GPIO_CRL_MODE7_0			(BIT_VALUE(0x1UL, GPIO_CRL_MODE7_Pos))
/** @brief MODE7 1 @def GPIO_CRL_MODE7_1 */
#define GPIO_CRL_MODE7_1			(BIT_VALUE(0x2UL, GPIO_CRL_MODE7_Pos))

// ------ CNF (Port Configuration Bits for Pins 0-7) ------ // 
/** @brief GPIO_CRL_CNF Position @def GPIO_CRL_CNF_Pos */
#define GPIO_CRL_CNF_Pos			(2U)
/** @brief GPIO_CRL_CNF Mask @def GPIO_CRL_CNF_Msk */
#define GPIO_CRL_CNF_Msk			(BIT_VALUE(0x33333333UL, GPIO_CRL_CNF_Pos))
/** @brief Port Configuration Bits @def GPIO_CRL_CNF */
#define GPIO_CRL_CNF				GPIO_CRL_CNF_Msk

/** @brief GPIO_CRL_CNF0 Position @def GPIO_CRL_CNF0_Pos */
#define GPIO_CRL_CNF0_Pos			(2U)
/** @brief GPIO_CRL_CNF0 Mask @def GPIO_CRL_CNF0_Msk */
#define GPIO_CRL_CNF0_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_CNF0_Pos))
/** @brief CNF0 @def GPIO_CRL_CNF0 */
#define GPIO_CRL_CNF0				GPIO_CRL_CNF0_Msk
/** @brief CNF0 0 @def GPIO_CRL_CNF0_0 */
#define GPIO_CRL_CNF0_0				(BIT_VALUE(0x1UL, GPIO_CRL_CNF0_Pos))
/** @brief CNF0 1 @def GPIO_CRL_CNF0_1 */
#define GPIO_CRL_CNF0_1				(BIT_VALUE(0x2UL, GPIO_CRL_CNF0_Pos))

/** @brief GPIO_CRL_CNF1 Position @def GPIO_CRL_CNF1_Pos */
#define GPIO_CRL_CNF1_Pos			(6U)
/** @brief GPIO_CRL_CNF1 Mask @def GPIO_CRL_CNF1_Msk */
#define GPIO_CRL_CNF1_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_CNF1_Pos))
/** @brief CNF1 @def GPIO_CRL_CNF1 */
#define GPIO_CRL_CNF1				GPIO_CRL_CNF1_Msk
/** @brief CNF1 0 @def GPIO_CRL_CNF1_0 */
#define GPIO_CRL_CNF1_0				(BIT_VALUE(0x1UL, GPIO_CRL_CNF1_Pos))
/** @brief CNF1 1 @def GPIO_CRL_CNF1_1 */
#define GPIO_CRL_CNF1_1				(BIT_VALUE(0x2UL, GPIO_CRL_CNF1_Pos))

/** @brief GPIO_CRL_CNF2 Position @def GPIO_CRL_CNF2_Pos */
#define GPIO_CRL_CNF2_Pos			(10U)
/** @brief GPIO_CRL_CNF2 Mask @def GPIO_CRL_CNF2_Msk */
#define GPIO_CRL_CNF2_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_CNF2_Pos))
/** @brief CNF2 @def GPIO_CRL_CNF2 */
#define GPIO_CRL_CNF2				GPIO_CRL_CNF2_Msk
/** @brief CNF2 0 @def GPIO_CRL_CNF2_0 */
#define GPIO_CRL_CNF2_0				(BIT_VALUE(0x1UL, GPIO_CRL_CNF2_Pos))
/** @brief CNF2 1 @def GPIO_CRL_CNF2_1 */
#define GPIO_CRL_CNF2_1				(BIT_VALUE(0x2UL, GPIO_CRL_CNF2_Pos))

/** @brief GPIO_CRL_CNF3 Position @def GPIO_CRL_CNF3_Pos */
#define GPIO_CRL_CNF3_Pos			(14U)
/** @brief GPIO_CRL_CNF3 Mask @def GPIO_CRL_CNF3_Msk */
#define GPIO_CRL_CNF3_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_CNF3_Pos))
/** @brief CNF3 @def GPIO_CRL_CNF3 */
#define GPIO_CRL_CNF3				GPIO_CRL_CNF3_Msk
/** @brief CNF3 0 @def GPIO_CRL_CNF3_0 */
#define GPIO_CRL_CNF3_0				(BIT_VALUE(0x1UL, GPIO_CRL_CNF3_Pos))
/** @brief CNF3 1 @def GPIO_CRL_CNF3_1 */
#define GPIO_CRL_CNF3_1				(BIT_VALUE(0x2UL, GPIO_CRL_CNF3_Pos))

/** @brief GPIO_CRL_CNF4 Position @def GPIO_CRL_CNF4_Pos */
#define GPIO_CRL_CNF4_Pos			(18U)
/** @brief GPIO_CRL_CNF4 Mask @def GPIO_CRL_CNF4_Msk */
#define GPIO_CRL_CNF4_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_CNF4_Pos))
/** @brief CNF4 @def GPIO_CRL_CNF4 */
#define GPIO_CRL_CNF4				GPIO_CRL_CNF4_Msk
/** @brief CNF4 0 @def GPIO_CRL_CNF4_0 */
#define GPIO_CRL_CNF4_0				(BIT_VALUE(0x1UL, GPIO_CRL_CNF4_Pos))
/** @brief CNF4 1 @def GPIO_CRL_CNF4_1 */
#define GPIO_CRL_CNF4_1				(BIT_VALUE(0x2UL, GPIO_CRL_CNF4_Pos))

/** @brief GPIO_CRL_CNF5 Position @def GPIO_CRL_CNF5_Pos */
#define GPIO_CRL_CNF5_Pos			(22U)
/** @brief GPIO_CRL_CNF5 Mask @def GPIO_CRL_CNF5_Msk */
#define GPIO_CRL_CNF5_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_CNF5_Pos))
/** @brief CNF5 @def GPIO_CRL_CNF5 */
#define GPIO_CRL_CNF5				GPIO_CRL_CNF5_Msk
/** @brief CNF5 0 @def GPIO_CRL_CNF5_0 */
#define GPIO_CRL_CNF5_0				(BIT_VALUE(0x1UL, GPIO_CRL_CNF5_Pos))
/** @brief CNF5 1 @def GPIO_CRL_CNF5_1 */
#define GPIO_CRL_CNF5_1				(BIT_VALUE(0x2UL, GPIO_CRL_CNF5_Pos))

/** @brief GPIO_CRL_CNF6 Position @def GPIO_CRL_CNF6_Pos */
#define GPIO_CRL_CNF6_Pos			(26U)
/** @brief GPIO_CRL_CNF6 Mask @def GPIO_CRL_CNF6_Msk */
#define GPIO_CRL_CNF6_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_CNF6_Pos))
/** @brief CNF6 @def GPIO_CRL_CNF6 */
#define GPIO_CRL_CNF6				GPIO_CRL_CNF6_Msk
/** @brief CNF6 0 @def GPIO_CRL_CNF6_0 */
#define GPIO_CRL_CNF6_0				(BIT_VALUE(0x1UL, GPIO_CRL_CNF6_Pos))
/** @brief CNF6 1 @def GPIO_CRL_CNF6_1 */
#define GPIO_CRL_CNF6_1				(BIT_VALUE(0x2UL, GPIO_CRL_CNF6_Pos))

/** @brief GPIO_CRL_CNF7 Position @def GPIO_CRL_CNF7_Pos */
#define GPIO_CRL_CNF7_Pos			(30U)
/** @brief GPIO_CRL_CNF7 Mask @def GPIO_CRL_CNF7_Msk */
#define GPIO_CRL_CNF7_Msk			(BIT_VALUE(0x3UL, GPIO_CRL_CNF7_Pos))
/** @brief CNF7 @def GPIO_CRL_CNF7 */
#define GPIO_CRL_CNF7				GPIO_CRL_CNF7_Msk
/** @brief CNF7 0 @def GPIO_CRL_CNF7_0 */
#define GPIO_CRL_CNF7_0				(BIT_VALUE(0x1UL, GPIO_CRL_CNF7_Pos))
/** @brief CNF7 1 @def GPIO_CRL_CNF7_1 */
#define GPIO_CRL_CNF7_1				(BIT_VALUE(0x2UL, GPIO_CRL_CNF7_Pos))

/** @} */ // GPIO_CRL

// ------------------------------------------------------------------------------------------
// GPIO_CRH (Port Configuration Register High)
// ------------------------------------------------------------------------------------------

/**
 * @brief GPIO High-Port Configuration Register Definitions
 * @defgroup GPIO_01_RegisterLayer_02_PortConfigHigh GPIO Port Configuration Register High
 * @ingroup GPIO_01_RegisterLayer
 * @details
 * @section GPIO_CRH_Theory Theory and Practical Role
 * This page documents `GPIOx_CRH`, which configures the practical electrical
 * behavior of pins 8-15. It uses the same 4-bit `MODE`/`CNF` slot layout as
 * `GPIOx_CRL`, but for the upper half of the port.
 *
 * @section GPIO_CRH_Macros Register-Specific Macros
 * The macro definitions below expose the raw bit positions, masks, and
 * convenience aliases used by the LL layer when it needs direct symbolic access
 * to `GPIOx_CRH`.
 *
 * @section GPIO_CRH_Union Register Union View
 * The `union GPIO_CRH` view inside @ref GPIO_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ MODE (Port Mode Bits for Pins 8-15) ------ // 
/** @brief GPIO_CRH_MODE Position @def GPIO_CRH_MODE_Pos */
#define GPIO_CRH_MODE_Pos			(0U)
/** @brief GPIO_CRH_MODE Mask @def GPIO_CRH_MODE_Msk */
#define GPIO_CRH_MODE_Msk			(BIT_VALUE(0x33333333UL, GPIO_CRH_MODE_Pos))
/** @brief Port Mode Bits @def GPIO_CRH_MODE */
#define GPIO_CRH_MODE				GPIO_CRH_MODE_Msk

/** @brief GPIO_CRH_MODE8 Position @def GPIO_CRH_MODE8_Pos */
#define GPIO_CRH_MODE8_Pos			(0U)
/** @brief GPIO_CRH_MODE8 Mask @def GPIO_CRH_MODE8_Msk */
#define GPIO_CRH_MODE8_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_MODE8_Pos))
/** @brief MODE8 @def GPIO_CRH_MODE8 */
#define GPIO_CRH_MODE8				GPIO_CRH_MODE8_Msk
/** @brief MODE8 0 @def GPIO_CRH_MODE8_0 */
#define GPIO_CRH_MODE8_0			(BIT_VALUE(0x1UL, GPIO_CRH_MODE8_Pos))
/** @brief MODE8 1 @def GPIO_CRH_MODE8_1 */
#define GPIO_CRH_MODE8_1			(BIT_VALUE(0x2UL, GPIO_CRH_MODE8_Pos))

/** @brief GPIO_CRH_MODE9 Position @def GPIO_CRH_MODE9_Pos */
#define GPIO_CRH_MODE9_Pos			(4U)
/** @brief GPIO_CRH_MODE9 Mask @def GPIO_CRH_MODE9_Msk */
#define GPIO_CRH_MODE9_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_MODE9_Pos))
/** @brief MODE9 @def GPIO_CRH_MODE9 */
#define GPIO_CRH_MODE9				GPIO_CRH_MODE9_Msk
/** @brief MODE9 0 @def GPIO_CRH_MODE9_0 */
#define GPIO_CRH_MODE9_0			(BIT_VALUE(0x1UL, GPIO_CRH_MODE9_Pos))
/** @brief MODE9 1 @def GPIO_CRH_MODE9_1 */
#define GPIO_CRH_MODE9_1			(BIT_VALUE(0x2UL, GPIO_CRH_MODE9_Pos))

/** @brief GPIO_CRH_MODE10 Position @def GPIO_CRH_MODE10_Pos */
#define GPIO_CRH_MODE10_Pos			(8U)
/** @brief GPIO_CRH_MODE10 Mask @def GPIO_CRH_MODE10_Msk */
#define GPIO_CRH_MODE10_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_MODE10_Pos))
/** @brief MODE10 @def GPIO_CRH_MODE10 */
#define GPIO_CRH_MODE10				GPIO_CRH_MODE10_Msk
/** @brief MODE10 0 @def GPIO_CRH_MODE10_0 */
#define GPIO_CRH_MODE10_0			(BIT_VALUE(0x1UL, GPIO_CRH_MODE10_Pos))
/** @brief MODE10 1 @def GPIO_CRH_MODE10_1 */
#define GPIO_CRH_MODE10_1			(BIT_VALUE(0x2UL, GPIO_CRH_MODE10_Pos))

/** @brief GPIO_CRH_MODE11 Position @def GPIO_CRH_MODE11_Pos */
#define GPIO_CRH_MODE11_Pos			(12U)
/** @brief GPIO_CRH_MODE11 Mask @def GPIO_CRH_MODE11_Msk */
#define GPIO_CRH_MODE11_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_MODE11_Pos))
/** @brief MODE11 @def GPIO_CRH_MODE11 */
#define GPIO_CRH_MODE11				GPIO_CRH_MODE11_Msk
/** @brief MODE11 0 @def GPIO_CRH_MODE11_0 */
#define GPIO_CRH_MODE11_0			(BIT_VALUE(0x1UL, GPIO_CRH_MODE11_Pos))
/** @brief MODE11 1 @def GPIO_CRH_MODE11_1 */
#define GPIO_CRH_MODE11_1			(BIT_VALUE(0x2UL, GPIO_CRH_MODE11_Pos))

/** @brief GPIO_CRH_MODE12 Position @def GPIO_CRH_MODE12_Pos */
#define GPIO_CRH_MODE12_Pos			(16U)
/** @brief GPIO_CRH_MODE12 Mask @def GPIO_CRH_MODE12_Msk */
#define GPIO_CRH_MODE12_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_MODE12_Pos))
/** @brief MODE12 @def GPIO_CRH_MODE12 */
#define GPIO_CRH_MODE12				GPIO_CRH_MODE12_Msk
/** @brief MODE12 0 @def GPIO_CRH_MODE12_0 */
#define GPIO_CRH_MODE12_0			(BIT_VALUE(0x1UL, GPIO_CRH_MODE12_Pos))
/** @brief MODE12 1 @def GPIO_CRH_MODE12_1 */
#define GPIO_CRH_MODE12_1			(BIT_VALUE(0x2UL, GPIO_CRH_MODE12_Pos))

/** @brief GPIO_CRH_MODE13 Position @def GPIO_CRH_MODE13_Pos */
#define GPIO_CRH_MODE13_Pos			(20U)
/** @brief GPIO_CRH_MODE13 Mask @def GPIO_CRH_MODE13_Msk */
#define GPIO_CRH_MODE13_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_MODE13_Pos))
/** @brief MODE13 @def GPIO_CRH_MODE13 */
#define GPIO_CRH_MODE13				GPIO_CRH_MODE13_Msk
/** @brief MODE13 0 @def GPIO_CRH_MODE13_0 */
#define GPIO_CRH_MODE13_0			(BIT_VALUE(0x1UL, GPIO_CRH_MODE13_Pos))
/** @brief MODE13 1 @def GPIO_CRH_MODE13_1 */
#define GPIO_CRH_MODE13_1			(BIT_VALUE(0x2UL, GPIO_CRH_MODE13_Pos))

/** @brief GPIO_CRH_MODE14 Position @def GPIO_CRH_MODE14_Pos */
#define GPIO_CRH_MODE14_Pos			(24U)
/** @brief GPIO_CRH_MODE14 Mask @def GPIO_CRH_MODE14_Msk */
#define GPIO_CRH_MODE14_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_MODE14_Pos))
/** @brief MODE14 @def GPIO_CRH_MODE14 */
#define GPIO_CRH_MODE14				GPIO_CRH_MODE14_Msk
/** @brief MODE14 0 @def GPIO_CRH_MODE14_0 */
#define GPIO_CRH_MODE14_0			(BIT_VALUE(0x1UL, GPIO_CRH_MODE14_Pos))
/** @brief MODE14 1 @def GPIO_CRH_MODE14_1 */
#define GPIO_CRH_MODE14_1			(BIT_VALUE(0x2UL, GPIO_CRH_MODE14_Pos))

/** @brief GPIO_CRH_MODE15 Position @def GPIO_CRH_MODE15_Pos */
#define GPIO_CRH_MODE15_Pos			(28U)
/** @brief GPIO_CRH_MODE15 Mask @def GPIO_CRH_MODE15_Msk */
#define GPIO_CRH_MODE15_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_MODE15_Pos))
/** @brief MODE15 @def GPIO_CRH_MODE15 */
#define GPIO_CRH_MODE15				GPIO_CRH_MODE15_Msk
/** @brief MODE15 0 @def GPIO_CRH_MODE15_0 */
#define GPIO_CRH_MODE15_0			(BIT_VALUE(0x1UL, GPIO_CRH_MODE15_Pos))
/** @brief MODE15 1 @def GPIO_CRH_MODE15_1 */
#define GPIO_CRH_MODE15_1			(BIT_VALUE(0x2UL, GPIO_CRH_MODE15_Pos))

// ------ CNF (Port Configuration Bits for Pins 8-15) ------ // 
/** @brief GPIO_CRH_CNF Position @def GPIO_CRH_CNF_Pos */
#define GPIO_CRH_CNF_Pos			(2U)
/** @brief GPIO_CRH_CNF Mask @def GPIO_CRH_CNF_Msk */
#define GPIO_CRH_CNF_Msk			(BIT_VALUE(0x33333333UL, GPIO_CRH_CNF_Pos))
/** @brief Port Configuration Bits @def GPIO_CRH_CNF */
#define GPIO_CRH_CNF				GPIO_CRH_CNF_Msk

/** @brief GPIO_CRH_CNF8 Position @def GPIO_CRH_CNF8_Pos */
#define GPIO_CRH_CNF8_Pos			(2U)
/** @brief GPIO_CRH_CNF8 Mask @def GPIO_CRH_CNF8_Msk */
#define GPIO_CRH_CNF8_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_CNF8_Pos))
/** @brief CNF8 @def GPIO_CRH_CNF8 */
#define GPIO_CRH_CNF8				GPIO_CRH_CNF8_Msk
/** @brief CNF8 0 @def GPIO_CRH_CNF8_0 */
#define GPIO_CRH_CNF8_0				(BIT_VALUE(0x1UL, GPIO_CRH_CNF8_Pos))
/** @brief CNF8 1 @def GPIO_CRH_CNF8_1 */
#define GPIO_CRH_CNF8_1				(BIT_VALUE(0x2UL, GPIO_CRH_CNF8_Pos))

/** @brief GPIO_CRH_CNF9 Position @def GPIO_CRH_CNF9_Pos */
#define GPIO_CRH_CNF9_Pos			(6U)
/** @brief GPIO_CRH_CNF9 Mask @def GPIO_CRH_CNF9_Msk */
#define GPIO_CRH_CNF9_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_CNF9_Pos))
/** @brief CNF9 @def GPIO_CRH_CNF9 */
#define GPIO_CRH_CNF9				GPIO_CRH_CNF9_Msk
/** @brief CNF9 0 @def GPIO_CRH_CNF9_0 */
#define GPIO_CRH_CNF9_0				(BIT_VALUE(0x1UL, GPIO_CRH_CNF9_Pos))
/** @brief CNF9 1 @def GPIO_CRH_CNF9_1 */
#define GPIO_CRH_CNF9_1				(BIT_VALUE(0x2UL, GPIO_CRH_CNF9_Pos))

/** @brief GPIO_CRH_CNF10 Position @def GPIO_CRH_CNF10_Pos */
#define GPIO_CRH_CNF10_Pos			(10U)
/** @brief GPIO_CRH_CNF10 Mask @def GPIO_CRH_CNF10_Msk */
#define GPIO_CRH_CNF10_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_CNF10_Pos))
/** @brief CNF10 @def GPIO_CRH_CNF10 */
#define GPIO_CRH_CNF10				GPIO_CRH_CNF10_Msk
/** @brief CNF10 0 @def GPIO_CRH_CNF10_0 */
#define GPIO_CRH_CNF10_0			(BIT_VALUE(0x1UL, GPIO_CRH_CNF10_Pos))
/** @brief CNF10 1 @def GPIO_CRH_CNF10_1 */
#define GPIO_CRH_CNF10_1			(BIT_VALUE(0x2UL, GPIO_CRH_CNF10_Pos))

/** @brief GPIO_CRH_CNF11 Position @def GPIO_CRH_CNF11_Pos */
#define GPIO_CRH_CNF11_Pos			(14U)
/** @brief GPIO_CRH_CNF11 Mask @def GPIO_CRH_CNF11_Msk */
#define GPIO_CRH_CNF11_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_CNF11_Pos))
/** @brief CNF11 @def GPIO_CRH_CNF11 */
#define GPIO_CRH_CNF11				GPIO_CRH_CNF11_Msk
/** @brief CNF11 0 @def GPIO_CRH_CNF11_0 */
#define GPIO_CRH_CNF11_0			(BIT_VALUE(0x1UL, GPIO_CRH_CNF11_Pos))
/** @brief CNF11 1 @def GPIO_CRH_CNF11_1 */
#define GPIO_CRH_CNF11_1			(BIT_VALUE(0x2UL, GPIO_CRH_CNF11_Pos))

/** @brief GPIO_CRH_CNF12 Position @def GPIO_CRH_CNF12_Pos */
#define GPIO_CRH_CNF12_Pos			(18U)
/** @brief GPIO_CRH_CNF12 Mask @def GPIO_CRH_CNF12_Msk */
#define GPIO_CRH_CNF12_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_CNF12_Pos))
/** @brief CNF12 @def GPIO_CRH_CNF12 */
#define GPIO_CRH_CNF12				GPIO_CRH_CNF12_Msk
/** @brief CNF12 0 @def GPIO_CRH_CNF12_0 */
#define GPIO_CRH_CNF12_0			(BIT_VALUE(0x1UL, GPIO_CRH_CNF12_Pos))
/** @brief CNF12 1 @def GPIO_CRH_CNF12_1 */
#define GPIO_CRH_CNF12_1			(BIT_VALUE(0x2UL, GPIO_CRH_CNF12_Pos))

/** @brief GPIO_CRH_CNF13 Position @def GPIO_CRH_CNF13_Pos */
#define GPIO_CRH_CNF13_Pos			(22U)
/** @brief GPIO_CRH_CNF13 Mask @def GPIO_CRH_CNF13_Msk */
#define GPIO_CRH_CNF13_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_CNF13_Pos))
/** @brief CNF13 @def GPIO_CRH_CNF13 */
#define GPIO_CRH_CNF13				GPIO_CRH_CNF13_Msk
/** @brief CNF13 0 @def GPIO_CRH_CNF13_0 */
#define GPIO_CRH_CNF13_0			(BIT_VALUE(0x1UL, GPIO_CRH_CNF13_Pos))
/** @brief CNF13 1 @def GPIO_CRH_CNF13_1 */
#define GPIO_CRH_CNF13_1			(BIT_VALUE(0x2UL, GPIO_CRH_CNF13_Pos))

/** @brief GPIO_CRH_CNF14 Position @def GPIO_CRH_CNF14_Pos */
#define GPIO_CRH_CNF14_Pos			(26U)
/** @brief GPIO_CRH_CNF14 Mask @def GPIO_CRH_CNF14_Msk */
#define GPIO_CRH_CNF14_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_CNF14_Pos))
/** @brief CNF14 @def GPIO_CRH_CNF14 */
#define GPIO_CRH_CNF14				GPIO_CRH_CNF14_Msk
/** @brief CNF14 0 @def GPIO_CRH_CNF14_0 */
#define GPIO_CRH_CNF14_0			(BIT_VALUE(0x1UL, GPIO_CRH_CNF14_Pos))
/** @brief CNF14 1 @def GPIO_CRH_CNF14_1 */
#define GPIO_CRH_CNF14_1			(BIT_VALUE(0x2UL, GPIO_CRH_CNF14_Pos))

/** @brief GPIO_CRH_CNF15 Position @def GPIO_CRH_CNF15_Pos */
#define GPIO_CRH_CNF15_Pos			(30U)
/** @brief GPIO_CRH_CNF15 Mask @def GPIO_CRH_CNF15_Msk */
#define GPIO_CRH_CNF15_Msk			(BIT_VALUE(0x3UL, GPIO_CRH_CNF15_Pos))
/** @brief CNF15 @def GPIO_CRH_CNF15 */
#define GPIO_CRH_CNF15				GPIO_CRH_CNF15_Msk
/** @brief CNF15 0 @def GPIO_CRH_CNF15_0 */
#define GPIO_CRH_CNF15_0			(BIT_VALUE(0x1UL, GPIO_CRH_CNF15_Pos))
/** @brief CNF15 1 @def GPIO_CRH_CNF15_1 */
#define GPIO_CRH_CNF15_1			(BIT_VALUE(0x2UL, GPIO_CRH_CNF15_Pos))

/** @} */ // GPIO_CRH

// ------------------------------------------------------------------------------------------
// GPIO_IDR (Input Data Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief GPIO Input Data Register Definitions
 * @defgroup GPIO_01_RegisterLayer_03_InputData GPIO Input Data Register
 * @ingroup GPIO_01_RegisterLayer
 * @details
 * @section GPIO_IDR_Theory Theory and Practical Role
 * This page documents `GPIOx_IDR`, which reports the sampled logic level
 * currently observed on each GPIO pin.
 *
 * @section GPIO_IDR_Macros Register-Specific Macros
 * The macro definitions below expose the raw per-pin input bits used when the
 * LL layer samples GPIO input state directly from hardware.
 *
 * @section GPIO_IDR_Union Register Union View
 * The `union GPIO_IDR` view inside @ref GPIO_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ IDR[15:0] (Port Input Data Bits) ------ // 
/** @brief GPIO_IDR_IDR0 Position @def GPIO_IDR_IDR0_Pos */
#define GPIO_IDR_IDR0_Pos			(0U)
/** @brief GPIO_IDR_IDR0 Mask @def GPIO_IDR_IDR0_Msk */
#define GPIO_IDR_IDR0_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR0_Pos))
/** @brief Port Input Data Bit 0 @def GPIO_IDR_IDR0 */
#define GPIO_IDR_IDR0				GPIO_IDR_IDR0_Msk
/** @brief GPIO_IDR_IDR1 Position @def GPIO_IDR_IDR1_Pos */
#define GPIO_IDR_IDR1_Pos			(1U)
/** @brief GPIO_IDR_IDR1 Mask @def GPIO_IDR_IDR1_Msk */
#define GPIO_IDR_IDR1_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR1_Pos))
/** @brief Port Input Data Bit 1 @def GPIO_IDR_IDR1 */
#define GPIO_IDR_IDR1				GPIO_IDR_IDR1_Msk
/** @brief GPIO_IDR_IDR2 Position @def GPIO_IDR_IDR2_Pos */
#define GPIO_IDR_IDR2_Pos			(2U)
/** @brief GPIO_IDR_IDR2 Mask @def GPIO_IDR_IDR2_Msk */
#define GPIO_IDR_IDR2_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR2_Pos))
/** @brief Port Input Data Bit 2 @def GPIO_IDR_IDR2 */
#define GPIO_IDR_IDR2				GPIO_IDR_IDR2_Msk
/** @brief GPIO_IDR_IDR3 Position @def GPIO_IDR_IDR3_Pos */
#define GPIO_IDR_IDR3_Pos			(3U)
/** @brief GPIO_IDR_IDR3 Mask @def GPIO_IDR_IDR3_Msk */
#define GPIO_IDR_IDR3_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR3_Pos))
/** @brief Port Input Data Bit 3 @def GPIO_IDR_IDR3 */
#define GPIO_IDR_IDR3				GPIO_IDR_IDR3_Msk
/** @brief GPIO_IDR_IDR4 Position @def GPIO_IDR_IDR4_Pos */
#define GPIO_IDR_IDR4_Pos			(4U)
/** @brief GPIO_IDR_IDR4 Mask @def GPIO_IDR_IDR4_Msk */
#define GPIO_IDR_IDR4_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR4_Pos))
/** @brief Port Input Data Bit 4 @def GPIO_IDR_IDR4 */
#define GPIO_IDR_IDR4				GPIO_IDR_IDR4_Msk
/** @brief GPIO_IDR_IDR5 Position @def GPIO_IDR_IDR5_Pos */
#define GPIO_IDR_IDR5_Pos			(5U)
/** @brief GPIO_IDR_IDR5 Mask @def GPIO_IDR_IDR5_Msk */
#define GPIO_IDR_IDR5_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR5_Pos))
/** @brief Port Input Data Bit 5 @def GPIO_IDR_IDR5 */
#define GPIO_IDR_IDR5				GPIO_IDR_IDR5_Msk
/** @brief GPIO_IDR_IDR6 Position @def GPIO_IDR_IDR6_Pos */
#define GPIO_IDR_IDR6_Pos			(6U)
/** @brief GPIO_IDR_IDR6 Mask @def GPIO_IDR_IDR6_Msk */
#define GPIO_IDR_IDR6_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR6_Pos))
/** @brief Port Input Data Bit 6 @def GPIO_IDR_IDR6 */
#define GPIO_IDR_IDR6				GPIO_IDR_IDR6_Msk
/** @brief GPIO_IDR_IDR7 Position @def GPIO_IDR_IDR7_Pos */
#define GPIO_IDR_IDR7_Pos			(7U)
/** @brief GPIO_IDR_IDR7 Mask @def GPIO_IDR_IDR7_Msk */
#define GPIO_IDR_IDR7_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR7_Pos))
/** @brief Port Input Data Bit 7 @def GPIO_IDR_IDR7 */
#define GPIO_IDR_IDR7				GPIO_IDR_IDR7_Msk
/** @brief GPIO_IDR_IDR8 Position @def GPIO_IDR_IDR8_Pos */
#define GPIO_IDR_IDR8_Pos			(8U)
/** @brief GPIO_IDR_IDR8 Mask @def GPIO_IDR_IDR8_Msk */
#define GPIO_IDR_IDR8_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR8_Pos))
/** @brief Port Input Data Bit 8 @def GPIO_IDR_IDR8 */
#define GPIO_IDR_IDR8				GPIO_IDR_IDR8_Msk
/** @brief GPIO_IDR_IDR9 Position @def GPIO_IDR_IDR9_Pos */
#define GPIO_IDR_IDR9_Pos			(9U)
/** @brief GPIO_IDR_IDR9 Mask @def GPIO_IDR_IDR9_Msk */
#define GPIO_IDR_IDR9_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR9_Pos))
/** @brief Port Input Data Bit 9 @def GPIO_IDR_IDR9 */
#define GPIO_IDR_IDR9				GPIO_IDR_IDR9_Msk
/** @brief GPIO_IDR_IDR10 Position @def GPIO_IDR_IDR10_Pos */
#define GPIO_IDR_IDR10_Pos			(10U)
/** @brief GPIO_IDR_IDR10 Mask @def GPIO_IDR_IDR10_Msk */
#define GPIO_IDR_IDR10_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR10_Pos))
/** @brief Port Input Data Bit 10 @def GPIO_IDR_IDR10 */
#define GPIO_IDR_IDR10				GPIO_IDR_IDR10_Msk
/** @brief GPIO_IDR_IDR11 Position @def GPIO_IDR_IDR11_Pos */
#define GPIO_IDR_IDR11_Pos			(11U)
/** @brief GPIO_IDR_IDR11 Mask @def GPIO_IDR_IDR11_Msk */
#define GPIO_IDR_IDR11_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR11_Pos))
/** @brief Port Input Data Bit 11 @def GPIO_IDR_IDR11 */
#define GPIO_IDR_IDR11				GPIO_IDR_IDR11_Msk
/** @brief GPIO_IDR_IDR12 Position @def GPIO_IDR_IDR12_Pos */
#define GPIO_IDR_IDR12_Pos			(12U)
/** @brief GPIO_IDR_IDR12 Mask @def GPIO_IDR_IDR12_Msk */
#define GPIO_IDR_IDR12_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR12_Pos))
/** @brief Port Input Data Bit 12 @def GPIO_IDR_IDR12 */
#define GPIO_IDR_IDR12				GPIO_IDR_IDR12_Msk
/** @brief GPIO_IDR_IDR13 Position @def GPIO_IDR_IDR13_Pos */
#define GPIO_IDR_IDR13_Pos			(13U)
/** @brief GPIO_IDR_IDR13 Mask @def GPIO_IDR_IDR13_Msk */
#define GPIO_IDR_IDR13_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR13_Pos))
/** @brief Port Input Data Bit 13 @def GPIO_IDR_IDR13 */
#define GPIO_IDR_IDR13				GPIO_IDR_IDR13_Msk
/** @brief GPIO_IDR_IDR14 Position @def GPIO_IDR_IDR14_Pos */
#define GPIO_IDR_IDR14_Pos			(14U)
/** @brief GPIO_IDR_IDR14 Mask @def GPIO_IDR_IDR14_Msk */
#define GPIO_IDR_IDR14_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR14_Pos))
/** @brief Port Input Data Bit 14 @def GPIO_IDR_IDR14 */
#define GPIO_IDR_IDR14				GPIO_IDR_IDR14_Msk
/** @brief GPIO_IDR_IDR15 Position @def GPIO_IDR_IDR15_Pos */
#define GPIO_IDR_IDR15_Pos			(15U)
/** @brief GPIO_IDR_IDR15 Mask @def GPIO_IDR_IDR15_Msk */
#define GPIO_IDR_IDR15_Msk			(BIT_VALUE(0x1UL, GPIO_IDR_IDR15_Pos))
/** @brief Port Input Data Bit 15 @def GPIO_IDR_IDR15 */
#define GPIO_IDR_IDR15				GPIO_IDR_IDR15_Msk

/** @} */ // GPIO_IDR

// ------------------------------------------------------------------------------------------
// GPIO_ODR (Output Data Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief GPIO Output Data Register Definitions
 * @defgroup GPIO_01_RegisterLayer_04_OutputData GPIO Output Data Register
 * @ingroup GPIO_01_RegisterLayer
 * @details
 * @section GPIO_ODR_Theory Theory and Practical Role
 * This page documents `GPIOx_ODR`, which holds the latched output state for
 * each GPIO pin and, for input pull-up/pull-down mode, also provides the pull
 * direction staging bit.
 *
 * @section GPIO_ODR_Macros Register-Specific Macros
 * The macro definitions below expose the raw per-pin output bits used by the
 * LL layer when it reads or stages GPIO output state.
 *
 * @section GPIO_ODR_Union Register Union View
 * The `union GPIO_ODR` view inside @ref GPIO_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ ODR[15:0] (Port Output Data Bits) ------ // 
/** @brief GPIO_ODR_ODR0 Position @def GPIO_ODR_ODR0_Pos */
#define GPIO_ODR_ODR0_Pos			(0U)
/** @brief GPIO_ODR_ODR0 Mask @def GPIO_ODR_ODR0_Msk */
#define GPIO_ODR_ODR0_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR0_Pos))
/** @brief Port Output Data Bit 0 @def GPIO_ODR_ODR0 */
#define GPIO_ODR_ODR0				GPIO_ODR_ODR0_Msk
/** @brief GPIO_ODR_ODR1 Position @def GPIO_ODR_ODR1_Pos */
#define GPIO_ODR_ODR1_Pos			(1U)
/** @brief GPIO_ODR_ODR1 Mask @def GPIO_ODR_ODR1_Msk */
#define GPIO_ODR_ODR1_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR1_Pos))
/** @brief Port Output Data Bit 1 @def GPIO_ODR_ODR1 */
#define GPIO_ODR_ODR1				GPIO_ODR_ODR1_Msk
/** @brief GPIO_ODR_ODR2 Position @def GPIO_ODR_ODR2_Pos */
#define GPIO_ODR_ODR2_Pos			(2U)
/** @brief GPIO_ODR_ODR2 Mask @def GPIO_ODR_ODR2_Msk */
#define GPIO_ODR_ODR2_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR2_Pos))
/** @brief Port Output Data Bit 2 @def GPIO_ODR_ODR2 */
#define GPIO_ODR_ODR2				GPIO_ODR_ODR2_Msk
/** @brief GPIO_ODR_ODR3 Position @def GPIO_ODR_ODR3_Pos */
#define GPIO_ODR_ODR3_Pos			(3U)
/** @brief GPIO_ODR_ODR3 Mask @def GPIO_ODR_ODR3_Msk */
#define GPIO_ODR_ODR3_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR3_Pos))
/** @brief Port Output Data Bit 3 @def GPIO_ODR_ODR3 */
#define GPIO_ODR_ODR3				GPIO_ODR_ODR3_Msk
/** @brief GPIO_ODR_ODR4 Position @def GPIO_ODR_ODR4_Pos */
#define GPIO_ODR_ODR4_Pos			(4U)
/** @brief GPIO_ODR_ODR4 Mask @def GPIO_ODR_ODR4_Msk */
#define GPIO_ODR_ODR4_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR4_Pos))
/** @brief Port Output Data Bit 4 @def GPIO_ODR_ODR4 */
#define GPIO_ODR_ODR4				GPIO_ODR_ODR4_Msk
/** @brief GPIO_ODR_ODR5 Position @def GPIO_ODR_ODR5_Pos */
#define GPIO_ODR_ODR5_Pos			(5U)
/** @brief GPIO_ODR_ODR5 Mask @def GPIO_ODR_ODR5_Msk */
#define GPIO_ODR_ODR5_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR5_Pos))
/** @brief Port Output Data Bit 5 @def GPIO_ODR_ODR5 */
#define GPIO_ODR_ODR5				GPIO_ODR_ODR5_Msk
/** @brief GPIO_ODR_ODR6 Position @def GPIO_ODR_ODR6_Pos */
#define GPIO_ODR_ODR6_Pos			(6U)
/** @brief GPIO_ODR_ODR6 Mask @def GPIO_ODR_ODR6_Msk */
#define GPIO_ODR_ODR6_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR6_Pos))
/** @brief Port Output Data Bit 6 @def GPIO_ODR_ODR6 */
#define GPIO_ODR_ODR6				GPIO_ODR_ODR6_Msk
/** @brief GPIO_ODR_ODR7 Position @def GPIO_ODR_ODR7_Pos */
#define GPIO_ODR_ODR7_Pos			(7U)
/** @brief GPIO_ODR_ODR7 Mask @def GPIO_ODR_ODR7_Msk */
#define GPIO_ODR_ODR7_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR7_Pos))
/** @brief Port Output Data Bit 7 @def GPIO_ODR_ODR7 */
#define GPIO_ODR_ODR7				GPIO_ODR_ODR7_Msk
/** @brief GPIO_ODR_ODR8 Position @def GPIO_ODR_ODR8_Pos */
#define GPIO_ODR_ODR8_Pos			(8U)
/** @brief GPIO_ODR_ODR8 Mask @def GPIO_ODR_ODR8_Msk */
#define GPIO_ODR_ODR8_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR8_Pos))
/** @brief Port Output Data Bit 8 @def GPIO_ODR_ODR8 */
#define GPIO_ODR_ODR8				GPIO_ODR_ODR8_Msk
/** @brief GPIO_ODR_ODR9 Position @def GPIO_ODR_ODR9_Pos */
#define GPIO_ODR_ODR9_Pos			(9U)
/** @brief GPIO_ODR_ODR9 Mask @def GPIO_ODR_ODR9_Msk */
#define GPIO_ODR_ODR9_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR9_Pos))
/** @brief Port Output Data Bit 9 @def GPIO_ODR_ODR9 */
#define GPIO_ODR_ODR9				GPIO_ODR_ODR9_Msk
/** @brief GPIO_ODR_ODR10 Position @def GPIO_ODR_ODR10_Pos */
#define GPIO_ODR_ODR10_Pos			(10U)
/** @brief GPIO_ODR_ODR10 Mask @def GPIO_ODR_ODR10_Msk */
#define GPIO_ODR_ODR10_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR10_Pos))
/** @brief Port Output Data Bit 10 @def GPIO_ODR_ODR10 */
#define GPIO_ODR_ODR10				GPIO_ODR_ODR10_Msk
/** @brief GPIO_ODR_ODR11 Position @def GPIO_ODR_ODR11_Pos */
#define GPIO_ODR_ODR11_Pos			(11U)
/** @brief GPIO_ODR_ODR11 Mask @def GPIO_ODR_ODR11_Msk */
#define GPIO_ODR_ODR11_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR11_Pos))
/** @brief Port Output Data Bit 11 @def GPIO_ODR_ODR11 */
#define GPIO_ODR_ODR11				GPIO_ODR_ODR11_Msk
/** @brief GPIO_ODR_ODR12 Position @def GPIO_ODR_ODR12_Pos */
#define GPIO_ODR_ODR12_Pos			(12U)
/** @brief GPIO_ODR_ODR12 Mask @def GPIO_ODR_ODR12_Msk */
#define GPIO_ODR_ODR12_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR12_Pos))
/** @brief Port Output Data Bit 12 @def GPIO_ODR_ODR12 */
#define GPIO_ODR_ODR12				GPIO_ODR_ODR12_Msk
/** @brief GPIO_ODR_ODR13 Position @def GPIO_ODR_ODR13_Pos */
#define GPIO_ODR_ODR13_Pos			(13U)
/** @brief GPIO_ODR_ODR13 Mask @def GPIO_ODR_ODR13_Msk */
#define GPIO_ODR_ODR13_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR13_Pos))
/** @brief Port Output Data Bit 13 @def GPIO_ODR_ODR13 */
#define GPIO_ODR_ODR13				GPIO_ODR_ODR13_Msk
/** @brief GPIO_ODR_ODR14 Position @def GPIO_ODR_ODR14_Pos */
#define GPIO_ODR_ODR14_Pos			(14U)
/** @brief GPIO_ODR_ODR14 Mask @def GPIO_ODR_ODR14_Msk */
#define GPIO_ODR_ODR14_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR14_Pos))
/** @brief Port Output Data Bit 14 @def GPIO_ODR_ODR14 */
#define GPIO_ODR_ODR14				GPIO_ODR_ODR14_Msk
/** @brief GPIO_ODR_ODR15 Position @def GPIO_ODR_ODR15_Pos */
#define GPIO_ODR_ODR15_Pos			(15U)
/** @brief GPIO_ODR_ODR15 Mask @def GPIO_ODR_ODR15_Msk */
#define GPIO_ODR_ODR15_Msk			(BIT_VALUE(0x1UL, GPIO_ODR_ODR15_Pos))
/** @brief Port Output Data Bit 15 @def GPIO_ODR_ODR15 */
#define GPIO_ODR_ODR15				GPIO_ODR_ODR15_Msk

/** @} */ // GPIO_ODR

// ------------------------------------------------------------------------------------------
// GPIO_BSRR (Bit Set/Reset Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief GPIO Atomic Set/Reset Register Definitions
 * @defgroup GPIO_01_RegisterLayer_05_BitSetReset GPIO Bit Set/Reset Register
 * @ingroup GPIO_01_RegisterLayer
 * @details
 * @section GPIO_BSRR_Theory Theory and Practical Role
 * This page documents `GPIOx_BSRR`, which is the atomic write path for GPIO
 * output transitions. `BS[15:0]` sets pins high and `BR[31:16]` resets pins low
 * without requiring a read-modify-write on `GPIOx_ODR`.
 *
 * @section GPIO_BSRR_Macros Register-Specific Macros
 * The macro definitions below expose the raw set and reset bits used by the
 * LL layer when it performs atomic GPIO output transitions.
 *
 * @section GPIO_BSRR_Union Register Union View
 * The `union GPIO_BSRR` view inside @ref GPIO_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ BS[15:0] (Atomic Set Bits) ------ // 
/** @brief GPIO_BSRR_BS0 Position @def GPIO_BSRR_BS0_Pos */
#define GPIO_BSRR_BS0_Pos			(0U)
/** @brief GPIO_BSRR_BS0 Mask @def GPIO_BSRR_BS0_Msk */
#define GPIO_BSRR_BS0_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS0_Pos))
/** @brief Port Set Bit 0 @def GPIO_BSRR_BS0 */
#define GPIO_BSRR_BS0				GPIO_BSRR_BS0_Msk
/** @brief GPIO_BSRR_BS1 Position @def GPIO_BSRR_BS1_Pos */
#define GPIO_BSRR_BS1_Pos			(1U)
/** @brief GPIO_BSRR_BS1 Mask @def GPIO_BSRR_BS1_Msk */
#define GPIO_BSRR_BS1_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS1_Pos))
/** @brief Port Set Bit 1 @def GPIO_BSRR_BS1 */
#define GPIO_BSRR_BS1				GPIO_BSRR_BS1_Msk
/** @brief GPIO_BSRR_BS2 Position @def GPIO_BSRR_BS2_Pos */
#define GPIO_BSRR_BS2_Pos			(2U)
/** @brief GPIO_BSRR_BS2 Mask @def GPIO_BSRR_BS2_Msk */
#define GPIO_BSRR_BS2_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS2_Pos))
/** @brief Port Set Bit 2 @def GPIO_BSRR_BS2 */
#define GPIO_BSRR_BS2				GPIO_BSRR_BS2_Msk
/** @brief GPIO_BSRR_BS3 Position @def GPIO_BSRR_BS3_Pos */
#define GPIO_BSRR_BS3_Pos			(3U)
/** @brief GPIO_BSRR_BS3 Mask @def GPIO_BSRR_BS3_Msk */
#define GPIO_BSRR_BS3_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS3_Pos))
/** @brief Port Set Bit 3 @def GPIO_BSRR_BS3 */
#define GPIO_BSRR_BS3				GPIO_BSRR_BS3_Msk
/** @brief GPIO_BSRR_BS4 Position @def GPIO_BSRR_BS4_Pos */
#define GPIO_BSRR_BS4_Pos			(4U)
/** @brief GPIO_BSRR_BS4 Mask @def GPIO_BSRR_BS4_Msk */
#define GPIO_BSRR_BS4_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS4_Pos))
/** @brief Port Set Bit 4 @def GPIO_BSRR_BS4 */
#define GPIO_BSRR_BS4				GPIO_BSRR_BS4_Msk
/** @brief GPIO_BSRR_BS5 Position @def GPIO_BSRR_BS5_Pos */
#define GPIO_BSRR_BS5_Pos			(5U)
/** @brief GPIO_BSRR_BS5 Mask @def GPIO_BSRR_BS5_Msk */
#define GPIO_BSRR_BS5_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS5_Pos))
/** @brief Port Set Bit 5 @def GPIO_BSRR_BS5 */
#define GPIO_BSRR_BS5				GPIO_BSRR_BS5_Msk
/** @brief GPIO_BSRR_BS6 Position @def GPIO_BSRR_BS6_Pos */
#define GPIO_BSRR_BS6_Pos			(6U)
/** @brief GPIO_BSRR_BS6 Mask @def GPIO_BSRR_BS6_Msk */
#define GPIO_BSRR_BS6_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS6_Pos))
/** @brief Port Set Bit 6 @def GPIO_BSRR_BS6 */
#define GPIO_BSRR_BS6				GPIO_BSRR_BS6_Msk
/** @brief GPIO_BSRR_BS7 Position @def GPIO_BSRR_BS7_Pos */
#define GPIO_BSRR_BS7_Pos			(7U)
/** @brief GPIO_BSRR_BS7 Mask @def GPIO_BSRR_BS7_Msk */
#define GPIO_BSRR_BS7_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS7_Pos))
/** @brief Port Set Bit 7 @def GPIO_BSRR_BS7 */
#define GPIO_BSRR_BS7				GPIO_BSRR_BS7_Msk
/** @brief GPIO_BSRR_BS8 Position @def GPIO_BSRR_BS8_Pos */
#define GPIO_BSRR_BS8_Pos			(8U)
/** @brief GPIO_BSRR_BS8 Mask @def GPIO_BSRR_BS8_Msk */
#define GPIO_BSRR_BS8_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS8_Pos))
/** @brief Port Set Bit 8 @def GPIO_BSRR_BS8 */
#define GPIO_BSRR_BS8				GPIO_BSRR_BS8_Msk
/** @brief GPIO_BSRR_BS9 Position @def GPIO_BSRR_BS9_Pos */
#define GPIO_BSRR_BS9_Pos			(9U)
/** @brief GPIO_BSRR_BS9 Mask @def GPIO_BSRR_BS9_Msk */
#define GPIO_BSRR_BS9_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS9_Pos))
/** @brief Port Set Bit 9 @def GPIO_BSRR_BS9 */
#define GPIO_BSRR_BS9				GPIO_BSRR_BS9_Msk
/** @brief GPIO_BSRR_BS10 Position @def GPIO_BSRR_BS10_Pos */
#define GPIO_BSRR_BS10_Pos			(10U)
/** @brief GPIO_BSRR_BS10 Mask @def GPIO_BSRR_BS10_Msk */
#define GPIO_BSRR_BS10_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS10_Pos))
/** @brief Port Set Bit 10 @def GPIO_BSRR_BS10 */
#define GPIO_BSRR_BS10				GPIO_BSRR_BS10_Msk
/** @brief GPIO_BSRR_BS11 Position @def GPIO_BSRR_BS11_Pos */
#define GPIO_BSRR_BS11_Pos			(11U)
/** @brief GPIO_BSRR_BS11 Mask @def GPIO_BSRR_BS11_Msk */
#define GPIO_BSRR_BS11_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS11_Pos))
/** @brief Port Set Bit 11 @def GPIO_BSRR_BS11 */
#define GPIO_BSRR_BS11				GPIO_BSRR_BS11_Msk
/** @brief GPIO_BSRR_BS12 Position @def GPIO_BSRR_BS12_Pos */
#define GPIO_BSRR_BS12_Pos			(12U)
/** @brief GPIO_BSRR_BS12 Mask @def GPIO_BSRR_BS12_Msk */
#define GPIO_BSRR_BS12_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS12_Pos))
/** @brief Port Set Bit 12 @def GPIO_BSRR_BS12 */
#define GPIO_BSRR_BS12				GPIO_BSRR_BS12_Msk
/** @brief GPIO_BSRR_BS13 Position @def GPIO_BSRR_BS13_Pos */
#define GPIO_BSRR_BS13_Pos			(13U)
/** @brief GPIO_BSRR_BS13 Mask @def GPIO_BSRR_BS13_Msk */
#define GPIO_BSRR_BS13_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS13_Pos))
/** @brief Port Set Bit 13 @def GPIO_BSRR_BS13 */
#define GPIO_BSRR_BS13				GPIO_BSRR_BS13_Msk
/** @brief GPIO_BSRR_BS14 Position @def GPIO_BSRR_BS14_Pos */
#define GPIO_BSRR_BS14_Pos			(14U)
/** @brief GPIO_BSRR_BS14 Mask @def GPIO_BSRR_BS14_Msk */
#define GPIO_BSRR_BS14_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS14_Pos))
/** @brief Port Set Bit 14 @def GPIO_BSRR_BS14 */
#define GPIO_BSRR_BS14				GPIO_BSRR_BS14_Msk
/** @brief GPIO_BSRR_BS15 Position @def GPIO_BSRR_BS15_Pos */
#define GPIO_BSRR_BS15_Pos			(15U)
/** @brief GPIO_BSRR_BS15 Mask @def GPIO_BSRR_BS15_Msk */
#define GPIO_BSRR_BS15_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BS15_Pos))
/** @brief Port Set Bit 15 @def GPIO_BSRR_BS15 */
#define GPIO_BSRR_BS15				GPIO_BSRR_BS15_Msk

// ------ BR[31:16] (Atomic Reset Bits) ------ // 
/** @brief GPIO_BSRR_BR0 Position @def GPIO_BSRR_BR0_Pos */
#define GPIO_BSRR_BR0_Pos			(16U)
/** @brief GPIO_BSRR_BR0 Mask @def GPIO_BSRR_BR0_Msk */
#define GPIO_BSRR_BR0_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR0_Pos))
/** @brief Port Reset Bit 0 @def GPIO_BSRR_BR0 */
#define GPIO_BSRR_BR0				GPIO_BSRR_BR0_Msk
/** @brief GPIO_BSRR_BR1 Position @def GPIO_BSRR_BR1_Pos */
#define GPIO_BSRR_BR1_Pos			(17U)
/** @brief GPIO_BSRR_BR1 Mask @def GPIO_BSRR_BR1_Msk */
#define GPIO_BSRR_BR1_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR1_Pos))
/** @brief Port Reset Bit 1 @def GPIO_BSRR_BR1 */
#define GPIO_BSRR_BR1				GPIO_BSRR_BR1_Msk
/** @brief GPIO_BSRR_BR2 Position @def GPIO_BSRR_BR2_Pos */
#define GPIO_BSRR_BR2_Pos			(18U)
/** @brief GPIO_BSRR_BR2 Mask @def GPIO_BSRR_BR2_Msk */
#define GPIO_BSRR_BR2_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR2_Pos))
/** @brief Port Reset Bit 2 @def GPIO_BSRR_BR2 */
#define GPIO_BSRR_BR2				GPIO_BSRR_BR2_Msk
/** @brief GPIO_BSRR_BR3 Position @def GPIO_BSRR_BR3_Pos */
#define GPIO_BSRR_BR3_Pos			(19U)
/** @brief GPIO_BSRR_BR3 Mask @def GPIO_BSRR_BR3_Msk */
#define GPIO_BSRR_BR3_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR3_Pos))
/** @brief Port Reset Bit 3 @def GPIO_BSRR_BR3 */
#define GPIO_BSRR_BR3				GPIO_BSRR_BR3_Msk
/** @brief GPIO_BSRR_BR4 Position @def GPIO_BSRR_BR4_Pos */
#define GPIO_BSRR_BR4_Pos			(20U)
/** @brief GPIO_BSRR_BR4 Mask @def GPIO_BSRR_BR4_Msk */
#define GPIO_BSRR_BR4_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR4_Pos))
/** @brief Port Reset Bit 4 @def GPIO_BSRR_BR4 */
#define GPIO_BSRR_BR4				GPIO_BSRR_BR4_Msk
/** @brief GPIO_BSRR_BR5 Position @def GPIO_BSRR_BR5_Pos */
#define GPIO_BSRR_BR5_Pos			(21U)
/** @brief GPIO_BSRR_BR5 Mask @def GPIO_BSRR_BR5_Msk */
#define GPIO_BSRR_BR5_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR5_Pos))
/** @brief Port Reset Bit 5 @def GPIO_BSRR_BR5 */
#define GPIO_BSRR_BR5				GPIO_BSRR_BR5_Msk
/** @brief GPIO_BSRR_BR6 Position @def GPIO_BSRR_BR6_Pos */
#define GPIO_BSRR_BR6_Pos			(22U)
/** @brief GPIO_BSRR_BR6 Mask @def GPIO_BSRR_BR6_Msk */
#define GPIO_BSRR_BR6_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR6_Pos))
/** @brief Port Reset Bit 6 @def GPIO_BSRR_BR6 */
#define GPIO_BSRR_BR6				GPIO_BSRR_BR6_Msk
/** @brief GPIO_BSRR_BR7 Position @def GPIO_BSRR_BR7_Pos */
#define GPIO_BSRR_BR7_Pos			(23U)
/** @brief GPIO_BSRR_BR7 Mask @def GPIO_BSRR_BR7_Msk */
#define GPIO_BSRR_BR7_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR7_Pos))
/** @brief Port Reset Bit 7 @def GPIO_BSRR_BR7 */
#define GPIO_BSRR_BR7				GPIO_BSRR_BR7_Msk
/** @brief GPIO_BSRR_BR8 Position @def GPIO_BSRR_BR8_Pos */
#define GPIO_BSRR_BR8_Pos			(24U)
/** @brief GPIO_BSRR_BR8 Mask @def GPIO_BSRR_BR8_Msk */
#define GPIO_BSRR_BR8_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR8_Pos))
/** @brief Port Reset Bit 8 @def GPIO_BSRR_BR8 */
#define GPIO_BSRR_BR8				GPIO_BSRR_BR8_Msk
/** @brief GPIO_BSRR_BR9 Position @def GPIO_BSRR_BR9_Pos */
#define GPIO_BSRR_BR9_Pos			(25U)
/** @brief GPIO_BSRR_BR9 Mask @def GPIO_BSRR_BR9_Msk */
#define GPIO_BSRR_BR9_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR9_Pos))
/** @brief Port Reset Bit 9 @def GPIO_BSRR_BR9 */
#define GPIO_BSRR_BR9				GPIO_BSRR_BR9_Msk
/** @brief GPIO_BSRR_BR10 Position @def GPIO_BSRR_BR10_Pos */
#define GPIO_BSRR_BR10_Pos			(26U)
/** @brief GPIO_BSRR_BR10 Mask @def GPIO_BSRR_BR10_Msk */
#define GPIO_BSRR_BR10_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR10_Pos))
/** @brief Port Reset Bit 10 @def GPIO_BSRR_BR10 */
#define GPIO_BSRR_BR10				GPIO_BSRR_BR10_Msk
/** @brief GPIO_BSRR_BR11 Position @def GPIO_BSRR_BR11_Pos */
#define GPIO_BSRR_BR11_Pos			(27U)
/** @brief GPIO_BSRR_BR11 Mask @def GPIO_BSRR_BR11_Msk */
#define GPIO_BSRR_BR11_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR11_Pos))
/** @brief Port Reset Bit 11 @def GPIO_BSRR_BR11 */
#define GPIO_BSRR_BR11				GPIO_BSRR_BR11_Msk
/** @brief GPIO_BSRR_BR12 Position @def GPIO_BSRR_BR12_Pos */
#define GPIO_BSRR_BR12_Pos			(28U)
/** @brief GPIO_BSRR_BR12 Mask @def GPIO_BSRR_BR12_Msk */
#define GPIO_BSRR_BR12_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR12_Pos))
/** @brief Port Reset Bit 12 @def GPIO_BSRR_BR12 */
#define GPIO_BSRR_BR12				GPIO_BSRR_BR12_Msk
/** @brief GPIO_BSRR_BR13 Position @def GPIO_BSRR_BR13_Pos */
#define GPIO_BSRR_BR13_Pos			(29U)
/** @brief GPIO_BSRR_BR13 Mask @def GPIO_BSRR_BR13_Msk */
#define GPIO_BSRR_BR13_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR13_Pos))
/** @brief Port Reset Bit 13 @def GPIO_BSRR_BR13 */
#define GPIO_BSRR_BR13				GPIO_BSRR_BR13_Msk
/** @brief GPIO_BSRR_BR14 Position @def GPIO_BSRR_BR14_Pos */
#define GPIO_BSRR_BR14_Pos			(30U)
/** @brief GPIO_BSRR_BR14 Mask @def GPIO_BSRR_BR14_Msk */
#define GPIO_BSRR_BR14_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR14_Pos))
/** @brief Port Reset Bit 14 @def GPIO_BSRR_BR14 */
#define GPIO_BSRR_BR14				GPIO_BSRR_BR14_Msk
/** @brief GPIO_BSRR_BR15 Position @def GPIO_BSRR_BR15_Pos */
#define GPIO_BSRR_BR15_Pos			(31U)
/** @brief GPIO_BSRR_BR15 Mask @def GPIO_BSRR_BR15_Msk */
#define GPIO_BSRR_BR15_Msk			(BIT_VALUE(0x1UL, GPIO_BSRR_BR15_Pos))
/** @brief Port Reset Bit 15 @def GPIO_BSRR_BR15 */
#define GPIO_BSRR_BR15				GPIO_BSRR_BR15_Msk

/** @} */ // GPIO_BSRR

// ------------------------------------------------------------------------------------------
// GPIO_BRR (Bit Reset Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief GPIO Reset-Only Register Definitions
 * @defgroup GPIO_01_RegisterLayer_06_BitReset GPIO Bit Reset Register
 * @ingroup GPIO_01_RegisterLayer
 * @details
 * @section GPIO_BRR_Theory Theory and Practical Role
 * This page documents `GPIOx_BRR`, which is the legacy reset-only write path
 * for GPIO outputs.
 *
 * @section GPIO_BRR_Macros Register-Specific Macros
 * The macro definitions below expose the raw reset bits used by the LL layer
 * when it needs direct symbolic access to `GPIOx_BRR`.
 *
 * @section GPIO_BRR_Union Register Union View
 * The `union GPIO_BRR` view inside @ref GPIO_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ BR[15:0] (Reset Bits) ------ // 
/** @brief GPIO_BRR_BR0 Position @def GPIO_BRR_BR0_Pos */
#define GPIO_BRR_BR0_Pos			(0U)
/** @brief GPIO_BRR_BR0 Mask @def GPIO_BRR_BR0_Msk */
#define GPIO_BRR_BR0_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR0_Pos))
/** @brief Port Reset Bit 0 @def GPIO_BRR_BR0 */
#define GPIO_BRR_BR0				GPIO_BRR_BR0_Msk
/** @brief GPIO_BRR_BR1 Position @def GPIO_BRR_BR1_Pos */
#define GPIO_BRR_BR1_Pos			(1U)
/** @brief GPIO_BRR_BR1 Mask @def GPIO_BRR_BR1_Msk */
#define GPIO_BRR_BR1_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR1_Pos))
/** @brief Port Reset Bit 1 @def GPIO_BRR_BR1 */
#define GPIO_BRR_BR1				GPIO_BRR_BR1_Msk
/** @brief GPIO_BRR_BR2 Position @def GPIO_BRR_BR2_Pos */
#define GPIO_BRR_BR2_Pos			(2U)
/** @brief GPIO_BRR_BR2 Mask @def GPIO_BRR_BR2_Msk */
#define GPIO_BRR_BR2_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR2_Pos))
/** @brief Port Reset Bit 2 @def GPIO_BRR_BR2 */
#define GPIO_BRR_BR2				GPIO_BRR_BR2_Msk
/** @brief GPIO_BRR_BR3 Position @def GPIO_BRR_BR3_Pos */
#define GPIO_BRR_BR3_Pos			(3U)
/** @brief GPIO_BRR_BR3 Mask @def GPIO_BRR_BR3_Msk */
#define GPIO_BRR_BR3_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR3_Pos))
/** @brief Port Reset Bit 3 @def GPIO_BRR_BR3 */
#define GPIO_BRR_BR3				GPIO_BRR_BR3_Msk
/** @brief GPIO_BRR_BR4 Position @def GPIO_BRR_BR4_Pos */
#define GPIO_BRR_BR4_Pos			(4U)
/** @brief GPIO_BRR_BR4 Mask @def GPIO_BRR_BR4_Msk */
#define GPIO_BRR_BR4_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR4_Pos))
/** @brief Port Reset Bit 4 @def GPIO_BRR_BR4 */
#define GPIO_BRR_BR4				GPIO_BRR_BR4_Msk
/** @brief GPIO_BRR_BR5 Position @def GPIO_BRR_BR5_Pos */
#define GPIO_BRR_BR5_Pos			(5U)
/** @brief GPIO_BRR_BR5 Mask @def GPIO_BRR_BR5_Msk */
#define GPIO_BRR_BR5_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR5_Pos))
/** @brief Port Reset Bit 5 @def GPIO_BRR_BR5 */
#define GPIO_BRR_BR5				GPIO_BRR_BR5_Msk
/** @brief GPIO_BRR_BR6 Position @def GPIO_BRR_BR6_Pos */
#define GPIO_BRR_BR6_Pos			(6U)
/** @brief GPIO_BRR_BR6 Mask @def GPIO_BRR_BR6_Msk */
#define GPIO_BRR_BR6_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR6_Pos))
/** @brief Port Reset Bit 6 @def GPIO_BRR_BR6 */
#define GPIO_BRR_BR6				GPIO_BRR_BR6_Msk
/** @brief GPIO_BRR_BR7 Position @def GPIO_BRR_BR7_Pos */
#define GPIO_BRR_BR7_Pos			(7U)
/** @brief GPIO_BRR_BR7 Mask @def GPIO_BRR_BR7_Msk */
#define GPIO_BRR_BR7_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR7_Pos))
/** @brief Port Reset Bit 7 @def GPIO_BRR_BR7 */
#define GPIO_BRR_BR7				GPIO_BRR_BR7_Msk
/** @brief GPIO_BRR_BR8 Position @def GPIO_BRR_BR8_Pos */
#define GPIO_BRR_BR8_Pos			(8U)
/** @brief GPIO_BRR_BR8 Mask @def GPIO_BRR_BR8_Msk */
#define GPIO_BRR_BR8_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR8_Pos))
/** @brief Port Reset Bit 8 @def GPIO_BRR_BR8 */
#define GPIO_BRR_BR8				GPIO_BRR_BR8_Msk
/** @brief GPIO_BRR_BR9 Position @def GPIO_BRR_BR9_Pos */
#define GPIO_BRR_BR9_Pos			(9U)
/** @brief GPIO_BRR_BR9 Mask @def GPIO_BRR_BR9_Msk */
#define GPIO_BRR_BR9_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR9_Pos))
/** @brief Port Reset Bit 9 @def GPIO_BRR_BR9 */
#define GPIO_BRR_BR9				GPIO_BRR_BR9_Msk
/** @brief GPIO_BRR_BR10 Position @def GPIO_BRR_BR10_Pos */
#define GPIO_BRR_BR10_Pos			(10U)
/** @brief GPIO_BRR_BR10 Mask @def GPIO_BRR_BR10_Msk */
#define GPIO_BRR_BR10_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR10_Pos))
/** @brief Port Reset Bit 10 @def GPIO_BRR_BR10 */
#define GPIO_BRR_BR10				GPIO_BRR_BR10_Msk
/** @brief GPIO_BRR_BR11 Position @def GPIO_BRR_BR11_Pos */
#define GPIO_BRR_BR11_Pos			(11U)
/** @brief GPIO_BRR_BR11 Mask @def GPIO_BRR_BR11_Msk */
#define GPIO_BRR_BR11_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR11_Pos))
/** @brief Port Reset Bit 11 @def GPIO_BRR_BR11 */
#define GPIO_BRR_BR11				GPIO_BRR_BR11_Msk
/** @brief GPIO_BRR_BR12 Position @def GPIO_BRR_BR12_Pos */
#define GPIO_BRR_BR12_Pos			(12U)
/** @brief GPIO_BRR_BR12 Mask @def GPIO_BRR_BR12_Msk */
#define GPIO_BRR_BR12_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR12_Pos))
/** @brief Port Reset Bit 12 @def GPIO_BRR_BR12 */
#define GPIO_BRR_BR12				GPIO_BRR_BR12_Msk
/** @brief GPIO_BRR_BR13 Position @def GPIO_BRR_BR13_Pos */
#define GPIO_BRR_BR13_Pos			(13U)
/** @brief GPIO_BRR_BR13 Mask @def GPIO_BRR_BR13_Msk */
#define GPIO_BRR_BR13_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR13_Pos))
/** @brief Port Reset Bit 13 @def GPIO_BRR_BR13 */
#define GPIO_BRR_BR13				GPIO_BRR_BR13_Msk
/** @brief GPIO_BRR_BR14 Position @def GPIO_BRR_BR14_Pos */
#define GPIO_BRR_BR14_Pos			(14U)
/** @brief GPIO_BRR_BR14 Mask @def GPIO_BRR_BR14_Msk */
#define GPIO_BRR_BR14_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR14_Pos))
/** @brief Port Reset Bit 14 @def GPIO_BRR_BR14 */
#define GPIO_BRR_BR14				GPIO_BRR_BR14_Msk
/** @brief GPIO_BRR_BR15 Position @def GPIO_BRR_BR15_Pos */
#define GPIO_BRR_BR15_Pos			(15U)
/** @brief GPIO_BRR_BR15 Mask @def GPIO_BRR_BR15_Msk */
#define GPIO_BRR_BR15_Msk			(BIT_VALUE(0x1UL, GPIO_BRR_BR15_Pos))
/** @brief Port Reset Bit 15 @def GPIO_BRR_BR15 */
#define GPIO_BRR_BR15				GPIO_BRR_BR15_Msk

/** @} */ // GPIO_BRR

// ------------------------------------------------------------------------------------------
// GPIO_LCKR (Configuration Lock Register)
// ------------------------------------------------------------------------------------------

/**
 * @brief GPIO Configuration Lock Register Definitions
 * @defgroup GPIO_01_RegisterLayer_07_ConfigLock GPIO Configuration Lock Register
 * @ingroup GPIO_01_RegisterLayer
 * @details
 * @section GPIO_LCKR_Theory Theory and Practical Role
 * This page documents `GPIOx_LCKR`, which exposes the raw per-pin lock bits and
 * the `LCKK` lock-key handshake bit used to freeze CRL/CRH configuration until
 * reset.
 *
 * @section GPIO_LCKR_Macros Register-Specific Macros
 * The macro definitions below expose the raw lock bits used by the LL layer
 * when it performs GPIO configuration lock sequencing.
 *
 * @section GPIO_LCKR_Union Register Union View
 * The `union GPIO_LCKR` view inside @ref GPIO_TypeDef mirrors the same register
 * in software so a developer can compare the full register image (`.REG`)
 * against the named bitfield view (`.BIT`).
 * @{
 */

// ------ LCK[15:0] (Per-Pin Lock Bits) ------ // 
/** @brief GPIO_LCKR_LCK0 Position @def GPIO_LCKR_LCK0_Pos */
#define GPIO_LCKR_LCK0_Pos			(0U)
/** @brief GPIO_LCKR_LCK0 Mask @def GPIO_LCKR_LCK0_Msk */
#define GPIO_LCKR_LCK0_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK0_Pos))
/** @brief Port Lock Bit 0 @def GPIO_LCKR_LCK0 */
#define GPIO_LCKR_LCK0				GPIO_LCKR_LCK0_Msk
/** @brief GPIO_LCKR_LCK1 Position @def GPIO_LCKR_LCK1_Pos */
#define GPIO_LCKR_LCK1_Pos			(1U)
/** @brief GPIO_LCKR_LCK1 Mask @def GPIO_LCKR_LCK1_Msk */
#define GPIO_LCKR_LCK1_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK1_Pos))
/** @brief Port Lock Bit 1 @def GPIO_LCKR_LCK1 */
#define GPIO_LCKR_LCK1				GPIO_LCKR_LCK1_Msk
/** @brief GPIO_LCKR_LCK2 Position @def GPIO_LCKR_LCK2_Pos */
#define GPIO_LCKR_LCK2_Pos			(2U)
/** @brief GPIO_LCKR_LCK2 Mask @def GPIO_LCKR_LCK2_Msk */
#define GPIO_LCKR_LCK2_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK2_Pos))
/** @brief Port Lock Bit 2 @def GPIO_LCKR_LCK2 */
#define GPIO_LCKR_LCK2				GPIO_LCKR_LCK2_Msk
/** @brief GPIO_LCKR_LCK3 Position @def GPIO_LCKR_LCK3_Pos */
#define GPIO_LCKR_LCK3_Pos			(3U)
/** @brief GPIO_LCKR_LCK3 Mask @def GPIO_LCKR_LCK3_Msk */
#define GPIO_LCKR_LCK3_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK3_Pos))
/** @brief Port Lock Bit 3 @def GPIO_LCKR_LCK3 */
#define GPIO_LCKR_LCK3				GPIO_LCKR_LCK3_Msk
/** @brief GPIO_LCKR_LCK4 Position @def GPIO_LCKR_LCK4_Pos */
#define GPIO_LCKR_LCK4_Pos			(4U)
/** @brief GPIO_LCKR_LCK4 Mask @def GPIO_LCKR_LCK4_Msk */
#define GPIO_LCKR_LCK4_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK4_Pos))
/** @brief Port Lock Bit 4 @def GPIO_LCKR_LCK4 */
#define GPIO_LCKR_LCK4				GPIO_LCKR_LCK4_Msk
/** @brief GPIO_LCKR_LCK5 Position @def GPIO_LCKR_LCK5_Pos */
#define GPIO_LCKR_LCK5_Pos			(5U)
/** @brief GPIO_LCKR_LCK5 Mask @def GPIO_LCKR_LCK5_Msk */
#define GPIO_LCKR_LCK5_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK5_Pos))
/** @brief Port Lock Bit 5 @def GPIO_LCKR_LCK5 */
#define GPIO_LCKR_LCK5				GPIO_LCKR_LCK5_Msk
/** @brief GPIO_LCKR_LCK6 Position @def GPIO_LCKR_LCK6_Pos */
#define GPIO_LCKR_LCK6_Pos			(6U)
/** @brief GPIO_LCKR_LCK6 Mask @def GPIO_LCKR_LCK6_Msk */
#define GPIO_LCKR_LCK6_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK6_Pos))
/** @brief Port Lock Bit 6 @def GPIO_LCKR_LCK6 */
#define GPIO_LCKR_LCK6				GPIO_LCKR_LCK6_Msk
/** @brief GPIO_LCKR_LCK7 Position @def GPIO_LCKR_LCK7_Pos */
#define GPIO_LCKR_LCK7_Pos			(7U)
/** @brief GPIO_LCKR_LCK7 Mask @def GPIO_LCKR_LCK7_Msk */
#define GPIO_LCKR_LCK7_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK7_Pos))
/** @brief Port Lock Bit 7 @def GPIO_LCKR_LCK7 */
#define GPIO_LCKR_LCK7				GPIO_LCKR_LCK7_Msk
/** @brief GPIO_LCKR_LCK8 Position @def GPIO_LCKR_LCK8_Pos */
#define GPIO_LCKR_LCK8_Pos			(8U)
/** @brief GPIO_LCKR_LCK8 Mask @def GPIO_LCKR_LCK8_Msk */
#define GPIO_LCKR_LCK8_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK8_Pos))
/** @brief Port Lock Bit 8 @def GPIO_LCKR_LCK8 */
#define GPIO_LCKR_LCK8				GPIO_LCKR_LCK8_Msk
/** @brief GPIO_LCKR_LCK9 Position @def GPIO_LCKR_LCK9_Pos */
#define GPIO_LCKR_LCK9_Pos			(9U)
/** @brief GPIO_LCKR_LCK9 Mask @def GPIO_LCKR_LCK9_Msk */
#define GPIO_LCKR_LCK9_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK9_Pos))
/** @brief Port Lock Bit 9 @def GPIO_LCKR_LCK9 */
#define GPIO_LCKR_LCK9				GPIO_LCKR_LCK9_Msk
/** @brief GPIO_LCKR_LCK10 Position @def GPIO_LCKR_LCK10_Pos */
#define GPIO_LCKR_LCK10_Pos			(10U)
/** @brief GPIO_LCKR_LCK10 Mask @def GPIO_LCKR_LCK10_Msk */
#define GPIO_LCKR_LCK10_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK10_Pos))
/** @brief Port Lock Bit 10 @def GPIO_LCKR_LCK10 */
#define GPIO_LCKR_LCK10				GPIO_LCKR_LCK10_Msk
/** @brief GPIO_LCKR_LCK11 Position @def GPIO_LCKR_LCK11_Pos */
#define GPIO_LCKR_LCK11_Pos			(11U)
/** @brief GPIO_LCKR_LCK11 Mask @def GPIO_LCKR_LCK11_Msk */
#define GPIO_LCKR_LCK11_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK11_Pos))
/** @brief Port Lock Bit 11 @def GPIO_LCKR_LCK11 */
#define GPIO_LCKR_LCK11				GPIO_LCKR_LCK11_Msk
/** @brief GPIO_LCKR_LCK12 Position @def GPIO_LCKR_LCK12_Pos */
#define GPIO_LCKR_LCK12_Pos			(12U)
/** @brief GPIO_LCKR_LCK12 Mask @def GPIO_LCKR_LCK12_Msk */
#define GPIO_LCKR_LCK12_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK12_Pos))
/** @brief Port Lock Bit 12 @def GPIO_LCKR_LCK12 */
#define GPIO_LCKR_LCK12				GPIO_LCKR_LCK12_Msk
/** @brief GPIO_LCKR_LCK13 Position @def GPIO_LCKR_LCK13_Pos */
#define GPIO_LCKR_LCK13_Pos			(13U)
/** @brief GPIO_LCKR_LCK13 Mask @def GPIO_LCKR_LCK13_Msk */
#define GPIO_LCKR_LCK13_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK13_Pos))
/** @brief Port Lock Bit 13 @def GPIO_LCKR_LCK13 */
#define GPIO_LCKR_LCK13				GPIO_LCKR_LCK13_Msk
/** @brief GPIO_LCKR_LCK14 Position @def GPIO_LCKR_LCK14_Pos */
#define GPIO_LCKR_LCK14_Pos			(14U)
/** @brief GPIO_LCKR_LCK14 Mask @def GPIO_LCKR_LCK14_Msk */
#define GPIO_LCKR_LCK14_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK14_Pos))
/** @brief Port Lock Bit 14 @def GPIO_LCKR_LCK14 */
#define GPIO_LCKR_LCK14				GPIO_LCKR_LCK14_Msk
/** @brief GPIO_LCKR_LCK15 Position @def GPIO_LCKR_LCK15_Pos */
#define GPIO_LCKR_LCK15_Pos			(15U)
/** @brief GPIO_LCKR_LCK15 Mask @def GPIO_LCKR_LCK15_Msk */
#define GPIO_LCKR_LCK15_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCK15_Pos))
/** @brief Port Lock Bit 15 @def GPIO_LCKR_LCK15 */
#define GPIO_LCKR_LCK15				GPIO_LCKR_LCK15_Msk

// ------ LCKK (Configuration Lock Key) ------ // 
/** @brief GPIO_LCKR_LCKK Position @def GPIO_LCKR_LCKK_Pos */
#define GPIO_LCKR_LCKK_Pos			(16U)
/** @brief GPIO_LCKR_LCKK Mask @def GPIO_LCKR_LCKK_Msk */
#define GPIO_LCKR_LCKK_Msk			(BIT_VALUE(0x1UL, GPIO_LCKR_LCKK_Pos))
/** @brief Lock Key @def GPIO_LCKR_LCKK */
#define GPIO_LCKR_LCKK				GPIO_LCKR_LCKK_Msk

/** @} */ // GPIO_LCKR

// ------------------------------------------------------------------------------------------
// GPIO Structure
// ------------------------------------------------------------------------------------------ 

/**
 * @defgroup GPIO_01_RegisterLayer_08_RegisterMap GPIO Register Block Map
 * @ingroup GPIO_01_RegisterLayer
 * @brief Memory-mapped GPIO register block and practical register layout
 * @details
 * @section GPIO_RegisterMap_Theory Theory and Practical Role
 * This page ties the register definitions above to the concrete memory map used by
 * the software stack. @ref GPIO_TypeDef is the raw peripheral view consumed by the
 * LL layer when it reads, writes, or stages GPIO register state.
 *
 * @section GPIO_RegisterMap_Structure GPIO Register Block Structure
 * The structure below is the software-visible GPIO register layout in offset order.
 * Each register exposes a full-register view (`.REG`) and a named bitfield view (`.BIT`).
 * @{
 */

/**
 * @brief GPIO Register Block Structure
 * @details
 * Complete memory-mapped GPIO peripheral register map.
 *
 * @see RM0008 Section 9.2 GPIO registers
 * @typedef GPIO_TypeDef
 */
typedef volatile struct _GPIO_TypeDef
{
	/**
	 * @ingroup GPIO_01_RegisterLayer_01_PortConfigLow GPIO_01_RegisterLayer_08_RegisterMap
	 * @section GPIO_TypeDef_CRL GPIO Port Configuration Register Low (CRL)
	 * @brief [R/W] Configuration register for pins 0 to 7
	 * @details
	 * Each pin occupies one 4-bit slot composed of MODE[1:0] and CNF[1:0].
	 * This register controls pins 0 to 7. The raw field encodings are documented
	 * in @ref GPIO_01_RegisterLayer_01_PortConfigLow.
	 */
	union GPIO_CRL
	{
		_IO REG;
		struct
		{
			_IO MODE0 : 2;
			_IO CNF0 : 2;
			_IO MODE1 : 2;
			_IO CNF1 : 2;
			_IO MODE2 : 2;
			_IO CNF2 : 2;
			_IO MODE3 : 2;
			_IO CNF3 : 2;
			_IO MODE4 : 2;
			_IO CNF4 : 2;
			_IO MODE5 : 2;
			_IO CNF5 : 2;
			_IO MODE6 : 2;
			_IO CNF6 : 2;
			_IO MODE7 : 2;
			_IO CNF7 : 2;
		} BIT;
	} CRL;

	/**
	 * @ingroup GPIO_01_RegisterLayer_02_PortConfigHigh GPIO_01_RegisterLayer_08_RegisterMap
	 * @section GPIO_TypeDef_CRH GPIO Port Configuration Register High (CRH)
	 * @brief [R/W] Configuration register for pins 8 to 15
	 * @details
	 * Same slot structure as `GPIOx_CRL`, but for pins 8 to 15.
	 * Each pin occupies one 4-bit MODE/CNF field pair. The raw field encodings
	 * are documented in @ref GPIO_01_RegisterLayer_02_PortConfigHigh.
	 */
	union GPIO_CRH
	{
		_IO REG;
		struct
		{
			_IO MODE8 : 2;
			_IO CNF8 : 2;
			_IO MODE9 : 2;
			_IO CNF9 : 2;
			_IO MODE10 : 2;
			_IO CNF10 : 2;
			_IO MODE11 : 2;
			_IO CNF11 : 2;
			_IO MODE12 : 2;
			_IO CNF12 : 2;
			_IO MODE13 : 2;
			_IO CNF13 : 2;
			_IO MODE14 : 2;
			_IO CNF14 : 2;
			_IO MODE15 : 2;
			_IO CNF15 : 2;
		} BIT;
	} CRH;

	/**
	 * @ingroup GPIO_01_RegisterLayer_03_InputData GPIO_01_RegisterLayer_08_RegisterMap
	 * @section GPIO_TypeDef_IDR GPIO Port Input Data Register (IDR)
	 * @brief [R] Sampled input state of the GPIO port
	 * @details
	 * Bits 0 to 15 reflect the logic level currently observed on pins 0 to 15.
	 * Bits 16 to 31 are reserved.
	 */
	union GPIO_IDR
	{
		const _IO REG;
		struct
		{
			volatile const uint32_t IDR0 : 1;
			volatile const uint32_t IDR1 : 1;
			volatile const uint32_t IDR2 : 1;
			volatile const uint32_t IDR3 : 1;
			volatile const uint32_t IDR4 : 1;
			volatile const uint32_t IDR5 : 1;
			volatile const uint32_t IDR6 : 1;
			volatile const uint32_t IDR7 : 1;
			volatile const uint32_t IDR8 : 1;
			volatile const uint32_t IDR9 : 1;
			volatile const uint32_t IDR10 : 1;
			volatile const uint32_t IDR11 : 1;
			volatile const uint32_t IDR12 : 1;
			volatile const uint32_t IDR13 : 1;
			volatile const uint32_t IDR14 : 1;
			volatile const uint32_t IDR15 : 1;
			volatile const uint32_t RESERVED_IDR : 16;
		} BIT;
	} IDR;

	/**
	 * @ingroup GPIO_01_RegisterLayer_04_OutputData GPIO_01_RegisterLayer_08_RegisterMap
	 * @section GPIO_TypeDef_ODR GPIO Port Output Data Register (ODR)
	 * @brief [R/W] Latched output state of the GPIO port
	 * @details
	 * Bits 0 to 15 hold the output value driven by pins configured as outputs.
	 * For input pull-up/pull-down mode, these bits also stage the pull direction.
	 * Bits 16 to 31 are reserved.
	 */
	union GPIO_ODR
	{
		_IO REG;
		struct
		{
			_IO ODR0 : 1;
			_IO ODR1 : 1;
			_IO ODR2 : 1;
			_IO ODR3 : 1;
			_IO ODR4 : 1;
			_IO ODR5 : 1;
			_IO ODR6 : 1;
			_IO ODR7 : 1;
			_IO ODR8 : 1;
			_IO ODR9 : 1;
			_IO ODR10 : 1;
			_IO ODR11 : 1;
			_IO ODR12 : 1;
			_IO ODR13 : 1;
			_IO ODR14 : 1;
			_IO ODR15 : 1;
			_IO RESERVED_ODR : 16;
		} BIT;
	} ODR;

	/**
	 * @ingroup GPIO_01_RegisterLayer_05_BitSetReset GPIO_01_RegisterLayer_08_RegisterMap
	 * @section GPIO_TypeDef_BSRR GPIO Port Bit Set/Reset Register (BSRR)
	 * @brief [W] Atomic set/reset register for GPIO outputs
	 * @details
	 * Bits 0 to 15 set the corresponding output bits. Bits 16 to 31 reset the
	 * corresponding output bits. This register exists to update outputs without a
	 * read-modify-write sequence on `GPIOx_ODR`.
	 */
	union GPIO_BSRR
	{
		_IO REG;
		struct
		{
			_IO BS0 : 1;
			_IO BS1 : 1;
			_IO BS2 : 1;
			_IO BS3 : 1;
			_IO BS4 : 1;
			_IO BS5 : 1;
			_IO BS6 : 1;
			_IO BS7 : 1;
			_IO BS8 : 1;
			_IO BS9 : 1;
			_IO BS10 : 1;
			_IO BS11 : 1;
			_IO BS12 : 1;
			_IO BS13 : 1;
			_IO BS14 : 1;
			_IO BS15 : 1;
			_IO BR0 : 1;
			_IO BR1 : 1;
			_IO BR2 : 1;
			_IO BR3 : 1;
			_IO BR4 : 1;
			_IO BR5 : 1;
			_IO BR6 : 1;
			_IO BR7 : 1;
			_IO BR8 : 1;
			_IO BR9 : 1;
			_IO BR10 : 1;
			_IO BR11 : 1;
			_IO BR12 : 1;
			_IO BR13 : 1;
			_IO BR14 : 1;
			_IO BR15 : 1;
		} BIT;
	} BSRR;

	/**
	 * @ingroup GPIO_01_RegisterLayer_06_BitReset GPIO_01_RegisterLayer_08_RegisterMap
	 * @section GPIO_TypeDef_BRR GPIO Port Bit Reset Register (BRR)
	 * @brief [W] Atomic reset register for GPIO outputs
	 * @details
	 * Bits 0 to 15 reset the corresponding output bits. This register provides a
	 * dedicated reset path alongside the upper reset half of `GPIOx_BSRR`.
	 */
	union GPIO_BRR
	{
		_IO REG;
		struct
		{
			_IO BR0 : 1;
			_IO BR1 : 1;
			_IO BR2 : 1;
			_IO BR3 : 1;
			_IO BR4 : 1;
			_IO BR5 : 1;
			_IO BR6 : 1;
			_IO BR7 : 1;
			_IO BR8 : 1;
			_IO BR9 : 1;
			_IO BR10 : 1;
			_IO BR11 : 1;
			_IO BR12 : 1;
			_IO BR13 : 1;
			_IO BR14 : 1;
			_IO BR15 : 1;
			_IO RESERVED_BRR : 16;
		} BIT;
	} BRR;

	/**
	 * @ingroup GPIO_01_RegisterLayer_07_ConfigLock GPIO_01_RegisterLayer_08_RegisterMap
	 * @section GPIO_TypeDef_LCKR GPIO Port Configuration Lock Register (LCKR)
	 * @brief [R/W] Configuration lock register for GPIO pins
	 * @details
	 * Bits 0 to 15 select which pins participate in the lock sequence, and bit 16
	 * (`LCKK`) is the lock key used to finalize the hardware configuration lock.
	 * Once the sequence completes successfully, the selected pin configuration
	 * remains locked until the next reset.
	 */
	union GPIO_LCKR
	{
		_IO REG;
		struct
		{
			_IO LCK0 : 1;
			_IO LCK1 : 1;
			_IO LCK2 : 1;
			_IO LCK3 : 1;
			_IO LCK4 : 1;
			_IO LCK5 : 1;
			_IO LCK6 : 1;
			_IO LCK7 : 1;
			_IO LCK8 : 1;
			_IO LCK9 : 1;
			_IO LCK10 : 1;
			_IO LCK11 : 1;
			_IO LCK12 : 1;
			_IO LCK13 : 1;
			_IO LCK14 : 1;
			_IO LCK15 : 1;
			_IO LCKK : 1;
			_IO RESERVED_LCKR : 15;
		} BIT;
	} LCKR;
	
} GPIO_TypeDef;

/** @} */ // GPIO_01_RegisterLayer_08_RegisterMap

/** @} */ // GPIO_01_RegisterLayer

// C++ Header Guards
#ifdef __cplusplus
}
#endif

#endif /* STM32F1XX_GPIO_H_ */
