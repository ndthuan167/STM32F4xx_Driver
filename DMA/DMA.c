/**
 * @file RCC.c
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Configuration for Direct Memory Access (DMA) of STM32F4xx (ARMCortex M4)
 * @date 2025-05-17
 *
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/

#include "DMA.h"
#include "../RCC/RCC.h"

/******************************************************************************
 * Variables declaration 
 ******************************************************************************/

DMAx *DMA1 = (DMAx *)ADDRESS_DMA1;
DMAx *DMA2 = (DMAx *)ADDRESS_DMA2;

uint8_t index_channel = 0;
uint8_t index_stream = 0;

uint8_t const DMA1_request_mapping[8][8] =
{
//  Stream0         Stream1     Stream2      Stream3        Stream4      Stream5        Stream6     Stream7
    {SPI3_RX,       NO_USE,     SPI3_RX,     SPI2_RX,       SPI2_TX,     SPI3_TX,       NO_USE,     SPI3_TX,    },  // Channel0
    {I2C1_RX,       NO_USE,     TIM7_UP,     NO_USE,        TIM7_UP,     I2C1_RX,       I2C1_TX,    I2C1_TX,    },  // Channel1
    {TIM4_CH1,      NO_USE,     I2S3_EXT_RX, TIM4_CH2,      I2S2_EXT_TX, I2S3_EXT_TX,   TIM4_UP,    TIM4_CH3,   },  // Channel2
    {I2S3_EXT_RX,   TIM2_CH3,   I2C3_RX,     I2S3_EXT_RX,   I2C3_TX,     TIM2_CH1,      TIM2_CH2,   TIM2_CH4,   },  // Channel3
    {UART5_RX,      USART3_RX,  UART4_RX,    USART3_TX,     UART4_TX,    USART2_RX,     USART2_TX,  UART5_TX,   },  // Channel4
    {UART8_TX,      UART7_TX,   TIM3_CH4,    UART7_RX,      TIM3_CH1,    TIM3_CH2,      UART8_RX,   TIM3_CH3,   },  // Channel5
    {TIM5_CH3,      TIM5_CH4,   TIM5_CH1,    TIM5_TRIG,     TIM5_CH2,    NO_USE,        TIM5_UP,    NO_USE,     },  // Channel6
    {NO_USE,        TIM6_UP,    I2C2_RX,     I2C2_RX,       USART3_TX,   DAC1,          DAC2,       I2C2_TX,    },  // Channel7
};

uint8_t const DMA2_request_mapping[8][8] =
{
//  Stream0         Stream1     Stream2      Stream3        Stream4      Stream5        Stream6     Stream7
    {ADC_1,         SAI1_A,    TIM8_CH1,     SAI1_A,        ADC_1,       SAI1_B,        TIM1_CH1,   NO_USE,     },  // Channel0
    {NO_USE,        DCMI,       ADC_2,       ADC_2,         SAI1_B,      SPI6_TX,       SPI6_RX,    DCMI,       },  // Channel1
    {ADC_3,         ADC_3,     NO_USE,       SPI5_RX,       SPI5_TX,     CRYP_OUT,      CRYP_IN,    HASS_IN,    },  // Channel2
    {SPI1_RX,       NO_USE,     SPI1_RX,     SPI1_TX,       NO_USE,      SPI1_TX,       NO_USE,     NO_USE,     },  // Channel3
    {SPI4_RX,       SPI4_TX,    USART1_RX,   SDIO,          NO_USE,      USART1_RX,     SDIO,       USART1_TX,  },  // Channel4
    {NO_USE,        USART6_RX,  USART6_RX,   SPI4_RX,       SPI4_TX,     NO_USE,        USART6_TX,  USART6_TX,  },  // Channel5
    {TIM1_TRIG,     TIM1_CH1,   TIM1_CH2,    TIM1_CH1,      TIM1_COM,    TIM1_UP,       TIM1_CH3,   NO_USE,     },  // Channel6
    {NO_USE,        TIM8_UP,    TIM8_CH1,    TIM8_CH2,      TIM8_CH3,    SPI5_RX,       SPI5_TX,    TIM8_CH4,   },  // Channel7
};

