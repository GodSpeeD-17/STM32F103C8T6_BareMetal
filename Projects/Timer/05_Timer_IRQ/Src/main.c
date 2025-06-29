/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// Timer 4 Configuration
timer_config_t TIM4_Config = {
	.TIM = TIM4,
	.channel = TIMx_CHANNEL_ALL
};
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	TIM_10kHz_Load_Default(&TIM4_Config);
	// Configure Timer 4 with 1MHz Configuration
	TIM_Config(&TIM4_Config);
	// Enable Interrupt for Timer 4
	TIM_IRQ_Enable(TIM4_Config.TIM, TIMx_IRQ_OVF_UVF);
	// Enable the Timer 4
	TIM_Enable(TIM4_Config.TIM);
	// Infinite Loop
	while(1){
		// Do Nothing
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/
// Timer IRQ Handler
void TIM4_IRQHandler(void){
	// Overflow/Underflow detected
	if(TIM_Get_IRQ_Status(TIM4_Config.TIM, TIMx_IRQ_OVF_UVF)){
		// Toggle OB LED
		OB_LED_Toggle();
		// Acknowledge the Interrupt
		TIM_IRQ_Ack(TIM4_Config.TIM, TIMx_IRQ_OVF_UVF);
	}

}
/*-------------------------------------------------------------------------------*/