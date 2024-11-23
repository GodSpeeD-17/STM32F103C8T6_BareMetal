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

// Timer Configuration Structure
__attribute__((packed)) typedef struct {
    // General Purpose Timer
    GPT_REG_STRUCT* GP_TIMx;
	// General Purpose Timer Channel
    uint8_t channel;
    // Auto Reload Value
    uint16_t auto_reload_value;
    // Frequency
    uint32_t frequency_Hz;
    // Count
    uint16_t count;
    // Centre-Aligned Mode Selection
	uint8_t cms_mode;
    // Count Direction
	uint8_t direction;
} gpt_config_t;

/*********************************************** Private ***********************************************/

/**
 * @brief Configures GP Timer Counting Mode along with Direction
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] cms_mode Center-Aligned Mode Selection `TIMx_MODE_...`
 */
__attribute__((always_inline)) static inline void set_GPT_mode(GPT_REG_STRUCT* GP_TIMx, uint8_t cms_mode){
	// Centre-Aligned Mode Selection
	GP_TIMx->CR1.BIT.CMS = cms_mode;
}

/**
 * @brief Configures GP Timer Counting Mode along with Direction
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] direction `TIMx_COUNT_UP`, `TIMx_COUNT_DOWN`
 */
__attribute__((always_inline)) static inline void set_GPT_direction(GPT_REG_STRUCT* GP_TIMx, uint8_t direction){
	// Direction Selection
	GP_TIMx->CR1.BIT.DIR = direction;
}

/**
 * @brief Updates the frequency of already configured General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] freq_Hz Timer Frequency (in Hz)
 */
__attribute__((always_inline)) static inline void set_GPT_frequency(GPT_REG_STRUCT* GP_TIMx, uint32_t freq_Hz){
	// Error
	if(freq_Hz == 0)
		return;
	// Calculate updated PSC Value
	GP_TIMx->PSC = calc_GPT_PSC(freq_Hz, GP_TIMx->ARR);
}

/**
 * @brief Updates the frequency of already configured General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] arr_value Auto Reload Value
 */
__attribute__((always_inline)) static inline void set_GPT_ARR(GPT_REG_STRUCT* GP_TIMx, uint16_t arr_value){
	// Calculate updated PSC Value
	GP_TIMx->ARR = arr_value;
}

/**
 * @brief Configures GP Timer Counting Mode along with Direction
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] cms_mode Center-Aligned Mode Selection `TIMx_MODE_...`
 * @param[in] direction `TIMx_COUNT_UP`, `TIMx_COUNT_DOWN`
 */
__attribute__((always_inline)) static inline void set_GPT_count(GPT_REG_STRUCT* GP_TIMx, uint8_t count_value){
	// Set the count value
	GP_TIMx->CNT = count_value;
}

/**
 * @brief Enables the Interrupt Generation for General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 */
__attribute__((always_inline)) static inline void enable_GPT_IRQ(GPT_REG_STRUCT* GP_TIMx){
    // Enable the Interrupt
    GP_TIMx->DIER.BIT.UIE = BIT_SET;
}

/**
 * @brief Disables the Interrupt Generation for General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 */
__attribute__((always_inline)) static inline void disable_GPT_IRQ(GPT_REG_STRUCT* GP_TIMx){
    // Disable the interrupt
    GP_TIMx->DIER.BIT.UIE = BIT_RESET;
}

/*********************************************** Private ***********************************************/

/*********************************************** Public ***********************************************/

/**
 * @brief Enables the Clock for General Purpose Timer
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void enable_GPT_clk(gpt_config_t* GPT_CONFIGx){
	// Enable the clock for the timer
	if(GPT_CONFIGx->GP_TIMx == TIM2)
		RCC->APB1ENR.BIT.TIM2EN = BIT_SET;
	else if(GPT_CONFIGx->GP_TIMx == TIM3)
		RCC->APB1ENR.BIT.TIM3EN = BIT_SET;
	else if(GPT_CONFIGx->GP_TIMx == TIM4)
		RCC->APB1ENR.BIT.TIM4EN = BIT_SET;
}

/**
 * @brief Disables the Clock for General Purpose Timer
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 * @note RCC->APB1ENR
 */
__attribute__((always_inline)) inline void disable_GPT_clk(gpt_config_t* GPT_CONFIGx){
	// Disable the clock for the timer
	if(GPT_CONFIGx->GP_TIMx == TIM2)
		RCC->APB1ENR.BIT.TIM2EN = BIT_RESET;
	else if(GPT_CONFIGx->GP_TIMx == TIM3)
		RCC->APB1ENR.BIT.TIM3EN = BIT_RESET;
	else if(GPT_CONFIGx->GP_TIMx == TIM4)
		RCC->APB1ENR.BIT.TIM4EN = BIT_RESET;
}

