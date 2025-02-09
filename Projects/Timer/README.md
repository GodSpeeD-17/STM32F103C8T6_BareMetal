# Timer

Reference Manual (RM-008 Rev 21) 
Start Page: 365/1116
End Page: 424/1116
General Purpose Timer: TIM2, TIM3, TIM4, TIM5 (APB1 Bus)

## Features

- **16-bit programmable prescaler**  
  Used to divide (also “on the fly”) the counter clock frequency by any factor between 1 and 65536

- **Up to 4 independent channels** for:
  - **Input capture (ICx)**
  - **Output compare (OCx)**
  - **PWM generation** (Edge- and Center-aligned modes)
  - **One-pulse mode output (OPM)**

- **Supports incremental (quadrature) encoder** and hall-sensor circuitry for positioning purposes


## Block Diagram:
	![General Purpose Timer Block Diagram](images/Block%20Diagram.png)

## Basic Units

| Units               | Register  | Description                                                                 |
|---------------------|-----------|-----------------------------------------------------------------------------|
| Counter Register    | TIMx_CNT  | Current Count Value of TIMx                                                 |
| Prescaler Register  | TIMx_PSC  | Scaling the TIMx Frequency with respect to APB1 Clock Frequency             |
| Auto-Reload Register| TIMx_ARR  | Maximum Value that TIMx can count up to (Up Counting) or start from (Down Counting) |
