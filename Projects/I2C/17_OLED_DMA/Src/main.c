/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// I2C Status
static volatile uint8_t i2c_status = 0x00;
static volatile uint8_t dma_completed = 0x00;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){

	// Delay for allowing SSD1306 to load
	delay_ms(2 * 1000);

	// Configure GPIO
	GPIO_Config(&LED_Configuration);
	// Reset GPIO
	GPIO_Reset(&LED_Configuration);

	// -----------------------------------------------------------------
	// SSD1306_I2Cx Configuration 
	// -----------------------------------------------------------------
	I2C1_Load_Default(&I2C_SSD1306_Configuration);
	I2C_Config(&I2C_SSD1306_Configuration);
	I2C_IRQ_enable(SSD1306_I2Cx, I2Cx_IRQ_BUFFER_DISABLE, I2Cx_IRQ_ERROR_ENABLE);
	I2C_enable(SSD1306_I2Cx);

	// -----------------------------------------------------------------
	// DMA Configuration
	// -----------------------------------------------------------------
	DMA_Load_Default_MEM2PER(&DMA_SSD1306_Configuration);
	DMA_SSD1306_Configuration.DMA_Channel = DMA_I2C1_TX;
	DMA_Config(&DMA_SSD1306_Configuration);
	src_buffer[0] = SSD1306_CMD_INDICATOR;
	memcpy(src_buffer + 1, SSD1306_initCmd, sizeof(SSD1306_initCmd)/sizeof(SSD1306_initCmd[0]));
	DMA_Transfer(DMA_I2C1_TX, src_buffer + 1, &SSD1306_I2Cx->DR.REG, (sizeof(SSD1306_initCmd)/sizeof(SSD1306_initCmd[0])));

	// -----------------------------------------------------------------
	// SSD1306 I2C Initialisation Setup
	// -----------------------------------------------------------------
	// Wait for Bus to be Ready
	while(!I2C_busReady(SSD1306_I2Cx));
	// Send Start Condition
	I2C_sendStart(SSD1306_I2Cx);
	// I2C Sequence Complete
	while(!dma_completed);
	delay_us(124);
	// Send I2C STOP
	I2C_sendStop(SSD1306_I2Cx);
	dma_completed = 0x00;
	// Toggle On-board LED
	OB_LED_Toggle();

	src_buffer[0] = SSD1306_CMD_INDICATOR;
	src_buffer[1] = SSD1306_CMD_PAGE_MODE_SET_PAGE(2);
	src_buffer[2] = SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(0);
	src_buffer[3] = SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(0);
	DMA_Transfer(DMA_I2C1_TX, src_buffer + 1, &SSD1306_I2Cx->DR.REG, 3);
	
	// -----------------------------------------------------------------
	// SSD1306 I2C Range Selection	
	// -----------------------------------------------------------------
	// I2C Sequence Complete
	while(!I2C_busReady(SSD1306_I2Cx));
	// Send Start Condition
	I2C_sendStart(SSD1306_I2Cx);
	// I2C Sequence Complete
	while(!dma_completed);
	delay_us(124);
	// Send I2C STOP
	I2C_sendStop(SSD1306_I2Cx);
	dma_completed = 0x00;
	// Toggle On-board LED
	OB_LED_Toggle();

	// -----------------------------------------------------------------
	// SSD1306 I2C Column Data 	
	// -----------------------------------------------------------------
	src_buffer[0] = SSD1306_DATA_INDICATOR;
	memset(src_buffer + 1, 0xFF, BUFFER_SIZE);
	DMA_Transfer(DMA_I2C1_TX, src_buffer + 1, &SSD1306_I2Cx->DR.REG, BUFFER_SIZE);

	// Wait for Bus to be Ready
	while(!I2C_busReady(SSD1306_I2Cx));
	// Send Start Condition
	I2C_sendStart(SSD1306_I2Cx);
	// I2C Sequence Complete
	while(!dma_completed);
	delay_us(124);
	// Send I2C STOP
	I2C_sendStop(SSD1306_I2Cx);
	dma_completed = 0x00;
	// Toggle On-board LED
	OB_LED_Toggle();

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
void I2C1_EV_IRQHandler(void){
	// I2C Status
	switch(i2c_status){
		// Start Bit Sent
		case 0x00:
			if(SSD1306_I2Cx->SR1.REG & I2C_SR1_SB){
				SSD1306_I2Cx->DR.REG = ((SSD1306_I2C_ADDRESS << 1) | I2Cx_WRITE);
				i2c_status = 0x01;
			}
			break;
		
		// Address Sent
		case 0x01:
			if(SSD1306_I2Cx->SR1.REG & I2C_SR1_ADDR){
				volatile uint32_t temp = SSD1306_I2Cx->SR1.REG;
				temp = SSD1306_I2Cx->SR2.REG;
				// Now TxE is ready
				if (SSD1306_I2Cx->SR1.REG & I2C_SR1_TXE) {
					SSD1306_I2Cx->DR.REG = src_buffer[0];
					i2c_status = 0x02;
				}
			}
		break;

		// Enable DMA
		case 0x02:
			if(SSD1306_I2Cx->SR1.REG & I2C_SR1_BTF){
				SSD1306_I2Cx->CR2.REG |= I2C_CR2_DMAEN;
				DMA_I2C1_TX->CCR.REG |= DMA_CCR_EN;
				i2c_status = 0x03;
			}
		break;
	}
}
/*-------------------------------------------------------------------------------*/
void DMA1_Channel6_IRQHandler(void){
	// DMA Half Transfer Interrupt
	if(DMA1->ISR.REG & DMA_ISR_HTIF6){
		// Clear Flag
		DMA1->IFCR.REG |= DMA_IFCR_CHTIF6;
	} 

	// DMA Transfer Complete
	if(DMA1->ISR.REG & DMA_ISR_TCIF6){
		// Disable DMA for I2C
		SSD1306_I2Cx->CR2.REG &= ~I2C_CR2_DMAEN;
		// Disable DMA Channel
		DMA_I2C1_TX->CCR.REG &= ~DMA_CCR_EN;
		// Update Status
		i2c_status = 0x00;
		dma_completed = 0x01;
		// Acknowledge the Interrupt
		DMA1->IFCR.REG |= DMA_IFCR_CTCIF6;
	}
}
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
/**
 * @brief Error Protection
 */
void I2C1_ER_IRQHandler(void){
	// Arbitration Lost Flag
	if(SSD1306_I2Cx->SR1.REG & I2C_SR1_AF) {
		// Clear NACK flag
		SSD1306_I2Cx->SR1.REG &= ~I2C_SR1_AF;
		// Force stop
		SSD1306_I2Cx->CR1.REG |= I2C_CR1_STOP;
		// Reset state machine
		i2c_status = 0x00;
	}
}
/*-------------------------------------------------------------------------------*/