1、功能说明

    这个例程配置并演示使用EXIT外部中断及TIM定时器中断。 


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
    
    EXIT：PA4为浮空输入模式，外部中断线 - EXIT_LINE1，开启外部中断
    TIM：预分频系数 - （SystemClock/1200-1），周期 - （1200-1），开启定时器中断

    
    测试步骤与现象：
    a，编译下载代码复位运行
    b，查看串口打印信息，定时器中断信息每1S打印一次，按下按键KEY1(PA4)打印停止，再次按下则继续打印，表明程序运行正常；


4、注意事项


1. Function description

    This routine configures and demonstrates the use of EXIT external interrupt and TIM timer interrupt.

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
    
    EXIT: PA4 is floating input mode, external interrupt line - EXIT_LINE1, open external interrupt
    TIM: prescale factor - (SystemClock/1200-1), period - (1200-1), enable timer interrupt

    
    Test steps and phenomena:
    A. Compile download code reset run
    B. Check the serial port printing information, the timer interrupt information is printed every 1S, press the button KEY1(PA4) to stop printing, 
       press it again to continue printing, indicating that the program is running normally


4. Attention
