/***************************************************************************************
 *  File: timer.h
 *  Created on: 23/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __TIMER_H__
#define __TIMER_H__

// Register Mapping
#include "timer_config.h"

/**
 * @brief Calculates the Prescaler Value based upon ARR Value provided
 * @param freq_Hz Frequency (in Hz)
 * @param arr_value Auto-Reload Register Value
 * @return Prescaler Value
 */
uint16_t TIM_Calc_Prescaler(uint32_t freq_Hz, uint16_t arr_value);

/**
 * @brief Configures the General Purpose Timer (TIMx)
 * @param TIMx_CONFIG Pointer to timer configuration structure
 */
void TIM_Config(timer_config_t* TIMx_CONFIG);

/**
 * @brief Configures the default parameters for TIMx_CONFIG
 * @param TIMx_CONFIG Pointer to timer configuration structure
 * @note - TIM & Channel should be already configured
 * @note - This loads frequency as 10kHz
 */
void TIM_10kHz_Load_Default(timer_config_t* TIMx_CONFIG);

/**
 * @brief Configures the default parameters for TIMx_CONFIG
 * @param TIMx_CONFIG Pointer to timer configuration structure
 * @note - TIM & Channel should be already configured
 * @note - This loads frequency as 1MHz
 */
void TIM_1MHz_Load_Default(timer_config_t* TIMx_CONFIG);

/**
 * @brief Provides CCMRx expected register value based on Channel Configuration Settings
 * @param channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`  
 * @param config Channel Configuration Structure
 * @param ccmr_reg Pointer to CCMR register value
 */
void TIM_Channel_CCMRx_Config(timer_channel_t channel, timer_channel_config_t config, uint16_t* ccmr_reg);

/**
 * @brief Configures the Timer Channel as per configuration structure
 * @param TIMx_CONFIG Pointer to Timer Configuration Structure
 */
void TIM_Channel_Config(timer_config_t* TIMx_CONFIG);

/**
 * @brief Configures the General Purpose Timer (TIMx)
 * @param TIMx_CONFIG Pointer to timer configuration structure
 */
void TIM_Config(timer_config_t* TIMx_CONFIG);

/**
 * @brief Retrieves the Interrupt Status
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_OUT_CMP_CHx`, `TIMx_IRQ_IN_CAP_CHx`
 * @return - 0: Interrupt was not triggered 
 * @return - 1: Interrupt was triggered 
 */
__STATIC_FORCEINLINE uint8_t TIM_IRQ_Get_Status(TIM_TypeDef* TIMx, timer_irq_t IRQ){
	// Capture the Status Register
	uint16_t status = TIMx->SR.REG;
	// Acknowledge Interrupt Flag
	if(IRQ & TIMx_IRQ_OVF_UVF)
		status >>= TIM_SR_UIF_Pos;
	// Acknowledge Capture/Compare Interrupt for Channel 1
	if((IRQ & TIMx_IRQ_OUT_CMP_CH1) || (IRQ & TIMx_IRQ_IN_CAP_CH1))
		status >>= TIM_SR_CC1IF_Pos;
	// Acknowledge Capture/Compare Interrupt for Channel 2
	if((IRQ & TIMx_IRQ_OUT_CMP_CH2) || (IRQ & TIMx_IRQ_IN_CAP_CH2))
		status >>= TIM_SR_CC2IF_Pos;
	// Acknowledge Capture/Compare Interrupt for Channel 3
	if((IRQ & TIMx_IRQ_OUT_CMP_CH3) || (IRQ & TIMx_IRQ_IN_CAP_CH3))
		status >>= TIM_SR_CC3IF_Pos;
	// Acknowledge Capture/Compare Interrupt for Channel 4
	if((IRQ & TIMx_IRQ_OUT_CMP_CH4) || (IRQ & TIMx_IRQ_IN_CAP_CH4))
		status >>= TIM_SR_CC4IF_Pos;
	// Return the status
	status &= 0x01;
	return ((uint8_t)status);
}

/**
 * @brief Retrieves the Overflow/Underflow Interrupt Status
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @return - 0: Interrupt was not triggered 
 * @return - 1: Interrupt was triggered
 */
__STATIC_FORCEINLINE uint8_t TIM_IRQ_Get_OVF_UVF(TIM_TypeDef* TIMx){
	// Get the Status Register Value
	return (TIMx->SR.REG & 0x01);
}

