#include "Soft_SPI.h"
#include "../GPIO/GPIO.h"
#include "../RCC/RCC.h"
#include "../SystemTimer/Systick.h"
#include "../USART/USART.h"
#include "math.h"

GPIOn * gpio_A_SSPI = (GPIOn*)ADDRESS_GPIO_A;
GPIOn * gpio_B_SSPI = (GPIOn*)ADDRESS_GPIO_B;
GPIOn * gpio_C_SSPI = (GPIOn*)ADDRESS_GPIO_C;

USARTn *usart_spi_2 = (USARTn*) ADDRESS_USART_2;

uint8_t clk_div = 0;
uint8_t pre_clk = 0;
uint8_t crr_clk = 0;
uint8_t nxt_pre_clk = 0;
uint8_t nxt_crr_clk = 0;

uint8_t re_crr_clk = 0;
uint8_t re_pre_clk = 0;

uint8_t bin_index = 1;
uint8_t first_bit_sent = 0;
uint8_t from_second_bit = 0;

bool sampling_second_edge = false;

uint8_t sampling_type_set = SAMPLING_TYPE_1_EDGE_RISING;
uint8_t read_data_type_set = MSB_FIRST;
uint8_t first_edge = RISING_EDGE;
uint8_t second_edge = FALLING_EDGE;
uint8_t index_first_bit;


uint8_t index_recevier = 0;
uint16_t j;

void SoftSPI_Master_GPIO_Configuration(uint8_t spi_n)
{
    switch (spi_n)
    {
        case SOFT_SPI1:
            RCC_EnablePeripheralClock(CLOCK_GPIO_A);
            // PA4 -> SPI1_NSS, PA5 -> SPI1_SCK, PA6 -> SPI1_MISO, PA7 -> SPI1_MOSI
            GPIO_Configuration(gpio_A_SSPI, GPIO_PIN4, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_LOW, PUPDR_NOTHING);      // CS
            GPIO_Configuration(gpio_A_SSPI, GPIO_PIN5, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING); // SCK
            GPIO_Configuration(gpio_A_SSPI, GPIO_PIN6, MODER_INPUT,  OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING); // MISO
            GPIO_Configuration(gpio_A_SSPI, GPIO_PIN7, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING); // MOSI
        break;
        case SOFT_SPI2:
            RCC_EnablePeripheralClock(CLOCK_GPIO_B);
            // PB12 -> SPI2_NSS, PB13 -> SPI2_SCK, PB14 -> SPI2_MISO, PB15 -> SPI2_MOSI
            GPIO_Configuration(gpio_B_SSPI, GPIO_PIN12, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_LOW, PUPDR_NOTHING);      // CS
            GPIO_Configuration(gpio_B_SSPI, GPIO_PIN13, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING); // SCK
            GPIO_Configuration(gpio_B_SSPI, GPIO_PIN14, MODER_INPUT,  OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING); // MISO
            GPIO_Configuration(gpio_B_SSPI, GPIO_PIN15, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING); // MOSI
        break;
        case SOFT_SPI3:
            RCC_EnablePeripheralClock(CLOCK_GPIO_A);
            RCC_EnablePeripheralClock(CLOCK_GPIO_C);

            // PA15 -> SPI3_NSS, PC10 -> SPI3_SCK, PC11 -> SPI3_MISO, PC12 -> SPI3_MOSI
            GPIO_Configuration(gpio_A_SSPI, GPIO_PIN15, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_LOW, PUPDR_NOTHING);      // CS
            GPIO_Configuration(gpio_C_SSPI, GPIO_PIN10, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING); // SCK
            GPIO_Configuration(gpio_C_SSPI, GPIO_PIN11, MODER_INPUT,  OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING); // MISO
            GPIO_Configuration(gpio_C_SSPI, GPIO_PIN12, MODER_OUTPUT, OTYPER_PUSHPULL, OSPEEDR_VERYHIGH, PUPDR_NOTHING); // MOSI 
        break;
        default:
        break;
    }
}


