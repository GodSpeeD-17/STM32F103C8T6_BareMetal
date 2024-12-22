// Reference: https://maldus512.medium.com/bare-metal-programming-on-an-stm32f103-3a0f4e50ca29

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define ARM_IRQ                     ((uint8_t) 11)
#define RESERVED                    ((uint8_t) 6)
#define STM32F103C8_IRQ             ((uint8_t) 59)

// Extern from Linker Script
extern uint32_t _svector, _evector, _stext, _etext, _srodata, _erodata, _sidata, _sdata, _edata, _sbss, _ebss;
extern void __estack(void); //  External end of stack pointer in SRAM

// External Main Function (../App_Inc/main.h)
__attribute__((weak, naked)) extern int main(void);    

// Default Handler Function Prototype
__attribute__((weak)) void Default_Handler(void);

/*
    weak: Allows to overwrite a function
    alias: Calls the Function Name defined when addressed
    section: Stores the code in the input partition
*/
__attribute__((weak, naked, noreturn))          void Reset_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void NMI_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void HardFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void MemManage_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void BusFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void UsageFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SVC_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void DebugMon_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void PendSV_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SysTick_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void WWDG_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void PVD_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TAMPER_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void RTC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void FLASH_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void RCC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI0_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI4_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel4_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel5_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel6_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Channel7_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void ADC1_2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USB_HP_CAN_TX_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USB_LP_CAN_RX0_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void CAN_RX1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void CAN_SCE_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI9_5_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM1_BRK_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM1_UP_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM1_TRG_COM_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM1_CC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM4_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C1_EV_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C1_ER_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C2_EV_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C2_ER_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SPI1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SPI2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USART1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USART2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USART3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI15_10_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void RTC_Alarm_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM8_BRK_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM8_UP_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM8_TRG_COM_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM8_CC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void ADC3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void FSMC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SDIO_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM5_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SPI3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void UART4_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void UART5_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM6_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM7_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Channel1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Channel2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Channel3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Channel4_5_IRQHandler(void);

// Vector Table (Placed in .isr_vector section)
__attribute__((section(".isr_vector"))) void (*const vector_table[ARM_IRQ + RESERVED + STM32F103C8_IRQ])(void) = {
    __estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,                                  // Reserved (STM32F103C8 Datasheet NVIC Section)
    0,                                  // Reserved (STM32F103C8 Datasheet NVIC Section)
    0,                                  // Reserved (STM32F103C8 Datasheet NVIC Section)
    0,                                  // Reserved (STM32F103C8 Datasheet NVIC Section)
    SVC_Handler,
    DebugMon_Handler,
    0,                                  // Reserved (STM32F103C8 Datasheet NVIC Section)
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,
    PVD_IRQHandler,
    TAMPER_IRQHandler,
    RTC_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler, 
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler,
    EXTI3_IRQHandler,
    EXTI4_IRQHandler,
    DMA1_Channel1_IRQHandler,
    DMA1_Channel2_IRQHandler,
    DMA1_Channel3_IRQHandler,
    DMA1_Channel4_IRQHandler,
    DMA1_Channel5_IRQHandler,
    DMA1_Channel6_IRQHandler,
    DMA1_Channel7_IRQHandler,
    ADC1_2_IRQHandler,
    USB_HP_CAN_TX_IRQHandler,
    USB_LP_CAN_RX0_IRQHandler,
    CAN_RX1_IRQHandler,
    CAN_SCE_IRQHandler,
    EXTI9_5_IRQHandler,
    TIM1_BRK_IRQHandler,
    TIM1_UP_IRQHandler,
    TIM1_TRG_COM_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM4_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    I2C2_EV_IRQHandler,
    I2C2_ER_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_IRQHandler,
    EXTI15_10_IRQHandler,
    RTC_Alarm_IRQHandler,
    0,                                  // Reserved (STM32F103C8 Datasheet NVIC Section)
    TIM8_BRK_IRQHandler,
    TIM8_UP_IRQHandler,
    TIM8_TRG_COM_IRQHandler,
    TIM8_CC_IRQHandler,
    ADC3_IRQHandler,
    FSMC_IRQHandler,
    SDIO_IRQHandler,
    TIM5_IRQHandler,
    SPI3_IRQHandler,
    UART4_IRQHandler,
    UART5_IRQHandler,
    TIM6_IRQHandler,
    TIM7_IRQHandler,
    DMA2_Channel1_IRQHandler,
    DMA2_Channel2_IRQHandler,
    DMA2_Channel3_IRQHandler,
    DMA2_Channel4_5_IRQHandler
};

// Reset Handler
__attribute__((weak, naked, noreturn)) void Reset_Handler(void){

    // Step 1: Copy ".data" section from FLASH (pSrc) to ".data" section in SRAM (pDst)
    uint32_t* pSrc = (uint32_t *) &_sidata;
    uint32_t* pDst = (uint32_t *) &_sdata;
    while(pDst < &_edata){
        *pDst++ = *pSrc++;
    }

    // Step 2: Initialise .bss to 0 in SRAM (pDst)
    pDst = (uint32_t *)&_sbss;
    while(pDst < &_ebss){
        *pDst++ = 0;
    } 

    // Step 3: In case, <stdio.h> used then call the init function


    // Step 4: Call main()
    main();

    // Step 5: Infinite Loop (In case main() returns)
    while(1) 
        (void) 0;
}

// Default Handler (Overwrite This)
__attribute__((weak)) void Default_Handler(void){
    // Infinite Loop
    while(1) 
        (void) 0;
}