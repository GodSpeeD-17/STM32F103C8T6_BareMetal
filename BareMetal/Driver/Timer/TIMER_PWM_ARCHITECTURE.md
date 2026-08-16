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
- Successful `TIM_Config()` completion is the PWM lifecycle admission point;
  Timer PWM does not independently query or mutate the RCC clock gate.
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
| API terminology | Use `PWMChannel` as the public subject. Lifecycle conjugates are `TIM_ConfigPWMChannel()` / `TIM_DeConfigPWMChannel()`; readable domains use symmetric `TIM_GetPWMChannel*()` / `TIM_SetPWMChannel*()` names. `OutputEnableState` names `CCxE` control and must not be shortened to the ambiguous physical-signal term `OutputState`. |
| Timer lifecycle | The application successfully configures the Timer first, configures PWM second, and enables the Timer last. |
| RCC boundary | Timer PWM neither queries nor mutates the Timer clock gate; successful `TIM_Config()` is its lifecycle prerequisite. |
| Frequency ownership | Timer timebase APIs own PSC, ARR, counter mode, and resulting PWM frequency. Timer PWM does not accept or set frequency. |
| GPIO ownership | The application owns GPIO mode, output speed, alternate-function selection, AFIO remap, and pin lifecycle. |
| PWM-channel configuration | `TIM_ConfigPWMChannel()` accepts channel mode and channel polarity as independent scalar parameters. |
| Duty configuration | `TIM_SetPWMChannelDutyCycle()` is a separate operation using the already-programmed ARR. |
| Output-enable state | Timer PWM controls selected `CCxE` channel-output-enable bits; `TIM_SetOperationState()` independently controls `CR1.CEN`. |
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
Application configures each PWM channel through TIM_ConfigPWMChannel()
        ↓
Application assigns each channel duty through TIM_SetPWMChannelDutyCycle()
        ↓
Application enables the required channel output(s)
        ↓
Application enables TIMx through TIM_SetOperationState()
```

The architectural precondition is therefore:

```text
TIM_Config() succeeds
        before
TIM_ConfigPWMChannel() / TIM_SetPWMChannelDutyCycle()
        before
