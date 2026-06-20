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
- [ ] Rework Timer IRQ APIs so codec owns DIER/SR mapping and driver owns NVIC policy.
- [ ] Update Timer examples and shared startup delay users to the new public API shape.
- [ ] Apply Timer Doxygen/style pass using GPIO banner style and `@ref` backtick convention.
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

## Remaining Deviations To Remove

- [ ] Channel/PWM public APIs are currently deferred and must be rebuilt on top of the existing channel codec surface.
- [ ] Timer IRQ public APIs are currently deferred and must be rebuilt with codec-owned DIER/SR mapping and driver-owned NVIC policy.
- [ ] Driver must validate channel masks and IRQ masks when those public APIs are reintroduced.
- [ ] IRQ disable policy can disable NVIC while other Timer IRQ sources remain enabled.
- [ ] Doxygen does not consistently use accepted values, `@retval`, or `@ref` with backticks.
- [ ] Style does not consistently use tabs and the established banner style.
- [ ] Timer example projects still use the legacy Timer config shape and removed legacy helper APIs.

## Verification Targets

- [ ] `Projects/Timer/04_Timer_Poll`
- [ ] `Projects/Timer/05_Timer_IRQ`
- [ ] One GPIO project using timer-based startup delay, for example `Projects/GPIO/03_PB_IRQ`

## Latest Verification Notes

- [x] `BareMetal/Driver/Timer/Src/timer.c` passes `arm-none-eabi-gcc -fsyntax-only -Wall -Wextra -Werror`.
- [x] `BareMetal/Driver/Timer/Src/timer_codec.c` passes `arm-none-eabi-gcc -fsyntax-only -Wall -Wextra -Werror`.
- [x] `git diff --check` passes.
- [ ] `Projects/Timer/04_Timer_Poll` build fails because `main.c` still uses `.instance`, `.channel`, `TIM_1MHz_Load_Default()`, and old one-argument `TIM_Config()`.
- [ ] `Projects/Timer/05_Timer_IRQ` build fails because `main.c` still uses the old config shape plus deferred IRQ/runtime APIs such as `TIM_IRQ_Enable()`, `TIM_Enable()`, `TIM_IRQ_Get_Status()`, and `TIM_IRQ_Ack()`.

## Notes

- Use `reg`, `reg_field_t`, `driver_status_t`, and existing `RegOps_*` helpers consistently.
- Every meaningful Timer codec Stage API should have a conjugate Extract API.
- LL functions should not validate, encode, batch, or decide mode/policy.
- Driver functions should own validation, sequencing, batching, dirty writes, and public status handling.
