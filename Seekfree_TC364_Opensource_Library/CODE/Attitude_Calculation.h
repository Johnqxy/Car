/*
   * Attitude_Calculation.h
 *
 *  Created on: 2020��5��14��
 *      Author: Administrator
 */

#ifndef SRC_APPSW_TRICORE_APP_ATTITUDE_CALCULATION_H_
#define SRC_APPSW_TRICORE_APP_ATTITUDE_CALCULATION_H_

#include "headfile.h"

#define PI					3.14159265358979f

#define  PERIODHZ      (float)250       /////����Ƶ��
#define  PERIODS       (float)0.004          ////��������

typedef struct{
  float W;
  float X;
  float Y;
  float Z;
}QuaternionTypedef;

typedef struct{
  float Pitch;  //������
  float Yaw;    //ƫ����
  float Roll;   //������
}EulerAngleTypedef;

typedef struct{
  float Xdata;
  float Ydata;
  float Zdata;
}AttitudeDatatypedef;

extern QuaternionTypedef    Quaternion;   //��Ԫ��
extern EulerAngleTypedef    EulerAngle;   //ŷ����
extern QuaternionTypedef    AxisAngle;    //���
extern EulerAngleTypedef    EulerAngleRate;//��ǰŷ�����ٶ�

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
