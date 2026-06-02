# GPIO IRQ Layer TODO

## Purpose

This file is the handoff reference for normalizing the GPIO IRQ layer to match
the GPIO architecture already established in this module.

The intended public GPIO IRQ setup should hide AFIO/EXTI implementation details
from application code. The user-facing setup call should be:

```c
GPIO_IRQ_Init(GPIOx, pinMask, inputConfig, trigger);
```

Example for a push button on `PA1` with an external pull-up resistor:

```c
GPIO_IRQ_Init(GPIOA, GPIO_PIN_1, GPIO_PIN_CONFIG_INPUT_FLOATING, GPIO_IRQ_TRIGGER_FALLING);
```

## Manual-Backed Hardware Sequence

Reference: `Reference_Docs/STM32F103C_Reference_Manual.pdf`.

The STM32F1 GPIO IRQ setup sequence is:

1. Enable GPIO port clock.
2. Configure selected GPIO pin(s) as input.
   Accepted GPIO electrical configs for EXTI input usage:
   - `GPIO_PIN_CONFIG_INPUT_FLOATING`
   - `GPIO_PIN_CONFIG_INPUT_PULL_DOWN`
   - `GPIO_PIN_CONFIG_INPUT_PULL_UP`
3. Enable AFIO clock before accessing `AFIO_EXTICR1..4`.
4. Route GPIO port to EXTI line through `AFIO_EXTICR`.
5. Configure edge trigger:
   - `EXTI_RTSR` for rising edge
   - `EXTI_FTSR` for falling edge
   - both for both-edge trigger
6. Clear stale pending bits by writing `1` to selected `EXTI_PR` bit(s).
7. Unmask interrupt line(s) in `EXTI_IMR`.
8. Enable corresponding NVIC IRQ:
   - `EXTI0_IRQn` for line 0
   - `EXTI1_IRQn` for line 1
   - `EXTI2_IRQn` for line 2
   - `EXTI3_IRQn` for line 3
   - `EXTI4_IRQn` for line 4
   - `EXTI9_5_IRQn` for lines 5..9
   - `EXTI15_10_IRQn` for lines 10..15
9. In ISR, check `EXTI_PR`, run user logic, then acknowledge with `EXTI_PR = pinMask`.

## Intended Layer Ownership

### Layer 0: Core Register Layer

Files:

- `BareMetal/Core/Inc/stm32f1xx_exti.h`
- `BareMetal/Core/Inc/stm32f1xx_afio.h`

Ownership:

- Raw EXTI/AFIO register structs, unions, bit positions, and masks.
- Hardware terminology such as AFIO EXTICR GPIO port-source fields.

Rules:

- Do not place driver selector policy here.
- Do not add GPIO IRQ public API concepts here.

### Layer 1: GPIO Data Types and Defines

Files:

- `BareMetal/Driver/GPIO/Inc/gpio_data_types.h`
- `BareMetal/Driver/GPIO/Inc/gpio_defines.h`

Ownership:

- `gpio_data_types.h` owns scalar typedef aliases only.
- `gpio_defines.h` owns public selector macros and pure validation macros.

Current intended IRQ aliases:

```c
typedef uint8_t gpio_irq_trigger_t;
```

Current intended IRQ selector macros:

```c
GPIO_IRQ_TRIGGER_FALLING
GPIO_IRQ_TRIGGER_RISING
GPIO_IRQ_TRIGGER_BOTH
GPIO_IRQ_TRIGGER_IS_VALID(trigger)
```

Important rule:

- Do not reintroduce `gpio_irq_port_t`.
- Do not reintroduce `GPIO_IRQ_PORT_SOURCE_*` macros in the GPIO driver layer.
- AFIO EXTICR port-field encoding must remain private to the IRQ codec.

### Layer 2: GPIO IRQ LL

File:

- `BareMetal/Driver/GPIO/Inc/gpio_irq_ll.h`

Ownership:

