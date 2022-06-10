/*!
  * @file     ANO_DT.h
  *
  * @brief    
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     Tab键 4个空格
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2020年6月5日
  */ 
#ifndef SRC_APPSW_TRICORE_USER_ANO_DT_H_
#define SRC_APPSW_TRICORE_USER_ANO_DT_H_

#include "headfile.h"//各个模块的头文件


void ANO_DT_Send_Data(uint8 *dataToSend , uint16 length);

/*!
  * @brief    向上位机发送发送8个int16_t数据
  *
  * @param    data1 - data8  ： 发送给上位机显示波形
  *
  * @return   无
  *
  * @note     无
  *
  * @see      ANO_DT_send_int16(1, 2, 3, 0, 0, 0, 0, 0);
  *
  * @date     2019/5/28 星期二
  */
//void ANO_DT_send_int16(sint16 data1, sint16 data2, sint16 data3, sint16 data4, sint16 data5, sint16 data6, sint16 data7, sint16 data8 );
void ANO_DT_send_int16(int data1, int data2, int data3, int data4);
#endif /* SRC_APPSW_TRICORE_USER_ANO_DT_H_ */
