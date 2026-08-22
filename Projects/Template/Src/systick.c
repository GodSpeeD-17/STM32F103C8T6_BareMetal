#include "systick.h"

#include "stm32f1xx.h"

/** @brief Maximum reload period admitted by the 24-bit SysTick counter @def SYSTICK_RELOAD_PERIOD_MAX */
#define SYSTICK_RELOAD_PERIOD_MAX			((uint32_t) 0x01000000UL)

static volatile uint32_t appTickCount = 0UL;

driver_status_t SysTick_Config
(
	const frequency_t inputClockHz,
	const frequency_t tickFrequencyHz
)
{
	frequency_t reloadPeriod = 0UL;

	if ((inputClockHz == 0UL) ||
		(tickFrequencyHz == 0UL) ||
		(tickFrequencyHz > inputClockHz) ||
		((inputClockHz % tickFrequencyHz) != 0UL))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	reloadPeriod = inputClockHz / tickFrequencyHz;
	if ((reloadPeriod == 0UL) || (reloadPeriod > SYSTICK_RELOAD_PERIOD_MAX))
	{
		return DRIVER_STATUS_ERROR_INVALID_ARG;
	}

	//! Stop SysTick before replacing the complete timebase configuration.
	SysTick->CTRL.REG = 0x00000000UL;
	SysTick->LOAD = (reg) (reloadPeriod - 1UL);
	SysTick->VAL = 0x00000000UL;
	SysTick->CTRL.REG = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;

	return DRIVER_STATUS_SUCCESS;
}

void SysTick_Enable(void)
{
	SysTick->CTRL.REG |= SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Disable(void)
{
	SysTick->CTRL.REG &= ~SysTick_CTRL_ENABLE_Msk;
}

uint32_t SysTick_GetTicks(void)
{
	return appTickCount;
}

void SysTick_ResetTicks(void)
{
	appTickCount = 0UL;
	SysTick->VAL = 0x00000000UL;
}

driver_status_t SysTick_GetOperationState(void)
{
	if ((SysTick->CTRL.REG & SysTick_CTRL_ENABLE_Msk) == 0UL)
	{
		return DRIVER_STATUS_OFF;
	}

	return DRIVER_STATUS_ON;
}

void SysTick_Handler(void)
{
	appTickCount++;
}
