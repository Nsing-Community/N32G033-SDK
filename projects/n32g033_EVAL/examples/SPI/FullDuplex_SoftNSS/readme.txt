1、功能说明

    1、SPI 全双工软件 NSS 模式发送接收数据


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

    4、SPI2 配置：
        SCK  -->  PB0
        MISO  -->  PA12
        MOSI  -->  PB1
        全双工
        从模式

    5、USART1配置：
        TX  -->  PA9
        RX  -->  PA10
        波特率：115200
        数据位：8bit
        停止位：1bit
        无校验

    6、使用方法：
        1.PB3连接PB0，PB4连接PA12，PB5连接PB1；
        2.通过J22连接串口；
        3.编译后下载程序复位运行；
        4.SPI1 初始化为主机，发送数据，SPI2 初始化为丛机，接收数据 ，传输完成后，检查数据，查看 TransferStatus1 和 TransferStatus2 状态为 PASSED；
          SPI2 初始化为主机，发送数据，SPI1 初始化为丛机，接收数据 ，传输完成后，检查数据，查看 TransferStatus3 和 TransferStatus4 状态为 PASSED；
        5.从串口看打印信息，验证结果。

4、注意事项

    1. 需根据主机时钟空闲电平来配置主机CLK引脚的上/下拉，CLKPOL为1配置为上拉，CLKPOL为0配置为下拉.


1. Function description

    1. SPI full-duplex software NSS mode to send and receive data

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

    4. SPI2 Configuration:
        SCK   -->  PB0 
        MISO  -->  PA12
        MOSI  -->  PB1
        Full duplex
        Slave mode

    5. USART1 configuration:
        TX  -->  PA9
        RX  -->  PA10
        Baud rate: 115200
        Data bit: 8 bits
        Stop bit: 1bit
        No verification

    6. Instructions
        1. PB3 connects to PB0, PB4 connects to PA12, PB5 connects to PB1;
        2. Using J22 to connect to the USART；
        3. After compiling, download the program to reset and run;
        4. SPI1 initializes the bit host, sends data, SPI2 initializes the bit cluster machine, receives data, after the transmission is completed, 
           check the data, check that the status of TransferStatus1 and TransferStatus2 is PASSED,
           SPI2 initializes the bit host, sends data, SPI1 initializes the bit cluster machine, receives data, and after the transmission is completed,
           check the data, and check that the status of TransferStatus3 and TransferStatus4 is PASSED;
        5. View the printed information from the serial port and verify the result.

4. Attention

    1. The pull-up/down of the host CLK pin should be configured according to the idle level of the host clock，
        when CLKPOL is set to 1, it is configured as pull-up; when CLKPOL is set to 0, it is configured as pull-down.