/**
 * @file	nvic.h
 * @author	Shrey Shah
 * @brief	NVIC Driver Public Interface
 * @version	v3.1
 * @date	16-08-2026
 *
 * @details
 * This header exposes the application-facing STM32F103C8T6 NVIC contract for
 * the 43 implemented maskable external interrupts. Cortex-M3 processor
 * exceptions remain SCB-owned and are outside this public external-IRQ API.
 *
 * APIs are grouped in the same order as `nvic.c`: global priority grouping,
 * per-IRQ priority, delivery enable state, pending state, software triggering,
 * and active state. Register mechanics and raw encodings remain in the Codec
 * and LL layers, so this public header contains declarations only.
 *
 * @see @ref NVIC_Peripheral_Guide "STM32F103C8T6 NVIC Architecture"
 */

// Header Guards
#ifndef NVIC_H_
#define NVIC_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "nvic_defines.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup NVIC_03_Driver
 * @{
 */

// ==================================================================================================== //
//									NVIC Priority Group APIs									//
// ==================================================================================================== //

// ------------------------------------- NVIC Priority Group Pair ------------------------------------- //

/**
 * @brief Sets the global NVIC priority grouping
 * @details
 * Reads `SCB_AIRCR`, stages the requested canonical `PRIGROUP` encoding and
 * mandatory write key through the Codec, clears AIRCR reset/action request
 * bits from the write image, and commits one AIRCR write. The operation changes
 * only the interpretation of stored IPR values; it does not rewrite them.
 *
 * @param[in] priorityGroup Logical NVIC priority-group selector
 * Accepted values:
 * - @ref `NVIC_PRIO_GROUP_0` : Zero preemption bits and four sub-priority bits
 * - @ref `NVIC_PRIO_GROUP_1` : One preemption bit and three sub-priority bits
 * - @ref `NVIC_PRIO_GROUP_2` : Two preemption bits and two sub-priority bits
 * - @ref `NVIC_PRIO_GROUP_3` : Three preemption bits and one sub-priority bit
 * - @ref `NVIC_PRIO_GROUP_4` : Four preemption bits and zero sub-priority bits
 * @returns @ref driver_status_t "Priority-group configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Priority grouping was configured
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p priorityGroup is invalid
 * @pre The application has exclusive ownership of global priority configuration
 * @warning Changing the global group immediately reinterprets every IRQ
 * priority already stored in the NVIC. Configure grouping during platform
 * initialization before configuring per-IRQ priorities
 */
driver_status_t NVIC_SetPriorityGroup(const nvic_priority_group_t priorityGroup);

/**
 * @brief Gets the current logical NVIC priority grouping
 * @details
 * Reads one `SCB_AIRCR` image and decodes its raw `PRIGROUP` field through the
 * Codec. The destination is published only after successful validation and
 * extraction.
 *
 * @param[out] pPriorityGroup Destination for the logical priority-group selector
 * Expected values:
 * - @ref `NVIC_PRIO_GROUP_0` : Zero preemption bits and four sub-priority bits
 * - @ref `NVIC_PRIO_GROUP_1` : One preemption bit and three sub-priority bits
 * - @ref `NVIC_PRIO_GROUP_2` : Two preemption bits and two sub-priority bits
 * - @ref `NVIC_PRIO_GROUP_3` : Three preemption bits and one sub-priority bit
 * - @ref `NVIC_PRIO_GROUP_4` : Four preemption bits and zero sub-priority bits
 * @returns @ref driver_status_t "Priority-group query status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Priority grouping was returned
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPriorityGroup is `NULL`
 * @note Raw AIRCR `PRIGROUP` values `0U..3U` are hardware-equivalent on this
 * four-priority-bit target and are reported canonically as @ref `NVIC_PRIO_GROUP_4`
 * @note @p pPriorityGroup is not modified when the operation fails
 * @warning The result is a hardware snapshot and can become stale if another
 * owner changes global grouping concurrently
 */
driver_status_t NVIC_GetPriorityGroup(nvic_priority_group_t* const pPriorityGroup);

// ==================================================================================================== //
//										NVIC IRQ Priority APIs										//
// ==================================================================================================== //

// -------------------------------------- NVIC IRQ Priority Pair -------------------------------------- //

/**
 * @brief Configures one external IRQ logical priority
 * @details
 * Reads the active global priority group, encodes the two logical selectors,
 * and writes exactly one IPR byte. Neighboring IRQ priority bytes are never
 * read or rewritten. Validation and Codec staging complete before the IPR
 * write, so an error performs no NVIC priority write.
 *
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[in] preemptPriority Logical preemption-priority selector
 * Accepted values:
 * - `0U` for @ref `NVIC_PRIO_GROUP_0`
 * - `0U..1U` for @ref `NVIC_PRIO_GROUP_1`
 * - `0U..3U` for @ref `NVIC_PRIO_GROUP_2`
 * - `0U..7U` for @ref `NVIC_PRIO_GROUP_3`
 * - `0U..15U` for @ref `NVIC_PRIO_GROUP_4`
 * @param[in] subPriority Logical sub-priority selector
 * Accepted values:
 * - `0U..15U` for @ref `NVIC_PRIO_GROUP_0`
 * - `0U..7U` for @ref `NVIC_PRIO_GROUP_1`
 * - `0U..3U` for @ref `NVIC_PRIO_GROUP_2`
 * - `0U..1U` for @ref `NVIC_PRIO_GROUP_3`
 * - `0U` for @ref `NVIC_PRIO_GROUP_4`
 * @returns @ref driver_status_t "IRQ-priority configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: IRQ priority was configured
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn or a priority selector is invalid for the active group
 * @pre Global priority grouping is configured and remains stable for the transaction
 * @note Lower numerical priority values have higher interrupt urgency
 * @warning Concurrent priority-group mutation can make the encoded priority
 * inconsistent with the grouping intended by the caller
 */
driver_status_t NVIC_SetIRQPriority
(
	const irq_t						IRQn,
	const nvic_preempt_priority_t	preemptPriority,
	const nvic_sub_priority_t		subPriority
);

/**
 * @brief Gets one external IRQ logical priority
 * @details
 * Snapshots the current global group and exactly one IPR byte, decodes both
 * logical selectors through local storage, and publishes both outputs only
 * after successful extraction.
 *
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[out] pPreemptPriority Destination for the decoded preemption priority
 * Expected values:
 * - `0U`, `0U..1U`, `0U..3U`, `0U..7U`, or `0U..15U` according to the active group
 * @param[out] pSubPriority Destination for the decoded sub-priority
 * Expected values:
 * - `0U..15U`, `0U..7U`, `0U..3U`, `0U..1U`, or `0U` according to the active group
 * @returns @ref driver_status_t "IRQ-priority query status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Both priority selectors were returned
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An output pointer is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @note Neither output is modified when the operation fails
 * @warning The two hardware reads are not an atomic snapshot relative to a
 * concurrent global priority-group change
 */
driver_status_t NVIC_GetIRQPriority
(
	const irq_t						IRQn,
	nvic_preempt_priority_t* const	pPreemptPriority,
	nvic_sub_priority_t* const		pSubPriority
);

// ==================================================================================================== //
//									NVIC IRQ Delivery State APIs									//
// ==================================================================================================== //

// ----------------------------------- NVIC IRQ Delivery State Family --------------------------------- //

/**
 * @brief Enables delivery of one external IRQ
 * @details
 * Issues one direct ISER write-one-to-set action for the selected IRQ. The
 * action does not read or rewrite neighboring enable bits.
 *
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns @ref driver_status_t "IRQ-delivery enable status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The ISER write-one-to-set action was issued
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @note This operation does not enable any peripheral-local interrupt source
 * or clear stale peripheral/NVIC pending state
 */
driver_status_t NVIC_EnableIRQ(const irq_t IRQn);

/**
 * @brief Disables delivery of one external IRQ
 * @details
 * Issues one direct ICER write-one-to-clear action followed by DSB and ISB so
 * subsequent execution observes the synchronized delivery-disable request.
 *
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns @ref driver_status_t "IRQ-delivery disable status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The ICER action and barriers completed
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @warning Disabling delivery does not clear pending state, silence the
 * peripheral source, terminate an already active handler, or prove that an
 * already accepted exception has quiesced
 */
driver_status_t NVIC_DisableIRQ(const irq_t IRQn);

/**
 * @brief Gets one external IRQ delivery-enable state
 * @details
 * Reads only the ISER bank containing the selected IRQ and decodes its
 * positive-polarity enable bit.
 *
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[out] pIRQState Destination for the enable state
 * Expected values:
 * - @ref `DRIVER_STATUS_OFF` : IRQ delivery is disabled
 * - @ref `DRIVER_STATUS_ON` : IRQ delivery is enabled
 * @returns @ref driver_status_t "IRQ-delivery state query status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Enable state was returned
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pIRQState is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @note @p pIRQState is not modified when the operation fails
 * @note The returned state is a hardware snapshot and can change immediately
 */
driver_status_t NVIC_GetIRQState(const irq_t IRQn, driver_status_t* const pIRQState);

// ==================================================================================================== //
//									NVIC IRQ Pending State APIs									//
// ==================================================================================================== //

// ------------------------------- NVIC IRQ Pending Query and Clear Pair ------------------------------ //

/**
 * @brief Gets one external IRQ pending state
 * @details
 * Reads only the ISPR bank containing the selected IRQ and decodes its
 * positive-polarity pending bit without changing pending state.
 *
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[out] pPendingState Destination for the pending state
 * Expected values:
 * - @ref `DRIVER_STATUS_OFF` : IRQ is not pending
 * - @ref `DRIVER_STATUS_ON` : IRQ is pending
 * @returns @ref driver_status_t "IRQ-pending state query status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pending state was returned
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPendingState is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @note @p pPendingState is not modified when the operation fails
 * @note The returned state is a hardware snapshot and can change immediately
 */
driver_status_t NVIC_GetPendingIRQState(const irq_t IRQn, driver_status_t* const pPendingState);

/**
 * @brief Clears one external IRQ pending state
 * @details
 * Issues one direct ICPR write-one-to-clear action for the selected IRQ. The
 * action does not read or rewrite neighboring pending bits.
 *
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns @ref driver_status_t "IRQ-pending clear status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The ICPR write-one-to-clear action was issued
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @note This operation does not acknowledge the corresponding peripheral
 * source flag. An asserted source can immediately pend the IRQ again
 */
driver_status_t NVIC_ClearPendingIRQ(const irq_t IRQn);

// ==================================================================================================== //
//									NVIC Software Trigger API									//
// ==================================================================================================== //

// ----------------------------------- NVIC Software Trigger Action ----------------------------------- //

/**
 * @brief Triggers one external IRQ from software
 * @details
 * Issues one action-only STIR write containing the validated external IRQ
 * number. The request may become pending while delivery is disabled.
 *
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns @ref driver_status_t "Software-trigger action status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The STIR action was issued
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @note Delivery remains subject to NVIC enable, priority, and processor masks
 * @warning Unprivileged callers require the `USERSETMPEND` bit in `SCB->CCR`;
 * privileged firmware can issue the request directly
 */
driver_status_t NVIC_SoftwareTriggerIRQ(const irq_t IRQn);

// ==================================================================================================== //
//									NVIC IRQ Active State API									//
// ==================================================================================================== //

// ------------------------------------ NVIC IRQ Active State Query ----------------------------------- //

/**
 * @brief Gets one external IRQ active state
 * @details
 * Reads only the IABR bank containing the selected IRQ and decodes its
 * positive-polarity active bit. Active includes a handler that was preempted
 * and remains stacked.
 *
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[out] pActiveState Destination for the active state
 * Expected values:
 * - @ref `DRIVER_STATUS_OFF` : IRQ handler is not active
 * - @ref `DRIVER_STATUS_ON` : IRQ handler is active or preempted and stacked
 * @returns @ref driver_status_t "IRQ-active state query status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Active state was returned
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pActiveState is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @note @p pActiveState is not modified when the operation fails
 * @note The returned state is a hardware snapshot and can change immediately
 */
driver_status_t NVIC_GetActiveIRQState(const irq_t IRQn, driver_status_t* const pActiveState);

/** @} */ // NVIC_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_H_ */
