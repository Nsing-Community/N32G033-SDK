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

TIM_ICInitType TIM_ICInitStructure;
uint16_t gOnePulsEn = 0;

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

     /* NVIC configuration */
    NVIC_Configuration();
 
    /* 
    TIMx configuration: Input Capture mode
     The external signal is connected to TIMx CH2 pin
     The Rising edge is used as active edge,
     The TIMx CCDAT2 is used to compute the frequency value

    gOnePulsEn = 1,will do GenTwoRisingEdge
    then see Capture that is dist time
    */

    TIM_InitIcStruct(&TIM_ICInitStructure);
    TIM_ICInitStructure.Channel     = TIM_CH_2;
    TIM_ICInitStructure.ICPolarity  = TIM_IC_POLARITY_RISING;
    TIM_ICInitStructure.ICSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStructure.ICPrescaler = TIM_IC_PSC_DIV1;
    TIM_ICInitStructure.ICFilter    = 0x0;

    TIM_ICInit(TIMx, &TIM_ICInitStructure);

    TIM_ClrIntPendingBit(TIMx,TIM_INT_UPDATE);
    TIM_ClrIntPendingBit(TIMx,TIM_INT_CC2);
    /* Enable the CC2 Interrupt Request */
    TIM_ConfigInt(TIMx, TIM_INT_CC2, ENABLE);    
    
    /* TIM enable counter */
    TIM_Enable(TIMx, ENABLE);
    
    while (1)
    {
        GenTwoRisingEdge();
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
    RCC_EnableAPBPeriphClk(TIMx_CLK,ENABLE);
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO | TIMx_CH2_GPIO_CLK,ENABLE);
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
    
    /* GPIOx Configuration: Pin of TIMx */
    GPIO_InitStructure.Pin        = TIMx_CH2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = TIMx_CH2_GPIO_AF;
    GPIO_InitPeripheral(TIMx_CH2_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
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

    /* Enable the TIMx Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                    = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority               = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
*\*\name    GenTwoRisingEdge.
*\*\fun     generation two rising edge.
*\*\param   none
*\*\return  none 
**/
void GenTwoRisingEdge(void)
{
    if (gOnePulsEn)
    {
        gOnePulsEn = 0;
        GPIO_SetBits(GPIOA, GPIO_PIN_3);
        {
           volatile uint32_t i = 0;
            while (i++ < 10)
                ;
        }
        GPIO_ResetBits(GPIOA, GPIO_PIN_3);
        {
           volatile uint32_t i = 0;
            while (i++ < 10)
                ;
        }

        GPIO_SetBits(GPIOA, GPIO_PIN_3);
        {
           volatile uint32_t i = 0;
            while (i++ < 10)
                ;
        }
        GPIO_ResetBits(GPIOA, GPIO_PIN_3);
        
    }
}

