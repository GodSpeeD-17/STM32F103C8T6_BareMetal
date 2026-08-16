# STM32F103C8T6 NVIC Architecture {#NVIC_Peripheral_Guide}

## Scope and reading order

This page describes the Nested Vectored Interrupt Controller implemented by the
STM32F103C8T6 Cortex-M3 processor and then traces that hardware model into this
repository's NVIC stack.

The supported public scope is the 43 maskable external interrupts numbered 0
through 42. Processor exceptions such as MemManage, BusFault, UsageFault,
PendSV, and SysTick are not external IRQs and remain SCB-owned.

Read the two major parts in order:

1. **Theory with Register Mapping Bridge** explains the interrupt model and the
   significance of every register without depending on project source code.
2. **Implementation with Theory Bridge** maps that theory into the Core, LL,
   Codec, Driver, and public API.

## Part I — Theory with Register Mapping Bridge

### What the NVIC does

The NVIC receives interrupt requests from MCU peripherals and other external
sources, records their state, arbitrates between them, and asks the Cortex-M3
processor to enter the selected handler.

An external IRQ number identifies an NVIC input. The processor exception number
for that external interrupt is 16 greater than the IRQ number because exception
numbers 0 through 15 are reserved for reset and processor exceptions.

```text
external IRQ number n
        -> exception number n + 16
        -> vector-table entry n + 16
        -> interrupt handler address
```

The NVIC is not the origin of most interrupt events. A peripheral normally
detects an event, records a local flag, and asserts its request only when its
local interrupt source is enabled. The request then enters the NVIC:

```text
Peripheral event
    -> peripheral-local status flag
    -> peripheral-local interrupt-source enable
    -> NVIC pending state
    -> NVIC enable state
    -> priority and processor-mask arbitration
    -> NVIC active state
    -> handler execution
```

### End-to-end interrupt sequence

The complete relationship is easiest to understand as one event moving through
the peripheral, NVIC, processor, and handler:

```text
Peripheral event occurs
        ↓
Peripheral status register records its event flag
        ↓
Peripheral interrupt-enable register permits an interrupt request
        ↓
NVIC marks the external IRQ pending in ISPR
        ↓
ISER state confirms that delivery for the IRQ is enabled
        ↓
NVIC priority arbitration and processor interrupt masks permit execution
        ↓
The IRQ becomes active in IABR as the processor accepts the exception
        ↓
The processor obtains the handler address from the vector table
        ↓
The processor executes the IRQ handler
        ↓
The peripheral Driver acknowledges or consumes the originating event
        ↓
The handler returns from the exception
        ↓
The processor clears the IRQ's active state in IABR
```

For a Timer update interrupt, the generic names map directly to the concrete
hardware and Driver operations:

```text
Peripheral event                  = TIM3 update event
Peripheral event flag             = TIM3_SR.UIF
Peripheral interrupt enable       = TIM3_DIER.UIE
External IRQ                      = TIM3_IRQn
IRQ handler                       = TIM3_IRQHandler()
Peripheral acknowledgement        = TIM_AckIRQEvents()
```

Pending state normally transitions to active state when the processor accepts
the exception. If the peripheral flag is not acknowledged, or another event
arrives while the handler is active, the IRQ can become pending again and run
again after exception return.

### Five-question interrupt mental model

Each stage answers a different question. Keeping these questions separate
prevents peripheral event state from being confused with NVIC delivery state:

```text
Peripheral flag = Why is the peripheral requesting attention?
Pending         = Is a request waiting in the NVIC?
Enabled         = May the NVIC deliver it?
Priority        = When should it run relative to other eligible requests?
Active          = Is its handler currently in progress?
```

No answer implies another. A peripheral flag can be set while the IRQ is not
pending, a pending IRQ can be disabled, an enabled IRQ can have no request, and
an active IRQ can become pending again before its current handler returns.

This separation matters. Clearing an NVIC pending bit does not acknowledge the
peripheral flag that created the request. If that source remains asserted, the
IRQ can become pending again immediately.

### The three independent IRQ states

Every external IRQ can independently be enabled, pending, and active:

| State | Meaning | What it does not mean |
| --- | --- | --- |
| Enabled | The NVIC is permitted to deliver the IRQ | The IRQ is not necessarily pending or executing |
| Pending | A request is latched and waiting for arbitration | Delivery is not guaranteed while disabled or masked |
| Active | The processor accepted the exception and its handler is executing or stacked | The originating peripheral flag is not necessarily cleared |

Important consequences follow:

