/**
 * @file STM32F4xx_Startup.c
 * @author Nguyen Dinh Thuan (thuan.nd.167@gmail.com)
 * @brief Configure the startup code for STM32F4xx (ARM Cortex M4) microcontrollers.
 * @date 2025-05-15
 *
 */

/******************************************************************************
 * Include Files
 ******************************************************************************/

#include "stdio.h"
#include "stdint.h"

/******************************************************************************
 * ADDRESS DEFINITION
 ******************************************************************************/

#define STACK_START_ADDRESS 0x20020000 // Start address of RAM (SRAM) for STM32F4xx series microcontrollers

/******************************************************************************
 * FUNCTIONS DEFINITION
 ******************************************************************************/

// define weak attribute for interrupt handlers to allow linking with user-defined handlers in the application code
// The weak attribute allows the user to override these handlers with their own implementations if needed.

void __attribute__((weak)) Reset_Handler(void);
void __attribute__((weak)) NMI_Handler(void);
void __attribute__((weak)) HardFault_Handler(void);
void __attribute__((weak)) MemManage_Handler(void);
void __attribute__((weak)) BusFault_Handler(void);
void __attribute__((weak)) UsageFault_Handler(void);
void __attribute__((weak)) SVC_Handler(void);
void __attribute__((weak)) DebugMon_Handler(void);
void __attribute__((weak)) PendSV_Handler(void);
void __attribute__((weak)) SysTick_Handler(void);
void __attribute__((weak)) Watchdog_IRQHandler(void);
void __attribute__((weak)) PVD_IRQHandler(void);
void __attribute__((weak)) TAMP_STAMP_IRQHandler(void);
void __attribute__((weak)) RTC_WKUP_IRQHandler(void);
void __attribute__((weak)) FLASH_IRQHandler(void);
void __attribute__((weak)) RCC_IRQHandler(void);
void __attribute__((weak)) EXTI0_IRQHandler(void);
void __attribute__((weak)) EXTI1_IRQHandler(void);
void __attribute__((weak)) EXTI2_IRQHandler(void);
void __attribute__((weak)) EXTI3_IRQHandler(void);
void __attribute__((weak)) EXTI4_IRQHandler(void);
void __attribute__((weak)) DMA1_Stream0_IRQHandler(void);
void __attribute__((weak)) DMA1_Stream1_IRQHandler(void);
void __attribute__((weak)) DMA1_Stream2_IRQHandler(void);
void __attribute__((weak)) DMA1_Stream3_IRQHandler(void);
void __attribute__((weak)) DMA1_Stream4_IRQHandler(void);
void __attribute__((weak)) DMA1_Stream5_IRQHandler(void);
void __attribute__((weak)) DMA1_Stream6_IRQHandler(void);
void __attribute__((weak)) ADC_IRQHandler(void);
void __attribute__((weak)) CAN1_TX_IRQHandler(void);
void __attribute__((weak)) CAN1_RX0_IRQHandler(void);
void __attribute__((weak)) CAN1_RX1_IRQHandler(void);
void __attribute__((weak)) CAN1_SCE_IRQHandler(void);
void __attribute__((weak)) EXTI9_5_IRQHandler(void);
void __attribute__((weak)) TIM1_BRK_TIM9_IRQHandler(void);
void __attribute__((weak)) TIM1_UP_TIM10_IRQHandler(void);
void __attribute__((weak)) TIM1_TRG_COM_TIM11_IRQHandler(void);
void __attribute__((weak)) TIM1_CC_IRQHandler(void);
void __attribute__((weak)) TIM2_IRQHandler(void);
void __attribute__((weak)) TIM3_IRQHandler(void);
void __attribute__((weak)) TIM4_IRQHandler(void);
void __attribute__((weak)) I2C1_EV_IRQHandler(void);
void __attribute__((weak)) I2C1_ER_IRQHandler(void);
void __attribute__((weak)) I2C2_EV_IRQHandler(void);
void __attribute__((weak)) I2C2_ER_IRQHandler(void);
void __attribute__((weak)) SPI1_IRQHandler(void);
void __attribute__((weak)) SPI2_IRQHandler(void);
void __attribute__((weak)) USART1_IRQHandler(void);
void __attribute__((weak)) USART2_IRQHandler(void);
void __attribute__((weak)) USART3_IRQHandler(void);
void __attribute__((weak)) EXTI15_10_IRQHandler(void);
void __attribute__((weak)) RTC_Alarm_IRQHandler(void);
void __attribute__((weak)) OTG_FS_WKUP_IRQHandler(void);
void __attribute__((weak)) TIM8_BRK_TIM12_IRQHandler(void);
void __attribute__((weak)) TIM8_UP_TIM13_IRQHandler(void);
void __attribute__((weak)) TIM8_TRG_COM_TIM14_IRQHandler(void);
void __attribute__((weak)) TIM8_CC_IRQHandler(void);
void __attribute__((weak)) DMA1_Stream7_IRQHandler(void);
void __attribute__((weak)) FSMC_IRQHandler(void);
void __attribute__((weak)) SDIO_IRQHandler(void);
void __attribute__((weak)) TIM5_IRQHandler(void);
void __attribute__((weak)) SPI3_IRQHandler(void);
void __attribute__((weak)) UART4_IRQHandler(void);
void __attribute__((weak)) UART5_IRQHandler(void);
void __attribute__((weak)) TIM6_DAC_IRQHandler(void);
void __attribute__((weak)) TIM7_IRQHandler(void);
void __attribute__((weak)) DMA2_Stream0_IRQHandler(void);
void __attribute__((weak)) DMA2_Stream1_IRQHandler(void);
void __attribute__((weak)) DMA2_Stream2_IRQHandler(void);
void __attribute__((weak)) DMA2_Stream3_IRQHandler(void);
void __attribute__((weak)) DMA2_Stream4_IRQHandler(void);
void __attribute__((weak)) ETH_IRQHandler(void);
void __attribute__((weak)) ETH_WKUP_IRQHandler(void);
void __attribute__((weak)) CAN2_TX_IRQHandler(void);
void __attribute__((weak)) CAN2_RX0_IRQHandler(void);
void __attribute__((weak)) CAN2_RX1_IRQHandler(void);
void __attribute__((weak)) CAN2_SCE_IRQHandler(void);
void __attribute__((weak)) OTG_FS_IRQHandler(void);
void __attribute__((weak)) DMA2_Stream5_IRQHandler(void);
void __attribute__((weak)) DMA2_Stream6_IRQHandler(void);
void __attribute__((weak)) DMA2_Stream7_IRQHandler(void);
void __attribute__((weak)) USART6_IRQHandler(void);
void __attribute__((weak)) I2C3_EV_IRQHandler(void);
void __attribute__((weak)) I2C3_ER_IRQHandler(void);
void __attribute__((weak)) OTG_HS_EP1_OUT_IRQHandler(void);
void __attribute__((weak)) OTG_HS_EP1_IN_IRQHandler(void);
void __attribute__((weak)) OTG_HS_WKUP_IRQHandler(void);
void __attribute__((weak)) OTG_HS_IRQHandler(void);
void __attribute__((weak)) DCMI_IRQHandler(void);
void __attribute__((weak)) CRYP_IRQHandler(void);
void __attribute__((weak)) HASH_IRQHandler(void);
void __attribute__((weak)) FPU_IRQHandler(void);

