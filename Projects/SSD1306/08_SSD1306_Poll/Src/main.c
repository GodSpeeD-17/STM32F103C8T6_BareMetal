/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// SSD1306 Configuration Structure
static ssd1306_config_t myOLED;
// SSD1306 Display Buffer
static uint8_t displayBuffer[SSD1306_PAGE][SSD1306_WIDTH];
// I2C Ring Buffer
static uint8_t i2cBuffer[I2C_BUFFER_SIZE];
// SysTick Callback Function
void SysTick_Callback_Fn(void);
// Counter (us)
static uint64_t tickCountUs = 0x00;
// I2C Ring Buffer Status
static uint8_t i2cRBStatus = 0x00;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(){
	// SSD1306 Parameters Configuration
	SSD1306_Config_Disp(&myOLED, displayBuffer);
	SSD1306_Config_RB(&myOLED, i2cBuffer, I2C_BUFFER_SIZE);
	SSD1306_Config_I2C1_Load_Default(&myOLED);

	// SSD1306 I2C Configure
	SSD1306_Config_I2C(&myOLED);
	SSD1306_Config_I2C_Enable(&myOLED);

	// Register SysTick Callback Function
	SysTick_Register_Callback(SysTick_Callback_Fn);

	// SSD1306 Display Initialization
	if(SSD1306_Frame_RB_Disp_Reset(&myOLED) == 0x00){
		// Indication of Failure
		OB_LED_Set();
		// Infinite Loop
		while(1);
	}
	// SSD1306 Display Alternate Pattern
	SSD1306_Frame_RB_Set_Disp_Pattern(&myOLED, SSD1306_PATTERN_ALTERNATE);

	// Infinite Loop
	while(1){
		// I2C Buffer Data Present
		if(i2cRBStatus){
			SSD1306_Frame_RB_I2C_Dequeue(&myOLED);
			i2cRBStatus = 0x00;
		}
		// On-board LED Toggle
		OB_LED_Toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
/*-------------------------------------------------------------------------------*/
// SysTick Callback Function
void SysTick_Callback_Fn(void){
	// Increment Tick Count
	if((tickCountUs++) > 0x0FFFFFFF){
		tickCountUs = 0x00;
	}
	// Check if new data is available
	if(tickCountUs & 0x3FFF){
		i2cRBStatus = Ring_Buffer_Available_Space(&myOLED.i2c_rb);
	}
}
/*-------------------------------------------------------------------------------*/