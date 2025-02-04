/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	config_GPIO(&LED_GPIO_Config);
	config_EXTI(&PB_EXTI_Config);
	// Infinite Loop
	while(1){
		// Toggle OB LED
		toggle_OB_LED();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/
// IRQ Handler
void EXTI9_5_IRQHandler(void){
	// Confirm PIN
	if(get_EXTI_pend(PB_GPIO_Config.PINx)){
		// Toggle External LED
		toggle_GPIO(&LED_GPIO_Config);
		// Acknowledge the EXTI
		clear_EXTI_pend(PB_GPIO_Config.PINx);
	}
}
/*-------------------------------------------------------------------------------*/