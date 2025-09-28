/**
 * @file rcc_config.h
 * @author Shrey Shah
 * @brief Reset & Clock Control Configuration
 * @version 1.1
 * @date 27-09-2025
 * @note Logs till v1.1:
 * @note - Aborted usage of `enums` as it consumes a lot of space
 * @note - Shifted to use combination of `typedef` & macros
 */

// Header Guards
#ifndef __RCC_CONFIG_H__
#define __RCC_CONFIG_H__

// C++ Safeguard
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*********************************************** Includes ***********************************************/
#include "reg_map.h"

/*********************************************** Frequency ***********************************************/
typedef uint32_t freq_t;
#define FREQ_12Hz 								((freq_t) 12)
#define FREQ_25Hz 								((freq_t) 25)
#define FREQ_50Hz 								((freq_t) 50)
#define FREQ_100Hz 								((freq_t) 100)
#define FREQ_500Hz 								((freq_t) 500)
#define FREQ_1kHz 								((freq_t) 1000)
#define FREQ_2kHz 								((freq_t) 2000)
#define FREQ_5kHz 								((freq_t) 5000)
#define FREQ_10kHz 								((freq_t) 10000)
#define FREQ_50kHz 								((freq_t) 50000)
#define FREQ_72kHz 								((freq_t) 72000)
#define FREQ_100kHz 							((freq_t) 100000)
#define FREQ_200kHz 							((freq_t) 200000)
#define FREQ_1MHz 								((freq_t) 1000000)
#define FREQ_10MHz 								((freq_t) 10000000)

// Clock Speed
#define HSI_FREQ 								((freq_t) 8000000)
#define HSE_FREQ 								((freq_t) 8000000)
#define PLL_MIN_FREQ 							((freq_t) 16000000)
#define PLL_MAX_FREQ 							((freq_t) 72000000)

/*********************************************** Clock Source ***********************************************/
#define RCC_SYS_CLK_HSI 						((system_clock_t) 0x00)
#define RCC_SYS_CLK_HSE 						((system_clock_t) 0x01)
#define RCC_SYS_CLK_PLL 						((system_clock_t) 0x02)

/*********************************************** AHB Prescaler ***********************************************/
#define RCC_AHB_DIV_1 							((rcc_bus_prescaler_t) 0x00)
#define RCC_AHB_DIV_2 							((rcc_bus_prescaler_t) 0x08)
#define RCC_AHB_DIV_4 							((rcc_bus_prescaler_t) 0x09)
#define RCC_AHB_DIV_8 							((rcc_bus_prescaler_t) 0x0A)
#define RCC_AHB_DIV_16 							((rcc_bus_prescaler_t) 0x0B)
#define RCC_AHB_DIV_64 							((rcc_bus_prescaler_t) 0x0C)
#define RCC_AHB_DIV_128 						((rcc_bus_prescaler_t) 0x0D)
#define RCC_AHB_DIV_256 						((rcc_bus_prescaler_t) 0x0E)
#define RCC_AHB_DIV_512 						((rcc_bus_prescaler_t) 0x0F)

/*********************************************** APB1 Prescaler ***********************************************/
#define RCC_APB1_DIV_1 							((rcc_bus_prescaler_t) 0x00)
#define RCC_APB1_DIV_2 							((rcc_bus_prescaler_t) 0x04)
#define RCC_APB1_DIV_4 							((rcc_bus_prescaler_t) 0x05)
#define RCC_APB1_DIV_8 							((rcc_bus_prescaler_t) 0x06)
#define RCC_APB1_DIV_16 						((rcc_bus_prescaler_t) 0x07)

/*********************************************** APB2 Prescaler ***********************************************/
#define RCC_APB2_DIV_1 							((rcc_bus_prescaler_t) 0x00)
#define RCC_APB2_DIV_2 							((rcc_bus_prescaler_t) 0x04)
#define RCC_APB2_DIV_4 							((rcc_bus_prescaler_t) 0x05)
#define RCC_APB2_DIV_8 							((rcc_bus_prescaler_t) 0x06)
#define RCC_APB2_DIV_16 						((rcc_bus_prescaler_t) 0x07)

