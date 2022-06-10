/*
 * motor.c
 *
 *  Created on: 2020年8月20日
 *      Author: Javelin
 */
#include "headfile.h"//各个模块的头文件

short inc1;
short inc2;
short inc3;
short inc4;
int bench_v = 70;
int duty_left = 0;
int duty_right = 0;

void motor_init(void)
{
    gtm_pwm_init(ATOM0_CH7_P02_7 ,12500, 0);
    gtm_pwm_init(ATOM0_CH5_P02_5 ,12500, 0);
    gtm_pwm_init(ATOM0_CH6_P02_6 ,12500, 0);
    gtm_pwm_init(ATOM0_CH4_P02_4 ,12500, 0);
}


void motor_limited(sint16 duty1,sint16 duty2)
{
    static float duty_rate =0;
    duty1 = duty1*voltage_proportion;
    duty2 = duty2*voltage_proportion;
    if(duty1>duty2&&duty1>10000)
    {
        duty_rate = (float)duty1/10000;
        duty1 = duty1/duty_rate;
        duty2 = duty2/duty_rate;
    }
    else if(duty2>duty1&&duty2>10000)
    {
        duty_rate = (float)duty2/10000;
        duty1 = duty1/duty_rate;
        duty2 = duty2/duty_rate;
    }
    motor_direction_left(duty1);
    motor_direction_right(duty2);
}

void motor_direction_left(int duty1)
{
    if(duty1>4000)  duty1 = 4000;
    else if(duty1<-4000)  duty1 = -4000;

         if(duty1>0)
         {
          pwm_duty(ATOM0_CH6_P02_6, duty1 );//左上正
             pwm_duty(ATOM0_CH4_P02_4, 0 );//左上负

         }
         else
         {
             pwm_duty(ATOM0_CH6_P02_6, 0 );//左上正
             pwm_duty(ATOM0_CH4_P02_4, -duty1 );//左上负

         }
}
void motor_direction_right(int duty2)
{
    if(duty2>4000)  duty2 = 4000;
        else if(duty2<-4000)  duty2 = -4000;
        if(duty2>0)
        {
            pwm_duty(ATOM0_CH5_P02_5, duty2 );//右上负
            pwm_duty(ATOM0_CH7_P02_7, 0 );//右上正

        }
        else
        {
            pwm_duty(ATOM0_CH5_P02_5, 0 );//右上负
            pwm_duty(ATOM0_CH7_P02_7, -duty2 );//右上正

        }
}






/*!
  * @brief    限幅函数
  *
  * @param    amt   ： 参数
  * @param    low   ： 最低值
  * @param    high  ： 最高值
  *
  * @return   无
  *
  * @note     无
  *
  * @see      无
  *
  * @date     2020/6/8
  */
int constrain_int(int amt, int low, int high)
{
    return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}




