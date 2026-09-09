1、功能说明

    1、COMP的输出刹车TIM1 的互补信号，COMP OUT变低后恢复TIM1波形


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件开发环境： 
        N32G033系列：
            基于评估板N32G033K8Q7-1_STB V1.0开发

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
          1、 SystemClock：64MHz
          2、端口配置：
            PA1选择为模拟功能COMP INP
            PA0选择为模拟功能COMP INM
            PA6选择为模拟功能COMP OUT
            PB0选择为IO输出
            PB1选择为IO输出
            PB3选择为TIM1 CH1输出
            PB4选择为TIM1 CH1N输出

    /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，将PA0连接到PB0，PA1连接到PB1，利用示波器或逻辑分析仪观察PA6和TIM1输出波形
        2、当软件输出PA1电平大于PA0时，TIM1波形消失，此时PA6输出高电平，相反时，波形正常输出，PA6输出低电平

4、注意事项
    无


1. Function description

    1. The output of COMP is the complementary signal of the brake TIM1. After COMP OUT goes low, the TIM1 waveform is restored.
    
2. Development environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0
        
3. How to use

    System Configuration;
        1. SystemClock：64MHz
        2. Port configuration:
            PA1 is selected as the analog function COMP INP
            PA0 is selected as the simulation function COMP INM
            PA6 is selected as emulation feature COMP OUT
            PB0 Select IO output
            PB1 select IO output
            PB3 is selected as TIM1 CH1 output
            PB4 is selected as TIM1 CH1N output
            
    Instructions:
        1. After compiling, open the debugging mode, connect PA0 to PB0 and PA1 to PB1, and observe the output waveform of PA6 and TIM1 using oscilloscope or logic analyzer.
        2. When the software output level of PA1 is higher than that of PA0, the TIM1 waveform disappears, and at this time, PA6 outputs a high level; 
           conversely, the waveform outputs normally, PA6 outputs low level. 
    
4. Attention
    No