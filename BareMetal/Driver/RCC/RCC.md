# STM32F103C8T6 RCC Architecture {#RCC_Peripheral_Guide}

**Scope and reading order.**

This page describes the Reset and Clock Control block implemented by the
STM32F103C8T6 and then traces that hardware model into this repository's RCC
stack.

RCC is the single peripheral that supplies every bus clock and most
peripheral clocks in the MCU. Its current documented and implemented scope
covers: the HSI/HSE/PLL clock sources, the SYSCLK mux, the AHB/APB1/APB2 bus
prescalers, the ADC and USB component prescalers, the Flash latency/prefetch
coupling to SYSCLK, peripheral clock-enable gating (`AHBENR`/`APB2ENR`/
`APB1ENR`), and peripheral reset pulsing (`APB2RSTR`/`APB1RSTR`).

The backup-domain control register (`BDCR`: LSE, RTC), the control/status
register (`CSR`: LSI, reset-cause flags), and the clock interrupt register
(`CIR`: oscillator-ready interrupts and the Clock Security System) are
physically part of the RCC block and are documented at the register layer for
completeness, but no LL or Driver function in this repository reads, writes,
or reacts to any of their bits today. Part II explains this as a deliberate,
currently unimplemented scope boundary rather than an oversight.

Read the two major parts in order:

1. **Theory with Register Mapping Bridge** explains the clock-tree model and
   the significance of every register without depending on project source
   code.
2. **Implementation with Theory Bridge** maps that theory into the Core, LL,
   Codec, Driver, and public API.

## Part I — Theory with Register Mapping Bridge

### What RCC does

Every other peripheral on the chip is either unclocked or misclocked until
RCC has: started a clock source, routed it to become the system clock,
divided that system clock down through a fixed bus hierarchy, and gated the
resulting bus clock to the target peripheral. RCC is therefore a supply-and-
gating peripheral rather than a data or interrupt peripheral: it does not
process application data, and its "events" are oscillator-ready transitions
rather than recurring interrupts.

Exactly one clock source drives SYSCLK at any moment. Every other clock in
the system — the core, every AHB/APB1/APB2 peripheral, the ADC, and USB — is
derived from SYSCLK by a fixed chain of integer dividers. Changing an
upstream choice (the source, or an upstream prescaler) changes every
downstream frequency that depends on it.

```text
HSI  \
HSE   >--- SYSCLK mux (SW/SWS) --- HCLK (HPRE) --- PCLK1 (PPRE1)
PLL  /                                  |
                                        +-------- PCLK2 (PPRE2) --- ADCCLK (ADCPRE)
PLL output ----------------------------------------------------- USBCLK (USBPRE)
```

### Clock sources: HSI, HSE, and PLL

**HSI** is the internal RC oscillator. It is always available immediately
after reset, requires no external components, has a nominal frequency of
8 MHz, and is factory-calibrated (`HSICAL`, read-only) with a software trim
adjustment (`HSITRIM`, 5 bits) layered on top. Its accuracy (roughly ±1%) is
worse than a crystal, which is why it is the safe reset-time default rather
than the normal high-speed choice.

**HSE** is an external clock source: either a crystal/resonator pair or a
digital clock signal. `HSEBYP` selects between those two physical
connections — clear for a crystal, set to accept a direct external clock
signal instead of driving a crystal — and only has a defined meaning while
`HSEON` is clear. `CSSON` arms the Clock Security System, which monitors HSE
for failure once it is being used (see CIR below).

**PLL** is a frequency multiplier, not an independent oscillator. It accepts
either HSI/2 (fixed) or HSE (optionally pre-divided by 2 through
`PLLXTPRE`) as its input, and multiplies that input by an integer factor of
2 through 16 (`PLLMUL`). Because the PLL's output frequency is a function of
its input selection and multiplier, both must be chosen consistently with the
target SYSCLK before the PLL is enabled.

Each source publishes an enable request bit and a separate, hardware-set
ready flag: `HSION`/`HSIRDY`, `HSEON`/`HSERDY`, `PLLON`/`PLLRDY`. Setting the
enable bit only requests that the source start; the ready flag is the
asynchronous confirmation that must be polled before the source may be
selected as SYSCLK or used to feed the PLL. This separation exists because
oscillator startup and PLL lock both take a real, variable amount of time
that software cannot skip.

**Hardware ordering rule.** `PLLSRC`, `PLLXTPRE`, and `PLLMUL` are only
software-modifiable while `PLLON` is clear. A running or already-configured
PLL must be disabled, and its ready flag observed to deassert, before any of
these three fields may be reprogrammed; the PLL must then be re-enabled and
observed ready again before SYSCLK may select it. This repository's clock-
tree orchestration (Part II) performs exactly this disable/reprogram/re-
enable sequence whenever the PLL configuration must change.

### System clock mux: SW and SWS

`CFGR.SW` is the request field: software writes one of the three source
encodings to ask the mux to switch. `CFGR.SWS` is the independent status
field: hardware sets it to reflect which source is *actually* driving SYSCLK
right now. The two fields are not the same value observed twice — `SWS` can
briefly continue reporting the previous source after `SW` has already been
written, because the mux physically settles onto the new source over a few
clock cycles. Software must poll `SWS`, not assume `SW`'s value is already
active, before relying on the new SYSCLK frequency for a subsequent
frequency-dependent operation such as raising a bus prescaler back up or
lowering Flash latency.

Selecting PLL through `SW` does not itself enable the PLL; the PLL must
already be configured, enabled, and ready, or the switch request has no safe
outcome.

### Bus prescalers: HPRE, PPRE1, PPRE2

