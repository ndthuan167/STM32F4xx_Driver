/**
 * @file Timer.h
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Some declaration for Timer of STM32F407VGTx (ARMCortex M4)
 * @date 2024-07-10
 * 
 */

/******************************************************************************
* Include Files
******************************************************************************/

#include "stdio.h"
#include "stdint.h"

/*******************************************************************************
* TIMER ADDRESS DEFINITION
*******************************************************************************/

#define ADDRESS_TIMER_1     0x40010000
#define ADDRESS_TIMER_2     0x40000000
#define ADDRESS_TIMER_3     0x40000400
#define ADDRESS_TIMER_4     0x40000800
#define ADDRESS_TIMER_5     0x40000C00
#define ADDRESS_TIMER_6     0x40001000
#define ADDRESS_TIMER_7     0x40001400
#define ADDRESS_TIMER_8     0x40010400
#define ADDRESS_TIMER_9     0x40014000
#define ADDRESS_TIMER_10    0x40014400
#define ADDRESS_TIMER_11    0x40014800
#define ADDRESS_TIMER_12    0x40001800
#define ADDRESS_TIMER_13    0x40001C00
#define ADDRESS_TIMER_14    0x40002000

/*******************************************************************************
* TIMER REGISTER STRUCTURE DEFINITION
*******************************************************************************/

typedef void INTERRUPT;

typedef struct
{
    uint32_t TIM_CR1;
    uint32_t TIM_CR2;
    uint32_t TIM_SMCR;
    uint32_t TIM_DIER;
    uint32_t TIM_SR;
    uint32_t TIM_EGR;
    uint32_t TIM_CCMR1;
    uint32_t TIM_CCMR2;
    uint32_t TIM_CCER;
    uint32_t TIM_CNT;
    uint32_t TIM_PSC;
    uint32_t TIM_ARR;
    uint32_t reserve;
    uint32_t TIM_CCR1;
    uint32_t TIM_CCR2;
    uint32_t TIM_CCR3;
    uint32_t TIM_CCR4;
    uint32_t reserve1;
    uint32_t TIM_DCR;
    uint32_t TIM_DMAR;
} TIMER;


extern volatile uint8_t timer_loop1ms_IT;


/*******************************************************************************
* ENUM DEFINITION
*******************************************************************************/
// enum of clock devision for timer

enum
{
    CLK_DIV_1,
    CLK_DIV_2,
    CLK_DIV_4,
};

enum
{
    TIMER_CHANNEL_1 = 1,
    TIMER_CHANNEL_2,
    TIMER_CHANNEL_3,
    TIMER_CHANNEL_4,
};

// const uint8_t TimerChannelPinConfigPortA[14][5] =
// {
//     // AFx     CH1,    CH2     CH3      CH4
//     {   1,     8,     9,      10,     11  },  // Timer 1 
//     {   1,     0,     1,      2,      3   },  // Timer 2 
//     {   2,     6,     7,      '-',    '-' },  // Timer 3 
//     {   2,     '-',   '-',    '-',    '-' },  // Timer 4 
//     {   2,     0,     1,      2,      3   },  // Timer 5 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 6 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 7 
//     {   3,     '-',   '-',    '-',    '-' },  // Timer 8 
//     {   3,     2,     3,      '-',    '-' },  // Timer 9 
//     {   3,     '-',   '-',    '-',    '-' },  // Timer 10
//     {   3,     '-',   '-',    '-',    '-' },  // Timer 11
//     {   9,     '-',   '-',    '-',    '-' },  // Timer 12
//     {   9,     6,     '-',    '-',    '-' },  // Timer 13
//     {   9,     7,     '-',    '-',    '-' },  // Timer 14
// };

