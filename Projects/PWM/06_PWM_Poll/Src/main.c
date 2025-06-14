/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// Timer 2 Configuration Structure
timer_config_t TIM2_Config;
gpio_config_t TIM2_PWM_Config;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	TIM_1MHz_Load_Default(&TIM2_Config);
	TIM2_Config.TIM = TIM2;
	TIM2_Config.channel = TIMx_CHANNEL_3;


	// Infinite Loop
	while(1){
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/