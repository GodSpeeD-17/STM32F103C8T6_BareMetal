/**
 * @file	nvic_codec.h
 * @author	Shrey Shah
 * @brief	NVIC Priority Codec Interface
 * @version	v1.1
 * @date	16-08-2026
 *
 * @details
 * @section NVIC_CODEC_SCOPE Scope
 * This header defines the pure representation layer used by the NVIC Driver.
 * Codec APIs translate logical priority groups and separate preemption/sub-
 * priority selectors to and from caller-owned AIRCR and IPR images.
 *
 * @section NVIC_CODEC_AUTHORITY Authority
 * Codec owns raw field translation, canonical alias handling, range validation,
 * unrelated-bit preservation, and failure-atomic publication. It never reads
 * or writes NVIC/SCB hardware, performs delivery actions, or decides application
 * ownership and sequencing.
 *
 * @section NVIC_CODEC_LAYOUT Interface Layout
 * Priority-group Extract/Stage functions appear first, followed by per-IRQ
 * priority Extract/Stage functions, matching `nvic_codec.c`.
 */

// Header Guards
#ifndef NVIC_CODEC_H_
#define NVIC_CODEC_H_

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

/**
 * @brief NVIC priority translation, extraction, and staging APIs
 * @defgroup NVIC_03_Driver_03_Codec NVIC Priority Codec
 * @ingroup NVIC_03_Driver
 * @details
 * Stage APIs mutate only caller-owned local register images and publish them
 * only after every validation succeeds. Extract APIs likewise decode through
 * local storage before publishing caller outputs.
 * @{
 */

// ==================================================================================================== //
//							NVIC Priority Configuration Codecs							//
// ==================================================================================================== //

// --------------------------------- NVIC Priority Group Codec Pair ---------------------------------- //

/**
 * @brief NVIC priority-group register-image Codec pair
 * @defgroup NVIC_03_Driver_03_Codec_01_PriorityGroup NVIC Priority-Group Codec Pair
 * @ingroup NVIC_03_Driver_03_Codec
 * @details
 * This pair translates between the logical priority-group selector and the
 * corresponding caller-owned `AIRCR.PRIGROUP` register image.
 * @{
 */

/**
 * @brief Extracts the logical priority group from an AIRCR image
 * @details
 * Decodes `AIRCR.PRIGROUP` without hardware access. Raw values `0U..3U` are
 * equivalent when four priority bits are implemented and are canonicalized to
 * @ref `NVIC_PRIO_GROUP_4`.
 *
 * @param[in] aircrRegImage Caller-owned complete AIRCR image
 * Accepted values:
 * - `0x00000000UL..0xFFFFFFFFUL` : Any captured AIRCR image
 * @param[out] pPriorityGroup Destination for the decoded logical group
 * Expected values:
 * - @ref `NVIC_PRIO_GROUP_0` through @ref `NVIC_PRIO_GROUP_4`
 * @returns @ref driver_status_t "Priority-group extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Logical priority group was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPriorityGroup is `NULL`
 * @note @p pPriorityGroup is not modified when extraction fails
 */
driver_status_t Codec_NVIC_ExtractPriorityGroup
(
	const reg						aircrRegImage,
	nvic_priority_group_t* const	pPriorityGroup
);

/**
 * @brief Stages one logical priority group into an AIRCR image
 * @details
 * Copies the caller image, removes the read-key image, existing `PRIGROUP`, and
 * AIRCR reset/action request bits, then inserts write key `0x5FA` and the
 * canonical raw priority-group encoding. Every unrelated writable image bit is
 * preserved.
 *
 * @param[in,out] pAircrRegImage Caller-owned complete AIRCR image to update
 * Expected values:
 * - Non-`NULL` : Local Driver-owned @ref reg image, never live MMIO
 * @param[in] priorityGroup Logical priority-group selector
 * Accepted values:
 * - @ref `NVIC_PRIO_GROUP_0`
 * - @ref `NVIC_PRIO_GROUP_1`
 * - @ref `NVIC_PRIO_GROUP_2`
 * - @ref `NVIC_PRIO_GROUP_3`
 * - @ref `NVIC_PRIO_GROUP_4`
 * @returns @ref driver_status_t "Priority-group staging status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Priority group and AIRCR write key were staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pAircrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p priorityGroup is invalid
 * @note @p pAircrRegImage is not modified when staging fails
 * @warning The staged image is suitable for an AIRCR priority-group write; the
 * reset/action request bits are deliberately cleared to prevent side effects
 */
