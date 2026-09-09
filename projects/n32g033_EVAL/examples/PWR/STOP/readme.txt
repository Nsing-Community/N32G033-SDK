1、功能说明
1、STOP进入和唤醒退出示例。


2、使用环境

    /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：KEIL MDK-ARM 5.34.0.0
            IAR EWARM 8.50.1
      
    /* 硬件环境：工程对应的开发硬件平台 */
     N32G033系列：
            基于评估板N32G033K8Q7-1_STB V1.0开发
     


3、使用说明

    系统配置；
        1、时钟源：HSI
        2、时钟频率：64M
        3、唤醒引脚：PA0
        4、打印：PA9-115200

    使用方法：
        在KEIL下编译后烧录到评估板，上电输出打印“PWR_STOP INIT”。过了一会输出打印“STOP ENTRY”，表明进入STOP了。
        按下PA0按键后，串口又输出“STOP EXIT”，表明MCU被唤醒了.从停止的位置执行。


4、注意事项
    


1. Function description
    1. Example of STOP entry and wake-up exit.


2. Development environment

    /* Software development environment: the name and version number of the software tool used in the current project */
    IDE tool: KEIL MDK-ARM 5.34.0.0
            IAR EWARM 8.50.1
      
    /* Hardware environment: the development hardware platform corresponding to the project */
     N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0


3. How to use

    System Configuration;
        1. Clock source: HSI
        2. Clock frequency: 64M
        3. Wakeup pin: PA0
        4. Log: PA9-115200

    Instructions:
        After compiling under KEIL and burning it to the evaluation board, the output prints "PWR_STOP INIT" after power-on. After a while, the output prints "STOP ENTRY", indicating that it has entered STOP.
        After pressing the PA0 button, the serial port outputs "STOP EXIT" again, indicating that the MCU is awakened. Execute from the stopped position.


4. Attention
   
