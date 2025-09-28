/**
 * @file rcc_config.c
 * @author Shrey Shah
 * @brief Reset & Clock Control Configuration
 * @version 1.1
 * @date 27-09-2025
 * @note Logs till v1.1:
 * @note - Aborted usage of `enums` as it consumes a lot of space
 * @note - Shifted to use combination of `typedef` & macros
 */

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
