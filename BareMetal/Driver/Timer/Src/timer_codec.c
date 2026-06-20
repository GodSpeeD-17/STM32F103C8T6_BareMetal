/**
 * @file	timer_codec.c
 * @author	Shrey Shah
 * @brief	Timer Selector Codec Implementation
 * @version	v1.0
 * @date	07-06-2026
 *
 * @details
 * This source file implements the Timer codec layer. It encodes driver-facing
 * Timer selectors into raw STM32F1 Timer fields, decodes raw fields back into
 * driver-facing selectors, and returns updated caller-owned register images.
 * It does not read or write peripheral hardware.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "timer_codec.h"

// ==================================================================================================== //
//												Local Defines											//
// ==================================================================================================== //

/** @brief Width of a one-bit Timer register field @def TIM_CODEC_FIELD_WIDTH_1BIT */
#define TIM_CODEC_FIELD_WIDTH_1BIT							((reg_field_width_t) 0x01U)
/** @brief Width of a two-bit Timer register field @def TIM_CODEC_FIELD_WIDTH_2BIT */
#define TIM_CODEC_FIELD_WIDTH_2BIT							((reg_field_width_t) 0x02U)
/** @brief Width of a three-bit Timer register field @def TIM_CODEC_FIELD_WIDTH_3BIT */
#define TIM_CODEC_FIELD_WIDTH_3BIT							((reg_field_width_t) 0x03U)
/** @brief All Timer status flags available on general-purpose timers @def TIM_CODEC_SR_GENERAL_PURPOSE_FLAG_MASK */
#define TIM_CODEC_SR_GENERAL_PURPOSE_FLAG_MASK						\
(																	\
	TIM_SR_UIF		| TIM_SR_CC1IF	| TIM_SR_CC2IF	|				\
	TIM_SR_CC3IF	| TIM_SR_CC4IF	| TIM_SR_TIF	|				\
	TIM_SR_CC1OF	| TIM_SR_CC2OF	| TIM_SR_CC3OF	| TIM_SR_CC4OF	\
)

// ==================================================================================================== //
//										Local Register Image Helpers									//
// ==================================================================================================== //

// ==================================================================================================== //
//										Local Binary State Image Helpers								//
// ==================================================================================================== //

