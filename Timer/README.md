# Timer Driver for STM32F4xx

## Overview
This driver provides a set of functions to configure and manage timers on STM32F4xx microcontrollers. Timers are essential peripherals used for generating delays, measuring input signals, and generating PWM signals. This driver supports both basic and advanced timer configurations, including input capture and output compare modes.

---

## Features
- Enable and configure timers (TIM1 to TIM14).
- Configure timer prescaler and auto-reload values.
- Enable and disable timer counters.
- Configure timer interrupts for periodic events.
- Support for input capture mode to measure external signals.
- Support for output compare mode to generate PWM or timed signals.
- Clear and manage timer interrupt flags.
- Generate periodic flags for 1ms, 10ms, 50ms, 100ms, 500ms, and 1s intervals.

---

## File Structure
### 1. `Timer.c`
This file contains the implementation of timer functions, including:

| **Function**                      | **Description**                                                                 |
|------------------------------------|---------------------------------------------------------------------------------|
| `Timer_EnableClock`                | Enable the clock for a specific timer.                                          |
| `Timer_Configuration`              | Configure the timer with prescaler, auto-reload, and interrupt settings.        |
| `Timer_SettingCounter`             | Enable or disable the timer counter.                                            |
| `Timer_SettingInterrupt`           | Enable or disable timer interrupts.                                             |
| `Timer_ClearInterruptFlag`         | Clear the interrupt flag for a specific timer.                                  |
| `LoopTimerSetting`                 | Generate periodic flags for 1ms, 10ms, 50ms, 100ms, 500ms, and 1s intervals.    |
| `GetFlagTimerXms`                  | Get the status of periodic flags (1ms, 10ms, 50ms, etc.).                       |
| `Timer_InputCaptureConfiguration`  | Configure the timer for input capture mode.                                     |
| `Timer_GetCaptureValue`            | Get the captured value from a specific timer channel.                           |
| `Timer_OutputCompareConfiguration` | Configure the timer for output compare mode.                                    |

### 2. `Timer.h`
This file contains the declarations of the functions implemented in `Timer.c` and the necessary macros, enums, and data types for timer configuration.

---

## How to Configure Timers for STM32F4xx

### 1. Include the Header File
Include `Timer.h` in your source file to use the timer driver:
```c
#include "Timer.h"
```

### 2. Enable Timer Clock
Use the `Timer_EnableClock` function to enable the clock for a specific timer:
```c
Timer_EnableClock((TIMER *)ADDRESS_TIMER_2); // Enable clock for TIM2
```

### 3. Configure Timer
Use the `Timer_Configuration` function to configure the timer with prescaler, auto-reload, and interrupt settings:
```c
Timer_Configuration((TIMER *)ADDRESS_TIMER_2, TIMER_1MS); // Configure TIM2 for 1ms periodic interrupts
```

### 4. Enable Timer Counter
Use the `Timer_SettingCounter` function to enable or disable the timer counter:
```c
Timer_SettingCounter((TIMER *)ADDRESS_TIMER_2, ENABLE); // Enable TIM2 counter
```

### 5. Configure Input Capture
Use the `Timer_InputCaptureConfiguration` function to configure the timer for input capture mode:
```c
Timer_InputCaptureConfiguration((TIMER *)ADDRESS_TIMER_2, TIMER_CHANNEL_1, TI1, RISING_EDGE, 0, ENABLE, ENABLE);
```

### 6. Configure Output Compare
Use the `Timer_OutputCompareConfiguration` function to configure the timer for output compare mode:
```c
Timer_OutputCompareConfiguration((TIMER *)ADDRESS_TIMER_2, TIMER_CHANNEL_1, PWM_MODE, 0, 1000);
```

---

## Functions

### Timer_EnableClock
- **Description**: Enable the clock for a specific timer.
- **Parameters**:
  - `TIMER *timex`: The timer instance (e.g., `ADDRESS_TIMER_1`, `ADDRESS_TIMER_2`).
