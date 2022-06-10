/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            main
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ3184284598)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        ADS v1.2.2
 * @Target core     TC364DP
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-11-23
 ********************************************************************************************************************/

#include "Cpu0_Main.h"
#include "headfile.h"
#pragma section all "cpu0_dsram"
//���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��


//���̵��뵽���֮��Ӧ��ѡ�й���Ȼ����refreshˢ��һ��֮���ٱ���

//����Ĭ������Ϊ�ر��Ż��������Լ��һ�����ѡ��properties->C/C++ Build->Setting
//Ȼ�����Ҳ�Ĵ������ҵ�C/C++ Compiler->Optimization->Optimization level�������Ż��ȼ�
//һ��Ĭ���½����Ĺ��̶���Ĭ�Ͽ�2���Ż�����˴��Ҳ��������Ϊ2���Ż�

//����TCϵ��Ĭ���ǲ�֧���ж�Ƕ�׵ģ�ϣ��֧���ж�Ƕ����Ҫ���ж���ʹ��enableInterrupts();�������ж�Ƕ��
//�򵥵�˵ʵ���Ͻ����жϺ�TCϵ�е�Ӳ���Զ�������disableInterrupts();���ܾ���Ӧ�κε��жϣ���Ϊ��Ҫ�����Լ��ֶ�����enableInterrupts();�������жϵ���Ӧ��

//��
int core0_main(void)
{
    get_clk();//��ȡʱ��Ƶ��  ��ر���
    //�û��ڴ˴����ø��ֳ�ʼ��������
    uart_init(UART_0,115200,UART0_TX_P14_0,UART0_RX_P14_1);       // ��ʼ������0 ������115200 ��������ʹ��P14_0 ��������ʹ��P14_1
//    uart_init(UART_1,115200,UART1_TX_P02_2,UART1_RX_P02_3);       // ��ʼ������0 ������115200 ��������ʹ��P14_0 ��������ʹ��P14_1
    oled_init();  //oled��ʼ��
    led_init();
    voltage_acquisition_Init();
    simiic_init();
//    BMX055_init();

    Inductive_Acquisition_init();
    motor_init();   //����pwmͨ����ʼ��
    encoder_init();//��������ʼ��
    pit_init(CCU6_0, PIT_CH1, 4000);    //���������ж�5000us

    car_information_init(3);
    mt9v03x_init();
//    ov7725_uart_init();
//    Infrared_init();
    MyKeyInit();//����
    systick_start(STM0);


//    gpio_init(P02_1, GPO, 1, PUSHPULL);
    //�ȴ����к��ĳ�ʼ�����
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();
    while (TRUE)
    {
        //seekfree_sendimg_03x(UART_0,mt9v03x_image[0],MT9V03X_W,MT9V03X_H);
        //DebugUI();
        OLED_UI();

//        oled_show_voltage();
//        if(exposure_time_last!=myCar.exposure_time)
//            exposure_time_last = set_exposure_time(MT9V03X_COF_UART,myCar.exposure_time);
    }
}

#pragma section all restore