/**
 * @brief Validates whether a state selector is an accepted ON/OFF state
 * @param[in] state Driver state selector
 * @returns Validation status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p state is accepted
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p state is not @ref `DRIVER_STATUS_OFF` or @ref `DRIVER_STATUS_ON`
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_ValidateState(const driver_status_t state)
{
	//! Codec binary state helpers accept only explicit OFF/ON states, never generic SUCCESS/ERROR states.
	if ((state != DRIVER_STATUS_OFF) && (state != DRIVER_STATUS_ON))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Extracts one positive-polarity bit state from a register image
 * @param[in] regImage Caller-owned register image
 * @param[in] bitMask Register-positioned bit mask
 * @returns Decoded state
 * @retval - @ref `DRIVER_STATUS_OFF`: @p bitMask is clear in @p regImage
 * @retval - @ref `DRIVER_STATUS_ON`: @p bitMask is set in @p regImage
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_ExtractBitStateFromImage(const reg regImage, const reg bitMask)
{
	//! Positive-polarity hardware bit convention: clear means OFF, set means ON.
	return ((regImage & bitMask) != 0x00000000UL) ? DRIVER_STATUS_ON : DRIVER_STATUS_OFF;
}

/**
 * @brief Stages one positive-polarity bit state inside a register image
 * @param[in] regImage Caller-owned register image before replacement
 * @param[in] bitMask Register-positioned bit mask
 * @param[in] state Requested ON/OFF state
 * @param[out] pRegImage Destination for updated register image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: State was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p state is not accepted
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_StageBitStateInImage
(
	const reg					regImage,
	const reg					bitMask,
	const driver_status_t		state,
	reg* const					pRegImage
)
{
	// Local Variable
	reg bitSet = 0x00000000UL;

	// Validate Input
	if (pRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_TIM_ValidateState(state));

	//! Convert the driver ON/OFF state into the raw bit value and stage only that bit.
	bitSet = (state == DRIVER_STATUS_ON) ? bitMask : 0x00000000UL;
	*pRegImage = RegOps_StageField(regImage, bitMask, bitSet);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local Scalar Field Image Helpers								//
// ==================================================================================================== //

/**
 * @brief Extracts one right-aligned scalar field from a register image
 * @param[in] regImage Caller-owned register image
 * @param[in] fieldMask Register-positioned field mask
 * @param[in] fieldPos Zero-based field bit position
 * @returns Right-aligned scalar value as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_ExtractScalarField
(
	const reg					regImage,
	const reg					fieldMask,
	const reg_bit_pos_t			fieldPos
)
{
	//! PSC/ARR/CNT are register-backed scalar fields; extract them through the Core field helper.
	return RegOps_ExtractFieldValue(regImage, fieldMask, fieldPos);
}

/**
 * @brief Stages one right-aligned scalar field inside a register image
 * @param[in] regImage Caller-owned register image before replacement
 * @param[in] fieldMask Register-positioned field mask
 * @param[in] fieldPos Zero-based field bit position
 * @param[in] value Right-aligned scalar value
 * @param[out] pRegImage Destination for updated register image
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Scalar field was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRegImage is `NULL`
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_StageScalarField
(
	const reg					regImage,
	const reg					fieldMask,
	const reg_bit_pos_t			fieldPos,
	const reg					value,
	reg* const					pRegImage
)
{
	if (pRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Pack the right-aligned value into its hardware field position, then replace only that field.
	*pRegImage = RegOps_StageField(regImage, fieldMask, REG_FIELD_VALUE(fieldPos, value));
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local Channel Index Helpers									//
// ==================================================================================================== //

/**
 * @brief Decodes a Timer single-channel mask into a zero-based channel index
 * @param[in] channel Timer single-channel mask
 * @param[out] pChannelIndex Destination for decoded channel index
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Channel index was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pChannelIndex is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not exactly one valid channel
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_GetChannelIndexFromMask
(
	const timer_channel_t			channel,
	timer_channel_index_t* const	pChannelIndex
)
{
	if (pChannelIndex == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	*pChannelIndex = TIM_ChannelMaskToIndex(channel);
	if (*pChannelIndex == TIM_CHANNEL_INDEX_INVALID)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! From this point onward the codec works with indexes because register fields are index-positioned.
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local CCMR Field Position Helpers								//
// ==================================================================================================== //

/**
 * @brief Returns the hardware `CCxS` field position for one channel index
 * @param[in] channelIndex Zero-based channel index
 * @returns Register-positioned `CCxS` bit position as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_GetCCMRCcsPos(const timer_channel_index_t channelIndex)
{
	reg fieldPos = (reg) TIM_CCMR1_CC1S_Pos;

	//! Map public channel indexes to concrete CCMR field positions owned by the Timer register layer.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = (reg) TIM_CCMR1_CC1S_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = (reg) TIM_CCMR1_CC2S_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = (reg) TIM_CCMR2_CC3S_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = (reg) TIM_CCMR2_CC4S_Pos;
			break;
		}
		default:
		{
			break;
		}
	}

	return fieldPos;
}

/**
 * @brief Returns the hardware `OCxFE` field position for one channel index
 * @param[in] channelIndex Zero-based channel index
 * @returns Register-positioned `OCxFE` bit position as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_GetCCMROcFastPos(const timer_channel_index_t channelIndex)
{
	reg fieldPos = (reg) TIM_CCMR1_OC1FE_Pos;

	//! Map public channel indexes to concrete CCMR output-compare fast-enable positions.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = (reg) TIM_CCMR1_OC1FE_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = (reg) TIM_CCMR1_OC2FE_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = (reg) TIM_CCMR2_OC3FE_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = (reg) TIM_CCMR2_OC4FE_Pos;
			break;
		}
		default:
		{
			break;
		}
	}

	return fieldPos;
}

/**
 * @brief Returns the hardware `OCxPE` field position for one channel index
 * @param[in] channelIndex Zero-based channel index
 * @returns Register-positioned `OCxPE` bit position as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_GetCCMROcPreloadPos(const timer_channel_index_t channelIndex)
{
	reg fieldPos = (reg) TIM_CCMR1_OC1PE_Pos;

	//! Map public channel indexes to concrete CCMR output-compare preload-enable positions.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = (reg) TIM_CCMR1_OC1PE_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = (reg) TIM_CCMR1_OC2PE_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = (reg) TIM_CCMR2_OC3PE_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = (reg) TIM_CCMR2_OC4PE_Pos;
			break;
		}
		default:
		{
			break;
		}
	}

	return fieldPos;
}

/**
 * @brief Returns the hardware `OCxM` field position for one channel index
 * @param[in] channelIndex Zero-based channel index
 * @returns Register-positioned `OCxM` bit position as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_GetCCMROcModePos(const timer_channel_index_t channelIndex)
{
	reg fieldPos = (reg) TIM_CCMR1_OC1M_Pos;

	//! Map public channel indexes to concrete CCMR output-compare mode positions.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = (reg) TIM_CCMR1_OC1M_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = (reg) TIM_CCMR1_OC2M_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = (reg) TIM_CCMR2_OC3M_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = (reg) TIM_CCMR2_OC4M_Pos;
			break;
		}
		default:
		{
			break;
		}
	}

	return fieldPos;
}

/**
 * @brief Returns the hardware `OCxCE` field position for one channel index
 * @param[in] channelIndex Zero-based channel index
 * @returns Register-positioned `OCxCE` bit position as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_GetCCMROcClearPos(const timer_channel_index_t channelIndex)
{
	reg fieldPos = (reg) TIM_CCMR1_OC1CE_Pos;

	//! Map public channel indexes to concrete CCMR output-compare clear-enable positions.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = (reg) TIM_CCMR1_OC1CE_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = (reg) TIM_CCMR1_OC2CE_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = (reg) TIM_CCMR2_OC3CE_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = (reg) TIM_CCMR2_OC4CE_Pos;
			break;
		}
		default:
		{
			break;
		}
	}

	return fieldPos;
}

// ==================================================================================================== //
//										Local CCER Field Position Helpers								//
// ==================================================================================================== //

/**
 * @brief Returns the hardware `CCxE` field position for one channel index inside `CCER`
 * @param[in] channelIndex Zero-based channel index
 * @returns Register-positioned `CCxE` bit position as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_GetCcerEnablePos(const timer_channel_index_t channelIndex)
{
	reg fieldPos = (reg) TIM_CCER_CC1E_Pos;

	//! Map public channel indexes to concrete CCER enable-bit positions.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = (reg) TIM_CCER_CC1E_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = (reg) TIM_CCER_CC2E_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = (reg) TIM_CCER_CC3E_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = (reg) TIM_CCER_CC4E_Pos;
			break;
		}
		default:
		{
			break;
		}
	}

	return fieldPos;
}

/**
 * @brief Returns the hardware `CCxP` field position for one channel index inside `CCER`
 * @param[in] channelIndex Zero-based channel index
 * @returns Register-positioned `CCxP` bit position as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_GetCcerPolarityPos(const timer_channel_index_t channelIndex)
{
	reg fieldPos = (reg) TIM_CCER_CC1P_Pos;

	//! Map public channel indexes to concrete CCER polarity-bit positions.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = (reg) TIM_CCER_CC1P_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = (reg) TIM_CCER_CC2P_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = (reg) TIM_CCER_CC3P_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = (reg) TIM_CCER_CC4P_Pos;
			break;
		}
		default:
		{
			break;
		}
	}

	return fieldPos;
}

// ==================================================================================================== //
//										Local Selector Encode Helpers									//
// ==================================================================================================== //

// ==================================================================================================== //
//										Local Generic Selector Translation Helpers						//
// ==================================================================================================== //

/**
 * @brief Encodes a valid selector into a right-aligned raw field value
 * @param[in] isValid Selector validity flag
 * @param[in] selector Selector value
 * @param[out] pRawField Destination for right-aligned raw field value
 * @returns Encode status
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeSelector
(
	const uint8_t				isValid,
	const uint32_t				selector,
	reg_field_t* const			pRawField
)
{
	if (pRawField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (isValid == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Selector values intentionally mirror the raw right-aligned STM32 field values.
	*pRawField = (reg_field_t) selector;
	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Decodes a right-aligned raw field into a selector when valid
 * @param[in] isValid Raw field validity flag
 * @param[in] rawField Right-aligned raw field value
 * @param[out] pSelector Destination for decoded selector
 * @returns Decode status
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeSelector
(
	const uint8_t				isValid,
	const reg_field_t			rawField,
	uint8_t* const				pSelector
)
{
	if (pSelector == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (isValid == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Decode is symmetric with encode: raw field values are valid public selectors.
	*pSelector = (uint8_t) rawField;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local CR1 Selector Translation Helpers							//
// ==================================================================================================== //

/**
 * @brief Encodes a count-mode selector into a register-positioned `CR1.CMS` value
 * @param[in] mode Timer count-mode selector
 * @param[out] pFieldSet Destination for register-positioned `CR1.CMS` value
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Count mode was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFieldSet is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mode is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeCountModeToCR1
(
	const timer_count_mode_t		mode,
	reg* const					pFieldSet
)
{
	if (pFieldSet == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (mode)
	{
		case TIMx_MODE_NORMAL:
		{
			*pFieldSet = TIM_CR1_CMS_EDGE_ALIGNED;
			break;
		}
		case TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING:
		{
			*pFieldSet = TIM_CR1_CMS_CENTER_ALIGNED_MODE_1;
			break;
		}
		case TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING:
		{
			*pFieldSet = TIM_CR1_CMS_CENTER_ALIGNED_MODE_2;
			break;
		}
		case TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING:
		{
			*pFieldSet = TIM_CR1_CMS_CENTER_ALIGNED_MODE_3;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Decodes a register-positioned `CR1.CMS` value into a count-mode selector
 * @param[in] fieldSet Register-positioned `CR1.CMS` value
 * @param[out] pMode Destination for decoded count-mode selector
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Count mode was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pMode is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p fieldSet is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeCR1ToCountMode
(
	const reg					fieldSet,
	timer_count_mode_t* const		pMode
)
{
	if (pMode == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (fieldSet & TIM_CR1_CMS)
	{
		case TIM_CR1_CMS_EDGE_ALIGNED:
		{
			*pMode = TIMx_MODE_NORMAL;
			break;
		}
		case TIM_CR1_CMS_CENTER_ALIGNED_MODE_1:
		{
			*pMode = TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING;
			break;
		}
		case TIM_CR1_CMS_CENTER_ALIGNED_MODE_2:
		{
			*pMode = TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING;
			break;
		}
		case TIM_CR1_CMS_CENTER_ALIGNED_MODE_3:
		{
			*pMode = TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Encodes a clock-division selector into a register-positioned `CR1.CKD` value
 * @param[in] clockDivision Timer clock-division selector
 * @param[out] pFieldSet Destination for register-positioned `CR1.CKD` value
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock division was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFieldSet is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockDivision is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeClockDivisionToCR1
(
	const timer_clock_division_t	clockDivision,
	reg* const					pFieldSet
)
{
	if (pFieldSet == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (clockDivision)
	{
		case TIMx_CKD_CLK_FREQ:
		{
			*pFieldSet = TIM_CR1_CKD_TDTS_TCK_INT;
			break;
		}
		case TIMx_CKD_CLK_2_FREQ:
		{
			*pFieldSet = TIM_CR1_CKD_TDTS_2_TCK_INT;
			break;
		}
		case TIMx_CKD_CLK_4_FREQ:
		{
			*pFieldSet = TIM_CR1_CKD_TDTS_4_TCK_INT;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Decodes a register-positioned `CR1.CKD` value into a clock-division selector
 * @param[in] fieldSet Register-positioned `CR1.CKD` value
 * @param[out] pClockDivision Destination for decoded clock-division selector
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock division was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockDivision is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p fieldSet is reserved or unsupported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeCR1ToClockDivision
(
	const reg							fieldSet,
	timer_clock_division_t* const			pClockDivision
)
{
	if (pClockDivision == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (fieldSet & TIM_CR1_CKD)
	{
		case TIM_CR1_CKD_TDTS_TCK_INT:
		{
			*pClockDivision = TIMx_CKD_CLK_FREQ;
			break;
		}
		case TIM_CR1_CKD_TDTS_2_TCK_INT:
		{
			*pClockDivision = TIMx_CKD_CLK_2_FREQ;
			break;
		}
		case TIM_CR1_CKD_TDTS_4_TCK_INT:
		{
			*pClockDivision = TIMx_CKD_CLK_4_FREQ;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local Trigger Selector Translation Helpers						//
// ==================================================================================================== //

/**
 * @brief Encodes a master-mode selector into a register-positioned `CR2.MMS` value
 * @param[in] masterMode Timer master-mode selector
 * @param[out] pFieldSet Destination for register-positioned `CR2.MMS` value
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Master mode was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFieldSet is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p masterMode is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeMasterModeToCR2
(
	const timer_master_mode_t		masterMode,
	reg* const					pFieldSet
)
{
	if (pFieldSet == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (masterMode)
	{
		case TIMx_MMS_RESET:
		{
			*pFieldSet = TIM_CR2_MMS_RESET;
			break;
		}
		case TIMx_MMS_ENABLE:
		{
			*pFieldSet = TIM_CR2_MMS_ENABLE;
			break;
		}
		case TIMx_MMS_UPDATE:
		{
			*pFieldSet = TIM_CR2_MMS_UPDATE;
			break;
		}
		case TIMx_MMS_CMP_PULSE:
		{
			*pFieldSet = TIM_CR2_MMS_COMPARE_PULSE;
			break;
		}
		case TIMx_MMS_CMP_OC1REF:
		{
			*pFieldSet = TIM_CR2_MMS_COMPARE_OC1REF;
			break;
		}
		case TIMx_MMS_CMP_OC2REF:
		{
			*pFieldSet = TIM_CR2_MMS_COMPARE_OC2REF;
			break;
		}
		case TIMx_MMS_CMP_OC3REF:
		{
			*pFieldSet = TIM_CR2_MMS_COMPARE_OC3REF;
			break;
		}
		case TIMx_MMS_CMP_OC4REF:
		{
			*pFieldSet = TIM_CR2_MMS_COMPARE_OC4REF;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Decodes a register-positioned `CR2.MMS` value into a master-mode selector
 * @param[in] fieldSet Register-positioned `CR2.MMS` value
 * @param[out] pMasterMode Destination for decoded master-mode selector
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Master mode was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pMasterMode is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p fieldSet is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeCR2ToMasterMode
(
	const reg							fieldSet,
	timer_master_mode_t* const			pMasterMode
)
{
	if (pMasterMode == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (fieldSet & TIM_CR2_MMS)
	{
		case TIM_CR2_MMS_RESET:
		{
			*pMasterMode = TIMx_MMS_RESET;
			break;
		}
		case TIM_CR2_MMS_ENABLE:
		{
			*pMasterMode = TIMx_MMS_ENABLE;
			break;
		}
		case TIM_CR2_MMS_UPDATE:
		{
			*pMasterMode = TIMx_MMS_UPDATE;
			break;
		}
		case TIM_CR2_MMS_COMPARE_PULSE:
		{
			*pMasterMode = TIMx_MMS_CMP_PULSE;
			break;
		}
		case TIM_CR2_MMS_COMPARE_OC1REF:
		{
			*pMasterMode = TIMx_MMS_CMP_OC1REF;
			break;
		}
		case TIM_CR2_MMS_COMPARE_OC2REF:
		{
			*pMasterMode = TIMx_MMS_CMP_OC2REF;
			break;
		}
		case TIM_CR2_MMS_COMPARE_OC3REF:
		{
			*pMasterMode = TIMx_MMS_CMP_OC3REF;
			break;
		}
		case TIM_CR2_MMS_COMPARE_OC4REF:
		{
			*pMasterMode = TIMx_MMS_CMP_OC4REF;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Encodes a slave-mode selector into a register-positioned `SMCR.SMS` value
 * @param[in] slaveMode Timer slave-mode selector
 * @param[out] pFieldSet Destination for register-positioned `SMCR.SMS` value
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Slave mode was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFieldSet is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p slaveMode is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeSlaveModeToSMCR
(
	const timer_slave_mode_t		slaveMode,
	reg* const					pFieldSet
)
{
	if (pFieldSet == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (slaveMode)
	{
		case TIMx_SMS_DISABLE:
		{
			*pFieldSet = TIM_SMCR_SMS_DISABLED;
			break;
		}
		case TIMx_SMS_ENC_MODE1:
		{
			*pFieldSet = TIM_SMCR_SMS_ENCODER_MODE_1;
			break;
		}
		case TIMx_SMS_ENC_MODE2:
		{
			*pFieldSet = TIM_SMCR_SMS_ENCODER_MODE_2;
			break;
		}
		case TIMx_SMS_ENC_MODE3:
		{
			*pFieldSet = TIM_SMCR_SMS_ENCODER_MODE_3;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Decodes a register-positioned `SMCR.SMS` value into a slave-mode selector
 * @param[in] fieldSet Register-positioned `SMCR.SMS` value
 * @param[out] pSlaveMode Destination for decoded slave-mode selector
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Slave mode was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSlaveMode is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p fieldSet is outside the current public Timer vocabulary
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeSMCRToSlaveMode
(
	const reg							fieldSet,
	timer_slave_mode_t* const				pSlaveMode
)
{
	if (pSlaveMode == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (fieldSet & TIM_SMCR_SMS)
	{
		case TIM_SMCR_SMS_DISABLED:
		{
			*pSlaveMode = TIMx_SMS_DISABLE;
			break;
		}
		case TIM_SMCR_SMS_ENCODER_MODE_1:
		{
			*pSlaveMode = TIMx_SMS_ENC_MODE1;
			break;
		}
		case TIM_SMCR_SMS_ENCODER_MODE_2:
		{
			*pSlaveMode = TIMx_SMS_ENC_MODE2;
			break;
		}
		case TIM_SMCR_SMS_ENCODER_MODE_3:
		{
			*pSlaveMode = TIMx_SMS_ENC_MODE3;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local CCMR Selector Translation Helpers						//
// ==================================================================================================== //

/**
 * @brief Encodes a channel capture/compare selector into a CCMR-local `CCxS` value
 * @param[in] captureCompareSelection Timer capture/compare selector
 * @param[out] pRawField Destination for right-aligned CCMR shared encoding
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Capture/compare selector was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRawField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p captureCompareSelection is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeChannelSelectionToCCMR
(
	const timer_channel_ccs_t		captureCompareSelection,
	reg_field_t* const			pRawField
)
{
	if (pRawField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (captureCompareSelection)
	{
		case TIMx_CHANNEL_CCS_OUTPUT:
		{
			*pRawField = TIM_CCMR_CCXS_OUTPUT;
			break;
		}
		case TIMx_CHANNEL_CCS_INPUT_TIx:
		{
			*pRawField = TIM_CCMR_CCXS_INPUT_DIRECT_TI;
			break;
		}
		case TIMx_CHANNEL_CCS_INPUT_TIx_1:
		{
			*pRawField = TIM_CCMR_CCXS_INPUT_INDIRECT_TI;
			break;
		}
		case TIMx_CHANNEL_CCS_INPUT_TRC:
		{
			*pRawField = TIM_CCMR_CCXS_INPUT_TRC;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Decodes a CCMR-local `CCxS` value into a channel capture/compare selector
 * @param[in] rawField Right-aligned CCMR shared encoding
 * @param[out] pCaptureCompareSelection Destination for decoded capture/compare selector
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Capture/compare selector was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCaptureCompareSelection is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p rawField is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeCCMRToChannelSelection
(
	const reg_field_t					rawField,
	timer_channel_ccs_t* const			pCaptureCompareSelection
)
{
	if (pCaptureCompareSelection == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (rawField)
	{
		case TIM_CCMR_CCXS_OUTPUT:
		{
			*pCaptureCompareSelection = TIMx_CHANNEL_CCS_OUTPUT;
			break;
		}
		case TIM_CCMR_CCXS_INPUT_DIRECT_TI:
		{
			*pCaptureCompareSelection = TIMx_CHANNEL_CCS_INPUT_TIx;
			break;
		}
		case TIM_CCMR_CCXS_INPUT_INDIRECT_TI:
		{
			*pCaptureCompareSelection = TIMx_CHANNEL_CCS_INPUT_TIx_1;
			break;
		}
		case TIM_CCMR_CCXS_INPUT_TRC:
		{
			*pCaptureCompareSelection = TIMx_CHANNEL_CCS_INPUT_TRC;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Encodes an output-compare mode selector into a CCMR-local `OCxM` value
 * @param[in] outputCompareMode Timer output-compare mode selector
 * @param[out] pRawField Destination for right-aligned CCMR shared encoding
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Output-compare mode was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRawField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p outputCompareMode is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeOutputCompareModeToCCMR
(
	const timer_channel_mode_t				outputCompareMode,
	reg_field_t* const					pRawField
)
{
	if (pRawField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (outputCompareMode)
	{
		case TIMx_CHANNEL_MODE_FREEZE:
		{
			*pRawField = TIM_CCMR_OCXM_FROZEN;
			break;
		}
		case TIMx_CHANNEL_MODE_SET_CH:
		{
			*pRawField = TIM_CCMR_OCXM_ACTIVE_ON_MATCH;
			break;
		}
		case TIMx_CHANNEL_MODE_RESET_CH:
		{
			*pRawField = TIM_CCMR_OCXM_INACTIVE_ON_MATCH;
			break;
		}
		case TIMx_CHANNEL_MODE_TOGGLE:
		{
			*pRawField = TIM_CCMR_OCXM_TOGGLE_ON_MATCH;
			break;
		}
		case TIMx_CHANNEL_MODE_FORCE_RESET:
		{
			*pRawField = TIM_CCMR_OCXM_FORCE_INACTIVE;
			break;
		}
		case TIMx_CHANNEL_MODE_FORCE_SET:
		{
			*pRawField = TIM_CCMR_OCXM_FORCE_ACTIVE;
			break;
		}
		case TIMx_CHANNEL_MODE_PWM1:
		{
			*pRawField = TIM_CCMR_OCXM_PWM_MODE_1;
			break;
		}
		case TIMx_CHANNEL_MODE_PWM2:
		{
			*pRawField = TIM_CCMR_OCXM_PWM_MODE_2;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

/**
 * @brief Decodes a CCMR-local `OCxM` value into an output-compare mode selector
 * @param[in] rawField Right-aligned CCMR shared encoding
 * @param[out] pOutputCompareMode Destination for decoded output-compare mode selector
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Output-compare mode was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pOutputCompareMode is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p rawField is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeCCMRToOutputCompareMode
(
	const reg_field_t					rawField,
	timer_channel_mode_t* const			pOutputCompareMode
)
{
	if (pOutputCompareMode == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	switch (rawField)
	{
		case TIM_CCMR_OCXM_FROZEN:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_FREEZE;
			break;
		}
		case TIM_CCMR_OCXM_ACTIVE_ON_MATCH:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_SET_CH;
			break;
		}
		case TIM_CCMR_OCXM_INACTIVE_ON_MATCH:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_RESET_CH;
			break;
		}
		case TIM_CCMR_OCXM_TOGGLE_ON_MATCH:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_TOGGLE;
			break;
		}
		case TIM_CCMR_OCXM_FORCE_INACTIVE:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_FORCE_RESET;
			break;
		}
		case TIM_CCMR_OCXM_FORCE_ACTIVE:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_FORCE_SET;
			break;
		}
		case TIM_CCMR_OCXM_PWM_MODE_1:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_PWM1;
			break;
		}
		case TIM_CCMR_OCXM_PWM_MODE_2:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_PWM2;
			break;
		}
		default:
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
	}

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Local DIER/SR Mask Translation Helpers							//
// ==================================================================================================== //

/**
 * @brief Encodes a Timer IRQ selector mask into raw `DIER` interrupt bits
 * @param[in] irqMask Timer IRQ selector mask
 * @returns Raw `DIER` interrupt bit mask
 */
