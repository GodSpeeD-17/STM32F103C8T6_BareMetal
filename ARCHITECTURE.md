# Bare-Metal Driver Architecture

This document defines the intended architecture for reusable peripheral drivers
in this repository. It is meant to be session independent: a future development
session should be able to read this file and understand the layer boundaries,
authority rules, optimization policy, and commit discipline without relying on
prior conversation history.

The architecture is intentionally learning-focused. It is not a direct clone of
vendor HAL, and it is not a single all-powerful low-level layer. Each layer owns
one kind of knowledge.

## Goals

- Keep raw MCU register definitions close to the reference manual.
- Keep public driver vocabulary separate from register access.
- Keep low-level layers as dumb register access points.
- Keep semantic translation, raw field placement, and staged register-image
  mutation in codec layers.
- Let public driver APIs own validation, sequencing, and batching decisions.
- Make application code depend on stable public APIs, not driver internals.
- Optimize repeated register access where it matters without hiding ownership.
- Keep public API names precise enough that users know which hardware state is
  being changed.

## Repository Layers

| Layer | Owns | Must Avoid |
|-------|------|------------|
| Core | MCU register structs, base addresses, raw peripheral constants, shared scalar aliases, generic bit/register utilities | Peripheral driver policy, public driver selectors, application behavior |
| Driver Data Types | Driver-facing scalar typedef aliases and plain shared data aliases | Public selector macros, validation policy, register access, hardware writes, sequencing |
| Driver Defines/Validation | Public selector macros and pure validation/policy macros shared within one driver family | Register access, hardware writes, sequencing, raw register field placement |
| Low-Level | Named static inline register read/write accessors and minimal register-address macros | Public selector translation, raw field placement, compatibility policy, batching policy, clock policy, board behavior |
| Codec | Translation between driver selectors and raw hardware fields, raw field placement, encode/decode logic, mutation of caller-owned staged register images | Hardware reads/writes, clock sequencing, public API decisions |
| Driver | Public API, argument validation, selector compatibility, clock sequencing, batching, dirty-register write decisions, user-facing status | Raw register map definitions, board-specific behavior |
| Project | Board/application behavior and examples | Driver internals |

## Core Layer

Core files live under `BareMetal/Core`.

Core is the hardware description base. It should define:

- register maps and base addresses
- raw bit masks taken from the reference manual
- device-level constants
- generic bit helpers
- generic register access helpers
- startup, linker, and system-level support

Core must not know that a driver later calls a field "mode", "config", "state",
or any other public API concept. It should stay hardware-shaped.

Raw bit-position and field-width values should use the shared scalar aliases
when available, for example `reg_bit_pos_t` and `reg_field_width_t`. Raw field
values and masks should use `reg` or `reg_field_t` consistently with the
existing Core helpers.

## Driver Data Types And Defines Layers

Each driver may split shared vocabulary across a data-types header and a
defines/validation header.

A data-types header, for example `<driver>_data_types.h`, owns only:

- driver-facing scalar aliases
- plain data aliases that genuinely need to be shared across layers

It must avoid public selector macros, validation policy, hardware register
types, and full MCU include coupling.

A defines/validation header, for example `<driver>_defines.h`, owns:

- public selector constants and selector macros
- pure validation macros/helpers that guard the same public vocabulary
- simple conversions that do not require register access

Use the full word `defines` in filenames, not the abbreviation `defs`. For
example, prefer `gpio_defines.h`, `rcc_defines.h`, and
`usart_defines.h`.

This defines layer is shared by the public driver, codec layer, and any
related drivers that need the same vocabulary. It must stay independent of
hardware reads/writes and sequencing.

Macro syntax alone does not decide ownership. A selector macro belongs in the
defines layer, a validation macro belongs in the defines/validation layer, and
raw field-placement knowledge belongs in the codec layer unless it is a direct
register-map fact already owned by Core.

Public configuration/request structures belong in the public driver layer unless
there is a specific reason for another layer or related driver to depend on that
structure as plain shared data.

