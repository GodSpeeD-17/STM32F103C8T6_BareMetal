/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Rising & Falling Edge Trigger
#ifdef BOTH_TRIGGER
// Main Entry Point
int main(){
	// Initialisation
	config_GPIO(&LED_GPIO_Config);
	PB_EXTI_Config.TRIGx = EXTI_TRIG_BOTH;
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
		// Push-Button Pressed
		if(get_GPIO(&PB_GPIO_Config)){
			set_GPIO(&LED_GPIO_Config);
		}
		// Push-Button Released
		else{
			reset_GPIO(&LED_GPIO_Config);
		}
		// Acknowledge the EXTI
		clear_EXTI_pend(PB_GPIO_Config.PINx);
	}
}
/*-------------------------------------------------------------------------------*/
#else
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
#endif /* BOTH_TRIGGER */