/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// SSD 1306 Configuration Structure
i2c_config_t SSD1306_I2C_Config;
// LED Configuration
gpio_config_t LED_Config = {
	.GPIOx = GPIOA,
	.PINx = GPIO_PIN_2,
	.MODEx = MODE_OUT_10MHz,
	.CNFx = CNF_OUT_GP_PP
};
// LED Status
uint8_t led_status[2] = {0x00};
uint32_t temp = 0x00;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	I2C1_loadDefault(&SSD1306_I2C_Config);
	SSD1306_I2C_Config.buffer_IRQ = I2Cx_BUFFER_IRQ_DISABLE;
	SSD1306_I2C_Config.event_IRQ = I2Cx_EVENT_IRQ_ENABLE;
	// Configure I2C
	I2C_config(&SSD1306_I2C_Config);
	// Enable I2C
	I2C_enable(SSD1306_I2Cx);
	// Configure external LED
	GPIO_config(&LED_Config);
	// I2C Send Address
	I2C_sendStart(SSD1306_I2Cx);
	// Infinite Loop
	while(1){
		// ISR Executed
		if(led_status[1] != led_status[0]){
			// Toggle on-board LED
			OB_LED_toggle();
			led_status[1] = led_status[0];
		}
		// Toggle LED
		GPIO_toggle(&LED_Config);
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
void I2C1_EV_IRQHandler(void){
	// Start bit
	if(SSD1306_I2Cx->SR1.REG & I2C_SR1_SB){
		// SSD1306 I2C Address with Write Privilege
		SSD1306_I2Cx->DR.REG = SSD1306_I2C_ADDRESS << 1;
		// Update the LED status
		led_status[0] = 0x01;
		// Stop Interrupt
		SSD1306_I2Cx->CR2.REG &= ~(I2C_CR2_ITEVTEN);
	}
	// Address Sent
	// else if(SSD1306_I2Cx->SR1.REG & I2C_SR1_ADDR){
	// 	// Clear ADDR Bit
	// 	temp = SSD1306_I2Cx->SR1.REG;
	// 	temp = SSD1306_I2Cx->SR2.REG;
	// 	// SSD1306 I2C Data
	// 	SSD1306_I2Cx->DR.REG = SSD1306_CMD_DISP_OFF;
	// 	// Update the LED status
	// 	led_status[0] = 0x00;
	// }
	// // Byte Transfer Finish
	// else if(SSD1306_I2Cx->SR1.REG & I2C_SR1_BTF){
	// 	// SSD1306 I2C Stop
	// 	I2C_sendStop(SSD1306_I2Cx);
	// }

}
