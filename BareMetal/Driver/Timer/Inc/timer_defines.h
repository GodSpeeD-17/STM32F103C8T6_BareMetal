/**
 * @file	timer_defines.h
 * @author	Shrey Shah
 * @brief	Timer Driver Selector and Validation Defines
 * @version	v1.0
 * @date	07-06-2026
 *
 * @details
 * This header owns public Timer selector macros and pure validation helpers.
 * It does not own Timer typedef aliases; those live in `timer_data_types.h`.
 *
 * Keep this file free of direct Timer register reads/writes. STM32F1 register
 * field placement belongs in the Timer codec layer. Register access belongs in
 * the Timer LL layer.
 *
 * @note During the migration step, this header is intentionally not wired into
 * `timer.h` until the legacy Timer selector enums are removed from Core.
 */

#ifndef TIMER_DEFINES_H_
#define TIMER_DEFINES_H_

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "stm32f1xx_base_address.h"
#include "stm32f1xx_timer.h"
#include "stm32f1xx_utils.h"
#include "timer_data_types.h"

// --- C++ Compatibility ---
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup TIM Timer Driver
 * @brief STM32F1 general-purpose Timer driver stack
 */

/**
 * @addtogroup TIM_03_Driver
 * @{
 */

/**
 * @brief Timer public selector and validation macros
 * @defgroup TIM_03_Driver_02_Defines Timer Driver Selector and Validation Defines
 * @ingroup TIM_03_Driver
 * @details
 * This group contains public Timer selector macros and pure validation helpers.
 * It deliberately excludes direct register access helpers and raw register
 * image staging.
 * @{
 */

// ==================================================================================================== //
//										Timer Instance Selectors										//
// ==================================================================================================== //

/**
 * @brief Timer instance validation helpers
 * @defgroup TIM_03_Driver_02_Defines_01_Instance Timer Instance Defines
 * @ingroup TIM_03_Driver_02_Defines
 * @{
 */

/** @brief First supported general-purpose Timer instance index @def TIM_INSTANCE_INDEX_FIRST */
#define TIM_INSTANCE_INDEX_FIRST						((tim_instance_index_t) 0x00U)
/** @brief `TIM2` instance index @def TIM_INSTANCE_INDEX_TIM2 */
#define TIM_INSTANCE_INDEX_TIM2							((tim_instance_index_t) 0x00U)
/** @brief `TIM3` instance index @def TIM_INSTANCE_INDEX_TIM3 */
#define TIM_INSTANCE_INDEX_TIM3							((tim_instance_index_t) 0x01U)
/** @brief `TIM4` instance index @def TIM_INSTANCE_INDEX_TIM4 */
#define TIM_INSTANCE_INDEX_TIM4							((tim_instance_index_t) 0x02U)
/** @brief `TIM5` instance index @def TIM_INSTANCE_INDEX_TIM5 */
#define TIM_INSTANCE_INDEX_TIM5							((tim_instance_index_t) 0x03U)
/** @brief Last supported general-purpose Timer instance index @def TIM_INSTANCE_INDEX_LAST */
#define TIM_INSTANCE_INDEX_LAST							TIM_INSTANCE_INDEX_TIM5
/** @brief Number of supported general-purpose Timer instances @def TIM_INSTANCE_COUNT */
#define TIM_INSTANCE_COUNT								((tim_instance_index_t) (TIM_INSTANCE_INDEX_LAST + 1U))
/** @brief Invalid Timer instance index sentinel @def TIM_INSTANCE_INDEX_INVALID */
#define TIM_INSTANCE_INDEX_INVALID						TIM_INSTANCE_COUNT

/**
 * @brief Checks whether a Timer instance index is supported by this driver
 * @param[in]	instanceIndex	Timer instance index to check
 * @returns Timer instance-index validity status
 * @retval - `0x00U`: @p instanceIndex is outside the supported range
 * @retval - `0x01U`: @p instanceIndex is supported
 * @def TIM_INSTANCE_INDEX_IS_VALID
 */
#define TIM_INSTANCE_INDEX_IS_VALID(instanceIndex)		\
	(((uint32_t) (instanceIndex)) <= ((uint32_t) TIM_INSTANCE_INDEX_LAST))

/**
 * @brief Checks whether a Timer peripheral instance is supported by this driver
 * @param[in]	TIMx	Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @returns Timer instance validity status
 * @retval - `0x00U`: @p TIMx is not supported by this Timer driver pass
 * @retval - `0x01U`: @p TIMx is a supported general-purpose Timer instance
 * @def TIM_INSTANCE_IS_VALID
 */
#define TIM_INSTANCE_IS_VALID(TIMx)								\
(																\
	(((uintptr_t) (TIMx)) == ((uintptr_t) TIM2_BASE_ADDRESS)) ||	\
	(((uintptr_t) (TIMx)) == ((uintptr_t) TIM3_BASE_ADDRESS)) ||	\
	(((uintptr_t) (TIMx)) == ((uintptr_t) TIM4_BASE_ADDRESS)) ||	\
	(((uintptr_t) (TIMx)) == ((uintptr_t) TIM5_BASE_ADDRESS))		\
)

/**
 * @brief Converts a supported Timer instance to a zero-based instance index
 * @param[in] TIMx Timer peripheral instance
 * Accepted values:
 * - @ref `TIM2`
 * - @ref `TIM3`
 * - @ref `TIM4`
 * - @ref `TIM5`
 * @returns Timer instance index
 * @retval - @ref `TIM_INSTANCE_INDEX_TIM2`: @p TIMx is @ref `TIM2`
 * @retval - @ref `TIM_INSTANCE_INDEX_TIM3`: @p TIMx is @ref `TIM3`
 * @retval - @ref `TIM_INSTANCE_INDEX_TIM4`: @p TIMx is @ref `TIM4`
 * @retval - @ref `TIM_INSTANCE_INDEX_TIM5`: @p TIMx is @ref `TIM5`
 * @retval - @ref `TIM_INSTANCE_INDEX_INVALID`: @p TIMx is not supported
 */
