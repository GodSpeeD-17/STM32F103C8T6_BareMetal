# Timer Refactor TODO

This checklist tracks the commit-sized Timer refactor sequence. Complete one
item, verify it, commit it, then move to the next item.

## Scope

- [x] Limit the first pass to general-purpose timers `TIM2`, `TIM3`, `TIM4`, and `TIM5`.
- [ ] Preserve existing public `TIM_*` API names where practical during the layer split.
- [x] Preserve existing public `TIMx_*` selector names initially to reduce churn.
- [x] Keep public Timer configuration structures as the primary modular configuration API.
- [x] Defer broad public selector/API naming cleanup until the layer boundaries are correct.

## Step Plan

- [x] Document intended Timer architecture and pending deviations in this directory.
- [x] Introduce `Inc/timer_data_types.h` for Timer scalar aliases and shared plain data aliases.
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
- [x] Finalize Timer config update-event sequencing around `EGR.UG`, `CNT`, and generated `SR.UIF`.
- [x] Add public header-local static inline `TIM_Config1MHz()` preset wrapper over `TIM_Config()`.
- [x] Add public `TIM_DelayUs()` blocking polling helper for Timers configured by `TIM_Config1MHz()`.
- [x] Add public `TIM_DelayMs()` blocking polling wrapper over `TIM_DelayUs(TIMx, 1000U)`.
- [x] Reorganize `timer.c` public implementations under the same banner and sub-banner order used by `timer.h`.
- [x] Add file-level Doxygen `@section` blocks to `timer.c` for scope, field ownership, and source layout.
- [ ] Rework Timer IRQ APIs so codec owns DIER/SR mapping and driver owns NVIC policy.
- [ ] Update Timer examples and shared startup delay users to the new public API shape.
- [ ] Finish remaining Timer Doxygen/style pass for source-local helper return wording, defines, and deferred public APIs.
- [ ] Build affected projects and fix integration issues.

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
- [x] RCC clock-gate state APIs `TIM_GetClockState()` and `TIM_SetClockState()` were exposed before configuration APIs.
- [x] Counter operation state APIs `TIM_GetOperationState()` and `TIM_SetOperationState()` were exposed.
- [x] Binary state codec extractors return decoded `DRIVER_STATUS_OFF` or `DRIVER_STATUS_ON` directly.
- [x] Core shared CCMR raw-value macros were normalized to STM32-style `CCxS`, `OCxM`, `ICxPSC`, and `ICxF` notation.
- [x] `TIM_DeConfig()` uses `TIM_SetClockState()`, `TIM_SetOperationState()`, config-owned reset staging, and clock-gate disable without issuing RCC peripheral reset.
- [x] Grouped/scalar `Get` and `Set` APIs now require the clock gate to already be enabled and return `DRIVER_STATUS_ERROR_STATE` when it is disabled.
- [x] `timer.h`, `timer_config.h`, and `timer_codec.h` now document caller input scope with `Accepted values` and decoded/output scope with `Expected values`.
- [x] `timer.h` public APIs now use function-specific `@returns @ref driver_status_t "... - Operation Status"` labels and parameter-specific `@retval` wording.
- [x] `TIM_Config()` now stages `CR1`, `PSC`, and `ARR`, temporarily clears `CR1.UDIS` for `EGR.UG`, restores final `CR1`, preserves pre-existing `SR.UIF`, clears only a newly generated update flag, and applies `CNT` after the update event.
- [x] `TIM_Config1MHz()` now shapes a local 1 MHz `tim_config_t` preset in the header and delegates to `TIM_Config()`.
- [x] `TIM_DelayUs()` now provides a `uint16_t`-bounded minimum blocking one-pulse polling delay using `ARR`/`CNT`/`UIF`, temporary `UDIS` enablement, and final counter stop for Timers configured by `TIM_Config1MHz()`.
- [x] `TIM_DelayMs()` now provides a minimum blocking millisecond delay by composing repeated `TIM_DelayUs(TIMx, 1000U)` chunks.
- [x] `timer.c` public implementation order now mirrors `timer.h`, including conjugate getter/setter sub-banners and final blocking-delay helpers.
- [x] `timer.c` file overview now uses Doxygen `@section` blocks for scope, field ownership, and source layout.
- [x] `_TIM_ClockEnabled()` was replaced by `_TIM_ValidateClockEnabled()` for narrow API clock-gate precondition checks.
- [x] `TIM_GetClockState()` and `TIM_SetClockState()` validate the Timer instance directly and do not require the Timer clock gate to already be enabled.

## Remaining Deviations To Remove

- [ ] Channel/PWM public APIs are currently deferred and must be rebuilt on top of the existing channel codec surface.
- [ ] Timer IRQ public APIs are currently deferred and must be rebuilt with codec-owned DIER/SR mapping and driver-owned NVIC policy.
- [ ] Driver must validate channel masks and IRQ masks when those public APIs are reintroduced.
- [ ] IRQ disable policy can disable NVIC while other Timer IRQ sources remain enabled.
- [ ] Remaining Doxygen/style pass is still required for source-local helper return wording, `timer_defines.h`, and deferred public APIs.
- [ ] A final Timer-wide style audit is still required for tabs, banners, and single-argument function layout.
- [ ] Timer example projects still use the legacy Timer config shape and removed legacy helper APIs.

## Verification Targets

- [ ] `Projects/Timer/04_Timer_Poll`
- [ ] `Projects/Timer/05_Timer_IRQ`
- [ ] One GPIO project using timer-based startup delay, for example `Projects/GPIO/03_PB_IRQ`

## Latest Verification Notes

- [x] `BareMetal/Driver/Timer/Src/timer.c` passes `arm-none-eabi-gcc -fsyntax-only -Wall -Wextra -Werror`.
- [x] `BareMetal/Driver/Timer/Src/timer_codec.c` passes `arm-none-eabi-gcc -fsyntax-only -Wall -Wextra -Werror`.
- [x] `BareMetal/Driver/RCC/Src/rcc.c` passes `arm-none-eabi-gcc -fsyntax-only -Wall -Wextra -Werror`.
- [x] `git diff --check` passes.
- [ ] `Projects/Timer/04_Timer_Poll` build fails because `main.c` still uses `.instance`, `.channel`, `TIM_1MHz_Load_Default()`, and old one-argument `TIM_Config()`.
- [ ] `Projects/Timer/05_Timer_IRQ` build fails because `main.c` still uses the old config shape plus deferred IRQ APIs such as `TIM_IRQ_Enable()`, `TIM_IRQ_Get_Status()`, and `TIM_IRQ_Ack()`.

## Notes

- Use `reg`, `reg_field_t`, `driver_status_t`, and existing `RegOps_*` helpers consistently.
- Every meaningful Timer codec Stage API should have a conjugate Extract API.
- LL functions should not validate, encode, batch, or decide mode/policy.
- Driver functions should own validation, sequencing, batching, dirty writes, and public status handling.
- Only `TIM_SetClockState()` owns RCC APB1 clock-gate mutation as a direct public state API.
- `TIM_Config()` and `TIM_DeConfig()` may use `TIM_SetClockState()` internally because they are full lifecycle orchestration APIs.
- Clock-state APIs validate Timer instance/state and directly read or mutate the RCC APB1 clock gate; they do not require that gate to already be enabled.
- Narrow grouped/scalar `Get` and `Set` APIs verify clock availability through the private `_TIM_ValidateClockEnabled()` helper and do not change clock state.