TIM_SetOperationState(TIMx, DRIVER_STATUS_ON)
```

Timer PWM never calls `TIM_Config()` or `TIM_SetOperationState()` on behalf of
the application and never queries or mutates the Timer RCC clock gate. A
successful `TIM_Config()` call is the evidence that the application admitted
the Timer lifecycle before entering the PWM subdomain. This keeps timebase
ownership, channel ownership, clock ownership, and counter operation visible
at the call site.

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
timebase suitable for PWM before calling `TIM_ConfigPWMChannel()`.

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
`TIM_ConfigPWMChannel()` rejects either boundary instead of silently approximating or
clamping it.

### Polarity

Polarity is applied after the internal output-reference signal:

- Active-high polarity makes the active interval electrically high.
- Active-low polarity makes the active interval electrically low.

Duty always means the fraction of the period spent at the selected active
polarity. Changing polarity changes the electrical level identified as active;
it does not change the duty calculation.

### Channel output-enable state and counter operation state

Two independent enable decisions are involved:

- `TIMx_CCER.CCxE` connects the selected channel output to the Timer output
  path.
- `TIMx_CR1.CEN` starts or stops the shared Timer counter.

Timer PWM owns the public channel-output operation, but the application retains
explicit Timer-counter control. Enabling a PWM channel does not start the
Timer, and disabling a PWM channel does not stop the Timer.

This independence permits several configured channels to share one running
counter while the application changes individual channel output-enable states.

### Preload and update events

CCR preload is mandatory while an admitted PWM channel can run. With preload
enabled, a CCR write changes the programmed preload value while the active
compare value is transferred at a natural update event.

This prevents an active-period duty update from changing the compare boundary
partway through that same period.

Two cases are distinguished:

1. **Timer stopped and selected output disabled:** Timer PWM temporarily
   disables only the selected lane's CCR preload, writes that lane's active CCR
   directly, and restores CCR preload before returning.
2. **Timer running:** Timer PWM writes the CCR preload and allows the next
   natural update event to activate it. Successful return means the programmed
   preload was updated; activation occurs at the next period boundary.

The stopped path deliberately does not write `EGR.UG`. A software update event
is Timer-wide: it can transfer every enabled ARR/CCR preload, reset the
prescaler phase and counter, affect status/request timing, and drive `TRGO`.
Using the selected lane's direct-load window therefore preserves every other
channel's pending preload and all Timer-wide update consumers. If the selected
output is still enabled, the stopped duty setter returns
`DRIVER_STATUS_ERROR_BUSY`; the application explicitly disables it first.

`TIM_Config()` remains responsible for activating the base PSC/ARR state before
PWM channel configuration begins. Timer PWM never repeats that base-owned
update transaction.

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
the duty of every configured PWM channel before enabling the Timer again. Each
selected channel output must be disabled while its stopped-state duty is
reapplied. Timer PWM stores no requested-duty registry from which to repair
channels automatically.

### Register mapping bridge

PWM has no independent register block. TIM2, TIM3, and TIM4 start at
`0x40000000`, `0x40000400`, and `0x40000800`, respectively. Every address below
is the selected instance base plus the stated offset. The LL performs aligned
32-bit transfers even where only the low 16 bits are implemented.

| Concept | Register/field | Software owner | Offset | Implemented width/range | Access class | Semantics and relationships |
| --- | --- | --- | ---: | --- | --- | --- |
| Counter and base PWM policy | `CR1.CEN`, `UDIS`, `URS`, `OPM`, `DIR`, `CMS`, `ARPE` | Timer base | `0x00` | Bits 0..7 used; PWM admits CEN=0 for configuration, UDIS=0, OPM=0, DIR=0, CMS=0, ARPE=1 | R/W | PWM reads the complete image for preconditions and never changes CEN or base policy |
| Master trigger selection | `CR2.MMS[2:0]` | Timer synchronization/application | `0x04` | Bits 6:4, encodings 0..7 | R/W | Selects `TRGO`; PWM preserves it and emits no software update action that could create a hidden trigger pulse |
| Slave/external clock control | `SMCR` | Timer synchronization/application | `0x08` | Implemented low 16 bits | R/W | Can make counter state asynchronous to software; PWM does not configure it and requires serialized application ownership |
| IRQ/DMA request enables | `DIER` | Timer IRQ/DMA domains | `0x0C` | Implemented bits 0..4, 6, 8..14 | R/W | PWM neither reads nor writes request enables |
| Event status | `SR` | Timer event domain | `0x10` | Implemented bits 0..4, 6, 9..12 | R/W, write-0-to-clear | PWM never acknowledges flags; unrelated status cannot be lost through a PWM transaction |
| Software event action | `EGR.UG` | Timer base commit domain | `0x14` | UG is bit 0 | Write-only action, self-clearing | UG transfers all enabled preloads and resets counter/prescaler phase; Timer PWM deliberately never writes EGR |
| Channel 1/2 mode lanes | `CCMR1.CCxS`, `OCxFE`, `OCxPE`, `OCxM`, `OCxCE` | Timer PWM per selected lane | `0x18` | Two 8-bit lanes in bits 15:0 | R/W | Selected lane is staged locally; other lane and reserved bits are preserved |
| Channel 3/4 mode lanes | `CCMR2.CCxS`, `OCxFE`, `OCxPE`, `OCxM`, `OCxCE` | Timer PWM per selected lane | `0x1C` | Two 8-bit lanes in bits 15:0 | R/W | Same lane semantics as CCMR1; CCxS is changed only while CCxE is clear |
| Output gate and polarity | `CCER.CCxE`, `CCxP` | Timer PWM | `0x20` | Enable/polarity pairs at bits 0/1, 4/5, 8/9, 12/13 | R/W | Masked state updates stage one complete CCER image; CEN remains independent |
| Counter phase | `CNT[15:0]` | Timer base | `0x24` | `0..65535` | R/W | PWM reads it only for the stopped initial-phase precondition and never writes it |
| Timer tick divider | `PSC[15:0]` | Timer base | `0x28` | `0..65535`, divide by PSC+1 | R/W, buffered | PWM neither reads nor writes PSC; the base Timer owns frequency |
| Period boundary | `ARR[15:0]` | Timer base | `0x2C` | Hardware `0..65535`; PWM admits `1..65534` | R/W, optionally buffered | PWM reads the programmed period for exact duty arithmetic and never writes ARR |
| Channel compare boundaries | `CCR1..CCR4[15:0]` | Timer PWM selected channel | `0x34`, `0x38`, `0x3C`, `0x40` | `0..65535` | Output: R/W; input: read-only capture | With OCxPE=1, access targets preload; with OCxPE=0, writes affect active compare immediately. An input-mode read can consume capture notification state, so PWM establishes output interpretation first |

GPIO `CRL`/`CRH` and AFIO `MAPR` determine whether a Timer signal reaches a
physical pin, but those registers are outside Timer PWM ownership in this base
architecture.

The hardware behavior above is grounded in the general-purpose Timer chapters
of the
[`STM32F103C Reference Manual`](../../../Reference_Docs/STM32F103C_Reference_Manual.pdf)
and the package/pin information in the
[`STM32F103C8T6 Datasheet`](../../../Reference_Docs/STM32F103C8T6_Datasheet.pdf).

### Applicable errata review

The applicable
[`ES096 STM32F103x8/B errata sheet`](https://www.st.com/resource/en/errata_sheet/es096-stm32f101x8b-stm32f102x8b-and-stm32f103x8b-mediumdensity-device-limitations-stmicroelectronics.pdf)
was reviewed for this scope. Its Timer findings do not require a PWM Driver
workaround because:

- the consecutive-compare limitation states that output modes other than
  toggle operate as expected, while this Driver admits only PWM mode 1/2;
- the output-compare-clear and 100-percent regulation limitations require
  `OCxCE`, which the admitted shape forces and validates disabled;
- the input-capture flag limitations reinforce the rule that configuration
  never reads an input-mode CCR and getters establish output interpretation
  before reading CCR; and
- the TRGO documentation erratum reinforces application-owned synchronization;
  Timer PWM preserves CR2/SMCR and generates no `EGR.UG` action.

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
- query or mutate RCC clock gates;
- allocate memory;
- call public Timer APIs as a substitute for owning its complete transaction.

Public Timer PWM APIs own validation, register snapshots, Codec staging,
ordered writes, selected-lane preload sequencing, and detailed status
propagation.

### Core representation and volatile-access contract

`TIM_TypeDef` is a volatile Core-owned structure whose member order matches the
hardware offsets above. CR1, CR2, SMCR, DIER, SR, CCMR1, CCMR2, and CCER expose
32-bit `.REG` images; CNT, PSC, and ARR are volatile 32-bit scalar members; each
CCR exposes a read-only input alias and a read/write output alias. EGR is marked
with the project's write-only `_O` convention because standard C has no native
write-only qualifier.

Timer PWM never uses `.BIT` members or a live register pointer. Each LL call
performs one named, aligned, 32-bit volatile transfer. The Driver snapshots
through LL, transforms caller-owned `reg` images through Codec, and sends final
images back through LL. `volatile` guarantees an access is emitted; the Driver
transaction and documentation supply the mode, ordering, and side-effect
rules that C qualifiers cannot express.

### Theory-to-implementation trace

| Public intent | Core registers | LL route | Codec role | Driver transaction |
| --- | --- | --- | --- | --- |
| Validate PWM base | CR1, ARR, and stopped CNT | `LL_TIM_ReadCR1/ARR/CNT()` | Extract counter config, update-event state, ARR, CEN, and CNT | Reject incompatible timebase, invalid exact-duty period, running configuration, or nonzero stopped phase before any write |
| Configure mode/polarity | CCMR1/2, CCER, selected CCR | Named CCMR/CCER reads and named CCMR/CCER/CCR writes | Stage output-compare shape, polarity, enable-off state, and compare scalar | With CEN=0 and CCxE=0, write selected lane with OCxPE=0, load active CCR, then write final selected lane with OCxPE=1; no EGR/SR/CR1 write |
| Get mode/polarity | CCMR1/2 and CCER | Named reads | Extract and validate complete admitted shape | Decode into locals and publish both outputs only after success |
| Set stopped duty | CR1, ARR, CNT, CCMR1/2, CCER, selected CCR | Named reads/writes | Validate shape, calculate/stage compare, stage temporary OCxPE=0 lane | Require CCxE=0, directly load only the selected active CCR, and restore its final CCMR image |
| Set running duty | CR1, ARR, CCMR1/2, CCER, selected CCR | Named reads plus one dirty CCR write | Validate shape and stage mode-correct compare | Update programmed CCR preload; hardware activates it at the next natural update boundary |
| Get duty | CR1, ARR, CCMR1/2, CCER, selected CCR | Named reads | Extract admitted mode, ARR, and compare scalar | Reconstruct achieved permille duty locally and publish only after success |
| Set channel output-enable state | CCMR1/2 and CCER | Read required CCMRs and one CCER; write CCER at most once | Validate selected PWM lanes and stage each CCxE | Validate the complete mask first, then commit one coherent CCER image without touching CEN |
| Get channel output-enable state | CCMR1/2 and CCER | Named reads | Validate PWM shape and extract CCxE | Return ON/OFF directly without collapsing errors |
| Deconfigure one channel | CR1, CCMR1/2, CCER, selected CCR | Named reads/writes | Validate current shape and stage reset selectors/scalar | Require CEN=0 and CCxE=0, then reset only the selected lane, polarity/enable pair, and CCR |

No Timer PWM path reads or writes PSC, writes ARR/CNT/CR1, accesses EGR/SR,
changes CR2/SMCR/DIER, or performs a subword Timer transfer. Those deliberate
omissions preserve Timer base, synchronization, IRQ/DMA, and event ownership.

### Implementation file layout

Only these new files belong to the base implementation:

```text
BareMetal/Driver/Timer/Inc/timer_pwm.h
BareMetal/Driver/Timer/Src/timer_pwm.c
BareMetal/Driver/Timer/TIMER_PWM_ARCHITECTURE.md
```

Existing Timer files receive only domain-appropriate extensions:

- `timer_data_types.h` owns `tim_pwm_duty_cycle_t` and the register-semantic
  `tim_compare_value_t` scalar used by CCR Codecs.
- `timer_defines.h` owns duty limits and PWM-specific validation helpers.
- `timer_codec.h/.c` own any missing CCR and coherent output-field
  Extract/Stage operations.
- `timer_ll.h` supplies the demanded named CR1, ARR, CNT, CCMR1/2, CCER, and
  CCR1-4 access; Timer PWM deliberately does not demand EGR or SR access.
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
driver_status_t TIM_ConfigPWMChannel
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channel,
	const tim_channel_mode_t channelMode,
	const tim_channel_polarity_t channelPolarity
);

driver_status_t TIM_GetPWMChannelConfig
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channel,
	tim_channel_mode_t* const pChannelMode,
	tim_channel_polarity_t* const pChannelPolarity
);

driver_status_t TIM_DeConfigPWMChannel
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channel
);

driver_status_t TIM_SetPWMChannelDutyCycle
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channel,
	const tim_pwm_duty_cycle_t dutyCycle
);

driver_status_t TIM_GetPWMChannelDutyCycle
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channel,
	tim_pwm_duty_cycle_t* const pDutyCycle
);

driver_status_t TIM_SetPWMChannelOutputEnableState
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channelMask,
	const driver_status_t outputEnableState
);

driver_status_t TIM_GetPWMChannelOutputEnableState
(
	TIM_TypeDef* const TIMx,
	const tim_channel_t channel
);
```

