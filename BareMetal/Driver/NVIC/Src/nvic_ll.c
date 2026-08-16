/**
 * @file	nvic_ll.c
 * @author	Shrey Shah
 * @brief	NVIC Low-Level Register Implementation
 * @version	v1.0
 * @date	16-08-2026
 *
 * @details
 * Each function performs exactly one raw register access. Callers own target
 * validation, write-one action policy, sequencing, and synchronization.
 */

#include "nvic_ll.h"

reg LL_NVIC_ReadISER(const uint8_t registerIndex)
{
	//! Capture one complete enable-state bank without interpreting its bits.
	return NVIC->ISER[registerIndex];
}

void LL_NVIC_WriteISER(const uint8_t registerIndex, const reg actionMask)
{
	//! Forward the action mask as one direct write-one-to-set transfer.
	NVIC->ISER[registerIndex] = actionMask;
}

void LL_NVIC_WriteICER(const uint8_t registerIndex, const reg actionMask)
{
	//! Forward the action mask as one direct write-one-to-clear transfer.
	NVIC->ICER[registerIndex] = actionMask;
}

reg LL_NVIC_ReadISPR(const uint8_t registerIndex)
{
	//! Capture one complete pending-state bank without interpreting its bits.
	return NVIC->ISPR[registerIndex];
}

void LL_NVIC_WriteICPR(const uint8_t registerIndex, const reg actionMask)
{
	//! Forward the action mask as one direct pending-clear transfer.
	NVIC->ICPR[registerIndex] = actionMask;
}

reg LL_NVIC_ReadIABR(const uint8_t registerIndex)
{
	//! Capture one complete active-state bank without interpreting its bits.
	return NVIC->IABR[registerIndex];
}

reg_field_t LL_NVIC_ReadIPR(const irq_t IRQn)
{
	//! Read only the byte owned by the selected external IRQ.
	return NVIC->IPR[IRQn];
}

void LL_NVIC_WriteIPR(const irq_t IRQn, const reg_field_t priorityFieldImage)
{
	//! Write only the byte owned by the selected external IRQ.
	NVIC->IPR[IRQn] = priorityFieldImage;
}

void LL_NVIC_WriteSTIR(const irq_t IRQn)
{
	//! Forward the validated interrupt identifier as one action-only transfer.
	NVIC->STIR = (reg) IRQn;
}

reg LL_SCB_ReadAIRCR(void)
{
	//! Capture the complete AIRCR image for caller-owned Codec staging.
	return SCB->AIRCR;
}

void LL_SCB_WriteAIRCR(const reg aircrRegImage)
{
	//! Commit the caller-staged keyed AIRCR image in one transfer.
	SCB->AIRCR = aircrRegImage;
}
