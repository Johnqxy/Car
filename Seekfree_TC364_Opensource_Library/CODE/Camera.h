#ifndef _CAMERA_H
#define _CAMERA_H

#include "headfile.h"

#define img_line 120
#define img_column 188


typedef enum {
    none = 0,               //������0

    STR_W,                  //ֱ��1
    CUR_W,                  //���������û�õ���2

    CRS_W_S1,               //ʮ�ֽ׶�1����ʮ�֣�3
    CRS_W_S2,               //ʮ�ֽ׶�2����ʮ�֣�4

    FOK_W_S1,               //����׶�1�����������Կ������������ֱ����5
    FOK_W_S2,               //����׶�2��������ֱ���ˣ�6
    FOK_W_S3,               //����׶�3��ͣ����ת��7

    //��
    LCIR_W_S1,              //�����׶�1�������󻷵���������ֱ������߽�ȱʧ�˵��б߽���ֱ�ߣ����ܻ����У�8
    LCIR_W_S2,              //�����׶�2������ȷ�ϣ�����S1�׶κ������������һ������߽�û���ˣ�9
    LCIR_W_S2_5,            //�����׶�2.5��S3��׼���׶Σ�����˫�߽綼��ʱ���룬˵���ڻ���ֱ�����м䣩10
    LCIR_W_S3,              //�����׶�3���뻷�׶Σ�Ѱ������㣬�����뻷��11
    LCIR_W_S4,              //�����׶�4�����ڽ׶Σ�12
    LCIR_W_S5,              //�����׶�5�������׶Σ����ֱ߽����������Ϊ3��6�ĶΣ�13
    LCIR_W_S6,              //�����׶�6��������������Բ����ֱ���ϣ�ͨ���������жϣ�14
    LCIR_W_S7,              //�����׶�7��׼������ʻ���������ٴ��ߵ���S3�׶ε�λ�ã����ж������ǣ��ڶ���Ϊ�����߽磩15

    //�һ�
    RCIR_W_S1,              //�����׶�1 16
    RCIR_W_S2,              //�����׶�2 17
    RCIR_W_S2_5,            //�����׶�2.5 18
    RCIR_W_S3,              //�����׶�3 19
    RCIR_W_S4,              //�����׶�4 20
    RCIR_W_S5,              //�����׶�5 21
    RCIR_W_S6,              //�����׶�6 22
    RCIR_W_S7,              //�����׶�7 23
} image_type;

//��ͼ������ȡ������Ϣ�ṹ��
typedef struct {
    image_type imgtype;     //ͼ������
    float offset;           //λ��ƫ��
} image_parameter;

#define SUD_TH 20                   //���ͻ����ֵ
#define SSUD_TH 10                  //����ͻ����ֵ����dl��dr����ʱ��Ϊ�Ƿ���ͻ����
#define NSUD_TH 3                   //��ͻ��������ֵ����Ϊ�������Χ������������
#define C_TH 7
#define CRS_OFFSET_TH 10            //ʮ��ƫ����ֵ��ʮ��·��Ҫֱ�У�ƫ���̫��
#define CUR_CIRTH 0.985             //������ֵ�������ж����߽߱绹�����ߣ���Ҫʵ��һ��
/////////////ȫ�ֱ���/////////////
extern uint8 centerline[120];//����
extern uint8 leftline[120];
extern uint8 rightline[120];
extern uint8 leftfindflag[120];
extern uint8 rightfindflag[120];
extern uint8 image_cache[MT9V03X_H][MT9V03X_W];
extern uint8 part_type[MT9V03X_H];         //�ֶ�����
extern uint8 part_index[MT9V03X_H];        //�ֶ��յ��±�
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
///////////////ȫ�ֺ���/////////////////

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
