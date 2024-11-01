/*
    Basic Notes:-
    YT Reference Video: https://youtu.be/zvTd3Zxtiek
    `uint32_t` inside every BIT struct because of padding alignment
    `volatile` used for ensuring no optimization by compiler
    `: x` indicates only x bit(s) to be used from that 32-bit
*/

// Header Guards
#ifndef __REG_MAP_H__
#define __REG_MAP_H__

// Standard C Libraries
#include <stdint.h>


/*********************************************** ARM CORTEX M3 ***********************************************/
// SysTick Structure
typedef struct {
	// Control and Status Register (CSR)
	union{
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t EN: 1;
			volatile uint32_t TICKINT: 1;
			volatile uint32_t CLKSRC: 1;
			volatile uint32_t resereved_1: 13;
			volatile uint32_t CNTFLAG: 1;
			volatile uint32_t reserved_2: 15;
		} BIT;
	} CSR;

	// Reload Value Register (RELOAD)
	uint32_t RELOAD_VALUE: 24;					// 24-bit used only (From LSB)

	// Current Value Register (CURRENT)
	uint32_t CURR_VALUE: 24;					// 24-bit used only (From LSB)

	// Calibration Value Register (CAL)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t TENMS: 24;
			volatile uint32_t reserved: 6;
			volatile uint32_t SKEW: 1;
			volatile uint32_t NOREF: 1;
		} BIT;
	} CAL;
} SYSTICK_REG_STRUCT;


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

// Window WatchDog
typedef struct {
	// Control Register (CR)
	union {
		// Full 32-bit Register Access
		uint32_t REG;
		// Bit Access
		struct {
			volatile uint32_t T: 7;
			volatile uint32_t WDGA: 1;
			volatile uint32_t reserved: 24;
		} BIT;
	} CR;
} WWDG_REG_STRUCT;

