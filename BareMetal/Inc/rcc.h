/***************************************************************************************
 *  File: rcc.h
 *  Created on: 14/09/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __RCC_H__
#define __RCC_H__

// Register Address Mapping
#include "reg_map.h"

// Generic Frequencies (used for PWM)
#define FREQ_12Hz               		((uint32_t) (12))   
#define FREQ_25Hz               		((uint32_t) ((2 * FREQ_12Hz) + (uint32_t) 1))   
#define FREQ_50Hz               		((uint32_t) (2 * FREQ_25Hz))   
#define FREQ_100Hz               		((uint32_t) (2 * FREQ_50Hz))   
#define FREQ_500Hz               		((uint32_t) (5 * FREQ_100Hz))   
#define FREQ_1kHz                		((uint32_t) (10 * FREQ_100Hz))   
#define FREQ_2kHz                		((uint32_t) (2 * FREQ_1kHz))   
#define FREQ_5kHz                		((uint32_t) (5 * FREQ_1kHz))   
#define FREQ_10kHz               		((uint32_t) (10 * FREQ_1kHz))   
#define FREQ_50kHz               		((uint32_t) (50 * FREQ_1kHz))   
#define FREQ_72kHz               		((uint32_t) (72 * FREQ_1kHz))   
#define FREQ_100kHz              		((uint32_t) (100 * FREQ_1kHz))   
#define FREQ_200kHz              		((uint32_t) (2 * FREQ_100kHz)) 
#define FREQ_1MHz						((uint32_t) (FREQ_1kHz * FREQ_1kHz))
#define FREQ_10MHz						((uint32_t) (10 * FREQ_1MHz))

// Clock Speed
#define HSI_FREQ						((uint32_t) (8 * FREQ_1MHz))
#define HSE_FREQ						((uint32_t) (8 * FREQ_1MHz))
#define PLL_MIN_FREQ					((uint32_t) (16 * FREQ_1MHz))
#define PLL_MAX_FREQ					((uint32_t) (72 * FREQ_1MHz))

// Clock Source
#define SW_CLK_HSI                     	((uint8_t) 0)
#define SW_CLK_HSE                     	((uint8_t) 1)
#define SW_CLK_PLL                     	((uint8_t) 2)

// AHB Prescaler
#define AHB_DIV_1                       ((uint8_t) 0x0)
#define AHB_DIV_2                       ((uint8_t) 0x8)
#define AHB_DIV_4                       ((uint8_t) 0x9)
#define AHB_DIV_8                       ((uint8_t) 0xA)
#define AHB_DIV_16                      ((uint8_t) 0xB)
#define AHB_DIV_64                      ((uint8_t) 0xC)
#define AHB_DIV_128                     ((uint8_t) 0xD)
#define AHB_DIV_256                     ((uint8_t) 0xE)
#define AHB_DIV_512                     ((uint8_t) 0xF)

// APB1 Prescaler
#define APB1_DIV_1                      ((uint8_t) 0x3)
#define APB1_DIV_2                      ((uint8_t) 0x4)
#define APB1_DIV_4                      ((uint8_t) 0x5)
#define APB1_DIV_8                      ((uint8_t) 0x6)
#define APB1_DIV_16                     ((uint8_t) 0x7)

// APB2 Prescaler
#define APB2_DIV_1                      ((uint8_t) 0x3)
#define APB2_DIV_2                      ((uint8_t) 0x4)
#define APB2_DIV_4                      ((uint8_t) 0x5)
#define APB2_DIV_8                      ((uint8_t) 0x6)
#define APB2_DIV_16                     ((uint8_t) 0x7)

// ADC Prescaler
#define ADC_DIV_2                       ((uint8_t) 0x0)
#define ADC_DIV_4                       ((uint8_t) 0x1)
#define ADC_DIV_6                       ((uint8_t) 0x2)
#define ADC_DIV_8                       ((uint8_t) 0x3)

// PLL Clock Source
#define PLL_SRC_HSI_DIV_2               ((uint8_t) 0)
#define PLL_SRC_HSE                     ((uint8_t) 1)

// PLL Clock Source Prescaler
#define PLL_HSE_DIV_1                   ((uint8_t) 0)
#define PLL_HSE_DIV_2                   ((uint8_t) 1)

// PLL Multiplication Factor
#define PLL_MUL_2                       ((uint8_t) 0x0)
#define PLL_MUL_3                       ((uint8_t) 0x1)
#define PLL_MUL_4                       ((uint8_t) 0x2)
#define PLL_MUL_5                       ((uint8_t) 0x3)
#define PLL_MUL_6                       ((uint8_t) 0x4)
#define PLL_MUL_7                       ((uint8_t) 0x5)
#define PLL_MUL_8                       ((uint8_t) 0x6)
#define PLL_MUL_9                       ((uint8_t) 0x7)
#define PLL_MUL_10                      ((uint8_t) 0x8)
#define PLL_MUL_11                      ((uint8_t) 0x9)
#define PLL_MUL_12                      ((uint8_t) 0xA)
#define PLL_MUL_13                      ((uint8_t) 0xB)
#define PLL_MUL_14                      ((uint8_t) 0xC)
#define PLL_MUL_15                      ((uint8_t) 0xD)
#define PLL_MUL_16_0                    ((uint8_t) 0xE)
#define PLL_MUL_16_1                    ((uint8_t) 0xF)

// USB Prescaler
#define USB_DIV_1_5                     ((uint8_t) 0)
#define USB_DIV_1                       ((uint8_t) 1)

// Enable Alternate Function
#define RCC_AF_ENABLE()              	(RCC->APB2ENR.BIT.AFIOEN = BIT_SET)

// PLL Clock Source
typedef enum {
	HSE_DIV_1 = (uint8_t)0XAA,
	HSE_DIV_2 = (uint8_t)0XBB,
	HSI_DIV_2 = (uint8_t)0XCC,
} PLL_CLK_SRC_ENUM;

// System Clock Frequency
typedef enum {
	SYSCLK_16MHz = (uint8_t) 1,
	SYSCLK_24MHz,
	SYSCLK_32MHz,
	SYSCLK_40MHz,
	SYSCLK_48MHz,
	SYSCLK_56MHz,
	SYSCLK_64MHz,
	SYSCLK_72MHz,
} SYSCLK_FREQ;

/***
 * @brief Retrieves the System Clock Source
 * @note Possible Return Values: `SYS_CLK_HSI`, `SYS_CLK_HSE`, `SYS_CLK_PLL`
 */