void SoftSPI_ClockGeneration(uint8_t spi_n)
{
	if(GetFlagTimerSystick50ms())
	{
		clk_div++;
		if(clk_div % 2 == 0)
        {
            switch (spi_n)
            {
                case SOFT_SPI1:
                    GPIO_SettingOutputDataBSRR(gpio_A_SSPI, GPIO_PIN5, CLEAR);
                break;
                case SOFT_SPI2:
                    GPIO_SettingOutputDataBSRR(gpio_B_SSPI, GPIO_PIN13, CLEAR);
                break;
                case SOFT_SPI3:
                    GPIO_SettingOutputDataBSRR(gpio_C_SSPI, GPIO_PIN10, CLEAR);
                break;
                
                default:
                break;
            }
        }
		else
        {
            switch (spi_n)
            {
                case SOFT_SPI1:
			        GPIO_SettingOutputDataBSRR(gpio_A_SSPI, GPIO_PIN5, SET);
                break;
                case SOFT_SPI2:
                    GPIO_SettingOutputDataBSRR(gpio_B_SSPI, GPIO_PIN13, SET);
                break;
                case SOFT_SPI3:
                    GPIO_SettingOutputDataBSRR(gpio_C_SSPI, GPIO_PIN10, SET);
                break;
                
                default:
                break;
            }
        }
	}
}

void SoftSPI_SlaveSelected(uint8_t spin_n)
{
    switch (spin_n)
    {
        case SOFT_SPI1:
            GPIO_SettingOutputDataBSRR(gpio_A_SSPI, GPIO_PIN4, CLEAR);
        break;
        case SOFT_SPI2:
            GPIO_SettingOutputDataBSRR(gpio_B_SSPI, GPIO_PIN12, CLEAR);
        break;
        case SOFT_SPI3:
            GPIO_SettingOutputDataBSRR(gpio_A_SSPI, GPIO_PIN15, CLEAR);
        break;
    }
}

void SoftSPI_SlaveDisSelected(uint8_t spin_n)
{
    switch (spin_n)
    {
        case SOFT_SPI1:
            GPIO_SettingOutputDataBSRR(gpio_A_SSPI, GPIO_PIN4, SET);
        break;
        case SOFT_SPI2:
            GPIO_SettingOutputDataBSRR(gpio_B_SSPI, GPIO_PIN12, SET);
        break;
        case SOFT_SPI3:
            GPIO_SettingOutputDataBSRR(gpio_A_SSPI, GPIO_PIN15, SET);
        break;
    }
}

void HexToBinConvert(uint8_t hex, uint8_t *bin)
{
    int j;

    for (j = 7; j >= 0; j--)
    {
        if ((hex >> j) & 0x01)
            bin[7  - j] = '1';
        else
            bin[7 - j] = '0';
    }

    bin[8] = '\0'; // Null-terminate the binary string
}

uint8_t SoftSPI_EdgeDetection(uint8_t spin_n)
{
    uint8_t edge = NOTHING_EDGE;

    switch (spin_n)
    {
        case SOFT_SPI1:
            crr_clk = GPIO_GetDataInOutputRes(gpio_A_SSPI, GPIO_PIN5);
        break;
        case SOFT_SPI2:
            crr_clk = GPIO_GetDataInOutputRes(gpio_B_SSPI, GPIO_PIN13);
        break;
        case SOFT_SPI3:
            crr_clk = GPIO_GetDataInOutputRes(gpio_C_SSPI, GPIO_PIN10);
        break;
        default:
        break;
    }

    if(crr_clk == 1 && pre_clk == 0)
        edge = RISING_EDGE;
    if(crr_clk == 0 && pre_clk == 1)
        edge = FALLING_EDGE;

    pre_clk = crr_clk;

    return edge;
}

