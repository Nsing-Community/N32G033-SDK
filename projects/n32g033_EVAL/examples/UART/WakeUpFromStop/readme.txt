1、功能说明

    该示例演示了UART3的低功耗唤醒功能。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件开发环境：
            基于评估板N32G033K8Q7-1_STB V1.0开发


3、使用说明

    系统时钟配置如下：
    - 系统时钟 = 32KHz
    
    UART配置如下：
    - 波特率 = 2000 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 接收器和发送器使能
    - 16倍过采样
    
    UART引脚连接如下：    
    - UART3_Tx.PA2   <------->   PC_RX
    - UART3_Rx.PA3   <------->   PC_TX

    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 通过串口工具看到在打印递加数，下发0x55,打印暂停，再打印0x55，打印继续。


4、注意事项
    无

1. Function description

    This example demonstrates the low-power wake-up function of UART3.

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0

3. How to use

    The system clock configuration is as follows:
    -System clock = 32KHz
    
    The UART configuration is as follows:
    -Baud rate = 2000 baud
    -Word length = 8 data bits
    -1 stop bit
    -Verification control disabled
    -Receiver and transmitter enable
    -16 times oversampling
    
    The UART pin connections are as follows:
    - UART3_Tx.PA2   <------->   PC_RX
    - UART3_Rx.PA3   <------->   PC_TX

    
    Test steps and phenomena:
    -After the Demo is compiled in the KEIL environment, download it to the MCU
    -By using the serial port tool, when printing the increment, issue 0x55, pause the printing, 
     then print 0x55 again, and continue printing.


4. Attention
    None
    