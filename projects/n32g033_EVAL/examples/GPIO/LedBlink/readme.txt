1、功能说明

    1、此例程展示 IO 控制 LED 闪烁


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件开发环境： 
        N32G033系列：
            基于评估板N32G033K8Q7-1_STB V1.0开发

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
          1、 SystemClock：64MHz
          2、 GPIO：PA6、A7、PB1 控制 LED(D1、D2、D3) 闪烁

    /* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2. LED(D1、D2、D3) 闪烁；

4、注意事项
    无


1. Function description

    1. This routine shows the IO control LED blinking
	
2. Development environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0
			
3. How to use

    System Configuration;
        1. SystemClock：64MHz
        2. GPIO: PA6、A7、PB1 control LED (D1, D2, D3) to blink
    Instructions:
        1. After compiling, download the program to reset and run
        2. LED (D1, D2, D3) to blinking
		
4. Attention
    No