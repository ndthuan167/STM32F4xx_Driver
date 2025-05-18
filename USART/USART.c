/**
 * @file USART.c
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Configuration for USART of STM32F4xx (ARMCortex M4)
 * @date 2024-09-11
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/

#include "USART.h"
#include "math.h"
#include "../GPIO/GPIO.h"
#include "../RCC/RCC.h"
#include "../DMA/DMA.h"

/******************************************************************************
 * Definition
 ******************************************************************************/

GPIOn *gpio_a = (GPIOn *)ADDRESS_GPIO_A;
GPIOn *gpio_c = (GPIOn *)ADDRESS_GPIO_C;
GPIOn *gpio_d = (GPIOn *)ADDRESS_GPIO_D;

/**
*******************************************************************************
* @ Name : USART_BaudrateCalculator
* @ Parameters: uint32_t baudrate, float clockfrequency, uint8_t over8
* @ Registers :
* @ Descriptions :
*		- Calulate baudrate value for USART
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-09-11
*******************************************************************************
*/
uint16_t USART_BaudrateCalculator(uint32_t baudrate, float clockfrequency, uint8_t over8)
{
    float USARTDIV = (clockfrequency) / (8 * (2 - over8) * baudrate);
    uint16_t value = (clockfrequency) / (8 * (2 - over8) * baudrate);
    uint8_t mod = ceil((USARTDIV - (float)value) * 16);
    uint16_t baudrate_set = value << 4 | mod;
    return baudrate_set;
}

/**
*******************************************************************************
* @ Name : USART_Configuration
* @ Parameters: USART_Config_Variables USART_Val
* @ Registers : SR, BRR, CR1
* @ Descriptions :
*		- Configure the USART Baud Rate, Word Length, Parity Control and Parity Type and oversampling type.
*       + usartn: uasrt1/2/3/6, UART4/5
*		+ baudrate: BAUDRATE_9600, BAUDRATE_19200, BAUDRATE_115200,...
*		+ wordlength: DATA_BITS_8, DATA_BITS_9
*       + over8: OVERSAMPLING_BY_16, OVERSAMPLING_BY_8
*       + paritycontrol: PARITY_ENABLE, PARITY_DISABLE
*		+ parity: PARITY_EVEN, PARITY_ODD
*		- Enable the USART peripheral.
*       - Enable Transmiter/Receiver
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-09-12
*******************************************************************************
*/
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

/**
*******************************************************************************
* @ Name : USART_SendData
* @ Parameters: USARTn *usartn, uint8_t *pData, uint16_t Size
* @ Registers : DR
* @ Descriptions :
*		- Send data via usart by set data to DR register after checking the status of TXE bit.
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-09-11
*******************************************************************************
*/
void USART_SendData(USARTn *usartn, volatile uint8_t *pData, uint16_t Size)
{
    uint16_t data_send;
    while (Size > 0)
    {
        Size--;
        if (!(USART_GET_WRITEDATA_STATUS(usartn)))
        {
        };
        data_send = (*pData++ & (uint8_t)0xFF);
        USART_DATA_VALUE(usartn, data_send);
        uint32_t i;
        for (i = 0; i < 10000; i++)
        {
        };
    }
}

/**
*******************************************************************************
* @ Name : USART_SendData_DMA
* @ Parameters: USARTn *usart_n, uint8_t *pData, uint16_t Size
* @ Registers : DMA registers, DR
* @ Descriptions :
*		- Send data via usart by using DMA confirguration:
*            + Set DMA direction: Memory to Peripheral
*            + Set Peripheral address: usartn->DR
*            + Set Memory address: pData
*            + Set Number of data: Size
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-17
*******************************************************************************
*/
void USART_SendData_DMA(USARTn *usart_n, uint8_t *pData, uint16_t Size)
{
    DMA_Variables DMA_val;
    if(usart_n == (USARTn *)ADDRESS_USART_1)
        DMA_val.Peripheral = USART1_TX;
    else if(usart_n == (USARTn *)ADDRESS_USART_2)
        DMA_val.Peripheral = USART2_TX;
    else if(usart_n == (USARTn *)ADDRESS_USART_3)
        DMA_val.Peripheral = USART3_TX;
    else if(usart_n == (USARTn *)ADDRESS_USART_6)
        DMA_val.Peripheral = USART6_TX;
    else if(usart_n == (USARTn *)ADDRESS_UART_4)
        DMA_val.Peripheral = UART4_TX;
    else if(usart_n == (USARTn *)ADDRESS_UART_5)
        DMA_val.Peripheral = UART5_TX;

    DMA_val.Direction = DIR_MEM2PHE;
    DMA_val.MemDataSize = PDATA_SIZE_BYTE;
    DMA_val.PheDataSize = PDATA_SIZE_BYTE;
    DMA_val.PriorityLevel = PL_HIGH;
    DMA_val.NumOfData = Size;
    DMA_val.Memory0Address = (uint32_t)pData;
    DMA_val.Memory1Address = (uint32_t)pData;
    DMA_val.PeripheralAddress = (uint32_t)&usart_n->DR;
    DMA_val.FIFOEnable = DISABLE;
    DMA_Configuration(DMA_val);
    
    DMA_Request rq = GetStreamAndChannelForPeripheral(DMA_val.Peripheral);
    DMA_TRANSFER_COMPLETE_IRQ_ENABLE(rq.DMAn, rq.StreamX);
    DMA_EnableStream(DMA_val);

}