- Dumb full-register EXTI/AFIO reads and writes.
- AFIO APB2 clock forwarding.
- `LL_GPIO_IRQ_EXTI_REG(...)` and `LL_GPIO_IRQ_AFIO_REG(...)` member-address macros.

Rules:

- LL must not validate GPIO pins, trigger selectors, input configs, or NVIC policy.
- LL must not know AFIO EXTICR field placement.
- LL must not know public driver API concepts.

### Layer 3: GPIO IRQ Codec

Files:

- `BareMetal/Driver/GPIO/Inc/gpio_irq_codec.h`
- `BareMetal/Driver/GPIO/Src/gpio_irq_codec.c`

Ownership:

- Convert `GPIOx + pin` into staged AFIO EXTICR routing-field updates.
- Stage EXTI trigger images.
- Reset staged AFIO EXTICR and trigger images.
- Resolve NVIC IRQ number from one GPIO IRQ line.

Rules:

- Codec must not directly read/write hardware registers.
- Codec must not include public `gpio_irq.h`.
- Codec may include `gpio_defines.h` and `nvic_types.h`.
- Codec functions should return `driver_status_t`.
- Validation helpers should not return `uint8_t` unless explicitly required.

### Layer 4: GPIO IRQ Driver

Files:

- `BareMetal/Driver/GPIO/Inc/gpio_irq.h`
- `BareMetal/Driver/GPIO/Src/gpio_irq.c`

Ownership:

- Public API.
- Public validation orchestration.
- GPIO input configuration.
- AFIO clock sequencing.
- Batched register read/stage/write sequence.
- NVIC enable/disable policy.
- Pending-bit acknowledgement policy.

Intended public API shape:

```c
driver_status_t GPIO_IRQ_Init
(
	GPIO_TypeDef* const			GPIOx,
	const gpio_pin_t			pinMask,
	const gpio_pin_config_t		inputConfig,
	const gpio_irq_trigger_t		trigger
);

driver_status_t GPIO_IRQ_DeInit(GPIO_TypeDef* const GPIOx, gpio_pin_t pinMask);
driver_status_t GPIO_IRQ_IsTriggered(const gpio_pin_t pinMask);
driver_status_t GPIO_IRQ_Ack(const gpio_pin_t pinMask);
```

## Current Implementation Snapshot

The current worktree has already moved away from the old EXTI/helper naming:

- Old shape: `gpio_exti.*`, `gpio_exti_helper.*`, `GPIO_EXTI_*`, `LL_GPIO_EXTI_*`
- New intended shape: `gpio_irq.*`, `gpio_irq_codec.*`, `GPIO_IRQ_*`, `LL_GPIO_IRQ_*`, `Codec_GPIO_IRQ_*`

Current public init shape is already correct:

```c
GPIO_IRQ_Init(GPIOx, pinMask, inputConfig, trigger);
```

`Projects/GPIO/03_PB_IRQ/Src/main.c` currently uses the intended single-call
setup for the push button IRQ path.

## Deviations and Mitigation

### 1. NVIC Enable Sequencing

Current deviation:

- `GPIO_IRQ_Init()` enables NVIC inside the per-pin loop before all staged
  `EXTICR`, `RTSR`, `FTSR`, `PR`, and `IMR` writes are complete.

Why this is not ideal:

- For a fresh masked line this is usually harmless.
- For reconfiguration of an already-enabled line, IRQ delivery could happen
  while routing/trigger state is being changed.

Mitigation:

1. Read `IMR`.
2. Mask selected line(s) in hardware before changing route/trigger state.
3. Stage and write `EXTICR`, `RTSR`, and `FTSR`.
4. Clear stale pending bits through `PR`.
5. Write final `IMR` with selected lines unmasked.
6. Enable NVIC after final register writes.

Preferred high-level init order:

