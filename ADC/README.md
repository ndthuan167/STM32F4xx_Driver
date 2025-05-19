# ADC Driver for STM32F4xx

## Overview
This driver provides a set of functions to configure and manage the Analog-to-Digital Converter (ADC) on STM32F4xx microcontrollers. The ADC peripheral allows the conversion of analog signals into digital values, supporting multiple channels, resolutions, and sampling times. The driver is implemented in `ADC.c` and its corresponding header file `ADC.h`.

---

## Features
- Support for ADC1, ADC2, and ADC3.
- Configure GPIO pins for ADC channels.
- Enable peripheral and GPIO clocks for ADC and its associated pins.
- Set ADC channel sequences and sampling times.
- Support for multiple resolutions (6-bit, 8-bit, 10-bit, 12-bit).
- Enable scan mode for multi-channel conversions.
- Configure data alignment (left or right).
- Support for DMA (Direct Memory Access) for efficient data transfer.
- Start ADC conversions and retrieve conversion results.

---

## File Structure
### 1. `ADC.c`
This file contains the implementation of ADC functions, including:
| **Function**          | **Description**                                                                 |
|------------------------|---------------------------------------------------------------------------------|
| `ADC_GPIOConfig`       | Configure GPIO pins for ADC channels and enable the necessary clocks.           |
| `ADC_SetSequence`      | Set the sequence of ADC channels.                                               |
| `ADC_Configuration`    | Configure the ADC peripheral with various settings.                             |
| `ADC_Start`            | Start ADC conversions.                                                         |
| `ADC_GetData`          | Retrieve ADC conversion results.                                                |

### 2. `ADC.h`
This file contains the declarations of the functions implemented in `ADC.c` and the necessary macros, enums, and data types for ADC configuration.

---

## How to Configure ADC for STM32F4xx

### 1. Include the Header File
Include `ADC.h` in your source file to use the ADC driver:
```c
#include "ADC.h"
```

### 2. Enable Peripheral and GPIO Clocks
Before configuring the ADC or its associated GPIO pins, ensure that the clocks for the ADC peripheral and GPIO ports are enabled. This is handled automatically in the `ADC_GPIOConfig` function.

#### Example
```c
ADC_GPIOConfig(adc1, ADC_CH0); // Enable clocks for ADC1 and GPIOA for Channel 0
```

| **Step**               | **Description**                                                                 |
|-------------------------|---------------------------------------------------------------------------------|
| **Enable ADC Clock**    | Enables the clock for the specified ADC instance (e.g., `CLOCK_ADC1`).          |
| **Enable GPIO Clock**   | Enables the clock for the GPIO port associated with the ADC channel.            |
| **Configure GPIO Pins** | Configures the GPIO pins as analog pins for ADC operation.                      |

---

### 3. Configure ADC
Use the `ADC_Configuration` function to configure the ADC peripheral:
```c
ADC_Variables adc_config = {
    .ADC_n = adc1,                     // ADC instance
    .prescaler_div = ADC_CLK_DIV_4,    // ADC clock prescaler
    .resolution = ADC_RESOLUTION_12BIT, // ADC resolution
    .eoc_type = EOC_END_OF_CONVERSION, // End of conversion type
    .dma_stop_type = DMA_CONTINUE_AFTER_LAST_CONVERSION, // DMA behavior
    .data_align = DATA_RIGHT_ALIGNMENT, // Data alignment
    .sequence_length = 2,              // Number of channels in sequence
    .channels = {ADC_CH0, ADC_CH1},    // Channels to convert
    .sampling_time = ADC_SPLT_15_CYCLES // Sampling time
};
ADC_Configuration(adc_config);
```

| **Parameter**          | **Description**                                                                 |
|-------------------------|---------------------------------------------------------------------------------|
| `ADC_n`                | Specifies the ADC instance (e.g., `adc1`, `adc2`, `adc3`).                      |
| `prescaler_div`        | Sets the ADC clock prescaler (e.g., `ADC_CLK_DIV_2`, `ADC_CLK_DIV_4`).           |
| `resolution`           | Configures the ADC resolution (e.g., `6-bit`, `8-bit`, `10-bit`, `12-bit`).     |
| `eoc_type`             | Specifies the end-of-conversion type (e.g., `EOC_END_OF_CONVERSION`).           |
| `dma_stop_type`        | Configures DMA behavior after the last conversion.                              |
| `data_align`           | Sets the data alignment (e.g., `DATA_RIGHT_ALIGNMENT`, `DATA_LEFT_ALIGNMENT`).  |
| `sequence_length`      | Specifies the number of channels in the conversion sequence.                    |
| `channels`             | Specifies the ADC channels to convert.                                         |
| `sampling_time`        | Configures the sampling time for each channel.                                  |

---

### 4. Start ADC Conversion
Use the `ADC_Start` function to start ADC conversions:
```c
ADC_Start(adc1);
```

---

### 5. Retrieve ADC Conversion Results
Use the `ADC_GetData` function to retrieve the conversion results:
```c
uint16_t adc_result = ADC_GetData(adc1);
```

---

## Functions

### ADC_GPIOConfig
- **Description**: Configure GPIO pins for ADC channels and enable the necessary clocks.
- **Parameters**:
  - `ADC_x`: The ADC instance (e.g., `adc1`, `adc2`, `adc3`).
  - `Channelx`: The ADC channel number (e.g., `ADC_CH0` for Channel 0).
