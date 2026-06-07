/**
 * @file	nvic.h
 * @author	Shrey Shah
 * @brief	NVIC Driver Interface
 * @version	v2.0
 * @date	06-06-2026
 *
 * @details
 * This header implements the Cortex-M3 NVIC driver as static inline functions.
 * It owns direct NVIC and SCB register access for external IRQ enable/disable,
 * software pending, priority field staging, and AIRCR priority grouping.
 *
 * Practical model:
 * - Lower numerical priority values have higher interrupt priority.
 * - STM32F1 implements four priority bits inside each 8-bit IPR field.
 * - @ref `NVIC_SetPriority` writes a raw 8-bit IPR field image.
 * - @ref `NVIC_ConfigPriority` accepts logical preemption/sub-priority values
 *   and packs them according to the current priority grouping.
 *
 * Authority:
 * - `nvic_data_types.h` owns NVIC scalar aliases.
 * - `nvic_defines.h` owns IRQ numbers, priority selectors, and helper macros.
 * - `nvic.h` owns direct NVIC/SCB register operations.
 */

#ifndef NVIC_H_
#define NVIC_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx.h"
#include "nvic_defines.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup NVIC_Driver
 * @{
 */

// ==================================================================================================== //
//											Local NVIC Helpers											//
// ==================================================================================================== //

/**
 * @brief Builds the NVIC register bit mask for one external IRQ number
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns Register-local IRQ bit mask
 * @retval - `0x00000001UL..0x80000000UL`: Mask for @p IRQn inside its NVIC register
 * @note Caller owns IRQ number validation.
 */
__STATIC_FORCEINLINE uint32_t _NVIC_GetIRQBitMask(const irq_t IRQn)
{
	//! Convert IRQn to a local bit position inside the selected 32-bit NVIC register
	return REG_BIT_MASK(NVIC_IRQ_GET_LOCAL_BIT_POS(IRQn));
}

/**
 * @brief Packs logical preemption/sub-priority values into one raw NVIC priority field
 * @param[in] preemptPriority Logical preemption priority selector
 * @param[in] subPriority Logical sub-priority selector
 * @param[in] priorityGroup Logical priority group selector
 * @returns Raw 8-bit NVIC IPR priority field image
 * @retval - `0x00U..0xF0U`: Priority value aligned to implemented STM32F1 priority bits
 * @note Only the upper four bits of the returned 8-bit field are implemented
 * by STM32F1 Cortex-M3 hardware.
 */
__STATIC_FORCEINLINE nvic_priority_t _NVIC_BuildPriorityField
(
	const nvic_priority_t			preemptPriority,
	const nvic_sub_priority_t		subPriority,
	const nvic_priority_group_t		priorityGroup
)
{
	// Local Variables
	const uint8_t preemptBits = (uint8_t) priorityGroup;
	const uint8_t subBits = (uint8_t) (NVIC_PRIORITY_IMPLEMENTED_BITS - preemptBits);
	const uint8_t preemptMask = (preemptBits == 0x00U) ? 0x00U : (uint8_t) ((0x01U << preemptBits) - 0x01U);
	const uint8_t subMask = (subBits == 0x00U) ? 0x00U : (uint8_t) ((0x01U << subBits) - 0x01U);
	uint8_t priorityNibble = 0x00U;

	//! Pack preemption priority into the upper part of the implemented four-bit priority field
	priorityNibble = (uint8_t) ((((uint8_t) preemptPriority) & preemptMask) << subBits);
	//! Pack sub-priority into the lower part of the implemented four-bit priority field
	priorityNibble |= (uint8_t) (((uint8_t) subPriority) & subMask);

	//! Align implemented STM32F1 priority bits to the upper nibble of the 8-bit IPR field
	return (nvic_priority_t) (priorityNibble << NVIC_PRIORITY_UNIMPLEMENTED_BITS);
}

// ==================================================================================================== //
//										SCB Priority Group APIs											//
// ==================================================================================================== //

/**
 * @brief Sets the NVIC priority grouping in `SCB->AIRCR`
 * @param[in] priorityGroup Logical priority group selector
 * Accepted values:
 * - @ref `NVIC_PRIO_GROUP_0`
 * - @ref `NVIC_PRIO_GROUP_1`
 * - @ref `NVIC_PRIO_GROUP_2`
 * - @ref `NVIC_PRIO_GROUP_3`
 * - @ref `NVIC_PRIO_GROUP_4`
 * @returns Void.
 * @note `AIRCR` writes require @ref `SCB_AIRCR_WRITE_KEY` in `VECTKEY`.
 * @note This function preserves all `AIRCR` bits except `VECTKEY` and `PRIGROUP`.
 */
__STATIC_FORCEINLINE void NVIC_SetPriorityGrouping(const nvic_priority_group_t priorityGroup)
{
	// Local Variables
	uint32_t aircrRegImage = SCB->AIRCR;
	const nvic_priority_group_t aircrPriorityGroup = NVIC_PRIO_GROUP_TO_AIRCR(priorityGroup);

	//! Clear the read-only VECTKEYSTAT image and the existing priority-group field
	aircrRegImage &= ~(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk);
	//! Write the required AIRCR key and the raw PRIGROUP field
	aircrRegImage |= REG_FIELD_VALUE(SCB_AIRCR_VECTKEY_Pos, SCB_AIRCR_WRITE_KEY);
	aircrRegImage |= REG_FIELD_VALUE(SCB_AIRCR_PRIGROUP_Pos, aircrPriorityGroup);

	SCB->AIRCR = aircrRegImage;
}

/**
 * @brief Gets the current logical NVIC priority grouping
 * @returns Logical priority group selector
 * @retval - @ref `NVIC_PRIO_GROUP_0`
 * @retval - @ref `NVIC_PRIO_GROUP_1`
 * @retval - @ref `NVIC_PRIO_GROUP_2`
 * @retval - @ref `NVIC_PRIO_GROUP_3`
 * @retval - @ref `NVIC_PRIO_GROUP_4`
 */
__STATIC_FORCEINLINE nvic_priority_group_t NVIC_GetPriorityGrouping(void)
{
	// Local Variable
	nvic_priority_group_t aircrPriorityGroup = (nvic_priority_group_t) 0x00U;
	//! Extract the raw AIRCR PRIGROUP field and convert it to the logical driver selector
	aircrPriorityGroup = (nvic_priority_group_t) ((SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos);
	return NVIC_AIRCR_TO_PRIO_GROUP(aircrPriorityGroup);
}

/**
 * @brief Enables one configurable SCB system exception
 * @param[in] exception SCB `SHCSR` exception enable bit mask
 * Accepted values:
 * - @ref `SCB_SHCSR_MEMFAULTENA_Msk`
 * - @ref `SCB_SHCSR_BUSFAULTENA_Msk`
 * - @ref `SCB_SHCSR_USGFAULTENA_Msk`
 * @returns Void.
 * @note This function only sets bits in `SCB->SHCSR`; it does not configure
 * exception priority.
 */
__STATIC_FORCEINLINE void SCB_EnableException(const scb_exception_t exception)
{
	//! Enable the requested configurable system exception bit(s)
	SCB->SHCSR |= exception;
}

// ==================================================================================================== //
//										NVIC Priority APIs												//
// ==================================================================================================== //

/**
 * @brief Gets the raw 8-bit priority field for one external IRQ
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns Raw NVIC IPR priority field image
 * @retval - `0x00U..0xFFU`: Right-aligned 8-bit priority field
 * @note On STM32F1 only the upper four bits of this field are implemented.
 */
__STATIC_FORCEINLINE nvic_priority_t NVIC_GetPriority(const irq_t IRQn)
{
	// Local Variables
	uint32_t iprRegImage = NVIC->IPR[_NVIC_IRQn_GET_IPR_REG(IRQn)];

	//! Shift the selected 8-bit priority field down to bit 0 and mask unrelated fields
	iprRegImage >>= _NVIC_IRQn_GET_IPR_REG_INDEX(IRQn);
	iprRegImage &= NVIC_PRIORITY_FIELD_MASK;

	return (nvic_priority_t) iprRegImage;
}

/**
 * @brief Sets the raw 8-bit priority field for one external IRQ
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[in] priority Raw NVIC IPR priority field image
 * Accepted values:
 * - `0x00U..0xFFU`
 * @returns Void.
 * @note Lower numerical priority values have higher effective priority.
 * @note On STM32F1 only the upper four bits of @p priority are implemented.
 */
__STATIC_FORCEINLINE void NVIC_SetPriority(const irq_t IRQn, const nvic_priority_t priority)
{
	// Local Variables
	const uint8_t iprRegIndex = _NVIC_IRQn_GET_IPR_REG(IRQn);
	const uint8_t priorityFieldPos = _NVIC_IRQn_GET_IPR_REG_INDEX(IRQn);
	uint32_t iprRegImage = NVIC->IPR[iprRegIndex];

	//! Replace only the selected IRQ priority field inside the IPR register image
	iprRegImage = RegOps_StageFieldValue
	(
		iprRegImage,
		priorityFieldPos,
		priority,
		NVIC_PRIORITY_FIELD_WIDTH
	);

	NVIC->IPR[iprRegIndex] = iprRegImage;
}

/**
 * @brief Configures one IRQ priority from logical preemption and sub-priority selectors
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[in] priority Logical preemption priority selector
 * Accepted values:
 * - `0U..15U`; effective range depends on current priority grouping
 * @param[in] subPriority Logical sub-priority selector
 * Accepted values:
 * - @ref `NVIC_SUB_PRIO_0` through @ref `NVIC_SUB_PRIO_15`; effective range
 * depends on current priority grouping
 * @returns Void.
 * @details
 * The current priority group decides how the four implemented STM32F1 priority
 * bits split between preemption priority and sub-priority. Values outside the
 * effective bit width are masked.
 */
__STATIC_FORCEINLINE void NVIC_ConfigPriority
(
	const irq_t					IRQn,
	const nvic_priority_t		priority,
	const nvic_sub_priority_t	subPriority
)
{
	// Local Variables
	const nvic_priority_group_t priorityGroup = NVIC_GetPriorityGrouping();
	const nvic_priority_t priorityField = _NVIC_BuildPriorityField(priority, subPriority, priorityGroup);
	NVIC_SetPriority(IRQn, priorityField);
}

// ==================================================================================================== //
//										NVIC IRQ State APIs												//
// ==================================================================================================== //

/**
 * @brief Enables one external IRQ in NVIC
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns Void.
 * @note This writes the corresponding `ISER` bit. It does not configure
 * peripheral-side interrupt masks or pending flags.
 */
__STATIC_FORCEINLINE void NVIC_IRQ_Enable(const irq_t IRQn)
{
	//! Write-one-to-set the selected interrupt enable bit
	NVIC->ISER[NVIC_IRQ_GET_REG_INDEX(IRQn)] = _NVIC_GetIRQBitMask(IRQn);
}

/**
 * @brief Disables one external IRQ in NVIC
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns Void.
 * @note This writes the corresponding `ICER` bit. It does not change
 * peripheral-side interrupt masks or pending flags.
 */
__STATIC_FORCEINLINE void NVIC_IRQ_Disable(const irq_t IRQn)
{
	//! Write-one-to-clear the selected interrupt enable bit
	NVIC->ICER[NVIC_IRQ_GET_REG_INDEX(IRQn)] = _NVIC_GetIRQBitMask(IRQn);
}

/**
 * @brief Triggers one external IRQ from software
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns Void.
 * @note This writes `NVIC->STIR`, which sets the selected interrupt pending
 * from software when privileged access permits it.
 */
__STATIC_FORCEINLINE void NVIC_IRQ_SoftwareTrigger(const irq_t IRQn)
{
	//! Request a software-generated interrupt through STIR
	NVIC->STIR = (uint32_t) IRQn;
}

/** @} */ // NVIC_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_H_ */
