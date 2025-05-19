# DMA Driver for STM32F4xx

## Overview
This driver provides a set of functions to configure and manage the Direct Memory Access (DMA) peripheral on STM32F4xx microcontrollers. The DMA peripheral allows high-speed data transfer between memory and peripherals without CPU intervention, improving system performance. The driver is implemented in `DMA.c` and its corresponding header file `DMA.h`.

---

## Features
- Support for DMA1 and DMA2 controllers.
- Map peripherals to DMA streams and channels based on STM32F4xx documentation.
- Configure DMA transfer direction:
  - Memory-to-Memory
  - Peripheral-to-Memory
  - Memory-to-Peripheral
- Set data size for memory and peripheral transfers:
  - Byte
  - Halfword
  - Word
- Configure priority levels for DMA streams:
  - Low
  - Medium
  - High
  - Very High
- Enable and configure FIFO for efficient data handling:
  - FIFO thresholds: 1/4, 1/2, 3/4, Full
- Support for circular mode and double-buffer mode.
- Enable and handle DMA interrupts:
  - Transfer Complete
  - Half Transfer
  - Transfer Error
  - FIFO Error
  - Direct Mode Error

---

## File Structure
### 1. `DMA.c`
This file contains the implementation of DMA functions, including:
## File Structure

| **Function**                      | **Description**                                                                 |
|------------------------------------|---------------------------------------------------------------------------------|
| `DMA_Configuration`                | Configure the DMA peripheral with various settings.                             |
| `DMA_EnableStream`                 | Enable a specific DMA stream.                                                  |
| `DMA_DisableStream`                | Disable a specific DMA stream.                                                 |
| `DMA_EnableFIFOErrorIRQ`           | Enable FIFO error interrupt.                                                   |
| `DMA_EnableDirectModeErrorIQR`     | Enable direct mode error interrupt.                                            |
| `DMA_EnableTransferErrorIQR`       | Enable transfer error interrupt.                                               |
| `DMA_EnableHalfTransferIQR`        | Enable half transfer interrupt.                                                |
| `DMA_EnableTransferCompleteIQR`    | Enable transfer complete interrupt.                                            |
| `DMA_Get_IRQ_Flag`                 | Get the status of a specific DMA interrupt flag.                               |
| `GetStreamAndChannelForPeripheral` | Map a peripheral to its corresponding DMA stream and channel.                  |

### 2. `DMA.h`
This file contains the declarations of the functions implemented in `DMA.c` and the necessary macros, enums, and data types for DMA configuration.

---

## How to Configure DMA for STM32F4xx

### 1. Include the Header File
Include `DMA.h` in your source file to use the DMA driver:
```c
#include "DMA.h"
```

### 2. Configure DMA Peripheral
Use the `DMA_Configuration` function to configure the DMA peripheral:
```c
DMA_Variables dma_config = {
    .Peripheral = SPI3_RX,                  // Peripheral to be used with DMA
    .Direction = DIR_MEM2PHE,               // Transfer direction (Memory-to-Peripheral)
    .MemDataSize = PDATA_SIZE_BYTE,         // Memory data size (Byte)
    .PheDataSize = PDATA_SIZE_BYTE,         // Peripheral data size (Byte)
    .PriorityLevel = PL_HIGH,               // Priority level (High)
    .NumOfData = 1,                       // Number of data items to transfer
    .Memory0Address = &(MEM0_add),      // Address of Memory 0
    .Memory1Address = &(MEM1_add),      // Address of Memory 1 (for double-buffer mode)
    .PeripheralAddress = &(Peripheral_add),// Address of the peripheral
    .FIFOEnable = ENABLE,                   // Enable FIFO mode
    .FIFOThreshold = FIFO_THRESHOLD_HALF,   // FIFO threshold (Half)
    .Circular_mode = ENABLE                 // Enable circular mode
};
DMA_Configuration(dma_config);
```

### 3. Enable DMA Stream
Use the `DMA_EnableStream` function to enable the configured DMA stream:
```c
DMA_EnableStream(dma_config);
```

### 4. Disable DMA Stream
Use the `DMA_DisableStream` function to disable the DMA stream:
```c
DMA_DisableStream(dma_config);
```

### 5. Enable DMA Interrupts
Enable specific DMA interrupts using the following functions:
- **FIFO Error Interrupt**:
  ```c
  DMA_EnableFIFOErrorIRQ(dma_config);
  ```
- **Direct Mode Error Interrupt**:
  ```c
  DMA_EnableDirectModeErrorIQR(dma_config);
  ```
- **Transfer Error Interrupt**:
  ```c
  DMA_EnableTransferErrorIQR(dma_config);
  ```
- **Half Transfer Interrupt**:
  ```c
  DMA_EnableHalfTransferIQR(dma_config);
  ```
- **Transfer Complete Interrupt**:
  ```c
  DMA_EnableTransferCompleteIQR(dma_config);
  ```

### 6. Get DMA Interrupt Flag Status
Use the `DMA_Get_IRQ_Flag` function to check the status of a specific DMA interrupt flag:
```c
bool flag_status = DMA_Get_IRQ_Flag(DMA1, DMA_STREAM0, DMA_TRANSFER_COMPLETE_IRQ_FLAG);
```

---

## Functions

