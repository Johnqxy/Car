/*
 * Positional_pid.c
 *
 *  Created on: 2020年11月14日
 *      Author: Javelin
 */
#include "headfile.h"

struct left_error_Information L_Error;
struct right_error_Information R_Error;
struct Car_Information myCar;


sint16 Back_up_flag = 0;
sint16 Back_up_count = 1000;
uint8  direction_control_cnt=0;//方向控制计数器
uint8 speed_control_cnt=0;//速度控制计数器

float Kp_position = 0;
float Ki_position = 0;
float Kd_position = 0;


/************************************************
函数名称 ： PID_Loc
功    能 ： PID位置(Location)计算
参    数 ： SetValue ------ 设置值(期望值)
            ActualValue --- 实际值(反馈值)
            PID ----------- PID数据结构
返 回 值 ： PIDLoc -------- PID位置
作    者 ：
*************************************************/
sint16 error_x=0;
sint16 PID_Loc(sint16 SetValue, sint16 ActualValue)//   40 30
{
    sint16 PIDLoc;                                  //位置
    sint16 Ek;
    static sint16 LocSum = 0;
    static sint16 Ek1 = 0 ;
    Ek = SetValue - ActualValue;   //92-(100)=-8
    LocSum +=  Ek;   //                      //累计误差
        Kp_position = 5.2;
        Kd_position = 0;
    PIDLoc =  Kp_position *  Ek +  Kd_position * ( Ek1 -  Ek);
    Ek1 =  Ek;
    return PIDLoc;
}

void oled_show_Pid(void)
{
    ips114_showstr(6,1,"Kp_position");
    ips114_showfloat(90,1,Kp_position,3,2);
    ips114_showstr(6,2,"Ki_position");
    ips114_showfloat(90,2,Ki_position,3,2);
    ips114_showstr(6,3,"Kd_position");
    ips114_showfloat(90,3,Kd_position,3,2);
}

sint16 error_roll = 0;
/************************************************
函数名称 ： PID_Loc
功    能 ： PID位置(Location)计算
参    数 ： SetValue ------ 设置值(期望值)
            ActualValue --- 实际值(反馈值)
            PID ----------- PID数据结构
返 回 值 ： PIDLoc -------- PID位置
作    者 ： strongerHuang
*************************************************/

sint16 PID_Loc_Roll(float SetValue, float ActualValue)//  0 5
{
    //190youzhuan
    sint16 PIDLoc;                                  //位置
    float Ek;
    static float LocSum = 0;
    static float Ek1 = 0 ;//180-190=-10
    Ek = SetValue - ActualValue;   //0-(5)=-5
    LocSum +=  Ek;   //                      //累计误差
    PIDLoc =  40 *  Ek+  0 * ( Ek1 -  Ek);   //50*(-200)=-10000  50*2000=100000  20000%50=400
    Ek1 =  Ek;
    return PIDLoc;
}


sint16 PID_Loc_need_charge(float SetValue, float ActualValue)//  0 5
{
    //190youzhuan
    sint16 PIDLoc;                                  //位置
    float Ek;
    static float LocSum = 0;
    static float Ek1 = 0 ;//180-190=-10
    Ek = SetValue - ActualValue;   //0-(5)=-5
    LocSum +=  Ek;   //                      //累计误差
    PIDLoc =   1.8*  Ek+  0.8 * ( Ek1 -  Ek);   //50*(-200)=-10000  50*2000=100000  20000%50=400
    Ek1 =  Ek;
    return PIDLoc;
}
//
//sint16 PID_Loc_Radius(sint16 SetValue, sint16 ActualValue)//  0 5
//{
//    sint16 PIDLoc;                                  //位置
//    sint16 Ek;
//    static sint16 LocSum = 0;
//    static sint16 Ek1 = 0 ;
//    Ek = SetValue - ActualValue;   //0-(5)=-5
//    LocSum +=  Ek;   //                      //累计误差
//    PIDLoc =  myCar.Kp_Radius *  Ek + ( myCar.Ki_Radius *  LocSum) +  myCar.Kd_Radius * ( Ek1 -  Ek);   //50*(-200)=-10000  50*2000=100000  20000%50=400
//    Ek1 =  Ek;
//    return PIDLoc;
//}



float Expect_Roll_Speed=0;

//float Aspeed_kp;
//float Aspeed_kd;
sint16 Aspeed_out=0;
sint16 Radius=0;//转向半径




void angspeed_control(void)
{
    static sint16 last_error_ANG;
//    sint16 temp_speed ;
//    temp_speed=Average_encValue;//Average_encValue;//speed;

//  if(speed>0.8*realset_speed)
//  Aspeed_kp = myCar.Aspeed_kp+myCar.Aspeed_kp*(speed-0.8*realset_speed)*0.01;
//  else
//    Radius = PID_Loc_Radius(0,error_x);
//    Radius = 0.87*error_x;
//    Aspeed_kp = myCar.Aspeed_kp;//+(0.5*(float)(temp_speed*temp_speed)/(320*320));
//    Aspeed_kd = myCar.Aspeed_kd;
    Expect_Roll_Speed=error_x;//temp_speed*0.02;
    Expect_Roll_Speed=(Expect_Roll_Speed>420)?420:Expect_Roll_Speed;
    Aspeed_out=3.50*(Expect_Roll_Speed-yaw_rate)+0.20*(last_error_ANG-Expect_Roll_Speed);//yaw_rate;//Aspeed_kd*((Radius*temp_speed-yaw_rate)-last_error_ANG);//单P
    last_error_ANG=Expect_Roll_Speed-yaw_rate;

}