uint8_t get_clock_source(void);

/**
 * @brief Retrieves the current System Clock
 * @return SYSCLK Frequency (in Hz)
 */
uint32_t get_clock_freq(void);

/**
 * @brief Retrieves the frequency of AHB
 * @return AHB Frequency (in Hz)
 */
uint32_t get_AHB_freq(void);

/**
 * @brief Retrieves the frequency of the APB1
 * @return APB1 Frequency (in Hz)
 * @note Max Value should not exceed more than 36MHz
 */
uint32_t get_APB1_freq(void);

/**
 * @brief Retrieves the frequency of the APB2
 * @return APB2 Frequency (in Hz)
 */
uint32_t get_APB2_freq(void);

/**
 * @brief Configures PLL parameters
 * @param[in] PLL_SRC PLL Input Source
 * @param[in] PLL_MUL PLL Multiplication Factor
 */
static void config_PLL(PLL_CLK_SRC_ENUM PLL_SRC, uint8_t PLL_MUL);

/**
 * @brief Updates the Peripheral Bus Prescaler
 * @param[in] AHB_PRE  AHB Prescaler `AHB_DIV_X`
 * @param[in] APB1_PRE APB1 Prescaler `APB1_DIV_X`
 * @param[in] APB2_PRE APB2 Prescaler `APB2_DIV_X`
 */
static void config_BUS(uint8_t AHB_PRE, uint8_t APB1_PRE, uint8_t APB2_PRE);

/**
 * @brief Reference Working Code
 */
static void config_SYS_72MHz(void);

/**
 * @brief Wrapper Function to create abstraction for System Core Clock Updation
 * @param[in] CLK_FREQ Core Clock Frequency `SYSCLK_FREQ`
 * @note - PLL as System Clock Source 
 * @note - HSE is used for PLL Clock Source
 */
void config_SYSCLK_MHz(SYSCLK_FREQ CLK_FREQ);

#endif /* __RCC_H__ */
