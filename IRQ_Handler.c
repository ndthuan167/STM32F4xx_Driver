#include "Peripheral/SystemTimer/Systick.h"
#include "Peripheral/Timer/Timer.h"
#include "Peripheral/USART/USART.h"
#include "Peripheral/EXTI/EXTI.h"
#include "Peripheral/SPI/SPI.h"

/*******************************************************************************
SYSTICK_HANDLER
*******************************************************************************/
void SysTick_Handler(void)
{
    systick_timer_loop_1ms_IT++;
}

/*******************************************************************************
TIMER_HANDLER
*******************************************************************************/
void TIM1_CC_IRQHandler()
{

}   

void TIM2_IRQHandler()
{

}

void TIM3_IRQHandler()
{
    timer_loop1ms_IT++;
}

void TIM4_IRQHandler()
{

}

void TIM7_IRQHandler()
{
    timer_loop1ms_IT++;
}


/*******************************************************************************
EXTI_HANDLER
*******************************************************************************/

void EXTI1_IRQHandler()
{
    HandleLED1();
}

void EXTI2_IRQHandler(void)
{
    HandleLED2();
}

/*******************************************************************************
    USARTx_HANDLER
*******************************************************************************/

void USART2_IRQHandler(void)
{
    USARTn *usart2 = (USARTn*)ADDRESS_USART_2;

	if (USART_GET_READDATA_STATUS(usart2))
	{
		value_re_IT = USART_GET_DATA_VALUE(usart2);		// data recevied
	}

	if(USART_GET_WRITEDATA_STATUS(usart2))
	{
		USART_SendData(usart2, &value_re_IT, 1);	// send data received to terminal
		USART_CLEAR_WRITEDATA_FLAG(usart2);
	}
}


/*******************************************************************************
    SPIx_HANDLER
*******************************************************************************/

// void SPI2_IRQHandler(void)
// {
// 	SPIn *spi2 = (SPIn*)ADDRESS_SPI_2;

// 	if(!(SPI_GET_BUSY_FLAG_STATUS(spi2)))
// 	{
// 		if(SPI_GET_RX_BUFFER_NOT_EMPTY_FLAG_STATUS(spi2))
// 		{
// 			value_re_IT_spi = SPI_GET_DATA_REGISTER(spi2);
// 		}
// 	}
// 	DISABLE_RX_BUFFER_NOT_EMPTY_INTERRUPT(spi2);
// }
