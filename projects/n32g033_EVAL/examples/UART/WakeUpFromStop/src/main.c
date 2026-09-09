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
#include <stdio.h>
#include "main.h"
#include "delay.h"

UART_InitType UART_InitStructure;
EXTI_InitType EXTI_InitStructure;

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    uint32_t cnt_temp = 0;
    /* At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_n32g033.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_n32g033.c file */
    
    /* Enable PWR/UART3/GPIO Clock */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_PWR | RCC_APB_PERIPH_UART3 | RCC_APB_PERIPH_GPIO, ENABLE);

    /* Configure the GPIO ports */
    GPIO_Configuration();
    
    /*Configure key EXTI line*/
    EXTI_InitStructure.EXTI_Line = EXTI_LINE10;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
    
    /* Configure the system clock as LSI */
    SetSysClock_LSI();
    /* Choose LSI as the clock source for UART3 */
    RCC_ConfigUart3Clk(RCC_UART3_CLKSRC_LSI);
    /* UARTy configuration */
    UART_StructInit(&UART_InitStructure);
    UART_InitStructure.BaudRate   = 2000;
    UART_InitStructure.WordLength = UART_WL_8B;
    UART_InitStructure.StopBits   = UART_STPB_1;
    UART_InitStructure.Parity     = UART_PE_NO;
    UART_InitStructure.OverSampling  = UART_16OVER;
    UART_InitStructure.Mode       = UART_MODE_RX | UART_MODE_TX;
    /* Configure UARTy */
    UART_Init(UARTy, &UART_InitStructure);
    /* Enable the UARTy */
    UART_Enable(UARTy, ENABLE);

    while (1)
    {
        /* Insert a long delay */
        SysTick_Delay_Ms(1000);
        
        if(UART_GetFlagStatus(UART3,UART_FLAG_RXDNE) == SET)
        {
            if(UART_ReceiveData(UART3) == 0x55)
            {
                /* configure uart3 wakeup mode */
                UART_CfgWakeupMode(UART3,UART_WAKEUP_DATACLR,UART_WAKEUP_ENABLE);
                /* Enter STOP mode */
                PWR_EnterSTOPMode(PWR_STOPENTRY_WFE);
                /* Configure UARTy and UARTz */
                UART_DeInit(UARTy);
                UART_Init(UARTy, &UART_InitStructure);
                /* Enable the UARTy and UARTz */
                UART_Enable(UARTy, ENABLE);
            }
        }
        else
        {
            UART_SendData(UART3,cnt_temp++);
        }
        
        /* Overflow data loss */
        if(UART_GetFlagStatus(UARTy, UART_FLAG_OREF) != RESET)
        {
            UARTy->DAT;
        }
    }
}


/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports.
*\*\param   none
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);
    
    /* Configure UARTy Tx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = UARTy_TxPin;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = UARTy_Tx_GPIO_AF;
    GPIO_InitPeripheral(UARTy_GPIO, &GPIO_InitStructure);

    /* Configure UARTx Rx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = UARTy_RxPin;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = UARTy_Rx_GPIO_AF;
    GPIO_InitPeripheral(UARTy_GPIO, &GPIO_InitStructure);          
}


/**
*\*\name    SetSysClock_LSI.
*\*\fun     Selects LSI as System clock source and configure HCLK, PCLK2
*\*\         and PCLK1 prescalers.
*\*\param   none
*\*\return  none 
**/
ErrorStatus SetSysClock_LSI(void)
{
    uint32_t timeout_value = 0xFFFFFFFF; 
    
    /* Wait till LSI is ready */
    if (RCC_GetFlagStatus(RCC_CLKINT_FLAG_LSIRDF) == SET)
    {
        /* HCLK = SYSCLK */
        RCC_ConfigHclk(RCC_SYSCLK_DIV1);

        /* PCLK = HCLK */
        RCC_ConfigPclk(RCC_HCLK_DIV1);
    
        RCC_ConfigSysclk(RCC_SYSCLK_SRC_LSI);
        while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_LSI)
        {
            if ((timeout_value--) == 0)
            {
                return ERROR;
            }
        }
        
        FLASH_SetLatency(FLASH_LATENCY_0);
    }
    else
    {
        /* If LSI fails to start-up, the application will have wrong clock
           configuration. User can add here some code to deal with this error */
        return ERROR;
    }
    return SUCCESS;

}