// const uint8_t TimerChannelPinConfigPortB[14][5] =
// {
//     // AFx     CH1,    CH2     CH3      CH4
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 1 
//     {   1,     '-',   3,      10,     11  },  // Timer 2 
//     {   2,     4,     5,      0,      1   },  // Timer 3 
//     {   2,     6,     7,      8,      9   },  // Timer 4 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 5 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 6 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 7 
//     {   3,     '-',   '-',    '-',    '-' },  // Timer 8 
//     {   3,     '-',   '-',    '-',    '-' },  // Timer 9 
//     {   3,     8,     '-',    '-',    '-' },  // Timer 10
//     {   3,     9,     '-',    '-',    '-' },  // Timer 11
//     {   9,     14,     15,    '-',    '-' },  // Timer 12
//     {   9,     '-',   '-',    '-',    '-' },  // Timer 13
//     {   9,     '-',   '-',    '-',    '-' },  // Timer 14
// };

// const uint8_t TimerChannelPinConfigPortC[14][5] =
// {
//     // AFx     CH1,    CH2     CH3      CH4
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 1 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 2 
//     {   2,     6,     7,      8,      9   },  // Timer 3 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 4 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 5 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 6 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 7 
//     {   3,     6,     7,      8,      9   },  // Timer 8 
//     {   3,     '-',   '-',    '-',    '-' },  // Timer 9 
//     {   3,     '-',   '-',    '-',    '-' },  // Timer 10
//     {   3,     '-',   '-',    '-',    '-' },  // Timer 11
//     {   9,     '-',   '-',    '-',    '-' },  // Timer 12
//     {   9,     '-',   '-',    '-',    '-' },  // Timer 13
//     {   9,     '-',   '-',    '-',    '-' },  // Timer 14
// };

// const uint8_t TimerChannelPinConfigPortD[14][5] =
// {
//     // AFx     CH1,    CH2     CH3      CH4
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 1 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 2 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 3 
//     {   2,     6,     7,      8,      9   },  // Timer 4 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 5 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 6 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 7 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 8 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 9 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 10
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 11
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 12
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 13
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 14
// };

// const uint8_t TimerChannelPinConfigPortE[14][5] =
// {
//     // AFx     CH1,    CH2     CH3      CH4
//     {   2,      9,      11,    13,    15  },  // Timer 1 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 2 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 3 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 4 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 5 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 6 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 7 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 8 
//     {   3,      5,      6,    '-',    '-' },  // Timer 9 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 10
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 11
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 12
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 13
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 14
// };

// const uint8_t TimerChannelPinConfigPortF[14][5] =
// {
//     // AFx     CH1,    CH2     CH3      CH4
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 1 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 2 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 3 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 4 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 5 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 6 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 7 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 8 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 9 
//     {   3,      6,    '-',    '-',    '-' },  // Timer 10
//     {   3,      7,    '-',    '-',    '-' },  // Timer 11
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 12
//     {   9,      8,    '-',    '-',    '-' },  // Timer 13
//     {   9,      9,    '-',    '-',    '-' },  // Timer 14
// };

// const uint8_t TimerChannelPinConfigPortH[14][5] =
// {
//     // AFx     CH1,    CH2     CH3      CH4
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 1 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 2 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 3 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 4 
//     {   2,      10,    11,     12,    '-' },  // Timer 5 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 6 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 7 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 8 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 9 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 10
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 11
//     {   9,       6,     9,    '-',    '-' },  // Timer 12
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 13
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 14
// };

// const uint8_t TimerChannelPinConfigPortI[14][5] =
// {
//     // AFx     CH1,    CH2     CH3      CH4
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 1 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 2 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 3 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 4 
//     {   2,      0,    '-',    '-',    '-' },  // Timer 5 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 6 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 7 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 8 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 9 
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 10
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 11
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 12
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 13
//     {   '-',   '-',   '-',    '-',    '-' },  // Timer 14
// };


/*******************************************************************************
* COMMON DEFINITION
*******************************************************************************/

#define     UP_COUNTER      0
#define     DOWN_COUNTER    1

#define     DISABLE         0
#define     ENABLE          1

#define     SET          1

#define     TIMER_1MS       0.001
#define     TIMER_10MS      0.01
#define     TIMER_50MS      0.05
#define     TIMER_100MS     0.1
#define     TIMER_500MS     0.5
#define     TIMER_1S        1

