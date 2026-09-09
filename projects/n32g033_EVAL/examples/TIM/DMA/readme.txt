1、功能说明
    1、TIM1 CH3 CH3N互补信号每6个周期改变一次占空比
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
            PA5选择为TIM1 CH3输出
            PB3选择为TIM1 CH3N输出
        4、TIM：
            TIM1 CH3 CH3N互补输出，每6个周期触发一次DMA传输
        5、DMA：
            DMA_CH1通道循环环模式搬运3个字SRC_Buffer[3]变量到TIM1 CCDAT3寄存器
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1 CH3 CH3N的波形
        2、TIM1的6个周期改变一次CH3 CH3N的占空比，循环改变


1. Function description

    1. TIM1 CH3 CH3N complementary signal changes duty cycle every 6 cycles
    
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
            PA5 selected as TIM1 CH3 Output
            PB3 selected as TIM1 CH3N Output
        4. TIM:
            TIM1 CH3 CH3N complementary output triggers DMA transmission every 6 cycles
        5. DMA:
            DMA1_ CH5 Channel circular mode handling 3 word SRC_ Buffer[3] variable to TIM1 CCDAT3 register        
    Instructions:
        1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveform of TIM1 CH3 CH3N
        2. Change the duty cycle of CH3 and CH3N once in 6 cycles of TIM1, and change cyclically
4. Attention
    No