For complex peripherals, prefer public configuration structures over long
argument lists. The root configuration structure should group related
substructures, for example `driver_config_t` containing
`driver_config_<group>_t` members. Keep peripheral instance pointers out of
reusable configuration objects so the same configuration can be applied to more
than one instance.

## Low-Level Layer

Each driver may have a low-level layer, for example `<driver>_ll.h/.c`.

The low-level layer owns hardware-near register access:

- named static inline readers for full peripheral register images
- named static inline writers for full peripheral register images
- minimal register-address macros when C token selection requires them

The low-level layer should stay intentionally dumb. It should not know how a
pin index maps to a field shift, which register image a public request touches,
or how a public selector maps to raw hardware bits.

The low-level layer must not know public semantic selectors or policy. It should
not translate public driver states into behavior, decide batching strategy, or
validate full public API requests. It should not enable, disable, or verify
clocks unless the module itself is the clock controller driver.

LL should be the single direct access point for peripheral register reads and
writes. Higher layers should call LL accessors instead of directly touching
peripheral registers.

Good low-level responsibilities:

```c
LL_DRIVER_ReadRegisterA(PERIPHx);
LL_DRIVER_WriteRegisterA(PERIPHx, regImage);
```

Bad low-level responsibilities:

```c
LL_DRIVER_ValidatePublicConfig(config);
LL_DRIVER_TranslatePublicModeToRawMode(mode);
LL_DRIVER_GetFieldShift(rawIndex);
LL_DRIVER_SetRawField(regImage, fieldShift, rawField);
LL_DRIVER_DecideWhichRegistersToRead(selectorMask);
LL_DRIVER_EnableClockBecausePublicModeNeedsIt(mode);
LL_DRIVER_SetClockState(PERIPHx, state);
```

Those belong above LL.

## Codec Layer

Each driver may have a codec layer, for example `<driver>_codec.h/.c`.

The codec layer owns translation and staged image mutation:

- encode public selectors into raw hardware fields
- decode raw hardware fields into public selectors
- select the relevant staged register image for a decoded raw index when that
  selection depends on field layout
- calculate field shifts, masks, and raw field placement inside caller-owned
  register images
- update caller-owned register images
- stage reset/default register images
- stage related side effects that are still image-based, not hardware writes

Private codec helpers should use Encode/Decode naming for translation and raw
field mapping. Public codec APIs should use Extract/Stage naming:

- `Extract*()` reads a caller-owned register image and returns a driver-facing
  value.
- `Stage*()` mutates a caller-owned register image and prepares it for a later
  driver-layer write.

Declare and implement Extract APIs before their conjugate Stage APIs inside
each logical group.

Codec functions may validate translation inputs. Functions that can fail should
return `driver_status_t`. Functions that only compute a raw register value,
position, mask, or field may return `reg`, `reg_field_t`, or another shared
Core scalar alias such as `reg_bit_pos_t`.

Codec APIs must be designed as conjugate symmetric pairs where the underlying
hardware image is mutable. Every `Stage*()` API that writes a driver-facing
value into a caller-owned register image should have a matching `Extract*()`
API that recovers the same driver-facing value from a caller-owned register
image. Extraction-only APIs are valid when the target register is naturally
read-only or not meaningful to stage, such as sampled input-state registers.

The codec layer must not touch hardware. It receives register images from the
driver, mutates those images, and returns status.

Stage APIs should take a pointer to the caller-owned register image. The
function should copy that image into a local variable, perform all validation
and staging on the local variable, and update the caller-owned image only after
the operation is valid. This avoids partially mutated images on validation
failure.

State extraction is a special case. When the only decoded value is an ON/OFF
state and no output pointer is otherwise needed, the Extract API may return
`driver_status_t` directly as the decoded state:

- `DRIVER_STATUS_OFF`
- `DRIVER_STATUS_ON`
- an error status only when validation can fail

Non-state extraction APIs should return operation status and write the decoded
value through an output pointer.

