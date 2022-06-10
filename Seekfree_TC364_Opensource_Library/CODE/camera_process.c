
#include "headfile.h"//各个模块的头文件
#define findcount    300
#define ABANDONLEFT  0//丢弃掉的图像范围
#define ABANDONRIGHT 0
#define ABANDONUP    0
#define ABANDONDOWN   0
#define WIDTHLIMITED  Image_Width       //宽度限制
#define Image_Height    MT9V03X_H      //max line 行max
#define Image_Width  MT9V03X_W     //max column 列max
#define LINE    Image_Height      //max line 行max
#define COLUMN  Image_Width     //max column 列max
#define BLACK_POINT   0         //BLACK_POINT
#define WHITE_POINT   255     //wihte
#define FAR  1
#define NEAR  0

int flashflag,Infraredflag,positionflag;
float Rectangularity=0;

//uint8 Recordflag =0 ;
//uint8 Distanceflag = FAR;
//uint8 g_iJudege=0;
//uint8 g_iJudege1=0;

uint8 g_u8BeaconLocation_x1=0;
uint8 g_u8BeaconLocation_x2=0;
uint8 g_u8Top_y1=0;
uint8 g_u8Top_y2=0;


//uint8 g_u8Car_start = 0;
//uint16 g_u16PointNum = 0;
//uint8 g_u8BeaconHeight = 0;
uint8 g_u8Top = 0;
uint8 g_u8Bottom_O = 0;
uint8 g_u8RealTop=0;
//uint8 carwide = 3;
//uint8 carwide1 = 3;
//uint8 g_u8LastTop = 0;
uint8 g_u8GetBeacon = 0;
uint8 loseBeacon = 0;
uint8 g_u8BeaconArea = 0;
uint8  g_u8BeaconLocation = 0;
int Deviation=0,Deviation1=0;


uint8 squareflag=0;
//uint8 g_u8Threshold = 40;
uint8 u8_findpoint_X[findcount]={0};
uint8 u8_findpoint_Y[findcount]={0};
uint8 BorderX=0;
uint8 BorderY=0;

uint8 f_firstarea_X=0;
uint8 f_firstmax_X[Image_Width]={0};
uint8 f_firstmin_X[Image_Width]={0};
uint8 f_firstmaxX=ABANDONLEFT;
uint8 f_firstminX=COLUMN-ABANDONRIGHT-1;

uint8 f_firstarea_Y=0;
uint8 f_firstmax_Y[Image_Height]={0};
uint8 f_firstmin_Y[Image_Height]={0};
uint8 f_firstmaxY=ABANDONUP;
uint8 f_firstminY=LINE-ABANDONDOWN-1;
uint8 area[findcount]={0};
uint8 areamax=0;
uint8 circumferencemax=0;
uint8 f_areamax=0;
uint8 ignorepoint=0;
uint8 missionfailed=0;
uint8 newk;
uint8 g_u8Topline=0;

uint8 g_u8BeaconLocation_true=0;
uint8 g_u8Top_true=0;
//uint8 flag = 0;

float Roltw=0;
uint8 width=0;

//Beacon_calculate
uint8 g_iNear = 0;
uint8 g_iTop = 0;
uint8 g_iIndex = 0;

uint8 startcar = 0;

/*前摄像头*/
//灯左过
//top:                        0  1   2   3  4  5  6   7   8   9   10  11  12   13   14  15  16  17  18  19  20   21  22  23  24  25  26  27  28  29  30  31   32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49
int PointDevLeft_75[Image_Height] =  {90,90 ,105 ,95,100,100, 100,105, 107, 108, 111, 113 ,121,122, 125 ,129,134,135,136,138,139,143,144,144,149,152,123,154,157,158,159,160,161,162,163,163,165,165,165,165,167,169,170,170,170,170,170,170,171,162};
int *pointDevLeft_75 = PointDevLeft_75;
//top:                     0   1   2   3   4   5   6   7   8   9  10  11  12  13   14  15   16   17   18   19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49
int PointDevLeft_25[Image_Height] =  {90,90 ,105 ,95,100,100, 100,105, 107, 108, 111, 113 ,121,122, 125 ,129,134,135,136,138,139,143,144,144,149,152,123,154,157,158,159,160,161,162,163,163,165,165,165,165,167,169,170,170,170,170,170,170,171,162};   //46 47 48 49
int *pointDevLeft_25 = PointDevLeft_25;
// -3, -3,-3, -3, -3,  1,  3,  4,  4,  6,  7,  9, 13, 13, 14, 18, 20, 21, 18, 25, 30, 34, 37, 38, 41, 43, 43, 45, 48, 49, 51, 53, 54, 56, 58, 60, 60, 62, 64, 65, 67, 69, 69, 70, 72, 73, 74, 75, 75, 76

