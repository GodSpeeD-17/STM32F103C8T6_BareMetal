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

Every macro or symbolic constant used as a Doxygen `@ref` target must be
enclosed in backticks. Apply this consistently in accepted/expected-value
lists, parameter descriptions, return descriptions, notes, warnings, and
ordinary Doxygen prose. Keep the backticks immediately around the referenced
identifier:

```c
 * - @ref `PERIPH_EVENT_UPDATE`: Update event
 * - Any non-empty combination contained by @ref `PERIPH_EVENT_ALL`
 * @note Start operation with @ref `DRIVER_STATUS_ON`
```

Do not leave macro or symbolic-constant reference targets unquoted. This
backtick rule does not apply to referenced types, structures, members, groups,
or functions unless another formatting rule explicitly requires code styling
for them.

## Function Doxygen Layout

Document every public and private function in this order:

1. `@brief`, followed by `@details` when behavior, ownership, sequencing, or
   side effects require explanation.
2. One `@param[in]`, `@param[out]`, or `@param[in,out]` entry per parameter.
3. An `Accepted values:` or `Expected values:` list immediately after each
   parameter whenever its valid input or output vocabulary can be stated.
4. A function-specific `@returns` line naming the returned status type for
   status-returning functions.
5. Complete `@retval` entries for every status the implementation can return.
6. Applicable `@pre`, `@note`, and `@warning` entries.

Use this status-returning function format:

```c
 * @param[in] operationState Requested Timer operation state
 * Accepted values:
 * - @ref `DRIVER_STATUS_OFF` : Stop Timer counter operation.
 * - @ref `DRIVER_STATUS_ON` : Start Timer counter operation.
 * @returns @ref driver_status_t "Operation-state operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer counter operation state was updated
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `operationState` was invalid
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
/** @brief Microsecond delay chunk used by the millisecond blocking helper @def TIM_DRIVER_BLOCKING_DELAY_MS_CHUNK_US */
#define TIM_DRIVER_BLOCKING_DELAY_MS_CHUNK_US			((uint16_t) 1000U)
/** @brief Conservative polling-loop budget per requested microsecond @def TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_PER_US */
#define TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_PER_US		((uint32_t) 1024UL)
/** @brief Fixed setup allowance added to the blocking polling-loop budget @def TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_BASE */
#define TIM_DRIVER_BLOCKING_DELAY_POLL_BUDGET_BASE		((uint32_t) 1024UL)
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

## Structured Configuration and Transaction Decomposition

A root configuration structure is a structure of independently coherent
configuration domains. The root public configuration function represents the
largest admitted configuration transaction for that peripheral. It must
visibly orchestrate each domain represented by the root structure; do not hide
the entire operation behind a private `_PERIPH_ApplyConfig()` helper that merely
duplicates the public function's authority.

Every nested configuration structure that represents an independently useful
and admitted operation must normally have a symmetric public grouped `Get` /
`Set` pair. Deliberately asymmetric hardware actions remain exceptions and
must document why no conjugate exists. The root function and grouped setter
must reuse the same narrowly scoped private staging helper; the grouped getter
uses the corresponding extraction path. Derive helpers from reusable
configuration domains and shared invariants, not merely to shorten a public
function.

Use this generic ownership model:

```c
typedef struct _periph_config_t
{
	periph_timebase_config_t	timebase;
	periph_counter_config_t		counter;

} periph_config_t;
```

Do not place interrupt-request source enables inside a root configuration
structure. IRQ-source enablement must remain an explicit application action so
the call site proves that interrupt generation was intentional. Root
configuration preserves the peripheral IRQ-source register, and the
application separately configures peripheral sources before enabling NVIC
delivery.

Use this generic sequence:

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
NVIC_IRQ_ClearPending(PERIPH1_IRQn);
NVIC_IRQ_Enable(PERIPH1_IRQn);
ASSERT_DRIVER_STATUS(PERIPH_SetOperationState(PERIPH1, DRIVER_STATUS_ON));
```

