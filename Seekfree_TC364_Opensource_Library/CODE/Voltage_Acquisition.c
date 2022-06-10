/*
 * voltage_acquisition.c
 *
 *  Created on: 2021年4月17日
 *      Author: Javelin
 */



#include "headfile.h"//各个模块的头文件


uint16 voltage;
float voltage_proportion;
float sum = 0;
float voltage_V = 0;
uint8 voltage_count = 0;
void voltage_acquisition_Init(void)
{
    adc_init(ADC_0, ADC0_CH2_A2);
}

//uint8 restart_sign = 0;
uint8 carstart = 0;
//uint8 restart_flag = 0;
uint8 car_state = 0;
uint8 car_mode = 0;
uint8 stop_sign = 0;
void voltage_acquisition(void)
{

    voltage = adc_convert(ADC_0, ADC0_CH2_A2, ADC_12BIT);//采集5次 然后返回平均值
//    voltage_proportion = 2400.0/voltage;
    voltage_count++;
   if(voltage_count<voltage_filter)
        sum += (float)voltage/310.3;
   else
   {
       voltage_V = sum/voltage_filter;
       voltage_proportion = 8.0/voltage_V;
       voltage_count = 0;
       sum = 0;
   }
   if (voltage <= 4 && stop_sign == 0) car_mode = 1;
   else car_mode = 0;

   if (voltage > 11 && stop_sign == 1) stop_sign = 0;
}



void oled_show_voltage(void)
{

    oled_printf_float(50, 1,voltage_V,2,2);
//    oled_printf_int32(75,0,voltage,4);
    oled_p6x8str(90,1,"V");
    oled_p6x8str(0,1,"voltage");

}
