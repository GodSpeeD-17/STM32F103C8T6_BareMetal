# Cortex-M3 SysTick Implementation Guide {#SYSTICK_Peripheral_Guide}

SysTick is the Cortex-M3 Core's dedicated 24-bit down-counter. This guide
defines the hardware model supported by this repository and the boundary
between reusable Driver state and application-owned elapsed time.

## Theory with Register Mapping Bridge

### Purpose and terminology

SysTick produces a periodic counter wrap without reserving an STM32
general-purpose Timer. Four terms remain distinct:

- **reload value**: the value stored in `LOAD`; a period contains
  `reload value + 1` input-clock cycles,
- **current value**: the live down-counter exposed by `VAL`,
- **exception request**: the Core exception requested at counter wrap when
  `TICKINT` is enabled,
- **software tick**: an application-defined quantity updated by its handler;
  this is not SysTick hardware state.

The counter loads `LOAD`, counts toward zero, asserts `COUNTFLAG` at wrap, and
reloads automatically while enabled. If `TICKINT` is enabled, the same wrap
requests the SysTick exception. SysTick is a Core exception, so it does not
have an STM32 peripheral clock gate or a separate NVIC enable bit.

### Hardware state and flow

The admitted state domains are independent:

1. `CLKSOURCE` and `LOAD` define root configuration.
2. `TICKINT` controls exception-request generation.
3. `ENABLE` controls counter operation.
4. `VAL` contains the current countdown position but acts as a clear port on
   writes.

A deterministic periodic service therefore follows this order:

1. disable operation and exception requests,
2. program clock source and reload value,
3. clear the current value,
4. enable the exception source if required,
5. enable counter operation.

Application work does not belong in the exception. The handler should publish
the smallest required state change, while main context observes that state and
performs scheduling, callbacks, I/O, or other processing.

### Register mapping

The SysTick register bank begins at `0xE000E010`. Every register occupies one
32-bit word, even where only 24 bits are implemented.

| Register | Address / offset | Access and implemented range | Significance and special behavior |
| --- | --- | --- | --- |
| `CTRL` | `0xE000E010` / `0x00` | Mixed R/W and read-only status | `ENABLE[0]` starts counting, `TICKINT[1]` enables the exception request, `CLKSOURCE[2]` selects processor clock or processor clock divided by eight, and `COUNTFLAG[16]` reports a wrap. Reading `CTRL` clears `COUNTFLAG`. |
| `LOAD` | `0xE000E014` / `0x04` | R/W, `RELOAD[23:0]` | Stores the next reload value. Values above `0x00FFFFFF` are not implemented. A stored value `N` represents `N + 1` input-clock cycles. |
| `VAL` | `0xE000E018` / `0x08` | Read current value; write-to-clear action | A read returns `CURRENT[23:0]`. Any write clears the current counter and `COUNTFLAG`; the written payload is not stored. |
| `CALIB` | `0xE000E01C` / `0x0C` | Read-only | `TENMS[23:0]` exposes a ten-millisecond calibration value when supplied, `SKEW[30]` marks inexact calibration, and `NOREF[31]` reports the absence of an external reference clock. |

`CTRL`, `LOAD`, and `VAL` interact directly: configuration determines the next
period, clearing `VAL` establishes its start, and `ENABLE` admits counting.
`TICKINT` changes only exception delivery; it does not start the counter.
`CALIB` is observational and does not alter operation.

### Timing and range

For input frequency `F` and exact requested tick frequency `T`:

```text
period cycles = F / T
reload value  = period cycles - 1
```

The division must be exact when each interrupt represents one fixed software
unit. The period-cycle range is `1..0x01000000`; therefore the reload-value
range is `0..0x00FFFFFF`. At a 72 MHz processor clock and a 1 kHz application
tick, the reload value is `71999`.

`COUNTFLAG` is not a durable event queue. Multiple wraps can collapse into one
observed flag, and ordinary `CTRL` reads clear it. Interrupt-backed elapsed
time must therefore use application-owned software state rather than polling
`COUNTFLAG` as a long-duration accumulator.

## Implementation with Theory Bridge

### Layer ownership

The implemented dependency chain points toward hardware only:

```text
Application handler/service
└── SysTick Driver
    └── SysTick LL
        └── Core SysTick register layer
```

- `stm32f1xx_systick.h` owns raw field macros and `SysTick_TypeDef`.
- `systick_ll.h` owns one generic full-width `.REG` read/write primitive pair;
  named register accessors only select and forward register pointers.
