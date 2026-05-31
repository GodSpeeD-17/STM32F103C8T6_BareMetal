/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// Debounce Time Counter
volatile uint32_t time_now = 0;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// LED Initialisation
	GPIO_LED_Init(RED_LED_PORT, (RED_LED_PIN | YELLOW_LED_PIN));
	// Push Button Initialisation
	GPIO_Init(PUSH_BUTTON_PORT, PUSH_BUTTON_PIN, GPIO_PIN_MODE_INPUT, GPIO_PIN_CONFIG_INPUT_FLOATING);
	// Assign EXTI Line to Push Button Pin
	GPIO_EXTI_Init(PUSH_BUTTON_PORT, PUSH_BUTTON_PIN, GPIO_EXTI_TRIGGER_FALLING);
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
/**
 * @brief IRQ Handler
 */
void EXTI1_IRQHandler(void){
	// Check if the Interrupt is from the Push Button
	if(GPIO_EXTI_IsTriggered(PUSH_BUTTON_PIN)){
		// Eliminate Debounce Time
		if(SysTick_Get_Ticks() - time_now > DEBOUNCE_TIME_MS){
			time_now = SysTick_Get_Ticks();
			// Toggle the Red LED
			GPIO_PinToggle(RED_LED_PORT, RED_LED_PIN);
		}
		// Clear the Pending Bit
		GPIO_EXTI_Ack(PUSH_BUTTON_PIN);
	}
}
/*-------------------------------------------------------------------------------*/
