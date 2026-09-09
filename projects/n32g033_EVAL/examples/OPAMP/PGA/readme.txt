1、功能说明

    1、OPA1 PGA模式，放大输入电压2倍


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件开发环境： 
        N32G033系列：
            基于评估板N32G033K8Q7-1_STB V1.0开发
        N32G033系列：
            基于评估板N32G033K8Q7-1_STB V1.0开发

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
          1、 SystemClock：64MHz
          2、端口配置：
            PA0选择为模拟功能OPA1 VP
            PA6选择为模拟功能OPA1 OUT
        3、OPA：
            OPA1 PGA功能，倍数2倍

    /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，用示波器观察OPA1的输入和输出
        2、OPA输出=2*OPA输入

4、注意事项
    无


1. Function description

    1. OPA1 PGA mode, amplify the input voltage by 2 times
    
2. Development environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0
         N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0
        
3. How to use

    System Configuration;
        1. SystemClock：64MHz
        2. Port configuration:
             PA0 selected as analog function, OPA1 VP
             PA6 is selected as analog function, OPA1 OUT
         3. OPA:
             OPA1 PGA function, multiple 2 times
             
     Instructions:
         1. Open the debug mode after compiling, and observe the input and output of OPA1 with an oscilloscope
         2. OPA output=2*OPA input
    
4. Attention
    No