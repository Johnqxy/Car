/*
 * Positional_pid.h
 *
 *  Created on: 2020��11��14��
 *      Author: Javelin
 */

#ifndef SRC_APPSW_TRICORE_USER_POSITION_H_
#define SRC_APPSW_TRICORE_USER_POSITION_H_


#include "headfile.h"

#define DIRECTION_CONTROL_COUNT 5
#define SPEED_CONTROL_COUNT 5

extern float Expect_Roll_Speed;
extern sint16 error_roll ;

extern uint8  direction_control_cnt;//������Ƽ�����
extern uint8 speed_control_cnt;//�ٶȿ��Ƽ�����
extern sint16 Aspeed_out;
extern sint16 position_error;
extern short error_position1;
extern sint16 error_x;
extern sint16 Radius;//ת��뾶
void angspeed_control(void);
void oled_show_Pid(void);
short PID_Loc(short SetValue, short ActualValue);
sint16 PID_Loc_Roll(float SetValue, float ActualValue);
sint16 PID_Loc_need_charge(float SetValue, float ActualValue);
void Direction_judgment1(sint16 x);
void car_control(void);

extern struct Car_Information myCar;       //������Ϣ



struct Car_Information
{


  sint16 base_speed1;//�����ٶ�
  sint16 base_speed2;//�����ٶ�
  sint16 base_speed3;//�����ٶ�
  sint16 base_speed4;//�����ٶ�
  sint16 nolight_speed_high;
  sint16 nolight_speed_low;
  uint32 loseBeacon_Threshold;
  uint16 FlashHandle;
  uint16 exposure_time;



   float Aspeed_kp;      //���ٶȻ�kp
   float Aspeed_kd;     //���ٶȻ�kd

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

   float SpeedPA;  //����
   float SpeedIA;//0.8;
   float SpeedDA;

   float SpeedPB;
   float SpeedIB;
   float SpeedDB;



};

extern struct left_error_Information L_Error;

struct left_error_Information
{
  uint16 L_ERROR_1_5;//�����ٶ�
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
        uint16 R_ERROR_1_5;//�����ٶ�
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




////���峵��״̬
//typedef enum
//{
//    CAR_STOP = 0,               //ͣ��״̬    0
//    CAR_START,                  //����״̬    1
//    CAR_NORMAL,                 //����״̬    2
//    CAR_SMALLS,                 //СS״̬     3
//    CAR_STRAIGHT,               //ֱ��״̬    4
//    CAR_ENTERTURN,              //����״̬    5
//    CAR_INTURN,                 //����״̬    6
//    CAR_RAMPWAY,                //�µ�        9
//    CAR_OBSTACLE,               //�ϰ�       10
//    CAR_BACKUP,                 //����״̬   11
//} CAR_STATUS_e;

//
//struct CarRun_Information
//{
//    sint16 Rotary_mode;//�ж����һ�
//    sint16 CarStatus;//�����˶�״̬
//    sint16 Y_NBRunIn;//�Ƿ������
//    sint16 Y_NSRunIn;//�Ƿ����С��
//    sint16 Y_NRunOut;//�Ƿ����
//
//};

//
//typedef enum
//{
//    LEFT_IN=12,//���뻷 12
//    RIGHT_IN=13,//���뻷 13
//    Pre_INTEND_IN=14,//׼���뻷 14
//    Start_INTEND_IN = 15,
//    INTEND_IN = 16,
//    IN_LEFT=17,//����
//    IN_RIGHT=18,//���һ�
//    ON_ROTARY=19,//�ڻ���15
//    Pre_INTEND_OUT=20,//׼������16
//    INTEND_OUT = 21,
//    shangpo=22,
//    READY_RELAY=23,//׼������
//    STOP_RELAY=24,
//    over = 25,
//    ready_CK=26
//}Rotary_e;

//
//
//extern int enterR_distance;
//extern int round_kind ;
//extern  float Turn_yaw;

//extern volatile CAR_STATUS_e carStatus;   //����״̬
//extern volatile Rotary_e Rotary_flag;//������־
//extern struct CarRun_Information myCarRun;//�����˶�״̬
////extern volatile CAR_STATUS_e   Last_carStatus;   //����״̬
//extern uint8 outround_temp ;
//extern float angle;
//extern uint32 delay_goslow ;




#endif /* SRC_APPSW_TRICORE_USER_POSITION_H_ */
