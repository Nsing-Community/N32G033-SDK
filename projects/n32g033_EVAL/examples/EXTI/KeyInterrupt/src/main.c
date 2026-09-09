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
#include <stdio.h>
#include <stdint.h>
#include "log.h"

/**
*\*\name    main.
*\*\fun     main program.
*\*\param   none
*\*\return  none 
**/
int main(void)
{
    /*SystemInit() function has been called by startup file startup_n32g033.s*/

    /*Initialize Led1 and Led2 as output pushpull mode*/
    LedInit(LED1_PORT, LED1_PIN);
    LedInit(LED2_PORT, LED2_PIN);

    /*Initialize key as external line interrupt*/
    KeyInputExtiInit(KEY_INPUT_PORT, KEY_INPUT_PIN);

    /*Turn on Led1*/
    LedOn(LED1_PORT, LED1_PIN);

    while (1)
    {
    }
}


/**
*\*\name    KeyInputExtiInit.
*\*\fun     Configures key port.
*\*\param   GPIOx x can be A to G to select the GPIO port
*\*\param   Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15
*\*\return  none 
**/
void KeyInputExtiInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;

    /* Enable the GPIO Clock */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO,ENABLE);

    /*Configure the GPIO pin as input floating*/
    if (Pin <= GPIO_PIN_ALL)
    {
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin          = Pin;
        GPIO_InitStructure.GPIO_Pull    = GPIO_PULL_UP;
        GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
    }

    /*Configure key EXTI Line to key input Pin*/
    GPIO_ConfigEXTILine(KEY_INPUT_PORT_SOURCE, KEY_INPUT_PIN_SOURCE);

    /*Configure key EXTI line*/
    EXTI_InitStructure.EXTI_Line    = KEY_INPUT_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    /*Set key input interrupt priority*/
    NVIC_InitStructure.NVIC_IRQChannel                   = KEY_INPUT_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = NVIC_PRIORITY_1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
*\*\name    LedInit.
*\*\fun     Configures LED GPIO.
*\*\param   Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15
*\*\return  none 
**/
void LedInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable the GPIO Clock */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO,ENABLE);

    /* Configure the GPIO pin as output push-pull */
    if (Pin <= GPIO_PIN_ALL)
    {
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin = Pin;
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
    }
}

/**
*\*\name    LedOn.
*\*\fun     Turns selected Led on.
*\*\param   GPIOx x can be A to G to select the GPIO port.
*\*\param   Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15
*\*\return  none 
**/
void LedOn(GPIO_Module* GPIOx, uint16_t Pin)
{    
    GPIO_SetBits(GPIOx, Pin);
}

/**
*\*\name    LedOff.
*\*\fun     Turns selected Led Off.
*\*\param   GPIOx x can be A to G to select the GPIO port.
*\*\param   Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15
*\*\return  none 
**/
void LedOff(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_ResetBits(GPIOx, Pin);
}

/**
*\*\name    LedBlink.
*\*\fun     Toggles the selected Led.
*\*\param   GPIOx x can be A to G to select the GPIO port.
*\*\param   Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15
*\*\return  none 
**/
void LedBlink(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_TogglePin(GPIOx, Pin);
}