////灯右过
////top:                         0  1   2   3  4  5   6   7   8   9  10  11  12  13  14  15  16  17  18  19   20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36   37  38  39  40  41  42  43  44  45  46  47  48  49
//int PointDevRight_75[50] =  { 70,70,69,  68,66,64, 63, 61, 57, 55, 53, 46, 44, 42, 41, 39, 35, 33 ,30 ,29, 28, 26, 24,  22, 17, 17, 15, 13, 12, 11, 10, 9,  7,  7,  5,  4,  4,   4 ,  3,  3,  3,  3,  2,  2,  1,  1,  1,  1,  1,  1};
//int *pointDevRight_75 = PointDevRight_75;
////top:                     0   1   2   3   4   5   6   7   8   9  10  11  12  13   14  15  16  17  18  19  20   21  22  23  24  25  26  27  28  29  30  31  32  33  34  35 36 37  38  39  40  41  42  43  44  45  46  47  48  49
//int PointDevRight_25[50] = { 70,70,69, 68, 66, 64, 62, 59, 57, 55, 51, 47, 45, 42, 41, 37, 32, 30, 30, 30, 26, 24, 21,  20, 18, 14, 11, 10, 10, 9,  8,  7,  6,  4,  4,  4,  4, 4,  4,  3,  3,  3,  3,  3,  3,  3,  3,  2,  2,  1};   //46 47 48 49
//int *pointDevRight_25 = PointDevRight_25;
//// -3, -3,-3, -3, -3,  1,  3,  4,  4,  6,  7,  9, 13, 13, 14, 18, 20, 21, 18, 25, 30, 34, 37, 38, 41, 43, 43, 45, 48, 49, 51, 53, 54, 56, 58, 60, 60, 62, 64, 65, 67, 69, 69, 70, 72, 73, 74, 75, 75, 76

//前                     5  7  9  12 16 21 25 27  31 37  40  45 50 50 55 60  60 63  65  70  75  78  80  85  90  90  90  95  100 105 105  105 105 105

//int LINITMAX[50] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,16,19,19,20,24,24,24,26,28,29,30,31,33,33,34,35,37,37,38,39,40,41,41,41,41,41,41,41,41,41,41,41,41,41,41};
//int *limitrmax = LINITMAX;
//
//int LINITMIN[50] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,16,16,15,16,16,16,16,16,16,16,16,16,16,15,13,13,13,13,13,12,12,12,12,12,12,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 };
//int *limitrmin = LINITMIN;


//
//int LINITMAX[65] = {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,37,39,40,40,39,39,38,38,37,36,35,34,33,31,29,27,25,23,21,19,17,15,13,11,10,10,10,10,10,10,10,10,10,10,};
//int *limitrmax = LINITMAX;
//
//int LINITMIN[65] = {80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,9 ,9 ,10,10,11,11,12,12,13,13,14,14,16,18,18,19,21,21,21,19,18,17,16,15,15,14,14,13,12,11,10,9 ,8 ,7 ,6 ,6 ,5 ,4 ,4 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 };
//int *limitrmin = LINITMIN;

