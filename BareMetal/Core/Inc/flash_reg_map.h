// Header Guards
#ifndef __FLASH_REG_MAP_H__
#define __FLASH_REG_MAP_H__

#include "common.h"

// Basic MACROS
#define FLASH_ZERO_WAIT                     ((uint8_t) 0x00)    //  0 < SYSCLK ≤ 24 MHz
#define FLASH_ONE_WAIT                      ((uint8_t) 0x01)    // 24 MHz < SYSCLK ≤ 48 MHz
#define FLASH_TWO_WAIT                      ((uint8_t) 0x02)    // 48 MHz < SYSCLK ≤ 72 MHz

// Flash Structure
typedef struct {
    // Flash Access Control Register (ACR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            uint32_t LATENCY: 3;
            uint32_t HLFCYA: 1;
            uint32_t PRFTBE: 1;
            uint32_t PRFTBS: 1;
            uint32_t reserved: 26;
        } BIT;
    } ACR;
    // FPEC Key Register (KEYR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            uint32_t demo: 1;
        } BIT;
    } KEYR;
    // Flash OPTKEY Register 
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            uint32_t demo: 1;
        } BIT;
    } OPTKEYR;
    // 
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            uint32_t demo: 1;
        } BIT;
    } SR;
    // 
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            uint32_t demo: 1;
        } BIT;
    } AR;
    // RESERVED
    uint32_t RESERVED;
    // 
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            uint32_t demo: 1;
        } BIT;
    } OBR;
    // 
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            uint32_t demo: 1;
        } BIT;
    } WRPR;
} FLASH_REG_STRUCT;


#endif /* __FLASH_REG_MAP_H__ */