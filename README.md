# STM32F4xx Driver

## Overview
The `STM32F4xx_Driver` project provides a collection of low-level drivers for the STM32F4xx microcontroller series. These drivers are designed to simplify the configuration and usage of various peripherals, including GPIO, USART, Timer, RCC, SysTick, DMA, and more. The project is modular, with each peripheral having its own dedicated driver files and documentation.

---

## Features

- **GPIO Driver**:
  - Configure GPIO pins as input, output, alternate function, or analog mode.
  - Support for pull-up, pull-down, and open-drain configurations.
  - Enable GPIO interrupts for external events.
  - Configure GPIO speed (low, medium, high, very high).
  - Support for toggling GPIO pins and reading pin states.

- **USART Driver**:
  - Configure USART for communication with various baud rates, word lengths, and parity settings.
  - Support for data transmission and reception using polling, interrupts, and DMA.
  - Enable transmitter and receiver interrupts.
  - Support for hardware flow control (RTS/CTS).
  - Configure oversampling modes (16x or 8x).

- **Timer Driver**:
  - Configure timers for periodic events, input capture, and output compare.
  - Generate periodic flags for time intervals (1ms, 10ms, etc.).
  - Support for PWM signal generation.
  - Configure timer prescaler and auto-reload values.
  - Enable timer interrupts for periodic tasks.

- **RCC (Reset and Clock Control) Driver**:
  - Configure system clock sources (HSI, HSE, PLL).
  - Enable and disable peripheral clocks for AHB1, APB1, and APB2 buses.
  - Configure MCU output clock (MCO1, MCO2).
  - Support for configuring PLL parameters (PLLM, PLLN, PLLP, PLLQ).
  - Enable CSS (Clock Security System) and HSE bypass.

- **SysTick Driver**:
  - Configure the SysTick timer for periodic interrupts.
  - Generate periodic flags for time intervals (1ms, 10ms, etc.).
  - Support for system tick-based delay functions.
  - Enable SysTick interrupts for real-time tasks.

- **DMA Driver**:
  - Configure DMA for memory-to-memory, peripheral-to-memory, and memory-to-peripheral transfers.
  - Enable DMA interrupts for transfer complete and error events.
  - Support for high-speed data transfer with minimal CPU intervention.
  - Configure DMA priority levels and circular/normal modes.

- **NVIC Driver**:
  - Configure interrupt priorities and enable/disable specific interrupts.
  - Support for up to 240 IRQ numbers.
  - Manage pending and active interrupt flags.
  - Enable and configure nested interrupt handling.

- **EXTI Driver**:
  - Configure GPIO pins as external interrupt sources.
  - Support for rising edge, falling edge, or both edge triggers.
  - Clear pending interrupt flags and handle EXTI interrupts.
  - Enable EXTI interrupts for specific lines.

- **I2C Driver**:
  - Configure I2C for master and slave modes.
  - Support for standard mode (100 kHz) and fast mode (400 kHz).
  - Enable I2C interrupts for event and error handling.
  - Support for multi-byte data transmission and reception.

- **CAN Driver**:
  - Configure CAN for communication in standard and extended ID modes.
  - Support for message filtering and FIFO management.
  - Enable CAN interrupts for transmit, receive, and error events.
  - Support for configuring CAN bit timing parameters.

- **SPI Driver**:
  - Configure SPI for master and slave modes.
  - Support for full-duplex and half-duplex communication.
  - Enable SPI interrupts for data transmission and reception.
  - Configure SPI clock polarity, phase, and data frame format.

- **ADC Driver**:
  - Configure ADC for single and continuous conversion modes.
  - Support for multi-channel ADC conversions.
  - Enable ADC interrupts for end-of-conversion events.
  - Configure ADC sampling time and resolution.


---

## How to Use
1. **Include the Required Header Files**:
   - Include the header file for the peripheral you want to use (e.g., `GPIO.h`, `USART.h`).

2. **Configure the Peripheral**:
   - Use the provided configuration functions to initialize and configure the peripheral.

3. **Use the Peripheral**:
   - Call the appropriate functions to perform operations (e.g., send/receive data, toggle GPIO pins, etc.).

4. **Refer to Documentation**:
   - Each driver folder contains a `README.md` file with detailed descriptions, usage examples, and notes.

## Relationships Between Folders and Core Files

### **1. Main Application (`main.c`)**
- The `main.c` file serves as the entry point for the application. It initializes the system, configures peripherals, and implements the main application logic.
- **Usage**:
  - Include the necessary driver header files (e.g., `GPIO.h`, `USART.h`, `Timer.h`) to configure and use peripherals.
  - Call initialization functions (e.g., `RCC_SettingSystemClock72MHz()`, `USART_Configuration()`) to set up the system and peripherals.
  - Use the driver APIs to perform operations like sending/receiving data, toggling GPIO pins, or generating PWM signals.
