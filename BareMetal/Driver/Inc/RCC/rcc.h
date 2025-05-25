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
 * @brief Configures RCC
 * @param configX RCC Configuration Structure
 */
void RCC_Config(rcc_config_t* configX);

/**
 * @brief Configures System to run at 72MHz
 */
void RCC_Config_72MHz();

#endif /* __RCC_H__ */
