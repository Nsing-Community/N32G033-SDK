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

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
uint32_t SRC_Buffer[3] = {0, 0, 0};
uint32_t TimerPeriod   = 0;

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

    /* DMA Configuration */
    DMA_Configuration();

    /* 
    TIMx DMA Transfer example
    TIMxCLK = SystemCoreClock, Prescaler = 0, TIMx counter clock = SystemCoreClock.

    The objective is to configure TIMx channel 3 to generate complementary PWM
    signal with a frequency equal to x Hz:
     - TIMx_Period = (SystemCoreClock / x) - 1
    and a variable duty cycle that is changed by the DMA after a specific number of
    Update DMA request.

    The number of this repetitive requests is defined by the TIMx Repetition counter,
    each 3 Update Requests, the TIMx Channel 3 Duty Cycle changes to the next new
    value defined by the SRC_Buffer .
    */
    
    /* Compute the value to be set in AR register to generate signal frequency at x hz */
    TimerPeriod = (SystemCoreClock / 8000) - 1;
    /* Compute CCDAT1 value to generate a duty cycle at 50% */
    SRC_Buffer[0] = (uint16_t)(((uint32_t)5 * (TimerPeriod - 1)) / 10);
    /* Compute CCDAT1 value to generate a duty cycle at 37.5% */
    SRC_Buffer[1] = (uint16_t)(((uint32_t)375 * (TimerPeriod - 1)) / 1000);
    /* Compute CCDAT1 value to generate a duty cycle at 25% */
    SRC_Buffer[2] = (uint16_t)(((uint32_t)25 * (TimerPeriod - 1)) / 100);

    /* Time Base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);    
    TIM_TimeBaseStructure.Prescaler     = 0;
    TIM_TimeBaseStructure.CounterMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period        = TimerPeriod;
    TIM_TimeBaseStructure.ClkDiv        = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.RepetCnt      = 5;
    TIM_InitTimeBase(TIMx, &TIM_TimeBaseStructure);   

     /* Channel 3 Configuration in PWM mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);     
    TIM_OCInitStructure.OCMode       = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = SRC_Buffer[0];
    TIM_OCInitStructure.OCPolarity   = TIM_OC_POLARITY_HIGH;
    TIM_OCInitStructure.OCNPolarity  = TIM_OCN_POLARITY_HIGH;
    TIM_OCInitStructure.OCIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OCNIdleState = TIM_OCN_IDLE_STATE_RESET;
    TIM_InitOc3(TIMx, &TIM_OCInitStructure);   
    
    /* TIMx Update DMA Request enable */
    TIM_EnableDma(TIMx, TIM_DMA_UPDATE, ENABLE);

    /* TIMx counter enable */
    TIM_Enable(TIMx, ENABLE);

    /* Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIMx, ENABLE);  
    
    while (1);

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
    RCC_EnableAPBPeriphClk(TIMx_CH3_GPIO_CLK | TIMx_CH3N_GPIO_CLK,ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA,ENABLE);
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
    GPIO_InitStructure.Pin              = TIMx_CH3_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = TIMx_CH3_GPIO_AF;
    GPIO_InitPeripheral(TIMx_CH3_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = TIMx_CH3N_GPIO_PIN;
    GPIO_InitStructure.GPIO_Alternate = TIMx_CH3N_GPIO_AF;
    GPIO_InitPeripheral(TIMx_CH3N_GPIO_PORT, &GPIO_InitStructure);
}

/**
*\*\name    DMA_Configuration.
*\*\fun     Configures the GPIO pins.
*\*\param   none
*\*\return  none 
**/
void DMA_Configuration(void)
{
    DMA_InitType DMA_InitStructure;

    /* DMA Channel1 Config */
    DMA_DeInit(DMA_CH1);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&TIMx->CCDAT3;
    DMA_InitStructure.MemAddr        = (uint32_t)SRC_Buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = 3;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_WORD;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_Word;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;

    DMA_Init(DMA_CH1, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_TIM1_UP,DMA,DMA_CH1,ENABLE);
    /* DMA Channel1 enable */
    DMA_EnableChannel(DMA_CH1, ENABLE);
}
