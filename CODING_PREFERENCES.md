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

## Two-Part Peripheral Documentation Model

Every canonical peripheral `.md` page must be self-explanatory and contain
exactly two primary teaching parts in this order:

1. **Theory with Register Mapping Bridge**
2. **Implementation with Theory Bridge**

The **Theory with Register Mapping Bridge** part explains the peripheral
without requiring source-code knowledge. It must cover the peripheral's
purpose, terminology, state model, hardware flow, peer interactions, and the
significance of every register in the supported scope. Its register mapping
must state the owner, address/offset, width, implemented range, access class,
special read/write semantics, side effects, and relationships between
registers.

The **Implementation with Theory Bridge** part maps that complete hardware
model into the repository. It must trace each theoretical state or action
through its Core C member, LL access, Codec transformation or documented
no-Codec reason, Driver transaction, public API, volatile access width,
ordering, validation, preservation, synchronization, concurrency, and
shared-resource rules. It must also explain deliberately omitted access
directions or lower-layer functions.

The first part answers **what the hardware means and which registers express
it**. The second answers **how this project implements that theory and why the
implementation has its present shape**. Do not interleave these parts in a way
that forces a reader to understand source symbols before learning the hardware
model.

The peripheral `.md` file is the single canonical long-form page for that
peripheral's theory, architecture, register model, layer ownership, and
implementation mapping. Give its top-level Markdown heading a stable explicit
Doxygen page identifier. The peripheral's public Driver and LL Doxygen groups
must link to that page with `@ref`. Source Doxygen must not duplicate the
peripheral theory. File/group comments summarize scope and ownership, while
individual API comments document only their local parameters, results,
preconditions, side effects, exact hardware transaction, and safety warnings.

The generated project documentation must use a concise Markdown main page as a
navigation index. That page references each documentation-ready peripheral
`.md` page and directs readers to the generated module/API reference; it does
not duplicate the peripheral guides. `Doxyfile` must include canonical
peripheral pages in `INPUT` and configure the navigation index through
`USE_MDFILE_AS_MAINPAGE`.

Only current, reviewed peripheral guides belong in the generated project
documentation. Mutable audit scratchpads, TODO files, superseded architecture
snapshots, and internal planning records remain excluded unless they are
explicitly promoted to current user-facing documentation. A new peripheral is
not documentation-complete until its page is linked from both the project
navigation index and the relevant generated Doxygen groups.

For special registers, explicitly distinguish stored state from an action
port in the canonical peripheral `.md`. Explain write-one-to-set,
write-one-to-clear, write-zero-to-clear, read-clear, FIFO, data-port,
keyed-write, and write-only behavior before describing the corresponding C
access. Source Doxygen repeats only the operation-specific warning required to
use an accessor safely. A C `volatile` declaration communicates access
generation but does not, by itself, document these hardware semantics.

Use the repository's Doxygen return-value layout exactly:

```c
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Register image was captured
 * @retval - @ref `DRIVER_STATUS_ERROR_NULL_PTR`: An input pointer is `NULL`
```

For status-returning functions, retain the list marker, reference the symbolic
status with a backtick-wrapped `@ref` target, and separate the description with
one colon. Do not terminate status descriptions with a period.

The configured Doxygen version may report repeated return-value warnings
because it parses the list marker as the return-value key. Those exact `'-'`
warnings are an accepted consequence of the repository display convention;
do not rewrite the documented house style to silence them. All other Doxygen
warnings remain subject to the normal validation pass.

Use the corresponding list layout for non-status return values:

```c
 * @retval - `0x00U`: The selector is not supported
 * @retval - `0x01U`: The selector is supported
```

Every macro or symbolic constant used as a Doxygen `@ref` must place the target
inside backticks. Apply this consistently in accepted/expected-value lists,
parameter descriptions, return descriptions, notes, warnings, and ordinary
Doxygen prose:

```c
 * - @ref `PERIPH_EVENT_UPDATE`: Update event
 * - Any non-empty combination contained by @ref `PERIPH_EVENT_ALL`
 * @note Start operation with @ref `DRIVER_STATUS_ON`
```

