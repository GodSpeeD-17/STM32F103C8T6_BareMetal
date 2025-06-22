/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// PWM Configuration Structure
pwm_config_t yellow_led = {
	.GPIOx_CONFIG = {
		.GPIO = GPIOA,
		.PIN = GPIOx_PIN_2,
	},
	.freq_Hz = FREQ_10kHz,
	.duty_cycle = 500,
	.mode = PWM_MODE_NORMAL,
	.polarity = PWM_CHx_POL_ACTIVE_HIGH,
	.preload = PWM_CHx_PRELOAD_ENABLE, 
};
// PWM Handle Structure
pwm_handle_t pwm_yellow_led_handle;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	pwm_yellow_led_handle = PWM_Config(&yellow_led);
	// Enable PWM
	PWM_Enable(pwm_yellow_led_handle);
	// Infinite Loop
	while(1){
		OB_LED_Toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Free PWM Handle
	PWM_DeConfig(pwm_yellow_led_handle);
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/