- Disabling an IRQ does not clear a pending request.
- Disabling an IRQ does not terminate a handler that is already active.
- An IRQ can be both active and pending when another occurrence is latched
  during handler execution.
- Reading any state register produces only a snapshot; hardware may change the
  state immediately afterward.

### State registers versus action registers

Memory-mapped registers are not always ordinary variables whose complete value
is replaced by assignment. The NVIC uses paired action ports for several
states:

| Access behavior | Meaning |
| --- | --- |
| Read state | A read returns the current bitmap or stored configuration |
| Write one to set | Each written one requests a state transition to one; zero has no effect |
| Write one to clear | Each written one requests a state transition to zero; zero has no effect |
| Read-only | Software may observe the state but cannot write it |
| Read/write configuration | Software reads or replaces persistent configuration |
| Write-only action | A write requests an operation rather than storing normal configuration |
| Keyed write | Hardware accepts the write only when a required key is present |

This is why action registers must not be treated as ordinary read-modify-write
storage. A value read as one and then written back can unintentionally repeat
an action on every corresponding bit.

### Register Mapping Bridge

The following table connects each NVIC concept to its architectural register.
Offsets are relative to the stated owner base. The NVIC base is `0xE000E100`;
the SCB base is `0xE000ED00`.

| Concept | Register | Owner | Offset | First address | Transfer width | Hardware significance |
| --- | --- | --- | ---: | ---: | ---: | --- |
| Enable state/set action | ISER | NVIC | `0x000` | `0xE000E100` | 32 bits | Read enable bitmap; write one to enable |
| Disable action | ICER | NVIC | `0x080` | `0xE000E180` | 32 bits | Write one to disable |
| Pending state/set action | ISPR | NVIC | `0x100` | `0xE000E200` | 32 bits | Read pending bitmap; write one to pend |
| Pending-clear action | ICPR | NVIC | `0x180` | `0xE000E280` | 32 bits | Write one to clear pending state |
| Active state | IABR | NVIC | `0x200` | `0xE000E300` | 32 bits | Read processor-owned active bitmap |
| Per-IRQ priority | IPR | NVIC | `0x300` | `0xE000E400` | 8 bits per IRQ | Read/write one independently addressed priority slot |
| Software request | STIR | NVIC | `0xE00` | `0xE000EF00` | 32 bits | Write an IRQ number to make it pending |
| Priority grouping | AIRCR | SCB | `0x00C` | `0xE000ED0C` | 32 bits | Keyed global priority interpretation and other system actions |

#### Banked bitmap mapping

ISER, ICER, ISPR, ICPR, and IABR use one bit per external IRQ. Each 32-bit bank
therefore covers 32 IRQ numbers:

```text
bank index   = IRQ number / 32
bit position = IRQ number % 32
bit mask     = 1 << bit position
```

For this target:

- bank 0 represents IRQ numbers 0 through 31;
- the implemented part of bank 1 represents IRQ numbers 32 through 42; and
- higher architectural banks do not represent implemented STM32F103C8T6 IRQs.

For example, IRQ 37 maps to bank 1, bit 5.

### ISER and ICER — interrupt delivery permission

ISER is the Interrupt Set-Enable Register family. Its read side shows whether
each IRQ is enabled. Writing one to a bit enables the corresponding IRQ;
writing zero has no effect.

ICER is the Interrupt Clear-Enable Register family. Writing one to a bit
disables the corresponding IRQ; writing zero has no effect. It is the clear
action port for the same logical enable state represented by ISER.

Enable state is only a delivery gate. It neither creates nor acknowledges a
request. If an IRQ becomes pending while disabled, enabling it later can allow
that stored request to be delivered.

### ISPR and ICPR — latched interrupt requests

ISPR is the Interrupt Set-Pending Register family. Reading it shows which IRQs
have a latched request. Writing one to an ISPR bit can set the corresponding
pending state in software.

ICPR is the Interrupt Clear-Pending Register family. Writing one clears the
corresponding pending state; zero has no effect.

Neither register owns the originating peripheral flag. Clearing ICPR while a
peripheral continues asserting its interrupt source can result in the IRQ being
pended again.

### IABR — handler activity

IABR is the Interrupt Active Bit Register family. A set bit means the processor
has accepted the exception and its handler is executing or remains stacked
after being preempted by a higher-urgency exception.

Active state is read-only because exception entry and return are processor
operations. Software cannot finish a handler by clearing an IABR bit.

### IPR — per-interrupt priority

Every external IRQ owns an 8-bit address slot in the Interrupt Priority
Register window. Four consecutive priority bytes occupy one naturally aligned
32-bit word, but Cortex-M3 permits each priority slot to be accessed as an
independent byte.

