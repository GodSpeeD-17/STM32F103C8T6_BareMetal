/**************************************************************************************
 * 	File: rcc.c
 *  Author: Shrey Shah
 *  Date: 14/09/2024
 ***************************************************************************************/

// Header File
#include "rcc.h"

// Main Clock Source
volatile uint32_t CoreClock = HSI_FREQ;
// Advanced High Performance Bus (AHB) Frequency
volatile uint32_t AHBClock = HSI_FREQ;
// Advanced Peripheral Bus 1 (APB1) Frequency
volatile uint32_t APB1Clock = HSI_FREQ;
// Advanced Peripheral Bus 2 (APB2) Frequency
volatile uint32_t APB2Clock = HSI_FREQ;

/**
 * @brief Retrieves the frequency of System Clock
 * @return SYSCLK Frequency (in Hz)
 */
uint32_t RCC_getClkFreq(void){
	// Final Value
	uint32_t clk_freq = 0;
	// Clock Source
	switch (RCC_getClkSrc()){
		// HSI
		case SW_CLK_HSI:
			clk_freq = HSI_FREQ;
		break;

		// HSE
		case SW_CLK_HSE:
			clk_freq = HSE_FREQ;
		break;

		// PLL
		case SW_CLK_PLL:
			// PLL Clock Source
			switch((RCC->CFGR.REG & RCC_CFGR_PLLSRC_Msk) >> RCC_CFGR_PLLSRC_Pos){
				// HSE
				case PLL_SRC_HSE:
					clk_freq = HSE_FREQ;
					// PLL Input Clock Prescaler
					if((RCC->CFGR.REG & RCC_CFGR_PLLXTPRE_Msk) == RCC_CFGR_PLLXTPRE_HSE_DIV2)
						clk_freq /= 2;
				break;
				// HSI
				case PLL_SRC_HSI_DIV_2:
					clk_freq = (uint32_t)(HSI_FREQ / 2);
				break;
			}
			// PLL Multiplication Factor
			clk_freq *= (uint8_t)(((uint8_t)((RCC->CFGR.REG & RCC_CFGR_PLLMULL_Msk) >> RCC_CFGR_PLLMULL_Pos)) + 2);
		break;
	}
	// Final Value
	return (uint32_t)clk_freq;
}

/**
 * @brief Retrieves the frequency of AHB
 * @return AHB Frequency (in Hz)
 */
uint32_t RCC_getAHBFreq(void){
	// Current SYSCLK
	uint32_t clk_freq = RCC_getClkFreq();
	// AHB Prescaler Value
	switch(RCC->CFGR.REG & RCC_CFGR_HPRE_Msk){
		case RCC_CFGR_HPRE_DIV2:
			clk_freq = (clk_freq >> 1); 
		break;
		case RCC_CFGR_HPRE_DIV4:
			clk_freq = (clk_freq >> 2); 
		break;
		case RCC_CFGR_HPRE_DIV8:
			clk_freq = (clk_freq >> 3); 
		break;
		case RCC_CFGR_HPRE_DIV16:
			clk_freq = (clk_freq >> 4); 
		break;
		case RCC_CFGR_HPRE_DIV64:
			clk_freq = (clk_freq >> 6); 
		break;
		case RCC_CFGR_HPRE_DIV128:
			clk_freq = (clk_freq >> 7);
		break;
		case RCC_CFGR_HPRE_DIV256:
			clk_freq = (clk_freq >> 8);
		break;
		case RCC_CFGR_HPRE_DIV512:
			clk_freq = (clk_freq >> 9);
		break;
	}
	return (uint32_t) clk_freq;
}

/**
 * @brief Retrieves the frequency of the APB1
 * @return APB1 Frequency (in Hz)
 * @note Max Value should not exceed more than 36MHz
 */
uint32_t RCC_getAPB1Freq(void){
	// AHB Frequency
	uint32_t clk_freq = RCC_getAHBFreq();
	// APB1 Prescaler
	switch(RCC->CFGR.REG & RCC_CFGR_PPRE1_Msk){
		case RCC_CFGR_PPRE1_DIV2:
			clk_freq = (clk_freq >> 1);
		break;
		case RCC_CFGR_PPRE1_DIV4:
			clk_freq = (clk_freq >> 2);
		break;
		case RCC_CFGR_PPRE1_DIV8:
			clk_freq = (clk_freq >> 3);
		break;
		case RCC_CFGR_PPRE1_DIV16:
			clk_freq = (clk_freq >> 4);
		break;
	}
	return (uint32_t) clk_freq;
}

