/**************************************************************************************
 * 	File: rcc.c
 *  Author: Shrey Shah
 *  Date: 14/09/2024
 ***************************************************************************************/

// Header File
#include "rcc.h"

// System Clock (SYSCLK) Frequency (in Hz)
volatile uint32_t CoreClock = (uint32_t) 0;
// Advanced High Performance Bus (AHB) Frequency (in Hz)
volatile uint32_t AHBClock = (uint32_t) 0;
// Advanced Peripheral Bus 1 (APB1) Frequency (in Hz)
volatile uint32_t APB1Clock = (uint32_t) 0;
// Advanced Peripheral Bus 2 (APB2) Frequency (in Hz)
volatile uint32_t APB2Clock = (uint32_t) 0;

/**
 * @brief Retrieves the frequency of System Clock
 * @return SYSCLK Frequency (in Hz)
 */
uint32_t get_clock_freq(void){
	
	// Final Value
	uint32_t clk_freq = 0;

	// Clock Source
	switch (get_clock_source()){

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
			switch(RCC->CFGR.BIT.PLLSRC){

				// HSE
				case PLL_SRC_HSE:
					clk_freq = HSE_FREQ;
					// PLL Input Clock Prescaler
					if(RCC->CFGR.BIT.PLLXTPRE == PLL_HSE_DIV_2){
						clk_freq /= 2;
					}
				break;

				// HSI
				case PLL_SRC_HSI_DIV_2:
					clk_freq = (uint32_t)(HSI_FREQ / 2);
				break;
			}

			// PLL Multiplication Factor
			switch(RCC->CFGR.BIT.PLLMUL){
				
				case PLL_MUL_2:
					clk_freq *= 2;
				break;

				case PLL_MUL_3:
					clk_freq *= 3;
				break;

				case PLL_MUL_4:
					clk_freq *= 4;
				break;

				case PLL_MUL_5:
					clk_freq *= 5;
				break;

				case PLL_MUL_6:
					clk_freq *= 6;
				break;

				case PLL_MUL_7:
					clk_freq *= 7;
				break;

				case PLL_MUL_8:
					clk_freq *= 8;
				break;

				case PLL_MUL_9:
					clk_freq *= 9;
				break;

				case PLL_MUL_10:
					clk_freq *= 10;
				break;

				case PLL_MUL_11:
					clk_freq *= 11;
				break;

				case PLL_MUL_12:
					clk_freq *= 12;
				break;

				case PLL_MUL_13:
					clk_freq *= 13;
				break;

				case PLL_MUL_14:
					clk_freq *= 14;
				break;

				case PLL_MUL_15:
					clk_freq *= 15;
				break;

				case PLL_MUL_16_0:
					clk_freq *= 16;
				break;

				case PLL_MUL_16_1:
					clk_freq *= 16;
				break;
			}

		break;
	}
	
	// Final Value
	return (uint32_t) clk_freq;
} 

/**
 * @brief Retrieves the frequency of AHB
 * @return AHB Frequency (in Hz)
 */
uint32_t get_AHB_freq(void){
	
	// Current SYSCLK
	uint32_t clk_freq = get_clock_freq();

	// AHB Prescaler Value
	switch(RCC->CFGR.BIT.HPRE){
		
		case AHB_DIV_1:
			clk_freq /= 1; 
		break;

		case AHB_DIV_2:
			clk_freq /= 2; 
		break;

		case AHB_DIV_4:
			clk_freq /= 4; 
		break;

		case AHB_DIV_8:
			clk_freq /= 8; 
		break;

		case AHB_DIV_16:
			clk_freq /= 16; 
		break;

		case AHB_DIV_64:
			clk_freq /= 64; 
		break;

		case AHB_DIV_128:
			clk_freq /= 128; 
		break;

		case AHB_DIV_256:
			clk_freq /= 256; 
		break;

		case AHB_DIV_512:
			clk_freq /= 512; 
		break;
	}
	
	return (uint32_t) clk_freq;
}

/**
 * @brief Retrieves the frequency of the APB1
 * @return APB1 Frequency (in Hz)
 * @note Max Value should not exceed more than 36MHz
 */
uint32_t get_APB1_freq(void){
	// AHB Frequency
	uint32_t clk_freq = get_AHB_freq();

	// APB1 Prescaler
	switch(RCC->CFGR.BIT.PPRE1){
		case APB1_DIV_1:
			clk_freq /= 1;
		break;

		case APB1_DIV_2:
			clk_freq /= 2;
		break;

		case APB1_DIV_4:
			clk_freq /= 4;
		break;

		case APB1_DIV_8:
			clk_freq /= 8;
		break;

		case APB1_DIV_16:
			clk_freq /= 16;
		break;
	}

	return (uint32_t) clk_freq;
}