int LINITMAX[Image_Height] = {6 ,8 ,8 ,8 ,8 ,8, 8, 8, 10,10,10,10,10,11,11,11,11,12,12,13,14,15,15,16,17,17,18,18,18,18,20,20,20,20,22,22,22,22,28,28,28,30,30,30,30,30,31,31,32,33,32,33,34,34,34,40,35,36,36,40,41,41,41,41,41};
int*limitrmax=LINITMAX;
                  //0，1，2，3，4, 5，6，7，8，9，10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64
int LINITMIN[Image_Height] = {2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,4 ,5 , 6, 6, 6, 6, 6, 7, 8, 8,10,10,10,11,11,12,12,13,13,13,13,14,14,14,14,15,15,15,15,15,16,17,18,18,19,20,16,16,15,15, 1, 1, 1,1  };
int *limitrmin = LINITMIN;

//int LINITMAX[65] = {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,31,33,33,34,34,34,34,37,37,38,38,39,40,40,40,45,45,45,45,45,45,46,46,46,46,50,50,50,50,50,50,32,30,30,30,30,30,30,30,30,30,30,30,30,30,80};
//int *limitrmax = LINITMAX;
//
//int LINITMIN[65] = {80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,12,13,14,15,15,15,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,17,17,17,17,17,17,17,14,14,14,14,14,14,0 };
//int *limitrmin = LINITMIN;



//截取摄像头范围
void WavefilteringEdge(uint8 EagleImgBuffer[Image_Height][Image_Width])
{
     uint8 i=0;
     for(i=ABANDONUP;i<LINE-ABANDONDOWN;i++)
     {
           EagleImgBuffer[i][ABANDONLEFT] = BLACK_POINT;
           EagleImgBuffer[i][COLUMN-ABANDONRIGHT-1] = BLACK_POINT;
     }
     for(i=ABANDONLEFT;i<COLUMN-ABANDONRIGHT;i++)              //滤边线
     {
           EagleImgBuffer[ABANDONUP][i] = BLACK_POINT;
           EagleImgBuffer[LINE-ABANDONDOWN-1][i] = BLACK_POINT;
     }
}

//摄像头采集的点的滤波，若该点与其上下左右4个点的颜色不同，则令其转换颜色
void WavefilteringPoint(uint8 EagleImgBuffer[Image_Height][Image_Width],uint8 times)
{
    uint8 k,i,j;
    for(k=0;k<times;k++)
    {
        for(i=ABANDONUP+1;i<LINE-ABANDONDOWN-1;i++)
          {
              for(j=ABANDONLEFT+1;j<COLUMN-ABANDONRIGHT-1;j++)
              {
                if((EagleImgBuffer[i][j] == WHITE_POINT)
                    &&((EagleImgBuffer[i-1][j] == BLACK_POINT && EagleImgBuffer[i+1][j] ==BLACK_POINT)
                     ||(EagleImgBuffer[i][j-1] ==BLACK_POINT && EagleImgBuffer[i][j+1] ==BLACK_POINT)))
                     {
                         EagleImgBuffer[i][j] = BLACK_POINT;
                     }
              }
          }
    }
}

//
//void dilation(uint8* data, int width, int height)
//{
//    int i, j, index, sum, flag;
//    sum = height * width * sizeof(uint8);
//    uint8 *tmpdata = (uint8*)malloc(sum);
//    memcpy((uint8*)tmpdata, (uint8*)data, sum);
//    for(i = 1;i < height - 1;i++)
//    {
//        for(j = 1;j < width - 1;j++)
//        {
//            flag = 1;
//            for(int m = i - 1;m < i + 2;m++)
//            {
//                for(int n = j - 1; n < j + 2;n++)
//                {
//                    //自身及领域中若有一个为255
//                    //则将该点设为255
//                    if(tmpdata[i * width + j] > 0
//                        || tmpdata[m * width + n] > 0)
//                    {
//                        flag = 0;
//                        break;
//                    }
//                }
//                if(flag == 0)
//                {
//                    break;
//                }
//            }
//            if(flag == 0)
//            {
//                data[i * width + j] = 255;
//            }
//            else
//            {
//                data[i * width + j] = 0;
//            }
//        }
//    }
//    free(tmpdata);
//}


