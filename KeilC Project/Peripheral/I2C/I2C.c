/**
 * @file I2C.c
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Configuration for I2C (Inter-Integrated Circuit) of STM32F407VGTx (ARMCortex M4)
 * @date 2025-03-07
 *
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/

#include "I2C.h"
#include "../RCC/RCC.h"
#include "../GPIO/GPIO.h"

/******************************************************************************
 * Variables definition
 ******************************************************************************/

I2C *_I2C1 = (I2C*)ADDRESS_I2C1; // 0x40005400
I2C *_I2C2 = (I2C*)ADDRESS_I2C2; // 0x40005800
I2C *_I2C3 = (I2C*)ADDRESS_I2C3; // 0x40005C00

GPIOn *gpioB_i2c = (GPIOn*)ADDRESS_GPIO_B;
GPIOn *gpioH_i2c = (GPIOn*)ADDRESS_GPIO_H;

/**
*******************************************************************************
* @ Name : I2C_ConfigGPIOPin
* @ Parameters: I2C* i2c_x
* @ Registers : GPIO registers
* @ Descriptions :
*		- Config GPIO for i2C pin (SCL, SDA pin):
*           . SCL: moder althmate, output type open-drain, high speed, pull-up
*           . SDA: moder althmate, output type open-drain, high speed, pull-up
*           + I2C1: PB6-> I2C1_SCL, PB7->I2C1_SDA, AF4
*           + I2C2: PB10->I2C2_SCL, PB11->I2C2_SDA, AF4
*           + I2C3: PH7->I2C3_SCL, PH8->I2C3_SDA, AF4
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-07
*******************************************************************************
*/
void I2C_ConfigGPIOPin(I2C* i2c_x)
{
    if(i2c_x == _I2C1)
    {
        RCC_EnablePeripheralClock(CLOCK_I2C1);
        RCC_EnablePeripheralClock(CLOCK_GPIO_B);

        // PB6-> I2C1_SCL, PB7->I2C1_SDA
        GPIO_Configuration(gpioB_i2c, GPIO_PIN6, MODER_ALTEMATE, OTYPER_OPENDRAIN, OSPEEDR_HIGH, PUPDR_PULLUP);
        GPIO_Configuration(gpioB_i2c, GPIO_PIN7, MODER_ALTEMATE, OTYPER_OPENDRAIN, OSPEEDR_HIGH, PUPDR_PULLUP);
    
        GPIO_ConfigAlternateFunc(gpioB_i2c, GPIO_PIN6, AF4);
        GPIO_ConfigAlternateFunc(gpioB_i2c, GPIO_PIN7, AF4);
    }
    else if(i2c_x == _I2C2)
    {
        RCC_EnablePeripheralClock(CLOCK_I2C2);
        RCC_EnablePeripheralClock(CLOCK_GPIO_B);
        // PB10->I2C2_SCL, PB11->I2C2_SDA
        GPIO_Configuration(gpioB_i2c, GPIO_PIN10, MODER_ALTEMATE, OTYPER_OPENDRAIN, OSPEEDR_HIGH, PUPDR_PULLUP);
        GPIO_Configuration(gpioB_i2c, GPIO_PIN11, MODER_ALTEMATE, OTYPER_OPENDRAIN, OSPEEDR_HIGH, PUPDR_PULLUP);
    
        GPIO_ConfigAlternateFunc(gpioB_i2c, GPIO_PIN10, AF4);
        GPIO_ConfigAlternateFunc(gpioB_i2c, GPIO_PIN11, AF4);
    }
    else if(i2c_x == _I2C3)
    {
        RCC_EnablePeripheralClock(CLOCK_I2C3);
        RCC_EnablePeripheralClock(CLOCK_GPIO_H);

        // PH7->I2C3_SCL, PH8->I2C3_SDA
        GPIO_Configuration(gpioH_i2c, GPIO_PIN7, MODER_ALTEMATE, OTYPER_OPENDRAIN, OSPEEDR_HIGH, PUPDR_PULLUP);
        GPIO_Configuration(gpioH_i2c, GPIO_PIN8, MODER_ALTEMATE, OTYPER_OPENDRAIN, OSPEEDR_HIGH, PUPDR_PULLUP);

        GPIO_ConfigAlternateFunc(gpioH_i2c, GPIO_PIN7, AF4);
        GPIO_ConfigAlternateFunc(gpioH_i2c, GPIO_PIN8, AF4);
    }
}

