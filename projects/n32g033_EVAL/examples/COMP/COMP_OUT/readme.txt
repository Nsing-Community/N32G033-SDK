1、功能说明

    1、COMP的输出PA6受输入INP PA1和INM PA0的影响


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


    /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，将PA0连接到PB0，PA1连接到PB1，利用示波器或者逻辑分析仪观察PA6输出波形
        2、当软件输出PA1电平大于PA0时，PA6输出高电平，相反时，输出低电平

4、注意事项
    无


1. Function description

    1. COMP output PA6 is affected by INP PA1 and INM PA0
    
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

            
    Instructions:
        1. After compiling, open the debugging mode, connect PA0 to PB0 and PA1 to PB1, and observe the output waveform of PA6 using oscilloscope or logic analyzer.
        2. When the software outputs PA1 level greater than PA0, PA6 outputs high level; otherwise, PA6 outputs low level 
    
4. Attention
    No