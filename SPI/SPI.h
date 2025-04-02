/**
 * @file SPI.h
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Some declaration for SPI configuration of STM32F407VGTx (ARMCortex M4)
 * @date 2025-03-03
 *
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/

#include "stdio.h"
#include "stdint.h"

/*******************************************************************************
* SPI ADDRESS DEFINITION
*******************************************************************************/

#define ADDRESS_SPI_1   0x40013000
#define ADDRESS_SPI_2   0x40003800
#define ADDRESS_SPI_3   0x40003C00

/*******************************************************************************
* SPI REGISTER STRUCTURE DEFINITION
*******************************************************************************/

typedef struct
{
    uint32_t CR1; // Control Register 1
    uint32_t CR2; // Control Register 2
    uint32_t SR;  // Status Register
    uint32_t DR;  // Data Register
    uint32_t CRCPR; // CRC Polynomial Register
    uint32_t RXCRCR; // RX CRC Register
    uint32_t TXCRCR; // TX CRC Register
    uint32_t I2SCFGR; // I2S Configuration Register
    uint32_t I2SPR; // I2S Prescaler Register
}SPIn;

extern volatile uint8_t value_re_IT_spi;

/*******************************************************************************
* DEFINITION
*******************************************************************************/
#define SOFTWARE_SLAVE_SELECT       1
#define HARDWARE_SLAVE_SELECT       0
#define NOTHING                     2
/*******************************************************************************
* CR1 REGISTERS DEFINITION
*******************************************************************************/

/*
    CPOL = 0 -> Default clock in Low level
    CPOL = 1 -> Default clock in High level
    CPHA = 1 -> The second edge of clock signal
    CPHA = 0 -> The first edge of clock signal
*/
#define SECOND_CLOCK_IDLE           (1 << 0) | (1 << 1)     // CPHA = 1 and CPOL = 1
#define SECOND_CLOCK_NO_IDLE        (1 << 0)                // CPHA = 1 and CPOL = 0

#define FIRST_CLOCK_IDLE            (1 << 1)                // CPHA = 0 and CPOL = 1
#define FIRST_CLOCK_NO_IDLE         0                       // CPHA = 0 and CPOL = 0

#define SET_SAMPLING_TYPE_WITH_CLOCK(spi, sampling_type)    spi->CR1 |= (sampling_type << 0)

// Master selection
#define MASTER_MODE                  1
#define SLAVE_MODE                   0
#define SET_MASTER_SELECT(spi, selection)       spi->CR1 |= (selection << 2)

// Baudrate control
#define BAUD_RATE_DIV_2              0
#define BAUD_RATE_DIV_4              1
#define BAUD_RATE_DIV_8              2
#define BAUD_RATE_DIV_16             3
#define BAUD_RATE_DIV_32             4
#define BAUD_RATE_DIV_64             5
#define BAUD_RATE_DIV_128            6
#define BAUD_RATE_DIV_256            7
#define SET_CLOCK_DIVIDER(spi, divider)         spi->CR1 |= (divider << 3)

// Enable SPI peripheral
#define ENABLE_SPI(spi)                         spi->CR1 |= (1 << 6)
#define DISABLE_SPI(spi)                        spi->CR1 &= ~(1 << 6)

// Data reading frame
#define MSB_FIRST       0
#define LSB_FIRST       1
#define SET_FRAME_FORMAT(spi, format)           spi->CR1 |= (format << 7)

// Set software selection by software
#define SET_SOFTWARE_SLAVE_MANAGEMENT(spi)      spi->CR1 |= ((1 << 9) | (1 << 8))   // SSM, SSI to 1

#define FULL_DUPLEX_MODE     0
#define RECEIVE_ONLY_MODE    1
#define SET_RECEIVE_MODE(spi, mode)         spi->CR1 |= (mode << 10)

