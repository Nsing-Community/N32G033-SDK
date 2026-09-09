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
#include "n32_cm0_STLcrc32.h"
#include "crc32_software.h"
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

/**
  * @brief  Initializes CRC peripheral (enable its clock and reset CRC)
  * @param :  None
  * @retval : None
  */  
void CRC_Init(void)
{  
  /* This is for control flow monitoring */
  control_flow_call(CRC32_INIT_CALLER);
 
  control_flow_resume(CRC32_INIT_CALLER);
}

  /**
  * @brief  Inializes the pointers to the Flash memory required during
  *   run-time
  * @param :  None
  * @retval : None
  */
void STL_FlashCrc32Init(void)
{
  /* MISRA violation of rules 11.3, 11.4: pointer casting is used to check the 
     memory area and keep class B variable integrity */
#ifdef __IAR_SYSTEMS_ICC__  /* IAR Compiler */
  #pragma diag_suppress=Pm140, Pm141
#endif /* IAR Compiler */
  p_RunCrc32Chk = (uint32_t*)ROM_START;
  p_RunCrc32ChkInv = ((uint32_t *)(uint32_t)(~(uint32_t)(ROM_START)));
#ifdef __IAR_SYSTEMS_ICC__  /* IAR Compiler */
  #pragma diag_default=Pm140, Pm141
#endif /* IAR Compiler */

  CRC_Init(); /* Reset the CRC generator */
}


/* ---------------------------------------------------------------------------*/
/**
  * @brief  Computes the crc in multiple steps and compare it with the
  *   ref value when the whole memory has been tested
  * @param :  None
  * @retval : ClassBTestStatus = (TEST_RUNNING, CLASS_B_DATA_FAIL,
  *   TEST_FAILURE, TEST_OK)
  */
void STL_crc32StartUp(void)
{
   uint32_t crc_result;
    
  /* Store pattern for regular 32-bit crc computation */
  control_flow_call(CRC32_TEST_CALLEE);
    
    /* Compute the 32-bit crc of the whole Flash by CRC unit except the checksum
     pattern stored at top of FLASH */
   
    crc_result = crc32_fsl(0,(void*)ROM_START,ROM_SIZE);  
 
    if(crc_result != *(uint32_t *)(&REF_CRC32))
    {
      #ifdef STL_VERBOSE_POR
        printf("FLASH 32-bit CRC Error at Start-up\n\r");
      #endif  /* STL_VERBOSE_POR */
      FailSafePOR();
    }
    else
    { /* Test OK */
      #ifdef STL_VERBOSE_POR
        printf("Start-up FLASH 32-bit CRC OK\n\r");
      #endif  /* STL_VERBOSE_POR */     
    } 
    
  /* If else statement is not executed, it will be detected by control flow monitoring */
  control_flow_resume(CRC32_TEST_CALLEE);  
}

/* ---------------------------------------------------------------------------*/
/**
  * @brief  Computes the crc in multiple steps and compare it with the
  *   ref value when the whole memory has been tested
  * @param :  None
  * @retval : ClassBTestStatus = (TEST_RUNNING, CLASS_B_DATA_FAIL,
  *   TEST_FAILURE, TEST_OK)
  */
ClassBTestStatus STL_crc32Run(void)
{
  ClassBTestStatus Result = CTRL_FLW_ERROR; /* In case of abnormal func exit*/
  
    

  control_flow_call(CRC32_RUN_TEST_CALLEE);

  /* MISRA violation of rules 10.1, 10.3, 11.3, 11.4 and 17.4: integral casting and pointer arithmetic 
    is used here to manage the crc compuation and Check Class B var integrity */
#ifdef __IAR_SYSTEMS_ICC__  /* IAR Compiler */
  #pragma diag_suppress=Pm088,Pm129,Pm136,Pm140,Pm141
#endif /* IAR Compiler */
  
  if ((((uint32_t)p_RunCrc32Chk) ^ ((uint32_t)p_RunCrc32ChkInv)) == 0xFFFFFFFFuL)
  {
    if (p_RunCrc32Chk < (uint32_t *)ROM_END)
    {  
      if(p_RunCrc32Chk==(uint32_t*)ROM_START)
      {
        crc32_fsl_continuous(0, (void *) p_RunCrc32Chk, FLASH_BLOCK_WORDS*4, 0);
      }else
      {
        crc32_fsl_continuous(0, (void *) p_RunCrc32Chk, FLASH_BLOCK_WORDS*4, 1);
      }
       
      Result = TEST_RUNNING;
        
      p_RunCrc32Chk += FLASH_BLOCK_WORDS;     /* Increment pointer to next block */
      p_RunCrc32ChkInv = ((uint32_t *)~(uint32_t)((uint32_t)p_RunCrc32Chk));
#ifdef __IAR_SYSTEMS_ICC__  /* IAR Compiler */
  #pragma diag_default=Pm088,Pm129,Pm136,Pm140,Pm141
#endif /* IAR Compiler */
         
    }
    else
    {
      if ((RefCrc32Flag ^ RefCrc32FlagInv) == 0xFFFFFFFFuL)
      {
        if(crc32_fsl_continuous(0, (void *) p_RunCrc32Chk, FLASH_BLOCK_WORDS*4, 2) == *(uint32_t *)(&REF_CRC32))
        {
            Result = TEST_OK;
        }
        else
        {
            Result = TEST_FAILURE;
        }
            
        STL_FlashCrc32Init(); /* Prepare next test (or redo it if this one failed) */
      }
      else /* Class B error on RefCrc32Flag */
      {
        Result = CLASS_B_DATA_FAIL;
      }
    }
  }
  else  /* Class B error p_RunCrc32Chk */
  {
    Result = CLASS_B_DATA_FAIL;
  }

  control_flow_resume(CRC32_RUN_TEST_CALLEE);

  return (Result);
}


/******************* (C)  *****END OF FILE****/
