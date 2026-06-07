# Timer Driver Refactor Architecture

This document captures the intended Timer driver architecture before code
movement begins. It is scoped to the current general-purpose Timer driver
surface for `TIM2`, `TIM3`, `TIM4`, and `TIM5`.

The first refactor pass should preserve the current public Timer vocabulary
where practical, including existing `TIMx_*` selector names, so each change can
be committed and reviewed independently. Naming cleanup can happen after the
layer boundaries are correct.

## Target Layers

| Layer | Files | Owns | Must Avoid |
| --- | --- | --- | --- |
| Core register layer | `BareMetal/Core/Inc/stm32f1xx_timer.h`, raw Timer section in `stm32f1xx_defines.h` | Raw STM32F1 register structs, raw bit positions, masks, reset values, and base mappings | Driver selectors, validation policy, public config structs, orchestration |
| Timer data types | `BareMetal/Driver/Timer/Inc/timer_data_types.h` | Timer scalar aliases and plain shared data aliases | Public selector macros, validation, register access, hardware writes |
| Timer defines | `BareMetal/Driver/Timer/Inc/timer_defines.h` | Public Timer selectors, defaults, pure validation helpers, simple selector utilities | Hardware reads/writes, sequencing, raw field placement |
| Timer LL | `BareMetal/Driver/Timer/Inc/timer_ll.h` | Dumb static inline register read/write helpers and minimal register address macros | Validation, encoding, mode decisions, batching, clock/reset sequencing, NVIC policy |
| Timer codec | `BareMetal/Driver/Timer/Inc/timer_codec.h`, `BareMetal/Driver/Timer/Src/timer_codec.c` | Private Encode/Decode helpers and public Extract/Stage functions over caller-owned register images | Hardware reads/writes, clock sequencing, public API decisions |
| Timer driver | `BareMetal/Driver/Timer/Inc/timer.h`, optional public config header, `BareMetal/Driver/Timer/Src/timer.c` | Public API, public configuration structures, validation, orchestration, clock enable/reset, batching, dirty-register writes, status handling, NVIC policy | Raw register map definitions, direct register field placement when codec can own it |
| Project/application | `Projects/*` and shared startup code | Board/application behavior and examples | Driver internals and raw register writes unless intentionally teaching raw access |

## Core Register Layer

Core must stay hardware-shaped. Timer Core content should include only:

- `TIM_TypeDef` and advanced timer raw register structs.
- Raw `TIM_*_Pos`, `TIM_*_Msk`, and raw bit masks.
- Reset/raw values when they are direct reference-manual facts.
- Base addresses and instance macros.

Current public Timer selectors and defaults in `stm32f1xx.h` must move out of
Core during this refactor.

## Timer Data Types

`timer_data_types.h` should define Timer scalar aliases such as:

- `tim_channel_t`
- `tim_channel_index_t`, if useful for codec/driver iteration
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

The file should include `stm32f1xx_data_types.h`, not the full `stm32f1xx.h`
unless a later step proves that unavoidable.

`timer_data_types.h` should not own full configuration structures. Timer
configuration is intentionally richer than GPIO configuration, so public
configuration structures remain a Timer driver-layer API concern.

## Timer Defines

`timer_defines.h` should own public selector values and validation helpers.

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

Public codec APIs should use Extract/Stage naming:

- `Codec_TIM_ExtractCounterConfig(...)`
- `Codec_TIM_StageCounterConfig(...)`
- `Codec_TIM_ExtractClockConfig(...)`
- `Codec_TIM_StageClockConfig(...)`
- `Codec_TIM_ExtractChannelConfig(...)`
- `Codec_TIM_StageChannelConfig(...)`
- `Codec_TIM_ExtractChannelPolarity(...)`
- `Codec_TIM_StageChannelPolarity(...)`
- `Codec_TIM_ExtractIRQStatus(...)`
- `Codec_TIM_StageIRQAck(...)`
- `Codec_TIM_ExtractIRQEnable(...)`
- `Codec_TIM_StageIRQEnable(...)`

Every meaningful Stage API should have a conjugate Extract API. Extraction-only
APIs are acceptable for naturally read-only or action-style register behavior.

Codec APIs may validate inputs and should return `driver_status_t` whenever
validation can fail.

## Timer Driver Layer

The driver layer owns public behavior.

It must:

- Own public Timer configuration structures such as `tim_clk_config_t`,
  `tim_param_t`, `tim_channel_config_t`, `tim_channel_instance_t`, and
  `timer_config_t`.
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

Unlike GPIO, Timer should keep a structured configuration API. GPIO can remain
ergonomic with a small fixed argument list because its basic configuration is
only port, pin mask, mode, and config. Timer configuration spans clock period,
counter behavior, update-event behavior, channel selection, channel mode,
preload/fast/clear behavior, polarity, and IRQ concerns. A configuration
structure keeps that API modular and extensible. The refactor should therefore
fix ownership and staging of `timer_config_t`, not remove the structured
configuration model.

## Current Deviations

- `timer_config.h` combines public config structs with LL-style register
  access, RCC access, NVIC dependency, and policy helpers. The configuration
  structs are intentional; the extra authority in the same header is the
  deviation.
- `timer.h` exposes inline hardware accessors and duplicate declarations.
- `timer.c` directly reads and writes peripheral registers instead of using LL.
- Public selector enums and Timer defaults live in `stm32f1xx.h`.
- No Timer codec exists.
- Register field placement is spread across driver/header code.
- Current driver APIs mostly return `void` or raw `uint8_t`.
- `TIM_Config()` performs unconditional writes and ORs fields without clearing
  old field values first.
- IRQ enable/disable policy does not account for other still-enabled Timer IRQ
  sources before disabling NVIC.
- Doxygen/style does not match the finalized GPIO/GPIO_IRQ layer style.

## Compatibility Boundary

Initial refactor steps should prefer compatibility over renaming:

- Preserve existing public `TIM_*` function names where possible.
- Preserve existing `TIMx_*` selector names initially.
- Keep `timer_config_t` and related public configuration structures as the
  Timer configuration API. Their exact fields can be refined later, but the
  structured configuration model should remain.
- Update examples only after the public header/API contract changes.

Breaking API cleanup can be planned after the Timer layer boundaries are correct
and builds are green.
