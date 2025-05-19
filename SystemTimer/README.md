# SysTick Driver for STM32F4xx

## Overview
This driver provides a set of functions to configure and control the SysTick timer on STM32F4xx microcontrollers. The SysTick timer is a system timer provided by the ARM Cortex-M4 core, which can be used for periodic interrupts and timekeeping. The driver is implemented in `Systick.c` and its corresponding header file `Systick.h`.

---

## Features
- Configure SysTick timer with different clock sources.
- Set reload values for periodic interrupts.
- Enable or disable SysTick interrupts.
- Get the current counter value of the SysTick timer.
- Generate periodic flags for time intervals (1ms, 10ms, 50ms, 100ms, 500ms, 1s).
- Support for multiple system clock frequencies.

---

## File Structure
### 1. `Systick.c`
This file contains the implementation of SysTick functions, including:
## SysTick Functions

| **Function**                     | **Description**                                                                 |
|-----------------------------------|---------------------------------------------------------------------------------|
| `SysTickGetCountFlag`             | Get the count flag of the SysTick timer.                                        |
| `SysTickSettingEnableCounter`     | Enable or disable the SysTick counter.                                          |
| `SysTickSettingReloadValue`       | Set the reload value for the SysTick timer.                                     |
| `SysTickGetCurrentCounterValue`   | Get the current counter value of the SysTick timer.                             |
| `InitSystemTimer`                 | Initialize the SysTick timer.                                                   |
| `SettingSystemTimer`              | Configure the SysTick timer with clock source, interrupt, and reload value.     |
| `LoopSystickTimerSetting`         | Generate periodic flags for time intervals (1ms, 10ms, etc.).                   |
| `GetFlagTimerSystickXms`          | Get flags for specific time intervals (10ms, 50ms, etc.).                       |

### 2. `Systick.h`
This file contains the declarations of the functions implemented in `Systick.c` and the necessary macros and data types for SysTick configuration.

---

## How to Configure SysTick for STM32F4xx

### 1. Include the Header File
Include `Systick.h` in your source file to use the SysTick driver:
```c
#include "Systick.h"
#include "../RCC/RCC.h"
```

### 2. Initialize the SysTick Timer
Use the `InitSystemTimer` function to initialize the SysTick timer:
```c
InitSystemTimer();
```

### 3. Configure the SysTick Timer
The `SettingSystemTimer` function is used to configure the SysTick timer with the desired clock source, interrupt, and reload value. This function initializes the timer and sets it up for periodic interrupts.

#### Function Prototype
```c
void SettingSystemTimer(uint8_t clksrc, uint8_t tick, float systick_interval);
```

#### Parameters
- **`clksrc`**: Clock source for the SysTick timer.
  - `PROCESSOR_CLKSRC`: Use the processor clock as the SysTick clock source.
  - `EXTERNAL_CLKSRC`: Use an external clock as the SysTick clock source.
- **`tick`**: Enable or disable SysTick interrupt.
  - `ENABLE`: Enable the SysTick interrupt. The `SysTick_Handler` will be called when the timer reaches zero.
  - `DISABLE`: Disable the SysTick interrupt.
- **`systick_interval`**: Time interval in seconds for the SysTick timer.
  - Example: `0.001f` for a 1ms interval, `0.01f` for a 10ms interval.

#### Steps Performed by `SettingSystemTimer`
1. **Initialize the SysTick Timer**:
   - Calls `InitSystemTimer()` to clear the current counter value and set the default reload value.

2. **Select Clock Source**:
   - Configures the SysTick timer to use either the processor clock (`PROCESSOR_CLKSRC`) or an external clock (`EXTERNAL_CLKSRC`).

3. **Enable or Disable Interrupts**:
   - Enables or disables the SysTick interrupt based on the `tick` parameter.

4. **Set Reload Value**:
   - Calculates the reload value based on the `systick_interval` and the clock frequency (`SYSTICK_CLOCK`).
   - The reload value is calculated as:
     ```c
     reloadvalue = systick_interval * SYSTICK_CLOCK - 1;
     ```
   - This value is then set using the `SysTickSettingReloadValue()` function.

5. **Enable the Counter**:
   - Starts the SysTick timer by enabling the counter using `SysTickSettingEnableCounter(ENABLE)`.

#### Example Usage
```c
// Configure the SysTick timer for a 1ms interval using the processor clock
SettingSystemTimer(PROCESSOR_CLKSRC, ENABLE, 0.001f);
```
### 4. Use Periodic Flags
Call the `LoopSystickTimerSetting` function in the SysTick interrupt handler to generate periodic flags for time intervals. This ensures that the flags are updated every time the SysTick interrupt occurs.

