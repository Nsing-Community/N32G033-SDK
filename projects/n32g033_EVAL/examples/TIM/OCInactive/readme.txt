1、功能说明
    1、TIM3 CH1 CH2 CH3 CH4 达到CC值后，对应拉低PA1 PA2 PA3 PA4的IO电平
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
            TIM3 比较中断打开
        4、端口配置：
            PA1选择为IO 输出
            PA2选择为IO 输出
            PA3选择为IO 输出
            PA4选择为IO 输出
        5、TIM：
            TIM3 配置好CH1 CH2 CH3 CH4的比较值输出翻转，并打开比较中断
        
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PA1 PA2 PA3 PA4的波形
        2、定时器运进入CC1 CC2 CC3 CC4中断后,对应拉低PA1 PA2 PA3 PA4的IO

1. Function description
    After TIM3 CH1 CH2 CH3 CH4 reaches the CC value, correspondingly pull down the IO level of PA1, PA2, PA3, and PA4
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
            TIM3 compare interrupt is turned on
        4. Port configuration:
            PA1 is selected as IO output
            PA2 is selected as IO output
            PA3 is selected as IO output
            PA4 is selected as IO output
        5. TIM:
            TIM3 configures the comparison value of CH1, CH2, CH3, CH4, and turns on the comparison interrupt
    Instructions:
        1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveforms of PA1, PA2, PA3, and PA4
        2. After the timer enters the CC1 CC2 CC3 CC4 interrupt, it will correspondingly pull down the IO of PA1 PA2 PA3 PA4
4. Attention
    without