The codec layer is the central compatibility point between stable public driver
selectors and raw hardware bit definitions. Public driver selectors may remain
unchanged even if the lower hardware bit definitions change; only the codec
mapping should need to adapt.

Good codec responsibilities:

```c
DRIVER_Codec_EncodeSelector(selector, &rawField);
DRIVER_Codec_DecodeField(rawField, &selector);
DRIVER_Codec_GetFieldShift(rawIndex);
DRIVER_Codec_ExtractField(regImage, &selector);
DRIVER_Codec_StageField(selector, &regImage);
DRIVER_Codec_StageReset(rawIndex, &regImage);
```

Bad codec responsibilities:

```c
LL_DRIVER_READ_REG(...);
LL_DRIVER_WRITE_REG(...);
LL_DRIVER_EnableClockMask(...);
```

## Driver Layer

The public driver layer owns the user-facing API and the policy around it.

It must own:

- public configuration and request structures
- public argument validation
- compatibility checks between public selectors
- clock sequencing or clock-state verification according to API ownership
- deciding which registers must be read
- batching selected fields or pins
- dirty-register tracking
- writing each dirty register at the correct time
- returning user-facing `driver_status_t`

Public functions should do what their names say and no more. A narrow API such
as `GetPrescaler()`, `SetMode()`, or `SetDirection()` should not silently enable
an unrelated clock gate or start a peripheral. If a register cannot be accessed
until a clock is enabled, the narrow API should verify the required state and
return `DRIVER_STATUS_ERROR_STATE` when a required peripheral
clock gate is disabled.

Clock and operation state should be explicit public concepts when both exist:

- `GetClockState()` / `SetClockState()` owns peripheral clock-gate state.
- `GetOperationState()` / `SetOperationState()` owns peripheral runtime enable
  state such as a counter-enable, transmitter-enable, or receiver-enable bit.

Full lifecycle APIs such as `Config()` and `DeConfig()` may orchestrate clock
state and operation state internally because their names describe a broader
operation. Even then, they should only touch the state needed for their stated
scope.

Driver APIs should also preserve conjugate intent. Prefer status-returning
`Get*()` APIs as the primary extraction path and `Set*()` APIs as the primary
mutation path. Value-returning getters may exist as convenience wrappers, but
driver code that needs to preserve existing state before a mutation should call
the status-returning getter so decode or validation failures are not hidden by
fallback values.

The intended optimized pattern for multi-field configuration is:

```c
validate_public_request(...);
verify_or_enable_required_clocks_for_this_api(...);

if (request touches register A) {
    regAImage = LL_DRIVER_ReadRegisterA(...);
}
if (request touches register B) {
    regBImage = LL_DRIVER_ReadRegisterB(...);
}

for each selected element {
    DRIVER_Codec_StageElementConfig(..., &relevantRegImage);
    mark_relevant_register_dirty();
}

if (register A dirty) {
    LL_DRIVER_WriteRegisterA(..., regAImage);
}
if (register B dirty) {
    LL_DRIVER_WriteRegisterB(..., regBImage);
}
```

This keeps optimization in the layer that understands the full operation, while
keeping low-level register primitives reusable.

## Project/Application Layer

Project code should normally call public driver APIs.

Direct LL access is allowed only when the caller intentionally accepts all raw
responsibility:

- valid peripheral instance
- valid raw fields, masks, or indices expected by the LL API being called
- clock already enabled
- register side effects understood
- no public driver policy applied

Examples should prefer public APIs unless the example is explicitly teaching raw
register or LL behavior.

## Optimization Policy

Do not optimize by pushing policy down into LL.

Optimize by putting batching in the driver layer:

- read each touched register once
- mutate local images through codec functions
- write each dirty register once
- keep semantic configuration flows in staged read-modify-write form, so
  single-pin and multi-pin setup paths share the same local-image model
- use hardware action registers for public output set/reset operations when the
  peripheral provides them, and reserve output latch read-modify-write for
  operations such as toggle that must observe the existing latch state

Initialization code is usually not a hot path, but this repository intentionally
uses it to learn where optimization belongs architecturally.

