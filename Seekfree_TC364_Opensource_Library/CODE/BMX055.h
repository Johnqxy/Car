#ifndef BMX055_H
#define BMX055_H

#include "common.h"

#define bool    _Bool
#define true    1
#define false   0

//////////////地址在数据手册里均能找到///////////////
#define IIC_BMX055_ACC_ADR    0x18
#define IIC_BMX055_GYRO_ADR   0x68
#define IIC_BMX055_MAG_ADR    0x10

#define BMX055_ACC_XDATALSB   0x02
//#define BMX055_ACC_YDATALASB  0x04
//#define BMX055_ACC_ZDATALASB  0x06
#define BMX055_ACC_ID         0x00
#define BMX055_ACC_PMURANGE   0x0F
#define BMX055_ACC_PMUBW      0x10
#define BMX055_ACC_PMULPM     0x11


#define BMX055_GYRO_XDATALSB  0x02
//#define BMX055_GYRO_YDATALSB  0x04
//#define BMX055_GYRO_ZDATALSB  0x06
#define BMX055_GYRO_ID        0x00
#define BMX055_GYRO_RANGE     0x0F
#define BMX055_GYRO_BW        0x10
#define BMX055_GYRO_LPM       0x11
#define BMX055_GYRO_RATEHBW   0x13

#define BMX055_MAG_XDATALSB   0x42
//#define BMX055_MAG_YDATALSB   0X44
//#define BMX055_MAG_ZDATALSB   0X46
#define BMX055_MAG_ID         0x40
#define BMX055_MAG_POM        0x4B
#define BMX055_MAG_DATARATE   0x4C
#define BMX055_MAG_INTEN      0x4E

typedef struct
{
  float GYROXdata;
  float GYROYdata;
  float GYROZdata;
  float ACCXdata;
  float ACCYdata;
  float ACCZdata;
  float MAGXdata;
  float MAGYdata;
  float MAGZdata;
}BMX055Datatypedef;


extern float GYRO_Speed_Z;
uint8 BMX055_init(void);
uint8 BMX055_DataRead(BMX055Datatypedef *Q, uint8 type);
extern void Get_Car_GYRO(void); 
extern void Get_Car_Angle(void);   
extern void Negative_treatment();
void oled_show_gyroscope(void);
extern float pitch ;
extern float roll  ;
extern float yaw   ;
extern float pitch_rate ;
extern float roll_rate  ;
extern float yaw_rate   ;
#endif
