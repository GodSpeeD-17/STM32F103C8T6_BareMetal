// Header Guards
#ifndef __ADC_REG_MAP_H__
#define __ADC_REG_MAP_H__

#include "common.h"

typedef struct {

    // Status Register (SR)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t AWD: 1;
            volatile uint32_t EOC: 1;
            volatile uint32_t JEOC: 1;
            volatile uint32_t JSTRT: 1;
            volatile uint32_t STRT: 1;
        } BIT;
	} SR;

    // Control Register 1 (CR1)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t AWDCH: 5;
            volatile uint32_t EOCIE: 1;
            volatile uint32_t AWDIE: 1;
            volatile uint32_t JEOCIE: 1;
            volatile uint32_t SCAN: 1;
            volatile uint32_t AWDSGL: 1;
            volatile uint32_t JAUTO: 1;
            volatile uint32_t DISCEN: 1;
            volatile uint32_t JDISCEN: 1;
            volatile uint32_t DISCNUM: 3;
            volatile uint32_t DUALMOD: 4;
            volatile uint32_t reserved_1: 2;
            volatile uint32_t JAWDEN: 1;
            volatile uint32_t AWDEN: 1;
            volatile uint32_t reserved_2: 8;
        } BIT;
	} CR1;
    
    // Control Register 2 (CR2)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t ADON: 1;
            volatile uint32_t CONT: 1;
            volatile uint32_t CAL: 1;
            volatile uint32_t RSTCAL: 1;
            volatile uint32_t reserved_1: 4;
            volatile uint32_t DMA: 1;
            volatile uint32_t reserved_2: 2;
            volatile uint32_t ALIGN: 1;
            volatile uint32_t JEXTSEL: 3;
            volatile uint32_t JEXTTRIG: 1;
            volatile uint32_t reserved_3: 1;
            volatile uint32_t EXTSEL: 3;
            volatile uint32_t EXTTRIG: 1;
            volatile uint32_t JSWSTART: 1;
            volatile uint32_t SWSTART: 1;
            volatile uint32_t TSVREFE: 1;
            volatile uint32_t reserved_4: 8;
        } BIT;
	} CR2;

    // Sample Register 1 (SMPR1)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t SMP10: 3;
            volatile uint32_t SMP11: 3;
            volatile uint32_t SMP12: 3;
            volatile uint32_t SMP13: 3;
            volatile uint32_t SMP14: 3;
            volatile uint32_t SMP15: 3;
            volatile uint32_t SMP16: 3;
            volatile uint32_t SMP17: 3;
            volatile uint32_t reserved: 8;
        } BIT;
	} SMPR1;
    
    // Sample Register 2 (SMPR2)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t SMP0: 3;
            volatile uint32_t SMP1: 3;
            volatile uint32_t SMP2: 3;
            volatile uint32_t SMP3: 3;
            volatile uint32_t SMP4: 3;
            volatile uint32_t SMP5: 3;
            volatile uint32_t SMP6: 3;
            volatile uint32_t SMP7: 3;
            volatile uint32_t SMP8: 3;
            volatile uint32_t SMP9: 3;
            volatile uint32_t reserved: 2;
        } BIT;
	} SMPR2;
    
    // ADC Injected Channel Data Offset Register 1 (JOFR1)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t JOFFSET1: 12;
            volatile uint32_t reserved: 20;
        } BIT;
	} JOFR1;

    // ADC Injected Channel Data Offset Register 2 (JOFR2)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t JOFFSET2: 12;
            volatile uint32_t reserved: 20;
        } BIT;
	} JOFR2;

    // ADC Injected Channel Data Offset Register 3 (JOFR3)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t JOFFSET3: 12;
            volatile uint32_t reserved: 20;
        } BIT;
	} JOFR3;

    // ADC Injected Channel Data Offset Register 4 (JOFR4)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t JOFFSET4: 12;
            volatile uint32_t reserved: 20;
        } BIT;
	} JOFR4;

    // ADC Watchdog High Threshold Register (HTR)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t HT: 12;
            volatile uint32_t reserved: 20;
        } BIT;
	} HTR;
    
    // ADC Watchdog Low Threshold Register (LTR)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t LT: 12;
            volatile uint32_t reserved: 20;
        } BIT;
	} LTR;
    
    // ADC Regular Sequence Register 1 (SQR1)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t SQ13: 5;
            volatile uint32_t SQ14: 5;
            volatile uint32_t SQ15: 5;
            volatile uint32_t SQ16: 5;
            volatile uint32_t L: 5;
            volatile uint32_t reserved: 7;
        } BIT;
	} SQR1;

    // ADC Regular Sequence Register 2 (SQR2)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t SQ7: 5;
            volatile uint32_t SQ8: 5;
            volatile uint32_t SQ9: 5;
            volatile uint32_t SQ10: 5;
            volatile uint32_t SQ11: 5;
            volatile uint32_t SQ12: 5;
            volatile uint32_t reserved: 2;
        } BIT;
	} SQR2;

    // ADC Regular Sequence Register 3 (SQR3)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t SQ1: 5;
            volatile uint32_t SQ2: 5;
            volatile uint32_t SQ3: 5;
            volatile uint32_t SQ4: 5;
            volatile uint32_t SQ5: 5;
            volatile uint32_t SQ6: 5;
            volatile uint32_t reserved: 2;
        } BIT;
	} SQR3;
    
    // ADC Injected Sequence Register (JSQR)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t JSQ1: 5;
            volatile uint32_t JSQ2: 5;
            volatile uint32_t JSQ3: 5;
            volatile uint32_t JSQ4: 5;
            volatile uint32_t JL: 2;
            volatile uint32_t reserved: 10;
        } BIT;
	} JSQR;
    
    // ADC Injected Data Register 1 (JDR1)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t JDATA1: 16;
            volatile uint32_t reserved: 16;
        } BIT;
	} JDR1;

    // ADC Injected Data Register 2 (JDR2)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t JDATA2: 16;
            volatile uint32_t reserved: 16;
        } BIT;
	} JDR2;

    // ADC Injected Data Register 3 (JDR3)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t JDATA3: 16;
            volatile uint32_t reserved: 16;
        } BIT;
	} JDR3;

    // ADC Injected Data Register 4 (JDR4)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t JDATA4: 16;
            volatile uint32_t reserved: 16;
        } BIT;
	} JDR4;

    // ADC Regular Data Register (DR)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t ADC2DATA: 16;
            volatile uint32_t DATA: 16;
        } BIT;
	} DR;
} ADC_REG_STRUCT;


#endif /* __ADC_REG_MAP_H__ */ 