`HPRE` divides SYSCLK to produce **HCLK** — the AHB bus clock, which also
clocks the Cortex-M3 core, the memory system, DMA, and is the sole input to
both APB prescalers. Its divider set is 1/2/4/8/16/64/128/256/512.

`PPRE1` and `PPRE2` each independently divide HCLK (not SYSCLK) to produce
**PCLK1** and **PCLK2**, the APB1 and APB2 bus clocks. Each divider set is
1/2/4/8/16.

APB1 is the device's "low-speed" bus: PCLK1 is hardware-limited to 36 MHz on
this device, so any HCLK above 36 MHz requires `PPRE1` to divide by at least
2. APB2 shares HCLK's own ceiling (up to 72 MHz) with no additional bus-
specific limit.

A peripheral's effective input clock is always its owning bus's derived
clock (HCLK, PCLK1, or PCLK2) — never SYSCLK directly, and never a clock the
peripheral chooses for itself.

### Component prescalers: ADCPRE and USBPRE

`ADCPRE` divides **PCLK2** (not HCLK, not SYSCLK) by 2/4/6/8 to produce the
ADC clock. The ADC clock is hardware-limited to 14 MHz on this device, so
`ADCPRE` must be chosen relative to whatever PCLK2 is currently configured to
be, not in isolation.

`USBPRE` divides the **PLL output** by 1 or by 1.5 to produce the USB clock,
which must equal 48 MHz to be usable. USB therefore requires SYSCLK to be
PLL-sourced, and the PLL output itself must already be either exactly 48 MHz
(select divide-by-1) or exactly 72 MHz (select divide-by-1.5); no other PLL
output yields a valid 48 MHz USB clock through either divider setting. If
SYSCLK is not PLL-sourced, the USB clock is undefined and this repository
reports it as zero.

### Flash latency/prefetch relationship to SYSCLK

Flash memory has a maximum safe read frequency lower than the core's maximum
SYSCLK. `FLASH_ACR.LATENCY` inserts wait states into every flash access so
reads remain valid at the configured SYSCLK; `FLASH_ACR.PRFTBE` enables a
prefetch buffer that hides most of that wait-state cost for sequential code
fetches. Both fields are physically owned by the Flash interface block, not
by RCC, but they exist purely to stay consistent with whatever SYSCLK RCC is
about to produce or has just produced.

This device supports three latency settings, each valid up to a maximum
SYSCLK: zero wait states up to 24 MHz, one wait state up to 48 MHz, and two
wait states above 48 MHz up to the device ceiling of 72 MHz.

**Hardware ordering rule.** Running the core from flash at a frequency the
current latency setting does not support corrupts instruction and data
fetches; there is no such hazard in the opposite direction; a wait-state
count that is *too high* for the current frequency only costs performance.
Consequently the only safe sequencing is: raise latency before raising
SYSCLK, and lower SYSCLK before lowering latency. The two operations must
never be reordered so that a raised SYSCLK executes even briefly against a
latency setting for the old, lower frequency.

### Peripheral clock-enable gating: AHBENR, APB2ENR, APB1ENR

Every non-core peripheral's clock is individually gated by one persistent,
ordinary read/write bit in one of these three registers, matching that
peripheral's owning bus. A peripheral whose gate bit is clear receives no
clock; its register bank is not guaranteed to be readable or writable in
that state.

Gating is orthogonal to bus prescaler configuration: the prescaler decides
what frequency a bus runs at, the gate decides whether one specific
peripheral on that bus receives that clock at all. These registers are
ordinary persistent state, not action ports — a bit set by one write stays
set until a later write clears it.

### Peripheral reset pulsing: APB2RSTR, APB1RSTR

Each of these registers holds one force-reset bit per peripheral on its bus.
Setting a bit holds that peripheral's register bank in reset (all its
registers read back their power-on values and the peripheral does nothing);
clearing the bit releases the reset and lets the peripheral resume normal
register behavior.

Unlike the enable registers, software normally wants a **transient action**
here — "put this peripheral back into its power-on state right now" — rather
than a persistent state. The conventional hardware idiom, and the one this
repository implements, is to set the bit and then immediately clear it in the
same operation: a reset **pulse**. Peripheral reset is independent of clock
gating in both directions: a peripheral can be held in reset while its clock
remains enabled, and releasing reset does not itself enable or disable that
peripheral's clock gate.

### Clock Security System and CIR (register layer only, outside current implemented scope)

`CR.CSSON` arms the Clock Security System, which watches HSE once it is
enabled. If HSE fails while CSS is armed, hardware autonomously disables HSE,
sets `CIR.CSSF`, raises an NMI, and — if HSE was driving SYSCLK either
directly or through the PLL — switches SYSCLK back to HSI so the core keeps
running on a known-good clock without software intervention.

`CIR` collects, for HSI/HSE/PLL ready events and the CSS event: a read-only
status flag, a read/write interrupt-enable bit (not present for CSS, which
always raises the NMI), and a write-one-to-clear bit that resets the
corresponding status flag. Writing zero to a clear bit has no effect.

This repository's register layer (`stm32f1xx_rcc.h`) documents every `CIR`
bit position and mask so the hardware model is complete, but no LL accessor
and no Driver transaction in the current RCC stack reads `CSSF`, enables any
`*RDYIE` bit, clears any `*RDYC`/`CSSC` bit, or reacts to a CSS event. An
application that needs oscillator-ready interrupts or CSS-failure handling
today must add that capability; it is not silently unsupported hardware, it
is explicitly unimplemented software.

### Register Mapping Bridge

