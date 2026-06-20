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

/**
 * @brief Returns the hardware `CCxS` field position for one channel index
 * @param[in] channelIndex Zero-based channel index
 * @returns Register-positioned `CCxS` bit position as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_GetCCMRCcsPos(const tim_channel_index_t channelIndex)
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
__STATIC_FORCEINLINE reg Codec_TIM_GetCCMROcFastPos(const tim_channel_index_t channelIndex)
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
__STATIC_FORCEINLINE reg Codec_TIM_GetCCMROcPreloadPos(const tim_channel_index_t channelIndex)
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
__STATIC_FORCEINLINE reg Codec_TIM_GetCCMROcModePos(const tim_channel_index_t channelIndex)
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
__STATIC_FORCEINLINE reg Codec_TIM_GetCCMROcClearPos(const tim_channel_index_t channelIndex)
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

/**
 * @brief Returns the hardware `CCxE` field position for one channel index inside `CCER`
 * @param[in] channelIndex Zero-based channel index
 * @returns Register-positioned `CCxE` bit position as @ref `reg`
 */
__STATIC_FORCEINLINE reg Codec_TIM_GetCcerEnablePos(const tim_channel_index_t channelIndex)
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
__STATIC_FORCEINLINE reg Codec_TIM_GetCcerPolarityPos(const tim_channel_index_t channelIndex)
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

