/**
 * @file	nvic.c
 * @author	Shrey Shah
 * @brief	NVIC Driver Implementation
 * @version	v3.1
 * @date	16-08-2026
 *
 * @details
 * @section NVIC_DRIVER_IMPL_SCOPE Scope
 * This source file implements every public function declared in `nvic.h`.
 * The Driver owns exact-target validation, register-bank routing, transaction
 * sequencing, Codec orchestration, caller-output publication, and required
 * disable synchronization.
 *
 * @section NVIC_DRIVER_IMPL_OWNERSHIP Ownership
 * Priority grouping and vector delivery are application/integration concerns.
 * Peripheral-local source enables and flags remain peer-driver concerns. This
 * implementation never reaches into a peripheral to configure or acknowledge
 * its interrupt source.
 *
 * @section NVIC_DRIVER_IMPL_TRANSACTIONS Transaction Rules
 * Action registers receive one direct write-one payload without read-modify-
 * write. Priority operations access one IPR byte. Fallible validation and
 * Codec work complete before mutation, and getter outputs publish only after
 * successful extraction.
 *
 * @section NVIC_DRIVER_IMPL_LAYOUT Source Layout
 * Local validation/routing helpers precede public implementations. Public
 * sections mirror `nvic.h`: priority grouping, IRQ priority, delivery state,
 * pending state, software trigger, and active state.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "nvic.h"
#include "nvic_codec.h"
#include "nvic_ll.h"

// ==================================================================================================== //
//									Local Driver Defines									//
// ==================================================================================================== //

/** @brief Bit shift used to divide an IRQ number by one 32-bit NVIC bank @def NVIC_IRQ_REGISTER_INDEX_SHIFT */
#define NVIC_IRQ_REGISTER_INDEX_SHIFT			((uint8_t) 0x05U)
/** @brief Mask used to select one bank-local IRQ bit position @def NVIC_IRQ_REGISTER_LOCAL_BIT_MASK */
#define NVIC_IRQ_REGISTER_LOCAL_BIT_MASK		((uint8_t) 0x1FU)

// ==================================================================================================== //
//									Local IRQ Translation Helpers									//
// ==================================================================================================== //

// --------------------------------------- Local IRQ Validation --------------------------------------- //

