# NVIC Driver for STM32F4xx

## Overview
This driver provides a set of functions to configure and manage the Nested Vectored Interrupt Controller (NVIC) on STM32F4xx microcontrollers. The NVIC is responsible for handling interrupts and exceptions, allowing the user to enable, disable, prioritize, and manage interrupts efficiently. The driver is implemented in `NVIC.c` and its corresponding header file `NVIC.h`.

---

## Features
- Enable or disable specific interrupts.
- Set or clear pending interrupt flags.
- Set interrupt priorities.
- Get the status of interrupts (enabled, pending, active, etc.).
- Initialize and configure NVIC for specific IRQ numbers.
- Support for up to 240 IRQ numbers.

---

## File Structure
### 1. `NVIC.c`
This file contains the implementation of NVIC functions, including:
## File Structure

| **Function**                  | **Description**                                                                 |
|--------------------------------|---------------------------------------------------------------------------------|
| `NVIC_SetInterruptEnable`      | Enable a specific interrupt.                                                   |
| `NVIC_ClearInterruptEnable`    | Disable a specific interrupt.                                                  |
| `NVIC_SetPendingInterrupt`     | Set a pending flag for a specific interrupt.                                   |
| `NVIC_ClearPendingInterrupt`   | Clear a pending flag for a specific interrupt.                                 |
| `NVIC_SetActiveInterrupt`      | Set an interrupt as active.                                                    |
| `NVIC_GetStatusInterrupt`      | Get the status of a specific interrupt.                                        |
| `NVIC_SetPriority`             | Set the priority of a specific interrupt.                                      |
| `NVIC_Init`                    | Initialize NVIC for a specific interrupt.                                      |
| `NVIC_Configuration`           | Configure NVIC for a specific interrupt with priority and enable/disable settings. |
### 2. `NVIC.h`
This file contains the declarations of the functions implemented in `NVIC.c` and the necessary macros, enums, and data types for NVIC configuration.

---

## How to Configure NVIC for STM32F4xx

### 1. Include the Header File
Include `NVIC.h` in your source file to use the NVIC driver:
```c
#include "NVIC.h"
```

### 2. Enable an Interrupt
Use the `NVIC_SetInterruptEnable` function to enable a specific interrupt:
```c
NVIC_SetInterruptEnable(_EXTI0_IRQHandler);
```
- **Parameters**:
  - `IRQNumber`: The IRQ number of the interrupt to enable (e.g., `_EXTI0_IRQHandler` for EXTI Line 0 interrupt).

### 3. Set Interrupt Priority
Use the `NVIC_SetPriority` function to set the priority of a specific interrupt:
```c
NVIC_SetPriority(_EXTI0_IRQHandler, 2);
```
- **Parameters**:
  - `IRQNumber`: The IRQ number of the interrupt.
  - `priority`: The priority level (0 is the highest priority, 255 is the lowest).

### 4. Configure NVIC for an Interrupt
Use the `NVIC_Configuration` function to configure an interrupt with priority and enable/disable settings:
```c
NVIC_Config_Variables nvic_config = {
    .IRQNumber = _EXTI0_IRQHandler,  // IRQ number
    .IRQPriority = 2,               // Priority level
    .IRQEnable = ENABLE             // Enable the interrupt
};
NVIC_Configuration(nvic_config);
```
- **Parameters**:
  - `IRQNumber`: The IRQ number of the interrupt.
  - `IRQPriority`: The priority level.
  - `IRQEnable`: Enable (`ENABLE`) or disable (`DISABLE`) the interrupt.

---

## Functions

### NVIC_SetInterruptEnable
- **Description**: Enable a specific interrupt.
- **Parameters**:
  - `IRQNumber`: The IRQ number of the interrupt to enable.
- **Return Value**: None.
- **Example**:
  ```c
  NVIC_SetInterruptEnable(_EXTI0_IRQHandler); // Enable EXTI Line 0 interrupt
  ```

### NVIC_ClearInterruptEnable
- **Description**: Disable a specific interrupt.
- **Parameters**:
  - `IRQNumber`: The IRQ number of the interrupt to disable.
- **Return Value**: None.
- **Example**:
  ```c
  NVIC_ClearInterruptEnable(_EXTI0_IRQHandler); // Disable EXTI Line 0 interrupt
  ```

