/**
 * @file	nvic_codec.h
 * @author	Shrey Shah
 * @brief	NVIC Priority Codec Interface
 * @version	v1.0
 * @date	16-08-2026
 *
 * @details
 * The NVIC Codec translates logical priority-group and IRQ-priority selectors
 * to and from caller-owned register images. Codec APIs never access hardware.
 */

// Header Guards
#ifndef NVIC_CODEC_H_
#define NVIC_CODEC_H_

#include "nvic_defines.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup NVIC_03_Codec NVIC Priority Codec
 * @ingroup NVIC_Driver
 * @brief Pure NVIC priority encoding, decoding, and register-image staging
 * @{
 */

/**
 * @brief Extracts the logical priority group from an AIRCR image
 * @param[in] aircrRegImage Caller-owned AIRCR image
 * @param[out] pPriorityGroup Destination for the decoded logical group
 * @returns @ref driver_status_t "Extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Logical group was extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pPriorityGroup is `NULL`
 * @note Raw PRIGROUP values `0U..3U` are canonicalized to Group 4.
 */
driver_status_t Codec_NVIC_ExtractPriorityGroup
(
	const reg					aircrRegImage,
	nvic_priority_group_t* const	pPriorityGroup
);

/**
 * @brief Stages one logical priority group into an AIRCR image
 * @param[in,out] pAircrRegImage Caller-owned AIRCR image to update
 * @param[in] priorityGroup Logical priority-group selector
 * @returns @ref driver_status_t "Staging status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Group and write key were staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pAircrRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p priorityGroup is invalid
 * @note Reset/action request bits are cleared in the staged image.
 */
driver_status_t Codec_NVIC_StagePriorityGroup
(
	reg* const					pAircrRegImage,
	const nvic_priority_group_t	priorityGroup
);

/**
 * @brief Decodes one IPR byte into logical priority selectors
 * @param[in] iprFieldImage Raw IPR byte image
 * @param[in] priorityGroup Logical priority group used for decoding
 * @param[out] pPreemptPriority Destination for the preemption priority
 * @param[out] pSubPriority Destination for the sub-priority
 * @returns @ref driver_status_t "Extraction status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Both selectors were extracted
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An output pointer is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p priorityGroup is invalid
 * @note Neither output is modified when extraction fails.
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
 * @param[out] pIprFieldImage Destination for the complete IPR byte image
 * @param[in] priorityGroup Logical priority group used for encoding
 * @param[in] preemptPriority Logical preemption priority
 * @param[in] subPriority Logical sub-priority
 * @returns @ref driver_status_t "Staging status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: IPR image was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pIprFieldImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: A selector is invalid
 * @note @p pIprFieldImage is not modified when staging fails.
 */
driver_status_t Codec_NVIC_StageIRQPriority
(
	reg_field_t* const				pIprFieldImage,
	const nvic_priority_group_t		priorityGroup,
	const nvic_preempt_priority_t	preemptPriority,
	const nvic_sub_priority_t		subPriority
);

/** @} */ // NVIC_03_Codec

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVIC_CODEC_H_ */
