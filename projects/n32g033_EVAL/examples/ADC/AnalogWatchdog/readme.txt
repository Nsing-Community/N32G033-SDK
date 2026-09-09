1、功能说明

    1、ADC采样转换PA3引脚的模拟电压，如果超过模拟看门狗定义的阈值范围，则跳入中断程序


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
            PA3选择为模拟功能
          3、ADC：
            ADC单段模式、单通道采样,连续模式，软件触发转换、12位数据右对齐，转换PA3的模拟电压数据

    /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，将变量gCntAwdg添加到watch窗口观察
        2、改变PA3引脚电压值，当电压值超出模拟看门狗定义的阈值范围外，则进入一次中断，变量做累加操作

4、注意事项
    无
    
    


1. Function description

    1. The ADC samples and converts the analog voltage of the PA3 pin. 
       If it exceeds the threshold range defined by the analog watchdog, it will jump into the interrupt program.
    
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
            PA3 is selected as the analog function
        3.ADC
            ADC single-segment mode, single-channel sampling, continuous mode,  software-triggered conversion, 
            12-bit data right-aligned, converting analog voltage data of PA3.
            
    Instructions:
        1. After compilation, open the debugging mode and add the variable gCntAwdg to the watch window for observation.
        2. Change the voltage value of the PA3 pin. When the voltage value exceeds the threshold range defined by the analog watchdog, 
           an interrupt will be entered, and the variable will perform an accumulation operation.

4. Attention
    No