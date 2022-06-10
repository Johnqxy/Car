/*
 * Inductive_Acquisition.c
 *
 *  Created on: 2021Äê7ÔÂ9ÈÕ
 *      Author: Javelin
 */

#include"zf_vadc.h"

uint16 Left_inductance = 0;
uint16 Right_inductance = 0;
float Inductive_error = 0;
uint16 average_inductance = 0;
void Inductive_Acquisition_init(void)
{
    adc_init(ADC_8,ADC8_CH5_A37);//right,green
    adc_init(ADC_8,ADC8_CH6_A38);//left,blue
}

void Inductive_Acquisition(void)
{
    static uint16 Left_inductance_unfilter = 0;
    static uint16 Right_inductance_unfilter = 0;
    static uint8 Inductive_count = 0;

    static uint32 Left_inductance_sum = 0;
    static uint32 Right_inductance_sum = 0;
    Left_inductance_unfilter = adc_convert(ADC_8,ADC8_CH6_A38,ADC_12BIT);
    Right_inductance_unfilter = adc_convert(ADC_8,ADC8_CH5_A37,ADC_12BIT);
    Inductive_count++;
    if(Inductive_count<20)
    {
        Left_inductance_sum += Left_inductance_unfilter;
        Right_inductance_sum += Right_inductance_unfilter;
    }
    else
    {
        Left_inductance = (uint16)(Left_inductance_sum/20);
        Right_inductance = (uint16)(Right_inductance_sum/20);
        average_inductance = Left_inductance+Right_inductance/2;
        Inductive_error = (sqrtf(Left_inductance)-sqrtf(Right_inductance))*100/(Left_inductance+Right_inductance);
        Inductive_count = 0;
        Left_inductance_sum = 0;
        Right_inductance_sum = 0;
    }
}