__STATIC_FORCEINLINE reg Codec_TIM_EncodeIRQMaskToDIERRaw(const timer_irq_t irqMask)
{
	reg rawMask = 0x00000000UL;

	//! Map public IRQ source bits explicitly so the driver never relies on DIER bit layout.
	if ((((uint32_t) irqMask) & ((uint32_t) TIMx_IRQ_OVF_UVF)) != 0x00000000UL)
	{
		rawMask |= TIM_DIER_UIE;
	}
	if ((((uint32_t) irqMask) & ((uint32_t) TIMx_IRQ_OUT_CMP_CH1)) != 0x00000000UL)
	{
		rawMask |= TIM_DIER_CC1IE;
	}
	if ((((uint32_t) irqMask) & ((uint32_t) TIMx_IRQ_OUT_CMP_CH2)) != 0x00000000UL)
	{
		rawMask |= TIM_DIER_CC2IE;
	}
	if ((((uint32_t) irqMask) & ((uint32_t) TIMx_IRQ_OUT_CMP_CH3)) != 0x00000000UL)
	{
		rawMask |= TIM_DIER_CC3IE;
	}
	if ((((uint32_t) irqMask) & ((uint32_t) TIMx_IRQ_OUT_CMP_CH4)) != 0x00000000UL)
	{
		rawMask |= TIM_DIER_CC4IE;
	}

	return rawMask;
}

