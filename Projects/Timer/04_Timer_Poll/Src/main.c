/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
#ifdef __OLD_TIMER_METHOD__
// Timer 2 Configuration
tim_config_t TIM_Configuration = {
	.TIM = TIM2,
	.channel = TIMx_CHANNEL_ALL,
};
#else
// Timer 2 Configuration
tim_config_t TIM_Configuration = {
	.instance = TIM2,
	.channel.instance = TIMx_CHANNEL_ALL,
};
#endif /* __OLD_TIMER_METHOD__ */
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	TIM_1MHz_Load_Default(&TIM_Configuration);
	TIM_Config(&TIM_Configuration);

	// Infinite Loop
	while(1){
		// Toggle OB LED
		OB_LED_Toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/