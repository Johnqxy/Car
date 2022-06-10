/*
 * OLED_Dis_Num.c
 *
 *  Created on: 2020年10月11日
 *      Author: Javelin
 */

#include "headfile.h"//各个模块的头文件
char txt[32];
uint8 Threshold;
struct Threshold_Information myThreshold;

                         //  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49
//int PointDevLeft[50] =  {  0,-10,-10,-10,-11,-12,-14,-16,-18,-19,-20,-21,-22,-24,-25,-28,-30,-31,-32,-34,-35,-36,-38,-39,-40,-42,-44,-46,-49,-50,-51,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52};
uint8 *pointThreshold = &myThreshold.Threshold_0_4;  // 灯左侧过
//top:

/** 二值化后用于OLED显示的数据 */
unsigned char Pixle[MT9V03X_H][MT9V03X_W];

void oled_show_position(void)
{

//    oled_printf_int32(25,1,g_u8GetBeacon,1);


    oled_printf_int32(25,1,Infrared_error,2);

}


void GetThreshold(void)
{
    static uint8 no_light_Threshold_flag= 0;
    if(!g_u8GetBeacon||g_u8Top<17)
    {
        Threshold = *pointThreshold;
//        if(!no_light_Threshold_flag)
//        {
//        Threshold = *pointThreshold;
//        no_light_Threshold_flag = 1;
//        }
//        else if(no_light_Threshold_flag)
//        {
//            Threshold = *pointThreshold+30;
//            no_light_Threshold_flag = 0;
//        }
    }

    else
        Threshold = *(pointThreshold+1);
//    else Threshold = *(pointThreshold+1);

}

//uint16 Threshold_last = 0;
//float HistoGram[256];
//
//int GetOSTU(uint8 tmImage[MT9V03X_H][MT9V03X_W])
//{
//    memset(HistoGram,0,sizeof(float) * 256); //初始化灰度直方图
////    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);         //获取最小灰度的值
////    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--);  //获取最大灰度的值
////    if (MaxValue == MinValue)     return MaxValue;         // 图像中只有一个颜色
////    if (MinValue + 1 == MaxValue)  return MinValue;        // 图像中只有二个颜色
//
//    float u = 0;
//    int size = MT9V03X_W * MT9V03X_H;
//    uint16 Threshold;
//    for (int j = 0; j < MT9V03X_H; j++)
//    {
//        for (int i = 0; i < MT9V03X_W; i++)
//        {
//            HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
//        }
//    }
//    for(int i = 0; i < 256; i++)
//    {
//        HistoGram[i] /= size;
//        u += i * HistoGram[i];
//    }
//
//    float maxval,w0,avg = 0;
//    for(uint16 i = 0; i < 256; i++)
//    {
//        w0 += HistoGram[i];
//        avg += i * HistoGram[i];
//
//        float t = avg / w0 - u;
//        float val = t * t * w0 / (1 - w0);
//        if(val > maxval)
//        {
//            maxval = val;
//            Threshold = i;
//        }
//    }
//    if((fabs(Threshold_last))-(fabs(Threshold))>myCar.Threshold_Error) Threshold = Threshold_last;
//    Threshold_last = Threshold;
//    return Threshold;                        //返回最佳阈值;
//}