```text
validate inputs
configure GPIO input
enable AFIO clock
read EXTI/AFIO images
temporarily mask selected EXTI lines
stage AFIO EXTICR routing
stage EXTI trigger bits
write touched AFIO EXTICR images
write EXTI RTSR/FTSR
clear EXTI PR for selected lines
write final EXTI IMR
enable NVIC lines
```

### 2. Pin-Mask Iteration

Current deviation:

- `gpio_irq.c` has `_GPIO_IRQ_GetLowestSelectedLine()` that scans from
  `GPIO_PIN_0` upward.

Why this is not ideal:

- The GPIO driver already adopted a bit-mask based iteration style.
- GPIO IRQ should not regress to scanning every possible bit.

Mitigation:

- Move generic pin-mask helpers into `gpio_defines.h` as static inline helpers,
  or reuse existing ones if already promoted:
  - extract lowest selected pin from pin mask
  - remove selected pin from pin mask
- Use the same helper style in `gpio.c` and `gpio_irq.c`.

Suggested API names:

```c
GPIO_PinMaskExtractLowestPin(pinMask)
GPIO_PinMaskRemovePin(&pinMask, pin)
```

The exact names can be adjusted to match existing GPIO naming style.

### 3. IRQ Input Config Validation Ownership

Current deviation:

- `_GPIO_IRQ_InputConfigIsCompatible()` lives in `gpio_irq.c`.

Why this is not ideal:

- This is pure selector validation.
- Pure validation belongs in `gpio_defines.h`.

Mitigation:

Add to `gpio_defines.h`:

```c
#define GPIO_IRQ_INPUT_CONFIG_IS_VALID(inputConfig)		\
(														\
	(((gpio_pin_config_t) (inputConfig)) == GPIO_PIN_CONFIG_INPUT_FLOATING)		|| \
	(((gpio_pin_config_t) (inputConfig)) == GPIO_PIN_CONFIG_INPUT_PULL_DOWN)	|| \
	(((gpio_pin_config_t) (inputConfig)) == GPIO_PIN_CONFIG_INPUT_PULL_UP)		\
)
```

Then remove `_GPIO_IRQ_InputConfigIsCompatible()` from `gpio_irq.c`.

### 4. Codec Validation Return Type

Current deviation:

- `Codec_GPIO_IRQ_IsSinglePinMaskValid()` returns `uint8_t`.

Why this is not ideal:

- Project policy says validation functions should return `driver_status_t`
  unless a non-status return was explicitly requested.

Mitigation options:

1. Remove the helper and use existing pin-mask validation macros directly.
2. Or convert it to:

```c
__STATIC_FORCEINLINE driver_status_t Codec_GPIO_IRQ_PinMaskIsSingleLine(const gpio_pin_t pin)
```

Use `DRIVER_STATUS_SUCCESS` and `DRIVER_STATUS_ERROR_INVALID_ARG`.

### 5. Codec Doxygen Still Uses Old Wording

Current deviation:

- Some codec Doxygen still says "Port source image".

Why this is not ideal:

- The GPIO driver no longer exposes a port-source selector concept.
- That wording should stay in core AFIO register documentation only.

Mitigation:

Update codec Doxygen wording:

- Use "AFIO EXTICR routing field".
- Use "AFIO EXTICR routing image".
- Avoid "port-source selector" in GPIO driver/codec docs.

### 6. LL Doxygen Mentions Helper

Current deviation:

- `gpio_irq_ll.h` still says `Codec/helper APIs`.

Mitigation:

- Replace with `Codec APIs`.
- Keep `helper` out of file names, API names, and Doxygen architecture text.

### 7. Deinit Ownership and Safety

Current deviation:

- `GPIO_IRQ_Deinit(GPIOx, pinMask)` accepts `GPIOx`, but current logic resets
  selected EXTICR fields without verifying that the selected line is actually
  routed to that `GPIOx`.

Mitigation options:

1. Keep `GPIOx` and add codec support to extract/verify current EXTICR routing
   before clearing it.
