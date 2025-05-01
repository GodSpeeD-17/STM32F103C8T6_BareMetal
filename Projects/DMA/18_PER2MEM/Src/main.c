/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/

uint8_t addr_sent = 0x00;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	GPIO_Config(&LED_Configuration);
	
	// I2C Config Test
	I2C1_Load_Default(&I2C_Configuration);
	I2C_Config(&I2C_Configuration);
	I2C_DMA_enable(I2C1);
	I2C_enable(I2C1);

	// Demo Test
	DMA_Load_Default_PER2MEM(&I2C_DMA_Configuration);
	I2C_DMA_Configuration.DMA_Channel = DMA_I2C1_TX;
	DMA_Config(&I2C_DMA_Configuration);
	DMA_Transfer_Config(DMA_I2C1_TX, (void*) &i2c_buffer, (void*) &I2C1->DR.REG, 1);
	DMA_CH_enable(DMA_I2C1_TX);

	// Try
	uint32_t temp = 0x00;
	I2C_sendStart(I2C1);
	while(!(I2C1->SR1.REG & I2C_SR1_SB));
	I2C_writeAddress(I2C1, 0x3C);
	while(!(I2C1->SR1.REG & I2C_SR1_ADDR));
	temp = I2C1->SR1.REG;
	temp = I2C1->SR2.REG;
	// TxE
	while(!addr_sent);

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
void DMA1_Channel6_IRQHandler(void){
	// DMA Transfer Complete
	if(DMA1->ISR.REG & DMA_ISR_TCIF6){
		// Toggle OB LED
		OB_LED_Toggle();
		// Addr Sent
		addr_sent = 0x01;
		// Disable the Channel
		DMA_CH_disable(DMA_I2C1_TX);
		// Clear the DMA Transfer Complete Interrupt Flag
		DMA1->IFCR.REG |= DMA_IFCR_CTCIF6;
	}
}
/*-------------------------------------------------------------------------------*/