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
- Let low-level layers expose hardware-layout primitives without absorbing
  driver policy.
- Keep semantic translation and staged register-image mutation in helper layers.
- Let public driver APIs own validation, sequencing, and batching decisions.
- Make application code depend on stable public APIs, not driver internals.
- Optimize repeated register access where it matters without hiding ownership.

## Repository Layers

| Layer | Owns | Must Avoid |
|-------|------|------------|
| Core | MCU register structs, base addresses, raw peripheral constants, shared scalar aliases, generic bit/register utilities | Peripheral driver policy, public driver selectors, application behavior |
| Driver Types | Public selector vocabulary, driver-facing scalar types, validation macros/helpers shared within one driver family | Register access, hardware writes, sequencing |
| Low-Level | Direct register access, raw peripheral operations, clock-gate forwarding when needed, raw hardware-layout helpers such as field offsets and masks | Public selector translation, compatibility policy, batching policy, board behavior |
| Helper | Translation between driver selectors and raw hardware fields, encode/decode logic, mutation of caller-owned staged register images | Hardware reads/writes, clock sequencing, public API decisions |
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

## Driver Types Layer

Each driver may have a shared types header, for example `<driver>_types.h`.

This layer owns:

- public selector constants
- public data structures
- driver-facing scalar aliases
- validation macros/helpers that do not touch hardware
- simple conversions that do not require register access

This layer is shared by the public driver, helper layer, and any related drivers
that need the same vocabulary.

This layer must stay independent of low-level register access.

## Low-Level Layer

Each driver may have a low-level layer, for example `<driver>_ll.h/.c`.

The low-level layer owns hardware-near operations:

- direct read/write/set/clear/modify wrappers for peripheral registers
- raw operations that map closely to one register action
- raw clock-gate forwarding when the peripheral driver needs it
- hardware-layout primitives such as register field offsets, masks, and raw
  field placement

The low-level layer may know bit positions because bit position is hardware
layout knowledge. It may expose helpers that operate on raw register images and
raw hardware fields.

The low-level layer must not know public semantic selectors or policy. It should
not translate public driver states into behavior, decide batching strategy, or
validate full public API requests.

Good low-level responsibilities:

```c
DRIVER_LL_ReadReg(PERIPHx, reg);
DRIVER_LL_WriteReg(PERIPHx, reg, value);
DRIVER_LL_SetRawMask(PERIPHx, mask);
DRIVER_LL_GetFieldShift(rawIndex);
DRIVER_LL_GetFieldMask(fieldShift);
DRIVER_LL_SetRawField(regImage, fieldShift, rawField);
```

Bad low-level responsibilities:

```c
DRIVER_LL_ValidatePublicConfig(config);
DRIVER_LL_TranslatePublicModeToRawMode(mode);
DRIVER_LL_DecideWhichRegistersToRead(selectorMask);
DRIVER_LL_EnableClockBecausePublicModeNeedsIt(mode);
```

Those belong above LL.

## Helper Layer

Each driver may have a helper layer, for example `<driver>_helper.h/.c`.

The helper layer owns translation and staged image mutation:

- encode public selectors into raw hardware fields
- decode raw hardware fields into public selectors
- update caller-owned register images
- stage reset/default register images
- stage related side effects that are still image-based, not hardware writes

Helper functions may validate translation inputs and return `driver_status_t`.
Any helper function that performs internal validation should return
`driver_status_t`.

The helper layer must not touch hardware. It receives register images from the
driver, mutates those images, and returns status.

Good helper responsibilities:

```c
DRIVER_Helper_EncodeSelector(selector, &rawField);
DRIVER_Helper_DecodeField(rawField, &selector);
DRIVER_Helper_StageField(selector, &regImage);
DRIVER_Helper_StageReset(rawIndex, &regImage);
```

Bad helper responsibilities:

```c
DRIVER_LL_READ_REG(...);
DRIVER_LL_WRITE_REG(...);
DRIVER_LL_EnableClockMask(...);
```

## Driver Layer

The public driver layer owns the user-facing API and the policy around it.

It must own:

- public argument validation
- compatibility checks between public selectors
- clock sequencing
- deciding which registers must be read
- deciding whether an operation can use atomic set/reset registers
- batching selected fields or pins
- dirty-register tracking
- writing each dirty register at the correct time
- returning user-facing `driver_status_t`

The intended optimized pattern for multi-field configuration is:

```c
validate_public_request(...);
enable_required_clocks(...);

if (request touches register A) {
    regAImage = LL_ReadRegisterA(...);
}
if (request touches register B) {
    regBImage = LL_ReadRegisterB(...);
}

for each selected element {
    Helper_StageElementConfig(..., &relevantRegImage);
    mark_relevant_register_dirty();
}

if (register A dirty) {
    LL_WriteRegisterA(..., regAImage);
}
if (register B dirty) {
    LL_WriteRegisterB(..., regBImage);
}
```

This keeps optimization in the layer that understands the full operation, while
keeping low-level register primitives reusable.

## Project/Application Layer

Project code should normally call public driver APIs.

Direct LL access is allowed only when the caller intentionally accepts all raw
responsibility:

- valid peripheral instance
- valid raw masks
- clock already enabled
- register side effects understood
- no public driver policy applied

Examples should prefer public APIs unless the example is explicitly teaching raw
register or LL behavior.

## Optimization Policy

Do not optimize by pushing policy down into LL.

Optimize by putting batching in the driver layer:

- read each touched register once
- mutate local images through helper functions
- write each dirty register once
- use atomic set/reset registers where the hardware provides them
- avoid full read-modify-write cycles when a write-only atomic register can
  express the operation

Initialization code is usually not a hot path, but this repository intentionally
uses it to learn where optimization belongs architecturally.

## Doxygen and Naming Policy

Documentation should describe authority and return meaning clearly.

Use `@returns` for what the return value represents.

Use `@retval - ...` for specific return cases.

Names should reveal ownership and intent:

- `LL` names should sound raw and hardware-near.
- `Helper` names should sound like translation, encoding, decoding, or staging.
- `Driver` names should sound like public operations.

Avoid names that hide policy or mix layer authority.

## Commit Discipline

Normalize one layer per commit.

Recommended order for a driver normalization:

1. Types and validation vocabulary.
2. LL raw access and hardware-layout primitives.
3. Helper translation and staging.
4. Driver orchestration and batching.
5. Project/application compatibility cleanup.

Each commit should leave the touched layer internally coherent before moving to
the next layer.

## Driver-Specific Notes

Driver-specific architecture notes may be added later when a driver needs extra
context. Those notes should point back to this document and explain only the
driver-specific interpretation or exception.
