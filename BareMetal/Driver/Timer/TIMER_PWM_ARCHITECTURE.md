# STM32F103C8T6 Timer PWM Architecture {#TIM_PWM_Peripheral_Guide}

## Status and scope

This page records the approved base architecture for pulse-width modulation
through the general-purpose `TIM2`, `TIM3`, and `TIM4` peripherals on the
STM32F103C8T6.

Timer PWM is a Timer-owned output-channel feature. It is not a separate
register-owning peripheral and it is not a peer driver that owns the Timer
timebase, GPIO configuration, RCC clocks, interrupt delivery, or board routing.

The base implementation is intentionally narrow:

- Timer base configuration is completed before PWM configuration.
- PWM configuration is completed while the Timer counter is disabled.
- The application enables the Timer only after every required PWM channel is
  configured and assigned a duty cycle.
- GPIO and AFIO configuration remain entirely application-owned.
- PWM frequency remains a Timer timebase property.
- PWM mode/polarity configuration and duty configuration are separate public
  operations.
- No PWM configuration structure, endpoint object, handle, heap allocation, or
  shared-frequency registry is introduced.

This guide must be read with the normative planning and safety rules in
`BareMetal/Driver/DRIVER_STACK_TOP_DOWN_AUDIT.md`. The existing
`BareMetal/Driver/Timer/TIMER_ARCHITECTURE.md` remains the broader Timer stack
reference. Those planning documents are deliberately excluded from generated
Doxygen output, so their repository paths are recorded without Doxygen links.

## Decision register

The following decisions are fixed for the first implementation:

| Topic | Decision |
| --- | --- |
| Repository placement | Add `Inc/timer_pwm.h` and `Src/timer_pwm.c` directly to the existing `Timer` module; do not create a new PWM folder or module. |
| Public identity | Pass `TIMx` and `tim_channel_t` explicitly. Do not hide them in an endpoint enum, group enum, handle, or configuration object. |
| Timer lifecycle | The application configures the Timer first, configures PWM second, and enables the Timer last. |
| Frequency ownership | Timer timebase APIs own PSC, ARR, counter mode, and resulting PWM frequency. Timer PWM does not accept or set frequency. |
| GPIO ownership | The application owns GPIO mode, output speed, alternate-function selection, AFIO remap, and pin lifecycle. |
| PWM configuration | `TIM_ConfigPWM()` accepts mode and polarity as independent scalar parameters. |
| Duty configuration | `TIM_SetPWMDutyCycle()` is a separate operation using the already-programmed ARR. |
| Output state | Timer PWM controls selected `CCxE` channel-output bits; `TIM_SetOperationState()` independently controls `CR1.CEN`. |
| Layering | `timer_pwm.c` is a Timer Driver source unit and follows the existing Timer Driver -> Codec -> LL stack. |
| Lower layers | Reuse and extend `timer_codec.*` and `timer_ll.h`; do not create PWM-specific Codec or LL files. |
| Memory | Use no dynamic allocation, opaque handle, caller-owned context, or static ownership registry. |
| Initial routing | Support Timer channel programming independently of physical pin routing; the application is responsible for selecting a valid pin. |

## Required application sequence

The required first-use sequence is:

```text
Application enables required RCC clock gates
        ↓
Application configures GPIO/AFIO for the selected physical output pin
        ↓
Application configures TIMx counter and timebase through TIM_Config()
        ↓
Application configures each PWM channel through TIM_ConfigPWM()
        ↓
Application assigns each channel duty through TIM_SetPWMDutyCycle()
        ↓
Application enables the required channel output(s)
        ↓
Application enables TIMx through TIM_SetOperationState()
```

The architectural precondition is therefore:

```text
TIM_Config() succeeds
        before
TIM_ConfigPWM() / TIM_SetPWMDutyCycle()
        before
TIM_SetOperationState(TIMx, DRIVER_STATUS_ON)
```

Timer PWM never calls `TIM_Config()` or `TIM_SetOperationState()` on behalf of
the application. This keeps timebase ownership, channel ownership, and counter
operation visible at the call site.

## Part I — Theory with Register Mapping Bridge

### PWM period and frequency

In edge-aligned up-counting mode, the Timer counter advances from zero through
the programmed auto-reload value. Both endpoints are included, so one PWM
period contains `ARR + 1` Timer ticks.

```text
Timer tick frequency = Timer input clock / (PSC + 1)

Period ticks P = ARR + 1

PWM frequency = Timer input clock / ((PSC + 1) × (ARR + 1))
```

