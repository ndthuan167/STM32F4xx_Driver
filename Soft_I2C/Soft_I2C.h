#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "stdbool.h"

#define I2C_1   0
#define I2C_2   1
#define I2C_3   2

#define I2C_MODE_WRITE  0
#define I2C_MODE_READ   1


#define NOTHING_EDGE    0
#define RISING_EDGE     1
#define FALLING_EDGE    2

void SoftI2C_GPIOConfiguration(uint8_t I2Cx, uint8_t modeRW);
void SoftI2C_Init(uint8_t I2Cx);
void SoftI2C_Start(uint8_t I2Cx);
void SoftI2C_Stop(uint8_t I2Cx);

void SoftI2C_ClockGeneration(uint8_t I2Cx);
void SoftI2C_Configuration(uint8_t I2Cx, uint8_t modeRW);

uint8_t SoftI2C_DetectRisingEdge(uint8_t I2Cx);
uint8_t SoftI2C_DetecFallingEdgeForSecond(uint8_t I2Cx);
bool SoftI2C_WriteByte(uint8_t I2Cx, uint8_t data);
void SoftI2C_WriteData(uint8_t I2Cx, uint8_t* data, uint8_t size);


bool SoftI2C_GetStartCondition(uint8_t I2Cx);
bool SoftI2C_GetStopCondition(uint8_t I2Cx);

