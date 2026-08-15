# Project Template Modular Architecture

This document captures the intended modular architecture for project templates
in this repository. It is meant to be session independent: a future development
session should be able to read this file and understand the current problem,
why the existing template deviates from the desired structure, and how to
migrate the project files without needing prior conversation context.

This document complements the repository-wide driver architecture in
`ARCHITECTURE.md`. That file defines reusable driver layer boundaries. This file
defines project-template boundaries: startup/runtime boot, project
initialization, delay policy, SysTick ownership, and application code.

## Goal

Make every project template file have one clear reason to change.

The project template should be reusable across GPIO, Timer, USART, DMA, PWM, and
future examples without turning `startup.c` into a central dumping ground for
runtime boot, board setup, delay implementation, Timer IRQ policy, and
application behavior.

## Current Context

The current project shape is:

```text
Projects/Template
├── CMakeLists.txt
├── Inc
│   ├── main.h
│   └── systick.h
└── Src
    ├── main.c
    ├── startup.c
    └── systick.c
```

`Projects/Timer/04_Timer_Poll` follows the same basic shape.

The current template CMake selects these driver modules:

```text
RCC
GPIO
BSP
NVIC
Timer
```

The shared startup header is:

```text
BareMetal/Driver/startup.h
```

That shared header currently provides:

- linker-symbol declarations
- vector table
- weak default handlers
- default delay Timer selection through `DELAY_TIMER`
- `DELAY_TIMER_IRQHandler` mapping

With `SYSTICK_DELAY__` not defined, the current template uses Timer-based delay
logic. The default delay Timer is currently `TIM4`.

## Current Deviation

`Projects/Template/Src/startup.c` currently owns too many unrelated concerns.

It currently does all of the following:

```text
1. Copies .data from Flash to RAM
2. Clears .bss
3. Implements _sbrk() heap bridge
4. Configures the 72 MHz system clock
5. Configures SysTick
6. Configures Timer as a 1 MHz delay source
7. Enables Timer IRQ for delay completion
8. Implements delay_us()
9. Implements delay_ms()
10. Implements the delay Timer IRQ handler
11. Initializes board LED state
12. Calls main()
```

This is the main modularity problem. A startup file should not know the project
delay backend, Timer IRQ policy, board LED initialization, or application delay
API.

## Why This Is A Problem

The current structure gives `startup.c` too many reasons to change.

If the delay backend changes from Timer to SysTick, `startup.c` changes.

If the board initialization policy changes, `startup.c` changes.

If heap allocation behavior changes, `startup.c` changes.

If clock setup changes, `startup.c` changes.

If Timer IRQ delay is replaced with polling delay, `startup.c` changes.

That means project-specific policy is mixed with CPU/runtime boot. This makes
the template harder to reuse and makes future refactors riskier than necessary.

## Modularity Rule

Each file should have one reason to change.

Use this ownership split:

| File | Owns | Must Avoid |
| --- | --- | --- |
| `startup.c` | Reset-handler runtime boot only: copy `.data`, zero `.bss`, call project initialization, call `main()` | Delay implementation, Timer IRQ policy, board behavior, application logic, heap policy |
| `syscalls.c` | `_sbrk()` and other C library syscall bridges | Reset-handler boot, board init, delay policy |
| `project_config.h` | Project-local compile-time selections and constants | Function bodies, runtime sequencing |
| `project_init.h/.c` | Project bring-up sequence: clock, delay backend init, board init | Raw delay loops, low-level reset memory copy |
| `project_delay.h/.c` | Project delay facade and backend policy | Reset-handler boot, application loop behavior |
| `systick.h/.c` | SysTick peripheral access, tick counter, SysTick ISR | Timer delay policy, board init, project startup orchestration |
| `main.h/.c` | Application-specific behavior | Runtime boot, driver internals, delay backend internals |

## Target Project Structure

Target shape for reusable projects:

```text
Projects/Template
├── CMakeLists.txt
├── Inc
│   ├── main.h
│   ├── project_config.h
│   ├── project_delay.h
│   ├── project_init.h
│   └── systick.h
└── Src
    ├── main.c
    ├── project_delay.c
    ├── project_init.c
    ├── startup.c
    ├── syscalls.c
    └── systick.c
```