`PSC`, `ARR`, counter direction, alignment, and the resulting frequency are
Timer timebase concerns. The PWM channel layer reads the already-programmed
period but does not choose or mutate the frequency.

The application must configure an edge-aligned, up-counting, continuous Timer
timebase suitable for PWM before calling `TIM_ConfigPWM()`.

### Compare value and active time

Each output channel has one capture/compare register, `CCR1` through `CCR4`.
The compare value defines the transition point within the programmed period.

The public duty representation is permille:

```text
0       = 0.0%
1       = 0.1%
500     = 50.0%
1000    = 100.0%
```

For period ticks `P`, active ticks are calculated with round-half-up behavior:

```text
active ticks A = round(duty permille × P / 1000)
```

The implementation uses 64-bit intermediates for the multiplication and
rounding operation even though the public duty value and hardware registers
are narrower.

### PWM mode 1

For edge-aligned up-counting PWM mode 1, the internal output reference is
active while `CNT < CCR` and inactive for the remainder of the period.

```text
PWM mode 1: CCR = A
```

Important boundaries are:

```text
0% duty:   CCR = 0
100% duty: CCR = P
```

### PWM mode 2

PWM mode 2 inverts the placement of the active interval relative to the
compare point. With duty defined as time spent at the selected active polarity:

```text
PWM mode 2: CCR = P - A
```

Important boundaries are:

```text
0% duty:   CCR = P
100% duty: CCR = 0
```

PWM mode therefore controls where the active interval appears within the
period. It does not change the public meaning of duty.

### Exact 0% and 100%

The Timer has 16-bit ARR and CCR registers. Exact endpoint behavior in both
PWM modes requires the value `P = ARR + 1` to fit in CCR. Timer PWM therefore
admits this base-period range:

```text
ARR:          1..65534
Period ticks: 2..65535
CCR:          0..65535
```

`ARR=0` is not a usable PWM period. `ARR=65535` produces 65536 period ticks,
which cannot be written to a 16-bit CCR for the mode-dependent exact endpoint.
`TIM_ConfigPWM()` rejects either boundary instead of silently approximating or
clamping it.

### Polarity

Polarity is applied after the internal output-reference signal:

- Active-high polarity makes the active interval electrically high.
- Active-low polarity makes the active interval electrically low.

Duty always means the fraction of the period spent at the selected active
polarity. Changing polarity changes the electrical level identified as active;
it does not change the duty calculation.

### Channel output state and counter state

Two independent enable decisions are involved:

- `TIMx_CCER.CCxE` connects the selected channel output to the Timer output
  path.
- `TIMx_CR1.CEN` starts or stops the shared Timer counter.

Timer PWM owns the public channel-output operation, but the application retains
explicit Timer-counter control. Enabling a PWM channel does not start the
Timer, and disabling a PWM channel does not stop the Timer.

This independence permits several configured channels to share one running
counter while the application changes individual channel-output states.

### Preload and update events

CCR preload is mandatory for admitted PWM channels. With preload enabled, a
CCR write changes the programmed preload value while the active compare value
is transferred at an update event.

This prevents an active-period duty update from changing the compare boundary
partway through that same period.

Two cases are distinguished:

1. **Timer stopped:** Timer PWM generates a controlled, non-requesting update
   event so the new CCR value is active before the application starts the
   counter.
2. **Timer running:** Timer PWM writes the CCR preload and allows the next
   natural update event to activate it. Successful return means the programmed
   preload was updated; activation occurs at the next period boundary.

The stopped-Timer update transaction must preserve the caller's update-source
and update-disable policy, avoid an IRQ/DMA request, preserve unrelated status
flags, and leave the counter at the PWM-admitted initial value of zero.

### Shared Timer timebase

All four channels of one Timer share:

- `PSC`;
- `ARR`;
- `CNT`;
- counter direction and alignment;
- update events;
- `CR1.CEN`.

Timer PWM does not create a second group abstraction or frequency registry.
`TIMx` itself is the shared group, and its timebase is already configured by
the Timer Driver before any PWM channel is configured.

If the application changes PSC or ARR later, it must stop the Timer and reapply
the duty of every configured PWM channel before enabling the Timer again.
Timer PWM stores no requested-duty registry from which to repair channels
automatically.

### Register mapping bridge

PWM has no independent register block. The relevant theory maps into
Timer-owned registers as follows:

