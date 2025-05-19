# CAN Driver for STM32F4xx

## Overview
This driver provides a set of functions to configure and manage the Controller Area Network (CAN) peripheral on STM32F4xx microcontrollers. The CAN peripheral is used for communication in automotive and industrial applications, supporting message filtering, multiple communication modes, and error handling. The driver is implemented in `CAN.c` and its corresponding header file `CAN.h`.

---

## Features
- Support for CAN1 and CAN2 peripherals.
- Configure CAN communication modes (Normal, Loopback, Silent, Silent Loopback).
- Set CAN bit timing parameters (Prescaler, Time Segments, Synchronization Jump Width).
- Enable and configure CAN filters for message filtering.
- Transmit and receive CAN messages.
- Handle CAN interrupts for error and message events.
- Configure GPIO pins for CAN_TX and CAN_RX.

---

## File Structure
### 1. `CAN.c`
This file contains the implementation of CAN functions, including:
## File Structure

| **Function**                  | **Description**                                                                 |
|--------------------------------|---------------------------------------------------------------------------------|
| `CAN_Configuration`            | Configure the CAN peripheral with various settings.                             |
| `CAN_ConfigGPIOPin`            | Configure GPIO pins for CAN_TX and CAN_RX.                                      |
| `CAN_BaudrateConfig`           | Configure the CAN baud rate.                                                    |
| `CAN_MessageFilterConfig`      | Configure CAN filters for message filtering.                                    |
| `CAN_MailboxTransmitConfig`    | Configure CAN transmit mailbox.                                                 |
| `CAN_Transmit_Data`            | Transmit a single byte of data.                                                 |
| `CAN_Receive_Data`             | Receive a single byte of data.                                                  |
| `CAN_EnableTransmitInterrupt`  | Enable CAN transmit interrupt.                                                  |
| `CAN_EnableReceiveInterrupt`   | Enable CAN receive interrupt.                                                   |

### 2. `CAN.h`
This file contains the declarations of the functions implemented in `CAN.c` and the necessary macros, enums, and data types for CAN configuration.

---

## How to Configure CAN for STM32F4xx

### 1. Include the Header File
Include `CAN.h` in your source file to use the CAN driver:
```c
#include "CAN.h"
```

### 2. Configure CAN Peripheral
Use the `CAN_Configuration` function to configure the CAN peripheral:
```c
CAN_Config_Variables can_config = {
    .CAN_n = CAN1,                     // CAN instance
    .Baudrate = CAN_BAUDRATE_500KB,    // CAN baud rate
    .Mailbox = 0,                      // Mailbox number
    .TX_ID = 0x123,                    // Transmit ID
    .TX_DataLength = 8,                // Transmit data length
    .FilterNumber = 0,      // Filter number
    .FilterMode = CAN_FILTER_IDENTIFIER_MASK_MODE, // Filter mode
    .ScaleMode = CAN_FILTER_SCALE_SINGLE_32,       // Filter scale
    .RX_ID = 0x123,                    // Receive ID
    .ExtraInfor = 0xFFF                // Extra information for filtering
};
CAN_Configuration(can_config);
```

### 3. Transmit a CAN Message
Use the `CAN_Transmit_Data` function to send a single byte of data:
```c
CAN_Transmit_Data(CAN1, 0, 0x55); // Transmit data 0x55 using mailbox 0
```

### 4. Receive a CAN Message
Use the `CAN_Receive_Data` function to receive a single byte of data:
```c
uint8_t received_data = CAN_Receive_Data(CAN1, 0, MESSAGE_FIFO0);
```

### 5. Enable CAN Interrupts
Use the `CAN_EnableTransmitInterrupt` and `CAN_EnableReceiveInterrupt` functions to enable CAN interrupts:
```c
CAN_EnableTransmitInterrupt(CAN1); // Enable transmit interrupt
CAN_EnableReceiveInterrupt(CAN1, MESSAGE_FIFO0); // Enable receive interrupt for FIFO0
```

---

## Functions

### CAN_Configuration
- **Description**: Configure the CAN peripheral with various settings.
- **Parameters**:
  - `CAN_Config_Variables CAN_Val`: A structure containing CAN configuration settings.
- **Steps Performed**:
  1. Configure GPIO pins for CAN_TX and CAN_RX.
  2. Enter CAN initialization mode and wait for acknowledgment.
  3. Exit sleep mode.
  4. Configure the CAN baud rate.
  5. Configure the transmit mailbox.
  6. Configure the filter for receiving messages.
  7. Exit CAN initialization mode.