driver_status_t Codec_NVIC_StagePriorityGroup
(
	reg* const						pAircrRegImage,
	const nvic_priority_group_t		priorityGroup
);

/** @} */ // NVIC_03_Driver_03_Codec_01_PriorityGroup

// ---------------------------------- NVIC IRQ Priority Codec Pair ------------------------------------ //

/**
 * @brief NVIC per-IRQ priority register-image Codec pair
 * @defgroup NVIC_03_Driver_03_Codec_02_IRQPriority NVIC IRQ-Priority Codec Pair
 * @ingroup NVIC_03_Driver_03_Codec
 * @details
 * This pair translates between logical preemption/sub-priority selectors and
 * one caller-owned `IPR` byte image under the selected priority grouping.
 * @{
 */

/**
 * @brief Decodes one IPR byte into logical priority selectors
 * @details
 * Uses the supplied logical group to split implemented IPR bits 7 through 4
 * into independent preemption and sub-priority values. Unimplemented IPR bits
 * 3 through 0 are ignored.
 *
 * @param[in] iprFieldImage Caller-owned raw IPR byte image
 * Accepted values:
 * - `0x00U..0xFFU` : Any captured IPR byte image
 * @param[in] priorityGroup Logical priority group used for decoding
 * Accepted values:
 * - @ref `NVIC_PRIO_GROUP_0` through @ref `NVIC_PRIO_GROUP_4`
 * @param[out] pPreemptPriority Destination for the decoded preemption priority
 * Expected values:
 * - `0U..15U` constrained by @p priorityGroup
 * @param[out] pSubPriority Destination for the decoded sub-priority
 * Expected values:
 * - `0U..15U` constrained by @p priorityGroup
 * @returns @ref driver_status_t "IRQ-priority extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Both logical priority selectors were extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An output pointer is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p priorityGroup is invalid
 * @note Neither output is modified when extraction fails
 */
driver_status_t Codec_NVIC_ExtractIRQPriority
(
	const reg_field_t				iprFieldImage,
	const nvic_priority_group_t		priorityGroup,
	nvic_preempt_priority_t* const	pPreemptPriority,
	nvic_sub_priority_t* const		pSubPriority
);

/**
 * @brief Encodes logical priority selectors into one IPR byte image
 * @details
 * Validates both selectors against the supplied four-bit group split, packs
 * them into implemented bits 7 through 4, and clears unimplemented bits 3
 * through 0 in the complete staged byte image.
 *
 * @param[out] pIprFieldImage Destination for the complete staged IPR byte image
 * Expected values:
 * - Non-`NULL` : Local Driver-owned @ref reg_field_t image, never live MMIO
 * @param[in] priorityGroup Logical priority group used for encoding
 * Accepted values:
 * - @ref `NVIC_PRIO_GROUP_0` through @ref `NVIC_PRIO_GROUP_4`
 * @param[in] preemptPriority Logical preemption priority
 * Accepted values:
 * - `0U..15U` constrained by @p priorityGroup
 * @param[in] subPriority Logical sub-priority
 * Accepted values:
 * - `0U..15U` constrained by @p priorityGroup
 * @returns @ref driver_status_t "IRQ-priority staging status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Complete IPR byte image was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pIprFieldImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A group or priority selector is invalid
 * @note @p pIprFieldImage is not modified when staging fails
 */
driver_status_t Codec_NVIC_StageIRQPriority
(
	reg_field_t* const				pIprFieldImage,
	const nvic_priority_group_t		priorityGroup,
	const nvic_preempt_priority_t	preemptPriority,
	const nvic_sub_priority_t		subPriority
);

/** @} */ // NVIC_03_Driver_03_Codec_02_IRQPriority

/** @} */ // NVIC_03_Driver_03_Codec

/** @} */ // NVIC_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_CODEC_H_ */