/*******************************************************************************
* TIM_CR REGISTERS DEFINITION
*******************************************************************************/

#define TIMER_SET_CLOCK_DEVISION(timerx, clk_div)               timerx->TIM_CR1 |= (clk_div << 8)
#define TIMER_SET_DIRECTION_COUNTER(timerx, direction)          timerx->TIM_CR1 |= (direction << 4)

#define TIMER_ENABLE_COUNTER(timerx, value)                     timerx->TIM_CR1 |= (value << 0)
#define TIMER_DISABLE_COUNTER(timerx, value)                    timerx->TIM_CR1 &=~ (value << 0)
/*******************************************************************************
* TIM_CNT REGISTERS DEFINITION
*******************************************************************************/

#define TIMER_GET_COUNTER_VALUE(timerx)                         timerx->TIM_CNT << 16
#define TIMER_GET_COUNTER_VALUE_TIM2_5(timerx)                  timerx->TIM_CNT >> 16
#define TIMER_SET_COUNTER_VALUE(timerx, value)                  timerx->TIM_CNT = (value)
#define TIMER_SET_COUNTER_VALUE_TIME2_5(timerx, value)          timerx->TIM_CNT = (value << 16)

/*******************************************************************************
* TIM_PCS REGISTERS DEFINITION
*******************************************************************************/

#define TIMER_SET_PRESCALER(timerx, prescaler)                  timerx->TIM_PSC = (prescaler)

/*******************************************************************************
* TIM_ARR REGISTERS DEFINITION
*******************************************************************************/

#define TIMER_SET_AUTORELOAD_VALUE(timerx, value)               timerx->TIM_ARR = (value)
#define TIMER_SET_AUTORELOAD_VALUE_TIM2_5(timerx, value)        timerx->TIM_ARR = (value << 16)

/*******************************************************************************
* TIM_DIER REGISTERS DEFINITION
*******************************************************************************/

#define TIMER_SET_ENBALE_INTERRUPT(timerx)                      timerx->TIM_DIER |= (1 << 0)
#define TIMER_SET_DISABLE_INTERRUPT(timerx)                     timerx->TIM_DIER &= ~(1 << 0)

#define TIMER_INPUT_CAPTURE_CONFIG_ENABLE_INTERRUPT(timerx, channel, enable)      timerx->TIM_DIER |= (enable << channel)

/*******************************************************************************
* TIM_SR REGISTERS DEFINITION
*******************************************************************************/

#define TIMER_CLEAR_INTERRUPT_FLAG(timerx)                              timerx->TIM_SR &= ~(1 << 0)

/*******************************************************************************
* TIM_CCMR1 REGISTERS DEFINITION
*******************************************************************************/
#define TI_1       0x01
#define TI_2       0x02

#define TIMER_INPUT_CAPTURE_CONFIG_CHANNEL1_2(timerx, TIx)         timerx->TIM_CCMR1 |= (TIx << 0)    // CC1S bit.

#define TI_3       0x01
#define TI_4       0x02

#define TIMER_INPUT_CAPTURE_CONFIG_CHANNEL3_4(timerx, TIx)         timerx->TIM_CCMR2 |= (TIx << 0)    // CC1S bit.

#define TIMER_CONFIG_IP1_FILTER_8_SAMPLES(timerx)                       timerx->TIM_CCMR1 |= (0x05 << 4)

enum IP_Prescaler
{
    IP_PRESCALER_DISABLE,
    IP_PRESCALER_DIV_BY_2,
    IP_PRESCALER_DIV_BY_4,
    IP_PRESCALER_DIV_BY_8,
};

#define TIMER_INPUT_CAPTURE_CONFIG_PRESCALER(timerx, prescaler)         timerx->TIM_CCMR1 |= (prescaler << 2)

/*******************************************************************************
* TIM_CCER REGISTERS DEFINITION
*******************************************************************************/

#define IP_RISING_TRIGGERED    0x00    // 000
#define IP_FALLING_TRIGGERED   0x01    // 001
#define IP_BOTH_TRIGGERED      0x05    // 101