/**
*******************************************************************************
* @ Name : I2C_ClockPeripheralConfig
* @ Parameters: I2C* i2c_x, uint32_t peripheral_clock
* @ Registers : CR2
* @ Descriptions :
*		- Config Peripheral clock use for I2C from Bus APB1: (maximum 36MHz)
*       -> peripheral_clock: 6,8,9,12,16,18,24,28,36
*       ** Note: config I2C clock base on APB1 bus
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-07
*******************************************************************************
*/
void I2C_ClockPeripheralConfig(I2C* i2c_x)
{
#if defined(USE_APB1CLK_36MHz)
    FREQ_I2C(i2c_x, I2C_CLOCK_36MHZ);
#elif defined(USE_APB1CLK_28MHz)
    FREQ_I2C(i2c_x, I2C_CLOCK_28MHZ);
#elif defined (USE_APB1CLK_24MHz)
    FREQ_I2C(i2c_x, I2C_CLOCK_24MHZ);
#elif defined(USE_APB1CLK_18MHz)
    FREQ_I2C(i2c_x, I2C_CLOCK_18MHZ);
#elif defined(USE_APB1CLK_16MHz)
    FREQ_I2C(i2c_x, I2C_CLOCK_16MHZ);
#elif defined(USE_APB1CLK_12MHz) 
    FREQ_I2C(i2c_x, I2C_CLOCK_12MHZ);
#elif defined(USE_APB1CLK_9MHz) 
    FREQ_I2C(i2c_x, I2C_CLOCK_9MHZ);
#elif defined(USE_APB1CLK_8MHz) 
    FREQ_I2C(i2c_x, I2C_CLOCK_8MHZ);
#elif defined(USE_APB1CLK_6MHz)
    FREQ_I2C(i2c_x, I2C_CLOCK_6MHZ);
#endif

}

/**
*******************************************************************************
* @ Name : I2C_ConfigI2CClock
* @ Parameters: I2C* i2c_x, uint8_t i2c_mode, uint32_t peripheral_clock, uint8_t scl_clock, uint8_t duty_type
* @ Registers : CCR, TRIST
* @ Descriptions :  Config I2C clock using in clock pin base on device (config i2c mode, expected i2c clock and duty type)
                    Config maximum time rise of clock from low to high to make sure data can be write/read
                    ** peripheral_clock: clock on bus APB1
                    ** scl_clock: speed of communication on the bus I2C (SCL) in Hz
                - Standard mode: Tlow = Thigh
                    CCR = (peripheral_clock / (2 * scl_clock))
                    TRISE = (peripheral_clock / 1,000,000) + 1
                        baudrate max = 100kHz
                - Fast mode:
                    .Duty = 0: Tlow = 2*Thigh
                        CCR = (peripheral_clock / (3 * scl_clock))
                        TRISE = (peripheral_clock / 1,000,000) * 300 / 1000 + 1
                    .Duty = 1 (16/9): Tlow = 16/9 * Thigh
                        CCR = (peripheral_clock / (1 + 16/9 * scl_clock))))
                        baudrate max = 400kHz
                - i2c_mode: I2C_STANDARD_MODE, I2C_FAST_MODE
                - peripheral_clock:  6,8,9,12,16,18,24,28,36
                - duty_type: I2C_DUTY_2_1, I2C_DUTY_16_9
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-07
*******************************************************************************
*/
void I2C_ConfigI2CClock(I2C* i2c_x, uint8_t i2c_mode, uint32_t peripheral_clock, uint32_t scl_clock, uint8_t duty_type)
{
    uint16_t ccr_value = 0;
    uint16_t trise_value = 0;


    I2C_ClockPeripheralConfig(i2c_x); // set clock speed in bus APB1

    if(i2c_mode == I2C_STANDARD_MODE)
    {
        I2C_SET_STD_MODE(i2c_x);
        ccr_value = (uint16_t)(peripheral_clock / (2 * scl_clock));
        trise_value = (uint16_t)((peripheral_clock / 1000000) + 1);
    }
    else if (i2c_mode == I2C_FAST_MODE)
    {
        I2C_SET_FST_MODE(i2c_x); // set fast mode
        trise_value = (uint16_t)((peripheral_clock * 3 / 10000000) + 1);
        if(duty_type == I2C_DUTY_2_1)
        {
            I2C_DUTY(i2c_x, I2C_DUTY_2_1); // set duty cycle type 2
            ccr_value = (uint16_t)(peripheral_clock / (3 * scl_clock));
        }
        else if(duty_type == I2C_DUTY_16_9)
        {
            I2C_DUTY(i2c_x, I2C_DUTY_16_9); // set duty cycle type 16/9
            ccr_value = (uint16_t)(peripheral_clock / ((1 + 16/9) * scl_clock));
        }
    }

    I2C_CCR(i2c_x, ccr_value); // set CCR value
    I2C_TRISE(i2c_x, trise_value);
}