Addresses are absolute; RCC's base is `0x40021000` and the Flash interface's
base is `0x40022000` on this device.

| Register | Owner | Address | Width | Implemented bits | Access class | Special semantics, side effects, and cross-register relationships |
| --- | --- | ---: | ---: | --- | --- | --- |
| `CR` | RCC | `0x40021000` | 32 | 0,1,3–7,16–19,24,25 | Mixed RW / RO | `HSION`/`HSEON`/`PLLON` (RW) request enable; `HSIRDY`/`HSERDY`/`PLLRDY` (RO) are hardware-set ready flags, independent of the matching enable bit; `HSITRIM` (RW) adjusts `HSICAL` (RO, factory value); `HSEBYP` (RW) only has defined meaning while `HSEON=0`; `CSSON` (RW) arms CSS against HSE; `PLLSRC`/`PLLXTPRE`/`PLLMUL` in `CFGR` are writable only while `PLLON=0` here |
| `CFGR` | RCC | `0x40021004` | 32 | 0–20,22–27 | Mixed RW / RO | `SW` (RW, request) and `SWS` (RO, status) form one request/status pair — see System clock mux above; `HPRE`/`PPRE1`/`PPRE2` (RW) are bus prescalers whose legal range depends on the resulting HCLK/PCLK1 limits; `PLLSRC`/`PLLXTPRE`/`PLLMUL` (RW) are gated by `CR.PLLON=0`; `ADCPRE` (RW) is legal only relative to the configured PCLK2; `USBPRE` (RW) is only meaningful while SYSCLK is PLL-sourced; `MCO` (RW) selects a debug clock-output source with no frequency limit enforced by hardware |
| `CIR` | RCC | `0x40021008` | 32 | 0–4,7–12,16–20,23 | Mixed RO flags / RW enables / W1C clears | `*RDYF` and `CSSF` (RO) are hardware-set status; `*RDYIE` (RW) are interrupt enables with no enable bit for CSS (always NMI); `*RDYC` and `CSSC` (W1C) clear the matching flag, writing 0 has no effect; not exercised by current LL/Driver |
| `APB2RSTR` | RCC | `0x4002100C` | 32 | 0,2–15,19–21 | RW, used as an action (force/release pulse) | Set = hold the peripheral's register bank in reset; clear = release; independent of `APB2ENR` gate state in both directions |
| `APB1RSTR` | RCC | `0x40021010` | 32 | 0–9,11,14–23,25,27–29 | RW, used as an action (force/release pulse) | Same reset semantics as `APB2RSTR`, scoped to the APB1 peripheral set |
| `AHBENR` | RCC | `0x40021014` | 32 | 0,1,2,4,6,8,10 | RW, persistent state | Clock-enable gate for DMA1/DMA2/SRAM/FLITF/CRC/FSMC/SDIO; orthogonal to `HPRE` |
| `APB2ENR` | RCC | `0x40021018` | 32 | 0,2–15,19–21 | RW, persistent state | Clock-enable gate for AFIO/GPIOA–G/ADC1–3/TIM1/TIM8/SPI1/USART1; orthogonal to `PPRE2` |
| `APB1ENR` | RCC | `0x4002101C` | 32 | 0–9,11,14–23,25,27–29 | RW, persistent state | Clock-enable gate for TIM2–7,12–14/WWDG/SPI2-3/USART2-3/UART4-5/I2C1-2/USB/CAN/BKP/PWR/DAC; orthogonal to `PPRE1` |
| `BDCR` | RCC | `0x40021020` | 32 | documented, not exercised | Mixed | Backup-domain LSE/RTC control; reset only by a separate backup-domain reset, not by system reset; outside current implemented scope |
| `CSR` | RCC | `0x40021024` | 32 | documented, not exercised | Mixed RO flags / RW / W1C (`RMVF`) | LSI enable/ready plus reset-cause flags (`PORRSTF`, `SFTRSTF`, watchdog flags, …); outside current implemented scope |
| `FLASH_ACR` | **Flash interface**, not RCC | `0x40022000` | 32 | 0–2 (`LATENCY`), 3 (`HLFCYA`, unused here), 4 (`PRFTBE`) | RW | Physically owned by the Flash block, consumed directly by RCC's clock-tree configuration because Flash wait states are a clock-tree-coupled concern; `LATENCY` must be raised before SYSCLK increases and may only be lowered after SYSCLK has already decreased |

## Part II — Implementation with Theory Bridge

### Stack and file ownership

The implementation follows the repository's Driver → Codec → LL derivation,
with Core underneath all three, matching the Timer and NVIC stacks:

```text
Application intent
      |
      v
Public operations and observations                       rcc.h
      |                    |                    |
      v                    v                    v
Configuration input   Public constants      Shared/output types
rcc_config.h -------> rcc_defines.h ------> rcc_data_types.h
      |                    |                    |
      +--------------------+--------------------+
                           |
                           v
Driver policy, validation, and sequencing                 rcc.c
                           |
             +-------------+-------------+
             |                           |
             v                           v
Pure selector/field transformation        Mechanical MMIO
rcc_codec.h / rcc_codec.c                 rcc_ll.h / rcc_ll.c
             |                           |
             +-------------+-------------+
                           |
                           v
Core register types and raw fields                        stm32f1xx_rcc.h
                           |
                           v
Repository-wide Core vocabulary
stm32f1xx_data_types.h
```

