/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// I2C SCL GPIO Config
extern gpio_config_t I2C2_SCL;
extern gpio_config_t I2C2_SDA;
// I2C Configuration Structure
i2c_config_t I2C_Config = {
	.I2Cx = I2C2,
	.SCL = &I2C2_SCL,
	.SDA = &I2C2_SDA,
	.mode = I2Cx_MODE_STD,
	.duty = I2Cx_DUTY_NORMAL,
};
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// Local Variable
	uint32_t event = 0;
	// I2C Initialisation
	I2C_Config.freq_MHz = (APB1Clock/FREQ_1MHz);
	I2C_Config.TRISE = I2C_calc_TRISE(I2C_Config.mode);
	I2C_Config.CCR = I2C_calc_CCR(I2C_Config.mode, I2C_Config.duty, I2C_Config.freq_MHz);
	I2C_config(&I2C_Config);
	I2C_enable(I2C_Config.I2Cx);
	
	// Wait for Bus
	while(!(I2C_busReady(I2C_Config.I2Cx)));
	
	// Start Sequence
	I2C_sendStart(I2C_Config.I2Cx);
	while((event = I2C_checkEvent(I2C_Config.I2Cx)) != I2Cx_EV_MST_START);
	
	// Address Sequence
	if(I2C_writeAddress(I2C_Config.I2Cx, MAX30102_ADDRESS)){
		// Send Register Address
		I2C_writeDR(I2C_Config.I2Cx, MAX30102_TEMP_INT);
		// Send Stop
		I2C_sendStop(I2C_Config.I2Cx);
	}

	// Infinite Loop
	while(1){
		// Toggle
		toggle_OB_LED();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/