void __attribute__((weak)) Default_Handler(void);

/******************************************************************************
 * VECTOR TABLE DEFINITION
 ******************************************************************************/

// Base on the STM32F4xx reference manual, the vector table is located at address 0x08000000 in Flash memory.
__attribute__((section(".isr_vector"))) // <- place the vector table in the .isr_vector section in Flash memory (0x08000000)
uint32_t *const stm32f4xx_vectors_table[] = {
    (uint32_t *)STACK_START_ADDRESS, // Initial stack pointer <- highest address of RAM
    (uint32_t *)Reset_Handler,       // 0x20020004

    // system exception handlers
    (uint32_t *)NMI_Handler,        // 0x20020008
    (uint32_t *)HardFault_Handler,  // 0x2002000C
    (uint32_t *)MemManage_Handler,  // 0x20020010
    (uint32_t *)BusFault_Handler,   // 0x20020014
    (uint32_t *)UsageFault_Handler, // 0x20020018
    (uint32_t *)0,                  // Reserved
    (uint32_t *)0,                  // Reserved
    (uint32_t *)0,                  // Reserved
    (uint32_t *)0,                  // Reserved
    (uint32_t *)SVC_Handler,        // 0x2002002C
    (uint32_t *)DebugMon_Handler,   // 0x20020030
    (uint32_t *)0,                  // Reserved
    (uint32_t *)PendSV_Handler,     // 0x20020038
    (uint32_t *)SysTick_Handler,    // 0x2002003C

    // Peripheral interrupt handlers
    (uint32_t *)Watchdog_IRQHandler,           // 0x20020040
    (uint32_t *)PVD_IRQHandler,                // 0x20020044
    (uint32_t *)TAMP_STAMP_IRQHandler,         // 0x20020048
    (uint32_t *)RTC_WKUP_IRQHandler,           // 0x2002004C
    (uint32_t *)FLASH_IRQHandler,              // 0x20020050
    (uint32_t *)RCC_IRQHandler,                // 0x20020054
    (uint32_t *)EXTI0_IRQHandler,              // 0x20020058
    (uint32_t *)EXTI1_IRQHandler,              // 0x2002005C
    (uint32_t *)EXTI2_IRQHandler,              // 0x20020060
    (uint32_t *)EXTI3_IRQHandler,              // 0x20020064
    (uint32_t *)EXTI4_IRQHandler,              // 0x20020068
    (uint32_t *)DMA1_Stream0_IRQHandler,       // 0x2002006C
    (uint32_t *)DMA1_Stream1_IRQHandler,       // 0x20020070
    (uint32_t *)DMA1_Stream2_IRQHandler,       // 0x20020074
    (uint32_t *)DMA1_Stream3_IRQHandler,       // 0x20020078
    (uint32_t *)DMA1_Stream4_IRQHandler,       // 0x2002007C
    (uint32_t *)DMA1_Stream5_IRQHandler,       // 0x20020080
    (uint32_t *)DMA1_Stream6_IRQHandler,       // 0x20020084
    (uint32_t *)ADC_IRQHandler,                // 0x20020088
    (uint32_t *)CAN1_TX_IRQHandler,            // 0x2002008C
    (uint32_t *)CAN1_RX0_IRQHandler,           // 0x20020090
    (uint32_t *)CAN1_RX1_IRQHandler,           // 0x20020094
    (uint32_t *)CAN1_SCE_IRQHandler,           // 0x20020098
    (uint32_t *)EXTI9_5_IRQHandler,            // 0x2002009C
    (uint32_t *)TIM1_BRK_TIM9_IRQHandler,      // 0x200200A0
    (uint32_t *)TIM1_UP_TIM10_IRQHandler,      // 0x200200A4
    (uint32_t *)TIM1_TRG_COM_TIM11_IRQHandler, // 0x200200A8
    (uint32_t *)TIM1_CC_IRQHandler,            // 0x200200AC
    (uint32_t *)TIM2_IRQHandler,               // 0x200200B0
    (uint32_t *)TIM3_IRQHandler,               // 0x200200B4
    (uint32_t *)TIM4_IRQHandler,               // 0x200200B8
    (uint32_t *)I2C1_EV_IRQHandler,            // 0x200200BC
    (uint32_t *)I2C1_ER_IRQHandler,            // 0x200200C0
    (uint32_t *)I2C2_EV_IRQHandler,            // 0x200200C4
    (uint32_t *)I2C2_ER_IRQHandler,            // 0x200200C8
    (uint32_t *)SPI1_IRQHandler,               // 0x200200CC
    (uint32_t *)SPI2_IRQHandler,               // 0x200200D0
    (uint32_t *)USART1_IRQHandler,             // 0x200200D4
    (uint32_t *)USART2_IRQHandler,             // 0x200200D8
    (uint32_t *)USART3_IRQHandler,             // 0x200200DC
    (uint32_t *)EXTI15_10_IRQHandler,          // 0x200200E0
    (uint32_t *)RTC_Alarm_IRQHandler,          // 0x200200E4
    (uint32_t *)OTG_FS_WKUP_IRQHandler,        // 0x200200E8
    (uint32_t *)TIM8_BRK_TIM12_IRQHandler,     // 0x200200EC
    (uint32_t *)TIM8_UP_TIM13_IRQHandler,      // 0x200200F0
    (uint32_t *)TIM8_TRG_COM_TIM14_IRQHandler, // 0x200200F4
    (uint32_t *)TIM8_CC_IRQHandler,            // 0x200200F8
    (uint32_t *)DMA1_Stream7_IRQHandler,       // 0x200200FC
    (uint32_t *)FSMC_IRQHandler,               // 0x20020100
    (uint32_t *)SDIO_IRQHandler,               // 0x20020104
    (uint32_t *)TIM5_IRQHandler,               // 0x20020108
    (uint32_t *)SPI3_IRQHandler,               // 0x2002010C
    (uint32_t *)UART4_IRQHandler,              // 0x20020110
    (uint32_t *)UART5_IRQHandler,              // 0x20020114
    (uint32_t *)TIM6_DAC_IRQHandler,           // 0x20020118
    (uint32_t *)TIM7_IRQHandler,               // 0x2002011C
    (uint32_t *)DMA2_Stream0_IRQHandler,       // 0x20020120
    (uint32_t *)DMA2_Stream1_IRQHandler,       // 0x20020124
    (uint32_t *)DMA2_Stream2_IRQHandler,       // 0x20020128
    (uint32_t *)DMA2_Stream3_IRQHandler,       // 0x2002012C
    (uint32_t *)DMA2_Stream4_IRQHandler,       // 0x20020130
    (uint32_t *)ETH_IRQHandler,                // 0x20020134
    (uint32_t *)ETH_WKUP_IRQHandler,           // 0x20020138
    (uint32_t *)CAN2_TX_IRQHandler,            // 0x2002013C
    (uint32_t *)CAN2_RX0_IRQHandler,           // 0x20020140
    (uint32_t *)CAN2_RX1_IRQHandler,           // 0x20020144
    (uint32_t *)CAN2_SCE_IRQHandler,           // 0x20020148
    (uint32_t *)OTG_FS_IRQHandler,             // 0x2002014C
    (uint32_t *)DMA2_Stream5_IRQHandler,       // 0x20020150
    (uint32_t *)DMA2_Stream6_IRQHandler,       // 0x20020154
    (uint32_t *)DMA2_Stream7_IRQHandler,       // 0x20020158
    (uint32_t *)USART6_IRQHandler,             // 0x2002015C
    (uint32_t *)I2C3_EV_IRQHandler,            // 0x20020160
    (uint32_t *)I2C3_ER_IRQHandler,            // 0x20020164
    (uint32_t *)OTG_HS_EP1_OUT_IRQHandler,     // 0x20020168
    (uint32_t *)OTG_HS_EP1_IN_IRQHandler,      // 0x2002016C
    (uint32_t *)OTG_HS_WKUP_IRQHandler,        // 0x20020170
    (uint32_t *)OTG_HS_IRQHandler,             // 0x20020174
    (uint32_t *)DCMI_IRQHandler,               // 0x20020178
    (uint32_t *)CRYP_IRQHandler,               // 0x2002017C
    (uint32_t *)HASH_IRQHandler,               // 0x20020180
    (uint32_t *)FPU_IRQHandler,                // 0x20020184
};