This structure keeps the template simple but gives each major concern a stable
home.

## Target Startup Responsibility

`startup.c` should become small and boring.

Target reset-handler shape:

```c
void Reset_Handler(void)
{
	_Startup_CopyData();
	_Startup_ZeroBss();

	Project_Init();

	main();
	Default_Handler();
}
```

Startup may keep private static helpers for copying `.data` and zeroing `.bss`.
It should not contain delay functions or Timer interrupt delay state.

Acceptable `startup.c` responsibilities:

- copy initialized data from Flash to RAM
- zero `.bss`
- call `Project_Init()`
- call `main()`
- fall into `Default_Handler()` if `main()` returns

Not acceptable in `startup.c`:

- direct Timer configuration such as `TIM_Config()`
- `TIM_DelayUs()`
- `TIM_DelayMs()`
- raw `TIMx->ARR` / `TIMx->CNT` / `TIMx->SR` access
- Timer IRQ delay completion state
- SysTick delay implementation
- LED or board initialization details
- `_sbrk()`

## Target Syscalls Responsibility

Move `_sbrk()` out of `startup.c`.

Target file:

```text
Projects/Template/Src/syscalls.c
```

`syscalls.c` should include the shared startup/linker declarations and own only
the C library bridge:

```c
void* _sbrk(intptr_t increment);
```

This isolates heap policy from reset-handler boot.

## Target Project Configuration

Move project-specific constants out of shared startup headers and generic files
where practical.

Target file:

```text
Projects/Template/Inc/project_config.h
```

Example content:

```c
#ifndef PROJECT_CONFIG_H_
#define PROJECT_CONFIG_H_

#include "stm32f1xx.h"

#define PROJECT_DELAY_TIMER					TIM4
#define PROJECT_LOOP_DELAY_MS				(1000UL)

#define PROJECT_USE_TIMER_DELAY				(1U)
#define PROJECT_USE_SYSTICK_DELAY			(0U)

#endif /* PROJECT_CONFIG_H_ */
```

The exact backend switch can evolve, but the important rule is that project
policy belongs in a project-owned config header, not inside `startup.c`.

## Target Project Initialization

Move project bring-up into:

```text
Projects/Template/Inc/project_init.h
Projects/Template/Src/project_init.c
```

Target ownership:

- configure system clock
- initialize delay backend
- initialize board peripherals used by the template
- keep startup policy out of the reset handler

Example:

```c
driver_status_t Project_Init(void)
{
	ASSERT_DRIVER_STATUS(RCC_Config_72MHz());
	ASSERT_DRIVER_STATUS(Project_DelayInit());

	OB_LED_Init();
	OB_LED_Reset();

	return DRIVER_STATUS_SUCCESS;
}
```

If `Project_Init()` returns `driver_status_t`, `Reset_Handler()` must decide how
to handle failure. In early template code, falling into `Default_Handler()` on
failure is acceptable:

```c
if (Project_Init() != DRIVER_STATUS_SUCCESS)
{
	Default_Handler();
}
```

## Target Delay Facade

Move delay policy into:

```text
Projects/Template/Inc/project_delay.h
Projects/Template/Src/project_delay.c
```

The application should call project-level delay APIs:

```c
Project_DelayUs(100U);
Project_DelayMs(1000UL);
```

The application should not care whether the backend is Timer, SysTick, DWT, or
another mechanism.

For the current Timer driver refactor, the preferred Timer delay backend is:

```c
driver_status_t Project_DelayInit(void)
{
	ASSERT_DRIVER_STATUS
	(
		RCC_APB1_ClockEnable(PROJECT_DELAY_TIMER_CLOCK_ENABLE_MASK)
	);
	return TIM_ConfigDelay1MHz(PROJECT_DELAY_TIMER);
}

driver_status_t Project_DelayUs(const uint16_t delayUs)
{
	return TIM_DelayUs(PROJECT_DELAY_TIMER, delayUs);
}

driver_status_t Project_DelayMs(const uint32_t delayMs)
{
	return TIM_DelayMs(PROJECT_DELAY_TIMER, delayMs);
}
```

This replaces the old template delay path that used:

- `TIM_1MHz_Load_Default()`
- old one-argument `TIM_Config()`
- `TIM_IRQ_Enable()`
- `delayCompleted`
- raw Timer register writes
- `DELAY_TIMER_IRQHandler()`

## Target SysTick Ownership

`systick.c` may remain project-specific, but it should be organized around the
SysTick peripheral only.

Good `systick.c` responsibilities:

- `SysTick_Config(...)`
- `SysTick_Enable()`
- `SysTick_Disable()`
- `SysTick_Get_Ticks()`
- `SysTick_Set_Ticks(...)`
- `SysTick_Handler()`
- raw SysTick register access

Avoid in `systick.c`:

- Timer delay backend selection
- Timer register access
- board LED initialization
- project startup orchestration

If SysTick is used as a delay backend, keep the backend selection in
`project_delay.c`. `systick.c` can provide lower-level tick primitives, while
`project_delay.c` decides how to expose project delay APIs.

## Target Main Ownership

`main.c` should express application behavior only.

Example:

```c
int main(void)
{
	while (1)
	{
		OB_LED_Toggle();
		(void) Project_DelayMs(PROJECT_LOOP_DELAY_MS);
	}
}
```

`main.c` should not configure clocks, configure the delay backend, or know the
Timer setup sequence unless the project is explicitly a Timer-driver teaching
example.

## Delay Backend Policy

There are two different concerns that should not be mixed:

1. SysTick as a system tick source.
2. Delay implementation backend.

SysTick may be configured for ticks even if delays use Timer. Timer may be
configured for delays even if SysTick owns the system tick.

The delay backend should be selected through `project_delay.c`, not scattered
through `startup.c`, `systick.c`, and `main.c`.

Current preferred Timer delay flow:

```text
Project_Init()
  -> RCC_Config_72MHz()
  -> Project_DelayInit()
       -> RCC_APB1_ClockEnable(PROJECT_DELAY_TIMER_CLOCK_ENABLE_MASK)
       -> TIM_ConfigDelay1MHz(PROJECT_DELAY_TIMER)
  -> OB_LED_Init()
  -> OB_LED_Reset()

main()
  -> Project_DelayMs(...)
       -> TIM_DelayMs(PROJECT_DELAY_TIMER, ...)
```

## Migration Plan

Use small, verifiable steps.

### Step 1: Add Project Config

Add:

```text
Projects/Template/Inc/project_config.h
```

Move constants such as loop delay and delay Timer selection into this file:

```c
#define PROJECT_LOOP_DELAY_MS				(1000UL)
#define PROJECT_DELAY_TIMER					TIM4
#define PROJECT_DELAY_TIMER_CLOCK_ENABLE_MASK	RCC_APB1ENR_TIM4EN
```

Keep old macros temporarily if other files still depend on them.

### Step 2: Add Project Delay Facade

Add:

```text
Projects/Template/Inc/project_delay.h
Projects/Template/Src/project_delay.c
```

Implement the Timer backend using the current Timer driver APIs:

```c
RCC_APB1_ClockEnable(PROJECT_DELAY_TIMER_CLOCK_ENABLE_MASK);
TIM_ConfigDelay1MHz(PROJECT_DELAY_TIMER);
TIM_DelayUs(PROJECT_DELAY_TIMER, delayUs);
TIM_DelayMs(PROJECT_DELAY_TIMER, delayMs);
```

Do not use old IRQ-based delay code.

### Step 3: Add Project Init

Add:

```text
Projects/Template/Inc/project_init.h
Projects/Template/Src/project_init.c
```

Move:

- `RCC_Config_72MHz()`
- delay backend initialization
- board LED initialization

out of `startup.c` and into `Project_Init()`.

### Step 4: Move `_sbrk()`

Add:

```text
Projects/Template/Src/syscalls.c
```

Move `_sbrk()` and `heap_ptr` out of `startup.c`.

### Step 5: Shrink Startup

After steps 1-4, `startup.c` should contain:

- includes
- private reset-memory helpers
- `Reset_Handler()`

It should no longer contain:

- `_sbrk()`
- Timer configuration object
- Timer IRQ delay state
- `delay_us()`
- `delay_ms()`
- `DELAY_TIMER_IRQHandler()`
- board initialization details

### Step 6: Clean SysTick

Keep `systick.c` focused on SysTick only.

