// --- Header Guards --- //
#ifndef STM32F1XX_NVIC_H_
#define STM32F1XX_NVIC_H_

// C++ Safeguards
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ---- Includes ---- //
#include <stdint.h>

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

// C++ Safeguards
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_NVIC_H_ */