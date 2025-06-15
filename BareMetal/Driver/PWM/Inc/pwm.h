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

/**
 * @brief Enables the PWM
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Enable(pwm_handle_t* PWM_HANDLE);

/**
 * @brief Enables the PWM Channel
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Channel_Enable(pwm_handle_t* PWM_HANDLE);

/**
 * @brief Disables the PWM
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Disable(pwm_handle_t* PWM_HANDLE);

/**
 * @brief Disables the PWM Channel
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Channel_Disable(pwm_handle_t* PWM_HANDLE);


#endif /* __PWM_H__ */