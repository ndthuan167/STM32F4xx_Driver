/**
 * @file Timer.c
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Configuration for timer of STM32F407VGTx (ARMCortex M4)
 * @date 2024-07-19
 *
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/
#include "Timer.h"
#include "../RCC/RCC.h"

#define INTERNAL_CLOCK            16000000
#if defined(USE_SYSCLK_16MHz)
#define INTERNAL_CLOCK            16000000
#elif defined(USE_SYSCLK_24MHz)
#define INTERNAL_CLOCK            24000000
#elif defined(USE_SYSCLK_36MHz)
#define INTERNAL_CLOCK            36000000
#elif defined(USE_SYSCLK_48MHz)
#define INTERNAL_CLOCK            48000000
#elif defined(USE_SYSCLK_56MHz)
#define INTERNAL_CLOCK            56000000
#elif defined(USE_SYSCLK_72MHz)
#define INTERNAL_CLOCK            72000000
#endif

/******************************************************************************
 * Variables definition
 ******************************************************************************/
volatile uint8_t timer_loop1ms_IT = 0;

uint8_t timer_loop10ms = 0;
uint8_t timer_loop50ms = 0;
uint8_t timer_loop100ms = 0;
uint8_t timer_loop500ms = 0;
uint8_t timer_loop1s = 0;

typedef struct
{
    uint8_t timer_1ms : 1;
    uint8_t timer_10ms : 1;
    uint8_t timer_50ms : 1;
    uint8_t timer_100ms : 1;
    uint8_t timer_500ms : 1;
    uint8_t timer_1s : 1;
} timer_flag;

timer_flag timer_fl;

/**
*******************************************************************************
* @ Name : Timer_EnableClock
* @ Parameters: TIMER *timerx
* @ Registers : 
* @ Descriptions : APB1ENR,AHB1ENR, APB2ENR
*		- Configuration for timerx.
*           + gpiox: timer1 -> timer14
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-02-24
*******************************************************************************
*/
void Timer_EnableClock(TIMER *timex)
{
    if (timex == (TIMER *)ADDRESS_TIMER_1)
        RCC_EnablePeripheralClock(CLOCK_TIM1);
    else if (timex == (TIMER *)ADDRESS_TIMER_2)
        RCC_EnablePeripheralClock(CLOCK_TIM2);
    else if (timex == (TIMER *)ADDRESS_TIMER_3)
        RCC_EnablePeripheralClock(CLOCK_TIM3);
    else if (timex == (TIMER *)ADDRESS_TIMER_4)
        RCC_EnablePeripheralClock(CLOCK_TIM4);
    else if (timex == (TIMER *)ADDRESS_TIMER_5)
        RCC_EnablePeripheralClock(CLOCK_TIM5);
    else if (timex == (TIMER *)ADDRESS_TIMER_6)
        RCC_EnablePeripheralClock(CLOCK_TIM6);
    else if (timex == (TIMER *)ADDRESS_TIMER_7)
        RCC_EnablePeripheralClock(CLOCK_TIM7);
    else if (timex == (TIMER *)ADDRESS_TIMER_8)
        RCC_EnablePeripheralClock(CLOCK_TIM8);
    else if (timex == (TIMER *)ADDRESS_TIMER_9)
        RCC_EnablePeripheralClock(CLOCK_TIM9);
    else if (timex == (TIMER *)ADDRESS_TIMER_10)
        RCC_EnablePeripheralClock(CLOCK_TIM10);
    else if (timex == (TIMER *)ADDRESS_TIMER_11)
        RCC_EnablePeripheralClock(CLOCK_TIM11);
    else if (timex == (TIMER *)ADDRESS_TIMER_12)
        RCC_EnablePeripheralClock(CLOCK_TIM12);
    else if (timex == (TIMER *)ADDRESS_TIMER_13)
        RCC_EnablePeripheralClock(CLOCK_TIM13);
    else if (timex == (TIMER *)ADDRESS_TIMER_14)
        RCC_EnablePeripheralClock(CLOCK_TIM14);
    else
        return;
}

