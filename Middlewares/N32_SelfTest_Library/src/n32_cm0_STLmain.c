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
#include "n32_cm0_STLmain.h"

/** @addtogroup N32_CM0_SelfTestLib_src
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
ErrorStatus STL_CheckStack(void);
__IO uint32_t uwTick;

void IncTick(void)
{
  uwTick++;
}
uint32_t GetTick(void)
{
  return uwTick;
}

#ifdef STL_FAULT_INJECTION_ENABLE
STL_FaultInj_t STLFaultInj;
#endif
/**
  * @brief  Initializes the Class B variables and their inverted
  *   redundant counterparts. Init also the Systick and RTC timer
  *   for clock frequency monitoring.
  * @param :  None
  * @retval : None
  */
void STL_InitRunTimeChecks(void)
{
  RCC_ClocksType RCC_ClocksStatusTmp;
  /* Init Class B variables required in main routine and SysTick interrupt
  service routine for timing purposes */
       
  /* start address of the test has to be aligned to 16 address range */	  
  pRunTimeRamChk = (uint32_t *)((uint32_t)CLASS_B_START & 0xFFFFFFFCuL);
  pRunTimeRamChkInv = (uint32_t *)(uint32_t)(~(uint32_t)pRunTimeRamChk);
  
  TickCounter = 0uL;
  TickCounterInv = 0xFFFFFFFFuL;

  TimeBaseFlag = 0uL;
  TimeBaseFlagInv = 0xFFFFFFFFuL;

  LastCtrlFlowCnt = 0uL;
  LastCtrlFlowCntInv = 0xFFFFFFFFuL;

  /* Initialize variables for SysTick interrupt routine control flow monitoring */
  ISRCtrlFlowCnt = 0uL;
  ISRCtrlFlowCntInv = 0xFFFFFFFFuL;
    
#ifdef STL_FAULT_INJECTION_ENABLE
    STLFaultInj.CpuRegTest = 0;
    STLFaultInj.CpuPCTest = 0;
    STLFaultInj.StackTest = 0;
    STLFaultInj.FlashTest = 0;
    STLFaultInj.ClockTest = 0;
    STLFaultInj.ADCTest = 0;
    STLFaultInj.InterruptTest = 0;
    STLFaultInj.TestFailFlag = 0;
#endif

    RCC_GetClocksFreqValue(&RCC_ClocksStatusTmp);
   /* Initialize SysTick to generate 1ms time base */
  if (SysTick_Config(RCC_ClocksStatusTmp.SysclkFreq/1000uL))
  {
    #ifdef STL_VERBOSE
    printf("Run time base init failure\r\n");
    #endif /* SELFTEST_VERBOSE_POR */
    FailSafePOR();
  }

  /* Initialize variables for run time invariable memory check */  
  STL_FlashCrc32Init();

  #if defined(USE_INDEPENDENT_WDOG) || defined(USE_WINDOW_WDOG)
    initialize_system_wdogs();
  #endif  /* USE_INDEPENDENT_WDOG | USE_WINDOW_WDOG */ 
  
         
  /* Initialize variables for main routine control flow monitoring */
  CtrlFlowCnt = 0uL;
  CtrlFlowCntInv = 0xFFFFFFFFuL;
}

/* ---------------------------------------------------------------------------*/
/**
  * @brief  Provide a short description of the function
  * @param :  None
  * @retval : None
  */

