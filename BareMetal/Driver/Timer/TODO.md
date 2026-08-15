# Timer Refactor TODO

This checklist tracks the commit-sized Timer refactor sequence. Complete one
item, verify it, commit it, then move to the next item.

The normative plan and closure gates now live in
[`../DRIVER_STACK_TOP_DOWN_AUDIT.md`](../DRIVER_STACK_TOP_DOWN_AUDIT.md). The
completed entries below record historical implementation milestones; they do
not override safety gaps reopened by the top-down audit.

## Scope

- [x] Limit the STM32F103C8T6 driver to the implemented general-purpose timers `TIM2`, `TIM3`, and `TIM4`.
- [ ] Preserve existing public `TIM_*` API names where practical during the layer split.
- [x] Preserve existing public `TIMx_*` selector names initially to reduce churn.
- [x] Keep public Timer configuration structures as the primary modular configuration API.
- [x] Defer broad public selector/API naming cleanup until the layer boundaries are correct.

## Step Plan

- [x] Document intended Timer architecture and pending deviations in this directory.
- [x] Introduce `Inc/timer_data_types.h` for Timer scalar aliases and shared plain data aliases.
- [x] Use the Core-owned `frequency_t` alias for every Timer frequency value instead of a duplicate Timer-specific typedef.
- [x] Introduce `Inc/timer_defines.h` for public selectors, defaults, validation helpers, and pure utilities.
- [x] Move Timer public selectors/defaults out of `stm32f1xx.h` while keeping Core raw-only.
- [x] Add `Inc/timer_ll.h` with dumb register read/write helpers only.
- [x] Add `Inc/timer_codec.h` and `Src/timer_codec.c` with private encode/decode helpers and public extract/stage image APIs.
- [x] Refactor `Inc/timer_config.h` into clean timer-independent configuration structures.
- [x] Refactor `Inc/timer.h` into public API only with `driver_status_t` contracts and no inline hardware access.
- [x] Refactor `Src/timer.c` orchestration for config-owned fields to use validation, LL, codec staging, dirty writes, and status returns.
- [x] Remove implicit RCC clock-gate enable side effects from grouped and scalar Timer `Get`/`Set` APIs.
- [x] Add `Accepted values` and `Expected values` Doxygen scope details to `timer.h`, `timer_config.h`, and `timer_codec.h`.
- [x] Standardize `timer.h` public API `@returns` and `@retval` Doxygen wording around function-specific operation status.
- [x] Implement the first-pass Timer config update-event sequence around `EGR.UG`, `CNT`, and generated `SR.UIF` (full-domain closure is reopened below).
- [x] Remove general frequency-targeting configuration functions; applications now provide explicit `tim_config_t` prescaler/timebase data.
- [x] Add `TIM_ConfigDelay1MHz()` as the single service-specific fixed-frequency exception for a validated 72 MHz Timer kernel clock.
- [x] Add public `TIM_DelayUs()` blocking polling helper for Timers explicitly configured with a 1 MHz programmed tick.
- [x] Add public `TIM_DelayMs()` blocking polling wrapper over `TIM_DelayUs(TIMx, 1000U)`.
- [x] Reorganize `timer.c` public implementations under the same banner and sub-banner order used by `timer.h`.
- [x] Add file-level Doxygen `@section` blocks to `timer.c` for scope, field ownership, and source layout.
- [x] Implement the first-pass Timer IRQ APIs with codec-owned DIER/SR mapping and Timer-owned NVIC coordination (source/event/delivery ownership is reopened below).
- [x] Update Timer polling/IRQ examples and shared startup delay users to the new public API shape.
- [x] Finish the Timer Doxygen pass for the implemented public APIs.
- [x] Build the Timer examples and one startup-delay consumer.

## Completed Deviations

- [x] Public Timer selector enums and defaults were moved out of `stm32f1xx.h`.
- [x] Timer LL layer was introduced.
- [x] Timer codec layer was introduced.
- [x] CR1, CCMR, CCER, DIER, and SR field placement was centralized in codec where current codec APIs exist.
- [x] `timer_config.h` was reduced to clean timer-independent public configuration structures.
- [x] Public Timer configuration structures now live in dedicated public config header `timer_config.h`.
- [x] `timer.h` was reduced to public API declarations with no inline hardware access.
- [x] `timer.c` now accesses Timer registers through LL and RCC through the RCC driver API.
- [x] First-pass public APIs now return `driver_status_t`.
- [x] First-pass driver validates Timer instances and config-owned selector compatibility.
- [x] First-pass driver reads only required registers for config-owned fields.
- [x] First-pass driver writes only changed staged images for config-owned fields.
- [x] Remove Timer-owned RCC clock-gate query/mutation APIs; applications use
  the RCC driver explicitly before invoking Timer APIs.