| Concept | Owning register/field |
| --- | --- |
| Counter operation | `TIMx_CR1.CEN` |
| Edge/center alignment | `TIMx_CR1.CMS` |
| Count direction | `TIMx_CR1.DIR` |
| Auto-reload preload | `TIMx_CR1.ARPE` |
| Update-event policy | `TIMx_CR1.UDIS`, `TIMx_CR1.URS` |
| Timer tick division | `TIMx_PSC` |
| Period | `TIMx_ARR` |
| Current phase | `TIMx_CNT` |
| Software preload transfer | `TIMx_EGR.UG` |
| Channel output selection | `TIMx_CCMR1/2.CCxS` |
| PWM mode | `TIMx_CCMR1/2.OCxM` |
| CCR preload | `TIMx_CCMR1/2.OCxPE` |
| Fast/clear behavior | `TIMx_CCMR1/2.OCxFE`, `TIMx_CCMR1/2.OCxCE` |
| Channel output enable | `TIMx_CCER.CCxE` |
| Channel polarity | `TIMx_CCER.CCxP` |
| Compare boundary | `TIMx_CCR1` through `TIMx_CCR4` |

GPIO `CRL`/`CRH` and AFIO `MAPR` determine whether a Timer signal reaches a
physical pin, but those registers are outside Timer PWM ownership in this base
architecture.

The hardware behavior above is grounded in the general-purpose Timer chapters
of the
[`STM32F103C Reference Manual`](../../../Reference_Docs/STM32F103C_Reference_Manual.pdf)
and the package/pin information in the
[`STM32F103C8T6 Datasheet`](../../../Reference_Docs/STM32F103C8T6_Datasheet.pdf).

## Part II — Implementation with Theory Bridge

### Module classification

Timer PWM is implemented as a cohesive public subdomain of the existing Timer
Driver:

```text
Application
        ↓
timer_pwm.h public Timer PWM API
        ↓
timer_pwm.c Timer Driver orchestration
        ↓
timer_codec.h / timer_codec.c image extraction and staging
        ↓
timer_ll.h named Timer register access
        ↓
STM32F103 Timer registers
```

This classification is why the source and header live directly in the Timer
module. `timer_pwm.c` may use the existing Timer Codec and LL interfaces in the
same way as `timer.c`, but it must not:

- dereference a `TIM_TypeDef` register field directly;
- encode raw CCMR/CCER fields in the Driver layer;
- create `timer_pwm_codec.*` or `timer_pwm_ll.*`;
- call GPIO, AFIO, NVIC, or project code;
- mutate RCC clock gates;
- allocate memory;
- call public Timer APIs as a substitute for owning its complete transaction.

Public Timer PWM APIs own validation, register snapshots, Codec staging,
ordered dirty writes, update sequencing, and detailed status propagation.

### Planned file layout

Only these new files belong to the base implementation:

```text
BareMetal/Driver/Timer/Inc/timer_pwm.h
BareMetal/Driver/Timer/Src/timer_pwm.c
BareMetal/Driver/Timer/TIMER_PWM_ARCHITECTURE.md
```

Existing Timer files receive only domain-appropriate extensions:

- `timer_data_types.h` owns `tim_pwm_duty_cycle_t`.
- `timer_defines.h` owns duty limits and PWM-specific validation helpers.
- `timer_codec.h/.c` own any missing CCR and coherent output-field
  Extract/Stage operations.
- `timer_ll.h` supplies named CCMR1/2, CCER, CCR1-4, CR1, EGR, and SR access;
  additional LL APIs are added only when a genuinely missing raw operation is
  proven.
- `timer.h/.c` continue to own the general Timer timebase and counter APIs.

There is no `timer_pwm_config.h` because the agreed public API has no PWM
configuration structure.

### Public scalar type and constants

The public duty type is a Timer-owned scalar alias:

```c
typedef uint16_t tim_pwm_duty_cycle_t;
```

The public limits are:

```c
#define TIM_PWM_DUTY_CYCLE_MIN		((tim_pwm_duty_cycle_t) 0U)
#define TIM_PWM_DUTY_CYCLE_MAX		((tim_pwm_duty_cycle_t) 1000U)
```

No PWM-specific frequency, GPIO, route, endpoint, group, ownership-token, or
handle type is introduced.

### Public API

The admitted base API is:

