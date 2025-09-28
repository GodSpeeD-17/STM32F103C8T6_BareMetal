/***************************************************************************************
 *  File: rcc.h
 *  Created on: 14/09/2024
 *  Author: Shrey Shah
 ***************************************************************************************/

// Header Guards
#ifndef __RCC_H__
#define __RCC_H__

// Header File
#include "rcc_config.h"

// System Frequency Tracker
extern rcc_clk_freq_t __systemFrequency__;

/**
 * @brief RCC Flash Configuration
 * @param flash Flash Configuration Structure `rcc_flash_config_t` 
 * @param reg Pointer to `FLASH->ACR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_FlashConfig(const rcc_flash_config_t flash, uint32_t* reg);

/**
 * @brief RCC PLL Configuration
 * @param pllConfig  PLL Configuration Structure
 * @param reg Pointer to `RCC->CFGR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_PLLConfig(const rcc_pll_config_t pllConfig, uint32_t* reg);

/**
 * @brief RCC Bus Prescaler Configuration
 * @param busConfig Bus Configuration Structure 
 * @param reg Pointer to `RCC->CFGR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success 
 */
driver_status_t RCC_BusConfig(const rcc_bus_prescaler_config_t busPrescalerConfig, uint32_t* reg);

/**
 * @brief RCC Component Configuration - ADC, USB
 * @param componentPrescalerConfig Compoennt Prescaler Configuration Structure  
 * @param reg Pointer to `RCC->CFGR.REG`
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success 
 */
driver_status_t RCC_ComponentConfig(const rcc_component_prescaler_config_t componentPrescalerConfig, uint32_t* reg);

/**
 * @brief RCC Clock Configuration
 * @param rccConfig RCC Clock Configuration Structure 
 * @return Status of operation
 * @return - `DRIVER_FAIL`: Failure
 * @return - `DRIVER_SUCCESS`: Success
 */
driver_status_t RCC_Config(const rcc_config_t* rccConfig);

/**
 * @brief Sets default flash configuration for 72MHz
 * @param flashConfig Pointer to Flash Configuration Structure 
 */
void RCC_72MHz_FlashDefaultConfig(rcc_flash_config_t* flashConfig);

/**
 * @brief PLL Default Configuration for 72MHz
 * @param pllConfig Pointer to PLL Configuration Structure
 */
void RCC_72MHz_PLLDefaultConfig(rcc_pll_config_t* pllConfig);

/**
 * @brief Sets System Configuration for 72MHz Clock
 * @param sysClkConfig Pointer to System Clock
 */
void RCC_72MHz_SystemDefaultConfig(rcc_sys_clk_config_t* sysClkConfig);

/**
 * @brief Sets Bus Prescaler for 72MHz
 * @param busPrescalerConfig Pointer to Bus Prescaler Configuration Structure
 */
void RCC_72MHz_BusPrescalerDefaultConfig(rcc_bus_prescaler_config_t* busPrescalerConfig);

/**
 * @brief Sets Component Prescaler for 72MHz
 * @param componentPrescalerConfig Pointer to Component Prescaler Configuration Structure
 */
void RCC_72MHz_ComponentPrescalerDefaultConfig(rcc_component_prescaler_config_t* componentPrescalerConfig);

/**
 * @brief Sets RCC Configuration 72MHz
 * @param rccConfig RCC Configuration Structure 
 */
void RCC_72MHz_LoadDefaultConfig(rcc_config_t* rccConfig);

/**
 * @brief Shortcut Function to set Clock Frequency to 72MHz
 */
__STATIC_INLINE__ driver_status_t RCC_Config_72MHz(void){
	static rcc_config_t rcc72MHzConfig = {0};
	RCC_72MHz_LoadDefaultConfig(&rcc72MHzConfig);
	driver_status_t status = RCC_Config(&rcc72MHzConfig);
	ASSERT_DRIVER_STATUS(status);
	return status;
}

/**
 * @brief Retrieves RCC Core Clock Frequency in Hz
 * @note This is the clock which is being fed to AHB Prescaler 
 */
__STATIC_INLINE__ freq_t RCC_CoreClockFreq_Get(void){
	return (__systemFrequency__.Core); 
}

/**
 * @brief Retrieves RCC AHB Clock Frequency in Hz
 * @note This is the clock which is being fed to APB1/APB2 Prescaler 
 */
__STATIC_INLINE__ freq_t RCC_AHBClockFreq_Get(void){
	return (__systemFrequency__.AHB);
}

/**
 * @brief Retrieves RCC APB1 Clock Frequency in Hz
 * @note This is the clock which is being fed to APB1 Peripherals 
 */
__STATIC_INLINE__ freq_t RCC_APB1ClockFreq_Get(void){
	return (__systemFrequency__.APB1);
}

/**
 * @brief Retrieves RCC APB2 Clock Frequency in Hz
 * @note This is the clock which is being fed to APB2 Peripherals 
 */
__STATIC_INLINE__ freq_t RCC_APB2ClockFreq_Get(void){
	return (__systemFrequency__.APB2);
}

#ifdef __OLD_RCC_METHOD__
/**
 * @brief Configures RCC
 * @param configX RCC Configuration Structure
 */
void RCC_Config(rcc_config_t* configX);

/**
 * @brief Loads `rcc_config_t` with PLL 72MHz configuration
 * @param configX Pointer to `rcc_config_t` structure to be configured
 */
void RCC_Config_Load_72MHz(rcc_config_t* configX);

/**
 * @brief Configures System to run at 72MHz
 */
void RCC_Config_72MHz();
#endif /* __OLD_RCC_METHOD__ */

#endif /* __RCC_H__ */
