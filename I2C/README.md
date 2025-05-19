# I2C Driver for STM32F4xx

## Overview
This driver provides a set of functions to configure and manage the Inter-Integrated Circuit (I2C) peripheral on STM32F4xx microcontrollers. The I2C peripheral is used for communication between multiple devices over a two-wire interface (SCL and SDA). The driver supports standard mode (100 kHz) and fast mode (400 kHz) communication, as well as DMA-based data transfer for efficient communication. The driver is implemented in `I2C.c` and its corresponding header file `I2C.h`.

---

## Features
- Support for I2C1, I2C2, and I2C3 peripherals.
- Configure GPIO pins for I2C communication (SCL and SDA).
- Support for standard mode (100 kHz) and fast mode (400 kHz).
- Configure clock speed, duty cycle, and rise time.
- Transmit and receive data using polling or DMA.
- Multi-byte data transmission and reception.
- Handle I2C interrupts for error and transfer events.
- DMA-based data transfer for high-speed communication.

---

## File Structure
### 1. `I2C.c`
This file contains the implementation of I2C functions, including:
## File Structure

| **Function**                  | **Description**                                                                 |
|--------------------------------|---------------------------------------------------------------------------------|
| `I2C_ConfigGPIOPin`            | Configure GPIO pins for I2C communication.                                      |
| `I2C_ClockPeripheralConfig`    | Configure the peripheral clock for I2C.                                         |
| `I2C_ConfigI2CClock`           | Configure the I2C clock speed, mode, and duty cycle.                            |
| `I2C_Configuration`            | Configure the I2C peripheral with various settings.                             |
| `I2C_Start`                    | Generate a start condition for I2C communication.                               |
| `I2C_WriteAddress`             | Send the slave address over the I2C bus.                                        |
| `I2C_WriteData`                | Transmit data over the I2C bus.                                                 |
| `I2C_ReadData`                 | Receive data from the I2C bus.                                                  |
| `I2C_ReceiveData`              | Receive multiple bytes of data.                                                 |
| `I2C_TransmitData`             | Transmit multiple bytes of data.                                                |
| `I2C_TransmitData_DMA`         | Transmit data using DMA.                                                        |
| `I2C_ReceiveData_DMA`          | Receive data using DMA.                                                         |
### 2. `I2C.h`
This file contains the declarations of the functions implemented in `I2C.c` and the necessary macros, enums, and data types for I2C configuration.

---

## How to Configure I2C for STM32F4xx

### 1. Include the Header File
Include `I2C.h` in your source file to use the I2C driver:
```c
#include "I2C.h"
```

### 2. Configure I2C Peripheral
Use the `I2C_Configuration` function to configure the I2C peripheral:
```c
I2C_Config_Variables i2c_config = {
    .i2c_x = _I2C1,                     // I2C instance
    .i2c_mode = I2C_STANDARD_MODE,      // I2C mode (Standard mode)
    .peripheral_clock = 16000000,             // Peripheral clock in MHz
    .scl_clock = 100000,                // SCL clock speed in Hz
    .duty_type = I2C_DUTY_2_1           // Duty cycle (2:1)
};
I2C_Configuration(i2c_config);
```
### 3. I2C_TransmitData
- **Description**: Transmit multiple bytes of data to a slave device over the I2C bus.
- **Parameters**:
  - `I2C *i2c_x`: The I2C instance (e.g., `_I2C1`, `_I2C2`, `_I2C3`).
  - `uint8_t slave_address`: The 7-bit address of the slave device.
  - `uint8_t *data`: Pointer to the data buffer to be transmitted.
  - `uint8_t NumOfBytes`: Number of bytes to transmit.
- **Steps Performed**:
  1. Generate a start condition using `I2C_Start`.
  2. Send the slave address with the write bit (`0`) using `I2C_WriteAddress`.
  3. Loop through the data buffer and write each byte to the `DR` register using `I2C_WriteData`.
  4. Optionally, generate a stop condition to end the transmission.
