# USART Refactor TODO

This checklist tracks the commit-sized USART refactor sequence. Complete one
item, verify it (build the two USART projects), commit it as
`BKCP #N: <Title Case Summary>!`, then move to the next item — the same
discipline `Timer/TODO.md` used.

The intended architecture and ownership rules live in
[`USART_ARCHITECTURE.md`](USART_ARCHITECTURE.md). Read it before starting any
step below.

## Scope

- [ ] Limit this pass to UART (asynchronous) mode on `USART1`, `USART2`, and
  `USART3`. Synchronous clock, Smartcard, IrDA, LIN, multiprocessor wake, and
  DMA stay deferred per `USART_ARCHITECTURE.md`'s Deferred Domains table.
- [ ] Preserve existing public `USART_*` function names where practical.
- [ ] Preserve the `usart_config_t` root-structure concept as the primary
  configuration API shape.

## Step Plan

- [x] Document intended USART architecture and the migration checklist in
  this directory (`USART_ARCHITECTURE.md`, this file).
- [ ] Introduce `Inc/usart_data_types.h` for USART scalar aliases
  (`usart_data_bits_t`, `usart_parity_t`, `usart_stop_bits_t`,
  `usart_hardware_enable_t`, `usart_irq_source_t`, `usart_event_flag_t`,
  `usart_baud_rate_t`). No pin-mapping structures — GPIO/AFIO pin
  configuration is entirely application-owned, matching Timer PWM, so the
  driver never needs a `usart_pin_t`/`usart_gpio_t` type.
- [ ] Introduce `Inc/usart_defines.h` for public USART selector macros,
  `USART1`/`USART2`/`USART3` instance validation, and pure validation
  helpers. Drop the `USART_4`/`USART_5` selectors — they don't exist on this
  part.
- [ ] Add `Inc/usart_ll.h` with dumb named `LL_USART_*` register read/write
  accessors for `SR`, `DR`, `BRR`, `CR1`, `CR2`, `CR3`. Leave `GTPR` as
  unclassified raw foundation until Smartcard/IrDA is admitted.
- [ ] Add `Inc/usart_codec.h` and `Src/usart_codec.c` with:
  - `Codec_USART_Extract/StageHardwareEnableState` (`CR1.TE/RE`)
  - `Codec_USART_Extract/StageDataConfig` (`CR1.M/PCE/PS`, `CR2.STOP`)
  - `Codec_USART_Extract/StageFlowControlState` (`CR3.RTSE/CTSE`)
  - `Codec_USART_Extract/StageOperationState` (`CR1.UE`)
  - `Codec_USART_Extract/StageBaudRate` (BRR mantissa/fraction from
    `busFrequency` + preset `usart_baud_rate_t` selector, resolved to bps
    internally)
  - `Codec_USART_Extract/StageIRQSources` (`CR1` + `CR3` enable bits)
  - `Codec_USART_ExtractIRQEvents` (pure `SR` decode) and
    `Codec_USART_StageIRQEventsClear` (write-0-to-clear staging for `TC`/
    `CTS` only); the driver owns the actual read-SR-then-read-DR hardware
    sequence for `PE/FE/NE/ORE/IDLE/RXNE` since that requires live register
    access, which the codec does not perform. `TXE` is never acknowledged.
- [ ] Refactor `Inc/usart_config.h` into the instance-independent
  `usart_config_t` root structure (hardware-enable, frame format, preset
  baud rate) only. No GPIO pin table and no `Src/usart_config.c`:
  GPIO/AFIO pin routing, configuration, and clocking are entirely
  application-owned, matching Timer PWM, so `__usartDriverGPIOMapping__[]`
  is removed rather than re-keyed, and the file is deleted (mirroring
  Timer's `.h`-only config layer).
- [ ] Refactor `Inc/usart.h` into public API only, no inline hardware
  access: `USART_GetOperationState`/`SetOperationState` (`CR1.UE`),
  `USART_Config`/`USART_DeConfig`, `USART_GetIRQSources`/`SetIRQSources`,
  `USART_GetIRQEvents`/`AckIRQEvents`, `USART_TX_Ready`/`RX_Ready`/byte
  send/recv helpers, `USART_printf`.
- [ ] Refactor `Src/usart.c` orchestration:
  - Remove `__USART_enableClock__()`/`__USART_disableClock__()`; require the
    application to enable the USART peripheral clock gate through RCC before
    `USART_Config()`, verified through a new private
    `_USART_ValidateClockEnabled()`.
  - No GPIO/AFIO pin-clock sequencing in the driver at all — the application
    enables those clocks and configures the pins itself, matching Timer
    PWM's GPIO ownership model. An earlier draft of this checklist proposed
    a driver-owned `_USART_GPIO_EnableClock()`; that plan is reversed.
  - Replace the `irq & 0x1F` CR1-only shift trick in
    `USART_IRQ_Enable`/`Disable` with codec-based `CR1`+`CR3` field
    placement through the new `usart_irq_source_t` split.
- [ ] Remove the `usart_t` enum, `USART_4`/`USART_5`, and the
  `__usartDriverRegisterMapping__[]` lookup table; migrate every internal
  call site to direct `USART1`/`USART2`/`USART3` pointer identity.
- [x] Migrate `Projects/USART/08_USART_Byte_Poll_TX`,
  `Projects/USART/09_USART_Byte_Poll_RX`, and
  `Projects/USART/10_USART_printf` to the pointer-identity API. Each project
  explicitly sequences: RCC-enable the USART peripheral clock, RCC-enable
  the GPIO/AFIO clocks and configure the TX/RX pins itself (application
  owns this, matching Timer PWM), then call `USART_Config()`.
- [x] Implement `USART_printf()` on top of `USART_TransmitByte()`:
  `vsnprintf()` into a bounded stack buffer, one `va_start()`/`va_end()` pair
  per call, then a plain byte loop. This sidesteps the old per-character
  `va_end(args)`-inside-the-loop bug entirely rather than patching it, since
  there is no per-character `va_arg()` walk left to get wrong.
- [ ] Finish the USART Doxygen pass for the implemented public APIs,
  matching the GPIO stack's completed pass.
- [ ] Build both USART example projects and run a repo-wide Doxygen
  validation pass.

## Verification Targets

- [x] `Projects/USART/08_USART_Byte_Poll_TX`
- [x] `Projects/USART/09_USART_Byte_Poll_RX`
- [x] `Projects/USART/10_USART_printf`

## Notes

- Use `reg`, `driver_status_t`, and existing `RegOps_*` helpers consistently,
  the same as Timer and GPIO.
- RCC/application owns the USART peripheral clock gate; the driver only
  verifies it through `_USART_ValidateClockEnabled()` and never mutates it.
- GPIO/AFIO pin selection, configuration, and clocking are entirely
  application-owned — the driver has no pin table and never touches GPIO,
  matching Timer PWM's GPIO ownership model exactly.
- IRQ sources (`CR1`+`CR3` enable bits) and IRQ events (`SR` flags) are
  separate types; acknowledgement is per-bit-correct, not one uniform
  register write.
- Baud rate is a preset selector (`usart_baud_rate_t`/`USART_BAUD_RATE_*`)
  resolved to its numeric bits-per-second value inside `usart_codec.c`,
  which then computes the `BRR` divider against the live bus frequency.
- Every meaningful codec Stage API should have a conjugate Extract API,
  except where the hardware is naturally asymmetric (documented explicitly,
  not silently omitted).
