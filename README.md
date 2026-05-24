# STM32F103C8T6 Blue Pill Bare-Metal Repository

This repository is a learning-focused bare-metal codebase for the STM32F103C8T6
Blue Pill board. The goal is to understand the MCU at register level while
gradually shaping the drivers into a modular, layered architecture that can be
maintained and extended without mixing hardware register details with public
driver policy.

The current normalization work is focused on defining a reusable driver
architecture that each peripheral module can follow consistently.

## Scope

- `BareMetal/Core` owns MCU register maps, base addresses, shared scalar types,
  generic register utilities, startup/linker support, and device constants.
- `BareMetal/Driver` owns reusable peripheral drivers built above the Core
  register model.
- `Projects` owns application examples. Each project selects the driver modules
  it needs through CMake.
- `Reference_Docs` stores datasheets, reference manuals, and board documents.

## Architecture

The intended repository-wide driver architecture is documented in
[`ARCHITECTURE.md`](./ARCHITECTURE.md).

That document defines the reusable layer boundaries for all peripheral drivers:
Core, shared driver types, low-level hardware access, helper translation/staging,
public driver orchestration, and project/application code. Driver development
should follow those rules unless a peripheral has a clearly documented reason to
deviate.

## Repository Layout

```text
.
├── BareMetal
│   ├── CMake
│   ├── Core
│   │   ├── Inc
│   │   └── Src
│   └── Driver
│       ├── ADC
│       ├── DMA
│       ├── GPIO
│       ├── I2C
│       ├── NVIC
│       ├── PWM
│       ├── RCC
│       ├── Ring_Buffer
│       ├── SSD1306
│       ├── Timer
│       └── USART
├── Projects
│   ├── DMA
│   ├── GPIO
│   ├── PWM
│   ├── Template
│   ├── Timer
│   └── USART
├── Reference_Docs
├── ARCHITECTURE.md
├── Doxyfile
└── README.md
```

## Project Layout

Each example project follows the same shape:

```text
<Project_Name>
├── CMakeLists.txt
├── Inc
│   ├── main.h
│   └── systick.h
└── Src
    ├── main.c
    ├── startup.c
    └── systick.c
```

Project `CMakeLists.txt` files call:

- `stm32f103_setup_toolchain()` before `project(...)`.
- `stm32f103_configure_project(...)` after `project(...)`.
- `DRIVER_MODULES` to select only the required driver modules.

## Build Workflow

Example using the template project:

```bash
cd Projects/Template
cmake -S . -B Build
cmake --build Build
```

Useful CMake targets:

```bash
cmake --build Build --target flash
cmake --build Build --target flash_uart
cmake --build Build --target erase_flash
cmake --build Build --target debug
cmake --build Build --target clean_all
cmake --build Build --target info
```

The shared CMake pipeline generates `.elf`, `.bin`, `.hex`, a memory report, and
optional VS Code debug metadata. The default Arm GNU toolchain path is configured
in `BareMetal/CMake/STM32F103Project.cmake`.

## Device Notes

| Specification | Details | Notes |
|---------------|---------|-------|
| MCU | STM32F103C8T6 | Medium-density STM32F1 |
| Core | Arm Cortex-M3 | Single core |
| HSI | 8 MHz | Internal oscillator |
| HSE | 8 MHz | Common Blue Pill external crystal |
| Max SYSCLK | 72 MHz | Device limit |
| Flash | 64 KB | Base `0x08000000` |
| SRAM | 20 KB | Base `0x20000000` |

## References

- [STM32F103C Reference Manual](./Reference_Docs/STM32F103C_Reference_Manual.pdf)
- [STM32F103C8T6 Datasheet](./Reference_Docs/STM32F103C8T6_Datasheet.pdf)
- [Blue Pill Pinout](./Reference_Docs/Blue_Pill_Pinout.gif)

Learning references used during development:

- [stm32f1-baremetal](https://github.com/csrohit/stm32f1-baremetal/tree/main)
- [stm32f103-1](https://github.com/freesources/stm32f103-1)
