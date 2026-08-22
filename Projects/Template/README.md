# Application Template

This directory is the source-only starting point for a new STM32F103C8T6
application. Startup mechanics, application policy, timekeeping, and blocking
delays are deliberately separated so adding one service does not silently
enable another peripheral.

```text
Template/
├── CMakeLists.txt          Build features and Driver-module selection
├── Inc/
│   ├── app_config.h        Application constants and feature visibility
│   ├── app_delay.h         Blocking millisecond and optional microsecond APIs
│   ├── app_init.h          Application-service initialization contract
│   ├── app_startup.h       Reset, linker-symbol, and vector declarations
│   ├── app_time.h          Monotonic millisecond observation APIs
│   ├── main.h              Application entry-point declaration
│   └── systick.h           SysTick-only hardware API
└── Src/
    ├── app_delay.c         SysTick millisecond wait and optional Timer wait
    ├── app_init.c          Clock and explicitly enabled service initialization
    ├── app_time.c          Wrap-safe application time calculations
    ├── main.c              Application behavior only
    ├── startup.c           Vector table, RAM initialization, App_Init, main
    ├── syscalls.c          C-library heap adapter
    └── systick.c           SysTick configuration and minimal tick ISR
```

## Default timing policy

SysTick runs at 1 kHz and increments one 32-bit millisecond counter. It supports
both non-blocking elapsed-time checks and `App_DelayMs()`. The blocking API
sleeps with `WFI` between interrupts; it must not be called from an exception
or while global interrupts are disabled.

TIM2, TIM3, and TIM4 remain unconfigured in the default application.

## Header dependency direction

Template headers form an acyclic, downward-only graph:

```text
main.h                 (standalone application entry declaration)
app_startup.h          -> C standard integer types
app_config.h           (standalone compile-time policy)
app_time.h             -> app_config.h + shared Driver scalar/status types
app_delay.h            -> app_config.h + shared Driver status types
app_init.h             -> shared Driver status types
systick.h              -> shared Driver scalar/status types
```

Peer implementation files may compose these public contracts, but public
headers never include peer implementation headers or rely on transitive
peripheral includes. Full register maps remain confined to `.c` files that
perform hardware access.

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
