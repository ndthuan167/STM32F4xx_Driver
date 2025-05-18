#include "Peripheral/SystemTimer/Systick.h"
#include "Peripheral/Timer/Timer.h"
#include "Peripheral/USART/USART.h"
#include "Peripheral/EXTI/EXTI.h"
#include "Peripheral/SPI/SPI.h"
#include "Peripheral/CAN/CAN.h"
#include "Peripheral/ADC/ADC.h"
#include "Peripheral/DMA/DMA.h"

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

void SPI2_IRQHandler(void)
{
	SPIn *spi2 = (SPIn*)ADDRESS_SPI_2;

	if(!(SPI_GET_BUSY_FLAG_STATUS(spi2)))
	{
		if(SPI_GET_RX_BUFFER_NOT_EMPTY_FLAG_STATUS(spi2))
		{
			value_re_IT_spi = SPI_GET_DATA_REGISTER(spi2);
		}
	}
	DISABLE_RX_BUFFER_NOT_EMPTY_INTERRUPT(spi2);
}

/*******************************************************************************
    CANx_HANDLER
*******************************************************************************/

void CAN1_TX_IRQHandler(void)
{
	// Check mailbox TX interrupt flag
	CANx *can1 = (CANx*)ADDRESS_CAN_1;
	if(GET_TRANSMIT_MB0_INTERRUPT_FLAG(can1))
	{
		CLEAR_TRANSMIT_MB0_INTERRUPT_FLAG(can1);
		// Send message to mailbox

	}
}

void CAN1_RX0_IRQHandler(void)
{
	CANx *can1 = (CANx*)ADDRESS_CAN_1;
	if(CAN_GET_MESSAGE_FIFO0_PENDING(can1))
	{
		CAN_CLEAR_FIFO0_PENDING(can1);

		// Read data from FIFO0
	}
}

void CAN1_RX1_IRQHandler(void)
{
}


/*******************************************************************************
    ADCx_HANDLER
*******************************************************************************/
volatile uint32_t data_converted;
void ADC_IRQHandler(void)
{
	ADCx *adc1 = (ADCx *)ADDRESS_ADC_1;
	
	if((ADC_GET_CONVERSION_RESULT(adc1)))
	{
		data_converted = ADC_GET_RESULT(adc1);
		ADC_CLEAR_STATUS_REGISTER(adc1);
	}
}

/*******************************************************************************
	DMAx_StreamX_HANDLER
*******************************************************************************/

// Example for DMA1 Stream 0
void DMA1_Stream0_IRQHandler(void)
{
	DMAx *dma1 = (DMAx *)ADDRESS_DMA1;

	// Check FIFO error
	if(DMA_Get_IRQ_Flag(dma1, DMA_STREAM0, DMA_FIFO_ERROR_IRQ_FLAG))
	{
		// Handle FIFO error
		/* ...... */
		DMA_CLEAR_FIFO_ERROR_IRQ_FLAG(dma1, DMA_STREAM0);
	}

	// Check Direct mode error
	if(DMA_Get_IRQ_Flag(dma1, DMA_STREAM0, DMA_DIRECT_MODE_ERROR_IRQ_FLAG))
	{
		// Handle Direct mode error
		/* ...... */
		DMA_CLEAR_DIRECT_MODE_ERROR_IRQ_FLAG(dma1, DMA_STREAM0);
	}

	// Check Transfer error
	if(DMA_Get_IRQ_Flag(dma1, DMA_STREAM0, DMA_TRANSFER_ERROR_IRQ_FLAG))
	{
		// Handle Transfer error
		/* ...... */
		DMA_CLEAR_TRANSFER_ERROR_IRQ_FLAG(dma1, DMA_STREAM0);
	}

	// Check Half transfer complete
	if(DMA_Get_IRQ_Flag(dma1, DMA_STREAM0, DMA_HAFT_TRANSFER_COMPLETE_IRQ_FLAG))
	{
		// Handle Half transfer complete
		/* ...... */
		DMA_CLEAR_HAFT_TRANSFER_COMPLETE_IRQ_FLAG(dma1, DMA_STREAM0);
	}

	// Check  transfer complete
	if(DMA_Get_IRQ_Flag(dma1, DMA_STREAM0, DMA_TRANSFER_COMPLETE_IRQ_FLAG))
	{
		// Handle transfer complete
		/* ...... */
		DMA_CLEAR_TRANSFER_COMPLETE_IRQ_FLAG(dma1, DMA_STREAM0);
	}
}
