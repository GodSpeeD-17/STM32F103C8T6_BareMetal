# General Purpose Input Output (GPIO)

### Hardware Specifications:
 - Recommended Source/Sink Current: 8mA
 - Max Source/Sink Current: 20mA
 - Absolute Max Combined Source/Sink Current (for Module): 150mA

### NOTE:
 - In order to configure a GPIO as Pull-Up/Pull-Down, we need to set/reset the bit in ODR respectively after setting the `CNFx` bits in `GPIOx->CRH`/`GPIOx->CRL` as `0b10`
 - PC13 has an on-board LED which is `Active-Low` (Writing `0` to the pin will turn on the LED)
 - PC13, PC14, PC15 should be used very carefully with following consideration:
    - Sink Current: 30mA (Max)
    - Source Current: 0mA (Speed: 2MHz)
---
### GPIO Configuration Structure
```
typedef struct {
	// Port
	GPIO_REG_STRUCT* GPIOx;
	// Pin
	uint8_t PINx;
	// Mode
	uint8_t MODEx;
	// Configuration
	uint8_t CNFx;
} gpio_config_t;
```
#### GPIO
```
#define APB2_BASE_ADDR							((uint32_t) 0x40010000)
#define GPIOA                   					((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x0800))
#define GPIOB                   					((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x0C00))
#define GPIOC                   					((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x1000))
#define GPIOD                   					((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x1400))
#define GPIOE                   					((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x1800))
#define GPIOF                   					((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x1C00))
#define GPIOG                   					((GPIO_REG_STRUCT *)(APB2_BASE_ADDR + (uint32_t)0x2000))
#define OB_LED_PORT							(GPIOC)
```

#### PIN
```
#define GPIO_PIN_0							((uint8_t) 0)
#define GPIO_PIN_1							((uint8_t) 1)
#define GPIO_PIN_2							((uint8_t) 2)
#define GPIO_PIN_3							((uint8_t) 3)
#define GPIO_PIN_4							((uint8_t) 4)
#define GPIO_PIN_5							((uint8_t) 5)
#define GPIO_PIN_6							((uint8_t) 6)
#define GPIO_PIN_7							((uint8_t) 7)
#define GPIO_PIN_8							((uint8_t) 8)
#define GPIO_PIN_9							((uint8_t) 9)
#define GPIO_PIN_10							((uint8_t) 10)
#define GPIO_PIN_11							((uint8_t) 11)
#define GPIO_PIN_12							((uint8_t) 12)
#define GPIO_PIN_13							((uint8_t) 13)
#define GPIO_PIN_14							((uint8_t) 14)
#define GPIO_PIN_15							((uint8_t) 15)
#define OB_LED_PIN							(GPIO_PIN_13)
```

#### GPIO Mode
```
#define MODE_IN								((uint8_t) 0)
#define MODE_OUT_10MHz							((uint8_t) 1)
#define MODE_OUT_2MHz							((uint8_t) 2)
#define MODE_OUT_50MHz							((uint8_t) 3)
```

#### GPIO Configuration
```
#define CNF_IN_ANALOG							((uint8_t) 0)
#define CNF_IN_FLOAT							((uint8_t) 1)
#define CNF_IN_PD							((uint8_t) 3)
#define CNF_IN_PU							((uint8_t) 4)
#define CNF_OUT_GP_PP							((uint8_t) 0)
#define CNF_OUT_GP_OD							((uint8_t) 1)
#define CNF_OUT_AF_PP							((uint8_t) 2)
#define CNF_OUT_AF_OD							((uint8_t) 3)
```
---
### Configuration Steps
- Step 1: Enable respective Peripheral Clock `IOPAEN`/`IOPBEN`/`IOPCEN`/`IOPDEN`/`IOPEEN` using `RCC->APB2ENR`
- Step 2: Based upon configuration, enable Alternate Function Clock `AFIOEN` using `RCC->APB2ENR`
- Step 3: Read & Store Current Data: 
    - `GPIO_PIN_x` <= `GPIO_PIN_7` -> `GPIOx->CRL`
    - `GPIO_PIN_x` > `GPIO_PIN_7` -> `GPIOx->CRH`
- Step 4: Configure the `MODEx` & `CNFx` bits in `GPIOx->CRx` as per requirement
- Step 5: Write the Register Value back to `GPIOx->CRx`
