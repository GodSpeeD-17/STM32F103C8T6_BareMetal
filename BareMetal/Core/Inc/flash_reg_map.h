// Header Guards
#ifndef __FLASH_REG_MAP_H__
#define __FLASH_REG_MAP_H__

// MACROS
#include "common.h"

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