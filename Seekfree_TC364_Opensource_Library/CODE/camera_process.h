/*
 * camera_process.h
 *
 *  Created on: 2020年7月31日
 *      Author: ywf
 */
#include "headfile.h"//各个模块的头文件

#ifndef SRC_APPSW_TRICORE_USER_CAMERA_PROCESS_H_
#define SRC_APPSW_TRICORE_USER_CAMERA_PROCESS_H_

#define Image_Width MT9V03X_W
#define Image_Height MT9V03X_H



extern uint8 area[300];
extern float Roltw;
extern uint8 perimeter;
extern uint8  g_u8BeaconLocation;
extern uint8 g_u8RealTop;
extern uint8 g_u8Bottom_O;
extern uint8 width;
extern uint8 g_u8Top;
extern uint8 g_u8GetBeacon;

extern uint8 g_u8BeaconLocation_x1;
extern uint8 g_u8BeaconLocation_x2;
extern uint8 g_u8Top_y1;
extern uint8 g_u8Top_y2;


extern uint8 g_u8BeaconLocation_true;
extern uint8 g_u8Top_true;
extern uint8 loseBeacon;
void WavefilteringEdge(uint8 EagleImgBuffer[Image_Height][Image_Width]);
void WavefilteringPoint(uint8 EagleImgBuffer[Image_Height][Image_Width],uint8 times);
void EagalCameraBeaconHandleGraduateAYear(uint8 EagleImgBuffer[Image_Height][Image_Width]);
uint8 EightDomainBoundaryTracing(uint8 f_firstarea_X,uint8 f_firstarea_Y,uint8 EagleImgBuffer[Image_Height][Image_Width]);
void FlashHandle (void);

#endif /* SRC_APPSW_TRICORE_USER_CAMERA_PROCESS_H_ */
