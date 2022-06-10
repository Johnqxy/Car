/*
 * OLED_Dis_Num.h
 *
 *  Created on: 2020年10月11日
 *      Author: Javelin
 */

#ifndef SRC_APPSW_TRICORE_USER_OLED_H_
#define SRC_APPSW_TRICORE_USER_OLED_H_

extern unsigned char Pixle[MT9V03X_H][MT9V03X_W];
extern uint8 Threshold;
extern char txt[32];
void oled_show_position(void);
//int GetOSTU(uint8 tmImage[MT9V03X_H][MT9V03X_W]);
void Pixle_ADD_Midline(void);
void Get_01_Value(unsigned char mode);
void GetThreshold(void);
void Pixle_ADD_My_Midline();
void Pixle_ADD_My_hengxian(int m);
extern struct Threshold_Information myThreshold;

struct Threshold_Information
{
  uint8 Threshold_0_4;//基础速度
  uint8 Threshold_5_9;
  uint8 Threshold_10_14;
  uint8 Threshold_15_19;
  uint8 Threshold_20_24;
  uint8 Threshold_25_29;
  uint8 Threshold_30_34;
  uint8 Threshold_35_39;
  uint8 Threshold_40_44;
  uint8 Threshold_45_49;
  uint8 Threshold_50_54;
  uint8 Threshold_55_59;
  uint8 Threshold_60_64;
};


#endif /* SRC_APPSW_TRICORE_USER_OLED_H_ */
