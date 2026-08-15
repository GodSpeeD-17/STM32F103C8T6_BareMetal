# Coding Preferences

This file records the repository owner's coding and documentation preferences.
Update it whenever a new preference is established, and consult it before every
code change, review, or Doxygen pass.

## Doxygen Pass Scope

A Doxygen pass is not limited to editing `/** ... */` blocks. It must include:

- Correct and complete file, group, function, parameter, return-value, note,
  precondition, and warning documentation where applicable.
- An explicit `@def MACRO_NAME` in the Doxygen block for every documented
  macro, including short one-line constant macros.
- Valid Doxygen command syntax with resolvable references.
- Concise `//!` comments inside functions that explain important logic,
  sequencing, preservation rules, hardware constraints, and side effects.
- Source formatting consistent with the call-layout rules below.
- A Doxygen validation run plus relevant compile, test, and diff checks.

A Doxygen pass is incomplete until every documented `#define` in scope has
been checked for an exact matching `@def` name and the audit reports zero
omissions. This applies equally to public, private, object-like, function-like,
and one-line macros; header guards without Doxygen blocks are excluded.

Use the repository's status-reference layout exactly:

```c
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Register image was captured
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An input pointer is `NULL`
```

Keep the list marker, `@ref`, backticks, colon, and single separating space in
this order for every documented driver status. Do not column-align `@retval`
descriptions with tabs or extra spaces, and do not terminate status
descriptions with a period.

Use the same list/value/colon layout for non-status return values, omitting
`@ref` when the value is a literal or range rather than a documented status:

```c
 * @retval - `0x00U`: The selector is not supported
 * @retval - `0x01U`: The selector is supported
```

Do not use the legacy `@retval VALUE Description` form.

## Function Doxygen Layout

Document every public and private function in this order:

1. `@brief`, followed by `@details` when behavior, ownership, sequencing, or
   side effects require explanation.
2. One `@param[in]`, `@param[out]`, or `@param[in,out]` entry per parameter.
3. An `Accepted values:` or `Expected values:` list immediately after each
   parameter whenever its valid input or output vocabulary can be stated.
4. `@returns @ref RETURN_TYPE "Function-specific operation status"` for
   status-returning functions.
5. Complete `@retval` entries for every status the implementation can return.
6. Applicable `@pre`, `@note`, and `@warning` entries.

Use this status-returning function format:

```c
 * @param[in] clockState Requested Timer clock-gate state
 * Accepted values:
 * - @ref DRIVER_STATUS_OFF : Disable the APB1 Timer clock gate.
 * - @ref DRIVER_STATUS_ON : Enable the APB1 Timer clock gate.
 * @returns @ref driver_status_t "Clock-state operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer APB1 clock gate was updated
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `clockState` was invalid
```

Validation helpers use an action-oriented `@brief` beginning with
`Validates`, a referenced `driver_status_t` return line whose quoted text names
the specific validation, and the same exact status-reference layout:

```c
 * @brief Validates that the Timer counter is stopped
 * @param[in] TIMx Timer peripheral instance
 * @returns @ref driver_status_t "Counter-state validation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer clock is enabled and the counter is stopped
 * @retval - @ref `DRIVER_STATUS_ERROR_BUSY`: Timer counter is running
```

Parameter documentation must be specific to that parameter. Do not combine
several parameters into one Accepted Values block, and do not omit a finite
selector/range list when the API defines one. Status lists must match the
implementation, including distinct null-pointer, invalid-argument, state,
busy, and timeout paths.

## Function-Local Logic Comments

Place a concise `//!` comment immediately before the operation or block it
explains:

```c
//! Reuse the shared apply path to keep batching and dirty writes consistent.
ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
```

Comments should explain why the operation exists or what invariant it protects.
Avoid comments that merely translate the following C statement into English.

## Function and Macro Call Layout

Keep a call on one line when it remains readable:

```c
ASSERT_DRIVER_STATUS(_TIM_ValidateClockEnabled(TIMx));
```

When a nested or argument-heavy call needs multiple lines, expand every nesting
level. Put each function or macro name on its own line, place its opening
parenthesis on the following line, use one argument per line, and align closing
parentheses with their call depth:

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

Do not expand short calls mechanically. Choose the compact or expanded form
based on readability and keep the chosen form consistent within the module.

## Macro Alignment

Align related `#define` values within each banner section. Find the longest
macro name in that section, place exactly two tab characters after that name,
and add enough tabs after every shorter name for all values to start in the
same column:

```c
/** @brief Microsecond delay chunk used by the millisecond blocking helper @def TIM_DRIVER_DELAY_MS_CHUNK_US */
#define TIM_DRIVER_DELAY_MS_CHUNK_US			((uint16_t) 1000U)
/** @brief Conservative polling-loop budget per requested microsecond @def TIM_DRIVER_DELAY_POLL_BUDGET_PER_US */
#define TIM_DRIVER_DELAY_POLL_BUDGET_PER_US		((uint32_t) 1024UL)
/** @brief Fixed setup allowance added to the polling-loop budget @def TIM_DRIVER_DELAY_POLL_BUDGET_BASE */
#define TIM_DRIVER_DELAY_POLL_BUDGET_BASE		((uint32_t) 1024UL)
```

Recalculate alignment independently for each banner section; do not use one
file-wide column.

