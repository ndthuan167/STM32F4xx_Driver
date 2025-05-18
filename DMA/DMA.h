/**
 * @file DMA.h
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Some declaration for Direct Memory Access (DMA) of STM32F4xx (ARMCortex M4)
 * @date 2025-05-15
 *
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

/*******************************************************************************
 * DMAx ADDRESS DEFINITION
 *******************************************************************************/

#define ADDRESS_DMA1 0x40026000
#define ADDRESS_DMA2 0x40026400

/*******************************************************************************
 * DMA REGISTER STRUCTURE DEFINITION
 *******************************************************************************/

typedef struct
{
    uint32_t SxCR;   // Stream x configuration register
    uint32_t SxNDTR; // Stream x number of data register
    uint32_t SxPAR;  // Stream x peripheral address register
    uint32_t SxM0AR; // Stream x memory 0 address register
    uint32_t SxM1AR; // Stream x memory 1 address register
    uint32_t SxFCR;  // Stream x FIFO control register
} StreamX;

typedef struct
{
    uint32_t DMA_LISR;      // Low interrupt status register
    uint32_t DMA_HISR;      // High interrupt status register
    uint32_t DMA_LIFCR;     // Low interrupt flag clear register
    uint32_t DMA_HIFCR;     // High interrupt flag clear register
    StreamX DMA_StreamX[8]; // Stream X configuration registers
} DMAx;

/*******************************************************************************
 * ENUM DEFINITION
 *******************************************************************************/

enum DMA_StreamX
{
    DMA_STREAM0,
    DMA_STREAM1,
    DMA_STREAM2,
    DMA_STREAM3,
    DMA_STREAM4,
    DMA_STREAM5,
    DMA_STREAM6,
    DMA_STREAM7,
};

typedef struct
{
    DMAx *DMAn; // DMAx base address
    uint8_t StreamX; // Stream number
    uint8_t Channel; // Channel number
} DMA_Request;

typedef struct
{
    uint8_t Peripheral;
    uint8_t Direction;
    uint8_t MemDataSize;
    uint8_t PheDataSize;
    uint8_t PriorityLevel;
    uint32_t NumOfData;
    uint32_t Memory0Address;
    uint32_t Memory1Address;
    uint32_t PeripheralAddress;
    uint8_t Circular_mode;
    uint8_t FIFOEnable;
    uint8_t FIFOThreshold;
    uint8_t FIFOErrorIRQ;

}DMA_Variables;

#define     ENABLE          1
#define     DISABLE          0
#define     DMA2_START      47

enum Peripheral_DMAx
{
    SPI3_RX, I2C1_RX,TIM4_CH1, I2S3_EXT_RX, UART5_RX, UART8_TX,TIM5_CH3,
    TIM2_CH3,USART3_RX,UART7_TX, TIM5_CH4, TIM6_UP, TIM7_UP, I2C3_RX, UART4_RX,
    TIM3_CH4, TIM5_CH1, I2C2_RX, SPI2_RX, TIM4_CH2, USART3_TX, UART7_RX, TIM5_TRIG,
    SPI2_TX, I2S2_EXT_TX, I2C3_TX, UART4_TX, TIM3_CH1, TIM5_CH2, SPI3_TX, I2S3_EXT_TX,
    TIM2_CH1, USART2_RX, TIM3_CH2, DAC1, I2C1_TX, TIM4_UP, TIM2_CH2, USART2_TX, UART8_RX,
    TIM5_UP, DAC2, TIM4_CH3, TIM2_CH4, UART5_TX, TIM3_CH3, I2C2_TX,

    ADC_1 = DMA2_START, SPI1_RX, SPI4_RX, TIM1_TRIG, SAI1_A, DCMI, ADC_3, SPI4_TX, USART6_RX,
    TIM1_CH1, TIM8_UP, TIM8_CH1, ADC_2, USART1_RX, TIM1_CH2, SPI5_RX, SPI1_TX, SDIO,
    TIM8_CH2, SAI1_B, SPI5_TX, TIM1_COM, TIM8_CH3, SPI6_TX, CRYP_OUT, CRYP_IN, SPI6_RX,
    TIM1_UP, USART6_TX, TIM1_CH3, HASS_IN, USART1_TX, TIM8_CH4
};

#define NO_USE  0

/*******************************************************************************
 * DMA_L/HISR REGISTERS DEFINITION
 *******************************************************************************/

