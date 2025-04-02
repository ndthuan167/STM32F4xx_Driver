#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "math.h"

#define SOFT_SPI1 0
#define SOFT_SPI2 1
#define SOFT_SPI3 2

// mode
#define MODE_MASTER 0
#define MODE_SLAVE 1

// simpling type (CPOL, CPHA)
/*
    CPOL = 0 -> Default clock in Low level
    CPOL = 1 -> Default clock in High level
    CPHA = 1 -> The second edge of clock signal
    CPHA = 0 -> The first edge of clock signal
*/

//edge
#define RISING_EDGE     0
#define FALLING_EDGE    1
#define NOTHING_EDGE    2

//timing
#define FIRST_EDGE      0
#define SECOND_EDGE     1

enum
{
    SAMPLING_TYPE_1_EDGE_RISING ,   // CPHA = 0, CPOL = 0
    SAMPLING_TYPE_1_EDGE_FALLING,   // CPHA = 0, CPOL = 1
    SAMPLING_TYPE_2_EDGE_RISING,    // CPHA = 1, CPOL = 0
    SAMPLING_TYPE_2_EDGE_FALLING,   // CPHA = 1, CPOL = 1
};

// DATA READ TYPE
#define     MSB_FIRST   0
#define     LSB_FIRST   1

void SoftSPI_Master_GPIO_Configuration(uint8_t spi_n);
void SoftSPI_Slave_GPIO_Configuration(uint8_t spi_n);
void SoftSPI_ClockGeneration(uint8_t spi_n);

void SoftSPI_SlaveSelected(uint8_t spin_n);
void SoftSPI_SlaveDisSelected(uint8_t spin_n);

uint8_t SoftSPI_EdgeDetection(uint8_t spin_n);
uint8_t SoftSPI_FromSecEdgeDetection(uint8_t spi_n);
uint8_t SoftSPI_GetCSStatus(uint8_t spi_n);

void HexToBinConvert(uint8_t hex, uint8_t *bin);
void SoftSPI_Master_Configuration(uint8_t spin_n, uint8_t sampling_type, uint8_t read_data_type);
void SoftSPI_Slave_Configuration(uint8_t spin_n, uint8_t sampling_type, uint8_t read_data_type);

bool SoftSPI_Master_TransmiterRecevier(uint8_t spi_n, uint8_t data, uint8_t size);

uint8_t SoftSPI_Slave_TransmitterReceiver(uint8_t spi_n, uint8_t data, uint8_t size);
uint8_t SoftSPI_Slave_Transmitter(uint8_t spin_n, uint8_t data, uint8_t size);

void SoftSPI_Slave_SendMISO(uint8_t spin_n, uint8_t value);


