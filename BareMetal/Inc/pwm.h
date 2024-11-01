/***************************************************************************************
 *  File: pwm.h
 *  Created on: 26/10/2024
 *  Author: shrey_shah
 ***************************************************************************************/

// Header Guards
#ifndef __PWM_H__
#define __PWM_H__

// Dependency
#include "gpio.h"
#include "timer.h"

// IMP: Store this value in ARR always to simplify the PWM calculation
#define DEFAULT_ARR_VALUE            ((uint16_t) 99)    // (ARR + 1) = (99 + 1) = (100) 
#define MIN_DUTY_CYCLE               ((uint8_t) 1)      // Min Value = 1%
#define MAX_DUTY_CYCLE               ((uint8_t) 100)    // Max Value = 100%

// Timer Remapping
#define TIM1_NO_REMAP                ((uint8_t) 0x00)
#define TIM1_PARTIAL_REMAP           ((uint8_t) 0x01)
#define TIM2_NO_REMAP                ((uint8_t) 0x00)
#define TIM2_PARTIAL_REMAP_1         ((uint8_t) 0x01)
#define TIM2_PARTIAL_REMAP_2         ((uint8_t) 0x02)
#define TIM2_FULL_REMAP              ((uint8_t) 0x03)
#define TIM3_NO_REMAP                ((uint8_t) 0x00)
#define TIM3_PARTIAL_REMAP           ((uint8_t) 0x02)
#define TIM4_NO_REMAP                ((uint8_t) 0x00)

// Preload Enable
#define PRELOAD_DISABLE              ((uint8_t) 0x00)
#define PRELOAD_ENABLE               ((uint8_t) 0x01)

// Enable Alternate Function
#define RCC_AF_ENABLE()              (RCC->APB2ENR.BIT.AFIOEN = BIT_SET)

// Timer Modes
typedef enum{
	TIMx_OCM_FREEZE         = ((uint8_t) 0x00),    // The comparison between the output compare register TIMx_CCRy and the counter TIMx_CNT has no effect on the outputs.
	TIMx_OCM_SET_CH         = ((uint8_t) 0x01),    // OCyREF signal is forced high when TIMx_CNT == TIMx_CCRy    
	TIMx_OCM_RESET_CH       = ((uint8_t) 0x02),    // OCyREF signal is forced low when TIMx_CNT == TIMx_CCRy
	TIMx_OCM_TOGGLE         = ((uint8_t) 0x03),    // OCyREF toggles when TIMx_CNT == TIMx_CCRy
	TIMx_OCM_FORCE_RESET    = ((uint8_t) 0x04),    // OCyREF is forced low
	TIMx_OCM_FORCE_SET      = ((uint8_t) 0x05),    // OCyREF is forced high
	TIMx_OCM_PWM_NORMAL     = ((uint8_t) 0x06),    // In up counting, CHy is active as long as TIMx_CNT < TIMx_CCRy else inactive. In down counting, CHy is inactive (OC1REF = ‘0’) as long as TIMx_CNT > TIMx_CCRy else active (OC1REF = ’1’) 
	TIMx_OCM_PWM_INVERTED   = ((uint8_t) 0x07),    // In up counting, CHy is inactive as long as TIMx_CNT < TIMx_CCRy else active. In down counting, CHy is active (OC1REF = ‘0’) as long as TIMx_CNT > TIMx_CCRy else active (OC1REF = ’1’) 
} TIMx_OCM_MODE;

/**
 * @brief Configure PWM Mode for General Purpose TIMx
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4`
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 * @param[in] pwm_mode  `TIMx_OCM_PWM_NORMAL`, `TIMx_OCM_PWM_INVERTED`
 * @param[in] preload_enable `PRELOAD_ENABLE`, `PRELOAD_DISABLE`
 */
void config_PWM_mode(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, TIMx_OCM_MODE pwm_mode, uint8_t preload_enable);

/**
 * @brief Configure PWM related parameters for GP Timer
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4` 
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 * @param[in] polarity  `TIMx_POL_ACTIVE_LOW`, `TIMx_POL_ACTIVE_HIGH`
 */
void set_PWM_polarity(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, uint8_t polarity);

/**
 * @brief Updates the Duty Cycle for the specified TIMx and Channel
 * @param[in] GP_TIMx `TIM2`, `TIM3`, `TIM4` 
 * @param[in] channel `TIMx_CHANNEL_1`, `TIMx_CHANNEL_2`, `TIMx_CHANNEL_3`, `TIMx_CHANNEL_4`, `TIMx_CHANNEL_ALL`
 * @param[in] duty_cycle Duty Cycle Value in (%) 
 */
void set_PWM_duty_cycle(GPT_REG_STRUCT* GP_TIMx, uint8_t channel, uint8_t duty_cycle);

#endif // __PWM_H__
