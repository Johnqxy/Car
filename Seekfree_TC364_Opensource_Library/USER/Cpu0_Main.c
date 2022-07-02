/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file            main
 * @company         成都逐飞科技有限公司
 * @author          逐飞科技(QQ3184284598)
 * @version         查看doc内version文件 版本说明
 * @Software        ADS v1.2.2
 * @Target core     TC364DP
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-11-23
 ********************************************************************************************************************/

#include "Cpu0_Main.h"
#include "headfile.h"
#include "stdlib.h"
#pragma section all "cpu0_dsram"
//将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中


//工程导入到软件之后，应该选中工程然后点击refresh刷新一下之后再编译

//工程默认设置为关闭优化，可以自己右击工程选择properties->C/C++ Build->Setting
//然后在右侧的窗口中找到C/C++ Compiler->Optimization->Optimization level处设置优化等级
//一般默认新建立的工程都会默认开2级优化，因此大家也可以设置为2级优化

//对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用enableInterrupts();来开启中断嵌套
//简单点说实际上进入中断后TC系列的硬件自动调用了disableInterrupts();来拒绝响应任何的中断，因为需要我们自己手动调用enableInterrupts();来开启中断的响应。

//旧
int core0_main(void)
{
    get_clk();//获取时钟频率  务必保留
    //用户在此处调用各种初始化函数等
//    uart_init(UART_0,115200,UART0_TX_P14_0,UART0_RX_P14_1);       // 初始化串口0 波特率115200 发送引脚使用P14_0 接收引脚使用P14_1
    uart_init(UART_2,115200,UART2_TX_P33_9,UART2_RX_P33_8);       // 初始化串口0 波特率115200 发送引脚使用P14_0 接收引脚使用P14_1
    oled_init();  //oled初始化
    led_init();
    voltage_acquisition_Init();
    simiic_init();
//    BMX055_init();
    seekfree_wireless_init();
    Inductive_Acquisition_init();
    motor_init();   //驱动pwm通道初始化
    encoder_init();//编码器初始化
    pit_init(CCU6_0, PIT_CH1, 4000);    //设置周期中断5000us

    car_information_init(3);
    mt9v03x_init();
//    ov7725_uart_init();
//    Infrared_init();
    MyKeyInit();//按键
    systick_start(STM0);


//    gpio_init(P02_1, GPO, 1, PUSHPULL);
    //等待所有核心初始化完毕
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();
    while (TRUE)
    {
        //seekfree_sendimg_03x(UART_0,mt9v03x_image[0],MT9V03X_W,MT9V03X_H);
       // seekfree_sendimg_03x(UART_2,mt9v03x_image[0],MT9V03X_W,MT9V03X_H);

        //DebugUI();
        ANO_DT_Send_Senser((int16)(bench_v), (int16)(encValue_1),0,0,0,0,0,0,0,0);
        OLED_UI();

//        oled_show_voltage();
//        if(exposure_time_last!=myCar.exposure_time)
//            exposure_time_last = set_exposure_time(MT9V03X_COF_UART,myCar.exposure_time);
    }
}

#pragma section all restore
