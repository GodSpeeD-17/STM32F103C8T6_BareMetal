/***************************************************************************************
 *  File: nvic.c
 *  Created on: 17/11/2024
 *  Author: Shrey Shah
 ***************************************************************************************/
/*
    THEORY: 
        NVIC: Nested Interrupt Vector Configuration
            - Global Interrupt Configuration
            - NVIC is used to configure the priority of interrupts
        EXTI: External Interrupt Configuration
*/

#include "nvic.h"

// Stores the status of Interrupts before disabling it Globally
volatile uint32_t nvic_irq_enabled[2] = {0};
// volatile uint32_t nvic_irq_disabled[2] = {0};

/**
 * @brief Disables the All the Interrupts Globally
 * @note NVIC->ICER, NVIC->ISER
 */
void __disable_irq(void){
    for(uint8_t i = 0; i < 2; i++){
        // Store the previous state of the interrupt
        nvic_irq_enabled[i] = NVIC->ISER[i];
        // nvic_irq_disabled[i] = NVIC->ICER[i];
        // Disable all the interrupts
        NVIC->ICER[i] = 0xFFFFFFFF; 
    }
}

/**
 * @brief Enables the All the Interrupts Globally
 * @note NVIC->ICER, NVIC->ISER
 */
void __enable_irq(void){
    // Traverse through all the registers
    for(uint8_t i = 0; i < 2; i++){
        // Restore the previous state of the interrupts
        NVIC->ISER[i] = nvic_irq_enabled[i]; 
        // NVIC->ICER[i] = nvic_irq_disabled[i] ;
    }
}

/**
 * @brief Configures the NVIC EXTI Source
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 */
void config_EXTI_src(GPIO_REG_STRUCT* GPIOx, uint8_t PINx){
    uint32_t reg = 0, pin = 0;
    uint8_t temp = 0xFF;

    // Port based selection
    if(GPIOx == GPIOA){
        temp = 0x0;
    }
    else if(GPIOx == GPIOB){
        temp = 0x1;
    }
    else if(GPIOx == GPIOC){
        temp = 0x2;
    }
    else 
        return;

    // Parameter Determination
    if(PINx < (uint8_t) 4){
        reg = AFIO->EXTICR1.REG;
        pin = PINx * 4;
    }
    else if(PINx < (uint8_t) 8){
        reg = AFIO->EXTICR2.REG;
        pin = (PINx - 4) * 4;
    }
    else if(PINx < (uint8_t) 12){
        reg = AFIO->EXTICR3.REG;
        pin = (PINx - 8) * 4;
    }
    else if(PINx < (uint8_t) 16){
        reg = AFIO->EXTICR4.REG;
        pin = (PINx - 12) * 4;
    }
    else 
        return;

    // Clear Register
    reg &= ~(0 << pin);
    // Set Register
    reg |= (temp << pin);

    // Write to Register 
    if(PINx < (uint8_t) 4){
        AFIO->EXTICR1.REG = reg;
    }
    else if(PINx < (uint8_t) 8){
        AFIO->EXTICR2.REG = reg;
    }
    else if(PINx < (uint8_t) 12){
        AFIO->EXTICR3.REG = reg;
    }
    else if(PINx < (uint8_t) 16){
        AFIO->EXTICR4.REG = reg;
    }
}

/**
 * @brief Configures the External Interrupt Trigger Selection
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] TRIGx `NVIC_TRIG_FALLING`, `NVIC_TRIG_FALLING`, `NVIC_TRIG_BOTH`
 * @note The external wakeup lines are edge triggered, no glitches must be generated on these lines
 */
void config_EXTI_trig(uint8_t PINx, uint8_t TRIGx){

    // Trigger Selection
    switch (TRIGx){
    
        // Falling Edge 
        case NVIC_TRIG_FALLING:
            EXTI->FTSR.REG |= (1 << PINx);
            break;

        // Rising Edge 
        case NVIC_TRIG_RISING:
            EXTI->RTSR.REG |= (1 << PINx);
            break;
        
        // Both Edge 
        case NVIC_TRIG_BOTH:
            EXTI->RTSR.REG |= (1 << PINx);
            EXTI->FTSR.REG |= (1 << PINx);
            break;
        
        // Error
        default:
            return;
            break;
    }
}

/**
 * @brief Configures the NVIC for GPIO EXTI
 * @param[in] GPIOx `GPIOA`, `GPIOB`, `GPIOC`
 * @param[in] PINx Pin Number `GPIO_PIN_x`
 * @param[in] TRIGx `NVIC_TRIG_FALLING`, `NVIC_TRIG_FALLING`, `NVIC_TRIG_BOTH`
 * @param[in] IRQn The Interrupt Number
 */
void config_NVIC_EXTI(GPIO_REG_STRUCT* GPIOx, uint8_t PINx, uint8_t TRIGx, uint8_t IRQn){
    
    // Configure the Source of Interrupt (Port Selection)
    config_EXTI_src(GPIOx, PINx);

    // Configure the External Trigger
    config_EXTI_trig(PINx, TRIGx);

    // Enable the IRQ (Remove the Mask)
    enable_EXTI_IRQ(PINx);

    // Enable the NVIC Interrupt
    NVIC_EnableIRQ(IRQn);

}

