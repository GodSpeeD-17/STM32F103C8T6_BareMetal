/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// Macros
#define RED_LED
#define YELLOW_LED
#define PWM_DUTY_UPDATE				(10)
/*-------------------------------------------------------------------------------*/
#ifdef YELLOW_LED
	// Yellow LED PWM Configuration Structure
	pwm_config_t yellow_led = {
		.GPIOx_CONFIG = {
			.GPIO = GPIOA,
			.PIN = GPIOx_PIN_3,
		},
	};
	// PWM Handle Structure
	pwm_handle_t yellow_led_handle;
#endif /* YELLOW_LED */
#ifdef RED_LED
	// Red LED PWM Configuration Structure
	pwm_config_t red_led = {
		.GPIOx_CONFIG = {
			.GPIO = GPIOA,
			.PIN = GPIOx_PIN_2,
		},
	};
	// PWM Handle Structure
	pwm_handle_t red_led_handle;
#endif /* RED_LED */
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	#ifdef RED_LED
		PWM_Default_Configuration(&red_led);
		red_led_handle = PWM_Config(&red_led);
		PWM_Enable(red_led_handle);
	#endif /* RED_LED */
	#ifdef YELLOW_LED
		PWM_Default_Configuration(&yellow_led);
		yellow_led_handle = PWM_Config(&yellow_led);
		PWM_Enable(yellow_led_handle);
	#endif /* YELLOW_LED */
	// Duty Cycle Variable
	int16_t duty_cycle = PWM_MIN_DUTY_CYCLE;
	// Infinite Loop
	while(1){
		// Increase Duty Cycle
		for(duty_cycle; duty_cycle < PWM_MAX_DUTY_CYCLE; duty_cycle += PWM_DUTY_UPDATE){
			#ifdef RED_LED
				PWM_Update_Duty_Cycle(red_led_handle, duty_cycle);
			#endif /* RED LED*/
			#ifdef YELLOW_LED
				PWM_Update_Duty_Cycle(yellow_led_handle, duty_cycle);
			#endif /* YELLOW LED*/
			delay_ms(PWM_DUTY_UPDATE << 1);
		}
		
		// Toggle OB LED
		OB_LED_Toggle();

		// Decrease Duty Cycle
		for(duty_cycle; duty_cycle > PWM_MIN_DUTY_CYCLE; duty_cycle -= PWM_DUTY_UPDATE){
			#ifdef RED_LED
				PWM_Update_Duty_Cycle(red_led_handle, duty_cycle);
			#endif /* RED LED*/
			#ifdef YELLOW_LED
				PWM_Update_Duty_Cycle(yellow_led_handle, duty_cycle);
			#endif /* YELLOW LED*/
			delay_ms(PWM_DUTY_UPDATE << 1);
		}

		// Toggle OB LED
		OB_LED_Toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Free PWM Handle
	#ifdef RED_LED
		PWM_DeConfig(red_led_handle);
	#endif /* RED_LED */
	#ifdef YELLOW_LED
		PWM_DeConfig(yellow_led_handle);
	#endif /* YELLOW_LED */

	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/