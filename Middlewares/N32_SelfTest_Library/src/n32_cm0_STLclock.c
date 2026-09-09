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

/* Includes ------------------------------------------------------------------*/
#include "n32_cm0_STLclock.h"

/** @addtogroup N32_CM0_SelfTestLib_src
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#ifdef STL_FAULT_INJECTION_ENABLE
extern STL_FaultInj_t STLFaultInj;
#endif

/** @addtogroup N32_CM0_SelfTestLib_src
  * @{
  */ 

/******************************************************************************/
/**
  * @brief Configure TIMX to measure LSI period
  * @param  : None
  * @retval : ErrorStatus = (ERROR, SUCCESS)
  */
void STL_InitClock_Xcross_Measurement(void)
{
    /* no process */
}

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/ 
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Start up the internal and external oscillators and verifies
  *   that clock source is within the expected range
  * @param  : None
  * @retval : ClockStatus = (LSI_START_FAIL, HSE_START_FAIL,
  *   HSI_HSE_SWITCH_FAIL, XCROSS_CONFIG_FAIL, EXT_SOURCE_FAIL, FREQ_OK)
  */
ClockStatus STL_ClockStartUpTest(void)
{

  ClockStatus clck_sts = TEST_ONGOING;
  uint32_t TimeOut = LSI_START_TIMEOUT;  
  RCC_ClocksType RCC_ClocksStatusTmp;
  uint32_t LSIcnt = 0;
  
  CtrlFlowCnt += CLOCK_TEST_CALLEE;

  /* Start low speed internal (LSI) oscillator */
  /* Wait till LSI is ready */
  do
  {
    TimeOut--;
  }
  while((RCC_GetFlagStatus(RCC_LSCTRL_FLAG_LSIRD) == RESET) && (TimeOut != 0uL));

  if (TimeOut == 0uL)
  {
    clck_sts = LSI_START_FAIL;     /* Internal low speed oscillator failure */
  }
  
  
  if(clck_sts == TEST_ONGOING)
  {
     /* Wait for LSI periods measurements */
    RCC_ConfigLSICalibPeriod(RCC_LSICAL_PERIOD_128);
    RCC_EnableLSICalibration(ENABLE);
    while(!(RCC->CTRL&RCC_CTRL_LSICALCF));
    LSIcnt = RCC_GetHSICalibPeriod();
    RCC_EnableLSICalibration(DISABLE);

    PeriodValue = LSIcnt*8/128;
    PeriodValueInv = ~PeriodValue;
    
    /*-------------------- HSI measurement check -------------------------*/
    RCC_GetClocksFreqValue(&RCC_ClocksStatusTmp);
    if ((PeriodValue < CLK_LimitLow(RCC_ClocksStatusTmp.HclkFreq)) || (PeriodValue > CLK_LimitHigh(RCC_ClocksStatusTmp.HclkFreq)))
    {
        clck_sts = EXT_SOURCE_FAIL;
    }
  }
        
  if(clck_sts == TEST_ONGOING)
  {
    /* the test was finished correctly */
    clck_sts = FREQ_OK;
  }
  CtrlFlowCntInv -= CLOCK_TEST_CALLEE;
  
  return(clck_sts);
}


/**
  * @brief  This function verifies the frequency from the last clock
  *   period measurement
  * @param  : None
  * @retval : ClockStatus = (LSI_START_FAIL, HSE_START_FAIL,
  *   HSI_HSE_SWITCH_FAIL, TEST_ONGOING, EXT_SOURCE_FAIL,
  *   CLASS_B_VAR_FAIL, CTRL_FLOW_ERROR, FREQ_OK)
  */
ClockStatus STL_MainClockTest(void)
{
  ClockStatus result = TEST_ONGOING; /* In case of unexpected exit */ 

  RCC_ClocksType RCC_ClocksStatusTmp;
  uint32_t Delaycount = 0;

    control_flow_call(CLOCKPERIOD_TEST_CALLEE);
     
    RCC_ConfigLSICalibPeriod(RCC_LSICAL_PERIOD_128);
    RCC_EnableLSICalibration(ENABLE);
    /* Wait for five subsequent LSI periods measurements */    		
    while(!(RCC->CTRL&RCC_CTRL_LSICALCF))
    {
        Delaycount++;
        if(Delaycount>0xFFFFF)
        {
            result = XCROSS_CONFIG_FAIL;
            break;
        }
    }
    
    if(result == TEST_ONGOING)
    {	
	    PeriodValue = RCC_GetHSICalibPeriod();
        PeriodValue = PeriodValue*8/128;
        PeriodValueInv = ~PeriodValue;
           
        RCC_EnableLSICalibration(DISABLE); // clear done flag;close LSI detect
    }


   if ((PeriodValue ^ PeriodValueInv) == 0xFFFFFFFFuL) 
  {
    RCC_GetClocksFreqValue(&RCC_ClocksStatusTmp);
    if ((PeriodValue < CLK_LimitLow(RCC_ClocksStatusTmp.HclkFreq)) || (PeriodValue > CLK_LimitHigh(RCC_ClocksStatusTmp.HclkFreq)))
    {
        /* Switch back to internal clock */
        RCC_ConfigSysclk(RCC_SYSCLK_SRC_HSI);
        result = EXT_SOURCE_FAIL;	
    }
    else
    {     
        result = FREQ_OK;         /* Crystal or Resonator started correctly */        
        /* clear flag here to ensure refresh LSI measurement result will be taken at next check */
        LSIPeriodFlag = 0u;
      
    } /* No sub-harmonics */
  } /* Control Flow error */
  else
  {
    result = CLASS_B_VAR_FAIL;
  }

  control_flow_resume(CLOCKPERIOD_TEST_CALLEE);

  return (result);
}



