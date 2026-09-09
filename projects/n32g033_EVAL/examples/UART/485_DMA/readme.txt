1、功能说明

    该测例演示了USARTy与USARTz间通过DMA（查询）实现的基础通信。
    首先，DMA传输TxBuffer1数据至USARTy发送数据寄存器，随后数据发送至
USARTz。USARTz接收数据，DMA从USARTz接收数据寄存器搬移数据至RxBuffer2。
    比较收、发数据，比较结果存入TransferStatus2变量。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件开发环境：
            基于评估板N32G033K8Q7-1_STB V1.0开发


3、使用说明

    系统时钟配置如下：
    - 系统时钟 = 64MHz
    
    UART配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 接收器和发送器使能
    - 16倍过采样
    
    UART引脚连接如下：    
    - UART1_Tx.PA2   <------->   UART2_Rx.PA0
    - UART1_Rx.PA3   <------->   UART2_Tx.PA1

    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，查看变量TransferStatus2，其中，PASSED为测试通过，FAILED为测试异常


4、注意事项

    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开

1. Function description

    This test example demonstrates basic communication between USARTy and USARTz through DMA. 
    First, the DMA transfers the TxBuffer1 data to the USARTy transmit data register, and then the data is sent to the 
USARTz. USARTz uses the interrupt to receive data and store it in RxBuffer2. 
    Compare data received and sent, and store the comparison results in the TransferStatus 2 variable.

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0

3. How to use

    The system clock configuration is as follows:
    -System clock = 64MHz
    
    The UART configuration is as follows:
    -Baud rate = 115200 baud
    -Word length = 8 data bits
    -1 stop bit
    -Verification control disabled
    -Receiver and transmitter enable
    -16 times oversampling
    
    The UART pin connections are as follows:
    - UART1_Tx.PA2   <------->   UART2_Rx.PA0
    - UART1_Rx.PA3   <------->   UART2_Tx.PA1

    
    Test steps and phenomena:
    -After the Demo is compiled in the KEIL environment, download it to the MCU
    -Reset operation, check the variables TransferStatus2 in turn, among them,
      PASSED means the test passed, FAILED means the test is abnormal


4. Attention

    the MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first