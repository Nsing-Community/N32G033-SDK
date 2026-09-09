1、功能说明
    1、TIM1输出4对互补波形
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
        3、端口配置：
            PA4 选择为TIM1 CH1输出
            PA3 选择为TIM1 CH2输出
            PA5 选择为TIM1 CH3输出
            PB3 选择为TIM1 CH4输出
            PA7 选择为TIM1 CH1N输出
            PB4 选择为TIM1 CH2N输出
            PB5 选择为TIM1 CH3N输出
            PB6 选择为TIM1 CH4N输出    
            PA2 选择为刹车输入
        4、TIM：
            TIM1 4对互补输出带死区，PA2刹车
        
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1的波形
        2、PA2拉低可观察到4对互补PWM，PA2拉高PWM消失


1. Function description

    1. TIM1 outputs 4 complementary waveforms
    
2. Development environment

    Software development environment:KEIL MDK-ARM 5.34
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
        3. Port configuration:
            PA4 is selected as TIM1 CH1 output
            PA3 is selected as TIM1 CH2 output
            PA5 is selected as TIM1 CH3 output
            PB3 is selected as TIM1 CH4 output
            PA7 is selected as TIM1 CH1N output
            PB4 is selected as TIM1 CH2N output
            PB5 is selected as TIM1 CH3N output
            PB6 is selected as TIM1 CH4N output
            PA2 is selected as break input
        4. TIM:
            TIM1 4-pair complementary with dead zone, PA2 is brake input
    Instructions:
        1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveform of TIM1
        2. When PA2 is low, 4 complementary PWM can be observed, and when PA2 is high, PWM disappears
4. Attention
    without