- **Steps Performed**:
  1. Enable the clock for the specified ADC instance (e.g., `CLOCK_ADC1` for `adc1`).
  2. Enable the clock for the GPIO port associated with the specified ADC channel.
  3. Configure the GPIO pin as an analog pin.
- **Return Value**: None.

---

### ADC_SetSequence
- **Description**: Set the sequence of ADC channels.
- **Parameters**:
  - `ADC_x`: The ADC instance (e.g., `adc1`, `adc2`, `adc3`).
  - `Sequence_index`: The sequence index (e.g., `0` for the first channel in the sequence).
  - `Channel`: The ADC channel number (e.g., `ADC_CH0` for Channel 0).
- **Return Value**: None.

---

### ADC_Configuration
- **Description**: Configure the ADC peripheral with various settings.
- **Parameters**:
  - `ADC_Variables ADC_val`: A structure containing ADC configuration settings.
- **Steps Performed**:
  1. Configure GPIO pins for the specified ADC channels.
  2. Set the sequence of channels in the ADC register.
  3. Set the sampling time for each channel.
  4. Configure the ADC clock prescaler.
  5. Enable scan mode and set the resolution.
  6. Configure conversion mode, DMA, and data alignment.
  7. Enable the ADC.
- **Return Value**: None.
- **Example**:
```c
void ADC_Configuration(ADC_Variables ADC_val)
{
    for(index_sq = 0; index_sq < ADC_val.sequence_length; index_sq++)
    {
        // Config GPIO pin as analog pin for ADC input channel
        ADC_GPIOConfig(ADC_val.ADC_n, ADC_val.channels[index_sq]);

        // Set sequence of channel in ADC register
        ADC_SetSequence(ADC_val.ADC_n, index_sq, ADC_val.channels[index_sq]);
        
        // Set sampling time
        ADC_SET_SAMPLING_TIME(ADC_val.ADC_n, ADC_val.channels[index_sq], ADC_val.sampling_time);
    }

    // Set prescaler to set clock frequency for ADC base on PCLK2 bus clock
    ADC_SET_CLK_PSL(adc_cmm, ADC_val.prescaler_div);

    // Enable Scan mode and set resolution
    ADC_ENABLE_SCAN_MODE(ADC_val.ADC_n);
    ADC_SET_RESOLUTION(ADC_val.ADC_n, ADC_val.resolution);

    // Set conversion mode, DMA, Data alignment for ADC
    ADC_ENABLE_CONTINUOUS_CONVERSION(ADC_val.ADC_n);
    ADC_SET_EOC_TYPE(ADC_val.ADC_n, ADC_val.eoc_type);
    ADC_USING_DMA(ADC_val.ADC_n);
    DMA_AFTER_CONVENSION(ADC_val.ADC_n, ADC_val.dma_stop_type);
    ADC_SET_DATA_ALIGNMENT(ADC_val.ADC_n, ADC_val.data_align);

    // Enable ADC
    ADC_ENABLE(ADC_val.ADC_n);

}
```

---

### ADC_Start
- **Description**: Start ADC conversions.
- **Parameters**:
  - `ADC_x`: The ADC instance (e.g., `adc1`, `adc2`, `adc3`).
- **Return Value**: None.

---

### ADC_GetData
- **Description**: Retrieve ADC conversion results.
- **Parameters**:
  - `ADC_x`: The ADC instance (e.g., `adc1`, `adc2`, `adc3`).
- **Return Value**: The ADC conversion result (`uint16_t`).

---

## Example
Below is an example of how to configure and use the ADC driver:

```c
#include "ADC.h"

int main(void)
{
    // Step 1: Configure GPIO for ADC1 Channel 0
    ADC_GPIOConfig(adc1, ADC_CH0);

    // Step 2: Configure ADC1
    ADC_Variables adc_config = {
        .ADC_n = adc1,
        .prescaler_div = ADC_CLK_DIV_4,
        .resolution = ADC_RESOLUTION_12BIT,
        .eoc_type = EOC_END_OF_CONVERSION,
        .dma_stop_type = DMA_CONTINUE_AFTER_LAST_CONVERSION,
        .data_align = DATA_RIGHT_ALIGNMENT,
        .sequence_length = 1,
        .channels = {ADC_CH0},
        .sampling_time = ADC_SPLT_15_CYCLES
    };
    ADC_Configuration(adc_config);

    // Step 3: Start ADC1 conversion
    ADC_Start(adc1);

    // Step 4: Retrieve ADC1 conversion result
    uint16_t adc_result = ADC_GetData(adc1);

    while (1)
    {
        // Main loop
    }
}
```

---

## Notes
- Ensure that the GPIO pins used for ADC channels are configured as analog pins.
- The ADC clock prescaler must be configured based on the PCLK2 bus clock to ensure the ADC operates within its frequency range.
- Use DMA for efficient data transfer when performing multi-channel conversions.
- The ADC resolution and sampling time should be chosen based on the application's requirements for accuracy and speed.

---

## Author
- **Name**: Nguyen Dinh Thuan
- **Email**: thuan.nd.167@gmail.com
- **Date**: 2025-05-15