/**
*******************************************************************************
* @ Name : GetStreamAndChannelForPeripheral
* @ Parameters: uint8_t peripheral
* @ Registers : 
* @ Descriptions :
*		- Get stream and chnnel for corresponding peripheral based on documentation
* @ Return value : DMA_Request
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-02-28
*******************************************************************************
*/
DMA_Request GetStreamAndChannelForPeripheral(uint8_t peripheral)
{
    DMA_Request request;
    
    if(peripheral < DMA2_START)
    {
        request.DMAn = DMA1;
        for (index_channel = 0; index_channel < 8; index_channel++)
        {
            for (index_stream = 0; index_stream < 8; index_stream++)
            {
                if (DMA1_request_mapping[index_channel][index_stream] == peripheral)
                {
                    request.StreamX = index_stream;
                    request.Channel = index_channel;
                    return request;
                }
            }
        }
    }
    else
    {
        request.DMAn = DMA2;
        for (index_channel = 0; index_channel < 8; index_channel++)
        {
            for (index_stream = 0; index_stream < 8; index_stream++)
            {
                if (DMA2_request_mapping[index_channel][index_stream] == peripheral)
                {
                    request.StreamX = index_stream;
                    request.Channel = index_channel;
                    return request;
                }
            }
        }
    }
		
		return request;
}

/**
*******************************************************************************
* @ Name : DMA_Configuration
* @ Parameters: DMA_Variables DMA_val
* @ Registers : DMA registers
* @ Descriptions :
*		- Configure DMA base on the parameters. Variables need to configure are:
*           Peripheral = {Peripheral_DMAx}
            Direction = {DIR_MEM2MEM, DIR_MEM2PHE, DIR_PHE2PHE}
            MemDataSize = {PDATA_SIZE_BYTE, PDATA_SIZE_HALFWORD, PDATA_SIZE_WORD}
            PheDataSize = {PDATA_SIZE_BYTE, PDATA_SIZE_HALFWORD, PDATA_SIZE_WORD}
            PriorityLevel = {PL_LOW, PL_MEDIUM, PL_HIGH, PL_VERY_HIGH}
            NumOfData = {0, 1, 2, 3, ...}
            Memory0Address = {ADDRESS_MEMORY0}
            Memory1Address = {ADDRESS_MEMORY1}
            PeripheralAddress = {ADDRESS_PERIPHERAL}
            FIFOEnable = {ENABLE, DISABLE}
            FIFOThreshold = {FIFO_THRESHOLD_1QUARTER, FIFO_THRESHOLD_HALF, FIFO_THRESHOLD_3QUARTER, FIFO_THRESHOLD_FULL}
            FIFOErrorIRQ = {ENABLE, DISABLE}
*
* @ Return value : DMA_Request
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-02-28
*******************************************************************************
*/
void DMA_Configuration(DMA_Variables DMA_val)
{
/* Process to configure DMA:
    1. Enable DMA clock
    2. Set Direction
    3. Set Data size
    4. Set Number of data
    5. Set Peripheral address
    6. Set Memory 0 address
    7. Set Memory 1 address
    8. Set Priority level
    9. Set Channel
*/
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


/**
*******************************************************************************
* @ Name : DMA_EnableStream
* @ Parameters: DMA_Variables DMA_val
* @ Registers : SxCR
* @ Descriptions :
*		- Enable DMA stream
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-17
*******************************************************************************
*/
void DMA_EnableStream(DMA_Variables DMA_val)
{
    uint8_t stream = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).StreamX;
    DMAx *DMAn = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).DMAn;

    // Enable DMA stream
    DMA_STREAM_ENABLE(DMAn, stream);
}

/**
*******************************************************************************
* @ Name : DMA_DisableStream
* @ Parameters: DMA_Variables DMA_val
* @ Registers : SxCR
* @ Descriptions :
*		- Diable DMA stream
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-17
*******************************************************************************
*/
void DMA_DisableStream(DMA_Variables DMA_val)
{
    uint8_t stream = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).StreamX;
    DMAx *DMAn = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).DMAn;

    // Disable DMA stream
    DMA_STREAM_ENABLE(DMAn, stream);
}

/**
*******************************************************************************
* @ Name : DMA_EnableFIFOErrorIRQ
* @ Parameters: DMA_Variables DMA_val
* @ Registers : SxCR
* @ Descriptions :
*		- Enable FIFO error interrupt
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-17
*******************************************************************************
*/
void DMA_EnableFIFOErrorIRQ(DMA_Variables DMA_val)
{
    uint8_t stream = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).StreamX;
    DMAx *DMAn = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).DMAn;

    // Enable FIFO error interrupt
    DMA_FIFO_ERROR_IRQ_ENABLE(DMAn, stream);
}

/**
*******************************************************************************
* @ Name : DMA_EnableDirectModeErrorIQR
* @ Parameters: DMA_Variables DMA_val
* @ Registers : SxCR
* @ Descriptions :
*		- Enable Direct mode error interrupt
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-17
*******************************************************************************
*/
void DMA_EnableDirectModeErrorIQR(DMA_Variables DMA_val)
{
    uint8_t stream = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).StreamX;
    DMAx *DMAn = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).DMAn;

    // Enable Direct mode error interrupt
    DMA_DIRECT_MODE_ERROR_IRQ_ENABLE(DMAn, stream);
}