Identity is never embedded in configuration state:

- `TIMx` selects the Timer instance.
- `channel` selects exactly one Timer channel for configuration and getters.
- `channelMask` selects one or more already-configured PWM channels for one
  coherent output-enable-state update.

### Why there is no PWM configuration structure

Channel mode and channel polarity form the narrow PWM-channel configuration
transaction and are passed directly to `TIM_ConfigPWMChannel()`. Duty has a
distinct lifecycle and preload/update contract, so it is configured separately.

Frequency and GPIO output speed are deliberately absent:

- Frequency belongs to the previously configured Timer timebase.
- GPIO output speed belongs to the application-owned GPIO configuration.

A structure containing those values would cross ownership boundaries and
allow independent fields to imply an orchestration policy that Timer PWM does
not own.

### `TIM_ConfigPWMChannel()` contract

`TIM_ConfigPWMChannel()` configures one Timer channel for PWM but never enables the
channel or starts the counter.

Required preconditions:

- `TIMx` is `TIM2`, `TIM3`, or `TIM4`.
- The application successfully completed `TIM_Config()` and has not
  invalidated the admitted Timer lifecycle.
- `TIMx_CR1.CEN` is clear.
- The selected `CCxE` bit is clear.
- The Timer is edge-aligned and up-counting.
- One-pulse mode is disabled.
- ARR preload and update-event operation satisfy the admitted PWM contract.
- `CNT` is zero.
- ARR is in `1..65534`.
- `channel` contains exactly one of `TIMx_CHANNEL_1` through
  `TIMx_CHANNEL_4`.
