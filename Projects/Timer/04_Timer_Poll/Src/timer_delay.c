#include "main.h"

extern timer_config_t TIM2_Config;

void TIMx_Delay_ms(volatile uint32_t delayMs){
	// Iteration for each number of milliseconds
	while(delayMs--){
		TIM2_Config.TIMx;
	}
}