```c
driver_status_t TIM_ConfigPWM
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channel,
	const tim_channel_mode_t mode,
	const tim_channel_polarity_t polarity
);

driver_status_t TIM_GetPWMConfig
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channel,
	tim_channel_mode_t* const pMode,
	tim_channel_polarity_t* const pPolarity
);

driver_status_t TIM_DeConfigPWM
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channel
);

driver_status_t TIM_SetPWMDutyCycle
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channel,
	const tim_pwm_duty_cycle_t dutyCycle
);

driver_status_t TIM_GetPWMDutyCycle
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channel,
	tim_pwm_duty_cycle_t* const pDutyCycle
);

driver_status_t TIM_SetPWMOutputState
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channelMask,
	const driver_status_t outputState
);

driver_status_t TIM_GetPWMOutputState
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channel
);
```

Identity is never embedded in configuration state:

- `TIMx` selects the Timer instance.
- `channel` selects exactly one Timer channel for configuration and getters.
- `channelMask` selects one or more already-configured PWM channels for one
  coherent output-state update.

### Why there is no PWM configuration structure

Mode and polarity form the narrow channel-mode configuration transaction and
are passed directly to `TIM_ConfigPWM()`. Duty has a distinct lifecycle and
preload/update contract, so it is configured separately.

Frequency and GPIO output speed are deliberately absent:

- Frequency belongs to the previously configured Timer timebase.
- GPIO output speed belongs to the application-owned GPIO configuration.

A structure containing those values would cross ownership boundaries and
allow independent fields to imply an orchestration policy that Timer PWM does
not own.

### `TIM_ConfigPWM()` contract

`TIM_ConfigPWM()` configures one Timer channel for PWM but never enables the
channel or starts the counter.

Required preconditions:

- `TIMx` is `TIM2`, `TIM3`, or `TIM4`.
- The application enabled the corresponding APB1 clock gate.
- The application already completed Timer base configuration.
- `TIMx_CR1.CEN` is clear.
- The selected `CCxE` bit is clear.
- The Timer is edge-aligned and up-counting.
- One-pulse mode is disabled.
- ARR preload and update-event operation satisfy the admitted PWM contract.
- `CNT` is zero.
- ARR is in `1..65534`.
- `channel` contains exactly one of `TIMx_CHANNEL_1` through
  `TIMx_CHANNEL_4`.
- `mode` is PWM mode 1 or PWM mode 2.
- `polarity` is active-high or active-low.

The transaction:

1. Validates every argument and all required Timer state.
2. Reads each required CCMR, CCER, CCR, CR1, ARR, CNT, and status image once.
3. Stages `CCxS` as output, the requested PWM mode, CCR preload enabled,
   output-compare fast disabled, and output-compare clear disabled.
4. Stages the requested polarity while keeping `CCxE` disabled.
5. Derives the mode-correct exact 0% CCR value from the programmed period.
6. Stages every prospective register image before the first hardware write.
7. Writes only dirty register images in the documented safe order.
8. Performs the controlled stopped-Timer preload transfer when required.
9. Returns with the channel disabled and Timer counter stopped.

An error before the first write leaves Timer state unchanged. After the first
write, no further fallible validation or Codec operation is permitted.

### `TIM_GetPWMConfig()` contract

The getter verifies that the selected channel has the complete admitted PWM
shape:

- `CCxS` selects output compare.
- `OCxM` selects PWM mode 1 or PWM mode 2.
- `OCxPE` is enabled.
- `OCxFE` and `OCxCE` are disabled.
- Polarity is decodable.

Both output pointers are required. The function decodes into local variables
and writes `pMode` and `pPolarity` only after the complete operation succeeds.
Caller output storage remains unchanged on failure.

### `TIM_SetPWMDutyCycle()` contract

The setter accepts one configured PWM channel and a duty value in
`0..1000`. It never changes PWM mode, polarity, PSC, ARR, GPIO state, channel
enable state, or counter enable state.

The transaction:

1. Validates `TIMx`, the single channel, and duty.
2. Reads and validates the channel's admitted PWM configuration.
3. Reads ARR and derives `P = ARR + 1`.
4. Rejects an invalid period instead of clamping it.
5. Calculates active ticks and the mode-dependent CCR with 64-bit
   intermediates and round-half-up behavior.
6. Selects the corresponding CCR register.
7. Writes the CCR preload only after all fallible work succeeds.
8. If the Timer is stopped, performs a controlled update transfer before
   returning.
9. If the Timer is running, leaves activation to the next natural update
   event.

The running-Timer return contract describes programmed preload state, not proof
that the active CCR has already transferred.

### `TIM_GetPWMDutyCycle()` contract