- `channelMode` is PWM mode 1 or PWM mode 2.
- `channelPolarity` is active-high or active-low.

The transaction:

1. Validates every argument and all required Timer state.
2. Reads each required CCMR, CCER, CR1, ARR, and CNT image once. It does not
   read CCR; the operation replaces the selected channel's compare state, and
   an input-mode CCR read could consume capture notification state.
3. Stages `CCxS` as output, the requested PWM mode, CCR preload enabled,
   output-compare fast disabled, and output-compare clear disabled.
4. Stages the requested polarity while keeping `CCxE` disabled.
5. Derives the mode-correct exact 0% CCR value from the programmed period.
6. Stages every prospective register image before the first hardware write.
7. Writes the selected CCMR lane with CCR preload temporarily disabled.
8. Writes the selected CCR directly into its active compare state.
9. Writes the final selected CCMR lane with CCR preload enabled.
10. Returns with the channel disabled and Timer counter stopped.

An error before the first write leaves Timer state unchanged. After the first
write, no further fallible validation or Codec operation is permitted.

When converting an input-capture lane, the Driver writes CCR only after CCMR
establishes output interpretation. This preserves unread input-capture
notification state during validation and avoids a mode-dependent consuming
read. The direct-load window is safe because CEN and selected CCxE are both
clear; the final image restores the mandatory PWM preload before return.

