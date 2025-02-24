#include "Peripheral/GPIO/GPIO.h"
#include "Peripheral/RCC/RCC.h"
#include "Peripheral/SystemTimer/Systick.h"
#include "Peripheral/NVIC/NVIC.h"
#include "Peripheral/SystemControlBLock/SCB.h"
#include "Peripheral/Timer/Timer.h"
#include "Peripheral/USART/USART.h"

// GPIO
GPIOn *GPIO_A = (GPIOn *)ADDRESS_GPIO_A;
GPIOn *GPIO_D = (GPIOn *)ADDRESS_GPIO_D;

// RCC
RCC *__RCC = (RCC *)ADDRESS_RCC;

// NVIC
NVIC *__NVIC = (NVIC*) ADDRESS_NVIC;

// UART
USARTn *uart4 = (USARTn *)ADDRESS_UART_4;
USARTn *uart5 = (USARTn *)ADDRESS_UART_5;

// USART
USARTn *usart1 = (USARTn *)ADDRESS_USART_1;
USARTn *usart2 = (USARTn *)ADDRESS_USART_2;
USARTn *usart3 = (USARTn *)ADDRESS_USART_3;
USARTn *usart6 = (USARTn *)ADDRESS_USART_6;

