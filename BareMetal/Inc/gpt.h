/***************************************************************************************
 *  File: gpt.h
 *  Created on: 13/10/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __GPT_H__
#define __GPT_H__

// Register Mapping
#include "reg_map.h"
#include "rcc.h"

/**
 * @brief Enables the Clock for General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @note RCC->APB1ENR
 */
inline __attribute__((always_inline)) void enable_GPT_clk(GPT_REG_STRUCT* GP_TIMx){
	// Enable the clock for the timer
	if(GP_TIMx == TIM2)
		RCC->APB1ENR.BIT.TIM2EN = BIT_SET;
	else if(GP_TIMx == TIM3)
		RCC->APB1ENR.BIT.TIM3EN = BIT_SET;
	else if(GP_TIMx == TIM4)
		RCC->APB1ENR.BIT.TIM4EN = BIT_SET;
}

/**
 * @brief Disables the Clock for General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @note RCC->APB1ENR
 */
inline __attribute__((always_inline)) void disable_GPT_clk(GPT_REG_STRUCT* GP_TIMx){
	// Disable the clock for the timer
	if(GP_TIMx == TIM2)
		RCC->APB1ENR.BIT.TIM2EN = BIT_RESET;
	else if(GP_TIMx == TIM3)
		RCC->APB1ENR.BIT.TIM3EN = BIT_RESET;
	else if(GP_TIMx == TIM4)
		RCC->APB1ENR.BIT.TIM4EN = BIT_RESET;
}

/**
 * @brief Enables the General Purpose GP_TIMx
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 */
inline __attribute__((always_inline)) void enable_GPT(GPT_REG_STRUCT* GP_TIMx){
    // Clear Update Interrupt Flag
    GP_TIMx->SR.BIT.UIF = BIT_RESET;
	// Enable GP_TIMx
	GP_TIMx->CR1.BIT.CEN = BIT_SET;
}

/**
 * @brief Disables the General Purpose GP_TIMx
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 */
inline __attribute__((always_inline)) void disable_GPT(GPT_REG_STRUCT* GP_TIMx){
	// Disable GP_TIMx
	GP_TIMx->CR1.BIT.CEN = BIT_RESET;
    // Clear Update Interrupt Flag
    GP_TIMx->SR.BIT.UIF = BIT_RESET;
}

/**
 * @brief Enables the General Purpose GP_TIMx's Channel
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
inline __attribute__((always_inline)) void enable_GPT_CH(GPT_REG_STRUCT* GP_TIMx, uint8_t channel){

	// Enable the General Purpose Timer Channel
	switch(channel){
		
		case TIMx_CHANNEL_1:
			GP_TIMx->CCER.BIT.CC1E = BIT_SET;
		break;

		case TIMx_CHANNEL_2:
			GP_TIMx->CCER.BIT.CC2E = BIT_SET;
		break;
		
		case TIMx_CHANNEL_3:
			GP_TIMx->CCER.BIT.CC3E = BIT_SET;
		break;
		
		case TIMx_CHANNEL_4:
			GP_TIMx->CCER.BIT.CC4E = BIT_SET;
		break;

		case TIMx_CHANNEL_ALL:
			GP_TIMx->CCER.BIT.CC1E = BIT_SET;
			GP_TIMx->CCER.BIT.CC2E = BIT_SET;
			GP_TIMx->CCER.BIT.CC3E = BIT_SET;
			GP_TIMx->CCER.BIT.CC4E = BIT_SET;
		break;
	}
}

/**
 * @brief Disables the General Purpose GP_TIMx's Channel
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
inline __attribute__((always_inline)) void disable_GPT_CH(GPT_REG_STRUCT* GP_TIMx, uint8_t channel){

	// Enable the General Purpose Timer Channel
	switch(channel){
		
		case TIMx_CHANNEL_1:
			GP_TIMx->CCER.BIT.CC1E = BIT_RESET;
		break;

		case TIMx_CHANNEL_2:
			GP_TIMx->CCER.BIT.CC2E = BIT_RESET;
		break;
		
		case TIMx_CHANNEL_3:
			GP_TIMx->CCER.BIT.CC3E = BIT_RESET;
		break;
		
		case TIMx_CHANNEL_4:
			GP_TIMx->CCER.BIT.CC4E = BIT_RESET;
		break;

		case TIMx_CHANNEL_ALL:
			GP_TIMx->CCER.BIT.CC1E = BIT_RESET;
			GP_TIMx->CCER.BIT.CC2E = BIT_RESET;
			GP_TIMx->CCER.BIT.CC3E = BIT_RESET;
			GP_TIMx->CCER.BIT.CC4E = BIT_RESET;
		break;
	}
}

/**
 * @brief Resets the General Purpose GP_TIMx
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 */
inline __attribute((always_inline)) void reset_GPT(GPT_REG_STRUCT* GP_TIMx){
    // Reset Based on GPT
    if(GP_TIMx == TIM2){
        RCC->APB1RSTR.BIT.TIM2RST = BIT_SET;
        RCC->APB1RSTR.BIT.TIM2RST = BIT_RESET;
    }
    else if(GP_TIMx == TIM3){
        RCC->APB1RSTR.BIT.TIM3RST = BIT_SET;
        RCC->APB1RSTR.BIT.TIM3RST = BIT_RESET;
    }
    else if(GP_TIMx == TIM4){
        RCC->APB1RSTR.BIT.TIM4RST = BIT_SET;
        RCC->APB1RSTR.BIT.TIM4RST = BIT_RESET;
    }
}