| Layer | Owns | Deliberately excludes |
| --- | --- | --- |
| Core types (`stm32f1xx_data_types.h`) | Repository-wide integer, register-image, physical-frequency, and Driver-status vocabulary | RCC-specific selectors, register fields, or policy |
| RCC data types (`rcc_data_types.h`) | Scalar RCC selector types and the read-only `rcc_clock_frequencies_t` observation shared by public RCC interfaces | Selector values, writable configuration structures, raw fields, MMIO, sequencing |
| Core register model (`stm32f1xx_rcc.h`) | `RCC_TypeDef` register union/`.BIT` layout, base address, raw `Pos`/`Msk`/selector field macros | Driver-facing selector vocabulary, validation, sequencing |
| Defines (`rcc_defines.h`) | Every public RCC selector, frequency-policy constant, and Driver-domain selector guard | Configuration structures, raw register fields, MMIO, sequencing |
| Configuration (`rcc_config.h`) | Every writable nested/root RCC descriptor | Selector definitions, observations, raw register fields, MMIO, sequencing |
| LL (`rcc_ll.h`/`rcc_ll.c`) | One generic pointer-based read/write primitive pair; named full-register `CR`/`CFGR`/`AHBENR`/`APB2ENR`/`APB1ENR`/`APB2RSTR`/`APB1RSTR` accessors built on it; single-field set/get wrappers; raw field-legality predicates | Selector-to-field translation, sequencing/timeout policy, derived-frequency math |
| Codec (`rcc_codec.h`/`rcc_codec.c`) | Pure selector⇄field encode/decode and prescaler→divider resolution over scalar values via small LUTs | Peripheral pointers, volatile I/O, hardware sequencing, public status policy |
| Driver (`rcc.h`/`rcc.c`) | Public validation, clock-tree sequencing (enable→ready→switch→confirm), root `RCC_Config()`/`RCC_ConfigClockTree()`/`RCC_ConfigFlash()` orchestration, derived-frequency cache, clock-gate Get/Set, reset-pulse | Public exposure of Codec, LL, raw register fields, or NVIC/GPIO/AFIO concerns |
| Application | Deciding which peripherals need which bus gate enabled, and when, relative to RCC and other peripheral configuration | Direct register access that bypasses Driver validation |

The `rcc_data_types.h` vocabulary layer prevents RCC-specific aliases from
leaking into the repository-wide Core type gateway. It also owns the
read-only frequency snapshot because that structure reports Driver state; it
does not request a configuration. `rcc_defines.h` builds every accepted
symbolic value and pure Driver-domain selector guard on those aliases.
`rcc_config.h` includes that vocabulary and owns only writable descriptors.
Codec consumes `rcc_defines.h` directly without depending on either the
configuration-structure layer or the public `rcc.h` Driver header.

`rcc.h` includes these three public vocabulary headers, but it does not
include `rcc_codec.h`, `rcc_ll.h`, or a Core RCC register header. The gate and
reset APIs are normal Driver functions implemented in `rcc.c`; keeping their
small forwarding bodies out of the public header prevents LL and raw Core
details from leaking transitively into application translation units.

`rcc_ll.h` includes only the RCC register model and Core base-address
vocabulary required for RCC MMIO; it does not include the repository-wide
`stm32f1xx.h` peripheral umbrella. `rcc.c` includes the Flash register model,
Flash field definitions, and base-address vocabulary directly because the
root RCC transaction owns the documented Flash-latency coupling. This keeps
unrelated peripheral register models outside the RCC include graph.

There is no `rcc_ll.c` for the register-access primitive pair or the named
full-register accessors — those are `__STATIC_FORCEINLINE` functions in
`rcc_ll.h`, matching the Timer/NVIC LL pattern. `rcc_ll.c` implements only the
system-clock/PLL/prescaler/gate/reset functions that are declared, not
inlined, in the header.

### Core C register representation

`RCC_TypeDef` models every documented register as a union of a full-width
`.REG` image and a named `.BIT` field view, with explicit `reserved_N` gaps
completing every register to 32 bits:

```c
union RCC_CR
{
	_IO REG;
	struct
	{
		_IO HSION: 1;
		_I  HSIRDY: 1;
		_I  reserved_1: 1;
		_IO HSITRIM: 5;
		_I  HSICAL: 8;
		_IO HSEON: 1;
		_I  HSERDY: 1;
		_IO HSEBYP: 1;
		_IO CSSON: 1;
		_I  reserved_2: 4;
		_IO PLLON: 1;
		_I  PLLRDY: 1;
		_I  reserved_3: 6;
	} BIT;
} CR;
```

`_IO` is `volatile uint32_t` (read/write), `_I` is `volatile const uint32_t`
(hardware-set, software read-only), and `_O` (used elsewhere in the Core
layer, not inside `RCC_TypeDef`) is the project's write-only documentation
convention. `CR`'s `.BIT` view correctly separates `_IO` enable requests from
`_I` ready flags, matching the true hardware asymmetry described in Part I.

`CFGR`'s `.BIT` view is less strict: every field, including `SWS`, is
declared `_IO` even though `SWS` is hardware read-only in the real register.
This is a structural simplification of the C bitfield layout, not a claim
about hardware behavior — the LL and Driver layers never write `SWS`
(`LL_RCC_GetSystemClockStatus()` has no matching setter), and every real
access to `CFGR` goes through `.REG`, not `.BIT`, per the next section. The
same simplification applies to `CIR`'s `.BIT` view, where the `*RDYF` status
flags, `*RDYIE` enables, and `*RDYC`/`CSSC` write-one-to-clear actions are all
declared `_IO` even though their true access classes differ; `CIR` is
outside the current implemented scope, so this has no effect on any existing
accessor today.

