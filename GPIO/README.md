# GPIO Driver for STM32F4xx

## Overview
This project provides a GPIO driver for STM32F4xx microcontrollers. It includes functions to configure and control GPIO pins, such as setting modes, output types, speeds, and pull-up/pull-down resistors. The driver is implemented in `GPIO.c` and its corresponding header file `GPIO.h`.

---

## Features
- Configure GPIO pin modes (Input, Output, Alternate Function, Analog).
- Set and get GPIO pin output types (Push-Pull, Open-Drain).
- Configure GPIO pin output speeds (Low, Medium, High, Very High).
- Set and get GPIO pin pull-up/pull-down resistors.
- Read and write GPIO pin data.
- Enable GPIO peripheral clock.
- Configure GPIO pins for alternate functions.

---
## File Structure
### 1. `GPIO.c`
This file contains the implementation of GPIO functions, including:
| **Function**                  | **Description**                                                                 |
|--------------------------------|---------------------------------------------------------------------------------|
| `GPIO_Set_Mode`                | Configure the mode of a GPIO pin.                                              |
| `GPIO_GetMode`                 | Get the current mode of a GPIO pin.                                            |
| `GPIO_Set_OutputType`          | Set the output type of a GPIO pin.                                             |
| `GPIO_GetOutputType`           | Get the current output type of a GPIO pin.                                     |
| `GPIO_Set_OutputSpeed`         | Set the output speed of a GPIO pin.                                            |
| `GPIO_GetOutputSpeed`          | Get the current output speed of a GPIO pin.                                    |
| `GPIO_SetInputType`            | Configure the pull-up/pull-down resistor for a GPIO pin.                       |
| `GPIO_GetInputType`            | Get the current pull-up/pull-down configuration of a GPIO pin.                 |
| `GPIO_GetInputData`            | Read the input data of a GPIO pin.                                             |
| `GPIO_SetOutputData`           | Write data to a GPIO pin.                                                      |
| `GPIO_EnableClock`             | Enable the clock for a specific GPIO port.                                     |
| `GPIO_Configuration`           | High-level function to configure a GPIO pin with multiple parameters.          |
| `GPIO_ConfigAlternateFunc`     | Configure a GPIO pin for an alternate function.                                |

### 2. `GPIO.h`
This file contains the declarations of the functions implemented in `GPIO.c` and the necessary macros and data types for GPIO configuration.

---

## How to Configure GPIO for STM32F4xx

### 1. Include the Header File
Include `GPIO.h` in your source file to use the GPIO driver:
```c
#include "GPIO.h"
#include "../RCC/RCC.h"
```

### 2. Enable GPIO Clock
Before configuring a GPIO pin, enable the clock for the corresponding GPIO port:
```c
GPIO_EnableClock(GPIO_A);
```

### 3. Configure GPIO Pin Mode
Set the mode of the GPIO pin using the `GPIO_Set_Mode` function:
```c
GPIO_Set_Mode(GPIO_A, GPIO_PIN5, MODER_OUTPUT);
```
| **Mode**           | **Description**          |
|---------------------|--------------------------|
| `MODER_INPUT`       | Input mode               |
| `MODER_OUTPUT`      | Output mode              |
| `MODER_ALTEMATE`    | Alternate function mode  |
| `MODER_ANALOG`      | Analog mode              |

### 4. Configure GPIO Output Type
Set the output type of the GPIO pin using the `GPIO_Set_OutputType` function:
```c
GPIO_Set_OutputType(GPIO_A, GPIO_PIN5, OTYPER_PUSHPULL);
```
| **Output Type**     | **Description**          |
|---------------------|--------------------------|
| `OTYPER_PUSHPULL`   | Push-pull output         |
| `OTYPER_OPENDRAIN`  | Open-drain output        |

### 5. Configure GPIO Output Speed
Set the output speed of the GPIO pin using the `GPIO_Set_OutputSpeed` function:
```c
GPIO_Set_OutputSpeed(GPIO_A, GPIO_PIN5, OSPEEDR_HIGH);
```
| **Speed**           | **Description**          |
|---------------------|--------------------------|
| `OSPEEDR_LOW`       | Low speed                |
| `OSPEEDR_MEDIUM`    | Medium speed             |
| `OSPEEDR_HIGH`      | High speed               |
| `OSPEEDR_VERYHIGH`  | Very high speed          |

