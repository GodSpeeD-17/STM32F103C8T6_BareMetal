// Header Guards
#ifndef __RCC_REG_MAP_H__
#define __RCC_REG_MAP_H__

// Core C Library
#include <stdint.h>

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


#endif /* __RCC_REG_MAP_H__ */