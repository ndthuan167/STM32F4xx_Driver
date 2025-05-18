/**
 * @file ADC.c
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Configuration for ADC of STM32F4xx (ARMCortex M4)
 * @date 2025-05-15
 *
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/

#include "ADC.h"
#include "../RCC/RCC.h"
#include "../GPIO/GPIO.h"

/******************************************************************************
 * Variables definition
 ******************************************************************************/

ADCx *adc1 = (ADCx *)ADDRESS_ADC_1;
ADCx *adc2 = (ADCx *)ADDRESS_ADC_2;
ADCx *adc3 = (ADCx *)ADDRESS_ADC_3;

ADC_Common* adc_cmm = (ADC_Common*) ADDRESS_ADC_COMMON;

GPIOn *gp_a = (GPIOn *)ADDRESS_GPIO_A;
GPIOn *gp_b = (GPIOn *)ADDRESS_GPIO_B;
GPIOn *gp_c = (GPIOn *)ADDRESS_GPIO_C;
GPIOn *gp_f = (GPIOn *)ADDRESS_GPIO_F;

uint8_t index_sq;

typedef struct
{
    uint32_t GPIOx;
    uint8_t GPIO_Pin;
} ADC_GPIO;

ADC_GPIO ADCx_CHy[3][16] =
    {
        {
            {ADDRESS_GPIO_A, GPIO_PIN0},    // CH0
            {ADDRESS_GPIO_A, GPIO_PIN1},    // CH1
            {ADDRESS_GPIO_A, GPIO_PIN2},    // CH2
            {ADDRESS_GPIO_A, GPIO_PIN3},    // CH3
            {ADDRESS_GPIO_A, GPIO_PIN4},    // CH4
            {ADDRESS_GPIO_A, GPIO_PIN5},    // CH5
            {ADDRESS_GPIO_A, GPIO_PIN6},    // CH6
            {ADDRESS_GPIO_A, GPIO_PIN7},    // CH7
            {ADDRESS_GPIO_B, GPIO_PIN0},    // CH8
            {ADDRESS_GPIO_B, GPIO_PIN1},    // CH9
            {ADDRESS_GPIO_C, GPIO_PIN0},    // CH10
            {ADDRESS_GPIO_C, GPIO_PIN1},    // CH11
            {ADDRESS_GPIO_C, GPIO_PIN2},    // CH12
            {ADDRESS_GPIO_C, GPIO_PIN3},    // CH13
            {ADDRESS_GPIO_C, GPIO_PIN4},    // CH14
            {ADDRESS_GPIO_C, GPIO_PIN5},    // CH15
        }, // ADC1
        {
            {ADDRESS_GPIO_A, GPIO_PIN0},    // CH0
            {ADDRESS_GPIO_A, GPIO_PIN1},    // CH1
            {ADDRESS_GPIO_A, GPIO_PIN2},    // CH2
            {ADDRESS_GPIO_A, GPIO_PIN3},    // CH3
            {ADDRESS_GPIO_A, GPIO_PIN4},    // CH4
            {ADDRESS_GPIO_A, GPIO_PIN5},    // CH5
            {ADDRESS_GPIO_A, GPIO_PIN6},    // CH6
            {ADDRESS_GPIO_A, GPIO_PIN7},    // CH7
            {ADDRESS_GPIO_B, GPIO_PIN0},    // CH8
            {ADDRESS_GPIO_B, GPIO_PIN1},    // CH9
            {ADDRESS_GPIO_C, GPIO_PIN0},    // CH10
            {ADDRESS_GPIO_C, GPIO_PIN1},    // CH11
            {ADDRESS_GPIO_C, GPIO_PIN2},    // CH12
            {ADDRESS_GPIO_C, GPIO_PIN3},    // CH13
            {ADDRESS_GPIO_C, GPIO_PIN4},    // CH14
            {ADDRESS_GPIO_C, GPIO_PIN5},    // CH15
        }, // ADC2
        {
            {ADDRESS_GPIO_A, GPIO_PIN0},    // CH0
            {ADDRESS_GPIO_A, GPIO_PIN1},    // CH1
            {ADDRESS_GPIO_A, GPIO_PIN2},    // CH2
            {ADDRESS_GPIO_A, GPIO_PIN3},    // CH3
            {ADDRESS_GPIO_F, GPIO_PIN6},    // CH4
            {ADDRESS_GPIO_F, GPIO_PIN7},    // CH5
            {ADDRESS_GPIO_F, GPIO_PIN8},    // CH6
            {ADDRESS_GPIO_F, GPIO_PIN9},    // CH7
            {ADDRESS_GPIO_F, GPIO_PIN10},    // CH8
            {ADDRESS_GPIO_F, GPIO_PIN3},    // CH9
            {ADDRESS_GPIO_C, GPIO_PIN0},    // CH10
            {ADDRESS_GPIO_C, GPIO_PIN1},    // CH11
            {ADDRESS_GPIO_C, GPIO_PIN2},    // CH12
            {ADDRESS_GPIO_C, GPIO_PIN3},    // CH13
            {ADDRESS_GPIO_F, GPIO_PIN4},    // CH14
            {ADDRESS_GPIO_F, GPIO_PIN5},    // CH15
        }, // ADC3
};

