/**
 * @file	bsp.c
 * @author	Shrey Shah
 * @brief	Board Support Package Implementation
 * @version	v1.0
 * @date	31-05-2026
 *
 * @details
 * This source owns board-specific behavior for the selected STM32F103C8T6
 * target. Generic GPIO driver code stays board-agnostic.
 */

// ==================================================================================================== //
//												Includes												//
// ==================================================================================================== //
#include "bsp.h"

#ifdef STM32F103C8T6__

// ==================================================================================================== //
//										On-Board LED APIs												//
// ==================================================================================================== //

driver_status_t OB_LED_Init(void)
{
	return GPIO_LED_Init(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

void OB_LED_Set(void)
{
	(void) GPIO_PinReset(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

void OB_LED_Reset(void)
{
	(void) GPIO_PinSet(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

void OB_LED_Toggle(void)
{
	(void) GPIO_PinToggle(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

driver_status_t OB_LED_Deinit(void)
{
	return GPIO_Deinit(GPIO_OB_LED_PORT, GPIO_OB_LED_PIN);
}

#endif /* STM32F103C8T6__ */
