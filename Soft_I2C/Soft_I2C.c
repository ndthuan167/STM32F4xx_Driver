#include "Soft_I2C.h"
#include "../GPIO/GPIO.h"
#include "../RCC/RCC.h"
#include "../Timer/Timer.h"

uint8_t clk_gen = 0;
uint8_t crr_clk_i2c = 0;
uint8_t pre_clk_i2c = 0;
uint8_t crr_clk_i2c_sc = 0;
uint8_t pre_clk_i2c_sc = 0;
uint8_t in;
uint8_t index_i2c = 1;
bool started_condition = false;
uint8_t index_arr = 0;

GPIOn *gpioB_S_i2c = (GPIOn *)ADDRESS_GPIO_B; // GPIO port B for I2C1/2
GPIOn *gpioH_S_i2c = (GPIOn *)ADDRESS_GPIO_H; // GPIO port H for I2C3


void SoftI2C_GPIOConfiguration(uint8_t I2Cx, uint8_t modeRW)
{
    switch (I2Cx)
    {
        case I2C_1:
            RCC_EnablePeripheralClock(CLOCK_GPIO_B);
            GPIO_Configuration(gpioB_S_i2c, GPIO_PIN6, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_NOTHING);
            if (modeRW == I2C_MODE_WRITE)
                GPIO_Configuration(gpioB_S_i2c, GPIO_PIN7, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_NOTHING);
            else if (modeRW == I2C_MODE_READ)
                GPIO_Configuration(gpioB_S_i2c, GPIO_PIN7, MODER_INPUT, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_NOTHING);
            break;
        case I2C_2:
            RCC_EnablePeripheralClock(CLOCK_GPIO_B);
            GPIO_Configuration(gpioB_S_i2c, GPIO_PIN10, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_NOTHING);
            if (modeRW == I2C_MODE_WRITE)
                GPIO_Configuration(gpioB_S_i2c, GPIO_PIN11, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_NOTHING);
            else if (modeRW == I2C_MODE_READ)
                GPIO_Configuration(gpioB_S_i2c, GPIO_PIN11, MODER_INPUT, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_NOTHING);
            break;
        case I2C_3:
            RCC_EnablePeripheralClock(CLOCK_GPIO_H);
            GPIO_Configuration(gpioH_S_i2c, GPIO_PIN7, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_NOTHING);
            if (modeRW == I2C_MODE_WRITE)
                GPIO_Configuration(gpioH_S_i2c, GPIO_PIN8, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_NOTHING);
            else if (modeRW == I2C_MODE_READ)
                GPIO_Configuration(gpioH_S_i2c, GPIO_PIN8, MODER_INPUT, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_NOTHING);
            break;
        default:
            break;
    }
}

void SoftI2C_Init(uint8_t I2Cx)
{
    switch (I2Cx)
    {
    case I2C_1:
        GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN6, SET);
        GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN7, SET);
        break;
    case I2C_2:
        GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN10, SET);
        GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN11, SET);
        break;
    case I2C_3:
        GPIO_SettingOutputDataBSRR(gpioH_S_i2c, GPIO_PIN7, SET);
        GPIO_SettingOutputDataBSRR(gpioH_S_i2c, GPIO_PIN8, SET);
        break;
    default:
        break;
    }
}

void SoftI2C_Start(uint8_t I2Cx)
{
    switch (I2Cx)
    {
    case I2C_1:
        GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN6, CLEAR);
        GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN7, CLEAR);
        break;
    case I2C_2:
        GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN10, CLEAR);
        GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN11, CLEAR);
        break;
    case I2C_3:
        GPIO_SettingOutputDataBSRR(gpioH_S_i2c, GPIO_PIN7, CLEAR);
        GPIO_SettingOutputDataBSRR(gpioH_S_i2c, GPIO_PIN8, CLEAR);
        break;
    default:
        break;
    }
}

void SoftI2C_Stop(uint8_t I2Cx)
{
    SoftI2C_Init(I2Cx);
}

void SoftI2C_ClockGeneration(uint8_t I2Cx)
{
    // if(GetFlagTimer1ms())
    //     GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN6, SET);
    // if(GetFlagTimer1ms())
    //     GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN6, CLEAR);
        

    if (GetFlagTimer1ms())
    {
        clk_gen++;
        if (clk_gen % 2 == 0)
        {
            switch (I2Cx)
            {
            case I2C_1:
                GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN6, CLEAR);
                break;
            case I2C_2:
                GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN10, CLEAR);
                break;
            case I2C_3:
                GPIO_SettingOutputDataBSRR(gpioH_S_i2c, GPIO_PIN7, CLEAR);
                break;

            default:
                break;
            }
        }
        else
        {
            switch (I2Cx)
            {
            case I2C_1:
                GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN6, SET);
                break;
            case I2C_2:
                GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN10, SET);
                break;
            case I2C_3:
                GPIO_SettingOutputDataBSRR(gpioH_S_i2c, GPIO_PIN7, SET);
                break;

            default:
                break;
            }
        }
    }
}

