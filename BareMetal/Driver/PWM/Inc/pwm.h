// Header Guards
#ifndef __PWM_H__
#define __PWM_H__

// Header Files
#include "pwm_config.h"

// Handle Type Definition
typedef struct pwm_handle* pwm_handle_t;

/**
 * @brief Configures PWM
 * @param PWM_HANDLE Final Handle for future reference to PWM Configuration
 * @param PWM_CONFIG PWM Configuration Structure
 * @returns Pointer to the PWM Handle on success
 * @returns -1 on memory allocation failure
 * @returns -2 on incorrect GPIO to Timer mapping
 * @note This function dynamically allocates memory for the PWM handle
 * @note After using, remember to free the handle using `PWM_DeConfig()`
 */
pwm_handle_t PWM_Config(pwm_config_t* PWM_CONFIG);

/**
 * @brief Deconfigures the PWM
 * @param PWM_HANDLE Final Handle for future reference to PWM Configuration
 * @return `NULL` on success
 * @note This function frees the dynamically allocated memory for the PWM handle
 * @note This function should be called after the PWM is no longer needed post `PWM_Config()`
 */
pwm_handle_t PWM_DeConfig(pwm_handle_t PWM_HANDLE);

/**
 * @brief Default Timer Configuration Structure for PWM
 * @param PWM_HANDLE PWM Handle
 * @note - Timer Mode: Edge Mode
 * @note - Direction: Up Counting
 */
void PWM_Default_TIM_Config(pwm_handle_t PWM_HANDLE);

/**
 * @brief Enables the PWM Channel
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Start(pwm_handle_t PWM_HANDLE);

/**
 * @brief Enables the PWM
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Enable(pwm_handle_t PWM_HANDLE);

/**
 * @brief Disables the PWM Channel
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Stop(pwm_handle_t PWM_HANDLE);

/**
 * @brief Disables the PWM
 * @param PWM_HANDLE Handle to the PWM Configuration
 */
void PWM_Disable(pwm_handle_t PWM_HANDLE);

/**
 * @brief Updates the Duty Cycle for a PWM Configuration
 * @param PWM_HANDLE Handle to the PWM Configuration
 * @param duty_cycle Updated Duty Cycle Value (%) x 10
 * @note `duty_cycle` is scaled value:
 * @note For 0.1% Duty Cycle -> `duty_cycle = 1`
 * @note For 100% Duty Cycle -> `duty_cycle = 1000`
 */
void PWM_Update_Duty_Cycle(pwm_handle_t PWM_HANDLE, uint16_t duty_cycle);

/**
 * @brief Calculates Timer Prescaler based on target PWM Frequency 
 * @param PWM_HANDLE Handle to the PWM Configuration
 * @returns Timer Prescaler Value
 */
uint16_t PWM_Calc_TIM_Prescaler(pwm_handle_t PWM_HANDLE);

#endif /* __PWM_H__ */