# Timer Driver Refactor Architecture

This document captures the intended Timer driver architecture and the current
refactor checkpoint. It is scoped to the current general-purpose Timer driver
surface for `TIM2`, `TIM3`, `TIM4`, and `TIM5`.

The first refactor pass preserves the current public Timer selector vocabulary
where practical, including existing `TIMx_*` selector names. Public helper APIs
that depended on the old configuration shape can be rebuilt after the layer
boundaries are correct.

## Target Layers

| Layer | Files | Owns | Must Avoid |
| --- | --- | --- | --- |
| Core register layer | `BareMetal/Core/Inc/stm32f1xx_timer.h`, raw Timer section in `stm32f1xx_defines.h` | Raw STM32F1 register structs, raw bit positions, masks, reset values, and base mappings | Driver selectors, validation policy, public config structs, orchestration |
| Timer data types | `BareMetal/Driver/Timer/Inc/timer_data_types.h` | Timer scalar aliases and plain shared data aliases | Public selector macros, validation, register access, hardware writes |
| Timer defines | `BareMetal/Driver/Timer/Inc/timer_defines.h` | Public Timer selectors, defaults, pure validation helpers, simple selector utilities | Hardware reads/writes, sequencing, raw field placement |
| Timer config | `BareMetal/Driver/Timer/Inc/timer_config.h` | Timer-independent public configuration structures, including `tim_config_t` as a structure of structures | Timer instance pointers, register access, RCC/NVIC access, driver orchestration |
| Timer LL | `BareMetal/Driver/Timer/Inc/timer_ll.h` | Dumb static inline register read/write helpers and minimal register address macros | Validation, encoding, mode decisions, batching, clock-state sequencing, NVIC policy |
| Timer codec | `BareMetal/Driver/Timer/Inc/timer_codec.h`, `BareMetal/Driver/Timer/Src/timer_codec.c` | Private Encode/Decode helpers and public Extract/Stage functions over caller-owned register images | Hardware reads/writes, clock-state sequencing, public API decisions |
| Timer driver | `BareMetal/Driver/Timer/Inc/timer.h`, `BareMetal/Driver/Timer/Src/timer.c` | Public API, validation, orchestration, clock-state handling, batching, dirty-register writes, status handling, NVIC policy | Raw register map definitions, direct register field placement when codec can own it |
| Project/application | `Projects/*` and shared startup code | Board/application behavior and examples | Driver internals and raw register writes unless intentionally teaching raw access |

## Core Register Layer

Core must stay hardware-shaped. Timer Core content should include only:

- `TIM_TypeDef` and advanced timer raw register structs.
- Raw `TIM_*_Pos`, `TIM_*_Msk`, and raw bit masks.
- Reset/raw values when they are direct reference-manual facts.
- Base addresses and instance macros.

Public Timer selectors and defaults have been moved out of Core during this
refactor. Core raw Timer macros now provide hardware-shaped positions, masks,
and register-positioned raw values for codec use. Shared channel-field values
use the STM32 field notation directly, for example `CCxS`, `OCxM`,
`ICxPSC`, and `ICxF`.

## Timer Data Types

`timer_data_types.h` defines Timer scalar aliases such as:

- `tim_channel_t`
- `tim_channel_index_t`
- `tim_count_mode_t`
- `tim_direction_t`
- `tim_arpe_t`
- `tim_opm_t`
- `tim_update_source_t`
- `tim_irq_t`
- `tim_channel_mode_t`
- `tim_channel_ccs_t`
- `tim_channel_oc_preload_t`
- `tim_channel_oc_fast_t`
- `tim_channel_oc_clear_t`
- `tim_channel_polarity_t`
- `tim_prescaler_t`
- `tim_auto_reload_t`
- `tim_counter_value_t`
- `tim_frequency_t`

The file should include `stm32f1xx_data_types.h`, not the full `stm32f1xx.h`
unless a later step proves that unavoidable.

`timer_data_types.h` does not own full configuration structures. Timer
configuration is intentionally richer than GPIO configuration, so public
configuration structures live in `timer_config.h`.

## Timer Configuration

