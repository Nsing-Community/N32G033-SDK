1、功能说明

    这个例程配置并演示对选项字节的操作。 


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
    
    UART引脚连接如下：
    - TX - PA9，RX - PA10

    
    测试步骤与现象：
    a，编译下载代码复位运行
    b，对选项字节进行编程，编程OK，打印信息为测试通过


4、注意事项


1. Function description

    This routine configures and demonstrates the operation of option bytes.

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
    
    The UART pin connections are as follows:
    - TX - PA9, RX - PA10, baud rate 115200

    
    Test steps and phenomena:
    A. Compile download code reset run
    B. Check the printing information of the serial port. When the data written to FLASH is the same as the data read, the printing information is the end of the test


4. Attention
