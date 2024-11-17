// Header Guards
#ifndef __EXTI_REG_MAP_H__
#define __EXTI_REG_MAP_H__

// Core C Library
#include <stdint.h>

// EXTI Register Structure
typedef struct {
    // Interrupt Mask Register (IMR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t MR0: 1;  
            volatile uint32_t MR1: 1;  
            volatile uint32_t MR2: 1;  
            volatile uint32_t MR3: 1;  
            volatile uint32_t MR4: 1;  
            volatile uint32_t MR5: 1;  
            volatile uint32_t MR6: 1;  
            volatile uint32_t MR7: 1;  
            volatile uint32_t MR8: 1;  
            volatile uint32_t MR9: 1;  
            volatile uint32_t MR10: 1; 
            volatile uint32_t MR11: 1; 
            volatile uint32_t MR12: 1; 
            volatile uint32_t MR13: 1; 
            volatile uint32_t MR14: 1; 
            volatile uint32_t MR15: 1; 
            volatile uint32_t MR16: 1; 
            volatile uint32_t MR17: 1; 
            volatile uint32_t MR18: 1; 
            volatile uint32_t MR19: 1; 
            volatile uint32_t reserved: 12;
        } BIT;
    } IMR;
    // Event Mask Register (EMR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t MR0: 1;  
            volatile uint32_t MR1: 1;  
            volatile uint32_t MR2: 1;  
            volatile uint32_t MR3: 1;  
            volatile uint32_t MR4: 1;  
            volatile uint32_t MR5: 1;  
            volatile uint32_t MR6: 1;  
            volatile uint32_t MR7: 1;  
            volatile uint32_t MR8: 1;  
            volatile uint32_t MR9: 1;  
            volatile uint32_t MR10: 1; 
            volatile uint32_t MR11: 1; 
            volatile uint32_t MR12: 1; 
            volatile uint32_t MR13: 1; 
            volatile uint32_t MR14: 1; 
            volatile uint32_t MR15: 1; 
            volatile uint32_t MR16: 1; 
            volatile uint32_t MR17: 1; 
            volatile uint32_t MR18: 1; 
            volatile uint32_t MR19: 1; 
            volatile uint32_t reserved: 12;
        } BIT;
    } EMR;
    // Rising Trigger Selection Register (RTSR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t TR0: 1;  
            volatile uint32_t TR1: 1;  
            volatile uint32_t TR2: 1;  
            volatile uint32_t TR3: 1;  
            volatile uint32_t TR4: 1;  
            volatile uint32_t TR5: 1;  
            volatile uint32_t TR6: 1;  
            volatile uint32_t TR7: 1;  
            volatile uint32_t TR8: 1;  
            volatile uint32_t TR9: 1;  
            volatile uint32_t TR10: 1; 
            volatile uint32_t TR11: 1; 
            volatile uint32_t TR12: 1; 
            volatile uint32_t TR13: 1; 
            volatile uint32_t TR14: 1; 
            volatile uint32_t TR15: 1; 
            volatile uint32_t TR16: 1; 
            volatile uint32_t TR17: 1; 
            volatile uint32_t TR18: 1; 
            volatile uint32_t TR19: 1; 
            volatile uint32_t reserved: 12;
        } BIT;
    } RTSR;
    // Falling Trigger Selection Register (FTSR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t TR0: 1;  
            volatile uint32_t TR1: 1;  
            volatile uint32_t TR2: 1;  
            volatile uint32_t TR3: 1;  
            volatile uint32_t TR4: 1;  
            volatile uint32_t TR5: 1;  
            volatile uint32_t TR6: 1;  
            volatile uint32_t TR7: 1;  
            volatile uint32_t TR8: 1;  
            volatile uint32_t TR9: 1;  
            volatile uint32_t TR10: 1; 
            volatile uint32_t TR11: 1; 
            volatile uint32_t TR12: 1; 
            volatile uint32_t TR13: 1; 
            volatile uint32_t TR14: 1; 
            volatile uint32_t TR15: 1; 
            volatile uint32_t TR16: 1; 
            volatile uint32_t TR17: 1; 
            volatile uint32_t TR18: 1; 
            volatile uint32_t TR19: 1; 
            volatile uint32_t reserved: 12;
        } BIT;
    } FTSR;
    // Software Interrupt Event Register (SWIER)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t SWIER0: 1;  
            volatile uint32_t SWIER1: 1;  
            volatile uint32_t SWIER2: 1;  
            volatile uint32_t SWIER3: 1;  
            volatile uint32_t SWIER4: 1;  
            volatile uint32_t SWIER5: 1;  
            volatile uint32_t SWIER6: 1;  
            volatile uint32_t SWIER7: 1;  
            volatile uint32_t SWIER8: 1;  
            volatile uint32_t SWIER9: 1;  
            volatile uint32_t SWIER10: 1; 
            volatile uint32_t SWIER11: 1; 
            volatile uint32_t SWIER12: 1; 
            volatile uint32_t SWIER13: 1; 
            volatile uint32_t SWIER14: 1; 
            volatile uint32_t SWIER15: 1; 
            volatile uint32_t SWIER16: 1; 
            volatile uint32_t SWIER17: 1; 
            volatile uint32_t SWIER18: 1; 
            volatile uint32_t SWIER19: 1; 
            volatile uint32_t reserved: 12;
        } BIT;
    } SWIER;
    // Pending Register (PR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t PR0: 1;  
            volatile uint32_t PR1: 1;  
            volatile uint32_t PR2: 1;  
            volatile uint32_t PR3: 1;  
            volatile uint32_t PR4: 1;  
            volatile uint32_t PR5: 1;  
            volatile uint32_t PR6: 1;  
            volatile uint32_t PR7: 1;  
            volatile uint32_t PR8: 1;  
            volatile uint32_t PR9: 1;  
            volatile uint32_t PR10: 1; 
            volatile uint32_t PR11: 1; 
            volatile uint32_t PR12: 1; 
            volatile uint32_t PR13: 1; 
            volatile uint32_t PR14: 1; 
            volatile uint32_t PR15: 1; 
            volatile uint32_t PR16: 1; 
            volatile uint32_t PR17: 1; 
            volatile uint32_t PR18: 1; 
            volatile uint32_t PR19: 1; 
            volatile uint32_t reserved: 12;
        } BIT;
    } PR;
} EXTI_REG_STRUCT;

#endif /* __EXTI_REG_MAP_H__ */