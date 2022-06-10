#include "led.h"
#include "Voltage_Acquisition.h"

// **************************** 变量定义 ****************************
uint8 temp = 0, temp1 = 0;       //计算变量
uint8 num = 0;                //刷新计次
//float supply_voltage=0;     //模拟电源电压

void led_init(void) {
    //初始化LED控制引脚
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

    temp = voltage_V;     //获取电源电压
    num++;                          //刷新计次
    if (num > 14) num = 0;
    //关闭所有LED显示
    gpio_set(L1, 0);
    gpio_set(L2, 0);
    gpio_set(L3, 0);
    systick_delay_us(STM0, 1);
    gpio_set(LA, 0);
    gpio_set(LB, 0);
    gpio_set(LC, 0);
    gpio_set(LD, 0);
    gpio_set(LE, 0);

    if (num < temp)                  //点亮需要点亮的LED灯
    {
        temp1 = num / 3;
        switch (temp1) {                          //打开列

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

    //systick_delay_ms(STM0, 1);                  //延时1ms  也可以把上面的语句放进1ms的周期中断中
    //supply_voltage+=0.1;                      //模拟充电
    //if(supply_voltage>15) supply_voltage=1;
}

