/**
 * @file CAN.h
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Some declaration for CAN (Controller Area Network) configuration of STM32F4xx (ARMCortex M4)
 * @date 2025-04-29
 *
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/

#include "stdio.h"
#include "stdint.h"

/*******************************************************************************
* CAN ADDRESS DEFINITION
*******************************************************************************/

#define ADDRESS_CAN_1 0x40006400UL
#define ADDRESS_CAN_2 0x40006800UL

/*******************************************************************************
* CAN REGISTER STRUCTURE DEFINITION
*******************************************************************************/

// Filter message structure
typedef struct
{
    uint32_t FR1; // Low 32 bits of filter
    uint32_t FR2; // High 32 bits of filter
} FilterID;

// Mailbox structure for transmit and receive message
typedef struct
{
    uint32_t TIR;
    uint32_t TDTR;
    uint32_t TDLR;
    uint32_t TDHR;
} MailBoxTx;

typedef struct
{
    uint16_t RIR;
    uint16_t RDTR;
    uint32_t RDLR;
    uint32_t RDHR;
} MailBoxRx;


// CAN register structure definition
typedef struct
{
    uint32_t MCR;
    uint32_t MSR;
    uint32_t TSR;
    uint32_t RF0R;
    uint32_t RF1R;
    uint32_t IER;
    uint32_t ESR;
    uint32_t BTR;
    uint32_t Reserved[88];
    MailBoxTx TIxR[3];  // Mailbox TX
    MailBoxRx RIxR[2];  // Mailbox RX
    uint32_t Reserved1[12];
    uint32_t FMR;
    uint32_t FM1R;
    uint32_t Reserved2;
    uint32_t FS1R;
    uint32_t Reserved3;
    uint32_t FFA1R;
    uint32_t Reserved4;
    uint32_t FA1R;
    uint32_t Reserved5[8];
    FilterID FxR1_2[28]; // x: 0 -> 27
} CANx;

/*************************************************************************************
* CAN CONTROL AND STATUS REGISTER DEFINITION
**************************************************************************************/

#define CAN_REQUEST_INITIALIZED_MODE(CANx)                  CANx->MCR |= (1 << 0)
#define CAN_GET_INITIALIZED_MODE(CANx)                      CANx->MSR & (1 << 0)

#define CAN_EXIT_INITIALIZED_MODE(CANx)                     CANx->MCR &= ~ (1 << 0)

#define CAN_EXIT_SLEEP_MODE(CANx)                           CANx->MCR &= ~(1 << 1)
#define CAN_GET_SLEEP_MODE(CANx)                            CANx->MSR & (1 << 1)

// Config baudrate
#define CAN_SELF_CONFIG_BAUDRATE    // If defined, Baudrate will be calculated base on the value input (prescaller, time segment 1, time segment 2, SJW))

#if !defined(CAN_SELF_CONFIG_BAUDRATE)
#define CAN_BAUDRATE_1GB 1000000
#define CAN_BAUDRATE_500KB 500000
#define CAN_BAUDRATE_100KB 100000
#define CAN_BAUDRATE_50KB 50000
#define CAN_BAUDRATE_10KB 10000
#endif

#define CAN_SET_BR_PRESCALER(CANx, value)                   CANx->BTR |= (value << 0)
#define CAN_SET_BR_TIME_SEGMENT_1(CANx, value)              CANx->BTR |= (value << 16)
#define CAN_SET_BR_TIME_SEGMENT_2(CANx, value)              CANx->BTR |= (value << 20)
#define CAN_SET_BR_SJW(CANx, value)                         CANx->BTR |= (value << 24) // 0 -> 3

/*************************************************************************************
* CAN FILTER REGISTER DEFINITION
**************************************************************************************/

// Filters Configuration
#define CAN_DEACTIVE_FILTER(CANx, filter_x)                 CANx->FA1R &= ~(1 << filter_x)
#define CAN_ACTIVE_FILTER(CANx, filter_x)                   CANx->FA1R |= (1 << filter_x)

enum
{
    CAN_FILTER_SCALE_SINGLE_32,
    CAN_FILTER_SCALE_DUAL_16,
};

#define CAN_SET_SCALE_SINGLE_32_FILTER(CANx, filter_x)      CANx->FS1R |= (1 << filter_x)
#define CAN_SET_SCALE_DUAL_16_FILTER(CANx, filter_x)        CANx->FS1R &= ~(1 << filter_x)

// Filter mask
enum
{
    CAN_FILTER_IDENTIFIER_MASK_MODE,
    CAN_FILTER_IDENTIFIER_LIST_MODE, // Default mode is list mode. So we don't need to set this bit if we want to use list mode. Only need to clear it if we want to use mask mode.
};

#define CAN_SET_FILTER_IDENTIFIER_MASK_MODE(CANx, filter_x) CANx->FM1R |= (1 << filter_x)
#define CAN_SET_FILTER_IDENTIFIER_LIST_MODE(CANx, filter_x) CANx->FM1R &= ~(1 << filter_x)

// Active filter mode
#define CAN_INITIALIZE_MODE_FOR_FILTER(CANx)                CANx->FMR |= (1 << 0)
#define CAN_NORMAL_MODE_FOR_FILTER(CANx)                    CANx->FMR &= ~(1 << 0)

// Set ID for List mode Or ID for Mask mode for filter
#define CAN_SET_FILTER_ID(CANx, filter_x, id)               CANx->FxR1_2[filter_x].FR1 = id
#define CAN_SET_FILTER_EXTRA_INFOR(CANx, filter_x, infor)   CANx->FxR1_2[filter_x].FR2 = infor


/*************************************************************************************
* CAN MAILBOX REGISTER DEFINITION
**************************************************************************************/