/**
 * @brief Decodes raw `DIER` interrupt bits into a Timer IRQ selector mask
 * @param[in] dierRegImage Caller-owned `DIER` image
 * @returns Timer IRQ selector mask as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_DecodeDIERRawToIRQMask(const reg dierRegImage)
{
	reg irqMask = 0x00000000UL;

	//! Convert raw DIER interrupt-enable bits back into the public IRQ source mask.
	if ((dierRegImage & TIM_DIER_UIE) != 0x00000000UL)
	{
		irqMask |= ((reg) TIMx_IRQ_OVF_UVF);
	}
	if ((dierRegImage & TIM_DIER_CC1IE) != 0x00000000UL)
	{
		irqMask |= ((reg) TIMx_IRQ_OUT_CMP_CH1);
	}
	if ((dierRegImage & TIM_DIER_CC2IE) != 0x00000000UL)
	{
		irqMask |= ((reg) TIMx_IRQ_OUT_CMP_CH2);
	}
	if ((dierRegImage & TIM_DIER_CC3IE) != 0x00000000UL)
	{
		irqMask |= ((reg) TIMx_IRQ_OUT_CMP_CH3);
	}
	if ((dierRegImage & TIM_DIER_CC4IE) != 0x00000000UL)
	{
		irqMask |= ((reg) TIMx_IRQ_OUT_CMP_CH4);
	}

	return irqMask;
}

/**
 * @brief Encodes a Timer IRQ selector mask into raw `SR` flag bits
 * @param[in] irqMask Timer IRQ selector mask
 * @returns Raw `SR` flag bit mask
 */
