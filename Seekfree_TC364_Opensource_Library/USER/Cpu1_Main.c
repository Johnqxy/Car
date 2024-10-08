/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC364DP
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-11-23
 ********************************************************************************************************************/

#include "headfile.h"
#pragma section all "cpu1_dsram"
//将本语句与#pragma section all restore语句之间的全局变量都放在CPU1的RAM中

void core1_main(void)
{
	disableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    //用户在此处调用各种初始化函数等
    /***********************************************************************陀螺仪初始化*/
    simiic_init();
    uint8 ErrLoop = 0;
    while (BMX055_init() == false)//陀螺仪初始化
    {
    ErrLoop++;
    if (ErrLoop == 5)break;
    }
    pit_init(CCU6_0, PIT_CH0, 4000);    //设置周期中断5000us
    systick_delay(STM0,1000);
    DialInit();//拨码
    ips114_init();




	//等待所有核心初始化完毕
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();
    while (TRUE)
    {
        dial_scan();
		//用户在此处编写任务代码
//        ips114_displayimage7725(ov7725_uart_image_bin[0],OV7725_UART_W,OV7725_UART_H);
    }
}



#pragma section all restore
