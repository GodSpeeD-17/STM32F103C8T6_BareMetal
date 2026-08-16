/**
 * @file	nvic.c
 * @author	Shrey Shah
 * @brief	NVIC Driver Implementation
 * @version	v3.0
 * @date	16-08-2026
 *
 * @details
 * This source file owns public NVIC validation, transaction sequencing,
 * priority Codec orchestration, register routing, and disable synchronization.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "nvic.h"
#include "nvic_codec.h"
#include "nvic_ll.h"

// ==================================================================================================== //
//											Local Defines											//
// ==================================================================================================== //

#define NVIC_IRQ_REGISTER_INDEX_SHIFT				((uint8_t) 0x05U)
#define NVIC_IRQ_REGISTER_LOCAL_BIT_MASK			((uint8_t) 0x1FU)

// ==================================================================================================== //
//										Local IRQ Helpers										//
// ==================================================================================================== //

/**
 * @brief Validates one exact-target external IRQ number
 * @param[in] IRQn External IRQ number
 * @returns @ref driver_status_t "IRQ validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: IRQ number is supported
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: IRQ number is unsupported
 */
static driver_status_t _NVIC_ValidateIRQ(const irq_t IRQn)
{
	//! The exact STM32F103C8T6 capability is a contiguous external IRQ range.
	if (IRQn > NVIC_IRQ_NUMBER_LAST)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Returns the NVIC bank index for a validated IRQ number
 * @param[in] IRQn Validated external IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns Zero-based NVIC register-bank index
 * @retval - `0U..1U`: Register bank containing @p IRQn
 * @pre Caller validated @p IRQn with @ref _NVIC_ValidateIRQ.
 */
static uint8_t _NVIC_GetIRQRegisterIndex(const irq_t IRQn)
{
	//! Divide the external IRQ number by the 32 bits represented by one bank.
	return (uint8_t) (IRQn >> NVIC_IRQ_REGISTER_INDEX_SHIFT);
}

/**
 * @brief Returns the bank-local action mask for a validated IRQ number
 * @param[in] IRQn Validated external IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns Register-positioned IRQ action mask
 * @retval - `0x00000001UL..0x80000000UL`: Bank-local bit for @p IRQn
 * @pre Caller validated @p IRQn with @ref _NVIC_ValidateIRQ.
 */
static reg _NVIC_GetIRQActionMask(const irq_t IRQn)
{
	const uint8_t localBitPosition = (uint8_t) (IRQn & NVIC_IRQ_REGISTER_LOCAL_BIT_MASK);
	//! Convert the bank-local bit position into a single write-action mask.
	return ((reg) 0x00000001UL << localBitPosition);
}

/**
 * @brief Decodes one positive-polarity IRQ state bit
 * @param[in] regImage Caller-owned NVIC state-register image
 * @param[in] irqMask Register-positioned single-IRQ mask
 * @returns @ref driver_status_t "Decoded IRQ state"
 * @retval - @ref `DRIVER_STATUS_OFF`: Selected state bit is clear
 * @retval - @ref `DRIVER_STATUS_ON`: Selected state bit is set
 */
static driver_status_t _NVIC_DecodeIRQState(const reg regImage, const reg irqMask)
{
	//! Positive-polarity NVIC state bits map clear to OFF and set to ON.
	if ((regImage & irqMask) != 0x00000000UL)
	{
		return DRIVER_STATUS_ON;
	}

	return DRIVER_STATUS_OFF;
}

// ==================================================================================================== //
//									Priority Group Implementation									//
// ==================================================================================================== //

driver_status_t NVIC_SetPriorityGroup(const nvic_priority_group_t priorityGroup)
{
	reg aircrRegImage = 0x00000000UL;

	if (priorityGroup > NVIC_PRIO_GROUP_4)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Stage a safe keyed AIRCR image before committing the global group change.
	aircrRegImage = LL_SCB_ReadAIRCR();
	ASSERT_DRIVER_STATUS(Codec_NVIC_StagePriorityGroup(&aircrRegImage, priorityGroup));
	LL_SCB_WriteAIRCR(aircrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t NVIC_GetPriorityGroup(nvic_priority_group_t* const pPriorityGroup)
{
	reg aircrRegImage = 0x00000000UL;
	nvic_priority_group_t priorityGroup = NVIC_PRIO_GROUP_4;

	if (pPriorityGroup == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Decode through a local so the caller output publishes only after success.
	aircrRegImage = LL_SCB_ReadAIRCR();
	ASSERT_DRIVER_STATUS(Codec_NVIC_ExtractPriorityGroup(aircrRegImage, &priorityGroup));

	*pPriorityGroup = priorityGroup;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//									IRQ Priority Implementation									//
// ==================================================================================================== //

driver_status_t NVIC_SetIRQPriority
(
	const irq_t					IRQn,
	const nvic_preempt_priority_t	preemptPriority,
	const nvic_sub_priority_t		subPriority
)
{
	reg aircrRegImage = 0x00000000UL;
	reg_field_t iprFieldImage = 0x00U;
	nvic_priority_group_t priorityGroup = NVIC_PRIO_GROUP_4;

	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));
	if ((preemptPriority > NVIC_PRIORITY_VALUE_MAX) || (subPriority > NVIC_PRIORITY_VALUE_MAX))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Read the active global split before encoding and writing one priority byte.
	aircrRegImage = LL_SCB_ReadAIRCR();
	ASSERT_DRIVER_STATUS(Codec_NVIC_ExtractPriorityGroup(aircrRegImage, &priorityGroup));
	ASSERT_DRIVER_STATUS
	(
		Codec_NVIC_StageIRQPriority(&iprFieldImage, priorityGroup, preemptPriority, subPriority)
	);
	LL_NVIC_WriteIPR(IRQn, iprFieldImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t NVIC_GetIRQPriority
(
	const irq_t						IRQn,
	nvic_preempt_priority_t* const	pPreemptPriority,
	nvic_sub_priority_t* const		pSubPriority
)
{
	reg aircrRegImage = 0x00000000UL;
	reg_field_t iprFieldImage = 0x00U;
	nvic_priority_group_t priorityGroup = NVIC_PRIO_GROUP_4;
	nvic_preempt_priority_t preemptPriority = 0x00U;
	nvic_sub_priority_t subPriority = 0x00U;

	if ((pPreemptPriority == NULL) || (pSubPriority == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));

	//! Capture both hardware images before decoding into caller-independent locals.
	aircrRegImage = LL_SCB_ReadAIRCR();
	ASSERT_DRIVER_STATUS(Codec_NVIC_ExtractPriorityGroup(aircrRegImage, &priorityGroup));
	iprFieldImage = LL_NVIC_ReadIPR(IRQn);
	ASSERT_DRIVER_STATUS
	(
		Codec_NVIC_ExtractIRQPriority
		(
			iprFieldImage,
			priorityGroup,
			&preemptPriority,
			&subPriority
		)
	);

	*pPreemptPriority = preemptPriority;
	*pSubPriority = subPriority;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										IRQ State Implementation									//
// ==================================================================================================== //

driver_status_t NVIC_EnableIRQ(const irq_t IRQn)
{
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));
	//! Issue one direct ISER write-one-to-set action for the selected IRQ.
	LL_NVIC_WriteISER(_NVIC_GetIRQRegisterIndex(IRQn), _NVIC_GetIRQActionMask(IRQn));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t NVIC_DisableIRQ(const irq_t IRQn)
{
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));
	//! Synchronize the direct ICER action before subsequent execution continues.
	LL_NVIC_WriteICER(_NVIC_GetIRQRegisterIndex(IRQn), _NVIC_GetIRQActionMask(IRQn));
	__DSB();
	__ISB();

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t NVIC_GetIRQState(const irq_t IRQn, driver_status_t* const pIRQState)
{
	reg iserRegImage = 0x00000000UL;
	driver_status_t irqState = DRIVER_STATUS_OFF;

	if (pIRQState == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));

	//! Read and decode only the enable-state bank containing the selected IRQ.
	iserRegImage = LL_NVIC_ReadISER(_NVIC_GetIRQRegisterIndex(IRQn));
	irqState = _NVIC_DecodeIRQState(iserRegImage, _NVIC_GetIRQActionMask(IRQn));

	*pIRQState = irqState;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t NVIC_GetPendingIRQState(const irq_t IRQn, driver_status_t* const pPendingState)
{
	reg isprRegImage = 0x00000000UL;
	driver_status_t pendingState = DRIVER_STATUS_OFF;

	if (pPendingState == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));

	//! Read and decode only the pending-state bank containing the selected IRQ.
	isprRegImage = LL_NVIC_ReadISPR(_NVIC_GetIRQRegisterIndex(IRQn));
	pendingState = _NVIC_DecodeIRQState(isprRegImage, _NVIC_GetIRQActionMask(IRQn));

	*pPendingState = pendingState;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t NVIC_ClearPendingIRQ(const irq_t IRQn)
{
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));
	//! Issue one direct ICPR write-one-to-clear action for the selected IRQ.
	LL_NVIC_WriteICPR(_NVIC_GetIRQRegisterIndex(IRQn), _NVIC_GetIRQActionMask(IRQn));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t NVIC_SoftwareTriggerIRQ(const irq_t IRQn)
{
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));
	//! Issue one action-only STIR write with the validated interrupt identifier.
	LL_NVIC_WriteSTIR(IRQn);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t NVIC_GetActiveIRQState(const irq_t IRQn, driver_status_t* const pActiveState)
{
	reg iabrRegImage = 0x00000000UL;
	driver_status_t activeState = DRIVER_STATUS_OFF;

	if (pActiveState == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));

	//! Read and decode only the active-state bank containing the selected IRQ.
	iabrRegImage = LL_NVIC_ReadIABR(_NVIC_GetIRQRegisterIndex(IRQn));
	activeState = _NVIC_DecodeIRQState(iabrRegImage, _NVIC_GetIRQActionMask(IRQn));

	*pActiveState = activeState;
	return DRIVER_STATUS_SUCCESS;
}
