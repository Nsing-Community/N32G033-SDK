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
#ifndef __N32_CM0_STLLIB_H
#define __N32_CM0_STLLIB_H

#include "stdio.h"
/* Includes ------------------------------------------------------------------*/
#if defined (N32G033) 
#include "n32g033.h"
#include "misc.h"
#include "n32g033_gpio.h"
#include "n32g033_uart.h"
#include "n32g033_flash.h"
#include "n32g033_rcc.h"
#include "n32g033_pwr.h"
#include "n32g033_tim.h"
#include "n32g033_iwdg.h"
#else
#error Chip family definition error
#endif


#if defined (N32G033)
#define USART1                       UART1
#define USART_InitType                  UART_InitType
#define USART_Enable                  UART_Enable
#define GPIO_AFX_USART1                 GPIO_AF4
#define USART_StructInit           UART_StructInit
#define USART_Init                 UART_Init

#define USART_GetFlagStatus        UART_GetFlagStatus
#define USART_SendData             UART_SendData
#define GPIO_Mode_AF_PP            GPIO_MODE_AF_PP

#define RCC_LSCTRL_FLAG_LSIRD     RCC_CLKINT_FLAG_LSIRDF
#define USART_WL_8B                  UART_WL_8B
#define USART_STPB_1                 UART_STPB_1
#define USART_PE_NO                  UART_PE_NO
#define USART_MODE_RX                UART_MODE_RX
#define USART_MODE_TX                UART_MODE_TX
#define USART_FLAG_TXC                UART_FLAG_TXC


#else
#error Chip family definition error
#endif

typedef enum {
              TEST_RUNNING,
              CLASS_B_DATA_FAIL,
              CTRL_FLW_ERROR,
              TEST_FAILURE,
              TEST_OK
              } ClassBTestStatus;

/* class B Variable */
#include "n32_cm0_STLparam.h"
#include "n32_cm0_STLclassBvar.h"
	
/* Self Test library routines main flow after initialization and at run */
#include "n32_cm0_STLstartup.h"
#include "n32_cm0_STLmain.h"

/* Cortex-M4 CPU test */
#include "n32_cm0_STLcpu.h"

/* Clock frequency test */
#include "n32_cm0_STLclock.h"

/* Invariable memory test */
#include "n32_cm0_STLcrc32.h"

/* Variable memory test */
#include "n32_cm0_STLRam.h"


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __n32_cm0_STL_LIB_H */

/******************* (C)  *****END OF FILE****/
