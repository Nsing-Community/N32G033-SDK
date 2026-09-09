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

#include "n32g033_it.h"
#include "log.h"

GPIO_InitType GPIO_InitStructure;
RCC_ClocksType RCC_ClockFreq;
ErrorStatus HSIStartUpStatus;
ErrorStatus LSIStartUpStatus;

ErrorStatus SetSysClockToHSI(uint32_t hsi_pres);
ErrorStatus SetSysClock_LSI(void);

/**
*\*\name    PrintfClockInfo.
*\*\fun     Printf clock information.
*\*\param   none
*\*\return  none 
**/
void PrintfClockInfo(const char* msg)
{
    log_init(); // should reinit after sysclk changed
    log_info("\n--------------------------------\n");
    log_info("%s:\n", msg);
    RCC_GetClocksFreqValue(&RCC_ClockFreq);
    log_info("SYSCLK: %d\n", RCC_ClockFreq.SysclkFreq);
    log_info("HCLK: %d\n", RCC_ClockFreq.HclkFreq);
    log_info("PCLK: %d\n", RCC_ClockFreq.PclkFreq);
}

int main(void)
{

    PrintfClockInfo("After reset");
	
/*** Select one of the following configuration methods ***/
#if SYSCLK_SOURCE_SELECT == SYSCLK_SOURCE_HSI
  /* Method 1  */	
    if(SetSysClockToHSI(RCC_SYSCLK_PRES_DIV1) == ERROR)
    {
        log_info("Clock configuration failure!\n");
    }
    else
    {
        PrintfClockInfo("HSI, 64MHz");
    }
#elif SYSCLK_SOURCE_SELECT == SYSCLK_SOURCE_HSI_DIV2 
  /* Method 2  */		
    if(SetSysClockToHSI(RCC_SYSCLK_PRES_DIV2) == ERROR)
    {
        log_info("Clock configuration failure!\n");
    }
    else
    {
        PrintfClockInfo("HSI, 32MHz");
    }
#elif SYSCLK_SOURCE_SELECT == SYSCLK_SOURCE_LSI 
	/* Method 3  */	
    if(SetSysClock_LSI() == ERROR)
    {
        log_info("Clock configuration failure!\n");
    }
    else
    {
        //Printing is only possible when system clock is LSI and the baud rate is configured to 1200
    }
#endif

    /* ----- Output HSE clock on MCO pin -------*/
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO, ENABLE);

    /* Configure the GPIO pin */
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    
    RCC_ConfigMcoClkPre(RCC_MCO_CLK_DIV4);
   /*** Select the corresponding MCO clock source ***/
    RCC_ConfigMco(RCC_MCO_SYSCLK);
    
    while (1);
}

/**
*\*\name    SetSysClockToHSI.
*\*\fun     Selects HSI as System clock source and configure HCLK, PCLK prescalers.
*\*\param   hsi_pres
*\*\	     - RCC_SYSCLK_PRES_DIV1       HSI divide 1 used as system clock
*\*\	     - RCC_SYSCLK_PRES_DIV2       HSI divide 2 used as system clock
*\*\return  none 
**/
ErrorStatus SetSysClockToHSI(uint32_t hsi_pres)
{
    uint32_t timeout_value = 0xFFFFFFFF; 
   
    RCC_EnableHsi(ENABLE);

    /* Wait till HSI is ready */
    HSIStartUpStatus = RCC_WaitHsiStable();

    if (HSIStartUpStatus == SUCCESS)
    {
        /* Flash 1 wait state */
        FLASH_SetLatency(FLASH_LATENCY_1);

        /* HCLK = SYSCLK */
        RCC_ConfigHclk(RCC_SYSCLK_DIV1);

        /* PCLK2*/
        if(hsi_pres == RCC_SYSCLK_PRES_DIV2)
        {
            RCC_ConfigPclk(RCC_HCLK_DIV1);
        }
        else 
        {
            RCC_ConfigPclk(RCC_HCLK_DIV2);
        }
        
        RCC_ConfigSysclkPres(hsi_pres);

        
        /* Select HSI as system clock source */
        RCC_ConfigSysclk(RCC_SYSCLK_SRC_HSI);
           
        /* Wait till HSI is used as system clock source */
        while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_HSI)
        {
            if ((timeout_value--) == 0)
            {
                return ERROR;
            }
        }
        
        if(hsi_pres == RCC_SYSCLK_PRES_DIV2)
        {
            /* Flash 0 wait state */
            FLASH_SetLatency(FLASH_LATENCY_0);
        }
       
    }
    else
    {
        /* If HSI fails to start-up, the application will have wrong clock
           configuration. User can add here some code to deal with this error */
        return ERROR;
    }
    return SUCCESS;
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