The getter reads the programmed ARR and selected CCR, validates the PWM mode,
reconstructs active ticks according to PWM mode 1 or PWM mode 2, and reports
the achieved duty rounded to the nearest permille value.

No requested-duty value is retained. The getter reports what the programmed
Timer state represents. Its output remains unchanged on failure.

If the Timer is running, the result describes the readable programmed CCR
preload and may differ temporarily from the active compare value until the next
update event.

### PWM output-state contracts

`TIM_SetPWMOutputState()` changes only `CCxE` for the selected channel mask.
It accepts `DRIVER_STATUS_OFF` and `DRIVER_STATUS_ON` and does not change
`CR1.CEN`.

Before enabling a channel, the function verifies that every selected channel
has the admitted PWM configuration. It stages one final CCER image and writes
CCER at most once.

For initial startup, the application should enable every required PWM channel
while the Timer is stopped and then call:

```c
TIM_SetOperationState(TIMx, DRIVER_STATUS_ON);
```

Changing `CCxE` while the Timer is already running takes effect immediately.
An enabled channel may therefore join an existing period partway through that
period. Applications requiring aligned first pulses configure and enable all
channels before starting the shared counter.

`TIM_GetPWMOutputState()` accepts exactly one channel and returns
`DRIVER_STATUS_OFF`, `DRIVER_STATUS_ON`, or a detailed error status directly.

### `TIM_DeConfigPWM()` contract

Deconfiguration requires both the Timer counter and selected channel output to
be disabled. It resets only the selected channel's owned fields:

- output-compare mode and selection;
- preload, fast, and clear selectors;
- polarity;
- channel enable;
- selected CCR value.

It preserves all other channels, the Timer timebase, IRQ/DMA state, RCC clock
gate, NVIC state, GPIO configuration, and AFIO routing.

### Status behavior

All fallible public APIs return `driver_status_t`.

| Status | Meaning in Timer PWM |
| --- | --- |
| `DRIVER_STATUS_SUCCESS` | Configuration, duty, state, or deconfiguration operation completed. |
| `DRIVER_STATUS_OFF` | Direct output-state getter reports the selected channel disabled. |
| `DRIVER_STATUS_ON` | Direct output-state getter reports the selected channel enabled. |
| `DRIVER_STATUS_ERROR_NULL_PTR` | `TIMx` or required output storage is `NULL`. |
| `DRIVER_STATUS_ERROR_INVALID_ARG` | Instance, channel, mask, mode, polarity, duty, or admitted ARR range is invalid. |
| `DRIVER_STATUS_ERROR_STATE` | Clock is disabled, Timer base state is incompatible, or the channel does not have the admitted PWM shape. |
| `DRIVER_STATUS_ERROR_BUSY` | A configuration/deconfiguration operation requires a stopped counter or disabled channel. |
| `DRIVER_STATUS_ERROR_FAIL` | A post-mutation safety cleanup could not establish the documented state. |

Peer and lower-layer statuses are propagated rather than collapsed into a
Boolean result.

### GPIO and AFIO application ownership

The first implementation deliberately performs no pin orchestration. Timer PWM
does not know which package pin carries a selected channel and does not verify
the current remap state.

The application must:

- enable the required GPIO and AFIO clocks;
- select a package-bonded Timer channel pin;
- configure alternate-function push-pull mode and output speed;
- configure or preserve the intended AFIO remap state;
- resolve any SWJ/debug-pin conflict;
- retain the GPIO configuration while PWM output is required;
- restore or repurpose the GPIO after Timer PWM deconfiguration.

For the initial `Projects/PWM/06_PWM_Poll` reference, the application will use
the default non-remapped routes:

```text
TIM2 CH3 -> PA2
TIM2 CH4 -> PA3
```

GPIO ownership may be revisited only after the base Timer PWM implementation
is functional and validated. Any future ownership change must update this
guide before changing source behavior.

### Shared-channel behavior without a registry

Timer PWM keeps no hidden group state:

- Multiple channels share whatever PSC/ARR the application programmed.
- Configuring a channel does not claim the Timer or alter another channel.
- Duty setters derive their result from the current readable ARR.
- Channel output state never starts or stops the shared counter.
- The application decides which channels are enabled before starting TIMx.
- The application stops TIMx before changing the shared timebase.
- The application reapplies every duty value after changing ARR.

This model makes the shared hardware relationship explicit instead of
duplicating it in software state.

### Documentation boundary

`TIMER_PWM_ARCHITECTURE.md` is the canonical theory, ownership, sequencing, and
implementation guide for Timer PWM.