__STATIC_FORCEINLINE reg Codec_TIM_EncodeIRQMaskToSRRaw(const timer_irq_t irqMask)
{
	reg rawMask = 0x00000000UL;

	//! IRQ selectors share meaning with SR event flags, but the raw SR mask is still built explicitly.
	if ((((uint32_t) irqMask) & ((uint32_t) TIMx_IRQ_OVF_UVF)) != 0x00000000UL)
	{
		rawMask |= TIM_SR_UIF;
	}
	if ((((uint32_t) irqMask) & ((uint32_t) TIMx_IRQ_OUT_CMP_CH1)) != 0x00000000UL)
	{
		rawMask |= TIM_SR_CC1IF;
	}
	if ((((uint32_t) irqMask) & ((uint32_t) TIMx_IRQ_OUT_CMP_CH2)) != 0x00000000UL)
	{
		rawMask |= TIM_SR_CC2IF;
	}
	if ((((uint32_t) irqMask) & ((uint32_t) TIMx_IRQ_OUT_CMP_CH3)) != 0x00000000UL)
	{
		rawMask |= TIM_SR_CC3IF;
	}
	if ((((uint32_t) irqMask) & ((uint32_t) TIMx_IRQ_OUT_CMP_CH4)) != 0x00000000UL)
	{
		rawMask |= TIM_SR_CC4IF;
	}

	return rawMask;
}

/**
 * @brief Decodes raw `SR` flag bits into a Timer IRQ selector mask
 * @param[in] srRegImage Caller-owned `SR` image
 * @returns Timer IRQ selector mask as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_DecodeSRRawToIRQMask(const reg srRegImage)
{
	reg irqMask = 0x00000000UL;

	//! Only event flags covered by the public IRQ vocabulary are surfaced to the driver.
	if ((srRegImage & TIM_SR_UIF) != 0x00000000UL)
	{
		irqMask |= ((reg) TIMx_IRQ_OVF_UVF);
	}
	if ((srRegImage & TIM_SR_CC1IF) != 0x00000000UL)
	{
		irqMask |= ((reg) TIMx_IRQ_OUT_CMP_CH1);
	}
	if ((srRegImage & TIM_SR_CC2IF) != 0x00000000UL)
	{
		irqMask |= ((reg) TIMx_IRQ_OUT_CMP_CH2);
	}
	if ((srRegImage & TIM_SR_CC3IF) != 0x00000000UL)
	{
		irqMask |= ((reg) TIMx_IRQ_OUT_CMP_CH3);
	}
	if ((srRegImage & TIM_SR_CC4IF) != 0x00000000UL)
	{
		irqMask |= ((reg) TIMx_IRQ_OUT_CMP_CH4);
	}

	return irqMask;
}

/**
 * @brief Encodes a Timer DMA selector mask into raw `DIER` DMA bits
 * @param[in] dmaMask Timer DMA selector mask
 * @returns Raw `DIER` DMA bit mask
 */
__STATIC_FORCEINLINE reg Codec_TIM_EncodeDMAMaskToDIERRaw(const timer_dma_t dmaMask)
{
	reg rawMask = 0x00000000UL;

	//! Public DMA source bits are compact; raw DIER DMA enable bits live at positions 8..12.
	if ((((uint32_t) dmaMask) & ((uint32_t) TIMx_DMA_UPDATE)) != 0x00000000UL)
	{
		rawMask |= TIM_DIER_UDE;
	}
	if ((((uint32_t) dmaMask) & ((uint32_t) TIMx_DMA_CC1DE)) != 0x00000000UL)
	{
		rawMask |= TIM_DIER_CC1DE;
	}
	if ((((uint32_t) dmaMask) & ((uint32_t) TIMx_DMA_CC2DE)) != 0x00000000UL)
	{
		rawMask |= TIM_DIER_CC2DE;
	}
	if ((((uint32_t) dmaMask) & ((uint32_t) TIMx_DMA_CC3DE)) != 0x00000000UL)
	{
		rawMask |= TIM_DIER_CC3DE;
	}
	if ((((uint32_t) dmaMask) & ((uint32_t) TIMx_DMA_CC4DE)) != 0x00000000UL)
	{
		rawMask |= TIM_DIER_CC4DE;
	}

	return rawMask;
}