/*********************************************** PLL Clock Source ***********************************************/
#define RCC_PLL_SRC_HSI 						((rcc_pll_src_t) 0x00)
#define RCC_PLL_SRC_HSE 						((rcc_pll_src_t) 0x01)
#define RCC_PLL_SRC_NOT_USED					((rcc_pll_src_t) 0x00) // Reset State

/*********************************************** PLL Clock Source ***********************************************/
#define RCC_PLL_SRC_HSE_DIV_1 					((rcc_pll_src_prescaler_t) 0x00)
#define RCC_PLL_SRC_HSE_DIV_2 					((rcc_pll_src_prescaler_t) 0x01)
#define RCC_PLL_SRC_HSI_DIV_2 					((rcc_pll_src_prescaler_t) 0x01)
#define RCC_PLL_SRC_PRE_NOT_USED				((rcc_pll_src_prescaler_t) 0x00) // Reset State

/*********************************************** PLL Multiplication Factor ***********************************************/
#define RCC_PLL_MUL_2 							((rcc_pll_mul_t) 0x00)
#define RCC_PLL_MUL_3 							((rcc_pll_mul_t) 0x01)
#define RCC_PLL_MUL_4 							((rcc_pll_mul_t) 0x02)
#define RCC_PLL_MUL_5 							((rcc_pll_mul_t) 0x03)
#define RCC_PLL_MUL_6 							((rcc_pll_mul_t) 0x04)
#define RCC_PLL_MUL_7 							((rcc_pll_mul_t) 0x05)
#define RCC_PLL_MUL_8 							((rcc_pll_mul_t) 0x06)
#define RCC_PLL_MUL_9 							((rcc_pll_mul_t) 0x07)
#define RCC_PLL_MUL_10 							((rcc_pll_mul_t) 0x08)
#define RCC_PLL_MUL_11 							((rcc_pll_mul_t) 0x09)
#define RCC_PLL_MUL_12 							((rcc_pll_mul_t) 0x0A)
#define RCC_PLL_MUL_13 							((rcc_pll_mul_t) 0x0B)
#define RCC_PLL_MUL_14 							((rcc_pll_mul_t) 0x0C)
#define RCC_PLL_MUL_15 							((rcc_pll_mul_t) 0x0D)
#define RCC_PLL_MUL_16 							((rcc_pll_mul_t) 0x0E)
#define RCC_PLL_MUL_NOT_USED					((rcc_pll_mul_t) 0x00) // Reset State

/*********************************************** ADC Prescaler ***********************************************/
#define RCC_ADC_DIV_2 							((component_prescaler_t) 0x00)
#define RCC_ADC_DIV_4 							((component_prescaler_t) 0x01)
#define RCC_ADC_DIV_6 							((component_prescaler_t) 0x02)
#define RCC_ADC_DIV_8 							((component_prescaler_t) 0x03)

/*********************************************** USB Prescaler ***********************************************/
#define RCC_USB_DIV_1_5 						((component_prescaler_t) 0x00)
#define RCC_USB_DIV_1 							((component_prescaler_t) 0x01)

/*********************************************** Flash Configuration Structure ***********************************************/
// TODO: Optimize this
typedef struct {
	// 0 < SYSCLK <= 24MHz -> Zero wait state
	// 24MHz < SYSCLK <= 48MHz -> One wait state
	// 48MHz < SYSCLK <= 72MHz -> Two wait states
	uint8_t latency: 3;
	// 0: Prefetch is disabled
	// 1: Prefetch is enabled
	uint8_t prefetch: 5;
} rcc_flash_config_t;

/*********************************************** Bus Configuration Structure ***********************************************/
typedef uint8_t rcc_bus_prescaler_t;
/**
 * @brief Bus Prescaler Configuration Structure
 */
