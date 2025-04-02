#include "LCD_I2C.h"
#include "../I2C/I2C.h"
#include "../SystemTimer/Systick.h"

#define LCD_Slave_Addr 0x27
I2C* i2c1_lcd = (I2C*)ADDRESS_I2C1;
uint8_t index_lcd;

uint8_t data_init_lcd[6] = {0x33, 0x32, 0x28, 0x0C, 0x06, 0x01};

void LCD_I2C_Write_CMD(uint8_t data)
{
	uint8_t buf[4] = {(data & 0xF0) | 0x04, (data & 0xF0) | 0x00, (data << 4) | 0x04, (data << 4) | 0x00};
	I2C_TransmitData(i2c1_lcd, LCD_Slave_Addr, buf, 4);
}

void LCD_I2C_Init(void)
{
	for (index_lcd = 0; index_lcd < 6; index_lcd++)
	{
		LCD_I2C_Write_CMD(data_init_lcd[index_lcd]);
	}
}
void LCD_I2C_Write_DATA(uint8_t data)
{
	uint8_t buf[4] = {(data & 0xF0) | 0x05, (data & 0xF0) | 0x01, (data << 4) | 0x05, (data << 4) | 0x01};
	I2C_TransmitData(i2c1_lcd, LCD_Slave_Addr, buf, 4);
}

void LCD_I2C_Clear(void)
{
	LCD_I2C_Write_CMD(0x01);
	if (GetFlagTimerSystick500ms()) // wait to clear
	{
	};
}

void LCD_I2C_Set_Cursor(uint8_t row, uint8_t col)
{
	if (row == 0)
		LCD_I2C_Write_CMD(0x80 + col);
	else if (row == 1)
		LCD_I2C_Write_CMD(0xC0 + col);
}

void LCD_I2C_Print(char *str)  // print string
{
	for (index_lcd = 0; index_lcd < strlen(str); index_lcd++)
	{
		LCD_I2C_Write_DATA(str[index_lcd]);
	}
}

