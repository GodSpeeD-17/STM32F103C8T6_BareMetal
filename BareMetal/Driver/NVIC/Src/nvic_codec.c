/**
 * @file	nvic_codec.c
 * @author	Shrey Shah
 * @brief	NVIC Priority Codec Implementation
 * @version	v1.0
 * @date	16-08-2026
 *
 * @details
 * This source file implements pure priority-group and IRQ-priority transforms.
 * It stages caller-owned images and never accesses NVIC or SCB hardware.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "nvic_codec.h"
#include "stm32f1xx.h"

// ==================================================================================================== //
//											Local Defines											//
// ==================================================================================================== //

#define NVIC_CODEC_PRIORITY_IMPLEMENTED_BITS			((uint8_t) 0x04U)
#define NVIC_CODEC_PRIORITY_FIELD_SHIFT				((uint8_t) 0x04U)
#define NVIC_CODEC_AIRCR_GROUP_BASE					((uint8_t) 0x07U)
#define NVIC_CODEC_AIRCR_GROUP_CANONICAL_MIN		((uint8_t) 0x03U)
#define NVIC_CODEC_AIRCR_WRITE_KEY					((reg) 0x05FAUL)
#define NVIC_CODEC_AIRCR_ACTION_MASK													\
(																									\
	SCB_AIRCR_SYSRESETREQ_Msk |																\
	SCB_AIRCR_VECTCLRACTIVE_Msk |														\
	SCB_AIRCR_VECTRESET_Msk																\
)

// ==================================================================================================== //
//										Local Validation Helpers									//
// ==================================================================================================== //

/**
 * @brief Validates one logical priority-group selector
 * @param[in] priorityGroup Logical priority-group selector
 * @returns @ref driver_status_t "Priority-group validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Selector is valid
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: Selector is invalid
 */
static driver_status_t _Codec_NVIC_ValidatePriorityGroup(const nvic_priority_group_t priorityGroup)
{
	if (priorityGroup > NVIC_PRIO_GROUP_4)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Calculates the maximum selector representable by a bit count
 * @param[in] bitCount Number of implemented selector bits
 * Accepted values:
 * - `0U..4U`
 * @returns Maximum right-aligned selector value
 * @retval - `0U..15U`: Maximum value representable by @p bitCount
 */
static uint8_t _Codec_NVIC_GetPriorityLimit(const uint8_t bitCount)
{
	if (bitCount == 0x00U)
	{
		return 0x00U;
	}

	return (uint8_t) ((0x01U << bitCount) - 0x01U);
}

// ==================================================================================================== //
//									Priority Group Codec Implementation								//
// ==================================================================================================== //

driver_status_t Codec_NVIC_ExtractPriorityGroup
(
	const reg						aircrRegImage,
	nvic_priority_group_t* const	pPriorityGroup
)
{
	uint8_t rawPriorityGroup = 0x00U;
	nvic_priority_group_t priorityGroup = NVIC_PRIO_GROUP_4;

	if (pPriorityGroup == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	rawPriorityGroup = (uint8_t) ((aircrRegImage & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos);
	if (rawPriorityGroup >= NVIC_CODEC_AIRCR_GROUP_CANONICAL_MIN)
	{
		priorityGroup = (nvic_priority_group_t) (NVIC_CODEC_AIRCR_GROUP_BASE - rawPriorityGroup);
	}

	*pPriorityGroup = priorityGroup;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_NVIC_StagePriorityGroup
(
	reg* const					pAircrRegImage,
	const nvic_priority_group_t	priorityGroup
)
{
	reg updatedAircrRegImage = 0x00000000UL;
	reg rawPriorityGroup = 0x00000000UL;

	if (pAircrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_Codec_NVIC_ValidatePriorityGroup(priorityGroup));

	updatedAircrRegImage = *pAircrRegImage;
	rawPriorityGroup = (reg) (NVIC_CODEC_AIRCR_GROUP_BASE - priorityGroup);

	//! Remove the read key image, the previous grouping, and every AIRCR action request.
	updatedAircrRegImage &= ~(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk | NVIC_CODEC_AIRCR_ACTION_MASK);
	//! Insert the mandatory write key and canonical raw priority-group field.
	updatedAircrRegImage |= (NVIC_CODEC_AIRCR_WRITE_KEY << SCB_AIRCR_VECTKEY_Pos);
	updatedAircrRegImage |= (rawPriorityGroup << SCB_AIRCR_PRIGROUP_Pos);

	*pAircrRegImage = updatedAircrRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//									IRQ Priority Codec Implementation									//
// ==================================================================================================== //

driver_status_t Codec_NVIC_ExtractIRQPriority
(
	const reg_field_t				iprFieldImage,
	const nvic_priority_group_t		priorityGroup,
	nvic_preempt_priority_t* const	pPreemptPriority,
	nvic_sub_priority_t* const		pSubPriority
)
{
	uint8_t priorityNibble = 0x00U;
	uint8_t subPriorityBits = 0x00U;
	uint8_t subPriorityMask = 0x00U;
	nvic_preempt_priority_t preemptPriority = 0x00U;
	nvic_sub_priority_t subPriority = 0x00U;

	if ((pPreemptPriority == NULL) || (pSubPriority == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_Codec_NVIC_ValidatePriorityGroup(priorityGroup));

	priorityNibble = (uint8_t) (iprFieldImage >> NVIC_CODEC_PRIORITY_FIELD_SHIFT);
	subPriorityBits = (uint8_t) (NVIC_CODEC_PRIORITY_IMPLEMENTED_BITS - priorityGroup);
	subPriorityMask = _Codec_NVIC_GetPriorityLimit(subPriorityBits);
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
	uint8_t preemptPriorityBits = 0x00U;
	uint8_t subPriorityBits = 0x00U;
	uint8_t preemptPriorityLimit = 0x00U;
	uint8_t subPriorityLimit = 0x00U;
	uint8_t priorityNibble = 0x00U;
	reg_field_t iprFieldImage = 0x00U;

	if (pIprFieldImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_Codec_NVIC_ValidatePriorityGroup(priorityGroup));

	preemptPriorityBits = (uint8_t) priorityGroup;
	subPriorityBits = (uint8_t) (NVIC_CODEC_PRIORITY_IMPLEMENTED_BITS - preemptPriorityBits);
	preemptPriorityLimit = _Codec_NVIC_GetPriorityLimit(preemptPriorityBits);
	subPriorityLimit = _Codec_NVIC_GetPriorityLimit(subPriorityBits);

	if ((preemptPriority > preemptPriorityLimit) || (subPriority > subPriorityLimit))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	priorityNibble = (uint8_t) ((preemptPriority << subPriorityBits) | subPriority);
	iprFieldImage = (reg_field_t) (priorityNibble << NVIC_CODEC_PRIORITY_FIELD_SHIFT);

	*pIprFieldImage = iprFieldImage;
	return DRIVER_STATUS_SUCCESS;
}