The architectural slot is eight bits wide; this STM32F103C8T6 implementation
uses only bits 7 through 4. Bits 3 through 0 are unimplemented. Consequently,
there are 16 implemented encoded priority values:

```text
0x00, 0x10, 0x20, ... 0xF0
```

Lower numerical values have higher urgency. Priority zero is therefore the
highest configurable urgency and priority fifteen is the lowest.

### AIRCR — global priority grouping

AIRCR is the SCB Application Interrupt and Reset Control Register. It is not
physically part of the NVIC register block, but its `PRIGROUP` field controls
how the implemented IPR bits are interpreted.

The four implemented priority bits can be divided between:

- **preemption priority**, which decides whether one configurable interrupt may
  interrupt another; and
- **sub-priority**, which orders simultaneously pending interrupts that have
  equal preemption priority.

| Logical group | AIRCR `PRIGROUP` | Preemption bits | Sub-priority bits |
| --- | ---: | ---: | ---: |
| Group 0 | 7 | 0 | 4 |
| Group 1 | 6 | 1 | 3 |
| Group 2 | 5 | 2 | 2 |
| Group 3 | 4 | 3 | 1 |
| Group 4 | 3 | 4 | 0 |

Raw `PRIGROUP` values 0 through 3 are hardware-equivalent when only four
priority bits are implemented. Changing `PRIGROUP` does not rewrite IPR; it
immediately changes how every existing IPR byte is interpreted.

AIRCR is a mixed-purpose and potentially destructive register. A valid write
requires `VECTKEY = 0x5FA`, and neighboring bits can request processor reset or
other system actions. Priority-group updates must therefore be carefully
staged before the register is written.

### STIR — software-generated requests

STIR is the Software Trigger Interrupt Register. Writing an external IRQ number
to STIR creates a software-generated request and makes that IRQ pending. It is
an action port, not persistent configuration, so reading it has no useful
configuration meaning.

Making an IRQ pending does not guarantee immediate handler execution. Delivery
still depends on NVIC enable state, configured priority, processor interrupt
masks, current exception state, and privilege. Unprivileged STIR use requires
the SCB `CCR.USERSETMPEND` permission.

### Ownership outside the NVIC

Peripheral drivers own their local source-enable bits and event flags. The
application or integration layer owns global NVIC vector delivery and shared
vector arbitration.

This is essential for shared vectors such as `ADC1_2_IRQn`,
`USB_HP_CAN_TX_IRQn`, `USB_LP_CAN_RX0_IRQn`, `EXTI9_5_IRQn`, and
`EXTI15_10_IRQn`. A leaf peripheral driver cannot safely disable a shared NVIC
vector because another source may still depend on it.

## Part II — Implementation with Theory Bridge

### Stack and file ownership

The implementation follows the repository's Driver -> Codec -> LL derivation
while retaining Core as the hardware description below those layers:

```text
Application intent
      |
      v
Public Driver API and transaction             nvic.h / nvic.c
      |                         \
      v                          v
Pure register-image transformation       Mechanical MMIO
nvic_codec.h / nvic_codec.c              nvic_ll.h
      \                          /
       v                        v
       Core register types, addresses, and raw fields
       stm32f1xx_nvic.h / stm32f1xx_scb.h
```

| Layer | Owns | Deliberately excludes |
| --- | --- | --- |
| Core | Register layout, base addresses, raw masks, access-qualified members | Public validation and interrupt policy |
| LL | One exact-width volatile register transfer per accessor | IRQ validation, encoding, barriers, and transaction policy |
| Codec | Pure AIRCR/IPR extraction and staging on caller-owned images | Peripheral pointers and volatile access |
| Driver | Public validation, bank/mask calculation, transaction order, output publication, and barriers | Direct raw field placement when Codec owns it |
| Application/integration | Initialization order, privilege, vector ownership, and shared-vector arbitration | Direct access that bypasses Driver contracts |

There is no `nvic_ll.c`. Following the Timer pattern, the complete LL
implementation consists of small static inline accessors in `nvic_ll.h`.

### Core C register representation

The Core structure maps the architectural NVIC address space:

```c
typedef volatile struct __NVIC_TypeDef
{
    volatile uint32_t       ISER[8];
    uint32_t                RESERVED_0[24];
    volatile uint32_t       ICER[8];
    uint32_t                RESERVED_1[24];
    volatile uint32_t       ISPR[8];
    uint32_t                RESERVED_2[24];
    volatile uint32_t       ICPR[8];
    uint32_t                RESERVED_3[24];
    volatile const uint32_t IABR[8];
    uint32_t                RESERVED_4[56];
    volatile uint8_t        IPR[240];
    uint32_t                RESERVED_5[644];
    _O                      STIR;

} NVIC_TypeDef;
```