- [x] Counter operation state APIs `TIM_GetOperationState()` and `TIM_SetOperationState()` were exposed.
- [x] Binary state codec extractors return decoded `DRIVER_STATUS_OFF` or `DRIVER_STATUS_ON` directly.
- [x] Core shared CCMR raw-value macros were normalized to STM32-style `CCxS`, `OCxM`, `ICxPSC`, and `ICxF` notation.
- [x] `TIM_DeConfig()` requires an enabled application-owned clock gate, pulses
  the matching RCC peripheral reset, and leaves both RCC gate and NVIC state
  unchanged.
- [x] Grouped/scalar `Get` and `Set` APIs now require the clock gate to already be enabled and return `DRIVER_STATUS_ERROR_STATE` when it is disabled.
- [x] `timer.h`, `timer_config.h`, and `timer_codec.h` now document caller input scope with `Accepted values` and decoded/output scope with `Expected values`.
- [x] `timer.h` public APIs now use function-specific `@returns @ref driver_status_t "... - Operation Status"` labels and parameter-specific `@retval` wording.
- [x] `TIM_Config()` and `TIM_DeConfig()` remain independent root lifecycle
  entry points; neither calls the other and the application owns their
  ordering.
- [x] `TIM_Config()` directly delegates every admitted `tim_config_t` domain to its narrow transaction helper without a root-shadow wrapper.
- [x] Remove Timer IRQ sources from `tim_config_t`; `TIM_Config()` preserves
  DIER without reading or modifying NVIC delivery, and applications explicitly
  sequence `TIM_SetIRQSources()`, NVIC delivery, and the active-state transition.
- [x] Stage all timebase/commit images and validate the stopped-counter precondition before the first MMIO write.
- [x] Timer-to-RCC-bus ownership is centralized in a static `rcc_bus_t` LUT so future APB mappings do not change frequency logic.
- [x] `TIM_DelayUs()` verifies an exact 1 MHz tick and uses bounded polling with cleanup on timeout.
- [x] `TIM_DelayMs()` now provides a minimum blocking millisecond delay by composing repeated `TIM_DelayUs(TIMx, 1000U)` chunks.
- [x] Shared startup delay consumers use `TIM_ConfigDelay1MHz()` instead of duplicating the canonical delay configuration object.
- [x] `timer.c` public implementation order now mirrors `timer.h`, including conjugate getter/setter sub-banners and final blocking-delay helpers.
- [x] `timer.c` file overview now uses Doxygen `@section` blocks for scope, field ownership, and source layout.
- [x] `_TIM_ClockEnabled()` was replaced by `_TIM_ValidateClockEnabled()` for narrow API clock-gate precondition checks.
- [x] `TIM_Config()` and `TIM_DeConfig()` validate the application-owned Timer
  clock-gate precondition without changing the gate.
- [x] A first-pass stopped guard exists for timebase and DIR/CMS setters; atomic ordering and complete mode validation remain reopened.
- [x] First-pass Timer IRQ source state, pending flags, and acknowledgements use codec-owned DIER/SR mapping and instance NVIC coordination; the target source/event/delivery split remains reopened.
- [x] Replace the first-pass IRQ surface with `TIM_GetIRQSources()`,
  `TIM_SetIRQSources()`, `TIM_GetIRQEvents()`, and `TIM_AckIRQEvents()`.
- [x] Separate `tim_irq_source_t` from `tim_event_flag_t`, include trigger and
  overcapture vocabulary, remove `tim_irq_enable_t` and all six legacy IRQ
  wrappers, and leave generic NVIC delivery under NVIC/application ownership.
- [x] Make generic capture/compare event acknowledgement mode-aware and reject
  input-capture lanes until the deferred capture-consumption contract exists.
- [x] A host codec suite verified CR1/timebase preservation and DIER/SR IRQ behavior during the refactor; its repository-local test artifact is intentionally not retained.

## Reopened P0 Safety Work

These items must close before channel/PWM implementation begins:

- [x] Split `_TIM_ApplyCounterConfig()` and `_TIM_ApplyTimeBaseConfig()` so
  grouped and root transactions reuse the existing grouped Codec staging paths
  through one `_TIM_Stage<Domain>Config()` helper per configuration structure;
  public APIs directly own the required MMIO ordering.
- [x] Make `TIM_Config()` visibly compose all `tim_config_t` domain-staging
  helpers before its first write; make `TIM_SetCounterConfig()` and
  `TIM_SetTimeBaseConfig()` reuse the same staging helpers while retaining
  ownership of their own narrow Read/Modify/Write transactions.
- [x] Make `TIM_Config()` and both grouped base-configuration setters complete
  validation and Codec staging before their first Timer-register write; a
  precommit BUSY/error result leaves Timer register state unchanged.
