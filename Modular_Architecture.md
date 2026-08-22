# Application Template Modular Architecture

This document records the locked project convention implemented by
`Projects/Template`. A copied project owns startup, policy, orchestration, and
application services. Reusable peripheral hardware behavior remains in shared
Drivers.

## Goal

Every copied file has one clear reason to change, every dependency points
toward hardware, and disabling an application capability removes its Driver
module without requiring source deletion.

## Layer hierarchy

Layer numbers start at hardware. Higher numbers contain progressively more
software-only policy and orchestration.

```text
Layer 4  Processor entry
         app_startup
             │
Layer 3  Application orchestration
         app_init, main
             │
Layer 2  Application services
         app_time, app_delay
             │
Layer 1  Reusable hardware access
         SysTick Driver, RCC Driver, Timer Driver
             │
Layer 0  Core register model
         stm32f1xx_* register headers
```

`app_config.h` is cross-cutting compile-time policy, not a runtime layer. It is
read by Layers 2 and 3 and performs no transaction.

Dependencies may move downward or between cohesive peers in one layer. They
must not move upward. In particular, a Driver must never include an application
header or call an application service.

## Copied project structure

```text
Projects/Template/
├── CMakeLists.txt
├── Inc/
│   ├── app_config.h
│   ├── app_delay.h
│   ├── app_init.h
│   ├── app_startup.h
│   ├── app_time.h
│   └── main.h
└── Src/
    ├── app_delay.c
    ├── app_init.c
    ├── app_startup.c
    ├── app_time.c
    ├── main.c
    └── syscalls.c
```

All reusable project-owned module names use `app_*.*`. `main.[ch]` and
`syscalls.c` retain their conventional roles. Processor, linker, and C-library
ABI symbols retain their mandated names even when their implementation belongs
to an `app_*` module.

The copied project deliberately contains no local `systick.[ch]`. Those names
belong to the shared hardware Driver:

```text
BareMetal/Driver/SysTick/
├── Inc/
│   ├── systick.h
│   └── systick_ll.h
├── Src/
│   └── systick.c
└── SYSTICK.md
```

## File ownership

| File | Owns | Must not own |
| --- | --- | --- |
| `app_startup.[ch]` | Linker symbols, vector table, reset memory initialization, weak fallbacks, transfer to `App_Init()` and `main()` | Clock policy, delay implementation, software ticks, Driver configuration |
| `app_config.h` | Compile-time capabilities, service constants, optional hardware selection | Functions, register headers, runtime sequencing |
| `app_init.[ch]` | Ordered application bring-up and first-error propagation | Raw register access, service implementation, main behavior |
| `app_time.[ch]` | Millisecond accumulator, elapsed-time API, timebase adaptation, strong `SysTick_Handler()` | Direct register access, callback execution inside IRQ, general-purpose Timer ownership |
| `app_delay.[ch]` | Blocking delay policy: SysTick-backed milliseconds and optional Timer-backed microseconds | Startup mechanics, SysTick hardware configuration, Timer IRQ policy |
| `main.[ch]` | Application behavior and main-context event consumption | Startup, Driver internals, ISR work |
| `syscalls.c` | C-library syscall bridges such as `_sbrk()` | Application initialization and peripheral policy |
| shared SysTick Driver | SysTick root configuration, IRQ-source state, operation state, current-value reset | Application tick, time unit, handler, callbacks |

## Reset and runtime flow

```text
Processor reset
└── Reset_Handler                         Layer 4
    ├── copy .data / clear .bss
    ├── App_Init                          Layer 3
    │   ├── RCC_Config_72MHz              Layer 1
    │   ├── App_TimeInit [optional]       Layer 2
    │   │   └── SysTick Driver            Layer 1
    │   └── App_DelayTimerInit [optional] Layer 2
    │       ├── RCC Driver                Layer 1
    │       └── Timer Driver              Layer 1
    └── main                              Layer 3
```

`app_startup.c` performs only processor/runtime entry work. It neither selects
a delay backend nor configures SysTick, Timer, RCC, GPIO, or board behavior.

## SysTick ownership and interrupt flow

SysTick hardware and application time are intentionally separated:

```text
Configuration path
App_TimeInit
└── SysTick_DeConfig
    SysTick_SetConfig
    SysTick_ResetCurrentValue
    SysTick_SetIRQState(ON)
    SysTick_SetOperationState(ON)

Interrupt path
SysTick exception
└── SysTick_Handler in app_time.c
    └── appTickMs++

Main-context path
main / app_delay
└── App_TimeGetTickMs / App_TimeGetElapsedMs
```

The shared Driver contains no `SysTick_Handler()` and no software tick. The
application handler performs exactly one increment and returns. Scheduling,
I/O, callbacks, state machines, and all other work remain in main context.

`app_startup.c` retains a weak `SysTick_Handler()` fallback because the vector
table always requires an entry. When the timebase is enabled, the strong
definition from `app_time.c` replaces it. When disabled, the fallback remains
and the SysTick Driver is not linked.

## Blocking and non-blocking time

The two needs coexist without sharing a general-purpose Timer by default:

- `App_TimeGetTickMs()` and `App_TimeGetElapsedMs()` support non-blocking,
  wrap-safe scheduling.
- `App_DelayMs()` performs a blocking wait over the same monotonic timebase and
  sleeps with `WFI` between interrupts.
- optional `App_DelayUs()` reserves TIM4 for precise polling-based microsecond
  delays without Timer IRQ or NVIC delivery.

TIM4 is configured only when `APP_ENABLE_TIMER_US_DELAY` is enabled. No Timer is
touched by default.

## Feature-to-build mapping

| CMake option | Default | Added Driver | Application result |
| --- | --- | --- | --- |
| `APP_ENABLE_SYSTICK_TIMEBASE` | `ON` | SysTick | `app_time`, non-blocking elapsed time, and `App_DelayMs()` become operational |
| `APP_ENABLE_TIMER_US_DELAY` | `OFF` | Timer | TIM4 polling service and `App_DelayUs()` are enabled |

RCC remains the only unconditional Driver because the Template always applies
its 72 MHz clock preset. Feature options are also emitted as compile definitions
so source visibility and linked Driver modules cannot disagree.

## Header dependency graph

Public Template headers remain hardware-independent:

```text
main.h                 -> no header
app_startup.h          -> stm32f1xx_data_types.h
app_init.h             -> stm32f1xx_data_types.h
app_config.h           -> no header
app_time.h             -> app_config.h + stm32f1xx_data_types.h
app_delay.h            -> app_config.h + stm32f1xx_data_types.h
```

Implementation-only dependencies are private:

```text
app_init.c  -> app_config + app_time + app_delay + RCC Driver
app_time.c  -> app_time + SysTick Driver [feature enabled]
app_delay.c -> app_delay + app_time + RCC/Timer Drivers [as required]
```

Every Template header that declares external symbols carries a C++ linkage
guard. Template code obtains fixed-width and shared repository types through
`stm32f1xx_data_types.h`, never by directly including `<stdint.h>`.

## SysTick Driver contract

The shared Driver exposes four cohesive domains:

1. complete hardware reset through `SysTick_DeConfig()`,
2. register-semantic root configuration through the
   `SysTick_GetConfig()` / `SysTick_SetConfig()` pair,
3. exception-source state through the
   `SysTick_GetIRQState()` / `SysTick_SetIRQState()` pair,
4. counter-operation state through the
   `SysTick_GetOperationState()` / `SysTick_SetOperationState()` pair.

`SysTick_ResetCurrentValue()` is deliberately asymmetric because any write to
`VAL` is a hardware clear action; an arbitrary setter would be false. Root
configuration preserves the separate IRQ-source domain and never performs
deconfiguration implicitly. The application owns teardown-before-setup order.

No Codec layer is present because the admitted clock selector and reload value
are already exact register-semantic payloads. LL performs one named mechanical
register access; Driver performs validation and preservation; application code
provides time units and interrupt policy.

## Audit order for a new project

Read and modify the copied project in dependency order:

1. `app_config.h` — select capabilities and constants.
2. `app_time.[ch]` — understand monotonic time and the minimal handler.
3. `app_delay.[ch]` — understand blocking delay behavior and optional TIM4.
4. `app_init.[ch]` — verify ordered service bring-up.
5. `main.[ch]` — implement main-context behavior.
6. `app_startup.[ch]` — audit the stable reset/vector ABI last.
7. `syscalls.c` — audit only when C-library heap behavior matters.

This order follows data and control dependencies from policy through services
to orchestration, then finishes with stable platform entry code.
