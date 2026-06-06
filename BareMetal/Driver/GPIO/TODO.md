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

- Convert `GPIOx` and `gpio_pin_t` single-pin masks into staged AFIO EXTICR
  routing-field updates.
- Stage EXTI trigger images.
- Reset staged AFIO EXTICR and trigger images.
- Extract staged AFIO EXTICR route fields back into driver-facing `GPIOx`
  pointers. Driver layer owns ownership comparison policy.

Rules:

- Codec must not directly read/write hardware registers.
- Codec must not include public `gpio_irq.h`.
- Codec may include `gpio_defines.h`.
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

driver_status_t GPIO_IRQ_Deinit(GPIO_TypeDef* const GPIOx, const gpio_pin_t pinMask);
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

## Current Alignment Status

The GPIO IRQ layer has been updated to match the GPIO module architecture:

- Generic pin-mask helpers now live in `gpio_defines.h`:
  `GPIO_PinMaskExtractLowestPin()` and `GPIO_PinMaskRemovePin()`.
- IRQ input-config validation now lives in `gpio_defines.h` as
  `GPIO_IRQ_INPUT_CONFIG_IS_VALID(inputConfig)`.
- IRQ codec APIs take `gpio_pin_t` single-pin masks when they operate on one
  EXTI line. Codec owns conversion to the EXTI line index internally.
- AFIO EXTICR register-address selection is owned by the GPIO IRQ driver layer
  as a private helper because it selects which hardware register image to read
  and write.
- AFIO EXTICR route ownership extraction is owned by
  `Codec_GPIO_IRQ_ExtractPortRouting()`. Codec owns decoding the extracted raw
  route into a driver-facing `GPIOx` pointer, and the driver owns comparing it
  with the expected port.
- AFIO EXTICR route staging is owned by
  `Codec_GPIO_IRQ_StagePortRouting()` and
  `Codec_GPIO_IRQ_StageResetPortRouting()`.
- EXTI trigger staging is owned by
  `Codec_GPIO_IRQ_StageTrigger()` and
  `Codec_GPIO_IRQ_StageResetTrigger()`.
- `gpio_irq.c` owns GPIO input setup, IMR sequencing, NVIC policy, batched
  register writes, pending-bit acknowledgement, and deinit ownership checks.
- `GPIO_IRQ_IsTriggered()` now returns `driver_status_t`:
  `DRIVER_STATUS_ON`, `DRIVER_STATUS_OFF`, or
  `DRIVER_STATUS_ERROR_INVALID_ARG`.

Current high-level init order:

```text
validate inputs
enable AFIO clock
read current EXTI IMR
temporarily mask selected EXTI lines if they are already unmasked
configure selected GPIO pins as input
read EXTI trigger images
read touched AFIO EXTICR images
stage AFIO EXTICR routing through codec
stage EXTI trigger bits through codec
write touched AFIO EXTICR images
write EXTI RTSR/FTSR
clear EXTI PR for selected lines
write final EXTI IMR
enable NVIC lines last
```

Current high-level deinit order:

```text
validate inputs
enable AFIO clock
read current EXTI IMR
mask selected EXTI lines
read EXTI trigger images
read touched AFIO EXTICR images
verify each selected route belongs to GPIOx
reset AFIO EXTICR routing slots through codec
reset EXTI trigger bits through codec
write touched AFIO EXTICR images
write EXTI RTSR/FTSR
clear EXTI PR for selected lines
write final EXTI IMR
disable NVIC groups only when no grouped line remains unmasked
```

## Verification Commands

Build the IRQ example:

```sh
cmake --build Projects/GPIO/03_PB_IRQ/Build
```

Sweep live code for old names:

```sh
rg -n "gpio_exti|GPIO_EXTI|gpio_irq_helper|GPIO_IRQ_HELPER|GPIO_IRQ_PORT_SOURCE|gpio_irq_port_t|LL_GPIO_EXTI" BareMetal Projects -g '*.[ch]'
```

Expected result:

- No old names in live code.
- Old names may appear only inside documentation that explicitly says not to
  reintroduce compatibility aliases.

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
5. Codec owns AFIO EXTICR field placement, route extraction, and trigger image
   staging.
6. Driver owns sequencing, GPIO input setup, batching, pending clear, IMR mask,
   and NVIC policy.
7. NVIC is enabled only after final EXTI/AFIO register writes.
8. Deinit ownership policy is explicit and implemented.
9. `03_PB_IRQ` builds successfully.
10. Old EXTI/helper names do not appear in live code.