The eight bitmap banks and 240 priority bytes preserve the complete Cortex-M3
architectural layout and the offset of STIR. They do not claim that this MCU
implements that many IRQs. Driver validation restricts access to IRQ numbers 0
through 42 and bitmap banks 0 and 1.

The C qualifiers express only part of the hardware contract:

- `volatile` forces each written C access to reach the memory-mapped register;
- `volatile const` prevents writes through the IABR member; and
- `_O` is the project's write-only documentation convention, implemented as a
  volatile 32-bit type because standard C has no write-only qualifier.

Special write-one and keyed-write semantics still require LL names, Doxygen,
and correct Driver transactions; `volatile` cannot express them.

AIRCR is represented separately by `SCB_TypeDef.AIRCR`, preserving its physical
SCB ownership.

### IRQ-number mapping in the Driver

The public API accepts a semantic `irq_t`. The Driver first validates it against
`NVIC_IRQ_NUMBER_FIRST` and `NVIC_IRQ_NUMBER_LAST`, then derives the bitmap
location:

```text
registerIndex = IRQn / 32
actionMask    = 1 << (IRQn % 32)
```

These calculations are Driver policy because they convert a validated public
IRQ number into a target-specific register bank and action mask. LL receives
only the already selected bank and mask and performs no range checking.

IPR needs no bank/bit calculation in software because its C representation is
a byte array. `NVIC->IPR[IRQn]` directly selects the priority byte owned by the
validated IRQ.

### Theory-to-implementation trace

| Theoretical intent | Core register | LL route | Codec role | Public Driver transaction |
| --- | --- | --- | --- | --- |
| Enable delivery | ISER | `LL_NVIC_WriteISER()` | None; action mask is exact | `NVIC_EnableIRQ()` validates, maps, and writes once |
| Disable delivery | ICER | `LL_NVIC_WriteICER()` | None; action mask is exact | `NVIC_DisableIRQ()` writes once, then executes DSB and ISB |
| Observe enable state | ISER | `LL_NVIC_ReadISER()` | None; Driver tests one bit | `NVIC_GetIRQState()` publishes ON/OFF after validation |
| Observe pending state | ISPR | `LL_NVIC_ReadISPR()` | None; Driver tests one bit | `NVIC_GetPendingIRQState()` publishes ON/OFF after validation |
| Clear pending state | ICPR | `LL_NVIC_WriteICPR()` | None; action mask is exact | `NVIC_ClearPendingIRQ()` writes one clear mask |
| Generate software request | STIR | `LL_NVIC_WriteSTIR()` | None; IRQ number is the exact payload | `NVIC_SoftwareTriggerIRQ()` validates and triggers once |
| Observe active state | IABR | `LL_NVIC_ReadIABR()` | None; Driver tests one bit | `NVIC_GetActiveIRQState()` publishes ON/OFF after validation |
| Read IRQ priority | IPR and AIRCR | `LL_NVIC_ReadIPR()` and `LL_SCB_ReadAIRCR()` | Decode priority byte using current group | `NVIC_GetIRQPriority()` publishes both logical outputs together |
| Write IRQ priority | IPR and AIRCR | `LL_NVIC_WriteIPR()` and `LL_SCB_ReadAIRCR()` | Encode logical priorities into one byte | `NVIC_SetIRQPriority()` stages fully, then writes one byte |
| Read priority grouping | AIRCR | `LL_SCB_ReadAIRCR()` | Decode and canonicalize `PRIGROUP` | `NVIC_GetPriorityGroup()` publishes the logical group |
| Write priority grouping | AIRCR | `LL_SCB_ReadAIRCR()` and `LL_SCB_WriteAIRCR()` | Preserve safe fields, clear action bits, insert group and key | `NVIC_SetPriorityGroup()` performs one read-stage-write transaction |

### Why some hardware directions have no LL function

The LL surface is derived from admitted Driver transactions, not from the mere
existence of every legal hardware access:

- There is no `LL_NVIC_ReadICER()` because enable state is read canonically
  through ISER.
- There is no `LL_NVIC_WriteISPR()` because the admitted public software-request
  operation uses the purpose-built STIR action.
- There is no `LL_NVIC_ReadICPR()` because pending state is read canonically
  through ISPR.
- There is no `LL_NVIC_WriteIABR()` because active state is hardware read-only.
- There is no `LL_NVIC_ReadSTIR()` because STIR is an action port without useful
  persistent state.

