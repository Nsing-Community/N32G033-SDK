/**
*     Copyright (c) 2025, Nations Technologies Inc.
*
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter
* referred to as NATIONS). This software, and the product of NATIONS described herein
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other
* intellectual property rights. Names and brands of third party may be mentioned or referred
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and
* improvements to this software at any time without notice. Please contact NATIONS and obtain
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes
* no responsibility for the accuracy and reliability of this software.
*
*     It is the responsibility of the user of this software to properly design, program, and test
* the functionality and safety of any application made of this information and any resulting product.
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations.
* User shall comply with any applicable export control laws and regulations promulgated and administered by
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 *\*\file main.c
 *\*\author Nations
 *\*\version v1.0.0
 *\*\copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 **/
#include "main.h"
#include "log.h"
#include "led.h"
#include "timer.h"

#include "FreeRTOS.h"
#include "task.h"

/** Task priority **/
#define START_TASK_PRIO      0
#define LOG_TASK_PRIO        1
#define LED_TASK_PRIO        2

/** Task stack size **/
#define START_STK_SIZE       100  
#define LED_STK_SIZE         100 
#define LOG_STK_SIZE         100

/** task handle **/
TaskHandle_t StartTask_Handler;
TaskHandle_t LEDTask_Handler;
TaskHandle_t LOGTask_Handler;

/** Task function **/
void start_task(void *pvParameters);
void led_task(void *pvParameters);
void log_task(void *pvParameters);

void bsp_initialized(void);

/**
 *\*\name    main.
 *\*\fun     Main program.
 *\*\param   none
 *\*\return  none
 **/
int main(void)
{
    /* hardware initialization */
    bsp_initialized();
    
    /* Create Start Task */
    xTaskCreate((TaskFunction_t )start_task,            //Task function
                (const char*    )"start_task",          //Task name
                (uint16_t       )START_STK_SIZE,        //Task stack size
                (void*          )NULL,                  //Parameters passed to the task function
                (UBaseType_t    )START_TASK_PRIO,       //Task priority
                (TaskHandle_t*  )&StartTask_Handler);   //task handle 

    /* Start task scheduling */
    vTaskStartScheduler();    

    while (1)
    {
    }
}

/**
 *\*\name    bsp_initialized.
 *\*\fun     hardware initialization.
 *\*\param   none
 *\*\return  none
 **/
void bsp_initialized(void)
{
    log_init();
    LED_GPIO_Config();
    TIM3_Config();
    SysTick_Config(SystemCoreClock / configTICK_RATE_HZ);

    printf("bsp_initialized \r\n");
}

/**
 *\*\name    start_task.
 *\*\fun     Start Task Function.
 *\*\param   none
 *\*\return  none
 **/
void start_task(void *pvParameters)
{
    /* Entering the critical zone */
    taskENTER_CRITICAL(); 
    
    /* Create LED Test task */
    xTaskCreate((TaskFunction_t )led_task,         
                (const char*    )"led_task",       
                (uint16_t       )LED_STK_SIZE, 
                (void*          )NULL,                
                (UBaseType_t    )LED_TASK_PRIO,    
                (TaskHandle_t*  )&LEDTask_Handler);   
    
    /* Create Uart Test task */
    xTaskCreate((TaskFunction_t )log_task,     
                (const char*    )"log_task",   
                (uint16_t       )LOG_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LOG_TASK_PRIO,
                (TaskHandle_t*  )&LOGTask_Handler);  

    /* Delete Start Task */
    vTaskDelete(StartTask_Handler);
    /* Exit the critical zone */            
    taskEXIT_CRITICAL();   
}

/**
 *\*\name    led_task.
 *\*\fun     LED flashing task.
 *\*\param   none
 *\*\return  none
 **/
void led_task(void *pvParameters)
{
    while(1)
    {
        GPIO_TogglePin(GPIOA, GPIO_PIN_7);
        vTaskDelay(500);
    }
}


/**
 *\*\name    log_task.
 *\*\fun     Serial port printing task.
 *\*\param   none
 *\*\return  none
 **/
void log_task(void *pvParameters)
{
    uint32_t num = 0;

    while(1)
    {
        num += 1;

        printf("num: %d \r\n",num);
        vTaskDelay(1000);
    }
}
