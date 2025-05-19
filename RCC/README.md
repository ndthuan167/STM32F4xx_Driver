# RCC Driver for STM32F4xx

## Overview
This driver provides a set of functions to configure and manage the Reset and Clock Control (RCC) peripheral on STM32F4xx microcontrollers. The RCC peripheral is responsible for configuring the system clock, enabling/disabling peripheral clocks, and managing PLL configurations. The driver is implemented in `RCC.c` and its corresponding header file `RCC.h`.

---

## Features
- Configure the system clock with various frequencies (16 MHz, 24 MHz, 36 MHz, 48 MHz, 56 MHz, 72 MHz).
- Configure the PLL (Phase-Locked Loop) parameters (PLLM, PLLN, PLLP, PLLQ).
- Enable or disable peripheral clocks for AHB1, APB1, and APB2 buses.
- Configure MCU output clock (MCO1, MCO2) with different sources and prescalers.
- Enable alternate HSE sources (CSS, HSE bypass).
- Support for multiple clock sources (HSI, HSE, PLL).
- Configure AHB, APB1, and APB2 clock dividers.

---

## File Structure
### 1. `RCC.c`
This file contains the implementation of RCC functions, including:

| **Function**                      | **Description**                                                                 |
|------------------------------------|---------------------------------------------------------------------------------|
| `RCC_SetPLLIndexValue`             | Configure the PLL parameters (PLLM, PLLN, PLLP, PLLQ).                          |
| `RCC_SettingSystemClock16MHz`      | Configure the system clock to 16 MHz using HSI.                                 |
| `RCC_SettingSystemClock24MHz`      | Configure the system clock to 24 MHz using PLL with HSI as the source.          |
| `RCC_SettingSystemClock36MHz`      | Configure the system clock to 36 MHz using PLL with HSI as the source.          |
| `RCC_SettingSystemClock48MHz`      | Configure the system clock to 48 MHz using PLL with HSI as the source.          |
| `RCC_SettingSystemClock56MHz`      | Configure the system clock to 56 MHz using PLL with HSI as the source.          |
| `RCC_SettingSystemClock72MHz`      | Configure the system clock to 72 MHz using PLL with HSI as the source.          |
| `RCC_EnableAnotherSourceForHSE`    | Enable alternate HSE sources (CSS or HSE bypass).                               |
| `RCC_SettingMCUOutputClock`        | Configure MCU output clock (MCO1, MCO2) with different sources and prescalers.  |
| `RCC_EnablePeripheralClock`        | Enable the clock for a specific peripheral on AHB1, APB1, or APB2 buses.        |

### 2. `RCC.h`
This file contains the declarations of the functions implemented in `RCC.c` and the necessary macros, enums, and data types for RCC configuration.

---

## How to Configure RCC for STM32F4xx

### 1. Include the Header File
Include `RCC.h` in your source file to use the RCC driver:
```c
#include "RCC.h"
```

### 2. Configure the PLL
Use the `RCC_SetPLLIndexValue` function to configure the PLL parameters:
```c
RCC_SetPLLIndexValue(8, 72, 2, 4); // Configure PLLM = 8, PLLN = 72, PLLP = 2, PLLQ = 4
```

### 3. Configure the System Clock
Use one of the predefined functions to configure the system clock:
```c
RCC_SettingSystemClock72MHz(); // Configure the system clock to 72 MHz
```

### 4. Enable Peripheral Clocks
Use the `RCC_EnablePeripheralClock` function to enable the clock for a specific peripheral:
```c
RCC_EnablePeripheralClock(CLOCK_GPIOA); // Enable the clock for GPIOA
```

### 5. Configure MCU Output Clock
Use the `RCC_SettingMCUOutputClock` function to configure the MCU output clock:
```c
RCC_SettingMCUOutputClock(MCO1_ENABLE, OUT1_HSI_CLK, 1); // Configure MCO1 to output HSI clock with no prescaler
```

---

## Functions

### RCC_SetPLLIndexValue
- **Description**: Configure the PLL parameters (PLLM, PLLN, PLLP, PLLQ).
- **Parameters**:
  - `uint8_t PLLM`: Division factor for the main PLL input clock (range: 2 to 63).
  - `uint8_t PLLN`: Multiplication factor for the main PLL (range: 50 to 432).
  - `uint8_t PLLP`: Division factor for the main system clock (values: 2, 4, 6, 8).
  - `uint8_t PLLQ`: Division factor for the USB OTG FS, SDIO, and RNG clocks (values: 2, 4, 6, 8).
- **Return Value**: None.

---

### RCC_SettingSystemClockXXMHz
- **Description**: These functions configure the system clock to a specific frequency using the HSI (High-Speed Internal) oscillator as the clock source. The functions set up the PLL (Phase-Locked Loop) and configure the AHB, APB1, and APB2 prescalers to achieve the desired system clock frequency.

