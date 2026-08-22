# Application Template

This directory is the source-only starting point for a new STM32F103C8T6
application. Startup mechanics, application policy, timekeeping, and blocking
delays are deliberately separated so adding one service does not silently
enable another peripheral.

Runtime dependencies move downward through four layers:

```text
Layer 4: Entry              app_startup
Layer 3: Orchestration      app_init, main
Layer 2: Services           app_time, app_delay
Layer 1: Hardware access    shared SysTick, RCC, and Timer Drivers
```

Layer numbering always begins at the hardware boundary. Layer 1 owns direct
hardware access; each higher number adds software service, policy, behavior, or
orchestration. Dependencies may point toward a lower layer, never upward.

`app_config.h` is standalone compile-time policy consumed by Layers 2 and 3;
it is not a runtime layer and performs no initialization.

```text
Template/
├── CMakeLists.txt          Build features and Driver-module selection
├── Inc/
│   ├── app_config.h        Application constants and feature visibility
│   ├── app_delay.h         Blocking millisecond and optional microsecond APIs
│   ├── app_init.h          Application-service initialization contract
│   ├── app_startup.h       Reset ABI and linker-symbol declarations
│   ├── app_time.h          Timebase state, observation, and handler ABI
│   └── main.h              Application entry-point declaration
└── Src/
    ├── app_delay.c         SysTick millisecond wait and optional Timer wait
    ├── app_init.c          Clock and explicitly enabled service initialization
    ├── app_startup.c       Vector table, RAM initialization, App_Init, main
    ├── app_time.c          Millisecond state, calculations, and minimal ISR
    ├── main.c              Application behavior only
    └── syscalls.c          C-library heap adapter
```

Reusable SysTick hardware lives outside the copied project:

```text
BareMetal/Driver/SysTick/
├── Inc/
│   ├── systick.h           Public hardware configuration and state API
│   └── systick_ll.h        Full-width register access only
├── Src/
│   └── systick.c           Validation and register transaction orchestration
└── SYSTICK.md              Hardware and implementation guide
```

## Default timing policy

The shared SysTick Driver configures hardware, but `app_time.c` owns the strong
`SysTick_Handler()` and one 32-bit millisecond counter. The interrupt performs
one increment only. Main context uses the counter for non-blocking elapsed-time
checks, while `App_DelayMs()` provides an optional blocking wait that sleeps
with `WFI` between interrupts. The blocking API must not be called from an
exception or while global interrupts are disabled.

TIM2, TIM3, and TIM4 remain unconfigured in the default application.

## Header dependency direction

Template headers form an acyclic, downward-only graph:

```text
main.h                 (standalone application entry declaration)
app_config.h           (standalone compile-time policy)
app_startup.h          -> shared Core scalar/status types
app_time.h             -> app_config.h + shared Core scalar/status types
app_delay.h            -> app_config.h + shared Core scalar/status types
app_init.h             -> shared Core status types
```

Peer implementation files may compose these public contracts, but public
headers never include peer implementation headers or rely on transitive
peripheral includes. Full register maps remain confined to `.c` files that
perform hardware access. Every header with external declarations provides an
`extern "C"` guard so the same declarations remain link-safe when included by
C++ application code. Template files obtain fixed-width integers and shared
repository types directly from `stm32f1xx_data_types.h`; they do not include
`<stdint.h>` themselves.

## Complete implementation chain

The implementation direction is also one-way:

```text
Processor reset
└── app_startup.c
    ├── app_startup.h -> shared Core scalar/status types
    ├── app_init.c
    │   ├── RCC Driver
    │   ├── app_time.c
    │   │   └── shared SysTick Driver -> SysTick LL -> Core register map
    │   └── app_delay.c [optional Timer initialization]
    │       ├── RCC Driver
    │       └── Timer Driver
    └── main.c
        └── app_time.c

Application blocking delay
└── app_delay.c
    ├── app_time.c [milliseconds]
    └── Timer Driver [optional microseconds]

C library allocation
└── syscalls.c -> linker heap symbols
```

Lower services never include their consumers: the SysTick Driver does not
include `app_time`, `app_time` does not include `app_delay`, and no Driver
includes an application header. The vector table refers to the handler ABI,
while the enabled application time service supplies its strong definition.
Every C and header file states its hierarchy position, responsibility, direct
users/dependencies, and prohibited ownership at the top so its boundary remains
understandable when the file is read by itself.

## Optional SysTick timebase

The timebase is enabled by default. Disable it at configure time when an
application does not need elapsed milliseconds or `App_DelayMs()`:

```sh
cmake -S . -B Build -DAPP_ENABLE_SYSTICK_TIMEBASE=OFF
```

This removes the SysTick Driver module, the strong application handler, and all
timebase APIs from the build. Startup retains only its weak fallback handler;
SysTick hardware remains untouched.

## Optional microsecond delay

Enable the dedicated TIM4 service at configure time:

```sh
cmake -S . -B Build -DAPP_ENABLE_TIMER_US_DELAY=ON
```

This single option adds the Timer Driver module, exposes `App_DelayUs()`,
enables the TIM4 clock during `App_Init()`, and configures TIM4 as the dedicated
1 MHz polling-delay Timer. Timer IRQ and NVIC state remain untouched.

Leave the option disabled when the application does not require microsecond
blocking delays. Millisecond timing continues to use SysTick and does not
reserve a general-purpose Timer.