- [x] Treat MMIO access count as a transaction constraint: snapshot each
  required Timer register once, coalesce compatible staged changes, and retain
  additional writes only for documented hardware-mandated transitions or
  commit semantics.
- [x] Reject a counter-direction change while the current mode makes `CR1.DIR`
  read-only; each admitted counter-configuration call stages one final `CR1`
  image and dirty-writes it at most once, while the application owns any
  explicit edge-aligned/direction/center-aligned call sequence.
- [x] Remove scalar-setter public-to-public delegation that repeated Timer
  snapshots; keep temporal register images explicit and reuse only the narrow
  counter-transition and timebase-update staging/commit sequences.
- [ ] Extend the same no-write-on-error and single-cleanup proof to the remaining
  Timer lifecycle and action transactions.
- [ ] Restrict the first safe root-config contract to exclusive application ownership, preserve deferred feature state, and trace the complete URS/UDIS/UG behavior.
- [ ] Separate programmed preload state from active/effective state and freeze the coherent PSC/ARR/CCR commit contract required by PWM.
- [ ] Finish the deferred DMA-source vocabulary independently from the completed
  Timer IRQ-source/event/NVIC split, including `DIER.TDE` when DMA admission opens.
- [ ] Correct write-only EGR, mode-dependent CCR, SR W0C, DMAR portal, and generic LL/RegOps access semantics.
- [ ] Extend current DIR/CMS validation to the complete live mode context,
  including the deferred encoder-mode state represented outside `CR1`.
- [ ] Freeze per-instance single-owner/transaction-guard and single-cleanup failure contracts with retained MMIO/peer trace evidence.
- [ ] Obtain and review the silicon errata matching the deployed STM32F103C8T6 revision.
- [ ] Reconcile this TODO and `TIMER_ARCHITECTURE.md` with every completed source wave.

## Remaining Deviations To Remove

- [ ] After the reopened P0 gates pass, rebuild TIM2/TIM3/TIM4 channel/PWM public APIs on the admitted narrow PWM-output surface.
- [ ] Channel masks must be validated when channel APIs are reintroduced.
- [ ] A final Timer-wide style audit is still required for tabs, banners, and single-argument function layout.
- [ ] PWM examples remain on the legacy API until channel/PWM public APIs are rebuilt.

## Verification Targets

- [x] `Projects/Timer/04_Timer_Poll`
- [x] `Projects/Timer/05_Timer_IRQ`
- [x] One GPIO project using timer-based startup delay: `Projects/GPIO/03_PB_IRQ`

## Latest Verification Notes

- [x] `BareMetal/Driver/Timer/Src/timer.c` passes `arm-none-eabi-gcc -fsyntax-only -Wall -Wextra -Werror`.
- [x] `BareMetal/Driver/Timer/Src/timer_codec.c` passes `arm-none-eabi-gcc -fsyntax-only -Wall -Wextra -Werror`.
- [x] `BareMetal/Driver/RCC/Src/rcc.c` passes `arm-none-eabi-gcc -fsyntax-only -Wall -Wextra -Werror`.
- [x] `git diff --check` passes.
- [x] `Projects/Timer/04_Timer_Poll`, `Projects/Timer/05_Timer_IRQ`, and `Projects/GPIO/03_PB_IRQ` configure and build successfully.
- [x] The then-current host Timer codec test built with `-Wall -Wextra -Werror` and passed through CTest; its repository-local test artifact is intentionally not retained.

## Notes

- Use `reg`, `reg_field_t`, `driver_status_t`, and existing `RegOps_*` helpers consistently.
- Every meaningful Timer codec Stage API should have a conjugate Extract API.
- LL functions should not validate, encode, batch, or decide mode/policy.
- Driver functions should own validation, sequencing, batching,
  register-specific dirty-write decisions, and public status handling;
  peripheral-independent compare/write mechanics belong to RegOps.
- RCC/application owns Timer APB1 clock-gate query and mutation. Timer public
  APIs validate that the required gate is enabled and never change it.
- `TIM_Config()` and `TIM_DeConfig()` are independent root lifecycle operations;
  neither calls its conjugate, changes the RCC gate, or changes NVIC delivery.
  The application explicitly orders clock enable, Timer configuration, Timer
  IRQ-source configuration, NVIC delivery, and Timer operation enablement.
- `TIM_Config()` preserves every `TIMx_DIER` source; applications explicitly
  call `TIM_SetIRQSources()` before enabling the independently owned NVIC line
  and starting the counter. Root configuration does not inspect NVIC state.
- Every Timer API that accesses the peripheral verifies clock availability
  through the private `_TIM_ValidateClockEnabled()` helper and does not change
  clock state.