// Data frame format 8/16bits
#define DATA_FRAME_8_BITS   0
#define DATA_FRAME_16_BITS  1
#define SET_DATA_FRAME(spi, fr_type)        spi->CR1 |= (fr_type << 11)

/*******************************************************************************
* CR2 REGISTERS DEFINITION
*******************************************************************************/

//RX buffer DMA
#define ENABLE_RX_BUFFER_DMA(spi)       spi->CR2 |= 1 << 0
#define DISABLE_RX_BUFFER_DMA(spi)       spi->CR2 &= ~(1 << 0)

//TX buffer DMA
#define ENABLE_TX_BUFFER_DMA(spi)       spi->CR2 |= 1 << 1
#define DISABLE_TX_BUFFER_DMA(spi)       spi->CR2 &= ~(1 << 1)

// Enable slave selection by hardware -> NSS = 0, SSOE = 1
#define SET_ENABLE_HARDWARE_NSS(spi)        spi->CR2 |= 1 << 2      //SSOE

// SPI type (Motorola/Texas Instruments)
#define SPI_MOTOROLA_MODE(spi)          spi->CR2 &= ~(1 << 4)
#define SPI_TI_MODE(spi)                spi->CR2 |= (1 << 4)

//Error interrupt mask
#define ENABLE_ERROR_MASKED(spi)        spi->CR2 &= ~(1 << 5)
#define ENABLE_ERROR_NOT_MASKED(spi)    spi->CR2 |= (1 << 5)

// RX buffer not empty interrupt (active when RX buffer not empty)
#define ENABLE_RX_BUFFER_NOT_EMPTY_INTERRUPT(spi)   spi->CR2 |= (1 << 6)
#define DISABLE_RX_BUFFER_NOT_EMPTY_INTERRUPT(spi)  spi->CR2 &= ~(1 << 6)

// TX buffer not empty interrupt (active when TX buffer not empty)
#define ENABLE_TX_BUFFER_NOT_EMPTY_INTERRUPT(spi)   spi->CR2 |= (1 << 7)
#define DISABLE_TX_BUFFER_NOT_EMPTY_INTERRUPT(spi)  spi->CR2 &= ~(1 << 7)


/*******************************************************************************
* SR REGISTERS DEFINITION
*******************************************************************************/

#define SPI_GET_RX_BUFFER_NOT_EMPTY_FLAG_STATUS(spi)        (spi->SR & (1 << 0))    // RXE flag
#define SPI_GET_TX_BUFFER_EMPTY_FLAG_STATUS(spi)            (spi->SR & (1 << 1))    // TXE flag
#define SPI_GET_OVERRUN_FLAG_STATUS(spi)                    (spi->SR & (1 << 6))
#define SPI_GET_BUSY_FLAG_STATUS(spi)                       (spi->SR & (1 << 7))

/*******************************************************************************
* DR REGISTERS DEFINITION
*******************************************************************************/

#define SPI_SET_DATA_REGISTER(spi, data)                    spi->DR = data
#define SPI_GET_DATA_REGISTER(spi)                          spi->DR


/*******************************************************************************
* FUNCTIONS DEFINITION
*******************************************************************************/
void SPI_Configuration(SPIn *spi_n,uint8_t spi_mode, uint8_t sampling_type,
    uint8_t clock_prescaler, uint8_t data_read_fr, 
    uint8_t receive_mode, uint8_t data_fr, uint8_t slave_mode_type);
void SPI_Transmiter(SPIn * spi_n, uint8_t* pData, uint8_t Size);
void SPI_ConfigGPIOPinForSPI(SPIn * spi_n);

void SPI_SlaveSelect(SPIn *spi_n);
void SPI_SlaveDisSelect(SPIn *spi_n);
void SPI_ReceiveData(SPIn* spi_n, uint8_t* pData, uint8_t Size);

void SPI_TransmitDataInterruptEnable(SPIn *spi_n);
void SPI_ReceiverDataInterruptEnable(SPIn *spi_n);
