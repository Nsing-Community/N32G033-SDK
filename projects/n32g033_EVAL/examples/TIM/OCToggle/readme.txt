1、功能说明
    1、TIM3 CH1 CH2 CH3 CH4 达到CC值后输出翻转，并且比较值累加
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
            PA0选择为TIM3的CH1输出
            PA1选择为TIM3的CH2输出
            PB0选择为TIM3的CH3输出
            PB1选择为TIM3的CH4输出
        5、TIM：
            TIM3 配置好CH1 CH2 CH3 CH4的比较值输出翻转，并打开比较中断
        
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM3 的CH1 CH2 CH3 CH4的波形
        2、每当达到比较值时，输出翻转，并且再增加同样的比较值，波形占空比为50%

1. Function description
    When TIM3 CH1 CH2 CH3 CH4 reaches the CC value, the output is reversed, and the comparison value is accumulated
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
            PA0 is selected as the CH1 output of TIM3
            PA1 is selected as the CH2 output of TIM3
            PB0 is selected as the CH3 output of TIM3
            PB1 is selected as the CH4 output of TIM3
        5. TIM:
            TIM3 configures the comparison value output of CH1, CH2, CH3, CH4, and turns on the comparison interrupt
    Instructions:
        1. After compiling, turn on the debug mode and use an oscilloscope or logic analyzer to observe the waveform of CH1 CH2 CH3 CH4 of TIM3
        2. Whenever the comparison value is reached, the output is reversed, and the same comparison value is increased again, and the waveform duty cycle is 50%
4. Attention
    without