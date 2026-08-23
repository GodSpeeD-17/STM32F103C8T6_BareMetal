# USART Implementation Guide {#USART_Peripheral_Guide}

This directory contains the STM32F1 USART driver family. Use this file as the
implementation entry point before editing USART code.

This document builds on the repository-wide rules in `../../../ARCHITECTURE.md`
and records the USART-specific scope, architecture, ownership rules, and
migration plan. The commit-sized checklist lives in
[`TODO.md`](TODO.md). Hardware register semantics are taken from the
`STM32F103C_Reference_Manual.pdf` (RM0008), USART chapter — the same manual
that governs the Timer stack.

## Scope

This pass implements **UART (asynchronous) mode only** for `USART1`,
`USART2`, and `USART3` on the STM32F103C8T6. Synchronous clock output and the
other USART hardware modes are deliberately deferred; see
[Deferred Domains](#deferred-domains). This mirrors how the Timer stack
deferred capture/DMA/encoder support until a named consumer needed them.

Non-goals for this pass:

- Synchronous USART (clock-out) mode.
- Smartcard, IrDA, and LIN modes.
- Multiprocessor addressed wake-up.
- DMA-driven TX/RX.
- GPIO/AFIO pin configuration, routing, and remap — entirely application-owned,
  matching Timer PWM's GPIO ownership model; the driver has no pin concept at
  all.

## Instance Capability Table

| Instance | Bus | Clock enable | Reset | IRQ line | Notes |
| --- | --- | --- | --- | --- | --- |
| `USART1` | APB2 | `RCC_APB2ENR_USART1EN` | `RCC_APB2RSTR_USART1RST` | `USART1_IRQn` (37) | Kernel clock is `PCLK2` |
| `USART2` | APB1 | `RCC_APB1ENR_USART2EN` | `RCC_APB1RSTR_USART2RST` | `USART2_IRQn` (38) | Kernel clock is `PCLK1` |
| `USART3` | APB1 | `RCC_APB1ENR_USART3EN` | `RCC_APB1RSTR_USART3RST` | `USART3_IRQn` (39) | Kernel clock is `PCLK1` |

The STM32F103C8T6 has no `USART4`/`USART5` peripheral. The current
`usart_t` enum incorrectly includes `USART_4`/`USART_5` values; they are
removed as part of this migration.

## Current And Intended File Map

| File | Layer | Responsibility |
|------|-------|----------------|
| `Inc/usart_data_types.h` | Data Types | USART scalar typedef aliases |
| `Inc/usart_defines.h` | Defines/Validation | Public USART selector macros and pure validation/policy macros |
| `Inc/usart_ll.h` | Low-Level | Dumb single point for named USART register reads/writes |
| `Inc/usart_codec.h`, `Src/usart_codec.c` | Codec | Selector encoding/decoding, BRR divider math, staged register-image mutation |
| `Inc/usart_config.h` | Config | Instance-independent `usart_config_t` structure-of-structures |
| `Inc/usart.h`, `Src/usart.c` | Driver | Public USART API, validation, clock-state verification, sequencing, batching, status returns |

## Goals

- Keep direct USART register access in the low-level layer only.
- Keep BRR divider math, CR1/CR2/CR3 field placement, and selector
  translation in the codec layer.
- Keep USART instance identity on the same pointer-based convention as GPIO
  and Timer (`USART_TypeDef* const USARTx`), not a private enum + lookup
  table.
- Keep the USART peripheral clock gate and the GPIO/AFIO pin clock gates
  exclusively application/RCC-owned; the driver only verifies.
- Keep IRQ *sources* (enable bits) and IRQ *events* (status flags) as
  separate vocabularies, matching the Timer driver's
  `tim_irq_source_t`/`tim_event_flag_t` split.
- Keep baud rate as a fixed preset selector (matching the original
  `usart_baud_t` enum's supported rates), resolved to its numeric
  bits-per-second value inside the codec before computing the divider
  against the live bus frequency.

## Implementation Rules

- Keep raw register definitions in `BareMetal/Core/Inc/stm32f1xx_usart.h`.
- Keep USART scalar aliases in `usart_data_types.h`. No pin-mapping
  structures — GPIO/AFIO is entirely application-owned.
- Keep public selector macros and pure validation macros together in
  `usart_defines.h`.
- Keep direct hardware reads/writes in the low-level layer. Low-level APIs
  read or write one full register image and know nothing about which public
  selector produced that image.
- Keep BRR mantissa/fraction computation, CR1/CR2/CR3 field placement, and
  SR flag interpretation in the codec layer. Codec APIs take caller-owned
  register images (and, for baud rate, a caller-supplied bus frequency) and
  return `driver_status_t`.
- Codec image-mutating APIs must be conjugate pairs: every
  `Codec_USART_Stage*()` has a matching `Codec_USART_Extract*()`.
  Extraction-only APIs are allowed for naturally read-only or asymmetric
  hardware behavior (see [IRQ Source/Event Model](#irq-sourceevent-model)).
- Keep batching and write ordering in the driver. GPIO pin setup and its
  clock gates are never a driver responsibility — the application owns
  GPIO mode, output speed, AFIO remap, and pin lifecycle for the USART's
  TX/RX/RTS/CTS pins entirely, exactly like Timer PWM's GPIO ownership
  model. The driver has no pin table at all.

## Layer Ownership

| Layer | USART Files | Owns | Must Avoid |
|-------|-------------|------|------------|
| Core | `BareMetal/Core/Inc/stm32f1xx_usart.h` | USART register structs, offsets, raw masks, reset-level hardware facts | Driver selectors, board aliases, public validation |
| Data Types | `Inc/usart_data_types.h` | Scalar aliases such as `usart_data_bits_t`, `usart_parity_t`, `usart_stop_bits_t`, `usart_hardware_enable_t`, `usart_irq_source_t`, `usart_event_flag_t` | Public selector macros, validation macros, `USART_TypeDef`, register layout, board behavior, GPIO/pin structures |
| Defines/Validation | `Inc/usart_defines.h` | Public USART selector macros, instance validation for `USART1`/`USART2`/`USART3`, pure validation/policy macros | Hardware reads/writes, clock sequencing, raw register field placement |
| Low-Level | `Inc/usart_ll.h` | Named static inline register read/write accessors, `LL_USART_*` API names | Public selector translation, field mapping, clock policy, board behavior |
| Codec | `Inc/usart_codec.h`, `Src/usart_codec.c` | Encoding/decoding selectors, BRR divider math, CR1/CR2/CR3 field placement, SR flag interpretation, caller-owned register-image staging/extraction | Hardware reads/writes, clock sequencing, public API policy |
| Config | `Inc/usart_config.h` | Instance-independent `usart_config_t` root structure | Register access, RCC/NVIC access, driver orchestration, GPIO/pin data |
| Driver | `Inc/usart.h`, `Src/usart.c` | Public APIs, argument validation, clock-state verification, IRQ source/event handling, status returns | Raw register map definitions, board-specific shortcuts, GPIO/AFIO configuration or clocking |
| Board/Project | `Projects/*` | Application-owned USART peripheral clock gate, GPIO/AFIO pin configuration and clock gates, examples | USART internals, raw register assumptions |

## Codec Rationale

`usart_codec.h/.c` is the compatibility boundary between stable public USART
selectors and raw STM32F1 bit definitions, the same role `gpio_codec.h/.c`
and `timer_codec.h/.c` play for their drivers.

Use the codec layer for:

- `TE`/`RE` hardware-enable staging in `CR1`.
- `M`/`PCE`/`PS` (data bits/parity) and `CR2.STOP` staging — the current
  `usart_data_config_t` bit-packed encoding.
- `RTSE`/`CTSE` hardware flow-control staging in `CR3`.
- `UE` operation-state staging in `CR1`.
- BRR mantissa/fraction computation from `(busFrequency, baudRate)` per
  RM0008, where `baudRate` is resolved from its preset selector to a numeric
  bits-per-second value first — pure arithmetic, no register access, so it
  belongs here rather than in the driver.
- IRQ source staging/extraction across `CR1` (`IDLEIE/RXNEIE/TCIE/TXEIE/
  PEIE`) and `CR3` (`CTSIE`, `EIE`).
- IRQ event extraction from `SR`, with the asymmetric acknowledgement rules
  documented explicitly rather than hidden behind a generic "ack" call.

Do not use the codec layer for direct hardware access, public input
validation, clock sequencing, or GPIO pin policy.

## Intended Configuration Flow

```c
driver_status_t USART_Config(USART_TypeDef* const USARTx, const usart_config_t* const pConfig);
```

The driver should:

1. Validate `USARTx` identity and every field in `pConfig`.
2. Verify the USART peripheral clock gate is already enabled (application
   owns enabling it through RCC beforehand) — return
   `DRIVER_STATUS_ERROR_STATE` otherwise.
3. Read `CR1`/`CR2`/`CR3`/`BRR` once each.
4. Stage hardware-enable, data-config, flow-control, and baud-rate fields
   through codec APIs.
5. Write only the dirty registers.
6. Return a user-facing `driver_status_t`.

`USART_Config()` never enables the USART peripheral's own clock gate — that
is exclusively an application/RCC operation, matching the rule already
enforced for `GPIO_Init()` and `TIM_Config()`. It also never touches GPIO
mode, AFIO remap, or GPIO/AFIO clock gates: the application configures and
clocks whichever physical TX/RX/RTS/CTS pins it has routed entirely on its
own, before calling this API — exactly matching Timer PWM's GPIO ownership
model, not the driver-owned pin table an earlier draft of this document
proposed.

## Clock Ownership Policy

Only one clock gate is ever the USART driver's concern, and even that one is
application-owned:

**The USART peripheral's own clock gate** (`RCC_APB2ENR_USART1EN`,
`RCC_APB1ENR_USART2EN`/`USART3EN`). The application must enable this through
`RCC_SetPeripheralClockState()` with `RCC_APB1_BUS` or `RCC_APB2_BUS` before
calling `USART_Config()`. The driver only verifies it through a private
`_USART_ValidateClockEnabled()` helper — the direct USART analogue of
Timer's `_TIM_ValidateClockEnabled()`. This replaces the current
`usart_config.h`'s `__USART_enableClock__()`/`__USART_disableClock__()`,
which self-enable the peripheral clock from inside the driver and must be
removed.

**GPIO/AFIO pin clocks are entirely out of the driver's scope**, matching
Timer PWM's `TIMER_PWM_ARCHITECTURE.md` exactly: the driver has no pin
table, so it never enables a GPIO/AFIO clock gate itself. The application
must:

- enable the required GPIO port and AFIO clocks;
- configure GPIO mode, output speed, and AFIO remap for the TX/RX/RTS/CTS
  pins it has chosen to route to a given USART instance;
- retain that GPIO configuration while the USART instance is in use; and
- restore or repurpose the GPIO pins after USART deconfiguration.

```c
ASSERT_DRIVER_STATUS
(
	RCC_SetPeripheralClockState
	(
		RCC_APB2_BUS,
		RCC_APB2ENR_USART1EN,
		DRIVER_STATUS_ON
	)
);
// Application also enables the GPIO/AFIO clocks and configures TX/RX pins
// here, exactly like a Timer PWM channel — the driver takes no part in it.
ASSERT_DRIVER_STATUS(USART_Config(USART1, &config));
```

## Baud Rate Policy

Keep the original `usart_baud_t` preset vocabulary (`9600`..`921600`),
carried forward as the current `usart_baud_rate_t`/`USART_BAUD_RATE_*`
selector convention instead of the old enum-plus-lookup-table shape. The
codec resolves the selected preset to its numeric bits-per-second value
internally and computes the `BRR` mantissa/fraction against the live bus
frequency (`RCC_GetBusFrequency()`):

```c
driver_status_t Codec_USART_StageBaudRate(reg* const pBrrRegImage, const frequency_t busFrequency, const usart_baud_rate_t baudRate);
driver_status_t Codec_USART_ExtractBaudRate(const reg brrRegImage, const frequency_t busFrequency, usart_baud_rate_t* const pBaudRate);
```

`Codec_USART_ExtractBaudRate()` resolves the closest supported preset to the
raw `BRR` divider; it is not guaranteed to round-trip exactly because `BRR`
quantizes to 1/16th-bit-period steps.

## IRQ Source/Event Model

Following the Timer driver's `tim_irq_source_t`/`tim_event_flag_t` split,
USART separates *enable-capable interrupt sources* from *latched status
flags* instead of reusing one `usart_irq_t` for both, which is what the
current `USART_IRQ_Enable()`/`USART_IRQ_Disable()` do today via a fragile
`(irq & 0x1F) << USART_CR1_IDLEIE_Pos` shift that only works because CR1
bit order happens to match the enum, and has no `CR3` coverage at all.

- `usart_irq_source_t` — enable bits: `CR1.IDLEIE`, `CR1.RXNEIE`,
  `CR1.TCIE`, `CR1.TXEIE`, `CR1.PEIE`, `CR3.CTSIE`, `CR3.EIE`.
- `usart_event_flag_t` — `SR` status: `PE`, `FE`, `NE`, `ORE`, `IDLE`,
  `RXNE`, `TC`, `TXE`, `CTS`.

Canonical functions:

```c
USART_GetIRQSources(...)
USART_SetIRQSources(...)
USART_GetIRQEvents(...)
USART_AckIRQEvents(...)
```

Acknowledgement is **not** uniform across `SR` bits, and the codec/driver
must document this explicitly rather than hide it behind one generic ack
call:

- `TC` and `CTS` are write-0-to-clear.
- `PE`, `FE`, `NE`, `ORE`, `IDLE`, and `RXNE` clear only through the
  hardware-mandated sequence of reading `SR` followed by reading `DR`; they
  cannot be cleared by writing `SR` directly.
- `TXE` is read-only status (set when `DR` is written); it is never
  acknowledged.

`USART_AckIRQEvents()` must apply the correct clearing mechanism per
selected bit rather than performing one uniform register write.

## Compatibility Boundary

Preserve existing public `USART_*` function names and the `usart_config_t`
root-structure concept where they do not conflict with the fixes below,
matching the same compatibility-boundary policy the Timer migration used.

Not preserved (deliberate breaks, each with a stated reason):

- `usart_t` enum and `__usartDriverRegisterMapping__[]` — replaced by direct
  `USART_TypeDef*` pointer identity, matching `GPIOx`/`TIMx`.
- `USART_4`/`USART_5` selectors — the peripherals don't exist on this part.
- `__usartDriverBaudRateMapping__[]` public lookup table — the preset
  vocabulary itself is kept (renamed to `usart_baud_rate_t`/
  `USART_BAUD_RATE_*`), but the bps resolution table moves inside
  `usart_codec.c` as private implementation detail.
- `usart_irq_t` single-vocabulary enum and the `irq & 0x1F` shift trick —
  replaced by the `usart_irq_source_t`/`usart_event_flag_t` split.
- `__USART_enableClock__()`/`__USART_disableClock__()` — removed; the
  application owns the USART peripheral clock gate through RCC.
- `__usartDriverGPIOMapping__[]` pin table and any driver-owned GPIO/AFIO
  pin-clock sequencing — removed entirely, not just re-keyed. GPIO/AFIO pin
  selection, configuration, and clocking become fully application-owned,
  matching Timer PWM's GPIO ownership model, rather than migrated into the
  new driver.

## Deferred Domains

| Domain | Registers | Disposition |
| --- | --- | --- |
| Synchronous clock output | `CR2.CLKEN/CPOL/CPHA/LBCL`, `CK` pin | Deferred; `usart_hardware_enable_t`'s `USART_CK_ENABLE` is not exposed by `USART_Config()` in this pass |
| Smartcard | `CR3.SCEN/NACK`, `GTPR` | Deferred; no consumer |
| IrDA | `CR3.IREN/IRLP` | Deferred; no consumer |
| LIN break detection | `CR2.LINEN/LBDL`, `CR2.LBDIE` (source) | Deferred; no consumer |
| Multiprocessor address/wake | `CR1.WAKE`, `CR2.ADD` | Deferred; no consumer |
| DMA | `CR3.DMAR/DMAT` | Deferred; needs a peer contract with the `DMA` driver, same open item Timer records for its own DMA sources |

Raw register fields for these domains stay defined in Core/LL as
unclassified raw foundation; they do not justify Driver/Codec scope until a
named consumer admits them, per the top-down audit's admission test.

## Suggested Commit Order

See [`TODO.md`](TODO.md) for the exact commit-sized checklist. In summary:

1. Documentation (this file and `TODO.md`).
2. Data types and defines/validation split.
3. Low-level `LL_USART_*` register access.
4. Codec translation and BRR/field staging.
5. Config structure migration to pointer identity (no pin table — GPIO/AFIO
   stay application-owned, matching Timer PWM).
6. Driver orchestration (clock verification, IRQ source/event split).
7. Removal of `usart_t`/preset enums/the lookup table.
8. Project migration (`08_USART_Byte_Poll_TX`, `09_USART_Byte_Poll_RX`,
   `10_USART_printf`).
9. Doxygen pass.

## Before Editing

1. Read `../../../ARCHITECTURE.md`.
2. Decide which layer owns the change.
3. Keep the edit inside that layer unless the change is intentionally part of
   a staged migration step from `TODO.md`.
4. Compile at least the touched USART source files with the Arm toolchain.

## Useful Compile Check

```bash
/opt/arm-gnu-toolchain-14.3/bin/arm-none-eabi-gcc \
  -mcpu=cortex-m3 -mthumb -DSTM32F103C8T6__ \
  -IBareMetal/Core/Inc \
  -IBareMetal/Driver \
  -IBareMetal/Driver/USART/Inc \
  -IBareMetal/Driver/GPIO/Inc \
  -IBareMetal/Driver/RCC/Inc \
  -IBareMetal/Driver/NVIC/Inc \
  -std=gnu11 -Wall -Wextra -ffreestanding \
  -c BareMetal/Driver/USART/Src/usart.c \
  -o /tmp/usart.o
```