__STATIC_FORCEINLINE tim_instance_index_t TIM_InstanceToIndex(const TIM_TypeDef* const TIMx)
{
	// Local Variables
	tim_instance_index_t instanceIndex = TIM_INSTANCE_INDEX_INVALID;
	const uintptr_t timerAddress = (uintptr_t) TIMx;
	//! Determine Timer Base Address and Instance Index
	switch (timerAddress)
	{
		case TIM2_BASE_ADDRESS:
		{
			instanceIndex = TIM_INSTANCE_INDEX_TIM2;
			break;
		}
		case TIM3_BASE_ADDRESS:
		{
			instanceIndex = TIM_INSTANCE_INDEX_TIM3;
			break;
		}
		case TIM4_BASE_ADDRESS:
		{
			instanceIndex = TIM_INSTANCE_INDEX_TIM4;
			break;
		}
		case TIM5_BASE_ADDRESS:
		{
			instanceIndex = TIM_INSTANCE_INDEX_TIM5;
			break;
		}
		default:
		{
			instanceIndex = TIM_INSTANCE_INDEX_INVALID;
			break;
		}
	}

	return instanceIndex;
}

/** @} */ // TIM_03_Driver_02_Defines_01_Instance

// ==================================================================================================== //
//											Timer Default Values											//
// ==================================================================================================== //

/**
 * @brief Timer default preset values
 * @defgroup TIM_03_Driver_02_Defines_02_Defaults Timer Default Defines
 * @ingroup TIM_03_Driver_02_Defines
 * @{
 */

/** @brief Default prescaler for 10 kHz timer tick at 72 MHz timer clock @def TIMx_DEFAULT_10kHz_PSC */
#define TIMx_DEFAULT_10kHz_PSC						((tim_prescaler_t) 7199U)
/** @brief Default auto-reload value for 10 kHz periodic count window @def TIMx_DEFAULT_10kHz_ARR */
#define TIMx_DEFAULT_10kHz_ARR						((tim_auto_reload_t) 9999U)
/** @brief Default prescaler for 1 MHz timer tick at 72 MHz timer clock @def TIMx_DEFAULT_1MHz_PSC */
#define TIMx_DEFAULT_1MHz_PSC						((tim_prescaler_t) 71U)
/** @brief Default auto-reload value for 1 MHz periodic count window @def TIMx_DEFAULT_1MHz_ARR */
#define TIMx_DEFAULT_1MHz_ARR						((tim_auto_reload_t) 999U)
/** @brief Default timer counter start value @def TIMx_DEFAULT_CNT */
#define TIMx_DEFAULT_CNT							((tim_counter_value_t) 0U)

/** @} */ // TIM_03_Driver_02_Defines_02_Defaults

// ==================================================================================================== //
//											Timer Channels												//
// ==================================================================================================== //

/**
 * @brief Timer channel bit-mask selectors and helpers
 * @defgroup TIM_03_Driver_02_Defines_03_Channel Timer Channel Defines
 * @ingroup TIM_03_Driver_02_Defines
 * @{
 */

/** @brief First valid zero-based Timer channel index @def TIM_CHANNEL_INDEX_FIRST */
#define TIM_CHANNEL_INDEX_FIRST						((tim_channel_index_t) 0U)
/** @brief Last valid zero-based Timer channel index @def TIM_CHANNEL_INDEX_LAST */
#define TIM_CHANNEL_INDEX_LAST						((tim_channel_index_t) 3U)
/** @brief Number of Timer channels available on one general-purpose Timer @def TIM_CHANNEL_COUNT */
#define TIM_CHANNEL_COUNT							((tim_channel_index_t) (TIM_CHANNEL_INDEX_LAST + 1U))
/** @brief Invalid Timer channel index sentinel @def TIM_CHANNEL_INDEX_INVALID */
#define TIM_CHANNEL_INDEX_INVALID					TIM_CHANNEL_COUNT

/**
 * @brief Checks if a Timer channel index is inside the supported channel-index range
 * @param[in]	channelIndex	Zero-based Timer channel index to check
 * @returns Channel-index validity status
 * @retval - `0x00U`: @p channelIndex is outside `0..3`
 * @retval - `0x01U`: @p channelIndex is inside `0..3`
 * @def TIM_CHANNEL_INDEX_IS_VALID
 */
#define TIM_CHANNEL_INDEX_IS_VALID(channelIndex)	\
	(((uint32_t) (channelIndex)) <= ((uint32_t) TIM_CHANNEL_INDEX_LAST))

/**
 * @brief Converts a zero-based Timer channel index to a single-channel mask
 * @param[in]	channelIndex	Zero-based Timer channel index
 * @returns Timer channel mask generated from @p channelIndex
 * @retval - @ref `TIMx_CHANNEL_1` through @ref `TIMx_CHANNEL_4`: @p channelIndex is valid
 * @def TIM_CHANNEL_INDEX_TO_MASK
 */
#define TIM_CHANNEL_INDEX_TO_MASK(channelIndex)		((tim_channel_t) REG_BIT_MASK(channelIndex))

/** @brief No timer channel selected @def TIMx_CHANNEL_NONE */
#define TIMx_CHANNEL_NONE							((tim_channel_t) 0x00U)
/** @brief Timer channel 1 selector @def TIMx_CHANNEL_1 */
#define TIMx_CHANNEL_1								TIM_CHANNEL_INDEX_TO_MASK(0U)
/** @brief Timer channel 2 selector @def TIMx_CHANNEL_2 */
#define TIMx_CHANNEL_2								TIM_CHANNEL_INDEX_TO_MASK(1U)
/** @brief Timer channel 3 selector @def TIMx_CHANNEL_3 */
#define TIMx_CHANNEL_3								TIM_CHANNEL_INDEX_TO_MASK(2U)
/** @brief Timer channel 4 selector @def TIMx_CHANNEL_4 */
#define TIMx_CHANNEL_4								TIM_CHANNEL_INDEX_TO_MASK(3U)
/** @brief All timer channels selected @def TIMx_CHANNEL_ALL */
#define TIMx_CHANNEL_ALL							((tim_channel_t) 0x0FU)

/**
 * @brief Checks if a Timer channel mask selects at least one channel
 * @param[in]	channelMask	Timer channel mask to check
 * @returns Channel-selection presence status
 * @retval - `0x00U`: @p channelMask selects no channel
 * @retval - `0x01U`: @p channelMask selects at least one channel
 * @def TIM_CHANNEL_MASK_HAS_ANY_CHANNEL
 */
