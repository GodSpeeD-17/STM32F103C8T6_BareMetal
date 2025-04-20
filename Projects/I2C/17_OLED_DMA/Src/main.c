/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// I2C Status
static volatile uint8_t i2c_status = 0x00;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){

	// Configure GPIO
	GPIO_Config(&LED_Configuration);
	// Reset GPIO
	GPIO_Reset(&LED_Configuration);

	// -----------------------------------------------------------------
	// I2C1 Configuration 
	// -----------------------------------------------------------------
	I2C1_Load_Default(&I2C_SSD1306_Configuration);
	I2C_Config(&I2C_SSD1306_Configuration);
	I2C_IRQ_enable(I2C1, I2Cx_IRQ_BUFFER_DISABLE, I2Cx_IRQ_ERROR_DISABLE);
	I2C_enable(I2C1);

	// -----------------------------------------------------------------
	// DMA Configuration
	// -----------------------------------------------------------------
	DMA_Load_Default_PER2MEM(&DMA_SSD1306_Configuration);
	DMA_SSD1306_Configuration.DMA_Channel = DMA_I2C1_TX;
	DMA_SSD1306_Configuration.data.srcInc = DMAx_INC_ENABLE;
	DMA_Config(&DMA_SSD1306_Configuration);
	src_buffer[0] = 0x00;
	memcpy(src_buffer + 1, SSD1306_initCmd, sizeof(SSD1306_initCmd)/sizeof(SSD1306_initCmd[0]));
	DMA_Transfer(DMA_I2C1_TX, src_buffer + 1, &I2C1->DR.REG, (sizeof(SSD1306_initCmd)/sizeof(SSD1306_initCmd[0])));

	// -----------------------------------------------------------------
	// I2C Setup
	// -----------------------------------------------------------------
	// Wait for Bus to be Ready
	while(!I2C_busReady(I2C1));
	// Send Start Condition
	I2C_sendStart(I2C1);

	// Wait for Bus to be Ready
	while(!I2C_busReady(I2C1));

	// -----------------------------------------------------------------
	// I2C Data Transmission
	// -----------------------------------------------------------------
	src_buffer[0] = 0x40;
	memset(src_buffer + 1, 0xFF, BUFFER_SIZE);
	DMA_Transfer(DMA_I2C1_TX, src_buffer + 1, &I2C1->DR.REG, BUFFER_SIZE);
	
	// Send Start Condition
	I2C_sendStart(I2C1);

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


// void I2C1_EV_IRQHandler(void){
// 	// 
// 	switch(i2c_status){

// 		case 0x00:
// 			if(I2C1->SR1.REG & I2C_SR1_SB){
// 				I2C1->DR.REG = ((0x3C << 1) | I2Cx_WRITE);
// 				i2c_status = 0x01;
// 			}
// 			break;
		
// 		case 0x01:
// 			if(I2C1->SR1.REG & I2C_SR1_ADDR){
// 				uint32_t temp = I2C1->SR2.REG;
// 				I2C1->CR2.REG |= I2C_CR2_DMAEN;
// 				DMA_I2C1_TX->CCR.REG |= DMA_CCR_EN;
// 				I2C1->DR.REG = src_buffer[0];
// 				i2c_status = 0x02;
// 			}
// 		break;
// 	}
// }

// void DMA1_Channel6_IRQHandler(void){
// 	// DMA Transfer Complete
// 	if(DMA1->ISR.REG & DMA_ISR_TCIF6){
// 		I2C1->CR2.REG &= ~I2C_CR2_DMAEN;
// 		I2C1->CR1.REG |= I2C_CR1_STOP;
// 		DMA_I2C1_TX->CCR.REG &= ~DMA_CCR_EN;
// 		OB_LED_Toggle();
// 		DMA1->IFCR.REG |= DMA_IFCR_CTCIF6;
// 		i2c_status = 0x00;
// 	}
// }

/*-------------------------------------------------------------------------------*/
// I2C IRQ Handler
// /*

void I2C1_EV_IRQHandler(void){
	// State Machine
	switch(i2c_status){

		// Initial Status
		case 0x00:
			// Start Bit Sent
			if(I2C1->SR1.REG & I2C_SR1_SB){
				// Clear SB by sending Address for Write
				I2C_writeAddress(I2C1, 0x3C);
				// Update State Machine
				i2c_status = 0x01;
			}
			// Error Condition
			else
				i2c_status = 0xFF;
		break;

		// Address Match
		case 0x01:
			// Address Match
			if(I2C1->SR1.REG & I2C_SR1_ADDR){
				// Clear ADDR
				uint32_t temp_reg = I2C1->SR2.REG;
				// Enable I2C DMA Transfer
				I2C_DMA_enable(I2C1);
				// Update State Machine
				i2c_status = 0x02;
			}
			// Error Condition
			else
				i2c_status = 0xFE;
		break;

		// STOP
		case 0x03:
			// Byte Transfer Completed
			if(I2C1->SR1.REG & I2C_SR1_BTF){
				// 
				I2C_sendStop(I2C1);
				// Indication
				OB_LED_Toggle();
				// Bus Free
				if(I2C_busReady(I2C1)){
					// Reset State Machine
					i2c_status = 0x00;
				}
			}
		break;
		// Unaccounted States
		default:
		break;
	}
}
// */
/*-------------------------------------------------------------------------------*/
// DMA IRQ Handler
// /*
void DMA1_Channel6_IRQHandler(void){
	// DMA Transfer Complete
	if(DMA1->ISR.REG & DMA_ISR_TCIF6){
		// Disable the Channel
		DMA_CH_disable(DMA_I2C1_TX);
		// Disable I2C DMA
		I2C_DMA_disable(I2C1);
		// Sent Stop Condition
		I2C_sendStop(I2C1);
		// Update State Machine
		i2c_status = 0x03;
		// Bus Free
		if(I2C_busReady(I2C1)){
			// Indication
			OB_LED_Toggle();
			// Reset
			i2c_status = 0x00;
		}
		// Clear the DMA Transfer Complete Interrupt Flag
		DMA1->IFCR.REG |= DMA_IFCR_CTCIF6;
	}
}
// */
/*-------------------------------------------------------------------------------*/
/**
 * @brief Error Protection
 */
void I2C1_ER_IRQHandler(void){
	// Arbitration Lost Flag
	if(I2C1->SR1.REG & I2C_SR1_AF) {
		// Clear NACK flag
		I2C1->SR1.REG &= ~I2C_SR1_AF;
		// Force stop
		I2C1->CR1.REG |= I2C_CR1_STOP;
		// Reset state machine
		i2c_status = 0x00;
	}
}
/*-------------------------------------------------------------------------------*/