#define TIMER_INPUT_CAPTURE_CONFIG_EDGE(timerx, channelX, edge)         timerx->TIM_CCER |= (edge << 4 * (channelX - 1) + 1)

#define TIMER_INPUT_CAPTURE_ENABLE(timerx, channelX, enable)            timerx->TIM_CCER |= (enable << 4 * (channelX - 1))


/*******************************************************************************
* TIM_CCRX REGISTERS DEFINITION
*******************************************************************************/
#define TIMER_RESET_CAPTURE_VALUE_CHANNEL1(timerx)          timerx->TIM_CCR1  = 0
#define TIMER_RESET_CAPTURE_VALUE_CHANNEL2(timerx)          timerx->TIM_CCR2  = 0
#define TIMER_RESET_CAPTURE_VALUE_CHANNEL3(timerx)          timerx->TIM_CCR3  = 0
#define TIMER_RESET_CAPTURE_VALUE_CHANNEL4(timerx)          timerx->TIM_CCR4  = 0

#define TIMER_INPUT_CAPTURE_GET_CAPTURE_VALUE_CHANNEL1(timerx)          timerx->TIM_CCR1
#define TIMER_INPUT_CAPTURE_GET_CAPTURE_VALUE_CHANNEL2(timerx)          timerx->TIM_CCR2
#define TIMER_INPUT_CAPTURE_GET_CAPTURE_VALUE_CHANNEL3(timerx)          timerx->TIM_CCR3
#define TIMER_INPUT_CAPTURE_GET_CAPTURE_VALUE_CHANNEL4(timerx)          timerx->TIM_CCR4

/*-------------------------------- OUTPUT COMPARE ------------------------------*/
#define TIMER_OUTPUT_COMPARE_SELECTION_CHANNEL1_2(timerx)          timerx->TIM_CCMR1 &= ~(1 << 0)
#define TIMER_OUTPUT_COMPARE_SELECTION_CHANNEL3_4(timerx)          timerx->TIM_CCMR2 &= ~(1 << 0)

enum OC_Mode
{
    OC_MODE_FROZEN,
    OC_MODE_ACTIVE_LEVEL,
    OC_MODE_INACTIVE_LEVEL,
    OC_MODE_TOGGLE,
    OC_MODE_FORCE_INACTIVE,
    OC_MODE_FORCE_ACTIVE,
    OC_MODE_PWM1,
    OC_MODE_PWM2
};

#define TIMER_OUTPUT_COMPARE_SETMODE_CHANNEL1_2(timerx, mode)      timerx->TIM_CCMR1 |= (mode << 4);
#define TIMER_OUTPUT_COMPARE_SETMODE_CHANNEL3_4(timerx, mode)      timerx->TIM_CCMR2 |= (mode << 4);


#define TIMER_OUTPUT_COMPARE_TURNON(timerx)         timerx->TIM_CCER |= (1 << 0);

/*******************************************************************************
* FUNCTIONS DEFINITION
*******************************************************************************/
void Timer_EnableClock(TIMER *timex);
void Timer_SettingInterrupt(TIMER* timerx, uint8_t value);
void Timer_ClearInterruptFlag(TIMER* timerx);
void Timer_Configuration(TIMER *timerx, float timer_flag);
void Timer_SettingCounter(TIMER* timerx, uint8_t value);
void LoopTimerSetting(void);

uint8_t GetFlagTimer1ms(void);
uint8_t GetFlagTimer10ms(void);
uint8_t GetFlagTimer50ms(void);
uint8_t GetFlagTimer100ms(void);
uint8_t GetFlagTimer500ms(void);
uint8_t GetFlagTimer1s(void);

void Timer_InputCaptureConfiguration(TIMER* timerx, uint8_t channel, uint8_t TIx, uint8_t edge, uint16_t prescaler, uint8_t interrupt, uint8_t enable);
uint16_t Timer_GetCaptureValue(TIMER* timerx, uint8_t channel);
void Timer_OutputCompareConfiguration(TIMER* timerx, uint8_t channel, uint8_t mode, uint16_t prescaler, uint32_t compare);

