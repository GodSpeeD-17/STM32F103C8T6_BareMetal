/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// RED LED Configuration
gpio_config_t LED_Red = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_2,
};
// Yellow LED Configuration
gpio_config_t LED_Yellow = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_3,
};
// Push Button Configuration
gpio_config_t Push_Button = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_1,
	.MODE = GPIOx_MODE_IN,
	.CNF = GPIOx_CNF_IN_PD,
};
// Debounce Time Counter
volatile uint64_t time_now = 0;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation of LEDs
	GPIO_Config_LED(&LED_Red);
	GPIO_Config_LED(&LED_Yellow);
	// Push Button IRQ
	EXTI_Config(&Push_Button, EXTI_TRIG_FALLING); 
	// Infinite Loop
	while(1){
		// Toggle OB LED
		OB_LED_Toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
		// Toggle Yellow LED
		GPIO_Toggle(&LED_Yellow);
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
	if(EXTI_IRQ_Get_Pending(Push_Button.PIN)){
		// Eliminate Debounce Time
		if(SysTick_Get_Ticks() - time_now > DEBOUNCE_TIME_MS){
			time_now = SysTick_Get_Ticks();
			// Toggle the Red LED
			GPIO_Toggle(&LED_Red);
		}
		// Clear the Pending Bit
		EXTI_IRQ_Clear_Pending(Push_Button.PIN);
	}
}
/*-------------------------------------------------------------------------------*/