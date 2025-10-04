// --- Header Guards --- //
#ifndef __STM32F1XX_NVIC_H__
#define __STM32F1XX_NVIC_H__

// ---- Includes ---- //
#include "common.h"

/**
 * @brief NVIC Register Structure
 * @brief Contains register sequencing
 */
typedef struct {
	// Interrupt Set-Enable Registers (ISER)
	uint32_t ISER[8];
	// Reserved
	uint32_t RESERVED_0[24];
	// Interrupt Clear-Enable Registers (ICER)
	uint32_t ICER[8];
	// Reserved
	uint32_t RESERVED_1[24];
	// Interrupt Set-Pending Register (ISPR)
	uint32_t ISPR[8];
	// Reserved
	uint32_t RESERVED_2[24];
	// Interrupt Clear-Pending Register (ICPR)
	uint32_t ICPR[8];
	// Reserved
	uint32_t RESERVED_3[24];
	// Interrupt Active Bit Register (IABR)
	uint32_t IABR[8];
	// Reserved
	uint32_t RESERVED_4[56];
	// Interrupt Priority Registers (IPR)
	uint32_t IPR[60];
	// Reserved
	uint32_t RESERVED_5[644];
	// Software Trigger Interrupt Register (STIR)
	uint32_t STIR;
} NVIC_TypeDef;

#endif /* __STM32F1XX_NVIC_H__ */