uint8_t SoftSPI_FromSecEdgeDetection(uint8_t spin_n)
{
    uint8_t edge = NOTHING_EDGE;

    switch (spin_n)
    {
        case SOFT_SPI1:
            nxt_crr_clk = GPIO_GetDataInOutputRes(gpio_A_SSPI, GPIO_PIN5);
        break;
        case SOFT_SPI2:
            nxt_crr_clk = GPIO_GetDataInOutputRes(gpio_B_SSPI, GPIO_PIN13);
        break;
        case SOFT_SPI3:
            nxt_crr_clk = GPIO_GetDataInOutputRes(gpio_C_SSPI, GPIO_PIN10);
        break;
        default:
        break;
    }

    if(nxt_crr_clk == 1 && nxt_pre_clk == 0)
        edge = RISING_EDGE;
    if(nxt_crr_clk == 0 && nxt_pre_clk == 1)
        edge = FALLING_EDGE;

    nxt_pre_clk = nxt_crr_clk;

    return edge;
}

uint8_t SoftSPI_GetCSStatus(uint8_t spi_n)
{
    uint8_t cs_selected = 0;

    switch (spi_n)
    {
        case SOFT_SPI1:
            cs_selected = GPIO_GetDataInOutputRes(gpio_A_SSPI, GPIO_PIN4);
            break;
        case SOFT_SPI2:
            cs_selected = GPIO_GetDataInOutputRes(gpio_B_SSPI, GPIO_PIN12);
            break;
        case SOFT_SPI3:
            cs_selected = GPIO_GetDataInOutputRes(gpio_A_SSPI, GPIO_PIN15);
            break;
        default:
            break;
    }

    return cs_selected;

}

void SoftSPI_SetMOSI(uint8_t spin_n, uint8_t status)
{
    switch (spin_n)
    {
        case SOFT_SPI1:
            if(status == SET)
                GPIO_SettingOutputDataBSRR(gpio_A_SSPI, GPIO_PIN7, SET);
            else
                GPIO_SettingOutputDataBSRR(gpio_A_SSPI, GPIO_PIN7, CLEAR);
        break;
        case SOFT_SPI2:
            if(status == SET)
                GPIO_SettingOutputDataBSRR(gpio_B_SSPI, GPIO_PIN15, SET);
            else
                GPIO_SettingOutputDataBSRR(gpio_B_SSPI, GPIO_PIN15, CLEAR);
        break;
        case SOFT_SPI3:
            if(status == SET)
                GPIO_SettingOutputDataBSRR(gpio_C_SSPI, GPIO_PIN12, SET);
            else
                GPIO_SettingOutputDataBSRR(gpio_C_SSPI, GPIO_PIN12, CLEAR);
        break;
    }
}

uint8_t SoftSPI_Master_GetMISOData(uint8_t spi_n)
{
    uint8_t MISO_value;
        switch (spi_n)
        {
        case SOFT_SPI1:
            MISO_value = GPIO_GetInputData(gpio_A_SSPI, GPIO_PIN6);
            break;
        
        case SOFT_SPI2:
            MISO_value = GPIO_GetInputData(gpio_B_SSPI, GPIO_PIN14);
            break;
        
        case SOFT_SPI3:
            MISO_value = GPIO_GetInputData(gpio_C_SSPI, GPIO_PIN11);
            break;
        
        default:
            break;
    }

    return MISO_value;
}