void STL_DoRunTimeChecks(void)
{
    uint32_t RomTest;
    
  /* Is the time base duration elapsed? */
  if (TimeBaseFlag == 0xAAAAAAAAuL)
  {     
    #ifdef __IAR_SYSTEMS_ICC__  /* IAR Compiler */
    #pragma diag_suppress=Pa082              
    #endif /* __IAR_SYSTEMS_ICC__ */
    /* Verify its integrity (class B variable) */
    if ((TimeBaseFlag ^ TimeBaseFlagInv) == 0xFFFFFFFFuL)
    {      
      TimeBaseFlag = 0uL;

              
      /*----------------------------------------------------------------------*/
      /*---------------------------- CPU registers ----------------------------*/
      /*----------------------------------------------------------------------*/
      control_flow_call(CPU_TEST_CALLER);
                
      if (STL_RunTimeCPUTest() != CPUTEST_SUCCESS)
      {
        #ifdef STL_VERBOSE
          printf("Run-time CPU Test Failure\n\r");
        #endif /* STL_VERBOSE */
        FailSafePOR();
      }
      else
      {  
        control_flow_resume(CPU_TEST_CALLER);
      }

      /*----------------------------------------------------------------------*/
      /*------------------------- Stack overflow -----------------------------*/
      /*----------------------------------------------------------------------*/
      control_flow_call(STACK_OVERFLOW_TEST); 
      if (STL_CheckStack() != SUCCESS)
      {
        #ifdef STL_VERBOSE
          printf("Stack overflow\n\r");
        #endif /* STL_VERBOSE */
        FailSafePOR();
      }
      else
      {
        control_flow_resume(STACK_OVERFLOW_TEST);
      }

      /*----------------------------------------------------------------------*/
      /*------------------------- Clock monitoring ---------------------------*/
      /*----------------------------------------------------------------------*/
      control_flow_call(CLOCK_TEST_CALLER);
       switch ( STL_MainClockTest() )
      {
        case FREQ_OK:
          control_flow_resume(CLOCK_TEST_CALLER);
          break;
  
        case EXT_SOURCE_FAIL:
          #ifdef STL_VERBOSE
          /* finish communication flow prior system clock change */
          while(USART_GetFlagStatus(USART1,USART_FLAG_TXC)==RESET){ }
          USART_ReConfigurationClk();
          printf("Clock Source failure (Run-time)\r\n");
          #endif /* STL_VERBOSE */
          FailSafePOR();
          break;
  
        case CLASS_B_VAR_FAIL:
          #ifdef STL_VERBOSE
          printf("Class B variable error (clock test)\r\n");
          #endif /* STL_VERBOSE */
          FailSafePOR();
          break;
  
        case LSI_START_FAIL:
        case HSE_START_FAIL:
        case HSI_HSE_SWITCH_FAIL:
        case TEST_ONGOING:
        case CTRL_FLOW_ERROR:
        default:
          #ifdef STL_VERBOSE
          printf("Abnormal Clock Test routine termination\r\n");
          #endif  /* STL_VERBOSE */
          FailSafePOR();
          break;
      }
      
      
      /*----------------------------------------------------------------------*/
      /*------------------ Invariable memory CRC check -----------------------*/
      /*----------------------------------------------------------------------*/
      control_flow_call(CRC32_RUN_TEST_CALLER);
      RomTest = STL_crc32Run();
      switch ( RomTest )
      {
        case TEST_RUNNING:
            control_flow_resume(CRC32_RUN_TEST_CALLER);
          break;

        case TEST_OK:
          #ifdef STL_VERBOSE
            putchar((int)'*');      /* FLASH test OK mark */
          #endif  /* STL_VERBOSE */
          control_flow_resume(CRC32_RUN_TEST_CALLER);
          break;

        case TEST_FAILURE:
        case CLASS_B_DATA_FAIL:
        default:
          #ifdef STL_VERBOSE
            printf("\n\r Run-time FLASH CRC Error\n\r");
          #endif  /* STL_VERBOSE */
          FailSafePOR();
          break;
      }

      /*----------------------------------------------------------------------*/
      /*---------------- Check Safety routines Control flow  -----------------*/
      /*------------- Refresh Window and independent watchdogs ---------------*/
      /*----------------------------------------------------------------------*/
      
      /* Reload IWDG counter */
      #ifdef USE_INDEPENDENT_WDOG
        IWDG_ReloadKey();
      #endif  /* USE_INDEPENDENT_WDOG */
      
      if (((CtrlFlowCnt ^ CtrlFlowCntInv) == 0xFFFFFFFFuL)
        &&((LastCtrlFlowCnt ^ LastCtrlFlowCntInv) == 0xFFFFFFFFuL))
      {
        if (RomTest == TEST_OK)
        {

	  #ifdef __IAR_SYSTEMS_ICC__  /* IAR Compiler */
  /* ==============================================================================*/
  /* MISRA violation of rule 17.4 - pointer arithmetic is used for Control flow calculation */
	    #pragma diag_suppress=Pm088
	  #endif   /* IAR Compiler */
          if ((CtrlFlowCnt == FULL_FLASH_CHECKED)\
          && ((CtrlFlowCnt - LastCtrlFlowCnt) == (LAST_DELTA_MAIN)))
	  #ifdef __IAR_SYSTEMS_ICC__  /* IAR Compiler */
	    #pragma diag_default=Pm088
  /* ==============================================================================*/
	  #endif   /* IAR Compiler */
          {
            CtrlFlowCnt = 0uL;
            CtrlFlowCntInv = 0xFFFFFFFFuL;
          }
          else  /* Return value form crc check was corrupted */
          {
            #ifdef STL_VERBOSE
              printf("Control Flow Error (main loop, Flash CRC)\n\r");
            #endif  /* STL_VERBOSE */
            FailSafePOR();
          }
        }
        else  /* Flash test not completed yet */
        {
            #ifdef STL_FAULT_INJECTION_ENABLE
            if(STLFaultInj.CpuPCTest)
            {
                CtrlFlowCnt = 369;
                LastCtrlFlowCnt = 256;
            }
            #endif
          if ((CtrlFlowCnt - LastCtrlFlowCnt) != DELTA_MAIN)
          {
            #ifdef STL_VERBOSE
              printf("Control Flow Error (main loop, Flash CRC on-going)\n\r");
            #endif  /* STL_VERBOSE */
            FailSafePOR();
          }
        }

        LastCtrlFlowCnt = CtrlFlowCnt;
        LastCtrlFlowCntInv = CtrlFlowCntInv;
      }
      else
      {
        #ifdef STL_VERBOSE
          printf("Control Flow Error (main loop)\n\r");
        #endif  /* STL_VERBOSE */
        FailSafePOR();
      }       
    } /* End of periodic Self-test routine */
    else  /* Class B variable error (can be Systick interrupt lost) */
    {
      #ifdef STL_VERBOSE
        printf("\n\r Class B variable error (clock test)\n\r");
      #endif  /* STL_VERBOSE */
      FailSafePOR();
    }
    
  } /* End of periodic Self-test routine */
  
}

