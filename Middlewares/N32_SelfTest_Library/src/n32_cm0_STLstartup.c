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
#include "n32_cm0_STLstartup.h"

/** @addtogroup N32_CM0_SelfTestLib_src
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef STL_FAULT_INJECTION_ENABLE
extern STL_FaultInj_t STLFaultInj;
#endif 
 
#ifdef __IAR_SYSTEMS_ICC__  /* IAR Compiler */
 /* Temporary RAM buffer used during transparent run-time tests */
  /* WARNING: Real reserved RAM location from 0x20000000 to 0x20000024*/
  __no_init uint32_t aRunTimeRamBuf[RT_RAM_BLOCKSIZE] @ "RUN_TIME_RAM_BUF";

  /* RAM pointer for run-time tests */
  __no_init uint32_t *pRunTimeRamChk     @ "RUN_TIME_RAM_PNT";
  __no_init uint32_t *pRunTimeRamChkInv  @ "RUN_TIME_RAM_PNT";
  
  /* Counter for verifying correct program execution at start */
  __no_init uint32_t CtrlFlowCnt          @ "CLASS_B_RAM";
  __no_init uint32_t CtrlFlowCntInv       @ "CLASS_B_RAM_REV";

  /* Counter for verifying correct program execution in interrupt */
  __no_init uint32_t ISRCtrlFlowCnt       @ "CLASS_B_RAM";
  __no_init uint32_t ISRCtrlFlowCntInv    @ "CLASS_B_RAM_REV";



  __no_init __IO uint32_t LSIPeriodFlag    @ "CLASS_B_RAM";
  __no_init __IO uint32_t LSIPeriodFlagInv @ "CLASS_B_RAM_REV";
  
  __no_init uint32_t PeriodValue           @ "CLASS_B_RAM";
  __no_init uint32_t PeriodValueInv        @ "CLASS_B_RAM_REV";
  
  /* Last period measure sample stored for run-time checks */
  __no_init uint32_t LastHSEPeriod           @ "CLASS_B_RAM";
  __no_init uint32_t LastHSEPeriodInv        @ "CLASS_B_RAM_REV";

  /* Last period measure stored as reference for run-time checks */
  __no_init uint32_t CurrentHSEPeriod        @ "CLASS_B_RAM";
  __no_init uint32_t CurrentHSEPeriodInv     @ "CLASS_B_RAM_REV";

  /* Sofware time base used in main program (incremented in SysTick timer ISR */
  __no_init uint32_t TickCounter          @ "CLASS_B_RAM";
  __no_init uint32_t TickCounterInv       @ "CLASS_B_RAM_REV";

  /* Indicates to the main routine a 100ms tick */
  __no_init __IO uint32_t TimeBaseFlag        @ "CLASS_B_RAM";
  __no_init __IO uint32_t TimeBaseFlagInv     @ "CLASS_B_RAM_REV";

  /* Stores the Control flow counter from one main loop to the other */
  __no_init uint32_t LastCtrlFlowCnt      @ "CLASS_B_RAM";
  __no_init uint32_t LastCtrlFlowCntInv   @ "CLASS_B_RAM_REV";

  /* Pointer to FLASH for crc32 run-time tests */
  __no_init uint32_t *p_RunCrc32Chk       @ "CLASS_B_RAM";
  __no_init uint32_t *p_RunCrc32ChkInv    @ "CLASS_B_RAM_REV";

  /* Reference 32-bit CRC for run-time tests */
  __no_init uint32_t RefCrc32Flag             @ "CLASS_B_RAM";
  __no_init uint32_t RefCrc32FlagInv          @ "CLASS_B_RAM_REV";
  
   /* Startup Test Flag */
  __no_init uint32_t StartupTestFlag             @ "CLASS_B_RAM";

  /* Magic pattern for Stack overflow in this array */
  __no_init __IO uint32_t aStackOverFlowPtrn[4] @ "STACK_BOTTOM";
#endif  /* __IAR_SYSTEMS_ICC__ */