#### **Available Functions**
| **Function**                  | **Description**                                                                 |
|--------------------------------|---------------------------------------------------------------------------------|
| `RCC_SettingSystemClock16MHz`  | Configure the system clock to 16 MHz using HSI directly without PLL.            |
| `RCC_SettingSystemClock24MHz`  | Configure the system clock to 24 MHz using PLL with HSI as the source.          |
| `RCC_SettingSystemClock36MHz`  | Configure the system clock to 36 MHz using PLL with HSI as the source.          |
| `RCC_SettingSystemClock48MHz`  | Configure the system clock to 48 MHz using PLL with HSI as the source.          |
| `RCC_SettingSystemClock56MHz`  | Configure the system clock to 56 MHz using PLL with HSI as the source.          |
| `RCC_SettingSystemClock72MHz`  | Configure the system clock to 72 MHz using PLL with HSI as the source.          |

---

#### **Registers Used**
- **CR**: Clock Control Register.
- **CFGR**: Clock Configuration Register.
- **PLLCFGR**: PLL Configuration Register.
- **AHB1ENR**: AHB1 Peripheral Clock Enable Register.

---

#### **How It Works**
1. **Enable HSI**:
   - The HSI oscillator is enabled as the clock source.

2. **Configure PLL**:
   - The PLL is configured with specific values for `PLLM`, `PLLN`, `PLLP`, and `PLLQ` to achieve the desired system clock frequency.

3. **Set System Clock Source**:
   - The system clock source is switched to the PLL output.

4. **Configure Prescalers**:
   - The AHB, APB1, and APB2 prescalers are configured to divide the clock appropriately for different buses.

---

#### **Code Implementation**
Below is an example implementation for `RCC_SettingSystemClock72MHz`:

```c
void RCC_SettingSystemClock72MHz(void)
{
    // Enable HSI
    RCC_SET_HSI_ON(_RCC);
    while (!RCC_GET_FLAG_HSI_READY(_RCC)); // Wait until HSI is ready

    // Configure PLL
    RCC_SET_PLLM(_RCC, 8);  // PLLM = 8
    RCC_SET_PLLN(_RCC, 72); // PLLN = 72
    RCC_SET_PLLP(_RCC, 2);  // PLLP = 2
    RCC_SET_PLLQ(_RCC, 4);  // PLLQ = 4

    // Enable PLL
    RCC_SET_PLL_ON(_RCC);
    while (!RCC_GET_FLAG_PLL_READY(_RCC)); // Wait until PLL is ready

    // Set PLL as system clock source
    RCC_SET_SYSCLK_SOURCE(_RCC, SYSCLK_PLL);
    while (RCC_GET_SYSCLK_SOURCE(_RCC) != SYSCLK_PLL); // Wait until PLL is used as system clock

    // Configure AHB, APB1, and APB2 prescalers
    RCC_SET_AHB_PRESCALER(_RCC, AHB_PRESCALER_1);   // AHB = SYSCLK / 1
    RCC_SET_APB1_PRESCALER(_RCC, APB1_PRESCALER_2); // APB1 = SYSCLK / 2
    RCC_SET_APB2_PRESCALER(_RCC, APB2_PRESCALER_1); // APB2 = SYSCLK / 1
}
```

---

#### **Example Usage**
```c
// Configure the system clock to 16 MHz
RCC_SettingSystemClock16MHz();

// Configure the system clock to 72 MHz
RCC_SettingSystemClock72MHz();
```
---

#### **Notes**
1. **Clock Stability**:
   - Ensure that the PLL parameters are configured correctly to avoid unstable clock behavior.

2. **Prescaler Configuration**:
   - The AHB, APB1, and APB2 prescalers must be configured appropriately to ensure that the peripheral clocks do not exceed their maximum frequencies.

3. **Power Consumption**:
   - Higher system clock frequencies result in increased power consumption. Choose the frequency based on the application requirements.

4. **Error Handling**:
   - The functions do not perform error checking for invalid PLL configurations. Ensure that the PLL parameters are valid before calling the functions.
---

### RCC_EnablePeripheralClock
- **Description**: This function enables the clock for a specific peripheral on the AHB1, APB1, or APB2 buses. It ensures that the peripheral is powered and ready for use by enabling its corresponding clock in the RCC registers.

#### **Parameters**
| **Parameter**       | **Type**      | **Description**                                                                 |
|---------------------|---------------|---------------------------------------------------------------------------------|
| `Peripheral`        | `uint8_t`     | The peripheral to enable the clock for. This value is mapped to specific peripherals on the AHB1, APB1, or APB2 buses. |

#### **Registers Used**
- **AHB1ENR**: AHB1 Peripheral Clock Enable Register.
- **APB1ENR**: APB1 Peripheral Clock Enable Register.
- **APB2ENR**: APB2 Peripheral Clock Enable Register.

