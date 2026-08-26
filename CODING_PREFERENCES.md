# Coding Preferences

This file records the repository owner's coding and documentation preferences.
Update it whenever a new preference is established, and consult it before every
code change, review, or Doxygen pass.

Sections are grouped by concern (Documentation, Naming, Formatting,
Architecture, Application Template) so a specific rule can be found without
reading the whole file. The **Preference Log** at the end is the only
chronological section — it exists to show *when* and *why* each rule was
adopted, not to be read top-to-bottom for daily reference.

---

# 1. Documentation

## 1.1 What Counts as a Doxygen Pass

A Doxygen pass is not limited to editing `/** ... */` blocks. It includes:

- Correct, complete file/group/function/parameter/return-value/note/
  precondition/warning documentation, wherever applicable.
- An explicit `@def MACRO_NAME` in every documented macro's block, including
  short one-line constant macros.
- Valid Doxygen command syntax with resolvable references.
- Concise `//!` comments inside functions explaining logic, sequencing,
  preservation rules, hardware constraints, and side effects.
- Source formatting consistent with the [Call Layout](#32-function--macro-call-layout) rules.
- A Doxygen validation run plus relevant compile, test, and diff checks.

A pass is incomplete until every `#define` in scope has an exact matching
`@def` name and the audit reports zero omissions. This applies to public,
private, object-like, function-like, and one-line macros alike; header
guards without Doxygen blocks are excluded.

## 1.2 Doxygen Reference & Retval Syntax

- Every macro or symbolic constant used as a Doxygen `@ref` must place the
  target inside backticks — in accepted/expected-value lists, parameter
  descriptions, return descriptions, notes, warnings, and ordinary prose:

  ```c
   * - @ref `PERIPH_EVENT_UPDATE`: Update event
   * - Any non-empty combination contained by @ref `PERIPH_EVENT_ALL`
   * @note Start operation with @ref `DRIVER_STATUS_ON`
  ```

  Do not add a second quoted display label after the `@ref` target. Types,
  structures, members, groups, and functions stay unwrapped unless the
  surrounding style explicitly requires code styling.

- Use this exact status-return layout — list marker, backtick-wrapped `@ref`,
  one colon, no trailing period:

  ```c
   * @retval - @ref `DRIVER_STATUS_SUCCESS`: Register image was captured
   * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An input pointer is `NULL`
  ```

- Use the same list/colon layout for non-status return values:

  ```c
   * @retval - `0x00U`: The selector is not supported
   * @retval - `0x01U`: The selector is supported
  ```

- Every Doxygen `@p` reference to a function parameter must place the
  parameter name inside backticks too, the same as `@ref`:

  ```c
   * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: @p `pConfig` was a null pointer
   * @note Reading `SR` through this API participates in @p `events` clearing
  ```

  The parameter itself is already code on the other end of the reference
  (a function argument), so the doc-side mention stays code-styled too.

- Two Doxygen 1.9 parser quirks are accepted, not bugs to work around:
  - Repeated return-value warnings because the parser reads the list marker
    (`-`) as the return-value key — do not rewrite the house style to
    silence these.
  - `unexpected token TK_EOF as the argument of ref` for the required
    backtick-wrapped `@ref \`SYMBOL\`` form, when the symbol actually exists.
  - Missing targets, undocumented symbols, and malformed commands remain
    real validation failures — only the two exact warnings above are exempt.

## 1.3 Function Doxygen Layout

Document every public and private function in this order:

1. `@brief`, then `@details` when behavior, ownership, sequencing, or side
   effects need explanation.
2. One `@param[in]` / `@param[out]` / `@param[in,out]` entry per parameter.
3. An `Accepted values:` (input) or `Expected values:` (output) list right
   after each parameter, whenever its vocabulary can be stated.
4. A function-specific `@returns` line naming the returned status type.
5. Complete `@retval` entries for every status the implementation can return.
6. Applicable `@pre`, `@note`, and `@warning` entries.

```c
 * @param[in] operationState Requested Timer operation state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF`: Stop Timer counter operation
 * - @ref `DRIVER_STATUS_ON`: Start Timer counter operation
 * @returns @ref driver_status_t "Operation-state operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer counter operation state was updated
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `operationState` was invalid
```

Validation helpers use an action-oriented `@brief` starting with
`Validates`, plus the same return layout:

```c
 * @brief Validates that the Timer counter is stopped
 * @param[in] TIMx Timer peripheral instance
 * @returns @ref driver_status_t "Counter-state validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer clock is enabled and the counter is stopped
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Timer counter is running
```

- Document each parameter on its own — never combine several parameters
  into one Accepted Values block.
- Never omit a finite selector/range list when the API defines one.
- The `@retval` list must match the implementation exactly, including
  distinct null-pointer, invalid-argument, state, busy, and timeout paths.

## 1.4 Structure Doxygen Layout

Document every public and private structure with `@struct` using the public
typedef name. Every member needs one complete block containing:

1. A focused `@brief` explaining the member's semantic role.
2. An `Accepted Values:` list (writable/config members) or `Expected Values:`
   list (observation/output members).
3. Explicit symbolic values when the vocabulary is finite — never hide the
   valid set behind vague prose.
4. `@memberof` naming the owning public typedef.

```c
/**
 * @brief Describes one coherent peripheral configuration domain
 * @struct peripheral_config_t
 */
typedef struct _peripheral_config_t
{
	/**
	 * @brief Operation-mode selector
	 * Accepted Values:
	 * - @ref `PERIPHERAL_MODE_A`
	 * - @ref `PERIPHERAL_MODE_B`
	 * @memberof peripheral_config_t
	 */
	peripheral_mode_t	mode;
} peripheral_config_t;
```

- Do not use a trailing `/**< ... */` member comment when a complete member
  contract can be documented instead.
- Keep accepted/expected lists inside the owning member block so the
  structure can be audited without following its consumers.

## 1.5 Function-Local `//!` Logic Comments

- Place a concise `//!` comment immediately before the operation/block it
  explains:

  ```c
  //! Reuse the shared apply path to keep batching and dirty writes consistent.
  ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
  ```

- A comment must explain *why* the operation exists or *what invariant* it
  protects — never just translate the following C statement into English.
- Every function body needs at least one meaningful `//!` comment, including
  one-line adapters, getters, setters, startup handlers, and minimal
  interrupt handlers. For a thin function, explain why direct delegation, an
  atomic read, or a bounded interrupt-side operation is the correct
  ownership choice. Function-level Doxygen does not substitute for this.
- **A comment is incomplete if a reader would need to ask a follow-up
  question to understand why the line exists.** A label for *what* the
  operation does is not the same as an explanation of *why* it's written
  that way. This applies most to non-obvious arithmetic, bit-manipulation,
  rounding, or hardware-quirk lines — state the actual mechanism, and
  include a concrete before/after example whenever the comment describes a
  numeric trick (rounding, scaling, masking).

  Insufficient — names the operation, not the mechanism:
  ```c
  //! Convert the x100 remainder into one of BRR's 16 fractional steps, rounding to nearest.
  uint32_t fraction = ((fractionRemainder * USART_CODEC_BRR_OVERSAMPLING) + USART_CODEC_BRR_DIV_SCALE_HALF) / USART_CODEC_BRR_DIV_SCALE_FACTOR;
  ```

  Complete — states the mechanism with a worked example:
  ```c
  //! DIV_FRACTION expresses the fraction in sixteenths, not hundredths, so rescale by
  //! OVERSAMPLING (x16) before dividing back out by the x100 scale. Plain integer
  //! division always truncates toward zero (e.g. 1.6 -> 1), so DIV_SCALE_HALF (half of
  //! the x100 divisor) is added first to turn that truncation into round-to-nearest
  //! (e.g. 1.6 -> 2), matching RM0008's own rounded BRR worked examples.
  uint32_t fraction = ((fractionRemainder * USART_CODEC_BRR_OVERSAMPLING) + USART_CODEC_BRR_DIV_SCALE_HALF) / USART_CODEC_BRR_DIV_SCALE_FACTOR;
  ```

- This same standard applies to macro `@brief`s: a brief that only restates
  where a bit lives (its register/field name) instead of what it does to
  hardware behavior fails the same test.

## 1.6 Peripheral `.md` Two-Part Documentation Model

Every canonical peripheral `.md` page must be self-explanatory and contain
exactly two teaching parts, in this order:

1. **Theory with Register Mapping Bridge** — explains the peripheral without
   requiring source-code knowledge:
   - Purpose, terminology, state model, hardware flow, peer interactions,
     and the significance of every register in scope.
   - Register mapping states: owner, address/offset, width, implemented
     range, access class, special read/write semantics, side effects, and
     relationships between registers.
2. **Implementation with Theory Bridge** — maps that hardware model onto the
   repository:
   - Traces each theoretical state/action through its Core C member, LL
     access, Codec transformation (or documented no-Codec reason), Driver
     transaction, public API, volatile access width, ordering, validation,
     preservation, synchronization, concurrency, and shared-resource rules.
   - Explains deliberately omitted access directions or lower-layer
     functions.

Part 1 answers *what the hardware means and which registers express it*;
part 2 answers *how this project implements that theory and why*. Do not
interleave them in a way that forces a reader to understand source symbols
before learning the hardware model.

- The peripheral `.md` file is the single canonical long-form page for that
  peripheral's theory, architecture, register model, layer ownership, and
  implementation mapping — give its top-level heading a stable Doxygen page
  identifier.
- The peripheral's public Driver/LL Doxygen groups must `@ref` that page.
  Source Doxygen must not duplicate the theory: file/group comments
  summarize scope and ownership; individual API comments document only
  their local parameters, results, preconditions, side effects, exact
  hardware transaction, and safety warnings.
- The generated project documentation uses a concise Markdown main page as a
  navigation index, referencing each documentation-ready peripheral page
  without duplicating it. `Doxyfile` must list canonical peripheral pages in
  `INPUT` and configure the index through `USE_MDFILE_AS_MAINPAGE`.
- Only current, reviewed peripheral guides belong in the generated docs.
  Scratchpads, TODO files, superseded architecture snapshots, and internal
  planning records stay excluded unless explicitly promoted. A peripheral
  isn't documentation-complete until its page is linked from both the
  navigation index *and* the relevant generated Doxygen groups.
- For special registers, explicitly distinguish stored state from an action
  port: explain write-one-to-set, write-one-to-clear, write-zero-to-clear,
  read-clear, FIFO, data-port, keyed-write, and write-only behavior *before*
  describing the corresponding C access. Source Doxygen repeats only the
  operation-specific safety warning; a `volatile` declaration alone does not
  document these semantics.

## 1.7 Application Template File Documentation

- Use the Timer module as the concrete Doxygen/file-layout reference for
  application Template files, subject to later explicit overrides (e.g.
  left-aligned section titles). Every file starts with the standard `@file`,
  `@author`, `@brief`, `@version`, `@date`, `@details` metadata.
- The `@details` block must make the file's architectural position
  understandable standalone, using uniquely identified `@section` blocks for
  hierarchy, responsibility, and dependency boundary: the file's layer or
  cross-cutting role, its direct users, its direct dependencies, and its
  prohibited ownership. Never use an unexplained arrow instead of a named
  `includes`/`calls`/`uses`/`is invoked by` relationship.
- Number application layers from hardware upward. Layer 1 is always the
  hardware-nearest project/Driver access layer; increasing numbers own
  progressively more software-only service, policy, behavior, and
  orchestration. A higher layer may depend downward; a lower layer must not
  depend upward.
- Every application configuration macro's Doxygen must explain more than its
  literal value: its architectural significance, the capability/behavior it
  controls, its direct consumers, every accepted value, relevant cross-macro
  or hardware constraints, and what defining it does *not* do. Feature flags
  document both enabled and disabled behavior; hardware-selection macros
  document exclusive ownership and every companion mapping that must stay
  consistent.

---

# 2. Naming Conventions

## 2.1 Selector Macros vs. Typedef Stem

- Every value macro for a selector typedef must carry that typedef's own
  stem (its name minus the trailing `_t`) — not merely live in the right
  Doxygen group or file section. Singular/plural drift is fine
  (`usart_stop_bits_t` pairing with `USART_STOP_BIT_1`/`_0_5`/`_2`/`_1_5`
  keeps the shared `STOP_BIT(S)` stem despite the plural/singular mismatch),
  but dropping the stem entirely is not.
- The typedef's `_IS_VALID` validation macro is normally already named with
  the full stem. If that validation macro's stem doesn't match the plain
  value macros, the *value macros* drifted and must be renamed to match —
  not the validator. For example:
  - `usart_data_bits_t` had values `USART_8_BITS`/`USART_9_BITS` beside an
    already-correct `USART_DATA_BITS_IS_VALID` → renamed to
    `USART_DATA_BITS_8`/`USART_DATA_BITS_9`.
  - `usart_hardware_enable_t` had values `USART_TX_ENABLE`/`USART_RX_ENABLE`/
    `USART_RTS_ENABLE`/`USART_CTS_ENABLE`/`USART_TX_RX_ENABLE`/
    `USART_RTS_CTS_ENABLE`/`USART_HARDWARE_ALL`/`USART_HARDWARE_NONE` beside
    an already-correct `USART_HARDWARE_ENABLE_IS_VALID` → every value
    renamed onto the shared `USART_HARDWARE_ENABLE_*` stem.
- A consistent stem lets IDE autocomplete surface a selector's full value
  set the moment its typedef-derived prefix is typed, without the author
  needing to already know an unrelated shorthand name.

## 2.2 Register Field Macro Naming

- Use the owning block, register, and field in every field-macro root:
  `BLOCK_REGISTER_FIELD`.
- A single-bit field exposes `_Pos`, `_Msk`, and the unsuffixed mask alias.
- A multi-bit field exposes `_Pos`, `_Width`, `_Msk`, and the unsuffixed
  mask alias, in that order.
- `_Pos`/`_Width` use `reg_bit_pos_t`/`reg_field_width_t`; `_Msk` uses
  `REG_BIT_MASK()` or `REG_FIELD_MASK()`.
- Group raw register-field macros under one banner per owning register;
  order fields least-significant-bit first. When two documented views begin
  at the same bit, keep each internally complete and place the broader
  register/subregister view before its contained fields.
- Keep register-mask macros native to the 32-bit register width; prefer the
  direct `0x01UL` shift expression. Support field widths `0U..31U`; use
  `0xFFFFFFFFUL` explicitly when all 32 bits are required. Document that
  positioned bits beyond bit 31 are discarded instead of complicating the
  macro to preserve out-of-range bits.

## 2.3 Scalar & Register Types

- Use `reg` for register images, register masks, register field values, and
  pointers to caller-owned register images. Reserve fixed-width integer
  types for values that are not register representations, and use
  `uintptr_t` for address arithmetic.
- Use the Core-owned `frequency_t` typedef for every hertz-valued API
  return, output, structure field, constant, and intermediate value. Do not
  introduce peripheral-specific aliases (`rcc_freq_t`, `tim_frequency_t`)
  for the same physical quantity. Prescaler selectors and dimensionless
  divider values keep their own semantic types instead of using
  `frequency_t`.

## 2.4 Variable Naming in Shared Helpers

- Prefer role-specific names — `registerImage`, `positionedFieldMask`,
  `fieldPosition` — over shortened generic names — `regImage`, `mask`,
  `value`, `pos` — inside shared register helpers.
- Express register-field replacement as explicit copy, clear, and set
  operations, with the final return kept separate so each preservation step
  stays easy to inspect.

## 2.5 Application Template File & Symbol Naming

- Startup declarations, linker-symbol declarations, the vector table, and
  application-service policy live inside each project — the shared Driver
  root must not own or inject a project's startup implementation.
- Name project-owned Template service modules `app_*.*`, including
  `app_startup.[ch]`. Keep conventional names only for `main.[ch]` and
  `syscalls.c`.
- Reusable SysTick hardware access is the shared `BareMetal/Driver/SysTick`
  stack, keeping `systick.[ch]` and the `SysTick_` prefix as a naming
  exception. Application time state and the strong `SysTick_Handler()`
  definition belong to the project-owned `app_time` service; the handler
  performs only the minimum state publication needed by main context.
- Symbols called by the processor, linker, or C library keep their required
  ABI names; every other project-owned public service function uses the
  `App_` prefix.
- Project include directories take precedence over shared Driver include
  directories.

---

# 3. Source Formatting & Layout

## 3.1 Control Flow

- Prefer explicit `if`/`else` over ternary expressions — the longer form
  keeps state mapping and error behavior easy to scan.
- Use fully braced, multi-line `switch` cases, with assignments, `break`,
  and returns on separate lines:

  ```c
  //! Match by peripheral base address because instance macros are raw memory-mapped pointers.
  switch ((uintptr_t) TIMx)
  {
  	case TIM2_BASE_ADDRESS:
  	{
  		*pClockMask = RCC_APB1ENR_TIM2EN;
  		break;
  	}
  	default:
  	{
  		return DRIVER_STATUS_ERROR_INVALID_ARG;
  	}
  }
  ```

  Never place a case assignment and `break`, or a default label and return,
  on the same line.

- The same fully braced, multi-line requirement applies to **every**
  `if`/`else` body, including single-statement bodies. Never collapse a
  condition and its body onto one line, and never pack multiple single-line
  `if` statements into an aligned column of `{ statement; }` blocks — even
  when a run of similar short conditions looks compact and readable that
  way:

  ```c
  // Not this:
  if ((cr1RegImage & USART_CR1_IDLEIE) != 0x00000000UL)	{ sources |= USART_IRQ_SOURCE_IDLE; }
  if ((cr1RegImage & USART_CR1_RXNEIE) != 0x00000000UL)	{ sources |= USART_IRQ_SOURCE_RXNE; }

  // This:
  if ((cr1RegImage & USART_CR1_IDLEIE) != 0x00000000UL)
  {
  	sources |= USART_IRQ_SOURCE_IDLE;
  }
  if ((cr1RegImage & USART_CR1_RXNEIE) != 0x00000000UL)
  {
  	sources |= USART_IRQ_SOURCE_RXNE;
  }
  ```

  This stays consistent with the `switch` layout above and remains easy to
  extend with a second statement or a breakpoint later.

- Do not introduce a local variable solely to avoid a ternary, or to
  pre-compute a value that is already directly available at each use site.
  If the input itself can be tested inline at every branch, test it there
  instead of caching it in a redundant intermediate:

  ```c
  // Not this — setBits only ever restates sourceState, adding a variable that
  // tracks no additional information:
  const uint8_t setBits = (sourceState == DRIVER_STATUS_ON) ? 0x01U : 0x00U;
  if (setBits) { updatedCr1RegImage |= USART_CR1_IDLEIE; } else { updatedCr1RegImage &= ~USART_CR1_IDLEIE; }

  // This — test the real input directly at each site:
  if (sourceState == DRIVER_STATUS_ON)
  {
  	updatedCr1RegImage |= USART_CR1_IDLEIE;
  }
  else
  {
  	updatedCr1RegImage &= ~USART_CR1_IDLEIE;
  }
  ```

## 3.2 Function & Macro Call Layout

- Keep a call on one line when it stays readable:

  ```c
  ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
  ```

- When a nested or argument-heavy call needs multiple lines, expand *every*
  nesting level: each function/macro name on its own line, its opening
  parenthesis on the next line, one argument per line, closing parentheses
  aligned to their call depth:

  ```c
  ASSERT_DRIVER_STATUS
  (
  	Codec_TIM_ExtractTimeBaseConfig
  	(
  		LL_TIM_ReadPSC(TIMx),
  		LL_TIM_ReadARR(TIMx),
  		LL_TIM_ReadCNT(TIMx),
  		&timeBase
  	)
  );
  ```

- Do not expand short calls mechanically — choose compact vs. expanded based
  on readability, and keep the chosen form consistent within a module.

## 3.3 Macro Alignment & Banner Grouping

- Align related `#define` values across their complete major banner domain:
  find the longest macro name in that domain, place exactly two tabs after
  it, and add enough tabs after every shorter name so all values start in the
  same column. Register sub-banners do not reset alignment; for example,
  every macro beneath one peripheral's `Register Defines` banner shares one
  column across CR1, CR2, SR1, SR2, and the remaining register sections.
  A single peripheral Core register header also keeps its device constants
  and register-field macros in that shared column. Recalculate only when
  entering a logically independent module or file domain.

  ```c
  /** @brief Microsecond delay chunk used by the millisecond blocking helper @def TIM_DRIVER_BLOCKING_DELAY_MS_CHUNK_US */
  #define TIM_DRIVER_BLOCKING_DELAY_MS_CHUNK_US			((uint16_t) 1000U)
  /** @brief Conservative polling-loop budget per requested microsecond @def TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_PER_US */
  #define TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_PER_US		((uint32_t) 1024UL)
  /** @brief Fixed setup allowance added to the blocking polling-loop budget @def TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_BASE */
  #define TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_BASE		((uint32_t) 1024UL)
  ```

- Use tab characters, not runs of spaces, for this alignment and for
  multi-line macro continuation indentation. The single separator after
  `#define` and the conventional ` *` inside Doxygen blocks are not
  indentation and remain spaces. Evaluate visual alignment with a four-column
  tab stop; macro values must begin in the same rendered column under that
  setting.

- Keep every register-field macro family visually atomic: place no blank
  lines between its `_Pos`, optional `_Width`, `_Msk`, and unsuffixed alias,
  then place exactly one blank line before the next field family. Treat a
  standalone raw field-value macro as its own family and separate it the same
  way. This whitespace is a semantic boundary that makes each complete field
  definition immediately distinguishable from the next.

- Within one register-map structure, align every sibling bitfield's trailing
  `/**< ... */` comment to one shared column across all register unions. Use
  the longest declaration as the anchor, place exactly two tabs after it, and
  add tabs after shorter declarations as required. Apply the same rule to
  documented closing register members such as `} CR1;` and `} SR2;`.

(See [2.2 Register Field Macro Naming](#22-register-field-macro-naming) for
the register-banner ordering and `_Pos`/`_Width`/`_Msk` family rules.)

## 3.4 Section Banner Formatting

- Write section-banner titles left-aligned, without decorative padding,
  between the existing border lines — never centered with space/tab runs:

  ```c
  // ==================================================================================================== //
  // Public API
  // ==================================================================================================== //
  ```

- Follow the Timer-header structural style: one `// Header Guard` line
  immediately before `#ifndef`/`#define`, `// --- C++ Compatibility ---` at
  both linkage boundaries, and close the file directly with
  `#endif /* HEADER_GUARD */`. Do not add redundant `Header Guard End`,
  `C++ Compatibility End`, or `Documentation Group` banners.
- Use banners to express logical API hierarchy, not just to divide a long
  file. A major `=` banner owns one coherent domain (configuration,
  operation control, state observation, tick storage, interrupt handling);
  a domain with distinct pairs/subdomains gets a left-aligned `-`
  sub-banner beneath it. Don't club unrelated control/state/data APIs under
  one generic banner. Header and source files use the same banner names and
  API order.
- Within every lifecycle/operation-control conjugate pair, place the
  teardown/release operation before the setup/acquire operation: `Destroy`
  before `Create`, `DeConfig` before `Config`, `Disable` before `Enable`,
  `Stop` before `Start`. Apply this order consistently in declarations,
  definitions, and documentation.

---

# 4. Driver Architecture

## 4.1 Layer Ownership & Reuse

- Place peripheral-independent behavior in the lowest shared layer that can
  express it safely. Peripheral layers keep only their own validation,
  register selection, sequencing, and hardware policy.
- Place every raw register-field macro in the Core header of the hardware
  block that *physically* owns the register, even when another Driver
  consumes that field (e.g. `SCB_AIRCR_xxx` belongs in `stm32f1xx_scb.h`;
  NVIC may consume `AIRCR.PRIGROUP` without owning or duplicating it).
  Compatibility headers may include the owner header to preserve macro
  visibility, but must not redeclare the macros.
- Do not centralize peripheral instance/capability predicates or
  peripheral-specific operating limits in `stm32f1xx_defines.h` — keep them
  in the respective peripheral stack (e.g. oscillator/clock-frequency
  limits belong to RCC).
- Peripheral-independent register *behavior* (e.g. compare-and-write) lives
  in a shared primitive like `RegOps_WriteIfChanged()`; a peripheral (Timer)
  wraps it to validate its own instance/register selection, and other
  peripherals (GPIO, RCC) can reuse the same primitive while keeping their
  own rules.
- Reserve a static LUT for genuine table-shaped per-instance data — the
  kind of mapping that would otherwise need real metadata storage (e.g. a
  GPIO pin-routing table with port/pin/mode per instance). When such a LUT
  is needed, index it by the driver's stable instance index using the
  smallest element type that represents the mapping directly (an array of
  `rcc_bus_t`, not an array of metadata structures).
- For a small, fixed dispatch over 2-3 known instances (such as resolving
  one RCC bus selector or one clock/reset mask per instance), prefer a
  `switch` on the peripheral base address over a LUT. A LUT trades memory
  for faster access, and that trade only pays for itself when the access is
  either genuinely hot or the data is too rich to express as `switch` cases;
  neither applies to a one-time-per-configuration-call constant lookup. Use
  the same base-address `switch` shape already established for register-field
  and reset-mask decoding (see `_TIM_DecodeAPB1ClockEnableMask()`), not a
  parallel array, so the lookup mechanism stays consistent regardless of
  which instance property is being resolved.

## 4.2 Register Access Pattern (`.REG` / `.BIT`)

- When a Core register structure models named fields, expose the hardware
  word as a register-member union with a full-width `.REG` image and a
  named `.BIT` field view (the Timer register-map pattern). Order fields
  least-significant-bit first, and represent every gap explicitly with a
  reserved field so the view totals exactly 32 bits. If one physical bit
  range has different read and write meanings, add named `.BIT.READ` /
  `.BIT.WRITE` views inside the union instead of picking one misleading
  interpretation.
- `.REG` is the canonical LL transaction path. A `.BIT` view documents and
  exposes field placement, but does not authorize a compiler-generated
  read-modify-write where the hardware contract requires a staged
  full-register transfer — keyed, action, write-only, and
  write-one-to-clear transactions must use the full-register operation.
- Centralize each peripheral LL's ordinary full-width volatile access in one
  generic pointer-based read primitive and one generic pointer-based write
  primitive. Named register accessors select the right `.REG` pointer and
  delegate to those primitives — never repeat direct dereference or
  `RegOps_Read()`/`RegOps_Write()` mechanics. Keep the named surface
  symmetric where hardware permits; preserve truthful asymmetry for
  read-only, write-only, and action-port registers, documenting *why* the
  missing direction/conjugate doesn't exist. A semantic write-to-clear
  helper may delegate through the corresponding named writer.

## 4.3 Validation & Fallible Results (`driver_status_t`)

- Every validation function returns `driver_status_t`:
  `DRIVER_STATUS_SUCCESS` when valid, the most specific
  `DRIVER_STATUS_ERROR_*` otherwise. Never return `uint8_t`, `bool`,
  `0x00U`, or `0x01U` as a validation result.
- Fallible predicates and state queries must preserve the distinction
  between a legitimate negative state and an operation failure — never
  collapse a null pointer, invalid argument, unavailable clock, invalid
  hardware state, or other error into `0`, `false`, or an apparent
  OFF/not-pending result.
- Use one of these three contracts:
  - **Validation-only helper** — returns `DRIVER_STATUS_SUCCESS` or a
    specific `DRIVER_STATUS_ERROR_*`.
  - **Truly binary state getter** — returns `DRIVER_STATUS_OFF`/`_ON`
    directly, while still preserving distinct error statuses.
  - **Fallible data/mask/extensible-state query** — returns operation
    status, publishing the result through an output pointer only after the
    operation succeeds.
- Compatibility wrappers must not collapse a status-returning API into a
  raw Boolean result — remove or migrate such wrappers instead of treating
  an error as a valid negative result.
- Driver and Codec orchestration/staging/commit/validation/cleanup helpers
  that participate in a status-returning call chain must also return
  `driver_status_t` — never `void` merely because current LL operations
  can't fail. Return `DRIVER_STATUS_SUCCESS` and preserve status
  propagation so later validation or hardware-error reporting doesn't need
  an API-contract change.
- Reserve `void` for interfaces whose contract is inherently void (an
  interrupt-handler ABI) and for deliberately dumb LL write primitives that
  own no validation, sequencing, or fallible policy.

## 4.4 Conjugate API Naming & Scope

- Conjugate API pairs must be symmetric in both naming and semantic scope —
  `TIM_Config()`/`TIM_DeConfig()`, `TIM_GetIRQEvents()`/`TIM_AckIRQEvents()`.
  Never pair a function that owns only a narrow subdomain with one that
  resets or mutates the complete peripheral.
- Every public getter for a mutable operation state needs its symmetric
  setter (`PERIPH_GetOperationState()` / `PERIPH_SetOperationState(state)`).
  When a state domain accepts both `DRIVER_STATUS_OFF` and `_ON`, prefer
  that single Get/Set pair over separate public `Disable()`/`Enable()`
  functions. Separate action verbs remain appropriate only when the
  hardware actions are genuinely asymmetric and can't be one truthful state
  setter — document that exception explicitly.
- A root configuration type (`tim_config_t`) represents every currently
  admitted base-configuration domain intentionally included in it. Its
  root config API applies the whole object while preserving explicitly
  separate operational domains (e.g. IRQ-source enables). Its
  deconfiguration conjugate restores the documented reset state. Conjugate
  lifecycle entry points stay independent: a configuration function must
  not call its deconfiguration conjugate, and vice versa — the application
  owns their ordering and explicitly requests a reset when needed.
- Do not expose general-purpose convenience functions that configure a
  peripheral to an arbitrary requested frequency — callers provide explicit
  register-semantic values. A narrowly named service-bootstrap helper is
  acceptable when a concrete admitted service needs one fixed
  configuration, validates its documented clock assumption, and delegates
  the canonical root configuration API (e.g. `TIM_ConfigForBlockingDelay()`
  for a validated 72 MHz Timer kernel clock) — it must never become a
  general frequency setter.
- Calculated-frequency *getters* are fine — they observe/report programmed
  state without mutating configuration.

## 4.5 Structured Configuration & Transaction Decomposition

**Configuration structures**

- A root configuration structure is a structure of independently coherent
  configuration domains. Do not create a configuration structure merely
  because one function accepts more than one value — prefer explicit typed
  parameters when a small set of single-use scalar values has no
  independently reusable domain, lifecycle, or cross-field invariant
  (SysTick clock-source + reload is the canonical example). A structure is
  appropriate only when its members form a stable domain that's passed,
  stored, returned, nested, or validated as one reusable object.
- Every nested configuration structure representing an independently
  useful, admitted operation normally needs a symmetric public grouped
  `Get`/`Set` pair. Deliberately asymmetric hardware actions are exceptions
  and must document why no conjugate exists. The root function and the
  grouped setter reuse the same narrowly scoped private staging helper; the
  grouped getter uses the matching extraction path.

  ```c
  typedef struct _periph_config_t
  {
  	periph_timebase_config_t	timebase;
  	periph_counter_config_t		counter;

  } periph_config_t;
  ```

- Do not place interrupt-request source enables inside a root configuration
  structure — IRQ-source enablement stays an explicit application action so
  the call site proves interrupt generation was intentional. Root
  configuration preserves the peripheral IRQ-source register; the
  application configures sources separately before enabling NVIC delivery:

  ```c
  ASSERT_DRIVER_STATUS(RCC_EnablePeripheralClock(PERIPH1_CLOCK_MASK));
  ASSERT_DRIVER_STATUS(PERIPH_Config(PERIPH1, &config));
  ASSERT_DRIVER_STATUS
  (
  	PERIPH_SetIRQSources
  	(
  		PERIPH1,
  		PERIPH_IRQ_SOURCE_UPDATE,
  		DRIVER_STATUS_ON
  	)
  );
  ASSERT_DRIVER_STATUS(NVIC_ClearPendingIRQ(PERIPH1_IRQn));
  ASSERT_DRIVER_STATUS(NVIC_EnableIRQ(PERIPH1_IRQn));
  ASSERT_DRIVER_STATUS(PERIPH_SetOperationState(PERIPH1, DRIVER_STATUS_ON));
  ```

  Omitting `PERIPH_SetIRQSources()` leaves existing IRQ-source state
  unchanged; disabling sources is equally explicit, passing the owned
  source mask with `DRIVER_STATUS_OFF`.

**Clock, reset, and NVIC ownership**

- Clock-gate ownership stays explicit and outside the peripheral Driver.
  The application uses the RCC Driver to enable the required gate *before*
  configuration. A peripheral Driver may query RCC to validate that
  precondition, but must not expose duplicate clock APIs or mutate the gate
  inside `Config()`, `DeConfig()`, grouped configuration, operation-state,
  IRQ, or action APIs.
- `DeConfig()` restores the peripheral register bank through the peer RCC
  reset service when that's the hardware-defined mechanism, but leaves the
  application-owned clock gate and NVIC delivery state unchanged. The
  application explicitly decides when either external resource is
  disabled:

  ```text
  RCC clock enable
    -> peripheral base configuration
    -> peripheral IRQ-source configuration
    -> NVIC pending-state cleanup and delivery enablement
    -> peripheral operation enablement
  ```

- Root peripheral configuration must not read, validate, clear, disable, or
  enable NVIC delivery state — the application owns the explicit ordering
  between base configuration, IRQ-source enablement, pending-line cleanup,
  NVIC delivery enablement, and the final transition to active state.

**Staging helpers**

- Staging helpers each accept only one configuration domain plus the
  caller-owned register images that domain can modify:

  ```c
  static driver_status_t _PERIPH_StageTimeBaseConfig
  (
  	const periph_timebase_config_t* const	pTimeBaseConfig,
  	reg* const								pPrescalerRegisterImage,
  	reg* const								pAutoReloadRegisterImage,
  	reg* const								pCounterRegisterImage
  );

  static driver_status_t _PERIPH_StageCounterConfig
  (
  	const periph_counter_config_t* const	pCounterConfig,
  	reg* const								pControlRegisterImage
  );
  ```

- A staging helper must:
  - perform only the transformation named by its signature;
  - validate its own pointer/domain contract and return `driver_status_t`;
  - transform caller-owned, non-volatile images with no MMIO, clock, reset,
    NVIC, operation-state, or cleanup work;
  - use Codec functions for individual field encoding instead of
    duplicating register placement in the Driver;
  - stage through local working images and publish output only after every
    fallible transformation succeeds; and
  - preserve every register field outside its declared domain.
- Every structure inside a public root configuration object has one
  corresponding private `_PERIPH_Stage<Domain>Config()` helper, owning the
  atomic local-copy/publication boundary for its structure and invoking the
  grouped Codec transformation. One reusable staging path per configuration
  member — no exceptions.

**Public API ownership**

- Public configuration APIs own the full Read/Modify/Write transaction:

  ```text
  PERIPH_GetTimeBaseConfig()
    -> validate public output and live preconditions
    -> read every required register image once
    -> extract the complete timebase structure without changing hardware

  PERIPH_SetTimeBaseConfig()
    -> validate public input and live preconditions
    -> read every required current register image once
    -> call _PERIPH_StageTimeBaseConfig(...)
    -> commit changed images in the required hardware order
    -> run the documented cleanup path

  PERIPH_Config()
    -> validate the complete root request and lifecycle preconditions
    -> read every image required by all represented domains
    -> call _PERIPH_StageCounterConfig(...)
    -> call _PERIPH_StageTimeBaseConfig(...)
    -> commit only after all fallible staging succeeds
    -> preserve peripheral IRQ-source state
    -> run the documented cleanup path
  ```

- The root function must not duplicate the grouped staging logic, and must
  not call public grouped setters when that would create multiple partially
  committed transactions — it reuses their private staging helpers, stages
  the whole root request before the first write, then owns one ordered
  commit. A grouped public setter reads and commits only its own domain's
  registers.
- Private helpers stage cached values but never commit configuration MMIO
  themselves — the public configuration API directly compares and writes
  its cached images in the required hardware order, including any
  temporary policy, action-register, or restoration sequence. This keeps
  the public function's maximum authority and real hardware cost visible.
  Only deliberately mechanical LL register-write primitives stay `void`.
- Timer example: `TIM_Config()` visibly composes the staging paths for
  `tim_config_counter_t` and `tim_config_timebase_t` while preserving
  `TIMx_DIER`. `TIM_GetCounterConfig()`/`SetCounterConfig()` and
  `TIM_GetTimeBaseConfig()`/`SetTimeBaseConfig()` are the grouped domain
  pairs; their setters reuse the staging paths while the root transaction
  performs one all-domain ordered commit. No private helper shadows all of
  `TIM_Config()`, and no configuration path calls `TIM_DeConfig()`.
  Applications configure Timer interrupt generation separately through
  `TIM_SetIRQSources()`.

## 4.6 MMIO Access Minimization

- Modularity must not multiply volatile register accesses. Helper
  boundaries separate validation, staging, and commit responsibilities —
  they never grant a helper permission to reread or rewrite the same
  hardware register.
- For each coherent Driver transaction:
  1. Validate the complete request and every live precondition that can
     fail.
  2. Snapshot each required volatile register exactly once.
  3. Pass caller-owned `reg` images through narrow, MMIO-free staging
     helpers.
  4. Coalesce every compatible domain/field change into the final register
     image.
  5. Dirty-write each changed register exactly once when hardware allows.
  6. Perform additional reads/writes only when a named hardware
     requirement demands it — an unlock sequence, mode transition,
     write-zero/write-one-to-clear behavior, read-to-clear behavior, or a
     preload/update-event commit.
- Hold the declared exclusive ownership or transaction guard across the
  whole snapshot/stage/commit interval. Do not reread a cached
  configuration register just to repeat a precondition check right before
  commit — if concurrency must be supported, define an explicit guard
  instead of weakening the cached-image model.
- Do not reread a register merely because multiple staging helpers consume
  its fields, and do not let separate helpers commit partial images when
  one public API owns the coherent transaction. Every additional MMIO
  access must be justified by the peripheral contract and documented
  beside the sequence requiring it — correct hardware ordering takes
  precedence over forcing an unsafe single-write implementation.
- Do not introduce a transaction structure merely to shorten a helper
  signature or hide several temporal images of the same register — pass
  independently required `reg` images explicitly so inputs, outputs, and
  authority stay visible. A structure is appropriate only for a stable,
  reusable domain with its own invariant, never as a bare argument
  container.
- When hardware makes a requested field read-only/non-writable in the
  current mode, return the appropriate `driver_status_t` error *before* the
  first write. Do not hide a multi-step mode transition inside one
  configuration call to force the request to succeed — the application
  explicitly calls the public APIs that leave the restrictive mode, apply
  the field, and restore the desired mode:

  ```c
  periph_domain_config_t currentConfig;

  ASSERT_DRIVER_STATUS
  (
  	Codec_PERIPH_ExtractDomainConfig(currentRegisterImage, &currentConfig)
  );

  //! Reject a field transition that hardware cannot accept in the current mode.
  if ((currentConfig.mode == PERIPH_MODE_RESTRICTIVE) &&
  	(currentConfig.field != pConfig->field))
  {
  	return DRIVER_STATUS_ERROR_STATE;
  }
  ```

  The Driver never synthesizes those mode-change calls or intermediate MMIO
  writes internally.
- The generic single-register transaction shape:

  ```c
  driver_status_t PERIPH_SetDomainConfig
  (
  	PERIPH_TypeDef* const				pPeripheral,
  	const periph_domain_config_t* const	pConfig
  )
  {
  	// Local Variables
  	reg currentRegisterImage = 0x00000000UL;
  	reg targetRegisterImage = 0x00000000UL;

  	// Validate Input and State
  	ASSERT_DRIVER_STATUS(_PERIPH_ValidateDomainTransaction(pPeripheral, pConfig));

  	//! Snapshot once, then let modular helpers transform only local images.
  	currentRegisterImage = LL_PERIPH_ReadControl(pPeripheral);
  	targetRegisterImage = currentRegisterImage;
  	ASSERT_DRIVER_STATUS(_PERIPH_StageDomainConfig(pConfig, &targetRegisterImage));

  	//! Coalesce compatible changes into one dirty write.
  	if (currentRegisterImage != targetRegisterImage)
  	{
  		LL_PERIPH_WriteControl(pPeripheral, targetRegisterImage);
  	}

  	return DRIVER_STATUS_SUCCESS;
  }
  ```

  If hardware requires an intermediate image, the public transaction
  performs the minimum ordered multi-write sequence directly, with Doxygen
  and `//!` comments naming the hardware rule that makes each additional
  access mandatory.

## 4.7 BSP Capability Packaging and Initialization

- Split board support by cohesive hardware capability. The Blue Pill board
  package uses `bsp_gpio.[ch]` for board GPIO conveniences and
  `bsp_usart.[ch]` for the fixed board USART transport; do not place either
  implementation back into a monolithic `bsp.c`.
- Each capability implementation includes its own matching public header
  first. Each public capability header is self-contained and includes only
  the headers required by its public macros, types, and declarations.
  Implementation-only dependencies remain in the `.c` file.
- `bsp.h` is an aggregate compatibility header. It includes capability headers
  only under BSP-owned build definitions such as
  `BSP_GPIO_CAPABILITY_ENABLED` and `BSP_USART_CAPABILITY_ENABLED`; shared BSP
  code never consumes project-owned `APP_ENABLE_*` policy.
- New and minimal consumers include `bsp_gpio.h` or `bsp_usart.h` directly and
  request the matching `BSP_GPIO` or `BSP_USART` CMake component. The aggregate
  `BSP` component deliberately resolves both capabilities.
- Expose one canonical public initialization transaction per capability:
  `BSP_InitOBLED()` and `BSP_InitUSART()`. Each initializer owns every RCC,
  GPIO, and peripheral operation needed to make its board capability ready and
  deterministic. Application boot code conditionally orchestrates those calls;
  it does not reproduce board clock masks or configuration sequences.
- Divide each complete BSP initializer into private `static inline` helpers
  for its cohesive clock, GPIO, and peripheral subtransactions. Do not expose
  those helpers or implementation-only RCC masks in public BSP headers.
- Keep steady-state board operations public only when a current consumer needs
  them. Legacy debug-USART wrappers may remain in the USART capability as
  explicitly documented compatibility APIs, but they delegate canonical BSP
  behavior and do not create a second initialization policy.

---

# 5. Application Template Rules

(For file/symbol naming specifics, see
[2.5 Application Template File & Symbol Naming](#25-application-template-file--symbol-naming).)

- Every application Template header that declares an externally linked
  function or object must wrap those declarations in an `extern "C"` guard
  for C++ consumers. Macro-only configuration headers don't need this.
- Application Template files use `stm32f1xx_data_types.h` as their direct
  source of fixed-width integers, shared physical quantities, register
  vocabulary, and driver statuses — never include `<stdint.h>` or another
  standard scalar-type header directly from a Template file. Standard
  headers providing a distinct service (`<errno.h>`) remain direct
  dependencies where that service is actually used.

---

# Preference Log

- 2026-08-26: Split BSP into independently selected GPIO and USART capability
  headers/sources and CMake components, retained `bsp.h` as a guarded aggregate,
  required capability headers to be self-contained and minimal, and assigned
  complete RCC/GPIO/peripheral initialization ownership to `BSP_InitOBLED()`
  and `BSP_InitUSART()` with private static-inline subtransaction helpers.
- 2026-08-23: Extended peripheral-header alignment across device constants,
  all register-field macros, sibling bitfield comments, and documented closing
  register members so the complete header uses coherent shared columns.
- 2026-08-23: Restricted static LUTs to genuine table-shaped per-instance
  data; required a base-address `switch` instead of a parallel array for
  small fixed dispatch such as an RCC bus or clock/reset mask lookup, since
  the memory-for-speed LUT trade-off doesn't pay for itself on a one-time
  configuration-path lookup.
- 2026-08-23: Clarified that one peripheral `Register Defines` domain uses a
  single macro-value column across every register sub-banner; sub-banners do
  not restart alignment.
- 2026-08-23: Fixed the repository's visual-alignment basis at four-column
  tab stops so tab-only macro alignment renders consistently in the owner's
  editor.
- 2026-08-23: Required exactly one blank line between complete register-field
  macro families, with no blank lines inside a `_Pos`/optional `_Width`/`_Msk`/
  alias family; standalone raw field values follow the same separation rule.
- 2026-08-23: Extended the fully braced, multi-line requirement from `switch`
  cases to every `if`/`else` body, prohibiting collapsed single-line
  `{ statement; }` forms even for runs of similar short conditions.
- 2026-08-23: Required `//!` logic comments (and macro `@brief`s) to state the
  actual mechanism behind non-obvious arithmetic/bit-manipulation/rounding
  lines, with a worked example for numeric tricks, rather than only labeling
  what the operation does.
- 2026-08-23: Required every selector-typedef value macro to carry that
  typedef's own stem, matching an already-correctly-named `_IS_VALID`
  validation macro rather than the other way around.
- 2026-08-23: Required Doxygen `@p` parameter references to backtick-wrap the
  parameter name, the same as `@ref`, since the referenced parameter is
  already code on the declaration side.
- 2026-08-22: Prohibited configuration structures that only bundle a small
  set of single-use scalar function arguments; required explicit typed
  parameters unless the values form a reusable domain object or invariant.
- 2026-08-22: Centralized peripheral LL register mechanics in generic
  pointer-based read/write primitives and required named accessors to delegate
  register selection while preserving hardware-defined access asymmetry.
- 2026-08-22: Required at least one meaningful implementation-local `//!`
  comment inside every function body, including thin wrappers, state accessors,
  startup handlers, and minimal IRQ handlers.
- 2026-08-22: Required every public mutable operation-state getter to have a
  symmetric setter and preferred one OFF/ON Get/Set pair over redundant public
  Disable/Enable functions.
- 2026-08-22: Required hierarchical logical API banners mirrored between
  headers and sources, and ordered lifecycle/control conjugates teardown-first
  (`Destroy`/`DeConfig`/`Disable`/`Stop` before their constructive counterparts).
- 2026-08-22: Fixed application layer numbering from hardware upward, with
  Layer 1 always hardware-nearest and higher layers owning progressively more
  software orchestration; required capability-oriented configuration-macro
  Doxygen with accepted values, consumers, constraints, and non-effects.
- 2026-08-22: Made `stm32f1xx_data_types.h` the sole Template-facing gateway
  for standard fixed-width and repository-wide scalar types; prohibited direct
  Template `<stdint.h>` includes.
- 2026-08-22: Adopted Timer-style Template file metadata and structural guard
  markers, prohibited redundant end/group banners, and required explicit
  per-file hierarchy, responsibility, and dependency-boundary documentation.
- 2026-08-22: Required left-aligned, unpadded ordinary section-banner titles
  and an explicit `Header Guard` marker before every header guard.
- 2026-08-22: Assigned startup ownership to each project, standardized
  reusable Template filenames on `app_*.*`, retained conventional platform and
  ABI entry filenames, and required project-local headers to take include-path
  precedence.
- 2026-08-22: Kept project-owned SysTick as an explicit `systick.[ch]` and
  `SysTick_` naming exception beneath the application time service.
- 2026-08-22: Superseded project-local SysTick ownership: moved reusable
  SysTick hardware state into a shared Driver/LL stack while keeping the
  software tick and minimal strong `SysTick_Handler()` in `app_time`.
- 2026-08-22: Required C++ linkage guards in every Template header that
  declares externally linked functions or objects.
- 2026-08-22: Named the project-owned startup module `app_startup.[ch]` while
  retaining processor-mandated reset and exception ABI symbol names.
- 2026-08-16: Restored the repository-owner Doxygen style using
  backtick-wrapped `@ref` targets and list-style referenced `@retval` status
  entries. This later decision supersedes the earlier same-day native Doxygen
  return/reference syntax preference.
- 2026-08-16: Replaced invalid backtick-wrapped Doxygen `@ref` targets with
  bare targets plus quoted backtick-styled display labels, and replaced the
  invalid `@retval - @ref ...` list form with Doxygen's native
  `@retval VALUE Description` form.
- 2026-08-16: Required Timer-style `.REG` and `.BIT` views for Core register
  structures with named fields, explicit reserved gaps, nested views for
  overlapping read/write meanings, and full-register LL transactions for
  keyed, action, write-only, or write-one-to-clear semantics.
- 2026-08-16: Required register-scoped macro banners, least-significant-bit
  first field order, `BLOCK_REGISTER_FIELD` roots, and complete
  `_Pos`/`_Width`/`_Msk`/mask-alias families matching the Timer register
  layer.
- 2026-08-16: Assigned raw register-field macros to the Core header of the
  physical register owner, prohibited peer Driver headers from duplicating
  those definitions, and permitted compatibility includes to preserve macro
  visibility.
- 2026-08-16: Assigned peripheral instance/capability predicates and
  peripheral-specific operating limits to their respective driver stacks
  instead of the shared Core defines header.
- 2026-08-16: Required macro value alignment and multi-line macro continuation
  indentation to use tabs rather than runs of spaces.
- 2026-08-16: Established the initial theory-to-implementation documentation
  bridge; the later two-part single-source rule below supersedes duplication of
  theory in function-local LL Doxygen.
- 2026-08-16: Made reviewed peripheral `.md` files the canonical long-form
  Doxygen pages, required public Driver/LL groups and the generated project
  navigation page to reference them, and kept planning/TODO material excluded.
- 2026-08-16: Required each canonical peripheral guide to contain Theory with
  Register Mapping Bridge followed by Implementation with Theory Bridge, and
  prohibited duplicating that theory in source Doxygen.
- 2026-08-15: Required every macro or symbolic constant used as a Doxygen
  `@ref` target to be enclosed in backticks in all documentation contexts.
- 2026-08-15: Assigned peripheral clock-gate query/mutation to RCC/application,
  prohibited peripheral Drivers from hiding gate transitions inside lifecycle
  or narrow APIs, and required `DeConfig()` to leave application-owned RCC and
  NVIC state unchanged.
- 2026-08-15: Required coherent Driver transactions to snapshot each required
  register once, stage modularly in local images, coalesce compatible changes,
  dirty-write each register once where legal, and document every additional
  hardware-mandated MMIO access.
- 2026-08-15: Required one MMIO-free `_PERIPH_Stage<Domain>Config()` helper per
  root-configuration structure member and required the public configuration API
  to commit all staged register images directly; private configuration commit
  helpers may not hide the public transaction's hardware writes.
- 2026-08-15: Required requests for fields that are not writable in the current
  hardware mode to fail before MMIO; applications explicitly own the public
  calls needed to leave and later restore that mode instead of one Driver call
  hiding intermediate mode writes.
- 2026-08-15: Prohibited private transaction structures that exist only to
  shorten signatures; independently required temporal register images remain
  explicit unless they form a stable reusable domain with their own invariant.
- 2026-08-15: Prohibited root configuration from reading or mutating NVIC
  delivery state; applications explicitly sequence IRQ sources and NVIC before
  transitioning the peripheral to its active operation state.
- 2026-08-15: Excluded IRQ-source enables from root configuration structures;
  applications must configure peripheral interrupt generation explicitly
  before independently enabling NVIC delivery.
- 2026-08-15: Defined root configuration as visible composition of reusable
  domain-staging helpers, assigned Read/Modify/Write and ordered commit
  ownership to public Driver APIs, and prohibited private helpers that shadow
  an entire public root transaction.
- 2026-08-15: Permitted narrowly named fixed-configuration service helpers
  when they validate their clock assumptions and delegate canonical root
  configuration, while retaining the prohibition on general frequency setters.
- 2026-08-15: Extended the retval list/value/colon layout to non-status return
  values and prohibited legacy entries without the list marker, code
  formatting, and colon.
- 2026-08-15: Required conjugate configuration/deconfiguration entry points to
  remain independent, prohibited either lifecycle function from calling its
  conjugate, and assigned lifecycle ordering and explicit reset decisions to
  the application.
- 2026-08-15: Established Core-owned `frequency_t` as the universal
  hertz-valued type and prohibited duplicate peripheral frequency aliases.
- 2026-08-15: Required conjugate APIs to have symmetric names and semantic
  scope, established root `Config` / `DeConfig` ownership, and prohibited
  frequency-targeting configuration functions while retaining observational
  frequency calculations.
- 2026-08-15: Required Driver and Codec transaction helpers to return
  `driver_status_t`; reserved `void` for inherently void interfaces and dumb,
  non-validating LL write primitives.
- 2026-08-15: Extended the exact function Doxygen layout to private helpers,
  required validation-specific return descriptions, and prohibited tab-aligned
  or period-terminated driver-status descriptions.
- 2026-08-15: Required validation functions to return `driver_status_t` and
  prohibited fallible predicates or compatibility wrappers from collapsing
  errors into raw Boolean results.
- 2026-08-15: Added compact-versus-expanded call layout rules.
- 2026-08-15: Required meaningful `//!` logic comments inside functions.
- 2026-08-15: Defined a Doxygen pass as documentation, source-style, and
  validation work rather than comment-only editing.
- 2026-08-15: Added banner-local macro alignment with two tabs after the
  section's longest macro name.
- 2026-08-15: Required fully braced multi-line switch cases.
- 2026-08-15: Preferred explicit if/else control flow over ternary expressions.
- 2026-08-15: Required peripheral-independent register behavior to live in
  RegOps, with peripheral layers retaining validation and hardware policy.
- 2026-08-15: Preferred simple 32-bit `UL` register-mask expressions, with a
  separate explicit full-register mask instead of special-case macro logic.
- 2026-08-15: Required `reg` for register representations, semantic variable
  names in shared helpers, and explicit copy-clear-set field staging.
- 2026-08-15: Required the exact status-reference layout shown above for
  documented driver statuses.
- 2026-08-15: Required per-instance hardware topology, such as Timer-to-RCC-bus
  ownership, to live in an indexed static LUT.
- 2026-08-15: Required LUTs to use the smallest direct element type and avoid
  metadata structures when the table stores only one value.
- 2026-08-15: Required every documented macro, including short constant
  macros, to carry an explicit `@def MACRO_NAME` tag.
- 2026-08-15: Defined the complete public-function Doxygen order, per-parameter
  Accepted/Expected Values blocks, referenced return type, exhaustive status
  list, and consistently formatted `@retval` descriptions.