/**
 * @brief Enables the General Purpose GP_TIMx
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void enable_GPT(gpt_config_t* GPT_CONFIGx){
    // Clear Update Interrupt Flag
    GPT_CONFIGx->GP_TIMx->SR.BIT.UIF = BIT_RESET;
	// Enable GP_TIMx
	GPT_CONFIGx->GP_TIMx->CR1.BIT.CEN = BIT_SET;
}

/**
 * @brief Disables the General Purpose GP_TIMx
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void disable_GPT(gpt_config_t* GPT_CONFIGx){
	// Disable GP_TIMx
	GPT_CONFIGx->GP_TIMx->CR1.BIT.CEN = BIT_RESET;
    // Clear Update Interrupt Flag
    GPT_CONFIGx->GP_TIMx->SR.BIT.UIF = BIT_RESET;
}

/**
 * @brief Enables the General Purpose GP_TIMx's Channel
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
__attribute__((always_inline)) inline void enable_GPT_CH(gpt_config_t* GPT_CONFIGx){

	// Enable the General Purpose Timer Channel
	switch(GPT_CONFIGx->channel){
		
		case TIMx_CHANNEL_1:
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC1E = BIT_SET;
		break;

		case TIMx_CHANNEL_2:
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC2E = BIT_SET;
		break;
		
		case TIMx_CHANNEL_3:
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC3E = BIT_SET;
		break;
		
		case TIMx_CHANNEL_4:
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC4E = BIT_SET;
		break;

		case TIMx_CHANNEL_ALL:
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC1E = BIT_SET;
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC2E = BIT_SET;
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC3E = BIT_SET;
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC4E = BIT_SET;
		break;
	}
}

/**
 * @brief Disables the General Purpose GP_TIMx's Channel
 * @param[in] GPT_CONFIGx 
 */
__attribute__((always_inline)) inline void disable_GPT_CH(gpt_config_t* GPT_CONFIGx){

	// Enable the General Purpose Timer Channel
	switch(GPT_CONFIGx->channel){
		
		case TIMx_CHANNEL_1:
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC1E = BIT_RESET;
		break;

		case TIMx_CHANNEL_2:
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC2E = BIT_RESET;
		break;
		
		case TIMx_CHANNEL_3:
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC3E = BIT_RESET;
		break;
		
		case TIMx_CHANNEL_4:
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC4E = BIT_RESET;
		break;

		case TIMx_CHANNEL_ALL:
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC1E = BIT_RESET;
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC2E = BIT_RESET;
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC3E = BIT_RESET;
			GPT_CONFIGx->GP_TIMx->CCER.BIT.CC4E = BIT_RESET;
		break;
	}
}

/**
 * @brief Resets the General Purpose GP_TIMx
 * @param[in] GPT_CONFIGx
 */
__attribute__((always_inline)) inline void reset_GPT(gpt_config_t* GPT_CONFIGx){
    // Reset Based on GPT
    if(GPT_CONFIGx->GP_TIMx == TIM2){
        RCC->APB1RSTR.BIT.TIM2RST = BIT_SET;
        RCC->APB1RSTR.BIT.TIM2RST = BIT_RESET;
    }
    else if(GPT_CONFIGx->GP_TIMx == TIM3){
        RCC->APB1RSTR.BIT.TIM3RST = BIT_SET;
        RCC->APB1RSTR.BIT.TIM3RST = BIT_RESET;
    }
    else if(GPT_CONFIGx->GP_TIMx == TIM4){
        RCC->APB1RSTR.BIT.TIM4RST = BIT_SET;
        RCC->APB1RSTR.BIT.TIM4RST = BIT_RESET;
    }
}

/**
 * @brief Triggers an update event to apply the settings
 * @param[in] GPT_CONFIGx
 */
__attribute__((always_inline)) inline void update_GPT_params(gpt_config_t* GPT_CONFIGx){
	// Send an update event to reset the timer and apply settings
  	GPT_CONFIGx->GP_TIMx->EGR.BIT.UG = BIT_SET;
}

/**
 * @brief Calculates the Prescaler Value based upon ARR Value provided
 * @param[in] freq_Hz Frequency (in Hz)
 * @param[in] arr_value Auto-Reload Register Value
 * @return Prescaler Value
 */
__attribute__((always_inline)) inline uint16_t calc_GPT_PSC(uint32_t freq_Hz, uint16_t arr_value){
	
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
 * @brief Configures the General Purpose Timer (GPT)
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
void config_GPT(gpt_config_t* GPT_CONFIGx);

/**
 * @brief Gets the GP Timer Clock Frequency
 * @param[in] GPT_CONFIGx `gpt_config_t *` structure containing the configuration
 */
uint32_t get_GPT_freq(gpt_config_t* GPT_CONFIGx);

/**
 * @brief General Purpose Timer Delay
 * @param[in] GPT_CONFIGx `TIM2`, `TIM3`, `TIM4`
 * @param[in] delayMs Number of milliseconds
 */
void GPT_delay_ms(gpt_config_t* GPT_CONFIGx, volatile uint32_t delayMs);

/*********************************************** Private ***********************************************/

#endif /* __GPT_H__ */