If the template no longer uses SysTick delay functions directly, remove
`delay_us()` / `delay_ms()` from `systick.c` or keep them behind a clearly named
SysTick-specific API. Do not let generic `delay_ms()` hide which backend is
being used.

Prefer project-facing names:

```c
Project_DelayUs(...)
Project_DelayMs(...)
```

### Step 7: Apply To Example Projects

Once `Projects/Template` is clean, migrate active examples such as:

```text
Projects/Timer/04_Timer_Poll
Projects/Timer/05_Timer_IRQ
Projects/GPIO/*
Projects/USART/*
Projects/DMA/*
Projects/PWM/*
```

Project-specific examples may intentionally expose driver details, but the
startup/runtime split should remain clean.

## Current Timer Driver Alignment

The current Timer driver provides the root configuration and delay operations
needed by the modular project delay facade:

```c
driver_status_t TIM_Config(TIM_TypeDef* const TIMx, const tim_config_t* const pConfig);
driver_status_t TIM_ConfigDelay1MHz(TIM_TypeDef* const TIMx);
driver_status_t TIM_DelayUs(TIM_TypeDef* const TIMx, const uint16_t delayUs);
driver_status_t TIM_DelayMs(TIM_TypeDef* const TIMx, const uint32_t delayMs);
```

Important constraints:

- Projects own explicit prescaler/timebase data; no frequency-targeting Timer configuration function exists.
- Applications explicitly enable the selected Timer clock through the RCC
  driver before Timer configuration; Timer APIs validate but never change the
  clock gate.
- `TIM_DelayUs()` accepts `1U..0xFFFFU`.
- `TIM_DelayUs()` is a minimum blocking delay, not a cycle-exact delay.
- `TIM_DelayMs()` composes repeated `TIM_DelayUs(TIMx, 1000U)` chunks.
- Delay helpers assume the Timer clock gate is enabled and the Timer was
  configured through `TIM_Config()` with a 1 MHz programmed counter tick.

## Current Example State

The Timer polling and IRQ examples now use the current public API and explicitly
enable their Timer clocks through RCC before configuration. Do not build new
template structure around old Timer APIs. Migrate any remaining project code
to the new Timer API as part of the modularization.

## Anti-Patterns To Remove

Avoid these patterns in the final template:

```c
// startup.c
TIM_1MHz_Load_Default(...);
TIM_IRQ_Enable(...);
void delay_us(...);
void delay_ms(...);
void DELAY_TIMER_IRQHandler(void);
```

```c
// application code
DELAY_TIMER->ARR = ...;
DELAY_TIMER->CNT = ...;
DELAY_TIMER->SR.REG &= ...;
```

```c
// systick.c
TIM_Config(...);
TIM_DelayMs(...);
```

These mix ownership and make future changes spread across unrelated files.

## Verification Checklist

After modularization:

- `startup.c` contains no Timer delay logic.
- `startup.c` contains no `_sbrk()`.
- `startup.c` calls `Project_Init()` once before `main()`.
- `project_init.c` owns clock, delay, and board bring-up order.
- `project_delay.c` owns the selected delay backend.
- `systick.c` contains only SysTick primitives and the SysTick ISR.
- `main.c` uses project-facing APIs, not startup internals.
- No project code calls removed Timer APIs such as `TIM_1MHz_Load_Default()`.
- The project builds through its normal CMake flow.

Recommended build check:

```bash
cd Projects/Template
cmake -S . -B Build
cmake --build Build
```

For Timer-delay validation on hardware, toggle a GPIO around:

```c
Project_DelayUs(1U);
Project_DelayUs(100U);
Project_DelayUs(65535U);
Project_DelayMs(1UL);
Project_DelayMs(100UL);
```

Measure with a scope or logic analyzer and treat the result as a minimum delay
with small positive software overhead.

## Final Target Mental Model

```text
startup.c        boots the CPU/runtime
syscalls.c       bridges libc heap calls
project_config.h declares project constants
project_init.c   initializes clocks, board, and project services
project_delay.c  owns delay backend policy
systick.c        owns SysTick hardware behavior
main.c           owns application behavior
```

If a future change does not naturally fit one of those buckets, define the
bucket first instead of adding more logic to `startup.c`.
