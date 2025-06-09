// Header Guards
#ifndef __TIMER_CONFIG_H__
#define __TIMER_CONFIG_H__

// Register Mapping
#include "reg_map.h"

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
	uint16_t prescaler;
	// Start Count Value
	uint16_t count;
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
 * @brief Enables the Clock for General Purpose Timer
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 */
__INLINE__ void TIM_Clk_Enable(TIM_REG_STRUCT* TIMx){
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
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 */
__INLINE__ void TIM_Clk_Disable(TIM_REG_STRUCT* TIMx){
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
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 */
__INLINE__ void TIM_Enable(TIM_REG_STRUCT* TIMx){
	// Clear Update Interrupt Flag
	TIMx->SR.REG &= ~TIM_SR_UIF;
	// Enable TIMx
	TIMx->CR1.REG |= TIM_CR1_CEN;
}

/**
 * @brief Disables the General Purpose TIMx
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 */
__INLINE__ void TIM_Disable(TIM_REG_STRUCT* TIMx){
	// Disable TIMx
	TIMx->CR1.REG &= ~TIM_CR1_CEN;
	// Clear Update Interrupt Flag
	TIMx->SR.REG &= ~TIM_SR_UIF;
}

/**
 * @brief Enables the General Purpose TIMx's Channel
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
__INLINE__ void TIM_Channel_Enable(TIM_REG_STRUCT* TIMx, uint8_t channel){
	// Local Variable
	uint32_t reg = TIMx->CCER.REG; 
	// Enable the General Purpose Timer Channel
	if(channel & TIMx_CHANNEL_1)
		reg |= TIM_CCER_CC1E;
	if(channel & TIMx_CHANNEL_2)
		reg |= TIM_CCER_CC2E;
	if(channel & TIMx_CHANNEL_3)
		reg |= TIM_CCER_CC3E;
	if(channel & TIMx_CHANNEL_4)
		reg |= TIM_CCER_CC4E;
	// Write to the register
	TIMx->CCER.REG = reg;
}

/**
 * @brief Disables the General Purpose TIMx's Channel
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
__INLINE__ void TIM_Channel_Disable(TIM_REG_STRUCT* TIMx, uint8_t channel){
	// Local Variable
	uint32_t reg = TIMx->CCER.REG; 
	// Enable the General Purpose Timer Channel
	if(channel & TIMx_CHANNEL_1)
		reg &= ~TIM_CCER_CC1E;
	if(channel & TIMx_CHANNEL_2)
		reg &= ~TIM_CCER_CC2E;
	if(channel & TIMx_CHANNEL_3)
		reg &= ~TIM_CCER_CC3E;
	if(channel & TIMx_CHANNEL_4)
		reg &= ~TIM_CCER_CC4E;
	// Write to the register
	TIMx->CCER.REG = reg;
}

/**
 * @brief Retrieves the IRQn based upon TIMx
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @returns IRQn (0 - 59)
 */
__INLINE__ uint8_t TIM_Get_IRQn(TIM_REG_STRUCT* TIMx){
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
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @returns UIF Flag Status
 */
__INLINE__ uint8_t TIM_Get_UIF(TIM_REG_STRUCT* TIMx){
	// Update Interrupt Flag (UIF) Status
	return (uint8_t)(TIMx->SR.REG & TIM_SR_UIF);
}

/**
 * @brief Clears the pending interrupt of TIMx 
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 * @returns UIF Flag Status
 */
__INLINE__ void TIM_Clear_UIF(TIM_REG_STRUCT* TIMx){
	// Clear Update Interrupt Flag (UIF)
	TIMx->SR.REG &= ~TIM_SR_UIF;
}

/**
 * @brief Triggers an update event to apply the settings
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 */
__INLINE__ void TIM_Update_Parameters(TIM_REG_STRUCT* TIMx){
	// Send an update event to reset the timer and apply settings
  	TIMx->EGR.REG |= TIM_EGR_UG;
	// Wait until bit reset by Hardware
	while(TIMx->EGR.REG & TIM_EGR_UG);
	// Clear the update flag
	TIMx->SR.REG &= ~TIM_SR_UIF; 
}

/**
 * @brief Enables the Update Event for TIMx
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 */
__INLINE__ void TIM_UEV_Enable(TIM_REG_STRUCT* TIMx){
	// Enable Update Event
	TIMx->CR1.REG &= ~TIM_CR1_UDIS;
}

/**
 * @brief Disables the Update Event for TIMx
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`
 */
__INLINE__ void TIM_UEV_Disable(TIM_REG_STRUCT* TIMx){
	// Disable Update Event
	TIMx->CR1.REG |= TIM_CR1_UDIS;
}



#endif /* __TIMER_CONFIG_H__ */