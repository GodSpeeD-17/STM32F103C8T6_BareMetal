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
| Timer config | `BareMetal/Driver/Timer/Inc/timer_config.h` | Timer-independent public configuration structures, including `timer_config_t` as a structure of structures | Timer instance pointers, register access, RCC/NVIC access, driver orchestration |
| Timer LL | `BareMetal/Driver/Timer/Inc/timer_ll.h` | Dumb static inline register read/write helpers and minimal register address macros | Validation, encoding, mode decisions, batching, clock/reset sequencing, NVIC policy |
| Timer codec | `BareMetal/Driver/Timer/Inc/timer_codec.h`, `BareMetal/Driver/Timer/Src/timer_codec.c` | Private Encode/Decode helpers and public Extract/Stage functions over caller-owned register images | Hardware reads/writes, clock sequencing, public API decisions |
| Timer driver | `BareMetal/Driver/Timer/Inc/timer.h`, `BareMetal/Driver/Timer/Src/timer.c` | Public API, validation, orchestration, clock enable/reset, batching, dirty-register writes, status handling, NVIC policy | Raw register map definitions, direct register field placement when codec can own it |
| Project/application | `Projects/*` and shared startup code | Board/application behavior and examples | Driver internals and raw register writes unless intentionally teaching raw access |

## Core Register Layer

Core must stay hardware-shaped. Timer Core content should include only:

- `TIM_TypeDef` and advanced timer raw register structs.
- Raw `TIM_*_Pos`, `TIM_*_Msk`, and raw bit masks.
- Reset/raw values when they are direct reference-manual facts.
- Base addresses and instance macros.

Public Timer selectors and defaults have been moved out of Core during this
refactor. Core raw Timer macros now provide hardware-shaped positions, masks,
and register-positioned raw values for codec use.

## Timer Data Types

`timer_data_types.h` defines Timer scalar aliases such as:

- `timer_channel_t`
- `timer_channel_index_t`
- `timer_count_mode_t`
- `timer_direction_t`
- `timer_arpe_t`
- `timer_opm_t`
- `timer_update_source_t`
- `timer_irq_t`
- `timer_channel_mode_t`
- `timer_channel_ccs_t`
- `timer_channel_oc_preload_t`
- `timer_channel_oc_fast_t`
- `timer_channel_oc_clear_t`
- `timer_channel_polarity_t`
- `timer_prescaler_t`
- `timer_auto_reload_t`
- `timer_counter_value_t`
- `timer_frequency_t`

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

- `timer_config_timebase_t`
  - `prescaler`
  - `auto_reload`
  - `initial_count`
- `timer_config_counter_t`
  - `direction`
  - `alignment`
  - `one_pulse`
  - `auto_reload_preload`
  - `update_source`
  - `clock_division`
- `timer_config_t`
  - `timebase`
  - `counter`

`timer_config.h` must not own register access helpers, clock enable/reset
helpers, NVIC helpers, public driver API declarations, or codec staging.

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

- `Codec_TIM_ExtractChannelConfig(...)` / `Codec_TIM_StageChannelConfig(...)`
- `Codec_TIM_ExtractChannelPolarity(...)` / `Codec_TIM_StageChannelPolarity(...)`
- `Codec_TIM_ExtractIRQStatus(...)`
- `Codec_TIM_StageIRQAck(...)`
- `Codec_TIM_ExtractIRQEnable(...)` / `Codec_TIM_StageIRQEnable(...)`

Every meaningful Stage API should have a conjugate Extract API. Extraction-only
APIs are acceptable for naturally read-only or action-style register behavior.

Codec APIs may validate inputs and should return `driver_status_t` whenever
validation can fail.

## Timer Driver Layer

The driver layer owns public behavior.

It must:

- Expose public status-returning APIs in `timer.h`.
- Consume public Timer configuration structures from `timer_config.h`.
- Validate public arguments before touching hardware.
- Enable required clocks before register access.
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

- `TIM_Config()` and `TIM_DeConfig()`
- grouped `TIM_GetTimebaseConfig()` / `TIM_SetTimebaseConfig()`
- grouped `TIM_GetCounterConfig()` / `TIM_SetCounterConfig()`
- scalar `Get`/`Set` APIs for `prescaler`, `auto_reload`, `counter_value`,
  `direction`, `alignment`, `one_pulse`, `auto_reload_preload`,
  `update_source`, and `clock_division`
- derived convenience getter `TIM_GetFrequency()`

`TIM_Config()` reads only `CR1`, `PSC`, `ARR`, and `CNT`, stages through the
codec, and writes only changed staged images. `TIM_DeConfig()` restores only
the fields represented by `timer_config_t`; it preserves unrelated CR1 runtime
bits such as `CEN` and `UDIS`.

Unlike GPIO, Timer should keep a structured configuration API. GPIO can remain
ergonomic with a small fixed argument list because its basic configuration is
only port, pin mask, mode, and config. Timer configuration spans clock period,
counter behavior, update-event behavior, channel selection, channel mode,
preload/fast/clear behavior, polarity, and IRQ concerns. A configuration
structure keeps that API modular and extensible. The refactor should therefore
fix ownership and staging of `timer_config_t`, not remove the structured
configuration model.

## Current Checkpoint

Completed:

- Core Timer raw field macros exist for the first codec pass.
- Public Timer scalar aliases live in `timer_data_types.h`.
- Public Timer selectors/defaults/validation helpers live in `timer_defines.h`.
- Public Timer configuration structures live in `timer_config.h`.
- Timer LL exists and exposes dumb full-register read/write helpers.
- Timer codec exists and operates on caller-owned register images.
- `timer.h` is public API only for the first-pass config-owned Timer fields.
- `timer.c` orchestrates first-pass config-owned fields through validation, LL,
  codec staging, dirty writes, and `driver_status_t` status handling.

Remaining:

- Channel/PWM public APIs are deferred and must be rebuilt on top of codec/LL
  boundaries.
- Timer IRQ public APIs are deferred and must be rebuilt so codec owns DIER/SR
  mapping and the driver owns NVIC policy.
- Project examples still use legacy Timer APIs and old configuration field
  names.
- Doxygen/style still needs a full pass across all Timer files.

## Compatibility Boundary

Initial refactor steps should prefer compatibility over unnecessary renaming:

- Preserve existing public `TIM_*` function names where possible.
- Preserve existing `TIMx_*` selector names initially.
- Keep `timer_config_t` and related public configuration structures as the
  Timer configuration API. `TIMx` stays a function argument, not a config
  member, so one configuration can be reused across Timer instances.
- Update examples only after the public header/API contract changes.

This branch intentionally accepts some compatibility breakage while the layer
boundaries are being corrected. The Timer examples must be migrated before
project builds are expected to be green again.
