/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC364DP
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-11-23
 ********************************************************************************************************************/

#include "headfile.h"
#pragma section all "cpu1_dsram"
//���������#pragma section all restore���֮���ȫ�ֱ���������CPU1��RAM��

void core1_main(void)
{
	disableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    //�û��ڴ˴����ø��ֳ�ʼ��������
    /***********************************************************************�����ǳ�ʼ��*/
    simiic_init();
    uint8 ErrLoop = 0;
    while (BMX055_init() == false)//�����ǳ�ʼ��
    {
    ErrLoop++;
    if (ErrLoop == 5)break;
    }
    pit_init(CCU6_0, PIT_CH0, 4000);    //���������ж�5000us
    systick_delay(STM0,1000);
    DialInit();//����
    ips114_init();




	//�ȴ����к��ĳ�ʼ�����
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();
    while (TRUE)
    {
        dial_scan();
		//�û��ڴ˴���д�������
//        ips114_displayimage7725(ov7725_uart_image_bin[0],OV7725_UART_W,OV7725_UART_H);
    }
}



#pragma section all restore