/**
*******************************************************************************
* @ Name : ADC_GPIOConfig
* @ Parameters: ADCx *ADC_x, uint8_t Chanelx
* @ Registers :
* @ Descriptions : Enable Clock for ADCx,GPIOx and Config GPIO pin for ADC base on ADCx and Chanelx.
*                + GPIO mode: MODER_ANALOG
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-15
*******************************************************************************
*/
void ADC_GPIOConfig(ADCx *ADC_x, uint8_t Chanelx)
{
    if (ADC_x == adc1)
    {
        RCC_EnablePeripheralClock(CLOCK_ADC1);

        ADC_GPIO adc_gp1 = ADCx_CHy[0][Chanelx];
        if ((GPIOn *)adc_gp1.GPIOx == gp_a)
            RCC_EnablePeripheralClock(CLOCK_GPIO_A);
        else if ((GPIOn *)adc_gp1.GPIOx == gp_b)
            RCC_EnablePeripheralClock(CLOCK_GPIO_B);
        else if ((GPIOn *)adc_gp1.GPIOx == gp_c)
            RCC_EnablePeripheralClock(CLOCK_GPIO_C);

        GPIO_Configuration((GPIOn *)adc_gp1.GPIOx, adc_gp1.GPIO_Pin, MODER_ANALOG, OTYPER_PUSHPULL, OSPEEDR_LOW, PUPDR_NOTHING);
    }
    else if (ADC_x == adc2)
    {
        RCC_EnablePeripheralClock(CLOCK_ADC2);

        ADC_GPIO adc_gp2 = ADCx_CHy[1][Chanelx];

        if ((GPIOn *)adc_gp2.GPIOx == gp_a)
            RCC_EnablePeripheralClock(CLOCK_GPIO_A);
        else if ((GPIOn *)adc_gp2.GPIOx == gp_b)
            RCC_EnablePeripheralClock(CLOCK_GPIO_B);
        else if ((GPIOn *)adc_gp2.GPIOx == gp_c)
            RCC_EnablePeripheralClock(CLOCK_GPIO_C);

        GPIO_Configuration((GPIOn *)adc_gp2.GPIOx, adc_gp2.GPIO_Pin, MODER_ANALOG, OTYPER_PUSHPULL, OSPEEDR_LOW, PUPDR_NOTHING);
    }
    else if (ADC_x == adc3)
    {
        RCC_EnablePeripheralClock(CLOCK_ADC3);

        ADC_GPIO adc_gp3 = ADCx_CHy[2][Chanelx];

        if ((GPIOn *)adc_gp3.GPIOx == gp_a)
            RCC_EnablePeripheralClock(CLOCK_GPIO_A);
        else if ((GPIOn *)adc_gp3.GPIOx == gp_c)
            RCC_EnablePeripheralClock(CLOCK_GPIO_C);
        else if ((GPIOn *)adc_gp3.GPIOx == gp_f)
            RCC_EnablePeripheralClock(CLOCK_GPIO_F);

        GPIO_Configuration((GPIOn *)adc_gp3.GPIOx, adc_gp3.GPIO_Pin, MODER_ANALOG, OTYPER_PUSHPULL, OSPEEDR_LOW, PUPDR_NOTHING);
    }
}

/**
*******************************************************************************
* @ Name : ADC_SetSequence
* @ Parameters: ADCx *ADC_x, uint8_t Sequence_index, uint8_t Channel
* @ Registers :
* @ Descriptions : base on Channel, set channel value into corresponding sequence register of ADCx.
*               + Channel 0 -> 5 => SQR3
*               + Channel 6 -> 11 => SQR2
*               + Channel 12 -> 15 => SQR1
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-15
*******************************************************************************
*/
void ADC_SetSequence(ADCx *ADC_x, uint8_t Sequence_index, uint8_t Channel)
{
    if(Sequence_index <= 5)
        ADC_SET_SEQUENCE_1(ADC_x, Channel << 5 * Sequence_index);
    else if(Sequence_index <= 11)
        ADC_SET_SEQUENCE_2(ADC_x, Channel << 5 * (Sequence_index - 6));
    else
        ADC_SET_SEQUENCE_3(ADC_x, Channel << 5 * (Sequence_index - 12));
}