#ifdef __CC_ARM   /* KEIL Compiler */
  /* Temporary RAM buffer used during transparent run-time tests */
  /* WARNING: Uses RAM location from 0x20000000 to 0x20000020 included */
  uint32_t aRunTimeRamBuf[RT_RAM_BLOCKSIZE] __attribute__((section("RUN_TIME_RAM_BUF")));

  /* RAM pointer for run-time tests */
  uint32_t *pRunTimeRamChk        __attribute__((section("RUN_TIME_RAM_PNT")));
  uint32_t *pRunTimeRamChkInv     __attribute__((section("RUN_TIME_RAM_PNT")));

  /* Note: the zero_init forces the linker to place variables in the bss section */
  /* This allows the UNINIT directive (in scatter file) to work. On the contrary */
  /* all Class B variables would be cleared by the C startup */

  /* Counter for verifying correct program execution at start */
  uint32_t CtrlFlowCnt             __attribute__((section("CLASS_B_RAM"), zero_init));
  uint32_t CtrlFlowCntInv          __attribute__((section("CLASS_B_RAM_REV"), zero_init));

  /* Counter for verifying correct program execution in interrupt */
  uint32_t ISRCtrlFlowCnt          __attribute__((section("CLASS_B_RAM"), zero_init));
  uint32_t ISRCtrlFlowCntInv       __attribute__((section("CLASS_B_RAM_REV"), zero_init));

  /* Indicates to the main routine a tick */
  __IO uint32_t LSIPeriodFlag      __attribute__((section("CLASS_B_RAM"), zero_init));
  __IO uint32_t LSIPeriodFlagInv   __attribute__((section("CLASS_B_RAM_REV"), zero_init));
  
  /* LSI period measurement at TIMx IRQHandler */
  uint32_t PeriodValue           __attribute__((section("CLASS_B_RAM"), zero_init));
  uint32_t PeriodValueInv        __attribute__((section("CLASS_B_RAM_REV"), zero_init));
  
   /* Last period measure sample stored for run-time checks */
  uint32_t LastHSEPeriod           __attribute__((section("CLASS_B_RAM"), zero_init));
  uint32_t LastHSEPeriodInv        __attribute__((section("CLASS_B_RAM_REV"), zero_init));

  /* Last period measure stored as reference for run-time checks */
  uint32_t CurrentHSEPeriod        __attribute__((section("CLASS_B_RAM"), zero_init));
  uint32_t CurrentHSEPeriodInv     __attribute__((section("CLASS_B_RAM_REV"), zero_init));

  /* Sofware time base used in main program (incremented in SysTick timer ISR */
  uint32_t TickCounter             __attribute__((section("CLASS_B_RAM"), zero_init));
  uint32_t TickCounterInv          __attribute__((section("CLASS_B_RAM_REV"), zero_init));

  /* Indicates to the main routine a tick */
  __IO uint32_t TimeBaseFlag           __attribute__((section("CLASS_B_RAM"), zero_init));
  __IO uint32_t TimeBaseFlagInv        __attribute__((section("CLASS_B_RAM_REV"), zero_init));

  /* Stores the Control flow counter from one main loop to the other */
  uint32_t LastCtrlFlowCnt         __attribute__((section("CLASS_B_RAM"), zero_init));
  uint32_t LastCtrlFlowCntInv      __attribute__((section("CLASS_B_RAM_REV"), zero_init));

  /* Pointer to FLASH for crc32 run-time tests */
  uint32_t *p_RunCrc32Chk          __attribute__((section("CLASS_B_RAM"), zero_init));
  uint32_t *p_RunCrc32ChkInv       __attribute__((section("CLASS_B_RAM_REV"), zero_init));

/* Reference 32-bit CRC for run-time tests */
  uint32_t RefCrc32Flag                __attribute__((section("CLASS_B_RAM"), zero_init));
  uint32_t RefCrc32FlagInv             __attribute__((section("CLASS_B_RAM_REV"), zero_init));
  
  /* Startup Test Flag */
  uint32_t StartupTestFlag             __attribute__((section("CLASS_B_RAM"), zero_init));

  /* Magic pattern for Stack overflow in this array */
  __IO uint32_t aStackOverFlowPtrn[4]   __attribute__((section("STACK_BOTTOM"), zero_init));
#endif  /* __CC_ARM */

/******************************************************************************/
/**
  * @brief  This routine is executed in case of failure is detected by one of
  *    self-test routines. The routine is empty and it has to be filled by end
  *    user to keep application safe while define proper recovery operation
  * @param  : None
  * @retval : None
  */