## Coding Style Policy

Use tabs for indentation in C source and header files.

Use include guards in the established uppercase file-name style:

```c
#ifndef DRIVER_CONFIG_H_
#define DRIVER_CONFIG_H_
...
#endif /* DRIVER_CONFIG_H_ */
```

Use the established banner style for major sections:

```c
// ==================================================================================================== //
```

Keep one-argument function declarations, function definitions, and function-like
macro calls on one line:

```c
driver_status_t DRIVER_DeConfig(DRIVER_TypeDef* const DRIVERx);
ASSERT_DRIVER_STATUS(DRIVER_ValidateInstance(DRIVERx));
```

Use the multiline parenthesized layout for functions or function-like macro
calls with multiple arguments, or when a single line would become hard to read:

```c
driver_status_t DRIVER_SetField
(
	DRIVER_TypeDef* const		DRIVERx,
	const driver_field_t			field
);
```

Order public APIs so read/reset style operations appear before write/apply
operations inside the same logical group:

- `DeConfig()` before `Config()`
- `Get*()` before `Set*()`
- `Extract*()` before `Stage*()`

Local helper functions should earn their existence. Do not add a wrapper that
only renames another helper without adding validation, ownership isolation,
shared policy, or readability around a genuinely repeated operation.

## Doxygen and Naming Policy

Documentation should describe authority and return meaning clearly.

Every public header and source file should have a file-level Doxygen block.
Every public API, codec-visible API, non-trivial local helper, public typedef,
configuration member, and public macro should have Doxygen.

Use `@brief` for the short behavior or hardware meaning. Use `@details` when
the function has sequencing, ownership, side effects, or non-obvious hardware
behavior.

Use `@returns` for what the return value represents.

Use `@retval - ...` for specific return cases.

Use `@ref` with backticks for project symbols:

```c
@retval - @ref `DRIVER_STATUS_SUCCESS`: Operation completed successfully.
```

Document accepted input values for public and codec-visible parameters in the
same style as return values:

```c
 * @param[in] state Requested state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Disable the state.
 * - @ref `DRIVER_STATUS_ON`: Enable the state.
```

Document expected output values for public and codec-visible output parameters
using the same style. Use `Accepted values` for caller-provided inputs and
`Expected values` for values the function writes back to the caller:

```c
 * @param[out] pState Destination for decoded state
 * Expected values:
 * - @ref `DRIVER_STATUS_OFF`: Decoded state is disabled.
 * - @ref `DRIVER_STATUS_ON`: Decoded state is enabled.
```

For output configuration structures, document expected member values with
`Expected member values`. For input configuration structures, document accepted
member values with `Accepted values`.

For bit and field macro Doxygen, the `@brief` should explain what the hardware
bit or field means, not only repeat the register and bit name.

Names should reveal ownership and intent:

- Low-level names should use `LL_<Module>_<Action>` so IntelliSense groups all
  low-level operations together.
- Avoid adding new low-level names in the legacy `<Module>_LL_<Action>` shape
  and migrate call sites directly when normalizing old code.
- `LL` names should sound raw and hardware-near.
- `Codec` names should sound like translation, encoding, decoding, or staging.
- `Driver` names should sound like public operations.

Avoid names that hide policy or mix layer authority.

Use names that preserve important hardware notation. For STM32-style channel
fields, keep the lowercase `x` in names such as `CCxS`, `OCxM`, `ICxPSC`, and
`ICxF`.

## Commit Discipline

Normalize one layer per commit.

Recommended order for a driver normalization:

1. Data aliases, selector defines, and validation vocabulary.
2. LL raw register access and naming.
3. Codec translation, hardware field placement, and staging.
4. Driver orchestration and batching.
5. Project/application compatibility cleanup.

Each commit should leave the touched layer internally coherent before moving to
the next layer.

## Driver-Specific Notes

Driver-specific architecture notes may be added later when a driver needs extra
context. Those notes should point back to this document and explain only the
driver-specific interpretation or exception.
