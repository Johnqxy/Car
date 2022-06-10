#ifndef _CAMERA_H
#define _CAMERA_H

#include "headfile.h"

#define img_line 120
#define img_column 188


typedef enum {
    none = 0,               //无类型0

    STR_W,                  //直道1
    CUR_W,                  //弯道（好像没用到）2

    CRS_W_S1,               //十字阶段1（入十字）3
    CRS_W_S2,               //十字阶段2（出十字）4

    FOK_W_S1,               //三岔阶段1（入三岔，可以看到三岔下面的直道）5
    FOK_W_S2,               //三岔阶段2（看不到直道了）6
    FOK_W_S3,               //三岔阶段3（停车旋转）7

    //左环
    LCIR_W_S1,              //环岛阶段1（初入左环岛，看到了直道后左边界缺失了但有边界是直线，可能会误判）8
    LCIR_W_S2,              //环岛阶段2（环岛确认，发现S1阶段后出现了最下面一段是左边界没有了）9
    LCIR_W_S2_5,            //环岛阶段2.5（S3的准备阶段，看到双边界都有时进入，说明在环岛直道的中间）10
    LCIR_W_S3,              //环岛阶段3（入环阶段，寻找特殊点，补线入环）11
    LCIR_W_S4,              //环岛阶段4（环内阶段）12
    LCIR_W_S5,              //环岛阶段5（出环阶段，发现边界出现了类型为3或6的段）13
    LCIR_W_S6,              //环岛阶段6（出环结束，在圆环的直道上，通过陀螺仪判断）14
    LCIR_W_S7,              //环岛阶段7（准备彻底驶出环岛，再次走到了S3阶段的位置，但判断条件是，第二段为正常边界）15

    //右环
    RCIR_W_S1,              //环岛阶段1 16
    RCIR_W_S2,              //环岛阶段2 17
    RCIR_W_S2_5,            //环岛阶段2.5 18
    RCIR_W_S3,              //环岛阶段3 19
    RCIR_W_S4,              //环岛阶段4 20
    RCIR_W_S5,              //环岛阶段5 21
    RCIR_W_S6,              //环岛阶段6 22
    RCIR_W_S7,              //环岛阶段7 23
} image_type;

//从图像中提取出的信息结构体
typedef struct {
    image_type imgtype;     //图像类型
    float offset;           //位置偏差
} image_parameter;

#define SUD_TH 20                   //宽度突变阈值
#define SSUD_TH 10                  //单边突变阈值，当dl或dr超过时认为是发生突变了
#define NSUD_TH 3                   //非突变特殊阈值，认为在这个范围内是正常波动
#define C_TH 7
#define CRS_OFFSET_TH 10            //十字偏差阈值，十字路口要直行，偏差不能太大
#define CUR_CIRTH 0.985             //曲率阈值，用来判断是线边界还是曲线，需要实测一下
/////////////全局变量/////////////
extern uint8 centerline[120];//中线
extern uint8 leftline[120];
extern uint8 rightline[120];
extern uint8 leftfindflag[120];
extern uint8 rightfindflag[120];
extern uint8 image_cache[MT9V03X_H][MT9V03X_W];
extern uint8 part_type[MT9V03X_H];         //分段类型
extern uint8 part_index[MT9V03X_H];        //分段终点下标
extern uint8 part_num;
extern uint8 road_type[120];
extern uint8 enter_flag;
extern uint8 img_mode;
extern uint8 num;
extern float cur;
extern image_parameter image_para;
extern float error,offset;
extern uint8 break_hangshu;
extern uint8 FOK_OUT_FLAG_1;
extern uint8 FOK_OUT_FLAG_2 ;
extern uint8 flag;
extern int degree;
///////////////全局函数/////////////////

extern void img_extract(void);

int GetOTSU(unsigned char tmImage[MT9V03X_H][MT9V03X_W]);

void Basic_line_scan(void);

void Advanced_line_scan(void);

void Boundary_part(void);

float angle_caculate(float x1, float y1, float x2, float y2, float x3, float y3);

float cur_circle(uint8 m);

void image_distinguish(void);

void Img_type_test(void);

/*******************/

#endif
