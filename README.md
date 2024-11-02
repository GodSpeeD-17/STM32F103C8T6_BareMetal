# **STM32F103C8T6 (Blue Pill) Bare Metal Repository**

## Description
  - Basic Repository for understanding the Registers present in Blue Pill Module
  - Created basic source files to use Registers for controlling purpose
  - `Projects/Template` is the template which can be used as base while creating New Project

## Repository Structure
  - `BareMetal`: Consists of all the Register Address Mapping along with basic functionality Source Code
  - `Projects`: Consists of User Specific Application
  - `Reference_Docs`: All the Reference Documentation relevant to the topic

## STM32F103C8T6 Reference Manual
[STM32F103C_Reference_Manual.pdf](https://github.com/user-attachments/files/17596951/STM32F103C_Reference_Manual.pdf)

## STM32F103C8T6 Pinout
![Blue_PIll_Pinout](https://github.com/user-attachments/assets/13d3a619-ac7a-4799-9715-64730e110f1b)

## STM32F103C8T6 Features
  - Processor: ARM Cortex-M3 (Single Core)
  - Clock Frequency: 8MHz - 72MHz
  - Flash: 64kB (0x08000000)
  - SRAM: 20kB (0x20000000)
  - Vector Table: 76
    - ARM Cortex-M3 IRQ: 11
    - STM32F103C8T6 IRQ: 59 
    - Reserved: 6

## Boot Process:
  - Power ON
  - Stack Pointer (SP) points to the top of SRAM (Vector Table Offset: 0x00)
  - Reset_Handler is called (Vector Table Offset: 0x01)
    1. Copy ".data" section from FLASH to SRAM (.data refers to initialized variables)
    2. Initialize ".bss" section to 0 (.bss refers to uninitialized variables)
    3. Main function is called

## BareMetal Structure
```
BareMetal
    |- Inc
    |  |- Core
    |  |  |- advtim_reg_map.h          # Advanced Timer Structure {TIM1, -TIM8-}
    |  |  |- afio_reg_map.h            # Alternate Function Input Output (AFIO) Structure
    |  |  |- flash_reg_map.h           # Flash Structure
    |  |  |- gpio_reg_map.h            # General Purpose Input Output (GPIO) Structure
    |  |  |- gpt_reg_map.h             # General Purpose Timer (GPT) Structure {TIM2, TIM3, TIM4, -TIM5-}
    |  |  |- nvic_reg_map.h            # Nested Vector Interrupt Control (NVIC) Structure
    |  |  |- rcc_reg_map.h             # Reset and Clock Control (RCC) Structure
    |  |  |- systick_reg_map.h         # SysTick Structure
    |  |  |- wwdg_reg_map.h            # Window Watchdog (WWDG) Structure
    |  |- gpio.h                       # GPIO Header File
    |  |- nvic.h                       # NVIC Header File
    |  |- pwm.h                        # PWM Header File
    |  |- rcc.h                        # Clock Configuration Header File
    |  |- reg_map.h                    # Main Register Mapping Header File
    |  |- systick.h                    # SysTick Header File (ARM Cortex-M3)
    |  |- timer.h                      # Timer Header File
    |
    |- Src
    |  |- gpio.c                       # GPIO Source File
    |  |- pwm.c                        # PWM Source File
    |  |- rcc.c                        # Clock Configuration Source File
    |  |- systick.c                    # SysTick Source File (ARM Cortex-M3)
    |  |- timer.c                      # Timer Source File
```

## Project Structure
```
<Project_Name>
      |- App_Inc
      |    |- main.h                    # Application Header File
      |
      |- App_Src
      |    |- main.c                    # Application Source File
      |
      |- Linker
      |    |- stm32_ls.ld               # Linker Script (Contains the mapping of sections to the address)
      |
      |- Startup
      |    |- stm32_startup.c           # Startup File (Contains Vector Table Mapping)
      |
      |- Makefile                       # Automation File (Used for compilation and flashing)
```

## Makefile Basic Commands
  - `make all`: Compiles all the .c files including "BareMetal" directory
  - `make clean`: Cleans all the extra intermediate files used for compiling including "BareMetal" Directory
  - `make user`: Compiles all the .c files present in the folder
  - `make clean_project`: Cleans the extra intermediate files used for compiling present in the Current Directory
  - `make flash`: Flashes Current Project's .bin file at Flash Address (0x080000000)
  - `make erase_flash`: Flashes Template Project's .bin file (Infinite loop)