#define TIM_CHANNEL_MASK_HAS_ANY_CHANNEL(channelMask)	\
	(((tim_channel_t) (channelMask)) != TIMx_CHANNEL_NONE)

/**
 * @brief Checks if a Timer channel mask contains only supported channel bits
 * @param[in]	channelMask	Timer channel mask to check
 * @returns Supported-range status
 * @retval - `0x00U`: @p channelMask contains bits outside @ref `TIMx_CHANNEL_ALL`
 * @retval - `0x01U`: @p channelMask contains only supported channel bits
 * @def TIM_CHANNEL_MASK_HAS_ONLY_VALID_CHANNELS
 */
#define TIM_CHANNEL_MASK_HAS_ONLY_VALID_CHANNELS(channelMask)	\
	((((uint32_t) (channelMask)) & (~((uint32_t) TIMx_CHANNEL_ALL))) == 0x00000000UL)

/**
 * @brief Checks if a Timer channel mask is valid and non-empty
 * @param[in]	channelMask	Timer channel mask to check
 * @returns Channel-mask validity status
 * @retval - `0x00U`: @p channelMask is empty or contains unsupported bits
 * @retval - `0x01U`: @p channelMask selects one or more supported channels
 * @def TIM_CHANNEL_MASK_IS_VALID
 */
#define TIM_CHANNEL_MASK_IS_VALID(channelMask)		\
	(TIM_CHANNEL_MASK_HAS_ANY_CHANNEL(channelMask) && TIM_CHANNEL_MASK_HAS_ONLY_VALID_CHANNELS(channelMask))

/**
 * @brief Checks if a Timer channel mask has zero or one bit set
 * @param[in]	channelMask	Timer channel mask to check
 * @returns At-most-one-bit status
 * @retval - `0x00U`: @p channelMask contains multiple selected channels
 * @retval - `0x01U`: @p channelMask is zero or contains exactly one channel
 * @def TIM_CHANNEL_MASK_HAS_AT_MOST_ONE_CHANNEL
 */
#define TIM_CHANNEL_MASK_HAS_AT_MOST_ONE_CHANNEL(channelMask)	\
	((((uint32_t) (channelMask)) & (((uint32_t) (channelMask)) - 1UL)) == 0x00000000UL)

/**
 * @brief Checks if a Timer channel mask contains exactly one selected channel
 * @param[in]	channelMask	Timer channel mask to check
 * @returns Single-channel selection status
 * @retval - `0x00U`: @p channelMask is empty or selects multiple channels
 * @retval - `0x01U`: @p channelMask selects exactly one supported channel
 * @def TIM_CHANNEL_MASK_HAS_ONLY_ONE_VALID_CHANNEL
 */
#define TIM_CHANNEL_MASK_HAS_ONLY_ONE_VALID_CHANNEL(channelMask)	\
	(TIM_CHANNEL_MASK_IS_VALID(channelMask) && TIM_CHANNEL_MASK_HAS_AT_MOST_ONE_CHANNEL(channelMask))

/**
 * @brief Returns the channel index for a single-channel mask
 * @param[in]	channelMask	Timer single-channel mask
 * @returns Timer channel index decoded from @p channelMask
 * @retval - `0U..3U`: Valid Timer channel index
 * @retval - @ref `TIM_CHANNEL_INDEX_INVALID`: Invalid, empty, or multi-channel mask
 */
__STATIC_FORCEINLINE tim_channel_index_t TIM_ChannelMaskToIndex(const tim_channel_t channelMask)
{
	// Local Variables
	tim_channel_t channelMaskImage = channelMask;
	tim_channel_index_t channelIndex = TIM_CHANNEL_INDEX_FIRST;

	// Validate Input
	if (TIM_CHANNEL_MASK_HAS_ONLY_ONE_VALID_CHANNEL(channelMask) == 0x00U)
	{
		return TIM_CHANNEL_INDEX_INVALID;
	}

	//! Right-shift the single-channel mask until it matches the first channel mask
	//! Count the shifts as the channel index
	while (channelMaskImage != TIMx_CHANNEL_1)
	{
		channelMaskImage = (tim_channel_t) (((uint32_t) channelMaskImage) >> 1U);
		++channelIndex;
	}

	return channelIndex;
}

/**
 * @brief Extracts the lowest selected channel from a Timer channel mask
 * @param[in]	channelMask	Timer channel mask image
 * @returns Single-channel mask for the lowest selected channel
 * @retval - @ref `TIMx_CHANNEL_NONE`: @p channelMask has no selected channel
 * @retval - @ref `TIMx_CHANNEL_1` through @ref `TIMx_CHANNEL_4`: Lowest selected channel mask
 */
__STATIC_FORCEINLINE tim_channel_t TIM_ChannelMaskExtractLowestChannel(const tim_channel_t channelMask)
{
	return (tim_channel_t) (((uint32_t) channelMask) & (0UL - ((uint32_t) channelMask)));
}

/**
 * @brief Removes one selected channel from a Timer channel mask image
 * @param[in,out]	pChannelMask	Timer channel mask image to update
 * @param[in]		channel			Timer single-channel mask to remove
 * @returns Remove status
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: @p channel was removed from @p pChannelMask
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p pChannelMask is `NULL`
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p channel is not a single valid channel selected in @p pChannelMask
 */
__STATIC_FORCEINLINE driver_status_t TIM_ChannelMaskRemoveChannel
(
	tim_channel_t* const	pChannelMask,
	const tim_channel_t		channel
)
{
	// Validate Input
	if (pChannelMask == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}
	if
	(
		(TIM_CHANNEL_MASK_IS_VALID(*pChannelMask) == 0x00U) ||
		(TIM_CHANNEL_MASK_HAS_ONLY_ONE_VALID_CHANNEL(channel) == 0x00U) ||
		((((uint32_t) (*pChannelMask)) & ((uint32_t) channel)) == 0x00000000UL)
	)
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Clear the specified channel bit from the channel mask image
	*pChannelMask = (tim_channel_t) (((uint32_t) (*pChannelMask)) & ~((uint32_t) channel));
	return DRIVER_STATUS_SUCCESS;
}

/** @} */ // TIM_03_Driver_02_Defines_03_Channel

