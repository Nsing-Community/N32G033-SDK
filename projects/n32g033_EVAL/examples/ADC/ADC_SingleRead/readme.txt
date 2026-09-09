1、功能说明

    1、ADC采样转换PA0 PA1引脚的模拟电压
    2、采用软件触发一次，采集一次的方式


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
          3、ADC：
            ADC单段模式、单通道采样，软件触发转换、12位数据右对齐，转换PA0 PA1的模拟电压数据

    /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，将变量ADCConvertedValue添加到watch窗口观察
        2、通过改变PA0,PA1引脚的电压，可以看到转换结果变量同步改变

4、注意事项
    无


1. Function description

    1. ADC samples and converts the analog voltage of PA0 and PA1 pins
    2. Adopt the method of software triggering once and collecting once
    
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
        3.ADC
            ADC single-segment mode, single-channel sampling, software-triggered conversion, 
            12-bit data right-aligned, converting analog voltage data of PA0 and PA1.
            
    Instructions:
        1. Open the debug mode after compiling, add the variables ADCConvertedValue to the watch window for observation
        2. By changing the voltage of PA0, PA1 pins, you can see that the conversion result variable changes synchronously
    
4. Attention
    No