#### Updated SysTick_Handler Implementation
```c
void SysTick_Handler(void)
{
    // Increment the 1ms loop counter
    systick_timer_loop_1ms_IT++;
}
```

#### Explanation
1. **Increment Counter**:
   - The `systick_timer_loop_1ms_IT` variable is incremented every time the SysTick interrupt occurs. This counter is used to track elapsed time in milliseconds.

#### Usage in Main Loop
In the main loop, you can check the flags generated by `LoopSystickTimerSetting` to perform periodic tasks:
```c

// Generate periodic flags for time intervals
LoopSystickTimerSetting();

if (GetFlagTimerSystick10ms())
{
    // Perform actions every 10ms
}

if (GetFlagTimerSystick1s())
{
    // Perform actions every 1 second
}
```

### 5. Check Time Interval Flags
Use the `GetFlagTimerSystickXms` functions to check if a specific time interval has elapsed:
```c
if (GetFlagTimerSystick10ms())
{
    // Perform actions every 10ms
}
```

---

## Method to Create Timer Xms Flags
The `LoopSystickTimerSetting` function is responsible for generating periodic flags for specific time intervals (1ms, 10ms, 50ms, 100ms, 500ms, 1s). These flags can be used to trigger periodic tasks in your application.

### How It Works
1. The function increments counters for each time interval (e.g., 10ms, 50ms, etc.).
2. When a counter reaches its threshold, the corresponding flag is set, and the counter is reset.
3. The flags are stored in a `systick_timer_flag` structure, which can be accessed using the `GetFlagTimerSystickXms` functions.

### Example Implementation
```c
void LoopSystickTimerSetting(void)
{
    *((uint8_t *)&systick_timer_fl) = 0;

    if (systick_timer_loop_1ms_IT)
    {
        systick_timer_loop_1ms_IT = 0;
        systick_timer_fl.systick_timer_1ms = SET;
        systick_timer_loop10ms++;
        if (systick_timer_loop10ms >= 10)
        {
            systick_timer_fl.systick_timer_10ms = SET;
            systick_timer_loop10ms = 0;
            systick_timer_loop50ms++;

            if (systick_timer_loop50ms >= 5)
            {
                systick_timer_fl.systick_timer_50ms = SET;
                systick_timer_loop50ms = 0;
                systick_timer_loop100ms++;

                if (systick_timer_loop100ms >= 2)
                {
                    systick_timer_fl.systick_timer_100ms = SET;
                    systick_timer_loop100ms = 0;
                    systick_timer_loop500ms++;

                    if (systick_timer_loop500ms >= 5)
                    {
                        systick_timer_fl.systick_timer_500ms = SET;
                        systick_timer_loop500ms = 0;
                        systick_timer_loop1s++;

                        if (systick_timer_loop1s >= 2)
                        {
                            systick_timer_fl.systick_timer_1s = SET;
                            systick_timer_loop1s = 0;
                        }
                    }
                }
            }
        }
    }
}
```

### Accessing Timer Flags
Use the following functions to access the flags:
- `GetFlagTimerSystick10ms()`: Returns `1` if 10ms has elapsed, `0` otherwise.
- `GetFlagTimerSystick50ms()`: Returns `1` if 50ms has elapsed, `0` otherwise.
- `GetFlagTimerSystick100ms()`: Returns `1` if 100ms has elapsed, `0` otherwise.
- `GetFlagTimerSystick500ms()`: Returns `1` if 500ms has elapsed, `0` otherwise.
- `GetFlagTimerSystick1s()`: Returns `1` if 1 second has elapsed, `0` otherwise.

---

## Example
Below is an example of how to configure and use the SysTick timer with this driver:

```c
#include "Systick.h"

int main(void)
{
    // Step 1: Initialize the SysTick timer
    InitSystemTimer();

    // Step 2: Configure the SysTick timer for 1ms interval with processor clock
    SettingSystemTimer(PROCESSOR_CLKSRC, ENABLE, 0.001f);

    while (1)
    {
        LoopSystickTimerSetting();

        // Check if 10ms has elapsed
        if (GetFlagTimerSystick10ms())
        {
            // Perform actions every 10ms
        }

        // Check if 1s has elapsed
        if (GetFlagTimerSystick1s())
        {
            // Perform actions every 1 second
        }
    }
}

// SysTick interrupt handler
void SysTick_Handler(void)
{
    systick_timer_loop_1ms_IT++;
}
```

---

## Author
- **Name**: Nguyen Dinh Thuan
- **Email**: thuan.nd.167@gmail.com
- **Date**: 2024-07-10
