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
	// Default DMA Configuration
	DMA_Load_Default_MEM2MEM(&DMA_Configuration);

	#ifdef BIT_SIZE_8
		DMA_Configuration.data.srcDataSize = DMAx_DATA_SIZE_BIT_8;
		DMA_Configuration.data.dstDataSize = DMAx_DATA_SIZE_BIT_8;
	#endif

	// DMA Configuration
	DMA_Config(&DMA_Configuration);
	// Configure DMA Transfer
	DMA_Transfer(DMA1_Channel1, src_buffer, dst_buffer, BUFFER_SIZE);
	// Enable DMA Channel
	DMA_CH_enable(DMA1_Channel1);
	
	// Infinite Loop
	while(1){
		// Toggle GPIO
		GPIO_Toggle(&LED_Configuration);
		// Delay
		delay_ms(LOOP_DELAY_MS);
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
		// Disable the Channel
		DMA_CH_disable(DMA1_Channel1);
		// Clear the DMA Transfer Complete Interrupt Flag
		DMA1->IFCR.REG |= DMA_IFCR_CTCIF1;
	}
}
/*-------------------------------------------------------------------------------*/