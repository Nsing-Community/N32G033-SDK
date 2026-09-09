1、功能说明
    1、TIM6 利用更新中断，唤醒STOP模式，LED（D1）闪烁。
2、使用环境
    软件开发环境：KEIL MDK-ARM 5.34
                IAR EWARM 8.50.1
    硬件开发环境： 
        N32G033系列：
            基于评估板N32G033K8Q7-1_STB V1.0开发
3、使用说明
    系统配置:
        1、时钟源：LSI
        2、时钟频率：
            N32G033系列：
                SYS_CLK=32K
        3、中断：
            TIM6 更新中断打开
        4、端口配置：
            PA6选择为IO输出，控制LED(D1)
        5、TIM：
            TIM6 使能周期中断
    使用方法：
        1、编译后下载程序复位运行；
        2、LED(D1) 闪烁；


1. Function description
    1.TIM6 uses the update interrupt to wake up from STOP mode, causing LED (D1) to blinking. 
2. Development environment
    Software development environment:  KEIL MDK-ARM 5.34
                                       IAR EWARM 8.50.1
    Hardware development environment:
        N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0
3. How to use
    System Configuration;
        1. Clock source: LSI
        2. Clock frequency: 
            N32G033 series:
                SYS_CLK=32K        
        3. Interruption:
            TIM6 update interrupt is turned on
        4. Port configuration:
            PA6 is selected as an I/O output to control LED (D1).
        5. TIM:
            TIM6 enables periodic interrupts
    Instructions:
        1. After compiling, download the program to reset and run
        2. LED (D1) to blinking
4. Attention
    No