/*********************************************** RCC ***********************************************/
// RCC Main Structure
typedef struct {
    // Clock Control Register (CR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t HSION: 1;
            volatile uint32_t HSIRDY: 1;
            volatile uint32_t reserved_1: 1;
            volatile uint32_t HSITRIM: 5;
            volatile uint32_t HSICAL: 8;
            volatile uint32_t HSEON: 1;
            volatile uint32_t HSERDY: 1;
            volatile uint32_t HSEBYP: 1;
            volatile uint32_t CSSON: 1;
            volatile uint32_t reserved_2: 4;
            volatile uint32_t PLLON: 1;
            volatile uint32_t PLLRDY: 1;
            volatile uint32_t reserved_3: 6;
        } BIT;
    } CR;
    // Configuration Register (CFGR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t SW: 2;
            volatile uint32_t SWS: 2;
            volatile uint32_t HPRE: 4;
            volatile uint32_t PPRE1: 3;
            volatile uint32_t PPRE2: 3;
            volatile uint32_t ADCPRE: 2;
            volatile uint32_t PLLSRC: 1;
            volatile uint32_t PLLXTPRE: 1;
            volatile uint32_t PLLMUL: 4;
            volatile uint32_t USBPRE: 1;
            volatile uint32_t reserved_1: 1;
            volatile uint32_t MCO: 3;
            volatile uint32_t reserved_2: 5;
        } BIT;
    } CFGR;
    // Clock Interrupt Register (CIR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t LSIRDYF: 1;
            volatile uint32_t LSERDYF: 1;
            volatile uint32_t HSIRDYF: 1;
            volatile uint32_t HSERDYF: 1;
            volatile uint32_t PLLRDYF: 1;
            volatile uint32_t reserved_1: 2;
            volatile uint32_t CSFF: 1;
            volatile uint32_t LSIRDYIE: 1;
            volatile uint32_t LSERDYIE: 1;
            volatile uint32_t HSIRDYIE: 1;
            volatile uint32_t HSERDYIE: 1;
            volatile uint32_t PLLRDYIE: 1;
            volatile uint32_t reserved_2: 3;
            volatile uint32_t LSIRDYC: 1;
            volatile uint32_t LSERDYC: 1;
            volatile uint32_t HSIRDYC: 1;
            volatile uint32_t HSERDYC: 1;
            volatile uint32_t PLLRDYC: 1;
            volatile uint32_t reserved_3: 2;
            volatile uint32_t CSSC: 1;
            volatile uint32_t reserved_4: 8;
        } BIT;
    } CIR;
    // APB2 Peripheral Reset Register (APB2RSTR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t AFIORST: 1;
            volatile uint32_t reserved_1: 1;
            volatile uint32_t IOPARST: 1;
            volatile uint32_t IOPBRST: 1;
            volatile uint32_t IOPCRST: 1;
            volatile uint32_t IOPDRST: 1;
            volatile uint32_t IOPERST: 1;
            volatile uint32_t IOPFRST: 1;
            volatile uint32_t IOPGRST: 1;
            volatile uint32_t ADC1RST: 1;
            volatile uint32_t ADC2RST: 1;
            volatile uint32_t TIM1RST: 1;
            volatile uint32_t SPI1RST: 1;
            volatile uint32_t TIM8RST: 1;
            volatile uint32_t USART1RST: 1;
            volatile uint32_t ADC3RST: 1;
            volatile uint32_t reserved_2: 3;
            volatile uint32_t TIM9RST: 1;
            volatile uint32_t TIM10RST: 1;
            volatile uint32_t TIM11RST: 1;
            volatile uint32_t reserved_3: 10;
        } BIT;
    } APB2RSTR;
    // APB1 Peripheral Reset Register (APB2RSTR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t TIM2RST: 1;
            volatile uint32_t TIM3RST: 1;
            volatile uint32_t TIM4RST: 1;
            volatile uint32_t TIM5RST: 1;
            volatile uint32_t TIM6RST: 1;
            volatile uint32_t TIM7RST: 1;
            volatile uint32_t TIM12RST: 1;
            volatile uint32_t TIM13RST: 1;
            volatile uint32_t TIM14RST: 1;
            volatile uint32_t reserved_1: 1;
            volatile uint32_t WWDGRST: 1;
            volatile uint32_t reserved_2: 2;
            volatile uint32_t SPI2RST: 1;
            volatile uint32_t SPI3RST: 1;
            volatile uint32_t reserved_3: 1;
            volatile uint32_t USART2RST: 1;
            volatile uint32_t USART3RST: 1;
            volatile uint32_t UART4RST: 1;
            volatile uint32_t UART5RST: 1;
            volatile uint32_t I2C1RST: 1;
            volatile uint32_t I2C2RST: 1;
            volatile uint32_t USBRST: 1;
            volatile uint32_t reserved_4: 1;
            volatile uint32_t CANRST: 1;
            volatile uint32_t reserved_5: 1;
            volatile uint32_t BKPRST: 1;
            volatile uint32_t PWRRST: 1;
            volatile uint32_t DACRST: 1;
            volatile uint32_t reserved_6: 2;
        } BIT;
    } APB1RSTR;
    // AHB Enable Register (AHBENR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t DMA1EN: 1;
            volatile uint32_t DMA2EN: 1;
            volatile uint32_t SRAMEN: 1;
            volatile uint32_t reserved_1: 1;
            volatile uint32_t FLITFEN: 1;
            volatile uint32_t reserved_2: 1;
            volatile uint32_t CRCEN: 1;
            volatile uint32_t reserved_3: 1;
            volatile uint32_t FSMCEN: 1;
            volatile uint32_t reserved_4: 1;
            volatile uint32_t SDIOEN: 1;
            volatile uint32_t reserved_5: 21;
        } BIT;
    } AHBENR;
    // APB2 Enable Register (APB2ENR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t AFIOEN: 1;
            volatile uint32_t reserved_1: 1;
            volatile uint32_t IOPAEN: 1;
            volatile uint32_t IOPBEN: 1;
            volatile uint32_t IOPCEN: 1;
            volatile uint32_t IOPDEN: 1;
            volatile uint32_t IOPEEN: 1;
            volatile uint32_t IOPFEN: 1;
            volatile uint32_t IOPGEN: 1;
            volatile uint32_t ADC1EN: 1;
            volatile uint32_t ADC2EN: 1;
            volatile uint32_t TIM1EN: 1;
            volatile uint32_t SPI1EN: 1;
            volatile uint32_t TIM8EN: 1;
            volatile uint32_t USART1EN: 1;
            volatile uint32_t ADC3EN: 1;
            volatile uint32_t reserved_2: 3;
            volatile uint32_t TIM9EN: 1;
            volatile uint32_t TIM10EN: 1;
            volatile uint32_t TIM11EN: 1;
            volatile uint32_t reserved_3: 10;
        } BIT;
    } APB2ENR;
    // APB1 Enable Register (APB1ENR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t TIM2EN: 1;
            volatile uint32_t TIM3EN: 1;
            volatile uint32_t TIM4EN: 1;
            volatile uint32_t TIM5EN: 1;
            volatile uint32_t TIM6EN: 1;
            volatile uint32_t TIM7EN: 1;
            volatile uint32_t TIM12EN: 1;
            volatile uint32_t TIM13EN: 1;
            volatile uint32_t TIM14EN: 1;
            volatile uint32_t reserved_1: 2;
            volatile uint32_t WWDGEN: 1;
            volatile uint32_t reserved_2: 2;
            volatile uint32_t SPI2EN: 1;
            volatile uint32_t SPI3EN: 1;
            volatile uint32_t reserved_3: 1;
            volatile uint32_t USART2EN: 1;
            volatile uint32_t USART3EN: 1;
            volatile uint32_t UART4EN: 1;
            volatile uint32_t UART5EN: 1;
            volatile uint32_t I2C1EN: 1;
            volatile uint32_t I2C2EN: 1;
            volatile uint32_t USBEN: 1;
            volatile uint32_t reserved_4: 1;
            volatile uint32_t CANEN: 1;
            volatile uint32_t reserved_5: 1;
            volatile uint32_t BKPEN: 1;
            volatile uint32_t PWREN: 1;
            volatile uint32_t DACEN: 1;
            volatile uint32_t reserved_6: 2;
        } BIT;
    } APB1ENR;
    // Backup Domain Control Register (BDCR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t LSEON: 1;
            volatile uint32_t LSERDY: 1;
            volatile uint32_t LSEBYP: 1;
            volatile uint32_t reserved_1: 5;
            volatile uint32_t RTCSEL: 2;
            volatile uint32_t reserved_2: 5;
            volatile uint32_t RTCEN: 2;
            volatile uint32_t BDRST: 2;
            volatile uint32_t reserved_3: 15;
        } BIT;
    } BDCR;
    // Control/Status Register (CSR)
    union {
        // Full 32-bit Register Access
        uint32_t REG;
        // Bit Access
        struct {
            volatile uint32_t LSION: 1;
            volatile uint32_t LSIRDY: 1;
            volatile uint32_t reserved_1: 22;
            volatile uint32_t RMVF: 1;
            volatile uint32_t reserved_2: 1;
            volatile uint32_t PINRSTF: 1;
            volatile uint32_t PORRSTF: 1;
            volatile uint32_t SFTRSTF: 1;
            volatile uint32_t IWDGRSTF: 1;
            volatile uint32_t WWDGRSTF: 1;
            volatile uint32_t LPWRRSTF: 1;
        } BIT;
    } CSR;
} RCC_REG_STRUCT;

