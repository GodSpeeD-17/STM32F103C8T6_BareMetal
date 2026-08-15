# Timer Refactor TODO

This checklist tracks the commit-sized Timer refactor sequence. Complete one
item, verify it, commit it, then move to the next item.

## Scope

- [x] Limit the STM32F103C8T6 driver to the implemented general-purpose timers `TIM2`, `TIM3`, and `TIM4`.
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
- [x] Rework Timer IRQ APIs so codec owns DIER/SR mapping and driver owns NVIC policy.
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
- [x] RCC clock-gate state APIs `TIM_GetClockState()` and `TIM_SetClockState()` were exposed before configuration APIs.
- [x] Counter operation state APIs `TIM_GetOperationState()` and `TIM_SetOperationState()` were exposed.
- [x] Binary state codec extractors return decoded `DRIVER_STATUS_OFF` or `DRIVER_STATUS_ON` directly.
- [x] Core shared CCMR raw-value macros were normalized to STM32-style `CCxS`, `OCxM`, `ICxPSC`, and `ICxF` notation.
- [x] `TIM_DeConfig()` disables/clears NVIC state, pulses the matching RCC peripheral reset, and leaves the clock gate disabled.
- [x] Grouped/scalar `Get` and `Set` APIs now require the clock gate to already be enabled and return `DRIVER_STATUS_ERROR_STATE` when it is disabled.
- [x] `timer.h`, `timer_config.h`, and `timer_codec.h` now document caller input scope with `Accepted values` and decoded/output scope with `Expected values`.
- [x] `timer.h` public APIs now use function-specific `@returns @ref driver_status_t "... - Operation Status"` labels and parameter-specific `@retval` wording.
- [x] `TIM_Config()` now commits `PSC`/`ARR` with `UDIS=0`, `URS=1`, and `EGR.UG`, restoring requested `CR1`, `CNT`, and entry NVIC state.
- [x] `TIM_Config1MHz()` derives the prescaler from the live APB1 Timer kernel clock through `TIM_ConfigTickFrequency()`.
- [x] `TIM_DelayUs()` verifies an exact 1 MHz tick and uses bounded polling with cleanup on timeout.
- [x] `TIM_DelayMs()` now provides a minimum blocking millisecond delay by composing repeated `TIM_DelayUs(TIMx, 1000U)` chunks.
- [x] `timer.c` public implementation order now mirrors `timer.h`, including conjugate getter/setter sub-banners and final blocking-delay helpers.
- [x] `timer.c` file overview now uses Doxygen `@section` blocks for scope, field ownership, and source layout.
- [x] `_TIM_ClockEnabled()` was replaced by `_TIM_ValidateClockEnabled()` for narrow API clock-gate precondition checks.
- [x] `TIM_GetClockState()` and `TIM_SetClockState()` validate the Timer instance directly and do not require the Timer clock gate to already be enabled.
- [x] Timebase and DIR/CMS setters reject a running counter with `DRIVER_STATUS_ERROR_BUSY`.
- [x] Timer IRQ source state, pending flags, and acknowledgements use codec-owned DIER/SR mapping and instance NVIC coordination.
- [x] Host codec tests cover CR1/timebase preservation and DIER/SR IRQ behavior.

## Remaining Deviations To Remove

- [ ] Channel/PWM public APIs are currently deferred and must be rebuilt on top of the existing channel codec surface.
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
- [x] Host Timer codec test builds with `-Wall -Wextra -Werror` and passes through CTest.

## Notes

- Use `reg`, `reg_field_t`, `driver_status_t`, and existing `RegOps_*` helpers consistently.
- Every meaningful Timer codec Stage API should have a conjugate Extract API.
- LL functions should not validate, encode, batch, or decide mode/policy.
- Driver functions should own validation, sequencing, batching, dirty writes, and public status handling.
- Only `TIM_SetClockState()` owns RCC APB1 clock-gate mutation as a direct public state API.
- `TIM_Config()` and `TIM_DeConfig()` may use `TIM_SetClockState()` internally because they are full lifecycle orchestration APIs.
- Clock-state APIs validate Timer instance/state and directly read or mutate the RCC APB1 clock gate; they do not require that gate to already be enabled.
- Narrow grouped/scalar `Get` and `Set` APIs verify clock availability through the private `_TIM_ValidateClockEnabled()` helper and do not change clock state.