/* ---------------------------------------------------------------------------*/
/**
  * @brief  Provide a short description of the function
  * @param :  None
  * @retval : None
  */

void STL_InterruptRunTimeChecks(void)
{
    uint32_t RamTestResult;
    IncTick();
    
    /* Verify TickCounter integrity */
    if ((TickCounter ^ TickCounterInv) == 0xFFFFFFFFuL)
    {
        
        TickCounter++;
        TickCounterInv = ~TickCounter;

        if (TickCounter >= SYSTICK_Xms_TB)
        {                   

          /* Reset timebase counter */
          TickCounter = 0u;
          TickCounterInv = 0xFFFFFFFF;

          /* Set Flag read in main loop */
          TimeBaseFlag = 0xAAAAAAAAuL;
          TimeBaseFlagInv = 0x55555555uL;
      /*----------------------------------------------------------------------*/
      /*------------------     RAM test(in interrupt)  -----------------------*/
      /*----------------------------------------------------------------------*/
          ISRCtrlFlowCnt += RAM_MARCHC_ISR_CALLER;
          __disable_irq();
          RamTestResult = STL_TranspMarch();
          __enable_irq();
          ISRCtrlFlowCntInv -= RAM_MARCHC_ISR_CALLER; 
          switch ( RamTestResult )
          {
            case TEST_RUNNING:
              break;
            case TEST_OK:
              #ifdef STL_VERBOSE
               /* avoid any long string output here in the interrupt, '#' marks ram test completed ok */
                putchar((int)'#');      /* RAM OK mark */
              #endif  /* STL_VERBOSE */
              break;
            case TEST_FAILURE:
            case CLASS_B_DATA_FAIL:
            default:
              #ifdef STL_VERBOSE
                printf("\n\r >>>>>>>>>>>>>>>>>>>  RAM Error (March C- Run-time check)\n\r");
              #endif  /* STL_VERBOSE */
              FailSafePOR();
              break;
          } /* End of the switch */
          
          /* Do we reached the end of RAM test? */
          /* Verify 1st ISRCtrlFlowCnt integrity */
          if ((ISRCtrlFlowCnt ^ ISRCtrlFlowCntInv) == 0xFFFFFFFFuL)
          {
            if (RamTestResult == TEST_OK)
            {
              if (ISRCtrlFlowCnt != RAM_TEST_COMPLETED)
              {
                  #ifdef STL_VERBOSE
                    printf("\n\r Control Flow error (RAM test) \n\r");
                  #endif  /* STL_VERBOSE */
                  FailSafePOR();
              }
              else  /* Full RAM was scanned */
              {
                 ISRCtrlFlowCnt = 0u;
                 ISRCtrlFlowCntInv = 0xFFFFFFFFuL;
              }
            } /* End of RAM completed if*/
          } /* End of control flow monitoring */
          else
          {
              #ifdef STL_VERBOSE
                printf("\n\r Control Flow error in ISR \n\r");
              #endif  /* STL_VERBOSE */
              FailSafePOR();
          }         
          
        } /* End of the 20 ms timebase interrupt */
    }
}

/* ---------------------------------------------------------------------------*/
/**
  * @brief  This function verifies that Stack didn't overflow
  * @param :  None
  * @retval : ErrorStatus = (ERROR, SUCCESS)
  */
ErrorStatus STL_CheckStack(void)
{
    ErrorStatus Result = SUCCESS;

    control_flow_call(STACK_OVERFLOW_CALLEE);
    
    #ifdef STL_FAULT_INJECTION_ENABLE
    if(STLFaultInj.StackTest)
    {
        aStackOverFlowPtrn[0] = 0x77777777;
    }
    #endif

    if ((aStackOverFlowPtrn[0] != 0xAAAAAAAAuL)||(aStackOverFlowPtrn[1] != 0xBBBBBBBBuL)|| \
       (aStackOverFlowPtrn[2] != 0xCCCCCCCCuL)||(aStackOverFlowPtrn[3] != 0xDDDDDDDDuL))
    {
      Result = ERROR;
    }
    
    control_flow_resume(STACK_OVERFLOW_CALLEE);

    return (Result);
}

/* ---------------------------------------------------------------------------*/
/**
  * @brief  This function initialize both independent & window system watch dogs
  * @param :  None
  * @retval None
  */
void initialize_system_wdogs(void)
{
  #ifdef USE_INDEPENDENT_WDOG
    IWDG_WriteConfig(IWDG_WRITE_ENABLE);

    /* IWDG clock: LSI / 4 = 8KHz (for example LSI = 32K)*/
    IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV4);
    /* Set counter reload value to 1/8k*500=62.5ms */
    IWDG_CntReload(500u);
    /* Reload IWDG counter */
    IWDG_ReloadKey();
    /* Enable IWDG */
    IWDG_Enable();
    
  #endif  /* USE_INDEPENDENT_WDOG */
}


/******************* (C)  *****END OF FILE****/
