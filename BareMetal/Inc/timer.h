/***************************************************************************************
 *  File: timer.h
 *  Created on: 13/10/2024
 *  Author: shrey_shah
 ***************************************************************************************/

// Header Guards
#ifndef __TIMER_H__
#define __TIMER_H__

// Register Mapping
#include "reg_map.h"
#include "rcc.h"

// Centre-align Mode Selection
#define CMS_EDGE			    ((uint8_t) 0x00)
#define CMS_IF_DOWN			    ((uint8_t) 0x01)
#define CMS_IF_UP			    ((uint8_t) 0x02)
#define CMS_IF_BOTH			    ((uint8_t) 0x03)

// Clock Division
#define CKD_CLK_FREQ		    ((uint8_t) 0x00)
#define CKD_CLK_2_FREQ		    ((uint8_t) 0x01)
#define CKD_CLK_4_FREQ		    ((uint8_t) 0x02)

// Master Mode Selection
#define MMS_RESET			    ((uint8_t) 0x00)
#define MMS_ENABLE			    ((uint8_t) 0x01)
#define MMS_UPDATE			    ((uint8_t) 0x02)
#define MMS_CMP_PULSE		    ((uint8_t) 0x03)
#define MMS_CMP_OC1REF		    ((uint8_t) 0x04)
#define MMS_CMP_OC2REF		    ((uint8_t) 0x05)
#define MMS_CMP_OC3REF		    ((uint8_t) 0x06)
#define MMS_CMP_OC4REF		    ((uint8_t) 0x07)

// Slave Mode Selection
#define SMS_DISABLE			    ((uint8_t) 0x00)
#define SMS_ENC_MODE1		    ((uint8_t) 0x01)
#define SMS_ENC_MODE2		    ((uint8_t) 0x02)
#define SMS_ENC_MODE3		    ((uint8_t) 0x03)

// TIM1 REMAP
#define TIM1_NO_REMAP           ((uint8_t) 0x00)    // (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12, CH1N/PB13, CH2N/PB14, CH3N/PB15)
#define TIM1_PARTIAL_REMAP      ((uint8_t) 0x01)    // (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6, CH1N/PA7, CH2N/PB0, CH3N/PB1)
#define TIM1_NOT_USED_REMAP     ((uint8_t) 0x02)    // Not Used
#define TIM1_FULL_REMAP         ((uint8_t) 0x03)    // (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15, CH1N/PE8, CH2N/PE10, CH3N/PE12)

// TIM2 REMAP
#define TIM2_NO_REMAP           ((uint8_t) 0x00)    // (CH1/ETR/PA0, CH2/PA1, CH3/PA2, CH4/PA3)
#define TIM2_PARTIAL1_REMAP     ((uint8_t) 0x01)    // (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3)
#define TIM2_PARTIAL2_REMAP     ((uint8_t) 0x02)    // (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11)
#define TIM2_FULL_REMAP         ((uint8_t) 0x03)    // (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11) 

// TIM3 REMAP
#define TIM3_NO_REMAP           ((uint8_t) 0x00)    // (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1)
#define TIM3_NOT_USED_REMAP     ((uint8_t) 0x01)    // Not Used
#define TIM3_PARTIAL_REMAP      ((uint8_t) 0x02)    // (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1)
#define TIM3_FULL_REMAP         ((uint8_t) 0x03)    // (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9) 

// TIM4 REMAP
#define TIM4_NO_REMAP           ((uint8_t) 0x00)    // (TIM4_CH1/PB6, TIM4_CH2/PB7, TIM4_CH3/PB8, TIM4_CH4/PB9)
#define TIM4_FULL_REMAP         ((uint8_t) 0x01)    // (TIM4_CH1/PD12, TIM4_CH2/PD13, TIM4_CH3/PD14, TIM4_CH4/PD15)

// Channel
#define TIMx_CHANNEL_1          ((uint8_t) 1)
#define TIMx_CHANNEL_2          ((uint8_t) 2)
#define TIMx_CHANNEL_3          ((uint8_t) 3)
#define TIMx_CHANNEL_4          ((uint8_t) 4)
#define TIMx_CHANNEL_ALL        ((uint8_t) 0xFF)

// Counting Mode
#define TIMx_MODE_NORMAL        ((uint8_t) 0x00)    // Up if DIR = 0 else Down if DIR = 1
#define TIMx_MODE_ALT_IF_DOWN   ((uint8_t) 0x01)
#define TIMx_MODE_ALT_IF_UP     ((uint8_t) 0x02)
#define TIMx_MODE_ALT_IF_BOTH   ((uint8_t) 0x03)