//八域边界追踪+图像生长算法
void EagalCameraBeaconHandleGraduateAYear(uint8 EagleImgBuffer[Image_Height][Image_Width])
{
//  LED_Ctrl(LED1,RVS);
      squareflag=1;
      uint8 i=0,j=0,k=0,m=0,n=0;
      WavefilteringEdge(EagleImgBuffer);//截取摄像头范围
      WavefilteringPoint(EagleImgBuffer,1);//滤波
      for(i=ABANDONUP+1;i<LINE-ABANDONDOWN-1;i++)                                                 //找边界点
      {
          for(j=ABANDONLEFT+1;j<COLUMN-ABANDONRIGHT-1;j++)
          {
              for(n=0;n<m;n++)
              {
                  if((j<=f_firstmax_X[n])                               //忽略判断过的部分
                     &&(j>=f_firstmin_X[n])
                       &&(i<=f_firstmax_Y[n])
                         &&(i>=f_firstmin_Y[n]))
                  {
                      ignorepoint=1;
                      break;
                  }
              }
              if(ignorepoint == 1)
              {
                  ignorepoint=0;
              }
              else if((EagleImgBuffer[i][j] == WHITE_POINT)
                       &&(EagleImgBuffer[i][j-1] == BLACK_POINT)  //jia
                         &&(EagleImgBuffer[i-1][j-1] == BLACK_POINT)  //jia
                           &&(EagleImgBuffer[i][j+1] == WHITE_POINT)
                             &&(EagleImgBuffer[i+1][j] == WHITE_POINT)             //  0/1 0  0       //    0  0  0
                               &&(EagleImgBuffer[i+1][j+1] == WHITE_POINT)         //  0/1 1  1   gai //    0  1  1
                                 &&(EagleImgBuffer[i-1][j] == BLACK_POINT)         //  0/1 1  1       //  0/1  1  1
                                   &&(EagleImgBuffer[i-1][j+1] == BLACK_POINT)
                                   )
//     &&(EagleImgBuffer[i+1][j-1] == BLACK_POINT))//这行条件是自己加的，，为了形成一个好的框？看到这里
             {
                  BorderX=j;
                  BorderY=i;

                  f_firstarea_X=j+1;
                  f_firstarea_Y=i;

                  k=EightDomainBoundaryTracing(f_firstarea_X,f_firstarea_Y,EagleImgBuffer);
                  //k=FourDomainBoundaryTracing(f_firstarea_X,f_firstarea_Y,EagleImgBuffer);
                  for(n=0;n<k;n++)
                  {
                       if(u8_findpoint_X[n]>f_firstmaxX)
                       {
                           f_firstmaxX=u8_findpoint_X[n];
                       }
                       if(u8_findpoint_Y[n]>f_firstmaxY)
                       {
                           f_firstmaxY=u8_findpoint_Y[n];              //找最大最小边界值
                       }
                       if(u8_findpoint_X[n]<f_firstminX)
                       {
                           f_firstminX=u8_findpoint_X[n];
                       }
                       if(u8_findpoint_Y[n]<f_firstminY)
                       {
                           f_firstminY=u8_findpoint_Y[n];
                       }
                  }
                  if(missionfailed == 0 && k>=5)
                  {
                      for(n=0;n<k;n++)
                      {
                          u8_findpoint_X[n]=0;
                          u8_findpoint_Y[n]=0;
                      }
                      f_firstmax_X[m]=f_firstmaxX;
                      f_firstmax_Y[m]=f_firstmaxY;
                      f_firstmin_X[m]=f_firstminX;
                      f_firstmin_Y[m]=f_firstminY;
                      f_firstmaxX=ABANDONLEFT;
                      f_firstmaxY=ABANDONUP;
                      f_firstminX=COLUMN-ABANDONRIGHT-1;
                      f_firstminY=LINE-ABANDONDOWN-1;
                      area[m]=k;
                      m++;
                      k=0;
                  }
                  else
                  {
                      for(n=0;n<k;n++)
                      {
                          u8_findpoint_X[n]=0;
                          u8_findpoint_Y[n]=0;
                      }
                      f_firstmax_X[m]=f_firstmaxX;
                      f_firstmax_Y[m]=f_firstmaxY;
                      f_firstmin_X[m]=f_firstminX;
                      f_firstmin_Y[m]=f_firstminY;
                      f_firstmaxX=ABANDONLEFT;
                      f_firstmaxY=ABANDONUP;
                      f_firstminX=COLUMN-ABANDONRIGHT-1;
                      f_firstminY=LINE-ABANDONDOWN-1;
                      missionfailed=0;
                      area[m]=0;
                      m++;
                      k=0;
                  }
             }
          }
    }
    for(i=0;i<m;i++)                                    //周长最大区域确定
    {
        if(area[i]>circumferencemax)
        {
//              if(area[i]<*(limitrmin+(int)(f_firstmax_Y[i]+f_firstmin_Y[i])/2)
//                 ||area[i]>*(limitrmax+(int)(f_firstmax_Y[i]+f_firstmin_Y[i])/2))
//              {
//                  continue;                                                                     //周长限制
//              }
            g_u8Bottom_O=(f_firstmax_Y[i]+f_firstmin_Y[i])/2+ f_firstmax_Y[i]-f_firstmin_Y[i];
//            if((g_u8Bottom_O< 0)
//                    || (g_u8Bottom_O>70))//限距离
//                continue;
            width=f_firstmax_X[i]-f_firstmin_X[i];
//            if(width < *(limitrmin+(int)((f_firstmax_Y[i]+f_firstmin_Y[i])/2))
//                    || width > *(limitrmax+(int)((f_firstmax_Y[i]+f_firstmin_Y[i])/2)))//宽度限制
//                continue;
            Roltw=(float)(f_firstmax_X[i]-f_firstmin_X[i])/(f_firstmax_Y[i]-f_firstmin_Y[i]);
            if (Roltw>7.5
                    || Roltw<0.8)
            {
                Roltw=0;                                                                      //长宽比限制
                continue;
            }

//              g_u8Bottom_O=f_firstmax_Y[i]+f_firstmin_Y[i])/2 + f_firstmax_Y[f_areamax]-f_firstmin_Y[f_areamax];
//            uint8 a,b;
//            uint32 newarea=0;
//            for(a=f_firstmin_Y[i];a<=f_firstmax_Y[i];a++)
//                    for(b=f_firstmin_X[i];b<f_firstmax_X[i];b++)
//                        if(EagleImgBuffer[a][b] == WHITE_POINT)
//                            newarea++;
//            Rectangularity=((float)newarea/(f_firstmax_X[i]-f_firstmin_X[i])/(f_firstmax_Y[i]-f_firstmin_Y[i]));
//            if(Rectangularity<0.70)
//              continue;
            f_areamax=i;
            circumferencemax=area[i];
        }
    }

//      for(i=f_firstmin_Y[f_areamax];i<=f_firstmax_Y[f_areamax];i++)
//      {
//          for(j=f_firstmin_X[f_areamax];j<=f_firstmax_X[f_areamax];j++)
//          {
//              if(EagleImgBuffer[i][j] == WHITE_POINT)
//              {
//                  areamax++;                                                      //面积（暂时不用）
//              }
//          }
//      }

    if(squareflag == 1)
    {
          if(m>0 && circumferencemax>0)
          {
               for(i=f_firstmin_Y[f_areamax];i<=f_firstmax_Y[f_areamax];i++)
               {
                   EagleImgBuffer[i][f_firstmin_X[f_areamax]] = WHITE_POINT;
                   EagleImgBuffer[i][f_firstmax_X[f_areamax]] = WHITE_POINT;
               }
               for(i=f_firstmin_X[f_areamax];i<=f_firstmax_X[f_areamax];i++)               //圈出目标区域
               {
                   EagleImgBuffer[f_firstmax_Y[f_areamax]][i] = WHITE_POINT;
                   EagleImgBuffer[f_firstmin_Y[f_areamax]][i] = WHITE_POINT;
               }
          }
//          LED_Ctrl(LED1,RVS);
//          for(i = ((ABANDONUP-1)>0)?(ABANDONUP-1):0 ; i < LINE-ABANDONDOWN ; i++)
//          {
//              u8_EagleImgBufferchange[i][((ABANDONLEFT-1)>0)?(ABANDONLEFT-1):0] = WHITE_POINT;
//              u8_EagleImgBufferchange[i][COLUMN-ABANDONRIGHT] = WHITE_POINT;                          //圈出处理区域
//          }
//          for(i = ((ABANDONLEFT-1)>0)?(ABANDONLEFT-1):0 ; i < COLUMN-ABANDONLEFT ; i++)
//          {
//              u8_EagleImgBufferchange[((ABANDONUP-1)>0)?(ABANDONUP-1):0][i] = WHITE_POINT;
//              u8_EagleImgBufferchange[LINE-ABANDONDOWN][i] = WHITE_POINT;
//          }
         squareflag=0;
    }

    if(m>0 && circumferencemax>0)
    {
        startcar = 1;
        g_u8BeaconLocation =(char)((f_firstmax_X[f_areamax]+f_firstmin_X[f_areamax])/2);//中心点x坐标
        g_u8BeaconLocation_x1=(char)f_firstmax_X[f_areamax];
        g_u8BeaconLocation_x2=(char)f_firstmin_X[f_areamax];


//        if(abs(g_u8BeaconLocation-80)<50)
        g_u8Top=(uint8)((f_firstmax_Y[f_areamax]+f_firstmin_Y[f_areamax])/2);              //最高点y坐标
        g_u8Top_y1=(char)f_firstmax_Y[f_areamax];
        g_u8Top_y2=(char)f_firstmin_Y[f_areamax];
//        g_u8Bottom_O=g_u8Top + (f_firstmax_Y[f_areamax]-f_firstmin_Y[f_areamax]);//底部坐标
//        else
//          g_u8Top=(int)(f_firstmax_Y[f_areamax]+f_firstmin_Y[f_areamax])/2-1;
//        else
//          g_u8Top=(int)(f_firstmax_Y[f_areamax]+f_firstmin_Y[f_areamax])/2-2;
//        g_u8RealTop=(char)g_u8Top;
        newk=area[f_areamax];
//        width=f_firstmax_X[f_areamax]-f_firstmin_X[f_areamax];//宽
//        Roltw=(float)(f_firstmax_X[f_areamax]-f_firstmin_X[f_areamax])/(f_firstmax_Y[f_areamax]-f_firstmin_Y[f_areamax]);//长宽比
        circumferencemax=0;
        g_u8GetBeacon=1;



//        if(g_u8BeaconLocation!=0&&g_u8Top!=0)
//        {
//            g_u8BeaconLocation_true=g_u8BeaconLocation;
//            g_u8Top_true=g_u8Top;
//            i=0;
//            flag=0;
//        }
//        else
//            i++;
//        if(i>=5)
//        {
//            i=5;
//            flag=1;
//        }
//        if(flag==1)
//        {
//            g_u8BeaconLocation_true=0;
//            g_u8Top_true=0;
//        }


        for(i=0;i<m;i++)
        {
            f_firstmax_X[i]=0;
            f_firstmax_Y[i]=0;
            f_firstmin_X[i]=0;                       //清零
            f_firstmin_Y[i]=0;
            area[i]=0;
        }
    }
    else
    {
        g_u8RealTop=0;
//        g_u8Top = 0;
        g_u8BeaconLocation = 0;
        g_u8GetBeacon=0;
        circumferencemax=0;
        g_u8Bottom_O=0;
        width=0;
        for(i=0;i<m;i++)
        {
            f_firstmax_X[i]=0;
            f_firstmax_Y[i]=0;
            f_firstmin_X[i]=0;                       //清零
            f_firstmin_Y[i]=0;
            area[i]=0;
        }
    }
//    LED_Ctrl(LED1,RVS);
 //   Beacon_calculate();
}