/**
 * @brief Retrieves the frequency of the APB2
 * @return APB2 Frequency (in Hz)
 */
uint32_t RCC_getAPB2Freq(void){
	// AHB Frequency
	uint32_t clk_freq = RCC_getAHBFreq();
	// APB2 Prescaler
	switch(RCC->CFGR.REG & RCC_CFGR_PPRE2_Msk){
		case RCC_CFGR_PPRE2_DIV2:
			clk_freq = (clk_freq >> 1);
		break;
		case RCC_CFGR_PPRE2_DIV4:
			clk_freq = (clk_freq >> 2);
		break;
		case RCC_CFGR_PPRE2_DIV8:
			clk_freq = (clk_freq >> 3);
		break;
		case RCC_CFGR_PPRE2_DIV16:
			clk_freq = (clk_freq >> 4);
		break;
	}
	return (uint32_t) clk_freq;
}

/**
 * @brief Configures PLL parameters
 * @param[in] PLL_SRC PLL Input Source
 * @param[in] PLL_MUL PLL Multiplication Factor
 */
static void RCC_PLL_config(PLL_CLK_SRC_ENUM PLL_SRC, uint8_t PLL_MUL){
	// PLL Multiplication Factor
	RCC->CFGR.BIT.PLLMUL = PLL_MUL;
	// PLL Clock Source Configuration
	switch(PLL_SRC){
		// HSE
		case HSE_DIV_1:
			// PLL Clock Source: HSE
			RCC->CFGR.BIT.PLLSRC = PLL_SRC_HSE;
			// PLL Clock Source Division
			RCC->CFGR.BIT.PLLXTPRE = PLL_HSE_DIV_1;
		break;

		// HSE
		case HSE_DIV_2:
			// PLL Clock Source: HSE
			RCC->CFGR.BIT.PLLSRC = PLL_SRC_HSE;
			// PLL Clock Source Division
			RCC->CFGR.BIT.PLLXTPRE = PLL_HSE_DIV_2;
		break;

		// HSI
		case HSI_DIV_2:
			// PLL Clock Source: HSI
			RCC->CFGR.BIT.PLLSRC = PLL_SRC_HSI_DIV_2;
		break;

		// Error
		default:
			return;
		break;
	}
}

/**
 * @brief Configures RCC
 * @param configX RCC Configuration Structure
 */
void RCC_Config(rcc_config_t* configX){
	// Local Variable
	uint32_t reg = 0x00000000;
	// Flash Configuration
	FLASH->ACR.REG |= (uint32_t)(configX->flash.latency << FLASH_ACR_LATENCY_Pos);
	// HSE ON
	RCC->CR.REG |= RCC_CR_HSEON;
	while(!(RCC->CR.REG & RCC_CR_HSERDY_Msk));
	// PLL Configuration
	reg |= (uint32_t)((configX->pll.mul_fact << RCC_CFGR_PLLMULL_Pos) | (configX->pll.ext_src_pre << RCC_CFGR_PLLXTPRE_Pos) | (configX->pll.ext_src << RCC_CFGR_PLLSRC_Pos));
	// Bus Prescaler Configuration
	reg |= (uint32_t)((configX->bus.APB2_pre << RCC_CFGR_PPRE2_Pos) | (configX->bus.APB1_pre << RCC_CFGR_PPRE1_Pos) | (configX->bus.AHB_pre << RCC_CFGR_HPRE_Pos));
	// Component Prescaler Configuration
	reg |= (uint32_t)((configX->component.USB_pre << RCC_CFGR_USBPRE_Pos) | (configX->component.ADC_pre << RCC_CFGR_ADCPRE_Pos));
	RCC->CFGR.REG = reg;
	// PLL ON
	if(configX->sys_clk_src == SW_CLK_PLL){
		RCC->CR.REG |= RCC_CR_PLLON;
		while(!(RCC->CR.REG & RCC_CR_PLLRDY));
	}
	// System Clock Source
	RCC->CFGR.REG |= (uint32_t)((configX->sys_clk_src << RCC_CFGR_SW_Pos));
	while(((RCC->CFGR.REG & RCC_CFGR_SWS_Msk) != (configX->sys_clk_src << RCC_CFGR_SWS_Pos)));
	// Store the Frequency
	CoreClock = RCC_getClkFreq();
	AHBClock = RCC_getAHBFreq();
	APB1Clock = RCC_getAPB1Freq();
	APB2Clock = RCC_getAPB2Freq();
}
