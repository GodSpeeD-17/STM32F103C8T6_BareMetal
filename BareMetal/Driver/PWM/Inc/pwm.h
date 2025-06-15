// Header Guards
#ifndef __PWM_H__
#define __PWM_H__

// Header Files
#include "pwm_config.h"

// Handle Type Definition
typedef struct pwm_handle pwm_handle_t;

/**
 * @brief Configures the GPIO based on Timer for PWM output
 * @param TIMx_CONFIG General Purpose Timer Configuration Structure
 * @param GPIOx_CONFIG GPIO Configuration Structure
 */
void PWM_GPIO_Config(const timer_config_t* TIMx_CONFIG, gpio_config_t* GPIOx_CONFIG);

#endif /* __PWM_H__ */