// Header Guards
#ifndef __NVIC_REG_MAP_H__
#define __NVIC_REG_MAP_H__

#include "common.h"

// NVIC Structures
typedef struct {
    // Interrupt Set-Enable Registers (ISER)
    uint32_t ISER[8];
} NVIC_IRQ_SET_REG_STRUCT;

typedef struct {
    // Interrupt Clear-Enable Registers (ICER)
    uint32_t ICER[8];
} NVIC_IRQ_CLEAR_REG_STRUCT;

typedef struct {
    // Interrupt Set-Pending Register (ISPR)
    uint32_t ISPR[8];
} NVIC_IRQ_SET_PEND_REG_STRUCT;

typedef struct {
    // Interrupt Clear-Pending Register (ICPR)
    uint32_t ICPR[8];
} NVIC_IRQ_CLEAR_PEND_REG_STRUCT;

// NVIC Register Structure
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
} NVIC_REG_STRUCT;

#endif  /* __NVIC_REG_MAP_H__ */