/**
*******************************************************************************
* @ Name : I2C_Configuration
* @ Parameters: I2C *i2c_x ,uint8_t i2c_mode, uint32_t peripheral_clock, uint8_t scl_clock, uint8_t duty_type
* @ Registers : 
* @ Descriptions :
*		- Config I2C (Config GPIO, Clock,...)
        **** STEPS FOLLOWED  ************
        1. Enable the I2C CLOCK and GPIO CLOCK
        2. Configure the I2C PINs for ALternate Functions
        3. Reset the I2C 	
        4. Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
        5. Configure the clock control registers
        6. Configure the rise time register
        7. Program the I2C_CR1 register to enable the peripheral
    - i2c_mode: I2C_STANDARD_MODE, I2C_FAST_MODE
    - peripheral_clock:  6,8,9,12,16,18,24,28,36
    - duty_type: I2C_DUTY_2_1, I2C_DUTY_16_9 
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-07
*******************************************************************************
*/
void I2C_Configuration(I2C *i2c_x ,uint8_t i2c_mode, uint32_t peripheral_clock, uint32_t scl_clock, uint8_t duty_type)
{
    I2C_ConfigGPIOPin(i2c_x);
    // Set and reset SWRST bit to clear all configuration of I2C first and re-config.
    SWRST_I2C(i2c_x);
    SWRST_RESET_I2C(i2c_x);

    I2C_ConfigI2CClock(i2c_x, i2c_mode, peripheral_clock, scl_clock, duty_type); // set clock speed on SCL line include config clock in bus)
    ENABLE_I2C(i2c_x);
}

/**
*******************************************************************************
* @ Name : I2C_Start
* @ Parameters: I2C* i2c_x
* @ Registers : CR1, SR1
* @ Descriptions :
*		- Start I2C communication
    **** STEPS FOLLOWED  ************
    1. Send the START condition 
    2. Wait for the SB ( Bit 0 in SR1) to set. This indicates that the start condition is generated
    3. Enable the ACK	
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-07
*******************************************************************************
*/
void I2C_Start(I2C *i2c_x)
{
    START_I2C(i2c_x);
    while(!(GET_I2C_START_GENERATED(i2c_x))){};
    CLEAR_I2C_START_GENERATED(i2c_x);
    // ACK_ENABLE_I2C(i2c_x);
}

/**
*******************************************************************************
* @ Name : I2C_WriteAddress
* @ Parameters: I2C *i2c_x, uint16_t slave_address, uint8_t ReadWrite
* @ Registers : DR, SR1
* @ Descriptions :
*		- Write slave address via SDA pin + ACK = Address + '0' and wait to address matched
    **** STEPS FOLLOWED  ************
    1. Send the Slave Address to the DR Register
    2. Wait for the ADDR (bit 1 in SR1) to set. This indicates the end of address transmission
    3. clear the ADDR by reading the SR1 and SR2
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-07
*******************************************************************************
*/
void I2C_WriteAddress(I2C *i2c_x, uint16_t slave_address)
{
    SET_I2C_DATA_TRANSMIT_ADDRESS(i2c_x, slave_address);

    while(!(GET_I2C_SLAVE_ADDRESS_MATCHED(i2c_x))){};
    CLEAR_I2C_SLAVE_ADDRESS_MATCHED(i2c_x);
}