//void Deviationdetermination(void)
//{
//  static uint8 Turn;
//         if(g_u8RealTop == 0)
//         {
//           if(g_fDeviation>0)
//              g_fDeviation=g_fDeviation-1;
//           else if(g_fDeviation<0)
//              g_fDeviation=g_fDeviation+1;
//         }
//         else
//         {
//             if(g_u8Threshold==MINThRESHOD)
//                Deviation = g_u8BeaconLocation -(*(pointDevLeft_25+g_u8Top)+changeflag[2]);
//             else
//                Deviation = g_u8BeaconLocation -(*(pointDevLeft_75+g_u8Top));
//
//
//             if(g_u8Threshold==MINThRESHOD)
//                Deviation1 = g_u8BeaconLocation -(*(PointDevRight_25+g_u8Top)-changeflag[2]);
//             else
//                Deviation1 = g_u8BeaconLocation -(*(PointDevRight_75+g_u8Top));
//
//
//             if(abs(Deviation)<abs(Deviation1)-13)
//             {
//               g_fDeviation = Deviation;
//               LightRight = 1;
//               Turn = 1;
//             }
//             else if(abs(Deviation1)<abs(Deviation)-13)
//             {
//               g_fDeviation = Deviation1;
//               LightRight = 0;
//               Turn = 0;
//             }
//             else
//             {
//               if(Turn ==1 )
//               {
//                 g_fDeviation = Deviation;
//                 LightRight = 1;
//               }
//               else
//               {
//                 g_fDeviation = Deviation1;
//                 LightRight = 0;
//               }
//             }
//         }
////        if(Recordflag == 0 && abs(g_fDeviation)<40)
////        {
////
////          if(g_u8Threshold == MAXThRESHOD && g_u8Top < 6)//6
////            Distanceflag = FAR;
////          else
////            Distanceflag = NEAR;
////          Recordflag++;
////        }
//}






