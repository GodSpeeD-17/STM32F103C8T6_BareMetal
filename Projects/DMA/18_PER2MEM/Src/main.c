/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	GPIO_Config(&LED_Configuration);
	// Demo Test
	USART1_config();
	DMA_Load_Default_PER2MEM(&USART_DMA_Configuration);
	USART_DMA_Configuration.DMA_Channel = DMA1_Channel4;
	DMA_Config(&USART_DMA_Configuration);
	DMA_Transfer(DMA1_Channel4, (void*) &usart_buffer, (void*) &USART1->DR.REG, 1);
	// Infinite Loop
	while(1){
		GPIO_Toggle(&LED_Configuration);
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/
// DMA IRQ Handler
void DMA1_Channel4_IRQHandler(void){
	// DMA Transfer Complete
	if(DMA1->ISR.REG & DMA_ISR_TCIF4){
		// Toggle OB LED
		OB_LED_Toggle();
		// Disable the Channel
		DMA_CH_disable(DMA1_Channel4);
		// Clear the DMA Transfer Complete Interrupt Flag
		DMA1->IFCR.REG |= DMA_IFCR_CTCIF4;
	}
}
/*-------------------------------------------------------------------------------*/