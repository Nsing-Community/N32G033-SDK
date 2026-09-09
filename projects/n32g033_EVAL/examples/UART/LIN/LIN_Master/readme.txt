1、功能说明

    该演示显示了USART模块LIN模式作为主节点轮询发送主请求帧（0x3C）和从应答帧（0x3D）。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件开发环境：
            基于评估板N32G033K8Q7-1_STB V1.0开发


3、使用说明

    系统时钟配置如下：
    - 系统时钟 = 64MHz
    
    打印串口配置：
            UART1：TX - PA9，RX - PA10，波特率115200
    
    UART配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 接收器和发送器使能
    - 16倍过采样
    
    UART引脚连接如下：    
    - UART2_Tx.PA1   <------->   UART2_Rx.PA0
    - UART2_Rx.PA0   <------->   UART2_Tx.PA1

    
    测试步骤与现象：
    a、 跳线连接到主机的从属引脚
    b、 一个开发板编译并下载LIN_Master代码作为主代码
         另一个开发板编译并下载LIN_Slave代码作为从属代码
    c、 重置从设备，然后重置主设备
    d、 主轮询发送请求帧（0x3C）和应答帧（0x3D）
         发送请求帧（0x3C）：主设备向从设备发送一个8字节的0x0F，并打印相关信息
         发送应答帧（0x3D）：从机收到应答帧后，向主机回复8字节0x01消息，并且主控打印相关信息


4、注意事项


1. Function description

    This demo shows that the USART module LIN mode as the master node polling to send the master
    request frame (0x3C) and the slave reply frame (0x3D). 

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0

3. How to use

    The system clock configuration is as follows:
    -System clock = 64MHz
    
    Print Serial Port Configuration:
                UART1：TX - PA9，RX - PA10，Baud rate 115200
    
    The UART configuration is as follows:
    -Baud rate = 115200 baud
    -Word length = 8 data bits
    -1 stop bit
    -Verification control disabled
    -Receiver and transmitter enable
    -16 times oversampling

    
    The UART pin connections are as follows:
    - UART2_Tx.PA1   <------->   UART2_Rx.PA0
    - UART2_Rx.PA0   <------->   UART2_Tx.PA1

    
    Test steps and phenomena:
    a, the jumper connects to the slave pin of the master
    b, one development board compiles and downloads LIN_Master code as the master and 
        the other development board compiles and downloads LIN_Slave code as the slave
    c, Reset the slave and then the master
    d, master polling sends request frame (0x3C) and reply frame (0x3D)
       Sending request frame (0x3C) : The master sends an 8-byte 0x0F to the slave and prints the related information
       Sending reply frame (0x3D) : After receiving a reply frame, the slave reply an 8-byte 0x01 message to the master, 
        and the master prints the related information


4. Attention