/**
 * @brief Decodes raw `DIER` DMA bits into a Timer DMA selector mask
 * @param[in] dierRegImage Caller-owned `DIER` image
 * @returns Timer DMA selector mask as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_DecodeDIERRawToDMAMask(const reg dierRegImage)
{
	reg dmaMask = 0x00000000UL;

	//! Decode only the general-purpose Timer DMA request sources represented by timer_defines.h.
	if ((dierRegImage & TIM_DIER_UDE) != 0x00000000UL)
	{
		dmaMask |= ((reg) TIMx_DMA_UPDATE);
	}
	if ((dierRegImage & TIM_DIER_CC1DE) != 0x00000000UL)
	{
		dmaMask |= ((reg) TIMx_DMA_CC1DE);
	}
	if ((dierRegImage & TIM_DIER_CC2DE) != 0x00000000UL)
	{
		dmaMask |= ((reg) TIMx_DMA_CC2DE);
	}
	if ((dierRegImage & TIM_DIER_CC3DE) != 0x00000000UL)
	{
		dmaMask |= ((reg) TIMx_DMA_CC3DE);
	}
	if ((dierRegImage & TIM_DIER_CC4DE) != 0x00000000UL)
	{
		dmaMask |= ((reg) TIMx_DMA_CC4DE);
	}

	return dmaMask;
}

// ==================================================================================================== //
//										Timer Timebase Codecs											//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer Timebase Scalar Codecs									//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractPrescaler
(
	const reg							pscRegImage,
	timer_prescaler_t* const				pPrescaler
)
{
	if (pPrescaler == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! PSC is a 16-bit scalar field; the codec only extracts the caller-owned image.
	*pPrescaler = (timer_prescaler_t) Codec_TIM_ExtractScalarField(pscRegImage, TIM_PSC_PSC, TIM_PSC_PSC_Pos);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StagePrescaler
(
	const reg							pscRegImage,
	const timer_prescaler_t				prescaler,
	reg* const							pPscRegImage
)
{
	//! Preserve any non-PSC bits in the caller-owned image while replacing PSC[15:0].
	return Codec_TIM_StageScalarField(pscRegImage, TIM_PSC_PSC, TIM_PSC_PSC_Pos, (reg) prescaler, pPscRegImage);
}

driver_status_t Codec_TIM_ExtractAutoReload
(
	const reg							arrRegImage,
	timer_auto_reload_t* const			pAutoReload
)
{
	if (pAutoReload == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! ARR is a 16-bit scalar field; the codec does not infer update period or frequency.
	*pAutoReload = (timer_auto_reload_t) Codec_TIM_ExtractScalarField(arrRegImage, TIM_ARR_ARR, TIM_ARR_ARR_Pos);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageAutoReload
(
	const reg							arrRegImage,
	const timer_auto_reload_t			autoReload,
	reg* const							pArrRegImage
)
{
	//! Stage the register-backed ARR value directly; timing policy remains in the driver layer.
	return Codec_TIM_StageScalarField(arrRegImage, TIM_ARR_ARR, TIM_ARR_ARR_Pos, (reg) autoReload, pArrRegImage);
}

driver_status_t Codec_TIM_ExtractCounterValue
(
	const reg							cntRegImage,
	timer_counter_value_t* const			pCounterValue
)
{
	if (pCounterValue == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! CNT is a 16-bit scalar field; extract only the hardware image value.
	*pCounterValue = (timer_counter_value_t) Codec_TIM_ExtractScalarField(cntRegImage, TIM_CNT_CNT, TIM_CNT_CNT_Pos);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageCounterValue
(
	const reg							cntRegImage,
	const timer_counter_value_t			counterValue,
	reg* const							pCntRegImage
)
{
	//! Stage the raw CNT value without deciding whether the counter should be stopped first.
	return Codec_TIM_StageScalarField(cntRegImage, TIM_CNT_CNT, TIM_CNT_CNT_Pos, (reg) counterValue, pCntRegImage);
}

// ==================================================================================================== //
//										Timer Timebase Config Codecs									//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractTimeBaseConfig
(
	const reg							pscRegImage,
	const reg							arrRegImage,
	const reg							cntRegImage,
	timer_config_timebase_t* const		pTimebase
)
{
	if (pTimebase == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Group extraction is just the three scalar extractions collected into the timebase structure.
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractPrescaler(pscRegImage, &(pTimebase->prescaler)));
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractAutoReload(arrRegImage, &(pTimebase->auto_reload)));
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractCounterValue(cntRegImage, &(pTimebase->initial_count)));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageTimeBaseConfig
(
	const reg								pscRegImage,
	const reg								arrRegImage,
	const reg								cntRegImage,
	const timer_config_timebase_t* const	pTimebase,
	reg* const								pPscRegImage,
	reg* const								pArrRegImage,
	reg* const								pCntRegImage
)
{
	if ((pTimebase == NULL) || (pPscRegImage == NULL) || (pArrRegImage == NULL) || (pCntRegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Stage every timebase register image independently so the driver can later dirty-write each one.
	ASSERT_DRIVER_STATUS(Codec_TIM_StagePrescaler(pscRegImage, pTimebase->prescaler, pPscRegImage));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageAutoReload(arrRegImage, pTimebase->auto_reload, pArrRegImage));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterValue(cntRegImage, pTimebase->initial_count, pCntRegImage));

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer CR1 Counter Codecs										//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer CR1 Counter Selector Codecs								//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractCounterDirection
(
	const reg							cr1RegImage,
	timer_direction_t* const				pDirection
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pDirection == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! `DIR` is the raw direction field and maps directly to the public direction selector.
	rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_DIR, TIM_CR1_DIR_Pos);
	return Codec_TIM_DecodeSelector(TIM_DIRECTION_IS_VALID(rawField), rawField, pDirection);
}

driver_status_t Codec_TIM_StageCounterDirection
(
	const reg							cr1RegImage,
	const timer_direction_t				direction,
	reg* const							pCr1RegImage
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Stage only DIR, preserving all other CR1 bits in the caller-owned image.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_DIRECTION_IS_VALID(direction), direction, &rawField));
	*pCr1RegImage = RegOps_StageFieldValue(cr1RegImage, TIM_CR1_DIR_Pos, rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_ExtractCounterAlignment
(
	const reg							cr1RegImage,
	timer_count_mode_t* const			pAlignment
)
{
	if (pAlignment == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! `CMS` uses register-positioned semantic values from the Timer register layer.
	return Codec_TIM_DecodeCR1ToCountMode((cr1RegImage & TIM_CR1_CMS), pAlignment);
}

driver_status_t Codec_TIM_StageCounterAlignment
(
	const reg							cr1RegImage,
	const timer_count_mode_t				alignment,
	reg* const							pCr1RegImage
)
{
	reg fieldSet = 0x00000000UL;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Convert the public alignment selector into the register-positioned CMS field.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeCountModeToCR1(alignment, &fieldSet));
	*pCr1RegImage = RegOps_StageField(cr1RegImage, TIM_CR1_CMS, fieldSet);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_ExtractOnePulse
(
	const reg							cr1RegImage,
	timer_opm_t* const					pOnePulse
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pOnePulse == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! `OPM` is a one-bit selector: continuous counting versus one-pulse mode.
	rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_OPM, TIM_CR1_OPM_Pos);
	return Codec_TIM_DecodeSelector(TIM_OPM_IS_VALID(rawField), rawField, pOnePulse);
}

driver_status_t Codec_TIM_StageOnePulse
(
	const reg							cr1RegImage,
	const timer_opm_t					onePulse,
	reg* const							pCr1RegImage
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Stage only OPM, preserving all unrelated CR1 fields.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_OPM_IS_VALID(onePulse), onePulse, &rawField));
	*pCr1RegImage = RegOps_StageFieldValue(cr1RegImage, TIM_CR1_OPM_Pos, rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_ExtractAutoReloadPreload
(
	const reg							cr1RegImage,
	timer_arpe_t* const					pAutoReloadPreload
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pAutoReloadPreload == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! `ARPE` controls whether ARR updates are buffered until update events.
	rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_ARPE, TIM_CR1_ARPE_Pos);
	return Codec_TIM_DecodeSelector(TIM_ARPE_IS_VALID(rawField), rawField, pAutoReloadPreload);
}

driver_status_t Codec_TIM_StageAutoReloadPreload
(
	const reg							cr1RegImage,
	const timer_arpe_t					autoReloadPreload,
	reg* const							pCr1RegImage
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Stage only ARPE, preserving all unrelated CR1 fields.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_ARPE_IS_VALID(autoReloadPreload), autoReloadPreload, &rawField));
	*pCr1RegImage = RegOps_StageFieldValue(cr1RegImage, TIM_CR1_ARPE_Pos, rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_ExtractUpdateSource
(
	const reg							cr1RegImage,
	timer_update_source_t* const			pUpdateSource
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pUpdateSource == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! `URS` selects whether any update source or only overflow/DMA sources generate update requests.
	rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_URS, TIM_CR1_URS_Pos);
	return Codec_TIM_DecodeSelector(TIM_UPDATE_SOURCE_IS_VALID(rawField), rawField, pUpdateSource);
}

driver_status_t Codec_TIM_StageUpdateSource
(
	const reg							cr1RegImage,
	const timer_update_source_t			updateSource,
	reg* const							pCr1RegImage
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Stage only URS; update-event enable state is still owned by UDIS helpers.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_UPDATE_SOURCE_IS_VALID(updateSource), updateSource, &rawField));
	*pCr1RegImage = RegOps_StageFieldValue(cr1RegImage, TIM_CR1_URS_Pos, rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_ExtractClockDivision
(
	const reg							cr1RegImage,
	timer_clock_division_t* const		pClockDivision
)
{
	if (pClockDivision == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! `CKD` divides the digital filter/dead-time sampling clock, not the counter clock.
	return Codec_TIM_DecodeCR1ToClockDivision((cr1RegImage & TIM_CR1_CKD), pClockDivision);
}

driver_status_t Codec_TIM_StageClockDivision
(
	const reg							cr1RegImage,
	const timer_clock_division_t			clockDivision,
	reg* const							pCr1RegImage
)
{
	reg fieldSet = 0x00000000UL;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Convert the public CKD selector into the register-positioned CKD field.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeClockDivisionToCR1(clockDivision, &fieldSet));
	*pCr1RegImage = RegOps_StageField(cr1RegImage, TIM_CR1_CKD, fieldSet);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer CR1 Counter Config Codecs								//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractCounterConfig
(
	const reg							cr1RegImage,
	timer_config_counter_t* const		pCounter
)
{
	if (pCounter == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Group extraction composes the individual CR1 field codecs into the counter structure.
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractCounterDirection(cr1RegImage, &(pCounter->direction)));
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractCounterAlignment(cr1RegImage, &(pCounter->alignment)));
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractOnePulse(cr1RegImage, &(pCounter->one_pulse)));
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractAutoReloadPreload(cr1RegImage, &(pCounter->auto_reload_preload)));
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractUpdateSource(cr1RegImage, &(pCounter->update_source)));
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractClockDivision(cr1RegImage, &(pCounter->clock_division)));

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageCounterConfig
(
	const reg							cr1RegImage,
	const timer_config_counter_t* const	pCounter,
	reg* const							pCr1RegImage
)
{
	reg updatedRegImage = cr1RegImage;

	if ((pCounter == NULL) || (pCr1RegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Group staging composes individual CR1 field stages so each field API has one implementation path.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterDirection(updatedRegImage, pCounter->direction, &updatedRegImage));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterAlignment(updatedRegImage, pCounter->alignment, &updatedRegImage));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageOnePulse(updatedRegImage, pCounter->one_pulse, &updatedRegImage));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageAutoReloadPreload(updatedRegImage, pCounter->auto_reload_preload, &updatedRegImage));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateSource(updatedRegImage, pCounter->update_source, &updatedRegImage));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageClockDivision(updatedRegImage, pCounter->clock_division, &updatedRegImage));

	*pCr1RegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer CR1 Runtime State Codecs									//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractCounterEnableState
(
	const reg							cr1RegImage,
	driver_status_t* const				pCounterState
)
{
	if (pCounterState == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	*pCounterState = Codec_TIM_ExtractBitStateFromImage(cr1RegImage, TIM_CR1_CEN);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageCounterEnableState
(
	const reg							cr1RegImage,
	const driver_status_t				counterState,
	reg* const							pCr1RegImage
)
{
	return Codec_TIM_StageBitStateInImage(cr1RegImage, TIM_CR1_CEN, counterState, pCr1RegImage);
}

driver_status_t Codec_TIM_ExtractUpdateEventState
(
	const reg							cr1RegImage,
	driver_status_t* const				pUpdateEventState
)
{
	if (pUpdateEventState == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! CR1.UDIS uses inverse polarity: bit set means update events are disabled.
	*pUpdateEventState = ((cr1RegImage & TIM_CR1_UDIS) != 0x00000000UL) ? DRIVER_STATUS_OFF : DRIVER_STATUS_ON;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageUpdateEventState
(
	const reg							cr1RegImage,
	const driver_status_t				updateEventState,
	reg* const							pCr1RegImage
)
{
	reg bitSet = 0x00000000UL;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_TIM_ValidateState(updateEventState));

	//! Convert driver-facing ON/OFF into inverse raw UDIS semantics.
	bitSet = (updateEventState == DRIVER_STATUS_OFF) ? TIM_CR1_UDIS : 0x00000000UL;
	*pCr1RegImage = RegOps_StageField(cr1RegImage, TIM_CR1_UDIS, bitSet);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Trigger Codecs											//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer Master Mode Codecs										//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractMasterMode
(
	const reg							cr2RegImage,
	timer_master_mode_t* const			pMasterMode
)
{
	//! Decode the register-positioned MMS image through the explicit CR2 mapping table.
	return Codec_TIM_DecodeCR2ToMasterMode((cr2RegImage & TIM_CR2_MMS), pMasterMode);
}

driver_status_t Codec_TIM_StageMasterMode
(
	const reg							cr2RegImage,
	const timer_master_mode_t				masterMode,
	reg* const							pCr2RegImage
)
{
	reg fieldSet = 0x00000000UL;

	if (pCr2RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeMasterModeToCR2(masterMode, &fieldSet));
	*pCr2RegImage = RegOps_StageField(cr2RegImage, TIM_CR2_MMS, fieldSet);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Slave Mode Codecs										//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractSlaveMode
(
	const reg							smcrRegImage,
	timer_slave_mode_t* const				pSlaveMode
)
{
	//! Decode the register-positioned SMS image through the explicit SMCR mapping table.
	return Codec_TIM_DecodeSMCRToSlaveMode((smcrRegImage & TIM_SMCR_SMS), pSlaveMode);
}

driver_status_t Codec_TIM_StageSlaveMode
(
	const reg							smcrRegImage,
	const timer_slave_mode_t				slaveMode,
	reg* const							pSmcrRegImage
)
{
	reg fieldSet = 0x00000000UL;

	if (pSmcrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSlaveModeToSMCR(slaveMode, &fieldSet));
	*pSmcrRegImage = RegOps_StageField(smcrRegImage, TIM_SMCR_SMS, fieldSet);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer CCMR Channel Codecs										//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer CCMR Channel Selection Codecs							//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractChannelSelection
(
	const reg							ccmrRegImage,
	const timer_channel_t					channel,
	timer_channel_ccs_t* const			pCaptureCompareSelection
)
{
	timer_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCaptureCompareSelection == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));

	//! The caller supplies CCMR1 for channels 1/2 or CCMR2 for channels 3/4; parity selects the slot.
	rawField = RegOps_ExtractFieldValue
	(
		ccmrRegImage,
		REG_FIELD_MASK(Codec_TIM_GetCCMRCcsPos(channelIndex), TIM_CODEC_FIELD_WIDTH_2BIT),
		Codec_TIM_GetCCMRCcsPos(channelIndex)
	);

	return Codec_TIM_DecodeCCMRToChannelSelection(rawField, pCaptureCompareSelection);
}

driver_status_t Codec_TIM_StageChannelSelection
(
	const reg							ccmrRegImage,
	const timer_channel_t					channel,
	const timer_channel_ccs_t				captureCompareSelection,
	reg* const							pCCMRRegImage
)
{
	timer_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCCMRRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeChannelSelectionToCCMR(captureCompareSelection, &rawField));

	//! Stage only CCxS; output-compare and input-capture mode fields are handled by dedicated codecs.
	*pCCMRRegImage = RegOps_StageFieldValue
	(
		ccmrRegImage,
		Codec_TIM_GetCCMRCcsPos(channelIndex),
		rawField,
		TIM_CODEC_FIELD_WIDTH_2BIT
	);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer CCMR Output Compare Codecs								//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractOutputCompareConfig
(
	const reg							ccmrRegImage,
	const timer_channel_t					channel,
	timer_channel_oc_clear_t* const		pOutputCompareClear,
	timer_channel_mode_t* const			pOutputCompareMode,
	timer_channel_oc_preload_t* const		pOutputComparePreload,
	timer_channel_oc_fast_t* const			pOutputCompareFast
)
{
	timer_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
	reg_field_t rawField = (reg_field_t) 0x00U;
	timer_channel_ccs_t captureCompareSelection = TIMx_CHANNEL_CCS_OUTPUT;

	if
	(
		(pOutputCompareClear == NULL) &&
		(pOutputCompareMode == NULL) &&
		(pOutputComparePreload == NULL) &&
		(pOutputCompareFast == NULL)
	)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Output-compare decode is valid only when CCxS selects output mode.
	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));
	ASSERT_DRIVER_STATUS(Codec_TIM_ExtractChannelSelection(ccmrRegImage, channel, &captureCompareSelection));
	if (captureCompareSelection != TIMx_CHANNEL_CCS_OUTPUT)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	if (pOutputCompareClear != NULL)
	{
		//! OCxCE controls whether trigger input can clear the output compare signal.
		rawField = RegOps_ExtractFieldValue
		(
			ccmrRegImage,
			REG_FIELD_MASK(Codec_TIM_GetCCMROcClearPos(channelIndex), TIM_CODEC_FIELD_WIDTH_1BIT),
			Codec_TIM_GetCCMROcClearPos(channelIndex)
		);
		ASSERT_DRIVER_STATUS(Codec_TIM_DecodeSelector(TIM_CHANNEL_OC_CLEAR_IS_VALID(rawField), rawField, pOutputCompareClear));
	}
	if (pOutputCompareMode != NULL)
	{
		//! OCxM selects the output behavior, including PWM modes.
		rawField = RegOps_ExtractFieldValue
		(
			ccmrRegImage,
			REG_FIELD_MASK(Codec_TIM_GetCCMROcModePos(channelIndex), TIM_CODEC_FIELD_WIDTH_3BIT),
			Codec_TIM_GetCCMROcModePos(channelIndex)
		);
		ASSERT_DRIVER_STATUS(Codec_TIM_DecodeCCMRToOutputCompareMode(rawField, pOutputCompareMode));
	}
	if (pOutputComparePreload != NULL)
	{
		//! OCxPE buffers CCR updates until an update event.
		rawField = RegOps_ExtractFieldValue
		(
			ccmrRegImage,
			REG_FIELD_MASK(Codec_TIM_GetCCMROcPreloadPos(channelIndex), TIM_CODEC_FIELD_WIDTH_1BIT),
			Codec_TIM_GetCCMROcPreloadPos(channelIndex)
		);
		ASSERT_DRIVER_STATUS(Codec_TIM_DecodeSelector(TIM_CHANNEL_OC_PRELOAD_IS_VALID(rawField), rawField, pOutputComparePreload));
	}
	if (pOutputCompareFast != NULL)
	{
		//! OCxFE bypasses compare latency for fast output-compare response.
		rawField = RegOps_ExtractFieldValue
		(
			ccmrRegImage,
			REG_FIELD_MASK(Codec_TIM_GetCCMROcFastPos(channelIndex), TIM_CODEC_FIELD_WIDTH_1BIT),
			Codec_TIM_GetCCMROcFastPos(channelIndex)
		);
		ASSERT_DRIVER_STATUS(Codec_TIM_DecodeSelector(TIM_CHANNEL_OC_FAST_IS_VALID(rawField), rawField, pOutputCompareFast));
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageOutputCompareConfig
(
	const reg							ccmrRegImage,
	const timer_channel_t					channel,
	const timer_channel_oc_clear_t		outputCompareClear,
	const timer_channel_mode_t			outputCompareMode,
	const timer_channel_oc_preload_t		outputComparePreload,
	const timer_channel_oc_fast_t			outputCompareFast,
	reg* const							pCCMRRegImage
)
{
	timer_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
	reg updatedRegImage = ccmrRegImage;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCCMRRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));

	//! Force CCxS to output mode before staging OCx fields so the image has a coherent interpretation.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeChannelSelectionToCCMR(TIMx_CHANNEL_CCS_OUTPUT, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, Codec_TIM_GetCCMRCcsPos(channelIndex), rawField, TIM_CODEC_FIELD_WIDTH_2BIT);

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_CHANNEL_OC_CLEAR_IS_VALID(outputCompareClear), outputCompareClear, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, Codec_TIM_GetCCMROcClearPos(channelIndex), rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeOutputCompareModeToCCMR(outputCompareMode, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, Codec_TIM_GetCCMROcModePos(channelIndex), rawField, TIM_CODEC_FIELD_WIDTH_3BIT);

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_CHANNEL_OC_PRELOAD_IS_VALID(outputComparePreload), outputComparePreload, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, Codec_TIM_GetCCMROcPreloadPos(channelIndex), rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_CHANNEL_OC_FAST_IS_VALID(outputCompareFast), outputCompareFast, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, Codec_TIM_GetCCMROcFastPos(channelIndex), rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	*pCCMRRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer CCER Channel Codecs										//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer CCER Channel Enable Codecs								//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractChannelEnableState
(
	const reg							ccerRegImage,
	const timer_channel_t					channel,
	driver_status_t* const				pChannelState
)
{
	timer_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;

	if (pChannelState == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! CCER channel enable bits sit in four-bit lanes selected from the channel index.
	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));
	*pChannelState = Codec_TIM_ExtractBitStateFromImage
	(
		ccerRegImage,
		REG_BIT_MASK(Codec_TIM_GetCcerEnablePos(channelIndex))
	);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageChannelEnableState
(
	const reg							ccerRegImage,
	const timer_channel_t					channel,
	const driver_status_t				channelState,
	reg* const							pCcerRegImage
)
{
	timer_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;

	if (pCcerRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Stage only CCxE; polarity and reserved lane bits are preserved.
	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));
	return Codec_TIM_StageBitStateInImage
	(
		ccerRegImage,
		REG_BIT_MASK(Codec_TIM_GetCcerEnablePos(channelIndex)),
		channelState,
		pCcerRegImage
	);
}

// ==================================================================================================== //
//										Timer CCER Channel Polarity Codecs								//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractChannelPolarity
(
	const reg							ccerRegImage,
	const timer_channel_t					channel,
	timer_channel_polarity_t* const		pPolarity
)
{
	timer_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pPolarity == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));
	//! CCxP is one bit after CCxE in each four-bit CCER channel lane.
	rawField = RegOps_ExtractFieldValue
	(
		ccerRegImage,
		REG_BIT_MASK(Codec_TIM_GetCcerPolarityPos(channelIndex)),
		Codec_TIM_GetCcerPolarityPos(channelIndex)
	);

	return Codec_TIM_DecodeSelector(TIM_CHANNEL_POLARITY_IS_VALID(rawField), rawField, pPolarity);
}

driver_status_t Codec_TIM_StageChannelPolarity
(
	const reg							ccerRegImage,
	const timer_channel_t					channel,
	const timer_channel_polarity_t			polarity,
	reg* const							pCcerRegImage
)
{
	timer_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCcerRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_CHANNEL_POLARITY_IS_VALID(polarity), polarity, &rawField));

	//! Stage only CCxP so channel enable state and reserved lane bits remain unchanged.
	*pCcerRegImage = RegOps_StageFieldValue
	(
		ccerRegImage,
		Codec_TIM_GetCcerPolarityPos(channelIndex),
		rawField,
		TIM_CODEC_FIELD_WIDTH_1BIT
	);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer DIER Request Codecs										//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer DIER IRQ Request Codecs									//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractIRQEnableMask
(
	const reg							dierRegImage,
	timer_irq_t* const					pIrqMask
)
{
	if (pIrqMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Extract only DIER interrupt-enable bits represented by the public IRQ source mask.
	*pIrqMask = (timer_irq_t) Codec_TIM_DecodeDIERRawToIRQMask(dierRegImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageIRQEnableMask
(
	const reg							dierRegImage,
	const timer_irq_t						irqMask,
	const timer_irq_enable_t				irqEnable,
	reg* const							pDierRegImage
)
{
	reg rawMask = 0x00000000UL;
	reg rawSet = 0x00000000UL;

	if (pDierRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if ((TIM_IRQ_MASK_IS_VALID(irqMask) == 0x00U) || (TIM_IRQ_ENABLE_IS_VALID(irqEnable) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Build the raw DIER mask once, then either set or clear the selected enable bits.
	rawMask = Codec_TIM_EncodeIRQMaskToDIERRaw(irqMask);
	rawSet = (irqEnable == TIMx_IRQ_ENABLE) ? rawMask : 0x00000000UL;
	*pDierRegImage = RegOps_StageField(dierRegImage, rawMask, rawSet);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer DIER DMA Request Codecs									//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractDMAEnableMask
(
	const reg							dierRegImage,
	timer_dma_t* const					pDmaMask
)
{
	if (pDmaMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Extract only DIER DMA-enable bits represented by the public DMA source mask.
	*pDmaMask = (timer_dma_t) Codec_TIM_DecodeDIERRawToDMAMask(dierRegImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageDMAEnableMask
(
	const reg							dierRegImage,
	const timer_dma_t						dmaMask,
	const driver_status_t				dmaState,
	reg* const							pDierRegImage
)
{
	reg rawMask = 0x00000000UL;
	reg rawSet = 0x00000000UL;

	if (pDierRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (TIM_DMA_MASK_IS_VALID(dmaMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	ASSERT_DRIVER_STATUS(Codec_TIM_ValidateState(dmaState));

	//! DMA uses driver OFF/ON state while IRQ uses the legacy TIMx_IRQ_DISABLE/ENABLE selector.
	rawMask = Codec_TIM_EncodeDMAMaskToDIERRaw(dmaMask);
	rawSet = (dmaState == DRIVER_STATUS_ON) ? rawMask : 0x00000000UL;
	*pDierRegImage = RegOps_StageField(dierRegImage, rawMask, rawSet);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer SR Flag Codecs											//
// ==================================================================================================== //

// ==================================================================================================== //
//										Timer SR IRQ Flag Codecs										//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractIRQFlagMask
(
	const reg							srRegImage,
	timer_irq_t* const					pIrqMask
)
{
	if (pIrqMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Status extraction reports pending event flags using the same public IRQ source mask.
	*pIrqMask = (timer_irq_t) Codec_TIM_DecodeSRRawToIRQMask(srRegImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageIRQAckMask
(
	const reg							srRegImage,
	const timer_irq_t						irqMask,
	reg* const							pSrRegImage
)
{
	const reg rawMask = Codec_TIM_EncodeIRQMaskToSRRaw(irqMask);
	reg updatedRegImage = srRegImage;

	if (pSrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if (TIM_IRQ_MASK_IS_VALID(irqMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Timer SR flags are write-0-to-clear; write 1 to unacknowledged supported flags to preserve them.
	if ((srRegImage & rawMask) != 0x00000000UL)
	{
		updatedRegImage |= (TIM_CODEC_SR_GENERAL_PURPOSE_FLAG_MASK & ~rawMask);
		updatedRegImage &= ~rawMask;
	}

	*pSrRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}