/**
*******************************************************************************
* @ Name : Timer_Configuration
* @ Parameters: TIMER *timerx, float timer_flag
* @ Registers : TIM_CR1, TIM_SMCR, TIM_DIER, TIM_PSC, TIM_ARR
* @ Descriptions :
*		- Configure the timer (prescaler = 0, auto reload value, enable counter, enable interrupt)
*		- timerx: timer1->timer14
*		- timer flag: (TIMER_1MS, TIMER_10MS, TIMER_50MS, TIMER_100MS, TIMER_500MS, TIMER_1S)
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-19
*******************************************************************************
*/
void Timer_Configuration(TIMER *timerx, float timer_flag)
{

    uint16_t prescaler_val = 0;
    uint32_t reload_val = 0;

    // Enable Clock
    Timer_EnableClock(timerx);
// 
    // reload_val = (timer_flag * INTERNAL_CLOCK) - 1;
    reload_val = 0x4F;
    // TIMER_SET_CLOCK_DEVISION(timerx, clk_division);
    TIMER_SET_PRESCALER(timerx, prescaler_val);

    if (timerx == (TIMER *)ADDRESS_TIMER_2 || timerx == (TIMER *)ADDRESS_TIMER_5)
    {
        TIMER_SET_COUNTER_VALUE_TIME2_5(timerx, 0x00);
        TIMER_SET_AUTORELOAD_VALUE_TIM2_5(timerx, reload_val);
    }
    else
    {
        TIMER_SET_COUNTER_VALUE(timerx, 0x00);
        TIMER_SET_AUTORELOAD_VALUE(timerx, reload_val);
    }
    Timer_SettingCounter(timerx, ENABLE);
    Timer_SettingInterrupt(timerx, ENABLE);
}

/**
*******************************************************************************
* @ Name : Timer_SettingCounter
* @ Parameters: TIMER *timerx, uint8_t value
* @ Registers : TIM_CR1
* @ Descriptions :
*		- Setting counter (Enable/ Disable)
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-19
*******************************************************************************
*/
void Timer_SettingCounter(TIMER *timerx, uint8_t value)
{
    if (value == ENABLE)
        TIMER_ENABLE_COUNTER(timerx, value);
    else
        TIMER_DISABLE_COUNTER(timerx, value);
}

/**
*******************************************************************************
* @ Name : Timer_SettingInterrupt
* @ Parameters: TIMER *timerx, uint8_t value
* @ Registers : TIM_DIER
* @ Descriptions :
*		- Setting timer interrupt (Enable/ Disable)
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-19
*******************************************************************************
*/
void Timer_SettingInterrupt(TIMER *timerx, uint8_t value)
{
    if (value)
        TIMER_SET_ENBALE_INTERRUPT(timerx);
    else
        TIMER_SET_DISABLE_INTERRUPT(timerx);
}

/**
*******************************************************************************
* @ Name : Timer_ClearInterruptFlag
* @ Parameters: TIMER *timerx
* @ Registers : TIM_SR
* @ Descriptions :
*		- Clear interrupt flag by software
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-19
*******************************************************************************
*/
void Timer_ClearInterruptFlag(TIMER *timerx)
{
    TIMER_CLEAR_INTERRUPT_FLAG(timerx);
}

/**
*******************************************************************************
* @ Name : LoopTimerSetting
* @ Parameters: void
* @ Registers :
* @ Descriptions :
*		- Loop to get the timer flag
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-19
*******************************************************************************
*/
void LoopTimerSetting(void)
{
    *((uint8_t *)&timer_fl) = 0;

    if (timer_loop1ms_IT)
    {
        timer_fl.timer_1ms = SET;
        timer_loop1ms_IT = 0;
        timer_loop10ms++;
        if (timer_loop10ms >= 10)
        {
            timer_fl.timer_10ms = SET;
            timer_loop10ms = 0;
            timer_loop50ms++;

            if (timer_loop50ms >= 5)
            {
                timer_fl.timer_50ms = SET;
                timer_loop50ms = 0;
                timer_loop100ms++;

                if (timer_loop100ms >= 2)
                {
                    timer_fl.timer_100ms = SET;
                    timer_loop100ms = 0;
                    timer_loop500ms++;

                    if (timer_loop500ms >= 5)
                    {
                        timer_fl.timer_500ms = SET;
                        timer_loop500ms = 0;
                        timer_loop1s++;

                        if (timer_loop1s >= 2)
                        {
                            timer_fl.timer_1s = SET;
                            timer_loop1s = 0;
                        }
                    }
                }
            }
        }
    }
}

/**
*******************************************************************************
* @ Name : GetFlagTimerXms
* @ Parameters:
* @ Registers :
* @ Descriptions :
*		- Get flag timer (10ms, 50ms, 100ms, 500ms, 1s).
*       - If GetFlagTimerXms() == TRUE, it means time of X is determined.
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167)
* @ date : 2024-07-19
*******************************************************************************
*/
uint8_t GetFlagTimer1ms(void)
{
    return timer_fl.timer_1ms;
}

uint8_t GetFlagTimer10ms(void)
{
    return timer_fl.timer_10ms;
}

uint8_t GetFlagTimer50ms(void)
{
    return timer_fl.timer_50ms;
}

uint8_t GetFlagTimer100ms(void)
{
    return timer_fl.timer_100ms;
}

uint8_t GetFlagTimer500ms(void)
{
    return timer_fl.timer_500ms;
}

