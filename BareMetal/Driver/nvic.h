/***************************************************************************************
 *  File: nvic.h
 *  Modified on:04-10-2025
 * 	Created on: 17/11/2024
 *  Author: Shrey Shah
 *  Version: v1.1
 *  Logs: Added Priority Configuration Functions
 * 
 * PREREQUISITES:
 * 1. Understanding of ARM Cortex-M Exception Model:
 *    - Exceptions: System exceptions (internal) + Interrupts (external)  
 *    - Exception Numbers: 1-15 (system), 16+ (external IRQs)
 *    - Priority: Lower number = Higher priority (0 = highest, 255 = lowest)
 *
 * 2. Priority Grouping Concept:
 *    - 8-bit priority field split into Preemption Priority + Sub-priority
 *    - Preemption: Higher priority can interrupt lower priority
 *    - Sub-priority: Used when same preemption level, no interruption
 *    
 * 3. Priority Group Configuration (`AIRCR.PRIGROUP`):
 * 		┌─────────────────┬──────────────┬──────────────┬─────────────────────┐
 * 		│ Group      	  │ Preempt Bits │ Sub Bits     │ Total Levels        │
 * 		├─────────────────┼──────────────┼──────────────┼─────────────────────┤
 * 		│ NVIC_GROUP_0    │ 0 (1 level)  │ 4 (16 levels)│ Cooperative         │
 * 		│ NVIC_GROUP_1    │ 1 (2 levels) │ 3 (8 levels) │ Basic 2-tier        │
 * 		│ NVIC_GROUP_2    │ 2 (4 levels) │ 2 (4 levels) │ Balanced (DEFAULT)  │
 * 		│ NVIC_GROUP_3    │ 3 (8 levels) │ 1 (2 levels) │ Complex RTOS        │
 * 		│ NVIC_GROUP_4    │ 4 (16 levels)│ 0 (1 level)  │ Hard Real-time      │
 * 		└─────────────────┴──────────────┴──────────────┴─────────────────────┘
 *
 * 4. Priority Register Layout:
 *    - IPR0-IPR59: Each holds 4 interrupt priorities (8 bits each)
 *	  - MEMORY LAYOUT OF IPR REGISTERS:
 *	     IPR[0] = | PRI_3[31:24] | PRI_2[23:16] | PRI_1[15:8] | PRI_0[7:0] |
 *	     IPR[1] = | PRI_7[31:24] | PRI_6[23:16] | PRI_5[15:8] | PRI_4[7:0] |
 *	     Each IPR register contains 4 priority fields of 8 bits each
 *    - IPR index calculation: IRQn / 4 :: IRQn >> 2
 *    - Byte offset: (IRQn % 4) * 8 :: ((IRQn >> 2) << 3)
 *
 * 5. AIRCR Register Key Protection:
 *    - VECTKEY (0x05FA) must be written to bits 31:16 for any write to succeed
 *    - Prevents accidental modification of critical system settings
 *
 * 6. Endianness Control:
 *    - Bit 15 of AIRCR controls data endianness
 *    - 0 = Little-endian (default), 1 = Big-endian
 *    - Most Cortex-M implementations are little-endian only
 *
 * EXAMPLE SCENARIOS:
 * 
 * Scenario 1: Group 2 Configuration (2+2 bits)
 *   Priority Value: 0b10100101 = 0xA5
 *   Preemption: 0b10 (2), Sub-priority: 0b01 (1)
 *   Interrupts with same preemption won't interrupt each other
 *   Higher preemption (0,1) can interrupt preemption level 2
 *
 * Scenario 2: Nested Interrupt Behavior
 *	|- IRQ A: Preempt=1, Sub=0 (running)
 *	|- IRQ B: Preempt=0, Sub=3 (arrives) → INTERRUPTS (higher preempt)
 *	|- IRQ C: Preempt=1, Sub=1 (arrives) → WAITS (same preempt level)
 *
 * IMPORTANT NOTES:
 * - Reset default: Priority Group 0 (all bits as sub-priority)
 * - System exceptions (SysTick, PendSV) use separate priority registers (SHPRx)
 * - Some implementations may not support all 8 priority bits (check device manual)
 * - Priority 0 is typically reserved for critical system functions
 * - When to Use Which Group:
 *	|- Group 0: Simple applications, no critical timing
 *	|- Group 2: Most common - balanced preemption control
 *	|- Group 4: Hard real-time, medical devices, aviation
 * - Key Takeaways:
 *	|- Priority Group = "How many levels of each do I have?"
 *	|- Preemption Priority = "Can this interrupt stop others?"
 *	|- Sub-priority = "Who goes first when equal preemption?"
 * In practice, 95% of embedded systems use Group 2 because it provides 
 * the right balance of responsiveness and simplicity
 ***************************************************************************************/

