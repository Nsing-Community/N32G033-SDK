1、功能说明
    1、TIM4 CH2上升沿计算频率
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
            TIM4 上升沿中断打开
        4、端口配置：
            PA1选择为TIM4的CH2输入
            PA3选择为IO输出
        5、TIM：
            TIM4 配置CH2上升沿触发CH1输出一个单脉冲
    使用方法：
        1、编译后打开调试模式，PA3连接PA1，将变量TIM4Freq添加到watch窗口
        2、通过调试窗口修改gOnePulsEn为1，PA3会有电平翻转
        3、程序控制PA3电平翻转后，查看TIM4Freq计算的频率值

1. Function description

    1. TIM4 CH2 rising edge calculation frequency
    
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
            TIM4 CH2 rising edge interrupt is turned on
        4. Port configuration:
            PA1 is selected as the CH2 input of TIM4
            PA3 is selected as IO output
        5. TIM:
            TIM4 CH2 rising edge capture interrupt is turned on
    Instructions:
        1. After compiling, open the debug mode, connect PA3 and PA1, and add the variable TIM4Freq to the watch window
        2. Modify gOnePulsEn to 1 in the debug mode and flip the PA3 pin level
        3. After the program controls the level of PA3 to flip, check the frequency value calculated by TIM4Freq
4. Attention
    without