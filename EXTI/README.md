# EXTI Driver for STM32F4xx

## Overview
This driver provides a set of functions to configure and handle external interrupts (EXTI) on STM32F4xx microcontrollers. The EXTI peripheral allows GPIO pins to trigger interrupts based on external events, such as rising or falling edges. The driver is implemented in `EXTI.c` and its corresponding header file `EXTI.h`.

---

## Features
- Configure GPIO pins as external interrupt sources.
- Support for rising edge, falling edge, or both edge triggers.
- Enable or disable specific EXTI lines.
- Clear pending interrupt flags.
- Handle EXTI interrupts in the IRQ handler.
- Software-triggered interrupts for testing purposes.

---

## File Structure
### 1. `EXTI.c`
This file contains the implementation of EXTI functions, including:
## File Structure

| **Function**                      | **Description**                                                                 |
|------------------------------------|---------------------------------------------------------------------------------|
| `SYSCFG_ConfigPortEXTI`           | Configure the GPIO port for an EXTI line.                                       |
| `EXTI_Configuration`              | Configure an EXTI line with trigger type, mask, and event request.              |
| `EXTI_SetInterruptOccurebySW`     | Trigger an interrupt manually via software.                                     |
| `EXTI_ClearFlagInterruptInLine`   | Clear the pending interrupt flag for an EXTI line.                              |
| `EXTI_GetFlagInterruptStatus`     | Get the status of the interrupt flag for an EXTI line.                          |
| `EXTI_GetTriggerStatus`           | Get the trigger type status (rising or falling) for an EXTI line.               |
### 2. `EXTI.h`
This file contains the declarations of the functions implemented in `EXTI.c` and the necessary macros and data types for EXTI configuration.

---

## How to Configure EXTI for STM32F4xx

### 1. Include the Header File
Include `EXTI.h` in your source file to use the EXTI driver:
```c
#include "EXTI.h"
```

### 2. Configure an EXTI Line
Use the `EXTI_Configuration` function to configure an EXTI line with the desired GPIO pin, trigger type, and mask settings:
```c
EXTI_Config_Variables exti_config = {
    .EXTI_port = EXTIx_PA_PIN,
    .EXTI_line = EXTI_LINE_1,
    .trigger_type = RISING_TRIGGER,
    .mask_it = NOT_MASKED,
    .mask_event = MASKED
};
EXTI_Configuration(exti_config);
```
- **Parameters**:
  - `EXTI_port`: GPIO port to use as the interrupt source (e.g., `EXTIx_PA_PIN`).
  - `EXTI_line`: EXTI line to configure (e.g., `EXTI_LINE_0`, `EXTI_LINE_15`).
  - `trigger_type`: Trigger type:
    - `RISING_TRIGGER`: Trigger on the rising edge.
    - `FALLING_TRIGGER`: Trigger on the falling edge.
  - `mask_it`: Enable or disable interrupt requests (`NOT_MASKED` or `MASKED`).
  - `mask_event`: Enable or disable event requests (`NOT_MASKED` or `MASKED`).

### 3. Enable the EXTI Line
Enable the interrupt for the configured EXTI line using the `EXTI_SettingMaskInterrupt` function:
```c
EXTI_SettingMaskInterrupt(EXTI_LINE_1, NOT_MASKED);
```

### 4. Handle the EXTI Interrupt
Implement the IRQ handler for the EXTI line in your application. Use the `EXTI_GetFlagInterruptStatus` and `EXTI_ClearFlagInterruptInLine` functions to check and clear the interrupt flag:
```c
void EXTI1_IRQHandler(void)
{
    if (EXTI_GetFlagInterruptStatus(EXTI_LINE_1))
    {
        // Handle the interrupt (e.g., toggle an LED)
        GPIO_TogglePin(GPIO_A, GPIO_PIN0);

        // Clear the pending flag
        EXTI_ClearFlagInterruptInLine(EXTI_LINE_1);
    }
}
```

---

## Functions

### EXTI_Configuration
- **Description**: Configure an EXTI line with the desired GPIO pin, trigger type, and mask settings.
- **Parameters**:
  - `EXTI_Config_Variables EXTI_val`: Configuration structure containing EXTI settings.
- **Steps Performed**:
  1. Configures the GPIO port for the EXTI line using `SYSCFG_ConfigPortEXTI`.
  2. Sets the trigger type (rising or falling edge) using `EXTI_RTSR` and `EXTI_FTSR`.
  3. Enables or disables interrupt requests using `EXTI_IMR`.
  4. Enables or disables event requests using `EXTI_EMR`.
