// Header Guards
#ifndef __NVIC_REG_MAP_H__
#define __NVIC_REG_MAP_H__

// Core C Library
#include <stdint.h>

// NVIC Structures
typedef struct {
    // Interrupt Set-Enable Registers (ISER)
    uint32_t ISER[8];
} NVIC_IRQ_SET_REG_STRUCT;

typedef struct {
    // Interrupt Clear-Enable Registers (ISER)
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

#endif  /* __NVIC_REG_MAP_H__ */