// ==================================================================================================== //
//										Timer Counter Selectors										//
// ==================================================================================================== //

/**
 * @brief Timer counter mode, direction, and update selectors
 * @defgroup TIM_03_Driver_02_Defines_04_Counter Timer Counter Defines
 * @ingroup TIM_03_Driver_02_Defines
 * @{
 */

/** @brief Edge-aligned mode @def TIMx_MODE_NORMAL */
#define TIMx_MODE_NORMAL									((tim_count_mode_t) 0x00U)
/** @brief Center-aligned mode 1, interrupt flag set while down-counting @def TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING */
#define TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING			((tim_count_mode_t) 0x01U)
/** @brief Center-aligned mode 2, interrupt flag set while up-counting @def TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING */
#define TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING			((tim_count_mode_t) 0x02U)
/** @brief Center-aligned mode 3, interrupt flag set while up-counting and down-counting @def TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING */
#define TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING			((tim_count_mode_t) 0x03U)

/**
 * @brief Checks whether a Timer count mode selector is valid
 * @param[in]	mode	Timer count mode selector
 * @returns Count mode validity status
 * @retval - `0x00U`: @p mode is not supported
 * @retval - `0x01U`: @p mode is supported
 * @def TIM_COUNT_MODE_IS_VALID
 */
#define TIM_COUNT_MODE_IS_VALID(mode)												\
(																					\
	(((tim_count_mode_t) (mode)) == TIMx_MODE_NORMAL) ||							\
	(((tim_count_mode_t) (mode)) == TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING) ||	\
	(((tim_count_mode_t) (mode)) == TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING) ||	\
	(((tim_count_mode_t) (mode)) == TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING)	\
)

/** @brief Timer counts up @def TIMx_DIR_COUNT_UP */
#define TIMx_DIR_COUNT_UP								((tim_direction_t) 0x00U)
/** @brief Timer counts down @def TIMx_DIR_COUNT_DOWN */
#define TIMx_DIR_COUNT_DOWN								((tim_direction_t) 0x01U)

/**
 * @brief Checks whether a Timer direction selector is valid
 * @param[in]	direction	Timer direction selector
 * @returns Direction validity status
 * @retval - `0x00U`: @p direction is not supported
 * @retval - `0x01U`: @p direction is supported
 * @def TIM_DIRECTION_IS_VALID
 */
#define TIM_DIRECTION_IS_VALID(direction)						\
(																\
	(((tim_direction_t) (direction)) == TIMx_DIR_COUNT_UP) ||	\
	(((tim_direction_t) (direction)) == TIMx_DIR_COUNT_DOWN)	\
)

/** @brief Disable auto-reload preload @def TIMx_ARPE_DISABLE */
#define TIMx_ARPE_DISABLE								((tim_arpe_t) 0x00U)
/** @brief Enable auto-reload preload @def TIMx_ARPE_ENABLE */
#define TIMx_ARPE_ENABLE								((tim_arpe_t) 0x01U)

/**
 * @brief Checks whether a Timer auto-reload preload selector is valid
 * @param[in]	arpe	Timer auto-reload preload selector
 * @returns Auto-reload preload validity status
 * @retval - `0x00U`: @p arpe is not supported
 * @retval - `0x01U`: @p arpe is supported
 * @def TIM_ARPE_IS_VALID
 */
#define TIM_ARPE_IS_VALID(arpe)							\
(														\
	(((tim_arpe_t) (arpe)) == TIMx_ARPE_DISABLE) ||		\
	(((tim_arpe_t) (arpe)) == TIMx_ARPE_ENABLE)			\
)

/** @brief Disable one-pulse mode @def TIMx_OPM_DISABLE */
#define TIMx_OPM_DISABLE								((tim_opm_t) 0x00U)
/** @brief Enable one-pulse mode @def TIMx_OPM_ENABLE */
#define TIMx_OPM_ENABLE									((tim_opm_t) 0x01U)

/**
 * @brief Checks whether a Timer one-pulse selector is valid
 * @param[in]	onePulse	Timer one-pulse selector
 * @returns One-pulse selector validity status
 * @retval - `0x00U`: @p onePulse is not supported
 * @retval - `0x01U`: @p onePulse is supported
 * @def TIM_OPM_IS_VALID
 */
#define TIM_OPM_IS_VALID(onePulse)						\
(														\
	(((tim_opm_t) (onePulse)) == TIMx_OPM_DISABLE) ||	\
	(((tim_opm_t) (onePulse)) == TIMx_OPM_ENABLE)		\
)

/** @brief Update event may be generated by any update source @def TIMx_UPDATE_SOURCE_ANY */
#define TIMx_UPDATE_SOURCE_ANY							((tim_update_source_t) 0x00U)
/** @brief Update request source limited to overflow/underflow or DMA request @def TIMx_UPDATE_SOURCE_OVF_DMA */
#define TIMx_UPDATE_SOURCE_OVF_DMA						((tim_update_source_t) 0x01U)

/**
 * @brief Checks whether a Timer update-source selector is valid
 * @param[in]	updateSource	Timer update-source selector
 * @returns Update-source validity status
 * @retval - `0x00U`: @p updateSource is not supported
 * @retval - `0x01U`: @p updateSource is supported
 * @def TIM_UPDATE_SOURCE_IS_VALID
 */
#define TIM_UPDATE_SOURCE_IS_VALID(updateSource)							\
(																			\
	(((tim_update_source_t) (updateSource)) == TIMx_UPDATE_SOURCE_ANY) ||	\
	(((tim_update_source_t) (updateSource)) == TIMx_UPDATE_SOURCE_OVF_DMA)	\
)

/** @brief Timer clock division is `t_DTS = t_CK_INT` @def TIMx_CKD_CLK_FREQ */
#define TIMx_CKD_CLK_FREQ								((tim_clock_division_t) 0x00U)
/** @brief Timer clock division is `t_DTS = 2 * t_CK_INT` @def TIMx_CKD_CLK_2_FREQ */
#define TIMx_CKD_CLK_2_FREQ							((tim_clock_division_t) 0x01U)
/** @brief Timer clock division is `t_DTS = 4 * t_CK_INT` @def TIMx_CKD_CLK_4_FREQ */
#define TIMx_CKD_CLK_4_FREQ							((tim_clock_division_t) 0x02U)

