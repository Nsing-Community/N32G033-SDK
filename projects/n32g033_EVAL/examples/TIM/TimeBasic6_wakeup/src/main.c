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

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
uint16_t PrescalerValue = 0;

/**
*\*\name    main.
*\*\fun     main program.
*\*\param   none
*\*\return  none 
**/
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* NVIC Configuration */
    NVIC_Configuration();

    SysTick_Delay_Ms(500);
    /* Reconfig TIM6 */

    TIM_Configuration();
    RCC_ConfigTim6Clk(RCC_TIM6_CLKSRC_LSI);
    /* TIM6 enable counter */
    TIM_Enable(TIM6, ENABLE);
    
    while (1)
    {
        /* Enter STOP mode */
        PWR_EnterSTOPMode(PWR_STOPENTRY_WFI);
        GPIO_WriteBit(GPIOA, GPIO_PIN_6, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_PIN_6)));
    }
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\param   none
*\*\return  none 
**/
void RCC_Configuration(void)
{
    
    /* TIMx, GPIOx clocks enable */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_TIM6,ENABLE);
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO,ENABLE);
    
    /* PWR clock enable */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_PWR, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the GPIO pins.
*\*\param   none
*\*\return  none 
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    
    /* GPIOx Configuration */
    GPIO_InitStructure.Pin        = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**
*\*\name    NVIC_Configuration.
*\*\fun     Configures the nested vectored interrupt controller.
*\*\param   none
*\*\return  none 
**/
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;
    EXTI_InitType EXTI_Struct;

    EXTI_ClrStatusFlag(EXTI_LINE9);
    EXTI_Struct.EXTI_Line    = EXTI_LINE9;
    EXTI_Struct.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_Struct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Struct.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_Struct);
    
    /* Enable the TIMx Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority             = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
*\*\name    TIM_Configuration.
*\*\fun     Configures the TIM6.
*\*\param   none
*\*\return  none 
**/
void TIM_Configuration(void)
{
    /* Time base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period        = 3200;
    TIM_TimeBaseStructure.Prescaler     = 0;
    TIM_TimeBaseStructure.ClkDiv        = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CounterMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM6, &TIM_TimeBaseStructure);
    
    /* TIM6 enable update irq */
    TIM_ClearFlag(TIM6,TIM_FLAG_UPDATE);
    TIM_ConfigInt(TIM6, TIM_INT_UPDATE, ENABLE);
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