/**
 * @brief Calculates the Prescaler Value based upon ARR Value provided
 * @param[in] freq_Hz Frequency (in Hz)
 * @param[in] arr_value Auto-Reload Register Value
 * @return Prescaler Value
 */
inline __attribute__((always_inline)) uint16_t calc_GPT_PSC(uint32_t freq_Hz, uint16_t arr_value){
	
	// Final Value
	uint32_t prescaler_value = 0x00;
	
	// Calculate the Timer Frequency
	if((RCC->CFGR.BIT.PPRE1 == APB1_DIV_1))
		prescaler_value = get_APB1_freq();
	else
		prescaler_value = (uint32_t)(2 * get_APB1_freq());
	
	// Update the value based upon the desired frequency
	prescaler_value /= freq_Hz;

	// Update the value based upon the ARR Value
	prescaler_value /= (arr_value + 1);

	// Final Calculated Value
	return (uint16_t)(prescaler_value - 1);
} 

/**
 * @brief Configure General Purpose GP_TIMx (Clock Source + Frequency)
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] arr_value ARR Value
 * @param[in] freq_Hz Timer Frequency (in Hz)
 * @param[in] count_value Timer Counter Value 
 * @note - Assumed DIR is Up Counting
 * @note - Assumed Edge Aligned Mode (Up counting or Down counting)
 */
void config_GPT(GPT_REG_STRUCT* GP_TIMx, uint16_t arr_value, uint32_t freq_Hz, uint16_t count_value);

/**
 * @brief Configures GP Timer Counting Mode along with Direction
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] cms_mode Center-Aligned Mode Selection `TIMx_MODE_...`
 * @param[in] direction `TIMx_COUNT_UP`, `TIMx_COUNT_DOWN`
 */
inline __attribute__((always_inline)) void set_GPT_mode(GPT_REG_STRUCT* GP_TIMx, uint8_t cms_mode, uint8_t direction){
	// Centre-Aligned Mode Selection
	GP_TIMx->CR1.BIT.CMS = cms_mode;
	// Direction Selection
	GP_TIMx->CR1.BIT.DIR = direction;
    // Send an update event to reset the timer and apply settings
  	GP_TIMx->EGR.BIT.UG = BIT_SET;
}

/**
 * @brief Gets the GP Timer Clock Frequency
 * @param[in] GP_TIMx  `TIM2`, `TIM3`, `TIM4`
 * @note Refer the formula mentioned in .c file  & clock tree to get clear understanding
 */
uint32_t get_GPT_freq(GPT_REG_STRUCT* GP_TIMx);

/**
 * @brief Updates the frequency of already configured General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] freq_Hz Timer Frequency (in Hz)
 */
inline __attribute__((always_inline)) void set_GPT_freq(GPT_REG_STRUCT* GP_TIMx, uint32_t freq_Hz){
	// Calculate updated PSC Value
	GP_TIMx->PSC = calc_GPT_PSC(freq_Hz, GP_TIMx->ARR);
    // Send an update event to reset the timer and apply settings
  	GP_TIMx->EGR.BIT.UG = BIT_SET;
}

/**
 * @brief Updates the frequency of already configured General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] arr_value Auto Reload Value
 */
inline __attribute__((always_inline)) void set_GPT_ARR(GPT_REG_STRUCT* GP_TIMx, uint16_t arr_value){
	// Calculate updated PSC Value
	GP_TIMx->ARR = arr_value;
    // Send an update event to reset the timer and apply settings
  	GP_TIMx->EGR.BIT.UG = BIT_SET;
}

/**
 * @brief Enables the Interrupt Generation for General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 */
inline __attribute__((always_inline)) void enable_GPT_IRQ(GPT_REG_STRUCT* GP_TIMx){
    // Enable the Interrupt
    GP_TIMx->DIER.BIT.UIE = BIT_SET;
}

/**
 * @brief Disables the Interrupt Generation for General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 */
inline __attribute__((always_inline)) void disable_GPT_IRQ(GPT_REG_STRUCT* GP_TIMx){
    // Disable the interrupt
    GP_TIMx->DIER.BIT.UIE = BIT_RESET;
}

/**
 * @brief General Purpose Timer Delay
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] delayMs Number of milliseconds
 */
void GPT_delay_ms(GPT_REG_STRUCT* GP_TIMx, volatile uint32_t delayMs);

#endif /* __GPT_H__ */