/**
 * @brief Checks whether a Timer clock-division selector is valid
 * @param[in]	clockDivision	Timer clock-division selector
 * @returns Clock-division validity status
 * @retval - `0x00U`: @p clockDivision is not supported
 * @retval - `0x01U`: @p clockDivision is supported
 * @def TIM_CLOCK_DIVISION_IS_VALID
 */
#define TIM_CLOCK_DIVISION_IS_VALID(clockDivision)							\
(																			\
	(((tim_clock_division_t) (clockDivision)) == TIMx_CKD_CLK_FREQ) ||		\
	(((tim_clock_division_t) (clockDivision)) == TIMx_CKD_CLK_2_FREQ) ||	\
	(((tim_clock_division_t) (clockDivision)) == TIMx_CKD_CLK_4_FREQ)		\
)

/** @} */ // TIM_03_Driver_02_Defines_04_Counter

// ==================================================================================================== //
//										Timer Channel Mode Selectors									//
// ==================================================================================================== //

/**
 * @brief Timer capture/compare channel selectors
 * @defgroup TIM_03_Driver_02_Defines_05_ChannelConfig Timer Channel Config Defines
 * @ingroup TIM_03_Driver_02_Defines
 * @{
 */

/** @brief Freeze output compare output @def TIMx_CHANNEL_MODE_FREEZE */
#define TIMx_CHANNEL_MODE_FREEZE						((tim_channel_mode_t) 0x00U)
/** @brief Set output compare output active on match @def TIMx_CHANNEL_MODE_SET_CH */
#define TIMx_CHANNEL_MODE_SET_CH						((tim_channel_mode_t) 0x01U)
/** @brief Reset output compare output inactive on match @def TIMx_CHANNEL_MODE_RESET_CH */
#define TIMx_CHANNEL_MODE_RESET_CH						((tim_channel_mode_t) 0x02U)
/** @brief Toggle output compare output on match @def TIMx_CHANNEL_MODE_TOGGLE */
#define TIMx_CHANNEL_MODE_TOGGLE						((tim_channel_mode_t) 0x03U)
/** @brief Force output compare output inactive @def TIMx_CHANNEL_MODE_FORCE_RESET */
#define TIMx_CHANNEL_MODE_FORCE_RESET					((tim_channel_mode_t) 0x04U)
/** @brief Force output compare output active @def TIMx_CHANNEL_MODE_FORCE_SET */
#define TIMx_CHANNEL_MODE_FORCE_SET						((tim_channel_mode_t) 0x05U)
/** @brief PWM mode 1 @def TIMx_CHANNEL_MODE_PWM1 */
#define TIMx_CHANNEL_MODE_PWM1							((tim_channel_mode_t) 0x06U)
/** @brief PWM mode 2 @def TIMx_CHANNEL_MODE_PWM2 */
#define TIMx_CHANNEL_MODE_PWM2							((tim_channel_mode_t) 0x07U)

/**
 * @brief Checks whether a Timer channel mode selector is valid
 * @param[in]	channelMode	Timer channel mode selector
 * @returns Channel mode validity status
 * @retval - `0x00U`: @p channelMode is not supported
 * @retval - `0x01U`: @p channelMode is supported
 * @def TIM_CHANNEL_MODE_IS_VALID
 */
#define TIM_CHANNEL_MODE_IS_VALID(channelMode)								\
	(((uint32_t) ((tim_channel_mode_t) (channelMode))) <= ((uint32_t) TIMx_CHANNEL_MODE_PWM2))

/** @brief Channel configured as output compare @def TIMx_CHANNEL_CCS_OUTPUT */
#define TIMx_CHANNEL_CCS_OUTPUT						((tim_channel_ccs_t) 0x00U)
/** @brief Input capture maps ICx to TIx @def TIMx_CHANNEL_CCS_INPUT_TIx */
#define TIMx_CHANNEL_CCS_INPUT_TIx					((tim_channel_ccs_t) 0x01U)
/** @brief Input capture maps ICx to adjacent TI input @def TIMx_CHANNEL_CCS_INPUT_TIx_1 */
#define TIMx_CHANNEL_CCS_INPUT_TIx_1				((tim_channel_ccs_t) 0x02U)
/** @brief Input capture maps ICx to TRC @def TIMx_CHANNEL_CCS_INPUT_TRC */
#define TIMx_CHANNEL_CCS_INPUT_TRC					((tim_channel_ccs_t) 0x03U)

/**
 * @brief Checks whether a Timer capture/compare selection selector is valid
 * @param[in]	ccs	Timer capture/compare selection selector
 * @returns Capture/compare selection validity status
 * @retval - `0x00U`: @p ccs is not supported
 * @retval - `0x01U`: @p ccs is supported
 * @def TIM_CHANNEL_CCS_IS_VALID
 */
#define TIM_CHANNEL_CCS_IS_VALID(ccs)										\
	(((uint32_t) ((tim_channel_ccs_t) (ccs))) <= ((uint32_t) TIMx_CHANNEL_CCS_INPUT_TRC))

/** @brief Disable output compare preload @def TIMx_CHANNEL_OC_PRELOAD_DISABLE */
#define TIMx_CHANNEL_OC_PRELOAD_DISABLE				((tim_channel_oc_preload_t) 0x00U)
/** @brief Enable output compare preload @def TIMx_CHANNEL_OC_PRELOAD_ENABLE */
#define TIMx_CHANNEL_OC_PRELOAD_ENABLE				((tim_channel_oc_preload_t) 0x01U)

/**
 * @brief Checks whether a Timer output-compare preload selector is valid
 * @param[in]	ocPreload	Timer output-compare preload selector
 * @returns Output-compare preload validity status
 * @retval - `0x00U`: @p ocPreload is not supported
 * @retval - `0x01U`: @p ocPreload is supported
 * @def TIM_CHANNEL_OC_PRELOAD_IS_VALID
 */
#define TIM_CHANNEL_OC_PRELOAD_IS_VALID(ocPreload)										\
(																						\
	(((tim_channel_oc_preload_t) (ocPreload)) == TIMx_CHANNEL_OC_PRELOAD_DISABLE) ||	\
	(((tim_channel_oc_preload_t) (ocPreload)) == TIMx_CHANNEL_OC_PRELOAD_ENABLE)		\
)

