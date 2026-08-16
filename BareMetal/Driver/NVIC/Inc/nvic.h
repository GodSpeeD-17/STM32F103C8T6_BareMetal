/**
 * @file	nvic.h
 * @author	Shrey Shah
 * @brief	NVIC Driver Interface
 * @version	v3.0
 * @date	16-08-2026
 *
 * @details
 * This header exposes the application-facing STM32F103C8T6 NVIC contract.
 * Implementations live in the NVIC Driver, Codec, and LL source files; this
 * public header contains no register helpers or inline implementations.
 *
 * The application or integration layer owns global NVIC vector delivery.
 * Peripheral drivers own only their peripheral-local interrupt sources and
 * flags. Lower numerical priority values have higher interrupt urgency.
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
 * @addtogroup NVIC_Driver
 * @{
 */

// ==================================================================================================== //
//									NVIC Priority Group APIs									//
// ==================================================================================================== //

/**
 * @brief Sets the global NVIC priority grouping
 * @param[in] priorityGroup Logical priority-group selector
 * Accepted values:
 * - @ref `NVIC_PRIO_GROUP_0`
 * - @ref `NVIC_PRIO_GROUP_1`
 * - @ref `NVIC_PRIO_GROUP_2`
 * - @ref `NVIC_PRIO_GROUP_3`
 * - @ref `NVIC_PRIO_GROUP_4`
 * @returns @ref driver_status_t "Priority-group configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Priority grouping was configured
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p priorityGroup is invalid
 * @warning Priority grouping is global. Changing it reinterprets every IRQ
 * priority already stored in the NVIC and must be application-init owned.
 */
driver_status_t NVIC_SetPriorityGroup(const nvic_priority_group_t priorityGroup);

/**
 * @brief Gets the current logical NVIC priority grouping
 * @param[out] pPriorityGroup Destination for the logical priority-group selector
 * Expected values:
 * - @ref `NVIC_PRIO_GROUP_0` through @ref `NVIC_PRIO_GROUP_4`
 * @returns @ref driver_status_t "Priority-group query status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Priority grouping was returned
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPriorityGroup is `NULL`
 * @note Raw AIRCR PRIGROUP values `0U..3U` are hardware-equivalent on this
 * four-priority-bit target and are reported canonically as @ref `NVIC_PRIO_GROUP_4`.
 */
driver_status_t NVIC_GetPriorityGroup(nvic_priority_group_t* const pPriorityGroup);

// ==================================================================================================== //
//										NVIC IRQ Priority APIs										//
// ==================================================================================================== //

/**
 * @brief Configures one external IRQ logical priority
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[in] preemptPriority Logical preemption-priority selector
 * Accepted values:
 * - `0U..15U`; the effective range depends on the current priority group
 * @param[in] subPriority Logical sub-priority selector
 * Accepted values:
 * - `0U..15U`; the effective range depends on the current priority group
 * @returns @ref driver_status_t "IRQ priority configuration status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: IRQ priority was configured
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: The IRQ number or a priority
 * selector is invalid for the current priority group
 * @note Valid selector ranges depend on the current global priority group.
 */
driver_status_t NVIC_SetIRQPriority
(
	const irq_t					IRQn,
	const nvic_preempt_priority_t	preemptPriority,
	const nvic_sub_priority_t		subPriority
);

/**
 * @brief Gets one external IRQ logical priority
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[out] pPreemptPriority Destination for the decoded preemption priority
 * Expected values:
 * - `0U..15U`; the effective range depends on the current priority group
 * @param[out] pSubPriority Destination for the decoded sub-priority
 * Expected values:
 * - `0U..15U`; the effective range depends on the current priority group
 * @returns @ref driver_status_t "IRQ priority query status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Both priority values were returned
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An output pointer is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @note Neither output is modified when the operation fails.
 */
driver_status_t NVIC_GetIRQPriority
(
	const irq_t						IRQn,
	nvic_preempt_priority_t* const	pPreemptPriority,
	nvic_sub_priority_t* const		pSubPriority
);

// ==================================================================================================== //
//										NVIC IRQ State APIs										//
// ==================================================================================================== //

/**
 * @brief Enables delivery of one external IRQ
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns @ref driver_status_t "IRQ enable status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The ISER write-one-to-set action was issued
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @note This does not enable any peripheral-local interrupt source.
 */
driver_status_t NVIC_EnableIRQ(const irq_t IRQn);

/**
 * @brief Disables delivery of one external IRQ
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns @ref driver_status_t "IRQ disable status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The ICER write-one-to-clear action was synchronized
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @warning Disabling delivery does not clear pending state, silence the
 * peripheral source, or terminate an already active handler.
 */
driver_status_t NVIC_DisableIRQ(const irq_t IRQn);

/**
 * @brief Gets one external IRQ enable state
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[out] pIRQState Destination for the enable state
 * Expected values:
 * - @ref `DRIVER_STATUS_OFF`: IRQ delivery is disabled
 * - @ref `DRIVER_STATUS_ON`: IRQ delivery is enabled
 * @returns @ref driver_status_t "IRQ enable-state query status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Enable state was returned
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pIRQState is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 */
driver_status_t NVIC_GetIRQState(const irq_t IRQn, driver_status_t* const pIRQState);

/**
 * @brief Gets one external IRQ pending state
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[out] pPendingState Destination for the pending state
 * Expected values:
 * - @ref `DRIVER_STATUS_OFF`: IRQ is not pending
 * - @ref `DRIVER_STATUS_ON`: IRQ is pending
 * @returns @ref driver_status_t "IRQ pending-state query status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Pending state was returned
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPendingState is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 */
driver_status_t NVIC_GetPendingIRQState(const irq_t IRQn, driver_status_t* const pPendingState);

/**
 * @brief Clears one external IRQ pending state
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns @ref driver_status_t "IRQ pending-clear status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The ICPR write-one-to-clear action was issued
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @note This does not clear the corresponding peripheral source flag. An
 * asserted source can immediately pend the IRQ again.
 */
driver_status_t NVIC_ClearPendingIRQ(const irq_t IRQn);

/**
 * @brief Triggers one external IRQ from software
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @returns @ref driver_status_t "Software-trigger status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: The STIR action was issued
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @note Delivery remains subject to NVIC enable, priority, and processor masks.
 * @warning Unprivileged callers require `SCB->CCR.USERSETMPEND`; privileged
 * firmware can issue the request directly.
 */
driver_status_t NVIC_SoftwareTriggerIRQ(const irq_t IRQn);

/**
 * @brief Gets one external IRQ active state
 * @param[in] IRQn External IRQ number
 * Accepted values:
 * - @ref `NVIC_IRQ_NUMBER_FIRST` through @ref `NVIC_IRQ_NUMBER_LAST`
 * @param[out] pActiveState Destination for the active state
 * Expected values:
 * - @ref `DRIVER_STATUS_OFF`: IRQ handler is not active
 * - @ref `DRIVER_STATUS_ON`: IRQ handler is active or preempted and stacked
 * @returns @ref driver_status_t "IRQ active-state query status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Active state was returned
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pActiveState is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p IRQn is unsupported
 * @note The returned state is a hardware snapshot and can change immediately.
 */
driver_status_t NVIC_GetActiveIRQState(const irq_t IRQn, driver_status_t* const pActiveState);

/** @} */ // NVIC_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_H_ */