uint8 EightDomainBoundaryTracing(uint8 f_firstarea_X,uint8 f_firstarea_Y,uint8 EagleImgBuffer[Image_Height][Image_Width])
{                                     // 8  9 10    0 1 2   0
    uint8 k=0,i=0;                    //15    11    7   3   1   state0  0 1 state1   1 state2  1 0 state3
                                      //14 13 12    6 5 4                            0
    uint8 findstate=0;
                          //1      1     0    0    3    3    2     2      1      1     0    0   3    3     2     2
                          //0      1     2    3    4    5    6     7      8      9    10   11   12   13    14   15
    int Direction[16][2]={{-1,-1}, {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}};//y0 x1
    while(1)
    {
         if(findstate == 0)
         {
             for(i=2;i<9;i++)
             {
                 if(EagleImgBuffer[f_firstarea_Y+Direction[i][0]][f_firstarea_X+Direction[i][1]] == WHITE_POINT)//Pixle数组改了
                 {
                     f_firstarea_X=f_firstarea_X+Direction[i][1];
                     f_firstarea_Y=f_firstarea_Y+Direction[i][0];
                     switch(i-1)
                     {
                         case 1:findstate=1;break;
                         case 2:findstate=0;break;
                         case 3:findstate=0;break;
                         case 4:findstate=3;break;
                         case 5:findstate=3;break;
                         case 6:findstate=2;break;
                         case 7:findstate=2;break;
                     }
                     break;
                 }
             }
         }
         else if(findstate == 1)
         {
             for(i=8;i<15;i++)
             {
                 if(EagleImgBuffer[f_firstarea_Y+Direction[i][0]][f_firstarea_X+Direction[i][1]] == WHITE_POINT)//Pixle数组改了
                 {
                     f_firstarea_X=f_firstarea_X+Direction[i][1];
                     f_firstarea_Y=f_firstarea_Y+Direction[i][0];
                     switch(i-1)
                     {
                         case 7:findstate=2;break;
                         case 8:findstate=1;break;
                         case 9:findstate=1;break;
                         case 10:findstate=0;break;
                         case 11:findstate=0;break;
                         case 12:findstate=3;break;
                         case 13:findstate=3;break;
                     }
                     break;
                 }
             }
         }
         else if(findstate == 2)
         {
             for(i=6;i<13;i++)
             {
                 if(EagleImgBuffer[f_firstarea_Y+Direction[i][0]][f_firstarea_X+Direction[i][1]] == WHITE_POINT)//Pixle数组改了
                 {
                     f_firstarea_X=f_firstarea_X+Direction[i][1];
                     f_firstarea_Y=f_firstarea_Y+Direction[i][0];
                     switch(i-1)
                     {
                         case 5:findstate=3;break;
                         case 6:findstate=2;break;
                         case 7:findstate=2;break;
                         case 8:findstate=1;break;
                         case 9:findstate=1;break;
                         case 10:findstate=0;break;
                         case 11:findstate=0;break;
                     }
                     break;
                 }
             }
         }
         else if(findstate == 3)
         {
             for(i=4;i<11;i++)
             {
                 if(EagleImgBuffer[f_firstarea_Y+Direction[i][0]][f_firstarea_X+Direction[i][1]] == WHITE_POINT)//Pixle数组改了
                 {
                     f_firstarea_X=f_firstarea_X+Direction[i][1];
                     f_firstarea_Y=f_firstarea_Y+Direction[i][0];
                     switch(i-1)
                     {
                         case 3:findstate=0;break;
                         case 4:findstate=3;break;
                         case 5:findstate=3;break;
                         case 6:findstate=2;break;
                         case 7:findstate=2;break;
                         case 8:findstate=2;break;
                         case 9:findstate=1;break;
                     }
                     break;
                 }
             }
         }
         if(k>300)
         {
             missionfailed=1;
             break;
         }

         u8_findpoint_X[k]=f_firstarea_X;
         u8_findpoint_Y[k]=f_firstarea_Y;
         k++;

         if((f_firstarea_X == BorderX)&&(f_firstarea_Y == BorderY))
         {
             break;
         }
    }
    return k;
}



