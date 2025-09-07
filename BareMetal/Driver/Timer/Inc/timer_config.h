// Header Guards
#ifndef __TIMER_CONFIG_H__
#define __TIMER_CONFIG_H__

// Register Mapping
#include "reg_map.h"
// APB1 Clock Frequency
#include "rcc.h"
// IRQ Enable/Disable
#include "nvic.h"

#ifdef __OLD_TIMER_METHOD__
// Timer Configuration Structure
typedef struct {
	// General Purpose Timer
	// - `TIM2`
	// - `TIM3`
	// - `TIM4`
	TIM_REG_STRUCT* TIM;
	// Timer Channel
	// - `TIMx_CHANNEL_1`
	// - `TIMx_CHANNEL_2`
	// - `TIMx_CHANNEL_3`
	// - `TIMx_CHANNEL_4`
	// - `TIMx_CHANNEL_ALL`
	uint8_t channel;
	// Auto Reload Register Value
	// - Max Value upto which the timer
	uint16_t auto_reload;
	// Prescaler Value
	// - Division from APB1 Clock Frequency
	uint32_t prescaler: 16;
	// Start Count Value
	uint32_t count: 16;
	// Centre-Aligned Mode Selection
	// - `TIMx_CMS_EDGE`
	// - `TIMx_CMS_IF_DOWN`
	// - `TIMx_CMS_IF_UP`
	// - `TIMx_CMS_IF_BOTH`
	uint8_t cms_mode: 2;
	// Count Direction
	// - `TIMx_DIR_COUNT_UP`
	// - `TIMx_DIR_COUNT_DOWN`
	uint8_t direction: 1;
	// Auto-Reload Preload Enable
	// - `TIMx_ARPE_DISABLE`: Buffers the ARR Value permanently
	// - `TIMx_ARPE_ENABLE`: Buffers the ARR Value temporarily
	uint8_t arpe: 1;
	// One-Pulse Mode Enable
	// - `TIMx_OPM_DISABLE`: One Pulse Mode is disabled
	// - `TIMx_OPM_ENABLE`: One Pulse Mode is enabled
	uint8_t one_pulse: 1;
} timer_config_t;

/**
 * @brief Enables the General Purpose TIMx's Channel
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
__STATIC_INLINE__ void TIM_Channel_Enable(TIM_REG_STRUCT* TIMx, uint8_t channel){
	// Local Variable
	uint32_t reg = TIMx->CCER.REG; 
	// Enable the General Purpose Timer Channel
	if(channel & TIMx_CHANNEL_1)
		reg |= TIM_CCER_CC1E;
	else if(channel & TIMx_CHANNEL_2)
		reg |= TIM_CCER_CC2E;
	else if(channel & TIMx_CHANNEL_3)
		reg |= TIM_CCER_CC3E;
	else if(channel & TIMx_CHANNEL_4)
		reg |= TIM_CCER_CC4E;
	// Write to the register
	TIMx->CCER.REG = reg;
}

/**
 * @brief Disables the General Purpose TIMx's Channel
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
__STATIC_INLINE__ void TIM_Channel_Disable(TIM_REG_STRUCT* TIMx, uint8_t channel){
	// Local Variable
	uint32_t reg = TIMx->CCER.REG; 
	// Disable the General Purpose Timer Channel
	if(channel & TIMx_CHANNEL_1)
		reg &= ~TIM_CCER_CC1E;
	else if(channel & TIMx_CHANNEL_2)
		reg &= ~TIM_CCER_CC2E;
	else if(channel & TIMx_CHANNEL_3)
		reg &= ~TIM_CCER_CC3E;
	else if(channel & TIMx_CHANNEL_4)
		reg &= ~TIM_CCER_CC4E;
	// Write to the register
	TIMx->CCER.REG = reg;
}


#else
/**
 * @struct tim_clk_config_t
 * @brief Timer Clock Configuration Structure
 * @note  Configures the timer's clock source and its fundamental period.
 *        This defines the "heartbeat" of the timer.
 */
typedef struct {
	/**
	 * @brief Prescaler value
	 * @details Divides the timer clock.
	 *          Counter clock (`CK_CNT`) = `f_TIMx / (PSC + 1)`.
	 * @range  0x0000 – 0xFFFF
	 */
	uint16_t prescaler;

	/**
	 * @brief Auto-Reload value
	 * @details Loaded into ARR (Auto-Reload Register).
	 *          Timer resets after reaching `(ARR + 1)`.
	 * @range  0x0000 – 0xFFFF
	 */
	uint16_t auto_reload;

	/**
	 * @brief Timer Start Value
	 * @details Loaded into CNT (Counter Register).
	 *          Timer starts counting from this value.
	 * @range  0x0000 – 0xFFFF
	 */
	uint16_t count;
} tim_clk_config_t;

/**
  * @brief  Timer Parameter Configuration Structure
  * @note   Configures the fundamental operating mode of the timer's counter.
  *         This defines the "behavior" of the timer.
  */
