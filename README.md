# ***STM32F103C8T6 (Blue Pill) Bare Metal Repository***
---
## ***Description***
---
  - Basic Repository for understanding the Registers present in Blue Pill Development Module
  - Created basic source files to use Registers for controlling purpose
  - `Projects/Template` is the template which can be used as reference while creating New Project

---
## ***Repository Structure***
---

  - `BareMetal`: Consists of all the Register Address Mapping along with basic functionality Source Code
  - `Projects`: Consists of User Specific Application
  - `Reference_Docs`: All the Reference Documentation relevant to the topic

---
## ***STM32F103C8T6 Reference Manual***
---
[STM32F103C_Reference_Manual.pdf](https://github.com/user-attachments/files/17964492/STM32F103C_Reference_Manual.pdf)

---
## ***STM32F103C8T6 Pinout***
---
![Blue_PIll_Pinout](https://github.com/user-attachments/assets/13d3a619-ac7a-4799-9715-64730e110f1b)

---
## ***STM32F103C8T6 Features***
---
│    **Specification**   │   **Details**   │  **Comments**     │
-------------------------│-----------------│-------------------│
│     ***Processor***    │ ARM Cortex-M3   │  Single Core      │
│ ***Clock Frequency***  │  8MHz - 72MHz   │  HSI/HSE: 8MHz    │
│       ***Flash***      │     64kB        │ 0x08000000  │
│       ***SRAM***       │     20kB        │ 0x20000000  │

---
## ***IRQ Details***
---
│     **Vector Table**      │ 76 │
│---------------------------│----│
│ ***ARM Cortex-M3 IRQ***   │ 11 │
│ ***STM32F103C8T6 IRQ***   │ 59 │
│ ***Reserved***            │ 6  │

---
## ***Boot Process***
---
1. **Power ON**
2. **Stack Pointer (SP)** 
   - Points to the top of SRAM (Vector Table Offset: `0x00`)
3. **`Reset_Handler()` is called** 
   - Vector Table Offset: `0x01`
   - **Initialization Steps:**
     1. Copy the **`.data`** section from FLASH to SRAM 
        - **Note:** `.data` refers to initialized variables.
     2. Initialize the **`.bss`** section to `0` 
        - **Note:** `.bss` refers to uninitialized variables.
     3. Call the **Main function**

---
## ***Overall Repository Structure***
```
<STM32F103C8T6>
      ├── BareMetal                             # Bare Metal Code
      │     ├── Core                            # Register Mapping
      │     ├── Inc                             # Driver Header File
      │     ├── Src                             # Driver Source Code
      │
      ├── Projects
      │     ├── ADC                             # ADC Related Projects
      │     │   ├── 08_ADC_Polling
      │     │   ├── 09_ADC_IRQ
      │     │   ├── 10_ADC_PWM_Polling
      │     │   ├── 11_ADC_PWM_IRQ
      │     ├── GPIO                            # GPIO Related Projects
      │     │   ├── 01_Blinky
      │     │   ├── 02_PB_Polling
      │     │   ├── 03_PB_IRQ
      │     ├── PWM                             # PWM Related Projects
      │     │   ├── 06_PWM_Polling
      │     │   ├── 07_PWM_PB_IRQ
      │     ├── Timer                           # Timer Related Projects
      │     │   ├── 04_GPT
      │     │   ├── 05_Timer_IRQ
      │     ├── USART                           # USART Related Projects
      │     │   ├── 12_char_TX
      │     │   ├── 13_string_TX
      │     │   ├── 14_printf
      │     ├── Template                        # Reference Template
      │      
      ├── README.md                             # README File
      │      
      └── Reference_Docs                        # Reference Documentations
```

## ***BareMetal Structure***
---
```
<BareMetal>
    │
    ├── Core
    │  ├── adc_reg_map.h                # Analog to Digital Converter Structure {ADC1, ADC2, -ADC3-}
    │  ├── advtim_reg_map.h             # Advanced Timer Structure {TIM1, -TIM8-}
    │  ├── afio_reg_map.h               # Alternate Function Input Output (AFIO) Structure
    │  ├── common.h                     # Core C Libraries Dependency
    │  ├── exti_reg_map.h               # External Interrupt (EXTI) Structure
    │  ├── flash_reg_map.h              # Flash Structure
    │  ├── gpio_reg_map.h               # General Purpose Input Output (GPIO) Structure
    │  ├── gpt_reg_map.h                # General Purpose Timer (GPT) Structure {TIM2, TIM3, TIM4, -TIM5-}
    │  ├── nvic_reg_map.h               # Nested Vector Interrupt Control (NVIC) Structure
    │  ├── rcc_reg_map.h                # Reset and Clock Control (RCC) Structure
    │  ├── systick_reg_map.h            # SysTick Structure
    │  ├── usart_reg_map.h              # Universal Synchronous Asynchronous Receiver Transmitter (USART) Structure
    │  └── wwdg_reg_map.h               # Window Watchdog (WWDG) Structure
    │
    │
    ├── Inc
    │  ├── adc.h                        # ADC Header File
    │  ├── bare_metal.h                 # Common Include Header File
    │  ├── exti.h                       # EXTI Header File
    │  ├── gpio.h                       # GPIO Header File
    │  ├── gpt.h                        # General Purpose Timer (GPT) Header File
    │  ├── nvic.h                       # NVIC Header File
    │  ├── pwm.h                        # PWM Header File
    │  ├── rcc.h                        # Clock Configuration Header File
    │  ├── reg_map.h                    # Main Register Mapping Header File
    │  ├── systick.h                    # SysTick Header File (ARM Cortex-M3)                 
    │  └── usart.h                      # USART Header File                 
    │
    │
    ├── Src
    │  ├── adc.c                        # ADC Source File
    │  ├── exti.c                       # EXTI Source File
    │  ├── gpio.c                       # GPIO Source File
    │  ├── gpt.c                        # General Purpose Timer Source File    
    │  ├── pwm.c                        # PWM Source File
    │  ├── rcc.c                        # Clock Configuration Source File
    │  ├── systick.c                    # SysTick Source File (ARM Cortex-M3)
    └──└── usart.c                      # USART Source File
```

---
## ***Project Structure***
---
```
<Project_Name>
      │
      ├── App_Inc
      │    ├── main.h                    # Application Header File
      │
      ├── App_Src
      │    ├── main.c                    # Application Source File
      │
      ├── Linker
      │    ├── stm32_ls.ld               # Linker Script (Contains the mapping of sections to the address)
      │
      ├── Startup
      │    ├── stm32_startup.c           # Startup File (Contains Vector Table Mapping)
      │
      └── Makefile                       # Automation File (Used for compilation and flashing)
```

---
## ***Makefile Basic Commands***
---
  - `make all`: Compiles all the .c files including "BareMetal" directory
  - `make clean`: Cleans all the extra intermediate files used for compiling including "BareMetal" Directory
  - `make flash`: Flashes Current Project's .bin file at Flash Address (0x080000000)
  - `make erase_flash`: Erases the Flash Memory of Blue Pill Module

---
## ***Project Overview***
---
│    **Projects**     │               **Description**                                │
│---------------------│--------------------------------------------------------------│
│ ***01_Blinky*** │ A simple LED blinking                                        │
│ ***02_PB_Polling*** │ A simple LED blinking based on polling the status of Push Button │
│ ***03_PB_IRQ*** │ A simple LED blinking based on Interrupt generated by Push Button │
│ ***04_GPT*** │ Delay generation based upon General Purpose Timer (GPT)     │
│ ***05_Timer_IRQ***  │ Interrupt generation using General Purpose Timer (GPT)      │
│ ***06_PWM_Polling*** │ Pulse Width Modulation (PWM) generation using General Purpose Timer (GPT) │
│ ***07_PWM_PB_IRQ*** │ Use the Interrupt generated using Push Button in order to change the PWM Duty Cycle for External LEDs │
│ ***08_ADC_Polling*** │ Read Potentiometer data using Analog to Digital Converter (ADC) │
│ ***09_ADC_IRQ*** │ Read Potentiometer data using Analog to Digital Converter (ADC) using Interrupts │
│ ***10_ADC_PWM_Polling*** │ Control the Duty Cycle value (%) of PWM for external LED based upon the ADC value obtained from Potentiometer │
│ ***11_ADC_IRQ_PWM*** │ Control the Duty Cycle value (%) of PWM for external LED based upon Interrupts generated by ADC value obtained from Potentiometer │
│ ***12_char_TX*** │ Transmit a single character using USART │
│ ***13_string_TX*** │ Transmit a string using USART │
│ ***14_printf*** │ Customized printf function for USART │
│ ***15_USART_ADC_PWM*** │ Same as 11_ADC_IRQ_PWM along with transmitting the data over USART │
│ ***Template*** │ Reference Project Structure (Used when `stm32-create-project <>`) │

---