Do not add a second quoted display label after the `@ref` target. References to
types, structures, members, groups, or functions remain unwrapped unless the
surrounding repository style explicitly requires code styling.

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
 * - @ref `DRIVER_STATUS_OFF`: Stop Timer counter operation
 * - @ref `DRIVER_STATUS_ON`: Start Timer counter operation
 * @returns @ref driver_status_t "Operation-state operation status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Timer counter operation state was updated
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: @p `TIMx` / @p `operationState` was invalid
```

Validation helpers use an action-oriented `@brief` beginning with
`Validates`, a referenced `driver_status_t` return line whose quoted text names
the specific validation, and the same repository return-value layout:

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

Every function body must contain at least one meaningful `//!` logic comment,
including one-line adapters, getters, setters, startup handlers, and minimal
interrupt handlers. For a thin function, explain why direct delegation, an
atomic read, or a bounded interrupt-side operation is the correct ownership
choice. Function-level Doxygen does not replace this implementation-local
explanation.

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

Group raw register-field macros under one logical banner per owning hardware
register. Within each register banner, order fields from the least-significant
implemented bit toward the most-significant implemented bit. When two
documented views begin at the same bit, keep each view internally complete and
place the broader register/subregister view before its contained fields.

Use the owning block, register, and field in every field-macro root:
`BLOCK_REGISTER_FIELD`. A single-bit field exposes `_Pos`, `_Msk`, and
the unsuffixed mask alias. A multi-bit field exposes `_Pos`, `_Width`,
`_Msk`, and the unsuffixed mask alias, in that order. Position and width
macros use `reg_bit_pos_t` and `reg_field_width_t`; mask macros use
`REG_BIT_MASK()` or `REG_FIELD_MASK()`.

Use tab characters, not runs of spaces, for macro value alignment and for the
leading indentation of multi-line macro continuations. The single lexical
separator after `#define` and the conventional ` *` inside Doxygen blocks are
not indentation and remain spaces.

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

Place every raw register-field macro in the Core register header of the
hardware block that physically owns the register, even when another Driver
consumes that field. For example, `SCB_AIRCR_xxx` symbols belong in
`stm32f1xx_scb.h`; the NVIC stack may consume `AIRCR.PRIGROUP` without owning
or duplicating its definitions. Compatibility headers may include the owner
header to preserve macro visibility, but they must not redeclare the macros.

When a Core register structure models named register fields, expose the
hardware word as a register-member union with a full-width `.REG` image and a
named `.BIT` field view, following the Timer register-map pattern. Keep the
fields in least-significant-bit-first order and represent every gap explicitly
with a reserved field so the view totals exactly 32 bits. If one physical bit
range has different read and write meanings, place named views such as
`.BIT.READ` and `.BIT.WRITE` inside the register union rather than selecting
one misleading interpretation.

Use `.REG` as the canonical LL transaction path. A `.BIT` view documents and
exposes field placement, but it does not authorize compiler-generated
read-modify-write accesses where the hardware contract requires a staged
full-register transfer. Keyed, action, write-only, and write-one-to-clear
register transactions must use the appropriate full-register operation.

Centralize each peripheral LL's ordinary full-width volatile access in one
generic pointer-based read primitive and one generic pointer-based write
primitive. Named register accessors select the appropriate `.REG` pointer and
delegate to those primitives; they must not repeat direct dereference or
`RegOps_Read()` / `RegOps_Write()` mechanics. Keep the named surface symmetric
where hardware permits. Preserve truthful asymmetry for read-only, write-only,
and action-port registers, and document why an unavailable direction or
conjugate does not exist. Semantic helpers such as a write-to-clear reset may
delegate through the corresponding named register writer.

Do not centralize peripheral instance/capability predicates or
peripheral-specific operating limits in `stm32f1xx_defines.h`. Introduce them
only when required and keep them inside the respective peripheral stack; for
example, oscillator and clock-frequency limits belong to RCC.

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
ASSERT_DRIVER_STATUS(NVIC_ClearPendingIRQ(PERIPH1_IRQn));
ASSERT_DRIVER_STATUS(NVIC_EnableIRQ(PERIPH1_IRQn));
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

Every public getter for a mutable operation state must have its symmetric
setter, such as `PERIPH_GetOperationState()` /
`PERIPH_SetOperationState(operationState)`. When one state domain accepts both
`DRIVER_STATUS_OFF` and `DRIVER_STATUS_ON`, prefer that single Get/Set pair over
combining a getter with separate public `Disable()` and `Enable()` functions.
Separate action verbs remain appropriate only when the hardware actions are
genuinely asymmetric and cannot be represented truthfully as one state setter;
document that exception explicitly.

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

