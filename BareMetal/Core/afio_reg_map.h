// Header Guards
#ifndef __AFIO_REG_MAP_H__
#define __AFIO_REG_MAP_H__

#include "common.h"

// Alternate Function Input Output
typedef struct {
    // Event Control Register (EVCR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t PIN: 4;
            volatile uint32_t PORT: 3;
            volatile uint32_t EVOE: 1;
            volatile uint32_t reserved: 24;
            
        } BIT;
    } EVCR;
    // AF Remap and Debug I/O Configuration Register (MAPR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t SPI1_REMAP: 1;
            volatile uint32_t I2C1_REMAP: 1;
            volatile uint32_t USART1_REMAP: 1;
            volatile uint32_t USART2_REMAP: 1;
            volatile uint32_t USART3_REMAP: 2;
            volatile uint32_t TIM1_REMAP: 2;
            volatile uint32_t TIM2_REMAP: 2;
            volatile uint32_t TIM3_REMAP: 2;
            volatile uint32_t TIM4_REMAP: 1;
            volatile uint32_t CAN_REMAP: 2;
            volatile uint32_t PD01_REMAP: 1;
            volatile uint32_t TIM5CH4_IREMAP: 1;
            volatile uint32_t ADC1_ETRGINJ_REMAP: 1;
            volatile uint32_t ADC1_ETGREG_REMAP: 1;
            volatile uint32_t ADC2_ETRGINJ_REMAP: 1;
            volatile uint32_t ADC2_ETGREG_REMAP: 1;
            volatile uint32_t reserved_1: 3;
            volatile uint32_t SWJ_CFG: 3;
            volatile uint32_t reserved_2: 5;
        } BIT;
    } MAPR;
    // External Interrupt Configuration Register 1 (EXTICR1)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t EXTI0: 4;
            volatile uint32_t EXTI1: 4;
            volatile uint32_t EXTI2: 4;
            volatile uint32_t EXTI3: 4;
            volatile uint32_t reserved: 16;
        } BIT;
    } EXTICR1;
    // External Interrupt Configuration Register 2 (EXTICR2)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t EXTI4: 4;
            volatile uint32_t EXTI5: 4;
            volatile uint32_t EXTI6: 4;
            volatile uint32_t EXTI7: 4;
            volatile uint32_t reserved: 16;
            
        } BIT;
    } EXTICR2;
    // External Interrupt Configuration Register 3 (EXTICR3)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t EXTI8: 4;
            volatile uint32_t EXTI9: 4;
            volatile uint32_t EXTI10: 4;
            volatile uint32_t EXTI11: 4;
            volatile uint32_t reserved: 16;
        } BIT;
    } EXTICR3;
    // External Interrupt Configuration Register 3 (EXTICR4)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t EXTI12: 4;
            volatile uint32_t EXTI13: 4;
            volatile uint32_t EXTI14: 4;
            volatile uint32_t EXTI15: 4;
            volatile uint32_t reserved: 16;
        } BIT;
    } EXTICR4;
    
} AFIO_REG_STRUCT;

#endif /* __AFIO_REG_MAP_H__ */