1、功能说明
    1、TIM3 CH2捕获引脚通过CH1下降沿和CH2上升沿计算占空比和频率
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
            PA1选择为TIM3 CH2输入
            PA3选择为IO 输出
        5、TIM：
            TIM3 CH1下降沿捕获CH2信号，CH2上升沿捕获CH2信号
        
    使用方法：
        1、编译后打开调试模式，连接PA3与PA1，将Frequency、DutyCycle添加到watch窗口
        2、程序运行后，PA3发送的脉冲数据可以被捕获到占空比和频率到变量

1. Function description
    1. After TIM3 CH1 CH2 CH3 CH4 reaches the CC value, correspondingly pull down the IO level of PA1, PA2, PA3, and PA4
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
            PA1 is selected as TIM3 CH2 input
            PA3 is selected as IO output
        5. TIM:
            TIM3 CH1 falling edge captures CH2 signal, CH2 rising edge captures CH2 signal
    Instructions:
        1. After compiling, open the debug mode, connect PA3 and PA1, and add Frequency and DutyCycle to the watch window
        2. After the program runs, the pulse data sent by PA3 can be captured to the duty cycle and frequency to the variable
4. Attention
    without