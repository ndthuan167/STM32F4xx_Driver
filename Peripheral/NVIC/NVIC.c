/**
 * @file NVIC.c
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Configuration for NVIC of STM32F407VGTx (ARMCortex M4)
 * @date 2024-07-11
 *
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/

#include "NVIC.h"

/**
*******************************************************************************
* @ Name : NVIC_SetInterruptEnable
* @ Parameters: NVIC *__NVIC, uint8_t IQRNumber
* @ Registers : NVIC_ISER
* @ Descriptions :
*		- Enable interrupt for specific IRQ_Hander number
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-11
*******************************************************************************
*/
void NVIC_SetInterruptEnable(NVIC *__NVIC, uint8_t IQRNumber)
{
    NVIC_SET_ENABLE_INTERRUPT(__NVIC, IQRNumber);
}

/**
*******************************************************************************
* @ Name : NVIC_ClearInterruptEnable
* @ Parameters: NVIC *__NVIC, uint8_t IQRNumber
* @ Registers : NVIC_ICER
* @ Descriptions :
*		- Clear Enable interrupt for specific IRQ_Hander number
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-11
*******************************************************************************
*/
void NVIC_ClearInterruptEnable(NVIC *__NVIC, uint8_t IQRNumber)
{
    NVIC_SET_CLEAR_ENABLE_INTERRUPT(__NVIC, IQRNumber);
}

/**
*******************************************************************************
* @ Name : NVIC_SetPendingInterrupt
* @ Parameters: NVIC *__NVIC, uint8_t IQRNumber
* @ Registers : NVIC_ISPR
* @ Descriptions :
*		- Setting pending for specific IRQ_Hander number
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-11
*******************************************************************************
*/
void NVIC_SetPendingInterrupt(NVIC *__NVIC, uint8_t IRQNumber)
{
    NVIC_SET_PENDING_INTERRUPT(__NVIC, IRQNumber);
}

/**
*******************************************************************************
* @ Name : NVIC_SetPendingInterrupt
* @ Parameters: NVIC *__NVIC, uint8_t IQRNumber
* @ Registers : NVIC_ICPR
* @ Descriptions :
*		- Setting pending for specific IRQ_Hander number
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-11
*******************************************************************************
*/
void NVIC_ClearPendingInterrupt(NVIC *__NVIC, uint8_t IRQNumber)
{
    NVIC_CLEAR_PENDING_INTERRUPT(__NVIC, IRQNumber);
}

/**
*******************************************************************************
* @ Name : NVIC_SetActiveInterrupt
* @ Parameters: NVIC *__NVIC, uint8_t IQRNumber
* @ Registers : NVIC_IABR
* @ Descriptions :
*		- Setting active interrupt for specific IRQ_Hander number
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-11
*******************************************************************************
*/
void NVIC_SetActiveInterrupt(NVIC *__NVIC, uint8_t IRQNumber)
{
    NVIC_SET_ACTIVE_INTERRUPT(__NVIC, IRQNumber);
}

/**
*******************************************************************************
* @ Name : NVIC_GetStatusInterrupt
* @ Parameters: NVIC *__NVIC, uint8_t IRQNumber, uint8_t register_read
* @ Registers : NVIC_ISER, NVIC_ICER, NVIC_ISPR, NVIC_ICPR
* @ Descriptions :
*		- Get the current status of the interrupt of specified IRQNumber
* @ Return value : uint8_t
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-11
*******************************************************************************
*/
uint8_t NVIC_GetStatusInterrupt(NVIC *__NVIC, uint8_t IRQNumber, uint8_t register_read)
{
    uint8_t value;
    uint32_t u32InterruptStatus;

    if (register_read != NVIC_PRIORITY_REGISTGER)
    {
        switch (register_read)
        {
        case NVIC_ENABLE_REGISTER:
            u32InterruptStatus = NVIC_GET_STATUS_ENABLE_INTERRUPT(__NVIC, IRQNumber);
            break;
        case NVIC_CLEAR_ENABLE_REGISTER:
            u32InterruptStatus = NVIC_GET_STATUS_CLEAR_INTERRUPT(__NVIC, IRQNumber);
            break;
        case NVIC_SET_PENDING_REGISTGER:
            u32InterruptStatus = NIVC_GET_STATUS_PENDING_INTERRUPT(__NVIC, IRQNumber);
            break;
        case NVIC_CLEAR_PENDING_REGISTGER:
            u32InterruptStatus = NVIC_GET_STATUS_CLEAR_PENDING_INTERRUPT(__NVIC, IRQNumber);
            break;
        case NVIC_ACTIVE_BIT_REGISTGER:
            u32InterruptStatus = NVIC_GET_STATUS_ACTIVE_INTERRUPT(__NVIC, IRQNumber);
            break;
        default:
            break;
        }
        value = (u32InterruptStatus & (1 << (IRQNumber % 32 - 1)));
        value = value >> ((IRQNumber % 32 - 1));
        return value;
    }
    else
    {
        return NVIC_GET_PRIORITY_INTERUPT(__NVIC, IRQNumber);
    }
}

/**
*******************************************************************************
* @ Name : NVIC_SetPriority
* @ Parameters: NVIC *__NVIC, uint8_t IRQNumber, uint8_t priority
* @ Registers : NVIC_IPR
* @ Descriptions :
*		- Set priority for IRQNumber
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-11
*******************************************************************************
*/
void NVIC_SetPriority(NVIC *__NVIC, uint8_t IRQNumber, uint8_t priority)
{
    NVIC_SET_PRIORITY_INTERUPT(__NVIC, IRQNumber, priority);
}

/**
*******************************************************************************
* @ Name : NVIC_Init
* @ Parameters: NVIC *__NVIC, uint8_t IRQNumber
* @ Registers : NVIC_ICER, NVIC_ICPR, NVIC_IPR
* @ Descriptions :
*		- Clear interrupt enable, clear pending, reset priority.
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-11
*******************************************************************************
*/
void NVIC_Init(NVIC *__NVIC, uint8_t IRQNumber)
{
    NVIC_ClearInterruptEnable(__NVIC, IRQNumber);
    NVIC_ClearPendingInterrupt(__NVIC, IRQNumber);
    NVIC_SetPriority(__NVIC, IRQNumber, 0x00);
}

/**
*******************************************************************************
* @ Name : NVIC_Configuration
* @ Parameters: NVIC *__NVIC, uint8_t IRQNumber, uint8_t priority, uint8_t enable
* @ Registers : NVIC_ISER, NVIC_IPR, NVIC_ICER
* @ Descriptions :
*		- Config NVIC for specific IRQNumber:
*           + IRQNumber: 0 ~ 239
*           + priority: uint8_t(0~255)
*           + enable: 0: disable, 1: enable
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2024-07-11
*******************************************************************************
*/
void NVIC_Configuration(NVIC *__NVIC, uint8_t IRQNumber, uint8_t priority, uint8_t enable)
{
    NVIC_Init(__NVIC, IRQNumber);
    if (enable)
    {
        NVIC_SetInterruptEnable(__NVIC, IRQNumber);
        NVIC_SetPriority(__NVIC, IRQNumber, priority);
    }
    else
    {
        NVIC_ClearInterruptEnable(__NVIC, IRQNumber);
    }
    NVIC_ClearPendingInterrupt(__NVIC, IRQNumber);
}