`timer_config.h` owns Timer configuration structures only. They are deliberately
timer-instance independent so the same configuration object can be applied to
`TIM2`, `TIM3`, `TIM4`, or `TIM5` by passing the instance separately to the
driver API.

Current first-pass structure shape:

- `tim_config_timebase_t`
  - `prescaler`
  - `auto_reload`
  - `initial_count`
- `tim_config_counter_t`
  - `direction`
  - `alignment`
  - `one_pulse`
  - `auto_reload_preload`
  - `update_source`
  - `clock_division`
- `tim_config_t`
  - `timebase`
  - `counter`

`timer_config.h` must not own register access helpers, clock-state helpers,
NVIC helpers, public driver API declarations, or codec staging.

## Timer Defines

`timer_defines.h` owns public selector values and validation helpers.

Expected groups:

- Timer instance validation for `TIM2`, `TIM3`, `TIM4`, and `TIM5`.
- Timer channel selectors and channel-mask validation.
- Counter mode, direction, preload, one-pulse, and update-source selectors.
- Channel output/input selectors and validation.
- IRQ selectors and IRQ-mask validation.
- Current default presets such as 10 kHz, 1 MHz, and reset count defaults.

The defines layer may contain pure helper functions for mask/index conversion,
but must not read or write hardware and must not place fields into register
images.

## Timer LL Layer

`timer_ll.h` should be intentionally dumb.

Expected accessors:

- `LL_TIM_REG(TIMx, REG)` built on `REGOPS_REG`.
- Generic `LL_TIM_ReadRegister()` and `LL_TIM_WriteRegister()` helpers using
  `RegOps_Read()` and `RegOps_Write()`.
- Named register readers/writers for `CR1`, `CR2`, `SMCR`, `DIER`, `SR`,
  `EGR`, `CCMR1`, `CCMR2`, `CCER`, `CNT`, `PSC`, `ARR`, `CCR1` through `CCR4`,
  `DCR`, and `DMAR` as needed.

LL must not:

- Validate public Timer config.
- Translate `TIMx_*` selectors.
- Decide which registers must be read.
- Encode CCMR/CCER/CR1/DIER/SR fields.
- Enable or disable NVIC IRQs.
- Enable, disable, or reset Timer clocks.
- Poll, delay, or make mode decisions.

## Timer Codec Layer

The codec layer must operate only on caller-owned register images.

Private helpers should be named and scoped for encoding/decoding raw fields,
for example:

- encode/decode counter config fields for `CR1`.
- encode/decode channel config fields for `CCMR1` and `CCMR2`.
- encode/decode channel polarity and enable fields for `CCER`.
- encode/decode IRQ selectors into `DIER` enable masks and `SR` status masks.
- compute channel-local field positions.

Public codec APIs use Extract/Stage naming. The first-pass timebase and counter
configuration APIs include:

- `Codec_TIM_ExtractPrescaler(...)`
- `Codec_TIM_StagePrescaler(...)`
- `Codec_TIM_ExtractAutoReload(...)`
- `Codec_TIM_StageAutoReload(...)`
- `Codec_TIM_ExtractCounterValue(...)`
- `Codec_TIM_StageCounterValue(...)`
- `Codec_TIM_ExtractTimeBaseConfig(...)`
- `Codec_TIM_StageTimeBaseConfig(...)`
- `Codec_TIM_ExtractCounterConfig(...)`
- `Codec_TIM_StageCounterConfig(...)`
- `Codec_TIM_ExtractCounterDirection(...)`
- `Codec_TIM_StageCounterDirection(...)`
- `Codec_TIM_ExtractCounterAlignment(...)`
- `Codec_TIM_StageCounterAlignment(...)`
- `Codec_TIM_ExtractOnePulse(...)`
- `Codec_TIM_StageOnePulse(...)`
- `Codec_TIM_ExtractAutoReloadPreload(...)`
- `Codec_TIM_StageAutoReloadPreload(...)`
- `Codec_TIM_ExtractUpdateSource(...)`
- `Codec_TIM_StageUpdateSource(...)`
- `Codec_TIM_ExtractClockDivision(...)`
- `Codec_TIM_StageClockDivision(...)`

Channel/PWM and IRQ codec surfaces can build on the same rules:

