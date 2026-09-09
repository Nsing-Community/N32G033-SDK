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
#include "delay.h"




void RCC_Configuration(void);
void GPIO_Configuration(void);
void EXTI_Configuration(void);
void NVIC_Configuration(void);
void COMP_Configuration(void);


/**
*\*\name    ChangeVmVp.
*\*\fun     Self Generate Puls ,by skip line connect to vp and vm if need.
*\*\return  none
**/
void ChangeVmVp(void)
{
    GPIO_SetBits(GPIOB, GPIO_PIN_0);
    GPIO_ResetBits(GPIOB, GPIO_PIN_1);
    /*Insert 50 ms delay */
    SysTick_Delay_Ms(50);
    GPIO_ResetBits(GPIOB, GPIO_PIN_0);
    GPIO_SetBits(GPIOB, GPIO_PIN_1);
    /*Insert 50 ms delay */
    SysTick_Delay_Ms(50);
}
/**
*\*\name    COMP_Configuration.
*\*\fun     Configures the comp module.
*\*\return  none
**/
void COMP_Configuration(void)
{
    COMP_InitType COMP_Initial;

    /*Initial comp*/
    COMP_StructInit(&COMP_Initial);
    COMP_Initial.InpSel     = COMP_INPSEL_PA1;
    COMP_Initial.InmSel     = COMP_INMSEL_PA0;
    COMP_Initial.SampWindow = 31;       //(0~31)
    COMP_Initial.Threshold  = 18;       //(0~31)
    COMP_Initial.FilterEn   = ENABLE;
    COMP_Initial.Hyst       = COMP_CTRL_HYST_LOW;
    COMP_Init(&COMP_Initial);
    /*Enable comp interrupt*/
    COMP_SetIntEn(ENABLE);
    COMP_Enable(ENABLE);
}
/** Main program. **/
int main(void)
{
    /* System clocks configuration --------------------------------*/
    RCC_Configuration();
    
    /* NVIC configuration -----------------------------------------*/
    NVIC_Configuration();
    
    /* GPIO configuration -----------------------------------------*/
    EXTI_Configuration();

    /* GPIO configuration -----------------------------------------*/
    GPIO_Configuration();

    /* COMP configuration -----------------------------------------*/
    COMP_Configuration();
    
    while (1)
    {
        ChangeVmVp();
    }
}



/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/

    /* Enable GPIO COMP clocks */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO | RCC_APB_PERIPH_COMP | RCC_APB_PERIPH_COMPFILT, ENABLE);

}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports.
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure  INP INM PA0 PA1 as analog input -----------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    
    /* Configure PB0 PB1 as analog input -----------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    
    /* OutSel */
    GPIO_InitStructure.Pin       = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF8;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**
*\*\name    EXTI_Configuration.
*\*\fun     Configures the EXTI line interrupt .
*\*\return  none
**/
void EXTI_Configuration(void)
{
    EXTI_InitType  EXTI_InitStructure;
    
    EXTI_InitStruct(&EXTI_InitStructure) ;
    /* Configure and enable EXTI Line */
    EXTI_InitStructure.EXTI_Line = EXTI_LINE8;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure) ;
}

/**
*\*\name    NVIC_Configuration.
*\*\fun     Configures Vector Table base location.
*\*\return  none
**/
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;
    /* Configure and enable COMP1 interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = COMP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