/**
*******************************************************************************
* @ Name : DMA_EnableTransferErrorIQR
* @ Parameters: DMA_Variables DMA_val
* @ Registers : SxCR
* @ Descriptions :
*		- Enable transfer error interrupt
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-17
*******************************************************************************
*/
void DMA_EnableTransferErrorIQR(DMA_Variables DMA_val)
{
    uint8_t stream = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).StreamX;
    DMAx *DMAn = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).DMAn;

    // Enable transfer error interrupt
    DMA_TRANSFER_ERROR_IRQ_ENABLE(DMAn, stream);
}

/**
*******************************************************************************
* @ Name : DMA_EnableHalfTransferIQR
* @ Parameters: DMA_Variables DMA_val
* @ Registers : SxCR
* @ Descriptions :
*		- Enable half transfer interrupt
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-17
*******************************************************************************
*/
void DMA_EnableHalfTransferIQR(DMA_Variables DMA_val)
{
    uint8_t stream = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).StreamX;
    DMAx *DMAn = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).DMAn;

    // Enable half transfer interrupt
    DMA_HALF_TRANSFER_IRQ_ENABLE(DMAn, stream);
}

/**
*******************************************************************************
* @ Name : DMA_EnableTransferCompleteIQR
* @ Parameters: DMA_Variables DMA_val
* @ Registers : SxCR
* @ Descriptions :
*		- Enable transfer complete interrupt
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-17
*******************************************************************************
*/
void DMA_EnableTransferCompleteIQR(DMA_Variables DMA_val)
{
    uint8_t stream = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).StreamX;
    DMAx *DMAn = GetStreamAndChannelForPeripheral(DMA_val.Peripheral).DMAn;

    // Enable transfer complete interrupt
    DMA_TRANSFER_COMPLETE_IRQ_ENABLE(DMAn, stream);
}


/**
*******************************************************************************
* @ Name : DMA_Get_IRQ_Flag
* @ Parameters: DMAx *DMAn, uint8_t stream, uint8_t flag
* @ Registers : DMA_LISR, DMA_HISR
* @ Descriptions :
*		- Get IRQ flag status
*       + IRQ flag status:
*           - DMA_FIFO_ERROR_IRQ_FLAG
*           - DMA_DIRECT_MODE_ERROR_IRQ_FLAG
*           - DMA_TRANSFER_ERROR_IRQ_FLAG
*           - DMA_HAFT_TRANSFER_COMPLETE_IRQ_FLAG
*           - DMA_TRANSFER_COMPLETE_IRQ_FLAG
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-17
*******************************************************************************
*/
bool DMA_Get_IRQ_Flag(DMAx *DMAn, uint8_t stream, uint8_t flag)
{
    bool status = 0;
    uint8_t val_a;
    switch (flag)
    {
        case DMA_FIFO_ERROR_IRQ_FLAG:
            val_a = 0;
        break;
        case DMA_DIRECT_MODE_ERROR_IRQ_FLAG:
            val_a = 2;
        break;
        case DMA_TRANSFER_ERROR_IRQ_FLAG:
            val_a = 3;
        break;
        case DMA_HAFT_TRANSFER_COMPLETE_IRQ_FLAG:
            val_a = 4;
        break;
        case DMA_TRANSFER_COMPLETE_IRQ_FLAG:
            val_a = 5;
        break;
        default:
            break;
    }

    if(stream == DMA_STREAM0 || stream == DMA_STREAM1)
        status = (DMA_GET_LOW_IRQ_FLAG(DMAn) & (1 << (6 * stream) + val_a)) >> (6 * stream) + val_a;
    else if (stream == DMA_STREAM2 || stream == DMA_STREAM3)
        status = (DMA_GET_LOW_IRQ_FLAG(DMAn) & (1 << (16 + val_a + (6 * (stream - 2))))) >> (16 + val_a + (6 * (stream - 2)));
    else if (stream == DMA_STREAM4 || stream == DMA_STREAM5)
        status = (DMA_GET_HIGH_IRQ_FLAG(DMAn) & (1 << (6 * stream) + val_a)) >> (6 * stream) + val_a;
    else if (stream == DMA_STREAM6 || stream == DMA_STREAM7)
        status = (DMA_GET_HIGH_IRQ_FLAG(DMAn) & (1 << (16 + val_a + (6 * (stream - 2))))) >> (16 + val_a + (6 * (stream - 2)));

    return status;
}