- **Registers Used**: AHB1ENR, APB1ENR, APB2ENR.
- **Return Value**: None.

---

### Timer_Configuration
- **Description**: This function configures a timer with the specified prescaler, auto-reload value, and interrupt settings. It is used to set up the timer for periodic events or other timing-related tasks.

#### **Parameters**
| **Parameter**       | **Type**      | **Description**                                                                 |
|---------------------|---------------|---------------------------------------------------------------------------------|
| `TIMER *timerx`     | `TIMER *`     | The timer instance (e.g., `ADDRESS_TIMER_1`, `ADDRESS_TIMER_2`).                |
| `float timer_flag`  | `float`       | The timer interval in milliseconds (e.g., `TIMER_1MS`, `TIMER_10MS`).           |

#### **Registers Used**
- **TIM_CR1**: Control register 1 (used to configure the timer's basic operation).
- **TIM_SMCR**: Slave mode control register (used for advanced configurations).
- **TIM_DIER**: DMA/Interrupt enable register (used to enable timer interrupts).
- **TIM_PSC**: Prescaler register (used to divide the timer clock frequency).
- **TIM_ARR**: Auto-reload register (used to set the timer's period).

---

#### **How It Works**
1. **Calculate Prescaler and Auto-Reload Values**:
   - The function calculates the prescaler and auto-reload values based on the desired timer interval (`timer_flag`) and the system clock frequency (`INTERNAL_CLOCK`).

2. **Configure Timer Registers**:
   - The prescaler value is written to the **TIM_PSC** register to divide the timer clock.
   - The auto-reload value is written to the **TIM_ARR** register to define the timer's period.

3. **Enable Timer Interrupts**:
   - The **TIM_DIER** register is configured to enable the update interrupt.

4. **Start the Timer**:
   - The timer is started by setting the appropriate bits in the **TIM_CR1** register.

---

#### **Code Implementation**
Below is an example implementation of the `Timer_Configuration` function:

```c
void Timer_Configuration(TIMER *timerx, float timer_flag)
{

    uint16_t prescaler_val = 0;
    uint32_t reload_val = 0;

    // Enable Clock
    Timer_EnableClock(timerx);
// 
    // reload_val = (timer_flag * INTERNAL_CLOCK) - 1;
    reload_val = 0x4F;
    // TIMER_SET_CLOCK_DEVISION(timerx, clk_division);
    TIMER_SET_PRESCALER(timerx, prescaler_val);

    if (timerx == (TIMER *)ADDRESS_TIMER_2 || timerx == (TIMER *)ADDRESS_TIMER_5)
    {
        TIMER_SET_COUNTER_VALUE_TIME2_5(timerx, 0x00);
        TIMER_SET_AUTORELOAD_VALUE_TIM2_5(timerx, reload_val);
    }
    else
    {
        TIMER_SET_COUNTER_VALUE(timerx, 0x00);
        TIMER_SET_AUTORELOAD_VALUE(timerx, reload_val);
    }
    Timer_SettingCounter(timerx, ENABLE);
    Timer_SettingInterrupt(timerx, ENABLE);
}

```
#### **Notes**
1. **Timer Interval**:
   - Ensure that the `timer_flag` parameter is within the valid range for the timer's resolution and clock frequency.

2. **Interrupt Handling**:
   - The function enables the timer interrupt, so an appropriate interrupt handler must be implemented to handle timer events.

3. **Clock Configuration**:
   - Ensure that the system clock and timer clock are configured correctly before calling this function.

4. **Prescaler and Auto-Reload**:
   - The prescaler and auto-reload values are calculated based on the system clock frequency (`INTERNAL_CLOCK`). Ensure that the `INTERNAL_CLOCK` macro is defined correctly in your project.

---

#### **Common Timer Intervals**
| **Interval** | **Macro**      | **Description**                     |
|--------------|----------------|-------------------------------------|
| 1 ms         | `TIMER_1MS`    | Configure the timer for 1ms events. |
| 10 ms        | `TIMER_10MS`   | Configure the timer for 10ms events.|
| 50 ms        | `TIMER_50MS`   | Configure the timer for 50ms events.|
| 100 ms       | `TIMER_100MS`  | Configure the timer for 100ms events.|
| 500 ms       | `TIMER_500MS`  | Configure the timer for 500ms events.|
| 1 s          | `TIMER_1S`     | Configure the timer for 1s events.  |
---

### Timer_SettingCounter
- **Description**: Enable or disable the timer counter.
- **Parameters**:
  - `TIMER *timerx`: The timer instance.
  - `uint8_t value`: `ENABLE` to enable the counter, `DISABLE` to disable it.
- **Registers Used**: TIM_CR1.
- **Return Value**: None.

---

### Timer_SettingInterrupt
- **Description**: Enable or disable timer interrupts.
- **Parameters**:
  - `TIMER *timerx`: The timer instance.
  - `uint8_t value`: `ENABLE` to enable interrupts, `DISABLE` to disable them.
- **Registers Used**: TIM_DIER.
- **Return Value**: None.

---

### Timer_ClearInterruptFlag
- **Description**: Clear the interrupt flag for a specific timer.
- **Parameters**:
  - `TIMER *timerx`: The timer instance.
- **Registers Used**: TIM_SR.
- **Return Value**: None.

---

### LoopTimerSetting
- **Description**: This function generates periodic flags for 1ms, 10ms, 50ms, 100ms, 500ms, and 1s intervals. These flags can be used in the main loop or interrupt handlers to perform periodic tasks without blocking the CPU.

---

#### **How It Works**
### 1. Timer Interrupt Dependency
- The `LoopTimerSetting` function is designed to be called inside the timer interrupt handler (e.g., `TIMx_IRQHandler`).
- It relies on a 1ms timer interrupt to increment an internal counter (`timer_loop1ms_IT`).

### 2. Increment Internal Counter
- Each time the function is called (every 1ms), the `timer_loop1ms_IT` counter is incremented.

### 3. Generate Periodic Flags
- Based on the value of `timer_loop1ms_IT`, the function generates flags for specific intervals:
  - **10ms**: `timer_loop10ms`
  - **50ms**: `timer_loop50ms`
  - **100ms**: `timer_loop100ms`
  - **500ms**: `timer_loop500ms`
  - **1s**: `timer_loop1s`
- These flags are set when the corresponding interval is reached.

### 4. Reset Internal Counter
- After 1 second (1000ms), the `timer_loop1ms_IT` counter is reset to 0 to start a new cycle.

### 5. Flag Usage
- The generated flags can be checked in the main loop or other parts of the program to execute periodic tasks.
- After processing, the flags should be reset to avoid repeated execution.

---

#### **Code Implementation**
Below is an example implementation of the `LoopTimerSetting` function:

```c
void LoopTimerSetting(void)
{
    *((uint8_t *)&timer_fl) = 0;

    if (timer_loop1ms_IT)
    {
        timer_fl.timer_1ms = SET;
        timer_loop1ms_IT = 0;
        timer_loop10ms++;
        if (timer_loop10ms >= 10)
        {
            timer_fl.timer_10ms = SET;
            timer_loop10ms = 0;
            timer_loop50ms++;

            if (timer_loop50ms >= 5)
            {
                timer_fl.timer_50ms = SET;
                timer_loop50ms = 0;
                timer_loop100ms++;

                if (timer_loop100ms >= 2)
                {
                    timer_fl.timer_100ms = SET;
                    timer_loop100ms = 0;
                    timer_loop500ms++;

                    if (timer_loop500ms >= 5)
                    {
                        timer_fl.timer_500ms = SET;
                        timer_loop500ms = 0;
                        timer_loop1s++;

                        if (timer_loop1s >= 2)
                        {
                            timer_fl.timer_1s = SET;
                            timer_loop1s = 0;
                        }
                    }
                }
            }
        }
    }
}
```
#### **Notes**
1. **Timer Configuration**:
   - Ensure that the timer is configured for 1ms periodic interrupts before using this function.

2. **Flag Reset**:
   - Always reset the flags (`timer_loop10ms`, `timer_loop100ms`, etc.) after processing them to avoid repeated execution.

3. **Interrupt Dependency**:
   - This function must be called inside the timer interrupt handler to ensure accurate timing.

4. **Scalability**:
   - Additional flags can be added for other intervals by modifying the function.

---

#### **Common Flags**
| **Flag**           | **Interval** | **Description**                     |
|---------------------|--------------|-------------------------------------|
| `timer_loop1ms_IT`  | 1 ms         | Internal counter for 1ms intervals. |
| `timer_loop10ms`    | 10 ms        | Flag for 10ms periodic tasks.       |
| `timer_loop50ms`    | 50 ms        | Flag for 50ms periodic tasks.       |
| `timer_loop100ms`   | 100 ms       | Flag for 100ms periodic tasks.      |
| `timer_loop500ms`   | 500 ms       | Flag for 500ms periodic tasks.      |
| `timer_loop1s`      | 1 s          | Flag for 1s periodic tasks.         |
---

### Timer_InputCaptureConfiguration
- **Description**: Configure the timer for input capture mode.
- **Parameters**:
  - `TIMER *timerx`: The timer instance.
  - `uint8_t channel`: The timer channel (e.g., `TIMER_CHANNEL_1`).
  - `uint8_t TIx`: The input pin (e.g., `TI1`).
  - `uint8_t edge`: The edge type (e.g., `RISING_EDGE`, `FALLING_EDGE`).
  - `uint16_t prescaler`: The prescaler value.
  - `uint8_t interrupt`: Enable or disable interrupts.
  - `uint8_t enable`: Enable or disable input capture.
- **Return Value**: None.

---

### Timer_GetCaptureValue
- **Description**: Get the captured value from a specific timer channel.
- **Parameters**:
  - `TIMER *timerx`: The timer instance.
  - `uint8_t channel`: The timer channel (e.g., `TIMER_CHANNEL_1`).
- **Return Value**: The captured value (`uint16_t`).

---

### Timer_OutputCompareConfiguration
- **Description**: Configure the timer for output compare mode.
- **Parameters**:
  - `TIMER *timerx`: The timer instance.
  - `uint8_t channel`: The timer channel (e.g., `TIMER_CHANNEL_1`).
  - `uint8_t mode`: The output compare mode (e.g., `PWM_MODE`).
  - `uint16_t prescaler`: The prescaler value.
  - `uint32_t compare`: The compare value.
- **Return Value**: None.

---

## Example
Below is an example of how to configure and use the timer driver:

```c
#include "Timer.h"

int main(void)
{
    // Step 1: Enable the clock for TIM2
    Timer_EnableClock((TIMER *)ADDRESS_TIMER_2);

    // Step 2: Configure TIM2 for 1ms periodic interrupts
    Timer_Configuration((TIMER *)ADDRESS_TIMER_2, TIMER_1MS);

    // Step 3: Enable the TIM2 counter
    Timer_SettingCounter((TIMER *)ADDRESS_TIMER_2, ENABLE);

    while (1)
    {
        // Check if 1ms flag is set
        if (GetFlagTimer1ms())
        {
            // Perform 1ms tasks
        }
    }
}
```

---

## Notes
- Ensure that the timer clock is enabled before configuring the timer.
- Use appropriate prescaler and auto-reload values to achieve the desired timer frequency.
- Handle timer interrupts carefully to avoid missing events.

---

## Author
- **Name**: Nguyen Dinh Thuan
- **Email**: thuan.nd.167@gmail.com
- **Date**: 2024-07-19