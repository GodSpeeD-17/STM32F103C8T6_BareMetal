/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// Timer 4 Configuration
timer_config_t TIM4_Config = {
	.TIM = TIM4,
	.channel = TIMx_CHANNEL_ALL,
};
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Timer Initialisation
	TIM_1MHz_Load_Default(&TIM4_Config);
	TIM_Config(&TIM4_Config);
	// Infinite Loop
	while(1){
		// Toggle OB LED
		OB_LED_Toggle();
		// Loop Delay
		TIM_delay_ms(TIM4_Config.TIM, 1000);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/