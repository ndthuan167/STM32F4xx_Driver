#include <stdio.h>
#include <stdint.h>

//RCC
#define ADDRESS_RCC             0x40023800

typedef struct
{
	uint32_t CR;
	uint32_t PLLCFGR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t AHB1RSTR;
	uint32_t AHB2RSTR;
	uint32_t AHB3RSTR;
    uint32_t reserve0;
	uint32_t APB1RSTR;
	uint32_t APB2RSTR;
    uint32_t reserve1;
    uint32_t reserve2;
	uint32_t AHB1ENR;
	uint32_t AHB2ENR;
	uint32_t AHB3ENR;
    uint32_t reserve3;
	uint32_t APB1ENR;
	uint32_t APB2ENR;
    uint32_t reserve4;
    uint32_t reserve5;
	uint32_t AHB1LPENR;
	uint32_t AHB2LPENR;
	uint32_t AHB3LPENR;
    uint32_t reserve6;
	uint32_t APB1LPENR;
	uint32_t APB2LPENR;
    uint32_t reserve7;
    uint32_t reserve8;
	uint32_t BDCR;
	uint32_t CSR;
    uint32_t reserve9;
    uint32_t reserve10;
	uint32_t SSCGR;
	uint32_t PLLI2SCFGR;
} RCC;

enum
{
    CLOCK_GPIO_A,
    CLOCK_GPIO_B,
    CLOCK_GPIO_C,
    CLOCK_GPIO_D,
    CLOCK_GPIO_E,
    CLOCK_GPIO_F,
    CLOCK_GPIO_G,
    CLOCK_GPIO_H,
    CLOCK_GPIO_I,
	CLOCK_GPIO_J,
	CLOCK_GPIO_K,
	CLOCK_GPIO_CRC,
};

#define RCC_SET_AHB1ENR(__RCC,value)  	__RCC->AHB1ENR = value
#define RCC_GET_AHB1ENR()  				__RCC->AHB1ENR

enum
{
	CLOCK_TIM2 		= CLOCK_GPIO_CRC + 1,
	CLOCK_TIM3,
	CLOCK_TIM4,
	CLOCK_TIM5,
	CLOCK_TIM6,
	CLOCK_TIM7,
	CLOCK_TIM12,
	CLOCK_TIM13,
	CLOCK_TIM14,
	CLOCK_WWDG 		= CLOCK_TIM2 + 11,
	CLOCK_SPI2 		= CLOCK_TIM2 + 14,
	CLOCK_SPI3,
	CLOCK_USART2 	= CLOCK_TIM2 + 17,
	CLOCK_USART3,
	CLOCK_UART4,
	CLOCK_UART5,
	CLOCK_I2C1 		= CLOCK_TIM2 + 21,
	CLOCK_I2C2,
	CLOCK_I2C3,
	CLOCK_CAN1		= CLOCK_TIM2 + 25,
	CLOCK_CAN2,
	CLOCK_PWR 		= CLOCK_TIM2 + 28,
	CLOCK_DAC 		= CLOCK_TIM2 + 29,
	CLOCK_UART7,
	CLOCK_UART8,
};

#define RCC_SET_APB1ENR(__RCC,value)  	__RCC->APB1ENR = value
#define RCC_GET_APB1ENR()  				__RCC->APB1ENR

enum
{
	CLOCK_TIM1 		= CLOCK_UART8 + 1,
	CLOCK_TIM8,
	CLOCK_USART1 	= CLOCK_TIM1 + 4,
	CLOCK_USART6,
	CLOCK_ADC1 		= CLOCK_TIM1 + 8,
	CLOCK_ADC2,
	CLOCK_ADC3,
	CLOCK_SDIO 		= CLOCK_TIM1 + 11,
	CLOCK_SDI1,
	CLOCK_SPI4 		= CLOCK_TIM1 + 13,
	CLOCK_SYSCFG,
	CLOCK_TIM9 		= CLOCK_TIM1 + 16,
	CLOCK_TIM10,
	CLOCK_TIM11,
	CLOCK_SPI5 		= CLOCK_TIM1 + 20,
	CLOCK_SPI6,
	CLOCK_SAI1,
};

#define RCC_SET_APB2ENR(__RCC,value)  	__RCC->APB2ENR = value
#define RCC_GET_APB2ENR()  				__RCC->APB2ENR

void RCC_EnablePeripheralClock(uint8_t Peripheral, RCC* __RCC);
