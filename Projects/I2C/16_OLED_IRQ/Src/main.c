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
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Initialisation
	I2C1_loadDefault(&SSD1306_I2C_Config);
	SSD1306_I2C_Config.buffer_IRQ = I2Cx_BUFFER_IRQ_ENABLE;
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
		// Toggle on-board LED
		OB_LED_toggle();
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
	// Local Variables
	uint32_t status = SSD1306_I2Cx->CR1.REG;
	// uint32_t CR2 = SSD1306_I2Cx->CR2.REG;
	// Start bit
	if(status & I2C_CR1_START){
		// Clear Start bit
		// SSD1306_I2Cx->CR1.REG &= ~I2C_CR1_START;
		I2C_writeByte(SSD1306_I2Cx, SSD1306_I2C_ADDRESS);
		// LED ON
		GPIO_set(&LED_Config);
	}
	// Address
	if (status & I2C_SR1_ADDR) {
        // Clear Address Flag
        uint32_t temp = (SSD1306_I2Cx->SR1.REG | SSD1306_I2Cx->SR2.REG);
		// 
		I2C_sendStop(SSD1306_I2Cx);
    } 

}
