/**
 * @file	nvic_codec.c
 * @author	Shrey Shah
 * @brief	NVIC Priority Codec Implementation
 * @version	v1.1
 * @date	16-08-2026
 *
 * @details
 * @section NVIC_CODEC_IMPL_SCOPE Scope
 * This source file implements pure priority-group and per-IRQ priority
 * transformations declared in `nvic_codec.h`.
 *
 * @section NVIC_CODEC_IMPL_BOUNDARY Boundary
 * Every function consumes scalar selectors and caller-owned register images.
 * No function dereferences NVIC/SCB hardware, performs volatile I/O, or owns
 * delivery, privilege, barrier, and concurrency policy.
 *
 * @section NVIC_CODEC_IMPL_PUBLICATION Publication
 * Stage functions transform local image copies and publish only after all
 * validation succeeds. Multi-output extraction likewise decodes into local
 * values before changing caller storage.
 *
 * @section NVIC_CODEC_IMPL_LAYOUT Source Layout
 * Private validation/limit helpers precede the priority-group and IRQ-priority
 * Codec pairs in the same order as `nvic_codec.h`.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "nvic_codec.h"
#include "stm32f1xx.h"

// ==================================================================================================== //
//									Local Codec Defines									//
// ==================================================================================================== //

/** @brief Number of implemented STM32F103C8T6 NVIC priority bits @def NVIC_CODEC_PRIORITY_IMPLEMENTED_BITS */
#define NVIC_CODEC_PRIORITY_IMPLEMENTED_BITS		((uint8_t) 0x04U)
/** @brief Bit shift from a logical priority nibble to implemented IPR bits @def NVIC_CODEC_PRIORITY_FIELD_SHIFT */
#define NVIC_CODEC_PRIORITY_FIELD_SHIFT				((uint8_t) 0x04U)
/** @brief Raw AIRCR group value corresponding to zero preemption bits @def NVIC_CODEC_AIRCR_GROUP_BASE */
#define NVIC_CODEC_AIRCR_GROUP_BASE					((uint8_t) 0x07U)
/** @brief Lowest canonical raw AIRCR group value on a four-bit target @def NVIC_CODEC_AIRCR_GROUP_CANONICAL_MIN */
#define NVIC_CODEC_AIRCR_GROUP_CANONICAL_MIN		((uint8_t) 0x03U)
/** @brief Mandatory AIRCR write-key value before field positioning @def NVIC_CODEC_AIRCR_WRITE_KEY */
#define NVIC_CODEC_AIRCR_WRITE_KEY					((reg) 0x05FAUL)
/** @brief AIRCR reset/action bits cleared from priority-group writes @def NVIC_CODEC_AIRCR_ACTION_MASK */
#define NVIC_CODEC_AIRCR_ACTION_MASK				\
	(SCB_AIRCR_SYSRESETREQ_Msk | SCB_AIRCR_VECTCLRACTIVE_Msk | SCB_AIRCR_VECTRESET_Msk)

// ==================================================================================================== //
//										Local Codec Helpers												//
// ==================================================================================================== //

// --------------------------------- Local Priority Group Validation --------------------------------- //

/**
 * @brief Validates one logical NVIC priority-group selector
 * @param[in] priorityGroup Logical priority-group selector
 * Accepted values:
 * - @ref `NVIC_PRIO_GROUP_0`
 * - @ref `NVIC_PRIO_GROUP_1`
 * - @ref `NVIC_PRIO_GROUP_2`
 * - @ref `NVIC_PRIO_GROUP_3`
 * - @ref `NVIC_PRIO_GROUP_4`
 * @returns @ref driver_status_t "Priority-group validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p `priorityGroup` is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `priorityGroup` is invalid
 */
