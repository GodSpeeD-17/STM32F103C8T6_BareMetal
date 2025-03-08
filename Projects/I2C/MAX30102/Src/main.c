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
	uint8_t partID = 0;
	// !! Very Important, DO NOT COMMENT THIS LINE !!
	uint32_t temp = 0;

	// I2C Initialisation
	I2C_Config.freq_MHz = (APB1Clock/FREQ_1MHz);
	I2C_Config.TRISE = I2C_calc_TRISE(I2C_Config.mode);
	I2C_Config.CCR = I2C_calc_CCR(I2C_Config.mode, I2C_Config.duty, I2C_Config.freq_MHz);
	I2C_config(&I2C_Config);
	I2C_enable(I2C_Config.I2Cx);
	
	// Wait for Bus to be Ready
	while (I2C_Config.I2Cx->SR2.REG & I2C_SR2_BUSY);
	
	// Start Sequence (Write Mode)
	I2C_sendStart(I2C_Config.I2Cx);
	while (!(I2C_Config.I2Cx->SR1.REG & I2C_SR1_SB)); // Wait for START condition (EV5)
	
	// Send Slave Address with Write Bit
	I2C_writeAddress(I2C_Config.I2Cx, MAX30102_ADDRESS);
	while(!(I2C_Config.I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2C_Config.I2Cx->SR1.REG; // Clearing ADDR Flag
	temp = I2C_Config.I2Cx->SR2.REG; // Clears ADDR Flag
	while(!(I2C_Config.I2Cx->SR1.REG & I2C_SR1_TXE));
	
	// Send Register Address (Temperature Integer Register)
	I2C_writeByte(I2C_Config.I2Cx, MAX30102_PART_ID);
	while (!(I2C_Config.I2Cx->SR1.REG & (I2C_SR1_TXE | I2C_SR1_BTF))); // Wait for TXE flag & BTF flag (EV8_1, EV8_2)

	// Repeated START Condition (Switch to Read Mode)
	I2C_sendStart(I2C_Config.I2Cx);
	while (!(I2C_Config.I2Cx->SR1.REG & I2C_SR1_SB)); // Wait for START condition (EV5)
	
	// Send Slave Address with Read Bit
	I2C_readAddress(I2C_Config.I2Cx, MAX30102_ADDRESS);
	while(!(I2C_Config.I2Cx->SR1.REG & I2C_SR1_ADDR));
	temp = I2C_Config.I2Cx->SR1.REG; // Clearing ADDR Flag
	temp = I2C_Config.I2Cx->SR2.REG; // Clears ADDR Flag
	while (!(I2C_Config.I2Cx->SR1.REG & I2C_SR1_RXNE));

	// Read Temperature Integer Value
	partID = I2C_readByte(I2C_Config.I2Cx); // Read data from DR register

	// Generate STOP condition
	I2C_sendStop(I2C_Config.I2Cx);
	while (I2C_Config.I2Cx->SR2.REG & I2C_SR2_BUSY); // Wait until BUSY flag is cleared

	// Infinite Loop
	while(1){
		// LED toggle based upon partID value
		for(uint8_t i = 0; i < partID; i++){
			// Toggle
			toggle_OB_LED();
			// Toggle Delay
			delay_ms((LOOP_DELAY_MS / 100) * 3);
		}
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/