enum DMA_Irq_Flags
{
    DMA_FIFO_ERROR_IRQ_FLAG = 0,
    DMA_DIRECT_MODE_ERROR_IRQ_FLAG,
    DMA_TRANSFER_ERROR_IRQ_FLAG,
    DMA_HAFT_TRANSFER_COMPLETE_IRQ_FLAG,
    DMA_TRANSFER_COMPLETE_IRQ_FLAG,
};

// FIFO error
#define DMA_GET_LOW_IRQ_FLAG(DMAn)      DMAn->DMA_LISR
#define DMA_GET_HIGH_IRQ_FLAG(DMAn)     DMAn->DMA_HISR

/*******************************************************************************
 * DMA_L/HISCR REGISTERS DEFINITION
 *******************************************************************************/

// Clear FIFO error flag
#define DMA_CLEAR_FIFO_ERROR_IRQ_FLAG(DMAn, stream)              \
    do                                                           \
    {                                                            \
        if (stream == DMA_STREAM0 || stream == DMA_STREAM1)      \
            DMAn->DMA_LIFCR |= (1 << (6 * stream));              \
        else if (stream == DMA_STREAM2 || stream == DMA_STREAM3) \
            DMAn->DMA_LIFCR |= (1 << (16 + (6 * (stream - 2)))); \
        else if (stream == DMA_STREAM4 || stream == DMA_STREAM5) \
            DMAn->DMA_HIFCR |= (1 << (6 * stream));              \
        else if (stream == DMA_STREAM6 || stream == DMA_STREAM7) \
            DMAn->DMA_HIFCR |= (1 << (16 + (6 * (stream - 2)))); \
    } while (0)

// Clear direct mode error flag
#define DMA_CLEAR_DIRECT_MODE_ERROR_IRQ_FLAG(DMAn, stream)       \
    do                                                           \
    {                                                            \
        if (stream == DMA_STREAM0 || stream == DMA_STREAM1)      \
            DMAn->DMA_LIFCR |= (1 << (6 * stream) + 2);          \
        else if (stream == DMA_STREAM2 || stream == DMA_STREAM3) \
            DMAn->DMA_LIFCR |= (1 << (18 + (6 * (stream - 2)))); \
        else if (stream == DMA_STREAM4 || stream == DMA_STREAM5) \
            DMAn->DMA_HIFCR |= (1 << (6 * stream) + 2);          \
        else if (stream == DMA_STREAM6 || stream == DMA_STREAM7) \
            DMAn->DMA_HIFCR |= (1 << (18 + (6 * (stream - 2)))); \
    } while (0)

// Clear transfer error flag
#define DMA_CLEAR_TRANSFER_ERROR_IRQ_FLAG(DMAn, stream)          \
    do                                                           \
    {                                                            \
        if (stream == DMA_STREAM0 || stream == DMA_STREAM1)      \
            DMAn->DMA_LIFCR |= (1 << (6 * stream) + 3);          \
        else if (stream == DMA_STREAM2 || stream == DMA_STREAM3) \
            DMAn->DMA_LIFCR |= (1 << (19 + (6 * (stream - 2)))); \
        else if (stream == DMA_STREAM4 || stream == DMA_STREAM5) \
            DMAn->DMA_HIFCR |= (1 << (6 * stream) + 3);          \
        else if (stream == DMA_STREAM6 || stream == DMA_STREAM7) \
            DMAn->DMA_HIFCR |= (1 << (19 + (6 * (stream - 2)))); \
    } while (0)

// Clear haft transfer complete flag
#define DMA_CLEAR_HAFT_TRANSFER_COMPLETE_IRQ_FLAG(DMAn, stream)  \
    do                                                           \
    {                                                            \
        if (stream == DMA_STREAM0 || stream == DMA_STREAM1)      \
            DMAn->DMA_LIFCR |= (1 << (6 * stream) + 4);          \
        else if (stream == DMA_STREAM2 || stream == DMA_STREAM3) \
            DMAn->DMA_LIFCR |= (1 << (20 + (6 * (stream - 2)))); \
        else if (stream == DMA_STREAM4 || stream == DMA_STREAM5) \
            DMAn->DMA_HIFCR |= (1 << (6 * stream) + 4);          \
        else if (stream == DMA_STREAM6 || stream == DMA_STREAM7) \
            DMAn->DMA_HIFCR |= (1 << (20 + (6 * (stream - 2)))); \
    } while (0)

