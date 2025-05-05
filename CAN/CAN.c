/**
 * @file CAN.c
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief CAN (Controller Area Network) configuration of STM32F4xx (ARMCortex M4)
 * @date 2025-04-29
 *
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/

#include "CAN.h"
#include "../GPIO/GPIO.h"
#include "../RCC/RCC.h"

/******************************************************************************
 * Variables definition
 ******************************************************************************/

CANx *CAN1 = (CANx *)ADDRESS_CAN_1; // CAN1 base address
CANx *CAN2 = (CANx *)ADDRESS_CAN_2; // CAN2 base address

GPIOn *gpio_can_A = (GPIOn*) ADDRESS_GPIO_A; // GPIOA base address
GPIOn *gpio_can_B = (GPIOn*) ADDRESS_GPIO_B; // GPIOB base address

/**
*******************************************************************************
* @ Name : CAN_ConfigGPIOPin
* @ Parameters: CANx* CAN_x
* @ Registers : GPIO registers
* @ Descriptions :
*		- Config GPIO for CAN pin (CAN_TX, CAN_RX pin):
*           . CAN_TX: moder althmate, output type pushpull, high speed, no pullup/pulldown
*           . CAN_RX: moder althmate, input floating, high speed, pullup
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-04-29
*******************************************************************************
*/
void CAN_ConfigGPIOPin(CANx* CAN_x)
{
    if(CAN_x == CAN1)
    {
        RCC_EnablePeripheralClock(CLOCK_CAN1);
        RCC_EnablePeripheralClock(CLOCK_GPIO_A);

        // PA11 : CAN1_TX, PA12: CAN1_RX, AF9
        GPIO_Configuration(gpio_can_A, GPIO_PIN11, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_NOTHING);  
        GPIO_Configuration(gpio_can_A, GPIO_PIN12, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_PULLUP);

        GPIO_ConfigAlternateFunc(gpio_can_A, GPIO_PIN11, AF9);
        GPIO_ConfigAlternateFunc(gpio_can_A, GPIO_PIN12, AF9);

    }
    else if(CAN_x == CAN2)
    {
        RCC_EnablePeripheralClock(CLOCK_CAN2);
        RCC_EnablePeripheralClock(CLOCK_GPIO_B);

        // PB12 : CAN2_TX, PB13: CAN2_RX, AF9
        GPIO_Configuration(gpio_can_B, GPIO_PIN12, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_NOTHING);  
        GPIO_Configuration(gpio_can_B, GPIO_PIN13, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_PULLUP);

        GPIO_ConfigAlternateFunc(gpio_can_B, GPIO_PIN12, AF9);
        GPIO_ConfigAlternateFunc(gpio_can_B, GPIO_PIN13, AF9);
    }
}

