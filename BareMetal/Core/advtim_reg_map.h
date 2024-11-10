// Header Guards
#ifndef __ADVTIM_REG_MAP_H__
#define __ADVTIM_REG_MAP_H__

// Core C Library
#include <stdint.h>

// Advanced Timers (TIM1, TIM8)
typedef struct {
	// Control Register 1 (CR1)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t CEN : 1;
            volatile uint32_t UDIS : 1;
            volatile uint32_t URS : 1;
            volatile uint32_t OPM : 1;
            volatile uint32_t DIR : 1;
            volatile uint32_t CMS : 2;
            volatile uint32_t ARPE : 1;
            volatile uint32_t CKD : 2;
            volatile uint32_t reserved : 22;
        } BIT;
	} CR1;
	// Control Register 2 (CR2)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t CCPC : 1;
            volatile uint32_t reserved_1 : 1;
            volatile uint32_t CCUS : 1;
            volatile uint32_t CDUS : 1;
            volatile uint32_t MMS : 3;
            volatile uint32_t TI1S : 1;
            volatile uint32_t OIS1 : 1;
            volatile uint32_t OIS1N : 1;
            volatile uint32_t OIS2 : 1;
            volatile uint32_t OIS2N : 1;
            volatile uint32_t OIS3 : 1;
            volatile uint32_t OIS3N : 1;
            volatile uint32_t OIS4 : 1;
            volatile uint32_t reserved_2 : 17;
        } BIT;
	} CR2;
	// Slave Mode Control Register (SMCR)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t SMS : 3;
            volatile uint32_t reserved_1 : 1;
            volatile uint32_t TS : 3;
            volatile uint32_t MSM : 1;
            volatile uint32_t ETF : 4;
            volatile uint32_t ETPS : 2;
            volatile uint32_t ECE : 1;
            volatile uint32_t ETP : 1;
			volatile uint32_t reserved_2 : 16;
        } BIT;
	} SMCR;
	// TIM1 and TIM8 DMA/Interrupt Enable Register (DIER)
	union {
		// Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t UIE : 1;
            volatile uint32_t CC1IE : 1;
            volatile uint32_t CC2IE : 1;
            volatile uint32_t CC3IE : 1;
            volatile uint32_t CC4IE : 1;
            volatile uint32_t COMIE : 1;
            volatile uint32_t TIE : 1;
            volatile uint32_t BIE : 1;
            volatile uint32_t UDE : 1;
            volatile uint32_t CC1DE : 1;
            volatile uint32_t CC2DE : 1;
            volatile uint32_t CC3DE : 1;
            volatile uint32_t CC4DE : 1;
            volatile uint32_t COMDE : 1;
            volatile uint32_t TDE : 1;
            volatile uint32_t reserved : 17;
        } BIT;
	} DIER;
	// TIM1 and TIM8 Status Register (SR)
	union {
		// FULL 32-BIT REGISTER ACCESS
        uint32_t REG;
        // BIT ACCESS
        struct {
            volatile uint32_t UIF: 1;
            volatile uint32_t CC1IF: 1;
            volatile uint32_t CC2IF: 1;
            volatile uint32_t CC3IF: 1;
            volatile uint32_t CC4IF: 1;
            volatile uint32_t COMIF: 1;
            volatile uint32_t TIF: 1;
            volatile uint32_t BIF: 1;
            volatile uint32_t reserved_1: 1;
            volatile uint32_t CC1OF: 1;
            volatile uint32_t CC2OF: 1;
            volatile uint32_t CC3OF: 1;
            volatile uint32_t CC4OF: 1;
            volatile uint32_t reserved_2: 19;
        } BIT;
	} SR;
	// TIM1 and TIM8 Event Generation Register (EGR)
	union {
		// FULL 32-BIT REGISTER ACCESS
        uint32_t REG;
        // BIT ACCESS
        struct {
            volatile uint32_t UG: 1;
            volatile uint32_t CC1G: 1;
            volatile uint32_t CC2G: 1;
            volatile uint32_t CC3G: 1;
            volatile uint32_t CC4G: 1;
            volatile uint32_t COMG: 1;
            volatile uint32_t TG: 1;
            volatile uint32_t BG: 1;
            volatile uint32_t reserved: 24;
        } BIT;
	} EGR;
	// TIM1 and TIM8 Capture/Compare Mode Register 1 (CCMR1)
	union {
		// FULL 32-BIT REGISTER ACCESS
        uint32_t REG;
        // BIT ACCESS
        union {
            struct{
                volatile uint32_t CC1S: 2;
                volatile uint32_t OC1FE: 1;
                volatile uint32_t OC1PE: 1;
                volatile uint32_t OC1M: 3;
                volatile uint32_t OC1CE: 1;
                volatile uint32_t CC2S: 2;
                volatile uint32_t OC2FE: 1;
                volatile uint32_t OC2PE: 1;
                volatile uint32_t OC2M: 3;
                volatile uint32_t OC2CE: 1;
                volatile uint32_t reserved: 16;
            } OCM;
            struct{
                volatile uint32_t CC1S: 2;
                volatile uint32_t IC1PSC: 2;
                volatile uint32_t IC1F: 4;
                volatile uint32_t CC2S: 2;
                volatile uint32_t IC2PSC: 2;
                volatile uint32_t IC2F: 4;
                volatile uint32_t reserved: 16;
            } ICM;
        } BIT;
	} CCMR1;
	// TIM1 and TIM8 Capture/Compare Mode Register 2 (CCMR2)
	union {
		// FULL 32-BIT REGISTER ACCESS
        uint32_t REG;
        // BIT ACCESS
        union {
            struct{
                volatile uint32_t CC3S: 2;
                volatile uint32_t OC3FE: 1;
                volatile uint32_t OC3PE: 1;
                volatile uint32_t OC3M: 3;
                volatile uint32_t OC3CE: 1;
                volatile uint32_t CC4S: 2;
                volatile uint32_t OC4FE: 1;
                volatile uint32_t OC4PE: 1;
                volatile uint32_t OC4M: 3;
                volatile uint32_t OC4CE: 1;
                volatile uint32_t reserved: 16;
            } OCM;
            struct{
                volatile uint32_t CC3S: 2;
                volatile uint32_t IC3PSC: 2;
                volatile uint32_t IC3F: 4;
                volatile uint32_t CC4S: 2;
                volatile uint32_t IC4PSC: 2;
                volatile uint32_t IC4F: 4;
                volatile uint32_t reserved: 16;
            } ICM;
        } BIT;
	} CCMR2;
	// TIM1 and TIM8 Capture/Compare Enable Register (CCER)
	union {
		// FULL 32-BIT REGISTER ACCESS
        uint32_t REG;
        // BIT ACCESS
        struct {
            volatile uint32_t CC1E: 1;
            volatile uint32_t CC1P: 1;
            volatile uint32_t CC1NE: 1;
            volatile uint32_t CC1NP: 1;
            volatile uint32_t CC2E: 1;
            volatile uint32_t CC2P: 1;
            volatile uint32_t CC2NE: 1;
            volatile uint32_t CC2NP: 1;
            volatile uint32_t CC3E: 1;
            volatile uint32_t CC3P: 1;
            volatile uint32_t CC3NE: 1;
            volatile uint32_t CC3NP: 1;
            volatile uint32_t CC4E: 1;
            volatile uint32_t CC4P: 1;
            volatile uint32_t reserved_1: 1;
            volatile uint32_t CC4NP: 1;
            volatile uint32_t reserved_2: 16;
        } BIT;
	} CCER;
	// TIM1 and TIM8 Counter (CNT)
	volatile uint32_t CNT;
	// TIM1 and TIM8 Prescaler (PSC)
    volatile uint32_t PSC;
	// TIM1 and TIM8 Auto-Reload Register (ARR)
	volatile uint32_t ARR;
	// TIM1 and TIM8 Repetition Counter Register (RCR)
    volatile uint32_t RCR;
	// TIM1 and TIM8 Capture/Compare Register 1 (CCR1)
    union {
        volatile uint32_t CC1_IN;
        volatile uint32_t CC1_OUT;
    } CCR1;
	// TIM1 and TIM8 Capture/Compare Register 2 (CCR2)
	union {
        volatile uint32_t CC2_IN;
        volatile uint32_t CC2_OUT;
	} CCR2;
	// TIM1 and TIM8 Capture/Compare Register 3 (CCR3)
	union {
        volatile uint32_t CC3_IN;
        volatile uint32_t CC3_OUT;
	} CCR3;
	// TIM1 and TIM8 Capture/Compare Register 4 (CCR4)
	union {
        volatile uint32_t CC3_IN;
        volatile uint32_t CC3_OUT;
	} CCR4;
	// TIM1 and TIM8 Break and Dead-Time Register (BDTR)
	union {
		// FULL 32-BIT REGISTER ACCESS
        uint32_t REG;
        // BIT ACCESS
        struct {
            volatile uint32_t DTG: 8;
            volatile uint32_t LOCK: 2;
            volatile uint32_t OSSI: 1;
            volatile uint32_t OSSR: 1;
            volatile uint32_t BKE: 1;
            volatile uint32_t BKP: 1;
            volatile uint32_t AOE: 1;
            volatile uint32_t MOE: 1;
            volatile uint32_t reserved: 16;
        } BIT;
	} BDTR;
	// TIM1 and TIM8 DMA Control Register (DCR)
	union {
		// FULL 32-BIT REGISTER ACCESS
        uint32_t REG;
        // BIT ACCESS
        struct {
            volatile uint32_t DBA: 5;
            volatile uint32_t reserved_1: 3;
            volatile uint32_t DBL: 5;
            volatile uint32_t reserved_2: 19;
        } BIT;
	} DCR;
	// TIM1 and TIM8 DMA Address for full transfer register (DMAR)
    volatile uint32_t DMAR;
} ADV_TIM_REG_STRUCT;

#endif /* __ADVTIM_REG_MAP_H__ */