// Clear transfer complete flag
#define DMA_CLEAR_TRANSFER_COMPLETE_IRQ_FLAG(DMAn, stream)       \
    do                                                           \
    {                                                            \
        if (stream == DMA_STREAM0 || stream == DMA_STREAM1)      \
            DMAn->DMA_LIFCR |= (1 << (6 * stream) + 5);          \
        else if (stream == DMA_STREAM2 || stream == DMA_STREAM3) \
            DMAn->DMA_LIFCR |= (1 << (21 + (6 * (stream - 2)))); \
        else if (stream == DMA_STREAM4 || stream == DMA_STREAM5) \
            DMAn->DMA_HIFCR |= (1 << (6 * stream) + 5);          \
        else if (stream == DMA_STREAM6 || stream == DMA_STREAM7) \
            DMAn->DMA_HIFCR |= (1 << (21 + (6 * (stream - 2)))); \
    } while (0)

/*******************************************************************************
 * DMA_SxCR REGISTERS DEFINITION
 *******************************************************************************/

// Stream Enable
#define DMA_STREAM_ENABLE(DMAn, stream)                             DMAn->DMA_StreamX[stream].SxCR |= (1 << 0)
#define DMA_STREAM_DISABLE(DMAn, stream)                            DMAn->DMA_StreamX[stream].SxCR &= ~(1 << 0)

// Direct mode error interrupt enable/disable
#define DMA_DIRECT_MODE_ERROR_IRQ_ENABLE(DMAn, stream)              DMAn->DMA_StreamX[stream].SxCR |= (1 << 1)
#define DMA_DIRECT_MODE_ERROR_IRQ_DISABLE(DMAn, stream)             DMAn->DMA_StreamX[stream].SxCR &= ~(1 << 1)

// Tranfer error interrupt enable/disable
#define DMA_TRANSFER_ERROR_IRQ_ENABLE(DMAn, stream)                 DMAn->DMA_StreamX[stream].SxCR |= (1 << 2)
#define DMA_TRANSFER_ERROR_IRQ_DISABLE(DMAn, stream)                DMAn->DMA_StreamX[stream].SxCR &= ~(1 << 2)

// Half transfer interrupt enable/disable
#define DMA_HALF_TRANSFER_IRQ_ENABLE(DMAn, stream)                  DMAn->DMA_StreamX[stream].SxCR |= (1 << 3)
#define DMA_HALF_TRANSFER_IRQ_DISABLE(DMAn, stream)                 DMAn->DMA_StreamX[stream].SxCR &= ~(1 << 3)

// Transfer complete interrupt enable/disable
#define DMA_TRANSFER_COMPLETE_IRQ_ENABLE(DMAn, stream)              DMAn->DMA_StreamX[stream].SxCR |= (1 << 4)
#define DMA_TRANSFER_COMPLETE_IRQ_DISABLE(DMAn, stream)             DMAn->DMA_StreamX[stream].SxCR &= ~(1 << 4)

// Peripheral flow controller
#define DMA_FLOW_CONTROLLER(DMAn, stream)                           DMAn->DMA_StreamX[stream].SxCR &= ~(1 << 5)
#define PERIPHERAL_FLOW_CONTROLLER(DMAn, stream)                    DMAn->DMA_StreamX[stream].SxCR |= (1 << 5)

// Data tranfer direction
enum Data_transfer_direction
{
    DIR_PHE2MEM,
    DIR_MEM2PHE,
    DIR_MEM2MEM,
};
#define DMA_DATA_TRANSFER_DIRECTION(DMAn, stream, dir)              DMAn->DMA_StreamX[stream].SxCR |= (dir << 6)

// Circular mode
#define DMA_CIRCULAR_MODE_ENABLE(DMAn, stream)                      DMAn->DMA_StreamX[stream].SxCR |= (1 << 8)
#define DMA_CIRCULAR_MODE_DISABLE(DMAn, stream)                     DMAn->DMA_StreamX[stream].SxCR &= ~(1 << 8)

// Peripheral data size
enum data_size
{
    PDATA_SIZE_BYTE,      // 8-bit
    PDATA_SIZE_HALF_WORD, // 16-bit
    PDATA_SIZE_WORD,      // 32-bit
};

