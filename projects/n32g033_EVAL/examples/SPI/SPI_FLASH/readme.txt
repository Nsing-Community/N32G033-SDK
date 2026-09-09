1、功能说明

    1、SPI 读、写、擦除 W25Q128

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
        SCK  -->  PB3
        MISO  -->  PB4
        MOSI  -->  PB5
        全双工
        主模式

    4、USART1配置：
        TX  -->  PA9
        RX  -->  PA10
        波特率：115200
        数据位：8bit
        停止位：1bit
        无校验

    5、使用方法：
        1.通过J22连接串口；
        2.编译后下载程序复位运行；
        3.从串口看打印信息，验证结果。

4、注意事项

    1. 需根据主机时钟空闲电平来配置主机CLK引脚的上/下拉，CLKPOL为1配置为上拉，CLKPOL为0配置为下拉.



1. Function description

    1. SPI Read, Write, Erase W25Q128

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
    Hardware development environment:
    N32G033 series:
    Developed based on the evaluation board N32G033K8Q7-1_STB V1.0
    N32G033 series:
    Developed based on the evaluation board N32G033K8Q7-1_STB V1.0

3. How to use

    1. SystemClock: 64MHz

    2. clock source:HSI

    3. SPI1 configuration:
        SCK   -->  PB3
        MISO  -->  PB4
        MOSI  -->  PB5
        Full duplex
        Master mode

    4. USART1 configuration:
        TX  -->  PA9
        RX  -->  PA10
        Baud rate: 115200
        Data bit: 8 bits
        Stop bit: 1bit
        No verification

    5. Instructions
        1. Using J22 to connect to the USART；
        2. After compiling, download the program to reset and run;
        3. View the printed information from the serial port and verify the result.


4. Attention

    1. The pull-up/down of the host CLK pin should be configured according to the idle level of the host clock，
        when CLKPOL is set to 1, it is configured as pull-up; when CLKPOL is set to 0, it is configured as pull-down.