- **Return Value**: None.
- **Example**:
  ```c
    /**
    *******************************************************************************
    * @ Name : EXTI_Configuration
    * @ Parameters: EXTI_Config_Variables EXTI_val
    * @ Registers : EXTI_RTSR, EXTI_FTSR, EXTI_IMR, EXTI_EMR, EXTI_PR
    * @ Descriptions :
    *		- Configure EXTI for EXTI_line
    *           + EXTI_line: EXTI_LINE_0 -> EXTI_LINE_15
    *           + mask_it, mask_event: NOT_MASKED (1), MASKED(0)
    *           + trigger_type: RISING_TRIGGER(0), FALLING_TRIGGER(1)
    * @ Return value : void
    * @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
    * @ date : 2024-07-13
    *******************************************************************************
    */
    void EXTI_Configuration(EXTI_Config_Variables EXTI_val)
    {
        SYSCFG_ConfigPortEXTI(EXTI_val.EXTI_port, EXTI_val.EXTI_line);     // enable EXTI interrupt line

        if (EXTI_val.trigger_type == RISING_TRIGGER)
        {
            EXTI_SET_RTSR(_EXTI, EXTI_val.EXTI_line, ENABLE);
            EXTI_SET_FTRS(_EXTI, EXTI_val.EXTI_line, DISABLE);
        }
        else if (EXTI_val.trigger_type == FALLING_TRIGGER)
        {
            EXTI_SET_RTSR(_EXTI, EXTI_val.EXTI_line, DISABLE);
            EXTI_SET_FTRS(_EXTI, EXTI_val.EXTI_line, ENABLE);
        }

        EXTI_SettingMaskInterrupt(EXTI_val.EXTI_line, EXTI_val.mask_it);       // enable interrupt request in line
        EXTI_SettingMaskEventRequest(EXTI_val.EXTI_line, EXTI_val.mask_event);    
    }

  ```

### SYSCFG_ConfigPortEXTI
- **Description**: Configure the GPIO port for an EXTI line.
- **Parameters**:
  - `port`: GPIO port to configure (e.g., `EXTIx_PA_PIN`).
  - `EXTI_line`: EXTI line to configure (e.g., `EXTI_LINE_0`, `EXTI_LINE_15`).
- **Return Value**: None.
- **Example**:
  ```c
  SYSCFG_ConfigPortEXTI(EXTIx_PA_PIN, EXTI_LINE_1);
  ```

### EXTI_SetInterruptOccurebySW
- **Description**: Trigger an interrupt manually via software for testing purposes.
- **Parameters**:
  - `EXTI_line`: EXTI line to trigger (e.g., `EXTI_LINE_0`, `EXTI_LINE_15`).
- **Return Value**: None.
- **Example**:
  ```c
  EXTI_SetInterruptOccurebySW(EXTI_LINE_1);
  ```

### EXTI_ClearFlagInterruptInLine
- **Description**: Clear the pending interrupt flag for an EXTI line.
- **Parameters**:
  - `EXTI_line`: EXTI line to clear (e.g., `EXTI_LINE_0`, `EXTI_LINE_15`).
- **Return Value**: None.
- **Example**:
  ```c
  EXTI_ClearFlagInterruptInLine(EXTI_LINE_1);
  ```

### EXTI_GetFlagInterruptStatus
- **Description**: Get the status of the interrupt flag for an EXTI line.
- **Parameters**:
  - `EXTI_line`: EXTI line to check (e.g., `EXTI_LINE_0`, `EXTI_LINE_15`).
- **Return Value**: `1` if the flag is set, `0` otherwise.
- **Example**:
  ```c
  if (EXTI_GetFlagInterruptStatus(EXTI_LINE_1))
  {
      // Handle the interrupt
  }
  ```

---

## Example
Below is an example of how to configure and use EXTI with this driver:

```c
#include "EXTI.h"
#include "GPIO.h"

int main(void)
{
    // Step 1: Enable the clock for GPIOA
    GPIO_EnableClock(GPIO_A);

    // Step 2: Configure PA1 as an EXTI source with a rising edge trigger
    EXTI_Config_Variables exti_config = {
        .EXTI_port = EXTIx_PA_PIN,
        .EXTI_line = EXTI_LINE_1,
        .trigger_type = RISING_TRIGGER,
        .mask_it = NOT_MASKED,
        .mask_event = MASKED
    };
    EXTI_Configuration(exti_config);

    while (1)
    {
        // Main loop
    }
}

// EXTI1 IRQ handler
void EXTI1_IRQHandler(void)
{
    if (EXTI_GetFlagInterruptStatus(EXTI_LINE_1))
    {
        // Toggle PA0 when the interrupt occurs
        GPIO_TogglePin(GPIO_A, GPIO_PIN0);

        // Clear the pending flag
        EXTI_ClearFlagInterruptInLine(EXTI_LINE_1);
    }
}
```

---

## Notes
- Ensure that the GPIO pin used as the EXTI source is configured as an input.
- The EXTI line must be enabled in the NVIC (Nested Vectored Interrupt Controller) for the interrupt to work.
- Use the appropriate IRQ handler for the EXTI line (e.g., `EXTI1_IRQHandler` for EXTI line 1).

---

## Author
- **Name**: Nguyen Dinh Thuan
- **Email**: thuan.nd.167@gmail.com
- **Date**: 2024-07-13