// Header Guards
#ifndef STM32F1XX_FLASH_H_
#define STM32F1XX_FLASH_H_

// C++ Safeguards
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// Includes
#include <stdint.h>

// Flash Structure
typedef volatile struct __FLASH_TypeDef 
{
    // Flash Access Control Register (ACR)
    union {
        // Full 32-bit Register Access
        volatile uint32_t REG;
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
        volatile uint32_t REG;
        // Bit Access
        struct {
            uint32_t demo: 1;
        } BIT;
    } KEYR;
    // Flash OPTKEY Register 
    union {
        // Full 32-bit Register Access
        volatile uint32_t REG;
        // Bit Access
        struct {
            uint32_t demo: 1;
        } BIT;
    } OPTKEYR;
    // 
    union {
        // Full 32-bit Register Access
        volatile uint32_t REG;
        // Bit Access
        struct {
            uint32_t demo: 1;
        } BIT;
    } SR;
    // 
    union {
        // Full 32-bit Register Access
        volatile uint32_t REG;
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
        volatile uint32_t REG;
        // Bit Access
        struct {
            uint32_t demo: 1;
        } BIT;
    } OBR;
    // 
    union {
        // Full 32-bit Register Access
        volatile uint32_t REG;
        // Bit Access
        struct {
            uint32_t demo: 1;
        } BIT;
    } WRPR;
} FLASH_TypeDef;

// C++ Safeguards
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_FLASH_H_ */