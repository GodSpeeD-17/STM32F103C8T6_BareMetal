/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// I2C Initialisation
	I2C_Config.freq_MHz = (APB1Clock/FREQ_1MHz);
	I2C_Config.TRISE = I2C_calc_TRISE(I2C_Config.mode);
	I2C_Config.CCR = I2C_calc_CCR(I2C_Config.mode, I2C_Config.duty, I2C_Config.freq_MHz);
	I2C_config(&I2C_Config);
	I2C_enable(I2C_Config.I2Cx);
	// START
	do{
		// Wait for Bus
		while(!(I2C_busReady(I2C_Config.I2Cx)));
		// Send Start
		while(!(I2C_sendStart(I2C_Config.I2Cx)));
		// Small Delay
		// delay_ms(50);
	} while(!(I2C_readAddress(I2C_Config.I2Cx, MAX30102_ADDRESS)));
	
	// Send Register Address
	I2C_sendByte(I2C_Config.I2Cx, MAX30102_TEMP_INT);
	// Send Stop
	I2C_sendStop(I2C_Config.I2Cx);

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