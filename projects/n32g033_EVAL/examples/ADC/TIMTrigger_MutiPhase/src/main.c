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

ADC_InitType ADC_InitStructure;
__IO uint16_t ADCConvertedValue[30] ={0};
uint32_t PrescalerValue = 0;
uint32_t Pluse1_Val      = 1500;
uint32_t Pluse2_Val      = 1200;
uint32_t Pluse3_Val      = 800;
uint32_t Pluse4_Val      = 200;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void TIM_Configuration(void);

/**
*\*\name    ADC_Initial.
*\*\fun     ADC_Initial program.
*\*\return  none
**/
void ADC_Initial(void)
{
    ADC_InitStruct(&ADC_InitStructure);
    /* ADC configuration ------------------------------------------------------*/
    ADC_InitStructure.ContinueConvEn = DISABLE;
    /* Initialize the ExtTrigSelect1 member */
    ADC_InitStructure.ExtTrigSelect1 = ADC_EXT_TRIGCONV_T1_CC1;
    /* Initialize the ExtTrigSelect2 member */
    ADC_InitStructure.ExtTrigSelect2 = ADC_EXT_TRIGCONV_T1_CC2;
    /* Initialize the ExtTrigSelect3 member */
    ADC_InitStructure.ExtTrigSelect3 = ADC_EXT_TRIGCONV_T1_CC3;
    /* Initialize the ExtTrigSelect4 member */
    ADC_InitStructure.ExtTrigSelect4 = ADC_EXT_TRIGCONV_T1_CC4;
    /* Initialize the DatAlign member */
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    /* Initialize the phase mode member */
    ADC_InitStructure.PhsMode        = ADC_PHS_TRG_MODE_FOUR ;
    /* Initialize the phase 1 channel number member */
    ADC_InitStructure.Phs1ChNumber   = 2U;
    /* Initialize the phase 2 channel number member */
    ADC_InitStructure.Phs2ChNumber   = 1U;
    /* Initialize the phase 3 channel number member */
    ADC_InitStructure.Phs3ChNumber   = 1U;
    /* Initialize the phase 4 channel number member */
    ADC_InitStructure.Phs4ChNumber   = 1U;
    ADC_Init(&ADC_InitStructure);
    //PH1
    ADC_ConfigRegularChannel(ADC_Channel_01_PA1,1,ADC_SAMP_TIME_4CYCLES);
    ADC_ConfigRegularChannel(ADC_Channel_04_PA4,2,ADC_SAMP_TIME_4CYCLES);
    //PH2
    ADC_ConfigRegularChannel(ADC_Channel_00_PA0,3,ADC_SAMP_TIME_4CYCLES);
    //PH3
    ADC_ConfigRegularChannel(ADC_Channel_08_PB0,4,ADC_SAMP_TIME_4CYCLES);
    //PH4
    ADC_ConfigRegularChannel(ADC_Channel_09_PB1,5,ADC_SAMP_TIME_4CYCLES);
    ADC_ConfigInt(ADC_INT_PHS4, ENABLE);
    /* Enable ADC */
    ADC_Enable(ENABLE);
    /*Check ADC Ready*/
    while(ADC_GetFlagStatus(ADC_FLAG_RDY) == RESET)
        ;
}
/** Main program. **/
int main(void)
{
    /* System clocks configuration --------------------------------*/
    RCC_Configuration();

    /* GPIO configuration -----------------------------------------*/
    GPIO_Configuration();
    
    /* NVIC configuration -----------------------------------------*/
    NVIC_Configuration();
    /* ADC  configuration -----------------------------------------*/
    ADC_Initial();
    /* TIM1 configuration -----------------------------------------*/
    TIM_Configuration();
    
    /* TIM1 PWM output enable */
    TIM_EnableCtrlPwmOutputs(TIM1, ENABLE);
    /* TIM1 counter enable */
    TIM_Enable(TIM1, ENABLE);
    
    while (1)
    {

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

    /* Enable GPIO TIM clocks */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO | RCC_APB_PERIPH_TIM1, ENABLE);
    /* Enable ADC clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC, ENABLE);
    
    /* RCC_ADCHCLK_DIV4*/
    ADC_ClockModeConfig(RCC_ADCHCLK_DIV4);
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
    /* Configure PA0 PA1 PA4 as analog input ----*/
    GPIO_InitStructure.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    /* Configure PB1 PB0 as analog input ----*/
    GPIO_InitStructure.Pin       = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    
    /* Configure PB3-CH1 as alternate function push-pull mode ----*/
    GPIO_InitStructure.Pin       = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate =GPIO_AF1;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    
    /* Configure PB4-CH2 as alternate function push-pull mode ----*/
    GPIO_InitStructure.Pin       = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate =GPIO_AF7;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    
    /* Configure PB5-CH3  as alternate function push-pull mode ----*/
    GPIO_InitStructure.Pin       = GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate =GPIO_AF9;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    
    /* Configure PB6-CH4 as alternate function push-pull mode ----*/
    GPIO_InitStructure.Pin       = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate =GPIO_AF11;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    
    /* Configure PB7 as push-pull mode ----*/
    GPIO_InitStructure.Pin       = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}

/**
*\*\name    TIM_Configuration.
*\*\fun     Configures the different EXTI lines.
*\*\return  none
**/
void TIM_Configuration(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    OCInitType TIM_OCInitStructure;
    /* GTIM1 configuration ------------------------------------------------------*/
    /* Time Base configuration */
    PrescalerValue = (uint32_t)(SystemCoreClock / 160000) - 1;
    /* Time base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = 1600;
    TIM_TimeBaseStructure.Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CounterMode   = TIM_CNT_MODE_CENTER_ALIGN3;
    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);
    /* PWM1 Mode configuration: Channel1 */
    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OCMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = Pluse1_Val;
    TIM_OCInitStructure.OCPolarity  = TIM_OC_POLARITY_HIGH;
    TIM_InitOc1(TIM1, &TIM_OCInitStructure);
    TIM_ConfigOc1Preload(TIM1, TIM_OC_PRE_LOAD_ENABLE);
    
    /* PWM1 Mode configuration: Channel2 */
    TIM_OCInitStructure.Pulse       = Pluse2_Val;
    TIM_InitOc2(TIM1, &TIM_OCInitStructure);
    TIM_ConfigOc2Preload(TIM1, TIM_OC_PRE_LOAD_ENABLE);
    
    /* PWM1 Mode configuration: Channel3 */
    TIM_OCInitStructure.Pulse       = Pluse3_Val;
    TIM_InitOc3(TIM1, &TIM_OCInitStructure);
    TIM_ConfigOc3Preload(TIM1, TIM_OC_PRE_LOAD_ENABLE);
    
    /* PWM1 Mode configuration: Channel4 */
    TIM_OCInitStructure.Pulse       = Pluse4_Val;
    TIM_InitOc4(TIM1, &TIM_OCInitStructure);
    TIM_ConfigOc4Preload(TIM1, TIM_OC_PRE_LOAD_ENABLE);

    TIM_ConfigArPreload(TIM1, ENABLE); 
}
/**
*\*\name    NVIC_Configuration.
*\*\fun     Configures NVIC and Vector Table base location.
*\*\return  none
**/
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;
    /* Configure and enable ADC interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = ADC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}