- `systick.c` owns public validation, field preservation, and transaction
  sequencing.
- a consuming application owns `SysTick_Handler()` and any software tick,
  scheduler flag, callback, or time unit.

The Driver never includes an application header. The application includes only
the public Driver header from its service implementation, preventing an upward
or circular dependency.

### Public contract mapping

| Hardware theory | Public operation | LL/Core path | Preservation rule |
| --- | --- | --- | --- |
| Complete reset state | `SysTick_DeConfig()` | full writes to `CTRL`, `LOAD`, then the `VAL` clear action | Resets operation, IRQ source, configuration, and current hardware state; cannot reset application data |
| Root configuration | `SysTick_GetConfig()` / `SysTick_SetConfig()` | `LL_SysTick_Read/WriteCTRL`, `LL_SysTick_Read/WriteLOAD` | Set requires stopped operation and preserves `TICKINT`; current value is unchanged |
| Exception source | `SysTick_GetIRQState()` / `SysTick_SetIRQState()` | staged `CTRL.TICKINT` update | Preserves `ENABLE` and `CLKSOURCE` |
| Counter operation | `SysTick_GetOperationState()` / `SysTick_SetOperationState()` | staged `CTRL.ENABLE` update | Preserves `TICKINT` and `CLKSOURCE` |
| Current-value origin | `SysTick_ResetCurrentValue()` | `LL_SysTick_ResetVAL()` | Models the asymmetric write-to-clear action; no misleading arbitrary setter exists |

Root configuration uses raw register-semantic values. It does not accept an
arbitrary frequency request. The application time service converts its known
clock and fixed time-unit policy into a reload value before calling the Driver.
This keeps reusable hardware semantics below and application units above.

### Documented no-Codec decision

SysTick has no Codec layer in the supported scope. The public clock-source
selectors are already positioned `CLKSOURCE` field images, and the reload value
is already the exact `LOAD.RELOAD` payload. The only transformations are mask,
clear, and set operations over one-bit state fields. A Codec would introduce a
forwarding layer without translating semantic vocabulary, packing multiple
instances, or staging a reusable peripheral representation.

If future scope introduces abstract frequency configuration, calibration
interpretation, or a richer selector vocabulary, that new transformation must
be audited before deciding whether a Codec becomes justified.

### Application-owned interrupt path

The Template's `app_time.c` owns both `appTickMs` and the strong
`SysTick_Handler()` definition. Startup continues to provide a weak fallback in
the vector table, so disabling the application timebase leaves a safe default
handler without linking the SysTick Driver.

The enabled handler contains one unsigned 32-bit increment. Cortex-M3 performs
aligned 32-bit application reads atomically, so `App_TimeGetTickMs()` needs no
critical section. The object remains `volatile` because hardware exception and
main context observe it asynchronously. Unsigned subtraction implements
wrap-safe elapsed-time measurement across one counter rollover.

No callback, Driver call, delay loop, peripheral transaction, or scheduler
walk occurs inside the handler. Main context consumes the published tick and
performs all work.

### Ordering, concurrency, and side effects

All public configuration fields are validated before the first hardware
mutation. `SysTick_SetConfig()` rejects a running counter with
`DRIVER_STATUS_ERROR_BUSY`. Root configuration preserves IRQ-source state;
IRQ-source control preserves configuration and operation; operation control
preserves configuration and IRQ-source state.

Every `CTRL` read clears `COUNTFLAG`, including state getters and the read side
of a staged update. The Driver deliberately exposes no `COUNTFLAG` polling API,
so this destructive read cannot invalidate another supported Driver contract.
Applications requiring wrap accounting use their handler-owned state.

The application owns lifecycle ordering. `SysTick_SetConfig()` never calls
`SysTick_DeConfig()`. The Template explicitly deconfigures, configures, clears
its software and hardware origins, enables the IRQ source, and finally enables
operation.

### Deliberately omitted interfaces

- No Driver-owned `SysTick_Handler()` or software tick exists because time unit
  and interrupt reaction are application policy.
- No arbitrary frequency-setting API exists because callers must provide
  register-semantic configuration.
- No arbitrary `VAL` setter exists because any write clears the register.
- No `CALIB` mutation exists because the register is read-only.
- No NVIC API is called because SysTick exception delivery has no independent
  NVIC enable transaction.