/**
*******************************************************************************
* @ Name : USART_ReceiveData
* @ Parameters: USARTn* usartn
* @ Registers : DR
* @ Descriptions :
*		- Return data receive from DR register after check status bit RXNE
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-09-11
*******************************************************************************
*/
unsigned char USART_ReceiveData(USARTn *usartn)
{
    while (!(USART_GET_READDATA_STATUS(usartn)))
    {
    };  
    return (USART_GET_DATA_VALUE(usartn));
}


/**
*******************************************************************************
* @ Name : USART_ReceiveData_DMA
* @ Parameters: USARTn *usart_n
* @ Registers : DMA registers, DR
* @ Descriptions :
*		- Receive data via usart by using DMA confirguration:
*            + Set DMA direction: Peripheral to Memory
*            + Set Peripheral address: usartn->DR
*            + Set Memory address: data_receive
*            + Set Number of data: 1
*            + Enable transfer complete interrupt
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-17
*******************************************************************************
*/
unsigned char USART_ReceiveData_DMA(USARTn *usartn)
{
    DMA_Variables DMA_val;
    unsigned char data_receive;

    if (usartn == (USARTn *)ADDRESS_USART_1)
        DMA_val.Peripheral = USART1_RX;
    else if (usartn == (USARTn *)ADDRESS_USART_2)
        DMA_val.Peripheral = USART2_RX;
    else if (usartn == (USARTn *)ADDRESS_USART_3)
        DMA_val.Peripheral = USART3_RX;
    else if (usartn == (USARTn *)ADDRESS_USART_6)
        DMA_val.Peripheral = USART6_RX;
    else if (usartn == (USARTn *)ADDRESS_UART_4)
        DMA_val.Peripheral = UART4_RX;
    else if (usartn == (USARTn *)ADDRESS_UART_5)
        DMA_val.Peripheral = UART5_RX;

    DMA_val.Direction = DIR_PHE2MEM;
    DMA_val.MemDataSize = PDATA_SIZE_BYTE;
    DMA_val.PheDataSize = PDATA_SIZE_BYTE;
    DMA_val.PriorityLevel = PL_HIGH;
    DMA_val.NumOfData = 1;
    DMA_val.Memory0Address = (uint32_t)&data_receive;
    DMA_val.Memory1Address = (uint32_t)&data_receive;
    DMA_val.PeripheralAddress = (uint32_t)&usartn->DR;
    DMA_val.FIFOEnable = DISABLE;
    DMA_Configuration(DMA_val);
    DMA_EnableStream(DMA_val);

    DMA_Request rq = GetStreamAndChannelForPeripheral(DMA_val.Peripheral);
    DMA_TRANSFER_COMPLETE_IRQ_ENABLE(rq.DMAn, rq.StreamX);
    while(!DMA_Get_IRQ_Flag(rq.DMAn, rq.StreamX, DMA_TRANSFER_COMPLETE_IRQ_FLAG))
    {
    };

    return data_receive;
}
/**
*******************************************************************************
* @ Name : USART_ReceiverDataInterruptEnable
* @ Parameters: USARTn* usartn
* @ Registers : CR1
* @ Descriptions :
*		- Enable received interrupt for usartn by enabling the RXNEIE bit in the CR1 register.
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-09-11
*******************************************************************************
*/
void USART_ReceiverDataInterruptEnable(USARTn* usartn)
{
    USART_ENABLE_RX_INTERRUPT(usartn);
}

/**
*******************************************************************************
* @ Name : USART_TransmiterDataInterruptEnable
* @ Parameters: USARTn* usartn
* @ Registers : CR1
* @ Descriptions :
*		- Enable transmitter interrupt for usartn by enabling the TXEIE bit in the CR1 register.
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-09-11
*******************************************************************************
*/
void USART_TransmiterDataInterruptEnable(USARTn* usartn)
{
    USART_ENABLE_TX_INTERRUPT(usartn);
}
