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

The target-oriented build system, project-facing CMake contract, Driver
dependency graph, generated tooling, and current migration state are documented
in [`CMAKE_ARCHITECTURE.md`](./CMAKE_ARCHITECTURE.md).

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
│       ├── BSP
│       ├── DMA
│       ├── GPIO
│       ├── I2C
│       ├── NVIC
│       ├── RCC
│       ├── Ring_Buffer
│       ├── SSD1306
│       ├── SysTick
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
├── CMAKE_ARCHITECTURE.md
├── Doxyfile
└── README.md
```

## Project Layout

New applications copied from `Projects/Template` follow this modular shape:

```text
<Project_Name>
├── CMakeLists.txt
├── Inc
│   ├── app_config.h
│   ├── app_delay.h
│   ├── app_init.h
│   ├── app_startup.h
│   ├── app_time.h
│   └── main.h
└── Src
    ├── app_delay.c
    ├── app_init.c
    ├── app_startup.c
    ├── app_time.c
    ├── main.c
    └── syscalls.c
```

Some existing examples still retain the legacy project-local `startup.c` and
`systick.c` layout while they are migrated. Their source layout does not change
the shared target-oriented CMake contract described below.

Project `CMakeLists.txt` files call:

- `stm32f103_setup_toolchain()` before `project(...)` to select the canonical
  Arm GNU toolchain file.
- `stm32f103_configure_project(...)` after `project(...)` to create the
  firmware and utility targets.
- `DRIVER_MODULES` to select application capabilities. Direct Driver
  dependencies are resolved by the shared component graph.

The shared pipeline represents build policy, Core, and every selected Driver
as separate CMake targets. Each component owns its sources, include directory,
and direct dependencies; the application target owns only application sources,
feature definitions, and the final linker transaction.

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
by `BareMetal/CMake/Toolchains/arm-none-eabi-gcc.cmake`.

Generate VS Code metadata only when it is required:

```bash
cmake --build Build --target vscode_files
```

The generated editor configuration reads `Build/compile_commands.json`, so
IntelliSense observes the exact compiler definitions, include paths, and flags
used by the active application configuration.

Projects stored inside this repository locate the shared `BareMetal` build
infrastructure automatically. A project copied outside the repository can select
that infrastructure explicitly:

```bash
cmake -S . -B Build \
    -DSTM32F103_REPO_ROOT=/absolute/path/to/STM32F103C8T6
```

`STM32F103_REPO_ROOT` must identify the directory that contains `BareMetal`.

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
