/*
   * Attitude_Calculation.h
 *
 *  Created on: 2020年5月14日
 *      Author: Administrator
 */

#ifndef SRC_APPSW_TRICORE_APP_ATTITUDE_CALCULATION_H_
#define SRC_APPSW_TRICORE_APP_ATTITUDE_CALCULATION_H_

#include "headfile.h"

#define PI					3.14159265358979f

#define  PERIODHZ      (float)250       /////采样频率
#define  PERIODS       (float)0.004          ////采样周期

typedef struct{
  float W;
  float X;
  float Y;
  float Z;
}QuaternionTypedef;

typedef struct{
  float Pitch;  //俯仰角
  float Yaw;    //偏航角
  float Roll;   //翻滚角
}EulerAngleTypedef;

typedef struct{
  float Xdata;
  float Ydata;
  float Zdata;
}AttitudeDatatypedef;

extern QuaternionTypedef    Quaternion;   //四元数
extern EulerAngleTypedef    EulerAngle;   //欧拉角
extern QuaternionTypedef    AxisAngle;    //轴角
extern EulerAngleTypedef    EulerAngleRate;//当前欧拉角速度

extern QuaternionTypedef    MeaQuaternion;
extern EulerAngleTypedef    MeaEulerAngle;
extern QuaternionTypedef    MeaAxisAngle;

extern QuaternionTypedef    ErrQuaternion;
extern EulerAngleTypedef    ErrEulerAngle;
extern QuaternionTypedef    ErrAxisAngle;
extern AttitudeDatatypedef         Acc;
extern AttitudeDatatypedef         Gyro;


extern void Quaternion_init(void);

extern void Attitude_UpdateGyro(void);

extern void Attitude_UpdateAcc(void);

#endif /* SRC_APPSW_TRICORE_APP_ATTITUDE_CALCULATION_H_ */