Clock-gate ownership remains explicit and outside the peripheral Driver. The
application uses the RCC Driver to enable the required peripheral gate before
configuration. A peripheral Driver may query RCC to validate that precondition,
but it must not expose duplicate peripheral-prefixed clock APIs or enable,
disable, restore, or otherwise mutate the gate inside `Config()`, `DeConfig()`,
grouped configuration, operation-state, IRQ, or action APIs.

`DeConfig()` restores the peripheral register bank through the peer RCC reset
service when that is the hardware-defined reset mechanism, but it leaves the
application-owned clock gate and NVIC delivery state unchanged. The application
explicitly decides when either external resource is disabled. This keeps the
full lifecycle visible at the call site:

```text
RCC clock enable
  -> peripheral base configuration
  -> peripheral IRQ-source configuration
  -> NVIC pending-state cleanup and delivery enablement
  -> peripheral operation enablement
```

Omitting `PERIPH_SetIRQSources()` means the root configuration leaves existing
peripheral IRQ-source state unchanged. Disabling sources is equally explicit;
the application passes the owned source mask with `DRIVER_STATUS_OFF`.

Root peripheral configuration must not read, validate, clear, disable, or
enable NVIC delivery state. The application owns the explicit ordering between
base configuration, peripheral IRQ-source enablement, pending-line cleanup,
NVIC delivery enablement, and the final transition to active peripheral state.

The corresponding staging helpers each accept only one configuration domain
and the caller-owned register images that domain can modify:

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

A staging helper must:

- perform only the transformation described by its name and
  configuration-domain input;
- validate its own pointer/domain contract and return `driver_status_t`;
- transform caller-owned, non-volatile register images without performing
  MMIO, clock, reset, NVIC, operation-state, or cleanup work;
- use Codec functions for individual field encoding instead of duplicating
  register placement in the Driver;
- stage through local working images and publish all output images only after
  every fallible transformation succeeds; and
- preserve every register field outside its declared domain.

Every structure contained by a public root configuration object has one
corresponding private Driver `_PERIPH_Stage<Domain>Config()` helper. That helper
owns the atomic local-copy/publication boundary for its structure and invokes
the grouped Codec transformation for field placement. It must not stage policy
or register images outside the fields represented by that structure. The
architecture requires one reusable staging path per configuration member.

Public configuration APIs own the Read/Modify/Write transaction. Their generic
flow is:

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

The root function must not implement a second copy of the grouped staging
logic, and it must not call public grouped setters when doing so would create
multiple partially committed transactions. It reuses their private staging
helpers, stages the whole root request before the first write, and then owns one
ordered commit. Conversely, a grouped public setter reads and commits only the
registers required by its own domain.

Private helpers stage cached values but do not commit configuration MMIO. The
public configuration API directly compares and writes its cached images in the
required hardware order, including any temporary policy, action-register, or
restoration sequence. This keeps the public function's maximum authority and
actual hardware cost visible. Only deliberately mechanical LL register-write
primitives remain `void`.

For Timer, this means `TIM_Config()` visibly composes the staging paths for
`tim_config_counter_t` and `tim_config_timebase_t` while preserving
`TIMx_DIER`.
`TIM_GetCounterConfig()` / `TIM_SetCounterConfig()` and
`TIM_GetTimeBaseConfig()` / `TIM_SetTimeBaseConfig()` provide the grouped
domain pairs. Their setters reuse the respective staging paths, while the root
transaction performs one all-base-domain ordered commit. No private helper
shadows all of `TIM_Config()`, and no configuration path calls
`TIM_DeConfig()`.
Applications configure Timer interrupt generation separately through
`TIM_SetIRQSources()`.

## MMIO Access Minimization and Modular Transactions

Modularity must not multiply volatile register accesses. Helper boundaries
separate validation, staging, and commit responsibilities; they do not grant
each helper permission to reread or rewrite the same hardware register.

