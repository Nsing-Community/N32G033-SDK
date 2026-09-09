/**
*     Copyright (c) 2025, Nsing Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nsing Technologies Inc. (Hereinafter 
* referred to as Nsing). This software, and the product of Nsing described herein 
* (Hereinafter referred to as the Product) are owned by Nsing under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     Nsing does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     Nsing reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact Nsing and obtain 
* the latest version of this software before placing orders.

*     Although Nsing has attempted to provide accurate and reliable information, Nsing assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall Nsing be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     Nsing Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify Nsing and hold Nsing 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by Nsing, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     Nsing products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
*\*\file main.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#include "main.h"
#include "log.h"
#include "n32g033.h"
#include "n32g033_gpio.h"
#include "n32g033_uart.h"
#include "n32g033_rcc.h"
#include "n32g033_iwdg.h"
#include "n32g033_flash.h"

/* Constant for BOOT */
uint32_t BootAddr,SPAddr;

/* The pointer of function */
typedef void (*pFunction)(void);


/* Function of how to jump to Boot */
void Jump_To_BOOT(void)
{
    /* Disable all interrupt */
    __disable_irq();
    
    /* Config IWDG */
    IWDG_ReloadKey();
    IWDG_WriteConfig(IWDG_WRITE_DISABLE);
    IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV256);
       
    /* Config system clock as 64M with HSI  */
    SetSysClock_HSI();    

    BootAddr = *(uint32_t*)0x1FFF0004;
    SPAddr = *(uint32_t*)0x1FFF0000;
    
    /* Set JumpBoot addr */
    pFunction JumpBoot = (pFunction)BootAddr;
    
    /* Initalize Stack Pointer */
    __set_MSP(SPAddr);
    
    /* Enable interrupt */
    __enable_irq();
    
    /* Jump to BOOT */
    JumpBoot();
}

/* Main program. */
int main(void)
{
    /* Init debug usart */
    log_init();
    /* Init a button */
    IAP_Button_Config();
    
    /* Debug information */
    printf("Jump to Boot demo start with normal state!\r\n");
    printf("If you press S(PA4),system will jump to BOOT!\r\n\r\n");
    
    /* Wait button to be pressed */
    while(IAP_Button_Read() == SET);
    printf("System jumped to BOOT!\r\n\r\n");
    
    /*Jump to BOOT */
    Jump_To_BOOT();
    
    /* Infinite loop */
    while(1);
}


/* Set system clock as 64M with HSI. */
void SetSysClock_HSI(void)
{
    /* Sets the code latency value */
    FLASH_SetLatency(FLASH_LATENCY_1);
    
    /* It is necessary to initialize the RCC peripheral to the reset state.*/
    RCC_DeInit();
    
    /* Enable HSI   */
    RCC_EnableHsi(ENABLE);
    while (RCC_WaitHsiStable() != SUCCESS)
    {
        /*  If HSI failed to start-up,the clock configuration must be wrong.
            User can add some code here to dela with this problem   */
    }
    
    /* AHB prescaler factor set to 1,HCLK = SYSCLK = 64M    */
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);
    /* APB prescaler factor set to 1,PCLK2 = HCLK = 32M  */
    RCC_ConfigPclk(RCC_HCLK_DIV2);
    
    /* Select HSI as system clock source */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_HSI);

    /* Wait till HSI is used as system clock source */
    while (RCC_GetSysclkSrc() != RCC_SYSCLK_SRC_HSI);
}

/* Init a button for test */
void IAP_Button_Config(void)
{  
    GPIO_InitType GPIO_InitStructure;

    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO,ENABLE);

    GPIO_InitStructure.Pin              = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Pull        = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Mode        = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/* Get the state of button */
uint8_t IAP_Button_Read(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_PIN_4);
}