typedef struct {
	/**
	 * @brief AHB Bus Prescaler
	 * @param AHB AHB Prescalar Values Refer `RCC_AHB_DIV_*`
	 * @note Max frequency = 72MHz
	 */
	rcc_bus_prescaler_t AHB: 4;
	/**
	 * @brief APB1 Bus Prescaler
	 * @param APB1 APB1 Prescalar Values Refer `RCC_APB1_DIV_*`
	 * @note Max frequency = 36MHz
	 */
	rcc_bus_prescaler_t APB1: 3;
	/**
	 * @brief APB2 Bus Prescaler
	 * @param APB2 APB2 Prescalar Values Refer `RCC_APB2_DIV_*`
	 * @note Max frequency = 72MHz
	 */
	rcc_bus_prescaler_t APB2: 3;
} rcc_bus_prescaler_config_t;

/*********************************************** PLL Configuration ***********************************************/
typedef uint8_t rcc_pll_src_t;
typedef uint8_t rcc_pll_mul_t;
typedef uint8_t rcc_pll_src_prescaler_t;
/**
 * @brief PLL Configuration Structure
 */
typedef struct {
	/**
	 * @brief PLL Multiplication Factor Configuration
	 * @note - Determines the multiplication factor
	 * @note - Determines the final Clock Frequency if PLL is Clock Source
	 * @note - Max frequency: 72MHz
	 * @note - Do not use `0x0F` for setting the multiplication factor to 16
	 */
	rcc_pll_mul_t mul_fact: 4;
	/**
	 * @brief PLL Source Configuration
	 * @note - Determines the input to PLL
	 * @note - For STM32F1xx, the HSI is always divided by 2 
	 */
	rcc_pll_src_t src: 1;
	/**
	 * @brief PLL Source Prescaler Configuration
	 * @note - Determines the prescaler to PLL Source
	 * @note - For STM32F1xx, the HSI does not have prescaler configuration
	 */
	rcc_pll_src_prescaler_t src_prescaler: 1;
} rcc_pll_config_t;

/*********************************************** Internal Components Clock Configuration ***********************************************/
typedef uint8_t component_prescaler_t;
/**
 * @brief Component Prescaler Configu()ration Structure
 */
typedef struct {
	/**
	 * @brief ADC Prescaler Configuration
	 * @note - Max Frequency: 14MHz
	 * @note - Clock Source: `APB2`
	 */
	component_prescaler_t ADC: 2;
	/**
	 * @brief USB Prescaler Configuration
	 * @note - Max Frequency: 48MHz
	 * @note - Clock Source: `PLL`
	 */
	component_prescaler_t USB: 1;
} rcc_component_prescaler_config_t;

/*********************************************** System Clock Structure ***********************************************/
typedef uint8_t system_clock_t;
/**
 * @brief System Clock Configuration Structure
 */
typedef struct {
	/**
	 * @brief System Clock Source
	 * @param clk_src `RCC_SYS_CLK_HSI`, `RCC_SYS_CLK_HSE`, `RCC_SYS_CLK_PLL`
	 * @note This defines the AHB input clock before AHB Prescaler
	 */
	system_clock_t clk_src;
	/**
	 * @brief Phase Lock Loop (PLL) Configuration Structure
	 * @param pll Refer `rcc_pll_config_t`
	 * @note This parameter defines the PLL Configuration to be set.
	 */
	rcc_pll_config_t pll;
} rcc_sys_clk_config_t;

/*********************************************** RCC Configuration Structure ***********************************************/
/**
 * @brief RCC Confifuration Structure
 */
typedef struct {
	// Bus Prescaler Configuration
	rcc_bus_prescaler_config_t bus_prescaler;
	// System Clock
	rcc_sys_clk_config_t system;
	// Flash Configuration
	rcc_flash_config_t flash;
	// Components Prescaler
	rcc_component_prescaler_config_t component_prescaler;
} rcc_config_t;

/*********************************************** RCC Clock Frequency ***********************************************/
/**
 * @brief RCC Clock Frequency Structure
 */