For each coherent Driver transaction:

1. validate the complete request and every live precondition that can fail;
2. snapshot each required volatile register exactly once;
3. pass caller-owned `reg` images through narrow, MMIO-free staging helpers;
4. coalesce every compatible domain or field change into the final register
   image;
5. dirty-write each changed register exactly once when hardware semantics
   permit; and
6. perform additional reads or writes only when a named hardware requirement
   makes them necessary, such as an unlock sequence, mode transition,
   write-zero-to-clear or write-one-to-clear behavior, read-to-clear behavior,
   or a preload/update-event commit.

Hold the declared exclusive application ownership or transaction guard across
the complete snapshot/stage/commit interval. Do not reread a cached
configuration register solely to repeat a precondition check immediately
before commit; if concurrency must be supported, define and acquire an explicit
guard rather than weakening the cached-image transaction model.

Do not reread a register merely because multiple staging helpers consume its
fields. Do not let separate helpers commit partial images when the public API
owns one coherent transaction. Every additional MMIO access must be justified
by the peripheral contract and documented beside the sequence that requires
it. Correct hardware ordering takes precedence over forcing an unsafe
single-write implementation.

Do not introduce a transaction structure merely to shorten a helper signature
or hide several temporal images of the same register. Pass independently
required `reg` images explicitly so the helper's inputs, outputs, and authority
remain visible. A structure is appropriate only when the grouped data forms a
stable reusable domain with its own invariant—not when it is only an argument
container.

When hardware makes a requested field read-only or otherwise non-writable in
the current mode, return the appropriate `driver_status_t` error before the
first write. Do not hide a multi-step mode transition inside one configuration
call merely to make the request succeed. The application must explicitly call
the public APIs that leave the restrictive mode, apply the requested field,
and restore the desired mode. This keeps lifecycle and mode-transition intent
visible while each admitted transaction retains one coherent final image and
the minimum register-access count.

Use this generic rejection shape before staging the final image:

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

The application then performs the required mode changes as separate public
transactions; the Driver does not synthesize those calls or intermediate MMIO
writes internally.

Use this generic transaction shape:

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

If hardware requires an intermediate image, the public transaction performs
the minimum ordered multi-write sequence directly. Its Doxygen and `//!` logic
comments must name the hardware rule that makes each additional access
mandatory.

## Conjugate API Naming and Scope

Conjugate API pairs must be symmetric in both naming and semantic scope. Use
the same subject in both names, such as `TIM_Config()` / `TIM_DeConfig()` or
`TIM_GetIRQEvents()` / `TIM_AckIRQEvents()`. Do not label two functions as a
pair when one owns only a narrow subdomain and the other resets or mutates the
complete peripheral.

A root configuration type such as `tim_config_t` represents every currently
admitted base-configuration domain intentionally included in that object. Its
root configuration API applies that whole object, while preserving explicitly
separate operational domains such as IRQ-source enables. Its deconfiguration
conjugate restores the complete peripheral to the documented reset state.
Conjugate lifecycle entry points remain independent: a configuration function
must not call its deconfiguration conjugate, and a deconfiguration function
must not call its configuration conjugate. The application owns their ordering
and explicitly requests a reset when required. Configuration preserves
deferred, unrepresented, and explicitly separated domains.

Do not expose general-purpose convenience functions that configure a
peripheral to an arbitrary requested frequency. Callers provide explicit
register-semantic configuration values. A narrowly named service-bootstrap
helper is acceptable when a concrete admitted service requires one fixed
configuration, validates its documented clock assumption, and delegates the
canonical root configuration API. For example, `TIM_ConfigForBlockingDelay()` may
configure the dedicated blocking polling-delay service for a validated 72 MHz Timer
kernel clock; it must not become a general frequency setter.

Calculated-frequency getters are acceptable because they observe and report
programmed state without mutating configuration.

## Preference Log

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
  list, and tab-aligned `@retval` descriptions.