//void Direction_judgment1(sint16 x)
//{
//
//
//    error_x = PID_Loc(64,x);
//
////    pid_adjust_motor((sint16)myCar.base_speed-error_x,(sint16)myCar.base_speed+error_x);
////    pid_adjust_motor((sint16)myCar.base_speed,(sint16)myCar.base_speed);
//
//}


//top:                     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49
uint16 PointDevLeft[64] = {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  5,  7,  9, 11, 13, 18, 22, 25, 26, 27, 29, 29, 30, 30, 31, 32, 33, 34, 35, 36, 37, 39, 40, 41, 42, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43 };
uint16 *pointDevLeft = &L_Error.L_ERROR_1_5;  // 灯左侧过
//top:                     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54  55  56  57  58  59  60  61  62  63 64
uint16 PointDevRight[64] ={0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  5,  7,  9, 11, 13, 18, 22, 25, 26, 27, 29, 29, 30, 30, 31, 32, 33, 34, 35, 36, 37, 39, 40, 41, 42, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43 };
//                           59    59    59    59    59    59    59    59    59    55    49    45    39    36    34    30    24    20   17      14   12    10     7   6    5    5   4    4     3
//                           21,21,21,21,21,21,21,21,21,25,31,35,41,44,46,50,56,60,63,66,68,70,73,74,75,75,76,76,77,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78

uint16 *pointDevRight = &R_Error.R_ERROR_1_5; // 灯右侧过
// -3, -3,-3, -3, -3,  1,  3,  4,  4,  6,  7,  9, 13, 13, 14, 18, 20, 21, 18, 25, 30, 34, 37, 38, 41, 43, 43, 45, 48, 49, 51, 53, 54, 56, 58, 60, 60, 62, 64, 65, 67, 69, 69, 70, 72, 73, 74, 75, 75, 76
sint16 g_fTwoDeviation=0;
sint16 g_fDeviation=0;
sint16 g_fLastDeviation=0;
//g_u8BeaconLocation_true  x
//g_u8Top  y

uint8 left_state=0;
uint8 right_state=1;
sint16 error_Infrared = 0;

sint16 position_error = 0;
void car_control(void)
{
    if(g_u8GetBeacon)
    {
//            g_fLastDeviation = g_fDeviation;
//            g_fDeviation = g_u8BeaconLocation_true -64;
//          if(g_u8BeaconLocation_true < 54)
//          {
//              left_state = 1;
//              right_state = 0;
//
////              if(g_u8Top%5 == 0&&g_u8Top>=5)
////                  position_error = (uint16)*(pointDevRight+g_u8Top/5);
////              else if(g_u8Top>=5)
////                  position_error = (uint16)*(pointDevRight+g_u8Top/5-1)-(5-g_u8Top%5);
//
//              g_fDeviation = g_u8BeaconLocation_true -64+position_error; //灯左，右转+carwide
//          }
//          else if(g_u8BeaconLocation_true > 74)
//          {
//              right_state = 1;
//              left_state = 0;
////              if(g_u8Top%5 == 0&&g_u8Top>=5)
////                  position_error = -(uint16)*(pointDevLeft+g_u8Top);
////              else if(g_u8Top>=5)
////                  position_error = -(uint16)*(pointDevLeft+g_u8Top/5-1)+(5-g_u8Top%5);
//
//                  g_fDeviation = g_u8BeaconLocation_true -64+position_error; //灯左，右转+carwide
//          }
//          else if(g_u8BeaconLocation_true >= 54&&g_u8BeaconLocation_true <= 74)
//          {
//              if(left_state)
//              {
////                                if(g_u8Top%5 == 0 && g_u8Top>=5)
////                                    position_error = (uint16)*(pointDevRight+g_u8Top/5);
////                                else if(g_u8Top>=5)
////                                    position_error = (uint16)*(pointDevRight+g_u8Top/5-1)-(5-g_u8Top%5);
//
//                                g_fDeviation = g_u8BeaconLocation_true -64+position_error; //灯左，右转+carwide
//
//              }
//              else
//              {
////                                if(g_u8Top%5 == 0&& g_u8Top>=5)
////                                    position_error = -(uint16)*(pointDevLeft+g_u8Top);
////                                else if(g_u8Top>=5)
////                                    position_error = -(uint16)*(pointDevLeft+g_u8Top/5-1)+(5-g_u8Top%5);
//
//                                    g_fDeviation = g_u8BeaconLocation_true -64+position_error; //灯左，右转+carwide
//              }
//          }

//          g_fTwoDeviation = g_fDeviation - g_fLastDeviation;
//          Direction_judgment1(g_u8BeaconLocation_true);
            error_x = PID_Loc(94,g_u8BeaconLocation_true);

    }
    else
    {
//        if(Infrared_error>0)
//        {
////        error_Infrared = PID_Loc_Infrared(0,Infrared_error);
//            pid_adjust_motor(25,-25);
////        pid_adjust_motor((sint16)myCar.nolight_speed+error_Infrared,(sint16)myCar.nolight_speed-error_Infrared);
////        pid_adjust_motor((sint16)myCar.nolight_speed,(sint16)myCar.?nolight_speed);
//        }
//        if(Infrared_error<0) pid_adjust_motor(25,-25);
//        else
//        {
//            pid_adjust_motor(0,0);
//            if(left_state) pid_adjust_motor(-3,3);
//            else pid_adjust_motor(3,-3);

//        }

    }

}

