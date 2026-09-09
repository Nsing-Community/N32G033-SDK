1、功能说明

    这个例程配置并演示如何修改线程模式特权访问及堆栈。


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
    1.编译后下载程序复位运行；
    2.可使用编译器的“Cortex寄存器”窗口查看线程模式下，使用的堆栈及代码的访问级别（特权级/非特权级）；


4、注意事项


1. Function description

    This routine configures and demonstrates how to modify thread mode privileged access and stack.

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
    1. After compiling, download the program to reset and run;
    2. You can use the "Cortex Register" window of the compiler to view the stack used in thread mode and the access level of the code (privileged level/unprivileged level);


4. Attention