void FailSafePOR(void)
{
    #ifdef STL_FAULT_INJECTION_ENABLE
    STLFaultInj.TestFailFlag = 1;
    #endif
      
    /* SysTick could be disabled here */
    SysTick->CTRL &= 0xFFFFFFFD;

    #ifdef STL_VERBOSE_POR
    printf(" >>>>>>>>>> POR FailSafe Mode <<<<<<<<<<\n\r");
    #endif  /* STL_VERBOSE_POR */

    while(1)
    {
    /* Generate system reset */
    #ifdef  GENERATE_RESET_AT_FAIL_SAFE
        NVIC_SystemReset();
    #else
        #ifdef USE_INDEPENDENT_WDOG
            IWDG_ReloadKey();
        #endif /* USE_INDEPENDENT_WDOG */
      
    #endif  /* GENERATE_RESET_AT_FAIL_SAFE */
    }
}


#ifdef __IAR_SYSTEMS_ICC__  /* IAR Compiler */
#pragma optimize = none
#endif

#ifdef __CC_ARM             /* KEIL Compiler */
/******************************************************************************/
/**
  * @brief  Switch between startup and main code
  * @param  : None
  * @retval : None
  */
  void $Sub$$main(void)
  {
    if ( StartupTestFlag != 0xAAu )
    {
      STL_StartUp();		/* trick to call StartUp before main entry */
    }
    StartupTestFlag = 0u;
    $Super$$main(); 
  }
#endif /* __CC_ARM */
	
/******************************************************************************/
/**
  * @brief  Contains the very first test routines executed right after
  *   the reset
  * @param  : None
  *   Flash interface initialized, Systick timer ON (2ms timebase)
  * @retval : None
  */
void STL_StartUp(void)
{
  ClockStatus clk_sts;
    
  /* Prevent systick counter overflow */
  SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk|SysTick_CTRL_ENABLE_Msk); // Systick IRQ off
  SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk; // Clear SysTick Exception pending flag
  
  
  /* Reset of all peripherals, Initializes the Flash interface and the Systick */
  
  /*Configure the SysTick to have interrupt in 1ms time basis*/
  #ifdef STL_VERBOSE_POR
  /* Update the SystemCoreClock global variable as USART Baud rate setting depends on it */
  STL_VerbosePORInit();
  printf("\r\n*******  Self Test Library Init  *******\r\n");
  #endif
  
  /* Initialization of counters for control flow monitoring */
  init_control_flow();
       
  /*--------------------------------------------------------------------------*/
  /*------------------- CPU registers and flags self test --------------------*/
  /*--------------------------------------------------------------------------*/ 
  /* WARNING: all registers destroyed when exiting this function (including
  preserved registers R4 to R11) while excluding stack pointer R13) */
  
  control_flow_call(CPU_TEST_CALLER);
  
  if (STL_StartUpCPUTest() != CPUTEST_SUCCESS)
  {    
    #ifdef STL_VERBOSE_POR
      printf("Start-up CPU Special Register Test Failure\n\r");
    #endif /* STL_VERBOSE_POR */
    FailSafePOR();
  }
  else  /* Test OK */
  {
    #ifdef STL_VERBOSE_POR
      printf("Start-up CPU Special Register Test OK\n\r");
    #endif /* STL_VERBOSE_POR */
  }
  if (STL_RunTimeCPUTest() != CPUTEST_SUCCESS)
  {    
    #ifdef STL_VERBOSE_POR
      printf("Start-up CPU General Register Test Failure\n\r");
    #endif /* STL_VERBOSE_POR */
    FailSafePOR();
  }
  else  /* Test OK */
  {
    #ifdef STL_VERBOSE_POR
      printf("Start-up CPU General Register Test OK\n\r");
    #endif /* STL_VERBOSE_POR */
  }
  control_flow_resume(CPU_TEST_CALLER);
  
   /*--------------------------------------------------------------------------*/
   /*------------------------- Watch dogs Self Test ---------------------------*/
   /*--------------------------------------------------------------------------*/
  control_flow_call(WDG_TEST_CALLER);
  STL_WDGSelfTest();
  control_flow_resume(WDG_TEST_CALLER);

  /*--------------------------------------------------------------------------*/
  /*--------------------- Invariable memory CRC check ------------------------*/
  /*--------------------------------------------------------------------------*/
  
  control_flow_call(CRC32_TEST_CALLER);
  STL_crc32StartUp();
  control_flow_resume(CRC32_TEST_CALLER);
  

   /*--------------------------------------------------------------------------*/
  /*   Verify Control flow before RAM init (which clears Ctrl flow counters)  */
  /*--------------------------------------------------------------------------*/
  if (control_flow_check_point(CHECKPOINT1) == ERROR)
  {
     #ifdef STL_VERBOSE_POR
     printf("Control Flow Error Checkpoint 1\r\n");
     #endif  /* STL_VERBOSE_POR */
     FailSafePOR();
  }
  else
  {
   #ifdef STL_VERBOSE_POR
   printf("Control Flow Checkpoint 1 OK\r\n");
   #endif  /* STL_VERBOSE_POR */
  }
 
  /*--------------------------------------------------------------------------*/
  /* --------------------- Variable memory functional test -------------------*/
  /*--------------------------------------------------------------------------*/
 
  /* no stack operation can be performed during the test */  
   __disable_irq();
  /* WARNING: Stack is zero-initialized when exiting from this routine */
  if (STL_FullRamMarchC(RAM_START, RAM_END, BCKGRND) != SUCCESS)
  {
    #ifdef STL_VERBOSE_POR
      printf("Full RAM Test Failure\n\r");
    #endif  /* STL_VERBOSE_POR */
    FailSafePOR();
  }
   else
  {
   #ifdef STL_VERBOSE_POR
   printf("Full RAM Test OK\r\n");
   #endif  /* STL_VERBOSE_POR */
  }
  /* restore interrupt capability */
  __enable_irq();
  