### 6. Configure GPIO Pull-Up/Pull-Down Resistors
Set the pull-up/pull-down resistor configuration using the `GPIO_SetInputType` function:
```c
GPIO_SetInputType(GPIO_A, GPIO_PIN5, PUPDR_PULLUP);
```
| **Pull-Up/Down**    | **Description**          |
|---------------------|--------------------------|
| `PUPDR_NOTHING`     | No pull-up or pull-down  |
| `PUPDR_PULLUP`      | Pull-up resistor enabled |
| `PUPDR_PULLDOWN`    | Pull-down resistor enabled|

### 7. Configure GPIO Alternate Function (if needed)
If the GPIO pin is used for an alternate function, configure it using the `GPIO_ConfigAlternateFunc` function:
```c
GPIO_ConfigAlternateFunc(GPIO_A, GPIO_PIN5, AF1);
```
| **Alternate Function** | **Description**                     |
|-------------------------|-------------------------------------|
| `AF1`, `AF2`, ...       | Alternate function number          |

### 8. High-Level GPIO Configuration
The `GPIO_Configuration` function provides a convenient way to configure a GPIO pin with multiple parameters in a single call. This function simplifies the process of setting up a GPIO pin by combining mode, output type, speed, and pull-up/pull-down configuration into one step.

#### Function Prototype
```c
void GPIO_Configuration(GPIOn *gpio_x, uint8_t pinx, uint8_t mode, uint8_t otype, uint8_t ospeed, uint8_t pupd);
```
| **Step**               | **Description**                                                                 |
|-------------------------|---------------------------------------------------------------------------------|
| **Set GPIO Mode**       | Configures the mode of the GPIO pin (e.g., input, output, alternate, or analog).|
| **Set Output Type**     | Configures the output type (push-pull or open-drain).                           |
| **Set Output Speed**    | Configures the output speed (low, medium, high, or very high).                  |
| **Set Pull-Up/Down**    | Configures the pull-up or pull-down resistor.                                   |

#### Function Prototype
```c
void GPIO_Configuration(GPIOn *gpio_x, uint8_t pinx, uint8_t mode, uint8_t otype, uint8_t ospeed, uint8_t pupd);
```
#### Steps Performed by `GPIO_Configuration`
1. **Set GPIO Mode**:
   - Configures the mode of the GPIO pin (e.g., input, output, alternate function, or analog) using the `GPIO_Set_Mode` function.

2. **Set Output Type**:
   - Configures the output type of the GPIO pin (e.g., push-pull or open-drain) using the `GPIO_Set_OutputType` function.

3. **Set Output Speed**:
   - Configures the output speed of the GPIO pin (e.g., low, medium, high, or very high) using the `GPIO_Set_OutputSpeed` function.

4. **Set Pull-Up/Pull-Down Resistor**:
   - Configures the pull-up or pull-down resistor for the GPIO pin using the `GPIO_SetInputType` function.

#### Example
```c
void GPIO_Configuration(GPIOn * gpio_x, uint8_t pinx, uint8_t mode, uint8_t outtyper, uint8_t speed, uint8_t pull)
{
    GPIO_EnableClock(gpio_x);
    GPIO_Set_Mode(gpio_x, pinx, mode);
    GPIO_Set_OutputType(gpio_x, pinx, outtyper);
    GPIO_Set_OutputSpeed(gpio_x, pinx, speed);
    GPIO_SetInputType(gpio_x, pinx, pull);
}
```
---

## Functions to Get and Set GPIO Pin Data

### GPIO_GetInputData
- **Description**: Reads the input data of a GPIO pin.
- **Parameters**:
  - `gpio_x`: GPIO port (e.g., `GPIO_A`, `GPIO_B`).
  - `pinx`: GPIO pin number (e.g., `GPIO_PIN0`, `GPIO_PIN15`).