/**
*******************************************************************************
* @ Name : I2C_WriteData
* @ Parameters: I2C *i2c_x, uint16_t data
* @ Registers : DR, SR1
* @ Descriptions :
*		- Wait TxE set + write data via SDA pin + wait to BTF bit set
    **** STEPS FOLLOWED  ************
    1. Wait for the TXE (bit 7 in SR1) to set. This indicates that the DR is empty
    2. Send the DATA to the DR Register
    3. Wait for the BTF (bit 2 in SR1) to set. This indicates the end of LAST DATA transmission
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-07
*******************************************************************************
*/
void I2C_WriteData(I2C *i2c_x, uint16_t data)
{
    while(!(GET_I2C_GET_DATA_TRANSMIT_REGISTER_EMPTY(i2c_x))){};
    SET_I2C_DATA_TRANSMIT(i2c_x, data);
    while(!(GET_I2C_DATA_TRANSMITTED(i2c_x))){};
}

/**
*******************************************************************************
* @ Name : I2C_ReadData
* @ Parameters: I2C *i2c_x
* @ Registers : DR, SR1
* @ Descriptions :
*		- Wait RXNE set + get data in SDA pin by DR register
    **** STEPS FOLLOWED  ************
    1. Wait for the RXNE (bit 6 in SR1) to set. This indicates that the DR is empty
    2. Read the DATA in the DR Register
* @ Return value : uint8_t
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-07
*******************************************************************************
*/
uint8_t I2C_ReadData(I2C *i2c_x)
{
    while(!(GET_I2C_GET_DATA_RECEIVE_REGISTER_EMPTY(i2c_x))){};
		return	GET_I2C_DATA(i2c_x);
}

/**
*******************************************************************************
* @ Name : I2C_ReceiveData
* @ Parameters: I2C *i2c_x, uint8_t slave_address, uint8_t NumOfBytes
* @ Registers : DR, SR1
* @ Descriptions :
*		- Wait RXNE set + get data in SDA pin by DR register
    **** STEPS FOLLOWED  ************
    1. Send slave address + recevie bit (0) and wait to slave address matching
    2. With byte not lastest (lenght -1) -> wait RXNE set and get data -> send ACK
    3. Lastest -> wait RXNE set and get data -> send NACK -> STOP I2C
        - NumOfBytes: Number of byte want to read
* @ Return value : uint8_t
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-07
*******************************************************************************
*/
void I2C_ReceiveData(I2C *i2c_x, uint8_t slave_address, uint8_t NumOfBytes)
{
    uint16_t data_buffer[NumOfBytes];
	uint8_t i;

    I2C_Start(i2c_x);
    I2C_WriteAddress(i2c_x, slave_address);

    for (i = 0; i < NumOfBytes - 1; i++)
    {
        data_buffer[i] = I2C_ReadData(i2c_x);
        ACK_ENABLE_I2C(i2c_x);
    }

    data_buffer[NumOfBytes - 1] = I2C_ReadData(i2c_x);
    ACK_DISABLE_I2C(i2c_x);

    // STOP_I2C(i2c_x);    
}

/**
*******************************************************************************
* @ Name : I2C_TransmitData
* @ Parameters: I2C *i2c_x, uint8_t slave_address, uint8_t *data, uint8_t NumOfBytes
* @ Registers : DR, SR1
* @ Descriptions :
    **** STEPS FOLLOWED  ************
    1. Send slave address + recevie bit (1) and wait to slave address matching
    2. Wait TxE set and send data
    3. STOP I2C
        - NumOfBytes: Number of byte want to write
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-03-07
*******************************************************************************
*/
void I2C_TransmitData(I2C *i2c_x, uint8_t slave_address, uint8_t *data, uint8_t NumOfBytes)
{
	uint8_t i;
    I2C_Start(i2c_x);
    I2C_WriteAddress(i2c_x, slave_address);

    for (i = 0; i < NumOfBytes; i++)
    {
        I2C_WriteData(i2c_x, data[i]);
    }
    // STOP_I2C(i2c_x);
}


