/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	

	// Configure GPIO
	GPIO_Config(&LED_Configuration);
	// Reset GPIO
	GPIO_Reset(&LED_Configuration);

	// Enable DMA Transfer
	DMA_CH_enable(DMA1_Channel1);

	// Infinite Loop
	while(1){
		// Toggle GPIO
		GPIO_Toggle(&LED_Configuration);
c		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/
// DMA IRQ Handler
void DMA1_Channel1_IRQHandler(void){
	// DMA Transfer Complete
	if(DMA1->ISR.REG & DMA_ISR_TCIF1){
		// Toggle OB LED
		OB_LED_Toggle();
		// Clear the DMA Transfer Complete Interrupt Flag
		DMA1->IFCR.REG |= DMA_IFCR_CTCIF1;
	}
}

/*-------------------------------------------------------------------------------*/