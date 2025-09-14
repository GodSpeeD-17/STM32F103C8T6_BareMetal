/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// Initialisation of LEDs
gpio_config_t combinedLEDConfig = {
	.pin = (RED_LED_PIN | YELLOW_LED_PIN),
};
// Initialisation of Push Button
gpio_config_t pushButtonConfig = {
	.pin = PUSH_BUTTON_PIN,
	.mode = GPIO_MODE_INPUT,
	.config = GPIO_PIN_CNF_IN_FLOAT
};
// Debounce Time Counter
volatile uint32_t time_now = 0;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// LED Initialisation
	GPIO_LED_Init(RED_LED_PORT, &combinedLEDConfig);
	// Push Button Initialisation
	GPIO_Init(PUSH_BUTTON_PORT, &pushButtonConfig);
	// Assign EXTI Line to Push Button Pin
	GPIO_EXTI_Init(PUSH_BUTTON_PORT, pushButtonConfig.pin, GPIO_EXTI_TRIGGER_FALLING);
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
	if(GPIO_EXTI_IsTriggered(pushButtonConfig.pin)){
		// Eliminate Debounce Time
		if(SysTick_Get_Ticks() - time_now > DEBOUNCE_TIME_MS){
			time_now = SysTick_Get_Ticks();
			// Toggle the Red LED
			GPIO_Toggle(RED_LED_PORT, RED_LED_PIN);
		}
		// Clear the Pending Bit
		GPIO_EXTI_Ack(pushButtonConfig.pin);
	}
}
/*-------------------------------------------------------------------------------*/