typedef struct {
	/**
	 * @brief Timer Counting Direction
	 * @note  Specifies the counter direction
	 * @enum `tim_direction_t`
	 */
	tim_direction_t direction: 1;
	/**
	 * @brief Timer Counting Mode
	 * @note  Specifies the counting mode
	 * @enum `tim_count_mode_t`
	 */
	tim_count_mode_t mode: 2;
	/**
	 * @brief Timer One-Pulse Mode
	 * @note  Specifies the One-Pulse Mode setting (Same as One-Shot Mode)
	 * @enum `tim_opm_t`
	 */
	tim_opm_t one_pulse: 1;
	/**
	 * @brief Timer Auto-Reload Preload Enable
	 * @note  Specifies the Auto-Reload Preload setting
	 * @enum `tim_arpe_t`
	 */
	tim_arpe_t preload_arr: 1;
	/**
	 * @brief Timer Update Source
	 * @note  Specifies the source of the update event
	 * @enum `tim_update_source_t`
	 */
	tim_update_source_t update_source: 1;
} tim_param_t;

/**
 * @brief Timer Channel Configuration Structure
 * @note  Configures the settings for a specific timer channel
 */
typedef struct {
	/**
	 * @brief Channel Polarity Configuration
	 * @param tim_channel_oc_clear_t
	 */
	tim_channel_oc_clear_t oc_clear: 1;
	/**
	 * @brief Channel Mode Configuration
	 * @param tim_channel_mode_t
	 */
	tim_channel_mode_t mode: 3;
	/**
	 * @brief Channel Output Compare Preload Enable
	 * @param tim_channel_oc_preload_t
	 */
	tim_channel_oc_preload_t oc_preload: 1;
	/**
	 * @brief Channel Output Compare Fast Enable
	 * @param tim_channel_oc_fast_t
	 */
	tim_channel_oc_fast_t oc_fast: 1;
	/**
	 * @brief Channel Capture/Compare Selection
	 * @param tim_channel_ccs_t
	 */
	tim_channel_ccs_t ccs: 2;
} tim_channel_config_t;

/**
  * @brief  Timer Preload Configuration Structure
  * @note   Configures the preload (buffering) for the timer's registers.
  *         This is critical for preventing glitches during runtime changes.
  */
typedef struct {
	/**
	 * @brief Specifies the Timer Channel Configuration
	 * @param `tim_channel_config_t`
	 */
	tim_channel_config_t config;
	/**
	 * @brief Instance of Timer Channel
	 * @param `tim_channel_t`
	 */
	tim_channel_t instance;
} tim_channel_instance_t;

/**
 * @brief Timer Configuration Structure
 * @note Configures the settings for a specific timer instance
 */
typedef struct {
	/**
     * @brief Timer hardware instance
     * @param TIMx
	 * @note Typically one of `TIM2`, `TIM3`, `TIM4`.
     */
	TIM_REG_STRUCT* instance;
	/**
     * @brief Timer clock configuration
	 * @param prescaler Timer frequency prescaler from APBx Clock Source
	 * @param auto_reload Timer reachable maximum/minimum value
	 * @param count Timer start/current value
     * @struct tim_clk_config_t
     */
	tim_clk_config_t clk;
	/**
	 * @brief Timer Parameter Configuration
	 * @param preload_arr Timer auto-reload preload enable
	 * @param mode Timer counting mode
	 * @param direction Timer counting direction
	 * @param one_pulse Timer one-pulse mode
	 * @param update_source Timer update source
	 * @struct tim_param_t
	 */
	tim_param_t config;
	/**
	 * @brief Timer Channel Instance
	 * @param instance Timer channel instance
	 * @param config Timer channel configuration
	 *		@param config.mode Timer channel mode
	 *		@param config.polarity Timer channel output polarity
	 *		@param config.oc_preload Timer channel output compare preload enable
	 * @struct tim_channel_instance_t
	 */
	tim_channel_instance_t channel;
} timer_config_t;

#endif /* __OLD_TIMER_METHOD__ */

/**
 * @brief Enables the Clock for General Purpose Timer
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 */
__STATIC_INLINE__ void TIM_Clk_Enable(TIM_REG_STRUCT* TIMx){
	// Enable the clock for the timer
	if(TIMx == TIM2)
		RCC->APB1ENR.REG |= RCC_APB1ENR_TIM2EN;
	else if(TIMx == TIM3)
		RCC->APB1ENR.REG |= RCC_APB1ENR_TIM3EN;
	else if(TIMx == TIM4)
		RCC->APB1ENR.REG |= RCC_APB1ENR_TIM4EN;
}

