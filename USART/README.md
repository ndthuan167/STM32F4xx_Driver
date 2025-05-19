# USART Driver for STM32F4xx

## Overview
This driver provides a set of functions to configure and manage the Universal Synchronous/Asynchronous Receiver Transmitter (USART) peripheral on STM32F4xx microcontrollers. The USART peripheral is used for serial communication between devices, supporting both synchronous and asynchronous modes. The driver supports baud rate configuration, data transmission, and reception using polling, DMA, and interrupts. The driver is implemented in `USART.c` and its corresponding header file `USART.h`.

---

## Features
- Support for USART1, USART2, USART3, USART6, UART4, and UART5 peripherals.
- Configure GPIO pins for USART communication (TX and RX).
- Support for various baud rates (e.g., 9600, 19200, 115200).
- Configure word length, parity control, and oversampling mode.
- Transmit and receive data using polling, DMA, or interrupts.
- Enable and handle USART interrupts for transmission and reception.
- DMA-based data transfer for efficient communication.

---

## File Structure
### 1. `USART.c`
This file contains the implementation of USART functions, including:
## USART Functions

| **Function**                     | **Description**                                                                 |
|-----------------------------------|---------------------------------------------------------------------------------|
| `USART_BaudrateCalculator`        | Calculate the baud rate value for USART.                                        |
| `USART_Configuration`             | Configure the USART peripheral with various settings.                           |
| `USART_SendData`                  | Transmit data using polling.                                                   |
| `USART_SendData_DMA`              | Transmit data using DMA.                                                       |
| `USART_ReceiveData`               | Receive data using polling.                                                    |
| `USART_ReceiveData_DMA`           | Receive data using DMA.                                                        |
| `USART_ReceiverDataInterruptEnable` | Enable the receiver interrupt.                                                |
| `USART_TransmiterDataInterruptEnable` | Enable the transmitter interrupt.                                            |

### 2. `USART.h`
This file contains the declarations of the functions implemented in `USART.c` and the necessary macros, enums, and data types for USART configuration.

---

## How to Configure USART for STM32F4xx

### 1. Include the Header File
Include `USART.h` in your source file to use the USART driver:
```c
#include "USART.h"
```

### 2. Configure USART Peripheral
Use the `USART_Configuration` function to configure the USART peripheral:
```c
USART_Config_Variables usart_config = {
    .usart_x = (USARTn *)ADDRESS_USART_1, // USART instance
    .baudrate = BAUDRATE_115200,          // Baud rate
    .wordlength = DATA_BITS_8,            // Word length (8 bits)
    .over8 = OVERSAMPLING_BY_16,          // Oversampling mode
    .paritycontrol = PARITY_DISABLE,      // Parity control
    .parity = PARITY_EVEN                 // Parity type (if enabled)
};
USART_Configuration(usart_config);
```

### 3. Transmit Data
Use the `USART_SendData` function to send data over the USART:
```c
uint8_t data[] = "Hello, USART!";
USART_SendData((USARTn *)ADDRESS_USART_1, data, sizeof(data));
```

### 4. Receive Data
Use the `USART_ReceiveData` function to receive data over the USART:
```c
uint8_t received_data = USART_ReceiveData((USARTn *)ADDRESS_USART_1);
```

### 5. Transmit Data Using DMA
Use the `USART_SendData_DMA` function to send data using DMA:
```c
uint8_t data[] = "Hello, DMA!";
USART_SendData_DMA((USARTn *)ADDRESS_USART_1, data, sizeof(data));
```

### 6. Receive Data Using DMA
Use the `USART_ReceiveData_DMA` function to receive data using DMA:
```c
uint8_t received_data = USART_ReceiveData_DMA((USARTn *)ADDRESS_USART_1);
```

### 7. Enable USART Interrupts
Enable specific USART interrupts using the following functions:
- **Receiver Interrupt**:
  ```c
  USART_ReceiverDataInterruptEnable((USARTn *)ADDRESS_USART_1);
  ```
- **Transmitter Interrupt**:
  ```c
  USART_TransmiterDataInterruptEnable((USARTn *)ADDRESS_USART_1);
  ```

---

## Functions

### USART_BaudrateCalculator
- **Description**: Calculate the baud rate value for USART based on the desired baud rate, clock frequency, and oversampling mode.

#### **Formula**
The baud rate value is calculated using the following formula:

For **Oversampling by 16**:
```math
USARTDIV = Fclk / (16 * Baudrate)
```

For **Oversampling by 8**:
```math
USARTDIV = Fclk / (8 * Baudrate)
```

Where:
- `USARTDIV`: The calculated baud rate value.
- `Fclk`: The clock frequency in Hz (e.g., 16 MHz).
- `Baudrate`: The desired baud rate (e.g., 9600, 115200).

