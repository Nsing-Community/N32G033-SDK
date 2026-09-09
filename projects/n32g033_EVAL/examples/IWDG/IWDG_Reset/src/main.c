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
*\*\file main.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nsing Technologies Inc. All rights reserved.
**/

#include "main.h"
#include "n32g033_tim.h"
#include "n32g033_pwr.h"
#include "delay.h"


/** Define the GPIO port to which the LED is connected **/
#define LED1_GPIO_PORT      GPIOA                       /* GPIO port */
#define LED1_GPIO_PIN       GPIO_PIN_6                  /* GPIO connected to the SCL clock line */

#define LED2_GPIO_PORT      GPIOA                       /* GPIO port */
#define LED2_GPIO_PIN       GPIO_PIN_7                  /* GPIO connected to the SCL clock line */


__IO uint32_t LsiFreq = 32000;
extern uint16_t CaptureNumber;

void TIM2_ConfigForLSI(void);


/**
*\*\name    LedInit.
*\*\fun     Configures LED GPIO.
*\*\param   GPIOx x can be A/B/F to select the GPIO port.
*\*\param   Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15?
*\*\return  none 
**/
void LedInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable the GPIO Clock */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO, ENABLE);
   
    /* Configure the GPIO pin */
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
}

/**
*\*\name    LedOn.
*\*\fun     Turns selected Led on.
*\*\param   GPIOx x can be A/B/F to select the GPIO port.
*\*\param   Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15?
*\*\return  none 
**/
void LedOn(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}

/**
*\*\name    LedOff.
*\*\fun     Turns selected Led Off.
*\*\param   GPIOx x can be A/B/F to select the GPIO port.
*\*\param   Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15?
*\*\return  none 
**/
void LedOff(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBC = Pin;
}

/**
*\*\name    LedBlink.
*\*\fun     Toggles the selected Led.
*\*\param   GPIOx x can be A/B/F to select the GPIO port.
*\*\param   Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15?
*\*\return  none 
**/
void LedBlink(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}

/** Main program. **/
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_n32g033.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_n32g033.c file
       */
    log_init();
    log_info("--- IWDG demo reset ---\n");
    LedInit(LED1_GPIO_PORT, LED1_GPIO_PIN);
    LedInit(LED2_GPIO_PORT, LED2_GPIO_PIN);
    LedOff(LED1_GPIO_PORT, LED1_GPIO_PIN);
    LedOff(LED2_GPIO_PORT, LED2_GPIO_PIN);
    
    /* Enable PWR Clock */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_PWR, ENABLE);

    /* Check if the system has resumed from IWDG reset */
    if(RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_IWDGRSTF) != RESET)
    {
        /* IWDGRST flag set */
        /* Turn on LED1 */
        LedOn(LED1_GPIO_PORT, LED1_GPIO_PIN);
        log_info("reset by IWDG\n");
        /* Clear reset flags */
        RCC_ClearResetFlag();
    }
    else
    {
        /* IWDGRST flag is not set */
        /* Turn off LED1 */
        LedOff(LED1_GPIO_PORT, LED1_GPIO_PIN);
    }
    
    /* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
       dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteConfig(IWDG_WRITE_ENABLE);

    /* IWDG counter clock: LSI/32 */
    IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV32);

    /* Set counter reload value to obtain 250ms IWDG TimeOut.
       Counter Reload Value = 250ms/IWDG counter clock period
                            = 250ms / (LSI/128)
                            = 0.25s / (LsiFreq/32)
                            = LsiFreq/(32 * 4)
                            = LsiFreq/128 */
    log_debug("LsiFreq is: %d\n", LsiFreq);

    IWDG_CntReload(LsiFreq / 128);
    /* Reload IWDG counter */
    IWDG_ReloadKey();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();

    while(1)
    {
        /* Toggle LED2 */
        LedBlink(LED2_GPIO_PORT, LED2_GPIO_PIN);
        /* Insert 249 ms delay */
        SysTick_Delay_Ms(249);

        /* Reload IWDG counter */
        IWDG_ReloadKey();
    }
}