/*********************************************** AFIO ***********************************************/
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
/*********************************************** GPIO ***********************************************/
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
/*********************************************** Timers ***********************************************/
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

// General Purpose Timers (TIM2 to TIM5)
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
            volatile uint32_t reserved_1 : 3;
            volatile uint32_t CCDS : 1;
            volatile uint32_t MMS : 3;
            volatile uint32_t TI1S : 1;
            volatile uint32_t reserved_2 : 24;
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
	// TIMx DMA/Interrupt Enable Register (DIER)
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
            volatile uint32_t reserved_1 : 1;
            volatile uint32_t TIE : 1;
            volatile uint32_t reserved_2 : 1;
            volatile uint32_t UDE : 1;
            volatile uint32_t CC1DE : 1;
            volatile uint32_t CC2DE : 1;
            volatile uint32_t CC3DE : 1;
            volatile uint32_t CC4DE : 1;
            volatile uint32_t reserved_3 : 1;
            volatile uint32_t TDE : 1;
            volatile uint32_t reserved_4 : 17;
        } BIT;
	} DIER;
	// TIMx Status Register (SR)
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
            volatile uint32_t reserved_1: 1;
            volatile uint32_t TIF: 1;
            volatile uint32_t reserved_2: 2;
            volatile uint32_t CC1OF: 1;
            volatile uint32_t CC2OF: 1;
            volatile uint32_t CC3OF: 1;
            volatile uint32_t CC4OF: 1;
            volatile uint32_t reserved_3: 19;
        } BIT;
	} SR;
	// TIMx Event Generation Register (EGR)
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
            volatile uint32_t reserved_1: 1;
            volatile uint32_t TG: 1;
            volatile uint32_t reserved_2: 25;
        } BIT;
	} EGR;
	// TIMx Capture/Compare Mode Register 1 (CCMR1)
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
	// TIMx Capture/Compare Mode Register 2 (CCMR2)
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
	// TIMx Capture/Compare Enable Register (CCER)
	union {
		// FULL 32-BIT REGISTER ACCESS
        uint32_t REG;
        // BIT ACCESS
        struct {
            volatile uint32_t CC1E: 1;
            volatile uint32_t CC1P: 1;
            volatile uint32_t reserved_1: 2;
            volatile uint32_t CC2E: 1;
            volatile uint32_t CC2P: 1;
            volatile uint32_t reserved_2: 2;
            volatile uint32_t CC3E: 1;
            volatile uint32_t CC3P: 1;
            volatile uint32_t reserved_3: 2;
            volatile uint32_t CC4E: 1;
            volatile uint32_t CC4P: 1;
            volatile uint32_t reserved_4: 18;
        } BIT;
	} CCER;
	// TIMx Counter (CNT)
	volatile uint32_t CNT;
	// TIMx Prescaler (PSC)
	volatile uint32_t PSC;
	// TIMx Auto-Reload Register (ARR)
	volatile uint32_t ARR;
	// Reserved
	volatile uint32_t RESERVED_1;
	// TIMx Capture/Compare Register 1 (CCR1)
    union {
        volatile uint32_t CC1_IN;
        volatile uint32_t CC1_OUT;
    } CCR1;
	// TIMx Capture/Compare Register 2 (CCR2)
	union {
        volatile uint32_t CC2_IN;
        volatile uint32_t CC2_OUT;
	} CCR2;
	// TIMx Capture/Compare Register 3 (CCR3)
	union {
        volatile uint32_t CC3_IN;
        volatile uint32_t CC3_OUT;
	} CCR3;
	// TIMx Capture/Compare Register 4 (CCR4)
	union {
        volatile uint32_t CC4_IN;
        volatile uint32_t CC4_OUT;
	} CCR4;
	// Reserved
	volatile uint32_t RESERVED_2;
	// TIMx DMA Control Register (DCR)
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
	// TIMx DMA Address for full transfer register (DMAR)
    volatile uint32_t DMAR;
} GPT_REG_STRUCT;