typedef struct {
	// System Clock Frequency
	freq_t Core;
	// AHB Clock Frequency
	freq_t AHB;
	// APB1 Clock Frequency
	freq_t APB1;
	// APB2 Clock Frequency
	freq_t APB2;
} rcc_clk_freq_t;

/*********************************************** Prescaler Lookup Table ***********************************************/
extern const rcc_bus_prescaler_t __ahbPrescalerDriverMapping__[8];
extern const rcc_bus_prescaler_t __apbPrescalerDriverMapping__[4];

/*********************************************** Helper APIs ***********************************************/
/**
 * @brief Enables Clock for Alternate Function (AFIO)
 */
__STATIC_INLINE__ void RCC_AFIO_Clk_Enable(void){
	// Enable AFIO Clock
	RCC->APB2ENR.REG |= RCC_APB2ENR_AFIOEN;
}

/**
 * @brief Disables Clock for Alternate Function (AFIO)
 */
__STATIC_INLINE__ void RCC_AFIO_Clk_Disable(void){
	// Disable AFIO Clock
	RCC->APB2ENR.REG &= ~RCC_APB2ENR_AFIOEN;
}

/**
 * @brief Turn ON High Speed External Clock (HSE)
 * @note Blocking Function waits for Clock to be ready
 */
__STATIC_INLINE__ void RCC_HSE_ON(void){
	// Turn ON HSE
	RCC->CR.REG |= RCC_CR_HSEON;
	// Blocking: Wait for Clock to be ready
	while(!(RCC->CR.REG & RCC_CR_HSERDY));
}

/**
 * @brief Turn OFF High Speed External Clock (HSE)
 * @note Blocking Function waits for Clock to be OFF
 */
__STATIC_INLINE__ void RCC_HSE_OFF(void){
	// Turn OFF HSE
	RCC->CR.REG &= ~RCC_CR_HSEON;
	// Blocking: Wait for Clock to be OFF
	while(RCC->CR.REG & RCC_CR_HSERDY);
}

/**
 * @brief Turn On Phase Lock Loop (PLL)
 * @note Blocking Function waits for Clock to be ready
 */
__STATIC_INLINE__ void RCC_PLL_ON(void){
	// Turn ON PLL
	RCC->CR.REG |= RCC_CR_PLLON;
	// Blocking: Wait for Clock to be ready
	while(!(RCC->CR.REG & RCC_CR_PLLRDY));
}

/**
 * @brief Turn OFF Phase Lock Loop (PLL)
 * @note Blocking Function waits for Clock to be OFF
 */
__STATIC_INLINE__ void RCC_PLL_OFF(void){
	// Turn OFF PLL
	RCC->CR.REG &= ~RCC_CR_PLLON;
	// Blocking: Wait for Clock to be OFF
	while(RCC->CR.REG & RCC_CR_PLLRDY);
}

/**
 * @brief Updates the System Clock Source
 * @param systemClk System Clock Source: `RCC_SYS_CLK_HSI`, `RCC_SYS_CLK_HSE`, `RCC_SYS_CLK_PLL`
 * @note Blocking Function waits for confirmation from Hardware regarding status 
 */
__STATIC_INLINE__ void RCC_SysClkSrc_Set(const system_clock_t systemClk){
	// Update the Register
	RCC->CFGR.REG |= (uint32_t)(((systemClk & 0x03) << RCC_CFGR_SW_Pos));
	// Blocking: Waits for hardware confirmation
	while((RCC->CFGR.REG & RCC_CFGR_SWS) != ((systemClk & 0x03) << RCC_CFGR_SWS_Pos));
}

/**
 * @brief Retrieves the System Clock Source
 * @note Reads the `RCC->CFGR.REG`
 */
__STATIC_INLINE__ system_clock_t RCC_SysClkSrc_Get(void){
	// System Clock Source (feedback from hardware)
	return ((system_clock_t) ((RCC->CFGR.REG & RCC_CFGR_SWS) >> RCC_CFGR_SWS_Pos));
}

