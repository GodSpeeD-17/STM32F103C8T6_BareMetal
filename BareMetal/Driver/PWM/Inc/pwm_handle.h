// Header Guards
#ifndef __PWM_HANDLE_H__
#define __PWM_HANDLE_H__

#include "pwm.h"

// Internal Handle for PWM Configuration
struct pwm_handle {
	// PWM Configuration Structure
	pwm_config_t* PWMx_CONFIG;
	// Timer Configuration Structure
	timer_config_t TIMx_CONFIG;
};



#endif /* __PWM_HANDLE_H__ */