/**
 * @file I2C.h
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Some declaration for I2C (Inter-Integrated Circuit) configuration of STM32F407VGTx (ARMCortex M4)
 * @date 2025-03-07
 *
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/


#include "stdio.h"
#include "stdint.h"

/*******************************************************************************
* I2C ADDRESS DEFINITION
*******************************************************************************/

#define ADDRESS_I2C1        0x40005400
#define ADDRESS_I2C2        0x40005800
#define ADDRESS_I2C3        0x40005C00

/*******************************************************************************
* I2C REGISTER STRUCTURE DEFINITION
*******************************************************************************/

typedef struct
{
    uint32_t CR1;         //Control Register 1
    uint32_t CR2;         //Control Register 2
    uint32_t OAR1;        //Own Address Register 1
    uint32_t OAR2;        //Own Address Register 2
    uint32_t DR;          //Data Register
    uint32_t SR1;         //Status Register 1
    uint32_t SR2;         //Status Register 2
    uint32_t CCR;         //Clock Control Register
    uint32_t TRISE;       //TRise Register
    uint32_t FLTR;        //FLTR Register
}I2C;

/*******************************************************************************
* DEFINITION
*******************************************************************************/

#define READ    0
#define WRITE   1

/*******************************************************************************
* CR1 REGISTERS DEFINITION
*******************************************************************************/

#define ENABLE_I2C(i2c)         i2c->CR1 |= (1 << 0)    // PE - Peripheral Enable
#define DISABLE_I2C(i2c)        i2c->CR1 &= ~(1 << 0)

#define START_I2C(i2c)          i2c->CR1 |= (1 << 8)    // START
#define STOP_I2C(i2c)           i2c->CR1 |= (1 << 9)

#define ACK_ENABLE_I2C(i2c)     i2c->CR1 |= (1 << 10)   // STOP
#define ACK_DISABLE_I2C(i2c)    i2c->CR1 &= ~(1 << 10)

#define POS_ENABLE_I2C(i2c)     i2c->CR1 |= (1 << 11)
#define POS_DISABLE_I2C(i2c)    i2c->CR1 &= ~(1 << 11)

#define SWRST_I2C(i2c)          i2c->CR1 |= (1 << 15)   // SWRST : Software Reset
#define SWRST_RESET_I2C(i2c)    i2c->CR1 &= ~(1 << 15)

/*******************************************************************************
* CR2 REGISTERS DEFINITION
*******************************************************************************/

// enum to config speed_clock (APB1 Bus)
enum
{
    I2C_CLOCK_6MHZ = 6,
    I2C_CLOCK_8MHZ = 8,
    I2C_CLOCK_9MHZ = 9,
    I2C_CLOCK_12MHZ = 12,
    I2C_CLOCK_16MHZ = 16,
    I2C_CLOCK_18MHZ = 18,
    I2C_CLOCK_24MHZ = 24,
    I2C_CLOCK_28MHZ = 28,
    I2C_CLOCK_36MHZ = 36,
};

#define FREQ_I2C(i2c, value)    i2c->CR2 |=  (value << 0)   // FREQ[6bits]

/*******************************************************************************
* CCR REGISTERS DEFINITION
*******************************************************************************/

enum
{
    I2C_STANDARD_MODE,
    I2C_FAST_MODE,
    I2C_FAST_MODE_PLUS,
};

#define I2C_SET_STD_MODE(i2c)     i2c->CCR &= ~(1 << 15)    // F/S mode (Standard mode)
#define I2C_SET_FST_MODE(i2c)     i2c->CCR |= (1 << 15)     // Fastmode

// Config DUTY only for Fastmode

enum
{
    I2C_DUTY_2_1,
    I2C_DUTY_16_9,
};

#define I2C_DUTY(i2c, duty)           i2c->CCR |= (duty << 14)  // DUTY bit

#define I2C_CCR(i2c, value)           i2c->CCR |= (value << 0)  // CCR value

/*******************************************************************************
* TRISE REGISTERS DEFINITION
*******************************************************************************/
// Time rise
#define I2C_TRISE(i2c, trise)         i2c->TRISE = trise    // TRISE: Time rise maximum value


/*******************************************************************************
* SR1 REGISTERS DEFINITION
*******************************************************************************/

#define GET_I2C_START_GENERATED(i2c)            i2c->SR1 & (1 << 0)     // SB
#define CLEAR_I2C_START_GENERATED(i2c)          i2c->SR1 &= ~(1 << 0)

#define GET_I2C_SLAVE_ADDRESS_MATCHED(i2c)      i2c->SR1 & (1 << 1)     // ADDR
#define CLEAR_I2C_SLAVE_ADDRESS_MATCHED(i2c)    i2c->SR1 &= ~(1 << 1)

#define GET_I2C_GET_DATA_RECEIVE_REGISTER_EMPTY(i2c)     i2c->SR1 & (1 << 6)    // RXNE
#define GET_I2C_GET_DATA_TRANSMIT_REGISTER_EMPTY(i2c)    i2c->SR1 & (1 << 7)     // TxE

#define GET_I2C_DATA_TRANSMITTED(i2c)           i2c->SR1 & (1 << 2) // BTF


#define SET_I2C_DATA_TRANSMIT_ADDRESS(i2c, data)    i2c->DR = data << 1
        
#define SET_I2C_DATA_TRANSMIT(i2c, data)        i2c->DR = data
#define GET_I2C_DATA(i2c)                       i2c->DR


void I2C_ConfigGPIOPin(I2C* i2c_x);
void I2C_ClockPeripheralConfig(I2C* i2c_x);
void I2C_ConfigI2CClock(I2C* i2c_x, uint8_t i2c_mode, uint32_t peripheral_clock, uint32_t scl_clock, uint8_t duty_type);
void I2C_Configuration(I2C *i2c_x ,uint8_t i2c_mode, uint32_t peripheral_clock, uint32_t scl_clock, uint8_t duty_type);
void I2C_Start(I2C *i2c_x);
void I2C_WriteAddress(I2C *i2c_x, uint16_t slave_address);
void I2C_WriteData(I2C *i2c_x, uint16_t data);
uint8_t I2C_ReadData(I2C *i2c_x);
void I2C_ReceiveData(I2C *i2c_x, uint8_t slave_address, uint8_t NumOfBytes);
void I2C_TransmitData(I2C *i2c_x, uint8_t slave_address, uint8_t *data, uint8_t NumOfBytes);