- **Return Value**: None.
- **Example**:
  ```c
  uint8_t data[] = {0x01, 0x02, 0x03};
  I2C_TransmitData(_I2C1, 0x50, data, sizeof(data));
  ```

---

### 4. I2C_ReceiveData
- **Description**: Receive multiple bytes of data from a slave device over the I2C bus.
- **Parameters**:
  - `I2C *i2c_x`: The I2C instance (e.g., `_I2C1`, `_I2C2`, `_I2C3`).
  - `uint8_t slave_address`: The 7-bit address of the slave device.
  - `uint8_t NumOfBytes`: Number of bytes to receive.
- **Steps Performed**:
  1. Generate a start condition using `I2C_Start`.
  2. Send the slave address with the read bit (`1`) using `I2C_WriteAddress`.
  3. For all bytes except the last one:
     - Wait for the `RXNE` bit to indicate data is ready.
     - Read the data from the `DR` register using `I2C_ReadData`.
     - Send an ACK to indicate readiness for the next byte.
  4. For the last byte:
     - Wait for the `RXNE` bit.
     - Read the data from the `DR` register.
     - Send a NACK to indicate no more data is expected.
  5. Optionally, generate a stop condition to end the reception.
- **Return Value**: None (data is stored in the internal buffer).
- **Example**:
  ```c
  uint8_t received_data[3];
  I2C_ReceiveData(_I2C1, 0x50, sizeof(received_data));
  ```

---

### 5. I2C_TransmitData_DMA
- **Description**: Transmit data to a slave device over the I2C bus using DMA.
- **Parameters**:
  - `I2C *i2c_x`: The I2C instance (e.g., `_I2C1`, `_I2C2`, `_I2C3`).
  - `uint8_t slave_address`: The 7-bit address of the slave device.
  - `uint8_t *pData`: Pointer to the data buffer to be transmitted.
  - `uint8_t NumOfBytes`: Number of bytes to transmit.
- **Steps Performed**:
  1. Configure the DMA peripheral:
     - Set the direction to Memory-to-Peripheral.
     - Set the peripheral address to the I2C data register.
     - Set the memory address to the data buffer.
     - Set the number of data items to transmit.
  2. Enable the DMA stream for the I2C peripheral.
  3. Enable the transfer complete interrupt for the DMA stream.
- **Return Value**: None.
- **Example**:
  ```c
  uint8_t data[] = {0x01, 0x02, 0x03};
  I2C_TransmitData_DMA(_I2C1, 0x50, data, sizeof(data));
  ```

---

### 6. I2C_ReceiveData_DMA
- **Description**: Receive data from a slave device over the I2C bus using DMA.
- **Parameters**:
  - `I2C *i2c_x`: The I2C instance (e.g., `_I2C1`, `_I2C2`, `_I2C3`).
- **Steps Performed**:
  1. Configure the DMA peripheral:
     - Set the direction to Peripheral-to-Memory.
     - Set the peripheral address to the I2C data register.
     - Set the memory address to the data buffer.
     - Set the number of data items to receive.
  2. Enable the DMA stream for the I2C peripheral.
  3. Enable the transfer complete interrupt for the DMA stream.
  4. Wait for the transfer complete flag to be set.
- **Return Value**: The received data (`uint32_t`).
- **Example**:
  ```c
  uint32_t received_data = I2C_ReceiveData_DMA(_I2C1);
  ```

---

## Functions

### I2C_ConfigGPIOPin
- **Description**: Configure GPIO pins for I2C communication.
- **Parameters**:
  - `I2C* i2c_x`: The I2C instance (e.g., `_I2C1`, `_I2C2`, `_I2C3`).
- **Steps Performed**:
  1. Enable the clock for the I2C peripheral and its associated GPIO port.
  2. Configure the GPIO pins for alternate function mode.
  3. Set the alternate function for SCL and SDA pins.
- **Return Value**: None.
- **Example**:
  ```c
  I2C_ConfigGPIOPin(_I2C1);
  ```