- **Example**:
```c
#include "Thuan_STM32F4xx_Driver.h"

int main()
{
    testvalue1 = 0;

    // Config Clock
	RCC_SettingSystemClock16MHz();

    // Enable Clock for System Config
	RCC_EnablePeripheralClock(CLOCK_SYSCFG);

	// Systick configuration
	SettingSystemTimer(PROCESSOR_CLKSRC, ENABLE, SYSTICK_TIMER_1MS);

	// Config PA1 is input pull down
	GPIO_Configuration(GPIO_A, GPIO_PIN0, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
	GPIO_Configuration(GPIO_A, GPIO_PIN1, MODER_INPUT, OTYPER_PUSHPULL, OSPEEDR_LOW, PUPDR_PULLUP);

	EXTI_Config_Variables EXTI1_Config;
	EXTI1_Config.EXTI_port = EXTIx_PA_PIN;
	EXTI1_Config.EXTI_line = EXTI_LINE_1;
	EXTI1_Config.trigger_type = RISING_TRIGGER;
	EXTI1_Config.mask_event = NOT_MASKED;
	EXTI1_Config.mask_it = NOT_MASKED;

    // Config EXTI line 1
	EXTI_Configuration(EXTI1_Config);

	NVIC_Config_Variables NVIC_Config1;
	NVIC_Config1.IRQNumber = _EXTI1_IRQHandler;
	NVIC_Config1.IRQPriority = 0x05;
	NVIC_Config1.IRQEnable = ENABLE;

	// NVIC configuration for EXTI1
	NVIC_Configuration(NVIC_Config1);

	// setup timer3
	Timer_Configuration(TIMER3, TIMER_1MS);

    // Config USART2
	USART_Config_Variables USART2_Config;
	USART2_Config.usart_x = USART2;
	USART2_Config.baudrate = BAUDRATE_9600;
	USART2_Config.wordlength = DATA_BITS_8;
	USART2_Config.over8 = OVERSAMPLING_BY_16;
	USART2_Config.paritycontrol = PARITY_DISABLE;
	USART2_Config.paritytype = EVEN_PARITY;

	USART_Configuration(USART2_Config);
	USART_ReceiverDataInterruptEnable(USART2);

	// Config SPI1
	SPI_Config_Variables SPI1_Config;
	SPI1_Config.spi_x = SPI1;
	SPI1_Config.spi_mode = MASTER_MODE;
	SPI1_Config.sampling_type = FIRST_CLOCK_NO_IDLE;
	SPI1_Config.clock_prescaler = BAUD_RATE_DIV_2;
	SPI1_Config.data_read_fr = LSB_FIRST;
	SPI1_Config.receive_mode = FULL_DUPLEX_MODE;
	SPI1_Config.data_fr = DATA_BITS_8;
	SPI1_Config.slave_mode_type = SOFTWARE_SLAVE_SELECT;

	SPI_Configuration(SPI1_Config);

    // Config ADC
	uint8_t ADC_Channels[7] = {ADC_CH0, ADC_CH4, ADC_CH5, ADC_CH6, ADC_CH7, ADC_CH8, ADC_CH9};

	ADC_Variables ADC1_val;
	ADC1_val.ADC_n = ADC1;
	ADC1_val.prescaler_div = ADC_CLK_DIV_2;
	ADC1_val.resolution = ADC_RESOLUTION_12BIT;
	ADC1_val.eoc_type = EOC_END_OF_CONVERSION;
	ADC1_val.dma_stop_type = DMA_CONTINUE_AFTER_LAST_CONVERSION;
	ADC1_val.data_align = DATA_RIGHT_ALIGNMENT;
	ADC1_val.sequence_length = 7;
	ADC1_val.channels = &ADC_Channels[0];
	ADC1_val.sampling_time = ADC_SPLT_3_CYCLES;
	ADC_Configuration(ADC1_val);

	while (1)
	{
		LoopTimerSetting();		   // Timer loop
		LoopSystickTimerSetting(); // Systick timer loop

	    if(GetFlagTimer1ms())
	    {
	    	testvalue1++;

	    	if(testvalue1 % 2)
	    	{
	    		GPIO_SettingOutputDataBSRR(GPIO_B, GPIO_PIN6, CLEAR);
	    		GPIO_SettingOutputDataBSRR(GPIO_B, GPIO_PIN7, SET);
	    	}
	    	else
	    	{
	    		GPIO_SettingOutputDataBSRR(GPIO_B, GPIO_PIN6, SET);
	    		GPIO_SettingOutputDataBSRR(GPIO_B, GPIO_PIN7, CLEAR);
	    	}
	    }
	}
}

```

---

