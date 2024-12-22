// Main Header
#include "main.h"

// GPIO Configuration Structure
gpio_config_t usart_tx_config = {
	.GPIOx = USART_PORT,
	.PINx = USART_TX_PIN,
};
gpio_config_t usart_rx_config = {
	.GPIOx = USART_PORT,
	.PINx = USART_RX_PIN,
};
// USART Configuration Structure
usart_config_t usart_config = {
	.TX_GPIO_CONFIGx = &usart_tx_config,
	.RX_GPIO_CONFIGx = &usart_rx_config,
	.USARTx = USART,
};

// ADC Configuration Structure
gpio_config_t pot_config = {
	.GPIOx = POT_PORT,
	.PINx = POT_PIN,
};
adc_config_t adc_config = {
	.GPIO_CONFIGx = &pot_config,
	.ADCx = POT_ADC,
	.channel = POT_ADC_CHANNEL,
};

// Global Variables
volatile uint8_t adc_conversion_complete = 0x00;
volatile uint16_t adc_data[2] = {0};

// Main Entry Point for User Code
int main(void){
	
	// Configure Clock
	config_SYSCLK_MHz(SYSCLK_MHz);
	// SysTick Timer (1ms)
	config_SysTick(SYSTICK_DELAY_1_MS);

	// ADC Configuration
	load_ADC_default(&adc_config);
	adc_config.enable_IRQ = ADCx_IRQ_ENABLE;
	config_ADC(&adc_config);

	// USART Configuration 
	load_USART_default(&usart_config);
	config_USART(&usart_config);
	enable_USART(&usart_config);

	// On-board LED Configuration
	config_OB_LED();
	reset_OB_LED();

	// Infinite Loop
	while(1){

		// ADC Conversion Completed
		if(adc_conversion_complete){
			// Read ADC data
			adc_data[0] = get_ADC_data(&adc_config);
			// ADC Data exceeds the Error Range
			if ((adc_data[0] > (adc_data[1] + ADC_ERROR_RANGE)) || (adc_data[0] < (adc_data[1] - ADC_ERROR_RANGE))){
				// Shift the new data
				adc_data[1] = adc_data[0];
				// Separate Function (Visually Pleasing) 
				// DEFAULT_SEP(&usart_config); // Causes more delay while printing in real-time
				// Print the data on USART
				USART_printf(&usart_config, "ADC Data: %d\r\n", adc_data[1]);
				// Toggle OB LED
				toggle_OB_LED();
			}
		}
		
		// Loop Delay
		SysTick_delay_ms(LOOP_DELAY_MS);
	}
		
	// Return Value
	return 0;
}

/**
 * @brief ADC1/ADC2 IRQ Handler
 */
void ADC1_2_IRQHandler(void){
	// EOC Flag Set
	if(get_ADC_EOC_flag(adc_config.ADCx)){
		// Flag
		adc_conversion_complete = 0x01;
		// Clear the EOC Flag
		clear_ADC_EOC_flag(adc_config.ADCx);
	}
}