### `TIM_GetPWMChannelConfig()` contract

The getter verifies that the selected channel has the complete admitted PWM
shape:

- `CCxS` selects output compare.
- `OCxM` selects PWM mode 1 or PWM mode 2.
- `OCxPE` is enabled.
- `OCxFE` and `OCxCE` are disabled.
- Polarity is decodable.

Both output pointers are required. The function decodes into local variables
and writes `pChannelMode` and `pChannelPolarity` only after the complete
operation succeeds.
Caller output storage remains unchanged on failure.

### `TIM_SetPWMChannelDutyCycle()` contract

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
7. Writes CCR only after all fallible work succeeds.
8. If the Timer is stopped, requires selected CCxE clear, temporarily disables
   selected OCxPE, writes the selected active CCR directly, and restores OCxPE.
9. If the Timer is running, leaves activation to the next natural update
   event.

The running-Timer return contract describes programmed preload state, not proof
that the active CCR has already transferred.

The stopped-Timer return contract guarantees that the selected active compare
value was loaded without transferring another channel's pending preload or
generating a Timer-wide update/TRGO action.

### `TIM_GetPWMChannelDutyCycle()` contract

The getter reads the programmed ARR and selected CCR, validates the PWM mode,
reconstructs active ticks according to PWM mode 1 or PWM mode 2, and reports
the achieved duty rounded to the nearest permille value.

No requested-duty value is retained. The getter reports what the programmed
Timer state represents. Its output remains unchanged on failure.

If the Timer is running, the result describes the readable programmed CCR
preload and may differ temporarily from the active compare value until the next
update event.

