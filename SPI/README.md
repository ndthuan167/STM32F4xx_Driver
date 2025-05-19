# SPI Driver for STM32F4xx

## Overview
This driver provides a set of functions to configure and manage the Serial Peripheral Interface (SPI) peripheral on STM32F4xx microcontrollers. The SPI peripheral is used for high-speed synchronous serial communication between devices. The driver supports master and slave modes, data transmission and reception using polling, DMA, and interrupts. The driver is implemented in `SPI.c` and its corresponding header file `SPI.h`.

---

## Features
- Support for SPI1, SPI2, and SPI3 peripherals.
- Configure GPIO pins for SPI communication (NSS, SCK, MISO, MOSI).
- Support for master and slave modes.
- Configure clock polarity (CPOL) and clock phase (CPHA).
- Support for different data frame formats (8-bit or 16-bit).
- Transmit and receive data using polling, DMA, or interrupts.
- Enable and handle SPI interrupts for transmission and reception.
- Support for full-duplex and receive-only modes.
- Configure software or hardware NSS (slave select) management.

---

## File Structure
### 1. `SPI.c`
This file contains the implementation of SPI functions, including:
- **SPI_ConfigGPIOPinForSPI**: Configure GPIO pins for SPI communication.
- **SPI_Configuration**: Configure the SPI peripheral with various settings.
- **SPI_SlaveSelect**: Select a slave device by driving the NSS pin low.
- **SPI_SlaveDisSelect**: Deselect a slave device by driving the NSS pin high.
- **SPI_Transmiter**: Transmit data using polling.
- **SPI_Transmiter_DMA**: Transmit data using DMA.
- **SPI_ReceiveData**: Receive data using polling.
- **SPI_ReceiveData_DMA**: Receive data using DMA.
- **SPI_TransmitDataInterruptEnable**: Enable the transmitter interrupt.
- **SPI_ReceiverDataInterruptEnable**: Enable the receiver interrupt.

### 2. `SPI.h`
This file contains the declarations of the functions implemented in `SPI.c` and the necessary macros, enums, and data types for SPI configuration.

---

## How to Configure SPI for STM32F4xx

### 1. Include the Header File
Include `SPI.h` in your source file to use the SPI driver:
```c
#include "SPI.h"
```

### 2. Configure SPI Peripheral
Use the `SPI_Configuration` function to configure the SPI peripheral:
```c
SPI_Config_Variables spi_config = {
    .spi_x = (SPIn *)ADDRESS_SPI_1,       // SPI instance
    .spi_mode = MASTER_MODE,              // SPI mode (Master or Slave)
    .sampling_type = FIRST_CLOCK_IDLE,    // Clock polarity and phase
    .clock_prescaler = BAUD_RATE_DIV_16,  // Clock prescaler (only for Master mode)
    .data_read_fr = MSB_FIRST,            // Data frame format (MSB or LSB first)
    .receive_mode = FULL_DUPLEX_MODE,     // Receive mode (Full-duplex or Receive-only)
    .data_fr = DATA_FRAME_8_BITS,         // Data frame size (8-bit or 16-bit)
    .slave_mode_type = SOFTWARE_SLAVE_SELECT // NSS management (Software or Hardware)
};
SPI_Configuration(spi_config);
```

### 3. Transmit Data
Use the `SPI_Transmiter` function to send data over SPI:
```c
uint8_t data[] = {0x01, 0x02, 0x03};
SPI_Transmiter((SPIn *)ADDRESS_SPI_1, data, sizeof(data));
```

### 4. Receive Data
Use the `SPI_ReceiveData` function to receive data over SPI:
```c
uint8_t received_data[3];
SPI_ReceiveData((SPIn *)ADDRESS_SPI_1, received_data, sizeof(received_data));
```

### 5. Transmit Data Using DMA
Use the `SPI_Transmiter_DMA` function to send data using DMA:
```c
uint8_t data[] = {0x01, 0x02, 0x03};
SPI_Transmiter_DMA((SPIn *)ADDRESS_SPI_1, data, sizeof(data));
```

### 6. Receive Data Using DMA
Use the `SPI_ReceiveData_DMA` function to receive data using DMA:
```c
uint8_t received_data = SPI_ReceiveData_DMA((SPIn *)ADDRESS_SPI_1);
```

### 7. Enable SPI Interrupts
Enable specific SPI interrupts using the following functions:
- **Transmitter Interrupt**:
  ```c
  SPI_TransmitDataInterruptEnable((SPIn *)ADDRESS_SPI_1);
  ```
- **Receiver Interrupt**:
  ```c
  SPI_ReceiverDataInterruptEnable((SPIn *)ADDRESS_SPI_1);
  ```

---

## Functions

### SPI_ConfigGPIOPinForSPI
- **Description**: Configure GPIO pins for SPI communication.
- **Parameters**:
  - `SPIn *spi_n`: The SPI instance (e.g., `SPI1`, `SPI2`, `SPI3`).
- **Steps Performed**:
  1. Enable the clock for the SPI peripheral and its associated GPIO port.
  2. Configure the GPIO pins for NSS, SCK, MISO, and MOSI.
  3. Set the alternate function for the SPI pins.
- **Return Value**: None.

---

### SPI_Configuration
- **Description**: Configure the SPI peripheral with various settings.
- **Parameters**:
  - `SPI_Config_Variables SPI_Val`: A structure containing SPI configuration settings.
