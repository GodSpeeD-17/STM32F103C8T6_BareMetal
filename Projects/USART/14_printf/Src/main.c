/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	uint32_t ticks_start = 0x00, ticks_end = 0x00;
	USART1_config();
	USART1_enable();
	// Infinite Loop
	while(1){
		// Default Separate
		USART1_DEF_SEP();
		// Update start ticks
		ticks_start = get_curr_ticks();
		// With precision
		USART_printf(&USART1_Config, "1.2 + 1.3 = %.2f\r\n", 1.2 + 1.3);
		// Update end ticks
		ticks_end = get_curr_ticks();
		// Calculating Time (Each tick corresponds to 1ms due to SysTick Configuration)
		USART_printf(&USART1_Config, "Time taken = %d ms\r\n", ticks_end - ticks_start);
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
		// Default Separate
		USART1_DEF_SEP();
		// Update start ticks
		ticks_start = get_curr_ticks();
		// Without precision
		USART_printf(&USART1_Config, "4.2821 + 6.9347 = %f\r\n", 4.2821 + 6.9347);
		// Update end ticks
		ticks_end = get_curr_ticks();
		// Calculating Time (Each tick corresponds to 1ms due to SysTick Configuration)
		USART_printf(&USART1_Config, "Time taken = %d ms\r\n", ticks_end - ticks_start);
		// Default Separate
		USART1_DEF_SEP();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/