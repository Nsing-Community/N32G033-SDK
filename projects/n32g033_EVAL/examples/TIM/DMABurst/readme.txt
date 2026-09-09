1、功能说明
    1、TIM1 一个周期后同时改变周期和占空比
2、使用环境
    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1
    硬件开发环境： 
        N32G033系列：
            基于评估板N32G033K8Q7-1_STB V1.0开发
3、使用说明
    系统配置:
        1、时钟源：HSI
        2、时钟频率：
            N32G033系列：
                SYS_CLK=64M,TIM1_CLK=64M
        3、端口配置：
             PA4选择为TIM1 CH1输出
        4、TIM：
            TIM1 CH1 输出，周期触发DMA burst传输，加载CCDAT1，CCDAT2，CCDAT3，CCDAT4，CCDAT5，CCDAT6，PSC, AR寄存器，改变占空比和周期和重复计数器
        5、DMA：
            DMA_CH1通道非循环模式搬运8个字SRC_Buffer[8]变量到TIM1寄存器
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM CH1的波形
        2、TIM的第一个周期结束后，后面的波形为DMA搬运的改变周期和占空比的波形
        3、调试状态下修改DmaAgain=1会再次搬运8个字SRC_Buffer[8]变量到TIM1 DMA寄存器


1. Function description

    1. TIM changes the period and duty cycle at the same time after one cycle
    
2. Development environment

    Software development environment:  KEIL MDK-ARM 5.34
                                       IAR EWARM 8.50.1
    Hardware development environment:
         N32G033 series:
            Developed based on the evaluation board N32G033K8Q7-1_STB V1.0
3. How to use
    System Configuration;
        1. Clock source: HSI
        2. Clock frequency: 
            N32G033 series:
                SYS_CLK=64M,TIM1_CLK=64M        
        3. Port configuration:
            PA4 selected as TIM CH1 Output
        4. TIM:
            TIM CH1 output, periodically triggered DMA burst transmission, loading CCDAT1，CCDAT2，CCDAT3，CCDAT4，CCDAT5，CCDAT6，PSC, AR registers, changing duty cycle, period and repeat counter
        5. DMA:
            DMA_CH1 channel normal mode carry 8 words SRC_Buffer[8] variable to TIM registers
        Instructions:
            1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveform of TIM1 CH1
            2. After the first cycle of TIM1 is over, the following waveforms are the waveforms of changing cycle and duty cycle of DMA transport
            3. Modifying DmaAgain=1 in the debug state will again carry the 8 word SRC_Buffer[8] variable to the TIM1 DMA register
4. Attention
    without