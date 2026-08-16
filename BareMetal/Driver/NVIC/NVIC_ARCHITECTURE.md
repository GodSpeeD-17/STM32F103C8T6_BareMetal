# STM32F103C8T6 NVIC Architecture

## Scope

This module controls the 43 maskable external interrupts implemented by the
STM32F103C8T6: IRQ numbers 0 through 42. Processor exceptions such as
MemManage, BusFault, UsageFault, PendSV, and SysTick remain SCB-owned and are
not part of the public NVIC IRQ API.

The public API intentionally exposes logical priority values. Raw IPR bytes,
register banks, AIRCR keys, masks, and action-register behavior stay below the
Driver boundary.

## Layer responsibilities

| Layer | Responsibility | Excluded responsibility |
|---|---|---|
| Driver (`nvic.c`) | Public validation, status returns, transactions, output publication, barriers | Raw field encoding and direct MMIO |
| Codec (`nvic_codec.c`) | Pure priority-group and IRQ-priority transforms | Hardware access and application policy |
| LL (`nvic_ll.c`) | One exact-width access per primitive | Validation, read-modify-write policy, sequencing |

The public `nvic.h` contains declarations and contracts only. Private helpers
remain in source files.

## Interrupt delivery ownership

An interrupt request crosses three independently controlled boundaries:

```text
Peripheral event
    -> peripheral flag and source-enable bit
    -> NVIC pending, enable, and priority state
    -> processor masking and exception arbitration
    -> active handler
```

Peripheral drivers own their local interrupt-source bits and flags. The
application or integration layer owns global NVIC vector delivery. This is
required for shared vectors such as `ADC1_2_IRQn`, `USB_HP_CAN_TX_IRQn`,
`USB_LP_CAN_RX0_IRQn`, `EXTI9_5_IRQn`, and `EXTI15_10_IRQn`.

A leaf peripheral driver must not disable a shared vector because it cannot
know whether another source still depends on that vector.

## Enabled, pending, and active state

These states are independent:

- Enabled means the NVIC is allowed to deliver the vector.
- Pending means a request is latched and waiting for service.
- Active means the handler is executing or has been preempted and stacked.

Disabling an IRQ does not clear pending state or terminate an active handler.
Clearing NVIC pending state does not acknowledge the peripheral source. An
asserted source can immediately pend the IRQ again. Active state is read-only
and every state query is only a hardware snapshot.

## Register transaction contracts

| Operation | Transaction |
|---|---|
| Enable | One ISER write-one-to-set write |
| Disable | One ICER write-one-to-clear write, then DSB and ISB |
| Get enable state | One ISER read |
| Get pending state | One ISPR read |
| Clear pending | One ICPR write-one-to-clear write |
| Software trigger | One STIR write |
| Get active state | One IABR read |
| Get IRQ priority | One AIRCR read and one byte-wide IPR read |
| Set IRQ priority | One AIRCR read and one byte-wide IPR write |
| Get priority group | One AIRCR read followed by pure decode |
| Set priority group | One AIRCR read, pure staging, then one keyed AIRCR write |

ISER, ICER, ISPR, and ICPR are action/state registers. Action writes use direct
assignment and never read-modify-write. In particular, an ICER or ICPR
read-modify-write could act on every bit returned as one by the preceding read.

## Priority model

The target implements four priority bits in IPR byte bits 7 through 4. Lower
numerical values have higher urgency.

| Logical group | AIRCR PRIGROUP | Preemption bits | Sub-priority bits |
|---|---:|---:|---:|
| Group 0 | 7 | 0 | 4 |
| Group 1 | 6 | 1 | 3 |
| Group 2 | 5 | 2 | 2 |
| Group 3 | 4 | 3 | 1 |
| Group 4 | 3 | 4 | 0 |

Raw PRIGROUP values 0 through 3 are equivalent when only four priority bits
exist. Decode canonicalizes all four values to logical Group 4. Encoding Group
4 always emits canonical raw value 3.

Preemption priority decides whether one configurable IRQ can interrupt
another. Sub-priority orders pending IRQs with equal preemption priority; it
does not permit one equal-preemption handler to interrupt another.

Priority grouping is global. Changing it immediately reinterprets every stored
IPR value without rewriting IPR. Application initialization must configure the
group before IRQ priorities and must prevent concurrent group changes.

## AIRCR safety

AIRCR is physically SCB-owned and requires VECTKEY `0x5FA` for writes. The
Codec stages the key and requested PRIGROUP into a caller-owned image while
clearing `SYSRESETREQ`, `VECTCLRACTIVE`, and `VECTRESET`. The Driver performs
one read and one write; the LL layer exposes those accesses with `LL_SCB_*`
names so physical ownership remains visible.

## Initialization and teardown

A normal initialization sequence is:

1. Configure the peripheral while its local interrupt sources are disabled.
2. Clear or acknowledge stale peripheral flags using the peripheral contract.
3. Configure the global priority group once during platform initialization.
4. Configure the IRQ priority.
5. Clear stale NVIC pending state.
6. Enable the NVIC vector.
7. Enable the peripheral-local interrupt source last.

A normal teardown first disables the peripheral-local source, then resolves
its flags, disables NVIC delivery when shared ownership permits it, and applies
any deliberate pending-state policy. DSB and ISB synchronize the NVIC disable,
but do not prove that an already accepted handler is quiescent.

## Concurrency rules

- Priority-group writes are single-owner application-init operations.
- IRQ priority and priority-group changes must not race each other.
- ISER, ICER, ICPR, and STIR actions are single direct writes without shared
  read-modify-write windows.
- Unprivileged STIR callers require the SCB `CCR.USERSETMPEND` permission;
  privileged firmware can trigger a validated external IRQ directly.
- IPR uses one byte per IRQ, so neighboring IRQ priorities are never rewritten.
- Shared-vector enable/disable arbitration belongs above leaf drivers.
- State getters do not provide synchronization; their results can become stale
  immediately after the read.