### NVIC_SetPendingInterrupt
- **Description**: Set a pending flag for a specific interrupt.
- **Parameters**:
  - `IRQNumber`: The IRQ number of the interrupt to set as pending.
- **Return Value**: None.
- **Example**:
  ```c
  NVIC_SetPendingInterrupt(_EXTI0_IRQHandler); // Set EXTI Line 0 interrupt as pending
  ```

### NVIC_ClearPendingInterrupt
- **Description**: Clear a pending flag for a specific interrupt.
- **Parameters**:
  - `IRQNumber`: The IRQ number of the interrupt to clear the pending flag.
- **Return Value**: None.
- **Example**:
  ```c
  NVIC_ClearPendingInterrupt(_EXTI0_IRQHandler); // Clear pending flag for EXTI Line 0 interrupt
  ```

### NVIC_SetPriority
- **Description**: Set the priority of a specific interrupt.
- **Parameters**:
  - `IRQNumber`: The IRQ number of the interrupt.
  - `priority`: The priority level (0 is the highest priority, 255 is the lowest).
- **Return Value**: None.
- **Example**:
  ```c
  NVIC_SetPriority(_EXTI0_IRQHandler, 2); // Set EXTI Line 0 interrupt priority to 2
  ```

### NVIC_Configuration
- **Description**: Configure NVIC for a specific interrupt with priority and enable/disable settings.
- **Parameters**:
  - `NVIC_Config_Variables NVIC_val`: Configuration structure containing IRQ number, priority, and enable/disable settings.
- **Steps Performed**:
  1. Calls `NVIC_Init` to reset the interrupt configuration.
  2. Enables or disables the interrupt using `NVIC_SetInterruptEnable` or `NVIC_ClearInterruptEnable`.
  3. Sets the priority of the interrupt using `NVIC_SetPriority`.
- **Return Value**: None.
- **Example**:
  ```c
    /**
    *******************************************************************************
    * @ Name : NVIC_Configuration
    * @ Parameters: NVIC_Config_Variables NVIC_val
    * @ Registers : NVIC_ISER, NVIC_IPR, NVIC_ICER
    * @ Descriptions :
    *		- Config NVIC for specific IRQNumber:
    *           + IRQNumber: 0 ~ 239
    *           + priority: uint8_t(0~255)
    *           + enable: 0: disable, 1: enable
    * @ Return value : void
    * @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
    * @ date : 2024-07-11
    *******************************************************************************
    */
    void NVIC_Configuration(NVIC_Config_Variables NVIC_val)
    {
        NVIC_Init(NVIC_val.IRQNumber);
        if (NVIC_val.IRQEnable)
        {
            NVIC_SetInterruptEnable(NVIC_val.IRQNumber);
            NVIC_SetPriority(NVIC_val.IRQNumber, NVIC_val.IRQPriority);
        }
        else
        {
            NVIC_ClearInterruptEnable(NVIC_val.IRQNumber);
        }
    }
  ```

---

## Example
Below is an example of how to configure and use NVIC with this driver:

```c
#include "NVIC.h"

int main(void)
{
    // Step 1: Configure NVIC for EXTI Line 0 with priority 2 and enable it
    NVIC_Config_Variables nvic_config = {
        .IRQNumber = _EXTI0_IRQHandler,  // IRQ number
        .IRQPriority = 2,               // Priority level
        .IRQEnable = ENABLE             // Enable the interrupt
    };
    NVIC_Configuration(nvic_config);

    // Step 2: Set EXTI Line 0 as pending
    NVIC_SetPendingInterrupt(_EXTI0_IRQHandler);

    // Step 3: Check the status of EXTI Line 0
    uint8_t status = NVIC_GetStatusInterrupt(_EXTI0_IRQHandler, ENABLE);

    while (1)
    {
        // Main loop
    }
}
```

---

## Notes
- The NVIC supports up to 240 IRQ numbers on STM32F4xx microcontrollers.
- Priority levels range from 0 (highest priority) to 255 (lowest priority).
- Ensure that the IRQ number is valid for the specific microcontroller being used.
- Use the appropriate IRQ handler for the interrupt (e.g., `_EXTI0_IRQHandler` for EXTI Line 0 interrupt).

---

## Author
- **Name**: Nguyen Dinh Thuan
- **Email**: thuan.nd.167@gmail.com
- **Date**: 2024-07-11
