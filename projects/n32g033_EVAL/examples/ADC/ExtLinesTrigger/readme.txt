1、功能说明

    1、EXTI线事件触发ADC采样转换PA0 PA1引脚的模拟电压.


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
            PA0选择为模拟功能
            PA1选择为模拟功能
            PA4选择为输入上拉功能
          3、ADC：
            ADC单段模式、多通道采样，EXTI线事件触发转换、12位数据右对齐，转换PA0 PA1的模拟电压数据

    /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，将变量ADCConvertedValue添加到watch窗口观察
        2、触发PA4拉低，通过改变PA0,PA1引脚的电压，可以看到转换结果变量同步改变

4、注意事项
    无


1. Function description

    1. EXTI line events trigger ADC sampling to convert the analog voltages of the PA0 and PA1 pins.

    
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
            PA0 is selected as the analog function
            PA1 is selected as the analog function
            PA4 is selected as the input pull-up function
        3.ADC
            ADC single-segment mode, multi-channel sampling, EXTI line event triggering conversion, 
            12-bit data right-aligned, converting analog voltage data of PA0 and PA1.
            
    Instructions:
        1. Open the debug mode after compiling, add the variables ADCConvertedValue to the watch window for observation
        2. Trigger PA4 to pull low.By changing the voltage of PA0, PA1 pins, you can see that the conversion result variable changes synchronously
    
4. Attention
    No