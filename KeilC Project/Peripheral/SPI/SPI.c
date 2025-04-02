/**
 * @file GPIO.c
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Configuration for SPI (Serial Peripheral Interface) of STM32F407VGTx (ARMCortex M4)
 * @date 2025-03-04
 *
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/

#include "SPI.h"
#include "../RCC/RCC.h"
#include "../GPIO/GPIO.h"

/******************************************************************************
 * Variables definition
 ******************************************************************************/
RCC *rcc = (RCC *)ADDRESS_RCC;
GPIOn *gpio_A_SPI = (GPIOn *)ADDRESS_GPIO_A;
GPIOn *gpio_B_SPI = (GPIOn *)ADDRESS_GPIO_B;
GPIOn *gpio_C_SPI = (GPIOn *)ADDRESS_GPIO_C;

/**
*******************************************************************************
* @ Name : SPI_ConfigGPIOPinForSPI
* @ Parameters: SPIn *spi_n
* @ Registers :
* @ Descriptions :
*		- Config GPIO for SPI pin:
*           . NSS pin -> OUTPUT PUSH/PULL
*           . MISO, MOSI, CLK pin -> Altemate
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-04
*******************************************************************************
*/
void SPI_ConfigGPIOPinForSPI(SPIn * spi_n)
{
    if (spi_n == (SPIn *)ADDRESS_SPI_1)
    {
        RCC_EnablePeripheralClock(CLOCK_SPI1);
        RCC_EnablePeripheralClock(CLOCK_GPIO_A);
        // PA4 -> SPI1_NSS, PA5 -> SPI1_SCK, PA6 -> SPI1_MISO, PA7 -> SPI1_MOSI
        GPIO_Configuration(gpio_A_SPI, GPIO_PIN4, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_LOW, PUPDR_NOTHING);
        GPIO_Configuration(gpio_A_SPI, GPIO_PIN5, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
        GPIO_Configuration(gpio_A_SPI, GPIO_PIN6, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
        GPIO_Configuration(gpio_A_SPI, GPIO_PIN7, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);

        // GPIO_ConfigAlternateFunc(gpio_A_SPI, GPIO_PIN4, AF5);
        GPIO_ConfigAlternateFunc(gpio_A_SPI, GPIO_PIN5, AF5);
        GPIO_ConfigAlternateFunc(gpio_A_SPI, GPIO_PIN6, AF5);
        GPIO_ConfigAlternateFunc(gpio_A_SPI, GPIO_PIN7, AF5);
    }
    else if (spi_n == (SPIn *)ADDRESS_SPI_2)
    {
        RCC_EnablePeripheralClock(CLOCK_SPI2);
        RCC_EnablePeripheralClock(CLOCK_GPIO_B);
        // PB12 -> SPI2_NSS, PB13 -> SPI2_SCK, PB14 -> SPI2_MISO, PB15 -> SPI2_MOSI
        GPIO_Configuration(gpio_B_SPI, GPIO_PIN12, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_LOW, PUPDR_NOTHING);
        GPIO_Configuration(gpio_B_SPI, GPIO_PIN13, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
        GPIO_Configuration(gpio_B_SPI, GPIO_PIN14, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
        GPIO_Configuration(gpio_B_SPI, GPIO_PIN15, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);

        GPIO_ConfigAlternateFunc(gpio_B_SPI, GPIO_PIN12, AF5);
        GPIO_ConfigAlternateFunc(gpio_B_SPI, GPIO_PIN13, AF5);
        GPIO_ConfigAlternateFunc(gpio_B_SPI, GPIO_PIN14, AF5);
        GPIO_ConfigAlternateFunc(gpio_B_SPI, GPIO_PIN15, AF5);
    }
    else if (spi_n == (SPIn *)ADDRESS_SPI_3)
    {
        RCC_EnablePeripheralClock(CLOCK_SPI3);
        RCC_EnablePeripheralClock(CLOCK_GPIO_A);
        RCC_EnablePeripheralClock(CLOCK_GPIO_C);

        // PA15 -> SPI3_NSS, PC10 -> SPI3_SCK, PC11 -> SPI3_MISO, PC12 -> SPI3_MOSI
        GPIO_Configuration(gpio_A_SPI, GPIO_PIN15, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
        GPIO_Configuration(gpio_C_SPI, GPIO_PIN10, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
        GPIO_Configuration(gpio_C_SPI, GPIO_PIN11, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_PULLDOWN);
        GPIO_Configuration(gpio_C_SPI, GPIO_PIN12, MODER_ALTEMATE, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);

        GPIO_ConfigAlternateFunc(gpio_A_SPI, GPIO_PIN15, AF6);
        GPIO_ConfigAlternateFunc(gpio_C_SPI, GPIO_PIN10, AF6);
        GPIO_ConfigAlternateFunc(gpio_C_SPI, GPIO_PIN11, AF6);
        GPIO_ConfigAlternateFunc(gpio_C_SPI, GPIO_PIN12, AF6);
    }
}

/**
* @ Name : SPI_Configuration
* @ Parameters: SPIn *spi_n,uint8_t spi_mode, uint8_t sampling_type,
    uint8_t clock_prescaler, uint8_t data_read_fr, 
    uint8_t receive_mode, uint8_t data_fr, uint8_t slave_mode_type
* @ Registers :
* @ Descriptions :
*		- Config SPI mode:
*           + spin_n: SPI1 -> SPI3
*           + spi_mode: MASTER_MODE -> SLAVE_MODE
*           + sampling_tpe: SECOND_CLOCK_IDLE (CPHA: 1, CPOL : 1)
                            SECOND_CLOCK_NO_IDLE (CPHA: 1, CPOL: 0)
                            FIRST_CLOCK_IDLE    (CPHA: 0, CPOL: 1)
                            FIRST_CLOCK_NO_IDLE (CPHA: 0, CPOL: 0)
*           + clock_prescaler (Only for Master): BAUD_RATE_DIV_2/4/8/16/32/64/128/256
*           + data_read_fr: MSB_FIRST (Most Significant Bit), LSB (Least Significant Bit)
*           + receive_mode: FULL_DUPLEX_MODE, RECEIVE_ONLY_MODE
*           + data_fr: DATA_FRAME_8_BITS, DATA_FRAME_16_BITS
*           + slave_mode_type: SOFTWARE_SLAVE_SELECT, HARDWARE_SLAVE_SELECT
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-04
*******************************************************************************
*/

/*
    Procedure:
    1. Select mode for device is master of slave (if master -> need to config baudrate in CLK common port)
    2. Config GPIO mode for SPI pin (NSS pin should be configed as output Push/Pull), orthers is althemate type for (MISO, MOSI, CLK pin) 
    3. Config data frame type is 8-bits data or 16-bits.
    4. Config time of start getting data
    5. Config type of getting data from right side or left side (M from right, L from left)
    6. Config type of trigger slave select is software of hardware
    7. If you want select type of SPI is Texas -> Enable TI mode
*/
void SPI_Configuration(SPIn *spi_n,uint8_t spi_mode, uint8_t sampling_type,
    uint8_t clock_prescaler, uint8_t data_read_fr, 
    uint8_t receive_mode, uint8_t data_fr, uint8_t slave_mode_type)
{
    SPI_ConfigGPIOPinForSPI(spi_n);
    SET_MASTER_SELECT(spi_n, spi_mode);
    SET_DATA_FRAME(spi_n, data_fr);
    SET_SAMPLING_TYPE_WITH_CLOCK(spi_n, sampling_type);
    SET_FRAME_FORMAT(spi_n, data_read_fr);

    if(spi_mode!= SLAVE_MODE)      // Slave mode, clock is provided from master
        SET_CLOCK_DIVIDER(spi_n, clock_prescaler);

    if(slave_mode_type == SOFTWARE_SLAVE_SELECT)
        SET_SOFTWARE_SLAVE_MANAGEMENT(spi_n);
    else if(slave_mode_type == HARDWARE_SLAVE_SELECT)
        SET_ENABLE_HARDWARE_NSS(spi_n);
    else if (slave_mode_type == NOTHING)
    {
        // nothing
    }
    SET_RECEIVE_MODE(spi_n, receive_mode);
    ENABLE_SPI(spi_n);
}

/**
*******************************************************************************
* @ Name : SPI_SlaveSelect
* @ Parameters: SPIn *spi_n, uint8_t slave_select_type
* @ Registers :
* @ Descriptions :
*		- Config Select slave mode: Drive NSS pin to Low
*           + spin_n: SPI1 -> SPI3
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-04
*******************************************************************************
*/
void SPI_SlaveSelect(SPIn *spi_n) // state: 1 - select, 0 - deselect
{
    if (spi_n == (SPIn *)ADDRESS_SPI_1)
        GPIO_SettingOutputDataBSRR(gpio_A_SPI, GPIO_PIN4, CLEAR);
    else if (spi_n == (SPIn *)ADDRESS_SPI_2)
        GPIO_SettingOutputDataBSRR(gpio_B_SPI, GPIO_PIN12, CLEAR);
    else if (spi_n == (SPIn *)ADDRESS_SPI_3)
        GPIO_SettingOutputDataBSRR(gpio_A_SPI, GPIO_PIN15, CLEAR);
}

/**
*******************************************************************************
* @ Name : SPI_SlaveDisSelect
* @ Parameters: SPIn *spi_n
* @ Registers :
* @ Descriptions :
*		- Dis-select Slave by setting high signal on NSS pin
*           + spin_n: SPI1 -> SPI3
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-05
*******************************************************************************
*/
void SPI_SlaveDisSelect(SPIn *spi_n)
{
    if (spi_n == (SPIn *)ADDRESS_SPI_1)
        GPIO_SettingOutputDataBSRR(gpio_A_SPI, GPIO_PIN4, SET);
    else if (spi_n == (SPIn *)ADDRESS_SPI_2)
        GPIO_SettingOutputDataBSRR(gpio_B_SPI, GPIO_PIN12, SET);
    else if (spi_n == (SPIn *)ADDRESS_SPI_3)
        GPIO_SettingOutputDataBSRR(gpio_A_SPI, GPIO_PIN15, SET);
}

/**
*******************************************************************************
* @ Name : SPI_Transmiter
* @ Parameters: SPIn *spi_n, uint8_t *pData, uint8_t Size
* @ Registers :
* @ Descriptions :
*		- Sequence to transmit data: the transmit sequence will be started after Slave recevied Clock follow sampling_tpe and first bit will come from MOSI pin:
*   /// Clock + First bit received -> remain bit is loaded to shift-register -> TXE flag is set -> interupt enable (TXEIE is set)
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-04
*******************************************************************************
*/
void SPI_Transmiter(SPIn *spi_n, uint8_t *pData, uint8_t Size)
{
/************** STEPS TO FOLLOW *****************
1. Wait for the TXE bit to set in the Status Register
2. Write the data to the Data Register
3. After the data has been transmitted, wait for the BSY bit to reset in Status Register
4. Clear the Overrun flag by reading DR and SR
************************************************/		

    // ENABLE_SPI(spi_n);  // When need to send data -> enable SPI, if not the program maybe will be stuck in SPI communication
    uint16_t data_send;
    while (Size > 0)
    {
        Size--;
        while (!(SPI_GET_TX_BUFFER_EMPTY_FLAG_STATUS(spi_n))){}; // wait for TXE = 1, not empty
        data_send = (*pData++ & (uint8_t)0xFF);
        SPI_SET_DATA_REGISTER(spi_n, data_send);

    }

	while (SPI_GET_BUSY_FLAG_STATUS(spi_n)) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	

	//  Clear the Overrun flag by reading DR and SR
	uint8_t temp = spi_n->DR;
			temp = spi_n->SR;
    // DISABLE_SPI(spi_n);
}

/**
*******************************************************************************
* @ Name : SPI_ReceiveData
* @ Parameters: SPIn *spi_n, uint8_t *pData, uint8_t Size
* @ Registers :
* @ Descriptions :
*		- Sequence to receive data: 
*   /// After data transmit is complete -> Data from shift load to RX buffer -> RXNE flag is set -> load data recevied to DR register -> clear RXNE flag
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-04
*******************************************************************************
*/
void SPI_ReceiveData(SPIn *spi_n, uint8_t *pData, uint8_t Size)
{
/************** STEPS TO FOLLOW *****************
1. Wait for the BSY bit to reset in Status Register
2. Send some Dummy data before reading the DATA
3. Wait for the RXNE bit to Set in the status Register
4. Read data from Data Register
************************************************/		

    while (Size)
    {
        while (SPI_GET_BUSY_FLAG_STATUS(spi_n)){};      // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication
        SPI_SET_DATA_REGISTER(spi_n, 0); // send dummy data
        while (!SPI_GET_RX_BUFFER_NOT_EMPTY_FLAG_STATUS(spi_n)){}; // Wait for RXNE to set -> This will indicate that the Rx buffer is not empty
        *pData++ = SPI_GET_DATA_REGISTER(spi_n);
        Size--;
    }
}

void SPI_TransmitDataInterruptEnable(SPIn *spi_n)
{
    ENABLE_TX_BUFFER_NOT_EMPTY_INTERRUPT(spi_n);
}

void SPI_ReceiverDataInterruptEnable(SPIn *spi_n)
{
    ENABLE_RX_BUFFER_NOT_EMPTY_INTERRUPT(spi_n);
}

