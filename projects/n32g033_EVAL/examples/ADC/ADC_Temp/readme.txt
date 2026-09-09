1、功能说明

    1、ADC采样内部温度传感器的模拟电压，并转换为温度值 

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
	              IAR EWARM 8.50.1
    硬件开发环境： 
        N32G033系列：
            基于评估板N32G033K8Q7-1_STB V1.0开发

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
          1、HSI=8M，ADC CLK=64/4=16M，,ADC 1M CLK=HSI/8
          2、ADC：
             ADC连续转换、软件触发、12位数据右对齐，转换通道16即内部温度传感器的模拟电压数据
          3、端口配置
             PA9选择为USART1的TX引脚
             PA10选择为USART1的RX引脚
          4、USART：
              USART1 115200波特率、8位数据位、1位停止位、无奇偶校验位、无硬件流控、发送和接收使能
           5、功能函数：
               TempValue = TempCal(ADCConvertedValue)函数将温度ADC原始格式数据转为度的单位的格式
    /* 描述Demo的测试步骤和现象 */
         1、编译后打开调试模式，将变量ADCConvertedValue,TempValue添加到watch窗口观察
        2、将串口工具连接到PA9引脚，并打开串口接收工具
        3、全速运行，可以看到温度变量的数值在常温下接近25度左右，同时串口工具显示实时芯片内的温度值

4、注意事项
    内置传感器在环境温度为30℃下校准


1. Function description
    1. ADC samples and converts the analog voltage of the internal temperature sensor and converts it to a temperature value

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
  	                                                 IAR EWARM 8.50.1
    Hardware development environment:
         N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0
        
3. How to use

    System Configuration;
        1.HSI=8M，ADC CLK=64/4=16M，,ADC 1M CLK=HSI/8
        2.ADC
            ADC configuration: continuous conversion, software trigger, 12-bit data right-aligned, conversion channel 16 is the analog voltage data of the internal temperature sensor
        3. Port configuration:
             PA9 is selected as the TX pin of USART1
             PA10 is selected as the RX pin of USART1
         4.USART
             115200 baud rate, 8 data bits, 1 stop bit, no parity bit, no hardware flow control, transmit and receive enabled
         5.Function
              The function TempValue = TempCal(ADCConvertedValue) converts the raw ADC temperature data into a format with the unit of degrees.

    Instructions:
        1. Open the debug mode after compiling, add the variables ADCConvertedValue, TempValue to the watch window for observation
        2. Connect the serial port tool to the PA9 pin and open the serial port receiving tool
        3. Running at full speed, you can see that the value of the temperature variable is close to about 25 degrees at room temperature, and the serial port tool displays the temperature value in the real-time chip

4. Attention
    The built-in sensor is calibrated at an ambient temperature of 30°C.