/** @brief Disable output compare fast mode @def TIMx_CHANNEL_OC_FAST_DISABLE */
#define TIMx_CHANNEL_OC_FAST_DISABLE					((tim_channel_oc_fast_t) 0x00U)
/** @brief Enable output compare fast mode @def TIMx_CHANNEL_OC_FAST_ENABLE */
#define TIMx_CHANNEL_OC_FAST_ENABLE					((tim_channel_oc_fast_t) 0x01U)

/**
 * @brief Checks whether a Timer output-compare fast selector is valid
 * @param[in]	ocFast	Timer output-compare fast selector
 * @returns Output-compare fast validity status
 * @retval - `0x00U`: @p ocFast is not supported
 * @retval - `0x01U`: @p ocFast is supported
 * @def TIM_CHANNEL_OC_FAST_IS_VALID
 */
#define TIM_CHANNEL_OC_FAST_IS_VALID(ocFast)								\
(																			\
	(((tim_channel_oc_fast_t) (ocFast)) == TIMx_CHANNEL_OC_FAST_DISABLE) ||	\
	(((tim_channel_oc_fast_t) (ocFast)) == TIMx_CHANNEL_OC_FAST_ENABLE)		\
)

/** @brief Disable output compare clear mode @def TIMx_CHANNEL_OC_CLEAR_DISABLE */
#define TIMx_CHANNEL_OC_CLEAR_DISABLE				((tim_channel_oc_clear_t) 0x00U)
/** @brief Enable output compare clear mode @def TIMx_CHANNEL_OC_CLEAR_ENABLE */
#define TIMx_CHANNEL_OC_CLEAR_ENABLE					((tim_channel_oc_clear_t) 0x01U)

/**
 * @brief Checks whether a Timer output-compare clear selector is valid
 * @param[in]	ocClear	Timer output-compare clear selector
 * @returns Output-compare clear validity status
 * @retval - `0x00U`: @p ocClear is not supported
 * @retval - `0x01U`: @p ocClear is supported
 * @def TIM_CHANNEL_OC_CLEAR_IS_VALID
 */
#define TIM_CHANNEL_OC_CLEAR_IS_VALID(ocClear)									\
(																				\
	(((tim_channel_oc_clear_t) (ocClear)) == TIMx_CHANNEL_OC_CLEAR_DISABLE) ||	\
	(((tim_channel_oc_clear_t) (ocClear)) == TIMx_CHANNEL_OC_CLEAR_ENABLE)		\
)

/** @brief Channel active-high polarity @def TIMx_CHANNEL_POLARITY_HIGH */
#define TIMx_CHANNEL_POLARITY_HIGH					((tim_channel_polarity_t) 0x00U)
/** @brief Channel active-low polarity @def TIMx_CHANNEL_POLARITY_LOW */
#define TIMx_CHANNEL_POLARITY_LOW					((tim_channel_polarity_t) 0x01U)

/**
 * @brief Checks whether a Timer channel polarity selector is valid
 * @param[in]	polarity	Timer channel polarity selector
 * @returns Channel polarity validity status
 * @retval - `0x00U`: @p polarity is not supported
 * @retval - `0x01U`: @p polarity is supported
 * @def TIM_CHANNEL_POLARITY_IS_VALID
 */
#define TIM_CHANNEL_POLARITY_IS_VALID(polarity)									\
(																				\
	(((tim_channel_polarity_t) (polarity)) == TIMx_CHANNEL_POLARITY_HIGH) ||	\
	(((tim_channel_polarity_t) (polarity)) == TIMx_CHANNEL_POLARITY_LOW)		\
)

/** @} */ // TIM_03_Driver_02_Defines_05_ChannelConfig

// ==================================================================================================== //
//												Timer IRQ												//
// ==================================================================================================== //

/**
 * @brief Timer IRQ selectors and validation helpers
 * @defgroup TIM_03_Driver_02_Defines_06_IRQ Timer IRQ Defines
 * @ingroup TIM_03_Driver_02_Defines
 * @{
 */

/** @brief Timer IRQ disabled selector @def TIMx_IRQ_DISABLE */
#define TIMx_IRQ_DISABLE							((tim_irq_enable_t) 0x00U)
/** @brief Timer IRQ enabled selector @def TIMx_IRQ_ENABLE */
#define TIMx_IRQ_ENABLE								((tim_irq_enable_t) 0x01U)

/**
 * @brief Checks whether a Timer IRQ enable selector is valid
 * @param[in]	irqEnable	Timer IRQ enable selector
 * @returns IRQ enable selector validity status
 * @retval - `0x00U`: @p irqEnable is not supported
 * @retval - `0x01U`: @p irqEnable is supported
 * @def TIM_IRQ_ENABLE_IS_VALID
 */
#define TIM_IRQ_ENABLE_IS_VALID(irqEnable)						\
(																\
	(((tim_irq_enable_t) (irqEnable)) == TIMx_IRQ_DISABLE) ||	\
	(((tim_irq_enable_t) (irqEnable)) == TIMx_IRQ_ENABLE)		\
)

