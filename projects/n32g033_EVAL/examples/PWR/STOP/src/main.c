/**
*     Copyright (c) 2023, Nsing Technologies Inc.
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
*\*\file main.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nsing Technologies Inc. All rights reserved.
**/
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include "log.h"
#include "delay.h"

void KeyInputExtiInit(GPIO_Module* GPIOx, uint16_t Pin);
ErrorStatus SetSysClockToHSI(uint32_t hsi_pres);


int main(void)
{
    /* At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_n32g033.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_n32g033.c file */
    /* Enable PWR Clock */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_PWR, ENABLE);
    /* Initialize LEDs on n32g033-EVAL board */
    log_init();
    log_info("\n PWR_STOP INIT ");
    /* Initialize Key button Interrupt to wakeUp stop */
    KeyInputExtiInit(KEY_INPUT_PORT, KEY_INPUT_PIN);

    while (1)
    {
        /* Insert a long delay */
        SysTick_Delay_Ms(2000);

        log_info("\n STOP ENTRY ");
        PWR_EnterSTOPMode(PWR_STOPENTRY_WFI);
        SetSysClockToHSI(RCC_SYSCLK_PRES_DIV1);
        log_init();
        log_info("\n STOP EXIT ");
    }
}




/**
*\*\name    SetSysClockToHSI.
*\*\fun     Selects HSI as System clock source and configure HCLK, PCLK prescalers.
*\*\param   hsi_pres
*\*\	     - RCC_SYSCLK_PRES_DIV1       HSI divide 1 used as system clock
*\*\	     - RCC_SYSCLK_PRES_DIV2       HSI divide 2 used as system clock
*\*\return  none 
**/
ErrorStatus SetSysClockToHSI(uint32_t hsi_pres)
{
    uint32_t timeout_value = 0xFFFFFFFF; 
    ErrorStatus HSIStartUpStatus;
   
    RCC_EnableHsi(ENABLE);

    /* Wait till HSI is ready */
    HSIStartUpStatus = RCC_WaitHsiStable();

    if (HSIStartUpStatus == SUCCESS)
    {
        /* Flash 1 wait state */
        FLASH_SetLatency(FLASH_LATENCY_1);

        /* HCLK = SYSCLK */
        RCC_ConfigHclk(RCC_SYSCLK_DIV1);

        /* PCLK2*/
        if(hsi_pres == RCC_SYSCLK_PRES_DIV2)
        {
            RCC_ConfigPclk(RCC_HCLK_DIV1);
        }
        else 
        {
            RCC_ConfigPclk(RCC_HCLK_DIV2);
        }
        
        RCC_ConfigSysclkPres(hsi_pres);

        
        /* Select HSI as system clock source */
        RCC_ConfigSysclk(RCC_SYSCLK_SRC_HSI);
           
        /* Wait till HSI is used as system clock source */
        while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_HSI)
        {
            if ((timeout_value--) == 0)
            {
                return ERROR;
            }
        }
        
        if(hsi_pres == RCC_SYSCLK_PRES_DIV2)
        {
            /* Flash 0 wait state */
            FLASH_SetLatency(FLASH_LATENCY_0);
        }
       
    }
    else
    {
        /* If HSI fails to start-up, the application will have wrong clock
           configuration. User can add here some code to deal with this error */
        return ERROR;
    }
    return SUCCESS;
}

/**
*\*\name    KeyInputExtiInit.
*\*\fun     Configures key GPIO.
*\*\param   GPIOx
*\*\param   Pin
*\*\return  none
**/
void KeyInputExtiInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;
   
    
    /* Enable the GPIO Clock */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO, ENABLE);

    /*Configure the GPIO pin as input floating*/
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);

    /*Configure key EXTI Line to key input  Pin*/
    GPIO_ConfigEXTILine(GPIOA_PORT_SOURCE, GPIO_PIN_SOURCE0);

    /*Configure key EXTI line*/
    EXTI_InitStructure.EXTI_Line = EXTI_LINE0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    /*Set key input interrupt priority*/
    NVIC_InitStructure.NVIC_IRQChannel                   = EXTI0_6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