- `Codec_TIM_ExtractCounterEnableState(...)` / `Codec_TIM_StageCounterEnableState(...)`
- `Codec_TIM_ExtractUpdateEventState(...)` / `Codec_TIM_StageUpdateEventState(...)`
- `Codec_TIM_ExtractChannelConfig(...)` / `Codec_TIM_StageChannelConfig(...)`
- `Codec_TIM_ExtractChannelEnableState(...)` / `Codec_TIM_StageChannelEnableState(...)`
- `Codec_TIM_ExtractChannelPolarity(...)` / `Codec_TIM_StageChannelPolarity(...)`
- `Codec_TIM_ExtractIRQStatus(...)`
- `Codec_TIM_StageIRQAck(...)`
- `Codec_TIM_ExtractIRQEnable(...)` / `Codec_TIM_StageIRQEnable(...)`

Every meaningful Stage API should have a conjugate Extract API. Extraction-only
APIs are acceptable for naturally read-only or action-style register behavior.

Codec APIs may validate inputs and should return `driver_status_t` whenever
validation can fail. For binary state extraction APIs, the returned
`driver_status_t` is the decoded state itself, either `DRIVER_STATUS_OFF` or
`DRIVER_STATUS_ON`, with error statuses used only when validation can fail.
Non-state extraction APIs use output pointers and return operation status.

Timer public and codec-visible Doxygen should make value scope visible at the
call site:

- Use `Accepted values` for caller-provided input parameters.
- Use `Expected values` for values written through output parameters.
- Use `Accepted member values` or `Expected member values` when the parameter
  is a structure and the relevant scope is member-level.
- Prefer concrete `@ref` entries over wildcard text so users can jump directly
  to selector definitions.

## Timer Driver Layer

The driver layer owns public behavior.

It must:

- Expose public status-returning APIs in `timer.h`.
- Consume public Timer configuration structures from `timer_config.h`.
- Validate public arguments before touching hardware.
- Own or verify required clocks before register access, according to each API
  ownership boundary.
- Own reset/update-event sequencing.
- Decide which registers must be read.
- Read each required register once.
- Stage changes through codec APIs.
- Write only when the staged image differs from the original image.
- Return `driver_status_t` for primary public mutation/extraction APIs.
- Own NVIC enable/disable policy for Timer IRQ APIs.

Existing value-returning APIs can remain as wrappers where useful, but the
primary public path should be status-returning.

Current first-pass public API scope:

- RCC clock-gate state APIs `TIM_GetClockState()` / `TIM_SetClockState()`
- counter operation state APIs `TIM_GetOperationState()` /
  `TIM_SetOperationState()`
- `TIM_Config()` and `TIM_DeConfig()`
- grouped `TIM_GetTimebaseConfig()` / `TIM_SetTimebaseConfig()`
- grouped `TIM_GetCounterConfig()` / `TIM_SetCounterConfig()`
- scalar `Get`/`Set` APIs for `prescaler`, `auto_reload`, `counter_value`,
  `direction`, `alignment`, `one_pulse`, `auto_reload_preload`,
  `update_source`, and `clock_division`
- derived convenience getter `TIM_GetFrequency()`

`TIM_GetClockState()` and `TIM_SetClockState()` own only the RCC APB1 clock
gate for one supported Timer instance. They do not start/stop the counter and
do not reset or rewrite Timer registers.

`TIM_GetOperationState()` and `TIM_SetOperationState()` own only
`TIMx_CR1.CEN`. They do not enable or disable the RCC APB1 clock gate. Public
users must enable the Timer clock gate before calling the operation-state APIs
directly.

### Clock Ownership Policy

Timer public APIs must not hide broad side effects behind narrow names. The
Timer layer therefore separates:

- clock-gate state: RCC APB1 enable bit, owned only by
  `TIM_GetClockState()` and `TIM_SetClockState()`.
- operation state: `TIMx_CR1.CEN`, owned only by `TIM_GetOperationState()` and
  `TIM_SetOperationState()`.
- configuration orchestration: `TIM_Config()` and `TIM_DeConfig()` may use the
  clock-state and operation-state APIs internally because their names describe
  a full Timer lifecycle operation.