uint8_t GetFlagTimer1s(void)
{
    return timer_fl.timer_1s;
}

void Timer_InputCaptureConfiguration(TIMER *timerx, uint8_t channel, uint8_t TIx, uint8_t edge, uint16_t prescaler, uint8_t interrupt, uint8_t enable)
{
    Timer_EnableClock(timerx);
    switch (channel)
    {
    case TIMER_CHANNEL_1:
    case TIMER_CHANNEL_2:
        TIMER_INPUT_CAPTURE_CONFIG_CHANNEL1_2(timerx, TIx);
        break;
    case TIMER_CHANNEL_3:
    case TIMER_CHANNEL_4:
        TIMER_INPUT_CAPTURE_CONFIG_CHANNEL3_4(timerx, TIx);
        break;
    default:
        break;
    }
    TIMER_CONFIG_IP1_FILTER_8_SAMPLES(timerx);
    TIMER_INPUT_CAPTURE_CONFIG_EDGE(timerx, channel, edge);
    TIMER_SET_PRESCALER(timerx, prescaler);
    TIMER_INPUT_CAPTURE_ENABLE(timerx, channel, enable);
    TIMER_ENABLE_COUNTER(timerx, ENABLE);
    TIMER_INPUT_CAPTURE_CONFIG_ENABLE_INTERRUPT(timerx, channel, interrupt);
}


uint16_t Timer_GetCaptureValue(TIMER* timerx, uint8_t channel)
{
    uint16_t ccr_value = 0;
    if(channel == TIMER_CHANNEL_1)
        ccr_value = TIMER_INPUT_CAPTURE_GET_CAPTURE_VALUE_CHANNEL1(timerx);
    else if ( channel == TIMER_CHANNEL_2)
        ccr_value = TIMER_INPUT_CAPTURE_GET_CAPTURE_VALUE_CHANNEL2(timerx);
    else if ( channel == TIMER_CHANNEL_3)
        ccr_value = TIMER_INPUT_CAPTURE_GET_CAPTURE_VALUE_CHANNEL3(timerx);
    else if ( channel == TIMER_CHANNEL_4)
        ccr_value = TIMER_INPUT_CAPTURE_GET_CAPTURE_VALUE_CHANNEL4(timerx);
    
    return ccr_value;
}


void Timer_OutputCompareConfiguration(TIMER* timerx, uint8_t channel, uint8_t mode, uint16_t prescaler, uint32_t compare)
{
    Timer_EnableClock(timerx);
    switch (channel)
    {
    case TIMER_CHANNEL_1:
        TIMER_OUTPUT_COMPARE_SELECTION_CHANNEL1_2(timerx);
        TIMER_OUTPUT_COMPARE_SETMODE_CHANNEL1_2(timerx, mode);
        TIMER_RESET_CAPTURE_VALUE_CHANNEL1(timerx);
    break;
    case TIMER_CHANNEL_2:
        TIMER_OUTPUT_COMPARE_SELECTION_CHANNEL1_2(timerx);
        TIMER_OUTPUT_COMPARE_SETMODE_CHANNEL1_2(timerx, mode);
        TIMER_RESET_CAPTURE_VALUE_CHANNEL2(timerx);
    break;
    case TIMER_CHANNEL_3:
        TIMER_OUTPUT_COMPARE_SELECTION_CHANNEL3_4(timerx);
        TIMER_OUTPUT_COMPARE_SETMODE_CHANNEL3_4(timerx, mode);
        TIMER_RESET_CAPTURE_VALUE_CHANNEL3(timerx);
    break;
    case TIMER_CHANNEL_4:
        TIMER_OUTPUT_COMPARE_SELECTION_CHANNEL3_4(timerx);
        TIMER_OUTPUT_COMPARE_SETMODE_CHANNEL3_4(timerx, mode);
        TIMER_RESET_CAPTURE_VALUE_CHANNEL4(timerx);
    break;
    default:
        break;
    }

    TIMER_SET_PRESCALER(timerx, prescaler);

    if (timerx == (TIMER *)ADDRESS_TIMER_2 || timerx == (TIMER *)ADDRESS_TIMER_5)
    {
        TIMER_SET_COUNTER_VALUE_TIME2_5(timerx, 0x00);
        // timerx->TIM_ARR = compare;
        // TIMER_SET_AUTORELOAD_VALUE_TIM2_5(timerx, compare);
    }
    else
    {
        TIMER_SET_COUNTER_VALUE(timerx, 0x00);
    }
    
    TIMER_SET_AUTORELOAD_VALUE(timerx, compare);
    TIMER_OUTPUT_COMPARE_TURNON(timerx);
    TIMER_ENABLE_COUNTER(timerx, ENABLE);
}

/*******************************************************************************
 * INTERRUPT HANDLER FUNCTION
 *******************************************************************************/

