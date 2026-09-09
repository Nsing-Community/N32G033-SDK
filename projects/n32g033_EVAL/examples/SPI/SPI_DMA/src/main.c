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


SPI_InitType SPI_InitStructure;
DMA_InitType DMA_InitStructure;
uint8_t SPI_Slave_Rx_Buffer[BUFFER_SIZE];
volatile Status TransferStatus1 = FAILED;

uint8_t SPI_Master_Tx_Buffer[BUFFER_SIZE] = {0xf1, 0x2e, 0xf1, 0xaf, 0x08, 0xa2, 0x41, 0xb4, 0xc8, 0x19, 0x38,
                                             0xb7, 0xd9, 0xdb, 0x9a, 0x64, 0x1f, 0xd6, 0x99, 0x9c, 0x0f, 0xae,
                                             0x84, 0xab, 0xda, 0x12, 0x95, 0x6c, 0xdb, 0xec, 0x06, 0x08};



/**
*\*\name    main.
*\*\fun     main program.
*\*\param   none
*\*\return  none 
**/
int main(void)
{
    log_init();
    log_info("\n This is a SPI_DMA to RAM Demo.\n");

    /* System Clocks Configuration */
    RCC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* SPI_MASTER configuration */
    SPI_InitStruct(&SPI_InitStructure);
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_8;
    SPI_InitStructure.FirstBit      = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly       = CRC_POLYNOMIAL;
    SPI_Init(SPI_MASTER, &SPI_InitStructure);

    /* SPI_SLAVE configuration */
    SPI_InitStructure.SpiMode = SPI_MODE_SLAVE;
    SPI_Init(SPI_SLAVE, &SPI_InitStructure);
    
    /* SPI_MASTER_RX_DMA_CHANNEL configuration */
    DMA_DeInit(SPI_MASTER_TX_DMA_CHANNEL);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&SPI1->DAT;
    DMA_InitStructure.MemAddr        = (uint32_t)SPI_Master_Tx_Buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = BUFFER_SIZE;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_LOW;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(SPI_MASTER_TX_DMA_CHANNEL, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_SPI1_TX,DMA,SPI_MASTER_TX_DMA_CHANNEL,ENABLE);

    /* SPI_SLAVE_RX_DMA_CHANNEL configuration */
    DMA_DeInit(SPI_SLAVE_RX_DMA_CHANNEL);
    DMA_InitStructure.PeriphAddr = (uint32_t)&SPI2->DAT;
    DMA_InitStructure.MemAddr    = (uint32_t)SPI_Slave_Rx_Buffer;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.Priority   = DMA_PRIORITY_VERY_HIGH;
    DMA_Init(SPI_SLAVE_RX_DMA_CHANNEL, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_SPI2_RX,DMA,SPI_SLAVE_RX_DMA_CHANNEL,ENABLE);

    
    /* Enable SPI_MASTER DMA Tx request */
    SPI_EnableDma(SPI_MASTER, SPI_DMA_TX, ENABLE);
    /* Enable SPI_SLAVE DMA Rx request */
    SPI_EnableDma(SPI_SLAVE, SPI_DMA_RX, ENABLE);
    
    /* Enable SPI_SLAVE */
    SPI_Enable(SPI_SLAVE, ENABLE);
    /* Enable SPI_MASTER */
    SPI_Enable(SPI_MASTER, ENABLE);
    
    /* Enable DMA channels */
    DMA_EnableChannel(SPI_SLAVE_RX_DMA_CHANNEL, ENABLE);
    DMA_EnableChannel(SPI_MASTER_TX_DMA_CHANNEL, ENABLE);

    /* Transfer complete */
    while (!DMA_GetFlagStatus(SPI_SLAVE_RX_DMA_FLAG, DMA))
        ;
    while (!DMA_GetFlagStatus(SPI_MASTER_TX_DMA_FLAG, DMA))
        ;

    /* Check the correctness of written dada */
    TransferStatus1 = Buffercmp(SPI_Slave_Rx_Buffer, SPI_Master_Tx_Buffer, BUFFER_SIZE);

    
    if (TransferStatus1 != FAILED)
    {
        log_info("SPI master passed.\n");
    }
    else
    {
        log_error("SPI master failed.\n");
    }

    while (1)
    {
    }
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\param   none
*\*\return  none 
**/
void RCC_Configuration(void)
{
    /* Enable peripheral clocks */
    /* Enable DMA clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);

    /* Enable GPIO clock*/
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_GPIO, ENABLE);

    /* Enable SPI clock */
    RCC_EnableAPBPeriphClk(RCC_APB_PERIPH_SPI1 | RCC_APB_PERIPH_SPI2, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports.
*\*\param   none
*\*\return  none 
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure SPI_MASTER pins */
    GPIO_InitStructure.Pin        = SPI_MASTER_SCK_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull  = GPIO_PULL_DOWN;
    GPIO_InitStructure.GPIO_Alternate = SPI_MASTER_SCK_GPIO_AF;
    GPIO_InitPeripheral(SPI_MASTER_SCK_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = SPI_MASTER_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull  = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_MASTER_MISO_GPIO_AF;
    GPIO_InitPeripheral(SPI_MASTER_MISO_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = SPI_MASTER_MOSI_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull  = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_MASTER_MOSI_GPIO_AF;
    GPIO_InitPeripheral(SPI_MASTER_MOSI_GPIO_PORT, &GPIO_InitStructure);
                
    /* Configure SPI_SLAVE pins */
    GPIO_InitStructure.Pin        = SPI_SLAVE_SCK_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull  = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_SLAVE_SCK_GPIO_AF;
    GPIO_InitPeripheral(SPI_SLAVE_SCK_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = SPI_SLAVE_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull  = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_SLAVE_MISO_GPIO_AF;
    GPIO_InitPeripheral(SPI_SLAVE_MISO_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = SPI_SLAVE_MOSI_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull  = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_SLAVE_MOSI_GPIO_AF;
    GPIO_InitPeripheral(SPI_SLAVE_MOSI_GPIO_PORT, &GPIO_InitStructure);
          
}


/**
*\*\name    Buffercmp.
*\*\fun     pBuffer, pBuffer1: buffers to be compared.
*\*\param   pBuffer,pBuffer1
*\*\return  - PASSED: pBuffer identical to pBuffer1 
*\*\return  - FAILED: pBuffer differs from pBuffer1 
**/
Status Buffercmp(uint8_t* pBuffer, uint8_t* pBuffer1, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer != *pBuffer1)
        {
            return FAILED;
        }

        pBuffer++;
        pBuffer1++;
    }

    return PASSED;
}