/**
 * @brief Retrieves the PLL Clock Source
 * @note Reads the `RCC->CFGR.REG`
 * @returns PLL Clock Source
 */
__STATIC_INLINE__ rcc_pll_src_t RCC_PLLClkSrc_Get(void){
	// Returns PLL Clock Source
	return ((rcc_pll_src_t) ((RCC->CFGR.REG & RCC_CFGR_PLLSRC) >> RCC_CFGR_PLLSRC_Pos));
}

/**
 * @brief Retrieves the PLL External Clock Src Prescaler (in form of bits to be right shifted)
 * @return Prescaler in form of bits to be right shifted for PLL External Clock Source Prescaler 
 * @note Takes care of only: `RCC_PLL_SRC_HSE`
 */
__STATIC_INLINE__ rcc_pll_src_prescaler_t RCC_PLLExtClkSrcPscRightShift_Get(void){
	// Return the External Clock Src Prescaler
	return ((rcc_pll_src_prescaler_t) ((RCC->CFGR.REG & RCC_CFGR_PLLXTPRE) >> RCC_CFGR_PLLXTPRE_Pos));
}

/**
 * @brief Retrieves the PLL Prescaler (in form of bits to be right shifted)
 * @returns Prescaler in form of bits to be right shifted for PLL Clock
 * @note Takes care of both the cases: `RCC_PLL_SRC_HSI`, `RCC_PLL_SRC_HSE`
 */
__STATIC_INLINE__ rcc_pll_src_prescaler_t RCC_PLLClkSrcPscRightShift_Get(void){
	// Get PLL Clock Source
	rcc_pll_src_t rccPLLSrc = RCC_PLLClkSrc_Get();
	// Final Prescaler Value
	rcc_pll_src_prescaler_t rccPLLSrcPrescaler = RCC_PLL_SRC_PRE_NOT_USED;
	// PLL Clock Source
	switch(rccPLLSrc){
		// HSI
		case RCC_PLL_SRC_HSI:
			// Right shift by 1 (/2)
			rccPLLSrcPrescaler = RCC_PLL_SRC_HSI_DIV_2;
		break;
		// HSE
		case RCC_PLL_SRC_HSE:
			// Right shift by equibalent bits
			rccPLLSrcPrescaler = RCC_PLLExtClkSrcPscRightShift_Get();
		break;
	}
	// Returns PLL Clock Source
	return rccPLLSrcPrescaler;
}

/**
 * @brief Retrieves the PLL Multiplication Factor
 * @return RCC Multiplication Factor
 * @note Reads `RCC->CFGR.REG`
 */
__STATIC_INLINE__ rcc_pll_mul_t RCC_PLLMulFactor_Get(void){
	// Retrives the PLL Multiplication Factor
	return ((rcc_pll_mul_t) (((RCC->CFGR.REG & RCC_CFGR_PLLMULL) >> RCC_CFGR_PLLMULL_Pos) + 2));
}

/**
 * @brief Retrieves the AHB Prescaler (in form of bits to be right shifted)
 * @return Prescaler in form of bits to be right shifted for AHB Clock
 */
