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
	GPIO_config(&LED_GPIO_Config);
	PB_EXTI_Config.TRIGx = EXTI_TRIG_BOTH;
	EXTI_config(&PB_EXTI_Config);
	// Infinite Loop
	while(1){
		// Toggle OB LED
		OB_LED_toggle();
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
	if(EXTI_getPending(PB_GPIO_Config.PINx)){
		// Push-Button Pressed
		if(GPIO_get(&PB_GPIO_Config)){
			GPIO_set(&LED_GPIO_Config);
		}
		// Push-Button Released
		else{
			GPIO_reset(&LED_GPIO_Config);
		}
		// Acknowledge the EXTI
		EXTI_clearPending(PB_GPIO_Config.PINx);
	}
}
/*-------------------------------------------------------------------------------*/
#else
// Main Entry Point
int main(){
	// Initialisation
	GPIO_config(&LED_GPIO_Config);
	EXTI_config(&PB_EXTI_Config);
	// Infinite Loop
	while(1){
		// Toggle OB LED
		OB_LED_toggle();
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
	if(EXTI_getPending(PB_GPIO_Config.PINx)){
		// Toggle External LED
		GPIO_toggle(&LED_GPIO_Config);
		// Acknowledge the EXTI
		EXTI_clearPending(PB_GPIO_Config.PINx);
	}
}
/*-------------------------------------------------------------------------------*/
#endif /* BOTH_TRIGGER */