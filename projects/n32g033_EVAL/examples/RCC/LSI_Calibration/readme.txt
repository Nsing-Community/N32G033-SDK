1、功能说明
    1、使用HSI计算LSI当前频率，通过Trim校准LSI时钟


2、使用环境
    软件开发环境：  KEIL MDK-ARM 5.34
            IAR EWARM 8.50.1
            
    硬件环境：      
     N32G033系列：
            基于评估板N32G033K8Q7-1_STB V1.0开发

3、使用说明
    系统配置:
        1、时钟源：
                    HSI=64MHz, LSI=32KHz
        2、端口配置：
                    PA8选择为MCO 输出
       
    使用方法：   
        1、编译后下载进芯片，通过计算LSI当前频率进行校准，使用示波器抓取PA8引脚波形，观察频率变化

4、注意事项
	无
	
	
	
1. Function description
     1. Calculate the current frequency of LSI using HSI and calibrate the LSI clock through Trim.

2. Development environment
    Software development environment: KEIL MDK-ARM 5.34
            IAR EWARM 8.50.1 
            
    Hardware environment: 
     N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0

3. How to use
    System Configuration;
        1. Clock source:
                    HSI=64MHz, LSI=32KHz
         2. Port configuration:
                   PA8 is selected as MCO output

     Instructions:
         1. After compiling and downloading into the chip, calibrate it by calculating the current frequency of the LSI. Use an oscilloscope to 
            capture the waveform of the PA8 pin and observe the frequency changes

4. Attention
     without
	