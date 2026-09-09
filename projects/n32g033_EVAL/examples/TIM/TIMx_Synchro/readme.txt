1、功能说明
    1、TIM3 在 TIM1 周期下计数
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
            PA4选择为TIM1 CH1输出
            PA6选择为TIM3 CH1输出
        4、TIM：
            TIM1 CH1 周期触发 TIM3 的门控

    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1 CH1、TIM3 CH1的波形
        2、程序运行后，TIM3 15倍周期TIM1


1. Function description
    1. TIM3 counts under the TIM1 cycle
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
            PA4 is selected as the CH1 output of TIM1
            PA6 is selected as the CH1 output of TIM3
        4. TIM:
            TIM1 CH1 period triggers the gating of TIM3
    Instructions:
        1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveforms of TIM1 CH1, TIM3
        2. After the program runs, TIM3 15 times cycle TIM1
4. Attention
    without