// Direction 
#define TIMx_COUNT_UP           ((uint8_t) 0x00)
#define TIMx_COUNT_DOWN         ((uint8_t) 0x01)

// Polarity (Define what Active means)
#define TIMx_POL_ACTIVE_HIGH    ((uint8_t) 0x00)
#define TIMx_POL_ACTIVE_LOW     ((uint8_t) 0x01)

/**
 * @brief Enables the Clock for General Purpose Timer
 * @param[in] GP_TIMx General Purpose Timer
 * @note RCC->APB1ENR
 */
inline __attribute__((always_inline)) void enable_GPT_clk(GPT_REG_STRUCT* GP_TIMx){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4)
		return;
		
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
 * @param[in] GP_TIMx General Purpose Timer
 * @note RCC->APB1ENR
 */
inline __attribute__((always_inline)) void disable_GPT_clk(GPT_REG_STRUCT* GP_TIMx){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4)
		return;

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
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 */
inline __attribute__((always_inline)) void enable_GPT(GPT_REG_STRUCT* GP_TIMx){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4)
		return;

	// Enable GP_TIMx
	GP_TIMx->CR1.BIT.CEN = BIT_SET;
}

/**
 * @brief Disables the General Purpose GP_TIMx
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 */
inline __attribute__((always_inline)) void disable_GPT(GPT_REG_STRUCT* GP_TIMx){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4)
		return;

	// Disable GP_TIMx
	GP_TIMx->CR1.BIT.CEN = BIT_RESET;
}

/**
 * @brief Enables the General Purpose TIMx's Channel
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
void enable_GPT_CH(GPT_REG_STRUCT* TIMx, uint8_t channel);

/**
 * @brief Disables the General Purpose TIMx's Channel
 * @param[in] TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 */
void disable_GPT_CH(GPT_REG_STRUCT* TIMx, uint8_t channel);

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
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @param[in] arr_value ARR Value
 * @param[in] freq_Hz Timer Frequency (in Hz)
 * @param[in] count_value Timer Counter Value 
 * @note - ERROR HANDLING NOT DONE
 * @note - Assumed DIR is Up Counting
 * @note - Assumed Edge Aligned Mode (Up counting or Down counting)
 */
void config_GPT(GPT_REG_STRUCT* GP_TIMx, uint16_t arr_value, uint32_t freq_Hz, uint16_t count_value);

/**
 * @brief Configures GP Timer Counting Mode along with Direction
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @param[in] cms_mode Centre-aligned mode selection `TIMx_MODE_...`
 * @param[in] direction `TIMx_COUNT_UP`, `TIMx_COUNT_DOWN`
 */
inline __attribute__((always_inline)) void set_GPT_mode(GPT_REG_STRUCT* GP_TIMx, uint8_t cms_mode, uint8_t direction){
	
	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4)
		return; 

	// Centre-Aligned Mode Selection
	GP_TIMx->CR1.BIT.CMS = cms_mode;

	// Direction Selection
	GP_TIMx->CR1.BIT.DIR = direction;
}

/**
 * @brief Gets the GP Timer Clock Frequency
 * @param[in] GP_TIMx  `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @note Refer the formula mentioned in .c file  & clock tree to get clear understanding
 */
uint32_t get_GPT_freq(GPT_REG_STRUCT* GP_TIMx);

/**
 * @brief Updates the frequency of already configured General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @param[in] freq_Hz Timer Frequency (in Hz)
 */
inline __attribute__((always_inline)) void set_GPT_freq(GPT_REG_STRUCT* GP_TIMx, uint32_t freq_Hz){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4)
		return; 

	// Calculate updated PSC Value
	GP_TIMx->PSC = calc_GPT_PSC(freq_Hz, GP_TIMx->ARR);
}

/**
 * @brief Updates the frequency of already configured General Purpose Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`, `TIM5`
 * @param[in] arr_value Auto Reload Value
 */
inline __attribute__((always_inline)) void set_GPT_ARR(GPT_REG_STRUCT* GP_TIMx, uint16_t arr_value){

	// Error Check
	if(GP_TIMx != TIM2 && GP_TIMx != TIM3 && GP_TIMx != TIM4)
		return;

	// Calculate updated PSC Value
	GP_TIMx->ARR = arr_value;
}

/**
 * @brief General Purpose Timer Delay
 * @param[in] GP_TIMx General Purpose Timer (TIM2, ..., TIM5)
 * @param[in] delayMs Number of milliseconds
 */
void GPT_delay_ms(GPT_REG_STRUCT* GP_TIMx, volatile uint32_t delayMs);

#endif /* __TIMER_H__ */
