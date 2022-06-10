#include "led.h"
#include "Voltage_Acquisition.h"

// **************************** �������� ****************************
uint8 temp = 0, temp1 = 0;       //�������
uint8 num = 0;                //ˢ�¼ƴ�
//float supply_voltage=0;     //ģ���Դ��ѹ

void led_init(void) {
    //��ʼ��LED��������
    gpio_init(L1, GPO, 0, PUSHPULL);
    gpio_init(L2, GPO, 0, PUSHPULL);
    gpio_init(L3, GPO, 0, PUSHPULL);
    gpio_init(LA, GPO, 0, PUSHPULL);
    gpio_init(LB, GPO, 0, PUSHPULL);
    gpio_init(LC, GPO, 0, PUSHPULL);
    gpio_init(LD, GPO, 0, PUSHPULL);
    gpio_init(LE, GPO, 0, PUSHPULL);
}

void light_up(void) {

    temp = voltage_V;     //��ȡ��Դ��ѹ
    num++;                          //ˢ�¼ƴ�
    if (num > 14) num = 0;
    //�ر�����LED��ʾ
    gpio_set(L1, 0);
    gpio_set(L2, 0);
    gpio_set(L3, 0);
    systick_delay_us(STM0, 1);
    gpio_set(LA, 0);
    gpio_set(LB, 0);
    gpio_set(LC, 0);
    gpio_set(LD, 0);
    gpio_set(LE, 0);

    if (num < temp)                  //������Ҫ������LED��
    {
        temp1 = num / 3;
        switch (temp1) {                          //����

            case 0:
                gpio_set(LA, 1);
                break;
            case 1:
                gpio_set(LB, 1);
                break;
            case 2:
                gpio_set(LC, 1);
                break;
            case 3:
                gpio_set(LD, 1);
                break;
            case 4:
                gpio_set(LE, 1);
                break;
            default:
                break;
        }
    }

    //systick_delay_ms(STM0, 1);                  //��ʱ1ms  Ҳ���԰���������Ž�1ms�������ж���
    //supply_voltage+=0.1;                      //ģ����
    //if(supply_voltage>15) supply_voltage=1;
}