// ---- Header Guards ---- // 
#ifndef __NVIC_H__
#define __NVIC_H__

// ---- Main Library ---- //
#include "reg_map.h"

// --- Helper Macros --- //
#define _IRQn_GET_IPR_REG(X)						((X) >> 2)
#define _IRQn_GET_IPR_REG_INDEX(X)					(((X) & 0x03) << 3)

// --- STM32F103C8T6 --- //
#ifdef __STM32F103C8T6__
#define SCB_AICR_WRITE_VALUE						0x5FA
#else
#define SCB_AICR_WRITE_VALUE						0x000
#endif /* __STM32F103C8T6__ */

// ----- tyepdefs ----- //
typedef uint8_t priority_group_t;
typedef uint8_t priority_t;
typedef uint8_t sub_priority_t;
typedef uint32_t scb_exception_t;

// ------ Priority ------ //
/**
 * @brief Priority group configurations for NVIC priority grouping
 * 
 * @note Priority grouping determines how the 8-bit priority field is split
 *       between preemption priority and sub-priority bits
 */
/** 
 * @brief Group 0: 
 * @brief - 0 bits preemption
 * @brief - 4 bits sub-priority
 * @details 0 preemption levels, 16 sub-priority levels
 * @note - Cooperative systems where no interrupt can preempt others
 * @note - Simple applications, no real-time requirements
 */
#define NVIC_PRIO_GROUP_0							((priority_group_t) 0x00)
/** 
 * @brief Group 1: 
 * @brief - 1 bit preemption
 * @brief - 3 bits sub-priority  
 * @details 2 preemption levels, 8 sub-priority levels
 * @note - Basic two-level system (critical vs normal)
 * @note - Systems with one critical task category
 */
#define NVIC_PRIO_GROUP_1							((priority_group_t) 0x01)
/** 
 * @brief Group 2: 
 * @brief - 2 bits preemption
 * @brief - 2 bits sub-priority
 * @details 4 preemption levels, 4 sub-priority levels
 * @note - Balanced preemption control with good flexibility
 * @note - Most embedded systems - recommended default
 */
#define NVIC_PRIO_GROUP_2							((priority_group_t) 0x02)
/** 
 * @brief Group 3: 
 * @brief - 3 bits preemption
 * @brief - 1 bit sub-priority
 * @details 8 preemption levels, 2 sub-priority levels  
 * @note - Many preemption levels with minimal sub-priority
 * @note - Complex real-time systems with many priority levels
 */
#define NVIC_PRIO_GROUP_3							((priority_group_t) 0x03)
/** 
 * @brief Group 4: 
 * @brief - 4 bits preemption
 * @brief - 0 bits sub-priority
 * @details 16 preemption levels, no sub-priority
 * @note - Maximum preemption control, no same-level ordering
 * @note - Hard real-time systems, medical, automotive safety
 */
#define NVIC_PRIO_GROUP_4							((priority_group_t) 0x04)

/**
 * @brief Sub-priority values (0-15) - lower = higher priority
 */
// Highest sub-priority
#define NVIC_SUB_PRIO_0								((sub_priority_t) 0)
// Second highest sub-priority
#define NVIC_SUB_PRIO_1								((sub_priority_t) 1)
#define NVIC_SUB_PRIO_2								((sub_priority_t) 2)
#define NVIC_SUB_PRIO_3								((sub_priority_t) 3)
#define NVIC_SUB_PRIO_4								((sub_priority_t) 4)
#define NVIC_SUB_PRIO_5								((sub_priority_t) 5)
#define NVIC_SUB_PRIO_6								((sub_priority_t) 6)
#define NVIC_SUB_PRIO_7								((sub_priority_t) 7)
#define NVIC_SUB_PRIO_8								((sub_priority_t) 8)
#define NVIC_SUB_PRIO_9								((sub_priority_t) 9)
#define NVIC_SUB_PRIO_10         					((sub_priority_t) 10)
#define NVIC_SUB_PRIO_11         					((sub_priority_t) 11)
#define NVIC_SUB_PRIO_12         					((sub_priority_t) 12)
#define NVIC_SUB_PRIO_13         					((sub_priority_t) 13)
// Second lowest sub-priority
#define NVIC_SUB_PRIO_14         					((sub_priority_t) 14)
// Lowest sub-priority
#define NVIC_SUB_PRIO_15         					((sub_priority_t) 15)


