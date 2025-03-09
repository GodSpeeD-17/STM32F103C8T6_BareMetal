/**************************************************************************************
 * 	File: rcc.c
 *  Author: Shrey Shah
 *  Date: 14/09/2024
 ***************************************************************************************/

// Header File
#include "rcc.h"

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
 * @brief Reference Working Code
 */
static void RCC_sys72MHz_config(void){
	// Reset CR
	RCC->CR.REG &= 0xFEF2FFFE;
	// HSE ON
	RCC->CR.BIT.HSEON = BIT_SET;
	// Wait for HSE to stabilize
	while(RCC->CR.BIT.HSERDY == BIT_RESET);
	// Two wait states, if 48 MHz < SYSCLK <= 72 MHz
	FLASH->ACR.REG |= (uint32_t)(1 << 1);
	// Reset CFGR
	RCC->CFGR.REG &= 0xF880000C;
	// PLL Multiplication Factor
	RCC->CFGR.BIT.PLLMUL = PLL_MUL_9;
	// HSE clock not divided
	RCC->CFGR.BIT.PLLXTPRE = BIT_RESET;
	// HSE oscillator clock selected as PLL input clock
	RCC->CFGR.BIT.PLLSRC = PLL_SRC_HSE;
	// PLL ON
	RCC->CR.BIT.PLLON = BIT_SET;
	// Wait for PLL to stabilize
	while(RCC->CR.BIT.PLLRDY == BIT_RESET);
	// AHB Prescaler
	RCC->CFGR.BIT.HPRE = AHB_DIV_1;
	// APB1 Prescaler
	RCC->CFGR.BIT.PPRE1 = APB1_DIV_2;
	// APB2 Prescaler
	RCC->CFGR.BIT.PPRE2 = APB2_DIV_1;
	// PLL selected as System Clock
	RCC->CFGR.BIT.SW = SW_CLK_PLL;
	// Wait for H/W Confirmation
	while(RCC->CFGR.BIT.SWS != RCC->CFGR.BIT.SW);
	// Store the Frequency
	CoreClock = RCC_getClkFreq();
	AHBClock = RCC_getAHBFreq();
	APB1Clock = RCC_getAPB1Freq();
	APB2Clock = RCC_getAPB2Freq();
}

/**
 * @brief Configures System Clock (SYSCLK)
 * @param[in] CLK_FREQ Core Clock Frequency `SYSCLK_FREQ`
 * @note - PLL as System Clock Source 
 * @note - HSE is used for PLL Clock Source
 * @note - ADC Max Clock Frequency is 14MHz
 * @note - USB Max Clock Frequency is 48MHz
 */
