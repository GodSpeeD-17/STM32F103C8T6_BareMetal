/**
 * @file stm32f1xx_nvic.h
 * @author Shrey Shah
 * @brief STM32F1 NVIC Register-Layer Definitions
 * @version v1.4
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
 * @brief Memory-mapped NVIC register block and practical register layout
 *
 * @details Complete register mapping for the Nested Vectored Interrupt Controller.
 *          The NVIC provides flexible interrupt management with hardware nesting support.
 *
 * @note 	Register addresses are relative to the NVIC base address (`NVIC_BASE_ADDR`)
 * @warning Some registers are read-only or have specific access requirements
 * @see 	Cortex-M3 TRM - Section 4.3.4 NVIC register descriptions
 * @{
 */

/**
 * @brief NVIC Register Structure
 * 
 * @details This structure maps the complete NVIC register set in memory.
 *          The NVIC supports up to 240 external interrupts with 16 priority levels
 *
 * @note Array sizes are designed for maximum STM32F1xx interrupt count
 * @see Reference Manual RM0008 - Table 63 for STM32F1xx interrupt mapping
 */
typedef volatile struct __NVIC_TypeDef 
{
	/**
	 * @brief Interrupt Set-Enable Registers (ISER)
	 * @details Enable interrupts by setting corresponding bits
	 * 
	 * - ISER[0]: Enables interrupts 0 to 31
	 * - ISER[1]: Enables interrupts 32 to 63  
	 * - ISER[2]: Enables interrupts 64 to 95
	 * - ISER[3]: Enables interrupts 96 to 127
	 * - ISER[4-7]: Reserved for future use
	 * 
	 * @note - 1: Enable
	 * @note - 0: Disable
	 * @see Cortex-M3 TRM - Section 4.3.6 NVIC register map
	 */
	volatile uint32_t ISER[8];
	
	/**
	 * @brief Reserved space between ISER and ICER
	 * @details 24 reserved words (0x020 - 0x07C)
	 */
	uint32_t RESERVED_0[24];
	
	/**
	 * @brief Interrupt Clear-Enable Registers (ICER)
	 * @details Disable interrupts by setting corresponding bits
	 * 
	 * - ICER[0]: Disables interrupts 0 to 31
	 * - ICER[1]: Disables interrupts 32 to 63
	 * - ICER[2]: Disables interrupts 64 to 95
	 * - ICER[3]: Disables interrupts 96 to 127
	 * - ICER[4-7]: Reserved for future use
	 * 
	 * @note - 1: Acknowledge
	 * @note - 0: No Effect
	 */
	volatile uint32_t ICER[8];
	
	/**
	 * @brief Reserved space between ICER and ISPR
	 * @details 24 reserved words (0x0A0 - 0x0FC)
	 */
	uint32_t RESERVED_1[24];
	
	/**
	 * @brief Interrupt Set-Pending Registers (ISPR)
	 * @details Force interrupts into pending state
	 * 
	 * - ISPR[0]: Sets pending for interrupts 0 to 31
	 * - ISPR[1]: Sets pending for interrupts 32 to 63
	 * - ISPR[2]: Sets pending for interrupts 64 to 95
	 * - ISPR[3]: Sets pending for interrupts 96 to 127
	 * - ISPR[4-7]: Reserved for future use
	 * 
	 * @note - 1: Software Trigger
	 * @note - 0: No Effect
	 */
	volatile uint32_t ISPR[8];
	
	/**
	 * @brief Reserved space between ISPR and ICPR
	 * @details 24 reserved words (0x120 - 0x17C)
	 */
	uint32_t RESERVED_2[24];
	
	/**
	 * @brief Interrupt Clear-Pending Registers (ICPR)
	 * @details Remove pending status from interrupts
	 * 
	 * - ICPR[0]: Clears pending for interrupts 0 to 31
	 * - ICPR[1]: Clears pending for interrupts 32 to 63
	 * - ICPR[2]: Clears pending for interrupts 64 to 95
	 * - ICPR[3]: Clears pending for interrupts 96 to 127
	 * - ICPR[4-7]: Reserved for future use
	 * 
	 * @note - 1: Acknowledge Software Trigger
	 * @note - 0: No Effect
	 */
	volatile uint32_t ICPR[8];
	
	/**
	 * @brief Reserved space between ICPR and IABR
	 * @details 24 reserved words (0x1A0 - 0x1FC)
	 */
	uint32_t RESERVED_3[24];
	
	/**
	 * @brief Interrupt Active Bit Registers (IABR)
	 * @details Read-only registers showing currently active interrupts
	 * 
	 * - IABR[0]: Active status for interrupts 0 to 31
	 * - IABR[1]: Active status for interrupts 32 to 63
	 * - IABR[2]: Active status for interrupts 64 to 95
	 * - IABR[3]: Active status for interrupts 96 to 127
	 * - IABR[4-7]: Reserved for future use
	 * 
	 * @note Read-only
	 * @note Set when interrupt is active
	 */
	volatile const uint32_t IABR[8];
	
	/**
	 * @brief Reserved space between IABR and IPR
	 * @details 56 reserved words (0x220 - 0x2FC)
	 */
	uint32_t RESERVED_4[56];
	
	/**
	 * @brief Interrupt Priority Registers (IPR)
	 * @details Configure priority levels for each interrupt
	 * 
	 * - Each IPR array element contains one interrupt priority byte
	 * - Each priority byte is 8 bits, but only the top 4 bits are implemented
	 * - Priority levels: 0 (highest) to 15 (lowest)
	 * - IPR[0]: Priority for interrupt 0
	 * - IPR[1]: Priority for interrupt 1
	 * - ... up to IPR[239] for interrupt 239
	 * 
	 * @note Only bits [7:4] are implemented in Cortex-M3
	 * @see Cortex-M3 TRM - Section 4.3.8 Interrupt Priority Registers
	 */
	volatile uint8_t IPR[240];
	
	/**
	 * @brief Reserved space between IPR and STIR
	 * @details 644 reserved words (0x3F0 - 0xDFC)
	 */
	uint32_t RESERVED_5[644];
	
	/**
	 * @brief Software Trigger Interrupt Register (STIR)
	 * @details Generate software interrupts by writing interrupt number
	 * 
	 * - Write interrupt number (0-239) to generate software interrupt
	 * - The request can become pending while interrupt delivery is disabled
	 * - Useful for testing and software synchronization
	 * 
	 * @note Only bits [8:0] are used for interrupt number
	 * @warning Requires privileged access to write
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