/**
*******************************************************************************
* @ Name : CAN_BaudrateConfig
* @ Parameters: CANx CAN_x, uint32_t BaudRate
* @ Registers : BTR registers
* @ Descriptions :
*		- Calculate baudrate for CAN bus base on parameter of prescaler, time segment1, time segment2 and clock bus use for CAN
*       + Formula: Baudrate = Fclk / (Prescaler + 1)(1 + (TimeSegment1 + 1) + (TimeSegment2 + 1))
*       + Example: Baudrate is 500kbps with system clock 16MHz
*           -> Prescaler = 3, TimeSegment1 = 2, TimeSegment2 = 3 <-> Baudrate = 16MHz / (3+1)(1 + (2+1) + (3+1)) = 500kbps
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-04-29
*******************************************************************************
*/
#if !defined(CAN_SELF_CONFIG_BAUDRATE)
void CAN_BaudrateConfig(CANx CAN_x, uint32_t BaudRate);
{
    switch (BaudRate)
    {
#if defined(USE_SYSCLK_16MHz)
        case CAN_BAUDRATE_1GB:
            // 1000000 bps = 16000000/ ((3+1)(1 + (0+1) + (1+1))
            CAN_SET_BR_PRESCALER(CAN_x, 3);
            CAN_SET_BR_TIME_SEGMENT_1(CAN_x, 0);
            CAN_SET_BR_TIME_SEGMENT_2(CAN_x, 1);    
        break;
        case CAN_BAUDRATE_500KB:
            // 500000 bps = 16000000/ ((3+1)(1 + (2+1) + (3+1))
            CAN_SET_BR_PRESCALER(CAN_x, 3);
            CAN_SET_BR_TIME_SEGMENT_1(CAN_x, 2);
            CAN_SET_BR_TIME_SEGMENT_2(CAN_x, 3);
        break;
        case CAN_BAUDRATE_100KB:
            // 100000 bps = 16000000/ ((9+1)(1 + (8+1) + (5+1))
            CAN_SET_BR_PRESCALER(CAN_x, 9);
            CAN_SET_BR_TIME_SEGMENT_1(CAN_x, 8);
            CAN_SET_BR_TIME_SEGMENT_2(CAN_x, 5);
        break;
        case CAN_BAUDRATE_50KB:
            // 50000 bps = 16000000/ ((19+1)(1 + (8+1) + (5+1))
            CAN_SET_BR_PRESCALER(CAN_x, 19);
            CAN_SET_BR_TIME_SEGMENT_1(CAN_x, 8);
            CAN_SET_BR_TIME_SEGMENT_2(CAN_x, 5);
        break;
        case CAN_BAUDRATE_10KB:
            // 10000 bps = 16000000/ ((159+1)(1 + (8+1) + (5+1))
            CAN_SET_BR_PRESCALER(CAN_x, 159);
            CAN_SET_BR_TIME_SEGMENT_1(CAN_x, 8);
            CAN_SET_BR_TIME_SEGMENT_2(CAN_x, 5);
        break;
#elif defined(USE_SYSCLK_24MHz)
        // TODO: add more baudrate configuration for system clock 24MHz
#elif defined(USE_SYSCLK_36MHz)
        // TODO: add more baudrate configuration for system clock 36MHz
#elif defined(USE_SYSCLK_48MHz)
        // TODO: add more baudrate configuration for system clock 48MHz
#elif defined(USE_SYSCLK_56MHz)
        // TODO: add more baudrate configuration for system clock 56MHz
#elif defined(USE_SYSCLK_72MHz)
        // TODO: add more baudrate configuration for system clock 72MHz
#endif
        default:
            break;
    }

    CAN_SET_BR_SJW(CANx, 2); // Synchronization Jump Width (SJW) = 2 (max value is 4, min value is 1))
}
#else
void CAN_BaudrateConfig(CANx* CAN_x, uint16_t Prescaler, uint8_t TimeSegment1, uint8_t TimeSegment2, uint8_t SJW)
{
    // Baudrate = Fclk / (Prescaler + 1)(1 + (TimeSegment1 + 1) + (TimeSegment2 + 1))
    CAN_SET_BR_PRESCALER(CAN_x, Prescaler);
    CAN_SET_BR_TIME_SEGMENT_1(CAN_x, TimeSegment1);
    CAN_SET_BR_TIME_SEGMENT_2(CAN_x, TimeSegment2);

    CAN_SET_BR_SJW(CAN_x, SJW); // Synchronization Jump Width (SJW) = 2 (max value is 4, min value is 1))
}
#endif

