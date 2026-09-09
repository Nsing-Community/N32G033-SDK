1、功能说明

    1、SPI 单线中断发送和接收数据

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
    硬件开发环境： 
    N32G033系列：
    基于评估板N32G033K8Q7-1_STB V1.0开发
    N32G033系列：
    基于评估板N32G033K8Q7-1_STB V1.0开发


3、使用说明

    1、时钟源：HSI

    2、系统时钟：64MHz

    3、SPI1 配置：
        SCK   -->  PB3
        MOSI  -->  PB5
        单线模式
        主模式

    4、SPI2 配置：
        SCK   -->  PB0
        MISO  -->  PA12
        单线模式
        从模式

    5、USART1配置：
        TX  -->  PA9
        RX  -->  PA10
        波特率：115200
        数据位：8bit
        停止位：1bit
        无校验

    6、中断：SPI1 中断入口函数 SPI1_IRQHandler，SPI2 中断入口函数 SPI2_IRQHandler

    7、使用方法：
        1.PB3连接PB0，PB5连接PA12；
        2.通过J22连接串口；
        3.编译后下载程序复位运行；
        4.SPI1 有数据需要发送时进入 SPI1_IRQHandler 中断函数发送，SPI2 有数据需要接收时进入 SPI2_IRQHandler中断函数接收，数据传输完成后，查看 TransferStatus 状态为 PASSED；
        5.从串口看打印信息，验证结果。

4、注意事项

    1. “单线”数据线在主设备端为MOSI引脚，在从设备端为MISO引脚
    2. 需根据主机时钟空闲电平来配置主机CLK引脚的上/下拉，CLKPOL为1配置为上拉，CLKPOL为0配置为下拉.



1. Function description

    1. SPI single-wire interrupt sending and receiving data

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
    Hardware development environment:
    N32G033 series:
    Developed based on the evaluation board N32G033K8Q7-1_STB V1.0
    N32G033 series:
    Developed based on the evaluation board N32G033K8Q7-1_STB V1.0

3. How to use

    1. SystemClock: 64MHz

    2. clock source:HSE

    3. SPI1 configuration:
        SCK   -->  PB3
        MOSI  -->  PB5
        single-line
        Master mode

    4. SPI2 Configuration:
        SCK   -->  PB0
        MISO  -->  PA12
        single-line
        Slave mode

    5. USART1 configuration:
        TX  -->  PA9
        Baud rate: 115200
        Data bit: 8 bits
        Stop bit: 1bit
        No verification

    6. Interrupt: SPI1 interrupt entry function SPI1_IRQHandler, SPI2 interrupt entry function SPI2_IRQHandler

    7. Instructions
        1. PB3 connects to PB0, PB5 connects to PA12;
        2. Using J22 to connect to the USART；
        3. After compiling, download the program to reset and run;
        4. Enter the SPI1_IRQHandler interrupt function to send when SPI1 has data to send, 
           and enter the SPI2_IRQHandler interrupt function to receive when SPI2 has data to receive. 
           After the data transmission is completed, check the TransferStatus status as PASSED;
        5. View the printed information from the serial port and verify the result。

4. Attention

    1. The "single wire" data lines are MOSI pins on the master side and MISO pins on the slave side.
    2. The pull-up/down of the host CLK pin should be configured according to the idle level of the host clock，
        when CLKPOL is set to 1, it is configured as pull-up; when CLKPOL is set to 0, it is configured as pull-down.