#define DMA_PERIPHERAL_DATA_SIZE(DMAn, stream, size)                DMAn->DMA_StreamX[stream].SxCR |= (size << 11)
#define DMA_MEM_DATA_SIZE(DMAn, stream, size)                       DMAn->DMA_StreamX[stream].SxCR |= (size << 13)

// Priority level
enum priority_level
{
    PL_LOW,
    PL_MEDIUM,
    PL_HIGH,
    PL_VERY_HIGH,
};

#define DMA_PRIORITY_LEVEL(DMAn, stream, level)                     DMAn->DMA_StreamX[stream].SxCR |= (level << 16)

// Channel selection
enum channel_selection
{
    DMA_CHANNEL_0,
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3,
    DMA_CHANNEL_4,
    DMA_CHANNEL_5,
    DMA_CHANNEL_6,
    DMA_CHANNEL_7,
};

#define DMA_CHANNEL_SELECTION(DMAn, stream, channel)                DMAn->DMA_StreamX[stream].SxCR |= (channel << 25)

/*******************************************************************************
 * DMA_SxNDTR REGISTERS DEFINITION
 *******************************************************************************/

#define DMA_SET_NUM_OF_DATA(DMAn, stream, value)                    DMAn->DMA_StreamX[stream].SxNDTR = (value)

/*******************************************************************************
 * DMA_SxPAR REGISTERS DEFINITION
 *******************************************************************************/
#define DMA_SET_PHE_ADDRESS(DMAn, stream, address)                  DMAn->DMA_StreamX[stream].SxPAR = (address)

/*******************************************************************************
 * DMA_SxM0AR REGISTERS DEFINITION
 *******************************************************************************/
#define DMA_SET_MEM0_ADDRESS(DMAn, stream, address)                 DMAn->DMA_StreamX[stream].SxM0AR = (address)

/*******************************************************************************
 * DMA_SxM1AR REGISTERS DEFINITION
 *******************************************************************************/
#define DMA_SET_MEM1_ADDRESS(DMAn, stream, address)                 DMAn->DMA_StreamX[stream].SxM1AR = (address)

/*******************************************************************************
 * DMA_SxFCR REGISTERS DEFINITION
 *******************************************************************************/

// FIFO threshold selection
enum fifo_threshold
{
    FIFO_THRESHOLD_1QUARTER,
    FIFO_THRESHOLD_HALF,
    FIFO_THRESHOLD_3QUARTERS,
    FIFO_THRESHOLD_FULL,
};
#define DMA_FIFO_THRESHOLD_SELECTION(DMAn, stream, threshold)       DMAn->DMA_StreamX[stream].SxFCR |= (threshold << 0)

// Direct mode config
#define DMA_DIRECT_MODE_ENABLE(DMAn, stream)                        DMAn->DMA_StreamX[stream].SxFCR &= ~(1 << 2)
#define DMA_DIRECT_MODE_DISABLE(DMAn, stream)                       DMAn->DMA_StreamX[stream].SxFCR |= (1 << 2)

// Get FIFO Status
#define DMA_GET_FIFO_STATUS(DMAn, stream)                           ((DMAn->DMA_StreamX[stream].SxFCR & (1 << 3)) >> 3)

// Set FIFO error interrupt
#define DMA_FIFO_ERROR_IRQ_ENABLE(DMAn, stream)                     DMAn->DMA_StreamX[stream].SxFCR |= (1 << 7)
#define DMA_FIFO_ERROR_IRQ_DISABLE(DMAn, stream)                    DMAn->DMA_StreamX[stream].SxFCR &= ~(1 << 7)


/*******************************************************************************
 * FUNCTION PROTOTYPES
 *******************************************************************************/
DMA_Request GetStreamAndChannelForPeripheral(uint8_t peripheral);
void DMA_Configuration(DMA_Variables DMA_val);
void DMA_EnableStream(DMA_Variables DMA_val);
void DMA_DisableStream(DMA_Variables DMA_val);

void DMA_EnableFIFOErrorIRQ(DMA_Variables DMA_val);
void DMA_EnableDirectModeErrorIQR(DMA_Variables DMA_val);
void DMA_EnableTransferErrorIQR(DMA_Variables DMA_val);
void DMA_EnableHalfTransferIQR(DMA_Variables DMA_val);
void DMA_EnableTransferCompleteIQR(DMA_Variables DMA_val);
bool DMA_Get_IRQ_Flag(DMAx *DMAn, uint8_t stream, uint8_t flag);

