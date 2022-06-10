/*
 * OLED_Dis_Num.c
 *
 *  Created on: 2020��10��11��
 *      Author: Javelin
 */

#include "headfile.h"//����ģ���ͷ�ļ�
char txt[32];
uint8 Threshold;
struct Threshold_Information myThreshold;

                         //  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49
//int PointDevLeft[50] =  {  0,-10,-10,-10,-11,-12,-14,-16,-18,-19,-20,-21,-22,-24,-25,-28,-30,-31,-32,-34,-35,-36,-38,-39,-40,-42,-44,-46,-49,-50,-51,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52};
uint8 *pointThreshold = &myThreshold.Threshold_0_4;  // ������
//top:

/** ��ֵ��������OLED��ʾ������ */
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
//    memset(HistoGram,0,sizeof(float) * 256); //��ʼ���Ҷ�ֱ��ͼ
////    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);         //��ȡ��С�Ҷȵ�ֵ
////    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--);  //��ȡ���Ҷȵ�ֵ
////    if (MaxValue == MinValue)     return MaxValue;         // ͼ����ֻ��һ����ɫ
////    if (MinValue + 1 == MaxValue)  return MinValue;        // ͼ����ֻ�ж�����ɫ
//
//    float u = 0;
//    int size = MT9V03X_W * MT9V03X_H;
//    uint16 Threshold;
//    for (int j = 0; j < MT9V03X_H; j++)
//    {
//        for (int i = 0; i < MT9V03X_W; i++)
//        {
//            HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
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
//    return Threshold;                        //���������ֵ;
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
//    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��;
//    signed short MinValue, MaxValue;
//    unsigned short Threshold = 0;
//
//    unsigned char HistoGram[256];              //
//
//    for (j = 0; j < 256; j++)  HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ
//
//    for (j = 0; j < MT9V03X_H; j++)
//    {
//        for (i = 0; i < MT9V03X_W; i++)
//        {
//            HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
//        }
//    }
//
//    for (MinValue = 0;   MinValue < 256      && HistoGram[MinValue] == 0; MinValue++) ;        //��ȡ��С�Ҷȵ�ֵ
//    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //��ȡ���Ҷȵ�ֵ
//
//    if (MaxValue == MinValue)     return MaxValue;         // ͼ����ֻ��һ����ɫ
//    if (MinValue + 1 == MaxValue)  return MinValue;        // ͼ����ֻ�ж�����ɫ
//
//    for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];        //  ��������
//
//    PixelIntegral = 0;
//    for (j = MinValue; j <= MaxValue; j++)
//    {
//        PixelIntegral += HistoGram[j] * j;//�Ҷ�ֵ����
//    }
//    SigmaB = -1;
//    for (j = MinValue; j < MaxValue; j++)
//    {
//        PixelBack = PixelBack + HistoGram[j];   //ǰ�����ص���
//        PixelFore = Amount - PixelBack;         //�������ص���
//        OmegaBack = (float)PixelBack / Amount;//ǰ�����ذٷֱ�
//        OmegaFore = (float)PixelFore / Amount;//�������ذٷֱ�
//        PixelIntegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
//        PixelIntegralFore = PixelIntegral - PixelIntegralBack;//�����Ҷ�ֵ
//        MicroBack = (float)PixelIntegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
//        MicroFore = (float)PixelIntegralFore / PixelFore;   //�����ҶȰٷֱ�
//        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//������䷽��
//        if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
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
//    return Threshold;                        //���������ֵ;
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
          if(mt9v03x_image[i][j] >Threshold) //��ֵԽС����ʾ������Խ�࣬��ǳ��ͼ��Ҳ����ʾ����
            Pixle[i][j] =255;
          else
            Pixle[i][j] =0;
        }
//      }
//      //�ۼ�
//      for(i = 0; i <LCDH; i++)
//      {
//          for(j = 0; j <LCDW; j++)
//          {
//              tv+=Image_Use[i][j];   //�ۼ�
//          }
//      }
//      Threshold=tv/LCDH/LCDW;        //��ƽ��ֵ,����Խ��ԽС��ȫ��Լ35��������ĻԼ160��һ������´�Լ100
//      Threshold=Threshold*7/10+10;   //�˴���ֵ���ã����ݻ����Ĺ������趨

  }
//  else
//  {
//      Threshold = GetOSTU(Image_Use);//�����ֵ
//      Threshold = (unsigned char)(Threshold * 0.5) + 70;
//  }
//#ifdef USEOLED
//  sprintf(txt,"%03d",Threshold);//ǰ��Ϊ�����õ���ֵ������Ϊƽ��ֵ
//  OLED_6x8Str(80,0,txt);
//#else
//  sprintf(txt,"%03d",Threshold);//ǰ��Ϊ�����õ���ֵ������Ϊƽ��ֵ
//  TFTSPI_P8X8Str(0,15, txt,u16RED,u16BLUE);
//#endif

}