- **Return Value**: The current state of the pin (0 or 1).
- **Example**:
  ```c
  uint8_t pinState = GPIO_GetInputData(GPIO_A, GPIO_PIN5);
  ```

### GPIO_SetOutputData
- **Description**: Sets the output data of a GPIO pin.
- **Parameters**:
  - `gpio_x`: GPIO port.
  - `pinx`: GPIO pin number.
  - `state`: Desired state of the pin (`SET` or `CLEAR`).
- **Return Value**: None.
- **Example**:
  ```c
  GPIO_SetOutputData(GPIO_A, GPIO_PIN5, SET);   // Set PA5 HIGH
  GPIO_SetOutputData(GPIO_A, GPIO_PIN5, CLEAR); // Set PA5 LOW
  ```

### GPIO_SettingOutputDataBSRR
- **Description**: Sets or resets the output data of a GPIO pin using the **Bit Set/Reset Register (BSRR)**. This function allows atomic operations to set or reset specific GPIO pins without affecting other pins.
- **Parameters**:
  - `gpio_x`: GPIO port (e.g., `GPIO_A`, `GPIO_B`).
  - `pinx`: GPIO pin number (e.g., `GPIO_PIN0`, `GPIO_PIN15`).
  - `value`: Desired action for the pin:
    - **SET**: Sets the pin (writes `1` to the lower 16 bits of the BSRR register).
    - **CLEAR**: Resets the pin (writes `1` to the upper 16 bits of the BSRR register).
- **Registers**:
  - **BSRR**:
    - **Lower 16 bits (BSx)**: Writing `1` sets the corresponding pin.
    - **Upper 16 bits (BRx)**: Writing `1` resets the corresponding pin.
    - If both bits are written as `1`, the **BSx** bit takes priority.
- **Return Value**: None.
- **Example**:
  ```c
  // Set PA5 HIGH
  GPIO_SettingOutputDataBSRR(GPIO_A, GPIO_PIN5, SET);

  // Set PA5 LOW
  GPIO_SettingOutputDataBSRR(GPIO_A, GPIO_PIN5, CLEAR);
  ```

---

## Example
Below is an example of how to configure and use GPIO pins with this driver:

```c
#include "GPIO.h"

int main(void)
{
    // Step 1: Enable the clock for GPIOA
    GPIO_EnableClock(GPIO_A);

    // Step 2: Configure PA5 as output, push-pull, high speed, pull-up
    GPIO_Configuration(GPIO_A, GPIO_PIN5, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_PULLUP);

    // Step 3: Toggle PA5 in an infinite loop
    while (1)
    {
        // Set PA5 HIGH
        GPIO_SetOutputData(GPIO_A, GPIO_PIN5, SET);
        for (volatile int i = 0; i < 100000; i++); // Simple delay

        // Set PA5 LOW
        GPIO_SetOutputData(GPIO_A, GPIO_PIN5, CLEAR);
        for (volatile int i = 0; i < 100000; i++); // Simple delay
    }
}
```

### Explanation of the Example
1. **Enable GPIO Clock**:
   - The `GPIO_EnableClock(GPIO_A)` function enables the clock for GPIOA, allowing it to be configured and used.

2. **Configure GPIO Pin**:
   - The `GPIO_Configuration` function is used to configure PA5 with the following settings:
     - **Mode**: Output (`MODER_OUTPUT`).
     - **Output Type**: Push-pull (`OTYPER_PUSHPULL`).
     - **Speed**: High speed (`OSPEEDR_HIGH`).
     - **Pull-up/Pull-down**: Pull-up resistor enabled (`PUPDR_PULLUP`).

3. **Toggle GPIO Pin**:
   - The `GPIO_SetOutputData` function is used to set or clear the output state of PA5.
   - A simple delay is added between toggles to make the blinking visible.

This example demonstrates how to configure and toggle a GPIO pin using the provided driver functions.

---

## Author
- **Name**: Nguyen Dinh Thuan
- **Email**: thuan.nd.167@gmail.com
- **Date**: 2024-07-07
