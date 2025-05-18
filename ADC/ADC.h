/**
 * @file ADC.h
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Some declaration for Analog Digital Converter (ADC) of STM32F4xx (ARMCortex M4)
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
* ADCx ADDRESS DEFINITION
*******************************************************************************/

#define ADDRESS_ADC_1   0x40012000
#define ADDRESS_ADC_2   0x40012100
#define ADDRESS_ADC_3   0x40012200

#define ADDRESS_ADC_COMMON   0x40012300

/*******************************************************************************
* ADC REGISTER STRUCTURE DEFINITION
*******************************************************************************/

typedef struct
{
    uint32_t SR;
    uint32_t CR1;
    uint32_t CR2;
    uint32_t SMPR1;
    uint32_t SMPR2;
    uint32_t JOFR1;
    uint32_t JOFR2;
    uint32_t JOFR3;
    uint32_t JOFR4;
    uint32_t HTR;
    uint32_t LTR;
    uint32_t SQR1;
    uint32_t SQR2;
    uint32_t SQR3;
    uint32_t JSQR;
    uint32_t JDR1;
    uint32_t JDR2;
    uint32_t JDR3;
    uint32_t JDR4;
    uint32_t DR;
} ADCx;

typedef struct
{
    uint32_t CSR;
    uint32_t CCR;
    uint32_t CDR;
} ADC_Common;

typedef struct
{
    ADCx* ADC_n;
    uint8_t prescaler_div;
    uint8_t resolution;
    uint8_t eoc_type;
    uint8_t dma_stop_type;
    uint8_t data_align;
    uint8_t sequence_length;
    uint8_t *channels;
    uint8_t sampling_time;
} ADC_Variables;

/*******************************************************************************
* ENUM DEFINITION
*******************************************************************************/

enum
{
    ADC_CH0,
    ADC_CH1,
    ADC_CH2,
    ADC_CH3,
    ADC_CH4,
    ADC_CH5,
    ADC_CH6,
    ADC_CH7,
    ADC_CH8,
    ADC_CH9,
    ADC_CH10,
    ADC_CH11,
    ADC_CH12,
    ADC_CH13,
    ADC_CH14,
    ADC_CH15,
};

// CCR common
// Setting prescaler
enum
{
    ADC_CLK_DIV_2,
    ADC_CLK_DIV_4,
    ADC_CLK_DIV_6,
    ADC_CLK_DIV_8,
};

/*******************************************************************************
* CCR REGISTERS DEFINITION
*******************************************************************************/

#define ADC_SET_CLK_PSL(ADC_Common, prescaler_div)        ADC_Common->CCR |= (prescaler_div << 16)

/*******************************************************************************
* CR1 REGISTERS DEFINITION
*******************************************************************************/

// Setting scan mode and resolution
#define ADC_ENABLE_SCAN_MODE(ADCx)          ADCx->CR1 |= (1 << 8)
#define ADC_DISABLE_SCAN_MODE(ADCx)         ADCx->CR1 &= ~(1 << 8)

enum ADC_resolution
{
    ADC_RESOLUTION_12BIT,
    ADC_RESOLUTION_10BIT,
    ADC_RESOLUTION_8BIT,
    ADC_RESOLUTION_6BIT,
};
#define ADC_SET_RESOLUTION(ADCx, resolution_val)        ADCx->CR1 |= resolution_val << 24

/*******************************************************************************
* CR2 REGISTERS DEFINITION
*******************************************************************************/

// Setting Continuous conversion mode, end of conversion type, DMA using, Data alignment
#define ADC_ENABLE_CONTINUOUS_CONVERSION(ADCx)          ADCx->CR2 |= (1 << 1)

enum
{
    EOC_END_OF_SEQUENCE,    // set bit EOC in SR to 1 after each channel convert completed.
    EOC_END_OF_CONVERSION,  // set bit EOC in SR to 1 only after all channel convert complated (using for DMA).
};

#define ADC_SET_EOC_TYPE(ADCx, EOC_type)        ADCx->CR2 |= EOC_type << 10

#define ADC_USING_DMA(ADCx)                     ADCx->CR2 |= (1 << 8)
#define ADC_NOT_USING_DMA(ADCx)                 ADCx->CR2 &= ~(1 << 8)

enum DMA_stop_type
{
    DMA_STOP_AT_LAST_CONVERSION,
    DMA_CONTINUE_AFTER_LAST_CONVERSION,
};

#define DMA_AFTER_CONVENSION(ADCx, type)       ADCx->CR2 |= (type << 9)

enum Data_alignment
{
    DATA_LEFT_ALIGNMENT,
    DATA_RIGHT_ALIGNMENT,
};

#define ADC_SET_DATA_ALIGNMENT(ADCx, type)      ADCx->CR2 |= (type << 11)

// Enable ADC
#define ADC_ENABLE(ADCx)                        ADCx->CR2 |= (1 << 0)
// Start ADC
#define ADC_START(ADCx)                         ADCx->CR2 |= (1 << 30)

/*******************************************************************************
* SMPRx REGISTERS DEFINITION
*******************************************************************************/

// Set Sampling time
enum ADC_Sampling_time
{
    ADC_SPLT_3_CYCLES,
    ADC_SPLT_15_CYCLES,
    ADC_SPLT_28_CYCLES,
    ADC_SPLT_56_CYCLES,
    ADC_SPLT_84_CYCLES,
    ADC_SPLT_112_CYCLES,
    ADC_SPLT_144_CYCLES,
    ADC_SPLT_480_CYCLES,
};

#define ADC_SET_SAMPLING_TIME(ADCx, channel, sampling_time)     \
    do { 							                            \
        if (channel <= ADC_CH9) { 			                    \
            ADCx->SMPR2 |= sampling_time << (channel * 3); 	    \
        } else { 	                                            \
            ADCx->SMPR1 |= sampling_time << (channel * 3 - 30); \
        } 							                            \
    } while (0)

/*******************************************************************************
* SQRx REGISTERS DEFINITION
*******************************************************************************/

// Set sequence length
#define ADC_SET_SEQUENCE_LENGTH(ADCx, length)    ADCx->SQR1 |= (length - 1) << 20

// Set sequence x
#define ADC_SET_SEQUENCE_1(ADCx, channel)       ADCx->SQR3 |= channel
#define ADC_SET_SEQUENCE_2(ADCx, channel)       ADCx->SQR2 |= channel
#define ADC_SET_SEQUENCE_3(ADCx, channel)       ADCx->SQR1 |= channel

/*******************************************************************************
* SR REGISTERS DEFINITION
*******************************************************************************/

#define ADC_CLEAR_STATUS_REGISTER(ADCx)         ADCx->SR = 0
// Get ADC result
#define ADC_GET_CONVERSION_RESULT(ADCx)         ADCx->SR & (1 << 1)

/*******************************************************************************
* DR REGISTERS DEFINITION
*******************************************************************************/

#define ADC_GET_RESULT(ADCx)                    ADCx->DR

/*******************************************************************************
* FUNCTIONS DEFINITION
*******************************************************************************/
void ADC_GPIOConfig(ADCx* ADC_x, uint8_t Chanelx);
void ADC_SetSequence(ADCx* ADC_x, uint8_t Sequence_index, uint8_t Channel);
void ADC_Configuration(ADC_Variables ADC_val);

void ADC_Start(ADCx *ADC_x);
uint16_t ADC_GetData(ADCx *ADC_x);