/**
*******************************************************************************
* @ Name : ADC_Configuration
* @ Parameters: ADC_Variables ADC_val
* @ Registers :
* @ Descriptions : Configure ADC follow:
*  Value of arguments:
*                   + ADC_x : ADC1, ADC2, ADC3
*                   + prescaler_dix: ADC_CLK_DIV_2, ADC_CLK_DIV_4, ADC_CLK_DIV_6, ADC_CLK_DIV_8
*                   + resolution: ADC_RESOLUTION_12BIT, ADC_RESOLUTION_10BIT, ADC_RESOLUTION_8BIT, ADC_RESOLUTION_6BIT
*                   + eoc: EOC_END_OF_CONVERSION, EOC_END_OF_SEQUENCE
*                   + dma_stop_type: DMA_STOP_AT_LAST_CONVERSION, DMA_CONTINUE_AFTER_LAST_CONVERSION
*                   + data_align: DATA_RIGHT_ALIGNMENT, DATA_LEFT_ALIGNMENT
*                   + sequence_lenght: number of channels in sequence
*                   + channels: array of channels need to be converted(ADC_CH0 -> ADC_CH15)
*                   + sampling_time: ADC_SPLT_3_CYCLES, ADC_SPLT_15_CYCLES, ADC_SPLT_28_CYCLES, ADC_SPLT_56_CYCLES, ADC_SPLT_84_CYCLES, ADC_SPLT_112_CYCLES, ADC_SPLT_144_CYCLES, ADC_SPLT_480_CYCLES
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-15
*******************************************************************************
*/
void ADC_Configuration(ADC_Variables ADC_val)
{
/************** STEPS TO FOLLOW *****************
1. Configure GPIO for channels (1 or multi channels)
2. Set sequence of channels in ADC register
3. Set sampling time for each channel
4. Set prescaler to set clock frequency for ADC base on PCLK2 bus clock
5. Enable Scan mode and set resolution
6. Set conversion mode, DMA, Data alignment for ADC
7. Enable ADC
************************************************/		

    for(index_sq = 0; index_sq < ADC_val.sequence_length; index_sq++)
    {
        // Config GPIO pin as analog pin for ADC input channel
        ADC_GPIOConfig(ADC_val.ADC_n, ADC_val.channels[index_sq]);

        // Set sequence of channel in ADC register
        ADC_SetSequence(ADC_val.ADC_n, index_sq, ADC_val.channels[index_sq]);
        
        // Set sampling time
        ADC_SET_SAMPLING_TIME(ADC_val.ADC_n, ADC_val.channels[index_sq], ADC_val.sampling_time);
    }

    // Set prescaler to set clock frequency for ADC base on PCLK2 bus clock
    ADC_SET_CLK_PSL(adc_cmm, ADC_val.prescaler_div);

    // Enable Scan mode and set resolution
    ADC_ENABLE_SCAN_MODE(ADC_val.ADC_n);
    ADC_SET_RESOLUTION(ADC_val.ADC_n, ADC_val.resolution);

    // Set conversion mode, DMA, Data alignment for ADC
    ADC_ENABLE_CONTINUOUS_CONVERSION(ADC_val.ADC_n);
    ADC_SET_EOC_TYPE(ADC_val.ADC_n, ADC_val.eoc_type);
    ADC_USING_DMA(ADC_val.ADC_n);
    DMA_AFTER_CONVENSION(ADC_val.ADC_n, ADC_val.dma_stop_type);
    ADC_SET_DATA_ALIGNMENT(ADC_val.ADC_n, ADC_val.data_align);

    // Enable ADC
    ADC_ENABLE(ADC_val.ADC_n);

}


/**
*******************************************************************************
* @ Name : ADC_Start
* @ Parameters: ADCx *ADC_x
* @ Registers :
* @ Descriptions : Start ADC conversion.
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-15
*******************************************************************************
*/
void ADC_Start(ADCx * ADC_x)
{
    ADC_CLEAR_STATUS_REGISTER(ADC_x);
    ADC_START(ADC_x);
}

/**
*******************************************************************************
* @ Name : ADC_GetData
* @ Parameters: ADCx *ADC_x
* @ Registers :
* @ Descriptions : Get ADC conversion data by read DR register after start conversion and wait EOC bit in SR to 1.
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-15
*******************************************************************************
*/
uint16_t ADC_GetData(ADCx *ADC_x)
{
    // Start ADC conversion
    ADC_Start(ADC_x);

    // Waiting ADC conversion complete -> set ECO bit in SR to 1
    while(!(ADC_GET_CONVERSION_RESULT(ADC_x)));

    // Read data from DR register
    return ADC_GET_RESULT(ADC_x);
}

