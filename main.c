#include "Thuan_STM32F4xx_Driver.h"

uint8_t testvalue;
uint8_t testvalue1;
uint8_t testit;
volatile uint32_t i;
volatile uint32_t time_it;

unsigned char value_re_RT[6] = "abcde ";
uint8_t value_spi_receive[10];
volatile uint8_t value_re_IT;
volatile uint8_t value_re_IT_spi;
unsigned char buffer[] = "HelloWorld~\n";
unsigned char buffer_re;
uint8_t size_buff = sizeof(buffer) / sizeof(buffer[0]);
unsigned char value_re;
uint8_t data = 0x55;

uint8_t lck_genx = 0;
bool start_condition = false;
uint8_t data_init_lcd1[7] = {0x4E, 0x33, 0x32, 0x28, 0x0C, 0x06, 0x01};

int main()
{
	testvalue = 0;
	testvalue1 = 0;
	testit = 0;
	time_it = 0;

#if defined(USE_SYSCLK_16MHz)
	RCC_SettingSystemClock16MHz();
#elif defined(USE_SYSCLK_24MHz)
	RCC_SettingSystemClock24MHz();
#elif defined(USE_SYSCLK_36MHz)
	RCC_SettingSystemClock36MHz();
#elif defined(USE_SYSCLK_48MHz)
	RCC_SettingSystemClock48MHz();
#elif defined(USE_SYSCLK_56MHz)
	RCC_SettingSystemClock56MHz();
#elif defined(USE_SYSCLK_72MHz)
	RCC_SettingSystemClock72MHz();
#endif

	RCC_EnablePeripheralClock(CLOCK_SYSCFG);

	// GPIO output configuration
	GPIO_Configuration(GPIO_A, GPIO_PIN2, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
	GPIO_Configuration(GPIO_A, GPIO_PIN3, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
	GPIO_Configuration(GPIO_C, GPIO_PIN13, MODER_OUTPUT, OTYPER_OPENDRAIN, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
	GPIO_Configuration(GPIO_E, GPIO_PIN11, MODER_OUTPUT, OTYPER_OPENDRAIN, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
	GPIO_Configuration(GPIO_B, GPIO_PIN4, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
	GPIO_Configuration(GPIO_B, GPIO_PIN10, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);



	// Systick configuration
	SettingSystemTimer(PROCESSOR_CLKSRC, ENABLE, SYSTICK_TIMER_1MS);

	// Config PA1 is input pull down
	GPIO_Configuration(GPIO_A, GPIO_PIN0, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
	GPIO_Configuration(GPIO_A, GPIO_PIN1, MODER_INPUT, OTYPER_PUSHPULL, OSPEEDR_LOW, PUPDR_PULLUP);

	EXTI_Config_Variables EXTI1_Config;
	EXTI1_Config.EXTI_port = EXTIx_PA_PIN;
	EXTI1_Config.EXTI_line = EXTI_LINE_1;
	EXTI1_Config.trigger_type = RISING_TRIGGER;
	EXTI1_Config.mask_event = NOT_MASKED;
	EXTI1_Config.mask_it = NOT_MASKED;

	EXTI_Configuration(EXTI1_Config);

	NVIC_Config_Variables NVIC_Config1;
	NVIC_Config1.IRQNumber = _EXTI1_IRQHandler;
	NVIC_Config1.IRQPriority = 0x05;
	NVIC_Config1.IRQEnable = ENABLE;

	// NVIC configuration for EXTI1
	NVIC_Configuration(NVIC_Config1);

	// Config PD1 is input pull down
	GPIO_Configuration(GPIO_D, GPIO_PIN0, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING);
	GPIO_Configuration(GPIO_D, GPIO_PIN2, MODER_INPUT, OTYPER_PUSHPULL, OSPEEDR_LOW, PUPDR_PULLDOWN);

	EXTI_Config_Variables EXTI2_Config;
	EXTI2_Config.EXTI_port = EXTIx_PD_PIN;
	EXTI2_Config.EXTI_line = EXTI_LINE_2;
	EXTI2_Config.trigger_type = RISING_TRIGGER;
	EXTI2_Config.mask_event = NOT_MASKED;
	EXTI2_Config.mask_it = NOT_MASKED;

	EXTI_Configuration(EXTI2_Config);

	NVIC_Config_Variables NVIC_Config2;
	NVIC_Config2.IRQNumber = _EXTI2_IRQHandler;
	NVIC_Config2.IRQPriority = 0x04;
	NVIC_Config2.IRQEnable = ENABLE;


	// NVIC configuration for EXTI2
	NVIC_Configuration(NVIC_Config2);

	// setup timer3
	Timer_Configuration(TIMER3, TIMER_1MS);

	NVIC_Config_Variables NVIC_Config3;
	NVIC_Config3.IRQNumber = _TIM3_IRQHandler;
	NVIC_Config3.IRQPriority = 0x03;
	NVIC_Config3.IRQEnable = ENABLE;

	NVIC_Configuration(NVIC_Config3);

	// PA8 - TIM3CH1 config input rising
	// GPIO_Configuration(GPIO_A, GPIO_PIN4, MODER_INPUT, OTYPER_PUSHPULL, OSPEEDR_HIGH, PUPDR_PULLUP);
	// GPIO_ConfigAlternateFunc(GPIO_A, GPIO_PIN8, AF1);
	// Timer_InputCaptureConfiguration(timer1, TIMER_CHANNEL_1, TI_1, IP_FALLING_TRIGGERED, IP_PRESCALER_DISABLE, ENABLE, ENABLE);
	// Timer_Configuration(timer1, TIMER_1MS);

	// Output compare -> create a signal with a frequency of 100Hz using Timer2, channel 1 -> PA5
	// GPIO_ConfigAlternateFunc(GPIO_A, GPIO_PIN5, AF1);
	// Timer_OutputCompareConfiguration(timer2, TIMER_CHANNEL_1, OC_MODE_TOGGLE, 1599, 999);

	USART_Config_Variables USART2_Config;
	USART2_Config.usart_x = USART2;
	USART2_Config.baudrate = BAUDRATE_9600;
	USART2_Config.wordlength = DATA_BITS_8;
	USART2_Config.over8 = OVERSAMPLING_BY_16;
	USART2_Config.paritycontrol = PARITY_DISABLE;
	USART2_Config.paritytype = EVEN_PARITY;

	USART_Configuration(USART2_Config);
	USART_ReceiverDataInterruptEnable(USART2);
	// USART_TransmiterDataInterruptEnable(USART2);
	// NVIC_Configuration(_USART2_IRQHandler, 0x01, ENABLE);

	// SPI
	SPI_Config_Variables SPI1_Config;
	SPI1_Config.spi_x = SPI1;
	SPI1_Config.spi_mode = MASTER_MODE;
	SPI1_Config.sampling_type = FIRST_CLOCK_NO_IDLE;
	SPI1_Config.clock_prescaler = BAUD_RATE_DIV_2;
	SPI1_Config.data_read_fr = LSB_FIRST;
	SPI1_Config.receive_mode = FULL_DUPLEX_MODE;
	SPI1_Config.data_fr = DATA_BITS_8;
	SPI1_Config.slave_mode_type = SOFTWARE_SLAVE_SELECT;

	SPI_Configuration(SPI1_Config);
	// SPI_ReceiverDataInterruptEnable(SPI1);
	// GPIO_Configuration(GPIO_B, GPIO_PIN13, MODER_INPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING );
	// GPIO_Configuration(GPIO_B, GPIO_PIN12, MODER_INPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING );

	// SPI_Configuration(SPI2, SLAVE_MODE, FIRST_CLOCK_NO_IDLE, BAUD_RATE_DIV_2, LSB_FIRST, FULL_DUPLEX_MODE, DATA_BITS_8, SOFTWARE_SLAVE_SELECT);
	// SPI_ReceiverDataInterruptEnable(SPI1);
	// SPI_ReceiverDataInterruptEnable(SPI2);
	// NVIC_Configuration(_SPI1_IRQHandler, 0x08, ENABLE);
	// NVIC_Configuration(_SPI2_IRQHandler, 0x08, ENABLE);

	// // I2C
	// I2C_Configuration(i2c1, I2C_STANDARD_MODE, 16000000, 100000, I2C_DUTY_2_1);
	// LCD_I2C_Init();

	// LCD_I2C_Set_Cursor(0, 0);
	// LCD_I2C_Print("I2C Hello");
	// LCD_I2C_Set_Cursor(1,0);
	// LCD_I2C_Print("ND Thuan");

	SoftI2C_Configuration(I2C_1, I2C_MODE_WRITE);
    SoftI2C_Start(I2C_1);
	// SoftI2C_Configuration(I2C_2, I2C_MODE_WRITE);

	uint8_t ADC_Channels[7] = {ADC_CH0, ADC_CH4, ADC_CH5, ADC_CH6, ADC_CH7, ADC_CH8, ADC_CH9};

	ADC_Variables ADC1_val;
	ADC1_val.ADC_n = ADC1;
	ADC1_val.prescaler_div = ADC_CLK_DIV_2;
	ADC1_val.resolution = ADC_RESOLUTION_12BIT;
	ADC1_val.eoc_type = EOC_END_OF_CONVERSION;
	ADC1_val.dma_stop_type = DMA_CONTINUE_AFTER_LAST_CONVERSION;
	ADC1_val.data_align = DATA_RIGHT_ALIGNMENT;
	ADC1_val.sequence_length = 7;
	ADC1_val.channels = &ADC_Channels[0];
	ADC1_val.sampling_time = ADC_SPLT_3_CYCLES;
	ADC_Configuration(ADC1_val);

	DMA_Request rq;
	rq = GetStreamAndChannelForPeripheral(I2C1_RX);
	
	while (1)
	{
		LoopTimerSetting();		   // Timer loop
		LoopSystickTimerSetting(); // Systick timer loop

		if(SoftI2C_GetStartCondition(I2C_1))
			start_condition = true;
		
		// if(start_condition == true)
		// 	GPIO_SettingOutputDataBSRR(GPIO_B, GPIO_PIN4, SET);

		if(start_condition)
		{
			if(GetFlagTimer1ms())
			{
				testvalue1++;

				if(testvalue1 % 2)
				{
					GPIO_SettingOutputDataBSRR(GPIO_B, GPIO_PIN6, CLEAR);
					GPIO_SettingOutputDataBSRR(GPIO_B, GPIO_PIN7, SET);
				}
				else
				{
					GPIO_SettingOutputDataBSRR(GPIO_B, GPIO_PIN6, SET);
					GPIO_SettingOutputDataBSRR(GPIO_B, GPIO_PIN7, CLEAR);
				}
			}

			if(testvalue1 >= 16)
			{
				start_condition = false;
				SoftI2C_Stop(I2C_1);
			}
		}

		// if(SoftI2C_WriteByte(I2C_1, 0x4E))
		// {
		// 	break;
		// }
		// SoftI2C_WriteData(I2C_1, &data_init_lcd1[0], 1);
		// //I2C loop
		// if (GetFlagTimerSystick1s())
		// {
		// 	testvalue++;
		// 	if(testvalue >= 2)
		// 	{
		// 		LCD_I2C_Clear();
		// 		LCD_I2C_Set_Cursor(0,1);
		// 		LCD_I2C_Print("After 5seconds");
		// 	}
		// }


		// if(GetFlagTimer1ms())
		// {
		// 	testvalue++;

		// 	if(testvalue % 2 == 0)
		// 		GPIO_SettingOutputDataBSRR(GPIO_B, GPIO_PIN4, SET);
		// 	else
		// 		GPIO_SettingOutputDataBSRR(GPIO_B, GPIO_PIN4, CLEAR);
		// }

		// SPI
		// uint8_t *data_TX;
		// data_TX = &data;
		// char a = 'a';
		// // uint8_t data_RX[3];
		// SPI_SlaveSelect(SPI1); // B?t Slave Select
		// SPI_Transmiter(SPI1, data_TX, 1); // Gui du lieu
		// USART_SendData(USART2, a, 1);
		// // SPI_ReceiveData(SPI2, data_RX, 3);
		// SPI_SlaveDisSelect(SPI1); // T?t Slave Select
		// for (i = 0; i < 100000; i++){
		// }
	}
}
