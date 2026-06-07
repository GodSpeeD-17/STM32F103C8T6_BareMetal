# Timer Refactor TODO

This checklist tracks the commit-sized Timer refactor sequence. Complete one
item, verify it, commit it, then move to the next item.

## Scope

- [x] Limit the first pass to general-purpose timers `TIM2`, `TIM3`, `TIM4`, and `TIM5`.
- [ ] Preserve existing public `TIM_*` API names where practical during the layer split.
- [ ] Preserve existing public `TIMx_*` selector names initially to reduce churn.
- [ ] Keep public Timer configuration structures as the primary modular configuration API.
- [ ] Defer broad public API renaming until the layer boundaries are correct.

## Step Plan

- [x] Document intended Timer architecture and pending deviations in this directory.
- [x] Introduce `Inc/timer_data_types.h` for Timer scalar aliases and shared plain data aliases.
- [x] Introduce `Inc/timer_defines.h` for public selectors, defaults, validation helpers, and pure utilities.
- [x] Move Timer public selectors/defaults out of `stm32f1xx.h` while keeping Core raw-only.
- [x] Add `Inc/timer_ll.h` with dumb register read/write helpers only.
- [ ] Add `Inc/timer_codec.h` and `Src/timer_codec.c` with private encode/decode helpers and public extract/stage image APIs.
- [ ] Refactor `Inc/timer.h` into public API only with `driver_status_t` contracts and no inline hardware access.
- [ ] Refactor `Src/timer.c` orchestration to use validation, LL, codec staging, dirty writes, and status returns.
- [ ] Rework Timer IRQ APIs so codec owns DIER/SR mapping and driver owns NVIC policy.
- [ ] Update Timer examples and shared startup delay users to the new public API shape.
- [ ] Apply Timer Doxygen/style pass using GPIO banner style and `@ref` backtick convention.
- [ ] Build affected projects and fix integration issues.

## Current Deviations To Remove

- [ ] `timer_config.h` owns too much: direct register access, RCC access, NVIC include, and policy helpers are mixed with intentional public config structs.
- [ ] Public Timer configuration structures need a clean driver-layer home, either in `timer.h` or a dedicated public config header with no register access.
- [ ] `timer.h` contains inline direct hardware access and duplicate declarations.
- [ ] `timer.c` directly accesses Timer and RCC registers instead of going through LL.
- [x] Public Timer selector enums and defaults live in `stm32f1xx.h`.
- [x] No Timer LL layer exists.
- [ ] No Timer codec layer exists.
- [ ] CR1, CCMR, CCER, DIER, and SR field placement is not centralized in codec.
- [ ] Public APIs do not consistently return `driver_status_t`.
- [ ] Driver does not validate Timer instance, channel mask, IRQ mask, or config selector compatibility.
- [ ] Driver does not consistently read only required registers.
- [ ] Driver does not consistently write only changed staged images.
- [ ] IRQ disable policy can disable NVIC while other Timer IRQ sources remain enabled.
- [ ] Doxygen does not consistently use accepted values, `@retval`, or `@ref` with backticks.
- [ ] Style does not consistently use tabs and the established banner style.

## Verification Targets

- [ ] `Projects/Timer/04_Timer_Poll`
- [ ] `Projects/Timer/05_Timer_IRQ`
- [ ] One GPIO project using timer-based startup delay, for example `Projects/GPIO/03_PB_IRQ`

## Notes

- Use `reg`, `reg_field_t`, `driver_status_t`, and existing `RegOps_*` helpers consistently.
- Every meaningful Timer codec Stage API should have a conjugate Extract API.
- LL functions should not validate, encode, batch, or decide mode/policy.
- Driver functions should own validation, sequencing, batching, dirty writes, and public status handling.