/* Initialization of counters for control flow monitoring 
     (destroyed during RAM test) */
  init_control_flow();
  
  /*------------- Store reference 32-bit CRC in RAM after RAM test -----------*/  
   RefCrc32Flag = 0;  
   RefCrc32FlagInv = ~RefCrc32Flag;

  //--------------------------------------------------------------------------*/
  //----------------------- Clock Frequency Self Test ------------------------*/
  //--------------------------------------------------------------------------*/
  control_flow_call(CLOCK_TEST_CALLER);
  
  /* test LSI & systems clock(TIM)  */
  clk_sts = STL_ClockStartUpTest();
 
  /* Re-init USART with modified clock setting */
  #ifdef STL_VERBOSE_POR
    USART_ReConfigurationClk();
  #endif  /* STL_VERBOSE_POR */
    
  switch(clk_sts)
  {
    case LSI_START_FAIL:     
    #ifdef STL_VERBOSE_POR
        printf("LSI start-up failure\r\n");
    #endif  /* STL_VERBOSE_POR */        
      break;

    case HSE_START_FAIL:
      #ifdef STL_VERBOSE_POR
        printf("HSE start-up failure\r\n");
      #endif  /* STL_VERBOSE_POR */
      break;

    case HSI_HSE_SWITCH_FAIL:
    case HSE_HSI_SWITCH_FAIL:
    case PLL_OFF_FAIL:
      #ifdef STL_VERBOSE_POR
      printf("Clock switch failure\r\n");
      #endif  /* STL_VERBOSE_POR */
      break;

    case XCROSS_CONFIG_FAIL:
      #ifdef STL_VERBOSE_POR
      printf("Clock Xcross measurement failure\r\n");
      #endif  /* STL_VERBOSE_POR */
      break;

    case EXT_SOURCE_FAIL:
      #ifdef STL_VERBOSE_POR
      printf("Clock found out of range\r\n");
      #endif  /* STL_VERBOSE_POR */
      break;
      
    case FREQ_OK:
      #ifdef STL_VERBOSE_POR
      printf("Clock frequency OK \r\n");
      #endif  /* STL_VERBOSE_POR */
      break;
      
    default:
      #ifdef STL_VERBOSE_POR
      printf("Abnormal exit from clock test\r\n");
      #endif  /* STL_VERBOSE_POR */
      break;
  }
  
  if(clk_sts != FREQ_OK)
  {
    FailSafePOR();
  }
  control_flow_resume(CLOCK_TEST_CALLER); 
 
 
  /* -----  Store verify pattern to stack bottom for its later testing  ----- */
   control_flow_call(STACK_OVERFLOW_TEST);

   aStackOverFlowPtrn[0] = 0xAAAAAAAAuL;
   aStackOverFlowPtrn[1] = 0xBBBBBBBBuL;
   aStackOverFlowPtrn[2] = 0xCCCCCCCCuL;
   aStackOverFlowPtrn[3] = 0xDDDDDDDDuL;

   control_flow_resume(STACK_OVERFLOW_TEST);
   /*--------------------------------------------------------------------------*/
  /* -----  Verify Control flow before Starting main program execution ------ */
  /*--------------------------------------------------------------------------*/ 
    if (control_flow_check_point(CHECKPOINT2) == ERROR)
    {
        #ifdef STL_VERBOSE_POR
        printf("Control Flow Error Checkpoint 2 \n\r");
        #endif  /* STL_VERBOSE_POR */
        FailSafePOR();
    }
    else
    {
        #ifdef STL_VERBOSE_POR
        printf("Control Flow Checkpoint 2 OK \n\r");
        #endif  /* STL_VERBOSE_POR */
    }
  
    GotoCompilerStartUp();
}


    
    
