// Main Header File
#include "systick.h"
#include "gpio.h"

// Delay Variable for microseconds
static volatile uint32_t futureTicksUs = 0x00;
// Tick Counter for microseconds
static volatile uint32_t tickCountUs = 0x00;
// Tick Counter for milliseconds
static volatile uint32_t tickCountMs = 0x00;
// I2C Ring Buffer Status 
volatile uint8_t i2cRBStatus = 0x00;
volatile uint8_t readFrameBuffer = 0x00;

/**
 * @brief Returns the current number of ticks
 * @note The ticks are dependent on Core Clock Frequency
 */
uint32_t SysTick_Get_Ticks(void){
	// Return final Value
	return tickCountUs;
}

/**
 * @brief Sets the current number of ticks
 * @param tick_value The number of ticks to be set
 * @note The ticks are dependent on Core Clock Frequency
 */
void SysTick_Set_Ticks(uint32_t tick_value){
	// Set the Current number of Ticks as `tick_value`
	tickCountUs = tick_value;
	// SysTick Disable
	SysTick_Disable();
	// Update the SysTick Current Value Register (24-bit)
	SysTick->VAL = SYSTICK_WRAP_VAL(tick_value - 1);
	// SysTick Enable
	SysTick_Enable();
}

/**
 * @brief Configures the SysTick Timer based upon the input count value
 * @param reloadValue Number of Ticks
 * @note - Value should be within the range of 24-bit unsigned integer
 * @note - Call `SysTick_Enable()` to start the SysTick Timer
 */
void SysTick_Config(uint32_t reloadValue){
	// Reset Value
	SysTick->CTRL.REG = 0x00;
	// Reload Value (24-bit)
	SysTick->LOAD = SYSTICK_WRAP_VAL(reloadValue - 1);
	// Update Current Value
	SysTick->VAL = 0x00;
	// Set Core as Reference Clock
	SysTick->CTRL.REG = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk);
}

/**
 * @brief Accurate us delay generation
 * @param delayTime Delay in microseconds (us)
 * @note Based upon SysTick Timer
 */
void delay_us(uint32_t delayTime){
	// Calculate the delay time
	futureTicksUs = tickCountUs + delayTime;
	// Wait for delay
	while(tickCountUs <= futureTicksUs);
}

/**
 * @brief Accurate ms delay generation
 * @param delayTime Delay in milliseconds (ms)
 * @note Based upon SysTick Timer
 */
void delay_ms(uint32_t delayTime){
	// Calculate the delay time
	while(delayTime--){
		// Wait for 1ms
		delay_us(1000);
	}
}

/**
 * @brief ISR for SysTick
 * @note Used for Delay Generation and Getting the total Number of Ticks
 */
void SysTick_Handler(void){

	/*********************************************** DO NOT COMMENT ***********************************************/
	// Delay (Non-blocking)
	tickCountUs = (tickCountUs <= (uint32_t) 0x0FFFFFFF)? (tickCountUs + 1) : 0;
	// Millisecond Counter (Raw as /1024)
	tickCountMs = (tickCountUs >> 10);
	/*********************************************** DO NOT COMMENT ***********************************************/

	/*********************************************** USER CODE ***********************************************/
	// Toggle On-board LED
	if(((tickCountMs & 0x003FF) == 0) && (tickCountMs != 0)){
		OB_LED_Toggle();
	}

	// if(readFrameBuffer){
	// 	// Increment the count
	// 	tickCountUs++;
	// 	// if((tickCountUs & 0x3FFF) == 0x0000){
	// 	// 	i2cRBStatus = 0x01;
	// 	// }
	// }
	/*********************************************** USER CODE ***********************************************/
}
