/**
 * @file	bsp.h
 * @author	Shrey Shah
 * @brief	Aggregates the BSP capabilities selected by the build
 * @version	v1.0
 * @date	26-08-2026
 *
 * @details
 * This compatibility interface exposes only the board capabilities selected
 * by CMake. New consumers include `bsp_gpio.h` or `bsp_usart.h` directly so
 * their compile-time dependency remains explicit. BSP-owned capability macros,
 * rather than application-owned `APP_ENABLE_*` policy, control this aggregate.
 */

// Header Guard
#ifndef BSP_H_
#define BSP_H_

#if defined(BSP_GPIO_CAPABILITY_ENABLED)
#include "bsp_gpio.h"
#endif /* BSP_GPIO_CAPABILITY_ENABLED */

#if defined(BSP_USART_CAPABILITY_ENABLED)
#include "bsp_usart.h"
#endif /* BSP_USART_CAPABILITY_ENABLED */

#endif /* BSP_H_ */
