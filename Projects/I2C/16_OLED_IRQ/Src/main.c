/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// SSD 1306 Configuration Structure
i2c_config_t SSD1306_I2C_Config;
/*-------------------------------------------------------------------------------*/
// LED Configuration
gpio_config_t LED_Config = {
	.GPIO = GPIOA,
	.PIN = GPIOx_PIN_2,
	.MODE = GPIOx_MODE_OUT_10MHz,
	.CNF = GPIOx_CNF_OUT_GP_PP
};
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){

	// Configure external LED
	GPIO_Config(&LED_Config);

	// I2C Initialisation
	I2C1_Load_Default(&SSD1306_I2C_Config);
	// Configure I2C
	I2C_Config(&SSD1306_I2C_Config);
	// Enable Interrupt
	I2C_IRQ_enable(SSD1306_I2Cx, I2Cx_IRQ_ALL);
	// Enable I2C
	I2C_enable(SSD1306_I2Cx);
	
	// Initialize the SSD1306 Display
	SSD1306_IRQ_Init(SSD1306_I2Cx);				  

	// Infinite Loop
	while(1){
		// Toggle Screen Color
		SSD1306_IRQ_clrScreen(SSD1306_I2Cx, GPIO_Get(&LED_Config)? 0xFF: 0x00);
		// Toggle LED
		GPIO_Toggle(&LED_Config);
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/
/**
 * @brief I2C1 Event Handler
 */
static void I2C1_EV_IRQHandler(void){
	// Switch Case Based upon Scenario
	switch(SSD1306_I2C_status){
		// Ready State
		case I2C_STATE_READY:
			// Success
			if(SSD1306_I2Cx->SR1.REG & I2C_SR1_SB){
				// Send Address
				SSD1306_I2Cx->DR.REG = ((SSD1306_I2C_ADDRESS << 1) | I2Cx_WRITE);
				// SSD1306 I2C Address Written
				SSD1306_I2C_status = I2C_STATE_ADDR_SENT;
			}
		break;

		// I2C Address Sent 
		case I2C_STATE_ADDR_SENT:
			// Slave Acknowledged
			if(SSD1306_I2Cx->SR1.REG & I2C_SR1_ADDR){
				// Clear ADDR
				temp_data = SSD1306_I2Cx->SR2.REG;
				// SSD1306 I2C Address Written
				SSD1306_I2C_status = I2C_STATE_ADDR_CLEARED;
			}
		break;
		
		// Sending First Byte 
		case I2C_STATE_ADDR_CLEARED:
			// Indicator Sent 
			SSD1306_I2Cx->DR.REG = SSD1306_I2C_buffer[SSD1306_buff_curr_index];
			// Update Index
			SSD1306_buff_curr_index = ((SSD1306_buff_curr_index + 1) & (BUFFER_SIZE - 1));
			// Data Burst
			SSD1306_I2C_status = I2C_STATE_SENDING;
		break;

		// Send remaining Data
		case I2C_STATE_SENDING:
			// Transmission Buffer Empty (Data Shifted to Shift Register)
			if(SSD1306_I2Cx->SR1.REG & I2C_SR1_TXE){
				// All Bytes Sent
				if(SSD1306_buff_curr_index == SSD1306_buff_last_index){
					// Stop Indication
					SSD1306_I2Cx->CR1.REG |= I2C_CR1_STOP;
					// Ready for Next Transmission
					SSD1306_I2C_status = I2C_STATE_READY;
					// << Demo Indication >>
					// OB_LED_Toggle();
				}
				// Transfer the remaining Bytes
				else{
					// Bytes Send 
					SSD1306_I2Cx->DR.REG = SSD1306_I2C_buffer[SSD1306_buff_curr_index];
					// Update Index
					SSD1306_buff_curr_index = ((SSD1306_buff_curr_index + 1) & (BUFFER_SIZE - 1));
				}
			}
		break;
	}
}

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
		SSD1306_I2C_status = I2C_STATE_READY;
	}
}