/**
*******************************************************************************
* @ Name : Reset_Handler
* @ Parameters: 
* @ Registers :
* @ Descriptions :
*		- Configure Reset Handler for STM32F4xx series microcontrollers with the following process:
*           1. Copy the main function from Flash to RAM
*           2. Initialize the bss section in RAM
*           3. Call the main function (user application entry point)
* @ Return value : void
* @ author : Nguyen Dinh Thuan(thuan.nd.167@gmail.com)
* @ date : 2025-05-15
*******************************************************************************
*/
void Reset_Handler(void)
{
    // Copy the main function from Flash to RAM
    extern uint32_t start_data_in_flash; // Start address of the main function in Flash memory <- PROVIDE(start_data_in_flash = LOADADDR(.data));
    extern uint32_t end_data_in_flash;   // End address of the main function in Flash memory   <- PROVIDE(end_data_in_flash = LOADADDR(.data) + SIZEOF(.data));
    extern uint32_t start_data_in_RAM; // Start address of the main function in RAM <- PROVIDE(start_data_in_RAM = ADDR(.data));
    extern uint32_t end_data_in_RAM;   // End address of the main function in RAM   <- PROVIDE(end_data_in_RAM = ADDR(.data) + SIZEOF(.data));

    uint32_t *pData_in_falsh = &start_data_in_flash; // Pointer to the start of the main function in Flash memory
    uint32_t *pData_in_RAM = &start_data_in_RAM; // Pointer to the start of the main function in RAM

    while (pData_in_falsh < &end_data_in_flash)
    {
        *pData_in_RAM++ = *pData_in_falsh++; // Copy the data from Flash to RAM
    }

    // Initialize the bss section in RAM
    extern uint32_t start_bss_in_RAM; // Start address of the bss section in RAM   <- PROVIDE(start_bss_in_RAM = ADDR(.bss));
    extern uint32_t end_bss_in_RAM;   // End address of the bss section in RAM     <- PROVIDE(end_bss_in_RAM = ADDR(.bss) + SIZEOF(.bss));

    uint32_t *pBss_in_RAM = &start_bss_in_RAM; // Pointer to the start of the bss section in RAM
    while (pBss_in_RAM < &end_bss_in_RAM)
    {
        *pBss_in_RAM++ = 0; // Zero out the bss section in RAM
    }

    // Call the main function (user application entry point)
    main();
}

void Default_Handler(void)
{
    // Infinite loop in case of an unhandled exception
    while (1)
    {
    }
}

