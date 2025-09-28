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