__STATIC_INLINE__ rcc_bus_prescaler_t __RCC_AHBPscRightShift_Get__(void){
	// AHB Prescaler Index for `__ahbPrescalerDriverMapping__[8]`
	rcc_bus_prescaler_t index = RCC_AHB_DIV_1;
	// Extract AHB Prescaler Bit Value
	uint8_t reg = ((RCC->CFGR.REG & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos);
	// Prescaler != 0x01
	if(reg >= RCC_AHB_DIV_2){
		// Wrap around 8 (Subtracting the value from 8)
		index = (reg & 0x07);
	}
	// Return the right shifting bits
	return __ahbPrescalerDriverMapping__[index];
}

/**
 * @brief Retrieves the APB1 Prescaler (in form of bits to be right shifted)
 * @return Prescaler in form of bits to be right shifted for APB1 Clock
 */
__STATIC_INLINE__ rcc_bus_prescaler_t __RCC_APB1PscRightShift_Get__(void){
	// APB1 Prescaler Index for `__apbPrescalerDriverMapping__[4]`
	rcc_bus_prescaler_t index = RCC_APB1_DIV_1;
	// Extract APB1 Prescaler Bit Value
	uint8_t reg = ((RCC->CFGR.REG & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos);
	// Prescaler != 0x01
	if(reg >= RCC_APB1_DIV_2){
		// Wrap around 4 (Subtracting the value from 4)
		index = (reg & 0x03);
	}
	// Return the right shifting bits
	return __apbPrescalerDriverMapping__[index];
}

/**
 * @brief Retrieves the APB2 Prescaler (in form of bits to be right shifted)
 * @return Prescaler in form of bits to be right shifted for APB2 Clock
 */
__STATIC_INLINE__ rcc_bus_prescaler_t __RCC_APB2PscRightShift_Get__(void){
	// APB2 Prescaler Index for `__apbPrescalerDriverMapping__[4]`
	rcc_bus_prescaler_t index = RCC_APB2_DIV_1;
	// Extract APB2 Prescaler Bit Value
	uint8_t reg = ((RCC->CFGR.REG & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos);
	// Prescaler != 0x01
	if(reg >= RCC_APB2_DIV_2){
		// Wrap around 4 (Subtracting the value from 4)
		index = (reg & 0x03);
	}
	// Return the right shifting bits
	return __apbPrescalerDriverMapping__[index];
}

/*********************************************** Driver APIs ***********************************************/
/**
 * @brief Updates the System Core Clock Frequency
 * @param coreClockFrequencyHz Pointer to variable which shall hold the Core Clock frequency
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_CoreClockFreq_Update(freq_t* coreClockFrequencyHz);

/**
 * @brief Updates the System AHB Clock Frequency
 * @param ahbClockFrequencyHz Pointer to variable which shall hold the AHB Clock frequency
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_AHBClockFreq_Update(freq_t* ahbClockFrequencyHz);

/**
 * @brief Updates the System APB1 Clock Frequency
 * @param apb1ClockFrequencyHz Pointer to variable which shall hold the APB1 Clock frequency
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_APB1ClockFreq_Update(freq_t* apb1ClockFrequencyHz);

/**
 * @brief Updates the System APB2 Clock Frequency
 * @param apb1ClockFrequencyHz Pointer to variable which shall hold the APB2 Clock frequency
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_APB2ClockFreq_Update(freq_t* apb2ClockFrequencyHz);

/**
 * @brief Updates the System AHB Clock Frequency
 * @param coreClockFrequencyHz Core Clock frequency
 * @param ahbClockFrequencyHz Pointer to variable which shall hold the AHB Clock frequency
 */
__STATIC_INLINE__ void RCC_AHBClockFreqFromCoreClock_Update(const freq_t coreClockFrequencyHz, freq_t* ahbClockFrequencyHz){
	// Account for AHB Prescaler
	*ahbClockFrequencyHz = (coreClockFrequencyHz >> __RCC_AHBPscRightShift_Get__());
}

/**
 * @brief Update the System APB1 Clock Frequency
 * @param ahbClockFrequencyHz AHB Clock frequency
 * @param apb1ClockFrequencyHz Pointer to variable which shall hold the APB1 Clock frequency
 */
__STATIC_INLINE__ void RCC_APB1ClockFreqFromAHBClock_Update(const freq_t ahbClockFrequencyHz, freq_t* apb1ClockFrequencyHz){
	// Account for APB1 Prescaler
	*apb1ClockFrequencyHz = (ahbClockFrequencyHz >> __RCC_APB1PscRightShift_Get__());
}

/**
 * @brief Retrives the System APB2 Clock Frequency
 * @param ahbClockFrequencyHz AHB Clock frequency
 * @param apb2ClockFrequencyHz Pointer to variable which shall hold the APB2 Clock frequency
 */
__STATIC_INLINE__ void RCC_APB2ClockFreqFromAHBClock_Update(const freq_t ahbClockFrequencyHz, freq_t* apb2ClockFrequencyHz){
	// Account for APB2 Prescaler
	*apb2ClockFrequencyHz = (ahbClockFrequencyHz >> __RCC_APB2PscRightShift_Get__());
}

/**
 * @brief Retrieves the System Clock Frequency (in Hz) 
 * @param clkFreq Pointer to System Clock Frequency 
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_ClockFreq_Update(rcc_clk_freq_t* clkFreq);

/**
 * @brief Computes the AHB Clock Divisor from prescaler
 * @param prescaler Refer `RCC_AHB_DIV_*`
 * @return Computed Prescaler Value
 */
__STATIC_INLINE__ rcc_bus_prescaler_t RCC_AHBComputePrescaler(const rcc_bus_prescaler_t prescaler){
	return ((rcc_bus_prescaler_t) (0x01 << __RCC_AHBPscRightShift_Get__()));
}

/**
 * @brief Computes the APB1 Clock Divisor from prescaler
 * @param prescaler Refer `RCC_APB1_DIV_*`
 * @return Computed Prescaler Value
 */
__STATIC_INLINE__ rcc_bus_prescaler_t RCC_APB1ComputePrescaler(const rcc_bus_prescaler_t prescaler){
	return ((rcc_bus_prescaler_t) (0x01 << __RCC_APB1PscRightShift_Get__()));
}

/**
 * @brief Computes the APB2 Clock Divisor from prescaler
 * @param prescaler Refer `RCC_APB2_DIV_*`
 * @return Computed Prescaler Value
 */
__STATIC_INLINE__ rcc_bus_prescaler_t RCC_APB2ComputePrescaler(const rcc_bus_prescaler_t prescaler){
	return ((rcc_bus_prescaler_t) (0x01 << __RCC_APB2PscRightShift_Get__()));;
}



#ifdef __OLD_RCC_METHOD__
/**
 * @brief AHB Prescaler
 */
uint8_t RCC_Get_AHB_Prescaler(void);

/**
 * @brief APB1 Prescaler
 */
uint8_t RCC_Get_APB1_Prescaler(void);

/**
 * @brief APB2 Prescaler
 */
uint8_t RCC_Get_APB2_Prescaler(void);

/**
 * @brief Updates the Core Clock
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 72MHz 
 */
void RCC_Update_CoreClock();

/**
 * @brief Updates the AHB Clock based upon AHB prescaler (`HPRE`)
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 72MHz
 */
void RCC_Update_AHBClock();

/**
 * @brief Updates the APB1 Clock based upon APB1 prescaler (`PPRE1`)
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 36MHz 
 */
void RCC_Update_APB1Clock();

/**
 * @brief Updates the APB2 Clock based upon APB2 prescaler (`PPRE2`)
 * @note This function should be called after any change in the RCC configuration
 * @note Max Frequency: 72MHz 
 */
void RCC_Update_APB2Clock();

/**
 * @brief Retrieves the Core Clock Frequency
 * @return Core Clock Frequency 
 * @note Max Frequency: 72MHz 
 */
uint32_t RCC_Get_CoreClock();

/**
 * @brief Retrieves the AHB Clock Frequency
 * @return AHB Frequency 
 * @note Max Frequency: 72MHz 
 */
uint32_t RCC_Get_AHBClock();

/**
 * @brief Retrieves the APB1 Clock Frequency
 * @return APB1 Frequency 
 * @note Max Frequency: 36MHz
 */
uint32_t RCC_Get_APB1Clock();

/**
 * @brief Retrieves the APB2 Clock Frequency
 * @return APB2 Frequency 
 * @note Max Frequency: 72MHz 
 */
uint32_t RCC_Get_APB2Clock();

#endif /* __OLD_RCC_METHOD__ */


// C++ Safeguard
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RCC_CONFIG_H__ */