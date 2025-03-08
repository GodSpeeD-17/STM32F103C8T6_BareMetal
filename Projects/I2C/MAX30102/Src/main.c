/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// I2C SCL GPIO Config
extern gpio_config_t I2C1_SCL;
extern gpio_config_t I2C1_SDA;
// I2C Configuration Structure
i2c_config_t I2C_Config = {
	.I2Cx = I2C1,
	.SCL = &I2C1_SCL,
	.SDA = &I2C1_SDA,
	.mode = I2Cx_MODE_STD,
	.duty = I2Cx_DUTY_NORMAL,
};
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Local Variable
	uint8_t partID = 0, revID = 0, data = 0x00;

	// I2C Initialisation
	I2C_Config.freq_MHz = (APB1Clock/FREQ_1MHz);
	I2C_Config.TRISE = I2C_calc_TRISE(I2C_Config.mode);
	I2C_Config.CCR = I2C_calc_CCR(I2C_Config.mode, I2C_Config.duty, I2C_Config.freq_MHz);
	I2C_config(&I2C_Config);
	I2C_enable(I2C_Config.I2Cx);
	
	// Wait for Bus to be Ready
	while(I2C_Config.I2Cx->SR2.REG & I2C_SR2_BUSY);

	// Write
	MAX30102_writeByteAtAddress(I2C_Config.I2Cx, MAX30102_TEMP_CONFIG, MAX30102_TEMP_CONFIG_TEMP_EN);
	data = MAX30102_readByteFromAddress(I2C_Config.I2Cx, MAX30102_TEMP_CONFIG);

	// Demo Function Test
	revID = MAX30102_readByteFromAddress(I2C_Config.I2Cx, MAX30102_REV_ID);
	partID = MAX30102_readByteFromAddress(I2C_Config.I2Cx, MAX30102_PART_ID);
	// Infinite Loop
	while(1){
		// LED toggle based upon partID value
		for(uint8_t i = 0; i < partID; i++){
			// Toggle
			toggle_OB_LED();
			// Toggle Delay
			delay_ms((LOOP_DELAY_MS/100) * 5);
		}
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/