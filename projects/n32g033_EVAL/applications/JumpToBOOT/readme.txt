1、功能说明

    1、用于演示如何从用户程序（FLASH）跳转到SYSTEM BOOT。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件开发环境： 
        N32G033系列：
            基于评估板N32G033K8Q7-1_STB V1.0开发

3、使用说明

    系统配置：
        1.按钮：S--PA4
        2.调试：TX--PA9、RX--PA10
                
    说明：
        1.打开PC端的下载工具（Nsing MCU下载工具）
        2.在KEIL下编译后，将其刻录到开发板上，通过USB电缆连接PC，然后打开电源
        3.此时，开发板工作正常。您可以通过调试串口看到提示信息。无法通过下载工具连接开发板。
        4.按下按钮KEY2(PA4)，系统跳转到system BOOT，此时您可以通过下载工具连接开发板并刻录程序

4、注意事项
    无


1. Function description

    1. Used to demonstrate how to jump to SYSTEM BOOT from the user program (FLASH).
	
2. Development environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0
			
3. How to use

    System Configuration:
         1. Button: S--PA4
         2. Debug serial products: TX--PA9, RX--PA10
        
     Instructions:
         1. Open the download tool (Nsing MCU Download Tool) on the PC side
         2. After compiling under KEIL, burn it to the development board, connect the PC through the USB cable, and turn on the power
         3. At this time, the development board is working in a normal state. You can see the prompt information through the debugging serial port. The development board cannot be connected through the download tool.
         4. Press the button KEY2(PA4), the system jumps to SYSTEM BOOT, at this time you can connect the development board through the download tool and burn the program
		
4. Attention
    No