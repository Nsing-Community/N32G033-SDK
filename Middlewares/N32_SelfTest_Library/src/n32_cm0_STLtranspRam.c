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
#include "n32_cm0_STLRam.h"

/** @addtogroup N32_CM0_SelfTestLib_src
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/* ---------------------------------------------------------------------------*/
/**
  * @brief  This function verifies that 6 words of RAM are functional,
  *   overlapping) using the March C- or March X algorithm.
  * @param  : None
  * @retval : ClassBTestStatus (TEST_RUNNING, CLASS_B_DATA_FAIL,
  *   TEST_FAILURE, TEST_OK)
  */
ClassBTestStatus STL_TranspMarch(void)
{
  ClassBTestStatus result = TEST_RUNNING;
  
  /* Check Class B var integrity */
  if ((((uint32_t)pRunTimeRamChk) ^ ((uint32_t)pRunTimeRamChkInv)) == 0xFFFFFFFFuL)
  {
    if (pRunTimeRamChk == CLASS_B_START)
    {
      /*------------- March test applied on the RAM Buffer itself --------------- */
      if (STL_TranspRamMarchCXStep(&aRunTimeRamBuf[0], &aRunTimeRamBuf[0], BCKGRND) == MARCH_STEP_SUCCESS)         
      {
        /* Prepare next Row Transparent RAM test */
        pRunTimeRamChk = CLASS_B_TESTSTART;
        pRunTimeRamChkInv = ((uint32_t *)~((uint32_t)CLASS_B_TESTSTART));
      }
      else  /* Buffer is not functional */
      {
        result = TEST_FAILURE;
      }
    }
    else
    { /* ------------- March test applied on Class B data area ------------------ */
      /* !!! Application has to ensure that no write or read operation
               is performed within Class B RAM area during this test !!!      */
      if (STL_TranspRamMarchCXStep(pRunTimeRamChk, &aRunTimeRamBuf[1], BCKGRND) == MARCH_STEP_SUCCESS)         
      {
        /* Prepare next Row Transparent RAM test */
        pRunTimeRamChk += RT_RAM_BLOCKSIZE - (2u * RT_RAM_BLOCK_OVERLAP);
        pRunTimeRamChkInv = (uint32_t *)(uint32_t)(~(uint32_t)pRunTimeRamChk);
      }
      else
      {
        result = TEST_FAILURE;  /* Word line under test was not functional */
      }
      
      if (pRunTimeRamChk >= CLASS_B_END)
      {
          /* All the RAM test is completed successfully */
          result = TEST_OK;
          /* Init next cycle of the transparent RAM test starting from the begin of the Class B area */
          pRunTimeRamChk = CLASS_B_START;
          pRunTimeRamChkInv = ((uint32_t *)~((uint32_t)CLASS_B_START));
      }
      
    }
  }
  else  /* Class B error on pRunTimeRamChk */
  {
    result = CLASS_B_DATA_FAIL;
  }
  return (result);  
}


/******************* (C)  *****END OF FILE****/
