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

/**
*\*\file main.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#include "main.h"


#define FLASH_WriteAddress  0x100000
#define FLASH_ReadAddress   FLASH_WriteAddress
#define FLASH_SectorToErase FLASH_WriteAddress

#define sFLASH_ID sFLASH_W25Q128_ID

#define BufferSize (countof(Tx_Buffer) - 1)

#define countof(a) (sizeof(a) / sizeof(*(a)))

uint8_t Tx_Buffer[] = "N32G03x SPI Firmware Library Example: communication with an GD25Q16 SPI FLASH";
uint8_t Rx_Buffer[BufferSize];
__IO uint8_t Index                  = 0x0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = PASSED;
__IO uint32_t FlashID = 0;



/** Main program. **/
int main(void)
{
    log_init();
    
    log_info(" This is SPI FLASH demo! \r\n");
    
    /* Initialize the SPI FLASH driver */
    sFLASH_Init();
    
    /* Get SPI Flash ID */
    FlashID = sFLASH_ReadID();

    /* Check the SPI Flash ID */
    if (FlashID == sFLASH_ID)
    {
        /* Perform a write in the Flash followed by a read of the written data */
        /* Erase SPI FLASH Sector to write on */
        sFLASH_EraseSector(FLASH_SectorToErase);

        /* Write Tx_Buffer data to SPI FLASH memory */
        sFLASH_WriteBuffer(Tx_Buffer, FLASH_WriteAddress, BufferSize);

        /* Read data from SPI FLASH memory */
        sFLASH_ReadBuffer(Rx_Buffer, FLASH_ReadAddress, BufferSize);

        /* Check the correctness of written dada */
        TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
        /* TransferStatus1 = PASSED, if the transmitted and received data by SPI1
           are the same */
        /* TransferStatus1 = FAILED, if the transmitted and received data by SPI1
           are different */

        /* Perform an erase in the Flash followed by a read of the written data */
        /* Erase SPI FLASH Sector to write on */
        sFLASH_EraseSector(FLASH_SectorToErase);

        /* Read data from SPI FLASH memory */
        sFLASH_ReadBuffer(Rx_Buffer, FLASH_ReadAddress, BufferSize);

        /* Check the correctness of erasing operation dada */
        for (Index = 0; Index < BufferSize; Index++)
        {
            if (Rx_Buffer[Index] != 0xFF)
            {
                TransferStatus2 = FAILED;
            }
        }
        /* TransferStatus2 = PASSED, if the specified sector part is erased */
        /* TransferStatus2 = FAILED, if the specified sector part is not well erased */
    }
    else
    {

    }
    
    if(TransferStatus1 == PASSED)
    {
        log_info("SPI FLASH read write OK! \r\n");
    }
    else
    {
        log_info("SPI FLASH read write Fail! \r\n");
    }
    
    if(TransferStatus2 == PASSED)
    {
        log_info("SPI FLASH read erase OK! \r\n");
    }
    else
    {
        log_info("SPI FLASH read erase Fail! \r\n");
    }
    
    while (1)
    {
    }
}

/**
*\*\name    Buffercmp.
*\*\fun     Compares two buffers.
*\*\param   pBuffer1
*\*\param   pBuffer2
*\*\param   BufferLength
*\*\return  FAILED or PASSED
**/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}