/**
*******************************************************************************
* @ Name : CAN_MessageFilterConfig
* @ Parameters: CANx* CAN_x, uint8_t FilterNumber, uint8_t FilterMode, uint8_t Scale, uint32_t ID, uint32_t ExtraInfor
* @ Registers : CAN Filter registers
* @ Descriptions :
*		- Configure filter message for CAN bus with the following process:
*         1. Disable filter message
*         2. Enable scale of filter 32-bit for message or 16bit Dual CAN
*         3. Set filter mode to mask mode or list mode
*         4. Switch filter to active initilize mode
*         5. Set filter identifier and extra information
*         6. Enable filter message
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-04-29
*******************************************************************************
*/
void CAN_MessageFilterConfig(CANx* CAN_x, uint8_t FilterNumber, uint8_t FilterMode, uint8_t Scale, uint32_t ID, uint32_t ExtraInfor)
{
    // Disable filter message before configuring it
    CAN_DEACTIVE_FILTER(CAN_x, FilterNumber);

    // Enable Scale of filter 32-bit for message or 16bit Dual CAN
    if(Scale == CAN_FILTER_SCALE_SINGLE_32)
        CAN_SET_SCALE_SINGLE_32_FILTER(CAN_x, FilterNumber);
    else if(Scale == CAN_FILTER_SCALE_DUAL_16)
        CAN_SET_SCALE_DUAL_16_FILTER(CAN_x, FilterNumber);

    // Set filter mode to mask mode or list mode
    if(FilterMode ==  CAN_FILTER_IDENTIFIER_MASK_MODE)
        CAN_SET_FILTER_IDENTIFIER_MASK_MODE(CAN_x, FilterNumber);
    else if(FilterMode == CAN_FILTER_IDENTIFIER_LIST_MODE)
        CAN_SET_FILTER_IDENTIFIER_LIST_MODE(CAN_x, FilterNumber);

    // Switch filter to active initilize mode
    CAN_INITIALIZE_MODE_FOR_FILTER(CAN_x);

    // Set filter identifier and extra information
    CAN_SET_FILTER_ID(CAN_x, FilterNumber, ID);
    CAN_SET_FILTER_EXTRA_INFOR(CAN_x, FilterNumber, ExtraInfor);

    // Enable filter message
    CAN_ACTIVE_FILTER(CAN_x, FilterNumber);

    
}


/**
*******************************************************************************
* @ Name : CAN_MailboxTransmitConfig
* @ Parameters: CANx *CAN_x, uint8_t Mailbox, uint32_t ID, uint8_t DataLength
* @ Registers : CAN Mailbox registers
* @ Descriptions :
*		- Configure mailbox tramsmit for CAN bus with the following process:
*         1. Clear mailbox data
*         2. Set identifier (ID)
*         3. Set data length
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-04-29
*******************************************************************************
*/
void CAN_MailboxTransmitConfig(CANx *CAN_x, uint8_t Mailbox, uint32_t ID, uint8_t DataLength)
{
    // Clear mailbox data
    CLEAR_MAILBOX_DATA(CAN_x, Mailbox);

    // Set identifier
    SET_MAILBOXTX_TRANSMIT_ID(CAN_x, Mailbox, ID);

    // Set data length
    SET_TX_DATA_LENGTH(CAN_x, Mailbox, DataLength);
}

/**
*******************************************************************************
* @ Name : CAN_Configuration
* @ Parameters: 
* @ Registers : CAN registers
* @ Descriptions :
*		- Configure CAN bus with the following process:
*         1. Config GPIO for CAN pin (CAN_TX, CAN_RX pin)
*         2. Enter CAN Initialize mode and wait for ACK
*         3. Exit Sleepmode
*         4. Config baudrate for CAN bus
*         5. Config Transmit mailbox
*         6. Config Filter message data receive
*         7. Exit Initialize mode
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-04-29
*******************************************************************************
*/
#if !defined(CAN_SELF_CONFIG_BAUDRATE)
void CAN_Configuration(CANx *CAN_x, uint32_t Baudrate,    // baudrate
                        uint8_t Mailbox, uint32_t TX_ID, uint8_t TX_DataLenght,                                     // TX mailbox
                        uint8_t FilterNumber, uint8_t FilterMode, uint8_t ScaleMode, uint32_t RX_ID, uint32_t ExtraInfor)  // RX filter message
#else
void CAN_Configuration(CANx *CAN_x, uint32_t Prescaler, uint8_t TimeSegment1, uint8_t TimeSegment2, uint8_t SJW,    // baudrate
                        uint8_t Mailbox, uint32_t TX_ID, uint8_t TX_DataLenght,                                     // TX mailbox
                        uint8_t FilterNumber, uint8_t FilterMode, uint8_t ScaleMode, uint32_t RX_ID, uint32_t ExtraInfor)  // RX filter message