#### **Parameters**
| **Parameter**       | **Type**      | **Description**                                                                 |
|---------------------|---------------|---------------------------------------------------------------------------------|
| `uint32_t baudrate` | `uint32_t`    | Desired baud rate (e.g., 9600, 115200).                                         |
| `float clockfrequency` | `float`   | Clock frequency in Hz (e.g., 16000000 for 16 MHz).                              |
| `uint8_t over8`     | `uint8_t`     | Oversampling mode (`OVERSAMPLING_BY_16` or `OVERSAMPLING_BY_8`).                |

#### **Return Value**
- The calculated baud rate value (`uint16_t`).

#### **Example**
```c
uint16_t baudrate_value = USART_BaudrateCalculator(9600, 16000000, OVERSAMPLING_BY_16);
```

#### **Notes**
1. Ensure that the clock frequency (`Fclk`) is configured correctly for the USART peripheral.
2. Use the appropriate oversampling mode (`OVERSAMPLING_BY_16` or `OVERSAMPLING_BY_8`) based on the application requirements.
3. The calculated `USARTDIV` value is used to configure the USART's baud rate register.
---

### USART_Configuration
- **Description**: Configure the USART peripheral with various settings, including baud rate, word length, parity control, oversampling mode, and enabling the transmitter and receiver.

---

#### **Parameters**
| **Parameter**                     | **Type**                  | **Description**                                                                 |
|-----------------------------------|---------------------------|---------------------------------------------------------------------------------|
| `USART_Config_Variables USART_Val`| `struct`                 | A structure containing USART configuration settings.                            |

---

#### **Steps Performed**
1. **Enable USART Clock**:
   - Enable the clock for the USART peripheral and its associated GPIO port.

2. **Configure GPIO Pins**:
   - Configure the GPIO pins for TX and RX in alternate function mode.

3. **Set Baud Rate**:
   - Use the `USART_BaudrateCalculator` function to calculate and set the baud rate.

4. **Configure Word Length and Parity**:
   - Set the word length (e.g., 8 bits or 9 bits).
   - Enable or disable parity control and configure the parity type (e.g., even or odd).

5. **Set Oversampling Mode**:
   - Configure the oversampling mode (e.g., `OVERSAMPLING_BY_16` or `OVERSAMPLING_BY_8`).

6. **Enable USART Peripheral**:
   - Enable the USART peripheral by setting the `UE` (USART Enable) bit in the `CR1` register.

7. **Enable Transmitter and Receiver**:
   - Enable the transmitter (`TE` bit) and receiver (`RE` bit) in the `CR1` register.

#### **Code Implementation**
Below is an example implementation of the `USART_Configuration` function:

```c
void USART_Configuration(USART_Config_Variables USART_Val)
{
    if (USART_Val.usart_x == (USARTn *)ADDRESS_USART_1)
    {
        RCC_EnablePeripheralClock(CLOCK_USART1);
        RCC_EnablePeripheralClock(CLOCK_GPIO_A);
        GPIO_Configuration(gpio_a, GPIO_PIN9, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_Configuration(gpio_a, GPIO_PIN10, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_ConfigAlternateFunc(gpio_a, GPIO_PIN9, AF7);
        GPIO_ConfigAlternateFunc(gpio_a, GPIO_PIN10, AF7);
    }
    else if (USART_Val.usart_x == (USARTn *)ADDRESS_USART_2)
    {
        RCC_EnablePeripheralClock(CLOCK_USART2);
        RCC_EnablePeripheralClock(CLOCK_GPIO_D);
        GPIO_Configuration(gpio_d, GPIO_PIN5, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_Configuration(gpio_d, GPIO_PIN6, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_ConfigAlternateFunc(gpio_d, GPIO_PIN5, AF7);
        GPIO_ConfigAlternateFunc(gpio_d, GPIO_PIN6, AF7);
    }
    else if (USART_Val.usart_x == (USARTn *)ADDRESS_USART_3)
    {
        RCC_EnablePeripheralClock(CLOCK_USART3);
        RCC_EnablePeripheralClock(CLOCK_GPIO_D);
        GPIO_Configuration(gpio_d, GPIO_PIN8, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_Configuration(gpio_d, GPIO_PIN9, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_ConfigAlternateFunc(gpio_d, GPIO_PIN8, AF7);
        GPIO_ConfigAlternateFunc(gpio_d, GPIO_PIN9, AF7);
    }
    else if (USART_Val.usart_x == (USARTn *)ADDRESS_USART_6)
    {
        RCC_EnablePeripheralClock(CLOCK_USART6);
        RCC_EnablePeripheralClock(CLOCK_GPIO_C);
        GPIO_Configuration(gpio_c, GPIO_PIN6, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_Configuration(gpio_c, GPIO_PIN7, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_ConfigAlternateFunc(gpio_c, GPIO_PIN6, AF8);
        GPIO_ConfigAlternateFunc(gpio_c, GPIO_PIN7, AF8);
    }
    else if (USART_Val.usart_x == (USARTn *)ADDRESS_UART_4)
    {
        RCC_EnablePeripheralClock(CLOCK_UART4);
        RCC_EnablePeripheralClock(CLOCK_GPIO_A);
        GPIO_Configuration(gpio_a, GPIO_PIN0, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_Configuration(gpio_a, GPIO_PIN1, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_ConfigAlternateFunc(gpio_a, GPIO_PIN0, AF8);
        GPIO_ConfigAlternateFunc(gpio_a, GPIO_PIN1, AF8);
    }
    else if (USART_Val.usart_x == (USARTn *)ADDRESS_UART_5)
    {
        RCC_EnablePeripheralClock(CLOCK_UART5);
        RCC_EnablePeripheralClock(CLOCK_GPIO_C);
        RCC_EnablePeripheralClock(CLOCK_GPIO_D);
        GPIO_Configuration(gpio_c, GPIO_PIN12, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_Configuration(gpio_d, GPIO_PIN2, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_ConfigAlternateFunc(gpio_c, GPIO_PIN12, AF8);
        GPIO_ConfigAlternateFunc(gpio_d, GPIO_PIN2, AF8);
    }

    USART_SET_OVERSAMPLING_MODE(USART_Val.usart_x, USART_Val.over8);
    uint16_t baudrate_cal = USART_BaudrateCalculator(USART_Val.baudrate, 16000000, USART_Val.over8);
    USART_SET_BAUDRATE(USART_Val.usart_x, baudrate_cal);
    USART_SET_STOP_BIT(USART_Val.usart_x, STOP_BIT_1);
    USART_TRANSMITER_ENABLE(USART_Val.usart_x);
    USART_RECEIVER_ENABLE(USART_Val.usart_x);
	USART_ENABLE_USART(USART_Val.usart_x);
    
}
```
---

