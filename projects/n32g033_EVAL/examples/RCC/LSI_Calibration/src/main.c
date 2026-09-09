/**
*     Copyright (c) 2022, Nsing Technologies Inc.
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
*\*\copyright Copyright (c) 2022, Nsing Technologies Inc. All rights reserved.
**/
#include "main.h"

uint32_t Lsi_Trim_Value1 = 0, Lsi_Trim_Value2 = 0, Lsi_Cal_Value = 0;

/**
*\*\name    main.
*\*\fun     main program.
*\*\param   none
*\*\return  none 
**/
int main(void)
{
    /* MCO Configuration */
    GPIO_Configuration();
    RCC_ConfigMco(RCC_MCO_LSI);

    /* Wait HSI ready */
    while (RCC_GetFlagStatus(RCC_CTRL_FLAG_HSIRDF) == RESET)
    {}
    /* Wait LSI ready */
    while (RCC_GetFlagStatus(RCC_CLKINT_FLAG_LSIRDF) == RESET)
    {}
    /* Config 128 LSI calibration period */  
    RCC_ConfigLSICalibPeriod(RCC_LSICAL_PERIOD_128);
    /* Enable LSI calibration */    
    RCC_EnableLSICalibration(ENABLE);
    /* Wait HSI ready */
    while (RCC_GetFlagStatus(RCC_CTRL_FLAG_LSICALCF) == RESET)
    {}
    /* LSI Frequency computation */   
    Lsi_Cal_Value = ((uint64_t)HSI_VALUE * 128 / RCC_GetHSICalibPeriod());
    /* LSI trim value computation */
    Lsi_Trim_Value1 = (RCC->LSCTRL & 0x01FF);
    RCC_ConfigLsiCalibSource(RCC_LSICAL_SRC_TRIM);
    if(Lsi_Cal_Value >= LSI_VALUE)
    {
        Lsi_Trim_Value2 = (Lsi_Cal_Value - LSI_VALUE)/100;
        if(Lsi_Trim_Value2 > Lsi_Trim_Value1)
        {
            Lsi_Trim_Value1 = 0;
        }
        else
        {
            Lsi_Trim_Value1 = Lsi_Trim_Value1 - Lsi_Trim_Value2;
        }
    }
    else
    {
        Lsi_Trim_Value2 = (LSI_VALUE - Lsi_Cal_Value)/100;
        if(Lsi_Trim_Value1 + Lsi_Trim_Value2 > 0x01FF)
        {
            Lsi_Trim_Value1 = 0x01FF;
        }
        else
        {
            Lsi_Trim_Value1 = Lsi_Trim_Value1 + Lsi_Trim_Value2;
        }
    }

    /* LSI trim*/
    RCC_SetLsiCalibValue(Lsi_Trim_Value1);
    
    while (1)
    {

    }
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
    
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO,ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* GPIOx Configuration: Pin of MCO */
    GPIO_InitStructure.Pin        = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}