//
//int GetOSTU(unsigned char tmImage[MT9V03X_H][MT9V03X_W])
//{
//    signed short i,j;
//    unsigned long Amount = 0;
//    unsigned long PixelBack = 0;
//    unsigned long PixelIntegralBack = 0;
//    unsigned long PixelIntegral = 0;
//    signed long PixelIntegralFore = 0;
//    signed long PixelFore = 0;
//    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
//    signed short MinValue, MaxValue;
//    unsigned short Threshold = 0;
//
//    unsigned char HistoGram[256];              //
//
//    for (j = 0; j < 256; j++)  HistoGram[j] = 0; //初始化灰度直方图
//
//    for (j = 0; j < MT9V03X_H; j++)
//    {
//        for (i = 0; i < MT9V03X_W; i++)
//        {
//            HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
//        }
//    }
//
//    for (MinValue = 0;   MinValue < 256      && HistoGram[MinValue] == 0; MinValue++) ;        //获取最小灰度的值
//    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //获取最大灰度的值
//
//    if (MaxValue == MinValue)     return MaxValue;         // 图像中只有一个颜色
//    if (MinValue + 1 == MaxValue)  return MinValue;        // 图像中只有二个颜色
//
//    for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];        //  像素总数
//
//    PixelIntegral = 0;
//    for (j = MinValue; j <= MaxValue; j++)
//    {
//        PixelIntegral += HistoGram[j] * j;//灰度值总数
//    }
//    SigmaB = -1;
//    for (j = MinValue; j < MaxValue; j++)
//    {
//        PixelBack = PixelBack + HistoGram[j];   //前景像素点数
//        PixelFore = Amount - PixelBack;         //背景像素点数
//        OmegaBack = (float)PixelBack / Amount;//前景像素百分比
//        OmegaFore = (float)PixelFore / Amount;//背景像素百分比
//        PixelIntegralBack += HistoGram[j] * j;  //前景灰度值
//        PixelIntegralFore = PixelIntegral - PixelIntegralBack;//背景灰度值
//        MicroBack = (float)PixelIntegralBack / PixelBack;   //前景灰度百分比
//        MicroFore = (float)PixelIntegralFore / PixelFore;   //背景灰度百分比
//        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//计算类间方差
//        if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
//        {
//            SigmaB = Sigma;
//            Threshold = j;
//        }
//    }
//
//    if((fabs(Threshold_last))-(fabs(Threshold))>myCar.Threshold_Error) Threshold = Threshold_last;
//    Threshold_last = Threshold;
//    if(Threshold>=110) Threshold = 110;
//    if(loseBeacon)  Threshold = (unsigned short)myCar.loseBeacon_Threshold;
//    return Threshold;                        //返回最佳阈值;
//}

//uint8 Pixle_Midline[MT9V03X_H][MT9V03X_W];
void Pixle_ADD_Midline(void)
{

    uint8 i = 0;
    for(i = 0;i<MT9V03X_H;i++)
    {
        Pixle[i][MT9V03X_W/2-1] = 128;
    }
}
void Pixle_ADD_My_Midline() {

    uint8 i = 0;
    for (i = 0; i < MT9V03X_H; i++) {
        image_cache[i][centerline[i]] = 0;
        image_cache[i][centerline[i] + 1] = 0;
        image_cache[i][centerline[i] - 1] = 0;
    }
}

void Pixle_ADD_My_hengxian(int m) {

    uint8 i = 0;
    for (i = 0; i < MT9V03X_W; i++) {
        image_cache[m][i] = 128;
    }
}
void Get_01_Value(unsigned char mode)
{
  int i = 0,j = 0;
  int Threshold;
//  unsigned long  tv=0;
//  char txt[16];

//  if(mode)
//  {
//
      Threshold = mode;
      for(i = 0; i < MT9V03X_H; i++)
      {
        for(j = 0; j < MT9V03X_W; j++)
        {
          if(mt9v03x_image[i][j] >Threshold) //数值越小，显示的内容越多，较浅的图像也能显示出来
            Pixle[i][j] =255;
          else
            Pixle[i][j] =0;
        }
//      }
//      //累加
//      for(i = 0; i <LCDH; i++)
//      {
//          for(j = 0; j <LCDW; j++)
//          {
//              tv+=Image_Use[i][j];   //累加
//          }
//      }
//      Threshold=tv/LCDH/LCDW;        //求平均值,光线越暗越小，全黑约35，对着屏幕约160，一般情况下大约100
//      Threshold=Threshold*7/10+10;   //此处阈值设置，根据环境的光线来设定

  }
//  else
//  {
//      Threshold = GetOSTU(Image_Use);//大津法阈值
//      Threshold = (unsigned char)(Threshold * 0.5) + 70;
//  }
//#ifdef USEOLED
//  sprintf(txt,"%03d",Threshold);//前者为大津法求得的阈值，后者为平均值
//  OLED_6x8Str(80,0,txt);
//#else
//  sprintf(txt,"%03d",Threshold);//前者为大津法求得的阈值，后者为平均值
//  TFTSPI_P8X8Str(0,15, txt,u16RED,u16BLUE);
//#endif

}


