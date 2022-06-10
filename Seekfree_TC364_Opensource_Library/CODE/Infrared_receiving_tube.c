/*
 * Infrared_receiving_tube.c
 *
 *  Created on: 2021年1月20日
 *      Author: Javelin
 */

#include "headfile.h"

void Infrared_init(void)
{
    gpio_init(P23_1, GPI, 1, PULLDOWN);//P00_0初始化为GPIO功能、输出模式、输出高电平、推挽输出
    gpio_init(P22_0, GPI, 1, PULLDOWN);//P00_0初始化为GPIO功能、输出模式、输出高电平、推挽输出
    gpio_init(P22_1, GPI, 1, PULLDOWN);//P00_0初始化为GPIO功能、输出模式、输出高电平、推挽输出
    gpio_init(P22_2, GPI, 1, PULLDOWN);//P00_0初始化为GPIO功能、输出模式、输出高电平、推挽输出
    gpio_init(P22_3, GPI, 1, PULLDOWN);//P00_0初始化为GPIO功能、输出模式、输出高电平、推挽输出
    gpio_init(P21_2, GPI, 1, PULLDOWN);//P00_0初始化为GPIO功能、输出模式、输出高电平、推挽输出
    gpio_init(P21_3, GPI, 1, PULLDOWN);//P00_0初始化为GPIO功能、输出模式、输出高电平、推挽输出
    gpio_init(P21_4, GPI, 1, PULLDOWN);//P00_0初始化为GPIO功能、输出模式、输出高电平、推挽输出
//    pit_init(CCU6_1, PIT_CH1, 5000); //设置周期中断5000us

}

uint8 Infrared_fiter0(uint8 *Infrared_data)
{
   static uint8 i=0;
   if (*Infrared_data >=1)
       i++;
   else i=0;
   if(i>50) i=50;
   if(i<=10)
   {
       return 1;
   }
   else
   {
       return 0;
   }
}

uint8 Infrared_fiter1(uint8 *Infrared_data)
{
   static uint8 i=0;
   if (*Infrared_data >=1)
       i++;
   else i=0;
   if(i>50) i=50;
   if(i<=10)
   {
       return 1;
   }
   else
   {
       return 0;
   }
}

uint8 Infrared_fiter2(uint8 *Infrared_data)
{
   static uint8 i=0;
   if (*Infrared_data >=1)
       i++;
   else i=0;
   if(i>50) i=50;
   if(i<=10)
   {
       return 1;
   }
   else
   {
       return 0;
   }
}

uint8 Infrared_fiter3(uint8 *Infrared_data)
{
   static uint8 i=0;
   if (*Infrared_data >=1)
       i++;
   else i=0;
   if(i>50) i=50;
   if(i<=10)
   {
       return 1;
   }
   else
   {
       return 0;
   }
}

uint8 Infrared_fiter4(uint8 *Infrared_data)
{
   static uint8 i=0;
   if (*Infrared_data >=1)
       i++;
   else i=0;
   if(i>50) i=50;
   if(i<=10)
   {
       return 1;
   }
   else
   {
       return 0;
   }
}

uint8 Infrared_fiter5(uint8 *Infrared_data)
{
   static uint8 i=0;
   if (*Infrared_data >=1)
       i++;
   else i=0;
   if(i>50) i=50;
   if(i<=10)
   {
       return 1;
   }
   else
   {
       return 0;
   }
}

uint8 Infrared_fiter6(uint8 *Infrared_data)
{
   static uint8 i=0;
   if (*Infrared_data >=1)
       i++;
   else i=0;
   if(i>50) i=50;
   if(i<=10)
   {
       return 1;
   }
   else
   {
       return 0;
   }
}

uint8 Infrared_fiter7(uint8 *Infrared_data)
{
   static uint8 i=0;
   if (*Infrared_data >=1)
       i++;
   else i=0;
   if(i>50) i=50;
   if(i<=10)
   {
       return 1;
   }
   else
   {
       return 0;
   }
}

uint8 Infrared[8];
uint8 Infrared_fitered[8];
sint8 Infrared_error = 0;
sint8 Infrared_error_last = 0;
void Infrared_receiving_tube(void)
{
    *Infrared     = gpio_get(P23_1);//获取P00_0引脚电平;
    *(Infrared+1) = gpio_get(P22_0);//获取P00_0引脚电平;
    *(Infrared+2) = gpio_get(P22_1);//获取P00_0引脚电平;
    *(Infrared+3) = gpio_get(P22_2);//获取P00_0引脚电平;
    *(Infrared+4) = gpio_get(P22_3);//获取P00_0引脚电平;
    *(Infrared+5) = gpio_get(P21_2);//获取P00_0引脚电平;
    *(Infrared+6) = gpio_get(P21_3);//获取P00_0引脚电平;
    *(Infrared+7) = gpio_get(P21_4);//获取P00_0引脚电平;

//    *Infrared_fitered=Infrared_fiter0(Infrared);
//    Infrared_fitered[1]=Infrared_fiter1((Infrared+1));
//    Infrared_fitered[2]=Infrared_fiter2((Infrared+2));
//    Infrared_fitered[3]=Infrared_fiter3((Infrared+3));
//    Infrared_fitered[4]=Infrared_fiter4((Infrared+4));
//    Infrared_fitered[5]=Infrared_fiter5((Infrared+5));
//    Infrared_fitered[6]=Infrared_fiter6((Infrared+6));
//    Infrared_fitered[7]=Infrared_fiter7((Infrared+7));
//大于0  灯右
        Infrared_error =Infrared[0]+Infrared[2]+Infrared[4]+Infrared[6]
                          -(Infrared[1]+Infrared[3]+Infrared[5]+Infrared[7]);
        if(Infrared_error>-2&&Infrared_error<=2) Infrared_error = Infrared_error_last;
        Infrared_error_last = Infrared_error;

}





void oled_show_Infrared(void)
{

    oled_printf_int32(104, 2, *Infrared_fitered,1);
    oled_printf_int32(104 , 3, *(Infrared_fitered+2),1);
    oled_printf_int32(104, 4, *(Infrared_fitered+4),1);
    oled_printf_int32(104, 5, *(Infrared_fitered+6),1);
    oled_printf_int32(0, 2, *(Infrared_fitered+1),1);
    oled_printf_int32(0, 3, *(Infrared_fitered+3),1);
    oled_printf_int32(0, 4, *(Infrared_fitered+5),1);
    oled_printf_int32(0, 5, *(Infrared_fitered+7),1);
    oled_p6x8str(0,6,"Infrared_error");
    oled_printf_int32(90,6,Infrared_error,1);

}