Keep register-mask macros native to the 32-bit register width and prefer the
direct `0x01UL` shift expression. Support field widths `0U..31U`; use
`0xFFFFFFFFUL` explicitly when all 32 register bits are required. Document
that positioned bits beyond bit 31 are discarded instead of complicating the
macro to preserve out-of-range bits.

Use the `reg` typedef for register images, register masks, register field
values, and pointers to caller-owned register images. Reserve fixed-width
integer types for values that are not register representations, and use
`uintptr_t` for address arithmetic.

Use the Core-owned `frequency_t` typedef for every hertz-valued API return,
output, structure field, constant, and intermediate value. Do not introduce
peripheral-specific aliases such as `rcc_freq_t` or `tim_frequency_t` for the
same physical quantity. Prescaler selectors and dimensionless divider values
must retain their own semantic types rather than using `frequency_t`.

Prefer role-specific names such as `registerImage`, `positionedFieldMask`, and
`fieldPosition` over shortened names such as `regImage`, `mask`, `value`, and
`pos` inside shared register helpers.

Express register-field replacement as explicit copy, clear, and set
operations. Keep the final return separate so each preservation step remains
easy to inspect.

## Control Flow

Prefer explicit `if`/`else` branches over ternary expressions. The slightly
longer form is preferred because state mapping and error behavior remain easy
to scan.

Use fully braced, multi-line `switch` cases. Put assignments, `break`, and
returns on separate lines:

```c
//! Match by peripheral base address because instance macros are raw memory-mapped pointers.
switch ((uint32_t) TIMx)
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

Do not place a case assignment and `break`, or a default label and return, on
the same line.

## Validation and Fallible Boolean Results

Every public or private validation function must return `driver_status_t`.
Return `DRIVER_STATUS_SUCCESS` when the input is valid and the most
specific applicable error status when it is not. Do not return `uint8_t`,
`bool`, `0x00U`, or `0x01U` as a validation result.

Fallible predicates and state queries must preserve the distinction between a
legitimate negative state and an operation failure. They must not convert a
null pointer, invalid argument, unavailable clock, invalid hardware state, or
other error into `0`, `false`, or an apparent OFF/not-pending result.

Use one of these contracts:

- Validation-only helper: return `DRIVER_STATUS_SUCCESS` or a specific
  `DRIVER_STATUS_ERROR_*` value.
- Truly binary state getter: return `DRIVER_STATUS_OFF` or
  `DRIVER_STATUS_ON` directly, while preserving distinct error statuses.
- Fallible data, mask, or extensible-state query: return operation status and
  publish the result through an output pointer only after the operation
  succeeds.

Compatibility wrappers must not collapse a status-returning API into a raw
Boolean result. Remove or migrate such wrappers instead of treating an error
as a valid negative result.

Driver and Codec orchestration, staging, commit, validation, and cleanup
helpers that participate in a status-returning call chain must also return
`driver_status_t`. Do not declare such a helper `void` merely because its
current LL register operations cannot report failure. Return
`DRIVER_STATUS_SUCCESS` after the operation and preserve status propagation at
the caller so later validation or hardware-error reporting does not require an
API-contract change.

Reserve `void` for interfaces whose contract is inherently void, such as an
interrupt-handler ABI, and for deliberately dumb LL write primitives that own
no validation, sequencing, or fallible policy.

## Layer Ownership and Reuse

Place behavior that is independent of a specific peripheral in the lowest
shared layer that can express it safely. Peripheral layers should retain only
their own validation, register selection, sequencing, and hardware policy.

For example, compare-and-write behavior belongs in `RegOps_WriteIfChanged()`.
Timer may wrap it to validate a Timer instance and select CR1, PSC, ARR, or CNT;
GPIO and RCC can later reuse the same primitive while preserving their own
peripheral-specific rules.

When hardware topology differs by peripheral instance, keep the mapping in a
static LUT indexed by the driver's stable instance index. Use the smallest
element type that represents the mapping directly; for example, a Timer-to-bus
table should be an array of `rcc_bus_t`, not an array of one-field metadata
structures. Shared logic should consume the mapped value instead of hard-coding
one bus or duplicating per-instance branches.

## Conjugate API Naming and Scope

Conjugate API pairs must be symmetric in both naming and semantic scope. Use
the same subject in both names, such as `TIM_Config()` / `TIM_DeConfig()` or
`TIM_GetIRQEvents()` / `TIM_AckIRQEvents()`. Do not label two functions as a
pair when one owns only a narrow subdomain and the other resets or mutates the
complete peripheral.

A root configuration type such as `tim_config_t` represents every currently
admitted configuration domain. Its root configuration API applies that whole
object, while its deconfiguration conjugate restores the complete peripheral
to the documented reset state. Conjugate lifecycle entry points remain
independent: a configuration function must not call its deconfiguration
conjugate, and a deconfiguration function must not call its configuration
conjugate. The application owns their ordering and explicitly requests a reset
when required. Configuration preserves deferred or unrepresented domains until
their contracts are admitted.

Do not expose convenience functions that configure a peripheral to a requested
frequency. Callers provide explicit register-semantic configuration values.
Calculated-frequency getters are acceptable because they observe and report
programmed state without mutating configuration.

## Preference Log

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
  list, and tab-aligned `@retval` descriptions.
