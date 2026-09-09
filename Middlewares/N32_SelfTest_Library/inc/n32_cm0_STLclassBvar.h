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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __N32_CM0_STL_CLASS_B_VAR_H
#define __N32_CM0_STL_CLASS_B_VAR_H

/* This avoids having multiply defined global variables */
#ifdef ALLOC_GLOBALS
#define EXTERN
#else
#define EXTERN extern
#endif

#include <stdint.h>
#include "core_cm0.h"
/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#ifdef __IAR_SYSTEMS_ICC__  /* IAR Compiler */
  EXTERN __no_init uint32_t aRunTimeRamBuf[];

  EXTERN __no_init uint32_t *pRunTimeRamChk;
  EXTERN __no_init uint32_t *pRunTimeRamChkInv;
  
  EXTERN __no_init uint32_t CtrlFlowCnt;
  EXTERN __no_init uint32_t CtrlFlowCntInv;

  EXTERN __no_init uint32_t ISRCtrlFlowCnt;
  EXTERN __no_init uint32_t ISRCtrlFlowCntInv;

  EXTERN __no_init __IO uint32_t LSIPeriodFlag;
  EXTERN __no_init __IO uint32_t LSIPeriodFlagInv;
  
  EXTERN __no_init uint32_t PeriodValue;
  EXTERN __no_init uint32_t PeriodValueInv;

  EXTERN __no_init uint32_t LastHSEPeriod;
  EXTERN __no_init uint32_t LastHSEPeriodInv;

  EXTERN __no_init uint32_t CurrentHSEPeriod;
  EXTERN __no_init uint32_t CurrentHSEPeriodInv;
  
  EXTERN __no_init uint32_t TickCounter;
  EXTERN __no_init uint32_t TickCounterInv;

  EXTERN __no_init __IO uint32_t TimeBaseFlag;
  EXTERN __no_init __IO uint32_t TimeBaseFlagInv;

  /* Stores the Control flow counter from one main loop to the other */
  EXTERN __no_init uint32_t LastCtrlFlowCnt;
  EXTERN __no_init uint32_t LastCtrlFlowCntInv;

  EXTERN __no_init uint32_t *p_RunCrc32Chk;
  EXTERN __no_init uint32_t *p_RunCrc32ChkInv;

  EXTERN __no_init uint32_t RefCrc32Flag;
  EXTERN __no_init uint32_t RefCrc32FlagInv;
  
  EXTERN __no_init uint32_t StartupTestFlag;

  EXTERN __no_init __IO uint32_t aStackOverFlowPtrn[];
#endif  /* __IAR_SYSTEMS_ICC__ */


#ifdef __CC_ARM   /* KEIL Compiler */
  EXTERN uint32_t aRunTimeRamBuf[];

  EXTERN uint32_t *pRunTimeRamChk;        
  EXTERN uint32_t *pRunTimeRamChkInv;     

  EXTERN uint32_t CtrlFlowCnt;             
  EXTERN uint32_t CtrlFlowCntInv;          

  EXTERN uint32_t ISRCtrlFlowCnt;          
  EXTERN uint32_t ISRCtrlFlowCntInv;       

  EXTERN __IO uint32_t LSIPeriodFlag;      
  EXTERN __IO uint32_t LSIPeriodFlagInv;   
  
  EXTERN uint32_t PeriodValue;           
  EXTERN uint32_t PeriodValueInv;        

  EXTERN uint32_t LastHSEPeriod;
  EXTERN uint32_t LastHSEPeriodInv;

  EXTERN uint32_t CurrentHSEPeriod;
  EXTERN uint32_t CurrentHSEPeriodInv;
  
  EXTERN uint32_t TickCounter;             
  EXTERN uint32_t TickCounterInv;          

  EXTERN __IO uint32_t TimeBaseFlag;           
  EXTERN __IO uint32_t TimeBaseFlagInv;        

  EXTERN uint32_t LastCtrlFlowCnt;         
  EXTERN uint32_t LastCtrlFlowCntInv;      

  EXTERN uint32_t *p_RunCrc32Chk;          
  EXTERN uint32_t *p_RunCrc32ChkInv;  
       
  EXTERN uint32_t RefCrc32Flag;                
  EXTERN uint32_t RefCrc32FlagInv;

  EXTERN uint32_t StartupTestFlag;

  EXTERN __IO uint32_t aStackOverFlowPtrn[];  
#endif  /* __CC_ARM */



#endif /* __N32_CM0_STL_CLASS_B_VAR_H */

/******************* (C)  *****END OF FILE****/