Source Doxygen will document local callable contracts and link to
@ref TIM_PWM_Peripheral_Guide rather than duplicating this complete theory.
`DRIVER_DOCUMENTATION.md` is updated only after the implementation and guide
have been reviewed together.

## Validation plan

### Host and Codec validation

Tests must cover:

- channel 1/2 selection through CCMR1;
- channel 3/4 selection through CCMR2;
- CCxS output selection;
- PWM1/PWM2 mode staging and extraction;
- mandatory preload and disabled fast/clear fields;
- all four CCER enable and polarity lanes;
- CCR1 through CCR4 selection;
- unrelated-bit preservation;
- no output-image mutation on Codec failure;
- no hardware write on Driver validation failure.

### Duty validation

Pure and Driver-level tests must cover:

- duty `0`, `1`, `500`, `999`, and `1000`;
- invalid duty above `1000`;
- PWM mode 1 and PWM mode 2;
- active-high and active-low polarity semantics;
- ARR `1`, representative intermediate values, and `65534`;
- rejected ARR `0` and `65535`;
- round-half-up boundaries;
- exact 0% and 100%;
- 64-bit intermediate arithmetic;
- readable programmed state versus deferred active preload state.

### Transaction validation

Tests must demonstrate:

- `TIM_ConfigPWM()` rejects a running Timer;
- `TIM_ConfigPWM()` rejects an enabled channel;
- Timer timebase fields are preserved;
- IRQ, DMA, RCC, and NVIC state are preserved;
- `TIM_ConfigPWM()` returns with channel and counter disabled;
- stopped duty updates perform the controlled commit;
- running duty updates wait for the next natural update event;
- multi-channel output-state updates use one staged CCER write;
- deconfiguring one channel preserves every other channel;
- getters leave caller output unchanged on failure.

### Build and documentation validation

The implementation wave must include:

- `arm-none-eabi-gcc -fsyntax-only -Wall -Wextra -Werror` for affected Timer
  sources;
- affected Timer, GPIO, Template, and PWM project builds;
- Doxygen generation with warning review;
- direct-register-access and ignored-status searches;
- legacy PWM API and dynamic-allocation searches;
- `git diff --check`.

Temporary host test artifacts remain under `/tmp`; no repository `Test/` or
`Tests/` directory is introduced.

### On-target reference validation

The first board reference must demonstrate:

- application-owned PA2 and PA3 alternate-function configuration;
- TIM2 configured before either PWM channel;
- TIM2 CH3 and CH4 configured while TIM2 is stopped;
- both channel outputs enabled before TIM2 is started;
- both outputs running from the same Timer timebase;
- exact 0% and 100%;
- representative intermediate duties;
- a running duty ramp using CCR preload;
- PWM mode 1 and PWM mode 2 behavior;
- active-high and active-low behavior;
- stopping and deconfiguring without hidden GPIO, RCC, IRQ, or NVIC changes.

## Deferred scope

The following work is explicitly deferred from the base implementation:

- GPIO/AFIO route discovery, validation, configuration, restoration, or
  ownership transfer;
- Timer-frequency request solving inside Timer PWM;
- hidden Timer ownership, shared-frequency registries, or automatic duty
  repair after an ARR change;
- TIM1 advanced-control output, MOE, complementary outputs, break, and dead
  time;
- remapped Timer channels and SWJ conflict policy;
- center-aligned, down-counting, and one-pulse PWM;
- input capture, encoder, DMA waveform, or interrupt-driven PWM services;
- phase-coherent enabling of a new individual channel into an already-running
  period;
- RTOS/thread/ISR synchronization;
- dynamic allocation and opaque handles.

Deferred features require a new top-down ownership and transaction review. They
must not be added by enlarging `TIM_ConfigPWM()` with unrelated fields.

## Implementation admission gates

Source implementation begins only after the relevant open Timer safety gates
are resolved:

- coherent programmed-versus-active preload semantics;
- correct write-only EGR and W0C SR behavior;
- stopped-Timer controlled update-event sequencing;
- complete no-write-on-error and post-mutation cleanup proof;
- channel-mask validation and CCMR1/CCMR2/CCR selection coverage;
- preservation of unrelated Timer channel, IRQ, DMA, RCC, and NVIC state;
- review of the errata applicable to the deployed STM32F103C8T6 revision.

These gates are implementation prerequisites, not reasons to weaken the
ownership decisions recorded in this guide.
