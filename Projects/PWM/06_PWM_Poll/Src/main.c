/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
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
/*-------------------------------------------------------------------------------*/
// PWM Handle Structure
pwm_handle_t yellow_led_handle;
pwm_handle_t red_led_handle;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	// red_led_handle = PWM_Config(&red_led);
	yellow_led_handle = PWM_Config(&yellow_led);
	// Enable PWM
	// PWM_Enable(red_led_handle);
	PWM_Enable(yellow_led_handle);
	// Duty Cycle Variable
	uint16_t duty_cycle = 0;
	// Infinite Loop
	while(1){
		// Update Duty Cycle
		for(duty_cycle = 0; duty_cycle < PWM_DEFAULT_ARR; duty_cycle++){
			// PWM_Update_Duty_Cycle(red_led_handle, duty_cycle);
			PWM_Update_Duty_Cycle(yellow_led_handle, duty_cycle);
			delay_ms(10);
		}
		// Toggle OB LED
		OB_LED_Toggle();
		// Update Duty Cycle
		for(duty_cycle = PWM_DEFAULT_ARR; duty_cycle > 0; duty_cycle--){
			// PWM_Update_Duty_Cycle(red_led_handle, duty_cycle);
			PWM_Update_Duty_Cycle(yellow_led_handle, duty_cycle);
			delay_ms(10);
		}
		// Toggle OB LED
		OB_LED_Toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Free PWM Handle
	// PWM_DeConfig(red_led_handle);
	PWM_DeConfig(yellow_led_handle);
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/