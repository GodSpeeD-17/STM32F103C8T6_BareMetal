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
  `usart_hardware_enable_t`, `usart_irq_source_t`, `usart_event_flag_t`) and
  the `usart_pin_t`/`usart_gpio_t` pin-mapping structures moved out of
  `usart_config.h`.
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
    `busFrequency` + numeric baud rate)
  - `Codec_USART_Extract/StageIRQSources` (`CR1` + `CR3` enable bits)
  - `Codec_USART_ExtractIRQEvents` and the per-bit-correct
    `Codec_USART_AckIRQEvents` (write-0-to-clear for `TC`/`CTS`; read-SR-then-
    read-DR for `PE/FE/NE/ORE/IDLE/RXNE`; `TXE` never acknowledged)
- [ ] Refactor `Inc/usart_config.h`/`Src/usart_config.c` into the
  instance-independent `usart_config_t` root structure (hardware-enable,
  data config, numeric baud rate) plus the per-instance default GPIO pin
  table, re-keyed from `usart_t` enum index to `USART_TypeDef*` pointer
  identity.
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
  - Keep `_USART_GPIO_EnableClock()` as the driver-owned GPIO/AFIO pin-clock
    sequencing step (already correct from the GPIO clock-ownership fix
    earlier this session).
  - Replace the `irq & 0x1F` CR1-only shift trick in
    `USART_IRQ_Enable`/`Disable` with codec-based `CR1`+`CR3` field
    placement through the new `usart_irq_source_t` split.
- [ ] Remove the `usart_t` enum, `USART_4`/`USART_5`, and the
  `__usartDriverRegisterMapping__[]` lookup table; migrate every internal
  call site to direct `USART1`/`USART2`/`USART3` pointer identity.
- [ ] Migrate `Projects/USART/08_USART_Byte_TX` and
  `Projects/USART/10_USART_printf` to the pointer-identity API and explicit
  RCC clock-gate sequencing (USART peripheral clock, then GPIO/AFIO clocks
  are handled by the driver, then `USART_Config()`).
- [ ] Fix `USART_printf()`'s `va_end(args)` call: it currently runs inside
  the per-character loop instead of once after it, which is undefined
  behavior because `va_arg()` is used again after `va_end()`.
- [ ] Finish the USART Doxygen pass for the implemented public APIs,
  matching the GPIO stack's completed pass.
- [ ] Build both USART example projects and run a repo-wide Doxygen
  validation pass.

## Verification Targets

- [ ] `Projects/USART/08_USART_Byte_TX`
- [ ] `Projects/USART/10_USART_printf`

## Notes

- Use `reg`, `driver_status_t`, and existing `RegOps_*` helpers consistently,
  the same as Timer and GPIO.
- RCC/application owns the USART peripheral clock gate; the driver only
  verifies it through `_USART_ValidateClockEnabled()` and never mutates it.
- The driver owns GPIO/AFIO pin-clock sequencing for its own private pin
  table through `_USART_GPIO_EnableClock()`, because the application does not
  know which physical pins a given `USARTx` instance uses by default.
- IRQ sources (`CR1`+`CR3` enable bits) and IRQ events (`SR` flags) are
  separate types; acknowledgement is per-bit-correct, not one uniform
  register write.
- Baud rate is a plain numeric value computed against the live bus
  frequency; there is no preset enum or lookup table.
- Every meaningful codec Stage API should have a conjugate Extract API,
  except where the hardware is naturally asymmetric (documented explicitly,
  not silently omitted).
