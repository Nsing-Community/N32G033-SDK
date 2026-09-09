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



#define    HIGH_THRESHOLD           ((uint16_t)0xB00)
#define    LOW_THRESHOLD            ((uint16_t)0x300)

ADC_InitType ADC_InitStructure;
uint32_t gCnt = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
/**
*\*\name    ADC_Initial.
*\*\fun     ADC_Initial program.
*\*\return  none
**/
void ADC_Initial(void)
{
    ADC_InitStruct(&ADC_InitStructure);
    /* ADC configuration ------------------------------------------------------*/
    ADC_InitStructure.ContinueConvEn = ENABLE;
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

    ADC_ConfigRegularChannel(ADC_Channel_03_PA3, 1, ADC_SAMP_TIME_72CYCLES);
    
    /*Enable anolog watchdog*/
    ADC_ConfigInt(ADC_INT_AWD, ENABLE);
    ADC_ConfigAnalogWatchdogThresholds(HIGH_THRESHOLD, LOW_THRESHOLD);
    /*Enable DAT0 watchdog*/
    ADC_ConfigAnalogWatchdogModeChannel(ADC_ANALOG_WTDG_DAT0);
    /* Anolog watchdog monitor DAT0 enable */
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
    
    ADC_EnableChannelStartConv(ADC_SWSTRRCH_PHS1_START);
    
    while (1)
    {
       gCnt++;
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
    /* Configure PA3 as analog input -----------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**
*\*\name    NVIC_Configuration.
*\*\fun     Configures NVIC and Vector Table base location.
*\*\return  none
**/
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;
    
    NVIC_InitStructure.NVIC_IRQChannel                   = ADC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


