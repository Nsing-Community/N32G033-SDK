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
__IO uint16_t ADCConvertedValue[3];


void RCC_Configuration(void);
void GPIO_Configuration(void);
uint16_t ADC_Config_And_Get_Data( uint8_t ADC_Channel);
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
    ADC_InitStructure.ExtTrigSelect1 = ADC_EXT_TRIGCONV_SWSTRRCH;
    /* Initialize the DatAlign member */
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    /* Initialize the phase mode member */
    ADC_InitStructure.PhsMode        = ADC_PHS_TRG_MODE_SINGLE ;
    /* Initialize the phase 1 channel number member */
    ADC_InitStructure.Phs1ChNumber   = 1U;
    /* Initialize the phase 2 channel number member */
    ADC_InitStructure.Phs2ChNumber   = 1U;
    /* Initialize the phase 3 channel number member */
    ADC_InitStructure.Phs3ChNumber   = 1U;
    /* Initialize the phase 4 channel number member */
    ADC_InitStructure.Phs4ChNumber   = 1U;
    ADC_Init(&ADC_InitStructure);

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

    /* ADC  configuration -----------------------------------------*/
    ADC_Initial();
    
    while (1)
    {
        ADCConvertedValue[0]= ADC_Config_And_Get_Data(ADC_Channel_00_PA0);
        ADCConvertedValue[1]= ADC_Config_And_Get_Data(ADC_Channel_01_PA1);
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

    /* Enable GPIO clocks */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO, ENABLE);
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
    /* Configure PA0 PA1 as analog input -----------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**
*\*\name    ADC_Config_And_Get_Data.
*\*\fun     Configures ADC and get ADC conversion results.
*\*\param   ADC_Channel :
*\*\          - ADC_CH_0
*\*\          - ADC_CH_1
*\*\          - ADC_CH_2
*\*\          - ADC_CH_3
*\*\          - ADC_CH_4
*\*\          - ADC_CH_5
*\*\          - ADC_CH_6
*\*\          - ADC_CH_7
*\*\          - ADC_CH_8
*\*\          - ADC_CH_9
*\*\          - ADC_CH_10
*\*\          - ADC_CH_TS
*\*\          - ADC_CH_VREFINT
*\*\          - ADC_CH_OPA0OUT
*\*\          - ADC_CH_OPA1OUT
*\*\          - ADC_CH_OPA2OUT
*\*\return  The Data conversion value.
**/
uint16_t ADC_Config_And_Get_Data( uint8_t ADC_Channel)
{
    uint16_t dat;
    
    ADC_ConfigRegularChannel(ADC_Channel, 1, ADC_SAMP_TIME_72CYCLES);
    /* Start ADC Software Conversion */
    ADC_EnableChannelStartConv(ADC_SWSTRRCH_PHS1_START);
    while(ADC_GetFlagStatus(ADC_FLAG_ENDC)==0){
    }
    ADC_ClearFlag(ADC_FLAG_ENDC);
    ADC_ClearFlag(ADC_FLAG_STR);
    dat=ADC_GetDat();
    
    return dat;
}


