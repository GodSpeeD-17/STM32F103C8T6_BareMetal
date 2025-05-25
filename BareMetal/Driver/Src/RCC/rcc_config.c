// Header
#include "rcc_config.h"

// AHB Prescaler 
static const uint8_t AHB_prescaler[8] = {1, 2, 3, 4, 6, 7, 8, 9};
// APBx Prescaler 
static const uint8_t APB_prescaler[4] = {1, 2, 3, 4};

// System Clock Frequencies
volatile static rcc_clk_t System = {
	.CoreClock = HSI_FREQ,
	.AHBClock = HSI_FREQ,
	.APB1Clock = HSI_FREQ,
	.APB2Clock = HSI_FREQ,
};

/**
 * @brief Updates the Core Clock
 * @note This function should be called after any change in the RCC configuration
 */
void RCC_Update_CoreClock() {
	// Final Clock
	uint32_t Core_Clock = HSI_FREQ;
	// Determine the Clock Source
	switch(RCC->CFGR.REG & RCC_CFGR_SWS){
		// HSE
		case RCC_CFGR_SWS_HSE:
			Core_Clock = HSE_FREQ;
		break;

		// PLL
		case RCC_CFGR_SWS_PLL:
			// Determine the PLL Source
			switch(RCC->CFGR.REG & RCC_CFGR_PLLSRC){
				// HSE
				case RCC_CFGR_PLLSRC_HSE:
					// Safety
					Core_Clock = HSE_FREQ;
					// HSE/2 
					if((RCC->CFGR.REG & RCC_CFGR_PLLXTPRE) == RCC_CFGR_PLLXTPRE_HSE_DIV2)
							Core_Clock >>= 1;
				break;

				// HSI/2
				case RCC_CFGR_PLLSRC_HSI_DIV2:
					Core_Clock >>= 1;
				break;
			}
			// PLL Multiplication Factor
			Core_Clock *= (((RCC->CFGR.REG & RCC_CFGR_PLLMULL) >> RCC_CFGR_PLLMULL_Pos) + 2);
		break;
	}
	// Update the Core Clock
	System.CoreClock = Core_Clock;
}

/**
 * @brief Updates the AHB Clock based upon AHB prescaler (`HPRE`)
 * @note This function should be called after any change in the RCC configuration
 */
void RCC_Update_AHBClock(){
	// Update the Core Clock and asign to AHB Clock
	RCC_Update_CoreClock();
	// Assign Core Clock to AHB Clock
	System.AHBClock = System.CoreClock;
	// Calculate the offset from HPRE_DIV_2
	int8_t prescaler = (((int32_t)(RCC->CFGR.REG & RCC_CFGR_HPRE)) - ((int32_t)RCC_CFGR_HPRE_DIV2)) >> RCC_CFGR_HPRE_Pos;
	// Positive Offset indicates a prescaler
	if(prescaler >= 0)
		System.AHBClock >>= AHB_prescaler[prescaler];
}

/**
 * @brief Updates the AHB Clock based upon AHB prescaler (`HPRE`)
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 72MHz
 */
void RCC_Update_AHBClock(){
	// Assign Core Clock to AHB Clock
	uint32_t AHB_Clock = System.CoreClock;
	// Calculate the offset from `HPRE_DIV_2`
	int8_t prescaler = (((int32_t)(RCC->CFGR.REG & RCC_CFGR_HPRE)) - ((int32_t)RCC_CFGR_HPRE_DIV2)) >> RCC_CFGR_HPRE_Pos;
	// Positive Offset indicates a prescaler
	if(prescaler >= 0)
		AHB_Clock >>= AHB_prescaler[prescaler];
	// Assign the AHB Clock Value
	System.AHBClock = AHB_Clock; 
}

/**
 * @brief Updates the APB1 Clock based upon APB1 prescaler (`PPRE1`)
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 36MHz
 */
void RCC_Update_APB1Clock(){
	// Assign AHB Clock to APB1 Clock
	uint32_t APB1_Clock = System.AHBClock;
	// Calculate the offset from `PPRE1_DIV_2`
	int8_t prescaler = (((int32_t)(RCC->CFGR.REG & RCC_CFGR_PPRE1)) - ((int32_t)RCC_CFGR_PPRE1_DIV2)) >> RCC_CFGR_PPRE1_Pos;
	// Positive Offset indicates a prescaler
	if(prescaler >= 0)
		APB1_Clock >>= APB_prescaler[prescaler];
	// Assign the APB1 Clock Value
	System.APB1Clock = APB1_Clock;
}

/**
 * @brief Updates the APB2 Clock based upon APB2 prescaler (`PPRE2`)
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 72MHz 
 */
void RCC_Update_APB2Clock(){
	// Assign AHB Clock to APB2 Clock
	uint32_t APB2_Clock = System.AHBClock;
	// Calculate the offset from `PPRE2_DIV_2`
	int8_t prescaler = (((int32_t)(RCC->CFGR.REG & RCC_CFGR_PPRE2)) - ((int32_t)RCC_CFGR_PPRE2_DIV2)) >> RCC_CFGR_PPRE2_Pos;
	// Positive Offset indicates a prescaler
	if(prescaler >= 0)
		APB2_Clock >>= APB_prescaler[prescaler];
	// Assign the APB1 Clock Value
	System.APB2Clock = APB2_Clock;
}

/**
 * @brief Retrieves the Core Clock Frequency
 * @return Core Clock Frequency 
 * @note Max Frequency: 72MHz 
 */
uint32_t RCC_Get_CoreClock(){
	// Fetch the value
	uint32_t Core_Clock = System.CoreClock;
	// Return the value
	return Core_Clock;
}

/**
 * @brief Retrieves the AHB Clock Frequency
 * @return AHB Frequency 
 * @note Max Frequency: 72MHz 
 */
uint32_t RCC_Get_AHBClock(){
	// Fetch the value
	uint32_t AHB_Clock = System.AHBClock;
	// Return the value
	return AHB_Clock;
}

/**
 * @brief Retrieves the APB1 Clock Frequency
 * @return APB1 Frequency 
 * @note Max Frequency: 36MHz 
 */
uint32_t RCC_Get_APB1Clock(){
	// Fetch the value
	uint32_t APB1_Clock = System.APB1Clock;
	// Return the value
	return APB1_Clock;
}

/**
 * @brief Retrieves the APB2 Clock Frequency
 * @return APB2 Frequency 
 * @note Max Frequency: 72MHz 
 */
uint32_t RCC_Get_APB2Clock(){
	// Fetch the value
	uint32_t APB2_Clock = System.APB2Clock;
	// Return the value
	return APB2_Clock;
}