`.REG` is the canonical LL transaction path for every RCC register. LL's own
Doxygen states this explicitly: *"Use `.REG` through `LL_RCC_REG` for RCC
union registers. Do not use `.BIT` in the LL layer."* A `.BIT` view documents
field placement for a human reader; it does not authorize a compiler-
generated read-modify-write where the hardware or the driver's own
sequencing (PLL reprogramming, reset pulsing) requires a staged full-register
transfer.

### Generic register access primitive

Every named RCC LL accessor is built on exactly one generic pointer-based
read primitive and one write primitive:

```c
LL_RCC_REG(_REG)                       // &(((RCC_TypeDef*) RCC_BASE_ADDRESS)->_REG.REG)
LL_RCC_ReadRegister(const _IO* const pRegister)   -> reg
LL_RCC_WriteRegister(_IO* const pRegister, const reg regImage) -> void
```

`LL_RCC_ReadRegister()`/`LL_RCC_WriteRegister()` delegate to the peripheral-
independent `RegOps_Read()`/`RegOps_Write()` primitives. Every named accessor
— `LL_RCC_ReadCR()`, `LL_RCC_WriteAPB1ENR()`, and so on — is a thin wrapper
that selects the correct `.REG` pointer through `LL_RCC_REG()` and forwards
to this same primitive pair; none of them repeat direct dereference or
`RegOps_*` mechanics locally. This keeps every RCC register transfer at
exactly one call depth above the shared MMIO primitive, and keeps volatile
access width and ordering identical across all seven registers LL exposes.

### Driver-facing selector vocabulary and Codec translation

`rcc_defines.h` defines every configuration selector the Driver and Codec share as a plain
value on an RCC-owned scalar typedef — for example `RCC_SYS_CLK_HSI`,
`RCC_PLL_MUL_9`, and `RCC_APB1_DIV_2` are all `uint8_t`-backed values
(`rcc_system_clock_t`, `rcc_pll_mul_t`, `rcc_bus_prescaler_t`). These
selectors are small ordinal indices, not raw hardware field values; they
exist so the Driver's public API never asks a caller to know a `RCC_CFGR_*`
bit pattern.

`rcc_codec.c` translates between that selector vocabulary and raw hardware
fields using small static lookup tables indexed either directly by selector
value (AHB/APB1/APB2/ADC/USB prescalers) or by an offset from the selector's
first valid value (`RCC_PLL_MUL_2..16`). Two generic helpers,
`Codec_RCC_FindFieldValueMapIndex()` and
`Codec_RCC_GetFieldValueMapLLFieldByIndex()`/
`Codec_RCC_GetFieldValueMapValueByIndex()`, implement the shared
search/lookup mechanics; a linear scan is an acceptable cost because every
RCC selector table has at most sixteen rows (the PLL multiplier table).

Encode functions (`Codec_RCC_Encode*`) reject an unrecognized selector with
`DRIVER_STATUS_ERROR_INVALID_ARG` — an invalid selector must never silently
program some other field value. Decode functions (`Codec_RCC_Decode*`) and
divider-resolution functions (`Codec_RCC_Get*PrescalerDivider`) instead fall
back to a documented safe default (typically the divide-by-1 or reset-state
selector) for an unrecognized raw field, and still return
`DRIVER_STATUS_SUCCESS`. This asymmetry is intentional: an application
*requesting* an unsupported configuration is a caller error worth rejecting
before any MMIO; *observing* an unexpected raw field while decoding live
hardware state (which should never happen with a correctly functioning part)
falls back to a safe interpretation instead of turning a read-only query into
a fallible operation with no recovery path for the caller.

Every Codec function is a pure scalar transformation: no peripheral pointer,
no register image, no volatile access. This is why Codec sits identically
between the Driver and LL for both encode (Driver → field, before an LL
write) and decode (field, after an LL read → Driver) directions.

### Theory-to-implementation trace

