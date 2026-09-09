1、功能说明
    1、TIM3 利用CH1 CH2 CH3 CH4 CC值产生定时中断，翻转IO电平
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
            PA3选择为IO输出
            PA4选择为IO输出
            PA5选择为IO输出
            PA6选择为IO输出
        5、TIM：
            TIM3输出冻结模式，CH1 CH2 CH3 CH4比较值产生中断
        
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PA3、PA4、PA5、PA6的波形
        2、程序运行后，对应通道达到比较值后，比较值累加并翻转对应IO口电平


1. Function description
    1. TIM3 uses CH1, CH2, CH3, CH4, and CC values to generate timing interrupts and flip IO levels.
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
            PA3 is selected as IO output
            PA4 is selected as IO output
            PA5 is selected as IO output
            PA6 is selected as IO output
        5. TIM:
            TIM1 enables periodic interrupts
    Instructions:
        1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveforms of PA3, PA4, PA5, and PA6
        2. After the program runs, after the corresponding channel reaches the comparison value, the comparison value accumulates and flips the corresponding IO port level
4. Attention
    without