/**
 * @brief Validates one exact-target external IRQ number
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns @ref driver_status_t "External-IRQ validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p IRQn is supported
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 */
static driver_status_t _NVIC_ValidateIRQ(const irq_t IRQn)
{
	//! Enforce the contiguous 0-through-42 capability of the exact target.
	if (IRQn > NVIC_IRQ_NUMBER_LAST)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

// ------------------------------------ Local IRQ Bank Translation ------------------------------------ //

/**
 * @brief Returns the NVIC register-bank index for one validated IRQ number
 * @param[in] IRQn Validated external IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns Zero-based NVIC register-bank index
 * @retval - `0U`: @p IRQn is in external IRQ range 0 through 31
 * @retval - `1U`: @p IRQn is in external IRQ range 32 through 42
 * @pre Caller validated @p IRQn through _NVIC_ValidateIRQ
 */
static uint8_t _NVIC_GetIRQRegisterIndex(const irq_t IRQn)
{
	//! Divide the external IRQ number by the 32 bits represented by one bank.
	return (uint8_t) (IRQn >> NVIC_IRQ_REGISTER_INDEX_SHIFT);
}

/**
 * @brief Returns the bank-local action mask for one validated IRQ number
 * @param[in] IRQn Validated external IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns @ref reg "Register-positioned single-IRQ action mask"
 * @retval - `0x00000001UL..0x80000000UL`: Bank-local bit for @p IRQn
 * @pre Caller validated @p IRQn through _NVIC_ValidateIRQ
 */
static reg _NVIC_GetIRQActionMask(const irq_t IRQn)
{
	// Local Variable
	const uint8_t localBitPosition = (uint8_t) (IRQn & NVIC_IRQ_REGISTER_LOCAL_BIT_MASK);

	//! Convert the bank-local bit position into a single write-action mask.
	return ((reg) 0x00000001UL << localBitPosition);
}

// --------------------------------------- Local State Decode ---------------------------------------- //

/**
 * @brief Decodes one positive-polarity IRQ state bit
 * @param[in] registerImage Caller-owned NVIC state-register image
 * Accepted values:
 * - `0x00000000UL..0xFFFFFFFFUL` : Any captured NVIC state-bank image
 * @param[in] irqActionMask Register-positioned single-IRQ mask
 * Accepted values:
 * - Exactly one bank-local IRQ bit
 * @returns @ref driver_status_t "Decoded IRQ state"
 * @retval - @ref `DRIVER_STATUS_OFF`: Selected state bit is clear
 * @retval - @ref `DRIVER_STATUS_ON`: Selected state bit is set
 * @pre Caller supplies a single-bit @p irqActionMask for the selected bank
 */
static driver_status_t _NVIC_DecodeIRQState(const reg registerImage, const reg irqActionMask)
{
	//! Positive-polarity NVIC state bits map clear to OFF and set to ON.
	if ((registerImage & irqActionMask) != 0x00000000UL)
	{
		return DRIVER_STATUS_ON;
	}
	else
	{
		return DRIVER_STATUS_OFF;
	}
}

// ==================================================================================================== //
//								NVIC Priority Group Implementation								//
// ==================================================================================================== //

// ------------------------------------- NVIC Priority Group Pair ------------------------------------- //

driver_status_t NVIC_SetPriorityGroup(const nvic_priority_group_t priorityGroup)
{
	// Local Variable
	reg aircrRegImage = 0x00000000UL;

	// Validate Input
	if (priorityGroup > NVIC_PRIO_GROUP_4)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Snapshot AIRCR once, stage a safe keyed image, then commit the global group change.
	aircrRegImage = LL_SCB_ReadAIRCR();
	ASSERT_DRIVER_STATUS(Codec_NVIC_StagePriorityGroup(&aircrRegImage, priorityGroup));
	LL_SCB_WriteAIRCR(aircrRegImage);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t NVIC_GetPriorityGroup(nvic_priority_group_t* const pPriorityGroup)
{
	// Local Variables
	reg aircrRegImage = 0x00000000UL;
	nvic_priority_group_t priorityGroup = NVIC_PRIO_GROUP_4;

	// Validate Output
	if (pPriorityGroup == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Decode through local storage so the caller output publishes only after success.
	aircrRegImage = LL_SCB_ReadAIRCR();
	ASSERT_DRIVER_STATUS(Codec_NVIC_ExtractPriorityGroup(aircrRegImage, &priorityGroup));

	*pPriorityGroup = priorityGroup;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//									NVIC IRQ Priority Implementation									//
// ==================================================================================================== //

// -------------------------------------- NVIC IRQ Priority Pair -------------------------------------- //

driver_status_t NVIC_SetIRQPriority
(
	const irq_t						IRQn,
	const nvic_preempt_priority_t	preemptPriority,
	const nvic_sub_priority_t		subPriority
)
{
	// Local Variables
	reg aircrRegImage = 0x00000000UL;
	reg_field_t iprFieldImage = 0x00U;
	nvic_priority_group_t priorityGroup = NVIC_PRIO_GROUP_4;

	// Validate Input
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));
	if ((preemptPriority > NVIC_PRIORITY_VALUE_MAX) || (subPriority > NVIC_PRIORITY_VALUE_MAX))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Read the active global split before encoding one complete priority byte.
	aircrRegImage = LL_SCB_ReadAIRCR();
	ASSERT_DRIVER_STATUS(Codec_NVIC_ExtractPriorityGroup(aircrRegImage, &priorityGroup));
	ASSERT_DRIVER_STATUS
	(
		Codec_NVIC_StageIRQPriority
		(
			&iprFieldImage,
			priorityGroup,
			preemptPriority,
			subPriority
		)
	);

	//! Commit exactly one byte so neighboring IRQ priorities remain unchanged.
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
	// Local Variables
	reg aircrRegImage = 0x00000000UL;
	reg_field_t iprFieldImage = 0x00U;
	nvic_priority_group_t priorityGroup = NVIC_PRIO_GROUP_4;
	nvic_preempt_priority_t preemptPriority = 0x00U;
	nvic_sub_priority_t subPriority = 0x00U;

	// Validate Input and Outputs
	if ((pPreemptPriority == NULL) || (pSubPriority == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));

	//! Snapshot the group and selected IPR byte before decoding caller-independent locals.
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

	//! Publish both decoded selectors together only after every fallible step succeeds.
	*pPreemptPriority = preemptPriority;
	*pSubPriority = subPriority;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//								NVIC IRQ Delivery State Implementation								//
// ==================================================================================================== //

// ----------------------------------- NVIC IRQ Delivery State Family --------------------------------- //

driver_status_t NVIC_EnableIRQ(const irq_t IRQn)
{
	// Validate Input
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));

	//! Issue one direct ISER write-one-to-set action without a shared read-modify-write window.
	LL_NVIC_WriteISER
	(
		_NVIC_GetIRQRegisterIndex(IRQn),
		_NVIC_GetIRQActionMask(IRQn)
	);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t NVIC_DisableIRQ(const irq_t IRQn)
{
	// Validate Input
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));

	//! Issue the direct ICER action before synchronizing subsequent execution.
	LL_NVIC_WriteICER
	(
		_NVIC_GetIRQRegisterIndex(IRQn),
		_NVIC_GetIRQActionMask(IRQn)
	);
	__DSB();
	__ISB();

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t NVIC_GetIRQState(const irq_t IRQn, driver_status_t* const pIRQState)
{
	// Local Variables
	reg iserRegImage = 0x00000000UL;
	driver_status_t irqState = DRIVER_STATUS_OFF;

	// Validate Input and Output
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

// ==================================================================================================== //
//								NVIC IRQ Pending State Implementation								//
// ==================================================================================================== //

// ------------------------------- NVIC IRQ Pending Query and Clear Pair ------------------------------ //

driver_status_t NVIC_GetPendingIRQState(const irq_t IRQn, driver_status_t* const pPendingState)
{
	// Local Variables
	reg isprRegImage = 0x00000000UL;
	driver_status_t pendingState = DRIVER_STATUS_OFF;

	// Validate Input and Output
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
	// Validate Input
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));

	//! Issue one direct ICPR write-one-to-clear action without reading pending state.
	LL_NVIC_WriteICPR
	(
		_NVIC_GetIRQRegisterIndex(IRQn),
		_NVIC_GetIRQActionMask(IRQn)
	);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//								NVIC Software Trigger Implementation								//
// ==================================================================================================== //

// ----------------------------------- NVIC Software Trigger Action ----------------------------------- //

driver_status_t NVIC_SoftwareTriggerIRQ(const irq_t IRQn)
{
	// Validate Input
	ASSERT_DRIVER_STATUS(_NVIC_ValidateIRQ(IRQn));

	//! Issue one action-only STIR write containing the validated interrupt identifier.
	LL_NVIC_WriteSTIR(IRQn);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//								NVIC IRQ Active State Implementation								//
// ==================================================================================================== //

// ------------------------------------ NVIC IRQ Active State Query ----------------------------------- //

driver_status_t NVIC_GetActiveIRQState(const irq_t IRQn, driver_status_t* const pActiveState)
{
	// Local Variables
	reg iabrRegImage = 0x00000000UL;
	driver_status_t activeState = DRIVER_STATUS_OFF;

	// Validate Input and Output
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