| Theoretical intent | Core register | LL route | Codec role | Public Driver transaction |
| --- | --- | --- | --- | --- |
| Enable/disable HSI, HSE, PLL | `CR` | `LL_RCC_EnableHSI/DisableHSI`, `...HSE...`, `...PLL...` (read‑modify‑write `.REG`) | None; bit masks are exact | `RCC_SetSystemClockSource()` / `RCC_ConfigClockTree()` sequence enable → wait‑ready internally |
| Observe source ready | `CR` | `LL_RCC_GetHSIReadyStatus/GetHSEReadyStatus/GetPLLReadyStatus()` | None; Driver tests the returned `driver_status_t` | `_RCC_WaitForClockSourceReady()` polls with a bounded timeout |
| Select SYSCLK source | `CFGR.SW` | `LL_RCC_SetSystemClockSource(field)` validates the raw field, then read‑modify‑writes `.REG` | `Codec_RCC_EncodeSystemClockSource()` selector → field | `RCC_SetSystemClockSource()` enables/validates the source, writes `SW`, then confirms `SWS` |
| Observe active SYSCLK source | `CFGR.SWS` | `LL_RCC_GetSystemClockStatus()` | `Codec_RCC_DecodeSystemClockSource()` field → selector | `RCC_GetSystemClockSource()` |
| Program PLL source/divider/multiplier | `CFGR.PLLSRC/PLLXTPRE/PLLMUL` | `LL_RCC_SetPLLSource/SetPLLHSEDivider/SetPLLMultiplier()` | `Codec_RCC_EncodePLLSource/EncodePLLHSEDivider/EncodePLLMultiplier()` | `RCC_ConfigClockTree()` disables PLL first, programs all three fields, then re‑enables and waits ready |
| Observe PLL configuration | `CFGR.PLLSRC/PLLXTPRE/PLLMUL` | `LL_RCC_GetPLLSource/GetPLLHSEDivider/GetPLLMultiplier()` | None (Driver decodes with local `switch`/comparison, not a Codec decode helper — see note below) | `RCC_GetPLLSource()` / `RCC_GetPLLSourcePrescaler()` / `RCC_GetPLLMultiplier()` |
| Program bus prescalers | `CFGR.HPRE/PPRE1/PPRE2` | `LL_RCC_SetAHBPrescaler/SetAPB1Prescaler/SetAPB2Prescaler()` | `Codec_RCC_EncodeAHBPrescaler/EncodeAPB1Prescaler/EncodeAPB2Prescaler()` | `RCC_ConfigBusPrescalers()`; also invoked internally by `_RCC_ApplyBusPrescalerConfig()` from `RCC_ConfigClockTree()` |
| Observe bus prescalers | `CFGR.HPRE/PPRE1/PPRE2` | `LL_RCC_GetAHBPrescaler/GetAPB1Prescaler/GetAPB2Prescaler()` | `Codec_RCC_DecodeAHBPrescaler/DecodeAPB1Prescaler/DecodeAPB2Prescaler()` | `RCC_GetBusPrescaler(bus)` |
| Program component prescalers | `CFGR.ADCPRE/USBPRE` | `LL_RCC_SetADCPrescaler/SetUSBPrescaler()` | `Codec_RCC_EncodeADCPrescaler/EncodeUSBPrescaler()` | `RCC_ConfigComponentPrescalers()` |
| Observe/resolve derived frequencies | `CFGR` (all prescaler fields) | Get* accessors above | `Codec_RCC_Get{AHB,APB,ADC}PrescalerDivider()` selector → numeric divider | `RCC_GetBusFrequency()`, `RCC_GetCoreClockFrequency()`, `RCC_GetClockFrequencies()` |
| Enable/disable a peripheral clock gate | `AHBENR`/`APB2ENR`/`APB1ENR` | `LL_RCC_Enable*Clock/Disable*Clock(mask)` (read‑modify‑write `.REG`) | None; Driver validates the bus capability and routes the caller's exact `RCC_*ENR_*EN` mask | `RCC_SetPeripheralClockState(bus, mask, state)` |
| Observe a peripheral clock gate | `AHBENR`/`APB2ENR`/`APB1ENR` | `LL_RCC_ReadAHBENR/ReadAPB2ENR/ReadAPB1ENR()` | None; Driver selects one register and tests `(regImage & mask) == mask` | `RCC_GetPeripheralClockState(bus, mask)` |
| Force/release/pulse a peripheral reset | `APB2RSTR`/`APB1RSTR` | `LL_RCC_Force*Reset/Release*Reset/Pulse*Reset(mask)` | None; Driver rejects AHB and routes the caller's exact `RCC_*RSTR_*RST` mask | `RCC_PulsePeripheralReset(bus, mask)` |
| Apply Flash latency/prefetch | `FLASH_ACR` (Flash block, not RCC) | none (direct `REGOPS_MODIFY`/`REGOPS_SET`/`REGOPS_CLEAR` on `FLASH->ACR.REG`, bypassing `rcc_ll.h`) | None | `RCC_ConfigFlash()` |
| Apply a complete clock‑tree change | `CR`, `CFGR` | every System Clock/Prescaler LL function above, in sequence | every Codec encode function above | `RCC_ConfigClockTree()` |
| Apply Flash + clock tree together, correctly ordered | `FLASH_ACR`, `CR`, `CFGR` | (delegates to the two rows above) | (delegates to the rows above) | `RCC_Config()` |

**Note on PLL observation.** Unlike every other Get/Set pair, the three PLL
observation getters (`RCC_GetPLLSource()`, `RCC_GetPLLSourcePrescaler()`,
`RCC_GetPLLMultiplier()`) decode the raw LL field with a local `switch` or
direct comparison inside `rcc.c` instead of calling a `Codec_RCC_Decode*`
function. `rcc_codec.h` only declares PLL *encode* functions
(`Codec_RCC_EncodePLLSource/EncodePLLHSEDivider/EncodePLLMultiplier`), not
matching decoders — this is an existing asymmetry between the PLL codec
surface and the bus/component prescaler codec surface, which does provide
both directions. It does not affect correctness (the Driver's local decoding
matches the same field encodings LL validates), but it means PLL decode logic
is duplicated in `rcc.c` rather than centralized in Codec the way prescaler
decode logic is.

### Why some hardware directions have no LL or Driver function

The implemented surface reflects admitted Driver transactions, not every
hardware direction that physically exists:

- There is no LL or Driver function for any `CIR` bit (ready interrupts, CSS
  flag/clear). CSS and oscillator-ready interrupts are documented hardware
  but unimplemented software, as stated in Part I.
- There is no LL or Driver function for `BDCR` or `CSR`. LSE, RTC, the
  backup domain, LSI, and reset-cause reporting are outside current scope.
- There is no `LL_RCC_SetSystemClockStatus()`. `SWS` is hardware read-only;
  only `LL_RCC_GetSystemClockStatus()` exists, matching the true direction
  even though the Core `.BIT` view declares the field `_IO`.
- `LL_RCC_EnableHSEBypass()`/`LL_RCC_DisableHSEBypass()` exist in
  `rcc_ll.h`, but `rcc.h` exposes no public Driver-level HSE-bypass Get/Set.
  HSE bypass is therefore reachable today only by code that includes the LL
  header directly; no admitted public transaction currently owns it.