### PWM channel output-enable-state contracts

`TIM_SetPWMChannelOutputEnableState()` changes only `CCxE` for the selected channel mask.
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

`TIM_GetPWMChannelOutputEnableState()` accepts exactly one channel and returns
`DRIVER_STATUS_OFF`, `DRIVER_STATUS_ON`, or a detailed error status directly.

### `TIM_DeConfigPWMChannel()` contract

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
| `DRIVER_STATUS_SUCCESS` | Configuration, duty-cycle, output-enable-state, or deconfiguration operation completed. |
| `DRIVER_STATUS_OFF` | Direct output-enable-state getter reports the selected channel disabled. |
| `DRIVER_STATUS_ON` | Direct output-enable-state getter reports the selected channel enabled. |
| `DRIVER_STATUS_ERROR_NULL_PTR` | `TIMx` or required output storage is `NULL`. |
| `DRIVER_STATUS_ERROR_INVALID_ARG` | Instance, channel, mask, channel mode, channel polarity, duty cycle, or admitted ARR range is invalid. |
| `DRIVER_STATUS_ERROR_STATE` | Timer base state is incompatible or the channel does not have the admitted PWM shape. |
| `DRIVER_STATUS_ERROR_BUSY` | Configuration/deconfiguration requires a stopped counter or disabled channel, or stopped-duty loading requires selected CCxE clear. |

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
- Channel output-enable state never starts or stops the shared counter.
- The application decides which channels are enabled before starting TIMx.
- The application stops TIMx before changing the shared timebase.
- The application reapplies every duty value after changing ARR.

This model makes the shared hardware relationship explicit instead of
duplicating it in software state.

### Concurrency and ownership guard

The base Driver contains no lock, critical section, reference count, or ISR
coordination. The application must serialize Timer base and Timer PWM calls for
one `TIMx`, prevent an ISR/DMA peer from mutating the same register images, and
prevent slave/trigger hardware from starting a supposedly stopped counter
during configuration. A getter racing a mutator is likewise outside the base
contract.

This is an explicit exclusive-owner precondition, not hidden state. A future
RTOS, DMA waveform, or synchronized-Timer feature must introduce its own
top-down ownership review before it can share these transactions.

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

- `TIM_ConfigPWMChannel()` rejects a running Timer;
- `TIM_ConfigPWMChannel()` rejects an enabled channel;
- Timer timebase fields are preserved;
- IRQ, DMA, RCC, and NVIC state are preserved;
- `TIM_ConfigPWMChannel()` returns with channel and counter disabled;
- stopped duty updates require selected CCxE clear and load only the selected
  active CCR without writing EGR, SR, CR1, or another channel;
- running duty updates wait for the next natural update event;
- multi-channel output-enable-state updates use one staged CCER write;
- deconfiguring one channel preserves every other channel;
- getters leave caller output unchanged on failure.

### Build and documentation validation

The implementation wave must include:

- `arm-none-eabi-gcc -fsyntax-only -Wall -Wextra -Werror` for affected Timer
  sources;
- affected Timer, GPIO, Template, and PWM project builds;
- Doxygen generation with warning review;
- direct-register-access and ignored-status searches;
- RCC include, query, and mutation searches in `timer_pwm.c`;
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
must not be added by enlarging `TIM_ConfigPWMChannel()` with unrelated fields.

## Implementation admission gates

Source implementation is commit-admissible only after these Timer PWM safety
gates are resolved:

- coherent programmed-versus-active preload semantics;
- no Timer PWM access to write-only EGR or W0C SR;
- no Timer PWM query or mutation of RCC clock-gate state;
- selected-lane stopped loading without a Timer-wide update event;
- complete no-write-on-error and post-mutation cleanup proof;
- channel-mask validation and CCMR1/CCMR2/CCR selection coverage;
- preservation of unrelated Timer channel, IRQ, DMA, RCC, and NVIC state;
- review of the errata applicable to the deployed STM32F103C8T6 revision.

These gates are implementation prerequisites, not reasons to weaken the
ownership decisions recorded in this guide.