void RCC_SYSCLK_config(SYSCLK_FREQ CLK_FREQ){
	// Reset CR
	RCC->CR.REG &= 0xFEF2FFFE;
	// Reset CFGR
	RCC->CFGR.REG &= 0xF880000C;

	// HSE ON
	RCC->CR.BIT.HSEON = BIT_SET;
	// Wait for HSE to stabilize
	while(RCC->CR.BIT.HSERDY == BIT_RESET);

	// Configuration of PLL based upon input frequency
    switch (CLK_FREQ) {

        // 16MHz
        case SYSCLK_16MHz:
			// Zero wait state, if SYSCLK <= 24 MHz
			FLASH->ACR.REG |= FLASH_ACR_LATENCY_0;
            // Configure PLL parameters
			RCC_PLL_config(HSE_DIV_1, PLL_MUL_2);
			// ADC Prescaler
			RCC->CFGR.REG |= ((ADC_DIV_2 & 0x03) << 14);
			// USB Prescaler
			RCC->CFGR.REG |= ((USB_DIV_1 & 0x01) << 22);
        break;

        // 24MHz
        case SYSCLK_24MHz:
			// Zero wait state, if SYSCLK <= 24 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_ACR_LATENCY_0;
            // Configure PLL parameters
			RCC_PLL_config(HSE_DIV_1, PLL_MUL_3);
			// ADC Prescaler
			RCC->CFGR.REG |= ((ADC_DIV_2 & 0x03) << 14);
			// USB Prescaler
			RCC->CFGR.REG |= ((USB_DIV_1 & 0x01) << 22);
        break;

        // 32MHz
        case SYSCLK_32MHz:
			// One wait state, if 24 MHz < SYSCLK <= 48 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_ACR_LATENCY_1;
            // Configure PLL parameters
			RCC_PLL_config(HSE_DIV_1, PLL_MUL_4);
			// ADC Prescaler
			RCC->CFGR.REG |= ((ADC_DIV_4 & 0x03) << 14);
			// USB Prescaler
			RCC->CFGR.REG |= ((USB_DIV_1 & 0x01) << 22);
        break;

        // 40MHz
        case SYSCLK_40MHz:
			// One wait state, if 24 MHz < SYSCLK <= 48 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_ACR_LATENCY_1;
            // Configure PLL parameters
			RCC_PLL_config(HSE_DIV_1, PLL_MUL_5);
			// ADC Prescaler
			RCC->CFGR.REG |= ((ADC_DIV_4 & 0x03) << 14);
			// USB Prescaler
			RCC->CFGR.REG |= ((USB_DIV_1 & 0x01) << 22);
        break;

        // 48MHz
        case SYSCLK_48MHz:
			// One wait state, if 24 MHz < SYSCLK <= 48 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_ACR_LATENCY_1;
			// Configure PLL parameters
			RCC_PLL_config(HSE_DIV_1, PLL_MUL_6);
			// ADC Prescaler
			RCC->CFGR.REG |= ((ADC_DIV_4 & 0x03) << 14);
			// USB Prescaler
			RCC->CFGR.REG |= ((USB_DIV_1 & 0x01) << 22);
        break;

        // 56MHz
        case SYSCLK_56MHz:
			// Two wait states, if 48 MHz < SYSCLK <= 72 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_ACR_LATENCY_2;
			// Configure PLL parameters
            RCC_PLL_config(HSE_DIV_1, PLL_MUL_7);
			// ADC Prescaler
			RCC->CFGR.REG |= ((ADC_DIV_4 & 0x03) << 14);
			// USB Prescaler
			RCC->CFGR.REG |= ((USB_DIV_1_5 & 0x01) << 22);
        break;

        // 64MHz
        case SYSCLK_64MHz:
			// Two wait states, if 48 MHz < SYSCLK <= 72 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_ACR_LATENCY_2;
			// Configure PLL parameters
            RCC_PLL_config(HSE_DIV_1, PLL_MUL_8);
			// ADC Prescaler
			RCC->CFGR.REG |= ((ADC_DIV_6 & 0x03) << 14);
			// USB Prescaler
			RCC->CFGR.REG |= ((USB_DIV_1_5 & 0x01) << 22);
        break;

        // 72MHz
        case SYSCLK_72MHz:
			// Two wait states, if 48 MHz < SYSCLK <= 72 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_ACR_LATENCY_2;
            // Configure PLL parameters
			RCC_PLL_config(HSE_DIV_1, PLL_MUL_9);
			// ADC Prescaler
			RCC->CFGR.REG |= ((ADC_DIV_6 & 0x03) << 14);
			// USB Prescaler
			RCC->CFGR.REG |= ((USB_DIV_1_5 & 0x01) << 22);
        break;

		// Error Handling
		default:
			return;
		break;	
    }

	// PLL ON
	RCC->CR.BIT.PLLON = BIT_SET;
	// Wait for PLL to stabilize
	while(RCC->CR.BIT.PLLRDY == BIT_RESET);

	// Configure BUS parameters (APB1 max 36MHz)
	if(CLK_FREQ > SYSCLK_32MHz){
		RCC_busConfig(AHB_DIV_1, APB1_DIV_2, APB2_DIV_1);
	}
	else{
		RCC_busConfig(AHB_DIV_1, APB1_DIV_1, APB2_DIV_1);
	}

	// Software Selection of PLL
	RCC->CFGR.BIT.SW = SW_CLK_PLL;
	// Confirmation by Hardware
	while(RCC->CFGR.BIT.SWS != RCC->CFGR.BIT.SW);

	// Store the Frequency
	CoreClock = RCC_getClkFreq();
	AHBClock = RCC_getAHBFreq();
	APB1Clock = RCC_getAPB1Freq();
	APB2Clock = RCC_getAPB2Freq();
}

/**
 * @brief Configures RCC
 * @param configX RCC Configuration Structure
 */
void RCC_config(rcc_config_t* configX){
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