## Application Template Ownership and Naming

Keep startup declarations, linker-symbol declarations, the vector table, and
application-service policy inside each project. The shared Driver root must not
own or inject a project's startup implementation.

Name project-owned Template service modules `app_*.*`, including
`app_startup.[ch]`. Retain conventional filenames only for `main.[ch]` and
`syscalls.c`. Reusable SysTick hardware access belongs to the shared
`BareMetal/Driver/SysTick` stack and retains `systick.[ch]` plus the direct
`SysTick_` public-function prefix. Application time state and the strong
`SysTick_Handler()` definition belong to the project-owned `app_time` service;
the handler performs only the minimum state publication needed by main context.
Symbols called by the processor, linker, or C library retain their required ABI
names; other project-owned public service functions use the `App_` prefix.

Project include directories take precedence over shared Driver include
directories so a project-local `startup.h` cannot resolve to legacy shared
startup content.

Every application Template header that declares a function or object with
external linkage must wrap those declarations in an `extern "C"` guard for C++
consumers. Macro-only configuration headers do not require a linkage guard.

Application Template files use `stm32f1xx_data_types.h` as their direct source
of fixed-width integers, shared physical quantities, register vocabulary, and
driver statuses. Do not include `<stdint.h>` or another standard scalar-type
header directly from a Template file. Standard headers that provide a distinct
service, such as `<errno.h>`, remain direct dependencies where that service is
used.

## Section Banner Formatting

Write section-banner titles left-aligned without decorative whitespace
padding. Keep ordinary section titles between the existing border lines:

```c
// ==================================================================================================== //
// Public API
// ==================================================================================================== //
```

Do not center section titles with runs of spaces or tabs. Follow the established
Timer-header style for structural boundaries: use one `// Header Guard` line
immediately before the opening `#ifndef` / `#define`, use
`// --- C++ Compatibility ---` at both C++ linkage boundaries, and close the
file directly with `#endif /* HEADER_GUARD */`. Do not add redundant
`Header Guard End`, `C++ Compatibility End`, or `Documentation Group` banner
sections.

Use banners to express logical API hierarchy, not merely to divide a long file.
A major `=` banner owns one coherent domain such as configuration, operation
control, state observation, tick storage, or interrupt handling. When a domain
contains distinct pairs or subdomains, place each beneath a left-aligned `-`
sub-banner. Do not club unrelated control, state, and data APIs beneath one
generic banner. Header and source files must use the same banner names and API
order.

Within every lifecycle or operation-control conjugate pair, place the
teardown/release operation before the setup/acquire operation: `Destroy` before
`Create`, `DeConfig` before `Config`, `Disable` before `Enable`, and `Stop`
before `Start`. Apply this order consistently to declarations, definitions, and
documentation.

## Application Template File Documentation

Use the Timer module as the concrete Doxygen and file-layout reference for
application Template files, subject to later explicit repository-owner
preferences such as left-aligned section titles. Every file begins with the
standard `@file`, `@author`, `@brief`, `@version`, `@date`, and `@details`
metadata layout.

The `@details` block must make the file's architectural position understandable
without reading another file. Use uniquely identified `@section` blocks for
hierarchy, responsibility, and dependency boundary. State the file's layer or
cross-cutting role, its direct users, its direct dependencies, and its
prohibited ownership. Never use an unexplained arrow as a substitute for a
named `includes`, `calls`, `uses`, or `is invoked by` relationship.

Number application architecture layers from hardware upward. Layer 1 is always
the hardware-nearest project/Driver access layer. Increasing layer numbers must
represent progressively more software-only service, policy, behavior, and
orchestration responsibility. A higher numbered layer may depend downward; a
lower numbered layer must not depend upward.

Every application configuration macro must explain more than its literal
value. Its Doxygen documents its architectural significance, the capability or
behavior it controls, its direct consumers, every accepted value, relevant
cross-macro or hardware constraints, and what defining it does not perform.
Feature flags must document both enabled and disabled behavior. Hardware
selection macros must document exclusive ownership and every companion mapping
that must remain consistent.

## Preference Log

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
