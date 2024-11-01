# STM32F103C8T6 (Blue Pill) Bare Metal Repository
  - Basic Repository for understanding the Registers present in Blue Pill Module
  - Created basic source files to use Registers for controlling purpose
  - Boot Process:
      1. Power ON
      2. Stack Pointer (SP) points to the top of SRAM (Vector Table Offset: 0x00)
      3. Reset_Handler is called (Vector Table Offset: 0x01)
         - (a) Copy ".data" section from FLASH to SRAM (.data referes to initialised variables)
         - (b) Initilise ".bss" section to 0 (.bss referes to uninitialised variables)
         - (c) Main function is called
  - `Projects/Template` is the template which can be used as base while creating New Project

## Repository Structure
  - `BareMetal`: Consists of all the Register Address Mapping along with basic functionality Source Code
  - `Projects`: Consists of User Specific Application
  - `Reference_Docs`: All the Reference Documentation relevant to the topic

## Makefile Basic Commands
  - `make all`: Compiles all the .c files including "BareMetal" directory
  - `make clean`: Cleans all the extra intermediate files used for compiling including "BareMetal" Directory
  - `make user`: Compiles all the .c files present in the folder
  - `make clean_project`: Cleans the extra intermediate files used for compiling present in the Current Directory
  - `make flash`: Flashes Current Project's .bin file at Flash Address (0x080000000)
  - `make erase_flash`: Flashes Template Project's .bin file (Infinite loop) 

## STM32F103C8T6 Pinout
![Blue_PIll_Pinout](https://github.com/user-attachments/assets/13d3a619-ac7a-4799-9715-64730e110f1b)
  - Flash: 64kB (0x08000000)
  - SRAM: 20kB (0x20000000)
  - Vector Table: 76
        - ARM Cortex M3 IRQ: 11
        - STM32F103C8T6: 59 
        - Reserved: 6

## STM32F103C8T6 Reference Manual
[STM32F103C_Reference_Manual.pdf](https://github.com/user-attachments/files/17596951/STM32F103C_Reference_Manual.pdf)

## Project Structure
```
Project_Name
    |- App_Inc
    |    |- main.h                    # Application Header File
    |
    |- App_Src
    |    |- main.c                    # Application Souce File
    |
    |- App_Inc
    |    |- stm32_ls.ld               # Linker Script (Contains the mapping of sections to the address)
    |
    |- App_Inc
    |    |- stm32_startup.c           # Startup File (Contains Vecotor Table Mapping)
    |
    |- Makefile                       # Automation File (Used for compilation and flashing)
```