/**
 * @brief Encodes a Timer IRQ selector mask into raw `DIER` interrupt bits
 * @param[in] irqMask Timer IRQ selector mask
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
//										Timer CR1 Counter Codecs										//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractCounterConfig
(
	const reg							cr1RegImage,
	tim_direction_t* const				pDirection,
	tim_count_mode_t* const				pMode,
	tim_opm_t* const					pOnePulse,
	tim_arpe_t* const					pAutoReloadPreload,
	tim_update_source_t* const			pUpdateSource,
	tim_clock_division_t* const			pClockDivision
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	//! At least one output is required; each non-NULL pointer is decoded independently.
	if
	(
		(pDirection == NULL) &&
		(pMode == NULL) &&
		(pOnePulse == NULL) &&
		(pAutoReloadPreload == NULL) &&
		(pUpdateSource == NULL) &&
		(pClockDivision == NULL)
	)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	if (pDirection != NULL)
	{
		//! `DIR` is the raw direction field and maps directly to the public direction selector.
		rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_DIR, TIM_CR1_DIR_Pos);
		ASSERT_DRIVER_STATUS(Codec_TIM_DecodeSelector(TIM_DIRECTION_IS_VALID(rawField), rawField, pDirection));
	}
	if (pMode != NULL)
	{
		//! `CMS` encodes edge/center-aligned counter mode in CR1.
		rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_CMS, TIM_CR1_CMS_Pos);
		ASSERT_DRIVER_STATUS(Codec_TIM_DecodeSelector(TIM_COUNT_MODE_IS_VALID(rawField), rawField, pMode));
	}
	if (pOnePulse != NULL)
	{
		//! `OPM` is a one-bit selector: continuous counting versus one-pulse mode.
		rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_OPM, TIM_CR1_OPM_Pos);
		ASSERT_DRIVER_STATUS(Codec_TIM_DecodeSelector(TIM_OPM_IS_VALID(rawField), rawField, pOnePulse));
	}
	if (pAutoReloadPreload != NULL)
	{
		//! `ARPE` controls whether ARR updates are buffered until update events.
		rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_ARPE, TIM_CR1_ARPE_Pos);
		ASSERT_DRIVER_STATUS(Codec_TIM_DecodeSelector(TIM_ARPE_IS_VALID(rawField), rawField, pAutoReloadPreload));
	}
	if (pUpdateSource != NULL)
	{
		//! `URS` selects whether any update source or only overflow/DMA sources generate update requests.
		rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_URS, TIM_CR1_URS_Pos);
		ASSERT_DRIVER_STATUS(Codec_TIM_DecodeSelector(TIM_UPDATE_SOURCE_IS_VALID(rawField), rawField, pUpdateSource));
	}
	if (pClockDivision != NULL)
	{
		//! `CKD` divides the digital filter/dead-time sampling clock, not the counter clock.
		rawField = RegOps_ExtractFieldValue(cr1RegImage, TIM_CR1_CKD, TIM_CR1_CKD_Pos);
		ASSERT_DRIVER_STATUS(Codec_TIM_DecodeSelector(TIM_CLOCK_DIVISION_IS_VALID(rawField), rawField, pClockDivision));
	}

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_StageCounterConfig
(
	const reg							cr1RegImage,
	const tim_direction_t				direction,
	const tim_count_mode_t				mode,
	const tim_opm_t						onePulse,
	const tim_arpe_t					autoReloadPreload,
	const tim_update_source_t			updateSource,
	const tim_clock_division_t			clockDivision,
	reg* const							pCr1RegImage
)
{
	reg updatedRegImage = cr1RegImage;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCr1RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	//! Stage into a working image so unrelated CR1 bits such as CEN and UDIS are preserved.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_DIRECTION_IS_VALID(direction), direction, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, TIM_CR1_DIR_Pos, rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_COUNT_MODE_IS_VALID(mode), mode, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, TIM_CR1_CMS_Pos, rawField, TIM_CODEC_FIELD_WIDTH_2BIT);

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_OPM_IS_VALID(onePulse), onePulse, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, TIM_CR1_OPM_Pos, rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_ARPE_IS_VALID(autoReloadPreload), autoReloadPreload, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, TIM_CR1_ARPE_Pos, rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_UPDATE_SOURCE_IS_VALID(updateSource), updateSource, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, TIM_CR1_URS_Pos, rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_CLOCK_DIVISION_IS_VALID(clockDivision), clockDivision, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, TIM_CR1_CKD_Pos, rawField, TIM_CODEC_FIELD_WIDTH_2BIT);

	*pCr1RegImage = updatedRegImage;
	return DRIVER_STATUS_SUCCESS;
}

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

driver_status_t Codec_TIM_ExtractMasterMode
(
	const reg							cr2RegImage,
	tim_master_mode_t* const			pMasterMode
)
{
	//! Master mode is a compact three-bit selector in CR2.MMS.
	const reg_field_t rawField = RegOps_ExtractFieldValue(cr2RegImage, TIM_CR2_MMS, TIM_CR2_MMS_Pos);
	return Codec_TIM_DecodeSelector(TIM_MASTER_MODE_IS_VALID(rawField), rawField, pMasterMode);
}

driver_status_t Codec_TIM_StageMasterMode
(
	const reg							cr2RegImage,
	const tim_master_mode_t				masterMode,
	reg* const							pCr2RegImage
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCr2RegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_MASTER_MODE_IS_VALID(masterMode), masterMode, &rawField));
	*pCr2RegImage = RegOps_StageFieldValue(cr2RegImage, TIM_CR2_MMS_Pos, rawField, TIM_CODEC_FIELD_WIDTH_3BIT);

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t Codec_TIM_ExtractSlaveMode
(
	const reg							smcrRegImage,
	tim_slave_mode_t* const				pSlaveMode
)
{
	//! Slave mode is a compact three-bit selector in SMCR.SMS.
	const reg_field_t rawField = RegOps_ExtractFieldValue(smcrRegImage, TIM_SMCR_SMS, TIM_SMCR_SMS_Pos);
	return Codec_TIM_DecodeSelector(TIM_SLAVE_MODE_IS_VALID(rawField), rawField, pSlaveMode);
}

driver_status_t Codec_TIM_StageSlaveMode
(
	const reg							smcrRegImage,
	const tim_slave_mode_t				slaveMode,
	reg* const							pSmcrRegImage
)
{
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pSmcrRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_SLAVE_MODE_IS_VALID(slaveMode), slaveMode, &rawField));
	*pSmcrRegImage = RegOps_StageFieldValue(smcrRegImage, TIM_SMCR_SMS_Pos, rawField, TIM_CODEC_FIELD_WIDTH_3BIT);

	return DRIVER_STATUS_SUCCESS;
}

// ==================================================================================================== //
//										Timer CCMR Channel Codecs										//
// ==================================================================================================== //

driver_status_t Codec_TIM_ExtractChannelSelection
(
	const reg							ccmrRegImage,
	const tim_channel_t					channel,
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

	return Codec_TIM_DecodeSelector(TIM_CHANNEL_CCS_IS_VALID(rawField), rawField, pCaptureCompareSelection);
}

driver_status_t Codec_TIM_StageChannelSelection
(
	const reg							ccmrRegImage,
	const tim_channel_t					channel,
	const tim_channel_ccs_t				captureCompareSelection,
	reg* const							pCCMRRegImage
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCCMRRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_CHANNEL_CCS_IS_VALID(captureCompareSelection), captureCompareSelection, &rawField));

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

driver_status_t Codec_TIM_ExtractOutputCompareConfig
(
	const reg							ccmrRegImage,
	const tim_channel_t					channel,
	tim_channel_oc_clear_t* const		pOutputCompareClear,
	tim_channel_mode_t* const			pOutputCompareMode,
	tim_channel_oc_preload_t* const		pOutputComparePreload,
	tim_channel_oc_fast_t* const			pOutputCompareFast
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
		ASSERT_DRIVER_STATUS(Codec_TIM_DecodeSelector(TIM_CHANNEL_MODE_IS_VALID(rawField), rawField, pOutputCompareMode));
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
	const tim_channel_t					channel,
	const tim_channel_oc_clear_t		outputCompareClear,
	const tim_channel_mode_t			outputCompareMode,
	const tim_channel_oc_preload_t		outputComparePreload,
	const tim_channel_oc_fast_t			outputCompareFast,
	reg* const							pCCMRRegImage
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
	reg updatedRegImage = ccmrRegImage;
	reg_field_t rawField = (reg_field_t) 0x00U;

	if (pCCMRRegImage == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	ASSERT_DRIVER_STATUS(Codec_TIM_GetChannelIndexFromMask(channel, &channelIndex));

	//! Force CCxS to output mode before staging OCx fields so the image has a coherent interpretation.
	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_CHANNEL_CCS_IS_VALID(TIMx_CHANNEL_CCS_OUTPUT), TIMx_CHANNEL_CCS_OUTPUT, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, Codec_TIM_GetCCMRCcsPos(channelIndex), rawField, TIM_CODEC_FIELD_WIDTH_2BIT);

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_CHANNEL_OC_CLEAR_IS_VALID(outputCompareClear), outputCompareClear, &rawField));
	updatedRegImage = RegOps_StageFieldValue(updatedRegImage, Codec_TIM_GetCCMROcClearPos(channelIndex), rawField, TIM_CODEC_FIELD_WIDTH_1BIT);

	ASSERT_DRIVER_STATUS(Codec_TIM_EncodeSelector(TIM_CHANNEL_MODE_IS_VALID(outputCompareMode), outputCompareMode, &rawField));
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

driver_status_t Codec_TIM_ExtractChannelEnableState
(
	const reg							ccerRegImage,
	const tim_channel_t					channel,
	driver_status_t* const				pChannelState
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;

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
	const tim_channel_t					channel,
	const driver_status_t				channelState,
	reg* const							pCcerRegImage
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;

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

driver_status_t Codec_TIM_ExtractChannelPolarity
(
	const reg							ccerRegImage,
	const tim_channel_t					channel,
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
		REG_BIT_MASK(Codec_TIM_GetCcerPolarityPos(channelIndex)),
		Codec_TIM_GetCcerPolarityPos(channelIndex)
	);

	return Codec_TIM_DecodeSelector(TIM_CHANNEL_POLARITY_IS_VALID(rawField), rawField, pPolarity);
}

driver_status_t Codec_TIM_StageChannelPolarity
(
	const reg							ccerRegImage,
	const tim_channel_t					channel,
	const tim_channel_polarity_t			polarity,
	reg* const							pCcerRegImage
)
{
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_INVALID;
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
	const reg							dierRegImage,
	const tim_irq_t						irqMask,
	const tim_irq_enable_t				irqEnable,
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
	const reg							dierRegImage,
	const tim_dma_t						dmaMask,
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
	const reg							srRegImage,
	const tim_irq_t						irqMask,
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
