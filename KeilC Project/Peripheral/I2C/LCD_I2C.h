#include "stdio.h"
#include "string.h"
#include "stdint.h"

void LCD_I2C_Init(void);
void LCD_I2C_Write_CMD(uint8_t data);
void LCD_I2C_Write_DATA(uint8_t data);
void LCD_I2C_Clear(void);
void LCD_I2C_Set_Cursor(uint8_t row, uint8_t col);

void LCD_I2C_Print(char *str);  // print string