/**
 * @brief Timer Interrupt Flag Acknowledge
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_OUT_CMP_CHx`, `TIMx_IRQ_IN_CAP_CHx`
 */
__STATIC_FORCEINLINE void TIM_IRQ_Ack(TIM_TypeDef* TIMx, timer_irq_t IRQ){
	// Get the Status Register
	uint16_t status = TIMx->SR.REG;
	// Acknowledge Interrupt Flag
	if(IRQ & TIMx_IRQ_OVF_UVF)
		status &= ~TIM_SR_UIF;
	// Acknowledge Capture/Compare Interrupt for Channel 1
	if((IRQ & TIMx_IRQ_OUT_CMP_CH1) || (IRQ & TIMx_IRQ_IN_CAP_CH1))
		status &= ~TIM_SR_CC1IF;
	// Acknowledge Capture/Compare Interrupt for Channel 2
	if((IRQ & TIMx_IRQ_OUT_CMP_CH2) || (IRQ & TIMx_IRQ_IN_CAP_CH2))
		status &= ~TIM_SR_CC2IF;
	// Acknowledge Capture/Compare Interrupt for Channel 3
	if((IRQ & TIMx_IRQ_OUT_CMP_CH3) || (IRQ & TIMx_IRQ_IN_CAP_CH3))
		status &= ~TIM_SR_CC3IF;
	// Acknowledge Capture/Compare Interrupt for Channel 4
	if((IRQ & TIMx_IRQ_OUT_CMP_CH4) || (IRQ & TIMx_IRQ_IN_CAP_CH4))
		status &= ~TIM_SR_CC4IF;
	// Update the Status Register
	TIMx->SR.REG = status;
}

/**
 * @brief Acknowledges the Overflow/Underflow Interrupt Status
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 */
__STATIC_FORCEINLINE void TIM_IRQ_Ack_OVF_UVF(TIM_TypeDef* TIMx){
	// Acknowledge the Interrupt Flag
	TIMx->SR.REG &= ~TIM_SR_UIF;
}

/**
 * @brief Creates a delay using Timer
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param delayUs Number of microseconds to delay
 * @note The following assumptions are made: 
 * @note - Timer is configured for 1MHz
 * @note - Timer is upcounter
 * @note - Timer Channel 1 is used for output compare
 */
void TIM_delay_us(TIM_TypeDef* TIMx, uint32_t delayUs);

/**
 * @brief Creates a delay using Timer
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param delayMs Number of milliseconds to delay
 * @note The following assumptions are made: 
 * @note - Timer is configured for 1MHz
 * @note - Timer is upcounter
 * @note - Timer Channel 1 is used for output compare
 */
void TIM_delay_ms(TIM_TypeDef* TIMx, uint32_t delayMs);

/**
 * @brief Enables Timer Interrupt for mentioned Interrupt
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_OUT_CMP_CHx`, `TIMx_IRQ_IN_CAP_CHx`
 */
void TIM_IRQ_Enable(TIM_TypeDef* TIMx, timer_irq_t IRQ);

/**
 * @brief Disables Timer Interrupt for mentioned Interrupt
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_OUT_CMP_CHx`, `TIMx_IRQ_IN_CAP_CHx`
 */
void TIM_IRQ_Disable(TIM_TypeDef* TIMx, timer_irq_t IRQ);

/**
 * @brief Timer Interrupt Flag Acknowledge
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_OUT_CMP_CHx`, `TIMx_IRQ_IN_CAP_CHx`
 */
void TIM_IRQ_Ack(TIM_TypeDef* TIMx, timer_irq_t IRQ);

/**
 * @brief Retrieves the Interrupt Status
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @param IRQ `TIMx_IRQ_OVF_UVF`, `TIMx_IRQ_OUT_CMP_CHx`, `TIMx_IRQ_IN_CAP_CHx`
 * @return - 0: Interrupt was not triggered 
 * @return - 1: Interrupt was triggered 
 */
uint8_t TIM_IRQ_Get_Status(TIM_TypeDef* TIMx, timer_irq_t IRQ);

/**
 * @brief Resets the General Purpose TIMx
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 */
void TIM_Reset(TIM_TypeDef* TIMx);

/**
 * @brief Provides the Timer Frequency
 * @param TIMx `TIM2`, `TIM3`, `TIM4`
 * @returns Timer Frequency (in Hz)
 */
uint32_t TIM_Get_Frequency(TIM_TypeDef* TIMx);


#endif /* __TIMER_H__ */