enum
{
    MAILBOX_0,
    MAILBOX_1,
    MAILBOX_2,
};

// Enable mailbox using
#define ENABLE_MAILBOX_TRANSMIT_REQUEST(CANx, mailbox)      CANx->TIxR[mailbox].TIR |= 1 << 0
#define SET_MAILBOXTX_TRANSMIT_ID(CANx, mailbox, ID)        CANx->TIxR[mailbox].TIR |= (ID << 21)

// Setting length of data
#define SET_TX_DATA_LENGTH(CANx, mailbox, length)           CANx->TIxR[mailbox].TDTR |= (length << 0)

// Clear mailbox first
#define CLEAR_MAILBOX_DATA(CANx, mailbox)                   CANx->TIxR[mailbox].TIR = 0x0000

#define CAN_SET_DATA_BYTE(CANx, mailbox, data)              CANx->TIxR[mailbox].TDLR = data

enum
{
    MAILBOX_RX_0,
    MAILBOX_RX_1,
};

#define CAN_GET_DATA_BYTE(CANx, mailboxRX)                  CANx->RIxR[mailboxRX].RDLR & 0xff

enum
{
    MESSAGE_FIFO0,
    MESSAGE_FIFO1,
};

#define CAN_GET_MESSAGE_FIFO0_PENDING(CANx)                 CANx->RF0R & 0x03 // 11 (FMP bits)
#define CAN_GET_MESSAGE_FIFO1_PENDING(CANx)                 CANx->RF1R & 0x03 // 11 (FMP bits)
#define CAN_CLEAR_FIFO0_PENDING(CANx)                       CANx->RF0R |= (1 << 5)
#define CAN_CLEAR_FIFO1_PENDING(CANx)                       CANx->RF1R |= (1 << 5)

/*************************************************************************************
* CAN INTERRUPT REGISTER DEFINITION
**************************************************************************************/

// For Transmit mailbox
#define CAN_ENABLE_INTERRUPT_TRANSMIT(CANx)                 CANx->IER |= (1 << 0)
#define CAN_DISABLE_INTERRUPT_TRANSMIT(CANx)                CANx->IER &= ~(1 << 0)

// For Receive FIFO0
#define CAN_ENABLE_INTERRUPT_RECEIVE_FIFO0(CANx)            CANx->IER |= (1 << 1)
#define CAN_DISABLE_INTERRUPT_RECEIVE_FIFO0(CANx)           CANx->IER &= ~(1 << 1)

// For Receive FIFO1
#define CAN_ENABLE_INTERRUPT_RECEIVE_FIFO1(CANx)            CANx->IER |= (1 << 4)
#define CAN_DISABLE_INTERRUPT_RECEIVE_FIFO1(CANx)           CANx->IER &= ~(1 << 4)

// Transmit interrupt flag
#define CLEAR_TRANSMIT_MB0_INTERRUPT_FLAG(CANx)                 CANx->TSR |= (1 << 1)
#define GET_TRANSMIT_MB0_INTERRUPT_FLAG(CANx)                   CANx->TSR & (1 << 1)

#define CLEAR_TRANSMIT_MB1_INTERRUPT_FLAG(CANx)                 CANx->TSR |= (1 << 9)
#define GET_TRANSMIT_MB1_INTERRUPT_FLAG(CANx)                   CANx->TSR & (1 << 9)

#define CLEAR_TRANSMIT_MB2_INTERRUPT_FLAG(CANx)                 CANx->TSR |= (1 << 17)
#define GET_TRANSMIT_MB2_INTERRUPT_FLAG(CANx)                   CANx->TSR & (1 << 17)



/*************************************************************************************
 * FUNCTIONS DEFINITION
 *************************************************************************************/
void CAN_ConfigGPIOPin(CANx *CAN_x);

#if !defined(CAN_SELF_CONFIG_BAUDRATE)
void CAN_BaudrateConfig(CANx *CAN_x, uint32_t BaudRate);
#else
void CAN_BaudrateConfig(CANx *CAN_x, uint16_t Prescaler, uint8_t TimeSegment1, uint8_t TimeSegment2, uint8_t SJW);
#endif

void CAN_MessageFilterConfig(CANx *CAN_x, uint8_t FilterNumber, uint8_t FilterMode, uint8_t Scale, uint32_t ID, uint32_t ExtraInfor);
void CAN_MailboxTransmitConfig(CANx *CAN_x, uint8_t Mailbox, uint32_t ID, uint8_t DataLength);

#if !defined(CAN_SELF_CONFIG_BAUDRATE)
void CAN_Configuration(CANx *CAN_x, uint32_t Baudrate,    // baudrate
                        uint8_t Mailbox, uint32_t TX_ID, uint8_t TX_DataLenght,                                     // TX mailbox
                        uint8_t FilterNumber, uint8_t FilterMode, uint8_t ScaleMode, uint32_t RX_ID, uint32_t ExtraInfor);  // RX filter message
#else
void CAN_Configuration(CANx *CAN_x, uint32_t Prescaler, uint8_t TimeSegment1, uint8_t TimeSegment2, uint8_t SJW,    // baudrate
                        uint8_t Mailbox, uint32_t TX_ID, uint8_t TX_DataLenght,                                     // TX mailbox
                        uint8_t FilterNumber, uint8_t FilterMode, uint8_t ScaleMode, uint32_t RX_ID, uint32_t ExtraInfor);  // RX filter message
#endif

void CAN_Transmit_Data(CANx *CAN_x, uint8_t mailbox, uint8_t data);
uint8_t CAN_Receive_Data(CANx *CAN_x, uint8_t mailbox, uint8_t FIFOx);

void CAN_EnableTransmitInterrupt(CANx *CAN_x);
void CAN_EnableReceiveInterrupt(CANx *CAN_x, uint8_t FIFOx);

