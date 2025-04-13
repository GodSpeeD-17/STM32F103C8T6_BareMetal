/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	#ifdef I2C_EXAMPLE
		DMA_CH_Config(DMA_I2C1_TX, &I2C1_TX_DMA_Channel_Configuration);
		DMA_CH_Data_Config(DMA_I2C1_TX, &I2C1_TX_DMA_Data_Configuration);
		DMA_CH_IRQ_Config(DMA_I2C1_TX, &I2C1_TX_DMA_IRQ_Configuration);
		DMA_CH_enable(DMA_I2C1_TX);
	#else
		// Set the Source Buffer to Some Value
		// memset(src_buffer, 0xAD, BUFFER_SIZE);
		// Set the Destination Buffer to Some Value
		// memset(dst_buffer, 0x00, BUFFER_SIZE);
		// DMA Configuration
		DMA_CH_Config(DMA1_Channel1, &mem2mem_config);
		DMA_CH_Data_Config(DMA1_Channel1, &mem2mem_data_config);
		DMA_CH_IRQ_Config(DMA1_Channel1, &mem2mem_irq_config);
		DMA_Transfer(DMA1_Channel1, src_buffer, dst_buffer, BUFFER_SIZE);
		// DMA_CH_enable(DMA1_Channel1);
	#endif

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