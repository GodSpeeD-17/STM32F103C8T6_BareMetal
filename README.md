# STM32F103C8T6 Blue Pill Bare-Metal Repository

This repository is a learning-focused bare-metal codebase for the STM32F103C8T6
Blue Pill board. The goal is to understand the MCU at register level while
gradually shaping the drivers into a modular, layered architecture that can be
maintained and extended without mixing hardware register details with public
driver policy.

The current normalization work is centered on the GPIO stack. GPIO is being used
as the reference design for how future peripheral drivers should be structured.

## Scope

- `BareMetal/Core` owns MCU register maps, base addresses, shared scalar types,
  generic register utilities, startup/linker support, and device constants.
- `BareMetal/Driver` owns reusable peripheral drivers built above the Core
  register model.
- `Projects` owns application examples. Each project selects the driver modules
  it needs through CMake.
- `Reference_Docs` stores datasheets, reference manuals, and board documents.

## GPIO Reference Architecture

The GPIO layer is intentionally split by responsibility. The same separation is
the intended architectural direction for other drivers.

| Layer | Files | Owns | Does Not Own |
|------:|-------|------|--------------|
| Layer 0 | `BareMetal/Core/Inc/stm32f1xx_gpio.h`, `stm32f1xx.h`, `stm32f1xx_data_types.h`, `stm32f1xx_utils.h` | Raw register layout, raw bit masks, base addresses, shared aliases, generic register operations | Driver policy, public configuration vocabulary, board behavior |
| Layer 1 | `BareMetal/Driver/GPIO/Inc/gpio_ll.h`, `gpio_exti_ll.h` | Register-near actions, `.REG` access macros, APB2 GPIO/AFIO clock gates, EXTI/AFIO/NVIC low-level hooks | Public GPIO validation, mode/config compatibility, selector translation |
| Layer 2 | `gpio_helper.h/.c`, `gpio_exti_helper.h/.c` | Translation between driver selectors and raw register fields, staged CRL/CRH/ODR images, hardware-state decoding | Application behavior, clock policy, public API sequencing |
| Layer 3 | `gpio.h/.c`, `gpio_exti.h/.c` | Public GPIO API, argument validation, mode/config compatibility checks, batched register writes, clock-enable sequencing | Raw register definitions, board-specific application logic |
| Layer 4 | `Projects/GPIO/*` | Application use cases such as LED output, button polling, and button interrupts | Driver internals |

### GPIO Design Rules

- Core headers describe hardware. They should stay close to the STM32F1
  reference manual.
- LL headers perform direct hardware-facing operations and use raw register
  masks. They should access registers through `.REG` and avoid driver-level
  selector vocabulary.
- Helper files translate public driver selectors into raw MODE/CNF/pull fields
  and update staged register images before the driver writes hardware.
- Driver files validate requests, enforce mode/config compatibility, batch
  touched register writes, and decide when to enable GPIO or AFIO clocks.
- Project code should call public driver APIs and should not reach into LL or
  helper internals.

### GPIO Functional Scope

The normalized GPIO stack is intended to cover:

- GPIO port clock enable/disable through RCC APB2 clock gates.
- Pin mode and configuration programming through CRL/CRH MODE/CNF fields.
- Input pull-up/pull-down selection through ODR state when required.
- Input sampling through IDR.
- Atomic output set/reset through BSRR/BRR.
- Output toggle through ODR.
- On-board LED convenience helpers built above the public GPIO API.
- EXTI line routing through AFIO EXTICR, trigger configuration, pending-bit
  acknowledgement, and NVIC IRQ enable/disable.

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

Example using the on-board LED GPIO project:

```bash
cd Projects/GPIO/01_OB_LED
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
