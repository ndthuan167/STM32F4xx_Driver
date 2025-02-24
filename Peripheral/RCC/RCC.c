#include "RCC.h"

void RCC_EnablePeripheralClock(uint8_t Peripheral, RCC* __RCC)
{
    uint32_t value = 0;
    if (Peripheral < CLOCK_TIM2)
    {
        value = RCC_GET_AHB1ENR();
        value |= (1 << Peripheral);

        RCC_SET_AHB1ENR(__RCC, value);
    }
    else if (Peripheral < CLOCK_TIM1)
    {
        value = RCC_GET_APB1ENR();
        value |= (1 << (Peripheral - CLOCK_TIM2));

        RCC_SET_APB1ENR(__RCC, value);
    }
    else
    {
        value = RCC_GET_APB2ENR();
        value |= (1 << (Peripheral - CLOCK_TIM1));

        RCC_SET_APB2ENR(__RCC, value);
    }
}
