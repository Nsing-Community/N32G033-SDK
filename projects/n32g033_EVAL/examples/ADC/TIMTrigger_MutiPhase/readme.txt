1、功能说明

    1、TIM1触发ADC采样转换PA1 PA4 PA0 PB0 PB1引脚的模拟电压


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
            PA4选择为模拟功能
            PB1选择为模拟功能
            PB0选择为模拟功能
            PB3选择为TIM1 CH1 PWM输出
            PB4选择为TIM1 CH2 PWM输出
            PB5选择为TIM1 CH3 PWM输出
            PB6选择为TIM1 CH4 PWM输出
            
            PB7选择为普通GPIO输出
          3、ADC：
            ADC 4段模式、多通道采样、12位数据右对齐
            PHS1   TIM1_CC1触发ADC 转换PA1 PA4的模拟电压数据
            PHS2   TIM1_CC2触发ADC 转换PA0的模拟电压数据
            PHS3   TIM1_CC3触发ADC 转换PB0的模拟电压数据
            PHS4   TIM1_CC4触发ADC 转换PB1的模拟电压数据

    /* 描述Demo的测试步骤和现象 */
        1、编译后打开调试模式，将变量ADCConvertedValue添加到watch窗口观察
        2、通过改变PA1 PA4 PA0 PB0 PB1引脚的电压，可以看到转换结果变量同步改变

4、注意事项
    无


1. Function description

    1. TIM1 triggers ADC sampling to convert the analog voltages of the PA1, PA4, PA0, PB0, and PB1 pins.
    
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
            PA0 is selected as  analog function
            PA1 is selected as  analog function
            PA4 is selected as  analog function
            PB1 is selected as  analog function
            PB0 is selected as  analog function
            PB3 is selected as TIM1 CH1 PWM output
            PB4 is selected as TIM1 CH2 PWM output
            PB5 is selected as TIM1 CH3 PWM output
            PB6 is selected as TIM1 CH4 PWM output
            PB7 is selected as a general-purpose GPIO output.
        3.ADC
            ADC 4-segment mode, multi-channel sampling, 12-bit data right-aligned
            PHS1: TIM1_CC1 triggers ADC to convert analog voltage data of PA1 and PA4
            PHS2: TIM1_CC2 triggers ADC to convert analog voltage data of PA0
            PHS3: TIM1_CC3 triggers ADC to convert analog voltage data of PB0
            PHS4: TIM1_CC4 triggers ADC to convert analog voltage data of PB1
            
    Instructions:
        1. Open the debug mode after compiling, add the variables ADC1ConvertedValue to the watch window for observation
        2. By changing the voltage of PA1 PA4 PA0 PB0 PB1 pins, you can see that the conversion result variable changes synchronously
    
4. Attention
    No