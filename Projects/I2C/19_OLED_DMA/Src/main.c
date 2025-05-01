/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// Time required for Display to Synchronize with data or commands
// @note - Try to keep between 100-150 us
// @note - Going below 100us is insufficient time for display to synchronize
// @note - Going beyond 150us creates I2C Bus Error
#define SSD1306_I2C_SYNC_DELAY_TIME_US			124

/**
 * @brief Used for Starting the transmission for I2C using DMA for SSD1306
 * @param[in] I2Cx I2C instance: `I2C1`, `I2C2`
 * @note Dependency on DMA 
 */
#define SSD1306_I2C_DMA_sendStart(I2Cx) 	\
{											\
	/* Wait for Bus to be free */ 			\
	while(!I2C_busReady((I2Cx))); 			\
	/* Send Start Condition */				\
	I2C_sendStart((I2Cx)); 					\
}

/**
 * @brief Used for Stoping the transmission for I2C using DMA for SSD1306
 * @param[in] I2Cx I2C instance: `I2C1`, `I2C2`
 * @note Dependency on DMA
 */
#define SSD1306_I2C_DMA_sendStop(I2Cx) 			\
{												\
	/* DMA Indicator for Transfer Complete */ 	\
	while(!dma_completed); 						\
	/* Wait for SSD1306 to synchronize */ 		\
	delay_us(SSD1306_I2C_SYNC_DELAY_TIME_US); 	\
	/* Send Stop Condition */					\
	I2C_sendStop((I2Cx)); 						\
	/* DMA Reset Status for Completion */		\
	dma_completed = 0x00;						\
}

/**
 * @brief Takes care of whole I2C with DMA sequence
 * @param[in] I2Cx I2C instance: `I2C1`, `I2C2`
 * @note Dependency on DMA 
 */
#define SSD1306_I2C_DMA_trigger(I2Cx)	\
{	/* Start I2C DMA Transfer */		\
	SSD1306_I2C_DMA_sendStart((I2Cx));	\
	/* Stop I2C DMA Transfer */			\
	SSD1306_I2C_DMA_sendStop((I2Cx));	\
}
/*-------------------------------------------------------------------------------*/

// I2C Status
static volatile uint8_t i2c_status = 0x00;
static volatile uint8_t dma_completed = 0x00;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){

	// Configure GPIO
	GPIO_Config(&LED_Configuration);
	// Reset GPIO
	GPIO_Reset(&LED_Configuration);

	// -----------------------------------------------------------------
	// SSD1306_I2Cx Configuration 
	// -----------------------------------------------------------------
	I2C1_Load_Default(&I2C_SSD1306_Configuration);
	I2C_Config(&I2C_SSD1306_Configuration);
	// Enable Interrupt
	I2C_IRQ_enable(SSD1306_I2Cx, (I2Cx_IRQ_EVENT | I2Cx_IRQ_ERROR));
	I2C_enable(SSD1306_I2Cx);

	// -----------------------------------------------------------------
	// DMA Configuration
	// -----------------------------------------------------------------
	DMA_Load_Default_MEM2PER(&DMA_SSD1306_Configuration);
	DMA_SSD1306_Configuration.DMA_Channel = DMA_I2C1_TX;
	DMA_Config(&DMA_SSD1306_Configuration);
	src_buffer[0] = SSD1306_CMD_INDICATOR;
	memcpy(src_buffer + 1, SSD1306_initCmd, sizeof(SSD1306_initCmd)/sizeof(SSD1306_initCmd[0]));
	DMA_Transfer_Config(DMA_I2C1_TX, src_buffer + 1, &SSD1306_I2Cx->DR.REG, (sizeof(SSD1306_initCmd)/sizeof(SSD1306_initCmd[0])));

	// Delay for allowing SSD1306 to Initialize
	delay_ms(LOOP_DELAY_MS);

	// -----------------------------------------------------------------
	// SSD1306 I2C Initialisation Setup Start
	// -----------------------------------------------------------------
		// SSD1306 I2C DMA Sequence
		SSD1306_I2C_DMA_trigger(SSD1306_I2Cx);
		// Toggle On-board LED
		OB_LED_Toggle();
	// -----------------------------------------------------------------
	// SSD1306 I2C Initialisation Setup End
	// -----------------------------------------------------------------

	src_buffer[0] = SSD1306_CMD_INDICATOR;
	src_buffer[1] = SSD1306_CMD_PAGE_MODE_SET_PAGE(0);
	src_buffer[2] = SSD1306_CMD_PAGE_MODE_SET_COL_LOWER_NIBBLE(0);
	src_buffer[3] = SSD1306_CMD_PAGE_MODE_SET_COL_UPPER_NIBBLE(0);
	DMA_Transfer_Config(DMA_I2C1_TX, src_buffer + 1, &SSD1306_I2Cx->DR.REG, 3);
	
	// -----------------------------------------------------------------
	// SSD1306 I2C Range Selection Start
	// -----------------------------------------------------------------
		// SSD1306 I2C DMA Sequence
		SSD1306_I2C_DMA_trigger(SSD1306_I2Cx);
		// Toggle On-board LED
		OB_LED_Toggle();
	// -----------------------------------------------------------------
	// SSD1306 I2C Range Selection End
	// -----------------------------------------------------------------

	src_buffer[0] = SSD1306_DATA_INDICATOR;
	memset(src_buffer + 1, 0xFF, BUFFER_SIZE);
	DMA_Transfer_Config(DMA_I2C1_TX, src_buffer + 1, &SSD1306_I2Cx->DR.REG, BUFFER_SIZE);
	
	// -----------------------------------------------------------------
	// SSD1306 I2C Column Data Start
	// -----------------------------------------------------------------
		// SSD1306 I2C DMA Sequence
		SSD1306_I2C_DMA_trigger(SSD1306_I2Cx);
		// Toggle On-board LED
		OB_LED_Toggle();
	// -----------------------------------------------------------------
	// SSD1306 I2C Column Data End
	// -----------------------------------------------------------------	

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