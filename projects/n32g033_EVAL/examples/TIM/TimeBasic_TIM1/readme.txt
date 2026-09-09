1、功能说明
    1、TIM1 利用更新中断，产生定时翻转IO
2、使用环境
    软件开发环境：KEIL MDK-ARM 5.34
                IAR EWARM 8.50.1
    硬件开发环境： 
        N32G033系列：
            基于评估板N32G033K8Q7-1_STB V1.0开发
3、使用说明
    系统配置:
        1、时钟源：HSI
        2、时钟频率：
            N32G033系列：
                SYS_CLK=64M,TIM1_CLK=64M
        3、中断：
            TIM1 更新中断打开
        4、端口配置：
            PA4选择为IO输出
        5、TIM：
            TIM1使能周期中断
        
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PA4的波形
        2、程序运行后，TIM1的周期中断来临翻转PA4电平


1. Function description
    1. TIM1 outputs 4 complementary waveforms
2. Development environment
    Software development environment:  KEIL MDK-ARM 5.34
                                       IAR EWARM 8.50.1
    Hardware development environment:
        N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0
3. How to use
    System Configuration;
        1. Clock source: HSI
        2. Clock frequency: 
            N32G033 series:
                SYS_CLK=64M,TIM1_CLK=64M        
        3. Interruption:
            TIM1 update interrupt is turned on
        4. Port configuration:
            PA4 is selected as IO output
        5. TIM:
            TIM1 enables periodic interrupts
    Instructions:
        1. After compiling, turn on the debug mode and observe the waveform of PA4 with an oscilloscope or logic analyzer
        2. After the program runs, the periodic interrupt of TIM1 comes to flip the PA4 level
4. Attention
    without