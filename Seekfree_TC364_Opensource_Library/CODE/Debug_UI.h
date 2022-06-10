/*
***基本函数列表及注释***
*/
#ifndef __DEBUG_UI_H__
#define __DEBUG_UI_H__


#define Beep P00_8
#define Beep_on 1
#define Beep_off 0


#define  FLASHSECTOR    11      //定义存入扇区码数
struct F_uint32Value
{
        uint32 base_speed1 ;uint32 base_speed2 ;uint32 base_speed3 ;uint32 base_speed4 ;uint32 nolight_speed_low ;uint32 FlashHandle ;uint32 ;uint32 ;uint32 ;uint32 ;
        uint32 Threshold_0_4 ;uint32 Threshold_5_9 ;uint32 Threshold_10_14 ;uint32 Threshold_15_19 ;uint32 Threshold_20_24 ;uint32 Threshold_25_29 ;uint32 Threshold_30_34 ;uint32 Threshold_35_39 ;uint32 Threshold_40_44 ;uint32 Threshold_45_49 ;
        uint32 exposure_time;uint32 ;uint32 ;uint32 ;uint32 ;uint32 ;uint32 ;uint32 ;uint32 ;uint32 ;
        uint32 L_ERROR_1_5;uint32 L_ERROR_6_10;uint32 L_ERROR_11_15;uint32 L_ERROR_16_20;uint32 L_ERROR_21_25;uint32 L_ERROR_26_30;uint32 L_ERROR_31_35;uint32 L_ERROR_36_40;uint32 L_ERROR_41_45;uint32 L_ERROR_46_50;
        uint32 L_ERROR_51_55;uint32 L_ERROR_56_60;uint32 L_ERROR_61_65;uint32 ;uint32 ;uint32 ;uint32 ;uint32 ;uint32 ;uint32 ;
        uint32 R_ERROR_1_5;uint32 R_ERROR_6_10;uint32 R_ERROR_11_15;uint32 R_ERROR_16_20;uint32 R_ERROR_21_25;uint32 R_ERROR_26_30;uint32 R_ERROR_31_35;uint32 R_ERROR_36_40;uint32 R_ERROR_41_45;uint32 R_ERROR_46_50;
        uint32 R_ERROR_51_55;uint32 R_ERROR_56_60;uint32 R_ERROR_61_65;uint32 ;uint32 ;uint32 ;uint32 ;uint32 ;uint32 ;uint32 ;
        uint32 Aspeed_kp;uint32 Aspeed_kd;uint32 Kp_Roll;uint32 Kd_Roll;uint32 begin_V;uint32 recharge_V;uint32 recharge_target;uint32 ;uint32 ;uint32 ;
        uint32 Kp_position1;uint32 Kd_position1;uint32 Kp_position2;uint32 Kd_position2;uint32 Kp_position3;uint32 Kd_position3;uint32 Kp_position4;uint32 Kd_position4;uint32 Kp_position5;uint32 Kd_position5;
        uint32 SpeedPA;uint32 SpeedIA;uint32 SpeedDA;uint32 SpeedPB;uint32 SpeedIB;uint32 SpeedDB;uint32 ;uint32 ;uint32 ;uint32 ;
};


typedef enum
{
    MYKEY_L,  //左
    MYKEY_R,  //右
    MYKEY_U,  //上
    MYKEY_D,  //下
    MYKEY_M,  //中
    MYKEY_MAX,
} MYKEY_e;

typedef enum
{
    ALLFREE,
    LPRESS,
    RPRESS,
    UPRESS,
    DPRESS,
    MPRESS,
} MYKEY_STATE_e;

typedef enum
{
    DIAL1,
    DIAL2,
    DIAL3,
    DIAL4,
    DIAL5,
//    DIAL6,
    DIAL_MAX,
} DIAL_e;


//
//extern int16 pageValue; //设定首页

void MyKeyInit(void);
void DialInit(void);
uint8 GetDial(void);
void DebugUI(void);
void dial_scan(void);
void oled_show_code_switch(void);

#endif