- **Return Value**: None.
- **Example**:
  ```c
    void CAN_Configuration(CAN_Config_Variables CAN_Val)
    {
        // Config GPIO for CANx
        CAN_ConfigGPIOPin(CAN_Val.CAN_n);

        // Enter CAN Initialize mode and wait for ACK
        CAN_REQUEST_INITIALIZED_MODE(CAN_Val.CAN_n);
        while(!CAN_GET_INITIALIZED_MODE(CAN_Val.CAN_n));

        //Exit Sleepmode
        CAN_EXIT_SLEEP_MODE(CAN_Val.CAN_n);
        while(CAN_GET_SLEEP_MODE(CAN_Val.CAN_n));

        // Config baudrate for CANx
    #if !defined(CAN_SELF_CONFIG_BAUDRATE)
        CAN_BaudrateConfig(CAN_Val.CAN_n, CAN_Val.Baudrate);
    #else
        CAN_BaudrateConfig(CAN_Val.CAN_n, CAN_Val.Prescaler, CAN_Val.TimeSegment1, CAN_Val.TimeSegment2, CAN_Val.SJW);
    #endif
        // Config Transmit mailbox
        CAN_MailboxTransmitConfig(CAN_Val.CAN_n, CAN_Val.Mailbox, CAN_Val.TX_ID, CAN_Val.TX_DataLength);

        // Config Filter message data receive
        CAN_MessageFilterConfig(CAN_Val.CAN_n, CAN_Val.FilterNumber, CAN_Val.FilterMode, CAN_Val.ScaleMode, CAN_Val.RX_ID, CAN_Val.ExtraInfor);

        // Exit Initialize mode
        CAN_EXIT_INITIALIZED_MODE(CAN_Val.CAN_n);
        while(CAN_GET_INITIALIZED_MODE(CAN_Val.CAN_n));

    }
  ```

### CAN_ConfigGPIOPin
- **Description**: Configure GPIO pins for CAN_TX and CAN_RX.
- **Parameters**:
  - `CANx* CAN_x`: The CAN instance (e.g., `CAN1`, `CAN2`).
- **Steps Performed**:
  1. Enable the clock for the CAN peripheral and its associated GPIO port.
  2. Configure the GPIO pins for alternate function mode.
  3. Set the alternate function for CAN_TX and CAN_RX.
- **Return Value**: None.
- **Example**:
  ```c
  CAN_ConfigGPIOPin(CAN1); // Configure GPIO pins for CAN1
  ```

### CAN_BaudrateConfig
- **Description**: Configure the CAN baud rate.
- **Parameters**:
  - `CANx* CAN_x`: The CAN instance (e.g., `CAN1`, `CAN2`).
  - `uint32_t BaudRate`: The desired baud rate (e.g., `CAN_BAUDRATE_500KB`).
- **Return Value**: None.
- **Example**:
  ```c
  CAN_BaudrateConfig(CAN1, CAN_BAUDRATE_500KB); // Set CAN1 baud rate to 500 kbps
  ```

### CAN_MessageFilterConfig
- **Description**: Configure CAN filters for message filtering.
- **Parameters**:
  - `CANx* CAN_x`: The CAN instance (e.g., `CAN1`, `CAN2`).
  - `uint8_t FilterNumber`: The filter number (e.g., `0`).
  - `uint8_t FilterMode`: The filter mode (e.g., `CAN_FILTER_IDENTIFIER_MASK_MODE`).
  - `uint8_t Scale`: The filter scale (e.g., `CAN_FILTER_SCALE_SINGLE_32`).
  - `uint32_t ID`: The filter ID.
  - `uint32_t ExtraInfor`: Additional filter information.
- **Return Value**: None.
- **Example**:
  ```c
  CAN_MessageFilterConfig(CAN1, 0, CAN_FILTER_IDENTIFIER_MASK_MODE, CAN_FILTER_SCALE_SINGLE_32, 0x123, 0xFFF);
  ```

### CAN_MailboxTransmitConfig
- **Description**: Configure the CAN transmit mailbox.
- **Parameters**:
  - `CANx* CAN_x`: The CAN instance (e.g., `CAN1`, `CAN2`).
  - `uint8_t Mailbox`: The mailbox number (e.g., `0`).
  - `uint32_t ID`: The transmit ID.
  - `uint8_t DataLength`: The data length (e.g., `8`).
- **Return Value**: None.
- **Example**:
  ```c
  CAN_MailboxTransmitConfig(CAN1, 0, 0x123, 8); // Configure mailbox 0 for CAN1
  ```

### CAN_Transmit_Data
- **Description**: Transmit a single byte of data.
- **Parameters**:
  - `CANx* CAN_x`: The CAN instance (e.g., `CAN1`, `CAN2`).
  - `uint8_t Mailbox`: The mailbox number (e.g., `0`).
  - `uint8_t Data`: The data to transmit.
- **Return Value**: None.
- **Example**:
  ```c
  CAN_Transmit_Data(CAN1, 0, 0x55); // Transmit data 0x55 using mailbox 0
  ```

### CAN_Receive_Data
- **Description**: Receive a single byte of data.
- **Parameters**:
  - `CANx* CAN_x`: The CAN instance (e.g., `CAN1`, `CAN2`).
  - `uint8_t Mailbox`: The mailbox number (e.g., `0`).
  - `uint8_t FIFOx`: The FIFO to receive the message from (e.g., `MESSAGE_FIFO0`).
- **Return Value**: The received data (`uint8_t`).
- **Example**:
  ```c
  uint8_t received_data = CAN_Receive_Data(CAN1, 0, MESSAGE_FIFO0);
  ```

---

## Notes
- Ensure that the CAN peripheral clock is enabled before configuring the CAN peripheral.
- Configure the CAN filters to allow only the desired messages to pass through.
- Use the appropriate CAN mode based on the application requirements (e.g., Normal, Loopback, Silent).
- Handle CAN interrupts for error and message events as needed.

---

## Author
- **Name**: Nguyen Dinh Thuan
- **Email**: thuan.nd.167@gmail.com
- **Date**: 2025-04-29