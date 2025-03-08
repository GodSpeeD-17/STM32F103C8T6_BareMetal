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
	// I2C Initialisation
	I2C_Config.freq_MHz = (APB1Clock/FREQ_1MHz);
	I2C_Config.TRISE = I2C_calc_TRISE(I2C_Config.mode);
	I2C_Config.CCR = I2C_calc_CCR(I2C_Config.mode, I2C_Config.duty, I2C_Config.freq_MHz);
	I2C_config(&I2C_Config);
	I2C_enable(I2C_Config.I2Cx);
	
	// Wait for Bus to be Ready
	while(!(I2C_busReady(I2C_Config.I2Cx)));


	// Infinite Loop
	while(1){
		// LED toggle based upon partID value
		
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/