### **2. Interrupt Handlers (`IRQ_Handler.c`)**
- The `IRQ_Handler.c` file contains the interrupt service routines (ISRs) for handling peripheral interrupts.
- **Integration**:
  - Each driver folder provides functions to enable and configure interrupts (e.g., `USART_ReceiverDataInterruptEnable`, `EXTI_EnableInterrupt`).
  - The corresponding ISRs in `IRQ_Handler.c` call the appropriate driver functions to handle events (e.g., data reception, external interrupts).
- **Example**:
  ```c
    void USART2_IRQHandler(void)
    {
        USARTn *usart2 = (USARTn*)ADDRESS_USART_2;

        if (USART_GET_READDATA_STATUS(usart2))
        {
            value_re_IT = USART_GET_DATA_VALUE(usart2);		// data recevied
        }

        if(USART_GET_WRITEDATA_STATUS(usart2))
        {
            USART_SendData(usart2, &value_re_IT, 1);	// send data received to terminal
            USART_CLEAR_WRITEDATA_FLAG(usart2);
        }
    }

  ```

---

### **3. Linker Script (`STM32F4xx_linker_script.ld`)**
- The linker script defines the memory layout of the microcontroller, including flash, RAM, and peripheral memory regions.
- **Integration**:
  - The driver files rely on the memory regions defined in the linker script to access peripheral registers.
  - Ensure that the memory-mapped addresses for peripherals (e.g., `USART1`, `GPIOA`) match the definitions in the linker script.
- **Key Sections**:
  - **Flash Memory**: Defines the program storage area.
  - **RAM**: Defines the data and stack memory regions.
  - **Vector Table**: Maps interrupt vectors to their corresponding ISRs.

---

### **4. Startup Code (`STM32F4xx_Startup.c`)**
- The startup code initializes the microcontroller, sets up the stack, and calls the `main` function.
- **Integration**:
  - The startup code defines the vector table, which maps interrupt vectors to their corresponding ISRs in `IRQ_Handler.c`.
  - It initializes the `.data` and `.bss` sections and sets up the system clock.
- **Key Responsibilities**:
  - **Reset Handler**: Initializes the system and calls `main`.
  - **Vector Table**: Maps interrupts (e.g., `USART1_IRQHandler`, `EXTI0_IRQHandler`) to their respective handlers.
  - **Default Handlers**: Provides default implementations for unused interrupts.

---

### **5. Driver Folders**
Each driver folder provides modular functionality for a specific peripheral. These folders interact with the core files as follows:
| **Folder**       | **Core File Interaction**                                                                 |
|-------------------|-------------------------------------------------------------------------------------------|
| `CAN`            | Used in `main.c` for CAN communication. Interrupts are handled in `IRQ_Handler.c`.        |
| `DMA`            | Configured in `main.c` for high-speed data transfer. Interrupts are handled in `IRQ_Handler.c`. |
| `EXTI`           | Configured in `main.c` for external interrupts. Handlers are defined in `IRQ_Handler.c`.  |
| `GPIO`           | Used in `main.c` to configure and control GPIO pins.                                      |
| `I2C`            | Configured in `main.c` for I2C communication. Interrupts are handled in `IRQ_Handler.c`.  |
| `NVIC`           | Configured in `main.c` to set interrupt priorities and enable/disable interrupts.         |
| `RCC`            | Used in `main.c` to configure the system clock and enable peripheral clocks.              |
| `SysTick`        | Configured in `main.c` for periodic interrupts. The SysTick handler is defined in `IRQ_Handler.c`. |
| `Timer`          | Configured in `main.c` for periodic events, PWM, or input capture. Interrupts are handled in `IRQ_Handler.c`. |
| `USART`          | Configured in `main.c` for serial communication. Interrupts are handled in `IRQ_Handler.c`. |

---

### **6. Workflow**
1. **Startup Code**:
   - Initializes the microcontroller and calls the `main` function.

2. **Main Application**:
   - Configures the system clock using the RCC driver.
   - Initializes peripherals (e.g., GPIO, USART, Timer) using the respective driver functions.
   - Implements the main application logic, including data processing and peripheral operations.

3. **Interrupt Handling**:
   - Peripheral interrupts are enabled and configured in `main.c`.
   - The corresponding ISRs in `IRQ_Handler.c` handle events and call driver functions for processing.

4. **Memory Mapping**:
   - The linker script ensures that peripheral registers are correctly mapped to their memory addresses.
   - Driver functions access these registers to configure and control peripherals.

---

### **Notes**
- Ensure that the startup code and linker script are correctly configured for the STM32F4xx microcontroller.
- Use the driver functions in `main.c` to initialize and configure peripherals.
- Implement interrupt handlers in `IRQ_Handler.c` to process peripheral events.
- Refer to the `README.md` files in each driver folder for detailed usage instructions and examples.

