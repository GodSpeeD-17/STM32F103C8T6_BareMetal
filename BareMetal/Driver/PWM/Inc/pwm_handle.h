// Header Guards
#ifndef __PWM_HANDLE_H__
#define __PWM_HANDLE_H__

// Header Files
#include "pwm_config.h"

// Internal Handle for PWM Configuration
struct pwm_handle {
	// PWM Configuration Structure
	pwm_config_t PWM_CONFIG;
	// Timer Configuration Structure
	timer_config_t TIMx_CONFIG;
};

/**
 * @brief Default Timer Configuration Structure for PWM
 * @param PWM_HANDLE PWM Handle
 * @note - Timer Mode: Edge Mode
 * @note - Direction: Up Counting
 */
void PWM_Default_TIM_Config(pwm_handle_t* PWM_HANDLE) {
	// Counter Max Value based on Duty Cycle precision of 0.1%
	PWM_HANDLE->TIMx_CONFIG.auto_reload = PWM_DEFAULT_ARR;
	// Default Count Value 
	PWM_HANDLE->TIMx_CONFIG.count = TIMx_DEFAULT_CNT;
	// Default Timer Couting Mode
	PWM_HANDLE->TIMx_CONFIG.cms_mode = TIMx_CMS_EDGE;
	// Default Timer Couting Direction
	PWM_HANDLE->TIMx_CONFIG.direction = TIMx_DIR_COUNT_UP;
	// Default Timer Auto-Reload Preload Enabled
	PWM_HANDLE->TIMx_CONFIG.arpe = TIMx_ARPE_ENABLE;
	// Default Timer One Pulse Mode Disabled
	PWM_HANDLE->TIMx_CONFIG.one_pulse = TIMx_OPM_DISABLE;
}


#endif /* __PWM_HANDLE_H__ */