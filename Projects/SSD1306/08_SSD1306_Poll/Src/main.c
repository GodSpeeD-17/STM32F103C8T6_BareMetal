/*-------------------------------------------------------------------------------*/
// Header Files
#include "main.h"
/*-------------------------------------------------------------------------------*/
// SSD1306 Configuration Structure
static ssd1306_config_t myOLED;
// SSD1306 Display Buffer
static uint8_t displayBuffer[SSD1306_PAGE][SSD1306_WIDTH];
// Frame Ring Buffer
static uint8_t frameBuffer[FRAME_BUFFER_SIZE];
// I2C Ring Buffer Status 
extern volatile uint8_t readFrameBuffer;
/*-------------------------------------------------------------------------------*/
// Main Entry Point
int main(void){

	// SSD1306 Parameters Configuration
	// SSD1306_Config_Disp(&myOLED, displayBuffer);
	// SSD1306_Config_RB(&myOLED, frameBuffer, FRAME_BUFFER_SIZE);
	// SSD1306_Load_I2C1(&myOLED);
	// SSD1306_I2C_Init(&myOLED);

	// // SSD1306 Display Initialization
	// if(SSD1306_Frame_RB_Disp_Init(&myOLED) != 0x01){
	// 	// Indication of Failure
	// 	OB_LED_Set();
	// 	// Return Error
	// 	return 1;
	// }
	

	// Infinite Loop
	while(1){
		// Read Frame Buffer
		// if(readFrameBuffer != 0x00){
		// 	// Check Data Availability
		// 	if(SSD1306_Frame_RB_Get_Filled_Space(&myOLED)){
		// 		// Process the Frame Buffer
		// 		SSD1306_Frame_RB_I2C_Dequeue(&myOLED);
		// 	}
		// 	// Reset
		// 	readFrameBuffer = 0x00;
		// }
		// On-board LED Toggle
		OB_LED_Toggle();
		// Delay
		delay_ms(LOOP_DELAY_MS);
	}
}

/*
int main(){

	__disable_irq(); // Disable Interrupts
	// Local Variables
	const uint16_t localI2CBuffSize = 0x100;
	uint8_t localI2CBuffer[localI2CBuffSize];
	uint16_t localI2CMaxIndex = 0x00;
	memset(localI2CBuffer, 0x00, localI2CBuffSize);
	__enable_irq(); // Enable Interrupts

	// SSD1306 Parameters Configuration
	SSD1306_Config_Disp(&myOLED, displayBuffer);
	SSD1306_Config_RB(&myOLED, frameBuffer, FRAME_BUFFER_SIZE);
	SSD1306_Load_I2C1(&myOLED);
	SSD1306_I2C_Init(&myOLED);
	
	// SSD1306 Display Initialization
	if(SSD1306_Frame_RB_Disp_Init(&myOLED) != 0x01){
		// Indication of Failure
		OB_LED_Set();
		// Return Error
		return 1;
	}

	readFrameBuffer = 0x01;

	// Infinite Loop
	while(1){
		// Buffer Space Read Time
		if(i2cRBStatus){
			// Buffer Value
			i2cRBStatus = Ring_Buffer_Available_Space(&myOLED.i2c_rb);
			// Buffer Data Present
			if(i2cRBStatus){
				// SSD1306 Frame Buffer Decode
				localI2CMaxIndex = SSD1306_RB_Decode_Frame(&myOLED, localI2CBuffer, localI2CBuffSize);
				// Occupy the I2C Bus
				SSD1306_I2C_Write(&myOLED, localI2CBuffer, localI2CMaxIndex);
				// Reset Status
				i2cRBStatus = 0x00;
			}
		}
		// On-board LED Toggle
		OB_LED_Toggle();
		// Loop Delay
		delay_ms(LOOP_DELAY_MS);
	}
	// Return Value
	return 0;
}
*/
/*-------------------------------------------------------------------------------*/