### DMA_Configuration
- **Description**: Configure the DMA peripheral with various settings.
- **Parameters**:
  - `DMA_Variables DMA_val`: A structure containing DMA configuration settings.
- **Steps Performed**:
  1. Enable the DMA clock.
  2. Set the transfer direction.
  3. Configure data sizes for memory and peripheral.
  4. Set the number of data items to transfer.
  5. Configure memory and peripheral addresses.
  6. Set the priority level.
  7. Select the DMA channel.
  8. Enable circular mode (if required).
  9. Configure FIFO settings (if enabled).
- **Return Value**: None.
- **Example**:
  ```c
    void DMA_Configuration(DMA_Variables DMA_val)
    {
        uint8_t stream = 0;
        uint8_t channel = 0;
        DMA_Request rq;

        rq = GetStreamAndChannelForPeripheral(DMA_val.Peripheral);
        stream = rq.StreamX;
        channel = rq.Channel;

        // Enable DMA clock
        if (rq.DMAn == DMA1)
            RCC_EnablePeripheralClock(CLOCK_DMA1);
        else
            RCC_EnablePeripheralClock(CLOCK_DMA2);

        // Set Direction
        DMA_DATA_TRANSFER_DIRECTION(rq.DMAn, stream, DMA_val.Direction);

        // Set Data size
        switch (DMA_val.Direction)
        {
            case DIR_MEM2MEM:
                DMA_MEM_DATA_SIZE(rq.DMAn, stream, DMA_val.MemDataSize);
                break;
            case DIR_MEM2PHE:
            case DIR_PHE2MEM:
                DMA_MEM_DATA_SIZE(rq.DMAn, stream, DMA_val.MemDataSize);
                DMA_PERIPHERAL_DATA_SIZE(rq.DMAn, stream, DMA_val.PheDataSize);
                break;
            default:
                break;
        }
        // Set Number of data
        DMA_SET_NUM_OF_DATA(rq.DMAn, stream, DMA_val.NumOfData);

        // Set Peripheral address
        DMA_SET_PHE_ADDRESS(rq.DMAn, stream, DMA_val.PeripheralAddress);

        // Set Memory 0 address
        DMA_SET_MEM0_ADDRESS(rq.DMAn, stream, DMA_val.Memory0Address);
        // Set Memory 1 address
        DMA_SET_MEM1_ADDRESS(rq.DMAn, stream, DMA_val.Memory1Address);

        // Set Priority level
        DMA_PRIORITY_LEVEL(rq.DMAn, stream, DMA_val.PriorityLevel);

        // Set Channel
        DMA_CHANNEL_SELECTION(rq.DMAn, stream, channel);

        // Set Circular mode
        if(DMA_val.Circular_mode == ENABLE)
            DMA_CIRCULAR_MODE_ENABLE(rq.DMAn, stream);

        if(DMA_val.FIFOEnable == ENABLE)
        {
            // Set FIFO mode
            DMA_CIRCULAR_MODE_ENABLE(rq.DMAn, stream);
            DMA_DIRECT_MODE_DISABLE(rq.DMAn, stream);   // Enable FIFO mode by disabling direct mode
            DMA_FIFO_THRESHOLD_SELECTION(rq.DMAn, stream, DMA_val.FIFOThreshold);
        }
    }
  ```

### DMA_EnableStream
- **Description**: Enable a specific DMA stream.
- **Parameters**:
  - `DMA_Variables DMA_val`: A structure containing DMA configuration settings.
- **Return Value**: None.
- **Example**:
  ```c
  DMA_EnableStream(dma_config);
  ```

### DMA_DisableStream
- **Description**: Disable a specific DMA stream.
- **Parameters**:
  - `DMA_Variables DMA_val`: A structure containing DMA configuration settings.
- **Return Value**: None.
- **Example**:
  ```c
  DMA_DisableStream(dma_config);
  ```

### DMA_EnableFIFOErrorIRQ
- **Description**: Enable FIFO error interrupt.
- **Parameters**:
  - `DMA_Variables DMA_val`: A structure containing DMA configuration settings.
- **Return Value**: None.
- **Example**:
  ```c
  DMA_EnableFIFOErrorIRQ(dma_config);
  ```

### DMA_Get_IRQ_Flag
- **Description**: Get the status of a specific DMA interrupt flag.
- **Parameters**:
  - `DMAx *DMAn`: The DMA instance (e.g., `DMA1`, `DMA2`).
  - `uint8_t stream`: The DMA stream number (e.g., `DMA_STREAM0`).
  - `uint8_t flag`: The interrupt flag to check (e.g., `DMA_TRANSFER_COMPLETE_IRQ_FLAG`).
- **Return Value**: `true` if the flag is set, `false` otherwise.
- **Example**:
  ```c
  bool flag_status = DMA_Get_IRQ_Flag(DMA1, DMA_STREAM0, DMA_TRANSFER_COMPLETE_IRQ_FLAG);
  ```

---

## Notes
- Ensure that the DMA clock is enabled before configuring the DMA peripheral.
- Use the `GetStreamAndChannelForPeripheral` function to map peripherals to DMA streams and channels.
- Configure FIFO settings for efficient data handling in high-speed transfers.
- Handle DMA interrupts for error and transfer events as needed.

---

## Author
- **Name**: Nguyen Dinh Thuan
- **Email**: thuan.nd.167@gmail.com
- **Date**: 2025-05-17