void SoftI2C_Configuration(uint8_t I2Cx, uint8_t modeRW)
{
    SoftI2C_GPIOConfiguration(I2Cx, modeRW);
    SoftI2C_Init(I2Cx);
}

uint8_t SoftI2C_DetectRisingEdge(uint8_t I2Cx)
{
    uint8_t edge = NOTHING_EDGE;

    switch (I2Cx)
    {
    case I2C_1:
        crr_clk_i2c = GPIO_GetDataInOutputRes(gpioB_S_i2c, GPIO_PIN6);
        break;
    case I2C_2:
        crr_clk_i2c = GPIO_GetDataInOutputRes(gpioB_S_i2c, GPIO_PIN10);
        break;
    case I2C_3:
        crr_clk_i2c = GPIO_GetDataInOutputRes(gpioH_S_i2c, GPIO_PIN7);
        break;
    default:
        break;
    }

    if (crr_clk_i2c == 1 && pre_clk_i2c == 0)
        edge = RISING_EDGE;
    if (crr_clk_i2c == 0 && pre_clk_i2c == 1)
        edge = FALLING_EDGE;

    pre_clk_i2c = crr_clk_i2c;

    return edge;
}

uint8_t SoftI2C_DetecFallingEdgeForSecond(uint8_t I2Cx)
{
    uint8_t edge = NOTHING_EDGE;

    switch (I2Cx)
    {
    case I2C_1:
        crr_clk_i2c_sc = GPIO_GetDataInOutputRes(gpioB_S_i2c, GPIO_PIN6);
        break;
    case I2C_2:
        crr_clk_i2c_sc = GPIO_GetDataInOutputRes(gpioB_S_i2c, GPIO_PIN10);
        break;
    case I2C_3:
        crr_clk_i2c_sc = GPIO_GetDataInOutputRes(gpioH_S_i2c, GPIO_PIN7);
        break;
    default:
        break;
    }

    if (crr_clk_i2c_sc == 1 && pre_clk_i2c_sc == 0)
        edge = RISING_EDGE;
    if (crr_clk_i2c_sc == 0 && pre_clk_i2c_sc == 1)
        edge = FALLING_EDGE;

    pre_clk_i2c_sc = crr_clk_i2c_sc;

    return edge;
}

bool SoftI2C_GetStartCondition(uint8_t I2Cx)
{
    bool start_condition = false;

    switch (I2Cx)
    {
        case I2C_1:
            if ((GPIO_GetDataInOutputRes(gpioB_S_i2c, GPIO_PIN6) == 0) && (GPIO_GetDataInOutputRes(gpioB_S_i2c, GPIO_PIN7) == 0))
                start_condition = true;
            break;
        case I2C_2:
            if ((GPIO_GetDataInOutputRes(gpioB_S_i2c, GPIO_PIN10) == 0) && (GPIO_GetDataInOutputRes(gpioB_S_i2c, GPIO_PIN11) == 0))
                start_condition = true;
            break;
        case I2C_3:
            if ((GPIO_GetDataInOutputRes(gpioH_S_i2c, GPIO_PIN7) == 0) && (GPIO_GetDataInOutputRes(gpioH_S_i2c, GPIO_PIN8) == 0))
                start_condition = true;
            break;
        default:
            break;
    }

    return start_condition;
}

void HexToBinConvert(uint8_t hex, uint8_t *bin)
{
    int j;

    for (j = 7; j >= 0; j--)
    {
        if ((hex >> j) & 0x01)
            bin[7 - j] = '1';
        else
            bin[7 - j] = '0';
    }

    bin[8] = '\0'; // Null-terminate the binary string
}

bool SoftI2C_WriteByte(uint8_t I2Cx, uint8_t data)
{
    uint8_t bin[8];


    if (SoftI2C_GetStartCondition(I2Cx))
    {
        started_condition = true;
    }

    HexToBinConvert(data, bin);

    if(started_condition == true)
    {
        GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN4, SET);
        SoftI2C_ClockGeneration(I2Cx);
        for (in = 0; in < 50; in++) // Delay to send first bit
        {
        };

        if (bin[0] == 0x30)
            GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN7, CLEAR);
        else if (bin[0] == 0x31)
            GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN7, SET);

        if (SoftI2C_DetecFallingEdgeForSecond(I2Cx) == FALLING_EDGE)
        {
            if (bin[index_i2c] == 0x30)
                GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN7, CLEAR);
            else if (bin[index_i2c] == 0x31)
                GPIO_SettingOutputDataBSRR(gpioB_S_i2c, GPIO_PIN7, SET);
            index_i2c++;
        }

        // // if(GetFlagTimer1ms())
        // //     index_i2c++;

        // if(index_i2c >= 8)
        // {
        //     SoftI2C_Stop(I2C_1);
        //     return true;        
        // }
    }
		
		return false;
}

void SoftI2C_WriteData(uint8_t I2Cx, uint8_t* data, uint8_t size)
{
    if(SoftI2C_WriteByte(I2Cx, data[index_arr]))
    {
        index_i2c = 1;
        index_arr++;
    }

    if(index_arr > size)
    {
        SoftI2C_Stop(I2Cx);
        // index_arr = 0;
    }
}


