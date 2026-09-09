1、功能说明

    /* 简单描述工程功能 */
    这个例程配置并演示设置不同的系统时钟，并用MCO从PA8输出


2、使用环境

    /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：KEIL MDK-ARM 5.34.0.0
            IAR EWARM 8.50.1
      
    /* 硬件环境：工程对应的开发硬件平台 */
     N32G033系列：
            基于评估板N32G033K8Q7-1_STB V1.0开发
     

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    USART：TX - PA9，波特率115200
    GPIO：PA8 - 复用为MC0时钟输出

    /* 描述Demo的测试步骤和现象 */
    1.编译后下载程序复位运行；
    2.分别配置系统时钟为HSI、HSI/2、LSI，分别使用串口打印出当前SYSCLK、HCLK、PCLK等信息，并且可以使用PA8复用引脚输出时钟，用示波器查看；


4、注意事项
   当系统时钟为LSI时，波特率设置为1200才能打印
    

1. Function description

     /* Briefly describe the engineering function */
     This example configures and demonstrates the setting of different system clocks, and uses MCO to output from PA8


2. Development environment

    /* Software development environment: the name and version number of the software tool used in the current project */
    IDE tool: KEIL MDK-ARM 5.34.0.0
            IAR EWARM 8.50.1
      
    /* Hardware environment: the development hardware platform corresponding to the project */
     N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0

3. How to use

     /* Describe the configuration method of related modules; for example: clock, I/O, etc. */
     USART: TX-PA9, baud rate 115200
     GPIO: PA8-multiplexed as MC0 clock output

     /* Describe the test steps and phenomena of Demo */
     1. After compiling, download the program to reset and run;
     2. Configure the system clock as HSI, HSI/2 and LSI respectively, and use the serial port to print out the current SYSCLK, HCLK, PCLK and other information, 
     and use the PA8 multiplex pin to output the clock and view it with an oscilloscope;


4. Attention
    Printing is only possible when system clock is LSI and the baud rate is configured to 1200