These omissions preserve semantic direction. They do not imply that every
omitted hardware direction is architecturally impossible.

### Special register implementation rules

#### Direct action writes

ISER, ICER, and ICPR writes use direct assignment:

```c
NVIC->ICER[registerIndex] = actionMask;
```

They never use a generic read-modify-write or dirty-write helper. Direct masks
avoid replaying actions for unrelated IRQ bits and require only one volatile
transfer.

#### Byte-wide IPR access

The LL reads or writes exactly one `uint8_t` IPR element. This matches the
hardware's independent priority slots, makes the IRQ number the natural array
index, and avoids a 32-bit read-modify-write that would touch four priorities.

Codec owns the logical-to-raw transformation. It places the four implemented
priority bits in the upper nibble and leaves the unimplemented lower nibble
clear.

#### Keyed AIRCR staging

The Driver snapshots AIRCR once. Codec works on that caller-owned image,
removes the read-side key image and previous grouping, clears
`SYSRESETREQ`, `VECTCLRACTIVE`, and `VECTRESET`, inserts the requested canonical
`PRIGROUP`, and inserts write key `0x5FA`. Only after all validation and staging
succeed does LL commit the complete 32-bit image.

The `LL_SCB_*` prefix is intentional: it keeps the foreign SCB register owner
visible even though the NVIC Driver consumes the access for priority grouping.

#### Disable synchronization

`NVIC_DisableIRQ()` performs the ICER action first and then executes DSB and
ISB. The barriers synchronize subsequent execution with the disable operation;
they do not prove that an already accepted handler has finished.

#### Getter publication

Public getters validate every pointer and IRQ before MMIO. They decode through
local storage and publish caller outputs only after the complete operation
succeeds. Their results remain snapshots rather than locks or synchronization
guarantees.

### Priority implementation

The public API keeps preemption priority and sub-priority as two scalar
parameters rather than introducing a two-member structure. Codec validates the
values against the current priority group, combines them into the four-bit
logical priority, and positions the result in IPR bits 7 through 4.

For logical Group 4, raw `PRIGROUP` values 0 through 3 decode to the same
four-preemption-bit behavior. Codec canonicalizes those reads to Group 4 and
always stages raw value 3 when writing Group 4.

Priority grouping is global. The application must configure it before setting
individual IRQ priorities and must prevent concurrent grouping and priority
changes.

### Application sequencing

A normal interrupt initialization sequence is:

1. Configure the peripheral while its local interrupt source is disabled.
2. Acknowledge stale peripheral-local event flags through the peripheral
   Driver.
3. Configure the global NVIC priority group once during platform
   initialization.
4. Configure the external IRQ priority.
5. Clear stale NVIC pending state.
6. Enable the NVIC vector.
7. Enable the peripheral-local interrupt source last.

A normal teardown reverses ownership deliberately:

1. Disable the peripheral-local interrupt source.
2. Resolve its event flags according to that peripheral's contract.
3. Disable NVIC delivery only when shared-vector ownership permits it.
4. Apply an explicit pending-state policy rather than clearing it implicitly.

### Concurrency and ownership rules

- Priority-group writes are single-owner platform-initialization operations.
- Priority-group and per-IRQ priority changes must not race because the group
  determines how every IPR byte is interpreted.
- ISER, ICER, ICPR, and STIR actions remain single direct writes without shared
  read-modify-write windows.
- Unprivileged STIR callers require `CCR.USERSETMPEND`; the Driver does not
  invent privilege that the caller does not possess.
- Shared-vector enable and disable arbitration belongs above leaf peripheral
  drivers.
- State getters do not synchronize hardware and can become stale immediately.

### Hardware and project authorities

Hardware behavior is governed by the Arm Cortex-M3 technical documentation and
the STM32F10xxx Cortex-M3 programming/reference manuals. The repository maps
that behavior through:

- `BareMetal/Core/Inc/stm32f1xx_nvic.h`
- `BareMetal/Core/Inc/stm32f1xx_scb.h`
- `BareMetal/Core/Inc/stm32f1xx_base_address.h`
- `BareMetal/Driver/NVIC/Inc/nvic.h`
- `BareMetal/Driver/NVIC/Inc/nvic_codec.h`
- `BareMetal/Driver/NVIC/Inc/nvic_ll.h`
- `BareMetal/Driver/NVIC/Src/nvic.c`
- `BareMetal/Driver/NVIC/Src/nvic_codec.c`

The Core headers are C mappings, not independent hardware specifications. The
hardware manuals remain authoritative when a source comment and documented
processor behavior disagree.
