#include "Thuan_STM32F407VGTx_Driver.h"
#include "stdbool.h"

unsigned char value_re_Fan[5] = "fanon";
unsigned char value_re_Fanoff[6] = "fanoff";
unsigned char value_re_light[7] = "lighton";
unsigned char value_re_lightoff[8] = "lightoff";
uint8_t value_re_IT;

uint8_t fan_control = false;
uint8_t light_control = false;
int main()
{
	// Enable Clock
	RCC_EnablePeripheralClock(CLOCK_GPIO_A, __RCC);
	RCC_EnablePeripheralClock(CLOCK_GPIO_D, __RCC);


	// GPIO output configuration
	GPIO_Configuration(GPIO_A, GPIO_PIN1, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
	GPIO_Configuration(GPIO_A, GPIO_PIN2, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);


	USART_Configuration(usart2, BAUDRATE_9600, DATA_BITS_8, OVERSAMPLING_BY_16, PARITY_DISABLE, EVEN_PARITY);
	USART_ReceiverDataInterruptEnable(usart2);
	NVIC_Configuration(__NVIC, _USART2_IRQHandler, 0x01, ENABLE);
	
	while (1)
	{
		if(value_re_IT == 'a')
		{
			if(fan_control == false)
				fan_control = true;
			else
				fan_control = false;
			
			if(fan_control == true)
			{
				GPIO_SettingOutputDataBSRR(GPIO_A, GPIO_PIN1, SET);
				USART_SendData(usart2, value_re_Fan, 5);	// send data received to terminal
				value_re_IT = 'c';
			}
			else
			{
				GPIO_SettingOutputDataBSRR(GPIO_A, GPIO_PIN1, CLEAR); // clear pin
				USART_SendData(usart2,value_re_Fanoff,6);
				value_re_IT = 'c';
			}
		}

		if(value_re_IT == 'b')
		{
			if(light_control == false)
				light_control = true;
			else
				light_control = false;
			
			if(light_control == true)
			{
				GPIO_SettingOutputDataBSRR(GPIO_A, GPIO_PIN2, SET);
				USART_SendData(usart2, value_re_light, 7);
				value_re_IT = 'd';
			}
			else
			{
				GPIO_SettingOutputDataBSRR(GPIO_A, GPIO_PIN2, CLEAR);
				USART_SendData(usart2, value_re_lightoff,8);
				value_re_IT = 'd';
			}
		}
	}
}

void USART2_IRQHandler(void)
{
	if (USART_GET_READDATA_STATUS(usart2))
	{
		value_re_IT = USART_GET_DATA_VALUE(usart2);		// data recevied
	}
}