### I2C_ClockPeripheralConfig
- **Description**: Configure the peripheral clock for I2C.
- **Parameters**:
  - `I2C* i2c_x`: The I2C instance (e.g., `_I2C1`, `_I2C2`, `_I2C3`).
- **Return Value**: None.
- **Example**:
  ```c
  I2C_ClockPeripheralConfig(_I2C1);
  ```

### I2C_ConfigI2CClock
- **Description**: Configure the I2C clock speed, mode, and duty cycle.
- **Parameters**:
  - `I2C* i2c_x`: The I2C instance.
  - `uint8_t i2c_mode`: The I2C mode (e.g., `I2C_STANDARD_MODE`, `I2C_FAST_MODE`).
  - `uint32_t peripheral_clock`: The peripheral clock in MHz.
  - `uint32_t scl_clock`: The SCL clock speed in Hz.
  - `uint8_t duty_type`: The duty cycle (e.g., `I2C_DUTY_2_1`, `I2C_DUTY_16_9`).
- **Return Value**: None.
- **Example**:
  ```c
  I2C_ConfigI2CClock(_I2C1, I2C_STANDARD_MODE, 16000000, 100000, I2C_DUTY_2_1);
  ```

### I2C_Configuration
- **Description**: Configure the I2C peripheral with various settings.
- **Parameters**:
  - `I2C_Config_Variables I2C_Val`: A structure containing I2C configuration settings.
- **Steps Performed**:
  1. Configure GPIO pins for I2C communication.
  2. Reset the I2C peripheral.
  3. Configure the I2C clock speed, mode, and duty cycle.
  4. Enable the I2C peripheral.
- **Return Value**: None.
- **Example**:
  ```c
    void I2C_Configuration(I2C_Config_Variables I2C_Val)
    {
        I2C_ConfigGPIOPin(I2C_Val.i2c_x);
        // Set and reset SWRST bit to clear all configuration of I2C first and re-config.
        SWRST_I2C(I2C_Val.i2c_x);
        SWRST_RESET_I2C(I2C_Val.i2c_x);

        I2C_ConfigI2CClock(I2C_Val.i2c_x, I2C_Val.i2c_mode, I2C_Val.peripheral_clock, I2C_Val.scl_clock, I2C_Val.duty_type); // set clock speed on SCL line include config clock in bus)
        ENABLE_I2C(I2C_Val.i2c_x);
    }
  ```

### I2C_Start
- **Description**: Generate a start condition for I2C communication.
- **Parameters**:
  - `I2C* i2c_x`: The I2C instance.
- **Return Value**: None.
- **Example**:
  ```c
  I2C_Start(_I2C1);
  ```

### I2C_WriteAddress
- **Description**: Send the slave address over the I2C bus.
- **Parameters**:
  - `I2C* i2c_x`: The I2C instance.
  - `uint16_t slave_address`: The slave address.
- **Return Value**: None.
- **Example**:
  ```c
  I2C_WriteAddress(_I2C1, 0x50);
  ```

### I2C_WriteData
- **Description**: Transmit data over the I2C bus.
- **Parameters**:
  - `I2C* i2c_x`: The I2C instance.
  - `uint16_t data`: The data to transmit.
- **Return Value**: None.
- **Example**:
  ```c
  I2C_WriteData(_I2C1, 0x01);
  ```

### I2C_ReadData
- **Description**: Receive data from the I2C bus.
- **Parameters**:
  - `I2C* i2c_x`: The I2C instance.
- **Return Value**: The received data (`uint8_t`).
- **Example**:
  ```c
  uint8_t data = I2C_ReadData(_I2C1);
  ```

---

## Notes
- Ensure that the I2C peripheral clock is enabled before configuring the I2C peripheral.
- Use the appropriate I2C mode (Standard or Fast) based on the application requirements.
- Handle I2C interrupts for error and transfer events as needed.
- Use DMA for efficient data transfer in high-speed applications.

---

## Author
- **Name**: Nguyen Dinh Thuan
- **Email**: thuan.nd.167@gmail.com
- **Date**: 2025-03-07