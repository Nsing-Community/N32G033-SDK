1、功能说明
    1、TIM3 CH1 CH2 CH3 CH4输出频率相同占空比不同的PWM
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
        4、TIM：
            TIM3 CH1 CH2 CH3 CH4周期相等，占空比不等
        
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM3 CH1 CH2 CH3 CH4的波形
        2、程序运行后，产生4路周期相等占空比不同的PWM信号

1. Function description
    1. TIM3 CH1 CH2 CH3 CH4 output frequency the same duty cycle different PWM
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
        4. TIM:
            TIM3 CH1 CH2 CH3 CH4 has the same period, and the duty cycle is not equal
    Instructions:
        1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveforms of TIM3 CH1, CH2, CH3, CH4
        2. After the program runs, 4 PWM signals with equal period and different duty cycle are generated
4. Attention
    without