static driver_status_t _Codec_NVIC_ValidatePriorityGroup(const nvic_priority_group_t priorityGroup)
{
	//! Logical group value equals the implemented preemption-bit count and must fit 0 through 4.
	if (priorityGroup > NVIC_PRIO_GROUP_4)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

// ----------------------------------- Local Priority Range Helper ------------------------------------ //

/**
 * @brief Calculates the maximum selector representable by a priority-bit count
 * @param[in] bitCount Number of implemented selector bits
 * Accepted values:
 * - `0U..4U`
 * @returns Maximum right-aligned selector value
 * @retval - `0U..15U`: Maximum value representable by @p bitCount
 * @pre Caller constrains @p bitCount to the four implemented priority bits
 */
static uint8_t _Codec_NVIC_GetPriorityLimit(const uint8_t bitCount)
{
	//! A zero-width selector has one legal semantic value: zero.
	if (bitCount == 0x00U)
	{
		return 0x00U;
	}

	return (uint8_t) ((0x01U << bitCount) - 0x01U);
}

// ==================================================================================================== //
//						NVIC Priority Configuration Codec Implementation						//
// ==================================================================================================== //

// --------------------------------- NVIC Priority Group Codec Pair ---------------------------------- //

driver_status_t Codec_NVIC_ExtractPriorityGroup
(
	const reg						aircrRegImage,
	nvic_priority_group_t* const	pPriorityGroup
)
{
	// Local Variables
	uint8_t rawPriorityGroup = 0x00U;
	nvic_priority_group_t priorityGroup = NVIC_PRIO_GROUP_4;

	// Validate Output
	if (pPriorityGroup == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Extract the raw PRIGROUP field without interpreting unrelated AIRCR bits.
	rawPriorityGroup = (uint8_t) ((aircrRegImage & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos);

	//! Raw values 0 through 3 are equivalent on a four-priority-bit target and canonicalize to Group 4.
	if (rawPriorityGroup >= NVIC_CODEC_AIRCR_GROUP_CANONICAL_MIN)
	{
		priorityGroup = (nvic_priority_group_t) (NVIC_CODEC_AIRCR_GROUP_BASE - rawPriorityGroup);
	}

	*pPriorityGroup = priorityGroup;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_NVIC_StagePriorityGroup
(
	reg* const						pAircrRegImage,
	const nvic_priority_group_t		priorityGroup
)
{
	// Local Variables
	reg updatedAircrRegImage = 0x00000000UL;
	reg rawPriorityGroup = 0x00000000UL;

	// Validate Input and Output
	if (pAircrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_Codec_NVIC_ValidatePriorityGroup(priorityGroup));

	//! Copy the caller image only after validation so failure leaves caller storage unchanged.
	updatedAircrRegImage = *pAircrRegImage;
	rawPriorityGroup = (reg) (NVIC_CODEC_AIRCR_GROUP_BASE - priorityGroup);

	//! Remove the read key image, previous group, and every AIRCR reset/action request.
	updatedAircrRegImage &= ~(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk | NVIC_CODEC_AIRCR_ACTION_MASK);

	//! Insert the mandatory write key and canonical raw priority-group field.
	updatedAircrRegImage |= (NVIC_CODEC_AIRCR_WRITE_KEY << SCB_AIRCR_VECTKEY_Pos);
	updatedAircrRegImage |= (rawPriorityGroup << SCB_AIRCR_PRIGROUP_Pos);

	*pAircrRegImage = updatedAircrRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ---------------------------------- NVIC IRQ Priority Codec Pair ------------------------------------ //

driver_status_t Codec_NVIC_ExtractIRQPriority
(
	const reg_field_t				iprFieldImage,
	const nvic_priority_group_t		priorityGroup,
	nvic_preempt_priority_t* const	pPreemptPriority,
	nvic_sub_priority_t* const		pSubPriority
)
{
	// Local Variables
	uint8_t priorityNibble = 0x00U;
	uint8_t subPriorityBits = 0x00U;
	uint8_t subPriorityMask = 0x00U;
	nvic_preempt_priority_t preemptPriority = 0x00U;
	nvic_sub_priority_t subPriority = 0x00U;

	// Validate Input and Outputs
	if ((pPreemptPriority == NULL) || (pSubPriority == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_Codec_NVIC_ValidatePriorityGroup(priorityGroup));

	//! Discard unimplemented low IPR bits before splitting the four implemented bits.
	priorityNibble = (uint8_t) (iprFieldImage >> NVIC_CODEC_PRIORITY_FIELD_SHIFT);
	subPriorityBits = (uint8_t) (NVIC_CODEC_PRIORITY_IMPLEMENTED_BITS - priorityGroup);
	subPriorityMask = _Codec_NVIC_GetPriorityLimit(subPriorityBits);

	//! Decode both logical selectors into locals so caller publication remains atomic.
	preemptPriority = (nvic_preempt_priority_t) (priorityNibble >> subPriorityBits);
	subPriority = (nvic_sub_priority_t) (priorityNibble & subPriorityMask);

	*pPreemptPriority = preemptPriority;
	*pSubPriority = subPriority;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_NVIC_StageIRQPriority
(
	reg_field_t* const				pIprFieldImage,
	const nvic_priority_group_t		priorityGroup,
	const nvic_preempt_priority_t	preemptPriority,
	const nvic_sub_priority_t		subPriority
)
{
	// Local Variables
	uint8_t preemptPriorityBits = 0x00U;
	uint8_t subPriorityBits = 0x00U;
	uint8_t preemptPriorityLimit = 0x00U;
	uint8_t subPriorityLimit = 0x00U;
	uint8_t priorityNibble = 0x00U;
	reg_field_t iprFieldImage = 0x00U;

	// Validate Input and Output
	if (pIprFieldImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_Codec_NVIC_ValidatePriorityGroup(priorityGroup));

	//! Derive independent selector widths and limits from the four-bit group split.
	preemptPriorityBits = (uint8_t) priorityGroup;
	subPriorityBits = (uint8_t) (NVIC_CODEC_PRIORITY_IMPLEMENTED_BITS - preemptPriorityBits);
	preemptPriorityLimit = _Codec_NVIC_GetPriorityLimit(preemptPriorityBits);
	subPriorityLimit = _Codec_NVIC_GetPriorityLimit(subPriorityBits);

	if ((preemptPriority > preemptPriorityLimit) || (subPriority > subPriorityLimit))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Pack both selectors into the implemented nibble and align it to IPR bits 7 through 4.
	priorityNibble = (uint8_t) ((preemptPriority << subPriorityBits) | subPriority);
	iprFieldImage = (reg_field_t) (priorityNibble << NVIC_CODEC_PRIORITY_FIELD_SHIFT);

	*pIprFieldImage = iprFieldImage;
	return DRIVER_STATUS_SUCCESS;
}
