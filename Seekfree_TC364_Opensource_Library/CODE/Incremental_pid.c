/*
 * pid1.c
 *
 *  Created on: 2020年8月19日
 *      Author: Javelin
 */

		/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差
e(k-1)代表上一次的偏差  以此类推
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
#include "headfile.h"

sint16 encValue_1;
sint16 encValue_2;
//sint16 encValue_3;
//sint16 encValue_4;


sint16 Average_encValue;

sint16 duty1;
sint16 duty2;
//sint16 duty3;
//sint16 duty4;





void encoder_init(void)
{
    gpt12_init(GPT12_T6, GPT12_T6INA_P20_3, GPT12_T6EUDA_P20_0);  //ENcoder1
//    gpt12_init(GPT12_T4, GPT12_T4INA_P02_8, GPT12_T4EUDA_P00_9);
    gpt12_init(GPT12_T4, GPT12_T4INA_P02_8, GPT12_T4EUDA_P00_9);  //ENcoder3
//    gpt12_init(GPT12_T6, GPT12_T6INA_P20_3, GPT12_T6EUDA_P20_0);  //ENcoder4

}

sint16 sint16data_filter(sint16 a,sint16 b,sint16 c)
{
    if(MAX(a,b) < c)        return MAX(a,b);
    else if( c < MIN(a,b) ) return MIN(a,b);
    else                    return c;
}

void oled_show_pwm(void)
{
    ips114_showint32(80,2,duty2,5);


}


sint16 base_speed = 0;

void base_speed_ctrl(void)
{
    if(g_u8Top<24)
        base_speed = myCar.base_speed1;
    else
        base_speed = myCar.base_speed2;
}

sint16 left_target_speed=0;
sint16 right_target_speed=0;

void oled_show_base_speed(void)
{
    ips114_showstr(0,4,"base_speed");
    ips114_showint32(90,4,base_speed,3);
}

sint16 encValue_1_last = 0;
sint16 encValue_2_last = 0;
void get_encoder(void)
{

    encValue_1 = -gpt12_get(GPT12_T4);
    gpt12_clear(GPT12_T4);
    if(encValue_1 - encValue_1_last>40)
        encValue_1 = encValue_1_last+40;
    if(encValue_1 - encValue_1_last<-40)
        encValue_1 = encValue_1_last-40;

    //encValue_2 = gpt12_get(GPT12_T4);
    encValue_2 = gpt12_get(GPT12_T6);
    gpt12_clear(GPT12_T6);
    if(encValue_2 - encValue_2_last>40)
        encValue_2 = encValue_2_last+40;
    if(encValue_2 - encValue_2_last<-40)
        encValue_2 = encValue_2_last-40;

    Average_encValue =(encValue_1 + encValue_2)/2;
    //encValue_2 = gpt12_get(GPT12_T6);
    //gpt12_clear(GPT12_T2);
    //gpt12_clear(GPT12_T4);


    encValue_1_last = encValue_1;
    encValue_2_last = encValue_2;


}

void oled_show_Enclder(void)
{

    ips114_showint32(0,0,encValue_1,3);
    ips114_showint32(95,0,Average_encValue,3);

//    ips114_showint32(50,0,encValue_1,3);
    ips114_showint32(190,0,encValue_2,3);
    ips114_showint32(0,1,left_target_speed,3);
    ips114_showint32(190,1,right_target_speed,3);
}



void MotorAPID (int speedA)  //10
{
    static sint16 incA = 0 ;
    static sint16 lasterrorA = 0,doublelasterrorA = 0;
    sint16 errorA = 0,doubleerrorA = 0;


    errorA = speedA - Average_encValue;
    doubleerrorA = errorA - lasterrorA;

    incA = (sint16)((5 * doubleerrorA + 2.2 * errorA + myCar.SpeedDA * (errorA - 2 * lasterrorA + doublelasterrorA))); //10*100

//    uint32 temp=voltageA*100;
    duty1 = incA + duty1;//*temp/100);//*voltageA);//*2400/voltage); //1000
    if(duty1 > 4000)
        duty1 = 4000;
    else if(duty1 < -4000)
        duty1 = -4000;
    doublelasterrorA = lasterrorA;
    lasterrorA = errorA;

}



//
void MotorBPID (sint16 speedB)
{
    sint16 incB = 0 ;

    static sint16 lasterrorB = 0,doublelasterrorB = 0;
    sint16 errorB = 0,doubleerrorB = 0;

    errorB = speedB - encValue_2;
    doubleerrorB = errorB - lasterrorB;

    incB = (sint16)(4.25 * doubleerrorB + 2.0 * errorB + myCar.SpeedDB * (errorB - 2 * lasterrorB + doublelasterrorB));
    duty2 = incB + duty2;
    if(duty2 > 4000)
        duty2 = 4000;
    else if(duty2 < -4000)
        duty2 = -4000;
    doublelasterrorB = lasterrorB;
    lasterrorB = errorB;



}

float speed_ki = 0;
float speed_kp = 0;
int error_speed=0,last_error_speed=0;
int speed_old=0;
int speed_new=0;
int basic_speed=0;//速度占空比输出
void speed_control(void)
{
//    error_speed=((sint16)myCar.base_speed-Average_encValue);
////  int speed_s = 0;
//    if(error_speed>myCar.base_speed-5)//真实速度远小于设定速度
//    {
////      //变速积分
//////        speed_ki= myCar.ki_SPE[0]*0.9*(((realset_speed-150)/realset_speed)-(error_speed)/(realset_speed));
//////        speed_kp = myCar.kp_SPE[0]*0.7;
//////        basic_speed+=(int)(speed_kp*(error_speed-last_error_speed)+speed_ki*error_speed);
//////        basic_speed = (basic_speed<realset_speed)?(realset_speed):(basic_speed);
////
////      //开环控制
////      basic_speed = realset_speed;
//        speed_ki = 0;
//        speed_kp = myCar.SpeedPA;
//    }
//    else
//    {
//    speed_ki = myCar.SpeedIA;
//    speed_kp = myCar.SpeedPA;
//    }

    basic_speed+=(int)(speed_kp*(error_speed-last_error_speed)+speed_ki*error_speed);

    //speed_old=speed_new;
//  speed_s = (int)(speed_kp*(error_speed-last_error_speed)+speed_ki*error_speed);
//  speed_s = (speed_s>4500)?4500:speed_s;
//  basic_speed+=speed_s;
    last_error_speed=error_speed;
//  basic_speed=(basic_speed>450)?450:basic_speed;
}

//pid调节驱动
void pid_adjust_motor(sint16 pid1,sint16 pid2)
{
	MotorAPID(pid1);   //左
	MotorBPID(pid2);   //右

}