/*********************************************** Address Mapping ***********************************************/
// Memory Mapping
#define SYSTICK_BASE_ADDR					(0xE000E010)
#define APB1_BASE_ADDR          			(0x40000000)
#define APB2_BASE_ADDR          			(0x40010000)
#define AHB_BASE_ADDR           			(0x40018000)
#define FLASH_BASE_ADDR                     (0x40022000)

// Address Mapping
#define SYSTICK								((SYSTICK_REG_STRUCT *)(SYSTICK_BASE_ADDR))
#define FLASH                               ((FLASH_REG_STRUCT *)(FLASH_BASE_ADDR))
#define WWDG								((WWDG_REG_STRUCT *) (APB1_BASE_ADDR + (uint32_t)0x2C00))
#define RCC                     			((RCC_REG_STRUCT *)(AHB_BASE_ADDR + (uint32_t)0x9000))
#define GPIOA                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x0800))
#define GPIOB                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x0C00))
#define GPIOC                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x1000))
#define GPIOD                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x1400))
#define GPIOE                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x1800))
#define GPIOF                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x1C00))
#define GPIOG                   			((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x2000))
#define AFIO                                ((AFIO_REG_STRUCT *)(APB2_BASE_ADDR))
#define TIM1								((ADV_TIM_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x2C00))
#define TIM2								((GPT_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x0000))
#define TIM3								((GPT_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x0400))
#define TIM4								((GPT_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x0800))
#define TIM5								((GPT_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x0C00))
#define TIM6								((GPT_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x1000))
#define TIM7								((GPT_REG_STRUCT *)(APB1_BASE_ADDR + (uint32_t)0x1400))
#define TIM8								((ADV_TIM_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x3400))

#endif  /* __REG_MAP_H__ */
