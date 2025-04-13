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
	GPIO_Config(&LED_GPIO_Config);
	PB_EXTI_Config.TRIGx = EXTI_TRIG_BOTH;
	EXTI_config(&PB_EXTI_Config);
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
// IRQ Handler
void EXTI9_5_IRQHandler(void){
	// Confirm PIN
	if(EXTI_getPending(PB_GPIO_Config.PIN)){
		// Push-Button Pressed
		if(GPIO_Get(&PB_GPIO_Config)){
			GPIO_Set(&LED_GPIO_Config);
		}
		// Push-Button Released
		else{
			GPIO_Reset(&LED_GPIO_Config);
		}
		// Acknowledge the EXTI
		EXTI_clearPending(PB_GPIO_Config.PIN);
	}
}
/*-------------------------------------------------------------------------------*/
#else
// Main Entry Point
int main(){
	// Initialisation
	GPIO_Config(&LED_GPIO_Config);
	EXTI_config(&PB_EXTI_Config);
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
// IRQ Handler
void EXTI9_5_IRQHandler(void){
	// Confirm PIN
	if(EXTI_getPending(PB_GPIO_Config.PIN)){
		// Toggle External LED
		GPIO_Toggle(&LED_GPIO_Config);
		// Acknowledge the EXTI
		EXTI_clearPending(PB_GPIO_Config.PIN);
	}
}
/*-------------------------------------------------------------------------------*/
#endif /* BOTH_TRIGGER */