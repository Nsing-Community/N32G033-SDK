1、功能说明
    1、systick 100ms触发TIM1输出6步换相波形
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
            TIM1 COM事件中断打开，抢断优先级1
                    Systick 10ms中断，优先级0
        4、端口配置：
            PA4选择为TIM1 CH1输出
            PA3选择为TIM1 CH2输出
            PA5选择为TIM1 CH3输出
            PA7选择为TIM1 CH1N输出
            PB4选择为TIM1 CH2N输出
            PB5选择为TIM1 CH3N输出
        5、TIM：
            TIM1 6路互补冻结输出模式，无刹车，开COM中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1的输出波形
        2、每隔100ms systick触发COM中断，在ATIM的COM中断里面输出AB AC BC BA CA CB的6步换相波形


1. Function description

    1. This routine shows the IO control LED blinking
    
2. Development environment

    Software development environment:  KEIL MDK-ARM 5.34
                                       IAR EWARM 8.50.1
    Hardware development environment:
        N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0
3. How to use
    TIM1 COM event interrupt on, steal priority level 1
    Systick 10ms interrupt, priority 0

    System Configuration;
        1. Clock source: HSI
        2. Clock frequency: 
            N32H473/474 series:
                HSYS_CLK=64M,TIM1_CLK=64M
        3. Interrupt:
            TIM1 COM event interrupt on, steal priority level 1
            Systick 10ms interrupt, priority 0
        4. Port configuration:
            PA4 is selected as TIM1 CH1 output
            PA3 is selected as TIM1 CH2 output
            PA5 is selected as TIM1 CH3 output
            PA7 is selected as TIM1 CH1N output
            PB4 is selected as TIM1 CH2N output
            PB5 is selected as TIM1 CH3N output
        5. TIM:
           TIM1 6-channel complementary freeze output mode, no brake, open COM interrupt
    Instructions:
        1. Open the debug mode after compiling, and observe the output waveform of TIM1 with an oscilloscope or logic analyzer
        2. The systick triggers the COM interrupt every 100ms, and outputs the 6-step commutation waveform of AB AC BC BA CA CB in the COM interrupt of the ATIM
        
4. Attention
    No