/**
 * @brief Retrieves the frequency of the APB2
 * @return APB2 Frequency (in Hz)
 */
uint32_t get_APB2_freq(void){
	// AHB Frequency
	uint32_t clk_freq = get_AHB_freq();

	// APB2 Prescaler
	switch(RCC->CFGR.BIT.PPRE2){

		case APB2_DIV_1:
			clk_freq /= 1;
		break;

		case APB2_DIV_2:
			clk_freq /= 2;
		break;

		case APB2_DIV_4:
			clk_freq /= 4;
		break;

		case APB2_DIV_8:
			clk_freq /= 8;
		break;

		case APB2_DIV_16:
			clk_freq /= 16;
		break;
	}

	return (uint32_t) clk_freq;
}

/**
 * @brief Configures PLL parameters
 * @param[in] PLL_SRC PLL Input Source
 * @param[in] PLL_MUL PLL Multiplication Factor
 */
static void config_PLL(PLL_CLK_SRC_ENUM PLL_SRC, uint8_t PLL_MUL){
	
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
static void config_SYS_72MHz(void){
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
	CoreClock = get_clock_freq();
	AHBClock = get_AHB_freq();
	APB1Clock = get_APB1_freq();
	APB2Clock = get_APB2_freq();
}

/**
 * @brief Configures System Clock (SYSCLK)
 * @param[in] CLK_FREQ Core Clock Frequency `SYSCLK_FREQ`
 * @note - PLL as System Clock Source 
 * @note - HSE is used for PLL Clock Source
 */
void config_SYSCLK_MHz(SYSCLK_FREQ CLK_FREQ){

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
			FLASH->ACR.REG |= (uint32_t) FLASH_ZERO_WAIT;
            // Configure PLL parameters
			config_PLL(HSE_DIV_1, PLL_MUL_2);
        break;

        // 24MHz
        case SYSCLK_24MHz:
			// Zero wait state, if SYSCLK <= 24 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_ZERO_WAIT;
            // Configure PLL parameters
			config_PLL(HSE_DIV_1, PLL_MUL_3);
        break;

        // 32MHz
        case SYSCLK_32MHz:
			// One wait state, if 24 MHz < SYSCLK <= 48 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_ONE_WAIT;
            // Configure PLL parameters
			config_PLL(HSE_DIV_1, PLL_MUL_4);
        break;

        // 40MHz
        case SYSCLK_40MHz:
			// One wait state, if 24 MHz < SYSCLK <= 48 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_ONE_WAIT;
            // Configure PLL parameters
			config_PLL(HSE_DIV_1, PLL_MUL_5);
        break;

        // 48MHz
        case SYSCLK_48MHz:
			// One wait state, if 24 MHz < SYSCLK <= 48 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_ONE_WAIT;
			// Configure PLL parameters
			config_PLL(HSE_DIV_1, PLL_MUL_6);
        break;

        // 56MHz
        case SYSCLK_56MHz:
			// Two wait states, if 48 MHz < SYSCLK <= 72 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_TWO_WAIT;
			// Configure PLL parameters
            config_PLL(HSE_DIV_1, PLL_MUL_7);
        break;

        // 64MHz
        case SYSCLK_64MHz:
			// Two wait states, if 48 MHz < SYSCLK <= 72 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_TWO_WAIT;
			// Configure PLL parameters
            config_PLL(HSE_DIV_1, PLL_MUL_8);
        break;

        // 72MHz
        case SYSCLK_72MHz:
			// Two wait states, if 48 MHz < SYSCLK <= 72 MHz
			FLASH->ACR.REG |= (uint32_t) FLASH_TWO_WAIT;
            // Configure PLL parameters
			config_PLL(HSE_DIV_1, PLL_MUL_9);
			
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
		config_BUS(AHB_DIV_1, APB1_DIV_2, APB2_DIV_1);
	}
	else{
		config_BUS(AHB_DIV_1, APB1_DIV_1, APB2_DIV_1);
	}

	// Software Selection of PLL
	RCC->CFGR.BIT.SW = SW_CLK_PLL;
	// Confirmation by Hardware
	while(RCC->CFGR.BIT.SWS != RCC->CFGR.BIT.SW);

	// Store the Frequency
	CoreClock = get_clock_freq();
	AHBClock = get_AHB_freq();
	APB1Clock = get_APB1_freq();
	APB2Clock = get_APB2_freq();
}