2. Drop `GPIOx` from `GPIO_IRQ_Deinit()` and document that deinit resets the
   selected EXTI line routing to AFIO reset state regardless of current owner.

Preferred conservative option:

- Keep `GPIOx`.
- Add route ownership verification before deinit clears the EXTICR field.

### 8. Register Index Ownership

Current deviation:

- Driver computes EXTICR index directly with:

```c
GPIO_PinMaskToIndex(currentPin) >> 2U
```

- Codec also has an internal EXTICR index helper.

Why this is not ideal:

- Duplicates AFIO EXTICR layout knowledge across driver and codec.

Mitigation options:

1. Expose a codec function:

```c
driver_status_t Codec_GPIO_IRQ_GetEXTICRIndex(const gpio_pin_t pin, uint8_t* const pIndex);
```

2. Or keep index selection in the driver and remove the duplicated codec helper
   if codec no longer needs it.

Preferred option:

- Let codec own AFIO EXTICR layout knowledge.
- Expose a small status-returning codec query for EXTICR index.

## Intended Implementation Plan

1. Clean Doxygen wording first.
   - Remove "helper".
   - Replace "port source image" with "AFIO EXTICR routing image".

2. Promote pure validation to `gpio_defines.h`.
   - Add `GPIO_IRQ_INPUT_CONFIG_IS_VALID(inputConfig)`.
   - Remove driver-local input config validation.

3. Promote or reuse generic pin-mask iteration helpers.
   - Use identical bit-mask iteration in GPIO and GPIO IRQ.
   - Avoid scanning all pins.

4. Tighten codec status behavior.
   - Remove `uint8_t` validation helper or convert to `driver_status_t`.
   - Keep codec functions image-based and hardware-free.

5. Rework `GPIO_IRQ_Init()` sequencing.
   - Configure GPIO input.
   - Enable AFIO clock.
   - Read images.
   - Mask selected IMR lines before route/trigger updates.
   - Stage through codec.
   - Write touched images.
   - Clear pending bits.
   - Unmask IMR.
   - Enable NVIC last.

6. Decide and implement `GPIO_IRQ_Deinit()` policy.
   - Preferred: verify route ownership with `GPIOx`.
   - Alternative: remove `GPIOx` from deinit and document reset behavior.

7. Build and verify.
   - Build `Projects/GPIO/03_PB_IRQ/Build`.
   - Sweep for old names:

```sh
rg -n "gpio_exti|GPIO_EXTI|gpio_irq_helper|GPIO_IRQ_HELPER|GPIO_IRQ_PORT_SOURCE|gpio_irq_port_t|LL_GPIO_EXTI" BareMetal Projects -g '*.[ch]' -g '*.md'
```

Expected result:

- Old names may appear only inside documentation text that explicitly says not
  to use compatibility aliases.

## Do Not Reintroduce

- `gpio_irq_helper.*`
- `gpio_exti.*`
- `GPIO_EXTI_*`
- `LL_GPIO_EXTI_*`
- `GPIO_IRQ_PORT_SOURCE_*`
- `gpio_irq_port_t`
- Backward compatibility aliases for old names

## Commit-Ready Criteria

The GPIO IRQ layer is commit-ready when:

1. Public setup is one call:

```c
GPIO_IRQ_Init(GPIOx, pinMask, inputConfig, trigger);
```

2. `gpio_data_types.h` contains only used scalar aliases.
3. `gpio_defines.h` owns public IRQ trigger selectors and pure IRQ validation.
4. LL contains only dumb register access and AFIO clock forwarding.
5. Codec owns AFIO EXTICR field placement and trigger image staging.
6. Driver owns sequencing, GPIO input setup, batching, pending clear, IMR mask,
   and NVIC policy.
7. NVIC is enabled only after final EXTI/AFIO register writes.
8. Deinit ownership policy is explicit and implemented.
9. `03_PB_IRQ` builds successfully.
10. Old EXTI/helper names do not appear in live code.