bool SoftSPI_Master_TransmiterRecevier(uint8_t spi_n, uint8_t data, uint8_t size)
{
    bool bReturn = false;
    uint8_t cs_status = SoftSPI_GetCSStatus(spi_n);
    uint8_t bin_data[8];
    uint8_t m_RX_bits;

    HexToBinConvert(data, bin_data);  // Convert the hexadecimal value to a binary string

    if(cs_status == CLEAR)  // Slave Selected
    {
        if(sampling_second_edge == true)    // start send data to MOSI after 1 cycle clock if sampling type is second edge
        {
            if(GetFlagTimerSystick100ms())
            {
                sampling_second_edge = false;
            }
        }

        if(sampling_second_edge == false)
        {
            if(SoftSPI_EdgeDetection(spi_n) == first_edge)
            {
                if(first_bit_sent == 0)
                {
                    first_bit_sent = 1;
                    if(bin_data[index_first_bit] == 0x30)    // first bit (MSB))
                    {
                        SoftSPI_SetMOSI(spi_n, CLEAR);
                    }
                    else if(bin_data[index_first_bit] == 0x31)
                    {
                        SoftSPI_SetMOSI(spi_n, SET);
                    }
                }

                // master receiver
                for (j = 0; j < 100; j++){} // delay for stable data
                if (SoftSPI_Master_GetMISOData(spi_n) == SET)   // Read MISO
                    m_RX_bits = 0x01 + '0';
                else
                    m_RX_bits = 0x00 + '0';
                USART_SendData(usart_spi_2, &m_RX_bits, 1);

            }

            if((SoftSPI_FromSecEdgeDetection(spi_n) == second_edge)
            && first_bit_sent == 1)
            {
                from_second_bit = 1;
                if(bin_data[abs(bin_index - index_first_bit)] == 0x30)
                {
                    SoftSPI_SetMOSI(spi_n, CLEAR);
                }
                else if(bin_data[abs(bin_index - index_first_bit)] == 0x31)
                {
                    SoftSPI_SetMOSI(spi_n, SET);
                }
            }

            if(from_second_bit == 1)
            {
                if(GetFlagTimerSystick100ms())
                {
                    bin_index++;
                    index_recevier++;
                    if(bin_index > 8)
                    {
                        bin_index = 1;
                        first_bit_sent = 0;
                        from_second_bit = 0;
                        bReturn = true;
                    }
                }
            }
            else
            {
                if(GetFlagTimerSystick100ms())
                    index_recevier++;
            }

            // Convert RX_data to Hex and send to USART
            if(index_recevier >= 8)
            {
                // USART_SendData(usart_spi_2, &hex_str, strlen(hex_str));
                USART_SendData(usart_spi_2, " ", 1);
                index_recevier = 0;
            }
        }
    }

    return bReturn;
}

void SoftSPI_Master_Configuration(uint8_t spin_n, uint8_t sampling_type, uint8_t read_data_type)
{
// GPIO_configuration
    SoftSPI_Master_GPIO_Configuration(spin_n);
    sampling_type_set = sampling_type;

    if(sampling_type_set == SAMPLING_TYPE_1_EDGE_RISING)
    {
        first_edge = RISING_EDGE;
        second_edge = FALLING_EDGE;
    }
    else if(sampling_type_set == SAMPLING_TYPE_1_EDGE_FALLING)
    {
        first_edge = FALLING_EDGE;
        second_edge = RISING_EDGE;
    }
    else if (sampling_type_set == SAMPLING_TYPE_2_EDGE_RISING)
    {
        sampling_second_edge = true;
        first_edge = RISING_EDGE;
        second_edge = FALLING_EDGE;
    }
    else if(sampling_type_set == SAMPLING_TYPE_2_EDGE_FALLING)
    {
        sampling_second_edge = true;
        first_edge = FALLING_EDGE;
        second_edge = RISING_EDGE;
    }

    read_data_type_set = read_data_type;

    if(read_data_type_set == MSB_FIRST)
        index_first_bit = 0;
    else if(read_data_type_set == LSB_FIRST)
        index_first_bit = 7;

// CS Disable
    switch (spin_n)
    {
        case SOFT_SPI1:
            GPIO_SettingOutputDataBSRR(gpio_A_SSPI, GPIO_PIN4, SET);
            break;
        
        case SOFT_SPI2:
            GPIO_SettingOutputDataBSRR(gpio_B_SSPI, GPIO_PIN12, SET);
            break;
        
        case SOFT_SPI3:
            GPIO_SettingOutputDataBSRR(gpio_A_SSPI, GPIO_PIN15, SET);
            break;
    
    default:
        break;
    }

}