/** @brief Timer update overflow/underflow IRQ selector @def TIMx_IRQ_OVF_UVF */
#define TIMx_IRQ_OVF_UVF							((tim_irq_t) 0x01U)
/** @brief Timer output compare channel 1 IRQ selector @def TIMx_IRQ_OUT_CMP_CH1 */
#define TIMx_IRQ_OUT_CMP_CH1						((tim_irq_t) 0x02U)
/** @brief Timer output compare channel 2 IRQ selector @def TIMx_IRQ_OUT_CMP_CH2 */
#define TIMx_IRQ_OUT_CMP_CH2						((tim_irq_t) 0x04U)
/** @brief Timer output compare channel 3 IRQ selector @def TIMx_IRQ_OUT_CMP_CH3 */
#define TIMx_IRQ_OUT_CMP_CH3						((tim_irq_t) 0x08U)
/** @brief Timer output compare channel 4 IRQ selector @def TIMx_IRQ_OUT_CMP_CH4 */
#define TIMx_IRQ_OUT_CMP_CH4						((tim_irq_t) 0x10U)
/** @brief Timer input capture channel 1 IRQ selector @def TIMx_IRQ_IN_CAP_CH1 */
#define TIMx_IRQ_IN_CAP_CH1							TIMx_IRQ_OUT_CMP_CH1
/** @brief Timer input capture channel 2 IRQ selector @def TIMx_IRQ_IN_CAP_CH2 */
#define TIMx_IRQ_IN_CAP_CH2							TIMx_IRQ_OUT_CMP_CH2
/** @brief Timer input capture channel 3 IRQ selector @def TIMx_IRQ_IN_CAP_CH3 */
#define TIMx_IRQ_IN_CAP_CH3							TIMx_IRQ_OUT_CMP_CH3
/** @brief Timer input capture channel 4 IRQ selector @def TIMx_IRQ_IN_CAP_CH4 */
#define TIMx_IRQ_IN_CAP_CH4							TIMx_IRQ_OUT_CMP_CH4
/** @brief All supported Timer IRQ selectors @def TIMx_IRQ_ALL */
#define TIMx_IRQ_ALL								((tim_irq_t) 0x1FU)

/**
 * @brief Checks if a Timer IRQ mask selects at least one IRQ source
 * @param[in]	irqMask	Timer IRQ mask to check
 * @returns IRQ-selection presence status
 * @retval - `0x00U`: @p irqMask selects no IRQ source
 * @retval - `0x01U`: @p irqMask selects at least one IRQ source
 * @def TIM_IRQ_MASK_HAS_ANY_IRQ
 */
#define TIM_IRQ_MASK_HAS_ANY_IRQ(irqMask)			\
	(((tim_irq_t) (irqMask)) != ((tim_irq_t) 0x00U))

/**
 * @brief Checks if a Timer IRQ mask contains only supported IRQ source bits
 * @param[in]	irqMask	Timer IRQ mask to check
 * @returns Supported-range status
 * @retval - `0x00U`: @p irqMask contains bits outside @ref `TIMx_IRQ_ALL`
 * @retval - `0x01U`: @p irqMask contains only supported IRQ source bits
 * @def TIM_IRQ_MASK_HAS_ONLY_VALID_IRQS
 */
#define TIM_IRQ_MASK_HAS_ONLY_VALID_IRQS(irqMask)	\
	((((uint32_t) (irqMask)) & (~((uint32_t) TIMx_IRQ_ALL))) == 0x00000000UL)

/**
 * @brief Checks if a Timer IRQ mask is valid and non-empty
 * @param[in]	irqMask	Timer IRQ mask to check
 * @returns IRQ-mask validity status
 * @retval - `0x00U`: @p irqMask is empty or contains unsupported bits
 * @retval - `0x01U`: @p irqMask selects one or more supported IRQ sources
 * @def TIM_IRQ_MASK_IS_VALID
 */
#define TIM_IRQ_MASK_IS_VALID(irqMask)				\
	(TIM_IRQ_MASK_HAS_ANY_IRQ(irqMask) && TIM_IRQ_MASK_HAS_ONLY_VALID_IRQS(irqMask))

/** @} */ // TIM_03_Driver_02_Defines_06_IRQ

// ==================================================================================================== //
//												Timer DMA												//
// ==================================================================================================== //

/**
 * @brief Timer DMA source selectors and validation helpers
 * @defgroup TIM_03_Driver_02_Defines_07_DMA Timer DMA Defines
 * @ingroup TIM_03_Driver_02_Defines
 * @{
 */

/** @brief Timer update DMA selector @def TIMx_DMA_UPDATE */
#define TIMx_DMA_UPDATE							((tim_dma_t) 0x01U)
/** @brief Timer capture/compare channel 1 DMA selector @def TIMx_DMA_CC1DE */
#define TIMx_DMA_CC1DE							((tim_dma_t) 0x02U)
/** @brief Timer capture/compare channel 2 DMA selector @def TIMx_DMA_CC2DE */
#define TIMx_DMA_CC2DE							((tim_dma_t) 0x04U)
/** @brief Timer capture/compare channel 3 DMA selector @def TIMx_DMA_CC3DE */
#define TIMx_DMA_CC3DE							((tim_dma_t) 0x08U)
/** @brief Timer capture/compare channel 4 DMA selector @def TIMx_DMA_CC4DE */
#define TIMx_DMA_CC4DE							((tim_dma_t) 0x10U)
/** @brief All supported Timer DMA selectors @def TIMx_DMA_ALL */
#define TIMx_DMA_ALL							((tim_dma_t) 0x1FU)

/**
 * @brief Checks whether a Timer DMA mask is valid and non-empty
 * @param[in]	dmaMask	Timer DMA mask to check
 * @returns DMA-mask validity status
 * @retval - `0x00U`: @p dmaMask is empty or contains unsupported bits
 * @retval - `0x01U`: @p dmaMask selects one or more supported DMA sources
 * @def TIM_DMA_MASK_IS_VALID
 */
#define TIM_DMA_MASK_IS_VALID(dmaMask)			\
	((((tim_dma_t) (dmaMask)) != ((tim_dma_t) 0x00U)) && ((((uint32_t) (dmaMask)) & (~((uint32_t) TIMx_DMA_ALL))) == 0x00000000UL))

/** @} */ // TIM_03_Driver_02_Defines_07_DMA

// ==================================================================================================== //
//											Timer Trigger Modes											//
// ==================================================================================================== //

/**
 * @brief Timer master/slave mode selectors
 * @defgroup TIM_03_Driver_02_Defines_08_Trigger Timer Trigger Defines
 * @ingroup TIM_03_Driver_02_Defines
 * @{
 */

