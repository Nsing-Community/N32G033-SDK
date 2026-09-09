1、功能说明

    此例程展示通过FreeRTOS调度实现LED和串口打印任务，并额外有一个TIM中断在工作执行。 


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
    
    GPIO：PB1控制LED3，PA7 控制 LED2

    
    测试步骤与现象：
    a，编译下载代码复位运行
    b，LED2每500ms闪烁一次，LED3每1S闪烁一次，串口每秒打印一个累加数；


4、注意事项
    systick作为时间基准源，并配置为1ms tick


1. Function description

    This example shows the implementation of LED and serial printing tasks through FreeRTOS scheduling, with an additional TIM interrupt during work execution.

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
    
    GPIO：PB1 controls LED3, PA7 controls LED2

    
    Test steps and phenomena:
    A. Compile download code reset run
    B. LED2 flashes once every 500ms, LED3 flashes once every 1S, and the serial port prints one cumulative count per second;


4. Attention
    Systick serves as the time reference source and is configured as a 1ms tick
