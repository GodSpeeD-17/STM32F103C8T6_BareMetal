/*********************************************** Headers ***********************************************/
#include "rcc_config.h"

/*********************************************** AHB Prescaler Lookup Table ***********************************************/
const rcc_bus_prescaler_t __ahbPrescalerDriverMapping__[8] = {1, 2, 3, 4, 6, 7, 8, 9};
/*********************************************** APB Prescaler Lookup Table ***********************************************/
const rcc_bus_prescaler_t __apbPrescalerDriverMapping__[4] = {1, 2, 3, 4};

/*********************************************** Driver APIs ***********************************************/
/**
 * @brief Updates the System Core Clock Frequency
 * @param coreClockFrequencyHz Pointer to variable which shall hold the Core Clock frequency
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_CoreClockFreq_Update(freq_t* coreClockFrequencyHz){
	// Fetch System Clock Source
	system_clock_t coreClockSource = RCC_SysClkSrc_Get();
	if((coreClockSource != RCC_SYS_CLK_HSE) && (coreClockSource != RCC_SYS_CLK_HSI) && (coreClockSource != RCC_SYS_CLK_PLL)){
		// Return Error
		return DRIVER_FAIL;
	}
	// Select Clock Source
	switch(coreClockSource){
		// HSI
		case RCC_SYS_CLK_HSI:
			*coreClockFrequencyHz = HSI_FREQ;
		break;
		// HSE
		case RCC_SYS_CLK_HSE:
			*coreClockFrequencyHz = HSE_FREQ;
		break;
		// PLL
		case RCC_SYS_CLK_PLL:
			// Update Core Clock Frequency to HSE 
			*coreClockFrequencyHz = HSE_FREQ;
			// Update for HSI
			if(RCC_PLLClkSrc_Get() == RCC_PLL_SRC_HSI){
				*coreClockFrequencyHz = HSI_FREQ;
			}
			// Account for Prescaler
			*coreClockFrequencyHz >>= RCC_PLLClkSrcPscRightShift_Get();
			// PLL Multiplication Factor
			*coreClockFrequencyHz *= RCC_PLLMulFactor_Get();
		break;
	}
	// Return Driver Success
	return DRIVER_SUCCESS;
}

/**
 * @brief Updates the System AHB Clock Frequency
 * @param ahbClockFrequencyHz Pointer to variable which shall hold the AHB Clock frequency
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_AHBClockFreq_Update(freq_t* ahbClockFrequencyHz){
	// Local Variables
	driver_status_t status = DRIVER_FAIL; 
	// Get the System Core Clock Frequency
	status = RCC_CoreClockFreq_Update(ahbClockFrequencyHz);
	ASSERT_DRIVER_STATUS(status);
	// Account for AHB Prescaler
	*ahbClockFrequencyHz >>= __RCC_AHBPscRightShift_Get__();
	// Return Driver Success
	return DRIVER_SUCCESS;
}

/**
 * @brief Updates the System APB1 Clock Frequency
 * @param apb1ClockFrequencyHz Pointer to variable which shall hold the APB1 Clock frequency
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_APB1ClockFreq_Update(freq_t* apb1ClockFrequencyHz){
	// Local Variables
	driver_status_t status = DRIVER_FAIL; 
	// Get the System Core Clock Frequency
	status = RCC_CoreClockFreq_Update(apb1ClockFrequencyHz);
	ASSERT_DRIVER_STATUS(status);
	// Account for APB1 Prescaler
	*apb1ClockFrequencyHz >>= __RCC_APB1PscRightShift_Get__();
	// Return Driver Success
	return DRIVER_SUCCESS;
}

/**
 * @brief Updates the System APB2 Clock Frequency
 * @param apb1ClockFrequencyHz Pointer to variable which shall hold the APB2 Clock frequency
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_APB2ClockFreq_Update(freq_t* apb2ClockFrequencyHz){
	// Local Variables
	driver_status_t status = DRIVER_FAIL; 
	// Get the System Core Clock Frequency
	status = RCC_CoreClockFreq_Update(apb2ClockFrequencyHz);
	ASSERT_DRIVER_STATUS(status);
	// Account for APB2 Prescaler
	*apb2ClockFrequencyHz >>= __RCC_APB2PscRightShift_Get__();
	// Return Driver Success
	return DRIVER_SUCCESS;
}

/**
 * @brief Updates the System Clock Frequency (in Hz) 
 * @param clkFreq Pointer to System Clock Frequency 
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_ClockFreq_Update(rcc_clk_freq_t* clkFreq){
	// Local Variables
	driver_status_t status = DRIVER_FAIL;
	// Fetch Core Clock
	status = RCC_CoreClockFreq_Update(&clkFreq->Core);
	ASSERT_DRIVER_STATUS(status);
	// Fetch AHB Clock
	RCC_AHBClockFreqFromCoreClock_Update(clkFreq->Core, &clkFreq->AHB);
	// Fetch APB1 Clock
	RCC_APB1ClockFreqFromAHBClock_Update(clkFreq->Core, &clkFreq->APB1);
	// Fetch APB2 Clock
	RCC_APB2ClockFreqFromAHBClock_Update(clkFreq->Core, &clkFreq->APB2);
	// Return Status
	return status;
}

#ifdef __OLD_RCC_METHOD__

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
 * @note Max Frequency: 72MHz
 */
void RCC_Update_AHBClock(){
	// Assign Core Clock to AHB Clock
	uint32_t AHB_Clock = System.CoreClock;
	// Calculate the offset from `HPRE_DIV_2`
	int8_t prescaler = (((int32_t)(RCC->CFGR.REG & RCC_CFGR_HPRE)) - ((int32_t)RCC_CFGR_HPRE_DIV2)) >> RCC_CFGR_HPRE_Pos;
	// Positive Offset indicates a prescaler
	if(prescaler >= 0){
		AHB_Clock >>= __ahbPrescalerDriverMapping__[prescaler];
	}
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
		APB1_Clock >>= __apbPrescalerDriverMapping__[prescaler];
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
		APB2_Clock >>= __apbPrescalerDriverMapping__[prescaler];
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

/**
 * @brief AHB Prescaler
 */
uint8_t RCC_Get_AHB_Prescaler(void){
	uint8_t index = ((RCC->CFGR.REG & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos);
	if(index > 0x07)
		return (1 << __apbPrescalerDriverMapping__[(index & 0x07)]);
	else
		return 1;
}

/**
 * @brief APB1 Prescaler
 */
uint8_t RCC_Get_APB1_Prescaler(void){
	uint8_t index = ((RCC->CFGR.REG & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos);
	if(index > 0x03)
		return (1 << __apbPrescalerDriverMapping__[(index & 0x03)]);
	else
		return 1;
}

/**
 * @brief APB2 Prescaler
 */
uint8_t RCC_Get_APB2_Prescaler(void){
	uint8_t index = ((RCC->CFGR.REG & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos);
	if(index > 0x03)
		return (1 << __apbPrescalerDriverMapping__[(index & 0x03)]);
	else
		return 1;
}

#endif /* __OLD_RCC_METHOD__ */