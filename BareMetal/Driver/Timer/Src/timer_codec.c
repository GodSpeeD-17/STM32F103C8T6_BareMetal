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
/** @brief Timer status flags with write-zero-to-clear behavior @def TIM_CODEC_SR_W0C_FLAG_MASK */
#define TIM_CODEC_SR_W0C_FLAG_MASK									\
(																	\
	TIM_SR_UIF		| TIM_SR_CC1IF	| TIM_SR_CC2IF	|				\
	TIM_SR_CC3IF	| TIM_SR_CC4IF	| TIM_SR_TIF	|				\
	TIM_SR_CC1OF	| TIM_SR_CC2OF	| TIM_SR_CC3OF	| TIM_SR_CC4OF	\
)

// ==================================================================================================== //
//										Local Register Image Helpers									//
// ==================================================================================================== //

// --------------------------------- Local Binary State Image Helpers --------------------------------- //

/**
 * @brief Validates whether a state selector is an accepted ON/OFF state
 * @param[in] state Driver state selector
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disabled/cleared state
 * - @ref `DRIVER_STATUS_ON`: Enabled/set state
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
 * @param[in,out] pRegImage Caller-owned register image to update in place
 * @param[in] bitMask Register-positioned bit mask
 * @param[in] state Requested ON/OFF state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Clear @p bitMask
 * - @ref `DRIVER_STATUS_ON`: Set @p bitMask
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: State was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRegImage is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p state is not accepted
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_StageBitStateInImage
(
	reg* const					pRegImage,
	const reg					bitMask,
	const driver_status_t		state
)
{
	// Local Variable
	reg updatedRegImage = 0x00000000UL;
	reg bitSet = 0x00000000UL;

	// Validate Input
	if (pRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pRegImage;

	ASSERT_DRIVER_STATUS(Codec_TIM_ValidateState(state));

	//! Convert the driver ON/OFF state into the raw bit value and stage only that bit.
	bitSet = (state == DRIVER_STATUS_ON) ? bitMask : 0x00000000UL;
	updatedRegImage = RegOps_StageField(updatedRegImage, bitMask, bitSet);

	*pRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// --------------------------------- Local Scalar Field Image Helpers --------------------------------- //

/**
 * @brief Stages one right-aligned scalar field inside a register image
 * @param[in,out] pRegImage Caller-owned register image to update in place
 * @param[in] fieldMask Register-positioned field mask
 * @param[in] fieldPos Zero-based field bit position
 * @param[in] value Right-aligned scalar value
 * @returns Staging status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Scalar field was staged
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRegImage is `NULL`
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_StageScalarField
(
	reg* const					pRegImage,
	const reg					fieldMask,
	const reg_bit_pos_t			fieldPos,
	const reg					value
)
{
	reg updatedRegImage = 0x00000000UL;

	if (pRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pRegImage;

	//! Pack the right-aligned value into its hardware field position, then replace only that field.
	updatedRegImage = RegOps_StageField(updatedRegImage, fieldMask, REG_FIELD_VALUE(fieldPos, value));

	*pRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ----------------------------------- Local Channel Index Helpers ------------------------------------ //

/**
 * @brief Decodes a Timer single-channel mask into a zero-based channel index
 * @param[in] channel Timer single-channel mask
 * Accepted values:
 * - @ref `TIMx_CHANNEL_1`: Decode channel 1 index
 * - @ref `TIMx_CHANNEL_2`: Decode channel 2 index
 * - @ref `TIMx_CHANNEL_3`: Decode channel 3 index
 * - @ref `TIMx_CHANNEL_4`: Decode channel 4 index
 * @param[out] pChannelIndex Destination for decoded channel index
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Channel index was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pChannelIndex is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not exactly one valid channel
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_GetChannelIndexFromMask
(
	const tim_channel_t			channel,
	tim_channel_index_t* const	pChannelIndex
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

// -------------------------------- Local CCMR Field Position Helpers --------------------------------- //

/**
 * @brief Returns the hardware `CCxS` field position for one channel index
 * @param[in] channelIndex Zero-based channel index
 * @returns Register-positioned `CCxS` bit position as @ref `reg_bit_pos_t`
 */
