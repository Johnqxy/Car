/*
 * Positional_pid.h
 *
 *  Created on: 2020年11月14日
 *      Author: Javelin
 */

#ifndef SRC_APPSW_TRICORE_USER_POSITION_H_
#define SRC_APPSW_TRICORE_USER_POSITION_H_


#include "headfile.h"

#define DIRECTION_CONTROL_COUNT 5
#define SPEED_CONTROL_COUNT 5

extern float Expect_Roll_Speed;
extern sint16 error_roll ;

extern uint8  direction_control_cnt;//方向控制计数器
extern uint8 speed_control_cnt;//速度控制计数器
extern sint16 Aspeed_out;
extern sint16 position_error;
extern short error_position1;
extern sint16 error_x;
extern sint16 Radius;//转向半径
void angspeed_control(void);
void oled_show_Pid(void);
short PID_Loc(short SetValue, short ActualValue);
sint16 PID_Loc_Roll(float SetValue, float ActualValue);
sint16 PID_Loc_need_charge(float SetValue, float ActualValue);
void Direction_judgment1(sint16 x);
void car_control(void);

extern struct Car_Information myCar;       //车辆信息



struct Car_Information
{


  sint16 base_speed1;//基础速度
  sint16 base_speed2;//基础速度
  sint16 base_speed3;//基础速度
  sint16 base_speed4;//基础速度
  sint16 nolight_speed_high;
  sint16 nolight_speed_low;
  uint32 loseBeacon_Threshold;
  uint16 FlashHandle;
  uint16 exposure_time;



   float Aspeed_kp;      //角速度环kp
   float Aspeed_kd;     //角速度环kd

   float Kp_Roll;
   float Kd_Roll;
   float begin_V;
   float recharge_V;
   float recharge_target;


   float Kp_position1;
   float Kp_position2;
   float Kp_position3;
   float Kp_position4;
   float Kp_position5;

   float Kd_position1;
   float Kd_position2;
   float Kd_position3;
   float Kd_position4;
   float Kd_position5;

   float SpeedPA;  //可以
   float SpeedIA;//0.8;
   float SpeedDA;

   float SpeedPB;
   float SpeedIB;
   float SpeedDB;



};

extern struct left_error_Information L_Error;

struct left_error_Information
{
  uint16 L_ERROR_1_5;//基础速度
  uint16 L_ERROR_6_10;
  uint16 L_ERROR_11_15;
  uint16 L_ERROR_16_20;
  uint16 L_ERROR_21_25;
  uint16 L_ERROR_26_30;
  uint16 L_ERROR_31_35;
  uint16 L_ERROR_36_40;
  uint16 L_ERROR_41_45;
  uint16 L_ERROR_46_50;
  uint16 L_ERROR_51_55;
  uint16 L_ERROR_56_60;
  uint16 L_ERROR_61_65;
};

extern struct right_error_Information R_Error;

struct right_error_Information
{
        uint16 R_ERROR_1_5;//基础速度
        uint16 R_ERROR_6_10;
        uint16 R_ERROR_11_15;
        uint16 R_ERROR_16_20;
        uint16 R_ERROR_21_25;
        uint16 R_ERROR_26_30;
        uint16 R_ERROR_31_35;
        uint16 R_ERROR_36_40;
        uint16 R_ERROR_41_45;
        uint16 R_ERROR_46_50;
        uint16 R_ERROR_51_55;
        uint16 R_ERROR_56_60;
        uint16 R_ERROR_61_65;
};




////定义车辆状态
//typedef enum
//{
//    CAR_STOP = 0,               //停车状态    0
//    CAR_START,                  //发车状态    1
//    CAR_NORMAL,                 //正常状态    2
//    CAR_SMALLS,                 //小S状态     3
//    CAR_STRAIGHT,               //直道状态    4
//    CAR_ENTERTURN,              //入弯状态    5
//    CAR_INTURN,                 //弯内状态    6
//    CAR_RAMPWAY,                //坡道        9
//    CAR_OBSTACLE,               //障碍       10
//    CAR_BACKUP,                 //倒车状态   11
//} CAR_STATUS_e;

//
//struct CarRun_Information
//{
//    sint16 Rotary_mode;//判断左右环
//    sint16 CarStatus;//车辆运动状态
//    sint16 Y_NBRunIn;//是否入过大环
//    sint16 Y_NSRunIn;//是否入过小环
//    sint16 Y_NRunOut;//是否出环
//
//};

//
//typedef enum
//{
//    LEFT_IN=12,//左入环 12
//    RIGHT_IN=13,//右入环 13
//    Pre_INTEND_IN=14,//准备入环 14
//    Start_INTEND_IN = 15,
//    INTEND_IN = 16,
//    IN_LEFT=17,//进左环
//    IN_RIGHT=18,//进右环
//    ON_ROTARY=19,//在环中15
//    Pre_INTEND_OUT=20,//准备出环16
//    INTEND_OUT = 21,
//    shangpo=22,
//    READY_RELAY=23,//准备接力
//    STOP_RELAY=24,
//    over = 25,
//    ready_CK=26
//}Rotary_e;

//
//
//extern int enterR_distance;
//extern int round_kind ;
//extern  float Turn_yaw;

//extern volatile CAR_STATUS_e carStatus;   //车辆状态
//extern volatile Rotary_e Rotary_flag;//环岛标志
//extern struct CarRun_Information myCarRun;//车辆运动状态
////extern volatile CAR_STATUS_e   Last_carStatus;   //车辆状态
//extern uint8 outround_temp ;
//extern float angle;
//extern uint32 delay_goslow ;




#endif /* SRC_APPSW_TRICORE_USER_POSITION_H_ */
