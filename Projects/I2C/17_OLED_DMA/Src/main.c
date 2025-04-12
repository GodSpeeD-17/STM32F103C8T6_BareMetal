/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	DMA_CH_Config(DMA_I2C1_TX, &I2C1_TX_DMA_Configuration);
	DMA_CH_dataConfig(DMA_I2C1_TX, &I2C1_TX_DMA_Data_Configuration);
	DMA_CH_IRQ_Config(DMA_I2C1_TX, &I2C1_TX_DMA_IRQ_Configuration);
	DMA_CH_enable(DMA_I2C1_TX);
	// Infinite Loop
	while(1){
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/