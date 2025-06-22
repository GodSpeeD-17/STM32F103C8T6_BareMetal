/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
#define RED_LED
#define YELLOW_LED
/*-------------------------------------------------------------------------------*/
#ifdef YELLOW_LED
	// Yellow LED PWM Configuration Structure
	pwm_config_t yellow_led = {
		.GPIOx_CONFIG = {
			.GPIO = GPIOA,
			.PIN = GPIOx_PIN_3,
		},
		.freq_Hz = FREQ_10kHz,
		.duty_cycle = 0,
		.mode = PWM_MODE_NORMAL,
		.polarity = PWM_CHx_POL_ACTIVE_HIGH,
		.preload = PWM_CHx_PRELOAD_ENABLE, 
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
		.freq_Hz = FREQ_10kHz,
		.duty_cycle = 0,
		.mode = PWM_MODE_NORMAL,
		.polarity = PWM_CHx_POL_ACTIVE_HIGH,
		.preload = PWM_CHx_PRELOAD_ENABLE, 
	};
	// PWM Handle Structure
	pwm_handle_t red_led_handle;
#endif /* RED_LED */
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	#ifdef RED_LED
		red_led_handle = PWM_Config(&red_led);
		PWM_Enable(red_led_handle);
	#endif /* RED_LED */
	#ifdef YELLOW_LED
		yellow_led_handle = PWM_Config(&yellow_led);
		PWM_Enable(yellow_led_handle);
	#endif /* YELLOW_LED */
	// Duty Cycle Variable
	uint16_t duty_cycle = 0;
	// Infinite Loop
	while(1){
		// Increase Duty Cycle
		for(duty_cycle = 0; duty_cycle < PWM_DEFAULT_ARR; duty_cycle++){
			#ifdef RED_LED
				PWM_Update_Duty_Cycle(red_led_handle, duty_cycle);
			#endif /* RED LED*/
			#ifdef YELLOW_LED
				PWM_Update_Duty_Cycle(yellow_led_handle, duty_cycle);
			#endif /* YELLOW LED*/
			delay_ms(10);
		}
		
		// Toggle OB LED
		OB_LED_Toggle();

		// Decrease Duty Cycle
		for(duty_cycle = PWM_DEFAULT_ARR; duty_cycle > 0; duty_cycle--){
			#ifdef RED_LED
				PWM_Update_Duty_Cycle(red_led_handle, duty_cycle);
			#endif /* RED LED*/
			#ifdef YELLOW_LED
				PWM_Update_Duty_Cycle(yellow_led_handle, duty_cycle);
			#endif /* YELLOW LED*/
			delay_ms(10);
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