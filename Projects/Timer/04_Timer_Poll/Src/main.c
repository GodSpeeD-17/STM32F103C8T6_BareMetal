/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// GPIO Configuration Structure
gpio_config_t PA2_Config = {
	.GPIOx = GPIOA,
	.PINx = GPIO_PIN_2,
	.MODEx = MODE_OUT_10MHz,
	.CNFx = CNF_OUT_GP_PP
};

// Timer 2 Configuration Structure
timer_config_t TIM2_Config = {
	.arpe = TIMx_ARPE_ENABLE,
	.auto_reload = 1000,
	.channel = TIMx_CHANNEL_3,
	.cms_mode = TIMx_CMS_EDGE,
	.count = 0,
	.direction = TIMx_DIR_COUNT_UP,
	.enable_IRQ = TIMx_IRQ_DISABLE,
	.GPIO_CONFIGx = NULL,
	.one_pulse = TIMx_OPM_ENABLE,
	.prescaler = (72-1),
	.TIMx = TIM2,
};
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// GPIO Initialisation
	GPIO_config(&PA2_Config);
	// Timer Initialisation
	config_TIM(&TIM2_Config);
	// Infinite Loop
	while(1){
		// Conditional Compilation
		#ifndef MS_DELAY
		// Loop Delay
			TIM_delay_us(&TIM2_Config, LOOP_DELAY_MS * 10);
		#else
			TIM_delay_ms(&TIM2_Config, LOOP_DELAY_MS);
		#endif
		GPIO_toggle(&PA2_Config);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/