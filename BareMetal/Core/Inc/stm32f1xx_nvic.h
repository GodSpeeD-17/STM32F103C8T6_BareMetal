/**
 * @file stm32f1xx_nvic.h
 * @author Shrey Shah
 * @brief STM32F1 NVIC Register-Layer Definitions
 * @version v1.5
 * @date 16-08-2026
 * @see @ref NVIC_Peripheral_Guide "STM32F103C8T6 NVIC Architecture"
 */

// Header Guards
#ifndef STM32F1XX_NVIC_H_
#define STM32F1XX_NVIC_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx_data_types.h"
#include "stm32f1xx_scb.h"

// --- C++ Safeguards ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup NVIC Nested Vectored Interrupt Controller (NVIC)
 * @brief Cortex-M3 external-interrupt state, delivery, and priority infrastructure
 * @details
 * This module maps the raw NVIC register block. Global priority grouping is
 * configured through the SCB-owned AIRCR register; its positions and masks
 * remain in @ref SCB_01_RegisterLayer_00_RegisterDefines.
 *
 * See @ref NVIC_Peripheral_Guide "STM32F103C8T6 NVIC Architecture" for the
 * complete interrupt theory, register semantics, and repository layer mapping.
 */

/**
 * @defgroup NVIC_01_RegisterLayer NVIC Register Layer
 * @ingroup NVIC
 * @brief Raw Cortex-M3 NVIC register structure
 * @details
 * This layer owns the hardware-visible NVIC access widths and memory layout
 * only. Driver-facing selectors, validation, encoding, and transaction
 * policy belong in the NVIC Driver, Codec, and LL layers.
 */

/**
 * @addtogroup NVIC_01_RegisterLayer
 * @{
 */

// ==================================================================================================== //
//											NVIC Register Map										//
// ==================================================================================================== //

/**
 * @defgroup NVIC_01_RegisterLayer_01_RegisterMap NVIC Register Block Map
 * @ingroup NVIC_01_RegisterLayer
 * @brief Memory-mapped Cortex-M3 NVIC architectural register layout
 * @details
 * The structure preserves the complete Cortex-M3 NVIC address aperture so
 * every architectural register retains its documented offset through STIR at
 * `0xE00`. These architectural array lengths do not claim that every slot is
 * implemented by STM32F103C8T6. The exact target implements external IRQs
 * `0..42`: all of bank 0, bits `0..10` of bank 1, and IPR bytes `0..42`.
 *
 * Register action semantics are summarized locally; the complete theory and
 * Driver mapping remain in @ref NVIC_Peripheral_Guide "STM32F103C8T6 NVIC Architecture".
 * @see Arm DDI 0337G, Table 8-1 NVIC registers
 * @see RM0008, Table 63 STM32F103xx interrupt vector table
 * @{
 */

/**
 * @brief Cortex-M3 NVIC architectural register block structure
 * @details
 * Maps the NVIC register window beginning at `0xE000E100`. Bitmap families
 * retain eight architectural banks and IPR retains 240 architectural byte
 * slots solely to preserve the register map and STIR offset. Exact-target
 * Driver validation prevents access beyond STM32F103C8T6 IRQ 42.
 *
 * @note STM32F103C8T6 implements priority bits `[7:4]` in each addressed IPR
 * byte, giving 16 encoded priority levels. The number of implemented priority
 * bits is implementation-defined by the Cortex-M3 architecture.
 */
typedef volatile struct __NVIC_TypeDef
{
	/**
	 * @section NVIC_TypeDef_ISER Interrupt Set-Enable Registers (ISER)
	 * @brief [R/W1S] Delivery-enable state and enable actions
	 * @details
	 * Reading returns enable state. Writing one enables the corresponding IRQ;
	 * writing zero has no effect. Each 32-bit bank represents 32 external IRQs.
	 * @note Offset: `0x000`
	 */
	volatile uint32_t ISER[8];

	/** @brief Reserved words from offsets `0x020` through `0x07C` */
	uint32_t RESERVED_0[24];

	/**
	 * @section NVIC_TypeDef_ICER Interrupt Clear-Enable Registers (ICER)
	 * @brief [R/W1C] Delivery-enable state and disable actions
	 * @details
	 * Reading returns enable state. Writing one disables the corresponding IRQ;
	 * writing zero has no effect.
	 * @note Offset: `0x080`
	 */
	volatile uint32_t ICER[8];

	/** @brief Reserved words from offsets `0x0A0` through `0x0FC` */
	uint32_t RESERVED_1[24];

	/**
	 * @section NVIC_TypeDef_ISPR Interrupt Set-Pending Registers (ISPR)
	 * @brief [R/W1S] Pending state and software-pend actions
	 * @details
	 * Reading returns pending state. Writing one pends the corresponding IRQ;
	 * writing zero has no effect.
	 * @note Offset: `0x100`
	 */
	volatile uint32_t ISPR[8];

	/** @brief Reserved words from offsets `0x120` through `0x17C` */
	uint32_t RESERVED_2[24];

	/**
	 * @section NVIC_TypeDef_ICPR Interrupt Clear-Pending Registers (ICPR)
	 * @brief [R/W1C] Pending state and pending-clear actions
	 * @details
	 * Reading returns pending state. Writing one clears the corresponding
	 * pending latch; writing zero has no effect. This action does not
	 * acknowledge a peripheral-owned source flag.
	 * @note Offset: `0x180`
	 */
	volatile uint32_t ICPR[8];

	/** @brief Reserved words from offsets `0x1A0` through `0x1FC` */
	uint32_t RESERVED_3[24];

	/**
	 * @section NVIC_TypeDef_IABR Interrupt Active Bit Registers (IABR)
	 * @brief [R] Processor-owned active exception state
	 * @details
	 * A set bit means the corresponding handler is executing or remains active
	 * while preempted and stacked. Software cannot clear active state.
	 * @note Offset: `0x200`
	 */
	volatile const uint32_t IABR[8];

	/** @brief Reserved words from offsets `0x220` through `0x2FC` */
	uint32_t RESERVED_4[56];

	/**
	 * @section NVIC_TypeDef_IPR Interrupt Priority Registers (IPR)
	 * @brief [R/W] Independently addressable per-IRQ priority bytes
	 * @details
	 * The architectural aperture contains 240 byte slots so `IPR[n]` is the
	 * priority byte for external IRQ `n`. STM32F103C8T6 implements slots `0..42`
	 * and the upper nibble `[7:4]` of each implemented slot.
	 * @note Offset: `0x300`
	 * @note Element access width: 8 bits
	 */
	volatile uint8_t IPR[240];

	/** @brief Reserved words from offsets `0x3F0` through `0xDFC` */
	uint32_t RESERVED_5[644];

	/**
	 * @section NVIC_TypeDef_STIR Software Trigger Interrupt Register (STIR)
	 * @brief [W] Software-generated external IRQ request action
	 * @details
	 * Writing a valid external IRQ number sets its pending state. The
	 * STM32F103C8T6 Driver restricts the architectural payload field to `0..42`.
	 * @note Offset: `0xE00`
	 * @warning Unprivileged writes require `SCB_CCR.USERSETMPEND`; otherwise the
	 * caller must execute with privileged access
	 */
	_O STIR;

} NVIC_TypeDef;

/** @} */ // NVIC_01_RegisterLayer_01_RegisterMap

/** @} */ // NVIC_01_RegisterLayer

// --- C++ Safeguards ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_NVIC_H_ */