#endif
{
    // Config GPIO for CANx
    CAN_ConfigGPIOPin(CAN_x);

    // Enter CAN Initialize mode and wait for ACK
    CAN_REQUEST_INITIALIZED_MODE(CAN_x);
    while(!CAN_GET_INITIALIZED_MODE(CAN_x));

    //Exit Sleepmode
    CAN_EXIT_SLEEP_MODE(CAN_x);
    while(CAN_GET_SLEEP_MODE(CAN_x));

    // Config baudrate for CANx
#if !defined(CAN_SELF_CONFIG_BAUDRATE)
    CAN_BaudrateConfig(CAN_x, Baudrate);
#else
    CAN_BaudrateConfig(CAN_x, Prescaler, TimeSegment1, TimeSegment2, SJW);
#endif
    // Config Transmit mailbox
    CAN_MailboxTransmitConfig(CAN_x, Mailbox, TX_ID, TX_DataLenght);

    // Config Filter message data receive
    CAN_MessageFilterConfig(CAN_x, FilterNumber, FilterMode, ScaleMode, RX_ID, ExtraInfor);

    // Exit Initialize mode
    CAN_EXIT_INITIALIZED_MODE(CAN_x);
    while(CAN_GET_INITIALIZED_MODE(CAN_x));

}

/**
*******************************************************************************
* @ Name : CAN_Transmit_Data
* @ Parameters: CANx *CAN_x, uint8_t mailbox, uint8_t data
* @ Registers : 
* @ Descriptions :
*		- Transmit 1 byte of data by set data into TDLR register of mailbox and enable transmition request
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-04-29
*******************************************************************************
*/
void CAN_Transmit_Data(CANx *CAN_x, uint8_t mailbox, uint8_t data)
{
    // Set data to mailbox
    CAN_SET_DATA_BYTE(CAN_x, mailbox, data);

    // Enable mailbox transmition request
    ENABLE_MAILBOX_TRANSMIT_REQUEST(CAN_x, mailbox);
}

/**
*******************************************************************************
* @ Name : CAN_Receive_Data
* @ Parameters: CANx *CAN_x, uint8_t mailbox
* @ Registers : 
* @ Descriptions :
*		- Get 1 byte of data from mailbox after receiving data from CAN bus and release FIFO0 to get new data in next time receive data from CAN bus
* @ Return value : uint8_t
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-04-29
*******************************************************************************
*/
uint8_t CAN_Receive_Data(CANx *CAN_x, uint8_t mailbox, uint8_t FIFOx)
{
    uint8_t data_RX;

    // Check FIFOx is peding or not
    if(FIFOx == MESSAGE_FIFO0)
        while(!(CAN_GET_MESSAGE_FIFO0_PENDING(CAN_x))){}
    else if(FIFOx == MESSAGE_FIFO1)
        while(!(CAN_GET_MESSAGE_FIFO1_PENDING(CAN_x))){}

    data_RX = CAN_GET_DATA_BYTE(CAN_x, mailbox);

    // Release FIFOx
    if(FIFOx == MESSAGE_FIFO0)
        CAN_CLEAR_FIFO0_PENDING(CAN_x);
    else if(FIFOx == MESSAGE_FIFO1)
        CAN_CLEAR_FIFO1_PENDING(CAN_x);

    return data_RX;
}

void CAN_EnableTransmitInterrupt(CANx *CAN_x)
{
    CAN_ENABLE_INTERRUPT_TRANSMIT(CAN_x);
}

void CAN_EnableReceiveInterrupt(CANx *CAN_x, uint8_t FIFOx)
{
    if(FIFOx == MESSAGE_FIFO0)
        CAN_ENABLE_INTERRUPT_RECEIVE_FIFO0(CAN_x);
    else if(FIFOx == MESSAGE_FIFO1)
        CAN_ENABLE_INTERRUPT_RECEIVE_FIFO1(CAN_x);
}


