// Header Guards
#ifndef __PWM_H__
#define __PWM_H__

// Header Files
#include "pwm_config.h"

// Handle Type Definition
typedef struct pwm_handle pwm_handle_t;

/**
 * @brief Configures PWM 
 * @param PWM_HANDLE Final Handle for future reference to PWM Configuration
 * @param PWM_CONFIG PWM Configuration Structure
 */
void PWM_Config(pwm_handle_t* PWM_HANDLE, pwm_config_t* PWM_CONFIG);

#endif /* __PWM_H__ */