- There is no LL or Driver function for `CFGR.MCO`. The clock-output mux is
  defined at the Core register layer (raw `RCC_CFGR_MCO_*` field macros) but
  has no LL accessor and no Driver transaction.
- `RCC_ConfigFlash()` writes `FLASH->ACR` directly through `REGOPS_MODIFY()`/
  `REGOPS_SET()`/`REGOPS_CLEAR()` instead of through an `rcc_ll.h` accessor,
  because `FLASH_ACR` is owned by the Flash interface block, not by RCC —
  consistent with the repository rule that raw register-field macros and
  their access live with the physical register owner even when a peer
  Driver (RCC, here) is the one that must program them.

### Clock-tree sequencing: `RCC_ConfigClockTree()`

Reconfiguring the clock tree safely requires a specific order because the
PLL cannot be reprogrammed while active, HSI is the only source guaranteed
already stable, and the currently active source must never be switched away
from without an already-ready replacement:

```text
Read the currently active SYSCLK source
        ↓
Enable HSI and wait ready (HSI is the universal safe harbor)
        ↓
If PLL is currently the active source, switch SYSCLK to HSI first
        ↓
If the target needs HSE (directly, or as the PLL input), enable HSE and wait ready
        ↓
If the PLL is currently enabled, disable it and wait for PLLRDY to clear
        ↓
Apply the requested AHB/APB1/APB2 bus prescalers
        ↓
Apply the requested ADC/USB component prescalers
        ↓
If the target source is PLL: encode and program PLLSRC/PLLXTPRE/PLLMUL,
enable the PLL, and wait ready
        ↓
Switch SYSCLK to the target source and wait for SWS to confirm
        ↓
Refresh the cached derived-frequency snapshot
```

This mirrors the Part I hardware ordering rule directly: the PLL is always
brought to a fully disabled, ready-deasserted state before any of its three
configuration fields change, and it is always fully re-armed and observed
ready before SYSCLK is asked to select it.

### Root configuration ordering: `RCC_Config()`

`RCC_Config()` is the root transaction over `rcc_config_t`, which bundles
`rcc_flash_config_t` and `rcc_clock_tree_config_t`. It validates the whole
request (`RCC_ValidateConfig()`), computes both the *current* hardware
frequency snapshot and the *target* frequency snapshot the requested
configuration would produce, and then orders the two domain transactions
based on whether SYSCLK is increasing or decreasing:

```text
target SYSCLK > current SYSCLK:
    RCC_ConfigFlash()        -- raise latency first
    RCC_ConfigClockTree()    -- then raise the clock

target SYSCLK <= current SYSCLK:
    RCC_ConfigClockTree()    -- lower the clock first
    RCC_ConfigFlash()        -- then relax latency
```

This directly implements the Flash latency/prefetch ordering rule from
Part I: the core never executes from flash at a frequency the currently
programmed `LATENCY` value does not support, in either direction of change.

`RCC_ValidateConfig()` performs four checks in order before any hardware is
touched: complete Flash-policy validity (`_RCC_ValidateFlashConfig()`),
field-level clock-tree validity (`_RCC_ValidateClockTreeConfig()`, which
Codec-encodes every selector and rejects the whole request if any one fails
to encode, plus a PLL-specific consistency check), derived-frequency limit
validity (`_RCC_ValidateClockFrequencies()`, comparing the same
`_RCC_LoadClockFrequenciesFromConfig()` computation used for sequencing
against `RCC_SYSCLK_MAX_FREQ`/`RCC_HCLK_MAX_FREQ`/`RCC_PCLK1_MAX_FREQ`/
`RCC_PCLK2_MAX_FREQ`/`RCC_ADCCLK_MAX_FREQ`), and inter-parameter dependency
validity (`_RCC_ValidateClockConfigDependencies()`, which enforces the exact
48 MHz USB-clock constraint and the three Flash-latency/SYSCLK bands from
Part I).

The domain entry points preserve the same validation-before-mutation rule
when called independently. `RCC_ConfigFlash()` validates both Flash members
before its first `FLASH_ACR` write, and `RCC_ConfigClockTree()` validates the
entire clock-tree descriptor before enabling, disabling, reprogramming, or
switching any clock source. A later hardware-ready timeout can leave the
system in a documented safe intermediate state, but invalid input cannot
cause a partial transaction.

`RCC_Config72MHz()` is a narrowly named, fixed-configuration bootstrap
helper: `RCC_Load72MHzDefaultConfig()` populates the documented Blue Pill
72 MHz preset (HSE → PLL ×9, AHB ÷1, APB1 ÷2, APB2 ÷1, ADC ÷6, USB ÷1.5,
Flash latency 2 with prefetch enabled) and `RCC_Config72MHz()` delegates
to `RCC_Config()` only after the preset loader reports success. The loader
returns `DRIVER_STATUS_ERROR_NULL_PTR` instead of silently ignoring a missing
destination. Neither helper accepts an arbitrary target frequency or
duplicates `RCC_Config()`'s orchestration, matching the repository rule
against general-purpose frequency-setter convenience functions.

### Derived-frequency computation and caching

Every derived frequency ultimately follows the same chain from Part I:
SYSCLK → HCLK (÷ HPRE) → PCLK1/PCLK2 (÷ PPRE1/PPRE2) → ADCCLK (÷ ADCPRE from
PCLK2); USBCLK is computed independently, directly from the PLL output and
`USBPRE`, and only while SYSCLK is PLL-sourced. This repository implements
that chain twice, deliberately kept structurally identical:

- `_RCC_LoadClockFrequenciesFromConfig()` computes what a *not-yet-applied*
  `rcc_clock_tree_config_t` would produce, purely from Codec divider
  resolution and the fixed `RCC_HSI_FREQ`/`RCC_HSE_FREQ` constants — no MMIO.
  Used by `RCC_ValidateConfig()` for pre-flight limit checking and by
  `RCC_Config()` to compare target-versus-current SYSCLK for latency
  ordering.
- `_RCC_LoadClockFrequenciesFromHardware()` computes the *actual current*
  frequencies by reading every relevant LL field from live hardware. Used to
  build and refresh the cache.

`RCC_GetClockFrequencies()` publishes a cached `rcc_clock_frequencies_t`
snapshot (`_rccClockFrequenciesSnapshot`, file-static in `rcc.c`) rather than
re-reading hardware on every call. The cache is refreshed after every
Driver operation that can change a derived frequency
(`RCC_SetSystemClockSource()`, `RCC_ConfigClockTree()`,
`RCC_ConfigBusPrescalers()`, `RCC_ConfigComponentPrescalers()`, and
transitively `RCC_Config()`), and is also lazily rebuilt on first read if it
is still all-zero — `RCC_FREQ_ZERO` doubles as "not yet populated" for
`sysclk` specifically, since a real system can never legitimately run at
0 Hz SYSCLK. `RCC_GetCoreClockFrequency()` and `RCC_GetBusFrequency()` are
both thin readers of this same cache; they do not perform their own MMIO.
The bus getter admits only the physical AHB, APB1, and APB2 domains. ADC and
USB are component-derived clocks, so callers retrieve `adcclk` and `usbclk`
from the coherent `RCC_GetClockFrequencies()` snapshot instead of pretending
those components are physical buses.

Every hertz-valued field in `rcc_clock_frequencies_t`, and every RCC
frequency constant (`RCC_HSI_FREQ`, `RCC_SYSCLK_MAX_FREQ`, …), uses the
Core-owned `frequency_t` alias rather than a peripheral-specific type, per
the repository-wide rule that all hertz-valued quantities share one type.

### Clock-gate and reset ownership boundary

`RCC_SetPeripheralClockState()` and its
`RCC_GetPeripheralClockState()` conjugate are the *only* public operations
through which a peripheral clock gate may be enabled, disabled, or observed.
The caller supplies `RCC_AHB_BUS`, `RCC_APB1_BUS`, or `RCC_APB2_BUS` so the
Driver can route one stable intent to the matching register-specific LL path.
Other peripheral Drivers (Timer, GPIO, and so on) call these RCC functions —
or query them to validate a precondition — but never expose a duplicate
peripheral-prefixed clock API, and never mutate a gate from inside their own
`Config()`/`DeConfig()`/operation-state APIs.

`RCC_PulsePeripheralReset()` is the corresponding action service that a
peripheral's `DeConfig()` may call when hardware-defined reset is the
documented restoration mechanism. It accepts APB1 or APB2, rejects AHB because
STM32F1 RCC exposes no matching AHB peripheral-reset register, and leaves the
peripheral's clock gate and NVIC delivery state untouched — the same lifecycle
boundary the Timer stack documents for its own `DeConfig()`.

The gate and reset functions are implemented in `rcc.c`, not inline in
`rcc.h`. This costs one ordinary Driver call at the application boundary but
keeps `rcc_ll.h`, Core registers, and raw field vocabulary out of the public
include chain. Each implementation still delegates to exactly one matching
LL operation, so register ownership remains singular.

### Concurrency and ownership rules

- `RCC_ConfigClockTree()` and `RCC_Config()` are single-owner, platform-
  initialization-style operations. Nothing in the Driver layer arbitrates a
  concurrent clock-tree change against a concurrent frequency read; a caller
  that needs that guarantee must supply its own external serialization.
- The derived-frequency cache is a plain file-static structure, refreshed
  synchronously at the end of every clock-changing transaction; it is not
  synchronized against concurrent readers on its own.
- `_RCC_WaitForClockSourceReady()` and `_RCC_WaitForSystemClockSwitch()` use
  a fixed, non-time-calibrated busy-wait budget (`RCC_READY_TIMEOUT`, 1000
  polling iterations); they bound worst-case blocking but do not correspond
  to a calibrated wall-clock duration.
- Clock-gate mutation and reset pulsing remain RCC/application-owned, never
  hidden inside a peripheral Driver's lifecycle APIs, as described above.

### Hardware and project authorities

Hardware behavior is governed by the STM32F10xxx reference manual (RM0008)
chapter on Reset and Clock Control. The repository maps that behavior
through:

- `BareMetal/Core/Inc/stm32f1xx_rcc.h`
- `BareMetal/Core/Inc/stm32f1xx_base_address.h`
- `BareMetal/Core/Inc/stm32f1xx_defines.h` (Flash `ACR` field macros)
- `BareMetal/Driver/RCC/Inc/rcc_data_types.h`
- `BareMetal/Driver/RCC/Inc/rcc_config.h`
- `BareMetal/Driver/RCC/Inc/rcc_defines.h`
- `BareMetal/Driver/RCC/Inc/rcc_ll.h`
- `BareMetal/Driver/RCC/Src/rcc_ll.c`
- `BareMetal/Driver/RCC/Inc/rcc_codec.h`
- `BareMetal/Driver/RCC/Src/rcc_codec.c`
- `BareMetal/Driver/RCC/Inc/rcc.h`
- `BareMetal/Driver/RCC/Src/rcc.c`

The Core headers are C mappings, not independent hardware specifications.
The reference manual remains authoritative when a source comment and
documented processor behavior disagree.