/** @brief Master mode reset trigger output @def TIMx_MMS_RESET */
#define TIMx_MMS_RESET								((tim_master_mode_t) 0x00U)
/** @brief Master mode counter enable trigger output @def TIMx_MMS_ENABLE */
#define TIMx_MMS_ENABLE								((tim_master_mode_t) 0x01U)
/** @brief Master mode update trigger output @def TIMx_MMS_UPDATE */
#define TIMx_MMS_UPDATE								((tim_master_mode_t) 0x02U)
/** @brief Master mode compare pulse trigger output @def TIMx_MMS_CMP_PULSE */
#define TIMx_MMS_CMP_PULSE							((tim_master_mode_t) 0x03U)
/** @brief Master mode output compare 1 reference trigger output @def TIMx_MMS_CMP_OC1REF */
#define TIMx_MMS_CMP_OC1REF							((tim_master_mode_t) 0x04U)
/** @brief Master mode output compare 2 reference trigger output @def TIMx_MMS_CMP_OC2REF */
#define TIMx_MMS_CMP_OC2REF							((tim_master_mode_t) 0x05U)
/** @brief Master mode output compare 3 reference trigger output @def TIMx_MMS_CMP_OC3REF */
#define TIMx_MMS_CMP_OC3REF							((tim_master_mode_t) 0x06U)
/** @brief Master mode output compare 4 reference trigger output @def TIMx_MMS_CMP_OC4REF */
#define TIMx_MMS_CMP_OC4REF							((tim_master_mode_t) 0x07U)

/**
 * @brief Checks whether a Timer master-mode selector is valid
 * @param[in]	masterMode	Timer master-mode selector
 * @returns Master-mode validity status
 * @retval - `0x00U`: @p masterMode is not supported
 * @retval - `0x01U`: @p masterMode is supported
 * @def TIM_MASTER_MODE_IS_VALID
 */
#define TIM_MASTER_MODE_IS_VALID(masterMode)		\
	(((uint32_t) ((tim_master_mode_t) (masterMode))) <= ((uint32_t) TIMx_MMS_CMP_OC4REF))

/** @brief Slave mode disabled @def TIMx_SMS_DISABLE */
#define TIMx_SMS_DISABLE							((tim_slave_mode_t) 0x00U)
/** @brief Encoder mode 1 @def TIMx_SMS_ENC_MODE1 */
#define TIMx_SMS_ENC_MODE1							((tim_slave_mode_t) 0x01U)
/** @brief Encoder mode 2 @def TIMx_SMS_ENC_MODE2 */
#define TIMx_SMS_ENC_MODE2							((tim_slave_mode_t) 0x02U)
/** @brief Encoder mode 3 @def TIMx_SMS_ENC_MODE3 */
#define TIMx_SMS_ENC_MODE3							((tim_slave_mode_t) 0x03U)

/**
 * @brief Checks whether a Timer slave-mode selector is valid for the current public vocabulary
 * @param[in]	slaveMode	Timer slave-mode selector
 * @returns Slave-mode validity status
 * @retval - `0x00U`: @p slaveMode is not supported
 * @retval - `0x01U`: @p slaveMode is supported
 * @def TIM_SLAVE_MODE_IS_VALID
 */
#define TIM_SLAVE_MODE_IS_VALID(slaveMode)			\
	(((uint32_t) ((tim_slave_mode_t) (slaveMode))) <= ((uint32_t) TIMx_SMS_ENC_MODE3))

/** @} */ // TIM_03_Driver_02_Defines_08_Trigger

// ==================================================================================================== //
//											Timer Remap Selectors										//
// ==================================================================================================== //

/**
 * @brief Timer alternate-function remap selectors
 * @defgroup TIM_03_Driver_02_Defines_09_Remap Timer Remap Defines
 * @ingroup TIM_03_Driver_02_Defines
 * @{
 */

/** @brief TIM1 no remap selector @def TIM1_NO_REMAP */
#define TIM1_NO_REMAP								((tim_remap_t) 0x00U)
/** @brief TIM1 partial remap selector @def TIM1_PARTIAL_REMAP */
#define TIM1_PARTIAL_REMAP							((tim_remap_t) 0x01U)
/** @brief TIM1 reserved remap selector @def TIM1_NOT_USED_REMAP */
#define TIM1_NOT_USED_REMAP							((tim_remap_t) 0x02U)
/** @brief TIM1 full remap selector @def TIM1_FULL_REMAP */
#define TIM1_FULL_REMAP								((tim_remap_t) 0x03U)
/** @brief TIM2 no remap selector @def TIM2_NO_REMAP */
#define TIM2_NO_REMAP								((tim_remap_t) 0x00U)
/** @brief TIM2 partial remap 1 selector @def TIM2_PARTIAL1_REMAP */
#define TIM2_PARTIAL1_REMAP							((tim_remap_t) 0x01U)
/** @brief TIM2 partial remap 1 compatibility alias @def TIM2_PARTIAL_REMAP_1 */
#define TIM2_PARTIAL_REMAP_1							TIM2_PARTIAL1_REMAP
/** @brief TIM2 partial remap 2 selector @def TIM2_PARTIAL2_REMAP */
#define TIM2_PARTIAL2_REMAP							((tim_remap_t) 0x02U)
/** @brief TIM2 partial remap 2 compatibility alias @def TIM2_PARTIAL_REMAP_2 */
#define TIM2_PARTIAL_REMAP_2							TIM2_PARTIAL2_REMAP
/** @brief TIM2 full remap selector @def TIM2_FULL_REMAP */
#define TIM2_FULL_REMAP								((tim_remap_t) 0x03U)
/** @brief TIM3 no remap selector @def TIM3_NO_REMAP */
#define TIM3_NO_REMAP								((tim_remap_t) 0x00U)
/** @brief TIM3 reserved remap selector @def TIM3_NOT_USED_REMAP */
#define TIM3_NOT_USED_REMAP							((tim_remap_t) 0x01U)
/** @brief TIM3 partial remap selector @def TIM3_PARTIAL_REMAP */
#define TIM3_PARTIAL_REMAP							((tim_remap_t) 0x02U)
/** @brief TIM3 full remap selector @def TIM3_FULL_REMAP */
#define TIM3_FULL_REMAP								((tim_remap_t) 0x03U)
/** @brief TIM4 no remap selector @def TIM4_NO_REMAP */
#define TIM4_NO_REMAP								((tim_remap_t) 0x00U)
/** @brief TIM4 full remap selector @def TIM4_FULL_REMAP */
#define TIM4_FULL_REMAP								((tim_remap_t) 0x01U)

/** @} */ // TIM_03_Driver_02_Defines_09_Remap

/** @} */ // TIM_03_Driver_02_Defines

/** @} */ // TIM_03_Driver

// --- C++ Compatibility ---
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_DEFINES_H_ */