/******************************************************************************/
/**
  * @brief  Verifies the consistency and value of control flow counters
  * @param  : check value of the positive counter
  * @retval : ErrorStatus (SUCCESS, ERROR)
  */
ErrorStatus control_flow_check_point(uint32_t chck)
{
  ErrorStatus Result= SUCCESS;
  
  if ((CtrlFlowCnt != (chck)) || ((CtrlFlowCnt ^ CtrlFlowCntInv) != 0xFFFFFFFFuL))
  {
    Result= ERROR;
  }
  return(Result);
}

/* ------------------------------------------------------------ */
/**
  * @brief  Initializes the USART1 and few I/Os for test purposes
  * @param :  None
  * @retval : None
  */
void STL_VerbosePORInit(void)
{
    GPIO_InitType GPIO_InitStructure;
    USART_InitType USART_InitStructure;
 
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_UART1 | RCC_APB_PERIPH_GPIO,ENABLE);
    
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin            = GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AFX_USART1;   
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;
    // init uart
    USART_Init(USART1, &USART_InitStructure);

    // enable uart
    USART_Enable(USART1, ENABLE);
}

/* ------------------------------------------------------------ */
/**
  * @brief  Reinitializes the USART1 with new clock frequency
  * @param  : None
  * @retval : None
  */
void USART_ReConfigurationClk()
{
    USART_InitType USART_InitStructure;

    USART_Enable(USART1, DISABLE);
    
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;
    // init uart
    USART_Init(USART1, &USART_InitStructure);

    // enable uart
    USART_Enable(USART1, ENABLE);
}


/* ============================================================================ */
/**
  * @brief  Verifies the watchdog by forcing watchdog resets
  * @param :  None
  * @retval : None
  */
void STL_WDGSelfTest(void)
{     
   #ifdef STL_VERBOSE_POR  
    if (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_PINRSTF)  != RESET) printf("Pin reset \r\n");
    if (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_PORRSTF)  != RESET) printf("POR reset \r\n");
    if (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_SFTRSTF)  != RESET) printf("SW reset \r\n");
    if (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_IWDGRSTF) != RESET) printf("IWDG reset \r\n");
  #endif /* STL_VERBOSE_POR */

  /* start watchdogs test if one of the 4 conditions below is valid */
  if ( ((RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_PORRSTF) != RESET)\
   ||  (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_SFTRSTF) != RESET)\
   || (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_PINRSTF)!= RESET)) && (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_IWDGRSTF) == RESET))
  {
    #ifdef STL_VERBOSE_POR
    printf("... Power-on or software reset, testing IWDG ... \r\n");
    #endif  /* STL_VERBOSE_POR */

    /* IWDG at debug mode */
    //RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_PWR, ENABLE);
   // DBG_ConfigPeriph(PWR_DBG_IWDG, ENABLE);

    /* Clear all flags before resuming test */
    RCC_ClearResetFlag();
   
    /* Setup IWDG to minimum period */
    IWDG_WriteConfig(IWDG_WRITE_ENABLE);
    IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV4);
    IWDG_CntReload(1);
    IWDG_ReloadKey();
    IWDG_Enable();
    
    /* Wait for an independent watchdog reset */
    while(1)
    { }
  }
  else  /* Watchdog test or software reset triggered by application failure */
  {
    /* If WWDG only was set, re-start the complete test (indicates a reset triggered by safety routines */
    if ((RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_PINRSTF)  != RESET) 
     && (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_IWDGRSTF) != RESET))
    {
      RCC_ClearResetFlag();
      #ifdef STL_VERBOSE_POR
      printf("... IWDG reset, WDG test completed ... \r\n");
      #endif  /* STL_VERBOSE_POR */
    }
    else  /* If IWDG only was set, continue the test with WWDG test*/
    {
      RCC_ClearResetFlag();
      #ifdef STL_VERBOSE_POR
      printf("...Unexpected Flag configuration, re-start WDG test... \r\n");
      #endif  /* STL_VERBOSE_POR */
      NVIC_SystemReset();
    } 
  }
}


/******************* (C)  *****END OF FILE****/