### USART_SendData
- **Description**: Transmit data using polling.
- **Parameters**:
  - `USARTn *usartn`: The USART instance.
  - `uint8_t *pData`: Pointer to the data buffer to be transmitted.
  - `uint16_t Size`: Number of bytes to transmit.
- **Steps Performed**:
  1. Check the `TXE` (Transmit Data Register Empty) bit in the status register.
  2. Write data to the `DR` register.
  3. Wait for the transmission to complete.
- **Return Value**: None.

---

### USART_SendData_DMA
- **Description**: Transmit data using DMA.
- **Parameters**:
  - `USARTn *usart_n`: The USART instance.
  - `uint8_t *pData`: Pointer to the data buffer to be transmitted.
  - `uint16_t Size`: Number of bytes to transmit.
- **Steps Performed**:
  1. Configure the DMA peripheral:
     - Set the direction to Memory-to-Peripheral.
     - Set the peripheral address to the USART data register.
     - Set the memory address to the data buffer.
     - Set the number of data items to transmit.
  2. Enable the DMA stream for the USART peripheral.
  3. Enable the transfer complete interrupt for the DMA stream.
- **Return Value**: None.

---

### USART_ReceiveData
- **Description**: Receive data using polling.
- **Parameters**:
  - `USARTn *usartn`: The USART instance.
- **Steps Performed**:
  1. Check the `RXNE` (Receive Data Register Not Empty) bit in the status register.
  2. Read data from the `DR` register.
- **Return Value**: The received data (`uint8_t`).

---

### USART_ReceiveData_DMA
- **Description**: Receive data using DMA.
- **Parameters**:
  - `USARTn *usartn`: The USART instance.
- **Steps Performed**:
  1. Configure the DMA peripheral:
     - Set the direction to Peripheral-to-Memory.
     - Set the peripheral address to the USART data register.
     - Set the memory address to the data buffer.
     - Set the number of data items to receive.
  2. Enable the DMA stream for the USART peripheral.
  3. Enable the transfer complete interrupt for the DMA stream.
  4. Wait for the transfer complete flag to be set.
- **Return Value**: The received data (`uint8_t`).

---

### USART_ReceiverDataInterruptEnable
- **Description**: Enable the receiver interrupt for the USART.
- **Parameters**:
  - `USARTn *usartn`: The USART instance.
- **Steps Performed**:
  1. Enable the `RXNEIE` (RX Not Empty Interrupt Enable) bit in the `CR1` register.
- **Return Value**: None.

---

### USART_TransmiterDataInterruptEnable
- **Description**: Enable the transmitter interrupt for the USART.
- **Parameters**:
  - `USARTn *usartn`: The USART instance.
- **Steps Performed**:
  1. Enable the `TXEIE` (TX Empty Interrupt Enable) bit in the `CR1` register.
- **Return Value**: None.

---

## Notes
- Ensure that the USART peripheral clock is enabled before configuring the USART peripheral.
- Use the appropriate baud rate and word length based on the application requirements.
- Handle USART interrupts for error and transfer events as needed.
- Use DMA for efficient data transfer in high-speed applications.

---

## Author
- **Name**: Nguyen Dinh Thuan
- **Email**: thuan.nd.167@gmail.com
- **Date**: 2024-09-11