/**
 * @brief Disables the Clock for General Purpose Timer
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 */
__STATIC_INLINE__ void TIM_Clk_Disable(TIM_REG_STRUCT* TIMx){
	// Disable the clock for the timer
	if(TIMx == TIM2)
		RCC->APB1ENR.REG &= ~RCC_APB1ENR_TIM2EN;
	else if(TIMx == TIM3)
		RCC->APB1ENR.REG &= ~RCC_APB1ENR_TIM3EN;
	else if(TIMx == TIM4)
		RCC->APB1ENR.REG &= ~RCC_APB1ENR_TIM4EN;
}

/**
 * @brief Enables the General Purpose TIMx
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 */
__STATIC_INLINE__ void TIM_Enable(TIM_REG_STRUCT* TIMx){
	// Clear Update Interrupt Flag
	TIMx->SR.REG &= ~TIM_SR_UIF;
	// Enable TIMx
	TIMx->CR1.REG |= TIM_CR1_CEN;
}

/**
 * @brief Disables the General Purpose TIMx
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 */
__STATIC_INLINE__ void TIM_Disable(TIM_REG_STRUCT* TIMx){
	// Disable TIMx
	TIMx->CR1.REG &= ~TIM_CR1_CEN;
	// Clear Update Interrupt Flag
	TIMx->SR.REG &= ~TIM_SR_UIF;
}

/**
 * @brief Retrieves the IRQn based upon TIMx
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @returns IRQn (0 - 59)
 */
__STATIC_INLINE__ uint8_t TIM_Get_IRQn(TIM_REG_STRUCT* TIMx){
	// Return IRQn based upon TIMx
	if(TIMx == TIM2)	
		return TIM2_IRQn;	
	else if(TIMx == TIM3)	
		return TIM3_IRQn;		
	else if(TIMx == TIM4)	
		return TIM4_IRQn;		
}

/**
 * @brief Retrieves the TIMx Interrupt Status
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @returns UIF Flag Status
 */
__STATIC_INLINE__ uint8_t TIM_Get_UIF(TIM_REG_STRUCT* TIMx){
	// Update Interrupt Flag (UIF) Status
	return (uint8_t)(TIMx->SR.REG & TIM_SR_UIF);
}

/**
 * @brief Clears the pending interrupt of TIMx 
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @returns UIF Flag Status
 */
__STATIC_INLINE__ void TIM_Clear_UIF(TIM_REG_STRUCT* TIMx){
	// Clear Update Interrupt Flag (UIF)
	TIMx->SR.REG &= ~TIM_SR_UIF;
}

/**
 * @brief Triggers an update event to apply the settings
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 */
__STATIC_INLINE__ void TIM_Update_Parameters(TIM_REG_STRUCT* TIMx){
	// Send an update event to reset the timer and apply settings
  	TIMx->EGR.REG |= TIM_EGR_UG;
	// Wait until bit reset by Hardware
	while(TIMx->EGR.REG & TIM_EGR_UG);
	// Clear the update flag
	TIMx->SR.REG &= ~TIM_SR_UIF; 
}

/**
 * @brief Enables the Update Event for TIMx
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 */
__STATIC_INLINE__ void TIM_UEV_Enable(TIM_REG_STRUCT* TIMx){
	// Enable Update Event
	TIMx->CR1.REG &= ~TIM_CR1_UDIS;
}

/**
 * @brief Disables the Update Event for TIMx
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 */
__STATIC_INLINE__ void TIM_UEV_Disable(TIM_REG_STRUCT* TIMx){
	// Disable Update Event
	TIMx->CR1.REG |= TIM_CR1_UDIS;
}

/**
 * @brief Configures the polarity for a specific timer channel
 * @param TIMx_CONFIG Pointer to the timer configuration structure
 * @param polarity The desired polarity for the channel
 */
__STATIC_INLINE__ void TIM_Polarity_Config(timer_config_t* TIMx_CONFIG, tim_channel_polarity_t polarity){
	// Get the current CCER register value
	uint32_t reg = TIMx_CONFIG->instance->CCER.REG;
	// Clear the polarity bits for the channel
	if(TIMx_CONFIG->channel.instance & TIMx_CHANNEL_1){
		reg &= ~TIM_CCER_CC1P;
		reg |= (polarity << TIM_CCER_CC1P_Pos);
	}
	if(TIMx_CONFIG->channel.instance & TIMx_CHANNEL_2){
		reg &= ~TIM_CCER_CC2P;
		reg |= (polarity << TIM_CCER_CC2P_Pos);
	}
	if(TIMx_CONFIG->channel.instance & TIMx_CHANNEL_3){
		reg &= ~TIM_CCER_CC3P;
		reg |= (polarity << TIM_CCER_CC3P_Pos);
	}
	if(TIMx_CONFIG->channel.instance & TIMx_CHANNEL_4){
		reg &= ~TIM_CCER_CC4P;
		reg |= (polarity << TIM_CCER_CC4P_Pos);
	}
	// Configure Timer Channel Polarity
	TIMx_CONFIG->instance->CCER.REG = reg;
}

#endif /* __TIMER_CONFIG_H__ */