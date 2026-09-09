1、功能说明
    1、TIM3 CH1 CH2 CH3 CH4 达到CC值后，输出ACTIVE电平
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
            PA0选择为TIM3的CH1输出
            PA1选择为TIM3的CH2输出
            PB0选择为TIM3的CH3输出
            PB1选择为TIM3的CH4输出
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM3 CH1 CH2 CH3 CH4的波形
        2、定时器运行到CC1 CC2 CC3 CC4之后，对应通道的输出变为Active
4、注意事项 
    无

1. Function description
    After TIM3 CH1 CH2 CH3 CH4 reaches the CC value, it outputs ACTIVE level
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
        3. Port configuration:
            PA0 is selected as the CH1 output of TIM3
            PA1 is selected as the CH2 output of TIM3
            PB0 is selected as the CH3 output of TIM3
            PB1 is selected as the CH4 output of TIM3
    Instructions:
        1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveform of TIM3 CH1 CH2 CH3 CH4
        2. After the timer runs to CC1 CC2 CC3 CC4, the output of the corresponding channel becomes Active
4. Attention
    without