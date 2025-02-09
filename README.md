# ***STM32F103C8T6 (Blue Pill) Bare Metal Repository***

---
Hi! I am a beginner and trying to program the Blue Pill Module using Bare Metal (Register Programming). This repository is only meant for learning purpose. Please let me know if there is any mistake and if possible how to resolve it. For any suggestions you can connect with me on LinkedIn: [Shrey Shah](https://www.linkedin.com/in/shreyshah1710/)

Few GitHub Repositories that I referred to during development phase:
- [stm32f1-baremetal](https://github.com/csrohit/stm32f1-baremetal/tree/main)
- [stm32f103-1](https://github.com/freesources/stm32f103-1)
---

---
## ***Description***
  - Basic Repository for understanding the Registers present in Blue Pill Development Module
  - Created basic source files to use Registers for controlling purpose
  - `Projects/Template` is the template which can be used as reference while creating New Project

---
## ***Repository Structure***
  - `BareMetal`: Consists of all the Register Address Mapping along with basic functionality Source Code
  - `Projects`: Consists of User Specific Application
  - `Reference_Docs`: All the Reference Documentation relevant to the topic

---
## ***STM32F103C8T6 Reference Manual***
[STM32F103C_Reference_Manual.pdf](https://github.com/user-attachments/files/17964492/STM32F103C_Reference_Manual.pdf)

---
## ***STM32F103C8T6 Pinout***
![Blue_PIll_Pinout](https://github.com/user-attachments/assets/13d3a619-ac7a-4799-9715-64730e110f1b)

---
## ***STM32F103C8T6 Features (Medium Density Device)***
| Specification      | Details        | Comments            |
|--------------------|----------------|---------------------|
| Processor          | ARM Cortex-M3  | Single Core         |
| Clock Frequency    | Min: 8MHz      | HSI: 8MHz           |
|                    | Max: 72MHz     | HSE: 8MHz           |
| Flash              | Size: 64kB     | Address: 0x08000000 |
| SRAM               | Size: 20kB     | Address: 0x20000000 |

---
## ***IRQ Details***
| **Vector Table**         | 76 |
|---------------------------|----|
| ***ARM Cortex-M3 IRQ***   | 11 |
| ***STM32F103C8T6 IRQ***   | 59 |
| ***Reserved***            | 6  |

---
## ***Boot Process***
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
STM32F103C8T6
      ├── BareMetal                         # Main Baremetal Programming Library
      │   ├── Core                          # Core Cortex-M3 Functions & Register Mapping
      │   │   ├── Inc                       # Register along with bits Mapping
      │   │   │   ├── adc_reg_map.h         # ADC Register Mapping
      │   │   │   ├── advtim_reg_map.h      # Advanced Timer Register Mapping
      │   │   │   ├── afio_reg_map.h        # Alternate Function I/O Register Mapping
      │   │   │   ├── cmsis_gcc.h           # Core Cortex-M3 Functions
      │   │   │   ├── common.h
      │   │   │   ├── exti_reg_map.h        # External Interrupt Register Mapping
      │   │   │   ├── flash_reg_map.h       # Flash Register Mapping
      │   │   │   ├── gpio_reg_map.h        # Flash Register Mapping
      │   │   │   ├── nvic_reg_map.h        # Nested Vector Interrupt Controller Register Mapping
      │   │   │   ├── rcc_reg_map.h         # Reset and Clock Control Register Mapping
      │   │   │   ├── systick_reg_map.h     # SysTick Register Mapping (Cortex-M3 24-bit down counter)
      │   │   │   ├── timer_reg_map.h       # General Purpose Timer Register Mapping
      │   │   │   ├── usart_reg_map.h       # Universal Synchronous Asynchronous Receiver Transmitter Register Mapping
      │   │   │   └── wwdg_reg_map.h        # Window Watchdog Register Mapping
      │   │   └── Src                       # Debugging Configuration Files Requirement
      │   │       ├── stlink.cfg
      │   │       ├── STM32F103.svd
      │   │       └── stm32f1x.cfg
      │   └── Driver                        # Actual BareMetal Codes
      │       ├── Inc                       # Header Files
      │       │   ├── adc.h
      │       │   ├── bare_metal.h
      │       │   ├── exti.h
      │       │   ├── gpio.h
      │       │   ├── nvic.h
      │       │   ├── pwm.h
      │       │   ├── rcc.h
      │       │   ├── reg_map.h
      │       │   ├── systick.h
      │       │   ├── timer.h
      │       │   └── usart.h
      │       └── Src                       # Source Files
      │           ├── adc.c
      │           ├── exti.c
      │           ├── gpio.c
      │           ├── pwm.c
      │           ├── rcc.c
      │           ├── systick.c
      │           ├── timer.c
      │           └── usart.c
      ├── Projects                          # Project Specific Codes
      │   ├── GPIO                          # General Purpose I/O Programming
      │   │   ├── 01_LED
      │   │   │   ├── Inc
      │   │   │   │   └── main.h
      │   │   │   ├── Makefile
      │   │   │   ├── Src
      │   │   │   │   └── main.c
      │   │   │   └── Startup
      │   │   │       ├── stm32f1_ls.ld
      │   │   │       └── stm32f1_startup.c
      │   │   ├── 02_PB_Poll
      │   │   │   ├── Inc
      │   │   │   │   └── main.h
      │   │   │   ├── Makefile
      │   │   │   ├── Src
      │   │   │   │   └── main.c
      │   │   │   └── Startup
      │   │   │       ├── stm32f1_ls.ld
      │   │   │       └── stm32f1_startup.c
      │   │   └── 03_PB_IRQ
      │   │       ├── Inc
      │   │       │   └── main.h
      │   │       ├── Makefile
      │   │       ├── Src
      │   │       │   └── main.c
      │   │       └── Startup
      │   │           ├── stm32f1_ls.ld
      │   │           └── stm32f1_startup.c
      │   ├── Template                          # Template for New Projects
      │   │   ├── Inc
      │   │   │   └── main.h
      │   │   ├── Makefile
      │   │   ├── Src
      │   │   │   └── main.c
      │   │   └── Startup
      │   │       ├── stm32f1_ls.ld
      │   │       └── stm32f1_startup.c
      │   ├── Timer                             # Timer Programming
      │   │   ├── 04_Timer_Poll
      │   │   │   ├── Inc
      │   │   │   │   └── main.h
      │   │   │   ├── Makefile
      │   │   │   ├── Src
      │   │   │   │   └── main.c
      │   │   │   └── Startup
      │   │   │       ├── stm32f1_ls.ld
      │   │   │       └── stm32f1_startup.c
      │   │   ├── 05_Timer_IRQ
      │   │   │   ├── Inc
      │   │   │   │   └── main.h
      │   │   │   ├── Makefile
      │   │   │   ├── Src
      │   │   │   │   └── main.c
      │   │   │   └── Startup
      │   │   │       ├── stm32f1_ls.ld
      │   │   │       └── stm32f1_startup.c
      │   │   ├── images
      │   │   │   └── Block Diagram.png
      │   │   └── README.md
      │   └── USART                             # USART Programming
      │       ├── 12_char_TX
      │       │   ├── Inc
      │       │   │   └── main.h
      │       │   ├── Makefile
      │       │   ├── Src
      │       │   │   └── main.c
      │       │   └── Startup
      │       │       ├── stm32f1_ls.ld
      │       │       └── stm32f1_startup.c
      │       ├── 13_string_TX
      │       │   ├── Inc
      │       │   │   └── main.h
      │       │   ├── Makefile
      │       │   ├── Src
      │       │   │   └── main.c
      │       │   └── Startup
      │       │       ├── stm32f1_ls.ld
      │       │       └── stm32f1_startup.c
      │       └── 14_printf
      │           ├── Inc
      │           │   └── main.h
      │           ├── Makefile
      │           ├── Src
      │           │   └── main.c
      │           └── Startup
      │               ├── stm32f1_ls.ld
      │               └── stm32f1_startup.c
      ├── README.md
      └── Reference_Docs
          ├── Arm Cortex M3 Reference.pdf
          ├── Blue_PIll_Pinout.gif
          ├── STM32F103C_Flash_Programming_Manual.pdf
          ├── STM32F103C_Reference_Manual.pdf
          └── STM32F103xx_Flash_Reference_Manual.pdf
```

## ***BareMetal Structure***
```
BareMetal
    ├── Core
    │   ├── Inc
    │   │   ├── adc_reg_map.h
    │   │   ├── advtim_reg_map.h
    │   │   ├── afio_reg_map.h
    │   │   ├── cmsis_gcc.h
    │   │   ├── common.h
    │   │   ├── exti_reg_map.h
    │   │   ├── flash_reg_map.h
    │   │   ├── gpio_reg_map.h
    │   │   ├── nvic_reg_map.h
    │   │   ├── rcc_reg_map.h
    │   │   ├── systick_reg_map.h
    │   │   ├── timer_reg_map.h
    │   │   ├── usart_reg_map.h
    │   │   └── wwdg_reg_map.h
    │   └── Src
    │       ├── stlink.cfg
    │       ├── STM32F103.svd
    │       └── stm32f1x.cfg
    └── Driver
        ├── Inc
        │   ├── adc.h
        │   ├── bare_metal.h
        │   ├── exti.h
        │   ├── gpio.h
        │   ├── nvic.h
        │   ├── pwm.h
        │   ├── rcc.h
        │   ├── reg_map.h
        │   ├── systick.h
        │   ├── timer.h
        │   └── usart.h
        └── Src
            ├── adc.c
            ├── exti.c
            ├── gpio.c
            ├── pwm.c
            ├── rcc.c
            ├── systick.c
            ├── timer.c
            └── usart.c
```

---
## ***Project Structure***
---
```
<Project_Name>
      ├── Inc
      │   └── main.h
      ├── Makefile
      ├── Src
      │   └── main.c
      └── Startup
          ├── stm32f1_ls.ld
          └── stm32f1_startup.c
```

---
## ***Makefile Basic Commands***
  - `make all`: Compiles all the .c files including "BareMetal" directory into a "Build" Directory
  - `make clean`: Cleans all the extra intermediate files used for compiling including "BareMetal" Directory
  - `make flash`: Flashes Current Project's .bin file at Flash Address (0x080000000)
  - `make erase_flash`: Erases the Flash Memory of Blue Pill Module
  - `make debug`: Creates the .json debug related files for Arm-Cortex Debug (VS Code) inside a .vscode directory
  - `make replace_makefiles`: Updates all Makefiles inside "Project" directory with current Makefile

---
## ***Project Overview***
| **Projects**            | **Description**                                                                                      |
|-------------------------|------------------------------------------------------------------------------------------------------|
| ***01_LED***            | A simple LED blinking                                                                                |
| ***02_PB_Poll***        | A simple LED blinking based on polling the status of Push Button                                    |
| ***03_PB_IRQ***         | A simple LED blinking based on Interrupt generated by Push Button                                   |
| ***04_Timer_Poll***     | Delay generation based upon General Purpose Timer (GPT)                                            |
| ***05_Timer_IRQ***      | Interrupt generation using General Purpose Timer (GPT)                                              |
| ***06_PWM_Polling***    | Pulse Width Modulation (PWM) generation using General Purpose Timer (GPT)                           |
| ***07_PWM_PB_IRQ***     | Use the Interrupt generated using Push Button in order to change the PWM Duty Cycle for External LEDs |
| ***08_ADC_Polling***    | Read Potentiometer data using Analog to Digital Converter (ADC)                                     |
| ***09_ADC_IRQ***        | Read Potentiometer data using Analog to Digital Converter (ADC) using Interrupts                     |
| ***10_ADC_PWM_Polling***| Control the Duty Cycle value (%) of PWM for external LED based upon the ADC value obtained from Potentiometer |
| ***11_ADC_IRQ_PWM***    | Control the Duty Cycle value (%) of PWM for external LED based upon Interrupts generated by ADC value obtained from Potentiometer |
| ***12_char_TX***        | Transmit a single character using USART                                                               |
| ***13_string_TX***      | Transmit a string using USART                                                                         |
| ***14_printf***         | Customized printf function for USART                                                                  |
| ***15_USART_ADC_PWM***  | Same as 11_ADC_IRQ_PWM along with transmitting the data over USART                                   |
| ***16_char_RX***        | Receive a character using Polling on USART peripheral and toggle LED based upon received character   |
| ***17_string_RX***      | Receive a string using USART                                                                         |
| ***18_USART_IRQ***      | Receive a character using USART IRQ -> 3 Methods Demo Code Provided                                  |
| ***Template***          | Reference Project Structure (Used when `stm32-create-project <>`)                                    |

---
