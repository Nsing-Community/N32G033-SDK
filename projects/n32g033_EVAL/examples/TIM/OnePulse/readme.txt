1、功能说明
    1、TIM4 CH2上升沿触发CH1输出一个单脉冲
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
            PA0选择为TIM4的CH1输出
            PA1选择为TIM4的CH2输入
            PA3选择为IO输出
        4、TIM：
            TIM4 配置CH2上升沿触发CH1输出一个单脉冲
    使用方法：
        1、编译后打开调试模式，PA3连接PA1，用示波器或者逻辑分析仪观察TIM4 的CH1 的波形
        2、通过调试窗口配置gSendTrigEn=1，程序发送PA3的上升沿，TIM4 CH1输出一个单脉冲

1. Function description
    1. The rising edge of TIM4 CH2 triggers CH1 to output a single pulse
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
            PA0 is selected as the CH1 output of TIM4
            PA1 is selected as the CH2 input of TIM4
            PA3 is selected as IO output
        4. TIM:
            TIM4 configures the rising edge of CH2 to trigger CH1 to output a single pulse
    Instructions:
        1. After compiling, turn on the debug mode, connect PA3 to PA1, and use an oscilloscope or logic analyzer to observe the waveform of CH1 of TIM4
        2. Configure gSendTrigEn=1 in the debug window,the program sends the rising edge of PA3, and TIM4 CH1 outputs a single pulse
4. Attention
    without