Grouped and scalar `Get`/`Set` APIs such as `TIM_GetPrescaler()`,
`TIM_SetAutoReload()`, and `TIM_SetDirection()` do not silently enable the RCC
clock gate. Their narrower contract is to read or modify one Timer-owned
configuration field. Those APIs verify that `TIM_GetClockState(TIMx)` returns
`DRIVER_STATUS_ON`, and return `DRIVER_STATUS_ERROR_STATE` when
the clock gate is disabled. The current implementation centralizes that
precondition in the private `_TIM_ClockEnabled()` helper.

This keeps call-site behavior explicit:

```c
ASSERT_DRIVER_STATUS(TIM_SetClockState(TIM2, DRIVER_STATUS_ON));
ASSERT_DRIVER_STATUS(TIM_SetPrescaler(TIM2, prescaler));
```

Instead of allowing `TIM_SetPrescaler()` to change RCC state as a hidden side
effect.

`TIM_Config()` validates the full public configuration, enables the Timer clock
gate through `TIM_SetClockState(TIMx, DRIVER_STATUS_ON)`, disables the counter
through `TIM_SetOperationState(TIMx, DRIVER_STATUS_OFF)`, reads the
configuration-owned registers, stages through the codec, writes only changed
`CR1`, `PSC`, and `ARR` images, temporarily clears `CR1.UDIS` for the forced
`TIMx_EGR.UG`, restores the final `CR1` image, conditionally clears a generated
`TIMx_SR.UIF`, and writes `TIMx_CNT` after the update event only when the
requested initial count differs from the post-update counter image. The current
implementation leaves the counter disabled after configuration; users explicitly
start the counter with
`TIM_SetOperationState(TIMx, DRIVER_STATUS_ON)`.

### Configuration Latch Policy

Timer configuration is not just "write the register and forget it." Some Timer
register writes feed shadow/preload logic:

- `TIMx_PSC` is loaded into the active prescaler on an update event.
- `TIMx_ARR` may be immediate or preloaded depending on `TIMx_CR1.ARPE`.
- `TIMx_EGR.UG` forces an update event so staged timebase values become active.
- `TIMx_CR1.UDIS` can block that update event, so root configuration temporarily
  clears `UDIS` around the generated `UG` and restores the final `CR1` image
  afterward.
- Forcing `EGR.UG` can set `TIMx_SR.UIF`, so the driver may need to clear that
  generated flag before returning.

The implemented `TIM_Config()` sequence is:

1. Validate `TIMx` and @p pConfig.
2. Enable the RCC APB1 clock gate with
   `TIM_SetClockState(TIMx, DRIVER_STATUS_ON)`.
3. Disable counter operation with
   `TIM_SetOperationState(TIMx, DRIVER_STATUS_OFF)`.
4. Read `CR1`, `PSC`, `ARR`, and pre-update `SR` into local images.
5. Stage `CR1`, `PSC`, `ARR`, and requested `CNT` through codec APIs.
6. Build a pre-update `CR1` image from the final staged `CR1` image with
   `UDIS` cleared.
7. Write only changed pre-update `CR1`, `PSC`, and `ARR` staged images.
8. Generate `TIMx_EGR.UG` through the codec-staged update event image so `PSC`
   and any preloaded `ARR` value are latched.
9. If `TIMx_SR.UIF` was clear before `UG`, clear `UIF` after `UG` only if that
   generated update event made it pending. A pre-existing pending `UIF` is
   preserved.
10. Restore the final `CR1` image, including the `UDIS` state that
    `tim_config_t` does not own.
11. Read `CNT` after `UG`, then write the requested initial counter value only
   when it differs from the post-update counter image.
12. Leave operation disabled until the user calls
    `TIM_SetOperationState(TIMx, DRIVER_STATUS_ON)`.

`TIM_DeConfig()` enables the Timer clock gate through
`TIM_SetClockState(TIMx, DRIVER_STATUS_ON)`, disables the counter through
`TIM_SetOperationState(TIMx, DRIVER_STATUS_OFF)`, restores only the fields
represented by `tim_config_t` through the same forced-update latch sequence,
restores the original `UDIS` state, writes reset `CNT` after `UG`, and then
disables the Timer clock gate through `TIM_SetClockState(TIMx, DRIVER_STATUS_OFF)`.
It does not issue an RCC peripheral reset and does not touch channel, IRQ, PWM,
DMA, master/slave, or delay-helper state.