/**
 * @brief Set the priority grouping using bit manipulation only
 * @param PriorityGroup Priority grouping field (0-4)
 */
__STATIC_INLINE__ void NVIC_SetPriorityGrouping(priority_group_t priorityGroup)
{
	uint32_t reg = SCB->AIRCR;
	// Writing to this register requires 0x5FA in the VECTKEY field
	// Otherwise the write value is ignored
	reg &= ~(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk);
	reg |= ((SCB_AICR_WRITE_VALUE << SCB_AIRCR_VECTKEY_Pos) | (priorityGroup & 0x07) << SCB_AIRCR_PRIGROUP_Pos);
	SCB->AIRCR = reg;
}

/**
 * @brief Get the current priority grouping
 * @return Current priority grouping (0-4)
 */
__STATIC_INLINE__ priority_group_t NVIC_GetPriorityGrouping(void)
{
	uint32_t reg = SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk;
	reg >>= SCB_AIRCR_PRIGROUP_Pos;
	return ((priority_group_t) reg);
}

/**
 * @brief Quick enable for common system exceptions
 * @param Exception: System exception number
 */
__STATIC_INLINE__ void SCB_EnableException(scb_exception_t exception)
{
	// Enable system exceptions via SHCSR
	SCB->SHCSR |= exception;
}

/**
 * @brief Get the current priority of an interrupt
 * @param IRQn Interrupt number
 * @return Current priority value (0-255)
 */
__STATIC_INLINE__ priority_t NVIC_GetPriority(const irq_t IRQn)
{
	uint32_t reg = NVIC->IPR[_IRQn_GET_IPR_REG(IRQn)];
	reg >>= _IRQn_GET_IPR_REG_INDEX(IRQn);
	reg &= 0xFF;
	return ((priority_t) reg);
}

/**
 * @brief Set the priority for an interrupt
 * @param IRQn Interrupt number
 * @param priority Priority value 
 * @note - `priority` permissible Values: 0 - 255 
 * @note - Lower Value implies higher priority
 */
__STATIC_INLINE__ void NVIC_SetPriority(const irq_t IRQn, const priority_t priority)
{
	uint32_t reg = NVIC->IPR[_IRQn_GET_IPR_REG(IRQn)];
	reg &= ~(0xFF << _IRQn_GET_IPR_REG_INDEX(IRQn));
	reg |= (priority & 0xFF) << _IRQn_GET_IPR_REG_INDEX(IRQn);
	NVIC->IPR[_IRQn_GET_IPR_REG(IRQn)] = reg;
}

/**
 * @brief Set priority with preemption and sub-priority
 * @param IRQn Interrupt number
 * @param PreemptPriority Preemption priority (0-15)
 * @param SubPriority Sub-priority (0-15) 
 * @param PriorityGroup Priority grouping (0-4)
 */
__STATIC_INLINE__ void NVIC_ConfigPriority(irq_t IRQn, priority_t priority, sub_priority_t subPriority)
{
	priority_t priorityGroup = NVIC_GetPriorityGrouping();
	NVIC_SetPriority(IRQn, (uint8_t) ((priority << (4 + priorityGroup)) | (subPriority << (4 - priorityGroup))));
}

/**
 * @brief Enables the NVIC Interrupt for the input IRQn
 * @param IRQn The Interrupt Number
 * @note Global Interrupt Configuration
 */
__STATIC_INLINE__ void NVIC_IRQEnable(uint8_t IRQn){
	// Enable the IRQn
	NVIC->ISER[(IRQn) >> 5] |=  (uint32_t) (1 << (IRQn & 0x1F));
}

/**
 * @brief Disables the NVIC Interrupt for the input IRQn
 * @param IRQn The Interrupt Number
 * @note Global Interrupt Configuration
 */
__STATIC_INLINE__ void NVIC_IRQDisable(uint8_t IRQn){
	// Disable the IRQn
	NVIC->ICER[(IRQn) >> 5] |=  (uint32_t) (1 << (IRQn & 0x1F));
}

/**
 * @brief Software IRQ Trigger
 * @param IRQn The Interrupt Number
 */
__STATIC_INLINE__ void NVIC_IRQ_SoftwareTrigger(uint8_t IRQn){
	// Set Pending Register
	NVIC->ISPR[(IRQn >> 5)] |= (uint32_t) (1 << (IRQn & 0x1F));
}

#endif /* __NVIC_H__ */