__STATIC_FORCEINLINE reg_bit_pos_t Codec_TIM_GetCCMRCcsPos(const tim_channel_index_t channelIndex)
{
	reg_bit_pos_t fieldPos = TIM_CCMR1_CC1S_Pos;

	//! Map public channel indexes to concrete CCMR field positions owned by the Timer register layer.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = TIM_CCMR1_CC1S_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = TIM_CCMR1_CC2S_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = TIM_CCMR2_CC3S_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = TIM_CCMR2_CC4S_Pos;
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
 * @returns Register-positioned `OCxFE` bit position as @ref `reg_bit_pos_t`
 */
__STATIC_FORCEINLINE reg_bit_pos_t Codec_TIM_GetCCMROcFastPos(const tim_channel_index_t channelIndex)
{
	reg_bit_pos_t fieldPos = TIM_CCMR1_OC1FE_Pos;

	//! Map public channel indexes to concrete CCMR output-compare fast-enable positions.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = TIM_CCMR1_OC1FE_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = TIM_CCMR1_OC2FE_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = TIM_CCMR2_OC3FE_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = TIM_CCMR2_OC4FE_Pos;
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
 * @returns Register-positioned `OCxPE` bit position as @ref `reg_bit_pos_t`
 */
__STATIC_FORCEINLINE reg_bit_pos_t Codec_TIM_GetCCMROcPreloadPos(const tim_channel_index_t channelIndex)
{
	reg_bit_pos_t fieldPos = TIM_CCMR1_OC1PE_Pos;

	//! Map public channel indexes to concrete CCMR output-compare preload-enable positions.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = TIM_CCMR1_OC1PE_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = TIM_CCMR1_OC2PE_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = TIM_CCMR2_OC3PE_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = TIM_CCMR2_OC4PE_Pos;
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
 * @returns Register-positioned `OCxM` bit position as @ref `reg_bit_pos_t`
 */
__STATIC_FORCEINLINE reg_bit_pos_t Codec_TIM_GetCCMROcModePos(const tim_channel_index_t channelIndex)
{
	reg_bit_pos_t fieldPos = TIM_CCMR1_OC1M_Pos;

	//! Map public channel indexes to concrete CCMR output-compare mode positions.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = TIM_CCMR1_OC1M_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = TIM_CCMR1_OC2M_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = TIM_CCMR2_OC3M_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = TIM_CCMR2_OC4M_Pos;
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
 * @returns Register-positioned `OCxCE` bit position as @ref `reg_bit_pos_t`
 */
__STATIC_FORCEINLINE reg_bit_pos_t Codec_TIM_GetCCMROcClearPos(const tim_channel_index_t channelIndex)
{
	reg_bit_pos_t fieldPos = TIM_CCMR1_OC1CE_Pos;

	//! Map public channel indexes to concrete CCMR output-compare clear-enable positions.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = TIM_CCMR1_OC1CE_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = TIM_CCMR1_OC2CE_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = TIM_CCMR2_OC3CE_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = TIM_CCMR2_OC4CE_Pos;
			break;
		}
		default:
		{
			break;
		}
	}

	return fieldPos;
}

// -------------------------------- Local CCER Field Position Helpers --------------------------------- //

/**
 * @brief Returns the hardware `CCxE` field position for one channel index inside `CCER`
 * @param[in] channelIndex Zero-based channel index
 * @returns Register-positioned `CCxE` bit position as @ref `reg_bit_pos_t`
 */
__STATIC_FORCEINLINE reg_bit_pos_t Codec_TIM_GetCCEREnablePos(const tim_channel_index_t channelIndex)
{
	reg_bit_pos_t fieldPos = TIM_CCER_CC1E_Pos;

	//! Map public channel indexes to concrete CCER enable-bit positions.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = TIM_CCER_CC1E_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = TIM_CCER_CC2E_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = TIM_CCER_CC3E_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = TIM_CCER_CC4E_Pos;
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
 * @returns Register-positioned `CCxP` bit position as @ref `reg_bit_pos_t`
 */
__STATIC_FORCEINLINE reg_bit_pos_t Codec_TIM_GetCCERPolarityPos(const tim_channel_index_t channelIndex)
{
	reg_bit_pos_t fieldPos = TIM_CCER_CC1P_Pos;

	//! Map public channel indexes to concrete CCER polarity-bit positions.
	switch (channelIndex)
	{
		case 0U:
		{
			fieldPos = TIM_CCER_CC1P_Pos;
			break;
		}
		case 1U:
		{
			fieldPos = TIM_CCER_CC2P_Pos;
			break;
		}
		case 2U:
		{
			fieldPos = TIM_CCER_CC3P_Pos;
			break;
		}
		case 3U:
		{
			fieldPos = TIM_CCER_CC4P_Pos;
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
//										Local Selector Translation Helpers								//
// ==================================================================================================== //

// ------------------------------ Local CR1 Selector Translation Helpers ------------------------------ //

/**
 * @brief Encodes a count-mode selector into a register-positioned `CR1.CMS` value
 * @param[in] mode Timer count-mode selector
 * Accepted values:
 * - @ref `TIMx_MODE_NORMAL`: Edge-aligned counter mode
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING`: Center-aligned mode 1
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING`: Center-aligned mode 2
 * - @ref `TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING`: Center-aligned mode 3
 * @param[out] pFieldSet Destination for register-positioned `CR1.CMS` value
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Count mode was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFieldSet is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p mode is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeCountModeToCR1
(
	const tim_count_mode_t	mode,
	reg* const					pFieldSet
)
{
	if (pFieldSet == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Public count-mode names describe behavior; CR1.CMS stores the corresponding hardware encoding.
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
 * Accepted values:
 * - @ref `TIM_CR1_CMS_EDGE_ALIGNED`: Edge-aligned hardware encoding
 * - @ref `TIM_CR1_CMS_CENTER_ALIGNED_MODE_1`: Center-aligned mode 1 hardware encoding
 * - @ref `TIM_CR1_CMS_CENTER_ALIGNED_MODE_2`: Center-aligned mode 2 hardware encoding
 * - @ref `TIM_CR1_CMS_CENTER_ALIGNED_MODE_3`: Center-aligned mode 3 hardware encoding
 * @param[out] pMode Destination for decoded count-mode selector
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Count mode was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pMode is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p fieldSet is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeCR1ToCountMode
(
	const reg					fieldSet,
	tim_count_mode_t* const	pMode
)
{
	if (pMode == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Mask first so reserved or unrelated CR1 bits cannot influence the decode table.
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
 * Accepted values:
 * - @ref `TIMx_CKD_CLK_FREQ`: `t_DTS = t_CK_INT`
 * - @ref `TIMx_CKD_CLK_2_FREQ`: `t_DTS = 2 * t_CK_INT`
 * - @ref `TIMx_CKD_CLK_4_FREQ`: `t_DTS = 4 * t_CK_INT`
 * @param[out] pFieldSet Destination for register-positioned `CR1.CKD` value
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock division was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFieldSet is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p clockDivision is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeClockDivisionToCR1
(
	const tim_clock_division_t	clockDivision,
	reg* const						pFieldSet
)
{
	if (pFieldSet == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Public CKD selectors are translated to the register-positioned TDTS sampling-clock encodings.
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
 * Accepted values:
 * - @ref `TIM_CR1_CKD_TDTS_TCK_INT`: `t_DTS = t_CK_INT`
 * - @ref `TIM_CR1_CKD_TDTS_2_TCK_INT`: `t_DTS = 2 * t_CK_INT`
 * - @ref `TIM_CR1_CKD_TDTS_4_TCK_INT`: `t_DTS = 4 * t_CK_INT`
 * @param[out] pClockDivision Destination for decoded clock-division selector
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Clock division was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pClockDivision is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p fieldSet is reserved or unsupported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeCR1ToClockDivision
(
	const reg							fieldSet,
	tim_clock_division_t* const		pClockDivision
)
{
	if (pClockDivision == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Mask CKD before decoding so only the two clock-division bits reach the switch table.
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

// ---------------------------- Local Trigger Selector Translation Helpers ---------------------------- //

/**
 * @brief Encodes a master-mode selector into a register-positioned `CR2.MMS` value
 * @param[in] masterMode Timer master-mode selector
 * Accepted values:
 * - @ref `TIMx_MMS_RESET`: Reset trigger output
 * - @ref `TIMx_MMS_ENABLE`: Counter-enable trigger output
 * - @ref `TIMx_MMS_UPDATE`: Update-event trigger output
 * - @ref `TIMx_MMS_CMP_PULSE`: Compare-pulse trigger output
 * - @ref `TIMx_MMS_CMP_OC1REF`: Output compare 1 reference trigger output
 * - @ref `TIMx_MMS_CMP_OC2REF`: Output compare 2 reference trigger output
 * - @ref `TIMx_MMS_CMP_OC3REF`: Output compare 3 reference trigger output
 * - @ref `TIMx_MMS_CMP_OC4REF`: Output compare 4 reference trigger output
 * @param[out] pFieldSet Destination for register-positioned `CR2.MMS` value
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Master mode was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFieldSet is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p masterMode is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeMasterModeToCR2
(
	const tim_master_mode_t	masterMode,
	reg* const					pFieldSet
)
{
	if (pFieldSet == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Master-mode selectors are policy names; CR2.MMS needs the raw trigger-output encoding.
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
 * Accepted values:
 * - @ref `TIM_CR2_MMS_RESET`: Reset trigger-output encoding
 * - @ref `TIM_CR2_MMS_ENABLE`: Counter-enable trigger-output encoding
 * - @ref `TIM_CR2_MMS_UPDATE`: Update trigger-output encoding
 * - @ref `TIM_CR2_MMS_COMPARE_PULSE`: Compare-pulse trigger-output encoding
 * - @ref `TIM_CR2_MMS_COMPARE_OC1REF`: Output compare 1 reference trigger-output encoding
 * - @ref `TIM_CR2_MMS_COMPARE_OC2REF`: Output compare 2 reference trigger-output encoding
 * - @ref `TIM_CR2_MMS_COMPARE_OC3REF`: Output compare 3 reference trigger-output encoding
 * - @ref `TIM_CR2_MMS_COMPARE_OC4REF`: Output compare 4 reference trigger-output encoding
 * @param[out] pMasterMode Destination for decoded master-mode selector
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Master mode was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pMasterMode is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p fieldSet is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeCR2ToMasterMode
(
	const reg							fieldSet,
	tim_master_mode_t* const			pMasterMode
)
{
	if (pMasterMode == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Decode only CR2.MMS and reject raw values outside the public master-mode vocabulary.
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
 * Accepted values:
 * - @ref `TIMx_SMS_DISABLE`: Slave mode disabled
 * - @ref `TIMx_SMS_ENC_MODE1`: Encoder mode 1
 * - @ref `TIMx_SMS_ENC_MODE2`: Encoder mode 2
 * - @ref `TIMx_SMS_ENC_MODE3`: Encoder mode 3
 * @param[out] pFieldSet Destination for register-positioned `SMCR.SMS` value
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Slave mode was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pFieldSet is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p slaveMode is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeSlaveModeToSMCR
(
	const tim_slave_mode_t	slaveMode,
	reg* const					pFieldSet
)
{
	if (pFieldSet == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Current public slave-mode support is intentionally limited to disabled and encoder modes.
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
 * Accepted values:
 * - @ref `TIM_SMCR_SMS_DISABLED`: Slave mode disabled hardware encoding
 * - @ref `TIM_SMCR_SMS_ENCODER_MODE_1`: Encoder mode 1 hardware encoding
 * - @ref `TIM_SMCR_SMS_ENCODER_MODE_2`: Encoder mode 2 hardware encoding
 * - @ref `TIM_SMCR_SMS_ENCODER_MODE_3`: Encoder mode 3 hardware encoding
 * @param[out] pSlaveMode Destination for decoded slave-mode selector
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Slave mode was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pSlaveMode is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p fieldSet is outside the current public Timer vocabulary
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeSMCRToSlaveMode
(
	const reg							fieldSet,
	tim_slave_mode_t* const			pSlaveMode
)
{
	if (pSlaveMode == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Mask SMS first so trigger-selection and other SMCR bits cannot affect slave-mode decode.
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

// ----------------------------- Local CCMR Selector Translation Helpers ------------------------------ //

/**
 * @brief Encodes a channel capture/compare selector into a CCMR-local `CCxS` value
 * @param[in] captureCompareSelection Timer capture/compare selector
 * Accepted values:
 * - @ref `TIMx_CHANNEL_CCS_OUTPUT`: Channel configured as output compare
 * - @ref `TIMx_CHANNEL_CCS_INPUT_TIx`: Input capture mapped to direct TI input
 * - @ref `TIMx_CHANNEL_CCS_INPUT_TIx_1`: Input capture mapped to indirect TI input
 * - @ref `TIMx_CHANNEL_CCS_INPUT_TRC`: Input capture mapped to TRC
 * @param[out] pRawField Destination for right-aligned CCMR shared encoding
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Capture/compare selector was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRawField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p captureCompareSelection is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeChannelSelectionToCCMR
(
	const tim_channel_ccs_t	captureCompareSelection,
	reg_field_t* const			pRawField
)
{
	if (pRawField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! CCxS has one shared two-bit encoding per channel slot; the position is handled separately.
	switch (captureCompareSelection)
	{
		case TIMx_CHANNEL_CCS_OUTPUT:
		{
			*pRawField = TIM_CCMR_CCxS_OUTPUT;
			break;
		}
		case TIMx_CHANNEL_CCS_INPUT_TIx:
		{
			*pRawField = TIM_CCMR_CCxS_INPUT_DIRECT_TI;
			break;
		}
		case TIMx_CHANNEL_CCS_INPUT_TIx_1:
		{
			*pRawField = TIM_CCMR_CCxS_INPUT_INDIRECT_TI;
			break;
		}
		case TIMx_CHANNEL_CCS_INPUT_TRC:
		{
			*pRawField = TIM_CCMR_CCxS_INPUT_TRC;
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
 * Accepted values:
 * - @ref `TIM_CCMR_CCxS_OUTPUT`: Output compare hardware encoding
 * - @ref `TIM_CCMR_CCxS_INPUT_DIRECT_TI`: Direct TI input-capture hardware encoding
 * - @ref `TIM_CCMR_CCxS_INPUT_INDIRECT_TI`: Indirect TI input-capture hardware encoding
 * - @ref `TIM_CCMR_CCxS_INPUT_TRC`: TRC input-capture hardware encoding
 * @param[out] pCaptureCompareSelection Destination for decoded capture/compare selector
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Capture/compare selector was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pCaptureCompareSelection is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p rawField is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeCCMRToChannelSelection
(
	const reg_field_t					rawField,
	tim_channel_ccs_t* const			pCaptureCompareSelection
)
{
	if (pCaptureCompareSelection == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! rawField is already right-aligned, so decode directly through the shared CCxS table.
	switch (rawField)
	{
		case TIM_CCMR_CCxS_OUTPUT:
		{
			*pCaptureCompareSelection = TIMx_CHANNEL_CCS_OUTPUT;
			break;
		}
		case TIM_CCMR_CCxS_INPUT_DIRECT_TI:
		{
			*pCaptureCompareSelection = TIMx_CHANNEL_CCS_INPUT_TIx;
			break;
		}
		case TIM_CCMR_CCxS_INPUT_INDIRECT_TI:
		{
			*pCaptureCompareSelection = TIMx_CHANNEL_CCS_INPUT_TIx_1;
			break;
		}
		case TIM_CCMR_CCxS_INPUT_TRC:
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
 * Accepted values:
 * - @ref `TIMx_CHANNEL_MODE_FREEZE`: Freeze output compare output
 * - @ref `TIMx_CHANNEL_MODE_SET_CH`: Set output active on match
 * - @ref `TIMx_CHANNEL_MODE_RESET_CH`: Reset output inactive on match
 * - @ref `TIMx_CHANNEL_MODE_TOGGLE`: Toggle output on match
 * - @ref `TIMx_CHANNEL_MODE_FORCE_RESET`: Force output inactive
 * - @ref `TIMx_CHANNEL_MODE_FORCE_SET`: Force output active
 * - @ref `TIMx_CHANNEL_MODE_PWM1`: PWM mode 1
 * - @ref `TIMx_CHANNEL_MODE_PWM2`: PWM mode 2
 * @param[out] pRawField Destination for right-aligned CCMR shared encoding
 * @returns Encode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Output-compare mode was encoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pRawField is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p outputCompareMode is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_EncodeOutputCompareModeToCCMR
(
	const tim_channel_mode_t			outputCompareMode,
	reg_field_t* const					pRawField
)
{
	if (pRawField == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! OCxM is a three-bit shared encoding; the channel-specific bit position is handled by callers.
	switch (outputCompareMode)
	{
		case TIMx_CHANNEL_MODE_FREEZE:
		{
			*pRawField = TIM_CCMR_OCxM_FROZEN;
			break;
		}
		case TIMx_CHANNEL_MODE_SET_CH:
		{
			*pRawField = TIM_CCMR_OCxM_ACTIVE_ON_MATCH;
			break;
		}
		case TIMx_CHANNEL_MODE_RESET_CH:
		{
			*pRawField = TIM_CCMR_OCxM_INACTIVE_ON_MATCH;
			break;
		}
		case TIMx_CHANNEL_MODE_TOGGLE:
		{
			*pRawField = TIM_CCMR_OCxM_TOGGLE_ON_MATCH;
			break;
		}
		case TIMx_CHANNEL_MODE_FORCE_RESET:
		{
			*pRawField = TIM_CCMR_OCxM_FORCE_INACTIVE;
			break;
		}
		case TIMx_CHANNEL_MODE_FORCE_SET:
		{
			*pRawField = TIM_CCMR_OCxM_FORCE_ACTIVE;
			break;
		}
		case TIMx_CHANNEL_MODE_PWM1:
		{
			*pRawField = TIM_CCMR_OCxM_PWM_MODE_1;
			break;
		}
		case TIMx_CHANNEL_MODE_PWM2:
		{
			*pRawField = TIM_CCMR_OCxM_PWM_MODE_2;
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
 * Accepted values:
 * - @ref `TIM_CCMR_OCxM_FROZEN`: Frozen output-compare hardware encoding
 * - @ref `TIM_CCMR_OCxM_ACTIVE_ON_MATCH`: Active-on-match hardware encoding
 * - @ref `TIM_CCMR_OCxM_INACTIVE_ON_MATCH`: Inactive-on-match hardware encoding
 * - @ref `TIM_CCMR_OCxM_TOGGLE_ON_MATCH`: Toggle-on-match hardware encoding
 * - @ref `TIM_CCMR_OCxM_FORCE_INACTIVE`: Force-inactive hardware encoding
 * - @ref `TIM_CCMR_OCxM_FORCE_ACTIVE`: Force-active hardware encoding
 * - @ref `TIM_CCMR_OCxM_PWM_MODE_1`: PWM mode 1 hardware encoding
 * - @ref `TIM_CCMR_OCxM_PWM_MODE_2`: PWM mode 2 hardware encoding
 * @param[out] pOutputCompareMode Destination for decoded output-compare mode selector
 * @returns Decode status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Output-compare mode was decoded
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pOutputCompareMode is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p rawField is not supported
 */
__STATIC_FORCEINLINE driver_status_t Codec_TIM_DecodeCCMRToOutputCompareMode
(
	const reg_field_t					rawField,
	tim_channel_mode_t* const			pOutputCompareMode
)
{
	if (pOutputCompareMode == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! rawField is right-aligned before decode, so the table stays independent of CCMR1/CCMR2 position.
	switch (rawField)
	{
		case TIM_CCMR_OCxM_FROZEN:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_FREEZE;
			break;
		}
		case TIM_CCMR_OCxM_ACTIVE_ON_MATCH:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_SET_CH;
			break;
		}
		case TIM_CCMR_OCxM_INACTIVE_ON_MATCH:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_RESET_CH;
			break;
		}
		case TIM_CCMR_OCxM_TOGGLE_ON_MATCH:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_TOGGLE;
			break;
		}
		case TIM_CCMR_OCxM_FORCE_INACTIVE:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_FORCE_RESET;
			break;
		}
		case TIM_CCMR_OCxM_FORCE_ACTIVE:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_FORCE_SET;
			break;
		}
		case TIM_CCMR_OCxM_PWM_MODE_1:
		{
			*pOutputCompareMode = TIMx_CHANNEL_MODE_PWM1;
			break;
		}
		case TIM_CCMR_OCxM_PWM_MODE_2:
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

// ------------------------------ Local DIER/SR Mask Translation Helpers ------------------------------ //

/**
 * @brief Encodes a Timer IRQ selector mask into raw `DIER` interrupt bits
 * @param[in] irqMask Timer IRQ selector mask
 * Accepted values:
 * - @ref `TIMx_IRQ_OVF_UVF`: Update overflow/underflow IRQ source
 * - @ref `TIMx_IRQ_OUT_CMP_CH1`: Channel 1 output-compare/input-capture IRQ source
 * - @ref `TIMx_IRQ_OUT_CMP_CH2`: Channel 2 output-compare/input-capture IRQ source
 * - @ref `TIMx_IRQ_OUT_CMP_CH3`: Channel 3 output-compare/input-capture IRQ source
 * - @ref `TIMx_IRQ_OUT_CMP_CH4`: Channel 4 output-compare/input-capture IRQ source
 * - @ref `TIMx_IRQ_ALL`: All supported IRQ sources
 * @returns Raw `DIER` interrupt bit mask
 */
__STATIC_FORCEINLINE reg Codec_TIM_EncodeIRQMaskToDIERRaw(const tim_irq_t irqMask)
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
 * Accepted values:
 * - @ref `TIMx_IRQ_OVF_UVF`: Update overflow/underflow IRQ flag
 * - @ref `TIMx_IRQ_OUT_CMP_CH1`: Channel 1 output-compare/input-capture IRQ flag
 * - @ref `TIMx_IRQ_OUT_CMP_CH2`: Channel 2 output-compare/input-capture IRQ flag
 * - @ref `TIMx_IRQ_OUT_CMP_CH3`: Channel 3 output-compare/input-capture IRQ flag
 * - @ref `TIMx_IRQ_OUT_CMP_CH4`: Channel 4 output-compare/input-capture IRQ flag
 * - @ref `TIMx_IRQ_ALL`: All supported IRQ flags
 * @returns Raw `SR` flag bit mask
 */
__STATIC_FORCEINLINE reg Codec_TIM_EncodeIRQMaskToSRRaw(const tim_irq_t irqMask)
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
 * Accepted values:
 * - @ref `TIMx_DMA_UPDATE`: Update DMA source
 * - @ref `TIMx_DMA_CC1DE`: Channel 1 capture/compare DMA source
 * - @ref `TIMx_DMA_CC2DE`: Channel 2 capture/compare DMA source
 * - @ref `TIMx_DMA_CC3DE`: Channel 3 capture/compare DMA source
 * - @ref `TIMx_DMA_CC4DE`: Channel 4 capture/compare DMA source
 * - @ref `TIMx_DMA_ALL`: All supported DMA sources
 * @returns Raw `DIER` DMA bit mask
 */
__STATIC_FORCEINLINE reg Codec_TIM_EncodeDMAMaskToDIERRaw(const tim_dma_t dmaMask)
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

// ----------------------------------- Timer Timebase Scalar Codecs ----------------------------------- //

driver_status_t Codec_TIM_ExtractPrescaler
(
	const reg							pscRegImage,
	tim_prescaler_t* const			pPrescaler
)
{
	if (pPrescaler == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! PSC is a 16-bit scalar field; the codec only extracts the caller-owned image.
	*pPrescaler = (tim_prescaler_t) RegOps_ExtractFieldValue(pscRegImage, TIM_PSC_PSC, TIM_PSC_PSC_Pos);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StagePrescaler
(
	reg* const							pPscRegImage,
	const tim_prescaler_t				prescaler
)
{
	//! Preserve any non-PSC bits in the caller-owned image while replacing PSC[15:0].
	return Codec_TIM_StageScalarField(pPscRegImage, TIM_PSC_PSC, TIM_PSC_PSC_Pos, (reg) prescaler);
}

driver_status_t Codec_TIM_ExtractAutoReload
(
	const reg							arrRegImage,
	tim_auto_reload_t* const			pAutoReload
)
{
	if (pAutoReload == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! ARR is a 16-bit scalar field; the codec does not infer update period or frequency.
	*pAutoReload = (tim_auto_reload_t) RegOps_ExtractFieldValue(arrRegImage, TIM_ARR_ARR, TIM_ARR_ARR_Pos);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageAutoReload
(
	reg* const							pArrRegImage,
	const tim_auto_reload_t			autoReload
)
{
	//! Stage the register-backed ARR value directly; timing policy remains in the driver layer.
	return Codec_TIM_StageScalarField(pArrRegImage, TIM_ARR_ARR, TIM_ARR_ARR_Pos, (reg) autoReload);
}

driver_status_t Codec_TIM_ExtractCounterValue
(
	const reg							cntRegImage,
	tim_counter_value_t* const		pCounterValue
)
{
	if (pCounterValue == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! CNT is a 16-bit scalar field; extract only the hardware image value.
	*pCounterValue = (tim_counter_value_t) RegOps_ExtractFieldValue(cntRegImage, TIM_CNT_CNT, TIM_CNT_CNT_Pos);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageCounterValue
(
	reg* const							pCntRegImage,
	const tim_counter_value_t			counterValue
)
{
	//! Stage the raw CNT value without deciding whether the counter should be stopped first.
	return Codec_TIM_StageScalarField(pCntRegImage, TIM_CNT_CNT, TIM_CNT_CNT_Pos, (reg) counterValue);
}

// ----------------------------------- Timer Timebase Config Codecs ----------------------------------- //

driver_status_t Codec_TIM_ExtractTimeBaseConfig
(
	const reg							pscRegImage,
	const reg							arrRegImage,
	const reg							cntRegImage,
	tim_config_timebase_t* const		pTimebase
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
	reg* const								pPscRegImage,
	reg* const								pArrRegImage,
	reg* const								pCntRegImage,
	const tim_config_timebase_t* const	pTimebase
)
{
	// Validate Input
	if ((pTimebase == NULL) || (pPscRegImage == NULL) || (pArrRegImage == NULL) || (pCntRegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	// Local Variables
	reg updatedPscRegImage = 0x00000000UL;
	reg updatedArrRegImage = 0x00000000UL;
	reg updatedCntRegImage = 0x00000000UL;

	//! Operate on these registers
	updatedPscRegImage = *pPscRegImage;
	updatedArrRegImage = *pArrRegImage;
	updatedCntRegImage = *pCntRegImage;

	//! Stage every timebase register image independently so the driver can later dirty-write each one.
	ASSERT_DRIVER_STATUS(Codec_TIM_StagePrescaler(&updatedPscRegImage, pTimebase->prescaler));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageAutoReload(&updatedArrRegImage, pTimebase->auto_reload));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterValue(&updatedCntRegImage, pTimebase->initial_count));

	//! Update the pointed register images with the staged values
	*pPscRegImage = updatedPscRegImage;
	*pArrRegImage = updatedArrRegImage;
	*pCntRegImage = updatedCntRegImage;
	
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer CR1 Counter Codecs										//
// ==================================================================================================== //

// -------------------------------- Timer CR1 Counter Selector Codecs --------------------------------- //

driver_status_t Codec_TIM_ExtractCounterDirection
(
	const reg							cr1RegImage,
	tim_direction_t* const			pDirection
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pDirection == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! `DIR` is the raw direction field and maps directly to the public direction selector.
	rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_DIR, TIM_CR1_DIR_Pos);
	if (TIM_DIRECTION_IS_VALID(rawField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pDirection = (tim_direction_t) rawField;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageCounterDirection
(
	reg* const							pCr1RegImage,
	const tim_direction_t				direction
)
{
	reg updatedRegImage = 0x00000000UL;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pCr1RegImage;

	//! Stage only DIR, preserving all other CR1 bits in the caller-owned image.
	if (TIM_DIRECTION_IS_VALID(direction) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	rawField = (reg_field_t) direction;
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, TIM_CR1_DIR_Pos, rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	*pCr1RegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_ExtractCounterAlignment
(
	const reg							cr1RegImage,
	tim_count_mode_t* const			pAlignment
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
	reg* const							pCr1RegImage,
	const tim_count_mode_t			alignment
)
{
	reg updatedRegImage = 0x00000000UL;
	reg fieldSet = 0x00000000UL;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pCr1RegImage;

	//! Convert the public alignment selector into the register-positioned CMS field.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeCountModeToCR1(alignment, &fieldSet));
	updatedRegImage = RegOps_StageField(updatedRegImage, TIM_CR1_CMS, fieldSet);

	*pCr1RegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_ExtractOnePulse
(
	const reg							cr1RegImage,
	tim_opm_t* const					pOnePulse
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pOnePulse == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! `OPM` is a one-bit selector: continuous counting versus one-pulse mode.
	rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_OPM, TIM_CR1_OPM_Pos);
	if (TIM_OPM_IS_VALID(rawField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pOnePulse = (tim_opm_t) rawField;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageOnePulse
(
	reg* const							pCr1RegImage,
	const tim_opm_t					onePulse
)
{
	reg updatedRegImage = 0x00000000UL;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pCr1RegImage;

	//! Stage only OPM, preserving all unrelated CR1 fields.
	if (TIM_OPM_IS_VALID(onePulse) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	rawField = (reg_field_t) onePulse;
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, TIM_CR1_OPM_Pos, rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	*pCr1RegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_ExtractAutoReloadPreload
(
	const reg							cr1RegImage,
	tim_arpe_t* const					pAutoReloadPreload
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pAutoReloadPreload == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! `ARPE` controls whether ARR updates are buffered until update events.
	rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_ARPE, TIM_CR1_ARPE_Pos);
	if (TIM_ARPE_IS_VALID(rawField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pAutoReloadPreload = (tim_arpe_t) rawField;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageAutoReloadPreload
(
	reg* const							pCr1RegImage,
	const tim_arpe_t					autoReloadPreload
)
{
	reg updatedRegImage = 0x00000000UL;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pCr1RegImage;

	//! Stage only ARPE, preserving all unrelated CR1 fields.
	if (TIM_ARPE_IS_VALID(autoReloadPreload) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	rawField = (reg_field_t) autoReloadPreload;
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, TIM_CR1_ARPE_Pos, rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	*pCr1RegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_ExtractUpdateSource
(
	const reg							cr1RegImage,
	tim_update_source_t* const			pUpdateSource
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pUpdateSource == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! `URS` selects whether any update source or only overflow/DMA sources generate update requests.
	rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_URS, TIM_CR1_URS_Pos);
	if (TIM_UPDATE_SOURCE_IS_VALID(rawField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pUpdateSource = (tim_update_source_t) rawField;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageUpdateSource
(
	reg* const							pCr1RegImage,
	const tim_update_source_t			updateSource
)
{
	reg updatedRegImage = 0x00000000UL;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pCr1RegImage;

	//! Stage only URS; update-event enable state is still owned by UDIS helpers.
	if (TIM_UPDATE_SOURCE_IS_VALID(updateSource) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	rawField = (reg_field_t) updateSource;
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, TIM_CR1_URS_Pos, rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	*pCr1RegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_ExtractClockDivision
(
	const reg							cr1RegImage,
	tim_clock_division_t* const		pClockDivision
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
	reg* const							pCr1RegImage,
	const tim_clock_division_t			clockDivision
)
{
	reg updatedRegImage = 0x00000000UL;
	reg fieldSet = 0x00000000UL;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pCr1RegImage;

	//! Convert the public CKD selector into the register-positioned CKD field.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeClockDivisionToCR1(clockDivision, &fieldSet));
	updatedRegImage = RegOps_StageField(updatedRegImage, TIM_CR1_CKD, fieldSet);

	*pCr1RegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// --------------------------------- Timer CR1 Counter Config Codecs ---------------------------------- //

driver_status_t Codec_TIM_ExtractCounterConfig
(
	const reg							cr1RegImage,
	tim_config_counter_t* const		pCounter
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
	reg* const							pCr1RegImage,
	const tim_config_counter_t* const	pCounter
)
{
	// Validate Input
	if ((pCounter == NULL) || (pCr1RegImage == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	// Local Variable
	reg updatedRegImage = 0x00000000UL;
	updatedRegImage = *pCr1RegImage;

	//! Group staging composes individual CR1 field stages so each field API has one implementation path.
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterDirection(&updatedRegImage, pCounter->direction));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageCounterAlignment(&updatedRegImage, pCounter->alignment));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageOnePulse(&updatedRegImage, pCounter->one_pulse));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageAutoReloadPreload(&updatedRegImage, pCounter->auto_reload_preload));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageUpdateSource(&updatedRegImage, pCounter->update_source));
	ASSERT_DRIVER_STATUS(Codec_TIM_StageClockDivision(&updatedRegImage, pCounter->clock_division));

	*pCr1RegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ---------------------------------- Timer CR1 Runtime State Codecs ---------------------------------- //

driver_status_t Codec_TIM_ExtractCounterEnableState(const reg cr1RegImage)
{
	//! CEN uses normal positive polarity: clear means the counter is stopped, set means it runs.
	return Codec_TIM_ExtractBitStateFromImage(cr1RegImage, TIM_CR1_CEN);
}

driver_status_t Codec_TIM_StageCounterEnableState
(
	reg* const							pCr1RegImage,
	const driver_status_t				counterState
)
{
	//! CEN follows the generic ON/OFF bit-state convention, so no Timer-specific inversion is needed.
	return Codec_TIM_StageBitStateInImage(pCr1RegImage, TIM_CR1_CEN, counterState);
}

driver_status_t Codec_TIM_ExtractUpdateEventState(const reg cr1RegImage)
{
	//! CR1.UDIS uses inverse polarity: bit set means update events are disabled.
	return ((cr1RegImage & TIM_CR1_UDIS) != 0x00000000UL) ? DRIVER_STATUS_OFF : DRIVER_STATUS_ON;
}

driver_status_t Codec_TIM_StageUpdateEventState
(
	reg* const							pCr1RegImage,
	const driver_status_t				updateEventState
)
{
	// Validate Input
	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	ASSERT_DRIVER_STATUS(Codec_TIM_ValidateState(updateEventState));

	// Local Variables
	reg updatedRegImage = 0x00000000UL;
	reg bitSet = 0x00000000UL;
	updatedRegImage = *pCr1RegImage;

	//! Convert driver-facing ON/OFF into inverse raw UDIS semantics.
	bitSet = (updateEventState == DRIVER_STATUS_OFF) ? TIM_CR1_UDIS : 0x00000000UL;
	updatedRegImage = RegOps_StageField(updatedRegImage, TIM_CR1_UDIS, bitSet);

	*pCr1RegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Update Event Codecs										//
// ==================================================================================================== //

// ---------------------------------- Timer EGR Update Event Codecs ----------------------------------- //

driver_status_t Codec_TIM_StageUpdateEventGeneration(reg* const pEgrRegImage)
{
	reg updatedRegImage = 0x00000000UL;

	if (pEgrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pEgrRegImage;

	//! EGR is an action register; staging UG prepares the exact write image that generates one update event.
	updatedRegImage = RegOps_StageField(updatedRegImage, TIM_EGR_UG, TIM_EGR_UG);

	*pEgrRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ----------------------------------- Timer SR Update Flag Codecs ------------------------------------ //

driver_status_t Codec_TIM_ExtractUpdateFlagState(const reg srRegImage)
{
	//! UIF uses normal positive polarity: clear means no update flag, set means update flag pending.
	return Codec_TIM_ExtractBitStateFromImage(srRegImage, TIM_SR_UIF);
}

driver_status_t Codec_TIM_StageUpdateFlagClear(reg* const pSrRegImage)
{
	// Validate Input
	if (pSrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	// Local Variable
	reg updatedRegImage = *pSrRegImage;

	//! SR flags are write-0-to-clear; write 1 to all other supported flags so only UIF is acknowledged.
	updatedRegImage |= (TIM_CODEC_SR_W0C_FLAG_MASK & ~TIM_SR_UIF);
	updatedRegImage &= ~TIM_SR_UIF;

	*pSrRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer Trigger Codecs											//
// ==================================================================================================== //

// ------------------------------------- Timer Master Mode Codecs ------------------------------------- //

driver_status_t Codec_TIM_ExtractMasterMode
(
	const reg							cr2RegImage,
	tim_master_mode_t* const			pMasterMode
)
{
	//! Decode the register-positioned MMS image through the explicit CR2 mapping table.
	return Codec_TIM_DecodeCR2ToMasterMode((cr2RegImage & TIM_CR2_MMS), pMasterMode);
}

driver_status_t Codec_TIM_StageMasterMode
(
	reg* const							pCr2RegImage,
	const tim_master_mode_t			masterMode
)
{
	reg updatedRegImage = 0x00000000UL;
	reg fieldSet = 0x00000000UL;

	if (pCr2RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pCr2RegImage;

	//! Translate the public master-mode selector before replacing only CR2.MMS.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeMasterModeToCR2(masterMode, &fieldSet));
	updatedRegImage = RegOps_StageField(updatedRegImage, TIM_CR2_MMS, fieldSet);

	*pCr2RegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ------------------------------------- Timer Slave Mode Codecs -------------------------------------- //

driver_status_t Codec_TIM_ExtractSlaveMode
(
	const reg							smcrRegImage,
	tim_slave_mode_t* const			pSlaveMode
)
{
	//! Decode the register-positioned SMS image through the explicit SMCR mapping table.
	return Codec_TIM_DecodeSMCRToSlaveMode((smcrRegImage & TIM_SMCR_SMS), pSlaveMode);
}

driver_status_t Codec_TIM_StageSlaveMode
(
	reg* const							pSmcrRegImage,
	const tim_slave_mode_t			slaveMode
)
{
	reg updatedRegImage = 0x00000000UL;
	reg fieldSet = 0x00000000UL;

	if (pSmcrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pSmcrRegImage;

	//! Translate the public slave-mode selector before replacing only SMCR.SMS.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSlaveModeToSMCR(slaveMode, &fieldSet));
	updatedRegImage = RegOps_StageField(updatedRegImage, TIM_SMCR_SMS, fieldSet);

	*pSmcrRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer CCMR Channel Codecs										//
// ==================================================================================================== //

// ------------------------------- Timer CCMR Channel Selection Codecs -------------------------------- //

driver_status_t Codec_TIM_ExtractChannelSelection
(
	const reg							ccmrRegImage,
	const tim_channel_t				channel,
	tim_channel_ccs_t* const			pCaptureCompareSelection
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
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
	reg* const							pCcmrRegImage,
	const tim_channel_t				channel,
	const tim_channel_ccs_t			captureCompareSelection
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
	reg updatedRegImage = 0x00000000UL;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCcmrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pCcmrRegImage;

	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeChannelSelectionToCCMR(captureCompareSelection, &rawField));

	//! Stage only CCxS; output-compare and input-capture mode fields are handled by dedicated codecs.
	updatedRegImage = RegOps_StageFieldValue
	(
		updatedRegImage,
		Codec_TIM_GetCCMRCcsPos(channelIndex),
		rawField,
		TIM_CODEC_FIELD_WIDTH_2BIT
	);

	*pCcmrRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// --------------------------------- Timer CCMR Output Compare Codecs --------------------------------- //

driver_status_t Codec_TIM_ExtractOutputCompareConfig
(
	const reg							ccmrRegImage,
	const tim_channel_t				channel,
	tim_channel_oc_clear_t* const		pOutputCompareClear,
	tim_channel_mode_t* const			pOutputCompareMode,
	tim_channel_oc_preload_t* const	pOutputComparePreload,
	tim_channel_oc_fast_t* const		pOutputCompareFast
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
	reg_field_t rawField = (reg_field_t) 0x00U;
	tim_channel_ccs_t captureCompareSelection = TIMx_CHANNEL_CCS_OUTPUT;

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
		if (TIM_CHANNEL_OC_CLEAR_IS_VALID(rawField) == 0x00U)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
		*pOutputCompareClear = (tim_channel_oc_clear_t) rawField;
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
		if (TIM_CHANNEL_OC_PRELOAD_IS_VALID(rawField) == 0x00U)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
		*pOutputComparePreload = (tim_channel_oc_preload_t) rawField;
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
		if (TIM_CHANNEL_OC_FAST_IS_VALID(rawField) == 0x00U)
		{
			return DRIVER_STATUS_ERROR_INVALID_ARG;
		}
		*pOutputCompareFast = (tim_channel_oc_fast_t) rawField;
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageOutputCompareConfig
(
	reg* const							pCcmrRegImage,
	const tim_channel_t				channel,
	const tim_channel_oc_clear_t		outputCompareClear,
	const tim_channel_mode_t			outputCompareMode,
	const tim_channel_oc_preload_t	outputComparePreload,
	const tim_channel_oc_fast_t		outputCompareFast
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
	reg updatedRegImage = 0x00000000UL;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCcmrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pCcmrRegImage;

	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));

	//! Force CCxS to output mode before staging OCx fields so the image has a coherent interpretation.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeChannelSelectionToCCMR(TIMx_CHANNEL_CCS_OUTPUT, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, Codec_TIM_GetCCMRCcsPos(channelIndex), rawField, TIM_CODEC_FIELD_WIDTH_2BIT);

	//! OCxCE is a direct one-bit selector; validate before staging the clear-enable bit.
	if (TIM_CHANNEL_OC_CLEAR_IS_VALID(outputCompareClear) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	rawField = (reg_field_t) outputCompareClear;
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, Codec_TIM_GetCCMROcClearPos(channelIndex), rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	//! OCxM has a three-bit hardware encoding, so stage it through the explicit mode map.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeOutputCompareModeToCCMR(outputCompareMode, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, Codec_TIM_GetCCMROcModePos(channelIndex), rawField, TIM_CODEC_FIELD_WIDTH_3BIT);

	//! OCxPE controls CCR buffering and is independent from the selected compare/PWM mode.
	if (TIM_CHANNEL_OC_PRELOAD_IS_VALID(outputComparePreload) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	rawField = (reg_field_t) outputComparePreload;
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, Codec_TIM_GetCCMROcPreloadPos(channelIndex), rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	//! OCxFE controls fast compare response and remains a separate one-bit field.
	if (TIM_CHANNEL_OC_FAST_IS_VALID(outputCompareFast) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	rawField = (reg_field_t) outputCompareFast;
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, Codec_TIM_GetCCMROcFastPos(channelIndex), rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	//! Publish the staged CCMR image only after all output-compare fields validate successfully.
	*pCcmrRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer CCER Channel Codecs										//
// ==================================================================================================== //

// --------------------------------- Timer CCER Channel Enable Codecs --------------------------------- //

driver_status_t Codec_TIM_ExtractChannelEnableState
(
	const reg							ccerRegImage,
	const tim_channel_t				channel
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;

	//! CCER channel enable bits sit in four-bit lanes selected from the channel index.
	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));
	return Codec_TIM_ExtractBitStateFromImage
	(
		ccerRegImage,
		REG_BIT_MASK(Codec_TIM_GetCCEREnablePos(channelIndex))
	);
}

driver_status_t Codec_TIM_StageChannelEnableState
(
	reg* const							pCCERRegImage,
	const tim_channel_t				channel,
	const driver_status_t				channelState
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;

	if (pCCERRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Stage only CCxE; polarity and reserved lane bits are preserved.
	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));
	return Codec_TIM_StageBitStateInImage
	(
		pCCERRegImage,
		REG_BIT_MASK(Codec_TIM_GetCCEREnablePos(channelIndex)),
		channelState
	);
}

// -------------------------------- Timer CCER Channel Polarity Codecs -------------------------------- //

driver_status_t Codec_TIM_ExtractChannelPolarity
(
	const reg							ccerRegImage,
	const tim_channel_t				channel,
	tim_channel_polarity_t* const		pPolarity
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
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
		REG_BIT_MASK(Codec_TIM_GetCCERPolarityPos(channelIndex)),
		Codec_TIM_GetCCERPolarityPos(channelIndex)
	);

	if (TIM_CHANNEL_POLARITY_IS_VALID(rawField) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	*pPolarity = (tim_channel_polarity_t) rawField;
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageChannelPolarity
(
	reg* const							pCCERRegImage,
	const tim_channel_t				channel,
	const tim_channel_polarity_t		polarity
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
	reg updatedRegImage = 0x00000000UL;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCCERRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pCCERRegImage;

	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));
	if (TIM_CHANNEL_POLARITY_IS_VALID(polarity) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	rawField = (reg_field_t) polarity;

	//! Stage only CCxP so channel enable state and reserved lane bits remain unchanged.
	updatedRegImage = RegOps_StageFieldValue
	(
		updatedRegImage,
		Codec_TIM_GetCCERPolarityPos(channelIndex),
		rawField,
		TIM_CODEC_FIELD_WIDTH_1BIT
	);

	*pCCERRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer DIER Request Codecs										//
// ==================================================================================================== //

// ---------------------------------- Timer DIER IRQ Request Codecs ----------------------------------- //

driver_status_t Codec_TIM_ExtractIRQEnableMask
(
	const reg							dierRegImage,
	tim_irq_t* const					pIrqMask
)
{
	if (pIrqMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Extract only DIER interrupt-enable bits represented by the public IRQ source mask.
	*pIrqMask = (tim_irq_t) Codec_TIM_DecodeDIERRawToIRQMask(dierRegImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageIRQEnableMask
(
	reg* const							pDierRegImage,
	const tim_irq_t					irqMask,
	const tim_irq_enable_t			irqEnable
)
{
	reg updatedRegImage = 0x00000000UL;
	reg rawMask = 0x00000000UL;
	reg rawSet = 0x00000000UL;

	if (pDierRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pDierRegImage;

	if ((TIM_IRQ_MASK_IS_VALID(irqMask) == 0x00U) || (TIM_IRQ_ENABLE_IS_VALID(irqEnable) == 0x00U))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Build the raw DIER mask once, then either set or clear the selected enable bits.
	rawMask = Codec_TIM_EncodeIRQMaskToDIERRaw(irqMask);
	rawSet = (irqEnable == TIMx_IRQ_ENABLE) ? rawMask : 0x00000000UL;
	updatedRegImage = RegOps_StageField(updatedRegImage, rawMask, rawSet);

	*pDierRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ---------------------------------- Timer DIER DMA Request Codecs ----------------------------------- //

driver_status_t Codec_TIM_ExtractDMAEnableMask
(
	const reg							dierRegImage,
	tim_dma_t* const					pDmaMask
)
{
	if (pDmaMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Extract only DIER DMA-enable bits represented by the public DMA source mask.
	*pDmaMask = (tim_dma_t) Codec_TIM_DecodeDIERRawToDMAMask(dierRegImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageDMAEnableMask
(
	reg* const							pDierRegImage,
	const tim_dma_t					dmaMask,
	const driver_status_t				dmaState
)
{
	reg updatedRegImage = 0x00000000UL;
	reg rawMask = 0x00000000UL;
	reg rawSet = 0x00000000UL;

	if (pDierRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pDierRegImage;

	if (TIM_DMA_MASK_IS_VALID(dmaMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	ASSERT_DRIVER_STATUS(Codec_TIM_ValidateState(dmaState));

	//! DMA uses driver OFF/ON state while IRQ uses the legacy TIMx_IRQ_DISABLE/ENABLE selector.
	rawMask = Codec_TIM_EncodeDMAMaskToDIERRaw(dmaMask);
	rawSet = (dmaState == DRIVER_STATUS_ON) ? rawMask : 0x00000000UL;
	updatedRegImage = RegOps_StageField(updatedRegImage, rawMask, rawSet);

	*pDierRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer SR Flag Codecs											//
// ==================================================================================================== //

// ------------------------------------- Timer SR IRQ Flag Codecs ------------------------------------- //

driver_status_t Codec_TIM_ExtractIRQFlagMask
(
	const reg							srRegImage,
	tim_irq_t* const					pIrqMask
)
{
	if (pIrqMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Status extraction reports pending event flags using the same public IRQ source mask.
	*pIrqMask = (tim_irq_t) Codec_TIM_DecodeSRRawToIRQMask(srRegImage);
	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageIRQAckMask
(
	reg* const							pSrRegImage,
	const tim_irq_t					irqMask
)
{
	reg rawMask = 0x00000000UL;
	reg updatedRegImage = 0x00000000UL;

	if (pSrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	updatedRegImage = *pSrRegImage;

	if (TIM_IRQ_MASK_IS_VALID(irqMask) == 0x00U)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}
	rawMask = Codec_TIM_EncodeIRQMaskToSRRaw(irqMask);

	//! Timer SR flags are write-0-to-clear; write 1 to unacknowledged supported flags to preserve them.
	if ((updatedRegImage & rawMask) != 0x00000000UL)
	{
		updatedRegImage |= (TIM_CODEC_SR_W0C_FLAG_MASK & ~rawMask);
		updatedRegImage &= ~rawMask;
	}

	*pSrRegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}