Unlike GPIO, Timer should keep a structured configuration API. GPIO can remain
ergonomic with a small fixed argument list because its basic configuration is
only port, pin mask, mode, and config. Timer configuration spans clock period,
counter behavior, update-event behavior, channel selection, channel mode,
preload/fast/clear behavior, polarity, and IRQ concerns. A configuration
structure keeps that API modular and extensible. The refactor should therefore
fix ownership and staging of `tim_config_t`, not remove the structured
configuration model.

## Coding Style

Timer files follow the established banner style:

```c
// ==================================================================================================== //
```

Use tabs for indentation.

When a function declaration, function definition, or function-like macro call
has exactly one argument, keep the argument on the same line as the function
name:

```c
driver_status_t TIM_DeConfig(TIM_TypeDef* const TIMx);
ASSERT_DRIVER_STATUS(TIM_ValidateInstance(TIMx));
```

Reserve the multiline parenthesized layout for functions or function-like
macro calls with multiple arguments, or for expressions that cannot stay
readable in a single line.

## Current Checkpoint

Completed:

- Core Timer raw field macros exist for the first codec pass.
- Public Timer scalar aliases live in `timer_data_types.h`.
- Public Timer selectors/defaults/validation helpers live in `timer_defines.h`.
- Public Timer configuration structures live in `timer_config.h`.
- Timer LL exists and exposes dumb full-register read/write helpers.
- Timer codec exists and operates on caller-owned register images.
- Binary state codec extractors return decoded `DRIVER_STATUS_OFF` or
  `DRIVER_STATUS_ON` directly.
- `timer.h` is public API only for the first-pass config-owned Timer fields.
- RCC clock-gate state APIs `TIM_GetClockState()` and `TIM_SetClockState()`
  are exposed before configuration APIs.
- Counter operation state APIs `TIM_GetOperationState()` and
  `TIM_SetOperationState()` are exposed.
- Grouped and scalar `Get`/`Set` APIs verify that the RCC APB1 clock gate is
  already enabled and return `DRIVER_STATUS_ERROR_STATE` when it
  is not.
- `timer.h`, `timer_config.h`, and `timer_codec.h` now document input
  `Accepted values` and output `Expected values` for the current public and
  codec-visible Timer scope.
- `TIM_Config()` now temporarily clears `CR1.UDIS`, generates `TIMx_EGR.UG`,
  restores the final `CR1` image, preserves pre-existing `TIMx_SR.UIF`, clears
  only a newly generated update flag, and applies `TIMx_CNT` after the update
  event.
- `TIM_DeConfig()` stops the counter, restores only config-owned fields, and
  ends at the Timer clock-gate boundary without issuing RCC peripheral reset.
- `timer.c` orchestrates first-pass config-owned fields through validation, LL,
  codec staging, dirty writes, and `driver_status_t` status handling.

Remaining:
- Channel/PWM public APIs are deferred and must be rebuilt on top of codec/LL
  boundaries.
- Timer IRQ public APIs are deferred and must be rebuilt so codec owns DIER/SR
  mapping and the driver owns NVIC policy.
- Project examples still use legacy Timer APIs and old configuration field
  names.
- Remaining Timer Doxygen/style work is limited to files not covered by the
  latest header pass, especially source-local helper documentation, defines,
  and deferred public APIs.

## Compatibility Boundary

Initial refactor steps should prefer compatibility over unnecessary renaming:

- Preserve existing public `TIM_*` function names where possible.
- Preserve existing `TIMx_*` selector names initially.
- Keep `tim_config_t` and related public configuration structures as the
  Timer configuration API. `TIMx` stays a function argument, not a config
  member, so one configuration can be reused across Timer instances.
- Update examples only after the public header/API contract changes.

This branch intentionally accepts some compatibility breakage while the layer
boundaries are being corrected. The Timer examples must be migrated before
project builds are expected to be green again.