- **Steps Performed**:
  1. Configure GPIO pins for SPI communication.
  2. Set the SPI mode (Master or Slave).
  3. Configure the data frame size (8-bit or 16-bit).
  4. Set the clock polarity and phase.
  5. Configure the data frame format (MSB or LSB first).
  6. Set the clock prescaler (only for Master mode).
  7. Configure NSS management (Software or Hardware).
  8. Set the receive mode (Full-duplex or Receive-only).
  9. Enable the SPI peripheral.
- **Return Value**: None.

---

### SPI_SlaveSelect
- **Description**: Select a slave device by driving the NSS pin low.
- **Parameters**:
  - `SPIn *spi_n`: The SPI instance.
- **Return Value**: None.

---

### SPI_SlaveDisSelect
- **Description**: Deselect a slave device by driving the NSS pin high.
- **Parameters**:
  - `SPIn *spi_n`: The SPI instance.
- **Return Value**: None.

---

### SPI_Transmiter
- **Description**: Transmit data using polling.
- **Parameters**:
  - `SPIn *spi_n`: The SPI instance.
  - `uint8_t *pData`: Pointer to the data buffer to be transmitted.
  - `uint8_t Size`: Number of bytes to transmit.
- **Steps Performed**:
  1. Wait for the `TXE` (Transmit Buffer Empty) flag to be set.
  2. Write data to the `DR` register.
  3. Wait for the `BSY` (Busy) flag to reset.
  4. Clear the overrun flag by reading `DR` and `SR`.
- **Return Value**: None.

---

### SPI_Transmiter_DMA
- **Description**: Transmit data using DMA.
- **Parameters**:
  - `SPIn *spi_n`: The SPI instance.
  - `uint8_t *pData`: Pointer to the data buffer to be transmitted.
  - `uint8_t Size`: Number of bytes to transmit.
- **Steps Performed**:
  1. Configure the DMA peripheral:
     - Set the direction to Memory-to-Peripheral.
     - Set the peripheral address to the SPI data register.
     - Set the memory address to the data buffer.
     - Set the number of data items to transmit.
  2. Enable the DMA stream for the SPI peripheral.
  3. Enable the transfer complete interrupt for the DMA stream.
- **Return Value**: None.

---

### SPI_ReceiveData
- **Description**: Receive data using polling.
- **Parameters**:
  - `SPIn *spi_n`: The SPI instance.
  - `uint8_t *pData`: Pointer to the buffer to store received data.
  - `uint8_t Size`: Number of bytes to receive.
- **Steps Performed**:
  1. Wait for the `BSY` (Busy) flag to reset.
  2. Send dummy data to generate the clock signal.
  3. Wait for the `RXNE` (Receive Buffer Not Empty) flag to be set.
  4. Read data from the `DR` register.
- **Return Value**: None.

---


### SPI_ReceiveData_DMA
- **Description**: Receive data via SPI using DMA.
- **Parameters**:
  - `SPIn *spi_n`: The SPI instance (e.g., `SPI1`, `SPI2`, `SPI3`).
- **Steps Performed**:
  1. Determine the SPI instance and set the corresponding DMA peripheral (e.g., `SPI1_RX`, `SPI2_RX`, `SPI3_RX`).
  2. Configure the DMA settings:
     - **Direction**: Set to `Peripheral-to-Memory`.
     - **Peripheral Address**: Set to the SPI data register (`spi_n->DR`).
     - **Memory Address**: Set to the variable `data_receive`.
     - **Data Size**: Configure both memory and peripheral data sizes as `Word`.
     - **Priority Level**: Set to `High`.
     - **Number of Data Items**: Set to `1` (for single-byte reception).
     - **FIFO Mode**: Disable FIFO.
  3. Call `DMA_Configuration` to apply the DMA settings.
  4. Enable the DMA stream using `DMA_EnableStream`.
  5. Enable the DMA transfer complete interrupt using `DMA_TRANSFER_COMPLETE_IRQ_ENABLE`.
  6. Wait for the DMA transfer complete flag (`DMA_TRANSFER_COMPLETE_IRQ_FLAG`) to ensure the data transfer is complete.
  7. Return the received data stored in the `data_receive` variable.
- **Return Value**: The received data (`uint8_t`).

---

### SPI_TransmitDataInterruptEnable
- **Description**: Enable the transmitter interrupt for SPI.
- **Parameters**:
  - `SPIn *spi_n`: The SPI instance.
- **Steps Performed**:
  1. Enable the `TXEIE` (TX Buffer Empty Interrupt Enable) bit in the SPI control register.
- **Return Value**: None.

---

### SPI_ReceiverDataInterruptEnable
- **Description**: Enable the receiver interrupt for SPI.
- **Parameters**:
  - `SPIn *spi_n`: The SPI instance.
- **Steps Performed**:
  1. Enable the `RXNEIE` (RX Buffer Not Empty Interrupt Enable) bit in the SPI control register.
- **Return Value**: None.

---

## Notes
- Ensure that the SPI peripheral clock is enabled before configuring the SPI peripheral.
- Use the appropriate SPI mode (Master or Slave) based on the application requirements.
- Handle SPI interrupts for error and transfer events as needed.
- Use DMA for efficient data transfer in high-speed applications.

---

## Author
- **Name**: Nguyen Dinh Thuan
- **Email**: thuan.nd.167@gmail.com
- **Date**: 2025-03-04