// Header Guards
#ifndef __GPIO_REG_MAP_H__
#define __GPIO_REG_MAP_H__

// Core C Library
#include <stdint.h>

// Generic
#define BIT_SET                            ((uint8_t) 0x01)
#define BIT_RESET                          ((uint8_t) 0x00)

// GPIO Main Structure
typedef struct {
    // Control Register Low (CRL)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t MODE0 : 2;
            volatile uint32_t CNF0 : 2;
            volatile uint32_t MODE1 : 2;
            volatile uint32_t CNF1 : 2;
            volatile uint32_t MODE2 : 2;
            volatile uint32_t CNF2 : 2;
            volatile uint32_t MODE3 : 2;
            volatile uint32_t CNF3 : 2;
            volatile uint32_t MODE4 : 2;
            volatile uint32_t CNF4 : 2;
            volatile uint32_t MODE5 : 2;
            volatile uint32_t CNF5 : 2;
            volatile uint32_t MODE6 : 2;
            volatile uint32_t CNF6 : 2;
            volatile uint32_t MODE7 : 2;
            volatile uint32_t CNF7 : 2;
        } BIT;
    } CRL;
    // Control Register High (CRH)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t MODE8 : 2;
            volatile uint32_t CNF8 : 2;
            volatile uint32_t MODE9 : 2;
            volatile uint32_t CNF9 : 2;
            volatile uint32_t MODE10 : 2;
            volatile uint32_t CNF10 : 2;
            volatile uint32_t MODE11 : 2;
            volatile uint32_t CNF11 : 2;
            volatile uint32_t MODE12 : 2;
            volatile uint32_t CNF12 : 2;
            volatile uint32_t MODE13 : 2;
            volatile uint32_t CNF13 : 2;
            volatile uint32_t MODE14 : 2;
            volatile uint32_t CNF14 : 2;
            volatile uint32_t MODE15 : 2;
            volatile uint32_t CNF15 : 2;
        } BIT;
    } CRH;
    // Input Data Register (IDR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t IDR0 : 1;
            volatile uint32_t IDR1 : 1;
            volatile uint32_t IDR2 : 1;
            volatile uint32_t IDR3 : 1;
            volatile uint32_t IDR4 : 1;
            volatile uint32_t IDR5 : 1;
            volatile uint32_t IDR6 : 1;
            volatile uint32_t IDR7 : 1;
            volatile uint32_t IDR8 : 1;
            volatile uint32_t IDR9 : 1;
            volatile uint32_t IDR10 : 1;
            volatile uint32_t IDR11 : 1;
            volatile uint32_t IDR12 : 1;
            volatile uint32_t IDR13 : 1;
            volatile uint32_t IDR14 : 1;
            volatile uint32_t IDR15 : 1;
            volatile uint32_t reserved : 16;
        } BIT;
    } IDR;
    // Output Data Register (ODR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t ODR0 : 1;
            volatile uint32_t ODR1 : 1;
            volatile uint32_t ODR2 : 1;
            volatile uint32_t ODR3 : 1;
            volatile uint32_t ODR4 : 1;
            volatile uint32_t ODR5 : 1;
            volatile uint32_t ODR6 : 1;
            volatile uint32_t ODR7 : 1;
            volatile uint32_t ODR8 : 1;
            volatile uint32_t ODR9 : 1;
            volatile uint32_t ODR10 : 1;
            volatile uint32_t ODR11 : 1;
            volatile uint32_t ODR12 : 1;
            volatile uint32_t ODR13 : 1;
            volatile uint32_t ODR14 : 1;
            volatile uint32_t ODR15 : 1;
            volatile uint32_t reserved : 16;
        } BIT;
    } ODR;
    // Bit Set/Reset Register (BSRR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t BS0 : 1;
            volatile uint32_t BS1 : 1;
            volatile uint32_t BS2 : 1;
            volatile uint32_t BS3 : 1;
            volatile uint32_t BS4 : 1;
            volatile uint32_t BS5 : 1;
            volatile uint32_t BS6 : 1;
            volatile uint32_t BS7 : 1;
            volatile uint32_t BS8 : 1;
            volatile uint32_t BS9 : 1;
            volatile uint32_t BS10 : 1;
            volatile uint32_t BS11 : 1;
            volatile uint32_t BS12 : 1;
            volatile uint32_t BS13 : 1;
            volatile uint32_t BS14 : 1;
            volatile uint32_t BS15 : 1;
            volatile uint32_t BR0 : 1;
            volatile uint32_t BR1 : 1;
            volatile uint32_t BR2 : 1;
            volatile uint32_t BR3 : 1;
            volatile uint32_t BR4 : 1;
            volatile uint32_t BR5 : 1;
            volatile uint32_t BR6 : 1;
            volatile uint32_t BR7 : 1;
            volatile uint32_t BR8 : 1;
            volatile uint32_t BR9 : 1;
            volatile uint32_t BR10 : 1;
            volatile uint32_t BR11 : 1;
            volatile uint32_t BR12 : 1;
            volatile uint32_t BR13 : 1;
            volatile uint32_t BR14 : 1;
            volatile uint32_t BR15 : 1;
        } BIT;
    } BSRR;
    // Bit Reset Register (BRR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t BR0 : 1;
            volatile uint32_t BR1 : 1;
            volatile uint32_t BR2 : 1;
            volatile uint32_t BR3 : 1;
            volatile uint32_t BR4 : 1;
            volatile uint32_t BR5 : 1;
            volatile uint32_t BR6 : 1;
            volatile uint32_t BR7 : 1;
            volatile uint32_t BR8 : 1;
            volatile uint32_t BR9 : 1;
            volatile uint32_t BR10 : 1;
            volatile uint32_t BR11 : 1;
            volatile uint32_t BR12 : 1;
            volatile uint32_t BR13 : 1;
            volatile uint32_t BR14 : 1;
            volatile uint32_t BR15 : 1;
            volatile uint32_t reserved : 16;
        } BIT;
    } BRR;
    // Lock Register (LCKR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t LCK0 : 1;
            volatile uint32_t LCK1 : 1;
            volatile uint32_t LCK2 : 1;
            volatile uint32_t LCK3 : 1;
            volatile uint32_t LCK4 : 1;
            volatile uint32_t LCK5 : 1;
            volatile uint32_t LCK6 : 1;
            volatile uint32_t LCK7 : 1;
            volatile uint32_t LCK8 : 1;
            volatile uint32_t LCK9 : 1;
            volatile uint32_t LCK10 : 1;
            volatile uint32_t LCK11 : 1;
            volatile uint32_t LCK12 : 1;
            volatile uint32_t LCK13 : 1;
            volatile uint32_t LCK14 : 1;
            volatile uint32_t LCK15 : 1;
            volatile uint32_t LCKK : 1;
            volatile uint32_t reserved : 15;
        } BIT;
    } LCKR;
} GPIO_REG_STRUCT;

#endif /* __GPIO_REG_MAP_H__ */