#### **How It Works**
1. **Determine the Peripheral Bus**:
   - If the `Peripheral` value is less than `CLOCK_TIM2`, it belongs to the **AHB1** bus.
   - If the `Peripheral` value is between `CLOCK_TIM2` and `CLOCK_TIM1`, it belongs to the **APB1** bus.
   - Otherwise, it belongs to the **APB2** bus.

2. **Enable the Clock**:
   - The function reads the current value of the corresponding clock enable register (e.g., `AHB1ENR`, `APB1ENR`, or `APB2ENR`).
   - It sets the bit corresponding to the `Peripheral` in the register.
   - The updated value is written back to the register to enable the clock.

#### **Code Implementation**
```c
void RCC_EnablePeripheralClock(uint8_t Peripheral)
{
    uint32_t value = 0;

    // Check if the peripheral belongs to the AHB1 bus
    if (Peripheral < CLOCK_TIM2)
    {
        value = RCC_GET_AHB1ENR(_RCC); // Read the current AHB1ENR value
        value |= (1 << Peripheral);   // Set the bit corresponding to the peripheral
        RCC_SET_AHB1ENR(_RCC, value); // Write back the updated value
    }
    // Check if the peripheral belongs to the APB1 bus
    else if (Peripheral < CLOCK_TIM1)
    {
        value = RCC_GET_APB1ENR(_RCC); // Read the current APB1ENR value
        value |= (1 << (Peripheral - CLOCK_TIM2)); // Set the bit for the peripheral
        RCC_SET_APB1ENR(_RCC, value); // Write back the updated value
    }
    // Otherwise, the peripheral belongs to the APB2 bus
    else
    {
        value = RCC_GET_APB2ENR(_RCC); // Read the current APB2ENR value
        value |= (1 << (Peripheral - CLOCK_TIM1)); // Set the bit for the peripheral
        RCC_SET_APB2ENR(_RCC, value); // Write back the updated value
    }
}
```

#### **Example Usage**
```c
// Enable the clock for GPIOA (AHB1 bus)
RCC_EnablePeripheralClock(CLOCK_GPIOA);

// Enable the clock for TIM2 (APB1 bus)
RCC_EnablePeripheralClock(CLOCK_TIM2);

// Enable the clock for USART1 (APB2 bus)
RCC_EnablePeripheralClock(CLOCK_USART1);
```

#### **Notes**
1. **Peripheral Mapping**:
   - The `Peripheral` parameter must be mapped to the correct peripheral index as defined in the `RCC.h` file. For example:
     - `CLOCK_GPIOA` for GPIOA on AHB1.
     - `CLOCK_TIM2` for TIM2 on APB1.
     - `CLOCK_USART1` for USART1 on APB2.

2. **Clock Dependencies**:
   - Ensure that the system clock is configured correctly before enabling peripheral clocks.
   - Some peripherals may require additional configurations after enabling their clocks.

3. **Error Handling**:
   - The function does not perform error checking for invalid `Peripheral` values. Ensure that the `Peripheral` parameter is valid before calling the function.
---

### RCC_SettingMCUOutputClock
- **Description**: Configure MCU output clock (MCO1, MCO2) with different sources and prescalers.
- **Parameters**:
  - `uint8_t MCOx`: The MCU output clock to configure (`MCO1_ENABLE`, `MCO2_ENABLE`).
  - `uint8_t MCUx_Source`: The clock source for the output (e.g., `OUT1_HSI_CLK`, `OUT1_HSE_CLK`).
  - `uint8_t MCUx_Prescaler`: The prescaler for the output clock (range: 1 to 5).
- **Return Value**: None.

---

### RCC_EnableAnotherSourceForHSE
- **Description**: Enable alternate HSE sources (CSS or HSE bypass).
- **Parameters**:
  - `uint8_t Source`: The alternate source to enable (`CSS_ENABLE`, `HSE_BYPASS_ENABLE`).
- **Return Value**: None.

---

## Example
Below is an example of how to configure the RCC driver:

```c
#include "RCC.h"

int main(void)
{
    // Step 1: Configure the PLL
    RCC_SetPLLIndexValue(8, 72, 2, 4);

    // Step 2: Configure the system clock to 72 MHz
    RCC_SettingSystemClock72MHz();

    // Step 3: Enable the clock for GPIOA
    RCC_EnablePeripheralClock(CLOCK_GPIOA);

    // Step 4: Configure MCO1 to output HSI clock with no prescaler
    RCC_SettingMCUOutputClock(MCO1_ENABLE, OUT1_HSI_CLK, 1);

    while (1)
    {
        // Main loop
    }
}
```

---

## Notes
- Ensure that the PLL parameters are configured correctly to avoid unstable clock behavior.
- Use the appropriate clock source and prescaler settings based on the application requirements.
- Always enable the peripheral clock before accessing the peripheral registers.

---

## Author
- **Name**: Nguyen Dinh Thuan
- **Email**: thuan.nd.167@gmail.com
- **Date**: 2025-02-28