uint8 FourDomainBoundaryTracing(uint8 f_firstarea_X,uint8 f_firstarea_Y,uint8 EagleImgBuffer[60][160])
{
                                        //  0       4
                                        //3   1   7   5
                                        //  2       6
    uint8 k=0,findstate=4,i=0;
                         //0    1    2    3      4    5    6    7
    int Direction[8][2]={{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,0}, {0,1}, {1,0}, {0,-1}};
    while(1)
    {
       for(i=findstate;i<findstate+4;i++)
       {
           if(EagleImgBuffer[f_firstarea_Y+Direction[i][0]][f_firstarea_X+Direction[i][1]] == WHITE_POINT)//Pixle数组改了
           {
               f_firstarea_X=f_firstarea_X+Direction[i][1];
               f_firstarea_Y=f_firstarea_Y+Direction[i][0];
               findstate=(i-1)<0?3:(i-1);
               if(findstate>=5)
                 findstate=findstate-4;
               break;
           }
       }
       if(k>200)
       {
           missionfailed=1;
           break;
       }

       u8_findpoint_X[k]=f_firstarea_X;
       u8_findpoint_Y[k]=f_firstarea_Y;
       k++;

       if((f_firstarea_X == BorderX)&&(f_firstarea_Y == BorderY))
       {
           break;
       }
    }
    return k;
}



void FlashHandle (void)
{
   static uint16 i=0;
   static uint8 g_u8Top_last = 0;
   static uint8 g_u8BeaconLocation_last = 0;
   if (g_u8GetBeacon == 0) i++;
   if(i>500) i=500;

   if(i>=400)
   {
      loseBeacon = 1;
      g_u8Top = 0;
      g_u8BeaconLocation = 0;
    }
   else
   {
       loseBeacon = 0;
       g_u8Top = g_u8Top_last;
       g_u8BeaconLocation = g_u8BeaconLocation_last;
   }

   if (g_u8GetBeacon == 1)
   {

      loseBeacon = 0;
      i = 0;
      g_u8Top_last = g_u8Top;
      g_u8BeaconLocation_last = g_u8BeaconLocation;
   }


}
